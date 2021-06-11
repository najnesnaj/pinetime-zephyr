/*
 * Copyright (c) 2021 najnesnaj@yahoo.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/gpio.h>
#include <drivers/sensor.h>
#include <stdbool.h>
//#include <pm/pm.h>
#include "battery.h"
#include "bt.h"
#include "clock.h"
#include "display.h"
#include "event_handler.h"
#include "log.h"
#include "buttons.h"

/* ********** defines ********** */
#define BAT_CHA 2 //jj
#define BTN_PORT DT_GPIO_LABEL(DT_ALIAS(sw0), gpios)
#define BTN_IN  DT_GPIO_PIN(DT_ALIAS(sw0), gpios)
#define BTN_OUT 3 //jj 
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_DOUBLE_EDGE)
#define PULL_UP DT_GPIO_FLAGS(DT_ALIAS(sw0), gpios)
#define LOW_POWER_TIMEOUT K_SECONDS(50) //switch to low power after 50 seconds
#define CLOCK_UPDATE K_SECONDS(20) //jj every minute clock should get update 
/* ********** ******* ********** */

/* ********** variables ********** */
static struct k_timer low_power_timer; //jj
static struct k_timer clock_update_timer; //jj

/* ********** ******* ********** */
/* setup buttons **** ********** */
/* ********** ******* ********** */

//when used with the native_posix_64 virtual device there are no buttons ...
//#if !(defined(CONFIG_BOARD_NATIVE_POSIX_64BIT))

#define SW0_NODE        DT_ALIAS(sw0)

#if DT_NODE_HAS_STATUS(SW0_NODE, okay)
#define SW0_GPIO_LABEL  DT_GPIO_LABEL(SW0_NODE, gpios)
#define SW0_GPIO_PIN    DT_GPIO_PIN(SW0_NODE, gpios)
#define SW0_GPIO_FLAGS  (GPIO_INPUT | DT_GPIO_FLAGS(SW0_NODE, gpios))
#else
//#error "Unsupported board: sw0 devicetree alias is not defined"
#define SW0_GPIO_LABEL  ""
#define SW0_GPIO_PIN    0
#define SW0_GPIO_FLAGS  0
#endif

#if defined(CONFIG_BOARD_PINETIME_DEVKIT1) //pinetime needs port 15 high for switch to work
#define SW1_NODE        DT_ALIAS(sw1)
#define SW1_GPIO_PIN    DT_GPIO_PIN(SW1_NODE, gpios)
#define SW1_GPIO_FLAGS  (GPIO_OUTPUT | DT_GPIO_FLAGS(SW1_NODE, gpios))
#define BUTTON_THRESH 4 //threshold to distinguish between short and long press
#define BUTTON_DOUBLE_THRESH 2 //double click
#endif

#if defined(CONFIG_BOARD_NATIVE_POSIX_64BIT)
#define BUTTON_THRESH 8 //threshold to distinguish between short and long press
//when used in a real watch it will probable have to be less
#define BUTTON_DOUBLE_THRESH 12 //double click
#endif

#if defined(CONFIG_BOARD_DS_D6)
#define BUTTON_THRESH 3 //threshold to distinguish between short and long press
#define BUTTON_DOUBLE_THRESH 2 //double click
#endif



static uint8_t button_press_cnt;
//struct k_timer button_timer;




//when the timer expires the number of presses is analysed
void button_timer_handler(struct k_timer *dummy)
{
	LOG_INF("timer expired\n");
	LOG_INF("press count %d\n", button_press_cnt);
	//if (button_press_cnt >= BUTTON_DOUBLE_THRESH){
	if (button_press_cnt > BUTTON_THRESH){
		LOG_INF("long press\n");
		display_btn_event(BTN1_LONG);
	}
	if (button_press_cnt <= BUTTON_THRESH){ //short press is used to scroll trough the labels with their value
		LOG_INF("short press\n");
		display_btn_event(BTN1_SHORT);
	}
//	if ((button_press_cnt > BUTTON_THRESH) && (button_press_cnt < BUTTON_DOUBLE_THRESH)){
//		LOG_INF("double click\n");

		//todo no function linked to double click
//	}
	button_press_cnt=0;


}

/*timer used to detect lenght of pushing*/
struct k_timer button_timer;
K_TIMER_DEFINE(button_timer, button_timer_handler,NULL);





void button_pressed(const struct device *dev, struct gpio_callback *cb,
		uint32_t pins)
{
	buttons_id_t btn_id;
        low_power_off();
	LOG_INF("Button pressed at %" PRIu32 "\n", k_cycle_get_32());

	if (button_press_cnt == 0U) {
		k_timer_start(&button_timer, K_SECONDS(1), K_NO_WAIT);
		btn_id=BTN1_SHORT;
	}

	if (k_timer_status_get(&button_timer) > 0) {
		/* timer has expired */
		//display_btn_event(BTN1_SHORT);
		button_press_cnt=0;
	} else  {
		/* timer still running */
		button_press_cnt++;
	}


}

//this is used in case of native_posix -- virtual button
void button_event_cb(lv_obj_t * obj, lv_event_t event)
{

        LOG_INF("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
        if (button_press_cnt == 0U) {
                k_timer_start(&button_timer, K_SECONDS(1), K_NO_WAIT);
        low_power_off();
                printf("Buttontime started" );
        }

        if (k_timer_status_get(&button_timer) > 0) {
                button_press_cnt=0;
        } else  {
                /* timer still running */
                button_press_cnt++;
        }

}


static struct gpio_callback button_cb_data;

void init_button(void)
{
	const struct device *button;
	int ret;
	button = device_get_binding(SW0_GPIO_LABEL);
	if (button == NULL) {
		printk("Error: didn't find %s device\n", SW0_GPIO_LABEL);
		return;
	}

	ret = gpio_pin_configure(button, SW0_GPIO_PIN, SW0_GPIO_FLAGS);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
				ret, SW0_GPIO_LABEL, SW0_GPIO_PIN);
		return;
	}

	ret = gpio_pin_interrupt_configure(button,
			SW0_GPIO_PIN,
			GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
				ret, SW0_GPIO_LABEL, SW0_GPIO_PIN);
		return;
	}
#if defined(CONFIG_BOARD_PINETIME_DEVKIT1)
	//port 15 has to be high in order for the button to work


	gpio_pin_configure(button, SW1_GPIO_PIN,SW1_GPIO_FLAGS); //push button out
	gpio_pin_set(button, SW1_GPIO_PIN, 1); //set port high



#endif



	gpio_init_callback(&button_cb_data, button_pressed, BIT(SW0_GPIO_PIN));
	gpio_add_callback(button, &button_cb_data);
	printk("Set up button at %s pin %d\n", SW0_GPIO_LABEL, SW0_GPIO_PIN);



}
//#endif

//static struct gpio_callback button_cb;

/* ********** ********* ********** */
void low_power_on()
{
	backlight_switch(false);
	LOG_INF("low power on\n");//jj
	display_sleep();
}

void low_power_off()
{
//	int pm_device_state_get(const struct device *dev, uint32_t *device_power_state)
	display_wake_up(); //switches power mode to active
#if !(defined(CONFIG_BOARD_NATIVE_POSIX_64BIT))
	display_init();
#endif
	k_timer_stop(&low_power_timer); //in case the timer was already running
        k_timer_init(&low_power_timer, low_power_on, NULL); //the timer for powersave is started agair
	k_timer_start(&low_power_timer, LOW_POWER_TIMEOUT, K_NO_WAIT);
	//k_timer_start(display_off,CLOCK_UPDATE, K_NO_WAIT);
}

/* ********** init function ********** */
void event_handler_init()
{

	/* Start timers */
	k_timer_init(&clock_update_timer, handle_clock_update, NULL); //jj
	k_timer_start(&clock_update_timer,CLOCK_UPDATE, K_NO_WAIT); //jj
	low_power_off();
//        k_timer_init(&low_power_timer, low_power_on, NULL);
//	k_timer_start(&low_power_timer, LOW_POWER_TIMEOUT, K_NO_WAIT);

	clock_show_time();

	LOG_DBG("Event handler init: Done");
}
/* ********** ************ ********** */

/* ********** interrupt handlers ********** */


void button_pressed_isr(const struct device *gpiobtn, struct gpio_callback *cb, uint32_t pins)
{
	//backlight_switch(true);

	printk("button_pressed_isr\n");
	handle_button_event();
}


void handle_clock_update(struct k_timer *clock_update) //jj if clock displayed, it should get the updated time
{
	printk("handle_clock_update\n");
	clock_increment_local_time();
	clock_show_time();
	display_clock_update(); //multiple screens but clock only appears in 1st
	k_timer_start(clock_update,CLOCK_UPDATE, K_NO_WAIT); //timer gets started again -- perpetuum mobile
}


/* ********** ************** ********** */
int handle_button_event(void)
{
//	k_timer_start(&display_off_timer, DISPLAY_TIMEOUT, K_NO_WAIT);
	clock_increment_local_time();
	clock_show_time();
//	display_on_isr();//switch to actice state wake up display
	return 1;
}


/*
 * Copyright (c) 2021 najnesnaj@yahoo.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/gpio.h>
#include <drivers/sensor.h>
#include <stdbool.h>
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
#define DISPLAY_TIMEOUT K_SECONDS(500) //jj suppose you leave display on -- time should be updated
#define CLOCK_UPDATE K_SECONDS(20) //jj every minute clock should get update 
/* ********** ******* ********** */

/* ********** variables ********** */
static struct k_timer clock_update_timer; //jj

/* ********** ******* ********** */
/* setup buttons **** ********** */
/* ********** ******* ********** */

//when used with the native_posix_64 virtual device there are no buttons ...
#if !(defined(CONFIG_BOARD_NATIVE_POSIX_64BIT))

#define SW0_NODE        DT_ALIAS(sw0)

#if DT_NODE_HAS_STATUS(SW0_NODE, okay)
#define SW0_GPIO_LABEL  DT_GPIO_LABEL(SW0_NODE, gpios)
#define SW0_GPIO_PIN    DT_GPIO_PIN(SW0_NODE, gpios)
#define SW0_GPIO_FLAGS  (GPIO_INPUT | DT_GPIO_FLAGS(SW0_NODE, gpios))
#else
#error "Unsupported board: sw0 devicetree alias is not defined"
#define SW0_GPIO_LABEL  ""
#define SW0_GPIO_PIN    0
#define SW0_GPIO_FLAGS  0
#endif

#if (defined(CONFIG_BOARD_PINETIME_DEVKIT1)||defined(CONFIG_BOARD_PINETIME_DEVKIT0)) //pinetime needs port 15 high for switch to work
#define SW1_NODE        DT_ALIAS(sw1)
#define SW1_GPIO_PIN    DT_GPIO_PIN(SW1_NODE, gpios)
#define SW1_GPIO_FLAGS  (GPIO_OUTPUT | DT_GPIO_FLAGS(SW1_NODE, gpios))
#endif



//todo
//distinction has to made between multiple presses, long press, short press in order to navigate the screen


static uint8_t button_press_cnt;
struct k_timer button_timer;
void button_pressed(const struct device *dev, struct gpio_callback *cb,
		uint32_t pins)
{
	buttons_id_t btn_id;

	LOG_INF("Button pressed at %" PRIu32 "\n", k_cycle_get_32());

	if (button_press_cnt == 0U) {
		k_timer_start(&button_timer, K_SECONDS(1), K_NO_WAIT);
		btn_id=BTN1_SHORT;
	}

	if (k_timer_status_get(&button_timer) > 0) {
		/* timer has expired */
		LOG_INF("SHORT PRESS EVENT %02x\n", button_press_cnt);
		if (button_press_cnt > 2){
			display_btn_event(BTN1_LONG);
		}
		else
			display_btn_event(BTN1_SHORT);
		button_press_cnt=0;
	} else  {
		/* timer still running */
		button_press_cnt++;
		if (button_press_cnt > 2){
			LOG_INF("LONG PRESS EVENT %02x\n", button_press_cnt);
			//      display_btn_event(BTN1_LONG);
		}
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
#if (defined(CONFIG_BOARD_PINETIME_DEVKIT1)||defined(CONFIG_BOARD_PINETIME_DEVKIT0)) //pinetime needs port 15 high for switch to work
//#if defined(CONFIG_BOARD_PINETIME_DEVKIT1)
//port 15 has to be high in order for the button to work


        gpio_pin_configure(button, SW1_GPIO_PIN,SW1_GPIO_FLAGS); //push button out
        gpio_pin_set(button, SW1_GPIO_PIN, 1); //set port high



#endif



	gpio_init_callback(&button_cb_data, button_pressed, BIT(SW0_GPIO_PIN));
	gpio_add_callback(button, &button_cb_data);
	printk("Set up button at %s pin %d\n", SW0_GPIO_LABEL, SW0_GPIO_PIN);



}
#endif

//static struct gpio_callback button_cb;

/* ********** ********* ********** */


/* ********** init function ********** */
void event_handler_init()
{

	/* Start timers */
	k_timer_init(&clock_update_timer, handle_clock_update, NULL); //jj
	k_timer_start(&clock_update_timer,CLOCK_UPDATE, K_NO_WAIT); //jj

	clock_show_time();

	LOG_DBG("Event handler init: Done");
}
/* ********** ************ ********** */

/* ********** interrupt handlers ********** */


void button_pressed_isr(const struct device *gpiobtn, struct gpio_callback *cb, uint32_t pins)
{
	//backlight_switch(true);

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
	clock_increment_local_time();
	clock_show_time();
	return 1;
}


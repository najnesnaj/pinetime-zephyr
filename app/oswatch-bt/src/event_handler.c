/*
 * Copyright (c) 2021 Jan Jansen     najnesnaj@yahoo.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/gpio.h>
#include <drivers/sensor.h>
//#include <drivers/sensor/cst816s.h>
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
#define DISPLAY_TIMEOUT K_SECONDS(5)
#ifdef CONFIG_BOOTLOADER_MCUBOOT
/* The watchdog released by the PineTime bootloader v5.0.0-rc1
 * will try to bite every 7 seconds.
 */
#define WDT_REFRESH 6
#endif
/* ********** ******* ********** */

/* ********** variables ********** */
#ifdef CONFIG_BOOTLOADER_MCUBOOT
static struct k_timer watchdog_refresh_timer;
#endif
static struct k_timer display_off_timer;
static const struct device *charging_dev;
//static struct gpio_callback charging_cb;
//static const struct device *button_dev;
//static struct gpio_callback button_cb;


//when used with the native_posix_64 virtual device there are no buttons ...
#if !(defined(CONFIG_BOARD_NATIVE_POSIX_64BIT)||defined(CONFIG_BOARD_NRF52_BSIM))
//#if (defined(CONFIG_BOARD_DS_D6) || defined(CONFIG_BOARD_PINETIME_DEVKIT1))

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

#if defined(CONFIG_BOARD_PINETIME_DEVKIT1) //pinetime needs port 15 high for switch to work
#define SW1_NODE        DT_ALIAS(sw1)
#define SW1_GPIO_PIN    DT_GPIO_PIN(SW1_NODE, gpios)
#define SW1_GPIO_FLAGS  (GPIO_OUTPUT | DT_GPIO_FLAGS(SW1_NODE, gpios))
#endif



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



	//	printk("button_press_cnt 0x%02x\n", button_press_cnt);
	//	button_press_cnt++;



	// 	LOG_INF("Button time %d\n", button_time);
	//      sensor_attr_set(dev, SENSOR_CHAN_LIGHT, SENSOR_ATTR_SAMPLING_FREQUENCY,0x22);
	//	button_time_previous = k_cycle_get32();
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
#endif

//static struct gpio_callback button_cb;

/* ********** ********* ********** */


/* ********** init function ********** */
void event_handler_init()
{
	/*
#if !(defined(CONFIG_BOARD_NATIVE_POSIX_64BIT))
	//	charging_dev = device_get_binding("GPIO_0");
	gpio_pin_configure(charging_dev, BAT_CHA, GPIO_INPUT | GPIO_INT_EDGE_BOTH);
	//	gpio_init_callback(&charging_cb, battery_charging_isr, BIT(BAT_CHA));
	button_dev = device_get_binding(BTN_PORT);
	gpio_pin_configure(button_dev, BTN_IN, GPIO_INPUT | GPIO_INT_EDGE_FALLING | PULL_UP);
	gpio_init_callback(&button_cb, button_pressed_isr, BIT(BTN_IN));

	gpio_add_callback(charging_dev, &charging_cb);
	gpio_add_callback(button_dev, &button_cb);

	uint32_t button_out = 1U;
	gpio_pin_configure(button_dev, BTN_OUT, GPIO_OUTPUT);
	gpio_pin_set_raw(button_dev, BTN_OUT, button_out);

#endif
	 */

	/* Start timers */
#ifdef CONFIG_BOOTLOADER_MCUBOOT
	if (NRF_WDT->RUNSTATUS) {
		LOG_INF("Watchdog detected. Let's kick it every %d seconds.",
				WDT_REFRESH);
		k_timer_init(&watchdog_refresh_timer, watchdog_refresh_isr,
				NULL);
		k_timer_start(&watchdog_refresh_timer, K_NO_WAIT,
				K_SECONDS(WDT_REFRESH));
	} else {
		LOG_INF("No watchdog detected.");
	}
#endif
	k_timer_init(&display_off_timer, display_off_isr, NULL);
	k_timer_start(&display_off_timer, DISPLAY_TIMEOUT, K_NO_WAIT);

	/* Special cases */
	/* Get battery charging status */
	//	k_sleep(K_MSEC(10));
	//	uint32_t res =  gpio_pin_get(charging_dev, BAT_CHA);
	//	battery_update_charging_status(res != 1U);

	/* Show time, date and battery status */
	clock_show_time();
	//	battery_show_status();

	LOG_DBG("Event handler init: Done");
}
/* ********** ************ ********** */

/* ********** interrupt handlers ********** */
#ifdef CONFIG_BOOTLOADER_MCUBOOT
void watchdog_refresh_isr(struct k_timer *wdt_refresh)
{
	NRF_WDT->RR[0] = WDT_RR_RR_Reload;
}
#endif

void display_off_isr(struct k_timer *light_off)
{
	//	backlight_enable(false);
	//display_sleep();
}

void battery_charging_isr(const struct device *gpiobat, struct gpio_callback *cb, uint32_t pins)
{
	uint32_t res = gpio_pin_get(charging_dev, BAT_CHA);
	battery_update_charging_status(res != 1U);
}

void button_pressed_isr(const struct device *gpiobtn, struct gpio_callback *cb, uint32_t pins)
{
	//display_wake_up();
	//backlight_enable(true);
	k_timer_start(&display_off_timer, DISPLAY_TIMEOUT, K_NO_WAIT);

	handle_button_event();
}


/* ********** ************** ********** */
int handle_button_event(void)
{
	clock_increment_local_time();
	clock_show_time();
	//      battery_show_status();
	//gfx_update();
	return 1;
}


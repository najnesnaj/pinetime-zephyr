/*
 * Copyright (c) 2021 <najnesnaj@yahoo.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/display.h>
#include <drivers/gpio.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>

#include "display.h"
#include "buttons.h"
#include "clock.h"
#include <logging/log.h>
LOG_MODULE_REGISTER(display, 3);

const static struct device * display_dev;

#define SCREEN_ID_0    0
#define SCREEN_ID_1    1
#define SCREEN_ID_2    2
#define SCREEN_ID_3    3
#define SCREEN_COUNT   4

#define PARAM_ID_0      0
#define PARAM_ID_1      1
#define PARAM_ID_2      2
#define PARAM_ID_3      3
#define PARAM_COUNT     3  //4

enum battery_symbol {
	BAT_CHARGE,
	BAT_FULL,
	BAT_3,
	BAT_2,
	BAT_1,
	BAT_EMPTY
};



void display_timer_handler(struct k_timer * timer);
void display_task_handler(struct k_work * work);

K_TIMER_DEFINE(display_timer, display_timer_handler, NULL);

K_WORK_DEFINE(display_work, display_task_handler);

#define TICK_PERIOD   (10)

/*---------------------------------------------------------------------------*/
void display_task_handler(struct k_work * work)
{
	lv_tick_inc(TICK_PERIOD);
	lv_task_handler();
}

/*---------------------------------------------------------------------------*/
void display_timer_handler(struct k_timer * timer)
{
	k_work_submit(&display_work);
}

/*---------------------------------------------------------------------------*/

typedef struct {
	lv_obj_t     ** object; 
	short         * value;
	short           step;
	short           max;
	short           min;
} param_t;

typedef struct {
	lv_obj_t * screen;
	int        count;
} screens_t;

/*---------------------------------------------------------------------------*/

static lv_obj_t   * button_obj;
static lv_obj_t   * screen0_label0_obj;
static lv_obj_t *time_label;
static lv_obj_t *date_label;
static lv_obj_t *title_label;
static lv_obj_t *battery_label;
static lv_obj_t *date_label;




static lv_obj_t   * screen1_label0_obj; 
static lv_obj_t   * screen1_label1_obj; 

static lv_obj_t   * screen2_label0_obj; 
static lv_obj_t   * screen2_label1_obj; 
static lv_obj_t   * screen2_label2_obj; 

static screens_t screens [] = {
	{ .screen = NULL, .count = 1 },
	{ .screen = NULL, .count = 2 },
	{ .screen = NULL, .count = 3 },
	{ .screen = NULL, .count = 0 },
};
#define SCREENS_COUNT (sizeof(screens)/sizeof(screens[0]))

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void display_time_set_label(char *str)
{
	lv_label_set_text(time_label, str);
}
void display_date_set_label(char *str)
{
	lv_label_set_text(date_label, str);
}








void display_clock_update() // jj the clock apears in the first screen only 
{
	lv_scr_load(screens[0].screen);



}

/*---------------------------------------------------------------------------*/
/*        todo                                                               */
/*        kscan_touch works for pinetime                                     */
/*        have not found a way to do this out of tree                        */
/*        some minor modification of the focaltech driver is needed          */
/*---------------------------------------------------------------------------*/

#if defined(CONFIG_LVGL_POINTER_KSCAN) 


static void button_event_cb(lv_obj_t * obj, lv_event_t event)
{
	static int screen_id = 0;  // init to first screen id
	static int param_id  = 0;  // init to first parameter index

	switch(event) {
		case LV_EVENT_PRESSED:
			break; 
		case LV_EVENT_SHORT_CLICKED:
			LOG_INF("Short clicked\n");
			break;

		case LV_EVENT_CLICKED:
			clock_increment_local_time();

			LOG_INF("Clicked\n");
			break;

		case LV_EVENT_LONG_PRESSED:
			clock_increment_local_time();
			clock_show_time();
			LOG_INF("Long press\n");
			break;

		case LV_EVENT_LONG_PRESSED_REPEAT:

			//this can be configured in menuconfig 
			//standard value < long_pressed
			screen_id++;
			if (screen_id >= SCREEN_COUNT)
				screen_id = 0;
			lv_scr_load(screens[screen_id].screen);
			param_id = 0;
			LOG_INF("BTN1: screen_id(%d)", screen_id);
			//   handle_button_event();



			LOG_INF("Long press repeat\n");
			break;

		case LV_EVENT_RELEASED:
			LOG_INF("Released\n");
			break;
	}

}
#endif
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
//todo if no touch screen define real button ds_d6




void display_battery(enum battery_symbol s)
{
	switch (s) {
		case BAT_CHARGE:
			lv_label_set_text(battery_label, LV_SYMBOL_CHARGE);
			break;
		case BAT_FULL:
			lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_FULL);
			break;
		case BAT_3:
			lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_3);
			break;
		case BAT_2:
			lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_2);
			break;
		case BAT_1:
			lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_1);
			break;
		default:
			lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_EMPTY);
	}
}






void display_button()
{
	/* the ds_d6 has a real button and no touchscreen, so no need for lvgl-button */
#if defined(CONFIG_LVGL_POINTER_KSCAN)
	//#if defined(CONFIG_BOARD_NATIVE_POSIX_64BIT)
	button_obj = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_width(button_obj, 5);
	lv_obj_set_height(button_obj, 5);
	//lv_obj_align(button_obj, NULL, LV_ALIGN_CENTER, 128, 0);
	lv_obj_align(button_obj, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_btn_set_fit(button_obj, LV_FIT_TIGHT);
	screen0_label0_obj = lv_label_create(button_obj, NULL);
	lv_label_set_text(screen0_label0_obj, "O"); //substitute for real switch on physical watch
	lv_obj_set_event_cb(button_obj, button_event_cb);
#endif

}

void display_connect_event()
{
	lv_scr_load(screens[3].screen); //display the CTS screen

}

void display_disconnect_event()
{
	lv_scr_load(screens[0].screen); //display the first screen
}



void display_btn_event(buttons_id_t btn_id)
{
	static int screen_id = 0;  // init to first screen id
	static int param_id  = 0;  // init to first parameter index

	//LOG_INF("%s: BTN%d", __func__, btn_id);

	switch (btn_id) {

		case BTN1_LONG:
			screen_id++;
			if (screen_id >= SCREEN_COUNT)
				screen_id = 0;
			lv_scr_load(screens[screen_id].screen);
			param_id = 0;
			LOG_INF("BTN1: screen_id(%d)", screen_id);
			break;

		case BTN1_SHORT:
			param_id++;
			if (param_id >= screens[screen_id].count)  param_id = 0;
			if (param_id < 0)                          param_id = 0;
			LOG_INF("BTN2: screen_id(%d) param_id(%d)", screen_id, param_id);
			break;


		default:
			break;
	}
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void display_screens_init(void)
{
	screens[0].screen = lv_obj_create(NULL, NULL);
	screens[1].screen = lv_obj_create(NULL, NULL);
	screens[2].screen = lv_obj_create(NULL, NULL);
	screens[3].screen = lv_obj_create(NULL, NULL);

	// lv_theme_t * mono = lv_theme_mono_init(0, NULL);
	// lv_theme_set_current(mono);

	/*
	 *  build basic screen0
	 */
	lv_scr_load(screens[0].screen);
	lv_obj_t * screen0_label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen0_label, "Pg1");
	lv_obj_align(screen0_label, screens[0].screen, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
	/* the ds_d6 has a real button and no touchscreen, so no need for lvgl-button */
	display_button();

	/* Time label */
	time_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(time_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0); //jj
	lv_label_set_text(time_label, "00:00");
	/* Date label */
	date_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(date_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
	lv_label_set_text(date_label, "Mon 10 Jan");

	/* title label */
	title_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(title_label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	//lv_label_set_text(title_label, LV_SYMBOL_BLUETOOTH"symb");
	//lv_label_set_text(title_label, LV_SYMBOL_BLUETOOTH);
	lv_label_set_text(title_label, LV_SYMBOL_WIFI);

	/* Battery label */
	//display_battery(3);
	battery_label = lv_label_create(lv_scr_act(), NULL);
	display_battery(BAT_3); //todo just demo value -- need real level
	//lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_2);
	lv_obj_align(battery_label, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

	//battery_label = lv_label_create(lv_scr_act(), NULL);
	//lv_obj_align(battery_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
	//lv_label_set_text(battery_label, LV_SYMBOL_BATTERY_EMPTY);


	//	lv_obj_t * mask = lv_img_create(lv_scr_act(), NULL);
	//	lv_img_set_src(mask, &mask);
	//	lv_obj_align(mask, NULL, LV_ALIGN_CENTER, 0, 0);


	//  hello_world_label = lv_label_create(hello_world_button, NULL);
	// printf("pointer enabled\n");
	// lv_label_set_text(hello_world_label, "O"); //substitute for real switch on physical watch
	//screen0_slider_obj = lv_slider_create(lv_scr_act(), NULL);
	//lv_obj_set_height(screen0_slider_obj, 10);
	//lv_obj_set_width(screen0_slider_obj, 110);
	//lv_obj_align(screen0_slider_obj, NULL, LV_ALIGN_CENTER, 0, 0);
	//lv_slider_set_value(screen0_slider_obj, 15, LV_ANIM_ON);
	//screen0_slider_value = 15;

	/*
	 *  build basic screen1
	 */
	lv_scr_load(screens[1].screen);
	lv_obj_t * screen1_page = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen1_page, "Pg2");
	lv_obj_align(screen1_page, screens[1].screen, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

	// to avoid creating the same button all over again jj
	display_button();

	screen1_label0_obj = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen1_label0_obj, "0");
	lv_obj_align(screen1_label0_obj, screens[1].screen, LV_ALIGN_IN_BOTTOM_LEFT, 5, -5);

	screen1_label1_obj = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen1_label1_obj, "0");
	lv_obj_align(screen1_label1_obj, screens[1].screen, LV_ALIGN_IN_BOTTOM_RIGHT, -15, -5);

	//	lv_obj_t * icon_1 = lv_img_create(lv_scr_act(), NULL);
	//	lv_img_set_src(icon_1, &icon1);
	//	lv_obj_align(icon_1, NULL, LV_ALIGN_CENTER, 0, 0);

	/*
	 *  build basic screen2
	 */
	lv_scr_load(screens[2].screen);
	lv_obj_t * screen2_page = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen2_page, "Pg3");
	lv_obj_align(screen2_page, screens[2].screen, LV_ALIGN_IN_TOP_RIGHT, 0, 0);
	// why define the same button all over again? jj
	display_button();

	//
	lv_obj_t * screen2_label0_tag = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen2_label0_tag, "value-0");
	lv_obj_align(screen2_label0_tag, screens[2].screen, LV_ALIGN_IN_TOP_RIGHT, -70, 2);

	screen2_label0_obj = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen2_label0_obj, "0");
	lv_obj_align(screen2_label0_obj, screens[2].screen, LV_ALIGN_IN_TOP_RIGHT, -45, 2);

	//
	lv_obj_t * screen2_label1_tag = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen2_label1_tag, "value-1");
	lv_obj_align(screen2_label1_tag, screens[2].screen, LV_ALIGN_IN_RIGHT_MID, -70, 0);

	screen2_label1_obj = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen2_label1_obj, "0");
	lv_obj_align(screen2_label1_obj, screens[2].screen, LV_ALIGN_IN_RIGHT_MID, -45, 0);

	//
	lv_obj_t * screen2_value2_tag = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen2_value2_tag, "value-2");
	lv_obj_align(screen2_value2_tag, screens[2].screen, LV_ALIGN_IN_BOTTOM_RIGHT, -70, -2);

	screen2_label2_obj = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen2_label2_obj, "0");
	lv_obj_align(screen2_label2_obj, screens[2].screen, LV_ALIGN_IN_BOTTOM_RIGHT, -45, -2);

	//#if 0
	//	lv_obj_t * icon_2 = lv_img_create(lv_scr_act(), NULL);
	//	lv_img_set_src(icon_2, &icon2);
	//#endif

	/*
	 *  build basic screen3
	 */
	lv_scr_load(screens[3].screen);
	lv_obj_t * screen3_page = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(screen3_page, "Sc4");
	lv_obj_align(screen3_page, screens[3].screen, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

	// why define the same button all over again? jj
	display_button();

	//	lv_obj_t * icon_3 = lv_img_create(lv_scr_act(), NULL);
	//	lv_img_set_src(icon_3, &icon3);
	//	lv_obj_align(icon_3, NULL, LV_ALIGN_CENTER, 0, 0);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
#if (defined(CONFIG_BOARD_PINETIME_DEVKIT1) || defined(CONFIG_BOARD_PINETIME_DEVKIT0))


#define LED0_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0    DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN     DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS   DT_GPIO_FLAGS(LED0_NODE, gpios)
#endif
#endif

static void backlight_switch(bool enable)
{
#if (defined(CONFIG_BOARD_PINETIME_DEVKIT1) || defined(CONFIG_BOARD_PINETIME_DEVKIT0))
//#if defined(CONFIG_BOARD_PINETIME_DEVKIT1)

	const struct device *dev;

	dev = device_get_binding(LED0);
	/* If you have a backlight, set it up and turn it on here */
	gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	//   gpio_pin_configure(dev, LED, GPIO_DIR_OUT);
	if (enable==true) 
		gpio_pin_set(dev, PIN, 1);
	else
		gpio_pin_set(dev, PIN, 0);
	//gpio_pin_write(dev, LED, 0);
#endif
}




int display_init(void)
{
	//#if defined(CONFIG_BOARD_PINETIME_DEVKIT1)
	backlight_switch(true); //jj check which board has backlight is done in procedure
	//#endif
	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found. %s", CONFIG_LVGL_DISPLAY_DEV_NAME);
		return -1;
	}

	//lv_init();

	display_screens_init();

	/*
	 *  First screen will be screen1
	 */
	lv_scr_load(screens[0].screen);

	/*
	 *  Turn on display
	 */
	lv_task_handler();//jj
	display_blanking_off(display_dev);

	/* 
	 * Register for button press notifications.
	 */
	//buttons_register_notify_handler(display_btn_event);

	/*
	 *  Start task handler timer loop
	 */
	k_timer_start(&display_timer, K_MSEC(TICK_PERIOD), K_MSEC(TICK_PERIOD));

	return 0;
};

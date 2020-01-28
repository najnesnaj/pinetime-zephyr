/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/display.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>
#include <drivers/gpio.h>
#include <sys/byteorder.h>
#include <stdlib.h>
#include <sys/printk.h> //tod have to remove this later on, since makes no sense
#include <drivers/counter.h>

#define DELAY 1000000 //should be 1 second
#define ALARM_CHANNEL_ID 0



#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);

//#include "lv_ex_conf.h"

#define LED_PORT        DT_ALIAS_LED1_GPIOS_CONTROLLER
#define LED             DT_ALIAS_LED1_GPIOS_PIN
#define LV_IMG_DECLARE(var_name) extern const lv_img_dsc_t var_name;
LV_IMG_DECLARE(klokje);

int seconden; //todo cannot be global
int minuten;
int uren;

struct counter_alarm_cfg alarm_cfg;

static void test_counter_interrupt_fn(struct device *counter_dev,
		u8_t chan_id, u32_t ticks,
		void *user_data)
{
	int err;

	seconden++;
	if (seconden > 59) {
		seconden=0;
		minuten++;
		if (minuten > 59){
			minuten=0;
			uren++;
			if (uren > 23)
			{
				uren=0;
			}
		}

	}



	// after expiring the alarm is set again
	err = counter_set_channel_alarm(counter_dev, ALARM_CHANNEL_ID,
			user_data);

	if (err != 0) {
		printk("Alarm could not be set\n");
	}
}











static void backlight_init(void)
{
	struct device *dev;

	dev = device_get_binding(LED_PORT);
	/* If you have a backlight, set it up and turn it on here */
	gpio_pin_configure(dev, LED, GPIO_DIR_OUT);
	gpio_pin_write(dev, LED, 0);
}



void main(void)
{
	int err;
	struct device *counter_dev;
	counter_dev = device_get_binding(DT_RTC_0_NAME);
	counter_start(counter_dev);
	if (counter_dev == NULL) {
		printk("Device not found\n");
		return;
	}
	alarm_cfg.flags = 0;
	alarm_cfg.ticks = counter_us_to_ticks(counter_dev, DELAY);
	alarm_cfg.callback = test_counter_interrupt_fn;
	alarm_cfg.user_data = &alarm_cfg;

	err=counter_set_channel_alarm(counter_dev, ALARM_CHANNEL_ID, &alarm_cfg);


	//todo catch err


	//lv_obj_t *scr = lv_scr_act();
	lv_obj_t * img_bin = lv_img_create(lv_scr_act(), NULL);

	/*clock background*/
	lv_img_set_src(img_bin, &klokje);



	//int year;
	//int buff[10];
	char snum[3];
	u32_t count = 0U;
	char count_str[11] = {0};
	struct device *display_dev;
	lv_obj_t *hello_world_label;
	lv_obj_t *count_label; 
	lv_obj_t *clock_label; 
	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);


	/*Create a style*/
	//	static lv_style_t style1;

	//	lv_style_copy(&style1, &lv_style_plain);        /*Copy a built-in style*/
	//	style1.body.main_color = LV_COLOR_RED;          /*Main color*/


	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}
	else
		backlight_init();

	hello_world_label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_long_mode(hello_world_label, LV_LABEL_LONG_BREAK);     //Break the long lines
	lv_label_set_recolor(hello_world_label, true);                      //Enable re-coloring by commands in the text
	lv_obj_set_width(hello_world_label, 240);
	lv_label_set_text(hello_world_label, "#0000ff Hello world! Still Space Here"); //recoloring should be blue ...



	count_label = lv_label_create(lv_scr_act(), NULL);
	clock_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(count_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
	lv_obj_align(clock_label, NULL, LV_ALIGN_CENTER, 0, 0);

	display_blanking_off(display_dev);

	while (1) {

		sprintf(snum, "%2d:%2d:%2d", uren, minuten,seconden); //seconden gets updated by interrupt
		lv_label_set_text(clock_label, snum); 

		if ((count % 100) == 0U) {
			sprintf(count_str, "%d", count/100U);
			lv_label_set_text(count_label, count_str);
		}
		lv_task_handler();
		k_sleep(K_MSEC(10));
		++count;
	}
}

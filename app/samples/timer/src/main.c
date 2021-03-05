/*
 * Copyright (c) 2021  <najnesnaj@yahoo.com>
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
#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>

#define LED_TIMEOUT K_SECONDS(2)


LOG_MODULE_REGISTER(app);

static struct k_timer led_timer;

static lv_obj_t * led2;

int toggle_state=0;

void toggle_led(struct k_timer *led_off)
{
	if (toggle_state==0){
		lv_led_off(led2);
		printk("led off triggered\n");
		toggle_state=1;
	}
	else
	{ 
		lv_led_on(led2);
		printk("led on triggered\n");
		toggle_state=0;
	}
	k_timer_start(led_off, LED_TIMEOUT, K_NO_WAIT);
	lv_task_handler();
}





void display_led()
{
	led2  = lv_led_create(lv_scr_act(), NULL);
	lv_obj_align(led2, NULL,  LV_ALIGN_CENTER, 0, 0);
	lv_led_on(led2);
	lv_led_set_bright(led2, 255);
	lv_obj_set_width(led2, 10);
	lv_obj_set_height(led2, 10);

}


void main(void)
{
	const struct device *display_dev;
	k_timer_init(&led_timer, toggle_led, NULL);
	k_timer_start(&led_timer, LED_TIMEOUT, K_NO_WAIT);

	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}


	display_blanking_off(display_dev);
	display_led();
	while (1) {
		printf("while loop\n");
		k_sleep(K_MSEC(100));
		//	lv_task_handler();
	}
}

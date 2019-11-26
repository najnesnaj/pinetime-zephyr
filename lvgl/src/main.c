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

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);



#define LED_PORT        DT_ALIAS_LED1_GPIOS_CONTROLLER
#define LED             DT_ALIAS_LED1_GPIOS_PIN


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
	u32_t count = 0U;
	char count_str[11] = {0};
	struct device *display_dev;
	lv_obj_t *hello_world_label;
	lv_obj_t *count_label;
	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}
	else
backlight_init();

	hello_world_label = lv_label_create(lv_scr_act(), NULL);
lv_label_set_long_mode(hello_world_label, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
    lv_label_set_recolor(hello_world_label, true);                      /*Enable re-coloring by commands in the text*/
	lv_label_set_text(hello_world_label, "#0000ff Hello world!");

	lv_obj_align(hello_world_label, NULL, LV_ALIGN_CENTER, 0, 0);


 lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
    lv_obj_set_width(label2, 150);
    lv_label_set_text(label2, "It is a circularly scrolling text. ");
    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);


	count_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(count_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

	display_blanking_off(display_dev);

	while (1) {
		if ((count % 100) == 0U) {
			sprintf(count_str, "%d", count/100U);
			lv_label_set_text(count_label, count_str);
		}
		lv_task_handler();
		k_sleep(K_MSEC(10));
		++count;
	}
}

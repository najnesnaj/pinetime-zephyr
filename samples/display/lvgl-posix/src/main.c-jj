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

#define LED0_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0    DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN     DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS   DT_GPIO_FLAGS(LED0_NODE, gpios)
#endif

static void backlight_init(void)
{
	const struct device *dev;

	dev = device_get_binding(LED0);
	/* If you have a backlight, set it up and turn it on here */
	gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	//   gpio_pin_configure(dev, LED, GPIO_DIR_OUT);
	gpio_pin_set(dev, PIN, 1);
	//gpio_pin_write(dev, LED, 0);
}




void main(void)
{
	uint32_t count = 0U;
	char count_str[11] = {0};
	char count_str2[11] = {0};
	const struct device *display_dev;
	lv_obj_t *hello_world_label;
		lv_obj_t *hello_world_button;
	lv_obj_t *count_label;
	lv_obj_t *count_label2;
	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}
	else
		backlight_init();
	if (IS_ENABLED(CONFIG_LVGL_POINTER_KSCAN)) {

		hello_world_button = lv_btn_create(lv_scr_act(), NULL);
		lv_obj_align(hello_world_button, NULL, LV_ALIGN_CENTER, 0, 0);
		lv_btn_set_fit(hello_world_button, LV_FIT_TIGHT);
		hello_world_label = lv_label_create(hello_world_button, NULL);
	} else {
		hello_world_label = lv_label_create(lv_scr_act(), NULL);
	}

	lv_label_set_text(hello_world_label, "Button");
	lv_obj_align(hello_world_label, NULL, LV_ALIGN_CENTER, 0, 0);

	count_label2 = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(count_label2, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
	count_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(count_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

	lv_task_handler();
	display_blanking_off(display_dev);

	while (1) {
		if ((count % 100) == 0U) {
			sprintf(count_str, "%d", count/100U);
			lv_label_set_text(count_label, count_str);
		}
		if (lv_btn_get_state(hello_world_button) == LV_BTN_STATE_PRESSED) {
			sprintf(count_str2, "pressed ");
			lv_label_set_text(count_label2, count_str2);
		}
		if (lv_btn_get_state(hello_world_button) == LV_BTN_STATE_RELEASED) {
			sprintf(count_str2, "released ");
			lv_label_set_text(count_label2, count_str2);
		}
		lv_task_handler();
		k_sleep(K_MSEC(10));
		++count;
	}
}

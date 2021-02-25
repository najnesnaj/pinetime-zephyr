/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2021  <najnesnaj@yahoo.com>
 */

#include <device.h>
#include <drivers/display.h>
#include <lvgl.h>
//#include <lv_style.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>
#include <drivers/gpio.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>

#if defined(CONFIG_BOARD_PINETIME_DEVKIT1)


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

#endif



LOG_MODULE_REGISTER(app);





void main(void)
{
	uint32_t count = 0U;
	char count_str[11] = {0};
	const struct device *display_dev;
	lv_obj_t *hello_world_label;
//	lv_obj_t *count_label;
#if defined(CONFIG_BOARD_PINETIME_DEVKIT1)
 backlight_init();
#endif

	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}
	hello_world_label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(hello_world_label, "all around the world!");
	lv_obj_align(hello_world_label, NULL, LV_ALIGN_CENTER, 0, 0);

	//	count_label = lv_label_create(lv_scr_act(), NULL);
	//	lv_obj_align(count_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

	lv_task_handler();
	display_blanking_off(display_dev);

	while (1) {
		if ((count % 100) == 0U) {
			sprintf(count_str, "%d", count/100U);
			//lv_label_set_text(count_label, count_str);		
		}
		lv_task_handler();
		k_sleep(K_MSEC(1000));
		++count;
	}
}

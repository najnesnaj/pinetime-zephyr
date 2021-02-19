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
LOG_MODULE_REGISTER(app);
static lv_obj_t   * screen0_label0_obj;
static lv_obj_t   * button_obj;


static lv_obj_t * led2;
//static lv_style_t  styleled;
//lv_style_copy(&styleled, &lv_style_scr);
//lv_style_init(&style_led);
//lv_style_set_bg_color(&style_led, LV_STATE_DEFAULT, LV_COLOR_WHITE);
//lv_obj_set_style(led2, &style_led);


static void button_event_cb(lv_obj_t * obj, lv_event_t event)
{
	switch(event) {
		case LV_EVENT_PRESSED:
			LOG_INF("Pressed\n");
			lv_led_on(led2);
			break;
		case LV_EVENT_SHORT_CLICKED:
			LOG_INF("Short clicked\n");
			break;

		case LV_EVENT_CLICKED:
			LOG_INF("Clicked\n");
			break;

		case LV_EVENT_LONG_PRESSED:
			LOG_INF("Long press\n");
			break;

		case LV_EVENT_LONG_PRESSED_REPEAT:
			LOG_INF("Long press repeat\n");
			lv_led_off(led2);
			break;

		case LV_EVENT_RELEASED:
			LOG_INF("Released\n");
			break;

	}
}


void display_button()
{
	led2  = lv_led_create(lv_scr_act(), NULL);
	//lv_led_set_style(led2, LV_LED_STYLE_MAIN, &style_led);
	lv_obj_align(led2, NULL,  LV_ALIGN_IN_TOP_RIGHT, 0, 0);
	lv_led_on(led2);
	lv_led_set_bright(led2, 255);
	//#if defined(CONFIG_LVGL_POINTER_KSCAN)
	button_obj = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_width(led2, 10);
	lv_obj_set_height(led2, 10);
	//lv_obj_set_width(button_obj, 25);
	//lv_obj_set_height(button_obj, 25);
	lv_obj_align(button_obj, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_btn_set_fit(button_obj, LV_FIT_TIGHT);
	screen0_label0_obj = lv_label_create(button_obj, NULL);
		lv_label_set_text(screen0_label0_obj, "Button"); 
	lv_obj_set_event_cb(button_obj, button_event_cb);
	//#endif

}
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



void main(void)
{
	const struct device *display_dev;

	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}

#if defined(CONFIG_BOARD_PINETIME_DEVKIT1)


 backlight_init();

#endif


	display_blanking_off(display_dev);
	display_button();
	while (1) {

		printf("loop\n");
		lv_task_handler();
		k_sleep(K_MSEC(100));
	}
}

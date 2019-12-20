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
#include <drivers/sensor.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);



#define LED_PORT        DT_ALIAS_LED1_GPIOS_CONTROLLER
#define LED             DT_ALIAS_LED1_GPIOS_PIN
#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F000)

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


	struct sensor_value accel[3];

	struct device *dev = device_get_binding(DT_INST_0_BOSCH_BMA280_LABEL);

	if (dev == NULL) {
		MY_REGISTER1=0x33;
		printf("Could not get %s device\n", DT_INST_0_BOSCH_BMA280_LABEL);
		return;
	}

	struct sensor_trigger trig = {
		.type = SENSOR_TRIG_DATA_READY,
		.chan = SENSOR_CHAN_ACCEL_XYZ,
	};



	if (sensor_sample_fetch(dev)) {
		MY_REGISTER1=0xEE;
		printf("sensor_sample_fetch failed\n");
	}
	else
		MY_REGISTER1=0xAA;

	sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, accel);


	u32_t count = 0U;
	char count_str[11] = {0};
	char accel_str[11] = {0};
	struct device *display_dev;
	lv_obj_t *hello_world_label;
	lv_obj_t *count_label;
	lv_obj_t *accel_label;
	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);
	//lv_btn_set_style(obj, LV_BTN_STYLE_REL, &lv_style_plain_color); /*set other style for background*/
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
	accel_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(accel_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

	display_blanking_off(display_dev);

	while (1) {
		if ((count % 100) == 0U) {
			sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, accel);
			sprintf(accel_str, "%d", accel[0]);
			lv_label_set_text(count_label, accel_str);
			sprintf(count_str, "%d", count/100U);
			lv_label_set_text(count_label, count_str);
		}
		lv_task_handler();
		k_sleep(K_MSEC(10));
		++count;
	}
}

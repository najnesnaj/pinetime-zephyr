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
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F001)

static void backlight_init(void)
{
	struct device *dev;

	dev = device_get_binding(LED_PORT);
	/* If you have a backlight, set it up and turn it on here */
	gpio_pin_configure(dev, LED, GPIO_DIR_OUT);
	gpio_pin_write(dev, LED, 0);
}
K_SEM_DEFINE(sem, 0, 1);

static void trigger_handler(struct device *dev, struct sensor_trigger *trig)
{
	switch (trig->type) {
		case SENSOR_TRIG_DATA_READY:
			if (sensor_sample_fetch(dev) < 0) {
				printf("Sample fetch error\n");
				return;
			}
			k_sem_give(&sem);
			break;
		case SENSOR_TRIG_THRESHOLD:
			printf("Threshold trigger\n");
			break;
		default:
			printf("Unknown trigger\n");
	}
}


void main(void)
{


	struct sensor_value accel[4];

	struct sensor_value tempera;
	//	struct sensor_value  hulp;
	//	tempera=&hulp;

	struct device *dev = device_get_binding(DT_INST_0_BOSCH_BMA421_LABEL);
	MY_REGISTER1=0x00;

	if (dev == NULL) {
		MY_REGISTER1=0x77;
		printf("Could not get %s device\n", DT_INST_0_BOSCH_BMA421_LABEL);
		return;
	}

	struct sensor_trigger trig = {
		.type = SENSOR_TRIG_DATA_READY,
		.chan = SENSOR_CHAN_ACCEL_XYZ,
	};
	lv_obj_t *hello_world_label;


	hello_world_label = lv_label_create(lv_scr_act(), NULL);

	if (sensor_sample_fetch(dev)) {
		lv_label_set_text(hello_world_label, "FAILED BMA");
		printf("sensor_sample_fetch failed\n");
	}
	else
		lv_label_set_text(hello_world_label, "BMA OK");
	//MY_REGISTER1=0xAA;

	sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, accel);


	u32_t count = 0U;
	char count_str[11] = {0};
	char accel_str[11] = {0};
	char accel_str2[11] = {0};
	char accel_str3[11] = {0};
	char temp_str[11] = {0};
	char step_str[11] = {0};
	struct device *display_dev;
	lv_obj_t *count_label;
	lv_obj_t *accel_label;
	lv_obj_t *accel_label2;
	lv_obj_t *accel_label3;
	lv_obj_t *temp_label;
	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);
	//lv_btn_set_style(obj, LV_BTN_STYLE_REL, &lv_style_plain_color); /*set other style for background*/
	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		MY_REGISTER1=0xEE;
		return;
	}
	else
		backlight_init();


	//	lv_label_set_long_mode(hello_world_label, LV_LABEL_LONG_BREAK);     /*Break the long lines*/
	//	lv_label_set_recolor(hello_world_label, true);                      /*Enable re-coloring by commands in the text*/
	//	lv_label_set_text(hello_world_label, "Hello world!");
	//lv_label_set_text(hello_world_label, "#0000ff Hello world!");

	lv_obj_align(hello_world_label, NULL, LV_ALIGN_CENTER, 0, 0);


	lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
	//	lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC);     /*Circular scroll*/
	//	lv_obj_set_width(label2, 150);
	//	lv_label_set_text(label2, "It is a circularly scrolling text. ");
	lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);


	count_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(count_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
	accel_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(accel_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
	accel_label2 = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(accel_label2, NULL, LV_ALIGN_IN_TOP_MID, 0, 25);
	accel_label3 = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(accel_label3, NULL, LV_ALIGN_IN_TOP_MID, 0, 50);
	temp_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(temp_label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 75);

	display_blanking_off(display_dev);

	while (1) {
		if ((count % 100) == 0U) {
			sensor_sample_fetch(dev);
			sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, accel);
			//MY_REGISTER2=temp;
			//	if (sensor_value_to_double(&accel[0]) != 0) MY_REGISTER1=0x99;
			sprintf(accel_str, "X: %.1f", sensor_value_to_double(&accel[0]));
			lv_label_set_text(accel_label, accel_str);

			sprintf(accel_str2, "Y: %.1f", sensor_value_to_double(&accel[1]));
			lv_label_set_text(accel_label2, accel_str2);

			sprintf(accel_str3, "Z: %.1f", sensor_value_to_double(&accel[2]));
			lv_label_set_text(accel_label3, accel_str3);
			sensor_sample_fetch(dev);
			sensor_channel_get(dev, SENSOR_CHAN_DIE_TEMP, &tempera);
			//sprintf(temp_str, "Temp : %.1f", sensor_value_to_double(&tempera)); //temperature
			sprintf(temp_str, "Temp : %d", (int)accel[3].val1); //temperature
			lv_label_set_text(temp_label, temp_str);
			MY_REGISTER1=count/100U;	
			sprintf(count_str, "%d", count/100U);
			lv_label_set_text(count_label, count_str);
		}
		lv_task_handler();
		k_sleep(K_MSEC(10));
		++count;
	}
}

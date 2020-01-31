/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This program display X and Y values of the touchscreen.


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
	ARG_UNUSED(trig);
	//	switch (trig->type) {
	//		case SENSOR_TRIG_DATA_READY:
	//					if (sensor_sample_fetch(dev) < 0) {
	//						printf("Sample fetch error\n");
	//						return;
	//					}
	k_sem_give(&sem);
	//			break;
	//		default:
	//			printf("Unknown trigger\n");
	//}
}


void main(void)
{


	struct sensor_value touch[1];


	struct device *devtouch = device_get_binding(DT_INST_0_HYNITRON_CST816S_LABEL);
	if (devtouch == NULL) {
		printf("Could not get %s device\n", DT_INST_0_HYNITRON_CST816S_LABEL);
		return;
	}
	struct sensor_trigger trig = {
		.type = SENSOR_TRIG_DATA_READY,
		.chan = SENSOR_CHAN_ACCEL_XYZ,
	};
	if (IS_ENABLED(CONFIG_CST816S_TRIGGER)) {

		if (sensor_trigger_set(devtouch, &trig, trigger_handler)){
			printf("Trigger set error\n");
		}

	}
	lv_obj_t *hello_world_label;


	hello_world_label = lv_label_create(lv_scr_act(), NULL);

	u32_t count = 0U;
	char count_str[11] = {0};
	char touch_strx[11] = {0};
	char touch_stry[11] = {0};

	struct device *display_dev;
	lv_obj_t *count_label;
	lv_obj_t *touch_labelx;
	lv_obj_t *touch_labely;
	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}
	else
		backlight_init();

	lv_obj_align(hello_world_label, NULL, LV_ALIGN_CENTER, 0, 0);



	count_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(count_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);

	touch_labelx = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(touch_labelx, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

	touch_labely = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(touch_labely, NULL, LV_ALIGN_IN_TOP_MID, 0, 25);


	display_blanking_off(display_dev);

	while (1) {
		count++;
		if (count > 200) count=0;
		sprintf(count_str, "%d", count);
		lv_label_set_text(count_label, count_str);  //this is just a counter that keeps track on number of executions
		lv_task_handler();
		if (IS_ENABLED(CONFIG_CST816S_TRIGGER)){
			k_sem_take(&sem, K_FOREVER); //bad idea to wait eternally on interrupt....
			sensor_sample_fetch(devtouch); 
			sensor_channel_get(devtouch, SENSOR_CHAN_ACCEL_XYZ, touch);
		}
		else
		{
			sensor_sample_fetch(devtouch); 
			sensor_channel_get(devtouch, SENSOR_CHAN_ACCEL_XYZ, touch);
			//	sensor_sample_fetch(dev);  //this is useless if there's no interrupt
		}
		//sprintf(touch_strx, "X: %.1f", sensor_value_to_double(&touch[0]));
		sprintf(touch_strx, "X: %d", touch[0].val2);
		lv_label_set_text(touch_labelx, touch_strx);

		sprintf(touch_stry, "Y: %d", touch[0].val1);
		lv_label_set_text(touch_labely, touch_stry);



		k_sleep(K_MSEC(100));

	}
}

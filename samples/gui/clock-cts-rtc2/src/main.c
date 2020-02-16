/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 *
 * demonstrates setting the time and displays (hopefully) an exact time
 *
 *
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


#define LED_PORT        DT_ALIAS_LED1_GPIOS_CONTROLLER
#define LED             DT_ALIAS_LED1_GPIOS_PIN
#define LV_IMG_DECLARE(var_name) extern const lv_img_dsc_t var_name;


#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <settings/settings.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#include "cts_sync.h"
static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
			0x0d, 0x18, 0x0f, 0x18, 0x05, 0x18),
	BT_DATA_BYTES(BT_DATA_UUID128_ALL,
			0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
			0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12),
};


static void bt_ready(void)
{
	int err;

	printk("Bluetooth initialized\n");

	if (IS_ENABLED(CONFIG_SETTINGS)) {
		settings_load();
	}
	printk("bt_le_adv_start\n");
	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}







struct counter_alarm_cfg alarm_cfg;
cts_datetime_t pinetime_datetime;

void init_clock(cts_datetime_t* datetime)
{
	pinetime_datetime.hours=datetime->hours;
	pinetime_datetime.minutes=datetime->minutes;
	pinetime_datetime.seconds=datetime->seconds;
	pinetime_datetime.day=datetime->day;
	pinetime_datetime.month=datetime->month;
	pinetime_datetime.year=datetime->year;

}




static void test_counter_interrupt_fn(struct device *counter_dev,
		u8_t chan_id, u32_t ticks,
		void *user_data)
{
	int err;
	//todo replace this with proper internal time system, that keeps track of date
	pinetime_datetime.seconds++;
	if (pinetime_datetime.seconds > 59) {
		pinetime_datetime.seconds=0;
		pinetime_datetime.minutes++;
		if (pinetime_datetime.minutes > 59){
			pinetime_datetime.minutes=0;
			pinetime_datetime.hours++;
			if (pinetime_datetime.hours > 23)
			{
				pinetime_datetime.hours=0;
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





	counter_dev = device_get_binding(DT_RTC_2_NAME);
	counter_start(counter_dev);
	if (counter_dev == NULL) {
		printk("Counter device not found\n");
		return;
	}
	alarm_cfg.flags = 0;
	alarm_cfg.ticks = counter_us_to_ticks(counter_dev, DELAY);
	alarm_cfg.callback = test_counter_interrupt_fn;
	alarm_cfg.user_data = &alarm_cfg;

	err=counter_set_channel_alarm(counter_dev, ALARM_CHANNEL_ID, &alarm_cfg);
	if (err) {
	}
	err = bt_enable(NULL);

	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}
	bt_ready();
	cts_sync_init();
	cts_get_datetime(&pinetime_datetime); //this already should get dummy value to show on screen

	cts_datetime_t localtime;
	init_clock(&localtime);
	//todo catch err




	char snum[3];
	u32_t count = 0U;
	char count_str[11] = {0};
	struct device *display_dev;
	lv_obj_t *hello_world_label;
	lv_obj_t *count_label; 
	lv_obj_t *clock_label; 
	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);




	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}
	else
		backlight_init();

	lv_obj_t *scr = lv_scr_act();



	hello_world_label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_long_mode(hello_world_label, LV_LABEL_LONG_BREAK);     //Break the long lines
	lv_label_set_recolor(hello_world_label, true);                      //Enable re-coloring by commands in the text
	lv_obj_set_width(hello_world_label, 240);
	lv_label_set_text(hello_world_label, "#00ffff Open Source Watch"); //recoloring should be blue ...



	count_label = lv_label_create(lv_scr_act(), NULL);
	clock_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(count_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
	lv_obj_align(clock_label, NULL, LV_ALIGN_CENTER, 0, 0);

	display_blanking_off(display_dev);

	while (1) {

		sprintf(snum, "%2d:%2d:%2d", pinetime_datetime.hours, pinetime_datetime.minutes,pinetime_datetime.seconds); 
		lv_label_set_text(clock_label, "#00ffff"); 
		lv_label_set_text(clock_label, snum); 

		if ((count % 100) == 0U) {
			sprintf(count_str, "%d", count/100U);
			lv_label_set_text(count_label, count_str);
		}
		lv_task_handler();
		k_sleep(K_MSEC(10));
		++count;
		cts_sync_loop();  //todo this should be activated by button or something - not looped
		cts_get_datetime(&pinetime_datetime);
	}
}

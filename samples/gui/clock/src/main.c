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
#include <misc/byteorder.h>
#include <stdlib.h>
#include <sys/printk.h> //have to remove this later on, since makes no sense
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
//LV_IMG_DECLARE(gezicht);
int seconden;
int minuten;
int uren;

struct counter_alarm_cfg alarm_cfg;

static void test_counter_interrupt_fn(struct device *counter_dev,
		u8_t chan_id, u32_t ticks,
		void *user_data)
{
	u32_t now_ticks = counter_read(counter_dev);
	u64_t now_usec = counter_ticks_to_us(counter_dev, now_ticks);
	int now_sec = (int)(now_usec / USEC_PER_SEC);
	struct counter_alarm_cfg *config = user_data;
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




	//	err = counter_set_channel_alarm(counter_dev, ALARM_CHANNEL_ID,
	//			user_data);


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
	//	void *images[] = {(void *) &WALLPAPER_1_IMG, (void *) &bg1};
	//	static lv_style_t style;
	//	lv_style_copy(&style, &lv_style_scr);
	//	lv_obj_set_style(main_cont, &style);


	//lv_obj_t * btn = lv_btn_create(lv_scr_act(), NULL);     /*Add a button the current screen*/
	//lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
	//lv_obj_set_size(btn, 100, 50);                          /*Set its size*/
	//lv_obj_set_event_cb(btn, btn_event_cb);                 /*Assign a callback to the button*/

	//lv_obj_t * label = lv_label_create(btn, NULL);          /*Add a label to the button*/
	//lv_label_set_text(label, "Button");                     /*Set the labels text*/
	int err;
	struct device *counter_dev;
	counter_dev = device_get_binding(DT_RTC_0_NAME);
	counter_start(counter_dev);

	alarm_cfg.flags = 0;
	alarm_cfg.ticks = counter_us_to_ticks(counter_dev, DELAY);
	alarm_cfg.callback = test_counter_interrupt_fn;
	alarm_cfg.user_data = &alarm_cfg;

	err=counter_set_channel_alarm(counter_dev, ALARM_CHANNEL_ID, &alarm_cfg);





	lv_obj_t *scr = lv_scr_act();
	lv_obj_t * img_bin = lv_img_create(lv_scr_act(), NULL);

	/*klokje achtergrond*/
		lv_img_set_src(img_bin, &klokje);
	//
//	lv_img_set_src(img_bin, &gezicht);



	int year;
	int buff[10];
	char snum[3];
	u32_t count = 0U;
	char count_str[11] = {0};
	struct device *display_dev;
	lv_obj_t *hello_world_label;
	lv_obj_t *count_label; 
	lv_obj_t *clock_label; 
	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);


	/*Create a style*/
	static lv_style_t style1;

	lv_style_copy(&style1, &lv_style_plain);        /*Copy a built-in style*/
	style1.body.main_color = LV_COLOR_RED;          /*Main color*/



	/*
	   lv_style_copy(&style1, &lv_style_plain);    //Copy a built-in style to initialize the new style
	   style1.body.main_color = LV_COLOR_BLACK;
	   style1.body.grad_color = LV_COLOR_BLUE;
	   style1.body.radius = 10;
	   style1.body.border.color = LV_COLOR_GRAY;
	   style1.body.border.width = 2;
	   style1.body.border.opa = LV_OPA_50;
	   style1.body.padding.left = 5;            //Horizontal padding, used by the bar indicator below
	   style1.body.padding.right = 5;
	   style1.body.padding.top = 5;            //Vertical padding, used by the bar indicator below
	   style1.body.padding.bottom = 5;
	   style1.text.color = LV_COLOR_GREEN;

*/


	//lv_btn_set_style(obj, LV_BTN_STYLE_REL, &lv_style_plain_color); /*set other style for background*/
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

	lv_obj_align(hello_world_label, NULL, LV_ALIGN_CENTER, 0, 0);

	/*
	   lv_obj_t * label2 = lv_label_create(lv_scr_act(), NULL);
	   lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC);     //circular scroll
	   lv_obj_set_width(label2, 150);
	   lv_label_set_text(label2, "It is a circularly scrolling text. ");
	   lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);

*/
	count_label = lv_label_create(lv_scr_act(), NULL);
	clock_label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(count_label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
	lv_obj_align(clock_label, NULL, LV_ALIGN_CENTER, 0, 0);

	display_blanking_off(display_dev);

	//demo_create(void);
	//
	//
	//LV_IMG_DECLARE(img_bubble_pattern)

	//lv_img_set_src(img, img_bubble_pattern);
	/*   lv_obj_t * scr = lv_disp_get_scr_act(NULL);  
	     lv_obj_t * wp = lv_img_create(scr, NULL);
	     lv_img_set_src(wp, &img_bubble_pattern);
	     lv_obj_set_pos(src, 10, 1);
	     lv_obj_set_drag(src, true);
	     */
	while (1) {

		sprintf(snum, "%2d:%2d:%2d", uren, minuten,seconden); //seconden gets updated by interrupt

		if ((count % 100) == 0U) {
			sprintf(count_str, "%d", count/100U);
			lv_label_set_text(count_label, count_str);
		}
		lv_task_handler();
		k_sleep(K_MSEC(10));
		lv_label_set_text(clock_label, snum); 
		++count;
	}
}

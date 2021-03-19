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

#define PARAM_TOTAL 6 //total number of parameters


char * string_array[] = {
	"temp1",
	"timer1",
	"temp2",
	"timer2",
	"temp3",
	"timer3"
};

int param[6]={10,20,30,40,50,60};


static lv_obj_t   * screen0_label0_obj;
static lv_obj_t   * button_obj;
static lv_obj_t   * screen0_label1_obj;
static lv_obj_t   * screen0_label2_obj;
//static lv_obj_t   * screen0_label0_obj;

//static short screen0_label1_value = 0;
#define BUTTON_THRESH 6 //threshold to distinguish between short and long press

//when used in a real watch it will probable have to be less
#define BUTTON_DOUBLE_THRESH 12 //double click


void display_label()
{
	screen0_label1_obj=lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(screen0_label1_obj, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);
	screen0_label2_obj=lv_label_create(lv_scr_act(), NULL);
	lv_obj_align(screen0_label2_obj, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, 0, 0);
	//lv_label_set_text(screen0_label1_obj, string_array[3]); //clears
	//lv_label_set_text(screen0_label1_obj, string_array[parnr]);
}


void show_label(int parnr)
{
	char snum[5];
	sprintf(snum, "%d",param[parnr]);
	lv_label_set_text(screen0_label1_obj, string_array[parnr]);
	lv_label_set_text(screen0_label2_obj, snum);
}



static uint8_t button_press_cnt;
static uint8_t label_select_cnt;

//when the timer expires the number of presses is analysed
void button_timer_handler(struct k_timer *dummy)
{
	printf("timer expired\n"); 
	printf("press count %d\n", button_press_cnt);
	if (button_press_cnt >= BUTTON_DOUBLE_THRESH){
		printf("long press\n");
//		show_label(0);
	}
	if (button_press_cnt <= BUTTON_THRESH){ //short press is used to scroll trough the labels with their value
		printf("short press\n");
		show_label(label_select_cnt);
		label_select_cnt++;
		if (label_select_cnt ==  PARAM_TOTAL) label_select_cnt=0;
	}
	if ((button_press_cnt > BUTTON_THRESH) && (button_press_cnt < BUTTON_DOUBLE_THRESH)){
		printf("double click\n");
//		show_label(2);
	}
	button_press_cnt=0;


}


/*timer used to detect lenght of pushing*/
struct k_timer button_timer;



K_TIMER_DEFINE(button_timer, button_timer_handler,NULL);


//during 1 second the number of buttonpresses is counted
static void button_event_cb(lv_obj_t * obj, lv_event_t event)
{

	LOG_INF("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
	if (button_press_cnt == 0U) {
		k_timer_start(&button_timer, K_SECONDS(1), K_NO_WAIT);
		printf("Buttontime started" );
	}

	if (k_timer_status_get(&button_timer) > 0) {
		button_press_cnt=0;
	} else  {
		/* timer still running */
		button_press_cnt++;
	}

}


void display_button()
{
	button_obj = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_align(button_obj, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
	lv_btn_set_fit(button_obj, LV_FIT_TIGHT);
	screen0_label0_obj = lv_label_create(button_obj, NULL);
	lv_label_set_text(screen0_label0_obj, "Button"); 
	lv_obj_set_event_cb(button_obj, button_event_cb);
}







void main(void)
{
	const struct device *display_dev;
        label_select_cnt=0;

	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("device not found.  Aborting test.");
		return;
	}

	display_blanking_off(display_dev);
	display_button();
	display_label();
	show_label(label_select_cnt); 
	while (1) {

		lv_task_handler();
		k_sleep(K_MSEC(100));
	}
}

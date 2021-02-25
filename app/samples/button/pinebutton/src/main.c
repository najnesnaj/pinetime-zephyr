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



#define SW0_NODE        DT_ALIAS(sw0)

#if DT_NODE_HAS_STATUS(SW0_NODE, okay)
#define SW0_GPIO_LABEL  DT_GPIO_LABEL(SW0_NODE, gpios)
#define SW0_GPIO_PIN    DT_GPIO_PIN(SW0_NODE, gpios)
#define SW0_GPIO_FLAGS  (GPIO_INPUT | DT_GPIO_FLAGS(SW0_NODE, gpios))
#else
#error "Unsupported board: sw0 devicetree alias is not defined"
#define SW0_GPIO_LABEL  ""
#define SW0_GPIO_PIN    0
#define SW0_GPIO_FLAGS  0
#endif

#if defined(CONFIG_BOARD_PINETIME_DEVKIT1) //pinetime needs port 15 high for switch to work
#define SW1_NODE        DT_ALIAS(sw1)
#define SW1_GPIO_PIN    DT_GPIO_PIN(SW1_NODE, gpios)
#define SW1_GPIO_FLAGS  (GPIO_OUTPUT | DT_GPIO_FLAGS(SW1_NODE, gpios))
#endif



static uint8_t button_press_cnt;
struct k_timer button_timer;
void button_pressed(const struct device *dev, struct gpio_callback *cb,
		uint32_t pins)
{
	//buttons_id_t btn_id;

	LOG_INF("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
	printf("button pressed\n");
	if (button_press_cnt == 0U) {
		k_timer_start(&button_timer, K_SECONDS(1), K_NO_WAIT);
		LOG_INF("Button short");
		//	btn_id=BTN1_SHORT;
	}

	if (k_timer_status_get(&button_timer) > 0) {
		/* timer has expired */
		LOG_INF("SHORT PRESS EVENT %02x\n", button_press_cnt);
		if (button_press_cnt > 2){
			LOG_INF("Button long");
			//			display_btn_event(BTN1_LONG);
		}
		//		else
		//			display_btn_event(BTN1_SHORT);
		button_press_cnt=0;
	} else  {
		/* timer still running */
		button_press_cnt++;
		if (button_press_cnt > 2){
			LOG_INF("LONG PRESS EVENT %02x\n", button_press_cnt);
			//      display_btn_event(BTN1_LONG);
		}
	}



	//	printk("button_press_cnt 0x%02x\n", button_press_cnt);
	//	button_press_cnt++;



	// 	LOG_INF("Button time %d\n", button_time);
	//      sensor_attr_set(dev, SENSOR_CHAN_LIGHT, SENSOR_ATTR_SAMPLING_FREQUENCY,0x22);
	//	button_time_previous = k_cycle_get32();
}


static struct gpio_callback button_cb_data;

void init_button(void)
{
	const struct device *button;
	int ret;
	button = device_get_binding(SW0_GPIO_LABEL);
	if (button == NULL) {
		printk("Error: didn't find %s device\n", SW0_GPIO_LABEL);
		return;
	}

	ret = gpio_pin_configure(button, SW0_GPIO_PIN, SW0_GPIO_FLAGS);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
				ret, SW0_GPIO_LABEL, SW0_GPIO_PIN);
		return;
	}

	ret = gpio_pin_interrupt_configure(button,
			SW0_GPIO_PIN,
			GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
				ret, SW0_GPIO_LABEL, SW0_GPIO_PIN);
		return;
	}
	//port 15 has to be high in order for the button to work


	gpio_pin_configure(button, SW1_GPIO_PIN,SW1_GPIO_FLAGS); //push button out
	gpio_pin_set(button, SW1_GPIO_PIN, 1); //set port high






	gpio_init_callback(&button_cb_data, button_pressed, BIT(SW0_GPIO_PIN));
	gpio_add_callback(button, &button_cb_data);
	printk("Set up button at %s pin %d\n", SW0_GPIO_LABEL, SW0_GPIO_PIN);



}




void display_button()
{
	led2  = lv_led_create(lv_scr_act(), NULL);
	lv_obj_align(led2, NULL,  LV_ALIGN_IN_TOP_RIGHT, 0, 0);
	lv_led_on(led2);
	lv_led_set_bright(led2, 255);
	button_obj = lv_btn_create(lv_scr_act(), NULL);
	lv_obj_set_width(led2, 10);
	lv_obj_set_height(led2, 10);
	lv_obj_align(button_obj, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_btn_set_fit(button_obj, LV_FIT_TIGHT);
	screen0_label0_obj = lv_label_create(button_obj, NULL);
	lv_label_set_text(screen0_label0_obj, "Push Button"); 

}


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
	const struct device *display_dev;

	display_dev = device_get_binding(CONFIG_LVGL_DISPLAY_DEV_NAME);

	if (display_dev == NULL) {
		LOG_ERR("display device not found.  Aborting test.");
		return;
	}

	//pinetime has a backlight

	backlight_init();



	display_blanking_off(display_dev);
	display_button();
	init_button();
	while (1) {

		//		printf("loop\n");
		lv_task_handler();
		k_sleep(K_MSEC(100));
	}
}

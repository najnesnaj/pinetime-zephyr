/*

 * Copyright (c) 2021 <najnesnaj@yahoo.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
//#include <zephyr/zephyr.h>
#include <zephyr/kernel.h>
#include "display.h"
#include "log.h"
#include "bt.h"
#include "clock.h"
#include "event_handler.h"
int main(void)
{
        printf ("Yo\n");
	init_button();
	LOG_INF ("button init\n");
        display_init();
	LOG_INF ("display init\n");
	clock_init();
	LOG_INF ("clock init\n");
	event_handler_init();
	LOG_INF ("event_handler init\n");
//	bt_init();
//      	LOG_INF("start bt\n");
	clock_init();
	while (1) {
//		printf ("hello\n");
		lv_task_handler();
		k_sleep(K_MSEC(100));
	}
	return 0;
}

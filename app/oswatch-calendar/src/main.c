/*

 * Copyright (c) 2021 <najnesnaj@yahoo.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/display.h>
#include <drivers/gpio.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>
#include "clock.h"
#include "log.h"
#include "display.h"
#include "event_handler.h"
#include "bt.h"

void main(void)
{
#if !(defined(CONFIG_BOARD_NATIVE_POSIX_64BIT)) //both the pinetime & ds_d6 have a real button 
	{
		init_button();
	}
#endif
	display_init();
	clock_init();
	event_handler_init();
        bt_init();
	while (1) {
		lv_task_handler();
		k_sleep(K_MSEC(100));
	}
}

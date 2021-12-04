/*

 * Copyright (c) 2021 <najnesnaj@yahoo.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <device.h>
#include <drivers/display.h>
#include <drivers/gpio.h>
//#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>
#include "clock.h"
#include "log.h"
//#include "display.h"
#include "event_handler.h"
#include "bt.h"
//#include "param_sync.h"


#include <drivers/sensor.h>
void main(void)
{
	LOG_INF(" Hello there!\n");
//	display_init();
	clock_init();
	event_handler_init();
	//bt_init(); //cts time update
	//param_sync_init();
	static unsigned int count;
	struct sensor_value accel[3];
	const char *overrun = "";
float hoek;
	const struct device *sensor = DEVICE_DT_GET_ANY(adi_adxl345new);

	if (sensor == NULL) {
		LOG_INF("No device found\n");
		return;
	}
	if (!device_is_ready(sensor)) {
		LOG_INF("Device %s is not ready\n", sensor->name);
		return;
	}

	LOG_INF("yippi! device ready !\n");
	while (1) { 

		int rc = sensor_sample_fetch(sensor);
		//LOG_INF(" value sensor rc %d\n", rc);
		//     ++count;
		if (rc == 0) {
			rc = sensor_channel_get(sensor,
					SENSOR_CHAN_ACCEL_XYZ,
					accel);
		}
		if (rc < 0) {
			LOG_INF("ERROR: Update failed: %d\n", rc);
		} else {
			hoek=1; //to avoid unintialised
			if (accel[2].val1 != 0) 
				hoek=accel[1].val1/accel[2].val1;
			else LOG_INF("problem exception accel2\n");
			/*                LOG_INF("#%u @ %u ms: %sx %f , y %f , z %f\n",
					  count, k_uptime_get_32(), overrun,
					  sensor_value_to_double(&accel[0]),
					  sensor_value_to_double(&accel[1]),
					  sensor_value_to_double(&accel[2]));*/
//			LOG_INF(" value 1 %d\n", accel[0].val1);
			LOG_INF(" value 2 %d\n", accel[1].val1);
			LOG_INF(" value 3 %d\n", accel[2].val1);
			//LOG_INF(" value 2 %d\n", accel[0].val2);
			printf("hoek   %lf     \n", (hoek));
		}

		k_sleep(K_MSEC(2000));


	}
}

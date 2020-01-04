/*
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/sensor.h>
#include <stdio.h>
#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F000)
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F001)
void main(void)
{
	struct sensor_value green;
	struct device *dev = device_get_binding(DT_INST_0_HX_HRS3300_LABEL);
MY_REGISTER1=0x00;
MY_REGISTER2=0x00;
	if (dev == NULL) {
MY_REGISTER1=0xee;
		printf("Could not get hrs3300 device\n");
		return;
	}

	while (1) {
		sensor_sample_fetch(dev);
		sensor_channel_get(dev, SENSOR_CHAN_GREEN, &green);

		/* Print green LED data*/
		printf("GREEN=%d\n", green.val1);
if (green.val1 > 0) MY_REGISTER2=0xaa; 
/*
 *green.val2 exists as well
 these two values are raw readings and have to be processed by an algorithm in order to get a heart rate
 * */
		k_sleep(K_MSEC(20));
	}
}

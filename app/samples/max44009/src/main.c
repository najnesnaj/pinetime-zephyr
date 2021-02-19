/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2021 <najnesnaj@yahoo.com>
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <drivers/sensor.h>

#include <device.h>

/**
 * @file Sample app using the MAX44009 light sensor through ARC I2C.
 *
 * This app will read the sensor reading via I2C interface and show
 * the result every 4 seconds.
 */



/* The devicetree node identifier for the "led0" alias. */
/*#define LED0_NODE DT_ALIAS(led0)

//#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0    DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN     DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS   DT_GPIO_FLAGS(LED0_NODE, gpios)
*/
//#else
/* A build error here means your board isn't set up to blink an LED. */
/*#error "Unsupported board: led0 devicetree alias is not defined"
#define LED0    ""
#define PIN     0
#define FLAGS   0
#endif
*/





void main(void)
{
	const struct device *dev;
	printk("MAX44009 light sensor application\n");


	struct sensor_value val;
	uint32_t lum = 0U;
	dev = device_get_binding("MAX44009");
	if (!dev) {
		printk("sensor: device not found.\n");
		return;
	}

	while (1) {
		if (sensor_sample_fetch_chan(dev, SENSOR_CHAN_LIGHT) != 0) {
			printk("sensor: sample fetch fail.\n");
			return;
		}

		if (sensor_channel_get(dev, SENSOR_CHAN_LIGHT, &val) != 0) {
			printk("sensor: channel get fail.\n");
			return;
		}

		lum = val.val1;
		printk("sensor: lum reading: %d\n", lum);

		k_sleep(K_MSEC(10));
	}
}

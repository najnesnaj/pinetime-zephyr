/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>

#define LED_PORT	DT_ALIAS_LED2_GPIOS_CONTROLLER
#define LED0		DT_ALIAS_LED0_GPIOS_PIN
#define LED1		DT_ALIAS_LED1_GPIOS_PIN
#define LED2		DT_ALIAS_LED2_GPIOS_PIN

/* 1000 msec = 1 sec */
#define SLEEP_TIME	1000

void main(void)
{
//	u32_t cnt = 0;
	struct device *dev;

	dev = device_get_binding(LED_PORT);
	/* Set LED pin as output */
//	gpio_pin_configure(dev, LED0, GPIO_DIR_OUT);
//	gpio_pin_configure(dev, LED1, GPIO_DIR_OUT);
	gpio_pin_configure(dev, LED2, GPIO_DIR_OUT);
//		gpio_pin_write(dev, LED0, 0);
//		gpio_pin_write(dev, LED1, 0);
		gpio_pin_write(dev, LED2, 0);

	while (1) {
		/* Set pin to HIGH/LOW every 1 second */
		//gpio_pin_write(dev, LED, cnt % 2);
//		gpio_pin_write(dev, LED0, 0);
//		gpio_pin_write(dev, LED1, 0);
//		gpio_pin_write(dev, LED2, 0);
//		cnt++;
//		k_sleep(SLEEP_TIME);
//		gpio_pin_write(dev, LED0, 1);
//		gpio_pin_write(dev, LED1, 1);
//		gpio_pin_write(dev, LED2, 1);
	}
}

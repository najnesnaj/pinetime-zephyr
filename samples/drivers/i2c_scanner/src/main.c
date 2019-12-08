/*
 * Copyright (c) 2018 Tavish Naruka <tavishnaruka@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <zephyr.h>
#include <sys/printk.h>
#include <device.h>
#include <drivers/i2c.h>

#ifdef ARDUINO_I2C_LABEL
#define I2C_DEV ARDUINO_I2C_LABEL
#else
#define I2C_DEV "I2C_1"
#endif
//debugging
#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F000)
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F001)
#define MY_REGISTER3 (*(volatile uint8_t*)0x2000F002)

/**
 * @file This app scans I2C bus for any devices present
 */

void main(void)
{
	struct device *i2c_dev;
int teller=0;
	printk("Starting i2c scanner...\n");
MY_REGISTER1=0xFF;
	i2c_dev = device_get_binding(I2C_DEV);
	if (!i2c_dev) {
		printk("I2C: Device driver not found.\n");
		return;
MY_REGISTER1=0xFE;
	}

	for (u8_t i = 4; i <= 0x77; i++) {
//	for (u8_t i = 18; i <= 0x77; i++) {
		struct i2c_msg msgs[1];
		u8_t dst;

		/* Send the address to read from */
		msgs[0].buf = &dst;
		msgs[0].len = 0U;
		msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

		if (i2c_transfer(i2c_dev, &msgs[0], 1, i) == 0) {
			printk("0x%2x FOUND\n", i);
			teller++;
			switch (teller) {
			case 1: MY_REGISTER1=i; break;
			case 2: MY_REGISTER2=i; break;
			case 3: MY_REGISTER3=i; break;
			}	
		}
	}
//MY_REGISTER=0xFF; //it showed this value so it was executed till the end
}

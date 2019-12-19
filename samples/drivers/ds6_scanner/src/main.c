/*
 * Copyright (c) 2018 Tavish Naruka <tavishnaruka@gmail.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <errno.h>
#include <zephyr.h>
#include <misc/printk.h>
#include <device.h>
#include <i2c.h>
//#include <drivers/gpio.h>
#include <gpio.h>
#define LED_PORT LED0_GPIO_CONTROLLER
#define LED     LED0_GPIO_PIN

#define I2C_DEV0  "I2C_1"
#define I2C_DEV1  "I2C_1"
//#define I2C_DEV "I2C_GPIO_1"
//#define PORT    DT_ALIAS_SW0_GPIOS_CONTROLLER
#define MY_REGISTER0 (*(volatile uint8_t*)0x2000F000)
#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F005)
/**
 * @file This app scans I2C bus for any devices present
 */

void main(void)
{
	struct device *i2c_dev;
	//	struct device *gpiob;
	u8_t cnt = 0;
	struct device *dev;

	dev = device_get_binding(LED_PORT);

	gpio_pin_configure(dev, LED, GPIO_DIR_OUT);


	gpio_pin_write(dev, LED, 1);


	//gpio_pin_configure(gpiob, 26,GPIO_DIR_OUT); //push button out
	//gpio_pin_write(gpiob, 26, &button_out); //set port high




	//	gpiob = device_get_binding(PORT);
	/*	if (!gpiob) {
		printk("error\n");
		MY_REGISTER1=0xEE; //error
		return;
		}
		*/
	/*	gpio_pin_configure(gpiob, 7,GPIO_DIR_OUT); //push button out
		gpio_pin_write(gpiob, 7, 0); //set port high
		gpio_pin_configure(gpiob, 6,GPIO_DIR_OUT); //push button out
		gpio_pin_write(gpiob, 6, 0); //set port high
		*/




	MY_REGISTER0=0x33;
	printk("Starting i2c scanner on i2c_0 ...\n");

	i2c_dev = device_get_binding(I2C_DEV0);
	if (!i2c_dev) {
		MY_REGISTER0=0x44;
		printk("I2C: Device driver %s not found.\n", I2C_DEV0);
		return;
	}
	printk("I2C: Device binding %s OK.\n", I2C_DEV0);

	for (u8_t i = 12; i <= 0x77; i++) {
		struct i2c_msg msgs[1];
		u8_t dst;
			MY_REGISTER0=i;

		msgs[0].buf = &dst;
		msgs[0].len = 0U;
		msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP;
		//		msgs[0].flags = I2C_MSG_WRITE ;
		printk("i2c_transfer hangs\n");

		if (i2c_transfer(i2c_dev, &msgs[0], 1, i) == 0) {
			MY_REGISTER0=0x99;
			printk("0x%2x FOUND\n", i);
			++cnt;
		}
	}
	printk("%u devices found on %s\n", cnt, I2C_DEV0);
	MY_REGISTER0=cnt;
	//MY_REGISTER1=0x33;



	MY_REGISTER1=0x55;
	printk("Starting i2c scanner on i2c_1 ...\n");

	i2c_dev = device_get_binding(I2C_DEV1);
	if (!i2c_dev) {
		MY_REGISTER1=0x44;
		printk("I2C: Device driver %s not found.\n", I2C_DEV1);
		return;
	}

	for (u8_t i = 12; i <= 0x77; i++) {
		struct i2c_msg msgs[1];
		u8_t dst;

		/* Send the address to read from */
		msgs[0].buf = &dst;
		msgs[0].len = 0U;
		msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP;
		//		msgs[0].flags = I2C_MSG_WRITE ;

		if (i2c_transfer(i2c_dev, &msgs[0], 1, i) == 0) {
			MY_REGISTER1=i;
			printk("0x%2x FOUND\n", i);
			++cnt;
		}
	}
	printk("%u devices found on %s\n", cnt, I2C_DEV1);
	MY_REGISTER1=cnt;

}

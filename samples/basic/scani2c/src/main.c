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
#include <drivers/gpio.h>
#ifdef ARDUINO_I2C_LABEL
#define I2C_DEV ARDUINO_I2C_LABEL
#else
#define I2C_DEV "I2C_1"
#endif
//debugging
#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F000)
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F001)
#define MY_REGISTER3 (*(volatile uint8_t*)0x2000F002)
#define MY_REGISTER4 (*(volatile uint8_t*)0x2000F003)
#define MY_REGISTER5 (*(volatile uint8_t*)0x2000F004)
#define MY_REGISTER6 (*(volatile uint8_t*)0x2000F005)
#define MY_REGISTER7 (*(volatile uint8_t*)0x2000F006)
#define MY_REGISTER8 (*(volatile uint8_t*)0x2000F007)

/**
 * @file This app scans I2C bus for any devices present
 * and puts their address in the REGISTERS 1-3
 *
 * the interrupt of the touch screen shows only when touched
 */

void main(void)
{
	//reset touchscreen
	//	 gpio_pin_configure(drv_data->gpio, 10,GPIO_DIR_OUT); //
	//	             gpio_pin_write(drv_data->gpio, 10, 0); //set port low
	//		             gpio_pin_write(drv_data->gpio, 10, 1); //set port high
	struct device *i2c_dev;
	int teller=0;
	printk("Starting i2c scanner...\n");
	MY_REGISTER1=0xFF; //debug
	MY_REGISTER2=0xFF;
	MY_REGISTER3=0xFF;
	MY_REGISTER5=0xFF;
	MY_REGISTER6=0xFF;
	MY_REGISTER7=0xFF;
	MY_REGISTER8=0xFF;
	i2c_dev = device_get_binding(I2C_DEV);
	if (!i2c_dev) {
		printk("I2C: Device driver not found.\n");
		return;
		//MY_REGISTER1=0xFE;
	}
	while (1){
		struct i2c_msg msgs[2];
		u8_t dst=0;
		u8_t rxt;
		u8_t buffer[64];
		//buf[0]=0x00;
		/* Send the address to read from */
		msgs[0].buf = &dst;
		msgs[0].len = 1U;
		msgs[0].flags = I2C_MSG_WRITE | I2C_MSG_STOP | I2C_MSG_RESTART;
		teller++;
		if (teller > 200) teller=0;
		if (i2c_transfer(i2c_dev, &msgs[0], 1, 0x15) == 0) {
			/* burst read 63 values from the touchscreen */
			MY_REGISTER2=teller;
			/*
			 *
			 *
			 msg[1].buf = (u8_t *)read_buf;
			 msg[1].len = num_read;
			 msg[1].flags = I2C_MSG_RESTART | I2C_MSG_READ | I2C_MSG_STOP;

			 *
			 *
			 *
			 */

			//msgs[1].buf = &rxt;
			msgs[1].buf = &buffer[0];
			msgs[1].len = 63U;
			msgs[1].flags = I2C_MSG_READ | I2C_MSG_STOP;
			//msgs[1].flags = I2C_MSG_READ;
			/* if (i2c_burst_read(i2c_dev, 0x15, 0, buf, 63) < 0) {
			   MY_REGISTER1=0xaa;

			   }*/
			buffer[0]=0;
			buffer[3]=0;
			buffer[4]=0;
			buffer[5]=0;
			buffer[6]=0;
			if (i2c_transfer(i2c_dev, &msgs[1], 1, 0x15) == 0) {
				MY_REGISTER1=teller;
				//buffer= &rxt;
				//MY_REGISTER5=msgs[3].buf & 0x0f;
				MY_REGISTER5=buffer[3] ;
				MY_REGISTER6=buffer[4];
				//MY_REGISTER7=msgs[5].buf & 0x0f;
				MY_REGISTER7=buffer[5] ;
				MY_REGISTER8=buffer[6];
			}
			else
				MY_REGISTER1=0xee;

		}
	}
}

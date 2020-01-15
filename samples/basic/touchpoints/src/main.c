/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 * get touchpoint out of touchscreen 
 *
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/util.h>
#include <sys/printk.h>
#include <inttypes.h>
#include <drivers/i2c.h>
/* change this to use another GPIO port */
#ifndef DT_ALIAS_SW0_GPIOS_CONTROLLER
#ifdef SW0_GPIO_NAME
#define DT_ALIAS_SW0_GPIOS_CONTROLLER SW0_GPIO_NAME
#else
#error SW0_GPIO_NAME or DT_ALIAS_SW0_GPIOS_CONTROLLER needs to be set in board.h
#endif
#endif
#define PORT	DT_ALIAS_SW0_GPIOS_CONTROLLER

/* change this to use another GPIO pin */
#ifdef DT_ALIAS_SW0_GPIOS_PIN
#define PIN     DT_ALIAS_SW0_GPIOS_PIN
#else
#error DT_ALIAS_SW0_GPIOS_PIN needs to be set in board.h
#endif

/* change to use another GPIO pin interrupt config */
#ifdef DT_ALIAS_SW0_GPIOS_FLAGS
#define EDGE    (DT_ALIAS_SW0_GPIOS_FLAGS | GPIO_INT_EDGE)
#else
/*
 * If DT_ALIAS_SW0_GPIOS_FLAGS not defined used default EDGE value.
 * Change this to use a different interrupt trigger
 */
#define EDGE    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#endif

/* change this to enable pull-up/pull-down */
#ifndef DT_ALIAS_SW0_GPIOS_FLAGS
#ifdef DT_ALIAS_SW0_GPIOS_PIN_PUD
#define DT_ALIAS_SW0_GPIOS_FLAGS DT_ALIAS_SW0_GPIOS_PIN_PUD
#else
#define DT_ALIAS_SW0_GPIOS_FLAGS 0
#endif
#endif
//#define PULL_UP DT_ALIAS_SW0_GPIOS_FLAGS

#define PULL_UP  (1<<8)
/* Sleep time */
#define SLEEP_TIME	500
#define I2C_DEV "I2C_1"
#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F000) //debugging
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F001)
#define MY_REGISTER3 (*(volatile uint8_t*)0x2000F002)
#define MY_REGISTER4 (*(volatile uint8_t*)0x2000F003)
#define MY_REGISTER5 (*(volatile uint8_t*)0x2000F004)
#define MY_REGISTER6 (*(volatile uint8_t*)0x2000F005)
#define MY_REGISTER7 (*(volatile uint8_t*)0x2000F006)
#define MY_REGISTER8 (*(volatile uint8_t*)0x2000F007)

void touched(struct device *gpiob, struct gpio_callback *cb,
		u32_t pins)
{
	 u8_t id = 0U;
	u8_t buf[64];
	struct device *i2c_dev;
	i2c_dev = device_get_binding(I2C_DEV);
	if (i2c_dev == NULL){ MY_REGISTER1=0xEE;
		return;
	}
	//	read register 0x00 from the touchscreen i2c 0x15
		k_sleep(SLEEP_TIME);

//if (i2c_reg_read_byte(i2c_dev, 0x15, 0x01, &buf[0]) < 0){
//if (i2c_reg_read_byte(i2c_dev, 0x15, 0x01, &buf[0]) < 0){
//		MY_REGISTER3=0xEE; //read a single byte

//}
//write 1 to register 0x00
id=1;
if (i2c_reg_write_byte(i2c_dev, 0x15, 0x00, id) < 0){MY_REGISTER1=0xEE;}

buf[0]=0x00;
buf[1]=0x00;
	if (i2c_burst_read(i2c_dev, 0x15, 1, buf, 63) < 0) {
	//if (i2c_write_read(i2c_dev, 0x15, buf, 1, buf, 63) < 0) {
		//LOG_DBG("Could not read data");
		MY_REGISTER3=0xEE;
		return ;
	}
	//	k_sleep(SLEEP_TIME);
//if (i2c_read(i2c_dev, buf, 63, 0x15) < 0){MY_REGISTER3=0xEE;}
//		k_sleep(SLEEP_TIME);

// bytes 3 to 8 are repeated 10 times
// byte 3 (MSB bit 3..0)
// byte 4 (LSB)
// only first is relevant
// 
//         msb = buf[3] & 0x0f;
//                 lsb = buf[4];
//                 MY_REGISTER1=lsb;
//                         drv_data->x_sample = (msb<<8)|lsb;
//
//                                 msb = buf[5] & 0x0f;
//                                         lsb = buf[6];
//                                                 drv_data->y_sample = (msb<<8)|lsb; // todo check if buf[5] is indeed Y
//
MY_REGISTER5=buf[3] & 0x0f;
MY_REGISTER6=buf[4];
MY_REGISTER7=buf[5] & 0x0f;
MY_REGISTER8=buf[6];
}

static struct gpio_callback gpio_cb;

void main(void)
{
	MY_REGISTER4=0x00; 
	MY_REGISTER3=0x00; 
	MY_REGISTER2=0x00;
	MY_REGISTER1=0x00; 
	struct device *gpiob;

	printk("Press the user defined button on the board\n");
	gpiob = device_get_binding(PORT);
	if (!gpiob) {
		printk("error\n");
		MY_REGISTER2=0xEE; //error
		return;
	}


	//gpio_pin_configure(gpiob, 28, GPIO_DIR_IN | PULL_UP);
	//MY_REGISTER1= GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | GPIO_INT_ACTIVE_HIGH;
	gpio_pin_configure(gpiob, 28, GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | GPIO_INT_ACTIVE_HIGH);
	//gpio_pin_configure(gpiob, 28, GPIO_DIR_IN );
	//	gpio_pin_configure(gpiob, 13,GPIO_DIR_IN);
	//	MY_REGISTER2=BIT(PIN); //check PIN  setting

	gpio_init_callback(&gpio_cb, touched, BIT(28));

	gpio_add_callback(gpiob, &gpio_cb);
	gpio_pin_enable_callback(gpiob, 28);




	while (1) {
		k_sleep(SLEEP_TIME);
	}
}

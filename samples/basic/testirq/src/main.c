/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 *
 * test the IRQ of the touchscreen
 *
 */

#include <zephyr.h>
#include <device.h>
#include <drivers/gpio.h>
#include <sys/util.h>
#include <sys/printk.h>
#include <inttypes.h>

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

#define PULL_UP  (1<<8)
/* Sleep time */
#define SLEEP_TIME	500

#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F000)
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F001)
#define MY_REGISTER3 (*(volatile uint8_t*)0x2000F002)
int teller;

/*each time the touchscreen is touched , the interrupt triggers this function and the counter is increased*/
void touched(struct device *gpiob, struct gpio_callback *cb,
		u32_t pins)
{
	teller++;
	if (teller > 200) teller=0;
	MY_REGISTER2=teller;

	printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());
}

static struct gpio_callback gpio_cb;

void main(void)
{
	MY_REGISTER2=0x00; //debugging
	MY_REGISTER1=0x00;
	MY_REGISTER3=0x00; 
	struct device *gpiob;

	printk("Press the user defined button on the board\n");
	gpiob = device_get_binding(PORT);
	if (!gpiob) {
		printk("error\n");
		MY_REGISTER3=0xEE; //error
		return;
	}
	/*this is a procedure for resetting the touchscreen*/

	gpio_pin_configure(gpiob, 10, GPIO_DIR_OUT );

	//	gpio_pin_write(gpiob, 10, 1); //set port high
	//		k_sleep(SLEEP_TIME);
	//	gpio_pin_write(gpiob, 10, 0); //set port high
	//		k_sleep(SLEEP_TIME);


	gpio_pin_configure(gpiob, 28, GPIO_DIR_IN | GPIO_INT |  PULL_UP | EDGE | GPIO_INT_ACTIVE_HIGH);

	gpio_init_callback(&gpio_cb, touched, BIT(28));

	gpio_add_callback(gpiob, &gpio_cb);
	gpio_pin_enable_callback(gpiob, 28);




	while (1) {
		k_sleep(SLEEP_TIME);
	}
}

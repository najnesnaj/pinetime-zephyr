/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/sensor.h>
#include <stdio.h>
#include <drivers/gpio.h>

#define LED_PORT        DT_ALIAS_LED1_GPIOS_CONTROLLER
#define LED             DT_ALIAS_LED1_GPIOS_PIN

int tellerke=0;
K_SEM_DEFINE(sem, 0, 1);

#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F000)
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F001)


static void backlight_init(void)
{
	struct device *dev;

	dev = device_get_binding(LED_PORT);
	/* If you have a backlight, set it up and turn it on here */
	gpio_pin_configure(dev, LED, GPIO_DIR_OUT);
	gpio_pin_write(dev, LED, 0);
}



static void trigger_handler(struct device *dev, struct sensor_trigger *trigger)
{
	ARG_UNUSED(trigger);
	tellerke++;
	if (tellerke > 200) tellerke=0;
	MY_REGISTER1=tellerke;
	//	if (sensor_sample_fetch(dev)) { //todo
	//		printf("sensor_sample_fetch failed\n");
	//		return;
	//	}

	k_sem_give(&sem);
}
int counter=0;




void main(void)
{
	backlight_init(); // test if interrupt still works with backlight
	MY_REGISTER1=0x93;
	MY_REGISTER2=0x93;
	struct sensor_value accel[3];
	struct device *dev = device_get_binding(DT_INST_0_HYNITRON_CST816S_LABEL);
	if (dev == NULL) {
		printf("Could not get %s device\n", DT_INST_0_HYNITRON_CST816S_LABEL);
		MY_REGISTER1=0xe6;
		return;
	}

	struct sensor_trigger trig = {
		.type = SENSOR_TRIG_DATA_READY,
		.chan = SENSOR_CHAN_ACCEL_XYZ, 
	};


	if (IS_ENABLED(CONFIG_CST816S_TRIGGER)) {
		if (sensor_trigger_set(dev, &trig, trigger_handler)) {
			printf("Could not set trigger\n");
			MY_REGISTER1=0xe7;
			return;
		}
	}

	while (1) {
		counter++;
		if (counter>200) counter=0;
		if (IS_ENABLED(CONFIG_CST816S_TRIGGER)) {
			//	k_sem_take(&sem, K_MSEC(50)); //you cannot wait FOREVER on interrupt
			k_sem_take(&sem, K_FOREVER); //you cannot wait FOREVER on interrupt
			MY_REGISTER2=counter;
			//	if (sensor_sample_fetch(dev)) {
			//		printf("sensor_sample_fetch failed\n");
			//		MY_REGISTER1=0xe5;
			//	}
		} else {
			MY_REGISTER1=0x25;
		}
		//	MY_REGISTER1=counter;

		//		sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, accel);

		//	printf("AX=%10.2f AY=%10.2f \n",
		//				sensor_value_to_double(&accel[0]),
		//				sensor_value_to_double(&accel[1]));
	}

	//	if (!IS_ENABLED(CONFIG_CST816S_TRIGGER)) {
	//		k_sleep(K_MSEC(2000));
	//	}
}

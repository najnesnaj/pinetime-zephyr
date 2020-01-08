/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <drivers/sensor.h>
#include <stdio.h>


//K_SEM_DEFINE(sem, 0, 1);

#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F000)

static void trigger_handler(struct device *dev, struct sensor_trigger *trigger)
{
	ARG_UNUSED(trigger);
MY_REGISTER1=0x11;
	if (sensor_sample_fetch(dev)) {
		printf("sensor_sample_fetch failed\n");
		return;
	}

//	k_sem_give(&sem);
}

void main(void)
{
	MY_REGISTER1=0xee;
//	struct k_sem my_sem; 
	struct sensor_value accel[3];
	struct device *dev = device_get_binding(DT_INST_0_HYNITRON_CST816S_LABEL);
struct cst816s_data *drv_data = dev->driver_data;
//my_sem=drv_data->gpio_sem;
	if (dev == NULL) {
		printf("Could not get %s device\n", DT_INST_0_HYNITRON_CST816S_LABEL);
		return;
	}

	struct sensor_trigger trig = {
		.type = SENSOR_TRIG_DATA_READY,
		.chan = SENSOR_CHAN_ACCEL_XYZ,
	};


	if (IS_ENABLED(CONFIG_CST816S_TRIGGER)) {
		if (sensor_trigger_set(dev, &trig, trigger_handler)) {
			printf("Could not set trigger\n");
			return;
		}
	}

	while (1) {
//		if (IS_ENABLED(CONFIG_CST816S_TRIGGER)) {
//			k_sem_take(&my_sem, K_MSEC(50)); //you cannot wait FOREVER on interrupt
//		} else {
//			MY_REGISTER1=0x15;
			if (sensor_sample_fetch(dev)) {
				printf("sensor_sample_fetch failed\n");
			}
//		}

		sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ, accel);

		printf("AX=%10.2f AY=%10.2f \n",
				sensor_value_to_double(&accel[0]),
				sensor_value_to_double(&accel[1]));
	}

	if (!IS_ENABLED(CONFIG_CST816S_TRIGGER)) {
		k_sleep(K_MSEC(2000));
	}
}

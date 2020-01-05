/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_CST816S_CST816S_H_
#define ZEPHYR_DRIVERS_SENSOR_CST816S_CST816S_H_

#include <device.h>
#include <sys/util.h>
#include <zephyr/types.h>
#include <drivers/gpio.h>

#define CST816S_I2C_ADDRESS		CONFIG_CST816S_I2C_ADDR

#define CST816S_REG_DATA 0x00

struct cst816s_data {
	struct device *i2c;
	s16_t x_sample;
	s16_t y_sample;

#ifdef CONFIG_CST816S_TRIGGER
	struct device *gpio;
	struct gpio_callback gpio_cb;

	struct sensor_trigger data_ready_trigger;
	sensor_trigger_handler_t data_ready_handler;


#if defined(CONFIG_CST816S_TRIGGER_OWN_THREAD)
	K_THREAD_STACK_MEMBER(thread_stack, CONFIG_CST816S_THREAD_STACK_SIZE);
	struct k_thread thread;
	struct k_sem gpio_sem;
#elif defined(CONFIG_CST816S_TRIGGER_GLOBAL_THREAD)
	struct k_work work;
	struct device *dev;
#endif

#endif /* CONFIG_CST816S_TRIGGER */
};

#ifdef CONFIG_CST816S_TRIGGER
int cst816s_trigger_set(struct device *dev,
		       const struct sensor_trigger *trig,
		       sensor_trigger_handler_t handler);

int cst816s_attr_set(struct device *dev,
		    enum sensor_channel chan,
		    enum sensor_attribute attr,
		    const struct sensor_value *val);

int cst816s_init_interrupt(struct device *dev);
#endif

#endif /* ZEPHYR_DRIVERS_SENSOR_CST816S_CST816S_H_ */

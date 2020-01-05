/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <drivers/i2c.h>
#include <init.h>
#include <drivers/sensor.h>
#include <sys/__assert.h>
#include <logging/log.h>

#include "cst816s.h"
#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F005)
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F006)
#define MY_REGISTER3 (*(volatile uint8_t*)0x2000F007)
#define MY_REGISTER4 (*(volatile uint8_t*)0x2000F008)
#define MY_REGISTER5 (*(volatile uint8_t*)0x2000F009)
#define MY_REGISTER6 (*(volatile uint8_t*)0x2000F00A)



LOG_MODULE_REGISTER(CST816S, CONFIG_SENSOR_LOG_LEVEL);

static int cst816s_sample_fetch(struct device *dev, enum sensor_channel chan)
{
	struct cst816s_data *drv_data = dev->driver_data;
	u8_t buf[64];
	u8_t lsb;
	u8_t id = 0U;
	__ASSERT_NO_MSG(chan == SENSOR_CHAN_ALL);

	/*
	 * since all accel data register addresses are consecutive,
	 * a burst read can be used to read all the samples
	 */
//	MY_REGISTER6=0x00;
/*	if (i2c_burst_read(drv_data->i2c, CST816S_I2C_ADDRESS,
				CST816S_REG_DATA, buf, 64) < 0) {
		LOG_DBG("Could not read data");
//		MY_REGISTER6=0xEE;
		return -EIO;
	}
*/
	drv_data->x_sample = 100; //todo assign value

	drv_data->y_sample = 100;


	return 0;
}

static void cst816s_channel_convert(struct sensor_value *val,
		s64_t raw_val)
{
	/*
	raw_val = (raw_val * BMA280_PMU_FULL_RANGE) /
		(1 << (8 + BMA280_ACCEL_LSB_BITS));
	val->val1 = raw_val / 1000000;
	val->val2 = raw_val % 1000000;

	if (val->val2 < 0) {
		val->val1 -= 1;
		val->val2 += 1000000;
	}
	 */
}

static int cst816s_channel_get(struct device *dev,
		enum sensor_channel chan,
		struct sensor_value *val)
{
	struct cst816s_data *drv_data = dev->driver_data;

	/*
	 */
	if (chan == SENSOR_CHAN_ACCEL_XYZ) {
	//	cst816s_channel_convert(val, drv_data->x_sample);
	//	cst816s_channel_convert(val + 1, drv_data->y_sample);
	} else {
		return -ENOTSUP;
	}

	return 0;
}

static const struct sensor_driver_api cst816s_driver_api = {
#if CONFIG_CST816S_TRIGGER
	.attr_set = cst816s_attr_set,
	.trigger_set = cst816s_trigger_set,
#endif
	.sample_fetch = cst816s_sample_fetch,
	.channel_get = cst816s_channel_get,
};


static void i2c_delay(unsigned int cycles_to_wait)
{
	u32_t start = k_cycle_get_32();

	/* Wait until the given number of cycles have passed */
	while (k_cycle_get_32() - start < cycles_to_wait) {
	}
}



int cst816s_init(struct device *dev)
{
/*	struct cst816s_data *drv_data = dev->driver_data;
	u8_t id = 0U;
	drv_data->i2c = device_get_binding(CONFIG_CST816S_I2C_MASTER_DEV_NAME);
	if (drv_data->i2c == NULL) {
		LOG_DBG("Could not get pointer to %s device",
				CONFIG_CST816S_I2C_MASTER_DEV_NAME);
		return -EINVAL;
	}*/

	/* read device ID */
//i2c_reg_read_byte(drv_data->i2c, BMA421_I2C_ADDRESS,0x40, &id); 

#ifdef CONFIG_BMA280_TRIGGER
if (cst816s_init_interrupt(dev) < 0) {
	LOG_DBG("Could not initialize interrupts");
	return -EIO;
}
#endif

return 0;
}

struct cst816s_data cst816s_driver;

DEVICE_AND_API_INIT(cst816s, CONFIG_CST816S_NAME, cst816s_init, &cst816s_driver,
		NULL, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,
		&cst816s_driver_api);

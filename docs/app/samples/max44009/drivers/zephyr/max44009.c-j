/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
*/

#define DT_DRV_COMPAT maxim_max44009

#include <device.h>
#include <drivers/i2c.h>
#include <drivers/sensor.h>
#include <sys/__assert.h>
#include <logging/log.h>
//#include <drivers/gpio.h>
#include "max44009.h"

LOG_MODULE_REGISTER(MAX44009, CONFIG_SENSOR_LOG_LEVEL);

static int max44009_reg_read(struct max44009_data *drv_data, uint8_t reg,

			     uint8_t *val, bool send_stop)
{
/*	struct i2c_msg msgs[2] = {
		{
			.buf = &reg,
			.len = 1,
			.flags = I2C_MSG_WRITE,
		},
		{
			.buf = val,
			.len = 1,
			.flags = I2C_MSG_READ,
		},
	};

	if (send_stop) {
		msgs[1].flags |= I2C_MSG_STOP;
	}*/
if (i2c_reg_read_byte(drv_data->i2c, MAX44009_I2C_ADDRESS, reg, val) < 0) {
                LOG_ERR("Failed to read ......");
                return -EIO;
        }


// max44009_reg_write(drv_data, 127, 1);
//	if (i2c_transfer(drv_data->i2c, msgs, 2, MAX44009_I2C_ADDRESS) != 0) {
// LOG_DBG("i2c_transfer  %d val",val);
//		return -EIO;
//	}

	return 0;
}

static int max44009_reg_write(struct max44009_data *drv_data, uint8_t reg,
			      uint8_t val)
{
	uint8_t tx_buf[2] = {reg, val};

	return i2c_write(drv_data->i2c, tx_buf, sizeof(tx_buf), MAX44009_I2C_ADDRESS);
 //LOG_DBG("writing to  %s address!",MAX44009_I2C_ADDRESS);

//	return i2c_write(drv_data->i2c, tx_buf, sizeof(tx_buf),0x6b);
}

static int max44009_reg_update(struct max44009_data *drv_data, uint8_t reg,
			       uint8_t mask, uint8_t val)
{
	uint8_t old_val = 0U;
	uint8_t new_val = 0U;

	if (max44009_reg_read(drv_data, reg, &old_val, true) != 0) {
		return -EIO;
	}

	new_val = old_val & ~mask;
	new_val |= val & mask;

	return max44009_reg_write(drv_data, reg, new_val);
}

static int max44009_attr_set(const struct device *dev,
			     enum sensor_channel chan,
			     enum sensor_attribute attr,
			     const struct sensor_value *val)
{
	struct max44009_data *drv_data = dev->data;
	uint8_t value;
	uint32_t cr;

	if (chan != SENSOR_CHAN_LIGHT) {
		return -ENOTSUP;
	}

	switch (attr) {
	case SENSOR_ATTR_SAMPLING_FREQUENCY:
		/* convert rate to mHz */
		cr = val->val1 * 1000 + val->val2 / 1000;

		/* the sensor supports 1.25Hz or continuous conversion */
		switch (cr) {
		case 1250:
			value = 0U;
			break;
		default:
			value = MAX44009_CONTINUOUS_SAMPLING;
		}

		if (max44009_reg_update(drv_data, MAX44009_REG_CONFIG,
					MAX44009_SAMPLING_CONTROL_BIT,
					value) != 0) {
			LOG_DBG("Failed to set attribute!");
			return -EIO;
		}

		return 0;

	default:
		return -ENOTSUP;
	}

	return 0;
}

static int max44009_sample_fetch(const struct device *dev,
				 enum sensor_channel chan)
{
	struct max44009_data *drv_data = dev->data;
	//uint8_t val_h, val_l;
	uint8_t  val_l;
			LOG_DBG("sample_fetch!");

	__ASSERT_NO_MSG(chan == SENSOR_CHAN_ALL || chan == SENSOR_CHAN_LIGHT);

	drv_data->sample = 0U;
/*
	if (max44009_reg_read(drv_data, MAX44009_REG_LUX_HIGH_BYTE, &val_h,
			      false) != 0) {
		return -EIO;
	}
*/
	//if (max44009_reg_read(drv_data, MAX44009_REG_LUX_LOW_BYTE, &val_l,
	if (max44009_reg_read(drv_data, 0x1b, &val_l,
			      true) != 0) {
			LOG_DBG("reading registry sensor failed!");
		return -EIO;
	}
LOG_DBG("sample_fetch value %d\n", val_l);
//	drv_data->sample = ((uint16_t)val_h) << 8;
	//drv_data->sample += val_l;
	drv_data->sample = val_l;

	return 0;
}

static int max44009_channel_get(const struct device *dev,
				enum sensor_channel chan,
				struct sensor_value *val)
{
	struct max44009_data *drv_data = dev->data;
	uint32_t uval;

	if (chan != SENSOR_CHAN_LIGHT) {
			LOG_DBG("Failed to set channeli light jj!");
		return -ENOTSUP;
	}

	/**
	 * sample consists of 4 bits of exponent and 8 bits of mantissa
	 * bits 15 to 12 are exponent bits
	 * bits 11 to 8 and 3 to 0 are the mantissa bits
	 */
	uval = drv_data->sample;
/*	uval = (uval & MAX44009_MANTISSA_LOW_NIBBLE_MASK) +
	       ((uval & MAX44009_MANTISSA_HIGH_NIBBLE_MASK) >> 4);
	uval = uval << (drv_data->sample >> MAX44009_SAMPLE_EXPONENT_SHIFT);
*/
	/* lux is the integer of sample output multiplied by 0.045. */
	//val->val1 = (uval * 45U) / 1000;
	val->val1 = uval ;
	val->val2 = 0;

	return 0;
}

static const struct sensor_driver_api max44009_driver_api = {
	.attr_set = max44009_attr_set,
	.sample_fetch = max44009_sample_fetch,
	.channel_get = max44009_channel_get,
};

int max44009_init(const struct device *dev)
{

	struct max44009_data *drv_data = dev->data;
 
	drv_data->i2c = device_get_binding(DT_INST_BUS_LABEL(0));
			LOG_DBG("device_get_binding\n");
//k_sleep(K_MSEC(200));
	if (drv_data->i2c == NULL) {
		LOG_DBG("Failed to get pointer to %s device!",
			    DT_INST_BUS_LABEL(0));
		return -EINVAL;
	}
 //       else
//		LOG_DBG("got pointer to device %s",DT_INST_BUS_LABEL(0));
		LOG_DBG("sleep a bit before writing");
k_sleep(K_MSEC(200));
        max44009_reg_write(drv_data, 6, 130);
		LOG_DBG("writing to max44!");
k_sleep(K_MSEC(200));
//here should be a delay 10 ms or something
  //      max44009_reg_write(drv_data, 0x09u, 0x5Au); //get error in using hex-values
        max44009_reg_write(drv_data, 9, 90);
        max44009_reg_write(drv_data, 5, 153);
        max44009_reg_write(drv_data, 127, 1); //switch to bank 1
        max44009_reg_write(drv_data, 56, 0); //switch led off
   //     max44009_reg_write(drv_data, 0x38, 0x22); //switch led on low intensity
        return 0;
};

static struct max44009_data max44009_drv_data;

DEVICE_AND_API_INIT(max44009, DT_INST_LABEL(0), max44009_init,
	    &max44009_drv_data, NULL, POST_KERNEL,
	    CONFIG_SENSOR_INIT_PRIORITY, &max44009_driver_api);

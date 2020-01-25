/*
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <drivers/i2c.h>
#include <init.h>
#include <drivers/sensor.h>
#include <sys/__assert.h>
#include <logging/log.h>

#include "bma421.h"

#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F005)
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F006)
#define MY_REGISTER3 (*(volatile uint8_t*)0x2000F007)
#define MY_REGISTER4 (*(volatile uint8_t*)0x2000F008)
#define MY_REGISTER5 (*(volatile uint8_t*)0x2000F009)
#define MY_REGISTER6 (*(volatile uint8_t*)0x2000F00A)


//#define BMA421_CMD_ADDR                         UINT8_C(0X7E)

LOG_MODULE_REGISTER(BMA421, CONFIG_SENSOR_LOG_LEVEL);



static void i2c_delay(unsigned int cycles_to_wait)
{
	u32_t start = k_cycle_get_32();

	/* Wait until the given number of cycles have passed */
	while (k_cycle_get_32() - start < cycles_to_wait) {
	}
}





static int bma421_sample_fetch(struct device *dev, enum sensor_channel chan)
{
	struct bma421_data *drv_data = dev->driver_data;
	u8_t buf[6];
	u8_t lsb;
	u8_t id = 0U;
	i2c_delay(1000);

	__ASSERT_NO_MSG(chan == SENSOR_CHAN_ALL);

	/*
	 * since all accel data register addresses are consecutive,
	 * a burst read can be used to read all the samples
	 */
	if (i2c_burst_read(drv_data->i2c, BMA421_I2C_ADDRESS,
				BMA421_REG_ACCEL_X_LSB, buf, 6) < 0) {
		LOG_DBG("Could not read accel axis data");
		return -EIO;
	}

	lsb = (buf[0] & BMA421_ACCEL_LSB_MASK) >> BMA421_ACCEL_LSB_SHIFT;
	drv_data->x_sample = (((s8_t)buf[1]) << BMA421_ACCEL_LSB_BITS) | lsb;

	lsb = (buf[2] & BMA421_ACCEL_LSB_MASK) >> BMA421_ACCEL_LSB_SHIFT;
	drv_data->y_sample = (((s8_t)buf[3]) << BMA421_ACCEL_LSB_BITS) | lsb;

	lsb = (buf[4] & BMA421_ACCEL_LSB_MASK) >> BMA421_ACCEL_LSB_SHIFT;
	drv_data->z_sample = (((s8_t)buf[5]) << BMA421_ACCEL_LSB_BITS) | lsb;

	if (i2c_reg_read_byte(drv_data->i2c, BMA421_I2C_ADDRESS,
				BMA421_REG_TEMP,
				(u8_t *)&drv_data->temp_sample) < 0) {
		LOG_DBG("Could not read temperature data");
		return -EIO;
	}
	return 0;
}

static void bma421_channel_accel_convert(struct sensor_value *val,
		s64_t raw_val)
{
	/*
	 * accel_val = (sample * BMA280_PMU_FULL_RAGE) /
	 *             (2^data_width * 10^6)
	 */
	raw_val = (raw_val * BMA421_ACC_FULL_RANGE) /
		(1 << (8 + BMA421_ACCEL_LSB_BITS));
	val->val1 = raw_val / 1000000;
	val->val2 = raw_val % 1000000;

	/* normalize val to make sure val->val2 is positive */
	if (val->val2 < 0) {
		val->val1 -= 1;
		val->val2 += 1000000;
	}
}

static void bma421_channel_value_add(struct sensor_value *val)
{
	val->val1 = 32; //todo -- here values can be read from REG 0x1E step counter
	val->val2 = 88; 
}

static int bma421_channel_get(struct device *dev,
		enum sensor_channel chan,
		struct sensor_value *val)
{
	struct bma421_data *drv_data = dev->driver_data;

	/*
	 * See datasheet "Sensor data" section for
	 * more details on processing sample data.
	 */
	if (chan == SENSOR_CHAN_ACCEL_X) {
		bma421_channel_accel_convert(val, drv_data->x_sample);
	} else if (chan == SENSOR_CHAN_ACCEL_Y) {
		bma421_channel_accel_convert(val, drv_data->y_sample);
	} else if (chan == SENSOR_CHAN_ACCEL_Z) {
		bma421_channel_accel_convert(val, drv_data->z_sample);
	} else if (chan == SENSOR_CHAN_ACCEL_XYZ) {
		bma421_channel_accel_convert(val, drv_data->x_sample);
		bma421_channel_accel_convert(val + 1, drv_data->y_sample);
		bma421_channel_accel_convert(val + 2, drv_data->z_sample);
		bma421_channel_value_add(val + 3); //todo check how extra data can be passed
	} else if (chan == SENSOR_CHAN_DIE_TEMP) {
		/* temperature_val = 23 + sample / 2 */
		val->val1 = (drv_data->temp_sample >> 1) + 23;
		val->val2 = 500000 * (drv_data->temp_sample & 1);
		return 0;
	} else {
		return -ENOTSUP;
	}

	return 0;
}

static const struct sensor_driver_api bma421_driver_api = {
#if CONFIG_BMA421_TRIGGER
	.attr_set = bma421_attr_set,
	.trigger_set = bma421_trigger_set,
#endif
	.sample_fetch = bma421_sample_fetch,
	.channel_get = bma421_channel_get,
};





int bma421_init(struct device *dev)
{
	struct bma421_data *drv_data = dev->driver_data;
	u8_t id = 0U;
	drv_data->i2c = device_get_binding(CONFIG_BMA421_I2C_MASTER_DEV_NAME);
	if (drv_data->i2c == NULL) {
		LOG_DBG("Could not get pointer to %s device",
				CONFIG_BMA421_I2C_MASTER_DEV_NAME);
		return -EINVAL;
	}

	/* read device ID */
	if (i2c_reg_read_byte(drv_data->i2c, BMA421_I2C_ADDRESS,
				BMA421_REG_CHIP_ID, &id) < 0) {
		LOG_DBG("Could not read chip id");
		return -EIO;
	}

	if (id != BMA421_CHIP_ID) {
		LOG_DBG("Unexpected chip id (%x)", id);
		return -EIO;
	}


	if (i2c_reg_update_byte(drv_data->i2c, BMA421_I2C_ADDRESS, BMA421_REG_CMD, BMA421_CMD_SOFT_RESET_MASK, BMA421_CMD_SOFT_RESET) < 0) { //soft reset
		//		MY_REGISTER5=0x33;
	}
//todo clean up debug registers

	i2c_delay(100);

	if (i2c_reg_update_byte(drv_data->i2c, BMA421_I2C_ADDRESS, BMA421_REG_ACC_CONF, 0x80, 0x80) < 0) { //acc performance 1
		//		MY_REGISTER4=0x33;
	}

	//todo create names for hardcoded stuff, review masks - should cover multiple bits...
	i2c_delay(100);
	if (i2c_reg_update_byte(drv_data->i2c, BMA421_I2C_ADDRESS, BMA421_REG_PWR_CTRL , 0x04, 0x04) < 0) { //enable accelerometer
		//		MY_REGISTER5=0x33;
	}
	i2c_delay(100);
	if (i2c_reg_update_byte(drv_data->i2c, BMA421_I2C_ADDRESS, BMA421_REG_PWR_CONF , 0x03, 0x00) < 0) { //disable powersave for testing (todo powersave)
		//		MY_REGISTER5=0x33;
	}
	i2c_delay(100);
	if (i2c_reg_read_byte(drv_data->i2c, BMA421_I2C_ADDRESS, 0x40, &id) < 0) {
		//could not read 0x40
		//		MY_REGISTER3=0xFF;
	}
	MY_REGISTER3=id; // read statement to check if update took place -- useless afterwards todo delete
	/* set g-range */
	i2c_reg_read_byte(drv_data->i2c, BMA421_I2C_ADDRESS,BMA421_REG_ACC_RANGE, &id); 
	id=id & 0xFC; // bit 1 and 0 of 0x41 are set to 0
	id=id | BMA421_ACC_RANGE; //this is set with a variable from Kconfig


	//todo use update_byte instead of write_byte
	if (i2c_reg_write_byte(drv_data->i2c, BMA421_I2C_ADDRESS,
				BMA421_REG_ACC_RANGE, id) < 0) {
		MY_REGISTER5=0xCC;
		LOG_DBG("Could not set data g-range");
		return -EIO;
	}
	else
		MY_REGISTER5=id; //todo remove

	i2c_delay(100);
	i2c_reg_read_byte(drv_data->i2c, BMA421_I2C_ADDRESS,BMA421_REG_ACC_CONF, &id); 
	id=id & 0xF0; //bit 3,2,1,0 are set to 0
	id=id | BMA421_ACC_ODR; 
	if (i2c_reg_write_byte(drv_data->i2c, BMA421_I2C_ADDRESS, BMA421_REG_ACC_CONF, id) < 0) {
		MY_REGISTER6=0xCC;
	}
	else
		MY_REGISTER6=id; //todo remove 

#ifdef CONFIG_BMA421_TRIGGER
	if (bma421_init_interrupt(dev) < 0) {
		LOG_DBG("Could not initialize interrupts");
		return -EIO;
	}
#endif

	return 0;
}

struct bma421_data bma421_driver;

DEVICE_AND_API_INIT(bma421, CONFIG_BMA421_NAME, bma421_init, &bma421_driver,
		NULL, POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,
		&bma421_driver_api);

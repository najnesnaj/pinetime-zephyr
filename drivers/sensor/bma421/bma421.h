/*
 * 
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_BMA421_BMA421_H_
#define ZEPHYR_DRIVERS_SENSOR_BMA421_BMA421_H_

#include <device.h>
#include <sys/util.h>
#include <zephyr/types.h>
#include <drivers/gpio.h>

#define BMA421_I2C_ADDRESS		CONFIG_BMA421_I2C_ADDR

#define BMA421_REG_CHIP_ID		0x00
#if CONFIG_BMA421_CHIP_BMA421
#define BMA421_CHIP_ID		0x11
#endif

#define BMA421_REG_ACC_CONF            0x40 //set the output data rate, bandwidth and read mode
#define BMA421_REG_ACC_RANGE           0x41 //set the output data rate, bandwidth and read mode
#define BMA421_REG_PWR_CONF            0x7C //power mode configuration
#define BMA421_REG_PWR_CTRL            0x7D //sensor enable
#define BMA421_REG_CMD            0x7E //command register
#define BMA421_REG_FEATURE        0x5E //feature register
#define BMA421_REG_INT_LATCH      0x55
#define BMA421_INT_MODE_LATCH     0x01 //permanent latched
#define BMA421_REG_INT1_MAP       0x56
#define BMA421_INT_MAP_MOTION     0x40 //bit 6 for any motion
#define BMA421_REG_INT_STATUS_0   0x1C //interrupt feature status

//#define BMA421_FEATURE_SIZE                    UINT8_C(64)
#define BMA421_FEATURE_SIZE                    64

#define BMA421_CMD_SOFT_RESET        0xB6
#define BMA421_CMD_SOFT_RESET_MASK   0xB6
#define BMA421_ACC_PERF_MODE         0x80 //continues filter function

//#define BMA421_REG_PMU_BW		0x10
#if CONFIG_BMA421_ACC_ODR_1
#define BMA421_ACC_ODR		0x01
#elif CONFIG_BMA421_ACC_ODR_2
#define BMA421_ACC_ODR		0x02
#elif CONFIG_BMA421_ACC_ODR_3
#define BMA421_ACC_ODR		0x03
#elif CONFIG_BMA421_ACC_ODR_4
#define BMA421_ACC_ODR		0x04
#elif CONFIG_BMA421_ACC_ODR_5
#define BMA421_ACC_ODR		0x05
#elif CONFIG_BMA421_ACC_ODR_6
#define BMA421_ACC_ODR		0x06
#elif CONFIG_BMA421_ACC_ODR_7
#define BMA421_ACC_ODR		0x07
#elif CONFIG_BMA421_ACC_ODR_8
#define BMA421_ACC_ODR		0x08
#elif CONFIG_BMA421_ACC_ODR_9
#define BMA421_ACC_ODR		0x09
#elif CONFIG_BMA421_ACC_ODR_10
#define BMA421_ACC_ODR		0x0a
#elif CONFIG_BMA421_ACC_ODR_11
#define BMA421_ACC_ODR		0x0b
#elif CONFIG_BMA421_ACC_ODR_12
#define BMA421_ACC_ODR		0x0c
#elif CONFIG_BMA421_ACC_ODR_13
#define BMA421_ACC_ODR		0x00
#endif




#if CONFIG_BMA421_ACC_RANGE_2G
#define BMA421_ACC_RANGE	0x00
#define BMA421_ACC_FULL_RANGE	(4 * SENSOR_G)
#elif CONFIG_BMA421_ACC_RANGE_4G
#define BMA421_ACC_RANGE	0x01
#define BMA421_ACC_FULL_RANGE	(8 * SENSOR_G)
#elif CONFIG_BMA421_ACC_RANGE_8G
#define BMA421_ACC_RANGE	0x02
#define BMA421_ACC_FULL_RANGE	(16 * SENSOR_G)
#elif CONFIG_BMA421_ACC_RANGE_16G
#define BMA421_ACC_RANGE	0x03
#define BMA421_ACC_FULL_RANGE	(32 * SENSOR_G)
#endif

#define BMA421_REG_TEMP			0x08
#define BMA421_REG_ACCEL_X_LSB		0x12
#define BMA421_REG_ACCEL_Y_LSB		0x14
#define BMA421_REG_ACCEL_Z_LSB		0x16

#if CONFIG_BMA421_CHIP_BMA421
#define BMA421_ACCEL_LSB_BITS	6
#define BMA421_ACCEL_LSB_SHIFT	2
#endif
#define BMA421_ACCEL_LSB_MASK		\
	(BIT_MASK(BMA421_ACCEL_LSB_BITS) << BMA421_ACCEL_LSB_SHIFT)

#define BMA421_REG_ACCEL_X_MSB		0x3
#define BMA421_REG_ACCEL_Y_MSB		0x5
#define BMA421_REG_ACCEL_Z_MSB		0x7

#define BMA421_THREAD_PRIORITY		10
#define BMA421_THREAD_STACKSIZE_UNIT	1024

struct bma421_data {
	struct device *i2c;
	s16_t x_sample;
	s16_t y_sample;
	s16_t z_sample;
	s8_t temp_sample;

#ifdef CONFIG_BMA421_TRIGGER
	struct device *gpio;
	struct gpio_callback gpio_cb;

	struct sensor_trigger data_ready_trigger;
	sensor_trigger_handler_t data_ready_handler;

	struct sensor_trigger any_motion_trigger;
	sensor_trigger_handler_t any_motion_handler;

#if defined(CONFIG_BMA421_TRIGGER_OWN_THREAD)
	K_THREAD_STACK_MEMBER(thread_stack, CONFIG_BMA421_THREAD_STACK_SIZE);
	struct k_thread thread;
	struct k_sem gpio_sem;
#elif defined(CONFIG_BMA421_TRIGGER_GLOBAL_THREAD)
	struct k_work work;
	struct device *dev;
#endif

#endif /* CONFIG_BMA421_TRIGGER */
};

#ifdef CONFIG_BMA421_TRIGGER
int bma421_trigger_set(struct device *dev,
		const struct sensor_trigger *trig,
		sensor_trigger_handler_t handler);

int bma421_attr_set(struct device *dev,
		enum sensor_channel chan,
		enum sensor_attribute attr,
		const struct sensor_value *val);

int bma421_init_interrupt(struct device *dev);
#endif

#endif /* ZEPHYR_DRIVERS_SENSOR_BMA421_BMA421_H_ */

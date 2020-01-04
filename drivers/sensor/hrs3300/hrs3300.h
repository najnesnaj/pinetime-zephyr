/*
 * Copyright (c) 2017, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <drivers/sensor.h>
#include <drivers/i2c.h>
#include <drivers/gpio.h>
#define HRS3300_I2C_ADDRESS  0x44
struct hrs3300_config {
};

struct hrs3300_data {
	struct device *i2c;
	u32_t raw[2];
};

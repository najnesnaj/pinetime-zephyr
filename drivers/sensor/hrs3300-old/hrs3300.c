/*
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>
#include <logging/log.h>
#include <shell/shell.h>
#include <sensor.h>
#include <hrs3300.h>
#include <drivers/i2c.h>

#define MY_REGISTER3 (*(volatile uint8_t*)0x2000F002)

LOG_MODULE_REGISTER(HRS3300, CONFIG_SENSOR_LOG_LEVEL);

#define HRS3300_I2C_ADDRESS  0x44

#define HRS3300_PDRIVE_12_5 0
#define HRS3300_PDRIVE_20 1
#define HRS3300_PDRIVE_30 2
#define HRS3300_PDRIVE_40 3

#define HRS3300_DEVICE_ID_ADDR	0x00
#define HRS3300_DEVICE_ID 0x21

#define HRS3300_ENABLED_ADDR	0x01

#define HRS3300_HWT_800MS 0x0
#define HRS3300_HWT_400MS 0x1
#define HRS3300_HWT_200MS 0x2
#define HRS3300_HWT_100MS 0x3
#define HRS3300_HWT_75MS 0x4
#define HRS3300_HWT_50MS 0x5
#define HRS3300_HWT_12_5MS 0x6
#define HRS3300_HWT_0MS 0x7

struct hrs3300_reg_enable {
	u8_t reserved	:3;
	u8_t pdrive1	:1;
	u8_t hwt	:3;
	u8_t enable	:1;
};

#define HRS3300_HRS_LED_DRIVER_SET_ADDR 0x0C
struct hrs3300_reg_hrs_led_driver_set {
	u8_t reserved	:5;
	u8_t pon	:1;
	u8_t pdrive0	:1;
	u8_t reserved1	:1;
};


#define HRS3300_RESOLUTION_ADDR 0x16
struct hrs3300_reg_resolution {
	u8_t als_res	:4;
	u8_t reserved 	:4;
};

#define HRS3300_HGAIN_ADDR 0x17
struct hrs3300_reg_hgain {
	u8_t reserved 	:2;
	u8_t hgain	:3;
	u8_t reserved1 	:3;
};

union hrs3300_reg {
	struct hrs3300_reg_enable enable;
	struct hrs3300_reg_hrs_led_driver_set hrs_led_driver_set;
	struct hrs3300_reg_resolution resolution;
	struct hrs3300_reg_hgain hgain;
	u8_t raw;
};

struct hrs3300_addr_reg {
	u8_t addr;
	union hrs3300_reg reg;
};

struct hrs3300_data {
	struct device *i2c;
	u32_t raw[2];
	struct hrs3300_addr_reg config[4];
};

struct hrs3300_config {
};

static u32_t get_hrs_adc(u8_t *buf)
{
	return	((u32_t)buf[7] & 0xF) |
		(((u32_t)buf[2] & 0xf) << 4) |
		((u32_t)buf[1] << 8) |
		(((u32_t)buf[7] & 0x30) << 16);
}

static u32_t get_als(u8_t *buf)
{
	return	((u32_t)buf[6] & 0x7) |
		((u32_t)buf[0] << 3) |
		((u32_t)buf[5] << 10);
}

static int hrs3300_sample_fetch(struct device *dev, enum sensor_channel chan)
{
	struct hrs3300_data *data = dev->driver_data;
	u8_t buf[8];
	int err;

	err = i2c_burst_read(data->i2c, HRS3300_I2C_ADDRESS, 0x8,
				buf, sizeof(buf));
	if (err < 0) {
		LOG_ERR("Failed to read data (err:%d)", err);
		return err;
	}

	data->raw[0] = get_hrs_adc(buf);
	data->raw[1] = get_als(buf);

	return 0;
}

//todo method to switch heart rate sensor off
int hrs3300_attr_set(struct device *dev,
		enum sensor_channel chan,
		enum sensor_attribute attr,
		const struct sensor_value *val)
{
	return 0;
}

static int hrs3300_channel_get(struct device *dev, enum sensor_channel chan,
		struct sensor_value *val)
{
	struct hrs3300_data *data = dev->driver_data;

	val->val1 = data->raw[0];
	val->val2 = data->raw[1];

	return 0;
}

static const struct sensor_driver_api hrs3300_driver_api = {
	.sample_fetch = hrs3300_sample_fetch,
	.channel_get = hrs3300_channel_get,
	.attr_set = hrs3300_attr_set,
};

static int hrs3300_init(struct device *dev)
{
	struct hrs3300_data *data = dev->driver_data;
	u8_t device_id;
	int err;

	/* Get the I2C device */
	data->i2c = device_get_binding(DT_INST_0_HX_HRS3300_BUS_NAME);
	if (!data->i2c) {
		LOG_ERR("Could not find I2C device");
		return -EINVAL;
	}

	err = i2c_reg_read_byte(data->i2c, HRS3300_I2C_ADDRESS,
				HRS3300_DEVICE_ID_ADDR, &device_id);
	if ((err < 0) || (device_id != HRS3300_DEVICE_ID)) {
		LOG_ERR("Failed to read device id (%d)", err);
		return err;
	}

	for (int i = 0; i < ARRAY_SIZE(data->config); i++) {
		err = i2c_reg_write_byte(data->i2c, HRS3300_I2C_ADDRESS,
				data->config[i].addr, data->config[i].reg.raw);
		if (err < 0) {
			LOG_ERR("Failed to write %x register (err:%d)",
				data->config[i].addr, err);
			return err;
		}
	}

	return 0;
}

static int write_reg(struct device *dev, struct hrs3300_addr_reg *reg)
{
	struct hrs3300_data *data = dev->driver_data;

	return i2c_reg_write_byte(data->i2c, HRS3300_I2C_ADDRESS,
				reg->addr, reg->reg.raw);
}

static int hrs3300_en(struct device *dev, bool en)
{
	struct hrs3300_data *data = dev->driver_data;

	data->config[0].reg.enable.enable = en ? 1 : 0;
	return write_reg(dev, &data->config[0]);
}

int hrs3300_enable(struct device *dev)
{
	return hrs3300_en(dev, true);
}

int hrs3300_disable(struct device *dev)
{
	return hrs3300_en(dev, false);
}

int hrs3300_hgain_set(struct device *dev, enum hrs3300_hgain val)
{
	struct hrs3300_data *data = dev->driver_data;
	data->config[3].reg.hgain.hgain = val;
	return write_reg(dev, &data->config[3]);
}

int hrs3300_hgain_get(struct device *dev, enum hrs3300_hgain *val)
{
	struct hrs3300_data *data = dev->driver_data;

	*val = data->config[3].reg.hgain.hgain;

	return 0;
}

int hrs3300_hwt_set(struct device *dev, enum hrs3300_hwt val)
{
	struct hrs3300_data *data = dev->driver_data;

	data->config[0].reg.enable.hwt = val;

	return write_reg(dev, &data->config[0]);
}

int hrs3300_hwt_get(struct device *dev, enum hrs3300_hwt *val)
{
	struct hrs3300_data *data = dev->driver_data;

	*val = data->config[0].reg.enable.hwt;

	return 0;
}

int hrs3300_pdrive_set(struct device *dev, enum hrs3300_pdrive val)
{
	struct hrs3300_data *data = dev->driver_data;
	int err;

	data->config[0].reg.enable.pdrive1 = (val & 2) ? 1 : 0;
	data->config[1].reg.hrs_led_driver_set.pdrive0 = val & 1;

	err = write_reg(dev, &data->config[0]);
	if (err < 0) {
		return err;
	}

	return write_reg(dev, &data->config[1]);
}

int hrs3300_pdrive_get(struct device *dev, enum hrs3300_pdrive *val)
{
	struct hrs3300_data *data = dev->driver_data;

	*val = data->config[1].reg.hrs_led_driver_set.pdrive0 |
		(data->config[0].reg.enable.pdrive1 << 1);

	return 0;
}

static struct hrs3300_config hrs3300_config;
static struct hrs3300_data hrs3300_data = {
	.config = {
		{
			.addr = HRS3300_ENABLED_ADDR,
			.reg = {
				.enable = {
					.enable = 0,
					.pdrive1 = (HRS3300_PDRIVE_40 & 0x2) ?
							1 : 0,
					.hwt = HRS3300_HWT_12_5MS
				}
			}
		},
		{
			.addr = HRS3300_HRS_LED_DRIVER_SET_ADDR,
			.reg = {
				.hrs_led_driver_set = {
					.pon = 1,
					.pdrive0 = HRS3300_PDRIVE_40 & 0x1,
					.reserved = 0x8
				}
			}
		},
		{
			.addr = HRS3300_RESOLUTION_ADDR,
			.reg = {
				.resolution = {
					.reserved = 0x6,
					.als_res = 0x8 /* 16bit*/
				}
			}
		},
		{
			.addr = HRS3300_HGAIN_ADDR,
			.reg = {
				.hgain = {
					.hgain = 0
				}
			}
		}
	}
};

DEVICE_AND_API_INIT(hrs3300, DT_INST_0_HX_HRS3300_LABEL, hrs3300_init,
		&hrs3300_data, &hrs3300_config,
		POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,
		&hrs3300_driver_api);

static int cmd_enable(const struct shell *shell, size_t argc, char **argv)
{
	int err;

	err = hrs3300_enable(DEVICE_GET(hrs3300));
	shell_print(shell, "Enabled (err:%d)", err);

	return 0;
}

static int cmd_disable(const struct shell *shell, size_t argc, char **argv)
{
	int err;

	err = hrs3300_disable(DEVICE_GET(hrs3300));
	shell_print(shell, "Disabled (err:%d)", err);

	return 0;
}

static int cmd_dump_registers(const struct shell *shell,
				size_t argc, char **argv)
{
	static const u8_t addr[] = {0, 1, 8, 9, 10, 12, 13, 14, 15, 22, 23};
	struct hrs3300_data *data = DEVICE_GET(hrs3300)->driver_data;
	int err;
	u8_t val;

	for (int i = 0; i < ARRAY_SIZE(addr); i++) {
		err = i2c_reg_read_byte(data->i2c, HRS3300_I2C_ADDRESS, addr[i],
			&val);
		if (err < 0) {
			shell_error(shell, "Failed to read %x (err: %d)",
								addr[i], err);
		} else {
			shell_print(shell, "Reg:%x value:%x", addr[i], val);
		}
	}

	return 0;
}

static int cmd_sample(const struct shell *shell, size_t argc, char **argv)
{
	int err;
	struct sensor_value value;

	err = sensor_sample_fetch(DEVICE_GET(hrs3300));
	if (err < 0) {
		shell_error(shell, "Failed to read (err:%d)", err);
	}

	err = sensor_channel_get(DEVICE_GET(hrs3300), 0, &value);
	if (err < 0) {
		shell_error(shell, "Failed to read channel (err:%d)", err);
	}

	shell_print(shell, "hrs:%d, als:%d", value.val1, value.val2);

	return 0;
}

static int cmd_read_gain(const struct shell *shell, size_t argc, char **argv)
{
	enum hrs3300_hgain gain_reg;
	u8_t gain_val;

	hrs3300_hgain_get(DEVICE_GET(hrs3300), &gain_reg);
	gain_val = (gain_reg < 4) ? (1 << gain_reg) : 64;

	shell_print(shell, "Gain:%dx", gain_val);

	return 0;
}

static int cmd_set_gain1(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hgain_set(DEVICE_GET(hrs3300), 0);
}

static int cmd_set_gain2(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hgain_set(DEVICE_GET(hrs3300), 1);
}

static int cmd_set_gain4(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hgain_set(DEVICE_GET(hrs3300), 2);
}

static int cmd_set_gain8(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hgain_set(DEVICE_GET(hrs3300), 3);
}

static int cmd_set_gain64(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hgain_set(DEVICE_GET(hrs3300), 4);
}

static int cmd_read_hwt(const struct shell *shell, size_t argc, char **argv)
{
	enum hrs3300_hwt val;
	static const char *hwt[] = {"800", "400", "200", "100",
					"75", "50", "12.5", "0"};

	hrs3300_hwt_get(DEVICE_GET(hrs3300), &val);

	shell_print(shell, "HWT:%sms", hwt[val]);

	return 0;
}

static int cmd_set_hwt800(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hwt_set(DEVICE_GET(hrs3300), 0);
}

static int cmd_set_hwt400(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hwt_set(DEVICE_GET(hrs3300), 1);
}

static int cmd_set_hwt200(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hwt_set(DEVICE_GET(hrs3300), 2);
}

static int cmd_set_hwt100(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hwt_set(DEVICE_GET(hrs3300), 3);
}

static int cmd_set_hwt75(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hwt_set(DEVICE_GET(hrs3300), 4);
}

static int cmd_set_hwt50(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hwt_set(DEVICE_GET(hrs3300), 5);
}

static int cmd_set_hwt12_5(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hwt_set(DEVICE_GET(hrs3300), 6);
}

static int cmd_set_hwt0(const struct shell *shell, size_t argc, char **argv)
{
	return hrs3300_hwt_set(DEVICE_GET(hrs3300), 7);
}

static int cmd_read_pdrive(const struct shell *shell, size_t argc, char **argv)
{
	enum hrs3300_pdrive val;
	static const char *pdrive[] = {"12.5", "20", "30", "40"};

	hrs3300_pdrive_get(DEVICE_GET(hrs3300), &val);

	shell_print(shell, "PDrive:%sms", pdrive[val]);

	return 0;
}

static int cmd_set_pdrive12_5(const struct shell *shell, size_t argc,
				char **argv)
{
	return hrs3300_pdrive_set(DEVICE_GET(hrs3300), HRS3300_PDRIVE_12_5);
}

static int cmd_set_pdrive20(const struct shell *shell, size_t argc,
				char **argv)
{
	return hrs3300_pdrive_set(DEVICE_GET(hrs3300), HRS3300_PDRIVE_20);
}

static int cmd_set_pdrive30(const struct shell *shell, size_t argc,
				char **argv)
{
	return hrs3300_pdrive_set(DEVICE_GET(hrs3300), HRS3300_PDRIVE_30);
}

static int cmd_set_pdrive40(const struct shell *shell, size_t argc,
				char **argv)
{
	return hrs3300_pdrive_set(DEVICE_GET(hrs3300), HRS3300_PDRIVE_40);
}

static int cmd_read(const struct shell *shell, size_t argc, char **argv,
			bool hrs)
{
	int len = strtol(argv[1], NULL, 10);
	enum hrs3300_hwt freq_reg;
	u32_t ms[] = {800,400, 200, 100, 75, 50, 12, 0};
	int err;
	static u16_t samples[1024];
	struct sensor_value value;
	int sleep_ms;

	if (len == 0) {
		return 0;
	} else if (len > ARRAY_SIZE(samples)) {
		shell_error(shell, "Request too big, limited to %d",
							ARRAY_SIZE(samples));
	}

	err = hrs3300_hwt_get(DEVICE_GET(hrs3300), &freq_reg);
	if (err < 0) {
		shell_error(shell, "Failed to read hwt (err:%d)", err);
		return 0;
	}

	sleep_ms = ms[freq_reg];

	for (int i = 0; i < len; i++) {
		err = sensor_sample_fetch(DEVICE_GET(hrs3300));
		if (err < 0) {
			shell_error(shell, "Failed to read (err:%d)", err);
			return 0;
		}

		err = sensor_channel_get(DEVICE_GET(hrs3300), 0, &value);
		if (err < 0) {
			shell_error(shell, "Failed to read channel (err:%d)", err);
			return 0;
		}

		samples[i] = (u16_t)(hrs ? value.val1 : value.val2);
		if (sleep_ms == 12) {
			sleep_ms++;
		} else if (sleep_ms == 13) {
			sleep_ms--;
		}

		k_sleep(K_MSEC(sleep_ms));
	}

	for (int i = 0; i < len; i++) {
		shell_print(shell, "%d", samples[i]);
	}

	shell_print(shell, "Sampling period %d", sleep_ms);

	return 0;
}

static int cmd_read_hrs(const struct shell *shell, size_t argc, char **argv)
{
	return cmd_read(shell, argc, argv, true);
}

static int cmd_read_als(const struct shell *shell, size_t argc, char **argv)
{
	return cmd_read(shell, argc, argv, false);
}

SHELL_STATIC_SUBCMD_SET_CREATE(gain_cmds,
	SHELL_CMD_ARG(x1, NULL, "Control Gain", cmd_set_gain1, 1, 0),
	SHELL_CMD_ARG(x2, NULL, "Control Gain", cmd_set_gain2, 1, 0),
	SHELL_CMD_ARG(x4, NULL, "Control Gain", cmd_set_gain4, 1, 0),
	SHELL_CMD_ARG(x8, NULL, "Control Gain", cmd_set_gain8, 1, 0),
	SHELL_CMD_ARG(x64, NULL, "Control Gain", cmd_set_gain64, 1, 0),
	SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(hwt_cmds,
	SHELL_CMD_ARG(800ms, NULL, "Set HWT", cmd_set_hwt800, 1, 0),
	SHELL_CMD_ARG(400ms, NULL, "Set HWT", cmd_set_hwt400, 1, 0),
	SHELL_CMD_ARG(200ms, NULL, "Set HWT", cmd_set_hwt200, 1, 0),
	SHELL_CMD_ARG(100ms, NULL, "Set HWT", cmd_set_hwt100, 1, 0),
	SHELL_CMD_ARG(75ms, NULL, "Set HWT", cmd_set_hwt75, 1, 0),
	SHELL_CMD_ARG(50ms, NULL, "Set HWT", cmd_set_hwt50, 1, 0),
	SHELL_CMD_ARG(12_5ms, NULL, "Set HWT", cmd_set_hwt12_5, 1, 0),
	SHELL_CMD_ARG(0ms, NULL, "Set HWT", cmd_set_hwt0, 1, 0),
	SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(pdrive_cmds,
	SHELL_CMD_ARG(12_5mA, NULL, "Control PDrive", cmd_set_pdrive12_5, 1, 0),
	SHELL_CMD_ARG(20mA, NULL, "Control PDrive", cmd_set_pdrive20, 1, 0),
	SHELL_CMD_ARG(30mA, NULL, "Control PDrive", cmd_set_pdrive30, 1, 0),
	SHELL_CMD_ARG(40mA, NULL, "Control PDrive", cmd_set_pdrive40, 1, 0),
	SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(read_cmds,
	SHELL_CMD_ARG(hrs, NULL, "Read <n> samples", cmd_read_hrs, 2, 0),
	SHELL_CMD_ARG(als, NULL, "Read <n> samples", cmd_read_als, 2, 0),
	SHELL_SUBCMD_SET_END
);

SHELL_STATIC_SUBCMD_SET_CREATE(hrs3300_cmds,
	SHELL_CMD_ARG(hgain, &gain_cmds, "Control Gain", cmd_read_gain, 1, 1),
	SHELL_CMD_ARG(hwt, &hwt_cmds, "Control HWT", cmd_read_hwt, 1, 1),
	SHELL_CMD_ARG(pdrive, &pdrive_cmds, "Control PDrive", cmd_read_pdrive, 1, 1),
	SHELL_CMD_ARG(read, &read_cmds, "Read HRS and ALS", cmd_read, 1, 0),
	SHELL_CMD_ARG(sample, NULL, "Sample HRS and ALS", cmd_sample, 1, 0),
	SHELL_CMD_ARG(dump, NULL, "Dump registers", cmd_dump_registers, 1, 0),
	SHELL_CMD_ARG(disable, NULL, "Disable", cmd_disable, 1, 0),
	SHELL_CMD_ARG(enable, NULL, "Enable", cmd_enable, 1, 0),
	SHELL_SUBCMD_SET_END
);

static int cmd_dummy(const struct shell *shell, size_t argc, char **argv)
{
	return 0;
}

SHELL_COND_CMD_REGISTER(CONFIG_HRS3300_CMDS, hrs3300, &hrs3300_cmds,
		"HRS3300 shell commands", cmd_dummy);

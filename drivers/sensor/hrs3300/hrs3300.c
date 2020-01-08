/*
 * Copyright (c) 2017, NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <logging/log.h>

#include "hrs3300.h"
#include "hrs3300_reg_init.h"
#define MY_REGISTER3 (*(volatile uint8_t*)0x2000F002)
LOG_MODULE_REGISTER(HRS3300, CONFIG_SENSOR_LOG_LEVEL);

static int hrs3300_sample_fetch(struct device *dev, enum sensor_channel chan)
{
	struct hrs3300_data *data = dev->driver_data;
	//	u8_t buffer[MAX30101_MAX_BYTES_PER_SAMPLE];
	//	u32_t fifo_data;
	//	int fifo_chan;
	//	int num_bytes;
	//	int i;

	/* Read all the active channels for one sample */
	//	num_bytes = data->num_channels * MAX30101_BYTES_PER_CHANNEL;
	uint8_t  databuf[3];
	uint16_t dataA, dataH;

	//	databuf[0] = Hrs3300_read_reg(0x09);
	//	databuf[1] = Hrs3300_read_reg(0x0a);
	//	databuf[2] = Hrs3300_read_reg(0x0f);

	if (i2c_reg_read_byte(data->i2c, HRS3300_I2C_ADDRESS,
				0x09, &databuf[0])) {}
	if (i2c_reg_read_byte(data->i2c, HRS3300_I2C_ADDRESS,
				0x0a, &databuf[1])) {}
	if (i2c_reg_read_byte(data->i2c, HRS3300_I2C_ADDRESS,
				0x0f, &databuf[2])) {}
	dataA = ((databuf[0]<<8)|((databuf[1]&0x0F)<<4)|(databuf[2]&0x0F));


	//	databuf[0] = Hrs3300_read_reg(0x08);
	if (i2c_reg_read_byte(data->i2c, HRS3300_I2C_ADDRESS,
				0x08, &databuf[0])) {}
	//	databuf[1] = Hrs3300_read_reg(0x0d);
	if (i2c_reg_read_byte(data->i2c, HRS3300_I2C_ADDRESS,
				0x0d, &databuf[0])) {}
	//	databuf[2] = Hrs3300_read_reg(0x0e);
	if (i2c_reg_read_byte(data->i2c, HRS3300_I2C_ADDRESS,
				0x0e, &databuf[0])) {}

	dataH = ((databuf[0]<<3)|((databuf[1]&0x3F)<<11)|(databuf[2]&0x07));

	if (dataH > 32767) dataH = 32767;

	data->raw[0] = dataA;
	data->raw[1] = dataH;




	//	if (i2c_burst_read(data->i2c, MAX30101_I2C_ADDRESS,
	//			   MAX30101_REG_FIFO_DATA, buffer, num_bytes)) {
	//		LOG_ERR("Could not fetch sample");
	//		return -EIO;
	//	}

	/*	fifo_chan = 0;
		for (i = 0; i < num_bytes; i += 3) {
		Each channel is 18-bits 
		fifo_data = (buffer[i] << 16) | (buffer[i + 1] << 8) |
		(buffer[i + 2]);
		fifo_data &= MAX30101_FIFO_DATA_MASK;

		data->raw[fifo_chan++] = fifo_data;
		}
		*/

	return 0;
}
//todo method to switch heart rate sensor off
int hrs3300_attr_set(struct device *dev,
		enum sensor_channel chan,
		enum sensor_attribute attr,
		const struct sensor_value *val)
{
	struct hrs3300_data *drv_data = dev->driver_data;
	if (chan == SENSOR_CHAN_RED) {
		MY_REGISTER3=0x53;
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver
/*		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x01, 0x08);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x02, 0x80);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x4e);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x16, 0x88);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x22);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x01, 0xf0);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x02);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x22);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x01, 0xf0);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x02);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x22);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x01, 0xf0);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x02);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x22);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x01, 0xf0);
		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x02);*/
	}


	return 0;
}





static int hrs3300_channel_get(struct device *dev, enum sensor_channel chan,
		struct sensor_value *val)
{
	struct hrs3300_data *data = dev->driver_data;
	//enum hrs3300_led_channel led_chan;
	int fifo_chan;
//	struct hrs3300_data *drv_data = dev->driver_data; //todo remove
 
/*		switch (chan) {
		case SENSOR_CHAN_GREEN:
	//led_chan = HRS3300_LED_CHANNEL_GREEN;
	                      //led_chan = 1;
	                      break;
		case SENSOR_CHAN_RED:
			     // MY_REGISTER3=0x33;
//		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver kicked out finally
//		i2c_reg_write_byte(drv_data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x00); //led driver todo remove
                              break;
	default:
	        LOG_ERR("Unsupported sensor channel");
	        return -ENOTSUP;
	}*/
	/*
	   fifo_chan = data->map[led_chan];
	   if (fifo_chan >= HRS3300_MAX_NUM_CHANNELS) {
	   LOG_ERR("Inactive sensor channel");
	   return -ENOTSUP;
	   }
	   */
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
	const struct hrs3300_config *config = dev->config->config_info;
	struct hrs3300_data *data = dev->driver_data;
	u8_t part_id;
	u8_t mode_cfg;
	u32_t led_chan;
	int fifo_chan;
	int i = 0;


	/* Get the I2C device */
	data->i2c = device_get_binding(DT_INST_0_HX_HRS3300_BUS_NAME);
	if (!data->i2c) {
		LOG_ERR("Could not find I2C device");
		return -EINVAL;
	}
	//Hrs3300_write_reg( 0x16, 0x78 );
	//Hrs3300_write_reg( 0x01, 0xd0 );	
	//Hrs3300_write_reg( 0x0c, 0x2e );

	/*init*/
	for (i=0; i<INIT_ARRAY_SIZE;i++)
	{
		i2c_reg_write_byte(data->i2c, HRS3300_I2C_ADDRESS, init_register_array[i][0], init_register_array[i]);
	}
	/*enable chip*/
	i2c_reg_write_byte(data->i2c, HRS3300_I2C_ADDRESS, 0x16, 0x78);
	i2c_reg_write_byte(data->i2c, HRS3300_I2C_ADDRESS, 0x01, 0xd0);
	i2c_reg_write_byte(data->i2c, HRS3300_I2C_ADDRESS, 0x0c, 0x2e);
	/* Check the part id to make sure this is MAX30101 */
	/*	if (i2c_reg_read_byte(data->i2c, HRS3300_I2C_ADDRESS,
		MAX30101_REG_PART_ID, &part_id)) {
		LOG_ERR("Could not get Part ID");
		return -EIO;
		}
		if (part_id != MAX30101_PART_ID) {
		LOG_ERR("Got Part ID 0x%02x, expected 0x%02x",
		part_id, MAX30101_PART_ID);
		return -EIO;
		}
		*/
	/* Reset the sensor */
	/*	if (i2c_reg_write_byte_byte(data->i2c, MAX30101_I2C_ADDRESS,
		MAX30101_REG_MODE_CFG,
		MAX30101_MODE_CFG_RESET_MASK)) {
		return -EIO;
		}
		*/
	/* Wait for reset to be cleared */


	/* Initialize the channel map and active channel count */
	/*	data->num_channels = 0U;
		for (led_chan = 0U; led_chan < MAX30101_MAX_NUM_CHANNELS; led_chan++) {
		data->map[led_chan] = MAX30101_MAX_NUM_CHANNELS;
		}
		*/
	/* Count the number of active channels and build a map that translates
	 * the LED channel number (red/ir/green) to the fifo channel number.
	 */
	/*	for (fifo_chan = 0; fifo_chan < MAX30101_MAX_NUM_CHANNELS;
		fifo_chan++) {
		led_chan = (config->slot[fifo_chan] & MAX30101_SLOT_LED_MASK)-1;
		if (led_chan < MAX30101_MAX_NUM_CHANNELS) {
		data->map[led_chan] = fifo_chan;
		data->num_channels++;
		}
		}
		*/
	return 0;
}
static struct hrs3300_config hrs3300_config;
static struct hrs3300_data hrs3300_data;
/*
   static struct max30101_config max30101_config = {
   .fifo = (CONFIG_MAX30101_SMP_AVE << MAX30101_FIFO_CFG_SMP_AVE_SHIFT) |
#ifdef CONFIG_MAX30101_FIFO_ROLLOVER_EN
MAX30101_FIFO_CFG_ROLLOVER_EN_MASK |
#endif
(CONFIG_MAX30101_FIFO_A_FULL <<
MAX30101_FIFO_CFG_FIFO_FULL_SHIFT),

#if defined(CONFIG_MAX30101_HEART_RATE_MODE)
.mode = MAX30101_MODE_HEART_RATE,
.slot[0] = MAX30101_SLOT_RED_LED1_PA,
.slot[1] = MAX30101_SLOT_DISABLED,
.slot[2] = MAX30101_SLOT_DISABLED,
.slot[3] = MAX30101_SLOT_DISABLED,
#elif defined(CONFIG_MAX30101_SPO2_MODE)
.mode = MAX30101_MODE_SPO2,
.slot[0] = MAX30101_SLOT_RED_LED1_PA,
.slot[1] = MAX30101_SLOT_IR_LED2_PA,
.slot[2] = MAX30101_SLOT_DISABLED,
.slot[3] = MAX30101_SLOT_DISABLED,
#else
.mode = MAX30101_MODE_MULTI_LED,
.slot[0] = CONFIG_MAX30101_SLOT1,
.slot[1] = CONFIG_MAX30101_SLOT2,
.slot[2] = CONFIG_MAX30101_SLOT3,
.slot[3] = CONFIG_MAX30101_SLOT4,
#endif

.spo2 = (CONFIG_MAX30101_ADC_RGE << MAX30101_SPO2_ADC_RGE_SHIFT) |
(CONFIG_MAX30101_SR << MAX30101_SPO2_SR_SHIFT) |
(MAX30101_PW_18BITS << MAX30101_SPO2_PW_SHIFT),

.led_pa[0] = CONFIG_MAX30101_LED1_PA,
.led_pa[1] = CONFIG_MAX30101_LED2_PA,
.led_pa[2] = CONFIG_MAX30101_LED3_PA,
};

static struct max30101_data max30101_data;
*/
DEVICE_AND_API_INIT(hrs3300, DT_INST_0_HX_HRS3300_LABEL, hrs3300_init,
		&hrs3300_data, &hrs3300_config,
		POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,
		&hrs3300_driver_api);

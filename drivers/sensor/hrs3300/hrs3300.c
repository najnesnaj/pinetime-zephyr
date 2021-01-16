/*
 * Copyright (c) 2021, najnesnaj 
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT hx_hrs3300

#include <logging/log.h>

#include "hrs3300.h"
//#include "hrs3300_reg_init.h"

LOG_MODULE_REGISTER(HRS3300, CONFIG_SENSOR_LOG_LEVEL);


static uint32_t get_hrs_adc(uint8_t *buf)
{
	return  ((uint32_t)buf[7] & 0xF) |
		(((uint32_t)buf[2] & 0xf) << 4) |
		((uint32_t)buf[1] << 8) |
		(((uint32_t)buf[7] & 0x30) << 16);
}

static uint32_t get_als(uint8_t *buf)
{
	return  ((uint32_t)buf[6] & 0x7) |
		((uint32_t)buf[0] << 3) |
		((uint32_t)buf[5] << 10);
}



static int hrs3300_sample_fetch(const struct device *dev,
		enum sensor_channel chan)
{
	struct hrs3300_data *data = dev->data;
	const struct hrs3300_config *config = dev->config;
	uint8_t buffer[HRS3300_MAX_BYTES_PER_SAMPLE];
	//uint32_t fifo_data;
	//int fifo_chan;
	//	int num_bytes;
	//int i;

	/* Read all the active channels for one sample */
	//	num_bytes = data->num_channels * HRS3300_BYTES_PER_CHANNEL;
	if (i2c_burst_read(data->i2c, config->i2c_addr,
				HRS3300_MAX_BYTES_PER_SAMPLE, buffer, sizeof(buffer))) {
		LOG_ERR("Could not fetch sample");
		return -EIO;
	}
	/*
	   fifo_chan = 0;
	   for (i = 0; i < num_bytes; i += 3) {
	   fifo_data = (buffer[i] << 16) | (buffer[i + 1] << 8) |
	   (buffer[i + 2]);
	   fifo_data &= HRS3300_FIFO_DATA_MASK;

	   data->raw[fifo_chan++] = fifo_data;
	   }
	 */
	data->raw[0] = get_hrs_adc(buffer);
	data->raw[1] = get_als(buffer);

	return 0;
}

static int hrs3300_channel_get(const struct device *dev,
		enum sensor_channel chan,
		struct sensor_value *val)
{
	struct hrs3300_data *data = dev->data;
	const struct hrs3300_config *config = dev->config; //jj
	enum hrs3300_led_channel led_chan;
	//int fifo_chan;

	switch (chan) {
		case SENSOR_CHAN_RED:
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0xf0 ); //  no waiting 
	//		i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0x01 ); //this switched LED OFF JJ
			led_chan = HRS3300_LED_CHANNEL_RED;
			break;

		case SENSOR_CHAN_IR:
			led_chan = HRS3300_LED_CHANNEL_IR;
			i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0x01 ); //this switched LED OFF JJ
			break;

		case SENSOR_CHAN_GREEN:
			led_chan = HRS3300_LED_CHANNEL_GREEN;
			break;

		default:
			LOG_ERR("Unsupported sensor channel");
			return -ENOTSUP;
	}

	/* Check if the led channel is active by looking up the associated fifo
	 * channel. If the fifo channel isn't valid, then the led channel
	 * isn't active.
	 */
	/*	fifo_chan = data->map[led_chan];
		if (fifo_chan >= HRS3300_MAX_NUM_CHANNELS) {
		LOG_ERR("Inactive sensor channel");
		return -ENOTSUP;
		}*/

	/* TODO: Scale the raw data to standard units */
	//val->val1 = data->raw[fifo_chan];
	//val->val2 = 0;
	val->val1 = data->raw[1]; //ALS
	val->val2 = data->raw[0]; //HRS

	return 0;
}

static const struct sensor_driver_api hrs3300_driver_api = {
	.sample_fetch = hrs3300_sample_fetch,
	.channel_get = hrs3300_channel_get,
};



bool Hrs3300_chip_init(void)
{
	//int i =0 ;
	//uint8_t id =0;
	printk(" hrs3300 init \n");
	/*	for(i = 0; i < HRS3300_MAX_BYTES_PER_SAMPLE;i++)
		{

		if (i2c_reg_write_byte(data->i2c, config->i2c_addr, init_register_array[i][0],
		init_register_array[i][1]) != 0 )
		{
		return false;
		}
		}	

	 */
	//20161117 added by ericy for "low power in no_touch state"		
	/*	if(hrs3300_power_up_flg == 0){
		reg_0x7f=Hrs3300_read_reg(0x7f) ;
		reg_0x80=Hrs3300_read_reg(0x80) ;
		reg_0x81=Hrs3300_read_reg(0x81) ;
		reg_0x82=Hrs3300_read_reg(0x82) ;		
		hrs3300_power_up_flg =  1; 
		}*/
	//20161117 added by ericy for "low power in no_touch state"

	//id = Hrs3300_read_reg(0x00);
	//printk("<<< hrs3300 init done id = 0x%x \r\n", id); // 0x21	
	//printk("%s (%d)	: ==huangwenjun==Hrs3300_chip_init== init done id = 0x%x\n", __func__, __LINE__, id);  // add by hwj

	return true;
	//RTN:
	//return false;		
}

/*
   static int write_reg(struct device *dev, struct hrs3300_addr_reg *reg)
   {
   struct hrs3300_data *data = dev->data;

   return i2c_reg_write_byte(data->i2c, HRS3300_I2C_ADDRESS,
   reg->addr, reg->reg.raw);
   }
 */




static int hrs3300_init(const struct device *dev)
{
	const struct hrs3300_config *config = dev->config;
	struct hrs3300_data *data = dev->data;
	uint8_t part_id;
	//uint8_t mode_cfg;
	uint32_t led_chan;
	int fifo_chan;

	/* Get the I2C device */
	data->i2c = device_get_binding(config->i2c_label);
	if (!data->i2c) {
		LOG_ERR("Could not find I2C device");
		return -EINVAL;
	}

	/* Check the part id to make sure this is HRS3300 */
	if (i2c_reg_read_byte(data->i2c, config->i2c_addr,
				HRS3300_REG_PART_ID, &part_id)) {
		LOG_ERR("Could not get Part ID");
		return -EIO;
	}
	if (part_id != HRS3300_PART_ID) {
		LOG_ERR("Got Part ID 0x%02x, expected 0x%02x",
				part_id, HRS3300_PART_ID);
		return -EIO;
	}

	/* Reset the sensor */
	/*	if (i2c_reg_write_byte(data->i2c, config->i2c_addr,
		HRS3300_REG_MODE_CFG,
		HRS3300_MODE_CFG_RESET_MASK)) {
		return -EIO;
		}*/


	//chip_disable()
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0x08 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x02, 0x80 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x4e );

	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x16, 0x88 );

	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x22 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0xf0 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x02 );

	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x22 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0xf0 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x02 );

	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x22 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0xf0 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x02 );

	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x22 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0xf0 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x02 );

	//chip_enable()
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x16, 0x78 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0xd0 );
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x2e );
	//init

	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x01, 0xd0);  //11010000  bit[7]=1,HRS enable;bit[6:4]=101,wait time=50ms,bit[3]=0,LED DRIVE=22 mA
	//i2c_reg_write_byte(data->i2c, config->i2c_addr,0x01, 0xf0);   //11010000  bit[7]=1,HRS enable;bit[6:4]=101,wait time=50ms,bit[3]=0,LED DRIVE=22 mA v13.05
	//i2c_reg_write_byte(data->i2c, config->i2c_addr,0x0c, 0x4e);  //00001110  bit[6]=0,LED DRIVE=22mA;bit[5]=0,sleep mode;p_pulse=1110,duty=50% 
	//i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0x01 ); //this switched LED OFF JJ 
	//    i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0x81 ); // LED blinks 800 ms 
	i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x01, 0xf0 ); //  no waiting 
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x0c, 0x02);  //00001110  bit[6]=0,LED DRIVE=22mA;bit[5]=0,sleep mode;p_pulse=1110,duty=50% 

	//i2c_reg_write_byte(data->i2c, config->i2c_addr, 0x0c, 0x22 );
	//0x4e 01001110


	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x16, 0x78);  //01111000  bits[7:4]=0111,HRS 15bits
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x17, 0x0d);  //00001101  bits[7:5]=011,HRS gain 16*;bit[1]=0,HRS data=AD0 
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x02, 0x80);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x03, 0x00);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x04, 0x00);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x05, 0x00);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x06, 0x00);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x07, 0x00);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x08, 0x74);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x09, 0x00);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x0a, 0x08);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x0b, 0x00);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x0c, 0x6e);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x0d, 0x02);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x0e, 0x07);
	i2c_reg_write_byte(data->i2c, config->i2c_addr,0x0f, 0x0f);
	/* Wait for reset to be cleared */
	/*	do {
		if (i2c_reg_read_byte(data->i2c, config->i2c_addr,
		HRS3300_REG_MODE_CFG, &mode_cfg)) {
		LOG_ERR("Could read mode cfg after reset");
		return -EIO;
		}
		} while (mode_cfg & HRS3300_MODE_CFG_RESET_MASK);
	 */

#ifdef CONFIG_HRS3300_MULTI_LED_MODE
	uint8_t multi_led[2];

	/* Write the multi-LED mode control registers */
	multi_led[0] = (config->slot[1] << 4) | (config->slot[0]);
	multi_led[1] = (config->slot[3] << 4) | (config->slot[2]);

	if (i2c_reg_write_byte(data->i2c, config->i2c_addr,
				HRS3300_REG_MULTI_LED, multi_led[0])) {
		return -EIO;
	}
	if (i2c_reg_write_byte(data->i2c, config->i2c_addr,
				HRS3300_REG_MULTI_LED + 1, multi_led[1])) {
		return -EIO;
	}
#endif

	/* Initialize the channel map and active channel count */
	data->num_channels = 0U;
	for (led_chan = 0U; led_chan < HRS3300_MAX_NUM_CHANNELS; led_chan++) {
		data->map[led_chan] = HRS3300_MAX_NUM_CHANNELS;
	}

	/* Count the number of active channels and build a map that translates
	 * the LED channel number (red/ir/green) to the fifo channel number.
	 */
	for (fifo_chan = 0; fifo_chan < HRS3300_MAX_NUM_CHANNELS;
			fifo_chan++) {
		led_chan = (config->slot[fifo_chan] & HRS3300_SLOT_LED_MASK)-1;
		if (led_chan < HRS3300_MAX_NUM_CHANNELS) {
			data->map[led_chan] = fifo_chan;
			data->num_channels++;
		}
	}

	return 0;
}

static struct hrs3300_config hrs3300_config = {
	.i2c_label = DT_INST_BUS_LABEL(0),
	.i2c_addr = DT_INST_REG_ADDR(0),
	.fifo = (CONFIG_HRS3300_SMP_AVE << HRS3300_FIFO_CFG_SMP_AVE_SHIFT) |
#ifdef CONFIG_HRS3300_FIFO_ROLLOVER_EN
		HRS3300_FIFO_CFG_ROLLOVER_EN_MASK |
#endif
		(CONFIG_HRS3300_FIFO_A_FULL <<
		 HRS3300_FIFO_CFG_FIFO_FULL_SHIFT),

#if defined(CONFIG_HRS3300_HEART_RATE_MODE)
	.mode = HRS3300_MODE_HEART_RATE,
	.slot[0] = HRS3300_SLOT_RED_LED1_PA,
	.slot[1] = HRS3300_SLOT_DISABLED,
	.slot[2] = HRS3300_SLOT_DISABLED,
	.slot[3] = HRS3300_SLOT_DISABLED,
#elif defined(CONFIG_HRS3300_SPO2_MODE)
	.mode = HRS3300_MODE_SPO2,
	.slot[0] = HRS3300_SLOT_RED_LED1_PA,
	.slot[1] = HRS3300_SLOT_IR_LED2_PA,
	.slot[2] = HRS3300_SLOT_DISABLED,
	.slot[3] = HRS3300_SLOT_DISABLED,
#else
	.mode = HRS3300_MODE_MULTI_LED,
	.slot[0] = CONFIG_HRS3300_SLOT1,
	.slot[1] = CONFIG_HRS3300_SLOT2,
	.slot[2] = CONFIG_HRS3300_SLOT3,
	.slot[3] = CONFIG_HRS3300_SLOT4,
#endif

	.spo2 = (CONFIG_HRS3300_ADC_RGE << HRS3300_SPO2_ADC_RGE_SHIFT) |
		(CONFIG_HRS3300_SR << HRS3300_SPO2_SR_SHIFT) |
		(HRS3300_PW_18BITS << HRS3300_SPO2_PW_SHIFT),

	.led_pa[0] = CONFIG_HRS3300_LED1_PA,
	.led_pa[1] = CONFIG_HRS3300_LED2_PA,
	.led_pa[2] = CONFIG_HRS3300_LED3_PA,
};

static struct hrs3300_data hrs3300_data;

DEVICE_DT_INST_DEFINE(0, hrs3300_init, device_pm_control_nop,
		&hrs3300_data, &hrs3300_config,
		POST_KERNEL, CONFIG_SENSOR_INIT_PRIORITY,
		&hrs3300_driver_api);

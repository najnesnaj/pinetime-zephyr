/*
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* measure battery power on pin 31 of the Pinetime
 */
#define MY_REGISTER1 (*(volatile uint8_t*)0x2000F000)
#define MY_REGISTER2 (*(volatile uint8_t*)0x2000F001)
#include <drivers/adc.h>
#include <zephyr.h>


#if defined(CONFIG_BOARD_PINETIME)

#include <hal/nrf_saadc.h>
#define ADC_DEVICE_NAME		DT_ADC_0_NAME
#define ADC_RESOLUTION		10
#define ADC_GAIN		ADC_GAIN_1_6
#define ADC_REFERENCE		ADC_REF_INTERNAL
#define ADC_ACQUISITION_TIME	ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 10)
#define ADC_1ST_CHANNEL_ID	31 //todo 
#define ADC_1ST_CHANNEL_INPUT	NRF_SAADC_INPUT_AIN1
#define ADC_2ND_CHANNEL_ID	2
#define ADC_2ND_CHANNEL_INPUT	NRF_SAADC_INPUT_AIN2


#else
#error "Unsupported board."
#endif

#define BUFFER_SIZE  6
//static ZTEST_BMEM s16_t m_sample_buffer[BUFFER_SIZE];
s16_t m_sample_buffer[BUFFER_SIZE];

static const struct adc_channel_cfg m_1st_channel_cfg = {
	.gain             = ADC_GAIN,
	.reference        = ADC_REFERENCE,
	.acquisition_time = ADC_ACQUISITION_TIME,
	.channel_id       = ADC_1ST_CHANNEL_ID,
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
	.input_positive   = ADC_1ST_CHANNEL_INPUT,
#endif
};

struct device *get_adc_device(void)
{
	return device_get_binding(ADC_DEVICE_NAME);
}

static struct device *init_adc(void)
{
	int ret;
	struct device *adc_dev = device_get_binding(ADC_DEVICE_NAME);


	ret = adc_channel_setup(adc_dev, &m_1st_channel_cfg);


	(void)memset(m_sample_buffer, 0, sizeof(m_sample_buffer));

	return adc_dev;
}


int read_battery(void)
{
	int ret;
	const struct adc_sequence sequence = {
		.channels    = BIT(ADC_1ST_CHANNEL_ID),
		.buffer      = m_sample_buffer,
		.buffer_size = sizeof(m_sample_buffer),
		.resolution  = ADC_RESOLUTION,
	};
	MY_REGISTER1 = 0x01;

	struct device *adc_dev = init_adc();

	if (!adc_dev) {
	MY_REGISTER1 = 0xee;
	}
        ret =0;
	//MY_REGISTER1 = 0xcc;
	ret = adc_read(adc_dev, &sequence);
	MY_REGISTER1 = ret;
        return(ret);
}







void main(void)
{      
        MY_REGISTER1 =0x00;	
        MY_REGISTER2 =0x00;	
	int voltage;
        voltage = read_battery() ;
}

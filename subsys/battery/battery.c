/*
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <battery.h>
#include <device.h>
#include <drivers/adc.h>
#include <drivers/gpio.h>
#include <hal/nrf_saadc.h>
#include <nrfx_saadc.h>
#include <logging/log.h>
#include <shell/shell.h>
LOG_MODULE_REGISTER(battery);

#if !defined(CONFIG_BOARD_PINETIME)
#error "Unsupported board."
#endif

#define USE_NRFX_SAADC 0
#define RESOLUTION 12

#define CHARGE_PIN 12
#define EXT_POWER_PIN 19
#define DIVIDER 2 /* On board resistor divider (full 2M, top 1M) */


static struct device *adc;
static struct device *gpio;

#define CHANNEL_ID 1
#define SAADC_OVERSAMPLE NRF_SAADC_OVERSAMPLE_8X

/* Factors for selecting ADC settings:
 * - Max battery voltage: 4200mV
 * - After on board divider: 2100mV
 * - In order to fit below 600mV internal reference 1/4 gain must be applied.
 * - After 1/4 gain max voltage: 525mV (below reference)
 */
static const struct adc_channel_cfg m_1st_channel_cfg = {
	.gain             = ADC_GAIN_1_4,
	.reference        = ADC_REF_INTERNAL,
	.acquisition_time = ADC_ACQ_TIME(ADC_ACQ_TIME_MICROSECONDS, 20),
	.channel_id       = CHANNEL_ID,
#if defined(CONFIG_ADC_CONFIGURABLE_INPUTS)
	.input_positive   = NRF_SAADC_INPUT_AIN7,
#endif
};

static struct k_sem sem;
static bool charge_active;
static bool ext_power_active;
static battery_callback_t callback;

struct battery_level_point {
	/** Remaining life at #lvl_mV. */
	u16_t lvl_pptt;

	/** Battery voltage at #lvl_pptt remaining life. */
	u16_t lvl_mV;
};

static const struct battery_level_point lipo[] = {

	/* "Curve" from https://forum.pine64.org/showthread.php?tid=8147
	 */

	{ 10000, 4200 },
	{ 5000, 3660},
	{ 2100, 3600 },
	{ 1000, 3560},
	{ 0, 3100 },
};

static void saadc_handler(nrfx_saadc_evt_t const * p_event)
{
	if (p_event->type == NRFX_SAADC_EVT_DONE) {
		k_sem_give(&sem);
	}
}

static int init_nrfx_saadc(void)
{
	#define OVERSAMPLE 0
	#define RESOLUTION_CFG \
		((RESOLUTION == 12) ? NRF_SAADC_RESOLUTION_12BIT : \
		((RESOLUTION == 10) ? NRF_SAADC_RESOLUTION_10BIT : \
		NRF_SAADC_RESOLUTION_14BIT))
	nrfx_err_t err;

	static const nrfx_saadc_channel_t channel = {
		.channel_config = {
			.resistor_p = NRF_SAADC_RESISTOR_DISABLED,
			.resistor_n = NRF_SAADC_RESISTOR_DISABLED,
			.gain = NRF_SAADC_GAIN1_6,
			.reference = NRF_SAADC_REFERENCE_VDD4,
			.acq_time = NRF_SAADC_ACQTIME_20US,
			.mode = NRF_SAADC_MODE_SINGLE_ENDED,
			.burst = OVERSAMPLE ? NRF_SAADC_BURST_ENABLED :
				NRF_SAADC_BURST_DISABLED
		},
		.pin_p = NRF_SAADC_INPUT_AIN7,
		.pin_n = NRF_SAADC_INPUT_DISABLED,
		.channel_index = 0
	};

	IRQ_CONNECT(DT_NORDIC_NRF_SAADC_ADC_0_IRQ_0,
		    DT_NORDIC_NRF_SAADC_ADC_0_IRQ_0_PRIORITY,
		    nrfx_isr, nrfx_saadc_irq_handler, 0);

	err = nrfx_saadc_init(5);
	if (err != NRFX_SUCCESS) {
		LOG_ERR("init failed %x", err);
		return -EIO;
	}

	err = nrfx_saadc_channels_config(&channel, 1);
	if (err != NRFX_SUCCESS) {
		LOG_ERR("channel config failed %x", err);
		return -EIO;
	}

	err = nrfx_saadc_simple_mode_set(BIT(0),
				RESOLUTION_CFG,
				OVERSAMPLE ? NRF_SAADC_OVERSAMPLE_8X :
					NRF_SAADC_OVERSAMPLE_DISABLED,
				saadc_handler);
	if (err != NRFX_SUCCESS) {
		LOG_ERR("mode set failed %x", err);
		return -EIO;
	}


	k_sem_init(&sem, 0, 1);

	return 0;
}

static void timeout_handler(struct k_timer *timer);

K_TIMER_DEFINE(debounce_timer, timeout_handler, NULL);

static void timeout_handler(struct k_timer *timer)
{
	u32_t ext_power_val;
	u32_t charge_val;
	bool log_action;

	gpio_pin_read(gpio, CHARGE_PIN, &ext_power_val);

	if (ext_power_val) {
		log_action = true;
		ext_power_active = false;
		charge_active = false;
		if (callback) {
			callback(BATTERY_EVT_DISCONNECTED);
		}
	} else {
		log_action = !ext_power_active;
		ext_power_active = true;
		gpio_pin_read(gpio, CHARGE_PIN, &charge_val);
		charge_active = charge_val ? false : true;

		if (callback) {
			callback(charge_active ? BATTERY_EVT_CHARGING :
						 BATTERY_EVT_NOT_CHARGING);
		}
		/* If power is connected use timer to periodically check if
		 * charging is active.
		 */
		k_timer_start(&debounce_timer, K_MSEC(50), 0);
		if (!log_action) {
			log_action = !charge_active;
		}
	}

	if (log_action) {
		LOG_INF("power pin change. Ext power %sconnected%s",
			ext_power_active ? "" : "not ",
			charge_active ? " (charging)" : "");
	}
}

bool battery_is_powered(void)
{
	return ext_power_active;
}

bool battery_is_charging(void)
{
	return charge_active;
}

static void pin_handler(struct device *gpiob, struct gpio_callback *cb,
		    u32_t pins)
{
	static bool flop = true;

	gpio_pin_configure(gpio, EXT_POWER_PIN,
			   GPIO_DIR_IN | GPIO_INT |  GPIO_PUD_NORMAL |
			   GPIO_INT_LEVEL |
			   (flop ?
			   GPIO_INT_ACTIVE_HIGH : GPIO_INT_ACTIVE_LOW));
	flop = !flop;
	k_timer_stop(&debounce_timer);
	k_timer_start(&debounce_timer, K_MSEC(2), 0);

}

static struct gpio_callback gpio_cb;

static int charge_pins_init(void)
{
	gpio = device_get_binding("GPIO_0");
	if (gpio == NULL) {
		return -ENODEV;
	}

	gpio_pin_configure(gpio, CHARGE_PIN,
			   GPIO_DIR_IN | GPIO_PUD_NORMAL);

	gpio_pin_configure(gpio, EXT_POWER_PIN,
			   GPIO_DIR_IN | GPIO_INT |  GPIO_PUD_NORMAL |
			   GPIO_INT_LEVEL | GPIO_INT_ACTIVE_LOW);

	gpio_init_callback(&gpio_cb, pin_handler, BIT(EXT_POWER_PIN));

	gpio_add_callback(gpio, &gpio_cb);
	gpio_pin_enable_callback(gpio, EXT_POWER_PIN);

	return 0;
}

static int adc_monitor_init(void)
{
	if (USE_NRFX_SAADC) {
		return init_nrfx_saadc();
	}

	adc = device_get_binding(DT_ADC_0_NAME);
	if (adc == NULL) {
		return -ENODEV;
	}

	return adc_channel_setup(adc, &m_1st_channel_cfg);
}

int battery_init(battery_callback_t cb)
{
	int err;

	err = adc_monitor_init();
	if (err < 0) {
		return err;
	}

	err = charge_pins_init();
	if (err < 0) {
		return err;
	}

	callback = cb;

	return 0;
}


int battery_read(s16_t *raw)
{
	s16_t data[1];
	int err;

	const struct adc_sequence sequence = {
		.channels    = BIT(CHANNEL_ID),
		.buffer      = data,
		.buffer_size = sizeof(data),
		.resolution  = RESOLUTION,
	};

	if (USE_NRFX_SAADC) {
		nrfx_saadc_buffer_set(raw, 1);
		nrfx_saadc_mode_trigger();
		return k_sem_take(&sem, K_MSEC(100));
	}

	err = adc_read(adc, &sequence);
	if (err < 0) {
		return err;
	}

	*raw = data[0];

	return 0;
}

int battery_raw_to_mv(s16_t raw)
{
	return (DIVIDER*600*(((int)raw*4*1000) >> RESOLUTION))/1000;
}

/* converstion to pptt taken from
 * https://github.com/zephyrproject-rtos/zephyr/pull/21606
 */
int battery_mv_to_ppt(int mv)
{
	const struct battery_level_point *pb = lipo;

	if (mv >= pb->lvl_mV) {
		/* Measured voltage above highest point, cap at maximum. */
		return pb->lvl_pptt;
	}
	/* Go down to the last point at or below the measured voltage. */
	while ((pb->lvl_pptt > 0)
	       && (mv < pb->lvl_mV)) {
		++pb;
	}
	if (mv < pb->lvl_mV) {
		/* Below lowest point, cap at minimum */
		return pb->lvl_pptt;
	}

	/* Linear interpolation between below and above points. */
	const struct battery_level_point *pa = pb - 1;

	return pb->lvl_pptt
	       + ((pa->lvl_pptt - pb->lvl_pptt)
		  * (mv - pb->lvl_mV)
		  / (pa->lvl_mV - pb->lvl_mV));
}

static int cmd_battery_status(const struct shell *shell,
				size_t argc, char **argv)
{
	int err;
	int mv;
	int proc;
	s16_t raw;

	err = battery_read(&raw);
	if (err < 0) {
		shell_error(shell, "Failed to read");
	}
	mv = battery_raw_to_mv(raw);
	proc = battery_mv_to_ppt(mv);
	shell_print(shell, "Charger %sconnected%s",
			battery_is_powered() ? "" : "not ",
			battery_is_charging() ? " (charging)" : "");
	shell_print(shell, "raw:%d(0x%x) mV:%d level:%d.%02d%%",
			raw, raw, mv, proc/100, proc % 100);

	return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_battery,
	SHELL_CMD_ARG(status, NULL,
			"Status", cmd_battery_status, 1, 0),
	SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(battery, &sub_battery, "Commands for battery monitor",
		   NULL);

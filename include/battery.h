/*
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BATTERY_H__
#define BATTERY_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <zephyr.h>

#ifdef __cplusplus
}
#endif

/** @brief Battery events. */
enum battery_evt {
	BATTERY_EVT_CHARGING,		/* Ext power connected and charging. */
	BATTERY_EVT_NOT_CHARGING,	/* Ext power connected, not charging. */
	BATTERY_EVT_DISCONNECTED,	/* Ext power not connected. */
};

typedef void (*battery_callback_t)(enum battery_evt);

/** @brief Battery monitor initialization.
 *
 * Initializes ADC and gpios for monitoring external power state. Callback is
 * called from interrupt context.
 *
 * @param callback	Notifies ext power state changes. Can be NULL.
 *
 * @return 0 on success, negative number on error.
 */
int battery_init(battery_callback_t callback);

/** @brief Read raw ADC value.
 *
 * Must be called from thread context.
 *
 * @param raw	Location to put raw value.
 *
 * @return 0 on success, negative number on error.
 */
int battery_read(s16_t *raw);

/** @brief Convert raw value to millivolts.
 *
 * @param raw	Raw value.
 * @return Value in millivolts.
 */
int battery_raw_to_mv(s16_t raw);

/** @brief Coonvert millivolts to pptt (points per ten thousend)
 *
 * @param mv	Millivots.
 * @return pptt value calculated based on estimated discharge curve.
 */
int battery_mv_to_ppt(int mv);

/** @brief Check if external power is connected.
 *
 * @return true if connected.
 */
bool battery_is_powered(void);

/** @brief Check if charging is active.
 *
 * @return true if charging.
 */
bool battery_is_charging(void);

#endif /* BATTERY_H__ */

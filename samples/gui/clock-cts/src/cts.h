/** @file
 *  @brief CTS Service
 */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CTS_H
#define CTS_H
#include <stddef.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

void cts_init(void);
void cts_notify(void);

typedef void (*cts_write_cb_t)(int);
void cts_register_write_cb(cts_write_cb_t);

typedef struct {
	uint16_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t day_of_week;
	uint8_t exact_time_256;
	uint8_t adjust_reason;
} cts_datetime_t;

void cts_get_datetime(cts_datetime_t*);

#ifdef __cplusplus
}
#endif
#endif
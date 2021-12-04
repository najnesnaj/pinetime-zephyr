/*
 * Modifications: Copyright (c) 2020 Endian Technologies AB
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CTS__H
#define CTS__H

#include <time.h>
#include <stdbool.h>

void cts_sync_init(void);
void cts_sync_loop(void);
void cts_sync_enable(bool enable);
void cts_update_datetime(struct tm *);

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

#endif /* CTS__H */

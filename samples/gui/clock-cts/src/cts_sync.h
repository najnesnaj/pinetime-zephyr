
/** @file
 *  @brief CTS Service sample
 */

/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef __cplusplus
extern "C" {
#endif
void cts_sync_init();
void cts_sync_loop();





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

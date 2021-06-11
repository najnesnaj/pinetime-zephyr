/*
 * Copyright (c) 2020 Endian Technologies AB
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CLOCK__H
#define CLOCK__H

#include <cts_sync.h>

void clock_init(void);
void clock_increment_local_time(void);
void clock_sync_time(cts_datetime_t *cts);
void clock_show_time(void);
void clock_set_alarm(int);
void clock_stop_alarm();
bool clock_check_alarm();
#endif /* CLOCK__H */

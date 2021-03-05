/*
 * Copyright (c) 2021 najnesnaj@yahoo.com
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <zephyr/types.h>
#include "battery.h"
#include "bt.h"
#include "version.h"
#include "cts_sync.h"
#include "log.h"
#include "event_handler.h"
//#include "gfx.h"
#include "display.h"

/* ********** ********** VARIABLES ********** ********** */
static char time_label_str[32];
static char date_label_str[32];
typedef unsigned long long  u64_t;

static u64_t uptime_ms;
static u64_t last_uptime_ms;
static u64_t elapsed_ms;

static struct tm ti = {
	.tm_sec = 0,
	.tm_min = 0,
	.tm_hour = 0,
	.tm_mday = 0,
	.tm_mon = 0,
	.tm_year = 0,
	.tm_wday = 0,
};

/* ********** ********** FUNCTIONS *********** ********** */
void clock_str_to_local_time(const char *str)
{
	if (sscanf(str, "%d-%d-%dT%d:%d:%d", &ti.tm_year, &ti.tm_mon,
		   &ti.tm_mday, &ti.tm_hour, &ti.tm_min, &ti.tm_sec) != 6) {
		LOG_ERR("Failed to parse time of build.");
	}
	ti.tm_year-=1900;
	ti.tm_mon-=1;
	mktime(&ti);
}

void clock_init()
{
	/* Set time to time of build */
	clock_str_to_local_time(TIME_OF_BUILD);
	LOG_DBG("Time set to time of build");
	LOG_DBG("Clock init: Done");
}

void clock_update_elapsed_ms()
{
	uptime_ms = k_uptime_get();
	elapsed_ms = uptime_ms - last_uptime_ms;
	last_uptime_ms = uptime_ms;
	LOG_INF("Clock updated: "); //jj
}

/* Called by cts sync */
void clock_sync_time(cts_datetime_t *cts)
{
	ti.tm_year = cts->year -1900;
	ti.tm_mon = cts->month -1;
	ti.tm_mday = cts->day;
	ti.tm_hour = cts->hours;
	ti.tm_min = cts->minutes;
	ti.tm_sec = cts->seconds;
	mktime(&ti);
	clock_update_elapsed_ms();
}

/* Called by event handler */
void clock_increment_local_time()
{
	clock_update_elapsed_ms();
	ti.tm_sec += elapsed_ms / 1000;
	mktime(&ti);
}

void clock_show_time()
{
	strftime(time_label_str, 32, "%H:%M", &ti);
	strftime(date_label_str, 32, "%a %d %b", &ti);
	display_time_set_label(time_label_str);
	display_date_set_label(date_label_str);
}

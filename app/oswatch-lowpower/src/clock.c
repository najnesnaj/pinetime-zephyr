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
#include "display.h"

/* ********** ********** VARIABLES ********** ********** */
static char time_label_str[32];
static char date_label_str[32];
typedef unsigned long long  u64_t;

static u64_t uptime_ms;
static u64_t last_uptime_ms;
static u64_t elapsed_ms;
//static u64_t alarm_ms=0;

static bool alarm_on = false;

static struct tm ti,alarm1 = {
	.tm_sec = 0,
	.tm_min = 0,
	.tm_hour = 0,
	.tm_mday = 0,
	.tm_mon = 0,
	.tm_year = 0,
	.tm_wday = 0,
	.tm_isdst = 1,
};

/* ********** ********** FUNCTIONS *********** ********** */
void clock_str_to_local_time(const char *str)
{
	if (sscanf(str, "%d-%d-%dT%d:%d:%d", &ti.tm_year, &ti.tm_mon,
				&ti.tm_mday, &ti.tm_hour, &ti.tm_min, &ti.tm_sec) != 6) {
		LOG_ERR("Failed to parse time of build.");
	}
	ti.tm_year-=1900;
	ti.tm_isdst=1; //daylight savings
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

void clock_set_alarm(int minut)
{
	time_t atime;
	alarm1.tm_year = ti.tm_year ;
	alarm1.tm_mon = ti.tm_mon  ;
	alarm1.tm_mday = ti.tm_mday ;
	//alarm1.tm_hour = ti.tm_hour -1 ; //todo jj dunno why substract 1 works
	alarm1.tm_hour = ti.tm_hour  ; //todo jj dunno why substract 1 works
	alarm1.tm_min = ti.tm_min  ;
	alarm1.tm_sec = ti.tm_sec + minut*60 ;
	alarm1.tm_isdst = 1;
	atime=mktime(&alarm1);
	printk("%d month", alarm1.tm_mon);
	printk("%d year", alarm1.tm_year);
	printk("%d hour", alarm1.tm_hour);
//	atime=atime+minut*60;
	alarm_on = true;
}

void clock_stop_alarm()
{ //alarm is set to the current time - so is expired
	alarm1.tm_year = ti.tm_year ;
	alarm1.tm_mon = ti.tm_mon  ;
	alarm1.tm_mday = ti.tm_mday ;
	alarm1.tm_hour = ti.tm_hour ;
	alarm1.tm_min = ti.tm_min  ;
	alarm1.tm_sec = ti.tm_sec  ;
	alarm1.tm_isdst = 1;
	//       mktime(&alarm1);
	alarm_on = false;
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
	time_t atime,now;
	double seconds_left; 
	clock_update_elapsed_ms();
	ti.tm_sec += elapsed_ms / 1000;
	now=mktime(&ti);
	if (alarm_on)  {
	//	now = mktime(&ti);
		atime=mktime(&alarm1);
		seconds_left=difftime(atime,now);
		if (seconds_left < 60)
		{
			printk("ALARM ALARM -- DO SOMETHING!!!!\n");
			alarm_on=false; //switch off alarm once alarmevent is due
		}

	}
}

bool clock_check_alarm()
{
	return(alarm_on);
}


void clock_show_time()
{       
	strftime(time_label_str, 32, "%H:%M", &ti);
	display_time_set_label(time_label_str);
	if (alarm_on)
	{
		strftime(date_label_str, 32, "Alarm %H:%M", &alarm1);
		display_date_set_label(date_label_str);
	}
	else
	{
		strftime(date_label_str, 32, "%a %d %b", &ti);
		display_date_set_label(date_label_str);
	}
}

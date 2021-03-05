/*
 * Copyright (c) 2020 Dejvino
 * Copyright (c) 2020 Endian Technologies AB
 * Copyright (c) 2020 max00
 * Copyright (c) 2021 Najnesnaj 
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <zephyr/types.h>
#include <time.h>
#include "log.h"
#include "cts_sync.h"
#include "clock.h"

/* ********** Definitions ********** */
#define CTS_SYNC_INTERVAL K_SECONDS(60)

/* ********** Function prototypes ********** */
static void cts_sync_timer_timeout_handler(struct k_timer *);
static void cts_sync_processor(struct bt_conn *, void *);

/* ********** Variables ********** */
static struct k_timer m_cts_sync_timer;
static struct bt_gatt_discover_params cts_discovery_params;
static struct bt_uuid_16 uuid = BT_UUID_INIT_16(0);
static struct bt_gatt_read_params read_params;
cts_datetime_t clock_datetime;
static struct {
	int offset;
	cts_datetime_t datetime;
} m_read_buf;

/* ********** Functions ********** */
void cts_sync_init()
{
	LOG_INF("CTS sync init\n");
	k_timer_init(&m_cts_sync_timer, cts_sync_timer_timeout_handler, NULL);
}

void cts_sync_enable(bool enable)
{
	if (enable) {
		k_timer_start(&m_cts_sync_timer, K_NO_WAIT, CTS_SYNC_INTERVAL);
	} else {
		k_timer_stop(&m_cts_sync_timer);
	}
}

static void sync_cts_to_clock(cts_datetime_t* cts_datetime)
{
	if (cts_datetime->year + cts_datetime->day + cts_datetime->hours
	    + cts_datetime->minutes + cts_datetime->seconds == 0) {
		LOG_WRN("Ignoring suspicious time data from companion application.");
		return;
	}

	LOG_INF("CTS sync to clock started.\n Y%04d D%03d T%2d:%2d:%2d",
		cts_datetime->year, cts_datetime->day,
		cts_datetime->hours, cts_datetime->minutes, cts_datetime->seconds);

	memcpy(&clock_datetime, cts_datetime, sizeof(clock_datetime));
	clock_sync_time(cts_datetime);
	LOG_INF("CTS sync to clock complete.");
}

void cts_update_datetime(struct tm *t)
{
	t->tm_year = clock_datetime.year -1900;
	t->tm_mon = clock_datetime.month -1;
	t->tm_mday = clock_datetime.day;
	t->tm_hour = clock_datetime.hours;
	t->tm_min = clock_datetime.minutes;
	t->tm_sec = clock_datetime.seconds;
}

static void cts_sync_timer_timeout_handler(struct k_timer *tmr)
{
	bt_conn_foreach(BT_CONN_TYPE_LE, cts_sync_processor, NULL);
}

uint8_t cts_sync_read(struct bt_conn *conn, uint8_t err,
				    struct bt_gatt_read_params *params,
				    //const void *data, u16_t length)
				    const void *data, uint16_t length)
{
	LOG_DBG("Reading CCC data: err %d, %d bytes, offset %d.", err, length, m_read_buf.offset);

	if (!data || length <= 0) {
		sync_cts_to_clock(&m_read_buf.datetime);
		return BT_GATT_ITER_STOP;
	}

	memcpy(&m_read_buf.datetime + m_read_buf.offset, data, length);
	m_read_buf.offset += length;

	return BT_GATT_ITER_CONTINUE;
}

uint8_t cts_sync_service_discovered(struct bt_conn* conn, const struct bt_gatt_attr* attr,
        struct bt_gatt_discover_params* params)
{
	if (!attr) {
		LOG_INF("CTS Service Discovery completed");
		return BT_GATT_ITER_STOP;
	}
	LOG_DBG("Discovered attribute, handle: %u", attr->handle);

	memset(&read_params, 0, sizeof(read_params));
	read_params.func = cts_sync_read;
	read_params.by_uuid.uuid = (struct bt_uuid *) &uuid;
	read_params.by_uuid.start_handle = attr->handle;
	read_params.by_uuid.end_handle = 0xffff;
	m_read_buf.offset = 0;
	if (bt_gatt_read(conn, &read_params) < 0) {
		LOG_DBG("Could not initiate read of CCC data.");
	}

	return BT_GATT_ITER_STOP;
}

static void cts_sync_processor(struct bt_conn *conn, void *data)
{
	memcpy(&uuid, BT_UUID_CTS_CURRENT_TIME, sizeof(uuid));
	cts_discovery_params.func = cts_sync_service_discovered;
	cts_discovery_params.start_handle = 0x0001;
	cts_discovery_params.end_handle = 0xFFFF;
	cts_discovery_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
	cts_discovery_params.uuid = (struct bt_uuid *) &uuid;

	if (bt_gatt_discover(conn, &cts_discovery_params) != 0) {
		LOG_ERR("CTS Sync > GATT discovery FAILED.");
	}
}

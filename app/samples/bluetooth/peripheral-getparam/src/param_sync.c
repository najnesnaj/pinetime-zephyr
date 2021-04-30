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
#include <stdio.h>
#include <time.h>
//#include "log.h"
#include <logging/log.h>
LOG_MODULE_REGISTER(sync);

//LOG_MODULE_DECLARE(sync, LOG_LEVEL_INF);
#include "param_sync.h"
//#include "clock.h"

/* ********** Definitions ********** */
//#define PARAM_SYNC_INTERVAL K_SECONDS(60)
#define PARAM_SYNC_INTERVAL K_SECONDS(60)

/* ********** Function prototypes ********** */
static void param_sync_timer_timeout_handler(struct k_timer *);
static void param_sync_processor(struct bt_conn *, void *);

/* ********** Variables ********** */
static struct k_timer m_param_sync_timer;
static struct bt_gatt_discover_params param_discovery_params;
static struct bt_uuid_16 uuid = BT_UUID_INIT_16(0);
static struct bt_gatt_read_params read_params;

bool param_read=false;
uint8_t paramdata[10];

bool get_param(uint8_t *elementary)
{
	if (param_read == true)
//		elementary=&paramdata;
	memcpy(elementary, paramdata, 10);
	return(param_read);
}


/* ********** Functions ********** */
void param_sync_init()
{
	LOG_INF("PARAM sync init\n");
	k_timer_init(&m_param_sync_timer, param_sync_timer_timeout_handler, NULL);
}

void param_sync_enable(bool enable)
{
	if (enable) {
		k_timer_start(&m_param_sync_timer, K_NO_WAIT, PARAM_SYNC_INTERVAL);
	} else {
		k_timer_stop(&m_param_sync_timer);
	}
}

static void param_sync_timer_timeout_handler(struct k_timer *tmr)
{
	LOG_INF("PARAM sync timer timeout handler");
	bt_conn_foreach(BT_CONN_TYPE_LE, param_sync_processor, NULL);
}

uint8_t param_sync_read(struct bt_conn *conn, uint8_t err,
		struct bt_gatt_read_params *params,
		//const void *data, u16_t length)
		const void *data, uint16_t length)
{
	LOG_INF("sync read lenght %d ",length);
	if (!data || length <= 0) {
		LOG_INF("oops  ");
		return BT_GATT_ITER_STOP;
	}
	param_read=true;
	memcpy(&paramdata[0], data, 10);
	for (int i=0; i<10; i++)
		LOG_INF("data field %d sync_read %d",i , paramdata[i]); 
		//this should give 10 bytes of usefull data to the watch


		return BT_GATT_ITER_STOP; //stop bluetooth transfer
//	return BT_GATT_ITER_CONTINUE;
}

uint8_t param_sync_service_discovered(struct bt_conn* conn, const struct bt_gatt_attr* attr,
		struct bt_gatt_discover_params* params)
{
	if (!attr) {
		LOG_INF("PARAM Service Discovery completed");
		return BT_GATT_ITER_STOP;
	}
	LOG_DBG("Discovered attribute, handle: %u", attr->handle);
	LOG_INF("discovered attribute\n");
	memset(&read_params, 0, sizeof(read_params));
	read_params.func = param_sync_read;
	read_params.by_uuid.uuid = (struct bt_uuid *) &uuid;
	read_params.by_uuid.start_handle = attr->handle;
	read_params.by_uuid.end_handle = 0xffff;
	if (bt_gatt_read(conn, &read_params) < 0) {
		//LOG_DBG("Could not initiate read of CCC data.");
		LOG_INF("problem reading");
	}

	return BT_GATT_ITER_STOP;
}

static void param_sync_processor(struct bt_conn *conn, void *data)
{
	memcpy(&uuid, BT_UUID_BAS_BATTERY_LEVEL, sizeof(uuid));  //use battery service of host to transfer param to watch
	param_discovery_params.func = param_sync_service_discovered;
	param_discovery_params.start_handle = 0x0001;
	param_discovery_params.end_handle = 0xFFFF;
	param_discovery_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
	param_discovery_params.uuid = (struct bt_uuid *) &uuid;

	if (bt_gatt_discover(conn, &param_discovery_params) != 0) {
		LOG_INF("BAT Sync > GATT discovery FAILED.");
	}
}

/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/printk.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <settings/settings.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#include "cts_sync.h"



//struct time* clock_get_datetime();
/*

   static const struct bt_data ad[] = {
   BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
   BT_DATA_BYTES(BT_DATA_UUID16_ALL,
   0x0d, 0x18, 0x0f, 0x18, 0x05, 0x18),
   BT_DATA_BYTES(BT_DATA_UUID128_ALL,
   0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
   0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12),
   };
   */
static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, 0xaa, 0xfe),
	BT_DATA_BYTES(BT_DATA_SVC_DATA16,
			0xaa, 0xfe, /* Eddystone UUID */
			0x10, /* Eddystone-URL frame type */
			0x00, /* Calibrated Tx power at 0m */
			0x00, /* URL Scheme Prefix http://www. */
			'P', 'i', 'n', 'e', 'T', 'i',
			'm', 'e', '-', '2', '0', '2', '0',
			0x08) /* .org */
};

static void bt_ready(void)
{
	int err;

	printk("Bluetooth initialized\n");


	if (IS_ENABLED(CONFIG_SETTINGS)) {
		settings_load();
	}
	printk("bt_le_adv_start\n");
	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}



void main(void)
{
	cts_datetime_t internal_datetime;
	int err;

	//bt_ctlr_set_public_addr(addr);
	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	//todo is this necessary ?
	bt_ready();
	//bt_enable(bt_ready) should work ...
	//	bt_conn_cb_register(&conn_callbacks);
	//	bt_conn_auth_cb_register(&auth_cb_display);
	cts_sync_init(); 


	while (1) {
		k_sleep(MSEC_PER_SEC);
		cts_sync_loop();

	}
}

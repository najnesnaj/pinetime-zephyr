/* main.c - Application main entry point */

/*
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) 2021 najnesnaj@yahoo.com 

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
#include <bluetooth/services/bas.h>
#include <bluetooth/services/hrs.h>
#include "param_sync.h"

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
			BT_UUID_16_ENCODE(BT_UUID_HRS_VAL),
			BT_UUID_16_ENCODE(BT_UUID_BAS_VAL),
			BT_UUID_16_ENCODE(BT_UUID_CTS_VAL)),
	BT_DATA_BYTES(BT_DATA_UUID128_ALL,
			0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
			0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12),
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err 0x%02x)\n", err);
	} else {
		printk("Connected\n");
		param_sync_enable(true); //enable reading of variables from gatt server
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
        uint8_t param_value[10] ;
	
	printk("Disconnected (reason 0x%02x)\n", reason);
	param_sync_enable(false);
	if (get_param(param_value) ==true) {
		printk("got update\n");
		for (int i=0; i<10; i++)
		printk("number %d value %d\n", i, param_value[i]);
	}
}

static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
};

static void bt_ready(void)
{
	int err;

	printk("Bluetooth initialized\n");


	if (IS_ENABLED(CONFIG_SETTINGS)) {
		settings_load();
	}

	err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
	if (err) {
		printk("Advertising failed to start (err %d)\n", err);
		return;
	}

	printk("Advertising successfully started\n");
}


void main(void)
{
	int err;
        int teller=0;
	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return;
	}

	bt_ready();

	bt_conn_cb_register(&conn_callbacks);


        param_sync_init();

	/* 
	 * a bluetooth gatt server needs to be in place
	 param_sync will search for battery service and read 10 values
	 once disconnected those 10 values will be displayed in the main program
	 */
	while (1) {
		k_sleep(K_SECONDS(1));

	}
}

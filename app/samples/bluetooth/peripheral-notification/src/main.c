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

/* Custom Service Variables */
static struct bt_uuid_128 vnd_uuid = BT_UUID_INIT_128(
		0xf0, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
		0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 vnd_enc_uuid = BT_UUID_INIT_128(
		0xf1, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
		0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static struct bt_uuid_128 vnd_auth_uuid = BT_UUID_INIT_128(
		0xf2, 0xde, 0xbc, 0x9a, 0x78, 0x56, 0x34, 0x12,
		0x78, 0x56, 0x34, 0x12, 0x78, 0x56, 0x34, 0x12);

static uint8_t vnd_value[] = { 'V', 'e', 'n', 'd', 'o', 'r' };

static ssize_t read_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr,
		void *buf, uint16_t len, uint16_t offset)
{
	const char *value = attr->user_data;

	return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
			strlen(value));
}

static ssize_t write_vnd(struct bt_conn *conn, const struct bt_gatt_attr *attr,
		const void *buf, uint16_t len, uint16_t offset,
		uint8_t flags)
{
	uint8_t *value = attr->user_data;

	if (offset + len > sizeof(vnd_value)) {
		return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
	}

	memcpy(value + offset, buf, len);

	return len;
}

static uint8_t simulate_vnd;

static void vnd_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{
	simulate_vnd = (value == BT_GATT_CCC_INDICATE) ? 1 : 0;
}
/* Vendor Primary Service Declaration */
BT_GATT_SERVICE_DEFINE(vnd_svc,
		BT_GATT_PRIMARY_SERVICE(&vnd_uuid),
		BT_GATT_CHARACTERISTIC(&vnd_enc_uuid.uuid, BT_GATT_CHRC_NOTIFY,
			BT_GATT_PERM_NONE, NULL, NULL, NULL),

		BT_GATT_CCC(vnd_ccc_cfg_changed,
			BT_GATT_PERM_READ | BT_GATT_PERM_WRITE_ENCRYPT),
		BT_GATT_CHARACTERISTIC(&vnd_auth_uuid.uuid,
			BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
			BT_GATT_PERM_READ_AUTHEN |
			BT_GATT_PERM_WRITE_AUTHEN,
			read_vnd, write_vnd, vnd_value),
		);

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		printk("Connection failed (err 0x%02x)\n", err);
	} else {
		printk("Connected\n");
		//cts_sync_enable(true); //only if testing cts
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printk("Disconnected (reason 0x%02x)\n", reason);
	//cts_sync_enable(false);
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

int bt_vendor_notify(uint16_t sequence, uint16_t heartrate)
{
	int rc;
	static uint8_t hrm[2];

	hrm[0] = sequence; /* value to describe the order, in case something gets lost */
	hrm[1] = heartrate; /* this is the real parameter value */

	rc = bt_gatt_notify(NULL, &vnd_svc.attrs[1], &hrm, sizeof(hrm));

	return rc == -ENOTCONN ? 0 : rc;
}

static void param_notify(int nummer)
{
	// instead of 240-nummer a measurement value can be used
	bt_vendor_notify(nummer,240-nummer);

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



	/* Implement notification
	 */
	while (1) {
		teller++;
		if (teller > 240) teller=0;
		param_notify(teller);
		k_sleep(K_SECONDS(1));
	}
}

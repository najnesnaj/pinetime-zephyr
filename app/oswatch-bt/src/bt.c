/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 * Copyright (c) 2015-2016 Intel Corporation
 * Copyright (c) 2020 Endian Technologies AB
 * Copyright (c) 2020 max00
 * Copyright (c) 2020 Prevas A/S
 * Copyright (c) 2021 najnesnaj@yahoo.com 
 * 
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/types.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <sys/byteorder.h>
#include <zephyr.h>

#include <settings/settings.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>

#ifdef CONFIG_MCUMGR
#include <mgmt/smp_bt.h>
#endif

#include "log.h"
#include "version.h"
#include "display.h"
/* ********** Function prototypes ********** */
static void connected(struct bt_conn *conn, uint8_t err);
static void disconnected(struct bt_conn *conn, uint8_t reason);
static bool le_param_req(struct bt_conn *conn, struct bt_le_conn_param *param);
static void le_param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency, uint16_t timeout);

/* ********** Variables ********** */

static struct k_work advertise_work;

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	/* Device information */
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
		      0x0a, 0x18),
	/* Current time */
	BT_DATA_BYTES(BT_DATA_UUID16_ALL,
		      0x05, 0x18),
#ifdef CONFIG_MCUMGR
	/* SMP */
	BT_DATA_BYTES(BT_DATA_UUID128_ALL,
		      0x84, 0xaa, 0x60, 0x74, 0x52, 0x8a, 0x8b, 0x86,
		      0xd3, 0x4c, 0xb7, 0x1d, 0x1d, 0xdc, 0x53, 0x8d),
#endif
};

static struct bt_conn_cb m_conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
	.le_param_req = le_param_req,
	.le_param_updated = le_param_updated
};

static struct bt_le_adv_param param = BT_LE_ADV_PARAM_INIT(
	BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_USE_NAME,
	BT_GAP_ADV_SLOW_INT_MIN,
	BT_GAP_ADV_SLOW_INT_MAX,
	NULL
);

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

static uint8_t vnd_value[] = { 'O', 'S', 'w', 'a', 't', 'c', 'h' };


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

#define MAX_DATA 74
static uint8_t vnd_long_value[] = {
                  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '1',
                  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '2',
                  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '3',
                  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '4',
                  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '5',
                  'V', 'e', 'n', 'd', 'o', 'r', ' ', 'd', 'a', 't', 'a', '6',
                  '.', ' ' };

static ssize_t read_long_vnd(struct bt_conn *conn,
                             const struct bt_gatt_attr *attr, void *buf,
                             uint16_t len, uint16_t offset)
{
        const char *value = attr->user_data;

        return bt_gatt_attr_read(conn, attr, buf, len, offset, value,
                                 sizeof(vnd_long_value));
}

static ssize_t write_long_vnd(struct bt_conn *conn,
                              const struct bt_gatt_attr *attr, const void *buf,
                              uint16_t len, uint16_t offset, uint8_t flags)
{
        uint8_t *value = attr->user_data;

        if (flags & BT_GATT_WRITE_FLAG_PREPARE) {
                return 0;
        }

        if (offset + len > sizeof(vnd_long_value)) {
                return BT_GATT_ERR(BT_ATT_ERR_INVALID_OFFSET);
        }

        memcpy(value + offset, buf, len);

        return len;
}










/* ********** Functions ********** */
static int settings_runtime_load(void)
{
	/*
#if defined(CONFIG_BOARD_PINETIME)
	settings_runtime_set("bt/dis/model",
			     "PineTime",
			     sizeof("PineTime"));
	settings_runtime_set("bt/dis/manuf",
			     "PINE64",
			     sizeof("PINE64"));
	settings_runtime_set("bt/dis/hw",
			     "1.0a",
			     sizeof("1.0a"));
#endif
#if defined(CONFIG_BOARD_P8)
	settings_runtime_set("bt/dis/model",
			     "P8",
			     sizeof("P8"));
	settings_runtime_set("bt/dis/manuf",
			     "Colmi",
			     sizeof("Colmi"));
#endif
#if defined(CONFIG_BOARD_DS_D6)
	settings_runtime_set("bt/dis/model",
			     "ds_d6",
			     sizeof("ds_d6"));
	settings_runtime_set("bt/dis/manuf",
			     "Desay",
			     sizeof("desay"));
#endif
#if defined(CONFIG_BOARD_NATIVE_POSIX_64)
	settings_runtime_set("bt/dis/model",
			     "posix_64",
			     sizeof("posix_64"));
	settings_runtime_set("bt/dis/manuf",
			     "Native",
			     sizeof("Native"));
#endif
	*/
	settings_runtime_set("bt/dis/sw",
			     CONFIG_BT_DEVICE_NAME,
			     sizeof(CONFIG_BT_DEVICE_NAME));
	settings_runtime_set("bt/dis/fw",
			     FW_VERSION,
			     sizeof(FW_VERSION));
	return 0;
}

static void advertise(struct k_work *work)
{
	int rc;

	bt_le_adv_stop();

	rc = bt_le_adv_start(&param, ad, ARRAY_SIZE(ad), NULL, 0);
	if (rc) {
		LOG_ERR("Advertising failed to start (rc %d)", rc);
		return;
	}

	LOG_INF("Advertising successfully started");
}

/* Vendor Primary Service Declaration */
BT_GATT_SERVICE_DEFINE(vnd_svc,
        BT_GATT_PRIMARY_SERVICE(&vnd_uuid),
        BT_GATT_CHARACTERISTIC(&vnd_enc_uuid.uuid,
                               BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE |
                               BT_GATT_CHRC_INDICATE,
                               BT_GATT_PERM_READ_ENCRYPT |
                               BT_GATT_PERM_WRITE_ENCRYPT,
                               read_vnd, write_vnd, vnd_value),
        BT_GATT_CCC(vnd_ccc_cfg_changed,
                    BT_GATT_PERM_READ | BT_GATT_PERM_WRITE_ENCRYPT),
        BT_GATT_CHARACTERISTIC(&vnd_auth_uuid.uuid,
                               BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
                               BT_GATT_PERM_READ_AUTHEN |
                               BT_GATT_PERM_WRITE_AUTHEN,
                               read_vnd, write_vnd, vnd_value),
        BT_GATT_CHARACTERISTIC(&vnd_long_uuid.uuid, BT_GATT_CHRC_READ |
                               BT_GATT_CHRC_WRITE | BT_GATT_CHRC_EXT_PROP,
                               BT_GATT_PERM_READ | BT_GATT_PERM_WRITE |
                               BT_GATT_PERM_PREPARE_WRITE,
                               read_long_vnd, write_long_vnd, &vnd_long_value),
        BT_GATT_CEP(&vnd_long_cep),
        BT_GATT_CHARACTERISTIC(&vnd_signed_uuid.uuid, BT_GATT_CHRC_READ |
                               BT_GATT_CHRC_WRITE | BT_GATT_CHRC_AUTH,
                               BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                               read_signed, write_signed, &signed_value),
        BT_GATT_CHARACTERISTIC(&vnd_write_cmd_uuid.uuid,
                               BT_GATT_CHRC_WRITE_WITHOUT_RESP,
                               BT_GATT_PERM_WRITE, NULL,
                               write_without_rsp_vnd, &vnd_value),
);









static void connected(struct bt_conn *conn, uint8_t err)
{
	printk("test\n");
	if (err) {
		return;
	}
	LOG_INF("connected");
	display_connect_event();
	//delay of some sort    todo jj
	//clock_show_time();
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	LOG_INF("disconnected (reason: %u)", reason);
	display_disconnect_event(); //shows first screen
	//display_set_bluetooth_disconnected(); //bt-symbol is displayed -- readability is not top...
	//gfx_bt_set_label(BT_ADVERTISING_ON);
	//gfx_update();
}

static bool le_param_req(struct bt_conn *conn, struct bt_le_conn_param *param)
{
	return true;
}

static void le_param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency, uint16_t timeout)
{

}

void bt_init(void)
{
	int err = bt_enable(NULL);
	if (err) {
		LOG_ERR("Bluetooth init failed (err %d)", err);
		return;
	}

	settings_load();
	settings_runtime_load();

	k_work_init(&advertise_work, advertise);
	bt_conn_cb_register(&m_conn_callbacks);
		LOG_INF("bt init callback started\n");

	k_work_submit(&advertise_work);
#ifdef CONFIG_MCUMGR
	/* Initialize the Bluetooth mcumgr transport. */
	smp_bt_register();
#endif

	LOG_INF("Bluetooth initialized"); //jj
	LOG_DBG("Bluetooth initialized");
}

void bt_adv_stop(void)
{
	k_sleep(K_MSEC(400));

	int err = bt_le_adv_stop();
	if (err) {
		LOG_ERR("Advertising failed to stop (err %d)", err);
		return;
	}
}

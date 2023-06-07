/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

/** @file
 *  @brief Nordic UART Bridge Service (NUS) sample
 */

#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/hci.h>
#include <bluetooth/services/nus.h>
#include <zephyr/logging/log.h>
#include <shell/shell_bt_nus.h>
#include <stdio.h>

// add display part
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>

//LV_IMG_DECLARE(flater);
//LV_IMG_DECLARE(beavis);


// TODO this is backlighting mid, might be necessary to set to led2 = high
// #define LED0_NODE DT_ALIAS(led1)

#if DT_NODE_EXISTS(DT_ALIAS(led0))
#define LED0 DT_ALIAS(led0)
#elif DT_NODE_EXISTS(DT_NODELABEL(led0))
#define LED0 DT_NODELABEL(led0)
#else
#define LED0 DT_INVALID_NODE
#endif

#if DT_NODE_EXISTS(DT_ALIAS(led2))
#define LED2 DT_ALIAS(led2)
#endif

#if DT_NODE_EXISTS(LED0)
#define LED0_DEV   DT_PHANDLE(LED0, gpios)
#define LED0_PIN   DT_PHA(LED0, gpios, pin)
#define LED0_FLAGS DT_PHA(LED0, gpios, flags)
#else
#define LED0 DT_INVALID_NODE
#endif

#if DT_NODE_EXISTS(LED2)
#define LED2_DEV   DT_PHANDLE(LED2, gpios)
#define LED2_PIN   DT_PHA(LED2, gpios, pin)
#define LED2_FLAGS DT_PHA(LED0, gpios, flags)
#else
#define LED2 DT_INVALID_NODE
#endif







static void backlight_switch(bool enable)
{

	const struct device *dev;

	// dev = device_get_binding(LED0);
	// dev = DEVICE_DT_GET(LED0_DEV);
	dev = DEVICE_DT_GET(LED2_DEV);
	// dev = device_get_binding(LED0);
	 
	gpio_pin_configure(dev, LED2_PIN, GPIO_OUTPUT_ACTIVE | LED2_FLAGS);
	//   gpio_pin_configure(dev, LED, GPIO_DIR_OUT);
	if (enable == true) {
		gpio_pin_set(dev, LED2_PIN, 1);
	} else {
		gpio_pin_set(dev, LED2_PIN, 0);
	}
	// gpio_pin_write(dev, LED, 0);
}



//static lv_obj_t *img_logo;

LOG_MODULE_REGISTER(app);

#define DEVICE_NAME	CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

static struct bt_conn *current_conn;

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static const struct bt_data sd[] = {
	BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_NUS_VAL),
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	if (err) {
		LOG_ERR("Connection failed (err %u)", err);
		return;
	}

	LOG_INF("Connected");
	current_conn = bt_conn_ref(conn);
	shell_bt_nus_enable(conn);
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	LOG_INF("Disconnected (reason %u)", reason);

	shell_bt_nus_disable();
	if (current_conn) {
		bt_conn_unref(current_conn);
		current_conn = NULL;
	}
}

static char *log_addr(struct bt_conn *conn)
{
	static char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	return addr;
}

static void __attribute__((unused))
security_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err)
{
	char *addr = log_addr(conn);

	if (!err) {
		LOG_INF("Security changed: %s level %u", addr, level);
	} else {
		LOG_INF("Security failed: %s level %u err %d", addr, level, err);
	}
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
	COND_CODE_1(CONFIG_BT_SMP, (.security_changed = security_changed), ())};

static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
	LOG_INF("Passkey for %s: %06u", log_addr(conn), passkey);
}

static void auth_cancel(struct bt_conn *conn)
{
	LOG_INF("Pairing cancelled: %s", log_addr(conn));
}

static void pairing_complete(struct bt_conn *conn, bool bonded)
{
	LOG_INF("Pairing completed: %s, bonded: %d", log_addr(conn), bonded);
}

static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
	LOG_INF("Pairing failed conn: %s, reason %d", log_addr(conn), reason);
}

static struct bt_conn_auth_cb conn_auth_callbacks = {
	.passkey_display = auth_passkey_display,
	.cancel = auth_cancel,
};

static struct bt_conn_auth_info_cb conn_auth_info_callbacks = {.pairing_complete = pairing_complete,
							       .pairing_failed = pairing_failed};

int main(void)
{
	int err;
    static lv_obj_t   *button_obj;
	static lv_obj_t   *screen0_label0_obj;
lv_obj_t *hello_world_label;
lv_obj_t *count_label;
	const struct device *display_dev;
	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting test");
		return 0;
	}
	else printf("display OK\n");

#if defined(CONFIG_BOARD_PINETIME_DEVKIT0)
	backlight_switch(true);
	printf("backlight OK\n");
#endif

	//img_logo = lv_img_create(lv_scr_act());
	//lv_img_set_src(img_logo, &flater);
	//lv_img_set_src(img_logo, &beavis);
	//lv_obj_center(img_logo);
	//lv_task_handler();
	hello_world_label = lv_label_create(lv_scr_act());

	printk("Set up label\n");
     lv_label_set_text(hello_world_label, "Hello world!");
	lv_obj_align(hello_world_label, LV_ALIGN_CENTER, 0, 0);
   
	count_label = lv_label_create(lv_scr_act());
	lv_obj_align(count_label, LV_ALIGN_BOTTOM_MID, 0, 0);
 printk("start handler\n");
	//lv_task_handler();
	 printk("handler not for testing memory issues started\n");
	display_blanking_off(display_dev);



	 
/*
	printk("Starting Bluetooth NUS shell transport example\n");

	if (IS_ENABLED(CONFIG_BT_SMP)) {
		err = bt_conn_auth_cb_register(&conn_auth_callbacks);
		if (err) {
			printk("Failed to register authorization callbacks.\n");
			return 0;
		}

		err = bt_conn_auth_info_cb_register(&conn_auth_info_callbacks);
		if (err) {
			printk("Failed to register authorization info callbacks.\n");
			return 0;
		}
	}

	err = bt_enable(NULL);
	if (err) {
		LOG_ERR("BLE enable failed (err: %d)", err);
		return 0;
	}

	err = shell_bt_nus_init();
	if (err) {
		LOG_ERR("Failed to initialize BT NUS shell (err: %d)", err);
		return 0;
	}

	err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)", err);
		return 0;
	}

	LOG_INF("Bluetooth ready. Advertising started.");

    err = bt_disable();
    if (err) {
        // Handle error, if any
	LOG_ERR("BLE disable failed (err: %d)", err);
    }
*/
    // Optionally, you can also release additional Bluetooth resources here

    // Example: Deinitialize the Bluetooth stack
    //bt_deinit();

printk("start handler\n");
	lv_task_handler();
	 printk("handler started\n");
	display_blanking_off(display_dev);


while (1) {
		
		printf("counted \n");
		k_sleep(K_MSEC(10));
	}
//	return 0;
}

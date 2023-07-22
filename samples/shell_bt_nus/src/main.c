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
#include <zephyr/sys/ring_buffer.h>

// #include <bluetooth/services/nus.h>
// #include <bluetooth/services/nus_client.h>

// LV_IMG_DECLARE(flater);
// LV_IMG_DECLARE(beavis);

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

#if defined(CONFIG_BOARD_PINETIME_DEVKIT0)
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
#endif

#define NUS_WRITE_TIMEOUT K_MSEC(150)
K_SEM_DEFINE(nus_write_sem, 0, 1);

/* UART payload buffer element size. */
#define UART_BUF_SIZE 20
struct uart_data_t {
	void *fifo_reserved;
	uint8_t data[UART_BUF_SIZE];
	uint16_t len;
};

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

	printf("Connected");
	current_conn = bt_conn_ref(conn);
//	shell_bt_nus_enable(conn);
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	printf("Disconnected (reason %u)", reason);

//	shell_bt_nus_disable();
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
		printf("Security changed: %s level %u", addr, level);
	} else {
		printf("Security failed: %s level %u err %d", addr, level, err);
	}
}




static void bt_receive_cb(struct bt_conn *conn, const uint8_t *const data,
              uint16_t len)
{
        int err;
        char addr[BT_ADDR_LE_STR_LEN] = {0};

        bt_addr_le_to_str(bt_conn_get_dst(conn), addr, ARRAY_SIZE(addr));

        printf("Received data from: %s", addr);

		  uint8_t buf[256] = {0};

    //todo figure out how to display 
    memcpy(buf, data, len);
	printf("len : %d\n", len);
    printf("%s\n", buf);

	printf ("%d\n", buf[2]);
printf ("%d\n", buf[3]);
printf ("%d\n", buf[4]);
printf ("%d\n", buf[5]);

//TODO
// while( bleuart.available() && bleuart.read() != '!' )  { }
//     if (bleuart.read() != 'I') return;

//     if ( !bleuart.available() ) return;

//     imageColorBit = bleuart.read8();
//     imageWidth  = bleuart.read16();
//     imageHeight = bleuart.read16();





//TODO
//
//lv_obj_t *img = lv_img_create(screen, NULL);
    
    // Set the bitmap data and size
  //  lv_img_set_src(img, myBitmap);
   // lv_img_set_size(img, width, height);
    
    // Set the position of the image on the screen
    //lv_obj_set_pos(img, x, y);

    
}
//static struct bt_nus_cb nus_cb = {
//    .received = bt_receive_cb,
//};

//struct bt_nus nus;
BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
//.received = bt_receive_cb,
	COND_CODE_1(CONFIG_BT_SMP, (.security_changed = security_changed), ())};

static void auth_passkey_display(struct bt_conn *conn, unsigned int passkey)
{
	printf("Passkey for %s: %06u", log_addr(conn), passkey);
}

static void auth_cancel(struct bt_conn *conn)
{
	printf("Pairing cancelled: %s", log_addr(conn));
}

static void pairing_complete(struct bt_conn *conn, bool bonded)
{
	printf("Pairing completed: %s, bonded: %d", log_addr(conn), bonded);
}

static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
	printf("Pairing failed conn: %s, reason %d", log_addr(conn), reason);
}

static struct bt_conn_auth_cb conn_auth_callbacks = {
	.passkey_display = auth_passkey_display,
	.cancel = auth_cancel,
};

static struct bt_conn_auth_info_cb conn_auth_info_callbacks = {.pairing_complete = pairing_complete,
							       .pairing_failed = pairing_failed};

// #define MAX_DATA_SIZE 50
// uint8_t temp_buffer[MAX_DATA_SIZE];
// size_t bytes_read = ring_buf_get(shell_transport_bt_nus_shell_bt_nus->rx_ringbuf, temp_buffer,
// sizeof(temp_buffer));

/**
 * @brief Define and initialize a ring buffer for byte data.
 *
 * This macro establishes a ring buffer of an arbitrary size.
 * The basic storage unit is a byte.
 *
 * The ring buffer can be accessed outside the module where it is defined
 * using:
 *
 * @code extern struct ring_buf <name>; @endcode
 *
 * @param name  Name of the ring buffer.
 * @param size8 Size of ring buffer (in bytes).
 */
//extern const struct shell_transport_api shell_bt_nus_transport_api;
extern struct ring_buf shell_transport_bt_nus_rx_ringbuf;
//const struct shell_bt_nus *bt_nus = shell_transport_api.ctx;
// TODO
//const struct shell_bt_nus *bt_nus = (const struct shell_bt_nus *)shell_transport_bt_nus.ctx;
//extern struct shell_transport shell_transport_bt_nus;
//extern struct shell_transport shell_transport_bt_nus;
//extern struct ring_buf shell_transport_bt_nus.rx_ringbuf;
#define MAX_DATA_SIZE 50
uint8_t temp_buffer[MAX_DATA_SIZE];
// size_t aantaaal;
//uint32_t sizer;
// ring_buf_get(shell_bt_nus_tx_ringbuf, temp_buffer, sizeof(temp_buffer));
// size_t  reet;


struct shell_transport *transport;
size_t length; 
size_t cnt;
//static struct bt_conn *current_conn;


//static struct bt_nus_cb nus_cb = {
//    .received = bt_receive_cb,
//};
//static struct bt_nus_callbacks nus_cb = {
 // .connected = my_connected,
 // .disconnected = my_disconnected,
 // .received = my_received,
//};


static struct bt_nus_cb nus_cb = {
    .received = bt_receive_cb,
};




// NUS initialization function
void nus_init()
{
	//int bt_nus_init(struct bt_nus_cb *callbacks)

    //err = bt_nus_init(&nus_cb);
    // Initialize NUS instance
    int err = bt_nus_init(&nus_cb);
    if (err)
    {
        printk("NUS initialization failed (err %d)\n", err);
        return;
    }

    printk("NUS initialized\n");
}



int main(void)
{
	int err;
	temp_buffer[0]=0;
	char count_str[11] = {0};
	int counter = 0;
	static lv_obj_t *button_obj;
	static lv_obj_t *screen0_label0_obj;
	lv_obj_t *hello_world_label;
	lv_obj_t *count_label;
	const struct device *display_dev;
	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting test");
		return 0;
	} else {
		printf("display says hello\n");
	}

#if defined(CONFIG_BOARD_PINETIME_DEVKIT0)
	backlight_switch(true);
	printf("backlight OK\n");
#endif

	// img_logo = lv_img_create(lv_scr_act());
	// lv_img_set_src(img_logo, &flater);
	// lv_img_set_src(img_logo, &beavis);
	// lv_obj_center(img_logo);
	// lv_task_handler();

	err = bt_enable(NULL);
	// err = bt_enable();
	if (err) {
		printf("BLE enable failed (err: %d)", err);
		return 0;
	}

	printf("Set up label\n");
	hello_world_label = lv_label_create(lv_scr_act());

	printf("Set up label\n");
	lv_label_set_text(hello_world_label, "Hello world!");
	lv_obj_align(hello_world_label, LV_ALIGN_CENTER, 0, 0);

	count_label = lv_label_create(lv_scr_act());
	lv_obj_align(count_label, LV_ALIGN_BOTTOM_MID, 0, 0);
	printf("start handler\n");
	lv_task_handler();
	printf("handler not for testing memory issues started\n");
	display_blanking_off(display_dev);

	printf("Bluetooth ready ");

	// printf("Starting Bluetooth NUS 2 shell transport example\n");
	// err = bt_enable(NULL);
	// printf("Starting Bluetooth NUS 3 shell transport example\n");

	if (IS_ENABLED(CONFIG_BT_SMP)) {
		printf("BT SMP enabled");
		err = bt_conn_auth_cb_register(&conn_auth_callbacks);
		if (err) {
			printf("Failed to register authorization callbacks.\n");
			return 0;
		}

		err = bt_conn_auth_info_cb_register(&conn_auth_info_callbacks);
		if (err) {
			printf("Failed to register authorization info callbacks.\n");
			return 0;
		}
	} else {
		printf("BT SMP not enabled");
	}
	printf("Bluetooth not ready yet");

	// err = shell_bt_nus_init();
	// if (err) {
	//	LOG_ERR("Failed to initialize BT NUS shell (err: %d)", err);
	//	return 0;
	// }

	err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
	if (err) {
		LOG_ERR("Advertising failed to start (err %d)", err);
		return 0;
	} else {
		printf("Nus client alive\n");
	}

	printf("Bluetooth ready. Advertising started.");

	// err = bt_disable();
	// if (err) {
	//  Handle error, if any
	// LOG_ERR("BLE disable failed (err: %d)", err);
	//}

	// Optionally, you can also release additional Bluetooth resources here

	// Example: Deinitialize the Bluetooth stack
	// bt_deinit();

	printf(" first start  handler\n");
	//	lv_task_handler();
	printf("handler started\n");
	// display_blanking_off(display_dev);
	printf("display blanked\n");
	// uint8_t read_buffer[BUFFER_SIZE];
	// size_t read_len;
	// err = nus_client_init();
	// if (err != 0) {
	//		printf("nus_client_init failed (err %d)", err);
	//		return 0;
	//	}
	//	else
	//			printf("nus_client_init OK\n" );
	//err = shell_bt_nus_init();


    // err = bt_nus_init(&nus_cb);
    // if (err) {
    //     printk("Failed to initialize Nordic UART service (err: %d)\n", err);
    //     return;
    // }
	// else
	// {
	// 	printf("nus initialized \n");
	// }
 nus_init();


	//if (err) {
//		LOG_ERR("Failed to initialize BT NUS shell (err: %d)", err);
//		return 0;
//	}

	// sizer = ring_buf_get(&shell_transport_bt_nus_rx_ringbuf, temp_buffer, 50);

	//        const struct shell_bt_nus *bt_nus =
	//                (const struct shell_bt_nus *)shell_transport_bt_nus.ctx;

	//  uint8_t data[50];
	// int num_elements;

	// num_elements = ring_buf_get_claim(bt_nus->rx_ringbuf, &data[0], sizeof(data));

	// printf (BUTT_TEST);

	while (1) {
		// read_len = ring_buf_get(&rb, read_buffer, sizeof(read_buffer));

		//		printf("lengte buffer = %ld\n", read_len);
		counter++;
		printf("counted  %d\n", counter);
		if ((counter % 100) == 0U) {
			sprintf(count_str, "%d", counter / 100U);
			lv_label_set_text(count_label, count_str);
			// err = bt_nus_client_send(&nus_client, buf->data, buf->len);
			// if (err) {
			// 	LOG_WRN("Failed to send data over BLE connection"
			// 		"(err %d)",
			// 		err);
			// }

			// err = k_sem_take(&nus_write_sem, NUS_WRITE_TIMEOUT);
			// if (err) {
			// 	LOG_WRN("NUS send timeout");
			// }
		}
		if (counter > 10000) {
			counter = 0;
		}

		
		k_sleep(K_MSEC(1000));
		lv_task_handler();
		length=50;
		//shell_bt_nus_transport_api.read(NULL,NULL,length,NULL);
		//printf("cnt %d\n", cnt);
	 //sizer = ring_buf_get(&shell_transport_bt_nus_rx_ringbuf, temp_buffer, 50);
	//printf("buffer received %d", sizer);
	 //   for (int j=0;j<50;j++) printf("--- %c\n", temp_buffer[j]);
		 
	}
	//	return 0;
}

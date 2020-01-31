#include <sys/printk.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/conn.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
//#include "log.h"
#include "cts_sync.h"
//#include "bt.h"
#include "cts.h"
#include "clock.h"

#define TIME_SYNC_WAIT 10 // TODO: tune
int time_sync_timeout = TIME_SYNC_WAIT;
static struct bt_gatt_discover_params cts_discovery_params;
static struct bt_uuid_16 uuid = BT_UUID_INIT_16(0);
static struct bt_gatt_read_params read_params;
int tijd;

int get_uur()
{
	return(tijd);
}

static void sync_cts_to_clock(cts_datetime_t* cts_datetime)
{
	printk("CTS sync to clock started.\n Y%04d D%03d T%2d:%2d:%2d",
			cts_datetime->year, cts_datetime->day,
			cts_datetime->hours, cts_datetime->minutes, cts_datetime->seconds);

	struct tm clock_datetime;
	memset(&clock_datetime, 0, sizeof(struct tm));
	//    clock_datetime.tm_year = cts_datetime->year;
	//    clock_datetime.tm_mon = cts_datetime->month;
	//    clock_datetime.tm_mday = cts_datetime->day;
	//clock_datetime.tm_hour = cts_datetime->hours;
	//tijd = cts_datetime->minutes;
	tijd = 32;
	//clock_datetime.tm_min = cts_datetime->minutes;
	//minuten = cts_datetime->minutes;
	//clock_datetime.tm_sec = cts_datetime->seconds;
	// seconden = cts_datetime->seconds;

	//clock_set_datetime(&clock_datetime);

	printk("CTS sync to clock complete.");

	time_sync_timeout = TIME_SYNC_WAIT;
}

static void sync_local_cts_to_clock()
{
	//cts_datetime_t cts_datetime;
	//cts_get_datetime(&cts_datetime);
	//sync_cts_to_clock(&cts_datetime);
}

static void cts_write_cb(int val)
{
	sync_local_cts_to_clock();
}

int offset = 0;
cts_datetime_t datetime_buf;
u8_t cts_sync_read(struct bt_conn *conn, u8_t err,
		struct bt_gatt_read_params *params,
		const void *data, u16_t length)
{
	printk("Reading CCC data: err %d, %d bytes, offset %d.", err, length, offset);

	if (!data || length <= 0) {
		sync_cts_to_clock(&datetime_buf);
		printk("BT_GATT_ITER_STOP\n");
		return BT_GATT_ITER_STOP;
	}

	//   memcpy(&datetime_buf + offset, data, length);
	offset += length;
	printk("BT_GATT_ITER_CONTINUE\n");

	return BT_GATT_ITER_CONTINUE;
}

u8_t cts_sync_service_discovered(struct bt_conn* conn, const struct bt_gatt_attr* attr,
		struct bt_gatt_discover_params* params)
{
	if (!attr) {
		printk("CTS Service Discovery completed");
		return BT_GATT_ITER_STOP;
	}
	printk("Discovered attribute, handle: %u\n", attr->handle);

	memset(&read_params, 0, sizeof(read_params));
	read_params.func = cts_sync_read;
	read_params.by_uuid.uuid = &uuid;
	read_params.by_uuid.start_handle = attr->handle;
	read_params.by_uuid.end_handle = 0xffff;
	offset = 0;
	if (bt_gatt_read(conn, &read_params) < 0) {
		printk("Could not initiate read of CCC data.");
	}

	return BT_GATT_ITER_STOP;
}

static void cts_sync_processor(struct bt_conn *conn, void *data)
{

	//#define BT_UUID_CTS                       BT_UUID_DECLARE_16(0x1805)
	//#define BT_UUID_CTS_CURRENT_TIME          BT_UUID_DECLARE_16(0x2a2b)
		printk("cts_sync_processor \n");
	memcpy(&uuid, BT_UUID_CTS_CURRENT_TIME, sizeof(uuid));
	cts_discovery_params.func = cts_sync_service_discovered;
	cts_discovery_params.start_handle = 0x0001;
	cts_discovery_params.end_handle = 0xFFFF;
	cts_discovery_params.type = BT_GATT_DISCOVER_CHARACTERISTIC;
	cts_discovery_params.uuid = &uuid;

	if (bt_gatt_discover(conn, &cts_discovery_params) != 0) {
		printk("CTS Sync > GATT discovery FAILED.\n");
	}
	else
		printk("CTS Sync  GATT discovery succeeded\n");
}

static void connected(struct bt_conn *conn, u8_t err)
{
	if (err) {
		return;
	}
	cts_sync_processor(conn, NULL);
}

static void disconnected(struct bt_conn *conn, u8_t reason)
{
}

static struct bt_conn_cb conn_callbacks = {
	.connected = connected,
	.disconnected = disconnected,
};

void cts_sync_init()
{
	printk("cts_sync_init \n");
	bt_conn_cb_register(&conn_callbacks);
	//cts_register_write_cb(cts_write_cb); //todo
	//    sync_local_cts_to_clock();
		printk("cts_sync_init finished\n");
}

void cts_sync_loop()
{
	if (time_sync_timeout > 0) {
		time_sync_timeout--;
		printk("time_sync_timeout-- \n");
	} else {
		printk("bt_conn_foreach \n");
		bt_conn_foreach(BT_CONN_TYPE_ALL, cts_sync_processor, NULL);
		time_sync_timeout = TIME_SYNC_WAIT;
	}
}

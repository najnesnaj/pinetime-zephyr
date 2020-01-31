/*
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/* measure battery power on pin 31 of the Pinetime
 */

#include <zephyr.h>
#include <battery.h>

void main(void)
{
	int err;

	err = battery_init(NULL);
	if (err < 0) {
		printk("init failed (%d)\n", err);
		return;
	}

	k_sleep(K_FOREVER);
}

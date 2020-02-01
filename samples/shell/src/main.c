/*
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <battery.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(app);

void main(void)
{
	int err;

	if (IS_ENABLED(CONFIG_BATTERY)){
		err = battery_init(NULL);
		if (err < 0) {
			LOG_ERR("init failed (%d)", err);
			return;
		}
	}
}

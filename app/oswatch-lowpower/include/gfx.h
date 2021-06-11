/*
 * Copyright (c) 2020 Endian Technologies AB
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GFX__H
#define GFX__H

enum bt_symbol {
	BT_CONNECTED,
	BT_ADVERTISING_ON,
	BT_ADVERTISING_OFF,
};

enum battery_symbol {
	BAT_CHARGE,
	BAT_FULL,
	BAT_3,
	BAT_2,
	BAT_1,
	BAT_EMPTY
};

void gfx_init(void);
void gfx_battery_set_label(enum battery_symbol);
void gfx_bt_set_label(enum bt_symbol);
void gfx_time_set_label(char *);
void gfx_date_set_label(char *);
void gfx_update(void);
void gfx_show_info(void);
void gfx_show_watch(void);

#endif /* GFX__H */

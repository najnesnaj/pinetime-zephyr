/*
 * Copyright (c) 2020 Endian Technologies AB
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BATTERY__H
#define BATTERY__H

void battery_init();
void battery_update_percentage();
void battery_update_charging_status(bool);
bool battery_get_charging_status();
uint32_t battery_raw_to_mv(int16_t raw);
uint32_t battery_mv_to_ppt(uint32_t mv);
void battery_show_status();
void battery_gfx_init();

#endif /* BATTERY__H */

/*
 * Copyright (c) 2021 Jan Jansen 
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef EVENT_HANDLER__H
#define EVENT_HANDLER__H

#include <drivers/gpio.h>
#include <drivers/sensor.h>
#include <lvgl.h>

void event_handler_init(void);
void display_off_isr(struct k_timer *);
#ifdef CONFIG_BOOTLOADER_MCUBOOT
void watchdog_refresh_isr(struct k_timer *);
#endif
void battery_percentage_isr(struct k_timer *);
void battery_charging_isr(const struct device*, struct gpio_callback *, uint32_t);
void button_pressed_isr(const struct device *, struct gpio_callback *, uint32_t);
int handle_button_event(void);
void handle_clock_update(struct k_timer *); //jj struct k_timer *clock_update
void button_event_cb(lv_obj_t * , lv_event_t );
//void button_event_cb(void);
void low_power_off();
//#if defined(CONFIG_BOARD_DS_D6)  //this watch has a button on the front (touch sensitive)
void init_button(void);
//#endif
#endif /* EVENT_HANDLER */

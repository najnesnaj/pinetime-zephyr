/*
 *   display.h
 */
#ifndef __DISPLAY_H
#define __DISPLAY_H
#include "buttons.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
int  display_init(void);
void display_time_set_label(char *str);
void display_date_set_label(char *str);
void display_btn_event(buttons_id_t btn_id);
void display_sleep();
void display_clock_update();
//void backlight_switch(bool)
#endif  /* __DISPLAY_H */

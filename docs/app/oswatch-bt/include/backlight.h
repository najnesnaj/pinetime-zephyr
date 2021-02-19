/*
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BACKLIGHT__H
#define BACKLIGHT__H

#include <stdbool.h>

void backlight_init(void);
void backlight_enable(bool);
bool backlight_is_enabled(void);

#endif /* BACKLIGHT__H */

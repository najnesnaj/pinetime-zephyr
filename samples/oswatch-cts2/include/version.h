/*
 * Copyright (c) 2020 Endian Technologies AB
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef VERSION__H
#define VERSION__H

/* Stringify firmware build data included by cmake */
#define _xstr(s) _str(s)
#define _str(s) #s
#define TIME_OF_BUILD _xstr(CURRENT_TIME_OF_BUILD)
#define FW_VERSION _xstr(FW_BUILD)

#endif /* VERSION__H */

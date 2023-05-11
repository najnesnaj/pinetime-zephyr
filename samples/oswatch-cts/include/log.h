/*
 * Copyright (c) 2020 Endian Technologies AB
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LOGGING__H
#define LOGGING__H
//#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL

#include <zephyr/logging/log.h>
//LOG_MODULE_REGISTER(spampy);

LOG_MODULE_DECLARE(app, LOG_LEVEL_INF);
//LOG_MODULE_DECLARE(hypnos, LOG_LEVEL_INF);

#endif /* LOGGING__H */

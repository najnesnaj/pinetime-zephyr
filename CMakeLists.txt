#
# Copyright (c) 2018 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

# Point to NCS root directory.
set(PINETIME_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "Pinetime root directory")

zephyr_include_directories(include)

add_subdirectory(drivers/sensor)

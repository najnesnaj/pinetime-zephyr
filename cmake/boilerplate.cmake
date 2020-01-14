#
# Copyright (c) 2018 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
#

# Point to NCS root directory.
set(PINETIME_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

if(NOT BOARD)
        set(BOARD $ENV{BOARD})
endif()

# Check if selected board is supported.
if(DEFINED NRF_SUPPORTED_BOARDS)
        if(NOT BOARD IN_LIST NRF_SUPPORTED_BOARDS)
                message(FATAL_ERROR "board ${BOARD} is not supported")
        endif()
endif()

# Check if selected build type is supported.
if(DEFINED NRF_SUPPORTED_BUILD_TYPES)
        if(NOT CMAKE_BUILD_TYPE IN_LIST NRF_SUPPORTED_BUILD_TYPES)
                message(FATAL_ERROR "${CMAKE_BUILD_TYPE} variant is not supported")
        endif()
endif()

# Add PINETIME_DIR as a BOARD_ROOT in case the board is in PINETIME_DIR
list(APPEND BOARD_ROOT ${PINETIME_DIR})

# Add PINETIME_DIR as a DTS_ROOT to include nrf/dts
list(APPEND DTS_ROOT ${PINETIME_DIR})

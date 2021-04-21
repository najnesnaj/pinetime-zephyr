# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
# Add the board
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_LIST_DIR})

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(periferal)



include_directories(include)

target_sources(app PRIVATE
  src/main.c
  src/param_sync.c
)


set(ZEPHYR_BOARD_FLASH_RUNNER jlink)

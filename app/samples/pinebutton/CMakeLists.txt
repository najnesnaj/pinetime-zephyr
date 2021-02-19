# SPDX-License-Identifier: Apache-2.0
#list(APPEND ZEPHYR_EXTRA_MODULES /root/zephyrproject/app/drivers/kscan2)
cmake_minimum_required(VERSION 3.13.1)
list(APPEND ZEPHYR_EXTRA_MODULES
  ${CMAKE_CURRENT_SOURCE_DIR}/oswatch_drivers
  )


# Add the board
list(APPEND BOARD_ROOT ${CMAKE_CURRENT_LIST_DIR})
#list(APPEND DTS_ROOT ${CMAKE_CURRENT_LIST_DIR}/..)
#add_subdirectory(drivers/kscan2)
# Enable configurations through environment variables
#set(CONF_FILE ${CMAKE_CURRENT_LIST_DIR}/config/prj.conf ${CMAKE_CURRENT_LIST_DIR}/config/bootloader.conf)
#IF("$ENV{BOOTLOADER}" STREQUAL "off")
#  set(CONF_FILE ${CMAKE_CURRENT_LIST_DIR}/config/prj.conf)
#ENDIF()
#IF("$ENV{LOGGING}" STREQUAL "on")
#  set(CONF_FILE ${CONF_FILE} ${CMAKE_CURRENT_LIST_DIR}/config/logging_rtt.conf)
#ENDIF()

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
include_directories(include)
project(sdlbutton)

FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})

# Get current time
string(TIMESTAMP CURRENT_TIME %Y-%m-%dT%H:%M:%S)

# Get short commit hash
execute_process(
  COMMAND ${GIT_EXECUTABLE} describe --tags
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
  OUTPUT_VARIABLE FW_BUILD_GIT
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DCURRENT_TIME_OF_BUILD=\"${CURRENT_TIME}\" -DFW_BUILD=\"${FW_BUILD_GIT}\"")
set(ZEPHYR_BOARD_FLASH_RUNNER jlink)

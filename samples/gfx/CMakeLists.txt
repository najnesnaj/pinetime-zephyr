# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(st7789v)

include_directories(include)
FILE(GLOB_RECURSE app_sources include/*.cpp src/*.cpp)
target_sources(app PRIVATE ${app_sources} src/main.cpp)

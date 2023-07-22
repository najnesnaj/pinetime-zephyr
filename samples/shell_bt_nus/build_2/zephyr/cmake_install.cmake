# Install script for directory: /home/naj/ncs/v2.4.0/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/soc/posix/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/TraceRecorder/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/naj/ncs/v2.4.0/nrf/samples/bluetooth/shell_bt_nus/build_2/zephyr/cmake/reports/cmake_install.cmake")
endif()


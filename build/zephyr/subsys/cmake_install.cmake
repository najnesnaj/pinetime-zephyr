# Install script for directory: /root/work/zephyr/subsys

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/root/work/pinetime/build/zephyr/subsys/debug/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/logging/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/bluetooth/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/fs/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/net/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/random/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/storage/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/fb/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/power/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/stats/cmake_install.cmake")
  include("/root/work/pinetime/build/zephyr/subsys/testsuite/cmake_install.cmake")

endif()


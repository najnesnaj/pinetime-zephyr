# LittlevGL Basic Sample

## Overview

This sample application displays "Hello World" in the center of the screen
and a counter at the bottom which increments every second.

If an input driver is supported, such as the touch panel controller on the pinetime
boards, "Hello World" is enclosed in a button that changes to the toggled state
when touched.

## Requirements

a pinetime or similar watch

## Building and Running

**NOTE**: When deferred logging is enabled you will likely need to increase
`CONFIG_LOG_STRDUP_BUF_COUNT` and/or
`CONFIG_LOG_STRDUP_MAX_STRING` to make sure no messages are lost or
truncated.

Example building for nrf52840dk_nrf52840:

Example building for native_posix:

## References

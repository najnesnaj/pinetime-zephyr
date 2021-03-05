# Basic OSWatch Framework

The application keeps track of time and displays time and date.
The initial time is the time of build.

Switching between screens can be done by multiple presses on button.

On the native_posix application 2 serial ports are available.
UART_1 connected to pseudotty: /dev/pts/2
UART_0 connected to pseudotty: /dev/pts/3

By connecting to UART_0 with :  minicom -D /dev/pts/3, you have access to the zephyr-shell.
(just type “help” to get overview)

## Overview

This is an opensource watch framework.
The same software can run in simulation (SDL) on linux, on the pinetime and on the ds_d6 oled watch.

This Basic application serves as a chassis, where accessories can be supplemented (bluetooth, fota, powermanagement, …)
These application carry the name oswatch-bt, oswatch-pm, oswatch-fota, oswatch-full.

Why implement powermanagent if you do not have a battery?
Why implement firmware over the air, if you can update the firmware with a debugprobe.

## Remark

This basic time keeping application, might need adjustment.
In that case you will still need CTS (bluetooth functionality).

## Requirements

no requirements since it can run without board (simulation)

## Building and Running

west build -p -b  native-posix_64 oswatch

## References

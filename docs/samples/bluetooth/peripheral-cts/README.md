# Bluetooth: Peripheral_cts

## Overview

Application demonstrating reading the time from a CTS service.

I used bluez on linux + a gatt server script that presents a current time service.

This program tests if it can get the time of a cts service. In order to get the time, you will have to connect the device first.

## Requirements


* a bluetoothdevice running the CTS service


* a board with this software (pinetime)

You will need a serial port to read the output of the "printk" messages.

## Building and Running

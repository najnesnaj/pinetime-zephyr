# Bluetooth: transferring data to the watch

## Overview

The same technique as in the cts-time setting is used.
A python script on linux, running bluez, reads 3 parameters.

The watch can read these parameters over bluetooth.

This sketch is used as a building block.

The gatt server python script is supplied. (values-gatt-server)
It prompts to input 3 parameters (integers)
You’ll need to run Bluez, start the script, and then connect to the watch, using bluetoothctl.

## Requirements


* BlueZ running on the host, or


* A board with BLE support

## Building and Running

See bluetooth samples section for details.

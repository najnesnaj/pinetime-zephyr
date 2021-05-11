# Data exchange   OSWatch Framework

## Overview

This sample reads/sets the time, using bluetooth CTS.
It reads 12 bytes of data from the gatt-server.

It uses notification to export data or real time transfer.

The idea is to exchange data with a linux box.

The watch behaves as a peripheral to the gatt server.

## Samples

This chunk of code is an extension on oswatch-cts. (exchanging data)
The extension can be found under samples/bluetooth, as individual samples.

## Requirements

A bluetooth gatt server. (example taken from bluez)
This can also be a smartphone.

Included is a python-script :  gatt-cts-bt-server.py, for use with bluez on linux.

```
python3  gatt-cts-bt-server.py
```

you need to connect to the watch in order, to have it read the time.

```
bluetoothctl
scan on (gets you list of bluetoothdevices)
connect D5:A0:A2:6D:A0:D5 (pick the pinetime - macaddress)
```

A few python scripts have been provided : scan+notification and scan+connect.

## Building and Running

west build -p -b  native-posix_64 oswatch-bt

## References

# Calendar oswatch

## Overview

Once the timer is started (2nd screen); the alarmtime is displayed on the first screen.

Now that we have a way to get data in/out of the watch, we can start to use it.
This timer corresponds to the timer1 parameter, which can be set with a bluetoothconnection.

Once the alarm expires, a message is display on the serial port. (This can be replaced by a vibrating motor)

## Button clicking

in the native_posix_64 version : long press switches screens. In the second screen, timer can be started by short clicks.
(2 times with some waiting in between). Short click means briefly clicking, otherwise it is interpreted as a double click.

In the code is defined for each board the clicking threshold. You can adapt this to your taste.

## Samples

This chunk of code is an extension on oswatch-bt. (exchanging data)

Smaller chunks of code can be found under samples. They can be run individually and can help explain/test some features.

## Requirements

Bluetooth/gatt server only needed if you want to change the timer1 value.

A bluetooth gatt server. (example taken from bluez)
This can also be a smartphone.

Included is a python-script :  gatt-cts-bt-server.py, for use with bluez on linux.

The timer-parameters are hardcoded in the python script, for testing purposes. (can be modified, of course)

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

west build -p -b  pinetime_devkit1 oswatch-calendar

## References

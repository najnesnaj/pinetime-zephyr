# bluetooth (BLE) example

The PineTime uses a Nordic nrf52832 chip, which has BLE functionality build into it.

To test, you can compile a standard application : Eddy Stone.

The watch will behave as a bluetooth beacon, and you should be able to detect it with your smartphone or with bluez under linux.

## Using a standard zephyr application under pinetime:

Each sample has its own directory.
In this directory you will notice a file : "CMakeLists.txt".

In order to use a standard, you can just copy it under the pinetime directory.

In order to be able to compile it, you just have to add one line in the CMakeList.txt :

include($ENV{ZEPHYR_BASE}/../pinetime/cmake/boilerplate.cmake)

Have a look in the samples/bluetooth/eddystone directory.

## Eddy Stone

> see:   Bluetooth: Eddystone

**Note:**  compile the provided example, so a build directory gets created

```
$ west build -p -b pinetime samples/bluetooth/eddystone
```

`this builds an image, which can be found under the build directory`

## Using the created bluetooth sample:

I use linux with a bluetoothadapter 4.0.
You need to install bluez.

```
#bluetoothctl
[bluetooth]#scan on
```

And your Eddy Stone should be visible.

If you have a smartphone, you can download the nrf utilities app from nordic.

## Ble Peripheral

this example is a demo of the services under bluetooth

first build the image

```
$  west build -p -b pinetime samples/bluetooth/peripheral
```

With linux you can have a look using bluetoothctl:

```
#bluetoothctl
[bluetooth]#scan on


[NEW] Device 60:7C:9E:92:50:C1 Zephyr Peripheral Sample Long
once you see your device
[blueooth]#connect 60:7C:9E:92:50:C1 (the device mac address as displayed)

then you can already see the services
```

same thing with the app from nordic, you could try to connect and display value of e.g. heart rate

## using Python to read out bluetoothservices

In this repo you will find a python script : readbat.py
In order to use it you need bluez on linux and the python bluepy module.

It can be used in conjunction with the peripheral bluetooth demo.
It just reads out the battery level, and prints it.

```
import binascii
from bluepy.btle import UUID, Peripheral

temp_uuid = UUID(0x2A19)

p = Peripheral("60:7C:9E:92:50:C1", "random")

try:
   ch = p.getCharacteristics(uuid=temp_uuid)[0]
   print binascii.b2a_hex(ch.read())
finally:
    p.disconnect()
```

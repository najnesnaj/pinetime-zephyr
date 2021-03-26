# Current Time Service

[https://www.bluetooth.com/specifications/gatt/services/](https://www.bluetooth.com/specifications/gatt/services/)

[https://www.bluetooth.com/specifications/gatt/characteristics/](https://www.bluetooth.com/specifications/gatt/characteristics/)


* 0x1805 current time service


* 0x2A2B current time characteristic

## Requirements:

You need :

    
    * a CTS server (use of bluez on linux explained)


            * start the CTS service (python script: gatt-cts-server.py provided)


            * connect to the CTS client


    * a CTS client (the oswatch)

## BLE Peripheral CTS sample for zephyr

This example demonstrates the basic usage of the current time service.
It is based on the [https://github.com/Dejvino/pinetime-hermes-firmware](https://github.com/Dejvino/pinetime-hermes-firmware).

It starts advertising it’s UUID, and you can connect to it.
Once connected, it will read the time from your CTS server
(bluez on linux running the gatt-cts-server script in my case)

first build the image

```
$  west build -p -b pinetime_devkit1 oswatch-cts
```

## Using bluez on linux to connect

The pinetime zephyr sample behaves as a peripheral:

```
- make sure your linuxbox has bluez running (type bluetoothctl if you're not sure)
- first of all start the cts service : python gatt-cts-server.py
- connect to the pinetime with bluetoothctl
```

Using bluetoothctl:

```
#bluetoothctl
[bluetooth]#scan on


[NEW] Device 60:7C:9E:92:50:C1 Zephyr Peripheral Sample Long
once you see your device
[blueooth]#connect 60:7C:9E:92:50:C1 (the device mac address as displayed)
```

## Howto use Bluez on linux to set up a time service

Within the bluez source distribution there is an example GATT (Generic Attribute Profile)server. It advertises some standard service such as heart rate, battery …
Koen zandberg adapted this script, so it advertises the current time :
[https://github.com/bosmoment/gatt-cts/blob/master/gatt-cts-server.py](https://github.com/bosmoment/gatt-cts/blob/master/gatt-cts-server.py)

You might have to install extra packages:

```
apt-get install python-dbus
apt-get install python-gi
apt-get install python-gobject
```

## Howto use Android to set up a time service

As soon as a device is bonded, Pinetime will look for a CTS server (Current Time Service) on the connected device.
Here is how to do it with an Android smartphone running NRFConnect:

Build and program the firmware on the Pinetime Install NRFConnect ([https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Connect-for-desktop](https://www.nordicsemi.com/Software-and-Tools/Development-Tools/nRF-Connect-for-desktop))

Start NRFConnect and create a CTS server : Tap the hamburger button on the top left and select “Configure GATT server” Tap “Add service” on the bottom Select server configuration “Current Time Service” and tap OK Go back to the main screen and scan for BLE devices. A device called “PineTime” should appear Tap the button “Connect” next to the PineTime device. It should connect to the PineTime and switch to a new tab. On this tab, on the top right, there is a 3 dots button. Tap on it and select Bond. The bonding process begins, and if it is successful, the PineTime should update its time and display it on the screen.

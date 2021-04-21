Bluetooth Notification
=======================


As mentioned earlier, I searched for ways to transfer data to, and(!) from the device.
Bluetooth data exchange might be a standard feature of Android, Apple ... 

On a linuxbox there are ways to do this as well!



In the zephyr samples,  I found a sample for Indication.
I created a sample for Notification. (samples/bluetooth/Peripheral-notification)

What?
-----

The BLE standard defines two ways to transfer data from the server to the client: notification and indication. 

Notification don't need acknowledgement, so it is faster. Hence, server does not know if the message reached the client....






How?
----

Notification has to be enabled.

Linuxbox (bluez) writes "enable" to the watch notification characteristic.

Once Nofication is enabled the watch sends continuously messages :
the maximum data payload size defined by the specification in each message is 20 bytes. 


Bluez
-----

on linux you could use  "bluetoothctl"

There is an example for heartrates.


::

        #bluetoothctl

	connect MAC-device

	menu gatt
	select-attribute 00002a37-0000-1000-8000-00805f9b34fb
	notify on

        if all goes well, the watch starts sending heartrates

	in case it stops:

	notify off
	notify on

A word on attributes
--------------------

The data that the server exposes is structured as attributes. 

Attribute type (Universally Unique Identifier or UUID)
This is a :
   - 16-bit number 
   - or 128-bit number 

The 16-bit number is converted to 128-bit by means of a
128-bit base UUID:00000000-0000-1000-8000-00805F9B34FB.

These 16-bit numbers are standardised. On each device the temperature measurement value is 0x2A1C.

Because I create a custom service to exchange data I use a custom attribute type, also sometimes referred to as vendor-specific UUID. 
BLE_CHARACTERISTIC_UUID= "12345678-1234-5678-1234-56789abcdef1"


Attribute Handle
----------------

This is a 16-bit value that the server assigns to each of its attributes — think of it as an address. This value is used by the client to reference a specific attribute and is guaranteed by the server to uniquely identify the attribute during the life of the connection between two devices. The range of handles is 0x0001-0xFFFF, where the value of 0x0000 is reserved.




Python
------
The scripts are provided. (scan+not.py)
But here is a short explanation on how to enable notifications.


On linux one could use the Gatttool from the commandprompt.

Another option is Python!

In this manual the module Bluepy is used : https://github.com/IanHarvey/bluepy.

(custom service)
BLE_SERVICE_UUID ="12345678-1234-5678-1234-56789abcdef0"
BLE_CHARACTERISTIC_UUID= "12345678-1234-5678-1234-56789abcdef1"

ch = ble_service.getCharacteristics()[0]
ch.valHandle (this gets you the handle to the notification characteristic

# Writing x01 is the protocol for all BLE notifications.
# However .... you need to write it to the handle + 1

dev.writeCharacteristic(ch.valHandle+1, b"\x01\x00", withResponse=True)













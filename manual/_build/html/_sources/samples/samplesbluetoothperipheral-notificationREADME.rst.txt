.. _ble_peripheral:

Bluetooth: getting data from the watch 
######################################

Overview
********


The watch transmits 240 indexed values.
It uses bluetoothnotification.
There is no confirmation of reception. (a bit like UDP network traffic)

This method is fast, and could be used to transmit measurement values in real time.

A custom service and characteristic is used.

A phyton script is supplied : 
 - the scrips scans for a specific device (since bluetoothmac is variable : a bit like DHCP in netwerk traffic)
 - once the device is found, it switches on "notifications" and listens for incoming messages.


Requirements
************

* BlueZ running on the host, or
* A board with BLE support

Building and Running
********************


See :ref:`bluetooth samples section <bluetooth-samples>` for details.

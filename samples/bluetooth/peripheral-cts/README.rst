.. _ble_peripheral_cts:

Bluetooth: Peripheral_cts
#########################

Overview
********

Application demonstrating reading the time from a CTS service. 

(reading out the cts service with bluez)

[Ds D6 sample cts server:/service0014/char0015]# read
Attempting to read /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0xdf
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0x07
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0x05
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0x1e
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0x0c
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0x2d
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0x1e
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0x01
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0x00
[CHG] Attribute /org/bluez/hci0/dev_75_D3_E5_20_20_26/service0014/char0015 Value: 0x00


Requirements
************

* a bluetoothdevice running the CTS service  (I used the bluetooth/samples/peripheral for this, it simulates a cts server)
* a board with this software (pinetime) 

Building and Running
********************

this is under development and is not working at all (yet)

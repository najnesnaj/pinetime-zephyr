# This code is intended to run on a device with up to date Bluez.
# Works on Raspberry Pi or Mac.
# Currently configured to stream heart rate.
# https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.service.heart_rate.xml
# Bluepy Docs
# @see http://ianharvey.github.io/bluepy-doc/
#  Notifciations doc: 
# @see http://ianharvey.github.io/bluepy-doc/notifications.html
# Code assumes adapter is already enabled, and scan was already done.

from bluepy import btle
import time
import binascii
import struct

# Address of BLE device to connect to. 47:C2:41:89:3E:F6
BLE_ADDRESS = "f6:2c:86:bd:4a:05"
# BLE heart rate service
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 00001800-0000-1000-8000-00805f9b34fb
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 00001801-0000-1000-8000-00805f9b34fb
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 0000180a-0000-1000-8000-00805f9b34fb
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 0000180d-0000-1000-8000-00805f9b34fb
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 0000180f-0000-1000-8000-00805f9b34fb




BLE_SERVICE_UUID ="0000180d-0000-1000-8000-00805f9b34fb"
# Heart rate measurement that notifies.
BLE_CHARACTERISTIC_UUID= "00002a37-0000-1000-8000-00805f9b34fb"
#BLE_CHARACTERISTIC_UUID = "0x2a37" 


class MyDelegate(btle.DefaultDelegate):
    def __init__(self):
        btle.DefaultDelegate.__init__(self)
        # ... initialise here

    def handleNotification(self, cHandle, data):
    	data = bytearray(data)
    	print 'Developer: do what you want with the data.'
	print data[0]
	print data[1]
#        print str(struct.unpack("B", data[1]))
        if(data[0] == '\x14'):
            self.message = "Connection Lost"
        if(data[0] == '\x16'):
            self.message = str(struct.unpack("B", data[1])[0])
        if(data[0] == '\x06'):
            self.message = "Booting"



#p = Peripheral("74:71:4B:D5:18:21", "random")
print "Connecting..."
dev = btle.Peripheral(BLE_ADDRESS, "random")
dev.setDelegate(MyDelegate())
 
service_uuid = btle.UUID(BLE_SERVICE_UUID)
ble_service = dev.getServiceByUUID(service_uuid)

ch = ble_service.getCharacteristics()[0]
print "jj was here" 
print(ch.valHandle)
#notify_handle = ch.getHandle() + 1

uuidConfig = btle.UUID(BLE_CHARACTERISTIC_UUID)
data_chrc = ble_service.getCharacteristics(uuidConfig)[0]

print "Debug Services...should show handles"
for svc in dev.services:
 	print str(svc)


print "data-chrc"
print data_chrc

# print 'Debug Characteristics...'
#for ch in es_service.getCharacteristics():
# 	print str(ch)

# Enable the sensor, start notifications
# Writing x01 is the protocol for all BLE notifications.
#char = peripheral.getCharacteristics(uuid=your_uuid_here)[0]
#   ccc_desc = char.getDescriptors(forUUID=0x2902)[0]
#   ccc_desc.write(b"\x01")

#data_chrc.write(bytes("\x01")) 
#data_chrc.write(b"\x01") 

#dev.writeCharacteristic(data_chrc, b"\x01\x00", withResponse=True)
dev.writeCharacteristic(ch.valHandle+1, b"\x01\x00", withResponse=True)

time.sleep(1.0) # Allow sensor to stabilise


# Main loop --------
while True:
    if dev.waitForNotifications(1.0):
        #handleNotification()
        # handleNotification() was called
        continue
    print "Waiting..."

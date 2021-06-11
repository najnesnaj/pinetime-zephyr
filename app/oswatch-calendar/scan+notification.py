# bluetooth MAC changes
# script scans bluetoothdevices and select name
#
#            if value == 'dsd6':
#         
# if a different board is used : replace dsd6 by your board eg. pinetime


from bluepy.btle import Scanner, DefaultDelegate

class ScanDelegate(DefaultDelegate):
    def __init__(self):
        DefaultDelegate.__init__(self)

#    def handleDiscovery(self, dev, isNewDev, isNewData):
#        if isNewDev:
#            print "Discovered device", dev.addr
#        elif isNewData:
#            print "Received new data from", dev.addr

scanner = Scanner().withDelegate(ScanDelegate())
devices = scanner.scan(10.0)
zephyrdevice = "not found"

for dev in devices:
#    print "Device %s (%s), RSSI=%d dB" % (dev.addr, dev.addrType, dev.rssi)
#    print "address %s   " % (dev.addr)
    for (adtype, desc, value) in dev.getScanData():
#            print "value = %s     " % (value)
            #if value == 'pinetime bluetooth peripheral':
            if value == 'dsd6':
#           print "%s   %s   %s" % (value, dev.addr, desc)
#                 print "%s   " % (value)
                 zephyrdevice = dev.addr

print('after scanning found this bluetooth MAC for the zephyr devices')
print(zephyrdevice)

if (zephyrdevice == "not found"):
	exit()
# This code is intended to run on a device with up to date Bluez.
# Works on Raspberry Pi or Mac.
# Currently configured to stream heart rate.
# https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.service.heart_rate.xml
# Bluepy Docs
# @see http://ianharvey.github.io/bluepy-doc/
#  Notifciations doc: 
# @see http://ianharvey.github.io/bluepy-doc/notifications.html
# Code assumes adapter is already enabled, and scan was already done.
# <najnesnaj@yahoo.com> 2021


from bluepy import btle
import time
import binascii
import struct

# Address of BLE device to connect to. 47:C2:41:89:3E:F6
#BLE_ADDRESS = "f6:2c:86:bd:4a:05"
BLE_ADDRESS = zephyrdevice 
# BLE heart rate service
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 00001800-0000-1000-8000-00805f9b34fb
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 00001801-0000-1000-8000-00805f9b34fb
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 0000180a-0000-1000-8000-00805f9b34fb
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 0000180d-0000-1000-8000-00805f9b34fb
#[CHG] Device 47:C2:41:89:3E:F6 UUIDs: 0000180f-0000-1000-8000-00805f9b34fb




BLE_SERVICE_UUID ="12345678-1234-5678-1234-56789abcdef0"
BLE_CHARACTERISTIC_UUID= "12345678-1234-5678-1234-56789abcdef1"


class MyDelegate(btle.DefaultDelegate):
    def __init__(self):
        btle.DefaultDelegate.__init__(self)
        # ... initialise here

    def handleNotification(self, cHandle, data):
        data = bytearray(data)
        print('next data....')
        print(data[0])
        print(data[1])
#        print str(struct.unpack("B", data[1]))
#        if(data[0] == '\x14'):
#            self.message = "Connection Lost"
#        if(data[0] == '\x16'):
#            self.message = str(struct.unpack("B", data[1])[0])
#        if(data[0] == '\x06'):
#            self.message = "Booting"



#p = Peripheral("74:71:4B:D5:18:21", "random")
print("Connecting...")
dev = btle.Peripheral(BLE_ADDRESS, "random")
time.sleep(10.0) # Allow some time for cts and param synchro 
dev.setDelegate(MyDelegate())
 
service_uuid = btle.UUID(BLE_SERVICE_UUID)
ble_service = dev.getServiceByUUID(service_uuid)

ch = ble_service.getCharacteristics()[0]
print(ch.valHandle)
#notify_handle = ch.getHandle() + 1

uuidConfig = btle.UUID(BLE_CHARACTERISTIC_UUID)
data_chrc = ble_service.getCharacteristics(uuidConfig)[0]

print("Debug Services...should show handles")
for svc in dev.services:
 	print(str(svc))


print("data-chrc")
print(data_chrc)

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
    if dev.waitForNotifications(2.0):
        #handleNotification()
        # handleNotification() was called
        continue
    print("Waiting...")

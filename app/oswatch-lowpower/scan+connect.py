# script scans bluetoothdevices and selects name (MAC changes, that is why)
#
# it connects to device and waits at bit .....
#
# and then disconnects
#
#  this should be enough to update the time and get parameters into the watch
#  condition : this script should be launched first:  gatt-cts-bt-server.py
#
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






class MyDelegate(btle.DefaultDelegate):
    def __init__(self):
        btle.DefaultDelegate.__init__(self)
        # ... initialise here

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
#dev.setDelegate(MyDelegate())
#btle.connect(BLE_ADDRESS, "random") 
print("waiting a bit and then disconnect..")

time.sleep(10.0) # allow cts to synchronise 

dev.disconnect()
# Main loop --------
#while True:
#    print("Waiting...")

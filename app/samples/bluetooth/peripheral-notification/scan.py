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

print 'after scanning found this bluetooth MAC for the zephyr devices'
print zephyrdevice



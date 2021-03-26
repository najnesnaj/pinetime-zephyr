import binascii
from bluepy.btle import UUID, Peripheral
 
temp_uuid = UUID(0x2A39)
  
p = Peripheral("74:71:4B:D5:18:21", "random")
   
try:
   ch = p.getCharacteristics(uuid=temp_uuid)[0]
   print 'write'
   ch.write(0x22)
finally:
    p.disconnect()

import binascii
from bluepy.btle import UUID, Peripheral
 
temp_uuid = UUID(0x2A19)
  
p = Peripheral("6D:E7:DE:A9:7A:7D", "random")
   
try:
   ch = p.getCharacteristics(uuid=temp_uuid)[0]
   print binascii.b2a_hex(ch.read())
finally:
    p.disconnect()

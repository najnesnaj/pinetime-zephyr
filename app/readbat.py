import binascii
from bluepy.btle import UUID, Peripheral
 
temp_uuid = UUID(0x2A19)
  
p = Peripheral("60:7C:9E:92:50:C1", "random")
   
try:
   ch = p.getCharacteristics(uuid=temp_uuid)[0]
   print binascii.b2a_hex(ch.read())
finally:
    p.disconnect()

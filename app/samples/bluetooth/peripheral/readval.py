import binascii
from bluepy.btle import UUID, Peripheral
 
temp_uuid = UUID(0x12345678)
  
p = Peripheral("51:47:ea:08:a9:b8", "random")
   
try:
   ch = p.getCharacteristics(uuid=temp_uuid)[0]
   print binascii.b2a_hex(ch.read())
finally:
    p.disconnect()

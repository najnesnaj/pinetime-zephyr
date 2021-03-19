import binascii
from bluepy.btle import UUID, Peripheral
 
temp_uuid = UUID(0x2A19)

p = Peripheral("74:71:4B:D5:18:21", "random")
   
try:
   ch = p.getCharacteristics(uuid=temp_uuid)[0]
   print binascii.b2a_hex(ch.read())
finally:
    p.disconnect()

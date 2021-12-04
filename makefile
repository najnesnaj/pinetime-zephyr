#sdcc -mstm8 -c  PID.c --> PID.rel
SDCC=sdcc
SDLD=sdcc
OBJECTS=ds18b20.ihx 



.PHONY: all clean flash

all: $(OBJECTS) 

clean:
	rm -f $(OBJECTS)

flash: ds18b20.ihx
	stm8flash -c stlink-v2 -pstm8s103?3 -w ds18b20.ihx



%.ihx: %.c stm8.h
	$(SDCC) -lstm8 -mstm8 --out-fmt-ihx $(CFLAGS) $(LDFLAGS) PID.rel $<
	stm8flash -c stlinkv2 -p stm8s103?3 -w ds18b20.ihx
	# minicom -b 115200 -D /dev/ttyUSB4

# hacking   the pinetime smartwatch

```
The pinetime is preloaded with firmware.
This firmware is secured, you cannot peek into it.
```

**NOTE**: The pinetime has a swd interface.
To be able to write firmware,  you need special hardware.
I use a stm-link which is very cheap(2$).
You can also use the GPIO header of a raspberry pi.
(my repo: [https://github.com/najnesnaj/openocd](https://github.com/najnesnaj/openocd) is adapted for the orange pi)

To flash the software I use openocd :
example for stm-link usb-stick

```
# openocd -s /usr/local/share/openocd/scripts -f interface/stlink.cfg -f target/nrf52.cfg
```

example for the orange-pi GPIO header (or raspberry)

> # openocd -f /usr/local/share/openocd/scripts/interface/sysfsgpio-raspberrypi.cfg
> -c ‘transport select swd’ -f /usr/local/share/openocd/scripts/target/nrf52.cfg
> -c ‘bindto 0.0.0.0’

once you started the openocd background server, you can connect to it using:

```
#telnet 127.0.0.1 4444
```

programming

```
once your telnet sessions started:
Trying 127.0.0.1...
Connected to 127.0.0.1.
Escape character is '^]'.
Open On-Chip Debugger
> program zephyr.bin

target halted due to debug-request, current mode: Thread
xPSR: 0x01000000 pc: 0x00001534 msp: 0x20004a10
** Programming Started **
auto erase enabled
using fast async flash loader. This is currently supported
only with ST-Link and CMSIS-DAP. If you have issues, add
"set WORKAREASIZE 0" before sourcing nrf51.cfg/nrf52.cfg to disable it
target halted due to breakpoint, current mode: Thread
xPSR: 0x61000000 pc: 0x2000001e msp: 0x20004a10
wrote 24576 bytes from file zephyr.bin in 1.703540s (14.088 KiB/s)
** Programming Finished **

And finally execute a reset :
>reset
```

removing write protection see:   howto flash your zephyr image

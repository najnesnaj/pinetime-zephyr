# Howto read the chip’s temperature?

open shell console
- trough a serial port
- trough segger RTT

uart:~$ sensor
sensor - Sensor commands
Subcommands:

> get  :Get sensor data. Channel names are optional. All channels are read when

>     no channels are provided. Syntax:
>     <device_name> <channel name 0> .. <channel name N>

uart:~$ sensor get
get: wrong parameter count
get - Get sensor data. Channel names are optional. All channels are read when no

> channels are provided. Syntax:
> <device_name> <channel name 0> .. <channel name N>

Subcommands:

    CLOCK               :
    UART_0              :
    RNG                 :
    sys_clock           :
    GPIO_0              :
    NRF_FLASH_DRV_NAME  :
    SPI_2               :
    TEMP_0              :

uart:~$ sensor get TEMP_0
channel idx=12 die_temp =  23.250000

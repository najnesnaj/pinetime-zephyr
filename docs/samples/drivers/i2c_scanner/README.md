# I2C Scanner sample

## Overview

This sample sends I2C messages without any data (i.e. stop condition
after sending just the address). If there is an ACK for the
address, it prints the address as `FOUND`.

**WARNING**: As  there  is  no  standard I2C detection command, this sample
uses arbitrary SMBus commands (namely SMBus quick write and SMBus
receive byte) to probe for devices.  This sample program can confuse
your I2C bus, cause data loss, and is known to corrupt
the Atmel AT24RF08 EEPROM found on many IBM Thinkpad laptops.
See also the [i2cdetect man page](http://manpages.ubuntu.com/manpages/bionic/man8/i2cdetect.8.html)

## Building and Running

# Bluetooth: transferring data to the watch

## Overview

On a linux box with bluez installed,  a python script is launched (example-gatt-server)

The linuxbox becomes a bluetooth gatt server.

This script offers a service and a bluetooth characteristic. (the battery service is used for this purpose)

In the python script example-gatt-server 10 bytes of data are advertised (battery service).

The watch scans for this characteristic, once it is connected and reads out the variables and puts them in a 10 byte arry.

Hence a transfer from the server to the watch took place!

Later on we can use this to set a timer in the watch or an alarm, or ….

You’ll need to:

    
    * run Bluez,


    * start the script,


    * and then connect to the watch, using bluetoothctl.

    The mechanism is the same as with the CTS time setting.

## Requirements


* BlueZ running on the host, or


* A board with BLE support

## Building and Running

See bluetooth samples section for details.

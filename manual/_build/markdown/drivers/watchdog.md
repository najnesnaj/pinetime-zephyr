# Watchdog

```
west build -p -b pinetime samples/drivers/watchdog
```

## Overview

Once the pinetime is closed and on your wrist, you still want access.

see : Firmware Over The Air (FOTA)

Suppose you upload a application which contains a bug, the watch freezes, and … you will have to open it up, connect the SWD …

Here comes the watchdog:

> 
> * you launch the watchdog


> * you launch the application


> * the application feeds the watchdog


> * if it cannot feed the watchdog, reset to fota, and you can upload another better version …

## Todo

testing

## References

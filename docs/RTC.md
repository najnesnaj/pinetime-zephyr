# Real Time Clock

## Overview

This sample application "clock" uses the RTC2 timer.
(the standard sample with RTC0 is not usable together with bluetooth)

It uses the counter driver. (based on the alarm sample)

Basically an interrupt is set to go off after 1 second.
The number of seconds is incremented and the interrupt is launched again.

It will serve as a building block for a "time of the day" clock.

In addition it will need a function to set the time.

In bluetooth one can use CTS (central time service)



```
**
```

NOTE: as I found out there is a conflict between RTC0 and bluetooth \*\*

## Requirements

Make sure the prj.conf contains the following :

```
CONFIG_COUNTER=y
```

## Building and Running

## Todo

> 
> * time of day clock


> * setting the time

## References

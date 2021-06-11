# Real Time Clock

The compile-time is used to set the initial time. (CMAKE file)

The elapsed time since the startup can be calculated.

Setting the exact time is done via bluetooth current time service. (oswatch-cts)

## Alarm

A cool feature, once you get a clock is an alarm. (oswatch-calendar)

You can set/stop the alarm.

Once set : the value of the “timer1” parameter is added to the current time.
Everytime the clock is updated, there is a check if the alarm-time has been reached.

The name (oswatch-calendar) was ambitious, but a more elaborate setup is possible using the same technique. (year month day hour minute needed as a parameter for a real calendar event)

## References

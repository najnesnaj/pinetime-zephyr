# Starting with some basic applications

The best way to get a feel of zephyr for the smartwatch, is to start building applications.

The gpio ports, i2c communication, memory layout, stuff that is particular for the watch is defined in the board definition file.

The provided samples are standard zephyr application, with some minor modifications.

The watch framework is under /app. This framework provides a clock, a button, bluetooth, touchscreen and 4 screens, where you can add stuff.

## Blinky    example

```
The pinetime watch does not contain a led as such, but it has a vibrator-motor which makes some noise.
The Desay D6 can blink it's heartrate sensor.
The vitual POSIX can print out to the screen.
```

### Building and Running

```
west build -p -b pinetime app/blinky
west build -p -b ds_d6 app/blinky
west build -p -b native_posix_64 app/blinky
```

## Reading out the button on the watch

```
The pinetime does have a button on the side.
The desay D6 has a touchbutton in front.
The virtual POSIX watch has a touchbutton
```

### Building and Running

*Note:*:
The pinetime watch has a button out port (15) and button in port (13). You have to set the out-port high. Took me a while to figure this out...

```
west build -p -b pinetime app/button
west build -p -b ds_d6 app/button
west build -p -b native_posix_64 app/button
```

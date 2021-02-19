# Starting with some basic applications

The best way to get a feel of zephyr for the smartwatch, is to start building applications.

The watch framework is under /app.

The framework contains a clock, bluetooth, a procedure to upgrade over the air, cts  …

To reduce the complexity, samples are provided.
Each sample contains a single feature of the framework.

## Building and Running

The “native_posix_64” board is your own linux-box.
This means that you can execute the code on your system.
You do not need a smartwatch.

```
west build -p -b native_posix_64 samples/sdlbutton
```

running : ./build/zephyr/zephyr.exe

```
west build -p -b pinetime_devkit1 samples/sdlbutton
```

running : west flash

### Reading out the button on the watch

```
The pinetime does have a button on the side.
The desay D6 has a touchbutton in front.
The virtual POSIX watch has a touchbutton
```

## Building and Running

*Note:*:
The pinetime watch has a button out port (15) and button in port (13). You have to set the out-port high. Took me a while to figure this out…

```
west build -p -b pinetime samples/button
west build -p -b ds_d6 samples/button
west build -p -b native_posix_64 samples/button
```

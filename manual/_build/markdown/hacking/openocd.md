w

# howto use 2 openocd sessions

Once you completed your `west build` , your image is located under the build directory

```
   $ cd ~/work/pinetime/zephyr/build/zephyr
   here you can find zephyr.bin which you can flash




I use Openocd to flash.
Just connect : telnet 127.0.0.1 4444

.. code-block:: console

    program zephyr.bin
```

## Suppose you have 2 microcontrollers

> Just connect : telnet 127.0.0.1 7777 for the second.

## Howto setup a second openocd session on a different port?

In this case an ST-LINK/V2 an in-circuit debugger and programmer is used.

```
openocd -c 'telnet_port 7777' -c 'tcl_port 6667' -c 'gdb_port 3332' -s /usr/local/share/openocd/scripts -f interface/stlink.cfg  -f target/nrf52.cfg
```

## Howto use the GPIO header of a Single Board computer

This works really well, and does not require a seperate programmer.

```
openocd -f /usr/local/share/openocd/scripts/interface/sysfsgpio-raspberrypi.cfg -c 'transport select swd' -f /usr/local/share/openocd/scripts/target/nrf52.cfg  -c 'bindto 0.0.0.0'
```

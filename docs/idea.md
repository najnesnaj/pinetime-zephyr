# The idea behind the framework

I adapted the pinetime hypnos firmware to run on the Desay D6 smartwatch.

This watch has a small (128x32) oled display and is rather minimalistic.

It does not have a touchscreen, but a single touchbutton.

One cannot run the software of a feature-rich smartwatch on a simple one.
But the reverse can be done.

## Screen

The OLED screen can only display a few lines.
This is used as a basis for screen layout.

Multiple screens can be displayed, but each screen has little info.

## Touchscreen

Although the LVGL graphics library offers touchscreen support and the Pinetimewatch has a touchscreen, the emphasis was put on the sidebutton. Most watches have a button.

Selecting a screen and a parameter on the screen is done with the button instead of the touchscreen.

## Heart rate sensor

Most heart rate sensors have a light sensor and an LED.
Instead of trying to get a heart rate out of it.
Emphasis was put on reading out the light sensor and controller the LED.

This way my cheap oled watch can be used to read out LED signals, and thus be used as a communication device.

The LED cannot be controlled indepently on the pinetime. Suppose you want to use the lightsensor without the led, it is not possible.

## Bluetooth

Setting time and timers or other parameters is a nuisance on a small device. It is far more easier to set/read parameters on a linux box or android device and transfer them to the smartwatch.

Bluetooth is used to set the time (CTS) current time service.

## Powersaving

Powersaving makes sense when the device is battery operated, which is probably not always the case.
Hence, powersaving is an option.

## Updating over the air

FOTA : firmwareupdating over the air, is a usefull option.
The way firmware updates work, is to have two firmware images on the device.
In the case of the cheap OLED device, there is no extra memory to store firmware images.
Hence, FOTA is an option.

## Motion sensor

The motion is used as a stepcounter, but could be used for other purposes as well. Knocksensor, position sensor, movement detection …
emphasis is put on reading out the sensor rather than processing the data.

## Drivers

Creating drivers takes a lot of time. Chances are that a specific driver does not exist for zephyr, or that the standard one does not work fully.

To overcome this problem a zephyr driver that ressembles the needed driver is adapted and placed out of tree. In some cases I have not even bothered to change the name. The max30101 lightsensor is not present in the smartwatches I worked with, but it exists as a driver that can easily be adapted. In zephyr this means that the board definition files need to refer to this driver as well. Board definition has to be placed out of tree as well.

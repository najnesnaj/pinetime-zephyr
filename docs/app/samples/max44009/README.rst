Lightsensor
###########




This is a modified sample app to read the pah8001 Heartrate sensor from the Desay D6 smartwatch.
It is used as a light sensor, uses the I2C protocol and is based on the max44009.
In order to function it needs the modified driver.

Notice :  in Kconfig MAX44009NEW was defined to avoid confusion with existing driver max44009
(this way the original does not get selected) 

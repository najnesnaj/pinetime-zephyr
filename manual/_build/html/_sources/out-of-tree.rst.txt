Out of tree 
===========

A technique used in zephyr/samples/application-development, is "out of tree" development.

When you tinker with watches, you will soon find out that not all the drivers exist.

You can adapt existing zephyr drivers, but placing them within the zephyr repository could cause issues (upgrading zephyr).


The samples provided contain the board definition and the drivers within their directory outside the zephyr directory.

Have a look at the samples, on how it is done.


::


	All the development, board definition files, drivers are contained in the "app" directory.
	Copy this directory alongside the zephyr rtos repository, and it should work.
	No extra configuration needed.
	You can use the latest Zephyr distribution.


Top Tip: 
--------

Adapting an existing driver is easier than writing one from scratch.  
In the Kconfig you just set another name : instead of SSD1306, you use SSD1306NEW.
You might need to adapt the board definition file <watch>.dts as well.
Zephyr stitches together parts based on labels. Make sure they match.

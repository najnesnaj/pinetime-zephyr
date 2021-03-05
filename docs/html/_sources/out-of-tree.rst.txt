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
  

========================
Install zephyr 
========================


In case you already have zephyr installed:
------------------------------------------


Pinetime works as external (out of tree) application.
You can clone pinetime next to zephyr in the working directory and update manifest and west.

::

     west config manifest.path pinetime


In case you start from scratch :
--------------------------------


https://docs.zephyrproject.org/latest/getting_started/index.html

the documentation describes an installation process under Ubuntu/macOS/Windows


I picked Debian (which is not listed)
.... and soon afterwards ran into trouble


`this behaviour is known as : stuborn or stupid, but I remain convinced it could work`



In the Zephyr getting started page :

1) select and update OS
2)  install dependencies
3) Get the source code

::   

      instead of following the procedure:
             cd ~
             west init zephyrproject
             cd zephyrproject
             west update

      you should do this :
              cd ~
              mkdir work
              cd work
              west init -m https://github.com/najnesnaj/pinetime-zephyr
              west update


4) complete the other steps


to test if your install works : 

cd ~/work/pinetime

west build -p -b pinetime samples/basic/blinky


**TIP : sometimes you run into trouble compiling: removing the build directory can help in that case**





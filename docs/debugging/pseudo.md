# pseudo

## simulation on NATIVE_POSIX_64

It is possible to use two serial ports on the virtual posix board.
One can display log message, while the other one lets you interact with the shell.

```
CONFIG_UART_CONSOLE=y
CONFIG_UART_CONSOLE_ON_DEV_NAME="UART_0"
CONFIG_UART_NATIVE_POSIX_PORT_1_ENABLE=y
CONFIG_UART_NATIVE_POSIX_PORT_1_NAME="UART_1"
CONFIG_SHELL=y
CONFIG_UART_SHELL_ON_DEV_NAME="UART_0"
```

```
root@osboxes:~/work/app# ./build/zephyr/zephyr.exe
UART_1 connected to pseudotty: /dev/pts/2
UART_0 connected to pseudotty: /dev/pts/3


minicom -D /dev/pts/3
```

```
(you should see log messages)
```

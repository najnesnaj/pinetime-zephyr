# debugging Posix

start gdb on the command prompt

```
(gdb) file build/zephyr/zephyr.elf
Reading symbols from build/zephyr/zephyr.elf...done.
(gdb) b main
Breakpoint 1 at 0x5909: file /root/work/zephyr/boards/posix/native_posix/main.c, line 56.
(gdb) run
```

Debug oswatch-bt (which needs and argument –bt-dev=hci0)
Set the breakpoint in the function connected

```
(gdb) file build/zephyr/zephyr.elf
Reading symbols from build/zephyr/zephyr.elf...done.
(gdb) b connected
Breakpoint 1 at 0x498a: file /root/work/app/oswatch-bt/src/bt.c, line 140.
(gdb) r --bt-dev=hci0
```

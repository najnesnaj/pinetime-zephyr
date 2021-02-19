=========
debugging Posix 
=========


start gdb


//(gdb) target exec build/zephyr/zephyr.exe
//No symbol table is loaded.  Use the "file" command.



dit is genoeg

(gdb) file build/zephyr/zephyr.elf
Reading symbols from build/zephyr/zephyr.elf...done.
(gdb) b main
Breakpoint 1 at 0x5909: file /root/work/zephyr/boards/posix/native_posix/main.c, line 56.

(gdb) run


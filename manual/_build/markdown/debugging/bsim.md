# Bsim

this is a method of debugging a bluetooth enabled application, without a bluetooth device

## debugging on nrf52_bsim

You can compile the oswatch-bt sample for the bsim board.

```
west build -p -b nrf52_bsim oswatch-bt
gdb

file build/zephyr/zephyr.elf
b connected (breakpoint on function connected)
r -s=trial_sim -d=1
```

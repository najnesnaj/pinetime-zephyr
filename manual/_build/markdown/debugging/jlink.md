# Segger RTT (Real Time Transfer)

# Serial data without a serial port

Pinetime does not have UART pins but UART-like connection can be achieved using RTT (Real Time Transfer)
feature of Segger JLink debugger. RTT data can be accessed using the SEGGER tool (JLinkRTTViewer) or by using
telnet connection to active debug session. Second method is recommended since it gives better throughput
and allows bidirectional communication using Zephyr Shell (with RTT as backend). PuTTY can be used to
telnet to debug session.

Prerequisites:
- JLink debugger, for example one of Nordic Semiconductor Development Kits.
- Setup: [https://wiki.pine64.org/index.php/PineTime#Using_JLink_programmer_and_nrfjprog_tools](https://wiki.pine64.org/index.php/PineTime#Using_JLink_programmer_and_nrfjprog_tools)

Following steps needs to be taken to run RTT shell in the application:
1. Install PuTTY and Setup RTT session. On Linux, copy misc/rtt_shell/rtt to ~/putty/sessions. On Windows,
execute misc/rtt_shell/putty-rtt.reg.
2. Enable logging and shell over RTT:
`\`
CONFIG_LOG=y
CONFIG_USE_SEGGER_RTT=y
CONFIG_SHELL=y
CONFIG_SHELL_BACKEND_RTT=y
\``


1. Build and flash application.

4. Start debug session
`\`
west debug (will start gdb)
continue (in gdb console)
\``
5. Start PuTTY RTT session, prompt should be printed.

Resources:
- Zephyr shell documentation: [https://docs.zephyrproject.org/latest/reference/shell/index.html](https://docs.zephyrproject.org/latest/reference/shell/index.html)
- Zephyr logger documentation: [https://docs.zephyrproject.org/latest/reference/logging/index.html](https://docs.zephyrproject.org/latest/reference/logging/index.html)

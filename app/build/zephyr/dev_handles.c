#include <device.h>
#include <toolchain.h>

/* 1 : /uart:
 * - (/)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_uart[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 2 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_sys_init_sys_clock_driver_init0[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 3 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_sdl[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 4 : /flash-controller@0:
 * - (/)
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_DT_N_S_flash_controller_0[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

/* 5 : sysinit:
 */
const device_handle_t __aligned(2) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_sdl_display[] = { DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS, DEVICE_HANDLE_ENDS };

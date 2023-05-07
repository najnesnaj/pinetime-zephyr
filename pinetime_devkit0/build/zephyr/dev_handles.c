#include <zephyr/device.h>
#include <zephyr/toolchain.h>

/* 1 : /gpio@800:
 * Supported:
 *    - /gpio@800/sdl_gpio
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_27[4];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_27[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 2, DEVICE_HANDLE_ENDS };

/* 2 : /gpio@800/sdl_gpio:
 * Direct Dependencies:
 *    - /gpio@800
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_28[4];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_28[] = { 1, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 3 : /input-sdl-touch:
 * Supported:
 *    - /input-sdl-touch/kscan-input
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_29[4];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_29[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, 4, DEVICE_HANDLE_ENDS };

/* 4 : /input-sdl-touch/kscan-input:
 * Direct Dependencies:
 *    - /input-sdl-touch
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_30[4];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_30[] = { 3, DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

/* 5 : /sdl_dc:
 */
extern const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2"))) __devicehdl_dts_ord_12[3];
const Z_DECL_ALIGN(device_handle_t) __attribute__((__section__(".__device_handles_pass2")))
__devicehdl_dts_ord_12[] = { DEVICE_HANDLE_SEP, DEVICE_HANDLE_SEP, DEVICE_HANDLE_ENDS };

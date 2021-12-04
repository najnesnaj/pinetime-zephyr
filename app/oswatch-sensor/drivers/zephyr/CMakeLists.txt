# SPDX-License-Identifier: Apache-2.0
if(CONFIG_SSD1306NEW)
	zephyr_library()
        zephyr_library_sources(
	ssd1306.c
		)
if(CONFIG_ADXL345NEW)

#zephyr_library_sources_ifdef(CONFIG_KSCAN_FT5336	kscan2_ft5336.c)
#zephyr_library_sources_ifdef(CONFIG_KSCAN_XEC		kscan_mchp_xec.c)
#zephyr_library_sources_ifdef(CONFIG_KSCAN_SDL		kscan2_sdl.c)

#zephyr_library_sources_ifdef(CONFIG_USERSPACE	    kscan_handlers.c)
endif()

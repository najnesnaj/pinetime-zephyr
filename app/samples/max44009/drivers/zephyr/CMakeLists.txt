# SPDX-License-Identifier: Apache-2.0
if(CONFIG_MAX44009NEW)
	zephyr_library()
        zephyr_library_sources(
		max44009.c	
		)

endif()

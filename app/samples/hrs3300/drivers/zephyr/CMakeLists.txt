# SPDX-License-Identifier: Apache-2.0
# Copyright (c) <najnesnaj@yahoo.com>
if(CONFIG_HRS3300NEW)
	zephyr_library()
        zephyr_library_sources(
		hrs3300.c	
		)

endif()

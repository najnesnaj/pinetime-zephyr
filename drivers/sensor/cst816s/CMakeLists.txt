# SPDX-License-Identifier: Apache-2.0

zephyr_library()

zephyr_library_sources_ifdef(CONFIG_CST816S cst816s.c)
zephyr_library_sources_ifdef(CONFIG_CST816S_TRIGGER cst816s_trigger.c)

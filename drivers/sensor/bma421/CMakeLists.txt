# SPDX-License-Identifier: Apache-2.0

zephyr_library()

zephyr_library_sources_ifdef(CONFIG_BMA421 bma421.c)
zephyr_library_sources_ifdef(CONFIG_BMA421_TRIGGER bma421_trigger.c)

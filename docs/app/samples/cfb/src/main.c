/*
 * Copyright (c) 2018 PHYTEC Messtechnik GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <device.h>
#include <display/cfb.h>
#include <stdio.h>
#include <drivers/gpio.h>

#if defined(CONFIG_SSD16XX)
#define DISPLAY_DRIVER		"SSD16XX"
#endif

#if defined(CONFIG_SSD1306)
#define DISPLAY_DRIVER		"SSD1306"
#endif

#if defined(CONFIG_ST7789V)
#define DISPLAY_DRIVER		"ST7789V"
#endif

#ifndef DISPLAY_DRIVER
#define DISPLAY_DRIVER		"DISPLAY"
#endif

#if defined(CONFIG_BOARD_PINETIME_DEVKIT1)


#define LED0_NODE DT_ALIAS(led1)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0    DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN     DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS   DT_GPIO_FLAGS(LED0_NODE, gpios)
#endif

static void backlight_init(void)
{
	const struct device *dev;

	dev = device_get_binding(LED0);
	/* If you have a backlight, set it up and turn it on here */
	gpio_pin_configure(dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
	//   gpio_pin_configure(dev, LED, GPIO_DIR_OUT);
	gpio_pin_set(dev, PIN, 1);
	//gpio_pin_write(dev, LED, 0);
}

#endif


void main(void)
{       

	uint16_t rows;
	uint8_t ppt;
	uint8_t font_width;
	uint8_t font_height;
	const struct device *dev;

	dev = device_get_binding(DISPLAY_DRIVER);

	if (dev == NULL) {
		printf("Device not found\n");
		return;
	}
#if defined(CONFIG_BOARD_PINETIME_DEVKIT1)
	backlight_init();
	if (display_set_pixel_format(dev, PIXEL_FORMAT_RGB_565) != 0) {
		printf("Failed to set required pixel format\n");
		return;
	}
#else
	if (display_set_pixel_format(dev, PIXEL_FORMAT_MONO10) != 0) {
		printf("Failed to set required pixel format\n");

		return;
	}

#endif
	printf("initialized %s\n", DISPLAY_DRIVER);

	if (cfb_framebuffer_init(dev)) {
		printf("Framebuffer initialization failed!\n");
		return;
	}

	cfb_framebuffer_clear(dev, true);

	display_blanking_off(dev);

	rows = cfb_get_display_parameter(dev, CFB_DISPLAY_ROWS);
	ppt = cfb_get_display_parameter(dev, CFB_DISPLAY_PPT);
	printf("rows %d\n", rows);
	printf("ppt %d\n", ppt);

	for (int idx = 0; idx < 42; idx++) {
		if (cfb_get_font_size(dev, idx, &font_width, &font_height)) {
			break;
		}
		cfb_framebuffer_set_font(dev, idx);
		printf("font width %d, font height %d\n",
				font_width, font_height);
	}

	//test to see if it gets any pixel light
	//cfb_framebuffer_invert(dev);
	printf("x_res %d, y_res %d, ppt %d, rows %d, cols %d\n",
			cfb_get_display_parameter(dev, CFB_DISPLAY_WIDTH),
			cfb_get_display_parameter(dev, CFB_DISPLAY_HEIGH),
			ppt,
			rows,
			cfb_get_display_parameter(dev, CFB_DISPLAY_COLS));

	while (1) {
//		for (int i = 0; i < rows; i++) {
			cfb_framebuffer_clear(dev, false);
			if (cfb_print(dev,
						"DS-D6 ZEPHYR j!\"§$%&/()=",
						//0, i * ppt)) {
						0, 1 * ppt)) {
//				printf("Failed to print a string\n");
				continue;
			}

			k_sleep(K_MSEC(1000));
			cfb_framebuffer_finalize(dev);
			//#if defined(CONFIG_ARCH_POSIX)
			//#endif
//		}
	}
}

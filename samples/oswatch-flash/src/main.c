/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <string.h>
//#include <zephyr/fs/fs.h>
//#include <zephyr/storage/flash_map.h>
#include "beavis.c"
#if defined(CONFIG_BOARD_ADAFRUIT_FEATHER_STM32F405)
#define SPI_FLASH_TEST_REGION_OFFSET 0xf000
#elif defined(CONFIG_BOARD_ARTY_A7_ARM_DESIGNSTART_M1) || \
	defined(CONFIG_BOARD_ARTY_A7_ARM_DESIGNSTART_M3)
/* The FPGA bitstream is stored in the lower 536 sectors of the flash. */
#define SPI_FLASH_TEST_REGION_OFFSET \
	DT_REG_SIZE(DT_NODE_BY_FIXED_PARTITION_LABEL(fpga_bitstream))
#elif defined(CONFIG_BOARD_NPCX9M6F_EVB) || \
	defined(CONFIG_BOARD_NPCX7M6FB_EVB)
#define SPI_FLASH_TEST_REGION_OFFSET 0x7F000
#else
//this is used for the pinetime
//  slot1_partition: partition@0 {
//  label = "image-1";
//  reg = <0x00000000 0x74000>;
//  };
//  storage_partition: partition@300000 {
//  label = "storage";
//  reg = <0x00300000 0x00100000>;
//
//
// So I guess I can use 0x74000 till 0x300000 for storing images ....
//#define SPI_FLASH_TEST_REGION_OFFSET 0xff000
#define SPI_FLASH_TEST_REGION_OFFSET 0x74000
#endif
#define SPI_FLASH_SECTOR_SIZE        4096

#if defined CONFIG_FLASH_STM32_OSPI
#define SPI_FLASH_MULTI_SECTOR_TEST
#endif

//#define IMAGE_FILE_PATH     "beavis.bin"


void single_sector_test(const struct device *flash_dev)
{
//	const uint8_t expected[] = { 0x55, 0xaa, 0x66, 0x99 };
//	const size_t len = sizeof(expected);
//	uint8_t buf[sizeof(expected)];
	int rc;
	//here I want to read the image file
	uint8_t buffer[256];
        struct fs_file_t file;
	struct fs_dirent entry;
	off_t file_size;
	int err;
	off_t flash_offset = SPI_FLASH_TEST_REGION_OFFSET;
	/* Open the image file for reading */
//	err = fs_open(&file, IMAGE_FILE_PATH, FS_O_READ);
//	if (err) {
//	         printk("Failed to open image file: %d\n", err);
//	         return;
//	         }
	 /* Get the size of the image file */
	//err = fs_size(&file, &file_size);
//        err = fs_stat(IMAGE_FILE_PATH, &entry);	
//	if (err) {
//	         printk("Failed to get image file information: %d\n", err);
//	         fs_close(&file);
//	         return;
//	         }
//        file_size = entry.size;
        printf("\nTest 1: Flash erase\n");

	        /* 
		 * erase the area where the image will get stored 
		 *                   */
	rc = flash_erase(flash_dev, SPI_FLASH_TEST_REGION_OFFSET,
				                         //SPI_FLASH_SECTOR_SIZE);
				                         file_size);
        if (rc != 0) {
                    printf("Flash erase failed! %d\n", rc);
    	        } else {
                  printf("Flash erase succeeded!\n");
	        }

	printf("\nTest 2: Flash write\n");

    /* Copy the image data to flash memory */
	while (file_size > 0) {
		            size_t read_size = MIN(file_size, sizeof(buffer));

		            /* Read a chunk of data from the image file */
		            err = fs_read(&file, buffer, read_size);
	                   if (err <= 0) {
			                printk("Failed to read image file: %d\n", err);
	     		                fs_close(&file);
				         return;
				        }
	                    /* Write the data to flash memory */
	err = flash_write(flash_dev, flash_offset, buffer, read_size);
	//	            err = flash_write(flash_offset, buffer, read_size);
			    if (err) {
			              printk("Failed to write to flash memory: %d\n", err);
			              fs_close(&file);
			              return;
			             }

			    flash_offset += read_size;
			    file_size -= read_size;
			    }


       printk("Image file copied to flash memory successfully.\n");

	        /* Close the image file */
        fs_close(&file);

/*	printf("Attempting to write %zu bytes\n", len);
	rc = flash_write(flash_dev, SPI_FLASH_TEST_REGION_OFFSET, expected, len);
	if (rc != 0) {
		printf("Flash write failed! %d\n", rc);
		return;
	}

	memset(buf, 0, len);
	rc = flash_read(flash_dev, SPI_FLASH_TEST_REGION_OFFSET, buf, len);
	if (rc != 0) {
		printf("Flash read failed! %d\n", rc);
		return;
	}

	if (memcmp(expected, buf, len) == 0) {
		printf("Data read matches data written. Good!!\n");
	} else {
		const uint8_t *wp = expected;
		const uint8_t *rp = buf;
		const uint8_t *rpe = rp + len;

		printf("Data read does not match data written!!\n");
		while (rp < rpe) {
			printf("%08x wrote %02x read %02x %s\n",
			       (uint32_t)(SPI_FLASH_TEST_REGION_OFFSET + (rp - buf)),
			       *wp, *rp, (*rp == *wp) ? "match" : "MISMATCH");
			++rp;
			++wp;
		}
	}
	*/
}

int main(void)
{
	const struct device *flash_dev = DEVICE_DT_GET(DT_ALIAS(spi_flash0));
//	const struct device *flash_dev = DEVICE_DT_GET(DT_ALIAS(spi1_cs0_flash));

	if (!device_is_ready(flash_dev)) {
		printk("%s: device not ready.\n", flash_dev->name);
		return 0;
	}
	else {
		printk("%s: device is really ready.\n", flash_dev->name);
	}
	printf("\n%s SPI flash testing\n", flash_dev->name);
	printf("==========================\n");

	single_sector_test(flash_dev);
	return 0;
}

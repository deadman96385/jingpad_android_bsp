/*
 * Copyright (C) 2013 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 */

#include <boot_mode.h>
#include <common.h>
#include <fat.h>
#include <sprd_common_rw.h>
#include <asm/arch/check_reboot.h>
#include <ext4fs.h>


#define PART_SYSTEM						"userdata"
#define SPRDISK_RAMDISK_PATH	"/sprdisk/ramdisk.img"
#define SD_RAMDISK   "ramdisk.img"
extern int _sd_fat_mount();
extern int load_sd_ramdisk(void* buf,int size);
extern unsigned reboot_mode_check(void);
static int file_read(char *mpart, char *filenm, void *buf, int len)
{
#ifdef CONFIG_FS_EXT4
	disk_partition_t info;
	block_dev_desc_t *dev_desc;

	loff_t len_read = 0;
	loff_t file_len = len;
	int ret = 0;

	dev_desc = get_dev("mmc", 0);
	if (NULL == dev_desc) {
		printf("ext4_read_content get dev error\n");
		return -1;
	}

	if (get_partition_info_by_name(dev_desc, mpart, &info) == -1) {
		printf("## Valid EFI partition not found ##\n");
		return -1;
	}

	/* set the device as block device */
	ext4fs_set_blk_dev(dev_desc, &info);

	/* mount the filesystem */
	if (!ext4fs_mount(info.size)) {
		printf("Bad ext4 partition:%s\n",  mpart);
		ext4fs_close();
		return -1;
	}

	ret = ext4fs_open(filenm, &file_len);
	if (ret < 0) {
		printf("** %s doesn't exist %s **\n", mpart, filenm);
		return -1;
	}

	if (len != 0) {
		/* start read */
	    if (ext4fs_read(buf, file_len, &len_read) < 0){
			printf("** Error ext4fs_read file %s **\n", filenm);
			ext4fs_close();
			return -1;
		}
	}

	ext4fs_close();
	ret = (int)file_len;
	return ret;

#endif
}

static int read_sd_ramdisk(void *buf, int size)
{
	int ret = 0;

	if(size != 0)
		return load_sd_ramdisk(buf, size);
	ret = _sd_fat_mount();
	if (ret < 0) {
		errorf("mount fat fs in sd fail\n");
		return -1;
	}

	loff_t len = 0;
	ret = fat_size(SD_RAMDISK, &len);
	if (ret < 0) {
		errorf("get %s in sd fail\n", SD_RAMDISK);
		return -1;
	}

	ret = (int)len;
	return ret;
}

int boot_sprdisk(int offset, char *ramdisk_addr)
{
	int	ret;

	ret = file_read(PART_SYSTEM, SPRDISK_RAMDISK_PATH, (void *)ramdisk_addr, offset);
	if(ret <= 0){
		ret = read_sd_ramdisk((void *)ramdisk_addr, offset);
		if(ret < 0){
			errorf("sd read file %s wrong!\n", SD_RAMDISK);
		}
	}
	return ret;
}

int sprdisk_mode_detect(void)
{
	if(reboot_mode_check() == CMD_SPRDISK_MODE) {
		return 1;
	}

	return 0;
}

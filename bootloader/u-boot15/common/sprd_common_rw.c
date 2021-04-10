#include <common.h>
#include <malloc.h>
#include <part.h>
#include <sprd_common_rw.h>
#include <ext4fs.h>
#include <mmc.h>
#include <chipram_env.h>
#ifdef  CONFIG_NAND_BOOT
#include <jffs2/load_kernel.h>
#include <linux/mtd/partitions.h>
#include <nand.h>
#include <ubi_uboot.h>
#include <dl_ubi.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

static disk_partition_t local_part_info;

enum block_boot_part {
	USER_PART       = 0x00,
	BOOT_PART1   = 0x01,
	BOOT_PART2      = 0x02
};

char *block_dev_get_name(void)
{
	char *boot_device_name;

	if (gd->boot_device == BOOT_DEVICE_UFS)
		boot_device_name = "ufs";
	else
		boot_device_name = "mmc";//if not ufs return emmc for default

	return boot_device_name;
}

int block_dev_read(block_dev_desc_t *dev_desc, uint64_t size, uint64_t offset, char *buf)
{
	lbaint_t start = 0;
	lbaint_t blkcnt = 0;
	char * temp = NULL;
	uint64_t header_sz = 0;
	uint64_t offb = 0;

	if ((0 != size % dev_desc->blksz) || (0 != offset % dev_desc->blksz)) {
		temp = malloc(dev_desc->blksz);
		if (NULL == temp)
			goto fail;
	}

	start = offset / dev_desc->blksz;
	offb = offset % dev_desc->blksz;
	if (0 != offb) {
		header_sz = dev_desc->blksz - offb;
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read start block 0x%x fail\n", start);
			goto fail;
		}
		if (size <= header_sz) {
			memcpy(buf, temp + offb, size);
			size = 0;
		} else {
			memcpy(buf, temp + offb, header_sz);
			start++;
			buf += header_sz;
			size -= header_sz;
		}
	}

	blkcnt = size / dev_desc->blksz;
	if (blkcnt > 0) {
		if (blkcnt != dev_desc->block_read(dev_desc->dev, start, blkcnt, buf)) {
			errorf("read block 0x%x size 0x%x fail\n", start, blkcnt);
			goto fail;
		}
		start += blkcnt;
		buf += (blkcnt * dev_desc->blksz);
		size = size % dev_desc->blksz;
	}

	if (size > 0) {
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read end block 0x%x fail\n", start);
			goto fail;
		}
		memcpy(buf, temp, size);
	}

	if (NULL != temp)
		free(temp);
	return 0;

fail:
	if (NULL != temp)
		free(temp);
	return -1;
}


int block_dev_write(block_dev_desc_t *dev_desc, uint64_t size, uint64_t offset, char *buf)
{
	lbaint_t start = 0;
	lbaint_t blkcnt = 0;
	char * temp = NULL;
	uint64_t header_sz = 0;
	uint64_t offb = 0;

	if ((0 != size % dev_desc->blksz) || (0 != offset % dev_desc->blksz)) {
		temp = malloc(dev_desc->blksz);
		if (NULL == temp)
			goto fail;
	}

	start = offset / dev_desc->blksz;
	offb = offset % dev_desc->blksz;
	if (0 != offb) {
		header_sz = dev_desc->blksz - offb;
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read start block 0x%x for write fail\n", start);
			goto fail;
		}
		if (size <= header_sz) {
			memcpy(temp + offb, buf, size);
			size = 0;
		} else {
			memcpy(temp + offb, buf, header_sz);
			buf += header_sz;
			size -= header_sz;
		}
		if (1 != dev_desc->block_write(dev_desc->dev, start, 1, temp)) {
			errorf("write start block 0x%x fail\n", start);
			goto fail;
		}
		start++;
	}

	blkcnt = size / dev_desc->blksz;

	if (blkcnt > 0) {
		if (blkcnt != dev_desc->block_write(dev_desc->dev, start, blkcnt, buf)) {
			errorf("write block 0x%x size 0x%x fail\n", start, blkcnt);
			goto fail;
		}
		start += blkcnt;
		buf += (blkcnt * dev_desc->blksz);
		size = size % dev_desc->blksz;
	}

	if (size > 0) {
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read end block 0x%x for write fail\n", start);
			goto fail;
		}
		memcpy(temp, buf, size);
		if (1 != dev_desc->block_write(dev_desc->dev, start, 1, temp)) {
			errorf("write end block 0x%x fail\n", start);
			goto fail;
		}
	}

	if (NULL != temp)
		free(temp);
	return 0;

fail:
	if (NULL != temp)
		free(temp);
	return -1;
}

int block_dev_erase(block_dev_desc_t *dev_desc, uint64_t size, uint64_t offset)
{
	lbaint_t start = 0;
	lbaint_t blkcnt = 0;
	char * temp = NULL;
	uint64_t header_sz = 0;
	uint64_t offb = 0;

	if ((0 != size % dev_desc->blksz) || (0 != offset % dev_desc->blksz)) {
		temp = malloc(dev_desc->blksz);
		if (NULL == temp)
			goto fail;
	}

	start = offset / dev_desc->blksz;
	offb = offset % dev_desc->blksz;
	if (0 != offb) {
		header_sz = dev_desc->blksz - offb;
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read start block 0x%x for erase fail\n", start);
			goto fail;
		}
		if (size <= header_sz) {
			memset(temp + offb, 0, size);
			size = 0;
		} else {
			memset(temp + offb, 0, header_sz);
			size -= header_sz;
		}
		if (1 != dev_desc->block_write(dev_desc->dev, start, 1, temp)) {
			errorf("erase start block 0x%x fail\n", start);
			goto fail;
		}
		start++;
	}

	blkcnt = size / dev_desc->blksz;
	if (blkcnt > 0) {
		if (blkcnt != dev_desc->block_erase(dev_desc->dev, start, blkcnt)) {
			errorf("erase block 0x%x size 0x%x fail\n", start, blkcnt);
			goto fail;
		}
		start += blkcnt;
		size = size % dev_desc->blksz;
	}

	if (size > 0) {
		if (1 != dev_desc->block_read(dev_desc->dev, start, 1, temp)) {
			errorf("read end block 0x%x for erase fail\n", start);
			goto fail;
		}
		memset(temp, 0, size);
		if (1 != dev_desc->block_write(dev_desc->dev, start, 1, temp)) {
			errorf("erase end block 0x%x fail\n", start);
			goto fail;
		}
	}

	if (NULL != temp)
		free(temp);
	return 0;

fail:
	if (NULL != temp)
		free(temp);
	return -1;
}

#ifndef CONFIG_NAND_BOOT
int common_raw_read(char *part_name, uint64_t size, uint64_t offset, char *buf)
{
	int dev_id = 0;
	char *ifname;
	lbaint_t part_start = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	uint64_t total_part_size = 0;
	uint64_t total_part_read_size = 0;
	int ret = 0;

	ifname = block_dev_get_name();

	if(strstr(part_name, "_size") != NULL) {
		ret =get_img_partition_size(part_name, &total_part_read_size);
		debugf("%s = 0x%llx block number: 0x" LBAF "\n",
				part_name, total_part_read_size, total_part_read_size/512);
		sprintf(buf, "size:%s: 0x%llx block number: 0x" LBAF "\n",
				part_name, total_part_read_size, total_part_read_size/512);
		return ret;
	} else if(strcmp(part_name, "user_partition") == 0) {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		part_start = 0;
		total_part_size = get_devsize_hwpart(ifname, USER_PART);
		if (size + offset > total_part_size) {
			errorf("read user partition size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n",
					size, offset, total_part_size);
			ret = -1;
		}
	} else if (0 == strcmp(part_name, "splloader")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART1);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART1);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		if (-1 == ret) {
			ret = 0;
			dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
			dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
		} else {
			part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
			total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
			if (size + offset > total_part_size) {
				errorf("uboot read size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
				ret = -1;
			}
		}
	} else {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
		total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
		if (size + offset > total_part_size) {
			errorf("read size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
			ret = -1;
		}
	}

	if (-1 == ret || NULL == dev_desc)
		return -1;

	if (0 == size)
		size = total_part_size;

	offset += part_start;

	return block_dev_read(dev_desc, size, offset, buf);

}

int common_raw_write(char *part_name, uint64_t size, uint64_t updsize, uint64_t offset, char *buf)
{
	int dev_id = 0;
	char *ifname;
	uint64_t part_start = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	uint64_t total_part_size = 0;
	int ret = 0;

	ifname = block_dev_get_name();

	if (0 == strcmp(part_name, "splloader")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART1);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART1);
	} else if(0 == strcmp(part_name, "splloader_bak")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
	} else if(0 == strcmp(part_name, "uboot")) {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		if (-1 == ret) {
			ret = 0;
			dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
			dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
		} else {
			part_start = (uint64_t)part_info.blksz * (uint64_t)part_info.start;
			total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
			if (size + offset > total_part_size) {
				errorf("uboot write size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
				return -1;
			}
		}
	} else {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		part_start = (uint64_t)part_info.blksz * (uint64_t)part_info.start;
		total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
		if (size + offset > total_part_size) {
			errorf("write size(0x%llx + 0x%llx) overflow the total partition size(0x%llx)\n", size, offset, total_part_size);
			return -1;
		}
	}

	if (-1 == ret || NULL == dev_desc)
		return -1;

	offset += part_start;

	return block_dev_write(dev_desc, size, offset, buf);

}

int common_raw_erase(char *part_name, uint64_t size, uint64_t offset)
{
	int dev_id = 0;
	uint64_t part_start = 0;
	char *ifname;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	uint64_t total_part_size = 0;
	int ret = 0;

	ifname = block_dev_get_name();

	if (0 == strcmp(part_name, "erase_all")) {
		debugf("erase all the flash\n");

		dev_id = get_devnum_hwpart(ifname, BOOT_PART1);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART1);
		total_part_size = get_devsize_hwpart(ifname, BOOT_PART1);
		if (NULL == dev_desc || 0 == total_part_size)
			return -1;
		if (0 != block_dev_erase(dev_desc, total_part_size, 0))
			return -1;

		dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
		total_part_size = get_devsize_hwpart(ifname, BOOT_PART2);
		if (NULL == dev_desc || 0 == total_part_size)
			return -1;
		if (0 != block_dev_erase(dev_desc, total_part_size, 0))
			return -1;

		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		total_part_size = get_devsize_hwpart(ifname, USER_PART);
		if (NULL == dev_desc || 0 == total_part_size)
			return -1;
		if (0 != block_dev_erase(dev_desc, total_part_size, 0))
			return -1;

		return 0;
	}

	if (0 == strcmp(part_name, "splloader")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART1);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART1);
		total_part_size = get_devsize_hwpart(ifname, BOOT_PART1);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
		total_part_size = get_devsize_hwpart(ifname, BOOT_PART2);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		if (-1 == ret) {
			ret = 0;
			dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
			dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
			total_part_size = get_devsize_hwpart(ifname, BOOT_PART2);
		} else {
			part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
			total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
		}
	} else {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		part_start = (uint64_t)part_info.start * (uint64_t)part_info.blksz;
		total_part_size = (uint64_t)part_info.blksz * (uint64_t)part_info.size;
	}

	if (-1 == ret || NULL == dev_desc || 0 == total_part_size)
		return -1;

	if (0 == size) {
		size = total_part_size;
		offset = part_start;
	} else if (size + offset > total_part_size) {
		return -1;
	} else {
		offset += part_start;
	}

	if(block_dev_erase(dev_desc, size, offset))
		return -1;

	if (0 == strcmp(part_name, "uboot")) {
		uchar buf[512] = { 0x5A };
		printf("Use Write 5A pattern to uboot partition for check download status\n");
		 if (common_raw_write(part_name,(uint64_t)1, (uint64_t)0, (uint64_t)0, buf))
			return -1;
	}
	return 0;
}

int common_repartition(disk_partition_t *partitions, int parts_count)
{
	block_dev_desc_t *dev_desc;
	int dev_id = 0;
	char *ifname;
	int counter = 0;
	int ret = 0;

	ifname = block_dev_get_name();
	dev_id = get_devnum_hwpart(ifname, USER_PART);
	dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);

	memset(&local_part_info, 0 , sizeof(disk_partition_t));
	while (counter < 3) {
		ret = gpt_restore(dev_desc, SPRD_DISK_GUID_STR, partitions, parts_count);
		if (0 == ret)
			break;
		counter++;
	}

	if (3 == counter) {
		return -1;
	} else {
		init_part(dev_desc);
		return 0;
	}
}

int common_partition_sync(char *part_name)
{
	int dev_id = 0;
	char *ifname;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;
	int ret = 0;

	ifname = block_dev_get_name();

	if (0 == strcmp(part_name, "splloader")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART1);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART1);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		if (-1 == ret) {
			ret = 0;
			dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
			dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
		}
	} else {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		if (-1 == ret)
			return -1;
	}

	if (NULL == dev_desc)
		return -1;

	if(NULL == dev_desc->block_sync)
		return 0;

	if (0 != dev_desc->block_sync(dev_desc->dev))
		return -1;

	return 0;
}

int get_img_partition_id(char *part_name, unsigned int *id)
{
	int dev_id = 0;
	char *ifname;
	int ret = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;

	ifname = block_dev_get_name();

	if (0 == strcmp(part_name, "splloader")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART1);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART1);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		if (-1 == ret) {
			ret = 0;
			dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
			dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
		}
	} else {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
	}

	ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
	*id = part_info.part_num + 1;

	return ret;
}

int get_img_partition_size(char *part_name, uint64_t *size)
{
	int dev_id = 0;
	char *ifname;
	int ret = 0;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;

	ifname = block_dev_get_name();

	if (0 == strcmp(part_name, "splloader") ||
			!strcmp(part_name, "splloader_size")) {
		*size = get_devsize_hwpart(ifname, BOOT_PART1);
		return ret;
	} else if (0 == strcmp(part_name, "splloader_bak") ||
			!strcmp(part_name, "splloader_bak_size")) {
		*size = get_devsize_hwpart(ifname, BOOT_PART2);
		return ret;
	} else if (0 == strcmp(part_name, "uboot") ||
			!strcmp(part_name, "uboot_size")) {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		if (-1 == ret) {
			ret = 0;
			*size = get_devsize_hwpart(ifname, BOOT_PART1);
			return ret;
		}
	} else if (0 == strcmp(part_name, "user_partition_size")) {
		*size = get_devsize_hwpart(ifname, USER_PART);
		return ret;
	} else {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
	}

	ret = get_partition_info_by_name(dev_desc, part_name, &part_info);

	*size = part_info.size * part_info.blksz;

	return ret;
}



int32_t common_get_lba_size(void)
{
	int dev_id = 0;
	block_dev_desc_t *dev_desc;
	char *ifname;

	ifname = block_dev_get_name();
	dev_id = get_devnum_hwpart(ifname, USER_PART);
	dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
	if (NULL == dev_desc)
		return -1;

	return (int32_t)dev_desc->blksz;
}

int do_fs_file_read(char *mpart, char *filenm, void *buf, int len)
{
#ifdef CONFIG_FS_EXT4
	static int dev_id = 0;
	char *ifname;
	disk_partition_t info;
	block_dev_desc_t *dev_desc;
	loff_t len_read = 0;

	ifname = block_dev_get_name();
	dev_id = get_devnum_hwpart(ifname, USER_PART);
	dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);

	if (NULL == dev_desc) {
		errorf("ext4_read_content get dev error\n");
		return -1;
	}

	if (get_partition_info_by_name(dev_desc, mpart, &info) == -1) {
		errorf("## Valid EFI partition not found ##\n");
		return -1;
	}

	/* set the device as block device */
	ext4fs_set_blk_dev(dev_desc, &info);

	/* mount the filesystem */
	if (!ext4fs_mount(info.size)) {
		errorf("Bad ext4 partition:%s\n",  mpart);
		ext4fs_close();
		return -1;
	}

	/* start read */
	if (ext4_read_file(filenm, buf, 0, len, &len_read) == -1) {
		errorf("** Error ext4_read_file() **\n");
		ext4fs_close();
		return -1;
	}
	debugf("read %s ok, len : 0x%llx", filenm, len_read);
	ext4fs_close();
	return 0;
#else
	return -1;
#endif
}

int do_fs_file_write(char *mpart, char *filenm, void *buf, int len)
{
	/*do not write in uboot now*/
	return -1;
}

#ifdef CONFIG_PARTITION_UUIDS
int get_img_partition_uuid(char *part_name, char* uuid)
{
	int ret = 0;
	int dev_id = 0;
	char *ifname;
	disk_partition_t part_info;
	block_dev_desc_t *dev_desc;

	if (uuid == NULL) {
		return -1;
	}

	ifname = block_dev_get_name();
	if (0 == strcmp(part_name, "splloader")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART1);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART1);
	} else if (0 == strcmp(part_name, "splloader_bak")) {
		dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
		dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
	} else if (0 == strcmp(part_name, "uboot")) {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
		ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
		if (-1 == ret) {
			dev_id = get_devnum_hwpart(ifname, BOOT_PART2);
			dev_desc = get_dev_hwpart(ifname, dev_id, BOOT_PART2);
		}
	} else {
		dev_id = get_devnum_hwpart(ifname, USER_PART);
		dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
	}

	ret = get_partition_info_by_name(dev_desc, part_name, &part_info);
	strncpy(uuid, part_info.uuid, 37);
	debugf("part_name: %s, uuid: %s\n", part_name, uuid);

	return ret;
}
#endif

int common_write_backstage(char *part_name, uint32_t size, uint64_t offset, char *buf)
{
	int dev_id = 0;
	lbaint_t start = 0;
	lbaint_t blk_num = 0;
	uint64_t total_part_size = 0;
	block_dev_desc_t *dev_desc = NULL;
	int ret = 0;
	char *ifname;

	ifname = block_dev_get_name();

	dev_id = get_devnum_hwpart(ifname, USER_PART);
	dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
	if (0 != strcmp(part_name, local_part_info.name)) {
		ret = get_partition_info_by_name(dev_desc, part_name, &local_part_info);
	}

	/*invoker must guarantee that the size and offset aligned to the block size*/
	if (0 != size % local_part_info.blksz || 0 != offset % local_part_info.blksz) {
		errorf("input size or offset not aligned, size(0x%x), offset(0x%x)\n", size, offset);
		ret = -1;
	}

	blk_num = size / local_part_info.blksz;
	start = local_part_info.start + (offset / local_part_info.blksz);
	if (blk_num + start > local_part_info.size + local_part_info.start) {
		errorf("backstage write size overflow the total partition size\n");
		ret = -1;
	}

	if (-1 == ret)
		return -1;

	/*only user partition can use backstage write*/
	if (blk_num != dev_desc->backstage_block_write(dev_id, start, blk_num, buf))
		return -1;

	return 0;
}

int common_query_backstage(char *part_name, uint32_t size, char *buf)
{
	int dev_id = 0;
	lbaint_t blk_num = 0;
	block_dev_desc_t *dev_desc = NULL;
	char *ifname;

	ifname = block_dev_get_name();

	dev_id = get_devnum_hwpart(ifname, USER_PART);
	dev_desc = get_dev_hwpart(ifname, dev_id, USER_PART);
	if (0 != strcmp(part_name, local_part_info.name))
		return -1;

	blk_num = size / local_part_info.blksz;
	if (blk_num != dev_desc->backstage_write_query(dev_id, blk_num, buf))
		return -1;

	return 0;
}
#endif

#ifdef CONFIG_NAND_BOOT
extern int ubifs_init(void);
extern struct ubi_selected_dev cur_ubi;
extern int _get_mtd_partition_info(char *name, struct mtd_partition *part);

int uboot_ubi_read(struct ubi_volume_desc *desc, char *buf,
			   int offset, int size)
{
	int err, lnum, off, len, tbuf_size, i = 0;
	size_t count_save = size;
	void *tbuf;
	unsigned long long tmp;
	struct ubi_volume *vol = NULL;
	struct ubi_device *ubi = NULL;
	loff_t offp = offset;

	vol = desc->vol;
	ubi = desc->vol->ubi;

	//printf("read %i bytes from volume %d to %x(buf address)\n",
	       //(int) size, vol->vol_id, (unsigned)buf);

	if (vol->updating) {
		printf("updating");
		return -EBUSY;
	}
	if (vol->upd_marker) {
		printf("damaged volume, update marker is set");
		return -EBADF;
	}
	if (offp == vol->used_bytes)
		return 0;

	if (size == 0) {
		printf("Read [%lu] bytes\n", (unsigned long) vol->used_bytes);
		size = vol->used_bytes;
	}

	if (vol->corrupted)
		printf("read from corrupted volume %d", vol->vol_id);
	if (offp + size > vol->used_bytes)
		count_save = size = vol->used_bytes - offp;

	tbuf_size = vol->usable_leb_size;
	if (size < tbuf_size)
		tbuf_size = ALIGN(size, ubi->min_io_size);
	tbuf = malloc(tbuf_size);
	if (!tbuf) {
		printf("NO MEM\n");
		return -ENOMEM;
	}
	len = size > tbuf_size ? tbuf_size : size;

	tmp = offp;
	off = do_div(tmp, vol->usable_leb_size);
	lnum = tmp;
	do {
		if (off + len >= vol->usable_leb_size)
			len = vol->usable_leb_size - off;
		err = ubi_eba_read_leb(ubi, vol, lnum, tbuf, off, len, 0);
		if (err) {
			printf("read err %x\n", err);
			break;
		}
		off += len;
		if (off == vol->usable_leb_size) {
			lnum += 1;
			off -= vol->usable_leb_size;
		}

		size -= len;
		offp += len;

		memcpy(buf, tbuf, len);

		buf += len;
		len = size > tbuf_size ? tbuf_size : size;
	} while (size);
	free(tbuf);
	return err ? err : count_save - size;
}

static int _boot_ubi_attach_mtd(const char *mtdpart)
{
	struct mtd_device *dev;
	struct part_info *part;
	struct mtd_info *mtd;
	struct mtd_partition mtd_part;
	char mtd_dev[16];
	u8 pnum;
	int ret;

	ret = find_dev_and_part(mtdpart, &dev, &pnum, &part);
	if(ret){
		printf("--->main partition %s miss<---\n",mtdpart);
		return -1;
	}
	if(dev->id->type != MTD_DEV_TYPE_NAND){
		printf("mtd dev %s not a nand device!\n",mtdpart);
		return -1;
	}
	sprintf(mtd_dev, "%s%d", MTD_DEV_TYPE(dev->id->type), dev->id->num);
	mtd = get_mtd_device_nm(mtd_dev);

	memset(&mtd_part, 0, sizeof(mtd_part));
	mtd_part.name = mtdpart;
	mtd_part.size = part->size;
	mtd_part.offset = part->offset;
	add_mtd_partitions(mtd, &mtd_part, 1);
	mtd = get_mtd_device_nm(mtdpart);
	ret = ubi_attach_mtd_dev(mtd, UBI_DEV_NUM_AUTO, 0,CONFIG_MTD_UBI_BEB_LIMIT);
	if(ret<0){
		printf("--->ubi attach mtd %s failed<---\n",mtdpart);
	}
	return ret;
}


int nand_ubi_dev_init(void)
{
	int ret;
	static int initialized=0;
	static int dev_num=-1;

	if(!initialized){
		//init mtd & ubi devices
		ret = mtdparts_init();
		if(ret){
			printf("mtdparts init error...\n");
			return -1;
		}
		printf("ubi init start\n");
		ret = ubi_init();
		if(ret){
			printf("ubi init error...\n");
			return -1;
		}
		//ubi attach mtd dev, and get the new ubi dev num
		dev_num = _boot_ubi_attach_mtd(UBIPAC_PART);
		initialized = 1;
	}

	return dev_num;
}


int common_raw_read(char *part_name, uint64_t size, uint64_t offset, char *buf)
{
	int ubi_dev_num;
	int ret;
	nand_info_t *nand;
	struct mtd_partition mtd_part;
        struct ubi_volume_desc *vol;

	nand = _get_cur_nand();
        ubi_dev_num = nand_ubi_dev_init();

        if(ubi_dev_num < 0){
                //dev num can't be a negative
                printf("read failed...\n");
                return;
        }

	if(0 == strcmp(part_name,"splloader")) {
		ret = sprd_nand_read_spl(buf, nand, size);
		if (ret)
			return -1;
	} else if(0 == strcmp(part_name,"uboot")) {
		ret = _get_mtd_partition_info(part_name, &mtd_part);
		if (!ret)
			return -1;
		ret = nand_read_skip_bad(nand, 0, &size, NULL, mtd_part.size, buf);
		if (ret)
			return -1;
	}  else {
		vol = ubi_open_volume_nm(ubi_dev_num, part_name, UBI_READONLY);
		if (IS_ERR(vol)){
			printf("cannot open \"%s\", error %d", part_name, (int)PTR_ERR(vol));
			return -1;
		}
		uboot_ubi_read(vol, buf, offset, size);
        }

        return 0;
}

/**
 * erase the given mtd part.
 * return 0 in case of success.
 */
int sprd_mtd_part_erase(nand_info_t * nand, struct mtd_partition *mtd_part)
{
	int ret;
	nand_erase_options_t opts;

	memset(&opts, 0, sizeof(opts));
	opts.offset = mtd_part->offset;
	opts.length = mtd_part->size;
	opts.quiet = 0;
	debugf("erase offset %x ,size %x\n", opts.offset, opts.length);
	ret = nand_erase_opts(nand, &opts);
	if (ret)
		errorf("nand erase %s failure %d\n", mtd_part->name, ret);
	else
		debugf("erase OK\n");

	return ret;
}

int common_raw_write(char *part_name, uint64_t size, uint64_t updsize,
		     uint64_t offset, char *buf)
{
	nand_info_t *nand;
	int ret;
	uint64_t rsvd_bytes;
	struct mtd_partition mtd_part;
	struct ubi_volume_desc *vol;
	char *buf_read = NULL;

	nand = _get_cur_nand();
	debugf("write part %s \n", part_name);
	if (_get_mtd_partition_info(part_name, &mtd_part)) {
		if (size + offset > mtd_part.size || size == 0) {
			debugf("write size 0x%llx & offset 0x%llx is incompatible"
			       " set to partition size 0x%llx\n",
			       size, offset, mtd_part.size);
			size = mtd_part.size;
			offset = 0;
		} else {
			debugf("write size 0x%llx from offset 0x%llx\n",
			       size, offset);
		}

		ret = sprd_mtd_part_erase(nand, &mtd_part);
		if (ret) {
			errorf("mtd %s erase failed!\n", part_name);
			goto out;
		}

		if (strcmp(part_name, "splloader") == 0) {
			ret = sprd_nand_write_spl(buf, nand);
			if (ret)
				errorf("write spl fail\n");
			goto out;
		} else {
			ret = nand_write_skip_bad(nand,
						  mtd_part.offset + offset,
						  &size, NULL,
						  mtd_part.size, buf, 0);
			if (ret)
				errorf("mtd %s write failed!\n", part_name);
			goto out;
		}
	} else {
		if (!cur_ubi.ubi_initialized) {
			ret = fdl_ubi_dev_init();
			if(!ret) {
				errorf("attach ubi failed !\n");
				goto out;
			}
		}

		vol = ubi_open_volume_nm(cur_ubi.dev_num, part_name,
					 UBI_READWRITE);
		if (IS_ERR(vol)) {
			errorf("cannot open volume \"%s\", error %d\n",
			       part_name, (int)PTR_ERR(vol));
			ret = IS_ERR(vol);
			goto out;
		}
		rsvd_bytes = vol->vol->reserved_pebs * (cur_ubi.dev->leb_size -
						   vol->vol->data_pad);
		if (size == 0 || size + offset > rsvd_bytes) {
			debugf("write size 0x%llx & offset 0x%llx is incompatible"
			       " set to partition size 0x%llx\n",
			       size, offset, rsvd_bytes);
			size = rsvd_bytes;
			offset = 0;
		} else {
			debugf("write size 0x%llx from offset 0x%llx\n",
			       size, offset);
		}
		/*If offset is set, we have to read the previous offset data*/
		if (offset) {
			buf_read = malloc(offset);
			if (!buf_read) {
				errorf("buf_read malloc failed\n");
				ubi_close_volume(vol);
				ret = -ENOMEM;
				goto out;
			}
			ret = fdl_ubi_volume_read(cur_ubi.dev, part_name,
						  buf_read, offset, 0);
			if (offset != ret) {
				errorf("can not read 0x%llx data from vol %s"
				       " ret %d!!\n", offset, part_name, ret);
				ubi_close_volume(vol);
				ret = -ENOMEM;
				goto out;
			}
		}
		if (!updsize)
			updsize = offset + size;
		ret = fdl_ubi_volume_start_update(cur_ubi.dev, part_name, updsize);
		if (ret) {
			errorf("vol %s start update failed!\n", part_name);
			ubi_close_volume(vol);
			goto out;
		}
		if (offset) {
			ret = fdl_ubi_volume_write(cur_ubi.dev, part_name,
						   buf_read, offset);
			if (ret) {
				errorf("ubi volume write error %d!\n", ret);
				ubi_close_volume(vol);
				goto out;
			}
		}
		ret = fdl_ubi_volume_write(cur_ubi.dev, part_name, buf, size);
		if (ret) {
			errorf("ubi volume write error %d!\n", ret);
			ubi_close_volume(vol);
			goto out;
		}
		ubi_close_volume(vol);
	}

out:
	if(buf_read != NULL)
		free(buf_read);

	return ret;
}

int common_raw_erase(char *part_name, uint64_t size, uint64_t offset)
{

}



int common_repartition(disk_partition_t *partitions, int parts_count)
{

}

int32_t common_get_lba_size(void)
{

}

int do_fs_file_read(char *mpart, char *filenm, void *buf, int len)
{
#if 1

	int ret=-1;
	static int is_ubifs_init = 0;
	if(is_ubifs_init == 0){
		ubifs_init();
		is_ubifs_init = 1;
	}


	ret = uboot_ubifs_mount(mpart);
	if(ret){
		printf("do_fs_file_read:mount %s failed!\n",mpart);
		return ret;
	}
	ret = ubifs_load(filenm, buf, len);
	if(ret)
		printf("do_fs_file_read:file %s not found!\n", filenm);
	return ret;
	#endif
}
int do_fs_file_write(char *mpart, char *filenm, void *buf, int len)
{
	/*do not write in uboot now*/
	return -1;
}





int do_raw_data_write(char *part, u32 updsz, u32 size, u32 off, char *buf)
{
	int ret =-1;
	int i =0;
	int ubi_dev;
	u8 pnum;
	loff_t offset;
	size_t length,wlen=0;
	struct mtd_device *dev;
	struct mtd_info *nand;
	struct part_info *mtdpart;
	struct ubi_volume_desc *vol;
	nand_erase_options_t opts;

try_mtd:
	ret = find_dev_and_part(part, &dev, &pnum, &mtdpart);
	if (ret)
		goto try_ubi;
	else if (dev->id->type != MTD_DEV_TYPE_NAND)
		goto end;

	offset = mtdpart->offset+off;
	length = size;
	nand = &nand_info[dev->id->num];
	memset(&opts, 0x0, sizeof(opts));
	opts.offset = offset;
	opts.length = length;
	opts.quiet = 1;
	opts.spread = 1;

	ret = nand_erase_opts(nand, &opts);
	if (ret) {
		printf("erase %s failed.\n",part);
		goto end;
	}
	//write spl part with header
	if(strcmp(part, "splloader")==0){
		ret = sprd_nand_write_spl(buf, nand);
		goto end;
	}

	while((size != wlen) && (i++<0xff)) {
		ret = nand_write_skip_bad(nand, offset, &length, NULL, mtdpart->size, buf, 0);
		wlen += length;
		buf += length;
		offset += length;

		if(ret){
			//mark a block as badblock
			printf("nand write error %d, mark bad block 0x%llx\n",ret,offset&~(nand->erasesize-1));
			nand->_block_markbad(nand,offset &~(nand->erasesize-1));
		}
	}
	goto end;

try_ubi:
	ubi_dev = nand_ubi_dev_init();
	if (ubi_dev<0) {
		printf("do_raw_data_write: ubi init failed.\n");
		return ret;
	}
	vol = ubi_open_volume_nm(ubi_dev, part, UBI_READWRITE);
	if (IS_ERR(vol)) {
		printf("cannot open \"%s\", error %d",
			  part, (int)PTR_ERR(vol));
		return ret;
	}

	//set total size to be updated in this volume
	if (updsz) {
		ret = ubi_start_update(vol->vol->ubi, vol->vol, updsz);
		if (ret < 0) {
			printf("Cannot start volume %s update\n",part);
			return ret;
		}
	}

	ret = ubi_more_update_data(vol->vol->ubi, vol->vol, buf, size);
	if (ret < 0) {
		printf("Couldnt write data in volume %s\n",part);
		return ret;
	}
	ret = 0;
	ubi_close_volume(vol);

end:
	if (ret)
		printf("do_raw_data_write error.\n");
	return ret;
}

#endif


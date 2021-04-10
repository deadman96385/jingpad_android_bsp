/**
 * libf2fs.c
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *             http://www.samsung.com/
 *
 * Dual licensed under the GPL or LGPL version 2 licenses.
 */
#define _LARGEFILE64_SOURCE
#include <common.h>
#if 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#ifdef HAVE_MNTENT_H
#include <mntent.h>
#endif
#include <time.h>
#ifndef ANDROID_WINDOWS_HOST
#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/ioctl.h>
#endif
#ifdef HAVE_LINUX_HDREG_H
#include <linux/hdreg.h>
#endif
#endif

#include "../include/f2fs_fs.h"

struct f2fs_configuration c;
#if 0
static void f2fs_print_buffer(unsigned char *buf, int len)
{
        int i;
        char msg[500];
        char item[40];

        for (i = 0; i < len; i++){
                if(i % 16 == 0)
                        sprintf(msg, "%02X: ", i);

                sprintf(item,"%02X ",*(buf + i));
                strcat(msg, item);
                if(i % 16 == 15) {
                        sprintf(item, "\n");
                        strcat(msg, item);
                        printf("%s", msg);
                }
        }
        if (i % 16 != 0) {
                sprintf(item, "\n");
                strcat(msg, item);
                printf("%s", msg);
        }
        printf("\n");
}
#endif

int dev_read(void *buf, __u64 offset, size_t len)
{
	int ret = 0;
	if ( offset + len <= c.cache_buffer_size) {
		memcpy(buf, c.cache_buffer + offset, len);
	} else {
		MSG(3, "dev_read1: @0x%llx, len=%ld\n", offset, len);
		ret = c.read(c.device_handle, (__u64)len, offset, buf);
		//f2fs_print_buffer(buf, len < 16 ? len : 16);
	}
	return ret;
}

int dev_write(void *buf, __u64 offset, size_t len)
{
	__u64 dirty_end;
	int ret = 0;
	dirty_end = offset + len;
	if (dirty_end <= c.cache_buffer_size) {
		memcpy(c.cache_buffer + offset, buf, len);
		if (dirty_end > c.cache_buffer_dirty_end)
			c.cache_buffer_dirty_end = dirty_end;

	} else {
		MSG(3, "dev_write1: @0x%llx, len=%ld\n", offset, len);
		ret = c.write(c.device_handle, (__u64)len, offset, buf);
		//f2fs_print_buffer(buf, len < 16 ? len : 16);
	}
	return ret;
}

int dev_write_block(void *buf, __u64 blk_addr)
{
	return dev_write(buf, blk_addr << F2FS_BLKSIZE_BITS, F2FS_BLKSIZE);
}


int dev_read_block(void *buf, __u64 blk_addr)
{
	return dev_read(buf, blk_addr << F2FS_BLKSIZE_BITS, F2FS_BLKSIZE);
}

int f2fs_fsync_device(void)
{
	//no buffer cache in uboot
#if 0
	int i;

	for (i = 0; i < c.ndevs; i++) {
		if (fsync(c.devices[i].fd) < 0) {
			MSG(0, "\tError: Could not conduct fsync!!!\n");
			return -1;
		}
	}
#endif
	return 0;
}

int f2fs_finalize_device(void)
{
	int ret = 0;
#if 0
	for (i = 0; i < c.ndevs; i++) {
#ifndef ANDROID_WINDOWS_HOST
		ret = fsync(c.devices[i].fd);
		if (ret < 0) {
			MSG(0, "\tError: Could not conduct fsync!!!\n");
			break;
		}
#endif
		ret = close(c.devices[i].fd);
		if (ret < 0) {
			MSG(0, "\tError: Failed to close device file!!!\n");
			break;
		}
		free(c.devices[i].path);
	}
	close(c.kd);
#endif
	return ret;
}

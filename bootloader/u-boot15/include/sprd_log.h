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
 * GNU General Public License for more details.
 */

#ifndef __SPRD_LOG_H__
#define __SPRD_LOG_H__
#ifdef CONFIG_LOG_2_SD
#include "../common/loader/sysdump.h"
#endif

#define LOG_BUFFER_START_ADDR   ALIGN(LOG_BUFFER_ADDR + sizeof(LOG_BUFFER), 8)
#define LOG_BUFFER_SIZE         0x040000 /* 256KB */

#define LOG_FOLDER_NUM		3
#define LOG_FOLDER_NAME		"ylog/ap/uboot"
#define LOG_AUTO_TEST		"ylog/uboot/uboot_log_auto_test.txt"

#define UBOOT_LOG_PARTITION	"uboot_log"
#define LOG_HEAD_MAGIC	        0x0000abcd
#define LOG_VERSION		        1
#define LOG_HEADER_SIZE	        512
#define LOG_BODY_NUM		6
#define LOG_BODY_SIZE		LOG_BUFFER_SIZE		/* 256KB */

#define SUCESS		1
#define FAILED		0

#define START_LOG_PARTITON_OFFSET	0
#define DOWNLD_LOG_PARTITION_OFFSET	0x200000	/* 2MB offset */

typedef enum {
	START_LOG_TYPE = 0,
	DOWNLD_LOG_TYPE
} LOG_TYPE_T;

typedef struct _LOG_BUFFER {
	uchar* addr;
	uchar* pointer;
	uint32_t size;
	uint32_t used;
	uint32_t spare;
	uint32_t status;
} LOG_BUFFER;

typedef struct _LOG_BODY {
	uint32_t p_offset;	/* offset in uboot log partiton */
	uint32_t b_offset;	/* offset in log body, it also indicates the log size in emmc */
	uint32_t size;
} LOG_BODY;

typedef struct _LOG_PARTITION_HEADER {
	uint32_t magic;
	uint32_t len;
	uint32_t boot_count;
	uint32_t body_num;
	uint32_t type;
	uint32_t next_body;
	LOG_BODY body[LOG_BODY_NUM];
} LOG_PARTITION_HEADER;

typedef struct _LOG_STRUCT {
	int32_t flag;
	uint64_t log_type_p_offset;
	LOG_PARTITION_HEADER log_par_hdr;
} LOG_STRUCT;

void flush_log_buffer(void);

#define init_write_log()
#define reinit_write_log()
#define write_log()
#define write_log_last()

#ifdef CONFIG_SPRD_LOG
#ifdef DEBUG
# if defined(CONFIG_LOG_2_EMMC)
#define init_write_log() do {		\
	init_log_struct();		\
	init_log_partition_hdr();	\
	flush_log_buffer();		\
} while(0)

#define reinit_write_log() do {		\
	init_log_partition_hdr();	\
	flush_log_buffer();		\
} while(0)

#define write_log() flush_log_buffer()
#define write_log_last() flush_log_buffer()
# elif defined(CONFIG_LOG_2_SD)
#define write_log_last() do {		\
	extern int sd_fs_type;		\
	puts("SD:   ");			\
	if (init_mmc_fat(&sd_fs_type)) {	\
		debugf("ERROR: init_mmc_fat,sd_fs_type=%d.\n", sd_fs_type);	\
	}				\
	flush_log_buffer();		\
} while(0)

# endif

#else

# if defined(CONFIG_LOG_2_EMMC)
#define write_log_last() do {		\
	init_log_struct();		\
	init_log_partition_hdr();	\
	flush_log_buffer();		\
} while(0)
# endif

#endif
#endif
#endif //__SPRD_LOG_H__

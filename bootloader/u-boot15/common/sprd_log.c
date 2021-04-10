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
#include <rtc.h>
#include <boot_mode.h>
#include <common.h>
#include <linux/input.h>
#include <linux/mtd/mtd.h>
#include <linux/sizes.h>
#include <asm/arch/check_reboot.h>
#include <mmc.h>
#include <fat.h>
#include <exfat.h>
#include <chipram_env.h>
#include <sprd_common_rw.h>

#ifdef CONFIG_SPRD_LOG
extern LOG_BUFFER *p_log_buffer;
#endif

#if defined(CONFIG_LOG_2_SD)
int sd_fs_type;  /* file system type on sd card */

void write_log_to_mmc(char *filename, int fs_type,
	void *memaddr, unsigned long memsize)
{
	int ret = 0;
	unsigned long actwrite = 0;

	debugf("writing 0x%lx bytes to sd file %s\n",
		memsize, filename);

	if (fs_type==FS_FAT32)
		ret = file_fat_write(filename, memaddr, 0, memsize, &actwrite);
	else if (fs_type==FS_EXFAT)
		ret = file_exfat_write(filename, memaddr, memsize);
	else
		ret = -1;

	if (ret != 0) {
		debugf("write file %s to SD Card error, and ret = %d !!!\n", filename, ret);
	}

	return;
}


/*
 * Flush log buffer to sd/emmc/nand etc
 */
void flush_log_buffer()
{
	struct rtc_time tm;
	dir_entry *dentptr = NULL;
	char fnbuf[72] = {0}, fnbuf_rename[72] = {0};
	int i, j, ret;
	int auto_test_flag = 0;

	if (sd_fs_type == FS_FAT32) {
		int mod, key_code;
		unsigned long max_size = 0;

		debugf("FileSystem is FAT32 !!!\n");
		max_size = p_log_buffer->size;

		mod = fat_checksys(max_size);
		if (mod &(FSFATAL | FSNOSPACE)) {
			int nospace_flag = 1;
			if (mod & FSFATAL) {
				debugf("\nHello Baby: SD Card is demaged !!!");
			}
			else if (mod & FSNOSPACE) {
				for (i = 1; i <= LOG_FOLDER_NUM; i++) {
					sprintf(fnbuf, LOG_FOLDER_NAME"/%d", i);
					fnbuf[strlen(fnbuf)] = '\0';
					dentptr = check_folder_flag(fnbuf);
					if(dentptr == NULL)
						break;
				}
				if (i != 1) {
					for(j = i; j != 1;) {
						sprintf(fnbuf, LOG_FOLDER_NAME"/%d", --j);
						fnbuf[strlen(fnbuf)] = '\0';
						ret = delete_folder(fnbuf);
						if(ret == -1) {
							debugf("ERROR: delete files or folder failed !!!\n");
							goto FINISH;
						}
						mod = fat_checksys(max_size);
						if (!(mod & FSNOSPACE)) {
							nospace_flag = 0;
							break;
						}
					}
				}
				if (nospace_flag) {
					debugf("\nHello Baby: SD Card have not enough space !!!");
				}
			}
			if (nospace_flag) {
				debugf("need to format SD Card !!!\n");
				goto FINISH;

			}
		}

		if(do_new_folder(LOG_FOLDER_NAME)) {
			debugf("ERROR: creat %s folder failed !!!\n", LOG_FOLDER_NAME);
			goto FINISH;
		}

		if(check_folder_flag(LOG_AUTO_TEST)) {
			auto_test_flag = 1;
			debugf("Now has existed uboot_log_auto_test.txt!!!\n");
		}

		for (i = 1; i <= LOG_FOLDER_NUM; i++) {
			sprintf(fnbuf, LOG_FOLDER_NAME"/%d", i);
			fnbuf[strlen(fnbuf)] = '\0';
			dentptr = check_folder_flag(fnbuf);
			if(dentptr == NULL)
				break;
		}

		if (i > LOG_FOLDER_NUM) {
			debugf("there existed %d history log !!!\n", LOG_FOLDER_NUM);
			i --;
			sprintf(fnbuf, LOG_FOLDER_NAME"/%d", i);
			fnbuf[strlen(fnbuf)] = '\0';
			ret = delete_folder(fnbuf);
			if(ret == -1) {
				debugf("ERROR: delete files or folder failed !!!\n");
				goto FINISH;
			}
		}

		for(j = i - 1; j > 0 && i != 1; j = j - 2) {
				sprintf(fnbuf, LOG_FOLDER_NAME"/%d", j++);
				fnbuf[strlen(fnbuf)] = '\0';
				sprintf(fnbuf_rename, LOG_FOLDER_NAME"/%d", j);
				fnbuf_rename[strlen(fnbuf_rename)] ='\0';
				debugf("rename folder from %s to %s !!!\n", fnbuf, fnbuf_rename);
				ret = rename_folder(fnbuf, fnbuf_rename);
				if (ret == -1) {
					debugf("ERROR: rename folder failed !!!\n");
					break;
				}
			}

		sprintf(fnbuf, LOG_FOLDER_NAME"/%d", 1);

		if(do_new_folder(fnbuf)) {
			debugf("ERROR: creat %s folder failed !!!\n", fnbuf);
			goto FINISH;
		}
	}
	else if (sd_fs_type == FS_EXFAT) {
		int mod, key_code;
		unsigned long max_size;

		debugf("FileSystem is exFAT !!!\n");
		max_size = p_log_buffer->size;
		debugf("ExFAT max space size is %lx\n",max_size);

		mod = exfat_checksys(max_size);
		if (mod & FSSMSIZE) {
			debugf("SD card volume size is smaller then dumped size. Skip write !!!\n");
			goto FINISH;
		}

		if (mod &(FSFATAL | FSNOSPACE)) {
			if (mod & FSFATAL)
				debugf("\nHello Baby: SD Card is demaged !!!");
			else if (mod & FSNOSPACE)
				debugf("\nHello Baby: SD Card has not enough space !!!");

			debugf("\npress volumedown to format SD Card !!!\n");
		}
	}
	else {
		debugf("Invalid file system... Write will be skipped !!!\n");
		goto FINISH;
	}

	sprintf(fnbuf, LOG_FOLDER_NAME"/1/uboot_log_%04d_%02d_%02d_%02d_%02d_%02d.txt", \
			tm.tm_year, tm.tm_mon, tm.tm_mday, \
			tm.tm_hour, tm.tm_min, tm.tm_sec);

	debugf("time is %04d.%02d.%02d_%02d:%02d:%02d\n", tm.tm_year, tm.tm_mon, \
			tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	write_log_to_mmc(fnbuf, sd_fs_type,
			(uchar *)p_log_buffer->addr, p_log_buffer->used);

FINISH:
	debugf ("Write  finish or happen abnormally!!!\n");
#if (defined CONFIG_X86) && (defined CONFIG_MOBILEVISOR)
		reset_to_normal(CMD_NORMAL_MODE);
#endif

	return;
}

#elif defined(CONFIG_LOG_2_EMMC)
LOG_STRUCT log_st;

void init_log_struct()
{
	memset(&log_st, 0, sizeof(LOG_STRUCT));
}

int init_log_partition_hdr()
{
	int i;
	int cur_body; /* current log body */
	int log_type;
	uint64_t size;
	uint64_t offset;
	uchar hdr_buf[LOG_HEADER_SIZE];
	LOG_PARTITION_HEADER *p_hdr=hdr_buf;

	memset(hdr_buf, 0, sizeof(hdr_buf));

	/* the same as do_role() function in  cmd_role.c */
#ifdef CONFIG_ZEBU
	boot_mode_t boot_role = BOOTLOADER_MODE_LOAD;
#else
	boot_mode_t boot_role = get_boot_role();
#endif

	log_type = 0;
	switch(boot_role) {
		case BOOTLOADER_MODE_DOWNLOAD:
		log_type = DOWNLD_LOG_TYPE;
		log_st.log_type_p_offset = DOWNLD_LOG_PARTITION_OFFSET;
			break;
		case BOOTLOADER_MODE_LOAD:
		log_type = START_LOG_TYPE;
		log_st.log_type_p_offset = START_LOG_PARTITON_OFFSET;
			break;
		default :
			printf("unkown uboot role ,nothing to do in preboot\n");
		log_st.flag = FAILED;
		return -1;
	}

	debugf("uboot role type %d\n", log_type);

	if (0 != common_raw_read(UBOOT_LOG_PARTITION, (uint64_t)LOG_HEADER_SIZE, log_st.log_type_p_offset, hdr_buf)) {
		errorf("read error\n");
		log_st.flag = FAILED;
		return -1;
	}

	if(p_hdr->magic != LOG_HEAD_MAGIC || p_hdr->next_body >= LOG_BODY_NUM) {
		debugf("reset log partition header\n");
		p_hdr->magic = LOG_HEAD_MAGIC;
		p_hdr->len = LOG_HEADER_SIZE;
		p_hdr->boot_count = 1;
		p_hdr->body_num = LOG_BODY_NUM;
		p_hdr->type = log_type;
		p_hdr->next_body = 1;

		for(i = 0; i < LOG_BODY_NUM; i++) {
			p_hdr->body[i].p_offset =  LOG_HEADER_SIZE + i *LOG_BODY_SIZE;
			p_hdr->body[i].b_offset = 0;
			p_hdr->body[i].size = LOG_BODY_SIZE;	//the same as buffer size
		}

		if (0 != common_raw_write(UBOOT_LOG_PARTITION, (uint64_t)LOG_HEADER_SIZE, (uint64_t)0, log_st.log_type_p_offset, hdr_buf)) {
			errorf("write error\n");
			log_st.flag = FAILED;
			return -1;
		}
	}else {
		if(log_st.flag == SUCESS) {
			printf("%s(): log partiton has been initialied!\n",__func__);
			return 0;
		}

		/* reset the body offset  */
		p_hdr->body[p_hdr->next_body].b_offset = 0;

		p_hdr->boot_count += 1;
		p_hdr->next_body += 1;
		if(p_hdr->next_body == LOG_BODY_NUM)
		p_hdr->next_body = 0;
	}

	cur_body = p_hdr->next_body - 1;
	if(cur_body == -1)
		cur_body = LOG_BODY_NUM - 1;

	size = (uint64_t)p_hdr->body[cur_body].size;
	offset = (uint64_t)p_hdr->body[cur_body].p_offset;
	if (0 != common_raw_erase(UBOOT_LOG_PARTITION, size, log_st.log_type_p_offset + offset)) {
		errorf("erase error\n");
		log_st.flag = FAILED;
		return -1;
	}

	memcpy((void *)&log_st.log_par_hdr, (void *)p_hdr, sizeof(LOG_PARTITION_HEADER));
	log_st.flag = SUCESS; /* set sucess flag */
	printf("init log partition header success on %d times bootup\n", p_hdr->boot_count);

	return 0;
}

void flush_log_buffer()
{
	int cur_body; /* current log body */
	uint32_t tmp_b_offset;
	int64_t buf_size;
	uint64_t p_offset;
	uchar hdr_buf[LOG_HEADER_SIZE];
	uchar *buf;
	LOG_BUFFER *p_log;
	LOG_PARTITION_HEADER *p_hdr;
	LOG_BODY *body;

	if( log_st.flag != SUCESS) {
		return;
	}

	p_hdr = &log_st.log_par_hdr;
	cur_body = p_hdr->next_body - 1;
	if(cur_body == -1)
		cur_body = LOG_BODY_NUM - 1;

	body = &p_hdr->body[cur_body];
	p_log = p_log_buffer;

	buf = p_log->addr + body->b_offset;
	buf_size = p_log->used - body->b_offset;
	if(buf_size <= 0) /* there is no more log in buf */
		return;

	p_offset = body->p_offset + body->b_offset;
	tmp_b_offset = body->b_offset;

	body->b_offset = p_log->used; /* must place this sentence before any printf until wirte to emmc */

/*
    printf("log buffer used:%d, current body:%d, body b_offset:%d, body p_offset:%d, buf_size:%lld, final p_offset:%lld\n",\
        p_log->used, cur_body,tmp_b_offset, body->p_offset, buf_size, log_st.log_type_p_offset + p_offset);
*/
	/* write log */
	if (0 != common_raw_write(UBOOT_LOG_PARTITION, (uint64_t)buf_size, (uint64_t)0, log_st.log_type_p_offset + p_offset, buf)) {
		errorf("write log 2 emmc failed\n");
		return;
	}

	memset((void *)hdr_buf, 0, LOG_HEADER_SIZE);
	memcpy((void *)hdr_buf, p_hdr, sizeof(LOG_PARTITION_HEADER));
	/* write back to header */
	if (0 != common_raw_write(UBOOT_LOG_PARTITION, (uint64_t)LOG_HEADER_SIZE, (uint64_t)0, log_st.log_type_p_offset, hdr_buf)) {
		errorf("write header 2 emmc failed\n");
		return;
	}

//    printf("%s(): write log 2 emmc sucess!\n",__func__);
}
#endif


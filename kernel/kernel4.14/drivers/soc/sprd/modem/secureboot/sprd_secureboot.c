/*
 * SPRD verify orca modem process in AP side.
 *
 * Copyright (C) 2020 Spreadtrum Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 of
 * the License as published by the Free Software Foundation.
 *
 * This program is used to verify orca modem in AP side for
 * Spreadtrum SoCs.
 */
#include "sprd_verify.h"
#include "sprd_secureboot.h"
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/string.h>

u8 mode_flag;
u8 rotpk_hash[HASH_BYTE_LEN + CRC_16];
static u8 hash_key[HASH_BYTE_LEN];
static u8 cmdline_str[4 * HASH_BYTE_LEN + 2 * CRC_16];

static int __init scanner_hash(char *str)
{
	u8 i;

	if (str) {
		for (i = 0; i < 4 * HASH_BYTE_LEN + 2 * CRC_16; i++) {
			cmdline_str[i] = (u8)(*str);
			str++;
		}
	}
	return 0;
}
__setup("hash=", scanner_hash);

int sprd_check_secure_part(u8 *partition_name)
{
	int i = 0;

	do {
		if (strcmp(secure_modem[i], partition_name) == 0)
			return i;
		i++;
	} while (secure_modem[i] != 0);
	return -ERANGE;
}

static u8 hexchar_to_int(u8 c)
{
	if (c > '9')
		return (c - '7');
	else
		return (c - '0');
}

int sprd_image_verify(struct kbc_load_table_s  *p_table)
{
	u8 i, high_4bit, low_4bit;
	void *vaddr;
	u32 data_len;
	int ret = 0;

	if (!p_table->image_cnt)
		return -ENOENT;

	for (i = 0; i < HASH_BYTE_LEN; i++) {
		high_4bit = hexchar_to_int(cmdline_str[2 * i]) << 4;
		low_4bit = hexchar_to_int(cmdline_str[2 * i + 1]);
		hash_key[i] = high_4bit | low_4bit;
	}

	for (i = 0; i < HASH_BYTE_LEN + CRC_16; i++) {
		high_4bit = hexchar_to_int(cmdline_str[2 * (i +
			HASH_BYTE_LEN)]) << 4;
		low_4bit = hexchar_to_int(cmdline_str[2 * (i +
			HASH_BYTE_LEN) + 1]);
		rotpk_hash[i] = high_4bit | low_4bit;
	}

	for (i = 0; i < MAX_MODEM_NUM; i++) {
		if (!p_table->image[i].img_name)
			continue;
		if (strcmp(p_table->image[i].img_name, "modem") == 0)
			mode_flag = MODEM_BLOCK;
		else if (strcmp(p_table->image[i].img_name, "v3phy") == 0)
			mode_flag = V3PHY_BLOCK;
		else if (strcmp(p_table->image[i].img_name, "nrphy") == 0)
			mode_flag = NRPHY_BLOCK;
		else if (strcmp(p_table->image[i].img_name, "nrdsp1") == 0)
			mode_flag = NRDSP1_BLOCK;

		if ((strcmp(p_table->image[i].img_name, "v3phy") == 0) ||
		     (strcmp(p_table->image[i].img_name, "nrphy") == 0) ||
		     (strcmp(p_table->image[i].img_name, "nrdsp1") == 0)) {
			vaddr = memremap(p_table->image[i].img_addr,
				p_table->image[i].img_len, MEMREMAP_WB);
			if (!vaddr)
				return -ENOMEM;
			data_len = sprd_get_img_size(vaddr);
			ret = sprd_verify_img_kbc(hash_key,
				(u8 *)vaddr + SECBOOT_HEAD_SIZE, data_len);
			memunmap(vaddr);
			if (ret)
				return ret;
		}

		if (strcmp(p_table->image[i].img_name, "modem") == 0) {
			vaddr = memremap(p_table->image[i].img_addr,
				p_table->image[i].img_len, MEMREMAP_WB);
			if (!vaddr)
				return -ENOMEM;
			data_len = sprd_get_modem_size(vaddr);
			ret = sprd_verify_modem(hash_key,
				(u8 *)vaddr, data_len);
			memunmap(vaddr);
			if (ret) {
				pr_err("verify modem failed\r\n");
				return ret;
			}
		}
	}
	pr_info("secboot verify success\n");
	return ret;
}


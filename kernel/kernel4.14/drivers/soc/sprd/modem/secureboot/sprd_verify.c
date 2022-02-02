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
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/nvmem-consumer.h>
#include "sprd_verify.h"
#include "../crypto/sprd_crypto.h"
#include "../crypto/sprd_sha256.h"
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/cdev.h>

#define TRUSTED_FIRMWARE 1
#define NON_TRUSTED_FIRMWARE 0

static dev_t dev_num;
static struct cdev v_dev;
static struct class *verify_class;
static struct nvmem_device *efuse;
static u32 img_rollback_version;

struct data_block_header_t {
	u32 type_flags;
	u32 offset;
	u32 length;
};

static const u16 crc16_verify_table[256] = {
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
	0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
	0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
	0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
	0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
	0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
	0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
	0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
	0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
	0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
	0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
	0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
	0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
	0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
	0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
	0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
	0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
	0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
	0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
	0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
	0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
	0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
	0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
	0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
	0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
	0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
	0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
	0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
	0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
	0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
	0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
	0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
};

static u16 crc16_verify(u8 *ptr, u8 len)
{
	u16 crc_val = 0;
	u8 tmp;

	if (!ptr) {
		pr_err("error:crc16 ptr is null\n");
		return 0;
	}

	while (len-- != 0) {
		tmp = (u8)(crc_val / 256);
		crc_val = crc_val << 8;
		crc_val ^= crc16_verify_table[tmp ^ (*ptr)];
		ptr++;
	}
	return crc_val;
}

void cal_sha256(u8 *input, u32 bytes_num, u8 *output)
{
	if (input && output)
		sha256_csum_wd(input, bytes_num, output, 0);
	else
		pr_err("\r\tthe pointer is error,pls check it\n");
}

int check_and_update_version(u32 block, u32 certversion)
{
	int ret;

	if (!efuse) {
		pr_err("get efuse handle error!\n");
		return -ENODEV;
	}
	nvmem_device_read(efuse, (block - 2) * 4, 4, &img_rollback_version);
	if (certversion < img_rollback_version) {
		pr_err("error:block%d rollback_ver = %d  cert_ver = %d\n",
			block, img_rollback_version, certversion);
		ret = -ERANGE;
	} else {
		if (certversion > img_rollback_version)
			nvmem_device_write(efuse,
			(block - 2) * 4, 1, &certversion);
		ret = 0;
	}
	return ret;
}

extern unsigned char mode_flag;
int sprd_anti_rollback(u32 certtype, u32 certversion)
{
	int ret;

	if (certtype != NON_TRUSTED_FIRMWARE)
		return -EBADF;

	switch (mode_flag) {
	case MODEM_BLOCK:
		mode_flag = 0;
		ret = check_and_update_version(MODEM_BLOCK, certversion);
		break;

	case V3PHY_BLOCK:
		mode_flag = 0;
		ret = check_and_update_version(V3PHY_BLOCK, certversion);
		break;

	case NRPHY_BLOCK:
		mode_flag = 0;
		ret = check_and_update_version(NRPHY_BLOCK, certversion);
		break;

	case NRDSP1_BLOCK:
		mode_flag = 0;
		ret = check_and_update_version(NRDSP1_BLOCK, certversion);
		break;

	default:
		mode_flag = 0;
		ret = -EINVAL;
		break;
	}
	return ret;
}

int sprd_verify_cert(u8 *hash_key_precert, u8 *hash_data, u8 *certptr)
{
	int ret;
	u8 certtype = *certptr;
	u8 temphash_data[HASH_BYTE_LEN];
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;
	sprd_rsa_pubkey_t pubkey;
	sprd_rsa_padding_t padding;
	int result;
	u8 certhash[HASH_BYTE_LEN];
	struct sprd_contentcert *curcertptr;

	padding.type = SPRD_RSASSA_PSS;
	padding.pad.rsassa_pss.type = SPRD_CRYPTO_HASH_SHA256;
	padding.pad.rsassa_pss.mgf1_hash_type = SPRD_CRYPTO_HASH_SHA256;
	padding.pad.rsassa_pss.salt_len = 32;

	if (certtype == CERTTYPE_CONTENT) {
		curcertptr = (struct sprd_contentcert *)certptr;
		cal_sha256((u8 *) &(curcertptr->pubkey), SPRD_RSAPUBKLEN,
			temphash_data);

		if (memcmp(hash_data, curcertptr->hash_data, HASH_BYTE_LEN)) {
			pr_err("<pss>cmp hash_data diffent\r\n");
			return -EFAULT;
		}
		if (memcmp(hash_key_precert, temphash_data, HASH_BYTE_LEN)) {
			pr_err("<pss>cmp hash key diffent\r\n");
			return -EFAULT;
		}
		pubkey.n = curcertptr->pubkey.mod;
		pubkey.n_len = (curcertptr->pubkey.keybit_len) >> 3;
		pubkey.e = (u8 *) &(curcertptr->pubkey.e);
		pubkey.e_len = 4;

		cal_sha256(curcertptr->hash_data, CNTCERT_HASH_LEN,
			certhash);
		err = sprd_rsa_verify((const sprd_rsa_pubkey_t *)(&pubkey),
			certhash, HASH_BYTE_LEN,
			(const u8 *)(curcertptr->signature),
			pubkey.n_len, padding, &result);

		if (err != SPRD_CRYPTO_SUCCESS) {
			pr_err("\n<pss>RSA verify err fail(%08x)\n", err);
			return -EFAULT;
		}

		if (result != SPRD_VERIFY_SUCCESS) {
			pr_err("\n<pss>RSA verify err result(%08x)\n", result);
			return -EFAULT;
		}

		ret = sprd_anti_rollback(curcertptr->type, curcertptr->version);
	} else {
		pr_err("<pss>invalid cert type %d!!", certtype);
		ret = -EINVAL;
	}

	return ret;
}

u32 sprd_get_img_size(u8 *buf)
{
	struct sys_img_header *imghdr = (struct sys_img_header *) buf;

	return imghdr->img_size;
}

u32 sprd_get_modem_size(u8 *buf)
{
	struct sys_img_header *imghdr = (struct sys_img_header *) buf;

	return imghdr->firmware_size;
}

u8 *sprd_get_cert_addr_kbc(u8 *buf, u32 imgSize)
{
	u8 *cert_addr;

	cert_addr = buf + imgSize + sizeof(struct signed_img_header);
	return cert_addr;
}

int sprd_verify_modem(u8 *hash_key_precert, u8 *imgbuf, u32 imgsize)
{
	u8 *code_addr;
	u8 *curcertptr;
	u8 soft_hash_data[HASH_BYTE_LEN];

	code_addr = imgbuf + sizeof(struct sys_img_header);
	cal_sha256(code_addr, imgsize, soft_hash_data);
	curcertptr = imgbuf + sizeof(struct sys_img_header) + imgsize
		+ sizeof(struct signed_img_header);
	return sprd_verify_cert(hash_key_precert, (u8 *)soft_hash_data,
		curcertptr);
}

int sprd_verify_img_kbc(u8 *hash_key_precert, u8 *imgbuf, u32 imgsize)
{
	u8 soft_hash_data[HASH_BYTE_LEN];
	u8 *curcertptr;

	memset(soft_hash_data, 0xff, HASH_BYTE_LEN);
	cal_sha256(imgbuf, imgsize, soft_hash_data);
	curcertptr = sprd_get_cert_addr_kbc(imgbuf, imgsize);
	return sprd_verify_cert(hash_key_precert, (u8 *)soft_hash_data,
		curcertptr);
}

static const struct of_device_id sprd_verify_of_match[] = {
	{ .compatible = "sprd,orca-verify", },
	{ }
};

static int efuse_write_and_check(u32 block, u32 write_data)
{
	u32 read_data = 0, read_org = 0;

	nvmem_device_read(efuse, (block - 2) * 4, 4, &read_org);
	nvmem_device_write(efuse, (block - 2) * 4, 4, &write_data);
	nvmem_device_read(efuse, (block - 2) * 4, 4, &read_data);

	if ((read_org | write_data) != read_data)
		return -EFAULT;

	return 0;
}

static int write_rotpk_blocks(u32 start_id, u32 end_id, u32 *pwrite_data)
{
	int ret;
	u32 block_id;
	u32 *write_ptr = pwrite_data;

	for (block_id = start_id; block_id <= end_id; block_id++) {
		ret = efuse_write_and_check(block_id, *write_ptr);
		if (ret)
			return ret;
		write_ptr++;
	}
	return ret;
}

static int verify_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static long verify_ioctl(struct file *pfile, unsigned int cmd,
	unsigned long arg)
{
	int ret, plcs;
	u16 crc_val;
	u32 block, temp_data[8], rotpk_data[8];

	if (!efuse) {
		pr_err("ioctl get efuse handle error!\n");
		return -ENODEV;
	}
	memcpy(rotpk_data, rotpk_hash, HASH_BYTE_LEN);

	if (_IOC_TYPE(cmd) != EFUSE_MAGIC)
		return -EINVAL;
	if (_IOC_NR(cmd) > EFUSE_MAGIC_MAXNR)
		return -EINVAL;

	switch (cmd) {
	case WR_EFUSE_ROTPK:
		crc_val = crc16_verify(rotpk_hash, HASH_BYTE_LEN);
		if (((crc_val & 0xff) != rotpk_hash[HASH_BYTE_LEN]) ||
			((crc_val >> 8) != rotpk_hash[HASH_BYTE_LEN+1]) ||
			(!crc_val)) {
			pr_err("error:rotpk_hash crc16_verify fail...\n");
			return -EINVAL;
		}

		ret = write_rotpk_blocks(ROTPK_START, ROTPK_END, rotpk_data);
		if (ret)
			return ret;
		break;

	case RD_EFUSE_LCS:
		for (block = ROTPK_START; block <= ROTPK_END; block++)
			nvmem_device_read(efuse, (block - 2) * 4, 4,
			&temp_data[block - ROTPK_START]);

		if (memcmp(temp_data, rotpk_data, HASH_BYTE_LEN))
			plcs = 1;
		else
			plcs = 5;
		if (copy_to_user((int *)arg, &plcs, sizeof(int))) {
			pr_err("error:copy_to_user fail...");
			return -EFAULT;
		}
		ret = 0;
		break;

	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}

static const struct file_operations verify_fops = {
	.owner = THIS_MODULE,
	.open = verify_open,
	.unlocked_ioctl = verify_ioctl,
};

static int sprd_verify_probe(struct platform_device *pdev)
{
	int ret;
	struct device *verify_dev;

	efuse = devm_nvmem_device_get(&pdev->dev, "ap-efuse");
	if (IS_ERR(efuse))
		return PTR_ERR(efuse);

	ret = alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
	if (ret < 0) {
		pr_err("orca dev_num can't be registered!");
		return ret;
	}

	cdev_init(&v_dev, &verify_fops);
	cdev_add(&v_dev, dev_num, 1);

	verify_class = class_create(THIS_MODULE, DEV_NAME);
	if (IS_ERR(verify_class)) {
		pr_err("error:create verify_class failed!");
		cdev_del(&v_dev);
		unregister_chrdev_region(dev_num, 1);
		return PTR_ERR(verify_class);
	}

	verify_dev = device_create(verify_class, NULL, dev_num, NULL, DEV_NAME);
	if (IS_ERR(verify_dev)) {
		pr_err("error:create device failed!");
		class_destroy(verify_class);
		cdev_del(&v_dev);
		unregister_chrdev_region(dev_num, 1);
		return PTR_ERR(verify_dev);
	}

	return 0;
}

static int sprd_verify_remove(struct platform_device *pdev)
{
	device_destroy(verify_class, dev_num);
	class_destroy(verify_class);
	cdev_del(&v_dev);
	unregister_chrdev_region(dev_num, 1);
	return 0;
}

static struct platform_driver sprd_verify_driver = {
	.probe = sprd_verify_probe,
	.remove = sprd_verify_remove,
	.driver = {
		.name = "sprd-verify",
		.of_match_table = sprd_verify_of_match,
	},
};

module_platform_driver(sprd_verify_driver);

MODULE_AUTHOR("gang.qie1 <gang.qie1@unisoc.com>");
MODULE_DESCRIPTION("modem verify driver");
MODULE_LICENSE("GPL v2");

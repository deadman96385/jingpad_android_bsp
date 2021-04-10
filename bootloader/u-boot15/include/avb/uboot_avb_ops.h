/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef UBOOT_AVB_OPS_H_
#define UBOOT_AVB_OPS_H_

#define  SPRD_RSA4096PUBK_HASHLEN  (32)
#define  SPRD_VBOOT_CMDLINE_MAXSIZE (512)
#define  SPRD_VBOOT_SYSTEM_CMDLINE_MAXSIZE (1024)

typedef enum {
	AVB_CHECK_BOOTING,
	AVB_CHECK_DOWNLOAD,
	AVB_CHECK_BUTT
}AvbCheckType;


extern AvbCheckType g_ulAvbCheckType;
extern unsigned char g_sprd_vboot_key[SPRD_RSA4096PUBK_HASHLEN];
extern unsigned int g_sprd_vboot_key_len;
extern unsigned char g_sprd_vboot_cmdline[SPRD_VBOOT_CMDLINE_MAXSIZE];
extern unsigned int g_sprd_vboot_ret[4];
extern bool g_sprd_vbmeta_checked_flag;
#ifdef CONFIG_VBOOT_SYSTEMASROOT
extern unsigned char g_vboot_sys_cmdline[SPRD_VBOOT_SYSTEM_CMDLINE_MAXSIZE];
#endif

int avb_check_image(unsigned char *name);
int avb_check_vbmeta(uint8_t * vbmeta_img_paddr, uint32_t vbmeta_image_len);
int avb_ops_new_for_download(void);
int avb_ops_new(void);
uint8_t* avb_ops_get_vboot_key(uint32_t * avb_vboot_key_len);
void set_current_dl_partition(const char* partition_name);
#endif /* UBOOT_AVB_OPS_H_ */

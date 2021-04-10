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


/*add for avb ops*/
#include <common.h>
#include <android_bootimg.h>
#include "loader_common.h"
#include <malloc.h>
#include <ext_common.h>
#include <ext4fs.h>
#include <linux/sizes.h>
#include "dl_operate.h"
#include "sprd_common_rw.h"

#include <otp_helper.h>
#include <stdio_dev.h>
#include <secureboot/sec_common.h>
/*end of add for avb ops*/

#include "sprd_imgversion.h"
#include <avb/uboot_avb_ops.h>
#include "avb_ops.h"
#include <avb/uboot_avb_util.h>

extern AvbOps g_avb_ops;
extern unsigned char *g_eMMCBuf;

AvbCheckType g_ulAvbCheckType = AVB_CHECK_BOOTING;
unsigned char g_sprd_vboot_key[SPRD_RSA4096PUBK_HASHLEN] __attribute__((aligned(4096))); /*must be PAGE ALIGNED*/
unsigned int g_sprd_vboot_key_len = 0;
unsigned char g_sprd_vboot_cmdline[SPRD_VBOOT_CMDLINE_MAXSIZE]__attribute__((aligned(4096))); /*must be PAGE ALIGNED*/
unsigned int g_sprd_vboot_ret[4]__attribute__((aligned(4096)));
char cur_dl_partition_name[PARTNAME_SZ];

// for dat modem
#define MODEM_MAGIC           "SCI1"
#define MODEM_HDR_SIZE        12  // size of a block
#define SCI_TYPE_MODEM_BIN    1
#define SCI_TYPE_PARSING_LIB  2
#define MODEM_LAST_HDR        0x100
#define MODEM_SHA1_HDR        0x400
#define MODEM_SHA1_SIZE       20

typedef struct {
    unsigned int type_flags;
    unsigned int offset;
    unsigned int length;
} data_block_header_t;

/*for skip check vbmeta when already checked*/
bool g_sprd_vbmeta_checked_flag = false;

/* This function hex dumps a buffer of characters */
void do_hex_dump(void * vaddr, int buflen)
{
	uint8_t *p;
	uint32_t bytes = buflen;
	uint32_t i;

	p = (uint8_t *)vaddr;
	for (i = 0; i < bytes; i++)
	{
		if(i%16 == 0)
		{
			printf("\ni:%d     ", i);
		}
		printf("  0x%02x", p[i]);
	}
	printf("\n");
}

AvbIOResult read_from_partition(AvbOps     *ops,
                                const char *partition_name,
                                int64_t     offset_from_partition,
                                size_t      num_bytes,
                                void       *buf,
                                size_t     *out_num_read) {
    int      ret = 0;
    uint64_t partition_size;

    extern int secure_get_partition_size(uchar * partition_name, uint64_t * size);
    secure_get_partition_size(partition_name, &partition_size);

    if (offset_from_partition < 0) {
        if ((-offset_from_partition) > partition_size) {
            debug("Offset outside range.\n");
            return AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION;
        }
        offset_from_partition = partition_size - (-offset_from_partition);
    }
    /* Check if num_bytes goes beyond partition end. If so, don't read beyond
     * this boundary -- do a partial I/O instead.
     */
    if (num_bytes > partition_size - offset_from_partition)
        *out_num_read = partition_size - offset_from_partition;
    else
        *out_num_read = num_bytes;
    if((strcmp(partition_name, "vbmeta")) &&
       (g_ulAvbCheckType == AVB_CHECK_DOWNLOAD)&&
       (strcmp(cur_dl_partition_name, partition_name) == 0)) {
        debug("buf:0x%x, g_eMMCBuf:0x%x, offset_from_partition:%d num_bytes:%d\n",
              buf, g_eMMCBuf, offset_from_partition, num_bytes);
        memcpy((char *)buf, g_eMMCBuf+offset_from_partition, num_bytes);
#ifdef CONFIG_VBOOT_DUMP
        do_hex_dump(g_eMMCBuf, 512);
#endif
        *out_num_read = num_bytes;
    } else {
        if (strcmp(partition_name, "vbmeta") == 0) {
            secure_load_partition(partition_name, (uint64_t)num_bytes,
                                  (uint64_t)offset_from_partition, (char *)buf);
        } else {
            ret = common_raw_read(partition_name, (uint64_t)num_bytes,
                                  (uint64_t)offset_from_partition, (char *)buf);
        }
        if (0 != ret) {
            debug("PARTITION %s read error, ret:%d \n", partition_name, ret);
            return ret;
        }
        *out_num_read = num_bytes;
    }
    return ret;
}

AvbIOResult validate_vbmeta_public_key(
    AvbOps* ops,
    const uint8_t* public_key_data,
    size_t public_key_length,
    const uint8_t* public_key_metadata,
    size_t public_key_metadata_length,
    bool* out_key_is_trusted) {
    AvbIOResult ret = AVB_IO_RESULT_OK;
    unsigned char sprd_vboot_key_in_vbmeta[SPRD_RSA4096PUBK_HASHLEN];

    uint8_t* public_key_hash;
    size_t public_key_hash_length;

    avb_debug("Enter: implement validate_vbmeta_public_key().\n");
    (void)public_key_metadata;
    (void)public_key_metadata_length;

    if (!out_key_is_trusted ||!public_key_data || !public_key_length) {
	avb_errorv("invalid: para is null.\n", NULL);
	return AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    }

    /*get expected_public_key from user data*/
    public_key_hash = avb_ops_get_vboot_key(&public_key_hash_length);

#ifdef CONFIG_VBOOT_DUMP
    debug("dump public_key_hash: public_key_hash_length:%d. \n", public_key_hash_length);
    if(public_key_hash_length && public_key_hash) {
        do_hex_dump(public_key_hash, public_key_hash_length);
    }
#endif

    extern void cal_sha256(uint8_t * input, uint32_t bytes_num, uint8_t * output);
    cal_sha256((uint8_t *)public_key_data, (uint32_t)public_key_length, (uint8_t *)sprd_vboot_key_in_vbmeta);
#ifdef CONFIG_VBOOT_DUMP
    do_hex_dump((uint8_t *)sprd_vboot_key_in_vbmeta, SPRD_RSA4096PUBK_HASHLEN);
#endif

    if (((uint32_t)public_key_hash_length != (uint32_t)SPRD_RSA4096PUBK_HASHLEN) ||
	(avb_safe_memcmp(public_key_hash, sprd_vboot_key_in_vbmeta, SPRD_RSA4096PUBK_HASHLEN) != 0)) {
	avb_debugv("expected_public_key is not matched.\n", NULL);
	avb_errorv("vbmeta",
		": Public key used to sign data does not match key in chain "
		"partition descriptor.\n",
		NULL);

	*out_key_is_trusted = false;
	ret = AVB_SLOT_VERIFY_RESULT_ERROR_PUBLIC_KEY_REJECTED;
    } else {
	avb_debugv("expected_public_key is matched.\n", NULL);
	*out_key_is_trusted = true;
    }

  return ret;
}

static AvbIOResult read_rollback_index(AvbOps* ops,
                                       size_t rollback_index_slot,
                                       uint64_t* out_rollback_index) {
  uint32_t swVersion = 0;
  int ret = 0;

  if(out_rollback_index == NULL) {
      error(">>>>> ERR:para is invalid.\n");
      return AVB_IO_RESULT_ERROR_OOM;
  }

  ret = sprd_get_imgversion((antirb_image_type)rollback_index_slot, &swVersion);
  debug(">>>>> rollback_index_slot:0x%llx, swVersion:%lld, ret:%d.\n", rollback_index_slot, swVersion, ret);

  if(!ret) {
    *out_rollback_index = (uint64_t)swVersion;
  } else {
     debug(">>>>> Warning:read rollback index return err.\n");
     *out_rollback_index = (uint64_t)0;
     //debug(">>>>> Debug *out_rollback_index:%d.\n", *out_rollback_index);
  }

  return AVB_IO_RESULT_OK;
}

AvbIOResult write_rollback_index(AvbOps* ops,
                                        size_t rollback_index_slot,
                                        uint64_t rollback_index) {
  /* For now this is a no-op. */
  avb_debug("TODO: implement write_rollback_index().\n");
  return AVB_IO_RESULT_OK;
}

AvbIOResult read_is_device_unlocked(AvbOps* ops, bool* out_is_unlocked) {
  if(g_DeviceStatus == VBOOT_STATUS_UNLOCK){
    *out_is_unlocked = true;
  }else{
    *out_is_unlocked = false;
  }

  debug("read_is_device_unlocked() get DeviceStatus 0x%x, *out_is_unlocked is %d.\n", g_DeviceStatus, *out_is_unlocked);
  return AVB_IO_RESULT_OK;
}

AvbIOResult get_unique_guid_for_partition(AvbOps* ops,
                                          const char* partition,
                                          char* guid_buf,
                                          size_t guid_buf_size) {
#ifdef CONFIG_VBOOT_SYSTEMASROOT
  debug("enter get_unique_guid_for_partition().\n");
  debug("partition: %s  guid_buf_size = %d \n", partition, guid_buf_size);
  memset(guid_buf, 0, guid_buf_size);
  get_img_partition_uuid(partition, guid_buf);
  debug("guid_buf: %s \n", guid_buf);
  return AVB_IO_RESULT_OK;
#else
  return AVB_IO_RESULT_OK;
#endif
}
AvbIOResult get_size_of_partition(AvbOps* ops,
                                  const char* partition,
                                  uint64_t* out_size_num_bytes) {

  debug("enter get_size_of_partition().\n");
  *out_size_num_bytes = 0;
  return AVB_IO_RESULT_OK;
}

int avb_ops_new_for_download(void)
{
  g_avb_ops.ab_ops = NULL;
  g_avb_ops.read_from_partition = read_from_partition;
  g_avb_ops.write_to_partition = NULL;
  g_avb_ops.validate_vbmeta_public_key = validate_vbmeta_public_key;
  g_avb_ops.read_rollback_index = read_rollback_index;
  g_avb_ops.write_rollback_index = write_rollback_index;
  g_avb_ops.read_is_device_unlocked = read_is_device_unlocked;
  g_avb_ops.get_unique_guid_for_partition = get_unique_guid_for_partition;
  g_avb_ops.get_size_of_partition = get_size_of_partition;
  g_avb_ops.user_data = 0x00;

  g_ulAvbCheckType = AVB_CHECK_DOWNLOAD;
   return 0;
}

AvbIOResult dummy_validate_vbmeta_public_key(
    AvbOps* ops,
    const uint8_t* public_key_data,
    size_t public_key_length,
    const uint8_t* public_key_metadata,
    size_t public_key_metadata_length,
    bool* out_key_is_trusted) {
	// vbmeta public key has been checked in previous bootloader phase.
	// In current fix vbmeta size and digest stage, returns true to
	// pass the check.
	*out_key_is_trusted = true;
	return AVB_IO_RESULT_OK;
}


static AvbIOResult dummy_read_rollback_index(AvbOps* ops,
                                       size_t rollback_index_slot,
                                       uint64_t* out_rollback_index) {
	*out_rollback_index = (uint64_t)0;
	return AVB_IO_RESULT_OK;
}


int avb_ops_new(void)
{
  g_avb_ops.ab_ops = NULL;
  g_avb_ops.read_from_partition = read_from_partition;
  g_avb_ops.write_to_partition = NULL;
  g_avb_ops.validate_vbmeta_public_key = dummy_validate_vbmeta_public_key;
  g_avb_ops.read_rollback_index = dummy_read_rollback_index;
  g_avb_ops.write_rollback_index = write_rollback_index;
  g_avb_ops.read_is_device_unlocked = read_is_device_unlocked;
  g_avb_ops.get_unique_guid_for_partition = get_unique_guid_for_partition;
  g_avb_ops.user_data = 0x00;

  g_ulAvbCheckType = AVB_CHECK_BOOTING;
   return 0;
}

static int is_packed_modem_image(uint8_t *data)
{
    if (sec_memcmp(data, (uint8_t*)MODEM_MAGIC, sizeof(MODEM_MAGIC)))
        return 0;
    return 1;
}

/*
 *  this function parse new packed modem image and return modem code offset and length
 */
static void get_modem_info(uint8_t *data, uint32_t *code_offset, uint32_t *code_len)
{
	uint32_t offset = 0, hdr_offset = 0, length = 0;
	uint8_t hdr_buf[MODEM_HDR_SIZE << 3] = {0};
	uint8_t read_len;
	uint8_t result = 0; // 0:OK, 1:not find, 2:some error occur
	data_block_header_t *hdr_ptr = NULL;

	read_len = sizeof(hdr_buf);
	sec_memcpy(hdr_buf, data, read_len);

    do {
      if (!hdr_offset) {
        if (memcmp(hdr_buf, MODEM_MAGIC, sizeof(MODEM_MAGIC))) {
          result = 2;
          debug("old image format!\n");
          break;
        }

        hdr_ptr = (data_block_header_t *)hdr_buf + 1;
        hdr_offset = MODEM_HDR_SIZE;
      } else {
        hdr_ptr = (data_block_header_t *)hdr_buf;
      }

      data_block_header_t* endp
          = (data_block_header_t*)(hdr_buf + sizeof hdr_buf);
      int found = 0;
      while (hdr_ptr < endp) {
        uint32_t type = (hdr_ptr->type_flags & 0xff);
        if (SCI_TYPE_MODEM_BIN == type) {
          found = 1;
          break;
        }

        /*  There is a bug (622472) in MODEM image generator.
         *  To recognize wrong SCI headers and correct SCI headers,
         *  we devise the workaround.
         *  When the MODEM image generator is fixed, remove #if 0.
         */
#if 0
        if (hdr_ptr->type_flags & MODEM_LAST_HDR) {
          result = 2;
          MODEM_LOGE("no modem image, error image header!!!\n");
          break;
        }
#endif
        hdr_ptr++;
      }
      if (!found) {
        result = 2;
        debug("no MODEM exe found in SCI header!");
      }

      if (result != 1) {
        break;
      }
    } while (1);

    if (!result) {
      offset = hdr_ptr->offset;
      if (hdr_ptr->type_flags & MODEM_SHA1_HDR) {
        offset += MODEM_SHA1_SIZE;
      }
      length = hdr_ptr->length;
    }

	*code_offset = offset;
	*code_len = length;
}

uint8_t* avb_ops_get_image_buffer(uint8_t avb_check_type)
{
    uint32_t modem_offset = 0;
    uint32_t modem_len = 0;

    debug("avb_check_type = %d\n", avb_check_type);
    if(avb_check_type == AVB_CHECK_BOOTING) {
        return (uint8_t*)KERNEL_ADR;
    } else {
        debug("check dat cp\n");
        if (is_packed_modem_image(g_eMMCBuf)) {
            debug("the image is new packed modem image\n");
            get_modem_info(g_eMMCBuf, &modem_offset, &modem_len);
            debug("modem offset: 0x%x, length: 0x%x\n", modem_offset, modem_len);
        }
        return (uint8_t*)(g_eMMCBuf + modem_offset);
    }
}

/*for uboot*/
int avb_ops_set_vboot_key(uint8_t * avb_vboot_key, uint32_t avb_vboot_key_len)
{
	if(avb_vboot_key_len > sizeof(g_sprd_vboot_key)) {
		avb_debug("in avb_ops_set_vboot_key, para size is overflow.\n");
		return -1;
	}
	memset(g_sprd_vboot_key, 0, sizeof(g_sprd_vboot_key));
	memcpy(g_sprd_vboot_key, avb_vboot_key, avb_vboot_key_len);
	g_sprd_vboot_key_len = sizeof(g_sprd_vboot_key);
	return 0;
}

/*for avb ops*/
uint8_t* avb_ops_get_vboot_key(uint32_t * avb_vboot_key_len)
{
	*avb_vboot_key_len = g_sprd_vboot_key_len;
	return (uint8_t*)g_sprd_vboot_key;
}

void set_current_dl_partition(const char* partition_name) {
	if(partition_name && (strlen(partition_name) > 0)) {
		memset(cur_dl_partition_name, 0, PARTNAME_SZ);
		strncpy(cur_dl_partition_name, partition_name, PARTNAME_SZ);
	}
}

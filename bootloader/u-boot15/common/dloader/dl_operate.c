#include "common.h"
#include <malloc.h>
#include <asm/arch/chip_releted_def.h>
#include "dl_common.h"
#include "dl_operate.h"
#include <ext_common.h>
#include <part.h>
#include <sparse_format.h>
#include <sprd_common_rw.h>
#include <sprd_rpmb.h>
#include <mmc.h>

#include <secure_boot.h>
#include <secureboot/sec_common.h>
#include <otp_helper.h>
#include <chipram_env.h>
#include "../../fs/f2fs-tools/include/f2fs_fs.h"

static DL_EMMC_FILE_STATUS g_status;
static DL_EMMC_STATUS g_dl_eMMCStatus;

static unsigned long g_checksum;
static unsigned long g_sram_addr;
static unsigned int img_backup_flag = 0;

extern fastboot_image_size;

# ifndef CONFIG_DTS_MEM_LAYOUT
#ifdef CONFIG_X86
#ifdef CONFIG_SPRD_SOC_SP9853I
unsigned char *g_eMMCBuf = (unsigned char *)0x00800000;
#else
unsigned char *g_eMMCBuf = (unsigned char *)0x35000000;
#endif
#else
unsigned char *g_eMMCBuf = (unsigned char *)0x82000000;
#endif
uint64_t  emmc_buf_size = SZ_256M;

# else
unsigned char *g_eMMCBuf = NULL;
uint64_t  emmc_buf_size = 0;
# endif

/**
	partitions not for raw data or normal usage(e.g. nv and prodinfo) should config here.
	partitions not list here mean raw data/normal usage.
*/
SPECIAL_PARTITION_CFG const s_special_partition_cfg[] = {
	{{"fixnv1"}, {"fixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"runtimenv1"}, {"runtimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"tdfixnv1"}, {"tdfixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"tdruntimenv1"}, {"tdruntimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"g_fixnv1"}, {"g_fixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"g_runtimenv1"}, {"g_runtimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"nr_fixnv1"}, {"nr_fixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"nr_runtimenv1"}, {"nr_runtimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"l_fixnv1"}, {"l_fixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"l_runtimenv1"}, {"l_runtimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"tl_fixnv1"}, {"tl_fixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"tl_runtimenv1"}, {"tl_runtimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"lf_fixnv1"}, {"lf_fixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"lf_runtimenv1"}, {"lf_runtimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"wfixnv1"}, {"wfixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"wruntimenv1"}, {"wruntimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"w_fixnv1"}, {"w_fixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"w_runtimenv1"}, {"w_runtimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"wl_fixnv1"}, {"wl_fixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"wl_runtimenv1"}, {"wl_runtimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"wcnfixnv1"}, {"wcnfixnv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"wcnruntimenv1"}, {"wcnruntimenv2"}, IMG_RAW, PARTITION_PURPOSE_NV},
	{{"uboot"},{"uboot_bak"}, IMG_RAW, PARTITION_PURPOSE_NORMAL},
	{{"system"}, NULL, IMG_RAW, PARTITION_PURPOSE_NORMAL},
	{{"userdata"}, NULL, IMG_WITH_SPARSE, PARTITION_PURPOSE_NORMAL},
	{{"cache"}, NULL, IMG_WITH_SPARSE, PARTITION_PURPOSE_NORMAL},
	{{"prodnv"}, NULL, IMG_RAW, PARTITION_PURPOSE_NORMAL},
	{{"splloader"},{"splloader_bak"}, IMG_RAW, PARTITION_PURPOSE_NORMAL},
	{NULL, NULL, IMG_TYPE_MAX, PARTITION_PURPOSE_MAX}
};

enum {
	PARTITION_CONFIG_EXIST = 0x1,
	GPT_HEADER_EXIST = 0x2,
	RPMB_KEY_EXIST = 0x4,
};

ALTER_BUFFER_ATTR alter_buffer1;
ALTER_BUFFER_ATTR alter_buffer2;
ALTER_BUFFER_ATTR* current_buffer;

/***********************************************************/
#ifdef CONFIG_DTS_MEM_LAYOUT

#define SET_DOWNLOAD_BUFFER_BASE_SIZE(basep, sizep)		get_buffer_base_size_from_dt("heap@5", basep, sizep)
#define SET_ALT_BUFFER1_BASE_SIZE(basep, sizep)			get_buffer_base_size_from_dt("heap@6", basep, sizep)
#define SET_ALT_BUFFER2_BASE_SIZE(basep, sizep)			get_buffer_base_size_from_dt("heap@7", basep, sizep)

int set_buf_base_size()
{
	unsigned long buf_base, alt_buf1_base, alt_buf2_base;

	if (SET_DOWNLOAD_BUFFER_BASE_SIZE(&buf_base, &emmc_buf_size) < 0) {
		errorf("set download buffer error\n");
		return -1;
	}

	if (SET_ALT_BUFFER1_BASE_SIZE(&alt_buf1_base, &alter_buffer1.size) < 0) {
		errorf("set download alt buffer1 error\n");
		return -1;
	}

	if (SET_ALT_BUFFER2_BASE_SIZE(&alt_buf2_base, &alter_buffer2.size) < 0) {
		errorf("set download alt buffer2 error\n");
		return -1;
	}

	g_eMMCBuf = (unsigned char *)ALIGN(buf_base , 8);
	alter_buffer1.addr = (unsigned char *)ALIGN(alt_buf1_base , 8);
	alter_buffer2.addr = (unsigned char *)ALIGN(alt_buf2_base , 8);

	debugf("download buffer base %p, size %llx\nalter buffer1 base %p, size %x\nalter buffer2 base %p, size %x\n",
			g_eMMCBuf, emmc_buf_size,
			alter_buffer1.addr, alter_buffer1.size,
			alter_buffer2.addr, alter_buffer2.size);

	return 0;
}
#endif

uint16_t eMMCCheckSum(const uint32_t * src, int32_t len)
{
	uint32_t sum = 0;
	unsigned short *src_short_ptr = NULL;

	while (len > 3) {
		sum += *src++;
		len -= 4;
	}

	src_short_ptr = (uint16_t *) src;

	if (0 != (len & 0x2)) {
		sum += *(src_short_ptr);
		src_short_ptr++;
	}

	if (0 != (len & 0x1)) {
		sum += *((unsigned char *)(src_short_ptr));
	}

	sum = (sum >> 16) + (sum & 0x0FFFF);
	sum += (sum >> 16);

	return (uint16_t) (~sum);
}

#ifdef CONFIG_MMC
uint8_t emmc_2ndhand_detect()
{
	char part_config;
	block_dev_desc_t *dev_desc;
	gpt_entry *pgpt_pte = NULL;
	int rpmb_key_result;
	uint8_t result = 0x0;
	struct mmc *mmc = find_mmc_device(0);
	dev_desc = get_dev_hwpart("mmc", 0, PARTITION_USER);
	ALLOC_CACHE_ALIGN_BUFFER_PAD(gpt_header, gpt_head, 1, dev_desc->blksz);

	/* judge the partition config */
	part_config = mmc->part_config;
	/* spreadtrum do not use BOOT_ACK,if the BOOT_ACK is 1,the emmc is used by other vendor */
	if (((part_config >> 6) & 0x1) == 0x1) {
		printf("The Emmc partition config was used\n");
		result |= PARTITION_CONFIG_EXIST;
	}

#ifdef CONFIG_EFI_PARTITION
	if (test_part_efi(dev_desc) == 0) {
		printf("Find gpt header from user partition,emmc was used\n");
		result |= GPT_HEADER_EXIST;
	}
#endif

	rpmb_key_result = is_wr_rpmb_key();
	if (rpmb_key_result != 0) {
		printf("The Emmc rpmb partition was used\n");
		result |= RPMB_KEY_EXIST;
	}

	return result;
}

uint8_t emmc_2ndhand_fix(uint8_t detect_result)
{
	struct mmc *mmc = find_mmc_device(0);

	/* clear the partition_boot_ack bit */
	if (detect_result & PARTITION_CONFIG_EXIST)
		mmc->part_config &= 0x3F;

	return 0;
}
#endif

uint32_t get_pad_data(const uint32_t * src, int32_t len, int32_t offset, uint16_t sum)
{
	uint32_t sum_tmp;
	uint32_t sum1 = 0;
	uint32_t pad_data;
	uint32_t i;
	sum = ~sum;
	sum_tmp = sum & 0xffff;
	sum1 = 0;
	for (i = 0; i < offset; i++) {
		sum1 += src[i];
	}
	for (i = (offset + 1); i < len; i++) {
		sum1 += src[i];
	}
	pad_data = sum_tmp - sum1;
	return pad_data;
}

void splFillCheckData(uchar * splBuf)
{
	EMMC_BootHeader *header;
	uint32_t pad_data;
	uint32_t w_len;
	uint32_t w_offset;
	uchar * buf = splBuf + BOOTLOADER_HEADER_OFFSET + sizeof(EMMC_BootHeader);
	w_len = (SPL_CHECKSUM_LEN - (BOOTLOADER_HEADER_OFFSET + sizeof(*header))) / 4;
	w_offset = w_len - 1;

	/*pad the data inorder to make check sum to 0 */
	pad_data = get_pad_data((uint32_t *)buf, w_len, w_offset, 0);
	debugf("splloader fill pad_data=0x%x\n", pad_data);
	*(volatile unsigned int *)(splBuf + SPL_CHECKSUM_LEN - 4) = pad_data;
	header = (EMMC_BootHeader *) (splBuf + BOOTLOADER_HEADER_OFFSET);
	header->version = 0;
	header->magicData = MAGIC_DATA;
	header->checkSum = (uint32_t) eMMCCheckSum(splBuf + BOOTLOADER_HEADER_OFFSET + sizeof(*header),
						   SPL_CHECKSUM_LEN - (BOOTLOADER_HEADER_OFFSET + sizeof(*header)));
#ifdef CONFIG_SECURE_BOOT
	header->hashLen = CONFIG_SPL_HASH_LEN >> 2;
#else
	header->hashLen = 0;
#endif
}


int _parser_repartition_cfg_v0(disk_partition_t * partition_info, const uchar * partition_cfg, uint16_t total_partition_num)
{
	uint16_t i = 0;
	uint16_t j = 0;
	uint32_t partition_size_m = 0;
	lbaint_t partition_start_lba = 0;
	int32_t blksz = 0;
	uint32_t lbas_per_m = 0;

	blksz = common_get_lba_size();
	if (-1 == blksz)
		return -1;

	lbas_per_m = SZ_1M / blksz;

	/*first 1 MB will be reserved, no partition can located here*/
	partition_start_lba = SZ_1M / blksz;

	/*Decode String: Partition Name(72Byte)+SIZE(4Byte)+... */
	for (i = 0; i < total_partition_num; i++) {
		partition_info[i].blksz = (ulong)blksz;
		strcpy(partition_info[i].type, "U-boot");	/*not useful */

		partition_size_m = *(uint32_t *) (partition_cfg + 76 * (i + 1) - 4);
		/*the last partition and partition_size_m is 0xFFFFFFFF means this partition use all the spare lba */
		if ((i == total_partition_num - 1) && (MAX_SIZE_FLAG == partition_size_m)) {
			/*size=0 represent use all the spare lba */
			partition_info[i].size = 0;
		} else {
			/*calc the partition size of lba , raw data unit is Mb */
			partition_info[i].size = (lbaint_t) partition_size_m * lbas_per_m;
		}

		/*in raw data rcv from download tool,partition_name is 38 uint16_t length;
		 **in part.h ,disk_partition_t.name is 32 uchar length;
		 **in part_efi.h ,gpt_entry.partition_name is 36 uint16_t length,
		 **we convert raw data to disk_partition_t format here , gpt_fill_pte() in part_efi.c will
		 **convert disk_partition_t to gpt_entry*/
		for (j = 0; j < 32 - 1; j++) {
			/*transform 64 bytes uint16_t to 32 bytes uchar ,and discard the last 8 bytes */
			partition_info[i].name[j] = *((uint16_t *) partition_cfg + 38 * i + j) & 0xFF;
		}
		partition_info[i].name[j] = '\0';
		partition_info[i].start = partition_start_lba;

		partition_start_lba += partition_info[i].size;
#ifdef CONFIG_PARTITION_UUIDS
		uuid_bin_to_str(partition_info[i].name, partition_info[i].uuid, UUID_STR_FORMAT_GUID);
#endif

		debugf("partition name:%s,partition_size:0x%lx,partiton_start:0x%lx,\n", partition_info[i].name, partition_info[i].size,
		       partition_info[i].start);
	}

	return 0;
}


int _parser_repartition_cfg_v1(disk_partition_t * partition_info, uchar* partition_cfg, uint16_t total_partition_num,
									uchar size_unit)
{
	int i, j;

	uint64_t partition_size_raw;
	uint64_t partition_size_lba;
	/*attention here, we use int64 instead of uint64 to support minus gap size, such as "-2048"*/
	int64_t gap_raw;
	int64_t gap_lba;
	uint64_t partition_start_lba = 0;
	int32_t blksz = 0;

	blksz = common_get_lba_size();
	if (-1 == blksz)
		return -1;

	/*V1 partition table format: Partition Name(72Byte)+SIZE(8Byte)+GAP(8Byte)...*/
	for (i = 0; i < total_partition_num; i++) {
		partition_size_raw = *(uint64_t *)(partition_cfg + 88 * (i + 1) - 16);
		gap_raw = *(int64_t *)(partition_cfg + 88 * (i + 1) - 8);
		debugf("partition_size_raw = 0x%llx, gap_raw = 0x%llx\n", partition_size_raw, gap_raw);

		switch (size_unit) {
		/*unit is MB*/
		case 0:
			partition_size_lba = partition_size_raw * SZ_1M / blksz;
			gap_lba = gap_raw * SZ_1M / blksz;
			break;
		/*unit is 512K*/
		case 1:
			partition_size_lba = partition_size_raw * SZ_512K / blksz;
			gap_lba = gap_raw * SZ_512K / blksz;
			break;
		/*unit is KB*/
		case 2:
			partition_size_lba = PAD_SIZE(partition_size_raw * SZ_1K, blksz) / blksz;
			if (0 == gap_raw)
				gap_lba = 0;
			else
				gap_lba = PAD_SIZE(gap_raw * SZ_1K, blksz) / blksz;
			break;
		/*unit is bytes, min partition unit supported is lba(512byte), so we pad it if neccessary*/
		case 3:
			partition_size_lba = PAD_SIZE(partition_size_raw, blksz) / blksz;
			if (0 == gap_raw)
				gap_lba = 0;
			else
				gap_lba = PAD_SIZE(gap_raw, blksz) / blksz;
			break;
		/*unit is sector*/
		case 4:
			partition_size_lba = partition_size_raw;
			gap_lba = gap_raw;
			break;
		/*unsupported unit we consider it as MB*/
		default:
			partition_size_lba = partition_size_raw * SZ_1M / blksz;
			gap_lba = gap_raw * SZ_1M / blksz;
			break;
		}

		/*check the gap of the first partition*/
		if (0 == i) {
			if (0 == gap_lba) {
				/*first 1 MB will be reserved, no partition can located here*/
				gap_lba = SZ_1M / blksz;
			} else if (gap_lba < FIRST_USABLE_LBA_FOR_PARTITION) {
				errorf("%s: FATAL ERROR, gap of the first partition counted in lba CAN NOT less than 34\n", __FUNCTION__);
				return -1;
			}
		}

		/*all the 8 bytes are 0xFF in the packet, but to compatible with the old version,
			we only consider the lower 4 bytes.*/
		if (MAX_SIZE_FLAG == (partition_size_raw & MAX_SIZE_FLAG)) {
			partition_size_lba = 0;
			debugf("the last partition use all the left lba\n");
		}
		partition_start_lba += gap_lba;
		partition_info[i].blksz = (ulong)blksz;
		partition_info[i].start = (lbaint_t)partition_start_lba;
		partition_info[i].size = (lbaint_t)partition_size_lba;
		if (0 != partition_size_lba)
			partition_start_lba += partition_size_lba;

		strcpy(partition_info[i].type, "U-boot");	/*not useful */

		for (j = 0; j < 32 - 1; j++)
			partition_info[i].name[j] = *((uint16_t *)partition_cfg + 44 * i + j) & 0xFF;

		debugf("partition name:%s,partition_size:0x%lx, partition_offset:0x%lx\n",
			partition_info[i].name, partition_info[i].size, partition_info[i].start);
	}
	return 0;
}

int _parser_repartition_cfg(disk_partition_t * partition_info, const uchar* partition_cfg, uint16_t total_partition_num,
								unsigned char version, unsigned char size_unit)
{
	int ret = 0;

	switch (version) {
	case 0:
		debugf("Handle repartition packet version 0  \n");
		ret = _parser_repartition_cfg_v0(partition_info, partition_cfg, total_partition_num);
		break;
	case 1:
	default:
		debugf("Handle repartition packet version 1  \n");
		ret = _parser_repartition_cfg_v1(partition_info, partition_cfg, total_partition_num, size_unit);
		break;
	}
	return ret;
}



/**
	Get the backup partition name
*/
uchar *_get_backup_partition_name(uchar * partition_name)
{
	int i = 0;

	for (i = 0; s_special_partition_cfg[i].partition != NULL; i++) {
		if (0 == strcmp(partition_name, s_special_partition_cfg[i].partition)) {
			return s_special_partition_cfg[i].bak_partition;
		}
	}

	return NULL;
}


void prepare_alternative_buffers(void)
{
#ifndef CONFIG_DTS_MEM_LAYOUT
	alter_buffer1.addr = g_eMMCBuf + emmc_buf_size+ALTERNATIVE_BUFFER_SIZE;
	alter_buffer1.size = ALTERNATIVE_BUFFER_SIZE;

	alter_buffer2.addr = alter_buffer1.addr + 2*ALTERNATIVE_BUFFER_SIZE;
	alter_buffer2.size = ALTERNATIVE_BUFFER_SIZE;
#endif
	alter_buffer1.pointer = alter_buffer1.addr;
	alter_buffer1.used = 0;
	alter_buffer1.spare = alter_buffer1.size;
	alter_buffer1.status = BUFFER_CLEAN;
	alter_buffer1.next = &alter_buffer2;

	alter_buffer2.pointer = alter_buffer2.addr;
	alter_buffer2.used = 0;
	alter_buffer2.spare = alter_buffer2.size;
	alter_buffer2.status = BUFFER_CLEAN;
	alter_buffer2.next = &alter_buffer1;

	current_buffer = &alter_buffer1;
	return;
}

int speedup_download_process(uint32_t size, char *buf)
{
	uint32_t blk_count = 0;
	uint32_t tot_buf_size = current_buffer->size;
	uint32_t last_size = 0;

	if (current_buffer->spare > size)  {
		memcpy(current_buffer->pointer, buf, size);
		current_buffer->used += size;
		current_buffer->spare -= size;
		current_buffer->pointer += size;

		if (g_status.total_recv_size == g_status.total_size) {
			if (BUFFER_DIRTY == current_buffer->next->status)
				if (0 != common_query_backstage(g_dl_eMMCStatus.curUserPartitionName,
					tot_buf_size, current_buffer->next->addr)) {
					errorf("last query backstage fail, offset=0x%x\n", g_dl_eMMCStatus.offset);
					return OPERATE_WRITE_ERROR;
				}

			if (0 != common_raw_write(g_dl_eMMCStatus.curUserPartitionName,
				(uint64_t)(current_buffer->used), (uint64_t)0, (uint64_t)(g_dl_eMMCStatus.offset), current_buffer->addr)) {
				errorf("last write fail, offset=0x%x\n", g_dl_eMMCStatus.offset);
				return OPERATE_WRITE_ERROR;
			}
			g_status.unsave_recv_size = 0;
		}
	} else {
		memcpy(current_buffer->pointer, buf, current_buffer->spare);
		last_size = size - current_buffer->spare;
		if (BUFFER_DIRTY == current_buffer->next->status)
			if (0 != common_query_backstage(g_dl_eMMCStatus.curUserPartitionName,
				tot_buf_size, current_buffer->next->addr)) {
				errorf("query backstage fail, offset=0x%x\n", g_dl_eMMCStatus.offset);
				return OPERATE_WRITE_ERROR;
			}

		if (0 != common_write_backstage(g_dl_eMMCStatus.curUserPartitionName,
			tot_buf_size, g_dl_eMMCStatus.offset, current_buffer->addr)) {
			errorf("write backstage fail, offset=0x%x\n", g_dl_eMMCStatus.offset);
			return OPERATE_WRITE_ERROR;
		}
		g_dl_eMMCStatus.offset += tot_buf_size;
		if (0 != last_size)
			memcpy(current_buffer->next->addr, buf + current_buffer->spare, last_size);
		current_buffer->used = 0;
		current_buffer->spare = current_buffer->size;
		current_buffer->pointer = current_buffer->addr;
		current_buffer->status = BUFFER_DIRTY;

		current_buffer = current_buffer->next;
		current_buffer->pointer = current_buffer->addr + last_size;
		current_buffer->used = last_size;
		current_buffer->spare = current_buffer->size - last_size;
		if (g_status.total_recv_size == g_status.total_size) {
			if (0 != common_query_backstage(g_dl_eMMCStatus.curUserPartitionName,
				tot_buf_size, current_buffer->next->addr)) {
				errorf("last cross query backstage fail, offset=0x%x\n", g_dl_eMMCStatus.offset);
				return OPERATE_WRITE_ERROR;
			}
			if (0 != current_buffer->used) {
				if (0 != common_raw_write(g_dl_eMMCStatus.curUserPartitionName,
					(uint64_t)(current_buffer->used), (uint64_t)0, (uint64_t)(g_dl_eMMCStatus.offset), current_buffer->addr)) {
					errorf("last cross write fail, offset=0x%x\n", g_dl_eMMCStatus.offset);
					return OPERATE_WRITE_ERROR;
				}
			}
			g_status.unsave_recv_size = 0;
		}
	}

	return OPERATE_SUCCESS;
}


void _get_partition_attribute(uchar * partition_name)
{
	int i;

	for (i = 0; s_special_partition_cfg[i].partition != NULL; i++) {
		if (0 == strcmp(s_special_partition_cfg[i].partition, partition_name)) {
			g_dl_eMMCStatus.curImgType = s_special_partition_cfg[i].imgattr;
			g_dl_eMMCStatus.partitionpurpose = s_special_partition_cfg[i].purpose;
			debugf("partition %s image type is %d,partitionpurpose:%d\n", partition_name, g_dl_eMMCStatus.curImgType,
			       g_dl_eMMCStatus.partitionpurpose);
			return;
		}
	}

	/*default type is IMG_RAW */
	g_dl_eMMCStatus.curImgType = IMG_RAW;
	g_dl_eMMCStatus.partitionpurpose = PARTITION_PURPOSE_NORMAL;
	debugf("partition %s image type is RAW, normal partition!\n", partition_name);

	return;
}


OPERATE_STATUS _nv_img_write(uchar * partition, uint32_t size)
{
	uint32_t nSectorCount;
	uint32_t nSectorBase;
	uint16_t sum = 0;
	uint16_t *dataaddr;
	uchar *backup_partition_name = NULL;
	uint8_t header_buf[NV_HEADER_SIZE];
	nv_header_t *nv_header_p = NULL;

	memset(header_buf, 0x00, NV_HEADER_SIZE);
	nv_header_p = header_buf;
	nv_header_p->magic = NV_HEAD_MAGIC;
	nv_header_p->len = size;
	nv_header_p->checksum = (uint32_t) fdl_calc_checksum(g_eMMCBuf, size);
	nv_header_p->version = NV_VERSION;

	debugf("Start to write first block of NV partition(%s)\n", partition);
	if (0 != common_raw_write(partition, NV_HEADER_SIZE, (uint64_t)0, (uint64_t)0, header_buf))
		return OPERATE_WRITE_ERROR;

	debugf("Start to write remain blocks of NV partition\n");
	if (0 != common_raw_write(partition, (uint64_t)size, (uint64_t)0, NV_HEADER_SIZE, g_eMMCBuf))
		return OPERATE_WRITE_ERROR;

	/*write the backup partition */
	backup_partition_name = _get_backup_partition_name(partition);

	if (0 != common_raw_write(backup_partition_name, NV_HEADER_SIZE, (uint64_t)0, (uint64_t)0, header_buf))
		return OPERATE_WRITE_ERROR;

	if (0 != common_raw_write(backup_partition_name, (uint64_t)size, (uint64_t)0, NV_HEADER_SIZE, g_eMMCBuf))
		return OPERATE_WRITE_ERROR;

	g_status.unsave_recv_size = 0;
	return OPERATE_SUCCESS;
}

OPERATE_STATUS _img_write_with_backup(uchar *partition)
{
	uint64_t write_size = 0;

	if (0 == strcmp("splloader",  partition)) {
		write_size = max(g_status.total_recv_size, SPL_CHECKSUM_LEN);
		if (0 != common_raw_write(partition, write_size, (uint64_t)0, (uint64_t)0, g_eMMCBuf))
			return OPERATE_WRITE_ERROR;
		strcat(partition, "_bak");
		if (0 != common_raw_write(partition, write_size, (uint64_t)0, (uint64_t)0, g_eMMCBuf))
			return OPERATE_WRITE_ERROR;
	} else if (0 == strcmp("uboot",  partition)
		|| 0 == strcmp("trustos",partition)
		|| 0 == strcmp("teecfg",partition)
		|| 0 == strcmp("sml",partition)
		|| 0 == strcmp("vbmeta",partition)) {
		write_size = g_status.total_recv_size;
		if (0 != common_raw_write(partition, write_size, (uint64_t)0, (uint64_t)0, g_eMMCBuf))
			return OPERATE_WRITE_ERROR;
		strcat(partition, "_bak");
		if (0 != common_raw_write(partition, write_size, (uint64_t)0, (uint64_t)0, g_eMMCBuf))
			return OPERATE_WRITE_ERROR;
	} else {
		return OPERATE_IGNORE;
	}

	g_status.unsave_recv_size = 0;
	return OPERATE_SUCCESS;
}

static int is_f2fs_filesystem(uchar *part_name)
{
#if 1
	__le32 f2fs_magic = 0;
	if (strcmp(part_name, "userdata"))
		return 0;
	if (0 != common_raw_read(part_name, (uint64_t)sizeof(f2fs_magic), (uint64_t)0x400, &f2fs_magic)) {
		return 0;
	}
	if (F2FS_SUPER_MAGIC == f2fs_magic)
		return 1;
#endif
	return 0;
}

static int f2fs_write_callback(void* handle, uint64_t size, uint64_t offset, void *buf)
{
	if (0 != common_raw_write((char*)handle, size, (uint64_t)0, offset,  buf)) {
		return -1;
	}
	return 0;
}

static int f2fs_read_callback(void* handle, uint64_t size, uint64_t offset, void *buf)
{
	if (0 != common_raw_read((char*)handle, size, offset, buf)) {
		return -1;
	}
	return 0;
}

OPERATE_STATUS _download_image(void)
{
	int32_t retval = 0;
	OPERATE_STATUS status = 0;
	ulong strip_header = 0;
	uint32_t write_size = 0;
	uchar * write_start = NULL;
	uint32_t fix_nv_checksum;
	sys_img_header *bakup_header = NULL;
	uint64_t total_size = 0;

#if defined (CONFIG_SECURE_BOOT) ||defined (CONFIG_SECBOOT)
	VERIFY_RESULT verify_res;
	boot_mode_t boot_role = get_boot_role();
	if (BOOTLOADER_MODE_DOWNLOAD == boot_role) {
		/* for normal download mode, use dl_secure_process_flow verify*/
		verify_res = dl_secure_process_flow(&strip_header,
			g_dl_eMMCStatus.curUserPartitionName,
			g_status.unsave_recv_size, g_status.total_size, g_eMMCBuf);
	} else {
		/* for autodloader mode, use fb_secure_process_flow verify */
		fastboot_image_size = g_status.unsave_recv_size;
		//printf("g_dl_eMMCStatus.curUserPartitionName:%s; fastboot_image_size:%x,g_status.total_size:%x\n",g_dl_eMMCStatus.curUserPartitionName,fastboot_image_size,g_status.total_size);
		verify_res = fb_secure_process_flow(&strip_header,
			g_dl_eMMCStatus.curUserPartitionName,
			g_status.unsave_recv_size, g_status.total_size, g_eMMCBuf);
	}
	switch (verify_res) {
	case VERIFY_FAIL:
		if (0 == strcmp("system", g_dl_eMMCStatus.curUserPartitionName))
			common_raw_erase(g_dl_eMMCStatus.curUserPartitionName, 0, 0);
			return OPERATE_SYSTEM_ERROR;
	/*for future extension*/
	case VERIFY_STOP_WRITE:
	case VERIFY_NO_NEED:
	case VERIFY_OK:
	default:
		break;
	}
#endif

	/*nv image*/
	if (PARTITION_PURPOSE_NV == g_dl_eMMCStatus.partitionpurpose) {
		debugf("Get all data of partition<%s>,start write to flash\n", g_dl_eMMCStatus.curUserPartitionName);
		fix_nv_checksum = Get_CheckSum((uchar *) g_eMMCBuf, g_status.total_recv_size);
		if (fix_nv_checksum != g_checksum) {
			/*may data transfer error */
			debugf("nv data transfer error,checksum error!\n");
			return OPERATE_CHECKSUM_DIFF;
		}
		status = _nv_img_write(g_dl_eMMCStatus.curUserPartitionName, FIXNV_SIZE);
		return status;
	}

	/*image with backup partition*/
	bakup_header = (sys_img_header *) g_eMMCBuf;
	if ((IMG_BAK_HEADER == bakup_header->mMagicNum) ||
		(0 == strcmp("vbmeta", g_dl_eMMCStatus.curUserPartitionName))) {
		status = _img_write_with_backup(g_dl_eMMCStatus.curUserPartitionName);
		if (OPERATE_IGNORE != status)
			return status;
	}

	/*special operation for SPL with no backup*/
	if (0 == strcmp("splloader", g_dl_eMMCStatus.curUserPartitionName)) {
		splFillCheckData(g_eMMCBuf);
		write_size = max(g_status.unsave_recv_size, SPL_CHECKSUM_LEN);
	} else {
		write_size = g_status.unsave_recv_size - strip_header;
	}
	write_start = g_eMMCBuf + strip_header;

	/*sparse image*/
	if (IMG_WITH_SPARSE == g_dl_eMMCStatus.curImgType) {
		debugf("Handle the saving of image with sparse,name=%s,buf start at %p,size=0x%x\n",
		       g_dl_eMMCStatus.curUserPartitionName, write_start, write_size);

		if (!strcmp(g_dl_eMMCStatus.curUserPartitionName, "userdata")) {
			get_img_partition_size(g_dl_eMMCStatus.curUserPartitionName, &total_size);
			common_raw_erase(g_dl_eMMCStatus.curUserPartitionName, total_size/100, (uint64_t)0LL);
		}

		retval = write_sparse_img(g_dl_eMMCStatus.curUserPartitionName, write_start, (ulong)write_size);
		if (-1 == retval) {
			g_status.unsave_recv_size = 0;
			errorf("Write sparse img fail\n");
			return OPERATE_WRITE_ERROR;
		}
		debugf("Write packed img %s success,return value=%d\n", g_dl_eMMCStatus.curUserPartitionName,retval);
		if (retval > 0) {
			memmove(g_eMMCBuf, write_start + retval, write_size - retval);
			g_status.unsave_recv_size = write_size - retval;
			debugf("After simg , unsave_recv_size=%lld, saved value=%d\n", g_status.unsave_recv_size, retval);
		} else {
			g_status.unsave_recv_size = 0;
			if (is_f2fs_filesystem(g_dl_eMMCStatus.curUserPartitionName)) {
				total_size = 0;
				get_img_partition_size(g_dl_eMMCStatus.curUserPartitionName, &total_size);
				if (emmc_buf_size < (total_size/128)) {
					errorf("resize skip! small buffer, config dts!\n");
				} else {
					retval = f2fs_resize_main(total_size,
						512,
						f2fs_write_callback,
						f2fs_read_callback,
						(void*)g_dl_eMMCStatus.curUserPartitionName,
						g_eMMCBuf,
						emmc_buf_size);
					if (retval==0) {
						debugf("resize userdata ok\n");
					} else {
						errorf("resize userdata error or Nothing to resize\n");
					}
				}
			}
		}
	} else {
		if (0 != common_raw_write(g_dl_eMMCStatus.curUserPartitionName, (uint64_t)write_size, (uint64_t)0,
			(uint64_t)g_dl_eMMCStatus.offset, write_start)) {
			errorf("write %s size 0x%x offset 0x%x fail\n", g_dl_eMMCStatus.curUserPartitionName, write_size, g_dl_eMMCStatus.offset);
			g_status.unsave_recv_size = 0;
			return OPERATE_WRITE_ERROR;
		}

		g_dl_eMMCStatus.offset += write_size;
		g_status.unsave_recv_size = 0;
	}

	return OPERATE_SUCCESS;
}

OPERATE_STATUS regular_download_process(uint32_t size, char *buf)
{
	uint32_t lastSize;
	OPERATE_STATUS ret;
	uint64_t buf_size = emmc_buf_size > SZ_256M ? SZ_256M : emmc_buf_size;

	if (buf_size >= (g_status.unsave_recv_size + size)) {
		memcpy((uchar *) g_sram_addr, buf, size);
		g_sram_addr += size;
		g_status.unsave_recv_size += size;

		if (g_status.total_recv_size == g_status.total_size) {
			ret = _download_image();
			return ret;
		}
	} else {
		lastSize = buf_size - g_status.unsave_recv_size;
		debugf("Unsaved buf size overflow the whole buffer size,lastsize=%u,unsavedsize=%u\n", lastSize, g_status.unsave_recv_size);
		if (0 != lastSize)
			memcpy((unsigned char *)g_sram_addr, buf, lastSize);

		g_status.unsave_recv_size = buf_size;

		ret = _download_image();
		if (OPERATE_SUCCESS != ret)
			return ret;

		g_sram_addr = (unsigned long) (g_eMMCBuf + g_status.unsave_recv_size);
		memcpy((uchar *) g_sram_addr, (char *)(&buf[lastSize]), size - lastSize);
		g_status.unsave_recv_size += size - lastSize;
		g_sram_addr = (unsigned long) (g_eMMCBuf + g_status.unsave_recv_size);
		debugf("After write,unsaved recv size=%lld\n", g_status.unsave_recv_size);

		if (g_status.total_recv_size == g_status.total_size) {
			ret = _download_image();
			return ret;
		}

	}
	return OPERATE_SUCCESS;
}

OPERATE_STATUS dl_erase(uchar * partition_name, uint64_t size)
{
	uchar *backup_partition_name = NULL;

	if ((0 == strcmp(partition_name, "erase_all")) && (0xffffffff == size)) {
		debugf("Erase all!\n");
		if (0 != common_raw_erase(partition_name, 0, 0))
			return OPERATE_WRITE_ERROR;
	} else {
		debugf("erase partition %s!\n", partition_name);

		if (0 != common_raw_erase(partition_name, size, 0)) {
			return OPERATE_WRITE_ERROR;
		}

		backup_partition_name = _get_backup_partition_name(partition_name);

		if (NULL != backup_partition_name) {
			if (0 != common_raw_erase(backup_partition_name, size, 0))
				return OPERATE_WRITE_ERROR;
		}

		if(0 == strcmp(partition_name, UBOOT_LOG_PARTITION)) {
		/* in download mode, initialize log if uboot log partition is erased */
			reinit_write_log();
		}
	}


	return OPERATE_SUCCESS;
}


int32_t _read_repair_nv_img(uchar * partition_name, uchar * buf)
{
	uchar *backup_partition_name = NULL;
	uchar header_buf[NV_HEADER_SIZE];
	uchar backup_header_buf[NV_HEADER_SIZE];
	nv_header_t *header_p = header_buf;
	nv_header_t *backup_header_p = backup_header_buf;
	uchar * backup_nv_buf = NULL;
	int status = ORIGIN_BACKUP_NV_OK;
	int ret = 0;

	backup_nv_buf = buf + SZ_16M;

	do {
		/*read origin image header */
		if (0 != common_raw_read(partition_name, NV_HEADER_SIZE, (uint64_t)0, header_buf)) {
			errorf("read origin nv image header failed\n");
			status |= ORIGIN_NV_DAMAGED;
			break;
		}

		if (NV_HEAD_MAGIC != header_p->magic) {
			errorf("nv header magic error, wrong magic=0x%x\n", header_p->magic);
			status |= ORIGIN_NV_DAMAGED;
			break;
		}

		/*read origin image */
		if (0 != common_raw_read(partition_name, (uint64_t)(header_p->len), NV_HEADER_SIZE, buf)) {
			errorf("read origin nv image failed\n");
			status |= ORIGIN_NV_DAMAGED;
			break;
		}

		/*check crc */
		if (fdl_check_crc(buf, header_p->len, header_p->checksum)) {
			debugf("read origin nv image success and crc correct\n");
		} else {
			errorf("check origin nv image crc wrong\n");
			status |= ORIGIN_NV_DAMAGED;
		}
	} while(0);

	/*get the backup partition name */
	backup_partition_name = _get_backup_partition_name(partition_name);
	if (NULL == backup_partition_name)
		return 0;

	do {
		/*read backup header */
		if (0 != common_raw_read(backup_partition_name, NV_HEADER_SIZE, (uint64_t)0, backup_header_buf)) {
			errorf("read backup nv image header failed\n");
			status |= BACKUP_NV_DAMAGED;
			break;
		}

		if (NV_HEAD_MAGIC != backup_header_p->magic) {
			errorf("backup nv header magic error, wrong magic=0x%x\n", backup_header_p->magic);
			status |= BACKUP_NV_DAMAGED;
			break;
		}

		/*read bakup image */
		if (0 != common_raw_read(backup_partition_name, (uint64_t)(backup_header_p->len), NV_HEADER_SIZE, backup_nv_buf)) {
			errorf("read backup nv image failed\n");
			status |= BACKUP_NV_DAMAGED;
			break;
		}

		/*check crc */
		if (fdl_check_crc(backup_nv_buf, backup_header_p->len, backup_header_p->checksum)) {
			debugf("read backup nv image success and crc correct\n");
		} else {
			errorf("check backup nv image crc wrong\n");
			status |= BACKUP_NV_DAMAGED;
		}
	} while(0);

	switch (status) {
	case ORIGIN_BACKUP_NV_OK :
		debugf("both org and bak nv partition are ok\n");
		ret = 1;
		break;
	case ORIGIN_NV_DAMAGED :
		memcpy(buf, backup_nv_buf, backup_header_p->len);
		if (0 != common_raw_write(partition_name, NV_HEADER_SIZE, (uint64_t)0, (uint64_t)0, backup_header_buf)) {
			ret = 0;
			break;
		}
		debugf("Start to write remain blocks of origin NV partition\n");
		if (0 != common_raw_write(partition_name, (uint64_t)(backup_header_p->len), (uint64_t)0, NV_HEADER_SIZE, backup_nv_buf)) {
			ret = 0;
			break;
		}
		ret = 1;
		break;
	case BACKUP_NV_DAMAGED :
		if (0 != common_raw_write(backup_partition_name, NV_HEADER_SIZE, (uint64_t)0, (uint64_t)0, header_buf)) {
			ret = 0;
			break;
		}
		debugf("Start to write remain blocks of backup NV partition\n");
		if (0 != common_raw_write(backup_partition_name, (uint64_t)(header_p->len), (uint64_t)0, NV_HEADER_SIZE, buf)) {
			ret = 0;
			break;
		}
		ret = 1;
		break;
	case ORIGIN_NV_DAMAGED | BACKUP_NV_DAMAGED :
		errorf("both org and bak partition are damaged!\n");
		ret = 0;
		break;
	}

	return ret;
}


OPERATE_STATUS dl_read_start(uchar * partition_name, uint64_t size)
{
	size_t sblock_size = 0;
	struct ext2_sblock *sblock = NULL;

	strcpy(g_dl_eMMCStatus.curUserPartitionName, partition_name);
	/*get special partition attr */
	_get_partition_attribute(partition_name);

	if (PARTITION_PURPOSE_NV == g_dl_eMMCStatus.partitionpurpose) {
		if (!_read_repair_nv_img(g_dl_eMMCStatus.curUserPartitionName, g_eMMCBuf))
			return OPERATE_SYSTEM_ERROR;
	}


	if (0 == strcmp("prodnv", g_dl_eMMCStatus.curUserPartitionName)) {
		sblock_size = sizeof(struct ext2_sblock);
		sblock = malloc(sblock_size);
		if (NULL == sblock) {
			errorf("malloc sblock failed\n");
			goto err;
		}

		if (0 != common_raw_read(g_dl_eMMCStatus.curUserPartitionName, (uint64_t)sblock_size, (uint64_t)1024, sblock)) {
			errorf("read prodnv super block fail\n");
			goto err;
		}

		if (sblock->magic != EXT2_MAGIC) {
			errorf("bad prodnv image magic(0x%x)\n", sblock->magic);
			goto err;
		}
		free(sblock);
	}

	return OPERATE_SUCCESS;
err:
	if (NULL != sblock)
		free(sblock);
	return OPERATE_SYSTEM_ERROR;
}

OPERATE_STATUS dl_read_midst(uint32_t size, uint64_t off, uchar * buf)
{
	if (PARTITION_PURPOSE_NV == g_dl_eMMCStatus.partitionpurpose) {
		memcpy(buf, (uchar *) (g_eMMCBuf + off), size);
	} else {
		if (0 != common_raw_read(g_dl_eMMCStatus.curUserPartitionName, (uint64_t)size, (uint64_t)off, buf)) {
			errorf("read error!\n");
			return OPERATE_SYSTEM_ERROR;
		}
	}

	return OPERATE_SUCCESS;
}

OPERATE_STATUS dl_read_end(void)
{
	return OPERATE_SUCCESS;
}


OPERATE_STATUS dl_download_start(uchar * partition_name, uint64_t size, uint32_t nv_checksum)
{
	int i = 0;
	uint32_t size_in_lba = 0;

	g_status.total_size = size;
	strcpy(g_dl_eMMCStatus.curUserPartitionName, partition_name);
	g_dl_eMMCStatus.offset = 0;

	/*get special partition attr */
	_get_partition_attribute(partition_name);

	if (PARTITION_PURPOSE_NV == g_dl_eMMCStatus.partitionpurpose) {
		debugf("partition purpose is NV\n");
		if (size > FIXNV_SIZE) {
			errorf("size(0x%llx) beyond FIXNV_SIZE:0x%x !\n", size, FIXNV_SIZE);
			return OPERATE_INVALID_SIZE;
		}
		memset(g_eMMCBuf, 0xff, FIXNV_SIZE + NV_HEADER_SIZE);
		g_checksum = nv_checksum;
	} else if (0 == strcmp("splloader", partition_name)) {
		memset(g_eMMCBuf, 0xff, SPL_CHECKSUM_LEN);
	}

	g_status.total_recv_size = 0;
	g_status.unsave_recv_size = 0;
	g_sram_addr = (void *) g_eMMCBuf;

	prepare_alternative_buffers();
	return OPERATE_SUCCESS;
}

OPERATE_STATUS dl_download_midst(uint32_t size, char *buf)
{
	uint32_t lastSize;
	uint32_t nSectorCount;
	uint32_t fix_nv_checksum;
	int ret = 0;
	ulong sec_offset = 0;

	int local_buf_index;
	sparse_header_t sparse_header_test_head;

	/*adjust the image type via the header magic*/
	if (0 == g_status.total_recv_size ) {
#ifdef CONFIG_SECURE_BOOT
		if (0 == strcmp(buf, HEADER_NAME))
			sec_offset = KEY_INFO_SIZ + VLR_INFO_SIZ;
#endif
#ifdef CONFIG_SECBOOT
		if (IMG_BAK_HEADER == ((sys_img_header *)buf)->mMagicNum)
			sec_offset = SYS_HEADER_SIZE;
#endif
		memset(&sparse_header_test_head, 0, sizeof(sparse_header_t));
		memcpy(&sparse_header_test_head, buf + sec_offset, sizeof(sparse_header_test_head));

		if (sparse_header_test_head.magic != SPARSE_HEADER_MAGIC)
			g_dl_eMMCStatus.curImgType = IMG_RAW;
		else
			g_dl_eMMCStatus.curImgType = IMG_WITH_SPARSE;
	}

	g_status.total_recv_size += size;

#if defined (CONFIG_SECURE_BOOT) ||defined (CONFIG_SECBOOT)

#ifdef CONFIG_SYSTEM_VERIFY
	ret = regular_download_process(size, buf);
#else
	if ((IMG_RAW == g_dl_eMMCStatus.curImgType) &&
                ((0 == strcmp("system", g_dl_eMMCStatus.curUserPartitionName)) || (0 == strcmp("super", g_dl_eMMCStatus.curUserPartitionName))))
		ret = speedup_download_process(size, buf);
	else
		ret = regular_download_process(size, buf);
#endif

#else
	if ((IMG_RAW == g_dl_eMMCStatus.curImgType)
	     && ((PARTITION_PURPOSE_NV != g_dl_eMMCStatus.partitionpurpose)
		  && (g_status.total_size > ALTERNATIVE_BUFFER_SIZE)))
		ret = speedup_download_process(size, buf);
	else
		ret = regular_download_process(size, buf);
#endif

	return ret;

}

OPERATE_STATUS dl_download_flush_data(uint32_t total_len, unsigned char *total_buf,
						uint16_t size, unsigned char *buf)
{
	unsigned char *pdata = (unsigned char *)total_buf;
	unsigned char hash[32];
	unsigned char Cnt;

	if (0x20 != size)
		return OPERATE_INVALID_SIZE;

	sha256_csum_wd((const unsigned char*)pdata, (uint32_t)total_len, hash, 0);

	if (memcmp(hash, buf, 32))
		return OPERATE_CHECKSUM_DIFF;

	return OPERATE_SUCCESS;
}

OPERATE_STATUS dl_download_end(void)
{
	if(!strcmp(g_dl_eMMCStatus.curUserPartitionName,"miscdata")){
		if(0 != common_raw_erase(g_dl_eMMCStatus.curUserPartitionName, 0x400, DATETIME_OFFSET))
			return OPERATE_WRITE_ERROR;
		if(0 != common_raw_erase(g_dl_eMMCStatus.curUserPartitionName, 0x400, DEBUG_INFO_OFFSET))
			return OPERATE_WRITE_ERROR;
	}
	if (g_status.unsave_recv_size != 0) {
		debugf("unsaved size is not zero!\n");
		return OPERATE_SYSTEM_ERROR;
	}

	g_status.total_size = 0;

	if (0 != common_partition_sync(g_dl_eMMCStatus.curUserPartitionName))
		return OPERATE_WRITE_ERROR;

	return OPERATE_SUCCESS;
}

OPERATE_STATUS dl_repartition(uchar * partition_cfg, uint16_t total_partition_num,
									uchar version, uchar size_unit)
{
	disk_partition_t *partition_info;
	int32_t res = 0;

	/*prepare mem to store <total_partition_num> partitions' info */
	partition_info = malloc(sizeof(disk_partition_t) * total_partition_num);
	if (NULL == partition_info) {
		errorf("No space to store partition_info!\n");
		return OPERATE_SYSTEM_ERROR;
	}

	res = _parser_repartition_cfg(partition_info, partition_cfg, total_partition_num, version, size_unit);
	if (res < 0) {
		free(partition_info);
		return OPERATE_SYSTEM_ERROR;
	}

	res = common_repartition(partition_info, (int)total_partition_num);
	free(partition_info);

	if (0 == res)
		return OPERATE_SUCCESS;
	else
		return OPERATE_SYSTEM_ERROR;
}

OPERATE_STATUS dl_read_ref_info(char *part_name, uint16_t size, uint64_t offset,
	uchar *receive_buf, uchar  *transmit_buf)
{
	if(0 != common_raw_read(part_name, (uint64_t)size, offset, transmit_buf)) {
		/* read old info from flash fail, transmit the receive info back to tool */
		debugf("read old info from flash fail\n");
		memcpy(transmit_buf, receive_buf, (size_t)size);
	}
	/* update receive ref info to flash */
	if(0 != common_raw_write(part_name, (uint64_t)size, (uint64_t)0, offset, receive_buf)){
		debugf("update receive ref info to flash fail\n");
		return  OPERATE_SYSTEM_ERROR;
	}
	return OPERATE_SUCCESS;
}

OPERATE_STATUS dl_record_pacdatetime(uchar * buf, uint64_t size)
{
	if(0 != common_raw_write(DATATIME_PARTNAME, size, (uint64_t)0, DATETIME_OFFSET, buf)){
		return OPERATE_WRITE_ERROR;
	}
	return OPERATE_SUCCESS;
}

#ifdef CONFIG_EMMC_DDR_CHECK_TYPE
static uint32_t flash_ddr_size_tab[] = {128, 256, 512, 1*1024, 2*1024, 3*1024, 4*1024, \
                6*1024, 8*1024, 16*1024, 32*1024, 64*1024, 128*1024, 256*1024, 512*1024};

uint32_t get_correct_size(uint32_t size)
{
	uint32_t i = 0;
	uint32_t diff_size = 50;
	uint32_t read_size = size;

	for(i = 0; i < sizeof(flash_ddr_size_tab)/sizeof(uint32_t); i++) {
		if(i < 3)
			diff_size = 50;
		else diff_size = 100;
		if(flash_ddr_size_tab[i]) {
			if(abs(flash_ddr_size_tab[i] - size) < diff_size) {
				read_size = flash_ddr_size_tab[i];
				break;
			}

		}
	}
	printf("correct size:%u\r\n", read_size);
	return read_size;
}

OPERATE_STATUS dl_get_flashtype(uchar * content, uint16_t * size)
{
	struct FLASH_TYPE flash_type;
	char temp[sizeof(struct FLASH_TYPE)];
	int i = 0;
	int j = 0;

	memset(&flash_type, 0, sizeof(struct FLASH_TYPE));

	/* dram size */
	int dram_size_inMB = 0;
	printf("get real ram size: 0x%x\n", get_real_ram_size());
	dram_size_inMB = ((get_real_ram_size()/1024/1024)+5);
	printf("dram_size_inMB:%u\n", dram_size_inMB);
	flash_type.mid = get_correct_size(dram_size_inMB);

	/* calculate emmc size in GB */
	int emmc_size = 0, emmc_size_inMB = 0;
	emmc_size = emmc_get_capacity(PARTITION_USER)/1000/1000;
	emmc_size_inMB = (emmc_size+500)/1000*1024;

	/* did field is used for emmc size */
	flash_type.did = get_correct_size(emmc_size_inMB);
	printf("emmc_size:%llu,emmc_size_inMB:%d\n", emmc_get_capacity(PARTITION_USER), emmc_size_inMB);
	*size = sizeof(struct FLASH_TYPE);
	memcpy(temp, &flash_type, *size);
	for (i = 0; i < *size; i++) {
		if ((i % 4) == 0)
			j = i + 4;
		content[i] = temp[--j];
	}
	return 1;
}
#endif

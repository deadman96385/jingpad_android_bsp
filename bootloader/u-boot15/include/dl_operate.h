#ifndef _FDL_EMMC_OPERATE_H
#define _FDL_EMMC_OPERATE_H

#include <linux/sizes.h>
#include "dl_cmd_proc.h"

#define IMG_BAK_HEADER 0x42544844

#define NV_HEADER_SIZE            (512)

#define ORIGIN_BACKUP_NV_OK 0x0
#define ORIGIN_NV_DAMAGED      0x1
#define BACKUP_NV_DAMAGED   0x2

#define MAGIC_DATA	0xAA55A5A5

/*according to standard ,the first usable LBA is 34,
but actually reserve 1MB space before the first partition can enhance the erase speed*/
#define FIRST_USABLE_LBA_FOR_PARTITION    (34)

#define MAX_SIZE_FLAG	0xFFFFFFFF

#define ALTERNATIVE_BUFFER_SIZE  0x200000

#define TRUE   1		/* Boolean true value. */
#define FALSE  0		/* Boolean false value. */

#define DATETIME_OFFSET 0x81400
#define DATATIME_PARTNAME "miscdata"

typedef enum _PARTITION_IMG_TYPE {
	IMG_RAW = 0,
	IMG_WITH_SPARSE = 1,
	IMG_TYPE_MAX
} PARTITION_IMG_TYPE;

typedef enum _PARTITION_PURPOSE {
	PARTITION_PURPOSE_NORMAL,
	PARTITION_PURPOSE_NV,
	PARTITION_PURPOSE_MAX
} PARTITION_PURPOSE;

typedef struct DL_EMMC_STATUS_TAG {
	uint64_t offset;
	uchar curUserPartitionName[32];
	PARTITION_PURPOSE partitionpurpose;
	PARTITION_IMG_TYPE curImgType;
} DL_EMMC_STATUS;

typedef struct DL_FILE_STATUS_TAG {
	uint64_t total_size;
	uint64_t total_recv_size;
	uint64_t unsave_recv_size;
} DL_EMMC_FILE_STATUS;

typedef struct _SPECIAL_PARTITION_CFG {
	uchar *partition;
	uchar *bak_partition;
	PARTITION_IMG_TYPE imgattr;
	PARTITION_PURPOSE purpose;
} SPECIAL_PARTITION_CFG;

typedef struct {
	uint32_t version;
	uint32_t magicData;
	uint32_t checkSum;
	uint32_t hashLen;
} EMMC_BootHeader;

typedef struct _ALTER_BUFFER_ATTR {
	uchar* addr;
	uchar* pointer;
	uint32_t size;
	uint32_t used;
	uint32_t spare;
	uint32_t status;
	struct _ALTER_BUFFER_ATTR* next;
} ALTER_BUFFER_ATTR;

typedef enum _ALTERNATIVE_BUFFER_STATUS {
	BUFFER_CLEAN,
	BUFFER_DIRTY
} ALTERNATIVE_BUFFER_STATUS;

typedef struct FLASH_TYPE {
	int mid;/* as ddr size */
	int did;/* as emmc size */
	int eid;/* reserved */
	int flag;
} FLASH_T;

OPERATE_STATUS dl_download_start(uchar * partition_name, uint64_t size, uint32_t nv_checksum);
OPERATE_STATUS dl_download_midst(uint32_t size, char *buf);
OPERATE_STATUS dl_download_end(void);
OPERATE_STATUS dl_read_start(uchar * partition_name, uint64_t size);
OPERATE_STATUS dl_read_midst(uint32_t size, uint64_t off, uchar * buf);
OPERATE_STATUS dl_read_end(void);
OPERATE_STATUS dl_erase(uchar * partition_name, uint64_t size);
OPERATE_STATUS dl_repartition(uchar * partition_cfg, uint16_t total_partition_num,
									uchar version, uchar size_unit);
OPERATE_STATUS dl_read_ref_info(char *part_name, uint16_t size, uint64_t offset,
	uchar *receive_buf, uchar  *transmit_buf);

OPERATE_STATUS dl_record_pacdatetime(uchar * buf, uint64_t size);
#ifdef CONFIG_EMMC_DDR_CHECK_TYPE
OPERATE_STATUS dl_get_flashtype(uchar * content, uint16_t * size);
#endif
#ifdef CONFIG_DTS_MEM_LAYOUT
int set_buf_base_size();
#endif

OPERATE_STATUS dl_download_flush_data(uint32_t total_len, unsigned char *total_buf, uint16_t size, unsigned char *buf);

#endif //_FDL_EMMC_OPERATE_H

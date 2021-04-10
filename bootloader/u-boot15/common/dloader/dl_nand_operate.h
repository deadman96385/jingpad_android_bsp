#ifndef FDL_NAND_OPERATE_H
#define FDL_NAND_OPERATE_H

#include <dl_cmd_def.h>
#include <linux/mtd/mtd.h>
#include <ubi_uboot.h>
#include <linux/list.h>
#include <nand.h>
#include <linux/mtd/nand.h>

typedef struct {
	char *vol;
	char *bakvol;
} dl_nv_info_t;

typedef struct {
	char name[MAX_PARTITION_NAME_SIZE];	//mtd partition name
	uint64_t size;		//mtd part size
	uint64_t rw_point;	//nand flash read/write offset point
} dl_mtd_info_t;

typedef struct {
	struct ubi_device *dev;
	int dev_num;
	//char *cur_volnm;
	char cur_volnm[UBI_VOL_NAME_MAX + 1];
	struct ubi_volume_desc *cur_voldesc;
} dl_ubi_info_t;

typedef enum {
	PART_TYPE_MIN,
	PART_TYPE_MTD,
	PART_TYPE_UBI,
	PART_TYPE_MAX
} dl_part_type;

typedef struct fdl_download_status {
	nand_info_t *nand;
	dl_part_type part_type;
	dl_mtd_info_t mtd;
	dl_ubi_info_t ubi;
	unsigned long total_dl_size;	//size to be recvd
	unsigned long recv_size;	//recv size from tool
	unsigned long unsv_size;	//data unsaved in buf
	char *buf;		//buf for data received from tool
	unsigned int bufsize;	//max buf size
	unsigned int rp;	//read point of buf,no use now
	unsigned int wp;	//write point of buf
} dl_status_t;

typedef struct {
	char name[UBI_VOL_NAME_MAX + 1];
	long long size;		//size in byte
	int autoresize;
} fdl_ubi_vtbl_t;

typedef struct {
	char *name;
	long long size;
	int autoresize;
	struct list_head list;
} fdl_ubi_cvol_t;

typedef struct MCP_TYPE {
	int flag;
	int blocksize;
	int pagesize;
} MCP_T;

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

#define UBIFS_NODE_MAGIC  0x06101831
#define AUTO_RESIZE_FLAG  0xFFFFFFFF
#ifdef CONFIG_SECURE_BOOT
#define FDL_BUF_LEN  (100*1024*1024)
#else
#define FDL_BUF_LEN  (1*1024*1024)
#endif

#define DATETIME_OFFSET 0x81400
#define DATATIME_PARTNAME "miscdata"
/**
 * dl_download_start
 *
 * Get download info from download start command which  
 * will used in next step
 *
 * @param part partition/volume name
 * @param size total download size
 * @param nv_checksum NA
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_download_start(char *name, uint32_t size, uint32_t nv_checksum);

/**
 * dl_download_midst
 *
 * Save data to fdl buf and finally write it to nand flash
 *
 * @param size total download size
 * @param buf data recvd
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_download_midst(uint32_t size, char *buf);

/**
 * dl_download_end
 *
 * Set download end
 *
 * @param void
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_download_end(void);

/**
 * dl_nand_read_start
 *
 * Get partition/volume info from read start command which  
 * will used in next step
 *
 * @param part partition/volume name
 * @param size total size
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_read_start(char *part, uint32_t size);

/**
 * dl_nand_read_midst
 *
 * Read partition/volume data
 *
 * @param size size to be read
 * @param off offset of begin of part/vol
 * @param buf data saved
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_read_midst(uint32_t size, uint32_t off, uchar * buf);

/**
 * dl_read_end
 *
 * Set read flash end
 *
 * @param void
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_read_end(void);

/**
 * dl_erase
 *
 * Erase partition/volume
 *
 * @param part partition/volume name
 * @param size size to be erased(no use now)
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_erase(char *part, uint32_t size);

OPERATE_STATUS dl_repartition(uchar * partition_cfg, uint16_t total_partition_num,
									uchar version, uchar size_unit);


OPERATE_STATUS dl_get_mcptype(uchar * content, uint16_t * size);

OPERATE_STATUS dl_download_flush_data(uint32_t total_len, unsigned char *total_buf, uint16_t size, unsigned char *buf);

#endif /*FDL_NAND_OPERATE_H */

#ifndef _DL_COMMON_
#define _DL_COMMON_

#include "linux/types.h"

/*loader_common.h has the same define*/
#define NV_HEAD_MAGIC	(0x00004e56)
#define NV_VERSION		(101)
#define NV_HEAD_LEN	(512)

#define BOOTLOADER_HEADER_OFFSET 0x20

#define PART_SAME 1
#define PART_DIFF   0
#define PART_FAIL   -1
#define PART_FATAL_ERR -2

typedef struct _NV_HEADER {
	uint32_t magic;
	uint32_t len;
	uint32_t checksum;
	uint32_t version;
} nv_header_t;

unsigned short fdl_calc_checksum(unsigned char *data, unsigned long len);
unsigned char fdl_check_crc(uint8_t * buf, uint32_t size, uint32_t checksum);
unsigned long Get_CheckSum(const unsigned char *src, int len);

#endif

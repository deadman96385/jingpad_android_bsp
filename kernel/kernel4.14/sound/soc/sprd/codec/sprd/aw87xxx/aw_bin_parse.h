#ifndef _AW86801_BIN_PARSE_H_
#define _AW86801_BIN_PARSE_H_

#define NULL    ((void *)0)
#define GET_32_DATA(w, x, y, z) ((unsigned int)(((w) << 24) | ((x) << 16) | ((y) << 8) | (z)))
#define BIN_NUM_MAX   100
#define HEADER_LEN    60
/*********************************************************
 *
 * header information
 *
 ********************************************************/
enum bin_header_version_enum {
	HEADER_VERSION_1_0_0 = 0x01000000,
};

enum data_type_enum {
	DATA_TYPE_REGISTER = 0x00000000,
	DATA_TYPE_DSP_REG = 0x00000010,
	DATA_TYPE_DSP_CFG = 0x00000011,
	DATA_TYPE_SOC_REG = 0x00000020,
	DATA_TYPE_SOC_APP = 0x00000021,
	DATA_TYPE_MULTI_BINS = 0x00002000,
};

enum data_version_enum {
	DATA_VERSION_V1 = 0X00000001,	/*default little edian */
	DATA_VERSION_MAX,
};

struct bin_header_info {
	unsigned int header_len;
	unsigned int check_sum;
	unsigned int header_ver;
	unsigned int bin_data_type;
	unsigned int bin_data_ver;
	unsigned int bin_data_len;
	unsigned int ui_ver;
	unsigned char chip_type[20];
	unsigned int reg_byte_len;
	unsigned int data_byte_len;
	unsigned int device_addr;
	unsigned int valid_data_len;
	unsigned int valid_data_addr;

	unsigned int reg_num;
	unsigned int reg_data_byte_len;
	unsigned int download_addr;
	unsigned int app_version;
};

/************************************************************
*
* function define
*
************************************************************/
struct bin_container {
	unsigned int len;
	unsigned char data[];
};

struct aw_bin {
	char *p_addr;
	unsigned int all_bin_parse_num;
	unsigned int multi_bin_parse_num;
	unsigned int single_bin_parse_num;
	struct bin_header_info header_info[BIN_NUM_MAX];
	struct bin_container info;
};

extern int aw_parsing_bin_file(struct aw_bin *bin);
int aw_parse_bin_header_1_0_0(struct aw_bin *bin);
#endif

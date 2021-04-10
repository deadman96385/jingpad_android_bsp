#ifndef TEECFG_PARSE_H
#define TEECFG_PARSE_H


#define TEECFG_HEADER_MAGIC      "TEE_CONFIG_HEADER"
#define SEG_NAME_MAX_SIZE      24
#define SEG_DESC_MAX_SIZE      20


typedef struct
{
	unsigned char name[SEG_NAME_MAX_SIZE];
	unsigned int offset;
	unsigned int size;
}seg_desc_t;

typedef struct
{
	unsigned char name[SEG_NAME_MAX_SIZE]; //"TEE_CONFIG_HEADER"
	unsigned int version; //v0.1
	unsigned int size; //sizeof(tee_config_header_t)
	unsigned int tos_size; //tos_size value
	unsigned int seg_desc_off; //the first seg_desc offset in the teecfg file
	unsigned int seg_desc_num; //seg_desc numbers
	unsigned int reserved0; //reserved
	unsigned int reserved1; //reserved
	unsigned int reserved2; //reserved
	seg_desc_t seg_desc[SEG_DESC_MAX_SIZE]; //seg descriptor infos
} __attribute__((packed)) tee_config_header_t;

#endif




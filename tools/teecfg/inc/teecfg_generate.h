/**
 * ----------------------------------------------------------------------------
 * Copyright (C) 2019 UNISOC Technologies Co.,Ltd.
 *
 * All rights reserved.
 * ----------------------------------------------------------------------------
 * This document contains proprietary information belonging to UNISOC.
 * Passing on and copying of this document, use and communication of its
 * contents is not permitted without prior written authorisation.
 * ----------------------------------------------------------------------------
 */

#ifndef _TEECFG_GENERATE_H
#define _TEECFG_GENERATE_H

#include <stdbool.h>
#include "../inc/libxml/tree.h"


#define TEE_CONFIG_DEBUG      0

#define TEECFG_HEADER_MAGIC      "TEE_CONFIG_HEADER"
#define SEG_NAME_MAX_SIZE      24
#define SEG_DESC_MAX_SIZE      20

typedef struct
{
	unsigned char name[SEG_NAME_MAX_SIZE];
	unsigned int offset;
	unsigned int size;
} __attribute__((packed)) seg_desc_t;

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
	seg_desc_t seg_desc[SEG_DESC_MAX_SIZE]; //to be filled
} __attribute__((packed)) tee_config_header_t;

typedef void (*callback)(unsigned char *name, unsigned int offset, unsigned int size);

typedef struct
{
	unsigned char *xml_file_name;
	xmlChar *xml_file_path;
	FILE *bin_fp;
	unsigned int offset;
	callback set_seg_info;
} __attribute__((aligned(8))) tee_config_info_t;

#define TEE_CONFIG_HEADER_SIZE      (sizeof(tee_config_header_t))

tee_config_header_t tee_config_header;

int generate_teecfg_image(unsigned char *xml_file_path, unsigned char *outfile);

#endif




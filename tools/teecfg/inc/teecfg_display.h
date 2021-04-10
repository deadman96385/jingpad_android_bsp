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

#ifndef TEECFG_DISPLAY_H
#define TEECFG_DISPLAY_H

#include "teecfg_generate.h"
#include "list.h"


#define PROPERTY_NAME_MAX_SIZE      24
#define TLV_STRING_MAX_SIZE      255
#define TEECFG_MEM_MAX_SIZE      128*1024

typedef struct _tlv_t
{
	struct list_node node;
	unsigned short t;
	unsigned char l;
	union
	{
		unsigned char int8_val;
		unsigned short int16_val;
		unsigned int int32_val;
		unsigned long int64_val;
		unsigned char bool_val;
		unsigned char str_val[TLV_STRING_MAX_SIZE];
	}v;
}tlv_t;

typedef struct _property_info_t
{
	struct list_node node;
	struct list_node *tlv_node_head;
	unsigned char name[PROPERTY_NAME_MAX_SIZE];
}property_info_t;

typedef struct _seg_info_t
{
	struct list_node node;
	struct list_node *property_node_head;
	unsigned char name[SEG_NAME_MAX_SIZE];
}seg_info_t;

int display_teecfg_image(const char *inputfile);

#endif




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

#ifndef _COMMON_H
#define _COMMON_H


#define ATTR_TYPE_UINT8      "ATTR_TYPE_UINT8"
#define ATTR_TYPE_UINT16      "ATTR_TYPE_UINT16"
#define ATTR_TYPE_UINT32      "ATTR_TYPE_UINT32"
#define ATTR_TYPE_UINT64      "ATTR_TYPE_UINT64"
#define ATTR_TYPE_BOOL      "ATTR_TYPE_BOOL"
#define ATTR_TYPE_STRING      "ATTR_TYPE_STRING"
#define ATTR_TAG_IN_TEECFG_HEADER      "ATTR_TAG_IN_TEECFG_HEADER"

#define ATTR_TYPE_UINT_PREFIX      "0x"
#define ATTR_TYPE_BOOL_TRUE      "true"
#define ATTR_TYPE_BOOL_FALSE      "false"

#define XML_FILE_NAME_TAG_SIZE      (sizeof(unsigned short))
#define XML_FILE_NAME_LEN_SIZE      (sizeof(unsigned char))
#define ATTR_ID_TAG_SIZE      (sizeof(unsigned short))
#define ATTR_ID_LEN_SIZE      (sizeof(unsigned char))
#define ATTR_TYPE_UINT8_TAG_SIZE      (sizeof(unsigned short))
#define ATTR_TYPE_UINT8_LEN_SIZE      (sizeof(unsigned char))
#define ATTR_TYPE_UINT8_LEN_VALUE      (sizeof(unsigned char))
#define ATTR_TYPE_UINT16_TAG_SIZE      (sizeof(unsigned short))
#define ATTR_TYPE_UINT16_LEN_SIZE      (sizeof(unsigned char))
#define ATTR_TYPE_UINT16_LEN_VALUE      (sizeof(unsigned short))
#define ATTR_TYPE_UINT32_TAG_SIZE      (sizeof(unsigned short))
#define ATTR_TYPE_UINT32_LEN_SIZE      (sizeof(unsigned char))
#define ATTR_TYPE_UINT32_LEN_VALUE      (sizeof(unsigned int))
#define ATTR_TYPE_UINT64_TAG_SIZE      (sizeof(unsigned short))
#define ATTR_TYPE_UINT64_LEN_SIZE      (sizeof(unsigned char))
#define ATTR_TYPE_UINT64_LEN_VALUE      (8)
#define ATTR_TYPE_BOOL_TAG_SIZE      (sizeof(unsigned short))
#define ATTR_TYPE_BOOL_LEN_SIZE      (sizeof(unsigned char))
#define ATTR_TYPE_BOOL_LEN_VALUE      (sizeof(unsigned char))
#define ATTR_TYPE_STRING_TAG_SIZE      (sizeof(unsigned short))
#define ATTR_TYPE_STRING_LEN_SIZE      (sizeof(unsigned char))

#define ERR_WRONG_TYPE        (-1)
#define ERR_WRONG_RANGE       (-2)
#define ERR_WRONG_FORMAT      (-3)
#define ERR_WRONG_TAG         (-4)

int handle_each_xml_file(tee_config_info_t *info);

#endif




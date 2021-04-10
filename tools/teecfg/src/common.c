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

#include <string.h>
#include "../inc/libxml/xpath.h"

#include "../inc/teecfg_generate.h"
#include "../inc/common.h"


const unsigned short XML_FILE_NAME_TAG = 0x9faa;
const unsigned short ATTR_PROPERTY_ID_TAG = 0x8faa;
const unsigned short ATTR_TYPE_UINT8_TAG = 0x7faa;
const unsigned short ATTR_TYPE_UINT16_TAG = 0x7fbb;
const unsigned short ATTR_TYPE_UINT32_TAG = 0x7fcc;
const unsigned short ATTR_TYPE_UINT64_TAG = 0x7fdd;
const unsigned short ATTR_TYPE_BOOL_TAG = 0x7fee;
const unsigned short ATTR_TYPE_STRING_TAG = 0x7fff;

static unsigned int seg_offset = 0;


/**
 * ----------------------------------------------
 * |------------ common functions --------------|
 * ----------------------------------------------
 */
/**
 * write_xml_file_name_tlv:
 * @fp:file handler of the output file
 * @len:length of file name
 * @val:file name
 *
 * Write file name value to file in TLV format
 */
static void write_xml_file_name_tlv(FILE *fp, unsigned char len, unsigned char *val)
{
	fwrite(&XML_FILE_NAME_TAG, XML_FILE_NAME_TAG_SIZE, 1, fp);
	fwrite(&len, XML_FILE_NAME_LEN_SIZE, 1, fp);
	fwrite(val, len, 1, fp);
}

/**
 * write_xml_file_name:
 * @info:contain essential infomations which can be used for handling xml file
 *
 * Write file name value to file
 */
static void write_xml_file_name(tee_config_info_t *info)
{
	unsigned char len;

	seg_offset = info->offset;
	len = strlen(info->xml_file_name) + 1;
	write_xml_file_name_tlv(info->bin_fp, len, info->xml_file_name);
	info->offset += XML_FILE_NAME_TAG_SIZE + XML_FILE_NAME_LEN_SIZE + len;
}

/**
 * write_id_attr_tlv:
 * @fp:file handler of the output file
 * @len:length of ID attribute value
 * @val:ID attribute value
 *
 * Write ID attribute value to file in TLV format
 */
static void write_id_attr_tlv(FILE *fp, unsigned char len, unsigned char *val)
{
	fwrite(&ATTR_PROPERTY_ID_TAG, ATTR_ID_TAG_SIZE, 1, fp);
	fwrite(&len, ATTR_ID_LEN_SIZE, 1, fp);
	fwrite(val, len, 1, fp);
}

/**
 * write_id_attr:
 * @info:contain essential infomations which can be used for handling xml file
 *
 * Write ID attribute value to file
 */
static int write_id_attr(tee_config_info_t *info, xmlNodePtr node)
{
	xmlChar *id;
	unsigned char len;

	id = xmlGetProp(node, "ID");
	if (id != NULL) {
		len = strlen(id) + 1;
	} else {
		printf("error: no ID attr!\n");
		return -1;
	}

	write_id_attr_tlv(info->bin_fp, len, id);
	info->offset += ATTR_ID_TAG_SIZE + ATTR_ID_LEN_SIZE + len;

	xmlFree(id);
	return 0;
}

/**
 * level0_node_handle_func:
 * @info:contain essential infomations which can be used for handling xml file
 * @node:level0 node
 *
 * Handle elements in level0 node
 */
static int level0_node_handle_func(tee_config_info_t *info, xmlNodePtr node)
{
	if (!xmlStrcmp(node->name, (const xmlChar *)"property")) {
		if (write_id_attr(info, node)) {
			printf("error: handle ID attr failed!\n");
			return -1;
		}
	} else {
		printf("error: invalid node name!\n");
		return -1;
	}

	return 0;
}

/**
 * write_attr_type_uint8_tlv:
 * @fp:file handler of the output file
 * @len:data length
 * @val:data value
 *
 * Write UINT8 data to file in TLV format
 */
static void write_attr_type_uint8_tlv(FILE *fp, unsigned char len, unsigned char val)
{
	fwrite(&ATTR_TYPE_UINT8_TAG, ATTR_TYPE_UINT8_TAG_SIZE, 1, fp);
	fwrite(&len, ATTR_TYPE_UINT8_LEN_SIZE, 1, fp);
	fwrite(&val, len, 1, fp);
}

/**
 * write_attr_type_uint16_tlv:
 * @fp:file handler of the output file
 * @len:data length
 * @val:data value
 *
 * Write UINT16 data to file in TLV format
 */
static void write_attr_type_uint16_tlv(FILE *fp, unsigned char len, unsigned short val)
{
	fwrite(&ATTR_TYPE_UINT16_TAG, ATTR_TYPE_UINT16_TAG_SIZE, 1, fp);
	fwrite(&len, ATTR_TYPE_UINT16_LEN_SIZE, 1, fp);
	fwrite(&val, len, 1, fp);
}

/**
 * write_attr_type_uint32_tlv:
 * @fp:file handler of the output file
 * @len:data length
 * @val:data value
 *
 * Write UINT32 data to file in TLV format
 */
static void write_attr_type_uint32_tlv(FILE *fp, unsigned char len, unsigned int val)
{
	fwrite(&ATTR_TYPE_UINT32_TAG, ATTR_TYPE_UINT32_TAG_SIZE, 1, fp);
	fwrite(&len, ATTR_TYPE_UINT32_LEN_SIZE, 1, fp);
	fwrite(&val, len, 1, fp);
}

/**
 * write_attr_type_uint64_tlv:
 * @fp:file handler of the output file
 * @len:data length
 * @val:data value
 *
 * Write UINT64 data to file in TLV format
 */
static void write_attr_type_uint64_tlv(FILE *fp, unsigned char len, unsigned int low, unsigned int high)
{
	fwrite(&ATTR_TYPE_UINT64_TAG, ATTR_TYPE_UINT64_TAG_SIZE, 1, fp);
	fwrite(&len, ATTR_TYPE_UINT64_LEN_SIZE, 1, fp);
	fwrite(&low, sizeof(int), 1, fp);
	fwrite(&high, sizeof(int), 1, fp);
}

/**
 * write_attr_type_bool_tlv:
 * @fp:file handler of the output file
 * @len:data length
 * @val:data value
 *
 * Write BOOL data to file in TLV format
 */
static void write_attr_type_bool_tlv(FILE *fp, unsigned char len, unsigned char val)
{
	fwrite(&ATTR_TYPE_BOOL_TAG, ATTR_TYPE_BOOL_TAG_SIZE, 1, fp);
	fwrite(&len, ATTR_TYPE_BOOL_LEN_SIZE, 1, fp);
	fwrite(&val, len, 1, fp);
}

/**
 * write_attr_type_string_tlv:
 * @fp:file handler of the output file
 * @len:data length
 * @val:data value
 *
 * Write STRING data to file in TLV format
 */
static void write_attr_type_string_tlv(FILE *fp, unsigned char len, unsigned char *val)
{
	fwrite(&ATTR_TYPE_STRING_TAG, ATTR_TYPE_STRING_TAG_SIZE, 1, fp);
	fwrite(&len, ATTR_TYPE_STRING_LEN_SIZE, 1, fp);
	fwrite(val, len, 1, fp);
}

/**
 * write_elements:
 * @info:contain essential infomations which can be used for handling xml file
 *
 * Write element values to file
 */
static int write_elements(tee_config_info_t *info, xmlNodePtr node)
{
	xmlChar *node_type = NULL;
	xmlChar *node_tag = NULL;
	xmlChar *node_content = NULL;
	char *err_char;
	unsigned char val8;
	unsigned short val16;
	unsigned int val32;
	unsigned int val64_low, val64_high;
	unsigned char *str_low, *str_high;
	unsigned int len;
	int ret = 0;

	node_type = xmlGetProp(node, "type");
	if (!xmlStrcmp(node_type, (const xmlChar *)ATTR_TYPE_UINT8)) {
		/* Get and check element value */
		node_content = xmlNodeGetContent(node);
		if (strlen(node_content) > ((ATTR_TYPE_UINT8_LEN_VALUE + 1) << 1)) {
			ret = ERR_WRONG_RANGE;
			goto err;
		}

		/* Check data format */
		if (xmlStrncmp(node_content, (const xmlChar *)ATTR_TYPE_UINT_PREFIX, 2)) {
			ret = ERR_WRONG_FORMAT;
			goto err;
		}

		/* Write element value in TLV format */
		val8 = strtoul(node_content, &err_char, 16);
		if (strlen(err_char) != 0) {
			ret = ERR_WRONG_FORMAT;
			goto err;
		}

		write_attr_type_uint8_tlv(info->bin_fp, ATTR_TYPE_UINT8_LEN_VALUE, val8);

		/* Adjust offset in file */
		info->offset += ATTR_TYPE_UINT8_TAG_SIZE + ATTR_TYPE_UINT8_LEN_SIZE + ATTR_TYPE_UINT8_LEN_VALUE;
	} else if (!xmlStrcmp(node_type, (const xmlChar *)ATTR_TYPE_UINT16)) {
		/* Get and check element value */
		node_content = xmlNodeGetContent(node);
		if (strlen(node_content) > ((ATTR_TYPE_UINT16_LEN_VALUE + 1) << 1)) {
			ret = ERR_WRONG_RANGE;
			goto err;
		}

		/* Check data format */
		if (xmlStrncmp(node_content, (const xmlChar *)ATTR_TYPE_UINT_PREFIX, 2)) {
			ret = ERR_WRONG_FORMAT;
			goto err;
		}

		/* Write element value in TLV format */
		val16 = strtoul(node_content, &err_char, 16);
		if (strlen(err_char) != 0) {
			ret = ERR_WRONG_FORMAT;
			goto err;
		}

		write_attr_type_uint16_tlv(info->bin_fp, ATTR_TYPE_UINT16_LEN_VALUE, val16);

		/* Adjust offset in file */
		info->offset += ATTR_TYPE_UINT16_TAG_SIZE + ATTR_TYPE_UINT16_LEN_SIZE + ATTR_TYPE_UINT16_LEN_VALUE;
	} else if (!xmlStrcmp(node_type, (const xmlChar *)ATTR_TYPE_UINT32)) {
		/* Get and check element value */
		node_content = xmlNodeGetContent(node);
		if (strlen(node_content) > ((ATTR_TYPE_UINT32_LEN_VALUE + 1) << 1)) {
			ret = ERR_WRONG_RANGE;
			goto err;
		}

		/* Check data format */
		if (xmlStrncmp(node_content, (const xmlChar *)ATTR_TYPE_UINT_PREFIX, 2)) {
			ret = ERR_WRONG_FORMAT;
			goto err;
		}

		/* Write element value in TLV format */
		val32 = strtoul(node_content, &err_char, 16);
		if (strlen(err_char) != 0) {
			ret = ERR_WRONG_FORMAT;
			goto err;
		}

		write_attr_type_uint32_tlv(info->bin_fp, ATTR_TYPE_UINT32_LEN_VALUE, val32);

		/* Store element value in tee config header */
		node_tag = xmlGetProp(node, "tag");
		if (!xmlStrcmp(node_tag, (const xmlChar *)ATTR_TAG_IN_TEECFG_HEADER)) {
			tee_config_header.tos_size = val32;
		} else {
			if (node_tag) {
				ret = ERR_WRONG_TAG;
				goto err;
			}
		}

		/* Adjust offset in file */
		info->offset += ATTR_TYPE_UINT32_TAG_SIZE + ATTR_TYPE_UINT32_LEN_SIZE + ATTR_TYPE_UINT32_LEN_VALUE;
	} else if (!xmlStrcmp(node_type, (const xmlChar *)ATTR_TYPE_UINT64)) {
		/* Get and check element value */
		node_content = xmlNodeGetContent(node);
		if (strlen(node_content) > ((ATTR_TYPE_UINT64_LEN_VALUE + 1) << 1)) {
			ret = ERR_WRONG_RANGE;
			goto err;
		}

		/* Check data format */
		if (xmlStrncmp(node_content, (const xmlChar *)ATTR_TYPE_UINT_PREFIX, 2)) {
			ret = ERR_WRONG_FORMAT;
			goto err;
		}

		/* Split one UINT64 to two UINT32 */
		len = strlen(node_content);
		if (len <= 10) {
			str_low = (unsigned char *)malloc(len + 1);
			memcpy(str_low, node_content, len + 1);
			val64_low = strtoul(str_low, &err_char, 16);
			if (strlen(err_char) != 0) {
				free(str_low);
				ret = ERR_WRONG_FORMAT;
				goto err;
			}
			val64_high = 0;
			free(str_low);
		} else {
			str_low = (unsigned char *)malloc(8 + 1);
			memcpy(str_low, node_content + len - 8, 9);
			val64_low = strtoul(str_low, &err_char, 16);
			if (strlen(err_char) != 0) {
				free(str_low);
				ret = ERR_WRONG_FORMAT;
				goto err;
			}
			free(str_low);

			str_high = (unsigned char *)malloc(len - 8 + 1);
			memcpy(str_high, node_content, len - 8);
			str_high[len - 8] = '\0';
			val64_high = strtoul(str_high, &err_char, 16);
			if (strlen(err_char) != 0) {
				free(str_high);
				ret = ERR_WRONG_FORMAT;
				goto err;
			}
			free(str_high);
		}

		/* Write element value in TLV format */
		write_attr_type_uint64_tlv(info->bin_fp, ATTR_TYPE_UINT64_LEN_VALUE, val64_low, val64_high);

		/* Adjust offset in file */
		info->offset += ATTR_TYPE_UINT64_TAG_SIZE + ATTR_TYPE_UINT64_LEN_SIZE + ATTR_TYPE_UINT64_LEN_VALUE;
	} else if (!xmlStrcmp(node_type, (const xmlChar *)ATTR_TYPE_BOOL)) {
		/* Get and check element value */
		node_content = xmlNodeGetContent(node);
		if (!xmlStrcmp(node_content, (const xmlChar *)ATTR_TYPE_BOOL_TRUE)) {
			val8 = 1;
		} else if (!xmlStrcmp(node_content, (const xmlChar *)ATTR_TYPE_BOOL_FALSE)) {
			val8 = 0;
		} else {
			ret = ERR_WRONG_FORMAT;
			goto err;
		}

		/* Write element value in TLV format */
		write_attr_type_bool_tlv(info->bin_fp, ATTR_TYPE_BOOL_LEN_VALUE, val8);

		/* Adjust offset in file */
		info->offset += ATTR_TYPE_BOOL_TAG_SIZE + ATTR_TYPE_BOOL_LEN_SIZE + ATTR_TYPE_BOOL_LEN_VALUE;
	} else if (!xmlStrcmp(node_type, (const xmlChar *)ATTR_TYPE_STRING)) {
		/* Get and check element value */
		node_content = xmlNodeGetContent(node);
		if (strlen(node_content) > ((1 << (ATTR_TYPE_STRING_LEN_SIZE << 3)) - 2)) {
			ret = ERR_WRONG_RANGE;
			goto err;
		}

		/* Write element value in TLV format */
		val8 = strlen(node_content) + 1;
		write_attr_type_string_tlv(info->bin_fp, val8, node_content);

		/* Adjust offset in file */
		info->offset += ATTR_TYPE_STRING_TAG_SIZE + ATTR_TYPE_STRING_LEN_SIZE + val8;
	} else {
		ret = ERR_WRONG_TYPE;
		goto err;
	}

err:
	switch (ret) {
		case ERR_WRONG_TYPE:
		printf("error: wrong attr type!\n");
		break;

		case ERR_WRONG_RANGE:
		printf("error: wrong value range!\n");
		break;

		case ERR_WRONG_FORMAT:
		printf("error: wrong data format!\n");
		break;

		case ERR_WRONG_TAG:
		printf("error: wrong attr tag!\n");
		break;
	}

	if (node_tag)
		xmlFree(node_tag);

	if (node_type)
		xmlFree(node_type);

	if (node_content)
		xmlFree(node_content);

	return ret;
}

/**
 * level1_node_handle_func:
 * @node:level1 node
 *
 * Handle elements in level1 node
 */
static int level1_node_handle_func(tee_config_info_t *info, xmlNodePtr node)
{
	if (write_elements(info, node)) {
		printf("error: handle elements failed!\n");
		return -1;
	}

	return 0;
}

/**
 * handle_each_xml_file:
 * @info:contain essential infomations which can be used for handling xml file
 *
 * Handle xml file
 */
int handle_each_xml_file(tee_config_info_t *info)
{
	xmlDocPtr doc;
	xmlNodePtr root_node, level0_node, level1_node;
	bool already_handled_node0 = false;
	bool already_handled_node1 = false;
	int ret = 0;

	/* Set libxml api function */
	xmlKeepBlanksDefault(0);

	/* Load xml file and get xml dom tree */
	doc = xmlParseFile(info->xml_file_path);
	if (NULL == doc) {
		printf("error: unable to parse file \"%s\"\n", info->xml_file_path);
		return -1;
	}

	/* Get root node */
#if TEE_CONFIG_DEBUG
	printf("------ start xml file handling:[%s] ------\n", info->xml_file_path);
#endif
	root_node = xmlDocGetRootElement(doc);
	if (NULL == root_node) {
		printf("error: no root node is defined!\n");
		ret = -1;
		goto err;
	}
#if TEE_CONFIG_DEBUG
	printf("root_node_name:%s\n", root_node->name);
#endif
	write_xml_file_name(info);

	/* Get level0 nodes */
	level0_node = root_node->xmlChildrenNode;
	while (level0_node) {
		/* Get rid of comment nodes */
		if (!xmlStrcmp(level0_node->name, (const xmlChar *)"comment") ||
			!xmlStrcmp(level0_node->name, (const xmlChar *)"text")) {
			level0_node = level0_node->next;
			if (NULL == level0_node && !already_handled_node0) {
				printf("no level0 node is defined!\n");
				ret = -1;
				goto err;
			}
			continue;
		} else {
			already_handled_node0 = true;
		}

		/* Handle values and attributes of the element in level0 node */
#if TEE_CONFIG_DEBUG
		printf("level0_node_name:%s\n", level0_node->name);
#endif
		if (level0_node_handle_func(info, level0_node)) {
			printf("error: level0 node func fails!\n");
			ret = -1;
			goto err;
		}

		/* Get level1 nodes */
		level1_node = level0_node->xmlChildrenNode;
		while (level1_node) {
			/* Get rid of comment nodes */
			if (!xmlStrcmp(level1_node->name, (const xmlChar *)"comment") ||
				!xmlStrcmp(level1_node->name, (const xmlChar *)"text")) {
				level1_node = level1_node->next;
				if (NULL == level1_node) {
					if (!already_handled_node1) {
						printf("no level1 node is defined!\n");
						ret = -1;
						goto err;
					} else {
						already_handled_node1 = false;
					}
				}
				continue;
			} else {
				already_handled_node1 = true;
			}

			/* Handle values and attributes of the element in level1 node */
#if TEE_CONFIG_DEBUG
			printf("level1_node_name:%s\n", level1_node->name);
#endif
			if (level1_node_handle_func(info, level1_node)) {
				printf("error: level1 node func fails!\n");
				ret = -1;
				goto err;
			}

			/* Process next level1 node */
			level1_node = level1_node->next;
		}

		/* Level1 nodes have been processed, adjust level0 node to point to his brother node */
		already_handled_node1 = false;
		level0_node = level0_node->next;
	}
#if TEE_CONFIG_DEBUG
	printf("------ end xml file handling:[%s] ------\n", info->xml_file_path);
#endif

	/* Set segment informations */
	info->set_seg_info(info->xml_file_name, seg_offset, (info->offset - seg_offset));

err:
	/* Free xml resource */
	xmlFreeDoc(doc);
	return ret;
}




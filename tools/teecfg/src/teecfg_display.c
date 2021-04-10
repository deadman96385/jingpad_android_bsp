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
#include <malloc.h>

#include "teecfg_display.h"


#define XML_FILE_NAME_TAG         0x9faa
#define ATTR_PROPERTY_ID_TAG      0x8faa
#define ATTR_TYPE_UINT8_TAG       0x7faa
#define ATTR_TYPE_UINT16_TAG      0x7fbb
#define ATTR_TYPE_UINT32_TAG      0x7fcc
#define ATTR_TYPE_UINT64_TAG      0x7fdd
#define ATTR_TYPE_BOOL_TAG        0x7fee
#define ATTR_TYPE_STRING_TAG      0x7fff

static struct list_node seg_node_head = LIST_INITIAL_VALUE(seg_node_head);


/**
 * ----------------------------------------------------
 * |----------- teecfg display functions -------------|
 * ----------------------------------------------------
 */
/**
 * parse_teecfg_header:
 * @image:the address storing teecfg image
 * @size:max size of teecfg image
 *
 * Parse teecfg header info
 */
static int parse_teecfg_header(unsigned char *image, unsigned int size)
{
	unsigned int len = TEE_CONFIG_HEADER_SIZE;
	unsigned int i;

	memcpy((unsigned char *)&tee_config_header, image, sizeof(tee_config_header_t));

	/* Check teecfg header magic */
	if (memcmp(TEECFG_HEADER_MAGIC, tee_config_header.name, strlen(TEECFG_HEADER_MAGIC)) != 0) {
		printf("error: check teecfg header magic failed!\n");
		return -1;
	}

	/* Check teecfg header size */
	if (tee_config_header.size != TEE_CONFIG_HEADER_SIZE) {
		printf("error: check teecfg header size failed!\n");
		return -1;
	}

	/* Check segment descriptor offset */
	if (tee_config_header.seg_desc_off != offsetof(tee_config_header_t, seg_desc)) {
		printf("error: check segment descriptor offset failed!\n");
		return -1;
	}

	/* Check segment descriptor number */
	if (tee_config_header.seg_desc_num > SEG_DESC_MAX_SIZE) {
		printf("error: segment descriptor number exceeds the max value(%#x)!\n", SEG_DESC_MAX_SIZE);
		return -1;
	}

	/* Check image size */
	for (i = 0; i < tee_config_header.seg_desc_num; i++) {
		len += tee_config_header.seg_desc[i].size;
	}
	if (len > size) {
		printf("error: file length exceeds the max value(%#x)!\n", TEECFG_MEM_MAX_SIZE);
		return -1;
	}

	/* Print teecfg header info */
	printf("<------ teecfg header ------>\n");
	printf("cfg_header_name:%s\n", tee_config_header.name);
	printf("cfg_header_version:%#x\n", tee_config_header.version);
	printf("cfg_header_size:%#x\n", tee_config_header.size);
	printf("cfg_header_tos_size:%#x\n", tee_config_header.tos_size);
	printf("cfg_header_seg_desc_off:%#x\n", tee_config_header.seg_desc_off);
	printf("cfg_header_seg_desc_num:%#x\n", tee_config_header.seg_desc_num);

	/* Print segment info */
	for (i = 0; i < tee_config_header.seg_desc_num; i++) {
		printf("cfg_seg_name:%s\n", tee_config_header.seg_desc[i].name);
		printf("cfg_seg_offset:%#x\n", tee_config_header.seg_desc[i].offset);
		printf("cfg_seg_size:%#x\n", tee_config_header.seg_desc[i].size);
	}

	return 0;
}

/**
 * free_teecfg_tlv_list:
 *
 * Free memory region used for storing teecfg info
 */
static void free_teecfg_tlv_list(void)
{
	seg_info_t *seg_info = NULL, *seg_info_tmp = NULL;
	property_info_t *property_info = NULL, *property_info_tmp = NULL;
	tlv_t *tlv = NULL, *tlv_tmp = NULL;

	list_for_every_entry_safe(&seg_node_head, seg_info, seg_info_tmp, seg_info_t, node) {
		list_for_every_entry_safe(seg_info->property_node_head, property_info, property_info_tmp, property_info_t, node) {
			list_for_every_entry_safe(property_info->tlv_node_head, tlv, tlv_tmp, tlv_t, node) {
				free(tlv);
			}
			free(property_info->tlv_node_head);
			free(property_info);
		}
		free(seg_info->property_node_head);
		free(seg_info);
	}
}

/**
 * decode_xml_file_name:
 * @name:xml file name
 * @buf:the buffer storing teecfg image
 * @pos:offset in teecfg image
 * @seg_info_cur:point to current seg_info_t var
 *
 * Decode xml file name from teecfg image and form segment info list
 */
static int decode_xml_file_name(unsigned char *name, unsigned char *buf, unsigned int pos, seg_info_t **seg_info_cur)
{
	unsigned char l = *(buf + pos);
	/* Check xml file name length */
	if (l > SEG_NAME_MAX_SIZE)
		return -1;
	pos += 1;

	/* Malloc a region for storing segment info */
	*seg_info_cur = (seg_info_t *)malloc(sizeof(seg_info_t));
	if (!(*seg_info_cur))
		return -1;
	memset(*seg_info_cur, 0x00, sizeof(seg_info_t));
	memcpy((*seg_info_cur)->name, buf + pos, l);
	pos += l;

	/* Compare the name value */
	if (memcmp(name, (*seg_info_cur)->name, l) != 0)
		goto err;

	/* Malloc a region for storing property node head */
	(*seg_info_cur)->property_node_head = (struct list_node *)malloc(sizeof(struct list_node));
	if (!(*seg_info_cur)->property_node_head)
		goto err;
	memset((*seg_info_cur)->property_node_head, 0x00, sizeof(struct list_node));

	list_initialize((*seg_info_cur)->property_node_head);

	return pos;

err:
	free(*seg_info_cur);
	return -1;
}

/**
 * decode_property_id:
 * @buf:the buffer storing teecfg image
 * @pos:offset in teecfg image
 * @property_info_cur:point to current property_info_t var
 *
 * Decode property id from teecfg image and form property info list
 */
static int decode_property_id(unsigned char *buf, unsigned int pos, property_info_t **property_info_cur)
{
	unsigned char l = *(buf + pos);
	/* Check property name length */
	if (l > PROPERTY_NAME_MAX_SIZE)
		return -1;
	pos += 1;

	/* Malloc a region for storing property info */
	*property_info_cur = (property_info_t *)malloc(sizeof(property_info_t));
	if (!(*property_info_cur))
		return -1;
	memset(*property_info_cur, 0x00, sizeof(property_info_t));
	memcpy((*property_info_cur)->name, buf + pos, l);
	pos += l;

	/* Malloc a region for storing tlv node head */
	(*property_info_cur)->tlv_node_head = (struct list_node *)malloc(sizeof(struct list_node));
	if (!(*property_info_cur)->tlv_node_head)
		goto err;
	memset((*property_info_cur)->tlv_node_head, 0x00, sizeof(struct list_node));

	list_initialize((*property_info_cur)->tlv_node_head);

	return pos;

err:
	free(*property_info_cur);
	return -1;
}

/**
 * decode_property_tlv:
 * @tag:tag value
 * @buf:the buffer storing teecfg image
 * @pos:offset in teecfg image
 * @tlv_cur:point to current tlv_t var
 *
 * Decode tlv info from teecfg image and form tlv list
 */
static int decode_property_tlv(unsigned short tag, unsigned char *buf, unsigned int pos, tlv_t **tlv_cur)
{
	unsigned char l = *(buf + pos);
	pos += 1;

	/* Malloc a region for storing tlv info */
	*tlv_cur = (tlv_t *)malloc(sizeof(tlv_t));
	if (!(*tlv_cur))
		return -1;
	memset(*tlv_cur, 0x00, sizeof(tlv_t));

	(*tlv_cur)->t = tag;
	(*tlv_cur)->l = l;

	/* Store v value */
	switch (tag) {
		case ATTR_TYPE_UINT8_TAG:
			/* Check l length */
			if (l != 1)
				goto err;
			(*tlv_cur)->v.int8_val = *(buf + pos);
			break;

		case ATTR_TYPE_UINT16_TAG:
			/* Check l length */
			if (l != 2)
				goto err;
			(*tlv_cur)->v.int16_val = *((unsigned short *)(buf + pos));
			break;

		case ATTR_TYPE_UINT32_TAG:
			/* Check l length */
			if (l != 4)
				goto err;
			(*tlv_cur)->v.int32_val = *((unsigned int *)(buf + pos));
			break;

		case ATTR_TYPE_UINT64_TAG:
			/* Check l length */
			if (l != 8)
				goto err;
			memcpy((unsigned char *)&(*tlv_cur)->v.int64_val, buf + pos, l);
			break;

		case ATTR_TYPE_BOOL_TAG:
			/* Check l length */
			if (l != 1)
				goto err;
			(*tlv_cur)->v.bool_val = *(buf + pos);
			break;

		case ATTR_TYPE_STRING_TAG:
			memcpy((*tlv_cur)->v.str_val, buf + pos, l);
			break;

		default:
			goto err;
	}
	pos += l;

	return pos;

err:
	free(*tlv_cur);
	return -1;
}

/**
 * tlv_decode_each_seg_info:
 * @name:xml file name
 * @buf:the buffer storing segment info
 * @len:segment len
 *
 * Decode each segment info in tlv format
 */
static int tlv_decode_each_seg_info(unsigned char *name, unsigned char *buf, unsigned int len)
{
	seg_info_t *seg_info_current = NULL;
	property_info_t *property_info_current = NULL;
	tlv_t *tlv_current = NULL;
	unsigned int off = 0;
	unsigned short t = 0;
	int ret = 0;

	while (len - off > 0) {
		t = *((unsigned short *)(buf + off));
		off += 2;
		switch (t) {
			/* Decode xml file name */
			case XML_FILE_NAME_TAG:
				ret = decode_xml_file_name(name, buf, off, &seg_info_current);
				if (ret < 0)
					return -1;
				else
					off = ret;
				list_add_tail(&seg_node_head, &(seg_info_current->node));
				break;

			/* Decode property id */
			case ATTR_PROPERTY_ID_TAG:
				if (!seg_info_current)
					return -1;

				ret = decode_property_id(buf, off, &property_info_current);
				if (ret < 0)
					return -1;
				else
					off = ret;
				list_add_tail(seg_info_current->property_node_head, &(property_info_current->node));
				break;

			/* Decode tlv */
			case ATTR_TYPE_UINT8_TAG:
			case ATTR_TYPE_UINT16_TAG:
			case ATTR_TYPE_UINT32_TAG:
			case ATTR_TYPE_UINT64_TAG:
			case ATTR_TYPE_BOOL_TAG:
			case ATTR_TYPE_STRING_TAG:
				if (!property_info_current)
					return -1;

				ret = decode_property_tlv(t, buf, off, &tlv_current);
				if (ret < 0)
					return -1;
				else
					off = ret;
				list_add_tail(property_info_current->tlv_node_head, &(tlv_current->node));
				break;

			default:
				return -1;
		}
	}

	return 0;
}

/**
 * parse_all_segs_info:
 * @buf:the buffer storing teecfg image
 * @tee_cfg_h:store teecfg header info
 *
 * Parse each segment info in teecfg image
 */
static int parse_all_segs_info(unsigned char *buf, tee_config_header_t *tee_cfg_h)
{
	unsigned int i;

	/* Decode each segment info in tlv format */
	for (i = 0; i < tee_cfg_h->seg_desc_num; i++) {
		if(tlv_decode_each_seg_info(tee_cfg_h->seg_desc[i].name, \
					buf + tee_cfg_h->seg_desc[i].offset, \
					tee_cfg_h->seg_desc[i].size) != 0)
			return -1;
	}

	return 0;
}

/**
 * display_teecfg_tlv_list:
 *
 * Display teecfg config info
 */
static void display_teecfg_tlv_list(void)
{
	printf("<------ teecfg tlv list ------>\n");
	seg_info_t *seg_info = NULL, *seg_info_tmp = NULL;
	property_info_t *property_info = NULL, *property_info_tmp = NULL;
	tlv_t *tlv = NULL, *tlv_tmp = NULL;

	list_for_every_entry_safe(&seg_node_head, seg_info, seg_info_tmp, seg_info_t, node) {
		printf("seg_name:%s\n", seg_info->name);

		list_for_every_entry_safe(seg_info->property_node_head, property_info, property_info_tmp, property_info_t, node) {
			printf("|---prop_id:%s\n", property_info->name);

			list_for_every_entry_safe(property_info->tlv_node_head, tlv, tlv_tmp, tlv_t, node) {
				printf("%s|---t:%#x", "    ", tlv->t);
				printf("%sl:%#x", "   ", tlv->l);

				switch (tlv->t) {
					case ATTR_TYPE_UINT8_TAG:
						printf("%sv:%#x\n", "   ", tlv->v.int8_val);
						break;

					case ATTR_TYPE_UINT16_TAG:
						printf("%sv:%#x\n", "   ", tlv->v.int16_val);
						break;

					case ATTR_TYPE_UINT32_TAG:
						printf("%sv:%#x\n", "   ", tlv->v.int32_val);
						break;

					case ATTR_TYPE_UINT64_TAG:
						printf("%sv:%#lx\n", "   ", tlv->v.int64_val);
						break;

					case ATTR_TYPE_BOOL_TAG:
						printf("%sv:%#x\n", "   ", tlv->v.bool_val);
						break;

					case ATTR_TYPE_STRING_TAG:
						printf("%sv:%s\n", "   ", tlv->v.str_val);
						break;
				}
			}
		}
	}
	printf("<------ teecfg tlv list ------>\n");
}

/**
 * parse_teecfg_image:
 * @image:the address storing teecfg image
 *
 * Parse teecfg image
 */
static int parse_teecfg_image(unsigned char *image)
{
	int ret = 0;

	/* Parse and get teecfg header info */
	if(parse_teecfg_header(image, TEECFG_MEM_MAX_SIZE) != 0) {
		printf("error: parse tee config header failed!\n");
		return -1;
	}

	/* Parse all segments info used for descripting xml file */
	if(parse_all_segs_info(image, &tee_config_header) != 0) {
		printf("error: parse segments info failed!\n");
		ret = -1;
		goto err;
	}

	/* Display teecfg info */
	display_teecfg_tlv_list();

err:
	/* Free malloc region */
	free_teecfg_tlv_list();

	return ret;
}

/**
 * display_teecfg_image:
 * @infile:input file path
 *
 * Parse teecfg image and show config info
 */
int display_teecfg_image(const char *infile)
{
	int ret = 0;

	/* Open teecfg image */
	FILE *fp = fopen(infile, "rb");
	if (NULL == fp) {
		printf("error: open %s file failed!\n", infile);
		return -1;
	}

	/* Get image size */
	if(fseek(fp, 0, SEEK_END)) {
		ret = -1;
		goto err0;
	}
	int size = ftell(fp);
	if (size == -1) {
		ret = -1;
		goto err0;
	}
	rewind(fp);

	/* Malloc a region for storing teecfg image */
	unsigned char *image = (unsigned char *)malloc(sizeof(unsigned char) * size);
	if (!image) {
		printf("error: malloc memory failed!\n");
		ret = -1;
		goto err0;
	}

	/* Read teecfg image */
	size_t num = fread(image, sizeof(unsigned char), size, fp);
	if (num != size) {
		printf("error: read image failed!\n");
		ret = -1;
		goto err1;
	}

	/* Parse teecfg image */
	if (parse_teecfg_image(image) != 0) {
		ret = -1;
		goto err1;
	}

err1:
	free(image);
err0:
	/* Close teecfg image */
	fclose(fp);
	return ret;
}




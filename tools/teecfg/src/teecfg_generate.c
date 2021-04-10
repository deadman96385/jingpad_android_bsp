/**
 * ----------------------------------------------------------------------------
 * Copyright (C) 2019 UNISOC Technologies Co.,Ltd.
 * All rights reserved.
 * ----------------------------------------------------------------------------
 * This document contains proprietary information belonging to UNISOC.
 * Passing on and copying of this document, use and communication of its
 * contents is not permitted without prior written authorisation.
 * ----------------------------------------------------------------------------
 */

#include <string.h>
#include <dirent.h>

#include "../inc/teecfg_generate.h"
#include "../inc/common.h"


#define offset_of(TYPE, MEMBER)      ((size_t)&((TYPE *)0)->MEMBER)
#define set_ver(h, l)      ((0xffff0000 & h) | (0x0000ffff & l))

static unsigned int seg_index = 0;


/**
 * ----------------------------------------------
 * |-------- teecfg generate functions ---------|
 * ----------------------------------------------
 */
/**
 * set_seg_info_func:
 * @name:segment name
 * @offset:start position to write the segment value
 * @size:segment size
 *
 * Set each segment informations, which will be written to file
 */
static void set_seg_info_func(unsigned char *name, unsigned int offset, unsigned int size)
{
	strcpy(tee_config_header.seg_desc[seg_index].name, name);
	tee_config_header.seg_desc[seg_index].offset = offset;
	tee_config_header.seg_desc[seg_index].size = size;
	seg_index++;
}

/**
 * set_tee_config_info:
 * @info:contain essential infomations which can be used for handling xml file
 * @outfile:name of the output file
 *
 * Initialize the struct var
 */
static int set_tee_config_info(tee_config_info_t *info, unsigned char *outfile)
{
	info->bin_fp = fopen(outfile, "wb");
	if (NULL == info->bin_fp)
		return -1;

	info->offset = TEE_CONFIG_HEADER_SIZE;
	info->set_seg_info = set_seg_info_func;
	if(fseek(info->bin_fp, info->offset, SEEK_SET)) {
		fclose(info->bin_fp);
		return -1;
	}

	return 0;
}

/**
 * handle_xml_files:
 * @info:contain essential infomations which can be used for handling xml file
 * @xml_file_path:the path includes feature specified xml files
 *
 * Handle each xml file which is used for feature configuration
 */
static int handle_xml_files(tee_config_info_t *info, unsigned char *xml_file_path)
{
	DIR *dir;
	struct dirent *dentry;
	char *file_path = NULL;
	char *tmp = NULL;
	int ret = 0;

	/* Open dir */
	dir = opendir(xml_file_path);
	if (!dir) {
		printf("error: open dir failed!\n");
		return -1;
	}

	/* Traverse each xml file */
	while((dentry = readdir(dir)) != NULL) {
		if (dentry->d_type == DT_REG && !strncmp(dentry->d_name + strlen(dentry->d_name) - 4, ".xml", 4)) {
			file_path = (char *)malloc(strlen(xml_file_path) + strlen(dentry->d_name) + 2);
			if (!file_path) {
				printf("error: malloc memory failed!\n");
				ret = -1;
				goto err;
			}
			sprintf(file_path, "%s/%s", xml_file_path, dentry->d_name);

			/* Set file attributes */
			info->xml_file_name = strtok_r(dentry->d_name, ".", &tmp);
			info->xml_file_path = file_path;

			/* Handle xml file */
			if (handle_each_xml_file(info)) {
				free(file_path);
				ret = -1;
				goto err;
			}

			free(file_path);
		}
	}

err:
	closedir(dir);
	return ret;
}

/**
 * write_tee_config_header:
 * @info:contain essential infomations which can be used for handling xml file
 *
 * Write header informations to file
 */
static int write_tee_config_header(tee_config_info_t *info)
{
	int ret = 0;

	strcpy((char *)(tee_config_header.name), TEECFG_HEADER_MAGIC);
	tee_config_header.version = set_ver(0, 1); //v0.1
	tee_config_header.size = TEE_CONFIG_HEADER_SIZE;
	tee_config_header.seg_desc_off = offset_of(tee_config_header_t, seg_desc);
	tee_config_header.seg_desc_num = seg_index;
#if TEE_CONFIG_DEBUG
	printf("tee_config_header_len:%d\n", (int)TEE_CONFIG_HEADER_SIZE);
#endif
	if (fseek(info->bin_fp, 0, SEEK_SET)) {
		ret = -1;
		goto err;
	}
	fwrite((unsigned char *)&tee_config_header, TEE_CONFIG_HEADER_SIZE, 1, info->bin_fp);

err:
	fclose(info->bin_fp);
	return ret;
}

/**
 * generate_teecfg_image:
 * @xml_file_path:the path includes feature specified xml files
 * @outfile:the output file name and path
 *
 * Parse xml files and write data to file
 */
int generate_teecfg_image(unsigned char *xml_file_path, unsigned char *outfile)
{
	tee_config_info_t tee_config_info;
	int ret = 0;

	/* Init libxml */
	xmlInitParser();

	/* Set initial infos */
	if (set_tee_config_info(&tee_config_info, outfile)) {
		ret = -1;
		goto err;
	}

	/* Invoke xml file handler */
	if (handle_xml_files(&tee_config_info, xml_file_path)) {
		ret = -1;
		goto err;
	}

	/* Write teeconfig header to file */
	if (write_tee_config_header(&tee_config_info)) {
		ret = -1;
		goto err;
	}

err:
	/* Shutdown libxml */
	xmlCleanupParser();
	return ret;
}




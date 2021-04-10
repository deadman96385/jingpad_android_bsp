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

#include <assert.h>
#include <unistd.h>

#include "../inc/teecfg_generate.h"
#include "../inc/teecfg_display.h"


/**
 * ----------------------------------------------
 * |---------- teecfg tool functions -----------|
 * ----------------------------------------------
 */
/**
 * usage:
 * @name:the program name
 *
 * Prints usage information
 */
static void usage(const char *name)
{
	assert(name);
	printf("usage: %s -g/-d -i <input_file> [-o <output_file>]\n", name);
}

/**
 * main:
 * @argc:param number
 * @argv:params
 *
 * Main routine
 */
int main(int argc, char **argv)
{
	int ret;
	char *optstring="gdi:o:";
	unsigned char *infile = NULL;
	unsigned char *outfile = NULL;
	bool is_generate_img = false;
	bool is_display_img = false;

	printf("teecfg configurator version %s!\n", VERSION);

	/* Process command line params */
	while ((ret = getopt(argc, argv, optstring)) != -1) {
		switch (ret) {
			case 'g':
				is_generate_img = true;
				break;

			case 'd':
				is_display_img = true;
				break;

			case 'i':
				infile = optarg;
				break;

			case 'o':
				outfile = optarg;
				break;

			default:
				goto err;
		}
	}

	/* Check command line params */
	if (is_generate_img == true && is_display_img == true) {
		goto err;
	} else if (is_generate_img == true) {
		if (argc != 6 || NULL == infile || NULL == outfile)
			goto err;
	} else if (is_display_img == true) {
		if (argc != 4 || NULL == infile)
			goto err;
	} else {
		goto err;
	}

	/* Process xml files and generate teecfg image */
	if (is_generate_img == true) {
		if (generate_teecfg_image(infile, outfile))
			return -1;
	}

	/* Show config info on terminal */
	if (is_display_img == true) {
		if (display_teecfg_image(infile))
			return -1;
	}

	printf("process done!\n");

	return 0;

err:
	printf("error: wrong cmdline option/arguments!\n");
	usage(argv[0]);
	return -1;
}




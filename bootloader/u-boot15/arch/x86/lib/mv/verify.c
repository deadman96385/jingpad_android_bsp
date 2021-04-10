/*
 * Copyright (C) 2015, Intel Corporation
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * Based on code from coreboot
 */

#include <common.h>
#include "mv_gal.h"
#include "mv_hypercalls.h"
#include "mv_svc_hypercalls.h"
#include "ivmc/mv_svc_ivmc.h"

static int init_flag;

static int do_verify(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	void *image_addr = NULL;
	char *s;
	ulong image_size = 0;
	struct mv_shared_data *shared_data;
	unsigned int *ptr;
	unsigned int result = 0;

	if (!init_flag) {
		printf("init flag=%d\n", init_flag);
		mv_init();
		init_flag = 1;
	}

	if (argc >= 2) {
		/* argv[1] holds the address of the image */
		s = argv[1];
	} else {
		s = getenv("fileaddr");
	}

	if (s)
		image_addr = (void *)simple_strtoul(s, NULL, 16);

	if (argc >= 3) {
		/* argv[2] holds the size of the bzImage */
		image_size = simple_strtoul(argv[2], NULL, 16);
	}

	printf("image addr=%p, size=%ld\n", image_addr, image_size);

	puts("## Start verify image ...\n");

    /**
     * uint32[0] : vm_id
     * uint32[1] : vcpu_id
     * uint32[2] : result
     * ...       : remain data
	 */
	shared_data = mv_gal_get_shared_data();
	ptr = (unsigned int *)shared_data->pal_shared_mem_data;
	printf("%s:%d---vm=%d,cpu=%d,result: %d\n",
	       __func__,
	       __LINE__,
	       ptr[0], ptr[1], ptr[2]);

	ptr[2] = result;
	ptr[3] = (unsigned int)image_addr;
	ptr[4] = image_size;

    /* secvm id: 3 */
	if (mv_svc_ivmc_request(3) != 0) {
		puts("## Waiting for response ...");
		while (1) {
			/* check the return value of ptr[2] */
			if (ptr[2] != result) {
				printf("%s:%d---vm=%u,cpu=%u,result: %u\n",
				       __func__,
				       __LINE__,
				       ptr[0], ptr[1], ptr[2]);
				break;
			}
		}
	} else {
		puts("## Verify request failed");
	}

	/* we assume that the kernel is in place */
	return 0;
}

U_BOOT_CMD(
	verify, 3, 0,	do_verify,
	"Verify Image",
	"[addr] [size] [initrd addr] [initrd size]\n"
	"      addr -        The optional starting address of the image.\n"
	"                    If not set it defaults to the environment\n"
	"                    variable \"fileaddr\".\n"
	"      size -        The optional size of the bzimage. Defaults to\n"
	"                    zero.\n"
);

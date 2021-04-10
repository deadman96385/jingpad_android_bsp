/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include <common.h>
#include <fdtdec.h>
#include <errno.h>


DECLARE_GLOBAL_DATA_PTR;

int get_buffer_base_size_from_dt(const char *name, unsigned long *basep, unsigned long *sizep)
{
	int phandle = 0;
	const void *fdt_blob = gd->fdt_blob;
	int nodeoffset = fdt_path_offset(fdt_blob, "/ion");

	//debugf("ion node offset = %d\n", nodeoffset);
	if (nodeoffset == -FDT_ERR_NOTFOUND)
		return -1;

	nodeoffset = fdt_subnode_offset(fdt_blob, nodeoffset, name);
	//debugf("%s node offset = %d\n", name, nodeoffset);
	if (nodeoffset == -FDT_ERR_NOTFOUND)
		return -1;

	phandle = fdtdec_lookup_phandle(fdt_blob, nodeoffset, "memory-region");
	//debugf("memory-region phandle = %d\n", phandle);
	if (phandle == -FDT_ERR_NOTFOUND)
		return -1;

	if (fdtdec_decode_region(fdt_blob, phandle, "reg", basep, sizep)) {
		errorf("Failed to decode reg property \n");
		return -EINVAL;
	}

	return 0;
}

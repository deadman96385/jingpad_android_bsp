/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
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

#include <malloc.h>
#include <fdtdec.h>
#include "sprd_dispc.h"
#ifdef CONFIG_ROUND_CORNER_SUPPORT
#include "sprd_round_corner.h"
#endif

DECLARE_GLOBAL_DATA_PTR;

void *lcd_get_base_addr(void *lcd_base)
{
	return (void *)gd->fb_base;
}

static void logo_flip(void)
{
	struct sprd_dispc *dispc = &dispc_device;
	struct sprd_restruct_config *config;
	struct panel_info *panel = panel_info_attach();
	uint8_t logo_bpp = panel_info.vl_bpix > 16 ? 4 : 2;

	config = malloc(sizeof(struct sprd_restruct_config) +
			sizeof(struct sprd_adf_hwlayer));
	if (config == NULL)
		return;

	config->number_hwlayer = 1;
	config->hwlayers[0].hwlayer_id = 0;
	config->hwlayers[0].iova_plane[0] = gd->fb_base;
	config->hwlayers[0].n_planes = 1;
	config->hwlayers[0].alpha = 0xFF;
	config->hwlayers[0].pitch[0] = panel->width * logo_bpp;
	config->hwlayers[0].dst_w = panel->width;
	config->hwlayers[0].dst_h = panel->height;
	config->hwlayers[0].dst_x = 0;
	config->hwlayers[0].dst_y = 0;
	config->hwlayers[0].start_x = 0;
	config->hwlayers[0].start_y = 0;
	config->hwlayers[0].start_w = 0;
	config->hwlayers[0].start_h = 0;
	config->hwlayers[0].blending = HWC_BLENDING_NONE;
	config->hwlayers[0].compression = 0;
	config->hwlayers[0].format = logo_bpp == 2 ?
		DRM_FORMAT_RGB565 : DRM_FORMAT_ARGB8888;

	sprd_dispc_flip(dispc, config);

	free(config);
}

int get_fb_base_from_dt(void)
{
	int phandle;
	const char *label;
	unsigned long base, size, offset;
	const void *fdt_blob = gd->fdt_blob;
	struct panel_info *panel = panel_info_attach();
	int nodeoffset;

	nodeoffset = fdt_path_offset(fdt_blob, "/ion");
	if (nodeoffset == -FDT_ERR_NOTFOUND) {
		pr_err("Failed to find /ion node\n");
		return -1;
	}

	nodeoffset = fdt_subnode_offset(fdt_blob, nodeoffset, "heap@3");
	if (nodeoffset == -FDT_ERR_NOTFOUND) {
		pr_err("Failed to find heap@3 sub node\n");
		return -1;
	}

	label = fdt_getprop(fdt_blob, nodeoffset, "label", NULL);
	if (label == NULL) {
		pr_err("Failed to decode label property\n");
		return -1;
	}

	phandle = fdtdec_lookup_phandle(fdt_blob, nodeoffset, "memory-region");
	if (phandle == -FDT_ERR_NOTFOUND) {
		pr_err("Failed to decode memory-region property\n");
		return -1;
	}

	if (fdtdec_decode_region(fdt_blob, phandle, "reg", &base, &size)) {
		pr_err("Failed to decode reg property\n");
		return -EINVAL;
	}

	/*
	 * For carveout_logo, it is wb_reserved memory.
	 * Which is not used by kernel ion module. So it
	 * will not be cleared by ion driver.
	 */
	if (!strcmp(label, "carveout_logo")) {
		gd->fb_base = base;
		return 0;
	}

	/*
	 * For carveout_fb, it is fb_reserved memory.
	 * We use the third reserved buffer for uboot logo,
	 * and the first reserved buffer is for write back.
	 */
	offset = panel->width * panel->height * 4 * 2;
	gd->fb_base = ALIGN(base + offset, 32);

	return 0;
}

int get_bmp_base_from_dt(void **bmp_base)
{
	int phandle;
	const char *label;
	unsigned long base, size;
	const void *fdt_blob = gd->fdt_blob;
	int nodeoffset;

	nodeoffset = fdt_path_offset(fdt_blob, "/ion");
	if (nodeoffset == -FDT_ERR_NOTFOUND) {
		pr_err("Failed to find /ion node\n");
		return -1;
	}

	nodeoffset = fdt_subnode_offset(fdt_blob, nodeoffset, "heap@9");
	if (nodeoffset == -FDT_ERR_NOTFOUND) {
		pr_err("Failed to find heap@9 sub node\n");
		return -1;
	}

	label = fdt_getprop(fdt_blob, nodeoffset, "label", NULL);
	if (label == NULL) {
		pr_err("Failed to decode label property\n");
		return -1;
	}

	phandle = fdtdec_lookup_phandle(fdt_blob, nodeoffset, "memory-region");
	if (phandle == -FDT_ERR_NOTFOUND) {
		pr_err("Failed to decode memory-region property\n");
		return -1;
	}

	if (fdtdec_decode_region(fdt_blob, phandle, "reg", &base, &size)) {
		pr_err("Failed to decode reg property\n");
		return -EINVAL;
	}

	if (strcmp(label, "carveout_bmp")) {
		pr_err("Error label %s, we need carveout_bmp\n", label);
		return -ENOMEM;
	}

	*bmp_base = base;

	return 0;
}

static int sprdfb_probe(void)
{
	sprd_panel_probe();
	get_fb_base_from_dt();
	sprd_dispc_probe();

	return 0;
}

void lcd_disable(void)
{
	pr_info("lcd disable\n");
}

void lcd_enable(void)
{
#ifdef CONFIG_ROUND_CORNER_SUPPORT
	struct panel_info *panel = panel_info_attach();
	dispc_logo_show_corner(panel->height, panel->width, gd->fb_base);
	lcd_set_flush_dcache(TRUE);
	lcd_sync();
#endif
	pr_info("start flip\n");
	logo_flip();
}

void lcd_ctrl_init(void *lcdbase)
{
	int size;
	void *bmp;
	char *s;
	ulong addr;
	u32 bmp_header_size = 8192;

	sprdfb_probe();
	size = lcd_get_size(&lcd_line_length);
	size += bmp_header_size;
	if (get_bmp_base_from_dt(&bmp)) {
		pr_err("can not found bmp_reserved node in dts, use malloc instead\n");
		bmp = malloc(size);
	}

	if (!bmp) {
		pr_err("failed to alloc bmp space\n");
		return;
	}
	setenv_hex("splashimage", (ulong)bmp);
	s = getenv("splashimage");
	if(s == NULL){
		pr_err("splashimage addr is NULL\n");
		setenv("splashimage",NULL);
		free(bmp);
		return;
	}
	addr = simple_strtoul(s, NULL, 16);
	pr_info("splashimage addr is 0x%p, fb size is 0x%x\n",
		(void *)addr, size);
	lcd_set_flush_dcache(TRUE);
}


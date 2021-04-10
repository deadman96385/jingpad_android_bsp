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

#include "sprd_panel.h"
#include "lcd/panel_cfg.h"
#include "sprd_dsi.h"
#include "sprd_dphy.h"

static uint32_t lcd_id_to_kernel;
static struct panel_driver *panel_drv;

#ifdef CONFIG_BACKLIGHT_DSI
void set_backlight(int brightness)
{
	if (panel_drv && panel_drv->ops->set_brightness) {
		panel_drv->ops->set_brightness(brightness);
	}
	pr_info("lcd cabc backlight brightness==%d\n",brightness);
	return;
}
#endif

struct panel_info *panel_info_attach(void)
{
	return panel_drv->info;
}

uint32_t lcd_get_pixel_clock(void)
{
	if (panel_drv && panel_drv->info)
		return panel_drv->info->pixel_clk;
	else
		return 0;
}

uint32_t lcd_get_bpix(void)
{
	return panel_info.vl_bpix;
}

const char *lcd_get_name(void)
{
	if (panel_drv && panel_drv->info)
		return panel_drv->info->lcd_name;
	else
		return NULL;
}

uint32_t load_lcd_id_to_kernel(void)
{
	return lcd_id_to_kernel;
}

/* WORKAROUND: to keep the same order with sprdfb_panel.c */
uint32_t load_lcd_width_to_kernel(void)
{
	if (panel_drv && panel_drv->info)
		return panel_drv->info->height;
	else
		return 0;
}

/* WORKAROUND: to keep the same order with sprdfb_panel.c */
uint32_t load_lcd_hight_to_kernel(void)
{
	if (panel_drv && panel_drv->info)
		return panel_drv->info->width;
	else
		return 0;
}

static int panel_if_init(void)
{
	int type = panel_drv->info->type;

	switch (type) {
	case SPRD_PANEL_TYPE_MIPI:
		sprd_dsi_probe();
		sprd_dphy_probe();
		return 0;

	case SPRD_PANEL_TYPE_RGB:
		return 0;

	default:
		pr_err("doesn't support current interface type %d\n", type);
		return -1;
	}
}

static int panel_if_uinit(void)
{
	int type = panel_drv->info->type;

	switch (type) {
	case SPRD_PANEL_TYPE_MIPI:
		sprd_dphy_suspend(&dphy_device);
		sprd_dsi_suspend(&dsi_device);
		return 0;

	case SPRD_PANEL_TYPE_RGB:
		return 0;

	default:
		pr_err("doesn't support current interface type %d\n", type);
		return -1;
	}
}

int sprd_panel_probe(void)
{
	struct panel_info *info;
	struct panel_ops *ops;
	int ret;
	int i;

	for (i = 0; i < ARRAY_SIZE(supported_panel); i++) {
		panel_drv = supported_panel[i].drv;
		info = panel_drv->info;
		ops = panel_drv->ops;

		panel_if_init();

		if (ops && ops->power)
			ops->power(true);
		if (ops && ops->read_id) {
			ret = ops->read_id();
			if (!ret) {
				pr_info("attach panel 0x%x success\n",
					supported_panel[i].lcd_id);
				break;
			}
		}
		if (ops && ops->power)
			ops->power(false);

		panel_if_uinit();

		pr_err("attach panel 0x%x failed, try next...\n",
			supported_panel[i].lcd_id);
	}

	if (ops && ops->init)
		ops->init();

	panel_info.vl_row = info->height;
	panel_info.vl_col = info->width;
	lcd_id_to_kernel = supported_panel[i].lcd_id;

	return 0;
}

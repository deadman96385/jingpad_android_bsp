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
#include "sprd_dsi.h"
#include "dsi/mipi_dsi_api.h"
#include "sprd_dphy.h"

static uint8_t init_data[] = {
	0x23, 0x00, 0x00, 0x02, 0xFF, 0x10,
	0x23, 0x00, 0x00, 0x02, 0xBB, 0x13,
	0x23, 0x00, 0x00, 0x02, 0xE5, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xC0, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xFB, 0x01,
	0x13, 0x78, 0x00, 0x01, 0x11,
	0x13, 0x64, 0x00, 0x01, 0x29,
	CMD_END
};

static int mipi_dsi_send_cmds(struct sprd_dsi *dsi, void *data)
{
	uint16_t len;
	struct dsi_cmd_desc *cmds = data;

	if ((cmds == NULL) || (dsi == NULL))
		return -1;

	for (; cmds->data_type != CMD_END;) {
		len = (cmds->wc_h << 8) | cmds->wc_l;
		mipi_dsi_gen_write(dsi, cmds->payload, len);
		if (cmds->wait)
			msleep(cmds->wait);
		cmds = (struct dsi_cmd_desc *)(cmds->payload + len);
	}
	return 0;
}

static int nt35597_init(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	struct sprd_dphy *dphy = &dphy_device;

	mipi_dsi_lp_cmd_enable(dsi, true);
	mipi_dsi_send_cmds(dsi, init_data);
	mipi_dsi_set_work_mode(dsi, SPRD_MIPI_MODE_VIDEO);
	mipi_dsi_state_reset(dsi);
	mipi_dphy_hs_clk_en(dphy, true);

	return 0;
}

static int nt35597_readid(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	uint8_t read_buf[4] = {0};

	mipi_dsi_lp_cmd_enable(dsi, true);
	mipi_dsi_set_max_return_size(dsi, 1);
	mipi_dsi_dcs_read(dsi, 0xF4, read_buf, 1);

	if (read_buf[0] == 0x97) {
		pr_info("nt35597 read id success!\n");
		return 0;
	}

	pr_err("nt35597 read id failed!\n");
	return -1;
}

static struct panel_ops nt35597_ops = {
	.init = nt35597_init,
	.read_id = nt35597_readid,
};

static struct panel_info nt35597_info = {
	/* common parameters */
	.lcd_name = "lcd_nt35597_fpga_mipi_2k",
	.type = SPRD_PANEL_TYPE_MIPI,
	.bpp = 24,
//	.fps = 3,
	.width = 720,
	.height = 1280,

	/* DPI specific parameters */
	.pixel_clk = 6500000,
	.rgb_timing = {
		64, 64, 2,
		15, 5, 2
	},

	/* MIPI DSI specific parameters */
	.phy_freq = 300000,
	.lane_num = 4,
	.work_mode = SPRD_MIPI_MODE_VIDEO,
	.burst_mode = PANEL_VIDEO_BURST_MODE,
	.nc_clk_en = false,
};

struct panel_driver nt35597_fpga_driver = {
	.info = &nt35597_info,
	.ops = &nt35597_ops,
};

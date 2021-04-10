/*
 *Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 *This software is licensed under the terms of the GNU General Public
 *License version 2, as published by the Free Software Foundation, and
 *may be copied, distributed, and modified under those terms.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 */

#include "sprd_dsi.h"
#include "dsi/mipi_dsi_api.h"

#define MAX_TIME_HS2LP       120 /* unit: ns */
#define MAX_TIME_LP2HS       500 /* unit: ns */

struct sprd_dsi dsi_device;

__weak struct dsi_core_ops *dsi_core_ops_attach(void)
{
	return NULL;
}

__weak struct dsi_glb_ops *dsi_glb_ops_attach(void)
{
	return NULL;
}

static uint32_t bpp_to_coding(uint32_t bits, bool compression)
{
	uint32_t code = 0;

	switch (bits) {
	case 16:
		code = COLOR_CODE_16BIT_CONFIG1;
		break;
	case 18:
		code = COLOR_CODE_18BIT_CONFIG1;
		break;
	case 24:
		if (compression)
			code = COLOR_CODE_COMPRESSTION;
		else
			code = COLOR_CODE_24BIT;
		break;
	default:
		pr_err("invalid bus width\n");
		break;
	}

	return code;
}

static int32_t dsi_dpi_video(struct sprd_dsi *dsi)
{
	struct dpi_video_param param = {};
	uint32_t hs2lp, lp2hs;
	struct panel_info *panel = dsi->panel;
	struct rgb_timing *timing = &panel->rgb_timing;

	param.burst_mode = panel->burst_mode;
	param.lanes = panel->lane_num;
	param.byte_clk = panel->phy_freq / 8;
	param.pixel_clk = panel->pixel_clk / 1000;

	hs2lp = MAX_TIME_HS2LP * panel->phy_freq / 8000000;
	hs2lp += (MAX_TIME_HS2LP * panel->phy_freq % 8000000) < 4000000 ? 0 : 1;
	lp2hs = MAX_TIME_LP2HS * panel->phy_freq / 8000000;
	lp2hs += (MAX_TIME_LP2HS * panel->phy_freq % 8000000) < 4000000 ? 0 : 1;
	param.data_hs2lp = hs2lp;
	param.data_lp2hs = lp2hs;
	param.clk_hs2lp = 4;
	param.clk_lp2hs = 15;
	param.coding = bpp_to_coding(panel->bpp, panel->dsc_en);

	param.hact = panel->width >> panel->bv3_en;
	param.hsync = timing->hsync;
	param.hbp = timing->hbp;
	param.hline = panel->width
		+ timing->hsync + timing->hbp + timing->hfp;

	param.vact = panel->height;
	param.vsync = timing->vsync;
	param.vbp = timing->vbp;
	param.vfp = timing->vfp;

	param.color_mode_pol = 0;
	param.shut_down_pol = 0;
	param.frame_ack_en = 0;
	param.channel = 0;
	param.is_18_loosely = 1;

	mipi_dsi_dpi_video(dsi, &param);

	return 0;
}

static int32_t dsi_edpi_video(struct sprd_dsi *dsi)
{
	struct edpi_video_param param = {};
	struct panel_info *panel = dsi->panel;

	param.coding = bpp_to_coding(panel->bpp, panel->dsc_en);
	param.hact = panel->width;

	mipi_dsi_edpi_video(dsi, &param);

	return 0;
}

int sprd_dsi_suspend(struct sprd_dsi *dsi)
{
	mipi_dsi_uninit(dsi);

	if (dsi->glb && dsi->glb->disable)
		dsi->glb->disable(&dsi->ctx);
	if (dsi->glb && dsi->glb->power)
		dsi->glb->power(&dsi->ctx, false);

	pr_info("dsi uninit OK\n");
	return 0;
}

static int sprd_dsi_resume(struct sprd_dsi *dsi)
{
	struct panel_info *panel = dsi->panel;

	if (dsi->glb && dsi->glb->power)
		dsi->glb->power(&dsi->ctx, true);
	if (dsi->glb && dsi->glb->enable)
		dsi->glb->enable(&dsi->ctx);
	if (dsi->glb && dsi->glb->reset)
		dsi->glb->reset(&dsi->ctx);

	mipi_dsi_init(dsi);

	if (panel->work_mode == SPRD_MIPI_MODE_VIDEO)
		dsi_dpi_video(dsi);
	else
		dsi_edpi_video(dsi);

	pr_info("dsi init OK\n");
	return 0;
}

static int dsi_context_init(struct sprd_dsi *dsi)
{
	struct panel_info *panel = dsi->panel;
	struct dsi_context *ctx = &dsi->ctx;

	if (dsi->glb && dsi->glb->parse_dt)
		dsi->glb->parse_dt(&dsi->ctx);

	ctx->id = 0;
	ctx->max_rd_time = 6000;
	ctx->int0_mask = 0xffffffff;
	ctx->int1_mask = 0xffffffff;

	ctx->freq = panel->phy_freq;
	ctx->lanes = panel->lane_num;
	ctx->nc_clk_en = panel->nc_clk_en;

	return 0;
}

int sprd_dsi_probe(void)
{
	struct sprd_dsi *dsi;

	dsi = &dsi_device;
	dsi->panel = panel_info_attach();
	dsi->core = dsi_core_ops_attach();
	dsi->glb = dsi_glb_ops_attach();

	dsi_context_init(dsi);
	sprd_dsi_resume(dsi);

	return 0;
}

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

#include "sprd_dispc.h"

struct sprd_dispc dispc_device;

__weak struct dispc_core_ops *dispc_core_ops_attach(void)
{
	return NULL;
}

__weak struct dispc_clk_ops *dispc_clk_ops_attach(void)
{
	return NULL;
}

__weak struct dispc_glb_ops *dispc_glb_ops_attach(void)
{
	return NULL;
}

void sprd_dispc_run(struct sprd_dispc *dispc)
{
	struct dispc_context *ctx = &dispc->ctx;

	if (!ctx->is_inited) {
		pr_err("dispc is not initialized!\n");
		return;
	}

	if (dispc->core)
		dispc->core->run(ctx);
}

void sprd_dispc_stop(struct sprd_dispc *dispc)
{
	struct dispc_context *ctx = &dispc->ctx;

	if (!ctx->is_inited) {
		pr_err("dispc is not initialized!\n");
		return;
	}

	if (dispc->core)
		dispc->core->stop(ctx);
}

int32_t sprd_dispc_flip(struct sprd_dispc *dispc,
			struct sprd_restruct_config *config)
{
	struct dispc_context *ctx = &dispc->ctx;

	if (!ctx->is_inited) {
		pr_err("dispc is not initialized!\n");
		return -1;
	}

	if (!dispc->core)
		return -1;

	dispc->core->flip(ctx, config);

	if (!ctx->is_stopped || (dispc->ctx.if_type == SPRD_DISPC_IF_EDPI))
		dispc->core->run(ctx);

	return 0;
}

static int32_t sprd_dispc_suspend(struct sprd_dispc *dispc)
{
	struct dispc_context *ctx = &dispc->ctx;

	if (!ctx->is_inited) {
		pr_err("dispc is not initialized\n");
		return -1;
	}

	if (dispc->core)
		dispc->core->uninit(ctx);

	if (dispc->glb) {
		dispc->glb->disable(ctx);
		dispc->glb->power(ctx, false);
	}

	ctx->is_inited = false;

	pr_info("dispc suspend OK\n");

	return 0;
}

static int32_t sprd_dispc_resume(struct sprd_dispc *dispc)
{
	struct dispc_context *ctx = &dispc->ctx;
	struct panel_info *panel = ctx->panel;

	if (ctx->is_inited) {
		pr_info("dispc has already initialized\n");
		return -1;
	}

	if (dispc->glb) {
		dispc->glb->power(ctx, true);
		dispc->glb->enable(ctx);
		dispc->glb->reset(ctx);
	}

	if (dispc->clk) {
		dispc->clk->init(ctx);
		dispc->clk->update(ctx, DISPC_CLK_ID_DPI, panel->pixel_clk);
	}

	if (dispc->core) {
		dispc->core->init(ctx);
		dispc->core->ifconfig(ctx);
		dispc->core->run(ctx);
	}

	ctx->is_inited = true;

	//sprd_iommu_restore(&dispc->dev);

	pr_info("dispc init OK\n");
	return 0;
}

static int dispc_context_init(struct sprd_dispc *dispc)
{
	struct dispc_context *ctx = &dispc->ctx;
	struct panel_info *panel = panel_info_attach();

	if (dispc->clk && dispc->clk->parse_dt)
		dispc->clk->parse_dt(&dispc->ctx);
	if (dispc->glb && dispc->glb->parse_dt)
		dispc->glb->parse_dt(&dispc->ctx);

	ctx->id = 0;
	ctx->is_stopped = true;
	ctx->panel = panel;

	switch (panel->type) {
	case SPRD_PANEL_TYPE_RGB:
	case SPRD_PANEL_TYPE_LVDS:
		ctx->if_type = SPRD_DISPC_IF_DPI;
		break;
	case SPRD_PANEL_TYPE_MIPI:
		if (panel->work_mode == SPRD_MIPI_MODE_VIDEO)
			ctx->if_type = SPRD_DISPC_IF_DPI;
		else
			ctx->if_type = SPRD_DISPC_IF_EDPI;
		break;
	case SPRD_PANEL_TYPE_MCU:
		ctx->if_type = SPRD_DISPC_IF_EDPI;
		break;
	default:
		ctx->if_type = SPRD_DISPC_IF_DPI;
		break;
	}

	return 0;
}

int sprd_dispc_probe(void)
{
	struct sprd_dispc *dispc;

	dispc = &dispc_device;

	dispc->core = dispc_core_ops_attach();
	dispc->clk = dispc_clk_ops_attach();
	dispc->glb = dispc_glb_ops_attach();

	dispc_context_init(dispc);
	sprd_dispc_resume(dispc);

	return 0;
}

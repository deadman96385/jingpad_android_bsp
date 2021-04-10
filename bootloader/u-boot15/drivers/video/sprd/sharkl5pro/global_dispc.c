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

#include <asm/arch/sprd_reg.h>
#include <sprd_glb.h>
#include "sprd_dispc.h"

static uint32_t dpu_core_clk[] = {
	153600000,
	192000000,
	256000000,
	307200000,
	384000000
};

static uint32_t dpi_clk_src[] = {
	96000000,
	128000000,
	153600000,
	192000000,
	204800000,
	273000000,
};

static uint32_t dpi_src_val;

static uint8_t calc_dpu_core_clk(void)
{
	return ARRAY_SIZE(dpu_core_clk) - 1;
}

static uint8_t calc_dpi_clk_src(uint32_t pclk)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dpi_clk_src); i++) {
		if ((dpi_clk_src[i] % pclk) == 0)
			return i;
	}

	pr_err("calc DPI_CLK_SRC failed, use default\n");
	return 0;
}

static int dispc_clk_init(struct dispc_context *ctx)
{
	uint8_t core_sel = calc_dpu_core_clk();
	uint8_t dpi_sel = calc_dpi_clk_src(ctx->panel->pixel_clk);

	pr_info("DPU_CORE_CLK = %u\n", dpu_core_clk[core_sel]);
	pr_info("DPI_CLK_SRC = %u\n", dpi_clk_src[dpi_sel]);

	sci_glb_write(REG_AP_CLK_CORE_CGM_DISPC0_CFG,
			core_sel, BIT(0) | BIT(1) | BIT(2));

	sci_glb_write(REG_AP_CLK_CORE_CGM_DISPC0_DPI_CFG,
			dpi_sel, BIT(0) | BIT(1) | BIT(2));

	dpi_src_val = dpi_clk_src[dpi_sel];

	return 0;
}

static int dispc_clk_update(struct dispc_context *ctx, int clk_id, int val)
{
	uint32_t div;

	div = dpi_src_val / val;
	if (dpi_src_val - div * val > (val / 2))
		div++;
	if ((div == 0) || (div > 0x10)) {
		pr_err("invalid dpi clk dividor (%d)\n", div);
		return -1;
	}

	sci_glb_write(REG_AP_CLK_CORE_CGM_DISPC0_DPI_CFG, (div - 1) << 8, (0xF << 8));

	pr_info("the actual dpi_clk = %d\n", dpi_src_val / div);
	return 0;
}

static int dispc_glb_parse_dt(struct dispc_context *ctx)
{
	ctx->base = SPRD_DPU_PHYS;

	return 0;
}

static void dispc_glb_enable(struct dispc_context *ctx)
{
	sci_glb_set(REG_AP_AHB_AHB_EB, BIT_AP_AHB_DISPC_EB);
}

static void dispc_glb_disable(struct dispc_context *ctx)
{
	sci_glb_clr(REG_AP_AHB_AHB_EB, BIT_AP_AHB_DISPC_EB);
}

static void dispc_reset(struct dispc_context *ctx)
{
	sci_glb_set(REG_AP_AHB_AHB_RST, BIT_AP_AHB_DISPC_SOFT_RST);
	udelay(10);
	sci_glb_clr(REG_AP_AHB_AHB_RST, BIT_AP_AHB_DISPC_SOFT_RST);
}

static void dispc_power_domain(struct dispc_context *ctx, int enable)
{

}

static struct dispc_clk_ops dispc_clk_ops = {
	.init = dispc_clk_init,
	.update = dispc_clk_update,
};

static struct dispc_glb_ops dispc_glb_ops = {
	.parse_dt = dispc_glb_parse_dt,
	.reset = dispc_reset,
	.enable = dispc_glb_enable,
	.disable = dispc_glb_disable,
	.power = dispc_power_domain,
};

struct dispc_clk_ops *dispc_clk_ops_attach(void)
{
	return &dispc_clk_ops;
}

struct dispc_glb_ops *dispc_glb_ops_attach(void)
{
	return &dispc_glb_ops;
}

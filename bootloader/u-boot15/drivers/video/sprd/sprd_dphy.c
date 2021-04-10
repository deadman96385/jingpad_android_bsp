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

#include "sprd_dphy.h"

struct sprd_dphy dphy_device;

__weak struct dphy_pll_ops *dphy_pll_ops_attach(void)
{
	return NULL;
}

__weak struct dphy_ppi_ops *dphy_ppi_ops_attach(void)
{
	return NULL;
}

__weak struct dphy_glb_ops *dphy_glb_ops_attach(void)
{
	return NULL;
}

int regmap_write(void *context, unsigned int reg,
				       unsigned int val)
{
	struct sprd_dphy *dphy = context;

	if (val > 0xff || reg > 0xff)
		return -EINVAL;

	pr_debug("reg = 0x%02x, val = 0x%02x\n", reg, val);

	mipi_dphy_test_write(dphy, reg, val);

	return 0;
}

int regmap_read(void *context, unsigned int reg,
				      unsigned int *val)
{
	struct sprd_dphy *dphy = context;
	int ret;

	if (reg > 0xff)
		return -EINVAL;

	ret = mipi_dphy_test_read(dphy, reg);
	if (ret < 0)
		return ret;

	*val = ret;

	pr_debug("reg = 0x%02x, val = 0x%02x\n", reg, *val);
	return 0;
}

static int sprd_dphy_resume(struct sprd_dphy *dphy)
{
	int ret;

	if (dphy->glb && dphy->glb->power)
		dphy->glb->power(&dphy->ctx, true);
	if (dphy->glb && dphy->glb->enable)
		dphy->glb->enable(&dphy->ctx);

	ret = mipi_dphy_configure(dphy);
	if (ret) {
		pr_err("sprd dphy init failed\n");
		return -EINVAL;
	}

	pr_info("dphy init OK\n");

	return ret;
}

int sprd_dphy_suspend(struct sprd_dphy *dphy)
{
	int ret;

	mipi_dphy_data_ulps_en(dphy, true);
	mipi_dphy_clk_ulps_en(dphy, true);

	ret = mipi_dphy_close(dphy);
	if (ret)
		pr_err("sprd dphy close failed\n");

	if (dphy->glb && dphy->glb->disable)
		dphy->glb->disable(&dphy->ctx);
	if (dphy->glb && dphy->glb->power)
		dphy->glb->power(&dphy->ctx, false);

	pr_info("dphy uninit OK\n");
	return ret;
}

static int dphy_context_init(struct sprd_dphy *dphy)
{
	if (dphy->glb && dphy->glb->parse_dt)
		dphy->glb->parse_dt(&dphy->ctx);

	dphy->ctx.regmap = dphy;
	dphy->ctx.freq = dphy->panel->phy_freq;
	dphy->ctx.lanes = dphy->panel->lane_num;

	return 0;
}

int sprd_dphy_probe(void)
{
	struct sprd_dphy *dphy;

	dphy = &dphy_device;
	dphy->panel = panel_info_attach();
	dphy->ppi = dphy_ppi_ops_attach();
	dphy->pll = dphy_pll_ops_attach();
	dphy->glb = dphy_glb_ops_attach();

	dphy_context_init(dphy);
	sprd_dphy_resume(dphy);

	return 0;
}

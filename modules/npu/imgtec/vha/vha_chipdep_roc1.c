/*
 * Chip depended functions for ROC1.
 *
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

#include <linux/err.h>
#include <linux/delay.h>
#include <linux/mfd/syscon.h>
#include <linux/device.h>
#include <linux/of_platform.h>
#include <linux/pm_domain.h>
#include <linux/regmap.h>
#include <linux/clk.h>
#include <linux/dma-mapping.h>
#include <dt-bindings/soc/sprd,roc1-regs.h>
#include <dt-bindings/soc/sprd,roc1-mask.h>
#include <linux/moduleparam.h>
#include <linux/soc/sprd/hwfeature.h>

#include "vha_chipdep.h"

static u32 ai_apll_freq = 0;
module_param(ai_apll_freq, uint, 0444);
MODULE_PARM_DESC(ai_apll_freq,
	"AI apll frequency in MHz");

struct npu_pm_domain {
	struct generic_pm_domain pd;
	struct device *dev;
	struct regmap *pmu_apb_regs;
	union {
		u32 args[2];
		struct {
			u32 cfg_regoff, cfg_mask;
		} s;
	} u;
};
static struct npu_pm_domain pd_ai_sys, pd_img_nna, pd_camb_nna;

static int vha_power_on(struct generic_pm_domain *domain)
{
	struct npu_pm_domain *pd;
	uint32_t reg, mask;
	pd = container_of(domain, struct npu_pm_domain, pd);
	reg = pd->u.s.cfg_regoff;
	mask = pd->u.s.cfg_mask;
	//WARN_ON(1);

	regmap_update_bits(pd->pmu_apb_regs, reg, mask, 0);
	/* FIXME: for debug purpose */
	return 0;
}

static int vha_power_off(struct generic_pm_domain *domain)
{
	struct npu_pm_domain *pd;
	uint32_t reg, mask;
	pd = container_of(domain, struct npu_pm_domain, pd);
	reg = pd->u.s.cfg_regoff;
	mask = pd->u.s.cfg_mask;
	//WARN_ON(1);

	/* FIXME: for debug purpose */
	regmap_update_bits(pd->pmu_apb_regs, reg, mask, mask);
	return 0;
}

int vha_powerdomain_init(struct device *dev)
{
	struct of_phandle_args args;
	int index = 1;
	int err, ret;
	err = of_parse_phandle_with_args(dev->of_node, "sprd,pd-ai",
					 NULL, index,
					 &args);

	if (err == 0) {
		struct device_node *np = args.np;
		struct npu_pm_domain *pd = &pd_camb_nna;
		dev_info(dev, "domain_np fullname %s\n", np->full_name);
		pd->pmu_apb_regs = syscon_regmap_lookup_by_name(np, "cfg");
		if (IS_ERR(pd->pmu_apb_regs)) {
			dev_err_once(dev, "failed to map domain cfg reg\n");
			return -EINVAL;
		}

		ret = syscon_get_args_by_name(np, "cfg", 2, pd->u.args);
		if (ret != 2) {
			dev_err_once(dev, "failed to parse domain cfg reg\n");
			return -EINVAL;
		}
		pd->dev = dev;

        }

	index = 0;
	err = of_parse_phandle_with_args(dev->of_node, "sprd,pd-ai",
					 NULL, index,
					 &args);
	if (err == 0) {
		struct device_node *np = args.np;
		struct npu_pm_domain *pd = &pd_img_nna;
		dev_info(dev, "domain_np fullname %s\n", np->full_name);
		pd->pmu_apb_regs = syscon_regmap_lookup_by_name(np, "cfg");
		if (IS_ERR(pd->pmu_apb_regs)) {
			dev_err_once(dev, "failed to map domain cfg reg\n");
			return -EINVAL;
		}

		ret = syscon_get_args_by_name(np, "cfg", 2, pd->u.args);
		if (ret != 2) {
			dev_err_once(dev, "failed to parse domain cfg reg\n");
			return -EINVAL;
		}
		pd->dev = dev;

		/* parse ai sys domain */
		err = of_parse_phandle_with_args(np, "sprd,pd-ai",
						 NULL, index,
						 &args);
		if (err == 0) {
			struct device_node *np = args.np;
			struct npu_pm_domain *pd = &pd_ai_sys;
			dev_info(dev, "domain_np fullname %s\n", np->full_name);
			pd->pmu_apb_regs = syscon_regmap_lookup_by_name(np, "cfg");
			if (IS_ERR(pd->pmu_apb_regs)) {
				dev_err_once(dev, "failed to map domain cfg reg\n");
				return -EINVAL;
			}

			ret = syscon_get_args_by_name(np, "cfg", 2, pd->u.args);
			if (ret != 2) {
				dev_err_once(dev, "failed to parse domain cfg reg\n");
				return -EINVAL;
			}
			pd->dev = dev;
		}

	}

	return err;
}

#define  LOOP_TIME  34  // (2000us - 300 us)/50us =34 times 
static int vha_wait_power_ready(struct generic_pm_domain *domain)
{

	struct npu_pm_domain *pd;
	uint32_t ret, mask, reg, val, loop=0;

	pd = container_of(domain, struct npu_pm_domain, pd);

	reg = REG_PMU_APB_PWR_STATUS0_DBG;
	mask =  MASK_PMU_APB_PD_AI_POWERVR_STATE |
	        MASK_PMU_APB_PD_AI_CAMBRICON_STATE |
	        MASK_PMU_APB_PD_AI_SYS_STATE;

        /* delay for setup power domain */
        udelay(300);
       /* check  setup if ok*/
        if (pd->pmu_apb_regs) {
            while(loop < LOOP_TIME){

                ret = regmap_read(pd->pmu_apb_regs,reg, &val);

                if (ret){
                    pr_err("read pmu_apb_regs error %s, %d\n",__func__, __LINE__);
                    pr_err("read pmu_apb_regs regs  0x%x\n", reg);
                    return ret;
                }

                if ((val & mask) == 0){
                    return 0 ;
                }

                loop++ ;
                udelay(50);

            }
        }
        else
        {
            pr_err("pmu_apb_regs uninit %s, %d\n",__func__, __LINE__);
        }

        pr_err("check pmu_apb_regs regs 0x%x  timeout!!!\n", reg);
        return 1 ;
}

int vha_powerdomain_setup(void)
{
        /* FIXME: for debug purpose */
        vha_power_on(&pd_ai_sys.pd);
        vha_power_on(&pd_camb_nna.pd);
        vha_power_on(&pd_img_nna.pd);

        vha_wait_power_ready(&pd_ai_sys.pd);
        return 0 ;

}

int vha_powerdomain_unsetup(void)
{

        /* FIXME: for debug purpose */
        vha_power_off(&pd_img_nna.pd);
        vha_power_off(&pd_camb_nna.pd);
        vha_power_off(&pd_ai_sys.pd);

        return 0;
}

static struct regmap *ai_apb_regs;

static struct regmap *vha_parse_ai_apb_regs_dt(struct device *dev)
{
	struct device_node *syscon_np;
	struct of_phandle_args args;
	int index = 0;
	int rc;
	struct device_node *np = dev->of_node;
	struct regmap *ai_apb_regs;

	/*FIXME: get ai_apb_regs base from reset syscon*/
	index = of_property_match_string(np, "syscon-names", "reset");
	if (index < 0) {
		pr_warn("failed to get syscon-name: reset\n");
		return ERR_PTR(-EINVAL);
	}

	rc = of_parse_phandle_with_args(np, "syscons", "#syscon-cells", index,
			&args);
	if (rc) {
		pr_warn("failed to get syscon args for reset\n");
		return ERR_PTR(-EINVAL);
	}

	syscon_np = args.np;

	if (!syscon_np) {
		pr_warn("failed to get syscon phandle\n");
		return ERR_PTR(-ENODEV);
	}

	ai_apb_regs = syscon_node_to_regmap(syscon_np);

	of_node_put(syscon_np);

	return ai_apb_regs;
}

struct regmap *vha_get_ai_apb_regs(struct device *dev)
{
	if (!ai_apb_regs)
		ai_apb_regs = vha_parse_ai_apb_regs_dt(dev);

	return ai_apb_regs;
}

static struct clk_bulk_data clks[] = {
	[0].id = "ap_ai",
	[1].id = "top_eb",
	[2].id = "pvr_eb",
};

static int vha_auto_ckg_setup(struct device *dev)
{
	unsigned int mask;
	struct regmap *ai_apb_regs;

	ai_apb_regs = vha_get_ai_apb_regs(dev);
	if (IS_ERR(ai_apb_regs)) {
		pr_warn("failed to get ai_apb_regs\n");
		return PTR_ERR(ai_apb_regs);
	}

	mask =	MASK_AI_APB_AUTO_CKG_EN_POWERVR_CFG |
		MASK_AI_APB_AUTO_CKG_EN_MAIN_MTX |
		MASK_AI_APB_AUTO_CKG_EN_POWERVR |
		MASK_AI_APB_DVFS_CKG_EN;
	regmap_update_bits(ai_apb_regs, REG_AI_APB_GEN_CLK_CFG, mask, mask);

	return 0;
}

enum {
	PVR_CLK_512M,
	PVR_CLK_APLL,
	PVR_CLK_NUM
};

static const char *vha_pvr_clk_names[PVR_CLK_NUM] = {
	[PVR_CLK_512M] = "pvr_clk_512m",
	[PVR_CLK_APLL] = "pvr_clk_apll",
};

struct vha_clk_src {
	char *clk_name;
	unsigned int parent_clk_id;
	unsigned int default_parent_clk_id;
	struct clk *clk;
	struct clk  *parent_clk;
	struct clk  *default_parent_clk;

};

static struct vha_clk_src vha_clk[] = {
	[0].clk_name = "pvr_clk",
	[0].parent_clk_id = PVR_CLK_APLL,
	[0].default_parent_clk_id = PVR_CLK_512M,
	[1].clk_name = "mtx_clk",
	[1].parent_clk_id = PVR_CLK_APLL,
	[1].default_parent_clk_id = PVR_CLK_512M,
};

static struct clk *vha_apll_clk = NULL;

enum {
	ROC1_AA_CHIP,
	ROC1_NOT_AA_CHIP
};

static int vha_get_chip_id(struct device *dev)
{
	int chip_id = ROC1_AA_CHIP;
	if (sprd_kproperty_chipid("UD710-AA") == 0)
		chip_id = ROC1_NOT_AA_CHIP;

	dev_info(dev, "chip id is %d\n", chip_id);

	return chip_id;
}

static u32 vha_get_apll_rate(struct device *dev) {
	int chip_id = vha_get_chip_id(dev);

	if (ai_apll_freq == 0) {
	/* ai_apll_freq is not set, use default freq*/
		if (chip_id == ROC1_AA_CHIP)
			ai_apll_freq = 600; //MHz
		else
			ai_apll_freq = 800; //MHz
	}

	return ai_apll_freq;
}

int vha_apll_rate_set(struct device *dev)
{
	int ret;
	unsigned long apll_rrate;
	unsigned long curr_apll_rate;

	if (vha_apll_clk) {
		apll_rrate = clk_round_rate(vha_apll_clk, vha_get_apll_rate(dev) * 1000 * 1000);
		curr_apll_rate = clk_get_rate(vha_apll_clk);
		if (curr_apll_rate != apll_rrate) {
			dev_info(dev, "apll rate is not %lu, set it now\n",
				 apll_rrate);
			ret = clk_set_rate(vha_apll_clk, apll_rrate);
			if (ret) {
				dev_err(dev, "set apll clock rate failed, ret %d\n", ret);
				return ret;
			}
		}
	}

	return 0;
}


int vha_clock_init(struct device *dev)
{
	int i;
	int num_clks = ARRAY_SIZE(vha_clk);
	unsigned int parent_clk_id;

        for (i = 0; i < num_clks; i++) {
                vha_clk[i].clk = devm_clk_get(dev, vha_clk[i].clk_name);
                if (IS_ERR(vha_clk[i].clk)) {
                        dev_err(dev, "get clock %s failed\n",
                                vha_clk[i].clk_name);
                        return PTR_ERR(vha_clk[i].clk);
                }

                parent_clk_id = vha_clk[i].default_parent_clk_id;
                if (parent_clk_id >= PVR_CLK_NUM) {
                        dev_err(dev, "parent clk id exceed %d\n", PVR_CLK_NUM);
                        return -EINVAL;
                }

                vha_clk[i].default_parent_clk = devm_clk_get(dev, vha_pvr_clk_names[parent_clk_id]);
                if (IS_ERR(vha_clk[i].default_parent_clk)) {
                        dev_err(dev, "get parent clock %s failed\n",
                                vha_pvr_clk_names[parent_clk_id]);
                        return PTR_ERR(vha_clk[i].default_parent_clk);
                }

                parent_clk_id = vha_clk[i].parent_clk_id;
                if (parent_clk_id >= PVR_CLK_NUM) {
                        dev_err(dev, "parent clk id exceed %d\n", PVR_CLK_NUM);
                        return -EINVAL;
                }

                vha_clk[i].parent_clk = devm_clk_get(dev, vha_pvr_clk_names[parent_clk_id]);
                if (IS_ERR(vha_clk[i].parent_clk)) {
                        dev_err(dev, "get parent clock %s failed\n",
                                vha_pvr_clk_names[parent_clk_id]);
                        return PTR_ERR(vha_clk[i].parent_clk);
                }

                if (parent_clk_id == PVR_CLK_APLL)
                        vha_apll_clk = vha_clk[i].parent_clk;

        }

	return 0;
}

static int vha_clock_select(struct device *dev)
{

	int i, ret;
	int num_clks = ARRAY_SIZE(vha_clk);

        for (i = 0; i < num_clks; i++) {
                ret = clk_set_parent(vha_clk[i].clk, vha_clk[i].default_parent_clk);
                if (ret) {
                        dev_err(dev, "clock set parent failed, ret %d\n", ret);
                        return ret;
                }

                ret = clk_set_parent(vha_clk[i].clk, vha_clk[i].parent_clk);
                if (ret) {
                        dev_err(dev, "clock set parent failed, ret %d\n", ret);
                        return ret;
                }
        }
        return 0 ;
}

int vha_clockdomain_init(struct device *dev)
{
	struct device_node *np = dev->of_node;
	int num_clks = ARRAY_SIZE(clks);
	struct of_phandle_args clkspec;
	int rc, res;

	res = clk_bulk_get(dev, num_clks - 1, &clks[1]);
	if (res) {
		dev_err(dev, "clk_bulk_get failed, res %d\n", res);
		return res;
	}
	rc = of_parse_phandle_with_args(np, "clocks", "#clock-cells", 0,
					&clkspec);
	if (rc == 0) {
		struct device_node *np = clkspec.np;
		dev_info(dev, "ai gate %s\n", np->full_name);
		clks[0].clk = of_clk_get(np, 0);
		if (IS_ERR(clks[0].clk)) {
			dev_err(dev, "failed to get ap ai_eb clock\n");
			return PTR_ERR(clks[0].clk);
		}
	}

	return 0;
}

int vha_clockdomain_select(struct device *dev)
{
	vha_auto_ckg_setup(dev);
	vha_clock_select(dev);
	vha_apll_rate_set(dev);
	return 0;
}


int vha_clockdomain_setup(void)
{
	int num_clks = ARRAY_SIZE(clks);

	clk_prepare_enable(vha_apll_clk);
	/* FIXME: for debug purpose */
	clk_bulk_prepare_enable(num_clks, clks);
	return 0;
}

int vha_clockdomain_unsetup(void)
{
	int num_clks = ARRAY_SIZE(clks);

	/* FIXME: for debug purpose */
	clk_bulk_disable_unprepare(num_clks, clks);
	clk_disable_unprepare(vha_apll_clk);
	return 0;
}

#define VHA_ROC1_DMAMASK DMA_BIT_MASK(33)
u64 vha_get_chip_dmamask(void)
{
	return VHA_ROC1_DMAMASK;
}

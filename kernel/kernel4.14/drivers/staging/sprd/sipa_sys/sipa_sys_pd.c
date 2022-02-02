/*
 * Copyright (C) 2018-2019 Unisoc Corporation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include <linux/clk.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/mfd/syscon.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/pm_domain.h>
#include <linux/power_supply.h>
#include <linux/regmap.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/sipa.h>
#include <linux/debugfs.h>

#define DRV_NAME "sprd-sipa-sys"

#define SPRD_IPA_POWERON_POLL_US 50
#define SPRD_IPA_POWERON_TIMEOUT 5000

static const char * const reg_name_tb[] = {
	"ipa-sys-forcewakeup",
	"ipa-sys-forceshutdown",
	"ipa-sys-autoshutdown",
	"ipa-sys-forcedslp",
	"ipa-sys-dslpen",
	"ipa-sys-forcelslp",
	"ipa-sys-lslpen",
	"ipa-sys-smartlslpen",
	"ipa-sys-ipaeb",
	"ipa-sys-cm4eb",
	"ipa-sys-autogaten",
	"ipa-sys-s5-autogaten",
	"ipa-sys-pwr-state",
};

enum  {
	IPA_SYS_FORCEWAKEUP,
	IPA_SYS_FORCESHUTDOWN,
	IPA_SYS_AUTOSHUTDOWN,
	IPA_SYS_FORCEDSLP,
	IPA_SYS_DSLPEN,
	IPA_SYS_FORCELSLP,
	IPA_SYS_LSLPEN,
	IPA_SYS_SMARTSLPEN,
	IPA_SYS_IPAEB,
	IPA_SYS_CM4EB,
	IPA_SYS_AUTOGATEN,
	IPA_SYS_S5_AUTOGATEN,
	IPA_SYS_PWR_STATE,
};

struct sipa_sys_register {
	struct regmap *rmap;
	u32 reg;
	u32 mask;
};

struct sipa_sys_pd_drv {
	struct device *dev;
	struct generic_pm_domain gpd;
	struct clk *ipa_core_clk;
	struct clk *ipa_core_parent;
	struct clk *ipa_core_default;
	bool pd_on;
	struct sipa_sys_register regs[0];
};

static int sipa_sys_set_register(struct sipa_sys_register *reg_info,
				 bool set)
{
	int ret = 0;
	u32 val = set ? reg_info->mask : (~reg_info->mask);

	if (reg_info->rmap) {
		ret = regmap_update_bits(reg_info->rmap,
					 reg_info->reg,
					 reg_info->mask,
					 val);
		if (ret < 0)
			pr_warn("%s: set register bits fail", __func__);
	}
	return ret;
}

static int sipa_sys_wait_power_on(struct sipa_sys_register *reg_info)
{
	int ret = 0;
	u32 val;

	if (reg_info->rmap) {
		pr_info("sipa start poll ipa sys power status\n");
		ret = regmap_read_poll_timeout(reg_info->rmap,
					       reg_info->reg,
					       val,
					       !(val & reg_info->mask),
					       SPRD_IPA_POWERON_POLL_US,
					       SPRD_IPA_POWERON_TIMEOUT);
	} else {
		usleep_range((SPRD_IPA_POWERON_TIMEOUT >> 2) + 1, 5000);
	}

	if (ret)
		pr_err("sipa polling check power on reg timed out: %x\n", val);

	return ret;
}

static int sipa_sys_do_power_on(struct sipa_sys_pd_drv *drv)
{
	struct sipa_sys_register *reg_info = &drv->regs[IPA_SYS_FORCEWAKEUP];
	int ret = 0;

	dev_info(drv->dev, "sipa do power on\n");
	if (reg_info->rmap) {
		ret = regmap_update_bits(reg_info->rmap,
					 reg_info->reg,
					 reg_info->mask,
					 reg_info->mask);
		if (ret < 0)
			pr_warn("%s: set forcewakeup bits fail", __func__);
	}

	/* access IPA_SYS_CM4EB register need wait ipa_sys power on */
	reg_info = &drv->regs[IPA_SYS_PWR_STATE];
	ret = sipa_sys_wait_power_on(reg_info);
	if (ret)
		pr_warn("%s: wait pwr on timeout\n", __func__);

	/* disable ipa_cm4 eb bit, for asic initail value fault */
	reg_info = &drv->regs[IPA_SYS_CM4EB];
	if (reg_info->rmap) {
		ret = regmap_update_bits(reg_info->rmap,
					 reg_info->reg,
					 reg_info->mask,
					 ~reg_info->mask);
		if (ret < 0)
			pr_warn("%s: update cm4eb fail", __func__);
	}

	/* set ipa core clock */
	if (drv->ipa_core_clk && drv->ipa_core_parent)
		clk_set_parent(drv->ipa_core_clk, drv->ipa_core_parent);

	return ret;
}

static int sipa_sys_clk_init(struct sipa_sys_pd_drv *drv)
{
	drv->ipa_core_clk = devm_clk_get(drv->dev, "ipa_core");
	if (IS_ERR(drv->ipa_core_clk)) {
		dev_warn(drv->dev, "sipa_sys can't get the IPA core clock\n");
		return PTR_ERR(drv->ipa_core_clk);
	}

	drv->ipa_core_parent = devm_clk_get(drv->dev, "ipa_core_source");
	if (IS_ERR(drv->ipa_core_parent)) {
		dev_warn(drv->dev, "sipa_sys can't get the ipa core source\n");
		return PTR_ERR(drv->ipa_core_parent);
	}

	drv->ipa_core_default = devm_clk_get(drv->dev, "ipa_core_default");
	if (IS_ERR(drv->ipa_core_default)) {
		dev_err(drv->dev, "sipa_sys can't get the ipa core default\n");
		return PTR_ERR(drv->ipa_core_default);
	}

	return 0;
}

static int sipa_sys_do_power_off(struct sipa_sys_pd_drv *drv)
{
	struct sipa_sys_register *reg_info = &drv->regs[IPA_SYS_FORCEWAKEUP];
	int ret = 0;

	dev_info(drv->dev, "sipa do power off\n");
	/* set ipa core clock to default */
	if (drv->ipa_core_clk && drv->ipa_core_default)
		clk_set_parent(drv->ipa_core_clk, drv->ipa_core_default);

	if (reg_info->rmap) {
		ret = regmap_update_bits(reg_info->rmap,
					 reg_info->reg,
					 reg_info->mask,
					 ~reg_info->mask);
		if (ret < 0)
			pr_warn("%s: clear forcewakeup bits fail", __func__);
	}

	return ret;
}

static int sipa_sys_update_power_state(struct sipa_sys_pd_drv *drv)
{
	if (drv->pd_on)
		sipa_sys_do_power_on(drv);
	else
		sipa_sys_do_power_off(drv);

	return 0;
}

static int sipa_sys_parse_dts(struct sipa_sys_pd_drv *drv)
{
	int ret, i;
	u32 reg_info[2];
	const char *reg_name;
	struct regmap *rmap;
	struct device_node *np = drv->dev->of_node;

	/* read regmap info */
	for (i = 0; i < ARRAY_SIZE(reg_name_tb); i++) {
		reg_name = reg_name_tb[i];
		rmap =  syscon_regmap_lookup_by_name(np, reg_name);
		if (IS_ERR(rmap)) {
			/* work normal when remove some item from dts */
			dev_warn(drv->dev, "Parse drs %s regmap fail\n",
				 reg_name);
			continue;
		}
		ret = syscon_get_args_by_name(np, reg_name, 2, reg_info);
		if (ret != 2) {
			dev_warn(drv->dev,
				 "Parse drs %s args fail, ret = %d\n",
				 reg_name,
				 ret);
			continue;
		}
		drv->regs[i].rmap = rmap;
		drv->regs[i].reg = reg_info[0];
		drv->regs[i].mask = reg_info[1];
		dev_dbg(drv->dev, "dts[%s]%p, 0x%x, 0x%x\n",
			reg_name,
			drv->regs[i].rmap,
			drv->regs[i].reg,
			drv->regs[i].mask);
	}

	return 0;
}

static int sipa_sys_pd_power_on(struct generic_pm_domain *domain)
{
	struct sipa_sys_pd_drv *drv;

	drv = container_of(domain, struct sipa_sys_pd_drv, gpd);

	drv->pd_on = true;
	sipa_sys_update_power_state(drv);
	dev_dbg(drv->dev, "pd power on\n");
	return 0;
}

static int sipa_sys_pd_power_off(struct generic_pm_domain *domain)
{
	struct sipa_sys_pd_drv *drv;

	drv = container_of(domain, struct sipa_sys_pd_drv, gpd);

	drv->pd_on = false;
	sipa_sys_update_power_state(drv);
	dev_dbg(drv->dev, "pd power off\n");
	return 0;
}

static void sipa_sys_init(struct sipa_sys_pd_drv *drv)
{
	/* step1 clear force shutdown:0x32280538[25] */
	sipa_sys_set_register(&drv->regs[IPA_SYS_FORCESHUTDOWN], false);
	/* set auto shutdown enable:0x32280538[24] */
	sipa_sys_set_register(&drv->regs[IPA_SYS_AUTOSHUTDOWN], true);

	/* step2 clear ipa force deep sleep:0x32280544[6] */
	sipa_sys_set_register(&drv->regs[IPA_SYS_FORCEDSLP], false);
	/* set ipa deep sleep enable:0x3228022c[0] */
	sipa_sys_set_register(&drv->regs[IPA_SYS_DSLPEN], true);

	/* step3 clear ipa force light sleep:0x32280548[6] */
	sipa_sys_set_register(&drv->regs[IPA_SYS_FORCELSLP], false);
	/* set ipa light sleep enable:0x32280230[6] */
	sipa_sys_set_register(&drv->regs[IPA_SYS_LSLPEN], true);
	/* set ipa smart light sleep enable:0x32280230[7] */
	sipa_sys_set_register(&drv->regs[IPA_SYS_SMARTSLPEN], true);
}

static int sipa_sys_register_power_domain(struct sipa_sys_pd_drv *drv)
{
	int ret;

	drv->gpd.name = kstrdup(drv->dev->of_node->name, GFP_KERNEL);
	if (!drv->gpd.name)
		return -ENOMEM;

	drv->gpd.power_off = sipa_sys_pd_power_off;
	drv->gpd.power_on = sipa_sys_pd_power_on;

	ret = pm_genpd_init(&drv->gpd, NULL, true);
	if (ret) {
		dev_warn(drv->dev, "sipa sys pm_genpd_init fail!");
		kfree(drv->gpd.name);
		return ret;
	}

	ret = of_genpd_add_provider_simple(drv->dev->of_node, &drv->gpd);
	if (ret) {
		dev_warn(drv->dev, "sipa sys genpd_add_provider fail!");
		pm_genpd_remove(&drv->gpd);
		kfree(drv->gpd.name);
	}

	return ret;
}

#ifdef CONFIG_DEBUG_FS
static int sipa_sys_debug_show(struct seq_file *s, void *unused)
{
	struct pm_domain_data *pdd;
	struct sipa_sys_pd_drv *drv = (struct sipa_sys_pd_drv *)s->private;

	seq_puts(s, "status:\n");
	seq_puts(s, "\t0: active 1: power off\n\n");
	seq_puts(s, "power status:\n");
	seq_puts(s, "\t0: active 1: resuming 2: suspended 3: suspending\n\n");

	seq_printf(s, "pd_on = %d sd_count = %d status = %d\n",
		   drv->pd_on,
		   atomic_read(&drv->gpd.sd_count),
		   drv->gpd.status);

	seq_printf(s, "device_count = %d suspended_count = %d prepared_count = %d\n",
		   drv->gpd.device_count, drv->gpd.suspended_count,
		   drv->gpd.prepared_count);

	list_for_each_entry(pdd, &drv->gpd.dev_list, list_node)
		seq_printf(s,
			   "%s power status = %d, disable_depth = %d usage_cnt = %d\n",
			   dev_name(pdd->dev), pdd->dev->power.runtime_status,
			   pdd->dev->power.disable_depth,
			   atomic_read(&pdd->dev->power.usage_count));

	debugfs_create_symlink("sprd-sipa-sys", NULL,
			       "/sys/kernel/debug/sprd-sipa-sys/power_domain");

	return 0;
}

static int sipa_sys_debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, sipa_sys_debug_show, inode->i_private);
}

static const struct file_operations sipa_sys_debug_fops = {
	.open = sipa_sys_debug_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int sipa_sys_init_debugfs(struct platform_device *pdev)
{
	struct dentry *root;
	struct sipa_sys_pd_drv *drv = platform_get_drvdata(pdev);

	root = debugfs_create_dir(DRV_NAME, NULL);
	if (!root)
		return -ENOMEM;

	debugfs_create_file("power_domain", 0444, root, drv,
			    &sipa_sys_debug_fops);

	return 0;
}
#endif

static int sipa_sys_drv_probe(struct platform_device *pdev_p)
{
	int ret;
	struct sipa_sys_pd_drv *drv;

	drv = devm_kzalloc(&pdev_p->dev, sizeof(*drv) +
		sizeof(struct sipa_sys_register) * ARRAY_SIZE(reg_name_tb),
		GFP_KERNEL);
	if (!drv)
		return -ENOMEM;

	platform_set_drvdata(pdev_p, drv);
	drv->dev = &pdev_p->dev;

	ret = sipa_sys_clk_init(drv);
	if (ret)
		return ret;

	ret = sipa_sys_parse_dts(drv);
	if (ret)
		return ret;

	ret = sipa_sys_register_power_domain(drv);
	if (ret)
		dev_warn(drv->dev, "sipa sys reg power domain fail!");

#ifdef CONFIG_DEBUG_FS
	ret = sipa_sys_init_debugfs(pdev_p);
	if (ret)
		dev_warn(drv->dev, "sipa_sys init debug fs fail\n");
#endif

	sipa_sys_init(drv);

	return 0;
}

static const struct of_device_id sipa_sys_drv_match[] = {
	{.compatible = "sprd,roc1-ipa-sys-power-domain",},
	{}
};

static struct platform_driver sipa_sys_drv = {
	.probe = sipa_sys_drv_probe,
	.driver = {
		.name = DRV_NAME,
		.of_match_table = sipa_sys_drv_match,
	},
};

static int __init sipa_sys_pd_init(void)
{
	pr_debug("sipa sys pd init\n");

	/* Register as a platform device driver */
	return platform_driver_register(&sipa_sys_drv);
}

module_init(sipa_sys_pd_init);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Spreadtrum sipa sys power domain device driver");

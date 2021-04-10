/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
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

#include <linux/clk.h>
#include <linux/clk-provider.h>
#include <linux/delay.h>
#include <linux/mfd/syscon.h>
/* #include <linux/mfd/syscon/sprd-glb.h> */
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/spinlock.h>
#include <linux/regmap.h>
#include <linux/interrupt.h>
#include <sprd_mm.h>
#include <video/sprd_mmsys_pw_domain.h>

#include "isp_reg.h"
#include "isp_int.h"
#include "isp_core.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "ISP_DRV: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

static uint32_t  s_isp_irq_no[ISP_LOGICAL_COUNT];
unsigned long s_isp_regbase[ISP_MAX_COUNT];
unsigned long isp_phys_base[ISP_MAX_COUNT];
unsigned long s_isp_mmubase;

int isp_hw_init(void *arg)
{
	int ret = 0;
	struct isp_pipe_dev *dev = NULL;
	struct cam_hw_info *hw = NULL;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct isp_pipe_dev *)arg;
	hw = dev->isp_hw;

	ret = sprd_cam_pw_on();
	ret = sprd_cam_domain_eb();

	ret = hw->hw_ops.isp_soc_ops.clk_enable(hw->soc_isp);
	if (ret)
		goto clk_fail;

	ret = hw->hw_ops.isp_soc_ops.reset(hw, NULL);
	if (ret)
		goto reset_fail;

	ret = isp_irq_request(&hw->pdev->dev, s_isp_irq_no, arg);

	return 0;

reset_fail:
	hw->hw_ops.isp_soc_ops.clk_disable(hw->soc_isp);
clk_fail:
	sprd_cam_domain_disable();
	sprd_cam_pw_off();

	return ret;
}

int isp_hw_deinit(void *arg)
{
	int ret = 0;
	struct isp_pipe_dev *dev = NULL;
	struct cam_hw_info *hw = NULL;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct isp_pipe_dev *)arg;
	hw = dev->isp_hw;

	ret = hw->hw_ops.isp_soc_ops.reset(hw, NULL);
	ret = isp_irq_free(&hw->pdev->dev, arg);
	ret = hw->hw_ops.isp_soc_ops.clk_disable(hw->soc_isp);

	sprd_cam_domain_disable();
	sprd_cam_pw_off();

	return ret;
}

struct isp_work_ctrl {
	uint32_t work_en_sw;
	uint32_t work_start;
	uint32_t work_mode;
};

int isp_hw_start(struct cam_hw_info *hw, void *arg)
{
	int ret = 0;
	struct isp_work_ctrl work_ctrl;

	/* by SW config (for DVFS)*/
	work_ctrl.work_mode = 1;
	work_ctrl.work_en_sw = 0;
	work_ctrl.work_start = 1;

#if 0
	/* to be refined. */
	ISP_HREG_MWR(ISP_WORK_CTRL, BIT_0, work_ctrl.work_mode);
	ISP_HREG_MWR(ISP_WORK_CTRL, BIT_1, (work_ctrl.work_start << 1));
	ISP_HREG_MWR(ISP_WORK_CTRL, BIT_2, (work_ctrl.work_en_sw << 2));
#endif
	hw->hw_ops.core_ops.default_para_set(hw, NULL, ISP_HW_PARA);

	return ret;
}

int isp_hw_stop(struct cam_hw_info *hw, void *arg)
{
	uint32_t id;
	uint32_t cid;

	id = hw->ip_isp->idx;

	ISP_HREG_MWR(ISP_AXI_ITI2AXIM_CTRL, BIT_26, 1 << 26);

	pr_info("ISP%d:ISP_AXI_AXIM_CTRL 0x%x INT STATUS 0x%x  0x%x 0x%x 0x%x\n",
		id, ISP_HREG_RD(ISP_AXI_ITI2AXIM_CTRL),
		ISP_HREG_RD(ISP_P0_INT_BASE + ISP_INT_STATUS),
		ISP_HREG_RD(ISP_C0_INT_BASE + ISP_INT_STATUS),
		ISP_HREG_RD(ISP_P1_INT_BASE + ISP_INT_STATUS),
		ISP_HREG_RD(ISP_C1_INT_BASE + ISP_INT_STATUS));
	udelay(10);

	for (cid = 0; cid < 4; cid++)
		hw->hw_ops.isp_irq_ops.irq_clear(hw->ip_isp, &cid);

	return 0;
}

int sprd_isp_parse_dt(struct device_node *dn,
		struct cam_hw_info *hw_info,
		uint32_t *isp_count)
{
	int i = 0;
	uint32_t count = 0;
	void __iomem *reg_base;
	struct cam_hw_soc_info *soc_isp = NULL;
	struct cam_hw_ip_info *ip_isp = NULL;
	struct device_node *isp_node = NULL;
	struct device_node *qos_node = NULL;
	struct device_node *iommu_node = NULL;
	struct resource res = {0};
	int args_count = 0;
	uint32_t args[2];

	/* todo: should update according to SharkL5/ROC1 dts
	 * or set value for required variables with hard-code
	 * for quick bringup
	 */

	if (!dn || !hw_info) {
		pr_err("fail to get dn %p hw info %p\n", dn, hw_info);
		return -EINVAL;
	}

	pr_info("isp dev device node %s, full name %s\n",
		dn->name, dn->full_name);
	isp_node = of_parse_phandle(dn, "sprd,isp", 0);
	if (isp_node == NULL) {
		pr_err("fail to parse the property of sprd,isp\n");
		return -EFAULT;
	}

	soc_isp = hw_info->soc_isp;
	ip_isp = hw_info->ip_isp;
	pr_info("after isp dev device node %s, full name %s\n",
		isp_node->name, isp_node->full_name);
	soc_isp->pdev = of_find_device_by_node(isp_node);
	pr_info("sprd s_isp_pdev name %s\n", soc_isp->pdev->name);

	if (of_device_is_compatible(isp_node, "sprd,isp")) {
		if (of_property_read_u32_index(isp_node,
			"sprd,isp-count", 0, &count)) {
			pr_err("fail to parse the property of sprd,isp-count\n");
			return -EINVAL;
		}

		if (count > 1) {
			pr_err("fail to count isp number: %d", count);
			return -EINVAL;
		}
		*isp_count = count;

		/* read clk from dts */
		soc_isp->core_eb = of_clk_get_by_name(isp_node, "isp_eb");
		if (IS_ERR_OR_NULL(soc_isp->core_eb)) {
			pr_err("fail to read dts isp eb\n");
			return -EFAULT;
		}
		soc_isp->axi_eb = of_clk_get_by_name(isp_node, "isp_axi_eb");
		if (IS_ERR_OR_NULL(soc_isp->core_eb)) {
			pr_err("fail to read dts isp axi eb\n");
			return -EFAULT;
		}
		soc_isp->clk = of_clk_get_by_name(isp_node, "isp_clk");
		if (IS_ERR_OR_NULL(soc_isp->core_eb)) {
			pr_err("fail to read dts isp clk\n");
			return -EFAULT;
		}
		soc_isp->clk_parent = of_clk_get_by_name(isp_node, "isp_clk_parent");
		if (IS_ERR_OR_NULL(soc_isp->core_eb)) {
			pr_err("fail to read dts isp clk parent\n");
			return -EFAULT;
		}
		soc_isp->clk_default = clk_get_parent(soc_isp->clk);

		iommu_node = of_parse_phandle(isp_node, "iommus", 0);
		if (iommu_node) {
			if (of_address_to_resource(iommu_node, 1, &res))
				pr_err("fail to get ISP IOMMU addr\n");
			else {
				reg_base = ioremap(res.start, res.end - res.start + 1);
				if (!reg_base)
					pr_err("fail to map ISP IOMMU base\n");
				else
					s_isp_mmubase = (unsigned long)reg_base;
			}
		}
		pr_info("ISP IOMMU Base  0x%lx\n", s_isp_mmubase);

		/* qos dt parse */
		qos_node = of_parse_phandle(isp_node, "isp_qos", 0);
		if (qos_node) {
			uint8_t val;

			if (of_property_read_u8(qos_node, "awqos-high", &val)) {
				pr_warn("isp awqos-high reading fail.\n");
				val = 7;
			}
			soc_isp->awqos_high = (uint32_t)val;
			if (of_property_read_u8(qos_node, "awqos-low", &val)) {
				pr_warn("isp awqos-low reading fail.\n");
				val = 6;
			}
			soc_isp->awqos_low = (uint32_t)val;
			if (of_property_read_u8(qos_node, "arqos-high", &val)) {
				pr_warn("isp arqos-high reading fail.\n");
				val = 7;
			}
			soc_isp->arqos_high = (uint32_t)val;
			if (of_property_read_u8(qos_node, "arqos-low", &val)) {
				pr_warn("isp arqos-low reading fail.\n");
				val = 6;
			}
			soc_isp->arqos_low = (uint32_t)val;
			pr_info("get isp qos node. r: %d %d w: %d %d\n",
				soc_isp->arqos_high, soc_isp->arqos_low,
				soc_isp->awqos_high, soc_isp->awqos_low);
		} else {
			soc_isp->awqos_high = 7;
			soc_isp->awqos_low = 6;
			soc_isp->arqos_high = 7;
			soc_isp->arqos_low = 6;
		}

		soc_isp->cam_ahb_gpr = syscon_regmap_lookup_by_phandle(isp_node,
			"sprd,cam-ahb-syscon");
		if (IS_ERR_OR_NULL(soc_isp->cam_ahb_gpr)) {
			pr_err("fail to get sprd,cam-ahb-syscon");
			return PTR_ERR(soc_isp->cam_ahb_gpr);
		}

		args_count = syscon_get_args_by_name(isp_node, "reset",
			sizeof(args), args);
		if (args_count == ARRAY_SIZE(args)) {
			ip_isp->syscon.rst = args[0];
			ip_isp->syscon.rst_mask = args[1];
		} else {
			pr_err("fail to get isp reset syscon\n");
			return -EINVAL;
		}

		args_count = syscon_get_args_by_name(isp_node, "isp_ahb_reset",
			sizeof(args), args);
		if (args_count == ARRAY_SIZE(args))
			ip_isp->syscon.rst_ahb_mask = args[1];

		args_count = syscon_get_args_by_name(isp_node, "isp_vau_reset",
			sizeof(args), args);
		if (args_count == ARRAY_SIZE(args))
			ip_isp->syscon.rst_vau_mask = args[1];

		if (of_address_to_resource(isp_node, i, &res))
			pr_err("fail to get isp phys addr\n");

		ip_isp->phy_base = (unsigned long)res.start;
		isp_phys_base[0] = ip_isp->phy_base;
		pr_info("isp phys reg base is %lx\n", isp_phys_base[0]);
		reg_base = of_iomap(isp_node, i);
		if (!reg_base) {
			pr_err("fail to get isp reg_base %d\n", i);
			return -ENXIO;
		}

		ip_isp->reg_base = (unsigned long)reg_base;
		s_isp_regbase[0] = ip_isp->reg_base;

		for (i = 0; i < ISP_LOGICAL_COUNT; i++) {
			s_isp_irq_no[i] = irq_of_parse_and_map(isp_node, i);
			if (s_isp_irq_no[i] <= 0) {
				pr_err("fail to get isp irq %d\n", i);
				return -EFAULT;
			}

			pr_info("ISP%d dts OK! regbase %lx, irq %d\n", i,
				s_isp_regbase[0],  s_isp_irq_no[i]);
		}
	} else {
		pr_err("fail to match isp device node\n");
		return -EINVAL;
	}

	return 0;
}

/*
 * Copyright (C) 2019-2020 Unisoc Communications Inc.
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
#include <linux/regmap.h>
#include <linux/spinlock.h>
#include <sprd_mm.h>

#include "cam_trusty.h"
#include "dcam_reg.h"
#include "defines.h"
#include "dcam_int.h"
#include "dcam_path.h"
#include "isp_reg.h"
#include "isp_core.h"
#include "isp_int.h"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "CAM_HW_IF_L3: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

#define DCAMX_STOP_TIMEOUT              2000
#define DCAM_AXI_STOP_TIMEOUT           2000
#define DCAM_AXIM_AQOS_MASK             0x30FFFF
#define ISP_AXI_STOP_TIMEOUT            1000
#define ISP_AXI_ARBITER_WQOS_MASK       0x37FF
#define ISP_AXI_ARBITER_RQOS_MASK       0x1FF

/*
.* pdaf bypass is bit3 of DCAM_CFG
.* 4in1 bypass is bit12 of DCAM_MIPI_CAP_CFG
.* blc bypass is bit18 of DCAM_MIPI_CAP_CFG
.*/
#define DCAM_PDAF_BYPASS_CTRL          DCAM_CFG
#define DCAM_4IN1_BYPASS_CTRL          DCAM_MIPI_CAP_CFG
#define DCAM_BLC_BYPASS_CTRL           DCAM_MIPI_CAP_CFG

static atomic_t clk_users;
static unsigned long irq_base[4] = {
	ISP_P0_INT_BASE,
	ISP_C0_INT_BASE,
	ISP_P1_INT_BASE,
	ISP_C1_INT_BASE
};

static const struct bypass_tag sharkl3_dcam_bypass_tab[] = {
	[_E_4IN1] = {"4in1", DCAM_4IN1_BYPASS_CTRL, 12}, /* 0x100.b12 */
	[_E_PDAF] = {"pdaf", DCAM_PDAF_BYPASS_CTRL, 3}, /* 0x008.b3 */
	[_E_LSC]  = {"lsc", DCAM_LENS_LOAD_ENABLE, 0}, /* 0x138.b0 */
	[_E_AEM]  = {"aem",  DCAM_AEM_FRM_CTRL0, 0}, /* 0x150.b0 */
	[_E_AFL]  = {"afl",  ISP_AFL_FRM_CTRL, 0}, /* 0x170.b0 */
	[_E_AFM]  = {"afm",  ISP_AFM_FRM_CTRL, 0}, /* 0x1A0.b0 */
	[_E_BPC]  = {"bpc",  ISP_BPC_PARAM, 0}, /* 0x200.b0 */
	[_E_BLC]  = {"blc",  DCAM_BLC_BYPASS_CTRL, 18}, /* 0x100.b18 */
	[_E_RGB]  = {"rgb",  ISP_RGBG_PARAM, 0}, /* 0x22c.b0 rgb gain */
	[_E_RAND] = {"rand", ISP_RGBG_YRANDOM_PARAMETER0, 0}, /* 0x238.b0 */
	[_E_AWBC] = {"awbc", ISP_AWBC_GAIN0, 31}, /* 0x380.b31 */
	[_E_NR3]  = {"nr3",  NR3_FAST_ME_PARAM, 0}, /* 0x3F0.b0 */
	[_E_GRGB] = {"grgb", DCAM_GRGB_CTRL, 0}, /* 0x120.b1 */
};

static const struct bypass_tag sharkl3_isp_bypass_tab[] = {
[_EISP_NLM] =      {"nlm",       ISP_NLM_PARA, 0, 1},
[_EISP_VST] =      {"vst",       ISP_VST_PARA, 0, 1},
[_EISP_IVST] =     {"ivst",      ISP_IVST_PARA, 0, 1},
[_EISP_CFA] =      {"cfa",       ISP_CFAE_NEW_CFG0, 0, 1},
[_EISP_CMC] =      {"cmc",       ISP_CMC10_PARAM, 0, 1},
[_EISP_GAMC] =     {"gamma-c",   ISP_GAMMA_PARAM, 0, 1}, /* Gamma correction */
[_EISP_HSV] =      {"hsv",       ISP_HSV_PARAM, 0, 1},
[_EISP_HIST] =    {"hist",     ISP_HIST_PARAM, 0, 1},
[_EISP_HIST2] =    {"hist2",     ISP_HIST2_PARAM, 0, 1},
[_EISP_PSTRZ] =    {"pstrz",     ISP_PSTRZ_PARAM, 0, 1},
[_EISP_PRECDN] =   {"precdn",    ISP_PRECDN_PARAM, 0, 1},
[_EISP_YNR] =      {"ynr",       ISP_YNR_CONTRL0, 0, 1},
[_EISP_EE] =       {"ee",        ISP_EE_PARAM, 0, 1},
[_EISP_GAMY] =     {"ygamma",    ISP_YGAMMA_PARAM, 0, 1},
[_EISP_CDN] =      {"cdn",       ISP_CDN_PARAM, 0, 1},
[_EISP_POSTCDN] =  {"postcdn",   ISP_POSTCDN_COMMON_CTRL, 0, 1},
[_EISP_UVD] =      {"uvd",       ISP_UVD_PARAM, 0, 1},
[_EISP_IIRCNR] =   {"iircnr",    ISP_IIRCNR_PARAM, 0, 1},
[_EISP_YRAND] =    {"yrandom",   ISP_YRANDOM_PARAM1, 0, 1},
[_EISP_CONTRAST] =    {"contrast",   ISP_CONTRAST_PARAM, 0, 1},
[_EISP_BRIGHT] =    {"brightness",   ISP_BRIGHT_PARAM, 0, 1},
[_EISP_SATURATION] =    {"saturation",   ISP_CSA_PARAM, 0, 1},
[_EISP_HUE] =    {"hue",   ISP_HUA_PARAM, 0, 1},
[_EISP_YUVNF] =    {"yuvnf",     ISP_YUV_NF_CTRL, 0, 1},

	{"ydelay",    ISP_YDELAY_PARAM, 0, 1},
	{"cce",    ISP_CCE_PARAM, 0, 0},
	/* can't bypass when prev */
	{"scale-pre", ISP_SCALER_PRE_CAP_BASE + ISP_SCALER_CFG, 20, 0},
	{"store-pre", ISP_STORE_PRE_CAP_BASE + ISP_STORE_PARAM, 0, 0},

	{"scale-vid", ISP_SCALER_VID_BASE + ISP_SCALER_CFG, 20, 1},
	{"store-vid", ISP_STORE_VID_BASE + ISP_STORE_PARAM, 0, 1},

	/* 3dnr/nr3 */
	{"nr3-crop",  ISP_3DNR_MEM_CTRL_PRE_PARAM0, 0, 1},
	{"nr3-store", ISP_3DNR_STORE_PARAM, 0, 1},
	{"nr3-mem",   ISP_3DNR_MEM_CTRL_PARAM0, 0, 1},

	{"fetch",     ISP_FETCH_PARAM, 0, 0},
	{"cfg",       ISP_CFG_PAMATER, 0, 0},
};

static uint32_t sharkl3_cam_bypass_count_get(enum cam_bypass_type type)
{
	uint32_t cnt = 0;

	switch (type) {
	case DCAM_BYPASS_TYPE:
		cnt = sizeof(sharkl3_dcam_bypass_tab) /
			sizeof(sharkl3_dcam_bypass_tab[0]);
		break;
	case ISP_BYPASS_TYPE:
		cnt = sizeof(sharkl3_isp_bypass_tab) /
			sizeof(sharkl3_isp_bypass_tab[0]);
		break;
	default:
		pr_err("fail to support bypass type %d\n", type);
		break;
	}

	if (cnt == 0)
		pr_err("fail to get valid bypass %d\n", type);

	return cnt;
}

static struct bypass_tag *sharkl3_cam_bypass_data_get(uint32_t i,
	enum cam_bypass_type type)
{
	struct bypass_tag *bypass = NULL;

	switch (type) {
	case DCAM_BYPASS_TYPE:
		bypass = (struct bypass_tag *)&sharkl3_dcam_bypass_tab[i];
		break;
	case ISP_BYPASS_TYPE:
		bypass = (struct bypass_tag *)&sharkl3_isp_bypass_tab[i];
		break;
	default:
		pr_err("fail to support bypass type %d\n", type);
		break;
	}

	if (bypass == NULL)
		pr_err("fail to get valid block func %d\n", type);

	return bypass;
}

static uint32_t sharkl3_cam_reg_trace_tab[] = {
		DCAM_CFG,
		DCAM_APB_SRAM_CTRL,
		DCAM_IMAGE_CONTROL,
		DCAM_PDAF_CONTROL,
		DCAM_LENS_LOAD_ENABLE,
		ISP_BPC_PARAM,
		DCAM_AEM_FRM_CTRL0,
		ISP_AFM_FRM_CTRL,
		ISP_AFL_FRM_CTRL,
		NR3_FAST_ME_PARAM,
		DCAM_FULL_BASE_WADDR,
		DCAM_BIN_BASE_WADDR0,
		DCAM_PDAF_BASE_WADDR,
		DCAM_VCH2_BASE_WADDR,
		DCAM_VCH3_BASE_WADDR,
		DCAM_AEM_BASE_WADDR,
		ISP_AFL_GLB_WADDR,
		ISP_AFL_REGION_WADDR,
		ISP_BPC_OUT_ADDR,
		ISP_AFM_BASE_WADDR,
		ISP_NR3_WADDR,
};

static void sharkl3_cam_reg_trace(uint32_t idx,
	enum cam_reg_trace_type type)
{
	unsigned long addr = 0;
	uint32_t val_mmu, val[8], i, j, n, cnt;

	if (type == NORMAL_REG_TRACE) {
		goto normal_reg_trace;
	} else if (type == ABNORMAL_REG_TRACE) {
		goto abnormal_reg_trace;
	} else {
		pr_err("fail to get valid type %d\n", type);
	}

abnormal_reg_trace:
	pr_info("DCAM%d: Register list\n", idx);
	for (addr = DCAM_IP_REVISION; addr <= ISP_AFL_SUM2;
		addr += 16) {
		pr_info("0x%03lx: 0x%x 0x%x 0x%x 0x%x\n",
			addr,
			DCAM_REG_RD(idx, addr),
			DCAM_REG_RD(idx, addr + 4),
			DCAM_REG_RD(idx, addr + 8),
			DCAM_REG_RD(idx, addr + 12));
	}
	pr_info("AXIM: Register list\n");
	for (addr = AXIM_CTRL; addr <= IMG_FETCH_RADDR;
		addr += 16) {
		pr_info("0x%03lx: 0x%x 0x%x 0x%x 0x%x\n",
			addr,
			DCAM_AXIM_RD(addr),
			DCAM_AXIM_RD(addr + 4),
			DCAM_AXIM_RD(addr + 8),
			DCAM_AXIM_RD(addr + 12));
	}

	for (addr = ISP_INT_EN0; addr <= ISP_INT_ALL_DONE_SRC_CTRL;
		addr += 16) {
		pr_info("0x%lx: 0x%x 0x%x 0x%x 0x%x\n",
			addr,
			ISP_HREG_RD(addr),
			ISP_HREG_RD(addr + 4),
			ISP_HREG_RD(addr + 8),
			ISP_HREG_RD(addr + 12));
	}

normal_reg_trace:
	val_mmu = DCAM_MMU_RD(MMU_EN);
	cnt = sizeof(sharkl3_cam_reg_trace_tab) /
		sizeof(sharkl3_cam_reg_trace_tab[0]);
	pr_info("dcam%d: 0x%08x, cnt %d\n", idx, val_mmu, cnt);

	for (i = 0; i < cnt; i += 8) {
		memset(val, 0, sizeof(val));
		n = ((cnt - i) < 8) ? (cnt - i) : 8;
		for (j = 0; j < n; j++) {
			addr = sharkl3_cam_reg_trace_tab[i + j];
			val[j] = DCAM_REG_RD(idx, addr);
		}
		pr_info("n=%d, %08x %08x %08x %08x %08x %08x %08x %08x\n", n,
			val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7]);
	}
}

static int sharkl3_dcam_clk_eb(struct cam_hw_soc_info *hw)
{
	int ret = 0;

	pr_debug(", E\n");
	if (atomic_inc_return(&clk_users) != 1) {
		pr_info("clk has enabled, users: %d\n",
			atomic_read(&clk_users));
		return 0;
	}

	if (!hw) {
		pr_err("fail to get invalid hw\n");
		return -EINVAL;
	}
	ret = clk_set_parent(hw->clk, hw->clk_parent);
	if (ret) {
		pr_err("fail to set clk parent\n");
		clk_set_parent(hw->clk, hw->clk_default);
		return ret;
	}
	ret = clk_prepare_enable(hw->clk);
	if (ret) {
		pr_err("fail to enable clk\n");
		clk_set_parent(hw->clk, hw->clk_default);
		return ret;
	}

	ret = clk_set_parent(hw->bpc_clk, hw->bpc_clk_parent);
	if (ret) {
		pr_err("fail to set bpc_clk parent\n");
		clk_set_parent(hw->bpc_clk, hw->bpc_clk_parent);
		return ret;
	}
	ret = clk_prepare_enable(hw->bpc_clk);
	if (ret) {
		pr_err("fail to enable bpc_clk\n");
		clk_set_parent(hw->bpc_clk, hw->bpc_clk_default);
		return ret;
	}

	ret = clk_prepare_enable(hw->core_eb);
	if (ret) {
		pr_err("fail to set eb\n");
		clk_disable_unprepare(hw->clk);
		return ret;
	}
	ret = clk_prepare_enable(hw->axi_eb);
	if (ret) {
		pr_err("fail to set dcam axi clk\n");
		clk_disable_unprepare(hw->clk);
		clk_disable_unprepare(hw->core_eb);
	}

	return ret;
}

static int sharkl3_dcam_clk_dis(struct cam_hw_soc_info *hw)
{
	int ret = 0;

	pr_debug(", E\n");
	if (atomic_dec_return(&clk_users) != 0) {
		pr_info("Other using, users: %d\n",
			atomic_read(&clk_users));
		return 0;
	}

	if (!hw) {
		pr_err("fail to get invalid hw\n");
		return -EINVAL;
	}
	clk_set_parent(hw->bpc_clk, hw->bpc_clk_default);
	clk_disable_unprepare(hw->bpc_clk);
	clk_set_parent(hw->clk, hw->clk_default);
	clk_disable_unprepare(hw->clk);
	clk_disable_unprepare(hw->axi_eb);
	clk_disable_unprepare(hw->core_eb);

	return ret;
}

static int sharkl3_dcam_clk_update(struct cam_hw_soc_info *hw, void *arg)
{
	int ret = 0;

	pr_debug(", E\n");
	pr_warn("Not support and no use, now\n");

	return ret;
}

static void sharkl3_dcam_axi_init(void *arg)
{
	uint32_t time_out = 0;
	struct dcam_pipe_dev *dev = NULL;
	struct cam_hw_soc_info *soc = NULL;
	struct cam_hw_ip_info *ip = NULL;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return;
	}

	dev = (struct dcam_pipe_dev *)arg;
	soc = dev->hw->soc_dcam;
	ip = dev->hw->ip_dcam[dev->idx];
	/* firstly, stop AXI writing. */
	DCAM_AXIM_MWR(AXIM_CTRL, BIT_24 | BIT_23, (0x3 << 23));

	/* then wait for AHB busy cleared */
	while (++time_out < DCAM_AXI_STOP_TIMEOUT) {
		if (0 == (DCAM_AXIM_RD(AXIM_DBG_STS) & 0x1F00F))
			break;
		udelay(1000);
	}

	if (time_out >= DCAM_AXI_STOP_TIMEOUT) {
		pr_warn("fail to dcam axim timeout status 0x%x\n",
			DCAM_AXIM_RD(AXIM_DBG_STS));
	} else {
		/* reset dcam all (0/1/2/bus) */
		regmap_update_bits(soc->cam_ahb_gpr, ip->syscon.all_rst,
			ip->syscon.all_rst_mask, ip->syscon.all_rst_mask);
		udelay(10);
		regmap_update_bits(soc->cam_ahb_gpr, ip->syscon.all_rst,
			ip->syscon.all_rst_mask, ~(ip->syscon.all_rst_mask));
	}

	/* AXIM shared by all dcam, should be init once only...*/
	dcam_aximreg_set_default_value();
	dev->hw->hw_ops.dcam_soc_ops.qos_set(soc);

	/* the end, enable AXI writing */
	DCAM_AXIM_MWR(AXIM_CTRL, BIT_24 | BIT_23, (0x0 << 23));
}

static void sharkl3_dcam_qos_set(struct cam_hw_soc_info *hw)
{
	uint32_t reg_val = 0;

	if (!hw) {
		pr_err("fail to get invalid hw\n");
		return;
	}

	reg_val = (0x0 << 20) | ((hw->arqos_low & 0xF) << 12) | (0x8 << 8) |
		((hw->awqos_high & 0xF) << 4) | (hw->awqos_low & 0xF);
	REG_MWR(hw->axi_reg_base + AXIM_CTRL, DCAM_AXIM_AQOS_MASK, reg_val);
}

static int sharkl3_dcam_start(void *arg)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;
	uint32_t idx = 0;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)arg;
	idx = dev->idx;

	DCAM_REG_WR(idx, DCAM_INT_CLR, 0xFFFFFFFF);
	/* see DCAM_PREVIEW_SOF in dcam_int.h for details */
	DCAM_REG_WR(idx, DCAM_INT_EN, DCAMINT_IRQ_LINE_EN_NORMAL);
	/* trigger cap_en*/
	DCAM_REG_MWR(idx, DCAM_CFG, BIT_0, 1);

	return ret;
}

static int sharkl3_dcam_stop(void *arg)
{
	int ret = 0;
	int time_out = DCAMX_STOP_TIMEOUT;
	struct dcam_pipe_dev *dev = NULL;
	uint32_t idx = 0;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)arg;
	idx = dev->idx;

	DCAM_REG_MWR(idx, DCAM_PATH_STOP, 0x3F, 0x3F);
	udelay(1000);
	DCAM_REG_MWR(idx, DCAM_CFG, 0x3F, 0);

	DCAM_REG_WR(idx, DCAM_INT_EN, 0);
	DCAM_REG_WR(idx, DCAM_INT_CLR, 0xFFFFFFFF);

	/* wait for AHB path busy cleared */
	while (time_out) {
		ret = DCAM_REG_RD(idx, DCAM_PATH_BUSY) & 0xFFF;
		if (!ret)
			break;
		udelay(1000);
		time_out--;
	}

	if (time_out == 0)
		pr_err("fail to stop:DCAM%d: stop timeout for 2s\n", idx);

	pr_info("dcam%d stop end\n", idx);
	return ret;
}

static int sharkl3_dcam_cap_disable(void *arg)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;
	uint32_t idx = 0;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)arg;
	idx = dev->idx;

	/* stop  cap_en*/
	DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_0, 0);
	return ret;
}

static void sharkl3_dcam_auto_copy(uint32_t id, void *arg)
{
	struct dcam_pipe_dev *dev = NULL;
	const uint32_t bitmap[] = {
		BIT_5, BIT_7, BIT_9, BIT_11, BIT_13, BIT_15, BIT_17, BIT_19
	};
	const uint32_t bitmap2 = BIT_5;
	uint32_t mask = 0, j;
	unsigned long flags = 0;

	if (unlikely(!arg)) {
		pr_err("fail to get valid arg\n");
		return;
	}

	dev = (struct dcam_pipe_dev *)arg;
	if (dev->idx < 2) {
		for (j = 0; j < 8; j++) {
			if (id & (1 << j))
				mask |= bitmap[j];
		}
	} else if (id && DCAM_CTRL_CAP) {
		mask = bitmap2;
	}

	pr_debug("DCAM%u: auto copy 0x%0x, id 0x%x\n", dev->idx, mask, id);
	if (mask == 0)
		return;

	spin_lock_irqsave(&dev->glb_reg_lock, flags);
	DCAM_REG_MWR(dev->idx, DCAM_CONTROL, mask, mask);
	spin_unlock_irqrestore(&dev->glb_reg_lock, flags);
}

static void sharkl3_dcam_force_copy(uint32_t id, void *arg)
{
	struct dcam_pipe_dev *dev = NULL;
	const uint32_t bitmap[] = {
		BIT_4, BIT_6, BIT_8, BIT_10, BIT_12, BIT_14, BIT_16, BIT_18
	};
	const uint32_t bitmap2 = BIT_4;
	uint32_t mask = 0, j;
	unsigned long flags = 0;

	if (unlikely(!arg)) {
		pr_warn("invalid param dev\n");
		return;
	}

	dev = (struct dcam_pipe_dev *)arg;
	if (dev->idx < 2) {
		for (j = 0; j < 8; j++) {
			if (id & (1 << j))
				mask |= bitmap[j];
		}
	} else if (id && DCAM_CTRL_CAP) {
		mask = bitmap2;
	}
	pr_debug("DCAM%u: force copy 0x%0x, id 0x%x\n", dev->idx, mask, id);
	if (mask == 0)
		return;

	spin_lock_irqsave(&dev->glb_reg_lock, flags);
	DCAM_REG_MWR(dev->idx, DCAM_CONTROL, mask, mask);
	spin_unlock_irqrestore(&dev->glb_reg_lock, flags);
}


static int sharkl3_dcam_reset(struct cam_hw_info *hw, void *arg)
{
	int ret = 0;
	int i = 0;
	enum dcam_id idx = 0;
	struct cam_hw_soc_info *soc = NULL;
	struct cam_hw_ip_info *ip = NULL;
	uint32_t bypass, eb;

	if (!hw || !arg) {
		pr_err("fail to get input para\n");
		return -EFAULT;
	}

	idx = *(uint32_t *)arg;
	soc = hw->soc_dcam;
	ip = hw->ip_dcam[idx];

	regmap_update_bits(soc->cam_ahb_gpr, ip->syscon.rst,
		ip->syscon.rst_mask, ip->syscon.rst_mask);
	udelay(1);
	regmap_update_bits(soc->cam_ahb_gpr, ip->syscon.rst,
		ip->syscon.rst_mask, ~(ip->syscon.rst_mask));

	for (i = 0x200; i < 0x400; i += 4)
		DCAM_REG_WR(idx, i, 0);

	DCAM_REG_MWR(idx, DCAM_INT_CLR,
		DCAMINT_IRQ_LINE_MASK, DCAMINT_IRQ_LINE_MASK);
	DCAM_REG_MWR(idx, DCAM_INT_EN,
		DCAMINT_IRQ_LINE_MASK, DCAMINT_IRQ_LINE_MASK);

	/* init registers(sram regs) to default value */
	dcam_reg_set_default_value(idx);
	/* disable internal logic access sram */
	DCAM_REG_MWR(idx, DCAM_APB_SRAM_CTRL, BIT_0, 0);

	DCAM_REG_WR(idx, DCAM_CFG, 0); /* disable all path */
	if (idx != DCAM_ID_2)
		DCAM_REG_WR(idx, DCAM_IMAGE_CONTROL, 0x2b << 8 | 0x01);
	else
		DCAM_REG_WR(idx, DCAM2_IMAGE_CONTROL, 0x2b << 8 | 0x01);

	eb = 0;
	DCAM_REG_MWR(idx, DCAM_PDAF_CONTROL, BIT_1 | BIT_0, eb);
	DCAM_REG_MWR(idx, DCAM_CROP0_START, BIT_31, eb << 31);

	/* default bypass all blocks */
	bypass = 1;
	DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_18, bypass << 18);
	DCAM_REG_MWR(idx, ISP_RGBG_YRANDOM_PARAMETER0, BIT_0, bypass);
	DCAM_REG_MWR(idx, DCAM_LENS_LOAD_ENABLE, BIT_0, bypass);
	DCAM_REG_MWR(idx, ISP_AWBC_PARAM, BIT_0, bypass);
	DCAM_REG_MWR(idx, ISP_BPC_PARAM, 0xF, 0xF); /*bpc bypass all */
	DCAM_REG_MWR(idx, ISP_AFL_PARAM0, BIT_1, bypass << 1); /*bayer2y*/
	DCAM_REG_MWR(idx, ISP_BPC_GC_CFG, 0x7, 6);
	DCAM_REG_MWR(idx, ISP_BPC_PARAM, 0x0F, 0xF);
	DCAM_REG_MWR(idx, DCAM_GRGB_CTRL, BIT_0, 1);
	DCAM_REG_MWR(idx, ISP_RGBG_PARAM, BIT_0, 1);

	/* 3A statistic */
	DCAM_REG_MWR(idx, DCAM_AEM_FRM_CTRL0, BIT_0, bypass);
	DCAM_REG_MWR(idx, ISP_AFM_FRM_CTRL, BIT_0, bypass);
	DCAM_REG_MWR(idx, ISP_AFL_FRM_CTRL, BIT_0, bypass);
	DCAM_REG_MWR(idx, NR3_FAST_ME_PARAM, BIT_0, bypass);
	DCAM_REG_MWR(idx, DCAM_CFG, 0x3F, 0);

	pr_info("DCAM%d: reset end\n", idx);

	return ret;
}

static int sharkl3_dcam_fetch_set(void *arg)
{
	int ret = 0;
	uint32_t fetch_pitch;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_fetch_info *fetch = NULL;

	pr_debug("enter.\n");

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)arg;
	fetch = &dev->fetch;
	/* !0 is loose */
	if (fetch->is_loose != 0) {
		fetch_pitch = fetch->size.w * 2;
	} else {
		/* to bytes */
		fetch_pitch = (fetch->size.w + 3) / 4 * 5;
		/* bytes align 32b */
		fetch_pitch = (fetch_pitch + 3) & (~0x3);
	}
	pr_info("size [%d %d], start %d, pitch %d, 0x%x\n",
		fetch->trim.size_x, fetch->trim.size_y,
		fetch->trim.start_x, fetch_pitch, fetch->addr.addr_ch0);
	/* (bitfile)unit 32b,(spec)64b */

	DCAM_REG_MWR(dev->idx, DCAM_INT_CLR,
		DCAMINT_IRQ_LINE_MASK, DCAMINT_IRQ_LINE_MASK);
	DCAM_REG_MWR(dev->idx, DCAM_INT_EN,
		DCAMINT_IRQ_LINE_MASK, DCAMINT_IRQ_LINE_MASK);
	DCAM_AXIM_MWR(IMG_FETCH_CTRL, 0x0F << 12, 0x0F << 12);
	DCAM_AXIM_MWR(IMG_FETCH_CTRL, 0xFF << 4, 0xFF << 4);
	fetch_pitch /= 4;
	DCAM_REG_MWR(dev->idx, DCAM_MIPI_CAP_CFG, 0x7, 0x3);
	DCAM_REG_MWR(dev->idx, DCAM_MIPI_CAP_CFG,
		BIT_17 | BIT_16, (fetch->pattern & 3) << 16);
	DCAM_AXIM_MWR(IMG_FETCH_CTRL, BIT_1, fetch->is_loose << 1);
	DCAM_AXIM_MWR(IMG_FETCH_CTRL, BIT_3 | BIT_2, fetch->endian << 2);
	DCAM_AXIM_WR(IMG_FETCH_SIZE,
		(fetch->trim.size_y << 16) | (fetch->trim.size_x & 0xffff));
	DCAM_AXIM_WR(IMG_FETCH_X,
		(fetch_pitch << 16) | (fetch->trim.start_x & 0xffff));
	DCAM_REG_WR(dev->idx, DCAM_MIPI_CAP_START, 0);
	DCAM_REG_WR(dev->idx, DCAM_MIPI_CAP_END,
		((fetch->trim.size_y - 1) << 16) | (fetch->trim.size_x - 1));
	DCAM_AXIM_WR(IMG_FETCH_RADDR, fetch->addr.addr_ch0);

	return ret;
}

int sharkl3_dcam_slice_fetch_set(void *arg)
{
	int ret = 0;
	uint32_t fetch_pitch;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_fetch_info *fetch = NULL;
	uint32_t reg_val;

	if (!arg)
		pr_err("fail to check param");

	dev = (struct dcam_pipe_dev *)arg;
	fetch = &dev->fetch;
	/* !0 is loose */
	if (fetch->is_loose != 0) {
		fetch_pitch = fetch->size.w * 2;
	} else {
		/* to bytes */
		fetch_pitch = (fetch->size.w + 3) / 4 * 5;
		/* bytes align 32b */
		fetch_pitch = (fetch_pitch + 3) & (~0x3);
	}
	pr_debug("size [%d %d], start [%d %d], pitch %d, 0x%x\n",
		fetch->trim.size_x, fetch->trim.size_y,
		fetch->trim.start_x, fetch->trim.start_y,
		fetch_pitch, fetch->addr.addr_ch0);
	fetch_pitch /= 4;
	DCAM_AXIM_MWR(IMG_FETCH_CTRL, BIT_16, BIT_16);
	DCAM_REG_MWR(dev->idx, DCAM_MIPI_CAP_CFG, 0x7, 0x3);
	DCAM_REG_MWR(dev->idx, DCAM_MIPI_CAP_CFG,
		BIT_17 | BIT_16, (fetch->pattern & 3) << 16);

	DCAM_AXIM_MWR(IMG_FETCH_CTRL,
		BIT_1, fetch->is_loose << 1);
	DCAM_AXIM_MWR(IMG_FETCH_CTRL,
		BIT_3 | BIT_2, fetch->endian << 2);
	DCAM_AXIM_MWR(IMG_FETCH_CTRL,
		0xFF << 8, 0x01 << 8);
	DCAM_AXIM_MWR(IMG_FETCH_CTRL,
		0x0F << 12, 0x01 << 12);

	DCAM_AXIM_WR(IMG_FETCH_SIZE,
		(fetch->trim.size_y << 16) | (fetch->trim.size_x & 0x3fff));
	DCAM_AXIM_WR(IMG_FETCH_X,
		(fetch_pitch << 16) | (fetch->trim.start_x & 0x3fff));

	DCAM_REG_WR(dev->idx, DCAM_MIPI_CAP_START, 0);
	DCAM_REG_WR(dev->idx, DCAM_MIPI_CAP_END,
		((fetch->trim.size_y - 1) << 16) | (fetch->trim.size_x - 1));

	DCAM_AXIM_WR(IMG_FETCH_RADDR, fetch->addr.addr_ch0);

	DCAM_REG_WR(dev->idx, DCAM_CAM_BIN_CFG, BIT_5 | BIT_4);

	reg_val = (0 << 16) | dev->slice_trim.start_x;
	DCAM_REG_WR(dev->idx, DCAM_CROP0_START, reg_val);
	reg_val = (dev->slice_trim.size_y << 17) | dev->slice_trim.size_x;
	DCAM_REG_WR(dev->idx, DCAM_CROP0_X, reg_val);

	return ret;
}

static int sharkl3_dcam_fetch_block_set(void *arg)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;

	pr_debug("enter.\n");

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)arg;
	if (DCAM_FIRST_FETCH(dev)) {
		pr_debug("fetch: 1st  only open BLC & Rgb_gain & yrandom\n");

		DCAM_REG_MWR(dev->idx,
			DCAM_MIPI_CAP_CFG, BIT_18, ~BIT_18);
		DCAM_REG_MWR(dev->idx,
			ISP_RGBG_PARAM, BIT_0, ~BIT_0);
		DCAM_REG_MWR(dev->idx,
			ISP_RGBG_YRANDOM_PARAMETER0, BIT_0, ~BIT_0);

		DCAM_REG_MWR(dev->idx, DCAM_LENS_LOAD_ENABLE, BIT_0, BIT_0);
		DCAM_REG_MWR(dev->idx, ISP_AWBC_PARAM, BIT_0, BIT_0);
		DCAM_REG_MWR(dev->idx, ISP_BPC_PARAM, 0x0F, 0x0F);
		DCAM_REG_MWR(dev->idx, DCAM_GRGB_CTRL, BIT_0, BIT_0);
	} else {
		pr_debug("fetch: 2nd  close BLC & Rgb_gain & yrandom, open other sublock\n");
		DCAM_REG_MWR(dev->idx,
			DCAM_MIPI_CAP_CFG, BIT_18, BIT_18);
		DCAM_REG_MWR(dev->idx,
			ISP_RGBG_PARAM, BIT_0, BIT_0);
		DCAM_REG_MWR(dev->idx,
			ISP_RGBG_PARAM, 0xFFFF << 16, 0xFFFF << 16);
		DCAM_REG_MWR(dev->idx,
			ISP_RGBG_YRANDOM_PARAMETER0, BIT_0, BIT_0);

		DCAM_REG_MWR(dev->idx,
			DCAM_LENS_LOAD_ENABLE, BIT_0, ~BIT_0);
		DCAM_REG_MWR(dev->idx, ISP_AWBC_PARAM, BIT_0, ~BIT_0);
		DCAM_REG_MWR(dev->idx, ISP_BPC_PARAM, 0x0F, 0x0);
		DCAM_REG_MWR(dev->idx, DCAM_GRGB_CTRL, BIT_0, ~BIT_0);
	}

	return ret;
}

static int sharkl3_dcam_mipi_cap_set(void *arg)
{
	int ret = 0;
	uint32_t idx = 0;
	uint32_t reg_val;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_mipi_info *cap_info = NULL;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)arg;
	cap_info = &dev->cap_info;
	idx = dev->idx;

	/* set mipi interface  */
	if (cap_info->sensor_if != DCAM_CAP_IF_CSI2) {
		pr_err("fail to supported sensor if : %d\n",
			cap_info->sensor_if);
		return -EINVAL;
	}

	/* data format */
	if (cap_info->format == DCAM_CAP_MODE_RAWRGB) {
		DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_1, 1 << 1);
		DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_17 | BIT_16,
				cap_info->pattern << 16);
	} else if (cap_info->format == DCAM_CAP_MODE_YUV) {
		if (unlikely(cap_info->data_bits != DCAM_CAP_8_BITS)) {
			pr_err("fail to get valid %d bits for yuv format\n",
				cap_info->data_bits);
			return -EINVAL;
		}

		DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_1,  0 << 1);
		DCAM_REG_MWR(idx, DCAM_MIPI_CAP_FRM_CTRL,
				BIT_1 | BIT_0, cap_info->pattern);

		/* x & y deci */
		DCAM_REG_MWR(idx, DCAM_MIPI_CAP_FRM_CTRL,
				BIT_9 | BIT_8 | BIT_5 | BIT_4,
				(cap_info->y_factor << 8)
				| (cap_info->x_factor << 4));
	} else {
		pr_err("fail to supported capture format: %d\n",
			cap_info->format);
		return -EINVAL;
	}

	/* data mode */
	DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_2, cap_info->mode << 2);

	/* href */
	DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_3, cap_info->href << 3);

	/* data bits */
	if (cap_info->data_bits == DCAM_CAP_12_BITS) {
		reg_val = 2;
	} else if (cap_info->data_bits == DCAM_CAP_10_BITS) {
		reg_val = 1;
	} else if (cap_info->data_bits == DCAM_CAP_8_BITS) {
		reg_val = 0;
	} else {
		pr_err("fail to supported data bits: %d\n",
			cap_info->data_bits);
		return -EINVAL;
	}
	DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_5 | BIT_4, reg_val << 4);

	/* frame deci */
	DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_7 | BIT_6,
			cap_info->frm_deci << 6);

	/* MIPI capture start */
	reg_val = (cap_info->cap_size.start_y << 16);
	reg_val |= cap_info->cap_size.start_x;
	if (idx != DCAM_ID_2)
		DCAM_REG_WR(idx, DCAM_MIPI_CAP_START, reg_val);
	else
		DCAM_REG_WR(idx, DCAM2_MIPI_CAP_START, reg_val);

	/* MIPI capture end */
	reg_val = (cap_info->cap_size.start_y
			+ cap_info->cap_size.size_y - 1) << 16;
	reg_val |= (cap_info->cap_size.start_x
			+ cap_info->cap_size.size_x - 1);
	if (idx != DCAM_ID_2)
		DCAM_REG_WR(idx, DCAM_MIPI_CAP_END, reg_val);
	else
		DCAM_REG_WR(idx, DCAM2_MIPI_CAP_END, reg_val);

	/* frame skip before capture */
	DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG,
			BIT_8 | BIT_9 | BIT_10 | BIT_11,
				cap_info->frm_skip << 8);

	/* bypass 4in1 */
	if (cap_info->is_4in1) /* 4in1 use sum, not avrg */
		DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_13,
				(!!cap_info->is_4in1) << 13);
	DCAM_REG_MWR(idx, DCAM_MIPI_CAP_CFG, BIT_12,
			(!cap_info->is_4in1) << 12);

	pr_info("mipi_cap: size %d, %d, %d, %d\n",
		cap_info->cap_size.start_x, cap_info->cap_size.start_y,
		cap_info->cap_size.size_x, cap_info->cap_size.size_y);
	pr_info("mipi_cap: frm %d, mode %d, bits %d, pattern %d, href %d\n",
		cap_info->format, cap_info->mode, cap_info->data_bits,
		cap_info->pattern, cap_info->href);
	pr_info("mipi_cap: deci %d, skip %d, x %d, y %d, 4in1 %d\n",
		cap_info->frm_deci, cap_info->frm_skip, cap_info->x_factor,
		cap_info->y_factor, cap_info->is_4in1);

	return ret;
}

static int sharkl3_dcam_path_start(void *handle, uint32_t path_id)
{
	int ret = 0;
	uint32_t idx;
	uint32_t value;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_path_desc *path = NULL;
	struct isp_img_rect rect; /* for 3dnr */

	pr_debug("enter.");

	if (!handle) {
		pr_err("fail to get input ptr.\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)handle;
	path = &dev->path[path_id];
	idx = dev->idx;

	switch (path_id) {
	case  DCAM_PATH_FULL:

		DCAM_REG_MWR(idx, DCAM_PATH_ENDIAN,
			BIT_17 |  BIT_16, path->endian.y_endian << 16);

		DCAM_REG_MWR(idx, DCAM_FULL_CFG, BIT_0, path->is_loose);
		DCAM_REG_MWR(idx, DCAM_FULL_CFG, BIT_2, path->src_sel << 2);

		/* full_path_en */
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_1, (1 << 1));
		break;


	case  DCAM_PATH_BIN:
		DCAM_REG_MWR(idx, DCAM_PATH_ENDIAN,
			BIT_19 |  BIT_18, path->endian.y_endian << 18);

		DCAM_REG_MWR(idx,
			DCAM_CAM_BIN_CFG, BIT_0, path->is_loose);

		value = (dev->slowmotion_count << 1) | !!dev->slowmotion_count;
		DCAM_REG_WR(idx, DCAM_MODE, value & 0xf);

		/* bin_path_en */
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_2, (1 << 2));
		break;
	case DCAM_PATH_PDAF:
		/* pdaf path en */
		if (dev->is_pdaf)
			DCAM_REG_MWR(idx, DCAM_CFG, BIT_3, (1 << 3));
		break;

	case DCAM_PATH_VCH2:
		/* data type for raw picture */
		if (path->src_sel)
			DCAM_REG_WR(idx, DCAM_VC2_CONTROL, 0x2b << 8 | 0x01);

		DCAM_REG_MWR(idx, DCAM_PATH_ENDIAN,
			BIT_23 |  BIT_22, path->endian.y_endian << 22);

		/*vch2 path en */
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_4, (1 << 4));
		break;

	case DCAM_PATH_VCH3:
		DCAM_REG_MWR(idx, DCAM_PATH_ENDIAN,
			BIT_25 |  BIT_24, path->endian.y_endian << 24);
		/*vch3 path en */
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_5, (1 << 5));
		break;
	case DCAM_PATH_3DNR:
		/*
		 * set default value for 3DNR
		 * nr3_mv_bypass: 0
		 * nr3_channel_sel: 0
		 * nr3_project_mode: 0
		 * nr3_sub_me_bypass: 0x1
		 * nr3_out_en: 0
		 * nr3_ping_pong_en: 0
		 * nr3_bypass: 0
		 */
		rect.x = path->in_trim.start_x;
		rect.y = path->in_trim.start_y;
		rect.w = path->in_trim.size_x;
		rect.h = path->in_trim.size_y;
		if (dev->cap_info.cap_size.size_x < (rect.x + rect.w) ||
			dev->cap_info.cap_size.size_y < (rect.y + rect.h)) {
			pr_err("fail to get dcam 3dnr input rect [%d %d %d %d]\n",
				rect.x, rect.y, rect.w, rect.h);
			break;
		}
		DCAM_REG_WR(idx, NR3_FAST_ME_PARAM, 0x8);
		dcam_k_3dnr_set_roi(rect,
				0/* project_mode=0 */, idx);
		break;
	default:
		break;
	}

	pr_debug("done\n");
	return ret;
}

static int sharkl3_dcam_path_stop(void *handle, uint32_t path_id)
{
	int ret = 0;
	uint32_t idx;
	uint32_t reg_val;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_path_desc *path = NULL;

	pr_debug("enter.");

	if (!handle) {
		pr_err("fail to get valid handle\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)handle;
	path = &dev->path[path_id];
	idx = dev->idx;

	switch (path_id) {
	case  DCAM_PATH_FULL:
		reg_val = 0;
		DCAM_REG_MWR(idx, DCAM_PATH_STOP, BIT_0, 1);
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_1, (0 << 1));
		break;
	case  DCAM_PATH_BIN:
		DCAM_REG_MWR(idx, DCAM_PATH_STOP, BIT_1, 1 << 1);
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_2, (0 << 2));
		break;
	case  DCAM_PATH_PDAF:
		DCAM_REG_MWR(idx, DCAM_PATH_STOP, BIT_3, 1 << 3);
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_3, (0 << 3));
		break;
	case  DCAM_PATH_VCH2:
		DCAM_REG_MWR(idx, DCAM_PATH_STOP, BIT_4, 1 << 4);
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_4, (0 << 4));
		break;

	case  DCAM_PATH_VCH3:
		DCAM_REG_MWR(idx, DCAM_PATH_STOP, BIT_5, 1 << 5);
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_5, (0 << 5));
		break;
	default:
		break;
	}

	pr_debug("done\n");
	return ret;
}

static int sharkl3_dcam_path_pause(uint32_t idx, uint32_t path_id)
{
	switch (path_id) {
	case DCAM_PATH_FULL:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_1, (0 << 1));
		break;
	case DCAM_PATH_BIN:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_2, (0 << 2));
		break;
	case DCAM_PATH_PDAF:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_3, (0 << 3));
		break;
	case DCAM_PATH_VCH2:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_4, (0 << 4));
		break;
	case DCAM_PATH_VCH3:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_5, (0 << 5));
		break;
	default:
		break;
	}

	return 0;
}

static int sharkl3_dcam_path_resume(uint32_t idx, uint32_t path_id)
{
	switch (path_id) {
	case DCAM_PATH_FULL:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_1, (1 << 1));
		break;
	case DCAM_PATH_BIN:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_2, (1 << 2));
		break;
	case DCAM_PATH_PDAF:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_3, (1 << 3));
		break;
	case DCAM_PATH_VCH2:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_4, (1 << 4));
		break;
	case DCAM_PATH_VCH3:
		DCAM_REG_MWR(idx, DCAM_CFG, BIT_5, (1 << 5));
		break;
	default:
		break;
	}

	return 0;
}

static void sharkl3_dcam_fetch_start(struct cam_hw_info *hw)
{
	if (!hw) {
		pr_err("fail to get invalid hw\n");
		return;
	}

	DCAM_AXIM_MWR(IMG_FETCH_CTRL, BIT_16, 0 << 16);
	DCAM_AXIM_WR(IMG_FETCH_START, 1);
}

static int sharkl3_dcam_path_size_update(void *handle, void *arg)
{
	int ret = 0;
	uint32_t idx;
	uint32_t path_id;
	uint32_t reg_val;
	struct dcam_pipe_dev *dev = NULL;
	struct dcam_path_desc *path = NULL;
	struct dcam_path_desc *path_3dnr = NULL;
	struct isp_img_rect rect; /* for 3dnr path */

	pr_debug("enter.");

	if (!handle || !arg) {
		pr_err("fail to get valid handle\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)handle;
	path = (struct dcam_path_desc *)arg;
	idx = dev->idx;
	path_id = path->path_id;

	switch (path_id) {
	case  DCAM_PATH_FULL:
		if ((path->in_size.w > path->in_trim.size_x) ||
			(path->in_size.h > path->in_trim.size_y)) {
			DCAM_REG_MWR(idx, DCAM_FULL_CFG, BIT_1, 1 << 1);
			reg_val = (path->in_trim.start_y << 16) |
						path->in_trim.start_x;
			DCAM_REG_WR(idx, DCAM_FULL_CROP_START, reg_val);
			reg_val = (path->in_trim.size_y << 16) |
						path->in_trim.size_x;
			DCAM_REG_WR(idx, DCAM_FULL_CROP_SIZE, reg_val);

		} else {
			DCAM_REG_MWR(idx, DCAM_FULL_CFG, BIT_1, 0 << 1);
		}
		break;
	case  DCAM_PATH_BIN:

		DCAM_REG_MWR(idx, DCAM_CAM_BIN_CFG,
			BIT_2, path->bin_ratio << 2);
		DCAM_REG_MWR(idx, DCAM_CAM_BIN_CFG, BIT_3,
			(path->scaler_sel & 1) << 3);
		DCAM_REG_MWR(idx, DCAM_CAM_BIN_CFG, BIT_5,
			(path->scaler_sel >> 1) << 5);
		/* set size to path[DCAM_PATH_3DNR]
		 * because, 3dnr set roi need know bin path crop size
		 * 3dnr end_y should <= bin crop.end_y
		 */
		path_3dnr = &dev->path[DCAM_PATH_3DNR];
		path_3dnr->in_trim = path->in_trim;
		path_3dnr->in_size = path->in_size;
		if ((path->in_size.w > path->in_trim.size_x) ||
			(path->in_size.h > path->in_trim.size_y)) {

			reg_val = (path->in_trim.start_y << 16) |
						path->in_trim.start_x;
			DCAM_REG_WR(idx, DCAM_BIN_CROP_START, reg_val);
			DCAM_REG_MWR(idx, DCAM_CAM_BIN_CFG, BIT_1, 1 << 1);

			reg_val = (path->in_trim.size_y << 16) |
						path->in_trim.size_x;
			DCAM_REG_WR(idx, DCAM_BIN_CROP_SIZE, reg_val);
		} else {
			/* bypass trim */
			DCAM_REG_MWR(idx, DCAM_CAM_BIN_CFG, BIT_1, 0 << 1);
		}

		if (path->scaler_sel == DCAM_SCALER_RAW_DOWNSISER) {
			uint32_t cnt;
			uint32_t *ptr = (uint32_t *)path->rds_coeff_buf;
			unsigned long addr = RDS_COEF_TABLE_START;

			for (cnt = 0; cnt < path->rds_coeff_size;
				cnt += 4, addr += 4)
				DCAM_REG_WR(idx, addr, *ptr++);

			reg_val = ((path->out_size.h & 0xfff) << 16) |
						(path->out_size.w & 0x1fff);
			DCAM_REG_WR(idx, DCAM_RDS_DES_SIZE, reg_val);
			dev->auto_cpy_id |= DCAM_CTRL_RDS;
		}
		break;
	case DCAM_PATH_3DNR:
		/* reset when zoom */
		rect.x = path->in_trim.start_x;
		rect.y = path->in_trim.start_y;
		rect.w = path->in_trim.size_x;
		rect.h = path->in_trim.size_y;
		if (dev->cap_info.cap_size.size_x < (rect.x + rect.w) ||
			dev->cap_info.cap_size.size_y < (rect.y + rect.h)) {
			pr_err("fail to get dcam 3dnr input rect[%d %d %d %d]\n",
				rect.x, rect.y, rect.w, rect.h);
			break;
		}
		dcam_k_3dnr_set_roi(rect,
				0/* project_mode=0 */, idx);
		break;
	default:
		break;
	}

	pr_debug("done\n");
	return ret;
}

static int sharkl3_dcam_full_path_src_sel(void *handle,
	enum dcam_full_src_sel_type src_sel)
{
	int ret = 0;
	struct dcam_pipe_dev *dev = NULL;

	if (!handle) {
		pr_err("fail to get valid handle\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)handle;

	switch (src_sel) {
	case ORI_RAW_SRC_SEL:
		DCAM_REG_MWR(dev->idx, DCAM_FULL_CFG, BIT(2), 0);
		break;
	case PROCESS_RAW_SRC_SEL:
		DCAM_REG_MWR(dev->idx, DCAM_FULL_CFG, BIT(2), BIT(2));
		break;
	default:
		pr_err("fail to support src_sel %d\n", src_sel);
		ret = -EINVAL;
		break;
	}

	return ret;
}

static int sharkl3_dcam_ebd_set(uint32_t idx, void *arg)
{
	struct sprd_ebd_control *p = NULL;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	p = (struct sprd_ebd_control *)arg;
	DCAM_REG_WR(idx, DCAM_VC2_CONTROL,
		((p->image_vc & 0x3) << 16) |
		((p->image_dt & 0x3F) << 8) |
		(p->mode & 0x3));

	return 0;
}

static int sharkl3_dcam_binning_4in1_set(void *arg, int binning_4in1_en)
{
	struct dcam_pipe_dev *dev = NULL;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)arg;
	if (binning_4in1_en) {
		DCAM_REG_MWR(dev->idx, DCAM_MIPI_CAP_CFG, BIT_13, BIT_13);
		DCAM_REG_MWR(dev->idx, DCAM_MIPI_CAP_CFG, BIT_12, 0 << 12);
	} else {
		DCAM_REG_MWR(dev->idx, DCAM_MIPI_CAP_CFG, BIT_13, BIT_13);
		DCAM_REG_MWR(dev->idx, DCAM_MIPI_CAP_CFG, BIT_12, BIT_12);
	}
	return 0;
}

static int sharkl3_dcam_sram_ctrl_set(void *arg, int sram_ctrl_en)
{
	struct dcam_pipe_dev *dev = NULL;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return -EFAULT;
	}

	dev = (struct dcam_pipe_dev *)arg;
	if (sram_ctrl_en)
		DCAM_REG_MWR(dev->idx, DCAM_APB_SRAM_CTRL, BIT_0, 1);
	else
		DCAM_REG_MWR(dev->idx, DCAM_APB_SRAM_CTRL, BIT_0, 0);

	return 0;
}

static int sharkl3_isp_clk_eb(struct cam_hw_soc_info *hw)
{
	int ret = 0;

	pr_debug(",E\n");
	if (!hw) {
		pr_err("fail to get invalid hw\n");
		return -EINVAL;
	}

	ret = clk_set_parent(hw->clk, hw->clk_parent);
	if (ret) {
		pr_err("fail to set parent, ret = %d\n", ret);
		clk_set_parent(hw->clk, hw->clk_default);
		return ret;
	}
	ret = clk_prepare_enable(hw->clk);
	if (ret) {
		pr_err("fail to enable isp clk, ret = %d\n", ret);
		clk_set_parent(hw->clk, hw->clk_default);
		return ret;
	}
	ret = clk_prepare_enable(hw->core_eb);
	if (ret) {
		pr_err("fail to set isp eb, ret = %d\n", ret);
		clk_disable_unprepare(hw->clk);
		return ret;
	}
	ret = clk_prepare_enable(hw->axi_eb);
	if (ret) {
		pr_err("fail to set isp axi eb, ret = %d\n", ret);
		clk_disable_unprepare(hw->clk);
		clk_disable_unprepare(hw->core_eb);
		return ret;
	}

	return ret;
}

static int sharkl3_isp_clk_dis(struct cam_hw_soc_info *hw)
{
	int ret = 0;
	pr_debug(",E\n");
	if (!hw) {
		pr_err("fail to get valid hw\n");
		return -EINVAL;
	}

	clk_set_parent(hw->clk, hw->clk_default);
	clk_disable_unprepare(hw->clk);
	clk_disable_unprepare(hw->axi_eb);
	clk_disable_unprepare(hw->core_eb);

	return ret;
}

static int sharkl3_isp_clk_update(struct cam_hw_soc_info *hw, void *arg)
{
	int ret = 0;

	pr_debug(",E\n");
	if (!hw) {
		pr_err("fail to get valid hw\n");
		return -EINVAL;
	}

	pr_warn("Not support and no use, now\n");

	return ret;
}

static int sharkl3_isp_reset(struct cam_hw_info *hw, void *arg)
{
	int rtn = 0;
	uint32_t cid;
	uint32_t time_out = 0;
	struct cam_hw_soc_info *soc = NULL;
	struct cam_hw_ip_info *ip = NULL;

	if (!hw) {
		pr_err("fail to get valid hw\n");
		return -EINVAL;
	}

	soc = hw->soc_isp;
	ip = hw->ip_isp;

	/* firstly stop axim transfering */
	ISP_HREG_MWR(ISP_AXI_ITI2AXIM_CTRL, BIT(26), BIT(26));

	/* then wait for AHB busy cleared */
	while (++time_out < ISP_AXI_STOP_TIMEOUT) {
		/* bit3: 1 - axi idle;  0 - axi busy */
		if  (ISP_HREG_RD(ISP_INT_STATUS) & BIT_3)
			break;
		udelay(1000);
	}

	if (time_out >= ISP_AXI_STOP_TIMEOUT) {
		pr_warn("fail to isp reset timeout %d\n", time_out);
	} else {
		regmap_update_bits(soc->cam_ahb_gpr,
			ip->syscon.rst, ip->syscon.rst_mask, ip->syscon.rst_mask);
		udelay(10);
		regmap_update_bits(soc->cam_ahb_gpr,
			ip->syscon.rst, ip->syscon.rst_mask, ~(ip->syscon.rst_mask));
	}

	/* enable axim transfering */
	ISP_HREG_MWR(ISP_AXI_ITI2AXIM_CTRL, BIT_26, 0);

	for (cid = 0; cid < 4; cid++) {
		hw->hw_ops.isp_irq_ops.irq_clear(ip, &cid);
		hw->hw_ops.isp_irq_ops.irq_disable(ip, &cid);
	}

	pr_info("ISP%d: reset end\n", ip->idx);
	return rtn;
}

int sharkl3_isp_irq_enable(struct cam_hw_ip_info *hw, void *arg)
{
	uint32_t ctx_id;
	uint32_t mask = ~0;

	if (!hw || !arg) {
		pr_err("fail to get valid hw\n");
		return -EFAULT;
	}

	ctx_id = *(uint32_t *)arg;
	if (ctx_id >= 4) {
		pr_err("fail to get right ctx id %d\n", ctx_id);
		return -EFAULT;
	}
	if (ctx_id != ISP_CONTEXT_HW_C0)
		mask &= ~ISP_INT_LINE_FMCU_MASK;

	ISP_HREG_MWR(irq_base[ctx_id] + ISP_INT_EN0, mask, mask);

	return 0;
}

int sharkl3_isp_irq_disable(struct cam_hw_ip_info *hw, void *arg)
{
	uint32_t ctx_id;

	if (!hw || !arg) {
		pr_err("fail to get valid hw\n");
		return -EFAULT;
	}

	ctx_id = *(uint32_t *)arg;
	if (ctx_id >= 4) {
		pr_err("fail to get ctx id %d\n", ctx_id);
		return -EFAULT;
	}

	ISP_HREG_WR(irq_base[ctx_id] + ISP_INT_EN0, 0);
	ISP_HREG_WR(irq_base[ctx_id] + ISP_INT_EN1, 0);

	return 0;
}

int sharkl3_isp_irq_clear(struct cam_hw_ip_info *hw, void *arg)
{
	uint32_t ctx_id;

	if (!hw || !arg) {
		pr_err("fail to get valid hw\n");
		return -EFAULT;
	}

	ctx_id = *(uint32_t *)arg;
	if (ctx_id >= 4) {
		pr_err("fail to get ctx id %d\n", ctx_id);
		return -EFAULT;
	}

	ISP_HREG_WR(irq_base[ctx_id] + ISP_INT_CLR0, 0xFFFFFFFF);
	ISP_HREG_WR(irq_base[ctx_id] + ISP_INT_CLR1, 0xFFFFFFFF);

	return 0;
}

static uint32_t ISP_CFG_MAP[] __aligned(8) = {
	0x00080710, /*0x0710  - 0x0714 , 2   , common path sel*/
	0x00041C10, /*0x1C10  - 0x1C10 , 1   , VST*/
	0x01702010,/*0x2010  - 0x217C , 92  , NLM*/
	0x00041E10, /*0x1E10  - 0x1E10 , 1   , IVST*/
	0x00503010,/*0x3010  - 0x305C , 20  , CFA_NEW*/
	0x00183110, /*0x3110  - 0x3124 , 6   , CMC10*/
	0x00043210, /*0x3210  - 0x3210 , 1   , GAMC_NEW*/
	0x00403310,/*0x3310  - 0x334C , 16  , HSV*/
	0x00243410,/*0x3410  - 0x3430 , 9   , PSTRZ*/
	0x001C3510,/*0x3510  - 0x3528 , 7   , CCE*/
	0x001C3610,/*0x3610  - 0x3628 , 7   , UVD*/
	0x004C5010,/*0x5010  - 0x5058 , 19  , PRECDN*/
	0x00845110,/*0x5110  - 0x5190 , 33  , YNR*/
	0x00045210,/*0x5210  - 0x5210 , 1   , BRTA*/
	0x00045310,/*0x5310  - 0x5310 , 1   , CNTA*/
	0x000C5410,/*0x5410  - 0x5418 , 3   , HISTS*/
	0x00145510,/*0x5510  - 0x5520 , 5   , HISTS2*/
	0x00485610,/*0x5610  - 0x5654 , 18  , CDN*/
	0x00745710,/*0x5710  - 0x5780 , 29  , NEW_EE*/
	0x00045810,/*0x5810  - 0x5810 , 1   , CSA*/
	0x00045910,/*0x5910  - 0x5910 , 1   , HUA*/
	0x00745A10,/*0x5A10  - 0x5A80 , 29  , POST_CDN*/
	0x00045B10,/*0x5B10  - 0x5B10 , 1   , YGAMMA*/
	0x00085C10,/*0x5C10  - 0x5C14 , 2   , YUVDELAY*/
	0x00C85D10,/*0x5D10  - 0x5DD4 , 50  , IIRCNR*/
	0x00185E10,/*0x5E10  - 0x5E24 , 6   , YRANDOM*/
	0x00449010,/*0x9010  - 0x9050 , 17   , 3DNR mem ctrl*/
	0x00649110,/*0x9110  - 0x9170 , 25   , 3DNR blend*/
	0x00189210,/*0x9210  - 0x9224 , 6   , 3DNR store*/
	0x00109310,/*0x9310  - 0x931C , 4   , 3DNR crop*/
	0x0050D010,/*0xD010  - 0xD05C , 20  , SCL_VID*/
	0x0034D110,/*0xD110  - 0xD140 , 13  , SCL_VID_store*/
	0x0044C010,/*0xC010  - 0xC050 , 17  , SCL_CAP*/
	0x0034C110,/*0xC110  - 0xC140 , 13  , SCL_CAP_store*/
	0x0044C210,/*0xC210  - 0xC250 , 17  ,SCL_CAP_noisefilter*/
	0x00300110, /*0x110   - 0x13C  , 12  , FETCH*/
	0x00300210, /*0x210   - 0x23C  , 12  , STORE*/
	0x001C0310, /*0x310   - 0x328  , 7   , DISPATCH*/
	0x05A18000,/*0x18000 - 0x1859C, 360 , ISP_HSV_BUF0_CH0*/
	0x10019000,/*0x19000 - 0x19FFC, 1024, ISP_VST_BUF0_CH0*/
	0x1001A000,/*0x1A000 - 0x1AFFC, 1024, ISP_IVST_BUF0_CH0*/
	0x0401B000,/*0x1B000 - 0x1B3FC, 256 , ISP_FGAMMA_R_BUF0_CH0*/
	0x0401C000,/*0x1C000 - 0x1C3FC, 256 , ISP_FGAMMA_G_BUF0_CH0*/
	0x0401D000,/*0x1D000 - 0x1D3FC, 256 , ISP_FGAMMA_B_BUF0_CH0*/
	0x0205E000,/*0x1E000 - 0x1E200, 129 , ISP_YGAMMA_BUF0_CH0*/
	0x00839100, /*0x39100 - 0x3917C, 32  , CAP_HOR_CORF_Y_BUF0_CH0*/
	0x00439300, /*0x39300 - 0x3933C, 16  , CAP_HOR_CORF_UV_BUF0*/
	0x021394F0, /*0x394F0 - 0x396FC, 132 , CAP_VER_CORF_Y_BUF0_CH0*/
	0x02139AF0, /*0x39AF0 - 0x39CFC, 132 , CAP_VER_CORF_UV_BUF0*/
	0x00838100, /*0x38100 - 0x3817C, 32  , VID_HOR_CORF_Y_BUF0_CH0*/
	0x00438300, /*0x38300 - 0x3833C, 16  , VID_HOR_CORF_UV_BUF0*/
	0x021384F0, /*0x384F0 - 0x386FC, 132 , VID_VER_CORF_Y_BUF0_CH0*/
	0x02138AF0, /*0x38AF0 - 0x38CFC, 132 , VID_VER_CORF_UV_BUF0*/
};

uint32_t *sharkl3_isp_cfg_map_info_get(void *arg)
{
	if (!arg) {
		pr_err("fail to get valid arg\n");
		return NULL;
	}

	*(uint32_t *)arg = ARRAY_SIZE(ISP_CFG_MAP);

	return ISP_CFG_MAP;
}

void sharkl3_isp_default_param_set(struct cam_hw_info *hw,
	void *arg, enum isp_default_type type)
{
	uint32_t idx = 0;
	uint32_t bypass = 1;
	uint32_t wqos_val = 0;
	uint32_t rqos_val = 0;

	if (type == ISP_HW_PARA) {
		goto isp_hw_para;
	} else if (type == ISP_CFG_PARA && arg) {
		idx = *(uint32_t *)arg;
		goto isp_cfg_para;
	} else {
		pr_err("fail to get valid type %d\n", type);
	}

isp_hw_para:
	ISP_HREG_MWR(ISP_AXI_ITI2AXIM_CTRL, 0xFF00, 1 << 8);
	wqos_val = (0x1 << 13) | (0x0 << 12) | (0x4 << 8) | (0x6 << 4) | 0x6;
	rqos_val = (0x0 << 8) | (0x6 << 4) | 0x6;
	ISP_HREG_MWR(ISP_AXI_ARBITER_WQOS,
		ISP_AXI_ARBITER_WQOS_MASK, wqos_val);
	ISP_HREG_MWR(ISP_AXI_ARBITER_RQOS,
		ISP_AXI_ARBITER_RQOS_MASK, rqos_val);
	ISP_HREG_WR(ISP_CORE_PMU_EN, 0xFFFF0000);
	ISP_HREG_WR(ISP_COMMON_GCLK_CTRL_0, 0xFFFF0000);
	ISP_HREG_WR(ISP_COMMON_GCLK_CTRL_1, 0xFFFF0000);
	ISP_HREG_WR(ISP_COMMON_GCLK_CTRL_2, 0xFFFF0000);
	ISP_HREG_WR(ISP_COMMON_GCLK_CTRL_3, 0xFF00);
	ISP_HREG_MWR(ISP_AXI_ISOLATION, BIT_0, 0);
	ISP_HREG_MWR(ISP_ARBITER_ENDIAN0, BIT_0, 0);
	ISP_HREG_MWR(ISP_ARBITER_ENDIAN1, BIT(0) | BIT(1), 0);
	ISP_HREG_WR(ISP_ARBITER_CHK_SUM_CLR, 0xF10);
	ISP_HREG_WR(ISP_ARBITER_CHK_SUM0, 0x0);
	/* enable axim transfering */
	ISP_HREG_MWR(ISP_AXI_ITI2AXIM_CTRL, BIT_26, 0);
	/* to be defined. */
	ISP_HREG_MWR(
		ISP_COMMON_SHADOW_CTRL_CH0, BIT_16, (1 << 16));
	ISP_HREG_MWR(
		ISP_COMMON_SHADOW_CTRL_CH0, BIT_21, (0 << 21));
	ISP_HREG_MWR(ISP_COMMON_PMU_RAM_MASK, BIT_0, 1);
	ISP_HREG_MWR(ISP_BLOCK_MODE, 0xF, 0);
	/* dispatch_done should be disable? */
	ISP_HREG_MWR(ISP_INT_ALL_DONE_CTRL, 0x1F, 0x1C);
	/* bypass config mode by default */
	ISP_HREG_MWR(ISP_CFG_PAMATER, BIT_0, 1);
	return;

isp_cfg_para:
	ISP_REG_MWR(idx, ISP_STORE_DEBUG_BASE + ISP_STORE_PARAM,
		BIT_0, bypass);
	/* bypass all path scaler & store */
	ISP_REG_MWR(idx, ISP_SCALER_PRE_CAP_BASE + ISP_SCALER_CFG,
		BIT_31, 0 << 31);
	ISP_REG_MWR(idx, ISP_SCALER_VID_BASE + ISP_SCALER_CFG,
		BIT_31, 0 << 31);

	ISP_REG_MWR(idx, ISP_STORE_PRE_CAP_BASE + ISP_STORE_PARAM,
		BIT_0, 1);
	ISP_REG_MWR(idx, ISP_STORE_VID_BASE + ISP_STORE_PARAM,
		BIT_0, 1);
	ISP_REG_MWR(idx, ISP_STORE_THUMB_BASE + ISP_STORE_PARAM,
		BIT_0, 1);

	/* default bypass all blocks */
	ISP_REG_MWR(idx, ISP_NLM_PARA, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_VST_PARA, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_IVST_PARA, BIT_0, bypass);

	ISP_REG_MWR(idx, ISP_CMC10_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_GAMMA_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_HSV_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_PSTRZ_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_CCE_PARAM, BIT_0, bypass);

	ISP_REG_MWR(idx, ISP_UVD_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_PRECDN_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_YNR_CONTRL0, BIT_0 | BIT_1, 0x3);
	ISP_REG_MWR(idx, ISP_HIST_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_HIST_CFG_READY, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_HIST2_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_HIST2_CFG_RDY, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_CFAE_NEW_CFG0, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_EE_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_GRGB_CTRL, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_YUV_NF_CTRL, BIT_0, 1);

	ISP_REG_MWR(idx, ISP_CDN_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_EE_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_BRIGHT_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_CONTRAST_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_CSA_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_HUA_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_POSTCDN_COMMON_CTRL, BIT_0|BIT_1, 0x3);
	ISP_REG_MWR(idx, ISP_YGAMMA_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_IIRCNR_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_YRANDOM_PARAM1, BIT_0, 1);

	/* 3DNR bypass */
	ISP_REG_MWR(idx, ISP_3DNR_MEM_CTRL_PARAM0, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_3DNR_BLEND_CONTROL0, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_3DNR_STORE_PARAM, BIT_0, 1);
	ISP_REG_MWR(idx, ISP_3DNR_MEM_CTRL_PRE_PARAM0, BIT_0, 1);

	/* 10b: out put yuv data */
	ISP_REG_MWR(idx, ISP_COMMON_SPACE_SEL, BIT_3 | BIT_2, 2 << 2);
	ISP_REG_MWR(idx, ISP_COMMON_SPACE_SEL, BIT_4, 0 << 4);
	ISP_REG_MWR(idx, ISP_COMMON_SCL_PATH_SEL, BIT_8, 0 << 8);
	ISP_REG_MWR(idx, ISP_COMMON_SCL_PATH_SEL, BIT_7 | BIT_6, 3 << 6);
	ISP_REG_MWR(idx, ISP_COMMON_SCL_PATH_SEL, BIT_3 | BIT_2, 3 << 2);
	ISP_REG_MWR(idx, ISP_COMMON_SCL_PATH_SEL, BIT_1 | BIT_0, 3 << 0);

	ISP_REG_WR(idx, ISP_FETCH_LINE_DLY_CTRL, 0x8);
	ISP_REG_WR(idx, ISP_DISPATCH_DLY,  0x253C);
	ISP_REG_WR(idx, ISP_DISPATCH_LINE_DLY1,  0x280001C);
	ISP_REG_WR(idx, ISP_DISPATCH_PIPE_BUF_CTRL_CH0,  0x64043C);
	ISP_REG_WR(idx, ISP_YDELAY_STEP, 0x144);
	ISP_REG_WR(idx, ISP_SCALER_PRE_CAP_BASE + ISP_SCALER_HBLANK, 0x4040);
	ISP_REG_WR(idx, ISP_SCALER_PRE_CAP_BASE + ISP_SCALER_RES, 0xFF);
	ISP_REG_WR(idx, ISP_SCALER_PRE_CAP_BASE + ISP_SCALER_DEBUG, 1);

	/*CFA*/
	ISP_REG_MWR(idx, ISP_CFAE_NEW_CFG0, BIT_0, 0);
	ISP_REG_WR(idx, ISP_CFAE_INTP_CFG0, 0x1F4 | 0x1F4 << 16);
	ISP_REG_WR(idx, ISP_CFAE_INTP_CFG1,
		(0x1 << 31) | (0x14 << 12) | (0x7F << 4) | 0x4);
	ISP_REG_WR(idx, ISP_CFAE_INTP_CFG2, 0x8 | (0x0 << 8));
	ISP_REG_WR(idx, ISP_CFAE_INTP_CFG3,
		(0x8 << 20) | (0x8 << 12) | 0x118);
	ISP_REG_WR(idx, ISP_CFAE_INTP_CFG4, 0x64 | (0x64 << 16));
	ISP_REG_WR(idx, ISP_CFAE_INTP_CFG5, 0xC8 | (0xC8 << 16));

	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG0, 0x64 | (0x96 << 16));
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG1, 0x14 | (0x5 << 16));
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG2,
		(0x28 << 20) | (0x1E << 10) | 0xF);
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG3, 0xC8);
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG4, (0x5 << 10));
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG5, (0x50 << 9) | 0x78);
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG6,
		(0x32 << 18) | (0x32 << 9));
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG7, (0x64 << 18));
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG8, 0x3C | (0x8 << 17));
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG9,
		(0x1FC << 20) | (0x134 << 10) | 0x27C);
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG10,
		(0x214 << 20) | (0x1FF << 10) | 0x1CD);
	ISP_REG_WR(idx, ISP_CFAE_CSS_CFG11, 0x22D << 10 | 0x205);

	/*CCE*/
	ISP_REG_MWR(idx, ISP_CCE_PARAM, BIT_0, 0);
	ISP_REG_WR(idx, ISP_CCE_MATRIX0, (150 << 11) | 77);
	ISP_REG_WR(idx, ISP_CCE_MATRIX1, ((-43) << 11) | 29);
	ISP_REG_WR(idx, ISP_CCE_MATRIX2, 0x407AB);
	ISP_REG_WR(idx, ISP_CCE_MATRIX3, ((-107) << 11) | 128);
	ISP_REG_WR(idx, ISP_CCE_MATRIX4, (-21));
	ISP_REG_WR(idx, ISP_CCE_SHIFT, 0);
}

static int dcam_k_cfg_null(struct isp_io_param *param, struct dcam_dev_param *p)
{
	return 0;
}

static struct isp_cfg_entry isp_cfg_func_tab[ISP_BLOCK_TOTAL - ISP_BLOCK_BASE] = {
[ISP_BLOCK_CCE - ISP_BLOCK_BASE]	= {ISP_BLOCK_CCE, isp_k_cfg_cce},
[ISP_BLOCK_CDN - ISP_BLOCK_BASE]	= {ISP_BLOCK_CDN, isp_k_cfg_cdn},
[ISP_BLOCK_CFA - ISP_BLOCK_BASE]	= {ISP_BLOCK_CFA, isp_k_cfg_cfa},
[ISP_BLOCK_BRIGHTNESS - ISP_BLOCK_BASE]	= {ISP_BLOCK_BRIGHTNESS, isp_k_cfg_brightness},
[ISP_BLOCK_CONTRAST - ISP_BLOCK_BASE]	= {ISP_BLOCK_CONTRAST, isp_k_cfg_contrast},
[ISP_BLOCK_CSA - ISP_BLOCK_BASE]	= {ISP_BLOCK_CSA, isp_k_cfg_csa},
[ISP_BLOCK_HUE - ISP_BLOCK_BASE]	= {ISP_BLOCK_HUE, isp_k_cfg_hue},
[ISP_BLOCK_CMC - ISP_BLOCK_BASE]	= {ISP_BLOCK_CMC, isp_k_cfg_cmc10},
[ISP_BLOCK_EDGE - ISP_BLOCK_BASE]	= {ISP_BLOCK_EDGE, isp_k_cfg_edge},
[ISP_BLOCK_GAMMA - ISP_BLOCK_BASE]	= {ISP_BLOCK_GAMMA, isp_k_cfg_gamma},
[ISP_BLOCK_HIST - ISP_BLOCK_BASE]	= {ISP_BLOCK_HIST, isp_k_cfg_hist},
[ISP_BLOCK_HSV - ISP_BLOCK_BASE]	= {ISP_BLOCK_HSV, isp_k_cfg_hsv},
[ISP_BLOCK_IIRCNR - ISP_BLOCK_BASE]	= {ISP_BLOCK_IIRCNR, isp_k_cfg_iircnr},
[ISP_BLOCK_POST_CDN - ISP_BLOCK_BASE]	= {ISP_BLOCK_POST_CDN, isp_k_cfg_post_cdn},
[ISP_BLOCK_PRE_CDN - ISP_BLOCK_BASE]	= {ISP_BLOCK_PRE_CDN, isp_k_cfg_pre_cdn},
[ISP_BLOCK_PSTRZ - ISP_BLOCK_BASE]	= {ISP_BLOCK_PSTRZ, isp_k_cfg_pstrz},
[ISP_BLOCK_UVD - ISP_BLOCK_BASE]	= {ISP_BLOCK_UVD, isp_k_cfg_uvd},
[ISP_BLOCK_YGAMMA - ISP_BLOCK_BASE]	= {ISP_BLOCK_YGAMMA, isp_k_cfg_ygamma},
[ISP_BLOCK_YRANDOM - ISP_BLOCK_BASE]	= {ISP_BLOCK_YRANDOM, isp_k_cfg_yrandom},
};

static struct dcam_cfg_entry dcam_cfg_func_tab[DCAM_BLOCK_TOTAL] = {
[DCAM_BLOCK_BLC - DCAM_BLOCK_BASE]     = {DCAM_BLOCK_BLC,              dcam_k_cfg_blc},
[DCAM_BLOCK_RGBG - DCAM_BLOCK_BASE]    = {DCAM_BLOCK_RGBG,             dcam_k_cfg_rgb_gain},
[DCAM_BLOCK_RGBG_DITHER - DCAM_BLOCK_BASE] = {DCAM_BLOCK_RGBG_DITHER,  dcam_k_cfg_rgb_dither},
[DCAM_BLOCK_PDAF - DCAM_BLOCK_BASE]    = {DCAM_BLOCK_PDAF,             dcam_k_cfg_pdaf},
[DCAM_BLOCK_LSC - DCAM_BLOCK_BASE]     = {DCAM_BLOCK_LSC,              dcam_k_cfg_lsc},
[DCAM_BLOCK_AEM - DCAM_BLOCK_BASE]     = {DCAM_BLOCK_AEM,              dcam_k_cfg_aem},
[DCAM_BLOCK_AFL - DCAM_BLOCK_BASE]     = {DCAM_BLOCK_AFL,              dcam_k_cfg_afl},
[DCAM_BLOCK_AWBC - DCAM_BLOCK_BASE]    = {DCAM_BLOCK_AWBC,             dcam_k_cfg_awbc},
[DCAM_BLOCK_BPC - DCAM_BLOCK_BASE]     = {DCAM_BLOCK_BPC,              dcam_k_cfg_bpc},
[DCAM_BLOCK_GRGB - DCAM_BLOCK_BASE]     = {DCAM_BLOCK_GRGB,              dcam_k_cfg_grgb},
[DCAM_BLOCK_3DNR_ME - DCAM_BLOCK_BASE] = {DCAM_BLOCK_3DNR_ME,          dcam_k_cfg_3dnr_me},
[DCAM_BLOCK_AFM - DCAM_BLOCK_BASE]     = {DCAM_BLOCK_AFM,              dcam_k_cfg_afm},
[DCAM_BLOCK_BAYERHIST - DCAM_BLOCK_BASE] = {DCAM_BLOCK_BAYERHIST,      dcam_k_cfg_null},
};

static void *sharkl3_block_func_get(uint32_t index, enum cam_block_type type)
{
	void *block_func = NULL;

	switch (type) {
	case DCAM_BLOCK_TYPE:
		if (index < DCAM_BLOCK_TOTAL)
			block_func = &dcam_cfg_func_tab[index];
		break;
	case ISP_BLOCK_TYPE:
		if (index < (ISP_BLOCK_TOTAL - ISP_BLOCK_BASE))
			block_func = &isp_cfg_func_tab[index];
		break;
	default:
		pr_err("fail to support block type %d\n", type);
		break;
	}

	if (block_func == NULL)
		pr_err("fail to get valid block func %d\n", type);

	return block_func;
}

static uint32_t sharkl3_isp_hist_enable_get(int ctx_id)
{
	uint32_t bypass = 0;
	bypass = ISP_REG_RD(ctx_id, ISP_HIST_PARAM) & BIT_0;

	return bypass;
}

static void sharkl3_isp_fetch_set(void *arg)
{
	struct isp_pipe_context *pctx = NULL;
	uint32_t idx = 0;
	uint32_t bypass = 0;
	struct isp_fetch_info *fetch = NULL;

	if (!arg) {
		pr_err("fail to get valid arg\n");
		return;
	}

	pctx = (struct isp_pipe_context *)arg;
	fetch = &pctx->fetch;
	idx = pctx->ctx_id;
	pr_info("isp_fetch: fmt:%d,dispatch_color %d w:%d, h:%d\n",
		fetch->fetch_fmt, pctx->dispatch_color,
		fetch->in_trim.size_x, fetch->in_trim.size_y);

	ISP_REG_MWR(idx, ISP_COMMON_SPACE_SEL,
			BIT_1 | BIT_0, pctx->dispatch_color);
	ISP_REG_MWR(idx, ISP_FETCH_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_FETCH_PARAM,
			(0xF << 4), fetch->fetch_fmt << 4);
	ISP_REG_WR(idx, ISP_FETCH_MEM_SLICE_SIZE,
			fetch->in_trim.size_x | (fetch->in_trim.size_y << 16));

	pr_info("isp_fetch: isp sec mode=%d ,pitch_ch0=0x%x, 0x%x, 0x%x\n",
		pctx->dev->sec_mode,
		fetch->pitch.pitch_ch0,
		fetch->pitch.pitch_ch1,
		fetch->pitch.pitch_ch2);

	if (pctx->dev->sec_mode == SEC_SPACE_PRIORITY) {
		camca_isp_pitch_set(fetch->pitch.pitch_ch0,
			fetch->pitch.pitch_ch1,
			fetch->pitch.pitch_ch2);
	} else {
		ISP_REG_WR(idx, ISP_FETCH_SLICE_Y_PITCH, fetch->pitch.pitch_ch0);
		ISP_REG_WR(idx, ISP_FETCH_SLICE_U_PITCH, fetch->pitch.pitch_ch1);
		ISP_REG_WR(idx, ISP_FETCH_SLICE_V_PITCH, fetch->pitch.pitch_ch2);
	}

	pr_info("isp_fetch: bayer mode=%d ,mipi_word_num %d, mipi_pos %d\n",
		pctx->dispatch_bayer_mode,
		fetch->mipi_word_num, fetch->mipi_byte_rel_pos);
	ISP_REG_WR(idx, ISP_FETCH_MIPI_INFO,
		fetch->mipi_word_num | (fetch->mipi_byte_rel_pos << 16));
	ISP_REG_WR(idx, ISP_DISPATCH_CH0_SIZE,
		fetch->in_trim.size_x | (fetch->in_trim.size_y << 16));
	ISP_REG_WR(idx, ISP_DISPATCH_CH0_BAYER, pctx->dispatch_bayer_mode);
}

/* workaround: temp disable FMCU 1 for not working */
static int sharkl3_isp_fmcu_available(uint32_t fmcu_id)
{
	return (fmcu_id > 0) ? 0 : 1;
}

void sharkl3_isp_cfg_subblock(void *ctx)
{
	uint32_t idx = 0;
	uint32_t bypass = 1;
	struct isp_pipe_context *pctx = NULL;
	struct isp_fetch_info *fetch = NULL;

	pctx = (struct isp_pipe_context *)ctx;
	fetch = &pctx->fetch;
	idx = pctx->ctx_id;
	pr_debug("superzoom enter: fmt:%d, in_trim %d %d, src %d %d\n",
		fetch->fetch_fmt, fetch->in_trim.size_x, fetch->in_trim.size_y,
		fetch->src.w, fetch->src.h);

	ISP_REG_MWR(idx, ISP_COMMON_SPACE_SEL, 0x0F, 0x0A);
	ISP_REG_MWR(idx, ISP_FETCH_PARAM, (0xF << 4),
		fetch->fetch_fmt << 4);
	ISP_REG_WR(idx, ISP_FETCH_SLICE_Y_PITCH,fetch->pitch.pitch_ch0);
	ISP_REG_WR(idx, ISP_FETCH_SLICE_U_PITCH, fetch->pitch.pitch_ch1);
	ISP_REG_WR(idx, ISP_FETCH_SLICE_V_PITCH, fetch->pitch.pitch_ch2);
	ISP_REG_WR(idx, ISP_FETCH_SLICE_Y_ADDR, fetch->addr.addr_ch0);
	ISP_REG_WR(idx, ISP_FETCH_SLICE_U_ADDR, fetch->addr.addr_ch1);
	ISP_REG_WR(idx, ISP_FETCH_SLICE_V_ADDR, fetch->addr.addr_ch2);
	ISP_REG_WR(idx, ISP_FETCH_LINE_DLY_CTRL, 0x8);
	ISP_REG_WR(idx, ISP_FETCH_MEM_SLICE_SIZE,
		fetch->src.w | (fetch->src.h << 16));
	ISP_REG_WR(idx, ISP_DISPATCH_DLY,  0x253C);
	ISP_REG_WR(idx, ISP_DISPATCH_LINE_DLY1,  0x280001C);
	ISP_REG_WR(idx, ISP_DISPATCH_PIPE_BUF_CTRL_CH0,  0x64043C);
	ISP_REG_WR(idx, ISP_DISPATCH_CH0_SIZE,
		fetch->in_trim.size_x | (fetch->in_trim.size_y << 16));
	ISP_REG_WR(idx, ISP_DISPATCH_CH0_BAYER, pctx->dispatch_bayer_mode);

	pr_debug("pitch ch0 %d, ch1 %d, ch2 %d\n",
		fetch->pitch.pitch_ch0, fetch->pitch.pitch_ch1, fetch->pitch.pitch_ch2);

	/*superzoom need to bypass below sublock*/
	ISP_REG_MWR(idx, ISP_VST_PARA, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_NLM_PARA, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_IVST_PARA, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_CFAE_NEW_CFG0, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_CMC10_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_GAMMA_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_HSV_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_PSTRZ_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_CCE_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_UVD_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_3DNR_MEM_CTRL_PARAM0, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_3DNR_MEM_CTRL_LINE_MODE, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_PRECDN_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_YNR_CONTRL0, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_BRIGHT_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_CONTRAST_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_HIST_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_HIST2_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_CDN_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_POSTCDN_COMMON_CTRL, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_EE_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_YGAMMA_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_CSA_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_HUA_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_IIRCNR_PARAM, BIT_0, bypass);
	ISP_REG_MWR(idx, ISP_YRANDOM_PARAM1, BIT_0, bypass);
	ISP_HREG_MWR(ISP_YUV_MULT, BIT_31, 0);
}

static uint32_t sharkl3_path_ctrl_id[DCAM_PATH_MAX] = {
	[DCAM_PATH_FULL] = DCAM_CTRL_FULL,
	[DCAM_PATH_BIN] = DCAM_CTRL_BIN,
	[DCAM_PATH_PDAF] = DCAM_CTRL_PDAF,
	[DCAM_PATH_VCH2] = DCAM_CTRL_VCH2,
	[DCAM_PATH_VCH3] = DCAM_CTRL_VCH3,
	[DCAM_PATH_AEM] = DCAM_CTRL_AEM,
	[DCAM_PATH_AFM] = DCAM_CTRL_BIN,
	[DCAM_PATH_AFL] = DCAM_CTRL_AEM,
	[DCAM_PATH_3DNR] = DCAM_CTRL_BIN,
	[DCAM_PATH_BPC] = DCAM_CTRL_BIN,
};

static unsigned long sharkl3_dcam_store_addr[DCAM_PATH_MAX] = {
	[DCAM_PATH_FULL] = DCAM_FULL_BASE_WADDR,
	[DCAM_PATH_BIN] = DCAM_BIN_BASE_WADDR0,
	[DCAM_PATH_PDAF] = DCAM_PDAF_BASE_WADDR,
	[DCAM_PATH_VCH2] = DCAM_VCH2_BASE_WADDR,
	[DCAM_PATH_VCH3] = DCAM_VCH3_BASE_WADDR,
	[DCAM_PATH_AEM] = DCAM_AEM_BASE_WADDR,
	[DCAM_PATH_AFM] = ISP_AFM_BASE_WADDR,
	[DCAM_PATH_AFL] = ISP_AFL_GLB_WADDR,
	[DCAM_PATH_3DNR] = ISP_NR3_WADDR,
	[DCAM_PATH_BPC] = ISP_BPC_OUT_ADDR,
};

static unsigned long sharkl3_dcam2_store_addr[DCAM_PATH_MAX] = {
	[DCAM_PATH_FULL] = DCAM2_PATH0_BASE_WADDR,
	[DCAM_PATH_BIN] = DCAM2_PATH1_BASE_WADDR,
};

static uint32_t sharkl3_isp_ctx_fmcu_support[ISP_CONTEXT_HW_NUM] = {
	[ISP_CONTEXT_HW_P0] = 0,
	[ISP_CONTEXT_HW_C0] = 1,
	[ISP_CONTEXT_HW_P1] = 0,
	[ISP_CONTEXT_HW_C1] = 1,
};

static struct cam_hw_soc_info sharkl3_dcam_soc_info;
static struct cam_hw_soc_info sharkl3_isp_soc_info;
static struct cam_hw_ip_info sharkl3_dcam[DCAM_ID_MAX] = {
	[DCAM_ID_0] = {
		.slm_path = BIT(DCAM_PATH_BIN),
		.lbuf_share_support = 0,
		.offline_slice_support = 0,
		.afl_gbuf_size = STATIS_AFL_GBUF_SIZE3,
		.superzoom_support = 0,
		.dcam_full_fbc_mode = DCAM_FBC_DISABLE,
		.dcam_bin_fbc_mode = DCAM_FBC_DISABLE,
		.store_addr_tab = sharkl3_dcam_store_addr,
		.path_ctrl_id_tab = sharkl3_path_ctrl_id,
		.pdaf_type3_reg_addr = DCAM_VCH2_BASE_WADDR,
	},
	[DCAM_ID_1] = {
		.slm_path = BIT(DCAM_PATH_BIN),
		.lbuf_share_support = 0,
		.offline_slice_support = 0,
		.afl_gbuf_size = STATIS_AFL_GBUF_SIZE3,
		.superzoom_support = 0,
		.dcam_full_fbc_mode = DCAM_FBC_DISABLE,
		.dcam_bin_fbc_mode = DCAM_FBC_DISABLE,
		.store_addr_tab = sharkl3_dcam_store_addr,
		.path_ctrl_id_tab = sharkl3_path_ctrl_id,
		.pdaf_type3_reg_addr = DCAM_VCH2_BASE_WADDR,
	},
	[DCAM_ID_2] = {
		.slm_path = 0,
		.lbuf_share_support = 0,
		.offline_slice_support = 0,
		.afl_gbuf_size = STATIS_AFL_GBUF_SIZE3,
		.superzoom_support = 0,
		.dcam_full_fbc_mode = DCAM_FBC_DISABLE,
		.dcam_bin_fbc_mode = DCAM_FBC_DISABLE,
		.store_addr_tab = sharkl3_dcam2_store_addr,
		.path_ctrl_id_tab = sharkl3_path_ctrl_id,
		.pdaf_type3_reg_addr = DCAM_VCH2_BASE_WADDR,
	},
};

static struct cam_hw_ip_info sharkl3_isp = {
	.slm_cfg_support = 0,
	.ctx_fmcu_support = sharkl3_isp_ctx_fmcu_support,
};

struct cam_hw_info sharkl3_hw_info = {
	.prj_id = SHARKL3,
	.pdev = NULL,
	.soc_dcam = &sharkl3_dcam_soc_info,
	.soc_isp = &sharkl3_isp_soc_info,
	.ip_dcam[DCAM_ID_0] = &sharkl3_dcam[DCAM_ID_0],
	.ip_dcam[DCAM_ID_1] = &sharkl3_dcam[DCAM_ID_1],
	.ip_dcam[DCAM_ID_2] = &sharkl3_dcam[DCAM_ID_2],
	.ip_isp = &sharkl3_isp,
	.hw_ops = {
		.dcam_soc_ops = {
			.clk_enable = sharkl3_dcam_clk_eb,
			.clk_disable = sharkl3_dcam_clk_dis,
			.clk_update = sharkl3_dcam_clk_update,
			.axi_init = sharkl3_dcam_axi_init,
			.qos_set = sharkl3_dcam_qos_set,
			.reset = sharkl3_dcam_reset,
		},
		.isp_soc_ops = {
			.clk_enable = sharkl3_isp_clk_eb,
			.clk_disable = sharkl3_isp_clk_dis,
			.clk_update = sharkl3_isp_clk_update,
			.axi_init = NULL,
			.qos_set = NULL,
			.reset = sharkl3_isp_reset,
		},
		.dcam_irq_ops = {
			.irq_request = NULL,
			.irq_free = NULL,
			.irq_enable = NULL,
			.irq_disable = NULL,
			.irq_clear = NULL,
			.irq_proc = NULL,
		},
		.isp_irq_ops = {
			.irq_request = NULL,
			.irq_free = NULL,
			.irq_enable = sharkl3_isp_irq_enable,
			.irq_disable = sharkl3_isp_irq_disable,
			.irq_clear = sharkl3_isp_irq_clear,
			.irq_proc = NULL,
		},
		.core_ops = {
			.start = sharkl3_dcam_start,
			.stop = sharkl3_dcam_stop,
			.stop_cap_eb = sharkl3_dcam_cap_disable,
			.fetch_start = sharkl3_dcam_fetch_start,
			.auto_copy = sharkl3_dcam_auto_copy,
			.force_copy = sharkl3_dcam_force_copy,
			.path_start = sharkl3_dcam_path_start,
			.path_stop = sharkl3_dcam_path_stop,
			.path_pause = sharkl3_dcam_path_pause,
			.path_resume = sharkl3_dcam_path_resume,
			.path_src_sel = sharkl3_dcam_full_path_src_sel,
			.path_size_update = sharkl3_dcam_path_size_update,
			.dcam_calc_rds_phase_info = NULL,
			.mipi_cap_set = sharkl3_dcam_mipi_cap_set,
			.dcam_fetch_set = sharkl3_dcam_fetch_set,
			.dcam_fetch_block_set = sharkl3_dcam_fetch_block_set,
			.ebd_set = sharkl3_dcam_ebd_set,
			.binning_4in1_set = sharkl3_dcam_binning_4in1_set,
			.sram_ctrl_set = sharkl3_dcam_sram_ctrl_set,
			.lbuf_share_set = NULL,
			.dcam_slice_fetch_set = sharkl3_dcam_slice_fetch_set,
			.dcam_fbc_ctrl = NULL,
			.dcam_fbc_addr_set = NULL,
			.dcam_gtm_status_get = NULL,
			.cam_gtm_ltm_eb = NULL,
			.cam_gtm_ltm_dis = NULL,
			.isp_fetch_set = sharkl3_isp_fetch_set,
			.default_para_set = sharkl3_isp_default_param_set,
			.block_func_get = sharkl3_block_func_get,
			.hist_enable_get = sharkl3_isp_hist_enable_get,
			.cfg_map_info_get = sharkl3_isp_cfg_map_info_get,
			.fmcu_valid_get = sharkl3_isp_fmcu_available,
			.isp_afbc_addr_set = NULL,
			.isp_afbc_path_set = NULL,
			.isp_fbd_slice_set = NULL,
			.isp_fbd_addr_set = NULL,
			.isp_afbc_fmcu_addr_set = NULL,
			.isp_afbc_path_slice_set = NULL,
			.isp_ltm_slice_set = NULL,
			.isp_nr3_fbc_slice_set = NULL,
			.isp_nr3_fbd_slice_set = NULL,
			.bypass_data_get = sharkl3_cam_bypass_data_get,
			.bypass_count_get = sharkl3_cam_bypass_count_get,
			.reg_trace = sharkl3_cam_reg_trace,
			.isp_cfg_subblock = sharkl3_isp_cfg_subblock,
		},
	},
};

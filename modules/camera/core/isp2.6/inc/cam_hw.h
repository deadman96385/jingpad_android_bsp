/*
 * Copyright (C) 2017-2018 Spreadtrum Communications Inc.
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

#ifndef _CAM_HW_H_
#define _CAM_HW_H_

#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/platform_device.h>

extern struct cam_hw_info sharkl3_hw_info;
extern struct cam_hw_info sharkl5pro_hw_info;

/*
 * Supported dcam_if index. Number 0&1 for dcam_if and 2 for dcam_if_lite.
 */
enum dcam_id {
	DCAM_ID_0 = 0,
	DCAM_ID_1,
	DCAM_ID_2,
	DCAM_ID_MAX,
};

enum cam_prj_id {
	SHARKL3,
	SHARKL5,
	ROC1,
	QOGIRN6pro,
	SHARKL5pro,
	PROJECT_MAX
};

enum isp_default_type {
	ISP_HW_PARA,
	ISP_CFG_PARA,
	ISP_MAX_PARA
};

enum cam_block_type {
	DCAM_BLOCK_TYPE,
	ISP_BLOCK_TYPE,
	MAX_BLOCK_TYPE
};

enum dcam_full_src_sel_type {
	ORI_RAW_SRC_SEL,
	PROCESS_RAW_SRC_SEL,
	MAX_RAW_SRC_SEL
};

enum cam_reg_trace_type {
	NORMAL_REG_TRACE,
	ABNORMAL_REG_TRACE,
	MAX_REG_TRACE
};

enum cam_bypass_type {
	DCAM_BYPASS_TYPE,
	ISP_BYPASS_TYPE,
	MAX_BYPASS_TYPE
};

enum dcam_fbc_mode_type {
	DCAM_FBC_DISABLE = 0,
	DCAM_FBC_FULL_10_BIT = 0x1,
	DCAM_FBC_BIN_10_BIT = 0x3,
	DCAM_FBC_FULL_14_BIT = 0x5,
	DCAM_FBC_BIN_14_BIT = 0x7,
};

struct glb_syscon {
	uint32_t rst;
	uint32_t rst_mask;
	uint32_t rst_ahb_mask;
	uint32_t rst_vau_mask;
	uint32_t all_rst;
	uint32_t all_rst_mask;
};

struct cam_hw_ip_info {
	uint32_t idx;
	uint32_t irq_no;
	uint32_t max_height;
	uint32_t max_width;
	unsigned long phy_base;
	unsigned long reg_base;
	struct glb_syscon syscon;

	/* For dcam support info */
	uint32_t slm_path;
	uint32_t lbuf_share_support;
	uint32_t offline_slice_support;
	uint32_t superzoom_support;
	uint32_t dcam_full_fbc_mode;
	uint32_t dcam_bin_fbc_mode;
	unsigned long *store_addr_tab;
	uint32_t *path_ctrl_id_tab;
	uint32_t afl_gbuf_size;
	unsigned long pdaf_type3_reg_addr;

	/* For isp support info */
	uint32_t slm_cfg_support;
	uint32_t *ctx_fmcu_support;
};

struct cam_hw_soc_info {
	struct platform_device *pdev;
	unsigned long axi_reg_base;

	struct regmap *cam_ahb_gpr;
	struct regmap *aon_apb_gpr;

	struct clk *clk;
	struct clk *clk_parent;
	struct clk *clk_default;
	struct clk *bpc_clk;
	struct clk *bpc_clk_parent;
	struct clk *bpc_clk_default;
	struct clk *core_eb;
	struct clk *axi_eb;
	struct clk *axi_clk;
	struct clk *axi_clk_parent;
	struct clk *axi_clk_default;

	uint32_t arqos_high;
	uint32_t arqos_low;
	uint32_t awqos_high;
	uint32_t awqos_low;
};

struct cam_hw_soc_ops {
	int (*clk_enable)(struct cam_hw_soc_info *hw);
	int (*clk_disable)(struct cam_hw_soc_info *hw);
	int (*clk_update)(struct cam_hw_soc_info *hw, void *arg);
	void (*axi_init)(void *arg);
	void (*qos_set)(struct cam_hw_soc_info *hw);
	int (*reset)(struct cam_hw_info *hw, void *arg);
};

struct cam_hw_irq_ops {
	int (*irq_request)(struct cam_hw_ip_info *hw, void *arg);
	int (*irq_free)(struct cam_hw_ip_info *hw, void *arg);
	int (*irq_enable)(struct cam_hw_ip_info *hw, void *arg);
	int (*irq_disable)(struct cam_hw_ip_info *hw, void *arg);
	int (*irq_clear)(struct cam_hw_ip_info *hw, void *arg);
	irqreturn_t (*irq_proc)(uint32_t irq_no, void *arg);
};

struct cam_hw_core_ops {
	int (*start)(void *arg);
	int (*stop)(void *arg);
	int (*stop_cap_eb)(void *arg);
	void (*fetch_start)(struct cam_hw_info *hw);
	void (*auto_copy)(uint32_t id, void *arg);
	void (*force_copy)(uint32_t id, void *arg);
	int (*path_start)(void *handle, uint32_t path_id);
	int (*path_stop)(void *handle, uint32_t path_id);
	int (*path_pause)(uint32_t idx, uint32_t path_id);
	int (*path_resume)(uint32_t idx, uint32_t path_id);
	int (*path_src_sel)(void *handle, enum dcam_full_src_sel_type src_sel);
	int (*path_size_update)(void *handle, void *arg);
	int (*dcam_calc_rds_phase_info)(void *arg,
		uint16_t slice_id, uint16_t slice_end0, uint16_t slice_end1);
	int (*mipi_cap_set)(void *arg);
	int (*dcam_fetch_block_set)(void *arg);
	int (*dcam_fetch_set)(void *arg);
	void (*dcam_fbc_ctrl)(uint32_t idx, int fbc_mode);
	int (*dcam_fbc_addr_set)(uint32_t idx, unsigned long addr, void *arg);
	int (*dcam_slice_fetch_set)(void *arg);
	int (* lbuf_share_set)(enum dcam_id idx, uint32_t width);
	int (* ebd_set)(uint32_t idx, void *arg);
	int (*binning_4in1_set)(void *arg, int binning_4in1_en);
	int (*sram_ctrl_set)(void *arg, int sram_ctrl_en);
	int (*dcam_gtm_status_get)(uint32_t idx);
	void (*cam_gtm_ltm_eb)(uint32_t dcam_idx, uint32_t isp_idx);
	void (*cam_gtm_ltm_dis)(uint32_t dcam_idx, uint32_t isp_idx);
	void (*isp_fetch_set)(void *arg);
	void (*isp_afbc_addr_set)(uint32_t idx, uint32_t spath_id,
		unsigned long *yuv_addr);
	int (*isp_afbc_path_set)(void *arg);
	int (*isp_fbd_slice_set)(void *fmcu_handle, void *arg);
	void (*isp_fbd_addr_set)(int idx, void *arg1, void *arg2);
	void (*isp_afbc_fmcu_addr_set)(void *fmcu_handle, void *arg, int index);
	int (*isp_afbc_path_slice_set)(void *fmcu_handle, uint32_t path_en,
		uint32_t ctx_idx, uint32_t spath_id, void *arg);
	int (*isp_ltm_slice_set)(void *fmcu_handle, void *arg, uint32_t ltm_id);
	int (*isp_nr3_fbc_slice_set)(void *fmcu_handle, void *arg);
	int (*isp_nr3_fbd_slice_set)(void *fmcu_handle, void *arg);
	void (*default_para_set)(struct cam_hw_info *hw,
		void *arg, enum isp_default_type type);
	uint32_t (*hist_enable_get)(int ctx_id);
	uint32_t* (*cfg_map_info_get)(void *arg);
	int (*fmcu_valid_get)(uint32_t fmcu_id);
	struct bypass_tag * (*bypass_data_get)(uint32_t idx, enum cam_bypass_type);
	uint32_t (*bypass_count_get)(enum cam_bypass_type type);
	void* (*block_func_get)(uint32_t index, enum cam_block_type type);
	void (*reg_trace)(uint32_t idx, enum cam_reg_trace_type type);
	void (*isp_cfg_subblock)(void *ctx);
};

struct cam_hw_ops {
	struct cam_hw_soc_ops dcam_soc_ops;
	struct cam_hw_soc_ops isp_soc_ops;
	struct cam_hw_irq_ops dcam_irq_ops;
	struct cam_hw_irq_ops isp_irq_ops;
	struct cam_hw_core_ops core_ops;
};

struct cam_hw_info {
	enum cam_prj_id prj_id;
	struct platform_device *pdev;
	struct cam_hw_soc_info *soc_dcam;
	struct cam_hw_soc_info *soc_isp;
	struct cam_hw_ip_info *ip_dcam[DCAM_ID_MAX];
	struct cam_hw_ip_info *ip_isp;
	struct cam_hw_ops hw_ops;
};

#endif

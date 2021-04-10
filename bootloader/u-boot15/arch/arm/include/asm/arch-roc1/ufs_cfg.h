/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _UFS_REG_V0_H_
#define _UFS_REG_V0_H_

struct ufs_cfg_info {
	uint32_t  ufshci_regbase;

	uint32_t  apb_enable_reg;
	uint32_t  apb_enable_bit;

	uint32_t  ao_aon_apb_enable_reg;
	uint32_t  ao_aon_apb_enable_bit;

	uint32_t  ufs_tx_clk_cfg;
	uint32_t  ufs_tx_clk_val;

	uint32_t  ufs_rx_clk_cfg;
	uint32_t  ufs_rx_clk_val;

	uint32_t  ao_aon_apb_reset_reg;
	uint32_t  ao_aon_apb_reset_bit;

	uint32_t  apb_reset_reg;
	uint32_t  apb_reset_bit;

	uint32_t  ao_regbase;
	uint32_t  ao_rest_bit;

	uint32_t  utp_reset_reg;
	uint32_t  utp_reset_bit;

	uint32_t  anlg_phy_g1_reg;
	uint32_t  anlg_phy_g1_reset_bit;

	uint32_t  anlg_phy_g1_trim_sel_reg;
	uint32_t  anlg_phy_g1_trim_bit;

	uint32_t  pmu_bypass_enable_reg;
	uint32_t  pmu_bypass_enable_bit;

	const char *ldo_core;
	const char *ldo_io;
};

struct unipro_cfg_info {
	uint32_t  unipro_regbase;

	uint32_t  pa_rxtx_reset_reg;
	uint32_t  pa_rxtx_reset_bit;

	uint32_t  dl_reset_reg;
	uint32_t  dl_reset_bit;

	uint32_t  n_reset_reg;
	uint32_t  n_reset_bit;

	uint32_t  t_reset_reg;
	uint32_t  t_reset_bit;

	uint32_t  dme_reset_reg;
	uint32_t  dme_reset_bit;
};

struct ufs_cfg_info *get_ufscontrol_info(void);
struct unipro_cfg_info *get_uniprocontrol_info(void);

#endif

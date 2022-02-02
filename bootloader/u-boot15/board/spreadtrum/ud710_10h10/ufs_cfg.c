/*
 * This file is produced by tools!!
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

#include <common.h>
#include <asm/arch/sprd_reg.h>
#include <asm/io.h>
#include <asm/arch/ufs_cfg.h>
#include <asm/arch/common.h>


const struct ufs_cfg_info ufs_ctrl_info[1] = {

	SPRD_UFS_HCI_PHYS,

	REG_AP_APB_APB_EB1,
	BIT_AP_APB_UFS_UTP_EB | BIT_AP_APB_UFS_EB | BIT_AP_APB_UFS_UNIPRO_EB | BIT_AP_APB_UFS_HCI_EB,

	REG_AON_APB_APB_EB1,
	BIT_AON_APB_UFS_AO_EB,

	REG_AP_CLK_CORE_CGM_UFS_TX_CFG,
	BIT_1,

	REG_AP_CLK_CORE_CGM_UFS_RX_CFG,
	BIT_1,

	REG_AON_APB_APB_RST1,
	BIT_AON_APB_UFS_AO_SOFT_RST,

	REG_AP_APB_APB_RST,
	BIT_AP_APB_UFS_UTP_SOFT_RST | BIT_AP_APB_UFS_HCI_SOFT_RST | BIT_AP_APB_UFS_UNIPRO_SOFT_RST | BIT_AP_APB_UFS_SOFT_RST,

	SPRD_UFS_AO_PHYS + 0x1C,
	BIT_1,

	SPRD_UFS_UTP_PHYS + 0x100,
	BIT_0 | BIT_1,

	REG_ANLG_PHY_G1_ANALOG_MIPI_MPHY_1T1R_MPHY_APB_REG,
	BIT_3,

	REG_ANLG_PHY_G1_ANALOG_MIPI_MPHY_1T1R_REG_SEL_CFG_0,
	BIT_6 | BIT_7 | BIT_8,

	REG_PMU_APB_UFS_PWR_GATE_BYP_CFG,
	BIT_PMU_APB_UFS_PWR_GATE_BYP,

	"vddgen",
	"vddemmccore",
};

const struct unipro_cfg_info unipro_ctrl_info[1] = {

	SPRD_UFS_UNIPRO_PHYS,

	SPRD_UFS_UNIPRO_PHYS + 0x3c,
	BIT_24 | BIT_25 | BIT_26 | BIT_27 | BIT_28 | BIT_29,

	SPRD_UFS_UNIPRO_PHYS + 0x40,
	BIT_0,

	SPRD_UFS_UNIPRO_PHYS + 0x84,
	BIT_1,

	SPRD_UFS_UNIPRO_PHYS + 0xc0,
	BIT_4,

	SPRD_UFS_UNIPRO_PHYS + 0xd0,
	BIT_2,

};

struct ufs_cfg_info *get_ufscontrol_info()
{
	return	&ufs_ctrl_info[0];
}

struct unipro_cfg_info *get_uniprocontrol_info()
{
	return	&unipro_ctrl_info[0];
}

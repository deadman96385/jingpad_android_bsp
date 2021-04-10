/*
 * This file is produced by tools!!
 *
 * Copyright (C) 2016 Spreadtrum Communications Inc.
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
#include <asm/arch/sdio_cfg.h>
#include <asm/arch/sdio_reg.h>
#include <asm/arch/common.h>

const struct sdio_base_info sdio_ctrl_info[2] = {
{
	EMMC,
	SPRD_EMMC_BASE,
#ifdef CONFIG_FPGA
	NULL,
	NULL,
	36000000,
	100000,
#else
	REG_AON_CLK_CORE_CGM_EMMC_2X_CFG,
	3,
	192000000,
	400000,
#endif
	REG_AP_AHB_AHB_EB,
	BIT_AP_AHB_EMMC_EB,
	REG_AP_AHB_AHB_RST,
	BIT_AP_AHB_EMMC_SOFT_RST,
	REG_AON_APB_CLK_EB0,
	BIT_0|BIT_1,

	"vddgen",
	"vddemmccore",
},
{
	SD,
	SPRD_SDIO0_BASE,
#ifdef CONFIG_FPGA
	NULL,
	NULL,
	36000000,
	100000,
#else
	REG_AON_CLK_CORE_CGM_SDIO0_2X_CFG,
	3,
	192000000,
	400000,
#endif

	REG_AP_AHB_AHB_EB,
	BIT_8,
	REG_AP_AHB_AHB_RST,
	BIT_11,
	REG_AON_APB_CLK_EB0,
	BIT_2|BIT_3,

	"vddsdio",
	"vddsdcore",
}
};

struct sdio_base_info *get_sdcontrol_info(uint32_t device_type)
{
	return  &sdio_ctrl_info[device_type];
}



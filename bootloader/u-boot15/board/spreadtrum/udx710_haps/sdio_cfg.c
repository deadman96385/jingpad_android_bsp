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

/*
 * TODO：
 * Now many macros(such as: SPRD_EMMC_BASE, REG_AP_CLK_EMMC_CFG)
 * have not defined in spreadtrum platform, so we use a immediate
 * value instead of it.
 * These immediate values should be removed if the corresponding
 * macros are defined.
 */
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
	REG_AP_CLK_CORE_CGM_EMMC_2X_CFG,
	BIT_0|BIT_1,
	/* selsect 2x clock source, baseclk = freq / 2 */
	195000000,
	400000,
#endif
	REG_AP_AHB_AHB_EB,
	BIT_11,
	REG_AP_AHB_AHB_RST,
	BIT_14,

	0,//"vddgen",
	0,//"vddemmccore",
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
	REG_AP_CLK_CORE_CGM_SDIO0_2X_CFG,
	BIT_0|BIT_1,
	/* selsect 2x clock source, baseclk = freq / 2 */
	195000000,
	400000,
#endif

	REG_AP_AHB_AHB_EB,
	BIT_8,
	REG_AP_AHB_AHB_RST,
	BIT_11,

	0,//"vddsdio",
	0,//"vddsdcore",
}
};

struct sdio_base_info *get_sdcontrol_info(uint32_t device_type)
{
	return  &sdio_ctrl_info[device_type];
}



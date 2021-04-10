/******************************************************************************
 ** File Name:    sprdfb_chip_7715.h                                     *
 ** Author:       congfu.zhao                                           *
 ** DATE:         30/04/2013                                        *
 ** Copyright:    2013 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:                                                    *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                       *

 ******************************************************************************/
#ifndef _SC7715_DISPC_GLB_REG_U_H_
#define _SC7715_DISPC_GLB_REG_U_H_


#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_reg_global.h>
#include "adi_hal_internal.h"


#define BIT(x) (1<<x)

//no mipi

#define DISPC_AHB_SOFT_RST            	REG_AP_AHB_AHB_RST
#define BIT_DISPC_SOFT_RST			BIT_DISPC0_SOFT_RST

#define DISPC_AHB_EN				(REG_AP_AHB_AHB_EB)
#define BIT_DISPC_AHB_EN			(BIT_DISPC0_EB)

#define DISPC_CORE_EN			(REG_AP_APB_APB_EB)
#define BIT_DISPC_CORE_EN			(BIT_AP_CKG_EB)

#define DISPC_EMC_EN				(REG_AON_APB_APB_EB1)
#define BIT_DISPC_EMC_EN			(BIT_DISP_EMC_EB)

#define DISPC_PLL_SEL_CFG			REG_AP_CLK_DISPC0_CFG
#define BITS_DISPC_PLL_SEL_CFG		0
#define BIT0_DISPC_PLL_SEL_CFG		BIT(0)
#define BIT1_DISPC_PLL_SEL_CFG		BIT(1)
#define BIT_DISPC_PLL_SEL_MSK		BIT1_DISPC_PLL_SEL_CFG | BIT0_DISPC_PLL_SEL_CFG

#define DISPC_PLL_DIV_CFG			REG_AP_CLK_DISPC0_CFG
#define BITS_DISPC_PLL_DIV_CFG		8
#define BIT0_DISPC_PLL_DIV_CFG		BIT(8)
#define BIT1_DISPC_PLL_DIV_CFG		BIT(9)
#define BIT2_DISPC_PLL_DIV_CFG		BIT(10)
#define BIT_DISPC_PLL_DIV_MSK		BIT0_DISPC_PLL_DIV_CFG | BIT1_DISPC_PLL_DIV_CFG | BIT2_DISPC_PLL_DIV_CFG

#define DISPC_DBI_SEL_CFG			REG_AP_CLK_DISPC0_DBI_CFG
#define BITS_DISPC_DBI_SEL_CFG		0
#define BIT0_DISPC_DBI_SEL_CFG		BIT(0)
#define BIT1_DISPC_DBI_SEL_CFG		BIT(1)
#define BIT_DISPC_DBI_SEL_MSK		BIT0_DISPC_DBI_SEL_CFG | BIT1_DISPC_DBI_SEL_CFG

#define DISPC_DBI_DIV_CFG			REG_AP_CLK_DISPC0_DBI_CFG
#define BITS_DISPC_DBI_DIV_CFG		8
#define BIT0_DISPC_DBI_DIV_CFG		BIT(8)
#define BIT1_DISPC_DBI_DIV_CFG		BIT(9)
#define BIT2_DISPC_DBI_DIV_CFG		BIT(10)
#define BIT_DISPC_DBI_DIV_MSK		BIT0_DISPC_DBI_DIV_CFG | BIT1_DISPC_DBI_DIV_CFG | BIT2_DISPC_DBI_DIV_CFG

#define DISPC_DPI_SEL_CFG			REG_AP_CLK_DISPC0_DPI_CFG
#define BITS_DISPC_DPI_SEL_CFG		0
#define BIT0_DISPC_DPI_SEL_CFG		BIT(0)
#define BIT1_DISPC_DPI_SEL_CFG		BIT(1)
#define BIT_DISPC_DPI_SEL_MSK		BIT0_DISPC_DPI_SEL_CFG | BIT1_DISPC_DPI_SEL_CFG

#define DISPC_DPI_DIV_CFG			REG_AP_CLK_DISPC0_DPI_CFG
#define BITS_DISPC_DPI_DIV_CFG		8
#define BIT0_DISPC_DPI_DIV_CFG		BIT(8)
#define BIT1_DISPC_DPI_DIV_CFG		BIT(9)
#define BIT2_DISPC_DPI_DIV_CFG		BIT(10)
#define BIT3_DISPC_DPI_DIV_CFG		BIT(11)
#define BIT4_DISPC_DPI_DIV_CFG		BIT(12)
#define BIT5_DISPC_DPI_DIV_CFG		BIT(13)
#define BIT6_DISPC_DPI_DIV_CFG		BIT(14)
#define BIT7_DISPC_DPI_DIV_CFG		BIT(15)
#define BIT_DISPC_DPI_DIV_MSK		BIT0_DISPC_DPI_DIV_CFG | BIT1_DISPC_DPI_DIV_CFG | BIT2_DISPC_DPI_DIV_CFG | BIT3_DISPC_DPI_DIV_CFG \
					| BIT4_DISPC_DPI_DIV_CFG | BIT5_DISPC_DPI_DIV_CFG | BIT6_DISPC_DPI_DIV_CFG | BIT7_DISPC_DPI_DIV_CFG


enum{
	DISPC_PLL_SEL_153_6M = 0,
	DISPC_PLL_SEL_192M,
};

enum{
	DISPC_DBI_SEL_128M = 0,
	DISPC_DBI_SEL_153_6M,
	DISPC_DBI_SEL_192M,
	DISPC_DBI_SEL_256M
};

enum{
	DISPC_DPI_SEL_128M = 0,
	DISPC_DPI_SEL_153_6M,
	DISPC_DPI_SEL_192M,
	DISPC_DPI_SEL_384M,
};

#define DISPC_PLL_SEL_DEFAULT	DISPC_PLL_SEL_192M
#define DISPC_DBI_SEL_DEFAULT	DISPC_DBI_SEL_256M
#define DISPC_DPI_SEL_DEFAULT	DISPC_DPI_SEL_384M

#define DISPC_PLL_DIV_DEFAULT	0
#define DISPC_DBI_DIV_DEFAULT	0
#define DISPC_DPI_DIV_DEFAULT	14

#define SPRDFB_DPI_CLOCK_SRC (384000000)

void dsi_enable(void);

void dispc_print_clk(void);



#endif

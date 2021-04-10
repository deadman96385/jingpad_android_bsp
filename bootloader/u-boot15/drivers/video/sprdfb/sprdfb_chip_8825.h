/******************************************************************************
 ** File Name:    sprdfb_chip_8825.h                                     *
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
#ifndef _SC8825_DISPC_GLB_REG_U_H_
#define _SC8825_DISPC_GLB_REG_U_H_


#include <asm/arch/sc8810_reg_ahb.h>
#include <asm/arch/sc8810_reg_global.h>

#define BIT(x) (1<<x)


//#define 	DSI_CTL_BEGIN	0x60100000
#define	SPRD_MIPI_DPHY_GEN1


#define DISPC_AHB_SOFT_RST            	AHB_SOFT_RST
#define BIT_DISPC_SOFT_RST		 	BIT(20)

#define DSI_AHB_SOFT_RST           		AHB_SOFT_RST
#define BIT_DSI_SOFT_RST	 		BIT(26)

#define DSI_REG_EB				(AHB_REG_BASE+0x1C)
#define DSI_BIT_EB					BIT(0)

#define DISPC_AHB_EN				(AHB_CTL0)
#define BIT_DISPC_AHB_EN			(BIT(22))

#define DISPC_CORE_EN			(AHB_CTL2)
#define BIT_DISPC_CORE_EN			(BIT(9))

#define DISPC_EMC_EN				(AHB_CTL2)
#define BIT_DISPC_EMC_EN			(BIT(11))

#define DISPC_PLL_SEL_CFG			AHB_DISPC_CLK
#define BITS_DISPC_PLL_SEL_CFG		1
#define BIT0_DISPC_PLL_SEL_CFG		BIT(1)
#define BIT1_DISPC_PLL_SEL_CFG		BIT(2)
#define BIT_DISPC_PLL_SEL_MSK		BIT1_DISPC_PLL_SEL_CFG | BIT0_DISPC_PLL_SEL_CFG

#define DISPC_PLL_DIV_CFG			AHB_DISPC_CLK
#define BITS_DISPC_PLL_DIV_CFG		3
#define BIT0_DISPC_PLL_DIV_CFG		BIT(3)
#define BIT1_DISPC_PLL_DIV_CFG		BIT(4)
#define BIT2_DISPC_PLL_DIV_CFG		BIT(5)
#define BIT_DISPC_PLL_DIV_MSK		BIT0_DISPC_PLL_DIV_CFG | BIT1_DISPC_PLL_DIV_CFG | BIT2_DISPC_PLL_DIV_CFG

#define DISPC_DBI_SEL_CFG			AHB_DISPC_CLK
#define BITS_DISPC_DBI_SEL_CFG		9
#define BIT0_DISPC_DBI_SEL_CFG		BIT(9)
#define BIT1_DISPC_DBI_SEL_CFG		BIT(10)
#define BIT_DISPC_DBI_SEL_MSK		BIT0_DISPC_DBI_SEL_CFG | BIT1_DISPC_DBI_SEL_CFG

#define DISPC_DBI_DIV_CFG			AHB_DISPC_CLK
#define BITS_DISPC_DBI_DIV_CFG		11
#define BIT0_DISPC_DBI_DIV_CFG		BIT(11)
#define BIT1_DISPC_DBI_DIV_CFG		BIT(12)
#define BIT2_DISPC_DBI_DIV_CFG		BIT(13)
#define BIT_DISPC_DBI_DIV_MSK		BIT0_DISPC_DBI_DIV_CFG | BIT1_DISPC_DBI_DIV_CFG | BIT2_DISPC_DBI_DIV_CFG

#define DISPC_DPI_SEL_CFG			AHB_DISPC_CLK
#define BITS_DISPC_DPI_SEL_CFG		17
#define BIT0_DISPC_DPI_SEL_CFG		BIT(17)
#define BIT1_DISPC_DPI_SEL_CFG		BIT(18)
#define BIT_DISPC_DPI_SEL_MSK		BIT0_DISPC_DPI_SEL_CFG | BIT1_DISPC_DPI_SEL_CFG

#define DISPC_DPI_DIV_CFG			AHB_DISPC_CLK
#define BITS_DISPC_DPI_DIV_CFG		19
#define BIT0_DISPC_DPI_DIV_CFG		BIT(19)
#define BIT1_DISPC_DPI_DIV_CFG		BIT(20)
#define BIT2_DISPC_DPI_DIV_CFG		BIT(21)
#define BIT3_DISPC_DPI_DIV_CFG		BIT(22)
#define BIT4_DISPC_DPI_DIV_CFG		BIT(23)
#define BIT5_DISPC_DPI_DIV_CFG		BIT(24)
#define BIT6_DISPC_DPI_DIV_CFG		BIT(25)
#define BIT7_DISPC_DPI_DIV_CFG		BIT(26)
#define BIT_DISPC_DPI_DIV_MSK		BIT0_DISPC_DPI_DIV_CFG | BIT1_DISPC_DPI_DIV_CFG | BIT2_DISPC_DPI_DIV_CFG | BIT3_DISPC_DPI_DIV_CFG \
					| BIT4_DISPC_DPI_DIV_CFG | BIT5_DISPC_DPI_DIV_CFG | BIT6_DISPC_DPI_DIV_CFG | BIT7_DISPC_DPI_DIV_CFG


enum{
	DISPC_PLL_SEL_256M = 0,
	DISPC_PLL_SEL_192M,
	DISPC_PLL_SEL_153_6M,
	DISPC_PLL_SEL_128M
};

enum{
	DISPC_DBI_SEL_256M = 0,
	DISPC_DBI_SEL_192M,
	DISPC_DBI_SEL_153_6M,
	DISPC_DBI_SEL_128M
};

enum{
	DISPC_DPI_SEL_384M = 0,
	DISPC_DPI_SEL_192M,
	DISPC_DPI_SEL_153_6M,
	DISPC_DPI_SEL_128M
};

#define DISPC_PLL_SEL_DEFAULT	DISPC_PLL_SEL_256M
#define DISPC_DBI_SEL_DEFAULT	DISPC_DBI_SEL_256M
#define DISPC_DPI_SEL_DEFAULT	DISPC_DPI_SEL_384M

#define DISPC_PLL_DIV_DEFAULT	0
#define DISPC_DBI_DIV_DEFAULT	0
#define DISPC_DPI_DIV_DEFAULT	10

#define SPRDFB_DPI_CLOCK_SRC (384000000)

void dsi_enable(void);

void dispc_print_clk(void);






#endif

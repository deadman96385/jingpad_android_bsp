/******************************************************************************
 ** File Name:    sprdfb_chip_9630.h                                     *
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
#ifndef _SC9630_DISPC_GLB_REG_U_H_
#define _SC9630_DISPC_GLB_REG_U_H_

/* DISPC regs offset */
#define DISPC_CTRL 		(0x0000)
#define DISPC_SIZE_XY 		(0x0004)
#define DISPC_RSTN 		(0x0008)

#define DISPC_STS 		(0x0010)

#define DISPC_LVDS_CTRL 	(0x0018)
#define DISPC_IMG_CTRL 		(0x0020)
#define DISPC_IMG_Y_BASE_ADDR 	(0x0024)
#define DISPC_IMG_UV_BASE_ADDR 	(0x0028)
#define DISPC_IMG_V_BASE_ADDR 	(0x002c)
#define DISPC_IMG_SIZE_XY 	(0x0030)
#define DISPC_IMG_PITCH 	(0x0034)
#define DISPC_IMG_DISP_XY 	(0x0038)
#define DISPC_BG_COLOR 		(0x003c)

#define DISPC_OSD_CTRL 		(0x0040)
#define DISPC_OSD_BASE_ADDR 	(0x0044)
#define DISPC_OSD_SIZE_XY 	(0x0048)
#define DISPC_OSD_PITCH 	(0x004c)
#define DISPC_OSD_DISP_XY 	(0x0050)
#define DISPC_OSD_ALPHA 	(0x0054)
#define DISPC_OSD_CK 		(0x0058)

#define DISPC_Y2R_CTRL 		(0x0060)
#define DISPC_Y2R_CONTRAST 	(0x0064)
#define DISPC_Y2R_SATURATION 	(0x0068)
#define DISPC_Y2R_BRIGHTNESS 	(0x006c)

#define DISPC_INT_EN 		(0x0070)
#define DISPC_INT_CLR 		(0x0074)
#define DISPC_INT_STATUS 	(0x0078)
#define DISPC_INT_RAW 		(0x007c)

#define DISPC_DPI_CTRL 		(0x0080)
#define DISPC_DPI_H_TIMING 	(0x0084)
#define DISPC_DPI_V_TIMING 	(0x0088)
#define DISPC_DPI_STS0 		(0x008c)
#define DISPC_DPI_STS1 		(0x0090)

#define DISPC_DBI_CTRL 		(0x00a0)
#define DISPC_DBI_TIMING0 	(0x00a4)
#define DISPC_DBI_TIMING1 	(0x00a8)
#define DISPC_DBI_RDATA 	(0x00ac)
#define DISPC_DBI_CMD 		(0x00b0)
#define DISPC_DBI_DATA 		(0x00b4)
#define DISPC_DBI_QUEUE 	(0x00b8)

/* shadow register , read only */
#define SHDW_IMG_CTRL 		(0x00C0)
#define SHDW_IMG_Y_BASE_ADDR 	(0x00C4)
#define SHDW_IMG_UV_BASE_ADDR 	(0x00C8)
#define SHDW_IMG_V_BASE_ADDR 	(0x00CC)
#define SHDW_IMG_SIZE_XY 	(0x00D0)
#define SHDW_IMG_PITCH 		(0x00D4)
#define SHDW_IMG_DISP_XY 	(0x00D8)
#define SHDW_BG_COLOR 		(0x00DC)
#define SHDW_OSD_CTRL 		(0x00E0)
#define SHDW_OSD_BASE_ADDR 	(0x00E4)
#define SHDW_OSD_SIZE_XY 	(0x00E8)
#define SHDW_OSD_PITCH 		(0x00EC)
#define SHDW_OSD_DISP_XY 	(0x00F0)
#define SHDW_OSD_ALPHA 		(0x00F4)
#define SHDW_OSD_CK 		(0x00F8)
#define SHDW_Y2R_CTRL 		(0x0100)
#define SHDW_Y2R_CONTRAST 	(0x0104)
#define SHDW_Y2R_SATURATION 	(0x0108)
#define SHDW_Y2R_BRIGHTNESS 	(0x010C)
#define SHDW_DPI_H_TIMING 	(0x0110)
#define SHDW_DPI_V_TIMING 	(0x0114)
#define DISPC_TE_SYNC_DELAY 	(0x00bc)

static inline u32 dispc_read(unsigned long reg)
{
	return __raw_readl(SPRD_DISPC0_BASE + reg);
}

static inline void dispc_write(u32 value, unsigned long reg)
{
	__raw_writel(value, (SPRD_DISPC0_BASE + reg));
}

static inline void dispc_set_bits(u32 bits, unsigned long reg)
{
	dispc_write(dispc_read(reg) | bits, reg);
}

static inline void dispc_clear_bits(u32 bits, unsigned long reg)
{
	dispc_write(dispc_read(reg) & ~bits, reg);
}

#define BIT(x) (1<<x)

#define	SPRD_MIPI_DPHY_GEN2

#define DSI_CTL_BEGIN				SPRD_DSI_BASE	

#define DSI_AHB_SOFT_RST           		REG_AP_AHB_AHB_RST
#define BIT_DSI_SOFT_RST	 		( BIT(0) )

#define DSI_REG_EB				REG_AP_AHB_AHB_EB
#define DSI_BIT_EB					BIT_DSI_EB

#define DISPC_AHB_SOFT_RST            	REG_AP_AHB_AHB_RST
//#define BIT_DISPC_SOFT_RST			BIT_DISPC_SOFT_RST

#define BIT_DISPC0_EB                   ( BIT(1)  )
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
	DISPC_PLL_SEL_96M = 0,
	DISPC_PLL_SEL_192M,
	DISPC_PLL_SEL_256M,
	DISPC_PLL_SEL_312M
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
	DISPC_DPI_SEL_384M
};

#define DISPC_PLL_SEL_DEFAULT	DISPC_PLL_SEL_256M
#define DISPC_DBI_SEL_DEFAULT	DISPC_DBI_SEL_256M
#define DISPC_DPI_SEL_DEFAULT	DISPC_DPI_SEL_384M

#define DISPC_PLL_DIV_DEFAULT	0
#define DISPC_DBI_DIV_DEFAULT	0
#define DISPC_DPI_DIV_DEFAULT	6

#define SPRDFB_DPI_CLOCK_SRC (384000000)


void dsi_enable(void);
void dsi_disable(void);
void dispc_early_configs(void);
void dispc_print_clk(void);



#endif

/******************************************************************************
 ** File Name:    sprdfb_chip_9860.h                                     *
 ** Author:       leon.he                                           *
 ** DATE:         14/01/2016                                        *
 ** Copyright:    2013 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:                                                    *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                       *

 ******************************************************************************/
#ifndef _SC9868_DISPC_GLB_REG_U_H_
#define _SC9868_DISPC_GLB_REG_U_H_

#include <asm/arch/sprd_reg.h>

/* DISPC regs offset */
#define DISPC_VERSION			(0x0000)
#define DISPC_CTRL			(0x0004)
#define DISPC_SIZE_XY			(0x0008)
#define DISPC_RSTN			(0x000C)
//#define DISPC_BUF_THRES (0x000C)

#define DISPC_SECURE                    (0x0010)
#define DISPC_STS			(0x0014)
#define DISPC_3D_CTRL			(0x0018)
//#define DISPC_LVDS_CTRL		(0x0018)

//#define IMG_BASE_ADDR0		(0x0020)
//#define IMG_BASE_ADDR1		(0x0024)
//#define IMG_BASE_ADDR2		(0x0028)

#define DISPC_IMG_CTRL			(0x0030)
#define DISPC_IMG_Y_BASE_ADDR		(0x0020)
#define DISPC_IMG_UV_BASE_ADDR		(0x0024)
#define DISPC_IMG_V_BASE_ADDR		(0x0028)

#define DISPC_IMG_SIZE_XY		(0x0034)
#define DISPC_IMG_PITCH			(0x0038)
#define DISPC_IMG_DISP_XY		(0x003c)
#define DISPC_BG_COLOR			(0x0040)

#define DISPC_OSD_CTRL			(0x0060)
#define DISPC_OSD_BASE_ADDR		(0x0050)
#define DISPC_OSD_SIZE_XY		(0x0064)
#define DISPC_OSD_PITCH			(0x0068)
#define DISPC_OSD_DISP_XY		(0x006c)
#define DISPC_OSD_ALPHA			(0x0070)
#define DISPC_OSD_CK			(0x0074)

#define DISPC_Y2R_CTRL			(0x0080)

#define DISPC_Y2R_Y_PARAM		(0x0084)
#define DISPC_Y2R_U_PARAM		(0x0088)
#define DISPC_Y2R_V_PARAM		(0x008c)
#define DISPC_Y2R_COEF_00		(0x0090)
#define DISPC_Y2R_COEF_01		(0x0094)
#define DISPC_Y2R_COEF_10		(0x0098)
#define DISPC_Y2R_COEF_11		(0x009c)
#define DISPC_Y2R_COEF_20		(0x00a0)
#define DISPC_Y2R_COEF_21		(0x00a4)


#define DISPC_INT_EN			(0x00b0)
#define DISPC_INT_CLR			(0x00b4)
#define DISPC_INT_STATUS		(0x00b8)
#define DISPC_INT_RAW			(0x00bc)

#define DISPC_DPI_CTRL			(0x00c0)
#define DISPC_DPI_H_TIMING		(0x00c4)
#define DISPC_DPI_V_TIMING		(0x00c8)
#define DISPC_DPI_STS0			(0x00cc)
#define DISPC_DPI_STS1			(0x00d0)

#define DISPC_DBI_CTRL			(0x00e0)
#define DISPC_DBI_TIMING0		(0x00e4)
#define DISPC_DBI_TIMING1		(0x00e8)
#define DISPC_DBI_RDATA			(0x00ec)
#define DISPC_DBI_CMD			(0x00f0)
#define DISPC_DBI_DATA			(0x00f4)
#define DISPC_DBI_QUEUE			(0x00f8)
#define DISPC_TE_SYNC_DELAY		(0x00fc)


//shadow register , read only
#define SHDW_BUF_THRES			(0x0210)
#define SHDW_3D_CTRL			(0x0218)

#define SHDW_IMG_CTRL			(0x0230)
#define SHDW_IMG_Y_BASE_ADDR		(0x0220)
#define SHDW_IMG_UV_BASE_ADDR		(0x0224)
#define SHDW_IMG_V_BASE_ADDR		(0x0228)

#define SHDW_IMG_SIZE_XY		(0x0234)
#define SHDW_IMG_PITCH			(0x0238)
#define SHDW_IMG_DISP_XY		(0x023c)
#define SHDW_BG_COLOR			(0x0240)


#define SHDW_OSD_CTRL			(0x0260)
#define SHDW_OSD_BASE_ADDR0		(0x0250)
#define SHDW_OSD_BASE_ADDR1		(0x0254)
#define SHDW_OSD_SIZE_XY		(0x0264)
#define SHDW_OSD_PITCH			(0x0268)
#define SHDW_OSD_DISP_XY		(0x026c)
#define SHDW_OSD_ALPHA			(0x0270)
#define SHDW_OSD_CK			(0x0274)
#define SHDW_Y2R_CTRL			(0x0280)
#define SHDW_Y2R_CONTRAST		(0x0284)
#define SHDW_Y2R_SATURATION		(0x0288)
#define SHDW_Y2R_BRIGHTNESS		(0x028c)
#define SGDW_Y2R_COEF_00		(0x0290)
#define SGDW_Y2R_COEF_01		(0x0294)
#define SGDW_Y2R_COEF_10		(0x0298)
#define SGDW_Y2R_COEF_11		(0x029c)
#define SGDW_Y2R_COEF_20		(0x02a0)
#define SGDW_Y2R_COEF_21		(0x02a4)

#define SHDW_DPI_H_TIMING		(0x02c4)
#define SHDW_DPI_V_TIMING		(0x02c8)

#define DSC_CTRL			(0x0400)

#define	SPRD_MIPI_DPHY_GEN2

#define DSI_CTL_BEGIN			SPRD_DSI0_BASE	

#define DSI_AHB_SOFT_RST           	REG_DISP_AHB_AHB_RST
#define BIT_DSI_SOFT_RST	 	(BIT_DISP_AHB_DSI0_SOFT_RST)

#define DSI_REG_EB			REG_DISP_AHB_AHB_EB
#define DSI_BIT_EB			BIT_DISP_AHB_DSI0_EB	

#define DISPC_AHB_SOFT_RST            	REG_DISP_AHB_AHB_RST
#define BIT_DISPC_SOFT_RST		BIT_DISP_AHB_DISPC0_SOFT_RST

#define DISPC_AHB_EN			(REG_DISP_AHB_AHB_EB)
#define BIT_DISPC_AHB_EN		(BIT_DISP_AHB_DISPC0_EB)

#define DISPC_CORE_EN			(REG_DISP_AHB_AHB_EB)
#define BIT_DISPC_CORE_EN		(BIT_DISP_AHB_CKG_EB)

#define DISPC_EMC_EN			(REG_DISP_AHB_AHB_EB)
#define BIT_DISPC_EMC_EN		(BIT_DISP_AHB_DISPC_MTX_EB)

#define REG_DISP_CLK_CORE_clk_dispc0_cfg                  (SPRD_DCAMPCKG_BASE + 0x24)/*clk_dispc0_cfg*/
#define REG_DISP_CLK_CORE_clk_dispc0_dpi_cfg              (SPRD_DCAMPCKG_BASE + 0x28)/*clk_dispc0_dpi_cfg*/
#define REG_DISP_CLK_CORE_clk_dispc1_cfg                  (SPRD_DCAMPCKG_BASE + 0x2c)/*clk_dispc0_cfg*/
#define REG_DISP_CLK_CORE_clk_dispc1_dpi_cfg              (SPRD_DCAMPCKG_BASE + 0x30)/*clk_dispc0_dpi_cfg*/

#define DISPC_PLL_SEL_CFG		REG_DISP_CLK_CORE_clk_dispc0_cfg	
#define BITS_DISPC_PLL_SEL_CFG		0
#define BIT0_DISPC_PLL_SEL_CFG		BIT(0)
#define BIT1_DISPC_PLL_SEL_CFG		BIT(1)
#define BIT_DISPC_PLL_SEL_MSK		BIT1_DISPC_PLL_SEL_CFG | BIT0_DISPC_PLL_SEL_CFG

#define DISPC_PLL_DIV_CFG		REG_DISP_CLK_CORE_clk_dispc0_cfg
#define BITS_DISPC_PLL_DIV_CFG		8
#define BIT0_DISPC_PLL_DIV_CFG		BIT(8)
#define BIT1_DISPC_PLL_DIV_CFG		BIT(9)
#define BIT2_DISPC_PLL_DIV_CFG		BIT(10)
#define BIT_DISPC_PLL_DIV_MSK		BIT0_DISPC_PLL_DIV_CFG | BIT1_DISPC_PLL_DIV_CFG | BIT2_DISPC_PLL_DIV_CFG


#define DISPC_DPI_SEL_CFG		REG_DISP_CLK_CORE_clk_dispc0_dpi_cfg	
#define BITS_DISPC_DPI_SEL_CFG		0
#define BIT0_DISPC_DPI_SEL_CFG		BIT(0)
#define BIT1_DISPC_DPI_SEL_CFG		BIT(1)
#define BIT_DISPC_DPI_SEL_MSK		BIT0_DISPC_DPI_SEL_CFG | BIT1_DISPC_DPI_SEL_CFG

#define DISPC_DPI_DIV_CFG		REG_DISP_CLK_CORE_clk_dispc0_dpi_cfg
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

enum{
	DISPC_PLL_SEL_192M = 0,
	DISPC_PLL_SEL_256M,
	DISPC_PLL_SEL_384M,
	DISPC_PLL_SEL_512M
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
	DISPC_DPI_SEL_256M
};

#define DISPC_PLL_SEL_DEFAULT	DISPC_PLL_SEL_512M
#define DISPC_DBI_SEL_DEFAULT	DISPC_DBI_SEL_256M

#define DISPC_PLL_DIV_DEFAULT	0
#define DISPC_DBI_DIV_DEFAULT	0
#define DISPC_DPI_DIV_DEFAULT	0


#ifdef CONFIG_FB_LCD_NT35532_2_MIPI
   #define DISPC_DPI_SEL_DEFAULT DISPC_DPI_SEL_153_6M
   #define SPRDFB_DPI_CLOCK_SRC (153600000)
#else
   #define DISPC_DPI_SEL_DEFAULT DISPC_DPI_SEL_256M
   #define SPRDFB_DPI_CLOCK_SRC (256000000)
#endif
/*for noc*/
typedef enum {
	DDR_8G = 0,
	DDR_1G,
	DDR_1_5G,
	DDR_2G,
	DDR_3G,
	DDR_4G
} DDR_CAPACITY;

typedef enum {
	NORMAL_MODE = 0,
	FULL_MODE,
	MIXED_MODE
} INTERLEAVE_MODE;

typedef enum {
	SIZE_64 = 0,
	SIZE_128
} INTERLEAVE_SEL;

#define DDR_CAPACITY_OFFSET	9
#define DDR_CAPACITY_MASK	(0x7 << DDR_CAPACITY_OFFSET)

#define INTERLEAVE_MODE_OFFSET	2
#define INTERLEAVE_MODE_MASK	(0x3 << INTERLEAVE_MODE_OFFSET)

#define INTERLEAVE_SEL_OFFSET	6
#define INTERLEAVE_SEL_MASK	(0x3 << INTERLEAVE_SEL_OFFSET)

#define WLED_CE_2705		(25)
void misc_noc_ctrl(unsigned long base, unsigned int mode, unsigned int sel);
void dsi_enable(void);
void dsi_disable(void);
void dispc_early_configs(void);
void dispc_print_clk(void);
int disp_domain_power_ctrl(int enable);

#endif

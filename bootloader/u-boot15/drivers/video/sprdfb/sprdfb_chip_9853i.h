/******************************************************************************
 ** File Name:    sprdfb_chip_isharkl2.h                                *
 ** Author:       billy.zhang                                       *
 ** DATE:         07/11/2016                                        *
 ** Copyright:    2016 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:                                                    *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                       *

 ******************************************************************************/
#ifndef _ISHARKL2_DISPC_GLB_REG_U_H_
#define _ISHARKL2_DISPC_GLB_REG_U_H_

/* DISPC regs offset */
#define DISPC_VERSION		(0x0000)
#define DISPC_CTRL			(0x0004)
#define DISPC_SIZE_XY		(0x0008)
#define DISPC_RSTN			(0x000C)
#define DISPC_SECURE		(0x0010)
#define DISPC_QOS			(0x0014)
#define DISPC_BG_COLOR		(0x001C)

#define DISPC_IMG_CTRL				(0x0030)
#define DISPC_IMG_Y_BASE_ADDR		(0x0020)
#define DISPC_IMG_UV_BASE_ADDR	(0x0024)
#define DISPC_IMG_SIZE_XY			(0x0034)
#define DISPC_IMG_PITCH				(0x0038)
#define DISPC_IMG_DISP_XY			(0x003C)
#define DISPC_IMG_ALPHA			(0x0040)
#define DISPC_IMG_CK				(0x0044)
#define DISPC_IMG_PALLETE			(0x0048)

#define DISPC_OSD_CTRL				(0x0060)
#define DISPC_OSD_BASE_ADDR		(0x0050)
#define DISPC_OSD_SIZE_XY			(0x0064)
#define DISPC_OSD_PITCH				(0x0068)
#define DISPC_OSD_DISP_XY			(0x006c)
#define DISPC_OSD_ALPHA			(0x0070)
#define DISPC_OSD_CK				(0x0074)
#define DISPC_OSD_PALLETE			(0x0078)

#define DISPC_OSD2_CTRL				(0x0090)
#define DISPC_OSD2_BASE_ADDR		(0x0080)
#define DISPC_OSD2_SIZE_XY			(0x0094)
#define DISPC_OSD2_PITCH			(0x0098)
#define DISPC_OSD2_DISP_XY			(0x009c)
#define DISPC_OSD2_ALPHA			(0x00a0)
#define DISPC_OSD2_CK				(0x00a4)
#define DISPC_OSD2_PALLETE			(0x00a8)

#define DISPC_OSD3_CTRL				(0x00c0)
#define DISPC_OSD3_BASE_ADDR		(0x00b0)
#define DISPC_OSD3_SIZE_XY			(0x00c4)
#define DISPC_OSD3_PITCH			(0x00c8)
#define DISPC_OSD3_DISP_XY			(0x00cc)
#define DISPC_OSD3_ALPHA			(0x00d0)
#define DISPC_OSD3_CK				(0x00d4)
#define DISPC_OSD3_PALLETE			(0x00d8)

#define DISPC_OSD4_CTRL				(0x00f0)
#define DISPC_OSD4_BASE_ADDR		(0x00e0)
#define DISPC_OSD4_SIZE_XY			(0x00f4)
#define DISPC_OSD4_PITCH			(0x00f8)
#define DISPC_OSD4_DISP_XY			(0x00fc)
#define DISPC_OSD4_ALPHA			(0x0100)
#define DISPC_OSD4_CK				(0x0104)
#define DISPC_OSD4_PALLETE			(0x0108)

#define DISPC_OSD5_CTRL				(0x0120)
#define DISPC_OSD5_BASE_ADDR		(0x0110)
#define DISPC_OSD5_SIZE_XY			(0x0124)
#define DISPC_OSD5_PITCH			(0x0128)
#define DISPC_OSD5_DISP_XY			(0x012c)
#define DISPC_OSD5_ALPHA			(0x0130)
#define DISPC_OSD5_CK				(0x0134)
#define DISPC_OSD5_PALLETE			(0x0138)

#define WB_CTRL				(0x0144)
#define WB_BASE_ADDR		(0x0140)
#define WB_PITCH			(0x0148)

#define DISPC_Y2R_CTRL				(0x0150)
#define DISPC_Y2R_Y_PARAM		(0x0154)
#define DISPC_Y2R_U_PARAM		(0x0158)
#define DISPC_Y2R_V_PARAM		(0x015c)

#define DISPC_INT_EN		(0x0160)
#define DISPC_INT_CLR		(0x0164)
#define DISPC_INT_STATUS		(0x0168)
#define DISPC_INT_RAW		(0x016c)

#define DISPC_DPI_CTRL				(0x0170)
#define DISPC_DPI_H_TIMING		(0x0174)
#define DISPC_DPI_V_TIMING		(0x0178)
#define DISPC_DPI_STS0				(0x018c)
#define DISPC_DPI_STS1				(0x0190)

#define DISPC_STS0			(0x0194)
#define DISPC_STS1			(0x0198)
#define DISPC_STS2			(0x019C)

#define SHDW_OSD_BASE_ADDR			(0x0250)


#define	SPRD_MIPI_DPHY_GEN2

#define G_DISPC_AHB_BASE	SPRD_DISPAHB_BASE
#define G_DISPC_CLK_BASE	SPRD_DCAMPCKG_BASE
#define G_DISPC0_BASE		SPRD_DPU_BASE
static inline u32 dispc_read(unsigned long reg)
{
	return __raw_readl(G_DISPC0_BASE + reg);
}

static inline void dispc_write(u32 value, unsigned long reg)
{
	__raw_writel(value, (G_DISPC0_BASE + reg));
}

static inline void dispc_set_bits(u32 bits, unsigned long reg)
{
	dispc_write(dispc_read(reg) | bits, reg);
}

static inline void dispc_clear_bits(u32 bits, unsigned long reg)
{
	dispc_write(dispc_read(reg) & ~bits, reg);
}

#define DSI_CTL_BEGIN			SPRD_DSI0_BASE

#define DSI_AHB_SOFT_RST		REG_DISP_AHB_AHB_EB
#define BIT_DSI_SOFT_RST		(BIT_DISP_AHB_DSI0_SOFT_RST)

#define DSI_REG_EB			REG_DISP_AHB_AHB_EB
#define DSI_BIT_EB			BIT_DISP_AHB_DSI0_EB

#define DISPC_AHB_SOFT_RST		REG_DISP_AHB_AHB_EB
#define BIT_DISPC_SOFT_RST		BIT_DISP_AHB_DISPC0_SOFT_RST

#define DISPC_AHB_EN			(REG_DISP_AHB_AHB_EB)
#define BIT_DISPC_AHB_EN		(BIT_DISP_AHB_DISPC0_EB)

#define DISPC_CORE_EN			(REG_DISP_AHB_AHB_EB)
#define BIT_DISPC_CORE_EN		(BIT_DISP_AHB_CKG_EB)

#define DISPC_EMC_EN			(REG_DISP_AHB_AHB_EB)
#define BIT_DISPC_EMC_EN		(BIT_DISP_AHB_DISPC_MTX_EB)

#define REG_DISP_CLK_CORE_clk_dispc0_cfg                  (SPRD_DCAMPCKG_BASE + 0x24)/*clk_dispc0_cfg*/
#define REG_DISP_CLK_CORE_clk_dispc0_dpi_cfg              (SPRD_DCAMPCKG_BASE + 0x28)/*clk_dispc0_dpi_cfg*/

#define DISPC_PLL_SEL_CFG		REG_DISP_CLK_CORE_clk_dispc0_cfg
#define BITS_DISPC_PLL_SEL_CFG		0
#define BIT_DISPC_PLL_SEL_MSK		(0x3 << 0)

#define DISPC_PLL_DIV_CFG		REG_DISP_CLK_CORE_clk_dispc0_cfg
#define BITS_DISPC_PLL_DIV_CFG		8
#define BIT_DISPC_PLL_DIV_MSK		(0x7 << 8)

#define DISPC_DPI_SEL_CFG		REG_DISP_CLK_CORE_clk_dispc0_dpi_cfg	
#define BITS_DISPC_DPI_SEL_CFG		0
#define BIT_DISPC_DPI_SEL_MSK		(0x3 << 0)

#define DISPC_DPI_DIV_CFG		REG_DISP_CLK_CORE_clk_dispc0_dpi_cfg
#define BITS_DISPC_DPI_DIV_CFG		8
#define BIT_DISPC_DPI_DIV_MSK		(0x7 << 8)
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

#define DISPC_PLL_SEL_DEFAULT	DISPC_PLL_SEL_384M
#if defined(CONFIG_FB_LCD_ST7701_MIPI)
#define DISPC_DPI_SEL_DEFAULT DISPC_DPI_SEL_256M
#else
#define DISPC_DPI_SEL_DEFAULT	DISPC_DPI_SEL_153_6M
#endif

#define DISPC_PLL_DIV_DEFAULT	0
#define DISPC_DPI_DIV_DEFAULT	1

#if defined(CONFIG_FB_LCD_ST7701_MIPI)
#define SPRDFB_DPI_CLOCK_SRC (256000000)
#else
#define SPRDFB_DPI_CLOCK_SRC (153600000)
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

#define INTERLEAVE_MODE_OFFSET	1
#define INTERLEAVE_MODE_MASK	(0x3 << INTERLEAVE_MODE_OFFSET)

#define INTERLEAVE_SEL_OFFSET	0
#define INTERLEAVE_SEL_MASK	(0x1 << INTERLEAVE_SEL_OFFSET)

void misc_noc_ctrl(unsigned long base, unsigned int mode, unsigned int sel);
void dsi_enable(void);
void dsi_disable(void);
void dispc_early_configs(void);
void dispc_print_clk(void);
int disp_domain_power_ctrl(int enable);

#endif

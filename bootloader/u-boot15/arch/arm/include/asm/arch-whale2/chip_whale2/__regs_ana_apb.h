/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef __H_REGS_ANA_APB_HEADFILE_H__
#define __H_REGS_ANA_APB_HEADFILE_H__



#define REG_ANA_APB_RST_CTRL                   SCI_ADDR(REGS_ANA_APB_BASE, 0x0000 )
#define REG_ANA_APB_PWR_CTRL0                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0004 )
#define REG_ANA_APB_PWR_CTRL1                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0008 )
#define REG_ANA_APB_REC_XTAL_CFG               SCI_ADDR(REGS_ANA_APB_BASE, 0x000C )
#define REG_ANA_APB_BB_BG_CTRL                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0010 )
#define REG_ANA_APB_M_AAPC_CFG                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0014 )
#define REG_ANA_APB_S_AAPC_CFG                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0018 )
#define REG_ANA_APB_RTC100M_CFG                SCI_ADDR(REGS_ANA_APB_BASE, 0x0020 )
#define REG_ANA_APB_MPLL0_CFG0                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0024 )
#define REG_ANA_APB_MPLL0_CFG1                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0028 )
#define REG_ANA_APB_MPLL1_CFG0                 SCI_ADDR(REGS_ANA_APB_BASE, 0x002C )
#define REG_ANA_APB_MPLL1_CFG1                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0030 )
#define REG_ANA_APB_DPLL0_CFG0                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0034 )
#define REG_ANA_APB_DPLL0_CFG1                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0038 )
#define REG_ANA_APB_DPLL1_CFG0                 SCI_ADDR(REGS_ANA_APB_BASE, 0x003C )
#define REG_ANA_APB_DPLL1_CFG1                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0040 )
#define REG_ANA_APB_RPLL0_CFG0                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0044 )
#define REG_ANA_APB_RPLL0_CFG1                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0048 )
#define REG_ANA_APB_RPLL0_CFG2                 SCI_ADDR(REGS_ANA_APB_BASE, 0x004C )
#define REG_ANA_APB_RPLL1_CFG0                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0050 )
#define REG_ANA_APB_RPLL1_CFG1                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0054 )
#define REG_ANA_APB_RPLL1_CFG2                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0058 )
#define REG_ANA_APB_TWPLL_CFG1                 SCI_ADDR(REGS_ANA_APB_BASE, 0x005C )
#define REG_ANA_APB_TWPLL_CFG2                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0060 )
#define REG_ANA_APB_LTEPLL_CFG1                SCI_ADDR(REGS_ANA_APB_BASE, 0x0064 )
#define REG_ANA_APB_LTEPLL_CFG2                SCI_ADDR(REGS_ANA_APB_BASE, 0x0068 )
#define REG_ANA_APB_LTECAPLL_CFG1              SCI_ADDR(REGS_ANA_APB_BASE, 0x006C )
#define REG_ANA_APB_LTECAPLL_CFG2              SCI_ADDR(REGS_ANA_APB_BASE, 0x0070 )
#define REG_ANA_APB_M_LVDSRF_PLL_CFG1          SCI_ADDR(REGS_ANA_APB_BASE, 0x0074 )
#define REG_ANA_APB_M_LVDSRF_PLL_CFG2          SCI_ADDR(REGS_ANA_APB_BASE, 0x0078 )
#define REG_ANA_APB_M_LVDSRF_CFG1              SCI_ADDR(REGS_ANA_APB_BASE, 0x007C )
#define REG_ANA_APB_M_LVDSRF_CFG2              SCI_ADDR(REGS_ANA_APB_BASE, 0x0080 )
#define REG_ANA_APB_M_LVDSRF_CFG3              SCI_ADDR(REGS_ANA_APB_BASE, 0x0084 )
#define REG_ANA_APB_S_LVDSRF_PLL_CFG1          SCI_ADDR(REGS_ANA_APB_BASE, 0x0088 )
#define REG_ANA_APB_S_LVDSRF_PLL_CFG2          SCI_ADDR(REGS_ANA_APB_BASE, 0x008C )
#define REG_ANA_APB_S_LVDSRF_CFG1              SCI_ADDR(REGS_ANA_APB_BASE, 0x0090 )
#define REG_ANA_APB_S_LVDSRF_CFG2              SCI_ADDR(REGS_ANA_APB_BASE, 0x0094 )
#define REG_ANA_APB_S_LVDSRF_CFG3              SCI_ADDR(REGS_ANA_APB_BASE, 0x0098 )
#define REG_ANA_APB_GPLL_CFG1                  SCI_ADDR(REGS_ANA_APB_BASE, 0x009C )
#define REG_ANA_APB_GPLL_CFG2                  SCI_ADDR(REGS_ANA_APB_BASE, 0x00A0 )
#define REG_ANA_APB_THM0_CFG                   SCI_ADDR(REGS_ANA_APB_BASE, 0x00B0 )
#define REG_ANA_APB_THM1_CFG                   SCI_ADDR(REGS_ANA_APB_BASE, 0x00B4 )
#define REG_ANA_APB_THM2_CFG                   SCI_ADDR(REGS_ANA_APB_BASE, 0x00B8 )
#define REG_ANA_APB_CPPLL_CFG1                 SCI_ADDR(REGS_ANA_APB_BASE, 0x00C4 )
#define REG_ANA_APB_CPPLL_CFG2                 SCI_ADDR(REGS_ANA_APB_BASE, 0x00C8 )
#define REG_ANA_APB_PLL_BIST_EN                SCI_ADDR(REGS_ANA_APB_BASE, 0x00CC )
#define REG_ANA_APB_PLL_BIST_CNT1              SCI_ADDR(REGS_ANA_APB_BASE, 0x00D0 )
#define REG_ANA_APB_PLL_BIST_CNT2              SCI_ADDR(REGS_ANA_APB_BASE, 0x00D4 )
#define REG_ANA_APB_PLL_BIST_CNT3              SCI_ADDR(REGS_ANA_APB_BASE, 0x00D8 )
#define REG_ANA_APB_PLL_BIST_CNT4              SCI_ADDR(REGS_ANA_APB_BASE, 0x00DC )
#define REG_ANA_APB_PLL_BIST_CNT5              SCI_ADDR(REGS_ANA_APB_BASE, 0x00E0 )
#define REG_ANA_APB_USB30_PHY_TUNE1            SCI_ADDR(REGS_ANA_APB_BASE, 0x00E4 )
#define REG_ANA_APB_USB30_PHY_TUNE2            SCI_ADDR(REGS_ANA_APB_BASE, 0x00E8 )
#define REG_ANA_APB_USB30_PHY_TEST             SCI_ADDR(REGS_ANA_APB_BASE, 0x00EC )
#define REG_ANA_APB_USB30_PHY_CTRL1            SCI_ADDR(REGS_ANA_APB_BASE, 0x00F0 )
#define REG_ANA_APB_USB30_PHY_CTRL2            SCI_ADDR(REGS_ANA_APB_BASE, 0x00F4 )
#define REG_ANA_APB_USB30_PHY_DBG1             SCI_ADDR(REGS_ANA_APB_BASE, 0x00F8 )
#define REG_ANA_APB_USB30_PHY_DBG2             SCI_ADDR(REGS_ANA_APB_BASE, 0x00FC )
#define REG_ANA_APB_MIPI_PHY_CTRL1             SCI_ADDR(REGS_ANA_APB_BASE, 0x0100 )
#define REG_ANA_APB_MIPI_PHY_CTRL2             SCI_ADDR(REGS_ANA_APB_BASE, 0x0104 )
#define REG_ANA_APB_MIPI_PHY_CTRL3             SCI_ADDR(REGS_ANA_APB_BASE, 0x0108 )
#define REG_ANA_APB_MIPI_PHY_CTRL4             SCI_ADDR(REGS_ANA_APB_BASE, 0x010C )
#define REG_ANA_APB_PROBE_CAL                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0110 )
#define REG_ANA_APB_AUX0_CAL                   SCI_ADDR(REGS_ANA_APB_BASE, 0x0114 )
#define REG_ANA_APB_AUX1_CAL                   SCI_ADDR(REGS_ANA_APB_BASE, 0x0118 )
#define REG_ANA_APB_AUX2_CAL                   SCI_ADDR(REGS_ANA_APB_BASE, 0x011C )
#define REG_ANA_APB_AAPC_GEN_CFG               SCI_ADDR(REGS_ANA_APB_BASE, 0x0120 )
#define REG_ANA_APB_BB_PLL_VSET                SCI_ADDR(REGS_ANA_APB_BASE, 0x0124 )
#define REG_ANA_APB_PLL_FREQ_CAL_CFG           SCI_ADDR(REGS_ANA_APB_BASE, 0x012C )
#define REG_ANA_APB_PROBE_RESULT               SCI_ADDR(REGS_ANA_APB_BASE, 0x0130 )
#define REG_ANA_APB_AUX0_RESULT                SCI_ADDR(REGS_ANA_APB_BASE, 0x0134 )
#define REG_ANA_APB_AUX1_RESULT                SCI_ADDR(REGS_ANA_APB_BASE, 0x0138 )
#define REG_ANA_APB_AUX2_RESULT                SCI_ADDR(REGS_ANA_APB_BASE, 0x013C )
#define REG_ANA_APB_PLL_TEST_FLAG              SCI_ADDR(REGS_ANA_APB_BASE, 0x014C )
#define REG_ANA_APB_MIPI_TEST                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0150 )
#define REG_ANA_APB_MIPI_TEST2                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0154 )
#define REG_ANA_APB_MIPI_CSI0_RESERVE          SCI_ADDR(REGS_ANA_APB_BASE, 0x0158 )
#define REG_ANA_APB_MIPI_CSI1_RESERVE          SCI_ADDR(REGS_ANA_APB_BASE, 0x015C )
#define REG_ANA_APB_MIPI_DSI0_RESERVE          SCI_ADDR(REGS_ANA_APB_BASE, 0x0160 )
#define REG_ANA_APB_MIPI_DSI1_RESERVE          SCI_ADDR(REGS_ANA_APB_BASE, 0x0164 )
#define REG_ANA_APB_MIPI_DSI_TXSKEW_CTRL       SCI_ADDR(REGS_ANA_APB_BASE, 0x0168 )
#define REG_ANA_APB_MACRO_POWER_FLAG0          SCI_ADDR(REGS_ANA_APB_BASE, 0x0174 )
#define REG_ANA_APB_MACRO_POWER_FLAG1          SCI_ADDR(REGS_ANA_APB_BASE, 0x0178 )
#define REG_ANA_APB_MACRO_RESET_FLAG0          SCI_ADDR(REGS_ANA_APB_BASE, 0x017C )
#define REG_ANA_APB_MACRO_CHECK_FLAG0          SCI_ADDR(REGS_ANA_APB_BASE, 0x0180 )
#define REG_ANA_APB_MACRO_CHECK_FLAG1          SCI_ADDR(REGS_ANA_APB_BASE, 0x0184 )
#define REG_ANA_APB_PLL_CLKOUT_AUTO_GATE0      SCI_ADDR(REGS_ANA_APB_BASE, 0x0188 )
#define REG_ANA_APB_PLL_CLKOUT_AUTO_GATE1      SCI_ADDR(REGS_ANA_APB_BASE, 0x018C )
#define REG_ANA_APB_AGLB_SEL0                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0200 )
#define REG_ANA_APB_AGLB_SEL1                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0204 )
#define REG_ANA_APB_MPLL_BIST_CNT              SCI_ADDR(REGS_ANA_APB_BASE, 0x0208 )
#define REG_ANA_APB_EFUSE_CFG                  SCI_ADDR(REGS_ANA_APB_BASE, 0x020C )
#define REG_ANA_APB_VDROP_SNSR_CTRL            SCI_ADDR(REGS_ANA_APB_BASE, 0x0210 )
#define REG_ANA_APB_USB30_PHY_CTRL3            SCI_ADDR(REGS_ANA_APB_BASE, 0x0214 )
#define REG_ANA_APB_RESONANCE_CTRL1            SCI_ADDR(REGS_ANA_APB_BASE, 0x0218 )
#define REG_ANA_APB_RESONANCE_CTRL2            SCI_ADDR(REGS_ANA_APB_BASE, 0x021C )
#define REG_ANA_APB_MPLL_CFG                   SCI_ADDR(REGS_ANA_APB_BASE, 0x0220 )
#define REG_ANA_APB_REC_XTAL_CFG1              SCI_ADDR(REGS_ANA_APB_BASE, 0x0224 )
#define REG_ANA_APB_THM4_CFG                   SCI_ADDR(REGS_ANA_APB_BASE, 0x0228 )
#define REG_ANA_APB_THM5_CFG                   SCI_ADDR(REGS_ANA_APB_BASE, 0x022C )
#define REG_ANA_APB_DPLL0_CFG2                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0230 )
#define REG_ANA_APB_DPLL1_CFG2                 SCI_ADDR(REGS_ANA_APB_BASE, 0x0234 )
#define REG_ANA_APB_MIPI_PHY_CTRL5             SCI_ADDR(REGS_ANA_APB_BASE, 0x0238 )
#define REG_ANA_APB_DEBUG_LOG_CTRL             SCI_ADDR(REGS_ANA_APB_BASE, 0x023C )
#define REG_ANA_APB_BB_TEST_CLK_SCFG           SCI_ADDR(REGS_ANA_APB_BASE, 0x0240 )
#define REG_ANA_APB_LTEPLL_CFG3                SCI_ADDR(REGS_ANA_APB_BASE, 0x0244 )
#define REG_ANA_APB_LTECAPLL_CFG3              SCI_ADDR(REGS_ANA_APB_BASE, 0x0248 )
#define REG_ANA_APB_MIPI_PHY_CTRL6             SCI_ADDR(REGS_ANA_APB_BASE, 0x024C )
#define REG_ANA_APB_MIPI_TRIM_SEL              SCI_ADDR(REGS_ANA_APB_BASE, 0x0250 )
#define REG_ANA_APB_RESERVED_CTRL              SCI_ADDR(REGS_ANA_APB_BASE, 0x0254 )
#define REG_ANA_APB_MIPI_APB_CGEN              SCI_ADDR(REGS_ANA_APB_BASE, 0x0258 )
#define REG_ANA_APB_UPLL_CFG1                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0260 )
#define REG_ANA_APB_UPLL_CFG2                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0264 )
#define REG_ANA_APB_UPLL_CFG3                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0268 )
#define REG_ANA_APB_UPLL_BIST                  SCI_ADDR(REGS_ANA_APB_BASE, 0x026C )
#define REG_ANA_APB_UPLL_CFG4                  SCI_ADDR(REGS_ANA_APB_BASE, 0x0270 )
#define REG_ANA_APB_SW_TEST                    SCI_ADDR(REGS_ANA_APB_BASE, 0x0404 )
#define REG_ANA_APB_ANLG_RESERVED1             SCI_ADDR(REGS_ANA_APB_BASE, 0x0408 )
#define REG_ANA_APB_ANLG_RESERVED2             SCI_ADDR(REGS_ANA_APB_BASE, 0x040C )

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RST_CTRL
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_PHY_SOFT_RST                             BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PWR_CTRL0
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_CPPLL_PD                                       BIT(18)
#define BIT_ANA_APB_GPLL_PD                                        BIT(17)
#define BIT_ANA_APB_S_LVDSRF_LVPLL_PD                              BIT(16)
#define BIT_ANA_APB_M_LVDSRF_LVPLL_PD                              BIT(15)
#define BIT_ANA_APB_LPLL1_PD                                       BIT(14)
#define BIT_ANA_APB_LPLL0_PD                                       BIT(13)
#define BIT_ANA_APB_TWPLL_PD                                       BIT(12)
#define BIT_ANA_APB_RPLL1_PD                                       BIT(11)
#define BIT_ANA_APB_RPLL0_PD                                       BIT(10)
#define BIT_ANA_APB_DPLL1_PD                                       BIT(9)
#define BIT_ANA_APB_DPLL0_PD                                       BIT(8)
#define BIT_ANA_APB_MPLL1_PD                                       BIT(7)
#define BIT_ANA_APB_MPLL0_PD                                       BIT(6)
#define BIT_ANA_APB_S_AAPC_PD                                      BIT(5)
#define BIT_ANA_APB_M_AAPC_PD                                      BIT(4)
#define BIT_ANA_APB_BB_BG_PD                                       BIT(3)
#define BIT_ANA_APB_REC_32MHZ_1_BUF_PD                             BIT(2)
#define BIT_ANA_APB_REC_32MHZ_0_BUF_PD                             BIT(1)
#define BIT_ANA_APB_REC_26MHZ_0_BUF_PD                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PWR_CTRL1
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_PS_PD                                    BIT(18)
#define BIT_ANA_APB_FORCE_DSI_PHY_SHUTDOWNZ_S                      BIT(11)
#define BIT_ANA_APB_FORCE_DSI_PHY_SHUTDOWNZ_M                      BIT(10)
#define BIT_ANA_APB_FORCE_CSI0_PHY_SHUTDOWNZ                       BIT(9)
#define BIT_ANA_APB_FORCE_CSI1_PHY_SHUTDOWNZ                       BIT(8)
#define BIT_ANA_APB_MIPI_DSI_PS_PD_S_S                             BIT(7)
#define BIT_ANA_APB_MIPI_DSI_PS_PD_L_S                             BIT(6)
#define BIT_ANA_APB_MIPI_DSI_PS_PD_S_M                             BIT(5)
#define BIT_ANA_APB_MIPI_DSI_PS_PD_L_M                             BIT(4)
#define BIT_ANA_APB_MIPI_CSI0_PS_PD_S                              BIT(3)
#define BIT_ANA_APB_MIPI_CSI0_PS_PD_L                              BIT(2)
#define BIT_ANA_APB_MIPI_CSI1_PS_PD_S                              BIT(1)
#define BIT_ANA_APB_MIPI_CSI1_PS_PD_L                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_REC_XTAL_CFG
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_PROBE_SEL(x)                                   (((x) & 0x3F) << 8)
#define BIT_ANA_APB_SINDRV_ENA_SQUARE                              BIT(7)
#define BIT_ANA_APB_SINDRV_ENA                                     BIT(6)
#define BIT_ANA_APB_REC_32MHZ_1_CUR_SEL                            BIT(2)
#define BIT_ANA_APB_REC_32MHZ_0_CUR_SEL                            BIT(1)
#define BIT_ANA_APB_REC_26MHZ_0_CUR_SEL                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_BB_BG_CTRL
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_ANA_BB_RESERVE(x)                              (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_BB_CON_BG                                      BIT(2)
#define BIT_ANA_APB_BB_BG_RBIAS_EN                                 BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_M_AAPC_CFG
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_AAPC_G2(x)                                     (((x) & 0x3) << 26)
#define BIT_ANA_APB_AAPC_G1(x)                                     (((x) & 0x3) << 24)
#define BIT_ANA_APB_AAPC_G0(x)                                     (((x) & 0x3) << 22)
#define BIT_ANA_APB_M_AAPC_SEL                                     BIT(21)
#define BIT_ANA_APB_M_AAPC_BPRES                                   BIT(20)
#define BIT_ANA_APB_M_AAPC_RESERVED(x)                             (((x) & 0x3) << 18)
#define BIT_ANA_APB_M_APCOUT_SEL(x)                                (((x) & 0x3) << 16)
#define BIT_ANA_APB_M_AAPC_LOW_V_CON                               BIT(15)
#define BIT_ANA_APB_M_AAPC_D(x)                                    (((x) & 0x3FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_S_AAPC_CFG
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_S_AAPC_SEL                                     BIT(21)
#define BIT_ANA_APB_S_AAPC_BPRES                                   BIT(20)
#define BIT_ANA_APB_S_AAPC_RESERVED(x)                             (((x) & 0x3) << 18)
#define BIT_ANA_APB_S_APCOUT_SEL(x)                                (((x) & 0x3) << 16)
#define BIT_ANA_APB_S_AAPC_LOW_V_CON                               BIT(15)
#define BIT_ANA_APB_S_AAPC_D(x)                                    (((x) & 0x3FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RTC100M_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RTC100M_RSTB                                   BIT(23)
#define BIT_ANA_APB_RTC100M_EN                                     BIT(22)
#define BIT_ANA_APB_RTC100M_RC_C(x)                                (((x) & 0x1FF) << 13)
#define BIT_ANA_APB_RTC100M_RESERVE(x)                             (((x) & 0xFF) << 5)
#define BIT_ANA_APB_RTC100M_I_C(x)                                 (((x) & 0xF) << 1)
#define BIT_ANA_APB_RTC100M_CHOP_EN                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MPLL0_CFG0
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MPLL0_VSET(x)                                  (((x) & 0x7) << 29)
#define BIT_ANA_APB_MPLL0_RESERVE(x)                               (((x) & 0xFF) << 21)
#define BIT_ANA_APB_MPLL0_LOCK_DONE                                BIT(20)
#define BIT_ANA_APB_MPLL0_DIV_S                                    BIT(19)
#define BIT_ANA_APB_MPLL0_MOD_EN                                   BIT(18)
#define BIT_ANA_APB_MPLL0_SDM_EN                                   BIT(17)
#define BIT_ANA_APB_MPLL0_LPF(x)                                   (((x) & 0x7) << 13)
#define BIT_ANA_APB_MPLL0_IBIAS(x)                                 (((x) & 0x3) << 11)
#define BIT_ANA_APB_MPLL0_RST                                      BIT(10)
#define BIT_ANA_APB_MPLL0_CLKOUT_EN                                BIT(9)
#define BIT_ANA_APB_MPLL0_DIV32_EN                                 BIT(8)
#define BIT_ANA_APB_MPLL0_FRELESS1G                                BIT(7)
#define BIT_ANA_APB_MPLL0_N(x)                                     (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MPLL0_CFG1
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MPLL0_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANA_APB_MPLL0_POSTDIV                                  BIT(24)
#define BIT_ANA_APB_MPLL0_PD_SEL                                   BIT(23)
#define BIT_ANA_APB_MPLL0_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MPLL1_CFG0
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MPLL1_VSET(x)                                  (((x) & 0x7) << 29)
#define BIT_ANA_APB_MPLL1_RESERVE(x)                               (((x) & 0xFF) << 21)
#define BIT_ANA_APB_MPLL1_LOCK_DONE                                BIT(20)
#define BIT_ANA_APB_MPLL1_DIV_S                                    BIT(19)
#define BIT_ANA_APB_MPLL1_MOD_EN                                   BIT(18)
#define BIT_ANA_APB_MPLL1_SDM_EN                                   BIT(17)
#define BIT_ANA_APB_MPLL1_LPF(x)                                   (((x) & 0x7) << 13)
#define BIT_ANA_APB_MPLL1_IBIAS(x)                                 (((x) & 0x3) << 11)
#define BIT_ANA_APB_MPLL1_RST                                      BIT(10)
#define BIT_ANA_APB_MPLL1_CLKOUT_EN                                BIT(9)
#define BIT_ANA_APB_MPLL1_DIV32_EN                                 BIT(8)
#define BIT_ANA_APB_MPLL1_N(x)                                     (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MPLL1_CFG1
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MPLL1_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANA_APB_MPLL1_PREDIV                                   BIT(24)
#define BIT_ANA_APB_MPLL1_PD_SEL                                   BIT(23)
#define BIT_ANA_APB_MPLL1_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_DPLL0_CFG0
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DPLL0_RESERVE(x)                               (((x) & 0xFF) << 21)
#define BIT_ANA_APB_DPLL0_DIV_SEL(x)                               (((x) & 0xF) << 17)
#define BIT_ANA_APB_DPLL0_LOCK_DONE                                BIT(16)
#define BIT_ANA_APB_DPLL0_DIV_S                                    BIT(15)
#define BIT_ANA_APB_DPLL0_MOD_EN                                   BIT(14)
#define BIT_ANA_APB_DPLL0_SDM_EN                                   BIT(13)
#define BIT_ANA_APB_DPLL0_LPF(x)                                   (((x) & 0x7) << 10)
#define BIT_ANA_APB_DPLL0_IBIAS(x)                                 (((x) & 0x3) << 8)
#define BIT_ANA_APB_DPLL0_CLKOUT_EN                                BIT(7)
#define BIT_ANA_APB_DPLL0_N(x)                                     (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_DPLL0_CFG1
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DPLL0_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANA_APB_DPLL0_PD_SEL                                   BIT(24)
#define BIT_ANA_APB_DPLL0_RST                                      BIT(23)
#define BIT_ANA_APB_DPLL0_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_DPLL1_CFG0
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DPLL1_RESERVE(x)                               (((x) & 0xFF) << 21)
#define BIT_ANA_APB_DPLL1_DIV_SEL(x)                               (((x) & 0xF) << 17)
#define BIT_ANA_APB_DPLL1_LOCK_DONE                                BIT(16)
#define BIT_ANA_APB_DPLL1_DIV_S                                    BIT(15)
#define BIT_ANA_APB_DPLL1_MOD_EN                                   BIT(14)
#define BIT_ANA_APB_DPLL1_SDM_EN                                   BIT(13)
#define BIT_ANA_APB_DPLL1_LPF(x)                                   (((x) & 0x7) << 10)
#define BIT_ANA_APB_DPLL1_IBIAS(x)                                 (((x) & 0x3) << 8)
#define BIT_ANA_APB_DPLL1_CLKOUT_EN                                BIT(7)
#define BIT_ANA_APB_DPLL1_N(x)                                     (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_DPLL1_CFG1
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DPLL1_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANA_APB_DPLL1_PD_SEL                                   BIT(24)
#define BIT_ANA_APB_DPLL1_RST                                      BIT(23)
#define BIT_ANA_APB_DPLL1_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RPLL0_CFG0
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RPLL0_VSET(x)                                  (((x) & 0x7) << 25)
#define BIT_ANA_APB_RPLL0_PD_SEL                                   BIT(24)
#define BIT_ANA_APB_RPLL0_RST                                      BIT(23)
#define BIT_ANA_APB_RPLL0_N(x)                                     (((x) & 0x7F) << 16)
#define BIT_ANA_APB_RPLL0_IBIAS(x)                                 (((x) & 0x3) << 14)
#define BIT_ANA_APB_RPLL0_LPF(x)                                   (((x) & 0x7) << 11)
#define BIT_ANA_APB_RPLL0_NINT(x)                                  (((x) & 0x7F) << 4)
#define BIT_ANA_APB_RPLL0_DIV_S                                    BIT(3)
#define BIT_ANA_APB_RPLL0_REF_SEL(x)                               (((x) & 0x3) << 1)
#define BIT_ANA_APB_RPLL0_LOCK_DONE                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RPLL0_CFG1
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RPLL0_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RPLL0_CFG2
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RPLL0_26M_DIV(x)                               (((x) & 0x3F) << 19)
#define BIT_ANA_APB_RPLL0_DIV1_EN                                  BIT(18)
#define BIT_ANA_APB_RPLL0_SDM_EN                                   BIT(17)
#define BIT_ANA_APB_RPLL0_MOD_EN                                   BIT(16)
#define BIT_ANA_APB_RPLL0_RESERVE(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RPLL1_CFG0
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RPLL1_VSET(x)                                  (((x) & 0x7) << 25)
#define BIT_ANA_APB_RPLL1_PD_SEL                                   BIT(24)
#define BIT_ANA_APB_RPLL1_RST                                      BIT(23)
#define BIT_ANA_APB_RPLL1_N(x)                                     (((x) & 0x7F) << 16)
#define BIT_ANA_APB_RPLL1_IBIAS(x)                                 (((x) & 0x3) << 14)
#define BIT_ANA_APB_RPLL1_LPF(x)                                   (((x) & 0x7) << 11)
#define BIT_ANA_APB_RPLL1_NINT(x)                                  (((x) & 0x7F) << 4)
#define BIT_ANA_APB_RPLL1_DIV_S                                    BIT(3)
#define BIT_ANA_APB_RPLL1_REF_SEL(x)                               (((x) & 0x3) << 1)
#define BIT_ANA_APB_RPLL1_LOCK_DONE                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RPLL1_CFG1
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RPLL1_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RPLL1_CFG2
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RPLL1_26M_DIV(x)                               (((x) & 0x3F) << 19)
#define BIT_ANA_APB_RPLL1_DIV1_EN                                  BIT(18)
#define BIT_ANA_APB_RPLL1_SDM_EN                                   BIT(17)
#define BIT_ANA_APB_RPLL1_MOD_EN                                   BIT(16)
#define BIT_ANA_APB_RPLL1_RESERVE(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_TWPLL_CFG1
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_TWPLL_RESERVE(x)                               (((x) & 0xFF) << 22)
#define BIT_ANA_APB_TWPLL_LOCK_DONE                                BIT(21)
#define BIT_ANA_APB_TWPLL_DIV_S                                    BIT(20)
#define BIT_ANA_APB_TWPLL_MOD_EN                                   BIT(19)
#define BIT_ANA_APB_TWPLL_SDM_EN                                   BIT(18)
#define BIT_ANA_APB_TWPLL_LPF(x)                                   (((x) & 0x7) << 15)
#define BIT_ANA_APB_TWPLL_IBIAS(x)                                 (((x) & 0x3) << 13)
#define BIT_ANA_APB_TWPLL_CLKOUT_EN                                BIT(12)
#define BIT_ANA_APB_TWPLL_DIV1_EN                                  BIT(11)
#define BIT_ANA_APB_TWPLL_DIV2_EN                                  BIT(10)
#define BIT_ANA_APB_TWPLL_DIV3_EN                                  BIT(9)
#define BIT_ANA_APB_TWPLL_DIV5_EN                                  BIT(8)
#define BIT_ANA_APB_TWPLL_DIV7_EN                                  BIT(7)
#define BIT_ANA_APB_TWPLL_N(x)                                     (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_TWPLL_CFG2
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_TWPLL_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANA_APB_TWPLL_PD_SEL                                   BIT(24)
#define BIT_ANA_APB_TWPLL_RST                                      BIT(23)
#define BIT_ANA_APB_TWPLL_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_LTEPLL_CFG1
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_LPLL0_LOCK_DONE                                BIT(31)
#define BIT_ANA_APB_LPLL0_REF_SEL(x)                               (((x) & 0x7) << 28)
#define BIT_ANA_APB_LPLL0_DIV_S                                    BIT(27)
#define BIT_ANA_APB_LPLL0_MOD_EN                                   BIT(26)
#define BIT_ANA_APB_LPLL0_SDM_EN                                   BIT(25)
#define BIT_ANA_APB_LPLL0_LPF(x)                                   (((x) & 0x7) << 22)
#define BIT_ANA_APB_LPLL0_IBIAS(x)                                 (((x) & 0x3) << 20)
#define BIT_ANA_APB_LPLL0_RESERVED(x)                              (((x) & 0xFF) << 12)
#define BIT_ANA_APB_LPLL0_CLKOUT_EN                                BIT(11)
#define BIT_ANA_APB_LPLL0_DIV1_EN                                  BIT(10)
#define BIT_ANA_APB_LPLL0_DIV2_EN                                  BIT(9)
#define BIT_ANA_APB_LPLL0_DIV3_EN                                  BIT(8)
#define BIT_ANA_APB_LPLL0_DIV5_EN                                  BIT(7)
#define BIT_ANA_APB_LPLL0_N(x)                                     (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_LTEPLL_CFG2
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_LPLL0_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANA_APB_LPLL0_PD_SEL                                   BIT(24)
#define BIT_ANA_APB_LPLL0_RST                                      BIT(23)
#define BIT_ANA_APB_LPLL0_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_LTECAPLL_CFG1
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_LPLL1_LOCK_DONE                                BIT(31)
#define BIT_ANA_APB_LPLL1_REF_SEL(x)                               (((x) & 0x7) << 28)
#define BIT_ANA_APB_LPLL1_DIV_S                                    BIT(27)
#define BIT_ANA_APB_LPLL1_MOD_EN                                   BIT(26)
#define BIT_ANA_APB_LPLL1_SDM_EN                                   BIT(25)
#define BIT_ANA_APB_LPLL1_LPF(x)                                   (((x) & 0x7) << 22)
#define BIT_ANA_APB_LPLL1_IBIAS(x)                                 (((x) & 0x3) << 20)
#define BIT_ANA_APB_LPLL1_RESERVED(x)                              (((x) & 0xFF) << 12)
#define BIT_ANA_APB_LPLL1_CLKOUT_EN                                BIT(11)
#define BIT_ANA_APB_LPLL1_DIV1_EN                                  BIT(10)
#define BIT_ANA_APB_LPLL1_DIV2_EN                                  BIT(9)
#define BIT_ANA_APB_LPLL1_DIV3_EN                                  BIT(8)
#define BIT_ANA_APB_LPLL1_DIV5_EN                                  BIT(7)
#define BIT_ANA_APB_LPLL1_N(x)                                     (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_LTECAPLL_CFG2
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_LPLL1_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANA_APB_LPLL1_PD_SEL                                   BIT(24)
#define BIT_ANA_APB_LPLL1_RST                                      BIT(23)
#define BIT_ANA_APB_LPLL1_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_M_LVDSRF_PLL_CFG1
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_M_LVDSRF_LVPLL_REFIN(x)                        (((x) & 0x3) << 30)
#define BIT_ANA_APB_M_LVDSRF_NINT(x)                               (((x) & 0x7F) << 23)
#define BIT_ANA_APB_M_LVDSRF_LVPLL_REFCK_SEL(x)                    (((x) & 0x7) << 20)
#define BIT_ANA_APB_M_LVDSRF_PLL_CLKOUT_EN                         BIT(19)
#define BIT_ANA_APB_M_LVDSRF_PLL_DIVOUT_EN                         BIT(18)
#define BIT_ANA_APB_M_LVDSRF_LVPLL_RST                             BIT(16)
#define BIT_ANA_APB_M_LVDSRF_SDM_EN                                BIT(15)
#define BIT_ANA_APB_M_LVDSRF_MOD_EN                                BIT(14)
#define BIT_ANA_APB_M_LVDSRF_LVPLL_DIV_S                           BIT(13)
#define BIT_ANA_APB_M_LVDSRF_LVPLL_IBIAS(x)                        (((x) & 0x3) << 11)
#define BIT_ANA_APB_M_LVDSRF_LVPLL_N(x)                            (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_M_LVDSRF_PLL_CFG2
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_M_LVDSRF_LOCKDONE                              BIT(31)
#define BIT_ANA_APB_M_LVDSRF_LVPLL_LPF(x)                          (((x) & 0x7) << 28)
#define BIT_ANA_APB_M_LVDSRF_KINT(x)                               (((x) & 0xFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_M_LVDSRF_CFG1
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_M_LVDSRF_TXIMP(x)                              (((x) & 0x7) << 28)
#define BIT_ANA_APB_M_LVDSRF_SER_RST                               BIT(27)
#define BIT_ANA_APB_M_LVDSRF_RXIMP_CAL(x)                          (((x) & 0x7) << 24)
#define BIT_ANA_APB_M_LVDSRF_RXIMP_CAL_EN                          BIT(23)
#define BIT_ANA_APB_M_LVDSRF_RXIMP(x)                              (((x) & 0xF) << 19)
#define BIT_ANA_APB_M_LVDSRF_LOWSPEED_MODE                         BIT(18)
#define BIT_ANA_APB_M_LVDSRF_EQ(x)                                 (((x) & 0x3) << 16)
#define BIT_ANA_APB_M_LVDSRF_CUR2X_EN                              BIT(13)
#define BIT_ANA_APB_M_LVDSRF_POSTDIV(x)                            (((x) & 0xF) << 9)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_M_LVDSRF_CFG2
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_M_LVDSRF_OFF_OCT                               BIT(27)
#define BIT_ANA_APB_M_LVDSRF_RESERVE(x)                            (((x) & 0xF) << 23)
#define BIT_ANA_APB_M_LVDSRF_RXCOM(x)                              (((x) & 0x3) << 21)
#define BIT_ANA_APB_M_LVDSRF_TXCOM(x)                              (((x) & 0x3) << 19)
#define BIT_ANA_APB_M_LVDSRF_DES_RST1                              BIT(18)
#define BIT_ANA_APB_M_LVDSRF_DES_RST0                              BIT(17)
#define BIT_ANA_APB_M_LVDSRF_RXPD1                                 BIT(16)
#define BIT_ANA_APB_M_LVDSRF_RXPD0                                 BIT(15)
#define BIT_ANA_APB_M_LVDSRF_PHASE1(x)                             (((x) & 0x1F) << 10)
#define BIT_ANA_APB_M_LVDSRF_PHASE0(x)                             (((x) & 0x1F) << 5)
#define BIT_ANA_APB_M_LVDSRF_TXSW(x)                               (((x) & 0x3) << 3)
#define BIT_ANA_APB_M_LVDSRF_TXPD                                  BIT(2)
#define BIT_ANA_APB_M_LVDSRF_RXBIAS_TRIM(x)                        (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_M_LVDSRF_CFG3
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_M_LVDSRF_RXRESERVED(x)                         (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_M_LVDSRF_TXRESERVED(x)                         (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_S_LVDSRF_PLL_CFG1
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_S_LVDSRF_LVPLL_REFIN(x)                        (((x) & 0x3) << 30)
#define BIT_ANA_APB_S_LVDSRF_NINT(x)                               (((x) & 0x7F) << 23)
#define BIT_ANA_APB_S_LVDSRF_LVPLL_REFCK_SEL(x)                    (((x) & 0x7) << 20)
#define BIT_ANA_APB_S_LVDSRF_PLL_CLKOUT_EN                         BIT(19)
#define BIT_ANA_APB_S_LVDSRF_PLL_DIVOUT_EN                         BIT(18)
#define BIT_ANA_APB_S_LVDSRF_LVPLL_RST                             BIT(16)
#define BIT_ANA_APB_S_LVDSRF_SDM_EN                                BIT(15)
#define BIT_ANA_APB_S_LVDSRF_MOD_EN                                BIT(14)
#define BIT_ANA_APB_S_LVDSRF_LVPLL_DIV_S                           BIT(13)
#define BIT_ANA_APB_S_LVDSRF_LVPLL_IBIAS(x)                        (((x) & 0x3) << 11)
#define BIT_ANA_APB_S_LVDSRF_LVPLL_N(x)                            (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_S_LVDSRF_PLL_CFG2
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_S_LVDSRF_LOCKDONE                              BIT(31)
#define BIT_ANA_APB_S_LVDSRF_LVPLL_LPF(x)                          (((x) & 0x7) << 28)
#define BIT_ANA_APB_S_LVDSRF_KINT(x)                               (((x) & 0xFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_S_LVDSRF_CFG1
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_S_LVDSRF_TXIMP(x)                              (((x) & 0x7) << 28)
#define BIT_ANA_APB_S_LVDSRF_SER_RST                               BIT(27)
#define BIT_ANA_APB_S_LVDSRF_RXIMP_CAL(x)                          (((x) & 0x7) << 24)
#define BIT_ANA_APB_S_LVDSRF_RXIMP_CAL_EN                          BIT(23)
#define BIT_ANA_APB_S_LVDSRF_RXIMP(x)                              (((x) & 0xF) << 19)
#define BIT_ANA_APB_S_LVDSRF_LOWSPEED_MODE                         BIT(18)
#define BIT_ANA_APB_S_LVDSRF_EQ(x)                                 (((x) & 0x3) << 16)
#define BIT_ANA_APB_S_LVDSRF_CUR2X_EN                              BIT(13)
#define BIT_ANA_APB_S_LVDSRF_POSTDIV(x)                            (((x) & 0xF) << 9)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_S_LVDSRF_CFG2
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_S_LVDSRF_OFF_OCT                               BIT(27)
#define BIT_ANA_APB_S_LVDSRF_RESERVE(x)                            (((x) & 0xF) << 23)
#define BIT_ANA_APB_S_LVDSRF_RXCOM(x)                              (((x) & 0x3) << 21)
#define BIT_ANA_APB_S_LVDSRF_TXCOM(x)                              (((x) & 0x3) << 19)
#define BIT_ANA_APB_S_LVDSRF_DES_RST1                              BIT(18)
#define BIT_ANA_APB_S_LVDSRF_DES_RST0                              BIT(17)
#define BIT_ANA_APB_S_LVDSRF_RXPD1                                 BIT(16)
#define BIT_ANA_APB_S_LVDSRF_RXPD0                                 BIT(15)
#define BIT_ANA_APB_S_LVDSRF_PHASE1(x)                             (((x) & 0x1F) << 10)
#define BIT_ANA_APB_S_LVDSRF_PHASE0(x)                             (((x) & 0x1F) << 5)
#define BIT_ANA_APB_S_LVDSRF_TXSW(x)                               (((x) & 0x3) << 3)
#define BIT_ANA_APB_S_LVDSRF_TXPD                                  BIT(2)
#define BIT_ANA_APB_S_LVDSRF_RXBIAS_TRIM(x)                        (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_S_LVDSRF_CFG3
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_S_LVDSRF_RXRESERVED(x)                         (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_S_LVDSRF_TXRESERVED(x)                         (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_GPLL_CFG1
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_GPLL_VSET(x)                                   (((x) & 0x7) << 27)
#define BIT_ANA_APB_GPLL_RESERVE(x)                                (((x) & 0xFF) << 19)
#define BIT_ANA_APB_GPLL_LOCK_DONE                                 BIT(18)
#define BIT_ANA_APB_GPLL_POSTDIV                                   BIT(17)
#define BIT_ANA_APB_GPLL_REF_SEL                                   BIT(16)
#define BIT_ANA_APB_GPLL_DIV_S                                     BIT(15)
#define BIT_ANA_APB_GPLL_MOD_EN                                    BIT(14)
#define BIT_ANA_APB_GPLL_SDM_EN                                    BIT(13)
#define BIT_ANA_APB_GPLL_LPF(x)                                    (((x) & 0x7) << 10)
#define BIT_ANA_APB_GPLL_IBIAS(x)                                  (((x) & 0x3) << 8)
#define BIT_ANA_APB_GPLL_CLKOUT_EN                                 BIT(7)
#define BIT_ANA_APB_GPLL_N(x)                                      (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_GPLL_CFG2
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_GPLL_NINT(x)                                   (((x) & 0x7F) << 25)
#define BIT_ANA_APB_GPLL_PD_SEL                                    BIT(24)
#define BIT_ANA_APB_GPLL_RST                                       BIT(23)
#define BIT_ANA_APB_GPLL_KINT(x)                                   (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_THM0_CFG
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_THM0_ITUNE(x)                                  (((x) & 0xF) << 9)
#define BIT_ANA_APB_THM0_CALI_EN                                   BIT(8)
#define BIT_ANA_APB_THM0_RUN                                       BIT(7)
#define BIT_ANA_APB_THM0_RSTN                                      BIT(6)
#define BIT_ANA_APB_THM0_PD                                        BIT(5)
#define BIT_ANA_APB_THM0_RESERVE(x)                                (((x) & 0xF) << 1)
#define BIT_ANA_APB_THM0_BJT_SEL                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_THM1_CFG
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_THM1_ITUNE(x)                                  (((x) & 0xF) << 8)
#define BIT_ANA_APB_THM1_CALI_EN                                   BIT(7)
#define BIT_ANA_APB_THM1_RUN                                       BIT(6)
#define BIT_ANA_APB_THM1_RSTN                                      BIT(5)
#define BIT_ANA_APB_THM1_PD                                        BIT(4)
#define BIT_ANA_APB_THM1_RESERVE(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_THM2_CFG
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_THM2_ITUNE(x)                                  (((x) & 0xF) << 8)
#define BIT_ANA_APB_THM2_CALI_EN                                   BIT(7)
#define BIT_ANA_APB_THM2_RUN                                       BIT(6)
#define BIT_ANA_APB_THM2_RSTN                                      BIT(5)
#define BIT_ANA_APB_THM2_PD                                        BIT(4)
#define BIT_ANA_APB_THM2_RESERVE(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_CPPLL_CFG1
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_CPPLL_POSTDIV                                  BIT(29)
#define BIT_ANA_APB_CPPLL_VSET(x)                                  (((x) & 0x7) << 26)
#define BIT_ANA_APB_CPPLL_RESERVE(x)                               (((x) & 0xFF) << 18)
#define BIT_ANA_APB_CPPLL_LOCK_DONE                                BIT(17)
#define BIT_ANA_APB_CPPLL_REF_SEL                                  BIT(16)
#define BIT_ANA_APB_CPPLL_DIV_S                                    BIT(15)
#define BIT_ANA_APB_CPPLL_MOD_EN                                   BIT(14)
#define BIT_ANA_APB_CPPLL_SDM_EN                                   BIT(13)
#define BIT_ANA_APB_CPPLL_LPF(x)                                   (((x) & 0x7) << 10)
#define BIT_ANA_APB_CPPLL_IBIAS(x)                                 (((x) & 0x3) << 8)
#define BIT_ANA_APB_CPPLL_CLKOUT_EN                                BIT(7)
#define BIT_ANA_APB_CPPLL_N(x)                                     (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_CPPLL_CFG2
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_CPPLL_NINT(x)                                  (((x) & 0x7F) << 25)
#define BIT_ANA_APB_CPPLL_PD_SEL                                   BIT(24)
#define BIT_ANA_APB_CPPLL_RST                                      BIT(23)
#define BIT_ANA_APB_CPPLL_KINT(x)                                  (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_BIST_EN
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_S_LVDSRF_PLL_BIST_EN                           BIT(8)
#define BIT_ANA_APB_M_LVDSRF_PLL_BIST_EN                           BIT(7)
#define BIT_ANA_APB_CPPLL_BIST_EN                                  BIT(6)
#define BIT_ANA_APB_GPLL_BIST_EN                                   BIT(5)
#define BIT_ANA_APB_TWPLL_BIST_EN                                  BIT(4)
#define BIT_ANA_APB_LPLL1_BIST_EN                                  BIT(3)
#define BIT_ANA_APB_LPLL0_BIST_EN                                  BIT(2)
#define BIT_ANA_APB_RPLL1_BIST_EN                                  BIT(1)
#define BIT_ANA_APB_RPLL0_BIST_EN                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_BIST_CNT1
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RPLL1_BISTCNT(x)                               (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_RPLL0_BISTCNT(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_BIST_CNT2
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_LPLL1_BISTCNT(x)                               (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_LPLL0_BISTCNT(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_BIST_CNT3
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_TWPLL_BISTCNT(x)                               (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_GPLL_BISTCNT(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_BIST_CNT4
// Register Offset : 0x00DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_S_LVDSRF_PLL_BISTCNT(x)                        (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_M_LVDSRF_PLL_BISTCNT(x)                        (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_BIST_CNT5
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_CPPLL_BISTCNT(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_USB30_PHY_TUNE1
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_COMPDISTUNE0(x)                          (((x) & 0x7) << 29)
#define BIT_ANA_APB_USB30_OTGTUNE0(x)                              (((x) & 0x7) << 26)
#define BIT_ANA_APB_USB30_SQRXTUNE0(x)                             (((x) & 0x7) << 23)
#define BIT_ANA_APB_USB30_TXFSLSTUNE0(x)                           (((x) & 0xF) << 19)
#define BIT_ANA_APB_USB30_TXHSXVTUNE0(x)                           (((x) & 0x3) << 17)
#define BIT_ANA_APB_USB30_TXPREEMPAMPTUNE0(x)                      (((x) & 0x3) << 15)
#define BIT_ANA_APB_USB30_TXPREEMPPULSETUNE0                       BIT(14)
#define BIT_ANA_APB_USB30_TXRESTUNE0(x)                            (((x) & 0x3) << 12)
#define BIT_ANA_APB_USB30_TXRISETUNE0(x)                           (((x) & 0x3) << 10)
#define BIT_ANA_APB_USB30_TXVREFTUNE0(x)                           (((x) & 0xF) << 6)
#define BIT_ANA_APB_USB30_LOS_BIAS(x)                              (((x) & 0x7) << 3)
#define BIT_ANA_APB_USB30_TX_VBOOST_LVL(x)                         (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_USB30_PHY_TUNE2
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_RTUNE_ACK                                BIT(30)
#define BIT_ANA_APB_USB30_PCS_RX_LOS_MASK_VAL(x)                   (((x) & 0x3FF) << 20)
#define BIT_ANA_APB_USB30_PCS_TX_DEEMPH_3P5DB(x)                   (((x) & 0x3F) << 14)
#define BIT_ANA_APB_USB30_PCS_TX_DEEMPH_6DB(x)                     (((x) & 0x3F) << 8)
#define BIT_ANA_APB_USB30_PCS_TX_SWING_FULL(x)                     (((x) & 0x7F) << 1)
#define BIT_ANA_APB_USB30_RTUNE_REQ                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_USB30_PHY_TEST
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_IDDIG0_CFG_SEL                           BIT(21)
#define BIT_ANA_APB_USB30_IDDIG0_REG                               BIT(20)
#define BIT_ANA_APB_USB30_VBUSVALID0_CFG_SEL                       BIT(19)
#define BIT_ANA_APB_USB30_VBUSVALID0_REG                           BIT(18)
#define BIT_ANA_APB_USB30_BVALID0_CFG_SEL                          BIT(17)
#define BIT_ANA_APB_USB30_BVALID0_REG                              BIT(16)
#define BIT_ANA_APB_USB30_PIPEP_POWERPRESENT_CFG_SEL               BIT(15)
#define BIT_ANA_APB_USB30_PIPEP_POWERPRESENT_REG                   BIT(14)
#define BIT_ANA_APB_USB30_JTAG_TRST_N                              BIT(13)
#define BIT_ANA_APB_USB30_JTAG_TDI                                 BIT(12)
#define BIT_ANA_APB_USB30_JTAG_TDO                                 BIT(11)
#define BIT_ANA_APB_USB30_JTAG_TDO_EN                              BIT(10)
#define BIT_ANA_APB_USB30_JTAG_TMS                                 BIT(9)
#define BIT_ANA_APB_USB30_JTAG_TCK                                 BIT(8)
#define BIT_ANA_APB_USB30_PIPEP_POWERDOWN(x)                       (((x) & 0x3) << 6)
#define BIT_ANA_APB_USB30_ATERESET                                 BIT(4)
#define BIT_ANA_APB_USB30_LOOPBACKENB0                             BIT(3)
#define BIT_ANA_APB_USB30_TEST_POWERDOWN_HSP                       BIT(2)
#define BIT_ANA_APB_USB30_TEST_POWERDOWN_SSP                       BIT(1)
#define BIT_ANA_APB_USB30_VATESTENB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_USB30_PHY_CTRL1
// Register Offset : 0x00F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_PORTRESET0                               BIT(29)
#define BIT_ANA_APB_USB30_FSEL(x)                                  (((x) & 0x3F) << 23)
#define BIT_ANA_APB_USB30_MPLL_MULTIPLIER(x)                       (((x) & 0x7F) << 16)
#define BIT_ANA_APB_USB30_REF_CLKDIV2                              BIT(15)
#define BIT_ANA_APB_USB30_REF_SSP_EN                               BIT(14)
#define BIT_ANA_APB_USB30_REF_USE_PAD                              BIT(13)
#define BIT_ANA_APB_USB30_SSC_EN                                   BIT(12)
#define BIT_ANA_APB_USB30_SSC_RANGE(x)                             (((x) & 0x7) << 9)
#define BIT_ANA_APB_USB30_SSC_REF_CLK_SEL(x)                       (((x) & 0x1FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_USB30_PHY_CTRL2
// Register Offset : 0x00F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_PIPEP_TX_ONES_ZEROS                      BIT(27)
#define BIT_ANA_APB_USB30_PIPEP_TX_ELECIDLE                        BIT(26)
#define BIT_ANA_APB_USB30_PIPEP_TX_DETECTRX                        BIT(25)
#define BIT_ANA_APB_USB30_PIPEP_TX_DEEMPH(x)                       (((x) & 0x3) << 23)
#define BIT_ANA_APB_USB30_PIPEP_RX_TERMINATION                     BIT(22)
#define BIT_ANA_APB_USB30_PIPEP_RX_POLARITY                        BIT(21)
#define BIT_ANA_APB_USB30_PIPEP_RX_EQ_TRAINING                     BIT(20)
#define BIT_ANA_APB_USB30_PIPEP_ELASTICITY_BUF_MODE                BIT(19)
#define BIT_ANA_APB_USB30_DRVVBUS0                                 BIT(18)
#define BIT_ANA_APB_USB30_IDPULLUP0                                BIT(17)
#define BIT_ANA_APB_USB30_PHY_RESET                                BIT(16)
#define BIT_ANA_APB_USB30_TXVALIDH                                 BIT(15)
#define BIT_ANA_APB_USB30_TXVALID                                  BIT(14)
#define BIT_ANA_APB_USB30_ACJT_LEVEL(x)                            (((x) & 0x1F) << 9)
#define BIT_ANA_APB_USB30_COMMONONN                                BIT(8)
#define BIT_ANA_APB_USB30_PIPEP_RESET_N                            BIT(7)
#define BIT_ANA_APB_USB30_OTGDISABLE0                              BIT(6)
#define BIT_ANA_APB_USB30_VBUSVLDEXTSEL0                           BIT(5)
#define BIT_ANA_APB_USB30_VBUSVLDEXT0                              BIT(4)
#define BIT_ANA_APB_USB30_ALT_CLK_EN                               BIT(3)
#define BIT_ANA_APB_USB30_ALT_CLK_SEL                              BIT(2)
#define BIT_ANA_APB_USB30_LANE0_EXT_PCLK_REQ                       BIT(1)
#define BIT_ANA_APB_USB30_LANE0_TX2RX_LOOPBK                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_USB30_PHY_DBG1
// Register Offset : 0x00F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_XCVRSEL0(x)                              (((x) & 0x3) << 29)
#define BIT_ANA_APB_USB30_WORDINTERFACE0                           BIT(28)
#define BIT_ANA_APB_USB30_TXBITSTUFFENH0                           BIT(27)
#define BIT_ANA_APB_USB30_TXBITSTUFFEN0                            BIT(26)
#define BIT_ANA_APB_USB30_TERMSEL0                                 BIT(25)
#define BIT_ANA_APB_USB30_SUSPENDM0                                BIT(24)
#define BIT_ANA_APB_USB30_SLEEPM0                                  BIT(23)
#define BIT_ANA_APB_USB30_OPMODE0(x)                               (((x) & 0x3) << 21)
#define BIT_ANA_APB_USB30_DPPULLDOWN0                              BIT(20)
#define BIT_ANA_APB_USB30_DMPULLDOWN0                              BIT(19)
#define BIT_ANA_APB_USB30_TXENABLEN0                               BIT(18)
#define BIT_ANA_APB_USB30_FSXCVROWNER0                             BIT(17)
#define BIT_ANA_APB_USB30_FSSE0EXT0                                BIT(16)
#define BIT_ANA_APB_USB30_FSDATAEXT0                               BIT(15)
#define BIT_ANA_APB_USB30_BYPASSSEL0                               BIT(14)
#define BIT_ANA_APB_USB30_BYPASSDMEN0                              BIT(13)
#define BIT_ANA_APB_USB30_BYPASSDPEN0                              BIT(12)
#define BIT_ANA_APB_USB30_BYPASSDMDATA0                            BIT(11)
#define BIT_ANA_APB_USB30_BYPASSDPDATA0                            BIT(10)
#define BIT_ANA_APB_USB30_VDATSRCENB0                              BIT(9)
#define BIT_ANA_APB_USB30_VDATDETENB0                              BIT(8)
#define BIT_ANA_APB_USB30_CHRGSEL0                                 BIT(7)
#define BIT_ANA_APB_USB30_DCDENB0                                  BIT(6)
#define BIT_ANA_APB_USB30_HSXCVREXTCTL0                            BIT(5)
#define BIT_ANA_APB_USB30_CR_ACK                                   BIT(4)
#define BIT_ANA_APB_USB30_CR_CAP_ADDR                              BIT(3)
#define BIT_ANA_APB_USB30_CR_CAP_DATA                              BIT(2)
#define BIT_ANA_APB_USB30_CR_READ                                  BIT(1)
#define BIT_ANA_APB_USB30_CR_WRITE                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_USB30_PHY_DBG2
// Register Offset : 0x00FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_CR_DATA_OUT(x)                           (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_USB30_CR_DATA_IN(x)                            (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_PHY_CTRL1
// Register Offset : 0x0100
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DSI_TXCLKESC_SEL                               BIT(31)
#define BIT_ANA_APB_DSI_REFCLK_SEL                                 BIT(30)
#define BIT_ANA_APB_DSI_CFGCLK_SEL                                 BIT(29)
#define BIT_ANA_APB_CSI_CFG_CLK_SEL                                BIT(28)
#define BIT_ANA_APB_DSI_PLLLOCK_S                                  BIT(27)
#define BIT_ANA_APB_DSI_PLLLOCK_M                                  BIT(26)
#define BIT_ANA_APB_CSI_IF_SEL                                     BIT(25)
#define BIT_ANA_APB_DSI_IF_SEL                                     BIT(24)
#define BIT_ANA_APB_CSI1_RX_RCTL(x)                                (((x) & 0xF) << 20)
#define BIT_ANA_APB_CSI0_RX_RCTL(x)                                (((x) & 0xF) << 16)
#define BIT_ANA_APB_DSI_TRIMBG_S(x)                                (((x) & 0xF) << 12)
#define BIT_ANA_APB_DSI_TX_RCTL_S(x)                               (((x) & 0xF) << 8)
#define BIT_ANA_APB_DSI_TRIMBG_M(x)                                (((x) & 0xF) << 4)
#define BIT_ANA_APB_DSI_TX_RCTL_M(x)                               (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_PHY_CTRL2
// Register Offset : 0x0104
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_CSI1_ENABLE_3                                  BIT(31)
#define BIT_ANA_APB_CSI1_ENABLE_2                                  BIT(30)
#define BIT_ANA_APB_CSI1_ENABLE_1                                  BIT(29)
#define BIT_ANA_APB_CSI1_ENABLE_0                                  BIT(28)
#define BIT_ANA_APB_CSI0_ENABLE_3                                  BIT(27)
#define BIT_ANA_APB_CSI0_ENABLE_2                                  BIT(26)
#define BIT_ANA_APB_CSI0_ENABLE_1                                  BIT(25)
#define BIT_ANA_APB_CSI0_ENABLE_0                                  BIT(24)
#define BIT_ANA_APB_DSI_ENABLE_3_S                                 BIT(23)
#define BIT_ANA_APB_DSI_ENABLE_2_S                                 BIT(22)
#define BIT_ANA_APB_DSI_ENABLE_1_S                                 BIT(21)
#define BIT_ANA_APB_DSI_ENABLE_0_S                                 BIT(20)
#define BIT_ANA_APB_DSI_ENABLE_3_M                                 BIT(19)
#define BIT_ANA_APB_DSI_ENABLE_2_M                                 BIT(18)
#define BIT_ANA_APB_DSI_ENABLE_1_M                                 BIT(17)
#define BIT_ANA_APB_DSI_ENABLE_0_M                                 BIT(16)
#define BIT_ANA_APB_DSI_BISTDONE_S                                 BIT(15)
#define BIT_ANA_APB_DSI_BISTDONE_M                                 BIT(14)
#define BIT_ANA_APB_CSI1_BISTOK                                    BIT(13)
#define BIT_ANA_APB_CSI0_BISTOK                                    BIT(12)
#define BIT_ANA_APB_CSI_BISTON                                     BIT(11)
#define BIT_ANA_APB_CSI_ENABLECLK                                  BIT(10)
#define BIT_ANA_APB_CSI_RSTZ                                       BIT(9)
#define BIT_ANA_APB_CSI_SHUTDOWNZ                                  BIT(8)
#define BIT_ANA_APB_DSI_TXREQUESTHSCLK_S                           BIT(7)
#define BIT_ANA_APB_DSI_TXREQUESTHSCLK_M                           BIT(6)
#define BIT_ANA_APB_DSI_FORCEPLL_S                                 BIT(5)
#define BIT_ANA_APB_DSI_FORCEPLL_M                                 BIT(4)
#define BIT_ANA_APB_DSI_BISTON                                     BIT(3)
#define BIT_ANA_APB_DSI_ENABLECLK                                  BIT(2)
#define BIT_ANA_APB_DSI_RSTZ                                       BIT(1)
#define BIT_ANA_APB_DSI_SHUTDOWNZ                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_PHY_CTRL3
// Register Offset : 0x0108
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DSI_TXREQUESTESC_3_S                           BIT(31)
#define BIT_ANA_APB_DSI_TXREQUESTESC_2_S                           BIT(30)
#define BIT_ANA_APB_DSI_TXREQUESTESC_1_S                           BIT(29)
#define BIT_ANA_APB_DSI_TXREQUESTESC_0_S                           BIT(28)
#define BIT_ANA_APB_DSI_TXREQUESTESC_3_M                           BIT(27)
#define BIT_ANA_APB_DSI_TXREQUESTESC_2_M                           BIT(26)
#define BIT_ANA_APB_DSI_TXREQUESTESC_1_M                           BIT(25)
#define BIT_ANA_APB_DSI_TXREQUESTESC_0_M                           BIT(24)
#define BIT_ANA_APB_DSI_TXDATAESC(x)                               (((x) & 0xFF) << 16)
#define BIT_ANA_APB_DSI_TXVALIDESC_3_S                             BIT(15)
#define BIT_ANA_APB_DSI_TXVALIDESC_2_S                             BIT(14)
#define BIT_ANA_APB_DSI_TXVALIDESC_1_S                             BIT(13)
#define BIT_ANA_APB_DSI_TXVALIDESC_0_S                             BIT(12)
#define BIT_ANA_APB_DSI_TXVALIDESC_3_M                             BIT(11)
#define BIT_ANA_APB_DSI_TXVALIDESC_2_M                             BIT(10)
#define BIT_ANA_APB_DSI_TXVALIDESC_1_M                             BIT(9)
#define BIT_ANA_APB_DSI_TXVALIDESC_0_M                             BIT(8)
#define BIT_ANA_APB_DSI_TXLPDTESC_3_S                              BIT(7)
#define BIT_ANA_APB_DSI_TXLPDTESC_2_S                              BIT(6)
#define BIT_ANA_APB_DSI_TXLPDTESC_1_S                              BIT(5)
#define BIT_ANA_APB_DSI_TXLPDTESC_0_S                              BIT(4)
#define BIT_ANA_APB_DSI_TXLPDTESC_3_M                              BIT(3)
#define BIT_ANA_APB_DSI_TXLPDTESC_2_M                              BIT(2)
#define BIT_ANA_APB_DSI_TXLPDTESC_1_M                              BIT(1)
#define BIT_ANA_APB_DSI_TXLPDTESC_0_M                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_PHY_CTRL4
// Register Offset : 0x010C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DSI_STOPSTATEDATA_3_S                          BIT(31)
#define BIT_ANA_APB_DSI_STOPSTATEDATA_2_S                          BIT(30)
#define BIT_ANA_APB_DSI_STOPSTATEDATA_1_S                          BIT(29)
#define BIT_ANA_APB_DSI_STOPSTATEDATA_0_S                          BIT(28)
#define BIT_ANA_APB_DSI_STOPSTATEDATA_3_M                          BIT(27)
#define BIT_ANA_APB_DSI_STOPSTATEDATA_2_M                          BIT(26)
#define BIT_ANA_APB_DSI_STOPSTATEDATA_1_M                          BIT(25)
#define BIT_ANA_APB_DSI_STOPSTATEDATA_0_M                          BIT(24)
#define BIT_ANA_APB_CSI1_STOPSTATEDATA(x)                          (((x) & 0xF) << 20)
#define BIT_ANA_APB_CSI0_STOPSTATEDATA(x)                          (((x) & 0xF) << 16)
#define BIT_ANA_APB_DSI_FORCERXMODE_3_S                            BIT(15)
#define BIT_ANA_APB_DSI_FORCERXMODE_2_S                            BIT(14)
#define BIT_ANA_APB_DSI_FORCERXMODE_1_S                            BIT(13)
#define BIT_ANA_APB_DSI_FORCERXMODE_0_S                            BIT(12)
#define BIT_ANA_APB_DSI_FORCERXMODE_3_M                            BIT(11)
#define BIT_ANA_APB_DSI_FORCERXMODE_2_M                            BIT(10)
#define BIT_ANA_APB_DSI_FORCERXMODE_1_M                            BIT(9)
#define BIT_ANA_APB_DSI_FORCERXMODE_0_M                            BIT(8)
#define BIT_ANA_APB_CSI1_FORCERXMODE_3                             BIT(7)
#define BIT_ANA_APB_CSI1_FORCERXMODE_2                             BIT(6)
#define BIT_ANA_APB_CSI1_FORCERXMODE_1                             BIT(5)
#define BIT_ANA_APB_CSI1_FORCERXMODE_0                             BIT(4)
#define BIT_ANA_APB_CSI0_FORCERXMODE_3                             BIT(3)
#define BIT_ANA_APB_CSI0_FORCERXMODE_2                             BIT(2)
#define BIT_ANA_APB_CSI0_FORCERXMODE_1                             BIT(1)
#define BIT_ANA_APB_CSI0_FORCERXMODE_0                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PROBE_CAL
// Register Offset : 0x0110
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_PROBE_MAX_RANGE(x)                             (((x) & 0x7FFF) << 16)
#define BIT_ANA_APB_PROBE_MIN_RANGE(x)                             (((x) & 0x7FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_AUX0_CAL
// Register Offset : 0x0114
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_AUX0_MAX_RANGE(x)                              (((x) & 0x7FFF) << 16)
#define BIT_ANA_APB_AUX0_MIN_RANGE(x)                              (((x) & 0x7FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_AUX1_CAL
// Register Offset : 0x0118
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_AUX1_MAX_RANGE(x)                              (((x) & 0x7FFF) << 16)
#define BIT_ANA_APB_AUX1_MIN_RANGE(x)                              (((x) & 0x7FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_AUX2_CAL
// Register Offset : 0x011C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_AUX2_MAX_RANGE(x)                              (((x) & 0x7FFF) << 16)
#define BIT_ANA_APB_AUX2_MIN_RANGE(x)                              (((x) & 0x7FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_AAPC_GEN_CFG
// Register Offset : 0x0120
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_AAPC_STEP_SEL                                  BIT(30)
#define BIT_ANA_APB_AAPC_MAX_RANGE(x)                              (((x) & 0x3FFF) << 16)
#define BIT_ANA_APB_AAPC_MIN_RANGE(x)                              (((x) & 0x3FFF) << 2)
#define BIT_ANA_APB_AAPC_RSTN                                      BIT(1)
#define BIT_ANA_APB_AAPC_GEN_SEL                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_BB_PLL_VSET
// Register Offset : 0x0124
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_PLL_REF_SEL                                    BIT(12)
#define BIT_ANA_APB_S_LVDSRF_VSET(x)                               (((x) & 0x7) << 9)
#define BIT_ANA_APB_M_LVDSRF_VSET(x)                               (((x) & 0x7) << 6)
#define BIT_ANA_APB_TWPLL_REF_SEL(x)                               (((x) & 0x7) << 3)
#define BIT_ANA_APB_TWPLL_VSET(x)                                  (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_FREQ_CAL_CFG
// Register Offset : 0x012C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DIV_NUM_26M(x)                                 (((x) & 0x3FF) << 16)
#define BIT_ANA_APB_AUX2_CAL_EN                                    BIT(3)
#define BIT_ANA_APB_AUX1_CAL_EN                                    BIT(2)
#define BIT_ANA_APB_AUX0_CAL_EN                                    BIT(1)
#define BIT_ANA_APB_PROBE_CAL_EN                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PROBE_RESULT
// Register Offset : 0x0130
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_PROBE_FREQ(x)                                  (((x) & 0x7FFF) << 15)
#define BIT_ANA_APB_PROBE_READY                                    BIT(1)
#define BIT_ANA_APB_PROBE_PASS                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_AUX0_RESULT
// Register Offset : 0x0134
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_AUX0_FREQ(x)                                   (((x) & 0x7FFF) << 15)
#define BIT_ANA_APB_AUX0_READY                                     BIT(1)
#define BIT_ANA_APB_AUX0_PASS                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_AUX1_RESULT
// Register Offset : 0x0138
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_AUX1_FREQ(x)                                   (((x) & 0x7FFF) << 15)
#define BIT_ANA_APB_AUX1_READY                                     BIT(1)
#define BIT_ANA_APB_AUX1_PASS                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_AUX2_RESULT
// Register Offset : 0x013C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_AUX2_FREQ(x)                                   (((x) & 0x7FFF) << 15)
#define BIT_ANA_APB_AUX2_READY                                     BIT(1)
#define BIT_ANA_APB_AUX2_PASS                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_TEST_FLAG
// Register Offset : 0x014C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_PLLS_FLAG(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_TEST
// Register Offset : 0x0150
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MIPI_TESTDOUT_SEL                              BIT(31)
#define BIT_ANA_APB_MIPI1_TESTIN_SEL                               BIT(30)
#define BIT_ANA_APB_MIPI1_TESTEN                                   BIT(29)
#define BIT_ANA_APB_MIPI1_TESTCLR                                  BIT(28)
#define BIT_ANA_APB_MIPI1_TESTCLK                                  BIT(27)
#define BIT_ANA_APB_MIPI0_TESTEN                                   BIT(26)
#define BIT_ANA_APB_MIPI0_TESTCLR                                  BIT(25)
#define BIT_ANA_APB_MIPI0_TESTCLK                                  BIT(24)
#define BIT_ANA_APB_MIPI_TEST_IF_SEL                               BIT(23)
#define BIT_ANA_APB_MIPI_TEST_DONE                                 BIT(22)
#define BIT_ANA_APB_MIPI_TEST_PASS                                 BIT(21)
#define BIT_ANA_APB_MIPI_TEST_DA_LEN(x)                            (((x) & 0x1FFF) << 8)
#define BIT_ANA_APB_MIPI_TEST_MODE_SEL                             BIT(7)
#define BIT_ANA_APB_MIPI_TEST_DLAN_SEL(x)                          (((x) & 0x7) << 4)
#define BIT_ANA_APB_MIPI_TEST_CLAN_SEL(x)                          (((x) & 0x7) << 1)
#define BIT_ANA_APB_MIPI_TEST_EN                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_TEST2
// Register Offset : 0x0154
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MIPI1_TESTDOUT(x)                              (((x) & 0xFF) << 24)
#define BIT_ANA_APB_MIPI1_TESTDIN(x)                               (((x) & 0xFF) << 16)
#define BIT_ANA_APB_MIPI0_TESTDOUT(x)                              (((x) & 0xFF) << 8)
#define BIT_ANA_APB_MIPI0_TESTDIN(x)                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_CSI0_RESERVE
// Register Offset : 0x0158
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_CSI0_RESERVE(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_CSI1_RESERVE
// Register Offset : 0x015C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_CSI1_RESERVE(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_DSI0_RESERVE
// Register Offset : 0x0160
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DSI0_RESERVE(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_DSI1_RESERVE
// Register Offset : 0x0164
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DSI1_RESERVE(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_DSI_TXSKEW_CTRL
// Register Offset : 0x0168
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DSI_STOPSTATECLK_S                             BIT(10)
#define BIT_ANA_APB_DSI_STOPSTATECLK_M                             BIT(9)
#define BIT_ANA_APB_DSI_TESTDOUT_SEL                               BIT(8)
#define BIT_ANA_APB_DSI_TXSKEWCALHS_3_S                            BIT(7)
#define BIT_ANA_APB_DSI_TXSKEWCALHS_2_S                            BIT(6)
#define BIT_ANA_APB_DSI_TXSKEWCALHS_1_S                            BIT(5)
#define BIT_ANA_APB_DSI_TXSKEWCALHS_0_S                            BIT(4)
#define BIT_ANA_APB_DSI_TXSKEWCALHS_3_M                            BIT(3)
#define BIT_ANA_APB_DSI_TXSKEWCALHS_2_M                            BIT(2)
#define BIT_ANA_APB_DSI_TXSKEWCALHS_1_M                            BIT(1)
#define BIT_ANA_APB_DSI_TXSKEWCALHS_0_M                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MACRO_POWER_FLAG0
// Register Offset : 0x0174
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MACRO_POWER_FLAG0(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MACRO_POWER_FLAG1
// Register Offset : 0x0178
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MACRO_POWER_FLAG1(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MACRO_RESET_FLAG0
// Register Offset : 0x017C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MACRO_RESET_FLAG0(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MACRO_CHECK_FLAG0
// Register Offset : 0x0180
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MACRO_CHECK_FLAG0(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MACRO_CHECK_FLAG1
// Register Offset : 0x0184
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MACRO_CHECK_FLAG1(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_CLKOUT_AUTO_GATE0
// Register Offset : 0x0188
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_GPLL_CLKOUT_AUTO_GATE_DIS                      BIT(27)
#define BIT_ANA_APB_LPLL0_CLKOUT_AUTO_GATE_DIS                     BIT(26)
#define BIT_ANA_APB_LPLL0_DIV1_AUTO_GATE_DIS                       BIT(25)
#define BIT_ANA_APB_LPLL0_DIV2_AUTO_GATE_DIS                       BIT(24)
#define BIT_ANA_APB_LPLL0_DIV3_AUTO_GATE_DIS                       BIT(23)
#define BIT_ANA_APB_LPLL0_DIV5_AUTO_GATE_DIS                       BIT(22)
#define BIT_ANA_APB_TWPLL_CLKOUT_AUTO_GATE_DIS                     BIT(21)
#define BIT_ANA_APB_TWPLL_DIV1_AUTO_GATE_DIS                       BIT(20)
#define BIT_ANA_APB_TWPLL_DIV2_AUTO_GATE_DIS                       BIT(19)
#define BIT_ANA_APB_TWPLL_DIV3_AUTO_GATE_DIS                       BIT(18)
#define BIT_ANA_APB_TWPLL_DIV5_AUTO_GATE_DIS                       BIT(17)
#define BIT_ANA_APB_TWPLL_DIV7_AUTO_GATE_DIS                       BIT(16)
#define BIT_ANA_APB_DPLL1_CLKOUT_AUTO_GATE_DIS                     BIT(15)
#define BIT_ANA_APB_DPLL0_CLKOUT_AUTO_GATE_DIS                     BIT(8)
#define BIT_ANA_APB_CPPLL_CLKOUT_AUTO_GATE_DIS                     BIT(2)
#define BIT_ANA_APB_MPLL1_CLKOUT_AUTO_GATE_DIS                     BIT(1)
#define BIT_ANA_APB_MPLL0_CLKOUT_AUTO_GATE_DIS                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_PLL_CLKOUT_AUTO_GATE1
// Register Offset : 0x018C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_LPLL1_PRE_AUTO_GATE_DIS                        BIT(6)
#define BIT_ANA_APB_LPLL0_PRE_AUTO_GATE_DIS                        BIT(5)
#define BIT_ANA_APB_LPLL1_CLKOUT_AUTO_GATE_DIS                     BIT(4)
#define BIT_ANA_APB_LPLL1_DIV1_AUTO_GATE_DIS                       BIT(3)
#define BIT_ANA_APB_LPLL1_DIV2_AUTO_GATE_DIS                       BIT(2)
#define BIT_ANA_APB_LPLL1_DIV3_AUTO_GATE_DIS                       BIT(1)
#define BIT_ANA_APB_LPLL1_DIV5_AUTO_GATE_DIS                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_AGLB_SEL0
// Register Offset : 0x0200
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_CFG_SEL                                  BIT(25)
#define BIT_ANA_APB_MIPI_CSI_CFG_SEL                               BIT(22)
#define BIT_ANA_APB_MIPI_DSI_CFG_SEL                               BIT(21)
#define BIT_ANA_APB_S_LVDSRF_CFG_SEL                               BIT(19)
#define BIT_ANA_APB_M_LVDSRF_CFG_SEL                               BIT(18)
#define BIT_ANA_APB_THM_CFG_SEL                                    BIT(17)
#define BIT_ANA_APB_GPLL_CFG_SEL                                   BIT(16)
#define BIT_ANA_APB_CPPLL_CFG_SEL                                  BIT(15)
#define BIT_ANA_APB_TWPLL_CFG_SEL                                  BIT(14)
#define BIT_ANA_APB_S_LVDSRF_PLL_CFG_SEL                           BIT(13)
#define BIT_ANA_APB_M_LVDSRF_PLL_CFG_SEL                           BIT(12)
#define BIT_ANA_APB_LPLL1_CFG_SEL                                  BIT(11)
#define BIT_ANA_APB_LPLL0_CFG_SEL                                  BIT(10)
#define BIT_ANA_APB_RPLL1_CFG_SEL                                  BIT(9)
#define BIT_ANA_APB_RPLL0_CFG_SEL                                  BIT(8)
#define BIT_ANA_APB_DPLL1_CFG_SEL                                  BIT(7)
#define BIT_ANA_APB_DPLL0_CFG_SEL                                  BIT(6)
#define BIT_ANA_APB_MPLL1_CFG_SEL                                  BIT(5)
#define BIT_ANA_APB_MPLL0_CFG_SEL                                  BIT(4)
#define BIT_ANA_APB_RTC_CFG_SEL                                    BIT(3)
#define BIT_ANA_APB_AAPC_CFG_SEL                                   BIT(2)
#define BIT_ANA_APB_BB_BG_CFG_SEL                                  BIT(1)
#define BIT_ANA_APB_XTAL_SIN_CFG_SEL                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_AGLB_SEL1
// Register Offset : 0x0204
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_PLL_ATE_REFCK_SEL                              BIT(7)
#define BIT_ANA_APB_MIPI_ATE_REFCK_SEL                             BIT(6)
#define BIT_ANA_APB_MDAR_PMU_RPLL1_CFG_SEL                         BIT(5)
#define BIT_ANA_APB_MDAR_PMU_RPLL0_CFG_SEL                         BIT(4)
#define BIT_ANA_APB_ANLG_DBG_BUS_SEL(x)                            (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MPLL_BIST_CNT
// Register Offset : 0x0208
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MPLL1_BISTCNT(x)                               (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_MPLL0_BISTCNT(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_EFUSE_CFG
// Register Offset : 0x020C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_EFS1_ENK2                                      BIT(7)
#define BIT_ANA_APB_EFS1_ENK1                                      BIT(6)
#define BIT_ANA_APB_EFS1_TRCS                                      BIT(5)
#define BIT_ANA_APB_EFS1_AT(x)                                     (((x) & 0x3) << 3)
#define BIT_ANA_APB_EFS0_TRCS                                      BIT(2)
#define BIT_ANA_APB_EFS0_AT(x)                                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_VDROP_SNSR_CTRL
// Register Offset : 0x0210
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_VDROP_OUT                                      BIT(18)
#define BIT_ANA_APB_VDROP_PULSE_SEL(x)                             (((x) & 0xF) << 14)
#define BIT_ANA_APB_VDROP_TEST_EN                                  BIT(13)
#define BIT_ANA_APB_VDROP_RANGE_SEL(x)                             (((x) & 0x3) << 11)
#define BIT_ANA_APB_VDROP_LATCH_EN                                 BIT(10)
#define BIT_ANA_APB_VDROP_RESERVED(x)                              (((x) & 0xF) << 6)
#define BIT_ANA_APB_VDROP_CTRL(x)                                  (((x) & 0x7) << 3)
#define BIT_ANA_APB_VDROP_CURRENT(x)                               (((x) & 0x3) << 1)
#define BIT_ANA_APB_VDROP_EN                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_USB30_PHY_CTRL3
// Register Offset : 0x0214
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_USB30_REF_PAD_PD                               BIT(9)
#define BIT_ANA_APB_USB30_REF_CLK_SEL(x)                           (((x) & 0x3) << 7)
#define BIT_ANA_APB_USB30_DIGPWRRST                                BIT(6)
#define BIT_ANA_APB_USB30_DIGPWRSTABLESSP                          BIT(5)
#define BIT_ANA_APB_USB30_DIGPWRSTABLEHSP0                         BIT(4)
#define BIT_ANA_APB_USB30_DIGPWERENSSP                             BIT(3)
#define BIT_ANA_APB_USB30_DIGPWERENHSP0                            BIT(2)
#define BIT_ANA_APB_USB30_DIGOUTISOENSSP                           BIT(1)
#define BIT_ANA_APB_USB30_DIGOUTISOENHSP0                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RESONANCE_CTRL1
// Register Offset : 0x0218
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RESONANCE_HI_CNT(x)                            (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_RESONANCE_LO_CNT(x)                            (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RESONANCE_CTRL2
// Register Offset : 0x021C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RESONANCE_CTRL(x)                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MPLL_CFG
// Register Offset : 0x0220
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MPLL1_BIST_EN                                  BIT(4)
#define BIT_ANA_APB_MPLL0_BIST_EN                                  BIT(3)
#define BIT_ANA_APB_MPLL_DBG_OD                                    BIT(2)
#define BIT_ANA_APB_MPLL_DBG_SEL                                   BIT(1)
#define BIT_ANA_APB_MPLL_DBG_EN                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_REC_XTAL_CFG1
// Register Offset : 0x0224
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_ANALOG_PLL_RESERVE(x)                          (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_ANALOG_TESTMUX(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_THM4_CFG
// Register Offset : 0x0228
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_THM4_ITUNE(x)                                  (((x) & 0xF) << 8)
#define BIT_ANA_APB_THM4_CALI_EN                                   BIT(7)
#define BIT_ANA_APB_THM4_RUN                                       BIT(6)
#define BIT_ANA_APB_THM4_RSTN                                      BIT(5)
#define BIT_ANA_APB_THM4_PD                                        BIT(4)
#define BIT_ANA_APB_THM4_RESERVE(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_THM5_CFG
// Register Offset : 0x022C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_THM5_ITUNE(x)                                  (((x) & 0xF) << 8)
#define BIT_ANA_APB_THM5_CALI_EN                                   BIT(7)
#define BIT_ANA_APB_THM5_RUN                                       BIT(6)
#define BIT_ANA_APB_THM5_RSTN                                      BIT(5)
#define BIT_ANA_APB_THM5_PD                                        BIT(4)
#define BIT_ANA_APB_THM5_RESERVE(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_DPLL0_CFG2
// Register Offset : 0x0230
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DPLL0_BISTCNT(x)                               (((x) & 0xFFFF) << 6)
#define BIT_ANA_APB_DPLL0_BIST_EN                                  BIT(5)
#define BIT_ANA_APB_DPLL0_VSET(x)                                  (((x) & 0x7) << 2)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_DPLL1_CFG2
// Register Offset : 0x0234
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_DPLL1_BISTCNT(x)                               (((x) & 0xFFFF) << 6)
#define BIT_ANA_APB_DPLL1_BIST_EN                                  BIT(5)
#define BIT_ANA_APB_DPLL1_VSET(x)                                  (((x) & 0x7) << 2)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_PHY_CTRL5
// Register Offset : 0x0238
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_CSI_TESTDOUT_SEL                               BIT(30)
#define BIT_ANA_APB_FORCE_CSI2_PHY_SHUTDOWNZ                       BIT(29)
#define BIT_ANA_APB_MIPI_CSI2_PS_PD_S                              BIT(28)
#define BIT_ANA_APB_MIPI_CSI2_PS_PD_L                              BIT(27)
#define BIT_ANA_APB_CSI2_PHY_SEL(x)                                (((x) & 0x3) << 25)
#define BIT_ANA_APB_CSI1_PHY_SEL(x)                                (((x) & 0x3) << 23)
#define BIT_ANA_APB_CSI0_PHY_SEL(x)                                (((x) & 0x3) << 21)
#define BIT_ANA_APB_CSI1_SEL(x)                                    (((x) & 0x3) << 19)
#define BIT_ANA_APB_CSI0_SEL(x)                                    (((x) & 0x3) << 17)
#define BIT_ANA_APB_CSI2_STOPSTATEDATA(x)                          (((x) & 0xF) << 13)
#define BIT_ANA_APB_CSI2_RX_RCTL(x)                                (((x) & 0xF) << 9)
#define BIT_ANA_APB_CSI2_FORCERXMODE_3                             BIT(8)
#define BIT_ANA_APB_CSI2_FORCERXMODE_2                             BIT(7)
#define BIT_ANA_APB_CSI2_FORCERXMODE_1                             BIT(6)
#define BIT_ANA_APB_CSI2_FORCERXMODE_0                             BIT(5)
#define BIT_ANA_APB_CSI2_ENABLE_3                                  BIT(4)
#define BIT_ANA_APB_CSI2_ENABLE_2                                  BIT(3)
#define BIT_ANA_APB_CSI2_ENABLE_1                                  BIT(2)
#define BIT_ANA_APB_CSI2_ENABLE_0                                  BIT(1)
#define BIT_ANA_APB_CSI2_BISTOK                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_DEBUG_LOG_CTRL
// Register Offset : 0x023C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_LOG_MODE_EN                                    BIT(1)
#define BIT_ANA_APB_DSI_IF_SEL_S                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_BB_TEST_CLK_SCFG
// Register Offset : 0x0240
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_TEST_CLK_EN                                    BIT(3)
#define BIT_ANA_APB_TEST_CLK_OD                                    BIT(2)
#define BIT_ANA_APB_TEST_CLK_DIV(x)                                (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_LTEPLL_CFG3
// Register Offset : 0x0244
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_LPLL0_VSET(x)                                  (((x) & 0x7) << 1)
#define BIT_ANA_APB_LPLL0_PRE_EN                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_LTECAPLL_CFG3
// Register Offset : 0x0248
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_LPLL1_VSET(x)                                  (((x) & 0x7) << 1)
#define BIT_ANA_APB_LPLL1_PRE_EN                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_PHY_CTRL6
// Register Offset : 0x024C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_CSI1_RXSKEWCAL_FAIL(x)                         (((x) & 0xF) << 24)
#define BIT_ANA_APB_CSI1_RXSKEWCAL_DONE(x)                         (((x) & 0xF) << 20)
#define BIT_ANA_APB_CSI1_RXSKEWCALHS(x)                            (((x) & 0xF) << 16)
#define BIT_ANA_APB_CSI0_RXSKEWCAL_FAIL(x)                         (((x) & 0xF) << 12)
#define BIT_ANA_APB_CSI0_RXSKEWCAL_DONE(x)                         (((x) & 0xF) << 8)
#define BIT_ANA_APB_CSI0_RXSKEWCALHS(x)                            (((x) & 0xF) << 4)
#define BIT_ANA_APB_CSI1_STOPSTATECLK                              BIT(1)
#define BIT_ANA_APB_CSI0_STOPSTATECLK                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_TRIM_SEL
// Register Offset : 0x0250
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_MIPI0_TEST_DISABLE                             BIT(5)
#define BIT_ANA_APB_CSI_TRIM_SEL(x)                                (((x) & 0x7) << 2)
#define BIT_ANA_APB_DSI_TRIM_SEL(x)                                (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_RESERVED_CTRL
// Register Offset : 0x0254
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_RESERVED_REG(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_MIPI_APB_CGEN
// Register Offset : 0x0258
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_FORCE_DSI_APB_CGEN                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_UPLL_CFG1
// Register Offset : 0x0260
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_UPLL_VSET(x)                                   (((x) & 0x7) << 27)
#define BIT_ANA_APB_UPLL_RESERVE(x)                                (((x) & 0xFF) << 19)
#define BIT_ANA_APB_UPLL_LOCK_DONE                                 BIT(18)
#define BIT_ANA_APB_UPLL_POSTDIV                                   BIT(17)
#define BIT_ANA_APB_UPLL_REF_SEL                                   BIT(16)
#define BIT_ANA_APB_UPLL_DIV_S                                     BIT(15)
#define BIT_ANA_APB_UPLL_MOD_EN                                    BIT(14)
#define BIT_ANA_APB_UPLL_SDM_EN                                    BIT(13)
#define BIT_ANA_APB_UPLL_LPF(x)                                    (((x) & 0x7) << 10)
#define BIT_ANA_APB_UPLL_IBIAS(x)                                  (((x) & 0x3) << 8)
#define BIT_ANA_APB_UPLL_CLKOUT_EN                                 BIT(7)
#define BIT_ANA_APB_UPLL_N(x)                                      (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_UPLL_CFG2
// Register Offset : 0x0264
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_UPLL_NINT(x)                                   (((x) & 0x7F) << 25)
#define BIT_ANA_APB_UPLL_PD_SEL                                    BIT(24)
#define BIT_ANA_APB_UPLL_RST                                       BIT(23)
#define BIT_ANA_APB_UPLL_KINT(x)                                   (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_UPLL_CFG3
// Register Offset : 0x0268
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_UPLL_DBG_SEL(x)                                (((x) & 0x3) << 6)
#define BIT_ANA_APB_UPLL_DBG_OD                                    BIT(5)
#define BIT_ANA_APB_UPLL_DBG_EN                                    BIT(4)
#define BIT_ANA_APB_UPLL_CLKOUT_FREQ_SEL                           BIT(3)
#define BIT_ANA_APB_UPLL_CLKOUT_SEL                                BIT(2)
#define BIT_ANA_APB_REC_26MHZ_1_CUR_SEL                            BIT(1)
#define BIT_ANA_APB_REC_26MHZ_1_BUF_PD                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_UPLL_BIST
// Register Offset : 0x026C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_UPLL_BIST_CNT(x)                               (((x) & 0xFFFF) << 9)
#define BIT_ANA_APB_UPLL_BIST_CRTL(x)                              (((x) & 0xFF) << 1)
#define BIT_ANA_APB_UPLL_BIST_EN                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_UPLL_CFG4
// Register Offset : 0x0270
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_UPLL_CFG(x)                                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_SW_TEST
// Register Offset : 0x0404
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_SW_FLAG                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_ANLG_RESERVED1
// Register Offset : 0x0408
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_ANLG_RESERVED1_HB(x)                           (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_ANLG_RESERVED1_LB(x)                           (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_ANA_APB_ANLG_RESERVED2
// Register Offset : 0x040C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_ANA_APB_ANLG_RESERVED2_HB(x)                           (((x) & 0xFFFF) << 16)
#define BIT_ANA_APB_ANLG_RESERVED2_LB(x)                           (((x) & 0xFFFF))
#endif

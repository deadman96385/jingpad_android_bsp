/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _AON_APB_REG_H
#define _AON_APB_REG_H

#define CTL_BASE_AON_APB SPRD_AONAPB_PHYS


#define REG_AON_APB_APB_EB0                    ( CTL_BASE_AON_APB + 0x0000 )
#define REG_AON_APB_APB_EB1                    ( CTL_BASE_AON_APB + 0x0004 )
#define REG_AON_APB_APB_RST0                   ( CTL_BASE_AON_APB + 0x0008 )
#define REG_AON_APB_APB_RST1                   ( CTL_BASE_AON_APB + 0x000C )
#define REG_AON_APB_APB_RTC_EB                 ( CTL_BASE_AON_APB + 0x0010 )
#define REG_AON_APB_REC_26MHZ_BUF_CFG          ( CTL_BASE_AON_APB + 0x0014 )
#define REG_AON_APB_SINDRV_CTRL                ( CTL_BASE_AON_APB + 0x0018 )
#define REG_AON_APB_ADA_SEL_CTRL               ( CTL_BASE_AON_APB + 0x001C )
#define REG_AON_APB_VBC_CTRL                   ( CTL_BASE_AON_APB + 0x0020 )
#define REG_AON_APB_PWR_CTRL                   ( CTL_BASE_AON_APB + 0x0024 )
#define REG_AON_APB_TS_CFG                     ( CTL_BASE_AON_APB + 0x0028 )
#define REG_AON_APB_BOOT_MODE                  ( CTL_BASE_AON_APB + 0x002C )
#define REG_AON_APB_BB_BG_CTRL                 ( CTL_BASE_AON_APB + 0x0030 )
#define REG_AON_APB_CP_ARM_JTAG_CTRL           ( CTL_BASE_AON_APB + 0x0034 )
#define REG_AON_APB_PLL_SOFT_CNT_DONE          ( CTL_BASE_AON_APB + 0x0038 )
#define REG_AON_APB_DCXO_LC_REG0               ( CTL_BASE_AON_APB + 0x003C )
#define REG_AON_APB_DCXO_LC_REG1               ( CTL_BASE_AON_APB + 0x0040 )
#define REG_AON_APB_MPLL_CFG1                  ( CTL_BASE_AON_APB + 0x0044 )
#define REG_AON_APB_MPLL_CFG2                  ( CTL_BASE_AON_APB + 0x0048 )
#define REG_AON_APB_DPLL_CFG1                  ( CTL_BASE_AON_APB + 0x004C )
#define REG_AON_APB_DPLL_CFG2                  ( CTL_BASE_AON_APB + 0x0050 )
#define REG_AON_APB_TWPLL_CFG1                 ( CTL_BASE_AON_APB + 0x0054 )
#define REG_AON_APB_TWPLL_CFG2                 ( CTL_BASE_AON_APB + 0x0058 )
#define REG_AON_APB_LTEPLL_CFG1                ( CTL_BASE_AON_APB + 0x005C )
#define REG_AON_APB_LTEPLL_CFG2                ( CTL_BASE_AON_APB + 0x0060 )
#define REG_AON_APB_LVDSRFPLL_CFG1             ( CTL_BASE_AON_APB + 0x0064 )
#define REG_AON_APB_LVDSRFPLL_CFG2             ( CTL_BASE_AON_APB + 0x0068 )
#define REG_AON_APB_AON_REG_PROT               ( CTL_BASE_AON_APB + 0x006C )
#define REG_AON_APB_DSI_PHY_CTRL               ( CTL_BASE_AON_APB + 0x0070 )
#define REG_AON_APB_CSI_2L_PHY_CTRL            ( CTL_BASE_AON_APB + 0x0074 )
#define REG_AON_APB_CSI_2P2L_S_PHY_CTRL        ( CTL_BASE_AON_APB + 0x0078 )
#define REG_AON_APB_CSI_2P2L_M_PHY_CTRL        ( CTL_BASE_AON_APB + 0x007C )
#define REG_AON_APB_CSI_2P2L_DBG_PHY_CTRL      ( CTL_BASE_AON_APB + 0x0080 )
#define REG_AON_APB_CSI_2P2L_PHY_CTRL          ( CTL_BASE_AON_APB + 0x0084 )
#define REG_AON_APB_AON_CGM_CFG                ( CTL_BASE_AON_APB + 0x0088 )
#define REG_AON_APB_SOFT_DFS_CTRL              ( CTL_BASE_AON_APB + 0x00A0 )
#define REG_AON_APB_HARD_DFS_CTRL_LO           ( CTL_BASE_AON_APB + 0x00A4 )
#define REG_AON_APB_HARD_DFS_CTRL_HI           ( CTL_BASE_AON_APB + 0x00A8 )
#define REG_AON_APB_APB_EB2                    ( CTL_BASE_AON_APB + 0x00B0 )
#define REG_AON_APB_ROSC_CFG                   ( CTL_BASE_AON_APB + 0x00C0 )
#define REG_AON_APB_ROSC_STATUS                ( CTL_BASE_AON_APB + 0x00C4 )
#define REG_AON_APB_AON_ANALOG_RSV             ( CTL_BASE_AON_APB + 0x00C8 )
#define REG_AON_APB_AON_CHIP_ID0               ( CTL_BASE_AON_APB + 0x00E0 )
#define REG_AON_APB_AON_CHIP_ID1               ( CTL_BASE_AON_APB + 0x00E4 )
#define REG_AON_APB_AON_PLAT_ID0               ( CTL_BASE_AON_APB + 0x00E8 )
#define REG_AON_APB_AON_PLAT_ID1               ( CTL_BASE_AON_APB + 0x00EC )
#define REG_AON_APB_AON_IMPL_ID                ( CTL_BASE_AON_APB + 0x00F0 )
#define REG_AON_APB_AON_MFT_ID                 ( CTL_BASE_AON_APB + 0x00F4 )
#define REG_AON_APB_AON_VER_ID                 ( CTL_BASE_AON_APB + 0x00F8 )
#define REG_AON_APB_AON_CHIP_ID                ( CTL_BASE_AON_APB + 0x00FC )
#define REG_AON_APB_CCIR_RCVR_CFG              ( CTL_BASE_AON_APB + 0x0100 )
#define REG_AON_APB_PLL_BG_CFG                 ( CTL_BASE_AON_APB + 0x0108 )
#define REG_AON_APB_LVDSDIS_SEL                ( CTL_BASE_AON_APB + 0x010C )
#define REG_AON_APB_DJTAG_MUX_SEL              ( CTL_BASE_AON_APB + 0x0110 )
#define REG_AON_APB_ARM7_SYS_SOFT_RST          ( CTL_BASE_AON_APB + 0x0114 )
#define REG_AON_APB_PUBCP_WTLCP_ADDR_MSB       ( CTL_BASE_AON_APB + 0x0118 )
#define REG_AON_APB_AON_DMA_INT_EN             ( CTL_BASE_AON_APB + 0x011C )
#define REG_AON_APB_EMC_AUTO_GATE_EN           ( CTL_BASE_AON_APB + 0x0120 )
#define REG_AON_APB_ARM7_CFG_BUS               ( CTL_BASE_AON_APB + 0x0124 )
#define REG_AON_APB_RTC4M_0_CFG                ( CTL_BASE_AON_APB + 0x0128 )
#define REG_AON_APB_RTC4M_1_CFG                ( CTL_BASE_AON_APB + 0x012C )
#define REG_AON_APB_APB_RST2                   ( CTL_BASE_AON_APB + 0x0130 )
#define REG_AON_APB_CLK_EB0                    ( CTL_BASE_AON_APB + 0x0134 )
#define REG_AON_APB_AON_SDIO                   ( CTL_BASE_AON_APB + 0x0138 )
#define REG_AON_APB_MPLL_CTRL                  ( CTL_BASE_AON_APB + 0x013C )
#define REG_AON_APB_GPLL_CFG1                  ( CTL_BASE_AON_APB + 0x0150 )
#define REG_AON_APB_GPLL_CFG2                  ( CTL_BASE_AON_APB + 0x0154 )
#define REG_AON_APB_RPLL_CFG1                  ( CTL_BASE_AON_APB + 0x0158 )
#define REG_AON_APB_RPLL_CFG2                  ( CTL_BASE_AON_APB + 0x015C )
#define REG_AON_APB_RPLL_CFG3                  ( CTL_BASE_AON_APB + 0x0160 )
#define REG_AON_APB_THM0_CTRL                  ( CTL_BASE_AON_APB + 0x0164 )
#define REG_AON_APB_THM1_CTRL                  ( CTL_BASE_AON_APB + 0x0168 )
#define REG_AON_APB_BUSMON_DMA_CFG             ( CTL_BASE_AON_APB + 0x0170 )
#define REG_AON_APB_ANALOG_CFG0                ( CTL_BASE_AON_APB + 0x0174 )
#define REG_AON_APB_ANALOG_CFG1                ( CTL_BASE_AON_APB + 0x0178 )
#define REG_AON_APB_RPLL_BIST_CTRL             ( CTL_BASE_AON_APB + 0x017C )
#define REG_AON_APB_MPLL_BIST_CTRL             ( CTL_BASE_AON_APB + 0x0180 )
#define REG_AON_APB_DPLL_BIST_CTRL             ( CTL_BASE_AON_APB + 0x0184 )
#define REG_AON_APB_GPLL_BIST_CTRL             ( CTL_BASE_AON_APB + 0x0188 )
#define REG_AON_APB_TWPLL_BIST_CTRL            ( CTL_BASE_AON_APB + 0x018C )
#define REG_AON_APB_LPLL_BIST_CTRL             ( CTL_BASE_AON_APB + 0x0190 )
#define REG_AON_APB_DPLL_CTRL                  ( CTL_BASE_AON_APB + 0x0194 )
#define REG_AON_APB_CPPLL_CFG1                 ( CTL_BASE_AON_APB + 0x0198 )
#define REG_AON_APB_CPPLL_CFG2                 ( CTL_BASE_AON_APB + 0x019C )
#define REG_AON_APB_CPPLL_BIST_CTRL            ( CTL_BASE_AON_APB + 0x01A0 )
#define REG_AON_APB_MPLL_CFG3                  ( CTL_BASE_AON_APB + 0x01B0 )
#define REG_AON_APB_DPLL_CFG3                  ( CTL_BASE_AON_APB + 0x01B4 )
#define REG_AON_APB_GPLL_CFG3                  ( CTL_BASE_AON_APB + 0x01B8 )
#define REG_AON_APB_CP_DAP_PAD_CTRL            ( CTL_BASE_AON_APB + 0x0200 )
#define REG_AON_APB_CA7_PROT_CTRL              ( CTL_BASE_AON_APB + 0x0204 )
#define REG_AON_APB_CSSYS_CFG                  ( CTL_BASE_AON_APB + 0x0208 )
#define REG_AON_APB_SEC_MUX_DBG_EN             ( CTL_BASE_AON_APB + 0x020C )
#define REG_AON_APB_CR5_PROT_CTRL              ( CTL_BASE_AON_APB + 0x0210 )
#define REG_AON_APB_DBG_DJTAG_CTRL             ( CTL_BASE_AON_APB + 0x0214 )
#define REG_AON_APB_WTLCP_CTRL                 ( CTL_BASE_AON_APB + 0x0240 )
#define REG_AON_APB_WTL_WCDMA_EB               ( CTL_BASE_AON_APB + 0x0244 )
#define REG_AON_APB_WTLCP_LDSP_CTRL0           ( CTL_BASE_AON_APB + 0x0248 )
#define REG_AON_APB_WTLCP_LDSP_CTRL1           ( CTL_BASE_AON_APB + 0x024C )
#define REG_AON_APB_WTLCP_TDSP_CTRL0           ( CTL_BASE_AON_APB + 0x0250 )
#define REG_AON_APB_WTLCP_TDSP_CTRL1           ( CTL_BASE_AON_APB + 0x0254 )
#define REG_AON_APB_PCP_AON_EB                 ( CTL_BASE_AON_APB + 0x0280 )
#define REG_AON_APB_PCP_SOFT_RST               ( CTL_BASE_AON_APB + 0x0284 )
#define REG_AON_APB_PUBCP_CTRL                 ( CTL_BASE_AON_APB + 0x0288 )
#define REG_AON_APB_SYS_DBG_SEL                ( CTL_BASE_AON_APB + 0x02B0 )
#define REG_AON_APB_MDAR_HSDL_CFG              ( CTL_BASE_AON_APB + 0x02B4 )
#define REG_AON_APB_SYS_DBG_SEL2               ( CTL_BASE_AON_APB + 0x02B8 )
#define REG_AON_APB_SUBSYS_DBG_CFG             ( CTL_BASE_AON_APB + 0x02BC )
#define REG_AON_APB_AP_LPC_CTRL                ( CTL_BASE_AON_APB + 0x02C0 )
#define REG_AON_APB_WTLCP_LPC_CTRL             ( CTL_BASE_AON_APB + 0x02C4 )
#define REG_AON_APB_PUBCP_LPC_CTRL             ( CTL_BASE_AON_APB + 0x02C8 )
#define REG_AON_APB_MDAR_SOFT_RST              ( CTL_BASE_AON_APB + 0x02D0 )
#define REG_AON_APB_GLB_WCDMA_CTRL             ( CTL_BASE_AON_APB + 0x0300 )
#define REG_AON_APB_PLL_CLKOUT_GATE            ( CTL_BASE_AON_APB + 0x0400 )
#define REG_AON_APB_HM_CFG_SEL                 ( CTL_BASE_AON_APB + 0x0404 )
#define REG_AON_APB_HM_PWR_CTRL                ( CTL_BASE_AON_APB + 0x0408 )
#define REG_AON_APB_HM_RST_CTRL                ( CTL_BASE_AON_APB + 0x040C )
#define REG_AON_APB_M_AAPC_CFG                 ( CTL_BASE_AON_APB + 0x0420 )
#define REG_AON_APB_DAP_DJTAG_CTRL             ( CTL_BASE_AON_APB + 0x0430 )
#define REG_AON_APB_CGM_REG1                   ( CTL_BASE_AON_APB + 0x0440 )
#define REG_AON_APB_TOP_LPC0                   ( CTL_BASE_AON_APB + 0x0500 )
#define REG_AON_APB_TOP_LPC1                   ( CTL_BASE_AON_APB + 0x0504 )
#define REG_AON_APB_TOP_LPC2                   ( CTL_BASE_AON_APB + 0x0508 )
#define REG_AON_APB_TOP_LPC3                   ( CTL_BASE_AON_APB + 0x050C )
#define REG_AON_APB_OVERHEAT_RST_CTRL          ( CTL_BASE_AON_APB + 0x0510 )
#define REG_AON_APB_AP_WPROT_EN1               ( CTL_BASE_AON_APB + 0x3004 )
#define REG_AON_APB_WTLCP_WPROT_EN1            ( CTL_BASE_AON_APB + 0x3008 )
#define REG_AON_APB_PUBCP_WPROT_EN1            ( CTL_BASE_AON_APB + 0x300C )
#define REG_AON_APB_IO_DLY_CTRL                ( CTL_BASE_AON_APB + 0x3014 )
#define REG_AON_APB_AP_WPROT_EN0               ( CTL_BASE_AON_APB + 0x3018 )
#define REG_AON_APB_WTLCP_WPROT_EN0            ( CTL_BASE_AON_APB + 0x3020 )
#define REG_AON_APB_PUBCP_WPROT_EN0            ( CTL_BASE_AON_APB + 0x3024 )
#define REG_AON_APB_PMU_RST_MONITOR            ( CTL_BASE_AON_APB + 0x302C )
#define REG_AON_APB_THM_RST_MONITOR            ( CTL_BASE_AON_APB + 0x3030 )
#define REG_AON_APB_AP_RST_MONITOR             ( CTL_BASE_AON_APB + 0x3034 )
#define REG_AON_APB_CA7_RST_MONITOR            ( CTL_BASE_AON_APB + 0x3038 )
#define REG_AON_APB_BOND_OPT0                  ( CTL_BASE_AON_APB + 0x303C )
#define REG_AON_APB_BOND_OPT1                  ( CTL_BASE_AON_APB + 0x3040 )
#define REG_AON_APB_RES_REG0                   ( CTL_BASE_AON_APB + 0x3044 )
#define REG_AON_APB_RES_REG1                   ( CTL_BASE_AON_APB + 0x3048 )
#define REG_AON_APB_AON_QOS_CFG                ( CTL_BASE_AON_APB + 0x304C )
#define REG_AON_APB_BB_LDO_CAL_START           ( CTL_BASE_AON_APB + 0x3050 )
#define REG_AON_APB_AON_MTX_PROT_CFG           ( CTL_BASE_AON_APB + 0x3058 )
#define REG_AON_APB_LVDS_CFG                   ( CTL_BASE_AON_APB + 0x3060 )
#define REG_AON_APB_PLL_LOCK_OUT_SEL           ( CTL_BASE_AON_APB + 0x3064 )
#define REG_AON_APB_RTC4M_RC_VAL               ( CTL_BASE_AON_APB + 0x3068 )
#define REG_AON_APB_FUNCTST_CTRL_0             ( CTL_BASE_AON_APB + 0x3070 )
#define REG_AON_APB_FUNCTST_CTRL_1             ( CTL_BASE_AON_APB + 0x3074 )
#define REG_AON_APB_FUNCTST_CTRL_2             ( CTL_BASE_AON_APB + 0x3078 )
#define REG_AON_APB_WDG_RST_FLAG               ( CTL_BASE_AON_APB + 0x3080 )
#define REG_AON_APB_CA7_CFG                    ( CTL_BASE_AON_APB + 0x3084 )
#define REG_AON_APB_RES_REG2                   ( CTL_BASE_AON_APB + 0x3090 )
#define REG_AON_APB_RES_REG3                   ( CTL_BASE_AON_APB + 0x3094 )
#define REG_AON_APB_RES_REG4                   ( CTL_BASE_AON_APB + 0x3098 )
#define REG_AON_APB_RES_REG5                   ( CTL_BASE_AON_APB + 0x309C )
#define REG_AON_APB_RES_REG6                   ( CTL_BASE_AON_APB + 0x30A0 )
#define REG_AON_APB_RES_REG7                   ( CTL_BASE_AON_APB + 0x30A4 )
#define REG_AON_APB_AON_APB_RSV                ( CTL_BASE_AON_APB + 0x30F0 )
#define REG_AON_APB_FUNCTION_DMA_BOOT_ADDR     ( CTL_BASE_AON_APB + 0x3110 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_APB_EB0
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_I2C_EB                                       BIT(31)
#define BIT_AON_APB_CA7_DAP_EB                                   BIT(30)
#define BIT_AON_APB_CA7_TS1_EB                                   BIT(29)
#define BIT_AON_APB_CA7_TS0_EB                                   BIT(28)
#define BIT_AON_APB_GPU_EB                                       BIT(27)
#define BIT_AON_APB_CKG_EB                                       BIT(26)
#define BIT_AON_APB_MM_EB                                        BIT(25)
#define BIT_AON_APB_AP_WDG_EB                                    BIT(24)
#define BIT_AON_APB_MSPI_EB                                      BIT(23)
#define BIT_AON_APB_SPLK_EB                                      BIT(22)
#define BIT_AON_APB_IPI_EB                                       BIT(21)
#define BIT_AON_APB_PIN_EB                                       BIT(20)
#define BIT_AON_APB_VBC_EB                                       BIT(19)
#define BIT_AON_APB_AUD_EB                                       BIT(18)
#define BIT_AON_APB_AUDIF_EB                                     BIT(17)
#define BIT_AON_APB_ADI_EB                                       BIT(16)
#define BIT_ADI_EB						BIT_AON_APB_ADI_EB
#define BIT_AON_APB_INTC_EB                                      BIT(15)
#define BIT_AON_APB_EIC_EB                                       BIT(14)
#define BIT_AON_APB_EFUSE_EB                                     BIT(13)
#define BIT_AON_APB_AP_TMR0_EB                                   BIT(12)
#define BIT_AON_APB_AON_TMR_EB                                   BIT(11)
#define BIT_AON_APB_AP_SYST_EB                                   BIT(10)
#define BIT_AON_APB_AON_SYST_EB                                  BIT(9)
#define BIT_AON_APB_KPD_EB                                       BIT(8)
#define BIT_AON_APB_PWM3_EB                                      BIT(7)
#define BIT_AON_APB_PWM2_EB                                      BIT(6)
#define BIT_AON_APB_PWM1_EB                                      BIT(5)
#define BIT_AON_APB_PWM0_EB                                      BIT(4)
#define BIT_AON_APB_GPIO_EB                                      BIT(3)
#define BIT_AON_APB_TPC_EB                                       BIT(2)
#define BIT_AON_APB_FM_EB                                        BIT(1)
#define BIT_AON_APB_ADC_EB                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_APB_EB1
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_SERDES_DPHY_EB                               BIT(31)
#define BIT_AON_APB_CROSS_TRIG_EB                                BIT(30)
#define BIT_AON_APB_DBG_EMC_EB                                   BIT(29)
#define BIT_AON_APB_DBG_EB                                       BIT(28)
#define BIT_AON_APB_ORP_JTAG_EB                                  BIT(27)
#define BIT_AON_APB_CA5_TS0_EB                                   BIT(26)
#define BIT_AON_APB_DEF_EB                                       BIT(25)
#define BIT_AON_APB_LVDS_PLL_DIV_EN                              BIT(24)
#define BIT_AON_APB_ARM7_JTAG_EB                                 BIT(23)
#define BIT_AON_APB_AON_DMA_EB                                   BIT(22)
#define BIT_AON_APB_MBOX_EB                                      BIT(21)
#define BIT_AON_APB_DJTAG_EB                                     BIT(20)
#define BIT_AON_APB_RTC4M1_CAL_EB                                BIT(19)
#define BIT_AON_APB_RTC4M0_CAL_EB                                BIT(18)
#define BIT_AON_APB_MDAR_EB                                      BIT(17)
#define BIT_AON_APB_LVDS_TCXO_EB                                 BIT(16)
#define BIT_AON_APB_LVDS_TRX_EB                                  BIT(15)
#define BIT_AON_APB_MM_VSP_EB                                    BIT(14)
#define BIT_AON_APB_GSP_EMC_EB                                   BIT(13)
#define BIT_AON_APB_ZIP_EMC_EB                                   BIT(12)
#define BIT_AON_APB_DISP_EMC_EB                                  BIT(11)
#define BIT_AON_APB_AP_TMR2_EB                                   BIT(10)
#define BIT_AON_APB_AP_TMR1_EB                                   BIT(9)
#define BIT_AON_APB_CA7_WDG_EB                                   BIT(8)
#define BIT_AON_APB_CLK_EMC_REF_EB                               BIT(7)
#define BIT_AON_APB_AVS_EB                                       BIT(6)
#define BIT_AON_APB_PROBE_EB                                     BIT(5)
#define BIT_AON_APB_AUX2_EB                                      BIT(4)
#define BIT_AON_APB_AUX1_EB                                      BIT(3)
#define BIT_AON_APB_AUX0_EB                                      BIT(2)
#define BIT_AON_APB_THM_EB                                       BIT(1)
#define BIT_AON_APB_PMU_EB                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_APB_RST0
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CA5_TS0_SOFT_RST                             BIT(31)
#define BIT_AON_APB_I2C_SOFT_RST                                 BIT(30)
#define BIT_AON_APB_CA7_TS1_SOFT_RST                             BIT(29)
#define BIT_AON_APB_CA7_TS0_SOFT_RST                             BIT(28)
#define BIT_AON_APB_DAP_MTX_SOFT_RST                             BIT(27)
#define BIT_AON_APB_MSPI1_SOFT_RST                               BIT(26)
#define BIT_AON_APB_MSPI0_SOFT_RST                               BIT(25)
#define BIT_AON_APB_SPLK_SOFT_RST                                BIT(24)
#define BIT_AON_APB_IPI_SOFT_RST                                 BIT(23)
#define BIT_AON_APB_CKG_SOFT_RST                                 BIT(22)
#define BIT_AON_APB_PIN_SOFT_RST                                 BIT(21)
#define BIT_AON_APB_VBC_SOFT_RST                                 BIT(20)
#define BIT_AON_APB_AUD_SOFT_RST                                 BIT(19)
#define BIT_AON_APB_AUDIF_SOFT_RST                               BIT(18)
#define BIT_AON_APB_ADI_SOFT_RST                                 BIT(17)
#define BIT_ADI_SOFT_RST					BIT_AON_APB_ADI_SOFT_RST
#define BIT_AON_APB_INTC_SOFT_RST                                BIT(16)
#define BIT_AON_APB_EIC_SOFT_RST                                 BIT(15)
#define BIT_AON_APB_EFUSE_SOFT_RST                               BIT(14)
#define BIT_AON_APB_AP_WDG_SOFT_RST                              BIT(13)
#define BIT_AON_APB_AP_TMR0_SOFT_RST                             BIT(12)
#define BIT_AON_APB_AON_TMR_SOFT_RST                             BIT(11)
#define BIT_AON_APB_AP_SYST_SOFT_RST                             BIT(10)
#define BIT_AON_APB_AON_SYST_SOFT_RST                            BIT(9)
#define BIT_AON_APB_KPD_SOFT_RST                                 BIT(8)
#define BIT_AON_APB_PWM3_SOFT_RST                                BIT(7)
#define BIT_AON_APB_PWM2_SOFT_RST                                BIT(6)
#define BIT_AON_APB_PWM1_SOFT_RST                                BIT(5)
#define BIT_AON_APB_PWM0_SOFT_RST                                BIT(4)
#define BIT_AON_APB_GPIO_SOFT_RST                                BIT(3)
#define BIT_AON_APB_TPC_SOFT_RST                                 BIT(2)
#define BIT_AON_APB_FM_SOFT_RST                                  BIT(1)
#define BIT_AON_APB_ADC_SOFT_RST                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_APB_RST1
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RTC4M_ANA_SOFT_RST                           BIT(31)
#define BIT_AON_APB_DEF_SLV_INT_SOFT_CLR                         BIT(30)
#define BIT_AON_APB_DEF_SOFT_RST                                 BIT(29)
#define BIT_AON_APB_ADC3_SOFT_RST                                BIT(28)
#define BIT_AON_APB_ADC2_SOFT_RST                                BIT(27)
#define BIT_AON_APB_ADC1_SOFT_RST                                BIT(26)
#define BIT_AON_APB_MBOX_SOFT_RST                                BIT(25)
#define BIT_AON_APB_ROSC_SOFT_RST                                BIT(24)
#define BIT_AON_APB_RTC4M1_CAL_SOFT_RST                          BIT(23)
#define BIT_AON_APB_RTC4M0_CAL_SOFT_RST                          BIT(22)
#define BIT_AON_APB_DAC3_SOFT_RST                                BIT(19)
#define BIT_AON_APB_DAC2_SOFT_RST                                BIT(18)
#define BIT_AON_APB_DAC1_SOFT_RST                                BIT(17)
#define BIT_AON_APB_ADC3_CAL_SOFT_RST                            BIT(16)
#define BIT_AON_APB_ADC2_CAL_SOFT_RST                            BIT(15)
#define BIT_AON_APB_ADC1_CAL_SOFT_RST                            BIT(14)
#define BIT_AON_APB_MDAR_SOFT_RST                                BIT(13)
#define BIT_AON_APB_LVDSDIS_SOFT_RST                             BIT(12)
#define BIT_AON_APB_BB_CAL_SOFT_RST                              BIT(11)
#define BIT_AON_APB_DCXO_LC_SOFT_RST                             BIT(10)
#define BIT_AON_APB_AP_TMR2_SOFT_RST                             BIT(9)
#define BIT_AON_APB_AP_TMR1_SOFT_RST                             BIT(8)
#define BIT_AON_APB_CA7_WDG_SOFT_RST                             BIT(7)
#define BIT_AON_APB_AON_DMA_SOFT_RST                             BIT(6)
#define BIT_AON_APB_AVS_SOFT_RST                                 BIT(5)
#define BIT_AON_APB_DMC_PHY_SOFT_RST                             BIT(4)
#define BIT_AON_APB_GPU_THMA_SOFT_RST                            BIT(3)
#define BIT_AON_APB_ARM_THMA_SOFT_RST                            BIT(2)
#define BIT_AON_APB_THM_SOFT_RST                                 BIT(1)
#define BIT_AON_APB_PMU_SOFT_RST                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_APB_RTC_EB
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_BB_CAL_RTC_EB                                BIT(18)
#define BIT_AON_APB_DCXO_LC_RTC_EB                               BIT(17)
#define BIT_AON_APB_AP_TMR2_RTC_EB                               BIT(16)
#define BIT_AON_APB_AP_TMR1_RTC_EB                               BIT(15)
#define BIT_AON_APB_GPU_THMA_RTC_AUTO_EN                         BIT(14)
#define BIT_AON_APB_ARM_THMA_RTC_AUTO_EN                         BIT(13)
#define BIT_AON_APB_GPU_THMA_RTC_EB                              BIT(12)
#define BIT_AON_APB_ARM_THMA_RTC_EB                              BIT(11)
#define BIT_AON_APB_THM_RTC_EB                                   BIT(10)
#define BIT_AON_APB_CA7_WDG_RTC_EB                               BIT(9)
#define BIT_AON_APB_AP_WDG_RTC_EB                                BIT(8)
#define BIT_AON_APB_EIC_RTCDV5_EB                                BIT(7)
#define BIT_AON_APB_EIC_RTC_EB                                   BIT(6)
#define BIT_AON_APB_AP_TMR0_RTC_EB                               BIT(5)
#define BIT_AON_APB_AON_TMR_RTC_EB                               BIT(4)
#define BIT_AON_APB_AP_SYST_RTC_EB                               BIT(3)
#define BIT_AON_APB_AON_SYST_RTC_EB                              BIT(2)
#define BIT_AON_APB_KPD_RTC_EB                                   BIT(1)
#define BIT_AON_APB_ARCH_RTC_EB                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_REC_26MHZ_BUF_CFG
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PLL_PROBE_SEL(x)                             (((x) & 0x3F) << 8)
#define BIT_AON_APB_REC_26MHZ_1_CUR_SEL                          BIT(4)
#define BIT_AON_APB_REC_26MHZ_0_CUR_SEL                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_SINDRV_CTRL
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CLK26M_TUNED_SEL                             BIT(20)
#define BIT_AON_APB_CLK26M_RESERVED(x)                           (((x) & 0x7FF) << 9)
#define BIT_AON_APB_REC_26MHZ_SR_TRIM(x)                         (((x) & 0xF) << 5)
#define BIT_AON_APB_SINDRV_LVL(x)                                (((x) & 0x3) << 3)
#define BIT_AON_APB_SINDRV_CLIP_MODE                             BIT(2)
#define BIT_AON_APB_SINDRV_ENA_SQUARE                            BIT(1)
#define BIT_AON_APB_SINDRV_ENA                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_ADA_SEL_CTRL
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_TW_MODE_SEL                                  BIT(3)
#define BIT_AON_APB_WGADC_DIV_EN                                 BIT(2)
#define BIT_AON_APB_AFCDAC_SYS_SEL                               BIT(1)
#define BIT_AON_APB_APCDAC_SYS_SEL                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_VBC_CTRL
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AUDIF_CKG_AUTO_EN                            BIT(20)
#define BIT_AON_APB_AUD_INT_SYS_SEL(x)                           (((x) & 0x3) << 18)
#define BIT_AON_APB_VBC_DA23_INT_SYS_SEL(x)                      (((x) & 0x3) << 16)
#define BIT_AON_APB_VBC_AD23_INT_SYS_SEL(x)                      (((x) & 0x3) << 14)
#define BIT_AON_APB_VBC_AD01_INT_SYS_SEL(x)                      (((x) & 0x3) << 12)
#define BIT_AON_APB_VBC_DA01_INT_SYS_SEL(x)                      (((x) & 0x3) << 10)
#define BIT_AON_APB_VBC_AD23_DMA_SYS_SEL(x)                      (((x) & 0x3) << 8)
#define BIT_AON_APB_VBC_AD01_DMA_SYS_SEL(x)                      (((x) & 0x3) << 6)
#define BIT_AON_APB_VBC_DA01_DMA_SYS_SEL(x)                      (((x) & 0x3) << 4)
#define BIT_AON_APB_VBC_DA23_DMA_SYS_SEL(x)                      (((x) & 0x3) << 2)
#define BIT_AON_APB_VBC_DMA_WTLCP_ARM_SEL                        BIT(1)
#define BIT_AON_APB_VBC_DMA_PUBCP_ARM_SEL                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PWR_CTRL
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_FORCE_DSI_DBG_PHY_SHUTDOWNZ                  BIT(21)
#define BIT_AON_APB_FORCE_CSI_S_PHY_SHUTDOWNZ                    BIT(20)
#define BIT_AON_APB_HSIC_PLL_EN                                  BIT(19)
#define BIT_AON_APB_HSIC_PHY_PD                                  BIT(18)
#define BIT_AON_APB_USB_PHY_PD_S                                 BIT(17)
#define BIT_AON_APB_USB_PHY_PD_L                                 BIT(16)
#define BIT_AON_APB_MIPI_DSI_PS_PD_S                             BIT(15)
#define BIT_AON_APB_MIPI_DSI_PS_PD_L                             BIT(14)
#define BIT_AON_APB_MIPI_CSI_2P2LANE_PS_PD_S                     BIT(13)
#define BIT_AON_APB_MIPI_CSI_2P2LANE_PS_PD_L                     BIT(12)
#define BIT_AON_APB_MIPI_CSI_2LANE_PS_PD_S                       BIT(11)
#define BIT_AON_APB_MIPI_CSI_2LANE_PS_PD_L                       BIT(10)
#define BIT_AON_APB_CA7_TS1_STOP                                 BIT(9)
#define BIT_AON_APB_CA7_TS0_STOP                                 BIT(8)
#define BIT_AON_APB_EFUSE_BIST_PWR_ON                            BIT(3)
#define BIT_AON_APB_FORCE_DSI_PHY_SHUTDOWNZ                      BIT(2)
#define BIT_AON_APB_FORCE_CSI_PHY_SHUTDOWNZ                      BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_TS_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DBG_TRACE_CTRL_EN                            BIT(14)
#define BIT_AON_APB_CSYSACK_TS_LP_2                              BIT(13)
#define BIT_AON_APB_CSYSREQ_TS_LP_2                              BIT(12)
#define BIT_AON_APB_CSYSACK_TS_LP_1                              BIT(11)
#define BIT_AON_APB_CSYSREQ_TS_LP_1                              BIT(10)
#define BIT_AON_APB_CSYSACK_TS_LP_0                              BIT(9)
#define BIT_AON_APB_CSYSREQ_TS_LP_0                              BIT(8)
#define BIT_AON_APB_EVENTACK_RESTARTREQ_TS01                     BIT(4)
#define BIT_AON_APB_EVENT_RESTARTREQ_TS01                        BIT(1)
#define BIT_AON_APB_EVENT_HALTREQ_TS01                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_BOOT_MODE
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_ARM_JTAG_EN                                  BIT(13)
#define BIT_AON_APB_WPLL_OVR_FREQ_SEL                            BIT(12)
#define BIT_AON_APB_PTEST_FUNC_ATSPEED_SEL                       BIT(8)
#define BIT_AON_APB_PTEST_FUNC_MODE                              BIT(7)
#define BIT_AON_APB_FUNCTST_DMA_EB                               BIT(5)
#define BIT_AON_APB_USB_DLOAD_EN                                 BIT(4)
#define BIT_AON_APB_ARM_BOOT_MD3                                 BIT(3)
#define BIT_AON_APB_ARM_BOOT_MD2                                 BIT(2)
#define BIT_AON_APB_ARM_BOOT_MD1                                 BIT(1)
#define BIT_AON_APB_ARM_BOOT_MD0                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_BB_BG_CTRL
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_BB_CON_BG                                    BIT(22)
#define BIT_AON_APB_BB_BG_RSV(x)                                 (((x) & 0x3) << 20)
#define BIT_AON_APB_BB_LDO_V(x)                                  (((x) & 0xF) << 16)
#define BIT_AON_APB_BB_BG_RBIAS_EN                               BIT(15)
#define BIT_AON_APB_BB_BG_IEXT_IB_EN                             BIT(14)
#define BIT_AON_APB_BB_LDO_REFCTRL(x)                            (((x) & 0x3) << 12)
#define BIT_AON_APB_BB_LDO_AUTO_PD_EN                            BIT(11)
#define BIT_AON_APB_BB_LDO_SLP_PD_EN                             BIT(10)
#define BIT_AON_APB_BB_LDO_FORCE_ON                              BIT(9)
#define BIT_AON_APB_BB_LDO_FORCE_PD                              BIT(8)
#define BIT_AON_APB_BB_BG_AUTO_PD_EN                             BIT(3)
#define BIT_AON_APB_BB_BG_SLP_PD_EN                              BIT(2)
#define BIT_AON_APB_BB_BG_FORCE_ON                               BIT(1)
#define BIT_AON_APB_BB_BG_FORCE_PD                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CP_ARM_JTAG_CTRL
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CP_ARM_JTAG_PIN_SEL(x)                       (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PLL_SOFT_CNT_DONE
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RC1_SOFT_CNT_DONE                            BIT(13)
#define BIT_AON_APB_RC0_SOFT_CNT_DONE                            BIT(12)
#define BIT_AON_APB_XTLBUF1_SOFT_CNT_DONE                        BIT(9)
#define BIT_AON_APB_XTLBUF0_SOFT_CNT_DONE                        BIT(8)
#define BIT_AON_APB_LVDSPLL_SOFT_CNT_DONE                        BIT(4)
#define BIT_AON_APB_LPLL_SOFT_CNT_DONE                           BIT(3)
#define BIT_AON_APB_TWPLL_SOFT_CNT_DONE                          BIT(2)
#define BIT_AON_APB_DPLL_SOFT_CNT_DONE                           BIT(1)
#define BIT_AON_APB_MPLL_SOFT_CNT_DONE                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DCXO_LC_REG0
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DCXO_LC_FLAG                                 BIT(8)
#define BIT_AON_APB_DCXO_LC_FLAG_CLR                             BIT(1)
#define BIT_AON_APB_DCXO_LC_CNT_CLR                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DCXO_LC_REG1
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DCXO_LC_CNT(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_MPLL_CFG1
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_MPLL_RES(x)                                  (((x) & 0xFF) << 22)
#define BIT_AON_APB_MPLL_LOCK_DONE                               BIT(21)
#define BIT_AON_APB_MPLL_DIV_S                                   BIT(20)
#define BIT_AON_APB_MPLL_MOD_EN                                  BIT(19)
#define BIT_AON_APB_MPLL_SDM_EN                                  BIT(18)
#define BIT_AON_APB_MPLL_LPF(x)                                  (((x) & 0x7) << 15)
#define BIT_AON_APB_MPLL_IBIAS(x)                                (((x) & 0x3) << 11)
#define BIT_AON_APB_MPLL_N(x)                                    (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_MPLL_CFG2
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_MPLL_POSTDIV                                 BIT(30)
#define BIT_AON_APB_MPLL_NINT(x)                                 (((x) & 0x7F) << 23)
#define BIT_AON_APB_MPLL_KINT(x)                                 (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DPLL_CFG1
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DPLL_RES(x)                                  (((x) & 0xFF) << 22)
#define BIT_AON_APB_DPLL_LOCK_DONE                               BIT(21)
#define BIT_AON_APB_DPLL_DIV_S                                   BIT(20)
#define BIT_AON_APB_DPLL_MOD_EN                                  BIT(19)
#define BIT_AON_APB_DPLL_SDM_EN                                  BIT(18)
#define BIT_AON_APB_DPLL_LPF(x)                                  (((x) & 0x7) << 15)
#define BIT_AON_APB_DPLL_IBIAS(x)                                (((x) & 0x3) << 11)
#define BIT_AON_APB_DPLL_N(x)                                    (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DPLL_CFG2
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DPLL_NINT(x)                                 (((x) & 0x7F) << 23)
#define BIT_AON_APB_DPLL_KINT(x)                                 (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_TWPLL_CFG1
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_TWPLL_RES(x)                                 (((x) & 0xFF) << 22)
#define BIT_AON_APB_TWPLL_LOCK_DONE                              BIT(21)
#define BIT_AON_APB_TWPLL_DIV_S                                  BIT(20)
#define BIT_AON_APB_TWPLL_MOD_EN                                 BIT(19)
#define BIT_AON_APB_TWPLL_SDM_EN                                 BIT(18)
#define BIT_AON_APB_TWPLL_LPF(x)                                 (((x) & 0x7) << 15)
#define BIT_AON_APB_TWPLL_IBIAS(x)                               (((x) & 0x3) << 11)
#define BIT_AON_APB_TWPLL_N(x)                                   (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_TWPLL_CFG2
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_TWPLL_NINT(x)                                (((x) & 0x7F) << 23)
#define BIT_AON_APB_TWPLL_KINT(x)                                (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_LTEPLL_CFG1
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LTEPLL_RES(x)                                (((x) & 0xFF) << 22)
#define BIT_AON_APB_LTEPLL_LOCK_DONE                             BIT(21)
#define BIT_AON_APB_LTEPLL_DIV_S                                 BIT(20)
#define BIT_AON_APB_LTEPLL_MOD_EN                                BIT(19)
#define BIT_AON_APB_LTEPLL_SDM_EN                                BIT(18)
#define BIT_AON_APB_LTEPLL_LPF(x)                                (((x) & 0x7) << 15)
#define BIT_AON_APB_LTEPLL_IBIAS(x)                              (((x) & 0x3) << 11)
#define BIT_AON_APB_LTEPLL_N(x)                                  (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_LTEPLL_CFG2
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LTEPLL_NINT(x)                               (((x) & 0x7F) << 23)
#define BIT_AON_APB_LTEPLL_KINT(x)                               (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_LVDSRFPLL_CFG1
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LVDSRFPLL_RES(x)                             (((x) & 0xFF) << 22)
#define BIT_AON_APB_LVDSRFPLL_LOCK_DONE                          BIT(21)
#define BIT_AON_APB_LVDSRFPLL_DIV_S                              BIT(20)
#define BIT_AON_APB_LVDSRFPLL_MOD_EN                             BIT(19)
#define BIT_AON_APB_LVDSRFPLL_SDM_EN                             BIT(18)
#define BIT_AON_APB_LVDSRFPLL_LPF(x)                             (((x) & 0x7) << 15)
#define BIT_AON_APB_LVDSRFPLL_IBIAS(x)                           (((x) & 0x3) << 11)
#define BIT_AON_APB_LVDSRFPLL_N(x)                               (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_LVDSRFPLL_CFG2
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LVDSRF_PLL_CLKOUT_EN                         BIT(30)
#define BIT_AON_APB_LVDSRFPLL_NINT(x)                            (((x) & 0x3F) << 24)
#define BIT_AON_APB_LVDSRFPLL_KINT(x)                            (((x) & 0xFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_REG_PROT
// Register Offset : 0x006C
// Description     : Big endian protect register
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LDSP_CTRL_PROT                               BIT(31)
#define BIT_AON_APB_REG_PROT_VAL(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DSI_PHY_CTRL
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DSI_IF_SEL                                   BIT(24)
#define BIT_AON_APB_DSI_TRIMBG(x)                                (((x) & 0xF) << 20)
#define BIT_AON_APB_DSI_RCTL(x)                                  (((x) & 0xF) << 16)
#define BIT_AON_APB_DSI_RES(x)                                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CSI_2L_PHY_CTRL
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CSI_2L_IF_SEL                                BIT(20)
#define BIT_AON_APB_CSI_2L_RCTL(x)                               (((x) & 0xF) << 16)
#define BIT_AON_APB_CSI_2L_RES(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CSI_2P2L_S_PHY_CTRL
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CSI_2P2L_TESTCLR_S                           BIT(23)
#define BIT_AON_APB_CSI_2P2L_TESTCLR_S_SEL                       BIT(22)
#define BIT_AON_APB_CSI_2P2L_TESTCLK_S_EN                        BIT(21)
#define BIT_AON_APB_CSI_2P2L_S_IF_SEL                            BIT(20)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CSI_2P2L_M_PHY_CTRL
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CSI_2P2L_TESTCLR_M                           BIT(23)
#define BIT_AON_APB_CSI_2P2L_TESTCLR_M_SEL                       BIT(22)
#define BIT_AON_APB_CSI_2P2L_TESTCLK_M_EN                        BIT(21)
#define BIT_AON_APB_CSI_2P2L_M_IF_SEL                            BIT(20)
#define BIT_AON_APB_CSI_2P2L_RCTL(x)                             (((x) & 0xF) << 16)
#define BIT_AON_APB_CSI_2P2L_RES(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CSI_2P2L_DBG_PHY_CTRL
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CSI_2P2L_DBG_EN                              BIT(25)
#define BIT_AON_APB_CSI_2P2L_DBG_IF_SEL                          BIT(24)
#define BIT_AON_APB_CSI_2P2L_DBG_TRIMBG(x)                       (((x) & 0xF) << 20)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CSI_2P2L_PHY_CTRL
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CSI_2P2L_MODE_SEL                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_CGM_CFG
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PROBE_CKG_DIV(x)                             (((x) & 0xF) << 28)
#define BIT_AON_APB_AUX2_CKG_DIV(x)                              (((x) & 0xF) << 24)
#define BIT_AON_APB_AUX1_CKG_DIV(x)                              (((x) & 0xF) << 20)
#define BIT_AON_APB_AUX0_CKG_DIV(x)                              (((x) & 0xF) << 16)
#define BIT_AON_APB_PROBE_CKG_SEL(x)                             (((x) & 0xF) << 12)
#define BIT_AON_APB_AUX2_CKG_SEL(x)                              (((x) & 0xF) << 8)
#define BIT_AON_APB_AUX1_CKG_SEL(x)                              (((x) & 0xF) << 4)
#define BIT_AON_APB_AUX0_CKG_SEL(x)                              (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_SOFT_DFS_CTRL
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUB_DFS_SW_SWITCH_PERIOD(x)                  (((x) & 0xFF) << 16)
#define BIT_AON_APB_PUB_DFS_SW_RATIO(x)                          (((x) & 0x1F) << 6)
#define BIT_AON_APB_PUB_DFS_SW_FRQ_SEL(x)                        (((x) & 0x3) << 4)
#define BIT_AON_APB_PUB_DFS_SW_RESP                              BIT(3)
#define BIT_AON_APB_PUB_DFS_SW_ACK                               BIT(2)
#define BIT_AON_APB_PUB_DFS_SW_REQ                               BIT(1)
#define BIT_AON_APB_PUB_DFS_SW_ENABLE                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_HARD_DFS_CTRL_LO
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUB_DFS_HW_INITIAL_FREQ(x)                   (((x) & 0x3) << 3)
#define BIT_AON_APB_PUB_DFS_HW_STOP                              BIT(2)
#define BIT_AON_APB_PUB_DFS_HW_START                             BIT(1)
#define BIT_AON_APB_PUB_DFS_HW_ENABLE                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_HARD_DFS_CTRL_HI
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUB_DFS_HW_SWITCH_PERIOD(x)                  (((x) & 0xFF) << 20)
#define BIT_AON_APB_PUB_DFS_HW_F3_RATIO(x)                       (((x) & 0x1F) << 15)
#define BIT_AON_APB_PUB_DFS_HW_F2_RATIO(x)                       (((x) & 0x1F) << 10)
#define BIT_AON_APB_PUB_DFS_HW_F1_RATIO(x)                       (((x) & 0x1F) << 5)
#define BIT_AON_APB_PUB_DFS_HW_F0_RATIO(x)                       (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_APB_EB2
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AP_DAP_EB                                    BIT(15)
#define BIT_AON_APB_BSMTMR_EB                                    BIT(14)
#define BIT_AON_APB_ANLG_APB_EB                                  BIT(13)
#define BIT_AON_APB_PIN_APB_EB                                   BIT(12)
#define BIT_AON_APB_ANLG_EB                                      BIT(11)
#define BIT_AON_APB_BUSMON_DMA_EB                                BIT(10)
#define BIT_AON_APB_SERDES_DPHY_REF_EB                           BIT(9)
#define BIT_AON_APB_SERDES_DPHY_CFG_EB                           BIT(8)
#define BIT_AON_APB_ROSC_EB                                      BIT(7)
#define BIT_AON_APB_PUB_REG_EB                                   BIT(6)
#define BIT_AON_APB_DMC_EB                                       BIT(5)
#define BIT_AON_APB_CSSYS_EB                                     BIT(4)
#define BIT_AON_APB_RFTI_RX_EB                                   BIT(3)
#define BIT_AON_APB_RFTI_TX_EB                                   BIT(2)
#define BIT_AON_APB_WCDMA_ICI_EB                                 BIT(1)
#define BIT_AON_APB_WCDMA_EB                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_ROSC_CFG
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_ROSC_NUM(x)                                  (((x) & 0xFFFF) << 12)
#define BIT_AON_APB_ROSC_SEL(x)                                  (((x) & 0x7FF) << 1)
#define BIT_AON_APB_ROSC_EN                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_ROSC_STATUS
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_ROSC_CNT(x)                                  (((x) & 0xFFFF) << 1)
#define BIT_AON_APB_ROSC_VALID                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_ANALOG_RSV
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_ANALOG_MPLL_DPLL_TOP_RSV(x)                  (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_CHIP_ID0
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_CHIP_ID0(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_CHIP_ID1
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_CHIP_ID1(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_PLAT_ID0
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_PLAT_ID0(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_PLAT_ID1
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_PLAT_ID1(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_IMPL_ID
// Register Offset : 0x00F0
// Description     : IMPL_ID
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_IMPL_ID(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_MFT_ID
// Register Offset : 0x00F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_MFT_ID(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_VER_ID
// Register Offset : 0x00F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_VER_ID(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_CHIP_ID
// Register Offset : 0x00FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_CHIP_ID(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CCIR_RCVR_CFG
// Register Offset : 0x0100
// Description     : APB clock control
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CCIR_SE                                      BIT(1)
#define BIT_AON_APB_CCIR_IE                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PLL_BG_CFG
// Register Offset : 0x0108
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PLL_BG_RSV(x)                                (((x) & 0x3) << 4)
#define BIT_AON_APB_PLL_BG_RBIAS_EN                              BIT(3)
#define BIT_AON_APB_PLL_BG_PD                                    BIT(2)
#define BIT_AON_APB_PLL_BG_IEXT_IBEN                             BIT(1)
#define BIT_AON_APB_PLL_CON_BG                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_LVDSDIS_SEL
// Register Offset : 0x010C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LVDSDIS_LOG_SEL(x)                           (((x) & 0x3) << 1)
#define BIT_AON_APB_LVDSDIS_DBG_SEL                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DJTAG_MUX_SEL
// Register Offset : 0x0110
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DJTAG_AON_SEL                                BIT(6)
#define BIT_AON_APB_DJTAG_PUB_SEL                                BIT(5)
#define BIT_AON_APB_DJTAG_PUBCP_SEL                              BIT(4)
#define BIT_AON_APB_DJTAG_WTLCP_SEL                              BIT(3)
#define BIT_AON_APB_DJTAG_GPU_SEL                                BIT(2)
#define BIT_AON_APB_DJTAG_MM_SEL                                 BIT(1)
#define BIT_AON_APB_DJTAG_AP_SEL                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_ARM7_SYS_SOFT_RST
// Register Offset : 0x0114
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_ARM7_SYS_SOFT_RST                            BIT(4)
#define BIT_AON_APB_ARM7_CORE_SOFT_RST                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PUBCP_WTLCP_ADDR_MSB
// Register Offset : 0x0118
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUBCP_WTLCP_ADDR_MSB(x)                      (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_DMA_INT_EN
// Register Offset : 0x011C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_DMA_INT_ARM7_EN                          BIT(6)
#define BIT_AON_APB_AON_DMA_INT_AP_EN                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_EMC_AUTO_GATE_EN
// Register Offset : 0x0120
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUBCP_PUB_AUTO_GATE_EN                       BIT(19)
#define BIT_AON_APB_WTLCP_PUB_AUTO_GATE_EN                       BIT(18)
#define BIT_AON_APB_AP_PUB_AUTO_GATE_EN                          BIT(17)
#define BIT_AON_APB_AON_APB_PUB_AUTO_GATE_EN                     BIT(16)
#define BIT_AON_APB_PUBCP_EMC_AUTO_GATE_EN                       BIT(3)
#define BIT_AON_APB_WTLCP_EMC_AUTO_GATE_EN                       BIT(2)
#define BIT_AON_APB_AP_EMC_AUTO_GATE_EN                          BIT(1)
#define BIT_AON_APB_CA7_EMC_AUTO_GATE_EN                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_ARM7_CFG_BUS
// Register Offset : 0x0124
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_ARM7_CFG_BUS_SLEEP                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RTC4M_0_CFG
// Register Offset : 0x0128
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RTC4M0_RSV(x)                                (((x) & 0xFF) << 16)
#define BIT_AON_APB_RTC4M0_I_C(x)                                (((x) & 0xF) << 8)
#define BIT_AON_APB_RTC4M0_CAL_DONE                              BIT(6)
#define BIT_AON_APB_RTC4M0_CAL_START                             BIT(5)
#define BIT_AON_APB_RTC4M0_CHOP_EN                               BIT(4)
#define BIT_AON_APB_RTC4M0_FORCE_EN                              BIT(1)
#define BIT_AON_APB_RTC4M0_AUTO_GATE_EN                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RTC4M_1_CFG
// Register Offset : 0x012C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RTC4M1_RSV(x)                                (((x) & 0xFF) << 16)
#define BIT_AON_APB_RTC4M1_I_C(x)                                (((x) & 0xF) << 8)
#define BIT_AON_APB_RTC4M1_CAL_DONE                              BIT(6)
#define BIT_AON_APB_RTC4M1_CAL_START                             BIT(5)
#define BIT_AON_APB_RTC4M1_CHOP_EN                               BIT(4)
#define BIT_AON_APB_RTC4M1_FORCE_EN                              BIT(1)
#define BIT_AON_APB_RTC4M1_AUTO_GATE_EN                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_APB_RST2
// Register Offset : 0x0130
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_THM1_SOFT_RST                                BIT(19)
#define BIT_AON_APB_BSMTMR_SOFT_RST                              BIT(18)
#define BIT_AON_APB_WTLCP_TDSP_CORE_SRST                         BIT(17)
#define BIT_AON_APB_WTLCP_LDSP_CORE_SRST                         BIT(16)
#define BIT_AON_APB_ANLG_SOFT_RST                                BIT(14)
#define BIT_AON_APB_SERDES_DPHY_APB_SOFT_RST                     BIT(13)
#define BIT_AON_APB_BUSMON_DMA_SOFT_RST                          BIT(12)
#define BIT_AON_APB_SERDES_DPHY_SOFT_RST                         BIT(11)
#define BIT_AON_APB_CROSS_TRIG_SOFT_RST                          BIT(10)
#define BIT_AON_APB_SERDES_SOFT_RST                              BIT(9)
#define BIT_AON_APB_DBG_SOFT_RST                                 BIT(8)
#define BIT_AON_APB_DJTAG_SOFT_RST                               BIT(7)
#define BIT_AON_APB_AON_DJTAG_SOFT_RST                           BIT(6)
#define BIT_AON_APB_PUB_DJTAG_SOFT_RST                           BIT(5)
#define BIT_AON_APB_GPU_DJTAG_SOFT_RST                           BIT(4)
#define BIT_AON_APB_MM_DJTAG_SOFT_RST                            BIT(3)
#define BIT_AON_APB_PUBCP_DJTAG_SOFT_RST                         BIT(2)
#define BIT_AON_APB_WTLCP_DJTAG_SOFT_RST                         BIT(1)
#define BIT_AON_APB_AP_DJTAG_SOFT_RST                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CLK_EB0
// Register Offset : 0x0134
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_ALL_PLL_TEST_EB                              BIT(18)
#define BIT_AON_APB_LVDSRF_CALI_EB                               BIT(17)
#define BIT_AON_APB_RFTI2_LTH_EB                                 BIT(16)
#define BIT_AON_APB_RFTI2_XO_EB                                  BIT(15)
#define BIT_AON_APB_RFTI1_LTH_EB                                 BIT(14)
#define BIT_AON_APB_RFTI1_XO_EB                                  BIT(13)
#define BIT_AON_APB_RFTI_SBI_EB                                  BIT(12)
#define BIT_AON_APB_TMR_EB                                       BIT(11)
#define BIT_AON_APB_DET_32K_EB                                   BIT(10)
#define BIT_AON_APB_AP_HS_SPI_EB                                 BIT(9)
#define BIT_AON_APB_CSSYS_CA7_EB                                 BIT(8)
#define BIT_AON_APB_SDIO2_2X_EB                                  BIT(7)
#define BIT_AON_APB_SDIO2_1X_EB                                  BIT(6)
#define BIT_AON_APB_SDIO1_2X_EB                                  BIT(5)
#define BIT_AON_APB_SDIO1_1X_EB                                  BIT(4)
#define BIT_AON_APB_SDIO0_2X_EB                                  BIT(3)
#define BIT_AON_APB_SDIO0_1X_EB                                  BIT(2)
#define BIT_AON_APB_EMMC_2X_EB                                   BIT(1)
#define BIT_AON_APB_EMMC_1X_EB                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_SDIO
// Register Offset : 0x0138
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CP_SDIO_ENABLE                               BIT(2)
#define BIT_AON_APB_AP_SDIO_ENABLE                               BIT(1)
#define BIT_AON_APB_SDIO_MODULE_SEL                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_MPLL_CTRL
// Register Offset : 0x013C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CGM_MPLL_CA7_FORCE_EN                        BIT(9)
#define BIT_AON_APB_CGM_MPLL_CA7_AUTO_GATE_SEL                   BIT(8)
#define BIT_AON_APB_MPLL_WAIT_FORCE_EN                           BIT(2)
#define BIT_AON_APB_MPLL_WAIT_AUTO_GATE_SEL                      BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_GPLL_CFG1
// Register Offset : 0x0150
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_GPLL_RES(x)                                  (((x) & 0xFF) << 22)
#define BIT_AON_APB_GPLL_LOCK_DONE                               BIT(21)
#define BIT_AON_APB_GPLL_DIV_S                                   BIT(20)
#define BIT_AON_APB_GPLL_MOD_EN                                  BIT(19)
#define BIT_AON_APB_GPLL_SDM_EN                                  BIT(18)
#define BIT_AON_APB_GPLL_LPF(x)                                  (((x) & 0x7) << 15)
#define BIT_AON_APB_GPLL_IBIAS(x)                                (((x) & 0x3) << 11)
#define BIT_AON_APB_GPLL_N(x)                                    (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_GPLL_CFG2
// Register Offset : 0x0154
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_GPLL_POSTDIV                                 BIT(30)
#define BIT_AON_APB_GPLL_NINT(x)                                 (((x) & 0x7F) << 23)
#define BIT_AON_APB_GPLL_KINT(x)                                 (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RPLL_CFG1
// Register Offset : 0x0158
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RPLL_LOCK_DONE                               BIT(21)
#define BIT_AON_APB_RPLL_DIV_S                                   BIT(20)
#define BIT_AON_APB_RPLL_MOD_EN                                  BIT(19)
#define BIT_AON_APB_RPLL_SDM_EN                                  BIT(18)
#define BIT_AON_APB_RPLL_LPF(x)                                  (((x) & 0x7) << 15)
#define BIT_AON_APB_RPLL_REFIN(x)                                (((x) & 0x3) << 13)
#define BIT_AON_APB_RPLL_IBIAS(x)                                (((x) & 0x3) << 11)
#define BIT_AON_APB_RPLL_N(x)                                    (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RPLL_CFG2
// Register Offset : 0x015C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RPLL_NINT(x)                                 (((x) & 0x7F) << 23)
#define BIT_AON_APB_RPLL_KINT(x)                                 (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RPLL_CFG3
// Register Offset : 0x0160
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RPLL_RES(x)                                  (((x) & 0x7FFF) << 16)
#define BIT_AON_APB_RPLL_26M_SEL                                 BIT(7)
#define BIT_AON_APB_RPLL_DIV1_EN                                 BIT(6)
#define BIT_AON_APB_RPLL_26M_DIV(x)                              (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_THM0_CTRL
// Register Offset : 0x0164
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_THM0_CALI_RSVD(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_THM1_CTRL
// Register Offset : 0x0168
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_THM1_CALI_RSVD(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_BUSMON_DMA_CFG
// Register Offset : 0x0170
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_BUSMON_DMA_CNT_START                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_ANALOG_CFG0
// Register Offset : 0x0174
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_ANALOG_PLL_RSV(x)                            (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_ANALOG_TESTMUX(x)                            (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_ANALOG_CFG1
// Register Offset : 0x0178
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_ANALOG_BB_RSV(x)                             (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RPLL_BIST_CTRL
// Register Offset : 0x017C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RPLL_BIST_CNT(x)                             (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_RPLL_BIST_CTRL(x)                            (((x) & 0x1FF) << 1)
#define BIT_AON_APB_RPLL_BIST_EN                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_MPLL_BIST_CTRL
// Register Offset : 0x0180
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_MPLL_BIST_CNT(x)                             (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_MPLL_BIST_CTRL(x)                            (((x) & 0x1FF) << 1)
#define BIT_AON_APB_MPLL_BIST_EN                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DPLL_BIST_CTRL
// Register Offset : 0x0184
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DPLL_BIST_CNT(x)                             (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_DPLL_BIST_CTRL(x)                            (((x) & 0x1FF) << 1)
#define BIT_AON_APB_DPLL_BIST_EN                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_GPLL_BIST_CTRL
// Register Offset : 0x0188
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_GPLL_BIST_CNT(x)                             (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_GPLL_BIST_CTRL(x)                            (((x) & 0x1FF) << 1)
#define BIT_AON_APB_GPLL_BIST_EN                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_TWPLL_BIST_CTRL
// Register Offset : 0x018C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_TWPLL_BIST_CNT(x)                            (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_TWPLL_BIST_CTRL(x)                           (((x) & 0x1FF) << 1)
#define BIT_AON_APB_TWPLL_BIST_EN                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_LPLL_BIST_CTRL
// Register Offset : 0x0190
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LPLL_BIST_CNT(x)                             (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_LPLL_BIST_CTRL(x)                            (((x) & 0x1FF) << 1)
#define BIT_AON_APB_LPLL_BIST_EN                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DPLL_CTRL
// Register Offset : 0x0194
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CGM_DPLL_40M_AON_FORCE_EN                    BIT(10)
#define BIT_AON_APB_CGM_DPLL_40M_AON_AUTO_GATE_SEL               BIT(9)
#define BIT_AON_APB_CGM_DPLL_AON_FORCE_EN                        BIT(8)
#define BIT_AON_APB_CGM_DPLL_AON_AUTO_GATE_SEL                   BIT(7)
#define BIT_AON_APB_CGM_DPLL_AP_FORCE_EN                         BIT(6)
#define BIT_AON_APB_CGM_DPLL_AP_AUTO_GATE_SEL                    BIT(5)
#define BIT_AON_APB_DPLL_DIV_40M_FORCE_EN                        BIT(4)
#define BIT_AON_APB_DPLL_DIV_40M_AUTO_GATE_SEL                   BIT(3)
#define BIT_AON_APB_DPLL_WAIT_FORCE_EN                           BIT(2)
#define BIT_AON_APB_DPLL_WAIT_AUTO_GATE_SEL                      BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CPPLL_CFG1
// Register Offset : 0x0198
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CPPLL_RES(x)                                 (((x) & 0xFF) << 22)
#define BIT_AON_APB_CPPLL_LOCK_DONE                              BIT(21)
#define BIT_AON_APB_CPPLL_DIV_S                                  BIT(20)
#define BIT_AON_APB_CPPLL_MOD_EN                                 BIT(19)
#define BIT_AON_APB_CPPLL_SDM_EN                                 BIT(18)
#define BIT_AON_APB_CPPLL_LPF(x)                                 (((x) & 0x7) << 15)
#define BIT_AON_APB_CPPLL_IBIAS(x)                               (((x) & 0x3) << 11)
#define BIT_AON_APB_CPPLL_N(x)                                   (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CPPLL_CFG2
// Register Offset : 0x019C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CPPLL_POSTDIV                                BIT(30)
#define BIT_AON_APB_CPPLL_NINT(x)                                (((x) & 0x7F) << 23)
#define BIT_AON_APB_CPPLL_KINT(x)                                (((x) & 0x7FFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CPPLL_BIST_CTRL
// Register Offset : 0x01A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CPPLL_BIST_CNT(x)                            (((x) & 0xFFFF) << 16)
#define BIT_AON_APB_CPPLL_BIST_CTRL(x)                           (((x) & 0x1FF) << 1)
#define BIT_AON_APB_CPPLL_BIST_EN                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_MPLL_CFG3
// Register Offset : 0x01B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_MPLL_CCS_CTRL(x)                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DPLL_CFG3
// Register Offset : 0x01B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DPLL_CCS_CTRL(x)                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_GPLL_CFG3
// Register Offset : 0x01B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_GPLL_CCS_CTRL(x)                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CP_DAP_PAD_CTRL
// Register Offset : 0x0200
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CP_DAP_PAD_SEL(x)                            (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CA7_PROT_CTRL
// Register Offset : 0x0204
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CA7_SPNIDEN(x)                               (((x) & 0xF) << 12)
#define BIT_AON_APB_CA7_SPIDEN(x)                                (((x) & 0xF) << 8)
#define BIT_AON_APB_CA7_NIDEN(x)                                 (((x) & 0xF) << 4)
#define BIT_AON_APB_CA7_DBGEN(x)                                 (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CSSYS_CFG
// Register Offset : 0x0208
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DAP_DEVICEEN                                 BIT(31)
#define BIT_AON_APB_DAP_DBGEN                                    BIT(30)
#define BIT_AON_APB_DAP_SPIDBGEN                                 BIT(29)
#define BIT_AON_APB_TG_JTAG_EN                                   BIT(9)
#define BIT_AON_APB_LTE_JTAG_EN                                  BIT(8)
#define BIT_AON_APB_ARM7_JTAG_EN                                 BIT(7)
#define BIT_AON_APB_DJTAG_EN                                     BIT(6)
#define BIT_AON_APB_AG_JTAG_EN                                   BIT(5)
#define BIT_AON_APB_MJTAG_EN                                     BIT(4)
#define BIT_AON_APB_CSSYS_NIDEN                                  BIT(3)
#define BIT_AON_APB_CSSYS_SPNIDEN                                BIT(2)
#define BIT_AON_APB_CSSYS_SPIDEN                                 BIT(1)
#define BIT_AON_APB_CSSYS_DBGEN                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_SEC_MUX_DBG_EN
// Register Offset : 0x020C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DAP_DEVICEEN_S                               BIT(25)
#define BIT_AON_APB_DAP_DBGEN_S                                  BIT(24)
#define BIT_AON_APB_DAP_SPIDBGEN_S                               BIT(23)
#define BIT_AON_APB_CR5_DBGEN_S                                  BIT(16)
#define BIT_AON_APB_CR5_NIDEN_S                                  BIT(15)
#define BIT_AON_APB_CSSYS_DBGEN_S                                BIT(14)
#define BIT_AON_APB_CSSYS_NIDEN_S                                BIT(13)
#define BIT_AON_APB_CSSYS_SPIDEN_S                               BIT(12)
#define BIT_AON_APB_CSSYS_SPNIDEN_S                              BIT(11)
#define BIT_AON_APB_CA7_DBGEN_S                                  BIT(10)
#define BIT_AON_APB_CA7_NIDEN_S                                  BIT(9)
#define BIT_AON_APB_CA7_SPIDEN_S                                 BIT(8)
#define BIT_AON_APB_CA7_SPNIDEN_S                                BIT(7)
#define BIT_AON_APB_DJTAG_EN_S                                   BIT(2)
#define BIT_AON_APB_AG_JTAG_EN_S                                 BIT(1)
#define BIT_AON_APB_MJTAG_EN_S                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CR5_PROT_CTRL
// Register Offset : 0x0210
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CR5_NIDEN                                    BIT(1)
#define BIT_AON_APB_CR5_DBGEN                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DBG_DJTAG_CTRL
// Register Offset : 0x0214
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DBGSYS_CSSYS_STM_NSGUAREN                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WTLCP_CTRL
// Register Offset : 0x0240
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_AON_FRC_WSYS_LT_STOP                   BIT(4)
#define BIT_AON_APB_WTLCP_AON_FRC_WSYS_STOP                      BIT(3)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WTL_WCDMA_EB
// Register Offset : 0x0244
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_WCMDA_EB                               BIT(16)
#define BIT_AON_APB_WCDMA_AUTO_GATE_EN                           BIT(8)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WTLCP_LDSP_CTRL0
// Register Offset : 0x0248
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_LDSP_BOOT_VECTOR(x)                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WTLCP_LDSP_CTRL1
// Register Offset : 0x024C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_STCK_LDSP                              BIT(13)
#define BIT_AON_APB_WTLCP_STMS_LDSP                              BIT(12)
#define BIT_AON_APB_WTLCP_STDO_LDSP                              BIT(11)
#define BIT_AON_APB_WTLCP_STDI_LDSP                              BIT(10)
#define BIT_AON_APB_WTLCP_STRTCK_LDSP                            BIT(9)
#define BIT_AON_APB_WTLCP_SW_JTAG_ENA_LDSP                       BIT(8)
#define BIT_AON_APB_WTLCP_LDSP_EXTERNAL_WAIT                     BIT(1)
#define BIT_AON_APB_WTLCP_LDSP_BOOT                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WTLCP_TDSP_CTRL0
// Register Offset : 0x0250
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_TDSP_BOOT_VECTOR(x)                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WTLCP_TDSP_CTRL1
// Register Offset : 0x0254
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_STCK_TDSP                              BIT(13)
#define BIT_AON_APB_WTLCP_STMS_TDSP                              BIT(12)
#define BIT_AON_APB_WTLCP_STDO_TDSP                              BIT(11)
#define BIT_AON_APB_WTLCP_STDI_TDSP                              BIT(10)
#define BIT_AON_APB_WTLCP_STRTCK_TDSP                            BIT(9)
#define BIT_AON_APB_WTLCP_SW_JTAG_ENA_TDSP                       BIT(8)
#define BIT_AON_APB_WTLCP_TDSP_EXTERNAL_WAIT                     BIT(1)
#define BIT_AON_APB_WTLCP_TDSP_BOOT                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PCP_AON_EB
// Register Offset : 0x0280
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUBCP_SYST_RTC_EB                            BIT(11)
#define BIT_AON_APB_PUBCP_TMR_EB                                 BIT(10)
#define BIT_AON_APB_PUBCP_TMR_RTC_EB                             BIT(9)
#define BIT_AON_APB_PUBCP_SYST_EB                                BIT(8)
#define BIT_AON_APB_PUBCP_WDG_EB                                 BIT(7)
#define BIT_AON_APB_PUBCP_WDG_RTC_EB                             BIT(6)
#define BIT_AON_APB_PUBCP_ARCH_RTC_EB                            BIT(5)
#define BIT_AON_APB_PUBCP_EIC_EB                                 BIT(4)
#define BIT_AON_APB_PUBCP_EIC_RTCDV5_EB                          BIT(3)
#define BIT_AON_APB_PUBCP_EIC_RTC_EB                             BIT(2)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PCP_SOFT_RST
// Register Offset : 0x0284
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUBCP_CR5_CORE_SOFT_RST                      BIT(10)
#define BIT_AON_APB_PUBCP_CR5_DBG_SOFT_RST                       BIT(9)
#define BIT_AON_APB_PUBCP_CR5_ETM_SOFT_RST                       BIT(8)
#define BIT_AON_APB_PUBCP_CR5_MP_SOFT_RST                        BIT(7)
#define BIT_AON_APB_PUBCP_CR5_CS_DBG_SOFT_RST                    BIT(6)
#define BIT_AON_APB_PUBCP_TMR_SOFT_RST                           BIT(5)
#define BIT_AON_APB_PUBCP_SYST_SOFT_RST                          BIT(4)
#define BIT_AON_APB_PUBCP_WDG_SOFT_RST                           BIT(3)
#define BIT_AON_APB_PUBCP_EIC_SOFT_RST                           BIT(2)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PUBCP_CTRL
// Register Offset : 0x0288
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_ACCESS_PUBCP                             BIT(13)
#define BIT_AON_APB_PUBCP_CR5_STANDBYWFI_N                       BIT(12)
#define BIT_AON_APB_PUBCP_CR5_STANDBYWFE_N                       BIT(11)
#define BIT_AON_APB_PUBCP_CR5_CLKSTOPPED0_N                      BIT(10)
#define BIT_AON_APB_PUBCP_CR5_L2IDLE                             BIT(9)
#define BIT_AON_APB_PUBCP_CR5_VALIRQ0_N                          BIT(8)
#define BIT_AON_APB_PUBCP_CR5_VALFIQ0_N                          BIT(7)
#define BIT_AON_APB_PUBCP_CR5_STOP                               BIT(6)
#define BIT_AON_APB_PUBCP_CR5_CSYSACK_ATB                        BIT(5)
#define BIT_AON_APB_PUBCP_CR5_CACTIVE_ATB                        BIT(4)
#define BIT_AON_APB_PUBCP_CR5_CSSYNC_REQ                         BIT(3)
#define BIT_AON_APB_PUBCP_CR5_CSYSREQ_ATB                        BIT(2)
#define BIT_AON_APB_PUBCP_CR5_NODBGCLK                           BIT(1)
#define BIT_AON_APB_PUBCP_CR5_CFGEE                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_SYS_DBG_SEL
// Register Offset : 0x02B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_MDAR_DBG_MOD_SEL(x)                          (((x) & 0xFF) << 24)
#define BIT_AON_APB_MDAR_DBG_SIG_SEL(x)                          (((x) & 0xFF) << 16)
#define BIT_AON_APB_PUBCP_DBG_MOD_SEL(x)                         (((x) & 0xFF) << 8)
#define BIT_AON_APB_WTLCP_DBG_SIG_SEL(x)                         (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_MDAR_HSDL_CFG
// Register Offset : 0x02B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_MDAR_HSDL_CFG(x)                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_SYS_DBG_SEL2
// Register Offset : 0x02B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_DBG_MOD_SEL                              BIT(8)
#define BIT_AON_APB_AON_DBG_SIG_SEL(x)                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_SUBSYS_DBG_CFG
// Register Offset : 0x02BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_SUBSYS_DBG_SEL(x)                            (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AP_LPC_CTRL
// Register Offset : 0x02C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AP_FRC_STOP_ACK                              BIT(8)
#define BIT_AON_APB_AP_FRC_STOP_REQ                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WTLCP_LPC_CTRL
// Register Offset : 0x02C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_FRC_STOP_ACK                           BIT(8)
#define BIT_AON_APB_WTLCP_FRC_STOP_REQ                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PUBCP_LPC_CTRL
// Register Offset : 0x02C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUBCP_FRC_STOP_ACK                           BIT(8)
#define BIT_AON_APB_PUBCP_FRC_STOP_REQ                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_MDAR_SOFT_RST
// Register Offset : 0x02D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LVDSRF_CALI_SOFT_RST                         BIT(3)
#define BIT_AON_APB_RFTI2_LTH_SOFT_RST                           BIT(2)
#define BIT_AON_APB_RFTI1_LTH_SOFT_RST                           BIT(1)
#define BIT_AON_APB_RFTI_SBI_SOFT_RST                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_GLB_WCDMA_CTRL
// Register Offset : 0x0300
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_WCDMA_AUTO_GATE_EN                     BIT(3)
#define BIT_AON_APB_WTLCP_WCDMA_SOFT_GATE_DIS                    BIT(2)
#define BIT_AON_APB_PUBCP_WCDMA_AUTO_GATE_EN                     BIT(1)
#define BIT_AON_APB_PUBCP_WCDMA_SOFT_GATE_DIS                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PLL_CLKOUT_GATE
// Register Offset : 0x0400
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RTC4M0_EN                                    BIT(30)
#define BIT_AON_APB_LPLL_CLKOUT_EN                               BIT(29)
#define BIT_AON_APB_LPLL_DIV1_EN                                 BIT(28)
#define BIT_AON_APB_LPLL_DIV2_EN                                 BIT(27)
#define BIT_AON_APB_LPLL_DIV3_EN                                 BIT(26)
#define BIT_AON_APB_LPLL_DIV5_EN                                 BIT(25)
#define BIT_AON_APB_TWPLL_CLKOUT_EN                              BIT(24)
#define BIT_AON_APB_TWPLL_DIV1_EN                                BIT(23)
#define BIT_AON_APB_TWPLL_DIV2_EN                                BIT(22)
#define BIT_AON_APB_TWPLL_DIV3_EN                                BIT(21)
#define BIT_AON_APB_TWPLL_DIV5_EN                                BIT(20)
#define BIT_AON_APB_TWPLL_DIV7_EN                                BIT(19)
#define BIT_AON_APB_GPLL_CLKOUT_EN                               BIT(18)
#define BIT_AON_APB_DPLL_CLKOUT_EN                               BIT(17)
#define BIT_AON_APB_MPLL_CLKOUT_EN                               BIT(16)
#define BIT_AON_APB_LPLL_CLKOUT_AUTO_GATE_DIS                    BIT(13)
#define BIT_AON_APB_LPLL_DIV1_AUTO_GATE_DIS                      BIT(12)
#define BIT_AON_APB_LPLL_DIV2_AUTO_GATE_DIS                      BIT(11)
#define BIT_AON_APB_LPLL_DIV3_AUTO_GATE_DIS                      BIT(10)
#define BIT_AON_APB_LPLL_DIV5_AUTO_GATE_DIS                      BIT(9)
#define BIT_AON_APB_TWPLL_CLKOUT_AUTO_GATE_DIS                   BIT(8)
#define BIT_AON_APB_TWPLL_DIV1_AUTO_GATE_DIS                     BIT(7)
#define BIT_AON_APB_TWPLL_DIV2_AUTO_GATE_DIS                     BIT(6)
#define BIT_AON_APB_TWPLL_DIV3_AUTO_GATE_DIS                     BIT(5)
#define BIT_AON_APB_TWPLL_DIV5_AUTO_GATE_DIS                     BIT(4)
#define BIT_AON_APB_TWPLL_DIV7_AUTO_GATE_DIS                     BIT(3)
#define BIT_AON_APB_GPLL_CLKOUT_AUTO_GATE_DIS                    BIT(2)
#define BIT_AON_APB_DPLL_CLKOUT_AUTO_GATE_DIS                    BIT(1)
#define BIT_AON_APB_MPLL_CLKOUT_AUTO_GATE_DIS                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_HM_CFG_SEL
// Register Offset : 0x0404
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_MDAR_PMU_RPLL_CFG_SEL                        BIT(12)
#define BIT_AON_APB_LVDSRF_CFG_SEL                               BIT(11)
#define BIT_AON_APB_LVDSRF_PLL_CFG_SEL                           BIT(10)
#define BIT_AON_APB_RPLL_CFG_SEL                                 BIT(9)
#define BIT_AON_APB_LPLL_CFG_SEL                                 BIT(8)
#define BIT_AON_APB_TWPLL_CFG_SEL                                BIT(7)
#define BIT_AON_APB_GPLL_CFG_SEL                                 BIT(6)
#define BIT_AON_APB_DPLL_CFG_SEL                                 BIT(5)
#define BIT_AON_APB_MPLL_CFG_SEL                                 BIT(4)
#define BIT_AON_APB_RTC4M0_CFG_SEL                               BIT(3)
#define BIT_AON_APB_AAPC_CFG_SEL                                 BIT(2)
#define BIT_AON_APB_BB_BG_CFG_SEL                                BIT(1)
#define BIT_AON_APB_XTAL_SIN_CFG_SEL                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_HM_PWR_CTRL
// Register Offset : 0x0408
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CPPLL_PD                                     BIT(12)
#define BIT_AON_APB_LVDSRF_PD                                    BIT(11)
#define BIT_AON_APB_LVDSRF_PLL_PD                                BIT(10)
#define BIT_AON_APB_RPLL_PD                                      BIT(9)
#define BIT_AON_APB_LPLL_PD                                      BIT(8)
#define BIT_AON_APB_TWPLL_PD                                     BIT(7)
#define BIT_AON_APB_GPLL_PD                                      BIT(6)
#define BIT_AON_APB_DPLL_PD                                      BIT(5)
#define BIT_AON_APB_MPLL_PD                                      BIT(4)
#define BIT_AON_APB_AAPC_PD                                      BIT(3)
#define BIT_AON_APB_BB_BG_PD                                     BIT(2)
#define BIT_AON_APB_XTAL_32M_BUF_PD                              BIT(1)
#define BIT_AON_APB_XTAL_26M_BUF_PD                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_HM_RST_CTRL
// Register Offset : 0x040C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CPPLL_RST                                    BIT(12)
#define BIT_AON_APB_LVDSRF_RST                                   BIT(11)
#define BIT_AON_APB_LVDSRF_PLL_RST                               BIT(10)
#define BIT_AON_APB_RPLL_RST                                     BIT(9)
#define BIT_AON_APB_LPLL_RST                                     BIT(8)
#define BIT_AON_APB_TWPLL_RST                                    BIT(7)
#define BIT_AON_APB_GPLL_RST                                     BIT(6)
#define BIT_AON_APB_DPLL_RST                                     BIT(5)
#define BIT_AON_APB_MPLL_RST                                     BIT(4)
#define BIT_AON_APB_RTC4M0_RST                                   BIT(3)
#define BIT_AON_APB_BB_BG_RST                                    BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_M_AAPC_CFG
// Register Offset : 0x0420
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AAPC_G1(x)                                   (((x) & 0x3) << 24)
#define BIT_AON_APB_AAPC_G0(x)                                   (((x) & 0x3) << 22)
#define BIT_AON_APB_AAPC_SEL                                     BIT(21)
#define BIT_AON_APB_AAPC_BPRES                                   BIT(20)
#define BIT_AON_APB_APCOUT_SEL                                   BIT(15)
#define BIT_AON_APB_AAPC_LOW_V_CON                               BIT(14)
#define BIT_AON_APB_AAPC_D(x)                                    (((x) & 0x3FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_DAP_DJTAG_CTRL
// Register Offset : 0x0430
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_DAP_DJTAG_EN                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CGM_REG1
// Register Offset : 0x0440
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LTE_PCCSCC_RFTI_CLK_SW_CFG(x)                (((x) & 0xFF) << 24)
#define BIT_AON_APB_LPLL1_CLKOUT_SW                              BIT(23)
#define BIT_AON_APB_LPLL0_CLKOUT_SW                              BIT(22)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_TOP_LPC0
// Register Offset : 0x0500
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_TOP_LPC0_ACTIVE_SYNC_SEL                     BIT(18)
#define BIT_AON_APB_TOP_LPC0_LP_REQ                              BIT(17)
#define BIT_AON_APB_TOP_LPC0_EB                                  BIT(16)
#define BIT_AON_APB_TOP_LPC0_NUM(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_TOP_LPC1
// Register Offset : 0x0504
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_TOP_LPC1_ACTIVE_SYNC_SEL                     BIT(18)
#define BIT_AON_APB_TOP_LPC1_LP_REQ                              BIT(17)
#define BIT_AON_APB_TOP_LPC1_EB                                  BIT(16)
#define BIT_AON_APB_TOP_LPC1_NUM(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_TOP_LPC2
// Register Offset : 0x0508
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_TOP_LPC2_ACTIVE_SYNC_SEL                     BIT(18)
#define BIT_AON_APB_TOP_LPC2_LP_REQ                              BIT(17)
#define BIT_AON_APB_TOP_LPC2_EB                                  BIT(16)
#define BIT_AON_APB_TOP_LPC2_NUM(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_TOP_LPC3
// Register Offset : 0x050C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_TOP_LPC3_ACTIVE_SYNC_SEL                     BIT(18)
#define BIT_AON_APB_TOP_LPC3_LP_REQ                              BIT(17)
#define BIT_AON_APB_TOP_LPC3_EB                                  BIT(16)
#define BIT_AON_APB_TOP_LPC3_NUM(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_OVERHEAT_RST_CTRL
// Register Offset : 0x0510
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_OVERHEAT_RST_DDIE_EN                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AP_WPROT_EN1
// Register Offset : 0x3004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AP_AWADDR_WPROT_EN1(x)                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WTLCP_WPROT_EN1
// Register Offset : 0x3008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_AWADDR_WPROT_EN1(x)                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PUBCP_WPROT_EN1
// Register Offset : 0x300C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUBCP_AWADDR_WPROT_EN1(x)                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_IO_DLY_CTRL
// Register Offset : 0x3014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CLK_CCIR_DLY_SEL(x)                          (((x) & 0xF) << 8)
#define BIT_AON_APB_CLK_PUBCPDSP_DLY_SEL(x)                      (((x) & 0xF) << 4)
#define BIT_AON_APB_CLK_WTLCPDSP_DLY_SEL(x)                      (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AP_WPROT_EN0
// Register Offset : 0x3018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AP_AWADDR_WPROT_EN0(x)                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WTLCP_WPROT_EN0
// Register Offset : 0x3020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_WTLCP_AWADDR_WPROT_EN0(x)                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PUBCP_WPROT_EN0
// Register Offset : 0x3024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PUBCP_AWADDR_WPROT_EN0(x)                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PMU_RST_MONITOR
// Register Offset : 0x302C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PMU_RST_MONITOR(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_THM_RST_MONITOR
// Register Offset : 0x3030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_THM_RST_MONITOR(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AP_RST_MONITOR
// Register Offset : 0x3034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AP_RST_MONITOR(x)                            (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CA7_RST_MONITOR
// Register Offset : 0x3038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_CA7_RST_MONITOR(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_BOND_OPT0
// Register Offset : 0x303C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_BOND_OPTION0(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_BOND_OPT1
// Register Offset : 0x3040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_BOND_OPTION1(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RES_REG0
// Register Offset : 0x3044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RES_REG0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RES_REG1
// Register Offset : 0x3048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RES_REG1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_QOS_CFG
// Register Offset : 0x304C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_QOS_R_GPU(x)                                 (((x) & 0xF) << 12)
#define BIT_AON_APB_QOS_W_GPU(x)                                 (((x) & 0xF) << 8)
#define BIT_AON_APB_QOS_R_GSP(x)                                 (((x) & 0xF) << 4)
#define BIT_AON_APB_QOS_W_GSP(x)                                 (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_BB_LDO_CAL_START
// Register Offset : 0x3050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_BB_LDO_CAL_START                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_MTX_PROT_CFG
// Register Offset : 0x3058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_HPROT_DMAW(x)                                (((x) & 0xF) << 4)
#define BIT_AON_APB_HPROT_DMAR(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_LVDS_CFG
// Register Offset : 0x3060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_LVDSDIS_TXCLKDATA(x)                         (((x) & 0x7F) << 16)
#define BIT_AON_APB_LVDSDIS_TXCOM(x)                             (((x) & 0x3) << 12)
#define BIT_AON_APB_LVDSDIS_TXSLEW(x)                            (((x) & 0x3) << 10)
#define BIT_AON_APB_LVDSDIS_TXSW(x)                              (((x) & 0x3) << 8)
#define BIT_AON_APB_LVDSDIS_TXRERSER(x)                          (((x) & 0x1F) << 3)
#define BIT_AON_APB_LVDSDIS_PRE_EMP(x)                           (((x) & 0x3) << 1)
#define BIT_AON_APB_LVDSDIS_TXPD                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_PLL_LOCK_OUT_SEL
// Register Offset : 0x3064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_SLEEP_PLLLOCK_SEL                            BIT(7)
#define BIT_AON_APB_PLL_LOCK_SEL(x)                              (((x) & 0x7) << 4)
#define BIT_AON_APB_SLEEP_DBG_SEL(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RTC4M_RC_VAL
// Register Offset : 0x3068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RTC4M1_RC_SEL                                BIT(31)
#define BIT_AON_APB_RTC4M1_RC_VAL(x)                             (((x) & 0x1FF) << 16)
#define BIT_AON_APB_RTC4M0_RC_SEL                                BIT(15)
#define BIT_AON_APB_RTC4M0_RC_VAL(x)                             (((x) & 0x1FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_FUNCTST_CTRL_0
// Register Offset : 0x3070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_FUNCTST_CTRL_0(x)                            (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_FUNCTST_CTRL_1
// Register Offset : 0x3074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_FUNCTST_CTRL_1(x)                            (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_FUNCTST_CTRL_2
// Register Offset : 0x3078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_FUNCTST_CTRL_2(x)                            (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_WDG_RST_FLAG
// Register Offset : 0x3080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_PCP_WDG_RST_FLAG                             BIT(5)
#define BIT_AON_APB_WTLCP_LTE_WDG_RST_FLAG                       BIT(4)
#define BIT_AON_APB_WTLCP_TG_WDG_RST_FLAG                        BIT(3)
#define BIT_AON_APB_CA7_WDG_RST_FLAG                             BIT(1)
#define BIT_AON_APB_SEC_WDG_RST_FLAG                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_CA7_CFG
// Register Offset : 0x3084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_READ_ALLOC_MODE_SPRD(x)                      (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RES_REG2
// Register Offset : 0x3090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RES_REG2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RES_REG3
// Register Offset : 0x3094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RES_REG3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RES_REG4
// Register Offset : 0x3098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RES_REG4(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RES_REG5
// Register Offset : 0x309C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RES_REG5(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RES_REG6
// Register Offset : 0x30A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RES_REG6(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_RES_REG7
// Register Offset : 0x30A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_RES_REG7(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_AON_APB_RSV
// Register Offset : 0x30F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_AON_APB_RSV(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_APB_FUNCTION_DMA_BOOT_ADDR
// Register Offset : 0x3110
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_APB_FUNCTION_DMA_BOOT_ADDR(x)                    (((x) & 0xFFFFFFFF))


#endif // _AON_APB_REG_H

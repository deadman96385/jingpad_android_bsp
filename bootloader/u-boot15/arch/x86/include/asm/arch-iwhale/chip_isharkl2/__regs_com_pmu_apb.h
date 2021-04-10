/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _COM_PMU_APB_REG_H
#define _COM_PMU_APB_REG_H

#define CTL_BASE_COM_PMU_APB 0xE42C0000


#define REG_COM_PMU_APB_SYS_SOFT_RESET                   ( CTL_BASE_COM_PMU_APB + 0x0000 )
#define REG_COM_PMU_APB_USB_PMU_CTRL                     ( CTL_BASE_COM_PMU_APB + 0x0004 )
#define REG_COM_PMU_APB_DDR_SLEEP_CTRL                   ( CTL_BASE_COM_PMU_APB + 0x0008 )
#define REG_COM_PMU_APB_MEM_SLP_CFG0                     ( CTL_BASE_COM_PMU_APB + 0x000C )
#define REG_COM_PMU_APB_MEM_SD_CFG0                      ( CTL_BASE_COM_PMU_APB + 0x0010 )
#define REG_COM_PMU_APB_MEM_AUTO_SLP_EN                  ( CTL_BASE_COM_PMU_APB + 0x0014 )
#define REG_COM_PMU_APB_MEM_AUTO_SD_EN                   ( CTL_BASE_COM_PMU_APB + 0x0018 )
#define REG_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_CTRL          ( CTL_BASE_COM_PMU_APB + 0x001C )
#define REG_COM_PMU_APB_PAD_OUT_XTL_EB_CTRL              ( CTL_BASE_COM_PMU_APB + 0x0020 )
#define REG_COM_PMU_APB_PAD_OUT_XTL_EB1_CTRL             ( CTL_BASE_COM_PMU_APB + 0x0024 )
#define REG_COM_PMU_APB_PAD_OUT_XTL_EB2_CTRL             ( CTL_BASE_COM_PMU_APB + 0x0028 )
#define REG_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_CTRL          ( CTL_BASE_COM_PMU_APB + 0x002C )
#define REG_COM_PMU_APB_PAD_OUT_DCDCCPU_EB_CTRL          ( CTL_BASE_COM_PMU_APB + 0x0030 )
#define REG_COM_PMU_APB_PAD_CFG_EN_ANLGMODE              ( CTL_BASE_COM_PMU_APB + 0x0034 )
#define REG_COM_PMU_APB_DDR_PHY_DATA_RET_CTRL            ( CTL_BASE_COM_PMU_APB + 0x0048 )
#define REG_COM_PMU_APB_EXT_XTL_COMB_EN                  ( CTL_BASE_COM_PMU_APB + 0x004C )
#define REG_COM_PMU_APB_LVDS_RF_PLL_REF_SEL              ( CTL_BASE_COM_PMU_APB + 0x0050 )
#define REG_COM_PMU_APB_SYS_FRC_SLEEP_REQ                ( CTL_BASE_COM_PMU_APB + 0x0054 )
#define REG_COM_PMU_APB_SYS_FRC_SLEEP_ACK                ( CTL_BASE_COM_PMU_APB + 0x0058 )
#define REG_COM_PMU_APB_EFUSE_START_CFG                  ( CTL_BASE_COM_PMU_APB + 0x005C )
#define REG_COM_PMU_APB_FRC_SLEEP_ACK_BYP                ( CTL_BASE_COM_PMU_APB + 0x0060 )
#define REG_COM_PMU_APB_FRC_SLEEP_REQ_CNT                ( CTL_BASE_COM_PMU_APB + 0x0064 )
#define REG_COM_PMU_APB_LDO_PWR_CTRL0                    ( CTL_BASE_COM_PMU_APB + 0x0068 )
#define REG_COM_PMU_APB_LDO_PWR_CTRL1                    ( CTL_BASE_COM_PMU_APB + 0x006C )
#define REG_COM_PMU_APB_AON_PUB_FRC_SLP_CTRL             ( CTL_BASE_COM_PMU_APB + 0x0070 )
#define REG_COM_PMU_APB_PD_EXT_DOMAIN_ACK                ( CTL_BASE_COM_PMU_APB + 0x0074 )
#define REG_COM_PMU_APB_UFS_LP_PWR_GATE_REQ_BYP          ( CTL_BASE_COM_PMU_APB + 0x0078 )
#define REG_COM_PMU_APB_USB2PHY_PS_CTRL                  ( CTL_BASE_COM_PMU_APB + 0x007C )
#define REG_COM_PMU_APB_USB2PHY_PS_REG_CTRL              ( CTL_BASE_COM_PMU_APB + 0x0080 )
#define REG_COM_PMU_APB_USB3PHY_DISCONNECT_CTRL          ( CTL_BASE_COM_PMU_APB + 0x0084 )
#define REG_COM_PMU_APB_USB3PHY_DISCONNECT_REG_CTRL      ( CTL_BASE_COM_PMU_APB + 0x0088 )
#define REG_COM_PMU_APB_DDR0_CHN_SLEEP_CTRL              ( CTL_BASE_COM_PMU_APB + 0x008C )
#define REG_COM_PMU_APB_DDR1_CHN_SLEEP_CTRL              ( CTL_BASE_COM_PMU_APB + 0x0090 )
#define REG_COM_PMU_APB_AON_RAM_SLEEP_CTRL               ( CTL_BASE_COM_PMU_APB + 0x0094 )
#define REG_COM_PMU_APB_PUB_MEM_RESET_RET                ( CTL_BASE_COM_PMU_APB + 0x0098 )
#define REG_COM_PMU_APB_BIA_VDD_L2_SRAM_CTRL             ( CTL_BASE_COM_PMU_APB + 0x009C )
#define REG_COM_PMU_APB_EFUSE_LDO_CTRL                   ( CTL_BASE_COM_PMU_APB + 0x00A0 )
#define REG_COM_PMU_APB_EFUSE_LDO_DBG                    ( CTL_BASE_COM_PMU_APB + 0x00A4 )
#define REG_COM_PMU_APB_MPLL0_LP_CTRL0                   ( CTL_BASE_COM_PMU_APB + 0x00B0 )
#define REG_COM_PMU_APB_MPLL0_LP_CTRL1                   ( CTL_BASE_COM_PMU_APB + 0x00B4 )
#define REG_COM_PMU_APB_MPLL1_LP_CTRL0                   ( CTL_BASE_COM_PMU_APB + 0x00B8 )
#define REG_COM_PMU_APB_MPLL1_LP_CTRL1                   ( CTL_BASE_COM_PMU_APB + 0x00BC )
#define REG_COM_PMU_APB_MPLL2_LP_CTRL0                   ( CTL_BASE_COM_PMU_APB + 0x00C0 )
#define REG_COM_PMU_APB_MPLL2_LP_CTRL1                   ( CTL_BASE_COM_PMU_APB + 0x00C4 )
#define REG_COM_PMU_APB_INT_REQ_PWR_CHG_CLR              ( CTL_BASE_COM_PMU_APB + 0x00C8 )
#define REG_COM_PMU_APB_MBOX_NOPWR_DOWN_BYP              ( CTL_BASE_COM_PMU_APB + 0x00CC )
#define REG_COM_PMU_APB_FENCING_LOCK_BYP                 ( CTL_BASE_COM_PMU_APB + 0x00D0 )
#define REG_COM_PMU_APB_FENCING0_CTRL_STATE              ( CTL_BASE_COM_PMU_APB + 0x00D4 )
#define REG_COM_PMU_APB_FENCING1_CTRL_STATE              ( CTL_BASE_COM_PMU_APB + 0x00D8 )
#define REG_COM_PMU_APB_EFUSE_LDO_DLY0                   ( CTL_BASE_COM_PMU_APB + 0x00DC )
#define REG_COM_PMU_APB_EFUSE_LDO_DLY1                   ( CTL_BASE_COM_PMU_APB + 0x00E0 )
#define REG_COM_PMU_APB_EFUSE_LDO_DLY2                   ( CTL_BASE_COM_PMU_APB + 0x00E4 )
#define REG_COM_PMU_APB_EFUSE_LDO_DLY3                   ( CTL_BASE_COM_PMU_APB + 0x00E8 )
#define REG_COM_PMU_APB_EFUSE_LDO_DLY4                   ( CTL_BASE_COM_PMU_APB + 0x00EC )
#define REG_COM_PMU_APB_EFUSE_LDO_DLY5                   ( CTL_BASE_COM_PMU_APB + 0x00F0 )
#define REG_COM_PMU_APB_EFUSE_LDO_DLY6                   ( CTL_BASE_COM_PMU_APB + 0x00F4 )
#define REG_COM_PMU_APB_EFUSE_LDO_DLY7                   ( CTL_BASE_COM_PMU_APB + 0x00F8 )
#define REG_COM_PMU_APB_AXI_LPC_CTRL_DISABLE             ( CTL_BASE_COM_PMU_APB + 0x00FC )
#define REG_COM_PMU_APB_AUD_DMA_BUSY_SLP_EN              ( CTL_BASE_COM_PMU_APB + 0x0100 )
#define REG_COM_PMU_APB_AUD_SYS_SLP_EN                   ( CTL_BASE_COM_PMU_APB + 0x0104 )
#define REG_COM_PMU_APB_DDR0_LP_MASK                     ( CTL_BASE_COM_PMU_APB + 0x0108 )
#define REG_COM_PMU_APB_DSPLL_LP_CTRL0                   ( CTL_BASE_COM_PMU_APB + 0x010C )
#define REG_COM_PMU_APB_DSPLL_LP_CTRL1                   ( CTL_BASE_COM_PMU_APB + 0x0110 )
#define REG_COM_PMU_APB_GPU_CORE_FORCE                   ( CTL_BASE_COM_PMU_APB + 0x0114 )
#define REG_COM_PMU_APB_INT_REQ_PWR_ON_CFG               ( CTL_BASE_COM_PMU_APB + 0x0118 )
#define REG_COM_PMU_APB_SMART_LSLP_ENA                   ( CTL_BASE_COM_PMU_APB + 0x011C )
#define REG_COM_PMU_APB_FENCING_LOCK_WAIT_NUM0           ( CTL_BASE_COM_PMU_APB + 0x0200 )
#define REG_COM_PMU_APB_FENCING_LOCK_WAIT_NUM1           ( CTL_BASE_COM_PMU_APB + 0x0204 )
#define REG_COM_PMU_APB_FENCING_LOCK_WAIT_NUM2           ( CTL_BASE_COM_PMU_APB + 0x0208 )
#define REG_COM_PMU_APB_SP_PUB_ACCESS_EN                 ( CTL_BASE_COM_PMU_APB + 0x020C )
#define REG_COM_PMU_APB_DDR_SLEEP_CNT                    ( CTL_BASE_COM_PMU_APB + 0x0210 )
#define REG_COM_PMU_APB_DDR_SLEEP_CNT_CFG                ( CTL_BASE_COM_PMU_APB + 0x0214 )
#define REG_COM_PMU_APB_PMU_ENHANCE_EN                   ( CTL_BASE_COM_PMU_APB + 0x0218 )
#define REG_COM_PMU_APB_PLL_STATUS_MASK                  ( CTL_BASE_COM_PMU_APB + 0x021C )
#define REG_COM_PMU_APB_PMU_DEBUG_CFG                    ( CTL_BASE_COM_PMU_APB + 0x0220 )
#define REG_COM_PMU_APB_PMU_DEBUG_BUS                    ( CTL_BASE_COM_PMU_APB + 0x0224 )

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_SYS_SOFT_RESET
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_BIA_CPU_SRST                                               BIT(22)
#define BIT_COM_PMU_APB_BIA_TAP_SRST                                               BIT(21)
#define BIT_COM_PMU_APB_PUBCP_CR5_SRST                                             BIT(20)
#define BIT_COM_PMU_APB_AGCP_DSP_SYS_SRST                                          BIT(19)
#define BIT_COM_PMU_APB_AGCP_DSP_SRST                                              BIT(18)
#define BIT_COM_PMU_APB_WTLCP_LDSP_SRST                                            BIT(17)
#define BIT_COM_PMU_APB_WTLCP_TGDSP_SRST                                           BIT(16)
#define BIT_COM_PMU_APB_PUBCP_CR5_CORE_SRST                                        BIT(15)
#define BIT_COM_PMU_APB_WTLCP_DSP_SYS_SRST                                         BIT(14)
#define BIT_COM_PMU_APB_WCDMA_AON_SRST                                             BIT(13)
#define BIT_COM_PMU_APB_AGCP_AON_SRST                                              BIT(12)
#define BIT_COM_PMU_APB_AGCP_SYS_SRST                                              BIT(11)
#define BIT_COM_PMU_APB_WTLCP_SYS_SRST                                             BIT(10)
#define BIT_COM_PMU_APB_WTL_AON_SRST                                               BIT(9)
#define BIT_COM_PMU_APB_CM4_SYS_SRST                                               BIT(8)
#define BIT_COM_PMU_APB_PUB1_SYS_SRST                                              BIT(7)
#define BIT_COM_PMU_APB_PUB0_SYS_SRST                                              BIT(6)
#define BIT_COM_PMU_APB_AP_SYS_SRST                                                BIT(5)
#define BIT_COM_PMU_APB_GPU_TOP_SRST                                               BIT(4)
#define BIT_COM_PMU_APB_CAM_SYS_SRST                                               BIT(3)
#define BIT_COM_PMU_APB_VSP_SYS_SRST                                               BIT(2)
#define BIT_COM_PMU_APB_PUBCP_SYS_SRST                                             BIT(1)
#define BIT_COM_PMU_APB_CM4_CORE_SRST                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_USB_PMU_CTRL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_USB_PMU_ACK_BYP                                            BIT(4)
#define BIT_COM_PMU_APB_CURRENT_POWER_STATE_U3PMU(x)                               (((x) & 0x3) << 2)
#define BIT_COM_PMU_APB_PM_POWER_STATE_REQUEST(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DDR_SLEEP_CTRL
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DDR0_CFG_AUTO_GATE_EN                                      BIT(14)
#define BIT_COM_PMU_APB_DDR1_PHY_SRST                                              BIT(13)
#define BIT_COM_PMU_APB_DDR1_AHB_SRST                                              BIT(12)
#define BIT_COM_PMU_APB_DDR1_PHY_AUTO_GATE_EN                                      BIT(11)
#define BIT_COM_PMU_APB_DDR1_UMCTL_SRST                                            BIT(10)
#define BIT_COM_PMU_APB_DDR1_UMCTL_AUTO_GATE_EN                                    BIT(9)
#define BIT_COM_PMU_APB_DDR1_PHY_EB                                                BIT(8)
#define BIT_COM_PMU_APB_DDR1_UMCTL_EB                                              BIT(7)
#define BIT_COM_PMU_APB_DDR0_PHY_SRST                                              BIT(6)
#define BIT_COM_PMU_APB_DDR0_AHB_SRST                                              BIT(5)
#define BIT_COM_PMU_APB_DDR0_PHY_AUTO_GATE_EN                                      BIT(4)
#define BIT_COM_PMU_APB_DDR0_UMCTL_SRST                                            BIT(3)
#define BIT_COM_PMU_APB_DDR0_UMCTL_AUTO_GATE_EN                                    BIT(2)
#define BIT_COM_PMU_APB_DDR0_PHY_EB                                                BIT(1)
#define BIT_COM_PMU_APB_DDR0_UMCTL_EB                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MEM_SLP_CFG0
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MEM_SLP_CFG0(x)                                            (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MEM_SD_CFG0
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MEM_SD_CFG0(x)                                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MEM_AUTO_SLP_EN
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MEM_AUTO_SLP_EN(x)                                         (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MEM_AUTO_SD_EN
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MEM_AUTO_SD_EN(x)                                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_CTRL
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_CAM_EB_MASK                             BIT(10)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_POL_SEL                                 BIT(9)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_PLL_PD_MASK                             BIT(8)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_EXT_XTL_PD_MASK                         BIT(7)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_PUB1_DEEP_SLEEP_MASK                    BIT(6)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_PUB0_DEEP_SLEEP_MASK                    BIT(5)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_CM4_DEEP_SLEEP_MASK                     BIT(4)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_AUD_DEEP_SLEEP_MASK                     BIT(3)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_WTLCP_DEEP_SLEEP_MASK                   BIT(2)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_PUBCP_DEEP_SLEEP_MASK                   BIT(1)
#define BIT_COM_PMU_APB_PAD_OUT_CHIP_SLEEP_AP_DEEP_SLEEP_MASK                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PAD_OUT_XTL_EB_CTRL
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_CAM_EB_MASK                                 BIT(10)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_POL_SEL                                     BIT(9)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_PLL_PD_MASK                                 BIT(8)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_EXT_XTL_PD_MASK                             BIT(7)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_PUB1_DEEP_SLEEP_MASK                        BIT(6)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_PUB0_DEEP_SLEEP_MASK                        BIT(5)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_CM4_DEEP_SLEEP_MASK                         BIT(4)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_AUD_DEEP_SLEEP_MASK                         BIT(3)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_WTLCP_DEEP_SLEEP_MASK                       BIT(2)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_PUBCP_DEEP_SLEEP_MASK                       BIT(1)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB_AP_DEEP_SLEEP_MASK                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PAD_OUT_XTL_EB1_CTRL
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_CAM_EB_MASK                                BIT(10)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_POL_SEL                                    BIT(9)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_PLL_PD_MASK                                BIT(8)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_EXT_XTL_PD_MASK                            BIT(7)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_PUB1_DEEP_SLEEP_MASK                       BIT(6)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_PUB0_DEEP_SLEEP_MASK                       BIT(5)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_CM4_DEEP_SLEEP_MASK                        BIT(4)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_AUD_DEEP_SLEEP_MASK                        BIT(3)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_WTLCP_DEEP_SLEEP_MASK                      BIT(2)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_PUBCP_DEEP_SLEEP_MASK                      BIT(1)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB1_AP_DEEP_SLEEP_MASK                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PAD_OUT_XTL_EB2_CTRL
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_CAM_EB_MASK                                BIT(10)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_POL_SEL                                    BIT(9)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_PLL_PD_MASK                                BIT(8)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_EXT_XTL_PD_MASK                            BIT(7)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_PUB1_DEEP_SLEEP_MASK                       BIT(6)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_PUB0_DEEP_SLEEP_MASK                       BIT(5)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_CM4_DEEP_SLEEP_MASK                        BIT(4)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_AUD_DEEP_SLEEP_MASK                        BIT(3)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_WTLCP_DEEP_SLEEP_MASK                      BIT(2)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_PUBCP_DEEP_SLEEP_MASK                      BIT(1)
#define BIT_COM_PMU_APB_PAD_OUT_XTL_EB2_AP_DEEP_SLEEP_MASK                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_CTRL
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_CAM_EB_MASK                             BIT(10)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_POL_SEL                                 BIT(9)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_PLL_PD_MASK                             BIT(8)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_EXT_XTL_PD_MASK                         BIT(7)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_PUB1_DEEP_SLEEP_MASK                    BIT(6)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_PUB0_DEEP_SLEEP_MASK                    BIT(5)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_CM4_DEEP_SLEEP_MASK                     BIT(4)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_AUD_DEEP_SLEEP_MASK                     BIT(3)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_WTLCP_DEEP_SLEEP_MASK                   BIT(2)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_PUBCP_DEEP_SLEEP_MASK                   BIT(1)
#define BIT_COM_PMU_APB_DCXO_LC_DEEP_SLEEP_AP_DEEP_SLEEP_MASK                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PAD_OUT_DCDCCPU_EB_CTRL
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PAD_OUT_DCDCCPU1_FRC_ON                                    BIT(3)
#define BIT_COM_PMU_APB_PAD_OUT_DCDCCPU1_EB_POL_SEL                                BIT(2)
#define BIT_COM_PMU_APB_PAD_OUT_DCDCCPU0_FRC_ON                                    BIT(1)
#define BIT_COM_PMU_APB_PAD_OUT_DCDCCPU0_EB_POL_SEL                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PAD_CFG_EN_ANLGMODE
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PAD_CFG_EN_ANLGMODE                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DDR_PHY_DATA_RET_CTRL
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DDR1_PHY_DATA_FRC_RET                                      BIT(3)
#define BIT_COM_PMU_APB_DDR1_PHY_DATA_AUTO_RET_EN                                  BIT(2)
#define BIT_COM_PMU_APB_DDR0_PHY_DATA_FRC_RET                                      BIT(1)
#define BIT_COM_PMU_APB_DDR0_PHY_DATA_AUTO_RET_EN                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EXT_XTL_COMB_EN
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EXT_XTL3_COMB_EN                                           BIT(3)
#define BIT_COM_PMU_APB_EXT_XTL2_COMB_EN                                           BIT(2)
#define BIT_COM_PMU_APB_EXT_XTL1_COMB_EN                                           BIT(1)
#define BIT_COM_PMU_APB_EXT_XTL0_COMB_EN                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_LVDS_RF_PLL_REF_SEL
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_LVDS_RF_PLL0_REF_SEL(x)                                    (((x) & 0x7) << 3)
#define BIT_COM_PMU_APB_LVDS_RF_PLL1_REF_SEL(x)                                    (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_SYS_FRC_SLEEP_REQ
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_GPU_TOP_FRC_SLEEP_REQ                                      BIT(7)
#define BIT_COM_PMU_APB_CAM_SYS_FRC_SLEEP_REQ                                      BIT(6)
#define BIT_COM_PMU_APB_VSP_SYS_FRC_SLEEP_REQ                                      BIT(5)
#define BIT_COM_PMU_APB_BIA_FRC_SLEEP_REQ                                          BIT(4)
#define BIT_COM_PMU_APB_AP_SYS_FRC_SLEEP_REQ                                       BIT(3)
#define BIT_COM_PMU_APB_WTLCP_SYS_FRC_SLEEP_REQ                                    BIT(2)
#define BIT_COM_PMU_APB_AGCP_SYS_FRC_SLEEP_REQ                                     BIT(1)
#define BIT_COM_PMU_APB_PUBCP_SYS_FRC_SLEEP_REQ                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_SYS_FRC_SLEEP_ACK
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_GPU_TOP_FRC_SLEEP_ACK                                      BIT(10)
#define BIT_COM_PMU_APB_CAM_SYS_FRC_SLEEP_ACK                                      BIT(8)
#define BIT_COM_PMU_APB_VSP_SYS_FRC_SLEEP_ACK                                      BIT(6)
#define BIT_COM_PMU_APB_BIA_FRC_SLEEP_ACK                                          BIT(5)
#define BIT_COM_PMU_APB_AP_SYS_FRC_SLEEP_ACK                                       BIT(4)
#define BIT_COM_PMU_APB_WTLCP_SYS_FRC_SLEEP_ACK                                    BIT(3)
#define BIT_COM_PMU_APB_AGCP_SYS_FRC_SLEEP_ACK                                     BIT(1)
#define BIT_COM_PMU_APB_PUBCP_SYS_FRC_SLEEP_ACK                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_START_CFG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_RESTART                                              BIT(8)
#define BIT_COM_PMU_APB_EFUSE_START_CNT(x)                                         (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_FRC_SLEEP_ACK_BYP
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_GPU_EB_LP_ACK_BYP                                          BIT(10)
#define BIT_COM_PMU_APB_VSP_EB_LP_ACK_BYP                                          BIT(9)
#define BIT_COM_PMU_APB_CAM_EB_LP_ACK_BYP                                          BIT(8)
#define BIT_COM_PMU_APB_GPU_TOP_FRC_SLEEP_ACK_BYP                                  BIT(7)
#define BIT_COM_PMU_APB_CAM_SYS_FRC_SLEEP_ACK_BYP                                  BIT(6)
#define BIT_COM_PMU_APB_VSP_SYS_FRC_SLEEP_ACK_BYP                                  BIT(5)
#define BIT_COM_PMU_APB_BIA_FRC_SLEEP_ACK_BYP                                      BIT(4)
#define BIT_COM_PMU_APB_AP_SYS_FRC_SLEEP_ACK_BYP                                   BIT(3)
#define BIT_COM_PMU_APB_WTLCP_SYS_FRC_SLEEP_ACK_BYP                                BIT(2)
#define BIT_COM_PMU_APB_AUD_SYS_FRC_SLEEP_ACK_BYP                                  BIT(1)
#define BIT_COM_PMU_APB_PUBCP_SYS_FRC_SLEEP_ACK_BYP                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_FRC_SLEEP_REQ_CNT
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_FRC_SLEEP_REQ_CNT(x)                                       (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_LDO_PWR_CTRL0
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_LDO1P2PLL_SLP_PD_EN                                        BIT(14)
#define BIT_COM_PMU_APB_LDO1P2PLL_FRC_ON                                           BIT(13)
#define BIT_COM_PMU_APB_LDO1P2PLL_FRC_PD                                           BIT(12)
#define BIT_COM_PMU_APB_LDO1P2_CP_PD_EN                                            BIT(6)
#define BIT_COM_PMU_APB_LDO1P2_SLP_PD_EN                                           BIT(5)
#define BIT_COM_PMU_APB_LDO1P2_FRC_ON                                              BIT(4)
#define BIT_COM_PMU_APB_LDO1P2_FRC_PD                                              BIT(3)
#define BIT_COM_PMU_APB_LDO0P84_SLP_PD_EN                                          BIT(2)
#define BIT_COM_PMU_APB_LDO0P84_FRC_ON                                             BIT(1)
#define BIT_COM_PMU_APB_LDO0P84_FRC_PD                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_LDO_PWR_CTRL1
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_LDO4_RAISE_PRESET_V(x)                                     (((x) & 0x1F) << 15)
#define BIT_COM_PMU_APB_LDO4_NORMAL_PRESET_V(x)                                    (((x) & 0x1F) << 10)
#define BIT_COM_PMU_APB_LDO3_RAISE_PRESET_V(x)                                     (((x) & 0x1F) << 5)
#define BIT_COM_PMU_APB_LDO3_NORMAL_PRESET_V(x)                                    (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_AON_PUB_FRC_SLP_CTRL
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_BIA_S3_FRC_DSLP                                            BIT(22)
#define BIT_COM_PMU_APB_CAM_SUB_PUB0_FRC_LSLP                                      BIT(21)
#define BIT_COM_PMU_APB_CAM_SUB_PUB0_FRC_DSLP                                      BIT(20)
#define BIT_COM_PMU_APB_BIA_S3_PUB1_FRC_LSLP                                       BIT(19)
#define BIT_COM_PMU_APB_BIA_S3_PUB0_FRC_LSLP                                       BIT(18)
#define BIT_COM_PMU_APB_BIA_S3_PUB1_FRC_DSLP                                       BIT(17)
#define BIT_COM_PMU_APB_BIA_S3_PUB0_FRC_DSLP                                       BIT(16)
#define BIT_COM_PMU_APB_BIA_PUB1_FRC_DSLP                                          BIT(15)
#define BIT_COM_PMU_APB_VSP_PUB1_FRC_DSLP                                          BIT(14)
#define BIT_COM_PMU_APB_GPU_PUB1_FRC_DSLP                                          BIT(13)
#define BIT_COM_PMU_APB_CAM_PUB1_FRC_DSLP                                          BIT(12)
#define BIT_COM_PMU_APB_BIA_PUB1_FRC_LSLP                                          BIT(11)
#define BIT_COM_PMU_APB_VSP_PUB1_FRC_LSLP                                          BIT(10)
#define BIT_COM_PMU_APB_GPU_PUB1_FRC_LSLP                                          BIT(9)
#define BIT_COM_PMU_APB_CAM_PUB1_FRC_LSLP                                          BIT(8)
#define BIT_COM_PMU_APB_BIA_PUB0_FRC_DSLP                                          BIT(7)
#define BIT_COM_PMU_APB_VSP_PUB0_FRC_DSLP                                          BIT(6)
#define BIT_COM_PMU_APB_GPU_PUB0_FRC_DSLP                                          BIT(5)
#define BIT_COM_PMU_APB_CAM_PUB0_FRC_DSLP                                          BIT(4)
#define BIT_COM_PMU_APB_BIA_PUB0_FRC_LSLP                                          BIT(3)
#define BIT_COM_PMU_APB_VSP_PUB0_FRC_LSLP                                          BIT(2)
#define BIT_COM_PMU_APB_GPU_PUB0_FRC_LSLP                                          BIT(1)
#define BIT_COM_PMU_APB_CAM_PUB0_FRC_LSLP                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PD_EXT_DOMAIN_ACK
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PD_RAW_TOP_ACK_D                                           BIT(19)
#define BIT_COM_PMU_APB_PD_RAW_TOP_ACK_M                                           BIT(18)
#define BIT_COM_PMU_APB_PD_ISP_LITE_ACK_D                                          BIT(17)
#define BIT_COM_PMU_APB_PD_ISP_LITE_ACK_M                                          BIT(16)
#define BIT_COM_PMU_APB_PD_ISP_SUB_ACK_D                                           BIT(15)
#define BIT_COM_PMU_APB_PD_ISP_SUB_ACK_M                                           BIT(14)
#define BIT_COM_PMU_APB_PD_ISP_MAIN_ACK_D                                          BIT(13)
#define BIT_COM_PMU_APB_PD_ISP_MAIN_ACK_M                                          BIT(12)
#define BIT_COM_PMU_APB_PD_PUB1_PHY_ACK_D                                          BIT(11)
#define BIT_COM_PMU_APB_PD_PUB1_PHY_ACK_M                                          BIT(10)
#define BIT_COM_PMU_APB_PD_PUB0_PHY_ACK_D                                          BIT(9)
#define BIT_COM_PMU_APB_PD_PUB0_PHY_ACK_M                                          BIT(8)
#define BIT_COM_PMU_APB_PD_GPU_MERCER1_ACK_D                                       BIT(7)
#define BIT_COM_PMU_APB_PD_GPU_MERCER1_ACK_M                                       BIT(6)
#define BIT_COM_PMU_APB_PD_GPU_MERCER0_ACK_D                                       BIT(5)
#define BIT_COM_PMU_APB_PD_GPU_MERCER0_ACK_M                                       BIT(4)
#define BIT_COM_PMU_APB_PD_GPU_BLACKP_ACK_D                                        BIT(3)
#define BIT_COM_PMU_APB_PD_GPU_BLACKP_ACK_M                                        BIT(2)
#define BIT_COM_PMU_APB_PD_GPU_TEAGUE_ACK_D                                        BIT(1)
#define BIT_COM_PMU_APB_PD_GPU_TEAGUE_ACK_M                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_UFS_LP_PWR_GATE_REQ_BYP
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_UFS_LP_PWR_GATE_REQ_BYP                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_USB2PHY_PS_CTRL
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_USB2PHY_PS_STATE(x)                                        (((x) & 0x1F) << 22)
#define BIT_COM_PMU_APB_OUSB2PHY_PWRGATE_CLKREQ_BYP                                BIT(21)
#define BIT_COM_PMU_APB_OUSB2PHY_SOC_PLLRUNNING_BYP                                BIT(20)
#define BIT_COM_PMU_APB_OUSB2PHY_SOC_COLDBOOTED_BYP                                BIT(19)
#define BIT_COM_PMU_APB_OUSB2PHY_PWRACK_PWRGATE_BYP                                BIT(16)
#define BIT_COM_PMU_APB_USB2PHY_PS_GAP_DLY(x)                                      (((x) & 0xFF) << 8)
#define BIT_COM_PMU_APB_USB2PHY_PWR_ON                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_USB2PHY_PS_REG_CTRL
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_OUSB2PHY_PWRGATE_CLKREQ                                    BIT(11)
#define BIT_COM_PMU_APB_OUSB2PHY_SOC_PLLRUNNING                                    BIT(10)
#define BIT_COM_PMU_APB_OUSB2PHY_SOC_COLDBOOTED                                    BIT(9)
#define BIT_COM_PMU_APB_OUSB2PHY_PWRACK_PWRGATE                                    BIT(8)
#define BIT_COM_PMU_APB_IUSB2PHY_APB_RSTB_REG                                      BIT(7)
#define BIT_COM_PMU_APB_IUSB2PHY_SOC_PHY_SUS_RSTB_REG                              BIT(6)
#define BIT_COM_PMU_APB_IUSB2PHY_PHY_FWENB_REG                                     BIT(5)
#define BIT_COM_PMU_APB_IUSB2PHY_PWRGATE_ACK_REG                                   BIT(4)
#define BIT_COM_PMU_APB_IUSB2PHY_PWRGATE_EN_REG                                    BIT(3)
#define BIT_COM_PMU_APB_IUSB2PHY_PWRGATEVNRFW_ENB_REG                              BIT(2)
#define BIT_COM_PMU_APB_IUSB2PHY_BRDPWRGOOD_H_REG                                  BIT(1)
#define BIT_COM_PMU_APB_USB2PHY_PS_CTRL_REG_BYP                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_USB3PHY_DISCONNECT_CTRL
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_USB3PHY_DISCONNECT_STATE(x)                                (((x) & 0x1F) << 25)
#define BIT_COM_PMU_APB_OCTL_PMA_DISCONNECT_STATUS_A_BYP                           BIT(24)
#define BIT_COM_PMU_APB_USB3PHY_DC_GAP_DLY(x)                                      (((x) & 0xFF) << 16)
#define BIT_COM_PMU_APB_USB3PHY_PS_GAP_DLY(x)                                      (((x) & 0xFF) << 8)
#define BIT_COM_PMU_APB_USB3PHY_DISCONNECT                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_USB3PHY_DISCONNECT_REG_CTRL
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_OCTL_PMA_DISCONNECT_STATUS_A                               BIT(5)
#define BIT_COM_PMU_APB_IPD_PMA_KEEPALIVE_B_NT_REG                                 BIT(4)
#define BIT_COM_PMU_APB_ICTL_PMA_KEEPALIVE_DISABLE_A_REG                           BIT(3)
#define BIT_COM_PMU_APB_ICTL_PMA_DISCONNECT_A_REG                                  BIT(2)
#define BIT_COM_PMU_APB_IRST_PIPE_RST_LX_B_A_REG                                   BIT(1)
#define BIT_COM_PMU_APB_USB3PHY_DISCONNECT_CTRL_REG_BYP                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DDR0_CHN_SLEEP_CTRL
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DDR0_CHN5_CGM_SEL                                          BIT(6)
#define BIT_COM_PMU_APB_DDR0_CHN4_CGM_SEL                                          BIT(5)
#define BIT_COM_PMU_APB_DDR0_CHN3_CGM_SEL                                          BIT(4)
#define BIT_COM_PMU_APB_DDR0_CHN2_CGM_SEL                                          BIT(3)
#define BIT_COM_PMU_APB_DDR0_CHN1_CGM_SEL                                          BIT(2)
#define BIT_COM_PMU_APB_DDR0_CHN0_CGM_SEL                                          BIT(1)
#define BIT_COM_PMU_APB_DDR0_CTRL_CGM_EN                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DDR1_CHN_SLEEP_CTRL
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DDR1_CHN3_CGM_SEL                                          BIT(4)
#define BIT_COM_PMU_APB_DDR1_CHN2_CGM_SEL                                          BIT(3)
#define BIT_COM_PMU_APB_DDR1_CHN1_CGM_SEL                                          BIT(2)
#define BIT_COM_PMU_APB_DDR1_CHN0_CGM_SEL                                          BIT(1)
#define BIT_COM_PMU_APB_DDR1_CTRL_CGM_EN                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_AON_RAM_SLEEP_CTRL
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_CM3_MEM_ALL_SLEEP_EN                                       BIT(2)
#define BIT_COM_PMU_APB_AON_MEM_CM3_SLEEP_EN                                       BIT(1)
#define BIT_COM_PMU_APB_BIA_MEM_ALL_SLEEP_EN                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PUB_MEM_RESET_RET
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PUB1_MEM_RESET_RET                                         BIT(1)
#define BIT_COM_PMU_APB_PUB0_MEM_RESET_RET                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_BIA_VDD_L2_SRAM_CTRL
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_BIA_VDD_L2_SRAM_FRC_ON                                     BIT(1)
#define BIT_COM_PMU_APB_BIA_VDD_L2_SRAM_OFF_REQ_POL_SEL                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_CTRL
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_STATE(x)                                         (((x) & 0x1F) << 27)
#define BIT_COM_PMU_APB_LDO1P05_HVM_ON                                             BIT(19)
#define BIT_COM_PMU_APB_EFUSE_LDO_SLP_PD_EN                                        BIT(18)
#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY(x)                                     (((x) & 0xFFFF) << 2)
#define BIT_COM_PMU_APB_EFUSE_MODE(x)                                              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_DBG
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_CTRL_BYP                                         BIT(12)
#define BIT_COM_PMU_APB_LDO_EFUSE_HVM_VCCFHV_SW_EN_R                               BIT(11)
#define BIT_COM_PMU_APB_LDO_EFUSE_HVM_VCCF_SW_EN_R                                 BIT(10)
#define BIT_COM_PMU_APB_LDO_EFUSE_IFP_VCCFHV_SW_EN_R                               BIT(9)
#define BIT_COM_PMU_APB_LDO_EFUSE_IFP_VCCF_SW_EN_R                                 BIT(8)
#define BIT_COM_PMU_APB_LDO2P4_IFP_PD_R                                            BIT(7)
#define BIT_COM_PMU_APB_LDO1P05_IFP_PD_R                                           BIT(6)
#define BIT_COM_PMU_APB_LDO_REG_R(x)                                               (((x) & 0x1F) << 1)
#define BIT_COM_PMU_APB_LDO1P05_HVM_PD_R                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MPLL0_LP_CTRL0
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MPLL0_PWR_TIME1(x)                                         (((x) & 0xFFFF) << 4)
#define BIT_COM_PMU_APB_MPLL0_PWR_MODE(x)                                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MPLL0_LP_CTRL1
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MPLL0_PWR_TIME0(x)                                         (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MPLL1_LP_CTRL0
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MPLL1_PWR_TIME1(x)                                         (((x) & 0xFFFF) << 4)
#define BIT_COM_PMU_APB_MPLL1_PWR_MODE(x)                                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MPLL1_LP_CTRL1
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MPLL1_PWR_TIME0(x)                                         (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MPLL2_LP_CTRL0
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MPLL2_PWR_TIME1(x)                                         (((x) & 0xFFFF) << 4)
#define BIT_COM_PMU_APB_MPLL2_PWR_MODE(x)                                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MPLL2_LP_CTRL1
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MPLL2_PWR_TIME0(x)                                         (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_INT_REQ_PWR_CHG_CLR
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_INT_REQ_PWR_DOWN_CLR                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_MBOX_NOPWR_DOWN_BYP
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MBOX_NOPWR_DOWN_BYP                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_FENCING_LOCK_BYP
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_AP_SYS_M1_FENCING_LOCK_BYP_DIS                             BIT(30)
#define BIT_COM_PMU_APB_BIA_MEMAXI_FENCING_LOCK_BYP_DIS                            BIT(29)
#define BIT_COM_PMU_APB_WTLCP_SYS_FENCING1_LOCK_BYP_DIS                            BIT(27)
#define BIT_COM_PMU_APB_PUBCP_SYS_FENCING0_LOCK_BYP_DIS                            BIT(22)
#define BIT_COM_PMU_APB_AUD_SYS_FENCING0_LOCK_BYP_DIS                              BIT(21)
#define BIT_COM_PMU_APB_WTLCP_SYS_FENCING0_LOCK_BYP_DIS                            BIT(20)
#define BIT_COM_PMU_APB_AP_SYS_FENCING0_LOCK_BYP_DIS                               BIT(19)
#define BIT_COM_PMU_APB_CAM_SYS_FENCING0_LOCK_BYP_DIS                              BIT(18)
#define BIT_COM_PMU_APB_VSP_SYS_FENCING0_LOCK_BYP_DIS                              BIT(17)
#define BIT_COM_PMU_APB_GPU_TOP_FENCING0_LOCK_BYP_DIS                              BIT(16)
#define BIT_COM_PMU_APB_AP_SYS_M1_FENCING_LOCK_BYP                                 BIT(14)
#define BIT_COM_PMU_APB_BIA_MEMAXI_FENCING_LOCK_BYP                                BIT(13)
#define BIT_COM_PMU_APB_AUD_SYS_FENCING1_LOCK_BYP                                  BIT(12)
#define BIT_COM_PMU_APB_WTLCP_SYS_FENCING1_LOCK_BYP                                BIT(11)
#define BIT_COM_PMU_APB_AP_SYS_FENCING1_LOCK_BYP                                   BIT(10)
#define BIT_COM_PMU_APB_CAM_SYS_FENCING1_LOCK_BYP                                  BIT(9)
#define BIT_COM_PMU_APB_VSP_SYS_FENCING1_LOCK_BYP                                  BIT(8)
#define BIT_COM_PMU_APB_GPU_TOP_FENCING1_LOCK_BYP                                  BIT(7)
#define BIT_COM_PMU_APB_PUBCP_SYS_FENCING0_LOCK_BYP                                BIT(6)
#define BIT_COM_PMU_APB_AUD_SYS_FENCING0_LOCK_BYP                                  BIT(5)
#define BIT_COM_PMU_APB_WTLCP_SYS_FENCING0_LOCK_BYP                                BIT(4)
#define BIT_COM_PMU_APB_AP_SYS_FENCING0_LOCK_BYP                                   BIT(3)
#define BIT_COM_PMU_APB_CAM_SYS_FENCING0_LOCK_BYP                                  BIT(2)
#define BIT_COM_PMU_APB_VSP_SYS_FENCING0_LOCK_BYP                                  BIT(1)
#define BIT_COM_PMU_APB_GPU_TOP_FENCING0_LOCK_BYP                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_FENCING0_CTRL_STATE
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_BIA_MEMAXI_FENCING_CTRL_STATE(x)                           (((x) & 0xF) << 28)
#define BIT_COM_PMU_APB_PUBCP_SYS_FENCING0_CTRL_STATE(x)                           (((x) & 0xF) << 24)
#define BIT_COM_PMU_APB_AUD_SYS_FENCING0_CTRL_STATE(x)                             (((x) & 0xF) << 20)
#define BIT_COM_PMU_APB_WTLCP_SYS_FENCING0_CTRL_STATE(x)                           (((x) & 0xF) << 16)
#define BIT_COM_PMU_APB_AP_SYS_FENCING0_CTRL_STATE(x)                              (((x) & 0xF) << 12)
#define BIT_COM_PMU_APB_CAM_SYS_FENCING0_CTRL_STATE(x)                             (((x) & 0xF) << 8)
#define BIT_COM_PMU_APB_VSP_SYS_FENCING0_CTRL_STATE(x)                             (((x) & 0xF) << 4)
#define BIT_COM_PMU_APB_GPU_TOP_FENCING0_CTRL_STATE(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_FENCING1_CTRL_STATE
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_AP_SYS_M1_FENCING_CTRL_STATE(x)                            (((x) & 0xF) << 20)
#define BIT_COM_PMU_APB_WTLCP_SYS_FENCING1_CTRL_STATE(x)                           (((x) & 0xF) << 16)
#define BIT_COM_PMU_APB_AP_SYS_FENCING1_CTRL_STATE(x)                              (((x) & 0xF) << 12)
#define BIT_COM_PMU_APB_CAM_SYS_FENCING1_CTRL_STATE(x)                             (((x) & 0xF) << 8)
#define BIT_COM_PMU_APB_VSP_SYS_FENCING1_CTRL_STATE(x)                             (((x) & 0xF) << 4)
#define BIT_COM_PMU_APB_GPU_TOP_FENCING1_CTRL_STATE(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_DLY0
// Register Offset : 0x00DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY1(x)                                    (((x) & 0xFFFF) << 16)
#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY0(x)                                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_DLY1
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY3(x)                                    (((x) & 0xFFFF) << 16)
#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY2(x)                                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_DLY2
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY5(x)                                    (((x) & 0xFFFF) << 16)
#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY4(x)                                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_DLY3
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY7(x)                                    (((x) & 0xFFFF) << 16)
#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY6(x)                                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_DLY4
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY9(x)                                    (((x) & 0xFFFF) << 16)
#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY8(x)                                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_DLY5
// Register Offset : 0x00F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY11(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY10(x)                                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_DLY6
// Register Offset : 0x00F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY13(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY12(x)                                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_EFUSE_LDO_DLY7
// Register Offset : 0x00F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY15(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_COM_PMU_APB_EFUSE_LDO_TRANS_DLY14(x)                                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_AXI_LPC_CTRL_DISABLE
// Register Offset : 0x00FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_AXI_LPC_CTRL_DISABLE                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_AUD_DMA_BUSY_SLP_EN
// Register Offset : 0x0100
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DAP_PUB0_FRC_DSLP                                          BIT(13)
#define BIT_COM_PMU_APB_DAP_PUB0_FRC_LSLP                                          BIT(12)
#define BIT_COM_PMU_APB_SP_PUB0_FRC_DSLP                                           BIT(11)
#define BIT_COM_PMU_APB_SP_PUB0_FRC_LSLP                                           BIT(10)
#define BIT_COM_PMU_APB_DMA_MASTER_PUB0_FRC_DSLP                                   BIT(9)
#define BIT_COM_PMU_APB_DMA_MASTER_PUB0_FRC_LSLP                                   BIT(8)
#define BIT_COM_PMU_APB_DMA_CHN2_GRP2_BUSY_PUB0_DSLP_EN                            BIT(7)
#define BIT_COM_PMU_APB_DMA_CHN1_GRP2_BUSY_PUB0_DSLP_EN                            BIT(6)
#define BIT_COM_PMU_APB_DMA_CHN2_GRP1_BUSY_PUB0_DSLP_EN                            BIT(5)
#define BIT_COM_PMU_APB_DMA_CHN1_GRP1_BUSY_PUB0_DSLP_EN                            BIT(4)
#define BIT_COM_PMU_APB_DMA_CHN2_GRP2_BUSY_LSLP_EN                                 BIT(3)
#define BIT_COM_PMU_APB_DMA_CHN1_GRP2_BUSY_LSLP_EN                                 BIT(2)
#define BIT_COM_PMU_APB_DMA_CHN2_GRP1_BUSY_LSLP_EN                                 BIT(1)
#define BIT_COM_PMU_APB_DMA_CHN1_GRP1_BUSY_LSLP_EN                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_AUD_SYS_SLP_EN
// Register Offset : 0x0104
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_AUD_SYS_PUB0_DSLP_EN                                       BIT(1)
#define BIT_COM_PMU_APB_AUD_SYS_LSLP_EN                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DDR0_LP_MASK
// Register Offset : 0x0108
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_AUD_SYS_DDR0_PD_MASK                                       BIT(3)
#define BIT_COM_PMU_APB_CAM_SYS_DDR0_PD_MASK                                       BIT(2)
#define BIT_COM_PMU_APB_AUD_SYS_DDR0_SLEEP_MASK                                    BIT(1)
#define BIT_COM_PMU_APB_CAM_SYS_DDR0_SLEEP_MASK                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DSPLL_LP_CTRL0
// Register Offset : 0x010C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DSPLL_PWR_TIME1(x)                                         (((x) & 0xFFFF) << 4)
#define BIT_COM_PMU_APB_DSPLL_PWR_MODE(x)                                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DSPLL_LP_CTRL1
// Register Offset : 0x0110
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DSPLL_PWR_TIME0(x)                                         (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_GPU_CORE_FORCE
// Register Offset : 0x0114
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_GPU_CORE_1_FORCE_ON                                        BIT(1)
#define BIT_COM_PMU_APB_GPU_CORE_0_FORCE_ON                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_INT_REQ_PWR_ON_CFG
// Register Offset : 0x0118
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_INT_REQ_PWR_ON_D(x)                                        (((x) & 0x7F) << 24)
#define BIT_COM_PMU_APB_INT_REQ_PWR_ON_R(x)                                        (((x) & 0x7F) << 8)
#define BIT_COM_PMU_APB_INT_REQ_PWR_ON_CLR(x)                                      (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_SMART_LSLP_ENA
// Register Offset : 0x011C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_AP_SYS_M1_SMART_LSLP_ENA                                   BIT(9)
#define BIT_COM_PMU_APB_BIA_MEMAXI_SMART_LSLP_ENA                                  BIT(8)
#define BIT_COM_PMU_APB_PUBCP_SYS_SMART_LSLP_ENA                                   BIT(7)
#define BIT_COM_PMU_APB_AUD_SYS_SMART_LSLP_ENA                                     BIT(6)
#define BIT_COM_PMU_APB_WTLCP_SYS_SMART_LSLP_ENA1                                  BIT(5)
#define BIT_COM_PMU_APB_WTLCP_SYS_SMART_LSLP_ENA0                                  BIT(4)
#define BIT_COM_PMU_APB_AP_SYS_SMART_LSLP_ENA                                      BIT(3)
#define BIT_COM_PMU_APB_CAM_SYS_SMART_LSLP_ENA                                     BIT(2)
#define BIT_COM_PMU_APB_VSP_SYS_SMART_LSLP_ENA                                     BIT(1)
#define BIT_COM_PMU_APB_GPU_TOP_SMART_LSLP_ENA                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_FENCING_LOCK_WAIT_NUM0
// Register Offset : 0x0200
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_AP_SYS_FENCING_LOCK_WAIT_NUM(x)                            (((x) & 0xFF) << 24)
#define BIT_COM_PMU_APB_CAM_SYS_FENCING_LOCK_WAIT_NUM(x)                           (((x) & 0xFF) << 16)
#define BIT_COM_PMU_APB_VSP_SYS_FENCING_LOCK_WAIT_NUM(x)                           (((x) & 0xFF) << 8)
#define BIT_COM_PMU_APB_GPU_TOP_FENCING_LOCK_WAIT_NUM(x)                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_FENCING_LOCK_WAIT_NUM1
// Register Offset : 0x0204
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PUBCP_SYS_FENCING_LOCK_WAIT_NUM(x)                         (((x) & 0xFF) << 24)
#define BIT_COM_PMU_APB_AUD_SYS_FENCING_LOCK_WAIT_NUM(x)                           (((x) & 0xFF) << 16)
#define BIT_COM_PMU_APB_WTLCP_SYS_FENCING1_LOCK_WAIT_NUM(x)                        (((x) & 0xFF) << 8)
#define BIT_COM_PMU_APB_WTLCP_SYS_FENCING0_LOCK_WAIT_NUM(x)                        (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_FENCING_LOCK_WAIT_NUM2
// Register Offset : 0x0208
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_BIA_MEMAXI_FENCING_LOCK_WAIT_NUM(x)                        (((x) & 0xFF) << 8)
#define BIT_COM_PMU_APB_AP_SYS_M1_FENCING_LOCK_WAIT_NUM(x)                         (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_SP_PUB_ACCESS_EN
// Register Offset : 0x020C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_SP_PUB_ACCESS_EN                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DDR_SLEEP_CNT
// Register Offset : 0x0210
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DDR_SLEEP_CNT(x)                                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_DDR_SLEEP_CNT_CFG
// Register Offset : 0x0214
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_DDR_SLEEP_CNT_HALT                                         BIT(1)
#define BIT_COM_PMU_APB_DDR_SLEEP_CNT_EN                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PMU_ENHANCE_EN
// Register Offset : 0x0218
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_CM4_INT_DIS_EN                                             BIT(5)
#define BIT_COM_PMU_APB_PD_TOP_OFF_COND_REDUCE                                     BIT(4)
#define BIT_COM_PMU_APB_TOP_FRC_BLK_OFF_EN                                         BIT(3)
#define BIT_COM_PMU_APB_BLK_FRC_TOP_ON_EN                                          BIT(2)
#define BIT_COM_PMU_APB_PD_TOP_OFF_COUPLE_EN                                       BIT(1)
#define BIT_COM_PMU_APB_NEST_DOM_ENHANCE_EN                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PLL_STATUS_MASK
// Register Offset : 0x021C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_MPLL1_PD_STAT_MASK                                         BIT(5)
#define BIT_COM_PMU_APB_MPLL0_PD_STAT_MASK                                         BIT(4)
#define BIT_COM_PMU_APB_DSPLL_STATUS_MASK                                          BIT(3)
#define BIT_COM_PMU_APB_MPLL2_STATUS_MASK                                          BIT(2)
#define BIT_COM_PMU_APB_MPLL1_STATUS_MASK                                          BIT(1)
#define BIT_COM_PMU_APB_MPLL0_STATUS_MASK                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PMU_DEBUG_CFG
// Register Offset : 0x0220
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PMU_DEBUG_SEL(x)                                           (((x) & 0x1F) << 16)
#define BIT_COM_PMU_APB_CM4_SYS_DOZE_SLEEP_CNT_EN                                  BIT(13)
#define BIT_COM_PMU_APB_CM4_SYS_DEEP_SLEEP_CNT_EN                                  BIT(12)
#define BIT_COM_PMU_APB_PUBCP_SYS_DOZE_SLEEP_CNT_EN                                BIT(11)
#define BIT_COM_PMU_APB_PUBCP_SYS_PUB_DEEP_SLEEP0_CNT_EN                           BIT(10)
#define BIT_COM_PMU_APB_PUBCP_SYS_LIGHT_SLEEP0_CNT_EN                              BIT(9)
#define BIT_COM_PMU_APB_PUBCP_SYS_DEEP_SLEEP_CNT_EN                                BIT(8)
#define BIT_COM_PMU_APB_WTLCP_SYS_DOZE_SLEEP_CNT_EN                                BIT(7)
#define BIT_COM_PMU_APB_WTLCP_SYS_PUB_DEEP_SLEEP0_CNT_EN                           BIT(6)
#define BIT_COM_PMU_APB_WTLCP_SYS_LIGHT_SLEEP0_CNT_EN                              BIT(5)
#define BIT_COM_PMU_APB_WTLCP_SYS_DEEP_SLEEP_CNT_EN                                BIT(4)
#define BIT_COM_PMU_APB_AP_SYS_DOZE_SLEEP_CNT_EN                                   BIT(3)
#define BIT_COM_PMU_APB_AP_SYS_PUB_DEEP_SLEEP0_CNT_EN                              BIT(2)
#define BIT_COM_PMU_APB_AP_SYS_LIGHT_SLEEP0_CNT_EN                                 BIT(1)
#define BIT_COM_PMU_APB_AP_SYS_DEEP_SLEEP_CNT_EN                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COM_PMU_APB_PMU_DEBUG_BUS
// Register Offset : 0x0224
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COM_PMU_APB_PMU_DEBUG_BUS(x)                                           (((x) & 0xFFFFFFFF))


#endif // _COM_PMU_APB_REG_H
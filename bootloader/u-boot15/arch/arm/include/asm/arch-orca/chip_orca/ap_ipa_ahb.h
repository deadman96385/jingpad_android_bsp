/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-02-11 15:07:05
 *
 */


#ifndef AP_IPA_AHB_H
#define AP_IPA_AHB_H

#define CTL_BASE_AP_IPA_AHB 0x29000000


#define REG_AP_IPA_AHB_AHB_EB                      ( CTL_BASE_AP_IPA_AHB + 0x0000 )
#define REG_AP_IPA_AHB_AHB_RST                     ( CTL_BASE_AP_IPA_AHB + 0x0004 )
#define REG_AP_IPA_AHB_AP_SYS_FORCE_SLEEP_CFG      ( CTL_BASE_AP_IPA_AHB + 0x0008 )
#define REG_AP_IPA_AHB_USB1_CTRL                   ( CTL_BASE_AP_IPA_AHB + 0x000C )
#define REG_AP_IPA_AHB_USB1_DBG0                   ( CTL_BASE_AP_IPA_AHB + 0x0014 )
#define REG_AP_IPA_AHB_USB1_DBG1                   ( CTL_BASE_AP_IPA_AHB + 0x0018 )
#define REG_AP_IPA_AHB_USB1_DBG2                   ( CTL_BASE_AP_IPA_AHB + 0x001C )
#define REG_AP_IPA_AHB_PCIE_CTL0                   ( CTL_BASE_AP_IPA_AHB + 0x002C )
#define REG_AP_IPA_AHB_PCIE_CTL1                   ( CTL_BASE_AP_IPA_AHB + 0x0030 )
#define REG_AP_IPA_AHB_PCIE_CTL2                   ( CTL_BASE_AP_IPA_AHB + 0x0034 )
#define REG_AP_IPA_AHB_PCIE_CTL3                   ( CTL_BASE_AP_IPA_AHB + 0x0038 )
#define REG_AP_IPA_AHB_APB_PCLK_AUTO_GATE_EB       ( CTL_BASE_AP_IPA_AHB + 0x003C )
#define REG_AP_IPA_AHB_APB_PCLK_AUTO_SLOW_SEL      ( CTL_BASE_AP_IPA_AHB + 0x0040 )
#define REG_AP_IPA_AHB_AP_SYS_AUTO_SLEEP_CFG       ( CTL_BASE_AP_IPA_AHB + 0x004C )
#define REG_AP_IPA_AHB_IMTX_M0_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0100 )
#define REG_AP_IPA_AHB_IMTX_M1_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0104 )
#define REG_AP_IPA_AHB_IMTX_M2_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0108 )
#define REG_AP_IPA_AHB_IMTX_M3_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x010C )
#define REG_AP_IPA_AHB_IMTX_M4_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0110 )
#define REG_AP_IPA_AHB_IMTX_M5_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0114 )
#define REG_AP_IPA_AHB_IMTX_M6_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0118 )
#define REG_AP_IPA_AHB_IMTX_M7_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x011C )
#define REG_AP_IPA_AHB_IMTX_M8_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0120 )
#define REG_AP_IPA_AHB_IMTX_M9_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0124 )
#define REG_AP_IPA_AHB_IMTX_MAIN_LPC               ( CTL_BASE_AP_IPA_AHB + 0x013C )
#define REG_AP_IPA_AHB_IMTX_S0_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0140 )
#define REG_AP_IPA_AHB_IMTX_S1_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0144 )
#define REG_AP_IPA_AHB_IMTX_S2_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0148 )
#define REG_AP_IPA_AHB_IMTX_S3_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x014C )
#define REG_AP_IPA_AHB_IMTX_S4_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0150 )
#define REG_AP_IPA_AHB_IMTX_S5_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0154 )
#define REG_AP_IPA_AHB_IMTX_S6_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0158 )
#define REG_AP_IPA_AHB_IMTX_S7_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x015C )
#define REG_AP_IPA_AHB_IMTX_S8_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0160 )
#define REG_AP_IPA_AHB_IMTX_S9_LPC                 ( CTL_BASE_AP_IPA_AHB + 0x0164 )
#define REG_AP_IPA_AHB_IMTX_MST_FRC_LSLP           ( CTL_BASE_AP_IPA_AHB + 0x0180 )
#define REG_AP_IPA_AHB_IMTX_LSLP_LPC_BYPASS        ( CTL_BASE_AP_IPA_AHB + 0x0184 )
#define REG_AP_IPA_AHB_IMTX_MST_FRC_PUB_DSLP       ( CTL_BASE_AP_IPA_AHB + 0x0188 )
#define REG_AP_IPA_AHB_IMTX_PUB_DSLP_LPC_BYPASS    ( CTL_BASE_AP_IPA_AHB + 0x018C )
#define REG_AP_IPA_AHB_IMTX_MST_FRC_DOZE           ( CTL_BASE_AP_IPA_AHB + 0x0190 )
#define REG_AP_IPA_AHB_IMTX_DOZE_LPC_BYPASS        ( CTL_BASE_AP_IPA_AHB + 0x0194 )
#define REG_AP_IPA_AHB_IMTX_AXI_FREQ_ALLOW0        ( CTL_BASE_AP_IPA_AHB + 0x0198 )
#define REG_AP_IPA_AHB_IMTX_AXI_FREQ_ALLOW1        ( CTL_BASE_AP_IPA_AHB + 0x019C )
#define REG_AP_IPA_AHB_IMTX_AXI_FREQ_LSLP_ALLOW0   ( CTL_BASE_AP_IPA_AHB + 0x01A0 )
#define REG_AP_IPA_AHB_IMTX_AXI_FREQ_LSLP_ALLOW1   ( CTL_BASE_AP_IPA_AHB + 0x01A4 )
#define REG_AP_IPA_AHB_AP_QOS0                     ( CTL_BASE_AP_IPA_AHB + 0x0300 )
#define REG_AP_IPA_AHB_AP_QOS1                     ( CTL_BASE_AP_IPA_AHB + 0x0304 )
#define REG_AP_IPA_AHB_AP_URGENCY                  ( CTL_BASE_AP_IPA_AHB + 0x0308 )
#define REG_AP_IPA_AHB_AP_USER0                    ( CTL_BASE_AP_IPA_AHB + 0x030C )
#define REG_AP_IPA_AHB_AP_USER1                    ( CTL_BASE_AP_IPA_AHB + 0x0310 )
#define REG_AP_IPA_AHB_AP_USER2                    ( CTL_BASE_AP_IPA_AHB + 0x0314 )
#define REG_AP_IPA_AHB_IMTX_CTRL                   ( CTL_BASE_AP_IPA_AHB + 0x0318 )
#define REG_AP_IPA_AHB_IPA_CTRL                    ( CTL_BASE_AP_IPA_AHB + 0x031C )
#define REG_AP_IPA_AHB_PAM_WIFI_CTRL               ( CTL_BASE_AP_IPA_AHB + 0x0320 )
#define REG_AP_IPA_AHB_IMTX_M10_CTRL               ( CTL_BASE_AP_IPA_AHB + 0x0324 )
#define REG_AP_IPA_AHB_PCIE_LP_CTRL                ( CTL_BASE_AP_IPA_AHB + 0x0328 )
#define REG_AP_IPA_AHB_IMTX_PU_NUM0                ( CTL_BASE_AP_IPA_AHB + 0x032C )
#define REG_AP_IPA_AHB_IMTX_PU_NUM1                ( CTL_BASE_AP_IPA_AHB + 0x0330 )
#define REG_AP_IPA_AHB_IMTX_PU_NUM2                ( CTL_BASE_AP_IPA_AHB + 0x0334 )
#define REG_AP_IPA_AHB_IMTX_PU_NUM3                ( CTL_BASE_AP_IPA_AHB + 0x0338 )
#define REG_AP_IPA_AHB_IMTX_PU_NUM4                ( CTL_BASE_AP_IPA_AHB + 0x033C )
#define REG_AP_IPA_AHB_IMTX_PU_NUM5                ( CTL_BASE_AP_IPA_AHB + 0x0340 )
#define REG_AP_IPA_AHB_PAM_WIFI_PCLK_DFS_CTRL      ( CTL_BASE_AP_IPA_AHB + 0x0344 )
#define REG_AP_IPA_AHB_PCIE_CTRL                   ( CTL_BASE_AP_IPA_AHB + 0x0348 )
#define REG_AP_IPA_AHB_SYS_ACCESS_EN               ( CTL_BASE_AP_IPA_AHB + 0x034C )
#define REG_AP_IPA_AHB_CGM_GATE_EN                 ( CTL_BASE_AP_IPA_AHB + 0x0350 )
#define REG_AP_IPA_AHB_IP_BUSY_GATE_EN             ( CTL_BASE_AP_IPA_AHB + 0x0354 )
#define REG_AP_IPA_AHB_SDSLV_CTRL                  ( CTL_BASE_AP_IPA_AHB + 0x0358 )
#define REG_AP_IPA_AHB_PCIE_SW_MSI_INT             ( CTL_BASE_AP_IPA_AHB + 0x035C )
#define REG_AP_IPA_AHB_RESERVE0                    ( CTL_BASE_AP_IPA_AHB + 0x0400 )
#define REG_AP_IPA_AHB_RESERVE1                    ( CTL_BASE_AP_IPA_AHB + 0x0404 )

/* REG_AP_IPA_AHB_AHB_EB */

#define BIT_AP_IPA_AHB_PCIE_SEL                          BIT(9)
#define BIT_AP_IPA_AHB_USB_PAM_EB                        BIT(8)
#define BIT_AP_IPA_AHB_IPA_EB                            BIT(7)
#define BIT_AP_IPA_AHB_PCIE_AUX_EB                       BIT(6)
#define BIT_AP_IPA_AHB_PCIE_EB                           BIT(5)
#define BIT_AP_IPA_AHB_SDIO_SLV_FRUN_EB                  BIT(4)
#define BIT_AP_IPA_AHB_SDIO_SLV_EB                       BIT(3)
#define BIT_AP_IPA_AHB_USB1_REF_EB                       BIT(2)
#define BIT_AP_IPA_AHB_USB1_SUSPEND_EB                   BIT(1)
#define BIT_AP_IPA_AHB_USB1_EB                           BIT(0)

/* REG_AP_IPA_AHB_AHB_RST */

#define BIT_AP_IPA_AHB_USB_PAM_SOFT_RST                  BIT(5)
#define BIT_AP_IPA_AHB_IPA_SOFT_RST                      BIT(4)
#define BIT_AP_IPA_AHB_PCIE_SOFT_RST                     BIT(3)
#define BIT_AP_IPA_AHB_SDIO_SLV_SOFT_RST                 BIT(2)
#define BIT_AP_IPA_AHB_PCIE_BUT_SOFT_RST                 BIT(1)
#define BIT_AP_IPA_AHB_USB1_SOFT_RST                     BIT(0)

/* REG_AP_IPA_AHB_AP_SYS_FORCE_SLEEP_CFG */

#define BIT_AP_IPA_AHB_CP1_SYS_SW_SLEEP                  BIT(3)
#define BIT_AP_IPA_AHB_CP0_SYS_SW_SLEEP                  BIT(2)
#define BIT_AP_IPA_AHB_IPA_APB_FRC_SLP                   BIT(1)
#define BIT_AP_IPA_AHB_CGM_CLK_AP_AXI_AUTO_GATE_EN       BIT(0)

/* REG_AP_IPA_AHB_USB1_CTRL */

#define BIT_AP_IPA_AHB_PIPE3_POWERPRESENT1               BIT(16)
#define BIT_AP_IPA_AHB_UTMISRP_BVALID_REG1               BIT(15)
#define BIT_AP_IPA_AHB_OTG_VBUS_VALID_PHYREG1            BIT(14)
#define BIT_AP_IPA_AHB_OTG_VBUS_VALID_PHYREG_SEL1        BIT(13)
#define BIT_AP_IPA_AHB_HOST_SYSTEM_ERR1                  BIT(12)
#define BIT_AP_IPA_AHB_HOST_PORT_POWER_CONTROL_PRESENT1  BIT(11)
#define BIT_AP_IPA_AHB_FLADJ_30MHZ_REG1(x)               (((x) & 0x3F) << 5)
#define BIT_AP_IPA_AHB_PME_EN1                           BIT(4)
#define BIT_AP_IPA_AHB_BUS_FILTER_BYPASS1(x)             (((x) & 0xF))

/* REG_AP_IPA_AHB_USB1_DBG0 */

#define BIT_AP_IPA_AHB_USB1_DUG_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_AP_IPA_AHB_USB1_DBG1 */

#define BIT_AP_IPA_AHB_USB1_DUG_1(x)                     (((x) & 0xFFFFFFFF))

/* REG_AP_IPA_AHB_USB1_DBG2 */

#define BIT_AP_IPA_AHB_USB1_HOST_CURRENT_BELT(x)         (((x) & 0xFFF) << 6)
#define BIT_AP_IPA_AHB_USB1_CLK_GATE_CTRL(x)             (((x) & 0x7) << 3)
#define BIT_AP_IPA_AHB_USB1_DUG_2(x)                     (((x) & 0x7))

/* REG_AP_IPA_AHB_PCIE_CTL0 */

#define BIT_AP_IPA_AHB_PCIE_STATUS(x)                    (((x) & 0xFFFF) << 16)
#define BIT_AP_IPA_AHB_PCIE_CONFIG(x)                    (((x) & 0x3FF) << 6)
#define BIT_AP_IPA_AHB_APP_XFER_PENDING                  BIT(5)
#define BIT_AP_IPA_AHB_APP_L1_PWR_OFF_EN                 BIT(4)
#define BIT_AP_IPA_AHB_DBG_PBA                           BIT(3)
#define BIT_AP_IPA_AHB_DBG_TABLE                         BIT(2)
#define BIT_AP_IPA_AHB_PCIE_SYS_INT_USB_PAM_EN           BIT(1)
#define BIT_AP_IPA_AHB_PCIE_SYS_INT_SW_EN                BIT(0)

/* REG_AP_IPA_AHB_PCIE_CTL1 */

#define BIT_AP_IPA_AHB_PCIE_RSV(x)                       (((x) & 0xFFFFFFFF))

/* REG_AP_IPA_AHB_PCIE_CTL2 */

#define BIT_AP_IPA_AHB_APP_RAS_DES_TBA_CTRL(x)           (((x) & 0x3) << 30)
#define BIT_AP_IPA_AHB_APP_RAS_DES_SD_HOLD_LTSSM         BIT(29)
#define BIT_AP_IPA_AHB_CFG_LINK_AUTO_BW_INT              BIT(28)
#define BIT_AP_IPA_AHB_HP_MSI                            BIT(27)
#define BIT_AP_IPA_AHB_HP_INT                            BIT(26)
#define BIT_AP_IPA_AHB_HP_PMUE(x)                        (((x) & 0x1F) << 21)
#define BIT_AP_IPA_AHB_CFG_PCIE_CAP_INT_MSG_NUM          BIT(20)
#define BIT_AP_IPA_AHB_CFG_PME_MSI                       BIT(19)
#define BIT_AP_IPA_AHB_CFG_PME_INT(x)                    (((x) & 0x1F) << 14)
#define BIT_AP_IPA_AHB_CFG_AER_INT_MSG_NUM               BIT(13)
#define BIT_AP_IPA_AHB_CFG_AER_RC_ERR_MSI                BIT(12)
#define BIT_AP_IPA_AHB_CFG_AER_RC_ERR_INT                BIT(11)
#define BIT_AP_IPA_AHB_CFG_EML_CONTRL                    BIT(10)
#define BIT_AP_IPA_AHB_CFG_BUS_MASTER_EN                 BIT(9)
#define BIT_AP_IPA_AHB_CFG_PWR_CTRLER_CTRL               BIT(8)
#define BIT_AP_IPA_AHB_CFG_ATTEN_IND(x)                  (((x) & 0x3) << 6)
#define BIT_AP_IPA_AHB_CFG_PWR_IND(x)                    (((x) & 0x3) << 4)
#define BIT_AP_IPA_AHB_CFG_MULTI_MSI_EN(x)               (((x) & 0x7) << 1)
#define BIT_AP_IPA_AHB_CFG_MSI_EN                        BIT(0)

/* REG_AP_IPA_AHB_PCIE_CTL3 */

#define BIT_AP_IPA_AHB_CFG_MSI_MASK(x)                   (((x) & 0xFFFFFFFF))

/* REG_AP_IPA_AHB_APB_PCLK_AUTO_GATE_EB */

#define BIT_AP_IPA_AHB_SDIO_SLV_PCLK_AUTO_GATE_EB        BIT(3)
#define BIT_AP_IPA_AHB_PCIE_SNPS_PCLK_AUTO_GATE_EB       BIT(2)
#define BIT_AP_IPA_AHB_PCIE_XZ_PCLK_AUTO_GATE_EB         BIT(1)
#define BIT_AP_IPA_AHB_USB_PAM_PCLK_AUTO_GATE_EB         BIT(0)

/* REG_AP_IPA_AHB_APB_PCLK_AUTO_SLOW_SEL */

#define BIT_AP_IPA_AHB_SDIO_SLV_PCLK_AUTO_SLOW_EN        BIT(15)
#define BIT_AP_IPA_AHB_SDIO_SLV_PCLK_AUTO_SLOW_SEL(x)    (((x) & 0x7) << 12)
#define BIT_AP_IPA_AHB_PCIE_SNPS_PCLK_AUTO_SLOW_EN       BIT(11)
#define BIT_AP_IPA_AHB_PCIE_SNPS_PCLK_AUTO_SLOW_SEL(x)   (((x) & 0x7) << 8)
#define BIT_AP_IPA_AHB_PCIE_XZ_PCLK_AUTO_SLOW_EN         BIT(7)
#define BIT_AP_IPA_AHB_PCIE_XZ_PCLK_AUTO_SLOW_SEL(x)     (((x) & 0x7) << 4)
#define BIT_AP_IPA_AHB_USB_PAM_PCLK_AUTO_SLOW_EN         BIT(3)
#define BIT_AP_IPA_AHB_USB_PAM_PCLK_AUTO_SLOW_SEL(x)     (((x) & 0x7))

/* REG_AP_IPA_AHB_AP_SYS_AUTO_SLEEP_CFG */

#define BIT_AP_IPA_AHB_CACTIVE_SLV3_WAKEUP_EN            BIT(3)
#define BIT_AP_IPA_AHB_AP_CLK_GATE_LPC_BYP               BIT(2)
#define BIT_AP_IPA_AHB_LP_AUTO_CTRL_EN                   BIT(1)
#define BIT_AP_IPA_AHB_IMTX_LPC_DISABLE                  BIT(0)

/* REG_AP_IPA_AHB_IMTX_M0_LPC */

#define BIT_AP_IPA_AHB_IMTX_M0_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M0_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_M1_LPC */

#define BIT_AP_IPA_AHB_IMTX_M1_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M1_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_M2_LPC */

#define BIT_AP_IPA_AHB_IMTX_M2_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_IMTX_M2_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M2_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_M3_LPC */

#define BIT_AP_IPA_AHB_IMTX_M3_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_IMTX_M3_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M3_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_M4_LPC */

#define BIT_AP_IPA_AHB_IMTX_M4_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_IMTX_M4_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M4_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_M5_LPC */

#define BIT_AP_IPA_AHB_IMTX_M5_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M5_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_M6_LPC */

#define BIT_AP_IPA_AHB_IMTX_M6_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M6_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_M7_LPC */

#define BIT_AP_IPA_AHB_IMTX_M7_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M7_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_M8_LPC */

#define BIT_AP_IPA_AHB_IMTX_M8_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M8_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_M9_LPC */

#define BIT_AP_IPA_AHB_IMTX_M9_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_IMTX_M9_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M9_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_MAIN_LPC */

#define BIT_AP_IPA_AHB_IMTX_MAIN_LP_EARLY_WAKEUP_EN      BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_AUTO_GATE_EN             BIT(17)
#define BIT_AP_IPA_AHB_IMTX_MAIN_LP_EB                   BIT(16)
#define BIT_AP_IPA_AHB_IMTX_MAIN_LP_NUM(x)               (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S0_LPC */

#define BIT_AP_IPA_AHB_IMTX_S0_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S0_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S0_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S0_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S1_LPC */

#define BIT_AP_IPA_AHB_IMTX_S1_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S1_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S1_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S1_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S2_LPC */

#define BIT_AP_IPA_AHB_IMTX_S2_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S2_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S2_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S2_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S3_LPC */

#define BIT_AP_IPA_AHB_IMTX_S3_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S3_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S3_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S3_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S4_LPC */

#define BIT_AP_IPA_AHB_IMTX_S4_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S4_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S4_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S4_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S5_LPC */

#define BIT_AP_IPA_AHB_IMTX_S5_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S5_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S5_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S5_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S6_LPC */

#define BIT_AP_IPA_AHB_IMTX_S6_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S6_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S6_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S6_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S7_LPC */

#define BIT_AP_IPA_AHB_IMTX_S7_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S7_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S7_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S7_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S8_LPC */

#define BIT_AP_IPA_AHB_IMTX_S8_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S8_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S8_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S8_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_S9_LPC */

#define BIT_AP_IPA_AHB_IMTX_S9_LP_EARLY_WAKEUP_EN        BIT(18)
#define BIT_AP_IPA_AHB_CGM_IMTX_S9_AUTO_GATE_EN          BIT(17)
#define BIT_AP_IPA_AHB_IMTX_S9_LP_EB                     BIT(16)
#define BIT_AP_IPA_AHB_IMTX_S9_LP_NUM(x)                 (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_IMTX_MST_FRC_LSLP */

#define BIT_AP_IPA_AHB_IMTX_S5_FRC_LSLP                  BIT(10)
#define BIT_AP_IPA_AHB_IMTX_M9_FRC_LSLP                  BIT(9)
#define BIT_AP_IPA_AHB_IMTX_M8_FRC_LSLP                  BIT(8)
#define BIT_AP_IPA_AHB_IMTX_M7_FRC_LSLP                  BIT(7)
#define BIT_AP_IPA_AHB_IMTX_M6_FRC_LSLP                  BIT(6)
#define BIT_AP_IPA_AHB_IMTX_M5_FRC_LSLP                  BIT(5)
#define BIT_AP_IPA_AHB_IMTX_M4_FRC_LSLP                  BIT(4)
#define BIT_AP_IPA_AHB_IMTX_M3_FRC_LSLP                  BIT(3)
#define BIT_AP_IPA_AHB_IMTX_M2_FRC_LSLP                  BIT(2)
#define BIT_AP_IPA_AHB_IMTX_M1_FRC_LSLP                  BIT(1)
#define BIT_AP_IPA_AHB_IMTX_M0_FRC_LSLP                  BIT(0)

/* REG_AP_IPA_AHB_IMTX_LSLP_LPC_BYPASS */

#define BIT_AP_IPA_AHB_LSLP_IMTX_S5_LPC_BYPASS           BIT(10)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M9_LPC_BYPASS           BIT(9)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M8_LPC_BYPASS           BIT(8)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M7_LPC_BYPASS           BIT(7)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M6_LPC_BYPASS           BIT(6)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M5_LPC_BYPASS           BIT(5)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M4_LPC_BYPASS           BIT(4)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M3_LPC_BYPASS           BIT(3)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M2_LPC_BYPASS           BIT(2)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M1_LPC_BYPASS           BIT(1)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M0_LPC_BYPASS           BIT(0)

/* REG_AP_IPA_AHB_IMTX_MST_FRC_PUB_DSLP */

#define BIT_AP_IPA_AHB_IMTX_S5_FRC_PUB_DSLP              BIT(10)
#define BIT_AP_IPA_AHB_IMTX_M9_FRC_PUB_DSLP              BIT(9)
#define BIT_AP_IPA_AHB_IMTX_M8_FRC_PUB_DSLP              BIT(8)
#define BIT_AP_IPA_AHB_IMTX_M7_FRC_PUB_DSLP              BIT(7)
#define BIT_AP_IPA_AHB_IMTX_M6_FRC_PUB_DSLP              BIT(6)
#define BIT_AP_IPA_AHB_IMTX_M5_FRC_PUB_DSLP              BIT(5)
#define BIT_AP_IPA_AHB_IMTX_M4_FRC_PUB_DSLP              BIT(4)
#define BIT_AP_IPA_AHB_IMTX_M3_FRC_PUB_DSLP              BIT(3)
#define BIT_AP_IPA_AHB_IMTX_M2_FRC_PUB_DSLP              BIT(2)
#define BIT_AP_IPA_AHB_IMTX_M1_FRC_PUB_DSLP              BIT(1)
#define BIT_AP_IPA_AHB_IMTX_M0_FRC_PUB_DSLP              BIT(0)

/* REG_AP_IPA_AHB_IMTX_PUB_DSLP_LPC_BYPASS */

#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_S5_LPC_BYPASS       BIT(10)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M9_LPC_BYPASS       BIT(9)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M8_LPC_BYPASS       BIT(8)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M7_LPC_BYPASS       BIT(7)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M6_LPC_BYPASS       BIT(6)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M5_LPC_BYPASS       BIT(5)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M4_LPC_BYPASS       BIT(4)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M3_LPC_BYPASS       BIT(3)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M2_LPC_BYPASS       BIT(2)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M1_LPC_BYPASS       BIT(1)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M0_LPC_BYPASS       BIT(0)

/* REG_AP_IPA_AHB_IMTX_MST_FRC_DOZE */

#define BIT_AP_IPA_AHB_IMTX_M9_FRC_DOZE                  BIT(9)
#define BIT_AP_IPA_AHB_IMTX_M8_FRC_DOZE                  BIT(8)
#define BIT_AP_IPA_AHB_IMTX_M7_FRC_DOZE                  BIT(7)
#define BIT_AP_IPA_AHB_IMTX_M6_FRC_DOZE                  BIT(6)
#define BIT_AP_IPA_AHB_IMTX_M5_FRC_DOZE                  BIT(5)
#define BIT_AP_IPA_AHB_IMTX_M4_FRC_DOZE                  BIT(4)
#define BIT_AP_IPA_AHB_IMTX_M3_FRC_DOZE                  BIT(3)
#define BIT_AP_IPA_AHB_IMTX_M2_FRC_DOZE                  BIT(2)
#define BIT_AP_IPA_AHB_IMTX_M1_FRC_DOZE                  BIT(1)
#define BIT_AP_IPA_AHB_IMTX_M0_FRC_DOZE                  BIT(0)

/* REG_AP_IPA_AHB_IMTX_DOZE_LPC_BYPASS */

#define BIT_AP_IPA_AHB_DOZE_IMTX_MAIN_LPC_BYPASS         BIT(20)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S9_LPC_BYPASS           BIT(19)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S8_LPC_BYPASS           BIT(18)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S7_LPC_BYPASS           BIT(17)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S6_LPC_BYPASS           BIT(16)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S5_LPC_BYPASS           BIT(15)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S4_LPC_BYPASS           BIT(14)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S3_LPC_BYPASS           BIT(13)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S2_LPC_BYPASS           BIT(12)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S1_LPC_BYPASS           BIT(11)
#define BIT_AP_IPA_AHB_DOZE_IMTX_S0_LPC_BYPASS           BIT(10)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M9_LPC_BYPASS           BIT(9)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M8_LPC_BYPASS           BIT(8)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M7_LPC_BYPASS           BIT(7)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M6_LPC_BYPASS           BIT(6)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M5_LPC_BYPASS           BIT(5)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M4_LPC_BYPASS           BIT(4)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M3_LPC_BYPASS           BIT(3)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M2_LPC_BYPASS           BIT(2)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M1_LPC_BYPASS           BIT(1)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M0_LPC_BYPASS           BIT(0)

/* REG_AP_IPA_AHB_IMTX_AXI_FREQ_ALLOW0 */

#define BIT_AP_IPA_AHB_IMTX_AXI_FREQ_DFS_MODE(x)         (((x) & 0x3) << 12)
#define BIT_AP_IPA_AHB_IMTX_AXI_FREQ_DFS_SW(x)           (((x) & 0xF) << 8)
#define BIT_AP_IPA_AHB_IMTX_M9_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 4)
#define BIT_AP_IPA_AHB_IMTX_M8_AXI_FREQ_ALLOW(x)         (((x) & 0xF))

/* REG_AP_IPA_AHB_IMTX_AXI_FREQ_ALLOW1 */

#define BIT_AP_IPA_AHB_IMTX_M7_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 28)
#define BIT_AP_IPA_AHB_IMTX_M6_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 24)
#define BIT_AP_IPA_AHB_IMTX_M5_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 20)
#define BIT_AP_IPA_AHB_IMTX_M4_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 16)
#define BIT_AP_IPA_AHB_IMTX_M3_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 12)
#define BIT_AP_IPA_AHB_IMTX_M2_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 8)
#define BIT_AP_IPA_AHB_IMTX_M1_AXI_FREQ_ALLOW(x)         (((x) & 0xF) << 4)
#define BIT_AP_IPA_AHB_IMTX_M0_AXI_FREQ_ALLOW(x)         (((x) & 0xF))

/* REG_AP_IPA_AHB_IMTX_AXI_FREQ_LSLP_ALLOW0 */

#define BIT_AP_IPA_AHB_IMTX_AXI_FREQ_LSLP_DFS_MODE(x)    (((x) & 0x3) << 12)
#define BIT_AP_IPA_AHB_IMTX_AXI_FREQ_LSLP_DFS_SW(x)      (((x) & 0xF) << 8)
#define BIT_AP_IPA_AHB_IMTX_M9_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 4)
#define BIT_AP_IPA_AHB_IMTX_M8_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF))

/* REG_AP_IPA_AHB_IMTX_AXI_FREQ_LSLP_ALLOW1 */

#define BIT_AP_IPA_AHB_IMTX_M7_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 28)
#define BIT_AP_IPA_AHB_IMTX_M6_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 24)
#define BIT_AP_IPA_AHB_IMTX_M5_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 20)
#define BIT_AP_IPA_AHB_IMTX_M4_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 16)
#define BIT_AP_IPA_AHB_IMTX_M3_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 12)
#define BIT_AP_IPA_AHB_IMTX_M2_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 8)
#define BIT_AP_IPA_AHB_IMTX_M1_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF) << 4)
#define BIT_AP_IPA_AHB_IMTX_M0_AXI_FREQ_LSLP_ALLOW(x)    (((x) & 0xF))

/* REG_AP_IPA_AHB_AP_QOS0 */

#define BIT_AP_IPA_AHB_ARQOS_PCIE_MSTR(x)                (((x) & 0xF) << 28)
#define BIT_AP_IPA_AHB_AWQOS_PCIE_MSTR(x)                (((x) & 0xF) << 24)
#define BIT_AP_IPA_AHB_ARQOS_TFT(x)                      (((x) & 0xF) << 20)
#define BIT_AP_IPA_AHB_AWQOS_TFT(x)                      (((x) & 0xF) << 16)
#define BIT_AP_IPA_AHB_ARQOS_IPA(x)                      (((x) & 0xF) << 12)
#define BIT_AP_IPA_AHB_AWQOS_IPA(x)                      (((x) & 0xF) << 8)
#define BIT_AP_IPA_AHB_ARQOS_USB_PAM(x)                  (((x) & 0xF) << 4)
#define BIT_AP_IPA_AHB_AWQOS_USB_PAM(x)                  (((x) & 0xF))

/* REG_AP_IPA_AHB_AP_QOS1 */

#define BIT_AP_IPA_AHB_ARQOS_USB1(x)                     (((x) & 0xF) << 12)
#define BIT_AP_IPA_AHB_AWQOS_USB1(x)                     (((x) & 0xF) << 8)
#define BIT_AP_IPA_AHB_ARQOS_SDIO_SLV(x)                 (((x) & 0xF) << 4)
#define BIT_AP_IPA_AHB_AWQOS_SDIO_SLV(x)                 (((x) & 0xF))

/* REG_AP_IPA_AHB_AP_URGENCY */

#define BIT_AP_IPA_AHB_ARURGENCY_USB1(x)                 (((x) & 0x3) << 22)
#define BIT_AP_IPA_AHB_AWURGENCY_USB1(x)                 (((x) & 0x3) << 20)
#define BIT_AP_IPA_AHB_ARURGENCY_SDIO_SLV(x)             (((x) & 0x3) << 18)
#define BIT_AP_IPA_AHB_AWURGENCY_SDIO_SLV(x)             (((x) & 0x3) << 16)
#define BIT_AP_IPA_AHB_ARURGENCY_PCIE(x)                 (((x) & 0x3) << 14)
#define BIT_AP_IPA_AHB_AWURGENCY_PCIE(x)                 (((x) & 0x3) << 12)
#define BIT_AP_IPA_AHB_ARURGENCY_TFT(x)                  (((x) & 0x3) << 10)
#define BIT_AP_IPA_AHB_AWURGENCY_TFT(x)                  (((x) & 0x3) << 8)
#define BIT_AP_IPA_AHB_ARURGENCY_IPA(x)                  (((x) & 0x3) << 6)
#define BIT_AP_IPA_AHB_AWURGENCY_IPA(x)                  (((x) & 0x3) << 4)
#define BIT_AP_IPA_AHB_ARURGENCY_USB_PAM(x)              (((x) & 0x3) << 2)
#define BIT_AP_IPA_AHB_AWURGENCY_USB_PAM(x)              (((x) & 0x3))

/* REG_AP_IPA_AHB_AP_USER0 */

#define BIT_AP_IPA_AHB_ARUSER_PCIE_MSTR(x)               (((x) & 0xFF) << 24)
#define BIT_AP_IPA_AHB_AWUSER_PCIE_MSTR(x)               (((x) & 0xFF) << 16)
#define BIT_AP_IPA_AHB_ARUSER_SDIO_SLV(x)                (((x) & 0xFF) << 8)
#define BIT_AP_IPA_AHB_AWUSER_SDIO_SLV(x)                (((x) & 0xFF))

/* REG_AP_IPA_AHB_AP_USER1 */

#define BIT_AP_IPA_AHB_ARUSER_USB_PAM(x)                 (((x) & 0xFF) << 24)
#define BIT_AP_IPA_AHB_AWUSER_USB_PAM(x)                 (((x) & 0xFF) << 16)
#define BIT_AP_IPA_AHB_ARUSER_USB1(x)                    (((x) & 0xFF) << 8)
#define BIT_AP_IPA_AHB_AWUSER_USB1(x)                    (((x) & 0xFF))

/* REG_AP_IPA_AHB_AP_USER2 */

#define BIT_AP_IPA_AHB_ARUSER_IPA(x)                     (((x) & 0xFF) << 24)
#define BIT_AP_IPA_AHB_AWUSER_IPA(x)                     (((x) & 0xFF) << 16)
#define BIT_AP_IPA_AHB_ARUSER_TFT(x)                     (((x) & 0xFF) << 8)
#define BIT_AP_IPA_AHB_AWUSER_TFT(x)                     (((x) & 0xFF))

/* REG_AP_IPA_AHB_IMTX_CTRL */

#define BIT_AP_IPA_AHB_IMTX_BUSMON_ENABLE                BIT(0)

/* REG_AP_IPA_AHB_IPA_CTRL */

#define BIT_AP_IPA_AHB_IPA_DFS_VOTE_LSLP_EB              BIT(2)
#define BIT_AP_IPA_AHB_IPA_DFS_VOTE_EB                   BIT(1)
#define BIT_AP_IPA_AHB_IPA_DEBUG_EB                      BIT(0)

/* REG_AP_IPA_AHB_PAM_WIFI_CTRL */

#define BIT_AP_IPA_AHB_ARUSER_PAM_WIFI(x)                (((x) & 0xFF) << 24)
#define BIT_AP_IPA_AHB_AWUSER_PAM_WIFI(x)                (((x) & 0xFF) << 16)
#define BIT_AP_IPA_AHB_ARQOS_PAM_WIFI(x)                 (((x) & 0xF) << 10)
#define BIT_AP_IPA_AHB_AWQOS_PAM_WIFI(x)                 (((x) & 0xF) << 6)
#define BIT_AP_IPA_AHB_ARURGENCY_PAM_WIFI(x)             (((x) & 0x3) << 4)
#define BIT_AP_IPA_AHB_AWURGENCY_PAM_WIFI(x)             (((x) & 0x3) << 2)
#define BIT_AP_IPA_AHB_PAM_WIFI_SOFT_RST                 BIT(1)
#define BIT_AP_IPA_AHB_PAM_WIFI_EB                       BIT(0)

/* REG_AP_IPA_AHB_IMTX_M10_CTRL */

#define BIT_AP_IPA_AHB_IMTX_M10_AXI_FREQ_LSLP_ALLOW(x)   (((x) & 0xF) << 27)
#define BIT_AP_IPA_AHB_IMTX_M10_AXI_FREQ_ALLOW(x)        (((x) & 0xF) << 23)
#define BIT_AP_IPA_AHB_DOZE_IMTX_M10_LPC_BYPASS          BIT(22)
#define BIT_AP_IPA_AHB_IMTX_M10_FRC_DOZE                 BIT(21)
#define BIT_AP_IPA_AHB_PUB_DSLP_IMTX_M10_LPC_BYPASS      BIT(20)
#define BIT_AP_IPA_AHB_IMTX_M10_FRC_PUB_DSLP             BIT(19)
#define BIT_AP_IPA_AHB_LSLP_IMTX_M10_LPC_BYPASS          BIT(18)
#define BIT_AP_IPA_AHB_IMTX_M10_FRC_LSLP                 BIT(17)
#define BIT_AP_IPA_AHB_IMTX_M10_LP_EB                    BIT(16)
#define BIT_AP_IPA_AHB_IMTX_M10_LP_NUM(x)                (((x) & 0xFFFF))

/* REG_AP_IPA_AHB_PCIE_LP_CTRL */

#define BIT_AP_IPA_AHB_CGM_BUSY_LPC_APB_MASK             BIT(7)
#define BIT_AP_IPA_AHB_CGM_BUSY_LPC_SAXI_MASK            BIT(6)
#define BIT_AP_IPA_AHB_PCIE_L12_AXI_CGM_MASK             BIT(5)
#define BIT_AP_IPA_AHB_PCIE_L2_AXI_CGM_MASK              BIT(4)
#define BIT_AP_IPA_AHB_PERST_AUX_CGM_MASK                BIT(3)
#define BIT_AP_IPA_AHB_PERST_SLP_MASK                    BIT(2)
#define BIT_AP_IPA_AHB_PCIE_L12_SLP_ENA                  BIT(1)
#define BIT_AP_IPA_AHB_PCIE_L2_SLP_ENA                   BIT(0)

/* REG_AP_IPA_AHB_IMTX_PU_NUM0 */

#define BIT_AP_IPA_AHB_IMTX_M3_PU_NUM(x)                 (((x) & 0xFF) << 24)
#define BIT_AP_IPA_AHB_IMTX_M2_PU_NUM(x)                 (((x) & 0xFF) << 16)
#define BIT_AP_IPA_AHB_IMTX_M1_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_IPA_AHB_IMTX_M0_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_IPA_AHB_IMTX_PU_NUM1 */

#define BIT_AP_IPA_AHB_IMTX_M7_PU_NUM(x)                 (((x) & 0xFF) << 24)
#define BIT_AP_IPA_AHB_IMTX_M6_PU_NUM(x)                 (((x) & 0xFF) << 16)
#define BIT_AP_IPA_AHB_IMTX_M5_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_IPA_AHB_IMTX_M4_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_IPA_AHB_IMTX_PU_NUM2 */

#define BIT_AP_IPA_AHB_IMTX_MAIN_PU_NUM(x)               (((x) & 0xFF) << 24)
#define BIT_AP_IPA_AHB_IMTX_M10_PU_NUM(x)                (((x) & 0xFF) << 16)
#define BIT_AP_IPA_AHB_IMTX_M9_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_IPA_AHB_IMTX_M8_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_IPA_AHB_IMTX_PU_NUM3 */

#define BIT_AP_IPA_AHB_IMTX_S3_PU_NUM(x)                 (((x) & 0xFF) << 24)
#define BIT_AP_IPA_AHB_IMTX_S2_PU_NUM(x)                 (((x) & 0xFF) << 16)
#define BIT_AP_IPA_AHB_IMTX_S1_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_IPA_AHB_IMTX_S0_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_IPA_AHB_IMTX_PU_NUM4 */

#define BIT_AP_IPA_AHB_IMTX_S7_PU_NUM(x)                 (((x) & 0xFF) << 24)
#define BIT_AP_IPA_AHB_IMTX_S6_PU_NUM(x)                 (((x) & 0xFF) << 16)
#define BIT_AP_IPA_AHB_IMTX_S5_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_IPA_AHB_IMTX_S4_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_IPA_AHB_IMTX_PU_NUM5 */

#define BIT_AP_IPA_AHB_IMTX_S9_PU_NUM(x)                 (((x) & 0xFF) << 8)
#define BIT_AP_IPA_AHB_IMTX_S8_PU_NUM(x)                 (((x) & 0xFF))

/* REG_AP_IPA_AHB_PAM_WIFI_PCLK_DFS_CTRL */

#define BIT_AP_IPA_AHB_PAM_WIFI_PCLK_AUTO_SLOW_EN        BIT(4)
#define BIT_AP_IPA_AHB_PAM_WIFI_PCLK_AUTO_SLOW_SEL(x)    (((x) & 0x7) << 1)
#define BIT_AP_IPA_AHB_PAM_WIFI_PCLK_AUTO_GATE_EB        BIT(0)

/* REG_AP_IPA_AHB_PCIE_CTRL */

#define BIT_AP_IPA_AHB_PCIE_SNPS_AXI_AUTO_GATE           BIT(12)
#define BIT_AP_IPA_AHB_PCIE_DEVICE_TYPE(x)               (((x) & 0xF) << 8)
#define BIT_AP_IPA_AHB_AP_CTL_PCIE(x)                    (((x) & 0xFF))

/* REG_AP_IPA_AHB_SYS_ACCESS_EN */

#define BIT_AP_IPA_AHB_NR_ACCESS_AP_EN                   BIT(3)
#define BIT_AP_IPA_AHB_PS_ACCESS_AP_EN                   BIT(2)
#define BIT_AP_IPA_AHB_NR_CP_ACCESS_EN                   BIT(1)
#define BIT_AP_IPA_AHB_PS_CP_ACCESS_EN                   BIT(0)

/* REG_AP_IPA_AHB_CGM_GATE_EN */

#define BIT_AP_IPA_AHB_CGM_CLK_CP1_AXI_AUTO_GATE_EN      BIT(1)
#define BIT_AP_IPA_AHB_CGM_CLK_CP0_AXI_AUTO_GATE_EN      BIT(0)

/* REG_AP_IPA_AHB_IP_BUSY_GATE_EN */

#define BIT_AP_IPA_AHB_USE_SDIO_SLV_BUSY                 BIT(0)

/* REG_AP_IPA_AHB_SDSLV_CTRL */

#define BIT_AP_IPA_AHB_SDSLV_DEBUG_EB                    BIT(0)

/* REG_AP_IPA_AHB_PCIE_SW_MSI_INT */

#define BIT_AP_IPA_AHB_PCIE_SW_MSI_INT(x)                (((x) & 0xFFFFFFFF))

/* REG_AP_IPA_AHB_RESERVE0 */

#define BIT_AP_IPA_AHB_RESERVE0(x)                       (((x) & 0xFFFFFFFF))

/* REG_AP_IPA_AHB_RESERVE1 */

#define BIT_AP_IPA_AHB_RESERVE1(x)                       (((x) & 0xFFFFFFFF))


#endif /* AP_IPA_AHB_H */



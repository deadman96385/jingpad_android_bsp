/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:54:28
 *
 */


#ifndef AP_CLK_CORE_H
#define AP_CLK_CORE_H

#define CTL_BASE_AP_CLK_CORE 0x20200000


#define REG_AP_CLK_CORE_CGM_AP_APB_CFG             ( CTL_BASE_AP_CLK_CORE + 0x0020 )
#define REG_AP_CLK_CORE_CGM_ICU_CFG                ( CTL_BASE_AP_CLK_CORE + 0x0024 )
#define REG_AP_CLK_CORE_CGM_UART0_CFG              ( CTL_BASE_AP_CLK_CORE + 0x0028 )
#define REG_AP_CLK_CORE_CGM_UART1_CFG              ( CTL_BASE_AP_CLK_CORE + 0x002C )
#define REG_AP_CLK_CORE_CGM_UART2_CFG              ( CTL_BASE_AP_CLK_CORE + 0x0030 )
#define REG_AP_CLK_CORE_CGM_I2C0_CFG               ( CTL_BASE_AP_CLK_CORE + 0x0034 )
#define REG_AP_CLK_CORE_CGM_I2C1_CFG               ( CTL_BASE_AP_CLK_CORE + 0x0038 )
#define REG_AP_CLK_CORE_CGM_I2C2_CFG               ( CTL_BASE_AP_CLK_CORE + 0x003C )
#define REG_AP_CLK_CORE_CGM_I2C3_CFG               ( CTL_BASE_AP_CLK_CORE + 0x0040 )
#define REG_AP_CLK_CORE_CGM_I2C4_CFG               ( CTL_BASE_AP_CLK_CORE + 0x0044 )
#define REG_AP_CLK_CORE_CGM_SPI0_CFG               ( CTL_BASE_AP_CLK_CORE + 0x0048 )
#define REG_AP_CLK_CORE_CGM_SPI1_CFG               ( CTL_BASE_AP_CLK_CORE + 0x004C )
#define REG_AP_CLK_CORE_CGM_SPI2_CFG               ( CTL_BASE_AP_CLK_CORE + 0x0050 )
#define REG_AP_CLK_CORE_CGM_SPI3_CFG               ( CTL_BASE_AP_CLK_CORE + 0x0054 )
#define REG_AP_CLK_CORE_CGM_IIS0_CFG               ( CTL_BASE_AP_CLK_CORE + 0x0058 )
#define REG_AP_CLK_CORE_CGM_IIS1_CFG               ( CTL_BASE_AP_CLK_CORE + 0x005C )
#define REG_AP_CLK_CORE_CGM_IIS2_CFG               ( CTL_BASE_AP_CLK_CORE + 0x0060 )
#define REG_AP_CLK_CORE_CGM_SIM_CFG                ( CTL_BASE_AP_CLK_CORE + 0x0064 )
#define REG_AP_CLK_CORE_CGM_CE_CFG                 ( CTL_BASE_AP_CLK_CORE + 0x0068 )
#define REG_AP_CLK_CORE_CGM_AP_SIM_32K_CFG         ( CTL_BASE_AP_CLK_CORE + 0x006C )
#define REG_AP_CLK_CORE_CGM_SDIO0_2X_CFG           ( CTL_BASE_AP_CLK_CORE + 0x0070 )
#define REG_AP_CLK_CORE_CGM_SDIO0_1X_CFG           ( CTL_BASE_AP_CLK_CORE + 0x0074 )
#define REG_AP_CLK_CORE_CGM_SDIO1_2X_CFG           ( CTL_BASE_AP_CLK_CORE + 0x0078 )
#define REG_AP_CLK_CORE_CGM_SDIO1_1X_CFG           ( CTL_BASE_AP_CLK_CORE + 0x007C )
#define REG_AP_CLK_CORE_CGM_EMMC_2X_CFG            ( CTL_BASE_AP_CLK_CORE + 0x0080 )
#define REG_AP_CLK_CORE_CGM_EMMC_1X_CFG            ( CTL_BASE_AP_CLK_CORE + 0x0084 )
#define REG_AP_CLK_CORE_CGM_UFS_TX_CFG             ( CTL_BASE_AP_CLK_CORE + 0x0088 )
#define REG_AP_CLK_CORE_CGM_UFS_TX_DIV2_CFG        ( CTL_BASE_AP_CLK_CORE + 0x008C )
#define REG_AP_CLK_CORE_CGM_UFS_RX_CFG             ( CTL_BASE_AP_CLK_CORE + 0x0090 )
#define REG_AP_CLK_CORE_CGM_UFS_CFG_CFG            ( CTL_BASE_AP_CLK_CORE + 0x0094 )
#define REG_AP_CLK_CORE_CGM_UFS_XTAL_CFG           ( CTL_BASE_AP_CLK_CORE + 0x0098 )
#define REG_AP_CLK_CORE_CGM_VSP_CFG                ( CTL_BASE_AP_CLK_CORE + 0x009C )
#define REG_AP_CLK_CORE_CGM_DISPC0_CFG             ( CTL_BASE_AP_CLK_CORE + 0x00A0 )
#define REG_AP_CLK_CORE_CGM_DISPC0_DPI_CFG         ( CTL_BASE_AP_CLK_CORE + 0x00A4 )
#define REG_AP_CLK_CORE_CGM_DSI_RXESC_CFG          ( CTL_BASE_AP_CLK_CORE + 0x00A8 )
#define REG_AP_CLK_CORE_CGM_DSI_LANEBYTE_CFG       ( CTL_BASE_AP_CLK_CORE + 0x00AC )
#define REG_AP_CLK_CORE_CGM_VDSP_CFG               ( CTL_BASE_AP_CLK_CORE + 0x00B0 )
#define REG_AP_CLK_CORE_CGM_VDSP_EDAP_CFG          ( CTL_BASE_AP_CLK_CORE + 0x00B4 )
#define REG_AP_CLK_CORE_CGM_VDSP_M0_CFG            ( CTL_BASE_AP_CLK_CORE + 0x00B8 )
#define REG_AP_CLK_CORE_CGM_DPHY_REF_CFG           ( CTL_BASE_AP_CLK_CORE + 0x00BC )
#define REG_AP_CLK_CORE_CGM_DPHY_CFG_CFG           ( CTL_BASE_AP_CLK_CORE + 0x00C0 )
#define REG_AP_CLK_CORE_CGM_DSI_PHY_SCAN_ONLY_CFG  ( CTL_BASE_AP_CLK_CORE + 0x00C4 )

/* REG_AP_CLK_CORE_CGM_AP_APB_CFG */

#define BIT_AP_CLK_CORE_CGM_AP_APB_CFG_CGM_AP_APB_SEL(x)                     (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_ICU_CFG */

#define BIT_AP_CLK_CORE_CGM_ICU_CFG_CGM_ICU_SEL(x)                           (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_UART0_CFG */

#define BIT_AP_CLK_CORE_CGM_UART0_CFG_CGM_UART0_DIV(x)                       (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_UART0_CFG_CGM_UART0_SEL(x)                       (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_UART1_CFG */

#define BIT_AP_CLK_CORE_CGM_UART1_CFG_CGM_UART1_DIV(x)                       (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_UART1_CFG_CGM_UART1_SEL(x)                       (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_UART2_CFG */

#define BIT_AP_CLK_CORE_CGM_UART2_CFG_CGM_UART2_DIV(x)                       (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_UART2_CFG_CGM_UART2_SEL(x)                       (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C0_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C0_CFG_CGM_I2C0_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C0_CFG_CGM_I2C0_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C1_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C1_CFG_CGM_I2C1_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C1_CFG_CGM_I2C1_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C2_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C2_CFG_CGM_I2C2_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C2_CFG_CGM_I2C2_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C3_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C3_CFG_CGM_I2C3_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C3_CFG_CGM_I2C3_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_I2C4_CFG */

#define BIT_AP_CLK_CORE_CGM_I2C4_CFG_CGM_I2C4_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_I2C4_CFG_CGM_I2C4_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SPI0_CFG */

#define BIT_AP_CLK_CORE_CGM_SPI0_CFG_CGM_SPI0_PAD_SEL                        BIT(16)
#define BIT_AP_CLK_CORE_CGM_SPI0_CFG_CGM_SPI0_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SPI0_CFG_CGM_SPI0_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SPI1_CFG */

#define BIT_AP_CLK_CORE_CGM_SPI1_CFG_CGM_SPI1_PAD_SEL                        BIT(16)
#define BIT_AP_CLK_CORE_CGM_SPI1_CFG_CGM_SPI1_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SPI1_CFG_CGM_SPI1_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SPI2_CFG */

#define BIT_AP_CLK_CORE_CGM_SPI2_CFG_CGM_SPI2_PAD_SEL                        BIT(16)
#define BIT_AP_CLK_CORE_CGM_SPI2_CFG_CGM_SPI2_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SPI2_CFG_CGM_SPI2_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SPI3_CFG */

#define BIT_AP_CLK_CORE_CGM_SPI3_CFG_CGM_SPI3_PAD_SEL                        BIT(16)
#define BIT_AP_CLK_CORE_CGM_SPI3_CFG_CGM_SPI3_DIV(x)                         (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SPI3_CFG_CGM_SPI3_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_IIS0_CFG */

#define BIT_AP_CLK_CORE_CGM_IIS0_CFG_CGM_IIS0_DIV(x)                         (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CORE_CGM_IIS0_CFG_CGM_IIS0_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_IIS1_CFG */

#define BIT_AP_CLK_CORE_CGM_IIS1_CFG_CGM_IIS1_DIV(x)                         (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CORE_CGM_IIS1_CFG_CGM_IIS1_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_IIS2_CFG */

#define BIT_AP_CLK_CORE_CGM_IIS2_CFG_CGM_IIS2_DIV(x)                         (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CORE_CGM_IIS2_CFG_CGM_IIS2_SEL(x)                         (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_SIM_CFG */

#define BIT_AP_CLK_CORE_CGM_SIM_CFG_CGM_SIM_DIV(x)                           (((x) & 0x7) << 8)
#define BIT_AP_CLK_CORE_CGM_SIM_CFG_CGM_SIM_SEL(x)                           (((x) & 0x7))

/* REG_AP_CLK_CORE_CGM_CE_CFG */

#define BIT_AP_CLK_CORE_CGM_CE_CFG_CGM_CE_SEL(x)                             (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_AP_SIM_32K_CFG */

#define BIT_AP_CLK_CORE_CGM_AP_SIM_32K_CFG_CGM_AP_SIM_32K_SEL                BIT(0)

/* REG_AP_CLK_CORE_CGM_SDIO0_2X_CFG */

#define BIT_AP_CLK_CORE_CGM_SDIO0_2X_CFG_CGM_SDIO0_2X_SEL(x)                 (((x) & 0x7))

/* REG_AP_CLK_CORE_CGM_SDIO0_1X_CFG */


/* REG_AP_CLK_CORE_CGM_SDIO1_2X_CFG */

#define BIT_AP_CLK_CORE_CGM_SDIO1_2X_CFG_CGM_SDIO1_2X_SEL(x)                 (((x) & 0x7))

/* REG_AP_CLK_CORE_CGM_SDIO1_1X_CFG */


/* REG_AP_CLK_CORE_CGM_EMMC_2X_CFG */

#define BIT_AP_CLK_CORE_CGM_EMMC_2X_CFG_CGM_EMMC_2X_SEL(x)                   (((x) & 0x7))

/* REG_AP_CLK_CORE_CGM_EMMC_1X_CFG */


/* REG_AP_CLK_CORE_CGM_UFS_TX_CFG */

#define BIT_AP_CLK_CORE_CGM_UFS_TX_CFG_CGM_UFS_TX_SEL(x)                     (((x) & 0x7))

/* REG_AP_CLK_CORE_CGM_UFS_TX_DIV2_CFG */

#define BIT_AP_CLK_CORE_CGM_UFS_TX_DIV2_CFG_CGM_UFS_TX_DIV2_DIV              BIT(8)

/* REG_AP_CLK_CORE_CGM_UFS_RX_CFG */

#define BIT_AP_CLK_CORE_CGM_UFS_RX_CFG_CGM_UFS_RX_SEL(x)                     (((x) & 0x7))

/* REG_AP_CLK_CORE_CGM_UFS_CFG_CFG */

#define BIT_AP_CLK_CORE_CGM_UFS_CFG_CFG_CGM_UFS_CFG_PAD_SEL                  BIT(16)
#define BIT_AP_CLK_CORE_CGM_UFS_CFG_CFG_CGM_UFS_CFG_DIV(x)                   (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CORE_CGM_UFS_CFG_CFG_CGM_UFS_CFG_SEL                      BIT(0)

/* REG_AP_CLK_CORE_CGM_UFS_XTAL_CFG */

#define BIT_AP_CLK_CORE_CGM_UFS_XTAL_CFG_CGM_UFS_XTAL_SEL                    BIT(0)

/* REG_AP_CLK_CORE_CGM_VSP_CFG */

#define BIT_AP_CLK_CORE_CGM_VSP_CFG_CGM_VSP_SEL(x)                           (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_DISPC0_CFG */

#define BIT_AP_CLK_CORE_CGM_DISPC0_CFG_CGM_DISPC0_SEL(x)                     (((x) & 0x7))

/* REG_AP_CLK_CORE_CGM_DISPC0_DPI_CFG */

#define BIT_AP_CLK_CORE_CGM_DISPC0_DPI_CFG_CGM_DISPC0_DPI_DIV(x)             (((x) & 0xF) << 8)
#define BIT_AP_CLK_CORE_CGM_DISPC0_DPI_CFG_CGM_DISPC0_DPI_SEL(x)             (((x) & 0x3))

/* REG_AP_CLK_CORE_CGM_DSI_RXESC_CFG */

#define BIT_AP_CLK_CORE_CGM_DSI_RXESC_CFG_CGM_DSI_RXESC_PAD_SEL              BIT(16)

/* REG_AP_CLK_CORE_CGM_DSI_LANEBYTE_CFG */

#define BIT_AP_CLK_CORE_CGM_DSI_LANEBYTE_CFG_CGM_DSI_LANEBYTE_PAD_SEL        BIT(16)

/* REG_AP_CLK_CORE_CGM_VDSP_CFG */

#define BIT_AP_CLK_CORE_CGM_VDSP_CFG_CGM_VDSP_SEL(x)                         (((x) & 0x7))

/* REG_AP_CLK_CORE_CGM_VDSP_EDAP_CFG */

#define BIT_AP_CLK_CORE_CGM_VDSP_EDAP_CFG_CGM_VDSP_EDAP_DIV(x)               (((x) & 0x3) << 8)

/* REG_AP_CLK_CORE_CGM_VDSP_M0_CFG */

#define BIT_AP_CLK_CORE_CGM_VDSP_M0_CFG_CGM_VDSP_M0_DIV(x)                   (((x) & 0x3) << 8)

/* REG_AP_CLK_CORE_CGM_DPHY_REF_CFG */

#define BIT_AP_CLK_CORE_CGM_DPHY_REF_CFG_CGM_DPHY_REF_SEL                    BIT(0)

/* REG_AP_CLK_CORE_CGM_DPHY_CFG_CFG */

#define BIT_AP_CLK_CORE_CGM_DPHY_CFG_CFG_CGM_DPHY_CFG_SEL                    BIT(0)

/* REG_AP_CLK_CORE_CGM_DSI_PHY_SCAN_ONLY_CFG */

#define BIT_AP_CLK_CORE_CGM_DSI_PHY_SCAN_ONLY_CFG_CGM_DSI_PHY_SCAN_ONLY_SEL  BIT(0)


#endif /* AP_CLK_CORE_H */



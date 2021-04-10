/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _AP_CLK_REG_H
#define _AP_CLK_REG_H

#define CTL_BASE_AP_CLK SPRD_APCKG_PHYS


#define REG_AP_CLK_CGM_AP_AXI_CFG           ( CTL_BASE_AP_CLK + 0x0020 )
#define REG_AP_CLK_CGM_AP_AHB_CFG           ( CTL_BASE_AP_CLK + 0x0024 )
#define REG_AP_CLK_CGM_AP_APB_CFG           ( CTL_BASE_AP_CLK + 0x0028 )
#define REG_AP_CLK_CGM_GSP_CFG              ( CTL_BASE_AP_CLK + 0x002C )
#define REG_AP_CLK_CGM_DISPC0_CFG           ( CTL_BASE_AP_CLK + 0x0030 )
#define REG_AP_CLK_CGM_DISPC0_DPI_CFG       ( CTL_BASE_AP_CLK + 0x0034 )
#define REG_AP_CLK_CGM_DSI_RXESC_CFG        ( CTL_BASE_AP_CLK + 0x0038 )
#define REG_AP_CLK_CGM_DSI_LANEBYTE_CFG     ( CTL_BASE_AP_CLK + 0x003C )
#define REG_AP_CLK_CGM_DPHY_REF_CFG         ( CTL_BASE_AP_CLK + 0x0040 )
#define REG_AP_CLK_CGM_DPHY_CFG_CFG         ( CTL_BASE_AP_CLK + 0x0044 )
#define REG_AP_CLK_CGM_OTG_REF_CFG          ( CTL_BASE_AP_CLK + 0x0048 )
#define REG_AP_CLK_CGM_OTG_UTMI_CFG         ( CTL_BASE_AP_CLK + 0x004C )
#define REG_AP_CLK_CGM_UART0_CFG            ( CTL_BASE_AP_CLK + 0x0050 )
#define REG_AP_CLK_CGM_UART1_CFG            ( CTL_BASE_AP_CLK + 0x0054 )
#define REG_AP_CLK_CGM_UART2_CFG            ( CTL_BASE_AP_CLK + 0x0058 )
#define REG_AP_CLK_CGM_UART3_CFG            ( CTL_BASE_AP_CLK + 0x005C )
#define REG_AP_CLK_CGM_UART4_CFG            ( CTL_BASE_AP_CLK + 0x0060 )
#define REG_AP_CLK_CGM_I2C0_CFG             ( CTL_BASE_AP_CLK + 0x0064 )
#define REG_AP_CLK_CGM_I2C1_CFG             ( CTL_BASE_AP_CLK + 0x0068 )
#define REG_AP_CLK_CGM_I2C2_CFG             ( CTL_BASE_AP_CLK + 0x006C )
#define REG_AP_CLK_CGM_I2C3_CFG             ( CTL_BASE_AP_CLK + 0x0070 )
#define REG_AP_CLK_CGM_I2C4_CFG             ( CTL_BASE_AP_CLK + 0x0074 )
#define REG_AP_CLK_CGM_SPI0_CFG             ( CTL_BASE_AP_CLK + 0x0078 )
#define REG_AP_CLK_CGM_SPI2_CFG             ( CTL_BASE_AP_CLK + 0x007C )
#define REG_AP_CLK_CGM_IIS0_CFG             ( CTL_BASE_AP_CLK + 0x0080 )
#define REG_AP_CLK_CGM_IIS1_CFG             ( CTL_BASE_AP_CLK + 0x0084 )
#define REG_AP_CLK_CGM_IIS2_CFG             ( CTL_BASE_AP_CLK + 0x0088 )
#define REG_AP_CLK_CGM_IIS3_CFG             ( CTL_BASE_AP_CLK + 0x008C )
#define REG_AP_CLK_CGM_CE_SEC_EFUSE_CFG     ( CTL_BASE_AP_CLK + 0x0090 )
#define REG_AP_CLK_CGM_CE_PUB_CFG           ( CTL_BASE_AP_CLK + 0x0094 )
#define REG_AP_CLK_CGM_CE_SEC_CFG           ( CTL_BASE_AP_CLK + 0x0098 )
#define REG_AP_CLK_CGM_AP_EMMC_32K_CFG      ( CTL_BASE_AP_CLK + 0x009C )
#define REG_AP_CLK_CGM_AP_SDIO0_32K_CFG     ( CTL_BASE_AP_CLK + 0x00A0 )
#define REG_AP_CLK_CGM_AP_SDIO1_32K_CFG     ( CTL_BASE_AP_CLK + 0x00A4 )
#define REG_AP_CLK_CGM_AP_SDIO2_32K_CFG     ( CTL_BASE_AP_CLK + 0x00A8 )
#define REG_AP_CLK_CGM_AP_SIM_32K_CFG       ( CTL_BASE_AP_CLK + 0x00AC )
#define REG_AP_CLK_CGM_AXI_AP_EMC_CFG       ( CTL_BASE_AP_CLK + 0x00B0 )
#define REG_AP_CLK_CGM_AXI_DISPC_EMC_CFG    ( CTL_BASE_AP_CLK + 0x00B4 )
#define REG_AP_CLK_CGM_AXI_GSP_CA7_EMC_CFG  ( CTL_BASE_AP_CLK + 0x00B8 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_AXI_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_AXI_CFG_CGM_AP_AXI_SEL(x)                           (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_AHB_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_AHB_CFG_CGM_AP_AHB_SEL(x)                           (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_APB_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_APB_CFG_CGM_AP_APB_SEL(x)                           (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_GSP_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_GSP_CFG_CGM_GSP_SEL(x)                                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_DISPC0_CFG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_DISPC0_CFG_CGM_DISPC0_SEL(x)                           (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_DISPC0_DPI_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_DISPC0_DPI_CFG_CGM_DISPC0_DPI_DIV(x)                   (((x) & 0xF) << 8)
#define BIT_AP_CLK_CGM_DISPC0_DPI_CFG_CGM_DISPC0_DPI_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_DSI_RXESC_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_DSI_RXESC_CFG_CGM_DSI_RXESC_PAD_SEL                    BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_DSI_LANEBYTE_CFG
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_DSI_LANEBYTE_CFG_CGM_DSI_LANEBYTE_PAD_SEL              BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_DPHY_REF_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_DPHY_REF_CFG_CGM_DPHY_REF_SEL                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_DPHY_CFG_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_DPHY_CFG_CFG_CGM_DPHY_CFG_SEL                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_OTG_REF_CFG
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_OTG_REF_CFG_CGM_OTG_REF_SEL                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_OTG_UTMI_CFG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_OTG_UTMI_CFG_CGM_OTG_UTMI_PAD_SEL                      BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART0_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART0_CFG_CGM_UART0_DIV(x)                             (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART0_CFG_CGM_UART0_SEL(x)                             (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART1_CFG
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART1_CFG_CGM_UART1_DIV(x)                             (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART1_CFG_CGM_UART1_SEL(x)                             (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART2_CFG
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART2_CFG_CGM_UART2_DIV(x)                             (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART2_CFG_CGM_UART2_SEL(x)                             (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART3_CFG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART3_CFG_CGM_UART3_DIV(x)                             (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART3_CFG_CGM_UART3_SEL(x)                             (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART4_CFG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART4_CFG_CGM_UART4_DIV(x)                             (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART4_CFG_CGM_UART4_SEL(x)                             (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C0_CFG
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C0_CFG_CGM_I2C0_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C0_CFG_CGM_I2C0_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C1_CFG
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C1_CFG_CGM_I2C1_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C1_CFG_CGM_I2C1_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C2_CFG
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C2_CFG_CGM_I2C2_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C2_CFG_CGM_I2C2_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C3_CFG
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C3_CFG_CGM_I2C3_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C3_CFG_CGM_I2C3_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C4_CFG
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C4_CFG_CGM_I2C4_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C4_CFG_CGM_I2C4_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_SPI0_CFG
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_SPI0_CFG_CGM_SPI0_PAD_SEL                              BIT(16)
#define BIT_AP_CLK_CGM_SPI0_CFG_CGM_SPI0_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_SPI0_CFG_CGM_SPI0_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_SPI2_CFG
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_SPI2_CFG_CGM_SPI2_PAD_SEL                              BIT(16)
#define BIT_AP_CLK_CGM_SPI2_CFG_CGM_SPI2_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_SPI2_CFG_CGM_SPI2_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_IIS0_CFG
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_IIS0_CFG_CGM_IIS0_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_IIS0_CFG_CGM_IIS0_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_IIS1_CFG
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_IIS1_CFG_CGM_IIS1_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_IIS1_CFG_CGM_IIS1_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_IIS2_CFG
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_IIS2_CFG_CGM_IIS2_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_IIS2_CFG_CGM_IIS2_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_IIS3_CFG
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_IIS3_CFG_CGM_IIS3_DIV(x)                               (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_IIS3_CFG_CGM_IIS3_SEL(x)                               (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_CE_SEC_EFUSE_CFG
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_CE_SEC_EFUSE_CFG_CGM_CE_SEC_EFUSE_SEL                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_CE_PUB_CFG
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_CE_PUB_CFG_CGM_CE_PUB_SEL(x)                           (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_CE_SEC_CFG
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_CE_SEC_CFG_CGM_CE_SEC_SEL(x)                           (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_EMMC_32K_CFG
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_EMMC_32K_CFG_CGM_AP_EMMC_32K_SEL                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_SDIO0_32K_CFG
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_SDIO0_32K_CFG_CGM_AP_SDIO0_32K_SEL                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_SDIO1_32K_CFG
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_SDIO1_32K_CFG_CGM_AP_SDIO1_32K_SEL                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_SDIO2_32K_CFG
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_SDIO2_32K_CFG_CGM_AP_SDIO2_32K_SEL                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_SIM_32K_CFG
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_SIM_32K_CFG_CGM_AP_SIM_32K_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AXI_AP_EMC_CFG
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AXI_DISPC_EMC_CFG
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AXI_GSP_CA7_EMC_CFG
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

/* referenced by sprd_ce_r3p0.c */
#define REG_AP_CLK_CE_SEC_CFG	REG_AP_CLK_CGM_CE_SEC_CFG

#endif // _AP_CLK_REG_H

/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _AP_CLK_CORE_REG_H
#define _AP_CLK_CORE_REG_H

#define CTL_BASE_AP_CLK_CORE 0x21500000


#define REG_AP_CLK_AP_AXI_CFG           ( CTL_BASE_AP_CLK_CORE + 0x0020 )
#define REG_AP_CLK_AP_AHB_CFG           ( CTL_BASE_AP_CLK_CORE + 0x0024 )
#define REG_AP_CLK_AP_APB_CFG           ( CTL_BASE_AP_CLK_CORE + 0x0028 )
#define REG_AP_CLK_GSP_CFG              ( CTL_BASE_AP_CLK_CORE + 0x002C )
#define REG_AP_CLK_DISPC0_CFG           ( CTL_BASE_AP_CLK_CORE + 0x0030 )
#define REG_AP_CLK_DISPC0_DPI_CFG       ( CTL_BASE_AP_CLK_CORE + 0x0034 )
#define REG_AP_CLK_DSI_RXESC_CFG        ( CTL_BASE_AP_CLK_CORE + 0x0038 )
#define REG_AP_CLK_DSI_LANEBYTE_CFG     ( CTL_BASE_AP_CLK_CORE + 0x003C )
#define REG_AP_CLK_DPHY_REF_CFG         ( CTL_BASE_AP_CLK_CORE + 0x0040 )
#define REG_AP_CLK_DPHY_CFG_CFG         ( CTL_BASE_AP_CLK_CORE + 0x0044 )
#define REG_AP_CLK_OTG_REF_CFG          ( CTL_BASE_AP_CLK_CORE + 0x0048 )
#define REG_AP_CLK_OTG_UTMI_CFG         ( CTL_BASE_AP_CLK_CORE + 0x004C )
#define REG_AP_CLK_UART0_CFG            ( CTL_BASE_AP_CLK_CORE + 0x0050 )
#define REG_AP_CLK_UART1_CFG            ( CTL_BASE_AP_CLK_CORE + 0x0054 )
#define REG_AP_CLK_I2C0_CFG             ( CTL_BASE_AP_CLK_CORE + 0x0058 )
#define REG_AP_CLK_I2C1_CFG             ( CTL_BASE_AP_CLK_CORE + 0x005C )
#define REG_AP_CLK_I2C2_CFG             ( CTL_BASE_AP_CLK_CORE + 0x0060 )
#define REG_AP_CLK_SPI0_CFG             ( CTL_BASE_AP_CLK_CORE + 0x0064 )
#define REG_AP_CLK_IIS0_CFG             ( CTL_BASE_AP_CLK_CORE + 0x0068 )
#define REG_AP_CLK_CE_CFG               ( CTL_BASE_AP_CLK_CORE + 0x006C )
#define REG_AP_CLK_AP_EMMC_32K_CFG      ( CTL_BASE_AP_CLK_CORE + 0x0070 )
#define REG_AP_CLK_AP_SDIO0_32K_CFG     ( CTL_BASE_AP_CLK_CORE + 0x0074 )
#define REG_AP_CLK_NANDC_ECC_CFG        ( CTL_BASE_AP_CLK_CORE + 0x0078 )
#define REG_AP_CLK_AP_SIM_32K_CFG       ( CTL_BASE_AP_CLK_CORE + 0x007C )
#define REG_AP_CLK_AXI_AP_EMC_CFG       ( CTL_BASE_AP_CLK_CORE + 0x0080 )
#define REG_AP_CLK_AXI_DISPC_EMC_CFG    ( CTL_BASE_AP_CLK_CORE + 0x0084 )
#define REG_AP_CLK_AXI_GSP_CA7_EMC_CFG  ( CTL_BASE_AP_CLK_CORE + 0x0088 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_AP_AXI_CFG
// Register Offset : 0x0020
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_AP_AXI_CFG_AP_AXI_SEL(x)                                (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_AP_AHB_CFG
// Register Offset : 0x0024
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_AP_AHB_CFG_AP_AHB_SEL(x)                                (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_AP_APB_CFG
// Register Offset : 0x0028
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_AP_APB_CFG_AP_APB_SEL(x)                                (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_GSP_CFG
// Register Offset : 0x002C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_GSP_CFG_GSP_SEL(x)                                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_DISPC0_CFG
// Register Offset : 0x0030
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_DISPC0_CFG_DISPC0_SEL(x)                                (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_DISPC0_DPI_CFG
// Register Offset : 0x0034
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_DISPC0_DPI_CFG_DISPC0_DPI_DIV(x)                        (((x) & 0xF) << 8)
#define BIT_AP_CLK_DISPC0_DPI_CFG_DISPC0_DPI_SEL(x)                        (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_DSI_RXESC_CFG
// Register Offset : 0x0038
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_DSI_RXESC_CFG_DSI_RXESC_PAD_SEL                         BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_DSI_LANEBYTE_CFG
// Register Offset : 0x003C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_DSI_LANEBYTE_CFG_DSI_LANEBYTE_PAD_SEL                   BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_DPHY_REF_CFG
// Register Offset : 0x0040
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_DPHY_REF_CFG_DPHY_REF_SEL                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_DPHY_CFG_CFG
// Register Offset : 0x0044
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_DPHY_CFG_CFG_DPHY_CFG_SEL                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_OTG_REF_CFG
// Register Offset : 0x0048
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_OTG_REF_CFG_OTG_REF_SEL                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_OTG_UTMI_CFG
// Register Offset : 0x004C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_OTG_UTMI_CFG_OTG_UTMI_PAD_SEL                           BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_UART0_CFG
// Register Offset : 0x0050
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_UART0_CFG_UART0_DIV(x)                                  (((x) & 0x7) << 8)
#define BIT_AP_CLK_UART0_CFG_UART0_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_UART1_CFG
// Register Offset : 0x0054
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_UART1_CFG_UART1_DIV(x)                                  (((x) & 0x7) << 8)
#define BIT_AP_CLK_UART1_CFG_UART1_SEL(x)                                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_I2C0_CFG
// Register Offset : 0x0058
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_I2C0_CFG_I2C0_DIV(x)                                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_I2C0_CFG_I2C0_SEL(x)                                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_I2C1_CFG
// Register Offset : 0x005C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_I2C1_CFG_I2C1_DIV(x)                                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_I2C1_CFG_I2C1_SEL(x)                                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_I2C2_CFG
// Register Offset : 0x0060
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_I2C2_CFG_I2C2_DIV(x)                                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_I2C2_CFG_I2C2_SEL(x)                                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_SPI0_CFG
// Register Offset : 0x0064
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_SPI0_CFG_SPI0_PAD_SEL                                   BIT(16)
#define BIT_AP_CLK_SPI0_CFG_SPI0_DIV(x)                                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_SPI0_CFG_SPI0_SEL(x)                                    (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_IIS0_CFG
// Register Offset : 0x0068
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_IIS0_CFG_IIS0_DIV(x)                                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_IIS0_CFG_IIS0_SEL(x)                                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CE_CFG
// Register Offset : 0x006C
// Description     :
---------------------------------------------------------------------------*/

#define REG_AP_CLK_CORE_CGM_CE_CFG  	REG_AP_CLK_CE_CFG

#define BIT_AP_CLK_CE_CFG_CE_SEL(x)                                        (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_AP_EMMC_32K_CFG
// Register Offset : 0x0070
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_AP_EMMC_32K_CFG_AP_EMMC_32K_SEL                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_AP_SDIO0_32K_CFG
// Register Offset : 0x0074
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_AP_SDIO0_32K_CFG_AP_SDIO0_32K_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_NANDC_ECC_CFG
// Register Offset : 0x0078
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_NANDC_ECC_CFG_NANDC_ECC_SEL(x)                          (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_AP_SIM_32K_CFG
// Register Offset : 0x007C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_AP_SIM_32K_CFG_AP_SIM_32K_SEL                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_AXI_AP_EMC_CFG
// Register Offset : 0x0080
// Description     :
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_AXI_DISPC_EMC_CFG
// Register Offset : 0x0084
// Description     :
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_AXI_GSP_CA7_EMC_CFG
// Register Offset : 0x0088
// Description     :
---------------------------------------------------------------------------*/



#endif // _AP_CLK_CORE_REG_H

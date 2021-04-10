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

#define CTL_BASE_AP_CLK SPRD_APCLK_BASE


#define REG_AP_CLK_CGM_CTL_CFG        ( CTL_BASE_AP_CLK + 0x0010 )
#define REG_AP_CLK_CGM_AP_APB_CFG     ( CTL_BASE_AP_CLK + 0x0020 )
#define REG_AP_CLK_CGM_AP_AXI_CFG     ( CTL_BASE_AP_CLK + 0x0024 )
#define REG_AP_CLK_CGM_USB3_UTMI_CFG  ( CTL_BASE_AP_CLK + 0x0028 )
#define REG_AP_CLK_CGM_USB3_PIPE_CFG  ( CTL_BASE_AP_CLK + 0x002C )
#define REG_AP_CLK_CGM_USB3_REF_CFG   ( CTL_BASE_AP_CLK + 0x0030 )
#define REG_AP_CLK_CGM_EFS_CFG        ( CTL_BASE_AP_CLK + 0x0034 )
#define REG_AP_CLK_CGM_CE0_CFG        ( CTL_BASE_AP_CLK + 0x0038 )
#define REG_AP_CLK_CGM_CE1_CFG        ( CTL_BASE_AP_CLK + 0x003C )
#define REG_AP_CLK_CGM_UART0_CFG      ( CTL_BASE_AP_CLK + 0x0040 )
#define REG_AP_CLK_CGM_UART1_CFG      ( CTL_BASE_AP_CLK + 0x0044 )
#define REG_AP_CLK_CGM_UART2_CFG      ( CTL_BASE_AP_CLK + 0x0048 )
#define REG_AP_CLK_CGM_UART3_CFG      ( CTL_BASE_AP_CLK + 0x004C )
#define REG_AP_CLK_CGM_UART4_CFG      ( CTL_BASE_AP_CLK + 0x0050 )
#define REG_AP_CLK_CGM_I2C0_CFG       ( CTL_BASE_AP_CLK + 0x0054 )
#define REG_AP_CLK_CGM_I2C1_CFG       ( CTL_BASE_AP_CLK + 0x0058 )
#define REG_AP_CLK_CGM_I2C2_CFG       ( CTL_BASE_AP_CLK + 0x005C )
#define REG_AP_CLK_CGM_I2C3_CFG       ( CTL_BASE_AP_CLK + 0x0060 )
#define REG_AP_CLK_CGM_I2C4_CFG       ( CTL_BASE_AP_CLK + 0x0064 )
#define REG_AP_CLK_CGM_I2C5_CFG       ( CTL_BASE_AP_CLK + 0x0068 )
#define REG_AP_CLK_CGM_SPI0_CFG       ( CTL_BASE_AP_CLK + 0x006C )
#define REG_AP_CLK_CGM_SPI1_CFG       ( CTL_BASE_AP_CLK + 0x0070 )
#define REG_AP_CLK_CGM_SPI3_CFG       ( CTL_BASE_AP_CLK + 0x0074 )
#define REG_AP_CLK_CGM_IIS0_CFG       ( CTL_BASE_AP_CLK + 0x0078 )
#define REG_AP_CLK_CGM_IIS1_CFG       ( CTL_BASE_AP_CLK + 0x007C )
#define REG_AP_CLK_CGM_IIS2_CFG       ( CTL_BASE_AP_CLK + 0x0080 )
#define REG_AP_CLK_CGM_IIS3_CFG       ( CTL_BASE_AP_CLK + 0x0084 )
#define REG_AP_CLK_CGM_AP_32K_CFG     ( CTL_BASE_AP_CLK + 0x0088 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_CTL_CFG
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_DOZE_MODE_EN                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_APB_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_APB_DOZE_EN                 BIT(17)
#define BIT_AP_CLK_CGM_AP_APB_SEL(x)                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_AXI_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_AXI_DOZE_EN                 BIT(17)
#define BIT_AP_CLK_CGM_AP_AXI_SEL(x)                  (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_USB3_UTMI_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_USB3_UTMI_PAD_SEL              BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_USB3_PIPE_CFG
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_USB3_PIPE_PAD_SEL              BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_USB3_REF_CFG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_USB3_REF_DOZE_EN               BIT(17)
#define BIT_AP_CLK_CGM_USB3_REF_SEL                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_EFS_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_EFS_DOZE_EN                    BIT(17)
#define BIT_AP_CLK_CGM_EFS_SEL                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_CE0_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_CE0_DOZE_EN                    BIT(17)
#define BIT_AP_CLK_CGM_CE0_SEL(x)                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_CE1_CFG
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_CE1_DOZE_EN                    BIT(17)
#define BIT_AP_CLK_CGM_CE1_SEL(x)                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART0_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART0_DOZE_EN                  BIT(17)
#define BIT_AP_CLK_CGM_UART0_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART0_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART1_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART1_DOZE_EN                  BIT(17)
#define BIT_AP_CLK_CGM_UART1_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART1_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART2_CFG
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART2_DOZE_EN                  BIT(17)
#define BIT_AP_CLK_CGM_UART2_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART2_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART3_CFG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART3_DOZE_EN                  BIT(17)
#define BIT_AP_CLK_CGM_UART3_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART3_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_UART4_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_UART4_DOZE_EN                  BIT(17)
#define BIT_AP_CLK_CGM_UART4_DIV(x)                   (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_UART4_SEL(x)                   (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C0_CFG
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C0_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_I2C0_DIV(x)                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C0_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C1_CFG
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C1_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_I2C1_DIV(x)                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C1_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C2_CFG
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C2_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_I2C2_DIV(x)                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C2_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C3_CFG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C3_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_I2C3_DIV(x)                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C3_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C4_CFG
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C4_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_I2C4_DIV(x)                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C4_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_I2C5_CFG
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_I2C5_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_I2C5_DIV(x)                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_I2C5_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_SPI0_CFG
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_SPI0_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_SPI0_PAD_SEL                   BIT(16)
#define BIT_AP_CLK_CGM_SPI0_DIV(x)                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_SPI0_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_SPI1_CFG
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_SPI1_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_SPI1_PAD_SEL                   BIT(16)
#define BIT_AP_CLK_CGM_SPI1_DIV(x)                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_SPI1_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_SPI3_CFG
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_SPI3_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_SPI3_PAD_SEL                   BIT(16)
#define BIT_AP_CLK_CGM_SPI3_DIV(x)                    (((x) & 0x7) << 8)
#define BIT_AP_CLK_CGM_SPI3_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_IIS0_CFG
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_IIS0_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_IIS0_DIV(x)                    (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CGM_IIS0_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_IIS1_CFG
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_IIS1_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_IIS1_DIV(x)                    (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CGM_IIS1_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_IIS2_CFG
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_IIS2_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_IIS2_DIV(x)                    (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CGM_IIS2_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_IIS3_CFG
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_IIS3_DOZE_EN                   BIT(17)
#define BIT_AP_CLK_CGM_IIS3_DIV(x)                    (((x) & 0x3F) << 8)
#define BIT_AP_CLK_CGM_IIS3_SEL(x)                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_CLK_CGM_AP_32K_CFG
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_CLK_CGM_AP_32K_DOZE_EN                 BIT(17)
#define BIT_AP_CLK_CGM_AP_32K_SEL                     BIT(0)


#endif // _AP_CLK_REG_H

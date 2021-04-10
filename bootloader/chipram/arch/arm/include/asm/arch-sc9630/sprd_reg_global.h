/******************************************************************************
 ** File Name:    sprd_reg_global.h                                        *
 ** Author:       Daniel.Ding                                                 *
 ** DATE:         11/13/2005                                                  *
 ** Copyright:    2005 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 11/13/2005    Daniel.Ding     Create.                                     *
 ** 05/05/2010    Mingwei.Zhang   Modified for SC8800G                        *
 ******************************************************************************/
#ifndef _SPRD_REG_GLOBAL_H_
#define _SPRD_REG_GLOBAL_H_
/*----------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **-------------------------------------------------------------------------- */
#define APB_EB                   (CTL_BASE_APB+0x00)
#define APB_RST                  (CTL_BASE_APB+0x04)
#define USB_PHY_TUNE             (CTL_BASE_APB+0x08)
#define USB_PHY_TEST             (CTL_BASE_APB+0x0C)
#define USB_PHY_CTRL             (CTL_BASE_APB+0x10)
#define APB_MISC_CTRL            (CTL_BASE_APB+0x14)

#define AONAPB_EB0               (CTL_BASE_AON_APB+0x00)
#define AONAPB_EB1               (CTL_BASE_AON_APB+0x04)
#define AONAPB_RST0              (CTL_BASE_AON_APB+0x08)
#define AONAPB_RST1              (CTL_BASE_AON_APB+0x0C)
#define AONAPB_RTC_EB            (CTL_BASE_AON_APB+0x10)
#define AONAPB_MPLL              (CTL_BASE_AON_APB+0x14)
#define AONAPB_DPLL              (CTL_BASE_AON_APB+0x18)
#define AONAPB_TDPLL             (CTL_BASE_AON_APB+0x1C)
#define AONAPB_CPLL              (CTL_BASE_AON_APB+0x20)
#define AONAPB_WIFIPLL0          (CTL_BASE_AON_APB+0x24)
#define AONAPB_WIFIPLL1          (CTL_BASE_AON_APB+0x28)
#define AONAPB_WPLL0             (CTL_BASE_AON_APB+0x2C)
#define AONAPB_WPLL1             (CTL_BASE_AON_APB+0x30)
#define AONAPB_CGM               (CTL_BASE_AON_APB+0x34)
#define AONAPB_RST_MONITOR       (CTL_BASE_AON_APB+0xAC)
#define AONAPB_BOND0             (CTL_BASE_AON_APB+0xB4)
#define AONAPB_BOND1             (CTL_BASE_AON_APB+0xB8)

#define INTC3_EB                 BIT_22
#define INTC2_EB                 BIT_21
#define INTC1_EB                 BIT_20
#define INTC0_EB                 BIT_19
#define APB_CKG_EB               BIT_18
#define UART4_EB                 BIT_17
#define UART3_EB                 BIT_16
#define UART2_EB                 BIT_15
#define UART1_EB                 BIT_14
#define UART0_EB                 BIT_13
#define I2C4_EB                  BIT_12
#define I2C3_EB                  BIT_11
#define I2C2_EB                  BIT_10
#define I2C1_EB                  BIT_9
#define I2C0_EB                  BIT_8
#define SPI2_EB                  BIT_7
#define SPI1_EB                  BIT_6
#define SPI0_EB                  BIT_5
#define IIS3_EB                  BIT_4
#define IIS2_EB                  BIT_3
#define IIS1_EB                  BIT_2
#define IIS0_EB                  BIT_1
#define SIM0_EB                  BIT_0

#define INTC3_RST                 BIT_22
#define INTC2_RST                 BIT_21
#define INTC1_RST                 BIT_20
#define INTC0_RST                 BIT_19
#define APB_CKG_RST               BIT_18
#define UART4_RST                 BIT_17
#define UART3_RST                 BIT_16
#define UART2_RST                 BIT_15
#define UART1_RST                 BIT_14
#define UART0_RST                 BIT_13
#define I2C4_RST                  BIT_12
#define I2C3_RST                  BIT_11
#define I2C2_RST                  BIT_10
#define I2C1_RST                  BIT_9
#define I2C0_RST                  BIT_8
#define SPI2_RST                  BIT_7
#define SPI1_RST                  BIT_6
#define SPI0_RST                  BIT_5
#define IIS3_RST                  BIT_4
#define IIS2_RST                  BIT_3
#define IIS1_RST                  BIT_2
#define IIS0_RST                  BIT_1
#define SIM0_RST                  BIT_0

/**---------------------------------------------------------------------------*
 **                             Compiler Flag                                 *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif
/**----------------------------------------------------------------------------*
**                               Micro Define                                 **
**----------------------------------------------------------------------------*/

#ifdef   __cplusplus
}
#endif
/**---------------------------------------------------------------------------*/
#endif //_SPRD_REG_GLOBAL_H_
// End



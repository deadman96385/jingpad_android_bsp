/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _AON_SEC_APB_REG_H
#define _AON_SEC_APB_REG_H

#define CTL_BASE_AON_SEC_APB SPRD_SEC_REG_PHYS


#define REG_AON_SEC_APB_SEC_EB                          ( CTL_BASE_AON_SEC_APB + 0x0000 )
#define REG_AON_SEC_APB_SEC_SOFT_RST                    ( CTL_BASE_AON_SEC_APB + 0x0004 )
#define REG_AON_SEC_APB_FUNC_DMA_EN                     ( CTL_BASE_AON_SEC_APB + 0x0008 )
#define REG_AON_SEC_APB_CA7_CFG_CTRL                    ( CTL_BASE_AON_SEC_APB + 0x000C )
#define REG_AON_SEC_APB_CA7_TOP_PWR_DOWN_PROT_EN        ( CTL_BASE_AON_SEC_APB + 0x0010 )
#define REG_AON_SEC_APB_AP_SYS_PWR_DOWN_PROT_EN         ( CTL_BASE_AON_SEC_APB + 0x0014 )
#define REG_AON_SEC_APB_MM_TOP_PWR_DOWN_PROT_EN         ( CTL_BASE_AON_SEC_APB + 0x0018 )
#define REG_AON_SEC_APB_GPU_TOP_PWR_DOWN_PROT_EN        ( CTL_BASE_AON_SEC_APB + 0x001C )
#define REG_AON_SEC_APB_WTLCP_SYS_PWR_DOWN_PROT_EN      ( CTL_BASE_AON_SEC_APB + 0x0020 )
#define REG_AON_SEC_APB_PUBCP_SYS_PWR_DOWN_PROT_EN      ( CTL_BASE_AON_SEC_APB + 0x0024 )
#define REG_AON_SEC_APB_CA7_TOP_PWR_DOWN_PROT_EN_HID    ( CTL_BASE_AON_SEC_APB + 0x0030 )
#define REG_AON_SEC_APB_AP_SYS_PWR_DOWN_PROT_EN_HID     ( CTL_BASE_AON_SEC_APB + 0x0034 )
#define REG_AON_SEC_APB_MM_TOP_PWR_DOWN_PROT_EN_HID     ( CTL_BASE_AON_SEC_APB + 0x0038 )
#define REG_AON_SEC_APB_GPU_TOP_PWR_DOWN_PROT_EN_HID    ( CTL_BASE_AON_SEC_APB + 0x003C )
#define REG_AON_SEC_APB_WTLCP_SYS_PWR_DOWN_PROT_EN_HID  ( CTL_BASE_AON_SEC_APB + 0x0040 )
#define REG_AON_SEC_APB_PUBCP_SYS_PWR_DOWN_PROT_EN_HID  ( CTL_BASE_AON_SEC_APB + 0x0044 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_SEC_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_SEC_EIC_RTCDV5_EB                                BIT(10)
#define BIT_AON_SEC_APB_SEC_EIC_RTC_EB                                   BIT(9)
#define BIT_AON_SEC_APB_SEC_EIC_EB                                       BIT(8)
#define BIT_AON_SEC_APB_SEC_GPIO_EB                                      BIT(7)
#define BIT_AON_SEC_APB_SEC_RTC_CLK_GATE_EB                              BIT(6)
#define BIT_AON_SEC_APB_SEC_WDG_EB                                       BIT(5)
#define BIT_AON_SEC_APB_SEC_WDG_RTC_EB                                   BIT(4)
#define BIT_AON_SEC_APB_SEC_RTC_EB                                       BIT(3)
#define BIT_AON_SEC_APB_SEC_TMR_EB                                       BIT(2)
#define BIT_AON_SEC_APB_SEC_TMR_RTC_EB                                   BIT(1)
#define BIT_AON_SEC_APB_SEC_TZPC_EB                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_SEC_SOFT_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_SEC_EIC_SOFT_RST                                 BIT(5)
#define BIT_AON_SEC_APB_SEC_GPIO_RST                                     BIT(4)
#define BIT_AON_SEC_APB_SEC_WDG_SOFT_RST                                 BIT(3)
#define BIT_AON_SEC_APB_SEC_RTC_SOFT_RST                                 BIT(2)
#define BIT_AON_SEC_APB_SEC_TMR_SOFT_RST                                 BIT(1)
#define BIT_AON_SEC_APB_SEC_TZPC_SOFT_RST                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_FUNC_DMA_EN
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_FUNC_DMA_EN                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_CA7_CFG_CTRL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_CA7_GIC_CFGSDISABLE                              BIT(8)
#define BIT_AON_SEC_APB_CP15SDISABLE(x)                                  (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_CA7_TOP_PWR_DOWN_PROT_EN
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_CA7_TOP_PWR_DOWN_PROT_EN                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_AP_SYS_PWR_DOWN_PROT_EN
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_AP_SYS_PWR_DOWN_PROT_EN                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_MM_TOP_PWR_DOWN_PROT_EN
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_MM_TOP_PWR_DOWN_PROT_EN                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_GPU_TOP_PWR_DOWN_PROT_EN
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_GPU_TOP_PWR_DOWN_PROT_EN                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_WTLCP_SYS_PWR_DOWN_PROT_EN
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_WTLCP_SYS_PWR_DOWN_PROT_EN                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_PUBCP_SYS_PWR_DOWN_PROT_EN
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_PUBCP_SYS_PWR_DOWN_PROT_EN                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_CA7_TOP_PWR_DOWN_PROT_EN_HID
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_CA7_TOP_PWR_DOWN_PROT_EN_HID                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_AP_SYS_PWR_DOWN_PROT_EN_HID
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_AP_SYS_PWR_DOWN_PROT_EN_HID                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_MM_TOP_PWR_DOWN_PROT_EN_HID
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_MM_TOP_PWR_DOWN_PROT_EN_HID                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_GPU_TOP_PWR_DOWN_PROT_EN_HID
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_GPU_TOP_PWR_DOWN_PROT_EN_HID                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_WTLCP_SYS_PWR_DOWN_PROT_EN_HID
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_WTLCP_SYS_PWR_DOWN_PROT_EN_HID                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_PUBCP_SYS_PWR_DOWN_PROT_EN_HID
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_PUBCP_SYS_PWR_DOWN_PROT_EN_HID                   BIT(0)


#endif // _AON_SEC_APB_REG_H

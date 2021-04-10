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

#define CTL_BASE_AON_SEC_APB SPRD_SEC_AON_BASE


#define REG_AON_SEC_APB_CHIP_KPRTL_0            ( CTL_BASE_AON_SEC_APB + 0x0000 )
#define REG_AON_SEC_APB_CHIP_KPRTL_1            ( CTL_BASE_AON_SEC_APB + 0x0004 )
#define REG_AON_SEC_APB_CHIP_KPRTL_2            ( CTL_BASE_AON_SEC_APB + 0x0008 )
#define REG_AON_SEC_APB_CHIP_KPRTL_3            ( CTL_BASE_AON_SEC_APB + 0x000C )
#define REG_AON_SEC_APB_SEC_EB                  ( CTL_BASE_AON_SEC_APB + 0x0010 )
#define REG_AON_SEC_APB_SEC_SOFT_RST            ( CTL_BASE_AON_SEC_APB + 0x0014 )
#define REG_AON_SEC_APB_RVBARADDR0_LIT          ( CTL_BASE_AON_SEC_APB + 0x0034 )
#define REG_AON_SEC_APB_RVBARADDR1_LIT          ( CTL_BASE_AON_SEC_APB + 0x0038 )
#define REG_AON_SEC_APB_RVBARADDR2_LIT          ( CTL_BASE_AON_SEC_APB + 0x003C )
#define REG_AON_SEC_APB_RVBARADDR3_LIT          ( CTL_BASE_AON_SEC_APB + 0x0040 )
#define REG_AON_SEC_APB_RVBARADDR0_BIG          ( CTL_BASE_AON_SEC_APB + 0x0044 )
#define REG_AON_SEC_APB_RVBARADDR1_BIG          ( CTL_BASE_AON_SEC_APB + 0x0048 )
#define REG_AON_SEC_APB_RVBARADDR2_BIG          ( CTL_BASE_AON_SEC_APB + 0x004C )
#define REG_AON_SEC_APB_RVBARADDR3_BIG          ( CTL_BASE_AON_SEC_APB + 0x0050 )
#define REG_AON_SEC_APB_SP_SUBSYS_SEC_ATTR      ( CTL_BASE_AON_SEC_APB + 0x005C )
#define REG_AON_SEC_APB_FUNCDMA_NORMAL_MODE_EN  ( CTL_BASE_AON_SEC_APB + 0x0060 )
#define REG_AON_SEC_APB_ADI_PPROT_SEL           ( CTL_BASE_AON_SEC_APB + 0x0064 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_CHIP_KPRTL_0
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_KPRTL_0(x)                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_CHIP_KPRTL_1
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_KPRTL_1(x)                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_CHIP_KPRTL_2
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_KPRTL_2(x)                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_CHIP_KPRTL_3
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_KPRTL_3(x)                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_SEC_EB
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_SEC_WDG_EB                          BIT(5)
#define BIT_AON_SEC_APB_SEC_WDG_RTC_EB                      BIT(4)
#define BIT_AON_SEC_APB_SEC_TMR0_EB                         BIT(2)
#define BIT_AON_SEC_APB_SEC_TMR0_RTC_EB                     BIT(1)
#define BIT_AON_SEC_APB_SEC_TZPC_EB                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_SEC_SOFT_RST
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_SEC_WDG_SOFT_RST                    BIT(3)
#define BIT_AON_SEC_APB_SEC_TMR0_SOFT_RST                   BIT(1)
#define BIT_AON_SEC_APB_SEC_TZPC_SOFT_RST                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_RVBARADDR0_LIT
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_RVBARADDR0_LIT(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_RVBARADDR1_LIT
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_RVBARADDR1_LIT(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_RVBARADDR2_LIT
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_RVBARADDR2_LIT(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_RVBARADDR3_LIT
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_RVBARADDR3_LIT(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_RVBARADDR0_BIG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_RVBARADDR0_BIG(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_RVBARADDR1_BIG
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_RVBARADDR1_BIG(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_RVBARADDR2_BIG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_RVBARADDR2_BIG(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_RVBARADDR3_BIG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_RVBARADDR3_BIG(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_SP_SUBSYS_SEC_ATTR
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_SP_SUBSYS_RD_SEC                    BIT(1)
#define BIT_AON_SEC_APB_SP_SUBSYS_WR_SEC                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_FUNCDMA_NORMAL_MODE_EN
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_FDMA_NORMAL_EB                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_SEC_APB_ADI_PPROT_SEL
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_SEC_APB_ADI_PPROT_SEL                       BIT(0)


#endif // _AON_SEC_APB_REG_H

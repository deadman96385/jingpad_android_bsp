/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef __H_REGS_AP_AHB_HEADFILE_H__
#define __H_REGS_AP_AHB_HEADFILE_H__



#define REG_AP_AHB_AHB_EB                      SCI_ADDR(REGS_AP_AHB_BASE, 0x0000 )
#define REG_AP_AHB_AHB_RST                     SCI_ADDR(REGS_AP_AHB_BASE, 0x0004 )
#define REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG      SCI_ADDR(REGS_AP_AHB_BASE, 0x0008 )
#define REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG       SCI_ADDR(REGS_AP_AHB_BASE, 0x000C )
#define REG_AP_AHB_HOLDING_PEN                 SCI_ADDR(REGS_AP_AHB_BASE, 0x0010 )
#define REG_AP_AHB_MISC_CKG_EN                 SCI_ADDR(REGS_AP_AHB_BASE, 0x0014 )
#define REG_AP_AHB_MISC_CFG                    SCI_ADDR(REGS_AP_AHB_BASE, 0x0018 )
#define REG_AP_AHB_NANC_CLK_CFG                SCI_ADDR(REGS_AP_AHB_BASE, 0x3000 )
#define REG_AP_AHB_AP_QOS_CFG                  SCI_ADDR(REGS_AP_AHB_BASE, 0x3004 )
#define REG_AP_AHB_RESERVED                    SCI_ADDR(REGS_AP_AHB_BASE, 0x3008 )
#define REG_AP_AHB_RESERVED_REG_0              SCI_ADDR(REGS_AP_AHB_BASE, 0x300C )
#define REG_AP_AHB_RESERVED_REG_1              SCI_ADDR(REGS_AP_AHB_BASE, 0x3010 )
#define REG_AP_AHB_RESERVED_REG_2              SCI_ADDR(REGS_AP_AHB_BASE, 0x3014 )
#define REG_AP_AHB_RESERVED_REG_3              SCI_ADDR(REGS_AP_AHB_BASE, 0x3018 )
#define REG_AP_AHB_RESERVED_REG_4              SCI_ADDR(REGS_AP_AHB_BASE, 0x301C )
#define REG_AP_AHB_USB3_CTRL                   SCI_ADDR(REGS_AP_AHB_BASE, 0x3020 )
#define REG_AP_AHB_MISC_CTRL                   SCI_ADDR(REGS_AP_AHB_BASE, 0x3024 )
#define REG_AP_AHB_MISC_STATUS                 SCI_ADDR(REGS_AP_AHB_BASE, 0x3028 )
#define REG_AP_AHB_NOC_CTRL0                   SCI_ADDR(REGS_AP_AHB_BASE, 0x302C )
#define REG_AP_AHB_NOC_CTRL1                   SCI_ADDR(REGS_AP_AHB_BASE, 0x3030 )
#define REG_AP_AHB_NOC_CTRL2                   SCI_ADDR(REGS_AP_AHB_BASE, 0x3034 )
#define REG_AP_AHB_NOC_CTRL3                   SCI_ADDR(REGS_AP_AHB_BASE, 0x3038 )
#define REG_AP_AHB_USB3_DBG0                   SCI_ADDR(REGS_AP_AHB_BASE, 0x303C )
#define REG_AP_AHB_USB3_DBG1                   SCI_ADDR(REGS_AP_AHB_BASE, 0x3040 )
#define REG_AP_AHB_USB3_DBG2                   SCI_ADDR(REGS_AP_AHB_BASE, 0x3044 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CE1_EB                                       BIT(25)
#define BIT_AP_AHB_CE0_EB                                       BIT(24)
#define BIT_AP_AHB_CC63P_EB                                     BIT(23)
#define BIT_AP_AHB_CC63S_EB                                     BIT(22)
#define BIT_AP_AHB_BUSMON_EB                                    BIT(13)
#define BIT_AP_AHB_ROM_EB                                       BIT(12)
#define BIT_AP_AHB_EMMC_EB                                      BIT(10)
#define BIT_AP_AHB_SDIO2_EB                                     BIT(9)
#define BIT_AP_AHB_SDIO1_EB                                     BIT(8)
#define BIT_AP_AHB_SDIO0_EB                                     BIT(7)
#define BIT_AP_AHB_DMA_EB                                       BIT(5)
#define BIT_DMA_EB                                     			BIT_AP_AHB_DMA_EB
#define BIT_AP_AHB_USB3_REF_EB                                  BIT(4)
#define BIT_AP_AHB_USB3_SUSPEND_EB                              BIT(3)
#define BIT_AP_AHB_USB3_EB                                      BIT(2)


/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AHB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CC63P_SOFT_RST                               BIT(31)
#define BIT_AP_AHB_CC63S_SOFT_RST                               BIT(30)
#define BIT_AP_AHB_CE1_SOFT_RST                                 BIT(26)
#define BIT_AP_AHB_CE0_SOFT_RST                                 BIT(25)
#define BIT_AP_AHB_BUSMON_SOFT_RST                              BIT(14)
#define BIT_AP_AHB_EMMC_SOFT_RST                                BIT(11)
#define BIT_AP_AHB_SDIO2_SOFT_RST                               BIT(10)
#define BIT_AP_AHB_SDIO1_SOFT_RST                               BIT(9)
#define BIT_AP_AHB_SDIO0_SOFT_RST                               BIT(8)
#define BIT_AP_AHB_DMA_SOFT_RST                                 BIT(5)
#define BIT_DMA_SOFT_RST                                        BIT_AP_AHB_DMA_SOFT_RST
#define BIT_AP_AHB_USB3_SOFT_RST                                BIT(1)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AP_SYS_FORCE_SLEEP_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_AP_PERI_FORCE_ON                             BIT(2)
#define BIT_AP_AHB_AP_PERI_FORCE_SLP                            BIT(1)
#define BIT_AP_AHB_AP_APB_SLEEP                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_DMA_ACT_LIGHT_EN                             BIT(2)
#define BIT_AP_AHB_AP_AHB_AUTO_GATE_EN                          BIT(1)
#define BIT_AP_AHB_AP_EMC_AUTO_GATE_EN                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_HOLDING_PEN
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_HOLDING_PEN(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MISC_CKG_EN
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_BUS_CLK_FORCE_ON(x)                          (((x) & 0x3FFF) << 2)
#define BIT_AP_AHB_DPHY_REF_CKG_EN                              (BIT(1))
#define BIT_AP_AHB_DPHY_CFG_CKG_EN                              (BIT(0))
#define BIT_DPHY_REF_CKG_EN                                     (BIT_AP_AHB_DPHY_REF_CKG_EN)
#define BIT_DPHY_CFG_CKG_EN                                     (BIT_AP_AHB_DPHY_CFG_CKG_EN)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MISC_CFG
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_AP_R_RES(x)                                  (((x) & 0x1F) << 27)
#define BIT_AP_AHB_AP_RW_RES(x)                                 (((x) & 0x3F) << 10)
#define BIT_AP_AHB_M0_NIU_IDLE_DET_DIS                          BIT(9)
#define BIT_AP_AHB_BUS_VALID_CNT(x)                             (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NANC_CLK_CFG
// Register Offset : 0x3000
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_AP_QOS_CFG
// Register Offset : 0x3004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_AP_QOS_ID7(x)                                (((x) & 0xF) << 28)
#define BIT_AP_AHB_AP_QOS_ID6(x)                                (((x) & 0xF) << 24)
#define BIT_AP_AHB_AP_QOS_ID5(x)                                (((x) & 0xF) << 20)
#define BIT_AP_AHB_AP_QOS_ID4(x)                                (((x) & 0xF) << 16)
#define BIT_AP_AHB_AP_QOS_ID3(x)                                (((x) & 0xF) << 12)
#define BIT_AP_AHB_AP_QOS_ID2(x)                                (((x) & 0xF) << 8)
#define BIT_AP_AHB_AP_QOS_ID1(x)                                (((x) & 0xF) << 4)
#define BIT_AP_AHB_AP_QOS_ID0(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_RESERVED
// Register Offset : 0x3008
// Description     : 
---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_RESERVED_REG_0
// Register Offset : 0x300C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_RESERVED0_REG(x)                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_RESERVED_REG_1
// Register Offset : 0x3010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_RESERVED1_REG(x)                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_RESERVED_REG_2
// Register Offset : 0x3014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_RESERVED2_REG(x)                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_RESERVED_REG_3
// Register Offset : 0x3018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_RESERVED3_REG(x)                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_RESERVED_REG_4
// Register Offset : 0x301C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_RESERVED4_REG(x)                             (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_USB3_CTRL
// Register Offset : 0x3020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_HOST_SYSTEM_ERR                              BIT(12)
#define BIT_AP_AHB_HOST_PORT_POWER_CONTROL_PRESENT              BIT(11)
#define BIT_AP_AHB_FLADJ_30MHZ_REG(x)                           (((x) & 0x3F) << 5)
#define BIT_AP_AHB_PME_EN                                       BIT(4)
#define BIT_AP_AHB_BUS_FILTER_BYPASS(x)                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MISC_CTRL
// Register Offset : 0x3024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_CC63P_APBS_PPROT(x)                          (((x) & 0x7) << 15)
#define BIT_AP_AHB_CC63S_APBS_PPROT(x)                          (((x) & 0x7) << 12)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_MISC_STATUS
// Register Offset : 0x3028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_INT_REQ_CC63P                                BIT(1)
#define BIT_AP_AHB_INT_REQ_CC63S                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NOC_CTRL0
// Register Offset : 0x302C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M9_QOS(x)                                    (((x) & 0xF) << 28)
#define BIT_AP_AHB_M6_QOS(x)                                    (((x) & 0xF) << 20)
#define BIT_AP_AHB_M5_QOS(x)                                    (((x) & 0xF) << 16)
#define BIT_AP_AHB_M4_QOS(x)                                    (((x) & 0xF) << 12)
#define BIT_AP_AHB_M3_QOS(x)                                    (((x) & 0xF) << 8)
#define BIT_AP_AHB_M2_QOS(x)                                    (((x) & 0xF) << 4)
#define BIT_AP_AHB_M1_QOS(x)                                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NOC_CTRL1
// Register Offset : 0x3030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_S5_T_MAINEXTEN                               BIT(21)
#define BIT_AP_AHB_S4_T_MAINEXTEN                               BIT(20)
#define BIT_AP_AHB_S3_T_MAINEXTEN                               BIT(19)
#define BIT_AP_AHB_S2_T_MAINEXTEN                               BIT(18)
#define BIT_AP_AHB_S1_T_MAINEXTEN                               BIT(17)
#define BIT_AP_AHB_S0_T_MAINEXTEN                               BIT(16)
#define BIT_AP_AHB_M14_QOS(x)                                   (((x) & 0xF) << 12)
#define BIT_AP_AHB_M13_QOS(x)                                   (((x) & 0xF) << 8)
#define BIT_AP_AHB_M12_QOS(x)                                   (((x) & 0xF) << 4)
#define BIT_AP_AHB_M11_QOS(x)                                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NOC_CTRL2
// Register Offset : 0x3034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M12_ARCACHE(x)                               (((x) & 0xF) << 28)
#define BIT_AP_AHB_M11_ARCACHE(x)                               (((x) & 0xF) << 24)
#define BIT_AP_AHB_M6_ARCACHE(x)                                (((x) & 0xF) << 16)
#define BIT_AP_AHB_M5_ARCACHE(x)                                (((x) & 0xF) << 12)
#define BIT_AP_AHB_M4_ARCACHE(x)                                (((x) & 0xF) << 8)
#define BIT_AP_AHB_M3_ARCACHE(x)                                (((x) & 0xF) << 4)
#define BIT_AP_AHB_M2_ARCACHE(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_NOC_CTRL3
// Register Offset : 0x3038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_M12_AWCACHE(x)                               (((x) & 0xF) << 28)
#define BIT_AP_AHB_M11_AWCACHE(x)                               (((x) & 0xF) << 24)
#define BIT_AP_AHB_M6_AWCACHE(x)                                (((x) & 0xF) << 16)
#define BIT_AP_AHB_M5_AWCACHE(x)                                (((x) & 0xF) << 12)
#define BIT_AP_AHB_M4_AWCACHE(x)                                (((x) & 0xF) << 8)
#define BIT_AP_AHB_M3_AWCACHE(x)                                (((x) & 0xF) << 4)
#define BIT_AP_AHB_M2_AWCACHE(x)                                (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_USB3_DBG0
// Register Offset : 0x303C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_USB3_DUG_0(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_USB3_DBG1
// Register Offset : 0x3040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_USB3_DUG_1(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AP_AHB_USB3_DBG2
// Register Offset : 0x3044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AP_AHB_USB3_DUG_2(x)                                (((x) & 0x3))

#endif

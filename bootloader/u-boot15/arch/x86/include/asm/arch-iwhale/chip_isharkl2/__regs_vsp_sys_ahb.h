/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _VSP_SYS_AHB_REG_H
#define _VSP_SYS_AHB_REG_H

#define CTL_BASE_VSP_SYS_AHB SPRD_VSPAHB_BASE


#define REG_VSP_SYS_AHB_AHB_EB                   ( CTL_BASE_VSP_SYS_AHB + 0x0000 )
#define REG_VSP_SYS_AHB_AHB_RST                  ( CTL_BASE_VSP_SYS_AHB + 0x0004 )
#define REG_VSP_SYS_AHB_AXI_CACHE                ( CTL_BASE_VSP_SYS_AHB + 0x0008 )
#define REG_VSP_SYS_AHB_MISC_CTRL                ( CTL_BASE_VSP_SYS_AHB + 0x000C )
#define REG_VSP_SYS_AHB_VSP_QOS_CFG0             ( CTL_BASE_VSP_SYS_AHB + 0x0010 )
#define REG_VSP_SYS_AHB_VSP_QOS_CFG1             ( CTL_BASE_VSP_SYS_AHB + 0x0014 )
#define REG_VSP_SYS_AHB_VSP_AXI_LPC0             ( CTL_BASE_VSP_SYS_AHB + 0x0018 )
#define REG_VSP_SYS_AHB_VSP_AXI_LPC1             ( CTL_BASE_VSP_SYS_AHB + 0x001C )
#define REG_VSP_SYS_AHB_VSP_AXI_LPC2             ( CTL_BASE_VSP_SYS_AHB + 0x0020 )
#define REG_VSP_SYS_AHB_VSP_AXI_LPC3             ( CTL_BASE_VSP_SYS_AHB + 0x0024 )
#define REG_VSP_SYS_AHB_VSP_AB0_CTRL0            ( CTL_BASE_VSP_SYS_AHB + 0x0028 )
#define REG_VSP_SYS_AHB_VSP_AB0_CTRL1            ( CTL_BASE_VSP_SYS_AHB + 0x002C )
#define REG_VSP_SYS_AHB_VSP_AB0_CTRL2            ( CTL_BASE_VSP_SYS_AHB + 0x0030 )
#define REG_VSP_SYS_AHB_VSP_AB0_DBG              ( CTL_BASE_VSP_SYS_AHB + 0x0040 )
#define REG_VSP_SYS_AHB_VSP_VSP_AXI_OT_CTRL_CFG  ( CTL_BASE_VSP_SYS_AHB + 0x0044 )
#define REG_VSP_SYS_AHB_VSP_GSP_AXI_OT_CTRL_CFG  ( CTL_BASE_VSP_SYS_AHB + 0x0048 )
#define REG_VSP_SYS_AHB_VSP_DYN_AWQOS_CTRL_CFG   ( CTL_BASE_VSP_SYS_AHB + 0x004C )
#define REG_VSP_SYS_AHB_VSP_DYN_ARQOS_CTRL_CFG   ( CTL_BASE_VSP_SYS_AHB + 0x0050 )
#define REG_VSP_SYS_AHB_GSP_DYN_AWQOS_CTRL_CFG   ( CTL_BASE_VSP_SYS_AHB + 0x0054 )
#define REG_VSP_SYS_AHB_GSP_DYN_ARQOS_CTRL_CFG   ( CTL_BASE_VSP_SYS_AHB + 0x0058 )

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_VSP_MEMFW_EN                                   BIT(14)
#define BIT_VSP_SYS_AHB_GSP_BUSMON_EN                                  BIT(13)
#define BIT_VSP_SYS_AHB_VSP_BUSMON_EN                                  BIT(12)
#define BIT_VSP_SYS_AHB_SYS_MTX_EB                                     BIT(10)
#define BIT_VSP_SYS_AHB_GSP0_EB                                        BIT(5)
#define BIT_VSP_SYS_AHB_CKG_EB                                         BIT(1)
#define BIT_VSP_SYS_AHB_VSP_1080P_EB                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_AHB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_MEM_FW_SOFT_RST                                BIT(8)
#define BIT_VSP_SYS_AHB_GSP0_SOFT_RST                                  BIT(6)
#define BIT_VSP_SYS_AHB_CKG_SOFT_RST                                   BIT(2)
#define BIT_VSP_SYS_AHB_VSP_1080P_SOFT_RST                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_AXI_CACHE
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_ARCACHE_GSP(x)                                 (((x) & 0xF) << 12)
#define BIT_VSP_SYS_AHB_AWCACHE_GSP(x)                                 (((x) & 0xF) << 8)
#define BIT_VSP_SYS_AHB_ARCACHE_VSP(x)                                 (((x) & 0xF) << 4)
#define BIT_VSP_SYS_AHB_AWCACHE_VSP(x)                                 (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_MISC_CTRL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_VSP1080P_SOFT_RST_MASK                         BIT(18)
#define BIT_VSP_SYS_AHB_GSP0_SOFT_RST_MASK                             BIT(16)
#define BIT_VSP_SYS_AHB_ADDR_CUTOFF_ENABLE_VSP                         BIT(12)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_QOS_CFG0
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_QOS_R_VSP_1080P(x)                             (((x) & 0xF) << 4)
#define BIT_VSP_SYS_AHB_QOS_W_VSP_1080P(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_QOS_CFG1
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_QOS_R_GSP0(x)                                  (((x) & 0xF) << 4)
#define BIT_VSP_SYS_AHB_QOS_W_GSP0(x)                                  (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_AXI_LPC0
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_LP_EB_AP_VSP                                   BIT(13)
#define BIT_VSP_SYS_AHB_LP_FORCE_AP_VSP                                BIT(12)
#define BIT_VSP_SYS_AHB_ACTIVE_SYNC_SEL_AP_VSP                         BIT(11)
#define BIT_VSP_SYS_AHB_LP_EB_GSP_NOC                                  BIT(10)
#define BIT_VSP_SYS_AHB_LP_FORCE_GSP_NOC                               BIT(9)
#define BIT_VSP_SYS_AHB_ACTIVE_SYNC_SEL_GSP_NOC                        BIT(8)
#define BIT_VSP_SYS_AHB_LP_EB_VSP_NOC                                  BIT(7)
#define BIT_VSP_SYS_AHB_LP_FORCE_VSP_NOC                               BIT(6)
#define BIT_VSP_SYS_AHB_ACTIVE_SYNC_SEL_VSP_NOC                        BIT(5)
#define BIT_VSP_SYS_AHB_LP_EB_VSP_PUB0                                 BIT(4)
#define BIT_VSP_SYS_AHB_LP_FORCE_VSP_PUB0                              BIT(3)
#define BIT_VSP_SYS_AHB_ACTIVE_SYNC_SEL_VSP_PUB0                       BIT(2)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_AXI_LPC1
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_LP_EB_VSP_MAIN                                 BIT(28)
#define BIT_VSP_SYS_AHB_LP_FORCE_VSP_MAIN                              BIT(27)
#define BIT_VSP_SYS_AHB_ACTIVE_SYNC_SEL_VSP_MAIN                       BIT(26)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_AXI_LPC2
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_LP_NUM_VSP_SYS(x)                              (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_AXI_LPC3
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_LP_NUM_VSP_AB(x)                               (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_AB0_CTRL0
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_AXI_DETECTOR_OVERFLOW_CH0                      BIT(31)
#define BIT_VSP_SYS_AHB_BRIDGE_TRANS_IDLE_CH0                          BIT(30)
#define BIT_VSP_SYS_AHB_BRIDGE_FIFO_FULL_CH0                           BIT(29)
#define BIT_VSP_SYS_AHB_BRIDGE_WFIFO_FULL_CH0                          BIT(28)
#define BIT_VSP_SYS_AHB_BRIDGE_RFIFO_FULL_CH0                          BIT(27)
#define BIT_VSP_SYS_AHB_FIFO_AF_LVL_AW_CH0(x)                          (((x) & 0x3F) << 20)
#define BIT_VSP_SYS_AHB_FIFO_AE_LVL_AW_CH0(x)                          (((x) & 0x3F) << 14)
#define BIT_VSP_SYS_AHB_FIFO_AF_LVL_W_CH0(x)                           (((x) & 0x3F) << 8)
#define BIT_VSP_SYS_AHB_FIFO_AE_LVL_W_CH0(x)                           (((x) & 0x3F) << 2)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_AB0_CTRL1
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_FIFO_AF_LVL_B_CH0(x)                           (((x) & 0x3F) << 24)
#define BIT_VSP_SYS_AHB_FIFO_AE_LVL_B_CH0(x)                           (((x) & 0x3F) << 18)
#define BIT_VSP_SYS_AHB_FIFO_AF_LVL_AR_CH0(x)                          (((x) & 0x3F) << 12)
#define BIT_VSP_SYS_AHB_FIFO_AE_LVL_AR_CH0(x)                          (((x) & 0x3F) << 6)
#define BIT_VSP_SYS_AHB_FIFO_AF_LVL_R_CH0(x)                           (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_AB0_CTRL2
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_FIFO_AE_LVL_R_CH0(x)                           (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_AB0_DBG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_VSP_AB0_DBG_SIGNAL(x)                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_VSP_AXI_OT_CTRL_CFG
// Register Offset : 0x0044
// Description     : axi outstanding control config register
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_VSP_AXI_OT_BYPASS_MODE                         BIT(31)
#define BIT_VSP_SYS_AHB_VSP_AR_MAX_OT(x)                               (((x) & 0x7F) << 8)
#define BIT_VSP_SYS_AHB_VSP_AW_MAX_OT(x)                               (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_GSP_AXI_OT_CTRL_CFG
// Register Offset : 0x0048
// Description     : axi outstanding control config register
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_GSP_AXI_OT_BYPASS_MODE                         BIT(31)
#define BIT_VSP_SYS_AHB_GSP_AR_MAX_OT(x)                               (((x) & 0x7F) << 8)
#define BIT_VSP_SYS_AHB_GSP_AW_MAX_OT(x)                               (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_DYN_AWQOS_CTRL_CFG
// Register Offset : 0x004C
// Description     : dynamic qos contorl config register
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_VSP_DYN_AWQOS_BYPASS_MODE                      BIT(31)
#define BIT_VSP_SYS_AHB_VSP_PARA_AWQOS_DFLT(x)                         (((x) & 0xF) << 24)
#define BIT_VSP_SYS_AHB_VSP_PARA_AWQOS_TIMEOUT(x)                      (((x) & 0xF) << 20)
#define BIT_VSP_SYS_AHB_VSP_PARA_AWQOS_EN                              BIT(19)
#define BIT_VSP_SYS_AHB_VSP_PARA_AWQOS_UPDATE                          BIT(18)
#define BIT_VSP_SYS_AHB_VSP_PARA_AWQOS_TIMEOUT_THRES(x)                (((x) & 0x3FF) << 8)
#define BIT_VSP_SYS_AHB_VSP_PARA_AWQOS_RUN_LEN(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_VSP_DYN_ARQOS_CTRL_CFG
// Register Offset : 0x0050
// Description     : dynamic qos contorl config register
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_VSP_DYN_ARQOS_BYPASS_MODE                      BIT(31)
#define BIT_VSP_SYS_AHB_VSP_PARA_ARQOS_DFLT(x)                         (((x) & 0xF) << 24)
#define BIT_VSP_SYS_AHB_VSP_PARA_ARQOS_TIMEOUT(x)                      (((x) & 0xF) << 20)
#define BIT_VSP_SYS_AHB_VSP_PARA_ARQOS_EN                              BIT(19)
#define BIT_VSP_SYS_AHB_VSP_PARA_ARQOS_UPDATE                          BIT(18)
#define BIT_VSP_SYS_AHB_VSP_PARA_ARQOS_TIMEOUT_THRES(x)                (((x) & 0x3FF) << 8)
#define BIT_VSP_SYS_AHB_VSP_PARA_ARQOS_RUN_LEN(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_GSP_DYN_AWQOS_CTRL_CFG
// Register Offset : 0x0054
// Description     : dynamic qos contorl config register
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_GSP_DYN_AWQOS_BYPASS_MODE                      BIT(31)
#define BIT_VSP_SYS_AHB_GSP_PARA_AWQOS_DFLT(x)                         (((x) & 0xF) << 24)
#define BIT_VSP_SYS_AHB_GSP_PARA_AWQOS_TIMEOUT(x)                      (((x) & 0xF) << 20)
#define BIT_VSP_SYS_AHB_GSP_PARA_AWQOS_EN                              BIT(19)
#define BIT_VSP_SYS_AHB_GSP_PARA_AWQOS_UPDATE                          BIT(18)
#define BIT_VSP_SYS_AHB_GSP_PARA_AWQOS_TIMEOUT_THRES(x)                (((x) & 0x3FF) << 8)
#define BIT_VSP_SYS_AHB_GSP_PARA_AWQOS_RUN_LEN(x)                      (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_SYS_AHB_GSP_DYN_ARQOS_CTRL_CFG
// Register Offset : 0x0058
// Description     : dynamic qos contorl config register
---------------------------------------------------------------------------*/

#define BIT_VSP_SYS_AHB_GSP_DYN_ARQOS_BYPASS_MODE                      BIT(31)
#define BIT_VSP_SYS_AHB_GSP_PARA_ARQOS_DFLT(x)                         (((x) & 0xF) << 24)
#define BIT_VSP_SYS_AHB_GSP_PARA_ARQOS_TIMEOUT(x)                      (((x) & 0xF) << 20)
#define BIT_VSP_SYS_AHB_GSP_PARA_ARQOS_EN                              BIT(19)
#define BIT_VSP_SYS_AHB_GSP_PARA_ARQOS_UPDATE                          BIT(18)
#define BIT_VSP_SYS_AHB_GSP_PARA_ARQOS_TIMEOUT_THRES(x)                (((x) & 0x3FF) << 8)
#define BIT_VSP_SYS_AHB_GSP_PARA_ARQOS_RUN_LEN(x)                      (((x) & 0xFF))


#endif // _VSP_SYS_AHB_REG_H

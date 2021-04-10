/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef __H_REGS_DISP_AHB_HEADFILE_H__
#define __H_REGS_DISP_AHB_HEADFILE_H__

#define REG_DISP_AHB_AHB_EB          SCI_ADDR(REGS_DISP_AHB_BASE, 0x0000 )
#define REG_DISP_AHB_AHB_RST         SCI_ADDR(REGS_DISP_AHB_BASE, 0x0004 )
#define REG_DISP_AHB_GEN_CKG_CFG     SCI_ADDR(REGS_DISP_AHB_BASE, 0x0008 )
#define REG_DISP_AHB_GEN_BUSMON_CFG  SCI_ADDR(REGS_DISP_AHB_BASE, 0x000C )
#define REG_DISP_AHB_DISPC_QOS_CFG0  SCI_ADDR(REGS_DISP_AHB_BASE, 0x0018 )
#define REG_DISP_AHB_DISPC_QOS_CFG1  SCI_ADDR(REGS_DISP_AHB_BASE, 0x001C )
#define REG_DISP_AHB_MISC_CTRL       SCI_ADDR(REGS_DISP_AHB_BASE, 0x0020 )

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_DISPC_MTX_EB                          BIT(16)
#define BIT_DISP_AHB_TMC_MTX_EB                            BIT(15)
#define BIT_DISP_AHB_GSP_MTX_EB                            BIT(14)
#define BIT_DISP_AHB_GPU_MTX_EB                            BIT(13)
#define BIT_DISP_AHB_GPU_EB                                BIT(10)
#define BIT_DISP_AHB_CKG_EB                                BIT(9)
#define BIT_DISP_AHB_DSI1_EB                               BIT(8)
#define BIT_DISP_AHB_DSI0_EB                               BIT(7)
#define BIT_DISP_AHB_GSP1_MMU_EB                           BIT(6)
#define BIT_DISP_AHB_GSP0_MMU_EB                           BIT(5)
#define BIT_DISP_AHB_GSP1_EB                               BIT(4)
#define BIT_DISP_AHB_GSP0_EB                               BIT(3)
#define BIT_DISP_AHB_DISPC_MMU_EB                          BIT(2)
#define BIT_DISP_AHB_DISPC1_EB                             BIT(1)
#define BIT_DISP_AHB_DISPC0_EB                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_AHB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_GSP_MTX_SOFT_RST                      BIT(15)
#define BIT_DISP_AHB_DISPC0_ENC_SOFT_RST                   BIT(12)
#define BIT_DISP_AHB_DISPC_MTX_SOFT_RST                    BIT(11)
#define BIT_DISP_AHB_CKG_SOFT_RST                          BIT(10)
#define BIT_DISP_AHB_DISPC0_LVDS_SOFT_RST                  BIT(9)
#define BIT_DISP_AHB_DSI1_SOFT_RST                         BIT(8)
#define BIT_DISP_AHB_DSI0_SOFT_RST                         BIT(7)
#define BIT_DISP_AHB_GSP1_MMU_SOFT_RST                     BIT(6)
#define BIT_DISP_AHB_GSP0_MMU_SOFT_RST                     BIT(5)
#define BIT_DISP_AHB_GSP1_SOFT_RST                         BIT(4)
#define BIT_DISP_AHB_GSP0_SOFT_RST                         BIT(3)
#define BIT_DISP_AHB_DISPC_MMU_SOFT_RST                    BIT(2)
#define BIT_DISP_AHB_DISPC1_SOFT_RST                       BIT(1)
#define BIT_DISP_AHB_DISPC0_SOFT_RST                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_GEN_CKG_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_REG_GATE_GSPM0IDLE_EN                 BIT(15)
#define BIT_DISP_AHB_REG_GATE_DISPM0IDLE_EN                BIT(14)
#define BIT_DISP_AHB_GSP_NOC_AUTO_CKG_EN                   BIT(13)
#define BIT_DISP_AHB_GSP_NOC_FORCE_CKG_EN                  BIT(12)
#define BIT_DISP_AHB_GSP_MTX_AUTO_CKG_EN                   BIT(11)
#define BIT_DISP_AHB_GSP_MTX_FORCE_CKG_EN                  BIT(10)
#define BIT_DISP_AHB_DISPC_NOC_AUTO_CKG_EN                 BIT(9)
#define BIT_DISP_AHB_DISPC_NOC_FORCE_CKG_EN                BIT(8)
#define BIT_DISP_AHB_DISPC_MTX_AUTO_CKG_EN                 BIT(7)
#define BIT_DISP_AHB_DISPC_MTX_FORCE_CKG_EN                BIT(6)
#define BIT_DISP_AHB_GSP1_FORCE_CKG_EN                     BIT(5)
#define BIT_DISP_AHB_GSP0_FORCE_CKG_EN                     BIT(4)
#define BIT_DISP_AHB_GSP1_AUTO_CKG_EN                      BIT(3)
#define BIT_DISP_AHB_GSP0_AUTO_CKG_EN                      BIT(2)
#define BIT_DISP_AHB_DPHY1_CFG_CKG_EN                      BIT(1)
#define BIT_DISP_AHB_DPHY0_CFG_CKG_EN                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_GEN_BUSMON_CFG
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_GPU_GSP_BUSMON_EN                     BIT(5)
#define BIT_DISP_AHB_GSP1_BUSMON_EN                        BIT(4)
#define BIT_DISP_AHB_GSP0_BUSMON_EN                        BIT(3)
#define BIT_DISP_AHB_TMC_BUSMON_EN                         BIT(2)
#define BIT_DISP_AHB_DISPC1_BUSMON_EN                      BIT(1)
#define BIT_DISP_AHB_DISPC0_BUSMON_EN                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_DISPC_QOS_CFG0
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_QOS_R_GSP1(x)                         (((x) & 0xF) << 28)
#define BIT_DISP_AHB_QOS_W_GSP1(x)                         (((x) & 0xF) << 24)
#define BIT_DISP_AHB_QOS_R_GSP0(x)                         (((x) & 0xF) << 20)
#define BIT_DISP_AHB_QOS_W_GSP0(x)                         (((x) & 0xF) << 16)
#define BIT_DISP_AHB_QOS_R_DISPC1(x)                       (((x) & 0xF) << 12)
#define BIT_DISP_AHB_QOS_W_DISPC1(x)                       (((x) & 0xF) << 8)
#define BIT_DISP_AHB_QOS_R_DISPC0(x)                       (((x) & 0xF) << 4)
#define BIT_DISP_AHB_QOS_W_DISPC0(x)                       (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_DISPC_QOS_CFG1
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_QOS_R_GPU(x)                          (((x) & 0xF) << 4)
#define BIT_DISP_AHB_QOS_W_GPU(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_DISP_AHB_MISC_CTRL
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_DISP_AHB_GSP_NIU_AR_QOS(x)                     (((x) & 0xF) << 16)
#define BIT_DISP_AHB_GSP_NIU_AW_QOS(x)                     (((x) & 0xF) << 12)
#define BIT_DISP_AHB_DISPC_NIU_AR_QOS(x)                   (((x) & 0xF) << 8)
#define BIT_DISP_AHB_DISPC_NIU_AW_QOS(x)                   (((x) & 0xF) << 4)
#define BIT_DISP_AHB_GSP_DDR_ADDR_BIT32                    BIT(1)
#define BIT_DISP_AHB_DISPC_DDR_ADDR_BIT32                  BIT(0)

#endif

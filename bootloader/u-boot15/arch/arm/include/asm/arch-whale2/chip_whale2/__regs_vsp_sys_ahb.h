/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef __H_REGS_VSP_AHB_HEADFILE_H__
#define __H_REGS_VSP_AHB_HEADFILE_H__



#define REG_VSP_AHB_AHB_EB       SCI_ADDR(REGS_VSP_AHB_BASE, 0x0000 )
#define REG_VSP_AHB_AHB_RST      SCI_ADDR(REGS_VSP_AHB_BASE, 0x0004 )
#define REG_VSP_AHB_GEN_CKG_CFG  SCI_ADDR(REGS_VSP_AHB_BASE, 0x0008 )
#define REG_VSP_AHB_MISC_CTRL    SCI_ADDR(REGS_VSP_AHB_BASE, 0x000C )
#define REG_VSP_AHB_VSP_QOS_CFG  SCI_ADDR(REGS_VSP_AHB_BASE, 0x0010 )

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_AHB_AHB_EB
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_AHB_VSP_26M_EB                       BIT(5)
#define BIT_VSP_AHB_VPP_EB                           BIT(4)
#define BIT_VSP_AHB_VSP_ENC_EB                       BIT(3)
#define BIT_VSP_AHB_MMU_EB                           BIT(2)
#define BIT_VSP_AHB_CKG_EB                           BIT(1)
#define BIT_VSP_AHB_VSP_EB                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_AHB_AHB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_AHB_VPP_SOFT_RST                     BIT(5)
#define BIT_VSP_AHB_VSP_ENC_SOFT_RST                 BIT(4)
#define BIT_VSP_AHB_MMU_SOFT_RST                     BIT(3)
#define BIT_VSP_AHB_CKG_SOFT_RST                     BIT(2)
#define BIT_VSP_AHB_OR1200_SOFT_RST                  BIT(1)
#define BIT_VSP_AHB_VSP_SOFT_RST                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_AHB_GEN_CKG_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_AHB_VPP_BUSMON_EN                    BIT(10)
#define BIT_VSP_AHB_VSP_ENC_BUSMON_EN                BIT(9)
#define BIT_VSP_AHB_VSP_BUSMON_EN                    BIT(8)
#define BIT_VSP_AHB_VPP_AXI_CKG_EN                   BIT(2)
#define BIT_VSP_AHB_VSP_ENC_AXI_CKG_EN               BIT(1)
#define BIT_VSP_AHB_VSP_AXI_CKG_EN                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_AHB_MISC_CTRL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_AHB_VSP_NIU_AR_QOS(x)                (((x) & 0xF) << 8)
#define BIT_VSP_AHB_VSP_NIU_AW_QOS(x)                (((x) & 0xF) << 4)
#define BIT_VSP_AHB_VSP_DDR_ADDR_BIT32               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VSP_AHB_VSP_QOS_CFG
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VSP_AHB_QOS_R_VPP(x)                     (((x) & 0xF) << 20)
#define BIT_VSP_AHB_QOS_W_VPP(x)                     (((x) & 0xF) << 16)
#define BIT_VSP_AHB_QOS_R_VSP_ENC(x)                 (((x) & 0xF) << 12)
#define BIT_VSP_AHB_QOS_W_VSP_ENC(x)                 (((x) & 0xF) << 8)
#define BIT_VSP_AHB_QOS_R_VSP(x)                     (((x) & 0xF) << 4)
#define BIT_VSP_AHB_QOS_W_VSP(x)                     (((x) & 0xF))
#endif

/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _GPU_SYS_APB_REG_H
#define _GPU_SYS_APB_REG_H

#define CTL_BASE_GPU_SYS_APB SPRD_GPUREG_BASE


#define REG_GPU_SYS_APB_APB_RST                        ( CTL_BASE_GPU_SYS_APB + 0x0004 )
#define REG_GPU_SYS_APB_GPU_CORE_CLK_CFG               ( CTL_BASE_GPU_SYS_APB + 0x0010 )
#define REG_GPU_SYS_APB_GPU_CORE_CLK_FDIV              ( CTL_BASE_GPU_SYS_APB + 0x0014 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH00_LVLCFG      ( CTL_BASE_GPU_SYS_APB + 0x0020 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH01_LVLCFG      ( CTL_BASE_GPU_SYS_APB + 0x0024 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH02_LVLCFG      ( CTL_BASE_GPU_SYS_APB + 0x0028 )
#define REG_GPU_SYS_APB_GPU_SYS_STATUS_RPT             ( CTL_BASE_GPU_SYS_APB + 0x0040 )
#define REG_GPU_SYS_APB_GPU_SYS_ASYNC_CH0_DEBUG_RPT    ( CTL_BASE_GPU_SYS_APB + 0x0044 )
#define REG_GPU_SYS_APB_GPU_BARRIER_DISABLE            ( CTL_BASE_GPU_SYS_APB + 0x0048 )
#define REG_GPU_SYS_APB_GPU_NIC400_MTX_M0_CFG          ( CTL_BASE_GPU_SYS_APB + 0x0050 )
#define REG_GPU_SYS_APB_GPU_NIC400_MTX_S0_CFG          ( CTL_BASE_GPU_SYS_APB + 0x0054 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH0_CFG          ( CTL_BASE_GPU_SYS_APB + 0x0060 )
#define REG_GPU_SYS_APB_GPU_LPC_NUM_CFG                ( CTL_BASE_GPU_SYS_APB + 0x0064 )
#define REG_GPU_SYS_APB_GPU_NIC400_AXI2APB_S0_CFG      ( CTL_BASE_GPU_SYS_APB + 0x0070 )
#define REG_GPU_SYS_APB_GPU_LPC_AXI2APB_NUM_CFG        ( CTL_BASE_GPU_SYS_APB + 0x0074 )

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_APB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_TOP_SOFT_RST                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_CORE_CLK_CFG
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_CORE_CLK_DIV(x)                                 (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_CORE_CLK_MUX(x)                                 (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_CORE_CLK_FDIV
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_CORE_CLK_FDIV_NUM(x)                            (((x) & 0xF) << 16)
#define BIT_GPU_SYS_APB_GPU_CORE_CLK_FDIV_DENOM(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH00_LVLCFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_AW_CH0(x)                           (((x) & 0xFF) << 24)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_AW_CH0(x)                           (((x) & 0xFF) << 16)
#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_W_CH0(x)                            (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_W_CH0(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH01_LVLCFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_AR_CH0(x)                           (((x) & 0xFF) << 24)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_AR_CH0(x)                           (((x) & 0xFF) << 16)
#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_R_CH0(x)                            (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_R_CH0(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH02_LVLCFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_B_CH0(x)                            (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_B_CH0(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_SYS_STATUS_RPT
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_SYS_ASYNC_TRANS_IDLE_CHL1                       BIT(3)
#define BIT_GPU_SYS_APB_GPU_SYS_ASYNC_TRANS_IDLE_CHL0                       BIT(2)
#define BIT_GPU_SYS_APB_GPU_SYS_ASYNC_BRG_OVERFLOW_CHL1                     BIT(1)
#define BIT_GPU_SYS_APB_GPU_SYS_ASYNC_BRG_OVERFLOW_CHL0                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_SYS_ASYNC_CH0_DEBUG_RPT
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_BRIDGE_DEBUG_SIGNAL_W_CH0_1D(x)                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_BARRIER_DISABLE
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_BARRIER_DISABLE                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NIC400_MTX_M0_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NIC400_MTX_M0_LP_EB                                 BIT(2)
#define BIT_GPU_SYS_APB_NIC400_MTX_M0_LP_FORCE                              BIT(1)
#define BIT_GPU_SYS_APB_NIC400_MTX_M0_ACTIVE_SYNC_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NIC400_MTX_S0_CFG
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NIC400_MTX_S0_LP_EB                                 BIT(2)
#define BIT_GPU_SYS_APB_NIC400_MTX_S0_LP_FORCE                              BIT(1)
#define BIT_GPU_SYS_APB_NIC400_MTX_S0_ACTIVE_SYNC_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH0_CFG
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_ASYNC_BRG_CH0_LP_EB                                 BIT(2)
#define BIT_GPU_SYS_APB_ASYNC_BRG_CH0_LP_FORCE                              BIT(1)
#define BIT_GPU_SYS_APB_ASYNC_BRG_CH0_ACTIVE_SYNC_SEL                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_LPC_NUM_CFG
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_SYS_LP_NUM(x)                                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NIC400_AXI2APB_S0_CFG
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NIC400_AXI2APB_S0_LP_EB                             BIT(2)
#define BIT_GPU_SYS_APB_NIC400_AXI2APB_S0_LP_FORCE                          BIT(1)
#define BIT_GPU_SYS_APB_NIC400_AXI2APB_S0_ACTIVE_SYNC_SEL                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_LPC_AXI2APB_NUM_CFG
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_SYS_AXI2APB_LP_NUM(x)                           (((x) & 0xFFFF))


#endif // _GPU_SYS_APB_REG_H

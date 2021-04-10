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

#define CTL_BASE_GPU_SYS_APB SPRD_GPUREG_APB_BASE


#define REG_GPU_SYS_APB_APB_RST                           ( CTL_BASE_GPU_SYS_APB + 0x0004 )
#define REG_GPU_SYS_APB_GPU_SYS_CLK_CFG                   ( CTL_BASE_GPU_SYS_APB + 0x000C )
#define REG_GPU_SYS_APB_GPU_CORE_CLK_CFG                  ( CTL_BASE_GPU_SYS_APB + 0x0010 )
#define REG_GPU_SYS_APB_GPU_CORE_CLK_FDIV                 ( CTL_BASE_GPU_SYS_APB + 0x0014 )
#define REG_GPU_SYS_APB_GPU_MEM_CLK_CFG                   ( CTL_BASE_GPU_SYS_APB + 0x0018 )
#define REG_GPU_SYS_APB_GPU_MEM_CLK_FDIV                  ( CTL_BASE_GPU_SYS_APB + 0x001C )
#define REG_GPU_SYS_APB_GPU_NIC400_M0_SOCIF_CFG           ( CTL_BASE_GPU_SYS_APB + 0x0020 )
#define REG_GPU_SYS_APB_GPU_NIC400_S0_SOCIF_CFG           ( CTL_BASE_GPU_SYS_APB + 0x0024 )
#define REG_GPU_SYS_APB_GPU_NIC400_S1_SOCIF_CFG           ( CTL_BASE_GPU_SYS_APB + 0x0028 )
#define REG_GPU_SYS_APB_GPU_NIC400_MAIN_SOCIF_CFG         ( CTL_BASE_GPU_SYS_APB + 0x0030 )
#define REG_GPU_SYS_APB_GPU_NOC_QOS_CFG                   ( CTL_BASE_GPU_SYS_APB + 0x0034 )
#define REG_GPU_SYS_APB_GPU_NOC_QOS_HIGH_CFG              ( CTL_BASE_GPU_SYS_APB + 0x0038 )
#define REG_GPU_SYS_APB_GPU_NOC_MEMIF_CFG                 ( CTL_BASE_GPU_SYS_APB + 0x003C )
#define REG_GPU_SYS_APB_GPU_NOC_M0_MEMIF_CFG              ( CTL_BASE_GPU_SYS_APB + 0x0040 )
#define REG_GPU_SYS_APB_GPU_NOC_M1_MEMIF_CFG              ( CTL_BASE_GPU_SYS_APB + 0x0044 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH0_CFG             ( CTL_BASE_GPU_SYS_APB + 0x004C )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH1_CFG             ( CTL_BASE_GPU_SYS_APB + 0x0050 )
#define REG_GPU_SYS_APB_GPU_LPC_NUM_CFG                   ( CTL_BASE_GPU_SYS_APB + 0x0054 )
#define REG_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_CTRL        ( CTL_BASE_GPU_SYS_APB + 0x0060 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH00_LVLCFG         ( CTL_BASE_GPU_SYS_APB + 0x0064 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH01_LVLCFG         ( CTL_BASE_GPU_SYS_APB + 0x0068 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH02_LVLCFG         ( CTL_BASE_GPU_SYS_APB + 0x006C )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH10_LVLCFG         ( CTL_BASE_GPU_SYS_APB + 0x0070 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH11_LVLCFG         ( CTL_BASE_GPU_SYS_APB + 0x0074 )
#define REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH12_LVLCFG         ( CTL_BASE_GPU_SYS_APB + 0x0078 )
#define REG_GPU_SYS_APB_GPU_SYS_STATUS_RPT                ( CTL_BASE_GPU_SYS_APB + 0x0080 )
#define REG_GPU_SYS_APB_GPU_SYS_ASYNC_CH0_DEBUG_RPT       ( CTL_BASE_GPU_SYS_APB + 0x0084 )
#define REG_GPU_SYS_APB_GPU_SYS_ASYNC_CH1_DEBUG_RPT       ( CTL_BASE_GPU_SYS_APB + 0x0088 )
#define REG_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_PULSE_CTRL  ( CTL_BASE_GPU_SYS_APB + 0x008C )
#define REG_GPU_SYS_APB_GPU_SYS_MEMIF_MASK_CTRL           ( CTL_BASE_GPU_SYS_APB + 0x0090 )
#define REG_GPU_SYS_APB_GPU_NIC400_S0_CFG                 ( CTL_BASE_GPU_SYS_APB + 0x0094 )
#define REG_GPU_SYS_APB_GPU_RESERVED_0                    ( CTL_BASE_GPU_SYS_APB + 0x0098 )
#define REG_GPU_SYS_APB_GPU_RESERVED_1                    ( CTL_BASE_GPU_SYS_APB + 0x009C )

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_APB_RST
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_PHANTOM_SOFT_RST                                   BIT(3)
#define BIT_GPU_SYS_APB_GPU_MEM_SOFT_RST                                       BIT(2)
#define BIT_GPU_SYS_APB_GPU_SYS_SOFT_RST                                       BIT(1)
#define BIT_GPU_SYS_APB_GPU_CORE_SOFT_RST                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_SYS_CLK_CFG
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_SYS_CLK_MUX                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_CORE_CLK_CFG
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_CORE_CLK_DIV(x)                                    (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_CORE_CLK_MUX(x)                                    (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_CORE_CLK_FDIV
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_CORE_CLK_FDIV_NUM(x)                               (((x) & 0xF) << 16)
#define BIT_GPU_SYS_APB_GPU_CORE_CLK_FDIV_DENOM(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_MEM_CLK_CFG
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_MEM_CLK_DIV(x)                                     (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_MEM_CLK_MUX(x)                                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_MEM_CLK_FDIV
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_MEM_CLK_FDIV_NUM(x)                                (((x) & 0xF) << 16)
#define BIT_GPU_SYS_APB_GPU_MEM_CLK_FDIV_DENOM(x)                              (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NIC400_M0_SOCIF_CFG
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NIC400_SOCIF_M0_LP_EB                                  BIT(2)
#define BIT_GPU_SYS_APB_NIC400_SOCIF_M0_LP_FORCE                               BIT(1)
#define BIT_GPU_SYS_APB_NIC400_SOCIF_M0_ACTIVE_SYNC_SEL                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NIC400_S0_SOCIF_CFG
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NIC400_SOCIF_S0_LP_EB                                  BIT(2)
#define BIT_GPU_SYS_APB_NIC400_SOCIF_S0_LP_FORCE                               BIT(1)
#define BIT_GPU_SYS_APB_NIC400_SOCIF_S0_ACTIVE_SYNC_SEL                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NIC400_S1_SOCIF_CFG
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NIC400_SOCIF_S1_LP_EB                                  BIT(2)
#define BIT_GPU_SYS_APB_NIC400_SOCIF_S1_LP_FORCE                               BIT(1)
#define BIT_GPU_SYS_APB_NIC400_SOCIF_S1_ACTIVE_SYNC_SEL                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NIC400_MAIN_SOCIF_CFG
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NIC400_SOCIF_MAIN_LP_EB                                BIT(2)
#define BIT_GPU_SYS_APB_NIC400_SOCIF_MAIN_LP_FORCE                             BIT(1)
#define BIT_GPU_SYS_APB_NIC400_SOCIF_MAIN_ACTIVE_SYNC_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NOC_QOS_CFG
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_AXI_AWQOS_MEMIF1(x)                                    (((x) & 0xF) << 12)
#define BIT_GPU_SYS_APB_AXI_ARQOS_MEMIF1(x)                                    (((x) & 0xF) << 8)
#define BIT_GPU_SYS_APB_AXI_AWQOS_MEMIF0(x)                                    (((x) & 0xF) << 4)
#define BIT_GPU_SYS_APB_AXI_ARQOS_MEMIF0(x)                                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NOC_QOS_HIGH_CFG
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_AXI_AWQOS_HIGH_MEMIF1(x)                               (((x) & 0xF) << 12)
#define BIT_GPU_SYS_APB_AXI_ARQOS_HIGH_MEMIF1(x)                               (((x) & 0xF) << 8)
#define BIT_GPU_SYS_APB_AXI_AWQOS_HIGH_MEMIF0(x)                               (((x) & 0xF) << 4)
#define BIT_GPU_SYS_APB_AXI_ARQOS_HIGH_MEMIF0(x)                               (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NOC_MEMIF_CFG
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NOC_MEMIF_INTERLEAVE_SIZE_SEL                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NOC_M0_MEMIF_CFG
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NOC_MEMIF_M0_LP_EB                                     BIT(2)
#define BIT_GPU_SYS_APB_NOC_MEMIF_M0_LP_FORCE                                  BIT(1)
#define BIT_GPU_SYS_APB_NOC_MEMIF_M0_ACTIVE_SYNC_SEL                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NOC_M1_MEMIF_CFG
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NOC_MEMIF_M1_LP_EB                                     BIT(2)
#define BIT_GPU_SYS_APB_NOC_MEMIF_M1_LP_FORCE                                  BIT(1)
#define BIT_GPU_SYS_APB_NOC_MEMIF_M1_ACTIVE_SYNC_SEL                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH0_CFG
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_ASYNC_BRG_CH0_LP_EB                                    BIT(2)
#define BIT_GPU_SYS_APB_ASYNC_BRG_CH0_LP_FORCE                                 BIT(1)
#define BIT_GPU_SYS_APB_ASYNC_BRG_CH0_ACTIVE_SYNC_SEL                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH1_CFG
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_ASYNC_BRG_CH1_LP_EB                                    BIT(2)
#define BIT_GPU_SYS_APB_ASYNC_BRG_CH1_LP_FORCE                                 BIT(1)
#define BIT_GPU_SYS_APB_ASYNC_BRG_CH1_ACTIVE_SYNC_SEL                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_LPC_NUM_CFG
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_SYS_LP_NUM(x)                                      (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_CTRL
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_RESERVE(x)                       (((x) & 0xF) << 13)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_TEST_MODE_EN                           BIT(12)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_TEST_PULSE                             BIT(11)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_EN                               BIT(10)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_LATCH_EN                         BIT(9)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_CTRL(x)                          (((x) & 0x7) << 6)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_CURRENT(x)                       (((x) & 0x3) << 4)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_RANGE_SEL(x)                     (((x) & 0x3) << 2)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_OUT                              BIT(1)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_TEST_OUT                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH00_LVLCFG
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_AW_CH0(x)                              (((x) & 0xFF) << 24)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_AW_CH0(x)                              (((x) & 0xFF) << 16)
#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_W_CH0(x)                               (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_W_CH0(x)                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH01_LVLCFG
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_AR_CH0(x)                              (((x) & 0xFF) << 24)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_AR_CH0(x)                              (((x) & 0xFF) << 16)
#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_R_CH0(x)                               (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_R_CH0(x)                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH02_LVLCFG
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_B_CH0(x)                               (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_B_CH0(x)                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH10_LVLCFG
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_AW_CH1(x)                              (((x) & 0xFF) << 24)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_AW_CH1(x)                              (((x) & 0xFF) << 16)
#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_W_CH1(x)                               (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_W_CH1(x)                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH11_LVLCFG
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_AR_CH1(x)                              (((x) & 0xFF) << 24)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_AR_CH1(x)                              (((x) & 0xFF) << 16)
#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_R_CH1(x)                               (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_R_CH1(x)                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_ASYNC_BRG_CH12_LVLCFG
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_FIFO_AF_LVL_B_CH1(x)                               (((x) & 0xFF) << 8)
#define BIT_GPU_SYS_APB_GPU_FIFO_AE_LVL_B_CH1(x)                               (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_SYS_STATUS_RPT
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_SYS_ASYNC_TRANS_IDLE_CHL1                          BIT(3)
#define BIT_GPU_SYS_APB_GPU_SYS_ASYNC_TRANS_IDLE_CHL0                          BIT(2)
#define BIT_GPU_SYS_APB_GPU_SYS_ASYNC_BRG_OVERFLOW_CHL1                        BIT(1)
#define BIT_GPU_SYS_APB_GPU_SYS_ASYNC_BRG_OVERFLOW_CHL0                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_SYS_ASYNC_CH0_DEBUG_RPT
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_BRIDGE_DEBUG_SIGNAL_W_CH0_1D(x)                        (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_SYS_ASYNC_CH1_DEBUG_RPT
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_BRIDGE_DEBUG_SIGNAL_W_CH1_1D(x)                        (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_PULSE_CTRL
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_PULSE_MODE                       BIT(5)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_TEST_PULSE_SEL(x)                (((x) & 0xF) << 1)
#define BIT_GPU_SYS_APB_ANALOG_V_SENSOR_VDROP_TEST_TRIG                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_SYS_MEMIF_MASK_CTRL
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_MEMIF_MASK                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_NIC400_S0_CFG
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_NIC400_S0_LP_EB                                        BIT(2)
#define BIT_GPU_SYS_APB_NIC400_S0_LP_FORCE                                     BIT(1)
#define BIT_GPU_SYS_APB_NIC400_S0_ACTIVE_SYNC_SEL                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_RESERVED_0
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_RESERVED_0(x)                                      (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_GPU_SYS_APB_GPU_RESERVED_1
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_GPU_SYS_APB_GPU_RESERVED_1(x)                                      (((x) & 0xFFFFFFFF))


#endif // _GPU_SYS_APB_REG_H

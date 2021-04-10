/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _COMMON_APB_REG_H
#define _COMMON_APB_REG_H

#define CTL_BASE_COMMON_APB SPRD_COMMON_APB


#define REG_COMMON_APB_VSP_FIFO_CH0_1                  ( CTL_BASE_COMMON_APB + 0x00A0 )
#define REG_COMMON_APB_VSP_FIFO_CH0_2                  ( CTL_BASE_COMMON_APB + 0x00A4 )
#define REG_COMMON_APB_VSP_FIFO_CH1_1                  ( CTL_BASE_COMMON_APB + 0x00AC )
#define REG_COMMON_APB_VSP_FIFO_CH1_2                  ( CTL_BASE_COMMON_APB + 0x00B0 )
#define REG_COMMON_APB_CAM_FIFO_CH0_1                  ( CTL_BASE_COMMON_APB + 0x00B8 )
#define REG_COMMON_APB_CAM_FIFO_CH0_2                  ( CTL_BASE_COMMON_APB + 0x00BC )
#define REG_COMMON_APB_CAM_FIFO_CH1_1                  ( CTL_BASE_COMMON_APB + 0x00C0 )
#define REG_COMMON_APB_CAM_FIFO_CH1_2                  ( CTL_BASE_COMMON_APB + 0x00C4 )
#define REG_COMMON_APB_GPU_FIFO_CH0_1                  ( CTL_BASE_COMMON_APB + 0x00CC )
#define REG_COMMON_APB_GPU_FIFO_CH0_2                  ( CTL_BASE_COMMON_APB + 0x00D0 )
#define REG_COMMON_APB_GPU_FIFO_CH1_1                  ( CTL_BASE_COMMON_APB + 0x00D4 )
#define REG_COMMON_APB_GPU_FIFO_CH1_2                  ( CTL_BASE_COMMON_APB + 0x00D8 )
#define REG_COMMON_APB_AP_FIFO_CH_1                    ( CTL_BASE_COMMON_APB + 0x00E0 )
#define REG_COMMON_APB_AP_FIFO_CH_2                    ( CTL_BASE_COMMON_APB + 0x00E4 )
#define REG_COMMON_APB_PUBCP_FIFO_CH_1                 ( CTL_BASE_COMMON_APB + 0x00E8 )
#define REG_COMMON_APB_PUBCP_FIFO_CH_2                 ( CTL_BASE_COMMON_APB + 0x00EC )
#define REG_COMMON_APB_PUBCP_FIFO_CH_3                 ( CTL_BASE_COMMON_APB + 0x00F0 )
#define REG_COMMON_APB_PLL_BG_CFG                      ( CTL_BASE_COMMON_APB + 0x0108 )
#define REG_COMMON_APB_BIA_R_FIFO_CH_1                 ( CTL_BASE_COMMON_APB + 0x0110 )
#define REG_COMMON_APB_BIA_R_FIFO_CH_2                 ( CTL_BASE_COMMON_APB + 0x0114 )
#define REG_COMMON_APB_BIA_W_FIFO_CH_1                 ( CTL_BASE_COMMON_APB + 0x0118 )
#define REG_COMMON_APB_BIA_W_FIFO_CH_2                 ( CTL_BASE_COMMON_APB + 0x011C )
#define REG_COMMON_APB_SP_CFG_BUS                      ( CTL_BASE_COMMON_APB + 0x0124 )
#define REG_COMMON_APB_SUB_SYS_DEBUG_BUS_SEL_0         ( CTL_BASE_COMMON_APB + 0x01C0 )
#define REG_COMMON_APB_SUB_SYS_DEBUG_BUS_SEL_1         ( CTL_BASE_COMMON_APB + 0x01C4 )
#define REG_COMMON_APB_GLB_DEBUG_BUS_SEL               ( CTL_BASE_COMMON_APB + 0x01C8 )
#define REG_COMMON_APB_SP_EIC_IN_SEL                   ( CTL_BASE_COMMON_APB + 0x01F4 )
#define REG_COMMON_APB_PRE_DBG_BUS_5_0_SEL             ( CTL_BASE_COMMON_APB + 0x0214 )
#define REG_COMMON_APB_PRE_DBG_BUS_11_6_SEL            ( CTL_BASE_COMMON_APB + 0x0218 )
#define REG_COMMON_APB_PRE_DBG_BUS_17_12_SEL           ( CTL_BASE_COMMON_APB + 0x021C )
#define REG_COMMON_APB_PRE_DBG_BUS_23_18_SEL           ( CTL_BASE_COMMON_APB + 0x0220 )
#define REG_COMMON_APB_PRE_DBG_BUS_29_24_SEL           ( CTL_BASE_COMMON_APB + 0x0224 )
#define REG_COMMON_APB_PRE_DBG_BUS_31_30_SEL           ( CTL_BASE_COMMON_APB + 0x0228 )
#define REG_COMMON_APB_SUB_SYS_DBG_SIG0                ( CTL_BASE_COMMON_APB + 0x029C )
#define REG_COMMON_APB_SUB_SYS_DBG_SIG1                ( CTL_BASE_COMMON_APB + 0x02A0 )
#define REG_COMMON_APB_SUB_SYS_DBG_SIG2                ( CTL_BASE_COMMON_APB + 0x02A4 )
#define REG_COMMON_APB_SUB_SYS_DBG_SIG3                ( CTL_BASE_COMMON_APB + 0x02A8 )
#define REG_COMMON_APB_SUB_SYS_DBG_SIG4                ( CTL_BASE_COMMON_APB + 0x02AC )
#define REG_COMMON_APB_SUB_SYS_DBG_SIG5                ( CTL_BASE_COMMON_APB + 0x02B0 )
#define REG_COMMON_APB_SUB_SYS_DBG_SIG6                ( CTL_BASE_COMMON_APB + 0x02B4 )
#define REG_COMMON_APB_SUB_SYS_DBG_SIG7                ( CTL_BASE_COMMON_APB + 0x02B8 )
#define REG_COMMON_APB_DEBUG_SUBSYS_SEL                ( CTL_BASE_COMMON_APB + 0x02BC )
#define REG_COMMON_APB_WTLCP2AON_R_FIFO_CH_1           ( CTL_BASE_COMMON_APB + 0x02C4 )
#define REG_COMMON_APB_WTLCP2AON_R_FIFO_CH0_2          ( CTL_BASE_COMMON_APB + 0x02C8 )
#define REG_COMMON_APB_WTLCP2AON_W_FIFO_CH_1           ( CTL_BASE_COMMON_APB + 0x02CC )
#define REG_COMMON_APB_WTLCP2AON_W_FIFO_CH0_2          ( CTL_BASE_COMMON_APB + 0x02D0 )
#define REG_COMMON_APB_AGCP2AON_R_FIFO_CH_1            ( CTL_BASE_COMMON_APB + 0x02D4 )
#define REG_COMMON_APB_AGCP2AON_R_FIFO_CH0_2           ( CTL_BASE_COMMON_APB + 0x02D8 )
#define REG_COMMON_APB_AGCP2AON_W_FIFO_CH_1            ( CTL_BASE_COMMON_APB + 0x02DC )
#define REG_COMMON_APB_AGCP2AON_W_FIFO_CH0_2           ( CTL_BASE_COMMON_APB + 0x02E0 )
#define REG_COMMON_APB_PUBCP2AON_R_FIFO_CH_1           ( CTL_BASE_COMMON_APB + 0x02E4 )
#define REG_COMMON_APB_PUBCP2AON_R_FIFO_CH0_2          ( CTL_BASE_COMMON_APB + 0x02E8 )
#define REG_COMMON_APB_PUBCP2AON_W_FIFO_CH_1           ( CTL_BASE_COMMON_APB + 0x02EC )
#define REG_COMMON_APB_PUBCP2AON_W_FIFO_CH0_2          ( CTL_BASE_COMMON_APB + 0x02F0 )
#define REG_COMMON_APB_AON2PUBCP_R_FIFO_CH_1           ( CTL_BASE_COMMON_APB + 0x02F4 )
#define REG_COMMON_APB_AON2PUBCP_R_FIFO_CH0_2          ( CTL_BASE_COMMON_APB + 0x02F8 )
#define REG_COMMON_APB_AON2PUBCP_W_FIFO_CH_1           ( CTL_BASE_COMMON_APB + 0x02FC )
#define REG_COMMON_APB_AON2PUBCP_W_FIFO_CH0_2          ( CTL_BASE_COMMON_APB + 0x0300 )
#define REG_COMMON_APB_AON2AGCP_R_FIFO_CH_1            ( CTL_BASE_COMMON_APB + 0x0304 )
#define REG_COMMON_APB_AON2AGCP_R_FIFO_CH0_2           ( CTL_BASE_COMMON_APB + 0x0308 )
#define REG_COMMON_APB_AON2AGCP_W_FIFO_CH_1            ( CTL_BASE_COMMON_APB + 0x030C )
#define REG_COMMON_APB_AON2AGCP_W_FIFO_CH0_2           ( CTL_BASE_COMMON_APB + 0x0310 )
#define REG_COMMON_APB_AON2PUB0_R_FIFO_CH_1            ( CTL_BASE_COMMON_APB + 0x0314 )
#define REG_COMMON_APB_AON2PUB0_R_FIFO_CH0_2           ( CTL_BASE_COMMON_APB + 0x031C )
#define REG_COMMON_APB_AON2PUB0_W_FIFO_CH_1            ( CTL_BASE_COMMON_APB + 0x0320 )
#define REG_COMMON_APB_AON2PUB0_W_FIFO_CH0_2           ( CTL_BASE_COMMON_APB + 0x0324 )
#define REG_COMMON_APB_AON2PUB1_R_FIFO_CH_1            ( CTL_BASE_COMMON_APB + 0x0328 )
#define REG_COMMON_APB_AON2PUB1_R_FIFO_CH0_2           ( CTL_BASE_COMMON_APB + 0x032C )
#define REG_COMMON_APB_AON2PUB1_W_FIFO_CH_1            ( CTL_BASE_COMMON_APB + 0x0330 )
#define REG_COMMON_APB_AON2PUB1_W_FIFO_CH0_2           ( CTL_BASE_COMMON_APB + 0x0334 )
#define REG_COMMON_APB_AON_APB_RSV                     ( CTL_BASE_COMMON_APB + 0x30F0 )
#define REG_COMMON_APB_AON_OSC_FUNC_CTRL               ( CTL_BASE_COMMON_APB + 0x3104 )
#define REG_COMMON_APB_VDROP_TEST_CTRL                 ( CTL_BASE_COMMON_APB + 0x3190 )
#define REG_COMMON_APB_PROBE_CAL_CTRL                  ( CTL_BASE_COMMON_APB + 0x3194 )
#define REG_COMMON_APB_AUX0_CAL_CTRL                   ( CTL_BASE_COMMON_APB + 0x3198 )
#define REG_COMMON_APB_AUX1_CAL_CTRL                   ( CTL_BASE_COMMON_APB + 0x319C )
#define REG_COMMON_APB_AUX2_CAL_CTRL                   ( CTL_BASE_COMMON_APB + 0x31A0 )
#define REG_COMMON_APB_PLL_FREQ_CAL_CFG                ( CTL_BASE_COMMON_APB + 0x31A4 )
#define REG_COMMON_APB_PROBE_RESULT                    ( CTL_BASE_COMMON_APB + 0x31A8 )
#define REG_COMMON_APB_AUX0_RESULT                     ( CTL_BASE_COMMON_APB + 0x31AC )
#define REG_COMMON_APB_AUX1_RESULT                     ( CTL_BASE_COMMON_APB + 0x31B0 )
#define REG_COMMON_APB_AUX2_RESULT                     ( CTL_BASE_COMMON_APB + 0x31B4 )
#define REG_COMMON_APB_PLL_TEST_FLAG                   ( CTL_BASE_COMMON_APB + 0x31B8 )
#define REG_COMMON_APB_WTL_GSM_TX_BYP                  ( CTL_BASE_COMMON_APB + 0x31BC )
#define REG_COMMON_APB_RCO100M_CAL_TEST                ( CTL_BASE_COMMON_APB + 0x31C0 )
#define REG_COMMON_APB_INT_REQ_WTL_GSM_TX              ( CTL_BASE_COMMON_APB + 0x31C4 )
#define REG_COMMON_APB_INT_REQ_ITHM1_ALERT             ( CTL_BASE_COMMON_APB + 0x31C8 )
#define REG_COMMON_APB_DSI_MUX                         ( CTL_BASE_COMMON_APB + 0x31CC )
#define REG_COMMON_APB_GPU_MEM_ECO                     ( CTL_BASE_COMMON_APB + 0x31D0 )
#define REG_COMMON_APB_ASYNC_BRIDGE_OVERFLOW_AND_IDLE  ( CTL_BASE_COMMON_APB + 0x31D4 )
#define REG_COMMON_APB_UFS_SLICE_CTRL                  ( CTL_BASE_COMMON_APB + 0x31D8 )
#define REG_COMMON_APB_COMMON_DUMMY_RW0                ( CTL_BASE_COMMON_APB + 0x31DC )
#define REG_COMMON_APB_COMMON_DUMMY_RW1                ( CTL_BASE_COMMON_APB + 0x31E0 )
#define REG_COMMON_APB_COMMON_DUMMY_RW2                ( CTL_BASE_COMMON_APB + 0x31E4 )
#define REG_COMMON_APB_COMMON_DUMMY_RW3                ( CTL_BASE_COMMON_APB + 0x31E8 )
#define REG_COMMON_APB_COMMON_DUMMY_RO0                ( CTL_BASE_COMMON_APB + 0x31EC )
#define REG_COMMON_APB_COMMON_DUMMY_RO1                ( CTL_BASE_COMMON_APB + 0x31F0 )
#define REG_COMMON_APB_COMMON_DUMMY_RO2                ( CTL_BASE_COMMON_APB + 0x31F4 )
#define REG_COMMON_APB_COMMON_DUMMY_RO3                ( CTL_BASE_COMMON_APB + 0x31F8 )

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_VSP_FIFO_CH0_1
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_AW_CH0(x)                          (((x) & 0xF) << 28)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_AW_CH0(x)                          (((x) & 0xF) << 24)
#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_W_CH0(x)                           (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_W_CH0(x)                           (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_B_CH0(x)                           (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_B_CH0(x)                           (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_VSP_FIFO_CH0_2
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_R_CH0(x)                           (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_R_CH0(x)                           (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_BADDTION_S_VSP_PUB0(x)                             (((x) & 0xF) << 12)
#define BIT_COMMON_APB_RADDTION_S_VSP_PUB0(x)                             (((x) & 0xF) << 8)
#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_AR_CH0(x)                          (((x) & 0xF) << 4)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_AR_CH0(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_VSP_FIFO_CH1_1
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_AW_CH1(x)                          (((x) & 0xF) << 28)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_AW_CH1(x)                          (((x) & 0xF) << 24)
#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_W_CH1(x)                           (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_W_CH1(x)                           (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_B_CH1(x)                           (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_B_CH1(x)                           (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_VSP_FIFO_CH1_2
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_R_CH1(x)                           (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_R_CH1(x)                           (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_BADDTION_S_VSP_PUB1(x)                             (((x) & 0xF) << 12)
#define BIT_COMMON_APB_RADDTION_S_VSP_PUB1(x)                             (((x) & 0xF) << 8)
#define BIT_COMMON_APB_VSP_FIFO_AF_LVL_AR_CH1(x)                          (((x) & 0xF) << 4)
#define BIT_COMMON_APB_VSP_FIFO_AE_LVL_AR_CH1(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_CAM_FIFO_CH0_1
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_AW_CH0(x)                          (((x) & 0xF) << 28)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_AW_CH0(x)                          (((x) & 0xF) << 24)
#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_W_CH0(x)                           (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_W_CH0(x)                           (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_B_CH0(x)                           (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_B_CH0(x)                           (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_CAM_FIFO_CH0_2
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_R_CH0(x)                           (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_R_CH0(x)                           (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_BADDTION_S_CAM_PUB0(x)                             (((x) & 0xF) << 12)
#define BIT_COMMON_APB_RADDTION_S_CAM_PUB0(x)                             (((x) & 0xF) << 8)
#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_AR_CH0(x)                          (((x) & 0xF) << 4)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_AR_CH0(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_CAM_FIFO_CH1_1
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_AW_CH1(x)                          (((x) & 0xF) << 28)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_AW_CH1(x)                          (((x) & 0xF) << 24)
#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_W_CH1(x)                           (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_W_CH1(x)                           (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_B_CH1(x)                           (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_B_CH1(x)                           (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_CAM_FIFO_CH1_2
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_R_CH1(x)                           (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_R_CH1(x)                           (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_BADDTION_S_CAM_PUB1(x)                             (((x) & 0xF) << 12)
#define BIT_COMMON_APB_RADDTION_S_CAM_PUB1(x)                             (((x) & 0xF) << 8)
#define BIT_COMMON_APB_CAM_FIFO_AF_LVL_AR_CH1(x)                          (((x) & 0xF) << 4)
#define BIT_COMMON_APB_CAM_FIFO_AE_LVL_AR_CH1(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_GPU_FIFO_CH0_1
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_AW_CH0(x)                          (((x) & 0xF) << 28)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_W_CH0(x)                           (((x) & 0x1F) << 23)
#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_W_CH0(x)                           (((x) & 0x1F) << 18)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_B_CH0(x)                           (((x) & 0x1F) << 13)
#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_B_CH0(x)                           (((x) & 0x1F) << 8)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_AR_CH0(x)                          (((x) & 0xF) << 4)
#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_AR_CH0(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_GPU_FIFO_CH0_2
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_BADDTION_S_GPU_PUB0(x)                             (((x) & 0xF) << 20)
#define BIT_COMMON_APB_RADDTION_S_GPU_PUB0(x)                             (((x) & 0xF) << 16)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_AW_CH0(x)                          (((x) & 0xF) << 12)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_R_CH0(x)                           (((x) & 0x1F) << 5)
#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_R_CH0(x)                           (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_GPU_FIFO_CH1_1
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_AW_CH1(x)                          (((x) & 0xF) << 28)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_W_CH1(x)                           (((x) & 0x1F) << 23)
#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_W_CH1(x)                           (((x) & 0x1F) << 18)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_B_CH1(x)                           (((x) & 0x1F) << 13)
#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_B_CH1(x)                           (((x) & 0x1F) << 8)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_AR_CH1(x)                          (((x) & 0xF) << 4)
#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_AR_CH1(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_GPU_FIFO_CH1_2
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_BADDTION_S_GPU_PUB1(x)                             (((x) & 0xF) << 20)
#define BIT_COMMON_APB_RADDTION_S_GPU_PUB1(x)                             (((x) & 0xF) << 16)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_AW_CH1(x)                          (((x) & 0xF) << 12)
#define BIT_COMMON_APB_GPU_FIFO_AF_LVL_R_CH1(x)                           (((x) & 0x1F) << 5)
#define BIT_COMMON_APB_GPU_FIFO_AE_LVL_R_CH1(x)                           (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AP_FIFO_CH_1
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AP_FIFO_AF_LVL_AW_CH(x)                            (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AP_FIFO_AE_LVL_AW_CH(x)                            (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AP_FIFO_AF_LVL_W_CH(x)                             (((x) & 0xF) << 20)
#define BIT_COMMON_APB_AP_FIFO_AE_LVL_W_CH(x)                             (((x) & 0xF) << 16)
#define BIT_COMMON_APB_AP_FIFO_AF_LVL_B_CH(x)                             (((x) & 0xF) << 12)
#define BIT_COMMON_APB_AP_FIFO_AE_LVL_B_CH(x)                             (((x) & 0xF) << 8)
#define BIT_COMMON_APB_AP_FIFO_AF_LVL_AR_CH(x)                            (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AP_FIFO_AE_LVL_AR_CH(x)                            (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AP_FIFO_CH_2
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AP_FIFO_AF_LVL_R_CH(x)                             (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AP_FIFO_AE_LVL_R_CH(x)                             (((x) & 0xF) << 24)
#define BIT_COMMON_APB_BADDTION_S_AP_PUB1(x)                              (((x) & 0xF) << 20)
#define BIT_COMMON_APB_RADDTION_S_AP_PUB1(x)                              (((x) & 0xF) << 16)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PUBCP_FIFO_CH_1
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PUBCP_FIFO_AF_LVL_AW_CH(x)                         (((x) & 0xF) << 28)
#define BIT_COMMON_APB_PUBCP_FIFO_AE_LVL_AW_CH(x)                         (((x) & 0xF) << 24)
#define BIT_COMMON_APB_PUBCP_FIFO_AF_LVL_W_CH(x)                          (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_PUBCP_FIFO_AE_LVL_W_CH(x)                          (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_PUBCP_FIFO_AF_LVL_B_CH(x)                          (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_PUBCP_FIFO_AE_LVL_B_CH(x)                          (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PUBCP_FIFO_CH_2
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PUBCP_FIFO_AF_LVL_R_CH(x)                          (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_PUBCP_FIFO_AE_LVL_R_CH(x)                          (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_BADDTION_S_PUBCP_PUB0(x)                           (((x) & 0xFF) << 12)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PUBCP_FIFO_CH_3
// Register Offset : 0x00F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_RADDTION_S_PUBCP_PUB0(x)                           (((x) & 0xFF) << 8)
#define BIT_COMMON_APB_PUBCP_FIFO_AF_LVL_AR_CH(x)                         (((x) & 0xF) << 4)
#define BIT_COMMON_APB_PUBCP_FIFO_AE_LVL_AR_CH(x)                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PLL_BG_CFG
// Register Offset : 0x0108
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PLL_BG_RSV(x)                                      (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_BIA_R_FIFO_CH_1
// Register Offset : 0x0110
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_BIA_R_FIFO_AF_LVL_AW_CH(x)                         (((x) & 0xF) << 28)
#define BIT_COMMON_APB_BIA_R_FIFO_AE_LVL_AW_CH(x)                         (((x) & 0xF) << 24)
#define BIT_COMMON_APB_BIA_R_FIFO_AF_LVL_W_CH(x)                          (((x) & 0xF) << 20)
#define BIT_COMMON_APB_BIA_R_FIFO_AE_LVL_W_CH(x)                          (((x) & 0xF) << 16)
#define BIT_COMMON_APB_BIA_R_FIFO_AF_LVL_B_CH(x)                          (((x) & 0xF) << 12)
#define BIT_COMMON_APB_BIA_R_FIFO_AE_LVL_B_CH(x)                          (((x) & 0xF) << 8)
#define BIT_COMMON_APB_BIA_R_FIFO_AF_LVL_AR_CH(x)                         (((x) & 0xF) << 4)
#define BIT_COMMON_APB_BIA_R_FIFO_AE_LVL_AR_CH(x)                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_BIA_R_FIFO_CH_2
// Register Offset : 0x0114
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_BIA_R_FIFO_AF_LVL_R_CH(x)                          (((x) & 0xF) << 28)
#define BIT_COMMON_APB_BIA_R_FIFO_AE_LVL_R_CH(x)                          (((x) & 0xF) << 24)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_BIA_W_FIFO_CH_1
// Register Offset : 0x0118
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_BIA_W_FIFO_AF_LVL_AW_CH(x)                         (((x) & 0xF) << 28)
#define BIT_COMMON_APB_BIA_W_FIFO_AE_LVL_AW_CH(x)                         (((x) & 0xF) << 24)
#define BIT_COMMON_APB_BIA_W_FIFO_AF_LVL_W_CH(x)                          (((x) & 0xF) << 20)
#define BIT_COMMON_APB_BIA_W_FIFO_AE_LVL_W_CH(x)                          (((x) & 0xF) << 16)
#define BIT_COMMON_APB_BIA_W_FIFO_AF_LVL_B_CH(x)                          (((x) & 0xF) << 12)
#define BIT_COMMON_APB_BIA_W_FIFO_AE_LVL_B_CH(x)                          (((x) & 0xF) << 8)
#define BIT_COMMON_APB_BIA_W_FIFO_AF_LVL_AR_CH(x)                         (((x) & 0xF) << 4)
#define BIT_COMMON_APB_BIA_W_FIFO_AE_LVL_AR_CH(x)                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_BIA_W_FIFO_CH_2
// Register Offset : 0x011C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_BIA_W_FIFO_AF_LVL_R_CH(x)                          (((x) & 0xF) << 28)
#define BIT_COMMON_APB_BIA_W_FIFO_AE_LVL_R_CH(x)                          (((x) & 0xF) << 24)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SP_CFG_BUS
// Register Offset : 0x0124
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_ARM7_AHB_CLK_SOFT_EN                               BIT(7)
#define BIT_COMMON_APB_CM4_SLEEPING_STAT                                  BIT(6)
#define BIT_COMMON_APB_CM4_LOCKUP_STAT                                    BIT(5)
#define BIT_COMMON_APB_CM4_SOFT_MPUDIS                                    BIT(4)
#define BIT_COMMON_APB_MMTX_SLEEP_CM4_PUB_WR                              BIT(3)
#define BIT_COMMON_APB_MMTX_SLEEP_CM4_PUB_RD                              BIT(2)
#define BIT_COMMON_APB_INT_REQ_CM4_SOFT                                   BIT(1)
#define BIT_COMMON_APB_SP_CFG_BUS_SLEEP                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DEBUG_BUS_SEL_0
// Register Offset : 0x01C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_WTLCP_DEBUG_BUS_SELECT(x)                          (((x) & 0xF) << 28)
#define BIT_COMMON_APB_PUBCP_DEBUG_BUS_SELECT(x)                          (((x) & 0xF) << 24)
#define BIT_COMMON_APB_DISP_DEBUG_BUS_SELECT(x)                           (((x) & 0xF) << 20)
#define BIT_COMMON_APB_CAM_DEBUG_BUS_SELECT(x)                            (((x) & 0xF) << 16)
#define BIT_COMMON_APB_VSP_DEBUG_BUS_SELECT(x)                            (((x) & 0xF) << 12)
#define BIT_COMMON_APB_GPU_DEBUG_BUS_SELECT(x)                            (((x) & 0xF) << 8)
#define BIT_COMMON_APB_AP_DEBUG_BUS_SELECT(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DEBUG_BUS_SEL_1
// Register Offset : 0x01C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_MDAR_LVDSRF_DBG_SEL(x)                             (((x) & 0xF) << 20)
#define BIT_COMMON_APB_MDAR_DEBUG_BUS_SELECT(x)                           (((x) & 0xF) << 16)
#define BIT_COMMON_APB_PUB1_DEBUG_BUS_SELECT(x)                           (((x) & 0xF) << 12)
#define BIT_COMMON_APB_PUB0_DEBUG_BUS_SELECT(x)                           (((x) & 0xF) << 8)
#define BIT_COMMON_APB_AON_DEBUG_BUS_SELECT(x)                            (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AGCP_DEBUG_BUS_SELECT(x)                           (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_GLB_DEBUG_BUS_SEL
// Register Offset : 0x01C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_DEBUG_SUBSYS_SELECT(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SP_EIC_IN_SEL
// Register Offset : 0x01F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_SP_EIC_IN_7_SEL                                    BIT(7)
#define BIT_COMMON_APB_SP_EIC_IN_6_SEL                                    BIT(6)
#define BIT_COMMON_APB_SP_EIC_IN_5_SEL                                    BIT(5)
#define BIT_COMMON_APB_SP_EIC_IN_4_SEL                                    BIT(4)
#define BIT_COMMON_APB_SP_EIC_IN_3_SEL                                    BIT(3)
#define BIT_COMMON_APB_SP_EIC_IN_2_SEL                                    BIT(2)
#define BIT_COMMON_APB_SP_EIC_IN_1_SEL                                    BIT(1)
#define BIT_COMMON_APB_SP_EIC_IN_0_SEL                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PRE_DBG_BUS_5_0_SEL
// Register Offset : 0x0214
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_DBG_BUS5_SEL(x)                                (((x) & 0x1F) << 25)
#define BIT_COMMON_APB_PRE_DBG_BUS4_SEL(x)                                (((x) & 0x1F) << 20)
#define BIT_COMMON_APB_PRE_DBG_BUS3_SEL(x)                                (((x) & 0x1F) << 15)
#define BIT_COMMON_APB_PRE_DBG_BUS2_SEL(x)                                (((x) & 0x1F) << 10)
#define BIT_COMMON_APB_PRE_DBG_BUS1_SEL(x)                                (((x) & 0x1F) << 5)
#define BIT_COMMON_APB_PRE_DBG_BUS0_SEL(x)                                (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PRE_DBG_BUS_11_6_SEL
// Register Offset : 0x0218
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_DBG_BUS11_SEL(x)                               (((x) & 0x1F) << 25)
#define BIT_COMMON_APB_PRE_DBG_BUS10_SEL(x)                               (((x) & 0x1F) << 20)
#define BIT_COMMON_APB_PRE_DBG_BUS9_SEL(x)                                (((x) & 0x1F) << 15)
#define BIT_COMMON_APB_PRE_DBG_BUS8_SEL(x)                                (((x) & 0x1F) << 10)
#define BIT_COMMON_APB_PRE_DBG_BUS7_SEL(x)                                (((x) & 0x1F) << 5)
#define BIT_COMMON_APB_PRE_DBG_BUS6_SEL(x)                                (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PRE_DBG_BUS_17_12_SEL
// Register Offset : 0x021C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_DBG_BUS17_SEL(x)                               (((x) & 0x1F) << 25)
#define BIT_COMMON_APB_PRE_DBG_BUS16_SEL(x)                               (((x) & 0x1F) << 20)
#define BIT_COMMON_APB_PRE_DBG_BUS15_SEL(x)                               (((x) & 0x1F) << 15)
#define BIT_COMMON_APB_PRE_DBG_BUS14_SEL(x)                               (((x) & 0x1F) << 10)
#define BIT_COMMON_APB_PRE_DBG_BUS13_SEL(x)                               (((x) & 0x1F) << 5)
#define BIT_COMMON_APB_PRE_DBG_BUS12_SEL(x)                               (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PRE_DBG_BUS_23_18_SEL
// Register Offset : 0x0220
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_DBG_BUS23_SEL(x)                               (((x) & 0x1F) << 25)
#define BIT_COMMON_APB_PRE_DBG_BUS22_SEL(x)                               (((x) & 0x1F) << 20)
#define BIT_COMMON_APB_PRE_DBG_BUS21_SEL(x)                               (((x) & 0x1F) << 15)
#define BIT_COMMON_APB_PRE_DBG_BUS20_SEL(x)                               (((x) & 0x1F) << 10)
#define BIT_COMMON_APB_PRE_DBG_BUS19_SEL(x)                               (((x) & 0x1F) << 5)
#define BIT_COMMON_APB_PRE_DBG_BUS18_SEL(x)                               (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PRE_DBG_BUS_29_24_SEL
// Register Offset : 0x0224
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_DBG_BUS29_SEL(x)                               (((x) & 0x1F) << 25)
#define BIT_COMMON_APB_PRE_DBG_BUS28_SEL(x)                               (((x) & 0x1F) << 20)
#define BIT_COMMON_APB_PRE_DBG_BUS27_SEL(x)                               (((x) & 0x1F) << 15)
#define BIT_COMMON_APB_PRE_DBG_BUS26_SEL(x)                               (((x) & 0x1F) << 10)
#define BIT_COMMON_APB_PRE_DBG_BUS25_SEL(x)                               (((x) & 0x1F) << 5)
#define BIT_COMMON_APB_PRE_DBG_BUS24_SEL(x)                               (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PRE_DBG_BUS_31_30_SEL
// Register Offset : 0x0228
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_DBG_BUS31_SEL(x)                               (((x) & 0x1F) << 5)
#define BIT_COMMON_APB_PRE_DBG_BUS30_SEL(x)                               (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DBG_SIG0
// Register Offset : 0x029C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_AON_DBG_SIG_SEL(x)                             (((x) & 0xFF) << 24)
#define BIT_COMMON_APB_PRE_AON_DBG_MOD_SEL(x)                             (((x) & 0xFF) << 16)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DBG_SIG1
// Register Offset : 0x02A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_DISP_DBG_SIG_SEL(x)                            (((x) & 0xFF) << 24)
#define BIT_COMMON_APB_PRE_DISP_DBG_MOD_SEL(x)                            (((x) & 0xFF) << 16)
#define BIT_COMMON_APB_PRE_VSP_DBG_SIG_SEL(x)                             (((x) & 0xFF) << 8)
#define BIT_COMMON_APB_PRE_VSP_DBG_MOD_SEL(x)                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DBG_SIG2
// Register Offset : 0x02A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_WTL_DBG_SIG_SEL(x)                             (((x) & 0xFF) << 24)
#define BIT_COMMON_APB_PRE_WTL_DBG_MOD_SEL(x)                             (((x) & 0xFF) << 16)
#define BIT_COMMON_APB_PRE_ANLG_DBG_SIG_SEL(x)                            (((x) & 0xFF) << 8)
#define BIT_COMMON_APB_PRE_ANLG_DBG_MOD_SEL(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DBG_SIG3
// Register Offset : 0x02A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_PUB1_DBG_SIG_SEL(x)                            (((x) & 0xFF) << 24)
#define BIT_COMMON_APB_PRE_PUB1_DBG_MOD_SEL(x)                            (((x) & 0xFF) << 16)
#define BIT_COMMON_APB_PRE_PUBCP_DBG_SIG_SEL(x)                           (((x) & 0xFF) << 8)
#define BIT_COMMON_APB_PRE_PUBCP_DBG_MOD_SEL(x)                           (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DBG_SIG4
// Register Offset : 0x02AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_GPU_DBG_SIG_SEL(x)                             (((x) & 0xFF) << 24)
#define BIT_COMMON_APB_PRE_GPU_DBG_MOD_SEL(x)                             (((x) & 0xFF) << 16)
#define BIT_COMMON_APB_PRE_PUB0_DBG_SIG_SEL(x)                            (((x) & 0xFF) << 8)
#define BIT_COMMON_APB_PRE_PUB0_DBG_MOD_SEL(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DBG_SIG5
// Register Offset : 0x02B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_CAM_DBG_SIG_SEL(x)                             (((x) & 0xFF) << 24)
#define BIT_COMMON_APB_PRE_CAM_DBG_MOD_SEL(x)                             (((x) & 0xFF) << 16)
#define BIT_COMMON_APB_PRE_AGCP_DBG_SIG_SEL(x)                            (((x) & 0xFF) << 8)
#define BIT_COMMON_APB_PRE_AGCP_DBG_MOD_SEL(x)                            (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DBG_SIG6
// Register Offset : 0x02B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_AP_DBG_SIG_SEL(x)                              (((x) & 0xFF) << 24)
#define BIT_COMMON_APB_PRE_AP_DBG_MOD_SEL(x)                              (((x) & 0xFF) << 16)
#define BIT_COMMON_APB_PRE_DBG_SIG_RESERVED(x)                            (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_SUB_SYS_DBG_SIG7
// Register Offset : 0x02B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_MDAR_DBG_SIG_SEL(x)                            (((x) & 0xFF) << 24)
#define BIT_COMMON_APB_PRE_MDAR_DBG_MOD_SEL(x)                            (((x) & 0xFF) << 16)
#define BIT_COMMON_APB_PRE_DBG_MOD_RESERVED(x)                            (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_DEBUG_SUBSYS_SEL
// Register Offset : 0x02BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PRE_DBG_SUBSYS_SEL(x)                              (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_WTLCP2AON_R_FIFO_CH_1
// Register Offset : 0x02C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AF_LVL_AW_CH(x)                   (((x) & 0xF) << 28)
#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AE_LVL_AW_CH(x)                   (((x) & 0xF) << 24)
#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AF_LVL_W_CH(x)                    (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AE_LVL_W_CH(x)                    (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AF_LVL_B_CH(x)                    (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AE_LVL_B_CH(x)                    (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_WTLCP2AON_R_FIFO_CH0_2
// Register Offset : 0x02C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AF_LVL_R_CH(x)                    (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AE_LVL_R_CH(x)                    (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AF_LVL_AR_CH(x)                   (((x) & 0xF) << 4)
#define BIT_COMMON_APB_WTLCP2AON_R_FIFO_AE_LVL_AR_CH(x)                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_WTLCP2AON_W_FIFO_CH_1
// Register Offset : 0x02CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AF_LVL_AW_CH(x)                   (((x) & 0xF) << 28)
#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AE_LVL_AW_CH(x)                   (((x) & 0xF) << 24)
#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AF_LVL_W_CH(x)                    (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AE_LVL_W_CH(x)                    (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AF_LVL_B_CH(x)                    (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AE_LVL_B_CH(x)                    (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_WTLCP2AON_W_FIFO_CH0_2
// Register Offset : 0x02D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AF_LVL_R_CH(x)                    (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AE_LVL_R_CH(x)                    (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AF_LVL_AR_CH(x)                   (((x) & 0xF) << 4)
#define BIT_COMMON_APB_WTLCP2AON_W_FIFO_AE_LVL_AR_CH(x)                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AGCP2AON_R_FIFO_CH_1
// Register Offset : 0x02D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AF_LVL_AW_CH(x)                    (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AE_LVL_AW_CH(x)                    (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AF_LVL_W_CH(x)                     (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AE_LVL_W_CH(x)                     (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AF_LVL_B_CH(x)                     (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AE_LVL_B_CH(x)                     (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AGCP2AON_R_FIFO_CH0_2
// Register Offset : 0x02D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AF_LVL_R_CH(x)                     (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AE_LVL_R_CH(x)                     (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AF_LVL_AR_CH(x)                    (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AGCP2AON_R_FIFO_AE_LVL_AR_CH(x)                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AGCP2AON_W_FIFO_CH_1
// Register Offset : 0x02DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AF_LVL_AW_CH(x)                    (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AE_LVL_AW_CH(x)                    (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AF_LVL_W_CH(x)                     (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AE_LVL_W_CH(x)                     (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AF_LVL_B_CH(x)                     (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AE_LVL_B_CH(x)                     (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AGCP2AON_W_FIFO_CH0_2
// Register Offset : 0x02E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AF_LVL_R_CH(x)                     (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AE_LVL_R_CH(x)                     (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AF_LVL_AR_CH(x)                    (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AGCP2AON_W_FIFO_AE_LVL_AR_CH(x)                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PUBCP2AON_R_FIFO_CH_1
// Register Offset : 0x02E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AF_LVL_AW_CH(x)                   (((x) & 0xF) << 28)
#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AE_LVL_AW_CH(x)                   (((x) & 0xF) << 24)
#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AF_LVL_W_CH(x)                    (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AE_LVL_W_CH(x)                    (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AF_LVL_B_CH(x)                    (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AE_LVL_B_CH(x)                    (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PUBCP2AON_R_FIFO_CH0_2
// Register Offset : 0x02E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AF_LVL_R_CH(x)                    (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AE_LVL_R_CH(x)                    (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AF_LVL_AR_CH(x)                   (((x) & 0xF) << 4)
#define BIT_COMMON_APB_PUBCP2AON_R_FIFO_AE_LVL_AR_CH(x)                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PUBCP2AON_W_FIFO_CH_1
// Register Offset : 0x02EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AF_LVL_AW_CH(x)                   (((x) & 0xF) << 28)
#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AE_LVL_AW_CH(x)                   (((x) & 0xF) << 24)
#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AF_LVL_W_CH(x)                    (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AE_LVL_W_CH(x)                    (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AF_LVL_B_CH(x)                    (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AE_LVL_B_CH(x)                    (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PUBCP2AON_W_FIFO_CH0_2
// Register Offset : 0x02F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AF_LVL_R_CH(x)                    (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AE_LVL_R_CH(x)                    (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AF_LVL_AR_CH(x)                   (((x) & 0xF) << 4)
#define BIT_COMMON_APB_PUBCP2AON_W_FIFO_AE_LVL_AR_CH(x)                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUBCP_R_FIFO_CH_1
// Register Offset : 0x02F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AF_LVL_AW_CH(x)                   (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AE_LVL_AW_CH(x)                   (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AF_LVL_W_CH(x)                    (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AE_LVL_W_CH(x)                    (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AF_LVL_B_CH(x)                    (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AE_LVL_B_CH(x)                    (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUBCP_R_FIFO_CH0_2
// Register Offset : 0x02F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AF_LVL_R_CH(x)                    (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AE_LVL_R_CH(x)                    (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AF_LVL_AR_CH(x)                   (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AON2PUBCP_R_FIFO_AE_LVL_AR_CH(x)                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUBCP_W_FIFO_CH_1
// Register Offset : 0x02FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AF_LVL_AW_CH(x)                   (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AE_LVL_AW_CH(x)                   (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AF_LVL_W_CH(x)                    (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AE_LVL_W_CH(x)                    (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AF_LVL_B_CH(x)                    (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AE_LVL_B_CH(x)                    (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUBCP_W_FIFO_CH0_2
// Register Offset : 0x0300
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AF_LVL_R_CH(x)                    (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AE_LVL_R_CH(x)                    (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AF_LVL_AR_CH(x)                   (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AON2PUBCP_W_FIFO_AE_LVL_AR_CH(x)                   (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2AGCP_R_FIFO_CH_1
// Register Offset : 0x0304
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AF_LVL_AW_CH(x)                    (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AE_LVL_AW_CH(x)                    (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AF_LVL_W_CH(x)                     (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AE_LVL_W_CH(x)                     (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AF_LVL_B_CH(x)                     (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AE_LVL_B_CH(x)                     (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2AGCP_R_FIFO_CH0_2
// Register Offset : 0x0308
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AF_LVL_R_CH(x)                     (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AE_LVL_R_CH(x)                     (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AF_LVL_AR_CH(x)                    (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AON2AGCP_R_FIFO_AE_LVL_AR_CH(x)                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2AGCP_W_FIFO_CH_1
// Register Offset : 0x030C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AF_LVL_AW_CH(x)                    (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AE_LVL_AW_CH(x)                    (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AF_LVL_W_CH(x)                     (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AE_LVL_W_CH(x)                     (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AF_LVL_B_CH(x)                     (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AE_LVL_B_CH(x)                     (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2AGCP_W_FIFO_CH0_2
// Register Offset : 0x0310
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AF_LVL_R_CH(x)                     (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AE_LVL_R_CH(x)                     (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AF_LVL_AR_CH(x)                    (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AON2AGCP_W_FIFO_AE_LVL_AR_CH(x)                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUB0_R_FIFO_CH_1
// Register Offset : 0x0314
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AF_LVL_AW_CH(x)                    (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AE_LVL_AW_CH(x)                    (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AF_LVL_W_CH(x)                     (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AE_LVL_W_CH(x)                     (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AF_LVL_B_CH(x)                     (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AE_LVL_B_CH(x)                     (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUB0_R_FIFO_CH0_2
// Register Offset : 0x031C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AF_LVL_R_CH(x)                     (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AE_LVL_R_CH(x)                     (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AF_LVL_AR_CH(x)                    (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AON2PUB0_R_FIFO_AE_LVL_AR_CH(x)                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUB0_W_FIFO_CH_1
// Register Offset : 0x0320
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AF_LVL_AW_CH(x)                    (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AE_LVL_AW_CH(x)                    (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AF_LVL_W_CH(x)                     (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AE_LVL_W_CH(x)                     (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AF_LVL_B_CH(x)                     (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AE_LVL_B_CH(x)                     (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUB0_W_FIFO_CH0_2
// Register Offset : 0x0324
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AF_LVL_R_CH(x)                     (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AE_LVL_R_CH(x)                     (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AF_LVL_AR_CH(x)                    (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AON2PUB0_W_FIFO_AE_LVL_AR_CH(x)                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUB1_R_FIFO_CH_1
// Register Offset : 0x0328
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AF_LVL_AW_CH(x)                    (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AE_LVL_AW_CH(x)                    (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AF_LVL_W_CH(x)                     (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AE_LVL_W_CH(x)                     (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AF_LVL_B_CH(x)                     (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AE_LVL_B_CH(x)                     (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUB1_R_FIFO_CH0_2
// Register Offset : 0x032C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AF_LVL_R_CH(x)                     (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AE_LVL_R_CH(x)                     (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AF_LVL_AR_CH(x)                    (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AON2PUB1_R_FIFO_AE_LVL_AR_CH(x)                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUB1_W_FIFO_CH_1
// Register Offset : 0x0330
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AF_LVL_AW_CH(x)                    (((x) & 0xF) << 28)
#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AE_LVL_AW_CH(x)                    (((x) & 0xF) << 24)
#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AF_LVL_W_CH(x)                     (((x) & 0x1F) << 19)
#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AE_LVL_W_CH(x)                     (((x) & 0x1F) << 14)
#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AF_LVL_B_CH(x)                     (((x) & 0x1F) << 9)
#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AE_LVL_B_CH(x)                     (((x) & 0x1F) << 4)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON2PUB1_W_FIFO_CH0_2
// Register Offset : 0x0334
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AF_LVL_R_CH(x)                     (((x) & 0x1F) << 27)
#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AE_LVL_R_CH(x)                     (((x) & 0x1F) << 22)
#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AF_LVL_AR_CH(x)                    (((x) & 0xF) << 4)
#define BIT_COMMON_APB_AON2PUB1_W_FIFO_AE_LVL_AR_CH(x)                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON_APB_RSV
// Register Offset : 0x30F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON_APB_RSV(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AON_OSC_FUNC_CTRL
// Register Offset : 0x3104
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_RST_BINING_FUNC_N                                  BIT(25)
#define BIT_COMMON_APB_OSC_BINING_SEL_FUNC(x)                             (((x) & 0x7F) << 18)
#define BIT_COMMON_APB_OSC_BINING_CTRL_FUNC_EN                            BIT(17)
#define BIT_COMMON_APB_OSC_BINING_CLK_FUNC_NUM(x)                         (((x) & 0x1FFF) << 4)
#define BIT_COMMON_APB_OSC_CHNL2_FUNC_OVERFLOW                            BIT(3)
#define BIT_COMMON_APB_OSC_CHNL1_FUNC_OVERFLOW                            BIT(2)
#define BIT_COMMON_APB_OSC_CHNL2_FUNC_CNT_VALID                           BIT(1)
#define BIT_COMMON_APB_OSC_CHNL1_FUNC_CNT_VALID                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_VDROP_TEST_CTRL
// Register Offset : 0x3190
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_GPU_VDROP_RESERVED(x)                              (((x) & 0xF) << 20)
#define BIT_COMMON_APB_GPU_VDROP_TEST_MODE_EN                             BIT(19)
#define BIT_COMMON_APB_GPU_VDROP_EN                                       BIT(18)
#define BIT_COMMON_APB_GPU_VDROP_LATCH_EN                                 BIT(17)
#define BIT_COMMON_APB_GPU_VDROP_CTRL(x)                                  (((x) & 0x7) << 12)
#define BIT_COMMON_APB_GPU_VDROP_CURRENT(x)                               (((x) & 0x3) << 10)
#define BIT_COMMON_APB_GPU_VDROP_RANGE_SEL(x)                             (((x) & 0x3) << 8)
#define BIT_COMMON_APB_GPU_VDROP_TEST_PULSE_SEL(x)                        (((x) & 0xF) << 4)
#define BIT_COMMON_APB_GPU_VDROP_TEST_TRIG                                BIT(2)
#define BIT_COMMON_APB_GPU_VDROP_PULSE_MODE                               BIT(1)
#define BIT_COMMON_APB_GPU_VDROP_MODE                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PROBE_CAL_CTRL
// Register Offset : 0x3194
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PROBE_MAX_RANGE(x)                                 (((x) & 0x7FFF) << 16)
#define BIT_COMMON_APB_PROBE_MIN_RANGE(x)                                 (((x) & 0x7FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AUX0_CAL_CTRL
// Register Offset : 0x3198
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AUX0_MAX_RANGE(x)                                  (((x) & 0x7FFF) << 16)
#define BIT_COMMON_APB_AUX0_MIN_RANGE(x)                                  (((x) & 0x7FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AUX1_CAL_CTRL
// Register Offset : 0x319C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AUX1_MAX_RANGE(x)                                  (((x) & 0x7FFF) << 16)
#define BIT_COMMON_APB_AUX1_MIN_RANGE(x)                                  (((x) & 0x7FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AUX2_CAL_CTRL
// Register Offset : 0x31A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AUX2_MAX_RANGE(x)                                  (((x) & 0x7FFF) << 16)
#define BIT_COMMON_APB_AUX2_MIN_RANGE(x)                                  (((x) & 0x7FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PLL_FREQ_CAL_CFG
// Register Offset : 0x31A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_DIV_NUM_26M(x)                                     (((x) & 0x3FF) << 16)
#define BIT_COMMON_APB_AUX2_CAL_EN                                        BIT(3)
#define BIT_COMMON_APB_AUX1_CAL_EN                                        BIT(2)
#define BIT_COMMON_APB_AUX0_CAL_EN                                        BIT(1)
#define BIT_COMMON_APB_PROBE_CAL_EN                                       BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PROBE_RESULT
// Register Offset : 0x31A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PROBE_FREQ(x)                                      (((x) & 0x7FFF) << 16)
#define BIT_COMMON_APB_PROBE_READY                                        BIT(1)
#define BIT_COMMON_APB_PROBE_PASS                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AUX0_RESULT
// Register Offset : 0x31AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AUX0_FREQ(x)                                       (((x) & 0x7FFF) << 16)
#define BIT_COMMON_APB_AUX0_READY                                         BIT(1)
#define BIT_COMMON_APB_AUX0_PASS                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AUX1_RESULT
// Register Offset : 0x31B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AUX1_FREQ(x)                                       (((x) & 0x7FFF) << 16)
#define BIT_COMMON_APB_AUX1_READY                                         BIT(1)
#define BIT_COMMON_APB_AUX1_PASS                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_AUX2_RESULT
// Register Offset : 0x31B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AUX2_FREQ(x)                                       (((x) & 0x7FFF) << 16)
#define BIT_COMMON_APB_AUX2_READY                                         BIT(1)
#define BIT_COMMON_APB_AUX2_PASS                                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_PLL_TEST_FLAG
// Register Offset : 0x31B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_PLLS_FLAG(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_WTL_GSM_TX_BYP
// Register Offset : 0x31BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_WTL_GSM_TX_BYP                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_RCO100M_CAL_TEST
// Register Offset : 0x31C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_CGM_RCO2M_EN_ATE_TEST                              BIT(7)
#define BIT_COMMON_APB_CGM_RCO100M_DIV_ATE_TEST(x)                        (((x) & 0x3F) << 1)
#define BIT_COMMON_APB_RCO_100M_DIV_EN_ATE_TEST                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_INT_REQ_WTL_GSM_TX
// Register Offset : 0x31C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_INT_REQ_WTL_GSM_TX                                 BIT(1)
#define BIT_COMMON_APB_INT_REQ_WTL_GSM_TX_CLR                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_INT_REQ_ITHM1_ALERT
// Register Offset : 0x31C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_INT_REQ_ITHM1_ALERT                                BIT(1)
#define BIT_COMMON_APB_INT_REQ_ITHM1_ALERT_CLR                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_DSI_MUX
// Register Offset : 0x31CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_DSI2_I_CTL_ENABLE_CLN                              BIT(19)
#define BIT_COMMON_APB_DSI2_I_CTL_PHYFORCEPLL                             BIT(18)
#define BIT_COMMON_APB_DSI2_I_CTL_TURNREQUEST                             BIT(17)
#define BIT_COMMON_APB_DSI2_I_CTL_TXLPDTESC                               BIT(16)
#define BIT_COMMON_APB_DSI2_I_CTL_TXULPSCLK_CLN                           BIT(15)
#define BIT_COMMON_APB_DSI2_I_CTL_TXULPSEXIT_CLN                          BIT(14)
#define BIT_COMMON_APB_DSI2_I_CTL_TXVALIDESC                              BIT(13)
#define BIT_COMMON_APB_DSI2_I_CTL_ENABLE_DLN(x)                           (((x) & 0xF) << 9)
#define BIT_COMMON_APB_DSI2_I_CTL_TXREQUESTESC(x)                         (((x) & 0xF) << 5)
#define BIT_COMMON_APB_DSI2_I_CTL_TXTRIGGERESC(x)                         (((x) & 0xF) << 1)
#define BIT_COMMON_APB_DSI2_I_RST_SYS_N                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_GPU_MEM_ECO
// Register Offset : 0x31D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_GPU_MEM_MARGIN_SEL                                 BIT(20)
#define BIT_COMMON_APB_GPU_MEM_SP_RME                                     BIT(19)
#define BIT_COMMON_APB_GPU_MEM_SP_RM(x)                                   (((x) & 0xF) << 15)
#define BIT_COMMON_APB_GPU_MEM_SP_WM(x)                                   (((x) & 0x3) << 13)
#define BIT_COMMON_APB_GPU_MEM_SP_RA(x)                                   (((x) & 0x7) << 10)
#define BIT_COMMON_APB_GPU_MEM_DP_RME                                     BIT(9)
#define BIT_COMMON_APB_GPU_MEM_DP_RM(x)                                   (((x) & 0xF) << 5)
#define BIT_COMMON_APB_GPU_MEM_DP_WM(x)                                   (((x) & 0x3) << 3)
#define BIT_COMMON_APB_GPU_MEM_DP_RA(x)                                   (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_ASYNC_BRIDGE_OVERFLOW_AND_IDLE
// Register Offset : 0x31D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_AON2PUB1_W_BRIDGE_TRANS_IDLE                       BIT(13)
#define BIT_COMMON_APB_AON2PUB0_W_BRIDGE_TRANS_IDLE                       BIT(12)
#define BIT_COMMON_APB_AON2PUBCP_W_BRIDGE_TRANS_IDLE                      BIT(11)
#define BIT_COMMON_APB_AON2AGCP_W_BRIDGE_TRANS_IDLE                       BIT(10)
#define BIT_COMMON_APB_WTLCP2AON_W_BRIDGE_TRANS_IDLE                      BIT(9)
#define BIT_COMMON_APB_PUBCP2AON_W_BRIDGE_TRANS_IDLE                      BIT(8)
#define BIT_COMMON_APB_AGCP2AON_W_BRIDGE_TRANS_IDLE                       BIT(7)
#define BIT_COMMON_APB_AON2PUB1_W_AXI_DETECTOR_OVERFLOW                   BIT(6)
#define BIT_COMMON_APB_AON2PUB0_W_AXI_DETECTOR_OVERFLOW                   BIT(5)
#define BIT_COMMON_APB_AON2PUBCP_W_AXI_DETECTOR_OVERFLOW                  BIT(4)
#define BIT_COMMON_APB_AON2AGCP_W_AXI_DETECTOR_OVERFLOW                   BIT(3)
#define BIT_COMMON_APB_WTLCP2AON_W_AXI_DETECTOR_OVERFLOW                  BIT(2)
#define BIT_COMMON_APB_PUBCP2AON_W_AXI_DETECTOR_OVERFLOW                  BIT(1)
#define BIT_COMMON_APB_AGCP2AON_W_AXI_DETECTOR_OVERFLOW                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_UFS_SLICE_CTRL
// Register Offset : 0x31D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_UFS_SLICE_DUMMY(x)                                 (((x) & 0x7FFFFF) << 9)
#define BIT_COMMON_APB_UFS_TX_PIPE_SW_BYP                                 BIT(8)
#define BIT_COMMON_APB_UFS_PIPE_CTRL_MODE                                 BIT(7)
#define BIT_COMMON_APB_UFS_TIMING_MODE                                    BIT(6)
#define BIT_COMMON_APB_UFS_MASK_BYP_SW                                    BIT(5)
#define BIT_COMMON_APB_UFS_SAVESTATE_BYP_SW                               BIT(4)
#define BIT_COMMON_APB_PHYDIRDY_DLY_SEL(x)                                (((x) & 0x3) << 2)
#define BIT_COMMON_APB_SAVESTATE_STATUSN_DLY_SEL(x)                       (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_COMMON_DUMMY_RW0
// Register Offset : 0x31DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_COMMON_DUMMY_RW0(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_COMMON_DUMMY_RW1
// Register Offset : 0x31E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_COMMON_DUMMY_RW1(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_COMMON_DUMMY_RW2
// Register Offset : 0x31E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_COMMON_DUMMY_RW2(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_COMMON_DUMMY_RW3
// Register Offset : 0x31E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_COMMON_DUMMY_RW3(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_COMMON_DUMMY_RO0
// Register Offset : 0x31EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_COMMON_DUMMY_RO0(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_COMMON_DUMMY_RO1
// Register Offset : 0x31F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_COMMON_DUMMY_RO1(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_COMMON_DUMMY_RO2
// Register Offset : 0x31F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_COMMON_DUMMY_RO2(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_COMMON_APB_COMMON_DUMMY_RO3
// Register Offset : 0x31F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_COMMON_APB_COMMON_DUMMY_RO3(x)                                (((x) & 0xFFFFFFFF))


#endif // _COMMON_APB_REG_H

/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _AON_LPC_APB_REG_H
#define _AON_LPC_APB_REG_H

#define CTL_BASE_AON_LPC_APB SPRD_AON_LPC_BASE


#define REG_AON_LPC_APB_BIA_W_LPC_CTRL                  ( CTL_BASE_AON_LPC_APB + 0x0000 )
#define REG_AON_LPC_APB_AP2MM_M0_LPC_CTRL               ( CTL_BASE_AON_LPC_APB + 0x0004 )
#define REG_AON_LPC_APB_AP2MM_MAIN_LPC_CTRL             ( CTL_BASE_AON_LPC_APB + 0x0008 )
#define REG_AON_LPC_APB_AP2MM_S0_LPC_CTRL               ( CTL_BASE_AON_LPC_APB + 0x000C )
#define REG_AON_LPC_APB_AP2MM_S1_LPC_CTRL               ( CTL_BASE_AON_LPC_APB + 0x0010 )
#define REG_AON_LPC_APB_AP2MM_S2_LPC_CTRL               ( CTL_BASE_AON_LPC_APB + 0x0014 )
#define REG_AON_LPC_APB_AP_NOC_BIA_M0_LPC_CTRL          ( CTL_BASE_AON_LPC_APB + 0x0018 )
#define REG_AON_LPC_APB_AP_NOC_BIA_M1_LPC_CTRL          ( CTL_BASE_AON_LPC_APB + 0x001C )
#define REG_AON_LPC_APB_AP_NOC_BIA_S0_LPC_CTRL          ( CTL_BASE_AON_LPC_APB + 0x0020 )
#define REG_AON_LPC_APB_AP_NOC_BIA_S1_LPC_CTRL          ( CTL_BASE_AON_LPC_APB + 0x0024 )
#define REG_AON_LPC_APB_GLB_BUS_CLK_GATE_CTRL           ( CTL_BASE_AON_LPC_APB + 0x0028 )
#define REG_AON_LPC_APB_AON_MTX_LP_CFG0                 ( CTL_BASE_AON_LPC_APB + 0x002C )
#define REG_AON_LPC_APB_AON_MTX_LP_CFG1                 ( CTL_BASE_AON_LPC_APB + 0x0030 )
#define REG_AON_LPC_APB_NIC400_TZMA_MTX_LPC_CTRL        ( CTL_BASE_AON_LPC_APB + 0x0034 )
#define REG_AON_LPC_APB_WTLCP2AON_W_LPC_CTRL            ( CTL_BASE_AON_LPC_APB + 0x0038 )
#define REG_AON_LPC_APB_AGCP2AON_W_LPC_CTRL             ( CTL_BASE_AON_LPC_APB + 0x003C )
#define REG_AON_LPC_APB_PUBCP2AON_W_LPC_CTRL            ( CTL_BASE_AON_LPC_APB + 0x0040 )
#define REG_AON_LPC_APB_AON2AGCP_W_LPC_CTRL             ( CTL_BASE_AON_LPC_APB + 0x0044 )
#define REG_AON_LPC_APB_AON2PUBCP_W_LPC_CTRL            ( CTL_BASE_AON_LPC_APB + 0x0048 )
#define REG_AON_LPC_APB_AON2PUB0_W_LPC_CTRL             ( CTL_BASE_AON_LPC_APB + 0x004C )
#define REG_AON_LPC_APB_AON2PUB1_W_LPC_CTRL             ( CTL_BASE_AON_LPC_APB + 0x0050 )
#define REG_AON_LPC_APB_BIA2AP_SLICE_LPC_CTRL           ( CTL_BASE_AON_LPC_APB + 0x0054 )
#define REG_AON_LPC_APB_PUBCP2DSP_SLICE_LPC_CTRL        ( CTL_BASE_AON_LPC_APB + 0x0058 )
#define REG_AON_LPC_APB_PUBCP2WCDMA_SLICE_LPC_CTRL      ( CTL_BASE_AON_LPC_APB + 0x005C )
#define REG_AON_LPC_APB_AON2PUB1_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x0060 )
#define REG_AON_LPC_APB_AON2PUB0_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x0064 )
#define REG_AON_LPC_APB_AON2AGCP_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x0068 )
#define REG_AON_LPC_APB_AON2PUBCP_SLICE_LPC_CTRL        ( CTL_BASE_AON_LPC_APB + 0x006C )
#define REG_AON_LPC_APB_PUBCP2AON_SLICE_LPC_CTRL        ( CTL_BASE_AON_LPC_APB + 0x0070 )
#define REG_AON_LPC_APB_AGCP2AON_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x0074 )
#define REG_AON_LPC_APB_AP2CAM_SLICE_LPC_CTRL           ( CTL_BASE_AON_LPC_APB + 0x0078 )
#define REG_AON_LPC_APB_VSP2PUB1_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x007C )
#define REG_AON_LPC_APB_CAM2PUB1_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x0080 )
#define REG_AON_LPC_APB_GPU2PUB1_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x0084 )
#define REG_AON_LPC_APB_AP_BIA_PUB1_SLICE_LPC_CTRL      ( CTL_BASE_AON_LPC_APB + 0x0088 )
#define REG_AON_LPC_APB_VSP2PUB0_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x008C )
#define REG_AON_LPC_APB_CAM2PUB0_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x0090 )
#define REG_AON_LPC_APB_GPU2PUB0_SLICE_LPC_CTRL         ( CTL_BASE_AON_LPC_APB + 0x0094 )
#define REG_AON_LPC_APB_AP_BIA_PUB0_SLICE_LPC_CTRL      ( CTL_BASE_AON_LPC_APB + 0x0098 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_BIA_W_LPC_CTRL
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_BIA_W_LP_NUM(x)                                     (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_BIA_W_ACTIVE_SYNC_SEL                               BIT(2)
#define BIT_AON_LPC_APB_BIA_W_LP_FORCE                                      BIT(1)
#define BIT_AON_LPC_APB_BIA_W_LP_EB                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP2MM_M0_LPC_CTRL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP2MM_M0_LP_NUM(x)                                  (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP2MM_M0_ACTIVE_SYNC_SEL                            BIT(2)
#define BIT_AON_LPC_APB_AP2MM_M0_LP_FORCE                                   BIT(1)
#define BIT_AON_LPC_APB_AP2MM_M0_LP_EB                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP2MM_MAIN_LPC_CTRL
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP2MM_MAIN_LP_NUM(x)                                (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP2MM_MAIN_ACTIVE_SYNC_SEL                          BIT(2)
#define BIT_AON_LPC_APB_AP2MM_MAIN_LP_FORCE                                 BIT(1)
#define BIT_AON_LPC_APB_AP2MM_MAIN_LP_EB                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP2MM_S0_LPC_CTRL
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP2MM_S0_LP_NUM(x)                                  (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP2MM_S0_ACTIVE_SYNC_SEL                            BIT(2)
#define BIT_AON_LPC_APB_AP2MM_S0_LP_FORCE                                   BIT(1)
#define BIT_AON_LPC_APB_AP2MM_S0_LP_EB                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP2MM_S1_LPC_CTRL
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP2MM_S1_LP_NUM(x)                                  (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP2MM_S1_ACTIVE_SYNC_SEL                            BIT(2)
#define BIT_AON_LPC_APB_AP2MM_S1_LP_FORCE                                   BIT(1)
#define BIT_AON_LPC_APB_AP2MM_S1_LP_EB                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP2MM_S2_LPC_CTRL
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP2MM_S2_LP_NUM(x)                                  (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP2MM_S2_ACTIVE_SYNC_SEL                            BIT(2)
#define BIT_AON_LPC_APB_AP2MM_S2_LP_FORCE                                   BIT(1)
#define BIT_AON_LPC_APB_AP2MM_S2_LP_EB                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP_NOC_BIA_M0_LPC_CTRL
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP_NOC_BIA_M0_LP_NUM(x)                             (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP_NOC_BIA_M0_ACTIVE_SYNC_SEL                       BIT(2)
#define BIT_AON_LPC_APB_AP_NOC_BIA_M0_LP_FORCE                              BIT(1)
#define BIT_AON_LPC_APB_AP_NOC_BIA_M0_LP_EB                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP_NOC_BIA_M1_LPC_CTRL
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP_NOC_BIA_M1_LP_NUM(x)                             (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP_NOC_BIA_M1_ACTIVE_SYNC_SEL                       BIT(2)
#define BIT_AON_LPC_APB_AP_NOC_BIA_M1_LP_FORCE                              BIT(1)
#define BIT_AON_LPC_APB_AP_NOC_BIA_M1_LP_EB                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP_NOC_BIA_S0_LPC_CTRL
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP_NOC_BIA_S0_LP_NUM(x)                             (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP_NOC_BIA_S0_ACTIVE_SYNC_SEL                       BIT(2)
#define BIT_AON_LPC_APB_AP_NOC_BIA_S0_LP_FORCE                              BIT(1)
#define BIT_AON_LPC_APB_AP_NOC_BIA_S0_LP_EB                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP_NOC_BIA_S1_LPC_CTRL
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP_NOC_BIA_S1_LP_NUM(x)                             (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP_NOC_BIA_S1_ACTIVE_SYNC_SEL                       BIT(2)
#define BIT_AON_LPC_APB_AP_NOC_BIA_S1_LP_FORCE                              BIT(1)
#define BIT_AON_LPC_APB_AP_NOC_BIA_S1_LP_EB                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_GLB_BUS_CLK_GATE_CTRL
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_PUBCP_WCDMA_SOFT_GATE_DIS                           BIT(13)
#define BIT_AON_LPC_APB_PUBCP_WCDMA_AUTO_GATE_EN                            BIT(12)
#define BIT_AON_LPC_APB_WTLCP_WCDMA_SOFT_GATE_DIS                           BIT(11)
#define BIT_AON_LPC_APB_WTLCP_WCDMA_AUTO_GATE_EN                            BIT(10)
#define BIT_AON_LPC_APB_AGCP_AON_SOFT_GATE_DIS                              BIT(7)
#define BIT_AON_LPC_APB_AGCP_AON_AUTO_GATE_EN                               BIT(6)
#define BIT_AON_LPC_APB_WTLCP_AON_SOFT_GATE_DIS                             BIT(5)
#define BIT_AON_LPC_APB_WTLCP_AON_AUTO_GATE_EN                              BIT(4)
#define BIT_AON_LPC_APB_PUBCP_AON_SOFT_GATE_DIS                             BIT(3)
#define BIT_AON_LPC_APB_PUBCP_AON_AUTO_GATE_EN                              BIT(2)
#define BIT_AON_LPC_APB_AP_AON_SOFT_GATE_DIS                                BIT(1)
#define BIT_AON_LPC_APB_AP_AON_AUTO_GATE_EN                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON_MTX_LP_CFG0
// Register Offset : 0x002C
// Description     : axi lower power clk gate config
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON_MTX_M0_LP_EB                                    BIT(31)
#define BIT_AON_LPC_APB_AON_MTX_M0_LP_FORCE                                 BIT(30)
#define BIT_AON_LPC_APB_AON_MTX_M0_ACTIVE_SYNC_SEL                          BIT(29)
#define BIT_AON_LPC_APB_AON_MTX_M1_LP_EB                                    BIT(28)
#define BIT_AON_LPC_APB_AON_MTX_M1_LP_FORCE                                 BIT(27)
#define BIT_AON_LPC_APB_AON_MTX_M1_ACTIVE_SYNC_SEL                          BIT(26)
#define BIT_AON_LPC_APB_AON_MTX_M2_LP_EB                                    BIT(25)
#define BIT_AON_LPC_APB_AON_MTX_M2_LP_FORCE                                 BIT(24)
#define BIT_AON_LPC_APB_AON_MTX_M2_ACTIVE_SYNC_SEL                          BIT(23)
#define BIT_AON_LPC_APB_AON_MTX_M3_LP_EB                                    BIT(22)
#define BIT_AON_LPC_APB_AON_MTX_M3_LP_FORCE                                 BIT(21)
#define BIT_AON_LPC_APB_AON_MTX_M3_ACTIVE_SYNC_SEL                          BIT(20)
#define BIT_AON_LPC_APB_AON_MTX_M4_LP_EB                                    BIT(19)
#define BIT_AON_LPC_APB_AON_MTX_M4_LP_FORCE                                 BIT(18)
#define BIT_AON_LPC_APB_AON_MTX_M4_ACTIVE_SYNC_SEL                          BIT(17)
#define BIT_AON_LPC_APB_AON_MTX_LP_NUM(x)                                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON_MTX_LP_CFG1
// Register Offset : 0x0030
// Description     : aon main mtx slave low power config
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON_MTX_S9_LP_EB                                    BIT(31)
#define BIT_AON_LPC_APB_AON_MTX_S9_LP_FORCE                                 BIT(30)
#define BIT_AON_LPC_APB_AON_MTX_S9_ACTIVE_SYNC_SEL                          BIT(29)
#define BIT_AON_LPC_APB_AON_MTX_S8_LP_EB                                    BIT(28)
#define BIT_AON_LPC_APB_AON_MTX_S8_LP_FORCE                                 BIT(27)
#define BIT_AON_LPC_APB_AON_MTX_S8_ACTIVE_SYNC_SEL                          BIT(26)
#define BIT_AON_LPC_APB_AON_MTX_S7_LP_EB                                    BIT(25)
#define BIT_AON_LPC_APB_AON_MTX_S7_LP_FORCE                                 BIT(24)
#define BIT_AON_LPC_APB_AON_MTX_S7_ACTIVE_SYNC_SEL                          BIT(23)
#define BIT_AON_LPC_APB_AON_MTX_S6_LP_EB                                    BIT(22)
#define BIT_AON_LPC_APB_AON_MTX_S6_LP_FORCE                                 BIT(21)
#define BIT_AON_LPC_APB_AON_MTX_S6_ACTIVE_SYNC_SEL                          BIT(20)
#define BIT_AON_LPC_APB_AON_MTX_S5_LP_EB                                    BIT(19)
#define BIT_AON_LPC_APB_AON_MTX_S5_LP_FORCE                                 BIT(18)
#define BIT_AON_LPC_APB_AON_MTX_S5_ACTIVE_SYNC_SEL                          BIT(17)
#define BIT_AON_LPC_APB_AON_MTX_S4_LP_EB                                    BIT(16)
#define BIT_AON_LPC_APB_AON_MTX_S4_LP_FORCE                                 BIT(15)
#define BIT_AON_LPC_APB_AON_MTX_S4_ACTIVE_SYNC_SEL                          BIT(14)
#define BIT_AON_LPC_APB_AON_MTX_S3_LP_EB                                    BIT(13)
#define BIT_AON_LPC_APB_AON_MTX_S3_LP_FORCE                                 BIT(12)
#define BIT_AON_LPC_APB_AON_MTX_S3_ACTIVE_SYNC_SEL                          BIT(11)
#define BIT_AON_LPC_APB_AON_MTX_S2_LP_EB                                    BIT(10)
#define BIT_AON_LPC_APB_AON_MTX_S2_LP_FORCE                                 BIT(9)
#define BIT_AON_LPC_APB_AON_MTX_S2_ACTIVE_SYNC_SEL                          BIT(8)
#define BIT_AON_LPC_APB_AON_MTX_S1_LP_EB                                    BIT(7)
#define BIT_AON_LPC_APB_AON_MTX_S1_LP_FORCE                                 BIT(6)
#define BIT_AON_LPC_APB_AON_MTX_S1_ACTIVE_SYNC_SEL                          BIT(5)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_NIC400_TZMA_MTX_LPC_CTRL
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_TZMA_MTX_LP_NUM(x)                                  (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_TZMA_MTX_ACTIVE_SYNC_SEL                            BIT(2)
#define BIT_AON_LPC_APB_TZMA_MTX_LP_FORCE                                   BIT(1)
#define BIT_AON_LPC_APB_TZMA_MTX_LP_EB                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_WTLCP2AON_W_LPC_CTRL
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_WTLCP2AON_W_LP_NUM(x)                               (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_WTLCP2AON_W_ACTIVE_SYNC_SEL                         BIT(2)
#define BIT_AON_LPC_APB_WTLCP2AON_W_LP_FORCE                                BIT(1)
#define BIT_AON_LPC_APB_WTLCP2AON_W_LP_EB                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AGCP2AON_W_LPC_CTRL
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AGCP2AON_W_LP_NUM(x)                                (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AGCP2AON_W_ACTIVE_SYNC_SEL                          BIT(2)
#define BIT_AON_LPC_APB_AGCP2AON_W_LP_FORCE                                 BIT(1)
#define BIT_AON_LPC_APB_AGCP2AON_W_LP_EB                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_PUBCP2AON_W_LPC_CTRL
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_PUBCP2AON_W_LP_NUM(x)                               (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_PUBCP2AON_W_ACTIVE_SYNC_SEL                         BIT(2)
#define BIT_AON_LPC_APB_PUBCP2AON_W_LP_FORCE                                BIT(1)
#define BIT_AON_LPC_APB_PUBCP2AON_W_LP_EB                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON2AGCP_W_LPC_CTRL
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON2AGCP_W_LP_NUM(x)                                (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AON2AGCP_W_ACTIVE_SYNC_SEL                          BIT(2)
#define BIT_AON_LPC_APB_AON2AGCP_W_LP_FORCE                                 BIT(1)
#define BIT_AON_LPC_APB_AON2AGCP_W_LP_EB                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON2PUBCP_W_LPC_CTRL
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON2PUBCP_W_LP_NUM(x)                               (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AON2PUBCP_W_ACTIVE_SYNC_SEL                         BIT(2)
#define BIT_AON_LPC_APB_AON2PUBCP_W_LP_FORCE                                BIT(1)
#define BIT_AON_LPC_APB_AON2PUBCP_W_LP_EB                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON2PUB0_W_LPC_CTRL
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON2PUB0_W_LP_NUM(x)                                (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AON2PUB0_W_ACTIVE_SYNC_SEL                          BIT(2)
#define BIT_AON_LPC_APB_AON2PUB0_W_LP_FORCE                                 BIT(1)
#define BIT_AON_LPC_APB_AON2PUB0_W_LP_EB                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON2PUB1_W_LPC_CTRL
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON2PUB1_W_LP_NUM(x)                                (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AON2PUB1_W_ACTIVE_SYNC_SEL                          BIT(2)
#define BIT_AON_LPC_APB_AON2PUB1_W_LP_FORCE                                 BIT(1)
#define BIT_AON_LPC_APB_AON2PUB1_W_LP_EB                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_BIA2AP_SLICE_LPC_CTRL
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_BIA2AP_SLICE_LP_NUM(x)                              (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_BIA2AP_SLICE_ACTIVE_SYNC_SEL                        BIT(2)
#define BIT_AON_LPC_APB_BIA2AP_SLICE_LP_FORCE                               BIT(1)
#define BIT_AON_LPC_APB_BIA2AP_SLICE_LP_EB                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_PUBCP2DSP_SLICE_LPC_CTRL
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_PUBCP2DSP_SLICE_LP_NUM(x)                           (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_PUBCP2DSP_SLICE_ACTIVE_SYNC_SEL                     BIT(2)
#define BIT_AON_LPC_APB_PUBCP2DSP_SLICE_LP_FORCE                            BIT(1)
#define BIT_AON_LPC_APB_PUBCP2DSP_SLICE_LP_EB                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_PUBCP2WCDMA_SLICE_LPC_CTRL
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_PUBCP2WCDMA_SLICE_LP_NUM(x)                         (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_PUBCP2WCDMA_SLICE_ACTIVE_SYNC_SEL                   BIT(2)
#define BIT_AON_LPC_APB_PUBCP2WCDMA_SLICE_LP_FORCE                          BIT(1)
#define BIT_AON_LPC_APB_PUBCP2WCDMA_SLICE_LP_EB                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON2PUB1_SLICE_LPC_CTRL
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON2PUB1_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AON2PUB1_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_AON2PUB1_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_AON2PUB1_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON2PUB0_SLICE_LPC_CTRL
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON2PUB0_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AON2PUB0_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_AON2PUB0_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_AON2PUB0_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON2AGCP_SLICE_LPC_CTRL
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON2AGCP_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AON2AGCP_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_AON2AGCP_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_AON2AGCP_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AON2PUBCP_SLICE_LPC_CTRL
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AON2PUBCP_SLICE_LP_NUM(x)                           (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AON2PUBCP_SLICE_ACTIVE_SYNC_SEL                     BIT(2)
#define BIT_AON_LPC_APB_AON2PUBCP_SLICE_LP_FORCE                            BIT(1)
#define BIT_AON_LPC_APB_AON2PUBCP_SLICE_LP_EB                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_PUBCP2AON_SLICE_LPC_CTRL
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_PUBCP2AON_SLICE_LP_NUM(x)                           (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_PUBCP2AON_SLICE_ACTIVE_SYNC_SEL                     BIT(2)
#define BIT_AON_LPC_APB_PUBCP2AON_SLICE_LP_FORCE                            BIT(1)
#define BIT_AON_LPC_APB_PUBCP2AON_SLICE_LP_EB                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AGCP2AON_SLICE_LPC_CTRL
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AGCP2AON_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AGCP2AON_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_AGCP2AON_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_AGCP2AON_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP2CAM_SLICE_LPC_CTRL
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP2CAM_SLICE_LP_NUM(x)                              (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP2CAM_SLICE_ACTIVE_SYNC_SEL                        BIT(2)
#define BIT_AON_LPC_APB_AP2CAM_SLICE_LP_FORCE                               BIT(1)
#define BIT_AON_LPC_APB_AP2CAM_SLICE_LP_EB                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_VSP2PUB1_SLICE_LPC_CTRL
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_VSP2PUB1_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_VSP2PUB1_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_VSP2PUB1_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_VSP2PUB1_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_CAM2PUB1_SLICE_LPC_CTRL
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_CAM2PUB1_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_CAM2PUB1_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_CAM2PUB1_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_CAM2PUB1_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_GPU2PUB1_SLICE_LPC_CTRL
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_GPU2PUB1_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_GPU2PUB1_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_GPU2PUB1_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_GPU2PUB1_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP_BIA_PUB1_SLICE_LPC_CTRL
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP_BIA_PUB1_SLICE_LP_NUM(x)                         (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP_BIA_PUB1_SLICE_ACTIVE_SYNC_SEL                   BIT(2)
#define BIT_AON_LPC_APB_AP_BIA_PUB1_SLICE_LP_FORCE                          BIT(1)
#define BIT_AON_LPC_APB_AP_BIA_PUB1_SLICE_LP_EB                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_VSP2PUB0_SLICE_LPC_CTRL
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_VSP2PUB0_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_VSP2PUB0_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_VSP2PUB0_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_VSP2PUB0_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_CAM2PUB0_SLICE_LPC_CTRL
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_CAM2PUB0_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_CAM2PUB0_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_CAM2PUB0_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_CAM2PUB0_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_GPU2PUB0_SLICE_LPC_CTRL
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_GPU2PUB0_SLICE_LP_NUM(x)                            (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_GPU2PUB0_SLICE_ACTIVE_SYNC_SEL                      BIT(2)
#define BIT_AON_LPC_APB_GPU2PUB0_SLICE_LP_FORCE                             BIT(1)
#define BIT_AON_LPC_APB_GPU2PUB0_SLICE_LP_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_LPC_APB_AP_BIA_PUB0_SLICE_LPC_CTRL
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_LPC_APB_AP_BIA_PUB0_SLICE_LP_NUM(x)                         (((x) & 0xFFFF) << 3)
#define BIT_AON_LPC_APB_AP_BIA_PUB0_SLICE_ACTIVE_SYNC_SEL                   BIT(2)
#define BIT_AON_LPC_APB_AP_BIA_PUB0_SLICE_LP_FORCE                          BIT(1)
#define BIT_AON_LPC_APB_AP_BIA_PUB0_SLICE_LP_EB                             BIT(0)


#endif // _AON_LPC_APB_REG_H

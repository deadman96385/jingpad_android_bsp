/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _MM_AHB_RF_REG_H
#define _MM_AHB_RF_REG_H

#define CTL_BASE_MM_AHB_RF 0x60D00000


#define REG_MM_AHB_RF_AHB_EB                ( CTL_BASE_MM_AHB_RF + 0x0000 )
#define REG_MM_AHB_RF_AHB_RST               ( CTL_BASE_MM_AHB_RF + 0x0004 )
#define REG_MM_AHB_RF_GEN_CKG_CFG           ( CTL_BASE_MM_AHB_RF + 0x0008 )
#define REG_MM_AHB_RF_MIPI_CSI2_CTRL        ( CTL_BASE_MM_AHB_RF + 0x000C )
#define REG_MM_AHB_RF_ISP_QOS_CTRL          ( CTL_BASE_MM_AHB_RF + 0x0010 )
#define REG_MM_AHB_RF_CAM_MTX_LPC_CTRL      ( CTL_BASE_MM_AHB_RF + 0x0014 )
#define REG_MM_AHB_RF_VSP_MTX_LPC_CTRL_M0   ( CTL_BASE_MM_AHB_RF + 0x0018 )
#define REG_MM_AHB_RF_VSP_MTX_LPC_CTRL_M1   ( CTL_BASE_MM_AHB_RF + 0x001C )
#define REG_MM_AHB_RF_VSP_MTX_LPC_CTRL_S0   ( CTL_BASE_MM_AHB_RF + 0x0020 )
#define REG_MM_AHB_RF_MM_MTX_LPC_STAT       ( CTL_BASE_MM_AHB_RF + 0x0024 )
#define REG_MM_AHB_RF_MM_LIGHT_SLEEP_CTRL   ( CTL_BASE_MM_AHB_RF + 0x0028 )
#define REG_MM_AHB_RF_CAM_MTX_LPC_CTRL_M0   ( CTL_BASE_MM_AHB_RF + 0x002C )
#define REG_MM_AHB_RF_CAM_MTX_LPC_CTRL_M1   ( CTL_BASE_MM_AHB_RF + 0x0030 )
#define REG_MM_AHB_RF_VSP_MTX_LPC_CTRL_GPV  ( CTL_BASE_MM_AHB_RF + 0x0034 )
#define REG_MM_AHB_RF_MM_DUMMY_REG_0        ( CTL_BASE_MM_AHB_RF + 0x0038 )
#define REG_MM_AHB_RF_MM_DUMMY_REG_1        ( CTL_BASE_MM_AHB_RF + 0x003C )

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_AHB_EB
// Register Offset : 0x0000
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_VSP_MTX_QOS_AHB_EB                       BIT(6)
#define BIT_MM_AHB_RF_CKG_EB                                   BIT(5)
#define BIT_MM_AHB_RF_JPG_EB                                   BIT(4)
#define BIT_MM_AHB_RF_CSI_EB                                   BIT(3)
#define BIT_MM_AHB_RF_VSP_EB                                   BIT(2)
#define BIT_MM_AHB_RF_ISP_EB                                   BIT(1)
#define BIT_MM_AHB_RF_DCAM_EB                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_AHB_RST
// Register Offset : 0x0004
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_AXI_VSP_MTX_SOFT_RST                     BIT(12)
#define BIT_MM_AHB_RF_AXI_CAM_MTX_SOFT_RST                     BIT(11)
#define BIT_MM_AHB_RF_AHB_CKG_SOFT_RST                         BIT(10)
#define BIT_MM_AHB_RF_APB_CSI_SOFT_RST                         BIT(9)
#define BIT_MM_AHB_RF_JPG_SOFT_RST                             BIT(8)
#define BIT_MM_AHB_RF_VSP_SOFT_RST                             BIT(7)
#define BIT_MM_AHB_RF_ISP_CFG_SOFT_RST                         BIT(6)
#define BIT_MM_AHB_RF_ISP_LOG_SOFT_RST                         BIT(5)
#define BIT_MM_AHB_RF_DCAM_ROT_SOFT_RST                        BIT(4)
#define BIT_MM_AHB_RF_DCAM_CAM2_SOFT_RST                       BIT(3)
#define BIT_MM_AHB_RF_DCAM_CAM1_SOFT_RST                       BIT(2)
#define BIT_MM_AHB_RF_DCAM_CAM0_SOFT_RST                       BIT(1)
#define BIT_MM_AHB_RF_DCAM_SOFT_RST                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_GEN_CKG_CFG
// Register Offset : 0x0008
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_MIPI_CSI_CKG_EN                          BIT(4)
#define BIT_MM_AHB_RF_DCAM_AXI_CKG_EN                          BIT(3)
#define BIT_MM_AHB_RF_ISP_AXI_CKG_EN                           BIT(2)
#define BIT_MM_AHB_RF_SENSOR0_CKG_EN                           BIT(1)
#define BIT_MM_AHB_RF_CPHY_CFG_CKG_EN                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_MIPI_CSI2_CTRL
// Register Offset : 0x000C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_MIPI_CPHY_SEL                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_ISP_QOS_CTRL
// Register Offset : 0x0010
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_ISP_ARQOS(x)                             (((x) & 0xF) << 4)
#define BIT_MM_AHB_RF_ISP_AWQOS(x)                             (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_CAM_MTX_LPC_CTRL
// Register Offset : 0x0014
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_CAM_MTX_LPC_FORCE                        BIT(17)
#define BIT_MM_AHB_RF_CAM_MTX_LPC_EB                           BIT(16)
#define BIT_MM_AHB_RF_CAM_MTX_LPC_NUM(x)                       (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_VSP_MTX_LPC_CTRL_M0
// Register Offset : 0x0018
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_VSP_MTX_M0_LPC_FORCE                     BIT(17)
#define BIT_MM_AHB_RF_VSP_MTX_M0_LPC_EB                        BIT(16)
#define BIT_MM_AHB_RF_VSP_MTX_M0_LPC_NUM(x)                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_VSP_MTX_LPC_CTRL_M1
// Register Offset : 0x001C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_VSP_MTX_M1_LPC_FORCE                     BIT(17)
#define BIT_MM_AHB_RF_VSP_MTX_M1_LPC_EB                        BIT(16)
#define BIT_MM_AHB_RF_VSP_MTX_M1_LPC_NUM(x)                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_VSP_MTX_LPC_CTRL_S0
// Register Offset : 0x0020
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_VSP_MTX_S0_LPC_FORCE                     BIT(17)
#define BIT_MM_AHB_RF_VSP_MTX_S0_LPC_EB                        BIT(16)
#define BIT_MM_AHB_RF_VSP_MTX_S0_LPC_NUM(x)                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_MM_MTX_LPC_STAT
// Register Offset : 0x0024
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_VSP_MTX_S0_FORCE_ACK                     BIT(13)
#define BIT_MM_AHB_RF_VSP_MTX_GPV_FORCE_ACK                    BIT(12)
#define BIT_MM_AHB_RF_VSP_MTX_M1_FORCE_ACK                     BIT(11)
#define BIT_MM_AHB_RF_VSP_MTX_M0_FORCE_ACK                     BIT(10)
#define BIT_MM_AHB_RF_CAM_MTX_LPC_FORCE_ACK                    BIT(9)
#define BIT_MM_AHB_RF_CAM_MTX_M1_FORCE_ACK                     BIT(8)
#define BIT_MM_AHB_RF_CAM_MTX_M0_FORCE_ACK                     BIT(7)
#define BIT_MM_AHB_RF_VSP_MTX_S0_LPC_STAT                      BIT(6)
#define BIT_MM_AHB_RF_VSP_MTX_GPV_LPC_STAT                     BIT(5)
#define BIT_MM_AHB_RF_VSP_MTX_M1_LPC_STAT                      BIT(4)
#define BIT_MM_AHB_RF_VSP_MTX_M0_LPC_STAT                      BIT(3)
#define BIT_MM_AHB_RF_CAM_MTX_M1_LPC_STAT                      BIT(2)
#define BIT_MM_AHB_RF_CAM_MTX_M0_LPC_STAT                      BIT(1)
#define BIT_MM_AHB_RF_CAM_MTX_LPC_STAT                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_MM_LIGHT_SLEEP_CTRL
// Register Offset : 0x0028
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_REG_CAM_MTX_AUTO_CTRL_EN                 BIT(13)
#define BIT_MM_AHB_RF_REG_CAM_MTX_LP_DISABLE                   BIT(10)
#define BIT_MM_AHB_RF_REG_CAM_MTX_FRC_LSLP_M0                  BIT(9)
#define BIT_MM_AHB_RF_REG_CAM_MTX_FRC_LSLP_M1                  BIT(8)
#define BIT_MM_AHB_RF_REG_VSP_MTX_AUTO_CTRL_EN                 BIT(5)
#define BIT_MM_AHB_RF_REG_VSP_MTX_LP_DISABLE                   BIT(2)
#define BIT_MM_AHB_RF_REG_VSP_MTX_FRC_LSLP_M0                  BIT(1)
#define BIT_MM_AHB_RF_REG_VSP_MTX_FRC_LSLP_M1                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_CAM_MTX_LPC_CTRL_M0
// Register Offset : 0x002C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_CAM_MTX_M0_LPC_FORCE                     BIT(17)
#define BIT_MM_AHB_RF_CAM_MTX_M0_LPC_EB                        BIT(16)
#define BIT_MM_AHB_RF_CAM_MTX_M0_LPC_NUM(x)                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_CAM_MTX_LPC_CTRL_M1
// Register Offset : 0x0030
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_CAM_MTX_M1_LPC_FORCE                     BIT(17)
#define BIT_MM_AHB_RF_CAM_MTX_M1_LPC_EB                        BIT(16)
#define BIT_MM_AHB_RF_CAM_MTX_M1_LPC_NUM(x)                    (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_VSP_MTX_LPC_CTRL_GPV
// Register Offset : 0x0034
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_VSP_MTX_GPV_LPC_FORCE                    BIT(17)
#define BIT_MM_AHB_RF_VSP_MTX_GPV_LPC_EB                       BIT(16)
#define BIT_MM_AHB_RF_VSP_MTX_GPV_LPC_NUM(x)                   (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_MM_DUMMY_REG_0
// Register Offset : 0x0038
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_MM_DUMMY_REG_0(x)                        (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_MM_AHB_RF_MM_DUMMY_REG_1
// Register Offset : 0x003C
// Description     :
---------------------------------------------------------------------------*/

#define BIT_MM_AHB_RF_MM_DUMMY_REG_1(x)                        (((x) & 0xFFFFFFFF))


#endif // _MM_AHB_RF_REG_H

/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _PUB_APB_PUB0_REG_H
#define _PUB_APB_PUB0_REG_H

#define CTL_BASE_PUB_APB_PUB0 SPRD_PUB0_GLB_BASE


#define REG_PUB_APB_PUB0_PUB_INT                           ( CTL_BASE_PUB_APB_PUB0 + 0x0000 )
#define REG_PUB_APB_PUB0_BUSMON_CFG                        ( CTL_BASE_PUB_APB_PUB0 + 0x0004 )
#define REG_PUB_APB_PUB0_DMC_PORT_REMAP_EN                 ( CTL_BASE_PUB_APB_PUB0 + 0x0008 )
#define REG_PUB_APB_PUB0_DMC_PORTS_MPU_EN                  ( CTL_BASE_PUB_APB_PUB0 + 0x000C )
#define REG_PUB_APB_PUB0_DMC_PORT0_ADDR_REMAP              ( CTL_BASE_PUB_APB_PUB0 + 0x0010 )
#define REG_PUB_APB_PUB0_DMC_PORT1_ADDR_REMAP              ( CTL_BASE_PUB_APB_PUB0 + 0x0014 )
#define REG_PUB_APB_PUB0_DMC_PORT2_ADDR_REMAP              ( CTL_BASE_PUB_APB_PUB0 + 0x0018 )
#define REG_PUB_APB_PUB0_DMC_PORT3_ADDR_REMAP              ( CTL_BASE_PUB_APB_PUB0 + 0x001C )
#define REG_PUB_APB_PUB0_DMC_PORT4_ADDR_REMAP              ( CTL_BASE_PUB_APB_PUB0 + 0x0020 )
#define REG_PUB_APB_PUB0_DMC_PORT5_ADDR_REMAP              ( CTL_BASE_PUB_APB_PUB0 + 0x0024 )
#define REG_PUB_APB_PUB0_DMC_PORT0_MPU_RANGE               ( CTL_BASE_PUB_APB_PUB0 + 0x0028 )
#define REG_PUB_APB_PUB0_DMC_PORT1_MPU_RANGE               ( CTL_BASE_PUB_APB_PUB0 + 0x002C )
#define REG_PUB_APB_PUB0_DMC_PORT2_MPU_RANGE               ( CTL_BASE_PUB_APB_PUB0 + 0x0030 )
#define REG_PUB_APB_PUB0_DMC_PORT3_MPU_RANGE               ( CTL_BASE_PUB_APB_PUB0 + 0x0034 )
#define REG_PUB_APB_PUB0_DMC_PORT4_MPU_RANGE               ( CTL_BASE_PUB_APB_PUB0 + 0x0038 )
#define REG_PUB_APB_PUB0_DMC_PORT5_MPU_RANGE               ( CTL_BASE_PUB_APB_PUB0 + 0x003C )
#define REG_PUB_APB_PUB0_DMC_PORT0_DUMP_ADDR               ( CTL_BASE_PUB_APB_PUB0 + 0x0040 )
#define REG_PUB_APB_PUB0_DMC_PORT1_DUMP_ADDR               ( CTL_BASE_PUB_APB_PUB0 + 0x0044 )
#define REG_PUB_APB_PUB0_DMC_PORT2_DUMP_ADDR               ( CTL_BASE_PUB_APB_PUB0 + 0x0048 )
#define REG_PUB_APB_PUB0_DMC_PORT3_DUMP_ADDR               ( CTL_BASE_PUB_APB_PUB0 + 0x004C )
#define REG_PUB_APB_PUB0_DMC_PORT4_DUMP_ADDR               ( CTL_BASE_PUB_APB_PUB0 + 0x0050 )
#define REG_PUB_APB_PUB0_DMC_PORT5_DUMP_ADDR               ( CTL_BASE_PUB_APB_PUB0 + 0x0054 )
#define REG_PUB_APB_PUB0_DMC_PORTS_MPU_SEL                 ( CTL_BASE_PUB_APB_PUB0 + 0x0058 )
#define REG_PUB_APB_PUB0_DMC_PORT0_MPU_VIO_WADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x005C )
#define REG_PUB_APB_PUB0_DMC_PORT0_MPU_VIO_RADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x0060 )
#define REG_PUB_APB_PUB0_DMC_PORT1_MPU_VIO_WADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x0064 )
#define REG_PUB_APB_PUB0_DMC_PORT1_MPU_VIO_RADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x0068 )
#define REG_PUB_APB_PUB0_DMC_PORT2_MPU_VIO_WADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x006C )
#define REG_PUB_APB_PUB0_DMC_PORT2_MPU_VIO_RADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x0070 )
#define REG_PUB_APB_PUB0_DMC_PORT3_MPU_VIO_WADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x0074 )
#define REG_PUB_APB_PUB0_DMC_PORT3_MPU_VIO_RADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x0078 )
#define REG_PUB_APB_PUB0_DMC_PORT4_MPU_VIO_WADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x007C )
#define REG_PUB_APB_PUB0_DMC_PORT4_MPU_VIO_RADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x0080 )
#define REG_PUB_APB_PUB0_DMC_PORT5_MPU_VIO_WADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x0084 )
#define REG_PUB_APB_PUB0_DMC_PORT5_MPU_VIO_RADDR           ( CTL_BASE_PUB_APB_PUB0 + 0x0088 )
#define REG_PUB_APB_PUB0_DMC_PORT0_MPU_VIO_WCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x008C )
#define REG_PUB_APB_PUB0_DMC_PORT0_MPU_VIO_RCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x0090 )
#define REG_PUB_APB_PUB0_DMC_PORT1_MPU_VIO_WCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x0094 )
#define REG_PUB_APB_PUB0_DMC_PORT1_MPU_VIO_RCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x0098 )
#define REG_PUB_APB_PUB0_DMC_PORT2_MPU_VIO_WCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x009C )
#define REG_PUB_APB_PUB0_DMC_PORT2_MPU_VIO_RCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x00A0 )
#define REG_PUB_APB_PUB0_DMC_PORT3_MPU_VIO_WCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x00A4 )
#define REG_PUB_APB_PUB0_DMC_PORT3_MPU_VIO_RCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x00A8 )
#define REG_PUB_APB_PUB0_DMC_PORT4_MPU_VIO_WCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x00AC )
#define REG_PUB_APB_PUB0_DMC_PORT4_MPU_VIO_RCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x00B0 )
#define REG_PUB_APB_PUB0_DMC_PORT5_MPU_VIO_WCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x00B4 )
#define REG_PUB_APB_PUB0_DMC_PORT5_MPU_VIO_RCMD            ( CTL_BASE_PUB_APB_PUB0 + 0x00B8 )
#define REG_PUB_APB_PUB0_CP_BASE_ADDR                      ( CTL_BASE_PUB_APB_PUB0 + 0x00BC )
#define REG_PUB_APB_PUB0_PUB0_MTX_LP_CFG0                  ( CTL_BASE_PUB_APB_PUB0 + 0x00C0 )
#define REG_PUB_APB_PUB0_PUB0_MTX_LP_CFG1                  ( CTL_BASE_PUB_APB_PUB0 + 0x00C4 )
#define REG_PUB_APB_PUB0_PUB0_MTX_LP_CFG2                  ( CTL_BASE_PUB_APB_PUB0 + 0x00C8 )
#define REG_PUB_APB_PUB0_PUB0_MTX_LP_CFG3                  ( CTL_BASE_PUB_APB_PUB0 + 0x00CC )
#define REG_PUB_APB_PUB0_DMC_PORT0_ADDR_REMAP_REG1         ( CTL_BASE_PUB_APB_PUB0 + 0x00D0 )
#define REG_PUB_APB_PUB0_DMC_PORT1_ADDR_REMAP_REG1         ( CTL_BASE_PUB_APB_PUB0 + 0x00D4 )
#define REG_PUB_APB_PUB0_DMC_PORT2_ADDR_REMAP_REG1         ( CTL_BASE_PUB_APB_PUB0 + 0x00D8 )
#define REG_PUB_APB_PUB0_DMC_PORT3_ADDR_REMAP_REG1         ( CTL_BASE_PUB_APB_PUB0 + 0x00DC )
#define REG_PUB_APB_PUB0_DMC_PORT4_ADDR_REMAP_REG1         ( CTL_BASE_PUB_APB_PUB0 + 0x00E0 )
#define REG_PUB_APB_PUB0_DMC_PORT5_ADDR_REMAP_REG1         ( CTL_BASE_PUB_APB_PUB0 + 0x00E4 )
#define REG_PUB_APB_PUB0_DMC_PORT0_OT_CTL_REG              ( CTL_BASE_PUB_APB_PUB0 + 0x00E8 )
#define REG_PUB_APB_PUB0_DMC_PORT1_OT_CTL_REG              ( CTL_BASE_PUB_APB_PUB0 + 0x00EC )
#define REG_PUB_APB_PUB0_DMC_PORT2_OT_CTL_REG              ( CTL_BASE_PUB_APB_PUB0 + 0x00F0 )
#define REG_PUB_APB_PUB0_DMC_PORT3_OT_CTL_REG              ( CTL_BASE_PUB_APB_PUB0 + 0x00F4 )
#define REG_PUB_APB_PUB0_DMC_PORT4_OT_CTL_REG              ( CTL_BASE_PUB_APB_PUB0 + 0x00F8 )
#define REG_PUB_APB_PUB0_DMC_PORT5_OT_CTL_REG              ( CTL_BASE_PUB_APB_PUB0 + 0x00FC )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG_CFG0              ( CTL_BASE_PUB_APB_PUB0 + 0x0200 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG_CFG1              ( CTL_BASE_PUB_APB_PUB0 + 0x0204 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG_CFG2              ( CTL_BASE_PUB_APB_PUB0 + 0x0208 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x0210 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x0214 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x0218 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x021C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x0220 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x0224 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x0228 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x022C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x0230 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_ADDR             ( CTL_BASE_PUB_APB_PUB0 + 0x0234 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x0238 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x023C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x0240 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x0244 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x0248 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x024C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x0250 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x0254 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x0258 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_ADDR            ( CTL_BASE_PUB_APB_PUB0 + 0x025C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x0300 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x0304 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x0308 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x030C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x0310 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x0314 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x0318 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x031C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x0320 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_DATA_F0          ( CTL_BASE_PUB_APB_PUB0 + 0x0324 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x0328 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x032C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x0330 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x0334 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x0338 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x033C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x0340 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x0344 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x0348 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_DATA_F0         ( CTL_BASE_PUB_APB_PUB0 + 0x034C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x0380 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x0384 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x0388 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x038C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x0390 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x0394 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x0398 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x039C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x03A0 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_DATA_F1          ( CTL_BASE_PUB_APB_PUB0 + 0x03A4 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03A8 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03AC )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03B0 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03B4 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03B8 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03BC )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03C0 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03C4 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03C8 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_DATA_F1         ( CTL_BASE_PUB_APB_PUB0 + 0x03CC )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x0400 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x0404 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x0408 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x040C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x0410 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x0414 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x0418 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x041C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x0420 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_DATA_F2          ( CTL_BASE_PUB_APB_PUB0 + 0x0424 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x0428 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x042C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x0430 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x0434 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x0438 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x043C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x0440 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x0444 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x0448 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_DATA_F2         ( CTL_BASE_PUB_APB_PUB0 + 0x044C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x0480 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x0484 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x0488 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x048C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x0490 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x0494 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x0498 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x049C )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x04A0 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_DATA_F3          ( CTL_BASE_PUB_APB_PUB0 + 0x04A4 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04A8 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04AC )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04B0 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04B4 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04B8 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04BC )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04C0 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04C4 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04C8 )
#define REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_DATA_F3         ( CTL_BASE_PUB_APB_PUB0 + 0x04CC )
#define REG_PUB_APB_PUB0_PUB_LP_CTRL_0                     ( CTL_BASE_PUB_APB_PUB0 + 0x04D0 )
#define REG_PUB_APB_PUB0_AXI_CHN0_LP_EN                    ( CTL_BASE_PUB_APB_PUB0 + 0x4000 )
#define REG_PUB_APB_PUB0_AXI_CHN1_LP_EN                    ( CTL_BASE_PUB_APB_PUB0 + 0x4004 )
#define REG_PUB_APB_PUB0_AXI_CHN2_LP_EN                    ( CTL_BASE_PUB_APB_PUB0 + 0x4008 )
#define REG_PUB_APB_PUB0_AXI_CHN3_LP_EN                    ( CTL_BASE_PUB_APB_PUB0 + 0x400C )
#define REG_PUB_APB_PUB0_AXI_CHN4_LP_EN                    ( CTL_BASE_PUB_APB_PUB0 + 0x4010 )
#define REG_PUB_APB_PUB0_AXI_CHN5_LP_EN                    ( CTL_BASE_PUB_APB_PUB0 + 0x4014 )
#define REG_PUB_APB_PUB0_AXI_CHN0_LP_IDLE_CNT              ( CTL_BASE_PUB_APB_PUB0 + 0x4018 )
#define REG_PUB_APB_PUB0_AXI_CHN1_LP_IDLE_CNT              ( CTL_BASE_PUB_APB_PUB0 + 0x401C )
#define REG_PUB_APB_PUB0_AXI_CHN2_LP_IDLE_CNT              ( CTL_BASE_PUB_APB_PUB0 + 0x4020 )
#define REG_PUB_APB_PUB0_AXI_CHN3_LP_IDLE_CNT              ( CTL_BASE_PUB_APB_PUB0 + 0x4024 )
#define REG_PUB_APB_PUB0_AXI_CHN4_LP_IDLE_CNT              ( CTL_BASE_PUB_APB_PUB0 + 0x4028 )
#define REG_PUB_APB_PUB0_AXI_CHN5_LP_IDLE_CNT              ( CTL_BASE_PUB_APB_PUB0 + 0x402C )
#define REG_PUB_APB_PUB0_PUB_CHN0_LP_CTRL                  ( CTL_BASE_PUB_APB_PUB0 + 0x4030 )
#define REG_PUB_APB_PUB0_PUB_CHN1_LP_CTRL                  ( CTL_BASE_PUB_APB_PUB0 + 0x4034 )
#define REG_PUB_APB_PUB0_PUB_CHN2_LP_CTRL                  ( CTL_BASE_PUB_APB_PUB0 + 0x4038 )
#define REG_PUB_APB_PUB0_PUB_CHN3_LP_CTRL                  ( CTL_BASE_PUB_APB_PUB0 + 0x403C )
#define REG_PUB_APB_PUB0_PUB_CHN4_LP_CTRL                  ( CTL_BASE_PUB_APB_PUB0 + 0x4040 )
#define REG_PUB_APB_PUB0_PUB_CHN5_LP_CTRL                  ( CTL_BASE_PUB_APB_PUB0 + 0x4044 )
#define REG_PUB_APB_PUB0_PUB_AUTO_GATE_COUNTER             ( CTL_BASE_PUB_APB_PUB0 + 0x4048 )
#define REG_PUB_APB_PUB0_MC_IDLE_WAIT_CTRL                 ( CTL_BASE_PUB_APB_PUB0 + 0x404C )
#define REG_PUB_APB_PUB0_CGM_DDR_MCTRL_DIV                 ( CTL_BASE_PUB_APB_PUB0 + 0x4050 )
#define REG_PUB_APB_PUB0_CA_OE_CTRL                        ( CTL_BASE_PUB_APB_PUB0 + 0x4054 )
#define REG_PUB_APB_PUB0_PUB_SOFT_DFS_CTRL                 ( CTL_BASE_PUB_APB_PUB0 + 0x8000 )
#define REG_PUB_APB_PUB0_PUB_HARD_DFS_CTRL_LO              ( CTL_BASE_PUB_APB_PUB0 + 0x8004 )
#define REG_PUB_APB_PUB0_PUB_HARD_DFS_CTRL_HI              ( CTL_BASE_PUB_APB_PUB0 + 0x8008 )
#define REG_PUB_APB_PUB0_PUB_SOFT_PURE_DFS_CTRL            ( CTL_BASE_PUB_APB_PUB0 + 0x800C )
#define REG_PUB_APB_PUB0_PUB_SOFT_PURE_DFS_CMD_STEP        ( CTL_BASE_PUB_APB_PUB0 + 0x8010 )
#define REG_PUB_APB_PUB0_PUB_SOFT_PURE_DFS_CMD_SEQ_LO      ( CTL_BASE_PUB_APB_PUB0 + 0x8014 )
#define REG_PUB_APB_PUB0_PUB_SOFT_PURE_DFS_CMD_SEQ_HI      ( CTL_BASE_PUB_APB_PUB0 + 0x8018 )
#define REG_PUB_APB_PUB0_AXI_AW_COBUF_EN                   ( CTL_BASE_PUB_APB_PUB0 + 0x801C )
#define REG_PUB_APB_PUB0_AXI_AWAPCMD_EN                    ( CTL_BASE_PUB_APB_PUB0 + 0x8020 )
#define REG_PUB_APB_PUB0_AXI_ARAPCMD_EN                    ( CTL_BASE_PUB_APB_PUB0 + 0x8024 )
#define REG_PUB_APB_PUB0_PUB_BIST_TEST_CTRL                ( CTL_BASE_PUB_APB_PUB0 + 0x8028 )
#define REG_PUB_APB_PUB0_PUB_LP_GEN_CTRL                   ( CTL_BASE_PUB_APB_PUB0 + 0x802C )
#define REG_PUB_APB_PUB0_PUB_PURE_SW_DFS_CTRL              ( CTL_BASE_PUB_APB_PUB0 + 0x8030 )
#define REG_PUB_APB_PUB0_PUB_DFS_STATUS                    ( CTL_BASE_PUB_APB_PUB0 + 0x8034 )
#define REG_PUB_APB_PUB0_PUB_PHY_BIST_CTRL_0               ( CTL_BASE_PUB_APB_PUB0 + 0x8038 )
#define REG_PUB_APB_PUB0_PUB_PHY_BIST_CTRL_1               ( CTL_BASE_PUB_APB_PUB0 + 0x803C )
#define REG_PUB_APB_PUB0_PUB_PHY_BIST_CTRL_2               ( CTL_BASE_PUB_APB_PUB0 + 0x8040 )
#define REG_PUB_APB_PUB0_PUB_PHY_VERF_CTRL                 ( CTL_BASE_PUB_APB_PUB0 + 0x8044 )
#define REG_PUB_APB_PUB0_PHY_BIST_AC_GRP0                  ( CTL_BASE_PUB_APB_PUB0 + 0x8048 )
#define REG_PUB_APB_PUB0_PHY_BIST_AC_GRP1                  ( CTL_BASE_PUB_APB_PUB0 + 0x804C )
#define REG_PUB_APB_PUB0_PHY_BIST_AC_GRP2                  ( CTL_BASE_PUB_APB_PUB0 + 0x8050 )
#define REG_PUB_APB_PUB0_PHY_BIST_ADR_GRP0                 ( CTL_BASE_PUB_APB_PUB0 + 0x8054 )
#define REG_PUB_APB_PUB0_PHY_BIST_ADR_GRP1                 ( CTL_BASE_PUB_APB_PUB0 + 0x8058 )
#define REG_PUB_APB_PUB0_PHY_BIST_DONE_GRP                 ( CTL_BASE_PUB_APB_PUB0 + 0x805C )
#define REG_PUB_APB_PUB0_PHY_BIST_ERR_GRP0                 ( CTL_BASE_PUB_APB_PUB0 + 0x8060 )
#define REG_PUB_APB_PUB0_PHY_BIST_ERR_GRP1                 ( CTL_BASE_PUB_APB_PUB0 + 0x8064 )
#define REG_PUB_APB_PUB0_DFI_WDQLVL_GRP0                   ( CTL_BASE_PUB_APB_PUB0 + 0x8068 )
#define REG_PUB_APB_PUB0_CTRL_DP_IDLE                      ( CTL_BASE_PUB_APB_PUB0 + 0x806C )
#define REG_PUB_APB_PUB0_OPCG_CTRL                         ( CTL_BASE_PUB_APB_PUB0 + 0x8070 )
#define REG_PUB_APB_PUB0_ZQ_CTRL                           ( CTL_BASE_PUB_APB_PUB0 + 0x8074 )
#define REG_PUB_APB_PUB0_PHY_BIST_PLL_MODE0                ( CTL_BASE_PUB_APB_PUB0 + 0x8078 )
#define REG_PUB_APB_PUB0_PHY_BIST_PLL_MODE1                ( CTL_BASE_PUB_APB_PUB0 + 0x807C )
#define REG_PUB_APB_PUB0_PHY_BIST_PLL_MODE2                ( CTL_BASE_PUB_APB_PUB0 + 0x8080 )
#define REG_PUB_APB_PUB0_PHY_BIST_TOP_PLL_MODE0            ( CTL_BASE_PUB_APB_PUB0 + 0x8084 )
#define REG_PUB_APB_PUB0_PHY_BIST_TOP_PLL_MODE1            ( CTL_BASE_PUB_APB_PUB0 + 0x8088 )
#define REG_PUB_APB_PUB0_PHY_BIST_TOP_PLL_MODE2            ( CTL_BASE_PUB_APB_PUB0 + 0x808C )
#define REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_PUBCP0           ( CTL_BASE_PUB_APB_PUB0 + 0x8090 )
#define REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_PUBCP1           ( CTL_BASE_PUB_APB_PUB0 + 0x8094 )
#define REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_WTL0_0           ( CTL_BASE_PUB_APB_PUB0 + 0x8098 )
#define REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_WTL0_1           ( CTL_BASE_PUB_APB_PUB0 + 0x809C )
#define REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_WTL1_0           ( CTL_BASE_PUB_APB_PUB0 + 0x80A0 )
#define REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_WTL1_1           ( CTL_BASE_PUB_APB_PUB0 + 0x80A4 )
#define REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_AG               ( CTL_BASE_PUB_APB_PUB0 + 0x80A8 )
#define REG_PUB_APB_PUB0_AWCACHE_SW                        ( CTL_BASE_PUB_APB_PUB0 + 0x80AC )
#define REG_PUB_APB_PUB0_ARCACHE_SW                        ( CTL_BASE_PUB_APB_PUB0 + 0x80B0 )
#define REG_PUB_APB_PUB0_AWCACHE_SW_EN                     ( CTL_BASE_PUB_APB_PUB0 + 0x80B4 )
#define REG_PUB_APB_PUB0_ARCACHE_SW_EN                     ( CTL_BASE_PUB_APB_PUB0 + 0x80B8 )
#define REG_PUB_APB_PUB0_PUB0_DUMMY_REG0                   ( CTL_BASE_PUB_APB_PUB0 + 0x80BC )
#define REG_PUB_APB_PUB0_PUB0_DUMMY_REG1                   ( CTL_BASE_PUB_APB_PUB0 + 0x80C0 )
#define REG_PUB_APB_PUB0_PUB0_PHY_BIST                     ( CTL_BASE_PUB_APB_PUB0 + 0x80C4 )
#define REG_PUB_APB_PUB0_AXI_DEBUG_STATUS                  ( CTL_BASE_PUB_APB_PUB0 + 0x80C8 )

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_INT
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_RF_INT_DMC_MPU_VIO                                     BIT(23)
#define BIT_PUB_APB_PUB0_RF_DMC_MPU_VIO_INT_RAW                                 BIT(22)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_INT_CLR                                    BIT(21)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_INT_EN                                     BIT(20)
#define BIT_PUB_APB_PUB0_CAM_SWITCH_EN                                          BIT(16)
#define BIT_PUB_APB_PUB0_RF_INT_DFS_ERROR                                       BIT(15)
#define BIT_PUB_APB_PUB0_RF_DFS_ERROR_INT_RAW                                   BIT(14)
#define BIT_PUB_APB_PUB0_DFS_ERROR_INT_CLR                                      BIT(13)
#define BIT_PUB_APB_PUB0_DFS_ERROR_INT_EN                                       BIT(12)
#define BIT_PUB_APB_PUB0_RF_INT_BUSMON_DMA                                      BIT(11)
#define BIT_PUB_APB_PUB0_RF_BUSMON_DMA_INT_RAW                                  BIT(10)
#define BIT_PUB_APB_PUB0_BUSMON_DMA_INT_CLR                                     BIT(9)
#define BIT_PUB_APB_PUB0_BUSMON_DMA_INT_EN                                      BIT(8)
#define BIT_PUB_APB_PUB0_RF_INT_HW_DFS_EXIT                                     BIT(7)
#define BIT_PUB_APB_PUB0_RF_HW_DFS_EXIT_INT_RAW                                 BIT(6)
#define BIT_PUB_APB_PUB0_HW_DFS_EXIT_INT_CLR                                    BIT(5)
#define BIT_PUB_APB_PUB0_HW_DFS_EXIT_INT_EN                                     BIT(4)
#define BIT_PUB_APB_PUB0_RF_INT_DFS_COMPLETE                                    BIT(3)
#define BIT_PUB_APB_PUB0_RF_DFS_COMPLETE_INT_RAW                                BIT(2)
#define BIT_PUB_APB_PUB0_DFS_COMPLETE_INT_CLR                                   BIT(1)
#define BIT_PUB_APB_PUB0_DFS_COMPLETE_INT_EN                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_BUSMON_CFG
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_ID_COMP_EB                                         BIT(31)
#define BIT_PUB_APB_PUB0_DFS_AHB_MASTER_EB                                      BIT(30)
#define BIT_PUB_APB_PUB0_DMC_MPU_EB                                             BIT(29)
#define BIT_PUB_APB_PUB0_MCTL_AXI_CFG_EB                                        BIT(28)
#define BIT_PUB_APB_PUB0_PUB_APB_REG_EB                                         BIT(27)
#define BIT_PUB_APB_PUB0_PUB_BUSMON5_EB                                         BIT(26)
#define BIT_PUB_APB_PUB0_PUB_BUSMON4_EB                                         BIT(25)
#define BIT_PUB_APB_PUB0_PUB_BUSMON3_EB                                         BIT(24)
#define BIT_PUB_APB_PUB0_PUB_BUSMON2_EB                                         BIT(23)
#define BIT_PUB_APB_PUB0_PUB_BUSMON1_EB                                         BIT(22)
#define BIT_PUB_APB_PUB0_PUB_BUSMON0_EB                                         BIT(21)
#define BIT_PUB_APB_PUB0_PUB_BUSMON5_SOFT_RST                                   BIT(5)
#define BIT_PUB_APB_PUB0_PUB_BUSMON4_SOFT_RST                                   BIT(4)
#define BIT_PUB_APB_PUB0_PUB_BUSMON3_SOFT_RST                                   BIT(3)
#define BIT_PUB_APB_PUB0_PUB_BUSMON2_SOFT_RST                                   BIT(2)
#define BIT_PUB_APB_PUB0_PUB_BUSMON1_SOFT_RST                                   BIT(1)
#define BIT_PUB_APB_PUB0_PUB_BUSMON0_SOFT_RST                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT_REMAP_EN
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORTS_REMAP_EN(x)                                  (((x) & 0xFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORTS_MPU_EN
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORTS_MPU_EN(x)                                    (((x) & 0xFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT0_ADDR_REMAP
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT0_ADDR_REMAP(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT1_ADDR_REMAP
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT1_ADDR_REMAP(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT2_ADDR_REMAP
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT2_ADDR_REMAP(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT3_ADDR_REMAP
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT3_ADDR_REMAP(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT4_ADDR_REMAP
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT4_ADDR_REMAP(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT5_ADDR_REMAP
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT5_ADDR_REMAP(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT0_MPU_RANGE
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT0_MPU_RANGE(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT1_MPU_RANGE
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT1_MPU_RANGE(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT2_MPU_RANGE
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT2_MPU_RANGE(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT3_MPU_RANGE
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT3_MPU_RANGE(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT4_MPU_RANGE
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT4_MPU_RANGE(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT5_MPU_RANGE
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT5_MPU_RANGE(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT0_DUMP_ADDR
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT0_DUMP_ADDR(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT1_DUMP_ADDR
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT1_DUMP_ADDR(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT2_DUMP_ADDR
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT2_DUMP_ADDR(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT3_DUMP_ADDR
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT3_DUMP_ADDR(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT4_DUMP_ADDR
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT4_DUMP_ADDR(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT5_DUMP_ADDR
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT5_DUMP_ADDR(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORTS_MPU_SEL
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORTS_MPU_SEL(x)                                   (((x) & 0xFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT0_MPU_VIO_WADDR
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWADDR0(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT0_MPU_VIO_RADDR
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARADDR0(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT1_MPU_VIO_WADDR
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWADDR1(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT1_MPU_VIO_RADDR
// Register Offset : 0x0068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARADDR1(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT2_MPU_VIO_WADDR
// Register Offset : 0x006C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWADDR2(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT2_MPU_VIO_RADDR
// Register Offset : 0x0070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARADDR2(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT3_MPU_VIO_WADDR
// Register Offset : 0x0074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWADDR3(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT3_MPU_VIO_RADDR
// Register Offset : 0x0078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARADDR3(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT4_MPU_VIO_WADDR
// Register Offset : 0x007C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWADDR4(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT4_MPU_VIO_RADDR
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARADDR4(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT5_MPU_VIO_WADDR
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWADDR5(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT5_MPU_VIO_RADDR
// Register Offset : 0x0088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARADDR5(x)                                 (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT0_MPU_VIO_WCMD
// Register Offset : 0x008C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWID0(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWBURST0(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWSIZE0(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWLEN0(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT0_MPU_VIO_RCMD
// Register Offset : 0x0090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARID0(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARBURST0(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARSIZE0(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARLEN0(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT1_MPU_VIO_WCMD
// Register Offset : 0x0094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWID1(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWBURST1(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWSIZE1(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWLEN1(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT1_MPU_VIO_RCMD
// Register Offset : 0x0098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARID1(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARBURST1(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARSIZE1(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARLEN1(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT2_MPU_VIO_WCMD
// Register Offset : 0x009C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWID2(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWBURST2(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWSIZE2(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWLEN2(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT2_MPU_VIO_RCMD
// Register Offset : 0x00A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARID2(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARBURST2(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARSIZE2(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARLEN2(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT3_MPU_VIO_WCMD
// Register Offset : 0x00A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWID3(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWBURST3(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWSIZE3(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWLEN3(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT3_MPU_VIO_RCMD
// Register Offset : 0x00A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARID3(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARBURST3(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARSIZE3(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARLEN3(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT4_MPU_VIO_WCMD
// Register Offset : 0x00AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWID4(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWBURST4(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWSIZE4(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWLEN4(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT4_MPU_VIO_RCMD
// Register Offset : 0x00B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARID4(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARBURST4(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARSIZE4(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARLEN4(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT5_MPU_VIO_WCMD
// Register Offset : 0x00B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWID5(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWBURST5(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWSIZE5(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_AWLEN5(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT5_MPU_VIO_RCMD
// Register Offset : 0x00B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARID5(x)                                   (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARBURST5(x)                                (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARSIZE5(x)                                 (((x) & 0x7) << 8)
#define BIT_PUB_APB_PUB0_DMC_MPU_VIO_ARLEN5(x)                                  (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_CP_BASE_ADDR
// Register Offset : 0x00BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AG_CP_BASE_ADDR(x)                                     (((x) & 0xF) << 12)
#define BIT_PUB_APB_PUB0_WTL1_CP_BASE_ADDR(x)                                   (((x) & 0xF) << 8)
#define BIT_PUB_APB_PUB0_WTL0_CP_BASE_ADDR(x)                                   (((x) & 0xF) << 4)
#define BIT_PUB_APB_PUB0_PUB_CP_BASE_ADDR(x)                                    (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB0_MTX_LP_CFG0
// Register Offset : 0x00C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S4_ACTIVE_SYNC_SEL                        BIT(15)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S4_LP_FORCE                               BIT(14)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S4_LP_EN                                  BIT(13)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S3_ACTIVE_SYNC_SEL                        BIT(12)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S3_LP_FORCE                               BIT(11)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S3_LP_EN                                  BIT(10)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S2_ACTIVE_SYNC_SEL                        BIT(9)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S2_LP_FORCE                               BIT(8)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S2_LP_EN                                  BIT(7)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S1_ACTIVE_SYNC_SEL                        BIT(6)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S1_LP_EN                                  BIT(5)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S0_ACTIVE_SYNC_SEL                        BIT(4)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S0_LP_FORCE                               BIT(3)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_S0_LP_EN                                  BIT(2)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_M0_ACTIVE_SYNC_SEL                        BIT(1)
#define BIT_PUB_APB_PUB0_PUB0_TOP_MTX_M0_LP_EN                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB0_MTX_LP_CFG1
// Register Offset : 0x00C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_S1_ACTIVE_SYNC_SEL                     BIT(17)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_S1_LP_FORCE                            BIT(16)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_S1_LP_EN                               BIT(15)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_S0_ACTIVE_SYNC_SEL                     BIT(14)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_S0_LP_FORCE                            BIT(13)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_S0_LP_EN                               BIT(12)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M3_ACTIVE_SYNC_SEL                     BIT(11)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M3_LP_FORCE                            BIT(10)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M3_LP_EN                               BIT(9)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M2_ACTIVE_SYNC_SEL                     BIT(8)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M2_LP_FORCE                            BIT(7)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M2_LP_EN                               BIT(6)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M1_ACTIVE_SYNC_SEL                     BIT(5)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M1_LP_FORCE                            BIT(4)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M1_LP_EN                               BIT(3)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M0_ACTIVE_SYNC_SEL                     BIT(2)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M0_LP_FORCE                            BIT(1)
#define BIT_PUB_APB_PUB0_PUB0_AG_WTL_MTX_M0_LP_EN                               BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB0_MTX_LP_CFG2
// Register Offset : 0x00C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB0_MTX_LP_NUM(x)                                     (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB0_MTX_LP_CFG3
// Register Offset : 0x00CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB0_CH3_SLICE_ACTIVE_SYNC_SEL                         BIT(11)
#define BIT_PUB_APB_PUB0_PUB0_CH3_SLICE_LP_FORCE                                BIT(10)
#define BIT_PUB_APB_PUB0_PUB0_CH3_SLICE_LP_EN                                   BIT(9)
#define BIT_PUB_APB_PUB0_PUB0_CH2_SLICE_ACTIVE_SYNC_SEL                         BIT(8)
#define BIT_PUB_APB_PUB0_PUB0_CH2_SLICE_LP_FORCE                                BIT(7)
#define BIT_PUB_APB_PUB0_PUB0_CH2_SLICE_LP_EN                                   BIT(6)
#define BIT_PUB_APB_PUB0_PUB0_CH1_SLICE_ACTIVE_SYNC_SEL                         BIT(5)
#define BIT_PUB_APB_PUB0_PUB0_CH1_SLICE_LP_FORCE                                BIT(4)
#define BIT_PUB_APB_PUB0_PUB0_CH1_SLICE_LP_EN                                   BIT(3)
#define BIT_PUB_APB_PUB0_PUB0_CH0_SLICE_ACTIVE_SYNC_SEL                         BIT(2)
#define BIT_PUB_APB_PUB0_PUB0_CH0_SLICE_LP_FORCE                                BIT(1)
#define BIT_PUB_APB_PUB0_PUB0_CH0_SLICE_LP_EN                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT0_ADDR_REMAP_REG1
// Register Offset : 0x00D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT0_ADDR_REMAP_REG1(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT1_ADDR_REMAP_REG1
// Register Offset : 0x00D4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT1_ADDR_REMAP_REG1(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT2_ADDR_REMAP_REG1
// Register Offset : 0x00D8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT2_ADDR_REMAP_REG1(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT3_ADDR_REMAP_REG1
// Register Offset : 0x00DC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT3_ADDR_REMAP_REG1(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT4_ADDR_REMAP_REG1
// Register Offset : 0x00E0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT4_ADDR_REMAP_REG1(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT5_ADDR_REMAP_REG1
// Register Offset : 0x00E4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DMC_PORT5_ADDR_REMAP_REG1(x)                           (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT0_OT_CTL_REG
// Register Offset : 0x00E8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_OT_CTRL_0_BYPASS_MODE                                  BIT(31)
#define BIT_PUB_APB_PUB0_AR_MAX_OT_0(x)                                         (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB0_AW_MAX_OT_0(x)                                         (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT1_OT_CTL_REG
// Register Offset : 0x00EC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_OT_CTRL_1_BYPASS_MODE                                  BIT(31)
#define BIT_PUB_APB_PUB0_AR_MAX_OT_1(x)                                         (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB0_AW_MAX_OT_1(x)                                         (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT2_OT_CTL_REG
// Register Offset : 0x00F0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_OT_CTRL_2_BYPASS_MODE                                  BIT(31)
#define BIT_PUB_APB_PUB0_AR_MAX_OT_2(x)                                         (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB0_AW_MAX_OT_2(x)                                         (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT3_OT_CTL_REG
// Register Offset : 0x00F4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_OT_CTRL_3_BYPASS_MODE                                  BIT(31)
#define BIT_PUB_APB_PUB0_AR_MAX_OT_3(x)                                         (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB0_AW_MAX_OT_3(x)                                         (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT4_OT_CTL_REG
// Register Offset : 0x00F8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_OT_CTRL_4_BYPASS_MODE                                  BIT(31)
#define BIT_PUB_APB_PUB0_AR_MAX_OT_4(x)                                         (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB0_AW_MAX_OT_4(x)                                         (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DMC_PORT5_OT_CTL_REG
// Register Offset : 0x00FC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_OT_CTRL_5_BYPASS_MODE                                  BIT(31)
#define BIT_PUB_APB_PUB0_AR_MAX_OT_5(x)                                         (((x) & 0x7F) << 8)
#define BIT_PUB_APB_PUB0_AW_MAX_OT_5(x)                                         (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG_CFG0
// Register Offset : 0x0200
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG_BASE_ADDR(x)                                  (((x) & 0xFFFF) << 16)
#define BIT_PUB_APB_PUB0_DFS_WR_MCTL_REG_ERROR                                  BIT(15)
#define BIT_PUB_APB_PUB0_DFS_WR_MCTL_REG_COMPLETE                               BIT(14)
#define BIT_PUB_APB_PUB0_DFS_FC_ACK_WAIT_COMP_EN                                BIT(13)
#define BIT_PUB_APB_PUB0_DFS_WR_MCTL_REG_NUM(x)                                 (((x) & 0x1F) << 8)
#define BIT_PUB_APB_PUB0_DFS_WR_AHB_HPROT(x)                                    (((x) & 0xF) << 4)
#define BIT_PUB_APB_PUB0_SW_WR_MCTL_REG_TRIG                                    BIT(3)
#define BIT_PUB_APB_PUB0_DFS_WR_MCTL_REG_MODE(x)                                (((x) & 0x3) << 1)
#define BIT_PUB_APB_PUB0_DFS_WR_MCTL_REG_EN                                     BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG_CFG1
// Register Offset : 0x0204
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_FC_SEL7_FN(x)                                     (((x) & 0x3) << 28)
#define BIT_PUB_APB_PUB0_MCTL_FC_SEL6_FN(x)                                     (((x) & 0x3) << 24)
#define BIT_PUB_APB_PUB0_MCTL_FC_SEL5_FN(x)                                     (((x) & 0x3) << 20)
#define BIT_PUB_APB_PUB0_MCTL_FC_SEL4_FN(x)                                     (((x) & 0x3) << 16)
#define BIT_PUB_APB_PUB0_MCTL_FC_SEL3_FN(x)                                     (((x) & 0x3) << 12)
#define BIT_PUB_APB_PUB0_MCTL_FC_SEL2_FN(x)                                     (((x) & 0x3) << 8)
#define BIT_PUB_APB_PUB0_MCTL_FC_SEL1_FN(x)                                     (((x) & 0x3) << 4)
#define BIT_PUB_APB_PUB0_MCTL_FC_SEL0_FN(x)                                     (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG_CFG2
// Register Offset : 0x0208
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DFS_WR_MCTL_WAIT_PERIOD(x)                             (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_ADDR
// Register Offset : 0x0210
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG0_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_ADDR
// Register Offset : 0x0214
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG1_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_ADDR
// Register Offset : 0x0218
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG2_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_ADDR
// Register Offset : 0x021C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG3_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_ADDR
// Register Offset : 0x0220
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG4_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_ADDR
// Register Offset : 0x0224
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG5_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_ADDR
// Register Offset : 0x0228
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG6_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_ADDR
// Register Offset : 0x022C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG7_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_ADDR
// Register Offset : 0x0230
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG8_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_ADDR
// Register Offset : 0x0234
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG9_ADDR(x)                                      (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_ADDR
// Register Offset : 0x0238
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG10_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_ADDR
// Register Offset : 0x023C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG11_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_ADDR
// Register Offset : 0x0240
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG12_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_ADDR
// Register Offset : 0x0244
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG13_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_ADDR
// Register Offset : 0x0248
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG14_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_ADDR
// Register Offset : 0x024C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG15_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_ADDR
// Register Offset : 0x0250
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG16_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_ADDR
// Register Offset : 0x0254
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG17_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_ADDR
// Register Offset : 0x0258
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG18_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_ADDR
// Register Offset : 0x025C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG19_ADDR(x)                                     (((x) & 0xFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_DATA_F0
// Register Offset : 0x0300
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG0_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_DATA_F0
// Register Offset : 0x0304
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG1_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_DATA_F0
// Register Offset : 0x0308
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG2_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_DATA_F0
// Register Offset : 0x030C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG3_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_DATA_F0
// Register Offset : 0x0310
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG4_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_DATA_F0
// Register Offset : 0x0314
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG5_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_DATA_F0
// Register Offset : 0x0318
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG6_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_DATA_F0
// Register Offset : 0x031C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG7_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_DATA_F0
// Register Offset : 0x0320
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG8_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_DATA_F0
// Register Offset : 0x0324
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG9_DATA_F0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_DATA_F0
// Register Offset : 0x0328
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG10_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_DATA_F0
// Register Offset : 0x032C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG11_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_DATA_F0
// Register Offset : 0x0330
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG12_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_DATA_F0
// Register Offset : 0x0334
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG13_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_DATA_F0
// Register Offset : 0x0338
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG14_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_DATA_F0
// Register Offset : 0x033C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG15_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_DATA_F0
// Register Offset : 0x0340
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG16_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_DATA_F0
// Register Offset : 0x0344
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG17_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_DATA_F0
// Register Offset : 0x0348
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG18_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_DATA_F0
// Register Offset : 0x034C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG19_DATA_F0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_DATA_F1
// Register Offset : 0x0380
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG0_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_DATA_F1
// Register Offset : 0x0384
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG1_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_DATA_F1
// Register Offset : 0x0388
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG2_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_DATA_F1
// Register Offset : 0x038C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG3_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_DATA_F1
// Register Offset : 0x0390
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG4_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_DATA_F1
// Register Offset : 0x0394
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG5_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_DATA_F1
// Register Offset : 0x0398
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG6_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_DATA_F1
// Register Offset : 0x039C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG7_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_DATA_F1
// Register Offset : 0x03A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG8_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_DATA_F1
// Register Offset : 0x03A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG9_DATA_F1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_DATA_F1
// Register Offset : 0x03A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG10_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_DATA_F1
// Register Offset : 0x03AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG11_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_DATA_F1
// Register Offset : 0x03B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG12_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_DATA_F1
// Register Offset : 0x03B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG13_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_DATA_F1
// Register Offset : 0x03B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG14_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_DATA_F1
// Register Offset : 0x03BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG15_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_DATA_F1
// Register Offset : 0x03C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG16_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_DATA_F1
// Register Offset : 0x03C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG17_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_DATA_F1
// Register Offset : 0x03C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG18_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_DATA_F1
// Register Offset : 0x03CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG19_DATA_F1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_DATA_F2
// Register Offset : 0x0400
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG0_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_DATA_F2
// Register Offset : 0x0404
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG1_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_DATA_F2
// Register Offset : 0x0408
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG2_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_DATA_F2
// Register Offset : 0x040C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG3_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_DATA_F2
// Register Offset : 0x0410
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG4_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_DATA_F2
// Register Offset : 0x0414
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG5_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_DATA_F2
// Register Offset : 0x0418
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG6_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_DATA_F2
// Register Offset : 0x041C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG7_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_DATA_F2
// Register Offset : 0x0420
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG8_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_DATA_F2
// Register Offset : 0x0424
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG9_DATA_F2(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_DATA_F2
// Register Offset : 0x0428
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG10_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_DATA_F2
// Register Offset : 0x042C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG11_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_DATA_F2
// Register Offset : 0x0430
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG12_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_DATA_F2
// Register Offset : 0x0434
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG13_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_DATA_F2
// Register Offset : 0x0438
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG14_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_DATA_F2
// Register Offset : 0x043C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG15_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_DATA_F2
// Register Offset : 0x0440
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG16_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_DATA_F2
// Register Offset : 0x0444
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG17_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_DATA_F2
// Register Offset : 0x0448
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG18_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_DATA_F2
// Register Offset : 0x044C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG19_DATA_F2(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG0_DATA_F3
// Register Offset : 0x0480
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG0_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG1_DATA_F3
// Register Offset : 0x0484
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG1_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG2_DATA_F3
// Register Offset : 0x0488
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG2_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG3_DATA_F3
// Register Offset : 0x048C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG3_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG4_DATA_F3
// Register Offset : 0x0490
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG4_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG5_DATA_F3
// Register Offset : 0x0494
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG5_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG6_DATA_F3
// Register Offset : 0x0498
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG6_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG7_DATA_F3
// Register Offset : 0x049C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG7_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG8_DATA_F3
// Register Offset : 0x04A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG8_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG9_DATA_F3
// Register Offset : 0x04A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG9_DATA_F3(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG10_DATA_F3
// Register Offset : 0x04A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG10_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG11_DATA_F3
// Register Offset : 0x04AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG11_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG12_DATA_F3
// Register Offset : 0x04B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG12_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG13_DATA_F3
// Register Offset : 0x04B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG13_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG14_DATA_F3
// Register Offset : 0x04B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG14_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG15_DATA_F3
// Register Offset : 0x04BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG15_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG16_DATA_F3
// Register Offset : 0x04C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG16_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG17_DATA_F3
// Register Offset : 0x04C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG17_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG18_DATA_F3
// Register Offset : 0x04C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG18_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFS_WR_MCTL_REG19_DATA_F3
// Register Offset : 0x04CC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MCTL_REG19_DATA_F3(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_LP_CTRL_0
// Register Offset : 0x04D0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB_LP_DUMMY_REG(x)                                    (((x) & 0x7FFFFFFF) << 1)
#define BIT_PUB_APB_PUB0_PUB_LP_CTRL_DDR_INIT_FINISH_FLAG_EN                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN0_LP_EN
// Register Offset : 0x4000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN0_LP_EN                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN1_LP_EN
// Register Offset : 0x4004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN1_LP_EN                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN2_LP_EN
// Register Offset : 0x4008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN2_LP_EN                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN3_LP_EN
// Register Offset : 0x400C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN3_LP_EN                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN4_LP_EN
// Register Offset : 0x4010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN4_LP_EN                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN5_LP_EN
// Register Offset : 0x4014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN5_LP_EN                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN0_LP_IDLE_CNT
// Register Offset : 0x4018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN0_LP_IDLE_CNT(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN1_LP_IDLE_CNT
// Register Offset : 0x401C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN1_LP_IDLE_CNT(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN2_LP_IDLE_CNT
// Register Offset : 0x4020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN2_LP_IDLE_CNT(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN3_LP_IDLE_CNT
// Register Offset : 0x4024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN3_LP_IDLE_CNT(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN4_LP_IDLE_CNT
// Register Offset : 0x4028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN4_LP_IDLE_CNT(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_CHN5_LP_IDLE_CNT
// Register Offset : 0x402C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_CHN5_LP_IDLE_CNT(x)                                (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_CHN0_LP_CTRL
// Register Offset : 0x4030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_RF_PUB_CHN_EB_0                                        BIT(12)
#define BIT_PUB_APB_PUB0_RF_ACTIVE_HW_WAIT_CNT_0(x)                             (((x) & 0x3FF) << 2)
#define BIT_PUB_APB_PUB0_RF_CHN_SW_LP_EN_0                                      BIT(1)
#define BIT_PUB_APB_PUB0_RF_CHN_HW_LP_EN_0                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_CHN1_LP_CTRL
// Register Offset : 0x4034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_RF_PUB_CHN_EB_1                                        BIT(12)
#define BIT_PUB_APB_PUB0_RF_ACTIVE_HW_WAIT_CNT_1(x)                             (((x) & 0x3FF) << 2)
#define BIT_PUB_APB_PUB0_RF_CHN_SW_LP_EN_1                                      BIT(1)
#define BIT_PUB_APB_PUB0_RF_CHN_HW_LP_EN_1                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_CHN2_LP_CTRL
// Register Offset : 0x4038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_RF_PUB_CHN_EB_2                                        BIT(12)
#define BIT_PUB_APB_PUB0_RF_ACTIVE_HW_WAIT_CNT_2(x)                             (((x) & 0x3FF) << 2)
#define BIT_PUB_APB_PUB0_RF_CHN_SW_LP_EN_2                                      BIT(1)
#define BIT_PUB_APB_PUB0_RF_CHN_HW_LP_EN_2                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_CHN3_LP_CTRL
// Register Offset : 0x403C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_RF_PUB_CHN_EB_3                                        BIT(12)
#define BIT_PUB_APB_PUB0_RF_ACTIVE_HW_WAIT_CNT_3(x)                             (((x) & 0x3FF) << 2)
#define BIT_PUB_APB_PUB0_RF_CHN_SW_LP_EN_3                                      BIT(1)
#define BIT_PUB_APB_PUB0_RF_CHN_HW_LP_EN_3                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_CHN4_LP_CTRL
// Register Offset : 0x4040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_RF_PUB_CHN_EB_4                                        BIT(12)
#define BIT_PUB_APB_PUB0_RF_ACTIVE_HW_WAIT_CNT_4(x)                             (((x) & 0x3FF) << 2)
#define BIT_PUB_APB_PUB0_RF_CHN_SW_LP_EN_4                                      BIT(1)
#define BIT_PUB_APB_PUB0_RF_CHN_HW_LP_EN_4                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_CHN5_LP_CTRL
// Register Offset : 0x4044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_RF_PUB_CHN_EB_5                                        BIT(12)
#define BIT_PUB_APB_PUB0_RF_ACTIVE_HW_WAIT_CNT_5(x)                             (((x) & 0x3FF) << 2)
#define BIT_PUB_APB_PUB0_RF_CHN_SW_LP_EN_5                                      BIT(1)
#define BIT_PUB_APB_PUB0_RF_CHN_HW_LP_EN_5                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_AUTO_GATE_COUNTER
// Register Offset : 0x4048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB_AUTO_GATE_COUNTER(x)                               (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_MC_IDLE_WAIT_CTRL
// Register Offset : 0x404C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_MC_IDLE_WAIT_CTRL(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_CGM_DDR_MCTRL_DIV
// Register Offset : 0x4050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_CGM_DDR_MCTRL_400M_DIV                                 BIT(2)
#define BIT_PUB_APB_PUB0_CGM_DDR_MCTRL_200M_DIV(x)                              (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_CA_OE_CTRL
// Register Offset : 0x4054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_CA_OE_CTRL(x)                                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_SOFT_DFS_CTRL
// Register Offset : 0x8000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB_DFS_SW_SWITCH_PERIOD(x)                            (((x) & 0xFF) << 23)
#define BIT_PUB_APB_PUB0_EMC_CKG_SEL_DELAY(x)                                   (((x) & 0x7) << 20)
#define BIT_PUB_APB_PUB0_PUB_DFS_SW_RATIO_DEFAULT(x)                            (((x) & 0x7F) << 13)
#define BIT_PUB_APB_PUB0_PUB_DFS_SW_RATIO(x)                                    (((x) & 0x7F) << 6)
#define BIT_PUB_APB_PUB0_PUB_DFS_SW_FRQ_SEL(x)                                  (((x) & 0x3) << 4)
#define BIT_PUB_APB_PUB0_PUB_DFS_SW_RESP                                        BIT(3)
#define BIT_PUB_APB_PUB0_PUB_DFS_SW_ACK                                         BIT(2)
#define BIT_PUB_APB_PUB0_PUB_DFS_SW_REQ                                         BIT(1)
#define BIT_PUB_APB_PUB0_PUB_DFS_SW_ENABLE                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_HARD_DFS_CTRL_LO
// Register Offset : 0x8004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB_DFS_HW_SWITCH_PERIOD(x)                            (((x) & 0xFF) << 12)
#define BIT_PUB_APB_PUB0_PUB_DFS_HW_RATIO_DEFAULT(x)                            (((x) & 0x7F) << 5)
#define BIT_PUB_APB_PUB0_PUB_DFS_HW_INITIAL_FREQ(x)                             (((x) & 0x3) << 3)
#define BIT_PUB_APB_PUB0_PUB_DFS_HW_STOP                                        BIT(2)
#define BIT_PUB_APB_PUB0_PUB_DFS_HW_START                                       BIT(1)
#define BIT_PUB_APB_PUB0_PUB_DFS_HW_ENABLE                                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_HARD_DFS_CTRL_HI
// Register Offset : 0x8008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB_DFS_HW_F3_RATIO(x)                                 (((x) & 0x7F) << 21)
#define BIT_PUB_APB_PUB0_PUB_DFS_HW_F2_RATIO(x)                                 (((x) & 0x7F) << 14)
#define BIT_PUB_APB_PUB0_PUB_DFS_HW_F1_RATIO(x)                                 (((x) & 0x7F) << 7)
#define BIT_PUB_APB_PUB0_PUB_DFS_HW_F0_RATIO(x)                                 (((x) & 0x7F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_SOFT_PURE_DFS_CTRL
// Register Offset : 0x800C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_SOFT_CMD_RESP                                          BIT(7)
#define BIT_PUB_APB_PUB0_SOFT_CMD_DONE                                          BIT(6)
#define BIT_PUB_APB_PUB0_SOFT_CMD_FC_SEL(x)                                     (((x) & 0x3) << 4)
#define BIT_PUB_APB_PUB0_SOFT_CMD_NUM(x)                                        (((x) & 0x7) << 1)
#define BIT_PUB_APB_PUB0_SOFT_CMD_START                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_SOFT_PURE_DFS_CMD_STEP
// Register Offset : 0x8010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_SOFT_CMD_STEP(x)                                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_SOFT_PURE_DFS_CMD_SEQ_LO
// Register Offset : 0x8014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_SOFT_CMD_SEQ_LO(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_SOFT_PURE_DFS_CMD_SEQ_HI
// Register Offset : 0x8018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_SOFT_CMD_SEQ_HI(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_AW_COBUF_EN
// Register Offset : 0x801C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_AW_COBUF_EN(x)                                     (((x) & 0x7FF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_AWAPCMD_EN
// Register Offset : 0x8020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_AWAPCMD_EN(x)                                      (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_ARAPCMD_EN
// Register Offset : 0x8024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_ARAPCMD_EN(x)                                      (((x) & 0x3F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_BIST_TEST_CTRL
// Register Offset : 0x8028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB_CDNS_LA_SEL(x)                                     (((x) & 0xFF) << 7)
#define BIT_PUB_APB_PUB0_PUB_CDNS_LA_EN                                         BIT(6)
#define BIT_PUB_APB_PUB0_PUB_CPU_CHN_BIST_EN                                    BIT(5)
#define BIT_PUB_APB_PUB0_PUB_CPU_BIST_PATH_SEL                                  BIT(4)
#define BIT_PUB_APB_PUB0_PUB_GPU_CHN_BIST_EN                                    BIT(3)
#define BIT_PUB_APB_PUB0_PUB_GPU_BIST_PATH_SEL                                  BIT(2)
#define BIT_PUB_APB_PUB0_PUB_VSP_CHN_BIST_EN                                    BIT(1)
#define BIT_PUB_APB_PUB0_PUB_VSP_BIST_PATH_SEL                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_LP_GEN_CTRL
// Register Offset : 0x802C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DFS_SW_MODE                                            BIT(6)
#define BIT_PUB_APB_PUB0_HW_DFS_STOP_ENABLE                                     BIT(5)
#define BIT_PUB_APB_PUB0_HW_DFS_RESTART_ENABLE                                  BIT(4)
#define BIT_PUB_APB_PUB0_AUTO_STOP_NOC_ENABLE                                   BIT(3)
#define BIT_PUB_APB_PUB0_AUTO_STOP_DFS_ENABLE                                   BIT(2)
#define BIT_PUB_APB_PUB0_PUB_DFS_EN                                             BIT(1)
#define BIT_PUB_APB_PUB0_PUB_LP_EN                                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_PURE_SW_DFS_CTRL
// Register Offset : 0x8030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_EMC_CKG_SEL_PURE_SW(x)                                 (((x) & 0x7F) << 7)
#define BIT_PUB_APB_PUB0_PURE_SW_DFS_FRQ_SEL(x)                                 (((x) & 0x3) << 5)
#define BIT_PUB_APB_PUB0_PURE_SW_DFS_FC_ACK                                     BIT(4)
#define BIT_PUB_APB_PUB0_PURE_SW_DFS_FC_REQ                                     BIT(3)
#define BIT_PUB_APB_PUB0_PURE_SW_DFS_RESP                                       BIT(2)
#define BIT_PUB_APB_PUB0_PURE_SW_DFS_ACK                                        BIT(1)
#define BIT_PUB_APB_PUB0_PURE_SW_DFS_REQ                                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_DFS_STATUS
// Register Offset : 0x8034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB_LP_FSM_STATUS(x)                                   (((x) & 0xF) << 19)
#define BIT_PUB_APB_PUB0_HW_DFS_FSM_IDLE                                        BIT(18)
#define BIT_PUB_APB_PUB0_CURE_HW_DFS_FSM_STATE(x)                               (((x) & 0xF) << 14)
#define BIT_PUB_APB_PUB0_CUR_EMC_CKG_SEL(x)                                     (((x) & 0x7F) << 7)
#define BIT_PUB_APB_PUB0_CUR_DFS_FRQ_SEL(x)                                     (((x) & 0x3) << 5)
#define BIT_PUB_APB_PUB0_CUR_DFS_FC_ACK                                         BIT(4)
#define BIT_PUB_APB_PUB0_CUR_DFS_FC_REQ                                         BIT(3)
#define BIT_PUB_APB_PUB0_CUR_DFS_RESP                                           BIT(2)
#define BIT_PUB_APB_PUB0_CUR_DFS_ACK                                            BIT(1)
#define BIT_PUB_APB_PUB0_CUR_DFS_REQ                                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_PHY_BIST_CTRL_0
// Register Offset : 0x8038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_TOP_PLL_EN                                    BIT(30)
#define BIT_PUB_APB_PUB0_PHY_BIST_GO                                            BIT(29)
#define BIT_PUB_APB_PUB0_PHY_BIST_MODE(x)                                       (((x) & 0x3FFFF) << 11)
#define BIT_PUB_APB_PUB0_PHY_BIST_PLL_BYPASS                                    BIT(10)
#define BIT_PUB_APB_PUB0_PHY_BIST_PLL_EN                                        BIT(9)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_PHY_BIST_CTRL_1
// Register Offset : 0x803C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_EN(x)                                         (((x) & 0x1F) << 25)
#define BIT_PUB_APB_PUB0_PHY_BIST_EN_PAD                                        BIT(24)
#define BIT_PUB_APB_PUB0_PHY_BIST_EN_PAD_MODE(x)                                (((x) & 0x3F) << 18)
#define BIT_PUB_APB_PUB0_PHY_BIST_ADR_EN(x)                                     (((x) & 0xF) << 14)
#define BIT_PUB_APB_PUB0_PHY_BIST_ADR_MODE(x)                                   (((x) & 0x3FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_PHY_BIST_CTRL_2
// Register Offset : 0x8040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_DDL_EN(x)                                     (((x) & 0xF) << 27)
#define BIT_PUB_APB_PUB0_PHY_BIST_AC_DDL_EN(x)                                  (((x) & 0xF) << 21)
#define BIT_PUB_APB_PUB0_PHY_BIST_AC_EN(x)                                      (((x) & 0xFF) << 13)
#define BIT_PUB_APB_PUB0_PHY_BIST_AC_MODE(x)                                    (((x) & 0x1FF) << 4)
#define BIT_PUB_APB_PUB0_PHY_BIST_ADR_DDL_EN(x)                                 (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB_PHY_VERF_CTRL
// Register Offset : 0x8044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PARAM_VREF_CTRL(x)                                     (((x) & 0x1FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_AC_GRP0
// Register Offset : 0x8048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_AC_GRP0(x)                                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_AC_GRP1
// Register Offset : 0x804C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_AC_GRP1(x)                                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_AC_GRP2
// Register Offset : 0x8050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_AC_GRP2(x)                                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_ADR_GRP0
// Register Offset : 0x8054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_ADR_GRP0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_ADR_GRP1
// Register Offset : 0x8058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_ADR_GRP1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_DONE_GRP
// Register Offset : 0x805C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_DONE_GRP(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_ERR_GRP0
// Register Offset : 0x8060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_ERR_GRP0(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_ERR_GRP1
// Register Offset : 0x8064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_ERR_GRP1(x)                                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_DFI_WDQLVL_GRP0
// Register Offset : 0x8068
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_DFI_WDQLVL_GRP0(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_CTRL_DP_IDLE
// Register Offset : 0x806C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_CTRL_DP_IDLE                                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_OPCG_CTRL
// Register Offset : 0x8070
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_OPCG_MODE                                              BIT(3)
#define BIT_PUB_APB_PUB0_OPCG_PGMSI                                             BIT(2)
#define BIT_PUB_APB_PUB0_OPCG_TRIG                                              BIT(1)
#define BIT_PUB_APB_PUB0_OPCG_PGMSO                                             BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ZQ_CTRL
// Register Offset : 0x8074
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_ZQ_STATUS_IN(x)                                        (((x) & 0x3) << 2)
#define BIT_PUB_APB_PUB0_ZQ_STATUS_OUT(x)                                       (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_PLL_MODE0
// Register Offset : 0x8078
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_PLL_MODE0(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_PLL_MODE1
// Register Offset : 0x807C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_PLL_MODE1(x)                                  (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_PLL_MODE2
// Register Offset : 0x8080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_PLL_MODE2(x)                                  (((x) & 0x1FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_TOP_PLL_MODE0
// Register Offset : 0x8084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_TOP_PLL_MODE0(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_TOP_PLL_MODE1
// Register Offset : 0x8088
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_TOP_PLL_MODE1(x)                              (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PHY_BIST_TOP_PLL_MODE2
// Register Offset : 0x808C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_BIST_TOP_PLL_MODE2(x)                              (((x) & 0x1FFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_PUBCP0
// Register Offset : 0x8090
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_AW_CH_PUBCP(x)                             (((x) & 0xF) << 24)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_AW_CH_PUBCP(x)                             (((x) & 0xF) << 20)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_W_CH_PUBCP(x)                              (((x) & 0x1F) << 15)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_W_CH_PUBCP(x)                              (((x) & 0x1F) << 10)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_B_CH_PUBCP(x)                              (((x) & 0x1F) << 5)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_B_CH_PUBCP(x)                              (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_PUBCP1
// Register Offset : 0x8094
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_AR_CH_PUBCP(x)                             (((x) & 0xF) << 14)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_AR_CH_PUBCP(x)                             (((x) & 0xF) << 10)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_R_CH_PUBCP(x)                              (((x) & 0x1F) << 5)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_R_CH_PUBCP(x)                              (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_WTL0_0
// Register Offset : 0x8098
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_AW_CH_WTL0(x)                              (((x) & 0xF) << 22)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_AW_CH_WTL0(x)                              (((x) & 0xF) << 18)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_W_CH_WTL0(x)                               (((x) & 0x1F) << 13)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_W_CH_WTL0(x)                               (((x) & 0x1F) << 8)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_B_CH_WTL0(x)                               (((x) & 0xF) << 4)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_B_CH_WTL0(x)                               (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_WTL0_1
// Register Offset : 0x809C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_AR_CH_WTL0(x)                              (((x) & 0xF) << 14)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_AR_CH_WTL0(x)                              (((x) & 0xF) << 10)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_R_CH_WTL0(x)                               (((x) & 0x1F) << 5)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_R_CH_WTL0(x)                               (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_WTL1_0
// Register Offset : 0x80A0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_AW_CH_WTL1(x)                              (((x) & 0xF) << 22)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_AW_CH_WTL1(x)                              (((x) & 0xF) << 18)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_W_CH_WTL1(x)                               (((x) & 0x1F) << 13)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_W_CH_WTL1(x)                               (((x) & 0x1F) << 8)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_B_CH_WTL1(x)                               (((x) & 0xF) << 4)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_B_CH_WTL1(x)                               (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_WTL1_1
// Register Offset : 0x80A4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_AR_CH_WTL1(x)                              (((x) & 0xF) << 14)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_AR_CH_WTL1(x)                              (((x) & 0xF) << 10)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_R_CH_WTL1(x)                               (((x) & 0x1F) << 5)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_R_CH_WTL1(x)                               (((x) & 0x1F))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ASYNC_FIFO_LEVEL_AG
// Register Offset : 0x80A8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_AW_CH_AG(x)                                (((x) & 0x7) << 27)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_AW_CH_AG(x)                                (((x) & 0x7) << 24)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_W_CH_AG(x)                                 (((x) & 0x7) << 21)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_W_CH_AG(x)                                 (((x) & 0x7) << 18)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_B_CH_AG(x)                                 (((x) & 0x7) << 15)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_B_CH_AG(x)                                 (((x) & 0x7) << 12)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_AR_CH_AG(x)                                (((x) & 0x7) << 9)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_AR_CH_AG(x)                                (((x) & 0x7) << 6)
#define BIT_PUB_APB_PUB0_FIFO_AF_LVL_R_CH_AG(x)                                 (((x) & 0x7) << 3)
#define BIT_PUB_APB_PUB0_FIFO_AE_LVL_R_CH_AG(x)                                 (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AWCACHE_SW
// Register Offset : 0x80AC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AWCACHE_SW5(x)                                         (((x) & 0xF) << 20)
#define BIT_PUB_APB_PUB0_AWCACHE_SW4(x)                                         (((x) & 0xF) << 16)
#define BIT_PUB_APB_PUB0_AWCACHE_SW3(x)                                         (((x) & 0xF) << 12)
#define BIT_PUB_APB_PUB0_AWCACHE_SW2(x)                                         (((x) & 0xF) << 8)
#define BIT_PUB_APB_PUB0_AWCACHE_SW1(x)                                         (((x) & 0xF) << 4)
#define BIT_PUB_APB_PUB0_AWCACHE_SW0(x)                                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ARCACHE_SW
// Register Offset : 0x80B0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_ARCACHE_SW5(x)                                         (((x) & 0xF) << 20)
#define BIT_PUB_APB_PUB0_ARCACHE_SW4(x)                                         (((x) & 0xF) << 16)
#define BIT_PUB_APB_PUB0_ARCACHE_SW3(x)                                         (((x) & 0xF) << 12)
#define BIT_PUB_APB_PUB0_ARCACHE_SW2(x)                                         (((x) & 0xF) << 8)
#define BIT_PUB_APB_PUB0_ARCACHE_SW1(x)                                         (((x) & 0xF) << 4)
#define BIT_PUB_APB_PUB0_ARCACHE_SW0(x)                                         (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AWCACHE_SW_EN
// Register Offset : 0x80B4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AWCACHE_SW_EN5                                         BIT(5)
#define BIT_PUB_APB_PUB0_AWCACHE_SW_EN4                                         BIT(4)
#define BIT_PUB_APB_PUB0_AWCACHE_SW_EN3                                         BIT(3)
#define BIT_PUB_APB_PUB0_AWCACHE_SW_EN2                                         BIT(2)
#define BIT_PUB_APB_PUB0_AWCACHE_SW_EN1                                         BIT(1)
#define BIT_PUB_APB_PUB0_AWCACHE_SW_EN0                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_ARCACHE_SW_EN
// Register Offset : 0x80B8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_ARCACHE_SW_EN5                                         BIT(5)
#define BIT_PUB_APB_PUB0_ARCACHE_SW_EN4                                         BIT(4)
#define BIT_PUB_APB_PUB0_ARCACHE_SW_EN3                                         BIT(3)
#define BIT_PUB_APB_PUB0_ARCACHE_SW_EN2                                         BIT(2)
#define BIT_PUB_APB_PUB0_ARCACHE_SW_EN1                                         BIT(1)
#define BIT_PUB_APB_PUB0_ARCACHE_SW_EN0                                         BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB0_DUMMY_REG0
// Register Offset : 0x80BC
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB0_DUMMY_REG0(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB0_DUMMY_REG1
// Register Offset : 0x80C0
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PUB0_DUMMY_REG1(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_PUB0_PHY_BIST
// Register Offset : 0x80C4
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_PHY_FREQ_CHANGE_REQ                                    BIT(13)
#define BIT_PUB_APB_PUB0_PHY_FREQ_CHANGE_REQ_TYPE(x)                            (((x) & 0x1F) << 8)
#define BIT_PUB_APB_PUB0_PHY_BIST_PLL_LOCK(x)                                   (((x) & 0xFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_APB_PUB0_AXI_DEBUG_STATUS
// Register Offset : 0x80C8
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_APB_PUB0_AXI_AXLEN_GT16(x)                                      (((x) & 0xFFF))


#endif // _PUB_APB_PUB0_REG_H

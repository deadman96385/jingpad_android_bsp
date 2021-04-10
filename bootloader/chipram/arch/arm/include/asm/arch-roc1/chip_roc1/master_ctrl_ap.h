/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:55:38
 *
 */


#ifndef MASTER_CTRL_AP_H
#define MASTER_CTRL_AP_H

#define CTL_BASE_MASTER_CTRL_AP 0x32808000


#define REG_MASTER_CTRL_AP_RD_SEC_0  ( CTL_BASE_MASTER_CTRL_AP + 0x0000 )
#define REG_MASTER_CTRL_AP_WR_SEC_0  ( CTL_BASE_MASTER_CTRL_AP + 0x0004 )

/* REG_MASTER_CTRL_AP_RD_SEC_0 */

#define BIT_MASTER_CTRL_AP_RD_SEC_0_SDIO0_RD_SEC(x)     (((x) & 0x3) << 20)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_SDIO1_RD_SEC(x)     (((x) & 0x3) << 18)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_SDIO2_RD_SEC(x)     (((x) & 0x3) << 16)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_EMMC_RD_SEC(x)      (((x) & 0x3) << 14)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_DPU_RD_SEC(x)       (((x) & 0x3) << 12)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_VDSP_EPP_RD_SEC(x)  (((x) & 0x3) << 10)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_VDSP_EDP_RD_SEC(x)  (((x) & 0x3) << 8)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_VDSP_M0_RD_SEC(x)   (((x) & 0x3) << 6)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_VDMA_RD_SEC(x)      (((x) & 0x3) << 4)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_VSP_RD_SEC(x)       (((x) & 0x3) << 2)
#define BIT_MASTER_CTRL_AP_RD_SEC_0_UFS_RD_SEC(x)       (((x) & 0x3))

/* REG_MASTER_CTRL_AP_WR_SEC_0 */

#define BIT_MASTER_CTRL_AP_WR_SEC_0_SDIO0_WR_SEC(x)     (((x) & 0x3) << 20)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_SDIO1_WR_SEC(x)     (((x) & 0x3) << 18)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_SDIO2_WR_SEC(x)     (((x) & 0x3) << 16)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_EMMC_WR_SEC(x)      (((x) & 0x3) << 14)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_DPU_WR_SEC(x)       (((x) & 0x3) << 12)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_VDSP_EPP_WR_SEC(x)  (((x) & 0x3) << 10)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_VDSP_EDP_WR_SEC(x)  (((x) & 0x3) << 8)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_VDSP_M0_WR_SEC(x)   (((x) & 0x3) << 6)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_VDMA_WR_SEC(x)      (((x) & 0x3) << 4)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_VSP_WR_SEC(x)       (((x) & 0x3) << 2)
#define BIT_MASTER_CTRL_AP_WR_SEC_0_UFS_WR_SEC(x)       (((x) & 0x3))


#endif /* MASTER_CTRL_AP_H */



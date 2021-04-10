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


#ifndef MASTER_CTRL_IPA_H
#define MASTER_CTRL_IPA_H

#define CTL_BASE_MASTER_CTRL_IPA 0x32830000


#define REG_MASTER_CTRL_IPA_RD_SEC_0  ( CTL_BASE_MASTER_CTRL_IPA + 0x0000 )
#define REG_MASTER_CTRL_IPA_WR_SEC_0  ( CTL_BASE_MASTER_CTRL_IPA + 0x0004 )

/* REG_MASTER_CTRL_IPA_RD_SEC_0 */

#define BIT_MASTER_CTRL_IPA_RD_SEC_0_PCIE2_RD_SEC(x)     (((x) & 0x3) << 18)
#define BIT_MASTER_CTRL_IPA_RD_SEC_0_PCIE3_RD_SEC(x)     (((x) & 0x3) << 16)
#define BIT_MASTER_CTRL_IPA_RD_SEC_0_PAM_U3_RD_SEC(x)    (((x) & 0x3) << 14)
#define BIT_MASTER_CTRL_IPA_RD_SEC_0_PAM_IPA_RD_SEC(x)   (((x) & 0x3) << 12)
#define BIT_MASTER_CTRL_IPA_RD_SEC_0_PAM0_RD_SEC(x)      (((x) & 0x3) << 10)
#define BIT_MASTER_CTRL_IPA_RD_SEC_0_PAM_WIFI_RD_SEC(x)  (((x) & 0x3) << 8)
#define BIT_MASTER_CTRL_IPA_RD_SEC_0_USB3_RD_SEC(x)      (((x) & 0x3) << 6)
#define BIT_MASTER_CTRL_IPA_RD_SEC_0_CM4I_RD_SEC(x)      (((x) & 0x3) << 4)
#define BIT_MASTER_CTRL_IPA_RD_SEC_0_CM4D_RD_SEC(x)      (((x) & 0x3) << 2)
#define BIT_MASTER_CTRL_IPA_RD_SEC_0_CM4S_RD_SEC(x)      (((x) & 0x3))

/* REG_MASTER_CTRL_IPA_WR_SEC_0 */

#define BIT_MASTER_CTRL_IPA_WR_SEC_0_PCIE2_WR_SEC(x)     (((x) & 0x3) << 18)
#define BIT_MASTER_CTRL_IPA_WR_SEC_0_PCIE3_WR_SEC(x)     (((x) & 0x3) << 16)
#define BIT_MASTER_CTRL_IPA_WR_SEC_0_PAM_U3_WR_SEC(x)    (((x) & 0x3) << 14)
#define BIT_MASTER_CTRL_IPA_WR_SEC_0_PAM_IPA_WR_SEC(x)   (((x) & 0x3) << 12)
#define BIT_MASTER_CTRL_IPA_WR_SEC_0_PAM0_WR_SEC(x)      (((x) & 0x3) << 10)
#define BIT_MASTER_CTRL_IPA_WR_SEC_0_PAM_WIFI_WR_SEC(x)  (((x) & 0x3) << 8)
#define BIT_MASTER_CTRL_IPA_WR_SEC_0_USB3_WR_SEC(x)      (((x) & 0x3) << 6)
#define BIT_MASTER_CTRL_IPA_WR_SEC_0_CM4I_WR_SEC(x)      (((x) & 0x3) << 4)
#define BIT_MASTER_CTRL_IPA_WR_SEC_0_CM4D_WR_SEC(x)      (((x) & 0x3) << 2)
#define BIT_MASTER_CTRL_IPA_WR_SEC_0_CM4S_WR_SEC(x)      (((x) & 0x3))


#endif /* MASTER_CTRL_IPA_H */



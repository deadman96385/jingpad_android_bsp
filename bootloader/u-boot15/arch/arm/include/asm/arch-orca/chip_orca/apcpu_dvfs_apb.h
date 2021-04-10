/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:54:34
 *
 */


#ifndef APCPU_DVFS_APB_H
#define APCPU_DVFS_APB_H

#define CTL_BASE_APCPU_DVFS_APB 0x63988000

#define REG_APCPU_DVFS_APB_APCPU_FREQ_UPD_TYPE_CFG               ( CTL_BASE_APCPU_DVFS_APB + 0x02CC )

/* REG_APCPU_DVFS_APB_APCPU_FREQ_UPD_TYPE_CFG */
#define BIT_APCPU_DVFS_APB_APCPU_GIC_FREQ_UPD_DELAY_EN            BIT(23)
#define BIT_APCPU_DVFS_APB_APCPU_GIC_FREQ_UPD_HDSK_EN             BIT(22)
#define BIT_APCPU_DVFS_APB_APCPU_PERIPH_FREQ_UPD_DELAY_EN         BIT(21)
#define BIT_APCPU_DVFS_APB_APCPU_PERIPH_FREQ_UPD_HDSK_EN          BIT(20)
#define BIT_APCPU_DVFS_APB_APCPU_ATB_FREQ_UPD_DELAY_EN            BIT(19)
#define BIT_APCPU_DVFS_APB_APCPU_ATB_FREQ_UPD_HDSK_EN             BIT(18)
#define BIT_APCPU_DVFS_APB_APCPU_SCU_FREQ_UPD_DELAY_EN            BIT(17)
#define BIT_APCPU_DVFS_APB_APCPU_SCU_FREQ_UPD_HDSK_EN             BIT(16)
#define BIT_APCPU_DVFS_APB_APCPU_CORE1_FREQ_UPD_DELAY_EN          BIT(3)
#define BIT_APCPU_DVFS_APB_APCPU_CORE1_FREQ_UPD_HDSK_EN           BIT(2)
#define BIT_APCPU_DVFS_APB_APCPU_CORE0_FREQ_UPD_DELAY_EN          BIT(1)
#define BIT_APCPU_DVFS_APB_APCPU_CORE0_FREQ_UPD_HDSK_EN           BIT(0)

#endif /* APCPU_DVFS_APB_H */



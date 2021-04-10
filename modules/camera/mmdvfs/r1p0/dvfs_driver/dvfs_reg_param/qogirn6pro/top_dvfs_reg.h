/*
 * Copyright (C) 2019 Unisoc Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 ********************************************************************
 * Auto generated c code from ASIC Documentation, PLEASE DONOT EDIT *
 ********************************************************************
 */

#ifndef __SHARKL5PRO_TOP_DVFS_REG_H____
#define __SHARKL5PRO_TOP_DVFS_REG_H____


/* Some defs, in case these are not defined elsewhere */
#ifndef SCI_IOMAP
#define SCI_IOMAP(_b_) ((unsigned long)(_b_))
#endif

#ifndef SCI_ADDR
#define SCI_ADDR(_b_, _o_) ((unsigned long)((_b_) + (_o_)))
#endif

#define REGS_MM_DVFS_AHB_START         SCI_IOMAP(0x62600000)
#define REGS_MM_DVFS_AHB_END           SCI_IOMAP(0x6260023c)

#define REGS_MM_TOP_DVFS_START         SCI_IOMAP(0x322A0000)
#define REGS_MM_TOP_DVFS_END           SCI_IOMAP(0x322A0150)

#define REGS_MM_AHB_REG_START          SCI_IOMAP(0x62200000)
#define REGS_MM_AHB_REG_END            SCI_IOMAP(0x62200150)

#define REGS_MM_POWER_REG_START        SCI_IOMAP(0x327e0024)
#define REGS_MM_POWER_REG_END          SCI_IOMAP(0x327e0028)

#define REGS_MM_POWER_ON_REG_START     SCI_IOMAP(0x327d0000)
#define REGS_MM_POWER_ON_REG_END       SCI_IOMAP(0x327d0004)

#ifndef REGS_MM_DVFS_AHB_BASE
#define REGS_MM_DVFS_AHB_BASE     g_mmreg_map.mmdvfs_ahb_regbase
#endif

#ifndef REGS_MM_TOP_DVFS_BASE
#define REGS_MM_TOP_DVFS_BASE     g_mmreg_map.mmdvfs_top_regbase
#endif

#ifndef REGS_MM_AHB_BASE
#define REGS_MM_AHB_BASE          g_mmreg_map.mm_ahb_regbase
#endif

#ifndef REGS_MM_POWER_BASE
#define REGS_MM_POWER_BASE        g_mmreg_map.mm_power_regbase
#endif

#ifndef REGS_MM_POWER_ON_BASE
#define REGS_MM_POWER_ON_BASE     g_mmreg_map.mm_power_on_regbase
#endif

/* power*/
/*#define REG_TOP_PMU_AUTO_SHUTDOWN_EN  SCI_ADDR(0X327e0024, 0x0000UL)*/

/* registers definitions for controller REGS_MM_AHB, 0x62200000 */
#define REG_MM_AHB_AHB_EB             0x0000UL

#define BIT_MM_CKG_EB                 (BIT(7))
#define BIT_MM_FD_EB                  (BIT(10))
#define BIT_MM_ISP_EB                 (BIT(3))
#define BIT_MM_DCAM_EB                (BIT(2))
#define BIT_MM_JPG_EB                 (BIT(1))
#define BIT_MM_CPP_EB                 (BIT(0))

#define SHIFT_BIT_MM_FD_EB   (10)
#define SHIFT_BIT_MM_ISP_EB  (3)
#define SHIFT_BIT_MM_DCAM_EB (2)
#define SHIFT_BIT_MM_JPG_EB  (1)
#define SHIFT_BIT_MM_CPP_EB  (0)

#define REG_MM_IP_BUSY                0x0038UL

#define BIT_MM_FD_BUSY    (BIT(4))
#define BIT_MM_DCAM_BUSY  (BIT(3))
#define BIT_MM_ISP_BUSY   (BIT(2))
#define BIT_MM_JPG_BUSY   (BIT(1))
#define BIT_MM_CPP_BUSY   (BIT(0))

#define SHIFT_BIT_MM_FD_BUSY    (4)
#define SHIFT_BIT_MM_DCAM_BUSY  (3)
#define SHIFT_BIT_MM_ISP_BUSY   (2)
#define SHIFT_BIT_MM_JPG_BUSY   (1)
#define SHIFT_BIT_MM_CPP_BUSY   (0)



/*REG_TOP_DVFS_APB_SUBSYS_SW_DVFS_EN_CFG, 0x322A0000 */
#define REG_TOP_DVFS_APB_DCDC_MM_FIX_VOLTAGE_CTRL   0x0000UL
#define REG_TOP_DVFS_APB_SUBSYS_SW_DVFS_EN_CFG      0x0150UL
#define REG_TOP_DVFS_APB_DCDC_MM_SW_DVFS_CTRL       0x0018UL

/* debug */
#define REG_TOP_DVFS_APB_DCDC_MM_DVFS_STATE_DBG         0x0020UL

#define BIT_DCDC_MM_SW_TUNE_EN                          (BIT(20))
#define BIT_MM_SYS_SW_DVFS_EN                           (BIT(2))
#define BIT_DCDC_MM_FIX_VOLTAGE_EN                      (BIT(0))


#endif /* __SHARKL5PRO_TOP_DVFS_REG_H____ */

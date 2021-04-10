/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <asm/io.h>
#include <common.h>
#include <sprd_glb.h>
#include <asm/arch/sprd_reg.h>
#include <linux/types.h>
#include <linux/err.h>
#include <errno.h>

#ifndef SCI_ADDR
#define SCI_ADDR(_b_, _o_)		((unsigned int)(_b_) + (_o_))
#endif

#ifndef bool
typedef int bool;
#endif
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif

typedef unsigned int  u32;

#define EFUSE_ALL0_INDEX		SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x0008)
#define EFUSE_MODE_CTRL			SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x000c)
#define EFUSE_IP_VER			SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x0014)
#define EFUSE_CFG0			SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x0018)
#define EFUSE_NS_EN			SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x0020)
#define EFUSE_NS_ERR_FLAG		SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x0024)
#define EFUSE_NS_FLAG_CLR		SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x0028)
#define EFUSE_NS_MAGIC_NUM		SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x002c)
#define EFUSE_FW_CFG			SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x0050)
#define EFUSE_PW_SWT			SCI_ADDR(SPRD_UIDEFUSE_PHYS, 0x0054)
#define EFUSE_MEM(val)			SCI_ADDR(SPRD_UIDEFUSE_PHYS,(0x1000 + (val << 2)))


/* bits definitions for register EFUSE_MODE_CTRL */

#define BIT_EFUSE_ALL0_CHECK_START       (BIT(0))

/* bits definitions for register EFUSE_NS_EN */

#define BIT_NS_VDD_EN			(BIT(0))
#define BIT_NS_AUTO_CHECK_ENABLE	(BIT(1))
#define BIT_DOUBLE_BIT_EN_NS            (BIT(2))
#define BIT_NS_MARGIN_RD_ENABLE         (BIT(3))
#define BIT_NS_LOCK_BIT_WR_EN           (BIT(4))

/* bits definitions for register EFUSE_NS_ERR_FLAG */
#define BIT_NS_WORD0_ERR_FLAG		(BIT(0))
#define BIT_NS_WORD1_ERR_FLAG		(BIT(1))
#define BIT_NS_WORD0_PROT_FLAG		(BIT(4))
#define BIT_NS_WORD1_PROT_FLAG		(BIT(5))
#define BIT_NS_PG_EN_WR_FLAG		(BIT(8))
#define BIT_NS_VDD_ON_RD_FLAG		(BIT(9))
#define BIT_NS_BLOCK0_RD_FLAG		(BIT(10))
#define BIT_NS_MAGNUM_WR_FLAG		(BIT(11))
#define BIT_NS_ENK_ERR_FLAG		(BIT(12))
#define BIT_NS_ALL0_CHECK_FLAG		(BIT(13))

/* bits definitions for register EFUSE_NS_FLAG_CLR */
#define BIT_NS_WORD0_ERR_CLR		(BIT(0))
#define BIT_NS_WORD1_ERR_CLR		(BIT(1))
#define BIT_NS_WORD0_PROT_CLR		(BIT(4))
#define BIT_NS_WORD1_PROT_CLR		(BIT(5))
#define BIT_NS_PG_EN_WR_CLR		(BIT(8))
#define BIT_NS_VDD_ON_RD_CLR		(BIT(9))
#define BIT_NS_BLOCK0_RD_CLR		(BIT(10))
#define BIT_NS_MAGNUM_WR_CLR		(BIT(11))
#define BIT_NS_ENK_ERR_CLR		(BIT(12))
#define BIT_NS_ALL0_CHECK_CLR		(BIT(13))

/* bits definitions for register EFUSE_PW_SWT */

#define BIT_EFS_ENK1_ON      		(BIT(0))
#define BIT_EFS_ENK2_ON      		(BIT(1))
#define BIT_NS_S_PG_EN      		(BIT(2))

/* Magic number, only when this field is 0x8810, the efuse programming
 * command can be handle. So, if SW want to program efuse memory,
 * except open clocks and power, the follow conditions must be met:
 * 1. PGM_EN = 1;
 * 2. EFUSE_MAGIC_NUMBER = 0x8810
 */
#define BITS_NS_EFUSE_MAGIC_NUMBER(_x_)          ((_x_) << 0 & (BIT(0)|BIT(1)\
	|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10)\
	|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15)))


#define EFUSE_MAGIC_NUMBER              ( 0x8810 )
#define ERR_CLR_MASK		0x3fff
extern void tmr_udelay (unsigned long usec);

#define udelay(x)	\
	do { \
		volatile int i; \
		int cnt = 1000 * x; \
		for (i=0; i<cnt; i++);\
	} while(0);

static void ap_efuse_lock(void)
{

}

static void ap_efuse_unlock(void)
{

}

static inline u32 ap_efuse_reg_read(unsigned long reg)
{
	return __raw_readl(reg);
}

static inline void ap_efuse_reg_write(u32 val, unsigned long reg)
{
	__raw_writel(val, reg);
}

static void ap_efuse_prog_power_on(void)
{
	u32 cfg0;

	cfg0 = ap_efuse_reg_read(EFUSE_PW_SWT);
	cfg0 &= ~BIT_EFS_ENK2_ON;
	ap_efuse_reg_write(cfg0, EFUSE_PW_SWT);
	tmr_udelay(1000);
	cfg0 |= BIT_EFS_ENK1_ON;
	ap_efuse_reg_write(cfg0, EFUSE_PW_SWT);
	tmr_udelay(1000);
}

static void ap_efuse_prog_power_off(void)
{
	u32 cfg0;

	cfg0 = ap_efuse_reg_read(EFUSE_PW_SWT);
	cfg0 &= ~BIT_EFS_ENK1_ON;
	ap_efuse_reg_write(cfg0, EFUSE_PW_SWT);
	tmr_udelay(1000);
	cfg0 |= BIT_EFS_ENK2_ON;
	ap_efuse_reg_write(cfg0, EFUSE_PW_SWT);
	tmr_udelay(1000);
}

static void ap_efuse_read_power_on(void)
{
	u32 cfg0;

	cfg0 = ap_efuse_reg_read(EFUSE_NS_EN);
	cfg0 |= BIT_NS_VDD_EN;
	ap_efuse_reg_write(cfg0,  EFUSE_NS_EN);
	tmr_udelay(1000);
}

static void ap_efuse_read_power_off(void)
{
	u32 cfg0;

	cfg0 = ap_efuse_reg_read(EFUSE_NS_EN);
	cfg0 &= ~BIT_NS_VDD_EN;
	ap_efuse_reg_write(cfg0, EFUSE_NS_EN);
	tmr_udelay(1000);
}

static void efuse_clk_enable(void)
{
#if defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_SHARKL5PRO) || \
	defined(CONFIG_SOC_ROC1) || defined(CONFIG_SOC_ORCA)
	sci_glb_set(REG_AON_APB_APB_EB1, BIT_EFUSE_EB);
#else
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
#endif
}

static void ap_efuse_prog_lock(bool en_lock)
{
	u32 cfg0;

	cfg0 = ap_efuse_reg_read(EFUSE_NS_EN);
	if(en_lock)
		cfg0 |= BIT_NS_LOCK_BIT_WR_EN;
	else
		cfg0 &= ~BIT_NS_LOCK_BIT_WR_EN;

	ap_efuse_reg_write(cfg0,  EFUSE_NS_EN);
}

static void ap_efuse_double(bool backup)
{
	u32 cfg0;

	cfg0 = ap_efuse_reg_read(EFUSE_NS_EN);
	if(backup)
		cfg0 |= BIT_DOUBLE_BIT_EN_NS;
	else
		cfg0 &= ~BIT_DOUBLE_BIT_EN_NS;

	ap_efuse_reg_write(cfg0,  EFUSE_NS_EN);
}

static void ap_efuse_auto_check(bool en_lock)
{
	u32 cfg0;

	cfg0 = ap_efuse_reg_read(EFUSE_NS_EN);
	if (en_lock)
		cfg0 |= BIT_NS_AUTO_CHECK_ENABLE;
	else
		cfg0 &= ~BIT_NS_AUTO_CHECK_ENABLE;

	ap_efuse_reg_write(cfg0, EFUSE_NS_EN);
}

static u32 ap_efuse_read(int blk, bool backup)
{
	u32 val = 0;

	ap_efuse_double(backup);
	val = ap_efuse_reg_read(EFUSE_MEM(blk));
	ap_efuse_double(false);
	return val;
}

static int ap_efuse_prog(u32 blk, bool backup, bool lock, u32 val)
{
	u32 cfg0;
	int ret;

	ap_efuse_reg_write(BITS_NS_EFUSE_MAGIC_NUMBER(EFUSE_MAGIC_NUMBER),
			   EFUSE_NS_MAGIC_NUM);
	ap_efuse_prog_power_on();
	ap_efuse_reg_write(ERR_CLR_MASK, EFUSE_NS_FLAG_CLR);
	cfg0 = ap_efuse_reg_read(EFUSE_PW_SWT);
	cfg0 |= BIT_NS_S_PG_EN;
	ap_efuse_reg_write(cfg0, EFUSE_PW_SWT);

	ap_efuse_double(backup);
	ap_efuse_auto_check(true);
	ap_efuse_reg_write(val, EFUSE_MEM(blk));
	ap_efuse_auto_check(false);
	ap_efuse_double(false);
	ret = ap_efuse_reg_read(EFUSE_NS_ERR_FLAG);
	if (!ret) {
		ap_efuse_prog_lock(lock);
		ap_efuse_reg_write(0x0, EFUSE_MEM(blk));
		ap_efuse_prog_lock(false);
	}
	ap_efuse_reg_write(ERR_CLR_MASK, EFUSE_NS_FLAG_CLR);

	cfg0 = ap_efuse_reg_read(EFUSE_PW_SWT);
	cfg0 &= ~BIT_NS_S_PG_EN;
	ap_efuse_reg_write(cfg0, EFUSE_PW_SWT);
	ap_efuse_prog_power_off();
	ap_efuse_reg_write(0, EFUSE_NS_MAGIC_NUM);

	return ret;
}

u32 sprd_efuse_double_read(int blk, bool backup)
{
	u32 val = 0;
	int ret;

	ap_efuse_lock();
	efuse_clk_enable();
	ap_efuse_reg_write(ERR_CLR_MASK, EFUSE_NS_FLAG_CLR);
	ap_efuse_read_power_on();
	val = ap_efuse_read(blk, backup);
	ap_efuse_read_power_off();
	ret = ap_efuse_reg_read(EFUSE_NS_ERR_FLAG);
	if (ret) {
		ap_efuse_reg_write(ERR_CLR_MASK, EFUSE_NS_FLAG_CLR);
		val = 0;
	}
	ap_efuse_unlock();
	debugf("efuse read blk %d, ret 0x%x, val 0x%08x\n", blk, ret, val);

	return val;
}

u32 sprd_ap_efuse_read(int blk)
{
	return sprd_efuse_double_read(blk, 1);
}

int sprd_efuse_double_prog(u32 blk, bool backup, bool lock, u32 val)
{
	int ret;

	ap_efuse_lock();
	efuse_clk_enable();
	ret = ap_efuse_prog(blk,backup,lock,val);
	if (ret)
		ret = -EIO;
	ap_efuse_unlock();
	debugf("efuse prog blk %d, ret 0x%x, val 0x%08x\n", blk, ret, val);
	return ret;
}

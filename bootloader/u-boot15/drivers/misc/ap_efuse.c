/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
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

/* IMPORTANT:
 * The electrical fuse is a type of non-volatile memory fabricated
 * in standard CMOS logic process. This electrical fuse macro is widely
 * used in chip ID, memory redundancy, security code, configuration setting,
 * and feature selection, etc.
 *
 * This efuse controller is designed for 32*32 bits electrical fuses,
 * support TSMC HPM 28nm product of "TEF28HPM32X32HD18_PHRM".
 *
 * and we default use double-bit, 512bits efuse are visiable for software.
 *
 * efuse driver ONLY support module ip version since from r3p0
 * which had integrated into scx30g and scx35l etc.
 *
 * TODO:
 * 1. do something when block had been locked with bit31 if need
 * 1. check and clear blk prog/err flag if need
 * 1. wait *300ms* for read/prog ready time-out
 * 1. only mutexlock and hwspinlock for efuse access sync with cp
 * 1. be care not do use efuse API in interrupt function
 * 1. no need soft reset after efuse read/prog and power on/off
 * 1. efuse block width should less than 8bits
 * 1. efuse block count should not bigger than 32! or not should expland the cached otp arrary
 * 1. support efuse DT info (version, blocks, ...) later
 * 1. there is no handle for efuse module removed
 */

#include <asm/io.h>
#include <sprd_glb.h>
#include <asm/arch/sprd_reg.h>
#include <common.h>
#include <linux/types.h>
#include <linux/err.h>

typedef unsigned int u32;

/* registers definitions for controller REGS_EFUSE */
#define REG_EFUSE_DATA_RD               SCI_ADDR(REGS_EFUSE_BASE, 0x0000)
#define REG_EFUSE_DATA_WR               SCI_ADDR(REGS_EFUSE_BASE, 0x0004)
#define REG_EFUSE_READ_WRITE_INDEX      SCI_ADDR(REGS_EFUSE_BASE, 0x0008)
#define REG_EFUSE_MODE_CTRL             SCI_ADDR(REGS_EFUSE_BASE, 0x000c)
#define REG_EFUSE_CFG0                  SCI_ADDR(REGS_EFUSE_BASE, 0x0010)
#define REG_EFUSE_CFG1                  SCI_ADDR(REGS_EFUSE_BASE, 0x0014)
#define REG_EFUSE_STATUS                SCI_ADDR(REGS_EFUSE_BASE, 0x0020)
#define REG_EFUSE_BLK_FLAG0             SCI_ADDR(REGS_EFUSE_BASE, 0x0024)
#define REG_EFUSE_BLK_FLAG1             SCI_ADDR(REGS_EFUSE_BASE, 0x0028)
#define REG_EFUSE_BLK_FLAG0_CLR         SCI_ADDR(REGS_EFUSE_BASE, 0x0030)
#define REG_EFUSE_BLK_FLAG1_CLR         SCI_ADDR(REGS_EFUSE_BASE, 0x0034)
#define REG_EFUSE_MAGIC_NUMBER          SCI_ADDR(REGS_EFUSE_BASE, 0x0040)
#define REG_EFUSE_STROBE_LOW_WIDTH      SCI_ADDR(REGS_EFUSE_BASE, 0x0044)
#define REG_EFUSE_EFUSE_DEB_CTRL        SCI_ADDR(REGS_EFUSE_BASE, 0x0048)

/* bits definitions for register REG_EFUSE_READ_WRITE_INDEX */
#define BITS_READ_WRITE_INDEX(_x_)      ( (_x_) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)) )

#define SHFT_READ_WRITE_INDEX           ( 0 )
#define MASK_READ_WRITE_INDEX           ( BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4) )

/* bits definitions for register REG_EFUSE_MODE_CTRL */
/* Write 1 to this bit start A_PGM mode(array PGM mode).
 * This bit is self-clear, read this bit will always get 0.
 */
#define BIT_PG_START                    ( BIT(0) )
#define BIT_RD_START                    ( BIT(1) )
#define BIT_STANDBY_START               ( BIT(2) )

/* bits definitions for register REG_EFUSE_CFG0 */
#define BITS_TPGM_TIME_CNT(_x_)         ( (_x_) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)) )
#define BITS_EFS_TYPE(_x_)              ( (_x_) << 16 & (BIT(16)|BIT(17)) )
#define BIT_EFS_VDDQ_K1_ON              ( BIT(28) )
#define BIT_EFS_VDDQ_K2_ON              ( BIT(29) )
/* Set this bit will open 0.9v static power supply for efuse memory,
 * before any operation towards to efuse memory this bit have to set to 1.
 * Once this bit is cleared, the efuse will go to power down mode.
 */
#define BIT_EFS_VDD_ON                  ( BIT(30) )
/* ONly set this bit can SW write register field of TPGM_TIME_CNT and start PGM mode,
 * for protect sw unexpectedly programmed efuse memory.
 */
#define BIT_PGM_EN                      ( BIT(31) )

/* bits definitions for register REG_EFUSE_CFG1 */
#define BIT_BLK0_AUTO_TEST_EN           ( BIT(0) )

/* bits definitions for register REG_EFUSE_STATUS */
#define BIT_PGM_BUSY                    ( BIT(0) )
#define BIT_READ_BUSY                   ( BIT(1) )
#define BIT_STANDBY_BUSY                ( BIT(2) )

/* bits definitions for register REG_EFUSE_BLK_FLAG0 */
#define BIT_BLK0_PROT_FLAG              ( BIT(0) )

/* bits definitions for register REG_EFUSE_BLK_FLAG1 */
#define BIT_BLK0_ERR_FLAG               ( BIT(0) )

/* bits definitions for register REG_EFUSE_BLK_FLAG0_CLR */
#define BIT_BLK0_PROT_FLAG_CLR          ( BIT(0) )

/* bits definitions for register REG_EFUSE_BLK_FLAG1_CLR */
#define BIT_BLK0_ERR_FLAG_CLR           ( BIT(0) )

/* bits definitions for register REG_EFUSE_MAGIC_NUMBER */
/* Magic number, only when this field is 0x8810, the efuse programming command can be handle.
 * So, if SW want to program efuse memory, except open clocks and power, the follow conditions must be met:
 * 1. PGM_EN = 1;
 * 2. EFUSE_MAGIC_NUMBER = 0x8810
 */
#define BITS_MAGIC_NUMBER(_x_)          ( (_x_) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)|BIT(14)|BIT(15)) )
#define BITS_DEB_MAGIC_NUMBER(_x_)      ( (_x_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)|BIT(20)|BIT(21)|BIT(22)|BIT(23)|BIT(24)|BIT(25)|BIT(26)|BIT(27)|BIT(28)|BIT(29)|BIT(30)|BIT(31)) )

/* bits definitions for register REG_EFUSE_STROBE_LOW_WIDTH */
#define BITS_EFUSE_STROBE_LOW_WIDTH(_x_)( (_x_) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)) )
#define BITS_CLK_EFS_DIV(_x_)           ( (_x_) << 16 & (BIT(16)|BIT(17)|BIT(18)|BIT(19)|BIT(20)|BIT(21)|BIT(22)|BIT(23)) )

#define SHFT_CLK_EFS_DIV                ( 16 )
#define MASK_CLK_EFS_DIV                ( BIT(16)|BIT(17)|BIT(18)|BIT(19)|BIT(20)|BIT(21)|BIT(22)|BIT(23) )

/* bits definitions for register REG_EFUSE_EFUSE_DEB_CTRL */
#define BIT_MARGIN_MODE_EN              ( BIT(1) )
#define BIT_DOUBLE_BIT_DISABLE          ( BIT(0) )

/* vars definitions for controller REGS_EFUSE */
#define EFUSE_MAGIC_NUMBER              ( 0x8810 )
#define EFUSE_DEB_MAGIC_NUMBER          ( 0x6868 )
#define BIT_EFUSE_PROT_LOCK             ( BIT(31) )

#define EFUSE_MAGIC 0x8810
#define REGS_EFUSE_BASE                 SPRD_UIDEFUSE_PHYS

#if defined(CONFIG_SC9860)
#define EFUSE_BLOCK_MAX                 ( 256)
#else
#define EFUSE_BLOCK_MAX                 ( 16 )
#endif
#define EFUSE_BLOCK_WIDTH               ( 32 )

u32 SCI_GetTickCount(void);
#define jiffies (get_timer_masked())	/* return msec count */
#define msecs_to_jiffies(a) (a)
#define time_after(a,b)	((int)(b) - (int)(a) < 0)
#define cpu_relax()

static void msleep(u32 ms)
{
	u32 timeout = jiffies + ms;
	while (!time_after(jiffies, timeout)) {
		;
	}
}

static void ap_efuse_lookat(void)
{
	volatile u32 *reg = (volatile u32 *)REGS_EFUSE_BASE;
	int cnt = 16;
	while (cnt--) {
		printf("[%p] = %08x\n", reg, *reg);
		reg++;
	}
	printf("\n");
}

static void ap_efuse_reset(void)
{
	/* should enable module before soft reset efuse */
	WARN_ON(!sci_glb_read(REG_AON_APB_APB_EB0, BIT_EFUSE_EB));
	sci_glb_set(REG_AON_APB_APB_RST0, BIT_EFUSE_SOFT_RST);
	udelay(5);
	sci_glb_clr(REG_AON_APB_APB_RST0, BIT_EFUSE_SOFT_RST);
}

/* FIXME: Set EFS_VDD_ON will open 0.9v static power supply for efuse memory,
 * before any operation towards to efuse memory this bit have to set to 1.
 * Once this bit is cleared, the efuse will go to power down mode.
 *
 * each time when EFS_VDD_ON changes, software should wait at least 1ms to let
 * VDD become stable.
 *
 * For VDDQ(1.8v) power, to prevent the overshot of VDDQ, a extra power switch
 * connected to ground are controlled by "EFS_VDDQ_K2_ON"
 */
static void ap_efuse_power_on(void)
{
	u32 cfg0;
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
	ap_efuse_reset();
	cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);
	cfg0 &= ~BIT_EFS_VDDQ_K1_ON;
	cfg0 |= BIT_EFS_VDD_ON | BIT_EFS_VDDQ_K2_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);
}

static void ap_efuse_power_off(void)
{
	u32 cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);
	if (cfg0 & BIT_EFS_VDDQ_K1_ON) {
		cfg0 &= ~BIT_EFS_VDDQ_K1_ON;
		__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
		msleep(1);
	}

	cfg0 |= BIT_EFS_VDDQ_K2_ON;
	cfg0 &= ~BIT_EFS_VDD_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);

	sci_glb_clr(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
}

static __inline int ap_efuse_wait_clear(u32 bits)
{
	int ret = 0;
	unsigned long timeout;

	debugf("ap efuse wait %x\n", __raw_readl((void *)REG_EFUSE_STATUS));

	/* wait for maximum of 300 msec */
	timeout = jiffies + msecs_to_jiffies(300);
	while (__raw_readl((void *)REG_EFUSE_STATUS) & bits) {
		if (time_after(jiffies, timeout)) {
			WARN_ON(1);
			ret = -ETIMEDOUT;
			break;
		}
		cpu_relax();
	}
	return ret;
}

static u32 ap_efuse_read(int blk)
{
	u32 val = 0;

	/* enable efuse module clk and power before */

	__raw_writel(blk,(void *)REG_EFUSE_READ_WRITE_INDEX);
	__raw_writel(BIT_RD_START, (void *)REG_EFUSE_MODE_CTRL);

	if (IS_ERR_VALUE(ap_efuse_wait_clear(BIT_READ_BUSY)))
		goto out;

	val = __raw_readl((void *)REG_EFUSE_DATA_RD);

out:
	return val;
}

u32 sprd_ap_efuse_read(int blk_index)
{
	u32 val;

	ap_efuse_power_on();
	val = ap_efuse_read(blk_index);
	ap_efuse_power_off();
	debugf("ap efuse read block =%d,val = 0x%x\n", blk_index,val);
	return val;
}

static void ap_efuse_prog_power_on(void)
{
	u32 cfg0;
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
	cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);
	cfg0 &= ~(BIT_EFS_VDDQ_K2_ON | BIT_EFS_VDDQ_K1_ON);
	cfg0 |= BIT_EFS_VDD_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);

	cfg0 |= BIT_EFS_VDDQ_K1_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);
}

static int ap_efuse_prog(int blk, u32 val)
{
	u32 cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);

	/* enable pgm mode and setup magic number before programming */
	cfg0 |= BIT_PGM_EN;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	__raw_writel(BITS_MAGIC_NUMBER(EFUSE_MAGIC),
		     (void *)REG_EFUSE_MAGIC_NUMBER);

	__raw_writel(val, (void *)REG_EFUSE_DATA_WR);
	__raw_writel(blk, (void *)REG_EFUSE_READ_WRITE_INDEX);
	printf("cfg0 %x\n", __raw_readl((void *)REG_EFUSE_CFG0));
	__raw_writel(BIT_PG_START, (void *)REG_EFUSE_MODE_CTRL);
	if (IS_ERR_VALUE(ap_efuse_wait_clear(BIT_PGM_BUSY)))
		goto out;

out:
	__raw_writel(0, (void *)REG_EFUSE_MAGIC_NUMBER);
	cfg0 &= ~BIT_PGM_EN;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	return 0;
}

int sprd_ap_efuse_prog(int blk_index, u32 val)
{
	int ret;
	printf("efuse prog %d %08x\n", blk_index, val);
	/* enable vddon && vddq */
	ap_efuse_prog_power_on();
	ret = ap_efuse_prog(blk_index, val);
	ap_efuse_power_off();
	return ret;
}

void ap_efuse_block_dump(void)
{
	int idx;
	printf("ddie efuse base %08x\n", REGS_EFUSE_BASE);
	printf("ddie efuse blocks dump:\n");
	for (idx = 0; idx < EFUSE_BLOCK_MAX; idx++) {
		printf("[%02d] %08x\n", idx, sprd_ap_efuse_read(idx));
	}
}
/*******only for sansa ********/
void ap_sansa_efuse_prog_power_on(void)
{
	u32 cfg0;
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
	cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);
	cfg0 &= ~(BIT_EFS_VDDQ_K2_ON | BIT_EFS_VDDQ_K1_ON);
	cfg0 |= BIT_EFS_VDD_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);

	cfg0 |= BIT_EFS_VDDQ_K1_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);
}
/*******only for sansa ********/
void ap_sansa_efuse_power_off(void)
{
	u32 cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);
	if (cfg0 & BIT_EFS_VDDQ_K1_ON) {
		cfg0 &= ~BIT_EFS_VDDQ_K1_ON;
		__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
		msleep(1);
	}

	cfg0 |= BIT_EFS_VDDQ_K2_ON;
	cfg0 &= ~BIT_EFS_VDD_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);

	sci_glb_clr(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
}
/*******only for sansa ********/
void sansa_enable_efuse_EB(void)
{
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
}




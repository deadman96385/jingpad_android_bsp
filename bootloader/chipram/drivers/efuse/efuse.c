/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
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

#include <common.h>
#include <linux/types.h>
#include <asm/io.h>
#include "sprd_regs_efuse.h"
#include <asm/arch/sprd_reg.h>
#include <timer.h>
#include <sci_types.h>

#define EFUSE_MAGIC 0x8810
#define printf(x...) do{}while(0)
#define pr_debug(args...)  printf(args)
#define pr_info() printf

#define WARN_ON(a)
//typedef unsigned long int		uint32;
#define REG_GLB_SET(A)                  ( A + 0x1000 )
#define REG_GLB_CLR(A)                  ( A + 0x2000 )

u32 sci_glb_read(u32 reg, u32 msk)
{
	return __raw_readl(reg) & msk;
}
int sci_glb_write(u32 reg, u32 val, u32 msk)
{
	unsigned long flags, hw_flags;
	__raw_writel((__raw_readl(reg) & ~msk) | val, reg);
	return 0;
}
static int __is_glb(u32 reg)
{
	return 1;
}
int sci_glb_set(u32 reg, u32 bit)
{
	if (__is_glb(reg))
	 __raw_writel(bit, REG_GLB_SET(reg));
	 else
	WARN_ON(1);
	return 0;
}
int sci_glb_clr(u32 reg, u32 bit)
{
	if (__is_glb(reg))
	__raw_writel(bit, REG_GLB_CLR(reg));
	else
	WARN_ON(1);
	return 0;
}

uint32 SCI_EGetTickCount(void)
{
	return sprd_get_syscnt();
}

//u32 SCI_GetTickCount(void);
#define jiffies (SCI_EGetTickCount()) /* return msec count */
#define msecs_to_jiffies(a) (a)
#define time_after(a,b)	((int)(b) - (int)(a) < 0)
#define cpu_relax()
#define	ETIMEDOUT	110	/* Connection timed out */
#define udelay(x)	\
	do { \
		volatile int i; \
		int cnt = 1000 * x; \
		for (i=0; i<cnt; i++);\
	} while(0);
static void msleep(u32 ms)
{
	u32 timeout = jiffies + ms;
	while(!time_after(jiffies, timeout)) {
		;
	}
}

#define REGS_EFUSE_BASE                 SPRD_UIDEFUSE_PHYS
#if defined (CONFIG_SOC_SHARKLJ1)
#define EFUSE_BLOCK_MAX                 ( 256 )
#else
#define EFUSE_BLOCK_MAX                 ( 16 )
#endif
#define EFUSE_BLOCK_WIDTH               ( 32 )	/* bit counts */
#define BLK_DHR_DETA		7

void efuse_lookat(void)
{
	volatile u32 *reg = (volatile u32 *)REGS_EFUSE_BASE;
	int cnt = 16;
	while(cnt--) {
		printf("[%p] = %08x\n", reg, *reg);
		reg++;
	}
	printf("\n");
}

static void efuse_lock(void)
{
}

static void efuse_unlock(void)
{
}

static void efuse_reset(void)
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
void __efuse_power_on(void)
{
	u32 cfg0;
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
	efuse_reset();
	cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);
	cfg0 &= ~BIT_EFS_VDDQ_K1_ON;
	cfg0 |= BIT_EFS_VDD_ON | BIT_EFS_VDDQ_K2_ON;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	msleep(1);
}

void __efuse_power_off(void)
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

static __inline int __efuse_wait_clear(u32 bits)
{
	int ret = 0;
	unsigned long timeout;

	pr_debug("wait %x\n", __raw_readl((void *)REG_EFUSE_STATUS));

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

static u32 __efuse_read(int blk)
{
	u32 val = 0;

	/* enable efuse module clk and power before */

	__raw_writel(blk,(void *)REG_EFUSE_READ_WRITE_INDEX);
	__raw_writel(BIT_RD_START, (void *)REG_EFUSE_MODE_CTRL);
	if ((__efuse_wait_clear(BIT_READ_BUSY)))
	//if (IS_ERR_VALUE(__efuse_wait_clear(BIT_READ_BUSY)))
		goto out;

	val = __raw_readl((void *)REG_EFUSE_DATA_RD);

out:
	return val;
}

static u32 efuse_read(int blk_index)
{
	u32 val;
	pr_debug("efuse read %d\n", blk_index);
	efuse_lock();

	__efuse_power_on();
	val = __efuse_read(blk_index);
	__efuse_power_off();

	efuse_unlock();
	return val;
}

PUBLIC u32 ddie_efuse_read(int blk_index)
{
	return efuse_read(blk_index);
}

void __efuse_prog_power_on(void)
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


static int __efuse_prog(int blk, u32 val)
{
	u32 cfg0 = __raw_readl((void *)REG_EFUSE_CFG0);


	if (blk < 0 || blk >= EFUSE_BLOCK_MAX)	/* debug purpose */
		goto out;

	/* enable pgm mode and setup magic number before programming */
	cfg0 |= BIT_PGM_EN;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	__raw_writel(BITS_MAGIC_NUMBER(EFUSE_MAGIC),
		     (void *)REG_EFUSE_MAGIC_NUMBER);

	__raw_writel(val, (void *)REG_EFUSE_DATA_WR);
	__raw_writel(blk,(void *)REG_EFUSE_READ_WRITE_INDEX);
	pr_debug("cfg0 %x\n", __raw_readl((void *)REG_EFUSE_CFG0));
	__raw_writel(BIT_PG_START, (void *)REG_EFUSE_MODE_CTRL);
	if ((__efuse_wait_clear(BIT_PGM_BUSY)))
		goto out;

out:
	__raw_writel(0, (void *)REG_EFUSE_MAGIC_NUMBER);
	cfg0 &= ~BIT_PGM_EN;
	__raw_writel(cfg0, (void *)REG_EFUSE_CFG0);
	return 0;
}


static int efuse_prog(int blk_index, u32 val)
{
	int ret;
	pr_debug("efuse prog %d %08x\n", blk_index, val);

	efuse_lock();

	/* enable vddon && vddq */
	__efuse_prog_power_on();
	ret = __efuse_prog(blk_index, val);
	__efuse_power_off();

	efuse_unlock();
	return ret;
}


PUBLIC int ddie_efuse_prog(int blk_index, u32 val)
{
        return efuse_prog(blk_index, val);
}


#define EFUSE_3RD_IP_BLOCK 2
#define BIT_EFUSE_CCP_EB (BIT(10))

static u32 ccp_efuse_read(int blk_index)
{
    u32 val;

	val = efuse_read(blk_index);
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_EFUSE_EB); /* TODO : need to update */

    return val;
}

PUBLIC void sync_efuse_ahb_ccp_eb(void)
{
    if(!(ccp_efuse_read(EFUSE_3RD_IP_BLOCK) & (uint32)BIT_EFUSE_CCP_EB))
	{
		/*Noted: freeman need check!!!!!!!!!!!!!!!!!*/
        //(*(volatile uint32 *)REG_AP_AHB_AHB_EB) &= (uint32)(~BIT_AP_AHB_CC63P_EB);
	}
}

void sansa_enable_efuse_EB(void)
{
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_EFUSE_EB);
}

/*blk config*/
#if defined(CONFIG_SOC_SHARKL5)
#include <security/sec_efuse_sharkl5_drv.h>
#define BLK_START 72
#define BLK_END 95
#define BLK_NUM 24
#define BLK_DOUBLE 0
#define EFUSE_IRAM_BASE 0x00015c04
#define EFUSE_IRAM_END	0x00015fff
#endif

#if defined(CONFIG_SOC_SHARKL5PRO)
#include <security/sec_efuse_sharkl5pro_drv.h>
#define BLK_START 72
#define BLK_END 95
#define BLK_NUM 24
#define BLK_DOUBLE 0
#define EFUSE_IRAM_BASE 0x00015c04
#define EFUSE_IRAM_END	0x00015fff
#endif

#if defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_SHARKL5PRO)
static int write_efuse_to_ram(void)
{
	int i;
	u32 blk[BLK_NUM] = { 0 };
	Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;

	for(i = 0; i < BLK_NUM ; i++) {
		CHIP_REG_SET(EFUSE_IRAM_BASE + i * 4, 0x0);
	}

	ret = efuse_read_drv(BLK_START, BLK_END, blk, BLK_DOUBLE);
	if(ret == EFUSE_RESULT_SUCCESS){
		for(i = 0; i < BLK_NUM; i++) {
			if((EFUSE_IRAM_BASE + i * 4) <= EFUSE_IRAM_END)
				CHIP_REG_SET(EFUSE_IRAM_BASE + i * 4, blk[i]);
		}
	}
	return ret;
}

int sprd_write_efuse_to_ram(void)
{
	Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;

	ret = write_efuse_to_ram();
	if(ret != EFUSE_RESULT_SUCCESS){
		ret = write_efuse_to_ram();
	}

	CHIP_REG_SET((EFUSE_IRAM_BASE - 0x4), 0);
	CHIP_REG_SET((EFUSE_IRAM_BASE - 0x4), ret);
	return ret;
}
#endif

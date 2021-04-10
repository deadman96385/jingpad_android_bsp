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
 */

#include <asm/io.h>
#include <sprd_glb.h>
#include <asm/arch/sprd_reg.h>
#include <common.h>
#include <linux/types.h>
#include <linux/err.h>

typedef unsigned int u32;

/* registers definitions for controller REGS_EFUSE */

#define REG_EFUSE_DATA_RD               SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0000)
#define REG_EFUSE_DATA_WR               SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0004)
#define REG_EFUSE_BLOCK_INDEX      		SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0008)
#define REG_EFUSE_CFG0	                SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x000c)
#define REG_EFUSE_DC_CFG0               SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0010)
#define REG_EFUSE_DC_CFG1               SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0014)
#define REG_EFUSE_RD_CFG              	SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0018)
#define REG_EFUSE_OP_CFG               	SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x001c)
#define REG_EFUSE_KAR             		SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0020)
#define REG_EFUSE_MOD_CTRL             	SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0024)
#define REG_EFUSE_STATUS                SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0028)
#define REG_EFUSE_IP_REVISION           SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x002c)
#define REG_EFUSE_SECURE_STATUS         SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0030)
#define REG_EFUSE_CMD_HI32         		SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0034)
#define REG_EFUSE_CMD_LO32         		SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0038)
#define REG_EFUSE_LDO_RAISE_TIME        SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x003c)
#define REG_EFUSE_LDO_DROP_TIME         SCI_ADDR(SPRD_UIDEFUSE_BASE, 0x0040)

/* bits definitions for register REG_EFUSE_CFG0 */
#define BIT_PGM_EN                    ( BIT(31) )
#define BIT_EFS_VDD_ON                ( BIT(30) )
#define BIT_EFS_VCCRAM_ON             ( BIT(29) )
#define BIT_EFS_VCCFHV_ON             ( BIT(28) )

/* bits definitions for register REG_EFUSE_DC_CFG1 */
#define BIT_DC_NUM(_x_)         ( (_x_) << 0 & (BIT(0) | BIT(1) | BIT(2) | BIT(3)))
#define BIT_DC_LEN(_x_)         ( (_x_) << 0 & (BIT(5) | BIT(6) | BIT(7) | BIT(8) | BIT(9)))

/* bits definitions for register REG_EFUSE_RD_CFG */
#define BIT_ISENSELV(_x_)         ( (_x_) << 0 & (BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4) | BIT(5)))
#define BIT_IFAVOR_LEN(_x_)       ( (_x_) << 0 & (BIT(6) | BIT(7) | BIT(8)))

/* bits definitions for register REG_EFUSE_OP_CFG */
#define BIT_OP_MODE(_x_)         ( (_x_) << 0 & (BIT(0) | BIT(1) | BIT(2) | BIT(3) | BIT(4)))

/* bits definitions for register REG_EFUSE_MOD_CTRL */
#define BIT_MARGIN_EN                 ( BIT(3) )
#define BIT_STANDBY_EN                ( BIT(2) )
#define BIT_CMD_DERECT_INPUT_SEL      ( BIT(1) )
#define BIT_CMD_INPUT                 ( BIT(0) )

/* bits definitions for register REG_EFUSE_STATUS */
#define BIT_PGM_BUSY                ( BIT(0) )
#define BIT_READ_BUSY               ( BIT(1) )
#define BIT_STANDY_BUSY             ( BIT(2) )
#define BIT_DATA_READY              ( BIT(4) )
#define BIT_CTL_BUSY                ( BIT(24) )

#define ISENSELV 0x0
#define IFAVOR 0x0
#define SHIFT_ISENSELV 0
#define READ_MODE 0x0015
#define PROG_MODE 0x0011
#define KEY_ACCESS_MODE 0x0018
#define KEY_ACCESS_VALUE             ( 0x55aa55)

#define DC_READ_MODE 0x0016
#define DC_WRITE_MODE 0x0013
#define HWSPINLOCK_TIMEOUT		(5000)
#define BIT_LOCK_EFUSE                (BIT(31))

#define EFUSE_BLOCK_MAX                 ( 63 )
#define EFUSE_BLOCK_WIDTH               ( 32 )

#define jiffies (get_timer_masked())	/* return msec count */
#define msecs_to_jiffies(a) (a)
#define time_after(a,b)	((int)(b) - (int)(a) < 0)
#define cpu_relax()

static inline unsigned int ap_efuse_reg_read(u32 reg)
{
	return __raw_readl(reg);
}

static inline void ap_efuse_reg_write(u32 val, u32 reg)
{
	__raw_writel(val, reg);
}

static inline void ap_efuse_bit_write(u32 reg, u32 bits,
				      u32 clear_msk)
{
	__raw_writel(((__raw_readl(reg) & ~clear_msk) | bits), reg);
}

static void msleep(u32 ms)
{
	u32 timeout = jiffies + ms;
	while (!time_after(jiffies, timeout)) {
		;
	}
}

static void ap_efuse_lookat(void)
{
	volatile u32 *reg = (volatile u32 *)SPRD_UIDEFUSE_BASE;
	int cnt = 16;
	while (cnt--) {
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

static void ap_efuse_reset(void)
{
	/* should enable module before soft reset efuse */
	WARN_ON(!sci_glb_read(REG_AON_APB_APB_EB0, BIT_AON_APB_EFUSE_EB));
	sci_glb_set(REG_AON_APB_APB_RST0, BIT_AON_APB_EFUSE_SOFT_RST);
	udelay(10);
	sci_glb_clr(REG_AON_APB_APB_RST0, BIT_AON_APB_EFUSE_SOFT_RST);
}

static __inline int ap_efuse_wait_clear(u32 bits)
{
	int ret = 0;
	unsigned long timeout;

	debugf("wait 0x%x\n", ap_efuse_reg_read(REG_EFUSE_STATUS));
	udelay(10);
	/* wait for maximum of 300 msec */
	timeout = jiffies + msecs_to_jiffies(300);
	while (ap_efuse_reg_read(REG_EFUSE_STATUS) & bits) {
		if (time_after(jiffies, timeout)) {
			WARN_ON(1);
			ret = -ETIMEDOUT;
			break;
		}
		cpu_relax();
	}
	return ret;
}

static void ap_efuse_enable(void)
{
	sci_glb_set(REG_AON_APB_APB_EB0, BIT_AON_APB_EFUSE_EB);
}

static void ap_efuse_disable(void)
{
	sci_glb_clr(REG_AON_APB_APB_EB0, BIT_AON_APB_EFUSE_EB);
}

static void ap_efuse_margin_mode(void)
{
	ap_efuse_bit_write(REG_EFUSE_MOD_CTRL, 0, BIT_MARGIN_EN);
}

static int ap_efuse_read(int bank_index, int blk_index, u32 *data)
{
	u32 val = 0;
	u32 cfg_temp = 0;
	int ret = 0;

	ap_efuse_reg_write(READ_MODE, REG_EFUSE_OP_CFG);
	cfg_temp = (ISENSELV << SHIFT_ISENSELV) | IFAVOR;
	ap_efuse_reg_write(cfg_temp, REG_EFUSE_RD_CFG);
	ap_efuse_reg_write(blk_index, REG_EFUSE_BLOCK_INDEX);
	ap_efuse_bit_write(REG_EFUSE_MOD_CTRL, BIT_CMD_INPUT, 0);

	ret = ap_efuse_wait_clear(BIT_CTL_BUSY);
	if (ret) {
		debugf("iefuse time out 0x%x\n", ap_efuse_reg_read(REG_EFUSE_STATUS));
		return ret;
	}

	val = ap_efuse_reg_read(REG_EFUSE_DATA_RD);
	*data = val;
	return ret;
}


static int ap_efuse_dc_read(u32 dc_num, u32 dc_len, u32 *data)
{
	u32 val = 0;
	int ret = 0;

	ap_efuse_reg_write(DC_READ_MODE, REG_EFUSE_OP_CFG);
	ap_efuse_bit_write(REG_EFUSE_DC_CFG1, dc_num, 0);
	ap_efuse_bit_write(REG_EFUSE_DC_CFG1, dc_len, 0);
	ap_efuse_bit_write(REG_EFUSE_MOD_CTRL, BIT_CMD_INPUT, 0);

	ret = ap_efuse_wait_clear(BIT_CTL_BUSY);
	if (ret) {
		debugf("iefuse time out 0x%x\n", ap_efuse_reg_read(REG_EFUSE_STATUS));
		return ret;
	}

	val = ap_efuse_reg_read(REG_EFUSE_DATA_RD);
	*data = val ;
	return ret;
}

static int ap_efuse_dc_write(u32 data, u32 dc_num, u32 dc_len)
{
	int ret = 0;

	debugf("iefuse dc write 0x%08x\n", data);
	ap_efuse_reg_write(DC_WRITE_MODE, REG_EFUSE_OP_CFG);
	ap_efuse_bit_write(REG_EFUSE_DC_CFG1, dc_num, 0);
	ap_efuse_bit_write(REG_EFUSE_DC_CFG1, dc_len, 0);
	ap_efuse_reg_write(data, REG_EFUSE_DC_CFG0);
	ap_efuse_bit_write(REG_EFUSE_MOD_CTRL, BIT_CMD_INPUT, 0);

	ret = ap_efuse_wait_clear(BIT_CTL_BUSY);
	if (ret) {
		debugf("iefuse time out 0x%x\n", ap_efuse_reg_read(REG_EFUSE_STATUS));
	}
	return ret;
}

int sprd_ap_efuse_dc_read(u32 dc_num, u32 dc_len, u32 *data)
{
	u32 val = 0;
    int ret = 0;

	debugf("iefuse dc read number=%d,len=%d\n", dc_len, dc_num);
	efuse_lock();
	ap_efuse_enable();
	ap_efuse_margin_mode();
	ret = ap_efuse_dc_read(dc_num, dc_len, data);
	ap_efuse_disable();
	efuse_unlock();
	debugf("iefuse read 0x%08x\n", val);
	return ret;
}

int sprd_ap_efuse_dc_write(u32 data, u32 dc_len, u32 dc_num)
{
	int ret = 0;

	debugf("iefuse dc write 0x%x num=%d,len=%d\n", data, dc_len, dc_num);
	efuse_lock();
	ap_efuse_enable();
	ap_efuse_margin_mode();
	ret = ap_efuse_dc_write(data, dc_len, dc_num);
	ap_efuse_disable();
	efuse_unlock();
	return ret;
}

u32 sprd_ap_efuse_read(int blk_index)
{
	u32 val = 0;
	int bank_index = 0;
	int ret = 0;

	efuse_lock();
	ap_efuse_enable();
	ap_efuse_margin_mode();
	ret = ap_efuse_read(bank_index, blk_index, &val);
	if(ret)
		val = 0;
	ap_efuse_disable();
	efuse_unlock();
	debugf("iefuse read ret %d,index %d, 0x%08x\n", ret, blk_index, val);
	return val;
}

int sprd_ap_efuse_prog(int blk_index, u32 val)
{
	int ret = 0;
	debugf("iefuse prog %d %08x\n", blk_index, val);
	return ret;
}

void ap_efuse_block_dump(void)
{
	int idx;
	debugf("ap iefuse base %08x\n", SPRD_UIDEFUSE_BASE);
	debugf("ap iefuse blocks dump:\n");
	for (idx = 0; idx < EFUSE_BLOCK_MAX; idx++) {
		debugf("[%02d] %08x\n", idx, sprd_ap_efuse_read(idx));
	}
}

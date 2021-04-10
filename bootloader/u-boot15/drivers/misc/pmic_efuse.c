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

#include <asm/arch/sprd_reg.h>
#include <asm/io.h>
#include <common.h>
#include <linux/types.h>
#include <linux/err.h>
#include "adi.h"

typedef unsigned int u32;

/* registers definitions for controller ANA_REGS_EFUSE */
#if defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721) || \
	defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
#define ANA_REG_EFUSE_GLB_CTRL          SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0000)
#define ANA_REG_EFUSE_DATA_RD           SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0004)
#define ANA_REG_EFUSE_DATA_WR           SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0008)
#define ANA_REG_EFUSE_BLOCK_INDEX       SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x000c)
#define ANA_REG_EFUSE_MODE_CTRL         SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0010)
#define ANA_REG_EFUSE_STATUS            SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0014)
#define ANA_REG_EFUSE_WR_TIMING_CTRL    SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0020)
#define ANA_REG_EFUSE_RD_TIMING_CTRL    SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0024)
#define ANA_REG_EFUSE_EFUSE_DEB_CTRL    SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0028)
#else
#define ANA_REG_EFUSE_GLB_CTRL          SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0000)
#define ANA_REG_EFUSE_DATA_RD           SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0004)
#define ANA_REG_EFUSE_DATA_WR           SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0008)
#define ANA_REG_EFUSE_BLOCK_INDEX       SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x000c)
#define ANA_REG_EFUSE_MODE_CTRL         SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0010)
#define ANA_REG_EFUSE_STATUS            SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0014)
#define ANA_REG_EFUSE_WR_TIMING_CTRL    SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0028)
#define ANA_REG_EFUSE_RD_TIMING_CTRL    SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x002c)
#define ANA_REG_EFUSE_EFUSE_DEB_CTRL    SCI_ADDR(ANA_REGS_EFUSE_BASE, 0x0030)
#endif

/* bits definitions for register ANA_REG_EFUSE_GLB_CTRL */
/* Efuse SW programme enable.
 */
#define BIT_EFUSE_PGM_EN                ( BIT(0) )
/* Efuse type select, 00:TSMC, 01, 1x reserved.
 */
#define BITS_EFUSE_TYPE(_x_)            ( (_x_) << 1 & (BIT(1)|BIT(2)) )

/* bits definitions for register ANA_REG_EFUSE_DATA_RD */
#define BITS_EFUSE_DATA_RD(_x_)         ( (_x_) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)) )

/* bits definitions for register ANA_REG_EFUSE_DATA_WR */
#define BITS_EFUSE_DATA_WR(_x_)         ( (_x_) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)) )

/* bits definitions for register ANA_REG_EFUSE_BLOCK_INDEX */
#define BITS_READ_WRITE_INDEX(_x_)      ( (_x_) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)) )

#define SHFT_READ_WRITE_INDEX           ( 0 )
#define MASK_READ_WRITE_INDEX           ( BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4) )

/* bits definitions for register ANA_REG_EFUSE_MODE_CTRL */
/* Write 1 to this bit start A_PGM mode(array PGM mode).
 * This bit is self-clear, read this bit will always get 0.
 */
#define BIT_PG_START                    ( BIT(0) )
#define BIT_RD_START                    ( BIT(1) )
#define BIT_STANDBY_START               ( BIT(2) )
#define BIT_NORMAL_RD_FLAG_CLR		( BIT(2) )

/* bits definitions for register ANA_REG_EFUSE_STATUS */
#define BIT_PGM_BUSY                    ( BIT(0) )
#define BIT_READ_BUSY                   ( BIT(1) )
#define BIT_STANDBY_BUSY                ( BIT(2) )
#define BIT_GLOBAL_PROT					( BIT(3) )
#define BIT_NORMAL_RD_DONE					( BIT(4) )

/* bits definitions for register ANA_REG_EFUSE_WR_TIMING_CTRL */
#define BITS_EFUSE_WR_TIMING(_x_)       ( (_x_) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9)|BIT(10)|BIT(11)|BIT(12)|BIT(13)) )

/* bits definitions for register ANA_REG_EFUSE_RD_TIMING_CTRL */
#define BITS_EFUSE_RD_TIMING(_x_)       ( (_x_) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9)) )

/* bits definitions for register ANA_REG_EFUSE_EFUSE_DEB_CTRL */
#define BIT_MARGIN_MODE_EN              ( BIT(1) )

u32 SCI_GetTickCount(void);
#define jiffies (get_timer_masked())	/* return msec count */
#define msecs_to_jiffies(a) (a)
#define time_after(a,b)	((int)(b) - (int)(a) < 0)
#define cpu_relax()

#define ANA_REGS_EFUSE_BASE ANA_EFS_BASE
#define EFUSE_BLOCK_MAX                 ( 32 )
#if defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721) || \
	defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
#define EFUSE_BLOCK_WIDTH               ( 16 )	/* bit counts */
#define VALUE_TYPE	u16
#else
#define EFUSE_BLOCK_WIDTH               ( 8 )	/* bit counts */
#define VALUE_TYPE	u8
#endif


static VALUE_TYPE dummy_cached_otp[EFUSE_BLOCK_MAX] = {
	0x9f, 0xdf, 0xef, 0x37, 0x91, 0x27, 0xfc, 0xfd,
	0x7f, 0x7f, 0x7f, 0x7f, 0xff, 0xfe, 0x7d, 0xbf,
	0x7f, 0xff, 0x6c, 0x00, 0xe7, 0x71, 0x5f, 0xb7,
	0x81, 0x5b, 0xe7, 0x3c, 0xa1, 0x27, 0x8a, 0xa1,
};

static void pmic_efuse_lookat(void)
{
	volatile u32 *reg = (volatile u32 *)ANA_REGS_EFUSE_BASE;
	int cnt = 16;
	while (cnt--) {
		debugf("[%p] = %08x\n", reg, sci_adi_read((u32) reg));
		reg++;
	}
	debugf("\n");
}

static void pmic_efuse_power_on(void)
{
	sci_adi_set(ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_EFS_EN);
}

static void pmic_efuse_power_off(void)
{
	sci_adi_clr(ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_EFS_EN);
}

static __inline int pmic_efuse_wait_clear(u32 bits)
{
	int ret = 0;
	unsigned long timeout;
	u32 bit_status = 1;
	u32 val;

	debugf("pmic efuse wait %x\n", sci_adi_read(ANA_REG_EFUSE_STATUS));
	udelay(2000);
	/* wait for maximum of 3000 msec */
	timeout = jiffies + msecs_to_jiffies(3000);
	while (bit_status) {
		val = sci_adi_read(ANA_REG_EFUSE_STATUS);
#if defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721) || \
	defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
		bit_status = (~val) & bits;
#else
		bit_status = val & bits;
#endif
		if (time_after(jiffies, timeout)) {
			WARN_ON(1);
			ret = -ETIMEDOUT;
			break;
		}
		cpu_relax();
	}
	return ret;
}

u32 sprd_pmic_efuse_read(int blk_index)
{
	u32 val = 0;

	pmic_efuse_power_on();
#if defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721) || \
	defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	sci_adi_set(ANA_REG_EFUSE_MODE_CTRL, BIT_NORMAL_RD_FLAG_CLR);
	if (IS_ERR_VALUE(pmic_efuse_wait_clear(BIT_STANDBY_BUSY)))
		goto out;
#endif
	sci_adi_raw_write(ANA_REG_EFUSE_BLOCK_INDEX,
			  BITS_READ_WRITE_INDEX(blk_index));
	sci_adi_set(ANA_REG_EFUSE_MODE_CTRL, BIT_RD_START);
#if defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721) || \
	defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	if (IS_ERR_VALUE(pmic_efuse_wait_clear(BIT_NORMAL_RD_DONE)))
		goto out;
#else
	if (IS_ERR_VALUE(pmic_efuse_wait_clear(BIT_READ_BUSY)))
		goto out;
#endif
	val = sci_adi_read(ANA_REG_EFUSE_DATA_RD);
#if defined(CONFIG_ADIE_SC2723)
	/* FIXME: reverse the otp value */
	val = BITS_EFUSE_DATA_RD(~val);
#endif
#if defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721)|| \
	defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	sci_adi_set(ANA_REG_EFUSE_MODE_CTRL, BIT_NORMAL_RD_FLAG_CLR);
#endif
out:
	pmic_efuse_power_off();

	debugf("pmic efuse read %d,val=0x%x\n", blk_index,val);
	return val;
}

u32 sprd_pmic_efuse_read_bits(int bit_index, int length)
{
	int i, blk_index = (int)bit_index / EFUSE_BLOCK_WIDTH;
	int blk_max = DIV_ROUND_UP(bit_index + length, EFUSE_BLOCK_WIDTH);
	u32 val = 0;

	for (i = blk_index; i < blk_max; i++) {
		val |= sprd_pmic_efuse_read(i)
		    << ((i - blk_index) * EFUSE_BLOCK_WIDTH);
	}
	val >>= (bit_index & (EFUSE_BLOCK_WIDTH - 1));
	val &= BIT(length) - 1;
	debugf("pmic efuse read bits %d ++ %d 0x%08x\n\n", bit_index, length, val);
	return val;
}

void pmic_efuse_block_dump(void)
{
	int i, idx;
	debugf("pmic efuse blocks dump:\n");

	for (idx = 0; idx < EFUSE_BLOCK_MAX; idx++) {
		u32 val = 0;
		debugf("\n");
		val = sprd_pmic_efuse_read(idx);
		dummy_cached_otp[idx] = (VALUE_TYPE) val;
		debugf("%02d  ", idx);
		for (i = EFUSE_BLOCK_WIDTH - 1; i >= 0; --i)
			debugf("%s ", (val & BIT(i)) ? "1" : "0");
		debugf("\n");
	}
	debugf("\n");
}

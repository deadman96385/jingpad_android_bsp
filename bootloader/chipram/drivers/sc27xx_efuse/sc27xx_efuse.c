/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 */

#include <timer.h>
#include <common.h>
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>

typedef unsigned int u32;

/* registers definitions for controller ANA_REGS_EFUSE */
#define ANA_REG_EFUSE_GLB_CTRL          (ANA_EFS_BASE + 0x0)
#define ANA_REG_EFUSE_DATA_RD           (ANA_EFS_BASE + 0x4)
#define ANA_REG_EFUSE_DATA_WR           (ANA_EFS_BASE + 0x8)
#define ANA_REG_EFUSE_BLOCK_INDEX       (ANA_EFS_BASE + 0xc)
#define ANA_REG_EFUSE_MODE_CTRL         (ANA_EFS_BASE + 0x10)
#define ANA_REG_EFUSE_STATUS            (ANA_EFS_BASE + 0x14)
#define ANA_REG_EFUSE_WR_TIMING_CTRL    (ANA_EFS_BASE + 0x20)
#define ANA_REG_EFUSE_RD_TIMING_CTRL    (ANA_EFS_BASE + 0x24)
#define ANA_REG_EFUSE_EFUSE_DEB_CTRL    (ANA_EFS_BASE + 0x28)

/* bits definitions for register ANA_REG_EFUSE_BLOCK_INDEX */
#define BITS_READ_INDEX(x)       ((x) << 0 & (BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)))

/* bits definitions for register ANA_REG_EFUSE_MODE_CTRL */
#define BIT_PG_START                    BIT(0)
#define BIT_RD_START                    BIT(1)
#define BIT_NORMAL_RD_FLAG_CLR		BIT(2)

/* bits definitions for register ANA_REG_EFUSE_STATUS */
#define BIT_PGM_BUSY                    BIT(0)
#define BIT_READ_BUSY                   BIT(1)
#define BIT_STANDBY_BUSY                BIT(2)
#define BIT_NORMAL_RD_DONE		BIT(4)

#define jiffies (sprd_get_syscnt())	/* return msec count */
#define msecs_to_jiffies(a) (a)
#define time_after(a,b)	((int)(b) - (int)(a) < 0)

extern void udelay(uint32 us);
extern uint32 sprd_get_syscnt(void);

static int sc27xx_efuse_wait_clear(u32 bits)
{
	unsigned long timeout;
	int ret = 0;
	u32 bit_status = 1;
	u32 val;

	udelay(2000);
	/* wait for maximum of 3000 msec */
	timeout = jiffies + msecs_to_jiffies(3000);
	while (bit_status) {
		val = ANA_REG_GET(ANA_REG_EFUSE_STATUS);
		bit_status = (~val) & bits;
		if (time_after(jiffies, timeout)) {
			ret = -1;
			break;
		}
	}
	return ret;
}

u32 sc27xx_efuse_read(int blk_index, u32 *val)
{
	int ret = 0;

	ANA_REG_OR(ANA_REG_GLB_MODULE_EN0, BIT_EFS_EN);
	ANA_REG_OR(ANA_REG_EFUSE_MODE_CTRL, BIT_NORMAL_RD_FLAG_CLR);
	ret = sc27xx_efuse_wait_clear(BIT_STANDBY_BUSY);
	if (ret)
		goto out;

	ANA_REG_SET(ANA_REG_EFUSE_BLOCK_INDEX, BITS_READ_INDEX(blk_index));
	ANA_REG_OR(ANA_REG_EFUSE_MODE_CTRL, BIT_RD_START);
	ret = sc27xx_efuse_wait_clear(BIT_NORMAL_RD_DONE);
	if (ret)
		goto out;

	*val = ANA_REG_GET(ANA_REG_EFUSE_DATA_RD);
	ANA_REG_OR(ANA_REG_EFUSE_MODE_CTRL, BIT_NORMAL_RD_FLAG_CLR);
out:
	ANA_REG_BIC(ANA_REG_GLB_MODULE_EN0, BIT_EFS_EN);

	return ret;
}

/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 */

#include <common.h>
#include <asm/io.h>
#include <timer.h>
#include <asm/sizes.h>
#include <asm/arch/sprd_reg.h>
#include <adi.h>
#include <config.h>

/* registers definitions for controller CTL_ADI */
#define REG_ADI_CTRL0				(SPRD_MISC_PHYS + 0x04)
#define REG_ADI_CHNL_PRIL			(SPRD_MISC_PHYS + 0x08)
#define REG_ADI_CHNL_PRIH			(SPRD_MISC_PHYS + 0x0C)
#define REG_ADI_INT_RAW				(SPRD_MISC_PHYS + 0x14)
#define REG_ADI_RD_CMD				(SPRD_MISC_PHYS + 0x28)
#define REG_ADI_RD_DATA				(SPRD_MISC_PHYS + 0x2C)
#define REG_ADI_FIFO_STS			(SPRD_MISC_PHYS + 0x30)
#define REG_ADI_GSSI_CFG0			(SPRD_MISC_PHYS + 0x20)
#define REG_ADI_GSSI_CFG1			(SPRD_MISC_PHYS + 0x24)

#define REG_ADI_CHNL_EN0			(SPRD_MISC_PHYS + 0x40)
#define REG_ADI_CHNL_EN1			(SPRD_MISC_PHYS + 0x20c)

#define REG_ADI_CHNL_ADDR(id)			(SPRD_MISC_PHYS + 0x44 + (id - 2) * 4)
#define HW_CHN_CNT				50

/* bits definitions for register REG_ADI_CTRL0 */
#define BIT_ARM_SCLK_EN				( BIT_1 )
#define BITS_CMMB_WR_PRI			( (1) << 4 & (BIT_4|BIT_5) )

/* bits definitions for register REG_ADI_CHNL_PRI */
#define BITS_PD_WR_PRI				( (1) << 14 & (BIT_14|BIT_15) )
#define BITS_RFT_WR_PRI				( (1) << 12 & (BIT_12|BIT_13) )
#define BITS_DSP_RD_PRI				( (2) << 10 & (BIT_10|BIT_11) )
#define BITS_DSP_WR_PRI				( (2) << 8 & (BIT_8|BIT_9) )
#define BITS_ARM_RD_PRI				( (3) << 6 & (BIT_6|BIT_7) )
#define BITS_ARM_WR_PRI				( (3) << 4 & (BIT_4|BIT_5) )
#define BITS_STC_WR_PRI				( (1) << 2 & (BIT_2|BIT_3) )
#define BITS_INT_STEAL_PRI			( (3) << 0 & (BIT_0|BIT_1) )

/* bits definitions for register REG_ADI_RD_DATA */
#define BIT_RD_CMD_BUSY				( BIT_31 )
#define SHIFT_RD_ADDR				( 16 )

#define SHIFT_RD_VALU				( 0 )
#define MASK_RD_VALU				( 0xFFFF )
#define START2LINE_MODE				( BIT_31 )
/* bits definitions for register REG_ADI_FIFO_STS */
#define BIT_FIFO_FULL				( BIT_11 )
#define FIFO_IS_FULL()	(__raw_readl(REG_ADI_FIFO_STS) & BIT_FIFO_FULL)
#define BIT_FIFO_EMPTY				( BIT_10 )

/* special V1 (sc9630 soc) defined */
/* bits definitions for register REG_ADI_CTRL0 */
#define BIT_ADI_WR(_X_)				( (_X_) << 2 )
#define BITS_ADDR_BYTE_SEL(_X_)			( (_X_) << 0 & (BIT_0|BIT_1) )

/* bits definitions for register REG_ADI_CHNL_PRI */
#define VALUE_CH_PRI				(0x0)

#define	TO_ADDR(_x_)	( ((_x_) >> SHIFT_RD_ADDR) & readback_addr_mak )
#define ANA_ADDR_SIZE			( SZ_32K + SZ_4K )
/* soc defined end*/

#define GSSI0_FRAME_LEN_MASK                    0x3f
#define GSSI0_FRAME_LEN_VALUE                   0x20
#define GSSI0_CMD_LEN_MASK                      0x1f
#define GSSI0_CMD_LEN_OFFSET                    6
#define GSSI0_CMD_LEN_VALUE                     0x10
#define ADI_ADDR_SEL_MASK                       0x3
#define ADI_ADDR_SEL_OFFSET                     3
#define ADI_ADDR_15BIT                          2

static u32 readback_addr_mak = 0;
static u32 readback_offset = 0;

static inline int __check_addr(u32 reg)
{
	if (reg < SPRD_ADISLAVE_PHYS || reg > (SPRD_ADISLAVE_PHYS + ANA_ADDR_SIZE))
		return -1;
	else
		return 0;
}

static inline int __adi_fifo_drain(void)
{
	int cnt = 1000;

	while (!(__raw_readl(REG_ADI_FIFO_STS) & BIT_FIFO_EMPTY) && --cnt) {
		udelay(2);
	}

	if (cnt == 0)
		return -1;

	return 0;
}

static inline int __adi_read(u32 regPddr)
{
	unsigned int val;
	int cnt = 200000;

	/*
	 * We don't wait write fifo empty in here,
	 * Because if normal write is SYNC, that will
	 * wait fifo empty at the end of the write.
	 */
	__raw_writel(regPddr, REG_ADI_RD_CMD);

	/*
	 * wait read operation complete, RD_data[31]
	 * is set simulaneously when writing read command.
	 * RD_data[31] will be cleared after the read operation complete, 
	 */
	do {
		val = __raw_readl(REG_ADI_RD_DATA);
	} while ((val & BIT_RD_CMD_BUSY) && --cnt);

	if (cnt == 0)
		return -1;

	/* val high part should be the address of the last read operation */
	if (TO_ADDR(val) != ((regPddr & readback_addr_mak) >> readback_offset)) {
		return -1 ;
	} else {
		return (val & MASK_RD_VALU);
	}
}

int sci_adi_read(u32 reg)
{
	int ret;

	ret = __check_addr(reg);
	if (ret < 0)
		return ret;

	return __adi_read(reg);
}

/*This value have a bit of depending on  real hardware fifo size*/
#define CACHE_SIZE	(16)
#define HEAD_ADD	(1)
#define TAIL_ADD	(0)
static struct __data {
	u32 reg;
	u16 val;
} __data_array[CACHE_SIZE];
struct __data *head_p = &__data_array[0];
struct __data *tail_p = &__data_array[0];
static u32 data_in_cache = 0;

static inline void __p_add(struct __data **p, u32 isHead)
{
	if (++(*p) > &__data_array[CACHE_SIZE - 1])
		(*p) = &__data_array[0];
	if (head_p == tail_p) {
		if (isHead == HEAD_ADD) {
			data_in_cache = 0;
		} else {
			data_in_cache = CACHE_SIZE;
		}
	} else {
		data_in_cache = 2;
	}
}

static inline int __adi_write(u32 reg, u16 val, u32 sync)
{
	tail_p->reg = reg;
	tail_p->val = val;
	__p_add(&tail_p, TAIL_ADD);
	while (!FIFO_IS_FULL() && (data_in_cache != 0)) {
		__raw_writel(head_p->val, head_p->reg);
		__p_add(&head_p, HEAD_ADD);
	}

	if (sync || data_in_cache == CACHE_SIZE) {
		__adi_fifo_drain();
		while (data_in_cache != 0) {
			while (FIFO_IS_FULL()) {
				//cpu_relax();
			}
			__raw_writel(head_p->val, head_p->reg);
			__p_add(&head_p, HEAD_ADD);
		}
		__adi_fifo_drain();
	}

	return 0;
}

int sci_adi_write_fast(u32 reg, u16 val, u32 sync)
{
	int ret;

	ret = __check_addr(reg);
	if (ret < 0)
		return ret;

	return __adi_write(reg, val, sync);
}

int sci_adi_write(u32 reg, u16 or_val, u16 clear_msk)
{
	int ret, val;

	ret = __check_addr(reg);
	if (ret < 0)
		return ret;

	val = __adi_read(reg);
	if (val < 0)
		return val;

	return __adi_write(reg, (val & ~clear_msk) | or_val, 1);
}

static void __adi_init(void)
{
	unsigned int value;

	value = VALUE_CH_PRI;
	__raw_writel(value, REG_ADI_CHNL_PRIL);
	__raw_writel(value, REG_ADI_CHNL_PRIH);

	/* for r3p0 */
	readback_addr_mak = 0xffff;
	readback_offset = 2;

	/* 2 line mode */
	value = __raw_readl(REG_ADI_GSSI_CFG1);
	value |= START2LINE_MODE;
	__raw_writel(value, REG_ADI_GSSI_CFG1);

#ifdef ADI_15BIT_MODE
	value = __raw_readl(REG_ADI_GSSI_CFG0);

	/* Set ADI frame length as 32 bits */
	value &= ~GSSI0_FRAME_LEN_MASK;
	value |= GSSI0_FRAME_LEN_VALUE & GSSI0_FRAME_LEN_MASK;

	/* set command length as 16 bits */
	value &= ~(GSSI0_CMD_LEN_MASK << GSSI0_CMD_LEN_OFFSET);
	value |= (GSSI0_CMD_LEN_VALUE & GSSI0_CMD_LEN_MASK) << GSSI0_CMD_LEN_OFFSET;

	__raw_writel(value, REG_ADI_GSSI_CFG0);

	/* set ADI 15 bits address */
	value = __raw_readl(REG_ADI_CTRL0);
	value &= ~(ADI_ADDR_SEL_MASK << ADI_ADDR_SEL_OFFSET);
	value |= (ADI_ADDR_15BIT & ADI_ADDR_SEL_MASK) << ADI_ADDR_SEL_OFFSET;
	__raw_writel(value, REG_ADI_CTRL0);
#endif
}

void sci_adi_init(void)
{
	/* enable adi in global regs */
	CHIP_REG_OR(REG_ADI_EB, BIT_ADI_EB);
	/* reset adi */
	CHIP_REG_OR(REG_ADI_RST, BIT_ADI_SOFT_RST);
	udelay(2);
	CHIP_REG_AND(REG_ADI_RST, (~BIT_ADI_SOFT_RST));

	__adi_init();
}

int adi_hwchannel_set(unsigned int chn, unsigned int config)
{
	u32 val;

	if (chn < 2)
		return -1;

	__raw_writel(config, REG_ADI_CHNL_ADDR(chn));

	if (chn < 32) {
		val = __raw_readl(REG_ADI_CHNL_EN0);
		val |= Bit(chn);
		__raw_writel(val, REG_ADI_CHNL_EN0);
	} else if (chn < HW_CHN_CNT) {
		val = __raw_readl(REG_ADI_CHNL_EN1);
		val |= Bit(chn - 32);
		__raw_writel(val, REG_ADI_CHNL_EN1);
	} else {
		return -1;
	}

	return 0;
}


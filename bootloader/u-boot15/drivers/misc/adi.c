/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 * Copyright (C) 2012 steve zhan
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/**
*For arm read ,delay about 1us when clk_adi runs at 76.8M
*The interface timing is compatible with spi timing
*/

#include <common.h>
#include <asm/io.h>
#include <asm/errno.h>
#include <ubi_uboot.h>
#include <linux/sizes.h>
#include <asm/arch/sprd_reg.h>

#include <asm/arch/common.h>

#ifdef SPRD_MISC_BASE
#undef SPRD_MISC_BASE
#endif
#define SPRD_MISC_BASE SPRD_MISC_PHYS

/* registers definitions for controller CTL_ADI */
#define REG_ADI_CTRL0					(SPRD_MISC_BASE + 0x04)
#if defined(ADI_R1P0_VER) || defined(ADI_R3P0_VER)
#define REG_ADI_CHNL_PRIL				(SPRD_MISC_PHYS + 0x08)
#define REG_ADI_CHNL_PRIH				(SPRD_MISC_PHYS + 0x0C)
#define REG_ADI_INT_RAW					(SPRD_MISC_PHYS + 0x14)
#define REG_ADI_RD_CMD					(SPRD_MISC_PHYS + 0x28)
#define REG_ADI_RD_DATA					(SPRD_MISC_PHYS + 0x2C)
#define REG_ADI_FIFO_STS				(SPRD_MISC_PHYS + 0x30)
#define REG_ADI_GSSI_CFG0                               (SPRD_MISC_PHYS + 0x20)
#define REG_ADI_GSSI_CFG1                               (SPRD_MISC_PHYS + 0x24)
#define REG_ADI_CHNL_EN0				(SPRD_MISC_PHYS + 0x40)
#define REG_ADI_CHNL_EN1				(SPRD_MISC_PHYS + 0x20c)
#define REG_ADI_CHNL_ADDR(id)				(SPRD_MISC_PHYS + 0x44 + (id - 2) * 4)
#define HW_CHN_CNT					50
#else
#define REG_ADI_CHNL_PRIL				(SPRD_MISC_PHYS + 0x08)
#define REG_ADI_INT_RAW					(SPRD_MISC_PHYS + 0x10)
#define REG_ADI_RD_CMD					(SPRD_MISC_PHYS + 0x24)
#define REG_ADI_RD_DATA					(SPRD_MISC_PHYS + 0x28)
#define REG_ADI_FIFO_STS				(SPRD_MISC_PHYS + 0x2C)
#define REG_ADI_GSSI_CFG0                               (SPRD_MISC_PHYS + 0x1C)
#define REG_ADI_GSSI_CFG1                               (SPRD_MISC_PHYS + 0x20)
#endif

/* bits definitions for register REG_ADI_CTRL0 */
#define BIT_ARM_SCLK_EN                 ( BIT_1 )
#define BITS_CMMB_WR_PRI			( (1) << 4 & (BIT_4|BIT_5) )

/* bits definitions for register REG_ADI_CHNL_PRI */
#define BITS_PD_WR_PRI             ( (1) << 14 & (BIT_14|BIT_15) )
#define BITS_RFT_WR_PRI       	   ( (1) << 12 & (BIT_12|BIT_13) )
#define BITS_DSP_RD_PRI            ( (2) << 10 & (BIT_10|BIT_11) )
#define BITS_DSP_WR_PRI            ( (2) << 8 & (BIT_8|BIT_9) )
#define BITS_ARM_RD_PRI            ( (3) << 6 & (BIT_6|BIT_7) )
#define BITS_ARM_WR_PRI            ( (3) << 4 & (BIT_4|BIT_5) )
#define BITS_STC_WR_PRI            ( (1) << 2 & (BIT_2|BIT_3) )
#define BITS_INT_STEAL_PRI         ( (3) << 0 & (BIT_0|BIT_1) )

/* bits definitions for register REG_ADI_RD_DATA */
#define BIT_RD_CMD_BUSY                 ( BIT_31 )
#define SHIFT_RD_ADDR                   ( 16 )

#define SHIFT_RD_VALU                   ( 0 )
#define MASK_RD_VALU                    ( 0xFFFF )

/* bits definitions for register REG_ADI_FIFO_STS */
#define BIT_FIFO_FULL                   ( BIT_11 )
#define FIFO_IS_FULL()	(__raw_readl(REG_ADI_FIFO_STS) & BIT_FIFO_FULL)

#define BIT_FIFO_EMPTY                  ( BIT_10 )

/* special V1 (sc8830 soc) defined */
/* bits definitions for register REG_ADI_CTRL0 */
#define BIT_ADI_WR(_X_)                 ( (_X_) << 2 )
#define BITS_ADDR_BYTE_SEL(_X_)			( (_X_) << 0 & (BIT_0|BIT_1) )

/* bits definitions for register REG_ADI_CHNL_PRI */
#define VALUE_CH_PRI	(0x0)

/* soc defined end*/

static u32 readback_addr_mak = 0;
static u32 readback_offset = 0;
static u8 is_ana_init = 0;

#if defined(CONFIG_NAND_SPL) || defined(CONFIG_FDL1)
#define panic(x...) do{}while(0)
#define printf(x...) do{}while(0)
#define udelay(x)	\
	do { \
		volatile int i; \
		int cnt = 1000 * x; \
		for (i=0; i<cnt; i++);\
	} while(0);
#endif

/*FIXME: Now define adi IP version, sc8825 is zero, sc8830 is one,
* Adi need init early that than read soc id, now using this ARCH dependency.
*/
static inline int __adi_ver(void)
{
	return 1;
}

#define	TO_ADDR(_x_)		( ((_x_) >> SHIFT_RD_ADDR) & readback_addr_mak )

/*FIXME:If we have not hwspinlock , we need use spinlock to do it*/
static inline void __adi_lock(unsigned long *flags, unsigned long *hw_flags)
{
	return;
}

static inline void __adi_unlock(unsigned long *flags, unsigned long *hw_flags)
{
	return;
}

static inline int __adi_fifo_drain(void)
{
#if defined(CONFIG_FPGA)
	return 0;
#else
	int cnt = 1000;
	while (!(__raw_readl(REG_ADI_FIFO_STS) & BIT_FIFO_EMPTY) && cnt--) {
		udelay(1);
	}
	if(cnt < 0) {
		while(1) {
			printf("[0x%s]: ADI READ timeout!!! \n", __func__);
			udelay(1000000);
		}
	}
	return 0;
#endif  /* CONFIG_FPGA */
}

#define ANA_VIRT_BASE			( SPRD_MISC_BASE )
#define ANA_PHYS_BASE			( SPRD_MISC_PHYS )
#define ANA_ADDR_SIZE			( SZ_32K + SZ_4K )
#define ADDR_VERIFY(_X_)	do { \
	BUG_ON((_X_) < SPRD_ADISLAVE_PHYS || (_X_) > (SPRD_ADISLAVE_PHYS + ANA_ADDR_SIZE));} while (0)

static inline u32 __adi_translate_addr(u32 regvddr)
{
	regvddr = regvddr - ANA_VIRT_BASE + ANA_PHYS_BASE;
	return regvddr;
}

static inline int __adi_read(u32 regPddr)
{
	unsigned long val;
	int cnt = 2000;
#if defined(CONFIG_FPGA)
	return 0;
#else
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
		udelay(1);
	} while ((val & BIT_RD_CMD_BUSY) && cnt--);

	if (cnt + 1 <= 0){
		while(1){
			printf("[0x%s]: ADI READ timeout!!! reg = 0x%x, value = 0x%x\n", __func__, regPddr, val);
			udelay(1000000);
		}
	}
	/* val high part should be the address of the last read operation */
	BUG_ON(TO_ADDR(val) != ((regPddr & readback_addr_mak) >> readback_offset));

	return (val & MASK_RD_VALU);
#endif  /* CONFIG_FPGA */
}

int sci_adi_read(u32 reg)
{
	unsigned long val;
	unsigned long flags;
#if defined(CONFIG_FPGA)
	return 0;
#else
	ADDR_VERIFY(reg);
	reg = __adi_translate_addr(reg);
	__adi_lock(&flags, NULL);
	val = __adi_read(reg);
	__adi_unlock(&flags, NULL);
	return val;
#endif  /* CONFIG_FPGA */
}

/*This value have a bit of depending on  real hardware fifo size*/
#define CACHE_SIZE	(16)
static struct __data {
	u32 reg;
	u16 val;
} __data_array[CACHE_SIZE];
struct __data *head_p = &__data_array[0];
struct __data *tail_p = &__data_array[0];
static u32 data_in_cache = 0;
#define HEAD_ADD	(1)
#define TAIL_ADD	(0)
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
#if defined(CONFIG_FPGA)
	return 0;
#else
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
#endif  /* CONFIG_FPGA */
}

int sci_adi_write_fast(u32 reg, u16 val, u32 sync)
{
#if defined(CONFIG_FPGA)
	return 0;
#else
	unsigned long flags;
	ADDR_VERIFY(reg);
	__adi_lock(&flags, NULL);
	__adi_write(reg, val, sync);
	__adi_unlock(&flags, NULL);
	return 0;
#endif  /* CONFIG_FPGA */
}

int sci_adi_write(u32 reg, u16 or_val, u16 clear_msk)
{
	unsigned long flags;
#if defined(CONFIG_FPGA)
	return 0;	
#else
	ADDR_VERIFY(reg);
	__adi_lock(&flags, NULL);
	__adi_write(reg,
		    (__adi_read(__adi_translate_addr(reg)) &
		     ~clear_msk) | or_val, 1);
	__adi_unlock(&flags, NULL);
	return 0;
#endif  /* CONFIG_FPGA */
}

static void __adi_init(void)
{
#if defined(CONFIG_FPGA)
	return;
#else
	u32 value;
	value = __raw_readl(REG_ADI_CTRL0);

	if (__adi_ver() == 0) {
		value &= ~BIT_ARM_SCLK_EN;
		value |= BITS_CMMB_WR_PRI;
		__raw_writel(value, REG_ADI_CTRL0);

		value = __raw_readl(REG_ADI_CHNL_PRIL);
		value |= BITS_PD_WR_PRI | BITS_RFT_WR_PRI |
		    BITS_DSP_RD_PRI | BITS_DSP_WR_PRI |
		    BITS_ARM_RD_PRI | BITS_ARM_WR_PRI |
		    BITS_STC_WR_PRI | BITS_INT_STEAL_PRI;
		__raw_writel(value, REG_ADI_CHNL_PRIL);

		readback_addr_mak = 0x7ff;
	} else if (__adi_ver() == 1) {
		if (value) {
			WARN_ON(1);
		}
		value = VALUE_CH_PRI;
		__raw_writel(value, REG_ADI_CHNL_PRIL);
#if defined(ADI_R1P0_VER) || defined(ADI_R3P0_VER)
		__raw_writel(value, REG_ADI_CHNL_PRIH);
#endif

#ifdef ADI_R3P0_VER
		readback_addr_mak = 0xffff;
		readback_offset = 2;
#else
		value = __raw_readl(REG_ADI_GSSI_CFG0);
		readback_addr_mak = (value & 0x3f) - ((value >> 11) & 0x1f) - 1;
		readback_offset = 0;
#endif
	}
#endif  /* CONFIG_FPGA */
}

void sci_adi_init(void)
{
#if defined(CONFIG_FPGA)
	return;
#else
	if(!is_ana_init) {
		/* enable adi in global regs */
		CHIP_REG_OR(REG_ADI_EB, BIT_ADI_EB);
		__adi_init();

		is_ana_init = 1;
	}
#endif  /* CONFIG_FPGA */
}

int adi_hwchannel_set(unsigned int chn, unsigned int config)
{
	u32 val;

	if (chn < 2)
		return -1;

	__raw_writel(config, REG_ADI_CHNL_ADDR(chn));

	if (chn < 32) {
		val = __raw_readl(REG_ADI_CHNL_EN0);
		val |= BIT(chn);
		__raw_writel(val, REG_ADI_CHNL_EN0);
	} else if (chn < HW_CHN_CNT) {
		val = __raw_readl(REG_ADI_CHNL_EN1);
		val |= BIT(chn - 32);
		__raw_writel(val, REG_ADI_CHNL_EN1);
	} else {
		return -1;
	}

	return 0;
}

/*
 * sci_get_adie_chip_id - read a-die chip id
 *
 * return:
 * the a-die chip id, example: 0x2711A000
 */
u32 sci_get_adie_chip_id(void)
{
#if defined(CONFIG_FPGA)
	return 0;
#else
	u32 chip_id;

	if(!is_ana_init) {
		sci_adi_init();
	}

	chip_id = (sci_adi_read(ANA_REG_GLB_CHIP_ID_HIGH) & 0xffff) << 16;
	chip_id |= sci_adi_read(ANA_REG_GLB_CHIP_ID_LOW) & 0xffff;

	return chip_id;
#endif  /* CONFIG_FPGA */
}


/*
 *  linux/arch/arm/mach-sprd/gpio.c
 *
 *  Generic SPRD GPIO handling
 *
 *  Author:	Yingchun Li(yingchun.li@spreadtrum.com)
 *  Created:	March 10, 2010
 *  Copyright:	Spreadtrum Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */
#include <config.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_eic.h>
#include "adi_hal_internal.h"
#include <asm/arch/common.h>

extern int printf(const char *fmt, ...);

#define KERN_WARNING ""
#define WARN(nmu, fmt...) printf(fmt)
#define WARN_ON(num)
#define BUG_ON(__cond__) if(__cond__) printf("%s line: %d bug on\n",\
					__FUNCTION__, __LINE__)
#define pr_err(fmt...) printf(fmt)
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define pr_debug(fmt...) printf(fmt)

//#define DEBUG


#ifdef DEBUG
#define GPIO_DBG(fmt...) pr_debug(fmt)
#else
#define GPIO_DBG(fmt...)
#endif

struct eic_info{
	u32 base_addr;
	int die;
	u8  bit_num;
};

enum eic_die {
	A_DIE = 0,
	D_DIE = 1,
};

#define GPIO_INVALID_ID	(0xffff)
#define INVALID_REG	(~(u32)0)

#define EIC_DATA 0x00
#define EIC_MASK 0x04
#define EIC_IEV  0x14
#define EIC_IE   0x18
#define EIC_RIS  0x1C
#define EIC_MIS  0x20
#define EIC_IC   0x24
#define EIC_TRIG 0x28

#define EIC0_CTL 0x40
#define EIC1_CTL 0x44
#define EIC2_CTL 0x48
#define EIC3_CTL 0x4C
#define EIC4_CTL 0x50
#define EIC5_CTL 0x54
#define EIC6_CTL 0x58
#define EIC7_CTL 0x5C
#define EIC8_CTL 0x60
#define EIC9_CTL 0x64
#define EIC10_CTL 0x68
#define EIC11_CTL 0x6C
#define EIC12_CTL 0x70

static void __get_eic_base_info (u32 eic_id, struct eic_info *info)
{
	if (eic_id>=SPRD_ADIE_EIC_START && eic_id<=SPRD_ADIE_EIC_END)
	{
		info->base_addr= SPRD_ANA_EIC_PHYS;
		info->bit_num  = eic_id&0xF;
		info->die	   = A_DIE;

	}
#ifndef CONFIG_SPRD_GPIO_PLUS
	else if (eic_id>=SPRD_DDIE_EIC_START && eic_id<=SPRD_DDIE_EIC_END)
	{
		info->base_addr= SPRD_EIC_PHYS;
		info->bit_num  = eic_id&0x7;
		info->die	   = D_DIE;
	}
#ifdef CONFIG_SPRD_EIC_EXT1
	else if (eic_id>=SPRD_DDIE_EIC1_START && eic_id<=SPRD_DDIE_EIC1_END)
	{
		info->base_addr= SPRD_EIC1_PHYS;
		info->bit_num  = eic_id&0x7;
		info->die	   = D_DIE;
	}
#endif
#ifdef CONFIG_SPRD_EIC_EXT2
	else if (eic_id>=SPRD_DDIE_EIC2_START && eic_id<=SPRD_DDIE_EIC2_END)
	{
		info->base_addr= SPRD_EIC2_PHYS;
		info->bit_num  = eic_id&0x7;
		info->die	   = D_DIE;
	}
#endif
#endif
	else
	{
		info->base_addr = INVALID_REG;
	}
}

static int __eic_get_pin_data (struct eic_info *info)
{
	u32 reg_addr = 0, reg_data;

	if (info->base_addr == INVALID_REG)
	{
		return  -1;
	}

	reg_addr = info->base_addr + EIC_DATA;

   	if (info->die == D_DIE)
		reg_data = __raw_readl (reg_addr);
	else
		reg_data = ANA_REG_GET (reg_addr);
	reg_data &= 1<<info->bit_num;

	return reg_data;
}

static int __eic_get_data_mask (struct eic_info *info)
{
	u32 reg_addr = 0, reg_data;

	if (info->base_addr == INVALID_REG)
	{
		return  -1;
	}

	reg_addr = info->base_addr + EIC_MASK;

   	if (info->die == D_DIE)
		reg_data = __raw_readl (reg_addr);
	else
		reg_data = ANA_REG_GET (reg_addr);
	reg_data &= 1<<info->bit_num;

	return reg_data;
}

/*
	set data mask, the gpio data register can be access
 */
static void __eic_set_data_mask (struct eic_info *info, int b_on)
{
	u32 reg_addr = 0, reg_data;

	reg_addr = info->base_addr + EIC_MASK;

	if (info->base_addr == INVALID_REG)
	{
		return;
	}

   	if (info->die == D_DIE)
		reg_data = __raw_readl (reg_addr);
	else
		reg_data = ANA_REG_GET (reg_addr);

	if (b_on)
	{
		if (!(reg_data&(1<<info->bit_num)))
		{
			reg_data |= 1<<info->bit_num;
			if (info->die == D_DIE)
				__raw_writel (reg_data, reg_addr);
			else
				ANA_REG_SET (reg_addr, reg_data);
		}
	}
	else
	{
		if (reg_data&(1<<info->bit_num))
		{
			reg_data &= ~(1<<info->bit_num);
			if (info->die == D_DIE)
				__raw_writel (reg_data, reg_addr);
			else
				ANA_REG_SET (reg_addr, reg_data);
		}
	}
}

int sprd_eic_get(unsigned offset)
{
	unsigned eic_id = offset;
	struct eic_info gpio_info;

	__get_eic_base_info (eic_id, &gpio_info);

	if (!__eic_get_data_mask (&gpio_info)) {
		WARN(1, "GPIO_%d data mask hasn't been opened!\n", eic_id);
	}

	return __eic_get_pin_data (&gpio_info);
}

int sprd_eic_irq_set_type(unsigned offset, unsigned flow_type)
{
        return 0;
}

int sprd_eic_irq_sts(unsigned offset)
{
	return 0;
}

int sprd_eic_request(unsigned offset)
{
	unsigned eic_id = offset;
	struct eic_info gpio_info;

   	__get_eic_base_info (eic_id, &gpio_info);
	__eic_set_data_mask (&gpio_info, 1);
	return 0;
}

static void sprd_eic_free(unsigned offset)
{
	unsigned eic_id = offset;
	struct eic_info gpio_info;

	__get_eic_base_info (eic_id, &gpio_info);
	__eic_set_data_mask (&gpio_info, 0);
	return;
}

void sprd_eic_init(void)
{
#ifdef REG_EIC_EB
	REG32(REG_EIC_EB) |= BIT_EIC_EB;
#else
	REG32(REG_AON_APB_APB_EB0) |= BIT_EIC_EB;
#endif

	REG32(REG_AON_APB_APB_RTC_EB) |= BIT_EIC_RTC_EB|BIT_EIC_RTCDV5_EB;
	ANA_REG_OR(ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_EIC_EN);
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN,    BIT_RTC_EIC_EN);
}


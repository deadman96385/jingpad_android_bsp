/*
 *  linux/arch/arm/mach-sprd/gpio.c
 *
 *  Generic SPRD GPIO handling
 *
 *  Author:	Ya.Zhou
 *  Created:	2017/12/22
 *  Copyright:	Spreadtrum Inc.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */
#include <config.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include "asm_generic_gpio.h"
#include <asm/arch/common.h>
#include <asm/errno.h>

extern int printf(const char *fmt, ...);

#define KERN_WARNING ""
#define WARN_ON(num)
#define BUG_ON(__cond__) if(__cond__) printf("%s line: %d bug on\n", __FUNCTION__, __LINE__)
#define pr_err(fmt...) printf(fmt)
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define pr_debug(fmt...) printf(fmt)

//#define DEBUG_GPIO

#ifdef DEBUG_GPIO
#define GPIO_DBG(fmt...) pr_debug(fmt)
#else
#define GPIO_DBG(fmt...)
#endif

#define INVALID_REG		(~(u32)0)

#define GPIO_DATA	BIT_0
#define GPIO_ODATA	BIT_1
#define GPIO_ENABLE	BIT_2
#define GPIO_DIR	BIT_3

static __inline u32 __get_base_addr (u32 gpio_id)
{
    return (gpio_id * 0x4 + (u32) SPRD_GPIO_PLUS_PHYS);
}

static void __gpio_set_dir (u32 offset, int dir)
{
	int value = !!dir;
	u32 reg_addr = 0;

	reg_addr = __get_base_addr(offset);

	value = __raw_readl(reg_addr);
	if (dir)
		value |= GPIO_DIR;
	else
		value &= ~(GPIO_DIR);
       __raw_writel(value, reg_addr);
}

static int __gpio_get_pin_data (u32 offset)
{
	u32 reg_addr = 0;

	reg_addr = __get_base_addr(offset);

	return (__raw_readl(reg_addr) & GPIO_DATA);
}

static int __gpio_get_data_mask (u32 offset)
{
	u32 reg_addr = 0;
	int value;

	reg_addr = __get_base_addr(offset);
	value = __raw_readl(reg_addr) & GPIO_ENABLE;

	return value ? true : false;
}

static int __gpio_get_dir (u32 offset)
{
	u32 reg_addr = 0;
	int value;

	reg_addr = __get_base_addr(offset);
	value = __raw_readl(reg_addr) & GPIO_DIR;

	return value ? true: false;
}

static void __gpio_set_pin_data (u32 offset, int b_on)
{
	u32 reg_addr;
	int value;

	reg_addr = __get_base_addr(offset);

	value = __raw_readl(reg_addr);
	if (b_on)
		value |= GPIO_DATA;
	else
		value &= ~(GPIO_DATA);
	__raw_writel(value, reg_addr);
}

/*
	set data mask, the gpio data register can be access
 */
static void __gpio_set_data_mask (u32 offset, int b_on)
{
	int value;
	u32 reg_addr;

	reg_addr = __get_base_addr(offset);

	value = __raw_readl(reg_addr);
	if (b_on)
		value |= GPIO_ENABLE;
	else
		value &= ~(GPIO_ENABLE);
	__raw_writel(value, reg_addr);

	return;
}

int sprd_gpio_direction_output(struct gpio_chip *chip,
				u32 offset, int value)
{
	u32 gpio_id = offset;

	__gpio_set_dir(gpio_id, 1);
	__gpio_set_pin_data(gpio_id, value);

	return 0;
}

int sprd_gpio_direction_input(struct gpio_chip *chip,
				u32 offset)
{
	u32 gpio_id = offset;

	__gpio_set_dir(gpio_id, 0);

	return 0;
}

/*
 * Return GPIO level
 */
int sprd_gpio_get(struct gpio_chip *chip, u32 offset)
{
	u32 gpio_id = offset;

	if (!__gpio_get_data_mask (gpio_id)) {
		printf("GPIO_%d data mask hasn't been opened!\n", gpio_id);
	}

	return __gpio_get_pin_data (gpio_id);
}


/*
 * Set output GPIO level
 */
void sprd_gpio_set(struct gpio_chip *chip, u32 offset, int value)
{
	u32 gpio_id = offset;

	if (!__gpio_get_dir (gpio_id)) {
	        printf("GPIO_%d dir wrong!can't set input value", gpio_id);
		return;
	}

	__gpio_set_pin_data (gpio_id, value);

	GPIO_DBG("gpio_%d setting :%x \n", gpio_id, value);
}

int sprd_gpio_request(struct gpio_chip *chip, u32 offset)
{
	u32 gpio_id = offset;

	GPIO_DBG("request gpio_%d\r\n", gpio_id);

	__gpio_set_data_mask (gpio_id, true);

	return 0;
}

static void sprd_gpio_free(struct gpio_chip *chip, u32 offset)
{
	u32 gpio_id = offset;

	if (gpio_id > GPIO_MAX_PIN_NUM) {
		printf("gpio number is too larger:%d\r\n", gpio_id);
		return;
	}

	__gpio_set_data_mask (gpio_id, false);

	return;
}

void sprd_gpio_init(void)
{
	//gpio plus enable and select move to chipram
}

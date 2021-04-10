#ifndef __GPIO_PHY_H__
#define __GPIO_PHY_H__

#include <linux/types.h>

//#include <mach/gpio.h>
//#include <adi_hal_internal.h>
#include <adi.h>
//#define GPIO_DBG(fmt...) printf(fmt)

#define GPIO_MAX_PIN_NUM            271

enum gpio_section_type {
    GPIO_SECTION_GPI = 0x0,
    GPIO_SECTION_GPO,
    GPIO_SECTION_GPIO,
    GPIO_SECTION_INVALID
};


struct gpio_section
{
    u32 page_base;
    u32 page_size;
    enum gpio_section_type  section_type;
};

enum gpio_die {
	A_DIE = 0,
	D_DIE = 1,
};

#define NR_D_DIE_GPIOS 256

/*
	gpio is locate in Digital Die(D die) or Analog Die(A die),
 */
static __inline int __get_gpio_die( u32 gpio)
{
	if (gpio < NR_D_DIE_GPIOS)
		return D_DIE;
	else if (gpio < GPIO_MAX_PIN_NUM)
		return A_DIE;
	else {
		return -1;
	}
}
static __inline u32 __get_base_addr (u32 gpio_id)
{
    return (gpio_id>>4) * 0x80 + (u32) GPIO_BASE;
}

static __inline u32 __get_bit_num (u32 gpio_id)
{
    return (gpio_id & 0xF);
}
static __inline void gpio_reg_set (u32 reg_addr, int die, u32 value)
{
	__raw_writel(value, reg_addr);

    return;
}

static __inline u32 gpio_reg_get (u32 reg_addr, int die)
{
		return __raw_readl (reg_addr);
}
static __inline void gpio_reg_and (u32 reg_addr, int die, u32 value)
{
		__raw_bits_and(value, reg_addr);
}
static __inline void gpio_reg_or (u32 reg_addr, int die, u32 value)
{
		__raw_bits_or(value, reg_addr);
}

struct gpio_section *gpio_get_section_table(u32 * table_size);

#endif


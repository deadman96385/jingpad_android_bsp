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
#include "gpio_reg_v0.h"
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

#include "gpio_phy.h"

//#define DEBUG_GPIO


#ifdef DEBUG_GPIO
#define GPIO_DBG(fmt...) pr_debug(fmt)
#else
#define GPIO_DBG(fmt...)
#endif

#ifndef GPO_TRI
#define GPO_TRI            0xFFFF
#endif

#ifndef GPO_DATA
#define GPO_DATA           0xFFFF
#endif


struct gpio_info{
	enum gpio_section_type gpio_type;
	u32 base_addr;
	int   die;
	u8   bit_num;
};

struct gpio_irq_map {
	unsigned int gpio_id;
	int irq_num;
};

#define GPIO_INVALID_ID 0xffff
#define INVALID_REG		(~(u32)0)

//static struct gpio_irq_map gpio_irq_table[NR_GPIO_IRQS];


static void __get_gpio_base_info (u32 gpio_id, struct gpio_info *info)
{
	int i = 0;
	u32 table_size = 0;
	struct gpio_section  *section_table;

	section_table = gpio_get_section_table (&table_size);
    	BUG_ON((gpio_id >= GPIO_MAX_PIN_NUM) || (table_size <= 0));


    	info->base_addr = __get_base_addr (gpio_id);
	info->bit_num  = __get_bit_num (gpio_id);
	info->die	   = __get_gpio_die(gpio_id);

	for (i = 0; i < table_size; i++) {
		if (section_table[i].page_base == info->base_addr) {
			if (section_table[i].page_size > info->bit_num) {
	            		info->gpio_type = section_table[i].section_type;
	            		return;
	        		}
			break;
	    	}
	}

    info->gpio_type = GPIO_SECTION_INVALID;

    return;
}



static void __gpio_set_dir (struct gpio_info * info, int dir)
{
	int value = !!dir;
	u32 reg_addr = 0;
	unsigned long flags;

	reg_addr = info->base_addr;

	switch (info->gpio_type) {
	case GPIO_SECTION_GPI:
		if (dir) {
		    WARN(1, "cannot set dir output with GPI");
		}
		return;

	case GPIO_SECTION_GPO:
		if (!dir) {
		WARN(1, "cannot set dir input with GPO");
		}
		return;

	case GPIO_SECTION_GPIO:
		reg_addr += GPIO_DIR;
		break;
	case GPIO_SECTION_INVALID:
	default:
		    WARN(1, " the GPIO_ID is Invalid in this chip");
		    return;
	}

	//local_irq_save(flags);
	value = gpio_reg_get(reg_addr, info->die);

	if (dir)
		value |= 1 << info->bit_num;
	else
		value &= ~(1 << info->bit_num);
       gpio_reg_set(reg_addr, info->die, value);

	//local_irq_restore(flags);
}

/*
	get data register's offset
 */
static u32 __gpio_get_data_reg_offs (struct gpio_info *info)
{
	u32 offset_addr;

	switch (info->gpio_type) {
	case GPIO_SECTION_GPI:
	    offset_addr = GPI_DATA;
	    break;
	case GPIO_SECTION_GPO:
	    offset_addr = GPO_DATA;
	    break;
	case GPIO_SECTION_GPIO:
	    offset_addr = GPIO_DATA;
	    break;
	case GPIO_SECTION_INVALID:
	default:
	    pr_err("the GPIO_ID is Invalid in this chip");
	    WARN_ON(1);
	    return INVALID_REG;
	}

	return offset_addr;
}

static int __gpio_get_pin_data (struct gpio_info *info)
{
	u32 offset_addr = 0;
	u32 reg_addr = 0;

	reg_addr = info->base_addr;

	offset_addr = __gpio_get_data_reg_offs (info);

	if (offset_addr != INVALID_REG) {
	   	reg_addr += offset_addr;
	 	return gpio_reg_get(reg_addr, info->die) & (1<<info->bit_num);
	}

	return -EINVAL;
}
static u32 __gpio_get_data_mask_reg_offs (struct gpio_info *info)
{
	u32 offset_addr;

	switch (info->gpio_type) {
       case GPIO_SECTION_GPI:
            offset_addr = GPI_DMSK;
            break;
       case GPIO_SECTION_GPO:
            offset_addr = GPO_TRI;
            break;
       case GPIO_SECTION_GPIO:
            offset_addr = GPIO_DMSK;
            break;
       case GPIO_SECTION_INVALID:
	default:
            pr_err ("the GPIO_ID is Invalid in this chip");
            WARN_ON(1);
            return INVALID_REG;
    }

    return offset_addr;
}

/*
	if the data register can be access, return ture, else return false;
  */
static int __gpio_get_data_mask (struct gpio_info *info)
{
	u32 offset_addr = 0;
	u32 reg_addr = 0;
	int value;

	reg_addr = info->base_addr;

	offset_addr = __gpio_get_data_mask_reg_offs(info);
	if (offset_addr != INVALID_REG) {
		reg_addr += offset_addr;

		GPIO_DBG("gpio_addr %x data mask :%x\r\n", info->base_addr,
			gpio_reg_get(reg_addr, info->die));

		value = gpio_reg_get(reg_addr, info->die);
		return ( value & (1<< info->bit_num)) ? true : false;
	}

	return false;
}

static int __gpio_get_dir (struct gpio_info *info)
{
	u32 reg_addr = 0;
	int value;

	reg_addr = info->base_addr;

	switch (info->gpio_type) {
	case GPIO_SECTION_GPI:
	    return false;

	case GPIO_SECTION_GPO:
	    return true;

	case GPIO_SECTION_GPIO:
	    reg_addr += GPIO_DIR;
	    break;

	case GPIO_SECTION_INVALID:
	default:
//	    pr_warning("[GPIO_DRV]the GPIO_ID is Invalid in this chip");
	    WARN_ON(1);
	    return -EINVAL;
	}

	value = gpio_reg_get(reg_addr, info->die) & (1<< info->bit_num);
	return value ? true: false;
}

static void __gpio_set_pin_data (struct gpio_info *info ,int b_on)
{
	u32 offset_addr;
	u32 reg_addr;
	int value;
	unsigned long flags;

	reg_addr = info->base_addr;

	offset_addr = __gpio_get_data_reg_offs (info);
	if (offset_addr == INVALID_REG)
		return;

	reg_addr += offset_addr;

	//local_irq_save(flags);

	value = gpio_reg_get(reg_addr, info->die);
	if (b_on)
		value |= 1 << info->bit_num;
	else
		value &= ~(1 << info->bit_num);
	gpio_reg_set(reg_addr, info->die, value);
	//local_irq_restore(flags);
}

/*
	set data mask, the gpio data register can be access
 */
static void __gpio_set_data_mask (struct gpio_info *info, int b_on)
{
	int value;
	u32 reg_addr;
	u32 offset_addr;
	unsigned long flags;

	reg_addr = info->base_addr;
	offset_addr = __gpio_get_data_mask_reg_offs(info);
	if (offset_addr != INVALID_REG) {
		reg_addr += offset_addr;

		//local_irq_save(flags);
		value = gpio_reg_get(reg_addr, info->die);
		if (b_on)
			value |= 1 << info->bit_num;
		else
			value &= ~(1 << info->bit_num);
		gpio_reg_set(reg_addr, info->die, value);
		//local_irq_restore(flags);

		GPIO_DBG("After setting gpio_addr %x data mask :%x\r\n", reg_addr,
		gpio_reg_get(reg_addr, info->die));
	}

	return;
}

int sprd_gpio_direction_output(struct gpio_chip *chip,
					unsigned offset, int value)
{
	unsigned gpio_id = offset;
	struct gpio_info gpio_info;

	__get_gpio_base_info (gpio_id, &gpio_info);
	__gpio_set_dir(&gpio_info, 1);
	__gpio_set_pin_data(&gpio_info, value);
	return 0;
}

int sprd_gpio_direction_input(struct gpio_chip *chip, unsigned offset)
{
	unsigned gpio_id = offset;
	struct gpio_info gpio_info;

       __get_gpio_base_info (gpio_id, &gpio_info);
	__gpio_set_dir(&gpio_info, 0);
	return 0;
}

/*
 * Return GPIO level
 */
int sprd_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	unsigned gpio_id = offset;
	struct gpio_info gpio_info;

	__get_gpio_base_info (gpio_id, &gpio_info);

	if (!__gpio_get_data_mask (&gpio_info)) {
		WARN(1, "GPIO_%d data mask hasn't been opened!\n", gpio_id);
	}
	/*
	if (__gpio_get_dir (&gpio_info))
	{
	WARN(1, "[GPIO_DRV]GPIO_GetValue: GPIO_%d should be input port!\n", gpio_id);
	}
	*/
	return __gpio_get_pin_data (&gpio_info);

}


/*
 * Set output GPIO level
 */
void sprd_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct gpio_info gpio_info;
	u32 gpio_id = offset;

	BUG_ON (gpio_id >= GPIO_MAX_PIN_NUM);

	__get_gpio_base_info (gpio_id, &gpio_info);

/*
	if (!__gpio_get_data_mask (&gpio_info))
	{
	    WARN(1, "GPIO_%d data mask no opened!",  gpio_id);
	}
*/

	if (!__gpio_get_dir (&gpio_info)) {
	        WARN(1, "GPIO_%d dir wrong!can't set input value", gpio_id);
		return;
	}

	__gpio_set_pin_data (&gpio_info, value);

	GPIO_DBG("gpio_%d setting :%x \n", gpio_id, value);
}

int sprd_gpio_request(struct gpio_chip *chip, unsigned offset)
{
	unsigned gpio_id = offset;
	struct gpio_info gpio_info;

	GPIO_DBG("request gpio_%d\r\n", gpio_id);
   	__get_gpio_base_info (gpio_id, &gpio_info);

	GPIO_DBG("gpio info, pin is :%d, base addr :%x, bit num :%d, type :%d\r\n", gpio_id,
		gpio_info.base_addr, gpio_info.bit_num, gpio_info.gpio_type);
    GPIO_DBG("ture is %d, false is %d\n", true, false);
	__gpio_set_data_mask (&gpio_info, true);

	return 0;
}

static void sprd_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	unsigned gpio_id = offset;
	struct gpio_info gpio_info;

	if (gpio_id > GPIO_MAX_PIN_NUM) {
		WARN(1, KERN_WARNING"gpio number is too larger:%d\r\n", gpio_id);
		return;
	}

	__get_gpio_base_info (gpio_id, &gpio_info);
	__gpio_set_data_mask (&gpio_info, false);

	return;
}

#if 0
static int sprd_gpio_to_irq(struct gpio_chip *chip, unsigned offset)
{
	int i;

	for (i = 0; i < NR_GPIO_IRQS; i++) {
		if (gpio_irq_table[i].gpio_id == offset)
			break;
	}

	if (i >= NR_GPIO_IRQS)
		return -1;
	return gpio_irq_table[i].irq_num;
}

int irq_to_gpio(unsigned long irq)
{
	 int i;

        for (i = 0; i < NR_GPIO_IRQS; i++) {
                if (gpio_irq_table[i].irq_num == irq)
                        break;
        }

        if (i >= NR_GPIO_IRQS)
                return -1;
        return gpio_irq_table[i].gpio_id;
}
EXPORT_SYMBOL(irq_to_gpio);

static struct gpio_chip sprd_gpio_chip = {
	.label		  = "sc8800s-gpio",
	.direction_input  = sprd_gpio_direction_input,
	.direction_output = sprd_gpio_direction_output,
	.get		  = sprd_gpio_get,
	.set		  = sprd_gpio_set,
	.request 	  = sprd_gpio_request,
	.free		  = sprd_gpio_free,
	.to_irq	= sprd_gpio_to_irq,
	.base		  = 0,
	.ngpio		  = GPIO_MAX_PIN_NUM,
};

static u32 __gpio_get_int_mask_addr (struct gpio_info *info)
{
	u32 offset_addr;

	switch (info->gpio_type) {
	case GPIO_SECTION_GPI:
	    offset_addr = GPI_IE;
	    break;
	case GPIO_SECTION_GPO:
	    WARN(1, "this opretion can not belong to GPO");
	    return INVALID_REG;

	case GPIO_SECTION_GPIO:
	    offset_addr = GPIO_IE;
	    break;

	case GPIO_SECTION_INVALID:
	default:
	    WARN (1, "the GPIO_ID is Invalid in this chip");
	    return INVALID_REG;
	}

	return offset_addr;

}


static void __gpio_enable_irq (struct gpio_info *info)
{
	int value;
	u32 reg_addr;
	u32 offset_addr = 0;
	unsigned long flags;

	reg_addr = info->base_addr;
	offset_addr = __gpio_get_int_mask_addr (info);
	if (offset_addr != INVALID_REG)	{
		reg_addr += offset_addr;
		local_irq_save(flags);
		value = gpio_reg_get(reg_addr, info->die);
		value |= 1 << info->bit_num;
		gpio_reg_set(reg_addr, info->die, value);
		local_irq_restore(flags);
	}

	return;
}

static void __gpio_disable_irq (struct gpio_info *info)
{
	int value;
	u32 reg_addr;
	u32 offset_addr;
	unsigned long flags;

	reg_addr = info->base_addr;
	offset_addr = __gpio_get_int_mask_addr (info);

	if (offset_addr != INVALID_REG) {
		reg_addr += offset_addr;
		local_irq_save(flags);
		value = gpio_reg_get(reg_addr, info->die);
		value &= ~ (1 << info->bit_num);
		gpio_reg_set(reg_addr, info->die, value);
		local_irq_restore(flags);
	}

	return;

}

static void __gpio_clear_irq_status (struct gpio_info *info)
{
	int value;
	u32 reg_addr;
	unsigned long flags;

	reg_addr = info->base_addr;

	switch (info->gpio_type) {
	case GPIO_SECTION_GPI:
	    reg_addr += GPI_IC;
	    break;
	case GPIO_SECTION_GPO:
	    GPIO_DBG("this opretion can not belong to GPO");
	    return;
	case GPIO_SECTION_GPIO:
	    reg_addr += GPIO_IC;
	    break;
	case GPIO_SECTION_INVALID:
	default:
	    GPIO_DBG("the GPIO_ID is Invalid in this chip");
	    WARN_ON(1);
	    return;
	}

	local_irq_save(flags);
	value = gpio_reg_get(reg_addr, info->die);
	value &= ~ (1 << info->bit_num);
	value |= 1 << info->bit_num;
	gpio_reg_set(reg_addr, info->die, value);
}

static int __gpio_get_int_status (struct gpio_info *info)
{
	u32 reg_addr = 0;
	int value;

	reg_addr = info->base_addr;

	switch (info->gpio_type) {
	case GPIO_SECTION_GPI:
		reg_addr += GPI_MIS;
		break;
	case GPIO_SECTION_GPO:
		WARN(1, "The corresponding reg of this GPIO_ID is a GPO! No Intr!");
		return false;

	case GPIO_SECTION_GPIO:
	    reg_addr += GPIO_MIS;
	    break;
	case GPIO_SECTION_INVALID:
	default:
	    WARN(1, "the GPIO_ID is Invalid in this chip");
	    return false;
	}

	value  = gpio_reg_get(reg_addr, info->die);

	return ( value & (1 << info->bit_num)) ? true : false;
}

static void __gpio_set_int_type (struct gpio_info *info, int type)
{
	if (info->gpio_type == GPIO_SECTION_GPI) {
		switch (type) {
		case IRQ_TYPE_LEVEL_HIGH:   // detect high level.
		           gpio_reg_or( (info->base_addr + GPI_IEV), info->die,
		           				(0x1 << info->bit_num));
		            break;

		   case IRQ_TYPE_LEVEL_LOW:    // detect low level.
		          gpio_reg_and( (info->base_addr + GPI_IEV), info->die,
		            				~ (0x1 << info->bit_num));
		            break;

		    case IRQ_TYPE_EDGE_BOTH:    // detect the rising edges and falling edges.
		    case IRQ_TYPE_EDGE_RISING:  // detect the rising edges.
		    case IRQ_TYPE_EDGE_FALLING:
		    default:
		            WARN(1, "The Irq type is invalid for GPI. \n");
		         break;
		    }
	} else if (info->gpio_type == GPIO_SECTION_GPIO) {
			switch (type) {
			case IRQ_TYPE_LEVEL_HIGH:   // detect high level.
				gpio_reg_or( (info->base_addr + GPIO_IS), info->die, (0x1 << info->bit_num));
				gpio_reg_and(info->base_addr + GPIO_IBE, info->die, ~ (0x1 << info->bit_num));
				gpio_reg_or( (info->base_addr + GPIO_IEV), info->die, (0x1 << info->bit_num));
				break;

			case IRQ_TYPE_LEVEL_LOW:    // detect low level.
				gpio_reg_or( (info->base_addr + GPIO_IS), info->die, (0x1 << info->bit_num));
				gpio_reg_and(info->base_addr + GPIO_IBE, info->die, ~ (0x1 << info->bit_num));
				gpio_reg_and( (info->base_addr + GPIO_IEV), info->die, ~(0x1 << info->bit_num));
				break;

			case IRQ_TYPE_EDGE_BOTH:    // detect the rising edges and falling edges.
				gpio_reg_and( (info->base_addr + GPIO_IS), info->die, ~(0x1 << info->bit_num));
				gpio_reg_or(info->base_addr + GPIO_IBE, info->die, (0x1 << info->bit_num));
				gpio_reg_and( (info->base_addr + GPIO_IEV), info->die, ~(0x1 << info->bit_num));
				break;

			case IRQ_TYPE_EDGE_RISING:  // detect the rising edges.
				gpio_reg_and( (info->base_addr + GPIO_IS), info->die, ~(0x1 << info->bit_num));
				gpio_reg_and(info->base_addr + GPIO_IBE, info->die, ~ (0x1 << info->bit_num));
				gpio_reg_or( (info->base_addr + GPIO_IEV), info->die, (0x1 << info->bit_num));
				break;

			case IRQ_TYPE_EDGE_FALLING:
				gpio_reg_and( (info->base_addr + GPIO_IS), info->die, ~(0x1 << info->bit_num));
				gpio_reg_and(info->base_addr + GPIO_IBE, info->die, ~ (0x1 << info->bit_num));
				gpio_reg_and( (info->base_addr + GPIO_IEV), info->die, ~(0x1 << info->bit_num));
				break;
			default:
				WARN(1, "fault irq type \r\n");
				break;
			}
	}      else {
		WARN(1, "the gpio type is Invalid for irq\r\n");
		return;
	}
}

/*
	The GPI module can do handware debouce, the max period is 255ms,
	NOTE:
	if your application need debounce time larger than that, please use software
	timer.
 */
void gpio_set_hw_debounce (unsigned int gpio, u8 period)
{
	u32 reg_addr = 0;
	int value;
	struct gpio_info gpio_info;
	unsigned long flags;

	__get_gpio_base_info (gpio, &gpio_info);
	if (gpio_info.gpio_type != GPIO_SECTION_GPI) {
		WARN(1, "GPIO_%d is not in GPI\r\n", gpio);
		return;
	}

	reg_addr = gpio_info.base_addr;
	reg_addr += (GPI_0CTRL+ (gpio_info.bit_num << 2));

	local_irq_save(flags);
	if (period >= 1) {
		/*
		GPIO_REG_OR (reg_addr, GPI_DEBOUNCE_BIT);
		GPIO_REG_SET (reg_addr, (GPIO_REG32 (reg_addr) & 0xFF00) +debounce_period);
		*/
		gpio_reg_or(reg_addr, gpio_info.die, GPI_DEBOUNCE_BIT);
		value = (gpio_reg_get(reg_addr, gpio_info.die) & 0xFF00) + period;
		gpio_reg_set(reg_addr, gpio_info.die, value);
	} else {// not recommend
		//GPIO_REG_AND (reg_addr, ~GPI_DEBOUNCE_BIT); //bypass mode
		gpio_reg_and(reg_addr, gpio_info.die, ~GPI_DEBOUNCE_BIT);
	}
	local_irq_restore(flags);
}

EXPORT_SYMBOL(gpio_set_hw_debounce);

/*
	generate the trig_start pulse for GPI interrupt;
 */
static void __gpio_trig_detect (struct gpio_info *info)
{
	int value;
	u32 reg_addr = 0;
	unsigned long flags;

	reg_addr = info->base_addr;

	switch (info->gpio_type) {
	case GPIO_SECTION_GPI:
		reg_addr += GPI_TRIG;
		break;

	case GPIO_SECTION_GPO:
	case GPIO_SECTION_GPIO:
		GPIO_DBG("[GPIO_DRV]this opretion can not belong to GPO/GPIO");
		WARN_ON(1);
		return;

	case GPIO_SECTION_INVALID:
	default:
		GPIO_DBG ("[GPIO_DRV]the GPIO_ID is Invalid in this chip");
		WARN_ON(1);
	  	return;
	}

	local_irq_save(flags);

	value = gpio_reg_get(reg_addr, info->die) & ~(1 << info->bit_num);
	value |= 1 << info->bit_num;
	gpio_reg_set(reg_addr, info->die, value);

	local_irq_restore(flags);
	//GPIO_REG_SET (reg_addr, ( (GPIO_REG32 (reg_addr) & ~ (1<<pGpio_info->bit_num)) | (value<<pGpio_info->bit_num)));

}


void gpio_enable_gpi_interupt (struct gpio_info *info)
{

	switch (info->gpio_type) {
	case GPIO_SECTION_GPI:
	    __gpio_enable_irq (info);
	    __gpio_trig_detect (info);
	    break;
	case GPIO_SECTION_GPO:
	case GPIO_SECTION_GPIO:
	    return;

	default:
	   WARN_ON(1);
	    break;
	}
}

//EXPORT_SYMBOL(gpio_enable_gpi_interupt);

static void sprd_ack_gpio_irq(unsigned int irq)
{
	int gpio;
 	struct gpio_irq_map *map= get_irq_chip_data(irq);
	struct gpio_info gpio_info;

	gpio = map->gpio_id;
	if (gpio >= GPIO_MAX_PIN_NUM ) {
		pr_warning(" [%s] error gpio %d\n", __FUNCTION__, gpio);
		return;
	}
	GPIO_DBG("ack irq gpio %d  irq %d", gpio, irq);

	__get_gpio_base_info (gpio, &gpio_info);
	__gpio_clear_irq_status(&gpio_info);
}

static void sprd_mask_gpio_irq(unsigned int irq)
{
	unsigned gpio;
	struct gpio_irq_map *map= get_irq_chip_data(irq);
	struct gpio_info gpio_info;

	gpio = map->gpio_id;
	if (gpio >= GPIO_MAX_PIN_NUM ) {
		pr_warning(" [%s] error gpio %d\n", __func__, gpio);
		return;
	}

	GPIO_DBG("mask gpio %d  irq %d", gpio, irq);
	__get_gpio_base_info (gpio, &gpio_info);
	__gpio_disable_irq (&gpio_info);
}


static void sprd_unmask_gpio_irq(unsigned int irq)
{
	unsigned gpio;
	struct gpio_info gpio_info;
	struct gpio_irq_map *map= get_irq_chip_data(irq);

	gpio = map->gpio_id;
	if (gpio >= GPIO_MAX_PIN_NUM ) {
		pr_warning(" [%s] error gpio %d\n", __FUNCTION__, gpio);
		return;
	}

	GPIO_DBG("unmask gpio %d  irq %d", gpio, irq);
	__get_gpio_base_info (gpio, &gpio_info);
	__gpio_enable_irq (&gpio_info);

	if(gpio_info.gpio_type == GPIO_SECTION_GPI)
		__gpio_trig_detect (&gpio_info);
}


static int sprd_gpio_irq_type(unsigned int irq, unsigned int type)
{
	int gpio;
	struct gpio_irq_map *map= get_irq_chip_data(irq);
	struct gpio_info gpio_info;

	gpio = map->gpio_id;
	if (gpio >= GPIO_MAX_PIN_NUM ) {
		pr_warning(" [%s] error gpio %d\n", __FUNCTION__, gpio);
		return -1;
	}

  	__get_gpio_base_info (gpio, &gpio_info);
	//set irq type
	__gpio_set_int_type(&gpio_info, type);

	if (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		__set_irq_handler_unlocked(irq, handle_level_irq);
	else if (type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		__set_irq_handler_unlocked(irq, handle_edge_irq);
	return 0;
}

static void sprd_disable_gpio_irq(unsigned int irq)
{
	sprd_mask_gpio_irq(irq);
}
static struct irq_chip sprd_muxed_gpio_chip = {
	.name		= "GPIO",
	.ack		= sprd_ack_gpio_irq,
	.mask		= sprd_mask_gpio_irq,
	.unmask		= sprd_unmask_gpio_irq,
	.set_type	= sprd_gpio_irq_type,
	.disable	= sprd_disable_gpio_irq,
};

static  int gpio_get_int_status(unsigned int gpio)
{
   	struct gpio_info gpio_info;

    	__get_gpio_base_info (gpio, &gpio_info);
   	return __gpio_get_int_status (&gpio_info);

}


static void sprd_gpio_demux_handler(unsigned int irq, struct irq_desc *desc)
{
	int i;

	for (i = 0; i < NR_GPIO_IRQS; i++) {
		if (gpio_irq_table[i].gpio_id == GPIO_INVALID_ID) {
		            continue;
        	}
		if (gpio_get_int_status(gpio_irq_table[i].gpio_id)) {
		  	generic_handle_irq(gpio_irq_table[i].irq_num);
		}
	}
}
static void sprd_gpio_irq_init(void)
{
	int irq;
	int i;

	for(i = 0; i < NR_GPIO_IRQS; i++) {
		gpio_irq_table[i].gpio_id= GPIO_INVALID_ID;
	}
	for (irq = GPIO_IRQ_START; irq < (GPIO_IRQ_START + NR_GPIO_IRQS); irq++) {
		set_irq_chip(irq, &sprd_muxed_gpio_chip);
		set_irq_flags(irq, IRQF_VALID | IRQF_PROBE);
	}

	set_irq_chained_handler(IRQ_GPIO_INT, sprd_gpio_demux_handler);
	set_irq_chained_handler(IRQ_ANA_GPIO_INT, sprd_gpio_demux_handler);
}

/*
	allocate an irq for gpio
*/
__must_check int sprd_alloc_gpio_irq(unsigned gpio)
{
	int irq;
	int i;
	struct gpio_info gpio_info;
	unsigned long flags;

	__get_gpio_base_info (gpio, &gpio_info);

	// find a free record
	for (i = 0; i< NR_GPIO_IRQS; i++) {
		if (gpio_irq_table[i].gpio_id == gpio) {
			pr_warning("irq for GPIO_%d has been alloc !\n", gpio);
		   	return -1;
		}
	}

	for(i = 0; i < NR_GPIO_IRQS; i++) {
		if (gpio_irq_table[i].gpio_id == GPIO_INVALID_ID)
			break;
	}

	if (i >= NR_GPIO_IRQS) {
		// No free item in the table.
		return -1;
	}
	local_irq_save(flags);
	irq = GPIO_IRQ_START + i;
	 gpio_irq_table[i].gpio_id = gpio;
	 gpio_irq_table[i].irq_num = irq;

	set_irq_chip_data(irq, &gpio_irq_table[i]);
	local_irq_restore(flags);
	__gpio_clear_irq_status(&gpio_info);
	if (gpio_info.gpio_type == GPIO_SECTION_GPI)
	       __gpio_trig_detect (&gpio_info);

	return irq;
}

EXPORT_SYMBOL(sprd_alloc_gpio_irq);

void sprd_free_gpio_irq(int irq)
{
	int i;
	unsigned long flags;

	local_irq_save(flags);
	for (i = 0; i < NR_GPIO_IRQS; i++) {
		if (gpio_irq_table[i].irq_num == irq) {
			set_irq_chip_data(irq, NULL);
			gpio_irq_table[i].gpio_id = GPIO_INVALID_ID;
			break;
        	}
	}
	local_irq_restore(flags);
}
EXPORT_SYMBOL(sprd_free_gpio_irq);

__init void sprd_gpio_init(void)
{
	//enable gpio bank 0~10, that is, all 176 gpio
	//__raw_writel(0x7fff, GR_GEN2);
	  //CHIP_REG_OR ( (GR_GEN0), (GEN0_GPIO_EN | GEN0_GPIO_RTC_EN));
	  __raw_bits_or (GEN0_GPIO_EN | GEN0_GPIO_RTC_EN, GR_GEN0);
	ANA_REG_OR (ANA_AGEN,AGEN_RTC_GPIO_EN);
	msleep(5);
	ANA_REG_OR (ANA_AGEN,AGEN_GPIO_EN);

	gpiochip_add(&sprd_gpio_chip);

	sprd_gpio_irq_init();
}
#endif
void sprd_gpio_init(void)
{
#if defined(CONFIG_SPX15)
	REG32(REG_AON_APB_APB_EB0) |= BIT_AON_GPIO_EB;
#else
	#ifdef REG_GPIO_EB
		REG32(REG_GPIO_EB) |= BIT_GPIO_EB;
	#else
		REG32(REG_AON_APB_APB_EB0) |= BIT_GPIO_EB;
	#endif

	#if defined(CONFIG_ADIE_SC2713)
		ANA_REG_OR(ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_GPIO_EN);
	#endif
#endif
}

#include <common.h>
#include <config.h>
#include <asm/arch/sprd_reg.h>
#include "gpio_reg_v0.h"
/* delete  chip_drv_common_io_h */
#include <asm/io.h>
#include <asm/arch/pinmap.h>
#include "gpio_phy.h"

//#define DEBUG

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
#define INVALID_REG			(~(u32)0)
#define REG_PIN_GPIO0            	( 0x0258 )
#define REG_PIN_GPIO1		       	( 0x025C )
#define BITS_AF(_x_)                	( ((_x_) << 4) & (BIT_4|BIT_5) )
#define BITS_STR(_x_)			((((_x_) << 18) & (BIT_18|BIT_19))||(((_x_) << 20) & (BIT_20|BIT_21)))//CFIO
#define BIT_SLP_AP                  	( BIT_13 )
#define BIT_NUL                     	( 0 )
#define BIT_SLP_NUL                 	( 0 )
#define BIT_SLP_IE                  	( BIT_1 )


static void __get_gpio_base_info (u32 gpio_id, struct gpio_info *info)
{
	int i = 0;
	u32 table_size = 0;
	struct gpio_section  *section_table;

	section_table = gpio_get_section_table (&table_size);

	info->base_addr = __get_base_addr (gpio_id);
	info->bit_num	= __get_bit_num (gpio_id);
	info->die	= __get_gpio_die(gpio_id);

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

	reg_addr = info->base_addr + GPIO_DIR;

	value = gpio_reg_get(reg_addr, info->die);

	if (dir)
		value |= 1 << info->bit_num;
	else
		value &= ~(1 << info->bit_num);

	gpio_reg_set(reg_addr, info->die, value);
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
	    return INVALID_REG;
	}

	return offset_addr;
}

static int __gpio_get_pin_data (struct gpio_info *info)
{
	u32 offset_addr = 0;
	u32 reg_addr = 0;
	int value;

	reg_addr = info->base_addr;

	offset_addr = __gpio_get_data_reg_offs (info);

	if (offset_addr != INVALID_REG) {
	   	reg_addr += offset_addr;
	 	value = gpio_reg_get(reg_addr, info->die) & (1<<info->bit_num);
		return value ? 1 : 0;
	}

	return -1;
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
		value = gpio_reg_get(reg_addr, info->die);
		return ( value & (1<< info->bit_num)) ? 1 : 0;
	}

	return 0;
}

static int __gpio_get_dir (struct gpio_info *info)
{
	u32 reg_addr = 0;
	int value;

	reg_addr = info->base_addr + GPIO_DIR;
	value = gpio_reg_get(reg_addr, info->die) & (1<< info->bit_num);
	return value ? 1 : 0;
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

	value = gpio_reg_get(reg_addr, info->die);
	if (b_on)
		value |= 1 << info->bit_num;
	else
		value &= ~(1 << info->bit_num);
	gpio_reg_set(reg_addr, info->die, value);
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

		value = gpio_reg_get(reg_addr, info->die);
		if (b_on)
			value |= 1 << info->bit_num;
		else
			value &= ~(1 << info->bit_num);
		gpio_reg_set(reg_addr, info->die, value);
	}

	return;
}

int sprd_gpio_direction_output(unsigned int offset, int value)
{
	unsigned int gpio_id = offset;
	struct gpio_info gpio_info;

	__get_gpio_base_info (gpio_id, &gpio_info);
	__gpio_set_dir(&gpio_info, 1);
	__gpio_set_pin_data (&gpio_info, value);
	return 0;
}

int sprd_gpio_direction_input(unsigned int offset)
{
	unsigned int gpio_id = offset;
	struct gpio_info gpio_info;

	__get_gpio_base_info (gpio_id, &gpio_info);
	__gpio_set_dir(&gpio_info, 0);
	return 0;
}

/*
 * Return GPIO level
 */
int sprd_gpio_get(unsigned int offset)
{
	unsigned int gpio_id = offset;
	struct gpio_info gpio_info;

	__get_gpio_base_info (gpio_id, &gpio_info);

	return __gpio_get_pin_data (&gpio_info);
}


/*
 * Set output GPIO level
 */
void sprd_gpio_set(unsigned int offset, int value)
{
	struct gpio_info gpio_info;
	u32 gpio_id = offset;

	__get_gpio_base_info (gpio_id, &gpio_info);
	__gpio_set_pin_data (&gpio_info, value);
}

int sprd_gpio_request(unsigned int offset)
{
	unsigned int gpio_id = offset;
	struct gpio_info gpio_info;

	__get_gpio_base_info (gpio_id, &gpio_info);
	__gpio_set_data_mask (&gpio_info, 1);

	return 0;
}

void sprd_gpio_free(unsigned int offset)
{
	unsigned int gpio_id = offset;
	struct gpio_info gpio_info;

	__get_gpio_base_info (gpio_id, &gpio_info);
	__gpio_set_data_mask (&gpio_info, 0);

	return;
}

static pinmap_t pinmap[]={
{REG_PIN_GPIO0,		BITS_AF(3)},//gpio87
{REG_PIN_GPIO1,		BITS_AF(3)},//GPIO88
};

int  pin_init(void)
{
	int i;
	for (i = 0; i < sizeof(pinmap)/sizeof(pinmap[0]); i++) {
		__raw_writel(pinmap[i].val, SPRD_PIN_BASE + pinmap[i].reg);
	}

	return 0;
}

void sprd_gpio_init(void)
{
	CHIP_REG_OR(REG_AON_APB_APB_EB0, BIT_AON_APB_GPIO_EB | BIT_AON_APB_PIN_EB);
	pin_init();
}

#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include "gpio_reg_v0.h"
#include "gpio_phy.h"

const static struct gpio_section  s_gpio_section_table[] = {
    {   (SPRD_ANA_GPIO_PHYS + 0*0x80),   0x8,  GPIO_SECTION_GPI   },/*GPIO0-7*/
    {   (SPRD_GPIO_PHYS + 0*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO10-15*/
    {   (SPRD_GPIO_PHYS + 1*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO16-31*/
    {   (SPRD_GPIO_PHYS + 2*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO32-47*/
    {   (SPRD_GPIO_PHYS + 3*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO48-63*/
    {   (SPRD_GPIO_PHYS + 4*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO64-79*/
    {   (SPRD_GPIO_PHYS + 5*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO80-95*/
    {   (SPRD_GPIO_PHYS + 6*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO96-111*/
    {   (SPRD_GPIO_PHYS + 7*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO112-127*/
    {   (SPRD_GPIO_PHYS + 8*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO128-143*/
    {   (SPRD_GPIO_PHYS + 9*0x80),    0x10,    GPIO_SECTION_GPIO  },/*GPIO144-159*/
    {   (SPRD_GPIO_PHYS + 10*0x80),   0x10,    GPIO_SECTION_GPIO  },/*GPIO160-175*/
    {   (SPRD_GPIO_PHYS + 11*0x80),   0x10,    GPIO_SECTION_GPIO  },/*GPIO176-191*/
    {   (SPRD_GPIO_PHYS + 12*0x80),   0x10,    GPIO_SECTION_GPIO  },/*GPIO192-207*/
    {   (SPRD_GPIO_PHYS + 13*0x80),   0x10,    GPIO_SECTION_GPIO  },/*GPIO208-223*/
    {   (SPRD_GPIO_PHYS + 14*0x80),   0x10,    GPIO_SECTION_GPIO  },/*GPIO224-239*/
    {   (SPRD_GPIO_PHYS + 15*0x80),   0x10,    GPIO_SECTION_GPIO  },/*GPIO240-255*/
    {   (SPRD_GPIO_PHYS + 16*0x80),   0x10,    GPIO_SECTION_GPIO  },/*GPIO256-271*/
};

struct gpio_section * gpio_get_section_table (u32 *table_size)
{
    *table_size = ARRAY_SIZE(s_gpio_section_table);

    return (struct gpio_section *) s_gpio_section_table;
}


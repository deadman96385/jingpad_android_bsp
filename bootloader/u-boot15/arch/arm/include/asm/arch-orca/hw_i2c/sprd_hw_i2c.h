#ifndef __ARCH_ARM_ASM_HW_I2C__
#define __ARCH_ARM_ASM_HW_I2C__

#include <asm/arch/sprd_reg.h>

#define USED_CHANNEL_NUM	0

struct hw_i2c_channel {
	unsigned channel_num;
	unsigned addr;
};

struct sprd_hw_i2c {
	void *apb_base;
	unsigned apb_eb;
	void *base;
	int num;
	struct hw_i2c_channel channel[USED_CHANNEL_NUM];
};

#define DVFS_ADDR(DA, RA)		(((DA) << 8 | (RA)) << 2)

#define SPRD_I2C_NUM		1

struct sprd_hw_i2c sprd_hw_i2c[SPRD_I2C_NUM] = {
	{
		.apb_base = (void *)REG_AON_APB_APB_EB2,
		.apb_eb = BIT_AON_APB_I2C_EB,
		.base = (void *)SPRD_AON_PERI_I2C_PHYS,
		.num = USED_CHANNEL_NUM,
	},
};

#endif /*__ARCH_ARM_ASM_HW_I2C__*/


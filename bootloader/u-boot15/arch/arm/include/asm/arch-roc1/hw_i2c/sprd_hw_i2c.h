#ifndef __ARCH_ARM_ASM_HW_I2C__
#define __ARCH_ARM_ASM_HW_I2C__

#include <asm/arch/sprd_reg.h>

#define USED_CHANNEL_NUM	2

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

#define SPRD_I2C_NUM		2

#define	DVFS_I2C0_TX_5_ADDR		DVFS_ADDR(CONFIG_I2C0_DVFS_ADDR, CONFIG_I2C0_DVFS_TX_5_REG_ADDR)
#define	DVFS_I2C0_TX_7_ADDR		DVFS_ADDR(CONFIG_I2C0_DVFS_ADDR, CONFIG_I2C0_DVFS_TX_7_REG_ADDR)

#define	DVFS_I2C1_TX_5_ADDR		DVFS_ADDR(CONFIG_I2C1_DVFS_ADDR, CONFIG_I2C1_DVFS_TX_5_REG_ADDR)
#define	DVFS_I2C1_TX_7_ADDR		DVFS_ADDR(CONFIG_I2C1_DVFS_ADDR, CONFIG_I2C1_DVFS_TX_7_REG_ADDR)

#define	DVFS_TX_5_CHNL		5
#define	DVFS_TX_7_CHNL		7

struct sprd_hw_i2c sprd_hw_i2c[SPRD_I2C_NUM] = {
	{
		.apb_base = (void *)REG_AON_APB_APB_EB2,
		.apb_eb = BIT_AON_APB_I2C0_EB,
		.base = (void *)SPRD_AON_I2C0_PHYS,
		.num = USED_CHANNEL_NUM,
		.channel[0] = {
			.channel_num = DVFS_TX_5_CHNL,
			.addr= DVFS_I2C0_TX_5_ADDR,
		},
		.channel[1] = {
			.channel_num = DVFS_TX_7_CHNL,
			.addr= DVFS_I2C0_TX_7_ADDR,
		},

	},
	{
		.apb_base = (void *)REG_AON_APB_APB_EB1,
		.apb_eb = BIT_AON_APB_I2C1_EB,
		.base = (void *)SPRD_AON_I2C1_PHYS,
		.num = USED_CHANNEL_NUM,
		.channel[0] = {
			.channel_num = DVFS_TX_5_CHNL,
			.addr= DVFS_I2C1_TX_5_ADDR,
		},
		.channel[1] = {
			.channel_num = DVFS_TX_7_CHNL,
			.addr= DVFS_I2C1_TX_7_ADDR,
		},
	},
};

#endif /*__ARCH_ARM_ASM_HW_I2C__*/


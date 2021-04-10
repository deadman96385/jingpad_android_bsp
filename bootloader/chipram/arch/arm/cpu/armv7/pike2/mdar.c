#include <common.h>
#include <sci_types.h>
/* delete  chip_drv_common_io_h */
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>

#define CTL_BASE_MDAR 0x40070000

void mdar_init(void)
{
	uint32 i;
	CHIP_REG_OR(REG_AON_APB_APB_EB1, BIT_AON_APB_MDAR_EB);
	CHIP_REG_OR(REG_AON_APB_CLK_EB0, BIT_AON_APB_RFTI_SBI_EB);
	CHIP_REG_OR(REG_AON_APB_APB_RST1, BIT_AON_APB_MDAR_SOFT_RST);
	CHIP_REG_OR(REG_AON_APB_MDAR_SOFT_RST, BIT_AON_APB_RFTI_SBI_SOFT_RST);
	for(i = 0; i < 100; i++);
	CHIP_REG_AND(REG_AON_APB_APB_RST1, ~BIT_AON_APB_MDAR_SOFT_RST);
	CHIP_REG_AND(REG_AON_APB_MDAR_SOFT_RST, ~BIT_AON_APB_RFTI_SBI_SOFT_RST);
}

void init_rfti_sbi(void)
{
	CHIP_REG_OR(CTL_BASE_MDAR+0x2c, 1<<0);
	CHIP_REG_OR(CTL_BASE_MDAR+0x3c, 1<<1);
	CHIP_REG_OR(CTL_BASE_MDAR+0x30, 1<<2);
	CHIP_REG_OR(CTL_BASE_MDAR+0xf0, 1<<0);
}

void mdar_deinit(void)
{
	CHIP_REG_AND(CTL_BASE_MDAR+0x30, ~(1<<2));
	CHIP_REG_AND(CTL_BASE_MDAR+0xf0, ~0x3);
}

uint32 mdar_sbi1_wr(uint16 addr, uint16 data)
{
	uint32 i;
	uint32 reg_val,reg_val_spi = 0;
	reg_val_spi = (addr << 16) | (data << 0);
	reg_val_spi &= ~(1<<31);
	REG32(CTL_BASE_MDAR +0x240) = reg_val_spi;
	REG32(CTL_BASE_MDAR + 0x244) = 0x1;
	for(i = 0; i < 100; i++);
	do{
		reg_val = CHIP_REG_GET(CTL_BASE_MDAR + 0x248);
	}while(reg_val & (1<<31));
	return 0;
}

void Mdar_rpll_init(void)
{
	mdar_init();
	init_rfti_sbi();
	mdar_sbi1_wr(0x3f73, 0x3);
	mdar_deinit();
}





















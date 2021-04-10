#include "debug.h"
#if (defined DDR_REINIT_TEST) || (defined POWER_TEST) || (defined DFS_SUPPORT)
#include "roc1_common.h"

void reg_bit_set(uint32 addr,uint32 start_bit,uint32 bits_num,uint32 val)
{
	uint32 tmp_val,bit_msk = ((1 << bits_num) - 1);
	tmp_val = REG32(addr);
	tmp_val &= ~(bit_msk << start_bit);
	tmp_val |= ( (val & bit_msk) << start_bit );
	REG32(addr)=tmp_val;
}

uint32 reg_bit_get(uint32 addr,uint32 start_bit,uint32 bits_num)
{
	uint32 tmp_val,bit_msk = ((1 << bits_num) - 1);
	tmp_val = REG32(addr);
	tmp_val &= (bit_msk << start_bit);
	tmp_val = tmp_val >> start_bit;
        return tmp_val;
}


void wait_us(uint32 us)
{
	volatile uint32 i = 0;
	volatile uint32 j  =0;
	volatile uint32 reg = 0;
	for(i=0; i< us; i++)
	{
		for(j=0; j<153; j++)
		{
			reg=REG32(PD_PUB_SYS_CFG);
		}
	}

}

void ddr_phy_eb(uint32 enable)
{
//    reg_bit_set(REG_PMU_APB_DDR_SLEEP_CTRL, 2, 1, enable);
}

void ddr_umctl_eb(uint32 enable)
{
//    reg_bit_set(REG_PMU_APB_DDR_SLEEP_CTRL, 1, 1, enable);
}

void ddr_publ_eb(uint32 enable)
{
//    reg_bit_set(REG_PMU_APB_DDR_SLEEP_CTRL, 0, 1, enable);
}

void pub_sys_clk_force_on(uint32 enable)
{
    ddr_publ_eb(enable);
    ddr_umctl_eb(enable);
    ddr_phy_eb(enable);
}

#endif

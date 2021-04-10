#include "isharkl2_common.h"


struct DFS_INFO_C  lp3_dfs_info[4]=
{
	{230,0,0x3B,0x0,BW_OF(230,30,10),BW_UF(0,20,10)},
	{460,1,0x0f,0x0,BW_OF(460,30,10),BW_UF(230,20,10)},
	{613,2,0x13,0x0,BW_OF(613,30,10),BW_UF(460,20,10)},
	{920,3,0x0b,0x0,BW_OF(920,30,10),BW_UF(613,20,10)}
};

struct IRAM_DDR_REG_INFO  iram_addr_info;
struct DDR_INFO_G  *ddr_info_g;
struct DEBUG_REINIT_INFO_T *reinit_info_g;
struct DEBUG_DFS_INFO_T	*dfs_info_g;
struct DFS_INFO_C *dfs_info_constant=&lp3_dfs_info;

void SCI_DisableIRQ(){}
void SCI_DisableFIQ(){}
void SCI_RestoreFIQ(){}
void SCI_RestoreIRQ(){}
#if 0
void reg_bit_set(uint32 addr,uint32 start_bit,uint32 bits_num,uint32 val)
{
	uint32 tmp_val,bit_msk = ((1 << bits_num) - 1);
	tmp_val = __raw_readl(addr);
	tmp_val &= ~(bit_msk << start_bit);
	tmp_val |= ( (val & bit_msk) << start_bit );
	__raw_writel(addr,tmp_val);
}

uint32 reg_bit_get(uint32 addr,uint32 start_bit,uint32 bits_num)
{
	uint32 tmp_val,bit_msk = ((1 << bits_num) - 1);
	tmp_val = __raw_readl(addr);
	tmp_val &= (bit_msk << start_bit);
	tmp_val = tmp_val >> start_bit;
        return tmp_val;
}
#endif
#if 0
void wait_us(uint32 us)
{
	volatile uint32 i = 0;
	volatile uint32 j  =0;
	volatile uint32 reg = 0;
	for(i=0; i< us; i++)
	{
		for(j=0; j<153; j++)
		{
			reg=REG32(PD_PUB0_SYS_PWR_CFG);
		}
	}

}
#endif
void ddr_umctl_eb_en(uint32 enable)
{
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 0, 1, enable); //ddr0_umctl_eb
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 1, 1, enable);//ddr0_phy_eb
}

void pub_auto_lsleep_cfg(uint32 enable)
{
	reg_bit_set(PMU_APB_PUB0_SYS_SLEEP_CTRL, 4, 1, enable);
}

void master_dll_obs_clear()
{
	uint32 slice_num=0;
	for(slice_num=0;slice_num<4;slice_num++)
	{
		reg_bit_set(CANDS_PHY0_(35)+slice_num*0x200,26, 1,0x1);
	}
}

uint32 sys_sleep_dis()
{
	uint32 ret=0;
	uint32 ack_value=0;
	reg_bit_set(PUB0_SYS_SLEEP_CTRL,6,1,1);//ddr0_sleep_disable
	wait_us(1);
	ack_value=(REG32(PUB0_SYS_SLEEP_CTRL)&(0x1<<7));
	if(ack_value)
	{
		reg_bit_set(PUB0_SYS_SLEEP_CTRL,6,1,0);//ddr0_sleep_disable
		ret = 1;
	}else
	{
		ret =0 ;
	}
	return ret;
}

void sys_sleep_en()
{
	reg_bit_set(PUB0_SYS_SLEEP_CTRL,6,1,0);//ddr0_sleep_disable
}

uint32 pub_umctl_eb_lock()
{
	SCI_DisableIRQ();
	SCI_DisableFIQ();

	if(1==ddr_info_g->sleep_flag)
	{
		SCI_RestoreFIQ();
		SCI_RestoreIRQ();
		return 0;
	}else
	{
		ddr_umctl_eb_en(0x1);
		pub_auto_lsleep_cfg(0x1);
	}
	return 1;
}

void pub_umctl_eb_unlock()
{
	if(0==ddr_info_g->sleep_flag)
	{
		ddr_umctl_eb_en(0x1);
		pub_auto_lsleep_cfg(0x1);
	}
	SCI_RestoreFIQ();
	SCI_RestoreIRQ();
}

void ddr_iram_addr_init(struct IRAM_DDR_REG_INFO *debug_addr_info)
{
	uint32 freq_num=0;
	uint32 reg_sec_num=0;
	debug_addr_info->ddr_info=PARA_SAVE_ADDRESS;
	debug_addr_info->debug_reinit_info=PARA_SAVE_ADDRESS+DDR_INFO_SAVE_SIZE*4;
	debug_addr_info->debug_dfs_info=debug_addr_info->debug_reinit_info+DEBUG_REINIT_SAVE_SIZE*4;
	debug_addr_info->ctl_reg=debug_addr_info->debug_dfs_info+DEBUG_DFS_SAVE_SIZE*4;
	debug_addr_info->pi_reg=debug_addr_info->ctl_reg+CTL0_REG_SAVE_SIZE*4;
	for(freq_num=0;freq_num<4;freq_num++)
	{
		if(freq_num==0)
		{
			debug_addr_info->phy_reg[freq_num][0]=debug_addr_info->pi_reg+PI0_REG_SAVE_SIZE*4;
		}else
		{
			debug_addr_info->phy_reg[freq_num][0]=debug_addr_info->phy_reg[freq_num-1][8]+PHY0_REG2_SAVE_SIZE*4;
		}
		debug_addr_info->phy_reg[freq_num][1]=debug_addr_info->phy_reg[freq_num][0]+PHY0_REG0_SAVE_SIZE*4;
		debug_addr_info->phy_reg[freq_num][2]=debug_addr_info->phy_reg[freq_num][1]+PHY0_REG1_SAVE_SIZE*4;
		debug_addr_info->phy_reg[freq_num][3]=debug_addr_info->phy_reg[freq_num][2]+PHY0_REG1_SAVE_SIZE*4;
		debug_addr_info->phy_reg[freq_num][4]=debug_addr_info->phy_reg[freq_num][3]+PHY0_REG1_SAVE_SIZE*4;
		debug_addr_info->phy_reg[freq_num][5]=debug_addr_info->phy_reg[freq_num][4]+PHY0_REG1_SAVE_SIZE*4;
		debug_addr_info->phy_reg[freq_num][6]=debug_addr_info->phy_reg[freq_num][5]+PHY0_REG2_SAVE_SIZE*4;
		debug_addr_info->phy_reg[freq_num][7]=debug_addr_info->phy_reg[freq_num][6]+PHY0_REG2_SAVE_SIZE*4;
		debug_addr_info->phy_reg[freq_num][8]=debug_addr_info->phy_reg[freq_num][7]+PHY0_REG2_SAVE_SIZE*4;
	}
	ddr_info_g=debug_addr_info->ddr_info;
	reinit_info_g=debug_addr_info->debug_reinit_info;
	dfs_info_g=debug_addr_info->debug_dfs_info;

}


//
uint32 cm4_bist_test(uint32 port_num,uint32 bist_addr,uint32 bist_len)
{

	volatile uint32 i=0;
	uint32 bist_timeout=0;
	uint32 bist_base_offset=0;
	uint32 bist_adr_base=0;
	uint32 bist_result=0;

	REG32(0xc0018028) =0x2a;

	for(i=0;i<port_num;i++)
	{
		bist_base_offset = i*0x4000;
		bist_adr_base = i*0x20000000+bist_addr;
		REG32(0xc00d0000+bist_base_offset) =0x30021b1;
		REG32(0xc00d0004+bist_base_offset) =bist_len;
		REG32(0xc00d0008+bist_base_offset) =bist_adr_base;
		REG32(0xc00d000c+bist_base_offset) =0x0;
		REG32(0xc00d0010+bist_base_offset) =0x0ff0c3a5;
		REG32(0xc00d0014+bist_base_offset) =0xffffaa55;
		REG32(0xc00d0018+bist_base_offset) =0x1111aa55;
		REG32(0xc00d001c+bist_base_offset) =0xaaaaaa55;
		REG32(0xc00d0020+bist_base_offset) =0x1234aa55;
		REG32(0xc00d0024+bist_base_offset) =0x0000aa55;
		REG32(0xc00d0028+bist_base_offset) =0x00000000;
		REG32(0xc00d002c+bist_base_offset) =0x00000000;

		REG32(0xc00d0008+bist_base_offset) =bist_adr_base;
		REG32(0xc00d0004+bist_base_offset) =bist_len;
		REG32(0xc00d0000+bist_base_offset) =0x30021b5;
	}

	for(i=0;i<port_num;i++)
	{
		bist_base_offset = i*0x4000;
		REG32(0xc00d0000+bist_base_offset) =0x30021b3;
	}

	for(i=0;i<port_num;i++)
	{
		while((REG32(0xc00d00b0+i*0x4000) & 0x2) != 0x2);
		((REG32(0xc00d00b0+i*0x4000) & 0x1) == 0x1)?(bist_result+=1):(bist_result+=0);
	}

	REG32(0xc0018028) =0x0;

	return bist_result;
}


void subsys_bus_clk_div_cfg(uint32 freq_num)
{
	uint32 div=0x0;
	switch(freq_num)
	{
		case 0:
			(LPDDR3==ddr_info_g->ddr_type)? (div=0x0):(div=0x0);
			break;
		case 1:
			(LPDDR3==ddr_info_g->ddr_type)?(div=0x1):(div=0x0);
			break;
		case 2:
			(LPDDR3==ddr_info_g->ddr_type)? (div=0x1):(div=0x0);
			break;
		case 3:
			(LPDDR3==ddr_info_g->ddr_type)? (div=0x6):(div=0x0);
			break;
		default:while(1);
	}
	reg_bit_set(PUB0_APB_CGM_MCTRL_DIV,0,3,div);
}



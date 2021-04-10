#include "isharkl2_common.h"
#include "isharkl2_dfi_bm.h"
#include "isharkl2_ddr_dfs.h"


static uint32 seed;

#ifdef DEBUG_DFS_TEST
uint32 dfs_num_g=0;


void SetSeed(uint32 s)
{
	if(s==0)
	{
		seed=-1;
	}else
	{
		seed =s;
	}
}

uint32 GetRandom()
{
	uint32 d;
	d= ((seed>>3)^seed)&0x1ffffffe;
	seed=(seed>>29)| d<<2;
	d=((seed>>3)^seed)&0xf;
	seed>>=3;
	seed |= d<<28;
	return seed;
}
#endif
uint32 find_curr_freq_num()
{
	uint32 freq_div=0;
	uint32 ratio=0;
	uint32 freq_num=4;
	uint32 num=0;
	freq_div=(REG32(AON_APB_CGM_CFG)>>8)&0x7f;

	for(num=0;num<DFS_FREQ_NUM;num++)
	{
		ratio=(dfs_info_constant+num)->ratio;
		if(ratio==freq_div)
		{
			freq_num=num;
			break;
		}
	}
	if(freq_num>=4)
	{
		return 4;
	}
	return freq_num;
}

uint32 find_freq_num(uint32 freq_clk)
{
	uint32 freq_num=DFS_FREQ_NUM;
	uint32 i=0;
	for(i=0;i<DFS_FREQ_NUM;i++)
	{
		if(freq_clk==(dfs_info_constant+i)->freq_clk)
		{
			freq_num=((dfs_info_constant+i)->freq_num);
			break;
		}

	}
	return freq_num;
}


void dfs_training_dis()
{
	reg_bit_set(CANDS_PI0_(1), 8, 1,0x0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(77), 8, 2,0x0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(123), 8, 2,0x0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(129),24, 1,0x0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(99),16, 2,0x0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(99),24, 2,0x0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(147),24, 1,0x0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(155), 16, 2,0x0); //pi_init_lvl_en

}

void ddr_hsoft_dfs_cfg(uint32 freq_num)
{
	uint32 ratio,scan_ratio;
	uint32 target_freq_n;
	if(ddr_info_g->support_freq_num<=0)
	{
		return;
	}
	ratio=(dfs_info_constant+freq_num)->ratio;
	scan_ratio=(dfs_info_constant+freq_num)->scan_ratio;
	reg_bit_set(CANDS_CTL0_(151),16,4,0x0);
	reg_bit_set(PUB0_SOFT_DFS_CTRL,0,1,1);
	reg_bit_set(PUB0_SOFT_DFS_CTRL,1,1,0);
	reg_bit_set(PUB0_SOFT_DFS_CTRL,4,2,freq_num);
	//pub_dfs_sw_ratio
	reg_bit_set(PUB0_SOFT_DFS_CTRL,6,7,ratio);
	//emc_ckg_sel_delay
	reg_bit_set(PUB0_SOFT_DFS_CTRL,20,3,0x1);
	//pub_dfs_sw_switch_period
	reg_bit_set(PUB0_SOFT_DFS_CTRL,23,8,0x30);
}

void ddr_dfs_trigger()
{
	reg_bit_set(PUB0_SOFT_DFS_CTRL,1,1,0);
	reg_bit_set(PUB0_SOFT_DFS_CTRL,1,1,1);
	//check whether mc has entered into selfresh or not
	while((REG32(PUB0_SOFT_DFS_CTRL)&0x4) != 0x4);
	while((REG32(PUB0_SOFT_DFS_CTRL)&0x8) != 0x0);//wait dfs ack flag
	//clear dfs trigger
	reg_bit_set(PUB0_SOFT_DFS_CTRL,1,1,0);
}

uint32 ddr_dfs(uint32 freq_n)
{
	uint32 dfs_freq_num=0;
	dfs_training_dis();
	switch(freq_n)
	{
		case 0:
			dfs_freq_num=0;
			dfs_info_g->dfs_f0_counter++;
			break;
		case 1:
			dfs_freq_num=1;
			dfs_info_g->dfs_f1_counter++;
			break;
		case 2:
			dfs_freq_num=2;
			dfs_info_g->dfs_f2_counter++;
			break;
		case 3:
			dfs_freq_num=3;
			dfs_info_g->dfs_f3_counter++;
			break;
		default:while(1);
	}
	ddr_hsoft_dfs_cfg(dfs_freq_num);
	ddr_dfs_trigger();
	__ddr_print("\r\nddr dfs to frequency:");
	ddr_print_u32_hex(dfs_freq_num);	
}

void ddr_dfs_reg_cfg()
{
	uint32 clk_sel_current,clk_dmc0_sel,clk_dmc0_2x_div,clk_dmc0_1x_div,pub_dfs_sw_ratio;
	clk_sel_current=(REG32(AON_APB_CGM_CFG)>>8)&0x7f;
	clk_dmc0_sel=clk_sel_current&0x3;
	clk_dmc0_2x_div=(clk_sel_current>>3)&0xf;
	clk_dmc0_1x_div=(clk_sel_current>>2)&0x1;
	pub_dfs_sw_ratio=(clk_dmc0_sel<<0) | (clk_dmc0_1x_div<<2) | (clk_dmc0_2x_div<<3);

	//pwrup_srefresh_exit
	reg_bit_set(CANDS_CTL0_(102),16,1,0x1);

	//dfs_soft_mode
	reg_bit_set(PUB0_LP_GEN_CTRL,6,1,1);
	//pub0_dfs_sw_switch_period used to control the time between dfs_fc_req and dfs_fc_ack
	reg_bit_set(PUB0_SOFT_DFS_CTRL,23,8,0x30);

	reg_bit_set(AON_APB_PUB_FC_CTRL,0,8,0xff);
	reg_bit_set(AON_APB_PUB_FC_CTRL,8,2,0x3);

	reg_bit_set(AON_APB_PUB_CTRL,0,7,pub_dfs_sw_ratio);

	reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,19,1,0x1);
	//
	reg_bit_set(AON_APB_CGM_CFG,7,1,0x1);

}

enum BM_INT_STATUS_E dfs_req_check(uint32 source)
{
	if(DFI_BM_REQ == source)
	{
		if(0==ddr_info_g->sleep_flag)
		{
			#ifdef DEBUG_DFS_TEST
			if(dfs_num_g>ddr_info_g->freq_num)
			{
				return UP_FREQ;
			}else
			{
				return DOWN_FREQ;
			}
			#else
			if(REG32(PUB0_DFS_BUSMON_INT_STATUS)&0x4)
			{
				return UP_FREQ;
			}
			if(REG32(PUB0_DFS_BUSMON_INT_STATUS)&0x1)
			{
				return DOWN_FREQ;
			}
			#endif
		}
	}

}

void bm_uf_int_close()
{
	uint32 freq_num=find_freq_num(ddr_info_g->ddr_clk);
	uint32 current_freq_num=find_curr_freq_num();
	if(CHANGE_LOWEST != ddr_info_g->dfs_mode)
	{
		return;
	}
	if(freq_num==current_freq_num)
	{
		dfi_bm_uf_int_set(DISABLE);
	}else if(freq_num < current_freq_num)
	{
		dfi_bm_uf_int_set(ENABLE);
	}else
	{

	}
}


void dfs_info_init()
{
	if(((REG32(PWR_STATE_DBG2)&(0x1f<<15))>>15)==0x0)
	{
		ddr_info_g->sleep_flag=0;
	}else
	{
		ddr_info_g->sleep_flag=1;
	}

	if(CANDS_CTL0_(292)&(0x1<<4))
	{
		ddr_info_g->init_done=1;
	}else
	{
		ddr_info_g->init_done=0;
	}

	if(LPDDR3==ddr_info_g->ddr_type)
	{
		dfs_info_constant=&lp3_dfs_info;
	}else
	{

	}
	ddr_info_g->dfs_freq_en=0xf;
}

void dfs_debug_info_init()
{
	dfs_info_g->dfs_freq_en=0xf;
	dfs_info_g->dfs_f0_counter=0x0;
	dfs_info_g->dfs_f1_counter=0x0;
	dfs_info_g->dfs_f2_counter=0x0;
	dfs_info_g->dfs_f3_counter=0x0;
	dfs_info_g->dfs_step=0x0;
	dfs_info_g->dfi_bm_step=0x0;
	dfs_info_g->dfs_total_times=0x0;
	dfs_info_g->dfs_sw_times=0x0;

}

void dfs_init()
{
	volatile uint32 i=0;
	dfs_info_init();
	dfs_debug_info_init();
	if(LPDDR4==ddr_info_g->ddr_type)
	{
		ddr_info_g->dfs_mode=CHANGE_LOWEST;
		if(ddr_info_g->init_done)
		{
			ddr_dfs_reg_cfg();
			dfs_training_dis();
		}
	}else
	{
		ddr_info_g->dfs_mode=CHANGE_LOWEST;
		if(ddr_info_g->init_done)
		{
			ddr_dfs_reg_cfg();
			dfs_training_dis();
		}
	}

}

uint32 dfs_freq_set(uint32 current_freq_num,enum DFS_STATUS_E dfs_status)
{
	uint32 target_freq_num=current_freq_num;
	uint32 freq_num=find_freq_num(ddr_info_g->ddr_clk);
	if(DFS_UP==dfs_status)
	{
		if(current_freq_num==3)
		{
			target_freq_num=3;
		}else
		{
			target_freq_num += 1;
		}
	}else if(DFS_DOWN==dfs_status)
	{
		if(current_freq_num==0)
		{
			target_freq_num=0;
		}else
		{
			target_freq_num -= 1;
		}
	}
	switch(ddr_info_g->dfs_mode)
	{
		case CHANGE_LOWEST:
			if((DFS_DOWN==dfs_status)&&(target_freq_num<freq_num))
			{
				target_freq_num=freq_num;
			}
			break;
		case CHANGE_HIGHEST:
			if((DFS_UP==dfs_status)&&(target_freq_num>freq_num))
			{
				target_freq_num=freq_num;
			}
			break;
		default:while(1);
	}
	return current_freq_num;
}

void no_dfs_sys_set(uint32 source)
{
	//busmonitor underflow interrupt set
	bm_uf_int_close();
	if(DFI_BM_REQ==source)
	{
		dfi_bm_int_clear();
	}
	sys_sleep_en();
}

uint32 ddr_dfs_go(uint32 source , enum DFS_STATUS_E dfs_status)
{
	uint32 curr_freq_num=0;
	uint32 dfs_freq_num=0;
	uint32 old_freq_num=0;
	if(sys_sleep_dis())
	{
		dfi_bm_int_clear();
	}
	curr_freq_num=find_curr_freq_num();
	old_freq_num=curr_freq_num;
	if(curr_freq_num>=DFS_FREQ_NUM)
	{
		no_dfs_sys_set(source);
		return;
	}

	#ifdef DEBUG_DFS_TEST
	dfs_freq_num=dfs_num_g;
	#else
	if(DFI_BM_REQ==source)
	{
		dfs_freq_num=dfs_freq_set(ddr_info_g->ddr_clk, dfs_status);
	}else if(SW_MAILBOX_REQ ==source)
	{
		dfs_freq_num=find_freq_num(ddr_info_g->ddr_clk);
	}
	#endif

	if(curr_freq_num==dfs_freq_num)
	{
		no_dfs_sys_set(source);
		return;
	}

	if(dfs_freq_num > old_freq_num)
	{
		subsys_bus_clk_div_cfg(dfs_freq_num);
	}
	ddr_dfs(dfs_freq_num);
	curr_freq_num=find_curr_freq_num();
	//
	if(dfs_freq_num != curr_freq_num)
	{
		subsys_bus_clk_div_cfg(curr_freq_num);
		no_dfs_sys_set(source);
		return;
	}
	//
	if(dfs_freq_num<old_freq_num)
	{
		subsys_bus_clk_div_cfg(dfs_freq_num);
	}
}


void dfs_f(uint32 source)
{
	enum BM_INT_STATUS_E bm_int_mode=0;
	if(DFI_BM_REQ==source)
	{
		//check busmonitor underflow/upflow interrupt status
		bm_int_mode=dfs_req_check(source);
		switch(bm_int_mode)
		{
			case UP_FREQ:
				ddr_dfs_go(source, DFS_UP);
				break;
			case DOWN_FREQ:
				ddr_dfs_go(source, DFS_DOWN);
				break;

		}

	}else if(SW_MAILBOX_REQ == source)
	{
		if(0==ddr_info_g->sleep_flag)
		{
			ddr_dfs_go(source, DFS_UP);
		}
	}


}

#ifdef DEBUG_DFS_TEST
void dfs_test()
{
	uint32 count=0;
	dfs_init();
	SetSeed(0);
	while(1)
	{
		dfs_num_g=(count%4);
		dfs_f(DFI_BM_REQ);
		ddr_test();
		count=GetRandom();
	}

}
#endif






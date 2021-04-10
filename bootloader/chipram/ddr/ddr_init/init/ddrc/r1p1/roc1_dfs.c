#include "roc1_dfs.h"
#include "dfs_para.h"


DFS_PARA **g_dfs_para;

//uint32 dfs_valid_frq[]={256,384,667,768,1024,1333,1536,1866};
uint32 dfs_valid_frq[]={256,384,667,768,1024,1333,1536};//};
typedef struct
{
	uint64 dfs_time_total;
	uint32 dfs_time[8];
}DFS_DBG_INFO;
DFS_DBG_INFO dfs_debug_info = {0};
uint32 freq_to_sel(uint32 freq)
{
	int i;
	for  (i=0; i<DFS_SEL; i++)
	{
		if (freq == g_dfs_para[i]->freq) {
			return i;
		}
	}
	return (uint32)(-1);
}

static uint32 sel_to_freq(uint32 sel)
{
	return g_dfs_para[sel]->freq;
}

static void get_dfs_para(uint32 sel, uint32* ratio,uint32* clk_mode, uint32* ratio_d2,uint32* ddl_adjs)
{

	*ratio = g_dfs_para[sel]->ratio;
	*clk_mode = g_dfs_para[sel]->clk_mode;
	*ratio_d2 = g_dfs_para[sel]->ratio_d2;
	*ddl_adjs = 0x16;

}

uint32 get_sel()
{
	return (REG32(REG_CUR_FREQ)  &  0xF00) >> 8;
}

static uint32 get_freq()
{
	uint32 sel;
	sel = get_sel();
	return g_dfs_para[sel]->freq;
}

static uint32 ddr_lightsleep_shut(void)
{
	uint32 acc_value = 0;

	reg_bits_set(DDR_SLEEP_DISABLE, 17, 1, 1);
	dmc_sprd_delay(1);
	return (REG32(REG_PMU_ACC_READY)&(0x1));
}

static void ddr_lightsleep_open(void)
{
	reg_bits_set(DDR_SLEEP_DISABLE, 17, 1, 0);
}
//sw mode
void sw_dfs_mode()
{
	reg_bits_set(REG_DFS_HW_CTRL,0,1,0);
	reg_bits_set(REG_DMC_CLK_INIT_CFG,0,1,1);
	reg_bits_set(REG_DFS_PURE_SW_CTRL,0,1,1);
	reg_bits_set(REG_DFS_SW_CTRL,0,1,1);
}

uint32 sw_dfs_go(uint32 dfs_point)
{
	uint32 sw_ratio;
	uint32 sw_clk_mode;
	uint32 sw_ratio_d2;
	uint32 sw_ddl_adjs;

	uint32 sel;

	sel = freq_to_sel(dfs_point);
	if(sel == (uint32)(-1))
		return DFS_FAIL;

	//need light reg
//	if (!ddr_lightsleep_shut()) {
//		ddr_lightsleep_open();
//		return DFS_FAIL;
//	}

	get_dfs_para(sel,&sw_ratio,&sw_clk_mode,&sw_ratio_d2,&sw_ddl_adjs);

	reg_bits_set(REG_DFS_SW_CTRL,8,7,sw_ratio);
	reg_bits_set(REG_DFS_SW_CTRL,15,7,sw_ratio);


	reg_bits_set(REG_DFS_SW_CTRL1,16,2,sw_clk_mode);
	reg_bits_set(REG_DFS_SW_CTRL1,18,2,sw_clk_mode);

	reg_bits_set(REG_DFS_SW_CTRL2,0,9,sw_ddl_adjs);
	reg_bits_set(REG_DFS_SW_CTRL2,16,9,sw_ddl_adjs);

	reg_bits_set(REG_DFS_SW_CTRL1,0,4,sw_ratio_d2);
	reg_bits_set(REG_DFS_SW_CTRL1,8,4,sw_ratio_d2);

	reg_bits_set(REG_DFS_SW_CTRL,4,3,sel);

	reg_bits_set(REG_DFS_SW_CTRL,1,1,1);
	while(0 == (REG32(REG_DFS_SW_CTRL)&0x4));
	reg_bits_set(REG_DFS_SW_CTRL,1,1,0);

	ddr_lightsleep_open();
	return DFS_SUCCESS;
}



//init
uint32 dfs_init()
{
	uint32 i = 0;
	uint32 array_size = 0;
	char s_tmp[11] = {0};
	g_dfs_para = dfs_para_init	;
	//dfs open
	reg_bits_set(REG_CUR_FREQ,0,1,1);
	//sw mode
	sw_dfs_mode();
	array_size = sizeof(dfs_valid_frq)/sizeof(uint32);
#if 0
	while(1)
	{
		for(i = 0; i < array_size; i++)
		{
			ddrc_print_debug("DFS to ");
			ddrc_print_debug(itoa_simple((dfs_valid_frq[i]), s_tmp, 10));
			ddrc_print_debug(" start.\r\n");
			sw_dfs_go(dfs_valid_frq[i]);
			dmc_ddr_test(0);
			dfs_debug_info.dfs_time_total++;
			ddrc_print_debug("DFS total time: ");
			ddrc_print_debug(itoa_simple(dfs_debug_info.dfs_time_total, s_tmp, 10));
			ddrc_print_debug(" \r\n");
			dfs_debug_info.dfs_time[i]++;
//			dmc_sprd_delay(100);
		}
	}
#endif
	return 0;
}


#include "debug.h"
#ifdef DFS_SUPPORT
#include "sharkl3_dfs.h"


uint32 g_dfs_table[DFS_SEL] = {160, 233, 311, 400, 533, 622, 800, 933};

//support
static uint32 freq_to_sel(uint32 freq)
{
	int i;
	for  (i=0; i<DFS_SEL; i++)
	{
		if (freq == g_dfs_table[i]) {
			return i;
		}
	}
	return (uint32)(-1);
}


static void get_dfs_para(uint32 sel, uint32* ratio,uint32* clk_mode, uint32* ratio_d2,uint32* ddl_adjs)
{
	uint32 temp_adjs,temp_adjs_1;
	switch(sel)
	{
		case 0://160
			*ratio = 0x21;
			*clk_mode = 0x2;
			*ratio_d2 = 0x9;
			break;
		case 1://233
			*ratio = 0x18;
			*clk_mode = 0x2;
			*ratio_d2 = 0x9;
			break;
		case 2:// 311
			*ratio = 0x10;
			*clk_mode = 0x2;
			*ratio_d2 = 0x9;
			break;
		case 3:// 400
			*ratio = 0x9;
			*clk_mode = 0x2;
			*ratio_d2 = 0x9;
			break;
		case 4://533
			*ratio = 0x11;
			*clk_mode = 0x1;
			*ratio_d2 = 0x4;
			break;
		case 5://622
			*ratio = 0x10;
			*clk_mode = 0x1;
			*ratio_d2 = 0x4;
			break;
		case 6://800
			*ratio = 0x1;
			*clk_mode = 0x2;
			*ratio_d2 = 0xa;
			break;
		case 7://933
			*ratio = 0x18;
			*clk_mode = 0x1;
			*ratio_d2 = 0x0;
			break;
		default:
			break;
	}
	temp_adjs = REG32(REG_ADJS_WB+0x50*sel);
	temp_adjs_1 = REG32(REG_ADJS_WB_1+0x50*sel);
	*ddl_adjs = (((temp_adjs_1&0x4000)>>6) | (temp_adjs&0xff));
}

static uint32 get_freq()
{
	uint32 sel;
	sel = (REG32(REG_CUR_FREQ) & (0xF00)) >> 8;
	return g_dfs_table[sel];
}

//sw mode
static void sw_dfs_mode()
{
	reg_bit_set(REG_DFS_HW_CTRL,0,1,0);
	reg_bit_set(REG_DMC_CLK_INIT_CFG,0,1,1);
	reg_bit_set(REG_DFS_PURE_SW_CTRL,0,1,1);
	reg_bit_set(REG_DFS_SW_CTRL,0,1,1);
}

uint32 sw_dfs_go(uint32 dfs_point)
{
	uint32 sw_ratio;
	uint32 sw_clk_mode;
	uint32 sw_ratio_d2;
	uint32 sw_ddl_adjs;

	uint32 sel;
	if(dfs_point == get_freq())
		return DFS_SUCCESS;

	sel = freq_to_sel(dfs_point);

	//if (0 != arm7_lightsleep_bypass(0))
	//	return DFS_FAIL;

	get_dfs_para(sel,&sw_ratio,&sw_clk_mode,&sw_ratio_d2,&sw_ddl_adjs);

	reg_bit_set(REG_DFS_SW_CTRL,8,7,sw_ratio);
	reg_bit_set(REG_DFS_SW_CTRL,15,7,sw_ratio);


	reg_bit_set(REG_DFS_SW_CTRL1,16,2,sw_clk_mode);
	reg_bit_set(REG_DFS_SW_CTRL1,18,2,sw_clk_mode);

	reg_bit_set(REG_DFS_SW_CTRL2,0,9,sw_ddl_adjs);
	reg_bit_set(REG_DFS_SW_CTRL2,16,9,sw_ddl_adjs);

	reg_bit_set(REG_DFS_SW_CTRL1,0,4,sw_ratio_d2);
	reg_bit_set(REG_DFS_SW_CTRL1,8,4,sw_ratio_d2);

	reg_bit_set(REG_DFS_SW_CTRL,4,3,sel);

	reg_bit_set(REG_DFS_SW_CTRL,1,1,1);
	while(0 == (REG32(REG_DFS_SW_CTRL)&0x4));
	reg_bit_set(REG_DFS_SW_CTRL,1,1,0);

	//arm7_lightsleep_bypass(1);
	return DFS_SUCCESS;
}

//init
uint32 dfs_init()
{
	uint32 phy_help;
//	reg_bit_set(0x30400010, 20, 2, 0);
//	reg_bit_set(0x30400060, 20, 2, 0);
//	reg_bit_set(0x304000b0, 20, 2, 0);
//	reg_bit_set(0x30400100, 20, 2, 0);
//	reg_bit_set(0x30400150, 20, 2, 0);
//	reg_bit_set(0x304001a0, 20, 2, 0);
//	reg_bit_set(0x304001f0, 20, 2, 0);
//	reg_bit_set(0x30400240, 20, 2, 0);
//
//	reg_bit_set(0x30400008, 1, 1, 1);
//	reg_bit_set(0x30400058, 1, 1, 1);
//	reg_bit_set(0x304000a8, 1, 1, 1);
//	reg_bit_set(0x304000f8, 1, 1, 1);
//	reg_bit_set(0x30400148, 1, 1, 1);
//	reg_bit_set(0x30400198, 1, 1, 1);
//	reg_bit_set(0x304001e8, 1, 1, 1);
//	reg_bit_set(0x30400238, 1, 1, 1);
	sw_dfs_mode();
}

//hal interface
#endif

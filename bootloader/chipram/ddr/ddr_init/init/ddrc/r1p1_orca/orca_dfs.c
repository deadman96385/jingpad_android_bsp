#include "ddrc_r1p1.h"
#include <asm/arch-orca/clk_para_config.h>
#include <asm/arch-orca/sprd_reg.h>
#include <asm/arch-orca/sprd_chipram_env.h>
#include "ddrc_r1p1_phy.h"
#include "ddrc_r1p1_common.h"

void sw_dfs_mode()
{
	reg_bits_set(REG_PUB_DFS_HW_CTRL,0,1,0);
	reg_bits_set(REG_DMC_CLK_INIT_CFG,0,1,1);
//	reg_bits_set(REG_PUB_DFS_PURE_SW_CTRL,0,1,1);
//	reg_bits_set(REG_PUB_DFS_SW_CTEL,0,1,0);
}
static uint32 freq_to_sel(uint32 freq)
{
    switch(freq)
        {
          case 256 : return 0;
          case 384 : return 1;
          case 667 : return 2;
          case 768 : return 3;
          case 1024: return 4;
          case 1333: return 5;
          case 1536: return 6;
          case 1866: return 7;
        }
	return (uint32)(-1);
}
static uint32 get_freq()
{
	uint32 sel;
	sel = (REG32(0x6100012c)  &  0xF00) >> 8;
    switch(sel)
        {
          case 0: return 256 ;
          case 1: return 384 ;
          case 2: return 667 ;
          case 3: return 768 ;
          case 4: return 1024;
          case 5: return 1333;
          case 6: return 1536;
          case 7: return 1866;
        }
}
static void ddr_lightsleep_shut(void)
{
	reg_bits_set(0x640100d0, 17, 1, 1);
	dmc_sprd_delay(10);
}
static void ddr_lightsleep_open(void)
{
	reg_bits_set(0x640100d0, 17, 1, 0);
	dmc_sprd_delay(10);
}
uint32 sw_ratio    ;
uint32 sw_clk_mode ;
uint32 sw_ratio_d2 ;
uint32 sw_half_freq;
uint32 sw_ddl_adjs ;

static void get_dfs_para_sw(uint32 sel)
{

    switch(sel)
    {
      case 0:{
         sw_ratio    = 0x4;
	     sw_clk_mode = 0x0;
	     sw_ratio_d2 = 0x9;
	     sw_half_freq= 0x1;
	     sw_ddl_adjs = 0x16;
         break;
        }
      case 1:{
         sw_ratio    = 0x5;
	     sw_clk_mode = 0x0;
	     sw_ratio_d2 = 0x9;
	     sw_half_freq= 0x1;
	     sw_ddl_adjs = 0x16;
         break;
        }
      case 2:{
         sw_ratio    = 0x0;
	     sw_clk_mode = 0x0;
	     sw_ratio_d2 = 0x9;
	     sw_half_freq= 0x1;
	     sw_ddl_adjs = 0x16;
         break;
        }
      case 3:{
         sw_ratio    = 0x5;
	     sw_clk_mode = 0x1;
	     sw_ratio_d2 = 0x4;
	     sw_half_freq= 0x1;
	     sw_ddl_adjs = 0x16;
         break;
        }
      case 4:{
         sw_ratio    = 0x4;
	     sw_clk_mode = 0x1;
	     sw_ratio_d2 = 0x0;
	     sw_half_freq= 0x0;
	     sw_ddl_adjs = 0x16;
         break;
        }
      case 5:{
         sw_ratio    = 0x8;
	     sw_clk_mode = 0x1;
	     sw_ratio_d2 = 0x0;
	     sw_half_freq= 0x0;
	     sw_ddl_adjs = 0x16;
         break;
        }
      case 6:{
         sw_ratio    = 0x5;
	     sw_clk_mode = 0x1;
	     sw_ratio_d2 = 0x0;
	     sw_half_freq= 0x0;
	     sw_ddl_adjs = 0x16;
         break;
        }
      case 7:{
         sw_ratio    = 0x1;
	     sw_clk_mode = 0x1;
	     sw_ratio_d2 = 0x0;
	     sw_half_freq= 0x0;
	     sw_ddl_adjs = 0x16;
         break;
        }
    }
}

uint32 puresw_to_sw(uint32 dfs_point)
{
	//uint32 sw_ratio;
	//uint32 sw_clk_mode;
	//uint32 sw_ratio_d2;
	//uint32 sw_ddl_adjs;
	//uint32 sw_half_freq;

	uint32 sel;

	sel = freq_to_sel(dfs_point);

	//if (0 != arm7_lightsleep_bypass(0))
	//	return DFS_FAIL;

	get_dfs_para_sw(sel);

	reg_bits_set(REG_PUB_DFS_SW_CTEL,15,7,sw_ratio);


	reg_bits_set(REG_PUB_DFS_SW_CTRL1,18,2,sw_clk_mode);

	reg_bits_set(REG_PUB_DFS_SW_CTRL1,8,4,sw_ratio_d2);

	reg_bits_set(REG_PUB_DFS_SW_CTEL,4,3,sel);

	return 0;
}

uint32 dfs_sel_fail;
uint32 sw_dfs_go(uint32 dfs_point)
{
	uint32 sel;

	ddrc_print_debug(" sw_dfs_go start@:");
	ddr_lightsleep_shut();

	if(dfs_point == get_freq()){
	//	return DFS_SUCCESS;
		}
	sel = freq_to_sel(dfs_point);
	if(sel == (uint32)(-1))
	{
		dfs_sel_fail = 0xff;
		while(1);
		return -1;
	}

	get_dfs_para_sw(sel);

	reg_bits_set(REG_PUB_DFS_SW_CTEL,8,7,sw_ratio);

	reg_bits_set(REG_PUB_DFS_SW_CTRL1,16,2,sw_clk_mode);

	reg_bits_set(REG_PUB_DFS_SW_CTRL1,0,4,sw_ratio_d2);

	reg_bits_set((0x610001a0 + 0x60 * sel), 30,1,sw_half_freq);

	reg_bits_set(REG_PUB_DFS_SW_CTEL,4,3,sel);



	reg_bits_set(REG_PUB_DFS_PURE_SW_CTRL,0,1,1);
	reg_bits_set(REG_PUB_DFS_SW_CTEL,0,1,1);

	reg_bits_set(REG_PUB_DFS_SW_CTEL,1,1,1);
	while(0 == (REG32(REG_PUB_DFS_SW_CTEL)&0x4));
	reg_bits_set(REG_PUB_DFS_SW_CTEL,1,1,0);


	ddr_lightsleep_open();
	ddrc_print_debug(" sw_dfs_go done@:");
	return 0;
}

uint32 sw_dfs_init()
{
	reg_bits_set(REG_PUB_APB_REG_HW_DESKEWPLL_PD_CTRL1,0, 2, 0x1);
	//bit[0]drf_dfs en
	reg_bits_set(0x6100012c,0,1,1);
	sw_dfs_mode();
	//puresw_to_sw(1333);//init freq
}

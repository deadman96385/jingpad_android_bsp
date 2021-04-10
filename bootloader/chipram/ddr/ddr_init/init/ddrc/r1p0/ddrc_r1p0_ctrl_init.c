#include "sci_types.h"
#include <asm/arch/sprd_reg.h>
#include "ddrc_r1p0.h"
#include "ddrc_r1p0_phy.h"
#include "ddrc_r1p0_common.h"
#include "ddrc_r1p0_auto_dected.h"
extern DRAM_CHIP_INFO ddr_chip_cur;
extern u8 cur_odt_on[8];

DDR_UNSYMMETRY_MODE unsymmetry_mode_cur = CFG_UNSYMMETRY_DRAM_MODE;	/*unsymmetry type*/
static u32 MCP_CS_POS_MODE = 0;
DMC_PUB_CLK_CFG dmc_pub_clk_cfg[8] =
{
	/*freq_num, ddr_clk, pll_source, ratio[1:1/1:2]*/
	/*pll_sel, pll_div_sel, deskew_mode, x1_sel, d2_sel, half_freq_mode	*/

	{0, PUB_CLK_160M,DPLL1, {0x1,0x4,DESKEW_ON, 0x1, 0x2,0x1}},
	{1, PUB_CLK_233M,DPLL0, {0x0,0x3,DESKEW_ON, 0x1, 0x2,0x1}},
	//{1, PUB_CLK_256M,TWPLL, {0x4,0x0,DESKEW_ON, 0x1, 0x2,0x1}},
	{2, PUB_CLK_311M,DPLL0, {0x0,0x2,DESKEW_ON, 0x1, 0x2,0x1}},
	{3, PUB_CLK_400M,DPLL1, {0x1,0x1,DESKEW_ON, 0x1, 0x2,0x1}},
	//{4, PUB_CLK_533M,DPLL1, {0x1,0x2,DESKEW_ON, 0x1, 0x1,0x0}},//1:2
	{4, PUB_CLK_533M,DPLL1, {0x1,0x2,DESKEW_ON, 0x0, 0x1,0x1}},  //1:1
	//{5, PUB_CLK_622M,DPLL0, {0x0,0x2,DESKEW_ON, 0x1, 0x1,0x0}},//1:2
	{5, PUB_CLK_622M,DPLL0, {0x0,0x2,DESKEW_ON, 0x0, 0x1,0x1}},  //1:1
	{6, PUB_CLK_800M,DPLL1, {0x1,0x3,DESKEW_ON, 0x0, 0x0,0x0}},
	//{6, PUB_CLK_800M,DPLL1, {0x1,0x0,DESKEW_OFF, 0x2, 0x2,0x0}},
	{7, PUB_CLK_933M,DPLL0, {0x0,0x3,DESKEW_ON, 0x0, 0x0,0x0}}
	//{7, PUB_CLK_933M,DPLL0, {0x0,0x0,DESKEW_OFF, 0x0, 0x0,0x0}}
};
static void ddrc_pub_clock_mode_set(u32 freq_sel)
{
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	{
		/*f0/f1/f2/f3 pub clock is set to bypass mode*/
		if (freq_sel < 4)
			dmc_pub_clk_cfg[freq_sel].clk_cfg.deskew_mode = 0;
	}

}
static void ddrc_pub_dll_adj_update(u32 dfs_freq_sel)
{
	u32 regval;
	u32 read_data;
	u32 tmp_addr = DMC_GUCPHY0_BASE + (dfs_freq_sel * 20 *4);
	regval = reg_bits_get(tmp_addr + 0xC, 0, 8);
	read_data = reg_bits_get(tmp_addr + 0x10, 14, 1);
	regval |= (read_data << 8);
	reg_bits_set(REG_PUB_AHB_WRAP_DFS_SW_CTRL2, 0, 9, regval);
}
void dmc_pub_clk_setting(u32 freq_sel)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval, i;
	u32 tmp_addr1 = DMC_GUCPHY0_BASE + (freq_sel * 20*4);
	u32 tmp_addr2 = DMC_GUCPHY1_BASE + (freq_sel * 20*4);
	u32 pub_dfs_hw_enable = 0;
	u32 dfs_clk_auto_mode = 0;
	u32 dfs_sw_dfs_mode =1;

	ddrc_pub_clock_mode_set(freq_sel);

	reg_bits_set(REG_PUB_DFS_HW_CTRL, 0, 1, pub_dfs_hw_enable );
	reg_bits_set(REG_DMC_CLK_INIT_CFG, 0, 1, dfs_clk_auto_mode);
	reg_bits_set(REG_PUB_DFS_PURE_SW_CTRL, 0, 1, dfs_sw_dfs_mode);

	reg_bits_set(REG_PUB_DFS_SW_CTEL, 15, 3, dmc_pub_clk_cfg[freq_sel].clk_cfg.pll_sel);
	reg_bits_set(REG_PUB_DFS_SW_CTEL, 18, 4, dmc_pub_clk_cfg[freq_sel].clk_cfg.pll_div_sel);
	reg_bits_set(REG_PUB_DFS_SW_CTRL1, 18, 2, dmc_pub_clk_cfg[freq_sel].clk_cfg.deskew_mode);
	reg_bits_set(REG_PUB_DFS_SW_CTRL1, 8, 2, dmc_pub_clk_cfg[freq_sel].clk_cfg.x1_sel);
	reg_bits_set(REG_PUB_DFS_SW_CTRL1, 10, 2, dmc_pub_clk_cfg[freq_sel].clk_cfg.d2_sel);

	if (dmc_pub_clk_cfg[freq_sel].clk_cfg.half_freq_mode)
	{
		pdmc->dmc_dtmg_f[freq_sel][8] |= (1<<30);
	}
	else
	{
		pdmc->dmc_dtmg_f[freq_sel][8] &= ~(1<<30);
	}

	if (dmc_pub_clk_cfg[freq_sel].clk_cfg.deskew_mode != DESKEW_ON)
	{
		//printf("deskew dll mode setting\n");
		reg_bits_set((tmp_addr1 + 0x8), 31, 1, 0x1);//deskew dll mode setting
		reg_bits_set((tmp_addr1 + 0xC), 31, 1, 0x1);//deskew dll mode setting
		reg_bits_set((tmp_addr2 + 0x8), 31, 1, 0x1);//deskew dll mode setting
		reg_bits_set((tmp_addr2 + 0xC), 31, 1, 0x1);//deskew dll mode setting
	}
	else
	{
		//printf("deskew pll mode setting\n");
		reg_bits_set((tmp_addr1 + 0x8), 31, 1, 0x0);//deskew pll mode setting
		reg_bits_set((tmp_addr1 + 0xC), 31, 1, 0x0);//deskew pll mode setting
		reg_bits_set((tmp_addr2 + 0x8), 31, 1, 0x0);//deskew pll mode setting
		reg_bits_set((tmp_addr2 + 0xC), 31, 1, 0x0);//deskew pll mode setting
	}

	ddrc_pub_dll_adj_update(freq_sel);

	reg_bits_set(REG_DMC_CLK_INIT_SW_START,0,1, 1);
	while(0x1 != ((REG32(REG_DMC_CLK_STATE) >> 0) & 0x1));
	reg_bits_set(REG_DMC_CLK_INIT_SW_START,0,1, 0);
}

void gucphy_set_clock(u32 freq_sel)
{
	dmc_pub_clk_setting(freq_sel);
}

void update_dfs_freq_sel(u32 freq_sel)
{
	unsigned int regval;
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	/*step 1. polling rf phy init complete[3:0]*/
#ifndef PXP_DEBUG
	regval = pdmc->dmc_cfg3 >> 16 & 0xf;
	/*0xa for lpaddr3; 0x0 for lpddr4*/
	if ((0xa != regval) && (0x0 != regval))
	{
		dmc_print_str("phy_init_complete is not zero,can not modify dfs_freq_sel\n");
		while(1);
	}
#endif
	dmc_sprd_delay(10);
	/*set 2. set wr cfg11 to update the timing parameter to each channel*/
	regval = pdmc->dmc_dcfg11;
	regval = u32_bits_set(regval, 13, 1, 1);//drf_dfs_cmd_mrw_first4_dis,this bit is used to disable the last 4 mrw(total 16) during dfs
	regval = u32_bits_set(regval, 15, 1, 1);//drf_dfs_cmd_mrw_first8_dis,this bit is used to disable the last 8 mrw(total 16) during dfs
	regval = u32_bits_set(regval, 4, 3, freq_sel);
	pdmc->dmc_dcfg11 = regval;

}

void change_clk_freq_seq(u32 freq_sel)
{
	unsigned int regval;
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	/*stetp3. change clock frequency form soc and setting the right rf half freq mode from soc*/
	/*include half mode setting*/
	gucphy_set_clock(freq_sel);

	/*stet 2. modify speed sel*/
	update_dfs_freq_sel(freq_sel);
	//init_clk_dmc_4x_en = 1;//????????
	//delay 100ns;
	/*stetp3. change clock frequency form soc and setting the right rf half freq mode from soc*/
	//gucphy_set_clock(freq_sel);

	//if (freq_sel < 622)
	//freq_ratio_1vs1 = 1;
	//else
	//freq_ratio_1vs1 = 0;

	/*avj_v for update initial dll setting*/
	// deskew_dll_adjv_init = 1;
	// delay(1);
	// deskew_dll_adjv_init = 0;


	//init_clk_dmc_4x_en = 0; ??????
}

void axi_ch_cfg_seq(void)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
        u32 regval = 0;
        u32 i = 0;
        for(i = 0; i < 8; i++)
        {
        	regval = REG32((&(pdmc->dmc_cfg1_ach0)) + (i * 8));
        	regval = u32_bits_set(regval, 4, 1, 1);
        	REG32((&(pdmc->dmc_cfg1_ach0)) + (i * 8)) = regval;
	}

//	regval = pdmc->dmc_cfg1_ach0;
//	regval= u32_bits_set(regval, 4, 1, 1);
//	pdmc->dmc_cfg1_ach0 = regval;

//	regval = pdmc->dmc_cfg1_ach1;
//	regval= u32_bits_set(regval, 4, 1, 1);
//	pdmc->dmc_cfg1_ach1 = regval;

//	regval = pdmc->dmc_cfg1_ach2;
//	regval= u32_bits_set(regval, 4, 1, 1);
//	pdmc->dmc_cfg1_ach2 = regval;

//	regval = pdmc->dmc_cfg1_ach3;
//	regval= u32_bits_set(regval, 4, 1, 1);
//	pdmc->dmc_cfg1_ach3 = regval;

//	regval = pdmc->dmc_cfg1_ach4;
//	regval= u32_bits_set(regval, 4, 1, 1);
//	pdmc->dmc_cfg1_ach4 = regval;

//	regval = pdmc->dmc_cfg1_ach5;
//	regval= u32_bits_set(regval, 4, 1, 1);
//	pdmc->dmc_cfg1_ach5 = regval;

//	regval = pdmc->dmc_cfg1_ach6;
//	regval= u32_bits_set(regval, 4, 1, 1);
//	pdmc->dmc_cfg1_ach6 = regval;

//	regval = pdmc->dmc_cfg1_ach7;
//	regval= u32_bits_set(regval, 4, 1, 1);
//	pdmc->dmc_cfg1_ach7 = regval;

}
#if 0
static void dmc_interleave_liner_cfg(struct interleave_cfg *liner_cfg)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval;

	regval = pdmc->dmc_dcfg18;//0x0148
	regval = u32_bits_set(regval, 0, 14, liner_cfg->liner_base_ch0);
	regval = u32_bits_set(regval, 16, 14, liner_cfg->liner_base_ch1);
	pdmc->dmc_dcfg18 = regval;

	regval = pdmc->dmc_dcfg19;//0x014c
	regval = u32_bits_set(regval, 0, 14, liner_cfg->liner_base_ch2);
	regval = u32_bits_set(regval, 16, 14, liner_cfg->liner_base_ch3);
	pdmc->dmc_dcfg19 = regval;

	regval = pdmc->dmc_dcfg20;//0x0150
	regval = u32_bits_set(regval, 0, 14, liner_cfg->interleave_base);
	regval = u32_bits_set(regval, 16, 14, liner_cfg->interleave_offset);
	pdmc->dmc_dcfg20 = regval;
}
#endif

static void dmc_interleave_cfg_seq(void)
{
        DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
        struct interleave_cfg liner_cfg;
        u32 regval;
        u32 cs_pos_mode;
        regval = pdmc->dmc_cfg5;
        /*0:64B 1:128B 2:256B 3:512B 4:1KB 5:2KB 6:4KB 7:8KB*/
        regval = u32_bits_set(regval, 0, 3, INTERLEAVE_SIZE);
        pdmc->dmc_cfg5 = regval;

        regval = pdmc->dmc_dcfg17;
	regval = u32_bits_set(regval, 24, 3, 1);/*1:ch0/1; 2:ch2/3; 3:ch0/1/2*/
        pdmc->dmc_dcfg17 = regval;

//        switch (MCP_CS_POS_MODE)
//        {
//	case 31:
//		liner_cfg.liner_base_ch0 = RF_LINER_BASE_CH0_16G;
//		liner_cfg.liner_base_ch1 = RF_LINER_BASE_CH1_16G;
//		liner_cfg.liner_base_ch2 = RF_LINER_BASE_CH2_16G;
//		liner_cfg.liner_base_ch3 = RF_LINER_BASE_CH3_16G;
//		liner_cfg.interleave_base = RF_INTERLEAVE_BASE_16G;
//		liner_cfg.interleave_offset= RF_INTERLEAVE_OFFSET_16G;
//		dmc_interleave_liner_cfg(&liner_cfg);
//		break;
//	case 30:
//		liner_cfg.liner_base_ch0 = RF_LINER_BASE_CH0_8G;
//		liner_cfg.liner_base_ch1 = RF_LINER_BASE_CH1_8G;
//		liner_cfg.liner_base_ch2 = RF_LINER_BASE_CH2_8G;
//		liner_cfg.liner_base_ch3 = RF_LINER_BASE_CH3_8G;
//		liner_cfg.interleave_base = RF_INTERLEAVE_BASE_8G;
//		liner_cfg.interleave_offset= RF_INTERLEAVE_OFFSET_8G;
//		dmc_interleave_liner_cfg(&liner_cfg);
//		break;
//	case 29:
//		liner_cfg.liner_base_ch0 = RF_LINER_BASE_CH0_4G;
//		liner_cfg.liner_base_ch1 = RF_LINER_BASE_CH1_4G;
//		liner_cfg.liner_base_ch2 = RF_LINER_BASE_CH2_4G;
//		liner_cfg.liner_base_ch3 = RF_LINER_BASE_CH3_4G;
//		liner_cfg.interleave_base = RF_INTERLEAVE_BASE_4G;
//		liner_cfg.interleave_offset= RF_INTERLEAVE_OFFSET_4G;
//		dmc_interleave_liner_cfg(&liner_cfg);
//		break;
//	case 28:
//		liner_cfg.liner_base_ch0 = RF_LINER_BASE_CH0_2G;
//		liner_cfg.liner_base_ch1 = RF_LINER_BASE_CH1_2G;
//		liner_cfg.liner_base_ch2 = RF_LINER_BASE_CH2_2G;
//		liner_cfg.liner_base_ch3 = RF_LINER_BASE_CH3_2G;
//		liner_cfg.interleave_base = RF_INTERLEAVE_BASE_2G;
//		liner_cfg.interleave_offset= RF_INTERLEAVE_OFFSET_2G;
//		dmc_interleave_liner_cfg(&liner_cfg);
//	break;
//	case 27:
//		liner_cfg.liner_base_ch0 = RF_LINER_BASE_CH0_1G;
//		liner_cfg.liner_base_ch1 = RF_LINER_BASE_CH1_1G;
//		liner_cfg.liner_base_ch2 = RF_LINER_BASE_CH2_1G;
//		liner_cfg.liner_base_ch3 = RF_LINER_BASE_CH3_1G;
//		liner_cfg.interleave_base = RF_INTERLEAVE_BASE_1G;
//		liner_cfg.interleave_offset= RF_INTERLEAVE_OFFSET_1G;
//		dmc_interleave_liner_cfg(&liner_cfg);
//	break;
//	case 26:
//		liner_cfg.liner_base_ch0 = RF_LINER_BASE_CH0_512M;
//		liner_cfg.liner_base_ch1 = RF_LINER_BASE_CH1_512M;
//		liner_cfg.liner_base_ch2 = RF_LINER_BASE_CH2_512M;
//		liner_cfg.liner_base_ch3 = RF_LINER_BASE_CH3_512M;
//		liner_cfg.interleave_base = RF_INTERLEAVE_BASE_512M;
//		liner_cfg.interleave_offset= RF_INTERLEAVE_OFFSET_512M;
//		dmc_interleave_liner_cfg(&liner_cfg);
//	break;
//	default:
//	break;
//
//        }
}

static void dmc_portx_remap_addr_x(u32 addr_0, u32 addr_1)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	pdmc->dmc_cfg5 |= (1 << 3);
	pdmc->dmc_cfg6 = addr_0;
	pdmc->dmc_cfg7 = addr_1;
}

static int dmc_pub_addr_remap(void)
{
	u64 chipsize;
	int i;
	u64 cs0_size,cs1_size;

	if ((ddr_chip_cur.cs_num == 2))
	{
		//cs0 2GB,cs1 4GB support
		sdram_cs_whole_size(0, &cs0_size);
		sdram_cs_whole_size(1, &cs1_size);
		if ((cs0_size==0x80000000) && (cs1_size == 0x100000000))
		{
			dmc_portx_remap_addr_x(0xba983210, 0x3210fedc);
			return 0;
		}
	}

	if ((ddr_chip_cur.cs_num == 1) || (ddr_chip_cur.unsymmetry != 0))
		return -1;

	if (-1 == sdram_chip_whole_size(&chipsize))
	{
		return -1;
	}

	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
        {
            chipsize /= 2;
        }
	/*enable all port remap*/
	switch(chipsize)
	{
		/*24G bit*/
		case 0x60000000:
			dmc_portx_remap_addr_x(0x10654210, 0x42106542);
			break;
		/*48G bit*/
		case 0xC0000000:
			dmc_portx_remap_addr_x(0x98543210, 0x3210dcba);
			break;
		default:
			break;
	}
	return 0;
}
void ctrl_dram_setting(void)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 dw;
	u32 val = pdmc->dmc_cfg0;
	uint64 chip_size;

	sdram_chip_whole_size(&chip_size);
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
        {
            chip_size /= 2;
        }
	/*cs position setting*/
	if (chip_size > 0x80000000)/*dmem size > 2GB*/
	{
		val = u32_bits_set(val, 0, 3, 0x7);	//rf_cs_position bit31
		MCP_CS_POS_MODE = 31;
	}
	else if (chip_size > 0x40000000)/*dmem size > 1GB*/
	{
		val = u32_bits_set(val, 0, 3, 0x6);	//rf_cs_position bit30
		MCP_CS_POS_MODE = 30;
	}
	else if (chip_size > 0x20000000)/*dmem size > 512M*/
	{
		val = u32_bits_set(val, 0, 3, 0x5);	//rf_cs_position bit29
		MCP_CS_POS_MODE = 29;
	}
	else if (chip_size > 0x10000000)/*dmem size > 256M*/
	{
		val = u32_bits_set(val, 0, 3, 0x4);	//rf_cs_position bit28
		MCP_CS_POS_MODE = 28;
	}
	else if (chip_size > 0x8000000)/*dmem size > 128M*/
	{
		val = u32_bits_set(val, 0, 3, 0x3);	//rf_cs_position bit27
		MCP_CS_POS_MODE = 27;
	}
	else
	{
		val = u32_bits_set(val, 0, 3, 0x2);	//rf_cs_position bit26
		MCP_CS_POS_MODE = 26;
	}

	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
	{
		val = u32_bits_set(val, 4, 3, 3);//rf_dburst_length
		val = u32_bits_set(val, 29, 1, 0);//lpddr3_mode, default is zero
	}
	else
	{
		val = u32_bits_set(val, 4, 3, 4);//rf_dburst_length
		val = u32_bits_set(val, 29, 1, 1);//lpddr4_mode
	}
	if (ddr_chip_cur.cs_num == 1)
	{
		val = u32_bits_set(val, 0, 3, 0x7);	//rf_cs_position bit31
		val = u32_bits_set(val, 14, 2, 0x1);	//cs mode,2'h1: the address space of cs0 and cs1 merged to cs0
		MCP_CS_POS_MODE = 31;
	}

	pdmc->dmc_cfg0 = val;

	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
	{
		val = pdmc->dmc_dcfg0;
		/*data width 1:x32, 0:x16*/
//		dw = (ddr_chip_cur.cs0_jedec_info->dw == 32) ? 1: 0;
		dw = 1;
		val = u32_bits_set(val, 8, 1, dw);
	        pdmc->dmc_dcfg0 = val;

	}
        else if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	{
		val = pdmc->dmc_dcfg3;
		/*data width 1:x8, 0:x16*/
		dw = (ddr_chip_cur.cs0_jedec_info->dw == 8) ? 0x1: 0;
		val = u32_bits_set(val, 16, 1, dw);
		val = u32_bits_set(val, 18, 1, dw);
		dw = (ddr_chip_cur.cs1_jedec_info->dw == 8) ? 0x1: 0;
		val = u32_bits_set(val, 17, 1, dw);
		val = u32_bits_set(val, 19, 1, dw);
	        pdmc->dmc_dcfg3 = val;

	}
        else
        {}
        if(ddr_chip_cur.chip_type == DRAM_LPDDR3)
        {
         	val = pdmc->dmc_dcfg0;
        	/*column mode*/
        	if (0 != ddr_chip_cur.unsymmetry)
        	{
        		switch(unsymmetry_mode_cur)
        		{
        			case DDR_6Gb_10_COL_MODE:
        				val = u32_bits_set(val, 4, 3, 5);
        				break;
        			case DDR_6Gb_11_COL_MODE:
        				val = u32_bits_set(val, 4, 3, 6);
        				break;
        			case DDR_12Gb_MODE:
        				val = u32_bits_set(val, 4, 3, 7);
        				break;
        			default:
        				break;
        		}
        	}
        	else
        	{
        		val = u32_bits_set(val, 4, 3, (ddr_chip_cur.cs0_jedec_info->column - 8));
        	}
        	pdmc->dmc_dcfg0 = val;
        }
}

void ctrl_init_dcfg1(void)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val = 0;
	u32 i= 0;
	u64 cs0_size,cs1_size;

	//per channel 12Gb
	//tRFCab = 380ns
	//rRFCpb = 190ns
	sdram_cs_whole_size(0, &cs0_size);
	sdram_cs_whole_size(1, &cs1_size);
	if (((cs0_size/2) >= 0x60000000) || ((cs1_size/2) >= 0x60000000))
	{
		pdmc->dmc_dtmg_f[0][2] = 0X1E101C48;
		pdmc->dmc_dtmg_f[1][2] = 0X2C171C52;
		pdmc->dmc_dtmg_f[2][2] = 0X3B1E245B;
		pdmc->dmc_dtmg_f[3][2] = 0X4B262466;
		pdmc->dmc_dtmg_f[4][2] = 0X65332C77;
		pdmc->dmc_dtmg_f[5][2] = 0X763C3482;
		pdmc->dmc_dtmg_f[6][2] = 0X974C389F;
		pdmc->dmc_dtmg_f[7][2] = 0XB15944B7;
	}
	if ((0x8 == ddr_chip_cur.cs0_jedec_info->dw) || (0x8 == ddr_chip_cur.cs1_jedec_info->dw))
        {
	    for (i = 5; i < MAX_FREQ_SEL; i++)
            {
                val = (pdmc->dmc_dtmg_f[i][1] >> 8) & (0xf);
                pdmc->dmc_dtmg_f[i][1]  = ((pdmc->dmc_dtmg_f[i][1] & (~(0xf << 8))) | (((val + 1) << 8)));
            }
        }
}
/*ddr type, column mode, data width, precharge pin are configed here*/
static void ctrl_init_dcfg0(void)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val;

	val = pdmc->dmc_dcfg0;
	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
	{
		/*pin mux mode*/
		/*2'b00 :ch0->phy_0,ch1->phy_1*/
		/*2'b01 :ch0->hpy_0&phy_1, ch1->empty*/
		val = u32_bits_set(val, 0, 1, 1);

		/*drf_dsoft_ch_sel*/
		/*bit-0 set '1' to enable channel-0 software command*/
		/*bit-1 set '1' to enable channel-1 software command*/
		/*bit-2 set '1' to enable channel-2 software command*/
		/*bit-3 set '1' to enable channel-3 software command*/
		val = u32_bits_set(val, 20, 4, 5);
	}
	else
	{
		/*pin mux mode*/
		/*2'b00 :ch0->phy_0,ch1->phy_1*/
		/*2'b01 :ch0->hpy_0&phy_1, ch1->empty*/
		val = u32_bits_set(val, 0, 1, 0);

		/*data width 1:x32. 0:X16*/
		val = u32_bits_set(val, 8, 1, 0);

		/*bit[11] rf_data_oe_mode, bit[12]rf_data_ie_mode*/
		val = u32_bits_set(val, 11, 2, 3);

		/*drf_dsoft_ch_sel*/
		/*bit-0 set '1' to enable channel-0 software command*/
		/*bit-1 set '1' to enable channel-1 software command*/
		/*bit-2 set '1' to enable channel-2 software command*/
		/*bit-3 set '1' to enable channel-3 software command*/
		val = u32_bits_set(val, 20, 4, 0xf);
	}

	/*enable drf_sample_auto_rst_en (default:0) */
	val = u32_bits_set(val, 17, 1, 1);
	pdmc->dmc_dcfg0 = val;
}
int ctrl_pre_set_seq(dfs_freq_table dfs_frequency[8])
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval;

	/*step 1) disable auto_sleep_en*/
	regval = pdmc->dmc_cfg0;
	regval = u32_bits_set(regval, 8, 1, 0);
	pdmc->dmc_cfg0= regval;

	/*step 2) disable drf_ext_clk_ag_en*/
	regval = pdmc->dmc_dcfg9;
	regval = u32_bits_set(regval, 12, 1, 0);
	pdmc->dmc_dcfg9= regval;

	/*Set dram mode*/
	ctrl_dram_setting();

	/*Set dram width if x16 or 4 bank*/
	ctrl_init_dcfg0();

	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
	{
		/*this fields is used to enable dmem ch3/2/1/0*/
		/*disable channel 1*/
		regval = pdmc->dmc_dcfg17;
		regval = u32_bits_set(regval, 0, 4, 5);
		pdmc->dmc_dcfg17 = regval;

		/*ch0 mrr dslice selected*/
		regval = pdmc->dmc_dcfg4;
		regval = u32_bits_set(regval, 24, 2, 0);
		pdmc->dmc_dcfg4 = regval;
	}

	/*dmem timing setting*/
	lpddr_timing_init(ddr_chip_cur.chip_type, dfs_frequency);

#ifdef ASYNC_MODE
	axi_ch_cfg_seq();
#endif
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
	{
		dmc_interleave_cfg_seq();
	}

	return 0;
}

void ctrl_post_set_seq(void)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 val ,num, mr0;
	/*Step 1.setting lowpower*/
	val = pdmc->dmc_cfg0;
	val = u32_bits_set(val, 8, 2, 3);//bit[9] auto gate bit[8] auto sleep
	pdmc->dmc_cfg0 = val;

	val = pdmc->dmc_dcfg9;
	val = u32_bits_set(val, 0,  3, 0x5);/*drf_auto_clk_stop_en_ahb : 1 */
					    /*drf_auto_pwr_down_en_ahb : 0 */
                                            /*drf_auto_self_ref_en_ahb : 1 */
	val = u32_bits_set(val, 8,  4, 0xf);/*bit[11:8] drf_t_cksre: 0xf*/
	val = u32_bits_set(val, 12, 2, 0x1);/*bit [12]drf_ext_clk_ag_en*/
					    /*bit [13]drf_auto_pwr_down_percs_en*/
#ifdef LP4_PINMUX_CASE1
	val = u32_bits_set(val, 14, 1, 0x0);/*bit [14]drf_auto_self_refresh_percs_en*/
#else
	val = u32_bits_set(val, 14, 1, 0x1);
#endif
	val = u32_bits_set(val, 16, 3, 0x7);/*drf_ca_shutdow : 1*/
                                            /*drf_cs_shutdown_en : 1*/
                                            /*drf_ck_shutdown_en : 1*/
	pdmc->dmc_dcfg9 = val;

	/*step 2) setting drf_t_mr4 for not the same with drf_t_zqc*/
#ifdef DRAM_AUTO_MR4
	val = pdmc->dmc_dcfg5;
	val = u32_bits_set(val, 0, 24, 0x1ff0); /*drf_t_mr4*/
	val = u32_bits_set(val, 24, 1, 1);      /*[24]=1: drf_auto_mr4_en, [25]=0: for rank-0 */
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
		val = u32_bits_set(val, 25, 1, 1); /*drf_auto_mr4_allcs*/
	pdmc->dmc_dcfg5 = val;
#endif
	/*step 3) enable auto refresh and pre bank refresh*/
	val = pdmc->dmc_dcfg3;
	val = u32_bits_set(val, 12, 1, 1);
	pdmc->dmc_dcfg3 = val;

	/*step 4) enable dfs and set pll lock time*/
	val = pdmc->dmc_dcfg11;
	if (cur_odt_on[7] == 1)
	{
		val = u32_bits_set(val, 13, 1, 0);//drf_dfs_cmd_mrw_first4_dis,this bit is used to disable the first 4 mrw(total 16) during dfs
		val = u32_bits_set(val, 14, 1, 0);//drf_dfs_cmd_mrw_last4_dis,this bit is used to disable the last 4 mrw(total 16) during dfs
		val = u32_bits_set(val, 15, 1, 0);//drf_dfs_cmd_mrw_last8_dis,this bit is used to disable the last 8 mrw(total 16) during dfs
	}
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
		val = u32_bits_set(val, 0, 4, 0x7);//bit[0]dfs en,bit[1] dll rst en,bit[2]cmd mrw en,bit[3]dram dll lock
	else
		val = u32_bits_set(val, 0, 4, 0xF);//bit[0]dfs en,bit[1] dll rst en,bit[2]cmd mrw en,bit[3]dram dll lock
	val = u32_bits_set(val, 17, 1, 1);//bit[17] drf dfs clk stop en
	pdmc->dmc_dcfg11 = val;

#ifdef DRAM_AUTO_ZQC
	/*step 5) drf_auto_zqc_sel (2:8`h56 ZQCS; 1:8`hAB ZQCL)*/
	val = pdmc->dmc_dcfg6;
	val = u32_bits_set(val, 0, 24, 0x630000);
	val = u32_bits_set(val, 24, 1, 1);        /*[24]=1: drf_auto_zqc_en */
	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
		val = u32_bits_set(val, 25, 1, 1);//drf_auto_zqc_allcs
	val = u32_bits_set(val, 26, 2, 2);//:0x56 short calibration
	pdmc->dmc_dcfg6 = val;
#endif

	/*step 6) enable rf_period_cpst_en*/
	val = pdmc->dmc_dcfg17;
	val = u32_bits_set(val, 4, 12, 0x01a);          //drf_t_cpst_3.9us
	val = u32_bits_set(val, 16, 1, 1);		//rt_period_cpst_en
	pdmc->dmc_dcfg17= val;

	/*step 7) mpu enable*/
	pdmc->dmc_cfg5 |= (1<<13);

	/*step 8) bit[3:0] phy update en,disable phy update*/
	pdmc->dmc_cfg1 = 0;

	/*step 9) dmc port address remap*/
	dmc_pub_addr_remap();

	/*step 10) drf_cmdq_busy_level*/
	val = pdmc->dmc_dcfg7;
	val = u32_bits_set(val, 8, 4, 0x8);
	pdmc->dmc_dcfg7 = val;

	if (ddr_chip_cur.chip_type == DRAM_LPDDR4)
        {
            ctrl_init_dcfg1();
        }
}


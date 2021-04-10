#include <asm/arch/clk_para_config.h>
#include "ddrc_init.h"
#include "ddrc_feature_init.h"
#include "dram_support.h"
#include "dram_test.h"
#include "lpddr4_ctl_timing.h"
#include "lpddr4_phy_timing.h"




extern DDRC_DMC_DTMG_T dmc_tmg_lp3[];
extern DDRC_DMC_DTMG_T dmc_tmg_lp4[];
extern DDRC_PHY_TMG_T phy_tmg_lp3[];
extern DDRC_PHY_TMG_T phy_tmg_lp4[];
extern DDRC_FREQ_INFO_T ddrc_freq_info[];

DRAM_INFO_T dram_info;
DDRC_DMC_DTMG_T *dmc_dtmg;
DDRC_PHY_TMG_T *phy_tmg;
DDRC_FREQ_INFO_T *freq_info=(DDRC_FREQ_INFO_T *)(&ddrc_freq_info[0]);

#ifdef DDR_SCAN_ENABLE
#define dmc_print_str(x) NULL
#define print_Hex(x) NULL
#define print_Dec(x) NULL
int first_init = 0;
u32 scan_target_clk = 0;
#endif

void dpll_cfg(u32 ddr_clk)
{
	u32 nint_val=0,kint_val=0;
	/***set div_s***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 0,1,0x1);

	/***set sdm_en***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 1,1,0x1);
	switch(ddr_clk)
	{
	case DDR_CLK_1866M:
		nint_val=0x47;kint_val=0x627627;break;
	case DDR_CLK_1200M:
		nint_val=0x2e;kint_val=0x13b13b;break;
	case DDR_CLK_1333M:
		nint_val=0x33;kint_val=0x227627;break;
	}
	/***set nint and kint***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL2,23,7,nint_val);
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL2,0,23,kint_val);
	wait_us(300);
}

void pll_ssc_cfg(u32 ddr_clk,u32 css_val)
{
/*
*delta F= delat Fs*Kstep=((256*PLL_CCS_CTRL[7:0]+255)/2^23)*215*26MHz
*						=0.17MHZ+PLL_CSS_CTRL[7:0]*0.17MHz
*
*if setting delta F=20M,PLL_DIV_S=1,PLL_SDM_EN=1,PLL_CCS_CTRL[7:0]=01110100
*/
	/***set div_s***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 0,1,0x1);

	/***set sdm_en***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 1,1,0x1);

	/***set mod_en***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL3, 3,1,0x1);

	/***PLL_CSS_CTRL***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL3, 4,8,css_val);
}

void dmc_freq_sel_search(u32 ddr_clk,u32* fn)
{
	*fn=0xffffffff;
	switch(ddr_clk)
	{
	case DDR_CLK_256M:*fn=0;break;
	case DDR_CLK_384M:*fn=1;break;
	case DDR_CLK_512M:*fn=2;break;
	case DDR_CLK_622M:*fn=3;break;
	case DDR_CLK_768M:*fn=4;break;
	case DDR_CLK_933M:*fn=5;break;
	case DDR_CLK_1200M:*fn=6;break;
	case DDR_CLK_1333M:*fn=7;break;
	}
	return;
}

void dmc_half_freq_mode_set()
{
	u32 fn=0;
	//half_freq_mode
	for(fn=0;fn<dram_info.fn_max;fn++)
	{
		reg_bit_set(DMC_CTL0_(0x01a0+fn*0x60),30,1,(freq_info+fn)->half_freq_mode);
	}
}

void ddrc_dmc_soft_reset()
{
	//ddrc soft reset
	reg_bit_set(DMC_SOFT_RST_CTRL, 2, 1,0x1);//dmc_soft_rst
}
void ddrc_dmc_soft_release()
{
	reg_bit_set(DMC_SOFT_RST_CTRL, 2, 1,0x0);//dmc_soft_rst
}

void ddrc_phy_soft_reset()
{
	//ddrc phy soft reset
	reg_bit_set(DMC_SOFT_RST_CTRL, 0, 1,0x1);//ddrphy_soft_rst
}

void ddrc_phy_soft_release()
{
	reg_bit_set(DMC_SOFT_RST_CTRL, 0, 1,0x0);//ddrphy_soft_rst
}

void ddrc_phy_fifo_reset()
{
	//reset fifo
	reg_bit_set(DMC_PHY0_(0x0004), 9, 1,0x1);//rf_phy_sample_rst
	reg_bit_set(DMC_PHY0_(0x0004), 9, 1,0x0);
}



void pure_sw_dfs_go(u32 fn)
{
	//emc_ckg_d2_sel_pure_sw
	reg_bit_set(DFS_PURE_SW_CTRL,20,4,(freq_info+fn)->ratio_d2);
	//emc_ckg_sel_pure_sw
	reg_bit_set(DFS_PURE_SW_CTRL, 1,7,(freq_info+fn)->ratio);
	//pure_sw_dfs_clk_mode
	reg_bit_set(DFS_PURE_SW_CTRL,18,2,(freq_info+fn)->clk_mode);
	//pure_sw_dfs_frq_sel
	reg_bit_set(DFS_PURE_SW_CTRL, 8,3,fn);
	//dmc_clk_init_sw_start
	reg_bit_set(DFS_CLK_INIT_SW_START, 0, 1,0x1);
	//wait done
	while((__raw_readl(DFS_CLK_STATE)&0x1) ==0 );
	//dmc_clk_init_sw_start clear
	reg_bit_set(DFS_CLK_INIT_SW_START, 0, 1,0x0);
}

void ddrc_clk_cfg(u32 fn)
{
	reg_bit_set(DMC_CTL0_(0x012c), 4, 3,fn);//drf_dfs_reg_sel
	reg_bit_set(DMC_CTL0_(0x012c), 4, 3,fn);//drf_dfs_reg_sel
	pure_sw_dfs_go(fn);
	dmc_half_freq_mode_set();
}

void ddrc_clk_13m_cfg()
{
	reg_bit_set(DMC_CTL0_(0x012c), 4, 3,0);//drf_dfs_reg_sel
	reg_bit_set(DMC_CTL0_(0x012c), 4, 3,0);//drf_dfs_reg_sel
	//emc_ckg_d2_sel_pure_sw
	reg_bit_set(DFS_PURE_SW_CTRL,20,4,0x9);
	//emc_ckg_sel_pure_sw
	reg_bit_set(DFS_PURE_SW_CTRL, 1,7,0x42);
	//pure_sw_dfs_clk_mode
	reg_bit_set(DFS_PURE_SW_CTRL,18,2,0x0);
	//pure_sw_dfs_frq_sel
	reg_bit_set(DFS_PURE_SW_CTRL, 8,3,0x0);
	//dmc_clk_init_sw_start
	reg_bit_set(DFS_CLK_INIT_SW_START, 0, 1,0x1);
	//wait done
	while((__raw_readl(DFS_CLK_STATE)&0x1) ==0 );
	//dmc_clk_init_sw_start clear
	reg_bit_set(DFS_CLK_INIT_SW_START, 0, 1,0x0);
	dmc_half_freq_mode_set();
}


void ddrc_dmc_timing_fn()
{
	u32 fn,i;
	if(dram_info.dram_type == DRAM_LP3)
	{
		dmc_dtmg=(DDRC_DMC_DTMG_T *)(&dmc_tmg_lp3[0]);
	}else
	{
		dmc_dtmg=(DDRC_DMC_DTMG_T *)(&dmc_tmg_lp4[0]);
	}
	for(fn=0;fn<dram_info.fn_max;fn++)
	{
        for(i=0; i<20 ;i++)
		    __raw_writel(DMC_CTL0_(0x0180+i*4+fn*0x60), ((u32*)(dmc_dtmg+fn))[i+4]);
	}
	if((dram_info.dram_type == DRAM_LP4))
	{
		for(fn=4;fn<dram_info.fn_max;fn++)
		{
#if defined(VRCG_ON_EN)
		switch(fn)
		{
		case 4:
			(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_768_DTMG1_RW;
			(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_768_DTMG13_RW;
			(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_768_DTMG14_RW;
			break;
		case 5:
			(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_933_DTMG1_RW;
			(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_933_DTMG13_RW;
			(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_933_DTMG14_RW;
			break;
		case 6:
			(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_1200_DTMG1_RW;
			(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_1200_DTMG13_RW;
			(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_1200_DTMG14_RW;
			break;
		case 7:
			(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_1333_DTMG1_RW;
			(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_1333_DTMG13_RW;
			(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_1333_DTMG14_RW;
			break;
		}
		__raw_writel(DMC_CTL0_(0x0184+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg1);
		__raw_writel(DMC_CTL0_(0x01b4+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg13);
		__raw_writel(DMC_CTL0_(0x01b8+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg14);
#else
			switch(fn)
			{
			case 4:
				(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_768_DTMG1_RW;
				(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_768_DTMG11_RW;
				(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_768_DTMG12_RW;
				break;
			case 5:
				(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_933_DTMG1_RW;
				(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_933_DTMG11_RW;
				(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_933_DTMG12_RW;
				break;
			case 6:
				(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_1200_DTMG1_RW;
				(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_1200_DTMG11_RW;
				(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_1200_DTMG12_RW;
				break;
			case 7:
				(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_1333_DTMG1_RW;
				(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_1333_DTMG11_RW;
				(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_1333_DTMG12_RW;
				break;
			}
			__raw_writel(DMC_CTL0_(0x0184+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg1);
			__raw_writel(DMC_CTL0_(0x01ac+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg11);
			__raw_writel(DMC_CTL0_(0x01b0+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg12);
#endif
		}
	}
}


void ddrc_dmc_lowpower_set()
{
	//dmc config
	reg_bit_set(DMC_CTL0_(0x0000), 8, 1,0x0);//rf_auto_sleep_en
	reg_bit_set(DMC_CTL0_(0x0124),12, 1,0x0);	//drf_ext_clk_ag_en
}

void ddrc_dmc_ctrl_set()
{
	//support different dram type
	reg_bit_set(DMC_CTL0_(0x0100), 8, 1,(dram_info.dram_type == DRAM_LP3)?0x1:0x0);//drf_data_width  0:x16/1:x32
	reg_bit_set(DMC_CTL0_(0x0100), 0, 1,(dram_info.dram_type == DRAM_LP3)?0x1:0x0);//drf_ch_pinmux_mode
	reg_bit_set(DMC_CTL0_(0x0000), 4, 3,(dram_info.dram_type == DRAM_LP3)?0x3:0x4);//rf_dburst_length
	reg_bit_set(DMC_CTL0_(0x0000),29, 1,(dram_info.dram_type == DRAM_LP3)?0x0:0x1);//rf_lpddr4_mode
	reg_bit_set(DMC_CTL0_(0x0100),20, 4,(dram_info.dram_type == DRAM_LP3)?0x1:0x3);//drf_dsoft_chn_sel
	//support different dram size
	reg_bit_set(DMC_CTL0_(0x0000), 0, 3,(dram_info.dram_type == DRAM_LP3)?0x7:0x6);//rf_cs_position
	reg_bit_set(DMC_CTL0_(0x0100), 4, 3,(dram_info.dram_type == DRAM_LP3)?0x3:0x2);//drf_column_mode
	//
	reg_bit_set(DMC_CTL0_(0x0100),17, 1,0x1);//drf_sample_auto_rst_en
	reg_bit_set(DMC_CTL0_(0x0100),11, 1,(dram_info.dram_type == DRAM_LP3)?0x0:0x1);//rf_data_ie_mode
	reg_bit_set(DMC_CTL0_(0x0100),12, 1,(dram_info.dram_type == DRAM_LP3)?0x0:0x1);//rf_data_oe_mode
	reg_bit_set(DMC_CTL0_(0x0144), 0, 4,(dram_info.dram_type == DRAM_LP3)?0x1:0x3);//rf_dmc_chnx_en
	//bit[13]:first4_dis bit[14]:last4_dis bit[15]:last8_dis
#if defined(VRCG_ON_EN)
	reg_bit_set(DMC_CTL0_(0x012c),13, 3,(dram_info.dram_type==DRAM_LP3)?0x5:0x5);
#else
	reg_bit_set(DMC_CTL0_(0x012c),13, 3,(dram_info.dram_type==DRAM_LP3)?0x5:0x0);
#endif
	//interleave size config
	ddrc_ctrl_interleave_init();
	//ddrc qos set
	ddrc_ctrl_qos_set();
}

void ddrc_phy_timing_fn()
{
	u32 fn=0,i;
	if(dram_info.dram_type == DRAM_LP3)
	{
		phy_tmg=(DDRC_PHY_TMG_T *)(&phy_tmg_lp3[0]);
	}else
	{
		phy_tmg=(DDRC_PHY_TMG_T *)(&phy_tmg_lp4[0]);
	}
	for(fn=0;fn<dram_info.fn_max;fn++)
	{
        for(i=0; i<16; i++)
		    __raw_writel(DMC_PHY0_(0x0040+i*4+fn*0xc0), ((u32*)(phy_tmg+fn))[i+2]);
        for(i=0; i<5; i++)
        {
		    __raw_writel(DMC_PHY0_(0x008c+i*4+fn*0xc0), ((u32*)(phy_tmg+fn))[i+18]);
		    __raw_writel(DMC_PHY0_(0x00ac+i*4+fn*0xc0), ((u32*)(phy_tmg+fn))[i+23]);
		    __raw_writel(DMC_PHY0_(0x00cc+i*4+fn*0xc0), ((u32*)(phy_tmg+fn))[i+28]);
        }
        for(i=0; i<3; i++)
		    __raw_writel(DMC_PHY0_(0x00ec+i*4+fn*0xc0), ((u32*)(phy_tmg+fn))[i+33]);
	}
	if((dram_info.dram_type == DRAM_LP4))
	{
		for(fn=4;fn<dram_info.fn_max;fn++)
		{
			switch(fn)
			{
			case 4:
				(phy_tmg+fn)->cfg5_tmg = DMC_PHY_LP4_768_DTMG5_RW;
				(phy_tmg+fn)->cfg_io_ds_cfg = DMC_PHY_LP4_768_DTMG45_RW;
				break;
			case 5:
				(phy_tmg+fn)->cfg5_tmg = DMC_PHY_LP4_933_DTMG5_RW;
				(phy_tmg+fn)->cfg_io_ds_cfg = DMC_PHY_LP4_933_DTMG45_RW;
				break;
			case 6:
				(phy_tmg+fn)->cfg5_tmg = DMC_PHY_LP4_1200_DTMG5_RW;
				(phy_tmg+fn)->cfg_io_ds_cfg = DMC_PHY_LP4_1200_DTMG45_RW;
				break;
			case 7:
				(phy_tmg+fn)->cfg5_tmg = DMC_PHY_LP4_1333_DTMG5_RW;
				(phy_tmg+fn)->cfg_io_ds_cfg = DMC_PHY_LP4_1333_DTMG45_RW;
				break;
			}
			__raw_writel(DMC_PHY0_(0x0054+fn*0xc0), (phy_tmg+fn)->cfg5_tmg);
			__raw_writel(DMC_PHY0_(0x00f4+fn*0xc0), (phy_tmg+fn)->cfg_io_ds_cfg);
		}
	}
}


void ddrc_phy_ctrl_set()
{
	reg_bit_set(DMC_PHY0_(0x0004),18, 1,(dram_info.dram_type == DRAM_LP3)?0x0:0x1);//rf_phy_lpddr4_mode
}

void ddrc_ds_set()
{
	u32 fn=0;
	switch(dram_info.dram_type)
	{
	case DRAM_LP3:
		ddrc_ca_ds_set(DDRC_CA_DS_LP3);
		ddrc_dq_ds_set(DDRC_DQ_DS_LP3);
		break;
	case DRAM_LP4:
		ddrc_ca_ds_set(DDRC_CA_DS_LP4);
		ddrc_dq_ds_set(DDRC_DQ_DS_LP4);
		for(fn=4;fn<dram_info.fn_max;fn++)
		{
			if(LP4_ODT_EN(fn)) {
				ddrc_dq_odt_set(fn,DDRC_DQ_ODT_LP4);
				dram_dq_odt_set(fn,DRAM_DQ_ODT_LP4);
			}
		}
		break;
	case DRAM_LP4X:
		ddrc_ca_ds_set(DDRC_CA_DS_LP4X);
		ddrc_dq_ds_set(DDRC_DQ_DS_LP4X);
		for(fn=4;fn<dram_info.fn_max;fn++)
		{
			if(LP4X_ODT_EN(fn)) {
				ddrc_dq_odt_set(fn,DDRC_DQ_ODT_LP4X);
				dram_dq_odt_set(fn,DRAM_DQ_ODT_LP4X);
			}
		}
		break;
	}
}


void ddrc_dbi_set(u32 current_clk)
{
	u32 fn;
	if(dram_info.dram_type == DRAM_LP3)
	{
		return;
	}
	//issue mr3@current frequency
	if(dram_info.dram_type == DRAM_LP4X)
	{
		dmc_dtmg->dram_mr3_data |=(RD_DBI_EN_LP4X<<6);
		dmc_dtmg->dram_mr3_data |=(WR_DBI_EN_LP4X<<7);
	}else
	{
		dmc_dtmg->dram_mr3_data |=(RD_DBI_EN_LP4<<6);
		dmc_dtmg->dram_mr3_data |=(WR_DBI_EN_LP4<<7);
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\nMR3 value:");
	print_Hex(dmc_dtmg->dram_mr3_data);
#endif
	dmc_mrw(DRAM_MR_3,DRAM_CS_ALL,dmc_dtmg->dram_mr3_data);
	for(fn=0;fn<dram_info.fn_max;fn++)
	{
		if(dram_info.dram_type == DRAM_LP4X)
		{
			(dmc_dtmg+fn)->dmc_dtmg4 |=(WR_DBI_EN_LP4X<<12);
			(dmc_dtmg+fn)->dmc_dtmg4 |=(RD_DBI_EN_LP4X<<13);
		}else
		{
			(dmc_dtmg+fn)->dmc_dtmg4 |=(WR_DBI_EN_LP4<<12);
			(dmc_dtmg+fn)->dmc_dtmg4 |=(RD_DBI_EN_LP4<<13);
		}
#if TEST_DEBUG_LOG_LEVEL>1
		dmc_print_str("\r\nWR/RD dbi status:");
		print_Hex((dmc_dtmg+fn)->dmc_dtmg4);
#endif
		__raw_writel(DMC_CTL0_(0x0190+0x60*fn),(dmc_dtmg+fn)->dmc_dtmg4);
	}
}

void ddrc_auto_refresh_open()
{
	//step3:enable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),15, 1,0x1);//auto pre bank refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//drf_auto_ref_en
}

void ddrc_master_dll_lock()
{
    u32 i=0;
    for(i=0; i<6; i++)
	    __raw_writel(DMC_PHY0_(0x0640+i*0x40), 0x3a118401);//cfg_dll_ac0
	//set rf_phy_init_start_ahb to high abd soc release dcc_rstn
	reg_bit_set(DMC_CTL0_(0x000c), 0,4,0xf);
	while(((__raw_readl(DMC_CTL0_(0x000c))>>16)&0xf) != 0xf);
	reg_bit_set(DMC_CTL0_(0x000c), 0,4,0x0);
}


void dmc_mrw(DRAM_MR_TYPE_E mr_num,DRAM_CS_TYPE_E cs_num,u32 mr_data)
{
	reg_bit_set(DMC_CTL0_(0x0108),0,8, mr_data);//drf_mode_reg_op
	reg_bit_set(DMC_CTL0_(0x0104),0,16,mr_num);//drf_mode_reg_a
	switch(cs_num)
	{
	case DRAM_CS_ALL:
		reg_bit_set(DMC_CTL0_(0x0104),31,1,0x1);
		break;
	case DRAM_CS_0:
		reg_bit_set(DMC_CTL0_(0x0104),31,1,0x0);
		reg_bit_set(DMC_CTL0_(0x0104),28,1,0x0);//dsoft_cs
		break;
	case DRAM_CS_1:
		reg_bit_set(DMC_CTL0_(0x0104),31,1,0x0);
		reg_bit_set(DMC_CTL0_(0x0104),28,1,0x1);//dsoft_cs
		break;
	default:while(1);
	}
	reg_bit_set(DMC_CTL0_(0x0104),24,1,0x1);//dsoft_mrw
	while(((__raw_readl(DMC_CTL0_(0x0104))>>19)&0x1ff) !=0);
}


int dmc_mrr(DRAM_MR_TYPE_E mr_num,DRAM_CS_TYPE_E cs_num,u32* mr_data)
{
	u32 mrr_valid[4]={0};
	//set mr num
	reg_bit_set(DMC_CTL0_(0x0104),0,16,mr_num);//drf_mode_reg_op
	//clear allcs
	reg_bit_set(DMC_CTL0_(0x0104),31, 1,0x0);//dsoft_cmd_allcs
	//set cs
	reg_bit_set(DMC_CTL0_(0x0104),28, 1,cs_num);//dsoft_cs
	//mr read cmd
	reg_bit_set(DMC_CTL0_(0x0104),25, 1,0x1);//dsoft_mrr
	while(((__raw_readl(DMC_CTL0_(0x0104))>>19)&0x1ff) !=0);
	mrr_valid[0]=(__raw_readl(DMC_CTL0_(0x00a0))>>12)&0x1;
	mrr_valid[1]=(__raw_readl(DMC_CTL0_(0x00a4))>>12)&0x1;
	mrr_valid[2]=(__raw_readl(DMC_CTL0_(0x00a8))>>12)&0x1;
	mrr_valid[3]=(__raw_readl(DMC_CTL0_(0x00ac))>>12)&0x1;
	if((mrr_valid[0]==0)&&(mrr_valid[1]==0)&&(mrr_valid[0]==0)&&(mrr_valid[0]==0))
	{
		return -1;
	}
	if(mrr_valid[0])
	{
		*mr_data = (__raw_readl(DMC_CTL0_(0x00b0)) & 0xff);
	}
	if(mrr_valid[1])
	{
		*mr_data |=((__raw_readl(DMC_CTL0_(0x00b0))>>16) & 0xff)<<8;
	}
	if(mrr_valid[2])
	{
		*mr_data |=(__raw_readl(DMC_CTL0_(0x00b4)) & 0xff)<<16;
	}
	if(mrr_valid[3])
	{
		*mr_data |=((__raw_readl(DMC_CTL0_(0x00b4))>>16) & 0xff)<<24;
	}
	return 0;
}

void dmc_mpc(u32 data,DRAM_CS_TYPE_E cs_num)
{
	reg_bit_set(DMC_CTL0_(0x0108), 0, 8,data);//drf_mode_reg_op
	switch(cs_num)
	{
	case DRAM_CS_ALL:
		reg_bit_set(DMC_CTL0_(0x0104),31,1,0x1);
		break;
	case DRAM_CS_0:
		reg_bit_set(DMC_CTL0_(0x0104),31,1,0x0);
		reg_bit_set(DMC_CTL0_(0x0104),28,1,0x0);//dsoft_cs
		break;
	case DRAM_CS_1:
		reg_bit_set(DMC_CTL0_(0x0104),31,1,0x0);
		reg_bit_set(DMC_CTL0_(0x0104),28,1,0x1);//dsoft_cs
		break;
	default:while(1);
	}
	reg_bit_set(DMC_CTL0_(0x0104),27,1,0x1);//dsoft_mpc
	while(((__raw_readl(DMC_CTL0_(0x0104))>>19)&0x1ff) !=0);
}

void dram_zqc_seq(u32 chn_num)
{
	reg_bit_set(DMC_CTL0_(0x0100),20,4,chn_num);
	if(dram_info.dram_type == DRAM_LP3)
	{
		dmc_mrw(DRAM_MR_10,DRAM_CS_0,0xff);
		wait_us(1);
		dmc_mrw(DRAM_MR_10,DRAM_CS_1,0xff);
		reg_bit_set(DMC_CTL0_(0x0100),20,4,1);
	}else
	{
		//rank0
		dmc_mpc(0x4f,DRAM_CS_0);
		wait_us(1);
		dmc_mpc(0x51,DRAM_CS_0);
		//rank1
		dmc_mpc(0x4f,DRAM_CS_1);
		wait_us(1);
		dmc_mpc(0x51,DRAM_CS_1);
		if(chn_num==2)
		{
			reg_bit_set(DMC_CTL0_(0x0100),20,4,0xf);
		}
	}
}


void lpddr3_powerup_seq(u32 fn)
{
	//step1:cke high
	reg_bit_set(DMC_CTL0_(0x0100),14,1,0x1);//drf_cke_output_high
	//tinit3
	wait_us(200);
	//step2:issue reset DRAM commad
	__raw_writel(DMC_CTL0_(0x0104),0x8100003f);
	//tinit5
	wait_us(10);
	//DRAM ZQ calibration
	dram_zqc_seq(1);
	wait_us(1);
	//issue mr2 data
	dmc_mrw(DRAM_MR_2,DRAM_CS_ALL,(dmc_dtmg+fn)->dram_mr2_data);
	//issue mr1 data
	dmc_mrw(DRAM_MR_1,DRAM_CS_ALL,(dmc_dtmg+fn)->dram_mr1_data);
}

void lpddr4_powerup_seq(u32 fn)
{
	//step 1:reset_n hold ---delay tINIT1 200us
	wait_us(200);
	//step 2:reset DRAM command---drf_ddr3_rst_out?å+
	reg_bit_set(DMC_CTL0_(0x0100),15, 1,0x1);
	//delay tInit3 2ms
	wait_us(2000);
	//setp 3:set cke high----drf_cke_output_high
	reg_bit_set(DMC_CTL0_(0x0100),14, 1,0x1);
	//issue MR2(WL/RL)/MR3/MR1/MR11
	//step4:issue mr2 data
	dmc_mrw(DRAM_MR_2,DRAM_CS_ALL,(dmc_dtmg+fn)->dram_mr2_data);
	//step5:issue mr3 data
	dmc_dtmg->dram_mr3_data &= ~(0x7<<3);
	if(dram_info.dram_type == DRAM_LP4X)
	{
		dmc_dtmg->dram_mr3_data |= (DRAM_DQ_DS_LP4X<<3);
	}else
	{
		dmc_dtmg->dram_mr3_data |= (DRAM_DQ_DS_LP4<<3);
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\nmr3 value:");
	print_Hex(dmc_dtmg->dram_mr3_data);
#endif
	dmc_mrw(DRAM_MR_3,DRAM_CS_ALL,dmc_dtmg->dram_mr3_data);
	//step6:issue mr1 data
	//dmc_mrw(DRAM_MR_1,DRAM_CS_ALL,(dmc_dtmg+fn)->dram_mr1_data);
	//step7:issule mr11 data odt
	dmc_dtmg->dram_mr22_data &= ~(0x7<<0);
	if(dram_info.dram_type==DRAM_LP4X)
	{
	#if (LP4X_ODT_EN(7)||LP4X_ODT_EN(6)||LP4X_ODT_EN(5)||LP4X_ODT_EN(4))
		dmc_dtmg->dram_mr22_data |=(DRAM_SOC_ODT_LP4X<<0);
	#endif
	}else
	{
	#if (LP4_ODT_EN(7)||LP4_ODT_EN(6)||LP4_ODT_EN(5)||LP4_ODT_EN(4))
		dmc_dtmg->dram_mr22_data |=(DRAM_SOC_ODT_LP4<<0);
	#else
		dmc_dtmg->dram_mr22_data &= ~(0x3f<<0);
	#endif
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\nmr22 value:");
	print_Hex(dmc_dtmg->dram_mr22_data);
#endif
	dmc_mrw(DRAM_MR_22,DRAM_CS_ALL,dmc_dtmg->dram_mr22_data);
	//step8:issue ZQ Start&Latch
	dram_zqc_seq(1);
	dram_zqc_seq(2);
}


void dram_powerup_seq(u32 fn)
{
	//rf_phy_sample_rst
	reg_bit_set(DMC_PHY0_(0x0004), 9, 1,0x1);//rf_phy_sample_rst
	reg_bit_set(DMC_PHY0_(0x0004), 9, 1,0x0);
	//enable auto resync
	reg_bit_set(DMC_PHY0_(0x0004),10, 1,0x1);//rf_phy_sample_auto_rst_en
	reg_bit_set(DMC_PHY0_(0x0004),19, 1,0x1);//rf_phy_io_ds_dqs_rpull_en
	if(dram_info.dram_type == DRAM_LP3)
	{
		lpddr3_powerup_seq(fn);
	}else
	{
		lpddr4_powerup_seq(fn);
	}
}

void ddrc_dmc_post_set()
{
	//step1:enable auto gate&auto sleep
	reg_bit_set(DMC_CTL0_(0x0000), 8, 2,0x3);//rf_auto_sleep_en/rf_auto_gate_en
	//step2:enable auto mr4
	reg_bit_set(DMC_CTL0_(0x0114),24, 2,0x0);//drf_auto_mr4_en
	reg_bit_set(DMC_CTL0_(0x0114), 0,23,0x0);//drf_t_mr4
	//step4:enable dfs
	reg_bit_set(DMC_CTL0_(0x012c), 0, 4,0xd);//drf_dfs_en
	//reg_bit_set(DMC_CTL0_(0x012c), 0, 1,0x1);//drf_dfs_en
	//reg_bit_set(DMC_CTL0_(0x012c), 1, 1,0x0);//drf_dfs_dll_rst_en
	//reg_bit_set(DMC_CTL0_(0x012c), 2, 1,0x1);//drf_dfs_cmd_mrw_en
	//reg_bit_set(DMC_CTL0_(0x012c), 3, 1,0x1);//drf_dfs_pll_lock_en
	reg_bit_set(DMC_CTL0_(0x012c),17, 1,0x1);//drf_dfs_clk_stop_en
	//step5:enable auto zqc
	reg_bit_set(DMC_CTL0_(0x0118),25,1,0x0);//drf_auto_zqc_allcs
	reg_bit_set(DMC_CTL0_(0x0118),26,2,0x0);//drf_auto_zq_sel
	//step6:enable auto cpst
	reg_bit_set(DMC_CTL0_(0x0144),16,1,0x1);//rf_period_cpst_en
	reg_bit_set(DMC_CTL0_(0x0144), 4,12,0x19);//drf_t_cpst--3.9us for cpst
	//step7:enable auto self-refresh
	reg_bit_set(DMC_CTL0_(0x0124), 0,3,0x5);//drf_auto_clk_stop_en
	reg_bit_set(DMC_CTL0_(0x0124),12,3,0x5);//drf_ext_clk_ag_en
	reg_bit_set(DMC_CTL0_(0x0124),16,3,0x7);//drf_ca_shutdown_en
}


/**************************sw dfs*****************************/
void sw_dfs_pre_set(u32 ddr_clk)
{
	u32 fn=0;
	dmc_freq_sel_search(ddr_clk,&fn);
	//close hw dfs enable
	reg_bit_set(DFS_HW_CTRL, 0, 1,0x0);//pub_dfs_hw_enbale
	//dmc clock init HW auto mode triggered by dfs req
	reg_bit_set(DMC_CLK_INIT_CFG, 0, 1,0x1);//dfs_clk_auto_mode
	//puresw to sw
	reg_bit_set(DFS_SW_CTRL,15, 7,(freq_info+fn)->ratio);//pub_dfs_sw_ratio_default
	reg_bit_set(DFS_SW_CTRL1,18, 2,(freq_info+fn)->clk_mode);//pub_dfs_sw_clk_mode_default
	reg_bit_set(DFS_SW_CTRL1, 8, 4,(freq_info+fn)->ratio_d2);//pub_dfs_sw_ratio_d2_default
	reg_bit_set(DFS_SW_CTRL, 4, 3,fn);//pub_dfs_sw_frq_sel
}

void sw_dfs_go(u32 fn)
{
	//pub_dfs_sw_ratio bit[2:0]000:DPLL0 010:26m 101:TWPLL-768m 110:TWPLL-1536M bit[6:3]:DPLL0 div value=N+1
	reg_bit_set(DFS_SW_CTRL, 8, 7,(freq_info+fn)->ratio);//pub_dfs_sw_ratio
	//pub_dfs_sw_clk_mode 00:pure bypass mode 01:deskew-pll mode 11:deskew-dll mode
	reg_bit_set(DFS_SW_CTRL1,16, 2,(freq_info+fn)->clk_mode);
	//pub_dfs_sw_ratio_d2 bit[1:0]:clk_x1_d2 select, 0:div0, 1:div2, 2:div4 bit[3:2]:clk_d2 select 0:div0, 1:div2, 2:div4
	reg_bit_set(DFS_SW_CTRL1, 0, 4,(freq_info+fn)->ratio_d2);
	reg_bit_set(DFS_SW_CTRL, 4, 3,fn);//pub_dfs_sw_frq_sel
	reg_bit_set(DFS_PURE_SW_CTRL,0,1,0x1);//dfs_sw_dfs_mode 1:software dfs mode 0:pure-software dfs mode
	reg_bit_set(DFS_SW_CTRL, 0, 1,0x1);//pub_dfs_sw_enable
	reg_bit_set(DFS_SW_CTRL, 1, 1,0x1);//pub_dfs_sw_req
	while(((__raw_readl(DFS_SW_CTRL)>>2)&0x1) == 0x0);//pub_dfs_sw_ack
	reg_bit_set(DFS_SW_CTRL, 1, 1,0x0);//pub_dfs_sw_req
}

void ddrc_train_seq(u32 ddr_mode,u32 train_top_clk)
{
	u32 bist_result;
	u32 fn,start_train_fn,end_train_fn,ddr_clk;
	u32 freq_sel=0;
	u32 debug_flag=(ddr_mode>>7)&0x1;
	start_train_fn=(dram_info.dram_type==DRAM_LP3)?LP3_TRAIN_START_FN:LP4_TRAIN_START_FN;
	if(dram_info.dram_type != DRAM_LP3)
	{
		ddrc_ctrl_interleave_set(INT_SIZE_256B);
	}
	for(fn=start_train_fn;fn<dram_info.fn_max;fn++)
	{
		ddr_clk=(freq_info+fn)->ddr_clk;
		if(train_top_clk < ddr_clk)
		{
			break;
		}
		if(0==((ddr_mode>>(8+fn))&0x1))
		{
			if(ddr_clk >= DDR_CLK_1200M)
			{
				if(train_top_clk != ddr_clk)
				{
					continue;
				}
				if(0==((ddr_mode>>13)&0x1))
				{
					dmc_freq_sel_search(DDR_CLK_768M,&freq_sel);
					sw_dfs_go(freq_sel);
				}
				if(ddr_clk==DDR_CLK_1333M)
				{
					//vddcore change to 800mv
					regulator_set_voltage("vddcore",900);
				}
				if(ddr_clk==DDR_CLK_1200M)
				{
					//vddcore change to 800mv
					regulator_set_voltage("vddcore",800);
				}
				//dpll cfg and relock
				dpll_cfg(ddr_clk);
			}
			dmc_phy_train(ddr_clk,debug_flag);
			dram_bist_test(0,0,2);
		}
	}
	if(dram_info.dram_type != DRAM_LP3)
	{
		ddrc_ctrl_interleave_set(INT_SIZE_128B);
	}
	return;
}
void pub_axi_port_lowpower_close()
{
	reg_bit_set(DDR_CHN_SLEEP_CTRL0,16,10,0x0);
}

void pub_lowpower_set()
{
	//AXI PORT lowpower enable
	reg_bit_set(DDR_CHN_SLEEP_CTRL0,16,10,0x3ff);
	//pub_sys auto light
	reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE,0,16,0xffff);
	//pub_sys smart light
	reg_bit_set(LIGHT_SLEEP_ENABLE,10,1,0x1);
	//sub_sys smart light bit[16]:ap,bit[17]:pubcp,bit[18]:wtlcp,bit[19]:audcp,bit[20]:aon
	reg_bit_set(LIGHT_SLEEP_ENABLE,16,5,0x1b);
	//pub_sys wait sleep cnt--CLK 4MHz=250ns
	reg_bit_set(DDR_SLP_WAIT_CNT,0,16,0x28);
}


void pub_acc_rdy_set()
{
	reg_bit_set(PUB_ACC_RDY, 0, 1,0x1);
}


void pmu_apb_state_set()
{
	//ddr_phy_cke_ret_en
	reg_bit_set(DDR_PHY_RET_CFG,0,1,0x1);
	//disable ddr phy retention
	reg_bit_set(DDR_OP_MODE_CFG,0,1,0x0);
}


void dram_init_from_low_freq(u32 ddr_clk)
{
	u32 fn;
	dmc_freq_sel_search(ddr_clk,&fn);
	//step1:close ddr auto sleep and gate clk enable
	ddrc_dmc_lowpower_set();
	//step2: ddrcphy regs config
	ddrc_phy_soft_reset();
	ddrc_phy_timing_fn();
	ddrc_phy_ctrl_set();
	ddrc_phy_soft_release();
	//step3:ddrc regs config
	ddrc_dmc_soft_reset();
	ddrc_dmc_timing_fn();
	ddrc_dmc_ctrl_set();
	ddrc_dmc_soft_release();
	//step4:ds cfg
	ddrc_ds_set();
	//step5:ddr clk cfg
	if(dram_info.dram_type == DRAM_LP3)
	{
		ddrc_clk_cfg(fn);
	}else
	{
		ddrc_clk_13m_cfg();
	}
	//step6:master dll lock
	ddrc_master_dll_lock();
	//step7:dram power sequence
	dram_powerup_seq(fn);
	if(dram_info.dram_type != DRAM_LP3)
	{
		ddrc_clk_cfg(fn);
	}
}


void ddrc_lock()
{
	//step8:enable dmc_rf wr lock
	__raw_writel(DMC_CTL0_(0x009c),0x0);
	__raw_writel(DMC_PHY0_(0x0ffc),0x0);
}

void ddrc_zqc_seq()
{
	u32 zqcal_flag,zqcal_val_a=0,zqcal_val_b=0;
	u32 zq_ncal=0,zq_pcal=0;
	#if 1
	reg_bit_set(DMC_PHY0_(0x0004),16, 1,(dram_info.dram_type == DRAM_LP3?0x0:0x1));//rf_phy_io_lpddr4x
	reg_bit_set(DMC_PHY0_(0),16,1,0x1);//rf_zq_cal_pwr_dn
	reg_bit_set(DMC_PHY0_(0),18,1,0x0);//rf_zq_cal_ncal_en
	reg_bit_set(DMC_PHY0_(0),17,1,0x0);//rf_zq_cal_pcal_en
	reg_bit_set(DMC_PHY0_(0),12,4,0xf);//rf_zq_cal_pu_sel
	reg_bit_set(DMC_PHY0_(0), 8,4,0x0);//rf_zq_cal_pd_sel
	reg_bit_set(DMC_PHY0_(0),16,1,0x0);//rf_zq_cal_pwr_dn
	wait_us(20);
	/***start pmos zq calibration****/
	reg_bit_set(DMC_PHY0_(0),17,1,0x1);//rf_zq_cal_pcal_en
	wait_us(20);
	zqcal_flag=(__raw_readl(DMC_PHY0_(0))>>20)&0x1;
	zqcal_val_a=(__raw_readl(DMC_PHY0_(0))>>12)&0xf;
	if(zqcal_flag == 0x0){
		while(1){
			zqcal_val_a=(__raw_readl(DMC_PHY0_(0))>>12)&0xf;
			zqcal_val_a-=1;
			reg_bit_set(DMC_PHY0_(0),12,4,zqcal_val_a);//rf_zq_cal_pu_sel
			wait_us(20);
			zqcal_flag=(__raw_readl(DMC_PHY0_(0))>>20)&0x1;
			if(zqcal_flag==1){
				break;
			}
			if(zqcal_val_a ==0x0){
				//zq cal fail
				dmc_print_str("\r\nDec PCAL fail");
			}
		}
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\npuio dec directions:");
	print_Dec(zqcal_val_a);
#endif
	reg_bit_set(DMC_PHY0_(0),12,4,0x0);//rf_zq_cal_pu_sel
	wait_us(20);
	zqcal_flag=(__raw_readl(DMC_PHY0_(0))>>20)&0x1;
	if(zqcal_flag == 0x1)
	{
		while(1){
			zqcal_val_b=(__raw_readl(DMC_PHY0_(0))>>12)&0xf;
			zqcal_val_b+=1;
			reg_bit_set(DMC_PHY0_(0),12,4,zqcal_val_b);//rf_zq_cal_pu_sel
			wait_us(10);
			zqcal_flag=(__raw_readl(DMC_PHY0_(0))>>20)&0x1;
			if(zqcal_flag==0){
				break;
			}
			if(zqcal_val_b ==0xf){
				//zq cal fail
				dmc_print_str("\r\nInc PCAL fail");
				if(zqcal_val_a == 0xf)
				{
					dmc_print_str("\r\nnot 240ohm");
				}
			}
		}
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\npuio inc directions:");
	print_Dec(zqcal_val_b);
#endif
	if(zqcal_val_a > zqcal_val_b)
	{
		if((zqcal_val_a-zqcal_val_b)<=3)
		{
			zq_pcal=(zqcal_val_a+zqcal_val_b)/2;
		}else
		{
			dmc_print_str("\r\ndelat P > 4");
			while(1);
		}
	}else
	{
		if((zqcal_val_b-zqcal_val_a)<=3)
		{
			zq_pcal=(zqcal_val_a+zqcal_val_b)/2;
		}else
		{
			dmc_print_str("\r\ndelat N > 4");
			while(1);
		}

	}
	reg_bit_set(DMC_PHY0_(0),17,1,0x0);//rf_zq_cal_pcal_en
	wait_us(20);
	/***start nmos zq calibration****/
	reg_bit_set(DMC_PHY0_(0),18,1,0x1);//rf_zq_cal_ncal_en
	wait_us(10);
	zqcal_flag=(__raw_readl(DMC_PHY0_(0))>>21)&0x1;
	if(zqcal_flag == 0x0){
		while(1){
			zqcal_val_a=(__raw_readl(DMC_PHY0_(0))>>8)&0xf;
			zqcal_val_a+=1;
			reg_bit_set(DMC_PHY0_(0), 8,4,zqcal_val_a);//rf_zq_cal_pd_sel
			wait_us(10);
			zqcal_flag=(__raw_readl(DMC_PHY0_(0))>>21)&0x1;
			if(zqcal_flag==1){
				break;
			}
			if(zqcal_val_a ==0xf){
				//zq cal fail
				dmc_print_str("Inc NCAL fail");
			}
		}
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\npdio inc directions:");
	print_Dec(zqcal_val_a);
#endif
	reg_bit_set(DMC_PHY0_(0), 8,4,0xf);//rf_zq_cal_pd_sel
	wait_us(20);
	zqcal_flag=(__raw_readl(DMC_PHY0_(0))>>21)&0x1;
	if(zqcal_flag == 0x1){
		while(1){
			zqcal_val_b=(__raw_readl(DMC_PHY0_(0))>>8)&0xf;
			zqcal_val_b-=1;
			reg_bit_set(DMC_PHY0_(0), 8,4,zqcal_val_b);//rf_zq_cal_pd_sel
			wait_us(10);
			zqcal_flag=(__raw_readl(DMC_PHY0_(0))>>21)&0x1;
			if(zqcal_flag==0){
				break;
			}
			if(zqcal_val_b ==0x0){
				//zq cal fail
				dmc_print_str("\r\nDec NCAL fail");
			}
		}
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\npdio dec directions:");
	print_Dec(zqcal_val_b);
#endif
	if(zqcal_val_a > zqcal_val_b)
	{
		if((zqcal_val_a-zqcal_val_b)<=3)
		{
			zq_ncal=(zqcal_val_a+zqcal_val_b)/2;
		}else
		{
			dmc_print_str("\r\ndelta N > 4");
			while(1);
		}
	}else
	{
		if((zqcal_val_b-zqcal_val_a)<=3)
		{
			zq_ncal=(zqcal_val_a+zqcal_val_b)/2;
		}else
		{
			dmc_print_str("\r\ndelta P > 4");
			while(1);
		}

	}
	reg_bit_set(DMC_PHY0_(0),18,1,0x0);//rf_zq_cal_pcal_en
	reg_bit_set(DMC_PHY0_(0),16,1,0x1);//rf_zq_cal_pwr_dn
	if(zq_ncal<=1)
	{
		reg_bit_set(DMC_PHY0_(0),0,4,0x8);//rf_zq_cal_pdio_sel
	}else
	{
		reg_bit_set(DMC_PHY0_(0),0,4,zq_ncal);//rf_zq_cal_pdio_sel
	}
	if(zq_pcal>=0xe)
	{
		reg_bit_set(DMC_PHY0_(0),4,4,0xb);//rf_zq_cal_puio_sel
	}else
	{
		reg_bit_set(DMC_PHY0_(0),4,4,zq_pcal);//rf_zq_cal_puio_sel
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\nzq_cal_puio_sel:");
	print_Dec(zq_pcal);
	dmc_print_str("\r\nzq_cal_pdio_sel:");
	print_Dec(zq_ncal);
#endif
	#else
	reg_bit_set(DMC_PHY0_(0x0004),16, 1,(dram_info.dram_type == DRAM_LP3?0x0:0x1));//rf_phy_io_lpddr4x
	reg_bit_set(DMC_PHY0_(0),0,4,0x8);//rf_zq_cal_pdio_sel
	reg_bit_set(DMC_PHY0_(0),4,4,0xb);//rf_zq_cal_puio_sel
	#endif
}


void ddrc_debug_mode(u32 mode,u32 top_freq)
{
	u32 chip_id =__raw_readl(CHIP_VERSION_ID);
	u32 dram_info_val=(((dram_info.dram_type>>4)&0xf)+(dram_info.dram_type&0xf))
						|(dram_info.cs_num<<4);
	//Send information to kernel
	__raw_writel(DDR_INIT_DEBUG_ADDR+0x8,dram_info_val);
#if defined(CONFIG_NAND_SPL)
	__raw_writel(DDR_INIT_DEBUG_ADDR+0xc,dram_info.mr_reg_cs0);
	__raw_writel(DDR_INIT_DEBUG_ADDR+0x10,dram_info.mr_reg_cs1);
	//dfs enable,0x1:disable
	__raw_writel(DDR_DFS_DEBUG_ADDR+0x4,(mode>>0)&0x1);
	//control vddcore 0.8v@cm4,0x1:750mv
	if((top_freq == DDR_CLK_1200M)&&(chip_id != 0))
	{
		__raw_writel(DDR_DFS_DEBUG_ADDR+0xc,800);
	}else
	{
		__raw_writel(DDR_DFS_DEBUG_ADDR+0xc,750);
	}
	//top freq
	__raw_writel(DDR_INIT_DEBUG_ADDR+0x20,top_freq);
	if(top_freq == DDR_CLK_1333M)
	{
		__raw_writel(DDR_DFS_DEBUG_ADDR+0xc,900);
	}
	switch(dram_info.dram_type)
	{
		case DRAM_LP3:
			//mask DDR frequency points,0x1:masked
			__raw_writel(DDR_DFS_DEBUG_ADDR+0x8,(((mode>>8)&0xff)|0xc8));
			break;
		case DRAM_LP4:
			//mask DDR frequency points,0x1:masked
			__raw_writel(DDR_DFS_DEBUG_ADDR+0x8,(((mode>>8)&0xff)|0x08));
			break;
		case DRAM_LP4X:
			//mask DDR frequency points,0x1:masked
			__raw_writel(DDR_DFS_DEBUG_ADDR+0x8,(((mode>>8)&0xff)|0x08));
			break;
		default:while(1);
	}
	//lightsleep disable
	if((mode>>4)&0x1)
	{
		reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE,0,1,0x0);
		__raw_writel(DDR_REINIT_DEBUG_ADDR+0x4,0x1);
	}
	//deepsleep disable
	if((mode>>5)&0x1)
	{
		__raw_writel(DDR_REINIT_DEBUG_ADDR+0x8,0x1);
	}
#endif
}


void wdg_rst_keep_sre()
{
	if((0x5e486947 == __raw_readl(CHIP_RESET_CONTROL_KEY))
		&&((__raw_readl(CHIP_RESET_CONTROL_STATUS)&0x3) == 0x3))
	{
		//magic key
		__raw_writel(CHIP_RESET_CONTROL_STATUS,0x19790000);
	}else
	{
		//magic key
		__raw_writel(CHIP_RESET_CONTROL_STATUS,0x19790000);
		//magic key,bit[15:12]:clk_32k_div_load:div clock to 32k/2^(CLK_DIV)
		//bit[1:0]:enable forec sre/sleep bit[0]:force_sleep_en,bit[1]:force_sre_en
		__raw_writel(CHIP_RESET_CONTROL_ENABLE,0x6A393003);
		//unreset register, enable wdg detect
		__raw_writel(CHIP_RESET_CONTROL_KEY, 0x5e486947);
	}
}

void ddrc_reboot_cnt()
{
	u32 val=0;
	if(__raw_readl(DDR_REBOOT_FLAG)!=0x12345678)
	{
		__raw_writel(DDR_REBOOT_FLAG,0x12345678);
		__raw_writel(DDR_REBOOT_CNT, 0x1);
	}else
	{
		val=__raw_readl(DDR_REBOOT_CNT);
		val+=1;
		__raw_writel(DDR_REBOOT_CNT, val);
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\nDDR Reboot Times:");
	print_Hex(__raw_readl(DDR_REBOOT_CNT));
#endif
}

void ddrc_target_point_set(u32* target_ddr_clk,u32 train_high_clk)
{
	u32 fn_val=0;
	if((*target_ddr_clk) <=train_high_clk)
	{
		if(*target_ddr_clk!=train_high_clk)
		{
			if(train_high_clk>=DDR_CLK_1200M)
			{
				dmc_freq_sel_search(DDR_CLK_768M, &fn_val);
				sw_dfs_go(fn_val);
				//vddcore change to 750mv
				regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core.value);
				//dpll cfg and relock
				dpll_cfg(DDR_CLK_1866M);
				if(*target_ddr_clk!=DDR_CLK_768M)
				{
					//dfs to 933m
					dmc_freq_sel_search(*target_ddr_clk, &fn_val);
					sw_dfs_go(fn_val);
				}
				}else
				{
					dmc_freq_sel_search(*target_ddr_clk, &fn_val);
					sw_dfs_go(fn_val);
				}
		}
	}
	else
	{
		*target_ddr_clk=train_high_clk;
	}

	/*DDR init target point print*/
	dmc_print_str("\r\nddr target freq:0x");
	print_Hex(*target_ddr_clk);
	dmc_print_str("MHz");
}

void sdram_init()
{
	#if defined(CONFIG_NAND_SPL) ||  defined(DDR_SCAN_ENABLE)
	u32 target_ddr_clk=(mcu_clk_para.ddr_freq.value)/1000000;
	//u32 target_ddr_clk=DDR_CLK_933M;
	u32 ddr_mode=mcu_clk_para.ddr_debug_mode.value;
	//u32 ddr_mode=0x0080;
	#else
	u32 target_ddr_clk=BOOT_FREQ_POINT;
	u32 ddr_mode=0x0800;
	#endif
	u32 train_high_point=DDR_CLK_933M;


#if defined(AUTO_SLT_EN)
	__raw_writel(UART1_TX_BUF_ADDR+0x24,0xa94);
	dmc_print_str("\r\nREV:SHARKL5_ASLT_A100    \r\n");
#endif

	/*DDR init start*/
	dmc_print_str("ddr init start");

	/*PMU status settinig*/
	//pmu_apb_state_set();

	/*axi port clk always on*/
	pub_axi_port_lowpower_close();

#ifdef DDR_SCAN_ENABLE
	u32 freq_index;
	/*pub soft rst*/
	reg_bit_set((PMU_APB_BASE_ADDR + 0xB0),6,1,1);
	wait_us(10);
	reg_bit_set((PMU_APB_BASE_ADDR + 0xB0),6,1,0);

	/*cust scan use fdl1,so set default freq to 933,if need 384 scan delete this code*/
	if(target_ddr_clk < DDR_CLK_512M)
		target_ddr_clk = DDR_CLK_933M;
	scan_target_clk = target_ddr_clk;
	if(first_init == 2)
	{
		dmc_freq_sel_search(target_ddr_clk, &freq_index);
		if(target_ddr_clk >= DDR_CLK_512M)
			ddr_mode = 0x7F00 & (~(1 << (freq_index + 8)));
	}
#endif
	/*dram type setting*/
	dram_type_pinmux_auto_detect();

	/*watchdog reset entry into sre*/
	wdg_rst_keep_sre();

	/*zq calibration*/
	ddrc_zqc_seq();

	/*pinmux setting*/
	ddrc_phy_pinmux_set();

	/*dram init at a low frequency*/
	dram_init_from_low_freq(BOOT_FREQ_POINT);

	/*dram size auto-detect*/
	dram_size_auto_detect();

	/*DFS pre setting,from pure sw dfs to sw dfs*/
	sw_dfs_pre_set(BOOT_FREQ_POINT);

	/**dram freq auto-detect*/
	dram_freq_auto_detect(&train_high_point);

	/*training flow*/
	ddrc_train_seq(ddr_mode,train_high_point);

	/*target frequency point*/
	ddrc_target_point_set(&target_ddr_clk, train_high_point);

	/*ssc cfg*/
#if defined(CONFIG_NAND_SPL) && defined(SSC_CFG)
	pll_ssc_cfg(target_ddr_clk,(ddr_mode>>16)&0xff);
#endif

	/*open mr4*/
	ddrc_auto_refresh_open();

#ifdef DDR_SCAN_ENABLE
	if(first_init == 0)
		first_init = 1;
	else
		return ;
	ddr_scan_offline_r2p0(target_ddr_clk);
#else

	/*bist test*/
#if defined(CONFIG_NAND_SPL)
	dram_bist_test(0,0,2);
#endif

	/*dbi setting*/
	//ddrc_dbi_set(target_ddr_clk);

	/*
	*ddr init end
	*1.ddrc lowpower
	*3.mr4 function
	*4.dfs function
	*5.auto cpst
	*6.auto zqc
	*/
	ddrc_dmc_post_set();

	/*pub_sys clk auto gate*/
	pub_lowpower_set();

	/*set pub_acc_rdy to make other subsys access*/
	pub_acc_rdy_set();

#ifdef DDR_POWER_TEST
	power_consumption_measure_entry();
#endif

#ifdef DRAM_MEM_TEST
	/***memtest***/
	//dram_mem_test(0x80000000,0xc0000000);
#endif

	/****send ddr size to kernel ****/
	dmc_update_param_for_uboot();

#if defined(CONFIG_NAND_SPL)
	/*watch dog reset*/
	ddrc_reboot_cnt();
#ifdef WDG_TEST
	start_watchdog(5);
#endif
#endif
	/*ddr debug mode---AON IRAM Addr
      AP:0x00003000-0x000043ff
      CM4:0x20001000-0x200023ff
    */
	ddrc_debug_mode(ddr_mode,train_high_point);

	dmc_print_str("\r\nddr init end\r\n");
	ddrc_lock();
#endif
}




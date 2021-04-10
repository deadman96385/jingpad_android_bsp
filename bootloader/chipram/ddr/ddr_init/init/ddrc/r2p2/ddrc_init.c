#include <asm/arch/clk_para_config.h>
#include "ddrc_init.h"
#include "ddrc_feature_init.h"
#include "dram_support.h"
#include "dram_test.h"
#include "lpddr4_ctl_timing.h"
#include "lpddr4_phy_timing.h"
#include <packet.h>
extern PACKET_T  *packet[ PACKET_MAX_NUM ];




extern DDRC_DMC_DTMG_T dmc_tmg_lp3[];
extern DDRC_DMC_DTMG_T dmc_tmg_lp4[];
extern DDRC_PHY_TMG_T phy_tmg_lp3[];
extern DDRC_PHY_TMG_T phy_tmg_lp4[];
extern DDRC_FREQ_INFO_T ddrc_freq_info[];
extern void dmc_phy_train_lp3();

DRAM_INFO_T dram_info;
DDRC_DMC_DTMG_T *dmc_dtmg;
DDRC_PHY_TMG_T *phy_tmg;

//dfs para
//Set this pointer in the dram_type_pinmux_auto_detect according to dram type
DDRC_FREQ_INFO_T  * freq_info;

#ifdef DDR_SCAN_ENABLE
#define dmc_print_str(x) NULL
#define print_Hex(x) NULL
int first_init = 0;
u32 scan_target_clk = 0;
#endif

void dpll_cfg(u32 ddr_clk)
{
	u32 nint_val=0,kint_val=0,dpll_icp=0;
	/***set div_s***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 0,1,0x1);

	/***set sdm_en***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 1,1,0x1);
	switch(ddr_clk)
	{
	case DDR_CLK_1866M:
		nint_val=0x47;kint_val=0x627627;dpll_icp=0x5;break;
	case DDR_CLK_1333M:
		nint_val=0x33;kint_val=0x227627;dpll_icp=0x3;break;
	}
	/***set nint and kint***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL2,23,7,nint_val);
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL2,0,23,kint_val);
	/***set dpll_icp***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 4,3,dpll_icp);
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
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 0,2,0x3);
	/***set div_s***/
	//reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 0,1,0x1);

	/***set sdm_en***/
	//reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL0, 1,1,0x1);

	/***set mod_en***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL3, 3,1,0x1);

	/***PLL_CSS_CTRL***/
	reg_bit_set(ANALOG_DPLL_TOP_DPLL_CTRL3, 4,8,css_val);
}

int dmc_freq_sel_search(u32 ddr_clk,u32* fn)
{
	*fn=0xffffffff;
	if(dram_info.dram_type==DRAM_LP3)
	{
		switch (ddr_clk)
		{
			case 933:*fn=0x5;break;
			case 768:*fn=0x4;break;
			case 622:*fn=0x3;break;
			case 512:*fn=0x2;break;
			case 384:*fn=0x1;break;
			case 256:*fn=0x0;break;
			default:
				while(1);
				return -1;
		}

	}else//LPDDR4 and LPDDR4X
	{
	switch (ddr_clk)
		{
		case 1866:*fn=0x7;break;
		case 1536:*fn=0x6;break;
		case 1333:*fn=0x5;break;
		case 1024:*fn=0x4;break;
		case 768:*fn=0x3;break;
		case 512:*fn=0x2;break;
		case 384:*fn=0x1;break;
		case 256:*fn=0x0;break;
		default:
			while(1);
			return -1;
		}
	}
	return 0;
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
	reg_bit_set(DMC_CTL0_(0x012c), 4, 3,fn);//drf_dfs_reg_sel-This fileds select the timming parameter
	reg_bit_set(DMC_CTL0_(0x012c), 4, 3,fn);//drf_dfs_reg_sel
	pure_sw_dfs_go(fn);
	//dmc_half_freq_mode_set();//Timming include this step
}

void ddrc_dmc_timing_fn()
{
	u32 fn,i;
	u32 *pvalue;
	if(dram_info.dram_type == DRAM_LP3)
	{
		dmc_dtmg=(DDRC_DMC_DTMG_T *)(&dmc_tmg_lp3[0]);
	}else
	{
		dmc_dtmg=(DDRC_DMC_DTMG_T *)(&dmc_tmg_lp4[0]);
	}
	for(fn=0;fn<dram_info.fn_max;fn++)
	{
		pvalue=&((dmc_dtmg+fn)->dmc_dtmg0);
		for(i=0;i<20;i++)
		{
			__raw_writel(DMC_CTL0_(0x0180+0x4*i+fn*0x60),(*(pvalue++)));
		}
		/*
		__raw_writel(DMC_CTL0_(0x0180+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg0);
		__raw_writel(DMC_CTL0_(0x0184+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg1);
		__raw_writel(DMC_CTL0_(0x0188+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg2);
		__raw_writel(DMC_CTL0_(0x018c+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg3);
		__raw_writel(DMC_CTL0_(0x0190+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg4);
		__raw_writel(DMC_CTL0_(0x0194+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg5);
		__raw_writel(DMC_CTL0_(0x0198+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg6);
		__raw_writel(DMC_CTL0_(0x019c+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg7);
		__raw_writel(DMC_CTL0_(0x01a0+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg8);
		__raw_writel(DMC_CTL0_(0x01a4+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg9);
		__raw_writel(DMC_CTL0_(0x01a8+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg10);
		__raw_writel(DMC_CTL0_(0x01ac+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg11);
		__raw_writel(DMC_CTL0_(0x01b0+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg12);
		__raw_writel(DMC_CTL0_(0x01b4+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg13);
		__raw_writel(DMC_CTL0_(0x01b8+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg14);
		__raw_writel(DMC_CTL0_(0x01bc+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg15);
		__raw_writel(DMC_CTL0_(0x01c0+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg16);
		__raw_writel(DMC_CTL0_(0x01c4+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg17);
		__raw_writel(DMC_CTL0_(0x01c8+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg18);
		__raw_writel(DMC_CTL0_(0x01cc+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg19);
		*/
		#ifdef DDR_SCAN_ENABLE
		__raw_writel(DMC_CTL0_(0x01ac+fn*0x60),0x0b000b00);
		__raw_writel(DMC_CTL0_(0x01b0+fn*0x60),0x163d0e5d);
		#endif
	}
	if((dram_info.dram_type == DRAM_LP4))
	{
		for(fn=4;fn<dram_info.fn_max;fn++)
		{
			switch(fn)
			{
			case 3://768
				(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_768_DTMG1_LP4;
				(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_768_DTMG11_LP4;
				(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_768_DTMG12_LP4;
				break;
			case 4://1024
				(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_1024_DTMG1_LP4;
				(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_1024_DTMG11_LP4;
				(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_1024_DTMG12_LP4;
				break;
			case 5://1333
				(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_1333_DTMG1_LP4;
				(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_1333_DTMG11_LP4;
				(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_1333_DTMG12_LP4;
				break;
			case 6://1536
				(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_1536_DTMG1_LP4;
				(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_1536_DTMG11_LP4;
				(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_1536_DTMG12_LP4;
				break;
			case 7://1866
				(dmc_dtmg+fn)->dmc_dtmg1 = DMC_LP4_1866_DTMG1_LP4;
				(dmc_dtmg+fn)->dmc_dtmg11 = DMC_LP4_1866_DTMG11_LP4;
				(dmc_dtmg+fn)->dmc_dtmg12 = DMC_LP4_1866_DTMG12_LP4;
				break;
			}
			__raw_writel(DMC_CTL0_(0x0184+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg1);
			__raw_writel(DMC_CTL0_(0x01ac+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg11);
			__raw_writel(DMC_CTL0_(0x01b0+fn*0x60), (dmc_dtmg+fn)->dmc_dtmg12);
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
	int type_is_lp3 = 0;
	if(dram_info.dram_type == DRAM_LP3)
		type_is_lp3 = 1;
	//support different dram type
	reg_bit_set(DMC_CTL0_(0x0100), 8, 1,(type_is_lp3)?0x1:0x0);//drf_data_width  0:x16/1:x32
	reg_bit_set(DMC_CTL0_(0x0100), 0, 1,(type_is_lp3)?0x1:0x0);//drf_ch_pinmux_mode,0:Ch0->PHY0,CH1->PHY1...  1:ch0->phy0&phy1...
	reg_bit_set(DMC_CTL0_(0x0000), 4, 3,(type_is_lp3)?0x3:0x4);//rf_dburst_length:LP3:8*32bit  LP4:16*32bit
	reg_bit_set(DMC_CTL0_(0x0000),29, 1,(type_is_lp3)?0x0:0x1);//rf_lpddr4_mode 1:LPDDR4 0:others
	reg_bit_set(DMC_CTL0_(0x0100),20, 4,(type_is_lp3)?0x1:0x3);//drf_dsoft_chn_sel,Select Enable DMC Channel(0x1:Enable channel 0 ,0X3:Enable channel 0 and channel 1 )
	//support different dram size
	reg_bit_set(DMC_CTL0_(0x0000), 0, 3,(type_is_lp3)?0x7:0x6);//rf_cs_position
	reg_bit_set(DMC_CTL0_(0x0100), 4, 3,(type_is_lp3)?0x3:0x2);//drf_column_mode
	//
	reg_bit_set(DMC_CTL0_(0x0100),17, 1,0x1);//drf_sample_auto_rst_en
	reg_bit_set(DMC_CTL0_(0x0100),11, 1,(type_is_lp3)?0x0:0x1);//rf_data_ie_mode,0:CS0 &CS1 with same dfs_rddata_en 1:different dfi_rddata_en
	reg_bit_set(DMC_CTL0_(0x0100),12, 1,(type_is_lp3)?0x0:0x1);//rf_data_oe_mode,0:CS0 &CS1 with same dfs_wrdata_en 1:different dfi_wrdata_en
	reg_bit_set(DMC_CTL0_(0x0144), 0, 4,(type_is_lp3)?0x1:0x3);//rf_dmc_chnx_en,1:Enable dmem ch0 3:Enable dmem ch0 & ch1

	//bit[12]:drf_dfs_cmd_fsp_en bit[13]:first4_dis bit[14]:last4_dis bit[15]:last8_dis
	//DMC Max send 16 MRW in dfs ,This mr seperate 4 group,every group include 4 MR
	//This three bit control Send 4 group enable or disable during dfs
	reg_bit_set(DMC_CTL0_(0x012c),12, 4,(type_is_lp3)?0xA:0x5);//LP3:Close send mrw durring DFS LP4:Enable send mrw durring DFS
	//interleave size config
	ddrc_ctrl_interleave_init();//64Byte all interleave
	//ddrc qos set
#if defined(CONFIG_NAND_SPL)
	ddrc_ctrl_qos_set();
#endif
}

void ddrc_phy_timing_fn()
{
	u32 fn=0;
	u32 num=0;
	u32* pPhyValue;
	if(dram_info.dram_type == DRAM_LP3)
	{
		phy_tmg=(DDRC_PHY_TMG_T *)(&phy_tmg_lp3[0]);
	}else
	{
		phy_tmg=(DDRC_PHY_TMG_T *)(&phy_tmg_lp4[0]);
	}
	for(fn=0;fn<dram_info.fn_max;fn++)
	{
		//0x40~0x7c
		pPhyValue=(&((phy_tmg+fn)->cfg0_tmg));
		for(num=0;num<16;num++)
		{
			__raw_writel(DMC_PHY0_((0x0040+0x4*num)+fn*0xc0),(*(pPhyValue++)));//0x40~0x7c
		}
		for(num=0;num<3;num++)
		{
			__raw_writel(DMC_PHY0_(0x008c+0x20*num+fn*0xc0),(*(pPhyValue++)));
			__raw_writel(DMC_PHY0_(0x0090+0x20*num+fn*0xc0),(*(pPhyValue++)));
			__raw_writel(DMC_PHY0_(0x0094+0x20*num+fn*0xc0),(*(pPhyValue++)));
			__raw_writel(DMC_PHY0_(0x0098+0x20*num+fn*0xc0),(*(pPhyValue++)));
			__raw_writel(DMC_PHY0_(0x009c+0x20*num+fn*0xc0),(*(pPhyValue++)));
		}
		for(num=0;num<3;num++)
		{
			__raw_writel(DMC_PHY0_((0x00ec+0x4*num)+fn*0xc0),(*(pPhyValue++)));//0x8c~0xDc
		}
		/*
		__raw_writel(DMC_PHY0_(0x0040+fn*0xc0), (phy_tmg+fn)->cfg0_tmg);
		__raw_writel(DMC_PHY0_(0x0044+fn*0xc0), (phy_tmg+fn)->cfg1_tmg);
		__raw_writel(DMC_PHY0_(0x0048+fn*0xc0), (phy_tmg+fn)->cfg2_tmg);
		__raw_writel(DMC_PHY0_(0x004c+fn*0xc0), (phy_tmg+fn)->cfg3_tmg);
		__raw_writel(DMC_PHY0_(0x0050+fn*0xc0), (phy_tmg+fn)->cfg4_tmg);
		__raw_writel(DMC_PHY0_(0x0054+fn*0xc0), (phy_tmg+fn)->cfg5_tmg);
		__raw_writel(DMC_PHY0_(0x0058+fn*0xc0), (phy_tmg+fn)->cfg6_tmg);
		__raw_writel(DMC_PHY0_(0x005c+fn*0xc0), (phy_tmg+fn)->cfg7_tmg);
		__raw_writel(DMC_PHY0_(0x0060+fn*0xc0), (phy_tmg+fn)->cfg8_tmg);
		__raw_writel(DMC_PHY0_(0x0064+fn*0xc0), (phy_tmg+fn)->cfg_dll_ac0_dl_0);
		__raw_writel(DMC_PHY0_(0x0068+fn*0xc0), (phy_tmg+fn)->cfg_dll_ac1_dl_0);
		__raw_writel(DMC_PHY0_(0x006c+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds0_dl_0);
		__raw_writel(DMC_PHY0_(0x0070+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds0_dl_1);
		__raw_writel(DMC_PHY0_(0x0074+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds0_dl_2);
		__raw_writel(DMC_PHY0_(0x0078+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds0_dl_3);
		__raw_writel(DMC_PHY0_(0x007c+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds0_dl_4);

		__raw_writel(DMC_PHY0_(0x008c+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds1_dl_0);
		__raw_writel(DMC_PHY0_(0x0090+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds1_dl_1);
		__raw_writel(DMC_PHY0_(0x0094+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds1_dl_2);
		__raw_writel(DMC_PHY0_(0x0098+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds1_dl_3);
		__raw_writel(DMC_PHY0_(0x009c+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds1_dl_4);

		__raw_writel(DMC_PHY0_(0x00ac+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds2_dl_0);
		__raw_writel(DMC_PHY0_(0x00b0+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds2_dl_1);
		__raw_writel(DMC_PHY0_(0x00b4+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds2_dl_2);
		__raw_writel(DMC_PHY0_(0x00b8+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds2_dl_3);
		__raw_writel(DMC_PHY0_(0x00bc+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds2_dl_4);

		__raw_writel(DMC_PHY0_(0x00cc+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds3_dl_0);
		__raw_writel(DMC_PHY0_(0x00d0+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds3_dl_1);
		__raw_writel(DMC_PHY0_(0x00d4+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds3_dl_2);
		__raw_writel(DMC_PHY0_(0x00d8+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds3_dl_3);
		__raw_writel(DMC_PHY0_(0x00dc+fn*0xc0), (phy_tmg+fn)->cfg_dll_ds3_dl_4);

		__raw_writel(DMC_PHY0_(0x00ec+fn*0xc0), (phy_tmg+fn)->cfg_dskpll_cfg0);
		__raw_writel(DMC_PHY0_(0x00f0+fn*0xc0), (phy_tmg+fn)->cfg_dskpll_cfg1);
		__raw_writel(DMC_PHY0_(0x00f4+fn*0xc0), (phy_tmg+fn)->cfg_io_ds_cfg);
		*/
	}
	/*If dram type == LP4,Change DQS TIMMING and IO configure in High Freq*/
	if((dram_info.dram_type == DRAM_LP4))
	{
		/*3~7:768,1024,1333,1536,1866*/
		for(fn=3;fn<dram_info.fn_max;fn++)
		{
			switch(fn)
			{
			case 3://768
				(phy_tmg+fn)->cfg5_tmg = DMC_PHY_LP4_768_DTMG5_LP4;
				(phy_tmg+fn)->cfg_io_ds_cfg = DMC_PHY_LP4_768_DTMG45_LP4;
				break;
			case 4://1024
				(phy_tmg+fn)->cfg5_tmg = DMC_PHY_LP4_1024_DTMG5_LP4;
				(phy_tmg+fn)->cfg_io_ds_cfg = DMC_PHY_LP4_1024_DTMG45_LP4;
				break;
			case 5://1333
				(phy_tmg+fn)->cfg5_tmg = DMC_PHY_LP4_1333_DTMG5_LP4;
				(phy_tmg+fn)->cfg_io_ds_cfg = DMC_PHY_LP4_1333_DTMG45_LP4;
				break;
			case 6://1536
				(phy_tmg+fn)->cfg5_tmg = DMC_PHY_LP4_1536_DTMG5_LP4;
				(phy_tmg+fn)->cfg_io_ds_cfg = DMC_PHY_LP4_1536_DTMG45_LP4;
				break;
			case 7://1866
				(phy_tmg+fn)->cfg5_tmg = DMC_PHY_LP4_1866_DTMG5_LP4;
				(phy_tmg+fn)->cfg_io_ds_cfg = DMC_PHY_LP4_1866_DTMG45_LP4;
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

void ddrc_ds_odt_set()
{
	u32 fn=0;
	switch(dram_info.dram_type)
	{
	case DRAM_LP3:
		ddrc_ca_ds_set(DDRC_CA_DS_LP3);
		ddrc_dq_ds_set(DDRC_DQ_DS_LP3);
		break;
	case DRAM_LP4:
		ddrc_ca_ds_set(DDRC_CA_DS_LP4);//driver strenth
		ddrc_dq_ds_set(DDRC_DQ_DS_LP4);
		for(fn=4;fn<dram_info.fn_max;fn++)//ODT:fn=4:1024
		{
		if(LP4_ODT_EN(fn)==1)
		{
			ddrc_dq_odt_set(fn,DDRC_DQ_ODT_LP4);
			dram_dq_odt_set(fn,DRAM_DQ_ODT_LP4);
		}
		if(LP4_CA_ODT_EN(fn)==1)
			dram_ca_odt_set(fn,DRAM_CA_ODT_LP4);
		}
		break;
	case DRAM_LP4X:
		ddrc_ca_ds_set(DDRC_CA_DS_LP4X);
		ddrc_dq_ds_set(DDRC_DQ_DS_LP4X);
		for(fn=4;fn<dram_info.fn_max;fn++)//fn=4:1024
		{
		if(LP4X_ODT_EN(fn)==1)
		{
			//ddrc_dq_odt_set(fn,DDRC_DQ_ODT_LP4X);
			//dram_dq_odt_set(fn,DRAM_DQ_ODT_LP4X);
		}
		if( LP4X_CA_ODT_EN(fn)==1)
			dram_ca_odt_set(fn,DRAM_CA_ODT_LP4X);
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
	//all freq same to dmc_dtmg->dram_mr3_data
	for(fn=0;fn<dram_info.fn_max;fn++)
	{
		if(dram_info.dram_type == DRAM_LP4X)
		{
			(dmc_dtmg+fn)->dram_mr3_data |=(RD_DBI_EN_LP4X<<6);
			(dmc_dtmg+fn)->dram_mr3_data |=(WR_DBI_EN_LP4X<<7);
		}else
		{
			(dmc_dtmg+fn)->dram_mr3_data |=(RD_DBI_EN_LP4<<6);
			(dmc_dtmg+fn)->dram_mr3_data |=(WR_DBI_EN_LP4<<7);
		}
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\nMR3 value:");
	print_Hex(dmc_dtmg->dram_mr3_data);
#endif
	/*****Write other MR=1 group*****/
	//After training set wr=1,so this func set wr=0
	reg_bit_set(DMC_CTL0_(0x10c),12,1,0x0);//disable auto refresh
	dmc_mrw(DRAM_MR_13,DRAM_CS_ALL,0x40);//WR=1
	dmc_mrw(DRAM_MR_3,DRAM_CS_ALL,dmc_dtmg->dram_mr3_data);
	dmc_mrw(DRAM_MR_13,DRAM_CS_ALL,0x0);//WR=0
	dmc_mrw(DRAM_MR_3,DRAM_CS_ALL,dmc_dtmg->dram_mr3_data);
	dmc_mrw(DRAM_MR_13,DRAM_CS_ALL,0x40);//wr=1 op=0
	reg_bit_set(DMC_CTL0_(0x10c),12,1,0x1);//Enable auto refresh
	/*Setting for soc*/
	for(fn=0;fn<dram_info.fn_max;fn++)
	{
		if(dram_info.dram_type == DRAM_LP4X)
		{
			//Set SOC Read and Write DBI EN/DISEN
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
/*Close dbi for all freq Befor training seq*/
void ddrc_dbi_close()
{
	u32 fn;

		for(fn=0;fn<dram_info.fn_max;fn++)
		{
			if(dram_info.dram_type != DRAM_LP3)
			{
				//Set SOC Read and Write DBI EN/DISEN
				(dmc_dtmg+fn)->dmc_dtmg4 &=(~(0x1<<12));
				(dmc_dtmg+fn)->dmc_dtmg4 &=(~(0x1<<13));
			}
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
	u32 num=0;
	for(num=0;num<6;num++)
		{
			__raw_writel(DMC_PHY0_(0x0640+num*0x40), 0x3a118401);//cfg_dll_acx
		}
	/*
	__raw_writel(DMC_PHY0_(0x0640), 0x3a118401);//cfg_dll_ac0
	__raw_writel(DMC_PHY0_(0x0680), 0x3a118401);//cfg_dll_ac1
	__raw_writel(DMC_PHY0_(0x06c0), 0x3a118401);//cfg_dll_ds0
	__raw_writel(DMC_PHY0_(0x0700), 0x3a118401);//cfg_dll_ds1
	__raw_writel(DMC_PHY0_(0x0740), 0x3a118401);//cfg_dll_ds2
	__raw_writel(DMC_PHY0_(0x0780), 0x3a118401);//cfg_dll_ds3
	*/
	//set rf_phy_init_start_ahb to high abd soc release dcc_rstn
	reg_bit_set(DMC_CTL0_(0x000c), 0,4,0xf);
	while(((__raw_readl(DMC_CTL0_(0x000c))>>16)&0xf) != 0xf);//wait dfi init complete
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
	dmc_mrw(DRAM_MR_2,DRAM_CS_ALL,(dmc_dtmg+fn)->dram_mr2_data);//read latency and write latency
	//issue mr1 data
	dmc_mrw(DRAM_MR_1,DRAM_CS_ALL,(dmc_dtmg+fn)->dram_mr1_data);//set clock cycles with start internal precharge operation
}

void lpddr4_powerup_seq(u32 fn)
{
	u32 fn_loop=0;
	//step 1:reset_n hold ---delay tINIT1 200us
	wait_us(200);
	//step 2:reset DRAM command---drf_ddr3_rst_out
	reg_bit_set(DMC_CTL0_(0x0100),15, 1,0x1);
	//delay tInit3 2ms
	wait_us(2000);
	//setp 3:set cke high----drf_cke_output_high
	reg_bit_set(DMC_CTL0_(0x0100),14, 1,0x1);

	//issue MR2(WL/RL)/MR3/MR1/MR11
	//step4:issue mr2 data(read/write latency)
	dmc_mrw(DRAM_MR_2,DRAM_CS_ALL,(dmc_dtmg+fn)->dram_mr2_data);

	//step5:issue mr3 data(PU-CAL\WR PST\Post Package\PDDS\DBI)
	for(fn_loop=0;fn_loop<dram_info.fn_max;fn_loop++)
	{
		(dmc_dtmg+fn_loop)->dram_mr3_data &= ~(0x7<<3);//Set write latency
		if(dram_info.dram_type == DRAM_LP4X)
		{
			(dmc_dtmg+fn_loop)->dram_mr3_data |= (DRAM_DQ_DS_LP4X<<3);//all freq same MR3
		}else
		{
			(dmc_dtmg+fn_loop)->dram_mr3_data |= (DRAM_DQ_DS_LP4<<3);
		}
}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\nmr3 value:");
	print_Hex(dmc_dtmg->dram_mr3_data);
#endif
	dmc_mrw(DRAM_MR_3,DRAM_CS_ALL,(dmc_dtmg+fn)->dram_mr3_data);

	//step6:issule mr22 data odt and update Global value
	//Tell DRAM SOC ODT in Mr22
	for(fn_loop=0;fn_loop<dram_info.fn_max;fn_loop++)
	{
		//Update Global Variable dram_mr22_data
		(dmc_dtmg+fn_loop)->dram_mr22_data &= ~(0x7<<0);
		//Update FSP Parameter for dmc_dtmg12
		(dmc_dtmg+fn_loop)->dmc_dtmg12 &= ~(0x7<<16);
		if(dram_info.dram_type==DRAM_LP4X)
		{
			(dmc_dtmg+fn_loop)->dram_mr22_data |=(DRAM_SOC_ODT_LP4X<<0);

			(dmc_dtmg+fn_loop)->dmc_dtmg12 |=(DRAM_SOC_ODT_LP4X<<16);
		}else
		{
			(dmc_dtmg+fn_loop)->dram_mr22_data |=(DRAM_SOC_ODT_LP4<<0);

			(dmc_dtmg+fn_loop)->dmc_dtmg12 |=(DRAM_SOC_ODT_LP4<<16);
		}
		//write variable in register
		__raw_writel(DMC_CTL0_(0x01b0+fn_loop*0x60), (dmc_dtmg+fn_loop)->dmc_dtmg12);
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\nmr22 value:");
	print_Hex(dmc_dtmg->dram_mr22_data);
#endif
	//dmc_mrw(DRAM_MR_22,DRAM_CS_ALL,(dmc_dtmg+fn)->dram_mr22_data);//set mr22-odt value
	//step8:issue ZQ Start&Latch
	dram_zqc_seq(1);//cal dram odt
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
	reg_bit_set(DMC_CTL0_(0x0000), 8, 2,0x3);//rf_auto_sleep_en
	//reg_bit_set(DMC_CTL0_(0x0000), 9, 1,0x1);//rf_auto_gate_en
	//step2:enable auto mr4
	reg_bit_set(DMC_CTL0_(0x0114), 0,26,0x0);//drf_t_mr4
/*	reg_bit_set(DMC_CTL0_(0x0114),24, 2,0x0);//drf_auto_mr4_en
	//reg_bit_set(DMC_CTL0_(0x0114),25, 1,0x0);//drf_auto_mr4_allcs
	reg_bit_set(DMC_CTL0_(0x0114), 0,23,0x0);//drf_t_mr4
*/
	//step4:enable dfs
	reg_bit_set(DMC_CTL0_(0x012c), 0, 4,0xD);//drf_dfs_en
	/*
	reg_bit_set(DMC_CTL0_(0x012c), 1, 1,0x0);//drf_dfs_dll_rst_en
	reg_bit_set(DMC_CTL0_(0x012c), 2, 1,0x1);//drf_dfs_cmd_mrw_en
	reg_bit_set(DMC_CTL0_(0x012c), 3, 1,0x1);//drf_dfs_pll_lock_en
	*/
	reg_bit_set(DMC_CTL0_(0x012c),17, 1,0x1);//drf_dfs_clk_stop_en
	//step5:enable auto zqc
	reg_bit_set(DMC_CTL0_(0x0118),25,2,0x0);//drf_auto_zqc_allcs
	//reg_bit_set(DMC_CTL0_(0x0118),26,2,0x0);//drf_auto_zq_sel
	//step6:enable auto cpst
	reg_bit_set(DMC_CTL0_(0x0144),16,1,0x1);//rf_period_cpst_en
	reg_bit_set(DMC_CTL0_(0x0144), 4,12,0x19);//drf_t_cpst--3.9us for cpst
	//step7:enable auto self-refresh
	reg_bit_set(DMC_CTL0_(0x0124), 0,3,0x5);//drf_auto_clk_stop_en
	reg_bit_set(DMC_CTL0_(0x0124),12,3,0x5);//drf_ext_clk_ag_en
	reg_bit_set(DMC_CTL0_(0x0124),16,3,0x7);//drf_ca_shutdown_en
	/*
	reg_bit_set(DMC_CTL0_(0x0124), 0,1,0x1);//drf_auto_clk_stop_en
	reg_bit_set(DMC_CTL0_(0x0124), 1,1,0x0);//drf_auto_pwr_down_en
	reg_bit_set(DMC_CTL0_(0x0124), 2,1,0x1);//drf_auto_self_ref_en
	reg_bit_set(DMC_CTL0_(0x0124),12,1,0x1);//drf_ext_clk_ag_en
	reg_bit_set(DMC_CTL0_(0x0124),13,1,0x0);//drf_auto_pwr_down_percs_en
	reg_bit_set(DMC_CTL0_(0x0124),14,1,0x1);//drf_auto_self_ref_percs_en
	reg_bit_set(DMC_CTL0_(0x0124),16,1,0x1);//drf_ca_shutdown_en
	reg_bit_set(DMC_CTL0_(0x0124),17,1,0x1);//drf_cs_shutdown_en
	reg_bit_set(DMC_CTL0_(0x0124),18,1,0x1);//drf_ck_shutdown_en
	*/
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
	u32 fn,start_train_fn,end_train_fn,ddr_clk;
	u32 freq_sel=0;

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
			if(ddr_clk >= DDR_CLK_1333M)/*Deal with Special freq dfs */
			{
				/*Transform VDDCORE*/
				if(ddr_clk==DDR_CLK_1333M)
				{
					//vddcore change to 800mv
					regulator_set_voltage("vddcore",800);
				}
				if(ddr_clk>=DDR_CLK_1536M)
				{
					//vddcore change to 900mv
					regulator_set_voltage("vddcore",900);
				}
				//1866 need dpll cfg and relock
				if(ddr_clk==DDR_CLK_1866M)
					{
						if(0==((ddr_mode>>12)&0x1))//F4:1024
						{
							dmc_freq_sel_search(DDR_CLK_1024M,&freq_sel);/*1024 is Intermediate frequency point */
							sw_dfs_go(freq_sel);
							sw_dfs_go(freq_sel);
							dpll_cfg(ddr_clk);//convert dll source
						}else
						{
							dmc_print_str("Error:ddr_mode for 1024 freq is disable");
							continue;
						}
					}

			}
			dmc_phy_train(ddr_clk);
			dram_bist_specific_space_init();
		}
	}
	if(dram_info.dram_type != DRAM_LP3)
	{
		ddrc_ctrl_interleave_set(INT_SIZE_128B);
	}

#if (!defined(CONFIG_NAND_SPL) && defined(CONFIG_PACKET_USB_FIX_ADDR))
/*
 pls check:
 //pls check 1,sizeof(dmc_phy_train_lp3)<sizeof(PACKET_T)+64) ?
 //pls check 2,sizeof(phy_tmg_lp4)<sizeof(PACKET_T)+64) ?
 //pls check 3,sizeof(phy_tmg_lp3)<sizeof(PACKET_T)+64) ?
 2020.1.15:
 map:
 dmc_phy_train_lp3 start/size : 0x92f8/0x630
 phy_tmg_lp4 start/size: 0x12f38/0x480
 phy_tmg_lp3 start/size: 0x12bd8/0x360
 MAX_PKT_SIZE is 0x300
 sizeof(PACKET_T) is 0x318
 uart log:
 packet[0]:0x00009300
 packet[1]:0x00012F40
 packet[2]:0x00012C00
*/
	packet[0] = (PACKET_T*)((((u32)dmc_phy_train_lp3+0x3f)>>6)<<6);
	packet[1] = (PACKET_T*)((((u32)phy_tmg_lp4+0x3f)>>6)<<6);
	packet[2] = (PACKET_T*)((((u32)phy_tmg_lp3+0x3f)>>6)<<6);

#if (PACKET_MAX_NUM!=3) || (MAX_PKT_SIZE!=0x300)
#error  pls don't change PACKET_MAX_NUM or MAX_PKT_SIZE
#endif

#if TEST_DEBUG_LOG_LEVEL>0
	dmc_print_str("\r\n packet:\r\n");
	print_Hex(packet[0]);
	dmc_print_str("\r\n");
	print_Hex(packet[1]);
	dmc_print_str("\r\n");
	print_Hex(packet[2]);
	dmc_print_str("\r\n");
	print_Hex(sizeof(PACKET_T));
	dmc_print_str("\r\n");
	print_Hex(MAX_PKT_SIZE);
#endif
#endif
	return;
}
void pub_axi_port_lowpower_close()
{
	reg_bit_set(DDR_CHN_SLEEP_CTRL0,16,10,0x0);//Disable lowpower mode
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
	reg_bit_set(DDR_SLP_WAIT_CNT,0,16,0x80);
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
	ddrc_phy_timing_fn();//set phy parameter (include default odt(DTMG45,ODT and DS))
	ddrc_phy_ctrl_set();//LP4 MODE set
	ddrc_phy_soft_release();
	//step3:ddrc regs config
	ddrc_dmc_soft_reset();
	ddrc_dmc_timing_fn();//configure dmc timming
	ddrc_dmc_ctrl_set();//configure dmc parameter for dram type
	ddrc_dmc_soft_release();
	//step4:ds cfg--set driver strenth and odt (include soc odt and dram odt)
	//dq ODT:This step main set ODT value or close odt . Sync  PHY_DTMG7[20:17] If you  want open odt
	//ca odt depend on define LP4X_CA_ODT_EN_FN
	ddrc_ds_odt_set();
	//step5:ddr clk cfg---change clk
	ddrc_clk_cfg(fn);
	//step6:master dll lock
	ddrc_master_dll_lock();
	//step7:dram power sequence
	dram_powerup_seq(fn);
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
#if 1 //if 0 disable zqc and set manual value
	reg_bit_set(DMC_PHY0_(0x00f4),24,8,0x50);
	reg_bit_set(DMC_PHY0_(0x00f4),23,1,0x0);
	reg_bit_set(DMC_PHY0_(0x0004),16, 1,(dram_info.dram_type == DRAM_LP3?0x0:0x1));//rf_phy_io_lpddr4x

	reg_bit_set(DMC_PHY0_(0),16,3,0x01);
	/*reg_bit_set(DMC_PHY0_(0),16,1,0x1);//rf_zq_cal_pwr_dn--power
	reg_bit_set(DMC_PHY0_(0),18,1,0x0);//rf_zq_cal_ncal_en
	reg_bit_set(DMC_PHY0_(0),17,1,0x0);//rf_zq_cal_pcal_en
	*/
	reg_bit_set(DMC_PHY0_(0),12,4,0xf);//rf_zq_cal_pu_sel   scope:0xf~0x0
	reg_bit_set(DMC_PHY0_(0), 8,4,0x0);//rf_zq_cal_pd_sel
	reg_bit_set(DMC_PHY0_(0),16,1,0x0);//rf_zq_cal_pwr_dn
	wait_us(20);
	/************start pmos zq calibration*************/
	//ZQC PCAL Start from the top
	reg_bit_set(DMC_PHY0_(0),17,1,0x1);//rf_zq_cal_pcal_en
	wait_us(20);
	zqcal_flag=(__raw_readl(DMC_PHY0_(0))>>20)&0x1;//pcal complete flag
	zqcal_val_a=(__raw_readl(DMC_PHY0_(0))>>12)&0xf;/*Read value didn't  care*/
	if(zqcal_flag == 0x0){
		while(1){
			/***********************************************************
			*Loop adjust pu sel(Decrease) and detect PCAL Complete flag
			* if Complete flag ==1 pu cal complete otherwise fail
			***********************************************************/
			zqcal_val_a=(__raw_readl(DMC_PHY0_(0))>>12)&0xf;//PU driver strenth adjustment
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
				while(1);
			}

		}
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\npuio dec directions:");
	print_Hex(zqcal_val_a);
#endif
	//ZQC PCAL Start from the bottom
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
				while(1);
			}
		}
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\npuio inc directions:");
	print_Hex(zqcal_val_b);
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
	/************start nmos zq calibration*************/
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
				while(1);
			}
		}
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\npdio inc directions:");
	print_Hex(zqcal_val_a);
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
				while(1);
			}
		}
	}
#if TEST_DEBUG_LOG_LEVEL>1
	dmc_print_str("\r\npdio dec directions:");
	print_Hex(zqcal_val_b);
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
	reg_bit_set(DMC_PHY0_(0),18,1,0x0);//rf_zq_cal_ncal_en
	reg_bit_set(DMC_PHY0_(0),16,1,0x1);//rf_zq_cal_pwr_dn-This bit is used to power down ZQ calibration circuit

	/*Judge ZQC result and if the result not in normal range Set Manual value*/
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
#if TEST_DEBUG_LOG_LEVEL>0
	dmc_print_str("\r\nzq_cal_puio_sel:");
	print_Hex(zq_pcal);
	dmc_print_str("\r\nzq_cal_pdio_sel:");
	print_Hex(zq_ncal);
#endif
#else
	reg_bit_set(DMC_PHY0_(0x0004),16, 1,(dram_info.dram_type == DRAM_LP3?0x0:0x1));//rf_phy_io_lpddr4x
	reg_bit_set(DMC_PHY0_(0),0,4,0xa);//rf_zq_cal_pdio_sel
	reg_bit_set(DMC_PHY0_(0),4,4,0xa);//rf_zq_cal_puio_sel
#endif
}

void ctl_sram_param_set(u32 val)
{
	u32 val_r=0;
	val=0x1e0;
	sprd_djtag_mux_sel(0x7,0x0);
	dmc_print_str("\r\ndjtag wr val:");
	print_Hex(val);
	sprd_djtag_write(0xa,10,val);
	val_r=sprd_djtag_read(0xa,10);
	dmc_print_str("\r\ndjtag rd val:");
	print_Hex(val_r);
}
/*
*Send kernel and dfs information through iram
*/
void ddrc_debug_mode(u32 mode,u32 top_freq)
{
	u32 chip_id =__raw_readl(CHIP_VERSION_ID);
	u32 dram_info_val=(((dram_info.dram_type>>4)&0xf)+(dram_info.dram_type&0xf))
						|(dram_info.cs_num<<4);//lp3:0x3,LP4:0x4,LP4X:0x5
	//Send information to kernel
	__raw_writel(DDR_INIT_DEBUG_ADDR+0x8,dram_info_val);
	__raw_writel(DDR_INIT_DEBUG_ADDR+0xc,dram_info.mr_reg_cs0);
	__raw_writel(DDR_INIT_DEBUG_ADDR+0x10,dram_info.mr_reg_cs1);
	//dfs enable,0x1:disable
	__raw_writel(DDR_DFS_DEBUG_ADDR+0x4,(mode>>0)&0x1);
	//control vddcore 0.8v@cm4,0x1:750mv
	if(((top_freq == DDR_CLK_1866M)||(top_freq == DDR_CLK_1536M))&&(chip_id != 0))
	{
		__raw_writel(DDR_DFS_DEBUG_ADDR+0xc,900);
	}else if((top_freq == DDR_CLK_1333M)&&(chip_id != 0))
	{
		__raw_writel(DDR_DFS_DEBUG_ADDR+0xc,800);
	}
	else
	{
		__raw_writel(DDR_DFS_DEBUG_ADDR+0xc,750);
	}
	//top freq
	__raw_writel(DDR_INIT_DEBUG_ADDR+0x20,top_freq);
//	if(top_freq == DDR_CLK_1866M)
//	{
//		__raw_writel(DDR_DFS_DEBUG_ADDR+0xc,900);
//	}
	switch(dram_info.dram_type)
	{
		case DRAM_LP3:
			//mask DDR frequency points,0x1:masked
			__raw_writel(DDR_DFS_DEBUG_ADDR+0x8,(((mode>>8)&0xff)|0xc8));//0xc8:Mask freq point for dfs
			break;
		case DRAM_LP4:
			//mask DDR frequency points,0x1:masked
			__raw_writel(DDR_DFS_DEBUG_ADDR+0x8,(((mode>>8)&0xff)|0x0));//0x8:Mask freq point for dfs
			break;
		case DRAM_LP4X:
			//mask DDR frequency points,0x1:masked
			__raw_writel(DDR_DFS_DEBUG_ADDR+0x8,(((mode>>8)&0xff)|0x0));//0x8:Mask freq point for dfs
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
	if((dram_info.dram_type==DRAM_LP3) && (*target_ddr_clk > train_high_clk))
			*target_ddr_clk = train_high_clk;
	/*Project include File "CLK_DDR_FREQ" value and dram_type mismatch*/
	if(dmc_freq_sel_search(*target_ddr_clk, &fn_val) !=0 )
		{
			//dmc_print_str("\r\nError:CLK_DDR_FREQ and dram_type mismatch.So contain Training High point\r\n");
			*target_ddr_clk=train_high_clk;

			return ;
	}

	if((*target_ddr_clk) < train_high_clk)
	{
			if(train_high_clk >= DDR_CLK_1333M)
			{
				if(train_high_clk ==DDR_CLK_1866M)
					{
						/*conver Intermediate frequency point*/
						dmc_freq_sel_search(DDR_CLK_1024M, &fn_val);
						sw_dfs_go(fn_val);
						/*dpll cfg and relock*/
						dpll_cfg(DDR_CLK_1333M);
					}
				/*change voltage except 1536M*/
				if(*target_ddr_clk ==DDR_CLK_1333M )
					{
						//vddcore change to default 800mv
						regulator_set_voltage("vddcore",800);
				}else if(*target_ddr_clk !=DDR_CLK_1536M)
					{
						//vddcore change to default 750mv
						regulator_set_voltage("vddcore",mcu_clk_para.dcdc_core.value);
					}
				if(*target_ddr_clk!=DDR_CLK_1024M)
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
	else
	{
		*target_ddr_clk=train_high_clk;
	}

	/*DDR init target point print*/
	dmc_print_str("\r\nddr target freq:");
	print_Hex(*target_ddr_clk);
	dmc_print_str("MHz");
}
void ddr_init_pass()
{
	dmc_print_str("\r\nddr init end pass!!!\r\n");
}
void reboot_times()
{
	u32 num=0;
	u32 num1=0;
	u32 flag=0;

	flag=__raw_readl(0x28);
	if(flag!=0xaaaaaaaa)
	{
		__raw_writel(0x28,0xaaaaaaaa);
		__raw_writel(0x20,0);
		__raw_writel(0x24,0);
	}
	num=__raw_readl(0x20);
	num=num+1;
	if(num==0xffffffff)
	{
		num=0;
		num1=__raw_readl(0x24);
		num1=num1+1;
		__raw_writel(0x24,num1);
	}
	__raw_writel(0x20,num);
}
void print_tdqs2dq(u32 high_value,u32 low_value,u32 cs_num)
{
	u32 value=0;
	u32 flag=0;
	u32 max=0;
	u32 min=0;

	u32 max_addr=0;
	u32 min_addr=0;

	high_value=((high_value << 8)&0xff00)|(low_value&0xff);
	dmc_print_str("ch0 cs");
	print_Hex(cs_num);
	dmc_print_str(" tdqs2dq =");
	value=((1024*1000*1000)/(BOOT_FREQ_POINT*high_value))/2;
	print_Hex(value);
	dmc_print_str("ps\r\n");
	//Save IRAM
	if(cs_num==0)//cs 0
	{
		max_addr=0x20;
		min_addr=0x24;
	}else
	{
		max_addr=0x28;
		min_addr=0x2c;
	}
	flag=__raw_readl(0x30);
	if(flag!=0xaaaaaaaa)
	{
		__raw_writel(0x30,0xaaaaaaaa);
		__raw_writel(0x20,value);//cs0
		__raw_writel(0x24,value);
		__raw_writel(0x28,value);//cs1
		__raw_writel(0x2c,value);
	}
	max=__raw_readl(max_addr);
	min=__raw_readl(min_addr);
	if(value>max)
	{
		__raw_writel(max_addr,value);
	}else if(value < min)
	{
		__raw_writel(min_addr,value);
	}
}
void dram_get_tdqs2dq()
{
	u32 high_value=0,low_value=0;
	reg_bit_set(DMC_CTL0_(0x100),20,4,0x1);
	dmc_mrw(DRAM_MR_23,DRAM_CS_0,0x3f);//1024 cycle
	//start dqs osc
	dmc_mpc(0x4b,DRAM_CS_0);
	wait_us(10);
	//stop dqs osc
	dmc_mrr(DRAM_MR_18,DRAM_CS_0,&low_value);
	dmc_mrr(DRAM_MR_19,DRAM_CS_0,&high_value);
	print_tdqs2dq(high_value,low_value,0);

	dmc_mrw(DRAM_MR_23,DRAM_CS_1,0x3f);//1024 cycles
	//start dqs osc
	dmc_mpc(0x4b,DRAM_CS_1);
	wait_us(10);

	dmc_mrr(DRAM_MR_18,DRAM_CS_1,&low_value);
	dmc_mrr(DRAM_MR_19,DRAM_CS_1,&high_value);
	print_tdqs2dq(high_value,low_value,1);
	reg_bit_set(DMC_CTL0_(0x100),20,4,0xf);
}
void loop_get_tdqs2dq()
{
	while(1)
	{
		dram_get_tdqs2dq();
		wait_us(1000);
	}
}
/**************************************************************************
*LP4:1866(F7) 1536(F6) 1333(F5) 1024(F4) 768(F3)  512(F2) 384(F1) 256(F0)
*LP3                           :933      768    622 512 384 256
*ddr_mode:
  Control training freq start bit:8 (0:Enable 1:Disable)
  LP4:bit8~bit15:F0~F7
  LP3:bit8~bit13:F0~F5
*target_ddr_clk:Target DDR frequency
*train_high_point :Training Top DDR frequency (according ddr_mode set this variable)
***************************************************************************/
uint32 scan_bist;
void sdram_init()
{
	dmc_print_str("\r\nSHARKL5pro ddr init...\r\n");
	u32 train_high_point=0;/*Training High freq point*/
	u32 target_ddr_clk=(mcu_clk_para.ddr_freq.value)/1000000;
	//u32 target_ddr_clk=DDR_CLK_1024M;
	u32 ddr_mode=mcu_clk_para.ddr_debug_mode.value;
	//u32 ddr_mode=0xe300;

#if defined(CONFIG_CHIPRAM_DDR_MAX_FREQ)
	//mask DDR frequency points,0x1:masked
	ddr_mode |= (1 << 15);
#endif

#if defined(AUTO_SLT_EN)
	__raw_writel(UART1_TX_BUF_ADDR+0x24,0xa94);
	dmc_print_str("\r\nREV:SHARKL5pro_ASLT_A100    \r\n");
#endif

	/*DDR init start*/
	//dmc_print_str("ddr init start!!!");

	/*axi port clk always on*/
	pub_axi_port_lowpower_close();

#ifdef DDR_SCAN_ENABLE
	u32 freq_index;
	/*pub soft rst*/
	reg_bit_set((PMU_APB_BASE_ADDR + 0xB0),6,1,1);
	wait_us(10);
	reg_bit_set((PMU_APB_BASE_ADDR + 0xB0),6,1,0);

	/* scan use fdl1,so set default freq to 933,if need 384 scan delete this code*/
	if(target_ddr_clk < DDR_CLK_512M)
		target_ddr_clk = DDR_CLK_1333M;
	scan_target_clk = target_ddr_clk;
	if(first_init == 2)
	{
		dmc_freq_sel_search(target_ddr_clk, &freq_index);
		if(target_ddr_clk >= DDR_CLK_512M)
			ddr_mode = 0xFF00 & (~(1 << (freq_index + 8)));
		if(target_ddr_clk == DDR_CLK_1866M)
			ddr_mode = 0xEFFF & ddr_mode;///1024 is need in ddrc_train_seq when 1866
	}
#endif
	/*dram type setting*/
	dram_type_pinmux_auto_detect();
	if(dram_info.dram_type == DRAM_LP3)
	{
		dpll_cfg(DDR_CLK_1866M);
	}
	/*According ddr_mode get training High point*/
	train_high_point=get_training_high_point(ddr_mode);
#if defined(CONFIG_NAND_SPL)
	/*watchdog reset entry into sre*/
	wdg_rst_keep_sre();
#endif
	/*zq calibration*/
	ddrc_zqc_seq();

	/*pinmux setting*/
	ddrc_phy_pinmux_set();

	/*dram init at a low frequency*/
	dram_init_from_low_freq(BOOT_FREQ_POINT);

	//loop_get_tdqs2dq();
	/*dram size auto-detect and include Manual setting mode */
	dram_size_auto_detect();

	/*DFS pre setting,from pure sw dfs to sw dfs*/
	sw_dfs_pre_set(BOOT_FREQ_POINT);

	/*According MR5,MR6,MR7(Manufacturer ID) limit Top freq(variable:train_high_point) */
	dram_freq_auto_detect(&train_high_point);

	//close dbi
	ddrc_dbi_close();

	/*training flow--Change freq and training
	Start freq:Global Variable:LP3_TRAIN_START_FN and LP4_TRAIN_START_FN
	ddr mode:bit8~bit15 map fn0~fn7 training enable flag (0:Enable 1:Disable)*/
	ddrc_train_seq(ddr_mode,train_high_point);//ddr_mode->represent ddr training freq

	/*target frequency point*/
	ddrc_target_point_set(&target_ddr_clk, train_high_point);
	ddrc_target_point_set(&target_ddr_clk, train_high_point);

	/*ssc cfg Extended frequency*/
#if defined(CONFIG_NAND_SPL) && defined(SSC_CFG)
	pll_ssc_cfg(target_ddr_clk,(ddr_mode>>16)&0xff);
#endif

	/*enable auto refresh*/
	ddrc_auto_refresh_open();
#ifdef DDR_SCAN_ENABLE
	if(first_init == 0)
		first_init = 1;
	else
		return ;
	ddr_scan_offline_r2p0(target_ddr_clk);
#else

	/*bist test*/
	//dram_bist_test();
	dmc_ddr_test(DRAM_BIST_TEST,0x0,0x0);
	/*dbi setting*/
	ddrc_dbi_set(target_ddr_clk);

	/*
	*ddr init end
	*1.ddrc lowpower
	*3.mr4 function
	*4.dfs function
	*5.auto cpst
	*6.auto zqc
	*/
	ddrc_dmc_post_set();
#if defined(CONFIG_NAND_SPL)
	/*pub_sys clk auto gate*/
	pub_lowpower_set();
#endif

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
#endif
#ifdef WDG_TEST
	reboot_times();
	start_watchdog(5);
#endif
	/*ddr debug mode---AON IRAM Addr
      AP:0x00003000-0x000043ff
      CM4:0x20001000-0x200023ff
    */
#if defined(CONFIG_NAND_SPL)
	/*Send kernel and dfs information through iram*/
	ddrc_debug_mode(ddr_mode,train_high_point);
#endif
	ddr_init_pass();
	ddrc_lock();
#endif

}

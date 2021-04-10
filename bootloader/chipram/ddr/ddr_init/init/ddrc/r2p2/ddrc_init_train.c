#include "ddrc_init.h"
#include "dram_support.h"
/*******************************Training flow*************************************/
typedef struct TRAIN_CFG_INFO
{
	u32 ddr_clk;
	u32 ddr_freq_num;
	u32 odt_status;
	u32 train_cs_num;
	u32 train_chn_num;
	u32 train_byte_en;
	u32 train_addr_31_0;
	u32 train_addr_33_32;
	u32 vrefca_val;
	u32 vrefca_val_chn0;
	u32 vrefca_val_chn1;
	u32 vrefdq_rd_val;
	u32 vrefdq_rd_val_chn0;
	u32 vrefdq_rd_val_chn1;
	u32 vrefdq_wr_val;
	u32 vrefdq_wr_val_chn0;
	u32 vrefdq_wr_val_chn1;
}TRAIN_CFG_INFO_T;
TRAIN_CFG_INFO_T train_info;
extern DRAM_INFO_T dram_info;
extern DDRC_DMC_DTMG_T *dmc_dtmg;
extern DDRC_PHY_TMG_T *phy_tmg;

#ifdef DDR_SCAN_ENABLE
#define dmc_print_str(x) NULL
#define print_Hex(x) NULL
extern u32 pass_win_max_scan[];
extern u32 scan_target_clk;
#endif
int rd_en_test_flag;
u32 wreye_val_cs0_max=0x0;
u16 dll_ac_ds_addr[6]={0x0064,0x0068,0x006c,0x008c,0x00ac,0x00cc};
u8 cadsk_done=0;
u8 wrdsk_done=0;
u8 rddsk_done=0;
u8 cs1_wrdsk_done=0;
u8 ch1_cs0_wrdsk_done=0;
u8 ch1_cs1_wrdsk_done=0;
u8 ch1_cadsk_done=0;
u8 ch1_rddsk_done=0;
u8 ch0_cavref_done =0;
u8 ch1_cavref_done = 0;
u32 wrdsk_train_address[24] = {0x310016e0, 0x310016e4, 0x310016f0,
                            0x31001720, 0x31001724, 0x31001730,
                            0x310017c0, 0x310017c4, 0x310017d0,
                            0x310017d4, 0x310017d8, 0x310017e4,
                            0x31001760, 0x31001764, 0x31001770,
                            0x310017a0, 0x310017a4, 0x310017b0,
                            0x310017e8, 0x310017ec, 0x310017f8,
                            0x310017fc, 0x31001800, 0x3100180c
};
/******************************************
*This variable use for distigunish first dfs
*and second dfs in dmc_fsp_dfs_prepare()
*******************************************/
u8 dfs_fsp_num=0;
u32 train_rd_pattern[]={TRAIN_RD_PATTERN_LP4_1,
			TRAIN_RD_PATTERN_LP4_2,
			TRAIN_RD_PATTERN_LP4_3,
			TRAIN_RD_PATTERN_LP4_4,
			TRAIN_RD_PATTERN_LP4_5,
			TRAIN_RD_PATTERN_LP4_6,
			TRAIN_RD_PATTERN_LP4_7,
			TRAIN_RD_PATTERN_LP4_8
			};
u32 train_wr_pattern[]={TRAIN_WR_PATTERN_LP4_1,
			TRAIN_WR_PATTERN_LP4_2,
			TRAIN_WR_PATTERN_LP4_3,
			TRAIN_WR_PATTERN_LP4_4,
			TRAIN_WR_PATTERN_LP4_5,
			TRAIN_WR_PATTERN_LP4_6,
			TRAIN_WR_PATTERN_LP4_7,
			TRAIN_WR_PATTERN_LP4_8
			};
u32 train_lp3_pattern[]={0x0,
			0xffffffff,
			0x0,
			0xffffffff,
			0x55555555,
			0xaaaaaaaa,
			0x55555555,
			0xaaaaaaaa
};
void rf_train_clear()
{
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
	wait_100ns(1);
}

//lpddr4_set_rd_dq_pattern
void dmc_phy_train_lp4_rd_dq_pattern()
{
	u32 i=0;
	for(i=0;i<8;i++)
	{
		__raw_writel(DMC_CTL0_(0x0060+i*4),train_rd_pattern[i]);
	}
		/*__raw_writel(DMC_CTL0_(0x0060),TRAIN_RD_PATTERN_LP4_1);
		__raw_writel(DMC_CTL0_(0x0064),TRAIN_RD_PATTERN_LP4_2);
		__raw_writel(DMC_CTL0_(0x0068),TRAIN_RD_PATTERN_LP4_3);
		__raw_writel(DMC_CTL0_(0x006c),TRAIN_RD_PATTERN_LP4_4);
		__raw_writel(DMC_CTL0_(0x0070),TRAIN_RD_PATTERN_LP4_5);
		__raw_writel(DMC_CTL0_(0x0074),TRAIN_RD_PATTERN_LP4_6);
		__raw_writel(DMC_CTL0_(0x0078),TRAIN_RD_PATTERN_LP4_7);
		__raw_writel(DMC_CTL0_(0x007c),TRAIN_RD_PATTERN_LP4_8);
		*/
		//set rf_train_dsk_base_value for rd training
		//Make rd training do more accurate
		reg_bit_set(DMC_CTL0_(0x0168),24,8,0x18);
}
void dmc_phy_train_lp4_wr_dq_pattern(u32 chn_num)
{
	u32 i=0;
	for(i=0;i<8;i++)
	{
		__raw_writel(DMC_CTL0_(0x0060+i*4),train_wr_pattern[i]);
	}
		/*
		__raw_writel(DMC_CTL0_(0x0060),TRAIN_WR_PATTERN_LP4_1);
		__raw_writel(DMC_CTL0_(0x0064),TRAIN_WR_PATTERN_LP4_2);
		__raw_writel(DMC_CTL0_(0x0068),TRAIN_WR_PATTERN_LP4_3);
		__raw_writel(DMC_CTL0_(0x006c),TRAIN_WR_PATTERN_LP4_4);
		__raw_writel(DMC_CTL0_(0x0070),TRAIN_WR_PATTERN_LP4_5);
		__raw_writel(DMC_CTL0_(0x0074),TRAIN_WR_PATTERN_LP4_6);
		__raw_writel(DMC_CTL0_(0x0078),TRAIN_WR_PATTERN_LP4_7);
		__raw_writel(DMC_CTL0_(0x007c),TRAIN_WR_PATTERN_LP4_8);
		*/
		//other configur
		reg_bit_set(DMC_CTL0_(0x0168),24,8,0x0); //rf_train_dsk_base_value = 0 for wr training
}
void dmc_phy_train_lp4_ca_pattern()
{
	//set ca pattern
	__raw_writel(DMC_CTL0_(0x0060), TRAIN_CA_PATTERN_LP4);
}


void dmc_phy_train_pre_set()
{
	u32 num=0;
	//set dfs parameter
	reg_bit_set(DMC_CTL0_(0x012c), 0, 4,0x0f);//drf_dfs
	/*
	reg_bit_set(DMC_CTL0_(0x012c), 0, 1,0x01);//drf_dfs_en
	reg_bit_set(DMC_CTL0_(0x012c), 1, 1,0x01);//drf_dfs_dll_rst_en
	reg_bit_set(DMC_CTL0_(0x012c), 2, 1,0x01);//drf_dfs_cmd_mrw_en
	reg_bit_set(DMC_CTL0_(0x012c), 3, 1,0x01);//drf_drf_dfs_pll_lock_en
	*/
	//This bit is used to enable to send the first 8 MRW before dfs for lp4 fsp dfs flow
	if(dram_info.dram_type == DRAM_LP3)
	{
		reg_bit_set(DMC_CTL0_(0x12C),12,4,0xA);//disable fsp
	}else
	{
		reg_bit_set(DMC_CTL0_(0x012c), 12, 4,0x05);//drf_dfs_cmd_mrw_fsp_en
	}

	if(dram_info.cs_num==DRAM_CS_ALL)//if ddr ==2 cs
		{
			reg_bit_set(DMC_CTL0_(0x0100),11, 1,((dram_info.cs_num==DRAM_CS_ALL)?0x1:0x0));//rf_data_ie_mode 1:different dfi_rddata_en 0:cs0&cs1 with same dfi_rddata_en
			reg_bit_set(DMC_CTL0_(0x0100),12, 1,((dram_info.cs_num==DRAM_CS_ALL)?0x1:0x0));//rf_data_oe_mode 1:different dfi_wrdata_en 0:cs0&cs1 with same dfi_wrdata_en
		}
	wait_100ns(1);
	//disable
	reg_bit_set(DMC_CTL0_(0x0114),24, 1,0x0);//drf_auto_mr4_en:Disable auto refresh rate update
	reg_bit_set(DMC_CTL0_(0x0118),24, 1,0x0);//drf_auto_zqc_en:Disable Automatic ZQ calibration
	reg_bit_set(DMC_CTL0_(0x0144),16, 2,0x0);//rf_period_cpst_en:It will affect phy training
	/*reg_bit_set(DMC_CTL0_(0x0144),16, 1,0x0);//rf_period_cpst_en:It will affect phy training
	reg_bit_set(DMC_CTL0_(0x0144),17, 1,0x0);//rf_wbuf_merge_en
	*/
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//drf_auto_ref_en--Enable HW auto-refresh
	reg_bit_set(DMC_CTL0_(0x0104),31, 1,0x0);//dsoft_cmd_allcs
	//LPDDR3 Train data pattern
	if(dram_info.dram_type == DRAM_LP3)
	{
	for(num=0;num<8;num++)
	{
		__raw_writel(DMC_CTL0_(0x0060+0x4*num),train_lp3_pattern[num]);
	}
/*
		__raw_writel(DMC_CTL0_(0x0060),0x0);
		__raw_writel(DMC_CTL0_(0x0064),0xffffffff);
		__raw_writel(DMC_CTL0_(0x0068),0x0);
		__raw_writel(DMC_CTL0_(0x006c),0xffffffff);
		__raw_writel(DMC_CTL0_(0x0070),0x55555555);
		__raw_writel(DMC_CTL0_(0x0074),0xaaaaaaaa);
		__raw_writel(DMC_CTL0_(0x0078),0x55555555);
		__raw_writel(DMC_CTL0_(0x007c),0xaaaaaaaa);
*/
	}
}
void dmc_train_cke_pre_set(u32 ddr_clk)
{
	//set dtmg_18
	reg_bit_set(DMC_CTL0_(0x01c8+train_info.ddr_freq_num*0x60), 16,1, 1);//cke=1

}
/*First DFS FSP should set WR=1 and second dfs should set 0
  First fsp dfs should repeat twice in same freq
*/
void dmc_fsp_dfs_prepare(u32 fn)
{
	if(dram_info.dram_type!=DRAM_LP3)
	{
		dfs_fsp_num++;
		if(dfs_fsp_num==1)
			{
				reg_bit_set(DMC_CTL0_(0x10c),12,1,0);//disable auto ref
				dmc_mrw(DRAM_MR_13,DRAM_CS_ALL,0x40);//WR=1
				reg_bit_set(DMC_CTL0_(0x10c),12,1,1);//Enable auto ref
				sw_dfs_go(fn);/*First dfs*/
			}else if(dfs_fsp_num==2)
				{
				reg_bit_set(DMC_CTL0_(0x10c),12,1,0);//disable auto ref
				dmc_mrw(DRAM_MR_13,DRAM_CS_ALL,0x0);//WR=0
				reg_bit_set(DMC_CTL0_(0x10c),12,1,1);//enable auto ref
				reg_bit_set(DMC_CTL0_(0x158),11,1,1);
				wait_us(1);
				reg_bit_set(DMC_CTL0_(0x158),11,1,0);//train_soft_rst---clear information in last messgae
				dfs_fsp_num=0;
			}
		}


}
void dmc_phy_train_en(u32 train_en)
{
	u32 tr_val=0;
	u32 tr_num=0;
	/*
	*rf_train_cadsk_en bit[0]
	*rf_train_caeye_en bit[4]
	*rf_train_gate_en  bit[8]
	*rf_train_rddsk_en bit[12]
	*rf_train_rdeye_en bit[16]
	*rf_train_wrdsk_en bit[20]
	*rf_train_wreye_en bit[24]
	*/
	tr_val = __raw_readl(DMC_CTL0_(0x0158));
	tr_val &= ~(0x1111111);
	tr_val |=(0x1<<(train_en*4));
	__raw_writel(DMC_CTL0_(0x0158), tr_val);
}

u32 is_dmc_phy_train_en(u32 tr_type)
{
	return (((phy_tmg+train_info.ddr_freq_num)->train_flag>>(tr_type*4))&0x1);
}

u32 dmc_phy_train_polling_done(u32 tr_type,u32 train_num)
{
	u32 train_done_flag=0;
	u32 train_wait_num=0;
	//wait train done
	while(1)
	{
		train_done_flag=(__raw_readl(DMC_CTL0_(0x0158))>>(tr_type*4+1))&0x1;
		if(train_done_flag)
		{
			break;
		}else
		{
#if TEST_DEBUG_LOG_LEVEL>2
			dmc_print_str("training not done   ");
#endif
			/*dmc_print_str("\r\n");
			print_Hex(__raw_readl(DMC_CTL0_(0x4e4)));
			dmc_print_str("\r\n");
			print_Hex(__raw_readl(DMC_CTL0_(0x4e8)));
			dmc_print_str("\r\n");*/
			wait_us(1);
		train_wait_num++;
		if(train_wait_num >= 1500)
			{
#if TEST_DEBUG_LOG_LEVEL>2
			dmc_print_str("\r\ntraining status=   ");
			print_Hex(__raw_readl(DMC_CTL0_(0x0158)));
			dmc_print_str("\r\n");
#endif
			while(1);
			}
		}
	}
	if((__raw_readl(DMC_CTL0_(0x0158))>>(tr_type*4+2))&0x1)
	{
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("training fail!!   ");
#endif
		if(train_num==1)//LP4:loop
		{
			if(dram_info.dram_type != DRAM_LP3)
			{
				while(1);
			}else
			{
				return 1;
			}
		}else//LP4 return error flag
		{
			/*******************************************************************
			*Only use for wr dsk training no while loop
			*If you want other training no loop please copy
			*this flow in new flow and delete clear rf_train_start(similar L5)
			*******************************************************************/
			/*if(dram_info.dram_type != DRAM_LP3)
			{
				reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);// clear rf_train_start
				//train clear
				reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
				wait_100ns(1);
				reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
			}*/
			return 1;
		}
	}else
	{
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("training pass!!!   ");
#endif
	}
	return 0;
}


void dmc_phy_train_all_clear()
{
	u32 register_value=0;
	register_value=__raw_readl(DMC_CTL0_(0x0158));
	//bit[24]rf_train_wreyw_en bit[20]rf_train_wrdsk_en bit[16]:rf_train_rdeye_en bit[12]:rf_train_rddsk_en
	//bit[8]:rf_train_gate_en bit[4]:rf_train_caeye_en bit[0]:rf_train_cadsk_en
	register_value |=0x1111111;
	__raw_writel(DMC_CTL0_(0x0158),register_value);
	wait_us(1);
	rf_train_clear();
	register_value=__raw_readl(DMC_CTL0_(0x0158));
	register_value &=(~0x1111111);
	__raw_writel(DMC_CTL0_(0x0158),register_value);
	//update slave delay period 2*16 4x_clk cycles
	reg_bit_set(DMC_CTL0_(0x0154),16, 8,0x2);//rf_phy_resync2_cnt
	reg_bit_set(DMC_CTL0_(0x0154), 8, 8,0x2);//rf_phy_resync1_cnt
}

void dmc_phy_soft_update()
{
	u32 dl_num,dl_addr_offset;
	for(dl_num=0;dl_num<6;dl_num++)
	{
		dl_addr_offset=0x0640+dl_num*0x40;
		//updated slave delay by software
		reg_bit_set(DMC_PHY0_(dl_addr_offset),11,1,0x1);//rf_dl_cpst_start_ac0
		reg_bit_set(DMC_PHY0_(dl_addr_offset),11,1,0x0);//rf_dl_cpst_start_ac0
	}
}
void dmc_phy_train_dll_convert()
{
	volatile u32 dll_num=0;
	u32 raw_2cycle_sel,raw_cycle_sel,raw_dl_sel;
	u32 dl_addr_offset=0;
	u32 num=0;
	//cfg dll ac0 dl_0~cfg dll_ds0_0
	for(dll_num=0;dll_num<6;dll_num++)
	{
		dl_addr_offset=train_info.ddr_freq_num*0xc0+dll_ac_ds_addr[dll_num];

		raw_2cycle_sel=((__raw_readl(DMC_PHY0_(dl_addr_offset))>>23)&0x1);//delay 2 cycle
		raw_cycle_sel=((__raw_readl(DMC_PHY0_(dl_addr_offset))>>15)&0x1);//delay 1 cycle
		raw_dl_sel=__raw_readl(DMC_PHY0_(dl_addr_offset))&0xff;//raw delay

		if(raw_2cycle_sel)//2cycle
		{
			raw_dl_sel += 0x80;
			reg_bit_set(DMC_PHY0_(dl_addr_offset),23, 1,0x0);//clear
		}
		if(raw_cycle_sel)//1cycle
		{
			raw_dl_sel += 0x40;
			reg_bit_set(DMC_PHY0_(dl_addr_offset), 15, 1,0x0);//clear
		}
		reg_bit_set(DMC_PHY0_(dl_addr_offset),0,8,raw_dl_sel);//write transform result
	}
	//lp4 clkwr_raw_cycle_ac0_sle cfg
	/**************************************************************************************
	*1.If raw_sel  1cycle 2cycle equal 0 ,dqs and dq pos Position difference 2*4x(+tdqs2dq)
	*	in this situation training may fail for not get  boundary
	*2.So Set 1cycle=1 can enhance dqs and dq pos difference  1*4x(+tdqs2dq)
	*3.High poin If training result perferct should set 2cycle=1 and repeat training
	**************************************************************************************/
	if(dram_info.dram_type != DRAM_LP3)
	{
		for(num=0;num<4;num++)
		{
			reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x006c+0x20*num),15,1,0x1);
		}
		/*
		reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x006c),15,1,0x1);//rf_clkwr_raw_cycle_0_sel
		reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x008c),15,1,0x1);//rf_clkwr_raw_cycle_1_sel
		reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x00ac),15,1,0x1);//rf_clkwr_raw_cycle_2_sel
		reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x00cc),15,1,0x1);//rf_clkwr_raw_cycle_3_sel
		*/
	}
	for(num=0;num<4;num++)
	{
		reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x007c+0x20*num),0,8,0x0);
	}
	/*reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x007c),0,8,0x0);//rf_clkwr_diff_dl_0_sel
	reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x009c),0,8,0x0);//rf_clkwr_diff_dl_1_sel
	reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x00bc),0,8,0x0);//rf_clkwr_diff_dl_2_sel
	reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x00dc),0,8,0x0);//rf_clkwr_diff_dl_3_sel
	*/
	//dmc_phy_soft_update();
	//reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//drf_auto_ref_en
}

//convert delay value to cycle
void dmc_phy_train_cycle_convert()
{
	u32 raw_dl_val;
	u32 dll_num;
	u32 raw_one_cycle;
	u32 raw_two_cycle;
	u32 reg_dll_ac_ds;
	//disable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);
	wait_100ns(2);
	//dll_cnt=(__raw_readl(DMC_PHY0_(0x0644))&0x7f);
	for(dll_num=0;dll_num<6;dll_num++)
	{
		reg_dll_ac_ds = DMC_PHY0_(train_info.ddr_freq_num*0xc0+dll_ac_ds_addr[dll_num]);
		raw_dl_val=(__raw_readl(reg_dll_ac_ds)&0xff);
		raw_one_cycle=(__raw_readl(reg_dll_ac_ds)>>15)&0x1;//1cycle flag
		raw_two_cycle=(__raw_readl(reg_dll_ac_ds)>>23)&0x1;
		if(raw_dl_val>=0x80)
			{
				if(raw_two_cycle==1)
					{
					if(raw_one_cycle==0)
						{
						raw_dl_val=raw_dl_val-0x40;
						reg_bit_set(reg_dll_ac_ds,0,8,raw_dl_val);//remainder
						reg_bit_set(reg_dll_ac_ds,15,1,0x1);//1 cycle
						}
					}
				else{
					raw_dl_val=raw_dl_val-0x80;
					reg_bit_set(reg_dll_ac_ds,0,8,raw_dl_val);//remainder
					reg_bit_set(reg_dll_ac_ds,23,1,0x1);//1 cycle +1 cycle=2cycle
					}
			}
		else if((raw_dl_val>=0x40) && ((raw_two_cycle==0x0)||(raw_one_cycle==0x0)))//raw_two_cycle=0 or raw_one_cycle=0
			{
			raw_dl_val=raw_dl_val-0x40;//-0x40=>one clock
			reg_bit_set(reg_dll_ac_ds,0,8,raw_dl_val);
			if(raw_one_cycle==0)
				reg_bit_set(reg_dll_ac_ds,15,1,0x1);//1 cycle
			else//raw_one_cycle=1 and raw_two_cycle=0
				{
				reg_bit_set(reg_dll_ac_ds,15,1,0x0);//Clear 1 cycle
				reg_bit_set(reg_dll_ac_ds,23,1,0x1);//Set 1 cycle +1 cycle=2cycle
				}
			}
		//update delay
		//reg_bit_set(DMC_PHY0_(0x0640+0x40*dll_num),11,1,0x1);//rf_dl_cpst_start_ac0
		//wait_100ns(1);
		//reg_bit_set(DMC_PHY0_(0x0640+0x40*dll_num),11,1,0x0);
	}
	dmc_phy_soft_update();
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//drf_auto_ref_en
}

void dmc_phy_train_delay_convert()
{
	reg_bit_set(DMC_PHY0_(0x4),10,1,0);//phy_sample_auto_rst_en
	reg_bit_set(DMC_CTL0_(0x10C),12,1,0);//disable drf_auto_ref_en

	//convert dll to delay value
	dmc_phy_train_dll_convert();
	//update
	dmc_phy_soft_update();
	//enable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1, 0x1);
}
void dmc_set_write_odt(u32 fn)
{
	u32 odt_cfg=0;
	odt_cfg=__raw_readl(DMC_CTL0_(0x1ac+0x60*fn));
	//odt_cfg=(value>>16)&0xff;
	dmc_mrw(DRAM_MR_11, DRAM_CS_ALL,odt_cfg);

}
void dmc_phy_train_info_pre_set_pre_chn(u32 cs_chn)
{
	train_info.train_addr_31_0=(u32)(((dram_info.cs0_size+dram_info.cs1_size)%0x100000000));
	train_info.train_addr_33_32=(u32)((dram_info.cs0_size+dram_info.cs1_size)/0x100000000);
	if((train_info.train_addr_31_0==0x0)&&(train_info.train_addr_33_32>0))
		{
		train_info.train_addr_31_0=0x100000000-(cs_chn+1)*dram_info.intlv_size;
		train_info.train_addr_33_32=train_info.train_addr_33_32-1;
		}
	else
		{
		train_info.train_addr_31_0=train_info.train_addr_31_0-(cs_chn+1)*dram_info.intlv_size;
		}
	return;
}
void dmc_phy_train_info_pre_set(u32 train_chn,u32 cs_num)
{
#if TEST_DEBUG_LOG_LEVEL>2
			dmc_print_str("\r\n----------LP4 training chn num: ");
			print_Hex(train_chn);
			dmc_print_str(" cs_num:");
			print_Hex(cs_num);
			dmc_print_str("\r\n");
#endif
	train_info.train_cs_num=cs_num;
	train_info.train_chn_num=train_chn;
	if(dram_info.dram_type == DRAM_LP3)
	{
		train_info.train_byte_en=0xf;/*Enable byte0,byte1,byte2,byte3 Training*/
		train_info.train_addr_31_0=0x0;
		train_info.train_addr_33_32=0x0;
	}else
	{
		if(train_chn==DRAM_CHN_0)
		{
			train_info.train_byte_en=0x3;/*Enable byte0,byte1 Training*/
			if(cs_num==DRAM_CS_0)
			{
				train_info.train_addr_31_0=0x0;
				train_info.train_addr_33_32=0x0;
			}else
			{
				//all interleave size
				//bit0~31:Max2^32=4GB space
				//ch0 and ch1 .......last:ch0 and ch1
				dmc_phy_train_info_pre_set_pre_chn(1);
			}
		}else
		{
			train_info.train_byte_en=0xc;/*Enable byte2,byte3 Training*/
			if(cs_num==DRAM_CS_0)
			{
				train_info.train_addr_31_0=dram_info.intlv_size;
				train_info.train_addr_33_32=0x0;
			}else
			{
				dmc_phy_train_info_pre_set_pre_chn(0);
			}
		}
	}
	//select train cs
	reg_bit_set(DMC_CTL0_(0x0158),31, 1,train_info.train_cs_num);//rf_train_cs_sel
	//select training channel0
	reg_bit_set(DMC_CTL0_(0x0154),3,1,train_info.train_chn_num);//rf_train_ch
	/*Set training byte CH0:byte0 and byte1 CH1:byte2 and byte3*/
	reg_bit_set(DMC_CTL0_(0x0154),4,4,train_info.train_byte_en);//rf_train_byte_en
	//train addr set
	__raw_writel(DMC_CTL0_(0x015c), train_info.train_addr_31_0);//rf_train_addr_0_31
	reg_bit_set(DMC_CTL0_(0x0158),28,2,train_info.train_addr_33_32);//rf_train_addr_33_32

#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("\r\nTraining Addrass:");
	dmc_print_str("		addr_31_0:");
	print_Hex(train_info.train_addr_31_0);
	dmc_print_str("		addr_33_32:");
	print_Hex(train_info.train_addr_33_32);
#endif
}


void dmc_phy_train_lp3_polling_retry(TRAIN_TYPE_E train_type_sel, u32 retry_times)
{
	u32 train_flag=0;

	train_flag=dmc_phy_train_polling_done(train_type_sel,1);
	//if(train_flag)
	//{
	//	retry_times=0;
	//}
	while((retry_times !=0) && (train_flag!=0) )
	{
		//retry training
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
		wait_100ns(1);
		//train clear
		rf_train_clear();
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
		retry_times--;
		train_flag=dmc_phy_train_polling_done(train_type_sel,1);
		if(!train_flag)
		{
			break;
		}
	}
	if((retry_times==0)&&(train_flag==1))
	{
		while(1);
	}
}

void dmc_phy_train_optimize_wrdsk_result()
{
	u32 min_dly;
	u32 bit_dly[9];
	u32 bit_0_3_dly;
	u32 bit_4_7_dly;
	int i, j;

	for(i=0; i<24; i=i+3 )
	{

		bit_0_3_dly = __raw_readl((wrdsk_train_address[i]));
		bit_4_7_dly = __raw_readl((wrdsk_train_address[i+1]));
		bit_dly[8] = (__raw_readl((wrdsk_train_address[i+2]))>>8) & 0xff;
		bit_dly[0] = bit_0_3_dly & 0xff;
		bit_dly[1] = (bit_0_3_dly>>8) & 0xff;
		bit_dly[2] = (bit_0_3_dly>>16) & 0xff;
		bit_dly[3] = (bit_0_3_dly>>24) & 0xff;
		bit_dly[4] = bit_4_7_dly & 0xff;
		bit_dly[5] = (bit_4_7_dly>>8) & 0xff;
		bit_dly[6] = (bit_4_7_dly>>16) & 0xff;
		bit_dly[7] = (bit_4_7_dly>>24) & 0xff;

		min_dly=0xff;
		for(j=0; j<9; j++)
		{
			if(bit_dly[j]<min_dly)
				min_dly=bit_dly[j]&0xfc;
		}
		for(j=0; j<9; j++)
		{
			bit_dly[j] = bit_dly[j] - min_dly;
		}
		bit_0_3_dly = bit_dly[0] | (bit_dly[1]<<8) | (bit_dly[2]<<16) | (bit_dly[3]<<24);
		bit_4_7_dly = bit_dly[4] | (bit_dly[5]<<8) | (bit_dly[6]<<16) | (bit_dly[7]<<24);

		__raw_writel((wrdsk_train_address[i]), bit_0_3_dly);
		__raw_writel((wrdsk_train_address[i+1]), bit_4_7_dly);
		__raw_writel((wrdsk_train_address[i+2]), bit_dly[8]<<8);
	}

}

void dmc_phy_train_lp3()
{
	u32 dll_cnt_temp;
	u32 caeye_train_val,caeye_pass_win;
	u32 dll_cnt;
	u32 rddsk_start =0;
    int ddr_freq;
	u32 i;
	u32 fn=train_info.ddr_freq_num;

	dll_cnt_temp=__raw_readl(DMC_PHY0_(0x644))&0x3f;
	if((dll_cnt_temp > 0x3c) && ((train_info.ddr_clk == DDR_CLK_512M)||(train_info.ddr_clk == DDR_CLK_622M)))
	{
		//(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_CADSK_INDEX*4));
		(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_CAEYE_INDEX*4));
		//(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_WRDSK_INDEX*4));
		(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_WREYE_INDEX*4));
	}

	reg_bit_set(DMC_CTL0_(0x0164), 0, 8,0x8);
	reg_bit_set(DMC_CTL0_(0x0164),16, 8,0x18);
	reg_bit_set(DMC_PHY0_(0x0060+train_info.ddr_freq_num*0xc0),4,4,0x1);//enable phy update
    //set vref
    for(ddr_freq=0; ddr_freq<7 ; ddr_freq++)
        reg_bit_set(DMC_PHY0_(0x00f4+ddr_freq*0xc0),24,8,0x50);
	//train pre set
	dmc_phy_train_info_pre_set(DRAM_CHN_0,DRAM_CS_0);
	//disable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);//drf_auto_ref_en
	reg_bit_set(DMC_CTL0_(0x0104),28, 1,0x0);//
	reg_bit_set(DMC_CTL0_(0x0158),31, 1,0x0);//select train cs0
	//set ca pattern
	__raw_writel(DMC_CTL0_(0x0060), 0x3ff);
	dll_cnt=__raw_readl(DMC_PHY0_(0x0644))&0x7f;
	/****cadsk training****/
	if(is_dmc_phy_train_en(TRAIN_CADSK_INDEX) && (cadsk_done==0) && ((dll_cnt<48) || (train_info.ddr_clk>DDR_CLK_768M)))
	{
		reg_bit_set(DMC_CTL0_(0x0158), 0, 1,0x1);//train_cadsk_en
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("\r\n  TRAIN_CADSK_INDEX \r\n");
#endif
		dmc_phy_train_lp3_polling_retry(TRAIN_CADSK_INDEX, 0);
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
		reg_bit_set(DMC_CTL0_(0x0158), 0, 1,0x0);//train_cadsk_en
		cadsk_done = 1;
	}
	/****caeye training****/
	if(is_dmc_phy_train_en(TRAIN_CAEYE_INDEX))
	{
		reg_bit_set(DMC_CTL0_(0x0158), 4, 1,0x1);//train_caeye_en
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
		wait_100ns(1);
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("\r\n  TRAIN_CAEYE_INDEX \r\n");
#endif
		dmc_phy_train_lp3_polling_retry(TRAIN_CAEYE_INDEX, 0);
		caeye_train_val=(__raw_readl(DMC_CTL0_(0x0168))>>11)&0x7ff;
		caeye_pass_win=__raw_readl(DMC_CTL0_(0x0168))&0x7ff;
		reg_bit_set(DMC_CTL0_(0x0158), 4, 1,0x0);//Disable train_caeye_en
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//Disable rf_train_start

	}
#ifdef DDR_SCAN_ENABLE
	//pass_win_max_scan[2]= caeye_pass_win;
#endif
	/****data slice training****/
	__raw_writel(DMC_CTL0_(0x0060), 0x00);//set dq pattern
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//drf_auto_ref_en
	if(is_dmc_phy_train_en(TRAIN_WRDSK_INDEX) && wrdsk_done==0 && ((dll_cnt<48) || (train_info.ddr_clk>DDR_CLK_768M)))
	{
		reg_bit_set(DMC_CTL0_(0x0158),20, 1,0x1);//train_wrdsk_en

		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("\r\n  TRAIN_WRDSK_INDEX \r\n");
#endif
		dmc_phy_train_lp3_polling_retry(TRAIN_WRDSK_INDEX, 10);
		wrdsk_done = 1;


		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
		rf_train_clear();

		dmc_phy_train_optimize_wrdsk_result();

		reg_bit_set(DMC_CTL0_(0x0158),20, 1,0x0);//train_wrdsk_en

	}
	if(is_dmc_phy_train_en(TRAIN_WREYE_INDEX))
	{
		reg_bit_set(DMC_CTL0_(0x0158),24, 1,0x1);//train_wreye_en
		for(i=0; i<4; i++)
		{
			reg_bit_set(DMC_CTL0_(0x0154),4,4,1<<i); //rf_train_byte_en
			rf_train_clear();

			reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
#if TEST_DEBUG_LOG_LEVEL>2
			dmc_print_str("\r\n  TRAIN_WREYE_INDEX \r\n");
#endif
			dmc_phy_train_lp3_polling_retry(TRAIN_WREYE_INDEX, 0);
			reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start

		}
		reg_bit_set(DMC_CTL0_(0x0158),24, 1,0x0);//train_wreye_en
	}
#ifdef DDR_SCAN_ENABLE
	pass_win_max_scan[1]= __raw_readl(DMC_CTL0_(0x0170));
#endif
	if(is_dmc_phy_train_en(TRAIN_RDDSK_INDEX) && (rddsk_done==0) )
	{
		reg_bit_set(DMC_CTL0_(0x0158),12, 1,0x1);//train_rddsk_en
		rddsk_start = 1;
		rf_train_clear();

		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("\r\n  TRAIN_RDDSK_INDEX \r\n");
#endif
		dmc_phy_train_lp3_polling_retry(TRAIN_RDDSK_INDEX, 0);
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
		reg_bit_set(DMC_CTL0_(0x0158),12, 1,0x0);//train_rddsk_en
		rddsk_done = 1;
	}
	if(is_dmc_phy_train_en(TRAIN_RDEYE_INDEX))
	{

		reg_bit_set(DMC_CTL0_(0x0158),16, 1,0x1);//train_rdeye_en
		for(i=0; i<4; i++)
		{
			reg_bit_set(DMC_CTL0_(0x0154),4,4,1<<i);	//rf_train_byte_en
			rf_train_clear();

			reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
#if TEST_DEBUG_LOG_LEVEL>2
			dmc_print_str("\r\n  TRAIN_RDEYE_INDEX \r\n");
#endif
			dmc_phy_train_lp3_polling_retry(TRAIN_RDEYE_INDEX, 0);
			reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
		}
	    reg_bit_set(DMC_CTL0_(0x0158),16, 1,0x0);//train_rdeye_en
	}
#ifdef DDR_SCAN_ENABLE
	pass_win_max_scan[0]= __raw_readl(DMC_CTL0_(0x0170));
#endif
	reg_bit_set(DMC_PHY0_(0x0060+train_info.ddr_freq_num*0xc0),4,4,0xf);//disable phy update
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
	reg_bit_set(DMC_CTL0_(0x0158),24, 1,0x0);//train_wreye_en
	reg_bit_set(DMC_CTL0_(0x0158),20, 1,0x0);//train_wrdsk_en
	reg_bit_set(DMC_CTL0_(0x0158),16, 1,0x0);//train_rdeye_en
	reg_bit_set(DMC_CTL0_(0x0158),12, 1,0x0);//train_rddsk_en
	reg_bit_set(DMC_CTL0_(0x0158), 8, 1,0x0);//train_gate_en
}

void dmc_phy_train_lp4_flag_sel()
{
	u32 fn=train_info.ddr_freq_num;
	u32 dll_cnt_temp;

	dll_cnt_temp=__raw_readl(DMC_PHY0_(0x644))&0x3f;//rfdll_cnt_ac0

	/*Update not training freq in training flag*/
	if((train_info.ddr_clk==DDR_CLK_512M)||(train_info.ddr_clk==DDR_CLK_768M))
	{
		if((dll_cnt_temp>0x56))
		{
			(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_CAEYE_INDEX*4));//MASK CA eye Training
			(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_CADSK_INDEX*4));//MASK CA DSK Training
//			(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_WREYE_INDEX*4));//MASK WR EYE Training
			(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_WRDSK_INDEX*4));//MASK WR DSK Training
		}
	}
	/*Update open odt status in variable train_info.odt_status*/
	/*train_info.odt_status use for choose scan eye vref scope*/
	train_info.odt_status=0x0;
	/*if( 0 !=(((phy_tmg+train_info.ddr_freq_num)->cfg_io_ds_cfg>>12)&0x7))//Get training freq odt status
	{
		train_info.odt_status=0x1;
	}*/
	if(LP4X_ODT_EN(fn) == 1 )
	{
		train_info.odt_status=0x1;//Get training freq odt status
	}
	train_info.vrefca_val=0;
	train_info.vrefdq_rd_val=0;
	train_info.vrefdq_wr_val=0;
}



void dmc_phy_train_lp4_caeye(u32 train_count)
{
	u32 vrefca_val=0,vrefca_step=2,vrefca_min,vrefca_max;
	u32 pass_win_max=0,pass_win_max1=0,pass_win_max2=0,pass_win_temp,last_pass_win_temp;
	u32 caeye_value=0,caeye_value_1=0,caeye_value_2=0,caeye_value_temp;
	u32 caeye_vref_first1=0,caeye_vref_last1=0;
	u32 caeye_vref_first2=0,caeye_vref_last2=0;

	if(0 == is_dmc_phy_train_en(TRAIN_CAEYE_INDEX))//Detect status for training enable
	{
		return;
	}
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("\r\n-------------caeye training---------------\r\n");
#endif

	reg_bit_set(DMC_CTL0_(0x0104),28,1,0x0);//set dsoft_cmd_allcs 0
	reg_bit_set(DMC_CTL0_(0x0104),31,1,0x0);//set dsoft_cs 0
	if(train_count==1)
	{
		vrefca_min=(dram_info.dram_type==DRAM_LP4X)?LP4X_CAEYE_VREFCA_MIN:LP4_CAEYE_VREFCA_MIN;
		vrefca_max=(dram_info.dram_type==DRAM_LP4X)?LP4X_CAEYE_VREFCA_MAX:LP4_CAEYE_VREFCA_MAX;
	}else
	{
		vrefca_min=(train_info.vrefca_val_chn0+train_info.vrefca_val_chn1)/2;
		vrefca_max=(train_info.vrefca_val_chn0+train_info.vrefca_val_chn1)/2;
	}
	//train enable
	dmc_phy_train_en(TRAIN_CAEYE_INDEX);
	/*This function only get best vref ,pass_win_max and caeye_value just use for statistics*/
	/*ASIC auto set Training result  */
	for(vrefca_val=vrefca_min;vrefca_val<=vrefca_max;vrefca_val+=vrefca_step)
	{
		//train clear
		rf_train_clear();
		reg_bit_set(DMC_CTL0_(0x010c),12,1,0x0);//rf_auto_ref_en
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0164), 8,7,vrefca_val);//rf_train_caeye_vref
		reg_bit_set(DMC_CTL0_(0x0164), 0,8,CAEYE_PASS_WIN_MIN);//rf_train_caeye_pass_window_min
		wait_100ns(1);
		//train start
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
		wait_100ns(1);
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("train_count==");
		print_Hex(train_count);
		dmc_print_str("caeye training vref:");
		print_Hex(vrefca_val);
		dmc_print_str("    ");
#endif
		if(train_count == 1)
			dmc_phy_train_polling_done(TRAIN_CAEYE_INDEX,2);//Vref training No Loop
		else
			dmc_phy_train_polling_done(TRAIN_CAEYE_INDEX,1);//Loop

		pass_win_temp=(__raw_readl(DMC_CTL0_(0x0168))&0x7ff);//bit[10:0]rf train caeye pass window
		caeye_value_temp=((__raw_readl(DMC_CTL0_(0x0168))>>11)&0x7ff);//bit[21:11]:rf train caeye value
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("caeye training vref:");
		print_Hex(vrefca_val);
		dmc_print_str("    ");
		dmc_print_str("Pass Window Value:");
		print_Hex(pass_win_temp);
		dmc_print_str("    ");
		dmc_print_str("Pass Value:");
		print_Hex(caeye_value_temp);
		dmc_print_str("\r\n");

		if(pass_win_temp<0x20)
		{
			dmc_print_str("\r\npass_win_temp<0x20!!\r\n");
			//reset delay line
			while(1);
		}
#endif
		if(train_count==1)/*Get the highest data and the second highest data for  relevant vref*/
		{
			if(vrefca_val != vrefca_min) {
				if(last_pass_win_temp>pass_win_temp)
				{
					if(last_pass_win_temp-pass_win_temp > 2)
						pass_win_temp = last_pass_win_temp-2;
				} else {
					if(pass_win_temp-last_pass_win_temp > 2)
						pass_win_temp = last_pass_win_temp+2;
				}
			}
			last_pass_win_temp = pass_win_temp;
#if TEST_DEBUG_LOG_LEVEL>2
					dmc_print_str("Now Pass Window Value is:");
					print_Hex(pass_win_temp);
					dmc_print_str("\r\n");
#endif
			if(pass_win_temp>pass_win_max1)
			{
				pass_win_max1=pass_win_temp;
				caeye_value_1=caeye_value_temp;
				caeye_vref_first1=vrefca_val;
			}else if(pass_win_temp == pass_win_max1)
			{
				caeye_vref_last1=vrefca_val;
			}
			if((pass_win_temp<pass_win_max1)&&(pass_win_temp>pass_win_max2))
			{
				pass_win_max2=pass_win_temp;
				caeye_value_2=caeye_value_temp;
				caeye_vref_first2=vrefca_val;
			}else if(pass_win_temp == pass_win_max2)
			{
				caeye_vref_last2=vrefca_val;
			}
		}else
		{
			pass_win_max=pass_win_temp;//pass_win_max and  caeye_value only use statistics
			caeye_value=caeye_value_temp;
		}
		//clear train start
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//Disable rf_train_start
	}
	if(train_count==1)/*Get average*/
	{
		if(caeye_vref_last1<caeye_vref_first1)
		{
			caeye_vref_last1=caeye_vref_first1;
		}
		if(caeye_vref_first2 == 0)//avoid windows increase caeye_vref_first2=0
		{
			caeye_vref_first2=caeye_vref_first1;
			pass_win_max2=pass_win_max1;
			caeye_value_2=caeye_value_1;
		}
		if(caeye_vref_last2<caeye_vref_first2)
		{
			caeye_vref_last2=caeye_vref_first2;
		}
		pass_win_max=(pass_win_max1+pass_win_max2)/2;//(Second highest +highest)/2
		caeye_value=(caeye_value_1+caeye_value_2)/2;
		train_info.vrefca_val=(caeye_vref_first1+caeye_vref_last1)/4+(caeye_vref_first2+caeye_vref_last2)/4;//Average =(average1+average1) /2
	}
#ifdef DDR_SCAN_ENABLE
	if(train_info.ddr_clk ==scan_target_clk)
		pass_win_max_scan[train_info.train_chn_num] |= (pass_win_max << 24);
#endif
	if(pass_win_max==0){
		dmc_print_str("\r\ncaeye training pass window is zero!!!");
		while(1);
	}
	//set caeye value-ASIC auto update
	//reg_bit_set(DMC_PHY0_(dll_ac_ds_addr[train_info.train_chn_num]+train_info.ddr_freq_num*0xc0),0,8,(caeye_value));
	//dmc_phy_soft_update();//Make the delay settings take effect

	//set vrefca
	reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<train_info.train_chn_num));//drf_dsoft_chn_sel
	if(train_count==1)
	{
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("first range =");
		print_Hex(caeye_vref_first1);
		dmc_print_str("	");
		print_Hex(caeye_vref_last1);
		dmc_print_str("	second range:");
		print_Hex(caeye_vref_first2);
		dmc_print_str("	");
		print_Hex(caeye_vref_last2);
		dmc_print_str("CAEYE Vref Value:");
		print_Hex(train_info.vrefca_val);
		dmc_print_str("\r\n");
#endif
#if 0
		if(train_info.train_chn_num==0)
		{
			__raw_writel(0x20,train_info.vrefca_val);//vref
			__raw_writel(0x24,pass_win_max);//vref training pass window
		}else
		{
			__raw_writel(0x30,train_info.vrefca_val);//vref
			__raw_writel(0x34,pass_win_max);//vref training pass window
		}
#endif
		dmc_mrw(DRAM_MR_12, DRAM_CS_ALL, train_info.vrefca_val);
		//Write Back variable and fsp register
		(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg14 &= ~(0xff<<0);
		(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg14 |= train_info.vrefca_val;
		__raw_writel(DMC_CTL0_(0x01b8+train_info.ddr_freq_num*0x60), (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg14);

		wait_100ns(5);
		//clear
		rf_train_clear();
		if(train_info.train_chn_num == 0)
			train_info.vrefca_val_chn0 = train_info.vrefca_val;
		else if(train_info.train_chn_num == 1)
			train_info.vrefca_val_chn1 = train_info.vrefca_val;
	}
#if 0
	else//train count =2
	{
		if(train_info.train_chn_num==0)//M point
		{
			__raw_writel(0x28,pass_win_max);//pass window
			__raw_writel(0x2c,caeye_value);//eye value
		}else
		{
			__raw_writel(0x38,pass_win_max);//pass window
			__raw_writel(0x3c,caeye_value);//eye value
		}
		if(pass_win_max<0x40)
		{
			while(1);
		}
	}
#endif
	reg_bit_set(DMC_CTL0_(0x0100),20,4,0x3);//drf_dsoft_chn_sel
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x1);//drf_auto_ref_en
}

void dmc_phy_train_lp4_cadsk(u32* eye_retry)
{
	u32 val_tmp;
	u32 ac0_val=0,ac1_val=0;
	if(0 == is_dmc_phy_train_en(TRAIN_CADSK_INDEX))
	{
		*eye_retry=0;
		return;
	}
	if( train_info.train_chn_num==0 )
	{
		if( cadsk_done== 1 )
		{
			*eye_retry=1;
			return;
		}
		cadsk_done=1;
	}
	else
	{
		if( ch1_cadsk_done== 1 )
		{
			*eye_retry=1;
			return;
		}
		ch1_cadsk_done=1;
	}
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("\r\n-------------cadsk training---------------\r\n");
#endif
	reg_bit_set(DMC_CTL0_(0x0104),28,1,0x0);//set dsoft_cmd_allcs 0
	reg_bit_set(DMC_CTL0_(0x0104),31,1,0x0);//set dsoft_cs 0
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x0);//drf_auto_ref_en
	/*********************************************************************
	*If raw_sel, cycle, 2cycle ==0, clk and ca phase differenct 2*4x clock
	*If ddr run in High clock,this difference may increase to 3*4x clock(limit)
	*So set cycle=1 before ca training to prevent clk and ca phase difference
	*	increase to 3*4x clock
	**********************************************************************/
	val_tmp=__raw_readl(DMC_PHY0_(0x0064+train_info.ddr_freq_num*0xc0));//rf_clkwr_raw_cycle_ac0_sel
	ac0_val=val_tmp;
	//increase delay one cycle(Compared to the previous delay adjustment here is a larger delay),bit7(l5) adjust to bit15(l5p)
	val_tmp |= 0x8000;
	val_tmp = ((val_tmp&0xff) >0x40)?(val_tmp- 0x40 ):(val_tmp & 0xffffff00);

	__raw_writel(DMC_PHY0_(0x0064+train_info.ddr_freq_num*0xc0), val_tmp);

	val_tmp=__raw_readl(DMC_PHY0_(0x0068+train_info.ddr_freq_num*0xc0));//rf_clkwr_raw_cycle_ac1_sel
	ac1_val=val_tmp;
	val_tmp |= 0x8000;
	val_tmp = ((val_tmp&0xff) >0x40)?(val_tmp- 0x40 ):(val_tmp & 0xffffff00);

	__raw_writel(DMC_PHY0_(0x0068+train_info.ddr_freq_num*0xc0), val_tmp);
	dmc_phy_soft_update();//Make the delay settings take effect

	// train enable
	dmc_phy_train_en(TRAIN_CADSK_INDEX);
	//train clear
	rf_train_clear();
	//disable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);
	//set ca vref
	//this flow not need
	if(train_info.vrefca_val==0)
	{
		train_info.vrefca_val=0x4d;
	}
	reg_bit_set(DMC_CTL0_(0x0164), 8, 7,train_info.vrefca_val);//set ca eye training vref result
	wait_100ns(1);
	//train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
	wait_100ns(1);
	dmc_phy_train_polling_done(TRAIN_CADSK_INDEX,1);
	//train start clear
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//Disable rf_train_start

	__raw_writel(DMC_PHY0_(0x0064+train_info.ddr_freq_num*0xc0), ac0_val);//set ca training delay result
	__raw_writel(DMC_PHY0_(0x0068+train_info.ddr_freq_num*0xc0), ac1_val);
	dmc_phy_soft_update();//Make the delay settings take effect
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x1);//enable auto refresh
	*eye_retry=1;
	return;
}


void dmc_phy_train_lp4_rdeye(u32 train_count)
{
	u32 vrefdq_val=0,vrefdq_step=2,vrefdq_min,vrefdq_max,byte_num;
	u32 pass_win_max=0,pass_win_temp,last_pass_win_temp;
	u32 rdeye_pos_value=0,rdeye_pos_max,rdeye_neg_value=0,rdeye_neg_max;
	u32 rdeye_vref_first=0,rdeye_vref_last=0;
	int i;
	if(0 == is_dmc_phy_train_en(TRAIN_RDEYE_INDEX))
	{
		return;
	}
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("\r\n-------------rdeye training---------------\r\n");
#endif
	// train enable
	dmc_phy_train_en(TRAIN_RDEYE_INDEX);
	wait_100ns(1);
	if(train_count==1)
	{
		if(train_info.odt_status)
		{
			vrefdq_min=(dram_info.dram_type==DRAM_LP4X)?LP4X_RDEYE_ODT_VREFDQ_MIN:LP4_RDEYE_ODT_VREFDQ_MIN;
			vrefdq_max=(dram_info.dram_type==DRAM_LP4X)?LP4X_RDEYE_ODT_VREFDQ_MAX:LP4_RDEYE_ODT_VREFDQ_MAX;
		}else
		{
			vrefdq_min=(dram_info.dram_type==DRAM_LP4X)?LP4X_RDEYE_VREFDQ_MIN:LP4_RDEYE_VREFDQ_MIN;
			vrefdq_max=(dram_info.dram_type==DRAM_LP4X)?LP4X_RDEYE_VREFDQ_MAX:LP4_RDEYE_VREFDQ_MAX;
		}
	}else
	{
		vrefdq_min=(train_info.vrefdq_rd_val_chn0+train_info.vrefdq_rd_val_chn1)/2;
		vrefdq_max=(train_info.vrefdq_rd_val_chn0+train_info.vrefdq_rd_val_chn1)/2;
	}
	for(vrefdq_val=vrefdq_min;vrefdq_val<=vrefdq_max;vrefdq_val+=vrefdq_step)
	{
		//train clear
		rf_train_clear();
		reg_bit_set(DMC_CTL0_(0x010c),12,1,0x1);//rf_auto_ref_en
		wait_100ns(2);
		//set vrefdq at BB
		reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),23,1,0x0);
		reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),24,8,vrefdq_val);
		//train start
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
		wait_100ns(1);
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("train_count==");
		print_Hex(train_count);
		dmc_print_str("rdeye training vref:");
		print_Hex(vrefdq_val);
		dmc_print_str("    ");
#endif
		if(train_count==1)
			dmc_phy_train_polling_done(TRAIN_RDEYE_INDEX,2);
		else
			dmc_phy_train_polling_done(TRAIN_RDEYE_INDEX,1);
		/*Get taining Result */
		pass_win_temp=(__raw_readl(DMC_CTL0_(0x0170))>>(train_info.train_chn_num?16:0))&0xff;
		for(i=0;i<4;i++)
		{
			rdeye_pos_value |=  ((__raw_readl(DMC_PHY0_(0x0070+i*0x20+train_info.ddr_freq_num*0xc0))&0xff)<<(i*8));
			rdeye_neg_value |=  ((__raw_readl(DMC_PHY0_(0x0074+i*0x20+train_info.ddr_freq_num*0xc0))&0xff)<<(i*8));
		}
		/*
		rdeye_pos_value=((__raw_readl(DMC_PHY0_(0x0070+train_info.ddr_freq_num*0xc0))&0x7f)<<0)
							|((__raw_readl(DMC_PHY0_(0x0090+train_info.ddr_freq_num*0xc0))&0x7f)<<8)
							|((__raw_readl(DMC_PHY0_(0x00b0+train_info.ddr_freq_num*0xc0))&0x7f)<<16)
							|((__raw_readl(DMC_PHY0_(0x00d0+train_info.ddr_freq_num*0xc0))&0x7f)<<24);
		rdeye_neg_value=((__raw_readl(DMC_PHY0_(0x0074+train_info.ddr_freq_num*0xc0))&0x7f)<<0)
							|((__raw_readl(DMC_PHY0_(0x0094+train_info.ddr_freq_num*0xc0))&0x7f)<<8)
							|((__raw_readl(DMC_PHY0_(0x00b4+train_info.ddr_freq_num*0xc0))&0x7f)<<16)
							|((__raw_readl(DMC_PHY0_(0x00d4+train_info.ddr_freq_num*0xc0))&0x7f)<<24);
		*/
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("Pass Window Value:");
		print_Hex(__raw_readl(DMC_CTL0_(0x0170)));
		dmc_print_str("    ");
		dmc_print_str("Pos Pass Value:");
		print_Hex(rdeye_pos_value);
		dmc_print_str("    ");
		dmc_print_str("Neg Pass Value:");
		print_Hex(rdeye_neg_value);
#endif
		if(train_count==1)/*Get Max pass window and relevant value*/
		{
			if(vrefdq_val != vrefdq_min) {
				if(last_pass_win_temp>pass_win_temp)
				{
					if(last_pass_win_temp-pass_win_temp > 2)
						pass_win_temp = last_pass_win_temp-2;
				} else {
					if(pass_win_temp-last_pass_win_temp > 2)
						pass_win_temp = last_pass_win_temp+2;
				}
			}
			last_pass_win_temp = pass_win_temp;
#if TEST_DEBUG_LOG_LEVEL>2
			dmc_print_str("Now Pass Window Value is:");
			print_Hex(pass_win_temp);
			dmc_print_str("\r\n");
#endif

			if(pass_win_temp>pass_win_max)
			{
				pass_win_max=pass_win_temp;
				rdeye_pos_max=rdeye_pos_value;
				rdeye_neg_max=rdeye_neg_value;
				rdeye_vref_first=vrefdq_val;
			}else if(pass_win_temp==pass_win_max)
			{
				rdeye_vref_last=vrefdq_val;
			}
		}else
		{
			pass_win_max=pass_win_temp;
			rdeye_pos_max=rdeye_pos_value;
			rdeye_neg_max=rdeye_neg_value;
		}
		//train start clear
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
	}
#ifdef DDR_SCAN_ENABLE
	if(train_info.ddr_clk ==scan_target_clk)
		pass_win_max_scan[train_info.train_chn_num] |= (pass_win_max << 16);
#endif
	if(pass_win_max==0){
#if TEST_DEBUG_LOG_LEVEL>1
		dmc_print_str("\r\nrdeye training pass window is zero!!!");
#endif
		while(1);
	}
	/*Deal with training result for delay cells*/
	for(byte_num=0;byte_num<4;byte_num++)
	{
		reg_bit_set(DMC_PHY0_(0x0070+train_info.ddr_freq_num*0xc0+0x20*byte_num),0,8,(rdeye_pos_max>>(8*byte_num))&0xff);
		reg_bit_set(DMC_PHY0_(0x0074+train_info.ddr_freq_num*0xc0+0x20*byte_num),0,8,(rdeye_neg_max>>(8*byte_num))&0xff);
	}
	dmc_phy_soft_update();//Make the setting take effect
	//disable auto refresh
	//reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);
	wait_100ns(2);
	/*Set training vref and Update vref global variable */
	if(train_count==1)
	{
		//update rd vref
		if(rdeye_vref_last<rdeye_vref_first)
		{
			rdeye_vref_last=rdeye_vref_first;
		}
		train_info.vrefdq_rd_val=(rdeye_vref_first+rdeye_vref_last)/2;//take average for first vref and last vref
		(phy_tmg+train_info.ddr_freq_num)->cfg_io_ds_cfg &= ~(0xFF<<24);//clear
		(phy_tmg+train_info.ddr_freq_num)->cfg_io_ds_cfg |= (train_info.vrefdq_rd_val<<24);//[31:24]rf_phy_io_vrefi_adj:update global variable
		//enable auto refresh
		//reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);
#if TEST_DEBUG_LOG_LEVEL>2
		print_Hex(rdeye_vref_first);
		dmc_print_str("	");
		print_Hex(rdeye_vref_last);
		dmc_print_str("RDEYE Vref Value:");
		print_Hex(train_info.vrefdq_rd_val);
		dmc_print_str("\r\n");
#endif
		//set rf_phy_io_vrefi_adj
		reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),24,8,train_info.vrefdq_rd_val);
		//clear
		rf_train_clear();
		if(train_info.train_chn_num == 0)
			train_info.vrefdq_rd_val_chn0 = train_info.vrefdq_rd_val;
		else if(train_info.train_chn_num == 1)
			train_info.vrefdq_rd_val_chn1 = train_info.vrefdq_rd_val;
	}
	//enable auto refresh
	//reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);
}

void dmc_phy_train_lp4_rddsk(u32* eye_retry)
{
	u32 byte0_bit_dly_val[8];
	u32 byte1_bit_dly_val[8];
	u32 byte0_bit_dly_addr;
	u32 byte1_bit_dly_addr;
	u32 cs1_byte0_bit_dly_addr;
	u32 cs1_byte1_bit_dly_addr;
	u32 val;
	u32 i;
	if(0 == is_dmc_phy_train_en(TRAIN_RDDSK_INDEX))
	{
		*eye_retry=0;
		return;
	}
	if( train_info.train_chn_num==0 )
	{
		if( rddsk_done==1 )
		{
			*eye_retry=1;
			return;
		}
		rddsk_done=1;
	}
	else
	{
		if( ch1_rddsk_done==1 )
		{
			*eye_retry=1;
			return;
		}
		ch1_rddsk_done=1;
	}
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("\r\n");
	print_Hex(train_info.ddr_freq_num);
	dmc_print_str("---------rddsk training---------------\r\n");
#endif
	if( train_info.train_chn_num == 0 )
	{
		byte0_bit_dly_addr = 0x6e8;
		byte1_bit_dly_addr = 0x728;
		cs1_byte0_bit_dly_addr = 0x7c8;
		cs1_byte1_bit_dly_addr = 0x7dc;
	}
	else
	{
		byte0_bit_dly_addr = 0x768;
		byte1_bit_dly_addr = 0x7a8;
		cs1_byte0_bit_dly_addr = 0x7f0;
		cs1_byte1_bit_dly_addr = 0x804;
	}
	for(i=0; i<8; i++)
	{
		byte0_bit_dly_val[i] = 0;
		byte1_bit_dly_val[i] = 0;
	}
	// train enable
	dmc_phy_train_en(TRAIN_RDDSK_INDEX);
	for(i=0; i<4; i=i+1 )
	{
	//train clear
	rf_train_clear();
	//set vrefdq at BB
	//reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),23,1,0x0);
	//reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),24,8,0x50);
	//train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//Enable rf_train_start
	wait_100ns(1);
	dmc_phy_train_polling_done(TRAIN_RDDSK_INDEX,1);
	//train start clear
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//Disable rf_train_start
	val=__raw_readl(DMC_PHY0_(byte0_bit_dly_addr));
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("byte0_bit_dly_addr_: ");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif

	byte0_bit_dly_val[0] += (val&0xff);
	byte0_bit_dly_val[1] += ((val>>8) & 0xff);
	byte0_bit_dly_val[2] += ((val>>16) & 0xff);
	byte0_bit_dly_val[3] += ((val>>24) & 0xff);
	val=__raw_readl(DMC_PHY0_(byte0_bit_dly_addr+4));
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("byte0_bit_dly_addr+4: ");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif
	byte0_bit_dly_val[4] += (val&0xff);
	byte0_bit_dly_val[5] += ((val>>8) & 0xff);
	byte0_bit_dly_val[6] += ((val>>16) & 0xff);
	byte0_bit_dly_val[7] += ((val>>24) & 0xff);
	val=__raw_readl(DMC_PHY0_(byte1_bit_dly_addr));
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("byte1_bit_dly_addr_: ");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif
	byte1_bit_dly_val[0] += (val&0xff);
	byte1_bit_dly_val[1] += ((val>>8) & 0xff);
	byte1_bit_dly_val[2] += ((val>>16) & 0xff);
	byte1_bit_dly_val[3] += ((val>>24) & 0xff);
	val=__raw_readl(DMC_PHY0_(byte1_bit_dly_addr+4));
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("byte1_bit_dly_addr+4: ");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif
	byte1_bit_dly_val[4] += (val&0xff);
	byte1_bit_dly_val[5] += ((val>>8) & 0xff);
	byte1_bit_dly_val[6] += ((val>>16) & 0xff);
	byte1_bit_dly_val[7] += ((val>>24) & 0xff);
	}
	val = ((byte0_bit_dly_val[3]>>2)<<24) |((byte0_bit_dly_val[2]>>2)<<16)|((byte0_bit_dly_val[1]>>2)<<8)|(byte0_bit_dly_val[0]>>2);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("byte0_bit_dly_addr_:final ");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif

	__raw_writel(DMC_PHY0_(byte0_bit_dly_addr), val);
	__raw_writel(DMC_PHY0_(cs1_byte0_bit_dly_addr), val);
	val = ((byte0_bit_dly_val[7]>>2)<<24) |((byte0_bit_dly_val[6]>>2)<<16)|((byte0_bit_dly_val[5]>>2)<<8)|(byte0_bit_dly_val[4]>>2);
	__raw_writel(DMC_PHY0_(byte0_bit_dly_addr+4), val);
	__raw_writel(DMC_PHY0_(cs1_byte0_bit_dly_addr+4), val);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("byte0_bit_dly_addr+4:final ");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif

	val = ((byte1_bit_dly_val[3]>>2)<<24) |((byte1_bit_dly_val[2]>>2)<<16)|((byte1_bit_dly_val[1]>>2)<<8)|(byte1_bit_dly_val[0]>>2);
	__raw_writel(DMC_PHY0_(byte1_bit_dly_addr), val);
	__raw_writel(DMC_PHY0_(cs1_byte1_bit_dly_addr), val);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("byte1_bit_dly_addr_:final ");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif

	val = ((byte1_bit_dly_val[7]>>2)<<24) |((byte1_bit_dly_val[6]>>2)<<16)|((byte1_bit_dly_val[5]>>2)<<8)|(byte1_bit_dly_val[4]>>2);
	 __raw_writel(DMC_PHY0_(byte1_bit_dly_addr+4), val);
	__raw_writel(DMC_PHY0_(cs1_byte1_bit_dly_addr+4), val);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("byte1_bit_dly_addr+4:final ");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif

	*eye_retry=1;
	return;
}

void dmc_phy_train_lp4_vrefdq_set(u32 vref_val)
{
	u32 mr14;
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x0);//rf_auto_ref_en
	wait_100ns(2);
	reg_bit_set(DMC_CTL0_(0x0100),20, 4,(1<<train_info.train_chn_num));
	dmc_mrw(DRAM_MR_14,DRAM_CS_ALL,vref_val);
	dmc_phy_soft_update();
	wait_100ns(100);
	dmc_mrr(DRAM_MR_14,DRAM_CS_ALL,&mr14);
	if(((mr14>>(train_info.train_chn_num*8))&0xff)!= vref_val)
		while(1);
	reg_bit_set(DMC_CTL0_(0x0104),31, 1,0x0);//dsoft_cmd_allcs off
	wait_100ns(5);
	reg_bit_set(DMC_CTL0_(0x0100),20, 4,0x3);//dsoft ch sel ch0,1
	wait_100ns(2);
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x1);//rf_auto_ref_en

}

void dmc_phy_train_lp4_wreye_cs0(u32 train_count)
{
	u32 vrefdq_val=0,vrefdq_step=2,vrefdq_min,vrefdq_max;
	u32 pass_win_max,pass_win_temp,last_pass_win_temp;
	u32 wreye_value,wreye_vref,wreye_val_cs0;
	u32 wreye_vref_first=0,wreye_vref_last=0;
	pass_win_max=0;
	wreye_val_cs0=0;
	wreye_vref=0;
	if(0 == is_dmc_phy_train_en(TRAIN_WREYE_INDEX))
	{
		return;
	}
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("\r\n-------------wreye cs0 training---------------\r\n");
#endif
	//train enable
	dmc_phy_train_en(TRAIN_WREYE_INDEX);
	if(train_count == 1)
	{
		if(train_info.odt_status)
		{
			vrefdq_min=(dram_info.dram_type==DRAM_LP4X)?LP4X_WREYE_ODT_VREFDQ_MIN:LP4_WREYE_ODT_VREFDQ_MIN;
			vrefdq_max=(dram_info.dram_type==DRAM_LP4X)?LP4X_WREYE_ODT_VREFDQ_MAX:LP4_WREYE_ODT_VREFDQ_MAX;
		}else
		{
			vrefdq_min=(dram_info.dram_type==DRAM_LP4X)?LP4X_WREYE_VREFDQ_MIN:LP4_WREYE_VREFDQ_MIN;
			vrefdq_max=(dram_info.dram_type==DRAM_LP4X)?LP4X_WREYE_VREFDQ_MAX:LP4_WREYE_VREFDQ_MAX;
		}
	}else
	{
		vrefdq_min=(train_info.vrefdq_wr_val_chn0+train_info.vrefdq_wr_val_chn1)/2;
		vrefdq_max=(train_info.vrefdq_wr_val_chn0+train_info.vrefdq_wr_val_chn1)/2;
	}
	for(vrefdq_val=vrefdq_min;vrefdq_val<=vrefdq_max;vrefdq_val += vrefdq_step)
	{
		//train clear
		rf_train_clear();
		//set dq vref
		dmc_phy_train_lp4_vrefdq_set(vrefdq_val);
		//set pass window
		reg_bit_set(DMC_CTL0_(0x0164),16, 8,WREYE_PASS_WIN_MIN);
		//start train
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
		wait_100ns(1);
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("train_count==");
		print_Hex(train_count);
		dmc_print_str("wreye training vref:");
		print_Hex(vrefdq_val);
		dmc_print_str("    ");
#endif
		if(train_count==1)
			dmc_phy_train_polling_done(TRAIN_WREYE_INDEX,2);
		else
			dmc_phy_train_polling_done(TRAIN_WREYE_INDEX,1);
		//[7:0]byte0_pass_window [15:8]byte1_pass_window [23:16]:byte2_pass_window [31:24]byte3_pass_window
		//train_ch 0:wreye_pass_window = byte0_pass_window
		//train_ch 1:wreye_pass_window = byte2_pass_window

		//Get training result
		pass_win_temp=(__raw_readl(DMC_CTL0_(0x0170))>>(train_info.train_chn_num*16))&0xff;
		wreye_val_cs0=((__raw_readl(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40))&0xff)<<0)
							|((__raw_readl(DMC_PHY0_(0x008c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40))&0xff)<<8);
#if TEST_DEBUG_LOG_LEVEL>2

		dmc_print_str("Pass Window Value:");
		print_Hex(__raw_readl(DMC_CTL0_(0x0170)));
		dmc_print_str("    ");
		dmc_print_str("Pass Value:");
		print_Hex(__raw_readl(DMC_CTL0_(0x016C)));
#endif
		if(train_count==1)//Get MAX pass window and relevant vref
		{
			if(vrefdq_val != vrefdq_min) {
				if(last_pass_win_temp>pass_win_temp)
				{
					if(last_pass_win_temp-pass_win_temp > 2)
						pass_win_temp = last_pass_win_temp-2;
				} else {
					if(pass_win_temp-last_pass_win_temp > 2)
						pass_win_temp = last_pass_win_temp+2;
				}
			}
			last_pass_win_temp = pass_win_temp;
#if TEST_DEBUG_LOG_LEVEL>2
					dmc_print_str("Now Pass Window Value is:");
					print_Hex(pass_win_temp);
#endif
			if(pass_win_temp>pass_win_max)
			{
				pass_win_max=pass_win_temp;
				wreye_val_cs0_max=wreye_val_cs0;
				wreye_vref_first=vrefdq_val;
			}else if(pass_win_temp==pass_win_max)
			{
				wreye_vref_last=vrefdq_val;
			}
		}else
		{
			pass_win_max=pass_win_temp;
			wreye_val_cs0_max=wreye_val_cs0;
		}
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("wreye_val_cs0_max:");
		print_Hex(wreye_val_cs0_max);
		dmc_print_str("\r\n");
#endif

		//clear train start
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
	}
	//train clear
	rf_train_clear();
#ifdef DDR_SCAN_ENABLE
	if(train_info.ddr_clk ==scan_target_clk)
		pass_win_max_scan[train_info.train_chn_num] |= pass_win_max;
#endif
	if(pass_win_max==0)
	{
		dmc_print_str("wreye training pass window is zero!!!");
		while(1);
	}
	//set training result
	reg_bit_set(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),0,8,(wreye_val_cs0>>0)&0xff);
	reg_bit_set(DMC_PHY0_(0x008c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),0,8,(wreye_val_cs0>>8)&0xff);
	dmc_phy_soft_update();
	/*if(train_count != 1)
	{
		if((((wreye_val_cs0>>0)&0xff)>((wreye_val_cs0>>8)&0xff))&&((((wreye_val_cs0>>0)&0xff)-((wreye_val_cs0>>8)&0xff))>0x10))
		{
			//dmc_print_str("\r\nwreye training result is abnormal 0\r\n");
			while(1);
		}
		if((((wreye_val_cs0>>0)&0xff)<((wreye_val_cs0>>8)&0xff))&&((((wreye_val_cs0>>8)&0xff)-((wreye_val_cs0>>0)&0xff))>0x10))
		{
			//dmc_print_str("\r\nwreye training result is abnormal 1\r\n");
			while(1);
		}
	}*/
	wait_100ns(2);
	if(train_count==1)
	{
		if(wreye_vref_last<wreye_vref_first)
		{
			wreye_vref_last=wreye_vref_first;
		}
		train_info.vrefdq_wr_val=(wreye_vref_first+wreye_vref_last)/2;//get vref average
		//set training vref for mr14
		dmc_phy_train_lp4_vrefdq_set(train_info.vrefdq_wr_val);
#if TEST_DEBUG_LOG_LEVEL>2
		print_Hex(wreye_vref_first);
		dmc_print_str("	");
		print_Hex(wreye_vref_last);
		dmc_print_str("WREYE Vref Value:");
		print_Hex(train_info.vrefdq_wr_val);
		dmc_print_str("\r\n");
#endif
		//update global variable for wr vref
		(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12 &= ~(0xFF<<0);
		(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12 |= (train_info.vrefdq_wr_val<<0);

		//This field indicated the MRW value used to change MRW value during DFS
		//MR14
		__raw_writel(DMC_CTL0_(0x01b0+train_info.ddr_freq_num*0x60), (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12);
		//clear
		rf_train_clear();
		if(train_info.train_chn_num == 0)
			train_info.vrefdq_wr_val_chn0 = train_info.vrefdq_wr_val;
		else if(train_info.train_chn_num == 1)
			train_info.vrefdq_wr_val_chn1 = train_info.vrefdq_wr_val;
	}
	//enable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);
	rf_train_clear();
}
void dmc_phy_train_lp4_adjust_cycle_cs(u32 *byte0_dqeye_value, u32 *byte1_dqeye_value, u32 *byte0_dqeye_pass_win, u32 *byte1_dqeye_pass_win, u32 cs_num)
{
	int reg_bit_offset = 0;
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("\r\n-------------dmc_phy_train_lp4_adjust_cycle wrdsk training---------------\r\n");
#endif
	dmc_phy_train_info_pre_set(train_info.train_chn_num,cs_num);
	// train enable
	dmc_phy_train_en(TRAIN_WRDSK_INDEX);
	//train clear
	rf_train_clear();

	//train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//Enable rf_train_start
	wait_100ns(1);

	dmc_phy_train_polling_done(TRAIN_WRDSK_INDEX,2);

	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//Disable rf_train_start
	reg_bit_offset = train_info.train_chn_num?16:0;
	*byte0_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),reg_bit_offset+0,8);
	*byte1_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),reg_bit_offset+8,8);
	*byte0_dqeye_pass_win=reg_bit_get(DMC_CTL0_(0x170),reg_bit_offset+0,8);
	*byte1_dqeye_pass_win=reg_bit_get(DMC_CTL0_(0x170),reg_bit_offset+8,8);
}

void dmc_phy_train_lp4_adjust_cycle ()
{
	u32 cs0_byte0_dqeye_value=0;
	u32 cs0_byte1_dqeye_value=0;
	u32 cs0_byte0_dqeye_pass_win=0;
	u32 cs0_byte1_dqeye_pass_win=0;
	u32 cs1_byte0_dqeye_value=0;
	u32 cs1_byte1_dqeye_value=0;
	u32 cs1_byte0_dqeye_pass_win=0;
	u32 cs1_byte1_dqeye_pass_win=0;
	u32 reg_offset = 0;
	u32 wrdsk_train_value[24];
	int i;
	//save
	for(i=0; i<24; i++)
	{
		wrdsk_train_value[i] = __raw_readl(wrdsk_train_address[i]);
	}
	/*
	if(0 == is_dmc_phy_train_en(TRAIN_WRDSK_INDEX))
	{
		return;
	}*/
	dmc_phy_train_lp4_adjust_cycle_cs(&cs0_byte0_dqeye_value, &cs0_byte1_dqeye_value, &cs0_byte0_dqeye_pass_win , &cs0_byte1_dqeye_pass_win, DRAM_CS_0);
	if(dram_info.cs_num==DRAM_CS_ALL)
		dmc_phy_train_lp4_adjust_cycle_cs(&cs1_byte0_dqeye_value, &cs1_byte1_dqeye_value, &cs1_byte0_dqeye_pass_win , &cs1_byte1_dqeye_pass_win, DRAM_CS_1);
	reg_offset = train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40;
	if(dram_info.cs_num==DRAM_CS_ALL) {
		if( (cs0_byte0_dqeye_value==0x0) ||  (cs1_byte0_dqeye_value==0x0) || ((cs0_byte0_dqeye_value-cs0_byte0_dqeye_pass_win) > 0x90) && ((cs1_byte0_dqeye_value-cs1_byte0_dqeye_pass_win) > 0x90) )
		{
			reg_bit_set(DMC_PHY0_(0x006c+reg_offset),23,1,1);//rf_clkwr_raw_2cycle_0_sel
		}
		else if(((cs0_byte0_dqeye_value-cs0_byte0_dqeye_pass_win) > 0x50) && ((cs1_byte0_dqeye_value-cs1_byte0_dqeye_pass_win) > 0x50) )
		{
			reg_bit_set(DMC_PHY0_(0x006c+reg_offset),23,1,1);//rf_clkwr_raw_2cycle_0_sel
			reg_bit_set(DMC_PHY0_(0x006c+reg_offset),15,1,0);//rf_clkwr_raw_cycle_0_sel
		}

		if( (cs0_byte1_dqeye_value==0x0) ||  (cs1_byte1_dqeye_value==0x0) || ((cs0_byte1_dqeye_value-cs0_byte1_dqeye_pass_win) > 0x90) && ((cs1_byte1_dqeye_value-cs1_byte1_dqeye_pass_win) > 0x90))
		{
			reg_bit_set(DMC_PHY0_(0x008c+reg_offset),23,1,1);//rf_clkwr_raw_2cycle_0_sel
		}
		else if(((cs0_byte1_dqeye_value-cs0_byte1_dqeye_pass_win) > 0x50) && ((cs1_byte1_dqeye_value-cs1_byte1_dqeye_pass_win) > 0x50) )
		{
			reg_bit_set(DMC_PHY0_(0x008c+reg_offset),23,1,1);//rf_clkwr_raw_2cycle_0_sel
			reg_bit_set(DMC_PHY0_(0x008c+reg_offset),15,1,0);//rf_clkwr_raw_cycle_0_sel
		}
	} else {
		if( (cs0_byte0_dqeye_value==0x0)  || ((cs0_byte0_dqeye_value-cs0_byte0_dqeye_pass_win) > 0x90) )
		{
			reg_bit_set(DMC_PHY0_(0x006c+reg_offset),23,1,1);//rf_clkwr_raw_2cycle_0_sel
		}
		else if(((cs0_byte0_dqeye_value-cs0_byte0_dqeye_pass_win) > 0x50))
		{
			reg_bit_set(DMC_PHY0_(0x006c+reg_offset),23,1,1);//rf_clkwr_raw_2cycle_0_sel
			reg_bit_set(DMC_PHY0_(0x006c+reg_offset),15,1,0);//rf_clkwr_raw_cycle_0_sel
		}

		if( (cs0_byte1_dqeye_value==0x0)  || ((cs0_byte1_dqeye_value-cs0_byte1_dqeye_pass_win) > 0x90))
		{
			reg_bit_set(DMC_PHY0_(0x008c+reg_offset),23,1,1);//rf_clkwr_raw_2cycle_0_sel
		}
		else if(((cs0_byte1_dqeye_value-cs0_byte1_dqeye_pass_win) > 0x50))
		{
			reg_bit_set(DMC_PHY0_(0x008c+reg_offset),23,1,1);//rf_clkwr_raw_2cycle_0_sel
			reg_bit_set(DMC_PHY0_(0x008c+reg_offset),15,1,0);//rf_clkwr_raw_cycle_0_sel
		}
	}

	//train clear
	rf_train_clear();
	#if TEST_DEBUG_LOG_LEVEL >3
	dmc_print_str("\r\n-------------dmc_phy_train_lp4_adjust_cycle---------------\r\n");
	dmc_print_str("\r\ncs0_byte0_dqeye_value=");
	print_Hex(cs0_byte0_dqeye_value);
	dmc_print_str("\r\ncs0_byte1_dqeye_value");
	print_Hex(cs0_byte1_dqeye_value);
	dmc_print_str("\r\ncs0_byte0_dqeye_pass_win");
	print_Hex(cs0_byte0_dqeye_pass_win);
	dmc_print_str("\r\ncs0_byte1_dqeye_pass_win");
	print_Hex(cs0_byte1_dqeye_pass_win);
	dmc_print_str("\r\ncs1_byte0_dqeye_value=");
	print_Hex(cs1_byte0_dqeye_value);
	dmc_print_str("\r\ncs1_byte1_dqeye_value");
	print_Hex(cs1_byte1_dqeye_value);
	dmc_print_str("\r\ncs1_byte0_dqeye_pass_win");
	print_Hex(cs1_byte0_dqeye_pass_win);
	dmc_print_str("\r\ncs1_byte1_dqeye_pass_win");
	print_Hex(cs1_byte1_dqeye_pass_win);
	#endif
	//restore
	for(i=0; i<24; i++)
	{
		 __raw_writel(wrdsk_train_address[i], wrdsk_train_value[i]);
	}
	//Manual Clear perbit training delay(this function only chose cycle so dsk delay line invalid)
	/*__raw_writel(0x310016e0,0x0);//rf_dly_out d0~d3
	__raw_writel(0x310016e4,0x0);//rf_dly_out d4~d7
	reg_bit_set(0X310016F0,8,8,0x0);//rf_dly_out_dqm_dl0_0_sel
	*/
}


void dmc_phy_train_lp4_wrdsk(u32* eye_retry,u32 train_num)
{
	u32 byte0_bit_dly_val[9];
	u32 byte1_bit_dly_val[9];
	u32 byte0_bit_dly_addr;
	u32 byte1_bit_dly_addr;
	u32 val;
	u32 i;
	if(0 == is_dmc_phy_train_en(TRAIN_WRDSK_INDEX))
	{
		*eye_retry=0;
		return;
	}
	if( train_info.train_chn_num== 0 && train_info.train_cs_num == DRAM_CS_0 )
	{
		if( wrdsk_done==1)
		{
			*eye_retry=1;
			return;
		}
		wrdsk_done = 1;
	}
	else if( train_info.train_chn_num== 0 && train_info.train_cs_num == DRAM_CS_1 )
	{
		if( cs1_wrdsk_done==1)
		{
			*eye_retry=1;
			return;
		}
		cs1_wrdsk_done = 1;
	}
	else if( train_info.train_chn_num== 1 && train_info.train_cs_num == DRAM_CS_0 )
	{
		if( ch1_cs0_wrdsk_done==1)
		{
			*eye_retry=1;
			return;
		}
		ch1_cs0_wrdsk_done = 1;
	}
	else if( train_info.train_chn_num== 1 && train_info.train_cs_num == DRAM_CS_1 )
	{
		if( ch1_cs1_wrdsk_done==1)
		{
			*eye_retry=1;
			return;
		}
		ch1_cs1_wrdsk_done = 1;
	}
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("\r\n");
		print_Hex(train_info.ddr_freq_num);
		dmc_print_str("-------------wrdsk training---------------\r\n");
#endif
	if( train_info.train_chn_num == 0 )
	{
		if( train_info.train_cs_num == 0 )
		{
			byte0_bit_dly_addr = 0x6e0;
			byte1_bit_dly_addr = 0x720;
		}
		else
		{
			byte0_bit_dly_addr = 0x7c0;
			byte1_bit_dly_addr = 0x7d4;
		}
	}
	else
	{
		if( train_info.train_cs_num == 0 )
		{
			byte0_bit_dly_addr = 0x760;
			byte1_bit_dly_addr = 0x7a0;
		}
		else
		{
			byte0_bit_dly_addr = 0x7e8;
			byte1_bit_dly_addr = 0x7fc;
		}
	}
	for(i=0; i<9; i++)
	{
		byte0_bit_dly_val[i] = 0;
		byte1_bit_dly_val[i] = 0;
	}
	// train enable
	dmc_phy_train_en(TRAIN_WRDSK_INDEX);
	for(i=0; i<8; i=i+1)
	{
		//train clear
		rf_train_clear();

		//train start
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//Enable rf_train_start
		wait_100ns(1);

		//If First wrdsk training fail adjust parameter and repeat wrdsk training
		dmc_phy_train_polling_done(TRAIN_WRDSK_INDEX,1);//if fail=>while(1)
		//start train clear
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//Disable rf_train_start
		val=__raw_readl(DMC_PHY0_(byte0_bit_dly_addr));
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("write byte0_bit_dly_addr_: ");
		print_Hex(DMC_PHY0_(byte0_bit_dly_addr));
		dmc_print_str(":");
		print_Hex(val);
		dmc_print_str("\r\n");
#endif
		byte0_bit_dly_val[0] += (val&0xff);
		byte0_bit_dly_val[1] += ((val>>8) & 0xff);
		byte0_bit_dly_val[2] += ((val>>16) & 0xff);
		byte0_bit_dly_val[3] += ((val>>24) & 0xff);
		val=__raw_readl(DMC_PHY0_(byte0_bit_dly_addr+4));
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("write byte0_bit_dly_addr+4: ");
		print_Hex(DMC_PHY0_(byte0_bit_dly_addr+4));
		dmc_print_str(":");
		print_Hex(val);
		dmc_print_str("\r\n");
#endif
		byte0_bit_dly_val[4] += (val&0xff);
		byte0_bit_dly_val[5] += ((val>>8) & 0xff);
		byte0_bit_dly_val[6] += ((val>>16) & 0xff);
		byte0_bit_dly_val[7] += ((val>>24) & 0xff);
		val=__raw_readl(DMC_PHY0_(byte0_bit_dly_addr+0x10));
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("write byte0_bit_dly_addr+0x10: ");
		print_Hex(DMC_PHY0_(DMC_PHY0_(byte0_bit_dly_addr+0x10)));
		dmc_print_str(":");
		print_Hex(val);
		dmc_print_str("\r\n");
#endif
		byte0_bit_dly_val[8] += ((val>>8) & 0xff);
		val=__raw_readl(DMC_PHY0_(byte1_bit_dly_addr));
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("write byte1_bit_dly_addr_: ");
		print_Hex(DMC_PHY0_(byte1_bit_dly_addr));
		dmc_print_str(":");
		print_Hex(val);
		dmc_print_str("\r\n");
#endif
		byte1_bit_dly_val[0] += (val&0xff);
		byte1_bit_dly_val[1] += ((val>>8) & 0xff);
		byte1_bit_dly_val[2] += ((val>>16) & 0xff);
		byte1_bit_dly_val[3] += ((val>>24) & 0xff);
		val=__raw_readl(DMC_PHY0_(byte1_bit_dly_addr+4));
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("write byte1_bit_dly_addr+4: ");
		print_Hex(DMC_PHY0_(byte1_bit_dly_addr+4));
		dmc_print_str(":");
		print_Hex(val);
		dmc_print_str("\r\n");
#endif
		byte1_bit_dly_val[4] += (val&0xff);
		byte1_bit_dly_val[5] += ((val>>8) & 0xff);
		byte1_bit_dly_val[6] += ((val>>16) & 0xff);
		byte1_bit_dly_val[7] += ((val>>24) & 0xff);
		val=__raw_readl(DMC_PHY0_(byte1_bit_dly_addr+0x10));
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("write byte1_bit_dly_addr+0x10: ");
		print_Hex(DMC_PHY0_(byte1_bit_dly_addr+0x10));
		dmc_print_str(":");
		print_Hex(val);
		dmc_print_str("\r\n");
#endif
		byte1_bit_dly_val[8] += ((val>>8) & 0xff);
	}
	val = ((byte0_bit_dly_val[3]>>3)<<24) |((byte0_bit_dly_val[2]>>3)<<16)|((byte0_bit_dly_val[1]>>3)<<8)|(byte0_bit_dly_val[0]>>3);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("write byte0_bit_dly_addr_:final ");
	print_Hex(DMC_PHY0_(byte0_bit_dly_addr));
	dmc_print_str(":");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif
	__raw_writel(DMC_PHY0_(byte0_bit_dly_addr), val);
	val = ((byte0_bit_dly_val[7]>>3)<<24) |((byte0_bit_dly_val[6]>>3)<<16)|((byte0_bit_dly_val[5]>>3)<<8)|(byte0_bit_dly_val[4]>>3);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("write byte0_bit_dly_addr+4:final ");
	print_Hex(DMC_PHY0_(byte0_bit_dly_addr+4));
	dmc_print_str(":");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif
	__raw_writel(DMC_PHY0_(byte0_bit_dly_addr+4), val);
	val = ((byte0_bit_dly_val[8]>>3)<<8);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("write byte0_bit_dly_addr+0x10:final ");
	print_Hex(DMC_PHY0_(byte0_bit_dly_addr+0x10));
	dmc_print_str(":");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif
	__raw_writel(DMC_PHY0_(byte0_bit_dly_addr+0x10), val);

	val = ((byte1_bit_dly_val[3]>>3)<<24) |((byte1_bit_dly_val[2]>>3)<<16)|((byte1_bit_dly_val[1]>>3)<<8)|(byte1_bit_dly_val[0]>>3);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("write byte1_bit_dly_addr_:final ");
	print_Hex(DMC_PHY0_(byte1_bit_dly_addr));
	dmc_print_str(":");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif
	__raw_writel(DMC_PHY0_(byte1_bit_dly_addr), val);
	val = ((byte1_bit_dly_val[7]>>3)<<24) |((byte1_bit_dly_val[6]>>3)<<16)|((byte1_bit_dly_val[5]>>3)<<8)|(byte1_bit_dly_val[4]>>3);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("write byte1_bit_dly_addr+4:final ");
	print_Hex(DMC_PHY0_(byte1_bit_dly_addr+4));
	dmc_print_str(":");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif
	__raw_writel(DMC_PHY0_(byte1_bit_dly_addr+4), val);
	val = ((byte1_bit_dly_val[8]>>3)<<8);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("write byte1_bit_dly_addr+0x10:final ");
	print_Hex(DMC_PHY0_(byte1_bit_dly_addr+0x10));
	dmc_print_str(":");
	print_Hex(val);
	dmc_print_str("\r\n");
#endif
	__raw_writel(DMC_PHY0_(byte1_bit_dly_addr+0x10), val);

	*eye_retry=1;
	return;
}


void dmc_phy_train_lp4_wreye_cs1()
{
	u32 wreye_val_cs1=0;
	u32 byte_wreye_cs0,byte_wreye_cs1;
	u32 byte_num=0;
	u32 pass_win_temp;
	u32 reg_offset_per_chn=0;
	if((0 == is_dmc_phy_train_en(TRAIN_WREYE_INDEX))||(dram_info.cs_num == 1))
	{
		return;
	}
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("\r\n-------------wreye cs1 training---------------\r\n");
#endif
	//train enable
	dmc_phy_train_en(TRAIN_WREYE_INDEX);
	//train clear
	rf_train_clear();
	//start train
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
	wait_100ns(1);
	dmc_phy_train_polling_done(TRAIN_WREYE_INDEX,1);
	reg_offset_per_chn = train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40;
	pass_win_temp=((__raw_readl(DMC_CTL0_(0x0170))>>(train_info.train_chn_num*16))&0xff);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("    ");
	dmc_print_str("Pass Window Value:");
	print_Hex(__raw_readl(DMC_CTL0_(0x0170)));
	dmc_print_str("    ");
	dmc_print_str("Pass Value:");
	print_Hex(__raw_readl(DMC_CTL0_(0x016C)));
#endif
#ifdef DDR_SCAN_ENABLE
	if(train_info.ddr_clk ==scan_target_clk)
		pass_win_max_scan[train_info.train_chn_num] |= (pass_win_temp << 8);
#endif
		wreye_val_cs1=((__raw_readl(DMC_PHY0_(0x006c+reg_offset_per_chn))&0xff)<<0) //BYE0
								|((__raw_readl(DMC_PHY0_(0x008c+reg_offset_per_chn))&0xff)<<8);//BYTE1
	//Disable start train flag
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//Disable rf_train_start
	wait_100ns(1);
	//one channel ==>two byte
	//Set training result for compare cs0 and cs1 result
	//Choose Max value  set register for cs0 and cs1 training result
	for(byte_num=0;byte_num<2;byte_num++)
	{
#if TEST_DEBUG_LOG_LEVEL>2
				dmc_print_str("dmc_phy_train_lp4_wreye_cs1 wreye_val_cs0_max:");
				print_Hex(wreye_val_cs0_max);
				dmc_print_str("  ");
				dmc_print_str("wreye_val_cs1:");
				print_Hex(wreye_val_cs1);
				dmc_print_str("\r\n");
#endif
		//Set the different value(byte_wreye_cs1 and byte_wreye_cs0 ) to the register
		byte_wreye_cs0=((wreye_val_cs0_max>>(byte_num*8))&0xff);
		byte_wreye_cs1=((wreye_val_cs1>>(byte_num*8))&0xff);
		reg_bit_set(DMC_PHY0_(0x007c+reg_offset_per_chn+byte_num*0x20),1,7,
			(byte_wreye_cs1>byte_wreye_cs0)?(byte_wreye_cs1-byte_wreye_cs0):(byte_wreye_cs0-byte_wreye_cs1));//rf_clkwr_diff_dl_0_sel

		reg_bit_set(DMC_PHY0_(0x007c+reg_offset_per_chn+byte_num*0x20),0,1,
			(byte_wreye_cs1>byte_wreye_cs0)?0x1:0x0);

		reg_bit_set(DMC_PHY0_(0x007c+reg_offset_per_chn+byte_num*0x20),31,1,0x1);//rf_clkwr_diff_dl_0_cpst_en

		reg_bit_set(DMC_PHY0_(0x006c+reg_offset_per_chn+byte_num*0x20),0,8, //rf_clkwr_raw_dl_0_sel
			(byte_wreye_cs1>byte_wreye_cs0)?byte_wreye_cs0:byte_wreye_cs1);
	}
	dmc_phy_soft_update();
}

void dmc_phy_train_lp4_gate()
{
	if(0==is_dmc_phy_train_en(TRAIN_GATE_INDEX))
	{
		return;
	}
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("\r\n-------------gate training---------------\r\n");
#endif
	//train enable
	dmc_phy_train_en(TRAIN_GATE_INDEX);
	wait_100ns(1);
	//train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
	wait_100ns(1);
	//wait train done
	dmc_phy_train_polling_done(TRAIN_GATE_INDEX,1);
	//clear train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
}

void dmc_phy_set_io_ds_dqs_rpull(u32 rpull_value)
{
	//set rf_phy_io_ds_dqs_rpull
	reg_bit_set(DMC_PHY0_(0xf4+train_info.ddr_freq_num*0xc0),20,1,rpull_value&0x01);

}
void dmc_phy_ca_vref_training_prepare()
{
	reg_bit_set(DMC_CTL0_(0x158),7,1,1);//no update for delay line
	//ca training use for cmos mode ch0 and ch1
	//fsp para only effective ch0 so add this function use for ch1
	if( train_info.train_chn_num == 1 )
	{
		reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<train_info.train_chn_num));
		__raw_writel(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0), 0x50700066);
		reg_bit_set(DMC_CTL0_(0x10c),12,1,0x0);//disable auto refresh
		wait_us(2);
		dmc_mrw(DRAM_MR_11,DRAM_CS_ALL,0x00);//set 48ohm for dq and ck odt
		dmc_mrw(DRAM_MR_22,DRAM_CS_ALL,0x3d);//set 48ohm for dq and ck odt
		dmc_mrw(DRAM_MR_14,DRAM_CS_ALL,0x5d);//set DQ vref
		reg_bit_set(DMC_CTL0_(0x10c),12,1,0x1);//Enable auto refresh
	}
}
void dmc_phy_ca_vref_training_restore(u32 flag)
{
  	if(flag==1)
		reg_bit_set(DMC_CTL0_(0x158),7,1,0);// update for delay line
	else if(flag==2)
		{
			if (train_info.ddr_clk > 768)
			{
				reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<train_info.train_chn_num));
				if(train_info.ddr_clk==1024)
				{
					reg_bit_set(DMC_CTL0_(0x10c),12,1,0x0);//disable auto refresh
					dmc_mrw(DRAM_MR_11,DRAM_CS_ALL,0x05);//set 48ohm for dq and ck odt
					dmc_mrw(DRAM_MR_14,DRAM_CS_ALL,0x12);//set dq vref
					reg_bit_set(DMC_CTL0_(0x10c),12,1,0x1);//Enable auto refresh
					//update dtmg12
					(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg11=0xb050b05;//update variable
					__raw_writel(DMC_CTL0_(0x01ac+train_info.ddr_freq_num*0x60),0x0b050b05);
				}else{
					reg_bit_set(DMC_CTL0_(0x10c),12,1,0x0);//disable auto refresh
					dmc_mrw(DRAM_MR_11,DRAM_CS_ALL,0x55);//set 48ohm for dq and ck odt
					dmc_mrw(DRAM_MR_22,DRAM_CS_ALL,0x35);//set 48ohm for dq and ck odt
					dmc_mrw(DRAM_MR_14,DRAM_CS_ALL,0x12);//set DQ VREF
					reg_bit_set(DMC_CTL0_(0x10c),12,1,0x1);//Enable auto refresh

					(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg11=0xb550b55;//update variable
					(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12=0x16350e5d;//update variable
					__raw_writel(DMC_CTL0_(0x01ac+train_info.ddr_freq_num*0x60),0x0b550b55);
					__raw_writel(DMC_CTL0_(0x01b0+train_info.ddr_freq_num*0x60),0x16350e5d);
				}
				__raw_writel(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),0x23465066);//restore io mode
			}
		}
}
u32 dsk_train_data[24]={0x0};
const u32 dsk_train_address[]={0x310016E0,0x310016E4,0x310016F0,0x31001720,0x31001724,0x31001730,0x31001760,0x31001764,0x31001770,0x310017A0,0x310017A4,0x310017B0,0x310017C0,0x310017C4,0x310017D0,0x310017D4,0x310017D8,0x310017E4,0x310017E8,0x310017EC,0x310017F8,0x310017FC,0x31001800,0x3100180C};
void Backup_Restore(u32 mode)
{	u32 i=0;
	if(mode==0x1)//backup
	{
		for(i=0;i<24;i++)
			dsk_train_data[i]=__raw_readl(dsk_train_address[i]);
	}else if(mode==0x2)//restore
	{
		for(i=0;i<24;i++)
			__raw_writel(dsk_train_address[i],dsk_train_data[i]);
	}
}
void dmc_phy_train_lp4()
{
    //u32 num=0;
    u32 chn_num=0;
    u32 eye_retry=0;
    u32 phy_io_ds_dqs_rpull=0;

    //get rf_phy_io_ds_dqs_rpull
    //phy_io_ds_dqs_rpull=reg_bit_get(DMC_PHY0_(0xf4+train_info.ddr_freq_num*0xc0),20,1);
    dmc_phy_train_lp4_ca_pattern();
    for(chn_num=0;chn_num<2;chn_num++)
    {
        dmc_phy_train_info_pre_set(chn_num,DRAM_CS_0);
        /**********CA Training CS0 *************/
        dmc_phy_ca_vref_training_prepare();//close delay line update and Update IO MODE for loW freq para
        dmc_phy_train_lp4_caeye(1);//Training VREF
    }



    for(chn_num=0;chn_num<2;chn_num++)
    {
        dmc_phy_train_info_pre_set(chn_num,DRAM_CS_0);
        reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<train_info.train_chn_num));//drf_dsoft_chn_sel

#if TEST_DEBUG_LOG_LEVEL>2
        dmc_print_str("New CAEYE Vref Value:");
        print_Hex((train_info.vrefca_val_chn0+train_info.vrefca_val_chn1)/2);
        dmc_print_str("\r\n");
#endif

        dmc_mrw(DRAM_MR_12, DRAM_CS_ALL, (train_info.vrefca_val_chn0+train_info.vrefca_val_chn1)/2);
        //Write Back variable and fsp register
        (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg14 &= ~(0xff<<0);
        (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg14 |= (train_info.vrefca_val_chn0+train_info.vrefca_val_chn1)/2;
        __raw_writel(DMC_CTL0_(0x01b8+train_info.ddr_freq_num*0x60), (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg14);

        dmc_phy_ca_vref_training_restore(1);//Open delay line update
        dmc_phy_train_lp4_cadsk(&eye_retry);//Adjust ca delay and run dsk training(Adjust the phase between each bit)
        //if(eye_retry)
        {
            dmc_phy_train_lp4_caeye(2);//Base in caeye(1) vref and dek training result to repeat ca eye training
            //	eye_retry=0;
        }
        dmc_phy_ca_vref_training_restore(2);//restore mr register ///
    }
    reg_bit_set(DMC_PHY0_(0x0060+train_info.ddr_freq_num*0xc0),4,4,0x0);//enable phy update
    dmc_phy_train_lp4_rd_dq_pattern();/*Set rd dq training pattern*/
    for(chn_num=0;chn_num<2;chn_num++)
    {
        dmc_phy_train_info_pre_set(chn_num,DRAM_CS_0);
        //dmc_phy_ca_vref_training_restore(2);//restore mr register ///
        /**********RD Training CS0*************/

        dmc_phy_train_lp4_rdeye(1);//training rd vref and delay cells
    }
    (phy_tmg+train_info.ddr_freq_num)->cfg_io_ds_cfg &= ~(0xFF<<24);
    (phy_tmg+train_info.ddr_freq_num)->cfg_io_ds_cfg |= (((train_info.vrefdq_rd_val_chn0+train_info.vrefdq_rd_val_chn1)/2)<<24);

#if TEST_DEBUG_LOG_LEVEL>2
    dmc_print_str("New RDEYE Vref Value:");
    print_Hex((train_info.vrefdq_rd_val_chn0+train_info.vrefdq_rd_val_chn1)/2);
    dmc_print_str("\r\n");
#endif

    reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),24,8,(train_info.vrefdq_rd_val_chn0+train_info.vrefdq_rd_val_chn1)/2);
    for(chn_num=0;chn_num<2;chn_num++)
    {
        dmc_phy_train_info_pre_set(chn_num,DRAM_CS_0);
        dmc_phy_train_lp4_rddsk(&eye_retry);
        //if(eye_retry)//Re-execute rdeye training if rddsk training enable
        {
            dmc_phy_train_lp4_rdeye(2);//Based on before training result for vrefi Re-execute rdeye training .Regerate rddelay
            //	eye_retry=0;
        }
    }
    /**********WR Training CS0 and CS1*************/

    dmc_phy_train_lp4_wr_dq_pattern(chn_num);/*Set wr dq training pattern*/
    for(chn_num=0;chn_num<2;chn_num++)
    {
        dmc_phy_train_info_pre_set(chn_num,DRAM_CS_0);
        dmc_phy_train_lp4_adjust_cycle();//Adjust suitable cycle 2cycle use default vref prevent vref training error
        dmc_phy_train_info_pre_set(chn_num,DRAM_CS_0);
        dmc_phy_train_lp4_wreye_cs0(1);//Get final vref and temporary delay
    }
    for(chn_num=0;chn_num<2;chn_num++)
    {
        dmc_phy_train_info_pre_set(chn_num,DRAM_CS_0);
        dmc_phy_train_lp4_vrefdq_set((train_info.vrefdq_wr_val_chn0+train_info.vrefdq_wr_val_chn1)/2);;//mr need two times

#if TEST_DEBUG_LOG_LEVEL>2
        dmc_print_str("New WREYE Vref Value:");
        print_Hex((train_info.vrefdq_wr_val_chn0+train_info.vrefdq_wr_val_chn1)/2);
        dmc_print_str("\r\n");
#endif
        //update global variable for wr vref
        (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12 &= ~(0xFF<<0);
        (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12 |= (((train_info.vrefdq_wr_val_chn0+train_info.vrefdq_wr_val_chn1)/2)<<0);

        //This field indicated the MRW value used to change MRW value during DFS
        //MR14
        __raw_writel(DMC_CTL0_(0x01b0+train_info.ddr_freq_num*0x60), (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12);

        dmc_phy_train_lp4_wrdsk(&eye_retry,2);//According VREF training result repeat wrdsk
        //if(eye_retry)
        {
            dmc_phy_train_lp4_wreye_cs0(2);//Based on before training result for vref Re-execute wreye training .Regerate wrdelay
            //	eye_retry=0;
        }
        if(dram_info.cs_num== DRAM_CS_ALL)
        {
            dmc_phy_train_info_pre_set(chn_num,DRAM_CS_1);
            dmc_phy_train_lp4_wrdsk(&eye_retry,2);
            dmc_phy_train_lp4_wreye_cs1();
        }
    }
    reg_bit_set(DMC_PHY0_(0x0060+train_info.ddr_freq_num*0xc0),4,4,0xf);//disable phy update
}
u32 dram_bist_specific_space_init()
{
	u32 bist_addr[3]={0x0,0x10000000,0x20000000};//bist[2] addr not use Only open bist0 and bist1
	u32 bist_result;
	int ret0,ret1;
	bist_addr[1]=(dram_info.cs0_size+dram_info.cs1_size-0x1000);//Use 4kb in last ddr space
	ret0=dram_bist_specific_space(bist_addr[0],0x1000);//First 512BYTE
	ret1=dram_bist_specific_space(bist_addr[1],bist_addr[1]+0x1000-1);//Last  512BYTE
	bist_result = ((ret0?1:0)<<0) | (((ret1?1:0)<<1));
	return bist_result;
}


/*******************************************************************************
fsp :Before dfs set 8 MR register through DTMG11~DTMG14
After  dfs set 4 MR register through DTMG15~DTMG16
 *Each time the end of the frequency conversion will automatically reverse the wr
 *
 *             set wr=1    1 dfs			 2 dfs       set wr=0
 *wr=0,op=0--->wr=1,op=0--->wr=0,op=1--->wr=1,op=0--->wr=0,op=0---->Training

 *Every Freq training should repeat run fsp seq (two dfs)
 *Because op must set 0 berfor current Freq Training
 *Eg1:start -> F5->F5->training(wr=0,op=0)    ->F6(wr=1,op=1),This status not run training seq

 *Eg1:start -> F5->F5->training(wr=0,op=0)    ->Before seq (wr=0,op=0),This status can run training seq
 ********************************************************************************/
void dmc_phy_train(u32 ddr_clk)
{
    int rd_en_val=0,rd_en_val_min=0,rd_en_val_max=0;
    u32 bist_result;
    /****train info init*****/
    train_info.ddr_clk=ddr_clk;
#if TEST_DEBUG_LOG_LEVEL>0
    dmc_print_str("\r\ntraining fn:");
    print_Hex(train_info.ddr_clk);
    dmc_print_str("MHz");
#endif

    dmc_freq_sel_search(ddr_clk, &train_info.ddr_freq_num);
    //trainning pre set
    dmc_phy_train_pre_set();
    //set cke high
    dmc_train_cke_pre_set(ddr_clk);
    //First:set wr=1 in first fsp dfs
    dmc_fsp_dfs_prepare(train_info.ddr_freq_num);
    //dfs to target frequency
    sw_dfs_go(train_info.ddr_freq_num);
    //Second:set wr=0 in second fsp dfs
    dmc_fsp_dfs_prepare(train_info.ddr_freq_num);
    //train enable
    reg_bit_set(DMC_CTL0_(0x0154), 0, 1,0x1);//rf_train_enable
    //dmc phy train clear
    dmc_phy_train_all_clear();
    //pre config
    dmc_phy_train_delay_convert();//delay convert

    //set write odt
    //dmc_set_write_odt(train_info.ddr_freq_num);//read dtmg11_xx and set to MR11


    if(dram_info.dram_type==DRAM_LP3){
        //lp3 train
        dmc_phy_train_lp3();
    }else{
        //set CA TRAINING flag
        dmc_phy_train_lp4_flag_sel();
        //lp4/lp4x train
        dmc_phy_train_lp4();
    }
    dmc_phy_train_cycle_convert();
    if(train_info.ddr_clk == 1536)
    {
        __raw_writel(0x310015A4,__raw_readl(0x310014e4));
        __raw_writel(0x310015A8,__raw_readl(0x310014e8));
    }
    if(train_info.ddr_clk == 1333)
    {
        __raw_writel(0x310014e4,__raw_readl(0x31001424));
        __raw_writel(0x310014e8,__raw_readl(0x31001428));
    }
    if(dram_info.dram_type==DRAM_LP3)
    {
	if((train_info.ddr_clk == 622) || (train_info.ddr_clk == 768))
	{
	        __raw_writel(DMC_PHY0_(0x0064+(train_info.ddr_freq_num+1)*0xc0),__raw_readl(DMC_PHY0_(0x0064+train_info.ddr_freq_num*0xc0)));
	        __raw_writel(DMC_PHY0_(0x0068+(train_info.ddr_freq_num+1)*0xc0),__raw_readl(DMC_PHY0_(0x0068+train_info.ddr_freq_num*0xc0)));
	        __raw_writel(DMC_PHY0_(0x006c+(train_info.ddr_freq_num+1)*0xc0),__raw_readl(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0)));
	        __raw_writel(DMC_PHY0_(0x008c+(train_info.ddr_freq_num+1)*0xc0),__raw_readl(DMC_PHY0_(0x008c+train_info.ddr_freq_num*0xc0)));
	        __raw_writel(DMC_PHY0_(0x00ac+(train_info.ddr_freq_num+1)*0xc0),__raw_readl(DMC_PHY0_(0x00ac+train_info.ddr_freq_num*0xc0)));
	        __raw_writel(DMC_PHY0_(0x00cc+(train_info.ddr_freq_num+1)*0xc0),__raw_readl(DMC_PHY0_(0x00cc+train_info.ddr_freq_num*0xc0)));

	}
    }


    //end train
    reg_bit_set(DMC_CTL0_(0x0104),31, 1,0x1);//dsoft_cmd_allcs
    reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);//disable auto ref
    //Set WR =1 use for next fsp dfs
    dmc_mrw(DRAM_MR_13,DRAM_CS_ALL,0x40);//WR=1
    reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//disable auto ref
    reg_bit_set(DMC_CTL0_(0x0154), 0, 1,0x0);//Disable rf_train_enable
#if TEST_DEBUG_LOG_LEVEL>0
		dmc_print_str("  ok!");
#endif
	rd_en_test_flag = 1;
	for(rd_en_val = 0;rd_en_val<16;rd_en_val++)
	{
		reg_bit_set(DMC_PHY0_(0x0058+train_info.ddr_freq_num*0xc0),0,16,1<<rd_en_val);
		bist_result=dram_bist_specific_space_init();
		if(!bist_result)
		{
#if TEST_DEBUG_LOG_LEVEL>0
			print_Hex(1<<rd_en_val);
			dmc_print_str(" :pass\r\n");
#endif
			rd_en_val_min = rd_en_val;
			break;
		}
	}
	rd_en_test_flag = 0;
#if TEST_DEBUG_LOG_LEVEL>0
	print_Hex(1<<((ddr_clk <= 933)?(rd_en_val_min+1):(rd_en_val_min+2)));
	dmc_print_str(" :target\r\n");
#endif

    reg_bit_set(DMC_PHY0_(0x0058+train_info.ddr_freq_num*0xc0),0,16,1<<((ddr_clk <= 933)?(rd_en_val_min+1):(rd_en_val_min+2)));
#if TEST_DEBUG_LOG_LEVEL>0
    dmc_print_str("  ok!");
#endif
}


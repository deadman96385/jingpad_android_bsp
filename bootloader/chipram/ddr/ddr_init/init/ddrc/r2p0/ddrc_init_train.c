#include "ddrc_init.h"

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
	u32 vrefdq_rd_val;
	u32 vrefdq_wr_val;
}TRAIN_CFG_INFO_T;
TRAIN_CFG_INFO_T train_info;
extern DRAM_INFO_T dram_info;
extern DDRC_DMC_DTMG_T *dmc_dtmg;
extern DDRC_PHY_TMG_T *phy_tmg;

#ifdef DDR_SCAN_ENABLE
#define dmc_print_str(x) NULL
#define print_Hex(x) NULL
#define print_Dec(x) NULL
extern u32 pass_win_max_scan[];
extern u32 scan_target_clk;
#endif

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
                            0x31001760, 0x31001764, 0x31001770,
                            0x310017a0, 0x310017a4, 0x310017b0,
                            0x310017c0, 0x310017c4, 0x310017d0,
                            0x310017d4, 0x310017d8, 0x310017e4,
                            0x310017e8, 0x310017ec, 0x310017f8,
                            0x310017fc, 0x31001800, 0x3100180c};
u32 lp3_train_data_pattern[8]={0x0,0xffffffff,0x0,0xffffffff,
                0x55555555,0xaaaaaaaa,0x55555555,0xaaaaaaaa};


void dmc_phy_train_pre_set()
{
	int i=0;
	reg_bit_set(DMC_CTL0_(0x012c), 0, 4,0xf);
	//reg_bit_set(DMC_CTL0_(0x012c), 0, 1,0x01);//drf_dfs_en
	//reg_bit_set(DMC_CTL0_(0x012c), 1, 1,0x01);//drf_dfs_dll_rst_en
	//reg_bit_set(DMC_CTL0_(0x012c), 2, 1,0x01);//drf_dfs_cmd_mrw_en
	//reg_bit_set(DMC_CTL0_(0x012c), 3, 1,0x01);//drf_drf_dfs_pll_lock_en
	//
	//reg_bit_set(DMC_CTL0_(0x0100),11, 1,((dram_info.cs_num==DRAM_CS_ALL)?0x1:0x0));//rf_data_ie_mode
	reg_bit_set(DMC_CTL0_(0x0100),12, 1,((dram_info.cs_num==DRAM_CS_ALL)?0x1:0x0));//rf_data_oe_mode
	wait_100ns(1);
	//disable
	reg_bit_set(DMC_CTL0_(0x0114),24, 1,0x0);//drf_auto_mr4_en
	reg_bit_set(DMC_CTL0_(0x0118),24, 1,0x0);//drf_auto_zqc_en
	reg_bit_set(DMC_CTL0_(0x0144),16, 2,0x0);//rf_period_cpst_en
	//reg_bit_set(DMC_CTL0_(0x0144),17, 1,0x0);//rf_wbuf_merge_en
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//drf_auto_ref_enå
	reg_bit_set(DMC_CTL0_(0x0104),31, 1,0x0);//dsoft_cmd_allcs
	//LPDDR3 Train data pattern
	if(dram_info.dram_type == DRAM_LP3)
	{
		for(i=0;i<8;i++)
			__raw_writel(DMC_CTL0_(0x0060+i*4),lp3_train_data_pattern[i]);
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
	tr_val &= ~(0xFFFFFFF);
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
			wait_us(1);
		}
	}
	if((__raw_readl(DMC_CTL0_(0x0158))>>(tr_type*4+2))&0x1)
	{
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("training fail!!   ");
#endif
		if(train_num==1)
		{
			if(dram_info.dram_type != DRAM_LP3)
			{
				while(1);
			}else
			{
				return 1;
			}
		}else
		{
			//if(dram_info.dram_type != DRAM_LP3)
			//{
			//	//train clear
			//	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
			//	wait_100ns(1);
			//	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
			//}
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
	u32 train_num=0;
	for(train_num=0;train_num<7;train_num++)
	{
		reg_bit_set(DMC_CTL0_(0x0158),train_num*4, 1,0x1);//rf_train_wreyw_en
	}
	//reg_bit_set(DMC_CTL0_(0x0158),24, 1,0x1);//rf_train_wreyw_en
	//reg_bit_set(DMC_CTL0_(0x0158),20, 1,0x1);//rf_train_wrdsk_en
	//reg_bit_set(DMC_CTL0_(0x0158),16, 1,0x1);//rf_train_rdeye_en
	//reg_bit_set(DMC_CTL0_(0x0158),12, 1,0x1);//rf_train_rddsk_en
	//reg_bit_set(DMC_CTL0_(0x0158), 8, 1,0x1);//rf_train_gate_en
	//reg_bit_set(DMC_CTL0_(0x0158), 4, 1,0x1);//rf_train_caeye_en
	//reg_bit_set(DMC_CTL0_(0x0158), 0, 1,0x1);//rf_train_cadsk_en
	wait_us(1);
	reg_bit_set(DMC_CTL0_(0x0154), 2, 1,0x1);//rf_train_clear
	wait_us(1);
	reg_bit_set(DMC_CTL0_(0x0154), 2, 1,0x0);//rf_train_clear
	wait_us(1);
	for(train_num=0;train_num<7;train_num++)
	{
		reg_bit_set(DMC_CTL0_(0x0158),train_num*4, 1,0x0);//rf_train_wreyw_en
	}
	//reg_bit_set(DMC_CTL0_(0x0158),24, 1,0x0);//rf_train_wreyw_en
	//reg_bit_set(DMC_CTL0_(0x0158),20, 1,0x0);//rf_train_wrdsk_en
	//reg_bit_set(DMC_CTL0_(0x0158),16, 1,0x0);//rf_train_rdeye_en
	//reg_bit_set(DMC_CTL0_(0x0158),12, 1,0x0);//rf_train_rddsk_en
	//reg_bit_set(DMC_CTL0_(0x0158), 8, 1,0x0);//rf_train_gate_en
	//reg_bit_set(DMC_CTL0_(0x0158), 4, 1,0x0);//rf_train_caeye_en
	//reg_bit_set(DMC_CTL0_(0x0158), 0, 1,0x0);//rf_train_cadsk_en
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
	u32 dll_cnt,dll_clk_sel,dll_clk_mode;
	u32 use_1x_clk;
	u32 raw_2cycle_sel,raw_cycle_sel,raw_dl_sel;
	u32 dl_addr_offset=0;
	dll_cnt=__raw_readl(DMC_PHY0_(0x0644))&0x7f;//rfdll_cnt_ac0
	dll_clk_sel=(__raw_readl(DMC_PHY0_(0x0640))>>14)&0x1;//rf_dll_clk_sel_ac0
	dll_clk_mode=((__raw_readl(DMC_PHY0_(0x0060+train_info.ddr_freq_num*0xc0)))>>3)&0x1;//drf_dll_clk_mode
	if(dll_clk_sel && dll_clk_mode){
		dll_cnt =(dll_cnt/2);
		use_1x_clk=0x1;
	}else{
		use_1x_clk=0x0;
	}
	if((!use_1x_clk)&&(dll_clk_mode)){
		dll_cnt = (dll_cnt*2);
	}
	/*
	*ac0(0x64) ac1(0x68)
	*ds0(0x6c) dqs_in_pos(0x70) dqs_in_neg(0x74) dqs_gate(0x78)
	*ds1(0x8c) dqs_in_pos(0x90) dqs_in_neg(0x94) dqs_gate(0x98)
	*ds2(0xac) dqs_in_pos(0xb0) dqs_in_neg(0xb4) dqs_gate(0xb8)
	*ds3(0xcc) dqs_in_pos(0xd0) dqs_in_neg(0xd4) dqs_gate(0xd8)
	*/
	for(dll_num=0;dll_num<18;dll_num++)
	{
		if(dll_num<2){
		dl_addr_offset=train_info.ddr_freq_num*0xc0+dll_ac_ds_addr[dll_num];
		}else{
		dl_addr_offset=train_info.ddr_freq_num*0xc0+dll_ac_ds_addr[((dll_num-2)/4)+2]+((dll_num-2)%4)*4;
		}
		raw_2cycle_sel=((__raw_readl(DMC_PHY0_(dl_addr_offset))>>15)&0x1);
		raw_cycle_sel=((__raw_readl(DMC_PHY0_(dl_addr_offset))>>7)&0x1);
		raw_dl_sel=__raw_readl(DMC_PHY0_(dl_addr_offset))&0x7f;
		if(raw_2cycle_sel)
		{
			raw_dl_sel += 0x40;
			reg_bit_set(DMC_PHY0_(dl_addr_offset),15, 1,0x0);
		}
		if(raw_cycle_sel)
		{
			raw_dl_sel += 0x20;
			reg_bit_set(DMC_PHY0_(dl_addr_offset), 7, 1,0x0);
		}
		reg_bit_set(DMC_PHY0_(dl_addr_offset),0,7,raw_dl_sel);
	}
	//
	if(dram_info.dram_type != DRAM_LP3)
	{
		reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x006c),7,1,0x1);//rf_clkwr_raw_cycle_0_sel
		reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x008c),7,1,0x1);//rf_clkwr_raw_cycle_1_sel
		reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x00ac),7,1,0x1);//rf_clkwr_raw_cycle_2_sel
		reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x00cc),7,1,0x1);//rf_clkwr_raw_cycle_3_sel
	}
	reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x007c),0,7,0x0);//rf_clkwr_diff_dl_0_sel
	reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x009c),0,7,0x0);//rf_clkwr_diff_dl_1_sel
	reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x00bc),0,7,0x0);//rf_clkwr_diff_dl_2_sel
	reg_bit_set(DMC_PHY0_(train_info.ddr_freq_num*0xc0+0x00dc),0,7,0x0);//rf_clkwr_diff_dl_3_sel
	dmc_phy_soft_update();
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//drf_auto_ref_en
}

//convert delay value to cycle
void dmc_phy_train_cycle_convert()
{
	u32 raw_dl_val;
	u32 dll_num;
	u32 raw_one_cycle;
	u32 raw_two_cycle;
	u32 reg_ac_ds_addr;
	//disable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);
	wait_100ns(2);
	//dll_cnt=(__raw_readl(DMC_PHY0_(0x0644))&0x7f);
	for(dll_num=0;dll_num<6;dll_num++)
	{
		reg_ac_ds_addr = DMC_PHY0_(train_info.ddr_freq_num*0xc0+dll_ac_ds_addr[dll_num]);
		raw_dl_val=(__raw_readl(reg_ac_ds_addr)&0x7f);
		raw_one_cycle=(__raw_readl(reg_ac_ds_addr)>>7)&0x1;//1cycle flag
		raw_two_cycle=(__raw_readl(reg_ac_ds_addr)>>15)&0x1;

		if(raw_dl_val>=0x40)//>=2cycles
		{
			if( raw_two_cycle==1 )
			{
				if( raw_one_cycle==0 )
				{
					raw_dl_val -= 0x20;
					reg_bit_set(reg_ac_ds_addr,0,7,raw_dl_val);
					reg_bit_set(reg_ac_ds_addr,7,1,0x1);
				}
			}
			else
			{
				raw_dl_val -= 0x40;
				reg_bit_set(reg_ac_ds_addr,0,7,raw_dl_val);
				reg_bit_set(reg_ac_ds_addr,15,1,0x1);
			}
		}else if(raw_dl_val >= 0x20 && ((raw_two_cycle==0x0)||(raw_one_cycle==0x0)))
		{
			raw_dl_val -= 0x20;
			reg_bit_set(reg_ac_ds_addr,0,7,raw_dl_val);
			if(raw_one_cycle==0x1)
			{
				reg_bit_set(reg_ac_ds_addr,7,1,0x0);
				reg_bit_set(reg_ac_ds_addr,15,1,0x1);
			}else
			{
				reg_bit_set(reg_ac_ds_addr,7,1,0x1);
			}

		}
		//reg_bit_set(DMC_PHY0_(0x0640+0x40*dll_num),11,1,0x1);
		//wait_100ns(1);
		//reg_bit_set(DMC_PHY0_(0x0640+0x40*dll_num),11,1,0x0);
	}
	dmc_phy_soft_update();
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//drf_auto_ref_en
}

void dmc_phy_train_delay_convert()
{
	//
	reg_bit_set(DMC_PHY0_(0x0040+train_info.ddr_freq_num*0xc0),28,1,(dram_info.cs_num==DRAM_CS_ALL)?0x1:0x0);//drf_multirank_sel
	//
	reg_bit_set(DMC_PHY0_(0x0004),10, 1,0x0);//rf_phy_sample_auto_rst_en
	reg_bit_set(DMC_PHY0_(0x010c),12, 1,0x0);//drf_auto_ref_en
	//convert dll to delay value
	dmc_phy_train_dll_convert();
	//update
	dmc_phy_soft_update();
	//enable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1, 0x1);
}

void dmc_phy_train_info_pre_set(u32 train_chn,u32 cs_num)
{
	train_info.train_cs_num=cs_num;
	train_info.train_chn_num=train_chn;
	if(dram_info.dram_type == DRAM_LP3)
	{
		train_info.train_byte_en=0xf;
		train_info.train_addr_31_0=0x0;
		train_info.train_addr_33_32=0x0;
	}else
	{
		if(train_chn==DRAM_CHN_0)
		{
			train_info.train_byte_en=0x3;
			if(cs_num==DRAM_CS_0)
			{
				train_info.train_addr_31_0=0x0;
				train_info.train_addr_33_32=0x0;
			}else
			{
				train_info.train_addr_31_0=(u32)(((dram_info.cs0_size+dram_info.cs1_size)%0x100000000));
				train_info.train_addr_33_32=(u32)((dram_info.cs0_size+dram_info.cs1_size)/0x100000000);
				if((train_info.train_addr_31_0==0x0)&&(train_info.train_addr_33_32>0))
				{
					train_info.train_addr_31_0=0x100000000-2*dram_info.intlv_size;
					train_info.train_addr_33_32=train_info.train_addr_33_32-1;
				}
				else
					train_info.train_addr_31_0=train_info.train_addr_31_0 - 2*dram_info.intlv_size;
			}
		}else
		{
			train_info.train_byte_en=0xc;
			if(cs_num==DRAM_CS_0)
			{
				train_info.train_addr_31_0=dram_info.intlv_size;
				train_info.train_addr_33_32=0x0;
			}else
			{
				train_info.train_addr_31_0=(u32)(((dram_info.cs0_size+dram_info.cs1_size)%0x100000000));
				train_info.train_addr_33_32=(u32)((dram_info.cs0_size+dram_info.cs1_size)/0x100000000);
				if((train_info.train_addr_31_0==0x0)&&(train_info.train_addr_33_32>0))
					{
					train_info.train_addr_31_0=0x100000000-dram_info.intlv_size;
					train_info.train_addr_33_32=train_info.train_addr_33_32-1;
				}
				else
					train_info.train_addr_31_0=train_info.train_addr_31_0-dram_info.intlv_size;

			}
		}
	}
	//select train cs
	reg_bit_set(DMC_CTL0_(0x0158),31, 1,train_info.train_cs_num);//rf_train_cs_sel
	//select training channel0
	reg_bit_set(DMC_CTL0_(0x0154),3,1,train_info.train_chn_num);//rf_train_ch
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

void dmc_phy_train_lp3_flag_sel()
{
	u32 dll_cnt_temp;
	u32 fn=train_info.ddr_freq_num;
	dll_cnt_temp=__raw_readl(DMC_PHY0_(0x644))&0x3f;
	if((dll_cnt_temp > 0x30) && ((train_info.ddr_clk == DDR_CLK_512M)||(train_info.ddr_clk == DDR_CLK_622M)))
	{
		//(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_CADSK_INDEX*4));
		(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_CAEYE_INDEX*4));
		//(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_WRDSK_INDEX*4));
		(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_WREYE_INDEX*4));
	}
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
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
		wait_100ns(1);
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
	u32 caeye_train_val,caeye_pass_win;
	u32 dll_cnt;
	u32 rddsk_start =0;
    int ddr_freq;
    //set vref
    for(ddr_freq=0; ddr_freq<7 ; ddr_freq++)
        reg_bit_set(DMC_PHY0_(0x00f4+ddr_freq*0xc0),24,8,0x50);
	//train pre set
	dmc_phy_train_info_pre_set(DRAM_CHN_0,DRAM_CS_0);
	//disable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);//drf_auto_ref_en
	reg_bit_set(DMC_CTL0_(0x0104),28, 1,0x0);//
	reg_bit_set(DMC_CTL0_(0x0158),31, 1,0x0);//select train cs0
	dll_cnt=__raw_readl(DMC_PHY0_(0x0644))&0x7f;
	/****cadsk training****/
	if(is_dmc_phy_train_en(TRAIN_CADSK_INDEX) && (cadsk_done==0) && ((dll_cnt<48) || (train_info.ddr_clk>DDR_CLK_768M)))
	{
		reg_bit_set(DMC_CTL0_(0x0158), 0, 1,0x1);//train_cadsk_en
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
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
		dmc_phy_train_lp3_polling_retry(TRAIN_CAEYE_INDEX, 0);
		caeye_train_val=(__raw_readl(DMC_CTL0_(0x0168))>>8)&0xff;
		caeye_pass_win=__raw_readl(DMC_CTL0_(0x0168))&0xff;
		reg_bit_set(DMC_PHY0_(0x0064)+train_info.ddr_freq_num*0xc0,0,7,(caeye_train_val-(caeye_pass_win>>1)));
		reg_bit_set(DMC_PHY0_(0x0068)+train_info.ddr_freq_num*0xc0,0,7,(caeye_train_val-(caeye_pass_win>>1)));
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
		reg_bit_set(DMC_CTL0_(0x0158), 4, 1,0x0);//train_caeye_en
		dmc_phy_soft_update();
	}
#ifdef DDR_SCAN_ENABLE
	pass_win_max_scan[2]= caeye_pass_win;
#endif
	/****data slice training****/
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//drf_auto_ref_en
	if(is_dmc_phy_train_en(TRAIN_WRDSK_INDEX) && wrdsk_done==0 && ((dll_cnt<48) || (train_info.ddr_clk>DDR_CLK_768M)))
	{
		reg_bit_set(DMC_CTL0_(0x0158),20, 1,0x1);//train_wrdsk_en

		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start

		dmc_phy_train_lp3_polling_retry(TRAIN_WRDSK_INDEX, 10);
		wrdsk_done = 1;


		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
		wait_100ns(1);

		dmc_phy_train_optimize_wrdsk_result();

		reg_bit_set(DMC_CTL0_(0x0158),20, 1,0x0);//train_wrdsk_en

	}


	if(is_dmc_phy_train_en(TRAIN_WREYE_INDEX))
	{
		reg_bit_set(DMC_CTL0_(0x0158),24, 1,0x1);//train_wreye_en
	}

	if(is_dmc_phy_train_en(TRAIN_RDEYE_INDEX))
	{
		reg_bit_set(DMC_CTL0_(0x0158),16, 1,0x1);//train_rdeye_en
	}
	if(is_dmc_phy_train_en(TRAIN_RDDSK_INDEX) && (rddsk_done==0) )
	{
		reg_bit_set(DMC_CTL0_(0x0158),12, 1,0x1);//train_rddsk_en
		rddsk_start = 1;
	}
#ifdef GATE_TRAIN_EN
	if(is_dmc_phy_train_en(TRAIN_GATE_INDEX))
	{
		reg_bit_set(DMC_CTL0_(0x0158), 8, 1,0x1);//train_gate_en
	}
#endif
	wait_100ns(1);
	if((phy_tmg+train_info.ddr_freq_num)->train_flag !=0)
	{
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
	}
#ifdef GATE_TRAIN_EN
	if(is_dmc_phy_train_en(TRAIN_GATE_INDEX))
	{
		dmc_phy_train_lp3_polling_retry(TRAIN_GATE_INDEX, 0);
	}
#endif
	if(is_dmc_phy_train_en(TRAIN_RDDSK_INDEX) && rddsk_start==1)
	{
		dmc_phy_train_lp3_polling_retry(TRAIN_RDDSK_INDEX, 0);
		rddsk_done = 1;
	}
	if(is_dmc_phy_train_en(TRAIN_RDEYE_INDEX))
	{
		dmc_phy_train_lp3_polling_retry(TRAIN_RDEYE_INDEX, 0);
	}
#ifdef DDR_SCAN_ENABLE
	pass_win_max_scan[0]= __raw_readl(DMC_CTL0_(0x0170));
#endif

	if(is_dmc_phy_train_en(TRAIN_WREYE_INDEX))
	{
		dmc_phy_train_lp3_polling_retry(TRAIN_WREYE_INDEX, 0);

		//use current fn training result for the next fn, to fix 87# rdeye training fail
		if( train_info.ddr_freq_num < 7 )
		{
			__raw_writel(DMC_PHY0_((train_info.ddr_freq_num+1)*0xc0+dll_ac_ds_addr[2]), __raw_readl(DMC_PHY0_(train_info.ddr_freq_num*0xc0+dll_ac_ds_addr[2])));
			__raw_writel(DMC_PHY0_((train_info.ddr_freq_num+1)*0xc0+dll_ac_ds_addr[3]), __raw_readl(DMC_PHY0_(train_info.ddr_freq_num*0xc0+dll_ac_ds_addr[3])));
			__raw_writel(DMC_PHY0_((train_info.ddr_freq_num+1)*0xc0+dll_ac_ds_addr[4]), __raw_readl(DMC_PHY0_(train_info.ddr_freq_num*0xc0+dll_ac_ds_addr[4])));
			__raw_writel(DMC_PHY0_((train_info.ddr_freq_num+1)*0xc0+dll_ac_ds_addr[5]), __raw_readl(DMC_PHY0_(train_info.ddr_freq_num*0xc0+dll_ac_ds_addr[5])));
		}
	}
#ifdef DDR_SCAN_ENABLE
	pass_win_max_scan[1]= __raw_readl(DMC_CTL0_(0x0170));
#endif


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
	u32 dll_clk_mode,dll_half_mode,dll_cnt_temp;
	dll_clk_mode=(__raw_readl(DMC_PHY0_(0x60)+0xc0*fn)>>3)&0x1;
	dll_half_mode=(__raw_readl(DMC_PHY0_(0x60)+0xc0*fn)>>2)&0x1;
	dll_cnt_temp=__raw_readl(DMC_PHY0_(0x644))&0x3f;
	if((train_info.ddr_clk==DDR_CLK_512M)||(train_info.ddr_clk==DDR_CLK_622M)||(train_info.ddr_clk==DDR_CLK_768M))
	{
		if((dll_clk_mode==0)&&(dll_half_mode==1)&&(dll_cnt_temp>0x30))
		{
			(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_CADSK_INDEX*4));
			(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_WRDSK_INDEX*4));
			(phy_tmg+fn)->train_flag &= ~(0x1<<(TRAIN_CAEYE_INDEX*4));
		}
	}
	train_info.odt_status=0x0;
	if( 0 !=(((phy_tmg+train_info.ddr_freq_num)->cfg_io_ds_cfg>>12)&0x7))
	{
		train_info.odt_status=0x1;
	}
	train_info.vrefca_val=0;
	train_info.vrefdq_rd_val=0;
	train_info.vrefdq_wr_val=0;
}



void dmc_phy_train_lp4_caeye(u32 train_count)
{
	u32 vrefca_val=0,vrefca_step=2,vrefca_min,vrefca_max;
	u32 pass_win_max=0,pass_win_max1=0,pass_win_max2=0,pass_win_temp;
	u32 caeye_value=0,caeye_value_1=0,caeye_value_2=0,caeye_value_temp;
	u32 caeye_vref_first1=0,caeye_vref_last1=0;
	u32 caeye_vref_first2=0,caeye_vref_last2=0;
	if(0 == is_dmc_phy_train_en(TRAIN_CAEYE_INDEX))
	{
		return;
	}

	if( (train_info.train_chn_num==0) && (train_count==1))
	{
		if( ch0_cavref_done==1 )
			return;
		ch0_cavref_done==1;
	}

	if( (train_info.train_chn_num==1) && (train_count==1))
	{
		if( ch1_cavref_done==1 )
			return;
		ch1_cavref_done==1;
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
		vrefca_min=train_info.vrefca_val;
		vrefca_max=train_info.vrefca_val;
	}
	//train enable
	dmc_phy_train_en(TRAIN_CAEYE_INDEX);
	//
	for(vrefca_val=vrefca_min;vrefca_val<=vrefca_max;vrefca_val+=vrefca_step)
	{
		//train clear
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x010c),12,1,0x0);//rf_auto_ref_en
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0164), 8,7,vrefca_val);//rf_train_caeye_vref
		reg_bit_set(DMC_CTL0_(0x0164), 0,8,CAEYE_PASS_WIN_MIN);//rf_train_caeye_pass_window_min
		wait_100ns(1);
		//train start
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
		wait_100ns(1);
		if(train_count==1 )
			dmc_phy_train_polling_done(TRAIN_CAEYE_INDEX,2);
		else
			dmc_phy_train_polling_done(TRAIN_CAEYE_INDEX,1);
		pass_win_temp=(__raw_readl(DMC_CTL0_(0x0168))&0xff);
		caeye_value_temp=((__raw_readl(DMC_CTL0_(0x0168))>>8)&0xff);
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
#endif
		//set caeye value
		//reg_bit_set(DMC_PHY0_(dll_ac_ds_addr[train_info.train_chn_num]+train_info.ddr_freq_num*0xc0),0,7,(caeye_value_temp-(pass_win_temp>>1)));
		//dmc_phy_soft_update();
		if(train_count==1)
		{
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
			pass_win_max=pass_win_temp;
			caeye_value=caeye_value_temp;
		}
		//clear train start
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
	}
	if(train_count==1)
	{
		if(caeye_vref_last1<caeye_vref_first1)
		{
			caeye_vref_last1=caeye_vref_first1;
		}
		if(caeye_vref_first2 == 0)//avoid windows increase caeye_vref_first2=0
		{
			caeye_vref_first2=caeye_vref_first1;
		}
		if(caeye_vref_last2<caeye_vref_first2)
		{
			caeye_vref_last2=caeye_vref_first2;
		}
		pass_win_max=(pass_win_max1+pass_win_max2)/2;
		caeye_value=(caeye_value_1+caeye_value_2)/2;
		train_info.vrefca_val=(caeye_vref_first1+caeye_vref_last1)/4
								+(caeye_vref_first2+caeye_vref_last2)/4;
	}
#ifdef DDR_SCAN_ENABLE
	if(train_info.ddr_clk ==scan_target_clk)
		pass_win_max_scan[train_info.train_chn_num] |= (pass_win_max << 24);
#endif
	if(pass_win_max==0){
		dmc_print_str("\r\ncaeye training pass window is zero!!!");
		while(1);
	}
	//set caeye value
	reg_bit_set(DMC_PHY0_(dll_ac_ds_addr[train_info.train_chn_num]+train_info.ddr_freq_num*0xc0),0,7,(caeye_value-(pass_win_max>>1)));
	dmc_phy_soft_update();
	//set vrefca
	reg_bit_set(DMC_CTL0_(0x0100),20,4,(1<<train_info.train_chn_num));//drf_dsoft_chn_sel
	if(train_count==1)
	{
#if TEST_DEBUG_LOG_LEVEL>2
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
		dmc_mrw(DRAM_MR_12, DRAM_CS_ALL, train_info.vrefca_val);
		wait_100ns(5);
	}
	reg_bit_set(DMC_CTL0_(0x0100),20,4,0x3);//drf_dsoft_chn_sel
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x1);//drf_auto_ref_en
}

void dmc_phy_train_lp4_cadsk(u32* eye_retry)
{
	u32 val_tmp;
	u32 ac0_val=0,ac1_val=0;
	if(0 == is_dmc_phy_train_en(TRAIN_CADSK_INDEX) )
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
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x0);
	val_tmp=__raw_readl(DMC_PHY0_(0x0064+train_info.ddr_freq_num*0xc0));//rf_clkwr_raw_cycle_ac0_sel
	ac0_val=val_tmp;
	val_tmp |= 0x80;
	val_tmp = ((val_tmp&0x7f) >0x20)?(val_tmp- 0x20 ):(val_tmp & 0xffffff80);
	__raw_writel(DMC_PHY0_(0x0064+train_info.ddr_freq_num*0xc0), val_tmp);
	val_tmp=__raw_readl(DMC_PHY0_(0x0068+train_info.ddr_freq_num*0xc0));//rf_clkwr_raw_cycle_ac1_sel
	ac1_val=val_tmp;
	val_tmp |= 0x80;
	val_tmp = ((val_tmp&0x7f) >0x20)?(val_tmp- 0x20 ):(val_tmp & 0xffffff80);
	__raw_writel(DMC_PHY0_(0x0068+train_info.ddr_freq_num*0xc0), val_tmp);
	dmc_phy_soft_update();
	// train enable
	dmc_phy_train_en(TRAIN_CADSK_INDEX);
	//train clear
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
	//disable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);//
	//set ca vref
	if(train_info.vrefca_val==0)
	{
		train_info.vrefca_val=0x4d;
	}
	reg_bit_set(DMC_CTL0_(0x0164), 8, 7,train_info.vrefca_val);//rf_train_caeye_vref set 0x5(temp)
	wait_100ns(1);
	//train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
	wait_100ns(1);
	dmc_phy_train_polling_done(TRAIN_CADSK_INDEX,1);
	//train start clear
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
	__raw_writel(DMC_PHY0_(0x0064+train_info.ddr_freq_num*0xc0), ac0_val);
	__raw_writel(DMC_PHY0_(0x0068+train_info.ddr_freq_num*0xc0), ac1_val);
	dmc_phy_soft_update();
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x1);
	*eye_retry=1;
	return;
}


void dmc_phy_train_lp4_rdeye(u32 train_count)
{
	u32 vrefdq_val=0,vrefdq_step=2,vrefdq_min,vrefdq_max,byte_num;
	u32 pass_win_max=0,pass_win_temp;
	u32 rdeye_pos_value,rdeye_pos_max,rdeye_neg_value,rdeye_neg_max;
	u32 rdeye_vref_first=0,rdeye_vref_last=0;
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
		vrefdq_min=train_info.vrefdq_rd_val;
		vrefdq_max=train_info.vrefdq_rd_val;
	}
	for(vrefdq_val=vrefdq_min;vrefdq_val<=vrefdq_max;vrefdq_val+=vrefdq_step)
	{
		//train clear
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x010c),12,1,0x1);//rf_auto_ref_en
		wait_100ns(2);
		//set vrefdq at BB
		reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),23,1,0x0);
		reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),24,8,vrefdq_val);
		//train start
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
		wait_100ns(1);
		if(train_count==1)
			dmc_phy_train_polling_done(TRAIN_RDEYE_INDEX,2);
		else
			dmc_phy_train_polling_done(TRAIN_RDEYE_INDEX,1);
		pass_win_temp=(__raw_readl(DMC_CTL0_(0x0170))>>(train_info.train_chn_num?16:0))&0xff;
		rdeye_pos_value=((__raw_readl(DMC_PHY0_(0x0070+train_info.ddr_freq_num*0xc0))&0x7f)<<0)
							|((__raw_readl(DMC_PHY0_(0x0090+train_info.ddr_freq_num*0xc0))&0x7f)<<8)
							|((__raw_readl(DMC_PHY0_(0x00b0+train_info.ddr_freq_num*0xc0))&0x7f)<<16)
							|((__raw_readl(DMC_PHY0_(0x00d0+train_info.ddr_freq_num*0xc0))&0x7f)<<24);
		rdeye_neg_value=((__raw_readl(DMC_PHY0_(0x0074+train_info.ddr_freq_num*0xc0))&0x7f)<<0)
							|((__raw_readl(DMC_PHY0_(0x0094+train_info.ddr_freq_num*0xc0))&0x7f)<<8)
							|((__raw_readl(DMC_PHY0_(0x00b4+train_info.ddr_freq_num*0xc0))&0x7f)<<16)
							|((__raw_readl(DMC_PHY0_(0x00d4+train_info.ddr_freq_num*0xc0))&0x7f)<<24);
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("rdeye training vref:");
		print_Hex(vrefdq_val);
		dmc_print_str("    ");
		dmc_print_str("Pass Window Value:");
		print_Hex(__raw_readl(DMC_CTL0_(0x0170)));
		dmc_print_str("    ");
		dmc_print_str("Pos Pass Value:");
		print_Hex(rdeye_pos_value);
		dmc_print_str("    ");
		dmc_print_str("Neg Pass Value:");
		print_Hex(rdeye_neg_value);
		dmc_print_str("\r\n");
#endif
		if(train_count==1)
		{
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
		dmc_print_str("\r\nrdeye training pass window is zero!!!");
		while(1);
	}
	for(byte_num=0;byte_num<4;byte_num++)
	{
		reg_bit_set(DMC_PHY0_(0x0070+train_info.ddr_freq_num*0xc0+0x20*byte_num),0,7,(rdeye_pos_max>>(8*byte_num))&0x7f);
		reg_bit_set(DMC_PHY0_(0x0074+train_info.ddr_freq_num*0xc0+0x20*byte_num),0,7,(rdeye_neg_max>>(8*byte_num))&0x7f);
	}
	dmc_phy_soft_update();
	//disable auto refresh
	//reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);
	wait_100ns(2);
	if(train_count==1)
	{
		//update rd vref
		if(rdeye_vref_last<rdeye_vref_first)
		{
			rdeye_vref_last=rdeye_vref_first;
		}
		train_info.vrefdq_rd_val=(rdeye_vref_first+rdeye_vref_last)/2;
		(phy_tmg+train_info.ddr_freq_num)->cfg_io_ds_cfg &= ~(0xFF<<24);
		(phy_tmg+train_info.ddr_freq_num)->cfg_io_ds_cfg |= (train_info.vrefdq_rd_val<<24);
#if TEST_DEBUG_LOG_LEVEL>2
		print_Hex(rdeye_vref_first);
		dmc_print_str("	");
		print_Hex(rdeye_vref_last);
		dmc_print_str("RDEYE Vref Value:");
		print_Hex(train_info.vrefdq_rd_val);
		dmc_print_str("\r\n");
#endif
		//reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),23,1,0x0);
		reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),24,8,train_info.vrefdq_rd_val);

		//clear
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
		wait_100ns(1);
	}
	//enable auto refresh
	//reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);
}

void dmc_phy_train_lp4_rddsk(u32* eye_retry)
{
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
		rddsk_done==1;
	}
	else
	{
		if( ch1_rddsk_done==1 )
		{
			*eye_retry=1;
			return;
		}
		ch1_rddsk_done==1;
	}
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("\r\n-------------rddsk training---------------\r\n");
#endif
	// train enable
	dmc_phy_train_en(TRAIN_RDDSK_INDEX);
	//train clear
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
	wait_100ns(1);
	//set vrefdq at BB
	//reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),23,1,0x0);
	//reg_bit_set(DMC_PHY0_(0x00f4+train_info.ddr_freq_num*0xc0),24,8,0x50);
	//train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
	wait_100ns(1);
	dmc_phy_train_polling_done(TRAIN_RDDSK_INDEX,1);
	//train start clear
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
	*eye_retry=1;
	return;
}


void dmc_phy_train_lp4_vrefdq_set(u32 vref_val)
{
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x0);//rf_auto_ref_en
	wait_100ns(2);
	reg_bit_set(DMC_CTL0_(0x0100),20, 4,(1<<train_info.train_chn_num));
	dmc_mrw(DRAM_MR_14,DRAM_CS_ALL,vref_val);
	reg_bit_set(DMC_CTL0_(0x0104),31, 1,0x0);//dsoft_cmd_allcs
	wait_100ns(5);
	reg_bit_set(DMC_CTL0_(0x0100),20, 4,0x3);
	wait_100ns(2);
	reg_bit_set(DMC_CTL0_(0x010c),12,1,0x1);//rf_auto_ref_en

}

void dmc_phy_train_lp4_wreye_cs0(u32 train_count)
{
	u32 vrefdq_val=0,vrefdq_step=2,vrefdq_min,vrefdq_max;
	u32 pass_win_max,pass_win_temp;
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
		vrefdq_min=train_info.vrefdq_wr_val;
		vrefdq_max=train_info.vrefdq_wr_val;
	}
	for(vrefdq_val=vrefdq_min;vrefdq_val<=vrefdq_max;vrefdq_val += vrefdq_step)
	{
		//train clear
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
		wait_100ns(1);
		reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
		wait_100ns(1);
		//set dq vref
		dmc_phy_train_lp4_vrefdq_set(vrefdq_val);
		//set pass window
		reg_bit_set(DMC_CTL0_(0x0164),16, 8,WREYE_PASS_WIN_MIN);
		//start train
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
		wait_100ns(1);
		if(train_count==1 )
			dmc_phy_train_polling_done(TRAIN_WREYE_INDEX,2);
		else
			dmc_phy_train_polling_done(TRAIN_WREYE_INDEX,1);
		pass_win_temp=(__raw_readl(DMC_CTL0_(0x0170))>>(train_info.train_chn_num*16))&0xff;
		wreye_val_cs0=((__raw_readl(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40))&0x7f)<<0)
							|((__raw_readl(DMC_PHY0_(0x008c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40))&0x7f)<<8);
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("wreye training vref:");
		print_Hex(vrefdq_val);
		dmc_print_str("    ");
		dmc_print_str("Pass Window Value:");
		print_Hex(__raw_readl(DMC_CTL0_(0x0170)));
		dmc_print_str("    ");
		dmc_print_str("Pass Value:");
		print_Hex(__raw_readl(DMC_CTL0_(0x016C)));
		dmc_print_str("\r\n");
#endif
		if(train_count==1)
		{
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
		//clear train start
		reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
	}
	//train clear
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
#ifdef DDR_SCAN_ENABLE
	if(train_info.ddr_clk ==scan_target_clk)
		pass_win_max_scan[train_info.train_chn_num] |= pass_win_max;
#endif
	if(pass_win_max==0)
	{
		dmc_print_str("wreye training pass window is zero!!!");
		while(1);
	}
	reg_bit_set(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),0,7,(wreye_val_cs0>>0)&0x7f);
	reg_bit_set(DMC_PHY0_(0x008c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),0,7,(wreye_val_cs0>>8)&0x7f);
	dmc_phy_soft_update();
	//disable auto refresh
	//reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);
	wait_100ns(2);
	if(train_count==1)
	{
		if(wreye_vref_last<wreye_vref_first)
		{
			wreye_vref_last=wreye_vref_first;
		}
		train_info.vrefdq_wr_val=(wreye_vref_first+wreye_vref_last)/2;
		dmc_phy_train_lp4_vrefdq_set(train_info.vrefdq_wr_val);
#if TEST_DEBUG_LOG_LEVEL>2
		print_Hex(wreye_vref_first);
		dmc_print_str("	");
		print_Hex(wreye_vref_last);
		dmc_print_str("WREYE Vref Value:");
		print_Hex(train_info.vrefdq_wr_val);
		dmc_print_str("\r\n");
#endif
#if defined(VRCG_ON_EN)
		//update wr vref
		(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg14 &= ~(0xFF<<16);
		(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg14 |= (train_info.vrefdq_wr_val<<16);
		__raw_writel(DMC_CTL0_(0x01b8+train_info.ddr_freq_num*0x60), (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg14);
#else
		//update wr vref
		(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12 &= ~(0xFF<<0);
		(dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12 |= (train_info.vrefdq_wr_val<<0);
		__raw_writel(DMC_CTL0_(0x01b0+train_info.ddr_freq_num*0x60), (dmc_dtmg+train_info.ddr_freq_num)->dmc_dtmg12);
#endif
	}
	//enable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
}

void dmc_phy_train_lp4_adjust_cycle ()
{
	u32 cs0_byte0_dqeye_value=0;
	u32 cs0_byte1_dqeye_value=0;
	u32 cs1_byte0_dqeye_value=0;
	u32 cs1_byte1_dqeye_value=0;
	u32 wrdsk_train_value[24];
	int i;
	/*
	if(0 == is_dmc_phy_train_en(TRAIN_WRDSK_INDEX))
	{
		return;
	}*/

#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("\r\n-------------wrdsk training---------------\r\n");
#endif
	//save
	for(i=0; i<24; i++)
	{
		wrdsk_train_value[i] = __raw_readl(wrdsk_train_address[i]);
	}
	dmc_phy_train_info_pre_set(train_info.train_chn_num,DRAM_CS_0);
	// train enable
	dmc_phy_train_en(TRAIN_WRDSK_INDEX);
	//train clear
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear

	//train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//Enable rf_train_start
	wait_100ns(1);

	dmc_phy_train_polling_done(TRAIN_WRDSK_INDEX,2);

	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//Disable rf_train_start

	if( train_info.train_chn_num ==0 )
	{
		cs0_byte0_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),0,8);
		cs0_byte1_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),8,8);
	}
	else
	{
		cs0_byte0_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),16,8);
		cs0_byte1_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),24,8);
	}

	//training cs1
	dmc_phy_train_info_pre_set(train_info.train_chn_num,DRAM_CS_1);

	//train clear
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear

	//train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//Enable rf_train_start
	wait_100ns(1);

	dmc_phy_train_polling_done(TRAIN_WRDSK_INDEX,2);

	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//Disable rf_train_start

	if( train_info.train_chn_num ==0 )
	{
		cs1_byte0_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),0,8);
		cs1_byte1_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),8,8);
	}
	else
	{
		cs1_byte0_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),16,8);
		cs1_byte1_dqeye_value=reg_bit_get(DMC_CTL0_(0x16c),24,8);
	}

	if( (cs0_byte0_dqeye_value==0x0) ||  (cs1_byte0_dqeye_value==0x0) || ((cs0_byte0_dqeye_value) > 0x60) && ((cs1_byte0_dqeye_value) > 0x60) )
	{
		reg_bit_set(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),15,1,1);//rf_clkwr_raw_2cycle_0_sel
	}
	else if(((cs0_byte0_dqeye_value) > 0x40) && ((cs1_byte0_dqeye_value) > 0x40) )
	{
		reg_bit_set(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),15,1,1);//rf_clkwr_raw_2cycle_0_sel
		reg_bit_set(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),7,1,0);//rf_clkwr_raw_cycle_0_sel
	}

	if( (cs0_byte1_dqeye_value==0x0) ||  (cs1_byte1_dqeye_value==0x0) || ((cs0_byte1_dqeye_value) > 0x60) && ((cs1_byte1_dqeye_value) > 0x60))
	{
		reg_bit_set(DMC_PHY0_(0x008c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),15,1,1);//rf_clkwr_raw_2cycle_0_sel
	}
	else if(((cs0_byte1_dqeye_value) > 0x40) && ((cs1_byte1_dqeye_value) > 0x40) )
	{
		reg_bit_set(DMC_PHY0_(0x008c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),15,1,1);//rf_clkwr_raw_2cycle_0_sel
		reg_bit_set(DMC_PHY0_(0x008c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40),7,1,0);//rf_clkwr_raw_cycle_0_sel
	}
	//train clear
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
	#if TEST_DEBUG_LOG_LEVEL >3
	dmc_print_str("\r\n-------------dmc_phy_train_lp4_adjust_cycle---------------\r\n");
	dmc_print_str("\r\ncs0_byte0_dqeye_value=");
	print_Hex(cs0_byte0_dqeye_value);
	dmc_print_str("\r\ncs0_byte1_dqeye_value");
	print_Hex(cs0_byte1_dqeye_value);
	print_Hex(cs1_byte0_dqeye_value);
	dmc_print_str("\r\ncs1_byte1_dqeye_value");
	print_Hex(cs1_byte1_dqeye_value);

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


void dmc_phy_train_lp4_wrdsk(u32* eye_retry)
{
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
		dmc_print_str("\r\n-------------wrdsk training---------------\r\n");
#endif
	// train enable
	dmc_phy_train_en(TRAIN_WRDSK_INDEX);
	//train clear
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
	//disable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x0);//rf_auto_ref_en
	wait_100ns(2);
	//set dq vref  cs1 remove
	if(train_info.train_cs_num == DRAM_CS_0)
	{
		//dmc_phy_train_lp4_vrefdq_set(0x59);//lp4:32%vddq lp4x:47.9%vddq
	}
	//enable auto refresh
	reg_bit_set(DMC_CTL0_(0x010c),12, 1,0x1);//rf_auto_ref_en
	//train start
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
	wait_100ns(1);
	dmc_phy_train_polling_done(TRAIN_WRDSK_INDEX,1);
	//start train clear
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
	dmc_phy_train_optimize_wrdsk_result();
	*eye_retry=1;
	return;
}


void dmc_phy_train_lp4_wreye_cs1()
{
	u32 wreye_val_cs1=0;
	u32 byte_wreye_cs0,byte_wreye_cs1;
	u32 byte_num=0;
	u32 pass_win_temp;
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
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x1);//rf_train_clear
	wait_100ns(1);
	reg_bit_set(DMC_CTL0_(0x0154),2,1,0x0);//rf_train_clear
	wait_100ns(1);
	//start train
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x1);//rf_train_start
	wait_100ns(1);
	dmc_phy_train_polling_done(TRAIN_WREYE_INDEX,1);
	pass_win_temp=((__raw_readl(DMC_CTL0_(0x0170))>>(train_info.train_chn_num*16))&0xff);
#if TEST_DEBUG_LOG_LEVEL>2
	dmc_print_str("    ");
	dmc_print_str("Pass Window Value:");
	print_Hex(__raw_readl(DMC_CTL0_(0x0170)));
	dmc_print_str("    ");
	dmc_print_str("Pass Value:");
	print_Hex(__raw_readl(DMC_CTL0_(0x016C)));
	dmc_print_str("\r\n");
#endif
#ifdef DDR_SCAN_ENABLE
	if(train_info.ddr_clk ==scan_target_clk)
		pass_win_max_scan[train_info.train_chn_num] |= (pass_win_temp << 8);
#endif
	wreye_val_cs1=((__raw_readl(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40))&0x7f)<<0)
							|((__raw_readl(DMC_PHY0_(0x008c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40))&0x7f)<<8);
	//start train
	reg_bit_set(DMC_CTL0_(0x0154),1,1,0x0);//rf_train_start
	wait_100ns(1);
	for(byte_num=0;byte_num<2;byte_num++)
	{
		byte_wreye_cs0=((wreye_val_cs0_max>>(byte_num*8))&0x7f);
		byte_wreye_cs1=((wreye_val_cs1>>(byte_num*8))&0x7f);
		reg_bit_set(DMC_PHY0_(0x007c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40+byte_num*0x20),1,6,
			(byte_wreye_cs1>byte_wreye_cs0)?(byte_wreye_cs1-byte_wreye_cs0):(byte_wreye_cs0-byte_wreye_cs1));
		reg_bit_set(DMC_PHY0_(0x007c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40+byte_num*0x20),0,1,
			(byte_wreye_cs1>byte_wreye_cs0)?0x1:0x0);
		reg_bit_set(DMC_PHY0_(0x007c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40+byte_num*0x20),31,1,0x1);//rf_clkwr_diff_dl_0_cpst_en
		reg_bit_set(DMC_PHY0_(0x006c+train_info.ddr_freq_num*0xc0+train_info.train_chn_num*0x40+byte_num*0x20),0,7,
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


void dmc_phy_train_lp4()
{
	//u32 num=0;
	u32 chn_num=0;
	u32 eye_retry=0;
	for(chn_num=0;chn_num<2;chn_num++)
	{
#if TEST_DEBUG_LOG_LEVEL>2
		dmc_print_str("\r\n----------LP4 training chn num: ");
		print_Dec(chn_num);
		dmc_print_str("-----------");
#endif
		dmc_phy_train_info_pre_set(chn_num,DRAM_CS_0);
		dmc_phy_train_lp4_caeye(1);
		dmc_phy_train_lp4_cadsk(&eye_retry);
		if(eye_retry)
		{
			dmc_phy_train_lp4_caeye(2);
			eye_retry=0;
		}
		//dmc_phy_train_lp4_gate();
		dmc_phy_train_lp4_rdeye(1);
		dmc_phy_train_lp4_rddsk(&eye_retry);
		if(eye_retry)
		{
			dmc_phy_train_lp4_rdeye(2);
			eye_retry=0;
		}
		dmc_phy_train_lp4_adjust_cycle(chn_num);
		dmc_phy_train_info_pre_set(chn_num,DRAM_CS_0);
		dmc_phy_train_lp4_wreye_cs0(1);
		dmc_phy_train_lp4_wrdsk(&eye_retry);
		if(eye_retry)
		{
			dmc_phy_train_lp4_wreye_cs0(2);
			eye_retry=0;
		}
		if(dram_info.cs_num== DRAM_CS_ALL)
		{
			dmc_phy_train_info_pre_set(chn_num,DRAM_CS_1);
			dmc_phy_train_lp4_wrdsk(&eye_retry);
			dmc_phy_train_lp4_wreye_cs1();
		}
	}
}


void dmc_phy_train(u32 ddr_clk,u32 debug_flag)
{
	/****train info init*****/
	train_info.ddr_clk=ddr_clk;
#ifdef CONFIG_DEBUG
	dmc_print_str("\r\ntraining fn:0x");
	print_Hex(train_info.ddr_clk);
	dmc_print_str("MHz");
#endif
	dmc_freq_sel_search(ddr_clk, &train_info.ddr_freq_num);
	//trainning pre set
	dmc_phy_train_pre_set();
	//dfs to target frequency
	sw_dfs_go(train_info.ddr_freq_num);
	//train enable
	reg_bit_set(DMC_CTL0_(0x0154), 0, 1,0x1);//rf_train_enable
	//dmc phy train clear
	dmc_phy_train_all_clear();
	//pre config
	dmc_phy_train_delay_convert();
	if(dram_info.dram_type==DRAM_LP3){
	//lp3 train
	dmc_phy_train_lp3_flag_sel();
	dmc_phy_train_lp3();
	}else{
	//set CA TRAINING flag
	dmc_phy_train_lp4_flag_sel();
	//lp4/lp4x train
	dmc_phy_train_lp4();
	}
	dmc_phy_train_cycle_convert();

	//end train
	reg_bit_set(DMC_CTL0_(0x0154), 0, 1,0x0);//rf_train_enable
	reg_bit_set(DMC_CTL0_(0x0104),31, 1,0x1);//dsoft_cmd_allcs
#ifdef CONFIG_DEBUG
	dmc_print_str("  ok!");
#endif
}


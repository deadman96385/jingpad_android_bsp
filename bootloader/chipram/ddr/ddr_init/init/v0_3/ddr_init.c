#include "ddr_init.h"
#include <gpio_drvapi.h>

extern uint32 ctl_regs_lp3[481];
extern uint32 pi_regs_lp3[249];
extern uint32 phy_regs_lp3[4][1109];
extern uint32 ctl_regs_lp4[481];
extern uint32 pi_regs_lp4[249];
extern uint32 phy_regs_lp4[4][1109];

uint32 pi_fn_div[5]={0};

uint32 ddr_mode =0;
uint32 chip_id =0;
uint32 freq_info[4]={0xe6,0x1cc,0x265,0x398};

uint32 swlvl_bist = 0;
static void ddr_print(char * log)
{
	char *s1 = NULL;
	if((ddr_mode>>5)&0x1)
	{
	  s1 = log;
	  while((*s1) != NULL)
	  {
		while(UART0_TX_BUF_CNT != 0);
		REG32(UART0_TX_BUF_ADDR) = *s1;
		s1++;
	  }
	}
}

static void ddr_char_output(char ch)
{
	if((ddr_mode>>5)&0x1)
	{
		//wait until uart1 tx fifo empty
		while(UART0_TX_BUF_CNT != 0);
		//put out char by uart1 tx fifo
		REG32(UART0_TX_BUF_ADDR) = ch;
	}
	return;
}

static char ascii[]="0123456789abcdef";
static void ddr_print_hex_u32(uint32 data)
{
	uint32 index,i;

	ddr_char_output('0');
	ddr_char_output('x');
	for(i=4;i<=32;i=i+4)
	{
		index= (data>>(32-i))&0xf;
		ddr_char_output(ascii[index]);
	}
	ddr_char_output(' ');
	return;
}

uint32 bist_base_addr[3];

//val
BOOLEAN islp3=0;
BOOLEAN pi_training_on=0;

BOOLEAN is_lp3()
{
	#ifdef DRAM_LPDDR3
	return 1;
	#else
	return 0;
	#endif
	//return DRAM_LPDDR3;
}
BOOLEAN pi_training_on_check()
{
    if(PI_TRAINING_ON==0x1)
	    return 1;
    else
	    return 0;
}


uint32 __get_mhz_num(uint32 ddr_clk)
{
   volatile uint32 i = 0;
   for(;;)
   {
      if(ddr_clk > 0)
	  {
           ddr_clk -= 1000000;
		   i++;

	  }else
	  {
         return i;
	  }

   }

}


/*********init freqency target**********************/
void ddr_freq_info_init()
{
	uint32 freq_num=0;
	uint32 freq_val=0;
	uint32 bypass_sel=0x0;
	uint32 dpll_source_sel=0x0;//0:DPLL 920M;1:DPLL 1066M;2:DPLL 1500M;3:DPLL 1840M
	uint32 clk_1xdiv = 0;
	uint32 clk_2xdiv = 0;
	uint32 clk_emc_sel=0;
	uint32 emc_ckg_sel=0;
	for(freq_num=0;freq_num<4;freq_num++)
	{
		switch(freq_num)
		{
		case 0:
			if(islp3)
			{
			  #ifdef DRAM_LPDDR3_750M
			  dpll_source_sel=0x2;emc_ckg_sel=0x2f;freq_val=250;bypass_sel=0x1;//bypass
			  #else
			  if(DPLL_CFG_LP3 == 920)
			  {
				dpll_source_sel=0x0;emc_ckg_sel=0x1f;freq_val=230;bypass_sel=0x1;//bypass
			  }
			  else
			  {
				dpll_source_sel=0x3;emc_ckg_sel=0x3f;freq_val=230;bypass_sel=0x1;//bypass
			  }
			  #endif
			}else
			{
			  #ifdef DRAM_LPDDR4_1000M
			  dpll_source_sel=0x2;emc_ckg_sel=0x2f;freq_val=250;bypass_sel=0x1;
			  #else
			  dpll_source_sel=0x1;emc_ckg_sel=0x27;freq_val=213;bypass_sel=0x1;
			  #endif
			}
			break;
		case 1:
			if(islp3)
			{
			  #ifdef DRAM_LPDDR3_750M
			  dpll_source_sel=0x2;emc_ckg_sel=0x17;freq_val=500;bypass_sel=0x1;//bypass
			  #else
			  if(DPLL_CFG_LP3 == 920)
			  {
				dpll_source_sel=0x0;emc_ckg_sel=0xf;freq_val=460;bypass_sel=0x1;//bypass
			  }else
			  {
				dpll_source_sel=0x3;emc_ckg_sel=0x1f;freq_val=460;bypass_sel=0x1;//bypass
			  }
			  #endif
			}else
			{
			  #ifdef DRAM_LPDDR4_1000M
			  dpll_source_sel=0x2;emc_ckg_sel=0x17;freq_val=500;bypass_sel=0x1;
			  #else
			  dpll_source_sel=0x1;emc_ckg_sel=0xf;freq_val=533;bypass_sel=0x1;
			  #endif
			}
			break;
		case 2:
			if(islp3)
			{
			  #ifdef DRAM_LPDDR3_750M
			  dpll_source_sel=0x2;emc_ckg_sel=0xf;freq_val=750;bypass_sel=0x1;//bypass
			  #else
			  if(DPLL_CFG_LP3 == 920)
			  {
				dpll_source_sel=0x0;emc_ckg_sel=0x13;freq_val=613;bypass_sel=0x0;//deskewpll
			  }else
			  {
				dpll_source_sel=0x3;emc_ckg_sel=0x17;freq_val=613;bypass_sel=0x1;//bypass
			  }
			  #endif
			}else
			{
			  #ifdef DRAM_LPDDR4_1000M
			  dpll_source_sel=0x2;emc_ckg_sel=0xf;freq_val=750;bypass_sel=0x1;
			  #else
			  dpll_source_sel=0x1;emc_ckg_sel=0x13;freq_val=711;bypass_sel=0x0;
			  #endif
			}
			break;
		case 3:
			if(islp3)
			{
			  #ifdef DRAM_LPDDR3_750M
			  dpll_source_sel=0x2;emc_ckg_sel=0xf;freq_val=750;bypass_sel=0x1;//bypass
			  #else
			  if(DPLL_CFG_LP3 == 920)
			  {
				dpll_source_sel=0x0;emc_ckg_sel=0xb;freq_val=920;bypass_sel=0x0;//deskewpll
			  }else
			  {
				dpll_source_sel=0x3;emc_ckg_sel=0xf;freq_val=920;bypass_sel=0x1;//bypass
			  }
			  #endif
			}else
			{
			  #ifdef DRAM_LPDDR4_1000M
			  dpll_source_sel=0x2;emc_ckg_sel=0x13;freq_val=1000;bypass_sel=0x0;
			  #else
			  dpll_source_sel=0x1;emc_ckg_sel=0xb;freq_val=1066;bypass_sel=0x0;
			  #endif
			}
			break;
		}
		freq_info[freq_num]=((dpll_source_sel<<28)|(bypass_sel<<24)|(emc_ckg_sel<<16)|(freq_val<<0));
		REG32(DDR_FREQ_INFO_ADDR+freq_num*4)=freq_info[freq_num];
		islp3?(pi_fn_div[freq_num+1]=0x0):(pi_fn_div[freq_num+1]=((((emc_ckg_sel>>2)&0x1)<<6)|(((emc_ckg_sel>>3)&0xf)<<2)|((emc_ckg_sel&0x3)<<0)));
	}
	//update pi_fn_div[0] 26M ratio
	islp3?(pi_fn_div[0]=0x0):(pi_fn_div[0]=0x40);
}
uint32 fn_ctl_target=0;
uint32 fn_ctl_boot=0;
uint32 fn_pi_target=0;
uint32 fsp_wr=0;
uint32 fsp_op=0;

void ddr_freq_target_set(uint32 ddr_clk)
{
	uint32 ddr_freq=0;
	ddr_freq=__get_mhz_num(ddr_clk);
	if(islp3)
	{
		#ifdef DFS_EN
		fn_ctl_target=0;
		fn_pi_target=0;
		#else
		switch(ddr_freq)
		{
		case 153:
		    fn_ctl_target=0;
		    fn_pi_target=0;
		    break;
		case 230:
		    fn_ctl_target=0;
		    fn_pi_target=0;
		    break;
		case 460:
		    fn_ctl_target=1;
		    fn_pi_target=1;
		    break;
		case 613:
		    fn_ctl_target=2;
		    fn_pi_target=2;
		    break;
		case 920:
		    fn_ctl_target=3;
		    fn_pi_target=3;
		    break;
		}
		#endif
		fsp_wr=0;
		fsp_op=0;
		fn_ctl_boot=0;
	}else
	{
		switch(ddr_freq)
		{
			#ifdef DRAM_LPDDR4_1000M
			case 1000:fn_ctl_target=3;fsp_wr=0;fsp_op=0;break;
			case 750  :fn_ctl_target=2;fsp_wr=1;fsp_op=1;break;
			case 500  :fn_ctl_target=1;fsp_wr=0;fsp_op=0;break;
			case 250  :fn_ctl_target=0;fsp_wr=0;fsp_op=0;break;
			default:while(1);
			#else
			case 1066:fn_ctl_target=3;fsp_wr=0;fsp_op=0;break;
			case 711  :fn_ctl_target=2;fsp_wr=1;fsp_op=1;break;
			case 533  :fn_ctl_target=1;fsp_wr=1;fsp_op=1;break;
			case 213  :fn_ctl_target=0;fsp_wr=1;fsp_op=1;break;
			default:while(1);
			#endif
		}
		fn_ctl_boot=4;
		fn_pi_target=fn_ctl_target+1;
	}

	//dfibus_freq_fn
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_CTL0_(33),0,5,0);
	reg_bit_set(CANDS_CTL0_(33),8,5,1);
	reg_bit_set(CANDS_CTL0_(33),16,5,2);
	reg_bit_set(CANDS_CTL0_(33),24,5,3);
	reg_bit_set(CANDS_CTL0_(34),0,5,4);
	#else
	reg_bit_set(CANDS_CTL0_(33),0,5,1);
	reg_bit_set(CANDS_CTL0_(33),8,5,2);
	reg_bit_set(CANDS_CTL0_(33),16,5,3);
	reg_bit_set(CANDS_CTL0_(33),24,5,4);
	reg_bit_set(CANDS_CTL0_(34),0,5,0);
	#endif

	//dfibus_freq_init
	reg_bit_set(CANDS_CTL0_(32),16,3,fn_ctl_target);
	//dfibus_boot_freq
	reg_bit_set(CANDS_CTL0_(32),24,3,fn_ctl_boot);
	//pi_init_work_freq
	reg_bit_set(CANDS_PI0_(38),0,5,fn_pi_target);

	//dfs_always_write_fsp
	reg_bit_set(CANDS_CTL0_(230),0,1,islp3?0:1);
	//fsp_op_curent
	reg_bit_set(CANDS_CTL0_(230),16,1,islp3?0: fsp_op);
	//fsp_wr_current
	reg_bit_set(CANDS_CTL0_(230),24,1,islp3?0: fsp_wr);

	if(!islp3)
	{
		//mr13_data
		//cs0
		reg_bit_set(CANDS_CTL0_(212),30,1,fsp_wr);
		reg_bit_set(CANDS_CTL0_(212),31,1,fsp_op);
		//cs1
		reg_bit_set(CANDS_CTL0_(224),14,1,fsp_wr);
		reg_bit_set(CANDS_CTL0_(224),15,1,fsp_op);

	}

	reg_bit_set(CANDS_CTL0_(214),8,1,0x1) ;//mr_fsp_data_valid_f0_0
	reg_bit_set(CANDS_CTL0_(214),16,1,0x1);//mr_fsp_data_valid_f1_0
	reg_bit_set(CANDS_CTL0_(214),24,1,0x1);//mr_fsp_data_valid_f2_0
	reg_bit_set(CANDS_CTL0_(215),0,1,0x1) ;//mr_fsp_data_valid_f3_0
	reg_bit_set(CANDS_CTL0_(215),8,1,0x1) ;//mr_fsp_data_valid_f4_0

	reg_bit_set(CANDS_CTL0_(225),24,1,0x1);//mr_fsp_data_valid_f0_1
	reg_bit_set(CANDS_CTL0_(226),0 ,1,0x1);//mr_fsp_data_valid_f1_1
	reg_bit_set(CANDS_CTL0_(226),8 ,1,0x1);//mr_fsp_data_valid_f2_1
	reg_bit_set(CANDS_CTL0_(226),16,1,0x1);//mr_fsp_data_valid_f3_1
	reg_bit_set(CANDS_CTL0_(226),24,1,0x1);//mr_fsp_data_valid_f4_1

}


void dfibus_freq_update(uint32 islp3)
{
    uint32 dfibus_freq_init=0;
    uint32 dfibus_boot_freq=0;
    if(islp3)
    {
        dfibus_freq_init = 3;
    }
    else {
        dfibus_boot_freq = 4;
    }
    reg_bit_set(CANDS_CTL0_(32),16,16,(dfibus_boot_freq<<8)|dfibus_freq_init);
}
//void ctrl_qos_setting()
//{
//}

void ctrl_dfiupd_set(void)
{
    reg_bit_set(CANDS_CTL0_(289),8,1,0x1);//CTRLUPD_REQ_PER_AREF_EN
    reg_bit_set(CANDS_CTL0_(161),0,1,0x0);//lpc_sr_ctrlupd_en
}

void ctrl_lp_set(uint32 islp3)
{

    //reg_bit_set(CANDS_CTL0_(151),17,1,0); //LPI_WAKEUP_EN. XH: this bit must be, otherwise when chip sleep, PHY won't enter deep sleep mode
    reg_bit_set(CANDS_CTL0_(162),8,1,0);//PCPCS_PD_EN

    //only part of lp feature will be enabled. use smart light sleep to control ddr power
    //PD is enabled
    //reg_bit_set(CANDS_CTL0_(151),16,4,0xf;//LPI_WAKEUP_EN, default is 0xf. but before DFS, this parameter must be set to 0 to prevent PHY die in LP state exit
    reg_bit_set(CANDS_CTL0_(153),24,4,0x1);//LP_AUTO_ENTRY_EN, default is 0x0
    reg_bit_set(CANDS_CTL0_(154),0,4,0xf); //LP_AUTO_EXIT_EN, default is 0x0
    //reg_bit_set(CANDS_CTL0_(141),16,4,0x0);//LPI_PD_WAKEUP_F0, default is 0x0
    //reg_bit_set(CANDS_CTL0_(143),16,4,0x0);//LPI_PD_WAKEUP_F1, default is 0x0
    //reg_bit_set(CANDS_CTL0_(145),16,4,0x0);//LPI_PD_WAKEUP_F2, default is 0x0
    //reg_bit_set(CANDS_CTL0_(147),16,4,0x0);//LPI_PD_WAKEUP_F3, default is 0x0
    //reg_bit_set(CANDS_CTL0_(149),16,4,0x0);//LPI_PD_WAKEUP_F4, default is 0x0
}

void phy_lp_setting(uint32 islp3)
{
    //reg_bit_set(CANDS_PHY0_(1072),24,4,0x0);//PHY_LP_WAKEUP, default is 0x0
}

BOOLEAN ddr_clk_set(unsigned int ddr_clk)
{

	uint32 dpll_kint = 0;
	uint32 dpll_nint = 0;
	uint32 clk_1xdiv = 0;
	uint32 clk_2xdiv = 0;
	uint32 clk_emc_sel=0;
	uint32 emc_ckg_sel=0;
	uint32 ddr_freq   = 0;
	uint32 dpll_source_sel=0;
	uint32 freq_num=0;
	uint32 freq_val=0;
	uint32 ssc_val = 0;

	dpll_source_sel=(freq_info[3]>>28)&0xf;
	switch(dpll_source_sel)
	{
	case 0: dpll_nint=0x23;dpll_kint=0x313b13;//920m
		break;
	case 1: dpll_nint=0x29;dpll_kint=0x00;//1066m
		break;
	case 2: dpll_nint=0x39;dpll_kint=0x589d89;//1500m
		break;
	case 3: dpll_nint=0x46;dpll_kint=0x627627;//1840m
		break;
	default:while(1);
	}

	ddr_freq = __get_mhz_num(ddr_clk);
	if(26 == ddr_freq)
	{
		clk_2xdiv = 0; clk_1xdiv = 1; clk_emc_sel = 0; emc_ckg_sel=0x4;
	}else
	{
		for(freq_num=0;freq_num<4;freq_num++)
		{
			freq_val=(freq_info[freq_num]>>0)&0xff;
			if(freq_val==ddr_freq)
			{
				clk_2xdiv=(freq_info[freq_num]>>19)&0xf;
				clk_1xdiv=(freq_info[freq_num]>>18)&0x1;
				clk_emc_sel=(freq_info[freq_num]>>16)&0x3;
				break;
			}
		}
	}
	if((!((ddr_mode>>30)&0x1))&&((ddr_mode>>4)&0x1))
	{
		ssc_val = (ddr_mode>>16)&0xff;
		reg_bit_set(ANA_DPLL_THM_TOP_0_DIV_CTRL_0,0,8,ssc_val);
	}
	#ifdef DDR_CLK_FLOATING
	//clear div_s and mod_en to 0
	reg_bit_set(ANA_DPLL_THM_TOP_0_MODU_CTRL_0, 0, 1, 0);
	reg_bit_set(ANA_DPLL_THM_TOP_0_DIV_CTRL_0, 12, 1, 0);
	#endif

	
	reg_bit_set(ANA_DPLL_THM_TOP_0_DIV_CTRL_0, 0, 1, 1);
	//set dpll0
	reg_bit_set(ANA_DPLL_THM_TOP_0_MODU_CTRL_0, 25, 7,dpll_nint);
	reg_bit_set(ANA_DPLL_THM_TOP_0_MODU_CTRL_0,  2,23,dpll_kint);

	#ifdef DDR_CLK_FLOATING
	reg_bit_set(ANA_DPLL_THM_TOP_0_DIV_CTRL_0, 12, 1, 1);
	reg_bit_set(ANA_DPLL_THM_TOP_0_MODU_CTRL_0, 0, 1, 1);
	#endif

	//reg_bit_set(0xe410601c, 8,1, 1);
	//set div
	reg_bit_set(AON_APB_CGM_CFG, 0,7, (clk_1xdiv<<6)|(clk_2xdiv<<2)|clk_emc_sel);

	//enable 1x/2x clk
	reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,  15, 2, 3);

    #ifdef DPLL_NO_WAIT
    #else
	    wait_us(50);
    #endif
	return TRUE;
}

void cands_ctl_phy_release()
{
	//uint32 i = 0;
	//clear ctl & phy & ahb reset
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 3, 1, 0);
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 6, 1, 0);
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 5, 1, 0);
    #ifdef PHY_RELEASE_NO_WAIT
    #else
	wait_us(10);
    #endif
       //umctl auto gate en
       reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 2, 1, 1);
      //phy auto gate en
      reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 4, 1, 1);
	//ctl & phy en
       reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 0, 2, 0);
    #ifdef PHY_RELEASE_NO_WAIT
    #else
	wait_us(10);
    #endif
	return;
}

/***
*** ddr init default config
***
*******/
void cands_ctl_init()
{
	uint32 ctl_num=0;
	for(ctl_num=0;ctl_num<CTL_REG_NUM;ctl_num++)
	{
		if(islp3)
		{
			REG32(CANDS_CTL0_(ctl_num))=ctl_regs_lp3[ctl_num];
		}else
		{
			REG32(CANDS_CTL0_(ctl_num))=ctl_regs_lp4[ctl_num];
		}
	}

}

void cands_ctrl_dfs_set(islp3)
{
    reg_bit_set(CANDS_CTL0_(171),0,16,0);//TDFI_INIT_COMPLETE_F0 XH: ???
    reg_bit_set(CANDS_CTL0_(172),0,16,0);//TDFI_INIT_COMPLETE_F1
    reg_bit_set(CANDS_CTL0_(173),0,16,0);//TDFI_INIT_COMPLETE_F2
    reg_bit_set(CANDS_CTL0_(174),0,16,0);//TDFI_INIT_COMPLETE_F3
    reg_bit_set(CANDS_CTL0_(175),0,16,0);//TDFI_INIT_COMPLETE_F4
    //XH
    reg_bit_set(CANDS_CTL0_(175),24,1,0);//DFS_PHY_REG_WRITE_EN should be 0
    //reg_bit_set(CANDS_CTL0_(206),8,8,1);//default value of 0x2 is invalid
    //reg_bit_set(CANDS_CTL0_(217),24,8,1);

    //XH: now default value changes to 0x1, i.e., RL3/WL1, please modify to 0x4 and verify again TBD ??
    if(islp3) {
    //reg_bit_set(CANDS_CTL0_(206),8,8,4);//0x1 is for <=166MHz, for safety purpose, set it to 0x4(<=400MHz)
    //reg_bit_set(CANDS_CTL0_(217),24,8,4);

        #ifdef LP3_SIM_FAST_INIT
	        REG32(CANDS_CTL0_(11))=0x100;//F0   
	        REG32(CANDS_CTL0_(12))=0x1;   
	        REG32(CANDS_CTL0_(13))=0x1;   
	        REG32(CANDS_CTL0_(14))=0x1;   
	        REG32(CANDS_CTL0_(23))=0x100;//F3   
	        REG32(CANDS_CTL0_(24))=0x1;   
	        REG32(CANDS_CTL0_(25))=0x1;   
	        REG32(CANDS_CTL0_(26))=0x1;   
        #endif
    }
    else {
    }
}

void cands_phy_deskew_pll_mode_set(uint32 islp3)
{
   uint32 freq_num=0;
   for(freq_num=0;freq_num<4;freq_num++)
   {
	REG32(CANDS_PHY0_(1024))=phy_regs_lp3[freq_num][1024];   //F0 PLL_SW_BYPASS SET
	reg_bit_set(CANDS_PHY0_(1039),0,1,((freq_info[freq_num]>>24)&0x1));//PLL_SW_BYPASS SET
   }
   //default is 0
   REG32(CANDS_PHY0_(1024))=phy_regs_lp3[0][1024];   //return to freq_index=0 for observation
}
void cands_phy_dfs_set(uint32 islp3)
{
	if(islp3)
    {
    //}
    //else
    //{
    //}
    }
    else
    {
    }
}


void cands_pi_init()
{
	uint32 pi_num=0;
	for(pi_num=0;pi_num<PI_REG_NUM;pi_num++)
	{
		if(islp3)
		{
			REG32(CANDS_PI0_(pi_num))=pi_regs_lp3[pi_num];
		}else
		{
			REG32(CANDS_PI0_(pi_num))=pi_regs_lp4[pi_num];
		}
	}

}
void phy_multicast_set(uint32 open_or_close)
{
	reg_bit_set(CANDS_PHY0_(1024),0,1,open_or_close);
}

void phy_multicast_index(uint32 freq_index)
{
	reg_bit_set(CANDS_PHY0_(1024),8,3,freq_index);
}
void cands_phy_init()
{
	uint32 phy_num=0;
	uint32 freq_num=0;
    	uint32 freq_max=4;
	phy_multicast_set(0);
	for(freq_num=0;freq_num<freq_max;freq_num++)
	{
		phy_multicast_index(freq_num);
		for(phy_num=0;phy_num<PHY_REG_NUM2;phy_num++)
		{
			if(islp3)
			{
				REG32(CANDS_PHY0_(1024+phy_num))=phy_regs_lp3[freq_num][1024+phy_num];
			}else
			{
				REG32(CANDS_PHY0_(1024+phy_num))=phy_regs_lp4[freq_num][1024+phy_num];
			}
		}
		for(phy_num=0;phy_num<PHY_REG_NUM1;phy_num++)
		{
			if(islp3)
			{
				REG32(CANDS_PHY0_(phy_num))=phy_regs_lp3[freq_num][phy_num];
			}else
			{
				REG32(CANDS_PHY0_(phy_num))=phy_regs_lp4[freq_num][phy_num];
			}
		}
	}

}

/*
**
**neccessary
**
*/
#if 1
int32 gpio87_val,gpio88_val;
void cands_phy_pinmux_init(uint32 islp3)
{
	//uint32 i = 0;
//	uint32 gpio87_val,gpio88_val;
	sprd_gpio_request(87);
	sprd_gpio_request(88);

	sprd_gpio_direction_input(87);
	sprd_gpio_direction_input(88);

	gpio87_val=sprd_gpio_get(87);
	gpio88_val=sprd_gpio_get(88);
	if(islp3) //lpddr3, single channel, sbs
	{
		//phy_adr_addr_sel_0
		__raw_writel(CANDS_PHY0_(541),0x98);
		//phy_adr_addr_sel_1
		__raw_writel(CANDS_PHY0_(669),0x6507);
		//phy_adr_addr_sel_2
		__raw_writel(CANDS_PHY0_(797),0x10);
		//phy_adr_addr_sel_3
		__raw_writel(CANDS_PHY0_(925),0x0243);

		//phy_adr_bit_mask_0
		reg_bit_set(CANDS_PHY0_(542),16,6,0x3);
		//phy_adr_seg_mask_0
		reg_bit_set(CANDS_PHY0_(542),24,6,0x2);

		//phy_adr_bit_mask_1
		reg_bit_set(CANDS_PHY0_(670),16,6,0xd);
		//phy_adr_seg_mask_1
		reg_bit_set(CANDS_PHY0_(670),24,6,0x0);

		//phy_adr_bit_mask_2
		reg_bit_set(CANDS_PHY0_(798),16,6,0x2);
		//phy_adr_seg_mask_2
		reg_bit_set(CANDS_PHY0_(798),24,6,0x0);

		//phy_adr_bit_mask_3
		reg_bit_set(CANDS_PHY0_(926),16,6,0xf);
		//phy_adr_seg_mask_3
		reg_bit_set(CANDS_PHY0_(926),24,6,0x2);

		//phy_adr_calvl_swizzle0_0_0
		reg_bit_set(CANDS_PHY0_(525),0,24,0x8e);
		//phy_adr_calvl_swizzle1_0_0
		reg_bit_set(CANDS_PHY0_(526),0,24,0x9f);
		//phy_adr_calvl_swizzle0_1_0
		reg_bit_set(CANDS_PHY0_(527),0,24,0x8e);
		//phy_adr_calvl_swizzle1_1_0
		reg_bit_set(CANDS_PHY0_(528),0,24,0x9f);

		//phy_adr_calvl_swizzle0_0_1
		reg_bit_set(CANDS_PHY0_(653),0,24,0xa80c);
		//phy_adr_calvl_swizzle1_0_1
		reg_bit_set(CANDS_PHY0_(654),0,24,0xb90d);
		//phy_adr_calvl_swizzle0_1_1
		reg_bit_set(CANDS_PHY0_(655),0,24,0xa80c);
		//phy_adr_calvl_swizzle1_1_1
		reg_bit_set(CANDS_PHY0_(656),0,24,0xb90d);

		//phy_adr_calvl_swizzle0_0_2
		reg_bit_set(CANDS_PHY0_(781),0,24,0x20);
		//phy_adr_calvl_swizzle1_0_2
		reg_bit_set(CANDS_PHY0_(782),0,24,0x30);
		//phy_adr_calvl_swizzle0_1_2
		reg_bit_set(CANDS_PHY0_(783),0,24,0x20);
		//phy_adr_calvl_swizzle1_1_2
		reg_bit_set(CANDS_PHY0_(784),0,24,0x30);
		//phy_adr_calvl_swizzle0_0_3
		reg_bit_set(CANDS_PHY0_(909),0,24,0x0406);
		//phy_adr_calvl_swizzle1_0_3
		reg_bit_set(CANDS_PHY0_(910),0,24,0x1517);
		//phy_adr_calvl_swizzle0_1_3
		reg_bit_set(CANDS_PHY0_(911),0,24,0x0406);
		//phy_adr_calvl_swizzle1_1_3
		reg_bit_set(CANDS_PHY0_(912),0,24,0x1517);

		//pi_data_byte_swap_en/PI_DATA_BYTE_SWAP_SLICE*
		__raw_writel(CANDS_PI0_(230),0x10301);//xiaohui ??
		reg_bit_set(CANDS_PI0_(231),0,8,0x2);

		//phy_data_byte_order_sel
		reg_bit_set(CANDS_PHY0_(1104),24,8,0x36);//

		/*-------data slice 0-----*/
		//phy_dm_dq_swizzle0_0
		__raw_writel(CANDS_PHY0_(0),0x61740523);
   		//phy_dm_dq_swizzle1_0
		reg_bit_set(CANDS_PHY0_(1),0,4,8);
    		//phy_rdlvl_data_swizzle_0
		//__raw_writel(CANDS_PHY0_(24)+chn_offset,0x43176205);

		/*-------data slice 1-----*/
		//phy_dm_dq_swizzle0_1
		__raw_writel(CANDS_PHY0_(128),0x75362810);
   		//phy_dm_dq_swizzle1_1
		reg_bit_set(CANDS_PHY0_(129),0,4,4);
    		//phy_rdlvl_data_swizzle_1
		//__raw_writel(CANDS_PHY0_(152)+chn_offset,0x42851630);

		/*-------data slice 2-----*/
		//phy_dm_dq_swizzle0_2
		__raw_writel(CANDS_PHY0_(256),0x38024576);
   		//phy_dm_dq_swizzle1_2
		reg_bit_set(CANDS_PHY0_(257),0,4,1);
    		//phy_rdlvl_data_swizzle_2
		//__raw_writel(CANDS_PHY0_(280)+chn_offset,0x31582647);

		/*-------data slice 3-----*/
		//phy_dm_dq_swizzle0_3
		__raw_writel(CANDS_PHY0_(384),0x36748012);
   		//phy_dm_dq_swizzle1_3
		reg_bit_set(CANDS_PHY0_(385),0,4,5);
    		//phy_rdlvl_data_swizzle_3
		//__raw_writel(CANDS_PHY0_(408)+chn_offset,0x34602157);

		//pi_cmd_swap_en
		reg_bit_set(CANDS_PI0_(225),24,1,1);//refer to isharkl2 pinmux_0906 by arthas.zhang

		if((gpio87_val==0)&&(gpio88_val==0))
		{
		#ifdef CUSTOM_BOARD_SUPPORT
			//pi_cke_mux
			__raw_writel(CANDS_PI0_(226),0x000c000D);
			//pi_cs_mux
			__raw_writel(CANDS_PI0_(227),0x08000900);
		#else
			//pi_cke_mux
			__raw_writel(CANDS_PI0_(226),0x0009000D);
			//__raw_writel(CANDS_PI0_(270)+chn_offset,0x0000);

			//pi_cs_mux
			__raw_writel(CANDS_PI0_(227),0x08000C00);
			//__raw_writel(CANDS_PI0_(272)+chn_offset,0x1110);
		#endif
		}else
		{
			//pi_cke_mux
			__raw_writel(CANDS_PI0_(226),0x000c000D);
			//pi_cs_mux
			__raw_writel(CANDS_PI0_(227),0x08000900);

		}
		//pi_odt_mux
		__raw_writel(CANDS_PI0_(228),0x00000000);
		//__raw_writel(CANDS_PI0_(274)+chn_offset,0x0000);

		//pi_reset_mux
		__raw_writel(CANDS_PI0_(229),0x00000000);
		//__raw_writel(CANDS_PI0_(276)+chn_offset,0x0000);

	}else
	{	//lpddr4, two channel, pop
		//phy_adr_addr_sel_0
		__raw_writel(CANDS_PHY0_(541),0x25);
		//phy_adr_addr_sel_1
		__raw_writel(CANDS_PHY0_(669),0x3140);
		//phy_adr_addr_sel_2
		__raw_writel(CANDS_PHY0_(797),0x14);
		//phy_adr_addr_sel_3
		__raw_writel(CANDS_PHY0_(925),0x2503);

		//phy_adr_bit_mask_0
		reg_bit_set(CANDS_PHY0_(542),16,6,0x3);
		//phy_adr_seg_mask_0, not used when LP4
		reg_bit_set(CANDS_PHY0_(542),24,6,0x0);

		//phy_adr_bit_mask_1
		reg_bit_set(CANDS_PHY0_(670),16,6,0xF);
		//phy_adr_seg_mask_1, not used when LP4
		reg_bit_set(CANDS_PHY0_(670),24,6,0x0);

		//phy_adr_bit_mask_2
		reg_bit_set(CANDS_PHY0_(798),16,6,0x3);
		//phy_adr_seg_mask_2, not used when LP4
		reg_bit_set(CANDS_PHY0_(798),24,6,0x0);

		//phy_adr_bit_mask_3
		reg_bit_set(CANDS_PHY0_(926),16,6,0xF);
		//phy_adr_seg_mask_3, not used when LP4
		reg_bit_set(CANDS_PHY0_(926),24,6,0x0);

if(1) {
		//phy_adr_calvl_swizzle0_0_0
		reg_bit_set(CANDS_PHY0_(525),0,24,0xAD);
		//phy_adr_calvl_swizzle1_0_0
		reg_bit_set(CANDS_PHY0_(526),0,24,0x0); //l3 only, lp4 unused
		//phy_adr_calvl_swizzle0_1_0
		reg_bit_set(CANDS_PHY0_(527),0,24,0xAD);
		//phy_adr_calvl_swizzle1_1_0
		reg_bit_set(CANDS_PHY0_(528),0,24,0x0); //l3 only, lp4 unused

		//phy_adr_calvl_swizzle0_0_1
		reg_bit_set(CANDS_PHY0_(653),0,24,0xB9C8);
		//phy_adr_calvl_swizzle1_0_1
		reg_bit_set(CANDS_PHY0_(654),0,24,0x0); //l3 only, lp4 unused
		//phy_adr_calvl_swizzle0_1_1
		reg_bit_set(CANDS_PHY0_(655),0,24,0xB9C8);
		//phy_adr_calvl_swizzle1_1_1
		reg_bit_set(CANDS_PHY0_(656),0,24,0x0); //l3 only, lp4 unused

		//phy_adr_calvl_swizzle0_0_2
		reg_bit_set(CANDS_PHY0_(781),0,24,0x9C);
		//phy_adr_calvl_swizzle1_0_2
		reg_bit_set(CANDS_PHY0_(782),0,24,0x0); //l3 only, lp4 unused
		//phy_adr_calvl_swizzle0_1_2
		reg_bit_set(CANDS_PHY0_(783),0,24,0x9C);
		//phy_adr_calvl_swizzle1_1_2
		reg_bit_set(CANDS_PHY0_(784),0,24,0x0); //l3 only, lp4 unused

		//phy_adr_calvl_swizzle0_0_3
		reg_bit_set(CANDS_PHY0_(909),0,24,0xAD8B);
		//phy_adr_calvl_swizzle1_0_3
		reg_bit_set(CANDS_PHY0_(910),0,24,0x0); //l3 only, lp4 unused
		//phy_adr_calvl_swizzle0_1_3
		reg_bit_set(CANDS_PHY0_(911),0,24,0xAD8B);
		//phy_adr_calvl_swizzle1_1_3
		reg_bit_set(CANDS_PHY0_(912),0,24,0x0); //l3 only, lp4 unused

		//PHY_ADR_CALVL_TRAIN_MASK_0
		reg_bit_set(CANDS_PHY0_(543),0,6,0x3);//please refer to pin mux to see which CA bits are not used
		//PHY_ADR_CALVL_TRAIN_MASK_1
		reg_bit_set(CANDS_PHY0_(671),0,6,0xF);
		//PHY_ADR_CALVL_TRAIN_MASK_2
		reg_bit_set(CANDS_PHY0_(799),0,6,0x3);
		//PHY_ADR_CALVL_TRAIN_MASK_3
		reg_bit_set(CANDS_PHY0_(927),0,6,0xF);
}

		//pi_data_byte_swap_en/PI_DATA_BYTE_SWAP_SLICE*
		//__raw_writel(CANDS_PI0_(230),0x01030201);//XH ??
		//reg_bit_set(CANDS_PI0_(231),0,8,0x00);

		//pi_data_byte_swap_en
		reg_bit_set(CANDS_PI0_(230),0,1,1);
		//pi_data_byte_swap_slice0
		reg_bit_set(CANDS_PI0_(230),8,2,0);
		//pi_data_byte_swap_slice1
		reg_bit_set(CANDS_PI0_(230),16,2,1);
		//pi_data_byte_swap_slice2
		reg_bit_set(CANDS_PI0_(230),24,2,3);
		//pi_data_byte_swap_slice3
		reg_bit_set(CANDS_PI0_(231),0,2,2);

		//phy_data_byte_order_sel
        //					SOC LP3                               				LP4
        //	0     		3 byte_order_sel[7:6]='b00      			2 byte_order_sel[5:4]='b00
        //	1     		1 byte_order_sel[3:2]='b01      			3 byte_order_sel[7:6]='b01
        //	2     		0 byte_order_sel[1:0]='b10      			1 byte_order_sel[3:2]='b10
        //	3       		2 byte_order_sel[5:4]='b11      			0 byte_order_sel[1:0]='b11
		reg_bit_set(CANDS_PHY0_(1104),24,8,0xB4);//

		#ifdef DRAM_LPDDR4_1000M
		/*-------data slice 0-----*/  //Elink LP4
		//phy_dm_dq_swizzle0_0
		__raw_writel(CANDS_PHY0_(0),0x63128075);
		//phy_dm_dq_swizzle1_0
		reg_bit_set(CANDS_PHY0_(1),0,4,4);

		/*-------data slice 1-----*/  //Elink LP4
		//phy_dm_dq_swizzle0_1
		__raw_writel(CANDS_PHY0_(128),0x06182354);
		//phy_dm_dq_swizzle1_1
		reg_bit_set(CANDS_PHY0_(129),0,4,7);

		/*-------data slice 2-----*/  //Elink LP4
		//phy_dm_dq_swizzle0_2
		__raw_writel(CANDS_PHY0_(256),0x05681243);
		//phy_dm_dq_swizzle1_2
		reg_bit_set(CANDS_PHY0_(257),0,4,7);

		/*-------data slice 3-----*/  //Elink LP4
		//phy_dm_dq_swizzle0_3
		__raw_writel(CANDS_PHY0_(384),0x34528076);
		//phy_dm_dq_swizzle1_3
		reg_bit_set(CANDS_PHY0_(385),0,4,1);

		#else
		/*-------data slice 0-----*/
		//phy_dm_dq_swizzle0_0
		__raw_writel(CANDS_PHY0_(0),0x43128075);
   		//phy_dm_dq_swizzle1_0
		reg_bit_set(CANDS_PHY0_(1),0,4,6);

		/*-------data slice 1-----*/
		//phy_dm_dq_swizzle0_1
		__raw_writel(CANDS_PHY0_(128),0x56384021);
   		//phy_dm_dq_swizzle1_1
		reg_bit_set(CANDS_PHY0_(129),0,4,7);

		/*-------data slice 2-----*/
		//phy_dm_dq_swizzle0_2
		__raw_writel(CANDS_PHY0_(256),0x70583412);
   		//phy_dm_dq_swizzle1_2
		reg_bit_set(CANDS_PHY0_(257),0,4,6);

		/*-------data slice 3-----*/
		//phy_dm_dq_swizzle0_3
		__raw_writel(CANDS_PHY0_(384),0x36528107);
   		//phy_dm_dq_swizzle1_3
		reg_bit_set(CANDS_PHY0_(385),0,4,4);
		#endif

		//pi_cmd_swap_en
		reg_bit_set(CANDS_PI0_(225),24,1,1);//refer to isharkl2 pinmux_0906 by arthas.zhang

		//pi_cke_mux
		__raw_writel(CANDS_PI0_(226),0x0E0F0C0D);

		//pi_cs_mux
		__raw_writel(CANDS_PI0_(227),0x0B0A0908);

		//pi_odt_mux
		//__raw_writel(CANDS_PI0_(228),0x00000405);

		//pi_reset_mux
		//__raw_writel(CANDS_PI0_(229),0x00000000);

	}

}
#endif


#ifdef DDR_AUTO_DETECT
void ddr_mpu_set(DRAM_TYPE_E ddr_type)
{
	uint32 remap_en=0;
	uint32 addr_remap=0;
	uint32 addr_remap_reg1=0;
	switch(ddr_type)
	{
		case DRAM_LPDDR3_1CS_4G_X32:break;
		case DRAM_LPDDR3_2CS_8G_X32:break;
		case DRAM_LPDDR3_1CS_6G_X32:break;
		case DRAM_LPDDR3_2CS_12G_X32:break;
		case DRAM_LPDDR3_1CS_8G_X32:break;
		case DRAM_LPDDR3_2CS_16G_X32:break;
		case DRAM_LPDDR3_1CS_12G_X32:break;
		case DRAM_LPDDR3_2CS_24G_X32:break;
		case DRAM_LPDDR3_1CS_16G_X32:break;
		case DRAM_LPDDR3_2CS_32G_X32:break;
		case DRAM_LPDDR3_2CS_24G_X32_X16X3:break;
		case DRAM_LPDDR3_2CS_24G_X32_X16X4:
			remap_en=0x00000fff;
			addr_remap=0x98543210;
			addr_remap_reg1=0x0000dcba;
			break;
		case DRAM_LPDDR3_1CS_8G_X16X2:break;
		case DRAM_LPDDR3_2CS_16G_X32_X16X4:break;
		case DRAM_LPDDR3_2CS_32G_X32_X16X4:break;
		default:   while(1); //invalid density
	}
	REG32(PUB0_DMC_PORT_REMAP_EN)=remap_en;
	REG32(PUB0_DMC_PORT0_ADDR_REMAP)=addr_remap;
	REG32(PUB0_DMC_PORT0_ADDR_REMAP_REG1)=addr_remap_reg1;
	REG32(PUB0_DMC_PORT1_ADDR_REMAP)=addr_remap;
	REG32(PUB0_DMC_PORT1_ADDR_REMAP_REG1)=addr_remap_reg1;
	REG32(PUB0_DMC_PORT2_ADDR_REMAP)=addr_remap;
	REG32(PUB0_DMC_PORT2_ADDR_REMAP_REG1)=addr_remap_reg1;
	REG32(PUB0_DMC_PORT3_ADDR_REMAP)=addr_remap;
	REG32(PUB0_DMC_PORT3_ADDR_REMAP_REG1)=addr_remap_reg1;
	REG32(PUB0_DMC_PORT4_ADDR_REMAP)=addr_remap;
	REG32(PUB0_DMC_PORT4_ADDR_REMAP_REG1)=addr_remap_reg1;
	REG32(PUB0_DMC_PORT5_ADDR_REMAP)=addr_remap;
	REG32(PUB0_DMC_PORT5_ADDR_REMAP_REG1)=addr_remap_reg1;
}

uint32 cands_mrr( uint32 cs_num, uint32 mr_addr)
{
	uint32 reg_val = 0;
	uint32 mrr_completed;
	uint32 timeout;

	reg_bit_set(CANDS_CTL0_(294),23,1,1);		// 0x30000504 int_ack , clear bit[23] mrr_completed

	reg_val = (1<<16)|((cs_num&0xFF)<<8)|(mr_addr&0xFF);
	reg_bit_set(CANDS_CTL0_(184),8,17,reg_val);	// read_modereg

	timeout = 0;
	mrr_completed = 0;
	while(mrr_completed == 0)
	{
		reg_val = REG32(CANDS_CTL0_(292));		// 0x300004fc int_status bit[23] mrr_completed
		mrr_completed = (reg_val>>23)&0x1;
		if(timeout++ > 0x10000)
			return 0;
	}
	reg_bit_set(CANDS_CTL0_(294),23,1,1);		// 0x30000504 int_ack , clear bit[23] mrr_completed

	reg_val = REG32(CANDS_CTL0_(185));		// 0x300002a4 peripheral_mrr_data

	return reg_val;
}

struct MR8_size_info MR8_size[] = {
	{MR8_SIZE_4Gb,4},
	{MR8_SIZE_6Gb,6},
	{MR8_SIZE_8Gb,8},
	{MR8_SIZE_12Gb,12},
	{MR8_SIZE_16Gb,16},
	{MR8_SIZE_32Gb,32},
};

uint32 cands_mr8_to_detect_info(uint32 mr8_value,struct ddr_detect_info *detect_info)
{

	uint32 mr8_type;
	uint32 mr8_size;
	uint32 mr8_width;
	uint32 i;

	mr8_type = (mr8_value & 0x3)>>0;
	mr8_size = (mr8_value & 0x3c)>>2;
	mr8_width = (mr8_value & 0xc0)>>6;

	if(mr8_type != S8_SDRAM)
	{
		return FALSE;
	}

	if(mr8_width == WIDTH_X32)
	{
		detect_info->mem_width = 0x32;

	}else if(mr8_width == WIDTH_X16)
	{
		detect_info->mem_width = 0x16;
	}else{
		return FALSE;
	}

	for(i=0;i<sizeof(MR8_size)/sizeof(MR8_size[0]);i++)
	{
		if(mr8_size == MR8_size[i].mr8_size)
		{
			detect_info->mem_size = MR8_size[i].mem_size;
			return TRUE;
		}
	}

	return FALSE;

}

uint32 mr8_value_cs0;
uint32 mr8_value_cs1;
struct ddr_detect_info detect_info_cs0;
struct ddr_detect_info detect_info_cs1;
uint32 DDR_TYPE_LOCAL;

uint32 cands_ddr_auto_detect()//xiaohui: TBD
{
	uint32 cs_num,die_num;
	uint32 mem_size_total,mem_size_total_hex;
	uint32 ret;

	cs_num = 1;
	die_num = 0;
	mr8_value_cs0 = cands_mrr( 0,8);
	ret = cands_mr8_to_detect_info(mr8_value_cs0,&detect_info_cs0);
	if(ret == FALSE)
	{
		ddr_print("\n\r ddr auto detect CS0 fail ");
		//__ddr_wdg_reset();
	}
	if(detect_info_cs0.mem_width == 0x16)
	{
		die_num += 2;
		detect_info_cs0.mem_size =  detect_info_cs0.mem_size*2;
		detect_info_cs0.mem_width = 0x32;
	}

	mr8_value_cs1 = cands_mrr( 1,8);
	ret = cands_mr8_to_detect_info(mr8_value_cs1,&detect_info_cs1);
	if(ret == TRUE)
	{
		cs_num ++;
		if(detect_info_cs1.mem_width == 0x16)
		{
			die_num += 2;
			detect_info_cs1.mem_size =  detect_info_cs1.mem_size*2;
			detect_info_cs1.mem_width = 0x32;
		}
		mem_size_total = detect_info_cs0.mem_size + detect_info_cs1.mem_size;
		REG32(CANDS_CTL0_(236))=(((uint64)(mem_size_total)*1024*1024*1024/8)&(0xffffffff));	//ddr density low 32bit  uint:byte
		REG32(CANDS_CTL0_(237))=((((uint64)(mem_size_total)*1024*1024*1024/8)>>32)&(0xffffffff));	//ddr density high 32bit uint:byte
	}else{
		ddr_print("\n\r ddr auto detect CS1 fail ");
		mem_size_total = detect_info_cs0.mem_size;
	}

	// DDR TYPE
	// bit[31:28]: 2:lpddr2 3:lpddr3 4:lpddr4
	// bit[23:20]: 1: 1CS  2:2CS
	// bit[19:12] size:4:4Gbit 6:6Gbit 8:8Gbit 0x12:12Gbit 0x16:16Gbit
	// bit[11:4] bit width: 16: 16bit 32:32bit
	// bit[3:0] N*die  2: 2*die  4:4*die
	if(islp3 )
	{
		detect_info_cs0.mem_type = 3;
		detect_info_cs1.mem_type = 3;
	}else{
		detect_info_cs0.mem_type = 4;
		detect_info_cs1.mem_type = 4;
	}
	mem_size_total_hex = (mem_size_total/10)*16+mem_size_total%10;
	DDR_TYPE_LOCAL = (detect_info_cs0.mem_type<<28) |(cs_num<<20)|(mem_size_total_hex<<12) |(detect_info_cs0.mem_width<<4) |(die_num);

	ddr_print("\n\r mr8_value_cs0:");
	ddr_print_hex_u32(mr8_value_cs0);
	ddr_print("\n\r mr8_value_cs1:");
	ddr_print_hex_u32(mr8_value_cs1);
	ddr_print("\n\r DDR_TYPE_LOCAL:");
	ddr_print_hex_u32(DDR_TYPE_LOCAL);
	ddr_mpu_set(DDR_TYPE_LOCAL);
	return DDR_TYPE_LOCAL;
}

void cands_auto_detect_fix_reg(DRAM_TYPE_E ddr_type )//xiaohui: TBD
{
	uint32 cs_map = 0;
	uint32 slice_num;
	uint32 slice_offset;

	//cs_map, dsiable unused cs
	//#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_CTL0_(285),0,2,IS_2CS(ddr_type)?3:1);
	//#else
	//reg_bit_set(CANDS_CTL0_(285)+chn_offset,24,8,1);
	//#endif

	//dram_clk_disable, disable unused cs clock
	//reg_bit_set(CANDS_CTL0_(452)+chn_offset,24,8,IS_2CS(ddr_type)?0xfc:0xfe);
	reg_bit_set(CANDS_CTL0_(417),0,2,0);

	//calvl_cs
	reg_bit_set(CANDS_CTL0_(378),24,1, 0);

	//calvl_cs_map
	reg_bit_set(CANDS_CTL0_(388),24,2, IS_2CS(ddr_type)?3:1);

	//rdlvl_cs
	reg_bit_set(CANDS_CTL0_(349),16,1, 0);
	//rdlvl_cs_map
	reg_bit_set(CANDS_CTL0_(353),0,2, IS_2CS(ddr_type));

	if(!islp3)
	{
		//zq_cal_latch_map  ??????
		reg_bit_set(CANDS_CTL0_(278), 24,2, 1);
		reg_bit_set(CANDS_CTL0_(279),8,2, IS_2CS(ddr_type)?2:0);

		//zq_cal_start_map   ??????
		reg_bit_set(CANDS_CTL0_(278), 16,2, 1);
		reg_bit_set(CANDS_CTL0_(279),0,2, IS_2CS(ddr_type)?2:0);
		//reg_bit_set(CANDS_CTL0_(291), 0,8, 0);
	}

	if(islp3)
	{
		cs_map = IS_2CS(ddr_type)?3:1;
	}else
	{
		cs_map = IS_2CS(ddr_type)?0xf:5;
	}
	//pi_cs_map
	reg_bit_set(CANDS_PI0_(55),24,4,cs_map);
	//calvl_cs_map
	reg_bit_set(CANDS_PI0_(115),0,4,cs_map);
	//rdlvl_cs_map
	reg_bit_set(CANDS_PI0_(97), 0,4, cs_map);
	//rdlvl_gate_cs_map
	reg_bit_set(CANDS_PI0_(97), 8,4, cs_map);
	//wrlvl_cs_map
	reg_bit_set(CANDS_PI0_(79), 0,4, cs_map);
	//wdqlvl_cs_map
	reg_bit_set(CANDS_PI0_(150),0,4, cs_map);

	//phy_per_rank_cs_map
	slice_num = 0;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(8)+slice_offset,8,2,cs_map); //?????
	slice_num = 1;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(8)+slice_offset,8,2,cs_map); //?????
	slice_num = 2;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(8)+slice_offset,8,2,cs_map); //?????
	slice_num = 3;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(8)+slice_offset,8,2,cs_map); //?????

	//phy_cslvl_cs_map
	reg_bit_set(CANDS_PHY0_(1027),8,4,cs_map);
	//phy_calvl_cs_map
	#ifdef DRAM_LPDDR3
	//dq slice select bit0~1 for cs0 bit2~3 for cs1
	reg_bit_set(CANDS_PHY0_(1033),0,8,0x50);
	#else
	reg_bit_set(CANDS_PHY0_(1033),0,8,0x5500);
	#endif

}
#endif

/*
**
**Debug Interface
**
*/

//========================================CANDS_CTL_ALLCHN_INFO========================================//
const CANDS_CTL_PERCHN_QOS_T CANDS_CTL_PERCHN_QOS_INFO[] =
{
        //r_priority    w_priority      bdw             bdw_overflow    fixed_priority_en       all_strobes_used_en     fifo_type_reg
        {0xD,             0xD,              0x63,           1,              1,                      0,                      3},//BIA(128)
        {0xC,             0xC,              0x63,           1,              1,                      0,                      3},//VSP/GSP/AP(64)
        {0xa,             0xa,              67,             1,              1,                      0,                      3},//DISP/CAM(128)
        {0xE,             0xE,              0x63,           1,              1,                      0,                      3},//GPU(128)
        {0xB,             0xB,              0x63,           1,              1,                      0,                      3},//PUBCP/64
        {0x9,             0x9,              0x63,           1,              1,                      0,                      3},//WTL0/WTL1(64)/AON(64)
};

const CANDS_CTL_ALLCHN_QOS_T CANDS_CTL_ALLCHN_QOS_INFO =
{
	//age_count	addr_cmp_en	ap	arb_cmd_q_threshold	bank_split_en	command_age_count	cs_same_en	disable_rd_interleave
	0xf,		1,		    0,	0x17,			    1,		        0xf,			    1,		    0,
	//disable_rw_group_w_bnk_conlit	inhibit_dram_cmd	inorder_accept	num_q_entries_act_disable	placement_en
	0x1,					        0,		            0,		        0x18,				        1,
	//priority_en	q_fullness	rw_same_en	rw_same_page_en	swap_en	w2r_split_en	wr_order_req
	1,		        0,		    1,		    1,		        1,	    1,		        0
};

void cands_ctl_qos_init()
{
    //uint32 i = 0;
	CANDS_CTL_PERCHN_QOS_T * perchn_qos = (CANDS_CTL_PERCHN_QOS_T*)(&CANDS_CTL_PERCHN_QOS_INFO[0]);
	CANDS_CTL_ALLCHN_QOS_T *allchn_qos = (CANDS_CTL_ALLCHN_QOS_T*)(&CANDS_CTL_ALLCHN_QOS_INFO);
    //age_count
    reg_bit_set(CANDS_CTL0_(281),0,8,allchn_qos->age_count); //should check !!!

    //addr_cmp_en
	reg_bit_set(CANDS_CTL0_(281),16,1,allchn_qos->addr_cmp_en);

	//reversed
	//reg_bit_set(CANDS_CTL0_(309),16,1,1);

	//ap
	reg_bit_set(CANDS_CTL0_(65),24,1,allchn_qos->ap);     //disable auto pre-charge mode for DRAM memories

    //arb_cmd_q_threshold
    reg_bit_set(CANDS_CTL0_(409),0,5,allchn_qos->arb_cmd_q_shreshold); //should check !!!

    //bank_split_en
    reg_bit_set(CANDS_CTL0_(282),0, 1,allchn_qos->bank_split_en);

    //command_age_count
    reg_bit_set(CANDS_CTL0_(281), 8,8,allchn_qos->cmd_age_count); //should check !!!

    //cs_same_en
    reg_bit_set(CANDS_CTL0_(283), 8, 1,allchn_qos->cs_same_en);

    //w2r_split_en
    reg_bit_set(CANDS_CTL0_(283), 16, 1,allchn_qos->w2r_split_en);

    //disable_rd_interleave
    reg_bit_set(CANDS_CTL0_(284), 16, 1, allchn_qos->disable_rd_interleave);

    //disable_rw_group_w_bnk_conflict
    reg_bit_set(CANDS_CTL0_(283),24, 2, allchn_qos->disable_rw_group_bank_conflit);
    //inhibit_dram_cmd
    reg_bit_set(CANDS_CTL0_(284),24, 2, allchn_qos->inhibit_dram_en);

    //in_order_accept
    reg_bit_set(CANDS_CTL0_(288),8, 1, allchn_qos->in_order_accept);

    //num_q_entries_act_disable
    reg_bit_set(CANDS_CTL0_(284),0, 5, allchn_qos->num_q_entries_act_disable); //should check !!!

    //placement_en
    reg_bit_set(CANDS_CTL0_(282), 8, 1, allchn_qos->placement_en);

    //priority_en
    reg_bit_set(CANDS_CTL0_(282), 16, 1, allchn_qos->priority_en);

    //q_fullness, should check ???
    reg_bit_set(CANDS_CTL0_(288), 0, 5, allchn_qos->q_fullness);

    //rw_same_en
    reg_bit_set(CANDS_CTL0_(282),24, 1, allchn_qos->rw_same_en);

    //rw_same_page_en
    reg_bit_set(CANDS_CTL0_(283),0, 1, allchn_qos->rw_same_page_en);

    //swap_en
    reg_bit_set(CANDS_CTL0_(284), 8, 1, allchn_qos->swap_en);

    //wr_order_req
    reg_bit_set(CANDS_CTL0_(288), 16,2,allchn_qos->wr_order_req); //Bit [1] = Port ID usage, Bit [0] = Source ID usage, should check

    //axiY_r_priority
    reg_bit_set(CANDS_CTL0_(402),0,4,perchn_qos[0].r_priority);
    reg_bit_set(CANDS_CTL0_(403),8,4,perchn_qos[1].r_priority);
    reg_bit_set(CANDS_CTL0_(404),16,4,perchn_qos[2].r_priority);
    reg_bit_set(CANDS_CTL0_(405),24,4,perchn_qos[3].r_priority);
    reg_bit_set(CANDS_CTL0_(407),0,4,perchn_qos[4].r_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(408),8,4,perchn_qos[5].r_priority); //should check !!!

    //axiY_w_priority
    reg_bit_set(CANDS_CTL0_(402), 8,4,perchn_qos[0].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(403), 16,4,perchn_qos[1].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(404), 24,4,perchn_qos[2].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(406), 0,4,perchn_qos[3].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(407), 8,4,perchn_qos[4].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(408), 16,4,perchn_qos[5].w_priority); //should check !!!

    //axiY_bdw, should check !!!
    reg_bit_set(CANDS_CTL0_(409),8,7,perchn_qos[0].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(410),0,7,perchn_qos[1].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(410), 24,7,perchn_qos[2].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(411), 16,7,perchn_qos[3].bdw); //should check !!!

    //axiY_bdw_overflow, should check !!!
    reg_bit_set(CANDS_CTL0_(409), 16,1,perchn_qos[0].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(410),8,1,perchn_qos[1].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(411),0,1,perchn_qos[2].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(411), 24,1,perchn_qos[3].bdw_overflow); //should check !!!


     reg_bit_set(CANDS_CTL0_(412),8,7,perchn_qos[4].bdw); //should check !!!
     reg_bit_set(CANDS_CTL0_(413),0,7,perchn_qos[5].bdw); //should check !!!
     reg_bit_set(CANDS_CTL0_(412), 16,1,perchn_qos[4].bdw_overflow); //should check !!!
     reg_bit_set(CANDS_CTL0_(413),8,1,perchn_qos[5].bdw_overflow); //should check !!!



    //axiY_fixed_prot_priority_enable  ??? fixed use axiY_r/w_priority of use axiY_AR/AWQOS ??? should check----CHANGE
    reg_bit_set(CANDS_CTL0_(401),24,1,perchn_qos[0].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(403), 0,1,perchn_qos[1].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(404), 8,1,perchn_qos[2].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(405),16,1,perchn_qos[3].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(406),24,1,perchn_qos[4].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(408), 0,1,perchn_qos[5].fixed_priority_en); //should check !!!

    //axiY_all_strobes_used_enable
    reg_bit_set(CANDS_CTL0_(401),16,1,perchn_qos[0].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(402),24,1,perchn_qos[1].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(404),0,1,perchn_qos[2].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(405),8,1,perchn_qos[3].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(406),16,1,perchn_qos[4].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(407),24,1,perchn_qos[5].all_strobes_used_en); //should check !!!

    //axiY_fifo_type_reg
    reg_bit_set(CANDS_CTL0_(402), 16, 2, perchn_qos[0].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(403), 24, 2, perchn_qos[1].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(405), 0, 2, perchn_qos[2].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(406), 8, 2, perchn_qos[3].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(407), 16, 2, perchn_qos[4].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(408), 24, 2, perchn_qos[5].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2

}


/**************************Customer Interface***********************************************/
void cands_pad_cal_clk_set(uint32 ddr_clk)
{
	uint32 ddr_freq=0;
	uint32 cal_clk_val=0;
	ddr_freq = __get_mhz_num(ddr_clk);
	if(islp3)
	{
		#ifdef DFS_EN
		cal_clk_val=0x3;
		#else
		switch(ddr_freq)
		{
		     case 153:cal_clk_val=0x3;break;
		     case 230:cal_clk_val=0x3;break;
		     case 460:cal_clk_val=0x4;break;
		     case 613:cal_clk_val=0x4;break;
		     case 920:cal_clk_val=0x5;break;
		     default:cal_clk_val=0x2;break;
		}
		#endif
	}else
	{
		cal_clk_val=0x0;
	}
	//phy_cal_clk_select, pad calibration clk, 0/1: clk_ctrl/2  2/3/4/5/6/7: clk_ctr/4/8/16/32/64/128
	reg_bit_set(CANDS_PHY0_(1096), 8,3,cal_clk_val);
}

/**************************Customer Interface***********************************************/
void cands_phy_dq_ds_sr_set(void)
{

    uint32 slice_num=0;
    uint32 freq_index;
    uint32 phy_pad_data_drive;
    uint32 phy_pad_dqs_drive;
    phy_multicast_set(0);//PHY_FREQ_SEL_MULTICAST_EN
    for(freq_index=0;freq_index<4;freq_index++)
    {
	phy_multicast_index(freq_index);
	switch(freq_index)
	{
	   case 0:
		phy_pad_data_drive = (0x0<<12) | (0x1<<11) | (((~islp3)&0x1)<<10) | 0x33;//max SR, "lpddr3_odt_en_lv" not used by IO cell. see ticket 46103160
		phy_pad_dqs_drive = (0x1<<13)|(0x0<<12) | (0x1<<11) | (((~islp3)&0x1)<<10) | 0x33;//max SR,
	        for(slice_num=0;slice_num<4;slice_num++)
	        {
			 reg_bit_set(CANDS_PHY0_(544)+slice_num*0x200,0,8,0xFF);//PHY_ADR_TSEL_SELECT_*
			//phy_dq_tsel_enable disabled for idle/wr/rd
			reg_bit_set(CANDS_PHY0_(5)+slice_num*0x200,16,3,0x0);
			reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200,24,3,0x0);
			reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200,0,24,0x00ff00);//PHY_DQ_TSEL_SELECT, idle/wr/rd
			reg_bit_set(CANDS_PHY0_(7)+slice_num*0x200,0,24,0x00ff00);//PHY_DQS_TSEL_SELECT, idle/wr/rd
			reg_bit_set(CANDS_PHY0_(92)+slice_num*0x200,16,8,0x51);//PHY_DQ_TSEL_WR_TIMING, set according to iWhale2 setting
			reg_bit_set(CANDS_PHY0_(93)+slice_num*0x200,8,8,0x51);//PHY_DQS_TSEL_WR_TIMING, set according to iWhale2 setting
		}
		break;
	   case 1:
		phy_pad_data_drive = (0x0<<12) | (0x1<<11) | (((~islp3)&0x1)<<10) | 0x33;//max SR, "lpddr3_odt_en_lv" not used by IO cell. see ticket 46103160
		phy_pad_dqs_drive = (0x1<<13)|(0x0<<12) | (0x1<<11) | (((~islp3)&0x1)<<10) | 0x33;//max SR,
	        for(slice_num=0;slice_num<4;slice_num++)
	        {
			reg_bit_set(CANDS_PHY0_(544)+slice_num*0x200,0,8,0xFF);//PHY_ADR_TSEL_SELECT_*
			//phy_dq_tsel_enable disabled for idle/wr/rd
			reg_bit_set(CANDS_PHY0_(5)+slice_num*0x200,16,3,0x0);
			reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200,24,3,0x0);
			reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200,0,24,0x00ff00);//PHY_DQ_TSEL_SELECT, idle/wr/rd
			reg_bit_set(CANDS_PHY0_(7)+slice_num*0x200,0,24,0x00ff00);//PHY_DQS_TSEL_SELECT, idle/wr/rd
			reg_bit_set(CANDS_PHY0_(92)+slice_num*0x200,16,8,0x51);//PHY_DQ_TSEL_WR_TIMING, set according to iWhale2 setting
			reg_bit_set(CANDS_PHY0_(93)+slice_num*0x200,8,8,0x51);//PHY_DQS_TSEL_WR_TIMING, set according to iWhale2 setting
		}
		break;
	   case 2:
		phy_pad_data_drive = (0x0<<12) | (0x1<<11) | (((~islp3)&0x1)<<10) | 0x33;//max SR, "lpddr3_odt_en_lv" not used by IO cell. see ticket 46103160
		phy_pad_dqs_drive = (0x1<<13)|(0x0<<12) | (0x1<<11) | (((~islp3)&0x1)<<10) | 0x33;//max SR,
	        for(slice_num=0;slice_num<4;slice_num++)
	        {
			reg_bit_set(CANDS_PHY0_(544)+slice_num*0x200,0,8,0xFF);//PHY_ADR_TSEL_SELECT_*
			//phy_dq_tsel_enable disabled for idle/wr/rd
			reg_bit_set(CANDS_PHY0_(5)+slice_num*0x200,16,3,0x0);
			reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200,24,3,0x0);
			reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200,0,24,0x00ff00);//PHY_DQ_TSEL_SELECT, idle/wr/rd
			reg_bit_set(CANDS_PHY0_(7)+slice_num*0x200,0,24,0x00ff00);//PHY_DQS_TSEL_SELECT, idle/wr/rd
			reg_bit_set(CANDS_PHY0_(92)+slice_num*0x200,16,8,0x51);//PHY_DQ_TSEL_WR_TIMING, set according to iWhale2 setting
			reg_bit_set(CANDS_PHY0_(93)+slice_num*0x200,8,8,0x51);//PHY_DQS_TSEL_WR_TIMING, set according to iWhale2 setting
		}
		break;
	   case 3:
		phy_pad_data_drive = (0x0<<12) | (0x1<<11) | (((~islp3)&0x1)<<10) | 0xff;//max SR, "lpddr3_odt_en_lv" not used by IO cell. see ticket 46103160
		phy_pad_dqs_drive = (0x1<<13)|(0x0<<12) | (0x1<<11) | (((~islp3)&0x1)<<10) | 0xff;//max SR,
	        for(slice_num=0;slice_num<4;slice_num++)
	        {
			reg_bit_set(CANDS_PHY0_(544)+slice_num*0x200,0,8,0xFF);//PHY_ADR_TSEL_SELECT_*
			//phy_dq_tsel_enable disabled for idle/wr/rd
			reg_bit_set(CANDS_PHY0_(5)+slice_num*0x200,16,3,0x0);
			reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200,24,3,0x0);
			reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200,0,24,0x00ff00);//PHY_DQ_TSEL_SELECT, idle/wr/rd
			reg_bit_set(CANDS_PHY0_(7)+slice_num*0x200,0,24,0x00ff00);//PHY_DQS_TSEL_SELECT, idle/wr/rd
			reg_bit_set(CANDS_PHY0_(92)+slice_num*0x200,16,8,0x51);//PHY_DQ_TSEL_WR_TIMING, set according to iWhale2 setting
			reg_bit_set(CANDS_PHY0_(93)+slice_num*0x200,8,8,0x51);//PHY_DQS_TSEL_WR_TIMING, set according to iWhale2 setting
		}
		break;
	}

	__raw_writel(CANDS_PHY0_(1075),(phy_pad_dqs_drive<<16) | phy_pad_data_drive);
    }

}

void cands_phy_ca_ds_sr_set(void) //xiaohui: TBD
{
    //uint32 ds,uint32 odt_en,uint32 odt,uint32 ca_sr,uint32 dq_sr
	uint32 slice_num=0;
    uint32 freq_index;
    uint32 phy_pad_cke_drive,phy_pad_clk_drive,phy_pad_cs_drive,phy_pad_rst_drive,phy_pad_addr_drive,phy_pad_fdbk_drive;
    //uint32 phy_pad_cke_drive,phy_pad_clk_drive,phy_pad_cs_drive,phy_pad_rst_drive,phy_pad_addr_drive,phy_pad_fdbk_drive;
    phy_multicast_set(0);//PHY_FREQ_SEL_MULTICAST_EN
	for(freq_index=0;freq_index<4;freq_index++)
	{
		phy_multicast_index(freq_index);
        switch(freq_index)
        {
            case 0:
                phy_pad_cke_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xFF77;//max SR, 60ohm@F0
                phy_pad_clk_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xFF77;
                phy_pad_cs_drive  = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xFF77;
                phy_pad_rst_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xFF77;
                phy_pad_addr_drive =(0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xFF77;//caution: address DRV is set by 
                phy_pad_fdbk_drive =(0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xFF77;
                break;
            case 1:
                phy_pad_cke_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;//max SR, 40ohm@F1
                phy_pad_clk_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_cs_drive  = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_rst_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_addr_drive =(0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_fdbk_drive =(0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                break;
            case 2:
                phy_pad_cke_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;//max SR, 40ohm@F2
                phy_pad_clk_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_cs_drive  = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_rst_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_addr_drive =(0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_fdbk_drive =(0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                break;
            case 3:
                phy_pad_cke_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;//max SR, 40ohm@F3
                phy_pad_clk_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_cs_drive  = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_rst_drive = (0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_addr_drive =(0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                phy_pad_fdbk_drive =(0x1<<19) | (((~islp3)&0x1)<<18) | (0x0<<16) | 0xffff;
                break;
        }
	    __raw_writel(CANDS_PHY0_(1083), phy_pad_cke_drive);	  //phy_pad_cke_drive
	    __raw_writel(CANDS_PHY0_(1077), phy_pad_clk_drive);	  //phy_pad_clk_drive
	    __raw_writel(CANDS_PHY0_(1087), phy_pad_cs_drive);	  //phy_pad_cs_drive
	    __raw_writel(CANDS_PHY0_(1085), phy_pad_rst_drive);	  //phy_pad_rst_drive
	    __raw_writel(CANDS_PHY0_(1076), phy_pad_addr_drive);	  //phy_pad_addr_drive
	    __raw_writel(CANDS_PHY0_(1074), phy_pad_fdbk_drive);	  //phy_pad_fdbk_drive

    }

}


//void device_ds_odt_set()//xiaohui: TBD
//{
//
//}


void cands_phy_vref_set()//xiaohui: TBD
{

}

void device_vref_set()//xiaohui: TBD
{

}

void cands_ac_timing_set()//xiaohui: TBD
{

}



/**********start init************/
void ddr_init_trigger(uint32 pi_training_on)
{
    if(pi_training_on==0x1) {
	//pi_start
	reg_bit_set(CANDS_PI0_(0),0,1,1);
    }
	//trigger whole ddr init flow, set START to 1
	reg_bit_set(CANDS_CTL0_(0),0,1,1);
}


//*************************DDR Training**************************************************************************:
//#ifdef PHONE_INIT
void pi_training_cs_map(void) //
{
    reg_bit_set(CANDS_PI0_(55),24,4,PI_CS_MAP);
    reg_bit_set(CANDS_PI0_(76),16,2,PI_CS_MAP);//PI_WRLVL_CS
    reg_bit_set(CANDS_PI0_(94),16,2,PI_CS_MAP);//PI_RDLVL_CS
    reg_bit_set(CANDS_PI0_(113),8,2,PI_CS_MAP);//PI_CALVL_CS
    reg_bit_set(CANDS_PI0_(152),0,2,PI_CS_MAP);//PI_WDQLVL_CS
    reg_bit_set(CANDS_PI0_(79),0,4,PI_CS_MAP);//PI_WRLVL_CS_MAP //XH ??? set a 4bit wide parameter to 0x3 ???
    reg_bit_set(CANDS_PI0_(97),0,4,PI_CS_MAP);//PI_RDLVL_CS_MAP
    reg_bit_set(CANDS_PI0_(97),8,4,PI_CS_MAP);//PI_RDLVL_GATE_CS_MAP
    reg_bit_set(CANDS_PI0_(115),0,4,PI_CS_MAP);//PI_CALVL_CS_MAP
    reg_bit_set(CANDS_PI0_(150),0,4,PI_CS_MAP);//PI_WDQLVL_CS_MAP
}
void pi_training_enable(void) //xiaohui: TBD
{
    REG32(CANDS_PI0_(2 ))=0x0;//PI_TDFI_PHYMSTR_MAX_F0
    REG32(CANDS_PI0_(4 ))=0x0;//PI_TDFI_PHYMSTR_MAX_F1
    REG32(CANDS_PI0_(6 ))=0x0;//PI_TDFI_PHYMSTR_MAX_F2
    REG32(CANDS_PI0_(8 ))=0x0;//PI_TDFI_PHYMSTR_MAX_F3
    REG32(CANDS_PI0_(10))=0x0;//PI_TDFI_PHYMSTR_MAX_F4
    reg_bit_set(CANDS_PI0_(1), 0,1,0x1); //pi_normal_lvl_seq
    reg_bit_set(CANDS_PI0_(1), 8,1,0x1); //pi_init_lvl_en
    reg_bit_set(CANDS_PI0_(77), 8,2,PI_WRLVL_EN); //pi_wrlvl_en
    reg_bit_set(CANDS_PI0_(123), 8,2,PI_CALVL_EN);//pi_calvl_en
    reg_bit_set(CANDS_PI0_(99),24,2,PI_RDLVL_GATE_EN); //pi_rdlvl_gate_en
    reg_bit_set(CANDS_PI0_(99),16,2,PI_RDLVL_EN); //pi_rdlvl_en
    reg_bit_set(CANDS_PI0_(155),16,2,0);//pi_wdqlvl_en
    reg_bit_set(CANDS_PI0_(129),24,2,0);//pi_ca_train_vref_en
    reg_bit_set(CANDS_PI0_(147),24,2,0);//pi_wdqlvl_vref_en
    pi_training_cs_map();
}

//lp4 training
void training_cs_map (uint32 cs_val) {/*{{{*/
    // CS_MAP
    //reg_bit_set(CANDS_CTL0_(285),0,2,cs_val); //XH: ???

    // PI_CS_MAP
    reg_bit_set(CANDS_PI0_(55),24,4,cs_val); //XH: ???

    // PI_WRLVL_CS_MAP
    reg_bit_set(CANDS_PI0_(79),0,4,cs_val); //XH: ???

    // PI_RDLVL_CS_MAP
    reg_bit_set(CANDS_PI0_(97),0,4,cs_val); //XH: ???

    // PI_RDLVL_GATE_CS_MAP
    reg_bit_set(CANDS_PI0_(97),8,4,cs_val); //XH: ???

    // PI_CALVL_CS_MAP
    reg_bit_set(CANDS_PI0_(115),0,4,cs_val); //XH: ???

    // PI_WDQLVL_CS_MAP
    reg_bit_set(CANDS_PI0_(150),0,4,cs_val); //XH: ???
    reg_bit_set(CANDS_PI0_(76),16,2,PI_CS_MAP);//PI_WRLVL_CS
    reg_bit_set(CANDS_PI0_(94),16,2,PI_CS_MAP);//PI_RDLVL_CS
    reg_bit_set(CANDS_PI0_(113),8,2,PI_CS_MAP);//PI_CALVL_CS
    reg_bit_set(CANDS_PI0_(152),0,2,PI_CS_MAP);//PI_WDQLVL_CS

    reg_bit_set(CANDS_PI0_(37), 0, 5, PI_FREQ_MAP);    //pi_freq_map
}

void training_pat_sel(uint32 pat_val) {
    uint32 i;
    for(i=0;i<4;i++) {
        // phy_wdqlvl_patt_0/1/2/3
        reg_bit_set(CANDS_PHY0_(28)+0x200*i,0,3,pat_val);
    }
}

void init_training_enable(void) {
    // dfi_inv_data_cs
    reg_bit_set(CANDS_CTL0_(31),8,1,0x1); //XH: LP4 cs polarity is different with lp3

    //please refer to pin mux to see byte order
    // phy_calvl_vref_driving_slice_0.
    reg_bit_set(CANDS_PHY0_(35),16,1,0x1);

    // phy_calvl_vref_driving_slice_1
    reg_bit_set(CANDS_PHY0_(163),16,1,0x0);

    // phy_calvl_vref_driving_slice_2
    reg_bit_set(CANDS_PHY0_(291),16,1,0x0);

    // phy_calvl_vref_driving_slice_3
    reg_bit_set(CANDS_PHY0_(419),16,1,0x1);
}

void phy_lp4_boot_pll_config(void) {
    // phy_lp4_boot_pll_ctrl0
    reg_bit_set(CANDS_PHY0_(1056),7,8,0x10);// vcodiv
    reg_bit_set(CANDS_PHY0_(1056),21,6,0x3);// bootcount

	// phy_lp4_boot_pll_ctrl0
    reg_bit_set(CANDS_PHY0_(1059),7,8,0x10);// vcodiv
    reg_bit_set(CANDS_PHY0_(1059),21,6,0x3);// bootcount
}

void lp4_boot_setting (void) {
    uint32 i;
    // phy_lp4_boot_disable
    reg_bit_set(CANDS_PHY0_(1026),24,1,0x0);//

    for(i=0;i<4;i=i+1) {
        // phy_lp4_boot_rddqs_latency_adjust_0/1/2/3
        reg_bit_set(CANDS_PHY0_(10)+0x200*i,0,4,0x0);//
        // phy_lp4_boot_rddata_en_dly_0/1/2/3
        reg_bit_set(CANDS_PHY0_(9)+0x200*i,8,4,0x8);//
    }
}

void lp4_phy_vref_cfg(void)
{
    uint32 i=0;

    #ifdef DRAM_LPDDR4
    unsigned short int lp4_phy_dq_vref_slice0[]={0xd16,0xd16,0xd16,0xd16};
    unsigned short int lp4_phy_dq_vref_slice1[]={0xd16,0xd16,0xd16,0xd16};
    unsigned short int lp4_phy_dq_vref_slice2[]={0xd16,0xd16,0xd16,0xd16};
    unsigned short int lp4_phy_dq_vref_slice3[]={0xd16,0xd16,0xd16,0xd16};
    #else
    unsigned short int lp4_phy_dq_vref_slice0[]={0xd29,0xd29,0xd29,0xd29};
    unsigned short int lp4_phy_dq_vref_slice1[]={0xd29,0xd29,0xd29,0xd29};
    unsigned short int lp4_phy_dq_vref_slice2[]={0xd29,0xd29,0xd29,0xd29};
    unsigned short int lp4_phy_dq_vref_slice3[]={0xd29,0xd29,0xd29,0xd29};
    #endif
    unsigned short int lp4_phy_ca_vref[]={0xd2e,0xd2e,0xd2e,0xd2e};
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(1024),  8,  3, i);
        reg_bit_set(CANDS_PHY0_(1048),  8, 14, lp4_phy_dq_vref_slice0[i]);
        reg_bit_set(CANDS_PHY0_(1049),  0, 14, lp4_phy_dq_vref_slice1[i]);
        reg_bit_set(CANDS_PHY0_(1049), 16, 14, lp4_phy_dq_vref_slice2[i]);
        reg_bit_set(CANDS_PHY0_(1050),  0, 14, lp4_phy_dq_vref_slice3[i]);
        reg_bit_set(CANDS_PHY0_(1050), 16, 14, lp4_phy_ca_vref[i]);
    }
}

void dq_vref_training_setting()
{
   reg_bit_set(CANDS_PI0_(147),24,1,0x1); //pi_wdqlvl_vref_en
   reg_bit_set(CANDS_PI0_(150),8,7,0x40); //pi_wdqlvl_vref_initial_start_point	33% range0
   reg_bit_set(CANDS_PI0_(150),16,7,0x72);//pi_wdqlvl_vref_initial_stop_point	52% range0
   reg_bit_set(CANDS_PI0_(150),24,4,0x4); //pi_wdqlvl_vref_initial_stepsize
   reg_bit_set(CANDS_PI0_(151),0,4,0x2);  //pi_wdqlvl_vref_normal_stepsize
   reg_bit_set(CANDS_PI0_(151),8,4,0x1);  //pi_wdqlvl_vref_delta
}

void ca_vref_training_setting()
{
	reg_bit_set(CANDS_PI0_(137), 16, 7, 0x6D);     //pi_calvl_vref_initial_start_point	40% range1
	reg_bit_set(CANDS_PI0_(137), 24, 7, 0x6D);     //pi_calvl_vref_initial_stop_point	40% range1
	reg_bit_set(CANDS_PI0_(138),  0, 4, 0x04);     //pi_calvl_vref_initial_stepsize
	reg_bit_set(CANDS_PI0_(138),  8, 4, 0x02);     //pi_calvl_vref_normal_stepsize
	reg_bit_set(CANDS_PI0_(138), 16, 4, 0x01);     //pi_calvl_vref_delta
}


void lp4_init_training_enable ()
{
	uint32 cs_val;
	uint32 pat_sel;

	if(PI_CS_MAP==1)
	    cs_val = 0x5; //xiaohui_pi: why 0x5? for 1 cs
	else if(PI_CS_MAP==3)
	    cs_val = 0xf; //xiaohui_pi: why 0xf? for 2cs//may deadlock, why?? for 1cs
	pat_sel = 0x1;

	lp4_phy_vref_cfg();
	dq_vref_training_setting();
	ca_vref_training_setting();
	lp4_boot_setting();
	phy_lp4_boot_pll_config();
	training_cs_map(cs_val);
	//lp4_set_boot_freq(init_freq, train_freq);
	training_pat_sel(pat_sel);
	init_training_enable();
	//lp4_fsp_setting(fsp_val);
} /*}}}*/

void lp4_pi_training_cfg(uint32 freq_sel) //xiaohui: TBD
{
    switch(freq_sel)
    {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
		reg_bit_set(CANDS_PI0_(99),24,2,0); //pi_rdlvl_gate_en
            break;
        case 4:
		reg_bit_set(CANDS_PI0_(99),24,2,0); //pi_rdlvl_gate_en
            break;
        default:
            break;
    }
}




void polling_pi_training_done(uint32 is_init_training, uint32 islp3) //XH: TBD
{
	volatile uint32 pi_tr_done = 0;
	volatile uint32 i = 0;
	uint32 freq_sel = 0;

    //ddr_print("\r\n\r\nenter pub0 polling pi training");

    if(islp3==0x1)
    {
        if(is_init_training==0x1) {
		    while(pi_tr_done == 0)
		    {
		    	pi_tr_done = (REG32(CANDS_PI0_(213))&0x1);
            }
		    pi_tr_done = REG32(CANDS_PI0_(213));
            if((pi_tr_done&0x3fffe)!=0x0) {
                REG32(REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_DUMMY_REG1)=token_pi_training_error;
            }
        }
        else {
		    pi_tr_done = REG32(CANDS_PI0_(213));
        }
	    REG32(CANDS_PI0_(214)) = 0x3ffff;
    }
    else
	{
		//write freq_int_en
		//reg_bit_set(PUB0_APB_FREQ_ACK_LP4_INIT+chn_offset,0,1,1);

		while(pi_tr_done == 0)
		{
			i++;
			pi_tr_done = (REG32(CANDS_PI0_(213))&0x1);

			if(1==pi_tr_done)
				break;

			if((REG32(REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_PHY_BIST)>>13)&0x1) {
				freq_sel = (REG32(REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_PHY_BIST)>>8) & 0x1F;
				//ddr_print("\r\nddr current freq = ");
				//ddr_print_u32_hex(freq_sel);
				//ddr_print_hex_u32(freq_sel);
			    //vref rang set
			    //lp4_pi_training_cfg( freq_sel);

				//set new clk div
				reg_bit_set(AON_APB_CGM_CFG,0,8,pi_fn_div[freq_sel]);

			    // Set phy_freq_change_ack
			    REG32(REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_DUMMY_REG0_SET) = (0x1<<1);

			    // Polling phy_freq_change_req until 0
			    while((REG32(REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_PHY_BIST)>>13)&0x1);

			    // Clear phy_freq_change_ack
			    REG32(REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_DUMMY_REG0_CLR) = (0x1<<1);
			}
			wait_us(10);

			pi_tr_done = (REG32(CANDS_PI0_(213))&0x1);

		}
		REG32(CANDS_PI0_(214)) = 0x3ffff; //XH: clear int ???
	}
}
//#endif

void wait_ctl_init_done()
{
	volatile uint32 ctl_tr_done = 0;
	volatile uint32 i = 0;
	volatile uint32 timeout = 0;

	do{
		for(i = 0; i <10; i++);

		ctl_tr_done = (REG32(CANDS_CTL0_(292))&0x10);

		timeout++;
		//if(islp3)
		//{
		//	if(timeout == 0x800)
		//	{
		//		// do manual rx cal
		//		reg_bit_set(CANDS_PHY0_(55), 0,1,1);
		//		reg_bit_set(CANDS_PHY0_(183),0,1,1);
		//		reg_bit_set(CANDS_PHY0_(311),0,1,1);
		//		reg_bit_set(CANDS_PHY0_(439),0,1,1);
		//	}
		//}

		//if(timeout == 0x1000)
			//__ddr_wdg_reset();
	}
	while(ctl_tr_done == 0);

	//ddr_print("\r\nleave ddr wait ctl init done");

}

//*****************************************after init done *********************************:
void sync_mr12_mr14(BOOLEAN islp3)
{
    uint32 tmp=0;

	if(islp3)
	{
		return;
	}
	else
	{
		//fsp_phy_update_mrw
		reg_bit_set(CANDS_CTL0_(229),24, 1, 0);  ///?????? define which part to updat MR12&MR14 in init/dfs/sw mrw 0:ctl 1:phy or pi

		//____________________mr12_cs0____________________
		tmp=reg_bit_get(CANDS_PI0_(157),8,8);       //MR12_DATA_F0_0
		reg_bit_set(CANDS_CTL0_(212),16,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(158),24,8);       //MR12_DATA_F1_0
		reg_bit_set(CANDS_CTL0_(211),16,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(160),8,8);       //MR12_F2_0
		reg_bit_set(CANDS_CTL0_(211),24,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(161),24,8);       //MR12_F3_0
		reg_bit_set(CANDS_CTL0_(212),0,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(163),8,8);       //MR12_F4_0
		reg_bit_set(CANDS_CTL0_(212),8,8,tmp);
		//____________________mr12_cs1____________________
		tmp=reg_bit_get(CANDS_PI0_(165),0,8);       //MR12_F0_1
		reg_bit_set(CANDS_CTL0_(224),0,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(166),16,8);       //MR12_F1_1
		reg_bit_set(CANDS_CTL0_(223),0,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(168),0,8);       //MR12_F2_1
		reg_bit_set(CANDS_CTL0_(223),8,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(169),16,8);       //MR12_F3_1
		reg_bit_set(CANDS_CTL0_(223),16,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(171), 0,8);       //MR12_F4_1
		reg_bit_set(CANDS_CTL0_(223),24,8,tmp);
		//____________________mr14_cs0____________________
		tmp=reg_bit_get(CANDS_PI0_(157),16,8);       //MR14_F0_0
		reg_bit_set(CANDS_CTL0_(214),0,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(159),0,8);       //MR14_F1_0
		reg_bit_set(CANDS_CTL0_(213),0,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(160),16,8);       //MR14_F2_0
		reg_bit_set(CANDS_CTL0_(213),8,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(162),0,8);       //MR14_F3_0
		reg_bit_set(CANDS_CTL0_(213),16,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(163),16,8);       //MR14_F4_0
		reg_bit_set(CANDS_CTL0_(213),24,8,tmp);
		//____________________mr14_cs1____________________
		tmp=reg_bit_get(CANDS_PI0_(165),8,8);       //MR12_F0_1
		reg_bit_set(CANDS_CTL0_(225),16,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(166),24,8);       //MR12_F1_1
		reg_bit_set(CANDS_CTL0_(224),16,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(168),8,8);       //MR12_F2_1
		reg_bit_set(CANDS_CTL0_(224),24,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(169),24,8);       //MR12_F3_1
		reg_bit_set(CANDS_CTL0_(225),0,8,tmp);

		tmp=reg_bit_get(CANDS_PI0_(171), 8,8);       //MR12_F4_1
		reg_bit_set(CANDS_CTL0_(225), 8,8,tmp);
	}
 }
void f0_master_delay_update()
{
    uint32 tmp=0;
    uint32 slice=0;
    for(slice=0; slice<4; slice++)
    {
//        reg_bit_set(CANDS_PHY0_(516)+(slice*0x200),0, 3, 0);     //phy_adr_master_dly_lock_obs_select
//        reg_bit_set(CANDS_PHY0_(517)+(slice*0x200),8, 1, 1);     //sc_phy_adr_snap_obs_regs
//        tmp=reg_bit_get(CANDS_PHY0_(516)+(slice*0x200),8, 10);     //phy_adr_master_dly_lock_obs
//        tmp=(tmp*(1.5));
//        if(tmp>0x3ff)
//        {
//            tmp=0x3ff;
//        }
        reg_bit_set(CANDS_PHY0_(514)+(slice*0x200), 0, 1, 1);     //phy_adr_clk_bypass_override
        //reg_bit_set(CANDS_PHY0_(513)+(slice*0x200),16, 10, tmp);     //phy_adr_clk_wr_bypass_slave_delay

        reg_bit_set(CANDS_PHY0_(23)+(slice*0x200), 16, 3, 0);     //phy_master_dly_lock_obs_select
        reg_bit_set(CANDS_PHY0_(14)+(slice*0x200), 24, 1, 1);     //sc_phy_snap_obs_regs
        tmp=reg_bit_get(CANDS_PHY0_(38)+(slice*0x200), 16, 10);     //phy_master_dly_lock_obs
        tmp=(tmp*(2.1));
        if(tmp>0x3ff)
        {
            tmp=0x3ff;
        }
        reg_bit_set(CANDS_PHY0_(1)+(slice*0x200), 8, 10, tmp);     //phy_clk_wr_bypass_slave_delay
        reg_bit_set(CANDS_PHY0_(1)+(slice*0x200), 18, 1, 1);     //phy_clk_wr_bypass_slave_delay
   }
}

void ddr_lowpower_pre_cfg()
{
	//lpi_sr_mcclk_gate_wakeup_f0
	reg_bit_set(CANDS_CTL0_(142), 0, 4,0x6);
	//lpi_sr_mcclk_gate_wakeup_f1
	reg_bit_set(CANDS_CTL0_(144), 0, 4,0x6);
	//lpi_sr_mcclk_gate_wakeup_f2
	reg_bit_set(CANDS_CTL0_(146), 0, 4,0x6);
	//lpi_sr_mcclk_gate_wakeup_f3
	reg_bit_set(CANDS_CTL0_(148), 0, 4,0x6);
	//lpi_sr_mcclk_gate_wakeup_f4
	reg_bit_set(CANDS_CTL0_(150), 0, 4,0x6);

#ifdef DRAM_LPDDR4_1000M
	//lpi_srpd_deep_mcclk_gate_wakeup_f0
	reg_bit_set(CANDS_CTL0_(142),24,4,0x6);
	//lpi_srpd_deep_mcclk_gate_wakeup_f1
	reg_bit_set(CANDS_CTL0_(144),24,4,0x6);
	//lpi_srpd_deep_mcclk_gate_wakeup_f2
	reg_bit_set(CANDS_CTL0_(146),24,4,0x6);
	//lpi_srpd_deep_mcclk_gate_wakeup_f3
	reg_bit_set(CANDS_CTL0_(148),24,4,0x6);
	//lpi_srpd_deep_mcclk_gate_wakeup_f4
	reg_bit_set(CANDS_CTL0_(150),24,4,0x6);

	//lpi_srpd_deep_wakeup_f0
	reg_bit_set(CANDS_CTL0_(142),16,4,0x8);
	//lpi_srpd_deep_wakeup_f1
	reg_bit_set(CANDS_CTL0_(144),16,4,0x8);
	//lpi_srpd_deep_wakeup_f2
	reg_bit_set(CANDS_CTL0_(146),16,4,0x8);
	//lpi_srpd_deep_wakeup_f3
	reg_bit_set(CANDS_CTL0_(148),16,4,0x8);
	//lpi_srpd_deep_wakeup_f4
	reg_bit_set(CANDS_CTL0_(150),16,4,0x8);
#endif
	//phy_lp_wakeup
	reg_bit_set(CANDS_PHY0_(1072),24,4,0x7);
	//lpi_sr_wakeup_f0
	reg_bit_set(CANDS_CTL0_(141),24,4,0x8);
	//lpi_sr_wakeup_f1
	reg_bit_set(CANDS_CTL0_(143),24,4,0x8);
	//lpi_sr_wakeup_f2
	reg_bit_set(CANDS_CTL0_(145),24,4,0x8);
	//lpi_sr_wakeup_f3
	reg_bit_set(CANDS_CTL0_(147),24,4,0x8);
	//lpi_sr_wakeup_f4
	reg_bit_set(CANDS_CTL0_(149),24,4,0x8);
	//lp_auto_sr_mc_gate_idle
	reg_bit_set(CANDS_CTL0_(155),24,8,0x4);
	//lpi_wakeup_en
	reg_bit_set(CANDS_CTL0_(151),16, 5,0xf);
	//long_count_mask
	//reg_bit_set(CANDS_CTL0_(238), 0, 5,0x18);
}
void ddr_lowpower_init()
{
       volatile uint32 i = 0;

       //set cobuf
	reg_bit_set(AXI_AW_COBUF_EN,0,2,0x3);
       //REG32(PMU_APB_DDR0_CHN_SLEEP_CTRL0) = 0x7ff;
	if(islp3)
	{
		//light_sleep_ddr0_data_ret_en
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,21,1,1);
		//pub0_mem_reset_ret
		reg_bit_set(0xE42c0098,0,1,0);
		//PWR_SEREFRESH_EXIT
		reg_bit_set(CANDS_CTL0_(102), 16, 1, 0);
		//PWR_SEREFRESH_EXIT_CS
		reg_bit_set(CANDS_CTL0_(170), 0, 2, 3);
	}else
	{
		//light_sleep_ddr0_data_ret_en
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,21,1,0);
		//pub0_mem_reset_ret
		reg_bit_set(0xE42c0098,0,1,1);
		//PWR_SEREFRESH_EXIT
		reg_bit_set(CANDS_CTL0_(102), 16, 1, 1);
		//PWR_SEREFRESH_EXIT_CS
		reg_bit_set(CANDS_CTL0_(170), 0, 2, 0);
	}
	//light sleep wait cnt to close 1x clock
	REG32(0xc00180bc)=0x01800000;
	//enable auto light sleep
	reg_bit_set(PMU_APB_PUB0_SYS_SLEEP_CTRL,4,1,1);
        //disable 2xen
	//reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,16,1,0);
 	//phy_set_dfi_input_0
	reg_bit_set(CANDS_PHY0_(1051),10,1,1);
 	 //pcpcs_pd_en
 	reg_bit_set(CANDS_CTL0_(162), 8, 1, 0);
	//lp_auto_entry_en
 	reg_bit_set(CANDS_CTL0_(153),24,4,0x4);
	//lp_auto_exit_en
 	reg_bit_set(CANDS_CTL0_(154), 0,4,0x4);
	//lp_auto_mem_gate_en
	reg_bit_set(CANDS_CTL0_(154),8,2,0x3);
	//axi port auto-gating enable
	reg_bit_set(PMU_APB_DDR0_CHN_SLEEP_CTRL,1,6,0x3f); 
	//pub0_chnx_lp_ctrl
      for(i = 0; i < 6; i++ )
               __raw_writel(PUB0_APB_PUB_CHN0_LP_CTRL + i*4, 0x31);
}


void prepare_reinit(void)
{
	REG32(DDR0_ACC_RDY) |= (0x1 << 0);

	#ifdef PUB_FORCE_ON
	reg_bit_set(PMU_APB_PD_PUB0_SYS_CFG, 24, 2, 0);
	#else
	reg_bit_set(PMU_APB_PD_PUB0_SYS_CFG, 24, 2, 1);
	#endif
}

//****************************************Device *******************************************************:
typedef struct SECTION_INFO
{
	uint32 type;	//reserved
	uint32 start_addr_h;
	uint32 start_addr_l;
	uint32 end_addr_h;
	uint32 end_addr_l;
}SECTION_INFO_T;

typedef struct DDR_INFO
{
	uint32 section_num;
	SECTION_INFO_T sec_info[MAX_SECTION_NUM];
}DDR_INFO_T;

DDR_INFO_T * ddr_info_s;

void ddr_info_init(void)
{

	ddr_info_s = (DDR_INFO_T *)(DDR_SIZE_TO_UBOOT);

	return;
}


void cands_ctl_addrmap_set(DRAM_TYPE_E ddr_type)
{

	volatile uint32 bank_diff = 0;
	volatile uint32 row_diff = 0;
	volatile uint32 col_diff = 0;
	volatile uint32 col_remap_en = 0;
	volatile uint32 sec_num = 0;

	if(islp3)
	{
		switch(ddr_type)
		{
			case DRAM_LPDDR3_1CS_4G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x1fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x1fc00000;
				bist_base_addr[2] = 0x1fd00000;
				break;
			case DRAM_LPDDR3_2CS_8G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x3fc00000;
				bist_base_addr[2] = 0x3fd00000;
			    	break;

            		case DRAM_LPDDR3_1CS_6G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x2fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x2fc00000;
				bist_base_addr[2] = 0x2fd00000;
				break;
            		case DRAM_LPDDR3_2CS_12G_X32:
				row_diff = 1; col_diff = 2; sec_num = 2;
				ddr_info_s->section_num = 2;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x2fffffff;

				ddr_info_s->sec_info[1].start_addr_h = 0;
				ddr_info_s->sec_info[1].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[1].end_addr_h = 0;
				ddr_info_s->sec_info[1].end_addr_l = 0x6fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x6fc00000;
				bist_base_addr[2] = 0x6fd00000;
				break;
			case DRAM_LPDDR3_1CS_8G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x3fc00000;
				bist_base_addr[2] = 0x3fd00000;
				break;
            		case DRAM_LPDDR3_2CS_16G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x7fc00000;
				bist_base_addr[2] = 0x7fd00000;
			    	break;

			case DRAM_LPDDR3_1CS_12G_X32:
				row_diff = 1; col_diff = 1; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x5fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x5fc00000;
				bist_base_addr[2] = 0x5fd00000;
				break;
            		case DRAM_LPDDR3_2CS_24G_X32:
				row_diff = 1; col_diff = 1; sec_num = 3;
				ddr_info_s->section_num = 3;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x5fffffff;

				ddr_info_s->sec_info[1].start_addr_h = 0;
				ddr_info_s->sec_info[1].start_addr_l = 0x80000000;
				ddr_info_s->sec_info[1].end_addr_h = 0;
				ddr_info_s->sec_info[1].end_addr_l = 0xbfffffff;

				ddr_info_s->sec_info[2].start_addr_h = 1;
				ddr_info_s->sec_info[2].start_addr_l = 0x00000000;
				ddr_info_s->sec_info[2].end_addr_h = 1;
				ddr_info_s->sec_info[2].end_addr_l = 0x1fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0xdfc00000;
				bist_base_addr[2] = 0xdfd00000;
				break;
			case DRAM_LPDDR3_1CS_16G_X32:
				row_diff = 1; col_diff = 1; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x7fc00000;
				bist_base_addr[2] = 0x7fd00000;
				break;
            		case DRAM_LPDDR3_2CS_32G_X32:
				row_diff = 1; col_diff = 1; sec_num = 2;
				ddr_info_s->section_num = 2;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0xbfffffff;

				ddr_info_s->sec_info[1].start_addr_h = 1;
				ddr_info_s->sec_info[1].start_addr_l = 0x00000000;
				ddr_info_s->sec_info[1].end_addr_h = 1;
				ddr_info_s->sec_info[1].end_addr_l = 0x3fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0xffc00000;
				bist_base_addr[2] = 0xffd00000;
				break;
			case DRAM_LPDDR3_2CS_24G_X32_X16X3:
				row_diff = 1; col_diff = 1; col_remap_en = 1; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0xbfafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0xbfc00000;
				bist_base_addr[2] = 0xbfd00000;
				break;

			case DRAM_LPDDR3_2CS_24G_X32_X16X4:
				row_diff = 1; col_diff = 1; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0xbfafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0xbfc00000;
				bist_base_addr[2] = 0xbfd00000;
			   	break;

			case DRAM_LPDDR3_1CS_8G_X16X2:
				row_diff = 2; col_diff = 1; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x3fc00000;
				bist_base_addr[2] = 0x3fd00000;
				break;
			case DRAM_LPDDR3_2CS_16G_X32_X16X4:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x7fc00000;
				bist_base_addr[2] = 0x7fd00000;
                		break;
			case DRAM_LPDDR3_2CS_32G_X32_X16X4:
				row_diff = 1; col_diff = 1; sec_num = 2;
				ddr_info_s->section_num = 2;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0xbfffffff;

				ddr_info_s->sec_info[1].start_addr_h = 1;
				ddr_info_s->sec_info[1].start_addr_l = 0x00000000;
				ddr_info_s->sec_info[1].end_addr_h = 1;
				ddr_info_s->sec_info[1].end_addr_l = 0x3fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0xffc00000;
				bist_base_addr[2] = 0xffd00000;
				break;
			default:   while(1); //invalid density
		}
	}
	else		//lpddr4
	{
		switch(ddr_type)
		{
	   		case DRAM_LPDDR4_1CS_4G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x1fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x1fc00000;
				bist_base_addr[2] = 0x1fd00000;
				break;
		  	case DRAM_LPDDR4_2CS_8G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x3fc00000;
				bist_base_addr[2] = 0x3fd00000;
				break;

			case DRAM_LPDDR4_1CS_6G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x2fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x2fc00000;
				bist_base_addr[2] = 0x2fd00000;
				break;
			case DRAM_LPDDR4_2CS_12G_X32:
				row_diff = 1; col_diff = 2; sec_num = 2;
				ddr_info_s->section_num = 2;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x2fffffff;

				ddr_info_s->sec_info[1].start_addr_h = 0;
				ddr_info_s->sec_info[1].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[1].end_addr_h = 0;
				ddr_info_s->sec_info[1].end_addr_l = 0x6fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x6fc00000;
				bist_base_addr[2] = 0x6fd00000;
				break;
			case DRAM_LPDDR4_1CS_8G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x3fc00000;
				bist_base_addr[2] = 0x3fd00000;
				break;
			case DRAM_LPDDR4_2CS_16G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x7fc00000;
				bist_base_addr[2] = 0x7fd00000;
				break;

			case DRAM_LPDDR4_2CS_16G_X8:
				row_diff = 0; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x7fc00000;
				bist_base_addr[2] = 0x7fd00000;
				break;

			case DRAM_LPDDR4_1CS_12G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x5fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x5fc00000;
				bist_base_addr[2] = 0x5fd00000;
				break;
			case DRAM_LPDDR4_2CS_24G_X32:
				row_diff = 1; col_diff = 2; sec_num = 3;
				ddr_info_s->section_num = 3;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x5fffffff;

				ddr_info_s->sec_info[1].start_addr_h = 0;
				ddr_info_s->sec_info[1].start_addr_l = 0x80000000;
				ddr_info_s->sec_info[1].end_addr_h = 0;
				ddr_info_s->sec_info[1].end_addr_l = 0xbfffffff;

				ddr_info_s->sec_info[2].start_addr_h = 1;
				ddr_info_s->sec_info[2].start_addr_l = 0x00000000;
				ddr_info_s->sec_info[2].end_addr_h = 1;
				ddr_info_s->sec_info[2].end_addr_l = 0x1fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0xdfc00000;
				bist_base_addr[2] = 0xdfd00000;
				break;
			case DRAM_LPDDR4_1CS_6G_X16:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x2fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x2fc00000;
				bist_base_addr[2] = 0x2fd00000;
				break;
			case DRAM_LPDDR4_1CS_16G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0x7fc00000;
				bist_base_addr[2] = 0x7fd00000;
				break;
			case DRAM_LPDDR4_2CS_32G_X32:
				row_diff = 0; col_diff = 2; sec_num = 2;
				ddr_info_s->section_num = 2;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0xbfffffff;

				ddr_info_s->sec_info[1].start_addr_h = 1;
				ddr_info_s->sec_info[1].start_addr_l = 0x00000000;
				ddr_info_s->sec_info[1].end_addr_h = 1;
				ddr_info_s->sec_info[1].end_addr_l = 0x3fafffff;
				bist_base_addr[0] = 0x700000;
				bist_base_addr[1] = 0xffc00000;
				bist_base_addr[2] = 0xffd00000;
				break;
			default: while(1); //invalid density
		}
	}

	reg_bit_set(CANDS_CTL0_(279),16,2,bank_diff);
	reg_bit_set(CANDS_CTL0_(279),24,3,row_diff);
	reg_bit_set(CANDS_CTL0_(280),0,4,col_diff);
	reg_bit_set(CANDS_CTL0_(176),29,2,col_remap_en);

}

void cands_pi_addrmap_set(DRAM_TYPE_E ddr_type) ///  ????????
{
	volatile uint32 bank_diff = 0;
	volatile uint32 row_diff = 0;
	volatile uint32 col_diff = 0;

	volatile uint32 i = 0;


	if(islp3)
	{
		switch(ddr_type)
		{
			case DRAM_LPDDR3_1CS_4G_X32:
			case DRAM_LPDDR3_2CS_8G_X32:
				row_diff = 2; col_diff = 2;break;
			case DRAM_LPDDR3_1CS_6G_X32:
            		case DRAM_LPDDR3_2CS_12G_X32:
			case DRAM_LPDDR3_1CS_8G_X32:
			case DRAM_LPDDR3_2CS_16G_X32:
				row_diff = 1; col_diff = 2;break;
			case DRAM_LPDDR3_1CS_12G_X32:
            		case DRAM_LPDDR3_2CS_24G_X32:
			case DRAM_LPDDR3_1CS_16G_X32:
            		case DRAM_LPDDR3_2CS_32G_X32:
			case DRAM_LPDDR3_2CS_24G_X32_X16X3:
				row_diff = 1; col_diff = 1;
				break;
			case DRAM_LPDDR3_2CS_24G_X32_X16X4:
				row_diff = 1; col_diff = 1;
			   	break;
            		case DRAM_LPDDR3_1CS_8G_X16X2:
			case DRAM_LPDDR3_2CS_16G_X32_X16X4:
				row_diff = 2; col_diff = 2;break;
			case DRAM_LPDDR3_2CS_32G_X32_X16X4:
				row_diff = 1; col_diff = 1;break;
			default:   while(1); //invalid density
		}
	}
	else		//lpddr4
	{
		switch(ddr_type)
		{
			case DRAM_LPDDR4_1CS_4G_X32:
			case DRAM_LPDDR4_2CS_8G_X32:
			row_diff = 2; col_diff = 2;break;
			case DRAM_LPDDR4_1CS_6G_X32:
			case DRAM_LPDDR4_2CS_12G_X32:
			row_diff = 1; col_diff = 2;break;
			case DRAM_LPDDR4_1CS_8G_X32:
			case DRAM_LPDDR4_2CS_16G_X32:
			row_diff = 1; col_diff = 2;break;
			case DRAM_LPDDR4_1CS_12G_X32:
			case DRAM_LPDDR4_2CS_24G_X32:
			case DRAM_LPDDR4_1CS_6G_X16:
			case DRAM_LPDDR4_2CS_16G_X8:
			row_diff = 0; col_diff = 2;break;
			case DRAM_LPDDR4_1CS_16G_X32:
			case DRAM_LPDDR4_2CS_32G_X32:
			row_diff = 0; col_diff = 2;break;
			default: while(1); //invalid density
		}
	}

	reg_bit_set(CANDS_PI0_(187),8,2,bank_diff);
	reg_bit_set(CANDS_PI0_(187),16,3,row_diff);
	reg_bit_set(CANDS_PI0_(248), 0,4,col_diff);

#ifdef DRAM_LPDDR4_1000M
	REG32(CANDS_CTL0_(104)) = 0x000;//DFS_ZQ_EN
#endif
}
//****************************************DDR LowPower *******************************************************:





//*****************************************DDR DFS******************************************************:
#ifdef DFS_EN
void switch_to_dfs_mode(void)
{
	uint32 clk_sel_current,clk_dmc0_sel,clk_dmc0_2x_div,clk_dmc0_1x_div,pub_dfs_sw_ratio;
	clk_sel_current=(REG32(AON_APB_CGM_CFG)>>8)&0x7f;
	clk_dmc0_sel=clk_sel_current&0x3;
	clk_dmc0_2x_div=(clk_sel_current>>3)&0xf;
	clk_dmc0_1x_div=(clk_sel_current>>2)&0x1;
	pub_dfs_sw_ratio=(clk_dmc0_sel<<0) | (clk_dmc0_1x_div<<2) | (clk_dmc0_2x_div<<3);


	//pwrup_srefresh_exit
	reg_bit_set(CANDS_CTL0_(102),16,1,0x1);

	//"pub0_dfs_sw_switch_period" is used in "u_pub_dfs_sw_ctrl",
    //it is used to control the time between dfs_fc_req and dfs_fc_ack
	reg_bit_set(PUB0_SOFT_DFS_CTRL,23,8,0x30);
	//emc_ckg_sel_delay gurantee dfs_clk_gate.dmc_2x_div_hw's setup time is enough
	reg_bit_set(PUB0_SOFT_DFS_CTRL,20,3,0x0);
    //set pub0_dfs_switch_wait_time to 0x30. should be enough to settle
    //it is used in "u_pub_dfs_clk_gate" to gate clock off during clock switch transitional period
	reg_bit_set(AON_APB_PUB_FC_CTRL,0,8,0x30);

    //set pub0_dmc_2x_cgm_sel / dmc_1x_cgm_sel to 0x1. so PUB clock 1x/2x be controlled by DFS logic
    //during DFS
	//__raw_writel(AON_APB_PUB_FC_CTRL,0x3<<8);
	reg_bit_set(AON_APB_PUB_FC_CTRL,8,2,0x3);
    //XH: to avoid PUB input clock shutdown for several cycles, must use software sequence
    //to avoid transtional state on "u_pub_dfs_clk_gate.dmc_clk_sel_o[1:0]"
    //step1: set pub_dfs_clk_gate's input "emc_ckg_sel_default[6:0]"
	reg_bit_set(AON_APB_EMC_CKG_SEL,0,7,pub_dfs_sw_ratio);

    //step2: load it using emc0_ckg_sel_load
	//__raw_writel(AON_APB_CGM_CLK_TOP_REG1_SET,0x1<<19);
	reg_bit_set(AON_APB_CGM_CLK_TOP_REG1_SET,19, 1, 1);

    //step3.1: set "pub_dfs_sw_ratio_default" so "pub_dfs_top_ctrl.sw_emc_ckg_sel[6:0]" have
    //the same value as software value "clk_dmc0_sel_sw[1:0]"
	reg_bit_set(PUB0_SOFT_DFS_CTRL,13,7,pub_dfs_sw_ratio);
	//step3.2: set dfs_soft_mode to 1. to enable non-pure soft mode. it's default value is 1
    //should be unnecessary to config it again
	//__raw_writel(PUB0_LP_GEN_CTRL_SET,0x1<<6);
	reg_bit_set(PUB0_LP_GEN_CTRL_SET, 6, 1, 1);


    //step4: set "clk_dmc0_sel_hw_en" to 0x1, in turn set "u_pub_dfs_clk_gate.clk_dmc_sel_hw_en" to 1
    //to make PUB clock be controlled by HW
	//__raw_writel(AON_APB_CGM_CFG_SET,0x1<<7);
	reg_bit_set(AON_APB_CGM_CFG_SET, 7, 1, 1);

#ifdef DRAM_LPDDR4_1000M
	REG32(CANDS_CTL0_(104)) = 0x000;//DFS_ZQ_EN to reduce latency approximate 3us.
#endif
}

void dfs_go(uint32 fn)
{
	uint32 ratio;
	uint32 scan_ratio;
	volatile uint32 i =0;
	ratio=((freq_info[fn]>>16)&0x7f);
	scan_ratio=0x0;

	reg_bit_set(CANDS_CTL0_(151),16,4,0x0);//LPI_WAKEUP_EN, default is 0xf. but before DFS, this parameter must be set to 0 to prevent PHY die in LP state exit
	reg_bit_set(PUB0_SOFT_DFS_CTRL,0,1,0x1);//pub_dfs_sw_enable
	reg_bit_set(PUB0_SOFT_DFS_CTRL,1,1,0x0);//pub_dfs_sw_req
	reg_bit_set(PUB0_SOFT_DFS_CTRL,4,2,fn);//pub_dfs_sw_freq_sel
	reg_bit_set(PUB0_SOFT_DFS_CTRL,6,7,ratio);//pub_dfs_sw_ratio
	reg_bit_set(PUB0_SOFT_DFS_CTRL,20,3,0x1);//emc_ckg_sel_delay
	reg_bit_set(PUB0_SOFT_DFS_CTRL,23,8,0x30);//pub_dfs_sw_switch_period
	reg_bit_set(PUB0_SOFT_DFS_CTRL,1,1,0x1);//pub_dfs_sw_req
	//__raw_writel(PUB0_SOFT_DFS_CTRL_SET,0x1<<1);//pub_dfs_sw_req

	while(((REG32(PUB0_SOFT_DFS_CTRL)&0x8) != 0x00)||
			((REG32(PUB0_SOFT_DFS_CTRL)&0x4)  != 0x04))
	{
		i++;
		//wait_us(10);
		if(i==1000)
		{
		}

	}
	reg_bit_set(PUB0_SOFT_DFS_CTRL,1,1,0x0);//pub_dfs_sw_req
    reg_bit_set(CANDS_CTL0_(151),16,4,0xf);//LPI_WAKEUP_EN, default is 0xf. after DFS, this parameter can be set to 0xf to enalbe PHY sleep state
}

#endif


//*************************Bist**************************************************************************:
#ifdef BIST_EN
uint32 user_mode_pattern[] = {
				0xFFFFFFFF,
				0x00000000,
				0xFFFFFFFF,
				0x00000000,
				0x00000000,
				0xFFFFFFFF,
				0x00000000,
				0xFFFFFFFF,
				0x00000000,
				0x00000000,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0x00000000,
				0x00000000,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0x00000000,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF,
				0xFFFFFFFF};

uint32 sipi_mode_pattern[] = {
			      0x444444b0,
                              0xbbbb4044,
                              0x0ff0bbbb,
                              0x0cc0aa00,
                              0xff000f0f,
                              0x0000aa00,
                              0x00000000,
                              0x00000000};

uint32 lfsr_mode_pattern[] = {
				  0x12345678,
	                      0x89abcdef,
	                      0x8abce529,
	                      0xfbed20ec};

void bist_en()
{
	//enable pub0 CA53 port bist module
	REG32(BIST_PORT_ADDR)	= 0x2A;
}

void bist_dis()
{
	//enable pub0 CA53 port bist module
	REG32(BIST_PORT_ADDR)	= 0;
}

void bist_clear_reset(uint32 bist_num)
{
	volatile uint32 val = 0;
	volatile uint32 offset = bist_num * 0x4000 ;
	//set bist clear/set bist start
	reg_bit_set(BIST_BASE_ADDR+ offset,2,1,0x0);
}

void bist_clear(uint32 bist_num)
{
	volatile uint32 val = 0;
	volatile uint32 offset = bist_num * 0x4000 ;

	//set bist clear/set bist start
	val  = REG32(BIST_BASE_ADDR+ offset);
	val |= 0x4;
	val &= (~0x2);
	REG32(BIST_BASE_ADDR+ offset) = val;
}

void bist_trigger(uint32 bist_num)
{
	volatile uint32 val = 0;
	volatile uint32 offset = bist_num * 0x4000 ;

	//trigger bist
	val  = REG32(BIST_BASE_ADDR+ offset);
	val |= 0x2;
	REG32(BIST_BASE_ADDR+ offset) = val;
}

void bist_wait_done(uint32 bist_num)
{
	volatile uint32 offset = bist_num * 0x4000 ;

	//wait bist done
	while((REG32(BIST_BASE_ADDR+0xB0+ offset)&0X2) != 0X2);
}

uint32 get_bist_result(uint32 bist_num)
{
	volatile uint32 val = 0;
	volatile uint32 offset = bist_num * 0x4000 ;

	//wait bist done
	while((REG32(BIST_BASE_ADDR+0xB0+ offset)&0X2) != 0X2);

	if( (REG32(BIST_BASE_ADDR+0xB0+ offset)&0X1) == 0x0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void sipi_bit_pat_sel(uint32 bist_num,uint32 pat_num)
{
	volatile uint32 i =0;
	volatile uint32 offset = bist_num*0x400;
	switch(pat_num)
	{
		case 0:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x00010001;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x00010001;
			break;
		case 1:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x00040004;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x00040004;
			break;
		case 2:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x00100010;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x00100010;
			break;
		case 3:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x00400040;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x00400040;
			break;
		case 4:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x01000100;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x01000100;
			break;
		case 5:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x04000400;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x04000400;
			break;
		case 6:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x10001000;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x10001000;
			break;
		case 7:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x40004000;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x40004000;
			break;
		case 8:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x22222222;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x22222222;
			break;
	}
}


void bist_set(uint32 bist_num,uint32 write_or_read,uint32 bist_patt, uint32 bist_mode,uint32 bist_src,uint32 bist_len)
{
	volatile uint32 i = 0;
	volatile uint32 val = 0;
	volatile uint32 offset = bist_num * 0x4000 ;

	REG32(BIST_BASE_ADDR+0x00+offset) = 4;
	for(i = 0; i < 3000; i++);
	REG32(BIST_BASE_ADDR+0x00+offset) = 0;

	//bist enable
	val = 0;
  	val |=1;
	//set bist mode
  	val |= (write_or_read<<3); //0:write  1:read  2:all write, then read compare  3:one write, then read compare
  	//set bist pattern mode
	val |= (bist_patt<<5); //0:user mode  1:sipi mode  2:lfsr
  	//set burst length
  	val |= (15<<7); //0:(n+1)*2  3:(n+1)*4  7:(n+1)*8  15:(n+1)*16  others:n+1
  	//set data size
  	val |= (4<<11); //0:byte  1:halfword  2:word  3:two word 4:four word
  	val |= (bist_mode<<14); //0:normal bist mode  1:bist will not stop util bist_start is low
  	val |= (0<<15); //the delay clk cycle between the two axi command
  	val |= (3<<24); //bist write/read outstanding enable

  	REG32(BIST_BASE_ADDR+0x00+offset) = val;

  	//set trans num
  	REG32(BIST_BASE_ADDR+0x04+offset) = (bist_len>>8) -1;

  	//set start address
  	REG32(BIST_BASE_ADDR+0x08+offset) = bist_src;
	if(bist_patt==USER_PATT)
	{
		//set bist data pattern
		for(i = 0; i < 32; i++)
		{
			REG32(BIST_BASE_ADDR+0x30 + i*4 + offset) = user_mode_pattern[i];
		}
	}
	if(bist_patt==SIPI_PATT)
	{
		//set sipi data pattern
		REG32(BIST_BASE_ADDR+0x10+offset) = sipi_mode_pattern[0];
		REG32(BIST_BASE_ADDR+0x14+offset) = sipi_mode_pattern[1];
		REG32(BIST_BASE_ADDR+0x18+offset) = sipi_mode_pattern[2];
		REG32(BIST_BASE_ADDR+0x1C+offset) = sipi_mode_pattern[3];
		REG32(BIST_BASE_ADDR+0x20+offset) = sipi_mode_pattern[4];
		REG32(BIST_BASE_ADDR+0x24+offset) = sipi_mode_pattern[5];
		sipi_bit_pat_sel(bist_num, 8);
	}
	if(bist_patt==LFSR_PATT)
	{
		REG32(BIST_BASE_ADDR+0xcc+offset)=lfsr_mode_pattern[0];
		REG32(BIST_BASE_ADDR+0xd0+offset)=lfsr_mode_pattern[1];
		REG32(BIST_BASE_ADDR+0xd4+offset)=lfsr_mode_pattern[2];
		REG32(BIST_BASE_ADDR+0xd8+offset)=lfsr_mode_pattern[3];
	}
}

void bist_test_init(uint32 write_or_read,uint32 bist_patt,uint32 bist_len,uint32 bist_base_channel0,uint32 bist_base_channel1,uint32 bist_base_channel2)
{
	bist_clear(BIST_ARM);
	bist_clear(BIST_GPU);
	bist_clear(BIST_VSP);

	bist_set(BIST_ARM,write_or_read,bist_patt,NORMAL_MODE,bist_base_channel0,bist_len);
	bist_set(BIST_GPU,write_or_read,bist_patt,NORMAL_MODE,bist_base_channel1,bist_len);
	bist_set(BIST_VSP,write_or_read,bist_patt,NORMAL_MODE,bist_base_channel2,bist_len);

}
uint32 bist_test_entry()
{
	uint32 bist_result=0x0;
	bist_en();

	bist_clear_reset(BIST_ARM);
	bist_clear_reset(BIST_GPU);
	bist_clear_reset(BIST_VSP);

	bist_trigger(BIST_ARM);
	bist_trigger(BIST_GPU);
	bist_trigger(BIST_VSP);

	bist_wait_done(BIST_ARM);
	bist_wait_done(BIST_GPU);
	bist_wait_done(BIST_VSP);

	bist_result += get_bist_result(BIST_ARM);
	bist_result += get_bist_result(BIST_GPU);
	bist_result += get_bist_result(BIST_VSP);
	if(swlvl_bist==0)
	{
		if(bist_result>0)
		{
			ddr_print("\r\n bist test is fail");
			bist_dis();
			while(1);
		}else
		{
			ddr_print("\r\n bist test is ok");
		}
	}

	bist_clear(BIST_ARM);
	bist_clear(BIST_GPU);
	bist_clear(BIST_VSP);

	bist_dis();
	return bist_result;
}
uint32 bist_result_out=0;
void bist_func(uint32 chn_num)
{
	uint32 bist_timeout=0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	REG32(0xc0018028+chn_offset) =0x2a;
	REG32(0xc00d0000+chn_offset) =0x30021b1;
	REG32(0xc00d0004+chn_offset) =0x3fFf;
	REG32(0xc00d0008+chn_offset) =0x14a00000;
	REG32(0xc00d000c+chn_offset) =0x0;
	REG32(0xc00d0010+chn_offset) =0xa55aaa55;
	REG32(0xc00d0014+chn_offset) =0xffffaa55;
	REG32(0xc00d0018+chn_offset) =0x1111aa55;
	REG32(0xc00d001c+chn_offset) =0xaaaaaa55;
	REG32(0xc00d0020+chn_offset) =0x1234aa55;
	REG32(0xc00d0024+chn_offset) =0x0000aa55;
	REG32(0xc00d0028+chn_offset) =0x01234567;
	REG32(0xc00d002c+chn_offset) =0x89abcdef;

	REG32(0xc00d0008+chn_offset) =0x14a00000;
	REG32(0xc00d0004+chn_offset) =0x3ffFff;
	REG32(0xc00d0000+chn_offset) =0x30021b5;
	REG32(0xc00d0000+chn_offset) =0x30021b3;

	while((REG32(0xc00d00b0+chn_offset) & 0x2) != 0x2)
	{
		bist_timeout++;
		if(bist_timeout>=500000000)
		{
			REG32(0xc0018028+chn_offset) =0x0;
			while(1);
		}
	}

	if((REG32(0xc00d00b0+chn_offset) & 0x1) == 0x1)
	{
		bist_result_out=1;
		REG32(0xc0018028+chn_offset) =0x0;
		ddr_print("\r\n bist failed, ddr unstable......");
		while(1);
	}

	REG32(0xc0018028+chn_offset) =0x0;

}

void bist_func_all_random(uint32 chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 bist_base_offset;
	uint32 i;
	uint32 bist_adr_base;
	uint32 seed[4];
	uint32 pass_num;

	pass_num = 0;

	REG32(0xc0018028+chn_offset) =0x2a;

	seed[0] = 0x11223344;
	seed[1] = 0x55667788;
	seed[2] = 0x99aabbcc;
	seed[3] = 0xddeeff11;

	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;

		REG32(0xc00d0010+chn_offset+bist_base_offset) =0x0ff0c3a5;
		REG32(0xc00d0014+chn_offset+bist_base_offset) =0xffffaa55;
		REG32(0xc00d0018+chn_offset+bist_base_offset) =0x1111aa55;
		REG32(0xc00d001c+chn_offset+bist_base_offset) =0xaaaaaa55;
		REG32(0xc00d0020+chn_offset+bist_base_offset) =0x1234aa55;
		REG32(0xc00d0024+chn_offset+bist_base_offset) =0x0000aa55;
		REG32(0xc00d0028+chn_offset+bist_base_offset) =0x00000000;
		REG32(0xc00d002c+chn_offset+bist_base_offset) =0x00000000;
	}

while(1)
{
	for(i=0;i<3;i++)
	{
		if(i==0)
		{
			bist_adr_base = 0x00000000;
		}
		else
		{
			bist_adr_base = i*0x20000000;
		}
		bist_base_offset = i*0x4000;

		if(i==0)
		{
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021d1;	//0x30021d1
		}
		else
		{
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021d9;	//0x30021d9
		}
		//this lenth about 1min 405 times
		REG32(0xc00d0004+chn_offset+bist_base_offset) =0x3fffff;
		REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
		REG32(0xc00d000c+chn_offset+bist_base_offset) =0x0;

		REG32(0xc00d00cc+chn_offset+bist_base_offset) =seed[0];
		REG32(0xc00d00d0+chn_offset+bist_base_offset) =seed[1];
		REG32(0xc00d00d4+chn_offset+bist_base_offset) =seed[2];
		REG32(0xc00d00d8+chn_offset+bist_base_offset) =seed[3];

		seed[0] = ~seed[0];
		seed[1] = ~seed[1];
		seed[2] = ~seed[2];
		seed[3] = ~seed[3];

		REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
		REG32(0xc00d0004+chn_offset+bist_base_offset) =0x3fffff;
		if(i==0)
		{
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021d5;	//0x30021d5
		}
		else
		{
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021dd;	//0x30021dd
		}
	}

	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;
		if(i==0)
		{
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021d3;	//0x30021d3
		}
		else
		{
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021db;	//0x30021db
		}
	}

	while((REG32(0xc00d00b0+chn_offset) & 0x3) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x4000) & 0x3) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x8000) & 0x3) != 0x2);
	pass_num += 1;
	ddr_print("\r\nddr bist pass num = ");
	ddr_print_hex_u32(pass_num);
	ddr_print("\r\n");
}

	REG32(0xc0018028+chn_offset) =0x0;
}
uint32 bist_fail_num[5]={0};
void ddr_test(uint32 freq_num)
{
	volatile uint32 i=0;
	uint32 test_num=0;
	uint32 bist_len;
//	bist_func(0);

	#ifdef WATCH_DOG_REBOOT_TEST
	bist_len = 0x10000000;
	#else
	bist_len = 0x2000000;
	#endif
	bist_test_init(BIST_ALLWRC,SIPI_PATT,bist_len,0x0,0x30000000,0x60000000);
	for(i=0;i<10;i++)
	{
		bist_fail_num[freq_num]+=bist_test_entry();
		test_num++;
		ddr_print("\r\n");
		ddr_print_hex_u32(test_num);
	}
}

#endif

//********************************************DDR Power Test***************************************************:
void vref_cfg(uint32 fn, uint32 phy_vref_val)
{
    reg_bit_set(CANDS_PHY0_(1024), 8, 3, fn);
    //vref setting
    reg_bit_set(CANDS_PHY0_(1048), 8, 14, phy_vref_val);
    reg_bit_set(CANDS_PHY0_(1049), 16, 14, phy_vref_val);
    reg_bit_set(CANDS_PHY0_(1049), 0, 14, phy_vref_val);
    reg_bit_set(CANDS_PHY0_(1050), 16, 14, phy_vref_val);
    reg_bit_set(CANDS_PHY0_(1050), 0, 14, phy_vref_val);
}
void vref_cfg_lp3()
{
    uint32 i=0;
    uint32 phy_vref_val;
    if((islp3)&&(chip_id > 1))
    {
        phy_vref_val=0x517;
	for(i=0;i<4;i++)
	{
            vref_cfg(i, phy_vref_val);
	}
    }
}

void misc_reg_cfg_change()
{
	volatile uint32 i=0;
	uint32 slice_num=0;
	uint32 freq_num=0;
	uint32 phy_vref_val=0x0;
	if(islp3)
	{
		for(freq_num=0;freq_num<4;freq_num++)
		{
			reg_bit_set(CANDS_PHY0_(1024),8,3,freq_num);
			for(slice_num=0;slice_num<4;slice_num++)
			{
				reg_bit_set(CANDS_PHY0_(96)+slice_num*0x200,16,4,freq_num+4);		//rptr_update
			}
		}

		reg_bit_set(CANDS_PHY0_(1024),8,3,0x1);
		for(i=0;i<4;i++)
		{
			reg_bit_set(CANDS_PHY0_(89)+i*0x200,0,1,0x1);
			reg_bit_set(CANDS_PHY0_(88)+i*0x200,0,10,0x180);
		}
		reg_bit_set(CANDS_PHY0_(1024),8,3,0x2);
		for(i=0;i<4;i++)
		{
			reg_bit_set(CANDS_PHY0_(89)+i*0x200,0,1,0x1);
			reg_bit_set(CANDS_PHY0_(88)+i*0x200,0,10,0x180);
			//reg_bit_set(CANDS_PHY0_(96)+i*0x200,16,4,5);	//phy_rptr_update
			reg_bit_set(CANDS_PHY0_(93)+i*0x200,16,1,0);	//phy_per_cs_training_en disable
		}
		reg_bit_set(CANDS_PHY0_(1024),8,3,0x3);
		for(i=0;i<4;i++)
		{
			reg_bit_set(CANDS_PHY0_(89)+i*0x200,0,1,0x1);
			reg_bit_set(CANDS_PHY0_(88)+i*0x200,0,10,0x180);
			reg_bit_set(CANDS_PHY0_(96)+i*0x200,16,4,7);	//phy_rptr_update
			reg_bit_set(CANDS_PHY0_(93)+i*0x200,16,1,0);	//phy_per_cs_training_en disable
		}
		(chip_id > 1)?(phy_vref_val=0x50B):(phy_vref_val=0x535);
		if((!((ddr_mode>>4)&0x1))&&((ddr_mode>>6)&0x1))
		{
			phy_vref_val &= ~(0x3f<<0);
			phy_vref_val |= (((ddr_mode>>16)&0x3f)<<0);
		}
		for(i=0;i<4;i++)
		{
			reg_bit_set(CANDS_PHY0_(1024),8,3,i);
			//vref setting
			reg_bit_set(CANDS_PHY0_(1048), 8, 14, phy_vref_val);
			reg_bit_set(CANDS_PHY0_(1049), 16, 14, phy_vref_val);
			reg_bit_set(CANDS_PHY0_(1049), 0, 14, phy_vref_val);
			reg_bit_set(CANDS_PHY0_(1050), 16, 14, phy_vref_val);
			reg_bit_set(CANDS_PHY0_(1050), 0, 14, phy_vref_val);
		}

		reg_bit_set(CANDS_PHY0_(1024),8,3,0x0);
		//phy_pll_ctrl0
		reg_bit_set(CANDS_PHY0_(1040),0,27,0x00e40160);		//vcodiv 2 for 230M
		//phy_top_pll_ctrl0
		reg_bit_set(CANDS_PHY0_(1044),0,27,0x00e40160);		//vcodiv 2 for 230M

		reg_bit_set(CANDS_PHY0_(1024),8,3,0x2);
		//phy_pll_ctrl0
		reg_bit_set(CANDS_PHY0_(1040),0,27,0x02640160);		//vcodiv 1 for 613M
		//phy_top_pll_ctrl0
		reg_bit_set(CANDS_PHY0_(1044),0,27,0x02640160);		//vcodiv 1 for 613M
		//mr11---pi
		reg_bit_set(CANDS_PI0_(157),0,8,0x0);
		reg_bit_set(CANDS_PI0_(164),24,8,0x0);
		reg_bit_set(CANDS_PI0_(172),16,8,0x0);
		reg_bit_set(CANDS_PI0_(180),8,8,0x0);
		reg_bit_set(CANDS_PI0_(158),16,8,0x0);
		reg_bit_set(CANDS_PI0_(166),8,8,0x0);
		reg_bit_set(CANDS_PI0_(174),0,8,0x0);
		reg_bit_set(CANDS_PI0_(181),24,8,0x0);
		reg_bit_set(CANDS_PI0_(160),0,8,0x0);
		reg_bit_set(CANDS_PI0_(167),24,8,0x0);
		reg_bit_set(CANDS_PI0_(175),16,8,0x0);
		reg_bit_set(CANDS_PI0_(183),8,8,0x0);
		reg_bit_set(CANDS_PI0_(161),16,8,0x0);
		reg_bit_set(CANDS_PI0_(169),8,8,0x0);
		reg_bit_set(CANDS_PI0_(177),0,8,0x0);
		reg_bit_set(CANDS_PI0_(184),24,8,0x0);
		reg_bit_set(CANDS_PI0_(163),0,8,0x0);
		reg_bit_set(CANDS_PI0_(170),24,8,0x0);
		reg_bit_set(CANDS_PI0_(178),16,8,0x0);
		reg_bit_set(CANDS_PI0_(186),8,8,0x0);
		//mr11 ---ctl
		reg_bit_set(CANDS_CTL0_(210),8,8,0x0);
		reg_bit_set(CANDS_CTL0_(221),24,8,0x0);
		reg_bit_set(CANDS_CTL0_(210),16,8,0x0);
		reg_bit_set(CANDS_CTL0_(222),0,8,0x0);
		reg_bit_set(CANDS_CTL0_(210),24,8,0x0);
		reg_bit_set(CANDS_CTL0_(222),8,8,0x0);
		reg_bit_set(CANDS_CTL0_(211),0,8,0x0);
		reg_bit_set(CANDS_CTL0_(222),16,8,0x0);
		reg_bit_set(CANDS_CTL0_(211),8,8,0x0);
		reg_bit_set(CANDS_CTL0_(222),24,8,0x0);
		//tinit fx
		REG32(CANDS_CTL0_(12))=0xb3af;
		REG32(CANDS_CTL0_(13))=0x00e6;
		REG32(CANDS_CTL0_(14))=0x08fc;
		REG32(CANDS_CTL0_(15))=0x002e;
		REG32(CANDS_CTL0_(16))=0x1675d;
		REG32(CANDS_CTL0_(17))=0x01cc;
		REG32(CANDS_CTL0_(18))=0x11f8;
		REG32(CANDS_CTL0_(19))=0x003e;
		REG32(CANDS_CTL0_(20))=0x1df01;
		REG32(CANDS_CTL0_(21))=0x0266;
		REG32(CANDS_CTL0_(22))=0x17f4;
		REG32(CANDS_CTL0_(23))=0x005c;
		REG32(CANDS_CTL0_(24))=0x2ceb9;
		REG32(CANDS_CTL0_(25))=0x0398;
		REG32(CANDS_CTL0_(26))=0x23f0;
		REG32(CANDS_CTL0_(27))=0x0017;
		REG32(CANDS_CTL0_(28))=0xb3af;
		REG32(CANDS_CTL0_(29))=0x00e6;
		REG32(CANDS_CTL0_(30))=0x08fc;
		#ifdef DRAM_LPDDR3_750M
		//tinit3_fx
		REG32(CANDS_CTL0_(12))=0xc3a0;
		REG32(CANDS_CTL0_(16))=0x186b0;
		REG32(CANDS_CTL0_(20))=0x24ba0;
		REG32(CANDS_CTL0_(24))=0x24b68;
		REG32(CANDS_CTL0_(28))=0xc3a0;
		//Tras_min
		reg_bit_set(CANDS_CTL0_(40),24,8,0xb);
		reg_bit_set(CANDS_CTL0_(42),16,8,0x16);
		reg_bit_set(CANDS_CTL0_(44), 8,8,0x22);
		reg_bit_set(CANDS_CTL0_(46), 0,8,0x22);
		#endif

		reg_bit_set(CANDS_PHY0_(1094),4,4,0x2);//lp3 set 0x2 pad_cal_mode
	}

//_____________________________commen config for lp3/lp4x____________________________
	//pwrup_srefresh_exit_cs
	reg_bit_set(CANDS_CTL0_(170), 0,2,0x3);
	//disable_memory_masked_write
	reg_bit_set(CANDS_CTL0_(473), 0,1,0x0);

	//ctrlupd_norm_threshold_f0
	reg_bit_set(CANDS_CTL0_(110), 0,16,0x0);
	//ctrlupd_norm_threshold_f1
	reg_bit_set(CANDS_CTL0_(112), 16,16,0x0);
	//ctrlupd_norm_threshold_f2
	reg_bit_set(CANDS_CTL0_(115), 0,16,0x0);
	//ctrlupd_norm_threshold_f3
	reg_bit_set(CANDS_CTL0_(117), 16,16,0x0);

	//enable rpull
	for(i=0;i<4;i++)
	{
		reg_bit_set(CANDS_PHY0_(1024),8,3,i);
		reg_bit_set(CANDS_PHY0_(1075),29,1,0x1); 					//rpull

		//phy_pll_ctrl1	config propcoeff
		reg_bit_set(CANDS_PHY0_(1041),0,21,0x055744);
		//phy_top_pll_ctrl1
		reg_bit_set(CANDS_PHY0_(1045),0,21,0x055744);

	}
	//no_phy_ind_train_init
	reg_bit_set(CANDS_CTL0_(32), 0,1,0x0);
	//set ctrlupd to disable
	REG32(CANDS_CTL0_(110))=0x0;
	REG32(CANDS_CTL0_(111))=0x0;
	REG32(CANDS_CTL0_(112))=0x0;
	REG32(CANDS_CTL0_(113))=0x0;
	REG32(CANDS_CTL0_(114))=0x0;
	REG32(CANDS_CTL0_(115))=0x0;
	REG32(CANDS_CTL0_(116))=0x0;
	REG32(CANDS_CTL0_(117))=0x0;
	REG32(CANDS_CTL0_(118))=0x0;
	REG32(CANDS_CTL0_(119))=0x0;
	REG32(CANDS_CTL0_(120))=0x0;
	REG32(CANDS_CTL0_(121))=0x0;
	//MR3_DATA_FX
	reg_bit_set(CANDS_CTL0_(208),24,8,DRAM_DS);
	REG32(CANDS_CTL0_(209))=(DRAM_DS<<24) | (DRAM_DS<<16) | (DRAM_DS<<8) | (DRAM_DS<<0);
	reg_bit_set(CANDS_CTL0_(220),8,24,(DRAM_DS<<16) | (DRAM_DS<<8) | (DRAM_DS<<0));
	reg_bit_set(CANDS_CTL0_(221),0,16,(DRAM_DS<<8) | (DRAM_DS<<0));
	//mr3_data_fx pi
	reg_bit_set(CANDS_PI0_(156),24,8,DRAM_DS);
	reg_bit_set(CANDS_PI0_(158),8,8,DRAM_DS);
	reg_bit_set(CANDS_PI0_(159),24,8,DRAM_DS);
	reg_bit_set(CANDS_PI0_(161),8,8,DRAM_DS);
	reg_bit_set(CANDS_PI0_(162),24,8,DRAM_DS);
	reg_bit_set(CANDS_PI0_(164),16,8,DRAM_DS);
	reg_bit_set(CANDS_PI0_(166),0,8,DRAM_DS);
	reg_bit_set(CANDS_PI0_(167),16,8,DRAM_DS);
	reg_bit_set(CANDS_PI0_(169),0,8,DRAM_DS);
	reg_bit_set(CANDS_PI0_(170),16,8,DRAM_DS);
	//on_fly_gate_adjust_en
	reg_bit_set(CANDS_PHY0_(16),16,2,0x3);
	reg_bit_set(CANDS_PHY0_(144),16,2,0x3);
	reg_bit_set(CANDS_PHY0_(272),16,2,0x3);
	reg_bit_set(CANDS_PHY0_(400),16,2,0x3);
	//per_cs_trainig_multicast_en
	reg_bit_set(CANDS_PHY0_(8),16,1,0x1);
	reg_bit_set(CANDS_PHY0_(136),16,1,0x1);
	reg_bit_set(CANDS_PHY0_(264),16,1,0x1);
	reg_bit_set(CANDS_PHY0_(392),16,1,0x1);

	//trasmax
	reg_bit_set(CANDS_CTL0_(50),0,17,0x1f89);
	reg_bit_set(CANDS_CTL0_(52),0,17,0x3274);
	reg_bit_set(CANDS_CTL0_(54),0,17,0x540c);
	reg_bit_set(CANDS_CTL0_(56),0,17,0x7e24);
	reg_bit_set(CANDS_CTL0_(58),0,17,0x1f89);

	//lpc_sr_ctrlupd_en
	reg_bit_set(CANDS_CTL0_(161),0,1,0x0);
	//rd_preamble_training_en
	reg_bit_set(CANDS_CTL0_(289),24,1,0x0);
	//srefresh_exit_no_refresh
	reg_bit_set(CANDS_CTL0_(102),24,1,0x1);
	//op mode
	for(i=0;i<4;i++)
	{
		reg_bit_set(CANDS_PHY0_(27)+i*0x200,0,2,0x2);
	}

	if(!islp3)
	{
		reg_bit_set(CANDS_PHY0_(1024),8,3,0x1);
		for(i=0;i<4;i++)
		{
			reg_bit_set(CANDS_PHY0_(89)+i*0x200,0,1,0x1);
			reg_bit_set(CANDS_PHY0_(88)+i*0x200,0,10,0x180);
		}
		reg_bit_set(CANDS_PHY0_(1024),8,3,0x2);
		for(i=0;i<4;i++)
		{
			reg_bit_set(CANDS_PHY0_(89)+i*0x200,0,1,0x1);
			reg_bit_set(CANDS_PHY0_(88)+i*0x200,0,10,0x180);
			reg_bit_set(CANDS_PHY0_(96)+i*0x200,16,4,7);	//phy_rptr_update
			reg_bit_set(CANDS_PHY0_(93)+i*0x200,16,1,0);	//phy_per_cs_training_en disable
			reg_bit_set(CANDS_PHY0_(87)+i*0x200,0,10,0x0);	//phy_rddqs_gate_slave_delay
			reg_bit_set(CANDS_PHY0_(87)+i*0x200,16,4,0x2);	//phy_rddqs_latency_adjust
		}
		reg_bit_set(CANDS_PHY0_(1024),8,3,0x3);
		for(i=0;i<4;i++)
		{
			reg_bit_set(CANDS_PHY0_(89)+i*0x200,0,1,0x1);
			reg_bit_set(CANDS_PHY0_(88)+i*0x200,0,10,0x180);
			reg_bit_set(CANDS_PHY0_(96)+i*0x200,16,4,7);	//phy_rptr_update
			reg_bit_set(CANDS_PHY0_(93)+i*0x200,16,1,0);	//phy_per_cs_training_en disable
			reg_bit_set(CANDS_PHY0_(87)+i*0x200,0,10,0x0);	//phy_rddqs_gate_slave_delay
			reg_bit_set(CANDS_PHY0_(87)+i*0x200,16,4,0x3);	//phy_rddqs_latency_adjust
		}

		reg_bit_set(CANDS_PHY0_(1024),8,3,0x0);
		//phy_pll_ctrl0
		reg_bit_set(CANDS_PHY0_(1040),7,8,0x2);		//vcodiv 2 for 213M
		//phy_top_pll_ctrl0
		reg_bit_set(CANDS_PHY0_(1044),7,8,0x2);		//vcodiv 2 for 213M

		reg_bit_set(CANDS_PHY0_(1024),8,3,0x2);
		//phy_pll_ctrl0
		reg_bit_set(CANDS_PHY0_(1040),7,8,0x1);		//vcodiv 1 for 711M
		//phy_top_pll_ctrl0
		reg_bit_set(CANDS_PHY0_(1044),7,8,0x1);		//vcodiv 1 for 711M
		//set LP4x MR11 DQ-ODT to RZQ/6=40ohm to mimic a LP4x protocol on DQ/DQS signaling
		//cs0 mr11_data
		reg_bit_set(CANDS_CTL0_(210),8,24,(LP4X_ODT_SET<<16) | (LP4X_ODT_SET<<8) | (LP4X_ODT_SET<<0));
		reg_bit_set(CANDS_CTL0_(211),0,16,(LP4X_ODT_SET<<8) | (LP4X_ODT_SET<<0));
		//cs1 mr11_data
		reg_bit_set(CANDS_CTL0_(221),24,8,LP4X_ODT_SET);
		REG32(CANDS_CTL0_(222))=(LP4X_ODT_SET<<24) | (LP4X_ODT_SET<<16) | (LP4X_ODT_SET<<8) | (LP4X_ODT_SET<<0);

		//pi cs0 mr11_data
		reg_bit_set(CANDS_PI0_(157),0,8,LP4X_ODT_SET);
		reg_bit_set(CANDS_PI0_(158),16,8,LP4X_ODT_SET);
		reg_bit_set(CANDS_PI0_(160),0,8,LP4X_ODT_SET);
		reg_bit_set(CANDS_PI0_(161),16,8,LP4X_ODT_SET);
		reg_bit_set(CANDS_PI0_(163),0,8,LP4X_ODT_SET);
		reg_bit_set(CANDS_PI0_(164),24,8,LP4X_ODT_SET);
		reg_bit_set(CANDS_PI0_(166),8,8,LP4X_ODT_SET);
		reg_bit_set(CANDS_PI0_(167),24,8,LP4X_ODT_SET);
		reg_bit_set(CANDS_PI0_(169),8,8,LP4X_ODT_SET);
		reg_bit_set(CANDS_PI0_(170),24,8,LP4X_ODT_SET);

		//mr12
		//cs0
		reg_bit_set(CANDS_PI0_(157), 8,8,VREF_CA_LP4X);
		reg_bit_set(CANDS_PI0_(158),24,8,VREF_CA_LP4X);
		reg_bit_set(CANDS_PI0_(160), 8,8,VREF_CA_LP4X);
		reg_bit_set(CANDS_PI0_(161),24,8,VREF_CA_LP4X);
		reg_bit_set(CANDS_PI0_(163), 8,8,VREF_CA_LP4X);
		//cs1
		reg_bit_set(CANDS_PI0_(165), 0,8,VREF_CA_LP4X);
		reg_bit_set(CANDS_PI0_(166),16,8,VREF_CA_LP4X);
		reg_bit_set(CANDS_PI0_(168), 0,8,VREF_CA_LP4X);
		reg_bit_set(CANDS_PI0_(169),16,8,VREF_CA_LP4X);
		reg_bit_set(CANDS_PI0_(171), 0,8,VREF_CA_LP4X);

		//mr14
		//cs0
		reg_bit_set(CANDS_PI0_(157),16,8,VREF_ODT_48OHM_LP4X);
		reg_bit_set(CANDS_PI0_(159), 0,8,VREF_ODT_48OHM_LP4X);
		reg_bit_set(CANDS_PI0_(160),16,8,VREF_ODT_48OHM_LP4X);
		reg_bit_set(CANDS_PI0_(162), 0,8,VREF_ODT_48OHM_LP4X);
		reg_bit_set(CANDS_PI0_(163),16,8,VREF_ODT_48OHM_LP4X);
		//cs1
		reg_bit_set(CANDS_PI0_(165), 8,8,VREF_ODT_48OHM_LP4X);
		reg_bit_set(CANDS_PI0_(166),24,8,VREF_ODT_48OHM_LP4X);
		reg_bit_set(CANDS_PI0_(168), 8,8,VREF_ODT_48OHM_LP4X);
		reg_bit_set(CANDS_PI0_(169),24,8,VREF_ODT_48OHM_LP4X);
		reg_bit_set(CANDS_PI0_(171), 8,8,VREF_ODT_48OHM_LP4X);

		reg_bit_set(CANDS_PHY0_(1094),4,4,0x6);//lp4 set 0x6 pad_cal_mode

		//lpc_sr_ctrlupd_en
		reg_bit_set(CANDS_CTL0_(161),0,1,0x1);

		//pi_rd_preamble_training_en
		reg_bit_set(CANDS_PI0_(108),0,1,0x0);

		//lpc_sr_ctrlupd_en
		reg_bit_set(CANDS_CTL0_(161),0,1,0x1);

		//pi_rd_preamble_training_en
		reg_bit_set(CANDS_PI0_(108),0,1,0x1);

	}

}

void cands_deskewpll_cfg()
{
	uint32 freq_num=0;
	uint32 lockcount=0;
	uint32 coeff=0;
	if(islp3)
	{
		lockcount=0x10;
	}
	//pll_lockcount cfg
	for(freq_num=2;freq_num<4;freq_num++)
	{
		reg_bit_set(CANDS_PHY0_(1024),8,3,freq_num);
		//phy_pll_ctrl0----pll_lockcount
		reg_bit_set(CANDS_PHY0_(1040),15,6,lockcount);
		//phy_top_pll_ctrl0----pll_lockcount
		reg_bit_set(CANDS_PHY0_(1044),15,6,lockcount);
		//phy_pll_ctrl1	config propcoeff
		//reg_bit_set(CANDS_PHY0_(1041),0,21,coeff);
		//phy_top_pll_ctrl1
		//reg_bit_set(CANDS_PHY0_(1045),0,21,coeff);
	}
}

void cands_26M_cal_clk_workaround()
{
	//for LP4, must do pad cal before initialization.
	if(!islp3) {
		//phy_cal_clk_select, pad calibration clk, 0/1: clk_ctrl/2  2/3/4/5/6/7: clk_ctr/4/8/16/32/64/128
		//phy_cal_clock 10~20M
		reg_bit_set(CANDS_PHY0_(1096), 8,3,3); ///500/4/8


		////phy_cal_start
		//reg_bit_set(CANDS_PHY0_(1094),16,1,1);
		//toggle PHY_DLL_RST, so as to trigger a pad calibration
		reg_bit_set(CANDS_PHY0_(1107),16,1,1); //PHY_DLL_RST_EN
		reg_bit_set(CANDS_PHY0_(1107),16,1,0); //PHY_DLL_RST_EN
		//phy_cal_result_obs_0		bit23 pad_cal_done
		while(((REG32(CANDS_PHY0_(1097))>>23) & 0x1) != 1);

		//result2 only for LP3, not need to check
		////phy_cal_result2_obs_0		bit23 pad_cal_done
		//while(((REG32(CANDS_PHY0_(1098))>>23) & 0x1) != 1);

		//umctl auto gate en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 2, 1, 0);
		//phy auto gate en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 4, 1, 0);
		//ctl & phy en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 0, 2, 0);
		//safely switch clock to 26MHz
		ddr_clk_set(26000000);
		//umctl auto gate en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 2, 1, 1);
		//phy auto gate en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 4, 1, 1);
		//ctl & phy en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 0, 2, 0);

		//don't move
		reg_bit_set(CANDS_PHY0_(1094),0,1,0x1);//initialization calibration bypassed
	}
}

void dfs_noinit_tr_en()
{
	reg_bit_set(CANDS_PI0_(1), 0,  1, 1); //pi_normal_lvl_seq
	reg_bit_set(CANDS_PI0_(1), 8,  1, 1); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(77), 8,  2, 0x2); //pi_wrlvl_noinit_en
	reg_bit_set(CANDS_PI0_(123), 8,  2, 0x2); //pi_calvl_noinit_en
	reg_bit_set(CANDS_PI0_(99), 16,  2, 0x2); //pi_rdlvl_noinit_en
	reg_bit_set(CANDS_PI0_(99), 24,  2, 0x2); //pi_rdlvl_gate_noinit_en

	#ifdef DRAM_LPDDR4
	reg_bit_set(CANDS_PI0_(155), 16,  2, 0x2); //pi_wdqlvl_noinit_en
	reg_bit_set(CANDS_PI0_(129), 24,  1, 0x1); //pi_ca_train_vref_en
	reg_bit_set(CANDS_PI0_(147), 24,  1, 0x1); //pi_wdqlvl_vref_en
	#endif

	reg_bit_set(CANDS_PI0_(214), 0,  24, 0x3ffff); //pi_init_status_clean
}


void dfs_noinit_tr_dis()
{
	reg_bit_set(CANDS_PI0_(1), 0,  1, 0); //pi_normal_lvl_seq
	reg_bit_set(CANDS_PI0_(1), 8,  1, 0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(77), 8,  2, 0); //pi_wrlvl_noinit_en
	reg_bit_set(CANDS_PI0_(123), 8,  2, 0); //pi_calvl_noinit_en
	reg_bit_set(CANDS_PI0_(99), 16,  2, 0); //pi_rdlvl_noinit_en
	reg_bit_set(CANDS_PI0_(99), 24,  2, 0); //pi_rdlvl_gate_noinit_en
	#ifdef DRAM_LPDDR4
	reg_bit_set(CANDS_PI0_(155), 16,  2, 0); //pi_wdqlvl_noinit_en
	reg_bit_set(CANDS_PI0_(129), 24,  1, 0); //pi_ca_train_vref_en
	reg_bit_set(CANDS_PI0_(147), 24,  1, 0); //pi_wdqlvl_vref_en
	#endif
}


void dfs_tr_polling()
{
	uint32 pi_tr_done=0;
	volatile uint32 i=0;

	do{
		i++;
		pi_tr_done = (REG32(CANDS_PI0_(213))&0x2000);
		#if 0
		wait_us(10);

		if(i >= 1000)
		{
			ddr_print("\r\ndo ddr dfs 933mhz polling hung, reboot......");
			//__ddr_wdg_reset();
			while(1);
		}
		#endif
	}
	while(pi_tr_done == 0);
//	for(i=0xffff;i>0;i--);
}

#if 0
void print_hw_rdlvl_result(fn)
{
	uint32 delay_midle;
	uint32 delay_left;
	uint32 delay_right;
	uint32 bit_num;
	uint32 i;

	reg_bit_set(CANDS_PHY0_(1024),8,3,fn);

	for(bit_num=0;bit_num<36;bit_num++)
	{
		ddr_print("\r\nbit_num = ");
		ddr_print_u32_hex(bit_num);
		for(i=0;i<2;i++)
		{
			//if !dm bit
			if((bit_num!=8) && (bit_num!=17) && (bit_num!=26) && (bit_num!=35))
			{
				//phy_rddqs_dq_obs_select
				reg_bit_set(CANDS_PHY0_(27)+(bit_num/9)*0x200,8,3,bit_num%9);
				reg_bit_set(CANDS_PHY0_(27)+(bit_num/9)*0x200,11,2,i);
			}
			else
			{
				//phy_rddqs_dq_obs_select
				reg_bit_set(CANDS_PHY0_(27)+(bit_num/9)*0x200,8,5,0x10|(i<<3));
			}
			//sc_phy_snap_obs_regs
			reg_bit_set(CANDS_PHY0_(14)+(bit_num/9)*0x200,24,1,1);
			delay_midle = (REG32(CANDS_PHY0_(78+(bit_num%9))+(bit_num/9)*0x200) >> (16*i)) & 0x3ff;
			delay_left = (REG32(CANDS_PHY0_(47)+(bit_num/9)*0x200) >> 0) & 0x3ff;
			delay_right = (REG32(CANDS_PHY0_(47)+(bit_num/9)*0x200) >> 16) & 0x3ff;
			if(i==0)
			{
				ddr_print("\r\nrdlvl_rising_left_right_mid_margin = (");
			}
			else
			{
				ddr_print("\r\nrdlvl_falling_left_right_mid_margin = (");
			}
			//ddr_print("\r\nhw_rdlvl_mid = ");
			//ddr_print_u32_hex(value);
			ddr_print_u32_hex(delay_left);
			ddr_print(",");
			ddr_print_u32_hex(delay_right);
			ddr_print(",");
			ddr_print_u32_hex(delay_midle);
			ddr_print(")");
			REG32(0x20000000+bit_num*8 + (i%2)*4) = delay_midle;
		}
	}
}


void get_rdlvl_sw_hw_diff(fn)
{
	uint32 value_sw;
	uint32 value_hw;
	uint32 bit_num;
	uint32 value_diff;
	uint32 i;

	reg_bit_set(CANDS_PHY0_(1024),8,3,fn);

	for(bit_num=0;bit_num<36;bit_num++)
	{
		ddr_print("\r\nbit_num = ");
		ddr_print_u32_hex(bit_num);
		for(i=0;i<2;i++)
		{
			value_sw = (REG32(CANDS_PHY0_(78+(bit_num%9))+(bit_num/9)*0x200) >> (16*i)) & 0x3ff;
			value_hw = REG32(0x20000000+bit_num*8 + (i%2)*4);
			if(value_sw >= value_hw)
			{
				value_diff = value_sw - value_hw;
			}
			else
			{
				value_diff = value_hw - value_sw;
			}
			ddr_print("\r\nsw hw diff = ");
			ddr_print_u32_hex(value_diff);
		}
	}
}

void run_sw_lvl_bit_mask_config(uint32 bit_num)
{
	switch(bit_num)
	{
		//----------slice 0
		case 0:	REG32(0xc00d000c) = ~(0x1 << 27);
				REG32(0xc00d400c) = ~(0x1 << 27);
				REG32(0xc00d800c) = ~(0x1 << 27);
				break;
		case 1:	REG32(0xc00d000c) = ~(0x1 << 26);
				REG32(0xc00d400c) = ~(0x1 << 26);
				REG32(0xc00d800c) = ~(0x1 << 26);
				break;
		case 2:	REG32(0xc00d000c) = ~(0x1 << 29);
				REG32(0xc00d400c) = ~(0x1 << 29);
				REG32(0xc00d800c) = ~(0x1 << 29);
				break;
		case 3:	REG32(0xc00d000c) = ~(0x1 << 24);
				REG32(0xc00d400c) = ~(0x1 << 24);
				REG32(0xc00d800c) = ~(0x1 << 24);
				break;
		case 4:	REG32(0xc00d000c) = ~(0x1 << 28);
				REG32(0xc00d400c) = ~(0x1 << 28);
				REG32(0xc00d800c) = ~(0x1 << 28);
				break;
		case 5:	REG32(0xc00d000c) = ~(0x1 << 31);
				REG32(0xc00d400c) = ~(0x1 << 31);
				REG32(0xc00d800c) = ~(0x1 << 31);
				break;
		case 6:	REG32(0xc00d000c) = ~(0x1 << 25);
				REG32(0xc00d400c) = ~(0x1 << 25);
				REG32(0xc00d800c) = ~(0x1 << 25);
				break;
		case 7:	REG32(0xc00d000c) = ~(0x1 << 30);
				REG32(0xc00d400c) = ~(0x1 << 30);
				REG32(0xc00d800c) = ~(0x1 << 30);
				break;
		//case 8:	dm
		//--------------slice 1
		case 9:	REG32(0xc00d000c) = ~(0x1 << 8);
				REG32(0xc00d400c) = ~(0x1 << 8);
				REG32(0xc00d800c) = ~(0x1 << 8);
				break;
		case 10:	REG32(0xc00d000c) = ~(0x1 << 9);
				REG32(0xc00d400c) = ~(0x1 << 9);
				REG32(0xc00d800c) = ~(0x1 << 9);
				break;
		//case 11:	dm
		case 12:	REG32(0xc00d000c) = ~(0x1 << 10);
				REG32(0xc00d400c) = ~(0x1 << 10);
				REG32(0xc00d800c) = ~(0x1 << 10);
				break;
		case 13:	REG32(0xc00d000c) = ~(0x1 << 14);
				REG32(0xc00d400c) = ~(0x1 << 14);
				REG32(0xc00d800c) = ~(0x1 << 14);
				break;
		case 14:	REG32(0xc00d000c) = ~(0x1 << 11);
				REG32(0xc00d400c) = ~(0x1 << 11);
				REG32(0xc00d800c) = ~(0x1 << 11);
				break;
		case 15:	REG32(0xc00d000c) = ~(0x1 << 13);
				REG32(0xc00d400c) = ~(0x1 << 13);
				REG32(0xc00d800c) = ~(0x1 << 13);
				break;
		case 16:	REG32(0xc00d000c) = ~(0x1 << 15);
				REG32(0xc00d400c) = ~(0x1 << 15);
				REG32(0xc00d800c) = ~(0x1 << 15);
				break;
		case 17:	REG32(0xc00d000c) = ~(0x1 << 12);
				REG32(0xc00d400c) = ~(0x1 << 12);
				REG32(0xc00d800c) = ~(0x1 << 12);
				break;
		//--------slice 2
		case 18:	REG32(0xc00d000c) = ~(0x1 << 6);
				REG32(0xc00d400c) = ~(0x1 << 6);
				REG32(0xc00d800c) = ~(0x1 << 6);
				break;
		case 19:	REG32(0xc00d000c) = ~(0x1 << 7);
				REG32(0xc00d400c) = ~(0x1 << 7);
				REG32(0xc00d800c) = ~(0x1 << 7);
				break;
		case 20:	REG32(0xc00d000c) = ~(0x1 << 5);
				REG32(0xc00d400c) = ~(0x1 << 5);
				REG32(0xc00d800c) = ~(0x1 << 5);
				break;
		case 21:	REG32(0xc00d000c) = ~(0x1 << 4);
				REG32(0xc00d400c) = ~(0x1 << 4);
				REG32(0xc00d800c) = ~(0x1 << 4);
				break;
		case 22:	REG32(0xc00d000c) = ~(0x1 << 2);
				REG32(0xc00d400c) = ~(0x1 << 2);
				REG32(0xc00d800c) = ~(0x1 << 2);
				break;
		case 23:	REG32(0xc00d000c) = ~(0x1 << 0);
				REG32(0xc00d400c) = ~(0x1 << 0);
				REG32(0xc00d800c) = ~(0x1 << 0);
				break;
		//case 24:	dm
		case 25:	REG32(0xc00d000c) = ~(0x1 << 3);
				REG32(0xc00d400c) = ~(0x1 << 3);
				REG32(0xc00d800c) = ~(0x1 << 3);
				break;
		case 26:	REG32(0xc00d000c) = ~(0x1 << 1);
				REG32(0xc00d400c) = ~(0x1 << 1);
				REG32(0xc00d800c) = ~(0x1 << 1);
				break;
		//--------------slice 3
		case 27:	REG32(0xc00d000c) = ~(0x1 << 18);
				REG32(0xc00d400c) = ~(0x1 << 18);
				REG32(0xc00d800c) = ~(0x1 << 18);
				break;
		case 28:	REG32(0xc00d000c) = ~(0x1 << 17);
				REG32(0xc00d400c) = ~(0x1 << 17);
				REG32(0xc00d800c) = ~(0x1 << 17);
				break;
		case 29:	REG32(0xc00d000c) = ~(0x1 << 16);
				REG32(0xc00d400c) = ~(0x1 << 16);
				REG32(0xc00d800c) = ~(0x1 << 16);
				break;
		//case 30:	dm
		case 31:	REG32(0xc00d000c) = ~(0x1 << 20);
				REG32(0xc00d400c) = ~(0x1 << 20);
				REG32(0xc00d800c) = ~(0x1 << 20);
				break;
		case 32:	REG32(0xc00d000c) = ~(0x1 << 23);
				REG32(0xc00d400c) = ~(0x1 << 23);
				REG32(0xc00d800c) = ~(0x1 << 23);
				break;
		case 33:	REG32(0xc00d000c) = ~(0x1 << 22);
				REG32(0xc00d400c) = ~(0x1 << 22);
				REG32(0xc00d800c) = ~(0x1 << 22);
				break;
		case 34:	REG32(0xc00d000c) = ~(0x1 << 19);
				REG32(0xc00d400c) = ~(0x1 << 19);
				REG32(0xc00d800c) = ~(0x1 << 19);
				break;
		case 35:	REG32(0xc00d000c) = ~(0x1 << 21);
				REG32(0xc00d400c) = ~(0x1 << 21);
				REG32(0xc00d800c) = ~(0x1 << 21);
				break;
		default: break;
	}
}

void run_sw_rdlvl_single_bit(uint32 fn)
{
	uint32 bit_num;
	uint32 delay_step;
	uint32 delay_cnt;
	uint32 delay_right;
	uint32 delay_left;
	uint32 delay_midle;
	uint32 bist_result;
	uint32 rescan_flag_left;
	uint32 bist_length;
	uint32 i;
	uint32 find_left;
	uint32 find_right;

	delay_step = 0x10;
	bist_length = 0x800000;
	rescan_flag_left = 0;

	swlvl_bist = 1;
	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(289), 8,1,0x0);

	reg_bit_set(CANDS_PHY0_(1024),8,3,fn);

	bist_test_init(BIST_ALLWRC,SIPI_PATT,bist_length,bist_base_addr[0],bist_base_addr[1],bist_base_addr[2]);
	for(bit_num=0;bit_num<36;bit_num++)
	{
		ddr_print("\r\nbit_num = ");
		ddr_print_hex_u32(bit_num);
		//bit_mask do not scan DM bit on dram side according to the pin map
		if((bit_num!=8) && (bit_num!=11) && (bit_num!=24) && (bit_num!=30))
		{
			run_sw_lvl_bit_mask_config(bit_num);
			for(i=0;i<2;i++)	// scan rise and fall
			{
				find_left = 0;
				find_right = 0;
				for(delay_cnt=0x20;delay_cnt<=0x260;delay_cnt+=delay_step)
				{
						reg_bit_set(CANDS_PHY0_(78+(bit_num%9))+(bit_num/9)*0x200,(16*i),10,delay_cnt);	//phy_rddqs_dq0_rise(fall)_slave_delay
						//ctrlupd_req
						reg_bit_set(CANDS_CTL0_(289), 0,1,0x1);

						bist_result = bist_test_entry();

						if((rescan_flag_left==0) && (bist_result==0))
						{
							delay_left = delay_cnt;
							//ddr_print("\r\nrdlvl_left_margin = ");
							//ddr_print_hex_u32(delay_left);
							rescan_flag_left = 1;
							find_left = 1;
						}
						if((rescan_flag_left==1) && (bist_result!=0))
						{
							delay_right = delay_cnt - delay_step;
							//ddr_print("\r\nrdlvl_right_margin = ");
							//ddr_print_hex_u32(delay_right);
							rescan_flag_left = 0;
							//goto wrdqlvl_left_out;
							delay_cnt=0x300;
							find_right = 1;
						}
				}

				if(find_left!=1)
				{
					delay_left = 0;
					//ddr_print("\r\nrdlvl_left_margin = NULL");
				}
				if(find_right!=1)
				{
					delay_right = 0;
					rescan_flag_left = 0;
					//ddr_print("\r\nrdlvl_right_margin = NULL");
				}

				delay_midle = (delay_right+delay_left)/2;
				if(i==0)
				{
					ddr_print("\r\nrdlvl_rising_left_right_mid_margin = (");
				}
				else
				{
					ddr_print("\r\nrdlvl_falling_left_right_mid_margin = (");
				}
				ddr_print_hex_u32(delay_left);
				ddr_print(",");
				ddr_print_hex_u32(delay_right);
				ddr_print(",");
				ddr_print_hex_u32(delay_midle);
				ddr_print(")");
				//ddr_print("\r\nrdlvl_sw_mid = ");
				//ddr_print_hex_u32(delay_midle);
				reg_bit_set(CANDS_PHY0_(78+(bit_num%9))+(bit_num/9)*0x200,(16*i),10,delay_midle);	//phy_rddqs_dq0_rise(fall)_slave_delay

				//ctrlupd_req
				reg_bit_set(CANDS_CTL0_(289), 0,1,0x1);
			}
		}
	}

	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(289), 8,1,0x1);

	swlvl_bist=0;
}
#endif

uint32 get_hw_rdlvl_window(uint32 slice)
{
	uint32 delay_midle;
	uint32 delay_left;
	uint32 delay_right;
	uint32 bit_num;
	uint32 i;
	uint32 rising_window;
	uint32 falling_window;
	uint32 window_delta;

	//reg_bit_set(CANDS_PHY0_(1024),8,3,fn);
	//for each slice we only check bit0 for the rising and falling window
	for(bit_num=slice*9;bit_num<(slice*9+1);bit_num++)
	{
		//ddr_print("\r\nbit_num = ");
		//ddr_print_hex_u32(bit_num);
		for(i=0;i<2;i++)
		{
			//if !dm bit
			if((bit_num!=8) && (bit_num!=17) && (bit_num!=26) && (bit_num!=35))
			{
				//phy_rddqs_dq_obs_select dq0~7
				reg_bit_set(CANDS_PHY0_(27)+(bit_num/9)*0x200,8,3,bit_num%9);
				reg_bit_set(CANDS_PHY0_(27)+(bit_num/9)*0x200,11,2,i);
			}
			else
			{
				//phy_rddqs_dq_obs_select	dm bit
				reg_bit_set(CANDS_PHY0_(27)+(bit_num/9)*0x200,8,5,0x10|(i<<3));
			}
			//sc_phy_snap_obs_regs
			reg_bit_set(CANDS_PHY0_(14)+(bit_num/9)*0x200,24,1,1);
			delay_midle = (REG32(CANDS_PHY0_(78+(bit_num%9))+(bit_num/9)*0x200) >> (16*i)) & 0x3ff;
			delay_left = (REG32(CANDS_PHY0_(47)+(bit_num/9)*0x200) >> 0) & 0x3ff;
			delay_right = (REG32(CANDS_PHY0_(47)+(bit_num/9)*0x200) >> 16) & 0x3ff;
			if(i==0)
			{
				ddr_print("\r\nrdlvl_rising_left_right_mid_margin = (");
				rising_window = delay_right - delay_left;
			}
			else
			{
				ddr_print("\r\nrdlvl_falling_left_right_mid_margin = (");
				falling_window = delay_right - delay_left;
			}
			ddr_print_hex_u32(delay_left);
			ddr_print(",");
			ddr_print_hex_u32(delay_right);
			ddr_print(",");
			ddr_print_hex_u32(delay_midle);
			ddr_print(")");
		}
		if(rising_window > falling_window)
		{
			window_delta = rising_window - falling_window;
		}
		else
		{
			window_delta = falling_window - rising_window;
		}
		ddr_print("\r\nslice");
		ddr_print_hex_u32(slice);
		ddr_print(" window_delta = ");
		ddr_print_hex_u32(window_delta);
	}

	return window_delta;
}

void trigger_sw_pad_cal_rx_cal(uint32 fn)
{
	uint32 i;
	uint32 cal_clk_val=0;

	switch(fn)
	{
	     case 0:cal_clk_val=0x3;break;
	     case 1:cal_clk_val=0x4;break;
	     case 2:cal_clk_val=0x4;break;
	     case 3:cal_clk_val=0x5;break;
	     default:break;
	}
	//modify phy_cal_clock for 920M
	reg_bit_set(CANDS_PHY0_(1096), 8,3,cal_clk_val);
	//phy_cal_start
	reg_bit_set(CANDS_PHY0_(1094),16,1,1);
	//phy_cal_result_obs_0		bit23 pad_cal_done
	while(((REG32(CANDS_PHY0_(1097))>>23) & 0x1) != 1);
	//phy_cal_result2_obs_0		bit23 pad_cal_done
	while(((REG32(CANDS_PHY0_(1098))>>23) & 0x1) != 1);
	for(i=0;i<4;i++)
	{
		//phy_rx_cal_override
		reg_bit_set(CANDS_PHY0_(55)+i*0x200,8,1,1);
		//phy_rx_cal_start
		reg_bit_set(CANDS_PHY0_(55)+i*0x200,0,1,1);
	}
	//wait at least 8us to let rx cal done, because there is no rx cal done signal to polling
	wait_us(5);
	for(i=0;i<4;i++)
	{
		//phy_rx_cal_override
		reg_bit_set(CANDS_PHY0_(55)+i*0x200,8,1,0);
		//phy_manual_clear to trigger a gate init
		reg_bit_set(CANDS_PHY0_(35)+i*0x200,24,6,1);
	}
}

void sw_trigger_exit_sref_rdlvl(void)
{
	//enable pi_rdlvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(95),16,1,1);

	//lp_cmd enter sref
	reg_bit_set(CANDS_CTL0_(141),0,9,0xa);
	while(((REG32(CANDS_CTL0_(153))>>8) & 0x1f) != 0x8);
	while(((REG32(CANDS_CTL0_(153))>>16) & 0x1f) != 0x8);

	//lp_cmd exit sref
	reg_bit_set(CANDS_CTL0_(141),0,9,0x9);
	while(((REG32(CANDS_CTL0_(153))>>8) & 0x1f) != 0x0);
	while(((REG32(CANDS_CTL0_(153))>>16) & 0x1f) != 0x0);

	//wait rdlvl done and write obs reg done
	//slice0
	while((REG32(CANDS_PHY0_(49))&0xf0000000) != 0);
	while((REG32(CANDS_PHY0_(49))&0xffff) != 0xffff);
	//slice1
	while((REG32(CANDS_PHY0_(177))&0xf0000000) != 0);
	while((REG32(CANDS_PHY0_(177))&0xffff) != 0xffff);
	//slice2
	while((REG32(CANDS_PHY0_(305))&0xf0000000) != 0);
	while((REG32(CANDS_PHY0_(305))&0xffff) != 0xffff);
	//slice3
	while((REG32(CANDS_PHY0_(433))&0xf0000000) != 0);
	while((REG32(CANDS_PHY0_(433))&0xffff) != 0xffff);
	//dis pi_rdlvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(95),16,1,0);

}
void run_sw_vref_lvl(uint32 fn)
{
	uint32 vref_cnt;
	uint32 vref_step;
	uint32 i;
	uint32 tmp_window[4]={0,0,0,0};
	uint32 vref_best[4]={0,0,0,0};
	uint32 delta_min = 0x24;
	uint32 found[4]={0,0,0,0};

	reg_bit_set(CANDS_PHY0_(1024),8,3,fn);
	ddr_print("\r\nvreflvl freq = ");
	ddr_print_hex_u32(fn);

	vref_step = 0x2;

	for(vref_cnt=0x2f;vref_cnt<=0x3f;vref_cnt+=vref_step)
	{
		ddr_print("\r\n--------------vref_cnt = ");
		ddr_print_hex_u32(vref_cnt);
		ddr_print("--------------");
		reg_bit_set(CANDS_PHY0_(1048), 8, 6, vref_cnt);
		reg_bit_set(CANDS_PHY0_(1049), 0, 6, vref_cnt);
		reg_bit_set(CANDS_PHY0_(1049), 16, 6, vref_cnt);
		reg_bit_set(CANDS_PHY0_(1050), 0, 6, vref_cnt);

		//trigger_sw_pad_cal_rx_cal(fn);
		//enable hw rdlvl
		sw_trigger_exit_sref_rdlvl();
		for(i=0;i<4;i++)
		{
			if(found[i]==0)
			{
				tmp_window[i] = get_hw_rdlvl_window(i);
				if(tmp_window[i] <= delta_min)
				{
					vref_best[i] = vref_cnt-1;
					found[i] = 1;
				}
			}
		}
	}

	ddr_print("\r\nvref_best slice0 = ");
	ddr_print_hex_u32(vref_best[0]);
	ddr_print("\r\nvref_best slice1 = ");
	ddr_print_hex_u32(vref_best[1]);
	ddr_print("\r\nvref_best slice2 = ");
	ddr_print_hex_u32(vref_best[2]);
	ddr_print("\r\nvref_best slice3 = ");
	ddr_print_hex_u32(vref_best[3]);

	for(i=0;i<4;i++)
	{
		reg_bit_set(CANDS_PHY0_(1024),8,3,i);
		reg_bit_set(CANDS_PHY0_(1048), 8, 6, vref_best[0]);
		reg_bit_set(CANDS_PHY0_(1049), 0, 6, vref_best[1]);
		reg_bit_set(CANDS_PHY0_(1049), 16, 6, vref_best[2]);
		reg_bit_set(CANDS_PHY0_(1050), 0, 6, vref_best[3]);
	}

	//trigger_sw_pad_cal_rx_cal(fn);
}

void run_sw_wrdqlvl_single_slice_adv(uint32 fn)
{
	uint32 slice_num;
	uint32 delay_step;
	uint32 delay_cnt;
	uint32 delay_right;
	uint32 delay_left;
	uint32 delay_midle;
	uint32 bist_result;
	uint32 rescan_flag_left;
	uint32 bist_length;
	uint32 find_left;
	uint32 find_right;

	swlvl_bist = 1;
	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(289), 8,1,0x0);

	delay_step = 0x10;
	bist_length = 0x80000;
	rescan_flag_left = 0;
	find_left = 0;
	find_right = 0;

	reg_bit_set(CANDS_PHY0_(1024),8,3,fn);
	ddr_print("\r\nwrdqlvl freq = ");
	ddr_print_hex_u32(fn);

	bist_test_init(BIST_ALLWRC,SIPI_PATT,bist_length,bist_base_addr[0],bist_base_addr[1],bist_base_addr[2]);
	for(slice_num=0;slice_num<4;slice_num++)
	{
		switch(slice_num)
		{
			case 0:	REG32(0xc00d000c) = ~(0xff << 24);
					REG32(0xc00d400c) = ~(0xff << 24);
					REG32(0xc00d800c) = ~(0xff << 24);
					break;
			case 1:	REG32(0xc00d000c) = ~(0xff << 8);
					REG32(0xc00d400c) = ~(0xff << 8);
					REG32(0xc00d800c) = ~(0xff << 8);
					break;
			case 2:	REG32(0xc00d000c) = ~(0xff << 0);
					REG32(0xc00d400c) = ~(0xff << 0);
					REG32(0xc00d800c) = ~(0xff << 0);
					break;
			case 3:	REG32(0xc00d000c) = ~(0xff << 16);
					REG32(0xc00d400c) = ~(0xff << 16);
					REG32(0xc00d800c) = ~(0xff << 16);
					break;

			default: while(1);break;
		}
		find_left = 0;
		find_right = 0;
		for(delay_cnt=0x1e0;delay_cnt<=0x350;delay_cnt+=delay_step)
		{
			reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq0_slave_delay
			reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq1_slave_delay
			reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq2_slave_delay
			reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq3_slave_delay

			reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq4_slave_delay
			reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq5_slave_delay
			reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq6_slave_delay
			reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq7_slave_delay

			reg_bit_set(CANDS_PHY0_(72)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdm_slave_delay

			//ctrlupd_req
			reg_bit_set(CANDS_CTL0_(289), 0,1,0x1);

			bist_result = bist_test_entry();

			if((rescan_flag_left==0) && (bist_result==0))
			{
				delay_left = delay_cnt;
				ddr_print("\r\nwrdqlvl_left_margin = ");
				ddr_print_hex_u32(delay_left);
				rescan_flag_left = 1;
				find_left = 1;
			}
			if((rescan_flag_left==1) && (bist_result!=0))
			{
				delay_right = delay_cnt - delay_step;
				ddr_print("\r\nwrdqlvl_right_margin = ");
				ddr_print_hex_u32(delay_right);
				rescan_flag_left = 0;
				delay_cnt = 0x390;
				find_right = 1;
			}
		}

		if(find_left!=1)
		{
			delay_left = 0x0;
			ddr_print("\r\nwrdqlvl_left_margin = NULL");
		}
		if(find_right!=1)
		{
			delay_right = 0x0;
			rescan_flag_left = 0;
			ddr_print("\r\nwrdqlvl_right_margin = NULL");
		}

		delay_midle = (delay_right+delay_left)/2;
		ddr_print("\r\nwrlvl_left_right_mid_margin = (");
		ddr_print_hex_u32(delay_left);
		ddr_print(",");
		ddr_print_hex_u32(delay_right);
		ddr_print(",");
		ddr_print_hex_u32(delay_midle);
		ddr_print(")");
		//ddr_print("\r\nwrdqlvl_midle = ");
		//ddr_print_hex_u32(delay_midle);

		reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq0_slave_delay
		reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq1_slave_delay
		reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq2_slave_delay
		reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq3_slave_delay

		reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq4_slave_delay
		reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq5_slave_delay
		reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq6_slave_delay
		reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq7_slave_delay

		reg_bit_set(CANDS_PHY0_(72)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdm_slave_delay

		//ctrlupd_req
		reg_bit_set(CANDS_CTL0_(289), 0,1,0x1);
	}

	REG32(0xc00d000c) = 0;
	REG32(0xc00d400c) = 0;
	REG32(0xc00d800c) = 0;
	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(289), 8,1,0x1);

	swlvl_bist=0;
}

#if 0
void run_sw_wrdqlvl_single_bit(uint32 fn)
{
	uint32 bit_num;
	uint32 delay_step;
	uint32 delay_cnt;
	uint32 delay_right;
	uint32 delay_left;
	uint32 delay_midle;
	uint32 bist_result;
	uint32 rescan_flag_left;
	uint32 bist_length;
	uint32 find_left;
	uint32 find_right;
	uint32 bit_offset;

	swlvl_bist = 1;
	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(289), 8,1,0x0);

	delay_step = 0x10;
	bist_length = 0x80000;
	rescan_flag_left = 0;
	find_left = 0;
	find_right = 0;

	reg_bit_set(CANDS_PHY0_(1024),8,3,fn);
	//ddr_print("\r\nwrdqlvl freq = ");
	//ddr_print_u32_hex(fn);

	for(bit_num=0;bit_num<36;bit_num++)
	{
		#if 0
		switch(bit_num/9)
		{
			case 0:	REG32(0xc00d000c) = ~(0xff << 24);
					REG32(0xc00d400c) = ~(0xff << 24);
					REG32(0xc00d800c) = ~(0xff << 24);
					break;
			case 1:	REG32(0xc00d000c) = ~(0xff << 8);
					REG32(0xc00d400c) = ~(0xff << 8);
					REG32(0xc00d800c) = ~(0xff << 8);
					break;
			case 2:	REG32(0xc00d000c) = ~(0xff << 0);
					REG32(0xc00d400c) = ~(0xff << 0);
					REG32(0xc00d800c) = ~(0xff << 0);
					break;
			case 3:	REG32(0xc00d000c) = ~(0xff << 16);
					REG32(0xc00d400c) = ~(0xff << 16);
					REG32(0xc00d800c) = ~(0xff << 16);
					break;

			default:	break;
		}
		#endif
		//bit_mask do not scan DM bit on dram side according to the pin map
		if((bit_num!=8) && (bit_num!=11) && (bit_num!=24) && (bit_num!=30))
		{
			switch(bit_num/9)
			{
				case 0:	bit_offset = bit_num%2;
						break;
				case 1:	bit_offset = (bit_num-9)%2;
						break;
				case 2:	bit_offset = (bit_num-18)%2;
						break;
				case 3:	bit_offset = (bit_num-27)%2;
						break;
				default:	break;
			}
			run_sw_lvl_bit_mask_config(bit_num);
			find_left = 0;
			find_right = 0;
			ddr_print("\r\nbit_num = ");
			ddr_print_u32_hex(bit_num);
			for(delay_cnt=0x1e0;delay_cnt<=0x350;delay_cnt+=delay_step)
			{
				reg_bit_set(CANDS_PHY0_(68+((bit_num%9)/2))+(bit_num/9)*0x200,16*bit_offset,11,delay_cnt);	//phy_clk_wrdq0_slave_delay
				//reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq1_slave_delay
				//reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq2_slave_delay
				//reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq3_slave_delay

				//reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq4_slave_delay
				//reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq5_slave_delay
				//reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq6_slave_delay
				//reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq7_slave_delay

				//reg_bit_set(CANDS_PHY0_(72)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdm_slave_delay

				//ctrlupd_req
				reg_bit_set(CANDS_CTL0_(289), 0,1,0x1);

				bist_result = bist_test(BIST_ALLWRC,SIPI_PATT,bist_length,bist_base_addr[0],bist_base_addr[1],bist_base_addr[2]);

				if((rescan_flag_left==0) && (bist_result==0))
				{
					delay_left = delay_cnt;
					//ddr_print("\r\nwrdqlvl_left_margin = ");
					//ddr_print_u32_hex(delay_left);
					rescan_flag_left = 1;
					find_left = 1;
				}
				if((rescan_flag_left==1) && (bist_result!=0))
				{
					delay_right = delay_cnt - delay_step;
					//ddr_print("\r\nwrdqlvl_right_margin = ");
					//ddr_print_u32_hex(delay_right);
					rescan_flag_left = 0;
					delay_cnt = 0x390;	//inorder to jump out
					find_right = 1;
				}
			}

			if(find_left!=1)
			{
				delay_left = 0;
				//ddr_print("\r\nwrdqlvl_left_margin = NULL");
			}
			if(find_right!=1)
			{
				delay_right = 0;
				rescan_flag_left = 0;
				//ddr_print("\r\nwrdqlvl_right_margin = NULL");
			}

			delay_midle = (delay_right+delay_left)/2;
			ddr_print("\r\nwrlvl_left_right_mid_margin = (");
			ddr_print_u32_hex(delay_left);
			ddr_print(",");
			ddr_print_u32_hex(delay_right);
			ddr_print(",");
			ddr_print_u32_hex(delay_midle);
			ddr_print(")");
			//ddr_print("\r\nwrdqlvl_midle = ");
			//ddr_print_u32_hex(delay_midle);
			reg_bit_set(CANDS_PHY0_(68+((bit_num%9)/2))+(bit_num/9)*0x200,16*bit_offset,11,delay_midle);
			//reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq0_slave_delay
			//reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq1_slave_delay
			//reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq2_slave_delay
			//reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq3_slave_delay

			//reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq4_slave_delay
			//reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq5_slave_delay
			//reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq6_slave_delay
			//reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq7_slave_delay

			//reg_bit_set(CANDS_PHY0_(72)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdm_slave_delay

			//ctrlupd_req
			reg_bit_set(CANDS_CTL0_(289), 0,1,0x1);
		}
	}

	REG32(0xc00d000c) = 0;
	REG32(0xc00d400c) = 0;
	REG32(0xc00d800c) = 0;
	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(289), 8,1,0x1);

	swlvl_bist=0;
}


void atb_enable(uint32 atb_sel, uint32 atb_data)
{
	reg_bit_set(CANDS_PHY0_(1099),0,15,(atb_sel<<8) | (atb_data<<1) | 0x0);
	reg_bit_set(CANDS_PHY0_(1099),0,15,(atb_sel<<8) | (atb_data<<1) | 0x1);
}

void atb_obs_data_pad(uint32 dqx, uint32 atb_data)
{
	uint32 atb_sel;

	atb_sel = 11+dqx;
	atb_enable(atb_sel,atb_data);
	reg_bit_set(CANDS_PHY0_(1088), 24,2,0x3);
}

void atb_obs_dqs_pad(uint32 dqsx, uint32 atb_data)
{
	uint32 atb_sel;

	atb_sel = 3+dqsx;
	atb_enable(atb_sel,atb_data);
	reg_bit_set(CANDS_PHY0_(1088), 24,2,0x3);
}
#endif

void rptr_scan(uint32 freq_num)
{
	uint32 slice_num=0x0;
	uint32 bist_result=0x0;
	uint32 rptr_val=0x0;
	uint32 left_pass,right_pass=0x1,center_pass;
	swlvl_bist=0x1;
	bist_test_init(BIST_ALLWRC,LFSR_PATT,0x1000,bist_base_addr[0],bist_base_addr[1],bist_base_addr[2]);
	ddr_print("\r\nddr freq:");
	ddr_print_hex_u32(freq_num);
	reg_bit_set(CANDS_PHY0_(1024),8,3,freq_num);
	for(slice_num=0;slice_num<4;slice_num++)
	{
		left_pass=0x0;
		right_pass=0x0;
		ddr_print("\r\nslice num:");
		ddr_print_hex_u32(slice_num);
		for(rptr_val=0x3;rptr_val<0xd;rptr_val++)
		{
			reg_bit_set(CANDS_PHY0_(96)+slice_num*0x200,16,4,rptr_val);		//rptr_update
			ddr_print("\r\nrptr value:");
			ddr_print_hex_u32(rptr_val);
			bist_result = bist_test_entry();
			if(bist_result>0)
			{
				if((left_pass != 0)&&(right_pass == 0))
				{
					right_pass=(rptr_val-1);
				}
				ddr_print("---bist result is fail!!!");
			}else
			{
				if(left_pass==0x0)
				{
					left_pass=rptr_val;
				}else
				{
					if(rptr_val==0xb)
					{
						right_pass=rptr_val;
					}
				}
				ddr_print("---bist result is ok!!!");
			}
		}
		center_pass =(uint32)((left_pass+right_pass)/2);
		reg_bit_set(CANDS_PHY0_(96)+slice_num*0x200,16,4,center_pass);		//rptr_update
		ddr_print("\r\ncenter rptr value:");
		ddr_print_hex_u32(REG32(CANDS_PHY0_(96)+slice_num*0x200));
	}
	swlvl_bist=0x0;
}

void ddr_chn_init(uint32 ddr_clk)
{
	volatile uint32 value = 0;
	volatile uint32 i = 0;
	uint32 ddr_clk_f0=0;
	int min, max;
	int result, len;
	DRAM_TYPE_E ddr_type;


	ddr_type = (islp3)? DDR_DFTYPE_LP3 : DDR_DFTYPE_LP4;

	#ifdef DRAM_LPDDR3_750M
	ddr_clk_f0=250000000;
	#else
		#ifdef LP3_F0_153
		ddr_clk_f0=153000000;
		#else
		ddr_clk_f0=230000000;
		#endif
	#endif

	//ddr_info_init(chn_num);
	//set ddr clk div
	if(islp3)
	{
		ddr_clk_set(ddr_clk_f0);
	}else
	{
		//ddr_clk_set(26000000);
		ddr_clk_set(1000000000); //speed up register program, don't modify
	}


	//ctl&phy reset
	cands_ctl_phy_release();

	//ctl&pi&phy reg set
	cands_ctl_init();
	cands_pi_init();
	cands_phy_init();
//moved to later place
//	cands_ctl_addrmap_set(ddr_type);
//	cands_pi_addrmap_set(ddr_type);

	//pinmux set
	cands_phy_pinmux_init(islp3);
	//qos
	cands_ctl_qos_init();

	cands_ctrl_dfs_set(islp3);
	cands_phy_dfs_set(islp3);
	cands_phy_deskew_pll_mode_set(islp3);

	//ddr freqency which you want to stop
	ddr_freq_target_set(ddr_clk);

	//XH begin
	//dfibus_freq_update(islp3); //
	ctrl_dfiupd_set();
	ctrl_lp_set(islp3);
	 phy_lp_setting(islp3);
	//phy_deskew_pll_bypass_setting();
	#ifndef PHY_DS_ODT_SR_CFG_OFF
	cands_phy_dq_ds_sr_set();
	cands_phy_ca_ds_sr_set();
	#endif
	//disabel emclk[0]/emclk_n_a[0] if islp3 to save power. xiaohui: TBD
	misc_reg_cfg_change();
	cands_deskewpll_cfg();
	ddr_lowpower_pre_cfg();
	if(islp3)
	{
		pi_training_enable();
	}
	else
	{
		lp4_init_training_enable();
	}

	cands_pad_cal_clk_set(ddr_clk);
	cands_ctl_addrmap_set(ddr_type);
	cands_pi_addrmap_set(ddr_type);

	if(!islp3)
	{
		cands_26M_cal_clk_workaround(); // only for LPDDR4
	}

	//trigger ddr init flow
	ddr_init_trigger(pi_training_on);//w/o pi training

	//polling training done
    //#ifdef DFS_EN
    if(pi_training_on==0x1) {
	    polling_pi_training_done(0x1,islp3); //XH: TBD
    }
    //#endif

	//wait ctl training done
	wait_ctl_init_done();
	sync_mr12_mr14(islp3);
        vref_cfg_lp3();
	//workaround_check_pvtr_value();
	REG32(DDR0_ACC_RDY) |= (0x1 << 0);
#if 0
    if(pi_training_on) {
        sync_mr12_mr14(); //xiaohui: TBD
    }
	 if(!islp3)
	 {
		f0_master_delay_update();// xiaohui : TBD
	 }
#endif

#ifdef DRAM_LPDDR3
	#ifdef DDR_AUTO_DETECT
	ddr_type = cands_ddr_auto_detect();
	cands_ctl_addrmap_set(ddr_type);
	cands_pi_addrmap_set(ddr_type);
	cands_auto_detect_fix_reg(ddr_type );
	#endif
	//dfs to target freq
	#ifdef DFS_EN
		switch_to_dfs_mode();
		dfs_noinit_tr_en();
		//dfs_go(3);
		//dfs_tr_polling();
		//run_sw_vref_lvl(3);
		#ifdef BIST_TEST_FX
		ddr_test(0);
		#endif
		dfs_go(1);
		dfs_tr_polling();
		//print_hw_rdlvl_result(1);
		//run_sw_rdlvl_single_bit(1);
		//run_sw_wrdqlvl_single_bit(1);
		#ifdef BIST_TEST_FX
		ddr_test(1);
		#endif
		dfs_go(2);
		dfs_tr_polling();
		//print_hw_rdlvl_result(2);
		//run_sw_rdlvl_single_bit(2);
		//run_sw_wrdqlvl_single_bit(2);
		run_sw_wrdqlvl_single_slice_adv(2);
		rptr_scan(2);
		#ifdef	BIST_TEST_FX
		ddr_test(2);
		#endif
		#ifdef DRAM_LPDDR3_750M
		dfs_noinit_tr_dis();
		if(ddr_clk==250000000)
		{
			dfs_go(0);
		}
		if(ddr_clk==500000000)
		{
			dfs_go(1);
		}
		#else
		dfs_go(3);
		dfs_tr_polling();
		//print_hw_rdlvl_result(3);
		//run_sw_rdlvl_single_bit(3);
		//run_sw_wrdqlvl_single_bit(3);
		run_sw_wrdqlvl_single_slice_adv(3);
		rptr_scan(3);
		#ifdef BIST_TEST_FX
		ddr_test(3);
		#endif
		dfs_noinit_tr_dis();
		if(ddr_clk==230000000)
		{
			dfs_go(0);
		}
		if(ddr_clk==460000000)
		{
			dfs_go(1);
		}
		if(ddr_clk==613000000)
		{
			dfs_go(2);
		}
		#endif
	#endif
#else
	switch_to_dfs_mode();
#endif
        ddr_lowpower_init();  //xiaohui: TBD
}

void ddr_debug_mode_cfg(uint32 ddr_mode)
{
	uint32 spl_mode=(ddr_mode>>30)&0x1;
	uint32 type=(ddr_mode>>0)&0xff;
	uint32 loop_mode,bist_size,bist_patt,bist_mode;
	if(spl_mode)
	{
		switch(type)
		{
			case 0:while(1);break;
			case 1:
				loop_mode=(ddr_mode>>24)&0xf;
				bist_size=(0x2000)<<((ddr_mode>>8)&0xf);
				bist_patt=(ddr_mode>>12)&0xf;
				bist_mode=(ddr_mode>>16)&0xf;
				do
				{
					bist_test_init(bist_mode,bist_patt,bist_size,bist_base_addr[0],bist_base_addr[1],bist_base_addr[2]);
				}while(loop_mode);
				break;
			default:break;
		}
	}else
	{
		//close dfs
		if((type>>0)&0x1)
		{
			REG32(0xe602a034)=0x12345678;
		}else
		{
			if(((ddr_mode>>8)&0xf) > 0)
			{
				REG32(0xe602a0f0)=(ddr_mode>>8)&0xf;
			}
		}
		if((type>>1)&0x1)
		{
			REG32(0xe602a038)=0x12345678;
		}
		if((type>>2)&0x1)
		{
			REG32(0xe602a030)=0x12345678;
		}
	}
}

void sdram_init(uint32 ddr_clk,uint32 mode)

{
//	ddr_clk=460000000;
	uint32 i = 0;
	uint32 cs_num=0x1;
	uint32 freq_num=0;
	ddr_mode = mode;
	chip_id = REG32(0xe42e3120);
	islp3 = is_lp3();
	pi_training_on = pi_training_on_check();
	//ddr_mpu_set();
	//ddr_pin_preset(islp3);
	ddr_info_init();
	ddr_freq_info_init();
	ddr_chn_init(ddr_clk);
	ddr_print("\r\nddr current freq:");
	ddr_print_hex_u32(REG32(0xe42e0098));
#ifdef WATCH_DOG_REBOOT_TEST
	if(REG32(0xe602a000)!=0x12345678)
	{
		REG32(0xe602a000)=0x12345678;
		REG32(0xe602a004)=0x0;
		ddr_print("\r\n set regs");
	}
	REG32(0xe602a004)+=1;
	ddr_print("\r\n total test times:");
	ddr_print_hex_u32(REG32(0xe602a004));
	__ddr_wdg_reset();
#endif
#ifdef DDR_SCAN
	swlvl_bist=1;
	if((ddr_mode>>7)&0x1)
	{
		cs_num=0x2;
	}
	ddr_scan(ddr_clk,cs_num,DDR_TYPE_LOCAL);
	while(1);
#endif
	if(ddr_mode !=0 )
	{
		ddr_debug_mode_cfg(ddr_mode);
	}
}







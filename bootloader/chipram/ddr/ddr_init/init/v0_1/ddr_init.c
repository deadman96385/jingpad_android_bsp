#include "ddr_init.h"
#include "ddr_timing.h"
#include "ddr_qos.h"

#ifdef  CODE_SIZE_OPTIMIZE
void * temp_fn[5] = {0};
#else
uint32 temp_fn[5] = {0};
#endif

uint32 pi_fn_div[5] = {0};

uint32 fn_ctl_target=0;
uint32 fn_pi_target=0;
uint32 fsp_wr=0;
uint32 fsp_op=0;

#if DO_DFS_INIT
#ifdef DRAM_LPDDR3
void dfs_reg_cfg(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//read current status form AON_CFG_CFG
	uint32 clk_div_old = 0;
	uint32 xtal_26m_old = 0;

	clk_div_old = (REG32(AON_APB_CGM_CFG)>>(8+(chn_num<<4)))&0x3f;
	xtal_26m_old = (REG32(AON_APB_CGM_CFG)>>(14+(chn_num<<4)))&0x1;

	//PWRUP_SREFRESH_EXIT
	reg_bit_set(CANDS_CTL0_(115)+chn_offset, 0, 1, 1);

	//dfs_soft_mode
	reg_bit_set(PUB0_LP_GEN_CTRL+chn_offset, 6, 1, 1);

	//set pub0 soft dfs ctrl
	#if 0
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset,0,6,0x0);
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset,6,6,clk_div_old);
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset,12,6,clk_div_old);
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset,18,3,0x0);
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset,21,1,xtal_26m_old);
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset,22,1,xtal_26m_old);
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset,23,9,0x0);
	#else
	REG32(PUB0_SOFT_DFS_CTRL+chn_offset) = (xtal_26m_old<<22)|(xtal_26m_old<<21)|(clk_div_old<<12)|(clk_div_old<<6);
	#endif

	if(chn_num == 0)
	{
		//set pub fc ctrl
		reg_bit_set(AON_APB_PUB_FC_CTRL,0,8,0xff);
		reg_bit_set(AON_APB_PUB_FC_CTRL,8,2,0x3);
		reg_bit_set(AON_APB_PUB_FC_CTRL,10,6,clk_div_old);

		//set emc_ckg_sel_default_pubx_exte
		reg_bit_set(AON_APB_PUB_CTRL,0,1,xtal_26m_old);

		//emc_ckg_sel_load
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,19, 1, 1);

		//clk_dmcx_sel_hw_en, 0:by hw 1:by sw
		reg_bit_set(AON_APB_CGM_CFG, 7, 1, 1);
	}
	else
	{
		//set pub fc ctrl
		reg_bit_set(AON_APB_PUB_FC_CTRL,16,8,0xff);
		reg_bit_set(AON_APB_PUB_FC_CTRL,24,2,0x3);
		reg_bit_set(AON_APB_PUB_FC_CTRL,26,6,clk_div_old);

		//set emc_ckg_sel_default_pubx_exte
		reg_bit_set(AON_APB_PUB_CTRL,1,1,xtal_26m_old);

		//emc_ckg_sel_load
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,20, 1, 1);

		//clk_dmcx_sel_hw_en, 0:by hw 1:by sw
		reg_bit_set(AON_APB_CGM_CFG, 23, 1, 1);

	}
}
void dfs_dma_cfg(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	reg_bit_set(AON_APB_PUB_FC_CTRL, (chn_num<<4), 8, 0xff);//pubx dfs switch wait time
	reg_bit_set(PUB0_APB_BUS_MON+chn_offset, 30, 1, 0x1);   //dfs ahb master eb
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG2+chn_offset, 0, 8, 0x20); //wr wait count

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG0_ADDR+chn_offset, 0, 20, (0x30000E98+chn_offset)); //wr wait count
	REG32(PUB0_APB_DFS_WR_MCTL_REG0_DATA_F0+chn_offset) = 0x3; //data0_F0, deskew bypass
	REG32(PUB0_APB_DFS_WR_MCTL_REG0_DATA_F1+chn_offset) = 0x0; //data0_F1
	REG32(PUB0_APB_DFS_WR_MCTL_REG0_DATA_F2+chn_offset) = 0x0; //data0_F2
	REG32(PUB0_APB_DFS_WR_MCTL_REG0_DATA_F3+chn_offset) = 0x0; //data0_F3

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG1_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(1075)+chn_offset)); //wr wait count
	REG32(PUB0_APB_DFS_WR_MCTL_REG1_DATA_F0+chn_offset) = 0x2FF; //data0_F0, cal_clk_select
	REG32(PUB0_APB_DFS_WR_MCTL_REG1_DATA_F1+chn_offset) = 0x3FF; //data0_F1, cal_clk_select
	REG32(PUB0_APB_DFS_WR_MCTL_REG1_DATA_F2+chn_offset) = 0x4FF; //data0_F2, cal_clk_select
	REG32(PUB0_APB_DFS_WR_MCTL_REG1_DATA_F3+chn_offset) = 0x5FF; //data0_F3, cal_clk_select

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 13, 1, 0x1); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 8,  5, 0x2); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 4,  4, 0x2); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 3,  1, 0x0); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 1,  2, 0x0); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 0,  1, 0x1); //dfs_fc_ack-wait_comp_en
}
void dfs_noinit_tr_en(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	reg_bit_set(CANDS_PI0_(1)+chn_offset, 0,  1, 1); //pi_normal_lvl_seq
	reg_bit_set(CANDS_PI0_(1)+chn_offset, 8,  1, 1); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(92)+chn_offset, 8,  2, 0x2); //pi_wrlvl_noinit_en
	reg_bit_set(CANDS_PI0_(135)+chn_offset, 8,  2, 0x2); //pi_calvl_noinit_en
	reg_bit_set(CANDS_PI0_(116)+chn_offset, 16,  2, 0x2); //pi_rdlvl_noinit_en
	reg_bit_set(CANDS_PI0_(116)+chn_offset, 24,  2, 0x2); //pi_rdlvl_gate_noinit_en

	reg_bit_set(CANDS_PI0_(257)+chn_offset, 0,  24, 0x3ffff); //pi_init_status_clean
}


void dfs_noinit_tr_dis(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	reg_bit_set(CANDS_PI0_(1)+chn_offset, 0,  1, 0); //pi_normal_lvl_seq
	reg_bit_set(CANDS_PI0_(1)+chn_offset, 8,  1, 0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(92)+chn_offset, 8,  2, 0); //pi_wrlvl_noinit_en
	reg_bit_set(CANDS_PI0_(135)+chn_offset, 8,  2, 0); //pi_calvl_noinit_en
	reg_bit_set(CANDS_PI0_(141)+chn_offset, 24,  1, 0); //pi_ca_train_vref_en
	reg_bit_set(CANDS_PI0_(116)+chn_offset, 16,  2, 0); //pi_rdlvl_noinit_en
	reg_bit_set(CANDS_PI0_(116)+chn_offset, 24,  2, 0); //pi_rdlvl_gate_noinit_en
	reg_bit_set(CANDS_PI0_(159)+chn_offset, 24,  1, 0); //pi_wdqlvl_vref_en
	reg_bit_set(CANDS_PI0_(167)+chn_offset, 16,  2, 0); //pi_wdqlvl_noinit_en
}
void dfs_tr_polling(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 pi_tr_done=0;
	volatile uint32 i=0;

	do{
		i++;
		pi_tr_done = (REG32(CANDS_PI0_(256)+chn_offset)&0x2000);
		wait_us(10);

		if(i >= 1000)
		{
			__ddr_print("\r\ndo ddr dfs 933mhz polling hung, reboot......");
			__ddr_wdg_reset();
			while(1);
		}
	}
	while(pi_tr_done == 0);
	for(i=0xffff;i>0;i--);
}

void dfs_go(DDR_CHANNEL_NUM_E chn_num, uint32 fn)
{
	uint32 ratio;
	uint32 scan_ratio;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	volatile uint32 i = 0;

	switch(fn)
	{
		case 0: ratio = 0x16; scan_ratio = 0; break;
		case 1: ratio = 0xA;  scan_ratio = 0; break;
		case 2: ratio = 0x06; scan_ratio = 0; break;
		case 3: ratio = 0x02; scan_ratio = 0; break;
		default:while(1);
	}

	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 0, 1, 1); //pub_dfs_sw_enable
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 1, 1, 0); //pub_dfs_sw_req
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 4, 2, fn); //pub_dfs_sw_frq_sel
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 6, 6, ratio); //pub_dfs_sw_ratio
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 21,1, 0); //pub_dfs_sw_ratio_default
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 22,1, scan_ratio); //scan_pub_dfs_sw_ratio
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 24,8, 0x08); //pub_dfs_sw_switch_period

	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 1,1, 1); //pub_dfs_sw_req--trigger

	//check whether mc has entered into selfrefresh or not
	while(((REG32(PUB0_SOFT_DFS_CTRL+chn_offset)&0x08) != 0x00) ||
	      ((REG32(PUB0_SOFT_DFS_CTRL+chn_offset)&0x04) != 0x04))
	{
		i++;
		wait_us(10);
		if(i == 1000)
		{
			__ddr_print("\r\ndo ddr init dfs hung, reboot......");
			__ddr_wdg_reset();
			while(1);
		}
	}

	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 1,1, 0x0); //pub_dfs_sw_req--trigger
}
#endif
#endif

void cands_ctl_phy_reset(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 i = 0;

	if(chn_num == DDR_CHANNEL_0)
	{
		//clear ctl & phy & ahb reset
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 5, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 7, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 8, 1, 0);
		wait_us(50);
                //umctl auto gate en
                reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 4, 1, 1);
                //phy auto gate en
                reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 6, 1, 1);
		//ctl & phy en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 1, 2, 0);
		wait_us(50);
	}
	else
	{
		//clear ctl & phy & ahb reset
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 21, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 23, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 24, 1, 0);
		wait_us(50);
                //umctl auto gate en
                reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 20, 1, 1);
                //phy auto gate en
                reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 22, 1, 1);
		//ctl & phy en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 17, 2, 0);
		wait_us(50);
	}
	return;
}

void cands_ctl_timing_map(uint32 set_sum,CANDS_CTL_TIMING_T * ctl_timing,
			uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4,
			CANDS_CTL_TIMING_T * f0_timing, CANDS_CTL_TIMING_T * f1_timing,
			CANDS_CTL_TIMING_T * f2_timing, CANDS_CTL_TIMING_T * f3_timing,
			CANDS_CTL_TIMING_T * f4_timing)
{
	uint32 i = 0;

	for(i = 0; i < set_sum; i++)
	{
		if(ctl_timing[i].ddr_clk == f0)
		{
			temp_fn[0] = (uint32)(&ctl_timing[i]);
		}
		if(ctl_timing[i].ddr_clk == f1)
		{
			temp_fn[1] = (uint32)(&ctl_timing[i]);
		}
		if(ctl_timing[i].ddr_clk == f2)
		{
			temp_fn[2] = (uint32)(&ctl_timing[i]);
		}
		if(ctl_timing[i].ddr_clk == f3)
		{
			temp_fn[3] = (uint32)(&ctl_timing[i]);
		}
		if(ctl_timing[i].ddr_clk == f4)
		{
			temp_fn[4] = (uint32)(&ctl_timing[i]);
		}
	}

}


//#if  1
void cands_ctl_actiming_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_CTL_TIMING_T * ctl_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
	#ifdef CODE_SIZE_OPTIMIZE
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T **)temp_fn;

	#else
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
	#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;


	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

	//cke_inactive
	__raw_writel(CANDS_CTL0_(19)+chn_offset, f0_timing->CKE_INACTIVE);
	//cke_delay
	reg_bit_set(CANDS_CTL0_(115)+chn_offset,24,3, f0_timing->CKE_DELAY);
	//CKSRE
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(519+65*i)+chn_offset,24,8, timing[i]->CKSRE);
		reg_bit_set(CANDS_CTL0_(520+65*i)+chn_offset,16,8, timing[i]->CKSRX);
	}
	#else
	reg_bit_set(CANDS_CTL0_(519)+chn_offset,24,8, f0_timing->CKSRE);
	reg_bit_set(CANDS_CTL0_(584)+chn_offset,24,8, f1_timing->CKSRE);
	reg_bit_set(CANDS_CTL0_(649)+chn_offset,24,8, f2_timing->CKSRE);
	reg_bit_set(CANDS_CTL0_(714)+chn_offset,24,8, f3_timing->CKSRE);
	reg_bit_set(CANDS_CTL0_(779)+chn_offset,24,8, f4_timing->CKSRE);
	//CKSRX
	reg_bit_set(CANDS_CTL0_(520)+chn_offset,16,8, f0_timing->CKSRX);
	reg_bit_set(CANDS_CTL0_(585)+chn_offset,16,8, f1_timing->CKSRX);
	reg_bit_set(CANDS_CTL0_(650)+chn_offset,16,8, f2_timing->CKSRX);
	reg_bit_set(CANDS_CTL0_(715)+chn_offset,16,8, f3_timing->CKSRX);
	reg_bit_set(CANDS_CTL0_(780)+chn_offset,16,8, f4_timing->CKSRX);
	#endif
    //
	reg_bit_set(CANDS_CTL0_(21)+chn_offset,16,3, f0_timing->TBST_INT_INTERVAL);
	reg_bit_set(CANDS_CTL0_(23)+chn_offset, 0,5, f0_timing->TCACKEH);
	reg_bit_set(CANDS_CTL0_(22)+chn_offset, 0,5, f0_timing->TCACKEL);
	reg_bit_set(CANDS_CTL0_(844)+chn_offset,0,10,f0_timing->TCAENT);
	reg_bit_set(CANDS_CTL0_(22)+chn_offset,24,5, f0_timing->TCAEXT);
	reg_bit_set(CANDS_CTL0_(22)+chn_offset,16,6, f0_timing->TCAMRD);
	reg_bit_set(CANDS_CTL0_(20)+chn_offset,24,5, f0_timing->TCCD);
	reg_bit_set(CANDS_CTL0_(20)+chn_offset, 8,6, f0_timing->TCCDMW);
	reg_bit_set(CANDS_CTL0_(20)+chn_offset,16,3, 3);
    //TCKCKEL
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(534+65*i)+chn_offset,16,4,timing[i]->TCKCKEL);
		reg_bit_set(CANDS_CTL0_(534+65*i)+chn_offset, 8,4,timing[i]->TCKE);
		reg_bit_set(CANDS_CTL0_(534+65*i)+chn_offset, 0,4,timing[i]->TCKEHCMD);
		reg_bit_set(CANDS_CTL0_(535+65*i)+chn_offset, 8,4,timing[i]->TCKEHCS);
		reg_bit_set(CANDS_CTL0_(535+65*i)+chn_offset, 0,4,timing[i]->TCKELCMD);
		reg_bit_set(CANDS_CTL0_(535+65*i)+chn_offset,16,4,timing[i]->TCKELCS);
		reg_bit_set(CANDS_CTL0_(535+65*i)+chn_offset,24,4,timing[i]->TCKELPD);
		reg_bit_set(CANDS_CTL0_(536+65*i)+chn_offset, 0,8,timing[i]->TCKESR);
	}
	#else
	reg_bit_set(CANDS_CTL0_(534)+chn_offset,16,4,f0_timing->TCKCKEL);
	reg_bit_set(CANDS_CTL0_(599)+chn_offset,16,4,f1_timing->TCKCKEL);
	reg_bit_set(CANDS_CTL0_(664)+chn_offset,16,4,f2_timing->TCKCKEL);
	reg_bit_set(CANDS_CTL0_(729)+chn_offset,16,4,f3_timing->TCKCKEL);//b64
	reg_bit_set(CANDS_CTL0_(794)+chn_offset,16,4,f4_timing->TCKCKEL);
	//TCKE
	reg_bit_set(CANDS_CTL0_(534)+chn_offset, 8,4,f0_timing->TCKE);
	reg_bit_set(CANDS_CTL0_(599)+chn_offset, 8,4,f1_timing->TCKE);
	reg_bit_set(CANDS_CTL0_(664)+chn_offset, 8,4,f2_timing->TCKE);
	reg_bit_set(CANDS_CTL0_(729)+chn_offset, 8,4,f3_timing->TCKE);//b64
	reg_bit_set(CANDS_CTL0_(794)+chn_offset, 8,4,f4_timing->TCKE);
    //TCKEHCMD
	reg_bit_set(CANDS_CTL0_(534)+chn_offset, 0,4,f0_timing->TCKEHCMD);
	reg_bit_set(CANDS_CTL0_(599)+chn_offset, 0,4,f1_timing->TCKEHCMD);
	reg_bit_set(CANDS_CTL0_(664)+chn_offset, 0,4,f2_timing->TCKEHCMD);
	reg_bit_set(CANDS_CTL0_(729)+chn_offset, 0,4,f3_timing->TCKEHCMD);//b64
	reg_bit_set(CANDS_CTL0_(794)+chn_offset, 0,4,f4_timing->TCKEHCMD);
    //TCKEHCS
	reg_bit_set(CANDS_CTL0_(535)+chn_offset, 8,4,f0_timing->TCKEHCS);
	reg_bit_set(CANDS_CTL0_(600)+chn_offset, 8,4,f1_timing->TCKEHCS);
	reg_bit_set(CANDS_CTL0_(665)+chn_offset, 8,4,f2_timing->TCKEHCS);
	reg_bit_set(CANDS_CTL0_(730)+chn_offset, 8,4,f3_timing->TCKEHCS);//b68
	reg_bit_set(CANDS_CTL0_(795)+chn_offset, 8,4,f4_timing->TCKEHCS);
    //TCKELCMD
	reg_bit_set(CANDS_CTL0_(535)+chn_offset, 0,4,f0_timing->TCKELCMD);
	reg_bit_set(CANDS_CTL0_(600)+chn_offset, 0,4,f1_timing->TCKELCMD);
	reg_bit_set(CANDS_CTL0_(665)+chn_offset, 0,4,f2_timing->TCKELCMD);
	reg_bit_set(CANDS_CTL0_(730)+chn_offset, 0,4,f3_timing->TCKELCMD);//b68
	reg_bit_set(CANDS_CTL0_(795)+chn_offset, 0,4,f4_timing->TCKELCMD);
    //TCKELCS
	reg_bit_set(CANDS_CTL0_(535)+chn_offset,16,4,f0_timing->TCKELCS);
	reg_bit_set(CANDS_CTL0_(600)+chn_offset,16,4,f1_timing->TCKELCS);
	reg_bit_set(CANDS_CTL0_(665)+chn_offset,16,4,f2_timing->TCKELCS);
	reg_bit_set(CANDS_CTL0_(730)+chn_offset,16,4,f3_timing->TCKELCS);//b68
	reg_bit_set(CANDS_CTL0_(795)+chn_offset,16,4,f4_timing->TCKELCS);
    //TCKELPD
	reg_bit_set(CANDS_CTL0_(535)+chn_offset,24,4,f0_timing->TCKELPD);
	reg_bit_set(CANDS_CTL0_(600)+chn_offset,24,4,f1_timing->TCKELPD);
	reg_bit_set(CANDS_CTL0_(665)+chn_offset,24,4,f2_timing->TCKELPD);
	reg_bit_set(CANDS_CTL0_(730)+chn_offset,24,4,f3_timing->TCKELPD);//b68
	reg_bit_set(CANDS_CTL0_(795)+chn_offset,24,4,f4_timing->TCKELPD);
    //TCKESR
	reg_bit_set(CANDS_CTL0_(536)+chn_offset, 0,8,f0_timing->TCKESR);
	reg_bit_set(CANDS_CTL0_(601)+chn_offset, 0,8,f1_timing->TCKESR);
	reg_bit_set(CANDS_CTL0_(666)+chn_offset, 0,8,f2_timing->TCKESR);
	reg_bit_set(CANDS_CTL0_(731)+chn_offset, 0,8,f3_timing->TCKESR);//b6c
	reg_bit_set(CANDS_CTL0_(796)+chn_offset, 0,8,f4_timing->TCKESR);
	#endif
    //TCKFSPE
	reg_bit_set(CANDS_CTL0_(856)+chn_offset, 0,5,f0_timing->TCKFSPE);
	reg_bit_set(CANDS_CTL0_(858)+chn_offset,16,5,f1_timing->TCKFSPE);
	reg_bit_set(CANDS_CTL0_(861)+chn_offset, 0,5,f2_timing->TCKFSPE);
	reg_bit_set(CANDS_CTL0_(863)+chn_offset,16,5,f3_timing->TCKFSPE);//d7c
	reg_bit_set(CANDS_CTL0_(866)+chn_offset, 0,5,f4_timing->TCKFSPE);
    //TCKFSPX
	reg_bit_set(CANDS_CTL0_(856)+chn_offset, 8,5,f0_timing->TCKFSPX);
	reg_bit_set(CANDS_CTL0_(858)+chn_offset,24,5,f1_timing->TCKFSPX);
	reg_bit_set(CANDS_CTL0_(861)+chn_offset, 8,5,f2_timing->TCKFSPX);
	reg_bit_set(CANDS_CTL0_(863)+chn_offset,24,5,f3_timing->TCKFSPX);//d7c
	reg_bit_set(CANDS_CTL0_(866)+chn_offset, 8,5,f4_timing->TCKFSPX);
    //TCMDCKE
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(536+65*i)+chn_offset, 8,4,timing[i]->TCMDCKE);
		reg_bit_set(CANDS_CTL0_(536+65*i)+chn_offset,24,4,timing[i]->TCSCKE);
		reg_bit_set(CANDS_CTL0_(536+65*i)+chn_offset,16,4,timing[i]->TCSCKEH);
		reg_bit_set(CANDS_CTL0_(537+65*i)+chn_offset, 0,6,timing[i]->TDAL);
		reg_bit_set(CANDS_CTL0_(547+65*i)+chn_offset, 0,4,timing[i]->TDQSCK_MAX);
		reg_bit_set(CANDS_CTL0_(547+65*i)+chn_offset, 8,2,timing[i]->TDQSCK_MIN);
		reg_bit_set(CANDS_CTL0_(547+65*i)+chn_offset,16,3,timing[i]->TESCKE);
		reg_bit_set(CANDS_CTL0_(547+65*i)+chn_offset,24,8,timing[i]->TFAW);
	}
	#else
	reg_bit_set(CANDS_CTL0_(536)+chn_offset, 8,4,f0_timing->TCMDCKE);
	reg_bit_set(CANDS_CTL0_(601)+chn_offset, 8,4,f1_timing->TCMDCKE);
	reg_bit_set(CANDS_CTL0_(666)+chn_offset, 8,4,f2_timing->TCMDCKE);
	reg_bit_set(CANDS_CTL0_(731)+chn_offset, 8,4,f3_timing->TCMDCKE);//b6c 0x3
	reg_bit_set(CANDS_CTL0_(796)+chn_offset, 8,4,f4_timing->TCMDCKE);
    //TCSCKE
	reg_bit_set(CANDS_CTL0_(536)+chn_offset,24,4,f0_timing->TCSCKE);
	reg_bit_set(CANDS_CTL0_(601)+chn_offset,24,4,f1_timing->TCSCKE);
	reg_bit_set(CANDS_CTL0_(666)+chn_offset,24,4,f2_timing->TCSCKE);
	reg_bit_set(CANDS_CTL0_(731)+chn_offset,24,4,f3_timing->TCSCKE);//b6c 0x0
	reg_bit_set(CANDS_CTL0_(796)+chn_offset,24,4,f4_timing->TCSCKE);
    //TCSCKEH
	reg_bit_set(CANDS_CTL0_(536)+chn_offset,16,4,f0_timing->TCSCKEH);
	reg_bit_set(CANDS_CTL0_(601)+chn_offset,16,4,f1_timing->TCSCKEH);
	reg_bit_set(CANDS_CTL0_(666)+chn_offset,16,4,f2_timing->TCSCKEH);
	reg_bit_set(CANDS_CTL0_(731)+chn_offset,16,4,f3_timing->TCSCKEH);
	reg_bit_set(CANDS_CTL0_(796)+chn_offset,16,4,f4_timing->TCSCKEH);
    //TDAL
	reg_bit_set(CANDS_CTL0_(537)+chn_offset, 0,6,f0_timing->TDAL);
	reg_bit_set(CANDS_CTL0_(602)+chn_offset, 0,6,f1_timing->TDAL);
	reg_bit_set(CANDS_CTL0_(667)+chn_offset, 0,6,f2_timing->TDAL);
	reg_bit_set(CANDS_CTL0_(732)+chn_offset, 0,6,f3_timing->TDAL);
	reg_bit_set(CANDS_CTL0_(797)+chn_offset, 0,6,f4_timing->TDAL);
    //TDQSCK_MAX
	reg_bit_set(CANDS_CTL0_(547)+chn_offset, 0,4,f0_timing->TDQSCK_MAX);
	reg_bit_set(CANDS_CTL0_(612)+chn_offset, 0,4,f1_timing->TDQSCK_MAX);
	reg_bit_set(CANDS_CTL0_(677)+chn_offset, 0,4,f2_timing->TDQSCK_MAX);
	reg_bit_set(CANDS_CTL0_(742)+chn_offset, 0,4,f3_timing->TDQSCK_MAX);
	reg_bit_set(CANDS_CTL0_(807)+chn_offset, 0,4,f4_timing->TDQSCK_MAX);
    //TDQSCK_MIN
	reg_bit_set(CANDS_CTL0_(547)+chn_offset, 8,2,f0_timing->TDQSCK_MIN);
	reg_bit_set(CANDS_CTL0_(612)+chn_offset, 8,2,f1_timing->TDQSCK_MIN);
	reg_bit_set(CANDS_CTL0_(677)+chn_offset, 8,2,f2_timing->TDQSCK_MIN);
	reg_bit_set(CANDS_CTL0_(742)+chn_offset, 8,2,f3_timing->TDQSCK_MIN);
	reg_bit_set(CANDS_CTL0_(807)+chn_offset, 8,2,f4_timing->TDQSCK_MIN);
	//TESCKE
	reg_bit_set(CANDS_CTL0_(547)+chn_offset,16,3,f0_timing->TESCKE);
	reg_bit_set(CANDS_CTL0_(612)+chn_offset,16,3,f1_timing->TESCKE);
	reg_bit_set(CANDS_CTL0_(677)+chn_offset,16,3,f2_timing->TESCKE);
	reg_bit_set(CANDS_CTL0_(742)+chn_offset,16,3,f3_timing->TESCKE);
	reg_bit_set(CANDS_CTL0_(807)+chn_offset,16,3,f4_timing->TESCKE);
	//TFAW
	reg_bit_set(CANDS_CTL0_(547)+chn_offset,24,8,f0_timing->TFAW);
	reg_bit_set(CANDS_CTL0_(612)+chn_offset,24,8,f1_timing->TFAW);
	reg_bit_set(CANDS_CTL0_(677)+chn_offset,24,8,f2_timing->TFAW);
	reg_bit_set(CANDS_CTL0_(742)+chn_offset,24,8,f3_timing->TFAW);
	reg_bit_set(CANDS_CTL0_(807)+chn_offset,24,8,f4_timing->TFAW);
	#endif
    //TFC
	reg_bit_set(CANDS_CTL0_(855)+chn_offset,16,10,f0_timing->TFC);
	reg_bit_set(CANDS_CTL0_(858)+chn_offset, 0,10,f1_timing->TFC);
	reg_bit_set(CANDS_CTL0_(860)+chn_offset,16,10,f2_timing->TFC);
	reg_bit_set(CANDS_CTL0_(863)+chn_offset, 0,10,f3_timing->TFC);
	reg_bit_set(CANDS_CTL0_(865)+chn_offset,16,10,f4_timing->TFC);
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(552+65*i)+chn_offset, 0,24,timing[i]->TINIT);
		reg_bit_set(CANDS_CTL0_(549+65*i)+chn_offset, 0,24,timing[i]->TINIT3);
		reg_bit_set(CANDS_CTL0_(550+65*i)+chn_offset, 0,24,timing[i]->TINIT4);
		reg_bit_set(CANDS_CTL0_(551+65*i)+chn_offset, 0,24,timing[i]->TINIT5);
		reg_bit_set(CANDS_CTL0_(549+65*i)+chn_offset,24, 8,timing[i]->TMOD);
		reg_bit_set(CANDS_CTL0_(550+65*i)+chn_offset,24, 5,timing[i]->TMRD);
	}
	#else
	//TINIT
	reg_bit_set(CANDS_CTL0_(552)+chn_offset, 0,24,f0_timing->TINIT);
	reg_bit_set(CANDS_CTL0_(617)+chn_offset, 0,24,f1_timing->TINIT);
	reg_bit_set(CANDS_CTL0_(682)+chn_offset, 0,24,f2_timing->TINIT);
	reg_bit_set(CANDS_CTL0_(747)+chn_offset, 0,24,f3_timing->TINIT);//bac 0xa0
	reg_bit_set(CANDS_CTL0_(812)+chn_offset, 0,24,f4_timing->TINIT);
    //TINIT3
	reg_bit_set(CANDS_CTL0_(549)+chn_offset, 0,24,f0_timing->TINIT3);
	reg_bit_set(CANDS_CTL0_(614)+chn_offset, 0,24,f1_timing->TINIT3);
	reg_bit_set(CANDS_CTL0_(679)+chn_offset, 0,24,f2_timing->TINIT3);
	reg_bit_set(CANDS_CTL0_(744)+chn_offset, 0,24,f3_timing->TINIT3);
	reg_bit_set(CANDS_CTL0_(809)+chn_offset, 0,24,f4_timing->TINIT3);
	//TINIT4
	reg_bit_set(CANDS_CTL0_(550)+chn_offset, 0,24,f0_timing->TINIT4);
	reg_bit_set(CANDS_CTL0_(615)+chn_offset, 0,24,f1_timing->TINIT4);
	reg_bit_set(CANDS_CTL0_(680)+chn_offset, 0,24,f2_timing->TINIT4);
	reg_bit_set(CANDS_CTL0_(745)+chn_offset, 0,24,f3_timing->TINIT4);
	reg_bit_set(CANDS_CTL0_(810)+chn_offset, 0,24,f4_timing->TINIT4);
    //TINIT5
	reg_bit_set(CANDS_CTL0_(551)+chn_offset, 0,24,f0_timing->TINIT5);
	reg_bit_set(CANDS_CTL0_(616)+chn_offset, 0,24,f1_timing->TINIT5);
	reg_bit_set(CANDS_CTL0_(681)+chn_offset, 0,24,f2_timing->TINIT5);
	reg_bit_set(CANDS_CTL0_(746)+chn_offset, 0,24,f3_timing->TINIT5);
	reg_bit_set(CANDS_CTL0_(811)+chn_offset, 0,24,f4_timing->TINIT5);
    //TMOD
	reg_bit_set(CANDS_CTL0_(549)+chn_offset,24, 8,f0_timing->TMOD);
	reg_bit_set(CANDS_CTL0_(614)+chn_offset,24, 8,f1_timing->TMOD);
	reg_bit_set(CANDS_CTL0_(679)+chn_offset,24, 8,f2_timing->TMOD);
	reg_bit_set(CANDS_CTL0_(744)+chn_offset,24, 8,f3_timing->TMOD);//ba0 0xa
	reg_bit_set(CANDS_CTL0_(809)+chn_offset,24, 8,f4_timing->TMOD);
	//TMRD
	reg_bit_set(CANDS_CTL0_(550)+chn_offset,24, 5,f0_timing->TMRD);
	reg_bit_set(CANDS_CTL0_(615)+chn_offset,24, 5,f1_timing->TMRD);
	reg_bit_set(CANDS_CTL0_(680)+chn_offset,24, 5,f2_timing->TMRD);
	reg_bit_set(CANDS_CTL0_(745)+chn_offset,24, 5,f3_timing->TMRD);
	reg_bit_set(CANDS_CTL0_(810)+chn_offset,24, 5,f4_timing->TMRD);
	#endif
    //TMRR
	reg_bit_set(CANDS_CTL0_(20)+chn_offset, 0, 4,f0_timing->TMRR);
    //TMRRI
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(551+65*i)+chn_offset, 24, 8,timing[i]->TMRRI);
		reg_bit_set(CANDS_CTL0_(552+65*i)+chn_offset, 24, 5,timing[i]->TMRWCKEL);
		reg_bit_set(CANDS_CTL0_(548+65*i)+chn_offset, 8,  5,timing[i]->TMRZ);
		reg_bit_set(CANDS_CTL0_(548+65*i)+chn_offset, 16, 16,timing[i]->TPDEX);
	}
	#else
	reg_bit_set(CANDS_CTL0_(551)+chn_offset, 24, 8,f0_timing->TMRRI);
	reg_bit_set(CANDS_CTL0_(616)+chn_offset, 24, 8,f1_timing->TMRRI);
	reg_bit_set(CANDS_CTL0_(681)+chn_offset, 24, 8,f2_timing->TMRRI);
	reg_bit_set(CANDS_CTL0_(746)+chn_offset, 24, 8,f3_timing->TMRRI);
	reg_bit_set(CANDS_CTL0_(811)+chn_offset, 24, 8,f4_timing->TMRRI);
	//TMRWCKEL
	reg_bit_set(CANDS_CTL0_(552)+chn_offset,24, 5,f0_timing->TMRWCKEL);
	reg_bit_set(CANDS_CTL0_(617)+chn_offset,24, 5,f1_timing->TMRWCKEL);
	reg_bit_set(CANDS_CTL0_(682)+chn_offset,24, 5,f2_timing->TMRWCKEL);
	reg_bit_set(CANDS_CTL0_(747)+chn_offset,24, 5,f3_timing->TMRWCKEL);
	reg_bit_set(CANDS_CTL0_(812)+chn_offset,24, 5,f4_timing->TMRWCKEL);
	//TMRZ
	reg_bit_set(CANDS_CTL0_(548)+chn_offset, 8, 5,f0_timing->TMRZ);
	reg_bit_set(CANDS_CTL0_(613)+chn_offset, 8, 5,f1_timing->TMRZ);
	reg_bit_set(CANDS_CTL0_(678)+chn_offset, 8, 5,f2_timing->TMRZ);
	reg_bit_set(CANDS_CTL0_(743)+chn_offset, 8, 5,f3_timing->TMRZ);
	reg_bit_set(CANDS_CTL0_(808)+chn_offset, 8, 5,f4_timing->TMRZ);
	//TPDEX
	reg_bit_set(CANDS_CTL0_(548)+chn_offset,16,16,f0_timing->TPDEX);
	reg_bit_set(CANDS_CTL0_(613)+chn_offset,16,16,f1_timing->TPDEX);
	reg_bit_set(CANDS_CTL0_(678)+chn_offset,16,16,f2_timing->TPDEX);
	reg_bit_set(CANDS_CTL0_(743)+chn_offset,16,16,f3_timing->TPDEX);
	reg_bit_set(CANDS_CTL0_(808)+chn_offset,16,16,f4_timing->TPDEX);
	#endif
	//TPPD
	reg_bit_set(CANDS_CTL0_(21)+chn_offset,8,3,f0_timing->TPPD);
	//TRAS_MAX
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(553+65*i)+chn_offset, 0,17,timing[i]->TRAS_MAX);
		reg_bit_set(CANDS_CTL0_(554+65*i)+chn_offset,24, 8,timing[i]->TRAS_MIN);
		reg_bit_set(CANDS_CTL0_(554+65*i)+chn_offset,16, 8,timing[i]->TRC);
		reg_bit_set(CANDS_CTL0_(554+65*i)+chn_offset, 8, 8,timing[i]->TRCD);
		reg_bit_set(CANDS_CTL0_(555+65*i)+chn_offset,16,16,timing[i]->TREF);
	}
	#else
	reg_bit_set(CANDS_CTL0_(553)+chn_offset, 0,17,f0_timing->TRAS_MAX);
	reg_bit_set(CANDS_CTL0_(618)+chn_offset, 0,17,f1_timing->TRAS_MAX);
	reg_bit_set(CANDS_CTL0_(683)+chn_offset, 0,17,f2_timing->TRAS_MAX);
	reg_bit_set(CANDS_CTL0_(748)+chn_offset, 0,17,f3_timing->TRAS_MAX);
	reg_bit_set(CANDS_CTL0_(813)+chn_offset, 0,17,f4_timing->TRAS_MAX);
	//TRAS_MIN
	reg_bit_set(CANDS_CTL0_(554)+chn_offset,24, 8,f0_timing->TRAS_MIN);
	reg_bit_set(CANDS_CTL0_(619)+chn_offset,24, 8,f1_timing->TRAS_MIN);
	reg_bit_set(CANDS_CTL0_(684)+chn_offset,24, 8,f2_timing->TRAS_MIN);
	reg_bit_set(CANDS_CTL0_(749)+chn_offset,24, 8,f3_timing->TRAS_MIN);  //bb4 0x22
	reg_bit_set(CANDS_CTL0_(814)+chn_offset,24, 8,f4_timing->TRAS_MIN);
    //TRC
	reg_bit_set(CANDS_CTL0_(554)+chn_offset,16, 8,f0_timing->TRC);
	reg_bit_set(CANDS_CTL0_(619)+chn_offset,16, 8,f1_timing->TRC);
	reg_bit_set(CANDS_CTL0_(684)+chn_offset,16, 8,f2_timing->TRC);
	reg_bit_set(CANDS_CTL0_(749)+chn_offset,16, 8,f3_timing->TRC); //bb4 0x31
	reg_bit_set(CANDS_CTL0_(814)+chn_offset,16, 8,f4_timing->TRC);
	//TRCD
	reg_bit_set(CANDS_CTL0_(554)+chn_offset, 8, 8,f0_timing->TRCD);
	reg_bit_set(CANDS_CTL0_(619)+chn_offset, 8, 8,f1_timing->TRCD);
	reg_bit_set(CANDS_CTL0_(684)+chn_offset, 8, 8,f2_timing->TRCD);
	reg_bit_set(CANDS_CTL0_(749)+chn_offset, 8, 8,f3_timing->TRCD);//bb4 0x0f
	reg_bit_set(CANDS_CTL0_(814)+chn_offset, 8, 8,f4_timing->TRCD);
    //TREF
	reg_bit_set(CANDS_CTL0_(555)+chn_offset,16,16,f0_timing->TREF);
	reg_bit_set(CANDS_CTL0_(620)+chn_offset,16,16,f1_timing->TREF);
	reg_bit_set(CANDS_CTL0_(685)+chn_offset,16,16,f2_timing->TREF);
	reg_bit_set(CANDS_CTL0_(750)+chn_offset,16,16,f3_timing->TREF);//bb8 0xc28
	reg_bit_set(CANDS_CTL0_(815)+chn_offset,16,16,f4_timing->TREF);
	#endif
	//TREF_INTERVAL
	reg_bit_set(CANDS_CTL0_(118)+chn_offset, 0,16,f0_timing->TREF_INTERVAL);
	//TRFC
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(555+65*i)+chn_offset, 0,10,timing[i]->TRFC);
		__raw_writel(CANDS_CTL0_(572+65*i)+chn_offset, (timing[i]->TRP_AB<<24)+(timing[i]->TRP_AB<<16)+(timing[i]->TRP_AB<<8)+timing[i]->TRP_AB);
		__raw_writel(CANDS_CTL0_(573+65*i)+chn_offset, (timing[i]->TRP_AB<<24)+(timing[i]->TRP_AB<<16)+(timing[i]->TRP_AB<<8)+timing[i]->TRP_AB);
		reg_bit_set(CANDS_CTL0_(554+65*i)+chn_offset, 0, 8,timing[i]->TRP);
		reg_bit_set(CANDS_CTL0_(556+65*i)+chn_offset, 8, 8,timing[i]->TRRD);
	}
	#else
	reg_bit_set(CANDS_CTL0_(555)+chn_offset, 0,10,f0_timing->TRFC);
	reg_bit_set(CANDS_CTL0_(620)+chn_offset, 0,10,f1_timing->TRFC);
	reg_bit_set(CANDS_CTL0_(685)+chn_offset, 0,10,f2_timing->TRFC);
	reg_bit_set(CANDS_CTL0_(750)+chn_offset, 0,10,f3_timing->TRFC);
	reg_bit_set(CANDS_CTL0_(815)+chn_offset, 0,10,f4_timing->TRFC);
    //TRP_AB
	__raw_writel(CANDS_CTL0_(572)+chn_offset, (f0_timing->TRP_AB<<24)+(f0_timing->TRP_AB<<16)+(f0_timing->TRP_AB<<8)+f0_timing->TRP_AB);
	__raw_writel(CANDS_CTL0_(573)+chn_offset, (f0_timing->TRP_AB<<24)+(f0_timing->TRP_AB<<16)+(f0_timing->TRP_AB<<8)+f0_timing->TRP_AB);

	__raw_writel(CANDS_CTL0_(637)+chn_offset, (f1_timing->TRP_AB<<24)+(f1_timing->TRP_AB<<16)+(f1_timing->TRP_AB<<8)+f1_timing->TRP_AB);
	__raw_writel(CANDS_CTL0_(638)+chn_offset, (f1_timing->TRP_AB<<24)+(f1_timing->TRP_AB<<16)+(f1_timing->TRP_AB<<8)+f1_timing->TRP_AB);

	__raw_writel(CANDS_CTL0_(702)+chn_offset, (f2_timing->TRP_AB<<24)+(f2_timing->TRP_AB<<16)+(f2_timing->TRP_AB<<8)+f2_timing->TRP_AB);
	__raw_writel(CANDS_CTL0_(703)+chn_offset, (f2_timing->TRP_AB<<24)+(f2_timing->TRP_AB<<16)+(f2_timing->TRP_AB<<8)+f2_timing->TRP_AB);

	__raw_writel(CANDS_CTL0_(767)+chn_offset, (f3_timing->TRP_AB<<24)+(f3_timing->TRP_AB<<16)+(f3_timing->TRP_AB<<8)+f3_timing->TRP_AB);
	__raw_writel(CANDS_CTL0_(768)+chn_offset, (f3_timing->TRP_AB<<24)+(f3_timing->TRP_AB<<16)+(f3_timing->TRP_AB<<8)+f3_timing->TRP_AB);

	__raw_writel(CANDS_CTL0_(832)+chn_offset, (f4_timing->TRP_AB<<24)+(f4_timing->TRP_AB<<16)+(f4_timing->TRP_AB<<8)+f4_timing->TRP_AB);
	__raw_writel(CANDS_CTL0_(833)+chn_offset, (f4_timing->TRP_AB<<24)+(f4_timing->TRP_AB<<16)+(f4_timing->TRP_AB<<8)+f4_timing->TRP_AB);
    //TRP
	reg_bit_set(CANDS_CTL0_(554)+chn_offset, 0, 8,f0_timing->TRP);
	reg_bit_set(CANDS_CTL0_(619)+chn_offset, 0, 8,f1_timing->TRP);
	reg_bit_set(CANDS_CTL0_(684)+chn_offset, 0, 8,f2_timing->TRP);
	reg_bit_set(CANDS_CTL0_(749)+chn_offset, 0, 8,f3_timing->TRP);
	reg_bit_set(CANDS_CTL0_(814)+chn_offset, 0, 8,f4_timing->TRP);
	//TRRD
	reg_bit_set(CANDS_CTL0_(556)+chn_offset, 8, 8,f0_timing->TRRD);
	reg_bit_set(CANDS_CTL0_(621)+chn_offset, 8, 8,f1_timing->TRRD);
	reg_bit_set(CANDS_CTL0_(686)+chn_offset, 8, 8,f2_timing->TRRD);
	reg_bit_set(CANDS_CTL0_(751)+chn_offset, 8, 8,f3_timing->TRRD);
	reg_bit_set(CANDS_CTL0_(816)+chn_offset, 8, 8,f4_timing->TRRD);
	#endif
    //TRST_PWRON
	__raw_writel(CANDS_CTL0_(18)+chn_offset, f0_timing->TRST_PWRON);
    //TRTP
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(556+65*i)+chn_offset, 0, 4,timing[i]->TRTP);
		reg_bit_set(CANDS_CTL0_(556+65*i)+chn_offset,24, 8,timing[i]->TSR);
	}
	#else
	reg_bit_set(CANDS_CTL0_(556)+chn_offset, 0, 4,f0_timing->TRTP);
	reg_bit_set(CANDS_CTL0_(621)+chn_offset, 0, 4,f1_timing->TRTP);
	reg_bit_set(CANDS_CTL0_(686)+chn_offset, 0, 4,f2_timing->TRTP);
	reg_bit_set(CANDS_CTL0_(751)+chn_offset, 0, 4,f3_timing->TRTP);
	reg_bit_set(CANDS_CTL0_(816)+chn_offset, 0, 4,f4_timing->TRTP);
    	//TSR
	reg_bit_set(CANDS_CTL0_(556)+chn_offset,24, 8,f0_timing->TSR);
	reg_bit_set(CANDS_CTL0_(621)+chn_offset,24, 8,f1_timing->TSR);
	reg_bit_set(CANDS_CTL0_(686)+chn_offset,24, 8,f2_timing->TSR);
	reg_bit_set(CANDS_CTL0_(751)+chn_offset,24, 8,f3_timing->TSR);
	reg_bit_set(CANDS_CTL0_(816)+chn_offset,24, 8,f4_timing->TSR);
	#endif
    	//TVRCG_DISABLE
    	reg_bit_set(CANDS_CTL0_(855)+chn_offset, 0,10,f0_timing->TVRCG_DISABLE);
	reg_bit_set(CANDS_CTL0_(857)+chn_offset,16,10,f1_timing->TVRCG_DISABLE);
	reg_bit_set(CANDS_CTL0_(860)+chn_offset, 0,10,f2_timing->TVRCG_DISABLE);
	reg_bit_set(CANDS_CTL0_(862)+chn_offset,16,10,f3_timing->TVRCG_DISABLE);
	reg_bit_set(CANDS_CTL0_(865)+chn_offset, 0,10,f4_timing->TVRCG_DISABLE);
    	//TVRCG_ENABLE
    	reg_bit_set(CANDS_CTL0_(854)+chn_offset, 8,10,f0_timing->TVRCG_ENABLE);
	reg_bit_set(CANDS_CTL0_(857)+chn_offset, 0,10,f1_timing->TVRCG_ENABLE);
	reg_bit_set(CANDS_CTL0_(859)+chn_offset,16,10,f2_timing->TVRCG_ENABLE);
	reg_bit_set(CANDS_CTL0_(862)+chn_offset, 0,10,f3_timing->TVRCG_ENABLE);
	reg_bit_set(CANDS_CTL0_(864)+chn_offset,16,10,f4_timing->TVRCG_ENABLE);
    	//TVREF_LONG
    	reg_bit_set(CANDS_CTL0_(856)+chn_offset,16,16,f0_timing->TVREF_LONG);
	reg_bit_set(CANDS_CTL0_(859)+chn_offset, 0,16,f1_timing->TVREF_LONG);
	reg_bit_set(CANDS_CTL0_(861)+chn_offset,16,16,f2_timing->TVREF_LONG);
	reg_bit_set(CANDS_CTL0_(864)+chn_offset, 0,16,f3_timing->TVREF_LONG);
	reg_bit_set(CANDS_CTL0_(866)+chn_offset,16,16,f4_timing->TVREF_LONG);
    //TWR
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(558+65*i)+chn_offset,24, 6,timing[i]->TWR);
		reg_bit_set(CANDS_CTL0_(556+65*i)+chn_offset,16, 6,timing[i]->TWTR);
		reg_bit_set(CANDS_CTL0_(557+65*i)+chn_offset,16,16,timing[i]->TXSNR);
		reg_bit_set(CANDS_CTL0_(557+65*i)+chn_offset, 0,16,timing[i]->TXSR);
		reg_bit_set(CANDS_CTL0_(558+65*i)+chn_offset, 0,12,timing[i]->TZQCAL);
		reg_bit_set(CANDS_CTL0_(559+65*i)+chn_offset,24, 4,timing[i]->TZQCKE);
		reg_bit_set(CANDS_CTL0_(558+65*i)+chn_offset,16, 6,timing[i]->TZQLAT);
	}
	#else
    reg_bit_set(CANDS_CTL0_(558)+chn_offset,24, 6,f0_timing->TWR);
	reg_bit_set(CANDS_CTL0_(623)+chn_offset,24, 6,f1_timing->TWR);
	reg_bit_set(CANDS_CTL0_(688)+chn_offset,24, 6,f2_timing->TWR);
	reg_bit_set(CANDS_CTL0_(753)+chn_offset,24, 6,f3_timing->TWR);
	reg_bit_set(CANDS_CTL0_(818)+chn_offset,24, 6,f4_timing->TWR);
    //TWTR
    reg_bit_set(CANDS_CTL0_(556)+chn_offset,16, 6,f0_timing->TWTR);
	reg_bit_set(CANDS_CTL0_(621)+chn_offset,16, 6,f1_timing->TWTR);
	reg_bit_set(CANDS_CTL0_(686)+chn_offset,16, 6,f2_timing->TWTR);
	reg_bit_set(CANDS_CTL0_(751)+chn_offset,16, 6,f3_timing->TWTR);
	reg_bit_set(CANDS_CTL0_(816)+chn_offset,16, 6,f4_timing->TWTR);
    //TXSNR
    reg_bit_set(CANDS_CTL0_(557)+chn_offset,16,16,f0_timing->TXSNR);
	reg_bit_set(CANDS_CTL0_(622)+chn_offset,16,16,f1_timing->TXSNR);
	reg_bit_set(CANDS_CTL0_(687)+chn_offset,16,16,f2_timing->TXSNR);
	reg_bit_set(CANDS_CTL0_(752)+chn_offset,16,16,f3_timing->TXSNR);
	reg_bit_set(CANDS_CTL0_(817)+chn_offset,16,16,f4_timing->TXSNR);
    //TXSR
    reg_bit_set(CANDS_CTL0_(557)+chn_offset, 0,16,f0_timing->TXSR);
	reg_bit_set(CANDS_CTL0_(622)+chn_offset, 0,16,f1_timing->TXSR);
	reg_bit_set(CANDS_CTL0_(687)+chn_offset, 0,16,f2_timing->TXSR);
	reg_bit_set(CANDS_CTL0_(752)+chn_offset, 0,16,f3_timing->TXSR);
	reg_bit_set(CANDS_CTL0_(817)+chn_offset, 0,16,f4_timing->TXSR);
    //TZQCAL
    reg_bit_set(CANDS_CTL0_(558)+chn_offset, 0,12,f0_timing->TZQCAL);
	reg_bit_set(CANDS_CTL0_(623)+chn_offset, 0,12,f1_timing->TZQCAL);
	reg_bit_set(CANDS_CTL0_(688)+chn_offset, 0,12,f2_timing->TZQCAL);
	reg_bit_set(CANDS_CTL0_(753)+chn_offset, 0,12,f3_timing->TZQCAL);// bc4 0x320
	reg_bit_set(CANDS_CTL0_(818)+chn_offset, 0,12,f4_timing->TZQCAL);
    //TZQCKE
    reg_bit_set(CANDS_CTL0_(559)+chn_offset,24, 4,f0_timing->TZQCKE);
	reg_bit_set(CANDS_CTL0_(624)+chn_offset,24, 4,f1_timing->TZQCKE);
	reg_bit_set(CANDS_CTL0_(689)+chn_offset,24, 4,f2_timing->TZQCKE);
	reg_bit_set(CANDS_CTL0_(754)+chn_offset,24, 4,f3_timing->TZQCKE);//bc8 0x00
	reg_bit_set(CANDS_CTL0_(819)+chn_offset,24, 4,f4_timing->TZQCKE);
    	//TZQLAT
    	reg_bit_set(CANDS_CTL0_(558)+chn_offset,16, 6,f0_timing->TZQLAT);
	reg_bit_set(CANDS_CTL0_(623)+chn_offset,16, 6,f1_timing->TZQLAT);
	reg_bit_set(CANDS_CTL0_(688)+chn_offset,16, 6,f2_timing->TZQLAT);
	reg_bit_set(CANDS_CTL0_(753)+chn_offset,16, 6,f3_timing->TZQLAT);// bc4 0x18
	reg_bit_set(CANDS_CTL0_(818)+chn_offset,16, 6,f4_timing->TZQLAT);
	#endif
    	//WLDQSEN
	reg_bit_set(CANDS_CTL0_(363)+chn_offset,16, 6,f0_timing->WLDQSEN);
	//WLMRD
	reg_bit_set(CANDS_CTL0_(363)+chn_offset,24, 6,f0_timing->WLMRD);

	return;
}

void cands_ctl_addrmap_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{

	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 cs_val0 = 0;
	uint32 cs_val1 = 0x200;

	uint32 cs_msk0 = 0x1ff;
	uint32 cs_msk1 = 0x1ff;

	uint32 cs_val2to7 = 0xffff;
	uint32 cs_msk2to7 = 0xffff;

	uint32 bank_diff = 0;
	uint32 row_diff = 0;
	uint32 col_diff = 0;

	uint32 i = 0;
	#ifdef CODE_SIZE_OPTIMIZE
	uint32 val;
	#endif

	if(IS_LPDDR3(ddr_type))
	{
		switch(ddr_type)
		{
			case DRAM_LPDDR3_1CS_4G_X32:
			case DRAM_LPDDR3_2CS_8G_X32:
			    cs_msk0 = 0x1ff; cs_val0 = 0x0;
			    cs_msk1 = 0x1ff; cs_val1 = 0x200;
				row_diff = 2; col_diff = 2;
			    break;
            case DRAM_LPDDR3_1CS_6G_X32:
            case DRAM_LPDDR3_2CS_12G_X32:
				cs_msk0 = 0x3ff; cs_val0 = 0x0;
			    cs_msk1 = 0x3ff; cs_val1 = 0x400;
				row_diff = 1; col_diff = 2;
			    break;
            case DRAM_LPDDR3_1CS_8G_X32:
            case DRAM_LPDDR3_2CS_16G_X32:
				cs_msk0 = 0x3ff; cs_val0 = 0x0;
			    cs_msk1 = 0x3ff; cs_val1 = 0x400;
				row_diff = 1; col_diff = 2;
			    break;
		case DRAM_LPDDR3_1CS_8G_X16X2:
		case DRAM_LPDDR3_2CS_16G_X32_X16X4:
                cs_msk0 = 0x3ff; cs_val0 = 0x0;
                cs_msk1 = 0x3ff; cs_val1 = 0x400;
				row_diff = 2; col_diff = 1;
                break;
			default:   while(1); //invalid density
		}
	}
	else if(IS_LPDDR4(ddr_type)) //lpddr4
	{
	   switch(ddr_type)
	   {
	      case DRAM_LPDDR4_1CS_4G_X32:
		  case DRAM_LPDDR4_2CS_8G_X32:
		  	cs_msk0 = 0x1ff; cs_val0 = 0x0;
			cs_msk1 = 0x1ff; cs_val1 = 0x200;
			row_diff = 2; col_diff = 2;
			break;
		  case DRAM_LPDDR4_1CS_6G_X32:
		  case DRAM_LPDDR4_2CS_12G_X32:
		  	cs_msk0 = 0x3ff; cs_val0 = 0x0;
			cs_msk1 = 0x3ff; cs_val1 = 0x400;
			row_diff = 1; col_diff = 2;
			break;
		  case DRAM_LPDDR4_1CS_8G_X32:
		  case DRAM_LPDDR4_2CS_16G_X32:
			cs_msk0 = 0x3ff; cs_val0 = 0x0;
			cs_msk1 = 0x3ff; cs_val1 = 0x400;
			row_diff = 1; col_diff = 2;
			break;
		  case DRAM_LPDDR4_1CS_12G_X32:
		  case DRAM_LPDDR4_2CS_24G_X32:
		  case DRAM_LPDDR4_1CS_6G_X16:
			cs_msk0 = 0x7ff; cs_val0 = 0x0;
			cs_msk1 = 0x7ff; cs_val1 = 0x800;
			row_diff = 0; col_diff = 2;
			break;
		  case DRAM_LPDDR4_1CS_16G_X32:
		  case DRAM_LPDDR4_2CS_32G_X32:
		  	cs_msk0 = 0x7ff; cs_val0 = 0x0;
			cs_msk1 = 0x7ff; cs_val1 = 0x800;
			row_diff = 0; col_diff = 2;
			break;
		  	default: while(1); //invalid density
	   }

	}

    //cs_value
	__raw_writel(CANDS_CTL0_(300)+chn_offset, (cs_val1<<16) | cs_val0);
#ifdef CODE_SIZE_OPTIMIZE
	val = (cs_val2to7<<16) | cs_val2to7;
	for(i =0;i < 3; i++) {
		__raw_writel(CANDS_CTL0_(301+i)+chn_offset, val);
	}
#else
	__raw_writel(CANDS_CTL0_(301)+chn_offset, (cs_val2to7<<16) | cs_val2to7);
	__raw_writel(CANDS_CTL0_(302)+chn_offset, (cs_val2to7<<16) | cs_val2to7);
	__raw_writel(CANDS_CTL0_(303)+chn_offset, (cs_val2to7<<16) | cs_val2to7);
#endif
    //cs_mask
	__raw_writel(CANDS_CTL0_(304)+chn_offset, (cs_msk1<<16) | cs_msk0);
#ifdef CODE_SIZE_OPTIMIZE
	val = (cs_msk2to7<<16) | cs_msk2to7;
	for(i =0;i < 3; i++) {
		__raw_writel(CANDS_CTL0_(305+i)+chn_offset, val);
	}
#else
	__raw_writel(CANDS_CTL0_(305)+chn_offset, (cs_msk2to7<<16) | cs_msk2to7);
	__raw_writel(CANDS_CTL0_(306)+chn_offset, (cs_msk2to7<<16) | cs_msk2to7);
	__raw_writel(CANDS_CTL0_(307)+chn_offset, (cs_msk2to7<<16) | cs_msk2to7);
#endif

	//bank_diff
	__raw_writel(CANDS_CTL0_(294)+chn_offset, (bank_diff<<24)|(bank_diff<<16)|(bank_diff<<8)|(bank_diff<<0));
	__raw_writel(CANDS_CTL0_(295)+chn_offset, (bank_diff<<24)|(bank_diff<<16)|(bank_diff<<8)|(bank_diff<<0));

	//row_diff
#ifdef CODE_SIZE_OPTIMIZE
	val = (row_diff<<24)|(row_diff<<16)|(row_diff<<8)|(row_diff<<0);
	for(i =0;i < 2; i++) {
		__raw_writel(CANDS_CTL0_(296+i)+chn_offset, val);
	}
#else
	__raw_writel(CANDS_CTL0_(296)+chn_offset, (row_diff<<24)|(row_diff<<16)|(row_diff<<8)|(row_diff<<0));
	__raw_writel(CANDS_CTL0_(297)+chn_offset, (row_diff<<24)|(row_diff<<16)|(row_diff<<8)|(row_diff<<0));
#endif
	//col_dff
#ifdef CODE_SIZE_OPTIMIZE
	val = (col_diff<<24)|(col_diff<<16)|(col_diff<<8)|(col_diff<<0);
	for(i =0;i < 2; i++) {
		__raw_writel(CANDS_CTL0_(298+i)+chn_offset, val);
	}
#else
	__raw_writel(CANDS_CTL0_(298)+chn_offset, (col_diff<<24)|(col_diff<<16)|(col_diff<<8)|(col_diff<<0));
	__raw_writel(CANDS_CTL0_(299)+chn_offset, (col_diff<<24)|(col_diff<<16)|(col_diff<<8)|(col_diff<<0));
#endif

}


void cands_ctl_basicmode_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{

	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//memory type, lpddr3 or lpddr4 ?
	reg_bit_set(CANDS_CTL0_(0)+chn_offset,8,4,islp3?0x7:0xb);

	//cs_map, dsiable unused cs
	//#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_CTL0_(312)+chn_offset,24,8,IS_2CS(ddr_type)?3:1);
	//#else
	//reg_bit_set(CANDS_CTL0_(312)+chn_offset,24,8,3);
	//#endif

	//dram_clk_disable, disable unused cs clock
	//reg_bit_set(CANDS_CTL0_(452)+chn_offset,24,8,IS_2CS(ddr_type)?0xfc:0xfe);
	reg_bit_set(CANDS_CTL0_(452)+chn_offset,24,8,0xfc);


	//aprebit
	reg_bit_set(CANDS_CTL0_(308)+chn_offset,16,4,islp3?0xa:0xb);  //Defines the location of the auto pre-charge bit in the DRAM address in decimal encoding

	//auto-refresh threshold
	reg_bit_set(CANDS_CTL0_(249)+chn_offset,16,5,0x15);  //aref_high_threshold
	reg_bit_set(CANDS_CTL0_(250)+chn_offset, 0,5,0x10);  //aref_max_credit
	reg_bit_set(CANDS_CTL0_(249)+chn_offset,24,5,0x18);  //aref_max_deficit
	reg_bit_set(CANDS_CTL0_(249)+chn_offset, 8,5,0x12);  //aref_norm_threshold

	//burst length--bstlen
	reg_bit_set(CANDS_CTL0_(23)+chn_offset, 8,5,islp3?3:4);   //3:bl8  4:bl16  5:bl32

	//concurrentap,  allow one bank to be auto pre-charged while another bank is reading or writing, memory should support
	reg_bit_set(CANDS_CTL0_(23)+chn_offset,24,1,0);   //?????

	//reversed, spec said to set to 3
	reg_bit_set(CANDS_CTL0_(24)+chn_offset,8,3,3);

	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(316)+chn_offset,16,1,1);

	//tref_enable
	reg_bit_set(CANDS_CTL0_(83)+chn_offset,8,1,1);

	//dfibus_boot_freq
	reg_bit_set(CANDS_CTL0_(17)+chn_offset,16,5,FN_CTL_BOOT);
	//dfibus_freq_init
	reg_bit_set(CANDS_CTL0_(17)+chn_offset,8,3,fn_ctl_target);
	//dfibus_freq_fn
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_CTL0_(520)+chn_offset,24,5,0);
	reg_bit_set(CANDS_CTL0_(585)+chn_offset,24,5,1);
	reg_bit_set(CANDS_CTL0_(650)+chn_offset,24,5,2);
	reg_bit_set(CANDS_CTL0_(715)+chn_offset,24,5,3);
	reg_bit_set(CANDS_CTL0_(780)+chn_offset,24,5,4);
	#else
	reg_bit_set(CANDS_CTL0_(520)+chn_offset,24,5,1);
	reg_bit_set(CANDS_CTL0_(585)+chn_offset,24,5,2);
	reg_bit_set(CANDS_CTL0_(650)+chn_offset,24,5,3);
	reg_bit_set(CANDS_CTL0_(715)+chn_offset,24,5,4);
	reg_bit_set(CANDS_CTL0_(780)+chn_offset,24,5,0);
    	#endif
	//en_1t_timing,   only for lp3
    	reg_bit_set(CANDS_CTL0_(508)+chn_offset,16,2,3); //2T timing on whale2?? should check

	//disable_memory_masked_write  0:allow mask write   1:disable make write, only for lp4    ?????
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_CTL0_(508)+chn_offset,24,1,1);
	#else
	reg_bit_set(CANDS_CTL0_(508)+chn_offset,24,1,0);
	#endif

    //enable_quick_srefresh
    reg_bit_set(CANDS_CTL0_(115)+chn_offset,16,1,1);

	//optimal_rmodw_en  ????????need check with asic
    reg_bit_set(CANDS_CTL0_(82)+chn_offset, 0, 1, 1);


    //long_count_mask
    reg_bit_set(CANDS_CTL0_(249)+chn_offset,0,5,0); //0:1024 clock  0x10:512 clock  0x18:256 clock   0x1c:128 clock ...

    //memdata_ratio_X
    reg_bit_set(CANDS_CTL0_(313)+chn_offset, 8,3,islp3?0:1);
    reg_bit_set(CANDS_CTL0_(313)+chn_offset,16,3,islp3?0:1);
    reg_bit_set(CANDS_CTL0_(313)+chn_offset,24,3,islp3?0:1);
    reg_bit_set(CANDS_CTL0_(314)+chn_offset, 0,3,islp3?0:1);
    reg_bit_set(CANDS_CTL0_(314)+chn_offset, 8,3,islp3?0:1);
    reg_bit_set(CANDS_CTL0_(314)+chn_offset,16,3,islp3?0:1);
    reg_bit_set(CANDS_CTL0_(314)+chn_offset,24,3,islp3?0:1);
    reg_bit_set(CANDS_CTL0_(315)+chn_offset, 0,3,islp3?0:1);

    //no_memory_dm, Indicates that the external DRAM does not support DM masking. ??????
    reg_bit_set(CANDS_CTL0_(24)+chn_offset, 16,1,0);

    //no_phy_ind_train_init, Disables PHY independent training from executing during initialization, should check ???????
    reg_bit_set(CANDS_CTL0_(16)+chn_offset, 24,1,0);

    //phy_indep_train_mode   ????????
    reg_bit_set(CANDS_CTL0_(17)+chn_offset,  0,1,1);

    //phymstr_no_aref,Disables refreshes during the PHY master interface sequence   ??????
    reg_bit_set(CANDS_CTL0_(84)+chn_offset, 16,1,0);

    //phyupd_append_en, Enables an automatic PHY-initiated update prior to running any type of training
    reg_bit_set(CANDS_CTL0_(362)+chn_offset, 24,1,1);

    //preamble_support, Defines the read and write premble. should check when lpddr4    ????????
    reg_bit_set(CANDS_CTL0_(316)+chn_offset, 24,2,islp3?0:2);

    //rd_dbi_en, Enables controller support of the DRAM DBI feature for read data. lpddr4 only
	reg_bit_set(CANDS_CTL0_(317)+chn_offset, 16,1,islp3?0:RD_DBI_EN);

    //rd_preamble_training_en, Enables read preamble training with gate training
	reg_bit_set(CANDS_CTL0_(317)+chn_offset,  0,1, islp3?0:RD_PREAMBLE_TR_EN);

    //reduc,  Allows the same controller to be used with memories with a smaller datapath
    reg_bit_set(CANDS_CTL0_(313)+chn_offset,  0,1,IS_16BIT(ddr_type));

    //reg_dimm_enable,  Enables registered DIMM operations to control the address and command pipeline of the controller
    reg_bit_set(CANDS_CTL0_(24)+chn_offset, 24,1,0);

    //tras_lockout,  Enables tRAS lockout. tRAS lockout allows the controller to execute auto pre-charge commands before the tras_min_fN_X parameter has expired
	reg_bit_set(CANDS_CTL0_(24)+chn_offset,  0,1,0);   //????????
    //reversed
	#ifdef DRAM_LPDDR4
	reg_bit_set(CANDS_CTL0_(24)+chn_offset,  8,3,3);   //????????
	#endif

    //tverf_disable,lpddr4 only   ????????
    reg_bit_set(CANDS_CTL0_(853)+chn_offset,  8,1,islp3?0:1);

    //wr_dbi_en
    reg_bit_set(CANDS_CTL0_(317)+chn_offset,  8,1,islp3?0:WR_DBI_EN);

    //writeinterp,    Defines whether the controller can interrupt a write burst with a read command.
    reg_bit_set(CANDS_CTL0_(21)+chn_offset,  0,1,0);
	#ifdef DRAM_LPDDR4
    reg_bit_set(CANDS_CTL0_(21)+chn_offset,  24,3,2);
	#endif
    //reversed
    __raw_writel(CANDS_CTL0_(121)+chn_offset, 0x40020100);
    __raw_writel(CANDS_CTL0_(122)+chn_offset, 0x00008010);
    __raw_writel(CANDS_CTL0_(273)+chn_offset, 0x3);
}

void cands_ctl_calvl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_CTL_TIMING_T * ctl_timing,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
#else
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

	//calvl_aref_en
	reg_bit_set(CANDS_CTL0_(418)+chn_offset,8,1, 1);

    //calvl_bg_pat_0~3
	__raw_writel(CANDS_CTL0_(410)+chn_offset, 0x000aaaaa);
	__raw_writel(CANDS_CTL0_(412)+chn_offset, 0x00055555);
	__raw_writel(CANDS_CTL0_(414)+chn_offset, 0x0004cd33);
	__raw_writel(CANDS_CTL0_(416)+chn_offset, 0x000b32cc);
    //calvl_pat_0~3
	__raw_writel(CANDS_CTL0_(409)+chn_offset, 0x000556aa);
	__raw_writel(CANDS_CTL0_(411)+chn_offset, 0x000aa955);
	__raw_writel(CANDS_CTL0_(413)+chn_offset, 0x000b3133);
	__raw_writel(CANDS_CTL0_(415)+chn_offset, 0x0004cecc);


	//calvl_cs
	reg_bit_set(CANDS_CTL0_(408)+chn_offset,24,3, 0);

	//calvl_cs_map
	reg_bit_set(CANDS_CTL0_(418)+chn_offset,24,8, IS_2CS(ddr_type)?3:1);

	//calvl_en
	reg_bit_set(CANDS_CTL0_(505)+chn_offset, 8,1, CALVL_EN);

	//calvl_on_sref_exit
	reg_bit_set(CANDS_CTL0_(418)+chn_offset, 0,1, CALVL_EN_SREF);

    //calvl_periodic
    reg_bit_set(CANDS_CTL0_(417)+chn_offset,24,1, 0); //disable periodic ca training

    //calvl_resp_mask
    reg_bit_set(CANDS_CTL0_(505)+chn_offset, 0,1, 0);

    //calvl_rotate   ???? only for sw calvl ??????
    reg_bit_set(CANDS_CTL0_(418)+chn_offset,16,1, 0); //0:train all cs   1:train only one cs

    //calvl_seq_en
    reg_bit_set(CANDS_CTL0_(417)+chn_offset, 8,2, 3); //calvl pattern sequence   3:pattern 0->1->2->3->0



}

void cands_ctl_dfi_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_CTL_TIMING_T * ctl_timing,
						uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;
#else
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

	//************************dfi lvl mode****************************/
    //dfi_phy_calvl_mode, Indicates the PHY\A1\AFs support for DFI CA training
    reg_bit_set(CANDS_CTL0_(417)+chn_offset,16,1, 1);
    //dfi_phy_rdlvl_gate_mode, Indicates the DFI gate training support for the PHY
    reg_bit_set(CANDS_CTL0_(380)+chn_offset,16,1, 1);
    //dfi_phy_rdlvl_mode, Indicates the DFI data eye training support for the PHY
    reg_bit_set(CANDS_CTL0_(380)+chn_offset, 8,1, 1);
    //dfi_phy_wrlvl_mode, Indicates the DFI write leveling mode support for the PHY,lpddr3 only ????????
    reg_bit_set(CANDS_CTL0_(364)+chn_offset, 8,1, 1);


    //*************************dfi lvl timing***************************/
    //TDFI_CALVL_CAPTURE, TDFI_CALVL_CC
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		__raw_writel(CANDS_CTL0_(538+65*i)+chn_offset,(timing[i]->TDFI_CALVL_CAPTURE<<16)|timing[i]->TDFI_CALVL_CC);
	}
	#else
    __raw_writel(CANDS_CTL0_(538)+chn_offset,(f0_timing->TDFI_CALVL_CAPTURE<<16)|f0_timing->TDFI_CALVL_CC);
    __raw_writel(CANDS_CTL0_(603)+chn_offset,(f1_timing->TDFI_CALVL_CAPTURE<<16)|f1_timing->TDFI_CALVL_CC);
    __raw_writel(CANDS_CTL0_(668)+chn_offset,(f2_timing->TDFI_CALVL_CAPTURE<<16)|f2_timing->TDFI_CALVL_CC);
    __raw_writel(CANDS_CTL0_(733)+chn_offset,(f3_timing->TDFI_CALVL_CAPTURE<<16)|f3_timing->TDFI_CALVL_CC);
    __raw_writel(CANDS_CTL0_(798)+chn_offset,(f4_timing->TDFI_CALVL_CAPTURE<<16)|f4_timing->TDFI_CALVL_CC);
	#endif
    //TDFI_CALVL_EN
    reg_bit_set(CANDS_CTL0_(497)+chn_offset,16, 8,f0_timing->TDFI_CALVL_EN);
    //TDFI_CALVL_MAX
    __raw_writel(CANDS_CTL0_(504)+chn_offset,f0_timing->TDFI_CALVL_MAX);
    //TDFI_CALVL_RESP
    __raw_writel(CANDS_CTL0_(503)+chn_offset,f0_timing->TDFI_CALVL_RESP);
    //TDFI_CTRL_DELAY
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(537+65*i)+chn_offset, 8, 4,timing[i]->TDFI_CTRL_DELAY);
		__raw_writel(CANDS_CTL0_(539+65*i)+chn_offset,timing[i]->TDFI_CTRLUPD_INTERVAL);
		reg_bit_set(CANDS_CTL0_(537+65*i)+chn_offset,16,16,timing[i]->TDFI_CTRLUPD_MAX);
	}
	#else
    reg_bit_set(CANDS_CTL0_(537)+chn_offset, 8, 4,f0_timing->TDFI_CTRL_DELAY);
    reg_bit_set(CANDS_CTL0_(602)+chn_offset, 8, 4,f1_timing->TDFI_CTRL_DELAY);
    reg_bit_set(CANDS_CTL0_(667)+chn_offset, 8, 4,f2_timing->TDFI_CTRL_DELAY);
    reg_bit_set(CANDS_CTL0_(732)+chn_offset, 8, 4,f3_timing->TDFI_CTRL_DELAY);
    reg_bit_set(CANDS_CTL0_(797)+chn_offset, 8, 4,f4_timing->TDFI_CTRL_DELAY);
    //TDFI_CTRLUPD_INTERVAL
    __raw_writel(CANDS_CTL0_(539)+chn_offset,f0_timing->TDFI_CTRLUPD_INTERVAL);
    __raw_writel(CANDS_CTL0_(604)+chn_offset,f1_timing->TDFI_CTRLUPD_INTERVAL);
    __raw_writel(CANDS_CTL0_(669)+chn_offset,f2_timing->TDFI_CTRLUPD_INTERVAL);
    __raw_writel(CANDS_CTL0_(734)+chn_offset,f3_timing->TDFI_CTRLUPD_INTERVAL);
    __raw_writel(CANDS_CTL0_(799)+chn_offset,f4_timing->TDFI_CTRLUPD_INTERVAL);
    //TDFI_CTRLUPD_MAX
    reg_bit_set(CANDS_CTL0_(537)+chn_offset,16,16,f0_timing->TDFI_CTRLUPD_MAX);
    reg_bit_set(CANDS_CTL0_(602)+chn_offset,16,16,f1_timing->TDFI_CTRLUPD_MAX);
    reg_bit_set(CANDS_CTL0_(667)+chn_offset,16,16,f2_timing->TDFI_CTRLUPD_MAX);
    reg_bit_set(CANDS_CTL0_(732)+chn_offset,16,16,f3_timing->TDFI_CTRLUPD_MAX);
    reg_bit_set(CANDS_CTL0_(797)+chn_offset,16,16,f4_timing->TDFI_CTRLUPD_MAX);
	#endif
    //TDFI_CTRLUPD_MIN
    reg_bit_set(CANDS_CTL0_(453)+chn_offset, 0, 4,f0_timing->TDFI_CTRLUPD_MIN);
    //TDFI_DRAM_CLK_DISABLE
    reg_bit_set(CANDS_CTL0_(489)+chn_offset,24, 4,f0_timing->TDFI_DRAM_CLK_DISABLE);
    //TDFI_DRAM_CLK_ENABLE
    reg_bit_set(CANDS_CTL0_(490)+chn_offset, 0, 4,f0_timing->TDFI_DRAM_CLK_ENABLE);
    //TDFI_INIT_COMPLETE
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(540+65*i)+chn_offset,16,16,timing[i]->TDFI_INIT_COMPLETE);
		reg_bit_set(CANDS_CTL0_(540+65*i)+chn_offset, 8, 8,timing[i]->TDFI_INIT_START);
	}
	#else
    reg_bit_set(CANDS_CTL0_(540)+chn_offset,16,16,f0_timing->TDFI_INIT_COMPLETE);
    reg_bit_set(CANDS_CTL0_(605)+chn_offset,16,16,f1_timing->TDFI_INIT_COMPLETE);
    reg_bit_set(CANDS_CTL0_(670)+chn_offset,16,16,f2_timing->TDFI_INIT_COMPLETE);
    reg_bit_set(CANDS_CTL0_(735)+chn_offset,16,16,f3_timing->TDFI_INIT_COMPLETE);
    reg_bit_set(CANDS_CTL0_(800)+chn_offset,16,16,f4_timing->TDFI_INIT_COMPLETE);
    //TDFI_INIT_START
    reg_bit_set(CANDS_CTL0_(540)+chn_offset, 8, 8,f0_timing->TDFI_INIT_START);
    reg_bit_set(CANDS_CTL0_(605)+chn_offset, 8, 8,f1_timing->TDFI_INIT_START);
    reg_bit_set(CANDS_CTL0_(670)+chn_offset, 8, 8,f2_timing->TDFI_INIT_START);
    reg_bit_set(CANDS_CTL0_(735)+chn_offset, 8, 8,f3_timing->TDFI_INIT_START);
    reg_bit_set(CANDS_CTL0_(800)+chn_offset, 8, 8,f4_timing->TDFI_INIT_START);
	#endif
    //TDFI_LP_RESP
    reg_bit_set(CANDS_CTL0_(160)+chn_offset, 0, 3,f0_timing->TDFI_LP_RESP);
    //TDFI_PHY_RDLAT
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(540+65*i)+chn_offset, 0, 7,timing[i]->TDFI_PHY_RDLAT);
	}
	#else
    reg_bit_set(CANDS_CTL0_(540)+chn_offset, 0, 7,f0_timing->TDFI_PHY_RDLAT);
    reg_bit_set(CANDS_CTL0_(605)+chn_offset, 0, 7,f1_timing->TDFI_PHY_RDLAT);
    reg_bit_set(CANDS_CTL0_(670)+chn_offset, 0, 7,f2_timing->TDFI_PHY_RDLAT);
    reg_bit_set(CANDS_CTL0_(735)+chn_offset, 0, 7,f3_timing->TDFI_PHY_RDLAT);
    reg_bit_set(CANDS_CTL0_(800)+chn_offset, 0, 7,f4_timing->TDFI_PHY_RDLAT);
	#endif
	//TDFI_PHY_WRDATA
	reg_bit_set(CANDS_CTL0_(505)+chn_offset,24, 3,f0_timing->TDFI_PHY_WRDATA);
	//TDFI_PHY_WRLAT
	reg_bit_set(CANDS_CTL0_(450)+chn_offset,24, 7,f0_timing->TDFI_PHY_WRLAT);

    //TDFI_PHYMSTR_MAX
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(541+65*i)+chn_offset, 0,16,timing[i]->TDFI_PHYMSTR_MAX);
		reg_bit_set(CANDS_CTL0_(541+65*i)+chn_offset,16,16,timing[i]->TDFI_PHYMSTR_RESP);
		reg_bit_set(CANDS_CTL0_(542+65*i)+chn_offset, 0,16,timing[i]->TDFI_PHYUPD_RESP);
		__raw_writel(CANDS_CTL0_(543+65*i)+chn_offset,timing[i]->TDFI_PHYUPD_TYPE0);
		__raw_writel(CANDS_CTL0_(544+65*i)+chn_offset,timing[i]->TDFI_PHYUPD_TYPE1);
		__raw_writel(CANDS_CTL0_(545+65*i)+chn_offset,timing[i]->TDFI_PHYUPD_TYPE2);
		__raw_writel(CANDS_CTL0_(546+65*i)+chn_offset,timing[i]->TDFI_PHYUPD_TYPE3);
	}
	#else
    reg_bit_set(CANDS_CTL0_(541)+chn_offset, 0,16,f0_timing->TDFI_PHYMSTR_MAX);
    reg_bit_set(CANDS_CTL0_(606)+chn_offset, 0,16,f1_timing->TDFI_PHYMSTR_MAX);
    reg_bit_set(CANDS_CTL0_(671)+chn_offset, 0,16,f2_timing->TDFI_PHYMSTR_MAX);
    reg_bit_set(CANDS_CTL0_(736)+chn_offset, 0,16,f3_timing->TDFI_PHYMSTR_MAX);
    reg_bit_set(CANDS_CTL0_(801)+chn_offset, 0,16,f4_timing->TDFI_PHYMSTR_MAX);
    //TDFI_PHYMSTR_RESP
    reg_bit_set(CANDS_CTL0_(541)+chn_offset,16,16,f0_timing->TDFI_PHYMSTR_RESP);
    reg_bit_set(CANDS_CTL0_(606)+chn_offset,16,16,f1_timing->TDFI_PHYMSTR_RESP);
    reg_bit_set(CANDS_CTL0_(671)+chn_offset,16,16,f2_timing->TDFI_PHYMSTR_RESP);
    reg_bit_set(CANDS_CTL0_(736)+chn_offset,16,16,f3_timing->TDFI_PHYMSTR_RESP);
    reg_bit_set(CANDS_CTL0_(801)+chn_offset,16,16,f4_timing->TDFI_PHYMSTR_RESP);
    //TDFI_PHYUPD_RESP
    reg_bit_set(CANDS_CTL0_(542)+chn_offset, 0,16,f0_timing->TDFI_PHYUPD_RESP);
    reg_bit_set(CANDS_CTL0_(607)+chn_offset, 0,16,f1_timing->TDFI_PHYUPD_RESP);
    reg_bit_set(CANDS_CTL0_(672)+chn_offset, 0,16,f2_timing->TDFI_PHYUPD_RESP);
    reg_bit_set(CANDS_CTL0_(737)+chn_offset, 0,16,f3_timing->TDFI_PHYUPD_RESP);
    reg_bit_set(CANDS_CTL0_(802)+chn_offset, 0,16,f4_timing->TDFI_PHYUPD_RESP);
    //TDFI_PHYUPD_TYPE
    //f0
    __raw_writel(CANDS_CTL0_(543)+chn_offset,f0_timing->TDFI_PHYUPD_TYPE0);
    __raw_writel(CANDS_CTL0_(544)+chn_offset,f0_timing->TDFI_PHYUPD_TYPE1);
    __raw_writel(CANDS_CTL0_(545)+chn_offset,f0_timing->TDFI_PHYUPD_TYPE2);
    __raw_writel(CANDS_CTL0_(546)+chn_offset,f0_timing->TDFI_PHYUPD_TYPE3);
    //f1
    __raw_writel(CANDS_CTL0_(608)+chn_offset,f1_timing->TDFI_PHYUPD_TYPE0);
    __raw_writel(CANDS_CTL0_(609)+chn_offset,f1_timing->TDFI_PHYUPD_TYPE1);
    __raw_writel(CANDS_CTL0_(610)+chn_offset,f1_timing->TDFI_PHYUPD_TYPE2);
    __raw_writel(CANDS_CTL0_(611)+chn_offset,f1_timing->TDFI_PHYUPD_TYPE3);
	//f2
    __raw_writel(CANDS_CTL0_(673)+chn_offset,f2_timing->TDFI_PHYUPD_TYPE0);
    __raw_writel(CANDS_CTL0_(674)+chn_offset,f2_timing->TDFI_PHYUPD_TYPE1);
    __raw_writel(CANDS_CTL0_(675)+chn_offset,f2_timing->TDFI_PHYUPD_TYPE2);
    __raw_writel(CANDS_CTL0_(676)+chn_offset,f2_timing->TDFI_PHYUPD_TYPE3);
	//f3
    __raw_writel(CANDS_CTL0_(738)+chn_offset,f3_timing->TDFI_PHYUPD_TYPE0);
    __raw_writel(CANDS_CTL0_(739)+chn_offset,f3_timing->TDFI_PHYUPD_TYPE1);
    __raw_writel(CANDS_CTL0_(740)+chn_offset,f3_timing->TDFI_PHYUPD_TYPE2);
    __raw_writel(CANDS_CTL0_(741)+chn_offset,f3_timing->TDFI_PHYUPD_TYPE3);
	//f4
    __raw_writel(CANDS_CTL0_(803)+chn_offset,f4_timing->TDFI_PHYUPD_TYPE0);
    __raw_writel(CANDS_CTL0_(804)+chn_offset,f4_timing->TDFI_PHYUPD_TYPE1);
    __raw_writel(CANDS_CTL0_(805)+chn_offset,f4_timing->TDFI_PHYUPD_TYPE2);
    __raw_writel(CANDS_CTL0_(806)+chn_offset,f4_timing->TDFI_PHYUPD_TYPE3);
	#endif
    //TDFI_RDDATA_EN
    reg_bit_set(CANDS_CTL0_(452)+chn_offset,16, 7,f0_timing->TDFI_RDDATA_EN);
    //TDFI_RDLVL_EN
    reg_bit_set(CANDS_CTL0_(493)+chn_offset, 0, 8,f0_timing->TDFI_RDLVL_EN);
    //TDFI_RDLVL_MAX
    __raw_writel(CANDS_CTL0_(496)+chn_offset, f0_timing->TDFI_RDLVL_MAX);
    //TDFI_RDLVL_RESP
    __raw_writel(CANDS_CTL0_(494)+chn_offset, f0_timing->TDFI_RDLVL_RESP);
    //TDFI_RDLVL_RR
    reg_bit_set(CANDS_CTL0_(493)+chn_offset, 8,10,f0_timing->TDFI_RDLVL_RR);

    //TDFI_RDCSLAT
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(542+65*i)+chn_offset,16, 7,timing[i]->TDFI_RDCSLAT);
		reg_bit_set(CANDS_CTL0_(542+65*i)+chn_offset,24, 7, timing[i]->TDFI_WRCSLAT);
	}
	#else
    reg_bit_set(CANDS_CTL0_(542)+chn_offset,16, 7,f0_timing->TDFI_RDCSLAT);
    reg_bit_set(CANDS_CTL0_(607)+chn_offset,16, 7,f1_timing->TDFI_RDCSLAT);
    reg_bit_set(CANDS_CTL0_(672)+chn_offset,16, 7,f2_timing->TDFI_RDCSLAT);
    reg_bit_set(CANDS_CTL0_(737)+chn_offset,16, 7,f3_timing->TDFI_RDCSLAT);
    reg_bit_set(CANDS_CTL0_(802)+chn_offset,16, 7,f4_timing->TDFI_RDCSLAT);
	//tdfi_wrcslat
	reg_bit_set(CANDS_CTL0_(542)+chn_offset,24, 7, f0_timing->TDFI_WRCSLAT);
	reg_bit_set(CANDS_CTL0_(607)+chn_offset,24, 7, f1_timing->TDFI_WRCSLAT);
	reg_bit_set(CANDS_CTL0_(672)+chn_offset,24, 7, f2_timing->TDFI_WRCSLAT);
	reg_bit_set(CANDS_CTL0_(737)+chn_offset,24, 7, f3_timing->TDFI_WRCSLAT);
	reg_bit_set(CANDS_CTL0_(802)+chn_offset,24, 7, f4_timing->TDFI_WRCSLAT);
	#endif
    //TDFI_WRLVL_EN
    reg_bit_set(CANDS_CTL0_(490)+chn_offset, 8, 8,f0_timing->TDFI_WRLVL_EN);
    //TDFI_WRLVL_MAX
    __raw_writel(CANDS_CTL0_(492)+chn_offset, f0_timing->TDFI_WRLVL_MAX);
    //TDFI_WRLVL_RESP
    __raw_writel(CANDS_CTL0_(491)+chn_offset, f0_timing->TDFI_WRLVL_RESP);
    //TDFI_WRLVL_WW
    reg_bit_set(CANDS_CTL0_(490)+chn_offset,16, 10,f0_timing->TDFI_WRLVL_WW);
}

void cands_ctl_dfs_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{

	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//dfs_always_write_fsp
	reg_bit_set(CANDS_CTL0_(907)+chn_offset,8,1,islp3?0:1);
	#ifdef DRAM_LPDDR4
	reg_bit_set(CANDS_CTL0_(907)+chn_offset,24, 1, 1);
	reg_bit_set(CANDS_CTL0_(843)+chn_offset,16, 1, 1);

	#endif

    //dfs_close_banks, ctl spec this parameter is reserved for future use and should be clear to 0
	reg_bit_set(CANDS_CTL0_(843)+chn_offset,8,1,0);

	//dfs_phy_reg_write_en
	reg_bit_set(CANDS_CTL0_(168)+chn_offset, 24,1,1);
	//dfs_enable
	reg_bit_set(CANDS_CTL0_(168)+chn_offset, 16,1,1);

	//dfs_phy_reg_write_addr
	__raw_writel(CANDS_CTL0_(166)+chn_offset,0xc00);
	//dfs_phy_reg_write_mask
	reg_bit_set(CANDS_CTL0_(167)+chn_offset, 0,4,0xe);

	//dfs_phy_reg_write_data
	__raw_writel(CANDS_CTL0_(521)+chn_offset, 0);
	__raw_writel(CANDS_CTL0_(586)+chn_offset, 1);
	__raw_writel(CANDS_CTL0_(651)+chn_offset, 2);
	__raw_writel(CANDS_CTL0_(716)+chn_offset, 3);
	__raw_writel(CANDS_CTL0_(781)+chn_offset, 4);


    //dfs_calvl_en
	reg_bit_set(CANDS_CTL0_(116)+chn_offset,24,1,CALVL_EN_DFS); //Enables CA training during a DFS exit
	//dfs_rdlvl_en
	reg_bit_set(CANDS_CTL0_(117)+chn_offset, 8,1,RDELVL_EN_DFS); //Enables data eye training during a DFS exit.
	//dfs_rdlvl_gate_en
	reg_bit_set(CANDS_CTL0_(117)+chn_offset, 16,1,RDGLVL_EN_DFS); //Enables gate training during a DFS exit.
	//dfs_wrlvl_en
	reg_bit_set(CANDS_CTL0_(117)+chn_offset,  0,1,WRLVL_EN_DFS); //Enables write leveling during a DFS exit.
	//dfs_zq_en
	reg_bit_set(CANDS_CTL0_(116)+chn_offset, 16,1,ZQ_EN_DFS); //Enables ZQ calibration during a DFS exit


	return;
}

void cands_ctl_fsp_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{

	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN	islp3 = IS_LPDDR3(ddr_type);

    //fsp_op_current
    reg_bit_set(CANDS_CTL0_(908)+chn_offset, 8, 1, islp3?0:fsp_op);  //???????? indentifies the FSP set that is currently in use
    //fsp_wr_current,  spec said recommand fsp_wr_current != fsp_op_current
    reg_bit_set(CANDS_CTL0_(908)+chn_offset,16, 1, islp3?0:fsp_wr);  //???????? indentifies the FSP set that will be write
    //fsp0_frc
    #ifdef DRAM_LPDDR3
    reg_bit_set(CANDS_CTL0_(908)+chn_offset,24, 3, 0); //???????? indentifies which fn is for FSP set 0
    #else
    //reg_bit_set(CANDS_CTL0_(908)+chn_offset,24, 3, 1); //???????? indentifies which fn is for FSP set 0
    #endif
    //fsp1_frc
    //reg_bit_set(CANDS_CTL0_(909)+chn_offset,0, 3, islp3?0:1); //???????? indentifies which fn is for FSP set 1

    //fsp_phy_update_mrw
    reg_bit_set(CANDS_CTL0_(907)+chn_offset,16, 1, islp3?1:1);  ///?????? define which part to updat MR12&MR14 in init/dfs/sw mrw 0:ctl 1:phy or pi
    //fsp_status

    //disable_update_tvrcg, lpddr4 only
    reg_bit_set(CANDS_CTL0_(853)+chn_offset,16, 1, IS_LPDDR3(ddr_type)?1:0);
	
	#ifdef DRAM_LPDDR4
	//mr_fsp_data_valid
	//cs0
	reg_bit_set(CANDS_CTL0_(869)+chn_offset,16, 1, 1);
	reg_bit_set(CANDS_CTL0_(869)+chn_offset,24, 1, 1);
	reg_bit_set(CANDS_CTL0_(870)+chn_offset, 0, 1, 1);
	reg_bit_set(CANDS_CTL0_(870)+chn_offset, 8, 1, 1);
	reg_bit_set(CANDS_CTL0_(870)+chn_offset,16, 1, 1);
	//cs1
	reg_bit_set(CANDS_CTL0_(874)+chn_offset,16, 1, 1);
	reg_bit_set(CANDS_CTL0_(874)+chn_offset,24, 1, 1);
	reg_bit_set(CANDS_CTL0_(875)+chn_offset, 0, 1, 1);
	reg_bit_set(CANDS_CTL0_(875)+chn_offset, 8, 1, 1);
	reg_bit_set(CANDS_CTL0_(875)+chn_offset,16, 1, 1);	
	#endif
	

}


void cands_ctl_latency_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
	#ifdef CODE_SIZE_OPTIMIZE
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;
	#else
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
	#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //RL  caslat_lin
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(519+65*i)+chn_offset,16, 7,timing[i]->CASLAT_LIN);
	}
	#else
    reg_bit_set(CANDS_CTL0_(519)+chn_offset,16, 7,f0_timing->CASLAT_LIN);
    reg_bit_set(CANDS_CTL0_(584)+chn_offset,16, 7,f1_timing->CASLAT_LIN);
    reg_bit_set(CANDS_CTL0_(649)+chn_offset,16, 7,f2_timing->CASLAT_LIN);
    reg_bit_set(CANDS_CTL0_(714)+chn_offset,16, 7,f3_timing->CASLAT_LIN);
    reg_bit_set(CANDS_CTL0_(779)+chn_offset,16, 7,f4_timing->CASLAT_LIN);
	#endif
    //DLL_RST_ADJ_DLY
    reg_bit_set(CANDS_CTL0_(450)+chn_offset,16, 8,f0_timing->DLL_RST_ADJ_DLY);
    //DLL_RST_DELAY
    reg_bit_set(CANDS_CTL0_(450)+chn_offset, 0,16,f0_timing->DLL_RST_DELAY);

    //RL_ADJ  rdlat_adj
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(529+65*i)+chn_offset, 0, 7,timing[i]->RDLAT_ADJ);
		reg_bit_set(CANDS_CTL0_(526+65*i)+chn_offset,24, 5,timing[i]->R2R_DIFFCS_DLY);
	}
	#else
    reg_bit_set(CANDS_CTL0_(529)+chn_offset, 0, 7,f0_timing->RDLAT_ADJ);
    reg_bit_set(CANDS_CTL0_(594)+chn_offset, 0, 7,f1_timing->RDLAT_ADJ);
    reg_bit_set(CANDS_CTL0_(659)+chn_offset, 0, 7,f2_timing->RDLAT_ADJ);
    reg_bit_set(CANDS_CTL0_(724)+chn_offset, 0, 7,f3_timing->RDLAT_ADJ);
    reg_bit_set(CANDS_CTL0_(789)+chn_offset, 0, 7,f4_timing->RDLAT_ADJ);

    //R2R_DIFFCS_DLY
    reg_bit_set(CANDS_CTL0_(526)+chn_offset,24, 5,f0_timing->R2R_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(591)+chn_offset,24, 5,f1_timing->R2R_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(656)+chn_offset,24, 5,f2_timing->R2R_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(721)+chn_offset,24, 5,f3_timing->R2R_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(786)+chn_offset,24, 5,f4_timing->R2R_DIFFCS_DLY);
	#endif
    //R2R_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(356)+chn_offset, 0, 5,f0_timing->R2R_SAMECS_DLY);

    //R2W_DIFFCS_DLY
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(527+65*i)+chn_offset, 0, 5,timing[i]->R2W_DIFFCS_DLY);
		reg_bit_set(CANDS_CTL0_(527+65*i)+chn_offset, 8, 5,timing[i]->R2W_SAMECS_DLY);
		reg_bit_set(CANDS_CTL0_(534+65*i)+chn_offset,24, 4,timing[i]->RW2MRW_DLY);
		reg_bit_set(CANDS_CTL0_(562+65*i)+chn_offset, 0, 6,timing[i]->WRLAT);
		reg_bit_set(CANDS_CTL0_(562+65*i)+chn_offset, 8, 7,timing[i]->WRLAT_ADJ);
		reg_bit_set(CANDS_CTL0_(559+65*i)+chn_offset, 0, 5,timing[i]->W2R_DIFFCS_DLY);
		reg_bit_set(CANDS_CTL0_(559+65*i)+chn_offset, 8, 5,timing[i]->W2W_DIFFCS_DLY);
	}
    //W2R_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(357)+chn_offset,16, 5,f0_timing->W2R_SAMECS_DLY);
	#else
    reg_bit_set(CANDS_CTL0_(527)+chn_offset, 0, 5,f0_timing->R2W_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(592)+chn_offset, 0, 5,f1_timing->R2W_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(657)+chn_offset, 0, 5,f2_timing->R2W_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(722)+chn_offset, 0, 5,f3_timing->R2W_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(787)+chn_offset, 0, 5,f4_timing->R2W_DIFFCS_DLY);

    //R2W_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(527)+chn_offset, 8, 5,f0_timing->R2W_SAMECS_DLY);
    reg_bit_set(CANDS_CTL0_(592)+chn_offset, 8, 5,f1_timing->R2W_SAMECS_DLY);
    reg_bit_set(CANDS_CTL0_(657)+chn_offset, 8, 5,f2_timing->R2W_SAMECS_DLY);
    reg_bit_set(CANDS_CTL0_(722)+chn_offset, 8, 5,f3_timing->R2W_SAMECS_DLY);
    reg_bit_set(CANDS_CTL0_(787)+chn_offset, 8, 5,f4_timing->R2W_SAMECS_DLY);

    //RW2MRW_DLY
    reg_bit_set(CANDS_CTL0_(534)+chn_offset,24, 4,f0_timing->RW2MRW_DLY);
    reg_bit_set(CANDS_CTL0_(599)+chn_offset,24, 4,f1_timing->RW2MRW_DLY);
    reg_bit_set(CANDS_CTL0_(664)+chn_offset,24, 4,f2_timing->RW2MRW_DLY);
    reg_bit_set(CANDS_CTL0_(729)+chn_offset,24, 4,f3_timing->RW2MRW_DLY);
    reg_bit_set(CANDS_CTL0_(794)+chn_offset,24, 4,f4_timing->RW2MRW_DLY);

    //WL   wrlat
    reg_bit_set(CANDS_CTL0_(562)+chn_offset, 0, 6,f0_timing->WRLAT);
    reg_bit_set(CANDS_CTL0_(627)+chn_offset, 0, 6,f1_timing->WRLAT);
    reg_bit_set(CANDS_CTL0_(692)+chn_offset, 0, 6,f2_timing->WRLAT);
    reg_bit_set(CANDS_CTL0_(757)+chn_offset, 0, 6,f3_timing->WRLAT);
    reg_bit_set(CANDS_CTL0_(822)+chn_offset, 0, 6,f4_timing->WRLAT);
    //WL_ADJ  wrlat_adj
    reg_bit_set(CANDS_CTL0_(562)+chn_offset, 8, 7,f0_timing->WRLAT_ADJ);
    reg_bit_set(CANDS_CTL0_(627)+chn_offset, 8, 7,f1_timing->WRLAT_ADJ);
    reg_bit_set(CANDS_CTL0_(692)+chn_offset, 8, 7,f2_timing->WRLAT_ADJ);
    reg_bit_set(CANDS_CTL0_(757)+chn_offset, 8, 7,f3_timing->WRLAT_ADJ);
    reg_bit_set(CANDS_CTL0_(822)+chn_offset, 8, 7,f4_timing->WRLAT_ADJ);
    //W2R_DIFFCS_DLY
    reg_bit_set(CANDS_CTL0_(559)+chn_offset, 0, 5,f0_timing->W2R_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(624)+chn_offset, 0, 5,f1_timing->W2R_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(689)+chn_offset, 0, 5,f2_timing->W2R_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(754)+chn_offset, 0, 5,f3_timing->W2R_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(819)+chn_offset, 0, 5,f4_timing->W2R_DIFFCS_DLY);
    //W2R_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(357)+chn_offset,16, 5,f0_timing->W2R_SAMECS_DLY);
    //W2W_DIFFCS_DLY
    reg_bit_set(CANDS_CTL0_(559)+chn_offset, 8, 5,f0_timing->W2W_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(624)+chn_offset, 8, 5,f1_timing->W2W_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(689)+chn_offset, 8, 5,f2_timing->W2W_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(754)+chn_offset, 8, 5,f3_timing->W2W_DIFFCS_DLY);
    reg_bit_set(CANDS_CTL0_(819)+chn_offset, 8, 5,f4_timing->W2W_DIFFCS_DLY);
	#endif
    //W2W_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(357)+chn_offset,24, 5,f0_timing->W2W_SAMECS_DLY);
}


void cands_ctl_lowpower_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,
							 uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;

#else
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //******************* low power mode en ************************//
    //lowpower_refresh_enable
    reg_bit_set(CANDS_CTL0_(162)+chn_offset, 8,8, 0);

    //lowpower_auto_entry_en, Enables automatic entry into each of the low power states when the associated idle timer expires
    reg_bit_set(CANDS_CTL0_(160)+chn_offset, 16, 1, 0); //power down
    reg_bit_set(CANDS_CTL0_(160)+chn_offset, 17, 1, 0); //self refresh
    reg_bit_set(CANDS_CTL0_(160)+chn_offset, 18, 1, 0); //self refresh with memory and controller clock gating
    //lp_auto_exit_en,Enables automatic exit from each of the low power states when a read or write command enters the command queue in the Controller core.
    reg_bit_set(CANDS_CTL0_(160)+chn_offset, 24, 1, 0); //power down
    reg_bit_set(CANDS_CTL0_(160)+chn_offset, 25, 1, 0); //lite self refresh
    reg_bit_set(CANDS_CTL0_(160)+chn_offset, 26, 1, 0); //deep refresh with memory and controller clock gating
    //lp_auto_mem_gate_en,Enables memory clock gating when entering each of the low power modes automatically.
    reg_bit_set(CANDS_CTL0_(161)+chn_offset,  0, 1, 0); //power down
    reg_bit_set(CANDS_CTL0_(161)+chn_offset,  1, 1, 0); //self refresh
    reg_bit_set(CANDS_CTL0_(161)+chn_offset,  2, 1, 0); //Self-Refresh Power-Down---probelem


    //lpc_sr_ctrlupd_en
    reg_bit_set(CANDS_CTL0_(167)+chn_offset, 16, 1, 0); //Enables the LPC to execute a DFI control update on a self-refresh exit sequence???should check
    //lpc_sr_phymstr_en
    reg_bit_set(CANDS_CTL0_(848)+chn_offset, 16, 1, 0); //Enables the LPC to execute a DFI PHY master request on a self-refresh exit sequence???should check
    //lpc_sr_phyupd_en
    reg_bit_set(CANDS_CTL0_(167)+chn_offset, 24, 1, 0); //Enables the LPC to execute a DFI PHY update on a self-refresh exit sequence???should check
    //lpi_wakeup_en
    reg_bit_set(CANDS_CTL0_(83)+chn_offset, 16, 5, 0xE);//bit0:Power-Down (lp_pd_wakeup_fN)
                                                        //bit1:Self-Refresh (lpi_sr_wakeup_fN)
                                                        //bit2:Self-Refresh with memory and controller clock gating
                                                        //bit3:Reserved
                                                        //bit4:LPI Timer


    //pwrup_srefresh_exit,   Allows the controller to exit low power by executing a self-refresh exit instead of the full memory initialization
    //reg_bit_set(CANDS_CTL0_(115)+chn_offset, 0, 1, 1);
    reg_bit_set(CANDS_CTL0_(115)+chn_offset, 0, 1, 0);

    //srefresh_exit_no_refresh
    reg_bit_set(CANDS_CTL0_(115)+chn_offset, 8, 1, 1); //not Allow automatic refresh when self-refresh exit


    //******************* low power timing ************************//
    reg_bit_set(CANDS_CTL0_(162)+chn_offset,16,12,f0_timing->LP_AUTO_PD_IDLE);
	reg_bit_set(CANDS_CTL0_(161)+chn_offset,24, 8,f0_timing->LP_AUTO_SR_IDLE);
	reg_bit_set(CANDS_CTL0_(848)+chn_offset, 0,12,f0_timing->LP_AUTO_SRPD_LITE_IDLE);
	reg_bit_set(CANDS_CTL0_(162)+chn_offset, 0, 8,f0_timing->LP_AUTO_SR_MC_GATE_IDLE);
    //LPI_PD_WAKEUP
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(523+65*i)+chn_offset,16, 4,timing[i]->LPI_PD_WAKEUP);
		reg_bit_set(CANDS_CTL0_(523+65*i)+chn_offset, 0, 4,timing[i]->LPI_SR_MCCLK_GATE_WAKEUP);
		reg_bit_set(CANDS_CTL0_(523+65*i)+chn_offset,24, 4,timing[i]->LPI_SR_WAKEUP);
	}
	#else
	reg_bit_set(CANDS_CTL0_(523)+chn_offset,16, 4,f0_timing->LPI_PD_WAKEUP);
	reg_bit_set(CANDS_CTL0_(588)+chn_offset,16, 4,f1_timing->LPI_PD_WAKEUP);
	reg_bit_set(CANDS_CTL0_(653)+chn_offset,16, 4,f2_timing->LPI_PD_WAKEUP);
	reg_bit_set(CANDS_CTL0_(718)+chn_offset,16, 4,f3_timing->LPI_PD_WAKEUP);
	reg_bit_set(CANDS_CTL0_(783)+chn_offset,16, 4,f4_timing->LPI_PD_WAKEUP);
	//LPI_SR_MCCLK_GATE_WAKEUP
	reg_bit_set(CANDS_CTL0_(523)+chn_offset, 0, 4,f0_timing->LPI_SR_MCCLK_GATE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(588)+chn_offset, 0, 4,f1_timing->LPI_SR_MCCLK_GATE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(653)+chn_offset, 0, 4,f2_timing->LPI_SR_MCCLK_GATE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(718)+chn_offset, 0, 4,f3_timing->LPI_SR_MCCLK_GATE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(783)+chn_offset, 0, 4,f4_timing->LPI_SR_MCCLK_GATE_WAKEUP);
    //LPI_SR_WAKEUP
    reg_bit_set(CANDS_CTL0_(523)+chn_offset,24, 4,f0_timing->LPI_SR_WAKEUP);
	reg_bit_set(CANDS_CTL0_(588)+chn_offset,24, 4,f1_timing->LPI_SR_WAKEUP);
	reg_bit_set(CANDS_CTL0_(653)+chn_offset,24, 4,f2_timing->LPI_SR_WAKEUP);
	reg_bit_set(CANDS_CTL0_(718)+chn_offset,24, 4,f3_timing->LPI_SR_WAKEUP);
	reg_bit_set(CANDS_CTL0_(783)+chn_offset,24, 4,f4_timing->LPI_SR_WAKEUP);
	#endif
    //LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP
    reg_bit_set(CANDS_CTL0_(845)+chn_offset, 0, 4,f0_timing->LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(845)+chn_offset,24, 4,f1_timing->LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(846)+chn_offset,16, 4,f2_timing->LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(847)+chn_offset, 8, 4,f3_timing->LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(848)+chn_offset, 0, 4,f4_timing->LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP);
    //LPI_SRPD_DEEP_WAKEUP
    reg_bit_set(CANDS_CTL0_(844)+chn_offset,24, 4,f0_timing->LPI_SRPD_DEEP_WAKEUP);
	reg_bit_set(CANDS_CTL0_(845)+chn_offset,16, 4,f1_timing->LPI_SRPD_DEEP_WAKEUP);
	reg_bit_set(CANDS_CTL0_(846)+chn_offset, 8, 4,f2_timing->LPI_SRPD_DEEP_WAKEUP);
	reg_bit_set(CANDS_CTL0_(847)+chn_offset, 0, 4,f3_timing->LPI_SRPD_DEEP_WAKEUP);
	reg_bit_set(CANDS_CTL0_(847)+chn_offset,24, 4,f4_timing->LPI_SRPD_DEEP_WAKEUP);
    //LPI_SRPD_LITE_WAKEUP
    reg_bit_set(CANDS_CTL0_(844)+chn_offset,16, 4,f0_timing->LPI_SRPD_LITE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(845)+chn_offset, 8, 4,f1_timing->LPI_SRPD_LITE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(846)+chn_offset, 0, 4,f2_timing->LPI_SRPD_LITE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(846)+chn_offset,24, 4,f3_timing->LPI_SRPD_LITE_WAKEUP);
	reg_bit_set(CANDS_CTL0_(847)+chn_offset,16, 4,f4_timing->LPI_SRPD_LITE_WAKEUP);
    //LPI_TIMER_COUNT
    reg_bit_set(CANDS_CTL0_(161)+chn_offset, 8,12,f0_timing->LPI_TIMER_COUNT);
    //LPI_TIMER_WAKEUP
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(523+65*i)+chn_offset, 8, 4,timing[i]->LPI_TIMER_WAKEUP);
	}
	#else
    reg_bit_set(CANDS_CTL0_(523)+chn_offset, 8, 4,f0_timing->LPI_TIMER_WAKEUP);
	reg_bit_set(CANDS_CTL0_(588)+chn_offset, 8, 4,f1_timing->LPI_TIMER_WAKEUP);
	reg_bit_set(CANDS_CTL0_(653)+chn_offset, 8, 4,f2_timing->LPI_TIMER_WAKEUP);
	reg_bit_set(CANDS_CTL0_(718)+chn_offset, 8, 4,f3_timing->LPI_TIMER_WAKEUP);
	reg_bit_set(CANDS_CTL0_(783)+chn_offset, 8, 4,f4_timing->LPI_TIMER_WAKEUP);
	#endif
    //LPI_WAKEUP_TIMEOUT
    reg_bit_set(CANDS_CTL0_(84)+chn_offset, 0,12,f0_timing->LPI_WAKEUP_TIMEOUT);

}

void cands_ctl_modreg_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,
							 uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;
	uint32 val;

#else
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //***********************mode register read&write mode*****************//
	//mrw_dfs_update_frc
    reg_bit_set(CANDS_CTL0_(853)+chn_offset, 0,3,0);

	//no_auto_mrr_init
    reg_bit_set(CANDS_CTL0_(17)+chn_offset, 24,1,0);  //for mr8&mr11 will be auto read if set to 0

	//no_mrw_bt_init
    reg_bit_set(CANDS_CTL0_(16)+chn_offset,  8,1,0);
	//no_mrw_init
    reg_bit_set(CANDS_CTL0_(16)+chn_offset, 16,1,0);

    //***********************mode register vale*****************//
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		//mr1
		val = (timing[i]->MR1_DATA<<24)|(timing[i]->MR1_DATA<<16)|(timing[i]->MR1_DATA<<8)|timing[i]->MR1_DATA;
		__raw_writel(CANDS_CTL0_(574+65*i)+chn_offset, val);
		__raw_writel(CANDS_CTL0_(575+65*i)+chn_offset, val);
		//mr2
		val = (timing[i]->MR2_DATA<<24)|(timing[i]->MR2_DATA<<16)|(timing[i]->MR2_DATA<<8)|timing[i]->MR2_DATA;
		__raw_writel(CANDS_CTL0_(576+65*i)+chn_offset, val);
		__raw_writel(CANDS_CTL0_(577+65*i)+chn_offset, val);
		//mr3
		val = (timing[i]->MR3_DATA<<24)|(timing[i]->MR3_DATA<<16)|(timing[i]->MR3_DATA<<8)|timing[i]->MR3_DATA;
		__raw_writel(CANDS_CTL0_(578+65*i)+chn_offset, val);
		__raw_writel(CANDS_CTL0_(579+65*i)+chn_offset, val);
		//mr11
		val = (timing[i]->MR11_DATA<<24)|(timing[i]->MR11_DATA<<16)|(timing[i]->MR11_DATA<<8)|timing[i]->MR11_DATA;
		__raw_writel(CANDS_CTL0_(580+65*i)+chn_offset, val);
		__raw_writel(CANDS_CTL0_(581+65*i)+chn_offset, val);
	}
	#else
	__raw_writel(CANDS_CTL0_(574)+chn_offset, (f0_timing->MR1_DATA<<24)|(f0_timing->MR1_DATA<<16)|(f0_timing->MR1_DATA<<8)|f0_timing->MR1_DATA);
	__raw_writel(CANDS_CTL0_(575)+chn_offset, (f0_timing->MR1_DATA<<24)|(f0_timing->MR1_DATA<<16)|(f0_timing->MR1_DATA<<8)|f0_timing->MR1_DATA);

	__raw_writel(CANDS_CTL0_(639)+chn_offset, (f1_timing->MR1_DATA<<24)|(f1_timing->MR1_DATA<<16)|(f1_timing->MR1_DATA<<8)|f1_timing->MR1_DATA);
	__raw_writel(CANDS_CTL0_(640)+chn_offset, (f1_timing->MR1_DATA<<24)|(f1_timing->MR1_DATA<<16)|(f1_timing->MR1_DATA<<8)|f1_timing->MR1_DATA);

    __raw_writel(CANDS_CTL0_(704)+chn_offset, (f2_timing->MR1_DATA<<24)|(f2_timing->MR1_DATA<<16)|(f2_timing->MR1_DATA<<8)|f2_timing->MR1_DATA);
    __raw_writel(CANDS_CTL0_(705)+chn_offset, (f2_timing->MR1_DATA<<24)|(f2_timing->MR1_DATA<<16)|(f2_timing->MR1_DATA<<8)|f2_timing->MR1_DATA);

    __raw_writel(CANDS_CTL0_(769)+chn_offset, (f3_timing->MR1_DATA<<24)|(f3_timing->MR1_DATA<<16)|(f3_timing->MR1_DATA<<8)|f3_timing->MR1_DATA);
    __raw_writel(CANDS_CTL0_(770)+chn_offset, (f3_timing->MR1_DATA<<24)|(f3_timing->MR1_DATA<<16)|(f3_timing->MR1_DATA<<8)|f3_timing->MR1_DATA);

    __raw_writel(CANDS_CTL0_(834)+chn_offset, (f4_timing->MR1_DATA<<24)|(f4_timing->MR1_DATA<<16)|(f4_timing->MR1_DATA<<8)|f4_timing->MR1_DATA);
    __raw_writel(CANDS_CTL0_(835)+chn_offset, (f4_timing->MR1_DATA<<24)|(f4_timing->MR1_DATA<<16)|(f4_timing->MR1_DATA<<8)|f4_timing->MR1_DATA);

    //mr2
    __raw_writel(CANDS_CTL0_(576)+chn_offset, (f0_timing->MR2_DATA<<24)|(f0_timing->MR2_DATA<<16)|(f0_timing->MR2_DATA<<8)|f0_timing->MR2_DATA);
    __raw_writel(CANDS_CTL0_(577)+chn_offset, (f0_timing->MR2_DATA<<24)|(f0_timing->MR2_DATA<<16)|(f0_timing->MR2_DATA<<8)|f0_timing->MR2_DATA);

    __raw_writel(CANDS_CTL0_(641)+chn_offset, (f1_timing->MR2_DATA<<24)|(f1_timing->MR2_DATA<<16)|(f1_timing->MR2_DATA<<8)|f1_timing->MR2_DATA);
    __raw_writel(CANDS_CTL0_(642)+chn_offset, (f1_timing->MR2_DATA<<24)|(f1_timing->MR2_DATA<<16)|(f1_timing->MR2_DATA<<8)|f1_timing->MR2_DATA);

    __raw_writel(CANDS_CTL0_(706)+chn_offset, (f2_timing->MR2_DATA<<24)|(f2_timing->MR2_DATA<<16)|(f2_timing->MR2_DATA<<8)|f2_timing->MR2_DATA);
    __raw_writel(CANDS_CTL0_(707)+chn_offset, (f2_timing->MR2_DATA<<24)|(f2_timing->MR2_DATA<<16)|(f2_timing->MR2_DATA<<8)|f2_timing->MR2_DATA);

    __raw_writel(CANDS_CTL0_(771)+chn_offset, (f3_timing->MR2_DATA<<24)|(f3_timing->MR2_DATA<<16)|(f3_timing->MR2_DATA<<8)|f3_timing->MR2_DATA);
    __raw_writel(CANDS_CTL0_(772)+chn_offset, (f3_timing->MR2_DATA<<24)|(f3_timing->MR2_DATA<<16)|(f3_timing->MR2_DATA<<8)|f3_timing->MR2_DATA);

    __raw_writel(CANDS_CTL0_(836)+chn_offset, (f4_timing->MR2_DATA<<24)|(f4_timing->MR2_DATA<<16)|(f4_timing->MR2_DATA<<8)|f4_timing->MR2_DATA);
    __raw_writel(CANDS_CTL0_(837)+chn_offset, (f4_timing->MR2_DATA<<24)|(f4_timing->MR2_DATA<<16)|(f4_timing->MR2_DATA<<8)|f4_timing->MR2_DATA);


    //mr3
    __raw_writel(CANDS_CTL0_(578)+chn_offset, (f0_timing->MR3_DATA<<24)|(f0_timing->MR3_DATA<<16)|(f0_timing->MR3_DATA<<8)|f0_timing->MR3_DATA);
    __raw_writel(CANDS_CTL0_(579)+chn_offset, (f0_timing->MR3_DATA<<24)|(f0_timing->MR3_DATA<<16)|(f0_timing->MR3_DATA<<8)|f0_timing->MR3_DATA);

    __raw_writel(CANDS_CTL0_(643)+chn_offset, (f1_timing->MR3_DATA<<24)|(f1_timing->MR3_DATA<<16)|(f1_timing->MR3_DATA<<8)|f1_timing->MR3_DATA);
    __raw_writel(CANDS_CTL0_(644)+chn_offset, (f1_timing->MR3_DATA<<24)|(f1_timing->MR3_DATA<<16)|(f1_timing->MR3_DATA<<8)|f1_timing->MR3_DATA);

    __raw_writel(CANDS_CTL0_(708)+chn_offset, (f2_timing->MR3_DATA<<24)|(f2_timing->MR3_DATA<<16)|(f2_timing->MR3_DATA<<8)|f2_timing->MR3_DATA);
    __raw_writel(CANDS_CTL0_(709)+chn_offset, (f2_timing->MR3_DATA<<24)|(f2_timing->MR3_DATA<<16)|(f2_timing->MR3_DATA<<8)|f2_timing->MR3_DATA);

    __raw_writel(CANDS_CTL0_(773)+chn_offset, (f3_timing->MR3_DATA<<24)|(f3_timing->MR3_DATA<<16)|(f3_timing->MR3_DATA<<8)|f3_timing->MR3_DATA);
    __raw_writel(CANDS_CTL0_(774)+chn_offset, (f3_timing->MR3_DATA<<24)|(f3_timing->MR3_DATA<<16)|(f3_timing->MR3_DATA<<8)|f3_timing->MR3_DATA);

    __raw_writel(CANDS_CTL0_(838)+chn_offset, (f4_timing->MR3_DATA<<24)|(f4_timing->MR3_DATA<<16)|(f4_timing->MR3_DATA<<8)|f4_timing->MR3_DATA);
    __raw_writel(CANDS_CTL0_(839)+chn_offset, (f4_timing->MR3_DATA<<24)|(f4_timing->MR3_DATA<<16)|(f4_timing->MR3_DATA<<8)|f4_timing->MR3_DATA);


    //mr11
    __raw_writel(CANDS_CTL0_(580)+chn_offset, (f0_timing->MR11_DATA<<24)|(f0_timing->MR11_DATA<<16)|(f0_timing->MR11_DATA<<8)|f0_timing->MR11_DATA);
    __raw_writel(CANDS_CTL0_(581)+chn_offset, (f0_timing->MR11_DATA<<24)|(f0_timing->MR11_DATA<<16)|(f0_timing->MR11_DATA<<8)|f0_timing->MR11_DATA);

    __raw_writel(CANDS_CTL0_(645)+chn_offset, (f1_timing->MR11_DATA<<24)|(f1_timing->MR11_DATA<<16)|(f1_timing->MR11_DATA<<8)|f1_timing->MR11_DATA);
    __raw_writel(CANDS_CTL0_(646)+chn_offset, (f1_timing->MR11_DATA<<24)|(f1_timing->MR11_DATA<<16)|(f1_timing->MR11_DATA<<8)|f1_timing->MR11_DATA);

    __raw_writel(CANDS_CTL0_(710)+chn_offset, (f2_timing->MR11_DATA<<24)|(f2_timing->MR11_DATA<<16)|(f2_timing->MR11_DATA<<8)|f2_timing->MR11_DATA);
    __raw_writel(CANDS_CTL0_(711)+chn_offset, (f2_timing->MR11_DATA<<24)|(f2_timing->MR11_DATA<<16)|(f2_timing->MR11_DATA<<8)|f2_timing->MR11_DATA);

    __raw_writel(CANDS_CTL0_(775)+chn_offset, (f3_timing->MR11_DATA<<24)|(f3_timing->MR11_DATA<<16)|(f3_timing->MR11_DATA<<8)|f3_timing->MR11_DATA);
    __raw_writel(CANDS_CTL0_(776)+chn_offset, (f3_timing->MR11_DATA<<24)|(f3_timing->MR11_DATA<<16)|(f3_timing->MR11_DATA<<8)|f3_timing->MR11_DATA);

    __raw_writel(CANDS_CTL0_(840)+chn_offset, (f4_timing->MR11_DATA<<24)|(f4_timing->MR11_DATA<<16)|(f4_timing->MR11_DATA<<8)|f4_timing->MR11_DATA);
    __raw_writel(CANDS_CTL0_(841)+chn_offset, (f4_timing->MR11_DATA<<24)|(f4_timing->MR11_DATA<<16)|(f4_timing->MR11_DATA<<8)|f4_timing->MR11_DATA);
	#endif

	//mr13
	
	REG32(CANDS_CTL0_(175)+chn_offset) = 0xc0c0;
	#ifdef DRAM_LPDDR4
	//mr13_data
	//CS0
	reg_bit_set(CANDS_CTL0_(175)+chn_offset,6,1,fsp_wr);
	reg_bit_set(CANDS_CTL0_(175)+chn_offset,7,1,fsp_op);
	//CS1
	reg_bit_set(CANDS_CTL0_(175)+chn_offset,14,1,fsp_wr);
	reg_bit_set(CANDS_CTL0_(175)+chn_offset,15,1,fsp_op);
	
	#endif
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 8; i++) {
		//mr12
	    __raw_writel(CANDS_CTL0_(867+5*i)+chn_offset, (f3_timing->MR12_DATA<<24)|(f2_timing->MR12_DATA<<16)|(f1_timing->MR12_DATA<<8)|(f0_timing->MR12_DATA));
		//mr14
		reg_bit_set(CANDS_CTL0_(868+5*i)+chn_offset, 0,8,f4_timing->MR12_DATA);
		reg_bit_set(CANDS_CTL0_(868+5*i)+chn_offset, 8,24,(f2_timing->MR14_DATA<<24)|(f1_timing->MR14_DATA<<16)|(f0_timing->MR14_DATA<<8));
		reg_bit_set(CANDS_CTL0_(869+5*i)+chn_offset + (5*i*4), 0,16,(f4_timing->MR14_DATA<<8)|(f3_timing->MR14_DATA));
	}
	#else
	//mr12
    __raw_writel(CANDS_CTL0_(867)+chn_offset, (f3_timing->MR12_DATA<<24)|(f2_timing->MR12_DATA<<16)|(f1_timing->MR12_DATA<<8)|(f0_timing->MR12_DATA));
    __raw_writel(CANDS_CTL0_(872)+chn_offset, (f3_timing->MR12_DATA<<24)|(f2_timing->MR12_DATA<<16)|(f1_timing->MR12_DATA<<8)|(f0_timing->MR12_DATA));
    __raw_writel(CANDS_CTL0_(877)+chn_offset, (f3_timing->MR12_DATA<<24)|(f2_timing->MR12_DATA<<16)|(f1_timing->MR12_DATA<<8)|(f0_timing->MR12_DATA));
    __raw_writel(CANDS_CTL0_(882)+chn_offset, (f3_timing->MR12_DATA<<24)|(f2_timing->MR12_DATA<<16)|(f1_timing->MR12_DATA<<8)|(f0_timing->MR12_DATA));
    __raw_writel(CANDS_CTL0_(887)+chn_offset, (f3_timing->MR12_DATA<<24)|(f2_timing->MR12_DATA<<16)|(f1_timing->MR12_DATA<<8)|(f0_timing->MR12_DATA));
    __raw_writel(CANDS_CTL0_(892)+chn_offset, (f3_timing->MR12_DATA<<24)|(f2_timing->MR12_DATA<<16)|(f1_timing->MR12_DATA<<8)|(f0_timing->MR12_DATA));
    __raw_writel(CANDS_CTL0_(897)+chn_offset, (f3_timing->MR12_DATA<<24)|(f2_timing->MR12_DATA<<16)|(f1_timing->MR12_DATA<<8)|(f0_timing->MR12_DATA));
    __raw_writel(CANDS_CTL0_(902)+chn_offset, (f3_timing->MR12_DATA<<24)|(f2_timing->MR12_DATA<<16)|(f1_timing->MR12_DATA<<8)|(f0_timing->MR12_DATA));

    reg_bit_set(CANDS_CTL0_(868)+chn_offset, 0,8,f4_timing->MR12_DATA);
    reg_bit_set(CANDS_CTL0_(873)+chn_offset, 0,8,f4_timing->MR12_DATA);
    reg_bit_set(CANDS_CTL0_(878)+chn_offset, 0,8,f4_timing->MR12_DATA);
    reg_bit_set(CANDS_CTL0_(883)+chn_offset, 0,8,f4_timing->MR12_DATA);
    reg_bit_set(CANDS_CTL0_(888)+chn_offset, 0,8,f4_timing->MR12_DATA);
    reg_bit_set(CANDS_CTL0_(893)+chn_offset, 0,8,f4_timing->MR12_DATA);
    reg_bit_set(CANDS_CTL0_(898)+chn_offset, 0,8,f4_timing->MR12_DATA);
    reg_bit_set(CANDS_CTL0_(903)+chn_offset, 0,8,f4_timing->MR12_DATA);

    //mr14
    reg_bit_set(CANDS_CTL0_(868)+chn_offset, 8,24,(f2_timing->MR14_DATA<<24)|(f1_timing->MR14_DATA<<16)|(f0_timing->MR14_DATA<<8));
    reg_bit_set(CANDS_CTL0_(873)+chn_offset, 8,24,(f2_timing->MR14_DATA<<24)|(f1_timing->MR14_DATA<<16)|(f0_timing->MR14_DATA<<8));
    reg_bit_set(CANDS_CTL0_(878)+chn_offset, 8,24,(f2_timing->MR14_DATA<<24)|(f1_timing->MR14_DATA<<16)|(f0_timing->MR14_DATA<<8));
    reg_bit_set(CANDS_CTL0_(883)+chn_offset, 8,24,(f2_timing->MR14_DATA<<24)|(f1_timing->MR14_DATA<<16)|(f0_timing->MR14_DATA<<8));
    reg_bit_set(CANDS_CTL0_(888)+chn_offset, 8,24,(f2_timing->MR14_DATA<<24)|(f1_timing->MR14_DATA<<16)|(f0_timing->MR14_DATA<<8));
    reg_bit_set(CANDS_CTL0_(893)+chn_offset, 8,24,(f2_timing->MR14_DATA<<24)|(f1_timing->MR14_DATA<<16)|(f0_timing->MR14_DATA<<8));
    reg_bit_set(CANDS_CTL0_(898)+chn_offset, 8,24,(f2_timing->MR14_DATA<<24)|(f1_timing->MR14_DATA<<16)|(f0_timing->MR14_DATA<<8));
    reg_bit_set(CANDS_CTL0_(903)+chn_offset, 8,24,(f2_timing->MR14_DATA<<24)|(f1_timing->MR14_DATA<<16)|(f0_timing->MR14_DATA<<8));

	  reg_bit_set(CANDS_CTL0_(869)+chn_offset, 0,16,(f4_timing->MR14_DATA<<8)|(f3_timing->MR14_DATA));
    reg_bit_set(CANDS_CTL0_(874)+chn_offset, 0,16,(f4_timing->MR14_DATA<<8)|(f3_timing->MR14_DATA));
    reg_bit_set(CANDS_CTL0_(879)+chn_offset, 0,16,(f4_timing->MR14_DATA<<8)|(f3_timing->MR14_DATA));
    reg_bit_set(CANDS_CTL0_(884)+chn_offset, 0,16,(f4_timing->MR14_DATA<<8)|(f3_timing->MR14_DATA));
    reg_bit_set(CANDS_CTL0_(889)+chn_offset, 0,16,(f4_timing->MR14_DATA<<8)|(f3_timing->MR14_DATA));
    reg_bit_set(CANDS_CTL0_(894)+chn_offset, 0,16,(f4_timing->MR14_DATA<<8)|(f3_timing->MR14_DATA));
    reg_bit_set(CANDS_CTL0_(899)+chn_offset, 0,16,(f4_timing->MR14_DATA<<8)|(f3_timing->MR14_DATA));
    reg_bit_set(CANDS_CTL0_(904)+chn_offset, 0,16,(f4_timing->MR14_DATA<<8)|(f3_timing->MR14_DATA));
	
   #endif

    //mrr_tempchk_high_threshold_fN, mrr_promote_threshold_fN
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		__raw_writel(CANDS_CTL0_(524+65*i)+chn_offset, (timing[i]->MRR_TEMPCHK_HIGH_THRESHOLD<<16)|timing[i]->MRR_PROMOTE_THRESHOLD);
		__raw_writel(CANDS_CTL0_(525+65*i)+chn_offset, (timing[i]->MRR_TEMPCHK_TIMEOUT<<16)|timing[i]->MRR_TEMPCHK_NORM_THRESHOLD);
		reg_bit_set(CANDS_CTL0_(526+65*i)+chn_offset, 0,16,timing[i]->MRW_PROMOTE_THRESHOLD);
	}
	#else
    __raw_writel(CANDS_CTL0_(524)+chn_offset, (f0_timing->MRR_TEMPCHK_HIGH_THRESHOLD<<16)|f0_timing->MRR_PROMOTE_THRESHOLD);
    __raw_writel(CANDS_CTL0_(589)+chn_offset, (f1_timing->MRR_TEMPCHK_HIGH_THRESHOLD<<16)|f1_timing->MRR_PROMOTE_THRESHOLD);
    __raw_writel(CANDS_CTL0_(654)+chn_offset, (f2_timing->MRR_TEMPCHK_HIGH_THRESHOLD<<16)|f2_timing->MRR_PROMOTE_THRESHOLD);
    __raw_writel(CANDS_CTL0_(719)+chn_offset, (f3_timing->MRR_TEMPCHK_HIGH_THRESHOLD<<16)|f3_timing->MRR_PROMOTE_THRESHOLD);
    __raw_writel(CANDS_CTL0_(784)+chn_offset, (f4_timing->MRR_TEMPCHK_HIGH_THRESHOLD<<16)|f4_timing->MRR_PROMOTE_THRESHOLD);

    //mrr_tempchk_norm_threshold_fN, mrr_tempchk_timeout_fN
    __raw_writel(CANDS_CTL0_(525)+chn_offset, (f0_timing->MRR_TEMPCHK_TIMEOUT<<16)|f0_timing->MRR_TEMPCHK_NORM_THRESHOLD);
    __raw_writel(CANDS_CTL0_(590)+chn_offset, (f1_timing->MRR_TEMPCHK_TIMEOUT<<16)|f1_timing->MRR_TEMPCHK_NORM_THRESHOLD);
    __raw_writel(CANDS_CTL0_(655)+chn_offset, (f2_timing->MRR_TEMPCHK_TIMEOUT<<16)|f2_timing->MRR_TEMPCHK_NORM_THRESHOLD);
    __raw_writel(CANDS_CTL0_(720)+chn_offset, (f3_timing->MRR_TEMPCHK_TIMEOUT<<16)|f3_timing->MRR_TEMPCHK_NORM_THRESHOLD);
    __raw_writel(CANDS_CTL0_(785)+chn_offset, (f4_timing->MRR_TEMPCHK_TIMEOUT<<16)|f4_timing->MRR_TEMPCHK_NORM_THRESHOLD);

    //mrw_promote_threshold_fN
    reg_bit_set(CANDS_CTL0_(526)+chn_offset, 0,16,f0_timing->MRW_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(591)+chn_offset, 0,16,f1_timing->MRW_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(656)+chn_offset, 0,16,f2_timing->MRW_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(721)+chn_offset, 0,16,f3_timing->MRW_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(786)+chn_offset, 0,16,f4_timing->MRW_PROMOTE_THRESHOLD);
	#endif

            //f0  
    reg_bit_set(CANDS_CTL0_(870)+chn_offset, 24,8,(f0_timing->MR22_DATA));
    reg_bit_set(CANDS_CTL0_(875)+chn_offset, 24, 8,(f0_timing->MR22_DATA));
    //f1
    reg_bit_set(CANDS_CTL0_(871)+chn_offset, 0, 8,(f1_timing->MR22_DATA));
    reg_bit_set(CANDS_CTL0_(876)+chn_offset, 0, 8,(f1_timing->MR22_DATA));

    reg_bit_set(CANDS_CTL0_(871)+chn_offset, 8, 8,(f2_timing->MR22_DATA));
    reg_bit_set(CANDS_CTL0_(876)+chn_offset, 8, 8,(f2_timing->MR22_DATA));

    reg_bit_set(CANDS_CTL0_(871)+chn_offset, 16, 8,(f3_timing->MR22_DATA));
    reg_bit_set(CANDS_CTL0_(876)+chn_offset, 16, 8,(f3_timing->MR22_DATA));

    reg_bit_set(CANDS_CTL0_(871)+chn_offset, 24, 8,(f4_timing->MR22_DATA));
    reg_bit_set(CANDS_CTL0_(876)+chn_offset, 24, 8,(f4_timing->MR22_DATA));

}

void cands_ctl_othertiming_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_CTL_TIMING_T * ctl_timing,
							    uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;
#else
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(528+65*i)+chn_offset, 8, 1, (timing[i]->CA_DEFAULT_VAL));
		reg_bit_set(CANDS_CTL0_(520+65*i)+chn_offset, 0,16, (timing[i]->DFS_PROMOTE_THRESHOLD));
		reg_bit_set(CANDS_CTL0_(522+65*i)+chn_offset,16,16, (timing[i]->HW_PROMOTE_THRESHOLD));
		reg_bit_set(CANDS_CTL0_(522+65*i)+chn_offset, 0,16, (timing[i]->LPC_PROMOTE_THRESHOLD));
		reg_bit_set(CANDS_CTL0_(527+65*i)+chn_offset,16,16, (timing[i]->PHYMSTR_DFI_PROMOTE_THRESHOLD));
		reg_bit_set(CANDS_CTL0_(560+65*i)+chn_offset, 0,16, (timing[i]->UPD_CTRLUPD_HIGH_THRESHOLD));
		reg_bit_set(CANDS_CTL0_(560+65*i)+chn_offset,16,16, (timing[i]->UPD_CTRLUPD_NORM_THRESHOLD));
		reg_bit_set(CANDS_CTL0_(561+65*i)+chn_offset, 0,16, (timing[i]->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));
		reg_bit_set(CANDS_CTL0_(561+65*i)+chn_offset,16,16, (timing[i]->UPD_CTRLUPD_TIMEOUT));
		reg_bit_set(CANDS_CTL0_(562+65*i)+chn_offset,16,16, (timing[i]->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
	}
	#else
	//CA_DEFAULT_VAL
    reg_bit_set(CANDS_CTL0_(528)+chn_offset, 8, 1, (f0_timing->CA_DEFAULT_VAL));
    reg_bit_set(CANDS_CTL0_(593)+chn_offset, 8, 1, (f1_timing->CA_DEFAULT_VAL));
    reg_bit_set(CANDS_CTL0_(658)+chn_offset, 8, 1, (f2_timing->CA_DEFAULT_VAL));
    reg_bit_set(CANDS_CTL0_(723)+chn_offset, 8, 1, (f3_timing->CA_DEFAULT_VAL));
    reg_bit_set(CANDS_CTL0_(788)+chn_offset, 8, 1, (f4_timing->CA_DEFAULT_VAL));

    //DFS_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(520)+chn_offset, 0,16, (f0_timing->DFS_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(585)+chn_offset, 0,16, (f1_timing->DFS_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(650)+chn_offset, 0,16, (f2_timing->DFS_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(715)+chn_offset, 0,16, (f3_timing->DFS_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(780)+chn_offset, 0,16, (f4_timing->DFS_PROMOTE_THRESHOLD));

    //HW_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(522)+chn_offset,16,16, (f0_timing->HW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(587)+chn_offset,16,16, (f1_timing->HW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(652)+chn_offset,16,16, (f2_timing->HW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(717)+chn_offset,16,16, (f3_timing->HW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(782)+chn_offset,16,16, (f4_timing->HW_PROMOTE_THRESHOLD));

    //LPC_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(522)+chn_offset, 0,16, (f0_timing->LPC_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(587)+chn_offset, 0,16, (f1_timing->LPC_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(652)+chn_offset, 0,16, (f2_timing->LPC_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(717)+chn_offset, 0,16, (f3_timing->LPC_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(782)+chn_offset, 0,16, (f4_timing->LPC_PROMOTE_THRESHOLD));

	//PHYMSTR_DFI_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(527)+chn_offset,16,16, (f0_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(592)+chn_offset,16,16, (f1_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(657)+chn_offset,16,16, (f2_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(722)+chn_offset,16,16, (f3_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(787)+chn_offset,16,16, (f4_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));

    //UPD_CTRLUPD_HIGH_THRESHOLD
    reg_bit_set(CANDS_CTL0_(560)+chn_offset, 0,16, (f0_timing->UPD_CTRLUPD_HIGH_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(625)+chn_offset, 0,16, (f1_timing->UPD_CTRLUPD_HIGH_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(690)+chn_offset, 0,16, (f2_timing->UPD_CTRLUPD_HIGH_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(755)+chn_offset, 0,16, (f3_timing->UPD_CTRLUPD_HIGH_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(820)+chn_offset, 0,16, (f4_timing->UPD_CTRLUPD_HIGH_THRESHOLD));

    //UPD_CTRLUPD_NORM_THRESHOLD
    reg_bit_set(CANDS_CTL0_(560)+chn_offset,16,16, (f0_timing->UPD_CTRLUPD_NORM_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(625)+chn_offset,16,16, (f1_timing->UPD_CTRLUPD_NORM_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(690)+chn_offset,16,16, (f2_timing->UPD_CTRLUPD_NORM_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(755)+chn_offset,16,16, (f3_timing->UPD_CTRLUPD_NORM_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(820)+chn_offset,16,16, (f4_timing->UPD_CTRLUPD_NORM_THRESHOLD));

    //UPD_CTRLUPD_SW_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(561)+chn_offset, 0,16, (f0_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(626)+chn_offset, 0,16, (f1_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(691)+chn_offset, 0,16, (f2_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(756)+chn_offset, 0,16, (f3_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(821)+chn_offset, 0,16, (f4_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));

    //UPD_CTRLUPD_TIMEOUT
    reg_bit_set(CANDS_CTL0_(561)+chn_offset,16,16, (f0_timing->UPD_CTRLUPD_TIMEOUT));
    reg_bit_set(CANDS_CTL0_(626)+chn_offset,16,16, (f1_timing->UPD_CTRLUPD_TIMEOUT));
    reg_bit_set(CANDS_CTL0_(691)+chn_offset,16,16, (f2_timing->UPD_CTRLUPD_TIMEOUT));
    reg_bit_set(CANDS_CTL0_(756)+chn_offset,16,16, (f3_timing->UPD_CTRLUPD_TIMEOUT));
    reg_bit_set(CANDS_CTL0_(821)+chn_offset,16,16, (f4_timing->UPD_CTRLUPD_TIMEOUT));

    //UPD_PHYUPD_DFI_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(562)+chn_offset,16,16, (f0_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(627)+chn_offset,16,16, (f1_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(692)+chn_offset,16,16, (f2_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(757)+chn_offset,16,16, (f3_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(822)+chn_offset,16,16, (f4_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
	#endif

}

void cands_ctl_odt_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,
						uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;
#else
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //en_odt_assert_except_rd    ?????? lp4 1200 need odt ???
    reg_bit_set(CANDS_CTL0_(347)+chn_offset,0,1,0); //Enables the controller to assert ODT at all times except during reads.


    //odt_en_fN
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(526+65*i)+chn_offset,16,1, timing[i]->ODT_EN); //f0
	}
	#else
    reg_bit_set(CANDS_CTL0_(526)+chn_offset,16,1, f0_timing->ODT_EN); //f0
    reg_bit_set(CANDS_CTL0_(591)+chn_offset,16,1, f1_timing->ODT_EN); //f1
    reg_bit_set(CANDS_CTL0_(656)+chn_offset,16,1, f2_timing->ODT_EN); //f2
    reg_bit_set(CANDS_CTL0_(721)+chn_offset,16,1, f3_timing->ODT_EN); //f3
    reg_bit_set(CANDS_CTL0_(786)+chn_offset,16,1, f4_timing->ODT_EN); //f4
    #endif

    //odt_rd_map_csX  ????????
    reg_bit_set(CANDS_CTL0_(340)+chn_offset, 0,8, 0x01); //cs0
    reg_bit_set(CANDS_CTL0_(340)+chn_offset,16,8, 0x02); //cs1
    reg_bit_set(CANDS_CTL0_(341)+chn_offset, 0,8, 0); //cs2
    reg_bit_set(CANDS_CTL0_(341)+chn_offset,16,8, 0); //cs3
    reg_bit_set(CANDS_CTL0_(342)+chn_offset, 0,8, 0); //cs4
    reg_bit_set(CANDS_CTL0_(342)+chn_offset,16,8, 0); //cs5
    reg_bit_set(CANDS_CTL0_(343)+chn_offset, 0,8, 0); //cs6
    reg_bit_set(CANDS_CTL0_(343)+chn_offset,16,8, 0); //cs7

    //odt_wr_map_csX   ????????
    reg_bit_set(CANDS_CTL0_(340)+chn_offset, 8,8, 0x01); //cs0
    reg_bit_set(CANDS_CTL0_(340)+chn_offset,24,8, 0x02); //cs1
    reg_bit_set(CANDS_CTL0_(341)+chn_offset, 8,8, 0); //cs2
    reg_bit_set(CANDS_CTL0_(341)+chn_offset,24,8, 0); //cs3
    reg_bit_set(CANDS_CTL0_(342)+chn_offset, 8,8, 0); //cs4
    reg_bit_set(CANDS_CTL0_(342)+chn_offset,24,8, 0); //cs5
    reg_bit_set(CANDS_CTL0_(343)+chn_offset, 8,8, 0); //cs6
    reg_bit_set(CANDS_CTL0_(343)+chn_offset,24,8, 0); //cs7

    //RD_TO_ODT
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(528+65*i)+chn_offset, 0, 6,timing[i]->RD_TO_ODTH);
		reg_bit_set(CANDS_CTL0_(559+65*i)+chn_offset,16, 6,timing[i]->WR_TO_ODTH);
	}
	#else
    reg_bit_set(CANDS_CTL0_(528)+chn_offset, 0, 6,f0_timing->RD_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(593)+chn_offset, 0, 6,f1_timing->RD_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(658)+chn_offset, 0, 6,f2_timing->RD_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(723)+chn_offset, 0, 6,f3_timing->RD_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(788)+chn_offset, 0, 6,f4_timing->RD_TO_ODTH);

    //WR_TO_ODT
    reg_bit_set(CANDS_CTL0_(559)+chn_offset,16, 6,f0_timing->WR_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(624)+chn_offset,16, 6,f1_timing->WR_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(689)+chn_offset,16, 6,f2_timing->WR_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(754)+chn_offset,16, 6,f3_timing->WR_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(819)+chn_offset,16, 6,f4_timing->WR_TO_ODTH);
	#endif
    //TODTH_RD
    reg_bit_set(CANDS_CTL0_(345)+chn_offset,16, 4,f0_timing->TODTH_RD);
    //TODTH_WR
    reg_bit_set(CANDS_CTL0_(345)+chn_offset, 8, 4,f0_timing->TODTH_WR);
    //TODTH_2CMD
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(548+65*i)+chn_offset, 0, 8,timing[i]->TODTL_2CMD);
	}
	#else
    reg_bit_set(CANDS_CTL0_(548)+chn_offset, 0, 8,f0_timing->TODTL_2CMD);
    reg_bit_set(CANDS_CTL0_(613)+chn_offset, 0, 8,f1_timing->TODTL_2CMD);
    reg_bit_set(CANDS_CTL0_(678)+chn_offset, 0, 8,f2_timing->TODTL_2CMD);
    reg_bit_set(CANDS_CTL0_(743)+chn_offset, 0, 8,f3_timing->TODTL_2CMD);
    reg_bit_set(CANDS_CTL0_(808)+chn_offset, 0, 8,f4_timing->TODTL_2CMD);
	#endif

}


void cands_ctl_qos_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type, CANDS_CTL_PERCHN_QOS_T* perchn_qos,CANDS_CTL_ALLCHN_QOS_T* allchn_qos)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
    	uint32 i = 0;

    	//age_count
    	reg_bit_set(CANDS_CTL0_(308)+chn_offset,24,8,allchn_qos->age_count); //should check !!!

    	//addr_cmp_en
	reg_bit_set(CANDS_CTL0_(309)+chn_offset,8,1,allchn_qos->addr_cmp_en);

	//reversed
	reg_bit_set(CANDS_CTL0_(309)+chn_offset,16,1,1);

	//ap
	reg_bit_set(CANDS_CTL0_(23)+chn_offset,16,1,allchn_qos->ap);     //disable auto pre-charge mode for DRAM memories

    //arb_cmd_q_threshold
    reg_bit_set(CANDS_CTL0_(441)+chn_offset,16,4,allchn_qos->arb_cmd_q_shreshold); //should check !!!

    //bank_split_en
    reg_bit_set(CANDS_CTL0_(309)+chn_offset,24, 1,allchn_qos->bank_split_en);

    //command_age_count
    reg_bit_set(CANDS_CTL0_(309)+chn_offset, 0,8,allchn_qos->cmd_age_count); //should check !!!

    //cs_same_en
    reg_bit_set(CANDS_CTL0_(311)+chn_offset, 0, 1,allchn_qos->cs_same_en);

    //w2r_split_en
    reg_bit_set(CANDS_CTL0_(311)+chn_offset, 8, 1,allchn_qos->w2r_split_en);

    //disable_rd_interleave
    reg_bit_set(CANDS_CTL0_(312)+chn_offset, 8, 1, allchn_qos->disable_rd_interleave);

    //disable_rw_group_w_bnk_conflict
    reg_bit_set(CANDS_CTL0_(311)+chn_offset,16, 2, allchn_qos->disable_rw_group_bank_conflit);
    //inhibit_dram_cmd
    reg_bit_set(CANDS_CTL0_(312)+chn_offset,16, 2, allchn_qos->inhibit_dram_en);

    //in_order_accept
    reg_bit_set(CANDS_CTL0_(315)+chn_offset,16, 1, allchn_qos->in_order_accept);

    //num_q_entries_act_disable
    reg_bit_set(CANDS_CTL0_(311)+chn_offset,24, 4, allchn_qos->num_q_entries_act_disable); //should check !!!


    //placement_en
    reg_bit_set(CANDS_CTL0_(310)+chn_offset, 0, 1, allchn_qos->placement_en);

    //priority_en
    reg_bit_set(CANDS_CTL0_(310)+chn_offset, 8, 1, allchn_qos->priority_en);

    //q_fullness, should check ???
    reg_bit_set(CANDS_CTL0_(315)+chn_offset, 8, 4, allchn_qos->q_fullness);

    //rw_same_en
    reg_bit_set(CANDS_CTL0_(310)+chn_offset,16, 1, allchn_qos->rw_same_en);

    //rw_same_page_en
    reg_bit_set(CANDS_CTL0_(310)+chn_offset,24, 1, allchn_qos->rw_same_page_en);

    //swap_en
    reg_bit_set(CANDS_CTL0_(312)+chn_offset, 0, 1, allchn_qos->swap_en);

    //wr_order_req
    reg_bit_set(CANDS_CTL0_(315)+chn_offset, 24,2,allchn_qos->wr_order_req); //Bit [1] = Port ID usage, Bit [0] = Source ID usage, should check

    //axiY_r_priority
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 10; i++) {
		reg_bit_set(CANDS_CTL0_(431+i)+chn_offset,24,4,perchn_qos[i].r_priority);
	}
	#else
    reg_bit_set(CANDS_CTL0_(431)+chn_offset,24,4,perchn_qos[0].r_priority);
    reg_bit_set(CANDS_CTL0_(432)+chn_offset,24,4,perchn_qos[1].r_priority);
    reg_bit_set(CANDS_CTL0_(433)+chn_offset,24,4,perchn_qos[2].r_priority);
    reg_bit_set(CANDS_CTL0_(434)+chn_offset,24,4,perchn_qos[3].r_priority);
    reg_bit_set(CANDS_CTL0_(435)+chn_offset,24,4,perchn_qos[4].r_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(436)+chn_offset,24,4,perchn_qos[5].r_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(437)+chn_offset,24,4,perchn_qos[6].r_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(438)+chn_offset,24,4,perchn_qos[7].r_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(439)+chn_offset,24,4,perchn_qos[8].r_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(440)+chn_offset,24,4,perchn_qos[9].r_priority); //should check !!!
	#endif
    reg_bit_set(CANDS_CTL0_(912)+chn_offset,24,4,perchn_qos[10].r_priority); //should check !!!
    //axiY_w_priority
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 10; i++) {
		reg_bit_set(CANDS_CTL0_(432+i)+chn_offset, 0,4,perchn_qos[i].w_priority); //should check !!!
	}
	#else
    reg_bit_set(CANDS_CTL0_(432)+chn_offset, 0,4,perchn_qos[0].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(433)+chn_offset, 0,4,perchn_qos[1].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(434)+chn_offset, 0,4,perchn_qos[2].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(435)+chn_offset, 0,4,perchn_qos[3].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(436)+chn_offset, 0,4,perchn_qos[4].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(437)+chn_offset, 0,4,perchn_qos[5].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(438)+chn_offset, 0,4,perchn_qos[6].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(439)+chn_offset, 0,4,perchn_qos[7].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(440)+chn_offset, 0,4,perchn_qos[8].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(441)+chn_offset, 0,4,perchn_qos[9].w_priority); //should check !!!
	#endif
    reg_bit_set(CANDS_CTL0_(913)+chn_offset, 0,4,perchn_qos[10].w_priority); //should check !!!

    //axiY_bdw, should check !!!
    reg_bit_set(CANDS_CTL0_(441)+chn_offset,24,7,perchn_qos[0].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(442)+chn_offset,16,7,perchn_qos[1].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(443)+chn_offset, 8,7,perchn_qos[2].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(444)+chn_offset, 0,7,perchn_qos[3].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(444)+chn_offset,24,7,perchn_qos[4].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(445)+chn_offset,16,7,perchn_qos[5].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(446)+chn_offset, 8,7,perchn_qos[6].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(447)+chn_offset, 0,7,perchn_qos[7].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(447)+chn_offset,24,7,perchn_qos[8].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(448)+chn_offset,16,7,perchn_qos[9].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(913)+chn_offset,16,7,perchn_qos[10].bdw); //should check !!!

    //axiY_bdw_overflow, should check !!!
    reg_bit_set(CANDS_CTL0_(442)+chn_offset, 0,1,perchn_qos[0].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(442)+chn_offset,24,1,perchn_qos[1].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(443)+chn_offset,16,1,perchn_qos[2].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(444)+chn_offset, 8,1,perchn_qos[3].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(445)+chn_offset, 0,1,perchn_qos[4].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(445)+chn_offset,24,1,perchn_qos[5].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(446)+chn_offset,16,1,perchn_qos[6].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(447)+chn_offset, 8,1,perchn_qos[7].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(448)+chn_offset, 0,1,perchn_qos[8].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(448)+chn_offset,24,1,perchn_qos[9].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(913)+chn_offset,24,1,perchn_qos[10].bdw_overflow); //should check !!!

    //axiY_fixed_prot_priority_enable  ??? fixed use axiY_r/w_priority of use axiY_AR/AWQOS ??? should check----CHANGE
    reg_bit_set(CANDS_CTL0_(909)+chn_offset,24,1,perchn_qos[0].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(910)+chn_offset, 0,1,perchn_qos[1].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(910)+chn_offset, 8,1,perchn_qos[2].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(910)+chn_offset,16,1,perchn_qos[3].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(910)+chn_offset,24,1,perchn_qos[4].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(911)+chn_offset, 0,1,perchn_qos[5].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(911)+chn_offset, 8,1,perchn_qos[6].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(911)+chn_offset,16,1,perchn_qos[7].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(911)+chn_offset,24,1,perchn_qos[8].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(912)+chn_offset, 0,1,perchn_qos[9].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(912)+chn_offset,16,1,perchn_qos[10].fixed_priority_en); //should check !!!

    //axiY_all_strobes_used_enable
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 10; i++) {
		reg_bit_set(CANDS_CTL0_(431+i)+chn_offset,16,1,perchn_qos[i].all_strobes_used_en); //should check !!!
		reg_bit_set(CANDS_CTL0_(432+i)+chn_offset, 8, 2, perchn_qos[0].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
	}
	reg_bit_set(CANDS_CTL0_(912)+chn_offset, 8,1,perchn_qos[10].all_strobes_used_en); //should check !!!
	reg_bit_set(CANDS_CTL0_(913)+chn_offset, 8, 2, perchn_qos[10].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
	#else
	reg_bit_set(CANDS_CTL0_(431)+chn_offset,16,1,perchn_qos[0].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(432)+chn_offset,16,1,perchn_qos[1].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(433)+chn_offset,16,1,perchn_qos[2].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(434)+chn_offset,16,1,perchn_qos[3].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(435)+chn_offset,16,1,perchn_qos[4].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(436)+chn_offset,16,1,perchn_qos[5].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(437)+chn_offset,16,1,perchn_qos[6].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(438)+chn_offset,16,1,perchn_qos[7].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(439)+chn_offset,16,1,perchn_qos[8].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(440)+chn_offset,16,1,perchn_qos[9].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(912)+chn_offset, 8,1,perchn_qos[10].all_strobes_used_en); //should check !!!


    //axiY_fifo_type_reg
    reg_bit_set(CANDS_CTL0_(432)+chn_offset, 8, 2, perchn_qos[0].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(433)+chn_offset, 8, 2, perchn_qos[1].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(434)+chn_offset, 8, 2, perchn_qos[2].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(435)+chn_offset, 8, 2, perchn_qos[3].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(436)+chn_offset, 8, 2, perchn_qos[4].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(437)+chn_offset, 8, 2, perchn_qos[5].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(438)+chn_offset, 8, 2, perchn_qos[6].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(439)+chn_offset, 8, 2, perchn_qos[7].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(440)+chn_offset, 8, 2, perchn_qos[8].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(441)+chn_offset, 8, 2, perchn_qos[9].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(913)+chn_offset, 8, 2, perchn_qos[10].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
	#endif
}


void cands_ctl_rdlvl_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //rdlvl_aref_en
	reg_bit_set(CANDS_CTL0_(381)+chn_offset,24,1, 1);
	//rdlvl_cs
	reg_bit_set(CANDS_CTL0_(379)+chn_offset,16,3, 0);
	//rdlvl_cs_map
	reg_bit_set(CANDS_CTL0_(383)+chn_offset,0,8, IS_2CS(ddr_type));
	//rdlvl_en
	reg_bit_set(CANDS_CTL0_(495)+chn_offset, 8,1, RDELVL_EN);
	//rdlvl_on_sref_exit
	reg_bit_set(CANDS_CTL0_(381)+chn_offset, 0,1, RDELVL_EN_DFS);
	//rdlvl_periodic
	reg_bit_set(CANDS_CTL0_(380)+chn_offset,24,1, 0);
    //rdlvl_rotate
    reg_bit_set(CANDS_CTL0_(382)+chn_offset,16,1, 0); //0:train all cs   1:train only one cs
    //rdlvl_seq_en
    reg_bit_set(CANDS_CTL0_(379)+chn_offset,24,4, 0); //calvl pattern sequence   3:pattern 0->1->2->3->0


    //rdlvl_gate_aref_en
	reg_bit_set(CANDS_CTL0_(382)+chn_offset, 0,1, 1);
	//rdlvl_gate_cs_map
	reg_bit_set(CANDS_CTL0_(383)+chn_offset, 8,8, IS_2CS(ddr_type));
	//rdlvl_gate_en
	reg_bit_set(CANDS_CTL0_(495)+chn_offset,16,1, RDGLVL_EN);
	//rdlvl_gate_on_sref_exit
	reg_bit_set(CANDS_CTL0_(381)+chn_offset,16,1, RDGLVL_EN_SREF);
	//rdlvl_gate_periodic
	reg_bit_set(CANDS_CTL0_(381)+chn_offset, 8,1, 0);
    //rdlvl_gate_rotate
    reg_bit_set(CANDS_CTL0_(382)+chn_offset,24,1, 0); //0:train all cs   1:train only one cs
    //rdlvl_gate_seq_en
    reg_bit_set(CANDS_CTL0_(380)+chn_offset, 0,4, 0); //calvl pattern sequence   3:pattern 0->1->2->3->0

}



void cands_ctl_wrlvl_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //wrlvl_aref_en
	reg_bit_set(CANDS_CTL0_(365)+chn_offset, 8,1, 1);
	//wrlvl_cs
	reg_bit_set(CANDS_CTL0_(363)+chn_offset, 8,3, 0);
	//wrlvl_en
	reg_bit_set(CANDS_CTL0_(364)+chn_offset, 0,1, WRLVL_EN);
	//wrlvl_on_sref_exit
	reg_bit_set(CANDS_CTL0_(364)+chn_offset,24,1, WRLVL_EN_SREF);
	//wrlvl_periodic
	reg_bit_set(CANDS_CTL0_(364)+chn_offset,16,1, 0);
    //wrlvl_resp_mask
    reg_bit_set(CANDS_CTL0_(365)+chn_offset, 0, 4, 0);
    //wrlvl_rotate
    reg_bit_set(CANDS_CTL0_(365)+chn_offset,16,1, 0); //0:train all cs   1:train only one cs

}

void cands_ctl_zq_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;
#else
	volatile CANDS_CTL_TIMING_T * f0_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f1_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f2_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f3_timing = NULL;
	volatile CANDS_CTL_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);
	uint32 cs_bits = IS_2CS(ddr_type)?3:1;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

	//multi_channel_zq_cal_master
	reg_bit_set(CANDS_CTL0_(509)+chn_offset,8,1,islp3?0:(chn_num==0));
	#ifdef DRAM_LPDDR4
	reg_bit_set(CANDS_CTL0_(509)+chn_offset,16,1,1);
	reg_bit_set(CANDS_CTL0_(509)+chn_offset,24,1,1);
	reg_bit_set(CANDS_CTL0_(510)+chn_offset, 0,1,1);
	#endif
	//no_zq_init
	reg_bit_set(CANDS_CTL0_(289)+chn_offset,16,1,ZQ_EN);

	//zqcs_rotate
	reg_bit_set(CANDS_CTL0_(289)+chn_offset,24,1, 1);  //0: all cs will be zqcs cal  1: one cs will be zqcs cal(on round-robin)

	#ifdef DRAM_LPDDR4
	//zq_cal_latch_map  ??????
	reg_bit_set(CANDS_CTL0_(290)+chn_offset, 8,8, 1);
	reg_bit_set(CANDS_CTL0_(290)+chn_offset,24,8, IS_2CS(ddr_type)?2:0);
	reg_bit_set(CANDS_CTL0_(291)+chn_offset, 8,8, 0);
	reg_bit_set(CANDS_CTL0_(291)+chn_offset,24,8, 0);
	reg_bit_set(CANDS_CTL0_(292)+chn_offset, 8,8, 0);
	reg_bit_set(CANDS_CTL0_(292)+chn_offset,24,8, 0);
	reg_bit_set(CANDS_CTL0_(293)+chn_offset, 8,8, 0);
	reg_bit_set(CANDS_CTL0_(293)+chn_offset,24,8, 0);

	//zq_cal_start_map   ??????
	reg_bit_set(CANDS_CTL0_(290)+chn_offset, 0,8, 1);
	reg_bit_set(CANDS_CTL0_(290)+chn_offset,16,8, IS_2CS(ddr_type)?2:0);
	reg_bit_set(CANDS_CTL0_(291)+chn_offset, 0,8, 0);
	reg_bit_set(CANDS_CTL0_(291)+chn_offset,16,8, 0);
	reg_bit_set(CANDS_CTL0_(292)+chn_offset, 0,8, 0);
	reg_bit_set(CANDS_CTL0_(292)+chn_offset,16,8, 0);
	reg_bit_set(CANDS_CTL0_(293)+chn_offset, 0,8, 0);
	reg_bit_set(CANDS_CTL0_(293)+chn_offset,16,8, 0);
	#else
	for(i = 0; i < 4; i++)
	{//zq_cal_latch_map  ??????
	reg_bit_set(CANDS_CTL0_((290+i))+chn_offset, 8,8, 0);
	reg_bit_set(CANDS_CTL0_((290+i))+chn_offset,24,8, 0);
    	//zq_cal_start_map   ??????
	reg_bit_set(CANDS_CTL0_((290+i))+chn_offset, 0,8, 0);
	reg_bit_set(CANDS_CTL0_((290+i))+chn_offset,16,8, 0);
	}
	#endif

    //zq_callatch_high_threshold
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(565+65*i)+chn_offset, 0,16, timing[i]->ZQ_CALLATCH_HIGH_THRESHOLD);
		reg_bit_set(CANDS_CTL0_(565+65*i)+chn_offset, 16,16, timing[i]->ZQ_CALLATCH_TIMEOUT);
		reg_bit_set(CANDS_CTL0_(566+65*i)+chn_offset,  0,16, timing[i]->ZQ_CALSTART_HIGH_THRESHOLD);
		reg_bit_set(CANDS_CTL0_(567+65*i)+chn_offset,  0,16, timing[i]->ZQ_CALSTART_NORM_THRESHOLD);
		reg_bit_set(CANDS_CTL0_(567+65*i)+chn_offset, 16,16, timing[i]->ZQ_CALSTART_TIMEOUT);
		reg_bit_set(CANDS_CTL0_(568+65*i)+chn_offset, 16,16, timing[i]->ZQ_CS_HIGH_THRESHOLD);
		reg_bit_set(CANDS_CTL0_(568+65*i)+chn_offset,  0,16, timing[i]->ZQ_CS_NORM_THRESHOLD);
		reg_bit_set(CANDS_CTL0_(569+65*i)+chn_offset,  0,16, timing[i]->ZQ_CS_TIMEOUT);
		reg_bit_set(CANDS_CTL0_(569+65*i)+chn_offset, 16,16, timing[i]->ZQ_PROMOTE_THRESHOLD);
		reg_bit_set(CANDS_CTL0_(570+65*i)+chn_offset, 16,12, timing[i]->ZQCS);
		reg_bit_set(CANDS_CTL0_(570+65*i)+chn_offset,  0,12, timing[i]->ZQCL);
		reg_bit_set(CANDS_CTL0_(571+65*i)+chn_offset, 16,12, timing[i]->ZQINIT);
		reg_bit_set(CANDS_CTL0_(571+65*i)+chn_offset,  0,12, timing[i]->ZQRESET);
	}
	#else
	reg_bit_set(CANDS_CTL0_(565)+chn_offset, 0,16, f0_timing->ZQ_CALLATCH_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(630)+chn_offset, 0,16, f1_timing->ZQ_CALLATCH_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(695)+chn_offset, 0,16, f2_timing->ZQ_CALLATCH_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(760)+chn_offset, 0,16, f3_timing->ZQ_CALLATCH_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(825)+chn_offset, 0,16, f4_timing->ZQ_CALLATCH_HIGH_THRESHOLD);

    //zq_callatch_timeout
	reg_bit_set(CANDS_CTL0_(565)+chn_offset, 16,16, f0_timing->ZQ_CALLATCH_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(630)+chn_offset, 16,16, f1_timing->ZQ_CALLATCH_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(695)+chn_offset, 16,16, f2_timing->ZQ_CALLATCH_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(760)+chn_offset, 16,16, f3_timing->ZQ_CALLATCH_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(825)+chn_offset, 16,16, f4_timing->ZQ_CALLATCH_TIMEOUT);

    //zq_calstart_high_threshold
	reg_bit_set(CANDS_CTL0_(566)+chn_offset,  0,16, f0_timing->ZQ_CALSTART_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(631)+chn_offset,  0,16, f1_timing->ZQ_CALSTART_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(696)+chn_offset,  0,16, f2_timing->ZQ_CALSTART_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(761)+chn_offset,  0,16, f3_timing->ZQ_CALSTART_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(826)+chn_offset,  0,16, f4_timing->ZQ_CALSTART_HIGH_THRESHOLD);

    //zq_calstart_norm_threshold
	reg_bit_set(CANDS_CTL0_(567)+chn_offset,  0,16, f0_timing->ZQ_CALSTART_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(632)+chn_offset,  0,16, f1_timing->ZQ_CALSTART_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(697)+chn_offset,  0,16, f2_timing->ZQ_CALSTART_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(762)+chn_offset,  0,16, f3_timing->ZQ_CALSTART_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(827)+chn_offset,  0,16, f4_timing->ZQ_CALSTART_NORM_THRESHOLD);

    //zq_calstart_timeout
	reg_bit_set(CANDS_CTL0_(567)+chn_offset, 16,16, f0_timing->ZQ_CALSTART_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(632)+chn_offset, 16,16, f1_timing->ZQ_CALSTART_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(697)+chn_offset, 16,16, f2_timing->ZQ_CALSTART_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(762)+chn_offset, 16,16, f3_timing->ZQ_CALSTART_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(827)+chn_offset, 16,16, f4_timing->ZQ_CALSTART_TIMEOUT);

    //zq_cs_high_threshold
    reg_bit_set(CANDS_CTL0_(568)+chn_offset, 16,16, f0_timing->ZQ_CS_HIGH_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(633)+chn_offset, 16,16, f1_timing->ZQ_CS_HIGH_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(698)+chn_offset, 16,16, f2_timing->ZQ_CS_HIGH_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(763)+chn_offset, 16,16, f3_timing->ZQ_CS_HIGH_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(828)+chn_offset, 16,16, f4_timing->ZQ_CS_HIGH_THRESHOLD);

    //zq_cs_norm_threshold
    reg_bit_set(CANDS_CTL0_(568)+chn_offset,  0,16, f0_timing->ZQ_CS_NORM_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(633)+chn_offset,  0,16, f1_timing->ZQ_CS_NORM_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(698)+chn_offset,  0,16, f2_timing->ZQ_CS_NORM_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(763)+chn_offset,  0,16, f3_timing->ZQ_CS_NORM_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(828)+chn_offset,  0,16, f4_timing->ZQ_CS_NORM_THRESHOLD);

    //zq_cs_timeout
    reg_bit_set(CANDS_CTL0_(569)+chn_offset,  0,16, f0_timing->ZQ_CS_TIMEOUT);
    reg_bit_set(CANDS_CTL0_(634)+chn_offset,  0,16, f1_timing->ZQ_CS_TIMEOUT);
    reg_bit_set(CANDS_CTL0_(699)+chn_offset,  0,16, f2_timing->ZQ_CS_TIMEOUT);
    reg_bit_set(CANDS_CTL0_(764)+chn_offset,  0,16, f3_timing->ZQ_CS_TIMEOUT);
    reg_bit_set(CANDS_CTL0_(829)+chn_offset,  0,16, f4_timing->ZQ_CS_TIMEOUT);

    //zq_promote_threshold
    reg_bit_set(CANDS_CTL0_(569)+chn_offset, 16,16, f0_timing->ZQ_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(634)+chn_offset, 16,16, f1_timing->ZQ_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(699)+chn_offset, 16,16, f2_timing->ZQ_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(764)+chn_offset, 16,16, f3_timing->ZQ_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(829)+chn_offset, 16,16, f4_timing->ZQ_PROMOTE_THRESHOLD);

    //zqcs
    reg_bit_set(CANDS_CTL0_(570)+chn_offset, 16,12, f0_timing->ZQCS);
    reg_bit_set(CANDS_CTL0_(635)+chn_offset, 16,12, f1_timing->ZQCS);
    reg_bit_set(CANDS_CTL0_(700)+chn_offset, 16,12, f2_timing->ZQCS);
    reg_bit_set(CANDS_CTL0_(765)+chn_offset, 16,12, f3_timing->ZQCS);
    reg_bit_set(CANDS_CTL0_(830)+chn_offset, 16,12, f4_timing->ZQCS);

    //zqcl
    reg_bit_set(CANDS_CTL0_(570)+chn_offset,  0,12, f0_timing->ZQCL);
    reg_bit_set(CANDS_CTL0_(635)+chn_offset,  0,12, f1_timing->ZQCL);
    reg_bit_set(CANDS_CTL0_(700)+chn_offset,  0,12, f2_timing->ZQCL);
    reg_bit_set(CANDS_CTL0_(765)+chn_offset,  0,12, f3_timing->ZQCL);
    reg_bit_set(CANDS_CTL0_(830)+chn_offset,  0,12, f4_timing->ZQCL);


    //zqinit
    reg_bit_set(CANDS_CTL0_(571)+chn_offset, 16,12, f0_timing->ZQINIT);
    reg_bit_set(CANDS_CTL0_(636)+chn_offset, 16,12, f1_timing->ZQINIT);
    reg_bit_set(CANDS_CTL0_(701)+chn_offset, 16,12, f2_timing->ZQINIT);
    reg_bit_set(CANDS_CTL0_(766)+chn_offset, 16,12, f3_timing->ZQINIT);
    reg_bit_set(CANDS_CTL0_(831)+chn_offset, 16,12, f4_timing->ZQINIT);

    //zqreset
    reg_bit_set(CANDS_CTL0_(571)+chn_offset,  0,12, f0_timing->ZQRESET);
    reg_bit_set(CANDS_CTL0_(636)+chn_offset,  0,12, f1_timing->ZQRESET);
    reg_bit_set(CANDS_CTL0_(701)+chn_offset,  0,12, f2_timing->ZQRESET);
    reg_bit_set(CANDS_CTL0_(766)+chn_offset,  0,12, f3_timing->ZQRESET);
    reg_bit_set(CANDS_CTL0_(831)+chn_offset,  0,12, f4_timing->ZQRESET);
	#endif
}



void cands_ctl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,
					CANDS_CTL_TIMING_T * ctl_timing, CANDS_CTL_PERCHN_QOS_T* perchn_qos,CANDS_CTL_ALLCHN_QOS_T* allchn_qos,
					uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{

	//timing init
	cands_ctl_actiming_init(chn_num,ctl_timing,f0,f1,f2,f3,f4);
	cands_ctl_othertiming_init(chn_num,ctl_timing,f0,f1,f2,f3,f4);

	//mode init
	cands_ctl_addrmap_init(chn_num,ddr_type);
	cands_ctl_basicmode_init(chn_num,ddr_type);
	cands_ctl_calvl_init(chn_num,ddr_type,ctl_timing,f0,f1,f2,f3,f4);
	cands_ctl_dfi_init(chn_num,ddr_type,ctl_timing,f0,f1,f2,f3,f4);
	cands_ctl_dfs_init(chn_num,ddr_type);
	cands_ctl_fsp_init(chn_num,ddr_type);
	cands_ctl_latency_init( chn_num,ctl_timing,f0,f1,f2,f3,f4);
	cands_ctl_lowpower_init(chn_num,ctl_timing,f0,f1,f2,f3,f4);
	cands_ctl_modreg_init(chn_num,ctl_timing,f0,f1,f2,f3,f4);
	cands_ctl_odt_init(chn_num,ctl_timing,f0,f1,f2,f3,f4);
	cands_ctl_qos_init(chn_num,ddr_type,perchn_qos,allchn_qos);
	cands_ctl_rdlvl_init(chn_num,ctl_timing,ddr_type,f0,f1,f2,f3,f4);
	cands_ctl_wrlvl_init(chn_num,ctl_timing,ddr_type,f0,f1,f2,f3,f4);
	cands_ctl_zq_init(chn_num,ctl_timing,ddr_type,f0,f1,f2,f3,f4);


}

void cands_pi_timing_map(uint32 set_sum,CANDS_PI_TIMING_T *pi_timing,
			 uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4,
			 CANDS_PI_TIMING_T *f0_timing,CANDS_PI_TIMING_T *f1_timing,
			 CANDS_PI_TIMING_T *f2_timing,CANDS_PI_TIMING_T *f3_timing,
			 CANDS_PI_TIMING_T *f4_timing)
{
	uint32 i = 0;

	for(i = 0; i < set_sum; i++)
	{
		if(pi_timing[i].ddr_clk == f0)
		{
				temp_fn[0] = (uint32)(&pi_timing[i]);
		}

		if(pi_timing[i].ddr_clk == f1)
		{
				temp_fn[1] = (uint32)(&pi_timing[i]);
		}

		if(pi_timing[i].ddr_clk == f2)
		{
				temp_fn[2] = (uint32)(&pi_timing[i]);
		}

		if(pi_timing[i].ddr_clk == f3)
		{
				temp_fn[3] = (uint32)(&pi_timing[i]);
		}

		if(pi_timing[i].ddr_clk == f4)
		{
				temp_fn[4] = (uint32)(&pi_timing[i]);
		}
	}

}

void cands_pi_addrmap_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type) ///  ????????
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 bank_diff = 0;
	uint32 row_diff = 0;
	uint32 col_diff = 0;

	uint32 i = 0;


	if(IS_LPDDR3(ddr_type))
	{
		switch(ddr_type)
		{
			case DRAM_LPDDR3_1CS_4G_X32:
			case DRAM_LPDDR3_2CS_8G_X32:
				row_diff = 2; col_diff = 2;break;
			case DRAM_LPDDR3_1CS_6G_X32:
            		case DRAM_LPDDR3_2CS_12G_X32:
				row_diff = 1; col_diff = 2;break;
			case DRAM_LPDDR3_1CS_8G_X32:
			case DRAM_LPDDR3_2CS_16G_X32:
				row_diff = 1; col_diff = 2;break;
            		case DRAM_LPDDR3_1CS_8G_X16X2:
			case DRAM_LPDDR3_2CS_16G_X32_X16X4:
				row_diff = 2; col_diff = 1;break;
			default:   while(1); //invalid density
		}
	}
	else if(IS_LPDDR4(ddr_type)) //lpddr4
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
			row_diff = 0; col_diff = 2;break;
			case DRAM_LPDDR4_1CS_16G_X32:
			case DRAM_LPDDR4_2CS_32G_X32:
			row_diff = 0; col_diff = 2;break;
			default: while(1); //invalid density
		}
	}

	reg_bit_set(CANDS_PI0_(230)+chn_offset,8,2,bank_diff);
	reg_bit_set(CANDS_PI0_(230)+chn_offset,16,3,row_diff);
	reg_bit_set(CANDS_PI0_(295)+chn_offset, 0,4,col_diff);

}

void cands_pi_seq_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 i = 0;
	#ifdef DRAM_LPDDR3
	//pi_seq1_pat
	__raw_writel(CANDS_PI0_(39), 0xf7f003f0);
	__raw_writel(CANDS_PI0_(40), 0xf);

	//pi_seq1_pat_msk
	__raw_writel(CANDS_PI0_(41), 0xf7fff000);
	__raw_writel(CANDS_PI0_(42), 0x7);

	//pi_seq2_pat
	__raw_writel(CANDS_PI0_(43), 0xf7f000a0);
	__raw_writel(CANDS_PI0_(44), 0xf);

	//pi_seq2_pat_msk
	__raw_writel(CANDS_PI0_(45), 0xf7fff000);
	__raw_writel(CANDS_PI0_(46), 0x7);

	//pi_seq3_pat
	__raw_writel(CANDS_PI0_(47), 0xf7f00020);
	__raw_writel(CANDS_PI0_(48), 0xf);

	//pi_seq3_pat_msk
	__raw_writel(CANDS_PI0_(49), 0xf7fff000);
	__raw_writel(CANDS_PI0_(50), 0x7);

	//pi_seq4_pat
	__raw_writel(CANDS_PI0_(51), 0xf7f00030);
	__raw_writel(CANDS_PI0_(52), 0xf);

	//pi_seq4_pat_msk
	__raw_writel(CANDS_PI0_(53), 0xf7fff000);
	__raw_writel(CANDS_PI0_(54), 0x7);

	//pi_seq5_pat
	__raw_writel(CANDS_PI0_(55), 0xf7f000b0);
	__raw_writel(CANDS_PI0_(56), 0xf);

	//pi_seq5_pat_msk
	__raw_writel(CANDS_PI0_(57), 0xf7fff000);
	__raw_writel(CANDS_PI0_(58), 0x7);

	//pi_seq6_pat
	__raw_writel(CANDS_PI0_(59), 0xf7f00100);
	__raw_writel(CANDS_PI0_(60), 0xf);

	//pi_seq6_pat_msk
	__raw_writel(CANDS_PI0_(61), 0xf7fff000);
	__raw_writel(CANDS_PI0_(62), 0x7);

	//pi_seq7_pat
	__raw_writel(CANDS_PI0_(63), 0xf7f00110);
	__raw_writel(CANDS_PI0_(64), 0xf);

	//pi_seq7_pat_msk
	__raw_writel(CANDS_PI0_(65), 0xf7fff000);
	__raw_writel(CANDS_PI0_(66), 0x7);

	//pi_seq8_pat
	__raw_writel(CANDS_PI0_(67), 0xf7f00010);
	__raw_writel(CANDS_PI0_(68), 0xf);

	//pi_seq8_pat_msk
	__raw_writel(CANDS_PI0_(69), 0xf7fff000);
	reg_bit_set(CANDS_PI0_(70)+chn_offset,0,4,7);
	#else
	for(i = 0; i < 31; i++)
	{
		REG32(CANDS_PI0_((39+i))) = 0;
	}

	reg_bit_set(CANDS_PI0_(70)+chn_offset,0,4,0);
	#endif
}
void cands_pi_basicmode_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,uint32 cs_map)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//pi_start
	//reg_bit_set(CANDS_PI0_(0)+chn_offset,0,1,PI_INITLVL_EN);

	//dram class
	reg_bit_set(CANDS_PI0_(0)+chn_offset,8,4,islp3?0x7:0xb);

	//normal_lvl_seq ???????
	reg_bit_set(CANDS_PI0_(1)+chn_offset,0,1,PI_NORMAL_LVL_EN);

	//pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(1)+chn_offset,8,1,PI_INITLVL_EN);

	//pi_bstlen
	//reg_bit_set(CANDS_PI0_(268)+chn_offset,8,5,islp3?3:4);

	//pi_cs_map
	reg_bit_set(CANDS_PI0_(71)+chn_offset,0,8,cs_map);


	//pi_tcmd_gap
	reg_bit_set(CANDS_PI0_(1)+chn_offset,16,16,0);

	//pi_exit_after_init_calvl
	reg_bit_set(CANDS_PI0_(36)+chn_offset,16,1,1);

	//pi_freq_map
	__raw_writel(CANDS_PI0_(37)+chn_offset, (PI_F4_TRAIN<<4)|(PI_F3_TRAIN<<3)|(PI_F2_TRAIN<<2)|(PI_F1_TRAIN<<1)|PI_F0_TRAIN); //  ???????

	//pi_init_work_freq
	reg_bit_set(CANDS_PI0_(38)+chn_offset,0,5, fn_pi_target);

	//pi_init_dfs_calvl_only
	reg_bit_set(CANDS_PI0_(38)+chn_offset,8,1,0);

	//pi_power_on_seq_bypass_array
	reg_bit_set(CANDS_PI0_(38)+chn_offset,16,8,0x00);

	//pi_power_on_seq_end_array
	reg_bit_set(CANDS_PI0_(38)+chn_offset,24,8,islp3?0x80:0x1);

	//pi_wdt_disable
	reg_bit_set(CANDS_PI0_(70)+chn_offset,8,1,1);

	//pi_sw_rst_n
	reg_bit_set(CANDS_PI0_(70)+chn_offset,16,1,1);

	//pi_preamble_support
	reg_bit_set(CANDS_PI0_(75)+chn_offset,8,2,islp3?0:2);//?????


	//pi_dfs_prediod_en, enable dfs-triggered periodic leveling
	reg_bit_set(CANDS_PI0_(89)+chn_offset,8,1,islp3?PI_DFS_PERDIC_LVL_EN_LP3:PI_DFS_PERDIC_LVL_EN_LP4);

	//pi_sre_prediod_en, enable selfrefresh exit-triggered periodic leveling
	reg_bit_set(CANDS_PI0_(89)+chn_offset,16,1,islp3?PI_SRE_PERDIC_LVL_EN_LP3:PI_SRE_PERDIC_LVL_EN_LP4);

	//pi_16bit_dram_connect
	//reg_bit_set(CANDS_PI0_(89)+chn_offset,24,1,IS_16BIT(ddr_type)?1:0);
	reg_bit_set(CANDS_PI0_(89)+chn_offset,24,1,IS_16BIT(ddr_type)?1:(islp3?0:1));

	//pi_en_odt_assert_except_rd
	reg_bit_set(CANDS_PI0_(105)+chn_offset,24,1,0);  //?????

	//pi_clkdisable_2_init_start
	reg_bit_set(CANDS_PI0_(157)+chn_offset,16,8,0x4); //??????

	//pi_init_startorcomplete_2_init_start
	reg_bit_set(CANDS_PI0_(157)+chn_offset,24,8,0x4); //?????

	//pi_dram_clk_disable_deassert_sel
	reg_bit_set(CANDS_PI0_(158)+chn_offset, 0,1,0x0);

	//pi_refresh_between_segment_disable
	reg_bit_set(CANDS_PI0_(158)+chn_offset, 8,1,0x1);

	//pi_cmd_swap_en
	reg_bit_set(CANDS_PI0_(268)+chn_offset, 24,1,1);

	//pi_long_count_mask
	reg_bit_set(CANDS_PI0_(268)+chn_offset,16,5,0);

	//pi_bstlen
	reg_bit_set(CANDS_PI0_(268)+chn_offset,8,5,islp3?3:4);

	//pi_ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_PI0_(278)+chn_offset, 8,1,1);

	//odt_rd_map_cs
	reg_bit_set(CANDS_PI0_(101)+chn_offset, 24,8,0x1);	//cs0
	reg_bit_set(CANDS_PI0_(102)+chn_offset,  8,8,0x2);	//cs1
	reg_bit_set(CANDS_PI0_(102)+chn_offset, 24,8,0x4);	//cs2
	reg_bit_set(CANDS_PI0_(103)+chn_offset,  8,8,0x8);	//cs3
	reg_bit_set(CANDS_PI0_(103)+chn_offset, 24,8,0x10);	//cs4
	reg_bit_set(CANDS_PI0_(104)+chn_offset,  8,8,0x20);	//cs5
	reg_bit_set(CANDS_PI0_(104)+chn_offset, 24,8,0x40);	//cs6
	reg_bit_set(CANDS_PI0_(105)+chn_offset,  8,8,0x80);	//cs7

	//odt_wr_map_cs
	reg_bit_set(CANDS_PI0_(102)+chn_offset,  0,8,0x1);	//cs0
	reg_bit_set(CANDS_PI0_(102)+chn_offset, 16,8,0x2);	//cs1
	reg_bit_set(CANDS_PI0_(103)+chn_offset,  0,8,0x4);	//cs2
	reg_bit_set(CANDS_PI0_(103)+chn_offset, 16,8,0x8);	//cs3
	reg_bit_set(CANDS_PI0_(104)+chn_offset,  0,8,0x10);	//cs4
	reg_bit_set(CANDS_PI0_(104)+chn_offset, 16,8,0x20);	//cs5
	reg_bit_set(CANDS_PI0_(105)+chn_offset,  0,8,0x40);	//cs6
	reg_bit_set(CANDS_PI0_(105)+chn_offset, 16,8,0x80);	//cs7

	//address map init
	cands_pi_addrmap_init(chn_num, ddr_type);

	//int seq pattern
	cands_pi_seq_init(chn_num, ddr_type);

}
void cands_pi_actiming_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_PI_TIMING_T *pi_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PI_TIMING_T * f0_timing = NULL;
	CANDS_PI_TIMING_T * f1_timing = NULL;
	CANDS_PI_TIMING_T * f2_timing = NULL;
	CANDS_PI_TIMING_T * f3_timing = NULL;
	CANDS_PI_TIMING_T * f4_timing = NULL;
	CANDS_PI_TIMING_T **timing = (CANDS_PI_TIMING_T **)temp_fn;
#else
	volatile CANDS_PI_TIMING_T * f0_timing = NULL;
	volatile CANDS_PI_TIMING_T * f1_timing = NULL;
	volatile CANDS_PI_TIMING_T * f2_timing = NULL;
	volatile CANDS_PI_TIMING_T * f3_timing = NULL;
	volatile CANDS_PI_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;


	cands_pi_timing_map(TIMING_SET_SUM,pi_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_PI_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PI_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PI_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PI_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_PI_TIMING_T *)(temp_fn[4]);

	//caslat_lin
	reg_bit_set(CANDS_PI0_(73)+chn_offset, 0,7,f0_timing->PI_CASLAT_LIN_Fx);
	reg_bit_set(CANDS_PI0_(73)+chn_offset,16,7,f1_timing->PI_CASLAT_LIN_Fx);
	reg_bit_set(CANDS_PI0_(74)+chn_offset, 0,7,f2_timing->PI_CASLAT_LIN_Fx);
	reg_bit_set(CANDS_PI0_(74)+chn_offset,16,7,f3_timing->PI_CASLAT_LIN_Fx);
	reg_bit_set(CANDS_PI0_(75)+chn_offset, 0,7,f4_timing->PI_CASLAT_LIN_Fx);

	//rdlat_adj
	reg_bit_set(CANDS_PI0_(121)+chn_offset, 0,7,f0_timing->PI_RDLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(121)+chn_offset, 8,7,f1_timing->PI_RDLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(121)+chn_offset,16,7,f2_timing->PI_RDLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(121)+chn_offset,24,7,f3_timing->PI_RDLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(122)+chn_offset, 0,7,f4_timing->PI_RDLAT_ADJ_Fx);

	//wrlat
	reg_bit_set(CANDS_PI0_(72)+chn_offset,24,6,f0_timing->PI_WRLAT_Fx);
	reg_bit_set(CANDS_PI0_(73)+chn_offset, 8,6,f1_timing->PI_WRLAT_Fx);
	reg_bit_set(CANDS_PI0_(73)+chn_offset,24,6,f2_timing->PI_WRLAT_Fx);
	reg_bit_set(CANDS_PI0_(74)+chn_offset, 8,6,f3_timing->PI_WRLAT_Fx);
	reg_bit_set(CANDS_PI0_(74)+chn_offset,24,6,f4_timing->PI_WRLAT_Fx);

	//wrlat_adj
	reg_bit_set(CANDS_PI0_(122)+chn_offset,16,7,f0_timing->PI_WRLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(122)+chn_offset,24,7,f1_timing->PI_WRLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(123)+chn_offset, 0,7,f2_timing->PI_WRLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(123)+chn_offset, 8,7,f3_timing->PI_WRLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(123)+chn_offset,16,7,f4_timing->PI_WRLAT_ADJ_Fx);

	//tcackel
	reg_bit_set(CANDS_PI0_(136)+chn_offset,16,5,f0_timing->PI_TCACKEL);

	//tcamrd
	reg_bit_set(CANDS_PI0_(136)+chn_offset,24,6,f0_timing->PI_TCAMRD);

	//tcackeh
	reg_bit_set(CANDS_PI0_(137)+chn_offset, 0,5,f0_timing->PI_TCACKEH);

	//tcaent
	reg_bit_set(CANDS_PI0_(137)+chn_offset,16,14,f0_timing->PI_TCAENT);
	reg_bit_set(CANDS_PI0_(138)+chn_offset,8,14,f1_timing->PI_TCAENT);
	reg_bit_set(CANDS_PI0_(139)+chn_offset,0,14,f2_timing->PI_TCAENT);
	reg_bit_set(CANDS_PI0_(140)+chn_offset,0,14,f3_timing->PI_TCAENT);
	reg_bit_set(CANDS_PI0_(141)+chn_offset,0,14,f4_timing->PI_TCAENT);

	//tcaext
	reg_bit_set(CANDS_PI0_(141)+chn_offset,16,5,f0_timing->PI_TCAEXT);

	//tccd
	reg_bit_set(CANDS_PI0_(233)+chn_offset,16,5,f0_timing->PI_TCCD);

	//tccdmw
	reg_bit_set(CANDS_PI0_(236)+chn_offset, 8,6,f0_timing->PI_TCCDMW_Fx);
	reg_bit_set(CANDS_PI0_(239)+chn_offset,16,6,f1_timing->PI_TCCDMW_Fx);
	reg_bit_set(CANDS_PI0_(243)+chn_offset, 8,6,f2_timing->PI_TCCDMW_Fx);
	reg_bit_set(CANDS_PI0_(246)+chn_offset,16,6,f3_timing->PI_TCCDMW_Fx);
	reg_bit_set(CANDS_PI0_(250)+chn_offset, 8,6,f4_timing->PI_TCCDMW_Fx);

	//tckckeh
	reg_bit_set(CANDS_PI0_(152)+chn_offset,16,4,f0_timing->PI_TCKCKEH);

	//tckehdqs
	reg_bit_set(CANDS_PI0_(158)+chn_offset,16,6,f0_timing->PI_TCKEHDQS_Fx);
	reg_bit_set(CANDS_PI0_(158)+chn_offset,24,6,f1_timing->PI_TCKEHDQS_Fx);
	reg_bit_set(CANDS_PI0_(159)+chn_offset, 0,6,f2_timing->PI_TCKEHDQS_Fx);
	reg_bit_set(CANDS_PI0_(159)+chn_offset, 8,6,f3_timing->PI_TCKEHDQS_Fx);
	reg_bit_set(CANDS_PI0_(159)+chn_offset,16,6,f4_timing->PI_TCKEHDQS_Fx);

	//tdqsck_max
	reg_bit_set(CANDS_PI0_(236)+chn_offset, 0,4,f0_timing->PI_TDQSCK_MAX_Fx);
	reg_bit_set(CANDS_PI0_(239)+chn_offset, 8,4,f1_timing->PI_TDQSCK_MAX_Fx);
	reg_bit_set(CANDS_PI0_(243)+chn_offset, 0,4,f2_timing->PI_TDQSCK_MAX_Fx);
	reg_bit_set(CANDS_PI0_(246)+chn_offset, 8,4,f3_timing->PI_TDQSCK_MAX_Fx);
	reg_bit_set(CANDS_PI0_(250)+chn_offset, 0,4,f4_timing->PI_TDQSCK_MAX_Fx);

	//tdelay_rdwr_2_bus_idle
	reg_bit_set(CANDS_PI0_(71)+chn_offset,  8,8,f0_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);
	reg_bit_set(CANDS_PI0_(71)+chn_offset, 16,8,f1_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);
	reg_bit_set(CANDS_PI0_(71)+chn_offset, 24,8,f2_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);
	reg_bit_set(CANDS_PI0_(72)+chn_offset,  0,8,f3_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);
	reg_bit_set(CANDS_PI0_(72)+chn_offset,  8,8,f4_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);

	//tfc
	reg_bit_set(CANDS_PI0_(231)+chn_offset, 0,10,f0_timing->PI_TFC_Fx);
	reg_bit_set(CANDS_PI0_(231)+chn_offset, 0,16,f1_timing->PI_TFC_Fx);
	reg_bit_set(CANDS_PI0_(232)+chn_offset, 0,10,f2_timing->PI_TFC_Fx);
	reg_bit_set(CANDS_PI0_(232)+chn_offset, 0,16,f3_timing->PI_TFC_Fx);
	reg_bit_set(CANDS_PI0_(233)+chn_offset, 0,10,f4_timing->PI_TFC_Fx);

	//tmrd
	reg_bit_set(CANDS_PI0_(236)+chn_offset,16,6,f0_timing->PI_TMRD_Fx);
	reg_bit_set(CANDS_PI0_(239)+chn_offset,24,6,f1_timing->PI_TMRD_Fx);
	reg_bit_set(CANDS_PI0_(243)+chn_offset,16,6,f2_timing->PI_TMRD_Fx);
	reg_bit_set(CANDS_PI0_(246)+chn_offset,24,6,f3_timing->PI_TMRD_Fx);
	reg_bit_set(CANDS_PI0_(250)+chn_offset,16,6,f4_timing->PI_TMRD_Fx);

	//tmrr
	reg_bit_set(CANDS_PI0_(72)+chn_offset,16,4,f0_timing->PI_TMRR);

	//tmrw
	reg_bit_set(CANDS_PI0_(236)+chn_offset,24,8,f0_timing->PI_TMRW_Fx);
	reg_bit_set(CANDS_PI0_(240)+chn_offset, 0,8,f1_timing->PI_TMRW_Fx);
	reg_bit_set(CANDS_PI0_(243)+chn_offset,24,8,f2_timing->PI_TMRW_Fx);
	reg_bit_set(CANDS_PI0_(247)+chn_offset, 0,8,f3_timing->PI_TMRW_Fx);
	reg_bit_set(CANDS_PI0_(250)+chn_offset,24,8,f4_timing->PI_TMRW_Fx);

	//tmrz
	reg_bit_set(CANDS_PI0_(137)+chn_offset, 8,5,f0_timing->PI_TMRZ_Fx);
	reg_bit_set(CANDS_PI0_(138)+chn_offset, 0,5,f1_timing->PI_TMRZ_Fx);
	reg_bit_set(CANDS_PI0_(138)+chn_offset,24,5,f2_timing->PI_TMRZ_Fx);
	reg_bit_set(CANDS_PI0_(139)+chn_offset,16,5,f3_timing->PI_TMRZ_Fx);
	reg_bit_set(CANDS_PI0_(140)+chn_offset,16,5,f4_timing->PI_TMRZ_Fx);

	//tras_max
	reg_bit_set(CANDS_PI0_(235)+chn_offset,0,17,f0_timing->PI_TRAS_MAX_Fx);
	reg_bit_set(CANDS_PI0_(238)+chn_offset,8,17,f1_timing->PI_TRAS_MAX_Fx);
	reg_bit_set(CANDS_PI0_(242)+chn_offset,0,17,f2_timing->PI_TRAS_MAX_Fx);
	reg_bit_set(CANDS_PI0_(245)+chn_offset,8,17,f3_timing->PI_TRAS_MAX_Fx);
	reg_bit_set(CANDS_PI0_(249)+chn_offset,0,17,f4_timing->PI_TRAS_MAX_Fx);

	//tras_min
	reg_bit_set(CANDS_PI0_(235)+chn_offset,24,8,f0_timing->PI_TRAS_MIN_Fx);
	reg_bit_set(CANDS_PI0_(239)+chn_offset, 0,8,f1_timing->PI_TRAS_MIN_Fx);
	reg_bit_set(CANDS_PI0_(242)+chn_offset,24,8,f2_timing->PI_TRAS_MIN_Fx);
	reg_bit_set(CANDS_PI0_(246)+chn_offset, 0,8,f3_timing->PI_TRAS_MIN_Fx);
	reg_bit_set(CANDS_PI0_(249)+chn_offset,24,8,f4_timing->PI_TRAS_MIN_Fx);

	//trcd
	reg_bit_set(CANDS_PI0_(234)+chn_offset, 8,8,f0_timing->PI_TRCD_Fx);
	reg_bit_set(CANDS_PI0_(237)+chn_offset,16,8,f1_timing->PI_TRCD_Fx);
	reg_bit_set(CANDS_PI0_(240)+chn_offset,24,8,f2_timing->PI_TRCD_Fx);
	reg_bit_set(CANDS_PI0_(244)+chn_offset,16,8,f3_timing->PI_TRCD_Fx);
	reg_bit_set(CANDS_PI0_(247)+chn_offset,24,8,f4_timing->PI_TRCD_Fx);

	//tref
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_PI0_(76+i)+chn_offset,16,16,timing[i]->PI_TREF_Fx);
	}
	#else
	reg_bit_set(CANDS_PI0_(76)+chn_offset,16,16,f0_timing->PI_TREF_Fx);
	reg_bit_set(CANDS_PI0_(77)+chn_offset,16,16,f1_timing->PI_TREF_Fx);
	reg_bit_set(CANDS_PI0_(78)+chn_offset,16,16,f2_timing->PI_TREF_Fx);
	reg_bit_set(CANDS_PI0_(79)+chn_offset,16,16,f3_timing->PI_TREF_Fx);
	reg_bit_set(CANDS_PI0_(80)+chn_offset,16,16,f4_timing->PI_TREF_Fx);
	#endif

	//tref_interval
	reg_bit_set(CANDS_PI0_(81)+chn_offset, 0,16,f0_timing->PI_TREF_INTERVAL);

	//trfc
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_PI0_(76+i)+chn_offset, 0,10,timing[i]->PI_TRFC_Fx);
	}
	#else
	reg_bit_set(CANDS_PI0_(76)+chn_offset, 0,10,f0_timing->PI_TRFC_Fx);
	reg_bit_set(CANDS_PI0_(77)+chn_offset, 0,10,f1_timing->PI_TRFC_Fx);
	reg_bit_set(CANDS_PI0_(78)+chn_offset, 0,10,f2_timing->PI_TRFC_Fx);
	reg_bit_set(CANDS_PI0_(79)+chn_offset, 0,10,f3_timing->PI_TRFC_Fx);
	reg_bit_set(CANDS_PI0_(80)+chn_offset, 0,10,f4_timing->PI_TRFC_Fx);
	#endif

	//trp
	reg_bit_set(CANDS_PI0_(234)+chn_offset, 0,8,f0_timing->PI_TRP_Fx);
	reg_bit_set(CANDS_PI0_(237)+chn_offset, 8,8,f1_timing->PI_TRP_Fx);
	reg_bit_set(CANDS_PI0_(240)+chn_offset,16,8,f2_timing->PI_TRP_Fx);
	reg_bit_set(CANDS_PI0_(244)+chn_offset, 8,8,f3_timing->PI_TRP_Fx);
	reg_bit_set(CANDS_PI0_(247)+chn_offset,16,8,f4_timing->PI_TRP_Fx);

	//trtp
	reg_bit_set(CANDS_PI0_(233)+chn_offset,24,4,f0_timing->PI_TRTP_Fx);
	reg_bit_set(CANDS_PI0_(237)+chn_offset, 0,4,f1_timing->PI_TRTP_Fx);
	reg_bit_set(CANDS_PI0_(240)+chn_offset, 8,4,f2_timing->PI_TRTP_Fx);
	reg_bit_set(CANDS_PI0_(244)+chn_offset, 0,4,f3_timing->PI_TRTP_Fx);
	reg_bit_set(CANDS_PI0_(247)+chn_offset, 8,4,f4_timing->PI_TRTP_Fx);

	//tvref_short
	reg_bit_set(CANDS_PI0_(142)+chn_offset,16,10,f0_timing->PI_TVREF_SHORT_Fx);
	reg_bit_set(CANDS_PI0_(144)+chn_offset, 0,10,f1_timing->PI_TVREF_SHORT_Fx);
	reg_bit_set(CANDS_PI0_(145)+chn_offset,16,10,f2_timing->PI_TVREF_SHORT_Fx);
	reg_bit_set(CANDS_PI0_(147)+chn_offset, 0,10,f3_timing->PI_TVREF_SHORT_Fx);
	reg_bit_set(CANDS_PI0_(148)+chn_offset,16,10,f4_timing->PI_TVREF_SHORT_Fx);

	//reversed
	reg_bit_set(CANDS_PI0_(148)+chn_offset, 8,1,1);
	//tvref_long
	reg_bit_set(CANDS_PI0_(143)+chn_offset, 0,10,f0_timing->PI_TVREF_LONG_Fx);
	reg_bit_set(CANDS_PI0_(144)+chn_offset,16,10,f1_timing->PI_TVREF_LONG_Fx);
	reg_bit_set(CANDS_PI0_(146)+chn_offset, 0,10,f2_timing->PI_TVREF_LONG_Fx);
	reg_bit_set(CANDS_PI0_(147)+chn_offset,16,10,f3_timing->PI_TVREF_LONG_Fx);
	reg_bit_set(CANDS_PI0_(149)+chn_offset, 0,10,f4_timing->PI_TVREF_LONG_Fx);

	//twr
	reg_bit_set(CANDS_PI0_(234)+chn_offset,24,6,f0_timing->PI_TWR_Fx);
	reg_bit_set(CANDS_PI0_(238)+chn_offset, 0,6,f1_timing->PI_TWR_Fx);
	reg_bit_set(CANDS_PI0_(241)+chn_offset, 8,6,f2_timing->PI_TWR_Fx);
	reg_bit_set(CANDS_PI0_(245)+chn_offset, 0,6,f3_timing->PI_TWR_Fx);
	reg_bit_set(CANDS_PI0_(248)+chn_offset, 8,6,f4_timing->PI_TWR_Fx);

	//twtr
	reg_bit_set(CANDS_PI0_(234)+chn_offset, 16,6,f0_timing->PI_TWTR_Fx);
	reg_bit_set(CANDS_PI0_(237)+chn_offset, 24,6,f1_timing->PI_TWTR_Fx);
	reg_bit_set(CANDS_PI0_(241)+chn_offset,  0,6,f2_timing->PI_TWTR_Fx);
	reg_bit_set(CANDS_PI0_(244)+chn_offset, 24,6,f3_timing->PI_TWTR_Fx);
	reg_bit_set(CANDS_PI0_(248)+chn_offset, 0,6,f4_timing->PI_TWTR_Fx);

}

void cands_pi_dfitiming_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_CTL_TIMING_T * pi_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PI_TIMING_T * f0_timing = NULL;
	CANDS_PI_TIMING_T * f1_timing = NULL;
	CANDS_PI_TIMING_T * f2_timing = NULL;
	CANDS_PI_TIMING_T * f3_timing = NULL;
	CANDS_PI_TIMING_T * f4_timing = NULL;
	CANDS_PI_TIMING_T ** timing = (CANDS_PI_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PI_TIMING_T * f0_timing = NULL;
	volatile CANDS_PI_TIMING_T * f1_timing = NULL;
	volatile CANDS_PI_TIMING_T * f2_timing = NULL;
	volatile CANDS_PI_TIMING_T * f3_timing = NULL;
	volatile CANDS_PI_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;


	cands_pi_timing_map(TIMING_SET_SUM,pi_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_PI_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PI_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PI_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PI_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_PI_TIMING_T *)(temp_fn[4]);

	//tdfi_phyupd_resp
	reg_bit_set(CANDS_PI0_(11)+chn_offset,16,16,f0_timing->PI_TDFI_PHYUPD_RESP_Fx);
	reg_bit_set(CANDS_PI0_(16)+chn_offset, 0,16,f1_timing->PI_TDFI_PHYUPD_RESP_Fx);
	reg_bit_set(CANDS_PI0_(21)+chn_offset, 0,16,f2_timing->PI_TDFI_PHYUPD_RESP_Fx);
	reg_bit_set(CANDS_PI0_(26)+chn_offset, 0,16,f3_timing->PI_TDFI_PHYUPD_RESP_Fx);
	reg_bit_set(CANDS_PI0_(31)+chn_offset, 0,16,f4_timing->PI_TDFI_PHYUPD_RESP_Fx);
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		__raw_writel(CANDS_PI0_(12+5*i)+chn_offset, timing[i]->PI_TDFI_PHYUPD_TYPE0_Fx);
		__raw_writel(CANDS_PI0_(13+5*i)+chn_offset, timing[i]->PI_TDFI_PHYUPD_TYPE1_Fx);
		__raw_writel(CANDS_PI0_(14+5*i)+chn_offset, timing[i]->PI_TDFI_PHYUPD_TYPE2_Fx);
		__raw_writel(CANDS_PI0_(15+5*i)+chn_offset, timing[i]->PI_TDFI_PHYUPD_TYPE3_Fx);
		__raw_writel(CANDS_PI0_(2+2*i)+chn_offset, timing[i]->PI_TDFI_PHYMSTR_MAX_Fx);
		reg_bit_set(CANDS_PI0_(3+2*i)+chn_offset, 0,16,timing[i]->PI_TDFI_PHYMSTR_RESP_Fx);
	}
	#else
	//tdfi_phyupd_type0
	__raw_writel(CANDS_PI0_(12)+chn_offset, f0_timing->PI_TDFI_PHYUPD_TYPE0_Fx);
	__raw_writel(CANDS_PI0_(17)+chn_offset, f1_timing->PI_TDFI_PHYUPD_TYPE0_Fx);
	__raw_writel(CANDS_PI0_(22)+chn_offset, f2_timing->PI_TDFI_PHYUPD_TYPE0_Fx);
	__raw_writel(CANDS_PI0_(27)+chn_offset, f3_timing->PI_TDFI_PHYUPD_TYPE0_Fx);
	__raw_writel(CANDS_PI0_(32)+chn_offset, f4_timing->PI_TDFI_PHYUPD_TYPE0_Fx);

	//tdfi_phyupd_type1
	__raw_writel(CANDS_PI0_(13)+chn_offset, f0_timing->PI_TDFI_PHYUPD_TYPE1_Fx);
	__raw_writel(CANDS_PI0_(18)+chn_offset, f1_timing->PI_TDFI_PHYUPD_TYPE1_Fx);
	__raw_writel(CANDS_PI0_(23)+chn_offset, f2_timing->PI_TDFI_PHYUPD_TYPE1_Fx);
	__raw_writel(CANDS_PI0_(28)+chn_offset, f3_timing->PI_TDFI_PHYUPD_TYPE1_Fx);
	__raw_writel(CANDS_PI0_(33)+chn_offset, f4_timing->PI_TDFI_PHYUPD_TYPE1_Fx);

	//tdfi_phyupd_type2
	__raw_writel(CANDS_PI0_(14)+chn_offset, f0_timing->PI_TDFI_PHYUPD_TYPE2_Fx);
	__raw_writel(CANDS_PI0_(19)+chn_offset, f1_timing->PI_TDFI_PHYUPD_TYPE2_Fx);
	__raw_writel(CANDS_PI0_(24)+chn_offset, f2_timing->PI_TDFI_PHYUPD_TYPE2_Fx);
	__raw_writel(CANDS_PI0_(29)+chn_offset, f3_timing->PI_TDFI_PHYUPD_TYPE2_Fx);
	__raw_writel(CANDS_PI0_(34)+chn_offset, f4_timing->PI_TDFI_PHYUPD_TYPE2_Fx);

	//tdfi_phyupd_type3
	__raw_writel(CANDS_PI0_(15)+chn_offset, f0_timing->PI_TDFI_PHYUPD_TYPE3_Fx);
	__raw_writel(CANDS_PI0_(20)+chn_offset, f1_timing->PI_TDFI_PHYUPD_TYPE3_Fx);
	__raw_writel(CANDS_PI0_(25)+chn_offset, f2_timing->PI_TDFI_PHYUPD_TYPE3_Fx);
	__raw_writel(CANDS_PI0_(30)+chn_offset, f3_timing->PI_TDFI_PHYUPD_TYPE3_Fx);
	__raw_writel(CANDS_PI0_(35)+chn_offset, f4_timing->PI_TDFI_PHYUPD_TYPE3_Fx);

	//tdfi_phymstr_max
	__raw_writel(CANDS_PI0_(2)+chn_offset, f0_timing->PI_TDFI_PHYMSTR_MAX_Fx);
	__raw_writel(CANDS_PI0_(4)+chn_offset, f1_timing->PI_TDFI_PHYMSTR_MAX_Fx);
	__raw_writel(CANDS_PI0_(6)+chn_offset, f2_timing->PI_TDFI_PHYMSTR_MAX_Fx);
	__raw_writel(CANDS_PI0_(8)+chn_offset, f3_timing->PI_TDFI_PHYMSTR_MAX_Fx);
	__raw_writel(CANDS_PI0_(10)+chn_offset,f4_timing->PI_TDFI_PHYMSTR_MAX_Fx);

	//tdfi_phymstr_resp
	reg_bit_set(CANDS_PI0_(3)+chn_offset, 0,16,f0_timing->PI_TDFI_PHYMSTR_RESP_Fx);
	reg_bit_set(CANDS_PI0_(5)+chn_offset, 0,16,f1_timing->PI_TDFI_PHYMSTR_RESP_Fx);
	reg_bit_set(CANDS_PI0_(7)+chn_offset, 0,16,f2_timing->PI_TDFI_PHYMSTR_RESP_Fx);
	reg_bit_set(CANDS_PI0_(9)+chn_offset, 0,16,f3_timing->PI_TDFI_PHYMSTR_RESP_Fx);
	reg_bit_set(CANDS_PI0_(11)+chn_offset,0,16,f4_timing->PI_TDFI_PHYMSTR_RESP_Fx);
	#endif
	//tdfi_ctrl_delay
	reg_bit_set(CANDS_PI0_(90)+chn_offset, 0,4,f0_timing->PI_TDFI_CTRL_DELAY_Fx);
	reg_bit_set(CANDS_PI0_(90)+chn_offset, 8,4,f1_timing->PI_TDFI_CTRL_DELAY_Fx);
	reg_bit_set(CANDS_PI0_(90)+chn_offset,16,4,f2_timing->PI_TDFI_CTRL_DELAY_Fx);
	reg_bit_set(CANDS_PI0_(90)+chn_offset,24,4,f3_timing->PI_TDFI_CTRL_DELAY_Fx);
	reg_bit_set(CANDS_PI0_(91)+chn_offset, 0,4,f4_timing->PI_TDFI_CTRL_DELAY_Fx);

	//tdfi_wrlvl_en
	reg_bit_set(CANDS_PI0_(94)+chn_offset,16,8,f0_timing->PI_TDFI_WRLVL_EN);

	//tdfi_wrlvl_ww
	reg_bit_set(CANDS_PI0_(95)+chn_offset, 0,10,f0_timing->PI_TDFI_WRLVL_WW);

	//tdfi_wrlvl_resp
	reg_bit_set(CANDS_PI0_(96)+chn_offset, 0,32,f0_timing->PI_TDFI_WRLVL_RESP);

	//tdfi_wrlvl_max
	reg_bit_set(CANDS_PI0_(97)+chn_offset, 0,32,f0_timing->PI_TDFI_WRLVL_MAX);

	//tdfi_rdlvl_en
	reg_bit_set(CANDS_PI0_(116)+chn_offset, 8,8,f0_timing->PI_TDFI_RDLVL_EN);

	//tdfi_rdlvl_rr
	reg_bit_set(CANDS_PI0_(114)+chn_offset,16,10,f0_timing->PI_TDFI_RDLVL_RR);

	//tdfi_rdlvl_resp
	reg_bit_set(CANDS_PI0_(115)+chn_offset, 0,32,f0_timing->PI_TDFI_RDLVL_RESP);

	//tdfi_rdlvl_max
	reg_bit_set(CANDS_PI0_(117)+chn_offset, 0,32,f0_timing->PI_TDFI_RDLVL_MAX);

	//tdfi_rddata_en
	reg_bit_set(CANDS_PI0_(122)+chn_offset, 8,7,f0_timing->PI_TDFI_RDDATA_EN);

	//tdfi_wrcslat
	reg_bit_set(CANDS_PI0_(124)+chn_offset, 0,7,f0_timing->PI_TDFI_WRCSLAT_Fx);
	reg_bit_set(CANDS_PI0_(124)+chn_offset, 8,7,f1_timing->PI_TDFI_WRCSLAT_Fx);
	reg_bit_set(CANDS_PI0_(124)+chn_offset,16,7,f2_timing->PI_TDFI_WRCSLAT_Fx);
	reg_bit_set(CANDS_PI0_(124)+chn_offset,24,7,f3_timing->PI_TDFI_WRCSLAT_Fx);
	reg_bit_set(CANDS_PI0_(125)+chn_offset, 0,7,f4_timing->PI_TDFI_WRCSLAT_Fx);

	//tdfi_phy_wrdata
	reg_bit_set(CANDS_PI0_(125)+chn_offset, 8,3,f0_timing->PI_TDFI_PHY_WRDATA);

	//tdfi_calvl_en
	reg_bit_set(CANDS_PI0_(127)+chn_offset,24,8,f0_timing->PI_TDFI_CALVL_EN);

	//tdfi_calvl_cc
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_PI0_(128+i)+chn_offset, 0,10,timing[i]->PI_TDFI_CALVL_CC_Fx);
		reg_bit_set(CANDS_PI0_(128+i)+chn_offset, 16,10,timing[i]->PI_TDFI_CALVL_CAPTURE_Fx);
	}
	#else
	reg_bit_set(CANDS_PI0_(128)+chn_offset, 0,10,f0_timing->PI_TDFI_CALVL_CC_Fx);
	reg_bit_set(CANDS_PI0_(129)+chn_offset, 0,10,f1_timing->PI_TDFI_CALVL_CC_Fx);
	reg_bit_set(CANDS_PI0_(130)+chn_offset, 0,10,f2_timing->PI_TDFI_CALVL_CC_Fx);
	reg_bit_set(CANDS_PI0_(131)+chn_offset, 0,10,f3_timing->PI_TDFI_CALVL_CC_Fx);
	reg_bit_set(CANDS_PI0_(132)+chn_offset, 0,10,f4_timing->PI_TDFI_CALVL_CC_Fx);

	//tdfi_calvl_capture
	reg_bit_set(CANDS_PI0_(128)+chn_offset, 16,10,f0_timing->PI_TDFI_CALVL_CAPTURE_Fx);
	reg_bit_set(CANDS_PI0_(129)+chn_offset, 16,10,f1_timing->PI_TDFI_CALVL_CAPTURE_Fx);
	reg_bit_set(CANDS_PI0_(130)+chn_offset, 16,10,f2_timing->PI_TDFI_CALVL_CAPTURE_Fx);
	reg_bit_set(CANDS_PI0_(131)+chn_offset, 16,10,f3_timing->PI_TDFI_CALVL_CAPTURE_Fx);
	reg_bit_set(CANDS_PI0_(132)+chn_offset, 16,10,f4_timing->PI_TDFI_CALVL_CAPTURE_Fx);
	#endif

	//tdfi_calvl_resp
	reg_bit_set(CANDS_PI0_(133)+chn_offset, 0,32,f0_timing->PI_TDFI_CALVL_RESP);

	//tdfi_calvl_max
	reg_bit_set(CANDS_PI0_(134)+chn_offset, 0,32,f0_timing->PI_TDFI_CALVL_MAX);

	//tdfi_calvl_strobe
	reg_bit_set(CANDS_PI0_(151)+chn_offset, 8,4,f0_timing->PI_TDFI_CALVL_STROBE_Fx);
	reg_bit_set(CANDS_PI0_(151)+chn_offset,16,4,f1_timing->PI_TDFI_CALVL_STROBE_Fx);
	reg_bit_set(CANDS_PI0_(151)+chn_offset,24,4,f2_timing->PI_TDFI_CALVL_STROBE_Fx);
	reg_bit_set(CANDS_PI0_(152)+chn_offset, 0,4,f3_timing->PI_TDFI_CALVL_STROBE_Fx);
	reg_bit_set(CANDS_PI0_(152)+chn_offset, 8,4,f4_timing->PI_TDFI_CALVL_STROBE_Fx);

	//tdfi_cacsca
	reg_bit_set(CANDS_PI0_(142)+chn_offset, 0,5,f0_timing->PI_TDFI_CACSCA_Fx);
	reg_bit_set(CANDS_PI0_(143)+chn_offset,16,5,f1_timing->PI_TDFI_CACSCA_Fx);
	reg_bit_set(CANDS_PI0_(145)+chn_offset, 0,5,f2_timing->PI_TDFI_CACSCA_Fx);
	reg_bit_set(CANDS_PI0_(146)+chn_offset,16,5,f3_timing->PI_TDFI_CACSCA_Fx);
	reg_bit_set(CANDS_PI0_(148)+chn_offset, 0,5,f4_timing->PI_TDFI_CACSCA_Fx);

	//tdfi_casel
	reg_bit_set(CANDS_PI0_(142)+chn_offset, 8,5,f0_timing->PI_TDFI_CASEL_Fx);
	reg_bit_set(CANDS_PI0_(143)+chn_offset,24,5,f1_timing->PI_TDFI_CASEL_Fx);
	reg_bit_set(CANDS_PI0_(145)+chn_offset, 8,5,f2_timing->PI_TDFI_CASEL_Fx);
	reg_bit_set(CANDS_PI0_(146)+chn_offset,24,5,f3_timing->PI_TDFI_CASEL_Fx);
	reg_bit_set(CANDS_PI0_(148)+chn_offset, 8,5,f4_timing->PI_TDFI_CASEL_Fx);

	//tdfi_init_start_min
	reg_bit_set(CANDS_PI0_(150)+chn_offset,24,8,f0_timing->PI_TDFI_INIT_START_MIN);

	//tdfi_init_complete_min
	reg_bit_set(CANDS_PI0_(151)+chn_offset, 0,8,f0_timing->PI_TDFI_INIT_COMPLETE_MIN);

	//tdfi_init_start
	reg_bit_set(CANDS_PI0_(153)+chn_offset, 8,8,f0_timing->PI_TDFI_INIT_START_Fx);
	reg_bit_set(CANDS_PI0_(154)+chn_offset, 0,8,f1_timing->PI_TDFI_INIT_START_Fx);
	reg_bit_set(CANDS_PI0_(154)+chn_offset,24,8,f2_timing->PI_TDFI_INIT_START_Fx);
	reg_bit_set(CANDS_PI0_(155)+chn_offset,16,8,f3_timing->PI_TDFI_INIT_START_Fx);
	reg_bit_set(CANDS_PI0_(156)+chn_offset,16,8,f4_timing->PI_TDFI_INIT_START_Fx);

	//tdfi_init_complete
	reg_bit_set(CANDS_PI0_(153)+chn_offset,16,16,f0_timing->PI_TDFI_INIT_COMPLETE_Fx);
	reg_bit_set(CANDS_PI0_(154)+chn_offset, 8,16,f1_timing->PI_TDFI_INIT_COMPLETE_Fx);
	reg_bit_set(CANDS_PI0_(155)+chn_offset, 0,16,f2_timing->PI_TDFI_INIT_COMPLETE_Fx);
	reg_bit_set(CANDS_PI0_(156)+chn_offset, 0,16,f3_timing->PI_TDFI_INIT_COMPLETE_Fx);
	reg_bit_set(CANDS_PI0_(157)+chn_offset, 0,16,f4_timing->PI_TDFI_INIT_COMPLETE_Fx);

	//tdfi_wdqlvl_wr
	reg_bit_set(CANDS_PI0_(160)+chn_offset, 8,10,f0_timing->PI_TDFI_WDQLVL_WR);

	//tdfi_wdqlvl_rw
	reg_bit_set(CANDS_PI0_(161)+chn_offset, 0,10,f0_timing->PI_TDFI_WDQLVL_RW);

	//tdfi_wdqlvl_en
	reg_bit_set(CANDS_PI0_(164)+chn_offset, 8,8,f0_timing->PI_TDFI_WDQLVL_EN);

	//tdfi_wdqlvl_resp
	reg_bit_set(CANDS_PI0_(165)+chn_offset, 0,32,f0_timing->PI_TDFI_WDQLVL_RESP);

	//tdfi_wdqlvl_max
	reg_bit_set(CANDS_PI0_(166)+chn_offset, 0,32,f0_timing->PI_TDFI_WDQLVL_MAX);

	//tdfi_ctrlupd_max
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 5; i++) {
		__raw_writel(CANDS_PI0_(279+2*i)+chn_offset, timing[i]->PI_TDFI_CTRLUPD_MAX_Fx);
		__raw_writel(CANDS_PI0_(280+2*i)+chn_offset, timing[i]->PI_TDFI_CTRLUPD_INTERVAL_Fx);
	}
	#else
	__raw_writel(CANDS_PI0_(279)+chn_offset, f0_timing->PI_TDFI_CTRLUPD_MAX_Fx);
	__raw_writel(CANDS_PI0_(281)+chn_offset, f1_timing->PI_TDFI_CTRLUPD_MAX_Fx);
	__raw_writel(CANDS_PI0_(283)+chn_offset, f2_timing->PI_TDFI_CTRLUPD_MAX_Fx);
	__raw_writel(CANDS_PI0_(285)+chn_offset, f3_timing->PI_TDFI_CTRLUPD_MAX_Fx);
	__raw_writel(CANDS_PI0_(287)+chn_offset, f4_timing->PI_TDFI_CTRLUPD_MAX_Fx);

	//tdfi_ctrlupd_interval
	__raw_writel(CANDS_PI0_(280)+chn_offset, f0_timing->PI_TDFI_CTRLUPD_INTERVAL_Fx);
	__raw_writel(CANDS_PI0_(282)+chn_offset, f1_timing->PI_TDFI_CTRLUPD_INTERVAL_Fx);
	__raw_writel(CANDS_PI0_(284)+chn_offset, f2_timing->PI_TDFI_CTRLUPD_INTERVAL_Fx);
	__raw_writel(CANDS_PI0_(286)+chn_offset, f3_timing->PI_TDFI_CTRLUPD_INTERVAL_Fx);
	__raw_writel(CANDS_PI0_(288)+chn_offset, f4_timing->PI_TDFI_CTRLUPD_INTERVAL_Fx);
	#endif

	//init_startorcomplete_2_clkdisable
	reg_bit_set(CANDS_PI0_(157)+chn_offset,24,8,f0_timing->PI_INIT_STARTORCOMPLETE_2_CLKDISABLE);

	//clkdisable_2_init_start
	reg_bit_set(CANDS_PI0_(157)+chn_offset,16,8,f0_timing->PI_CLKDISABLE_2_INIT_START);

}


void cands_pi_odtiming_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_CTL_TIMING_T * pi_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PI_TIMING_T * f0_timing = NULL;
	CANDS_PI_TIMING_T * f1_timing = NULL;
	CANDS_PI_TIMING_T * f2_timing = NULL;
	CANDS_PI_TIMING_T * f3_timing = NULL;
	CANDS_PI_TIMING_T * f4_timing = NULL;
#else
	volatile CANDS_PI_TIMING_T * f0_timing = NULL;
	volatile CANDS_PI_TIMING_T * f1_timing = NULL;
	volatile CANDS_PI_TIMING_T * f2_timing = NULL;
	volatile CANDS_PI_TIMING_T * f3_timing = NULL;
	volatile CANDS_PI_TIMING_T * f4_timing = NULL;
#endif
	uint32 chn_offset = (chn_num==0)?0:0x00800000;


	cands_pi_timing_map(TIMING_SET_SUM,pi_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_PI_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PI_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PI_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PI_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_PI_TIMING_T *)(temp_fn[4]);

	//odt_en
	reg_bit_set(CANDS_PI0_(99)+chn_offset,  0,1,f0_timing->PI_ODT_EN_Fx);
	reg_bit_set(CANDS_PI0_(99)+chn_offset, 16,1,f1_timing->PI_ODT_EN_Fx);
	reg_bit_set(CANDS_PI0_(100)+chn_offset, 0,1,f2_timing->PI_ODT_EN_Fx);
	reg_bit_set(CANDS_PI0_(100)+chn_offset,16,1,f3_timing->PI_ODT_EN_Fx);
	reg_bit_set(CANDS_PI0_(101)+chn_offset, 0,1,f4_timing->PI_ODT_EN_Fx);

	//odtlon
	reg_bit_set(CANDS_PI0_(106)+chn_offset, 0,4,f0_timing->PI_ODTLON_Fx);
	reg_bit_set(CANDS_PI0_(106)+chn_offset,16,4,f1_timing->PI_ODTLON_Fx);
	reg_bit_set(CANDS_PI0_(107)+chn_offset, 0,4,f2_timing->PI_ODTLON_Fx);
	reg_bit_set(CANDS_PI0_(107)+chn_offset,16,4,f3_timing->PI_ODTLON_Fx);
	reg_bit_set(CANDS_PI0_(108)+chn_offset, 0,4,f4_timing->PI_ODTLON_Fx);

	//todth_wr
	reg_bit_set(CANDS_PI0_(101)+chn_offset, 8,4,f0_timing->PI_TODTH_WR);

	//todth_rd
	reg_bit_set(CANDS_PI0_(101)+chn_offset,16,4,f0_timing->PI_TODTH_RD);

	//todtl_2cmd
	reg_bit_set(CANDS_PI0_(98)+chn_offset, 24,8,f0_timing->PI_TODTL_2CMD_Fx);
	reg_bit_set(CANDS_PI0_(99)+chn_offset,  8,8,f1_timing->PI_TODTL_2CMD_Fx);
	reg_bit_set(CANDS_PI0_(99)+chn_offset, 24,8,f2_timing->PI_TODTL_2CMD_Fx);
	reg_bit_set(CANDS_PI0_(100)+chn_offset, 8,8,f3_timing->PI_TODTL_2CMD_Fx);
	reg_bit_set(CANDS_PI0_(100)+chn_offset,24,8,f4_timing->PI_TODTL_2CMD_Fx);

	//todton_min
	reg_bit_set(CANDS_PI0_(106)+chn_offset, 8,4,f0_timing->PI_TODTON_MIN_Fx);
	reg_bit_set(CANDS_PI0_(106)+chn_offset,24,4,f1_timing->PI_TODTON_MIN_Fx);
	reg_bit_set(CANDS_PI0_(107)+chn_offset, 8,4,f2_timing->PI_TODTON_MIN_Fx);
	reg_bit_set(CANDS_PI0_(107)+chn_offset,24,4,f3_timing->PI_TODTON_MIN_Fx);
	reg_bit_set(CANDS_PI0_(108)+chn_offset, 8,4,f4_timing->PI_TODTON_MIN_Fx);

	//wr_to_odth
	reg_bit_set(CANDS_PI0_(108)+chn_offset,16,6,f0_timing->PI_WR_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(108)+chn_offset,24,6,f1_timing->PI_WR_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(109)+chn_offset, 0,6,f2_timing->PI_WR_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(109)+chn_offset, 8,6,f3_timing->PI_WR_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(109)+chn_offset,16,6,f4_timing->PI_WR_TO_ODTH_Fx);

	//rd_to_odth
	reg_bit_set(CANDS_PI0_(109)+chn_offset,24,6,f0_timing->PI_RD_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(110)+chn_offset, 0,6,f1_timing->PI_RD_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(110)+chn_offset, 8,6,f2_timing->PI_RD_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(110)+chn_offset,16,6,f3_timing->PI_RD_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(110)+chn_offset,24,6,f4_timing->PI_RD_TO_ODTH_Fx);

}

void cands_pi_modreg_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_CTL_TIMING_T * pi_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
	volatile CANDS_PI_TIMING_T * f0_timing = NULL;
	volatile CANDS_PI_TIMING_T * f1_timing = NULL;
	volatile CANDS_PI_TIMING_T * f2_timing = NULL;
	volatile CANDS_PI_TIMING_T * f3_timing = NULL;
	volatile CANDS_PI_TIMING_T * f4_timing = NULL;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;


	cands_pi_timing_map(TIMING_SET_SUM,pi_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_PI_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PI_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PI_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PI_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_PI_TIMING_T *)(temp_fn[4]);

	//mr1
	//cs0
	reg_bit_set(CANDS_PI0_(168)+chn_offset, 8,8,f0_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(169)+chn_offset,24,8,f1_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(171)+chn_offset, 8,8,f2_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(172)+chn_offset,24,8,f3_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(174)+chn_offset, 8,8,f4_timing->PI_MR1_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(176)+chn_offset, 0,8,f0_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(177)+chn_offset,16,8,f1_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(179)+chn_offset, 0,8,f2_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(180)+chn_offset,16,8,f3_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(182)+chn_offset, 0,8,f4_timing->PI_MR1_DATA_Fx);
	#ifdef DRAM_LPDDR4
	//cs4
	reg_bit_set(CANDS_PI0_(199)+chn_offset, 8,8,f0_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(200)+chn_offset,24,8,f1_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(202)+chn_offset, 8,8,f2_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(203)+chn_offset,24,8,f3_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(205)+chn_offset, 8,8,f4_timing->PI_MR1_DATA_Fx);
	//cs5
	reg_bit_set(CANDS_PI0_(207)+chn_offset, 0,8,f0_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(208)+chn_offset,16,8,f1_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(210)+chn_offset, 0,8,f2_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(211)+chn_offset,16,8,f3_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(213)+chn_offset, 0,8,f4_timing->PI_MR1_DATA_Fx);
	#endif

	//mr2
	//cs0
	reg_bit_set(CANDS_PI0_(168)+chn_offset,16,8,f0_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(170)+chn_offset, 0,8,f1_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(171)+chn_offset,16,8,f2_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(173)+chn_offset, 0,8,f3_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(174)+chn_offset,16,8,f4_timing->PI_MR2_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(176)+chn_offset, 8,8,f0_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(177)+chn_offset,24,8,f1_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(179)+chn_offset, 8,8,f2_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(180)+chn_offset,24,8,f3_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(182)+chn_offset, 8,8,f4_timing->PI_MR2_DATA_Fx);
	#ifdef DRAM_LPDDR4
	//cs4
	reg_bit_set(CANDS_PI0_(199)+chn_offset,16,8,f0_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(201)+chn_offset, 0,8,f1_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(202)+chn_offset,16,8,f2_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(204)+chn_offset, 0,8,f3_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(205)+chn_offset,16,8,f4_timing->PI_MR2_DATA_Fx);
	//cs5
	reg_bit_set(CANDS_PI0_(207)+chn_offset, 8,8,f0_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(208)+chn_offset,24,8,f1_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(210)+chn_offset, 8,8,f2_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(211)+chn_offset,24,8,f3_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(213)+chn_offset, 8,8,f4_timing->PI_MR2_DATA_Fx);
	#endif

	//mr3
	//cs0
	reg_bit_set(CANDS_PI0_(168)+chn_offset,24,8,f0_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(170)+chn_offset, 8,8,f1_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(171)+chn_offset,24,8,f2_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(173)+chn_offset, 8,8,f3_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(174)+chn_offset,24,8,f4_timing->PI_MR3_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(176)+chn_offset,16,8,f0_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(178)+chn_offset, 0,8,f1_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(179)+chn_offset,16,8,f2_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(181)+chn_offset, 0,8,f3_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(182)+chn_offset,16,8,f4_timing->PI_MR3_DATA_Fx);
	#ifdef DRAM_LPDDR4
	//cs4
	reg_bit_set(CANDS_PI0_(199)+chn_offset,24,8,f0_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(201)+chn_offset, 8,8,f1_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(202)+chn_offset,24,8,f2_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(204)+chn_offset, 8,8,f3_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(205)+chn_offset,24,8,f4_timing->PI_MR3_DATA_Fx);
	//cs5
	reg_bit_set(CANDS_PI0_(207)+chn_offset,16,8,f0_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(209)+chn_offset, 0,8,f1_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(210)+chn_offset,16,8,f2_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(212)+chn_offset, 0,8,f3_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(213)+chn_offset,16,8,f4_timing->PI_MR3_DATA_Fx);
	#endif
	

	#ifdef DRAM_LPDDR4
	//mr11
	//cs0
	reg_bit_set(CANDS_PI0_(169)+chn_offset, 0,8,f0_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(170)+chn_offset,16,8,f1_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(172)+chn_offset, 0,8,f2_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(173)+chn_offset,16,8,f3_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(175)+chn_offset, 0,8,f4_timing->PI_MR11_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(176)+chn_offset,24,8,f0_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(178)+chn_offset, 8,8,f1_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(179)+chn_offset,24,8,f2_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(181)+chn_offset, 8,8,f3_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(182)+chn_offset,24,8,f4_timing->PI_MR11_DATA_Fx);
	//cs4
	reg_bit_set(CANDS_PI0_(200)+chn_offset, 0,8,f0_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(201)+chn_offset,16,8,f1_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(203)+chn_offset, 0,8,f2_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(204)+chn_offset,16,8,f3_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(206)+chn_offset, 0,8,f4_timing->PI_MR11_DATA_Fx);
	//cs5
	reg_bit_set(CANDS_PI0_(207)+chn_offset,24,8,f0_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(209)+chn_offset, 8,8,f1_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(210)+chn_offset,24,8,f2_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(212)+chn_offset, 8,8,f3_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(213)+chn_offset,24,8,f4_timing->PI_MR11_DATA_Fx);

	//mr12
	//cs0
	reg_bit_set(CANDS_PI0_(169)+chn_offset, 8,8,f0_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(170)+chn_offset,24,8,f1_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(172)+chn_offset, 8,8,f2_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(173)+chn_offset,24,8,f3_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(175)+chn_offset, 8,8,f4_timing->PI_MR12_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(177)+chn_offset, 0,8,f0_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(178)+chn_offset,16,8,f1_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(180)+chn_offset, 0,8,f2_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(181)+chn_offset,16,8,f3_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(183)+chn_offset, 0,8,f4_timing->PI_MR12_DATA_Fx);
	//cs4
	reg_bit_set(CANDS_PI0_(200)+chn_offset, 8,8,f0_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(201)+chn_offset,24,8,f1_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(203)+chn_offset, 8,8,f2_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(204)+chn_offset,24,8,f3_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(206)+chn_offset, 8,8,f4_timing->PI_MR12_DATA_Fx);
	//cs5
	reg_bit_set(CANDS_PI0_(208)+chn_offset, 0,8,f0_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(209)+chn_offset,16,8,f1_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(211)+chn_offset, 0,8,f2_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(212)+chn_offset,16,8,f3_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(214)+chn_offset, 0,8,f4_timing->PI_MR12_DATA_Fx);
	
	//mr14
	//cs0
	reg_bit_set(CANDS_PI0_(169)+chn_offset,16,8,f0_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(171)+chn_offset, 0,8,f1_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(172)+chn_offset,16,8,f2_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(174)+chn_offset, 0,8,f3_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(175)+chn_offset,16,8,f4_timing->PI_MR14_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(177)+chn_offset, 8,8,f0_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(178)+chn_offset,24,8,f1_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(180)+chn_offset, 8,8,f2_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(181)+chn_offset,24,8,f3_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(183)+chn_offset, 8,8,f4_timing->PI_MR14_DATA_Fx);
	//cs4
	reg_bit_set(CANDS_PI0_(200)+chn_offset,16,8,f0_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(202)+chn_offset, 0,8,f1_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(203)+chn_offset,16,8,f2_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(205)+chn_offset, 0,8,f3_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(206)+chn_offset,16,8,f4_timing->PI_MR14_DATA_Fx);
	//cs5
	reg_bit_set(CANDS_PI0_(208)+chn_offset, 8,8,f0_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(209)+chn_offset,24,8,f1_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(211)+chn_offset, 8,8,f2_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(212)+chn_offset,24,8,f3_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(214)+chn_offset, 8,8,f4_timing->PI_MR14_DATA_Fx);

	//mr13
	reg_bit_set(CANDS_PI0_(175)+chn_offset,24,8,f0_timing->PI_MR13_DATA_CSm);//cs0
	reg_bit_set(CANDS_PI0_(183)+chn_offset,16,8,f0_timing->PI_MR13_DATA_CSm);//cs1
	reg_bit_set(CANDS_PI0_(191)+chn_offset, 8,8,f0_timing->PI_MR13_DATA_CSm);//cs2
	reg_bit_set(CANDS_PI0_(199)+chn_offset, 0,8,f0_timing->PI_MR13_DATA_CSm);//cs3
	reg_bit_set(CANDS_PI0_(206)+chn_offset,24,8,f0_timing->PI_MR13_DATA_CSm);//cs4
	reg_bit_set(CANDS_PI0_(214)+chn_offset,16,8,f0_timing->PI_MR13_DATA_CSm);//cs5
	reg_bit_set(CANDS_PI0_(222)+chn_offset, 8,8,f0_timing->PI_MR13_DATA_CSm);//cs6
	reg_bit_set(CANDS_PI0_(230)+chn_offset, 0,8,f0_timing->PI_MR13_DATA_CSm);//cs7
	#endif
}

void cands_pi_catr_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,uint32 cs_map)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//calvl_cs
	reg_bit_set(CANDS_PI0_(125)+chn_offset, 24,3, 0);

	//calvl_seq_en
	reg_bit_set(CANDS_PI0_(126)+chn_offset, 16,2,0x3);

	//calvl_periodic
	reg_bit_set(CANDS_PI0_(126)+chn_offset, 24,1,PI_CALVL_PERDIC_EN);

	//calvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(127)+chn_offset, 0,1,PI_CALVL_SRE_EN);

	//calvl_rotate
	reg_bit_set(CANDS_PI0_(127)+chn_offset, 8,1,0); //??????

	//calvl_cs_map
	reg_bit_set(CANDS_PI0_(127)+chn_offset,16,8,cs_map);

	//calvl_resp_mask
	reg_bit_set(CANDS_PI0_(135)+chn_offset, 0,1,0);

	//calvl_en
	reg_bit_set(CANDS_PI0_(135)+chn_offset, 8,2,(PI_CALVL_EN_NOINIT<<1)|PI_CALVL_EN_INIT);

	//calvl_interval
	reg_bit_set(CANDS_PI0_(136)+chn_offset, 0,16,0); //?????

	//ca_train_vref_en
	reg_bit_set(CANDS_PI0_(141)+chn_offset, 24,1,PI_CALVL_VREF_EN); //?????

	//calvl_vref_initial_start_point
	reg_bit_set(CANDS_PI0_(149)+chn_offset, 16,7,0x68); //?????

	//calvl_vref_initial_stop_point
	reg_bit_set(CANDS_PI0_(149)+chn_offset, 24,7,0x72); //?????

	//calvl_vref_initial_stepsize
	reg_bit_set(CANDS_PI0_(150)+chn_offset, 0,4,0x4); //?????

	//calvl_vref_normal_stepsize
	reg_bit_set(CANDS_PI0_(150)+chn_offset, 8,4,0x2); //?????

	//calvl_vref_delta
	reg_bit_set(CANDS_PI0_(150)+chn_offset, 16,4,0x1); //?????

	//calvl_strobe_num
	reg_bit_set(CANDS_PI0_(152)+chn_offset, 24,5,0x2); //?????

	//sw_ca_train_vref
	reg_bit_set(CANDS_PI0_(153)+chn_offset,  0,7,0x0);
}

void cands_pi_rdlvl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,uint32 cs_map)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//rdlvl_cs_map
	reg_bit_set(CANDS_PI0_(114)+chn_offset, 0,8, cs_map);

	//rdlvl_gate_cs_map
	reg_bit_set(CANDS_PI0_(114)+chn_offset, 8,8, cs_map);

	//rdlvl_en
	reg_bit_set(CANDS_PI0_(116)+chn_offset, 16,2,(PI_RDLVL_EN_NOINIT<<1)|PI_RDLVL_EN_INIT);

	//rdlvl_seq_en
	reg_bit_set(CANDS_PI0_(111)+chn_offset,24,4, 0);

	//rdlvl_gate_en
	reg_bit_set(CANDS_PI0_(116)+chn_offset, 24,2,(PI_RDLVL_GATE_EN_NOINIT<<1)|PI_RDLVL_GATE_EN_INIT);

	//rdlvl_gate_seq_en
	reg_bit_set(CANDS_PI0_(112)+chn_offset, 0,4, 0);

	//rd_preamble_training_en
	reg_bit_set(CANDS_PI0_(120)+chn_offset, 16,1, PI_RD_PREAMBLE_TR_EN);

	//rdlvl_periodic
	reg_bit_set(CANDS_PI0_(112)+chn_offset,  8,1, PI_RDLVL_PERDIC_EN); //??????

	//rdlvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(112)+chn_offset, 16,1, PI_RDLVL_SRE_EN); //??????

	//rdlvl_gate_periodic
	reg_bit_set(CANDS_PI0_(112)+chn_offset, 24,1, PI_RDLVL_GATE_PERDIC_EN); //??????

	//rdlvl_gate_on_sref_exit
	reg_bit_set(CANDS_PI0_(113)+chn_offset,  0,1, PI_RDLVL_GATE_SRE_EN); //??????

	//rdlvl_rotate
	reg_bit_set(CANDS_PI0_(113)+chn_offset, 16,1, 0); //??????

	//rdlvl_gate_rotate
	reg_bit_set(CANDS_PI0_(113)+chn_offset, 24,1, 0); //??????

	//rdlvl_interval
	reg_bit_set(CANDS_PI0_(118)+chn_offset, 8,16, 0); //??????

	//rdlvl_gate_interval
	reg_bit_set(CANDS_PI0_(119)+chn_offset, 0,16, 0); //??????

	//rdlvl_pattern_start
	reg_bit_set(CANDS_PI0_(119)+chn_offset,16,4, 0); //??????

	//rdlvl_pattern_num
	reg_bit_set(CANDS_PI0_(119)+chn_offset,24,4, 1); //??????

	//rdlvl_strobe_num
	reg_bit_set(CANDS_PI0_(120)+chn_offset,0,5, 1); //??????

	//rdlvl_gate_strobe_num
	reg_bit_set(CANDS_PI0_(120)+chn_offset,8,5, 1); //??????

	//rdlvl_gate_strobe_num
	reg_bit_set(CANDS_PI0_(120)+chn_offset,8,5, 1); //??????

}

void cands_pi_wrlvl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type, uint32 cs_map)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//wldqsen
	reg_bit_set(CANDS_PI0_(91)+chn_offset,24,6, 0xd); //??????

	//wlmrd
	reg_bit_set(CANDS_PI0_(92)+chn_offset, 0,6, 0x28); //??????

	//wrlvl_en
	reg_bit_set(CANDS_PI0_(92)+chn_offset, 8,2, (PI_WRLVL_EN_NOINIT<<1)|PI_WRLVL_EN_INIT); //??????

	//wrlvl_interval
	reg_bit_set(CANDS_PI0_(92)+chn_offset, 16,16,0);

	//wrlvl_periodic
	reg_bit_set(CANDS_PI0_(93)+chn_offset, 0,1, PI_WRLVL_PERDIC_EN);

	//wrlvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(93)+chn_offset, 8,1, PI_WRLVL_SRE_EN);

	//wrlvl_resp_mask
	reg_bit_set(CANDS_PI0_(93)+chn_offset,16,4,0);

	//wrlvl_rotate
	reg_bit_set(CANDS_PI0_(93)+chn_offset,24,1,0); //????????

	//wrlvl_cs_map
	reg_bit_set(CANDS_PI0_(94)+chn_offset, 0,8, cs_map);

	//wrlvl_strobe_num
	reg_bit_set(CANDS_PI0_(98)+chn_offset, 0,5,2);

}

void cands_pi_wdqlvl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type, uint32 cs_map)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//wdqlvl_en
	reg_bit_set(CANDS_PI0_(167)+chn_offset,16,2,(PI_WDQLVL_EN_NOINIT<<1)|PI_WDQLVL_EN_INIT);

	//wdq_vref_en
	reg_bit_set(CANDS_PI0_(159)+chn_offset,24,1,PI_WDQLVL_VREF_EN);

	//wdqlvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(167)+chn_offset,24,1,PI_WDQLVL_SRE_EN);

	//wdqlvl_periodic
	reg_bit_set(CANDS_PI0_(163)+chn_offset,16,1,PI_WDQLVL_PERDIC_EN);

	//wdqlvl_cs_map
	reg_bit_set(CANDS_PI0_(162)+chn_offset,0,8, cs_map);

	//wdqlvl_bst_num
	reg_bit_set(CANDS_PI0_(160)+chn_offset,0,3,1); //??????

	//wdqlvl_resp_mask
	reg_bit_set(CANDS_PI0_(161)+chn_offset,16,4,0);

	//wdqlvl_rotate
	reg_bit_set(CANDS_PI0_(161)+chn_offset,24,1,0); //??????

	//wdqlvl_vref_initial_start_point
	reg_bit_set(CANDS_PI0_(162)+chn_offset, 8,7,0x1a); //?????

	//wdqlvl_vref_initial_stop_point
	reg_bit_set(CANDS_PI0_(162)+chn_offset,16,7,0x23); //?????

	//wdqlvl_vref_initial_stepsize
	reg_bit_set(CANDS_PI0_(162)+chn_offset,24,5,0x1); //?????

	//wdqlvl_vref_normal_stepsize
	reg_bit_set(CANDS_PI0_(163)+chn_offset, 0,5,0x1); //?????

	//wdqlvl_vref_delta
	reg_bit_set(CANDS_PI0_(163)+chn_offset, 8,4,0x1); //?????

	//wdqlvl_interval
	reg_bit_set(CANDS_PI0_(167)+chn_offset, 0,16,0); //?????

}

void cands_pi_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_PI_TIMING_T	*pi_timing,
				   uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 pi_fn[5] = {0};
	uint32 ctl_fn[5] = {f0,f1,f2,f3,f4};
	uint32 i = 0;
	uint32 j = 0;
	uint32 cs_map = 0;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	#ifdef DRAM_LPDDR3
	uint32 ctlfn_to_pifn[5] = {0,1,2,3,4};
	#else
	uint32 ctlfn_to_pifn[5] = {1,2,3,4,0};
	#endif

	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			if(ctlfn_to_pifn[i] == j)
				pi_fn[j] = ctl_fn[i];
		}

	}

	for(i = 0; i < 5; i++)
	{
		switch(pi_fn[i])
		{
			case 1200: pi_fn_div[i] = CLKDIV_1200MHZ; break;
			case 933:  pi_fn_div[i] = CLKDIV_933MHZ;  break;
			case 768:  pi_fn_div[i] = CLKDIV_768MHZ;  break;
			case 600:  pi_fn_div[i] = CLKDIV_600MHZ;  break;
			case 466:  pi_fn_div[i] = CLKDIV_466MHZ;  break;
			case 400:  pi_fn_div[i] = CLKDIV_400MHZ;  break;
			case 311:  pi_fn_div[i] = CLKDIV_311MHZ;  break;
			case 240:  pi_fn_div[i] = CLKDIV_240MHZ;  break;
			case 200:  pi_fn_div[i] = CLKDIV_200MHZ;  break;
			case 156:  pi_fn_div[i] = CLKDIV_156MHZ;  break;
			case 26:   pi_fn_div[i] = CLKDIV_26MHZ;   break;
			default: while(1);
		}
	}
	//cs_map = islp3?(IS_2CS(ddr_type)?3:1):(IS_2CS(ddr_type)?0x33:(IS_16BIT(ddr_type)?0x1:0x11));
	cs_map = islp3?(IS_2CS(ddr_type)?3:1):((IS_2CS(ddr_type)?0x33:0x11)&(IS_16BIT(ddr_type)?0xf:0xff));

	cands_pi_basicmode_init(chn_num,ddr_type,cs_map);
	cands_pi_actiming_init( chn_num, pi_timing, pi_fn[0], pi_fn[1], pi_fn[2], pi_fn[3], pi_fn[4]);
	cands_pi_dfitiming_init(chn_num, pi_timing, pi_fn[0], pi_fn[1], pi_fn[2], pi_fn[3], pi_fn[4]);
	cands_pi_odtiming_init( chn_num, pi_timing, pi_fn[0], pi_fn[1], pi_fn[2], pi_fn[3], pi_fn[4]);
	cands_pi_modreg_init(   chn_num, pi_timing, pi_fn[0], pi_fn[1], pi_fn[2], pi_fn[3], pi_fn[4]);
	cands_pi_catr_init(chn_num,ddr_type,cs_map);
	cands_pi_rdlvl_init(chn_num,ddr_type,cs_map);
	cands_pi_wrlvl_init(chn_num,ddr_type,cs_map);
	cands_pi_wdqlvl_init(chn_num,ddr_type,cs_map);

}

void phy_reg_multicast_open(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,0,1,1);
}
void phy_reg_multicast_shut(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,0,1,0);
}

void phy_reg_switch_dfs(DDR_CHANNEL_NUM_E chn_num,uint32 dfs_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//set index
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,8,3,dfs_num);
}


void cands_phy_timing_map(uint32 set_sum,CANDS_PHY_TIMING_T *phy_timing,
                          uint32 f0, uint32 f1, uint32 f2, uint32 f3,
                          CANDS_PI_TIMING_T *f0_timing,CANDS_PI_TIMING_T *f1_timing,
                          CANDS_PI_TIMING_T *f2_timing,CANDS_PI_TIMING_T *f3_timing)
{
	uint32 i = 0;

	for(i = 0; i < set_sum; i++)
	{
		if(phy_timing[i].ddr_clk == f0)
		{
				temp_fn[0] = (uint32)(&phy_timing[i]);
		}

		if(phy_timing[i].ddr_clk == f1)
		{
				temp_fn[1] = (uint32)(&phy_timing[i]);
		}

		if(phy_timing[i].ddr_clk == f2)
		{
				temp_fn[2] = (uint32)(&phy_timing[i]);
		}

		if(phy_timing[i].ddr_clk == f3)
		{
				temp_fn[3] = (uint32)(&phy_timing[i]);
		}
	}

}

void cands_phy_pinmux_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//if(islp3) //lpddr3, single channel, sbs
	#ifdef DRAM_LPDDR3 //lpddr3, single channel, sbs

	//phy_adr_addr_sel_0
	__raw_writel(CANDS_PHY0_(540)+chn_offset,0x8);
	//phy_adr_addr_sel_1
	__raw_writel(CANDS_PHY0_(668)+chn_offset,0x5967);
	//phy_adr_addr_sel_2
	__raw_writel(CANDS_PHY0_(796)+chn_offset,0x34);
	//phy_adr_addr_sel_3
	__raw_writel(CANDS_PHY0_(924)+chn_offset,0x0102);

	//phy_adr_bit_mask_0
	reg_bit_set(CANDS_PHY0_(541)+chn_offset,16,6,0x1);
	//phy_adr_seg_mask_0
	reg_bit_set(CANDS_PHY0_(541)+chn_offset,24,6,0x0);

	//phy_adr_bit_mask_1
	reg_bit_set(CANDS_PHY0_(669)+chn_offset,16,6,0xf);
	//phy_adr_seg_mask_1
	reg_bit_set(CANDS_PHY0_(669)+chn_offset,24,6,0x4);

	//phy_adr_bit_mask_2
	reg_bit_set(CANDS_PHY0_(797)+chn_offset,16,6,0x3);
	//phy_adr_seg_mask_2
	reg_bit_set(CANDS_PHY0_(797)+chn_offset,24,6,0x1);

	//phy_adr_bit_mask_3
	reg_bit_set(CANDS_PHY0_(925)+chn_offset,16,6,0xd);
	//phy_adr_seg_mask_3
	reg_bit_set(CANDS_PHY0_(925+chn_offset),24,6,0x0);

	//phy_adr_calvl_swizzle0_0_0
	__raw_writel(CANDS_PHY0_(524)+chn_offset,0xe);
	//phy_adr_calvl_swizzle1_0_0
	__raw_writel(CANDS_PHY0_(525)+chn_offset,0xf);
	//phy_adr_calvl_swizzle0_1_0
	__raw_writel(CANDS_PHY0_(526)+chn_offset,0xe);
	//phy_adr_calvl_swizzle1_1_0
	reg_bit_set(CANDS_PHY0_(527)+chn_offset,0,16,0xf);

	//phy_adr_calvl_swizzle0_0_1
	__raw_writel(CANDS_PHY0_(652)+chn_offset,0x88ac);
	//phy_adr_calvl_swizzle1_0_1
	__raw_writel(CANDS_PHY0_(653)+chn_offset,0x99bd);
	//phy_adr_calvl_swizzle0_1_1
	__raw_writel(CANDS_PHY0_(654)+chn_offset,0x88ac);
	//phy_adr_calvl_swizzle1_1_1
	reg_bit_set(CANDS_PHY0_(655)+chn_offset,0,16,0x99bd);

	//phy_adr_calvl_swizzle0_0_2
	__raw_writel(CANDS_PHY0_(780)+chn_offset,0x60);
	//phy_adr_calvl_swizzle1_0_2
	__raw_writel(CANDS_PHY0_(781)+chn_offset,0x71);
	//phy_adr_calvl_swizzle0_1_2
	__raw_writel(CANDS_PHY0_(782)+chn_offset,0x60);
	//phy_adr_calvl_swizzle1_1_2
	reg_bit_set(CANDS_PHY0_(783)+chn_offset,0,16,0x71);

	//phy_adr_calvl_swizzle0_0_3
	__raw_writel(CANDS_PHY0_(908)+chn_offset,0x0204);
	//phy_adr_calvl_swizzle1_0_3
	__raw_writel(CANDS_PHY0_(909)+chn_offset,0x1305);
	//phy_adr_calvl_swizzle0_1_3
	__raw_writel(CANDS_PHY0_(910)+chn_offset,0x0204);
	//phy_adr_calvl_swizzle1_1_3
	reg_bit_set(CANDS_PHY0_(911)+chn_offset,0,16,0x1305);

	//pi_byte_swap_en
	__raw_writel(CANDS_PI0_(277)+chn_offset,0x10301);
	reg_bit_set(CANDS_PI0_(278)+chn_offset,0,8,0x2);

	//pi_data_byte_order_sel
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,16,8,0x36);

	/*-------data slice 0-----*/
	//phy_dm_dq_swizzle0_0
	__raw_writel(CANDS_PHY0_(0)+chn_offset,0x43176205);
   	//phy_dm_dq_swizzle1_0
	reg_bit_set(CANDS_PHY0_(1)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_0
	__raw_writel(CANDS_PHY0_(24)+chn_offset,0x43176205);

	/*-------data slice 1-----*/
	//phy_dm_dq_swizzle0_1
	__raw_writel(CANDS_PHY0_(128)+chn_offset,0x42851630);
   	//phy_dm_dq_swizzle1_1
	reg_bit_set(CANDS_PHY0_(129)+chn_offset,0,4,7);
    //phy_rdlvl_data_swizzle_1
	__raw_writel(CANDS_PHY0_(152)+chn_offset,0x42851630);

	/*-------data slice 2-----*/
	//phy_dm_dq_swizzle0_2
	__raw_writel(CANDS_PHY0_(256)+chn_offset,0x31582647);
   	//phy_dm_dq_swizzle1_2
	reg_bit_set(CANDS_PHY0_(257)+chn_offset,0,4,0);
    //phy_rdlvl_data_swizzle_2
	__raw_writel(CANDS_PHY0_(280)+chn_offset,0x31582647);

	/*-------data slice 3-----*/
	//phy_dm_dq_swizzle0_3
	__raw_writel(CANDS_PHY0_(384)+chn_offset,0x34602157);
   	//phy_dm_dq_swizzle1_3
	reg_bit_set(CANDS_PHY0_(385)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_3
	__raw_writel(CANDS_PHY0_(408)+chn_offset,0x34602157);

	//pi_cke_mux
	__raw_writel(CANDS_PI0_(269)+chn_offset,0x1918);
	__raw_writel(CANDS_PI0_(270)+chn_offset,0x0000);

	//pi_cs_mux
	__raw_writel(CANDS_PI0_(271)+chn_offset,0x0000);
	__raw_writel(CANDS_PI0_(272)+chn_offset,0x1110);

	//pi_odt_mux
	__raw_writel(CANDS_PI0_(273)+chn_offset,0x0000);
	__raw_writel(CANDS_PI0_(274)+chn_offset,0x0000);

	//pi_reset_mux
	__raw_writel(CANDS_PI0_(275)+chn_offset,0x0000);
	__raw_writel(CANDS_PI0_(276)+chn_offset,0x0000);

	#else ////lpddr4, two channel, pop

	//phy_adr_addr_sel_0
	__raw_writel(CANDS_PHY0_(540)+chn_offset,0x12);
	//phy_adr_addr_sel_1
	__raw_writel(CANDS_PHY0_(668)+chn_offset,0x5034);
	//phy_adr_addr_sel_2
	__raw_writel(CANDS_PHY0_(796)+chn_offset,0x10);
	//phy_adr_addr_sel_3
	__raw_writel(CANDS_PHY0_(924)+chn_offset,0x4352);

	//phy_adr_bit_mask_0
	reg_bit_set(CANDS_PHY0_(541)+chn_offset,16,6,0x3);
	//phy_adr_seg_mask_0
	reg_bit_set(CANDS_PHY0_(541)+chn_offset,24,6,0x0);

	//phy_adr_bit_mask_1
	reg_bit_set(CANDS_PHY0_(669)+chn_offset,16,6,0xf);
	//phy_adr_seg_mask_1
	reg_bit_set(CANDS_PHY0_(669)+chn_offset,24,6,0x0);

	//phy_adr_bit_mask_2
	reg_bit_set(CANDS_PHY0_(797)+chn_offset,16,6,0x3);
	//phy_adr_seg_mask_2
	reg_bit_set(CANDS_PHY0_(797)+chn_offset,24,6,0x0);

	//phy_adr_bit_mask_3
	reg_bit_set(CANDS_PHY0_(925)+chn_offset,16,6,0xf);
	//phy_adr_seg_mask_3
	reg_bit_set(CANDS_PHY0_(925)+chn_offset,24,6,0x0);

	//phy_adr_calvl_swizzle0_0_0
	__raw_writel(CANDS_PHY0_(524)+chn_offset,0x9a);
	//phy_adr_calvl_swizzle1_0_0
	__raw_writel(CANDS_PHY0_(525)+chn_offset,0x9a);
	//phy_adr_calvl_swizzle0_1_0
	__raw_writel(CANDS_PHY0_(526)+chn_offset,0x9a);
	//phy_adr_calvl_swizzle1_1_0
	reg_bit_set(CANDS_PHY0_(527)+chn_offset,0,16,0x9a);

	//phy_adr_calvl_swizzle0_0_1
	__raw_writel(CANDS_PHY0_(652)+chn_offset,0xd8bc);
	//phy_adr_calvl_swizzle1_0_1
	__raw_writel(CANDS_PHY0_(653)+chn_offset,0xd8bc);
	//phy_adr_calvl_swizzle0_1_1
	__raw_writel(CANDS_PHY0_(654)+chn_offset,0xd8bc);
	//phy_adr_calvl_swizzle1_1_1
	reg_bit_set(CANDS_PHY0_(655)+chn_offset,0,16,0xd8bc);

	//phy_adr_calvl_swizzle0_0_2
	__raw_writel(CANDS_PHY0_(780)+chn_offset,0x98);
	//phy_adr_calvl_swizzle1_0_2
	__raw_writel(CANDS_PHY0_(781)+chn_offset,0x98);
	//phy_adr_calvl_swizzle0_1_2
	__raw_writel(CANDS_PHY0_(782)+chn_offset,0x98);
	//phy_adr_calvl_swizzle1_1_2
	reg_bit_set(CANDS_PHY0_(783)+chn_offset,0,16,0x98);

	//phy_adr_calvl_swizzle0_0_3
	__raw_writel(CANDS_PHY0_(908)+chn_offset,0xcbda);
	//phy_adr_calvl_swizzle1_0_3
	__raw_writel(CANDS_PHY0_(909)+chn_offset,0xcbda);
	//phy_adr_calvl_swizzle0_1_3
	__raw_writel(CANDS_PHY0_(910)+chn_offset,0xcbda);
	//phy_adr_calvl_swizzle1_1_3
	reg_bit_set(CANDS_PHY0_(911)+chn_offset,0,16,0xcbda);


	//pi_byte_swap_en
	__raw_writel(CANDS_PI0_(277)+chn_offset,0x2010001);
	reg_bit_set(CANDS_PI0_(278)+chn_offset,0,8,0x3);

	//pi_data_byte_order_sel
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,16,8,0xe4);

	/*-------data slice 0-----*/
	//phy_dm_dq_swizzle0_0
	__raw_writel(CANDS_PHY0_(0)+chn_offset,0x65743081);
   	//phy_dm_dq_swizzle1_0
	reg_bit_set(CANDS_PHY0_(1)+chn_offset,0,4,2);
    //phy_rdlvl_data_swizzle_0
	__raw_writel(CANDS_PHY0_(24)+chn_offset,0x65743081);

	/*-------data slice 1-----*/
	//phy_dm_dq_swizzle0_1
	__raw_writel(CANDS_PHY0_(128)+chn_offset,0x64752013);
   	//phy_dm_dq_swizzle1_1
	reg_bit_set(CANDS_PHY0_(129)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_1
	__raw_writel(CANDS_PHY0_(152)+chn_offset,0x64752013);

	/*-------data slice 2-----*/
	//phy_dm_dq_swizzle0_2
	__raw_writel(CANDS_PHY0_(256)+chn_offset,0x76543201);
   	//phy_dm_dq_swizzle1_2
	reg_bit_set(CANDS_PHY0_(257)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_2
	__raw_writel(CANDS_PHY0_(280)+chn_offset,0x76543201);

	/*-------data slice 3-----*/
	//phy_dm_dq_swizzle0_3
	__raw_writel(CANDS_PHY0_(384)+chn_offset,0x75346120);
   	//phy_dm_dq_swizzle1_3
	reg_bit_set(CANDS_PHY0_(385)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_3
	__raw_writel(CANDS_PHY0_(408)+chn_offset,0x75346120);

	//pi_cke_mux
	__raw_writel(CANDS_PI0_(269)+chn_offset,0x1011);
	__raw_writel(CANDS_PI0_(270)+chn_offset,0x1d1c);

	//pi_reset_mux
	__raw_writel(CANDS_PI0_(271)+chn_offset,0x1918);
	__raw_writel(CANDS_PI0_(272)+chn_offset,0x1514);

	//pi_odt_mux
	__raw_writel(CANDS_PI0_(273)+chn_offset,0x0808);
	__raw_writel(CANDS_PI0_(274)+chn_offset,0x0808);

	//pi_cs_mux
	__raw_writel(CANDS_PI0_(275)+chn_offset,0x0000);
	__raw_writel(CANDS_PI0_(276)+chn_offset,0x0000);

	#endif


}

void cands_data_gen_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);
	uint32 cs_map = 0;
	cs_map = islp3?(IS_2CS(ddr_type)):((IS_2CS(ddr_type)?0x33:0x11)&(IS_16BIT(ddr_type)?0xf:0xff));

	//phy_two_cyc_preamble, bit0:2 cycle read preamble bit1: 2 cycle write preamble
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(6)+chn_offset+slice_offset,24,2,islp3?0:2); //?????
	}
	#else
	reg_bit_set(CANDS_PHY0_(6)+chn_offset+slice_offset,24,2,islp3?0:2); //?????
	#endif

	//phy_per_rank_cs_map
	#ifdef DRAM_LPDDR3
	//reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,8,3,IS_2CS(ddr_type)); //?????
	#else
	//reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,8,3,IS_2CS(ddr_type)?3:1); //?????
	#endif
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,8,3,cs_map); //?????
	//phy_dbi_mode
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,0,1,RD_DBI_EN); //?????no write dbi???

	//phy_lpddr_type
	reg_bit_set(CANDS_PHY0_(11)+chn_offset+slice_offset,8,2,islp3?1:2);

	//phy_lpddr
	reg_bit_set(CANDS_PHY0_(11)+chn_offset+slice_offset,0,1,1);

	//on_fly_gate_adjust_en
	reg_bit_set(CANDS_PHY0_(12)+chn_offset+slice_offset,16,2,0); //??????

	//phy_per_cs_training_index
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,24,2,0); //????

	//phy_per_cs_training_multicast_en
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,16,1,1); //????

	//phy_per_cs_training_en
	#ifdef DRAM_LPDDR4
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset,16,1,1); //????
	}
	#else
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset,16,1,1); //????
	#endif
	#endif
	//phy_lvl_debug_mode
	reg_bit_set(CANDS_PHY0_(21)+chn_offset+slice_offset,0,1,0);

	//phy_calvl_vref_driving_slice, if drvie vref value to slice during catraining
	reg_bit_set(CANDS_PHY0_(32)+chn_offset+slice_offset,16,1,islp3?0:((slice_num%2)?0:1)); //??????

	//phy_dll_mode
	__raw_writel(CANDS_PHY0_(48)+chn_offset+slice_offset,0); //????

	//phy_ie_mode
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,16,2,PHY_IE_ALWAYS_ON);
	}
	#else
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,16,2,PHY_IE_ALWAYS_ON);
	#endif

	//phy_rptr_update
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,16,4,islp3?5:6);
	}
	#else
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,16,4,islp3?5:6);
	#endif
}

void cands_data_bypass_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);
#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_clk_bypass_override
	reg_bit_set(CANDS_PHY0_(1)+chn_offset+slice_offset,24,1,0);
	//phy_clk_wr_bypass_slave_delay
	reg_bit_set(CANDS_PHY0_(1)+chn_offset+slice_offset,8,11,islp3?0x4c0:0x4f0); //??????
	//phy_rddqs_dq_bypass_slave_dleay
	reg_bit_set(CANDS_PHY0_(10)+chn_offset+slice_offset,0,10,0xc0);

	//set f0~f3 dll bypass mode
	#ifdef CODE_SIZE_OPTIMIZE
	for(i=0;i < 4; i++) {
		phy_reg_switch_dfs(chn_num, i);
		reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,8,4,timing[i]->phy_sw_master_mode_X);
	}
	#else
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,8,4,f0_timing->phy_sw_master_mode_X);
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,8,4,f1_timing->phy_sw_master_mode_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,8,4,f2_timing->phy_sw_master_mode_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,8,4,f3_timing->phy_sw_master_mode_X);
	#endif
}

void cands_data_wrdqdqs_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 j = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);
#ifdef CODE_SIZE_OPTIMIZE
	//phy_clk_wrdm_slave_delay
  	#if DO_DFS_INIT
	for(i = 0; i < 4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 0,11,timing[i]->phy_clk_wrdm_slave_delay_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 0,11,f0_timing->phy_clk_wrdm_slave_delay_X);
	#endif
#else
	//phy_clk_wrdm_slave_delay
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 0,11,f0_timing->phy_clk_wrdm_slave_delay_X);
  	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 0,11,f1_timing->phy_clk_wrdm_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 0,11,f2_timing->phy_clk_wrdm_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 0,11,f3_timing->phy_clk_wrdm_slave_delay_X);
	#endif
#endif


#ifdef CODE_SIZE_OPTIMIZE
	//phy_clk_wrdq0~7_slave_delay
	for(i = 0; i< 8; i++)
	{
	#if DO_DFS_INIT
	for(j = 0; j<4; j++)
	{
	phy_reg_switch_dfs(chn_num, j);
	reg_bit_set(CANDS_PHY0_(58)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,11,timing[j]->phy_clk_wrdqZ_slave_delay_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(58)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,11,f0_timing->phy_clk_wrdqZ_slave_delay_X);
	#endif
	}
#else
	//phy_clk_wrdq0~7_slave_delay
	for(i = 0; i< 8; i++)
	{
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(58)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,11,f0_timing->phy_clk_wrdqZ_slave_delay_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(58)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,11,f1_timing->phy_clk_wrdqZ_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(58)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,11,f2_timing->phy_clk_wrdqZ_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(58)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,11,f3_timing->phy_clk_wrdqZ_slave_delay_X);
	#endif
	}
#endif

#ifdef CODE_SIZE_OPTIMIZE
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 16,10,timing[i]->phy_clk_wrdqs_slave_delay_X);
	}
	#else
	//phy_clk_wrdqs_slave_delay
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 16,10,f0_timing->phy_clk_wrdqs_slave_delay_X);
	#endif
#else
	//phy_clk_wrdqs_slave_delay
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 16,10,f0_timing->phy_clk_wrdqs_slave_delay_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 16,10,f1_timing->phy_clk_wrdqs_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 16,10,f2_timing->phy_clk_wrdqs_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(62)+chn_offset+slice_offset, 16,10,f3_timing->phy_clk_wrdqs_slave_delay_X);
	#endif
#endif
	//phy_sw_wrdq0/1/2/3_shirt
	__raw_writel(CANDS_PHY0_(2)+chn_offset+slice_offset, 0);

	//phy_sw_wrdq4/5/6/7_shirt
	__raw_writel(CANDS_PHY0_(3)+chn_offset+slice_offset, 0);

	//phy_sw_wrdqqs_shirt
	reg_bit_set(CANDS_PHY0_(4)+chn_offset+slice_offset,8,4,0);

	//phy_sw_wrdm_shirt
	reg_bit_set(CANDS_PHY0_(4)+chn_offset+slice_offset,0,4,0);


}

void cands_data_dqdqs_tsel_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_dq_tsel_enable, dq/dm tsel_en, bit0: read cycle  bit1: write cycle  bit2: idle cycle
	reg_bit_set(CANDS_PHY0_(4)+chn_offset+slice_offset,16,3,PHY_DQDQS_ODT_RD_EN|(PHY_DQDQS_ODT_WR_EN<<1)|(PHY_DQDQS_ODT_IDLE_EN<<2)); //??????

	//phy_dq_tsel_select
	reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_offset,0,24,(PHY_DQDQS_ODT_IDLE_DRV<<20) |(PHY_DQDQS_ODT_IDLE_DRV<<16)|
	                                                        (PHY_DQDQS_ODT_WR_DRV<<12)   |(PHY_DQDQS_ODT_WR_DRV<<8)    |
	                                                        (PHY_DQDQS_ODT_RD_DRV_P<<4)  |(PHY_DQDQS_ODT_RD_DRV_N) ); //??????


#ifdef CODE_SIZE_OPTIMIZE
	#if DO_DFS_INIT
	for(i = 0; i < 4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 8,8,timing[i]->phy_dq_tsel_rd_timing_X);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset,16,8,timing[i]->phy_dq_tsel_wr_timing_X);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 0,8,timing[i]->phy_dqs_tsel_rd_timing_X);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 8,8,timing[i]->phy_dqs_tsel_wr_timing_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 8,8,f0_timing->phy_dq_tsel_rd_timing_X);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset,16,8,f0_timing->phy_dq_tsel_wr_timing_X);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 0,8,f0_timing->phy_dqs_tsel_rd_timing_X);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 8,8,f0_timing->phy_dqs_tsel_wr_timing_X);
	#endif
#else
	//phy_dq_tsel_rd_timing
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 8,8,f0_timing->phy_dq_tsel_rd_timing_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 8,8,f1_timing->phy_dq_tsel_rd_timing_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 8,8,f2_timing->phy_dq_tsel_rd_timing_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 8,8,f3_timing->phy_dq_tsel_rd_timing_X);
	#endif

	//phy_dq_tsel_wr_timing
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 16,8,f0_timing->phy_dq_tsel_wr_timing_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 16,8,f1_timing->phy_dq_tsel_wr_timing_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 16,8,f2_timing->phy_dq_tsel_wr_timing_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 16,8,f3_timing->phy_dq_tsel_wr_timing_X);
	#endif

	//phy_dqs_tsel_rd_timing
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 0,8,f0_timing->phy_dqs_tsel_rd_timing_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 0,8,f1_timing->phy_dqs_tsel_rd_timing_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 0,8,f2_timing->phy_dqs_tsel_rd_timing_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 0,8,f3_timing->phy_dqs_tsel_rd_timing_X);
	#endif
	//phy_dqs_tsel_wr_timing
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 8,8,f0_timing->phy_dqs_tsel_wr_timing_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 8,8,f1_timing->phy_dqs_tsel_wr_timing_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 8,8,f2_timing->phy_dqs_tsel_wr_timing_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset, 8,8,f3_timing->phy_dqs_tsel_wr_timing_X);
	#endif
#endif
	//phy_dqs_tsel_enable, dqs tsel_en, bit0: read cycle  bit1: write cycle  bit2: idle cycle
	reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_offset,24,3,PHY_DQDQS_ODT_RD_EN|(PHY_DQDQS_ODT_WR_EN<<1)|(PHY_DQDQS_ODT_IDLE_EN<<2)); //??????


	//phy_dqs_tsel_select
	reg_bit_set(CANDS_PHY0_(6)+chn_offset+slice_offset,0,24,(PHY_DQDQS_ODT_IDLE_DRV<<20)|(PHY_DQDQS_ODT_IDLE_DRV<<16)|
	                                                        (PHY_DQDQS_ODT_WR_DRV<<12)  |(PHY_DQDQS_ODT_WR_DRV<<8)   |
	                                                        (PHY_DQDQS_ODT_RD_DRV_P<<4) |(PHY_DQDQS_ODT_RD_DRV_N)); //??????


}

void cands_data_dqdqs_ieoe_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

#ifdef CODE_SIZE_OPTIMIZE
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset,24,8,timing[i]->phy_dq_ie_timing_X);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 0,8,timing[i]->phy_dq_oe_timing_X);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset, 0,8,timing[i]->phy_dqs_ie_timing_X);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset,24,8,timing[i]->phy_dqs_oe_timing_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset,24,8,f0_timing->phy_dq_ie_timing_X);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 0,8,f0_timing->phy_dq_oe_timing_X);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset, 0,8,f0_timing->phy_dqs_ie_timing_X);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset,24,8,f0_timing->phy_dqs_oe_timing_X);
	#endif
#else
	//phy_dq_ie_timing
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset,24,8,f0_timing->phy_dq_ie_timing_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset,24,8,f1_timing->phy_dq_ie_timing_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset,24,8,f2_timing->phy_dq_ie_timing_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(82)+chn_offset+slice_offset,24,8,f3_timing->phy_dq_ie_timing_X);
	#endif
	//phy_dq_oe_timing
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 0,8,f0_timing->phy_dq_oe_timing_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 0,8,f1_timing->phy_dq_oe_timing_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 0,8,f2_timing->phy_dq_oe_timing_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset, 0,8,f3_timing->phy_dq_oe_timing_X);
	#endif
	//phy_dqs_ie_timing
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset, 0,8,f0_timing->phy_dqs_ie_timing_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset, 0,8,f1_timing->phy_dqs_ie_timing_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset, 0,8,f2_timing->phy_dqs_ie_timing_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset, 0,8,f3_timing->phy_dqs_ie_timing_X);
	#endif
	//phy_dqs_oe_timing
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset,24,8,f0_timing->phy_dqs_oe_timing_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset,24,8,f1_timing->phy_dqs_oe_timing_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset,24,8,f2_timing->phy_dqs_oe_timing_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(81)+chn_offset+slice_offset,24,8,f3_timing->phy_dqs_oe_timing_X);
	#endif
#endif
}

void cands_data_dqdqs_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	cands_data_dqdqs_ieoe_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_dqdqs_tsel_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
}


void cands_data_rddqdqs_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 j = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

#ifdef CODE_SIZE_OPTIMIZE
	#if DO_DFS_INIT
	for(j = 0; j<4; j++)
	{
	phy_reg_switch_dfs(chn_num,j);
	reg_bit_set(CANDS_PHY0_(67)+chn_offset+slice_offset,0,10,0);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,24,4,timing[j]->phy_rddata_en_dly_X);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset, 0,4,timing[j]->phy_rddata_en_tsel_dly_X);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset, 8,2,timing[j]->phy_rddata_en_ie_dly_X);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset, 0,10,timing[j]->phy_rddqs_dm_fall_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset,16,10,timing[j]->phy_rddqs_dm_rise_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,16,10,timing[j]->phy_rddqs_gate_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset, 0, 4,timing[j]->phy_rddqs_latency_adjust_X);
	for(i = 0; i< 8; i++)
	{
	reg_bit_set(CANDS_PHY0_(63)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,10,timing[j]->phy_rddqZ_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(68)+i*4+chn_offset+slice_offset, 0,10,timing[j]->phy_rddqs_dqZ_fall_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(67)+i*4+chn_offset+slice_offset,16,10,timing[j]->phy_rddqs_dqZ_rise_slave_delay_X);
	}
	}
	#else
	reg_bit_set(CANDS_PHY0_(67)+chn_offset+slice_offset,0,10,0);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,24,4,f0_timing->phy_rddata_en_dly_X);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset, 0,4,f0_timing->phy_rddata_en_tsel_dly_X);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset, 8,2,f0_timing->phy_rddata_en_ie_dly_X);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,0,10,f0_timing->phy_rddqs_dm_fall_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset,16,10,f0_timing->phy_rddqs_dm_rise_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,16,10,f0_timing->phy_rddqs_gate_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset, 0,4,f0_timing->phy_rddqs_latency_adjust_X);
	for(i = 0; i< 8; i++)
	{
	reg_bit_set(CANDS_PHY0_(63)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,10,f0_timing->phy_rddqZ_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(68)+i*4+chn_offset+slice_offset, 0,10,f0_timing->phy_rddqs_dqZ_fall_slave_delay_X);
	reg_bit_set(CANDS_PHY0_(67)+i*4+chn_offset+slice_offset,16,10,f0_timing->phy_rddqs_dqZ_rise_slave_delay_X);
	}
	#endif
#else
	//phy_rddm_slave_delay
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(67)+chn_offset+slice_offset,0,10,0);
	}
	#else
		reg_bit_set(CANDS_PHY0_(67)+chn_offset+slice_offset,0,10,0);
	#endif
	//phy_rddata_en_dly
	phy_reg_switch_dfs(chn_num,0);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,24,4,f0_timing->phy_rddata_en_dly_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num,1);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,24,4,f1_timing->phy_rddata_en_dly_X);
	phy_reg_switch_dfs(chn_num,2);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,24,4,f2_timing->phy_rddata_en_dly_X);
	phy_reg_switch_dfs(chn_num,3);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,24,4,f3_timing->phy_rddata_en_dly_X);
	#endif
	//phy_rddata_en_tsel_dly
	phy_reg_switch_dfs(chn_num,0);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset, 0,4,f0_timing->phy_rddata_en_tsel_dly_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num,1);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset, 0,4,f1_timing->phy_rddata_en_tsel_dly_X);
	phy_reg_switch_dfs(chn_num,2);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset, 0,4,f2_timing->phy_rddata_en_tsel_dly_X);
	phy_reg_switch_dfs(chn_num,3);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset, 0,4,f3_timing->phy_rddata_en_tsel_dly_X);
	#endif
	//phy_rddata_en_ie_dly
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,8,2,f0_timing->phy_rddata_en_ie_dly_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,8,2,f1_timing->phy_rddata_en_ie_dly_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,8,2,f2_timing->phy_rddata_en_ie_dly_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(83)+chn_offset+slice_offset,8,2,f3_timing->phy_rddata_en_ie_dly_X);
	#endif
	//phy_rddq0~7_slave_delay
	for(i = 0; i< 8; i++)
	{
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(63)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,10,f0_timing->phy_rddqZ_slave_delay_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(63)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,10,f1_timing->phy_rddqZ_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(63)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,10,f2_timing->phy_rddqZ_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(63)+((i>>1)<<2)+chn_offset+slice_offset, ((i%2)<<4)+0,10,f3_timing->phy_rddqZ_slave_delay_X);
	#endif
	}

	//phy_rddqs_dm_fall_slave_delay
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,0,10,f0_timing->phy_rddqs_dm_fall_slave_delay_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,0,10,f1_timing->phy_rddqs_dm_fall_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,0,10,f2_timing->phy_rddqs_dm_fall_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,0,10,f3_timing->phy_rddqs_dm_fall_slave_delay_X);
	#endif

	//phy_rddqs_dm_rise_slave_delay
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset,16,10,f0_timing->phy_rddqs_dm_rise_slave_delay_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset,16,10,f1_timing->phy_rddqs_dm_rise_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset,16,10,f2_timing->phy_rddqs_dm_rise_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset,16,10,f3_timing->phy_rddqs_dm_rise_slave_delay_X);
	#endif
	//phy_rddqs_dqZ_fall_slave_delay
	for(i = 0; i< 8; i++)
	{
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(68)+i*4+chn_offset+slice_offset, 0,10,f0_timing->phy_rddqs_dqZ_fall_slave_delay_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(68)+i*4+chn_offset+slice_offset, 0,10,f1_timing->phy_rddqs_dqZ_fall_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(68)+i*4+chn_offset+slice_offset, 0,10,f2_timing->phy_rddqs_dqZ_fall_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(68)+i*4+chn_offset+slice_offset, 0,10,f3_timing->phy_rddqs_dqZ_fall_slave_delay_X);
	#endif
	}

	//phy_rddqs_dqZ_rise_slave_delay
	for(i = 0; i< 8; i++)
	{
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(67)+i*4+chn_offset+slice_offset,16,10,f0_timing->phy_rddqs_dqZ_rise_slave_delay_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(67)+i*4+chn_offset+slice_offset,16,10,f1_timing->phy_rddqs_dqZ_rise_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(67)+i*4+chn_offset+slice_offset,16,10,f2_timing->phy_rddqs_dqZ_rise_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(67)+i*4+chn_offset+slice_offset,16,10,f3_timing->phy_rddqs_dqZ_rise_slave_delay_X);
	#endif
	}
	//phy_rddqs_gate_slave_delay
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,16,10,f0_timing->phy_rddqs_gate_slave_delay_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,16,10,f1_timing->phy_rddqs_gate_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,16,10,f2_timing->phy_rddqs_gate_slave_delay_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset,16,10,f3_timing->phy_rddqs_gate_slave_delay_X);
	#endif
	//phy_rddqs_latency_adjust
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset, 0,4,f0_timing->phy_rddqs_latency_adjust_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset, 0,4,f1_timing->phy_rddqs_latency_adjust_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset, 0,4,f2_timing->phy_rddqs_latency_adjust_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset, 0,4,f3_timing->phy_rddqs_latency_adjust_X);
	#endif
#endif
}


void cands_data_gtlvl_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif
	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_gate_error_delay_select
	reg_bit_set(CANDS_PHY0_(10)+chn_offset+slice_offset,16,5,0x17);

	//phy_gate_smpl1_slave_delay
	reg_bit_set(CANDS_PHY0_(11)+chn_offset+slice_offset,16,9,0xcc);

	//phy_gate_smpl2_slave_delay
	reg_bit_set(CANDS_PHY0_(12)+chn_offset+slice_offset,0,9,0x66);

	//phy_gtlvl_updt_wait_cnt
	reg_bit_set(CANDS_PHY0_(22)+chn_offset+slice_offset,8,4,0x4);

	//phy_gtlvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(22)+chn_offset+slice_offset,0,6,0x0);

#ifdef CODE_SIZE_OPTIMIZE
	#if DO_DFS_INIT
	for(i = 0; i < 4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset, 0,10,timing[i]->phy_gtlvl_back_step_X);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 8, 4,timing[i]->phy_gtlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,16,10,timing[i]->phy_gtlvl_final_step_X);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset,16, 4,timing[i]->phy_gtlvl_lat_adj_start_X);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset, 0,10,timing[i]->phy_gtlvl_rddqs_slv_dly_start_X);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset,16, 5,timing[i]->phy_gtlvl_resp_wait_cnt_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset, 0,10,f0_timing->phy_gtlvl_back_step_X);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 8, 4,f0_timing->phy_gtlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,16,10,f0_timing->phy_gtlvl_final_step_X);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset,16, 4,f0_timing->phy_gtlvl_lat_adj_start_X);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset, 0,10,f0_timing->phy_gtlvl_rddqs_slv_dly_start_X);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset,16, 5,f0_timing->phy_gtlvl_resp_wait_cnt_X);
	#endif
#else
	//phy_gtlvl_back_step
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,0,10,f0_timing->phy_gtlvl_back_step_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,0,10,f1_timing->phy_gtlvl_back_step_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,0,10,f2_timing->phy_gtlvl_back_step_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,0,10,f3_timing->phy_gtlvl_back_step_X);
	#endif
	//phy_gtlvl_dly_step
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset,8,4,f0_timing->phy_gtlvl_dly_step_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset,8,4,f1_timing->phy_gtlvl_dly_step_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset,8,4,f2_timing->phy_gtlvl_dly_step_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset,8,4,f3_timing->phy_gtlvl_dly_step_X);
	#endif
	//phy_gtlvl_final_step
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,16,10,f0_timing->phy_gtlvl_final_step_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,16,10,f1_timing->phy_gtlvl_final_step_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,16,10,f2_timing->phy_gtlvl_final_step_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,16,10,f3_timing->phy_gtlvl_final_step_X);
	#endif
	//phy_gtlvl_lat_adj_start
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset,16,4,f0_timing->phy_gtlvl_lat_adj_start_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset,16,4,f1_timing->phy_gtlvl_lat_adj_start_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset,16,4,f2_timing->phy_gtlvl_lat_adj_start_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset,16,4,f3_timing->phy_gtlvl_lat_adj_start_X);
	#endif
	//phy_gtlvl_rddqs_slv_dly_start
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset, 0,10,f0_timing->phy_gtlvl_rddqs_slv_dly_start_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset, 0,10,f1_timing->phy_gtlvl_rddqs_slv_dly_start_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset, 0,10,f2_timing->phy_gtlvl_rddqs_slv_dly_start_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(79)+chn_offset+slice_offset, 0,10,f3_timing->phy_gtlvl_rddqs_slv_dly_start_X);
	#endif

	//phy_gtlvl_resp_wait_cnt
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 16,5,f0_timing->phy_gtlvl_resp_wait_cnt_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 16,5,f1_timing->phy_gtlvl_resp_wait_cnt_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 16,5,f2_timing->phy_gtlvl_resp_wait_cnt_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 16,5,f3_timing->phy_gtlvl_resp_wait_cnt_X);
	#endif
#endif
}


void cands_data_wrlvl_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif
	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//wrlvl pattern
	//phy_user_patt0~4
	__raw_writel(CANDS_PHY0_(28)+chn_offset+slice_offset, 0x55555555);
	__raw_writel(CANDS_PHY0_(29)+chn_offset+slice_offset, 0xaaaaaaaa);
	__raw_writel(CANDS_PHY0_(30)+chn_offset+slice_offset, 0x55555555);
	__raw_writel(CANDS_PHY0_(31)+chn_offset+slice_offset, 0xaaaaaaaa);
	reg_bit_set(CANDS_PHY0_(32)+chn_offset+slice_offset,0,16,0x5555);


#ifdef CODE_SIZE_OPTIMIZE
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset,16,10,timing[i]->phy_wrlvl_delay_early_threshold_X);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset, 0,10,timing[i]->phy_wrlvl_delay_period_threshold_X);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,24, 4,timing[i]->phy_wrlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,16, 1,timing[i]->phy_wrlvl_early_force_zero_X);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 0, 5,timing[i]->phy_wrlvl_resp_wait_cnt_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset,16,10,f0_timing->phy_wrlvl_delay_early_threshold_X);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset, 0,10,f0_timing->phy_wrlvl_delay_period_threshold_X);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,24, 4,f0_timing->phy_wrlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,16, 1,f0_timing->phy_wrlvl_early_force_zero_X);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 0, 5,f0_timing->phy_wrlvl_resp_wait_cnt_X);
	#endif
#else
	//phy_wrlvl_delay_early_threshold
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset,16,10,f0_timing->phy_wrlvl_delay_early_threshold_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset,16,10,f1_timing->phy_wrlvl_delay_early_threshold_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset,16,10,f2_timing->phy_wrlvl_delay_early_threshold_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset,16,10,f3_timing->phy_wrlvl_delay_early_threshold_X);
	#endif
	//phy_wrlvl_delay_period_threshold
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,0,10,f0_timing->phy_wrlvl_delay_period_threshold_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,0,10,f1_timing->phy_wrlvl_delay_period_threshold_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,0,10,f2_timing->phy_wrlvl_delay_period_threshold_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,0,10,f3_timing->phy_wrlvl_delay_period_threshold_X);
	#endif
	//phy_wrlvl_dly_step
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,24,4,f0_timing->phy_wrlvl_dly_step_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,24,4,f1_timing->phy_wrlvl_dly_step_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,24,4,f2_timing->phy_wrlvl_dly_step_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,24,4,f3_timing->phy_wrlvl_dly_step_X);
	#endif
	//phy_wrlvl_early_force_zero
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,16,1,f0_timing->phy_wrlvl_early_force_zero_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,16,1,f1_timing->phy_wrlvl_early_force_zero_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,16,1,f2_timing->phy_wrlvl_early_force_zero_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(78)+chn_offset+slice_offset,16,1,f3_timing->phy_wrlvl_early_force_zero_X);
	#endif
	//phy_wrlvl_resp_wait_cnt
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 0,5,f0_timing->phy_wrlvl_resp_wait_cnt_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 0,5,f1_timing->phy_wrlvl_resp_wait_cnt_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 0,5,f2_timing->phy_wrlvl_resp_wait_cnt_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 0,5,f3_timing->phy_wrlvl_resp_wait_cnt_X);
  	#endif
#endif
	//phy_wrlvl_updt_wait_cnt
	reg_bit_set(CANDS_PHY0_(21)+chn_offset+slice_offset, 24,4,4);
	//phy_wrlvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(21)+chn_offset+slice_offset, 16,6,8);
}



void cands_data_wdqlvl_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_wdqlvl_dqdm_slv_dly_jump_offset
	reg_bit_set(CANDS_PHY0_(25)+chn_offset+slice_offset, 16,11,0xc0);

	//phy_wdqlvl_pattern
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_PHY0_(25)+chn_offset+slice_offset, 8,3,0x7);
	#else
	reg_bit_set(CANDS_PHY0_(25)+chn_offset+slice_offset, 8,3,0x2);
	#endif
	//phy_wdqlvl_burst_cnt
	reg_bit_set(CANDS_PHY0_(25)+chn_offset+slice_offset, 0,6,0x8);

	//phy_wdqlvl_qtr_dly_step
	reg_bit_set(CANDS_PHY0_(26)+chn_offset+slice_offset,16,4,0x1);

	//phy_wdqlvl_updt_wait_cnt
	reg_bit_set(CANDS_PHY0_(26)+chn_offset+slice_offset, 0,4,0xc);

	//phy_wdqlvl_datadm_mask
	reg_bit_set(CANDS_PHY0_(27)+chn_offset+slice_offset, 0,9,0x100);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(80)+chn_offset+slice_offset, 0,11,0x200);
		reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset, 0,8,0x20);
	}
	#else
		reg_bit_set(CANDS_PHY0_(80)+chn_offset+slice_offset, 0,11,0x200);
		reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset, 0,8,0x20);
	#endif

}

void cands_data_rdlvl_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif
	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_rdlvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(22)+chn_offset+slice_offset,16,6,8);

	//phy_rdlvl_updt_wait_cnt
	reg_bit_set(CANDS_PHY0_(22)+chn_offset+slice_offset,24,4,4);

	//phy_rdlvl_data_mask
	reg_bit_set(CANDS_PHY0_(23)+chn_offset+slice_offset,16,8,0);

	//phy_rdlvl_op_mode
	reg_bit_set(CANDS_PHY0_(23)+chn_offset+slice_offset,16,8,0);

#ifdef CODE_SIZE_OPTIMIZE
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset, 8, 4,timing[i]->phy_rdlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(80)+chn_offset+slice_offset,16,10,timing[i]->phy_rdlvl_rddqs_dq_slv_dly_start_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset, 8, 4,f0_timing->phy_rdlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(80)+chn_offset+slice_offset,16,10,f0_timing->phy_rdlvl_rddqs_dq_slv_dly_start_X);
	#endif
#else
	//phy_rdlvl_dly_step
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset,8,4,f0_timing->phy_rdlvl_dly_step_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset,8,4,f1_timing->phy_rdlvl_dly_step_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset,8,4,f2_timing->phy_rdlvl_dly_step_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset,8,4,f3_timing->phy_rdlvl_dly_step_X);
	#endif
	//phy_rdlvl_rddqs_dq_slv_dly_start
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(80)+chn_offset+slice_offset,16,10,f0_timing->phy_rdlvl_rddqs_dq_slv_dly_start_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(80)+chn_offset+slice_offset,16,10,f1_timing->phy_rdlvl_rddqs_dq_slv_dly_start_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(80)+chn_offset+slice_offset,16,10,f2_timing->phy_rdlvl_rddqs_dq_slv_dly_start_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(80)+chn_offset+slice_offset,16,10,f3_timing->phy_rdlvl_rddqs_dq_slv_dly_start_X);
	#endif
#endif
}


void cands_data_rxcal_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);


	//phy_rx_cal_sample_wait
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_PHY0_(51)+chn_offset+slice_offset,16,8,0xff);
	#else
	reg_bit_set(CANDS_PHY0_(51)+chn_offset+slice_offset,16,8,0x20);
	#endif
	//phy_rx_cal_override
	reg_bit_set(CANDS_PHY0_(51)+chn_offset+slice_offset,8,1,0);

	//phy_rx_cal_dq0~7
	reg_bit_set(CANDS_PHY0_(52)+chn_offset+slice_offset, 0,12,0x820);
	reg_bit_set(CANDS_PHY0_(52)+chn_offset+slice_offset,16,12,0x820);
	reg_bit_set(CANDS_PHY0_(53)+chn_offset+slice_offset, 0,12,0x820);
	reg_bit_set(CANDS_PHY0_(53)+chn_offset+slice_offset,16,12,0x820);
	reg_bit_set(CANDS_PHY0_(54)+chn_offset+slice_offset, 0,12,0x820);
	reg_bit_set(CANDS_PHY0_(54)+chn_offset+slice_offset,16,12,0x820);
	reg_bit_set(CANDS_PHY0_(55)+chn_offset+slice_offset, 0,12,0x820);
	reg_bit_set(CANDS_PHY0_(55)+chn_offset+slice_offset,16,12,0x820);

	//phy_rx_cal_dqs
	reg_bit_set(CANDS_PHY0_(56)+chn_offset+slice_offset,16,12,0x820);

	//phy_rx_cal_dm
	reg_bit_set(CANDS_PHY0_(56)+chn_offset+slice_offset,0,12,0x820);


	//phy_rx_cal_fdbk
	reg_bit_set(CANDS_PHY0_(57)+chn_offset+slice_offset, 0,12,0x820);
}

//not complete lp4boot code ??????
void cands_data_lp4boot_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//phy_lp4_boot_rptr_update,  for lpddr4 boot freq, time in cycles from dfi_rddata_en to release data from entry fifo
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,24,4, islp3?0x5:0x4); //??????

	//phy_lp4_boot_rddata_en_tsel_dly,  for lpddr4 boot freq, time in cycles from dfi_rddata_en earlier than TSEL enable
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,16,4, islp3?0x7:0); //??????lp3 have dif value

	//phy_lp4_boot_rddata_en_dly,  for lpddr4 boot freq, time in cycles from dfi_rddata_en early
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,8,4, islp3?0x8:0x1); //?????? lp3 have dif value

	//phy_lp4_boot_rddata_en_ie_dly,  for lpddr4 boot freq, time in cycles from dfi_rddata_en earlier than input enable
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,0,4, 0);

	//phy_lp4_boot_rddqs_latency_adjust
	reg_bit_set(CANDS_PHY0_(9)+chn_offset+slice_offset,16,4, islp3?0x3:0); //???? lp3 have dif value

	//phy_lp4_boot_rddqs_gate_slave_adjust
	reg_bit_set(CANDS_PHY0_(9)+chn_offset+slice_offset,0,10, islp3?0x71:0x133); //???? lp3 have dif value
}
void cands_data_mdll_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);


#ifdef CODE_SIZE_OPTIMIZE
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,16,10,timing[i]->phy_master_delay_start_X);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset, 8, 8,timing[i]->phy_master_delay_wait_X);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset, 0, 6,timing[i]->phy_master_delay_step_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,16,10,f0_timing->phy_master_delay_start_X);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset, 8, 8,f0_timing->phy_master_delay_wait_X);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset, 0, 6,f0_timing->phy_master_delay_step_X);
	#endif
#else
	//phy_master_delay_start
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,16,10,f0_timing->phy_master_delay_start_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,16,10,f1_timing->phy_master_delay_start_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,16,10,f2_timing->phy_master_delay_start_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(84)+chn_offset+slice_offset,16,10,f3_timing->phy_master_delay_start_X);
	#endif
	//phy_master_delay_wait
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,8,8,f0_timing->phy_master_delay_wait_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,8,8,f1_timing->phy_master_delay_wait_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,8,8,f2_timing->phy_master_delay_wait_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,8,8,f3_timing->phy_master_delay_wait_X);
	#endif
	//phy_master_delay_step
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,0,6,f0_timing->phy_master_delay_step_X);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,0,6,f1_timing->phy_master_delay_step_X);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,0,6,f2_timing->phy_master_delay_step_X);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(85)+chn_offset+slice_offset,0,6,f3_timing->phy_master_delay_step_X);
	#endif
#endif
}

void cands_phy_data_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type,
						uint32 f0,uint32 f1,uint32 f2,uint32 f3)
{
	cands_data_gen_init(slice_num,chn_num,phy_timing_info,ddr_type);
	cands_data_bypass_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_wrdqdqs_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_dqdqs_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_rddqdqs_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_gtlvl_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_wrlvl_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_wdqlvl_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_rdlvl_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_rxcal_init(slice_num,chn_num,phy_timing_info,ddr_type);
	cands_data_mdll_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_data_lp4boot_init(slice_num,chn_num,phy_timing_info,ddr_type);
}

void cands_adr_gen_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//phy_adr_tsel_enable
	reg_bit_set(CANDS_PHY0_(517)+chn_offset+slice_offset,16,1,PHY_ADR_ODT_EN); //????

	//phy_adr_tsel_select
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(543)+chn_offset+slice_offset,0,8,(PHY_ADR_ODT_DRV<<4)|PHY_ADR_ODT_DRV); //????
	}
	#else
		reg_bit_set(CANDS_PHY0_(543)+chn_offset+slice_offset,0,8,(PHY_ADR_ODT_DRV<<4)|PHY_ADR_ODT_DRV); //????
	#endif

	//phy_adr_ie_mode
	reg_bit_set(CANDS_PHY0_(518)+chn_offset+slice_offset,16,1,0);

	//phy_adr_adr_type, address pin ddr type
	reg_bit_set(CANDS_PHY0_(518)+chn_offset+slice_offset,0,2,islp3?1:2);

	//phy_adr_dll_mode
	reg_bit_set(CANDS_PHY0_(519)+chn_offset+slice_offset,0,15,0);

	//phy_adr_sw_txio_ctrl
	reg_bit_set(CANDS_PHY0_(542)+chn_offset+slice_offset,8,6,0);

	//phy_adr_clk_bypass_override
	reg_bit_set(CANDS_PHY0_(514)+chn_offset+slice_offset,0,1,0);

	//phy_adr_clk_wr_bypass_slave_delay
	reg_bit_set(CANDS_PHY0_(513)+chn_offset+slice_offset,16,11,islp3?0x80:0x0); //??????

}
void cands_adr_mdll_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

#ifdef CODE_SIZE_OPTIMIZE
	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;
#else
	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;
#endif
	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

#ifdef CODE_SIZE_OPTIMIZE
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset,16, 4,timing[i]->phy_adr_sw_master_mode);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset, 0,10,timing[i]->phy_adr_master_delay_start);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,24, 8,timing[i]->phy_adr_master_delay_wait);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,16, 6,timing[i]->phy_adr_master_delay_step);
	}
	#else
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset,16, 4,f0_timing->phy_adr_sw_master_mode);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset, 0,10,f0_timing->phy_adr_master_delay_start);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,24, 8,f0_timing->phy_adr_master_delay_wait);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,16, 6,f0_timing->phy_adr_master_delay_step);
	#endif
#else
	//phy_adr_sw_master_mode
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset,16,4,f0_timing->phy_adr_sw_master_mode);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset,16,4,f1_timing->phy_adr_sw_master_mode);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset,16,4,f2_timing->phy_adr_sw_master_mode);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset,16,4,f3_timing->phy_adr_sw_master_mode);
  	#endif
	//phy_adr_master_delay_start
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,0,10,f0_timing->phy_adr_master_delay_start);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,0,10,f1_timing->phy_adr_master_delay_start);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,0,10,f2_timing->phy_adr_master_delay_start);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,0,10,f3_timing->phy_adr_master_delay_start);
	#endif
	//phy_adr_master_delay_wait
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,24,8,f0_timing->phy_adr_master_delay_wait);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,24,8,f1_timing->phy_adr_master_delay_wait);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,24,8,f2_timing->phy_adr_master_delay_wait);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,24,8,f3_timing->phy_adr_master_delay_wait);
	#endif
	//phy_adr_master_delay_step
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,16,6,f0_timing->phy_adr_master_delay_step);
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,16,6,f1_timing->phy_adr_master_delay_step);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,16,6,f2_timing->phy_adr_master_delay_step);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,16,6,f3_timing->phy_adr_master_delay_step);
	#endif
#endif

}


void cands_adr_calvl_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;


	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_adr_calvl_coarse_dly
	reg_bit_set(CANDS_PHY0_(522)+chn_offset+slice_offset,16,11,0x40);

	//phy_adr_calvl_start
	reg_bit_set(CANDS_PHY0_(522)+chn_offset+slice_offset, 0,11,0x320);

	//phy_adr_calvl_qtr
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_PHY0_(523)+chn_offset+slice_offset, 0,11,0x40);
	#else
	reg_bit_set(CANDS_PHY0_(523)+chn_offset+slice_offset, 0,11,0xc0);
	#endif
	//phy_adr_calvl_device_map
	reg_bit_set(CANDS_PHY0_(527)+chn_offset+slice_offset,24, 4,1); //??????calvl device map en???

	//phy_adr_calvl_resp_wait_cnt
	reg_bit_set(CANDS_PHY0_(528)+chn_offset+slice_offset,24,4,0);

	//phy_adr_calvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(528)+chn_offset+slice_offset,16,4,0x2);

	//phy_adr_calvl_num_patterns
	reg_bit_set(CANDS_PHY0_(528)+chn_offset+slice_offset,8,2,0);

	//phy_adr_calvl_rank_ctrl
	reg_bit_set(CANDS_PHY0_(528)+chn_offset+slice_offset,0,2,3); ///????

	//phy_adr_calvl_debug_mode
	reg_bit_set(CANDS_PHY0_(529)+chn_offset+slice_offset,0,1,0);

	#ifdef DRAM_LPDDR3
	//phy_adr_calvl_fg0~3
	reg_bit_set(CANDS_PHY0_(532)+chn_offset+slice_offset,0,20,0x556aa);
	reg_bit_set(CANDS_PHY0_(534)+chn_offset+slice_offset,0,20,0xaa955);
	reg_bit_set(CANDS_PHY0_(536)+chn_offset+slice_offset,0,20,0xb3133);
	reg_bit_set(CANDS_PHY0_(538)+chn_offset+slice_offset,0,20,0x4cecc);

	//phy_adr_calvl_bg0~3
	reg_bit_set(CANDS_PHY0_(533)+chn_offset+slice_offset,0,20,0xaaaaa);
	reg_bit_set(CANDS_PHY0_(535)+chn_offset+slice_offset,0,20,0x55555);
	reg_bit_set(CANDS_PHY0_(537)+chn_offset+slice_offset,0,20,0x4cd33);
	reg_bit_set(CANDS_PHY0_(539)+chn_offset+slice_offset,0,20,0xb32cc);
	#else
	//phy_adr_calvl_fg0~3
	reg_bit_set(CANDS_PHY0_(532)+chn_offset+slice_offset,0,20,0x2a);
	reg_bit_set(CANDS_PHY0_(534)+chn_offset+slice_offset,0,20,0x15);
	reg_bit_set(CANDS_PHY0_(536)+chn_offset+slice_offset,0,20,0x33);
	reg_bit_set(CANDS_PHY0_(538)+chn_offset+slice_offset,0,20,0xc);

	//phy_adr_calvl_bg0~3
	reg_bit_set(CANDS_PHY0_(533)+chn_offset+slice_offset,0,20,0x15);
	reg_bit_set(CANDS_PHY0_(535)+chn_offset+slice_offset,0,20,0x2a);
	reg_bit_set(CANDS_PHY0_(537)+chn_offset+slice_offset,0,20,0xc);
	reg_bit_set(CANDS_PHY0_(539)+chn_offset+slice_offset,0,20,0x33);
	#endif
	//phy_adr_calvl_train_mask, ????????
	if(islp3)
	{
		switch(slice_num)
		{
			case 0:i = 0x2;break;
			case 1:i = 0xf;break;
			case 2:i = 0x3;break;
			case 3:i = 0xb;break;
		}
	}
	else
	{
		switch(slice_num)
		{
			case 0:i = 0x3;break;
			case 1:i = 0xf;break;
			case 2:i = 0x3;break;
			case 3:i = 0xf;break;
		}
	}
	reg_bit_set(CANDS_PHY0_(542)+chn_offset+slice_offset,0,6,i);


	//phy_adr_calvl_dly_step
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(548)+chn_offset+slice_offset,0,4,0x3);
	}
	#else
		reg_bit_set(CANDS_PHY0_(548)+chn_offset+slice_offset,0,4,0x3);
	#endif


}


void cands_adr_clkwr_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 j = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	i = islp3?0x380:0x300;
	#if DO_DFS_INIT
	for(j = 0; j<4; j++)
	{
	//phy_adr0~5_clk_wr_slave_delay
	phy_reg_switch_dfs(chn_num,j);
	reg_bit_set(CANDS_PHY0_(543)+chn_offset+slice_offset, 8,11,i);
	reg_bit_set(CANDS_PHY0_(544)+chn_offset+slice_offset, 0,11,i);
	reg_bit_set(CANDS_PHY0_(544)+chn_offset+slice_offset,16,11,i);
	reg_bit_set(CANDS_PHY0_(545)+chn_offset+slice_offset, 0,11,i);
	reg_bit_set(CANDS_PHY0_(545)+chn_offset+slice_offset,16,11,i);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset, 0,11,i);
	}
	#else
	reg_bit_set(CANDS_PHY0_(543)+chn_offset+slice_offset, 8,11,i);
	reg_bit_set(CANDS_PHY0_(544)+chn_offset+slice_offset, 0,11,i);
	reg_bit_set(CANDS_PHY0_(544)+chn_offset+slice_offset,16,11,i);
	reg_bit_set(CANDS_PHY0_(545)+chn_offset+slice_offset, 0,11,i);
	reg_bit_set(CANDS_PHY0_(545)+chn_offset+slice_offset,16,11,i);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset, 0,11,i);
	#endif
}

void cands_phy_adr_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type,
						uint32 f0,uint32 f1,uint32 f2,uint32 f3)
{
	cands_adr_gen_init(slice_num,chn_num,phy_timing_info,ddr_type);
	cands_adr_mdll_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_adr_calvl_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_adr_clkwr_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);

}

void cands_ac_gen_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//phy_lp4_boot_disable
	reg_bit_set(CANDS_PHY0_(1027)+chn_offset, 8,1,islp3?1:0);

	//phy_lp4_boot_low_freq_sel
	reg_bit_set(CANDS_PHY0_(1055)+chn_offset, 8,1,islp3?0:LP4_BOOT_LOW_FREQ);

	//phy_dfi_phyupd_type
	reg_bit_set(CANDS_PHY0_(1035)+chn_offset,16,2,1);

	//phy_adrctl_lpddr
	reg_bit_set(CANDS_PHY0_(1035)+chn_offset,24,1,1);

	//phy_lpddr3_cs
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,8,1,islp3);

	//phy_lpr4_active
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,0,1,islp3?0:1);

	//phy_low_freq_sel, ????whick frequency set to 1???  less than 300mhz???
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(1041)+chn_offset,0,1,PHY_LOW_FREQ_SEL);
	}
	#else
		reg_bit_set(CANDS_PHY0_(1041)+chn_offset,0,1,PHY_LOW_FREQ_SEL);
	#endif
	//phy_adrctl_lpddr
	reg_bit_set(CANDS_PHY0_(1041)+chn_offset,0,1,PHY_LOW_FREQ_SEL);

	//phy_tdfi_phy_wrdelay
	reg_bit_set(CANDS_PHY0_(1055)+chn_offset,24,1,0);

	//phy_lp_wakeup, !!!!!import, number of clock that take into wakeup from low power,??????
	reg_bit_set(CANDS_PHY0_(1055)+chn_offset,16,4,0);

	//phy_tcksre_wait, !!!!!wait time before pll turn off for deepsleep or dfs event, ??????
	reg_bit_set(CANDS_PHY0_(1055)+chn_offset,0,4,0x5);

	//phy_dll_rst_en, ?????no description in spec, how to set?????
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,16,2,0x0);

}

void cands_ac_adr_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//phy_adrctl_slave_loop_cnt_update
	reg_bit_set(CANDS_PHY0_(1035)+chn_offset,0,3,0);
	//phy_adrctl_rx_cal
	reg_bit_set(CANDS_PHY0_(1071)+chn_offset,0,25,0);

	//phy_adrctl_lp3_rx_cal
	reg_bit_set(CANDS_PHY0_(1072)+chn_offset,0,25,0);

	//phy_adrctl_manul_update
	reg_bit_set(CANDS_PHY0_(1078)+chn_offset,16,1,0);

	//phy_adrctl_mstr_dly_enc_sel, disable unused address slice to save powr, ????need set or not for lp3/4????
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,24,4,0);
}

void cands_ac_cscalvl_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);
	uint32 cs_map;

	//cs_map = islp3?(IS_2CS(ddr_type)?3:1):(IS_2CS(ddr_type)?0x33:(IS_16BIT(ddr_type)?0x1:0x11));
	cs_map = islp3?(IS_2CS(ddr_type)?3:1):((IS_2CS(ddr_type)?0x33:0x11)&(IS_16BIT(ddr_type)?0xf:0xff));


	//phy_cslvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(1029)+chn_offset,0,4,2);
	//phy_cslvl_coarse_capture_cnt
	reg_bit_set(CANDS_PHY0_(1029)+chn_offset,24,4,2);

	//phy_cslvl_coarse_dly
	reg_bit_set(CANDS_PHY0_(1029)+chn_offset,8,11,0x55);

	//phy_cslvl_cs_map
	reg_bit_set(CANDS_PHY0_(1027)+chn_offset,24,8,cs_map);

	//phy_cslvl_debug_mode
	reg_bit_set(CANDS_PHY0_(1030)+chn_offset,0,1,0);

	//phy_cslvl_dly_step
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,4,0);
	#else

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num,i);

	//phy_cslvl_dly_step
	reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,4,3);
	//phy_cslvl_qtr
	reg_bit_set(CANDS_PHY0_(1028)+chn_offset,16,11,0x40);

	//phy_cslvl_start
	reg_bit_set(CANDS_PHY0_(1028)+chn_offset,0,11,0x400);
	}
	#else
	//phy_cslvl_dly_step
	reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,4,3);
	//phy_cslvl_qtr
	reg_bit_set(CANDS_PHY0_(1028)+chn_offset,16,11,0x40);

	//phy_cslvl_start
	reg_bit_set(CANDS_PHY0_(1028)+chn_offset,0,11,0x400);
	#endif

	#endif
	//phy_cslvl_enable
	reg_bit_set(CANDS_PHY0_(1027)+chn_offset,16,1,PHY_CSLVL_EN);


	//phy_calvl_cs_map
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_PHY0_(1033)+chn_offset,0,16,cs_map);
	#else
	reg_bit_set(CANDS_PHY0_(1033)+chn_offset,0,16,0x5500);
	#endif
	//phy_calvl_result_mask
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,16,2,0);
	#else
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,16,2,2);
	#endif
}

void cands_ac_pll_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{

	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	volatile CANDS_PHY_TIMING_T * f0_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f1_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f2_timing = NULL;
	volatile CANDS_PHY_TIMING_T * f3_timing = NULL;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);


	//phy_pll_ctrl
	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num, 0);
	reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,13,f0_timing->phy_pll_ctrl);
	phy_reg_switch_dfs(chn_num, 1);
	reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,13,f1_timing->phy_pll_ctrl);
	phy_reg_switch_dfs(chn_num, 2);
	reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,13,f2_timing->phy_pll_ctrl);
	phy_reg_switch_dfs(chn_num, 3);
	reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,13,f3_timing->phy_pll_ctrl);
	#else
	reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,13,f0_timing->phy_pll_ctrl);
	#endif
	//phy_pll_ctrl_override
	reg_bit_set(CANDS_PHY0_(1005)+chn_offset,32,0,0);

	//phy_pll_wait
	reg_bit_set(CANDS_PHY0_(1038)+chn_offset,8,8,0x64);

	//phy_pll_bypass, ?????? lower than 300mhz don't need set ?????
	#ifdef PHY_PLL_BYPASS
	reg_bit_set(CANDS_PHY0_(1040)+chn_offset,0,8,0xff);
	#else
	reg_bit_set(CANDS_PHY0_(1040)+chn_offset,0,8,0x0);
	#endif
	//phy_lp4_boot_pll_ctrl, ??????when lp3, how to set ????
	reg_bit_set(CANDS_PHY0_(1049)+chn_offset,0,13,0x1b02);

}
#if 0
void cands_ac_ddl_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//phy_ddl_ac_enable, enable address/control block ddl delay test
	reg_bit_set(CANDS_PHY0_(1085)+chn_offset,0,32,0);

	//phy_ddl_ac_mode, control address/control block ddl delay test mode
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,0,11,0);

	//phy_ddl_ac_test_index
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,0,11,0);

}
#endif
void cands_ac_bypass_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//phy_sw_grp_bypass_shift
	reg_bit_set(CANDS_PHY0_(1026)+chn_offset,16,5,5);

	//phy_sw_grp_shirt0
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,16,5,0);
	//phy_sw_grp_shirt1
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,24,5,0);
	//phy_sw_grp_shirt2
	reg_bit_set(CANDS_PHY0_(1025)+chn_offset, 0,5,0);
	//phy_sw_grp_shirt3
	reg_bit_set(CANDS_PHY0_(1025)+chn_offset, 8,5,0);
	//phy_sw_grp_shirt4
	reg_bit_set(CANDS_PHY0_(1025)+chn_offset,16,5,0);
	//phy_sw_grp_shirt5
	reg_bit_set(CANDS_PHY0_(1025)+chn_offset,24,5,0);

	//phy_grp_bypass_override
	reg_bit_set(CANDS_PHY0_(1025)+chn_offset,24,5,0);

	//phy_grp_bypass_slave_delay
	reg_bit_set(CANDS_PHY0_(1026)+chn_offset,0,11,0);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num,i);
	//phy_grp_slave_delay0
	reg_bit_set(CANDS_PHY0_(1046)+chn_offset,0,11,0x300);
	//phy_grp_slave_delay1
	reg_bit_set(CANDS_PHY0_(1046)+chn_offset,16,11,0x300);
	//phy_grp_slave_delay2
	reg_bit_set(CANDS_PHY0_(1047)+chn_offset,0,11,0x300);
	//phy_grp_slave_delay3
	reg_bit_set(CANDS_PHY0_(1047)+chn_offset,16,11,0x300);
	//phy_grp_slave_delay4
	reg_bit_set(CANDS_PHY0_(1048)+chn_offset,0,11,0x300);
	//phy_grp_slave_delay5
	reg_bit_set(CANDS_PHY0_(1048)+chn_offset,16,11,0x300);
	}
	#else
	//phy_grp_slave_delay0
	reg_bit_set(CANDS_PHY0_(1046)+chn_offset,0,11,0x300);
	//phy_grp_slave_delay1
	reg_bit_set(CANDS_PHY0_(1046)+chn_offset,16,11,0x300);
	//phy_grp_slave_delay2
	reg_bit_set(CANDS_PHY0_(1047)+chn_offset,0,11,0x300);
	//phy_grp_slave_delay3
	reg_bit_set(CANDS_PHY0_(1047)+chn_offset,16,11,0x300);
	//phy_grp_slave_delay4
	reg_bit_set(CANDS_PHY0_(1048)+chn_offset,0,11,0x300);
	//phy_grp_slave_delay5
	reg_bit_set(CANDS_PHY0_(1048)+chn_offset,16,11,0x300);
	#endif
	//phy_sw_txio_ctl0
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,24,4,0);
	//phy_sw_txio_ctl1
	reg_bit_set(CANDS_PHY0_(1037)+chn_offset,0,4,0);
	//phy_sw_txio_ctl2
	reg_bit_set(CANDS_PHY0_(1037)+chn_offset,8,4,0);
	//phy_sw_txio_ctl3
	reg_bit_set(CANDS_PHY0_(1037)+chn_offset,16,4,0);
	//phy_sw_txio_ctl4
	reg_bit_set(CANDS_PHY0_(1037)+chn_offset,24,4,0);
	//phy_sw_txio_ctl5
	reg_bit_set(CANDS_PHY0_(1038)+chn_offset,0,4,0);
}
void cands_ac_pad_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

        unsigned short int lp4_phy_dq_vref_slice0[]={0xd2e,0xd2e,0xd2e,0xf1f};
        unsigned short int lp4_phy_dq_vref_slice1[]={0xd2e,0xd2e,0xd2e,0xf1f};
        unsigned short int lp4_phy_dq_vref_slice2[]={0xd2e,0xd2e,0xd2e,0xf1f};
        unsigned short int lp4_phy_dq_vref_slice3[]={0xd2e,0xd2e,0xd2e,0xf1f};
        unsigned short int lp4_phy_ca_vref[]={0xd2e,0xd2e,0xd2e,0xd2e};
	//phy_pad_atb_ctrl
	reg_bit_set(CANDS_PHY0_(1078)+chn_offset,0,16,0);

	#if DO_DFS_INIT
	for(i=0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num,i);
	//phy_pad_vref_ctrl_ac,bit12~9:mode_lv,2=lp3,6=lp4rang1,7=lp4rang2  bit8:en_lv  bit5~0:vrefsel_lv,5=50%vddq
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset,16,14,islp3?0x51f:lp4_phy_ca_vref[i]);
	//phy_pad_vref_ctrl_dq0
	reg_bit_set(CANDS_PHY0_(1041)+chn_offset, 8,14,islp3?0x51f:lp4_phy_dq_vref_slice0[i]);
	//phy_pad_vref_ctrl_dq1
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset, 0,14,islp3?0x51f:lp4_phy_dq_vref_slice1[i]);
	//phy_pad_vref_ctrl_dq2
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset,16,14,islp3?0x51f:lp4_phy_dq_vref_slice2[i]);
	//phy_pad_vref_ctrl_dq3
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset, 0,14,islp3?0x51f:lp4_phy_dq_vref_slice3[i]);
	}
	#else
	//phy_pad_vref_ctrl_ac,bit12~9:mode_lv,2=lp3,6=lp4rang1,7=lp4rang2  bit8:en_lv  bit5~0:vrefsel_lv,5=50%vddq
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset,16,14,islp3?0x51f:0xf1f);
	//phy_pad_vref_ctrl_dq0
	reg_bit_set(CANDS_PHY0_(1041)+chn_offset, 8,14,islp3?0x51f:0xf1f);
	//phy_pad_vref_ctrl_dq1
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset, 0,14,islp3?0x51f:0xf1f);
	//phy_pad_vref_ctrl_dq2
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset,16,14,islp3?0x51f:0xf1f);
	//phy_pad_vref_ctrl_dq3
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset, 0,14,islp3?0x51f:0xf1f);
	#endif

	//phy_set_dfi_input_0~5, indicate default value of adrctl slice bit
	reg_bit_set(CANDS_PHY0_(1044)+chn_offset, 8,4,0);
	reg_bit_set(CANDS_PHY0_(1044)+chn_offset,16,4,0);
	reg_bit_set(CANDS_PHY0_(1044)+chn_offset,24,4,0);
	reg_bit_set(CANDS_PHY0_(1045)+chn_offset, 0,4,0);
	reg_bit_set(CANDS_PHY0_(1045)+chn_offset, 8,4,0);
	reg_bit_set(CANDS_PHY0_(1045)+chn_offset,16,4,0);

	//phy_pad_addr_drive - ddr202
	reg_bit_set(CANDS_PHY0_(1058)+chn_offset,15,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1058)+chn_offset,14,1,islp3?0:1); 			//lpddr4
	reg_bit_set(CANDS_PHY0_(1058)+chn_offset,12,2,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1058)+chn_offset,11,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1058)+chn_offset,9,2,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1058)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1058)+chn_offset,4,4,PHY_ADDR_DRV); 		//drive strength
	reg_bit_set(CANDS_PHY0_(1058)+chn_offset,0,4,PHY_ADDR_DRV); 		//drive strength

	//phy_pad_cke_drive - ddr202
	reg_bit_set(CANDS_PHY0_(1065)+chn_offset,15,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1065)+chn_offset,14,1,islp3?0:1); 			//lpddr4
	reg_bit_set(CANDS_PHY0_(1065)+chn_offset,12,2,PHY_CKE_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1065)+chn_offset,11,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1065)+chn_offset,9,2,PHY_CKE_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1065)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1065)+chn_offset,4,4,PHY_CKE_DRV); 		//drive strength
	reg_bit_set(CANDS_PHY0_(1065)+chn_offset,0,4,PHY_CKE_DRV); 		//drive strength


	//phy_pad_clk_drive  - ddr203
	reg_bit_set(CANDS_PHY0_(1059)+chn_offset,15,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1059)+chn_offset,14,1,islp3?0:1); 			//lpddr4
	reg_bit_set(CANDS_PHY0_(1059)+chn_offset,12,2,PHY_CLK_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1059)+chn_offset,11,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1059)+chn_offset,9,2,PHY_CLK_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1059)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1059)+chn_offset,4,4,PHY_CLK_DRV); 			//drive strength
	reg_bit_set(CANDS_PHY0_(1059)+chn_offset,0,4,PHY_CLK_DRV); 			//drive strength

	//phy_pad_cs_drive   - ddr202
	reg_bit_set(CANDS_PHY0_(1069)+chn_offset,15,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1069)+chn_offset,14,1,islp3?0:1); 			//lpddr4
	reg_bit_set(CANDS_PHY0_(1069)+chn_offset,12,2,PHY_CS_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1069)+chn_offset,11,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1069)+chn_offset,9,2,PHY_CS_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1069)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1069)+chn_offset,4,4,PHY_CS_DRV); 			//drive strength
	reg_bit_set(CANDS_PHY0_(1069)+chn_offset,0,4,PHY_CS_DRV); 			//drive strength

	//phy_pad_data_drive - ddr202
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,7,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,6,1,islp3?0:1); 			//lpddr4
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,4,2,PHY_DATA_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,3,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,1,2,PHY_DATA_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,0,1,1); 					//slew rate  mode


	//phy_pad_dqs_drive  - ddr203
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,23,1,0); 					//rpull
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,22,1,islp3?0:1); 			//lpddr4
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,20,2,PHY_DQS_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,19,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,17,2,PHY_DQS_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,16,1,1); 					//slew rate  mode

	//phy_pad_fdbk_drive - ddr202
	reg_bit_set(CANDS_PHY0_(1056)+chn_offset,15,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1056)+chn_offset,14,1,islp3?0:1); 			//lpddr4
	reg_bit_set(CANDS_PHY0_(1056)+chn_offset,12,2,PHY_FDBK_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1056)+chn_offset,11,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1056)+chn_offset,9,2,PHY_FDBK_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1056)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1056)+chn_offset,4,4,PHY_FDBK_DRV); 			//drive strength
	reg_bit_set(CANDS_PHY0_(1056)+chn_offset,0,4,PHY_FDBK_DRV); 			//drive strength

	//phy_pad_rst_drive  - ddr202
	reg_bit_set(CANDS_PHY0_(1067)+chn_offset,15,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1067)+chn_offset,14,1,islp3?0:1); 			//lpddr4
	reg_bit_set(CANDS_PHY0_(1067)+chn_offset,12,2,PHY_RST_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1067)+chn_offset,11,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1067)+chn_offset,9,2,PHY_RST_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1067)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1067)+chn_offset,4,4,PHY_RST_DRV); 			//drive strength
	reg_bit_set(CANDS_PHY0_(1067)+chn_offset,0,4,PHY_RST_DRV); 			//drive strength

	//phy_pad_addr_term - ddr202
	reg_bit_set(CANDS_PHY0_(1063)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1063)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_clk_term
	reg_bit_set(CANDS_PHY0_(1064)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1064)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_cs_term
	reg_bit_set(CANDS_PHY0_(1070)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1070)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_data_term
	reg_bit_set(CANDS_PHY0_(1061)+chn_offset,17,1,0); 					//DIFFI_EN ??????
	reg_bit_set(CANDS_PHY0_(1061)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_dqs_term
	reg_bit_set(CANDS_PHY0_(1062)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_fdbk_term
	reg_bit_set(CANDS_PHY0_(1060)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1060)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_rst_term
	reg_bit_set(CANDS_PHY0_(1060)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1060)+chn_offset, 0,17,0x4410); 			//pvtr/n/p



}


void cands_ac_cal_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);
	uint32 cal_clk_div = 0;

	#if 0
	switch(DDR_CLK)
	{
		case 26:  cal_clk_div = 1;break;
		case 156: cal_clk_div = 2;break;
		case 466: cal_clk_div = 4;break;
		case 933: cal_clk_div = 5;break;
		default: while(1);
	}
	#else
	if(DDR_CLK_CAL <= 80)
	{
		cal_clk_div = 1; //clk_ctrl/2
	}
	else if(DDR_CLK_CAL <= 160)
	{
		cal_clk_div = 2; //clk_ctrl/4
	}
	else if(DDR_CLK_CAL <= 320)
	{
		cal_clk_div = 3; //clk_ctrl/8
	}
	else if(DDR_CLK_CAL <= 640)
	{
		cal_clk_div = 4; //clk_ctrl/16
	}
	else
	{
		cal_clk_div = 5; //clk_ctrl/32
	}
	#endif
	//phy_cal_clk_select, pad calibration clk, 0/1: clk_ctrl/2  2/3/4/5/6/7: clk_ctr/4/8/16/32/64/128
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset, 8,3,cal_clk_div);

	//phy_cal_interval_count, periodic calibration cycle, when phy_cal_mode[1]=1
	#ifdef DRAM_LPDDR3
	__raw_writel(CANDS_PHY0_(1074)+chn_offset, 4000000);
	#else
	__raw_writel(CANDS_PHY0_(1074)+chn_offset, 0);
	#endif
	//phy_cal_mode
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset, 0,1,0); //init_disable, disable pad cal when init
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset, 1,1,0); //auto_en, enable automatic cal
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset, 2,2,1); //base_mode ?????
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset, 4,4,islp3?0x0:0x6); //pad_cal_mode ??????

	//phy_cal_sample_wait
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset, 0,8,0xff);

	//phy_cal_start, sw trigger pad calibration

	//phy_cal_clear, sw clear pad calibration machine and result




}

void cands_phy_ac_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type,
						uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	cands_ac_gen_init(chn_num,phy_timing_info,ddr_type);
	cands_ac_adr_init(chn_num,phy_timing_info,ddr_type);
	cands_ac_cscalvl_init(chn_num,phy_timing_info,ddr_type);
	cands_ac_pll_init(chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_ac_bypass_init(chn_num,phy_timing_info,ddr_type);
	cands_ac_pad_init(chn_num,phy_timing_info,ddr_type);
	cands_ac_cal_init(chn_num,phy_timing_info,ddr_type);
}

void cands_phy_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_PHY_TIMING_T* phy_timing_info,
					uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	#if DO_DFS_INIT
	phy_reg_multicast_shut(chn_num);
	#else
	phy_reg_multicast_open(chn_num);
	#endif

	cands_phy_ac_init(chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);

	cands_phy_data_init(0,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_phy_data_init(1,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_phy_data_init(2,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
	cands_phy_data_init(3,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);

	cands_phy_adr_init(0,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3); //ca0/1
	cands_phy_adr_init(1,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3); //ca2/3/4/5
	cands_phy_adr_init(2,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3); //ca6/7
	cands_phy_adr_init(3,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3); //ca8/9/10/11

	#if DO_DFS_INIT
	phy_reg_switch_dfs(chn_num,fn_ctl_target);
	#endif
}

void cands_phy_dataslice_lpbk_test()
{
	uint32 i = 0;

	i = (1<<6)|//ctrl_lpbk_go: 0:stop 1:go
			(3<<4)|//ctrl_lpbk_cnt: 0:free runing 1:1024 clk 2:8192 clk 3:64k clk
			(0<<3)|//ctrl_data_err_clk: 0:no action 1:clear the error
			(1<<2)|//ctrl_data_type: 0:lfsr 1:clock pattern
			(0<<1)| //loopback mode: 0:internal 1:external
			(1<<0); //loopback en

	reg_bit_set(CANDS_PHY0_(9),  24,7,i);
	reg_bit_set(CANDS_PHY0_(137),24,7,i);
	reg_bit_set(CANDS_PHY0_(265),24,7,i);
	reg_bit_set(CANDS_PHY0_(393),24,7,i);
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

void ddr_freq_target_set(unsigned int ddr_clk)
{
	uint32 ddr_freq=0;

#ifdef DRAM_LPDDR4
	ddr_freq = __get_mhz_num(ddr_clk);
	switch(ddr_freq)
	{
		case 1200:fn_ctl_target=3;fsp_wr=1;fsp_op=1;break;
		case 600 :fn_ctl_target=2;fsp_wr=0;fsp_op=0;break;
		case 400 :fn_ctl_target=1;fsp_wr=0;fsp_op=0;break;
		case 200 :fn_ctl_target=0;fsp_wr=0;fsp_op=0;break;
		default:while(1);
	}
	fn_pi_target=fn_ctl_target+1;
#else
	fn_ctl_target=0;
	fn_pi_target=0;
	fsp_wr=0;
	fsp_op=0;
#endif
}

BOOLEAN ddr_clk_set(DDR_CHANNEL_NUM_E chn_num,unsigned int ddr_clk,BOOLEAN islp3)
{

	uint32 dpll_kint = 0;
	uint32 dpll_nint = 0;
	uint32 clk_1xdiv = 0;
	uint32 clk_2xdiv = 0;
	uint32 xtal_26m  = 0;
	uint32 twpll_sel = 0;
	uint32 ddr_freq   = 0;
	//lp3 dpll = 920mhz, lp4 dpll = 1192mhz
	dpll_nint = islp3?0x23:0x2e;
	dpll_kint = islp3?0x313b13:0x13b13b;
	//dpll_kint = islp3?0x49D89D:0x6C4EC4;
	//dpll_kint = islp3?0xE2762:0xD89D8;

	ddr_freq = __get_mhz_num(ddr_clk);
	switch(ddr_freq)
	{
		case 1200:	xtal_26m = 0; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 0;break;
		case 933:	xtal_26m = 0; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 0;break;
		case 768:	xtal_26m = 0; twpll_sel = 1; clk_1xdiv = 1; clk_2xdiv = 1;break;
		case 600:	xtal_26m = 0; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 1;break;
		case 466:	xtal_26m = 0; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 1;break;
		case 400:	xtal_26m = 0; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 2;break;
		case 311:	xtal_26m = 0; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 2;break;
		case 240:	xtal_26m = 0; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 4;break;
		case 200:	xtal_26m = 0; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 5;break;
		case 156:	xtal_26m = 0; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 5;break;
		case 26:	xtal_26m = 1; twpll_sel = 0; clk_1xdiv = 1; clk_2xdiv = 0;break;
		default:	while(1); //other invald frequency
	}

	if(chn_num == 0)
	{
		#ifdef DDR_CLK_FLOATING
		//clear div_s and mod_en to 0
		reg_bit_set(ANA_APB_DPLL0_CFG0, 14, 2, 0);
		#endif

		//set dpll0
		reg_bit_set(ANA_APB_DPLL0_CFG1, 25, 7,dpll_nint);
		reg_bit_set(ANA_APB_DPLL0_CFG1,  0,23,dpll_kint);


		#ifdef DDR_CLK_FLOATING
		reg_bit_set(ANA_APB_DPLL0_CFG0, 14, 1, 1);//mod_en = 1
		reg_bit_set(ANA_APB_DPLL0_CFG0, 15, 1, 1);//div_s  = 1
		#endif

		//set div
		reg_bit_set(AON_APB_CGM_CFG, 0,8, (xtal_26m<<6)|(clk_2xdiv<<2)|(clk_1xdiv<<1)|twpll_sel);

		//enable 1x/2x clk
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,  15, 2, 3);

	}
	else
	{
		//disable pub1 force shutdown
		reg_bit_set(PMU_APB_PD_PUB1_SYS_CFG, 25, 1,0);

		#ifdef DDR_CLK_FLOATING
		//clear div_s and mod_en to 0
		reg_bit_set(ANA_APB_DPLL1_CFG0, 14, 2, 0);
		#endif

		//set dpll1
		reg_bit_set(ANA_APB_DPLL1_CFG1, 25, 7,dpll_nint);
		reg_bit_set(ANA_APB_DPLL1_CFG1,  0,23,dpll_kint);

		#ifdef DDR_CLK_FLOATING
		reg_bit_set(ANA_APB_DPLL1_CFG0, 14, 1, 1);//mod_en = 1
		reg_bit_set(ANA_APB_DPLL1_CFG0, 15, 1, 1);//div_s  = 1
		#endif

		//set div
		reg_bit_set(AON_APB_CGM_CFG, 16,8, (xtal_26m<<6)|(clk_2xdiv<<2)|(clk_1xdiv<<1)|twpll_sel);

		//enable 1x/2x clk
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,  17, 2, 3);
	}
	wait_us(50);
	return TRUE;
}

void ddr_init_trigger(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//pi_start
	reg_bit_set(CANDS_PI0_(0)+chn_offset,0,1,PI_START);

	//trigger whole ddr init flow, set START to 1
	reg_bit_set(CANDS_CTL0_(0)+chn_offset,0,1,1);
}

#ifdef DRAM_LPDDR4
void phy_dq_dqs_ds_set(uint32 chn_offset,uint32 enable,uint32 ds)
{
	uint32 i=0;
	for(i=0;i<4;i++)
	{
		//phy_dq_tsel_enable
		reg_bit_set(CANDS_PHY0_(4)+chn_offset+i*0x200,17,1,enable);
		//phy_dq_tsel_select
		reg_bit_set(CANDS_PHY0_(5)+chn_offset+i*0x200,8,4,ds);
		reg_bit_set(CANDS_PHY0_(5)+chn_offset+i*0x200,12,4,ds);
		//phy_dqs_tsel_enable
		reg_bit_set(CANDS_PHY0_(5)+chn_offset+i*0x200,25,1,enable);
		//phy_dqs_tsel_select
		reg_bit_set(CANDS_PHY0_(6)+chn_offset+i*0x200,8,4,ds);
		reg_bit_set(CANDS_PHY0_(6)+chn_offset+i*0x200,12,4,ds);
		
	}
}

void phy_dq_dqs_odt_set(uint32 chn_offset,uint32 enable,uint32 odt)
{
	uint32 i=0;
	for(i=0;i<4;i++)
	{
		//phy_dq_tsel_enable
		reg_bit_set(CANDS_PHY0_(4)+chn_offset+i*0x200,16,1,enable);
		//phy_dq_tsel_select
		reg_bit_set(CANDS_PHY0_(5)+chn_offset+i*0x200,0,4,odt);
		reg_bit_set(CANDS_PHY0_(5)+chn_offset+i*0x200,4,4,0x0);
		//phy_dqs_tsel_enable
		reg_bit_set(CANDS_PHY0_(5)+chn_offset+i*0x200,24,1,enable);
		//phy_dqs_tsel_select
		reg_bit_set(CANDS_PHY0_(6)+chn_offset+i*0x200,0,4,odt);
		reg_bit_set(CANDS_PHY0_(6)+chn_offset+i*0x200,4,4,0x0);
	}
}

void vref_rang_cfg(uint32 freq_sel,uint32 chn_offset)
{
    switch(freq_sel)
    {
        case 0:
            REG32(CANDS_PI0_(162)+chn_offset)=0x01726011;
	    phy_dq_dqs_ds_set(chn_offset,0x1,0x7);
	    phy_dq_dqs_odt_set(chn_offset,0x0,0x0);
            break;
        case 1:
            REG32(CANDS_CTL0_(934)+chn_offset)=0x0;
            REG32(CANDS_PI0_(162)+chn_offset)=0x01726011;
	    phy_dq_dqs_ds_set(chn_offset,0x1,0x7);
	    phy_dq_dqs_odt_set(chn_offset,0x0,0x0);
            break;
        case 2:
            REG32(CANDS_CTL0_(934)+chn_offset)=0x0;
            REG32(CANDS_PI0_(162)+chn_offset)=0x01726011;
	    phy_dq_dqs_ds_set(chn_offset,0x1,0x7);
	    phy_dq_dqs_odt_set(chn_offset,0x0,0x0);
            break;
        case 3:
            REG32(CANDS_CTL0_(934)+chn_offset)=0x0;
            REG32(CANDS_PI0_(162)+chn_offset)=0x01726011;
	    phy_dq_dqs_ds_set(chn_offset,0x1,0x7);
	    phy_dq_dqs_odt_set(chn_offset,0x0,0x0);
            break;
        case 4:
            REG32(CANDS_CTL0_(934)+chn_offset)=0x0;
            REG32(CANDS_PI0_(162)+chn_offset)=0x01231a11;
	    phy_dq_dqs_ds_set(chn_offset,0x1,0x6);
	    phy_dq_dqs_odt_set(chn_offset,0x1,0xe);
            break;
        default:
            break;
    }
}

void f0_master_delay_update(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 tmp=0;
    uint32 slice=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    for(slice=0; slice<4; slice++)
    {
//        reg_bit_set(CANDS_PHY0_(516)+chn_offset+(slice*0x200),0, 3, 0);     //phy_adr_master_dly_lock_obs_select
//        reg_bit_set(CANDS_PHY0_(517)+chn_offset+(slice*0x200),8, 1, 1);     //sc_phy_adr_snap_obs_regs
//        tmp=reg_bit_get(CANDS_PHY0_(516)+chn_offset+(slice*0x200),8, 10);     //phy_adr_master_dly_lock_obs
//        tmp=(tmp*(1.5));
//        if(tmp>0x3ff)
//        {
//            tmp=0x3ff;
//        }
        reg_bit_set(CANDS_PHY0_(514)+chn_offset+(slice*0x200), 0, 1, 1);     //phy_adr_clk_bypass_override
        //reg_bit_set(CANDS_PHY0_(513)+chn_offset+(slice*0x200),16, 10, tmp);     //phy_adr_clk_wr_bypass_slave_delay

        reg_bit_set(CANDS_PHY0_(19)+chn_offset+(slice*0x200), 16, 3, 0);     //phy_master_dly_lock_obs_select
        reg_bit_set(CANDS_PHY0_(10)+chn_offset+(slice*0x200), 24, 1, 1);     //sc_phy_snap_obs_regs
        tmp=reg_bit_get(CANDS_PHY0_(35)+chn_offset+(slice*0x200), 0, 10);     //phy_master_dly_lock_obs
        tmp=(tmp*(2.1));
        if(tmp>0x3ff)
        {
            tmp=0x3ff;
        }
        reg_bit_set(CANDS_PHY0_(1)+chn_offset+(slice*0x200), 8, 10, tmp);     //phy_clk_wr_bypass_slave_delay
        reg_bit_set(CANDS_PHY0_(1)+chn_offset+(slice*0x200), 18, 1, 1);     //phy_clk_wr_bypass_slave_delay
   }
}
#endif
void sync_mr12_mr14(uint32 chn_num,BOOLEAN islp3)
{
    uint32 tmp=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    //fsp_phy_update_mrw
    reg_bit_set(CANDS_CTL0_(907)+chn_offset,16, 1, islp3?1:0);  ///?????? define which part to updat MR12&MR14 in init/dfs/sw mrw 0:ctl 1:phy or pi
    tmp=reg_bit_get(CANDS_PI0_(169)+chn_offset,8,8);       //MR12_F0_0
    reg_bit_set(CANDS_CTL0_(868)+chn_offset,0,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(170)+chn_offset,24,8);       //MR12_F1_0
    reg_bit_set(CANDS_CTL0_(867)+chn_offset,0,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(172)+chn_offset,8,8);       //MR12_F2_0
    reg_bit_set(CANDS_CTL0_(867)+chn_offset,8,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(173)+chn_offset,24,8);       //MR12_F3_0
    reg_bit_set(CANDS_CTL0_(867)+chn_offset,16,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(175)+chn_offset,8,8);       //MR12_F4_0
    reg_bit_set(CANDS_CTL0_(867)+chn_offset,24,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(177)+chn_offset,0,8);       //MR12_F0_1
    reg_bit_set(CANDS_CTL0_(873)+chn_offset,0,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(178)+chn_offset,16,8);       //MR12_F1_1
    reg_bit_set(CANDS_CTL0_(872)+chn_offset,0,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(180)+chn_offset,0,8);       //MR12_F2_1
    reg_bit_set(CANDS_CTL0_(872)+chn_offset,8,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(181)+chn_offset,16,8);       //MR12_F3_1
    reg_bit_set(CANDS_CTL0_(872)+chn_offset,16,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(183)+chn_offset, 0,8);       //MR12_F4_1
    reg_bit_set(CANDS_CTL0_(872)+chn_offset,24,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(169)+chn_offset,16,8);       //MR14_F0_0
    reg_bit_set(CANDS_CTL0_(869)+chn_offset,8,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(171)+chn_offset,0,8);       //MR14_F1_0
    reg_bit_set(CANDS_CTL0_(868)+chn_offset,8,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(172)+chn_offset,16,8);       //MR14_F2_0
    reg_bit_set(CANDS_CTL0_(868)+chn_offset,16,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(174)+chn_offset,0,8);       //MR14_F3_0
    reg_bit_set(CANDS_CTL0_(868)+chn_offset,24,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(175)+chn_offset,16,8);       //MR14_F4_0
    reg_bit_set(CANDS_CTL0_(869)+chn_offset,0,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(177)+chn_offset,8,8);       //MR12_F0_1
    reg_bit_set(CANDS_CTL0_(874)+chn_offset,8,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(178)+chn_offset,24,8);       //MR12_F1_1
    reg_bit_set(CANDS_CTL0_(873)+chn_offset,8,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(180)+chn_offset,8,8);       //MR12_F2_1
    reg_bit_set(CANDS_CTL0_(873)+chn_offset,16,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(181)+chn_offset,24,8);       //MR12_F3_1
    reg_bit_set(CANDS_CTL0_(873)+chn_offset,24,8,tmp);
    tmp=reg_bit_get(CANDS_PI0_(183)+chn_offset, 8,8);       //MR12_F4_1
    reg_bit_set(CANDS_CTL0_(874)+chn_offset, 8,8,tmp);
 }
void polling_pi_training_done(DDR_CHANNEL_NUM_E chn_num,BOOLEAN islp3)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	volatile uint32 pi_tr_done = 0;
	volatile uint32 i = 0;
	uint32 freq_sel = 0;

        if(chn_num == 0)
        __ddr_print("\r\n\r\nenter pub - 0 polling pi training");
        else
        __ddr_print("\r\n\r\nenter pub - 1 polling pi training");



	//if(islp3)
	#ifdef  DRAM_LPDDR3
	{
		return;
		//do{pi_tr_done = (REG32(CANDS_PI0_(256)+chn_offset)&0x1);}
		//while(pi_tr_done == 0);
	}
	#else
	{
		//write freq_int_en
		reg_bit_set(PUB0_APB_FREQ_ACK_LP4_INIT+chn_offset,0,1,1);

		while(pi_tr_done == 0)
		{
			i++;
			pi_tr_done = (REG32(CANDS_PI0_(256)+chn_offset)&0x1);

			if(1==pi_tr_done)
				break;

			if(REG32(PUB0_APB_FREQ_CHANGE_LP4_INIT+chn_offset)&0X8)
			{
				//read *_11e0 bit[8:4] freq_type and does frequency change to 0x402e_0098 according to dfs table???
				freq_sel = (REG32(PUB0_APB_FREQ_CHANGE_LP4_INIT+chn_offset)&0X1F0)>>4;
                                //vref rang set
                                vref_rang_cfg( freq_sel, chn_offset);
				//set calvl traget freq ddr clk div
				reg_bit_set(AON_APB_CGM_CFG,(chn_num<<4),8,pi_fn_div[freq_sel]);

				//write freq_ack
				reg_bit_set(PUB0_APB_FREQ_CHANGE_LP4_INIT+chn_offset,9,1,1);

				//write int_clr
				reg_bit_set(PUB0_APB_FREQ_CHANGE_LP4_INIT+chn_offset,1,1,1);

				//write *_21e0=32'h3FE, to do write 1 clear all register except for enable bit
				REG32(PUB0_APB_FREQ_CHANGE_WCL_LP4_INIT+chn_offset) = 0x3FE;
			}
			if((freq_sel==4)&&(fn_ctl_target!=3))
			{
				while((REG32(CANDS_PHY0_(1051)+chn_offset)&0x1)!=0x1)
				{
					wait_us(1);
				}
        			f0_master_delay_update(chn_num);
			}
			wait_us(10);

			pi_tr_done = (REG32(CANDS_PI0_(256)+chn_offset)&0x1);

			if((i <= 1500) && ((i%300) == 0))
			{
				if(chn_num == 0)
                                __ddr_print("\r\nddr polling pub0 pi tr hung, do rx cal workaround...");
                                else
                                __ddr_print("\r\nddr polling pub1 pi tr hung, do rx cal workaround...");
				//re-do rx offset calibration
				REG32(0X300020CC+chn_offset) = 0x00200001;
                                REG32(0X300022CC+chn_offset) = 0x00200001;
                                REG32(0X300024CC+chn_offset) = 0x00200001;
                                REG32(0X300026CC+chn_offset) = 0x00200001;
			}

                        if(i >= 1501)
                        {
                                __ddr_print("\r\nddr polling ");
                                __ddr_wdg_reset();
                                while(1);
                        }
		}

	}
	#endif
}
void wait_ctl_init_done(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	volatile uint32 ctl_tr_done = 0;
	volatile uint32 i = 0;
	volatile uint32 timeout = 0;


	//do{ctl_tr_done = (REG32(CANDS_CTL0_(319)+chn_offset)&0x10);}
	do{
		for(i = 0; i <1000; i++);

		ctl_tr_done = (REG32(CANDS_CTL0_(319)+chn_offset)&0x10);

		timeout++;
		#ifdef DRAM_LPDDR3
		if(timeout == 0x800)
		{
			// do manual rx cal
			reg_bit_set(CANDS_PHY0_(51), 0,1,1);
			reg_bit_set(CANDS_PHY0_(179),0,1,1);
			reg_bit_set(CANDS_PHY0_(307),0,1,1);
			reg_bit_set(CANDS_PHY0_(435),0,1,1);
		}
		#endif
		if(timeout == 0x1000)
			__ddr_wdg_reset();
	}
	while(ctl_tr_done == 0);

	__ddr_print("\r\nleave ddr wait ctl init done");

}
void write_fsp_valid(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	#ifdef  DRAM_LPDDR3
	{
		return;
	}
	#else
	{
		return;
		//cs0
		reg_bit_set(CANDS_CTL0_(869)+chn_offset,16,1,PI_F0_TRAIN);
		reg_bit_set(CANDS_CTL0_(869)+chn_offset,24,1,PI_F1_TRAIN);
		reg_bit_set(CANDS_CTL0_(870)+chn_offset, 0,1,PI_F2_TRAIN);
		reg_bit_set(CANDS_CTL0_(870)+chn_offset, 8,1,PI_F3_TRAIN);
		reg_bit_set(CANDS_CTL0_(870)+chn_offset,16,1,PI_F4_TRAIN);

		//cs1
		if(IS_2CS(ddr_type))
		{
		reg_bit_set(CANDS_CTL0_(874)+chn_offset,16,1,PI_F0_TRAIN);
		reg_bit_set(CANDS_CTL0_(874)+chn_offset,24,1,PI_F1_TRAIN);
		reg_bit_set(CANDS_CTL0_(875)+chn_offset, 0,1,PI_F2_TRAIN);
		reg_bit_set(CANDS_CTL0_(875)+chn_offset, 8,1,PI_F3_TRAIN);
		reg_bit_set(CANDS_CTL0_(875)+chn_offset,16,1,PI_F4_TRAIN);
		}
	}
	#endif
}

BOOLEAN is_lp3()
{
	#ifdef DRAM_LPDDR3
	return 1;
	#else
	return 0;
	#endif
	//return DRAM_LPDDR3;
}

void axi_busmon_cfg_set(uint32 clk, uint32 chn_num, uint32 axi_chan, uint32 enable)
{
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    if(enable)
    {
        //enable axi busmonitor
        reg_bit_set((PUB0_APB_BUSMON_CFG+chn_offset),(16+axi_chan),1,enable);
    }
    //axi busmonitor config
    reg_bit_set((PUB0_AXI_BUSMON_CHN_CFG(axi_chan)+chn_offset),0,1,enable);
}

void dfs_axi_busmon_chn10_cfg(uint32 clk, uint32 chn_num, uint32 enable)
{
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    if(enable)
    {
        //enable axi busmonitor
        reg_bit_set((PUB0_APB_BUSMON_CFG+chn_offset),(16+10),1,enable);
    }
     //axi busmonitor config
    reg_bit_set((PUB0_AXI_BUSMON_CHN10_CFG+chn_offset),0,1,enable);
}


#ifdef DRAM_LPDDR3
void dfs_axi_busmon_cfg(uint32 clk)
{
    uint32 axi_chan=0;
    uint32 chn_num=0;
    for(axi_chan=0; axi_chan<10; axi_chan++)
    {
        axi_busmon_cfg_set(clk, chn_num, axi_chan, 1);
    }
    dfs_axi_busmon_chn10_cfg(clk, chn_num, 1);
}
#endif
#ifdef DRAM_LPDDR4
void dfs_axi_busmon_cfg(uint32 clk)
{
    uint32 axi_chan=0;
    uint32 chn_num=0;
    for(chn_num=0; chn_num<2; chn_num++)
    {
        for(axi_chan=0; axi_chan<10; axi_chan++)
        {
            axi_busmon_cfg_set(clk, chn_num, axi_chan, 1);
        }
        dfs_axi_busmon_chn10_cfg(clk, chn_num, 1);
    }

}
#endif

#ifdef DDR_AUTO_DETECT
uint32 cands_mrr(DDR_CHANNEL_NUM_E chn_num, uint32 cs_num, uint32 mr_addr)
{
	uint32 reg_val = 0;
	uint32 mrr_completed;
	uint32 timeout;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	reg_bit_set(CANDS_CTL0_(321)+chn_offset,23,1,1);		// 0x30000504 int_ack , clear bit[23] mrr_completed

	reg_val = (1<<16)|((cs_num&0xFF)<<8)|(mr_addr&0xFF);
	REG32(CANDS_CTL0_(163)+chn_offset)= reg_val;	// 0x3000028c read_modereg

	timeout = 0;
	mrr_completed = 0;
	while(mrr_completed == 0)
	{
		reg_val = REG32(CANDS_CTL0_(319)+chn_offset);		// 0x300004fc int_status bit[23] mrr_completed
		mrr_completed = (reg_val>>23)&0x1;
		if(timeout++ > 0x10000)
			return 0;
	}
	reg_bit_set(CANDS_CTL0_(321)+chn_offset,23,1,1);		// 0x30000504 int_ack , clear bit[23] mrr_completed

	reg_val = REG32(CANDS_CTL0_(169)+chn_offset);		// 0x300002a4 peripheral_mrr_data

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

uint32 cands_ddr_auto_detect(DDR_CHANNEL_NUM_E chn_num,BOOLEAN islp3 )
{
	uint32 cs_num,die_num;
	uint32 mem_size_total,mem_size_total_hex;
	uint32 ret;

	cs_num = 1;
	die_num = 0;
	mr8_value_cs0 = cands_mrr(chn_num, 0,8);
	ret = cands_mr8_to_detect_info(mr8_value_cs0,&detect_info_cs0);
	if(ret == FALSE)
	{
		__ddr_print("\n\r ddr auto detect CS0 fail ");
		//__ddr_wdg_reset();
	}
	if(detect_info_cs0.mem_width == 0x16)
	{
		die_num += 2;
		detect_info_cs0.mem_size =  detect_info_cs0.mem_size*2;
		detect_info_cs0.mem_width = 0x32;
	}

	mr8_value_cs1 = cands_mrr(chn_num, 1,8);
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
	}else{
		__ddr_print("\n\r ddr auto detect CS1 fail ");
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

	__ddr_print("\n\r mr8_value_cs0:");
	ddr_print_u32_hex(mr8_value_cs0);
	__ddr_print("\n\r mr8_value_cs1:");
	ddr_print_u32_hex(mr8_value_cs1);
	__ddr_print("\n\r DDR_TYPE_LOCAL:");
	ddr_print_u32_hex(DDR_TYPE_LOCAL);

	return DDR_TYPE_LOCAL;
}

void cands_auto_detect_fix_reg(DDR_CHANNEL_NUM_E chn_num,BOOLEAN islp3,DRAM_TYPE_E ddr_type )
{
	uint32 cs_map = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 slice_num;
	uint32 slice_offset;

	//cs_map, dsiable unused cs
	//#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_CTL0_(312)+chn_offset,24,8,IS_2CS(ddr_type)?3:1);
	//#else
	//reg_bit_set(CANDS_CTL0_(312)+chn_offset,24,8,3);
	//#endif

	//dram_clk_disable, disable unused cs clock
	//reg_bit_set(CANDS_CTL0_(452)+chn_offset,24,8,IS_2CS(ddr_type)?0xfc:0xfe);
	reg_bit_set(CANDS_CTL0_(452)+chn_offset,24,8,0xfc);

	//calvl_cs
	reg_bit_set(CANDS_CTL0_(408)+chn_offset,24,3, 0);

	//calvl_cs_map
	reg_bit_set(CANDS_CTL0_(418)+chn_offset,24,8, IS_2CS(ddr_type)?3:1);

	//rdlvl_cs
	reg_bit_set(CANDS_CTL0_(379)+chn_offset,16,3, 0);
	//rdlvl_cs_map
	reg_bit_set(CANDS_CTL0_(383)+chn_offset,0,8, IS_2CS(ddr_type));

	#ifdef DRAM_LPDDR4
	//zq_cal_latch_map  ??????
	reg_bit_set(CANDS_CTL0_(290)+chn_offset, 8,8, 1);
	reg_bit_set(CANDS_CTL0_(290)+chn_offset,24,8, IS_2CS(ddr_type)?2:0);
	reg_bit_set(CANDS_CTL0_(291)+chn_offset, 8,8, 0);
	reg_bit_set(CANDS_CTL0_(291)+chn_offset,24,8, 0);
	reg_bit_set(CANDS_CTL0_(292)+chn_offset, 8,8, 0);
	reg_bit_set(CANDS_CTL0_(292)+chn_offset,24,8, 0);
	reg_bit_set(CANDS_CTL0_(293)+chn_offset, 8,8, 0);
	reg_bit_set(CANDS_CTL0_(293)+chn_offset,24,8, 0);

	//zq_cal_start_map   ??????
	reg_bit_set(CANDS_CTL0_(290)+chn_offset, 0,8, 1);
	reg_bit_set(CANDS_CTL0_(290)+chn_offset,16,8, IS_2CS(ddr_type)?2:0);
	reg_bit_set(CANDS_CTL0_(291)+chn_offset, 0,8, 0);
	#endif

	cs_map = islp3?(IS_2CS(ddr_type)?3:1):((IS_2CS(ddr_type)?0x33:0x11)&(IS_16BIT(ddr_type)?0xf:0xff));

	//pi_cs_map
	reg_bit_set(CANDS_PI0_(71)+chn_offset,0,8,cs_map);
	//calvl_cs_map
	reg_bit_set(CANDS_PI0_(127)+chn_offset,16,8,cs_map);
	//rdlvl_cs_map
	reg_bit_set(CANDS_PI0_(114)+chn_offset, 0,8, cs_map);
	//wrlvl_cs_map
	reg_bit_set(CANDS_PI0_(94)+chn_offset, 0,8, cs_map);
	//wdqlvl_cs_map
	reg_bit_set(CANDS_PI0_(162)+chn_offset,0,8, cs_map);

	cs_map = islp3?(IS_2CS(ddr_type)):((IS_2CS(ddr_type)?0x33:0x11)&(IS_16BIT(ddr_type)?0xf:0xff));
	slice_num = 0;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,8,3,cs_map); //?????
	slice_num = 1;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,8,3,cs_map); //?????
	slice_num = 2;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,8,3,cs_map); //?????
	slice_num = 3;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,8,3,cs_map); //?????


	cs_map = islp3?(IS_2CS(ddr_type)?3:1):((IS_2CS(ddr_type)?0x33:0x11)&(IS_16BIT(ddr_type)?0xf:0xff));
	//phy_cslvl_cs_map
	reg_bit_set(CANDS_PHY0_(1027)+chn_offset,24,8,cs_map);
	//phy_calvl_cs_map
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_PHY0_(1033)+chn_offset,0,16,cs_map);
	#else
	reg_bit_set(CANDS_PHY0_(1033)+chn_offset,0,16,0x5500);
	#endif

}
#endif

void ddr_lowpower_init(DDR_CHANNEL_NUM_E chn_num,uint32 clk)
{
       volatile uint32 i = 0;
       uint32 chn_offset = (chn_num==0)?0:0x00800000;

       //enable pubx axi channels clock auto gate 
       if(chn_num == 0){
               //REG32(PMU_APB_DDR0_CHN_SLEEP_CTRL0) = 0x7ff;
		#ifdef DRAM_LPDDR3
               reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,21,1,1);
		#else
               reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,21,1,1);
		#endif
               if((200000000!=clk)&&(400000000!=clk))
               {
                    reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,15,1,0);
               }
               reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,16,1,0);
       }
       else{
               //REG32(PMU_APB_DDR1_CHN_SLEEP_CTRL0) = 0x7ff;
		#ifdef DRAM_LPDDR3
               reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,22,1,1);
		#else
               reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,22,1,1);
		#endif
               if((200000000!=clk)&&(400000000!=clk))
               {
                    reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,17,1,0);
               }
               reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,18,1,0);
       }

       //pub0_chnx_lp_ctrl
       for(i = 0; i < 11; i++ )
               REG32(PUB0_APB_PUB_CHN0_LP_CTRL + i*4 + chn_offset) = 0x31;
}
#ifdef DRAM_LPDDR4
void clear_master_dll_value(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 i=0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	for(i=0;i<4;i++)
	{
		reg_bit_set(CANDS_PHY0_(32)+chn_offset+i*0x200,26,1,1);
	}
}
#endif
void ddr_chn_init(DDR_CHANNEL_NUM_E chn_num,BOOLEAN islp3,uint32 ddr_clk,
                  uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	volatile uint32 value = 0;
	volatile uint32 i = 0;
	int min, max;
	int result, len;
	DRAM_TYPE_E ddr_type;

	CANDS_CTL_TIMING_T	*ctl_timing_info	= __get_cands_ctl_timing_info();
	CANDS_PI_TIMING_T	*pi_timing_info		= __get_cands_pi_timing_info();
	CANDS_PHY_TIMING_T	*phy_timing_info	= __get_cands_phy_timing_info();

	CANDS_CTL_PERCHN_QOS_T	*ctl_perchn_qos = __get_cands_ctl_perchn_qos_info();
	CANDS_CTL_ALLCHN_QOS_T	*ctl_allchn_qos = __get_cands_ctl_allchn_qos_info();

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//#ifdef DDR_AUTO_DETECT
	//if(islp3)
	//{
	//	ddr_type = DRAM_LPDDR3_2CS_8G_X32;
	//}else{
	//	ddr_type = DRAM_LPDDR4_2CS_8G_X32;
	//}
	//#else
	ddr_type = (islp3)? DDR_DFTYPE_LP3:DDR_DFTYPE_LP4;
	//#endif

	if(islp3 && (chn_num==1))
		return; //lp3 don't have 2rd channel, return

	//set ddr clk div
	#ifdef DRAM_LPDDR3
	ddr_clk_set(chn_num,156000000,islp3);
	#else
	ddr_clk_set(chn_num,26000000,islp3);
	#endif


	ddr_freq_target_set(ddr_clk);


	//ctl&phy reset
	cands_ctl_phy_reset(chn_num);

	//ctl&pi&phy reg set
	cands_ctl_init(chn_num,ddr_type,ctl_timing_info,ctl_perchn_qos,ctl_allchn_qos,f0,f1,f2,f3,f4);
	cands_pi_init(chn_num,ddr_type,pi_timing_info,f0,f1,f2,f3,f4);
	cands_phy_init(chn_num,ddr_type,phy_timing_info, f0,f1,f2,f3);
	cands_phy_pinmux_init(chn_num, ddr_type);

	//trigger ddr init flow
	ddr_init_trigger(chn_num);

	//polling training done
	polling_pi_training_done(chn_num,islp3);

	//wait ctl training done
	wait_ctl_init_done(chn_num);

        sync_mr12_mr14(chn_num,islp3);
	#ifdef DRAM_LPDDR4
	if(fn_ctl_target==3)
	{
        	f0_master_delay_update(chn_num);
	}
	#endif
	//if lp4 init with fsp, write fsp valid
	//write_fsp_valid(chn_num, ddr_type);
	#ifdef DDR_AUTO_DETECT
	ddr_type = cands_ddr_auto_detect(chn_num,islp3);
	cands_ctl_addrmap_init(chn_num,ddr_type);
	cands_pi_addrmap_init(chn_num, ddr_type);
	cands_auto_detect_fix_reg(chn_num,islp3,ddr_type );
	#endif

#if DO_DFS_INIT
	#ifdef DRAM_LPDDR3
	dfs_reg_cfg(chn_num);
	dfs_dma_cfg(chn_num);

	//dfs to 311mhz
	if(ddr_clk >= 311000000){
	dfs_noinit_tr_dis(chn_num);
	dfs_go(chn_num,1);
	}

	//dfs to 466mhz
	//dfs_noinit_tr_en(chn_num);
	if(ddr_clk >= 466000000){
	dfs_go(chn_num,2);
	}

	//dfs to 933mhz
	if(ddr_clk >= 933000000){
	dfs_noinit_tr_en(chn_num);
	dfs_go(chn_num,3);
	dfs_tr_polling(chn_num);
	dfs_noinit_tr_dis(chn_num);
	}
	#endif
#endif
#ifdef DRAM_LPDDR4
	clear_master_dll_value(chn_num);
#endif
        ddr_lowpower_init(chn_num,ddr_clk);

}

void ddr_mpu_set()
{}

void ddr_pin_preset(BOOLEAN islp3)
{
	if(islp3)
	{
		//set lp3 vref pin
		reg_bit_set(ANA_APB_DPLL0_CFG0, 21, 1, 1);
		reg_bit_set(ANA_APB_DPLL1_CFG0, 21, 1, 0);

	}
	else
	{
		reg_bit_set(ANA_APB_DPLL0_CFG0, 21, 1, 0);
		reg_bit_set(ANA_APB_DPLL1_CFG0, 21, 1, 0);

		//force reset mode
		reg_bit_set(PMU_DUMMY_REG, 30, 2, 3);

	}
}



void prepare_reinit(void)
{
       REG32(DDR0_ACC_RDY) |= (0x1 << 0);
       REG32(DDR1_ACC_RDY) |= (0x1 << 0);

	#ifdef PUB_FORCE_ON
	reg_bit_set(PMU_APB_PD_PUB0_SYS_CFG, 24, 2, 0);
	if((REG32(PMU_DUMMY_REG) & 0xC0000000))
	{
		reg_bit_set(PMU_APB_PD_PUB1_SYS_CFG, 24, 2, 0);
	}
	#else
	reg_bit_set(PMU_APB_PD_PUB0_SYS_CFG, 24, 2, 1);
	if((REG32(PMU_DUMMY_REG) & 0xC0000000))
	{
		reg_bit_set(PMU_APB_PD_PUB1_SYS_CFG, 24, 2, 1);
	}
	#endif
}

void bist_func(uint32 chn_num)
{
	uint32 bist_timeout=0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	REG32(0x30018028+chn_offset) =0x2a;
	REG32(0x300d0000+chn_offset) =0x7b1;
	REG32(0x300d0004+chn_offset) =0x3Fff;
	REG32(0x300d0008+chn_offset) =0x0;
	REG32(0x300d000c+chn_offset) =0x0;
	REG32(0x300d0010+chn_offset) =0xa55aaa55;
	REG32(0x300d0014+chn_offset) =0xffffaa55;
	REG32(0x300d0018+chn_offset) =0x1111aa55;
	REG32(0x300d001c+chn_offset) =0xaaaaaa55;
	REG32(0x300d0020+chn_offset) =0x1234aa55;
	REG32(0x300d0024+chn_offset) =0x0000aa55;
	REG32(0x300d0028+chn_offset) =0x01234567;
	REG32(0x300d002c+chn_offset) =0x89abcdef;

	REG32(0x300d0008+chn_offset) =0x1eff0000;
	REG32(0x300d0004+chn_offset) =0x3Fff;
	REG32(0x300d0000+chn_offset) =0x7b5;
	REG32(0x300d0000+chn_offset) =0x7b3;

	while((REG32(0x300d00b0+chn_offset) & 0x2) != 0x2)
	{
		bist_timeout++;
		if(bist_timeout>=500000000)
		{
			REG32(0x30018028+chn_offset) =0x0;
			REG32(RESET_CNT) += 1;
			__ddr_wdg_reset();
		}
	}

	if((REG32(0x300d00b0+chn_offset) & 0x1) == 0x1)
	{
		REG32(0x30018028+chn_offset) =0x0;
		REG32(RESET_CNT) += 1;
		__ddr_wdg_reset();
	}

	REG32(0x300d0000+chn_offset) =0x7b4;
	REG32(0x30018028+chn_offset) =0x0;

}
#ifdef POWER_TEST
void ddr_self_refresh_clock_stop(uint32 chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 freq_num=(REG32(CANDS_CTL0_(167)+chn_offset)>>8)&0x7;
	uint32 idle_cnt=0;
	reg_bit_set(CANDS_CTL0_(161)+chn_offset,24,8,0x10);
	reg_bit_set(CANDS_CTL0_(161)+chn_offset, 0,3,0x7);
	reg_bit_set(CANDS_CTL0_(162)+chn_offset,16,12,0x10);
	switch(freq_num)
	{
		case 0:idle_cnt=0x4;break;
		case 1:idle_cnt=0x8;break;
		case 2:idle_cnt=0xc;break;
		case 3:idle_cnt=0x18;break;
		default:while(1);
	}
	reg_bit_set(CANDS_CTL0_(162)+chn_offset, 0, 8,idle_cnt);
	reg_bit_set(CANDS_CTL0_(249)+chn_offset, 0, 5,0x10);
	reg_bit_set(CANDS_CTL0_(848)+chn_offset, 8,12,0x10);
	reg_bit_set(CANDS_CTL0_(160)+chn_offset,24, 4,0x4);
	reg_bit_set(CANDS_CTL0_(160)+chn_offset,16, 4,0x4);
}

void ddr_power_test(uint32 state)
{
	uint32 pat_num=0;
	switch(state)
	{
		case 0:					//idle state
			break;
		case 1:					//auto selfrefresj
			ddr_self_refresh_clock_stop(0);
			ddr_self_refresh_clock_stop(1);
			break;
		case 2:					//bist read
			while(1)
			{
				bist_test(BIST_READ,USER_MODE,0x1000,0);
			}
		case 3:					//bist write
			while(1)
			{
				for(pat_num=0;pat_num<8;pat_num++)
				{
					bist_test(BIST_WRITE,SIPI_MODE,0xf00,pat_num);
				}
			}
	}
	while(1);
}
#endif
void sdram_init(uint32 ddr_clk)
{
	uint32 i = 0;
	BOOLEAN islp3 = 0;
	islp3 = is_lp3();

	if(REG32(FIRST_BOOT_FLAG) != 0x89abcdef)
	{
		REG32(FIRST_BOOT_FLAG) = 0x89abcdef;
		REG32(BOOT_CNT) = 0;
		REG32(RESET_CNT) = 0;
	}
	ddr_mpu_set();
	ddr_pin_preset(islp3);
	ddr_chn_init(0,islp3,ddr_clk, F0_FREQ, F1_FREQ, F2_FREQ, F3_FREQ, F4_FREQ);
	ddr_chn_init(1,islp3,ddr_clk, F0_FREQ, F1_FREQ, F2_FREQ, F3_FREQ, F4_FREQ);
	#ifdef POWER_TEST
	ddr_power_test(3);
	#endif
	#ifdef DRAM_LPDDR4
	bist_func(0);
	bist_func(1);
	#endif
	REG32(BOOT_CNT) += 1;
	prepare_reinit();
	dfs_axi_busmon_cfg(ddr_clk);
}

/*

void test_entry ( void )
{
	volatile int i = 0;

	i=i+1;
	sdram_init(DDR_FREQ);
	while(1);
}
*/

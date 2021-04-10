
#include "../../init/v0_2/ddr_init.h"
#include "../../timing/v0_2/ddr_timing.h"
#include "../../qos/v0_2/ddr_qos.h"


static uint32 aon_ver_id;

#ifdef  CODE_SIZE_OPTIMIZE
void * temp_fn[5] = {0};
#else
uint32 temp_fn[5] = {0};
#endif
#ifdef DDR_IP_CONFIG_FILE
#define PI_FREQ_MAP 0x1E
#define INIT_FREQ_N 3
uint32 pi_fn_div[5] = {0x40,0x57,0x4b,0x47,0x43};
#else
uint32 pi_fn_div[5] = {0};
#endif

//#define PHY_PLL_BYPASS

#define MAX_SECTION_NUM	8

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

void ddr_info_init(chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x100;

	ddr_info_s = (DDR_INFO_T *)(DDR_SIZE_TO_UBOOT+chn_offset);

	return;
}

#if DO_DFS_INIT
void dfs_reg_cfg(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//read current status form AON_CFG_CFG
	//uint32 clk_div_old = 0;
	//uint32 xtal_26m_old = 0;
	uint32 clk_sel_current;
	uint32 clk_dmc0_sel;
	uint32 clk_dmc0_2x_div;
	uint32 clk_dmc0_1x_div;
	uint32 pub_dfs_sw_ratio;

	//clk_div_old = (REG32(AON_APB_CGM_CFG)>>(8+(chn_num<<4)))&0x3f;
	//xtal_26m_old = (REG32(AON_APB_CGM_CFG)>>(14+(chn_num<<4)))&0x1;
	clk_sel_current = (REG32(AON_APB_CGM_CFG)>>(8+(chn_num<<4)))&0x7f;
	clk_dmc0_sel = clk_sel_current & 0x3;
	clk_dmc0_2x_div = (clk_sel_current>>3) & 0xf;
	clk_dmc0_1x_div = (clk_sel_current>>2) & 0x1;

	pub_dfs_sw_ratio = (clk_dmc0_sel<<0) | (clk_dmc0_1x_div<<2) | (clk_dmc0_2x_div<<3);

	//PWRUP_SREFRESH_EXIT
	reg_bit_set(CANDS_CTL0_(102)+chn_offset, 16, 1, 1);

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
	REG32(PUB0_SOFT_DFS_CTRL+chn_offset) = (pub_dfs_sw_ratio<<13)|(pub_dfs_sw_ratio<<6);
	//pub_dfs_sw_switch_period     used to controller the time between dfs_fc_req and dfs_fc_ack
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 23, 8, 0x30);
	#endif

	if(chn_num == 0)
	{
		//set pub fc ctrl pub0_dfs_switch_wait_time   how long ctrl clk could not be gated
		reg_bit_set(AON_APB_PUB_FC_CTRL,0,8,0xff);
		reg_bit_set(AON_APB_PUB_FC_CTRL,8,2,0x3);
		//config clk_dmc_sel for dmc_clk_hw_en
		reg_bit_set(AON_APB_EMC_CKG_SEL,0,7,pub_dfs_sw_ratio);

		//set emc_ckg_sel_default_pubx_exte
		//reg_bit_set(AON_APB_PUB_CTRL,0,1,xtal_26m_old);

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
		reg_bit_set(AON_APB_EMC_CKG_SEL,7,7,pub_dfs_sw_ratio);

		//set emc_ckg_sel_default_pubx_exte
		//reg_bit_set(AON_APB_PUB_CTRL,1,1,xtal_26m_old);

		//emc_ckg_sel_load
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,20, 1, 1);

		//clk_dmcx_sel_hw_en, 0:by hw 1:by sw
		reg_bit_set(AON_APB_CGM_CFG, 23, 1, 1);

	}
}
#ifdef DRAM_LPDDR3
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
#endif
void dfs_noinit_tr_en(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	reg_bit_set(CANDS_PI0_(1)+chn_offset, 0,  1, 1); //pi_normal_lvl_seq
	reg_bit_set(CANDS_PI0_(1)+chn_offset, 8,  1, 1); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(77)+chn_offset, 8,  2, 0x2); //pi_wrlvl_noinit_en
	reg_bit_set(CANDS_PI0_(123)+chn_offset, 8,  2, 0x2); //pi_calvl_noinit_en
	reg_bit_set(CANDS_PI0_(99)+chn_offset, 16,  2, 0x2); //pi_rdlvl_noinit_en
	reg_bit_set(CANDS_PI0_(99)+chn_offset, 24,  2, 0x2); //pi_rdlvl_gate_noinit_en

	#ifdef DRAM_LPDDR4
	reg_bit_set(CANDS_PI0_(155)+chn_offset, 16,  2, 0x2); //pi_wdqlvl_noinit_en
	reg_bit_set(CANDS_PI0_(129)+chn_offset, 24,  1, 0x1); //pi_ca_train_vref_en
	reg_bit_set(CANDS_PI0_(147)+chn_offset, 24,  1, 0x1); //pi_wdqlvl_vref_en
	#endif

	reg_bit_set(CANDS_PI0_(214)+chn_offset, 0,  24, 0x3ffff); //pi_init_status_clean
}


void dfs_noinit_tr_dis(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	reg_bit_set(CANDS_PI0_(1)+chn_offset, 0,  1, 0); //pi_normal_lvl_seq
	reg_bit_set(CANDS_PI0_(1)+chn_offset, 8,  1, 0); //pi_init_lvl_en
	reg_bit_set(CANDS_PI0_(77)+chn_offset, 8,  2, 0); //pi_wrlvl_noinit_en
	reg_bit_set(CANDS_PI0_(123)+chn_offset, 8,  2, 0); //pi_calvl_noinit_en
	reg_bit_set(CANDS_PI0_(99)+chn_offset, 16,  2, 0); //pi_rdlvl_noinit_en
	reg_bit_set(CANDS_PI0_(99)+chn_offset, 24,  2, 0); //pi_rdlvl_gate_noinit_en
	#ifdef DRAM_LPDDR4
	reg_bit_set(CANDS_PI0_(155)+chn_offset, 16,  2, 0); //pi_wdqlvl_noinit_en
	reg_bit_set(CANDS_PI0_(129)+chn_offset, 24,  1, 0); //pi_ca_train_vref_en
	reg_bit_set(CANDS_PI0_(147)+chn_offset, 24,  1, 0); //pi_wdqlvl_vref_en
	#endif
}
void dfs_tr_polling(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 pi_tr_done=0;
	volatile uint32 i=0;

	do{
		i++;
		pi_tr_done = (REG32(CANDS_PI0_(213)+chn_offset)&0x2000);
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

#ifdef CONFIG_DFS_TIMING
uint32 time_consume1[4][4] = {0};
uint32 time_consume2[4][4] = {0};

void bist_func_all_start(uint32 chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 bist_base_offset;
	uint32 i;
	uint32 bist_adr_base;

	REG32(0xc0018028+chn_offset) =0x2a;

	for(i=0;i<3;i++) {
		bist_base_offset = i*0x4000;
		bist_adr_base = i*0x20000000;
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021b1;
		REG32(0xc00d0004+chn_offset+bist_base_offset) =0x1fFf;
		REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
		REG32(0xc00d000c+chn_offset+bist_base_offset) =0x0;
		REG32(0xc00d0010+chn_offset+bist_base_offset) =0x0ff0c3a5;
		REG32(0xc00d0014+chn_offset+bist_base_offset) =0xffffaa55;
		REG32(0xc00d0018+chn_offset+bist_base_offset) =0x1111aa55;
		REG32(0xc00d001c+chn_offset+bist_base_offset) =0xaaaaaa55;
		REG32(0xc00d0020+chn_offset+bist_base_offset) =0x1234aa55;
		REG32(0xc00d0024+chn_offset+bist_base_offset) =0x0000aa55;
		REG32(0xc00d0028+chn_offset+bist_base_offset) =0x00000000;
		REG32(0xc00d002c+chn_offset+bist_base_offset) =0x00000000;

		REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
		REG32(0xc00d0004+chn_offset+bist_base_offset) =0x1fFf;
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021b5;
	}

	for(i=0;i<3;i++) {
		bist_base_offset = i*0x4000;
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021b3;
	}
}

void bist_func_all_wait_done(uint32 chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	while((REG32(0xc00d00b0+chn_offset) & 0x3) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x4000) & 0x3) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x8000) & 0x3) != 0x2);

	REG32(0xc0018028+chn_offset) =0x0;
}

uint32 dfs_timing(DDR_CHANNEL_NUM_E chn_num, uint32 fn)
{
	uint32 ratio;
	uint32 scan_ratio;
	uint32 pub_status;
	uint32 time_start;
	uint32 time_end;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	volatile uint32 i = 0;

	#ifdef DRAM_LPDDR3
	switch(fn)
	{
		case 0: ratio = 0x1f; scan_ratio = 0; break;
		case 1: ratio = 0x23;  scan_ratio = 0; break;
		case 2: ratio = 0x13; scan_ratio = 0; break;
		case 3: ratio = 0x07; scan_ratio = 0; break;
		default:while(1);
	}
	#else
	switch(fn)
	{
		case 0: ratio = 0x2f; scan_ratio = 0; break;
		case 1: ratio = 0x17; scan_ratio = 0; break;
		case 2: ratio = 0x13; scan_ratio = 0; break;
		case 3: ratio = 0x07; scan_ratio = 0; break;
		default:while(1);
	}
	#endif

	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 0, 1, 1); //pub_dfs_sw_enable
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 1, 1, 0); //pub_dfs_sw_req
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 4, 2, fn); //pub_dfs_sw_frq_sel
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 6, 6, ratio); //pub_dfs_sw_ratio
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 21,1, 0); //scan_dfs_sw_ratio_default
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 22,1, scan_ratio); //scan_pub_dfs_sw_ratio
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 23,8, 0x30); //pub_dfs_sw_switch_period

	time_start = REG32(0xE4050058);
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 1,1, 1); //pub_dfs_sw_req--trigger

	//check whether mc has entered into selfrefresh or not
	while(((REG32(PUB0_SOFT_DFS_CTRL+chn_offset)&0x08) != 0x00) ||
	      ((REG32(PUB0_SOFT_DFS_CTRL+chn_offset)&0x04) != 0x04))
	{
		i++;
		//wait_us(10);
		if(i == 1000000)
		{
			__ddr_print("\r\ndo ddr init dfs hung, reboot......");
			__ddr_wdg_reset();
			while(1);
		}
	}
	time_end = REG32(0xE4050058);

	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 1,1, 0x0); //pub_dfs_sw_req--trigger
	pub_status = REG32(PUB0_DFS_STATUS+chn_offset);
	if (((pub_status >>5)&0x3) != fn) {
		__ddr_print("\r\nThe result fn is not equal to expected vale, reboot......");
		while(1);
	}

	if (((pub_status >>7) & 0x7f) != ratio) {
		__ddr_print("\r\nThe result ratio is not equal to expected vale, reboot......");
		while(1);
	}
	return time_start - time_end;
}

void dfs_timing_test(uint32 chn_num)
{
	uint32 i = 0;
	uint32 time = 0;
	uint32 time_consume = 0;
	uint32 fn_last = 0;
	uint32 fn = 0;

	reg_bit_set(0xE42E0000, 9, 4, 0xF);
	reg_bit_set(0xE4050050, 0, 2, 0x3);
	REG32(0xE4050040) = 0xFFFFFFFF;

	// enable 26M timer
	reg_bit_set(0xE42E0138, 19, 1, 0x1);

	dfs_reg_cfg(chn_num);
	for(i = 0; i < 2999; i++) {
		dfs_noinit_tr_en(chn_num);
		time = __raw_readl(0xE4050058);
		fn = time % 4;
		time_consume = dfs_timing(chn_num, fn);
		//__ddr_print("\nChange freq from ");
		//printd(fn_last);
		//__ddr_print(" to ");
		//printd(fn);
		//__ddr_print(", consume time:  ");
		//printd(time_end - time_start);
		if (time_consume > time_consume1[fn_last][fn])
			time_consume1[fn_last][fn] = time_consume;
		fn_last = fn;
		dfs_tr_polling(chn_num);
		dfs_noinit_tr_dis(chn_num);
		bist_func_all_start(chn_num);
		bist_func_all_wait_done(chn_num);
	}

	for(i = 0; i < 2999; i++) {
		bist_func_all_start(chn_num);
		dfs_noinit_tr_en(chn_num);
		time = __raw_readl(0xe4050058);
		fn = time % 4;
		time_consume = dfs_timing(chn_num, fn);
		if (time_consume > time_consume2[fn_last][fn])
			time_consume2[fn_last][fn] = time_consume;
		fn_last = fn;
		dfs_tr_polling(chn_num);
		dfs_noinit_tr_dis(chn_num);
		bist_func_all_wait_done(chn_num);
	}
}
#endif

void dfs_go(DDR_CHANNEL_NUM_E chn_num, uint32 fn)
{
	uint32 ratio;
	uint32 scan_ratio;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	volatile uint32 i = 0;

	#ifdef DRAM_LPDDR3
	switch(fn)
	{
		case 0: ratio = 0x1f; scan_ratio = 0; break;
		case 1: ratio = 0x23;  scan_ratio = 0; break;
		case 2: ratio = 0x13; scan_ratio = 0; break;
		case 3: ratio = 0x07; scan_ratio = 0; break;
		default:while(1);
	}
	#else
	switch(fn)
	{
		case 0: ratio = 0x2f; scan_ratio = 0; break;
		case 1: ratio = 0x17; scan_ratio = 0; break;
		case 2: ratio = 0x13; scan_ratio = 0; break;
		case 3: ratio = 0x07; scan_ratio = 0; break;
		default:while(1);
	}
	#endif

	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 0, 1, 1); //pub_dfs_sw_enable
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 1, 1, 0); //pub_dfs_sw_req
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 4, 2, fn); //pub_dfs_sw_frq_sel
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 6, 6, ratio); //pub_dfs_sw_ratio
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 21,1, 0); //scan_dfs_sw_ratio_default
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 22,1, scan_ratio); //scan_pub_dfs_sw_ratio
	reg_bit_set(PUB0_SOFT_DFS_CTRL+chn_offset, 23,8, 0x30); //pub_dfs_sw_switch_period

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

void cands_ctl_phy_release(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 i = 0;

	if(chn_num == DDR_CHANNEL_0)
	{
		//clear ctl & phy & ahb reset
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 3, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 6, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 5, 1, 0);
		wait_us(10);
                //umctl auto gate en
                reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 2, 1, 1);
                //phy auto gate en
                reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 4, 1, 1);
		//ctl & phy en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 0, 2, 0);
		wait_us(10);
	}
	else
	{
		//clear ctl & phy & ahb reset
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 10, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 13, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 12, 1, 0);
		wait_us(10);
                //umctl auto gate en
                reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 9, 1, 1);
                //phy auto gate en
                reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 11, 1, 1);
		//ctl & phy en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 7, 2, 0);
		wait_us(10);
	}
	return;
}

void cands_ctl_addrmap_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	volatile uint32 bank_diff = 0;
	volatile uint32 row_diff = 0;
	volatile uint32 col_diff = 0;
	volatile uint32 sec_num = 0;

	if(IS_LPDDR3(ddr_type))
	{
		switch(ddr_type)
		{
			case DRAM_LPDDR3_1CS_4G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x1fffffff;
				break;
			case DRAM_LPDDR3_2CS_8G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fffffff;
			    	break;

                        case DRAM_LPDDR3_1CS_6G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x2fffffff;
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
				ddr_info_s->sec_info[1].end_addr_l = 0x6fffffff;
				break;
			case DRAM_LPDDR3_1CS_8G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fffffff;
				break;
                        case DRAM_LPDDR3_2CS_16G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fffffff;
			    	break;

			case DRAM_LPDDR3_1CS_12G_X32:
				row_diff = 1; col_diff = 1; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x5fffffff;
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
				ddr_info_s->sec_info[2].end_addr_l = 0x1fffffff;
				break;
			case DRAM_LPDDR3_1CS_16G_X32:
				row_diff = 1; col_diff = 1; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fffffff;
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
				ddr_info_s->sec_info[1].end_addr_l = 0x3fffffff;
				break;
			case DRAM_LPDDR3_2CS_24G_X32_X16X4:
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
				ddr_info_s->sec_info[2].end_addr_l = 0x1fffffff;
			   	break;

			case DRAM_LPDDR3_1CS_8G_X16X2:
				row_diff = 2; col_diff = 1; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fffffff;
				break;
			case DRAM_LPDDR3_2CS_16G_X32_X16X4:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fffffff;
                                break;
			default:   while(1); //invalid density
		}
	}
	else if(IS_LPDDR4(ddr_type)) //lpddr4
	{
            if(0==chn_num)
            {
		switch(ddr_type)
		{
	   		case DRAM_LPDDR4_1CS_4G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x1fffffff;
				break;
		  	case DRAM_LPDDR4_2CS_8G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fffffff;
				break;

			case DRAM_LPDDR4_1CS_6G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x2fffffff;
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
				ddr_info_s->sec_info[1].end_addr_l = 0x6fffffff;
				break;
			case DRAM_LPDDR4_1CS_8G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fffffff;
				break;
			case DRAM_LPDDR4_2CS_16G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fffffff;
				break;

			case DRAM_LPDDR4_1CS_12G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x5fffffff;
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
				ddr_info_s->sec_info[2].end_addr_l = 0x1fffffff;
				break;
			case DRAM_LPDDR4_1CS_6G_X16:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x2fffffff;
				break;
			case DRAM_LPDDR4_1CS_16G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 0;
				ddr_info_s->sec_info[0].start_addr_l = 0;
				ddr_info_s->sec_info[0].end_addr_h = 0;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fffffff;
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
				ddr_info_s->sec_info[1].end_addr_l = 0x3fffffff;
				break;
			default: while(1); //invalid density
                }
           }
           else
           {
		switch(ddr_type)
		{
	   		case DRAM_LPDDR4_1CS_4G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0x5fffffff;
				break;
		  	case DRAM_LPDDR4_2CS_8G_X32:
				row_diff = 2; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fffffff;
				break;

			case DRAM_LPDDR4_1CS_6G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0x6fffffff;
				break;
			case DRAM_LPDDR4_2CS_12G_X32:
				row_diff = 1; col_diff = 2; sec_num = 2;
				ddr_info_s->section_num = 2;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0x6fffffff;

				ddr_info_s->sec_info[1].start_addr_h = 1;
				ddr_info_s->sec_info[1].start_addr_l = 0x80000000;
				ddr_info_s->sec_info[1].end_addr_h = 1;
				ddr_info_s->sec_info[1].end_addr_l = 0xAfffffff;
				break;
			case DRAM_LPDDR4_1CS_8G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0x7fffffff;
				break;
			case DRAM_LPDDR4_2CS_16G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0xBfffffff;
				break;

			case DRAM_LPDDR4_1CS_12G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0x9fffffff;
				break;
			case DRAM_LPDDR4_2CS_24G_X32:
				row_diff = 1; col_diff = 2; sec_num = 2;
				ddr_info_s->section_num = 2;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0x9fffffff;

				ddr_info_s->sec_info[1].start_addr_h = 1;
				ddr_info_s->sec_info[1].start_addr_l = 0xA0000000;
				ddr_info_s->sec_info[1].end_addr_h = 2;
				ddr_info_s->sec_info[1].end_addr_l = 0x1fffffff;
				break;
			case DRAM_LPDDR4_1CS_6G_X16:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0x6fffffff;
				break;
			case DRAM_LPDDR4_1CS_16G_X32:
				row_diff = 1; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 1;
				ddr_info_s->sec_info[0].end_addr_l = 0xBfffffff;
				break;
			case DRAM_LPDDR4_2CS_32G_X32:
				row_diff = 0; col_diff = 2; sec_num = 1;
				ddr_info_s->section_num = 1;
				ddr_info_s->sec_info[0].start_addr_h = 1;
				ddr_info_s->sec_info[0].start_addr_l = 0x40000000;
				ddr_info_s->sec_info[0].end_addr_h = 2;
				ddr_info_s->sec_info[0].end_addr_l = 0x3fffffff;
				break;
			default: while(1); //invalid density
                }
	    }
	}

	reg_bit_set(CANDS_CTL0_(279)+chn_offset,16,2,bank_diff);
	reg_bit_set(CANDS_CTL0_(279)+chn_offset,24,3,row_diff);
	reg_bit_set(CANDS_CTL0_(280)+chn_offset,0,4,col_diff);

}

void cands_pi_addrmap_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type) ///  ????????
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	volatile uint32 bank_diff = 0;
	volatile uint32 row_diff = 0;
	volatile uint32 col_diff = 0;

	volatile uint32 i = 0;


	if(IS_LPDDR3(ddr_type))
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
			case DRAM_LPDDR3_2CS_24G_X32_X16X4:
				row_diff = 1; col_diff = 1;
			   	break;
                        case DRAM_LPDDR3_1CS_8G_X16X2:
			case DRAM_LPDDR3_2CS_16G_X32_X16X4:
				row_diff = 2; col_diff = 2;break;
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

	reg_bit_set(CANDS_PI0_(187)+chn_offset,8,2,bank_diff);
	reg_bit_set(CANDS_PI0_(187)+chn_offset,16,3,row_diff);
	reg_bit_set(CANDS_PI0_(248)+chn_offset, 0,4,col_diff);

}

#ifndef DDR_IP_CONFIG_FILE
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

	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T **)temp_fn;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

	//cke_inactive
	__raw_writel(CANDS_CTL0_(36)+chn_offset, f0_timing->CKE_INACTIVE);
	//cke_delay
	reg_bit_set(CANDS_CTL0_(103)+chn_offset,8,3, f0_timing->CKE_DELAY);
	//CKSRE
	reg_bit_set(CANDS_CTL0_(138)+chn_offset,8,8, f0_timing->CKSRE);
	reg_bit_set(CANDS_CTL0_(138)+chn_offset,24,8, f1_timing->CKSRE);
	reg_bit_set(CANDS_CTL0_(139)+chn_offset,8,8, f2_timing->CKSRE);
	reg_bit_set(CANDS_CTL0_(139)+chn_offset,24,8, f3_timing->CKSRE);
	reg_bit_set(CANDS_CTL0_(140)+chn_offset,8,8, f4_timing->CKSRE);
	//CKSRX
	reg_bit_set(CANDS_CTL0_(138)+chn_offset,16,8, f0_timing->CKSRX);
	reg_bit_set(CANDS_CTL0_(139)+chn_offset,0,8, f1_timing->CKSRX);
	reg_bit_set(CANDS_CTL0_(139)+chn_offset,16,8, f2_timing->CKSRX);
	reg_bit_set(CANDS_CTL0_(140)+chn_offset,0,8, f3_timing->CKSRX);
	reg_bit_set(CANDS_CTL0_(140)+chn_offset,16,8, f4_timing->CKSRX);
	//OTHER
	reg_bit_set(CANDS_CTL0_(39)+chn_offset,16,3, f0_timing->TBST_INT_INTERVAL);
	reg_bit_set(CANDS_CTL0_(64)+chn_offset, 8,5, f0_timing->TCACKEH);
	reg_bit_set(CANDS_CTL0_(63)+chn_offset, 0,5, f0_timing->TCACKEL);
	reg_bit_set(CANDS_CTL0_(63)+chn_offset,8,10,f0_timing->TCAENT);
	reg_bit_set(CANDS_CTL0_(64)+chn_offset,0,5, f0_timing->TCAEXT);
	reg_bit_set(CANDS_CTL0_(63)+chn_offset,24,6, f0_timing->TCAMRD);
	reg_bit_set(CANDS_CTL0_(39)+chn_offset,24,5, f0_timing->TCCD);
	reg_bit_set(CANDS_CTL0_(40)+chn_offset, 0,6, f0_timing->TCCDMW);
	//reg_bit_set(CANDS_CTL0_(20)+chn_offset,16,3, 3); RESERVED ON WHALE2
    //TCKCKEL
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(93+2*i)+chn_offset,0,4,timing[i]->TCKCKEL);
		reg_bit_set(CANDS_CTL0_(50+2*i)+chn_offset, 24,4,timing[i]->TCKE);
		reg_bit_set(CANDS_CTL0_(92+2*i)+chn_offset, 24,4,timing[i]->TCKEHCMD);
		reg_bit_set(CANDS_CTL0_(92+2*i)+chn_offset, 16,4,timing[i]->TCKELCMD);
		reg_bit_set(CANDS_CTL0_(93+2*i)+chn_offset,24,4,timing[i]->TCKELPD);
		reg_bit_set(CANDS_CTL0_(51+2*i)+chn_offset, 0,8,timing[i]->TCKESR);
	}
    //TCKEHCS
	reg_bit_set(CANDS_CTL0_(81)+chn_offset, 24,4,f0_timing->TCKEHCS);
	reg_bit_set(CANDS_CTL0_(83)+chn_offset, 0,4,f1_timing->TCKEHCS);
	reg_bit_set(CANDS_CTL0_(84)+chn_offset, 8,4,f2_timing->TCKEHCS);
	reg_bit_set(CANDS_CTL0_(85)+chn_offset, 16,4,f3_timing->TCKEHCS);//b68
	reg_bit_set(CANDS_CTL0_(86)+chn_offset, 24,4,f4_timing->TCKEHCS);
    //TCKELCS
	reg_bit_set(CANDS_CTL0_(81)+chn_offset,16,4,f0_timing->TCKELCS);
	reg_bit_set(CANDS_CTL0_(82)+chn_offset,24,4,f1_timing->TCKELCS);
	reg_bit_set(CANDS_CTL0_(84)+chn_offset,0,4,f2_timing->TCKELCS);
	reg_bit_set(CANDS_CTL0_(85)+chn_offset,8,4,f3_timing->TCKELCS);//b68
	reg_bit_set(CANDS_CTL0_(86)+chn_offset,16,4,f4_timing->TCKELCS);

    //TCKFSPE
	reg_bit_set(CANDS_CTL0_(190)+chn_offset, 0,5,f0_timing->TCKFSPE);
	reg_bit_set(CANDS_CTL0_(192)+chn_offset,16,5,f1_timing->TCKFSPE);
	reg_bit_set(CANDS_CTL0_(195)+chn_offset, 0,5,f2_timing->TCKFSPE);
	reg_bit_set(CANDS_CTL0_(197)+chn_offset,16,5,f3_timing->TCKFSPE);//d7c
	reg_bit_set(CANDS_CTL0_(200)+chn_offset, 0,5,f4_timing->TCKFSPE);
    //TCKFSPX
	reg_bit_set(CANDS_CTL0_(190)+chn_offset, 8,5,f0_timing->TCKFSPX);
	reg_bit_set(CANDS_CTL0_(192)+chn_offset,24,5,f1_timing->TCKFSPX);
	reg_bit_set(CANDS_CTL0_(195)+chn_offset, 8,5,f2_timing->TCKFSPX);
	reg_bit_set(CANDS_CTL0_(197)+chn_offset,24,5,f3_timing->TCKFSPX);//d7c
	reg_bit_set(CANDS_CTL0_(200)+chn_offset, 8,5,f4_timing->TCKFSPX);
    //TCMDCKE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(94+2*i)+chn_offset, 8,4,timing[i]->TCMDCKE);
		reg_bit_set(CANDS_CTL0_(94+2*i)+chn_offset,0,4,timing[i]->TCSCKEH);
		reg_bit_set(CANDS_CTL0_(93+2*i)+chn_offset,16,3,timing[i]->TESCKE);
	}

    //TCSCKE
	reg_bit_set(CANDS_CTL0_(81)+chn_offset,8,4,f0_timing->TCSCKE);
	reg_bit_set(CANDS_CTL0_(82)+chn_offset,16,4,f1_timing->TCSCKE);
	reg_bit_set(CANDS_CTL0_(83)+chn_offset,24,4,f2_timing->TCSCKE);
	reg_bit_set(CANDS_CTL0_(85)+chn_offset,0,4,f3_timing->TCSCKE);//b6c 0x0
	reg_bit_set(CANDS_CTL0_(86)+chn_offset,8,4,f4_timing->TCSCKE);
    //TDAL
	reg_bit_set(CANDS_CTL0_(66)+chn_offset, 16,8,f0_timing->TDAL);
	reg_bit_set(CANDS_CTL0_(66)+chn_offset, 24,8,f1_timing->TDAL);
	reg_bit_set(CANDS_CTL0_(67)+chn_offset, 0,8,f2_timing->TDAL);
	reg_bit_set(CANDS_CTL0_(67)+chn_offset, 8,8,f3_timing->TDAL);
	reg_bit_set(CANDS_CTL0_(67)+chn_offset, 16,8,f4_timing->TDAL);
    //TDQSCK_MAX
	reg_bit_set(CANDS_CTL0_(328)+chn_offset, 8,4,f0_timing->TDQSCK_MAX);
	reg_bit_set(CANDS_CTL0_(328)+chn_offset, 24,4,f1_timing->TDQSCK_MAX);
	reg_bit_set(CANDS_CTL0_(329)+chn_offset, 8,4,f2_timing->TDQSCK_MAX);
	reg_bit_set(CANDS_CTL0_(329)+chn_offset, 24,4,f3_timing->TDQSCK_MAX);
	reg_bit_set(CANDS_CTL0_(330)+chn_offset, 8,4,f4_timing->TDQSCK_MAX);
    //TDQSCK_MIN
	reg_bit_set(CANDS_CTL0_(328)+chn_offset, 16,2,f0_timing->TDQSCK_MIN);
	reg_bit_set(CANDS_CTL0_(329)+chn_offset, 0,2,f1_timing->TDQSCK_MIN);
	reg_bit_set(CANDS_CTL0_(329)+chn_offset, 16,2,f2_timing->TDQSCK_MIN);
	reg_bit_set(CANDS_CTL0_(330)+chn_offset, 0,2,f3_timing->TDQSCK_MIN);
	reg_bit_set(CANDS_CTL0_(330)+chn_offset, 16,2,f4_timing->TDQSCK_MIN);
	//TFAW
	reg_bit_set(CANDS_CTL0_(41)+chn_offset,16,8,f0_timing->TFAW);
	reg_bit_set(CANDS_CTL0_(43)+chn_offset,8,8,f1_timing->TFAW);
	reg_bit_set(CANDS_CTL0_(45)+chn_offset,0,8,f2_timing->TFAW);
	reg_bit_set(CANDS_CTL0_(46)+chn_offset,24,8,f3_timing->TFAW);
	reg_bit_set(CANDS_CTL0_(48)+chn_offset,16,8,f4_timing->TFAW);
    //TFC
	reg_bit_set(CANDS_CTL0_(189)+chn_offset,16,10,f0_timing->TFC);
	reg_bit_set(CANDS_CTL0_(192)+chn_offset, 0,10,f1_timing->TFC);
	reg_bit_set(CANDS_CTL0_(194)+chn_offset,16,10,f2_timing->TFC);
	reg_bit_set(CANDS_CTL0_(197)+chn_offset, 0,10,f3_timing->TFC);
	reg_bit_set(CANDS_CTL0_(199)+chn_offset,16,10,f4_timing->TFC);

	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(12+4*i)+chn_offset, 0,24,timing[i]->TINIT3);
		reg_bit_set(CANDS_CTL0_(13+4*i)+chn_offset, 0,24,timing[i]->TINIT4);
		reg_bit_set(CANDS_CTL0_(14+4*i)+chn_offset, 0,24,timing[i]->TINIT5);
	}

	//TINIT
	reg_bit_set(CANDS_CTL0_(11)+chn_offset, 8,24,f0_timing->TINIT);
	reg_bit_set(CANDS_CTL0_(15)+chn_offset, 0,24,f1_timing->TINIT);
	reg_bit_set(CANDS_CTL0_(19)+chn_offset, 0,24,f2_timing->TINIT);
	reg_bit_set(CANDS_CTL0_(23)+chn_offset, 0,24,f3_timing->TINIT);//bac 0xa0
	reg_bit_set(CANDS_CTL0_(27)+chn_offset, 0,24,f4_timing->TINIT);
    //TMOD
	reg_bit_set(CANDS_CTL0_(49)+chn_offset,16, 8,f0_timing->TMOD);
	reg_bit_set(CANDS_CTL0_(51)+chn_offset,24, 8,f1_timing->TMOD);
	reg_bit_set(CANDS_CTL0_(53)+chn_offset,24, 8,f2_timing->TMOD);
	reg_bit_set(CANDS_CTL0_(55)+chn_offset,24, 8,f3_timing->TMOD);//ba0 0xa
	reg_bit_set(CANDS_CTL0_(57)+chn_offset,24, 8,f4_timing->TMOD);
	//TMRD
	reg_bit_set(CANDS_CTL0_(49)+chn_offset,8, 8,f0_timing->TMRD);
	reg_bit_set(CANDS_CTL0_(51)+chn_offset,16, 8,f1_timing->TMRD);
	reg_bit_set(CANDS_CTL0_(53)+chn_offset,16, 8,f2_timing->TMRD);
	reg_bit_set(CANDS_CTL0_(55)+chn_offset,16, 8,f3_timing->TMRD);
	reg_bit_set(CANDS_CTL0_(57)+chn_offset,16, 8,f4_timing->TMRD);
    //TMRR
	reg_bit_set(CANDS_CTL0_(62)+chn_offset, 24, 4,f0_timing->TMRR);

	//TMRRI
	reg_bit_set(CANDS_CTL0_(80)+chn_offset, 0, 8,f0_timing->TMRRI);
	reg_bit_set(CANDS_CTL0_(80)+chn_offset, 8, 8,f1_timing->TMRRI);
	reg_bit_set(CANDS_CTL0_(80)+chn_offset, 16, 8,f2_timing->TMRRI);
	reg_bit_set(CANDS_CTL0_(80)+chn_offset, 24, 8,f3_timing->TMRRI);
	reg_bit_set(CANDS_CTL0_(81)+chn_offset, 0, 8,f4_timing->TMRRI);
	//TMRWCKEL
	reg_bit_set(CANDS_CTL0_(82)+chn_offset,0, 5,f0_timing->TMRWCKEL);
	reg_bit_set(CANDS_CTL0_(83)+chn_offset,8, 5,f1_timing->TMRWCKEL);
	reg_bit_set(CANDS_CTL0_(84)+chn_offset,16, 5,f2_timing->TMRWCKEL);
	reg_bit_set(CANDS_CTL0_(85)+chn_offset,24, 5,f3_timing->TMRWCKEL);
	reg_bit_set(CANDS_CTL0_(87)+chn_offset,0, 5,f4_timing->TMRWCKEL);
	//TMRZ
	reg_bit_set(CANDS_CTL0_(64)+chn_offset, 16, 5,f0_timing->TMRZ);
	reg_bit_set(CANDS_CTL0_(64)+chn_offset, 24, 5,f1_timing->TMRZ);
	reg_bit_set(CANDS_CTL0_(65)+chn_offset, 0, 5,f2_timing->TMRZ);
	reg_bit_set(CANDS_CTL0_(65)+chn_offset, 8, 5,f3_timing->TMRZ);
	reg_bit_set(CANDS_CTL0_(65)+chn_offset, 16, 5,f4_timing->TMRZ);
	//TPDEX
	reg_bit_set(CANDS_CTL0_(77)+chn_offset,0,16,f0_timing->TPDEX);
	reg_bit_set(CANDS_CTL0_(77)+chn_offset,16,16,f1_timing->TPDEX);
	reg_bit_set(CANDS_CTL0_(78)+chn_offset,0,16,f2_timing->TPDEX);
	reg_bit_set(CANDS_CTL0_(78)+chn_offset,16,16,f3_timing->TPDEX);
	reg_bit_set(CANDS_CTL0_(79)+chn_offset,0,16,f4_timing->TPDEX);
	//TPPD
	reg_bit_set(CANDS_CTL0_(59)+chn_offset,8,3,f0_timing->TPPD);

	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(50+2*i)+chn_offset, 0,17,timing[i]->TRAS_MAX);
		reg_bit_set(CANDS_CTL0_(72+i)+chn_offset,0,16,timing[i]->TREF);
	}

	//TRAS_MIN
	reg_bit_set(CANDS_CTL0_(40)+chn_offset,24, 8,f0_timing->TRAS_MIN);
	reg_bit_set(CANDS_CTL0_(42)+chn_offset,16, 8,f1_timing->TRAS_MIN);
	reg_bit_set(CANDS_CTL0_(44)+chn_offset,8, 8,f2_timing->TRAS_MIN);
	reg_bit_set(CANDS_CTL0_(46)+chn_offset,0, 8,f3_timing->TRAS_MIN);  //bb4 0x22
	reg_bit_set(CANDS_CTL0_(47)+chn_offset,24, 8,f4_timing->TRAS_MIN);
    //TRC
	reg_bit_set(CANDS_CTL0_(40)+chn_offset,16, 8,f0_timing->TRC);
	reg_bit_set(CANDS_CTL0_(42)+chn_offset,8, 8,f1_timing->TRC);
	reg_bit_set(CANDS_CTL0_(44)+chn_offset,0, 8,f2_timing->TRC);
	reg_bit_set(CANDS_CTL0_(45)+chn_offset,24, 8,f3_timing->TRC); //bb4 0x31
	reg_bit_set(CANDS_CTL0_(47)+chn_offset,16, 8,f4_timing->TRC);
	//TRCD
	reg_bit_set(CANDS_CTL0_(60)+chn_offset, 8, 8,f0_timing->TRCD);
	reg_bit_set(CANDS_CTL0_(60)+chn_offset, 24, 8,f1_timing->TRCD);
	reg_bit_set(CANDS_CTL0_(61)+chn_offset, 8, 8,f2_timing->TRCD);
	reg_bit_set(CANDS_CTL0_(61)+chn_offset, 24, 8,f3_timing->TRCD);//bb4 0x0f
	reg_bit_set(CANDS_CTL0_(62)+chn_offset, 8, 8,f4_timing->TRCD);
	//TREF_INTERVAL no this param in iwhale2
	//reg_bit_set(CANDS_CTL0_(118)+chn_offset, 0,16,f0_timing->TREF_INTERVAL);

	//TRFC
	reg_bit_set(CANDS_CTL0_(71)+chn_offset, 8,10,f0_timing->TRFC);
	reg_bit_set(CANDS_CTL0_(72)+chn_offset, 16,10,f1_timing->TRFC);
	reg_bit_set(CANDS_CTL0_(73)+chn_offset, 16,10,f2_timing->TRFC);
	reg_bit_set(CANDS_CTL0_(74)+chn_offset, 16,10,f3_timing->TRFC);
	reg_bit_set(CANDS_CTL0_(75)+chn_offset, 16,10,f4_timing->TRFC);
    //TRP_AB
	__raw_writel(CANDS_CTL0_(68)+chn_offset, (f3_timing->TRP_AB<<24)+(f2_timing->TRP_AB<<16)+(f1_timing->TRP_AB<<8)+f0_timing->TRP_AB);
	reg_bit_set(CANDS_CTL0_(69)+chn_offset, 0,8,f4_timing->TRP_AB);
    //TRP
	reg_bit_set(CANDS_CTL0_(41)+chn_offset, 8, 8,f0_timing->TRP);
	reg_bit_set(CANDS_CTL0_(43)+chn_offset, 0, 8,f1_timing->TRP);
	reg_bit_set(CANDS_CTL0_(44)+chn_offset, 24, 8,f2_timing->TRP);
	reg_bit_set(CANDS_CTL0_(46)+chn_offset, 16, 8,f3_timing->TRP);
	reg_bit_set(CANDS_CTL0_(48)+chn_offset, 8, 8,f4_timing->TRP);
	//TRRD
	reg_bit_set(CANDS_CTL0_(40)+chn_offset, 8, 8,f0_timing->TRRD);
	reg_bit_set(CANDS_CTL0_(42)+chn_offset, 0, 8,f1_timing->TRRD);
	reg_bit_set(CANDS_CTL0_(43)+chn_offset, 24, 8,f2_timing->TRRD);
	reg_bit_set(CANDS_CTL0_(45)+chn_offset, 16, 8,f3_timing->TRRD);
	reg_bit_set(CANDS_CTL0_(47)+chn_offset, 8, 8,f4_timing->TRRD);

    //TRST_PWRON
	__raw_writel(CANDS_CTL0_(35)+chn_offset, f0_timing->TRST_PWRON);

	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(93+2*i)+chn_offset,8, 8,timing[i]->TSR);
	}
	//TRTP
	reg_bit_set(CANDS_CTL0_(49)+chn_offset, 0, 8,f0_timing->TRTP);
	reg_bit_set(CANDS_CTL0_(51)+chn_offset, 8, 8,f1_timing->TRTP);
	reg_bit_set(CANDS_CTL0_(53)+chn_offset, 8, 8,f2_timing->TRTP);
	reg_bit_set(CANDS_CTL0_(55)+chn_offset, 8, 8,f3_timing->TRTP);
	reg_bit_set(CANDS_CTL0_(57)+chn_offset, 8, 8,f4_timing->TRTP);
    	//TVRCG_DISABLE
    	reg_bit_set(CANDS_CTL0_(189)+chn_offset, 0,10,f0_timing->TVRCG_DISABLE);
	reg_bit_set(CANDS_CTL0_(191)+chn_offset,16,10,f1_timing->TVRCG_DISABLE);
	reg_bit_set(CANDS_CTL0_(194)+chn_offset, 0,10,f2_timing->TVRCG_DISABLE);
	reg_bit_set(CANDS_CTL0_(196)+chn_offset,16,10,f3_timing->TVRCG_DISABLE);
	reg_bit_set(CANDS_CTL0_(199)+chn_offset, 0,10,f4_timing->TVRCG_DISABLE);
    	//TVRCG_ENABLE
    	reg_bit_set(CANDS_CTL0_(188)+chn_offset, 16,10,f0_timing->TVRCG_ENABLE);
	reg_bit_set(CANDS_CTL0_(191)+chn_offset, 0,10,f1_timing->TVRCG_ENABLE);
	reg_bit_set(CANDS_CTL0_(193)+chn_offset,16,10,f2_timing->TVRCG_ENABLE);
	reg_bit_set(CANDS_CTL0_(196)+chn_offset, 0,10,f3_timing->TVRCG_ENABLE);
	reg_bit_set(CANDS_CTL0_(198)+chn_offset,16,10,f4_timing->TVRCG_ENABLE);
    	//TVREF_LONG
    	reg_bit_set(CANDS_CTL0_(190)+chn_offset,16,16,f0_timing->TVREF_LONG);
	reg_bit_set(CANDS_CTL0_(193)+chn_offset, 0,16,f1_timing->TVREF_LONG);
	reg_bit_set(CANDS_CTL0_(195)+chn_offset,16,16,f2_timing->TVREF_LONG);
	reg_bit_set(CANDS_CTL0_(198)+chn_offset, 0,16,f3_timing->TVREF_LONG);
	reg_bit_set(CANDS_CTL0_(200)+chn_offset,16,16,f4_timing->TVREF_LONG);

	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(88+i)+chn_offset,0,16,timing[i]->TXSNR);
		reg_bit_set(CANDS_CTL0_(87+i)+chn_offset, 16,16,timing[i]->TXSR);
	}
	//TWR
    	reg_bit_set(CANDS_CTL0_(60)+chn_offset,16, 6,f0_timing->TWR);
	reg_bit_set(CANDS_CTL0_(61)+chn_offset,0, 6,f1_timing->TWR);
	reg_bit_set(CANDS_CTL0_(61)+chn_offset,16, 6,f2_timing->TWR);
	reg_bit_set(CANDS_CTL0_(62)+chn_offset,0, 6,f3_timing->TWR);
	reg_bit_set(CANDS_CTL0_(62)+chn_offset,16, 6,f4_timing->TWR);
    //TWTR
    reg_bit_set(CANDS_CTL0_(41)+chn_offset,0, 6,f0_timing->TWTR);
	reg_bit_set(CANDS_CTL0_(42)+chn_offset,24, 6,f1_timing->TWTR);
	reg_bit_set(CANDS_CTL0_(44)+chn_offset,16, 6,f2_timing->TWTR);
	reg_bit_set(CANDS_CTL0_(46)+chn_offset,8, 6,f3_timing->TWTR);
	reg_bit_set(CANDS_CTL0_(48)+chn_offset,0, 6,f4_timing->TWTR);
    //TZQCAL
    reg_bit_set(CANDS_CTL0_(264)+chn_offset, 0,12,f0_timing->TZQCAL);
	reg_bit_set(CANDS_CTL0_(266)+chn_offset, 16,12,f1_timing->TZQCAL);
	reg_bit_set(CANDS_CTL0_(269)+chn_offset, 0,12,f2_timing->TZQCAL);
	reg_bit_set(CANDS_CTL0_(271)+chn_offset, 16,12,f3_timing->TZQCAL);// bc4 0x320
	reg_bit_set(CANDS_CTL0_(274)+chn_offset, 0,12,f4_timing->TZQCAL);
    //TZQCKE
    reg_bit_set(CANDS_CTL0_(82)+chn_offset,8, 4,f0_timing->TZQCKE);
	reg_bit_set(CANDS_CTL0_(83)+chn_offset,16, 4,f1_timing->TZQCKE);
	reg_bit_set(CANDS_CTL0_(84)+chn_offset,24, 4,f2_timing->TZQCKE);
	reg_bit_set(CANDS_CTL0_(86)+chn_offset,0, 4,f3_timing->TZQCKE);//bc8 0x00
	reg_bit_set(CANDS_CTL0_(87)+chn_offset,8, 4,f4_timing->TZQCKE);
    	//TZQLAT
    	reg_bit_set(CANDS_CTL0_(264)+chn_offset,16, 6,f0_timing->TZQLAT);
	reg_bit_set(CANDS_CTL0_(267)+chn_offset,0, 6,f1_timing->TZQLAT);
	reg_bit_set(CANDS_CTL0_(269)+chn_offset,16, 6,f2_timing->TZQLAT);
	reg_bit_set(CANDS_CTL0_(272)+chn_offset,0, 6,f3_timing->TZQLAT);// bc4 0x18
	reg_bit_set(CANDS_CTL0_(274)+chn_offset,16, 6,f4_timing->TZQLAT);
    	//WLDQSEN
	reg_bit_set(CANDS_CTL0_(333)+chn_offset,24, 6,f0_timing->WLDQSEN);
	//WLMRD
	reg_bit_set(CANDS_CTL0_(334)+chn_offset,0, 6,f0_timing->WLMRD);

	return;
}

void cands_ctl_basicmode_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{

	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//memory type, lpddr3 or lpddr4 ?
	reg_bit_set(CANDS_CTL0_(0)+chn_offset,8,4,islp3?0x7:0xb);

	//cs_map, dsiable unused cs
	//#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_CTL0_(285)+chn_offset,0,2,IS_2CS(ddr_type)?3:1);
	//#else
	//reg_bit_set(CANDS_CTL0_(312)+chn_offset,24,8,3);
	//#endif

	//dram_clk_disable, disable unused cs clock
	//reg_bit_set(CANDS_CTL0_(452)+chn_offset,24,8,IS_2CS(ddr_type)?0xfc:0xfe);
	//dram_clk_disable for each cs
	reg_bit_set(CANDS_CTL0_(417)+chn_offset,0,2,0);

	//aprebit
	reg_bit_set(CANDS_CTL0_(280)+chn_offset,24,4,islp3?0xa:0xb);  //Defines the location of the auto pre-charge bit in the DRAM address in decimal encoding

	//auto-refresh threshold
	reg_bit_set(CANDS_CTL0_(238)+chn_offset,16,5,0x15);  //aref_high_threshold
	reg_bit_set(CANDS_CTL0_(239)+chn_offset, 0,5,0x10);  //aref_max_credit
	reg_bit_set(CANDS_CTL0_(238)+chn_offset,24,5,0x18);  //aref_max_deficit
	reg_bit_set(CANDS_CTL0_(238)+chn_offset, 8,5,0x12);  //aref_norm_threshold

	//burst length--bstlen
	reg_bit_set(CANDS_CTL0_(67)+chn_offset, 24,5,islp3?3:4);   //3:bl8  4:bl16  5:bl32

	//concurrentap,  allow one bank to be auto pre-charged while another bank is reading or writing, memory should support
	reg_bit_set(CANDS_CTL0_(66)+chn_offset,0,1,1);   //?????

	//reversed, spec said to set to 3
	//reg_bit_set(CANDS_CTL0_(24)+chn_offset,8,3,3);

	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(289)+chn_offset,8,1,1);

	//tref_enable enalbe auto_selfrefsh cmd according to tref
	reg_bit_set(CANDS_CTL0_(70)+chn_offset,24,1,1);

	//dfibus_boot_freq
	reg_bit_set(CANDS_CTL0_(32)+chn_offset,24,3,FN_CTL_BOOT);
	//dfibus_freq_init
	reg_bit_set(CANDS_CTL0_(32)+chn_offset,16,3,FN_CTL_TARGET);
	//dfibus_freq_fn
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_CTL0_(33)+chn_offset,0,5,0);
	reg_bit_set(CANDS_CTL0_(33)+chn_offset,8,5,1);
	reg_bit_set(CANDS_CTL0_(33)+chn_offset,16,5,2);
	reg_bit_set(CANDS_CTL0_(33)+chn_offset,24,5,3);
	reg_bit_set(CANDS_CTL0_(34)+chn_offset,0,5,4);
	#else
	reg_bit_set(CANDS_CTL0_(33)+chn_offset,0,5,1);
	reg_bit_set(CANDS_CTL0_(33)+chn_offset,8,5,2);
	reg_bit_set(CANDS_CTL0_(33)+chn_offset,16,5,3);
	reg_bit_set(CANDS_CTL0_(33)+chn_offset,24,5,4);
	reg_bit_set(CANDS_CTL0_(34)+chn_offset,0,5,0);
    	#endif
	//en_1t_timing,   only for lp3
    	reg_bit_set(CANDS_CTL0_(472)+chn_offset,24,1,1); //2T timing on whale2?? should check

	//disable_memory_masked_write  0:allow mask write   1:disable make write, only for lp4    ?????
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_CTL0_(473)+chn_offset,0,1,0);
	#else
	reg_bit_set(CANDS_CTL0_(473)+chn_offset,0,1,1);
	#endif

    //enable_quick_srefresh
    reg_bit_set(CANDS_CTL0_(103)+chn_offset,0,1,1);

	//optimal_rmodw_en  ????????need check with asic
    reg_bit_set(CANDS_CTL0_(69)+chn_offset, 16, 1, 1);


    //long_count_mask
    reg_bit_set(CANDS_CTL0_(238)+chn_offset,0,5,0); //0:1024 clock  0x10:512 clock  0x18:256 clock   0x1c:128 clock ...

    //memdata_ratio_X
    reg_bit_set(CANDS_CTL0_(285)+chn_offset, 16,3,islp3?0:1);
    reg_bit_set(CANDS_CTL0_(286)+chn_offset,24,3,islp3?0:1);

    //no_memory_dm, Indicates that the external DRAM does not support DM masking. ??????
    reg_bit_set(CANDS_CTL0_(70)+chn_offset, 0,1,0);

    //no_phy_ind_train_init, Disables PHY independent training from executing during initialization, should check ???????
    reg_bit_set(CANDS_CTL0_(32)+chn_offset, 0,1,0);

    //phy_indep_train_mode   ????????
    reg_bit_set(CANDS_CTL0_(32)+chn_offset,  8,1,1);

    //phymstr_no_aref,Disables refreshes during the PHY master interface sequence   ??????
    reg_bit_set(CANDS_CTL0_(130)+chn_offset, 0,1,0);

    //phyupd_append_en, Enables an automatic PHY-initiated update prior to running any type of training
    reg_bit_set(CANDS_CTL0_(333)+chn_offset, 0,1,1);

    //preamble_support, Defines the read and write premble. should check when lpddr4    ????????
    reg_bit_set(CANDS_CTL0_(289)+chn_offset, 16,2,islp3?0:2);

    //rd_dbi_en, Enables controller support of the DRAM DBI feature for read data. lpddr4 only
	reg_bit_set(CANDS_CTL0_(290)+chn_offset, 8,1,islp3?0:RD_DBI_EN);

    //rd_preamble_training_en, Enables read preamble training with gate training
	reg_bit_set(CANDS_CTL0_(289)+chn_offset,  24,1, islp3?0:RD_PREAMBLE_TR_EN);

    //reduc,  Allows the same controller to be used with memories with a smaller datapath
    reg_bit_set(CANDS_CTL0_(285)+chn_offset,  8,1,IS_16BIT(ddr_type));

    //device0_byte0_cs0,  for mrr data back on 1:byte0    2:byte1    3:byte2     4:byte3       0: data always 0
    reg_bit_set(CANDS_CTL0_(285)+chn_offset,  24,4,1);

    //device0_byte0_cs1,  for mrr data back on 1:byte0    2:byte1    3:byte2     4:byte3       0: data always 0
    reg_bit_set(CANDS_CTL0_(287)+chn_offset,  0,4,1);

    //reg_dimm_enable,  Enables registered DIMM operations to control the address and command pipeline of the controller
    reg_bit_set(CANDS_CTL0_(69)+chn_offset, 8,1,0);

    //tras_lockout,  Enables tRAS lockout. tRAS lockout allows the controller to execute auto pre-charge commands before the tras_min_fN_X parameter has expired
	reg_bit_set(CANDS_CTL0_(66)+chn_offset,  8,1,0);   //????????
    //reversed
	//#ifdef DRAM_LPDDR4
	//reg_bit_set(CANDS_CTL0_(24)+chn_offset,  8,3,3);   //????????
	//#endif

    //tverf_disable,lpddr4 only   ???????? can not find this param on iwhale2
    //reg_bit_set(CANDS_CTL0_(853)+chn_offset,  8,1,islp3?0:1);

    //wr_dbi_en
    reg_bit_set(CANDS_CTL0_(290)+chn_offset,  0,1,islp3?0:WR_DBI_EN);

    //writeinterp,    Defines whether the controller can interrupt a write burst with a read command.
    reg_bit_set(CANDS_CTL0_(60)+chn_offset,  0,1,0);
	//#ifdef DRAM_LPDDR4
	//reserved
    //reg_bit_set(CANDS_CTL0_(21)+chn_offset,  24,3,2);
	//#endif
    //reversed
    //__raw_writel(CANDS_CTL0_(121)+chn_offset, 0x40020100);
    //__raw_writel(CANDS_CTL0_(122)+chn_offset, 0x00008010);
    //__raw_writel(CANDS_CTL0_(273)+chn_offset, 0x3);
}

void cands_ctl_calvl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_CTL_TIMING_T * ctl_timing,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

	//calvl_aref_en
	reg_bit_set(CANDS_CTL0_(388)+chn_offset,8,1, 1);
    //calvl_bg_pat_0~3
    	reg_bit_set(CANDS_CTL0_(380)+chn_offset,0,20, 0x000aaaaa);
	reg_bit_set(CANDS_CTL0_(382)+chn_offset,0,20, 0x00055555);
	reg_bit_set(CANDS_CTL0_(384)+chn_offset,0,20, 0x0004cd33);
	reg_bit_set(CANDS_CTL0_(386)+chn_offset,0,20, 0x000b32cc);
    //calvl_pat_0~3
	reg_bit_set(CANDS_CTL0_(379)+chn_offset,0,20, 0x000556aa);
	reg_bit_set(CANDS_CTL0_(381)+chn_offset,0,20, 0x000aa955);
	reg_bit_set(CANDS_CTL0_(383)+chn_offset,0,20, 0x000b3133);
	reg_bit_set(CANDS_CTL0_(385)+chn_offset,0,20, 0x0004cecc);
	//calvl_cs
	reg_bit_set(CANDS_CTL0_(378)+chn_offset,24,1, 0);
	//calvl_cs_map
	reg_bit_set(CANDS_CTL0_(388)+chn_offset,24,2, IS_2CS(ddr_type)?3:1);
	//calvl_en
	reg_bit_set(CANDS_CTL0_(469)+chn_offset, 8,1, CALVL_EN);
	//calvl_on_sref_exit
	reg_bit_set(CANDS_CTL0_(388)+chn_offset, 0,1, CALVL_EN_SREF);
    //calvl_periodic
    reg_bit_set(CANDS_CTL0_(387)+chn_offset,24,1, 0); //disable periodic ca training
    //calvl_resp_mask
    reg_bit_set(CANDS_CTL0_(469)+chn_offset, 0,1, 0);
    //calvl_rotate   ???? only for sw calvl ??????
    reg_bit_set(CANDS_CTL0_(388)+chn_offset,16,1, 0); //0:train all cs   1:train only one cs
    //calvl_seq_en
    reg_bit_set(CANDS_CTL0_(387)+chn_offset, 8,2, 3); //calvl pattern sequence   3:pattern 0->1->2->3->0
}

void cands_ctl_dfi_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_CTL_TIMING_T * ctl_timing,
						uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

	//************************dfi lvl mode****************************/
    //dfi_phy_calvl_mode, Indicates the PHY\A1\AFs support for DFI CA training
    reg_bit_set(CANDS_CTL0_(387)+chn_offset,16,1, 1);
    //dfi_phy_rdlvl_gate_mode, Indicates the DFI gate training support for the PHY
    reg_bit_set(CANDS_CTL0_(350)+chn_offset,16,1, 1);
    //dfi_phy_rdlvl_mode, Indicates the DFI data eye training support for the PHY
    reg_bit_set(CANDS_CTL0_(350)+chn_offset, 8,1, 1);
    //dfi_phy_wrlvl_mode, Indicates the DFI write leveling mode support for the PHY,lpddr3 only ????????
    reg_bit_set(CANDS_CTL0_(334)+chn_offset, 16,1, 1);

    //*************************dfi lvl timing***************************/
    //TDFI_CALVL_CAPTURE, TDFI_CALVL_CC
	for(i=0;i < 5; i++) {
		__raw_writel(CANDS_CTL0_(462+i)+chn_offset,(timing[i]->TDFI_CALVL_CAPTURE<<16)|timing[i]->TDFI_CALVL_CC);
	}

    //TDFI_CALVL_EN
    reg_bit_set(CANDS_CTL0_(461)+chn_offset,16, 8,f0_timing->TDFI_CALVL_EN);
    //TDFI_CALVL_MAX
    __raw_writel(CANDS_CTL0_(468)+chn_offset,f0_timing->TDFI_CALVL_MAX);
    //TDFI_CALVL_RESP
    __raw_writel(CANDS_CTL0_(467)+chn_offset,f0_timing->TDFI_CALVL_RESP);

	for(i=0;i < 5; i++) {
		__raw_writel(CANDS_CTL0_(423+7*i)+chn_offset,timing[i]->TDFI_CTRLUPD_INTERVAL);
		reg_bit_set(CANDS_CTL0_(417+7*i)+chn_offset,16,16,timing[i]->TDFI_CTRLUPD_MAX);
	}
	//TDFI_CTRL_DELAY
    reg_bit_set(CANDS_CTL0_(452)+chn_offset, 16, 4,f0_timing->TDFI_CTRL_DELAY);
    reg_bit_set(CANDS_CTL0_(452)+chn_offset, 24, 4,f1_timing->TDFI_CTRL_DELAY);
    reg_bit_set(CANDS_CTL0_(453)+chn_offset, 0, 4,f2_timing->TDFI_CTRL_DELAY);
    reg_bit_set(CANDS_CTL0_(453)+chn_offset, 8, 4,f3_timing->TDFI_CTRL_DELAY);
    reg_bit_set(CANDS_CTL0_(453)+chn_offset, 16, 4,f4_timing->TDFI_CTRL_DELAY);
    //TDFI_CTRLUPD_MIN
    reg_bit_set(CANDS_CTL0_(417)+chn_offset, 8, 4,f0_timing->TDFI_CTRLUPD_MIN);
    //TDFI_DRAM_CLK_DISABLE
    reg_bit_set(CANDS_CTL0_(453)+chn_offset,24, 4,f0_timing->TDFI_DRAM_CLK_DISABLE);
    //TDFI_DRAM_CLK_ENABLE
    reg_bit_set(CANDS_CTL0_(454)+chn_offset, 0, 4,f0_timing->TDFI_DRAM_CLK_ENABLE);
    //TDFI_INIT_COMPLETE
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(171+i)+chn_offset,0,16,timing[i]->TDFI_INIT_COMPLETE);
	}

    //TDFI_INIT_START
    reg_bit_set(CANDS_CTL0_(170)+chn_offset, 24, 8,f0_timing->TDFI_INIT_START);
    reg_bit_set(CANDS_CTL0_(171)+chn_offset, 16, 8,f1_timing->TDFI_INIT_START);
    reg_bit_set(CANDS_CTL0_(172)+chn_offset, 16, 8,f2_timing->TDFI_INIT_START);
    reg_bit_set(CANDS_CTL0_(173)+chn_offset, 16, 8,f3_timing->TDFI_INIT_START);
    reg_bit_set(CANDS_CTL0_(174)+chn_offset, 16, 8,f4_timing->TDFI_INIT_START);
    //TDFI_LP_RESP
    reg_bit_set(CANDS_CTL0_(153)+chn_offset, 0, 3,f0_timing->TDFI_LP_RESP);
    //TDFI_PHY_RDLAT
    reg_bit_set(CANDS_CTL0_(415)+chn_offset, 16, 7,f0_timing->TDFI_PHY_RDLAT);
    reg_bit_set(CANDS_CTL0_(415)+chn_offset, 24, 7,f1_timing->TDFI_PHY_RDLAT);
    reg_bit_set(CANDS_CTL0_(416)+chn_offset, 0, 7,f2_timing->TDFI_PHY_RDLAT);
    reg_bit_set(CANDS_CTL0_(416)+chn_offset, 8, 7,f3_timing->TDFI_PHY_RDLAT);
    reg_bit_set(CANDS_CTL0_(416)+chn_offset, 16, 7,f4_timing->TDFI_PHY_RDLAT);
	//TDFI_PHY_WRDATA
	reg_bit_set(CANDS_CTL0_(469)+chn_offset,24, 3,f0_timing->TDFI_PHY_WRDATA);
	//TDFI_PHY_WRLAT
	reg_bit_set(CANDS_CTL0_(415)+chn_offset,0, 7,f0_timing->TDFI_PHY_WRLAT);


	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(422+7*i)+chn_offset, 0,16,timing[i]->TDFI_PHYUPD_RESP);
		__raw_writel(CANDS_CTL0_(418+7*i)+chn_offset,timing[i]->TDFI_PHYUPD_TYPE0);
		__raw_writel(CANDS_CTL0_(419+7*i)+chn_offset,timing[i]->TDFI_PHYUPD_TYPE1);
		__raw_writel(CANDS_CTL0_(420+7*i)+chn_offset,timing[i]->TDFI_PHYUPD_TYPE2);
		__raw_writel(CANDS_CTL0_(421+7*i)+chn_offset,timing[i]->TDFI_PHYUPD_TYPE3);
	}
	//TDFI_PHYMSTR_MAX
    reg_bit_set(CANDS_CTL0_(122)+chn_offset, 16,16,f0_timing->TDFI_PHYMSTR_MAX);
    reg_bit_set(CANDS_CTL0_(124)+chn_offset, 0,16,f1_timing->TDFI_PHYMSTR_MAX);
    reg_bit_set(CANDS_CTL0_(125)+chn_offset, 16,16,f2_timing->TDFI_PHYMSTR_MAX);
    reg_bit_set(CANDS_CTL0_(127)+chn_offset, 0,16,f3_timing->TDFI_PHYMSTR_MAX);
    reg_bit_set(CANDS_CTL0_(128)+chn_offset, 16,16,f4_timing->TDFI_PHYMSTR_MAX);
    //TDFI_PHYMSTR_RESP
    reg_bit_set(CANDS_CTL0_(123)+chn_offset,0,16,f0_timing->TDFI_PHYMSTR_RESP);
    reg_bit_set(CANDS_CTL0_(124)+chn_offset,16,16,f1_timing->TDFI_PHYMSTR_RESP);
    reg_bit_set(CANDS_CTL0_(126)+chn_offset,0,16,f2_timing->TDFI_PHYMSTR_RESP);
    reg_bit_set(CANDS_CTL0_(127)+chn_offset,16,16,f3_timing->TDFI_PHYMSTR_RESP);
    reg_bit_set(CANDS_CTL0_(129)+chn_offset,0,16,f4_timing->TDFI_PHYMSTR_RESP);

    //TDFI_RDDATA_EN
    reg_bit_set(CANDS_CTL0_(416)+chn_offset,24, 7,f0_timing->TDFI_RDDATA_EN);
    //TDFI_RDLVL_EN
    reg_bit_set(CANDS_CTL0_(457)+chn_offset, 0, 8,f0_timing->TDFI_RDLVL_EN);
    //TDFI_RDLVL_MAX
    __raw_writel(CANDS_CTL0_(460)+chn_offset, f0_timing->TDFI_RDLVL_MAX);
    //TDFI_RDLVL_RESP
    __raw_writel(CANDS_CTL0_(458)+chn_offset, f0_timing->TDFI_RDLVL_RESP);
    //TDFI_RDLVL_RR
    reg_bit_set(CANDS_CTL0_(457)+chn_offset, 8,10,f0_timing->TDFI_RDLVL_RR);

    //TDFI_RDCSLAT
    reg_bit_set(CANDS_CTL0_(470)+chn_offset,0, 7,f0_timing->TDFI_RDCSLAT);
    reg_bit_set(CANDS_CTL0_(470)+chn_offset,16, 7,f1_timing->TDFI_RDCSLAT);
    reg_bit_set(CANDS_CTL0_(471)+chn_offset,0, 7,f2_timing->TDFI_RDCSLAT);
    reg_bit_set(CANDS_CTL0_(471)+chn_offset,16, 7,f3_timing->TDFI_RDCSLAT);
    reg_bit_set(CANDS_CTL0_(472)+chn_offset,0, 7,f4_timing->TDFI_RDCSLAT);
	//tdfi_wrcslat
	reg_bit_set(CANDS_CTL0_(470)+chn_offset,8, 7, f0_timing->TDFI_WRCSLAT);
	reg_bit_set(CANDS_CTL0_(470)+chn_offset,24, 7, f1_timing->TDFI_WRCSLAT);
	reg_bit_set(CANDS_CTL0_(471)+chn_offset,8, 7, f2_timing->TDFI_WRCSLAT);
	reg_bit_set(CANDS_CTL0_(471)+chn_offset,24, 7, f3_timing->TDFI_WRCSLAT);
	reg_bit_set(CANDS_CTL0_(472)+chn_offset,8, 7, f4_timing->TDFI_WRCSLAT);
    //TDFI_WRLVL_EN
    reg_bit_set(CANDS_CTL0_(454)+chn_offset, 8, 8,f0_timing->TDFI_WRLVL_EN);
    //TDFI_WRLVL_MAX
    __raw_writel(CANDS_CTL0_(456)+chn_offset, f0_timing->TDFI_WRLVL_MAX);
    //TDFI_WRLVL_RESP
    __raw_writel(CANDS_CTL0_(455)+chn_offset, f0_timing->TDFI_WRLVL_RESP);
    //TDFI_WRLVL_WW
    reg_bit_set(CANDS_CTL0_(454)+chn_offset,16, 10,f0_timing->TDFI_WRLVL_WW);
}

void cands_ctl_dfs_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{

	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//dfs_always_write_fsp
	reg_bit_set(CANDS_CTL0_(230)+chn_offset,8,1,islp3?0:1);
	#ifdef DRAM_LPDDR4
	//reg_bit_set(CANDS_CTL0_(907)+chn_offset,24, 1, 1);
	//dfi_inv_data_cs
	reg_bit_set(CANDS_CTL0_(31)+chn_offset,8, 1, 1);
	#endif

    //dfs_close_banks, ctl spec this parameter is reserved for future use and should be clear to 0
	reg_bit_set(CANDS_CTL0_(11)+chn_offset,0,1,0);
	//only_for_lpddr3
	//dfs_phy_reg_write_en
	reg_bit_set(CANDS_CTL0_(175)+chn_offset, 24,1,0);
	//dfs_enable
	reg_bit_set(CANDS_CTL0_(170)+chn_offset, 16,1,1);
	//dfs_phy_reg_write_addr
	__raw_writel(CANDS_CTL0_(176)+chn_offset,0xc00);
	//dfs_phy_reg_write_mask
	reg_bit_set(CANDS_CTL0_(182)+chn_offset, 0,4,0xe);

	//dfs_phy_reg_write_data
	__raw_writel(CANDS_CTL0_(177)+chn_offset, 0);
	__raw_writel(CANDS_CTL0_(178)+chn_offset, 1);
	__raw_writel(CANDS_CTL0_(179)+chn_offset, 2);
	__raw_writel(CANDS_CTL0_(180)+chn_offset, 3);
	__raw_writel(CANDS_CTL0_(181)+chn_offset, 4);

    //dfs_calvl_en
	reg_bit_set(CANDS_CTL0_(104)+chn_offset,16,1,CALVL_EN_DFS); //Enables CA training during a DFS exit
	//dfs_rdlvl_en
	reg_bit_set(CANDS_CTL0_(105)+chn_offset, 0,1,RDELVL_EN_DFS); //Enables data eye training during a DFS exit.
	//dfs_rdlvl_gate_en
	reg_bit_set(CANDS_CTL0_(105)+chn_offset, 8,1,RDGLVL_EN_DFS); //Enables gate training during a DFS exit.
	//dfs_wrlvl_en
	reg_bit_set(CANDS_CTL0_(104)+chn_offset,  24,1,WRLVL_EN_DFS); //Enables write leveling during a DFS exit.
	//dfs_zq_en
	reg_bit_set(CANDS_CTL0_(104)+chn_offset, 8,1,ZQ_EN_DFS); //Enables ZQ calibration during a DFS exit

	return;
}

void cands_ctl_fsp_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{

	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN	islp3 = IS_LPDDR3(ddr_type);

    //fsp_op_current
    reg_bit_set(CANDS_CTL0_(230)+chn_offset, 16, 1, islp3?0:FSP_OP);  //???????? indentifies the FSP set that is currently in use
    //fsp_wr_current,  spec said recommand fsp_wr_current != fsp_op_current
    reg_bit_set(CANDS_CTL0_(230)+chn_offset,24, 1, islp3?0:FSP_WR);  //???????? indentifies the FSP set that will be write
    //fsp0_frc
    #ifdef DRAM_LPDDR3
    reg_bit_set(CANDS_CTL0_(231)+chn_offset,16, 3, 0); //???????? indentifies which fn is for FSP set 0
    #else
    //reg_bit_set(CANDS_CTL0_(908)+chn_offset,24, 3, 1); //???????? indentifies which fn is for FSP set 0
    #endif
    //fsp1_frc
    //reg_bit_set(CANDS_CTL0_(909)+chn_offset,0, 3, islp3?0:1); //???????? indentifies which fn is for FSP set 1

    //fsp_phy_update_mrw
    reg_bit_set(CANDS_CTL0_(229)+chn_offset,24, 1, islp3?1:1);  ///?????? define which part to updat MR12&MR14 in init/dfs/sw mrw 0:ctl 1:phy or pi
    //fsp_status

    //disable_update_tvrcg, lpddr4 only
    reg_bit_set(CANDS_CTL0_(187)+chn_offset,16, 1, IS_LPDDR3(ddr_type)?1:0);

	#ifdef DRAM_LPDDR4
	//mr_fsp_data_valid	indicate the fn was trained, and the data was loaded into mrx_data register
	//cs0
	reg_bit_set(CANDS_CTL0_(214)+chn_offset,8, 1, 1);
	reg_bit_set(CANDS_CTL0_(214)+chn_offset,16, 1, 1);
	reg_bit_set(CANDS_CTL0_(214)+chn_offset, 24, 1, 1);
	reg_bit_set(CANDS_CTL0_(215)+chn_offset, 0, 1, 1);
	reg_bit_set(CANDS_CTL0_(215)+chn_offset,8, 1, 1);
	//cs1
	reg_bit_set(CANDS_CTL0_(225)+chn_offset,24, 1, 1);
	reg_bit_set(CANDS_CTL0_(226)+chn_offset,0, 1, 1);
	reg_bit_set(CANDS_CTL0_(226)+chn_offset, 8, 1, 1);
	reg_bit_set(CANDS_CTL0_(226)+chn_offset, 16, 1, 1);
	reg_bit_set(CANDS_CTL0_(226)+chn_offset,24, 1, 1);
	#endif

}


void cands_ctl_latency_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //RL  caslat_lin
    reg_bit_set(CANDS_CTL0_(37)+chn_offset,0, 7,f0_timing->CASLAT_LIN);
    reg_bit_set(CANDS_CTL0_(37)+chn_offset,16, 7,f1_timing->CASLAT_LIN);
    reg_bit_set(CANDS_CTL0_(38)+chn_offset,0, 7,f2_timing->CASLAT_LIN);
    reg_bit_set(CANDS_CTL0_(38)+chn_offset,16, 7,f3_timing->CASLAT_LIN);
    reg_bit_set(CANDS_CTL0_(39)+chn_offset,0, 7,f4_timing->CASLAT_LIN);

	//do not use in this system, phy_dll_rst_en default alwasy on do not care controller's dll_rst_n
    //DLL_RST_ADJ_DLY
    reg_bit_set(CANDS_CTL0_(414)+chn_offset,24, 8,f0_timing->DLL_RST_ADJ_DLY);
    //DLL_RST_DELAY
    reg_bit_set(CANDS_CTL0_(414)+chn_offset, 8,16,f0_timing->DLL_RST_DELAY);

    //RL_ADJ  rdlat_adj
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(424+7*i)+chn_offset, 0, 7,timing[i]->RDLAT_ADJ);
		reg_bit_set(CANDS_CTL0_(321+i)+chn_offset,8, 5,timing[i]->R2R_DIFFCS_DLY);
	}

    //R2R_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(326)+chn_offset, 8, 5,f0_timing->R2R_SAMECS_DLY);

    //R2W_DIFFCS_DLY
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(321+i)+chn_offset, 16, 5,timing[i]->R2W_DIFFCS_DLY);
		reg_bit_set(CANDS_CTL0_(424+7*i)+chn_offset, 8, 7,timing[i]->WRLAT_ADJ);
		reg_bit_set(CANDS_CTL0_(321+i)+chn_offset, 24, 5,timing[i]->W2R_DIFFCS_DLY);
		reg_bit_set(CANDS_CTL0_(322+i)+chn_offset, 0, 5,timing[i]->W2W_DIFFCS_DLY);
	}
    //W2R_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(327)+chn_offset,24, 5,f0_timing->W2R_SAMECS_DLY);

    //R2W_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(326)+chn_offset, 16, 5,f0_timing->R2W_SAMECS_DLY);
    reg_bit_set(CANDS_CTL0_(326)+chn_offset, 24, 5,f1_timing->R2W_SAMECS_DLY);
    reg_bit_set(CANDS_CTL0_(327)+chn_offset, 0, 5,f2_timing->R2W_SAMECS_DLY);
    reg_bit_set(CANDS_CTL0_(327)+chn_offset, 8, 5,f3_timing->R2W_SAMECS_DLY);
    reg_bit_set(CANDS_CTL0_(327)+chn_offset, 16, 5,f4_timing->R2W_SAMECS_DLY);

    //RW2MRW_DLY
    reg_bit_set(CANDS_CTL0_(320)+chn_offset,0, 4,f0_timing->RW2MRW_DLY);
    reg_bit_set(CANDS_CTL0_(320)+chn_offset,8, 4,f1_timing->RW2MRW_DLY);
    reg_bit_set(CANDS_CTL0_(320)+chn_offset,16, 4,f2_timing->RW2MRW_DLY);
    reg_bit_set(CANDS_CTL0_(320)+chn_offset,24, 4,f3_timing->RW2MRW_DLY);
    reg_bit_set(CANDS_CTL0_(321)+chn_offset,0, 4,f4_timing->RW2MRW_DLY);

    //WL   wrlat
    reg_bit_set(CANDS_CTL0_(37)+chn_offset, 8, 7,f0_timing->WRLAT);
    reg_bit_set(CANDS_CTL0_(37)+chn_offset, 24, 7,f1_timing->WRLAT);
    reg_bit_set(CANDS_CTL0_(38)+chn_offset, 8, 7,f2_timing->WRLAT);
    reg_bit_set(CANDS_CTL0_(38)+chn_offset, 24, 7,f3_timing->WRLAT);
    reg_bit_set(CANDS_CTL0_(39)+chn_offset, 8, 7,f4_timing->WRLAT);

    //W2R_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(327)+chn_offset,24, 5,f0_timing->W2R_SAMECS_DLY);
    //W2W_SAMECS_DLY
    reg_bit_set(CANDS_CTL0_(328)+chn_offset,0, 5,f0_timing->W2W_SAMECS_DLY);
}


void cands_ctl_lowpower_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,
							 uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //******************* low power mode en ************************//
    //lowpower_refresh_enable
    reg_bit_set(CANDS_CTL0_(138)+chn_offset, 0,2, 0);

    //lowpower_auto_entry_en, Enables automatic entry into each of the low power states when the associated idle timer expires
    //reg_bit_set(CANDS_CTL0_(160)+chn_offset, 16, 1, 0); //power down
    //reg_bit_set(CANDS_CTL0_(160)+chn_offset, 17, 1, 0); //self refresh
    //reg_bit_set(CANDS_CTL0_(160)+chn_offset, 18, 1, 0); //self refresh with memory and controller clock gating
	reg_bit_set(CANDS_CTL0_(153)+chn_offset, 24, 4, 0);
    //lp_auto_exit_en,Enables automatic exit from each of the low power states when a read or write command enters the command queue in the Controller core.
    //reg_bit_set(CANDS_CTL0_(160)+chn_offset, 24, 1, 0); //power down
    //reg_bit_set(CANDS_CTL0_(160)+chn_offset, 25, 1, 0); //lite self refresh
    //reg_bit_set(CANDS_CTL0_(160)+chn_offset, 26, 1, 0); //deep refresh with memory and controller clock gating
	reg_bit_set(CANDS_CTL0_(154)+chn_offset, 0, 4, 0);
	//lp_auto_mem_gate_en,Enables memory clock gating when entering each of the low power modes automatically.
    //reg_bit_set(CANDS_CTL0_(161)+chn_offset,  0, 1, 0); //power down
    //reg_bit_set(CANDS_CTL0_(161)+chn_offset,  1, 1, 0); //self refresh
    //reg_bit_set(CANDS_CTL0_(161)+chn_offset,  2, 1, 0); //Self-Refresh Power-Down---probelem
	reg_bit_set(CANDS_CTL0_(155)+chn_offset, 24, 8, 0);

    //lpc_sr_ctrlupd_en
    reg_bit_set(CANDS_CTL0_(161)+chn_offset, 0, 1, 0); //Enables the LPC to execute a DFI control update on a self-refresh exit sequence???should check
    //lpc_sr_phymstr_en
    reg_bit_set(CANDS_CTL0_(161)+chn_offset, 16, 1, 0); //Enables the LPC to execute a DFI PHY master request on a self-refresh exit sequence???should check
    //lpc_sr_phyupd_en
    reg_bit_set(CANDS_CTL0_(161)+chn_offset, 8, 1, 0); //Enables the LPC to execute a DFI PHY update on a self-refresh exit sequence???should check
    //lpi_wakeup_en
    reg_bit_set(CANDS_CTL0_(151)+chn_offset, 16, 5, 0xF);//bit0:Power-Down (lp_pd_wakeup_fN)
                                                        //bit1:Self-Refresh (lpi_sr_wakeup_fN)
                                                        //bit2:Self-Refresh with memory and controller clock gating
                                                        //bit3:Reserved
                                                        //bit4:LPI Timer

    //pwrup_srefresh_exit,   Allows the controller to exit low power by executing a self-refresh exit instead of the full memory initialization
    //reg_bit_set(CANDS_CTL0_(115)+chn_offset, 0, 1, 1);
    reg_bit_set(CANDS_CTL0_(102)+chn_offset, 16, 1, 0);
	//pwrup_srefresh_exit_cs for cs has different low power state
    reg_bit_set(CANDS_CTL0_(170)+chn_offset, 0, 2, 0);

    //srefresh_exit_no_refresh
    reg_bit_set(CANDS_CTL0_(102)+chn_offset, 24, 1, 1); //not Allow automatic refresh when self-refresh exit
	//pcpcs_pd_en
	reg_bit_set(CANDS_CTL0_(162)+chn_offset, 8, 1, 0);
	//pcpcs_cs_map
	reg_bit_set(CANDS_CTL0_(163)+chn_offset, 16, 2, 3);
	//pcpcs_pd_enter_timer
	reg_bit_set(CANDS_CTL0_(163)+chn_offset, 0, 8, 0);
	//pcpcs_pd_enter_depth
	reg_bit_set(CANDS_CTL0_(162)+chn_offset, 16, 5, 4);
	//pcpcs_pd_exit_depth
	reg_bit_set(CANDS_CTL0_(162)+chn_offset, 24, 5, 4);

    //******************* low power timing ************************//
    reg_bit_set(CANDS_CTL0_(154)+chn_offset,16,12,f0_timing->LP_AUTO_PD_IDLE);
	reg_bit_set(CANDS_CTL0_(155)+chn_offset,16, 8, f0_timing->LP_AUTO_SR_IDLE);
	reg_bit_set(CANDS_CTL0_(155)+chn_offset, 0,12,f0_timing->LP_AUTO_SRPD_LITE_IDLE);
	reg_bit_set(CANDS_CTL0_(155)+chn_offset, 24, 8,f0_timing->LP_AUTO_SR_MC_GATE_IDLE);
    //LPI_PD_WAKEUP
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(141+2*i)+chn_offset,16, 4,timing[i]->LPI_PD_WAKEUP);
		reg_bit_set(CANDS_CTL0_(142+2*i)+chn_offset, 0, 4,timing[i]->LPI_SR_MCCLK_GATE_WAKEUP);
		reg_bit_set(CANDS_CTL0_(141+2*i)+chn_offset,24, 4,timing[i]->LPI_SR_WAKEUP);
		reg_bit_set(CANDS_CTL0_(142+2*i)+chn_offset,24, 4,timing[i]->LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP);
		reg_bit_set(CANDS_CTL0_(142+2*i)+chn_offset,16, 4,timing[i]->LPI_SRPD_DEEP_WAKEUP);
		reg_bit_set(CANDS_CTL0_(142+2*i)+chn_offset,8, 4,timing[i]->LPI_SRPD_LITE_WAKEUP);
	}

    //LPI_TIMER_COUNT
    reg_bit_set(CANDS_CTL0_(152)+chn_offset, 0,12,f0_timing->LPI_TIMER_COUNT);
    //LPI_TIMER_WAKEUP
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_CTL0_(143+2*i)+chn_offset, 8, 4,timing[i]->LPI_TIMER_WAKEUP);
	}
    //LPI_WAKEUP_TIMEOUT
    reg_bit_set(CANDS_CTL0_(152)+chn_offset, 16,12,f0_timing->LPI_WAKEUP_TIMEOUT);

}

void cands_ctl_modreg_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,
							 uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;
	uint32 val;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //***********************mode register read&write mode*****************//
	//mrw_dfs_update_frc
    reg_bit_set(CANDS_CTL0_(188)+chn_offset, 0,3,0);

	//no_auto_mrr_init
    reg_bit_set(CANDS_CTL0_(30)+chn_offset, 24,1,0);  //for mr8&mr11 will be auto read if set to 0

	//no_mrw_bt_init
    reg_bit_set(CANDS_CTL0_(31)+chn_offset,  16,1,0);
	//no_mrw_init
    reg_bit_set(CANDS_CTL0_(31)+chn_offset, 24,1,0);

    //***********************mode register vale*****************//
    //mr1_data cs0
	reg_bit_set(CANDS_CTL0_(206)+chn_offset, 0,8,f0_timing->MR1_DATA);
	reg_bit_set(CANDS_CTL0_(206)+chn_offset, 16,8,f1_timing->MR1_DATA);
	reg_bit_set(CANDS_CTL0_(207)+chn_offset, 0,8,f2_timing->MR1_DATA);
	reg_bit_set(CANDS_CTL0_(207)+chn_offset, 16,8,f3_timing->MR1_DATA);
	reg_bit_set(CANDS_CTL0_(208)+chn_offset, 0,8,f4_timing->MR1_DATA);
	//mr1_data cs1
	reg_bit_set(CANDS_CTL0_(217)+chn_offset, 16,8,f0_timing->MR1_DATA);
	reg_bit_set(CANDS_CTL0_(218)+chn_offset, 0,8,f1_timing->MR1_DATA);
	reg_bit_set(CANDS_CTL0_(218)+chn_offset, 16,8,f2_timing->MR1_DATA);
	reg_bit_set(CANDS_CTL0_(219)+chn_offset, 0,8,f3_timing->MR1_DATA);
	reg_bit_set(CANDS_CTL0_(219)+chn_offset, 16,8,f4_timing->MR1_DATA);

	 //mr2_data cs0
	reg_bit_set(CANDS_CTL0_(206)+chn_offset, 8,8,f0_timing->MR2_DATA);
	reg_bit_set(CANDS_CTL0_(206)+chn_offset, 24,8,f1_timing->MR2_DATA);
	reg_bit_set(CANDS_CTL0_(207)+chn_offset, 8,8,f2_timing->MR2_DATA);
	reg_bit_set(CANDS_CTL0_(207)+chn_offset, 24,8,f3_timing->MR2_DATA);
	reg_bit_set(CANDS_CTL0_(208)+chn_offset, 8,8,f4_timing->MR2_DATA);
	//mr2_data cs1
	reg_bit_set(CANDS_CTL0_(217)+chn_offset, 24,8,f0_timing->MR2_DATA);
	reg_bit_set(CANDS_CTL0_(218)+chn_offset, 8,8,f1_timing->MR2_DATA);
	reg_bit_set(CANDS_CTL0_(218)+chn_offset, 24,8,f2_timing->MR2_DATA);
	reg_bit_set(CANDS_CTL0_(219)+chn_offset, 8,8,f3_timing->MR2_DATA);
	reg_bit_set(CANDS_CTL0_(219)+chn_offset, 24,8,f4_timing->MR2_DATA);

	 //mr3_data cs0
	reg_bit_set(CANDS_CTL0_(208)+chn_offset, 24,8,f0_timing->MR3_DATA);
	reg_bit_set(CANDS_CTL0_(209)+chn_offset, 0,8,f1_timing->MR3_DATA);
	reg_bit_set(CANDS_CTL0_(209)+chn_offset, 8,8,f2_timing->MR3_DATA);
	reg_bit_set(CANDS_CTL0_(209)+chn_offset, 16,8,f3_timing->MR3_DATA);
	reg_bit_set(CANDS_CTL0_(209)+chn_offset, 24,8,f4_timing->MR3_DATA);
	//mr3_data cs1
	reg_bit_set(CANDS_CTL0_(220)+chn_offset, 8,8,f0_timing->MR3_DATA);
	reg_bit_set(CANDS_CTL0_(220)+chn_offset, 16,8,f1_timing->MR3_DATA);
	reg_bit_set(CANDS_CTL0_(220)+chn_offset, 24,8,f2_timing->MR3_DATA);
	reg_bit_set(CANDS_CTL0_(221)+chn_offset, 0,8,f3_timing->MR3_DATA);
	reg_bit_set(CANDS_CTL0_(221)+chn_offset, 8,8,f4_timing->MR3_DATA);

	 //mr11_data cs0
	reg_bit_set(CANDS_CTL0_(210)+chn_offset, 8,8,f0_timing->MR11_DATA);
	reg_bit_set(CANDS_CTL0_(210)+chn_offset, 16,8,f1_timing->MR11_DATA);
	reg_bit_set(CANDS_CTL0_(210)+chn_offset, 24,8,f2_timing->MR11_DATA);
	reg_bit_set(CANDS_CTL0_(211)+chn_offset, 0,8,f3_timing->MR11_DATA);
	reg_bit_set(CANDS_CTL0_(211)+chn_offset, 8,8,f4_timing->MR11_DATA);
	//mr11_data cs1
	reg_bit_set(CANDS_CTL0_(221)+chn_offset, 24,8,f0_timing->MR11_DATA);
	reg_bit_set(CANDS_CTL0_(222)+chn_offset, 0,8,f1_timing->MR11_DATA);
	reg_bit_set(CANDS_CTL0_(222)+chn_offset, 8,8,f2_timing->MR11_DATA);
	reg_bit_set(CANDS_CTL0_(222)+chn_offset, 16,8,f3_timing->MR11_DATA);
	reg_bit_set(CANDS_CTL0_(222)+chn_offset, 24,8,f4_timing->MR11_DATA);

	//mr13
	reg_bit_set(CANDS_CTL0_(212)+chn_offset, 24,8,0xc0);
	reg_bit_set(CANDS_CTL0_(224)+chn_offset, 8,8,0xc0);
	#ifdef DRAM_LPDDR4
	//mr13_data
	//CS0
	reg_bit_set(CANDS_CTL0_(212)+chn_offset,30,1,FSP_WR);
	reg_bit_set(CANDS_CTL0_(212)+chn_offset,31,1,FSP_OP);
	//CS1
	reg_bit_set(CANDS_CTL0_(224)+chn_offset,14,1,FSP_WR);
	reg_bit_set(CANDS_CTL0_(224)+chn_offset,15,1,FSP_OP);
	#endif

	 //mr12_data cs0
	reg_bit_set(CANDS_CTL0_(211)+chn_offset, 16,8,f0_timing->MR12_DATA);
	reg_bit_set(CANDS_CTL0_(211)+chn_offset, 24,8,f1_timing->MR12_DATA);
	reg_bit_set(CANDS_CTL0_(212)+chn_offset, 0,8,f2_timing->MR12_DATA);
	reg_bit_set(CANDS_CTL0_(212)+chn_offset, 8,8,f3_timing->MR12_DATA);
	reg_bit_set(CANDS_CTL0_(212)+chn_offset, 16,8,f4_timing->MR12_DATA);
	//mr12_data cs1
	reg_bit_set(CANDS_CTL0_(223)+chn_offset, 0,8,f0_timing->MR12_DATA);
	reg_bit_set(CANDS_CTL0_(223)+chn_offset, 8,8,f1_timing->MR12_DATA);
	reg_bit_set(CANDS_CTL0_(223)+chn_offset, 16,8,f2_timing->MR12_DATA);
	reg_bit_set(CANDS_CTL0_(223)+chn_offset, 24,8,f3_timing->MR12_DATA);
	reg_bit_set(CANDS_CTL0_(224)+chn_offset, 0,8,f4_timing->MR12_DATA);

	 //mr14_data cs0
	reg_bit_set(CANDS_CTL0_(213)+chn_offset, 0,8,f0_timing->MR14_DATA);
	reg_bit_set(CANDS_CTL0_(213)+chn_offset, 8,8,f1_timing->MR14_DATA);
	reg_bit_set(CANDS_CTL0_(213)+chn_offset, 16,8,f2_timing->MR14_DATA);
	reg_bit_set(CANDS_CTL0_(213)+chn_offset, 24,8,f3_timing->MR14_DATA);
	reg_bit_set(CANDS_CTL0_(214)+chn_offset, 0,8,f4_timing->MR14_DATA);
	//mr14_data cs1
	reg_bit_set(CANDS_CTL0_(224)+chn_offset, 16,8,f0_timing->MR14_DATA);
	reg_bit_set(CANDS_CTL0_(224)+chn_offset, 24,8,f1_timing->MR14_DATA);
	reg_bit_set(CANDS_CTL0_(225)+chn_offset, 0,8,f2_timing->MR14_DATA);
	reg_bit_set(CANDS_CTL0_(225)+chn_offset, 8,8,f3_timing->MR14_DATA);
	reg_bit_set(CANDS_CTL0_(225)+chn_offset, 16,8,f4_timing->MR14_DATA);

	//mrr_tempchk_high_threshold_fN
	reg_bit_set(CANDS_CTL0_(131)+chn_offset, 0,16,f0_timing->MRR_TEMPCHK_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(132)+chn_offset, 16,16,f1_timing->MRR_TEMPCHK_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(134)+chn_offset, 0,16,f2_timing->MRR_TEMPCHK_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(135)+chn_offset, 16,16,f3_timing->MRR_TEMPCHK_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(137)+chn_offset, 0,16,f4_timing->MRR_TEMPCHK_HIGH_THRESHOLD);
	//mrr_tempchk_norm_threshold_fN
	reg_bit_set(CANDS_CTL0_(130)+chn_offset, 16,16,f0_timing->MRR_TEMPCHK_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(132)+chn_offset, 0,16,f1_timing->MRR_TEMPCHK_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(133)+chn_offset, 16,16,f2_timing->MRR_TEMPCHK_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(135)+chn_offset, 0,16,f3_timing->MRR_TEMPCHK_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(136)+chn_offset, 16,16,f4_timing->MRR_TEMPCHK_NORM_THRESHOLD);
	//mrr_tempchk_timeout_fN
	reg_bit_set(CANDS_CTL0_(131)+chn_offset, 16,16,f0_timing->MRR_TEMPCHK_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(133)+chn_offset, 0,16,f1_timing->MRR_TEMPCHK_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(134)+chn_offset, 16,16,f2_timing->MRR_TEMPCHK_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(136)+chn_offset, 0,16,f3_timing->MRR_TEMPCHK_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(137)+chn_offset, 16,16,f4_timing->MRR_TEMPCHK_TIMEOUT);
	//mrr_promote_threshold_fN
	reg_bit_set(CANDS_CTL0_(201)+chn_offset, 0,16,f0_timing->MRR_PROMOTE_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(201)+chn_offset, 16,16,f1_timing->MRR_PROMOTE_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(202)+chn_offset, 0,16,f2_timing->MRR_PROMOTE_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(202)+chn_offset, 16,16,f3_timing->MRR_PROMOTE_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(203)+chn_offset, 0,16,f4_timing->MRR_PROMOTE_THRESHOLD);
    //mrw_promote_threshold_fN
    reg_bit_set(CANDS_CTL0_(203)+chn_offset, 16,16,f0_timing->MRW_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(204)+chn_offset, 0,16,f1_timing->MRW_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(204)+chn_offset, 16,16,f2_timing->MRW_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(205)+chn_offset, 0,16,f3_timing->MRW_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(205)+chn_offset, 16,16,f4_timing->MRW_PROMOTE_THRESHOLD);

            //cs0 mr22_data
      reg_bit_set(CANDS_CTL0_(216)+chn_offset, 8,8,(f0_timing->MR22_DATA));
	reg_bit_set(CANDS_CTL0_(216)+chn_offset, 16, 8,(f1_timing->MR22_DATA));
	reg_bit_set(CANDS_CTL0_(216)+chn_offset, 24, 8,(f2_timing->MR22_DATA));
	reg_bit_set(CANDS_CTL0_(217)+chn_offset, 0, 8,(f3_timing->MR22_DATA));
	reg_bit_set(CANDS_CTL0_(217)+chn_offset, 8, 8,(f4_timing->MR22_DATA));
	//cs1 mr22_data
    reg_bit_set(CANDS_CTL0_(227)+chn_offset, 24, 8,(f0_timing->MR22_DATA));
    reg_bit_set(CANDS_CTL0_(228)+chn_offset, 0, 8,(f1_timing->MR22_DATA));
    reg_bit_set(CANDS_CTL0_(228)+chn_offset, 8, 8,(f2_timing->MR22_DATA));
    reg_bit_set(CANDS_CTL0_(228)+chn_offset, 16, 8,(f3_timing->MR22_DATA));
    reg_bit_set(CANDS_CTL0_(228)+chn_offset, 24, 8,(f4_timing->MR22_DATA));
}

void cands_ctl_othertiming_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_CTL_TIMING_T * ctl_timing,
							    uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;
	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

	//CA_DEFAULT_VAL
    reg_bit_set(CANDS_CTL0_(41)+chn_offset, 24, 1, (f0_timing->CA_DEFAULT_VAL));
    reg_bit_set(CANDS_CTL0_(43)+chn_offset, 16, 1, (f1_timing->CA_DEFAULT_VAL));
    reg_bit_set(CANDS_CTL0_(45)+chn_offset, 8, 1, (f2_timing->CA_DEFAULT_VAL));
    reg_bit_set(CANDS_CTL0_(47)+chn_offset, 0, 1, (f3_timing->CA_DEFAULT_VAL));
    reg_bit_set(CANDS_CTL0_(48)+chn_offset, 24, 1, (f4_timing->CA_DEFAULT_VAL));
    //DFS_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(105)+chn_offset, 16,16, (f0_timing->DFS_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(106)+chn_offset, 0,16, (f1_timing->DFS_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(106)+chn_offset, 16,16, (f2_timing->DFS_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(107)+chn_offset, 0,16, (f3_timing->DFS_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(107)+chn_offset, 16,16, (f4_timing->DFS_PROMOTE_THRESHOLD));

    //HW_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(156)+chn_offset,0,16, (f0_timing->HW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(156)+chn_offset,16,16, (f1_timing->HW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(157)+chn_offset,0,16, (f2_timing->HW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(157)+chn_offset,16,16, (f3_timing->HW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(158)+chn_offset,0,16, (f4_timing->HW_PROMOTE_THRESHOLD));

    //LPC_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(158)+chn_offset, 16,16, (f0_timing->LPC_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(159)+chn_offset, 0,16, (f1_timing->LPC_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(159)+chn_offset, 16,16, (f2_timing->LPC_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(160)+chn_offset, 0,16, (f3_timing->LPC_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(160)+chn_offset, 16,16, (f4_timing->LPC_PROMOTE_THRESHOLD));

	//PHYMSTR_DFI_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(123)+chn_offset,16,16, (f0_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(125)+chn_offset,0,16, (f1_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(126)+chn_offset,16,16, (f2_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(128)+chn_offset,0,16, (f3_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(129)+chn_offset,16,16, (f4_timing->PHYMSTR_DFI_PROMOTE_THRESHOLD));

    //UPD_CTRLUPD_HIGH_THRESHOLD
    reg_bit_set(CANDS_CTL0_(110)+chn_offset, 16,16, (f0_timing->UPD_CTRLUPD_HIGH_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(113)+chn_offset, 0,16, (f1_timing->UPD_CTRLUPD_HIGH_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(115)+chn_offset, 16,16, (f2_timing->UPD_CTRLUPD_HIGH_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(118)+chn_offset, 0,16, (f3_timing->UPD_CTRLUPD_HIGH_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(120)+chn_offset, 16,16, (f4_timing->UPD_CTRLUPD_HIGH_THRESHOLD));

    //UPD_CTRLUPD_NORM_THRESHOLD
    reg_bit_set(CANDS_CTL0_(110)+chn_offset,0,16, (f0_timing->UPD_CTRLUPD_NORM_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(112)+chn_offset,16,16, (f1_timing->UPD_CTRLUPD_NORM_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(115)+chn_offset,0,16, (f2_timing->UPD_CTRLUPD_NORM_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(117)+chn_offset,16,16, (f3_timing->UPD_CTRLUPD_NORM_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(120)+chn_offset,0,16, (f4_timing->UPD_CTRLUPD_NORM_THRESHOLD));

    //UPD_CTRLUPD_SW_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(111)+chn_offset, 16,16, (f0_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(114)+chn_offset, 0,16, (f1_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(116)+chn_offset, 16,16, (f2_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(119)+chn_offset, 0,16, (f3_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(121)+chn_offset, 16,16, (f4_timing->UPD_CTRLUPD_SW_PROMOTE_THRESHOLD));

    //UPD_CTRLUPD_TIMEOUT
    reg_bit_set(CANDS_CTL0_(111)+chn_offset,0,16, (f0_timing->UPD_CTRLUPD_TIMEOUT));
    reg_bit_set(CANDS_CTL0_(113)+chn_offset,16,16, (f1_timing->UPD_CTRLUPD_TIMEOUT));
    reg_bit_set(CANDS_CTL0_(116)+chn_offset,0,16, (f2_timing->UPD_CTRLUPD_TIMEOUT));
    reg_bit_set(CANDS_CTL0_(118)+chn_offset,16,16, (f3_timing->UPD_CTRLUPD_TIMEOUT));
    reg_bit_set(CANDS_CTL0_(121)+chn_offset,0,16, (f4_timing->UPD_CTRLUPD_TIMEOUT));

    //UPD_PHYUPD_DFI_PROMOTE_THRESHOLD
    reg_bit_set(CANDS_CTL0_(112)+chn_offset,0,16, (f0_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(114)+chn_offset,16,16, (f1_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(117)+chn_offset,0,16, (f2_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(119)+chn_offset,16,16, (f3_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));
    reg_bit_set(CANDS_CTL0_(122)+chn_offset,0,16, (f4_timing->UPD_PHYUPD_DFI_PROMOTE_THRESHOLD));

}

void cands_ctl_odt_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,
						uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_ctl_timing_map(TIMING_SET_SUM,ctl_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_CTL_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_CTL_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_CTL_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_CTL_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_CTL_TIMING_T *)(temp_fn[4]);

    //en_odt_assert_except_rd    ?????? lp4 1200 need odt ???
    reg_bit_set(CANDS_CTL0_(317)+chn_offset,8,1,0); //Enables the controller to assert ODT at all times except during reads.

    //odt_en_fN
    reg_bit_set(CANDS_CTL0_(316)+chn_offset,0,1, f0_timing->ODT_EN); //f0
    reg_bit_set(CANDS_CTL0_(316)+chn_offset,8,1, f1_timing->ODT_EN); //f1
    reg_bit_set(CANDS_CTL0_(316)+chn_offset,16,1, f2_timing->ODT_EN); //f2
    reg_bit_set(CANDS_CTL0_(316)+chn_offset,24,1, f3_timing->ODT_EN); //f3
    reg_bit_set(CANDS_CTL0_(317)+chn_offset,0,1, f4_timing->ODT_EN); //f4

    //odt_rd_map_csX  ????????
    reg_bit_set(CANDS_CTL0_(313)+chn_offset, 8,2, 0x01); //cs0
    reg_bit_set(CANDS_CTL0_(313)+chn_offset,24,2, 0x02); //cs1
    //odt_wr_map_csX   ????????
    reg_bit_set(CANDS_CTL0_(313)+chn_offset, 16,2, 0x01); //cs0
    reg_bit_set(CANDS_CTL0_(314)+chn_offset,0,2, 0x02); //cs1

    //RD_TO_ODT
    reg_bit_set(CANDS_CTL0_(318)+chn_offset, 24, 6,f0_timing->RD_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(319)+chn_offset, 0, 6,f1_timing->RD_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(319)+chn_offset, 8, 6,f2_timing->RD_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(319)+chn_offset, 16, 6,f3_timing->RD_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(319)+chn_offset, 24, 6,f4_timing->RD_TO_ODTH);

    //WR_TO_ODT
    reg_bit_set(CANDS_CTL0_(317)+chn_offset,16, 6,f0_timing->WR_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(317)+chn_offset,24, 6,f1_timing->WR_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(318)+chn_offset,0, 6,f2_timing->WR_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(318)+chn_offset,8, 6,f3_timing->WR_TO_ODTH);
	reg_bit_set(CANDS_CTL0_(318)+chn_offset,16, 6,f4_timing->WR_TO_ODTH);

    //TODTH_RD
    reg_bit_set(CANDS_CTL0_(315)+chn_offset,24, 4,f0_timing->TODTH_RD);
    //TODTH_WR
    reg_bit_set(CANDS_CTL0_(315)+chn_offset, 16, 4,f0_timing->TODTH_WR);
    //TODTH_2CMD

	for(i=0;i < 5; i++) {
		//reg_bit_set(CANDS_CTL0_(548+65*i)+chn_offset, 0, 8,timing[i]->TODTL_2CMD);
	}

    reg_bit_set(CANDS_CTL0_(314)+chn_offset, 8, 8,f0_timing->TODTL_2CMD);
    reg_bit_set(CANDS_CTL0_(314)+chn_offset, 16, 8,f1_timing->TODTL_2CMD);
    reg_bit_set(CANDS_CTL0_(314)+chn_offset, 24, 8,f2_timing->TODTL_2CMD);
    reg_bit_set(CANDS_CTL0_(315)+chn_offset, 0, 8,f3_timing->TODTL_2CMD);
    reg_bit_set(CANDS_CTL0_(315)+chn_offset, 8, 8,f4_timing->TODTL_2CMD);

}


void cands_ctl_qos_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type, CANDS_CTL_PERCHN_QOS_T* perchn_qos,CANDS_CTL_ALLCHN_QOS_T* allchn_qos)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
    	uint32 i = 0;

    	//age_count
    	reg_bit_set(CANDS_CTL0_(281)+chn_offset,0,8,allchn_qos->age_count); //should check !!!

    	//addr_cmp_en
	reg_bit_set(CANDS_CTL0_(281)+chn_offset,16,1,allchn_qos->addr_cmp_en);

	//reversed
	//reg_bit_set(CANDS_CTL0_(309)+chn_offset,16,1,1);

	//ap
	reg_bit_set(CANDS_CTL0_(65)+chn_offset,24,1,allchn_qos->ap);     //disable auto pre-charge mode for DRAM memories

    //arb_cmd_q_threshold
    reg_bit_set(CANDS_CTL0_(409)+chn_offset,0,5,allchn_qos->arb_cmd_q_shreshold); //should check !!!

    //bank_split_en
    reg_bit_set(CANDS_CTL0_(282)+chn_offset,0, 1,allchn_qos->bank_split_en);

    //command_age_count
    reg_bit_set(CANDS_CTL0_(281)+chn_offset, 8,8,allchn_qos->cmd_age_count); //should check !!!

    //cs_same_en
    reg_bit_set(CANDS_CTL0_(283)+chn_offset, 8, 1,allchn_qos->cs_same_en);

    //w2r_split_en
    reg_bit_set(CANDS_CTL0_(283)+chn_offset, 16, 1,allchn_qos->w2r_split_en);

    //disable_rd_interleave
    reg_bit_set(CANDS_CTL0_(284)+chn_offset, 16, 1, allchn_qos->disable_rd_interleave);

    //disable_rw_group_w_bnk_conflict
    reg_bit_set(CANDS_CTL0_(283)+chn_offset,24, 2, allchn_qos->disable_rw_group_bank_conflit);
    //inhibit_dram_cmd
    reg_bit_set(CANDS_CTL0_(284)+chn_offset,24, 2, allchn_qos->inhibit_dram_en);

    //in_order_accept
    reg_bit_set(CANDS_CTL0_(288)+chn_offset,8, 1, allchn_qos->in_order_accept);

    //num_q_entries_act_disable
    reg_bit_set(CANDS_CTL0_(284)+chn_offset,0, 5, allchn_qos->num_q_entries_act_disable); //should check !!!

    //placement_en
    reg_bit_set(CANDS_CTL0_(282)+chn_offset, 8, 1, allchn_qos->placement_en);

    //priority_en
    reg_bit_set(CANDS_CTL0_(282)+chn_offset, 16, 1, allchn_qos->priority_en);

    //q_fullness, should check ???
    reg_bit_set(CANDS_CTL0_(288)+chn_offset, 0, 5, allchn_qos->q_fullness);

    //rw_same_en
    reg_bit_set(CANDS_CTL0_(282)+chn_offset,24, 1, allchn_qos->rw_same_en);

    //rw_same_page_en
    reg_bit_set(CANDS_CTL0_(283)+chn_offset,0, 1, allchn_qos->rw_same_page_en);

    //swap_en
    reg_bit_set(CANDS_CTL0_(284)+chn_offset, 8, 1, allchn_qos->swap_en);

    //wr_order_req
    reg_bit_set(CANDS_CTL0_(288)+chn_offset, 16,2,allchn_qos->wr_order_req); //Bit [1] = Port ID usage, Bit [0] = Source ID usage, should check

    //axiY_r_priority
    reg_bit_set(CANDS_CTL0_(402)+chn_offset,0,4,perchn_qos[0].r_priority);
    reg_bit_set(CANDS_CTL0_(403)+chn_offset,8,4,perchn_qos[1].r_priority);
    reg_bit_set(CANDS_CTL0_(404)+chn_offset,16,4,perchn_qos[2].r_priority);
    reg_bit_set(CANDS_CTL0_(405)+chn_offset,24,4,perchn_qos[3].r_priority);
    reg_bit_set(CANDS_CTL0_(407)+chn_offset,0,4,perchn_qos[4].r_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(408)+chn_offset,8,4,perchn_qos[5].r_priority); //should check !!!

    //axiY_w_priority
    reg_bit_set(CANDS_CTL0_(402)+chn_offset, 8,4,perchn_qos[0].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(403)+chn_offset, 16,4,perchn_qos[1].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(404)+chn_offset, 24,4,perchn_qos[2].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(406)+chn_offset, 0,4,perchn_qos[3].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(407)+chn_offset, 8,4,perchn_qos[4].w_priority); //should check !!!
    reg_bit_set(CANDS_CTL0_(408)+chn_offset, 16,4,perchn_qos[5].w_priority); //should check !!!

    //axiY_bdw, should check !!!
    reg_bit_set(CANDS_CTL0_(409)+chn_offset,8,7,perchn_qos[0].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(410)+chn_offset,0,7,perchn_qos[1].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(410)+chn_offset, 24,7,perchn_qos[2].bdw); //should check !!!
    reg_bit_set(CANDS_CTL0_(411)+chn_offset, 16,7,perchn_qos[3].bdw); //should check !!!

    //axiY_bdw_overflow, should check !!!
    reg_bit_set(CANDS_CTL0_(409)+chn_offset, 16,1,perchn_qos[0].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(410)+chn_offset,8,1,perchn_qos[1].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(411)+chn_offset,0,1,perchn_qos[2].bdw_overflow); //should check !!!
    reg_bit_set(CANDS_CTL0_(411)+chn_offset, 24,1,perchn_qos[3].bdw_overflow); //should check !!!

	if(chn_num==0)
	{
	    reg_bit_set(CANDS_CTL0_(412)+chn_offset,8,7,perchn_qos[4].bdw); //should check !!!
	    reg_bit_set(CANDS_CTL0_(413)+chn_offset,0,7,perchn_qos[5].bdw); //should check !!!
	    reg_bit_set(CANDS_CTL0_(412)+chn_offset, 16,1,perchn_qos[4].bdw_overflow); //should check !!!
	    reg_bit_set(CANDS_CTL0_(413)+chn_offset,8,1,perchn_qos[5].bdw_overflow); //should check !!!
	}
	else
	{
	    reg_bit_set(CANDS_CTL0_(412)+chn_offset,8,7,0); //axi4_bdw
	    reg_bit_set(CANDS_CTL0_(413)+chn_offset,0,7,0); //axi5_bdw
	    reg_bit_set(CANDS_CTL0_(412)+chn_offset, 16,1,0); //axi4_bdw_ovflow   pub1 do not use this port
	    reg_bit_set(CANDS_CTL0_(413)+chn_offset,8,1,0); //axi5_bdw_ovflow	  pub1 do not use this port
	}

    //axiY_fixed_prot_priority_enable  ??? fixed use axiY_r/w_priority of use axiY_AR/AWQOS ??? should check----CHANGE
    reg_bit_set(CANDS_CTL0_(401)+chn_offset,24,1,perchn_qos[0].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(403)+chn_offset, 0,1,perchn_qos[1].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(404)+chn_offset, 8,1,perchn_qos[2].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(405)+chn_offset,16,1,perchn_qos[3].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(406)+chn_offset,24,1,perchn_qos[4].fixed_priority_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(408)+chn_offset, 0,1,perchn_qos[5].fixed_priority_en); //should check !!!

    //axiY_all_strobes_used_enable
	reg_bit_set(CANDS_CTL0_(401)+chn_offset,16,1,perchn_qos[0].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(402)+chn_offset,24,1,perchn_qos[1].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(404)+chn_offset,0,1,perchn_qos[2].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(405)+chn_offset,8,1,perchn_qos[3].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(406)+chn_offset,16,1,perchn_qos[4].all_strobes_used_en); //should check !!!
    reg_bit_set(CANDS_CTL0_(407)+chn_offset,24,1,perchn_qos[5].all_strobes_used_en); //should check !!!

    //axiY_fifo_type_reg
    reg_bit_set(CANDS_CTL0_(402)+chn_offset, 16, 2, perchn_qos[0].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(403)+chn_offset, 24, 2, perchn_qos[1].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(405)+chn_offset, 0, 2, perchn_qos[2].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(406)+chn_offset, 8, 2, perchn_qos[3].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(407)+chn_offset, 16, 2, perchn_qos[4].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2
    reg_bit_set(CANDS_CTL0_(408)+chn_offset, 24, 2, perchn_qos[5].fifo_type_reg);// 0:Asynchronous  3:Synchronous, only support synchronous on whale2

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
	reg_bit_set(CANDS_CTL0_(351)+chn_offset,24,1, 1);
	//rdlvl_cs
	reg_bit_set(CANDS_CTL0_(349)+chn_offset,16,1, 0);
	//rdlvl_cs_map
	reg_bit_set(CANDS_CTL0_(353)+chn_offset,0,2, IS_2CS(ddr_type)?3:1);
	//rdlvl_en
	reg_bit_set(CANDS_CTL0_(459)+chn_offset, 8,1, RDELVL_EN);
	//rdlvl_on_sref_exit
	reg_bit_set(CANDS_CTL0_(351)+chn_offset, 0,1, RDELVL_EN_DFS);
	//rdlvl_periodic
	reg_bit_set(CANDS_CTL0_(350)+chn_offset,24,1, 0);
    //rdlvl_rotate
    reg_bit_set(CANDS_CTL0_(352)+chn_offset,16,1, 0); //0:train all cs   1:train only one cs
    //rdlvl_seq_en
    reg_bit_set(CANDS_CTL0_(349)+chn_offset,24,4, 0); //calvl pattern sequence   3:pattern 0->1->2->3->0

    //rdlvl_gate_aref_en
	reg_bit_set(CANDS_CTL0_(352)+chn_offset, 0,1, 1);
	//rdlvl_gate_cs_map
	reg_bit_set(CANDS_CTL0_(353)+chn_offset, 8,2, IS_2CS(ddr_type)?3:1);
	//rdlvl_gate_en
	reg_bit_set(CANDS_CTL0_(459)+chn_offset,16,1, RDGLVL_EN);
	//rdlvl_gate_on_sref_exit
	reg_bit_set(CANDS_CTL0_(351)+chn_offset,16,1, RDGLVL_EN_SREF);
	//rdlvl_gate_periodic
	reg_bit_set(CANDS_CTL0_(351)+chn_offset, 8,1, 0);
    //rdlvl_gate_rotate
    reg_bit_set(CANDS_CTL0_(352)+chn_offset,24,1, 0); //0:train all cs   1:train only one cs
    //rdlvl_gate_seq_en
    reg_bit_set(CANDS_CTL0_(350)+chn_offset, 0,4, 0); //calvl pattern sequence   3:pattern 0->1->2->3->0
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
	reg_bit_set(CANDS_CTL0_(335)+chn_offset, 16,1, 1);
	//wrlvl_cs
	reg_bit_set(CANDS_CTL0_(333)+chn_offset, 16,1, 0);
	//wrlvl_cs_map
	reg_bit_set(CANDS_CTL0_(336)+chn_offset, 0,2, IS_2CS(ddr_type)?3:1);
	//wrlvl_en
	reg_bit_set(CANDS_CTL0_(334)+chn_offset, 8,1, WRLVL_EN);
	//wrlvl_on_sref_exit
	reg_bit_set(CANDS_CTL0_(335)+chn_offset,0,1, WRLVL_EN_SREF);
	//wrlvl_periodic
	reg_bit_set(CANDS_CTL0_(334)+chn_offset,24,1, 0);
    //wrlvl_resp_mask
    reg_bit_set(CANDS_CTL0_(335)+chn_offset, 8, 4, 0);
    //wrlvl_rotate
    reg_bit_set(CANDS_CTL0_(335)+chn_offset,24,1, 0); //0:train all cs   1:train only one cs

}

void cands_ctl_zq_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * ctl_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_CTL_TIMING_T * f0_timing = NULL;
	CANDS_CTL_TIMING_T * f1_timing = NULL;
	CANDS_CTL_TIMING_T * f2_timing = NULL;
	CANDS_CTL_TIMING_T * f3_timing = NULL;
	CANDS_CTL_TIMING_T * f4_timing = NULL;
	CANDS_CTL_TIMING_T ** timing = (CANDS_CTL_TIMING_T ** )temp_fn;

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
	reg_bit_set(CANDS_CTL0_(473)+chn_offset,16,1,(chn_num==0)?1:0);
	//#ifdef DRAM_LPDDR4
	//reg_bit_set(CANDS_CTL0_(509)+chn_offset,16,1,1);
	//reg_bit_set(CANDS_CTL0_(509)+chn_offset,24,1,1);
	//reg_bit_set(CANDS_CTL0_(510)+chn_offset, 0,1,1);
	//#endif
	//no_zq_init
	reg_bit_set(CANDS_CTL0_(278)+chn_offset,0,1,ZQ_EN);

	//zqcs_rotate only for lpddr3
	reg_bit_set(CANDS_CTL0_(278)+chn_offset,8,1, 1);  //0: all cs will be zqcs cal  1: one cs will be zqcs cal(on round-robin)

	#ifdef DRAM_LPDDR4
	//zq_cal_latch_map  ??????
	reg_bit_set(CANDS_CTL0_(278)+chn_offset, 24,2, 1);
	reg_bit_set(CANDS_CTL0_(279)+chn_offset,8,2, IS_2CS(ddr_type)?2:0);
	//zq_cal_start_map   ??????
	reg_bit_set(CANDS_CTL0_(278)+chn_offset, 16,2, 1);
	reg_bit_set(CANDS_CTL0_(279)+chn_offset,0,2, IS_2CS(ddr_type)?2:0);
	#else
	//zq_cal_latch_map  ??????
	reg_bit_set(CANDS_CTL0_(278)+chn_offset, 24,2, 0);
	reg_bit_set(CANDS_CTL0_(279)+chn_offset,8,2, 0);
	//zq_cal_start_map   ??????
	reg_bit_set(CANDS_CTL0_(278)+chn_offset, 16,2, 0);
	reg_bit_set(CANDS_CTL0_(279)+chn_offset,0,2, 0);
	#endif

	//zq_callatch_high_threshold
	reg_bit_set(CANDS_CTL0_(240)+chn_offset, 16,16, f0_timing->ZQ_CALLATCH_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(245)+chn_offset, 0,16, f1_timing->ZQ_CALLATCH_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(249)+chn_offset, 16,16, f2_timing->ZQ_CALLATCH_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(254)+chn_offset, 0,16, f3_timing->ZQ_CALLATCH_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(258)+chn_offset, 16,16, f4_timing->ZQ_CALLATCH_HIGH_THRESHOLD);
    //zq_callatch_timeout
	reg_bit_set(CANDS_CTL0_(242)+chn_offset, 16,16, f0_timing->ZQ_CALLATCH_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(247)+chn_offset, 0,16, f1_timing->ZQ_CALLATCH_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(251)+chn_offset, 16,16, f2_timing->ZQ_CALLATCH_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(256)+chn_offset, 0,16, f3_timing->ZQ_CALLATCH_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(260)+chn_offset, 16,16, f4_timing->ZQ_CALLATCH_TIMEOUT);
    //zq_calstart_high_threshold
	reg_bit_set(CANDS_CTL0_(240)+chn_offset,  0,16, f0_timing->ZQ_CALSTART_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(244)+chn_offset,  16,16, f1_timing->ZQ_CALSTART_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(249)+chn_offset,  0,16, f2_timing->ZQ_CALSTART_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(253)+chn_offset,  16,16, f3_timing->ZQ_CALSTART_HIGH_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(258)+chn_offset,  0,16, f4_timing->ZQ_CALSTART_HIGH_THRESHOLD);

    //zq_calstart_norm_threshold
	reg_bit_set(CANDS_CTL0_(239)+chn_offset,  8,16, f0_timing->ZQ_CALSTART_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(244)+chn_offset,  0,16, f1_timing->ZQ_CALSTART_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(248)+chn_offset,  16,16, f2_timing->ZQ_CALSTART_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(253)+chn_offset,  0,16, f3_timing->ZQ_CALSTART_NORM_THRESHOLD);
	reg_bit_set(CANDS_CTL0_(257)+chn_offset,  16,16, f4_timing->ZQ_CALSTART_NORM_THRESHOLD);

    //zq_calstart_timeout
	reg_bit_set(CANDS_CTL0_(242)+chn_offset, 0,16, f0_timing->ZQ_CALSTART_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(246)+chn_offset, 16,16, f1_timing->ZQ_CALSTART_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(251)+chn_offset, 0,16, f2_timing->ZQ_CALSTART_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(255)+chn_offset, 16,16, f3_timing->ZQ_CALSTART_TIMEOUT);
	reg_bit_set(CANDS_CTL0_(260)+chn_offset, 0,16, f4_timing->ZQ_CALSTART_TIMEOUT);

    //zq_cs_high_threshold
    reg_bit_set(CANDS_CTL0_(241)+chn_offset, 16,16, f0_timing->ZQ_CS_HIGH_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(246)+chn_offset, 0,16, f1_timing->ZQ_CS_HIGH_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(250)+chn_offset, 16,16, f2_timing->ZQ_CS_HIGH_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(255)+chn_offset, 0,16, f3_timing->ZQ_CS_HIGH_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(259)+chn_offset, 16,16, f4_timing->ZQ_CS_HIGH_THRESHOLD);

    //zq_cs_norm_threshold
    reg_bit_set(CANDS_CTL0_(241)+chn_offset,  0,16, f0_timing->ZQ_CS_NORM_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(245)+chn_offset,  16,16, f1_timing->ZQ_CS_NORM_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(250)+chn_offset,  0,16, f2_timing->ZQ_CS_NORM_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(254)+chn_offset,  16,16, f3_timing->ZQ_CS_NORM_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(259)+chn_offset,  0,16, f4_timing->ZQ_CS_NORM_THRESHOLD);

    //zq_cs_timeout
    reg_bit_set(CANDS_CTL0_(243)+chn_offset,  0,16, f0_timing->ZQ_CS_TIMEOUT);
    reg_bit_set(CANDS_CTL0_(247)+chn_offset,  16,16, f1_timing->ZQ_CS_TIMEOUT);
    reg_bit_set(CANDS_CTL0_(252)+chn_offset,  0,16, f2_timing->ZQ_CS_TIMEOUT);
    reg_bit_set(CANDS_CTL0_(256)+chn_offset,  16,16, f3_timing->ZQ_CS_TIMEOUT);
    reg_bit_set(CANDS_CTL0_(261)+chn_offset,  0,16, f4_timing->ZQ_CS_TIMEOUT);

    //zq_promote_threshold
    reg_bit_set(CANDS_CTL0_(243)+chn_offset, 16,16, f0_timing->ZQ_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(248)+chn_offset, 0,16, f1_timing->ZQ_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(252)+chn_offset, 16,16, f2_timing->ZQ_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(257)+chn_offset, 0,16, f3_timing->ZQ_PROMOTE_THRESHOLD);
    reg_bit_set(CANDS_CTL0_(261)+chn_offset, 16,16, f4_timing->ZQ_PROMOTE_THRESHOLD);

    //zqcs
    reg_bit_set(CANDS_CTL0_(263)+chn_offset, 16,12, f0_timing->ZQCS);
    reg_bit_set(CANDS_CTL0_(266)+chn_offset, 0,12, f1_timing->ZQCS);
    reg_bit_set(CANDS_CTL0_(268)+chn_offset, 16,12, f2_timing->ZQCS);
    reg_bit_set(CANDS_CTL0_(271)+chn_offset, 0,12, f3_timing->ZQCS);
    reg_bit_set(CANDS_CTL0_(273)+chn_offset, 16,12, f4_timing->ZQCS);

    //zqcl
    reg_bit_set(CANDS_CTL0_(263)+chn_offset,  0,12, f0_timing->ZQCL);
    reg_bit_set(CANDS_CTL0_(265)+chn_offset,  16,12, f1_timing->ZQCL);
    reg_bit_set(CANDS_CTL0_(268)+chn_offset,  0,12, f2_timing->ZQCL);
    reg_bit_set(CANDS_CTL0_(270)+chn_offset,  16,12, f3_timing->ZQCL);
    reg_bit_set(CANDS_CTL0_(273)+chn_offset,  0,12, f4_timing->ZQCL);

    //zqinit
    reg_bit_set(CANDS_CTL0_(262)+chn_offset, 8,12, f0_timing->ZQINIT);
    reg_bit_set(CANDS_CTL0_(265)+chn_offset, 0,12, f1_timing->ZQINIT);
    reg_bit_set(CANDS_CTL0_(267)+chn_offset, 8,12, f2_timing->ZQINIT);
    reg_bit_set(CANDS_CTL0_(270)+chn_offset, 0,12, f3_timing->ZQINIT);
    reg_bit_set(CANDS_CTL0_(272)+chn_offset, 8,12, f4_timing->ZQINIT);

    //zqreset
    reg_bit_set(CANDS_CTL0_(275)+chn_offset,  16,12, f0_timing->ZQRESET);
    reg_bit_set(CANDS_CTL0_(276)+chn_offset,  0,12, f1_timing->ZQRESET);
    reg_bit_set(CANDS_CTL0_(276)+chn_offset,  16,12, f2_timing->ZQRESET);
    reg_bit_set(CANDS_CTL0_(277)+chn_offset,  0,12, f3_timing->ZQRESET);
    reg_bit_set(CANDS_CTL0_(277)+chn_offset,  16,12, f4_timing->ZQRESET);

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

void cands_pi_seq_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 i = 0;
	#ifdef DRAM_LPDDR3
	//pi_seq1_pat
	reg_bit_set(CANDS_PI0_(39)+chn_offset, 0,28,0x7f003f0);
	//__raw_writel(CANDS_PI0_(39), 0xf7f003f0);
	//__raw_writel(CANDS_PI0_(40), 0xf);

	//pi_seq1_pat_msk
	reg_bit_set(CANDS_PI0_(40)+chn_offset, 0,28,0x7fff000);
	//__raw_writel(CANDS_PI0_(41), 0xf7fff000);
	//__raw_writel(CANDS_PI0_(42), 0x7);

	//pi_seq2_pat
	reg_bit_set(CANDS_PI0_(41)+chn_offset, 0,28,0x7f000a0);
	//__raw_writel(CANDS_PI0_(43), 0xf7f000a0);
	//__raw_writel(CANDS_PI0_(44), 0xf);

	//pi_seq2_pat_msk
	reg_bit_set(CANDS_PI0_(42)+chn_offset, 0,28,0x7fff000);
	//__raw_writel(CANDS_PI0_(45), 0xf7fff000);
	//__raw_writel(CANDS_PI0_(46), 0x7);

	//pi_seq3_pat
	reg_bit_set(CANDS_PI0_(43)+chn_offset, 0,28,0x7f00020);
	//__raw_writel(CANDS_PI0_(47), 0xf7f00020);
	//__raw_writel(CANDS_PI0_(48), 0xf);

	//pi_seq3_pat_msk
	reg_bit_set(CANDS_PI0_(44)+chn_offset, 0,28,0x7fff000);
	//__raw_writel(CANDS_PI0_(49), 0xf7fff000);
	//__raw_writel(CANDS_PI0_(50), 0x7);

	//pi_seq4_pat
	reg_bit_set(CANDS_PI0_(45)+chn_offset, 0,28,0x7f00030);
	//__raw_writel(CANDS_PI0_(51), 0xf7f00030);
	//__raw_writel(CANDS_PI0_(52), 0xf);

	//pi_seq4_pat_msk
	reg_bit_set(CANDS_PI0_(46)+chn_offset, 0,28,0x7fff000);
	//__raw_writel(CANDS_PI0_(53), 0xf7fff000);
	//__raw_writel(CANDS_PI0_(54), 0x7);

	//pi_seq5_pat
	reg_bit_set(CANDS_PI0_(47)+chn_offset, 0,28,0x7f000b0);
	//__raw_writel(CANDS_PI0_(55), 0xf7f000b0);
	//__raw_writel(CANDS_PI0_(56), 0xf);

	//pi_seq5_pat_msk
	reg_bit_set(CANDS_PI0_(48)+chn_offset, 0,28,0x7fff000);
	//__raw_writel(CANDS_PI0_(57), 0xf7fff000);
	//__raw_writel(CANDS_PI0_(58), 0x7);

	//pi_seq6_pat
	reg_bit_set(CANDS_PI0_(49)+chn_offset, 0,28,0x7f00100);
	//__raw_writel(CANDS_PI0_(59), 0xf7f00100);
	//__raw_writel(CANDS_PI0_(60), 0xf);

	//pi_seq6_pat_msk
	reg_bit_set(CANDS_PI0_(50)+chn_offset, 0,28,0x7fff000);
	//__raw_writel(CANDS_PI0_(61), 0xf7fff000);
	//__raw_writel(CANDS_PI0_(62), 0x7);

	//pi_seq7_pat
	reg_bit_set(CANDS_PI0_(51)+chn_offset, 0,28,0x7f00110);
	//__raw_writel(CANDS_PI0_(63), 0xf7f00110);
	//__raw_writel(CANDS_PI0_(64), 0xf);

	//pi_seq7_pat_msk
	reg_bit_set(CANDS_PI0_(52)+chn_offset, 0,28,0x7fff000);
	//__raw_writel(CANDS_PI0_(65), 0xf7fff000);
	//__raw_writel(CANDS_PI0_(66), 0x7);

	//pi_seq8_pat
	reg_bit_set(CANDS_PI0_(53)+chn_offset, 0,28,0x7f00010);
	//__raw_writel(CANDS_PI0_(67), 0xf7f00010);
	//__raw_writel(CANDS_PI0_(68), 0xf);

	//pi_seq8_pat_msk
	reg_bit_set(CANDS_PI0_(54)+chn_offset, 0,28,0x7fff000);
	//__raw_writel(CANDS_PI0_(69), 0xf7fff000);
	//reg_bit_set(CANDS_PI0_(70)+chn_offset,0,4,7);
	#else
	for(i = 0; i < 16; i++)
	{
		reg_bit_set(CANDS_PI0_(39+i)+chn_offset, 0,28,0);
	}

	//reg_bit_set(CANDS_PI0_(70)+chn_offset,0,4,0);
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
	reg_bit_set(CANDS_PI0_(55)+chn_offset,24,4,cs_map);

	//pi_tcmd_gap
	reg_bit_set(CANDS_PI0_(1)+chn_offset,16,16,0);

	//pi_exit_after_init_calvl
	reg_bit_set(CANDS_PI0_(36)+chn_offset,16,1,1);

	//pi_freq_map
	__raw_writel(CANDS_PI0_(37)+chn_offset, (PI_F4_TRAIN<<4)|(PI_F3_TRAIN<<3)|(PI_F2_TRAIN<<2)|(PI_F1_TRAIN<<1)|PI_F0_TRAIN); //  ???????

	//pi_init_work_freq
	reg_bit_set(CANDS_PI0_(38)+chn_offset,0,5, FN_PI_TARGET);

	//pi_init_dfs_calvl_only
	reg_bit_set(CANDS_PI0_(38)+chn_offset,8,1,0);

	//pi_power_on_seq_bypass_array
	reg_bit_set(CANDS_PI0_(38)+chn_offset,16,8,0x00);

	//pi_power_on_seq_end_array
	reg_bit_set(CANDS_PI0_(38)+chn_offset,24,8,islp3?0x80:0x1);

	//pi_wdt_disable
	reg_bit_set(CANDS_PI0_(55)+chn_offset,0,1,1);

	//pi_sw_rst_n
	reg_bit_set(CANDS_PI0_(55)+chn_offset,8,1,1);

	//pi_preamble_support
	reg_bit_set(CANDS_PI0_(60)+chn_offset,0,2,islp3?0:2);//?????


	//pi_dfs_period_en, enable dfs-triggered periodic leveling
	reg_bit_set(CANDS_PI0_(74)+chn_offset,0,1,islp3?PI_DFS_PERDIC_LVL_EN_LP3:PI_DFS_PERDIC_LVL_EN_LP4);

	//pi_sre_prediod_en, enable selfrefresh exit-triggered periodic leveling
	reg_bit_set(CANDS_PI0_(74)+chn_offset,8,1,islp3?PI_SRE_PERDIC_LVL_EN_LP3:PI_SRE_PERDIC_LVL_EN_LP4);

	//pi_16bit_dram_connect  which means a single cs is 16bit or 32bit   1:16bit   0:32bit
	//reg_bit_set(CANDS_PI0_(89)+chn_offset,24,1,IS_16BIT(ddr_type)?1:0);
	reg_bit_set(CANDS_PI0_(74)+chn_offset,24,1,0);

	//pi_en_odt_assert_except_rd
	reg_bit_set(CANDS_PI0_(88)+chn_offset,24,1,0);  //?????

	//pi_clkdisable_2_init_start
	reg_bit_set(CANDS_PI0_(145)+chn_offset,16,8,0x4); //??????

	//pi_init_startorcomplete_2_clkdisable
	reg_bit_set(CANDS_PI0_(145)+chn_offset,24,8,0x4); //?????

	//pi_dram_clk_disable_deassert_sel
	reg_bit_set(CANDS_PI0_(146)+chn_offset, 0,1,0x0);

	//pi_refresh_between_segment_disable
	reg_bit_set(CANDS_PI0_(146)+chn_offset, 8,1,0x1);

	//pi_cmd_swap_en
	reg_bit_set(CANDS_PI0_(225)+chn_offset, 24,1,0);

	//pi_long_count_mask
	reg_bit_set(CANDS_PI0_(225)+chn_offset,16,5,0);

	//pi_bstlen
	reg_bit_set(CANDS_PI0_(225)+chn_offset,8,5,islp3?3:4);

	//pi_ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_PI0_(231)+chn_offset, 8,1,1);

	//odt_rd_map_cs
	reg_bit_set(CANDS_PI0_(86)+chn_offset, 24,4,0x1);	//cs0
	reg_bit_set(CANDS_PI0_(87)+chn_offset,  8,4,0x2);	//cs1
	reg_bit_set(CANDS_PI0_(87)+chn_offset, 24,4,0x4);	//cs2
	reg_bit_set(CANDS_PI0_(88)+chn_offset,  8,4,0x8);	//cs3

	//odt_wr_map_cs
	reg_bit_set(CANDS_PI0_(87)+chn_offset,  0,4,0x1);	//cs0
	reg_bit_set(CANDS_PI0_(87)+chn_offset, 16,4,0x2);	//cs1
	reg_bit_set(CANDS_PI0_(88)+chn_offset,  0,4,0x4);	//cs2
	reg_bit_set(CANDS_PI0_(88)+chn_offset, 16,4,0x8);	//cs3

	//address map init
	cands_pi_addrmap_init(chn_num, ddr_type);

	//int seq pattern
	cands_pi_seq_init(chn_num, ddr_type);

}
void cands_pi_actiming_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_PI_TIMING_T *pi_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_PI_TIMING_T * f0_timing = NULL;
	CANDS_PI_TIMING_T * f1_timing = NULL;
	CANDS_PI_TIMING_T * f2_timing = NULL;
	CANDS_PI_TIMING_T * f3_timing = NULL;
	CANDS_PI_TIMING_T * f4_timing = NULL;
	CANDS_PI_TIMING_T **timing = (CANDS_PI_TIMING_T **)temp_fn;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_pi_timing_map(TIMING_SET_SUM,pi_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_PI_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PI_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PI_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PI_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_PI_TIMING_T *)(temp_fn[4]);

	//caslat_lin
	reg_bit_set(CANDS_PI0_(57)+chn_offset, 24,7,f0_timing->PI_CASLAT_LIN_Fx);
	reg_bit_set(CANDS_PI0_(58)+chn_offset,8,7,f1_timing->PI_CASLAT_LIN_Fx);
	reg_bit_set(CANDS_PI0_(58)+chn_offset, 24,7,f2_timing->PI_CASLAT_LIN_Fx);
	reg_bit_set(CANDS_PI0_(59)+chn_offset,8,7,f3_timing->PI_CASLAT_LIN_Fx);
	reg_bit_set(CANDS_PI0_(59)+chn_offset, 24,7,f4_timing->PI_CASLAT_LIN_Fx);

	//rdlat_adj
	reg_bit_set(CANDS_PI0_(108)+chn_offset, 16,7,f0_timing->PI_RDLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(108)+chn_offset, 24,7,f1_timing->PI_RDLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(109)+chn_offset,0,7,f2_timing->PI_RDLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(109)+chn_offset,8,7,f3_timing->PI_RDLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(109)+chn_offset, 16,7,f4_timing->PI_RDLAT_ADJ_Fx);

	//wrlat
	reg_bit_set(CANDS_PI0_(57)+chn_offset,16,7,f0_timing->PI_WRLAT_Fx);
	reg_bit_set(CANDS_PI0_(58)+chn_offset, 0,7,f1_timing->PI_WRLAT_Fx);
	reg_bit_set(CANDS_PI0_(58)+chn_offset,16,7,f2_timing->PI_WRLAT_Fx);
	reg_bit_set(CANDS_PI0_(59)+chn_offset, 0,7,f3_timing->PI_WRLAT_Fx);
	reg_bit_set(CANDS_PI0_(59)+chn_offset,16,7,f4_timing->PI_WRLAT_Fx);

	//wrlat_adj
	reg_bit_set(CANDS_PI0_(110)+chn_offset,0,7,f0_timing->PI_WRLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(110)+chn_offset,8,7,f1_timing->PI_WRLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(110)+chn_offset, 16,7,f2_timing->PI_WRLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(110)+chn_offset, 24,7,f3_timing->PI_WRLAT_ADJ_Fx);
	reg_bit_set(CANDS_PI0_(111)+chn_offset,0,7,f4_timing->PI_WRLAT_ADJ_Fx);

	//tcackel
	reg_bit_set(CANDS_PI0_(124)+chn_offset,16,5,f0_timing->PI_TCACKEL);

	//tcamrd
	reg_bit_set(CANDS_PI0_(124)+chn_offset,24,6,f0_timing->PI_TCAMRD);

	//tcackeh
	reg_bit_set(CANDS_PI0_(125)+chn_offset, 0,5,f0_timing->PI_TCACKEH);

	//tcaent
	reg_bit_set(CANDS_PI0_(125)+chn_offset,16,14,f0_timing->PI_TCAENT);
	reg_bit_set(CANDS_PI0_(126)+chn_offset,8,14,f1_timing->PI_TCAENT);
	reg_bit_set(CANDS_PI0_(127)+chn_offset,0,14,f2_timing->PI_TCAENT);
	reg_bit_set(CANDS_PI0_(128)+chn_offset,0,14,f3_timing->PI_TCAENT);
	reg_bit_set(CANDS_PI0_(129)+chn_offset,0,14,f4_timing->PI_TCAENT);

	//tcaext
	reg_bit_set(CANDS_PI0_(129)+chn_offset,16,5,f0_timing->PI_TCAEXT);

	//tccd
	reg_bit_set(CANDS_PI0_(190)+chn_offset,16,5,f0_timing->PI_TCCD);

	//tccdmw
	reg_bit_set(CANDS_PI0_(193)+chn_offset, 8,6,f0_timing->PI_TCCDMW_Fx);
	reg_bit_set(CANDS_PI0_(196)+chn_offset,16,6,f1_timing->PI_TCCDMW_Fx);
	reg_bit_set(CANDS_PI0_(200)+chn_offset, 8,6,f2_timing->PI_TCCDMW_Fx);
	reg_bit_set(CANDS_PI0_(203)+chn_offset,16,6,f3_timing->PI_TCCDMW_Fx);
	reg_bit_set(CANDS_PI0_(207)+chn_offset, 8,6,f4_timing->PI_TCCDMW_Fx);

	//tckckeh
	reg_bit_set(CANDS_PI0_(140)+chn_offset,16,4,f0_timing->PI_TCKCKEH);

	//tckehdqs
	reg_bit_set(CANDS_PI0_(146)+chn_offset,16,6,f0_timing->PI_TCKEHDQS_Fx);
	reg_bit_set(CANDS_PI0_(146)+chn_offset,24,6,f1_timing->PI_TCKEHDQS_Fx);
	reg_bit_set(CANDS_PI0_(147)+chn_offset, 0,6,f2_timing->PI_TCKEHDQS_Fx);
	reg_bit_set(CANDS_PI0_(147)+chn_offset, 8,6,f3_timing->PI_TCKEHDQS_Fx);
	reg_bit_set(CANDS_PI0_(147)+chn_offset,16,6,f4_timing->PI_TCKEHDQS_Fx);

	//tdqsck_max
	reg_bit_set(CANDS_PI0_(193)+chn_offset, 0,4,f0_timing->PI_TDQSCK_MAX_Fx);
	reg_bit_set(CANDS_PI0_(196)+chn_offset, 8,4,f1_timing->PI_TDQSCK_MAX_Fx);
	reg_bit_set(CANDS_PI0_(200)+chn_offset, 0,4,f2_timing->PI_TDQSCK_MAX_Fx);
	reg_bit_set(CANDS_PI0_(203)+chn_offset, 8,4,f3_timing->PI_TDQSCK_MAX_Fx);
	reg_bit_set(CANDS_PI0_(207)+chn_offset, 0,4,f4_timing->PI_TDQSCK_MAX_Fx);

	//tdelay_rdwr_2_bus_idle
	reg_bit_set(CANDS_PI0_(56)+chn_offset,  0,8,f0_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);
	reg_bit_set(CANDS_PI0_(56)+chn_offset, 8,8,f1_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);
	reg_bit_set(CANDS_PI0_(56)+chn_offset, 16,8,f2_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);
	reg_bit_set(CANDS_PI0_(56)+chn_offset,  24,8,f3_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);
	reg_bit_set(CANDS_PI0_(57)+chn_offset,  0,8,f4_timing->PI_TDELAY_RDWR_2_BUS_IDLE_Fx);

	//tfc
	reg_bit_set(CANDS_PI0_(188)+chn_offset, 0,10,f0_timing->PI_TFC_Fx);
	reg_bit_set(CANDS_PI0_(188)+chn_offset, 16,10,f1_timing->PI_TFC_Fx);
	reg_bit_set(CANDS_PI0_(189)+chn_offset, 0,10,f2_timing->PI_TFC_Fx);
	reg_bit_set(CANDS_PI0_(189)+chn_offset, 16,10,f3_timing->PI_TFC_Fx);
	reg_bit_set(CANDS_PI0_(190)+chn_offset, 0,10,f4_timing->PI_TFC_Fx);

	//tmrd
	reg_bit_set(CANDS_PI0_(193)+chn_offset,16,6,f0_timing->PI_TMRD_Fx);
	reg_bit_set(CANDS_PI0_(196)+chn_offset,24,6,f1_timing->PI_TMRD_Fx);
	reg_bit_set(CANDS_PI0_(200)+chn_offset,16,6,f2_timing->PI_TMRD_Fx);
	reg_bit_set(CANDS_PI0_(203)+chn_offset,24,6,f3_timing->PI_TMRD_Fx);
	reg_bit_set(CANDS_PI0_(207)+chn_offset,16,6,f4_timing->PI_TMRD_Fx);

	//tmrr
	reg_bit_set(CANDS_PI0_(57)+chn_offset,8,4,f0_timing->PI_TMRR);

	//tmrw
	reg_bit_set(CANDS_PI0_(193)+chn_offset,24,8,f0_timing->PI_TMRW_Fx);
	reg_bit_set(CANDS_PI0_(197)+chn_offset, 0,8,f1_timing->PI_TMRW_Fx);
	reg_bit_set(CANDS_PI0_(200)+chn_offset,24,8,f2_timing->PI_TMRW_Fx);
	reg_bit_set(CANDS_PI0_(204)+chn_offset, 0,8,f3_timing->PI_TMRW_Fx);
	reg_bit_set(CANDS_PI0_(207)+chn_offset,24,8,f4_timing->PI_TMRW_Fx);

	//tmrz
	reg_bit_set(CANDS_PI0_(125)+chn_offset, 8,5,f0_timing->PI_TMRZ_Fx);
	reg_bit_set(CANDS_PI0_(126)+chn_offset, 0,5,f1_timing->PI_TMRZ_Fx);
	reg_bit_set(CANDS_PI0_(126)+chn_offset,24,5,f2_timing->PI_TMRZ_Fx);
	reg_bit_set(CANDS_PI0_(127)+chn_offset,16,5,f3_timing->PI_TMRZ_Fx);
	reg_bit_set(CANDS_PI0_(128)+chn_offset,16,5,f4_timing->PI_TMRZ_Fx);

	//tras_max
	reg_bit_set(CANDS_PI0_(192)+chn_offset,0,17,f0_timing->PI_TRAS_MAX_Fx);
	reg_bit_set(CANDS_PI0_(195)+chn_offset,8,17,f1_timing->PI_TRAS_MAX_Fx);
	reg_bit_set(CANDS_PI0_(199)+chn_offset,0,17,f2_timing->PI_TRAS_MAX_Fx);
	reg_bit_set(CANDS_PI0_(202)+chn_offset,8,17,f3_timing->PI_TRAS_MAX_Fx);
	reg_bit_set(CANDS_PI0_(206)+chn_offset,0,17,f4_timing->PI_TRAS_MAX_Fx);

	//tras_min
	reg_bit_set(CANDS_PI0_(192)+chn_offset,24,8,f0_timing->PI_TRAS_MIN_Fx);
	reg_bit_set(CANDS_PI0_(196)+chn_offset, 0,8,f1_timing->PI_TRAS_MIN_Fx);
	reg_bit_set(CANDS_PI0_(199)+chn_offset,24,8,f2_timing->PI_TRAS_MIN_Fx);
	reg_bit_set(CANDS_PI0_(203)+chn_offset, 0,8,f3_timing->PI_TRAS_MIN_Fx);
	reg_bit_set(CANDS_PI0_(206)+chn_offset,24,8,f4_timing->PI_TRAS_MIN_Fx);

	//trcd
	reg_bit_set(CANDS_PI0_(191)+chn_offset, 8,8,f0_timing->PI_TRCD_Fx);
	reg_bit_set(CANDS_PI0_(194)+chn_offset,16,8,f1_timing->PI_TRCD_Fx);
	reg_bit_set(CANDS_PI0_(197)+chn_offset,24,8,f2_timing->PI_TRCD_Fx);
	reg_bit_set(CANDS_PI0_(201)+chn_offset,16,8,f3_timing->PI_TRCD_Fx);
	reg_bit_set(CANDS_PI0_(204)+chn_offset,24,8,f4_timing->PI_TRCD_Fx);

	//tref
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_PI0_(61+i)+chn_offset,16,16,timing[i]->PI_TREF_Fx);
	}

	//tref_interval
	//reg_bit_set(CANDS_PI0_(81)+chn_offset, 0,16,f0_timing->PI_TREF_INTERVAL);

	//trfc
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_PI0_(61+i)+chn_offset, 0,10,timing[i]->PI_TRFC_Fx);
	}

	//trp
	reg_bit_set(CANDS_PI0_(191)+chn_offset, 0,8,f0_timing->PI_TRP_Fx);
	reg_bit_set(CANDS_PI0_(194)+chn_offset, 8,8,f1_timing->PI_TRP_Fx);
	reg_bit_set(CANDS_PI0_(197)+chn_offset,16,8,f2_timing->PI_TRP_Fx);
	reg_bit_set(CANDS_PI0_(201)+chn_offset, 8,8,f3_timing->PI_TRP_Fx);
	reg_bit_set(CANDS_PI0_(204)+chn_offset,16,8,f4_timing->PI_TRP_Fx);

	//trtp
	reg_bit_set(CANDS_PI0_(190)+chn_offset,24,4,f0_timing->PI_TRTP_Fx);
	reg_bit_set(CANDS_PI0_(194)+chn_offset, 0,4,f1_timing->PI_TRTP_Fx);
	reg_bit_set(CANDS_PI0_(197)+chn_offset, 8,4,f2_timing->PI_TRTP_Fx);
	reg_bit_set(CANDS_PI0_(201)+chn_offset, 0,4,f3_timing->PI_TRTP_Fx);
	reg_bit_set(CANDS_PI0_(204)+chn_offset, 8,4,f4_timing->PI_TRTP_Fx);

	//tvref_short
	reg_bit_set(CANDS_PI0_(130)+chn_offset,16,10,f0_timing->PI_TVREF_SHORT_Fx);
	reg_bit_set(CANDS_PI0_(132)+chn_offset, 0,10,f1_timing->PI_TVREF_SHORT_Fx);
	reg_bit_set(CANDS_PI0_(133)+chn_offset,16,10,f2_timing->PI_TVREF_SHORT_Fx);
	reg_bit_set(CANDS_PI0_(135)+chn_offset, 0,10,f3_timing->PI_TVREF_SHORT_Fx);
	reg_bit_set(CANDS_PI0_(136)+chn_offset,16,10,f4_timing->PI_TVREF_SHORT_Fx);

	//reversed
	//reg_bit_set(CANDS_PI0_(148)+chn_offset, 8,1,1);
	//tvref_long
	reg_bit_set(CANDS_PI0_(131)+chn_offset, 0,10,f0_timing->PI_TVREF_LONG_Fx);
	reg_bit_set(CANDS_PI0_(132)+chn_offset,16,10,f1_timing->PI_TVREF_LONG_Fx);
	reg_bit_set(CANDS_PI0_(134)+chn_offset, 0,10,f2_timing->PI_TVREF_LONG_Fx);
	reg_bit_set(CANDS_PI0_(135)+chn_offset,16,10,f3_timing->PI_TVREF_LONG_Fx);
	reg_bit_set(CANDS_PI0_(137)+chn_offset, 0,10,f4_timing->PI_TVREF_LONG_Fx);

	//twr
	reg_bit_set(CANDS_PI0_(191)+chn_offset,24,6,f0_timing->PI_TWR_Fx);
	reg_bit_set(CANDS_PI0_(195)+chn_offset, 0,6,f1_timing->PI_TWR_Fx);
	reg_bit_set(CANDS_PI0_(198)+chn_offset, 8,6,f2_timing->PI_TWR_Fx);
	reg_bit_set(CANDS_PI0_(202)+chn_offset, 0,6,f3_timing->PI_TWR_Fx);
	reg_bit_set(CANDS_PI0_(205)+chn_offset, 8,6,f4_timing->PI_TWR_Fx);

	//twtr
	reg_bit_set(CANDS_PI0_(191)+chn_offset, 16,6,f0_timing->PI_TWTR_Fx);
	reg_bit_set(CANDS_PI0_(194)+chn_offset, 24,6,f1_timing->PI_TWTR_Fx);
	reg_bit_set(CANDS_PI0_(198)+chn_offset,  0,6,f2_timing->PI_TWTR_Fx);
	reg_bit_set(CANDS_PI0_(201)+chn_offset, 24,6,f3_timing->PI_TWTR_Fx);
	reg_bit_set(CANDS_PI0_(205)+chn_offset, 0,6,f4_timing->PI_TWTR_Fx);

}

void cands_pi_dfitiming_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_CTL_TIMING_T * pi_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_PI_TIMING_T * f0_timing = NULL;
	CANDS_PI_TIMING_T * f1_timing = NULL;
	CANDS_PI_TIMING_T * f2_timing = NULL;
	CANDS_PI_TIMING_T * f3_timing = NULL;
	CANDS_PI_TIMING_T * f4_timing = NULL;
	CANDS_PI_TIMING_T ** timing = (CANDS_PI_TIMING_T ** )temp_fn;

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

	for(i=0;i < 5; i++) {
		__raw_writel(CANDS_PI0_(12+5*i)+chn_offset, timing[i]->PI_TDFI_PHYUPD_TYPE0_Fx);
		__raw_writel(CANDS_PI0_(13+5*i)+chn_offset, timing[i]->PI_TDFI_PHYUPD_TYPE1_Fx);
		__raw_writel(CANDS_PI0_(14+5*i)+chn_offset, timing[i]->PI_TDFI_PHYUPD_TYPE2_Fx);
		__raw_writel(CANDS_PI0_(15+5*i)+chn_offset, timing[i]->PI_TDFI_PHYUPD_TYPE3_Fx);
		__raw_writel(CANDS_PI0_(2+2*i)+chn_offset, timing[i]->PI_TDFI_PHYMSTR_MAX_Fx);
		reg_bit_set(CANDS_PI0_(3+2*i)+chn_offset, 0,16,timing[i]->PI_TDFI_PHYMSTR_RESP_Fx);
	}

	//tdfi_ctrl_delay
	reg_bit_set(CANDS_PI0_(75)+chn_offset, 0,4,f0_timing->PI_TDFI_CTRL_DELAY_Fx);
	reg_bit_set(CANDS_PI0_(75)+chn_offset, 8,4,f1_timing->PI_TDFI_CTRL_DELAY_Fx);
	reg_bit_set(CANDS_PI0_(75)+chn_offset,16,4,f2_timing->PI_TDFI_CTRL_DELAY_Fx);
	reg_bit_set(CANDS_PI0_(75)+chn_offset,24,4,f3_timing->PI_TDFI_CTRL_DELAY_Fx);
	reg_bit_set(CANDS_PI0_(76)+chn_offset, 0,4,f4_timing->PI_TDFI_CTRL_DELAY_Fx);

	//tdfi_wrlvl_en
	reg_bit_set(CANDS_PI0_(79)+chn_offset,16,8,f0_timing->PI_TDFI_WRLVL_EN);

	//tdfi_wrlvl_ww
	reg_bit_set(CANDS_PI0_(80)+chn_offset, 0,10,f0_timing->PI_TDFI_WRLVL_WW);

	//tdfi_wrlvl_resp
	__raw_writel(CANDS_PI0_(81)+chn_offset, f0_timing->PI_TDFI_WRLVL_RESP);

	//tdfi_wrlvl_max
	__raw_writel(CANDS_PI0_(82)+chn_offset, f0_timing->PI_TDFI_WRLVL_MAX);

	//tdfi_rdlvl_en
	reg_bit_set(CANDS_PI0_(99)+chn_offset, 8,8,f0_timing->PI_TDFI_RDLVL_EN);

	//tdfi_rdlvl_rr
	reg_bit_set(CANDS_PI0_(97)+chn_offset,16,10,f0_timing->PI_TDFI_RDLVL_RR);

	//tdfi_rdlvl_resp
	__raw_writel(CANDS_PI0_(98)+chn_offset, f0_timing->PI_TDFI_RDLVL_RESP);

	//tdfi_rdlvl_max
	__raw_writel(CANDS_PI0_(100)+chn_offset, f0_timing->PI_TDFI_RDLVL_MAX);

	//tdfi_rddata_en
	reg_bit_set(CANDS_PI0_(109)+chn_offset, 24,7,f0_timing->PI_TDFI_RDDATA_EN);

	//tdfi_wrcslat
	reg_bit_set(CANDS_PI0_(111)+chn_offset, 16,7,f0_timing->PI_TDFI_WRCSLAT_Fx);
	reg_bit_set(CANDS_PI0_(111)+chn_offset, 24,7,f1_timing->PI_TDFI_WRCSLAT_Fx);
	reg_bit_set(CANDS_PI0_(112)+chn_offset,0,7,f2_timing->PI_TDFI_WRCSLAT_Fx);
	reg_bit_set(CANDS_PI0_(112)+chn_offset,8,7,f3_timing->PI_TDFI_WRCSLAT_Fx);
	reg_bit_set(CANDS_PI0_(112)+chn_offset, 16,7,f4_timing->PI_TDFI_WRCSLAT_Fx);

	//tdfi_phy_wrdata
	reg_bit_set(CANDS_PI0_(112)+chn_offset, 24,3,f0_timing->PI_TDFI_PHY_WRDATA);

	//tdfi_calvl_en
	reg_bit_set(CANDS_PI0_(115)+chn_offset,8,8,f0_timing->PI_TDFI_CALVL_EN);

	//tdfi_calvl_cc
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_PI0_(115+i)+chn_offset, 16,10,timing[i]->PI_TDFI_CALVL_CC_Fx);
		reg_bit_set(CANDS_PI0_(116+i)+chn_offset, 0,10,timing[i]->PI_TDFI_CALVL_CAPTURE_Fx);
	}

	//tdfi_calvl_resp
	__raw_writel(CANDS_PI0_(121)+chn_offset, f0_timing->PI_TDFI_CALVL_RESP);

	//tdfi_calvl_max
	__raw_writel(CANDS_PI0_(122)+chn_offset, f0_timing->PI_TDFI_CALVL_MAX);

	//tdfi_calvl_strobe
	reg_bit_set(CANDS_PI0_(139)+chn_offset, 8,4,f0_timing->PI_TDFI_CALVL_STROBE_Fx);
	reg_bit_set(CANDS_PI0_(139)+chn_offset,16,4,f1_timing->PI_TDFI_CALVL_STROBE_Fx);
	reg_bit_set(CANDS_PI0_(139)+chn_offset,24,4,f2_timing->PI_TDFI_CALVL_STROBE_Fx);
	reg_bit_set(CANDS_PI0_(140)+chn_offset, 0,4,f3_timing->PI_TDFI_CALVL_STROBE_Fx);
	reg_bit_set(CANDS_PI0_(140)+chn_offset, 8,4,f4_timing->PI_TDFI_CALVL_STROBE_Fx);

	//tdfi_cacsca
	reg_bit_set(CANDS_PI0_(130)+chn_offset, 0,5,f0_timing->PI_TDFI_CACSCA_Fx);
	reg_bit_set(CANDS_PI0_(131)+chn_offset,16,5,f1_timing->PI_TDFI_CACSCA_Fx);
	reg_bit_set(CANDS_PI0_(133)+chn_offset, 0,5,f2_timing->PI_TDFI_CACSCA_Fx);
	reg_bit_set(CANDS_PI0_(134)+chn_offset,16,5,f3_timing->PI_TDFI_CACSCA_Fx);
	reg_bit_set(CANDS_PI0_(136)+chn_offset, 0,5,f4_timing->PI_TDFI_CACSCA_Fx);

	//tdfi_casel
	reg_bit_set(CANDS_PI0_(130)+chn_offset, 8,5,f0_timing->PI_TDFI_CASEL_Fx);
	reg_bit_set(CANDS_PI0_(131)+chn_offset,24,5,f1_timing->PI_TDFI_CASEL_Fx);
	reg_bit_set(CANDS_PI0_(133)+chn_offset, 8,5,f2_timing->PI_TDFI_CASEL_Fx);
	reg_bit_set(CANDS_PI0_(134)+chn_offset,24,5,f3_timing->PI_TDFI_CASEL_Fx);
	reg_bit_set(CANDS_PI0_(136)+chn_offset, 8,5,f4_timing->PI_TDFI_CASEL_Fx);

	//tdfi_init_start_min
	reg_bit_set(CANDS_PI0_(138)+chn_offset,24,8,f0_timing->PI_TDFI_INIT_START_MIN);

	//tdfi_init_complete_min
	reg_bit_set(CANDS_PI0_(139)+chn_offset, 0,8,f0_timing->PI_TDFI_INIT_COMPLETE_MIN);

	//tdfi_init_start
	reg_bit_set(CANDS_PI0_(141)+chn_offset, 8,8,f0_timing->PI_TDFI_INIT_START_Fx);
	reg_bit_set(CANDS_PI0_(142)+chn_offset, 0,8,f1_timing->PI_TDFI_INIT_START_Fx);
	reg_bit_set(CANDS_PI0_(142)+chn_offset,24,8,f2_timing->PI_TDFI_INIT_START_Fx);
	reg_bit_set(CANDS_PI0_(143)+chn_offset,16,8,f3_timing->PI_TDFI_INIT_START_Fx);
	reg_bit_set(CANDS_PI0_(144)+chn_offset,16,8,f4_timing->PI_TDFI_INIT_START_Fx);

	//tdfi_init_complete
	reg_bit_set(CANDS_PI0_(141)+chn_offset,16,16,f0_timing->PI_TDFI_INIT_COMPLETE_Fx);
	reg_bit_set(CANDS_PI0_(142)+chn_offset, 8,16,f1_timing->PI_TDFI_INIT_COMPLETE_Fx);
	reg_bit_set(CANDS_PI0_(143)+chn_offset, 0,16,f2_timing->PI_TDFI_INIT_COMPLETE_Fx);
	reg_bit_set(CANDS_PI0_(144)+chn_offset, 0,16,f3_timing->PI_TDFI_INIT_COMPLETE_Fx);
	reg_bit_set(CANDS_PI0_(145)+chn_offset, 0,16,f4_timing->PI_TDFI_INIT_COMPLETE_Fx);

	//tdfi_wdqlvl_wr
	reg_bit_set(CANDS_PI0_(148)+chn_offset, 8,10,f0_timing->PI_TDFI_WDQLVL_WR);

	//tdfi_wdqlvl_rw
	reg_bit_set(CANDS_PI0_(149)+chn_offset, 0,10,f0_timing->PI_TDFI_WDQLVL_RW);

	//tdfi_wdqlvl_en
	reg_bit_set(CANDS_PI0_(152)+chn_offset, 8,8,f0_timing->PI_TDFI_WDQLVL_EN);

	//tdfi_wdqlvl_resp
	__raw_writel(CANDS_PI0_(153)+chn_offset, f0_timing->PI_TDFI_WDQLVL_RESP);

	//tdfi_wdqlvl_max
	__raw_writel(CANDS_PI0_(154)+chn_offset, f0_timing->PI_TDFI_WDQLVL_MAX);

	//tdfi_ctrlupd_max
	for(i=0;i < 5; i++) {
		reg_bit_set(CANDS_PI0_(232+2*i)+chn_offset, 0,16,timing[i]->PI_TDFI_CTRLUPD_MAX_Fx);
		__raw_writel(CANDS_PI0_(233+2*i)+chn_offset, timing[i]->PI_TDFI_CTRLUPD_INTERVAL_Fx);
	}

	//init_startorcomplete_2_clkdisable
	reg_bit_set(CANDS_PI0_(145)+chn_offset,24,8,f0_timing->PI_INIT_STARTORCOMPLETE_2_CLKDISABLE);

	//clkdisable_2_init_start
	reg_bit_set(CANDS_PI0_(145)+chn_offset,16,8,f0_timing->PI_CLKDISABLE_2_INIT_START);

}


void cands_pi_odtiming_init(DDR_CHANNEL_NUM_E chn_num,volatile CANDS_CTL_TIMING_T * pi_timing,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i = 0;

	CANDS_PI_TIMING_T * f0_timing = NULL;
	CANDS_PI_TIMING_T * f1_timing = NULL;
	CANDS_PI_TIMING_T * f2_timing = NULL;
	CANDS_PI_TIMING_T * f3_timing = NULL;
	CANDS_PI_TIMING_T * f4_timing = NULL;

	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	cands_pi_timing_map(TIMING_SET_SUM,pi_timing,f0,f1,f2,f3,f4, f0_timing,f1_timing,f2_timing,f3_timing,f4_timing);

	f0_timing = (CANDS_PI_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PI_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PI_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PI_TIMING_T *)(temp_fn[3]);
	f4_timing = (CANDS_PI_TIMING_T *)(temp_fn[4]);

	//odt_en
	reg_bit_set(CANDS_PI0_(84)+chn_offset,  0,1,f0_timing->PI_ODT_EN_Fx);
	reg_bit_set(CANDS_PI0_(84)+chn_offset, 16,1,f1_timing->PI_ODT_EN_Fx);
	reg_bit_set(CANDS_PI0_(85)+chn_offset, 0,1,f2_timing->PI_ODT_EN_Fx);
	reg_bit_set(CANDS_PI0_(85)+chn_offset,16,1,f3_timing->PI_ODT_EN_Fx);
	reg_bit_set(CANDS_PI0_(86)+chn_offset, 0,1,f4_timing->PI_ODT_EN_Fx);

	//odtlon
	reg_bit_set(CANDS_PI0_(89)+chn_offset, 0,4,f0_timing->PI_ODTLON_Fx);
	reg_bit_set(CANDS_PI0_(89)+chn_offset,16,4,f1_timing->PI_ODTLON_Fx);
	reg_bit_set(CANDS_PI0_(90)+chn_offset, 0,4,f2_timing->PI_ODTLON_Fx);
	reg_bit_set(CANDS_PI0_(90)+chn_offset,16,4,f3_timing->PI_ODTLON_Fx);
	reg_bit_set(CANDS_PI0_(91)+chn_offset, 0,4,f4_timing->PI_ODTLON_Fx);

	//todth_wr
	reg_bit_set(CANDS_PI0_(86)+chn_offset, 8,4,f0_timing->PI_TODTH_WR);

	//todth_rd
	reg_bit_set(CANDS_PI0_(86)+chn_offset,16,4,f0_timing->PI_TODTH_RD);

	//todtl_2cmd
	reg_bit_set(CANDS_PI0_(83)+chn_offset, 24,8,f0_timing->PI_TODTL_2CMD_Fx);
	reg_bit_set(CANDS_PI0_(84)+chn_offset,  8,8,f1_timing->PI_TODTL_2CMD_Fx);
	reg_bit_set(CANDS_PI0_(84)+chn_offset, 24,8,f2_timing->PI_TODTL_2CMD_Fx);
	reg_bit_set(CANDS_PI0_(85)+chn_offset, 8,8,f3_timing->PI_TODTL_2CMD_Fx);
	reg_bit_set(CANDS_PI0_(85)+chn_offset,24,8,f4_timing->PI_TODTL_2CMD_Fx);

	//todton_min
	reg_bit_set(CANDS_PI0_(89)+chn_offset, 8,4,f0_timing->PI_TODTON_MIN_Fx);
	reg_bit_set(CANDS_PI0_(89)+chn_offset,24,4,f1_timing->PI_TODTON_MIN_Fx);
	reg_bit_set(CANDS_PI0_(90)+chn_offset, 8,4,f2_timing->PI_TODTON_MIN_Fx);
	reg_bit_set(CANDS_PI0_(90)+chn_offset,24,4,f3_timing->PI_TODTON_MIN_Fx);
	reg_bit_set(CANDS_PI0_(91)+chn_offset, 8,4,f4_timing->PI_TODTON_MIN_Fx);

	//wr_to_odth
	reg_bit_set(CANDS_PI0_(91)+chn_offset,16,6,f0_timing->PI_WR_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(91)+chn_offset,24,6,f1_timing->PI_WR_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(92)+chn_offset, 0,6,f2_timing->PI_WR_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(92)+chn_offset, 8,6,f3_timing->PI_WR_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(92)+chn_offset,16,6,f4_timing->PI_WR_TO_ODTH_Fx);

	//rd_to_odth
	reg_bit_set(CANDS_PI0_(92)+chn_offset,24,6,f0_timing->PI_RD_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(93)+chn_offset, 0,6,f1_timing->PI_RD_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(93)+chn_offset, 8,6,f2_timing->PI_RD_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(93)+chn_offset,16,6,f3_timing->PI_RD_TO_ODTH_Fx);
	reg_bit_set(CANDS_PI0_(93)+chn_offset,24,6,f4_timing->PI_RD_TO_ODTH_Fx);

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
	reg_bit_set(CANDS_PI0_(156)+chn_offset, 8,8,f0_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(157)+chn_offset,24,8,f1_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(159)+chn_offset, 8,8,f2_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(160)+chn_offset,24,8,f3_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(162)+chn_offset, 8,8,f4_timing->PI_MR1_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(164)+chn_offset, 0,8,f0_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(165)+chn_offset,16,8,f1_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(167)+chn_offset, 0,8,f2_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(168)+chn_offset,16,8,f3_timing->PI_MR1_DATA_Fx);
	reg_bit_set(CANDS_PI0_(170)+chn_offset, 0,8,f4_timing->PI_MR1_DATA_Fx);

	//mr2
	//cs0
	reg_bit_set(CANDS_PI0_(156)+chn_offset,16,8,f0_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(158)+chn_offset, 0,8,f1_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(159)+chn_offset,16,8,f2_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(161)+chn_offset, 0,8,f3_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(162)+chn_offset,16,8,f4_timing->PI_MR2_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(164)+chn_offset, 8,8,f0_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(165)+chn_offset,24,8,f1_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(167)+chn_offset, 8,8,f2_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(168)+chn_offset,24,8,f3_timing->PI_MR2_DATA_Fx);
	reg_bit_set(CANDS_PI0_(170)+chn_offset, 8,8,f4_timing->PI_MR2_DATA_Fx);

	//mr3
	//cs0
	reg_bit_set(CANDS_PI0_(156)+chn_offset,24,8,f0_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(158)+chn_offset, 8,8,f1_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(159)+chn_offset,24,8,f2_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(161)+chn_offset, 8,8,f3_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(162)+chn_offset,24,8,f4_timing->PI_MR3_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(164)+chn_offset,16,8,f0_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(166)+chn_offset, 0,8,f1_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(167)+chn_offset,16,8,f2_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(169)+chn_offset, 0,8,f3_timing->PI_MR3_DATA_Fx);
	reg_bit_set(CANDS_PI0_(170)+chn_offset,16,8,f4_timing->PI_MR3_DATA_Fx);

	//mr11
	//cs0
	reg_bit_set(CANDS_PI0_(157)+chn_offset, 0,8,f0_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(158)+chn_offset,16,8,f1_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(160)+chn_offset, 0,8,f2_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(161)+chn_offset,16,8,f3_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(163)+chn_offset, 0,8,f4_timing->PI_MR11_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(164)+chn_offset,24,8,f0_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(166)+chn_offset, 8,8,f1_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(167)+chn_offset,24,8,f2_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(169)+chn_offset, 8,8,f3_timing->PI_MR11_DATA_Fx);
	reg_bit_set(CANDS_PI0_(170)+chn_offset,24,8,f4_timing->PI_MR11_DATA_Fx);

	#ifdef DRAM_LPDDR4
	//mr12
	//cs0
	reg_bit_set(CANDS_PI0_(157)+chn_offset, 8,8,f0_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(158)+chn_offset,24,8,f1_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(160)+chn_offset, 8,8,f2_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(161)+chn_offset,24,8,f3_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(163)+chn_offset, 8,8,f4_timing->PI_MR12_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(165)+chn_offset, 0,8,f0_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(166)+chn_offset,16,8,f1_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(168)+chn_offset, 0,8,f2_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(169)+chn_offset,16,8,f3_timing->PI_MR12_DATA_Fx);
	reg_bit_set(CANDS_PI0_(171)+chn_offset, 0,8,f4_timing->PI_MR12_DATA_Fx);

	//mr14
	//cs0
	reg_bit_set(CANDS_PI0_(157)+chn_offset,16,8,f0_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(159)+chn_offset, 0,8,f1_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(160)+chn_offset,16,8,f2_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(162)+chn_offset, 0,8,f3_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(163)+chn_offset,16,8,f4_timing->PI_MR14_DATA_Fx);
	//cs1
	reg_bit_set(CANDS_PI0_(165)+chn_offset, 8,8,f0_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(166)+chn_offset,24,8,f1_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(168)+chn_offset, 8,8,f2_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(169)+chn_offset,24,8,f3_timing->PI_MR14_DATA_Fx);
	reg_bit_set(CANDS_PI0_(171)+chn_offset, 8,8,f4_timing->PI_MR14_DATA_Fx);

	//mr13
	reg_bit_set(CANDS_PI0_(163)+chn_offset,24,8,f0_timing->PI_MR13_DATA_CSm);//cs0
	reg_bit_set(CANDS_PI0_(171)+chn_offset,16,8,f0_timing->PI_MR13_DATA_CSm);//cs1
	#else
#if 0
	//mr11
	//cs0
	reg_bit_set(CANDS_PI0_(157)+chn_offset, 0,8,0);
	reg_bit_set(CANDS_PI0_(158)+chn_offset,16,8,0);
	reg_bit_set(CANDS_PI0_(160)+chn_offset, 0,8,0);
	reg_bit_set(CANDS_PI0_(161)+chn_offset,16,8,0);
	reg_bit_set(CANDS_PI0_(163)+chn_offset, 0,8,0);
	//cs1
	reg_bit_set(CANDS_PI0_(164)+chn_offset,24,8,0);
	reg_bit_set(CANDS_PI0_(166)+chn_offset, 8,8,0);
	reg_bit_set(CANDS_PI0_(167)+chn_offset,24,8,0);
	reg_bit_set(CANDS_PI0_(169)+chn_offset, 8,8,0);
	reg_bit_set(CANDS_PI0_(170)+chn_offset,24,8,0);
#endif
	//mr12
	//cs0
	reg_bit_set(CANDS_PI0_(157)+chn_offset, 8,8,0);
	reg_bit_set(CANDS_PI0_(158)+chn_offset,24,8,0);
	reg_bit_set(CANDS_PI0_(160)+chn_offset, 8,8,0);
	reg_bit_set(CANDS_PI0_(161)+chn_offset,24,8,0);
	reg_bit_set(CANDS_PI0_(163)+chn_offset, 8,8,0);
	//cs1
	reg_bit_set(CANDS_PI0_(165)+chn_offset, 0,8,0);
	reg_bit_set(CANDS_PI0_(166)+chn_offset,16,8,0);
	reg_bit_set(CANDS_PI0_(168)+chn_offset, 0,8,0);
	reg_bit_set(CANDS_PI0_(169)+chn_offset,16,8,0);
	reg_bit_set(CANDS_PI0_(171)+chn_offset, 0,8,0);

	//mr14
	//cs0
	reg_bit_set(CANDS_PI0_(157)+chn_offset,16,8,0);
	reg_bit_set(CANDS_PI0_(159)+chn_offset, 0,8,0);
	reg_bit_set(CANDS_PI0_(160)+chn_offset,16,8,0);
	reg_bit_set(CANDS_PI0_(162)+chn_offset, 0,8,0);
	reg_bit_set(CANDS_PI0_(163)+chn_offset,16,8,0);
	//cs1
	reg_bit_set(CANDS_PI0_(165)+chn_offset, 8,8,0);
	reg_bit_set(CANDS_PI0_(166)+chn_offset,24,8,0);
	reg_bit_set(CANDS_PI0_(168)+chn_offset, 8,8,0);
	reg_bit_set(CANDS_PI0_(169)+chn_offset,24,8,0);
	reg_bit_set(CANDS_PI0_(171)+chn_offset, 8,8,0);

	//mr13
	reg_bit_set(CANDS_PI0_(163)+chn_offset,24,8,0);//cs0
	reg_bit_set(CANDS_PI0_(171)+chn_offset,16,8,0);//cs1
	#endif
}

void cands_pi_catr_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,uint32 cs_map)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//calvl_cs
	reg_bit_set(CANDS_PI0_(113)+chn_offset, 8,2, 0);

	//calvl_seq_en
	reg_bit_set(CANDS_PI0_(114)+chn_offset, 0,2,0x3);

	//calvl_periodic
	reg_bit_set(CANDS_PI0_(114)+chn_offset, 8,1,PI_CALVL_PERDIC_EN);

	//calvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(114)+chn_offset, 16,1,PI_CALVL_SRE_EN);

	//calvl_rotate
	reg_bit_set(CANDS_PI0_(114)+chn_offset, 24,1,0); //??????

	//calvl_cs_map
	reg_bit_set(CANDS_PI0_(115)+chn_offset,0,4,cs_map);

	//calvl_resp_mask
	reg_bit_set(CANDS_PI0_(123)+chn_offset, 0,1,0);

	//calvl_en
	reg_bit_set(CANDS_PI0_(123)+chn_offset, 8,2,(PI_CALVL_EN_NOINIT<<1)|PI_CALVL_EN_INIT);

	//calvl_interval
	reg_bit_set(CANDS_PI0_(124)+chn_offset, 0,16,0); //?????

	//ca_train_vref_en
	reg_bit_set(CANDS_PI0_(129)+chn_offset, 24,1,PI_CALVL_VREF_EN); //?????

	//calvl_vref_initial_start_point
	reg_bit_set(CANDS_PI0_(137)+chn_offset, 16,7,0x68); //?????

	//calvl_vref_initial_stop_point
	reg_bit_set(CANDS_PI0_(137)+chn_offset, 24,7,0x72); //?????

	//calvl_vref_initial_stepsize
	reg_bit_set(CANDS_PI0_(138)+chn_offset, 0,4,0x4); //?????

	//calvl_vref_normal_stepsize
	reg_bit_set(CANDS_PI0_(138)+chn_offset, 8,4,0x2); //?????

	//calvl_vref_delta
	reg_bit_set(CANDS_PI0_(138)+chn_offset, 16,4,0x1); //?????

	//calvl_strobe_num
	reg_bit_set(CANDS_PI0_(140)+chn_offset, 24,5,0x2); //?????

	//sw_ca_train_vref
	reg_bit_set(CANDS_PI0_(141)+chn_offset,  0,7,0x0);
}

void cands_pi_rdlvl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,uint32 cs_map)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//rdlvl_cs_map
	reg_bit_set(CANDS_PI0_(97)+chn_offset, 0,4, cs_map);

	//rdlvl_gate_cs_map
	reg_bit_set(CANDS_PI0_(97)+chn_offset, 8,4, cs_map);

	//rdlvl_en
	reg_bit_set(CANDS_PI0_(99)+chn_offset, 16,2,(PI_RDLVL_EN_NOINIT<<1)|PI_RDLVL_EN_INIT);

	//rdlvl_seq_en
	reg_bit_set(CANDS_PI0_(94)+chn_offset,24,4, 0);

	//rdlvl_gate_en
	reg_bit_set(CANDS_PI0_(99)+chn_offset, 24,2,(PI_RDLVL_GATE_EN_NOINIT<<1)|PI_RDLVL_GATE_EN_INIT);

	//rdlvl_gate_seq_en
	reg_bit_set(CANDS_PI0_(95)+chn_offset, 0,4, 0);

	//rd_preamble_training_en
	reg_bit_set(CANDS_PI0_(108)+chn_offset, 0,1, PI_RD_PREAMBLE_TR_EN);

	//rdlvl_periodic
	reg_bit_set(CANDS_PI0_(95)+chn_offset,  8,1, PI_RDLVL_PERDIC_EN); //??????

	//rdlvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(95)+chn_offset, 16,1, PI_RDLVL_SRE_EN); //??????

	//rdlvl_gate_periodic
	reg_bit_set(CANDS_PI0_(95)+chn_offset, 24,1, PI_RDLVL_GATE_PERDIC_EN); //??????

	//rdlvl_gate_on_sref_exit
	reg_bit_set(CANDS_PI0_(96)+chn_offset,  0,1, PI_RDLVL_GATE_SRE_EN); //??????

	//rdlvl_rotate
	reg_bit_set(CANDS_PI0_(96)+chn_offset, 16,1, 0); //??????

	//rdlvl_gate_rotate
	reg_bit_set(CANDS_PI0_(96)+chn_offset, 24,1, 0); //??????

	//rdlvl_interval
	reg_bit_set(CANDS_PI0_(101)+chn_offset, 8,16, 0); //??????

	//rdlvl_gate_interval
	reg_bit_set(CANDS_PI0_(102)+chn_offset, 0,16, 0); //??????

	//rdlvl_pattern_start
	reg_bit_set(CANDS_PI0_(102)+chn_offset,16,4, 0); //??????

	//rdlvl_pattern_num
	reg_bit_set(CANDS_PI0_(102)+chn_offset,24,4, 1); //??????

	//rdlvl_strobe_num
	reg_bit_set(CANDS_PI0_(103)+chn_offset,0,5, 1); //??????

	//rdlvl_gate_strobe_num
	reg_bit_set(CANDS_PI0_(103)+chn_offset,8,5, 1); //??????

	//rdlvl_gate_strobe_num
	//reg_bit_set(CANDS_PI0_(120)+chn_offset,8,5, 1); //??????

}

void cands_pi_wrlvl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type, uint32 cs_map)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//wldqsen
	reg_bit_set(CANDS_PI0_(76)+chn_offset,24,6, 0xa); //??????

	//wlmrd
	reg_bit_set(CANDS_PI0_(77)+chn_offset, 0,6, 0x28); //??????

	//wrlvl_en
	reg_bit_set(CANDS_PI0_(77)+chn_offset, 8,2, (PI_WRLVL_EN_NOINIT<<1)|PI_WRLVL_EN_INIT); //??????

	//wrlvl_interval
	reg_bit_set(CANDS_PI0_(77)+chn_offset, 16,16,0);

	//wrlvl_periodic
	reg_bit_set(CANDS_PI0_(78)+chn_offset, 0,1, PI_WRLVL_PERDIC_EN);

	//wrlvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(78)+chn_offset, 8,1, PI_WRLVL_SRE_EN);

	//wrlvl_resp_mask
	reg_bit_set(CANDS_PI0_(78)+chn_offset,16,4,0);

	//wrlvl_rotate
	reg_bit_set(CANDS_PI0_(78)+chn_offset,24,1,0); //????????

	//wrlvl_cs_map
	reg_bit_set(CANDS_PI0_(79)+chn_offset, 0,4, cs_map);

	//wrlvl_strobe_num
	reg_bit_set(CANDS_PI0_(83)+chn_offset, 0,5,2);

}

void cands_pi_wdqlvl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type, uint32 cs_map)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//wdqlvl_en
	reg_bit_set(CANDS_PI0_(155)+chn_offset,16,2,(PI_WDQLVL_EN_NOINIT<<1)|PI_WDQLVL_EN_INIT);

	//wdq_vref_en
	reg_bit_set(CANDS_PI0_(147)+chn_offset,24,1,PI_WDQLVL_VREF_EN);

	//wdqlvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(155)+chn_offset,24,1,PI_WDQLVL_SRE_EN);

	//wdqlvl_periodic
	reg_bit_set(CANDS_PI0_(151)+chn_offset,16,1,PI_WDQLVL_PERDIC_EN);

	//wdqlvl_cs_map
	reg_bit_set(CANDS_PI0_(150)+chn_offset,0,4, cs_map);

	//wdqlvl_bst_num
	reg_bit_set(CANDS_PI0_(148)+chn_offset,0,3,1); //??????

	//wdqlvl_resp_mask
	reg_bit_set(CANDS_PI0_(149)+chn_offset,16,4,0);

	//wdqlvl_rotate
	reg_bit_set(CANDS_PI0_(149)+chn_offset,24,1,0); //??????

	//wdqlvl_vref_initial_start_point
	reg_bit_set(CANDS_PI0_(150)+chn_offset, 8,7,0x1a); //?????

	//wdqlvl_vref_initial_stop_point
	reg_bit_set(CANDS_PI0_(150)+chn_offset,16,7,0x23); //?????

	//wdqlvl_vref_initial_stepsize
	reg_bit_set(CANDS_PI0_(150)+chn_offset,24,5,0x1); //?????

	//wdqlvl_vref_normal_stepsize
	reg_bit_set(CANDS_PI0_(151)+chn_offset, 0,5,0x1); //?????

	//wdqlvl_vref_delta
	reg_bit_set(CANDS_PI0_(151)+chn_offset, 8,4,0x1); //?????

	//wdqlvl_interval
	reg_bit_set(CANDS_PI0_(155)+chn_offset, 0,16,0); //?????

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
	cs_map = IS_2CS(ddr_type)?3:1;
	#else
	uint32 ctlfn_to_pifn[5] = {1,2,3,4,0};
	cs_map = IS_2CS(ddr_type)?0xf:5;
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
			case 1400: pi_fn_div[i] = CLKDIV_1400MHZ; break;
			case 934:  pi_fn_div[i] = CLKDIV_934MHZ;  break;
			case 466:  pi_fn_div[i] = CLKDIV_466MHZ;  break;
			case 234:  pi_fn_div[i] = CLKDIV_234MHZ;  break;
			case 933:  pi_fn_div[i] = CLKDIV_933MHZ;  break;
			case 622:  pi_fn_div[i] = CLKDIV_622MHZ;  break;
			case 460:  pi_fn_div[i] = CLKDIV_460MHZ;  break;
			case 368:  pi_fn_div[i] = CLKDIV_368MHZ;  break;
			case 233:  pi_fn_div[i] = CLKDIV_233MHZ;  break;
			case 311:  pi_fn_div[i] = CLKDIV_311MHZ;  break;
			case 156:  pi_fn_div[i] = CLKDIV_156MHZ;  break;
			case 26:   pi_fn_div[i] = CLKDIV_26MHZ;   break;
			default: while(1);
		}
	}
	//cs_map = islp3?(IS_2CS(ddr_type)?3:1):(IS_2CS(ddr_type)?0x33:(IS_16BIT(ddr_type)?0x1:0x11));
	//cs_map = islp3?(IS_2CS(ddr_type)?3:1):((IS_2CS(ddr_type)?0x33:0x11)&(IS_16BIT(ddr_type)?0xf:0xff));

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
#endif //#ifndef DDR_IP_CONFIG_FILE
void cands_phy_pinmux_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//if(islp3) //lpddr3, single channel, sbs
	#ifdef DRAM_LPDDR3 //lpddr3, single channel, sbs

	//phy_adr_addr_sel_0
	reg_bit_set(CANDS_PHY0_(541)+chn_offset,0,24,0x80);
	//phy_adr_addr_sel_1
	reg_bit_set(CANDS_PHY0_(669)+chn_offset,0,24,0x7659);
	//phy_adr_addr_sel_2
	reg_bit_set(CANDS_PHY0_(797)+chn_offset,0,24,0x43);
	//phy_adr_addr_sel_3
	reg_bit_set(CANDS_PHY0_(925)+chn_offset,0,24,0x1200);

	//phy_adr_bit_mask_0
	reg_bit_set(CANDS_PHY0_(542)+chn_offset,16,6,0x2);
	//phy_adr_seg_mask_0
	reg_bit_set(CANDS_PHY0_(542)+chn_offset,24,6,0x0);

	//phy_adr_bit_mask_1
	reg_bit_set(CANDS_PHY0_(670)+chn_offset,16,6,0xf);
	//phy_adr_seg_mask_1
	reg_bit_set(CANDS_PHY0_(670)+chn_offset,24,6,0x1);

	//phy_adr_bit_mask_2
	reg_bit_set(CANDS_PHY0_(798)+chn_offset,16,6,0x3);
	//phy_adr_seg_mask_2
	reg_bit_set(CANDS_PHY0_(798)+chn_offset,24,6,0x2);

	//phy_adr_bit_mask_3
	reg_bit_set(CANDS_PHY0_(926)+chn_offset,16,6,0xe);
	//phy_adr_seg_mask_3
	reg_bit_set(CANDS_PHY0_(926)+chn_offset,24,6,0x0);

	//phy_adr_calvl_swizzle0_0_0
	reg_bit_set(CANDS_PHY0_(525)+chn_offset,0,24,0xe0);
	//phy_adr_calvl_swizzle1_0_0
	reg_bit_set(CANDS_PHY0_(526)+chn_offset,0,24,0xf1);
	//phy_adr_calvl_swizzle0_1_0
	reg_bit_set(CANDS_PHY0_(527)+chn_offset,0,24,0xe0);
	//phy_adr_calvl_swizzle1_1_0
	reg_bit_set(CANDS_PHY0_(528)+chn_offset,0,24,0xf1);

	//phy_adr_calvl_swizzle0_0_1
	reg_bit_set(CANDS_PHY0_(653)+chn_offset,0,24,0xca88);
	//phy_adr_calvl_swizzle1_0_1
	reg_bit_set(CANDS_PHY0_(654)+chn_offset,0,24,0xdb99);
	//phy_adr_calvl_swizzle0_1_1
	reg_bit_set(CANDS_PHY0_(655)+chn_offset,0,24,0xca88);
	//phy_adr_calvl_swizzle1_1_1
	reg_bit_set(CANDS_PHY0_(656)+chn_offset,0,24,0xdb99);

	//phy_adr_calvl_swizzle0_0_2
	reg_bit_set(CANDS_PHY0_(781)+chn_offset,0,24,0x06);
	//phy_adr_calvl_swizzle1_0_2
	reg_bit_set(CANDS_PHY0_(782)+chn_offset,0,24,0x17);
	//phy_adr_calvl_swizzle0_1_2
	reg_bit_set(CANDS_PHY0_(783)+chn_offset,0,24,0x06);
	//phy_adr_calvl_swizzle1_1_2
	reg_bit_set(CANDS_PHY0_(784)+chn_offset,0,24,0x17);

	//phy_adr_calvl_swizzle0_0_3
	reg_bit_set(CANDS_PHY0_(909)+chn_offset,0,24,0x2400);
	//phy_adr_calvl_swizzle1_0_3
	reg_bit_set(CANDS_PHY0_(910)+chn_offset,0,24,0x3511);
	//phy_adr_calvl_swizzle0_1_3
	reg_bit_set(CANDS_PHY0_(911)+chn_offset,0,24,0x2400);
	//phy_adr_calvl_swizzle1_1_3
	reg_bit_set(CANDS_PHY0_(912)+chn_offset,0,24,0x3511);

	//pi_byte_swap_en
	__raw_writel(CANDS_PI0_(230)+chn_offset,0x10301);
	reg_bit_set(CANDS_PI0_(231)+chn_offset,0,8,0x2);

	//phy_data_byte_order_sel
	reg_bit_set(CANDS_PHY0_(1103)+chn_offset,24,8,0x036);

	/*-------data slice 0-----*/
	//phy_dm_dq_swizzle0_0
	__raw_writel(CANDS_PHY0_(0)+chn_offset,0x47163205);
   	//phy_dm_dq_swizzle1_0
	reg_bit_set(CANDS_PHY0_(1)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_0
	//__raw_writel(CANDS_PHY0_(24)+chn_offset,0x43176205);

	/*-------data slice 1-----*/
	//phy_dm_dq_swizzle0_1
	__raw_writel(CANDS_PHY0_(128)+chn_offset,0x45726130);
   	//phy_dm_dq_swizzle1_1
	reg_bit_set(CANDS_PHY0_(129)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_1
	//__raw_writel(CANDS_PHY0_(152)+chn_offset,0x42851630);

	/*-------data slice 2-----*/
	//phy_dm_dq_swizzle0_2
	__raw_writel(CANDS_PHY0_(256)+chn_offset,0x51082647);
   	//phy_dm_dq_swizzle1_2
	reg_bit_set(CANDS_PHY0_(257)+chn_offset,0,4,3);
    //phy_rdlvl_data_swizzle_2
	//__raw_writel(CANDS_PHY0_(280)+chn_offset,0x31582647);

	/*-------data slice 3-----*/
	//phy_dm_dq_swizzle0_3
	__raw_writel(CANDS_PHY0_(384)+chn_offset,0x63042175);
   	//phy_dm_dq_swizzle1_3
	reg_bit_set(CANDS_PHY0_(385)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_3
	//__raw_writel(CANDS_PHY0_(408)+chn_offset,0x34602157);

	//pi_cmd_swap_en
	reg_bit_set(CANDS_PI0_(225)+chn_offset,24,1,1);

	//pi_cke_mux
	__raw_writel(CANDS_PI0_(226)+chn_offset,0x0f0e0d0c);
	//__raw_writel(CANDS_PI0_(270)+chn_offset,0x0000);

	//pi_cs_mux
	__raw_writel(CANDS_PI0_(227)+chn_offset,0x09080b0a);
	//__raw_writel(CANDS_PI0_(272)+chn_offset,0x1110);

	//pi_odt_mux
	__raw_writel(CANDS_PI0_(228)+chn_offset,0x0000);
	//__raw_writel(CANDS_PI0_(274)+chn_offset,0x0000);

	//pi_reset_mux
	__raw_writel(CANDS_PI0_(229)+chn_offset,0x0000);
	//__raw_writel(CANDS_PI0_(276)+chn_offset,0x0000);

	#else ////lpddr4, two channel, pop
	//phy_adr_addr_sel_0
	reg_bit_set(CANDS_PHY0_(541)+chn_offset,0,24,0x10);
	//phy_adr_addr_sel_1
	reg_bit_set(CANDS_PHY0_(669)+chn_offset,0,24,0x5432);
	//phy_adr_addr_sel_2
	reg_bit_set(CANDS_PHY0_(797)+chn_offset,0,24,0x10);
	//phy_adr_addr_sel_3
	reg_bit_set(CANDS_PHY0_(925)+chn_offset,0,24,0x5432);

	//phy_adr_bit_mask_0
	reg_bit_set(CANDS_PHY0_(542)+chn_offset,16,6,0x3);
	//phy_adr_seg_mask_0
	reg_bit_set(CANDS_PHY0_(542)+chn_offset,24,6,0x0);

	//phy_adr_bit_mask_1
	reg_bit_set(CANDS_PHY0_(670)+chn_offset,16,6,0xf);
	//phy_adr_seg_mask_1
	reg_bit_set(CANDS_PHY0_(670)+chn_offset,24,6,0x0);

	//phy_adr_bit_mask_2
	reg_bit_set(CANDS_PHY0_(798)+chn_offset,16,6,0x3);
	//phy_adr_seg_mask_2
	reg_bit_set(CANDS_PHY0_(798)+chn_offset,24,6,0x0);

	//phy_adr_bit_mask_3
	reg_bit_set(CANDS_PHY0_(926)+chn_offset,16,6,0xf);
	//phy_adr_seg_mask_3
	reg_bit_set(CANDS_PHY0_(926)+chn_offset,24,6,0x0);

	//phy_adr_calvl_swizzle0_0_0
	reg_bit_set(CANDS_PHY0_(525)+chn_offset,0,24,0x98);
	//phy_adr_calvl_swizzle1_0_0
	reg_bit_set(CANDS_PHY0_(526)+chn_offset,0,24,0x0);
	//phy_adr_calvl_swizzle0_1_0
	reg_bit_set(CANDS_PHY0_(527)+chn_offset,0,24,0x98);
	//phy_adr_calvl_swizzle1_1_0
	reg_bit_set(CANDS_PHY0_(528)+chn_offset,0,24,0x0);

	//phy_adr_calvl_swizzle0_0_1
	reg_bit_set(CANDS_PHY0_(653)+chn_offset,0,24,0xdcba);
	//phy_adr_calvl_swizzle1_0_1
	reg_bit_set(CANDS_PHY0_(654)+chn_offset,0,24,0x0);
	//phy_adr_calvl_swizzle0_1_1
	reg_bit_set(CANDS_PHY0_(655)+chn_offset,0,24,0xdcba);
	//phy_adr_calvl_swizzle1_1_1
	reg_bit_set(CANDS_PHY0_(656)+chn_offset,0,24,0x0);

	//phy_adr_calvl_swizzle0_0_2
	reg_bit_set(CANDS_PHY0_(781)+chn_offset,0,24,0x98);
	//phy_adr_calvl_swizzle1_0_2
	reg_bit_set(CANDS_PHY0_(782)+chn_offset,0,24,0x0);
	//phy_adr_calvl_swizzle0_1_2
	reg_bit_set(CANDS_PHY0_(783)+chn_offset,0,24,0x98);
	//phy_adr_calvl_swizzle1_1_2
	reg_bit_set(CANDS_PHY0_(784)+chn_offset,0,24,0x0);

	//phy_adr_calvl_swizzle0_0_3
	reg_bit_set(CANDS_PHY0_(909)+chn_offset,0,24,0xdcba);
	//phy_adr_calvl_swizzle1_0_3
	reg_bit_set(CANDS_PHY0_(910)+chn_offset,0,24,0x0);
	//phy_adr_calvl_swizzle0_1_3
	reg_bit_set(CANDS_PHY0_(911)+chn_offset,0,24,0xdcba);
	//phy_adr_calvl_swizzle1_1_3
	reg_bit_set(CANDS_PHY0_(912)+chn_offset,0,24,0x0);

	//pi_byte_swap_en
	__raw_writel(CANDS_PI0_(230)+chn_offset,0x02010000);
	reg_bit_set(CANDS_PI0_(231)+chn_offset,0,8,0x3);

	//phy_data_byte_order_sel
	reg_bit_set(CANDS_PHY0_(1103)+chn_offset,24,8,0xe4);

	/*-------data slice 0-----*/
	//phy_dm_dq_swizzle0_0
	__raw_writel(CANDS_PHY0_(0)+chn_offset,0x76543210);
   	//phy_dm_dq_swizzle1_0
	reg_bit_set(CANDS_PHY0_(1)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_0
	//__raw_writel(CANDS_PHY0_(24)+chn_offset,0x43176205);

	/*-------data slice 1-----*/
	//phy_dm_dq_swizzle0_1
	__raw_writel(CANDS_PHY0_(128)+chn_offset,0x76543210);
   	//phy_dm_dq_swizzle1_1
	reg_bit_set(CANDS_PHY0_(129)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_1
	//__raw_writel(CANDS_PHY0_(152)+chn_offset,0x42851630);

	/*-------data slice 2-----*/
	//phy_dm_dq_swizzle0_2
	__raw_writel(CANDS_PHY0_(256)+chn_offset,0x76543210);
   	//phy_dm_dq_swizzle1_2
	reg_bit_set(CANDS_PHY0_(257)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_2
	//__raw_writel(CANDS_PHY0_(280)+chn_offset,0x31582647);

	/*-------data slice 3-----*/
	//phy_dm_dq_swizzle0_3
	__raw_writel(CANDS_PHY0_(384)+chn_offset,0x76543210);
   	//phy_dm_dq_swizzle1_3
	reg_bit_set(CANDS_PHY0_(385)+chn_offset,0,4,8);
    //phy_rdlvl_data_swizzle_3
	//__raw_writel(CANDS_PHY0_(408)+chn_offset,0x34602157);

	//pi_cmd_swap_en
	reg_bit_set(CANDS_PI0_(225)+chn_offset,24,1,0);
	//pi_cke_mux
	__raw_writel(CANDS_PI0_(226)+chn_offset,0x0f0e0d0c);
	//__raw_writel(CANDS_PI0_(270)+chn_offset,0x0000);

	//pi_cs_mux
	__raw_writel(CANDS_PI0_(227)+chn_offset,0x0b0a0908);
	//__raw_writel(CANDS_PI0_(272)+chn_offset,0x1110);

	//pi_odt_mux
	__raw_writel(CANDS_PI0_(228)+chn_offset,0x0000);
	//__raw_writel(CANDS_PI0_(274)+chn_offset,0x0000);

	//pi_reset_mux
	__raw_writel(CANDS_PI0_(229)+chn_offset,0x0000);
	//__raw_writel(CANDS_PI0_(276)+chn_offset,0x0000);

	#endif

}

#ifndef DDR_IP_CONFIG_FILE
void cands_data_gen_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);
	uint32 cs_map = 0;

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	cs_map = IS_2CS(ddr_type)?0x3:0x1;

	//phy_two_cyc_preamble, bit0:2 cycle read preamble bit1: 2 cycle write preamble
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,24,2,islp3?0:2); //?????
	}
	#else
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,24,2,islp3?0:2); //?????
	#endif

	//phy_per_rank_cs_map
	#ifdef DRAM_LPDDR3
	//reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,8,3,IS_2CS(ddr_type)); //?????
	#else
	//reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,8,3,IS_2CS(ddr_type)?3:1); //?????
	#endif
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,8,2,cs_map); //?????
	//phy_dbi_mode
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,0,1,RD_DBI_EN); //?????no write dbi???

	//phy_lpddr_type
	reg_bit_set(CANDS_PHY0_(15)+chn_offset+slice_offset,8,2,islp3?1:2);

	//phy_lpddr
	reg_bit_set(CANDS_PHY0_(15)+chn_offset+slice_offset,0,1,1);

	//on_fly_gate_adjust_en
	reg_bit_set(CANDS_PHY0_(16)+chn_offset+slice_offset,16,2,0); //??????

	//phy_per_cs_training_index
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,24,1,0); //????

	//phy_per_cs_training_multicast_en
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,16,1,1); //????

	//phy_per_cs_training_en
	#ifdef DRAM_LPDDR4
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset,16,1,1); //????
	}
	#else
	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset,16,1,1); //????
	#endif
	#endif
	//phy_lvl_debug_mode
	reg_bit_set(CANDS_PHY0_(25)+chn_offset+slice_offset,0,1,0);

	//phy_calvl_vref_driving_slice, if drvie vref value to slice during catraining
	reg_bit_set(CANDS_PHY0_(35)+chn_offset+slice_offset,16,1,islp3?0:((slice_num%2)?0:1)); //??????

	//phy_ddl_mode
	reg_bit_set(CANDS_PHY0_(52)+chn_offset+slice_offset,0,18,0);

	//phy_ie_mode
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(94)+chn_offset+slice_offset,16,2,PHY_IE_ALWAYS_ON);
	}
	#else
	reg_bit_set(CANDS_PHY0_(94)+chn_offset+slice_offset,16,2,PHY_IE_ALWAYS_ON);
	#endif

	//phy_rptr_update
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(96)+chn_offset+slice_offset,16,4,timing[i]->phy_rptr_update_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(96)+chn_offset+slice_offset,16,4,f3_timing->phy_rptr_update_X);
	#endif
}

void cands_data_bypass_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_clk_bypass_override
	reg_bit_set(CANDS_PHY0_(2)+chn_offset+slice_offset,24,1,0);
	//phy_clk_wr_bypass_slave_delay
	reg_bit_set(CANDS_PHY0_(1)+chn_offset+slice_offset,8,11,islp3?0x4c0:0x4f0); //??????
	//phy_rddqs_dq_bypass_slave_dleay
	reg_bit_set(CANDS_PHY0_(14)+chn_offset+slice_offset,0,10,0xc0);

	//set f0~f3 dll bypass mode
	for(i=0;i < 4; i++) {
		phy_reg_switch_dfs(chn_num, i);
		reg_bit_set(CANDS_PHY0_(95)+chn_offset+slice_offset,8,4,timing[i]->phy_sw_master_mode_X);
	}
}

void cands_data_wrdqdqs_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
							uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 j = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_clk_wrdm_slave_delay
  	#if DO_DFS_INIT
	for(i = 0; i < 4; i++)
	{
		phy_reg_switch_dfs(chn_num, i);
		reg_bit_set(CANDS_PHY0_(72)+chn_offset+slice_offset, 0,11,timing[i]->phy_clk_wrdm_slave_delay_X);
		for(j = 0; j< 4; j++)
		{
			reg_bit_set(CANDS_PHY0_(68+j)+chn_offset+slice_offset, 0,11,timing[i]->phy_clk_wrdqZ_slave_delay_X);
			reg_bit_set(CANDS_PHY0_(68+j)+chn_offset+slice_offset, 16,11,timing[i]->phy_clk_wrdqZ_slave_delay_X);
		}
		reg_bit_set(CANDS_PHY0_(72)+chn_offset+slice_offset, 16,10,timing[i]->phy_clk_wrdqs_slave_delay_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(72)+chn_offset+slice_offset, 0,11,f3_timing->phy_clk_wrdm_slave_delay_X);
	for(i = 0; i< 4; i++)
	{
		reg_bit_set(CANDS_PHY0_(68+i)+chn_offset+slice_offset, 0,11,f3_timing->phy_clk_wrdqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(68+i)+chn_offset+slice_offset, 16,11,f3_timing->phy_clk_wrdqZ_slave_delay_X);
	}
	reg_bit_set(CANDS_PHY0_(72)+chn_offset+slice_offset, 16,10,f3_timing->phy_clk_wrdqs_slave_delay_X);
	#endif

	//phy_sw_wrdq0/1/2/3_shirt
	__raw_writel(CANDS_PHY0_(3)+chn_offset+slice_offset, 0);
	//phy_sw_wrdq4/5/6/7_shirt
	__raw_writel(CANDS_PHY0_(4)+chn_offset+slice_offset, 0);
	//phy_sw_wrdqqs_shirt
	reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_offset,8,4,0);
	//phy_sw_wrdm_shirt
	reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_offset,0,5,0);

}

void cands_data_dqdqs_tsel_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_dq_tsel_enable, dq/dm tsel_en, bit0: read cycle  bit1: write cycle  bit2: idle cycle
	reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_offset,16,3,PHY_DQDQS_ODT_RD_EN|(PHY_DQDQS_ODT_WR_EN<<1)|(PHY_DQDQS_ODT_IDLE_EN<<2)); //??????

	//phy_dq_tsel_select
	reg_bit_set(CANDS_PHY0_(6)+chn_offset+slice_offset,0,24,(PHY_DQDQS_ODT_IDLE_DRV<<20) |(PHY_DQDQS_ODT_IDLE_DRV<<16)|
	                                                        (PHY_DQDQS_ODT_WR_DRV<<12)   |(PHY_DQDQS_ODT_WR_DRV<<8)    |
	                                                        (PHY_DQDQS_ODT_RD_DRV_P<<4)  |(PHY_DQDQS_ODT_RD_DRV_N) ); //??????


	#if DO_DFS_INIT
	for(i = 0; i < 4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset, 8,8,timing[i]->phy_dq_tsel_rd_timing_X);
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset,16,8,timing[i]->phy_dq_tsel_wr_timing_X);
	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset, 0,8,timing[i]->phy_dqs_tsel_rd_timing_X);
	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset, 8,8,timing[i]->phy_dqs_tsel_wr_timing_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset, 8,8,f3_timing->phy_dq_tsel_rd_timing_X);
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset,16,8,f3_timing->phy_dq_tsel_wr_timing_X);
	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset, 0,8,f3_timing->phy_dqs_tsel_rd_timing_X);
	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset, 8,8,f3_timing->phy_dqs_tsel_wr_timing_X);
	#endif

	//phy_dqs_tsel_enable, dqs tsel_en, bit0: read cycle  bit1: write cycle  bit2: idle cycle
	reg_bit_set(CANDS_PHY0_(6)+chn_offset+slice_offset,24,3,PHY_DQDQS_ODT_RD_EN|(PHY_DQDQS_ODT_WR_EN<<1)|(PHY_DQDQS_ODT_IDLE_EN<<2)); //??????

	//phy_dqs_tsel_select
	reg_bit_set(CANDS_PHY0_(7)+chn_offset+slice_offset,0,24,(PHY_DQDQS_ODT_IDLE_DRV<<20)|(PHY_DQDQS_ODT_IDLE_DRV<<16)|
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

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset,24,8,timing[i]->phy_dq_ie_timing_X);
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset, 0,8,timing[i]->phy_dq_oe_timing_X);
	reg_bit_set(CANDS_PHY0_(94)+chn_offset+slice_offset, 0,8,timing[i]->phy_dqs_ie_timing_X);
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset,24,8,timing[i]->phy_dqs_oe_timing_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset,24,8,f3_timing->phy_dq_ie_timing_X);
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset, 0,8,f3_timing->phy_dq_oe_timing_X);
	reg_bit_set(CANDS_PHY0_(94)+chn_offset+slice_offset, 0,8,f3_timing->phy_dqs_ie_timing_X);
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset,24,8,f3_timing->phy_dqs_oe_timing_X);
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

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	#if DO_DFS_INIT
	for(j = 0; j<4; j++)
	{
		phy_reg_switch_dfs(chn_num,j);
		//rddm_slave_delay
		reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset,16,10,0);
		reg_bit_set(CANDS_PHY0_(94)+chn_offset+slice_offset,24,4,timing[j]->phy_rddata_en_dly_X);
		reg_bit_set(CANDS_PHY0_(95)+chn_offset+slice_offset, 0,4,timing[j]->phy_rddata_en_tsel_dly_X);
		reg_bit_set(CANDS_PHY0_(94)+chn_offset+slice_offset, 8,2,timing[j]->phy_rddata_en_ie_dly_X);
		reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 16,10,timing[j]->phy_rddqs_dm_fall_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset,0,10,timing[j]->phy_rddqs_dm_rise_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,0,10,timing[j]->phy_rddqs_gate_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset, 16, 4,timing[j]->phy_rddqs_latency_adjust_X);

		reg_bit_set(CANDS_PHY0_(73)+chn_offset+slice_offset, 8,10,timing[j]->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(74)+chn_offset+slice_offset, 0,10,timing[j]->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(74)+chn_offset+slice_offset, 8,10,timing[j]->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset, 0,10,timing[j]->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset, 8,10,timing[j]->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset, 0,10,timing[j]->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset, 8,10,timing[j]->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset, 0,10,timing[j]->phy_rddqZ_slave_delay_X);
		for(i = 0; i< 8; i++)
		{
			reg_bit_set(CANDS_PHY0_(78+i)+chn_offset+slice_offset, 16,10,timing[j]->phy_rddqs_dqZ_fall_slave_delay_X);
			reg_bit_set(CANDS_PHY0_(78+i)+chn_offset+slice_offset,0,10,timing[j]->phy_rddqs_dqZ_rise_slave_delay_X);
		}
	}
	#else
		//rddm_slave_delay
		reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset,16,10,0);
		reg_bit_set(CANDS_PHY0_(94)+chn_offset+slice_offset,24,4,f3_timing->phy_rddata_en_dly_X);
		reg_bit_set(CANDS_PHY0_(95)+chn_offset+slice_offset, 0,4,f3_timing->phy_rddata_en_tsel_dly_X);
		reg_bit_set(CANDS_PHY0_(94)+chn_offset+slice_offset, 8,2,f3_timing->phy_rddata_en_ie_dly_X);
		reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset, 16,10,f3_timing->phy_rddqs_dm_fall_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(86)+chn_offset+slice_offset,0,10,f3_timing->phy_rddqs_dm_rise_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset,0,10,f3_timing->phy_rddqs_gate_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(87)+chn_offset+slice_offset, 16, 4,f3_timing->phy_rddqs_latency_adjust_X);

		reg_bit_set(CANDS_PHY0_(73)+chn_offset+slice_offset, 8,10,f3_timing->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(74)+chn_offset+slice_offset, 0,10,f3_timing->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(74)+chn_offset+slice_offset, 8,10,f3_timing->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset, 0,10,f3_timing->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(75)+chn_offset+slice_offset, 8,10,f3_timing->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset, 0,10,f3_timing->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(76)+chn_offset+slice_offset, 8,10,f3_timing->phy_rddqZ_slave_delay_X);
		reg_bit_set(CANDS_PHY0_(77)+chn_offset+slice_offset, 0,10,f3_timing->phy_rddqZ_slave_delay_X);
		for(i = 0; i< 8; i++)
		{
			reg_bit_set(CANDS_PHY0_(78+i)+chn_offset+slice_offset, 16,10,f3_timing->phy_rddqs_dqZ_fall_slave_delay_X);
			reg_bit_set(CANDS_PHY0_(78+i)+chn_offset+slice_offset,0,10,f3_timing->phy_rddqs_dqZ_rise_slave_delay_X);
		}
	#endif
}


void cands_data_gtlvl_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_gate_error_delay_select
	reg_bit_set(CANDS_PHY0_(14)+chn_offset+slice_offset,16,5,0x17);

	//phy_gate_smpl1_slave_delay
	reg_bit_set(CANDS_PHY0_(15)+chn_offset+slice_offset,16,9,0xcc);

	//phy_gate_smpl2_slave_delay
	reg_bit_set(CANDS_PHY0_(16)+chn_offset+slice_offset,0,9,0x66);

	//phy_gtlvl_updt_wait_cnt
	reg_bit_set(CANDS_PHY0_(26)+chn_offset+slice_offset,8,4,0x4);

	//phy_gtlvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(26)+chn_offset+slice_offset,0,6,0x0);

	#if DO_DFS_INIT
	for(i = 0; i < 4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(98)+chn_offset+slice_offset, 0,10,timing[i]->phy_gtlvl_back_step_X);
	reg_bit_set(CANDS_PHY0_(97)+chn_offset+slice_offset, 8, 4,timing[i]->phy_gtlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(98)+chn_offset+slice_offset,16,10,timing[i]->phy_gtlvl_final_step_X);
	reg_bit_set(CANDS_PHY0_(89)+chn_offset+slice_offset,24, 4,timing[i]->phy_gtlvl_lat_adj_start_X);
	reg_bit_set(CANDS_PHY0_(89)+chn_offset+slice_offset, 8,10,timing[i]->phy_gtlvl_rddqs_slv_dly_start_X);
	reg_bit_set(CANDS_PHY0_(97)+chn_offset+slice_offset,16, 5,timing[i]->phy_gtlvl_resp_wait_cnt_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(98)+chn_offset+slice_offset, 0,10,f3_timing->phy_gtlvl_back_step_X);
	reg_bit_set(CANDS_PHY0_(97)+chn_offset+slice_offset, 8, 4,f3_timing->phy_gtlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(98)+chn_offset+slice_offset,16,10,f3_timing->phy_gtlvl_final_step_X);
	reg_bit_set(CANDS_PHY0_(89)+chn_offset+slice_offset,24, 4,f3_timing->phy_gtlvl_lat_adj_start_X);
	reg_bit_set(CANDS_PHY0_(89)+chn_offset+slice_offset, 8,10,f3_timing->phy_gtlvl_rddqs_slv_dly_start_X);
	reg_bit_set(CANDS_PHY0_(97)+chn_offset+slice_offset,16, 5,f3_timing->phy_gtlvl_resp_wait_cnt_X);
	#endif
}


void cands_data_wrlvl_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//wrlvl pattern
	//phy_user_patt0~4
	__raw_writel(CANDS_PHY0_(31)+chn_offset+slice_offset, 0x55555555);
	__raw_writel(CANDS_PHY0_(32)+chn_offset+slice_offset, 0xaaaaaaaa);
	__raw_writel(CANDS_PHY0_(33)+chn_offset+slice_offset, 0x55555555);
	__raw_writel(CANDS_PHY0_(34)+chn_offset+slice_offset, 0xaaaaaaaa);
	reg_bit_set(CANDS_PHY0_(35)+chn_offset+slice_offset,0,16,0x5555);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset,0,10,timing[i]->phy_wrlvl_delay_early_threshold_X);
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset, 16,10,timing[i]->phy_wrlvl_delay_period_threshold_X);
	reg_bit_set(CANDS_PHY0_(96)+chn_offset+slice_offset,24, 4,timing[i]->phy_wrlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(89)+chn_offset+slice_offset,0, 1,timing[i]->phy_wrlvl_early_force_zero_X);
	reg_bit_set(CANDS_PHY0_(97)+chn_offset+slice_offset, 0, 5,timing[i]->phy_wrlvl_resp_wait_cnt_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset,0,10,f3_timing->phy_wrlvl_delay_early_threshold_X);
	reg_bit_set(CANDS_PHY0_(88)+chn_offset+slice_offset, 16,10,f3_timing->phy_wrlvl_delay_period_threshold_X);
	reg_bit_set(CANDS_PHY0_(96)+chn_offset+slice_offset,24, 4,f3_timing->phy_wrlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(89)+chn_offset+slice_offset,0, 1,f3_timing->phy_wrlvl_early_force_zero_X);
	reg_bit_set(CANDS_PHY0_(97)+chn_offset+slice_offset, 0, 5,f3_timing->phy_wrlvl_resp_wait_cnt_X);
	#endif
	//phy_wrlvl_updt_wait_cnt
	reg_bit_set(CANDS_PHY0_(25)+chn_offset+slice_offset, 24,4,4);
	//phy_wrlvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(25)+chn_offset+slice_offset, 16,6,8);
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
	reg_bit_set(CANDS_PHY0_(28)+chn_offset+slice_offset, 8,11,0xc0);

	//phy_wdqlvl_pattern
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_PHY0_(28)+chn_offset+slice_offset, 0,3,0x7);
	#else
	reg_bit_set(CANDS_PHY0_(28)+chn_offset+slice_offset, 0,3,0x2);
	#endif
	//phy_wdqlvl_burst_cnt
	reg_bit_set(CANDS_PHY0_(27)+chn_offset+slice_offset, 24,6,0x10);

	//phy_wdqlvl_qtr_dly_step
	reg_bit_set(CANDS_PHY0_(29)+chn_offset+slice_offset,8,4,0x1);

	//phy_wdqlvl_updt_wait_cnt
	reg_bit_set(CANDS_PHY0_(28)+chn_offset+slice_offset, 24,4,0xc);

	//phy_wdqlvl_datadm_mask
	reg_bit_set(CANDS_PHY0_(30)+chn_offset+slice_offset, 0,9,0x100);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		//phy_wdqlvl_dqdm_dly_start
		reg_bit_set(CANDS_PHY0_(90)+chn_offset+slice_offset, 0,11,0x200);
		//phy_wdqlvl_dly_step
		reg_bit_set(CANDS_PHY0_(99)+chn_offset+slice_offset, 0,8,0x20);
	}
	#else
		reg_bit_set(CANDS_PHY0_(90)+chn_offset+slice_offset, 0,11,0x200);
		reg_bit_set(CANDS_PHY0_(99)+chn_offset+slice_offset, 0,8,0x20);
	#endif

}

void cands_data_rdlvl_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	//phy_rdlvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(26)+chn_offset+slice_offset,16,6,8);

	//phy_rdlvl_updt_wait_cnt
	reg_bit_set(CANDS_PHY0_(26)+chn_offset+slice_offset,24,4,4);

	//phy_rdlvl_data_mask
	reg_bit_set(CANDS_PHY0_(27)+chn_offset+slice_offset,16,8,0);

	//phy_rdlvl_op_mode
	reg_bit_set(CANDS_PHY0_(27)+chn_offset+slice_offset,0,2,0);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(99)+chn_offset+slice_offset, 8, 4,timing[i]->phy_rdlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(90)+chn_offset+slice_offset,16,10,timing[i]->phy_rdlvl_rddqs_dq_slv_dly_start_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(99)+chn_offset+slice_offset, 8, 4,f3_timing->phy_rdlvl_dly_step_X);
	reg_bit_set(CANDS_PHY0_(90)+chn_offset+slice_offset,16,10,f3_timing->phy_rdlvl_rddqs_dq_slv_dly_start_X);
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
	reg_bit_set(CANDS_PHY0_(55)+chn_offset+slice_offset,16,8,0x20);
	#else
	reg_bit_set(CANDS_PHY0_(55)+chn_offset+slice_offset,16,8,0x20);
	#endif
	//phy_rx_cal_override
	reg_bit_set(CANDS_PHY0_(55)+chn_offset+slice_offset,8,1,0);

	for(i=0;i<8;i++)
	{
		//phy_rx_cal_dq0~7
		reg_bit_set(CANDS_PHY0_(56+i)+chn_offset+slice_offset, 0,24,0x820);
	}

	//phy_rx_cal_dqs
	reg_bit_set(CANDS_PHY0_(65)+chn_offset+slice_offset,0,26,0x820);

	//phy_rx_cal_dm
	reg_bit_set(CANDS_PHY0_(64)+chn_offset+slice_offset,0,24,0x820);

	//phy_rx_cal_fdbk
	reg_bit_set(CANDS_PHY0_(66)+chn_offset+slice_offset, 0,24,0x820);
}

//not complete lp4boot code ??????
void cands_data_lp4boot_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//phy_lp4_boot_rptr_update,  for lpddr4 boot freq, time in cycles from dfi_rddata_en to release data from entry fifo
	reg_bit_set(CANDS_PHY0_(9)+chn_offset+slice_offset,24,4, islp3?0x5:0x4); //??????

	//phy_lp4_boot_rddata_en_tsel_dly,  for lpddr4 boot freq, time in cycles from dfi_rddata_en earlier than TSEL enable
	reg_bit_set(CANDS_PHY0_(9)+chn_offset+slice_offset,16,4, islp3?0x6:0); //??????lp3 have dif value

	//phy_lp4_boot_rddata_en_dly,  for lpddr4 boot freq, time in cycles from dfi_rddata_en early
	reg_bit_set(CANDS_PHY0_(9)+chn_offset+slice_offset,8,4, islp3?0x8:0x1); //?????? lp3 have dif value

	//phy_lp4_boot_rddata_en_ie_dly,  for lpddr4 boot freq, time in cycles from dfi_rddata_en earlier than input enable
	reg_bit_set(CANDS_PHY0_(9)+chn_offset+slice_offset,0,2, 0);

	//phy_lp4_boot_rddqs_latency_adjust
	reg_bit_set(CANDS_PHY0_(10)+chn_offset+slice_offset,0,4, islp3?0x3:0); //???? lp3 have dif value

	//phy_lp4_boot_rddqs_gate_slave_adjust	to be defined
	//reg_bit_set(CANDS_PHY0_(9)+chn_offset+slice_offset,0,10, islp3?0x71:0x133); //???? lp3 have dif value
}
void cands_data_mdll_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing,DRAM_TYPE_E ddr_type,
						  uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	uint32 slice_offset = slice_num*0x200;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(95)+chn_offset+slice_offset,16,10,timing[i]->phy_master_delay_start_X);
	reg_bit_set(CANDS_PHY0_(96)+chn_offset+slice_offset, 8, 8,timing[i]->phy_master_delay_wait_X);
	reg_bit_set(CANDS_PHY0_(96)+chn_offset+slice_offset, 0, 6,timing[i]->phy_master_delay_step_X);
	}
	#else
	reg_bit_set(CANDS_PHY0_(95)+chn_offset+slice_offset,16,10,f3_timing->phy_master_delay_start_X);
	reg_bit_set(CANDS_PHY0_(96)+chn_offset+slice_offset, 8, 8,f3_timing->phy_master_delay_wait_X);
	reg_bit_set(CANDS_PHY0_(96)+chn_offset+slice_offset, 0, 6,f3_timing->phy_master_delay_step_X);
	#endif
}

void cands_phy_data_init(uint32 slice_num,DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type,
						uint32 f0,uint32 f1,uint32 f2,uint32 f3)
{
	cands_data_gen_init(slice_num,chn_num,phy_timing_info,ddr_type,f0,f1,f2,f3);
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
	reg_bit_set(CANDS_PHY0_(518)+chn_offset+slice_offset,8,1,PHY_ADR_ODT_EN); //????

	//phy_adr_tsel_select
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(544)+chn_offset+slice_offset,0,8,(PHY_ADR_ODT_DRV<<4)|PHY_ADR_ODT_DRV); //????
	}
	#else
		reg_bit_set(CANDS_PHY0_(544)+chn_offset+slice_offset,0,8,(PHY_ADR_ODT_DRV<<4)|PHY_ADR_ODT_DRV); //????
	#endif

	//phy_adr_ie_mode
	reg_bit_set(CANDS_PHY0_(520)+chn_offset+slice_offset,0,1,0);

	//phy_adr_adr_type, address pin ddr type
	reg_bit_set(CANDS_PHY0_(519)+chn_offset+slice_offset,16,2,islp3?1:2);

	//phy_adr_dll_mode
	reg_bit_set(CANDS_PHY0_(520)+chn_offset+slice_offset,8,15,0);

	//phy_adr_sw_txio_ctrl
	reg_bit_set(CANDS_PHY0_(543)+chn_offset+slice_offset,8,6,0);

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

	CANDS_PHY_TIMING_T * f0_timing = NULL;
	CANDS_PHY_TIMING_T * f1_timing = NULL;
	CANDS_PHY_TIMING_T * f2_timing = NULL;
	CANDS_PHY_TIMING_T * f3_timing = NULL;
	CANDS_PHY_TIMING_T ** timing=(CANDS_PHY_TIMING_T ** )temp_fn;

	cands_phy_timing_map(TIMING_SET_SUM,phy_timing,f0,f1,f2,f3, f0_timing,f1_timing,f2_timing,f3_timing);

	f0_timing = (CANDS_PHY_TIMING_T *)(temp_fn[0]);
	f1_timing = (CANDS_PHY_TIMING_T *)(temp_fn[1]);
	f2_timing = (CANDS_PHY_TIMING_T *)(temp_fn[2]);
	f3_timing = (CANDS_PHY_TIMING_T *)(temp_fn[3]);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num, i);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,16, 4,timing[i]->phy_adr_sw_master_mode);
	reg_bit_set(CANDS_PHY0_(548)+chn_offset+slice_offset, 0,10,timing[i]->phy_adr_master_delay_start);
	reg_bit_set(CANDS_PHY0_(548)+chn_offset+slice_offset,24, 8,timing[i]->phy_adr_master_delay_wait);
	reg_bit_set(CANDS_PHY0_(548)+chn_offset+slice_offset,16, 6,timing[i]->phy_adr_master_delay_step);
	}
	#else
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset,16, 4,f3_timing->phy_adr_sw_master_mode);
	reg_bit_set(CANDS_PHY0_(548)+chn_offset+slice_offset, 0,10,f3_timing->phy_adr_master_delay_start);
	reg_bit_set(CANDS_PHY0_(548)+chn_offset+slice_offset,24, 8,f3_timing->phy_adr_master_delay_wait);
	reg_bit_set(CANDS_PHY0_(548)+chn_offset+slice_offset,16, 6,f3_timing->phy_adr_master_delay_step);
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
	reg_bit_set(CANDS_PHY0_(523)+chn_offset+slice_offset,16,11,0x40);

	//phy_adr_calvl_start
	reg_bit_set(CANDS_PHY0_(523)+chn_offset+slice_offset, 0,11,0x320);

	//phy_adr_calvl_qtr
	reg_bit_set(CANDS_PHY0_(524)+chn_offset+slice_offset, 0,11,0x40);

	//phy_adr_calvl_device_map
	reg_bit_set(CANDS_PHY0_(528)+chn_offset+slice_offset,24, 4,1); //??????calvl device map en???

	//phy_adr_calvl_resp_wait_cnt
	reg_bit_set(CANDS_PHY0_(529)+chn_offset+slice_offset,24,4,0);

	//phy_adr_calvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(529)+chn_offset+slice_offset,16,4,0x2);

	//phy_adr_calvl_num_patterns
	reg_bit_set(CANDS_PHY0_(529)+chn_offset+slice_offset,8,2,2);

	//phy_adr_calvl_rank_ctrl
	reg_bit_set(CANDS_PHY0_(529)+chn_offset+slice_offset,0,2,3); ///????

	//phy_adr_calvl_debug_mode
	reg_bit_set(CANDS_PHY0_(530)+chn_offset+slice_offset,0,1,0);

	#ifdef DRAM_LPDDR3
	//phy_adr_calvl_fg0~3
	reg_bit_set(CANDS_PHY0_(533)+chn_offset+slice_offset,0,20,0x556aa);
	reg_bit_set(CANDS_PHY0_(535)+chn_offset+slice_offset,0,20,0xaa955);
	reg_bit_set(CANDS_PHY0_(537)+chn_offset+slice_offset,0,20,0xb3133);
	reg_bit_set(CANDS_PHY0_(539)+chn_offset+slice_offset,0,20,0x4cecc);

	//phy_adr_calvl_bg0~3
	reg_bit_set(CANDS_PHY0_(534)+chn_offset+slice_offset,0,20,0xaaaaa);
	reg_bit_set(CANDS_PHY0_(536)+chn_offset+slice_offset,0,20,0x55555);
	reg_bit_set(CANDS_PHY0_(538)+chn_offset+slice_offset,0,20,0x4cd33);
	reg_bit_set(CANDS_PHY0_(540)+chn_offset+slice_offset,0,20,0xb32cc);
	#else
	//phy_adr_calvl_fg0~3
	reg_bit_set(CANDS_PHY0_(533)+chn_offset+slice_offset,0,20,0x2a);
	reg_bit_set(CANDS_PHY0_(535)+chn_offset+slice_offset,0,20,0x15);
	reg_bit_set(CANDS_PHY0_(537)+chn_offset+slice_offset,0,20,0x33);
	reg_bit_set(CANDS_PHY0_(539)+chn_offset+slice_offset,0,20,0xc);

	//phy_adr_calvl_bg0~3
	reg_bit_set(CANDS_PHY0_(534)+chn_offset+slice_offset,0,20,0x15);
	reg_bit_set(CANDS_PHY0_(536)+chn_offset+slice_offset,0,20,0x2a);
	reg_bit_set(CANDS_PHY0_(538)+chn_offset+slice_offset,0,20,0xc);
	reg_bit_set(CANDS_PHY0_(540)+chn_offset+slice_offset,0,20,0x33);
	#endif
	//phy_adr_calvl_train_mask, ????????
	if(islp3)
	{
		switch(slice_num)
		{
			case 0:i = 0x2;break;
			case 1:i = 0xf;break;
			case 2:i = 0x3;break;
			case 3:i = 0xe;break;
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
	reg_bit_set(CANDS_PHY0_(543)+chn_offset+slice_offset,0,6,i);


	//phy_adr_calvl_dly_step
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		reg_bit_set(CANDS_PHY0_(549)+chn_offset+slice_offset,0,4,0x3);
	}
	#else
		reg_bit_set(CANDS_PHY0_(549)+chn_offset+slice_offset,0,4,0x3);
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
	reg_bit_set(CANDS_PHY0_(544)+chn_offset+slice_offset, 8,11,i);
	reg_bit_set(CANDS_PHY0_(545)+chn_offset+slice_offset, 0,11,i);
	reg_bit_set(CANDS_PHY0_(545)+chn_offset+slice_offset,16,11,i);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset, 0,11,i);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset,16,11,i);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset, 0,11,i);
	}
	#else
	reg_bit_set(CANDS_PHY0_(544)+chn_offset+slice_offset, 8,11,i);
	reg_bit_set(CANDS_PHY0_(545)+chn_offset+slice_offset, 0,11,i);
	reg_bit_set(CANDS_PHY0_(545)+chn_offset+slice_offset,16,11,i);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset, 0,11,i);
	reg_bit_set(CANDS_PHY0_(546)+chn_offset+slice_offset,16,11,i);
	reg_bit_set(CANDS_PHY0_(547)+chn_offset+slice_offset, 0,11,i);
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
	reg_bit_set(CANDS_PHY0_(1026)+chn_offset, 24,1,islp3?1:0);

	//phy_lp4_boot_low_freq_sel  should be 0?
	reg_bit_set(CANDS_PHY0_(1071)+chn_offset, 16,1,islp3?0:LP4_BOOT_LOW_FREQ);

	//phy_dfi_phyupd_type
	reg_bit_set(CANDS_PHY0_(1035)+chn_offset,8,2,1);

	//phy_adrctl_lpddr
	reg_bit_set(CANDS_PHY0_(1035)+chn_offset,16,1,1);

	//phy_lpddr3_cs
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,0,1,islp3);

	//phy_lpr4_active
	reg_bit_set(CANDS_PHY0_(1035)+chn_offset,24,1,islp3?0:1);

	//phy_low_freq_sel, ????whick frequency set to 1???  less than 300mhz???
	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		switch(i)
		{
			case 0:	reg_bit_set(CANDS_PHY0_(1047)+chn_offset,0,1,PHY_LOW_FREQ_SEL_F0);
					break;
			case 1:	reg_bit_set(CANDS_PHY0_(1047)+chn_offset,0,1,PHY_LOW_FREQ_SEL_F1);
					break;
			case 2:	reg_bit_set(CANDS_PHY0_(1047)+chn_offset,0,1,PHY_LOW_FREQ_SEL_F2);
					break;
			case 3:	reg_bit_set(CANDS_PHY0_(1047)+chn_offset,0,1,PHY_LOW_FREQ_SEL_F3);
					break;
			default:	break;
		}
	}
	#else
		reg_bit_set(CANDS_PHY0_(1047)+chn_offset,0,1,PHY_LOW_FREQ_SEL_F3);
	#endif

	//reg_bit_set(CANDS_PHY0_(1047)+chn_offset,0,1,PHY_LOW_FREQ_SEL);

	//phy_tdfi_phy_wrdelay
	reg_bit_set(CANDS_PHY0_(1072)+chn_offset,8,1,0);

	//phy_lp_wakeup, !!!!!import, number of clock that take into wakeup from low power,??????
	reg_bit_set(CANDS_PHY0_(1071)+chn_offset,24,4,7);

	//phy_tcksre_wait, !!!!!wait time before pll turn off for deepsleep or dfs event, ??????
	reg_bit_set(CANDS_PHY0_(1071)+chn_offset,8,4,0x5);

	//phy_dll_rst_en, ?????no description in spec, how to set?????
	//bit0 dll_rst_en(0 hardware 1 software using bit1 rst_drive)   bit1 rst_drive
	reg_bit_set(CANDS_PHY0_(1106)+chn_offset,16,2,0x2);

}

void cands_ac_adr_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);

	//phy_adrctl_slave_loop_cnt_update
	reg_bit_set(CANDS_PHY0_(1034)+chn_offset,24,3,0);
	//phy_adrctl_rx_cal
	reg_bit_set(CANDS_PHY0_(1088)+chn_offset,0,26,0);

	//phy_adrctl_lp3_rx_cal
	reg_bit_set(CANDS_PHY0_(1089)+chn_offset,0,25,0);

	//phy_adrctl_manul_update
	reg_bit_set(CANDS_PHY0_(1098)+chn_offset,16,1,0);

	//phy_adrctl_mstr_dly_enc_sel, disable unused address slice to save powr, ????need set or not for lp3/4????
	reg_bit_set(CANDS_PHY0_(1104)+chn_offset,0,4,0);
}

void cands_ac_cscalvl_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);
	uint32 cs_map;

	//cs_map = islp3?(IS_2CS(ddr_type)?3:1):(IS_2CS(ddr_type)?0x33:(IS_16BIT(ddr_type)?0x1:0x11));
	//cs_map = islp3?(IS_2CS(ddr_type)?3:1):((IS_2CS(ddr_type)?0x33:0x11)&(IS_16BIT(ddr_type)?0xf:0xff));
	cs_map = IS_2CS(ddr_type)?3:1;

	//phy_cslvl_capture_cnt
	reg_bit_set(CANDS_PHY0_(1028)+chn_offset,16,4,2);
	//phy_cslvl_coarse_capture_cnt
	reg_bit_set(CANDS_PHY0_(1029)+chn_offset,16,4,2);

	//phy_cslvl_coarse_dly
	reg_bit_set(CANDS_PHY0_(1029)+chn_offset,0,11,0x55);

	//phy_cslvl_cs_map
	reg_bit_set(CANDS_PHY0_(1027)+chn_offset,8,4,cs_map);

	//phy_cslvl_debug_mode
	reg_bit_set(CANDS_PHY0_(1029)+chn_offset,24,1,0);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		//phy_cslvl_dly_step
		reg_bit_set(CANDS_PHY0_(1050)+chn_offset,0,4,3);
	}
	#else
	//phy_cslvl_dly_step
	reg_bit_set(CANDS_PHY0_(1050)+chn_offset,0,4,3);
	#endif

	//phy_cslvl_qtr
	reg_bit_set(CANDS_PHY0_(1028)+chn_offset,0,11,0x40);
	//phy_cslvl_start
	reg_bit_set(CANDS_PHY0_(1027)+chn_offset,16,11,0x400);

	//phy_cslvl_enable
	reg_bit_set(CANDS_PHY0_(1027)+chn_offset,0,1,PHY_CSLVL_EN);

	//phy_calvl_cs_map   only 0 or 1 valid define channel swap
	//#ifdef DRAM_LPDDR3
	//reg_bit_set(CANDS_PHY0_(1033)+chn_offset,0,8,cs_map);
	//#else
	reg_bit_set(CANDS_PHY0_(1033)+chn_offset,0,8,0x50);
	//#endif
	//phy_calvl_result_mask need to be checked why lp4 disable slice1 on whale2
	#ifdef DRAM_LPDDR3
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,8,2,0);
	#else
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,8,2,2);
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

	#if DO_DFS_INIT
	for(i=0;i<4;i++)
	{
		phy_reg_switch_dfs(chn_num,i);
		switch(i)
		{
			case 0:	//phy_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,27,f0_timing->phy_pll_ctrl0);
					//phy_top_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1043)+chn_offset,0,27,f0_timing->phy_pll_ctrl0);
					//phy_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1040)+chn_offset,0,21,0x055762);
					//phy_top_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,21,0x055762);
					break;
			case 1:	//phy_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,27,f1_timing->phy_pll_ctrl0);
					//phy_top_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1043)+chn_offset,0,27,f1_timing->phy_pll_ctrl0);
					//phy_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1040)+chn_offset,0,21,0x055752);
					//phy_top_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,21,0x055752);
					break;
			case 2:	//phy_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,27,f2_timing->phy_pll_ctrl0);
					//phy_top_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1043)+chn_offset,0,27,f2_timing->phy_pll_ctrl0);
					//phy_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1040)+chn_offset,0,21,0x055744);
					//phy_top_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,21,0x055744);
					break;
			case 3:	//phy_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,27,f3_timing->phy_pll_ctrl0);
					//phy_top_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1043)+chn_offset,0,27,f3_timing->phy_pll_ctrl0);
					//phy_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1040)+chn_offset,0,21,0x055744);
					//phy_top_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,21,0x055744);
					break;
			default:	//phy_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,27,f3_timing->phy_pll_ctrl0);
					//phy_top_pll_ctrl0
					reg_bit_set(CANDS_PHY0_(1043)+chn_offset,0,27,f3_timing->phy_pll_ctrl0);
	                                //phy_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1040)+chn_offset,0,21,0x055744);
					//phy_top_pll_ctrl1
					reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,21,0x055744);
				break;
		}
		//phy_pll_pwrn_rst_wait
		reg_bit_set(CANDS_PHY0_(1042)+chn_offset,0,8,0x50);
		if(0 == aon_ver_id)
                {
                        //phy_pll_ctrl1
			reg_bit_set(CANDS_PHY0_(1040)+chn_offset,0,21,0x055744);
			//phy_top_pll_ctrl1
			reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,21,0x055744);
		}
        }
	#else
	//phy_pll_ctrl0
	reg_bit_set(CANDS_PHY0_(1039)+chn_offset,0,27,f3_timing->phy_pll_ctrl0);
	//phy_pll_ctrl1
	reg_bit_set(CANDS_PHY0_(1040)+chn_offset,0,21,0x055742);
	//phy_top_pll_ctrl0
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset,0,27,f3_timing->phy_pll_ctrl0);
	//phy_top_pll_ctrl1
	reg_bit_set(CANDS_PHY0_(1044)+chn_offset,0,21,0x055742);
	//phy_pll_pwrn_rst_wait
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset,0,8,0x50);
	#endif
	//phy_pll_ctrl2
	reg_bit_set(CANDS_PHY0_(1054)+chn_offset,0,1,1);
	//phy_top_pll_ctrl2
	reg_bit_set(CANDS_PHY0_(1054)+chn_offset,8,1,1);
	//phy_pll_wait
	reg_bit_set(CANDS_PHY0_(1037)+chn_offset,24,8,0xff);
	//phy_pll_wait_top
	reg_bit_set(CANDS_PHY0_(1038)+chn_offset,0,8,0xff);
	//phy_pll_bypass, ?????? lower than 300mhz don't need set ?????
	#ifdef PHY_PLL_BYPASS
	reg_bit_set(CANDS_PHY0_(1046)+chn_offset,0,8,0x7f);
	#else
	reg_bit_set(CANDS_PHY0_(1046)+chn_offset,0,8,0x0);
	#endif
	//phy_lp4_boot_pll_ctrl0
	reg_bit_set(CANDS_PHY0_(1055)+chn_offset,0,27,0x00630460);
	//phy_lp4_boot_pll_ctrl1
	reg_bit_set(CANDS_PHY0_(1056)+chn_offset,0,21,0x055742);
	//phy_lp4_boot_top_pll_ctrl0
	reg_bit_set(CANDS_PHY0_(1058)+chn_offset,0,27,0x00630460);
	//phy_lp4_boot_top_pll_ctrl1
	reg_bit_set(CANDS_PHY0_(1059)+chn_offset,0,21,0x055742);
	//phy_lp4_boot_pll_pwrn_rst_wait
	reg_bit_set(CANDS_PHY0_(1061)+chn_offset,0,8,0x1e);
	//phy_pll_ctrl_override
	__raw_writel(CANDS_PHY0_(1062)+chn_offset, 0);
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
	reg_bit_set(CANDS_PHY0_(1026)+chn_offset,0,5,5);

	//phy_sw_grp_shirt0
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,16,5,0);
	//phy_sw_grp_shirt1
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,24,5,0);
	//phy_sw_grp_shirt2
	reg_bit_set(CANDS_PHY0_(1025)+chn_offset, 0,5,0);
	//phy_sw_grp_shirt3
	reg_bit_set(CANDS_PHY0_(1025)+chn_offset, 8,5,0);

	//phy_grp_bypass_override
	reg_bit_set(CANDS_PHY0_(1026)+chn_offset,8,1,0);

	//phy_grp_bypass_slave_delay
	reg_bit_set(CANDS_PHY0_(1025)+chn_offset,16,11,0);

	#if DO_DFS_INIT
	for(i = 0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num,i);
	//phy_grp_slave_delay0
	reg_bit_set(CANDS_PHY0_(1051)+chn_offset,8,11,0x300);
	//phy_grp_slave_delay1
	reg_bit_set(CANDS_PHY0_(1052)+chn_offset,0,11,0x300);
	//phy_grp_slave_delay2
	reg_bit_set(CANDS_PHY0_(1052)+chn_offset,16,11,0x300);
	//phy_grp_slave_delay3
	reg_bit_set(CANDS_PHY0_(1053)+chn_offset,0,11,0x300);
	}
	#else
	//phy_grp_slave_delay0
	reg_bit_set(CANDS_PHY0_(1051)+chn_offset,8,11,0x300);
	//phy_grp_slave_delay1
	reg_bit_set(CANDS_PHY0_(1052)+chn_offset,0,11,0x300);
	//phy_grp_slave_delay2
	reg_bit_set(CANDS_PHY0_(1052)+chn_offset,16,11,0x300);
	//phy_grp_slave_delay3
	reg_bit_set(CANDS_PHY0_(1053)+chn_offset,0,11,0x300);
	#endif
	//phy_sw_txio_ctl0
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,16,4,0);
	//phy_sw_txio_ctl1
	reg_bit_set(CANDS_PHY0_(1036)+chn_offset,24,4,0);
	//phy_sw_txio_ctl2
	reg_bit_set(CANDS_PHY0_(1037)+chn_offset,0,4,0);
	//phy_sw_txio_ctl3
	reg_bit_set(CANDS_PHY0_(1037)+chn_offset,8,4,0);
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
	reg_bit_set(CANDS_PHY0_(1098)+chn_offset,0,16,0);

	#if DO_DFS_INIT
	for(i=0; i<4; i++)
	{
	phy_reg_switch_dfs(chn_num,i);
	//phy_pad_vref_ctrl_ac,bit12~9:mode_lv,2=lp3,6=lp4rang1,7=lp4rang2  bit8:en_lv  bit5~0:vrefsel_lv,5=50%vddq
	reg_bit_set(CANDS_PHY0_(1049)+chn_offset,16,14,islp3?0x51f:lp4_phy_ca_vref[i]);
	//phy_pad_vref_ctrl_dq0
	reg_bit_set(CANDS_PHY0_(1047)+chn_offset, 8,14,islp3?0x52B:lp4_phy_dq_vref_slice0[i]);
	//phy_pad_vref_ctrl_dq1
	reg_bit_set(CANDS_PHY0_(1048)+chn_offset, 0,14,islp3?0x52B:lp4_phy_dq_vref_slice1[i]);
	//phy_pad_vref_ctrl_dq2
	reg_bit_set(CANDS_PHY0_(1048)+chn_offset,16,14,islp3?0x52B:lp4_phy_dq_vref_slice2[i]);
	//phy_pad_vref_ctrl_dq3
	reg_bit_set(CANDS_PHY0_(1049)+chn_offset, 0,14,islp3?0x52B:lp4_phy_dq_vref_slice3[i]);
	}
	#else
	//phy_pad_vref_ctrl_ac,bit12~9:mode_lv,2=lp3,6=lp4rang1,7=lp4rang2  bit8:en_lv  bit5~0:vrefsel_lv,5=50%vddq
	reg_bit_set(CANDS_PHY0_(1049)+chn_offset,16,14,islp3?0x51f:0xf1f);
	//phy_pad_vref_ctrl_dq0
	reg_bit_set(CANDS_PHY0_(1047)+chn_offset, 8,14,islp3?0x51f:0xf1f);
	//phy_pad_vref_ctrl_dq1
	reg_bit_set(CANDS_PHY0_(1048)+chn_offset, 0,14,islp3?0x51f:0xf1f);
	//phy_pad_vref_ctrl_dq2
	reg_bit_set(CANDS_PHY0_(1048)+chn_offset,16,14,islp3?0x51f:0xf1f);
	//phy_pad_vref_ctrl_dq3
	reg_bit_set(CANDS_PHY0_(1049)+chn_offset, 0,14,islp3?0x51f:0xf1f);
	#endif

	//phy_set_dfi_input_0~3, indicate default value of adrctl slice bit
	reg_bit_set(CANDS_PHY0_(1050)+chn_offset, 8,4,0);
	reg_bit_set(CANDS_PHY0_(1050)+chn_offset,16,4,0);
	reg_bit_set(CANDS_PHY0_(1050)+chn_offset,24,4,0);
	reg_bit_set(CANDS_PHY0_(1051)+chn_offset, 0,4,0);

	//phy_pad_addr_drive - ddr202
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,20,1,0); 					//lpddr3_odt_en
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,19,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,18,1,islp3?0:1); 			//lpddr4_en
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,17,1,0); 					//boostp
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,16,1,0); 					//boostn
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,13,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,12,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,9,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,8,1,1); 					//slew rate  mode
	//not using here
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,4,4,PHY_ADDR_DRV); 		//drive strength
	reg_bit_set(CANDS_PHY0_(1075)+chn_offset,0,4,PHY_ADDR_DRV); 		//drive strength

	//phy_pad_cke_drive - ddr202
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,20,1,0); 					//lpddr3_odt_en
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,19,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,18,1,islp3?0:1); 			//lpddr4_en
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,17,1,0); 					//boostp
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,16,1,0); 					//boostn
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,13,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,12,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,9,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,4,4,PHY_ADDR_DRV); 		//drive strength
	reg_bit_set(CANDS_PHY0_(1082)+chn_offset,0,4,PHY_ADDR_DRV); 		//drive strength

	//phy_pad_clk_drive  - ddr203
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,21,1,0); 					//rpull
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,20,1,0); 					//lpddr3_odt_en
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,19,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,18,1,islp3?0:1); 			//lpddr4_en
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,17,1,0); 					//boostp
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,16,1,0); 					//boostn
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,13,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,12,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,9,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,4,4,PHY_ADDR_DRV); 		//drive strength
	reg_bit_set(CANDS_PHY0_(1076)+chn_offset,0,4,PHY_ADDR_DRV); 		//drive strength

	//phy_pad_cs_drive   - ddr202
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,20,1,0); 					//lpddr3_odt_en
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,19,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,18,1,islp3?0:1); 			//lpddr4_en
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,17,1,0); 					//boostp
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,16,1,0); 					//boostn
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,13,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,12,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,9,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,4,4,PHY_ADDR_DRV); 		//drive strength
	reg_bit_set(CANDS_PHY0_(1086)+chn_offset,0,4,PHY_ADDR_DRV); 		//drive strength

	//phy_pad_data_drive - ddr202
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,12,1,0); 					//lpddr3_odt_en
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,11,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,10,1,islp3?0:1); 			//lpddr4_en
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,9,1,0); 					//boostp
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,8,1,0); 					//boostn
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,5,3,PHY_DATA_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,4,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,1,3,PHY_DATA_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,0,1,1); 					//slew rate  mode

	//phy_pad_dqs_drive  - ddr203
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,29,1,1); 					//rpull
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,28,1,0); 					//lpddr3_odt_en
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,27,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,26,1,islp3?0:1); 			//lpddr4_en
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,25,1,0); 					//boostp
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,24,1,0); 					//boostn
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,21,3,PHY_DATA_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,20,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,17,3,PHY_DATA_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,16,1,1); 					//slew rate  mode

	//phy_pad_fdbk_drive - ddr202
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,20,1,0); 					//lpddr3_odt_en
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,19,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,18,1,islp3?0:1); 			//lpddr4_en
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,17,1,0); 					//boostp
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,16,1,0); 					//boostn
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,13,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,12,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,9,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,4,4,PHY_ADDR_DRV); 		//drive strength
	reg_bit_set(CANDS_PHY0_(1073)+chn_offset,0,4,PHY_ADDR_DRV); 		//drive strength

	//phy_pad_rst_drive  - ddr202
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,20,1,0); 					//lpddr3_odt_en
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,19,1,0); 					//pod
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,18,1,islp3?0:1); 			//lpddr4_en
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,17,1,0); 					//boostp
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,16,1,0); 					//boostn
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,13,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,12,1,1); 					//slew rate mode
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,9,3,PHY_ADDR_SLEW_RATE); 	//slew rate value
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,8,1,1); 					//slew rate  mode
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,4,4,PHY_ADDR_DRV); 		//drive strength
	reg_bit_set(CANDS_PHY0_(1084)+chn_offset,0,4,PHY_ADDR_DRV); 		//drive strength

	//phy_pad_addr_term - ddr202
	reg_bit_set(CANDS_PHY0_(1080)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1080)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_clk_term
	reg_bit_set(CANDS_PHY0_(1081)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1081)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_cs_term
	reg_bit_set(CANDS_PHY0_(1087)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1087)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_data_term
	reg_bit_set(CANDS_PHY0_(1078)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_dqs_term
	reg_bit_set(CANDS_PHY0_(1079)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_fdbk_term
	reg_bit_set(CANDS_PHY0_(1077)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1077)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

	//phy_pad_rst_term
	reg_bit_set(CANDS_PHY0_(1085)+chn_offset,17,1,0); 					//tsel
	reg_bit_set(CANDS_PHY0_(1085)+chn_offset, 0,17,0x4410); 			//pvtr/n/p

}


void cands_ac_cal_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T* phy_timing_info,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	uint32 chn_offset   = (chn_num==0)?0:0x00800000;
	BOOLEAN islp3 = IS_LPDDR3(ddr_type);
	uint32 cal_clk_div = 0;

	#if 1
	switch(DDR_CLK_CAL)
	{
		//lpddr3
		case 156: cal_clk_div = 2;break;		//clk_ctrl/4
		case 311: cal_clk_div = 3;break;		//clk_ctrl/8
		case 233: cal_clk_div = 3;break;		//clk_ctrl/8
		case 368: cal_clk_div = 4;break;		//clk_ctrl/16
		case 460: cal_clk_div = 4;break;		//clk_ctrl/16
		case 622: cal_clk_div = 4;break;		//clk_ctrl/16
		case 933: cal_clk_div = 5;break;		//clk_ctrl/32
		//lpddr4
		case 26:  cal_clk_div = 1;break;			//clk_ctrl/2
		case 234:  cal_clk_div = 3;break;		//clk_ctrl/8
		case 466: cal_clk_div = 4;break;		//clk_ctrl/16
		case 934: cal_clk_div = 5;break;		//clk_ctrl/32
		case 1400: cal_clk_div = 6;break;		//clk_ctrl/64
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
		cal_clk_div = 6; //clk_ctrl/64
	}
	#endif
	//phy_cal_clk_select, pad calibration clk, 0/1: clk_ctrl/2  2/3/4/5/6/7: clk_ctr/4/8/16/32/64/128
	reg_bit_set(CANDS_PHY0_(1095)+chn_offset, 8,3,cal_clk_div);

	//phy_cal_interval_count, periodic calibration cycle, when phy_cal_mode[1]=1
	__raw_writel(CANDS_PHY0_(1094)+chn_offset, 0);	//about 712ms
	//phy_cal_mode
	reg_bit_set(CANDS_PHY0_(1093)+chn_offset, 0,1,0); //init_disable, disable pad cal when init

	if(aon_ver_id)
	{
		reg_bit_set(CANDS_PHY0_(1093)+chn_offset, 1,1,0); //auto_en, enable automatic cal
	}
	else
	{
		reg_bit_set(CANDS_PHY0_(1093)+chn_offset, 1,1,0); //auto_en, enable automatic cal
	}
	reg_bit_set(CANDS_PHY0_(1093)+chn_offset, 2,2,1); //base_mode ?????
	reg_bit_set(CANDS_PHY0_(1093)+chn_offset, 4,4,islp3?0x2:0x6); //pad_cal_mode ??????

	//phy_cal_sample_wait
	reg_bit_set(CANDS_PHY0_(1095)+chn_offset, 0,8,0x8);

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
	phy_reg_switch_dfs(chn_num,FN_CTL_TARGET);
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
#endif //#ifndef DDR_IP_CONFIG_FILE
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


BOOLEAN ddr_clk_set(DDR_CHANNEL_NUM_E chn_num,unsigned int ddr_clk,BOOLEAN islp3)
{

	uint32 dpll_kint = 0;
	uint32 dpll_nint = 0;
	uint32 clk_1xdiv = 0;
	uint32 clk_2xdiv = 0;
	uint32 clk_emc_sel=0;
	uint32 emc_ckg_sel=0;
	uint32 ddr_freq   = 0;
	//lp3 dpll = 920mhz, lp4 dpll = 1392mhz
	dpll_nint = islp3?0x23:0x35;
	dpll_kint = islp3?0x313b13:0x44ec4e;
	//dpll_kint = islp3?0x49D89D:0x6C4EC4;
	//dpll_kint = islp3?0xE2762:0xD89D8;

	ddr_freq = __get_mhz_num(ddr_clk);
	switch(ddr_freq)
	{
		//lpddr4
		case 1400:	clk_2xdiv = 0; clk_1xdiv = 1; clk_emc_sel = 3; emc_ckg_sel = 0x7; break;
		case 934:	clk_2xdiv = 2; clk_1xdiv = 0; clk_emc_sel = 3; emc_ckg_sel = 0x13; break;
		case 700:	clk_2xdiv = 1; clk_1xdiv = 1; clk_emc_sel = 3; emc_ckg_sel = 0xf; break;
		case 466:	clk_2xdiv = 2; clk_1xdiv = 1; clk_emc_sel = 3; emc_ckg_sel = 0x17; break;
		case 234:	clk_2xdiv = 5; clk_1xdiv = 1; clk_emc_sel = 3; emc_ckg_sel = 0x2f; break;
		//lpddr3
		case 933:	clk_2xdiv = 0; clk_1xdiv = 1; clk_emc_sel = 3; emc_ckg_sel = 0x7; break;
		case 622:	clk_2xdiv = 2; clk_1xdiv = 0; clk_emc_sel = 3; emc_ckg_sel = 0x13; break;
		case 460:	clk_2xdiv = 1; clk_1xdiv = 1; clk_emc_sel = 3; emc_ckg_sel = 0xf; break;
		case 368:	clk_2xdiv = 4; clk_1xdiv = 0; clk_emc_sel = 3; emc_ckg_sel = 0x23; break;
		case 233:	clk_2xdiv = 3; clk_1xdiv = 1; clk_emc_sel = 3; emc_ckg_sel = 0x1f; break;
		case 311:	clk_2xdiv = 2; clk_1xdiv = 1; clk_emc_sel = 3; emc_ckg_sel = 0x17; break;
		case 156:	clk_2xdiv = 5; clk_1xdiv = 1; clk_emc_sel = 3; emc_ckg_sel = 0x2f; break;
		//boot_freq f4= lp4/26m
		case 26:		clk_2xdiv = 0; clk_1xdiv = 1; clk_emc_sel = 0; emc_ckg_sel = 0x4; break;
		default:	while(1); //other invald frequency
	}

	if(chn_num == 0)
	{
		#ifdef DDR_CLK_FLOATING
		//clear div_s and mod_en to 0
		reg_bit_set(ANA_DPLL_THM_TOP_0_MODU_CTRL_0, 0, 1, 0);
		reg_bit_set(ANA_DPLL_THM_TOP_0_DIV_CTRL_0, 12, 1, 0);
		#endif

		//set dpll0
		REG32(ANA_DPLL_THM_TOP_0_CLK_CTRL_0)=0xE49F;
		reg_bit_set(ANA_DPLL_THM_TOP_0_MODU_CTRL_0, 25, 7,dpll_nint);
		reg_bit_set(ANA_DPLL_THM_TOP_0_MODU_CTRL_0,  2,23,dpll_kint);

		#ifdef DDR_CLK_FLOATING
		reg_bit_set(ANA_DPLL_THM_TOP_0_DIV_CTRL_0, 12, 1, 1);
		reg_bit_set(ANA_DPLL_THM_TOP_0_MODU_CTRL_0, 0, 1, 1);
		#endif

		//set div
		reg_bit_set(AON_APB_CGM_CFG, 0,7, (clk_1xdiv<<6)|(clk_2xdiv<<2)|clk_emc_sel);

		//enable 1x/2x clk
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,  15, 2, 3);
                reg_bit_set(ANA_DPLL_THM_TOP_0_REG_SEL_CFG_0, 5, 1, 1);  //Pdebug_eb
                reg_bit_set(ANA_DPLL_THM_TOP_0_PWR_CTRL_0, 0, 1, 1);  //reset_eb
                wait_us(3);
                reg_bit_set(ANA_DPLL_THM_TOP_0_PWR_CTRL_0, 0, 1, 0);  //reset_eb
                wait_us(50);
                reg_bit_set(ANA_DPLL_THM_TOP_0_REG_SEL_CFG_0, 5, 1, 0);  //Pdebug_eb

	}
	else
	{
		//disable pub1 force shutdown
		reg_bit_set(PMU_APB_PD_PUB1_SYS_CFG, 25, 1,0);

		#ifdef DDR_CLK_FLOATING
		//clear div_s and mod_en to 0
		reg_bit_set(ANA_DPLL_THM_TOP_1_MODU_CTRL_0, 0, 1, 0);
		reg_bit_set(ANA_DPLL_THM_TOP_1_DIV_CTRL_0, 12, 1, 0);
		#endif

		//set dpll1
		REG32(ANA_DPLL_THM_TOP_1_CLK_CTRL_0)=0xE49F;
		reg_bit_set(ANA_DPLL_THM_TOP_1_MODU_CTRL_0, 25, 7,dpll_nint);
		reg_bit_set(ANA_DPLL_THM_TOP_1_MODU_CTRL_0,  2,23,dpll_kint);

		#ifdef DDR_CLK_FLOATING
		reg_bit_set(ANA_DPLL_THM_TOP_1_DIV_CTRL_0, 12, 1, 1);
		reg_bit_set(ANA_DPLL_THM_TOP_1_MODU_CTRL_0, 0, 1, 1);
		#endif

		//set div
		reg_bit_set(AON_APB_CGM_CFG, 16,7, (clk_1xdiv<<6)|(clk_2xdiv<<2)|clk_emc_sel);

		//enable 1x/2x clk
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,  17, 2, 3);
                reg_bit_set(ANA_DPLL_THM_TOP_1_REG_SEL_CFG_0, 5, 1, 1);  //Pdebug_eb
                reg_bit_set(ANA_DPLL_THM_TOP_1_PWR_CTRL_0, 0, 1, 1);  //reset_eb
                wait_us(3);
                reg_bit_set(ANA_DPLL_THM_TOP_1_PWR_CTRL_0, 0, 1, 0);  //reset_eb
                wait_us(50);
                reg_bit_set(ANA_DPLL_THM_TOP_1_REG_SEL_CFG_0, 5, 1, 0);  //Pdebug_eb

	}

	return TRUE;
}

void ddr_init_trigger(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	if(aon_ver_id)
	{
		//pi_start
		reg_bit_set(CANDS_PI0_(0)+chn_offset,0,1,PI_START);
		//trigger whole ddr init flow, set START to 1
		reg_bit_set(CANDS_CTL0_(0)+chn_offset,0,1,1);
	}
	else
	{
		//trigger whole ddr init flow, set START to 1
		reg_bit_set(CANDS_CTL0_(0)+chn_offset,0,1,1);
		wait_us(10);
		Do_RX_CAL_DQX_c();
		manual_clear_gate_init(chn_num);
		wait_us(10);
		//pi_start
		reg_bit_set(CANDS_PI0_(0)+chn_offset,0,1,PI_START);
	}
}
void vref_rang_cfg(uint32 freq_sel,uint32 chn_offset)
{
    uint32 i=0;
    switch(freq_sel)
    {
        case 0:
            dq_vref_training_setting(chn_offset);
            w2w_samecs_dly(chn_offset,0x0);
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(5+(i*128))+chn_offset), 16, 1 , 0x0);
            }
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(6+(i*128))+chn_offset), 24, 1 , 0x0);
            }
            break;
        case 1:
            dq_vref_training_setting(chn_offset);
            w2w_samecs_dly(chn_offset,0x0);
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(5+(i*128))+chn_offset), 16, 1 , 0x0);
            }
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(6+(i*128))+chn_offset), 24, 1 , 0x0);
            }
            break;
        case 2:
            dq_vref_training_setting(chn_offset);
            w2w_samecs_dly(chn_offset,0x0);
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(5+(i*128))+chn_offset), 16, 1 , 0x0);
            }
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(6+(i*128))+chn_offset), 24, 1 , 0x0);
            }
            break;
        case 3:
            dq_vref_training_setting(chn_offset);
            w2w_samecs_dly(chn_offset,0x0);
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(5+(i*128))+chn_offset), 16, 1 , 0x0);
            }
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(6+(i*128))+chn_offset), 24, 1 , 0x0);
            }
            break;
        case 4:
            dq_odt_vref_training_setting(chn_offset);
            w2w_samecs_dly(chn_offset,0x0);
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(5+(i*128))+chn_offset), 16, 1 , 0x1);
            }
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(6+(i*128))+chn_offset), 0 , 8 , 0x07);
            }
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(6+(i*128))+chn_offset), 24, 1 , 0x1);
            }
            for(i=0;i<4;i++)
            {
                reg_bit_set((CANDS_PHY0_(7+(i*128))+chn_offset), 0 , 8 , 0x07);
            }
            break;
       default:
            break;
    }
}
#if 1
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

        reg_bit_set(CANDS_PHY0_(23)+chn_offset+(slice*0x200), 16, 3, 0);     //phy_master_dly_lock_obs_select
        reg_bit_set(CANDS_PHY0_(14)+chn_offset+(slice*0x200), 24, 1, 1);     //sc_phy_snap_obs_regs
        tmp=reg_bit_get(CANDS_PHY0_(38)+chn_offset+(slice*0x200), 16, 10);     //phy_master_dly_lock_obs
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
    reg_bit_set(CANDS_CTL0_(229)+chn_offset,24, 1, islp3?1:0);  ///?????? define which part to updat MR12&MR14 in init/dfs/sw mrw 0:ctl 1:phy or pi
    //____________________mr12_cs0____________________
    tmp=reg_bit_get(CANDS_PI0_(157)+chn_offset,8,8);       //PI_MR12_DATA_F0_0   ----- CTL_MR12_DATA_F4_0 
    reg_bit_set(CANDS_CTL0_(212)+chn_offset,16,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(158)+chn_offset,24,8);       //PI_MR12_DATA_F1_0    -----  CTL_MR12_DATA_F0_0 
    reg_bit_set(CANDS_CTL0_(211)+chn_offset,16,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(160)+chn_offset,8,8);       //PI_MR12_F2_0    ------   CTL_MR12_DATA_F1_0 
    reg_bit_set(CANDS_CTL0_(211)+chn_offset,24,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(161)+chn_offset,24,8);       //PI_MR12_F3_0   -----   CTL_MR12_DATA_F2_0
    reg_bit_set(CANDS_CTL0_(212)+chn_offset,0,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(163)+chn_offset,8,8);       //PI_MR12_F4_0   -----   CTL_MR12_DATA_F3_0
    reg_bit_set(CANDS_CTL0_(212)+chn_offset,8,8,tmp);
	//____________________mr12_cs1____________________
    tmp=reg_bit_get(CANDS_PI0_(165)+chn_offset,0,8);       //PI_MR12_F0_1   ----- CTL_MR12_DATA_F4_1
    reg_bit_set(CANDS_CTL0_(224)+chn_offset,0,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(166)+chn_offset,16,8);       //PI_MR12_F1_1   ----- CTL_MR12_DATA_F0_1
    reg_bit_set(CANDS_CTL0_(223)+chn_offset,0,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(168)+chn_offset,0,8);       //PI_MR12_F2_1   ----- CTL_MR12_DATA_F1_1
    reg_bit_set(CANDS_CTL0_(223)+chn_offset,8,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(169)+chn_offset,16,8);       //PI_MR12_F3_1   ----- CTL_MR12_DATA_F2_1
    reg_bit_set(CANDS_CTL0_(223)+chn_offset,16,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(171)+chn_offset, 0,8);       //PI_MR12_F4_1   ----- CTL_MR12_DATA_F3_1
    reg_bit_set(CANDS_CTL0_(223)+chn_offset,24,8,tmp);
    //____________________mr14_cs0____________________
    tmp=reg_bit_get(CANDS_PI0_(157)+chn_offset,16,8);       //PI_MR14_F0_0   ----- CTL_MR14_DATA_F4_0
    reg_bit_set(CANDS_CTL0_(214)+chn_offset,0,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(159)+chn_offset,0,8);       //PI_MR14_F1_0   ----- CTL_MR14_DATA_F0_0
    reg_bit_set(CANDS_CTL0_(213)+chn_offset,0,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(160)+chn_offset,16,8);       //PI_MR14_F2_0   ----- CTL_MR14_DATA_F1_0
    reg_bit_set(CANDS_CTL0_(213)+chn_offset,8,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(162)+chn_offset,0,8);       //PI_MR14_F3_0   ----- CTL_MR14_DATA_F2_0
    reg_bit_set(CANDS_CTL0_(213)+chn_offset,16,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(163)+chn_offset,16,8);       //PI_MR14_F4_0   ----- CTL_MR14_DATA_F3_0
    reg_bit_set(CANDS_CTL0_(213)+chn_offset,24,8,tmp);
    //____________________mr14_cs1____________________
    tmp=reg_bit_get(CANDS_PI0_(165)+chn_offset,8,8);       //PI_MR14_F0_1   ----- CTL_MR14_DATA_F4_1
    reg_bit_set(CANDS_CTL0_(225)+chn_offset,16,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(166)+chn_offset,24,8);       //PI_MR14_F1_1   ----- CTL_MR14_DATA_F0_1
    reg_bit_set(CANDS_CTL0_(224)+chn_offset,16,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(168)+chn_offset,8,8);       //PI_MR14_F2_1   ----- CTL_MR14_DATA_F1_1
    reg_bit_set(CANDS_CTL0_(224)+chn_offset,24,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(169)+chn_offset,24,8);       //PI_MR14_F3_1   ----- CTL_MR14_DATA_F2_1
    reg_bit_set(CANDS_CTL0_(225)+chn_offset,0,8,tmp);

    tmp=reg_bit_get(CANDS_PI0_(171)+chn_offset, 8,8);       //PI_MR14_F4_1   ----- CTL_MR14_DATA_F3_1
    reg_bit_set(CANDS_CTL0_(225)+chn_offset, 8,8,tmp);
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
		//reg_bit_set(PUB0_APB_FREQ_ACK_LP4_INIT+chn_offset,0,1,1);

		while(pi_tr_done == 0)
		{
			i++;
			pi_tr_done = (REG32(CANDS_PI0_(213)+chn_offset)&0x1);

			if(1==pi_tr_done)
				break;

			if(REG32(PUB0_APB_FREQ_CHANGE_LP4_REQ+chn_offset)&0x1)
			{
				//read *_11e0 bit[8:4] freq_type and does frequency change to 0x402e_0098 according to dfs table???
				freq_sel = (REG32(PUB0_APB_FREQ_CHANGE_LP4_TYPE+chn_offset)&0x3e)>>1;
                                //vref rang set
                                vref_rang_cfg( freq_sel, chn_offset);
				//set calvl traget freq ddr clk div
				reg_bit_set(AON_APB_CGM_CFG,(chn_num<<4),8,pi_fn_div[freq_sel]);
                                wait_us(50);    //wait pll locked,
				if(chn_num == 0)
				{
					//write freq_ack
					reg_bit_set(PUB0_APB_FREQ_CHANGE_LP4_ACK,1,1,1);
				}
				else
				{
					//write freq_ack
					reg_bit_set(PUB1_APB_FREQ_CHANGE_LP4_ACK,0,1,1);
				}
				wait_us(3);
				if(chn_num == 0)
				{
					//write freq_ack
					reg_bit_set(PUB0_APB_FREQ_CHANGE_LP4_ACK,1,1,0);
				}
				else
				{
					//write freq_ack
					reg_bit_set(PUB1_APB_FREQ_CHANGE_LP4_ACK,0,1,0);
				}
				//write int_clr
				//reg_bit_set(PUB0_APB_FREQ_CHANGE_LP4_INIT+chn_offset,1,1,1);

				//write *_21e0=32'h3FE, to do write 1 clear all register except for enable bit
				//REG32(PUB0_APB_FREQ_CHANGE_WCL_LP4_INIT+chn_offset) = 0x3FE;
			}
			wait_us(10);

			pi_tr_done = (REG32(CANDS_PI0_(213)+chn_offset)&0x1);
#if 0
			if((i <= 1500) && ((i%300) == 0))
			{
				if(chn_num == 0)
                                __ddr_print("\r\nddr polling pub0 pi tr hung, do rx cal workaround...");
                                else
                                __ddr_print("\r\nddr polling pub1 pi tr hung, do rx cal workaround...");
					//re-do rx offset calibration
					REG32(0Xc00020DC+chn_offset) = 0x00200001;
                                REG32(0Xc00022DC+chn_offset) = 0x00200001;
                                REG32(0Xc00024DC+chn_offset) = 0x00200001;
                                REG32(0Xc00026DC+chn_offset) = 0x00200001;
			}
#endif
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

		ctl_tr_done = (REG32(CANDS_CTL0_(292)+chn_offset)&0x10);

		timeout++;
		#ifdef DRAM_LPDDR3
		if(timeout == 0x800)
		{
			// do manual rx cal
			reg_bit_set(CANDS_PHY0_(55), 0,1,1);
			reg_bit_set(CANDS_PHY0_(183),0,1,1);
			reg_bit_set(CANDS_PHY0_(311),0,1,1);
			reg_bit_set(CANDS_PHY0_(439),0,1,1);
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

void ddr_dfs_busmon_cfg(BOOLEAN islp3)
{
    volatile uint32 i=0;
	#ifdef DRAM_LPDDR3
    //CGM_CM3_TMR2_EN
    reg_bit_set(AON_APB_CGM_REG1,19,1,1);
    //26M force enable
    reg_bit_set(AON_CLK_PREDIV_GATE_EN_SEL3_CFG,2,1,0);
    reg_bit_set(AON_CLK_PREDIV_GATE_EN_CTL3_CFG,2,1,1);
    //enable busmonitor timer eb
    reg_bit_set(AON_APB_EB_AON_ADD1,1,1,1);

    //enable axi busmonitor
    reg_bit_set(PUB0_APB_BUSMON_CFG,16,1,1);


    //set bandwidth busmonitor over/under flow
    //pub0
    __raw_writel(PUB0_DFS_BUSMON_OVERFLOW_TSHOLD_F0,BW_KB(3744));//f0 max bandwidth is 1248Mbyte/s
    __raw_writel(PUB0_DFS_BUSMON_UNDERFLOW_TSHOLD_F0,0);
    __raw_writel(PUB0_DFS_BUSMON_OVERFLOW_TSHOLD_F1,BW_KB(7464));//f1 max bandwidth is 2488Mbyte/s
    __raw_writel(PUB0_DFS_BUSMON_UNDERFLOW_TSHOLD_F1,BW_KB(2496));
    __raw_writel(PUB0_DFS_BUSMON_OVERFLOW_TSHOLD_F2,BW_KB(11184));//f2 max bandwidth is 3728Mbyte/s
    __raw_writel(PUB0_DFS_BUSMON_UNDERFLOW_TSHOLD_F2,BW_KB(4976));
    __raw_writel(PUB0_DFS_BUSMON_OVERFLOW_TSHOLD_F3,BW_KB(22392));//f3 max bandwidth is 7464Mbyte/s
    __raw_writel(PUB0_DFS_BUSMON_UNDERFLOW_TSHOLD_F3,BW_KB(7456));

    __raw_writel(PUB0_DFS_BUSMON_INT_EN,0x7);//busmon interrupt enable

#if 0
    //set busmonitor timer1 cnt value :10ms
    __raw_writel(BUS_MONITOR_TIMER_HIGH_LEN_T1 ,0x3F7A0);//high_len,(*38.5ns),period = high_len + low_len
    __raw_writel(BUS_MONITOR_TIMER_LOW_LEN_T1 ,0x1);//low_len,(*38.5ns),shouldnot set 0
    reg_bit_set(BUS_MONITOR_TIMER_CTRL ,0,1,1);//timer1_en
    __raw_writel(BUS_MONITOR_TIMER_CTRL ,0x1);//timer_en
#endif

#if 1
    //set busmonitor timer2 cnt value :10ms
    reg_bit_set(BUS_MONITOR_TIMER_OUT_SEL ,0,1,1);//dfi busmonitor use timer2
    __raw_writel(BUS_MONITOR_TIMER_HIGH_LEN_T2 ,0x3F7A0);//high_len,(*38.5ns),period = high_len + low_len
    __raw_writel(BUS_MONITOR_TIMER_LOW_LEN_T2 ,0x1);//low_len,(*38.5ns),shouldnot set 0
    reg_bit_set(BUS_MONITOR_TIMER_CTRL ,2,1,1);//timer2_en
#endif

    __raw_writel(PUB0_DFS_BUSMON_CFG,0x1);//bit0: busmon_en bit2:dfs_req_en
    dfs_busmon_eb(0,0);     //disable busmon
	#else
    //CGM_CM3_TMR2_EN
    reg_bit_set(AON_APB_CGM_REG1,19,1,1);
    //26M force enable
    reg_bit_set(AON_CLK_PREDIV_GATE_EN_SEL3_CFG,2,1,0);
    reg_bit_set(AON_CLK_PREDIV_GATE_EN_CTL3_CFG,2,1,1);
    //enable busmonitor timer eb
    reg_bit_set(AON_APB_EB_AON_ADD1,1,1,1);

    //enable axi busmonitor
    reg_bit_set(PUB0_APB_BUSMON_CFG,16,1,1);


    //set bandwidth busmonitor over/under flow
    //pub0
    __raw_writel(PUB0_DFS_BUSMON_OVERFLOW_TSHOLD_F0,4915200);
    __raw_writel(PUB0_DFS_BUSMON_UNDERFLOW_TSHOLD_F0,0);
    __raw_writel(PUB0_DFS_BUSMON_OVERFLOW_TSHOLD_F1,16000000);
    __raw_writel(PUB0_DFS_BUSMON_UNDERFLOW_TSHOLD_F1,3276800);
    __raw_writel(PUB0_DFS_BUSMON_OVERFLOW_TSHOLD_F2,26880000);
    __raw_writel(PUB0_DFS_BUSMON_UNDERFLOW_TSHOLD_F2,8000000);
    __raw_writel(PUB0_DFS_BUSMON_OVERFLOW_TSHOLD_F3,BW_KB(96000));
    __raw_writel(PUB0_DFS_BUSMON_UNDERFLOW_TSHOLD_F3,23520000);
    __raw_writel(PUB0_DFS_BUSMON_INT_EN,0x7);//busmon interrupt enable

	#if 0
    //set busmonitor timer1 cnt value :10ms
    __raw_writel(BUS_MONITOR_TIMER_HIGH_LEN_T1 ,0x3F7A0);//high_len,(*38.5ns),period = high_len + low_len
    __raw_writel(BUS_MONITOR_TIMER_LOW_LEN_T1 ,0x1);//low_len,(*38.5ns),shouldnot set 0
    reg_bit_set(BUS_MONITOR_TIMER_CTRL ,0,1,1);//timer1_en
    __raw_writel(BUS_MONITOR_TIMER_CTRL ,0x1);//timer_en
	#endif

	#if 1
    //set busmonitor timer2 cnt value :10ms
	reg_bit_set(BUS_MONITOR_TIMER_OUT_SEL ,0,1,1);//dfi busmonitor use timer2
	__raw_writel(BUS_MONITOR_TIMER_HIGH_LEN_T2 ,0x3F7A0);//high_len,(*38.5ns),period = high_len + low_len
	__raw_writel(BUS_MONITOR_TIMER_LOW_LEN_T2 ,0x1);//low_len,(*38.5ns),shouldnot set 0
	reg_bit_set(BUS_MONITOR_TIMER_CTRL ,2,1,1);//timer2_en
	#endif

    __raw_writel(PUB0_DFS_BUSMON_CFG,0x1);//bit0: busmon_en bit2:dfs_req_en
    reg_bit_set(PUB0_DFS_BUSMON_CFG,3,1,0x1);//bit3: sw control frequency select enable
    reg_bit_set(PUB0_DFS_BUSMON_CFG,4,2,FN_CTL_TARGET);//bit[5:4]: sw control frequency selcet

    reg_bit_set(PUB1_APB_BUSMON_CFG,16,1,1);
    //pub1
    __raw_writel(PUB1_DFS_BUSMON_OVERFLOW_TSHOLD_F0,BW_KB(4800));
    __raw_writel(PUB1_DFS_BUSMON_UNDERFLOW_TSHOLD_F0,0);
    __raw_writel(PUB1_DFS_BUSMON_OVERFLOW_TSHOLD_F1,BW_KB(9600));
    __raw_writel(PUB1_DFS_BUSMON_UNDERFLOW_TSHOLD_F1,BW_KB(3200));
    __raw_writel(PUB1_DFS_BUSMON_OVERFLOW_TSHOLD_F2,BW_KB(14400));
    __raw_writel(PUB1_DFS_BUSMON_UNDERFLOW_TSHOLD_F2,BW_KB(6400));
    __raw_writel(PUB1_DFS_BUSMON_OVERFLOW_TSHOLD_F3,BW_KB(96000));
    __raw_writel(PUB1_DFS_BUSMON_UNDERFLOW_TSHOLD_F3,BW_KB(9600));
    __raw_writel(PUB1_DFS_BUSMON_INT_EN,0x7);//busmon interrupt enable

	__raw_writel(PUB1_DFS_BUSMON_CFG,0x1);//bit1: busmon_en bit2:dfs_req_en
    reg_bit_set(PUB1_DFS_BUSMON_CFG,3,1,0x1);//bit3: sw control frequency select enable
    reg_bit_set(PUB1_DFS_BUSMON_CFG,4,2,FN_CTL_TARGET);//bit[5:4]: sw control frequency selcet
    reg_bit_set(PUB1_DFS_BUSMON_CFG,3,1,0x0);//bit3: sw control frequency select disable
    dfs_busmon_eb(0,0);     //disable busmon
    dfs_busmon_eb(1,0);     //disable busmon
	#endif

}
void busmon_timer1_ms_cfg(uint32 count)
{
    uint32 reg_value;
    float tbusmon=(float)count;
    if(tbusmon > TIME_MS_MAX)
    {
        __ddr_print("busmonitor cycle time overflow ,do nothing .\r\n");
    }
    else
    {
        tbusmon=tbusmon*1000.*1000.;
        tbusmon=tbusmon/DFS_TIMER_STEP;
        reg_value=(uint32)(tbusmon-0.5);

        reg_bit_set(BUS_MONITOR_TIMER_CTRL ,0,1,0);
        __raw_writel(BUS_MONITOR_TIMER_HIGH_LEN_T1 ,reg_value);
        __raw_writel(BUS_MONITOR_TIMER_LOW_LEN_T1 ,0x1);
        reg_bit_set(BUS_MONITOR_TIMER_CTRL ,0,1,1);
    }
}
void dfs_busmon_eb(DDR_CHANNEL_NUM_E chn_num,uint32 flag)
{
	uint32 chn_offset = (0==chn_num)?0:0x00800000;
	reg_bit_set(PUB0_DFS_BUSMON_CFG+chn_offset, 0, 1, flag);
	reg_bit_set(PUB0_DFS_BUSMON_INT_EN+chn_offset, 0, 1, flag);
	reg_bit_set(PUB0_DFS_BUSMON_INT_EN+chn_offset, 1, 1, flag);
	reg_bit_set(PUB0_DFS_BUSMON_INT_EN+chn_offset, 2, 1, flag);
}

struct AXI_BUSMON_LATENCY
{
    uint32 enable;
    uint32 dn_rlatency;
    uint32 dn_wlatency;
    uint32 up_rlatency;
    uint32 up_wlatency;
};
#define AXI_BUSMON_NUM 11
struct AXI_BUSMON_LATENCY axi_busmon_cfg[AXI_BUSMON_NUM]={      //enable, dn_rltc,dm_wltc,up_rltc,up_wltc
                                                               {      1,      0,     0,   1000,   1000}, //A53
                                                               {      1,      0,     0,   1000,   1000}, //DISP
                                                               {      1,      0,     0,   1000,   1000}, //GPU/GSP
                                                               {      1,      0,     0,   1000,   1000}, //AP
                                                               {      1,      0,     0,   1000,   1000}, //CAM
                                                               {      1,      0,     0,   1000,   1000}, //VSP
                                                               {      1,      0,     0,   1000,   1000}, //LWT_DSP
                                                               {      1,      0,     0,   1000,   1000}, //LWT_ACC
                                                               {      1,      0,     0,   1000,   1000}, //PUB CP
                                                               {      1,      0,     0,   1000,   1000}, //AUD CP
                                                               {      1,      0,     0,   1000,   1000}  //CAM2
};
/*clk : unit MHz   ltc_us : unit us */
uint32 axi_busmon_latency_cfg(uint32 clk, uint32 ltc_us)
{
    uint32 reg_value;
    reg_value=ltc_us*clk;
    return reg_value;
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


void dfs_axi_timer_cfg(uint32 ms)
{
    //CGM_CM3_TMR2_EN//cm3 timer config register enable
    reg_bit_set(AON_APB_CGM_REG1,19,1,1);
    //26M force enable
    reg_bit_set(AON_CLK_PREDIV_GATE_EN_SEL3_CFG,2,1,0);
    reg_bit_set(AON_CLK_PREDIV_GATE_EN_CTL3_CFG,2,1,1);
    //enable busmonitor timer eb
    reg_bit_set(AON_APB_EB_AON_ADD1,1,1,1);

    busmon_timer1_ms_cfg(ms );
 #if 0
    __raw_writel(BUS_MONITOR_TIMER_HIGH_LEN_T1 ,0x3F7A0);//high_len,(*38.5ns),period = high_len + low_len
    __raw_writel(BUS_MONITOR_TIMER_LOW_LEN_T1 ,0x1);//low_len,(*38.5ns),shouldnot set 0
    reg_bit_set(BUS_MONITOR_TIMER_CTRL ,0,1,1);//timer1_en
    __raw_writel(BUS_MONITOR_TIMER_CTRL ,0x1);//timer_en
#endif
    #if 0
    //set busmonitor timer2 cnt value :10ms
    reg_bit_set(BUS_MONITOR_TIMER_OUT_SEL ,0,1,1);//dfi busmonitor use timer2
    __raw_writel(BUS_MONITOR_TIMER_HIGH_LEN_T2 ,0x3F7A0);//high_len,(*38.5ns),period = high_len + low_len
    __raw_writel(BUS_MONITOR_TIMER_LOW_LEN_T2 ,0x1);//low_len,(*38.5ns),shouldnot set 0
    reg_bit_set(BUS_MONITOR_TIMER_CTRL ,2,1,1);//timer2_en
    #endif
}
#ifdef DRAM_LPDDR3
void dfs_axi_busmon_cfg(uint32 clk)
{
    uint32 axi_chan=0;
    uint32 chn_num=0;
    uint32 enable=0;
    for(axi_chan=0; axi_chan<10; axi_chan++)
    {
        enable=axi_busmon_cfg[axi_chan].enable;
        axi_busmon_cfg_set(clk, chn_num, axi_chan, enable);
    }
    enable=axi_busmon_cfg[10].enable;
    dfs_axi_busmon_chn10_cfg(clk, chn_num, enable);
}
#endif
#ifdef DRAM_LPDDR4
void dfs_axi_busmon_cfg(uint32 clk)
{
    uint32 axi_chan=0;
    uint32 chn_num=0;
    uint32 enable=0;
    for(chn_num=0; chn_num<2; chn_num++)
    {
        for(axi_chan=0; axi_chan<10; axi_chan++)
        {
            enable=axi_busmon_cfg[axi_chan].enable;
            axi_busmon_cfg_set(clk, chn_num, axi_chan, enable);
        }
        enable=axi_busmon_cfg[10].enable;
        dfs_axi_busmon_chn10_cfg(clk, chn_num, enable);
    }

}
#endif
#ifdef DRAM_LPDDR4
void lp4_dfs_dma_cfg(DDR_CHANNEL_NUM_E chn_num)
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
	REG32(PUB0_APB_DFS_WR_MCTL_REG1_DATA_F0+chn_offset) = 0x1FF; //data0_F0, cal_clk_select
	REG32(PUB0_APB_DFS_WR_MCTL_REG1_DATA_F1+chn_offset) = 0x4FF; //data0_F1, cal_clk_select
	REG32(PUB0_APB_DFS_WR_MCTL_REG1_DATA_F2+chn_offset) = 0x5FF; //data0_F2, cal_clk_select
	REG32(PUB0_APB_DFS_WR_MCTL_REG1_DATA_F3+chn_offset) = 0x6FF; //data0_F3, cal_clk_select


	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG2_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(4)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG2_DATA_F0+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG2_DATA_F1+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG2_DATA_F2+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG2_DATA_F3+chn_offset) = 0x00030000;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG3_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(132)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG3_DATA_F0+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG3_DATA_F1+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG3_DATA_F2+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG3_DATA_F3+chn_offset) = 0x00030000;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG4_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(260)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG4_DATA_F0+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG4_DATA_F1+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG4_DATA_F2+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG4_DATA_F3+chn_offset) = 0x00030000;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG5_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(388)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG5_DATA_F0+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG5_DATA_F1+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG5_DATA_F2+chn_offset) = 0x00020000;
	REG32(PUB0_APB_DFS_WR_MCTL_REG5_DATA_F3+chn_offset) = 0x00030000;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG6_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(5)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG6_DATA_F0+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG6_DATA_F1+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG6_DATA_F2+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG6_DATA_F3+chn_offset) = 0x03006606;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG7_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(133)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG7_DATA_F0+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG7_DATA_F1+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG7_DATA_F2+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG7_DATA_F3+chn_offset) = 0x03006606;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG8_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(261)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG8_DATA_F0+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG8_DATA_F1+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG8_DATA_F2+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG8_DATA_F3+chn_offset) = 0x03006606;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG9_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(389)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG9_DATA_F0+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG9_DATA_F1+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG9_DATA_F2+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG9_DATA_F3+chn_offset) = 0x03006606;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG10_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(6)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG10_DATA_F0+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG10_DATA_F1+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG10_DATA_F2+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG10_DATA_F3+chn_offset) = 0x02006606;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG11_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(134)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG11_DATA_F0+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG11_DATA_F1+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG11_DATA_F2+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG11_DATA_F3+chn_offset) = 0x02006606;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG12_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(262)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG12_DATA_F0+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG12_DATA_F1+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG12_DATA_F2+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG12_DATA_F3+chn_offset) = 0x02006606;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG13_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(390)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG13_DATA_F0+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG13_DATA_F1+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG13_DATA_F2+chn_offset) = 0x02007700;
	REG32(PUB0_APB_DFS_WR_MCTL_REG13_DATA_F3+chn_offset) = 0x02006606;
	#if 1
	//vref
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG14_ADDR+chn_offset, 0, 20, (CANDS_PI0_(162)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG14_DATA_F0+chn_offset) = 0x01724011;
	REG32(PUB0_APB_DFS_WR_MCTL_REG14_DATA_F1+chn_offset) = 0x01724011;
	REG32(PUB0_APB_DFS_WR_MCTL_REG14_DATA_F2+chn_offset) = 0x01724011;
	REG32(PUB0_APB_DFS_WR_MCTL_REG14_DATA_F3+chn_offset) = 0x01281a11;
#if 0
	//phy_vref
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG15_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(1041)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG15_DATA_F0+chn_offset) = 0x000d2e00;
	REG32(PUB0_APB_DFS_WR_MCTL_REG15_DATA_F1+chn_offset) = 0x000d2e00;
	REG32(PUB0_APB_DFS_WR_MCTL_REG15_DATA_F2+chn_offset) = 0x000d2e00;
	REG32(PUB0_APB_DFS_WR_MCTL_REG15_DATA_F3+chn_offset) = 0x000f1f00;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG16_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(1042)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG16_DATA_F0+chn_offset) = 0x0d2e0d2e;
	REG32(PUB0_APB_DFS_WR_MCTL_REG16_DATA_F1+chn_offset) = 0x0d2e0d2e;
	REG32(PUB0_APB_DFS_WR_MCTL_REG16_DATA_F2+chn_offset) = 0x0d2e0d2e;
	REG32(PUB0_APB_DFS_WR_MCTL_REG16_DATA_F3+chn_offset) = 0x0f1f0f1f;

	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG17_ADDR+chn_offset, 0, 20, (CANDS_PHY0_(1043)+chn_offset));
	REG32(PUB0_APB_DFS_WR_MCTL_REG17_DATA_F0+chn_offset) = 0x0d2e0d2e;
	REG32(PUB0_APB_DFS_WR_MCTL_REG17_DATA_F1+chn_offset) = 0x0d2e0d2e;
	REG32(PUB0_APB_DFS_WR_MCTL_REG17_DATA_F2+chn_offset) = 0x0d2e0d2e;
	REG32(PUB0_APB_DFS_WR_MCTL_REG17_DATA_F3+chn_offset) = 0x0d2e0f1f;
#endif
	#endif


	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 16, 16, ((chn_num==0)?0x3000:0x3080)); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 13, 1, 0x1); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 8,  5, 0xF); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 4,  4, 0x2); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 3,  1, 0x0); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 1,  2, 0x0); //dfs_fc_ack-wait_comp_en
	reg_bit_set(PUB0_APB_DFS_WR_MCTL_REG_CFG0+chn_offset, 0,  1, 0x1); //dfs_fc_ack-wait_comp_en
}
#endif

#ifdef DDR_AUTO_DETECT
uint32 cands_mrr(DDR_CHANNEL_NUM_E chn_num, uint32 cs_num, uint32 mr_addr)
{
	uint32 reg_val = 0;
	uint32 mrr_completed;
	uint32 timeout;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	reg_bit_set(CANDS_CTL0_(294)+chn_offset,23,1,1);		// 0x30000504 int_ack , clear bit[23] mrr_completed

	reg_val = (1<<16)|((cs_num&0xFF)<<8)|(mr_addr&0xFF);
	reg_bit_set(CANDS_CTL0_(184)+chn_offset,8,17,reg_val);	// read_modereg

	timeout = 0;
	mrr_completed = 0;
	while(mrr_completed == 0)
	{
		reg_val = REG32(CANDS_CTL0_(292)+chn_offset);		// 0x300004fc int_status bit[23] mrr_completed
		mrr_completed = (reg_val>>23)&0x1;
		if(timeout++ > 0x10000)
			return 0;
	}
	reg_bit_set(CANDS_CTL0_(294)+chn_offset,23,1,1);		// 0x30000504 int_ack , clear bit[23] mrr_completed

	reg_val = REG32(CANDS_CTL0_(185)+chn_offset);		// 0x300002a4 peripheral_mrr_data

	return reg_val;
}
#ifdef DRAM_LPDDR4
uint32 fn_ctl_target=3;
void ddr_freq_target_set(uint32 ddr_clk)
{
    uint32 ddr_freq=0;
    ddr_freq = __get_mhz_num(ddr_clk);
    switch(ddr_freq)
    {
        case 1400:fn_ctl_target=3;break;
        case  700:fn_ctl_target=2;break;
        case  466:fn_ctl_target=1;break;
        case  234:fn_ctl_target=0;break;
        default:break;
    }
}
struct MR8_size_info LP4_MR8_size[] = {
	{LP4_MR8_SIZE_4Gb,2},
	{LP4_MR8_SIZE_6Gb,3},
	{LP4_MR8_SIZE_8Gb,4},
	{LP4_MR8_SIZE_12Gb,6},
	{LP4_MR8_SIZE_16Gb,8},
	{LP4_MR8_SIZE_24Gb,12},
	{LP4_MR8_SIZE_32Gb,16},
};

uint32 cands_lp4_mr8_to_detect_info(uint32 mr8_value,struct ddr_detect_info *detect_info)
{

	uint32 mr8_type;
	uint32 mr8_size;
	uint32 mr8_width;
	uint32 i;

	mr8_type = (mr8_value & 0x3)>>0;
	mr8_size = (mr8_value & 0x3c)>>2;
	mr8_width = (mr8_value & 0xc0)>>6;
        if(mr8_type != S16_SDRAM)
	{
		return FALSE;
	}

        if(mr8_width == LP4_WIDTH_X16)
	{
		detect_info->mem_width = 0x16;
	}else{
		return FALSE;
	}

	for(i=0;i<sizeof(LP4_MR8_size)/sizeof(LP4_MR8_size[0]);i++)
	{
		if(mr8_size == LP4_MR8_size[i].mr8_size)
		{
			detect_info->mem_size = LP4_MR8_size[i].mem_size;
			return TRUE;
		}
	}

	return FALSE;

}

#endif
#ifdef DRAM_LPDDR3
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
#endif
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
        #ifdef DRAM_LPDDR3
	ret = cands_mr8_to_detect_info(mr8_value_cs0,&detect_info_cs0);
        #endif

        #ifdef DRAM_LPDDR4
	ret = cands_lp4_mr8_to_detect_info(mr8_value_cs0,&detect_info_cs0);
        #endif
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
        #ifdef DRAM_LPDDR3
	ret = cands_mr8_to_detect_info(mr8_value_cs1,&detect_info_cs1);
        #endif
        #ifdef DRAM_LPDDR4
	ret = cands_lp4_mr8_to_detect_info(mr8_value_cs1,&detect_info_cs1);
        #endif
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
	reg_bit_set(CANDS_CTL0_(285)+chn_offset,0,2,IS_2CS(ddr_type)?3:1);
	//#else
	//reg_bit_set(CANDS_CTL0_(285)+chn_offset,24,8,1);
	//#endif

	//dram_clk_disable, disable unused cs clock
	//reg_bit_set(CANDS_CTL0_(452)+chn_offset,24,8,IS_2CS(ddr_type)?0xfc:0xfe);
	reg_bit_set(CANDS_CTL0_(417)+chn_offset,0,2,0);

	//calvl_cs
	reg_bit_set(CANDS_CTL0_(378)+chn_offset,24,1, 0);

	//calvl_cs_map
	reg_bit_set(CANDS_CTL0_(388)+chn_offset,24,2, IS_2CS(ddr_type)?3:1);

	//rdlvl_cs
	reg_bit_set(CANDS_CTL0_(349)+chn_offset,16,1, 0);
	//rdlvl_cs_map
	reg_bit_set(CANDS_CTL0_(353)+chn_offset,0,2, IS_2CS(ddr_type));

	#ifdef DRAM_LPDDR4
	//zq_cal_latch_map  ??????
	reg_bit_set(CANDS_CTL0_(278)+chn_offset, 24,2, 1);
	reg_bit_set(CANDS_CTL0_(279)+chn_offset,8,2, IS_2CS(ddr_type)?2:0);

	//zq_cal_start_map   ??????
	reg_bit_set(CANDS_CTL0_(278)+chn_offset, 16,2, 1);
	reg_bit_set(CANDS_CTL0_(279)+chn_offset,0,2, IS_2CS(ddr_type)?2:0);
	//reg_bit_set(CANDS_CTL0_(291)+chn_offset, 0,8, 0);
	#endif

	#ifdef DRAM_LPDDR3
	cs_map = IS_2CS(ddr_type)?3:1;
	#else
	cs_map = IS_2CS(ddr_type)?0xf:5;
	#endif
	//pi_cs_map
	reg_bit_set(CANDS_PI0_(55)+chn_offset,24,4,cs_map);
	//calvl_cs_map
	reg_bit_set(CANDS_PI0_(115)+chn_offset,0,4,cs_map);
	//rdlvl_cs_map
	reg_bit_set(CANDS_PI0_(97)+chn_offset, 0,4, cs_map);
	//rdlvl_gate_cs_map
	reg_bit_set(CANDS_PI0_(97)+chn_offset, 8,4, cs_map);
	//wrlvl_cs_map
	reg_bit_set(CANDS_PI0_(79)+chn_offset, 0,4, cs_map);
	//wdqlvl_cs_map
	reg_bit_set(CANDS_PI0_(150)+chn_offset,0,4, cs_map);

	//phy_per_rank_cs_map
	slice_num = 0;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,8,2,cs_map); //?????
	slice_num = 1;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,8,2,cs_map); //?????
	slice_num = 2;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,8,2,cs_map); //?????
	slice_num = 3;
	slice_offset = slice_num*0x200;
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,8,2,cs_map); //?????

	//phy_cslvl_cs_map
	reg_bit_set(CANDS_PHY0_(1027)+chn_offset,8,4,cs_map);
	//phy_calvl_cs_map
	#ifdef DRAM_LPDDR3
	//dq slice select bit0~1 for cs0 bit2~3 for cs1
	reg_bit_set(CANDS_PHY0_(1033)+chn_offset,0,8,0x50);
	#else
	reg_bit_set(CANDS_PHY0_(1033)+chn_offset,0,8,0x5500);
	#endif

}
#endif
void rf_active_hw_wait_cnt_2_cfg(DDR_CHANNEL_NUM_E chn_num,uint32 clk)
{
	uint32 chn_offset = (0 == chn_num)?0:0x00800000;
	uint32 ddr_clk = clk;

	reg_bit_set(PUB0_APB_PUB_CHN0_LP_CTRL+chn_offset, 2, 10, ddr_clk);
	reg_bit_set(PUB0_APB_PUB_CHN1_LP_CTRL+chn_offset, 2, 10, (ddr_clk/2));
	reg_bit_set(PUB0_APB_PUB_CHN2_LP_CTRL+chn_offset, 2, 10, (ddr_clk/4));
	reg_bit_set(PUB0_APB_PUB_CHN3_LP_CTRL+chn_offset, 2, 10, ddr_clk);
}

void ddr_lowpower_init(DDR_CHANNEL_NUM_E chn_num,uint32 clk)
{
       volatile uint32 i = 0;
       uint32 chn_offset = (chn_num==0)?0:0x00800000;

       //enable pubx axi channels clock auto gate
       if(chn_num == 0){
               //REG32(PMU_APB_DDR0_CHN_SLEEP_CTRL0) = 0x7ff;
		#ifdef DRAM_LPDDR3
		//light_sleep_ddr0_data_ret_en
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,21,1,1);
		//pub0_mem_reset_ret
		reg_bit_set(0xE42c0098,0,1,0);
		//PWR_SEREFRESH_EXIT
		reg_bit_set(CANDS_CTL0_(102)+chn_offset, 16, 1, 0);
		//PWR_SEREFRESH_EXIT_CS
		reg_bit_set(CANDS_CTL0_(170)+chn_offset, 0, 2, 3);
		#else
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,21,1,1);
		//pub0_mem_reset_ret
		reg_bit_set(0xE42c0098,0,1,1);
		//PWR_SEREFRESH_EXIT
		reg_bit_set(CANDS_CTL0_(102)+chn_offset, 16, 1, 1);
		//PWR_SEREFRESH_EXIT_CS
		reg_bit_set(CANDS_CTL0_(170)+chn_offset, 0, 2, 0);
		#endif
            //   if((200000000!=clk)&&(400000000!=clk))
             //  {
             //       reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,15,1,0);
             //  }
             //enable auto light sleep
             reg_bit_set(AON_TOP_PUB0_SYS_SLEEP_CTRL,4,1,1);
             #ifndef PHY_PLL_BYPASS
             //disable 2xen
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,16,1,0);
		#endif
       }
       else{
               //REG32(PMU_APB_DDR1_CHN_SLEEP_CTRL0) = 0x7ff;
		#ifdef DRAM_LPDDR3
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,22,1,1);
		//pub1_mem_reset_ret
		reg_bit_set(0xE42c0098,1,1,0);
		//PWR_SEREFRESH_EXIT
		reg_bit_set(CANDS_CTL0_(102)+chn_offset, 16, 1, 0);
		//PWR_SEREFRESH_EXIT_CS
		reg_bit_set(CANDS_CTL0_(170)+chn_offset, 0, 2, 3);
		#else
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,22,1,1);
		//pub1_mem_reset_ret
		reg_bit_set(0xE42c0098,1,1,1);
		//PWR_SEREFRESH_EXIT
		reg_bit_set(CANDS_CTL0_(102)+chn_offset, 16, 1, 1);
		//PWR_SEREFRESH_EXIT_CS
		reg_bit_set(CANDS_CTL0_(170)+chn_offset, 0, 2, 0);
		#endif
            //   if((200000000!=clk)&&(400000000!=clk))
             //  {
             //       reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,17,1,0);
             //  }
             //enable auto light sleep
             reg_bit_set(AON_TOP_PUB1_SYS_SLEEP_CTRL,4,1,1);
             #ifndef PHY_PLL_BYPASS
             //disable 2xen
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,18,1,0);
		#endif
       }

	//phy_set_dfi_input_0
	reg_bit_set(CANDS_PHY0_(1050)+chn_offset,10,1,1);
	 //pcpcs_pd_en
	reg_bit_set(CANDS_CTL0_(162)+chn_offset, 8, 1, 0);
	 //lp_auto_entry_en
	reg_bit_set(CANDS_CTL0_(153)+chn_offset, 24, 4, 0x4);
	 //lp_auto_exit_en
	reg_bit_set(CANDS_CTL0_(154)+chn_offset, 0, 4, 0x4);
	 //lp_auto_mem_gate_en
	reg_bit_set(CANDS_CTL0_(154)+chn_offset, 8, 2, 0x3);

#ifdef DRAM_LPDDR4	//for lp3 lpi_sr_wakeup is defined in ddr_timing_lp3.c
	 //lpi_sr_wakeup_f0	hw lp interface enter this status
	 reg_bit_set(CANDS_CTL0_(141)+chn_offset, 24, 8, 8);
	 //lpi_sr_wakeup_f1
	 reg_bit_set(CANDS_CTL0_(143)+chn_offset, 24, 8, 8);
	 //lpi_sr_wakeup_f2
	 reg_bit_set(CANDS_CTL0_(145)+chn_offset, 24, 8, 8);
	 //lpi_sr_wakeup_f3
	 reg_bit_set(CANDS_CTL0_(147)+chn_offset, 24, 8, 8);
	 //lpi_sr_wakeup_f4
	 reg_bit_set(CANDS_CTL0_(149)+chn_offset, 24, 8, 8);
#endif
	   //pub0_chnx_lp_ctrl
       for(i = 0; i < 6; i++ )
               REG32(PUB0_APB_PUB_CHN0_LP_CTRL + i*4 + chn_offset) = 0x31;
}

void cands_phy_rx_cal_modify(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 i,j;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//phy_rx_cal_dqs SET dqs to singal end mode for rx cal
	reg_bit_set(CANDS_PHY0_(65)+chn_offset, 24, 1, 1);
	reg_bit_set(CANDS_PHY0_(193)+chn_offset, 24, 1, 1);
	reg_bit_set(CANDS_PHY0_(321)+chn_offset, 24, 1, 1);
	reg_bit_set(CANDS_PHY0_(449)+chn_offset, 24, 1, 1);
	for(i=0;i<4;i++)
	{
		for(j=0;j<11;j++)
		{
			reg_bit_set(CANDS_PHY0_(56+j)+chn_offset+(0x200*i),0,24,0x940);
		}
	}
	//reset to diff mode for normal operation
	reg_bit_set(CANDS_PHY0_(65)+chn_offset, 24, 1, 0);
	reg_bit_set(CANDS_PHY0_(193)+chn_offset, 24, 1, 0);
	reg_bit_set(CANDS_PHY0_(321)+chn_offset, 24, 1, 0);
	reg_bit_set(CANDS_PHY0_(449)+chn_offset, 24, 1, 0);
}

void manual_clear_master_dly_lock(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//phy_manual_clear master dly lock value
	reg_bit_set(CANDS_PHY0_(35)+chn_offset, 26, 1, 1);
	reg_bit_set(CANDS_PHY0_(163)+chn_offset, 26, 1, 1);
	reg_bit_set(CANDS_PHY0_(291)+chn_offset, 26, 1, 1);
	reg_bit_set(CANDS_PHY0_(419)+chn_offset, 26, 1, 1);
	//phy_adr_manual_clear master dly lock value
	reg_bit_set(CANDS_PHY0_(514)+chn_offset,  8, 1, 1);
	reg_bit_set(CANDS_PHY0_(642)+chn_offset,  8, 1, 1);
	reg_bit_set(CANDS_PHY0_(770)+chn_offset,  8, 1, 1);
	reg_bit_set(CANDS_PHY0_(898)+chn_offset,  8, 1, 1);
}

void manual_clear_gate_init(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//phy_manual_clear master dly lock value
	reg_bit_set(CANDS_PHY0_(35)+chn_offset, 24, 1, 1);
	reg_bit_set(CANDS_PHY0_(163)+chn_offset, 24, 1, 1);
	reg_bit_set(CANDS_PHY0_(291)+chn_offset, 24, 1, 1);
	reg_bit_set(CANDS_PHY0_(419)+chn_offset, 24, 1, 1);
}
void cands_do_sw_training(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//calvl_gate_training
	//reg_bit_set(CANDS_PI0_(113)+chn_offset, 0, 1, 1);
	//while((REG32(CANDS_PHY0_(532)) & (0xf000)) != 0x3000);
	//while((REG32(CANDS_PHY0_(660)) & (0xf000)) != 0x3000);
	//rdlvl_gate_training
	reg_bit_set(CANDS_PI0_(94)+chn_offset, 8, 1, 1);

	while((REG32(CANDS_PHY0_(46)) & (0xf00000)) != 0x300000);
	while((REG32(CANDS_PHY0_(174)) & (0xf00000)) != 0x300000);
	while((REG32(CANDS_PHY0_(302)) & (0xf00000)) != 0x300000);
	while((REG32(CANDS_PHY0_(430)) & (0xf00000)) != 0x300000);

	//rdlvl_training
	reg_bit_set(CANDS_PI0_(94)+chn_offset, 0, 1, 1);

	wait_us(1000);
}
void phy_on_fly_gate_adjust_en(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(16)+chn_offset+(0x200*i) , 16, 2, 0x3);
    }
}

#ifdef DDR_IP_CONFIG_FILE
extern void cands_ctl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,
					CANDS_CTL_TIMING_T * ctl_timing, CANDS_CTL_PERCHN_QOS_T* perchn_qos,CANDS_CTL_ALLCHN_QOS_T* allchn_qos,
					uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4);
extern void cands_pi_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_PI_TIMING_T	*pi_timing,
				   uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4);
extern void cands_phy_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_PHY_TIMING_T* phy_timing_info,
					uint32 f0, uint32 f1, uint32 f2, uint32 f3);
#endif

#define REG_SIZE (32)
uint gUpCodeStart = 0x20; //0x3F;
uint gDownCodeStart = 0x20; //1;
uint32 chn_offset_do_rx = 0x0;

// Utility function to extract bits from value passed.
// This function will extract bit from pos "msb" to pos "lsb"
uint GetBitsFromValue(uint value, int msb, int lsb)
{

    uint result;
    result = (uint)(value << (REG_SIZE - 1 - msb));
    result >>= (REG_SIZE - 1 - msb);
    result = (uint)(result >> lsb);

    return result;

}

// Replaces MSB to LSb of the orig value with the value "value" passed as argment.
// If value has more bits than the msb to lsb then higher order bits will be truncated.
uint WriteBitsToValue(uint value, uint orig, int msb, int lsb)
{
    // clear the bits msb to lsb from the orgnal value
    uint val = 0xFFFFFFFF;
    val = (val >>lsb) << lsb;
    val = (val << (REG_SIZE-1-msb)) >> (REG_SIZE-1-msb);
    val = ~val; // all bits are one except for msb to lasb
    orig &= val;
    // get only the correct bits from the value to be assigned
    // if there are more bits then exclude them
    int NoOfBits = (msb -lsb);

    value = (value << (REG_SIZE -1 - NoOfBits)) >> (REG_SIZE -1 - NoOfBits);
    value = (value << lsb);
    return (orig | value);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DLL Memory controller register read
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
uint jtag_dll_mc_reg_read(uint address,uint phy)
{
	return __raw_readl(CANDS_PHY0_(address)+chn_offset_do_rx );
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DLL Memory controller register write
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void jtag_dll_mc_reg_write(uint address, uint data, uint phy)
{
	__raw_writel(CANDS_PHY0_(address)+chn_offset_do_rx , data);
}

void SleepIn_10_MiliSecounds(uint val)
{
	//wait_us(val * 10 * 1000);
	//wait_us(val * 10);
	//wait_us(val);
}

//#define print_message __ddr_print
#define print_message(...)

uint GetDQValue(uint bitNo)
{
//DENALI_PHY_67_DATA 32'b00000000_00000000_00000000_00000000 // PHY_RX_CAL_OBS_0:RD:0:11:=0x0000
// param_phy_rx_cal_obs   <= `PD {rx_cal_rd_fdbk,rx_cal_rd_dqs,rx_cal_rd_dm,wrlvl_rd_dq[7:0]};

	if ((bitNo & 0x30) == 0x0)
	{
		int bit = (int)(bitNo & 0xF);
		return (uint)GetBitsFromValue(jtag_dll_mc_reg_read(67, TRUE), bit, bit);
	}
	else if ((bitNo & 0x30) == 0x10)
	{
		int bit = (int)(bitNo & 0xF);
		return (uint)GetBitsFromValue(jtag_dll_mc_reg_read(195, TRUE), bit, bit);
	}
	else if ((bitNo & 0x30) == 0x20)
	{
		int bit = (int)(bitNo & 0xF);
		return (uint)GetBitsFromValue(jtag_dll_mc_reg_read(323, TRUE), bit, bit);
	}
	else
	{
		int bit = (int)(bitNo & 0xF);
		return (uint)GetBitsFromValue(jtag_dll_mc_reg_read(451, TRUE), bit, bit);
	}
}

uint rx_cal_high(uint bit, uint rxCalRegAddr) {
        // If result is high, decrease RX_CAL_CODE_UP_LV and increase RX_CAL_CODE_DOWN_LV until result changes from high to low
        uint RX_CAL_CODE_UP_LV = gUpCodeStart;
        uint RX_CAL_CODE_DOWN_LV = gDownCodeStart;
        uint dqval = GetDQValue(bit);
        ulong regValue = jtag_dll_mc_reg_read(rxCalRegAddr, TRUE);
        while (dqval == 1)
        {
                RX_CAL_CODE_UP_LV++;
                RX_CAL_CODE_DOWN_LV--;

                //param_phy_rx_cal_dq0[5:0]    <= `PD rx_cal_down_code;
                //param_phy_rx_cal_dq0[11:6]   <= `PD rx_cal_up_code;
                regValue = jtag_dll_mc_reg_read(rxCalRegAddr, TRUE);

                regValue = WriteBitsToValue(RX_CAL_CODE_DOWN_LV, regValue, 5, 0);
                regValue = WriteBitsToValue(RX_CAL_CODE_UP_LV, regValue, 11, 6);

                jtag_dll_mc_reg_write(rxCalRegAddr, regValue, TRUE);

                SleepIn_10_MiliSecounds(100);
                dqval = GetDQValue(bit);
                //Console.Write("DQ0 = " + val.ToString("x") + "\n");

                if ((RX_CAL_CODE_DOWN_LV == 0x0) || (RX_CAL_CODE_UP_LV == 0x3f))
		{
			jtag_dll_mc_reg_write(rxCalRegAddr, 0x0, TRUE);
			break;
		}
        } ;

        //WriteBitsToValue(RX_CAL_CODE_UP_LV, regValue, 5, 0);
        //WriteBitsToValue(RX_CAL_CODE_DOWN_LV, regValue, 11, 6);
        return dqval;
}

uint rx_cal_low(uint bit, uint rxCalRegAddr) {
        // . If result is low, increase RX_CAL_CODE_UP_LV and decrease RX_CAL_CODE_DOWN_LV until result changes from low to high
        uint RX_CAL_CODE_UP_LV = gUpCodeStart;
        uint RX_CAL_CODE_DOWN_LV = gDownCodeStart;
        uint dqval = GetDQValue(bit);
        ulong regValue = jtag_dll_mc_reg_read(rxCalRegAddr, TRUE);
        while (dqval == 0)
        {
                                RX_CAL_CODE_UP_LV--;
                                RX_CAL_CODE_DOWN_LV++;
                //param_phy_rx_cal_dq0[5:0]    <= `PD rx_cal_down_code;
                //param_phy_rx_cal_dq0[11:6]   <= `PD rx_cal_up_code;
                regValue = jtag_dll_mc_reg_read(rxCalRegAddr, TRUE);
                regValue = WriteBitsToValue(RX_CAL_CODE_DOWN_LV, regValue, 5, 0);
                regValue = WriteBitsToValue(RX_CAL_CODE_UP_LV, regValue, 11, 6);
                jtag_dll_mc_reg_write(rxCalRegAddr, regValue, TRUE);

                SleepIn_10_MiliSecounds(100);

                dqval = GetDQValue(bit);
                //Console.Write("DQ = " + val.ToString("x") + "\n");

		if ((RX_CAL_CODE_UP_LV == 0) || (RX_CAL_CODE_DOWN_LV == 0x3f))
		{
			jtag_dll_mc_reg_write(rxCalRegAddr, 0x0, TRUE);
                        break;
		}
        } ;

        return dqval;
}

uint trigger_rx_calibration(uint bit)
{
	uint rxCalCode = 0;
	uint rxCalRegAddr = 0;
	uint rxCalOverrideRegAddr = 0;
	uint IEModeRegAddr = 0;
	// Enable IE -- set to always on
// DENALI_PHY_94_DATA 32'b00001011_00000000_00000000_11000000 // PHY_RDDATA_EN_DLY_0:RW+:24:4:=0x0b PHY_IE_MODE_0:RW+:16:2:=0x00 PHY_RDDATA_EN_IE_DLY_0:RW+:8:2:=0x00 PHY_DQS_IE_TIMING_0:RW+:0:8:=0xc0 // DENALI_PHY_55_DATA 32'b00000000_00100000_00000000_00000000 // PHY_RX_CAL_SAMPLE_WAIT_0:RW:16:8:=0x20 PHY_RX_CAL_OVERRIDE_0:RW:8:1:=0x00 SC_PHY_RX_CAL_START_0:WR:0:1:=0x00
// DENALI_PHY_56_DATA 32'b00000000_00000000_00000000_00000000 // PHY_RX_CAL_DQ0_0:RW+:0:24:=0x000000

	if ((bit & 0x30) == 0x0)
	{
		 rxCalRegAddr = (uint)56 + (bit & 0xF);
		 rxCalOverrideRegAddr = 55;
		 IEModeRegAddr = 94;
	}
	else if((bit & 0x30) == 0x10)
	{
		 rxCalRegAddr = (uint)((56+(128*1)) + (bit & 0xF));
		 rxCalOverrideRegAddr = (55+(128*1));
		 IEModeRegAddr = (94+(128*1));
	}
	else if ((bit & 0x30) == 0x20)
	{
		 rxCalRegAddr = (uint)((56+(128*2)) + (bit & 0xF));
		 rxCalOverrideRegAddr = (55+(128*2));
		 IEModeRegAddr = (94+(128*2));
	}
	else if((bit & 0x30) == 0x30)
	{
		 rxCalRegAddr = (uint)((56+(128*3)) + (bit & 0xF));
		 rxCalOverrideRegAddr = (55+(128*3));
		 IEModeRegAddr = (94+(128*3));
	}

	ulong rxCalInitValue = (gUpCodeStart << 6)| gDownCodeStart;
	jtag_dll_mc_reg_write(rxCalRegAddr, rxCalInitValue, TRUE);
	jtag_dll_mc_reg_write(IEModeRegAddr, WriteBitsToValue(0x1, jtag_dll_mc_reg_read(IEModeRegAddr, TRUE), (17), (16)), TRUE);
	jtag_dll_mc_reg_write(rxCalOverrideRegAddr, WriteBitsToValue(0x1, jtag_dll_mc_reg_read(rxCalOverrideRegAddr, TRUE), (8), (8)), TRUE);
	SleepIn_10_MiliSecounds(100);

	uint dqZ = GetDQValue(bit);
	if (dqZ == 1)
	{
		dqZ = rx_cal_high(bit, rxCalRegAddr);
		if (dqZ == 1)
		{
			print_message("Error in Rx Cal \n");
		}
		else
		{
			print_message("Rx Cal Success\n");
		}
	}
	else
	{
		dqZ = rx_cal_low(bit, rxCalRegAddr);
		if (dqZ == 0)
		{
			print_message("Error in Rx Cal \n");
		}
		else
		{
			print_message("Rx Cal Success\n");
		}
	}

	jtag_dll_mc_reg_write(rxCalOverrideRegAddr, WriteBitsToValue(0x0, jtag_dll_mc_reg_read(rxCalOverrideRegAddr, TRUE), (8), (8)), TRUE);

	jtag_dll_mc_reg_write(IEModeRegAddr, WriteBitsToValue(0, jtag_dll_mc_reg_read(IEModeRegAddr, TRUE), (17), (16)), TRUE);

	return rxCalCode;
}

uint rx_cal2_high(uint bit, uint rxCalRegAddr) {
	// If result is high, Decrement RX_CAL_CODE2_UP_LV Increment RX_CAL_CODE2_DOWN_LV
	uint RX_CAL_CODE2_UP_LV = 0x20;
	uint RX_CAL_CODE2_DOWN_LV = 0x20;
	uint dqval = GetDQValue(bit);
	ulong regValue = jtag_dll_mc_reg_read(rxCalRegAddr, TRUE);
	while (dqval == 1)
	{
		RX_CAL_CODE2_UP_LV++;
		RX_CAL_CODE2_DOWN_LV--;

		//param_phy_rx_cal_dq0[17:12]  <= `PD rx_cal2_down_code;
		//param_phy_rx_cal_dq0[23:18]  <= `PD rx_cal2_up_code;
		regValue = jtag_dll_mc_reg_read(rxCalRegAddr, TRUE);
		regValue = WriteBitsToValue(RX_CAL_CODE2_DOWN_LV, regValue, 17, 12);
		regValue = WriteBitsToValue(RX_CAL_CODE2_UP_LV, regValue, 23, 18);
		jtag_dll_mc_reg_write(rxCalRegAddr, regValue, TRUE);

		SleepIn_10_MiliSecounds(100);
		dqval = GetDQValue(bit);
		//Console.Write("DQ0 = " + val.ToString("x") + "\n");

		if ((RX_CAL_CODE2_DOWN_LV == 0) || (RX_CAL_CODE2_UP_LV == 0x3f))
			break;
	};

	return dqval;
}

uint rx_cal2_low(uint bit, uint rxCalRegAddr) {
	// Increment RX_CAL_CODE2_UP_LV Decrement RX_CAL_CODE2_DOWN_LV
	uint RX_CAL2_CODE_UP_LV = 0x20;
	uint RX_CAL2_CODE_DOWN_LV = 0x20;
	uint dqval = GetDQValue(bit);
	ulong regValue = jtag_dll_mc_reg_read(rxCalRegAddr, TRUE);
	while (dqval == 0)
	{
		RX_CAL2_CODE_UP_LV++;
		RX_CAL2_CODE_DOWN_LV--;

		//param_phy_rx_cal_dq0[17:12]  <= `PD rx_cal2_down_code;
		//param_phy_rx_cal_dq0[23:18]  <= `PD rx_cal2_up_code;
		regValue = jtag_dll_mc_reg_read(rxCalRegAddr, TRUE);
		regValue = WriteBitsToValue(RX_CAL2_CODE_DOWN_LV, regValue, 17, 12);
		regValue = WriteBitsToValue(RX_CAL2_CODE_UP_LV, regValue, 23, 18);
		jtag_dll_mc_reg_write(rxCalRegAddr, regValue, TRUE);

		SleepIn_10_MiliSecounds(100);

		dqval = GetDQValue(bit);
		//Console.Write("DQ = " + val.ToString("x") + "\n");

		if ((RX_CAL2_CODE_UP_LV == 0x3f) || (RX_CAL2_CODE_DOWN_LV == 0))
			break;
	};

	return dqval;
}
void Do_RX_CAL_DQX_c()
{
	uint slice;
	uint bit;
	for (slice = 0; slice< 4; slice++)
	{
		for(bit =0; bit<11; bit++)
		{
			trigger_rx_calibration(bit | (slice << 4) );
		}
	}
}
void light_sleep_ddr_workaround(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    REG32(PUB0_TOP_PUB0_DUMMY_REG0+chn_offset) = 0x01800000;
}
#ifdef DDR_IP_CONFIG_FILE
void pcpcs_pd_disable(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_CTL0_(162)+chn_offset , 8, 1, 0x0);
}
void boot_freq_init_freq(DDR_CHANNEL_NUM_E chn_num, uint32 boot_freq, uint32 init_freq)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
	//dfibus_boot_freq
	reg_bit_set(CANDS_CTL0_(32)+chn_offset,24,3,boot_freq);
	//dfibus_freq_init
	reg_bit_set(CANDS_CTL0_(32)+chn_offset,16,3,init_freq);
}
void phy_cal_clk_select(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_PHY0_(1095)+chn_offset , 8, 3, 0x5);
}
void phy_cal_mode(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_PHY0_(1093)+chn_offset , 0, 8, 0x24);
}
void mr11_mr22_odt_cfg(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_CTL0_(211)+chn_offset ,  0, 8, 0x6);      //mr11_F3
    reg_bit_set(CANDS_CTL0_(222)+chn_offset , 16, 8, 0x6);      //mr11_F3
    reg_bit_set(CANDS_PI0_(163)+chn_offset  ,  0, 8, 0x6);      //mr11_F3
    reg_bit_set(CANDS_PI0_(170)+chn_offset  , 24, 8, 0x6);      //mr11_F3
    reg_bit_set(CANDS_PI0_(178)+chn_offset  , 16, 8, 0x6);      //mr11_F3
    reg_bit_set(CANDS_PI0_(186)+chn_offset  ,  8, 8, 0x6);      //mr11_F3
    reg_bit_set(CANDS_CTL0_(217)+chn_offset ,  0, 8, 0x4);      //mr22_F3
    reg_bit_set(CANDS_CTL0_(228)+chn_offset , 16, 8, 0x4);      //mr22_F3
}

void lp4_phy_vref_cfg(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    unsigned short int lp4_phy_dq_vref_slice0[]={0xd2f,0xd2f,0xd2f,0xf1f};
    unsigned short int lp4_phy_dq_vref_slice1[]={0xd2f,0xd2f,0xd2f,0xf1f};
    unsigned short int lp4_phy_dq_vref_slice2[]={0xd2f,0xd2f,0xd2f,0xf1f};
    unsigned short int lp4_phy_dq_vref_slice3[]={0xd2f,0xd2f,0xd2f,0xf1f};
    unsigned short int lp4_phy_ca_vref[]={0xd2e,0xd2e,0xd2e,0xd2e};
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(1024)+chn_offset ,  8,  3, i);
        reg_bit_set(CANDS_PHY0_(1047)+chn_offset ,  8, 14, lp4_phy_dq_vref_slice0[i]);
        reg_bit_set(CANDS_PHY0_(1048)+chn_offset ,  0, 14, lp4_phy_dq_vref_slice1[i]);
        reg_bit_set(CANDS_PHY0_(1048)+chn_offset , 16, 14, lp4_phy_dq_vref_slice2[i]);
        reg_bit_set(CANDS_PHY0_(1049)+chn_offset ,  0, 14, lp4_phy_dq_vref_slice3[i]);
        reg_bit_set(CANDS_PHY0_(1049)+chn_offset , 16, 14, lp4_phy_ca_vref[i]);
    }
}

void ca_vref_training_setting(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_PI0_(137)+chn_offset  , 16, 7, 0x40);     //pi_calvl_vref_initial_start_point
    reg_bit_set(CANDS_PI0_(137)+chn_offset  , 24, 7, 0x72);     //pi_calvl_vref_initial_stop_point
    reg_bit_set(CANDS_PI0_(138)+chn_offset  ,  0, 4, 0x04);     //pi_calvl_vref_initial_stepsize
    reg_bit_set(CANDS_PI0_(138)+chn_offset  ,  8, 4, 0x02);     //pi_calvl_vref_normal_stepsize
    reg_bit_set(CANDS_PI0_(138)+chn_offset  , 16, 4, 0x01);     //pi_calvl_vref_delta
}

void dq_odt_vref_training_setting(uint32 chn_offset)
{
    reg_bit_set(CANDS_PI0_(147)+chn_offset  , 24, 1, 0x01);     //pi_wdqlvl_vref_en
    reg_bit_set(CANDS_PI0_(150)+chn_offset  ,  8, 7, 0x00);     //pi_wdqlvl_vref_initial_start_point
    reg_bit_set(CANDS_PI0_(150)+chn_offset  , 16, 7, 0x32);     //pi_wdqlvl_vref_initial_stop_point
    reg_bit_set(CANDS_PI0_(150)+chn_offset  , 24, 4, 0x04);     //pi_wdqlvl_vref_initial_stepsize
    reg_bit_set(CANDS_PI0_(151)+chn_offset  ,  0, 4, 0x02);     //pi_wdqlvl_vref_normal_stepsize
    reg_bit_set(CANDS_PI0_(151)+chn_offset  ,  8, 4, 0x01);     //pi_wdqlvl_vref_delta
}
void dq_vref_training_setting(uint32 chn_offset)
{
    reg_bit_set(CANDS_PI0_(147)+chn_offset  , 24, 1, 0x01);     //pi_wdqlvl_vref_en
    reg_bit_set(CANDS_PI0_(150)+chn_offset  ,  8, 7, 0x40);     //pi_wdqlvl_vref_initial_start_point
    reg_bit_set(CANDS_PI0_(150)+chn_offset  , 16, 7, 0x72);     //pi_wdqlvl_vref_initial_stop_point
    reg_bit_set(CANDS_PI0_(150)+chn_offset  , 24, 4, 0x04);     //pi_wdqlvl_vref_initial_stepsize
    reg_bit_set(CANDS_PI0_(151)+chn_offset  ,  0, 4, 0x02);     //pi_wdqlvl_vref_normal_stepsize
    reg_bit_set(CANDS_PI0_(151)+chn_offset  ,  8, 4, 0x01);     //pi_wdqlvl_vref_delta
}

void ctrl_mr_modify(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
//    reg_bit_set(CANDS_PI0_(161)+chn_offset  , 16, 8, 0x66);     //MR11_F3
    reg_bit_set(CANDS_CTL0_(211)+chn_offset  ,  0, 8, 0x04);     //MR11_F3_0
    reg_bit_set(CANDS_CTL0_(222)+chn_offset  , 16, 8, 0x04);     //MR11_F3_1
    reg_bit_set(CANDS_CTL0_(217)+chn_offset  ,  0, 8, 0x04);     //MR22_F3_0
    reg_bit_set(CANDS_CTL0_(228)+chn_offset  , 16, 8, 0x04);     //MR22_F3_1
}

void pi_mr_modify(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
//    reg_bit_set(CANDS_PI0_(161)+chn_offset  , 16, 8, 0x66);     //MR11_F3
    reg_bit_set(CANDS_PI0_(163)+chn_offset  ,  0, 8, 0x04);     //MR11_F4_0
    reg_bit_set(CANDS_PI0_(170)+chn_offset  , 24, 8, 0x04);     //MR11_F4_1
    reg_bit_set(CANDS_PI0_(178)+chn_offset  , 16, 8, 0x04);     //MR11_F4_2
    reg_bit_set(CANDS_PI0_(186)+chn_offset  ,  8, 8, 0x04);     //MR11_F4
}


void pi_init_work_freq(DDR_CHANNEL_NUM_E chn_num,uint32 freq_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;

    reg_bit_set(CANDS_PI0_(38)+chn_offset , 0, 5, freq_num);
}

void fsp_frc_update(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_CTL0_(231)+chn_offset , 16, 3, 3);  //fsp0_frc
    reg_bit_set(CANDS_CTL0_(231)+chn_offset , 24, 3, 2);  //fsp1_frc
    reg_bit_set(CANDS_CTL0_(229)+chn_offset , 24, 1, 0);  //fsp_phy_updtae_mrw
}
void fsp_lp4(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;

    reg_bit_set(CANDS_CTL0_(230)+chn_offset , 0 , 1, 1);  //dfs_always_write_fsp
    reg_bit_set(CANDS_CTL0_(230)+chn_offset , 16, 1, ((fn_ctl_target==3)?0:1));  //fsp_op_current
    reg_bit_set(CANDS_CTL0_(230)+chn_offset , 24, 1, ((fn_ctl_target==3)?0:1));  //fsp_wr_current
    reg_bit_set(CANDS_CTL0_(212)+chn_offset , 30, 2, ((fn_ctl_target==3)?0:3));  //mr13_data_0
    reg_bit_set(CANDS_CTL0_(224)+chn_offset , 14, 2, ((fn_ctl_target==3)?0:3));  //mr13_data_1
    reg_bit_set(CANDS_CTL0_(214)+chn_offset ,  8, 1, 1);  //mr_fsp_data_vaild_f0_0
    reg_bit_set(CANDS_CTL0_(214)+chn_offset , 16, 1, 1);  //mr_fsp_data_vaild_f1_0
    reg_bit_set(CANDS_CTL0_(214)+chn_offset , 24, 1, 1);  //mr_fsp_data_vaild_f2_0
    reg_bit_set(CANDS_CTL0_(215)+chn_offset ,  0, 1, 1);  //mr_fsp_data_vaild_f3_0
    reg_bit_set(CANDS_CTL0_(215)+chn_offset ,  8, 1, 1);  //mr_fsp_data_vaild_f4_0
    reg_bit_set(CANDS_CTL0_(225)+chn_offset , 24, 1, 1);  //mr_fsp_data_vaild_f0_1
    reg_bit_set(CANDS_CTL0_(226)+chn_offset ,  0, 1, 1);  //mr_fsp_data_vaild_f1_1
    reg_bit_set(CANDS_CTL0_(226)+chn_offset ,  8, 1, 1);  //mr_fsp_data_vaild_f2_1
    reg_bit_set(CANDS_CTL0_(226)+chn_offset , 16, 1, 1);  //mr_fsp_data_vaild_f3_1
    reg_bit_set(CANDS_CTL0_(226)+chn_offset , 24, 1, 1);  //mr_fsp_data_vaild_f4_1
}
void pi_init_work_freq_lp4(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_CTL0_(33)+chn_offset, 0 , 5, 0x1);        //dfibus_freq_f0
    reg_bit_set(CANDS_CTL0_(33)+chn_offset, 8 , 5, 0x2);        //dfibus_freq_f1
    reg_bit_set(CANDS_CTL0_(33)+chn_offset, 16, 5, 0x3);        //dfibus_freq_f2
    reg_bit_set(CANDS_CTL0_(33)+chn_offset, 24, 5, 0x4);        //dfibus_freq_f3
    reg_bit_set(CANDS_CTL0_(34)+chn_offset, 0 , 5, 0x0);        //dfibus_freq_f4

    reg_bit_set(CANDS_PI0_(37)+chn_offset , 0, 5, PI_FREQ_MAP );    //pi_freq_map
    reg_bit_set(CANDS_PI0_(38)+chn_offset , 0, 5, (fn_ctl_target+1));    //pi-init_work_freq
//    reg_bit_set(CANDS_PI0_(38)+chn_offset , 0, 5, (3));    //pi-init_work_freq
}
void phy_lvl_updt_wait_cnt(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
//    reg_bit_set(CANDS_PHY0_(153)+chn_offset , 0, 8, 0x24);

    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(26)+(i*0x200)+chn_offset , 24, 4, 0xA);
        reg_bit_set(CANDS_PHY0_(26)+(i*0x200)+chn_offset ,  8, 4, 0xA);
        reg_bit_set(CANDS_PHY0_(27)+(i*0x200)+chn_offset ,  0, 2, 0x2);
    }
}
void phy_cal_sample_wait(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_PHY0_(1095)+chn_offset , 0, 8, 0xf0);
}

void addr_map(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_CTL0_(280)+chn_offset, 0 , 4, 0x2);       //col_diff
    reg_bit_set(CANDS_CTL0_(279)+chn_offset, 16, 2, 0x0);       //bank_diff
    reg_bit_set(CANDS_CTL0_(279)+chn_offset, 24, 3, 0x1);       //row_diff
}
void rd_lvl_rd_gate_training(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_PI0_(94)+chn_offset , 8, 1, 0x1);
    reg_bit_set(CANDS_PI0_(94)+chn_offset , 8, 1, 0x0);
    reg_bit_set(CANDS_PI0_(94)+chn_offset , 0, 1, 0x1);
}

void pi_init_training_disable(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_CTL0_(32)+chn_offset , 8, 1, 0x1);
    reg_bit_set(CANDS_CTL0_(32)+chn_offset , 0, 1, 0x0);
    reg_bit_set(CANDS_PI0_(1)+chn_offset , 0, 1, 0x1);
    reg_bit_set(CANDS_PI0_(1)+chn_offset , 8, 1, 0x1);
    reg_bit_set(CANDS_PI0_(77)+chn_offset , 8, 2, 0x2);
    reg_bit_set(CANDS_PI0_(123)+chn_offset , 8, 2, 0x2);
    reg_bit_set(CANDS_PI0_(129)+chn_offset , 24, 1, 0x0);
    reg_bit_set(CANDS_PI0_(99)+chn_offset , 16, 2, 0x2);
    reg_bit_set(CANDS_PI0_(99)+chn_offset , 24, 2, 0x2);
    reg_bit_set(CANDS_PI0_(147)+chn_offset , 24, 1, 0x0);
    reg_bit_set(CANDS_PI0_(155)+chn_offset , 16, 2, 0x0);
}

void pi_init_training_enable(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_CTL0_(32)+chn_offset , 8, 1, 0x1);
    reg_bit_set(CANDS_CTL0_(32)+chn_offset , 0, 1, 0x0);
    reg_bit_set(CANDS_PI0_(1)+chn_offset , 0, 1, 0x1);  //pi_normal_lvl_seq
    reg_bit_set(CANDS_PI0_(1)+chn_offset , 8, 1, 0x1);  //pi_init_lvl_en
    reg_bit_set(CANDS_PI0_(77)+chn_offset , 8, 2, 0x1); //pi_wrlvl_en
    reg_bit_set(CANDS_PI0_(123)+chn_offset , 8, 2, 0x1);//pi_calvl_en
    reg_bit_set(CANDS_PI0_(129)+chn_offset , 24, 1, 0x1);//pi_ca_train_vref_en
    reg_bit_set(CANDS_PI0_(99)+chn_offset , 16, 2, 0x1);//pi_rdlvl_en
    reg_bit_set(CANDS_PI0_(99)+chn_offset , 24, 2, 0x1);        //pi_rdlvl_gate_en
    reg_bit_set(CANDS_PI0_(147)+chn_offset , 24, 1, 0x1);       //pi_wdqlvl_vref_en
    reg_bit_set(CANDS_PI0_(155)+chn_offset , 16, 2, 0x1);       //pi_wdqlvl_en
    reg_bit_set(CANDS_PI0_(1)+chn_offset , 0, 1, 0x1);       //pi_normal_lvl_seq
}

void training_cs_map(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_CTL0_(285)+chn_offset ,  0, 2, 0x3);
    reg_bit_set(CANDS_PI0_(55)+chn_offset   , 24, 4, 0xF);
    reg_bit_set(CANDS_PI0_(79)+chn_offset   ,  0, 4, 0xF);
    reg_bit_set(CANDS_PI0_(97)+chn_offset   ,  0, 4, 0xF);
    reg_bit_set(CANDS_PI0_(97)+chn_offset   ,  8, 4, 0xF);
    reg_bit_set(CANDS_PI0_(115)+chn_offset  ,  0, 4, 0xF);
    reg_bit_set(CANDS_PI0_(150)+chn_offset  ,  0, 4, 0xF);
}
void reg_26_1400_diff_with_4freq_modify(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    //TRST_PWRON
    __raw_writel(CANDS_CTL0_(35)+chn_offset, 0x119);
    //cke_inactive
    __raw_writel(CANDS_CTL0_(36)+chn_offset, 0x2bd);
    reg_bit_set(CANDS_CTL0_(63)+chn_offset,8,10,0x15f);
}
void phy_cs_training_en(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    uint32 slice_offset;
    for(i = 0; i < 4; i++)
    {
        slice_offset = 0x200*i;
	//phy_per_cs_training_en
	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset,16,1,1); //????
	//phy_per_rank_cs_map
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,8,2,0x3); //?????
	//phy_per_cs_training_multicast_en
	reg_bit_set(CANDS_PHY0_(8)+chn_offset+slice_offset,16,1,0); //????
    }
}

void phy_dq_tsel_rd_timing(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    uint32 slice_offset;
    reg_bit_set(CANDS_PHY0_(1024)+chn_offset,  8,3,0x3); //
    for(i = 0; i < 4; i++)
    {
        slice_offset = 0x200*i;
//	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset, 8,8,0x71);
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset, 0,8,0x51); //phy_dq_oe_timging
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset,24,8,0x50); //phy_dqs_oe_timging
	reg_bit_set(CANDS_PHY0_(92)+chn_offset+slice_offset,16,8,0x51); //phy_dq_tsel_wr_timing
//	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset, 0,8,0x71);
	reg_bit_set(CANDS_PHY0_(93)+chn_offset+slice_offset, 8,8,0x50); //phy_dqs_tsel_wr_timing
    }
}

void phy_low_freq_sel_dis(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_PHY0_(1047)+chn_offset , 0, 1, 0x0);
}

void w2r_samecs_dly(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_CTL0_(327)+chn_offset, 24, 5, 0xA);     //w2r_samecs_dly
}

void w2w_samecs_dly(uint32 chn_offset,uint32 delay)
{
    reg_bit_set(CANDS_CTL0_(328)+chn_offset,  0, 5, delay);     //w2w_samecs_dly
}

void w2w_diffcs_dly(uint32 chn_offset,uint32 delay)
{
    reg_bit_set(CANDS_CTL0_(325)+chn_offset,  0, 5, delay);     //w2w_diffcs_dly_F3
}

void phy_rptr_update(DDR_CHANNEL_NUM_E chn_num, uint32 cycle)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(96)+chn_offset+(i*0x200),  16, 4,cycle); //
    }
}

void phy_wrlvl_early_force_zero(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(89)+chn_offset+(i*0x200), 0, 1, 0x1);     //phy_wrlvl_early_force_zero
//        reg_bit_set(CANDS_PHY0_(87)+chn_offset+(i*0x200),  0, 10,0x119); //
        reg_bit_set(CANDS_PHY0_(88)+chn_offset+(i*0x200),  0, 10,0x180); //
//        reg_bit_set(CANDS_PHY0_(94)+chn_offset+(i*0x200),  24, 4,0xB); //
//        reg_bit_set(CANDS_PHY0_(95)+chn_offset+(i*0x200),  0,  4,0x9); //
    }
}

void phy_gtlvl_capture_cnt(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(26)+chn_offset+(i*0x200), 0, 6, 0x2);     //phy_gtlvl_capture_cnt
    }
}
void lp4_ds_phy_set(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_PHY0_(1082)+chn_offset , 0, 21, 0x4FFFF);     //phy_pad_cke_drive
    reg_bit_set(CANDS_PHY0_(1076)+chn_offset , 0, 22, 0x4FFFF);     //phy_pad_clk_drive
    reg_bit_set(CANDS_PHY0_(1086)+chn_offset , 0, 21, 0x4FFFF);     //phy_pad_cs_drive
    reg_bit_set(CANDS_PHY0_(1084)+chn_offset , 0, 21, 0x4FFFF);     //phy_pad_rst_drive
    reg_bit_set(CANDS_PHY0_(1075)+chn_offset , 0, 21, 0x4FFFF);     //phy_pad_addr_drive
    reg_bit_set(CANDS_PHY0_(1073)+chn_offset , 0, 21, 0x4FFFF);     //phy_pad_fdbk_drive

    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(544)+chn_offset+(i*0x200), 0, 8, 0xFF);     //phy_addr_tsel_select
    }

    reg_bit_set(CANDS_PHY0_(1074)+chn_offset ,  0, 13, 0x4FF);     //phy_pad_data_drive
    reg_bit_set(CANDS_PHY0_(1074)+chn_offset , 16, 13, 0x4FF);     //phy_pad_data_drive
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(5)+(i*0x200)+chn_offset ,16,  3, 0x0);     //phy_dq_tsel_select_en
        reg_bit_set(CANDS_PHY0_(6)+(i*0x200)+chn_offset , 8,  8, 0xFF);     //phy_dq_tsel_select
        reg_bit_set(CANDS_PHY0_(6)+(i*0x200)+chn_offset , 16, 8, 0x00);     //phy_dq_tsel_idle_select
        reg_bit_set(CANDS_PHY0_(6)+(i*0x200)+chn_offset ,24,  3, 0x0);     //phy_dqs_tsel_select
        reg_bit_set(CANDS_PHY0_(7)+(i*0x200)+chn_offset , 8,  8, 0xFF);     //phy_dqs_tsel_select
        reg_bit_set(CANDS_PHY0_(7)+(i*0x200)+chn_offset ,16,  8, 0x00);     //phy_dqs_tsel_idle_select
    }
}

void ds_phy_set(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 i=0;
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
    reg_bit_set(CANDS_PHY0_(1082)+chn_offset , 0, 21, 0x7FFFF);     //phy_pad_cke_drive
    reg_bit_set(CANDS_PHY0_(1076)+chn_offset , 0, 21, 0x7FFFF);     //phy_pad_clk_drive
    reg_bit_set(CANDS_PHY0_(1086)+chn_offset , 0, 21, 0x7FFFF);     //phy_pad_cs_drive
    reg_bit_set(CANDS_PHY0_(1084)+chn_offset , 0, 21, 0x7FFFF);     //phy_pad_rst_drive
    reg_bit_set(CANDS_PHY0_(1075)+chn_offset , 0, 21, 0x7FFFF);     //phy_pad_addr_drive
    reg_bit_set(CANDS_PHY0_(1073)+chn_offset , 0, 21, 0x7FF77);     //phy_pad_fdbk_drive

    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(544)+chn_offset+(i*0x200), 0, 8, 0xFF);     //phy_addr_tsel_select
    }

    reg_bit_set(CANDS_PHY0_(1074)+chn_offset ,  0, 13, 0x7FF);     //phy_pad_data_drive
    reg_bit_set(CANDS_PHY0_(1074)+chn_offset , 16, 13, 0x7FF);     //phy_pad_data_drive
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(5)+(i*0x200)+chn_offset , 16, 1, 0x0);     //phy_dq_wr_tsel_enable
    }
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(5)+(i*0x200)+chn_offset , 17, 2, 0x1);     //phy_dq_tsel_enable
    }
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(6)+(i*0x200)+chn_offset , 0, 8, 0);     //phy_dq_tsel_select
    }
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(6)+(i*0x200)+chn_offset , 8, 8, 0xff);     //phy_dq_tsel_select
    }
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(6)+(i*0x200)+chn_offset , 24, 1, 0x0);     //phy_dqs_wr_tsel_enable
    }
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(6)+(i*0x200)+chn_offset , 25, 2, 0x1);     //phy_dqs_tsel_enable
    }
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(7)+(i*0x200)+chn_offset , 0, 8, 0x0);     //phy_dqs_tsel_select
    }
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(7)+(i*0x200)+chn_offset , 8, 8, 0xff);     //phy_dqs_tsel_select
    }
}
void init_flow_cadence(DDR_CHANNEL_NUM_E chn_num)
{
    uint32 chn_offset = (chn_num==0)?0:0x00800000;
	volatile uint32 ctl_tr_done = 0;
	volatile uint32 i = 0;
	volatile uint32 timeout = 0;
    //no_phy_ind_train_init, Disables PHY independent training from executing during initialization, should check ???????
    reg_bit_set(CANDS_CTL0_(32)+chn_offset, 0,1,0);

    //phy_indep_train_mode   ????????
    reg_bit_set(CANDS_CTL0_(32)+chn_offset,  8,1,1);

    //trigger whole ddr init flow, set START to 1
    reg_bit_set(CANDS_CTL0_(0)+chn_offset,0,1,1);
    wait_us(20);
//    cands_phy_rx_cal_modify(chn_num);
    Do_RX_CAL_DQX_c();
    wait_us(20);
    for(i=0;i<4;i++)
    {
        reg_bit_set(CANDS_PHY0_(35+(128*i))+chn_offset, 24,1,0x1); //manual gate init
    }
    //pi_start
    reg_bit_set(CANDS_PI0_(0)+chn_offset,0,1,1);

}
#endif
#ifdef SW_WRDQLVL_EN
uint32 bist_func_all(uint32 chn_num);
void run_sw_wrdqlvl(uint32 fn)
{
	uint32 slice_num;
	uint32 delay_step;
	uint32 delay_cnt;
	uint32 delay_right;
	uint32 delay_left;
	uint32 delay_midle;
	uint32 bist_result;
        uint32 wrdqlvl_bist;

	wrdqlvl_bist = 1;
	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(289), 8,1,0x0);

	delay_cnt = 0x280;
	delay_step = 0x10;
	delay_midle = 0x280;

	reg_bit_set(CANDS_PHY0_(1024),8,3,fn);
	__ddr_print("\r\nwrdqlvl freq = ");
	ddr_print_u32_hex(fn);
#if 1
	//find the right margin
	for(delay_cnt=0x280;delay_cnt<=0x7f0;delay_cnt+=delay_step)
	{
		for(slice_num=0;slice_num<4;slice_num++)
		{
			reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq0_slave_delay
			reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq1_slave_delay
			reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq2_slave_delay
			reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq3_slave_delay

			reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq4_slave_delay
			reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq5_slave_delay
			reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq6_slave_delay
			reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq7_slave_delay

			reg_bit_set(CANDS_PHY0_(72)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdm_slave_delay
		}

		//ctrlupd_req
		reg_bit_set(CANDS_CTL0_(289), 0,1,0x1);

		bist_result = bist_func_all(0);
//		bist_result = bist_test(BIST_ALLWRC,SIPI_PATT,0x4000000,0x8);

		if(bist_result)
		{
			delay_right = delay_cnt - delay_step;
			goto wrdqlvl_right_out;
		}
	}
	//never fail set right to 0x280
	delay_right = 0x280;

wrdqlvl_right_out:

	__ddr_print("\r\nwrdqlvl_right_margin = ");
	ddr_print_u32_hex(delay_right);
	//find the left margin
	for(delay_cnt=0x280;delay_cnt>=0;delay_cnt-=delay_step)
	{
		for(slice_num=0;slice_num<4;slice_num++)
		{
			reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq0_slave_delay
			reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq1_slave_delay
			reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq2_slave_delay
			reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq3_slave_delay

			reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq4_slave_delay
			reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq5_slave_delay
			reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,16,11,delay_cnt);	//phy_clk_wrdq6_slave_delay
			reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdq7_slave_delay

			reg_bit_set(CANDS_PHY0_(72)+slice_num*0x200,0,11,delay_cnt);	//phy_clk_wrdm_slave_delay
		}

		//ctrlupd_req
		reg_bit_set(CANDS_CTL0_(289), 0,1,0x1);

//		bist_result = bist_test(BIST_ALLWRC,SIPI_PATT,0x4000000,0x8);
		bist_result = bist_func_all(0);

		if(bist_result)
		{
			delay_left = delay_cnt + delay_step;
			goto wrdqlvl_left_out;
		}
	}

	//never fail set left to 0x280
	delay_left = 0x280;

wrdqlvl_left_out:

	__ddr_print("\r\nwrdqlvl_left_margin = ");
	ddr_print_u32_hex(delay_left);

	delay_midle = (delay_right+delay_left)/2;
#endif
	for(slice_num=0;slice_num<4;slice_num++)
	{
		reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq0_slave_delay
		reg_bit_set(CANDS_PHY0_(68)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq1_slave_delay
		reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq2_slave_delay
		reg_bit_set(CANDS_PHY0_(69)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq3_slave_delay

		reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq4_slave_delay
		reg_bit_set(CANDS_PHY0_(70)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq5_slave_delay
		reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,16,11,delay_midle);	//phy_clk_wrdq6_slave_delay
		reg_bit_set(CANDS_PHY0_(71)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdq7_slave_delay

		reg_bit_set(CANDS_PHY0_(72)+slice_num*0x200,0,11,delay_midle);	//phy_clk_wrdm_slave_delay
	}

	__ddr_print("\r\nwrdqlvl_midle_margin = ");
	ddr_print_u32_hex(delay_midle);
	__ddr_print("\r\n");

	//ctrlupd_req
	reg_bit_set(CANDS_CTL0_(289), 0,1,0x1);

	//ctrlupd_req_per_aref_en
	reg_bit_set(CANDS_CTL0_(289), 8,1,0x1);

	wrdqlvl_bist=0;
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
		//__ddr_print("\r\nbit_num = ");
		//ddr_print_u32_hex(bit_num);
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
				__ddr_print("\r\nrdlvl_rising_left_right_mid_margin = (");
				rising_window = delay_right - delay_left;
			}
			else
			{
				__ddr_print("\r\nrdlvl_falling_left_right_mid_margin = (");
				falling_window = delay_right - delay_left;
			}
			ddr_print_u32_hex(delay_left);
			__ddr_print(",");
			ddr_print_u32_hex(delay_right);
			__ddr_print(",");
			ddr_print_u32_hex(delay_midle);
			__ddr_print(")");
		}
		if(rising_window > falling_window)
		{
			window_delta = rising_window - falling_window;
		}
		else
		{
			window_delta = falling_window - rising_window;
		}
		__ddr_print("\r\nslice");
		ddr_print_u32_hex(slice);
		__ddr_print(" window_delta = ");
		ddr_print_u32_hex(window_delta);
	}

	return window_delta;
}

uint32 sw_trigger_exit_sref_rdlvl(void)
{
        uint32 ret_value = 0;
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
	//slice0~3
	while(((REG32(CANDS_PHY0_(49))&0xf0000000) != 0)&&((REG32(CANDS_PHY0_(177))&0xf0000000) != 0)&&((REG32(CANDS_PHY0_(305))&0xf0000000) != 0)&&((REG32(CANDS_PHY0_(433))&0xf0000000) != 0))
        {
	    __ddr_print("\r\nrdlvl doing......");
        }
	if(((REG32(CANDS_PHY0_(49))&0xffff) != 0xffff)&&((REG32(CANDS_PHY0_(177))&0xffff) != 0xffff)&&((REG32(CANDS_PHY0_(305))&0xffff) != 0xffff)&&((REG32(CANDS_PHY0_(433))&0xffff) != 0xffff))
        {
            ret_value = 1;
        }
        else
        {
            ret_value = 0;
        }
        //dis pi_rdlvl_on_sref_exit
	reg_bit_set(CANDS_PI0_(95),16,1,0);
        return ret_value;

}
#define VREF_SCAN_MIN 0x1
#define VREF_SCAN_MAX 0x3F
#define DELTA_MIN  0x24
#define VREF_STEP  0x2
void run_sw_vref_lvl(uint32 fn)
{
	uint32 vref_cnt;
	uint32 i;
	uint32 tmp_window[4]={0,0,0,0};
	uint32 vref_best[4]={0,0,0,0};
	uint32 vref_best_p[4]={0,0,0,0};
	uint32 vref_best_m[4]={0,0,0,0};
	uint32 found[4]={0,0,0,0};

	reg_bit_set(CANDS_PHY0_(1024),8,3,fn);
	__ddr_print("\r\nvreflvl freq = ");
	ddr_print_u32_hex(fn);


	for(vref_cnt = VREF_SCAN_MIN;vref_cnt <= VREF_SCAN_MAX;vref_cnt += VREF_STEP)
	{
		__ddr_print("\r\n--------------vref_cnt = ");
		ddr_print_u32_hex(vref_cnt);
		__ddr_print("--------------");
		reg_bit_set(CANDS_PHY0_(1047), 8, 6, vref_cnt);
		reg_bit_set(CANDS_PHY0_(1048), 0, 6, vref_cnt);
		reg_bit_set(CANDS_PHY0_(1048), 16, 6, vref_cnt);
		reg_bit_set(CANDS_PHY0_(1049), 0, 6, vref_cnt);

		//trigger_sw_pad_cal_rx_cal(fn);
		//enable hw rdlvl
		if(sw_trigger_exit_sref_rdlvl())
                {
		    __ddr_print("\r\nrdlvl failed......");
                    continue;
                }
		for(i=0;i<4;i++)
		{
			if(found[i]==0)
			{
				tmp_window[i] = get_hw_rdlvl_window(i);
				if(tmp_window[i] <= DELTA_MIN)
				{
					vref_best_p[i] = vref_cnt-1;
					found[i] = 1;
				}
			}
		}
                if((found[0]==1)&&(found[1]==1)&&(found[2]==1)&&(found[3]==1))
                {
                    __ddr_print("\r\nplus sequence, rdlvl all slice get best value.");
                    break;
                }
	}
	for(i=0;i<4;i++)
	{
	    found[i]=0;
        }

	for(vref_cnt = VREF_SCAN_MAX;vref_cnt >= VREF_SCAN_MIN;vref_cnt -= VREF_STEP)
	{
		__ddr_print("\r\n--------------vref_cnt = ");
		ddr_print_u32_hex(vref_cnt);
		__ddr_print("--------------");
		reg_bit_set(CANDS_PHY0_(1047), 8, 6, vref_cnt);
		reg_bit_set(CANDS_PHY0_(1048), 0, 6, vref_cnt);
		reg_bit_set(CANDS_PHY0_(1048), 16, 6, vref_cnt);
		reg_bit_set(CANDS_PHY0_(1049), 0, 6, vref_cnt);

		//trigger_sw_pad_cal_rx_cal(fn);
		//enable hw rdlvl
		if(sw_trigger_exit_sref_rdlvl())
                {
		    __ddr_print("\r\nrdlvl failed......");
                    continue;
                }
		for(i=0;i<4;i++)
		{
			if(found[i]==0)
			{
				tmp_window[i] = get_hw_rdlvl_window(i);
				if(tmp_window[i] <= DELTA_MIN)
				{
					vref_best_m[i] = vref_cnt-1;
					found[i] = 1;
				}
			}
		}
                if((found[0]==1)&&(found[1]==1)&&(found[2]==1)&&(found[3]==1))
                {
                    __ddr_print("\r\nminus sequence, rdlvl all slice get best value.");
                    break;
                }
	}
	for(i=0;i<4;i++)
	{
	    vref_best[i] = (vref_best_p[i] + vref_best_m[i]) / 2;
        }

	__ddr_print("\r\nvref_best slice0 = ");
	ddr_print_u32_hex(vref_best[0]);
	__ddr_print("\r\nvref_best slice1 = ");
	ddr_print_u32_hex(vref_best[1]);
	__ddr_print("\r\nvref_best slice2 = ");
	ddr_print_u32_hex(vref_best[2]);
	__ddr_print("\r\nvref_best slice3 = ");
	ddr_print_u32_hex(vref_best[3]);

	for(i=0;i<4;i++)
	{
		reg_bit_set(CANDS_PHY0_(1024),8,3,i);
		reg_bit_set(CANDS_PHY0_(1047), 8, 6, vref_best[0]);
		reg_bit_set(CANDS_PHY0_(1048), 0, 6, vref_best[1]);
		reg_bit_set(CANDS_PHY0_(1048), 16, 6, vref_best[2]);
		reg_bit_set(CANDS_PHY0_(1049), 0, 6, vref_best[3]);
	}
        sw_trigger_exit_sref_rdlvl();
	//trigger_sw_pad_cal_rx_cal(fn);
}
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

        chn_offset_do_rx = chn_offset;
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
	ddr_info_init(chn_num);
	//set ddr clk div
	#ifdef DRAM_LPDDR3
	ddr_clk_set(chn_num,233000000,islp3);
	#else
	ddr_clk_set(chn_num,26000000,islp3);
	ddr_freq_target_set(ddr_clk);
	#endif

	//ctl&phy reset
	cands_ctl_phy_release(chn_num);

        light_sleep_ddr_workaround(chn_num);
	//ctl&pi&phy reg set
	cands_ctl_init(chn_num,ddr_type,ctl_timing_info,ctl_perchn_qos,ctl_allchn_qos,f0,f1,f2,f3,f4);
	cands_pi_init(chn_num,ddr_type,pi_timing_info,f0,f1,f2,f3,f4);
	cands_phy_init(chn_num,ddr_type,phy_timing_info, f0,f1,f2,f3);
	cands_phy_pinmux_init(chn_num, ddr_type);
        phy_on_fly_gate_adjust_en(chn_num);
#ifdef DDR_IP_CONFIG_FILE
        #ifdef DRAM_LPDDR4
        pi_init_work_freq_lp4(chn_num);
        boot_freq_init_freq(chn_num, 4, fn_ctl_target);
        fsp_lp4(chn_num);
        //device0_byte0_cs0,  for mrr data back on 1:byte0    2:byte1    3:byte2     4:byte3       0: data always 0
        reg_bit_set(CANDS_CTL0_(285)+chn_offset,  24,4,1);
        //device0_byte0_cs1,  for mrr data back on 1:byte0    2:byte1    3:byte2     4:byte3       0: data always 0
        reg_bit_set(CANDS_CTL0_(287)+chn_offset,  0,4,1);

        addr_map(chn_num);
//        reg_bit_set(CANDS_PHY0_(1024)+chn_offset,  0,1,0x1); //
        reg_bit_set(CANDS_PHY0_(1026)+chn_offset,  24,1,0x0); //lp4_phy_boot_disable
        if(fn_ctl_target==3)
	 {
		reg_bit_set(CANDS_PHY0_(1093)+chn_offset,  4,4,0x7); //cal_mode
        }
	 else
	 {
		reg_bit_set(CANDS_PHY0_(1093)+chn_offset,  4,4,0x6); //cal_mode
	 }
        reg_bit_set(CANDS_PHY0_(1095)+chn_offset,  8,3,0x0); //cal_clk
        w2w_diffcs_dly(chn_offset,0x10);
        lp4_phy_vref_cfg(chn_num); //For non-odt
        lp4_ds_phy_set(chn_num);

        reg_bit_set(CANDS_PHY0_(1024)+chn_offset,  8,3,0x3); //
//        reg_bit_set(CANDS_PHY0_(1077)+chn_offset, 17,1,0x1); //
//        reg_bit_set(CANDS_PHY0_(90)+chn_offset, 0, 11, 0x100); //phy_wdqlvl_dqdm_slv_dly_start
//        reg_bit_set(CANDS_PHY0_(218)+chn_offset, 0, 11, 0x100); //phy_wdqlvl_dqdm_slv_dly_start
//        reg_bit_set(CANDS_PHY0_(346)+chn_offset, 0, 11, 0x100); //phy_wdqlvl_dqdm_slv_dly_start
//        reg_bit_set(CANDS_PHY0_(474)+chn_offset, 0, 11, 0x100); //phy_wdqlvl_dqdm_slv_dly_start
        phy_gtlvl_capture_cnt(chn_num);
        phy_wrlvl_early_force_zero(chn_num);
        phy_rptr_update(chn_num, 0x8);
        phy_dq_tsel_rd_timing(chn_num);
        phy_cs_training_en(chn_num);
        training_cs_map(chn_num);
        ca_vref_training_setting(chn_num);
        pi_init_training_enable(chn_num);
        pi_mr_modify(chn_num);
        ctrl_mr_modify(chn_num);
//        reg_26_1400_diff_with_4freq_modify(chn_num);

//        reg_bit_set(CANDS_PHY0_(1024)+chn_offset,  0,1,0x0); //
        reg_bit_set(CANDS_PHY0_(1024)+chn_offset,  8,3,0x0); //
        #endif
        pcpcs_pd_disable(chn_num);

        init_flow_cadence(chn_num);

	//polling training done
	polling_pi_training_done(chn_num,islp3);

	//wait ctl training done
	wait_ctl_init_done(chn_num);
        sync_mr12_mr14(chn_num,islp3);

	#ifdef DDR_AUTO_DETECT
	ddr_type = cands_ddr_auto_detect(chn_num,islp3);
	cands_ctl_addrmap_init(chn_num,ddr_type);
	cands_pi_addrmap_init(chn_num, ddr_type);
	cands_auto_detect_fix_reg(chn_num,islp3,ddr_type );
	#endif
#else
	//trigger ddr init flow
	ddr_init_trigger(chn_num);

	//polling training done
	polling_pi_training_done(chn_num,islp3);

	//wait ctl training done
	wait_ctl_init_done(chn_num);

        #ifdef SW_WRDQLVL_EN
        run_sw_wrdqlvl(0);
        #endif
	#ifdef DRAM_LPDDR4
	sync_mr12_mr14(chn_num,islp3);
        f0_master_delay_update(chn_num);
	#endif

	#ifdef DDR_AUTO_DETECT
	ddr_type = cands_ddr_auto_detect(chn_num,islp3);
	cands_ctl_addrmap_init(chn_num,ddr_type);
	cands_pi_addrmap_init(chn_num, ddr_type);
	cands_auto_detect_fix_reg(chn_num,islp3,ddr_type );
	#endif

	//cands_phy_rx_cal_modify(chn_num);
	//Do_RX_CAL_DQX_c();
	//manual_clear_gate_init(chn_num);
	//cands_do_sw_training(chn_num);
	//if lp4 init with fsp, write fsp valid
	//write_fsp_valid(chn_num, ddr_type);
#if DO_DFS_INIT
	dfs_reg_cfg(chn_num);

	#ifdef DRAM_LPDDR4
	//lp4_dfs_dma_cfg(chn_num);

	//dfs to 1200mhz
	if(ddr_clk >=1400000000){
            if(3!=FN_CTL_TARGET){
	    dfs_noinit_tr_en(chn_num);
	    dfs_go(chn_num,3);
	    dfs_tr_polling(chn_num);
            }
	}
        //dfs to 600mhz
	else if(ddr_clk >= 934000000){
            if(2!=FN_CTL_TARGET){
	    dfs_noinit_tr_dis(chn_num);
	    dfs_go(chn_num,2);
	    }
        }
        //dfs to 400mhz
	else if(ddr_clk >= 466000000){
            if(1!=FN_CTL_TARGET){
	    dfs_noinit_tr_dis(chn_num);
	    dfs_go(chn_num,1);
            }
	}
        //dfs to 200mhz
	else{
            if(0!=FN_CTL_TARGET){
	    dfs_noinit_tr_dis(chn_num);
	    dfs_go(chn_num,0);
            }
	}

	dfs_noinit_tr_dis(chn_num);
	#else
	//dfs_dma_cfg(chn_num);
	dfs_noinit_tr_en(chn_num);
	dfs_go(chn_num,1);
        #ifdef SW_WRDQLVL_EN
        run_sw_wrdqlvl(1);
        #endif
	dfs_tr_polling(chn_num);
	dfs_go(chn_num,2);
        #ifdef SW_WRDQLVL_EN
        run_sw_wrdqlvl(2);
        #endif
	dfs_tr_polling(chn_num);
	dfs_go(chn_num,3);
        #ifdef SW_WRDQLVL_EN
        run_sw_wrdqlvl(3);
        #endif
	dfs_tr_polling(chn_num);
	run_sw_vref_lvl(3);
	dfs_noinit_tr_dis(chn_num);

	//disable rpull
	reg_bit_set(CANDS_PHY0_(1074)+chn_offset,29,1,0); 					//rpull
	//dfs to 233mhz
	if(ddr_clk == 233000000){
	dfs_go(chn_num,0);
	}

	//dfs to 368mhz
	if(ddr_clk == 368000000){
	dfs_go(chn_num,1);
	}

	//dfs to 622mhz
	//dfs_noinit_tr_en(chn_num);
	if(ddr_clk == 622000000){
	dfs_go(chn_num,2);
	}
	#endif
#endif
#endif

	manual_clear_master_dly_lock(chn_num);
        ddr_lowpower_init(chn_num,ddr_clk);
	rf_active_hw_wait_cnt_2_cfg(chn_num,ddr_clk);
	reg_bit_set((PUB0_APB_PUB_MTX_LP_CFG2+chn_offset), 0, 16, 6000);	//for smart light sleep

	//en tref auto update
	reg_bit_set(CANDS_CTL0_(490)+chn_offset,  14,1,1);
	//en auto mrr temp check
	reg_bit_set(CANDS_CTL0_(490)+chn_offset,  0,1,1);
}

#if 0
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
#endif

void prepare_reinit(void)
{
	REG32(DDR0_ACC_RDY) |= (0x1 << 0);
	//REG32(DDR0_LIGHT_ACC_RDY) |= (0x1 << 0);
	reg_bit_set(DDR0_SLP_CFG,0,16,DDR0_SLEEP_WAIT_CNT);
	//reg_bit_set(DDR0_SLP_CFG,16,16,DDR0_PWR_DOWN_WAIT_CNT);
	REG32(DDR1_ACC_RDY) |= (0x1 << 0);
	//REG32(DDR1_LIGHT_ACC_RDY) |= (0x1 << 0);
	//reg_bit_set(DDR1_SLP_CFG,0,16,DDR0_SLEEP_WAIT_CNT);
	//reg_bit_set(DDR1_SLP_CFG,16,16,DDR0_PWR_DOWN_WAIT_CNT);

	reg_bit_set(CGM_AON_PUB_APB_CFG,0,3,5); //clk aon pub apb : 0: rco_4m, 1: 26M_aon, 2:rcp_100m, 3:96m, 4:128m, 5:153.6m, default:3'h1
	#ifdef PUB_FORCE_ON
	reg_bit_set(PMU_APB_PD_PUB0_SYS_CFG, 24, 2, 0);
	if(is_lp3())
	{
		reg_bit_set(PMU_APB_PD_PUB1_SYS_CFG, 24, 2, 2);
	}
	else
	{
		reg_bit_set(PMU_APB_PD_PUB1_SYS_CFG, 24, 2, 0);
	}
	#else
	reg_bit_set(PMU_APB_PD_PUB0_SYS_CFG, 24, 2, 1);
	if(is_lp3())
	{
		reg_bit_set(PMU_APB_PD_PUB1_SYS_CFG, 24, 2, 2);
	}
	else
	{
		reg_bit_set(PMU_APB_PD_PUB1_SYS_CFG, 24, 2, 1);
	}
	#endif
}

void bist_func(uint32 chn_num)
{
	uint32 bist_timeout=0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	REG32(0xc0018028+chn_offset) =0x2a;
	REG32(0xc00d0000+chn_offset) =0x30021b1;
	REG32(0xc00d0004+chn_offset) =0x3fF;
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
	REG32(0xc00d0004+chn_offset) =0x3fF;
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
		REG32(0xc0018028+chn_offset) =0x0;
		__ddr_print("\r\n bist failed, ddr unstable......");
		while(1);
	}

	REG32(0xc0018028+chn_offset) =0x0;

}

uint32 bist_func_all(uint32 chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 bist_base_offset;
	uint32 i;
	uint32 bist_adr_base;

	REG32(0xc0018028+chn_offset) =0x2a;

//while(1)
{
	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;
		bist_adr_base = (0x14a00000+(i*0x28000));
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021b1;
		REG32(0xc00d0004+chn_offset+bist_base_offset) =0x7Ff;
		REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
		REG32(0xc00d000c+chn_offset+bist_base_offset) =0x0;
		REG32(0xc00d0010+chn_offset+bist_base_offset) =0x0ff0c3a5;
		REG32(0xc00d0014+chn_offset+bist_base_offset) =0xffffaa55;
		REG32(0xc00d0018+chn_offset+bist_base_offset) =0x1111aa55;
		REG32(0xc00d001c+chn_offset+bist_base_offset) =0xaaaaaa55;
		REG32(0xc00d0020+chn_offset+bist_base_offset) =0x1234aa55;
		REG32(0xc00d0024+chn_offset+bist_base_offset) =0x0000aa55;
		REG32(0xc00d0028+chn_offset+bist_base_offset) =0x00000000;
		REG32(0xc00d002c+chn_offset+bist_base_offset) =0x00000000;

		REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
		REG32(0xc00d0004+chn_offset+bist_base_offset) =0x7Ff;
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021b5;
	}

	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021b3;
	}

	while((REG32(0xc00d00b0+chn_offset) & 0x2) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x4000) & 0x2) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x8000) & 0x2) != 0x2);
}

	REG32(0xc0018028+chn_offset) =0x0;
        if(
	((REG32(0xc00d00b0+chn_offset) & 0x1) != 0x0)||
	((REG32(0xc00d00b0+chn_offset+0x4000) & 0x1) != 0x0)||
	((REG32(0xc00d00b0+chn_offset+0x8000) & 0x1) != 0x0))
        return 1;
        else
        return 0;
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
	__ddr_print("\r\nddr bist pass num = ");
	ddr_print_u32_hex(pass_num);
	__ddr_print("\r\n");
}

	REG32(0xc0018028+chn_offset) =0x0;
}

#ifdef DRAM_LPDDR3
void deep_sleep_ddr_workaround()
{
    REG32(DDR1_ACC_RDY) = 0x00000001;
    REG32(AON_TOP_PUB1_SYS_SLEEP_CTRL) |= 0xC;
    REG32(PMU_APB_PD_PUB1_SYS_CFG) = 0x0220581C;
    REG32(PMU_APB_FENCING_LOCK_BYP) = 0x780;
}
#endif

uint32 get_aon_ver_id(void)
{
	return REG32(0xe42e3120);
}
void sdram_init(uint32 ddr_clk)

{
	uint32 i = 0;
	BOOLEAN islp3 = 0;
	islp3 = is_lp3();

	aon_ver_id = get_aon_ver_id();

	//ddr_mpu_set();
	//ddr_pin_preset(islp3);
	ddr_chn_init(0,islp3,ddr_clk, F0_FREQ, F1_FREQ, F2_FREQ, F3_FREQ, F4_FREQ);
	ddr_chn_init(1,islp3,ddr_clk, F0_FREQ, F1_FREQ, F2_FREQ, F3_FREQ, F4_FREQ);
	prepare_reinit();
	#ifdef DRAM_LPDDR3
	deep_sleep_ddr_workaround();
	#endif

	#ifdef POWER_TEST
	ddr_power_test();
	#endif
	bist_func(0);

	__ddr_print("\r\nddr bist pass\r\n");
	#ifdef CONFIG_DFS_TIMING
	dfs_timing_test(0);
	#endif
	//bist_func_all_random(0);
        //ddr_dfs_busmon_cfg(islp3);
        //dfs_axi_busmon_cfg(ddr_clk);
	//__ddr_wdg_reset();
        #ifdef DDR_REINIT_TEST          //enable reinit code , need DDR_REINIT_TEST, in chipram/include/configs/spxxx_yyy.h and chipram/Makefile(SPxxx_yyy_CONFIG)
        DMC_Reinit();
        #endif
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

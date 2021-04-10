#include <asm/arch/sprd_reg.h>
#include "ddrc_init.h"
#include "ddrc_common.h"
#include "ddrc_r2p0_power_deepsleep.h"

//----------------------------------PUB Deep Sleep Configure--------------------------------------------------
struct PUB_CLK_CFG *clk_cfg;
struct PUB_CLK_CFG lp3_clk_info[]=
{
	/*freq_num,ddr_clk,half_freq_mode,emc_ckg_d2_sel_pure_sw,pure_sw_dfs_freq_sel,emc_ckg_sel_pure_sw,pure_sw_dfs_mode*/
	{0,DDR_CLK_256M		,1	,0x9	,0x0	,0x44	,0x0},
	{1,DDR_CLK_384M 	,1	,0x9	,0x1	,0x45	,0x0},
	{2,DDR_CLK_512M 	,1	,0x4	,0x2	,0x44	,0x1},
	{3,DDR_CLK_622M 	,0	,0x0	,0x3	,0x28	,0x1},
	{4,DDR_CLK_768M 	,0	,0x0	,0x4	,0x43	,0x1},
	{5,DDR_CLK_933M 	,0	,0x0	,0x5	,0x18	,0x1},
	{6,DDR_CLK_1200M 	,0	,0x0	,0x6	,0x08	,0x1},
};

uint32 phy0_reg_arr[DMC_PHY_REG_NUM];

uint32 ctl_reg0_arr[DMC_CTRL_REG0_NUM];
uint32 ctl_reg1_arr[DMC_CTRL_REG1_NUM];
uint32 ctl_reg2_arr[DMC_CTRL_REG1_NUM];

struct ddr_sys_info sys_info_config;
struct ddr_sys_info * sys_info=&sys_info_config;



void __data_move( uint32 src,uint32 dst,uint32 count)
{
	volatile uint32 i=0;
	for(i=0;i<count;i++)
	{
		REG32(dst+i*4)=REG32(src+i*4);
	}
}
 void phy_register_restore()
{
	uint32 *addr;
	addr=phy0_reg_arr;
	__data_move(addr,DMC_PHY0_(0),DMC_PHY_REG_NUM);
}
 void ctrl_register_restore()
{
	uint32 *addr;
	//disable dmc_rf_wr_lock
	REG32(POWER_DMC_CTL0_(39))=0xdeadbeef;
	//disable rf_auto_gate_en
	ctl_reg0_arr[0] &=~(0x1<<9);
	//disable MR4
	ctl_reg1_arr[5] &=~(0x3<<24);
	//disable ext clk ag en
	ctl_reg1_arr[9] &=~(0x1<<12);
	//disable drf dfs_en
	ctl_reg1_arr[11] &= ~(0x1<<0);
	//cpst period en
	ctl_reg1_arr[17] &=~(0x1<<16);
	//ctr regs restore
	addr=ctl_reg0_arr;
	__data_move(addr,POWER_DMC_CTL0_(0),DMC_CTRL_REG0_NUM);
	addr=ctl_reg1_arr;
	__data_move(addr,POWER_DMC_CTL0_(64),DMC_CTRL_REG1_NUM);
	//set reinit frequency num
	reg_bit_set(POWER_DMC_CTL0_(75),4,3,sys_info->freq_num);//drf_dfs_reg_set
}
void ddr_sys_info_init()
{
	clk_cfg=lp3_clk_info;
	if((REG32(POWER_DMC_CTL0_(0))>>29)&0x1)
		{
		sys_info->ddr_type=LPDDR4;
	}else
		{
		sys_info->ddr_type=LPDDR3;
	}
	sys_info->freq_num=((REG32(POWER_DMC_CTL0_(75)))>>8)&0x7;
	sys_info->ddr_clk=(clk_cfg+(sys_info->freq_num))->ddr_clk;
}
void pub_clk_init()
{
	uint32 freq_n=0;
	for(freq_n=0;freq_n<8;freq_n++)
		{
		//DMC_DTMG8_F0-rf_half_freq_mode
		reg_bit_set(POWER_DMC_CTL0_(104+24*freq_n),30,1,(clk_cfg+freq_n)->half_freq_mode);
	}
	//emc_ckg_d2_sel_pure_sw
	reg_bit_set(DFS_PURE_SW_CTRL,20,4,(clk_cfg+sys_info->freq_num)->emc_ckg_d2_sel_pure_sw);
	//pure_sw_dfs_freq_sel
	reg_bit_set(DFS_PURE_SW_CTRL,8,3,(clk_cfg+sys_info->freq_num)->pure_sw_dfs_freq_sel);
	//emc_ckg_sel_pure_sw
	reg_bit_set(DFS_PURE_SW_CTRL,1,7,(clk_cfg+sys_info->freq_num)->emc_ckg_sel_pure_sw);
	//pure_sw_dfs_clk_mode
	reg_bit_set(DFS_PURE_SW_CTRL,18,2,(clk_cfg+sys_info->freq_num)->pure_sw_dfs_clk_mode);
	//dmc_clk_init_sw_start
	reg_bit_set(DFS_CLK_INIT_SW_START, 0,1,1);
	//dmc_clk_init_sw_start
	reg_bit_set(DFS_CLK_INIT_SW_START, 0,1,0);

}
void polling_ddr_reinit_done()
{
	//ddr init start
	reg_bit_set(POWER_DMC_CTL0_(3),0,4,0xf);

	while(((REG32(POWER_DMC_CTL0_(3))>>16)&0x3) != 0x3);
	reg_bit_set(POWER_DMC_CTL0_(3),0,4,0x0);
}
void ddr_reinit_start()
{
	//enable_dfs
	reg_bit_set(POWER_DMC_CTL0_(75),0,1,0x0);/*mai:Current comment*/
	reg_bit_set(POWER_DMC_CTL0_(75),0,1,0x1);
	//phy init
	polling_ddr_reinit_done();
	//enable auto gate en
	reg_bit_set(POWER_DMC_CTL0_(81),16,1,0x1);//enable cps period en
	reg_bit_set(POWER_DMC_CTL0_(0),9, 1,0x1);//rf_auto_gate_en
	reg_bit_set(POWER_DMC_CTL0_(73),12,1, 0x1);//ext_clk_ag_en
	//wait dmc ctrl into self-refresh status
	while((REG32(POWER_DMC_CTL0_(73))>>24)&0xf !=0xf);
	//make sure ctl_reset-control register bit high
	reg_bit_set(POWER_DMC_CTL0_(64),15,1,0x1);
}
void ddr_reinit()
{
	uint32 i;
	//dmc_soft_reset
	reg_bit_set(DMC_SOFT_RST_CTRL,2,1,1);
	//ddr PHY soft rst
	reg_bit_set(DMC_SOFT_RST_CTRL,0,1,1);
	//pub_clk_init
	pub_clk_init();
	//restore ddr_phy
	phy_register_restore();
	//restore dmc ctrl
	ctrl_register_restore();
	//dmc_soft_rst ddrc soft reset
	reg_bit_set(DMC_SOFT_RST_CTRL,2,1,0x0);
	//ddrphy_soft_reset
	reg_bit_set(DMC_SOFT_RST_CTRL,0,1,0x0);
	ddr_reinit_start();
}

void pub_power_off()
{
	uint32 state=0;
	reg_bit_set(PUB_ACC_RDY,0,1,1);
	//ddr_phy_auto_ret_en
	reg_bit_set(DDR_OP_MODE_CFG,24,1,1);
	//ddr_cke_ret_en
	reg_bit_set(DDR_PHY_RET_CFG,0,1,1);
	REG32(PUB_ACC_RDY) &= ~(0x1<<0);//clear acc ready
	while((REG32(PUB_ACC_RDY)&0x1)!=0x0)
		{
		wait_us(1);
		}
	//store ddr freq
	sys_info->freq_num=(REG32(POWER_DMC_CTL0_(75))>>8)&0x7;
	//force deep sleep
	reg_bit_set(PUB_APB_SLEEP_CTRL,29,1,0x1);
	//wait state
	while(((REG32(DDR_SLP_CTRL_STATUS)>>0)&0xf)!=0x7);
}

static void pub_acc_rdy_set()
{
	uint32 acc_val=0x0;
	reg_bit_set(PUB_ACC_RDY,0,1,1);
	while(acc_val !=1)
		{
		acc_val=REG32(PUB_ACC_RDY)&0x1;
	}
}
void pub_power_on()
{
#ifdef FORCE_DEEP_SLEEP
	//force pub poweron
	reg_bit_set(PUB_APB_SLEEP_CTRL, 29,1,0x0);
	while(((REG32(PWR_STATUS4_DBG)>>16)&0xff)!=0);//PD pub sys state
#else
	//clear ap force deep
	reg_bit_set(PUB_SYS_DEEP_SLEEP_POLL1, 8,8,0);
	while(((REG32(PWR_STATUS4_DBG)>>16)&0xff)!=0);//PD pub sys state

	//pub_sys_auto_light_sleep_enable
	reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE,0,16,0xfffe);
#endif
	//ddr reint
	ddr_reinit();
	//ddr_cke_ret_en
	reg_bit_set(DDR_PHY_RET_CFG,0,1,0x0);
	//ddr_phy_auto_ret_en
	reg_bit_set(DDR_OP_MODE_CFG,24,1,0x0);
	//ddr_cke_ret_en
	reg_bit_set(DDR_PHY_RET_CFG,0,1,0x1);

	dmc_print_str("pub_power_on complete DDR bist Start\r\n");
	//bist-test
	//set pub_acc_rdy
	pub_acc_rdy_set();
}
void ddr_reinit_prepare()
{
#ifdef FORCE_DEEP_SLEEP
	//pub sys force shutdown
	reg_bit_set(PD_PUB_SYS_CFG,25,1,0x0);
	//pub_sys_auto_shutdown_en
	reg_bit_set(PD_PUB_SYS_CFG,24,1,0x1);
	//ddr_phy_auto_gate_en
	reg_bit_set(DDR_SLEEP_CTRL,6,1,0x1);
	//ddr_phy_en
	reg_bit_set(DDR_SLEEP_CTRL,2,1,0x0);
	//ddr_fencing_en
	reg_bit_set(FENCING_CTRL,30,1,0x1);
	//fencing_chn1_idle_cnt
	reg_bit_set(FENCING_CTRL,0,30,0x29B);
	//disp_async_brg_lp_eb
	reg_bit_set(DISP_ASYNC_BRG,0,1,0x1);

	reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE,0,16,0xffff);
#else
	//apcpu_ddr_ab_lp_eb
	reg_bit_set(APCPU_DDR_AB_LPC_CTRL,0,1,0x1);
	//pub_sys_auto_light_sleep_enable
	reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE,0,16,0xffff);
	//subsys wakeup bypass
	reg_bit_set(AUDCP2DDR_SLI_LPC_CTRL,0,1,0x0);
	reg_bit_set(DCAM2DDR_SLI_LPC_CTRL,0,1,0x0);
	reg_bit_set(ISP2DDR_SLI_LPC_CTRL,0,1,0x0);
	reg_bit_set(GPU2DDR_SLI_LPC_CTRL,0,1,0x0);
	//ddr_cke_ret_en
	reg_bit_set(DDR_PHY_RET_CFG,0,1,0x1);
	//pub sys auto deep sleep enable
	reg_bit_set(PUB_APB_SLEEP_CTRL,28,1,0x1);
	//pub sys deep sleep sel
	reg_bit_set(PUB_SYS_DEEP_SLEEP_SEL,0,1,0x1);
	//pd_pub_sys_auto_shutdown_en
	reg_bit_set(PD_PUB_SYS_CFG,24,1,0x1);
	//pub_sys_smart_light_en
	reg_bit_set(LIGHT_SLEEP_ENABLE,10,1,0x1);
	//ddr phy_auto ret_en
	reg_bit_set(DDR_OP_MODE_CFG,24,1,0x1);
#endif
}
static void pub_register_save()
{
	uint32 *addr;
	//ctl regs save
	addr=ctl_reg0_arr;
	__data_move(POWER_DMC_CTL0_(0),addr,DMC_CTRL_REG0_NUM);
	addr=ctl_reg1_arr;
	__data_move(POWER_DMC_CTL0_(64),addr,DMC_CTRL_REG1_NUM);

	addr=phy0_reg_arr;
	__data_move(DMC_PHY0_(0),addr,DMC_PHY_REG_NUM);
}
void pwr_dmc_reinit(void)
{
	uint32 result=0;
	dmc_print_str("pwr_dmc_reinit\r\n");
	ddr_sys_info_init();
	ddr_reinit_prepare();
	pub_register_save();
	//pub_sys_bypass
	reg_bit_set(REG_SYS_DDR_PWR_HS_ACK,0,8,0xff);
}
void reinit_handler(uint32 status)
{
	uint32 pub_level=status;
	if(pub_level == 1)
		{
	pub_power_off();
	}else if(pub_level == 0)
	{
	pub_power_on();
	}else
		{
	dmc_print_str("Status Error!!");
	}
}


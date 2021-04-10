/**************************************
 ;case                  nr      state
 ;
 ;CASE_BIST_READ        0       [done]
 ;CASE_BIST_WRITE,      1       [done]
 ;CASE_BIST_SIPI,       2       [x]
 ;CASE_POWER_DOWN1,     3       [done]
 ;CASE_POWER_DOWN2,     4       [done]
 ;CASE_POWER_DOWN3,     5       [done]
 ;CASE_POWER_DOWN4,     6       [done]=SR
 ;CASE_SELF_REFRESH,    7       [x]
 ;CASE_LIGHT_RETENTION, 8       [done]
 ;CASE_LIGHT,           9       [done]
 ;CASE_PUB_POWER_DOWN,  0xa     [x]
 ;CASE_CHANNEL_POWER,   0xb     [x]
 ;CASE_DEEP_SLEEP,      0xc     [done]
 ;CASE_IDLE,            0xd     [done]
 ;CASE_LIGHT_AUTO       0xe     [done]=smart light
 ;CASE_RPULL            0xf     [done]
 ;CASE_BYPASS_DESKEW,   0x10    [done]
 ;CASE_POWER_DOWN5,     0x11    [done]
 ;CASE_POWER_DOWN6,     0x12    [done]
 ;CASE_POWER_DOWN7,     0x13    [done]
 ;**************************************

 ;DFS freq
 ;
 ;0 - 233MHz
 ;1 - 364MHz
 ;2 - 622MHz
 ;3 - 933MHz
 ;**************************************
*/
#include "ddrc_init.h"
#include "ddrc_common.h"
#include "dram_test.h"
#include <asm/arch/sprd_reg.h>
#include "ddrc_r2p0_power_consumption.h"

extern ddrc_freq_info;
//#define PWR_CONS_MEAS_UART_EN
#define PWR_CONS_MEAS_LOG_EN
#define PWRTEST_ARUGMENTS_ADDR (0x00800000)

#define BIST_LEN (0x20000)
#define BIST_CHN0_START_ADDR (0x0)
#define BIST_CHN1_START_ADDR (0x30000000)
#define BIST_CHN2_START_ADDR (0x60000000)
#define PD_PUB_SYS_CFG		(PMU_APB_BASE_ADDR+0x006c)
#define PUB_APB_SLEEP_CTRL	(PMU_APB_BASE_ADDR+0x00cc)
extern DRAM_INFO_T dram_info;


enum PWR_CASE_SLT{
    DDR_IDLE,
    DDR_SR,
    DDR_PD,
    DDR_WRITE,
    DDR_READ,
    PUB_LS,
    PUB_DS
};
#define RX_BUF_MAX_SIZE 2000
char uart_rx_buf[RX_BUF_MAX_SIZE];
uint32 g_uart_rx_buf_index = 0;
uint32 g_uart_rx_buf_index_avild = 0;
static uint32 current_freq_fn=0;

static void pwr_uart_put(char *string)
{
    #ifdef PWR_CONS_MEAS_LOG_EN
    serial_puts(string);
    #endif
}

static char * pwr_uart_get(void)
{
#ifdef PWR_CONS_MEAS_UART_EN
	char tmp = 0;
	g_uart_rx_buf_index_avild = g_uart_rx_buf_index;
	do{
		tmp = (serial_getc());
		uart_rx_buf[g_uart_rx_buf_index++] = tmp;
	}while('\r' != tmp);
	uart_rx_buf[g_uart_rx_buf_index-1] = '\0';
	//UART tools send wrap transform \r\n or \n
	if(uart_rx_buf[g_uart_rx_buf_index_avild]=='\n')
		return &(uart_rx_buf[g_uart_rx_buf_index_avild+1]);//transform \r\n
	else
		return &(uart_rx_buf[g_uart_rx_buf_index_avild]);//transform \r
#endif
}

/****************************************
pub_sys_force_light_sleep 0x402B00CC[29]
pd_pub_sys_state 0x402B00C4[24:20]
****************************************/

void  ddr_idle_entry()
{
	u32 val ,num, mr0;

	//pub sys smart lslp ena
	reg_bit_set(LIGHT_SLEEP_ENABLE,10,1,0);
	/* disable pub light sleep */
	reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE, 0, 16, 0);
	reg_bit_set(DDR_CHN_SLEEP_CTRL0,16,10,0x0);/*Disable PORT LowPower:channel clock always available*/
	/*Step 1.setting lowpower*/
	reg_bit_set(DMC_CTL0_(0x0000), 8, 2, 0x2);//bit[9] auto gate bit[8] auto sleep
	reg_bit_set(DMC_CTL0_(0x0124), 0, 3, 0x0); /*drf_auto_clk_stop_en_ahb : 0 */
	/*drf_auto_pwr_down_en_ahb : 0 */
	/*drf_auto_self_ref_en_ahb : 0 */
	/* disable per cs en */
	reg_bit_set(DMC_CTL0_(0x0124), 12, 3, 0x0); /*bit [12]drf_ext_clk_ag_en*/
						/*bit [13]drf_auto_pwr_down_percs_en*/
						/*bit [14]drf_auto_self_refresh_percs_en*/
	wait_us(100);
   // while(0 != ((__raw_readl(DMC_CTL0_(0x0124)) >> 24) & (0x3)));     //1:sleep(Memory status for power down and selfrefresh all considered sleep state) 0:resumed; [24]:cs0, [25]:cs1.
	while(((__raw_readl(DMC_CTL0_(0xa0))>>6)&0x1f)!=0x0);//wait idle
}
void  ddr_pd_entry()
{
	u32 val ,num, mr0;
	ddr_idle_entry();
	//set auto_gate_en --weizeng
	reg_bit_set(DMC_CTL0_(0),9,1,1);
	/*Step 1.setting lowpower*/
	reg_bit_set(DMC_CTL0_(0x0124), 0, 3, 0x3);	/*drf_auto_clk_stop_en_ahb : 1 */
							/*drf_auto_pwr_down_en_ahb : 1 */
							/*drf_auto_self_ref_en_ahb : 0 */
	/* disable per cs en */
	reg_bit_set(DMC_CTL0_(0x0124), 12, 3, 0x2);	/*bit [12]drf_ext_clk_ag_en	:0*/
							/*bit [13]drf_auto_pwr_down_percs_en:1*/
							/*bit [14]drf_auto_self_refresh_percs_en:0*/
	wait_us(100);
	// while(3 != ((__raw_readl(DMC_CTL0_(0x0124)) >> 24) & 0x3));     //1:sleep(selfrefresh or pd ) 0:resuned; [24]:cs0, [25]:cs1.
	//while(((__raw_readl(DMC_CTL0_(0xa0))>>6)&0x1f)!=0x7);//percs 0x310000124 bit 13==0 check 该位置
	while(((__raw_readl(DMC_CTL0_(0xbc))>>0)&0xf)!=0x3);//percs 0x310000124 bit 13==1 check 该位置
}
void  ddr_srf_entry()
{
	u32 val ,num, mr0;
	ddr_idle_entry();/*Must entry Idle before you want Entry Self refresh */
	/*If PUB enter Ligh sleep,Memory must enter self refresh*/
	//set auto_gate_en --weizeng
	reg_bit_set(DMC_CTL0_(0),9,1,1);
	/*Step 1.setting lowpower*/
	reg_bit_set(DMC_CTL0_(0x0124), 0, 3, 0x5);	/*drf_auto_clk_stop_en_ahb : 1 */
							/*drf_auto_pwr_down_en_ahb : 0 */
							/*drf_auto_self_ref_en_ahb : 1 */
	/* disable per cs en */
	reg_bit_set(DMC_CTL0_(0x0124), 12, 3, 0x0);	/*bit [12]drf_ext_clk_ag_en*/
							/*bit [13]drf_auto_pwr_down_percs_en*/
							/*bit [14]drf_auto_self_refresh_percs_en*/
	wait_us(100);
	// while(3 != ((__raw_readl(DMC_CTL0_(0x0124)) >> 24) & (0x3)));     //1:sleep 0:resuned; [24]:cs0, [25]:cs1.
	while(((__raw_readl(DMC_CTL0_(0xa0))>>6)&0x1f)!=0x1b);
}
//----------------------------------BIST Configure--------------------------------------------------
static void ddr_bist_set(BIST_PARA *bist_parameter)
{
	volatile u32 i = 0;
	volatile u32 offset = bist_parameter->bist_chn_num*0x4000;
	//bist clear
	bist_clear(bist_parameter->bist_chn_num);
	__raw_writel(BIST_BASE_ADDR+0x00+offset,0x0);
	//bist enable
	reg_bit_set(BIST_BASE_ADDR+0x00+offset, 0, 1, 0x1);
	//bist_mode, 2'00:write 2'01 read, 2'10 all read after all write 2'11 read after write
	reg_bit_set(BIST_BASE_ADDR+0x00+offset, 3, 2, bist_parameter->bist_mode);
	//bist_data_pattern_mode, 2'00:user data pattern, 2'01:sipi data pattern, 2'10:lfsr data pattern, 2'11:xtk_data_pattern
	reg_bit_set(BIST_BASE_ADDR+0x00+offset, 5, 2, bist_parameter->data_pattern_mode);
	//bist_burst_length
	reg_bit_set(BIST_BASE_ADDR+0x00+offset, 7, 4,0xf);
	//bist_data_size, 3'000:byte, 3'001:half word, 3'010:word, 3'011:two words, 3'100:four words
	reg_bit_set(BIST_BASE_ADDR+0x00+offset,11, 3, bist_parameter->bist_data_mode_size);
	//bist_write_outstanding_en/bist_read_outstanding_en
	reg_bit_set(BIST_BASE_ADDR+0x00+offset,24, 2, 0x3);
	//datawidth_mode
	reg_bit_set(BIST_BASE_ADDR+0x00+offset,28, 1,(dram_info.dram_type==DRAM_LP3)?0x1:0x0);
	//bist_trans_num
	__raw_writel(BIST_BASE_ADDR+0x04+offset,(bist_parameter->bist_size));
	//bist_start_addr
	__raw_writel(BIST_BASE_ADDR+0x08+offset,bist_parameter->bist_src[bist_parameter->bist_chn_num]);
	//bist bw test mode if set 1 bist can while loop
	reg_bit_set(BIST_BASE_ADDR+0x00+offset,14,1,bist_parameter->bist_bw_test_mode);
	switch(bist_parameter->data_pattern_mode)
	{
		case USER_DATA_PATTERN:
			for(i = 0; i < 32; i++)
			{
				__raw_writel(BIST_BASE_ADDR+0x30+i*4+offset,user_mode_pattern_test[bist_parameter->user_pattern_data][i]);
			}
			break;
		case SIPI_DATA_PATTERN:
			for(i = 0; i < 6; i++)
			{
				__raw_writel(BIST_BASE_ADDR+0x10+i*4+offset,sipi_mode_pattern[i]);
			}
			break;
		case LFSR_DATA_PATTERN:
			for(i = 0; i < 4; i++)
			{
				__raw_writel(BIST_BASE_ADDR+0xcc+i*4+offset,lfsr_mode_pattern[i]);
			}
			break;
	}

}
static u32 bist_data_mode[3]={FOUR_WORDS,FOUR_WORDS,FOUR_WORDS};
//static void bist_init(u32 write_or_read, u32 data_pattern_mode, u32 bist_size, u32* bist_src,u32 bist_mode,u32 user_pattern_data)
static void ddr_bist_init(BIST_PARA *bist_parameter)
{
	u32 bist_chn_num=0;
	for(bist_chn_num=0;bist_chn_num <3;bist_chn_num++)
	{
		//bist_set(bist_chn_num,write_or_read,data_pattern_mode,bist_data_mode[bist_chn_num],bist_size,bist_src[bist_chn_num],bist_mode,user_pattern_data);
		bist_parameter->bist_chn_num=bist_chn_num;
		bist_parameter->bist_data_mode_size=bist_data_mode[bist_chn_num];
		ddr_bist_set(bist_parameter);
	}
}
static void	bist_en()
{
	u32 master_bit_set = ((BIST_PORT6_PUBCP_AUDCP_EN<<6)|(BIST_PORT5_WTLCP_EN<<5)|(BIST_PORT4_AP_VSP_AON_EN<<4)
		|(BIST_PORT3_ISP_EN<<3)|(BIST_PORT2_DPU_DCAM_EN<<2)|(BIST_PORT1_GPU_EN<<1)|(BIST_PORT0_CPU_EN<<0));
	REG32(BIST_PORT_ADDR) = master_bit_set;
}

static void bist_test_start()
{
	bist_en();
	reg_bit_set(DDR_CHN_SLEEP_CTRL0,16,10,0x3F1);/*Enable DMC PORT 1\2\3 clock :channel clock always available*/

	bist_clear_reset(BIST_CHN0);
	bist_clear_reset(BIST_CHN1);
	bist_clear_reset(BIST_CHN2);

	bist_trigger(BIST_CHN0);
	bist_trigger(BIST_CHN1);
	bist_trigger(BIST_CHN2);

	return;
}
 void dmc_ddr_test_stop()/*bist stop*/
{
	//volatile u32 offset = BIST_CHN0*0x4000;
	reg_bit_set(BIST_BASE_ADDR+0x00+BIST_CHN0*0x4000,1,1,0);	//Disable bist
	reg_bit_set(BIST_BASE_ADDR+0x00+BIST_CHN1*0x4000,1,1,0);	//Disable bist
	reg_bit_set(BIST_BASE_ADDR+0x00+BIST_CHN2*0x4000,1,1,0);	//Disable bist

	bist_wait_done(BIST_CHN0);
	bist_wait_done(BIST_CHN1);
	bist_wait_done(BIST_CHN2);

	bist_clear(BIST_CHN0);
	bist_clear(BIST_CHN1);
	bist_clear(BIST_CHN2);
	//reg_bit_set(DDR_CHN_SLEEP_CTRL0,16,10,0x3ff);/*Enable PORT LowPower:channel clock always available*/
	bist_dis();
}

void dmc_ddr_test_start(int bist_pattern,int user_pattern_data,int bist_mode)/*bist start*/
{
	u32 bist_addr[3];
	u32 size;
	u32 bist_result=0;
	BIST_PARA bist_parameter;
	size=((dram_info.cs0_size+dram_info.cs1_size-0x100000)>>8)-1;  //0x20000000
	bist_addr[0]=0x0;
	bist_addr[1]=(u32)(dram_info.cs0_size/2);
	bist_addr[2]=(u32)(dram_info.cs0_size);

	bist_parameter.bist_bw_test_mode=1;/*BW*/
	bist_parameter.bist_mode=bist_mode;/*READ or write or RW*/
	bist_parameter.bist_size=size;
	bist_parameter.bist_src=bist_addr;
	bist_parameter.data_pattern_mode=bist_pattern;/*SIPI/LFSR/USER DATA*/
	bist_parameter.user_pattern_data=user_pattern_data;

	ddr_bist_init(&bist_parameter);  /*configure bist parameter*/
	bist_test_start();/*start bist*/
}

void bist_prepare(int flag)
{
#if 1
	if(flag==1)/*Start*/
		{
		//close lowpower
		reg_bit_set(0x327e00c8,0, 16,0);/*close auto light*/

		reg_bit_set(0x327e0230,10,1,0);//close smart light

		wait_us(1000);
		reg_bit_set(PUB_ACC_RDY,0,1,0);//open accrdy
		/*open bist clock*/
		reg_bit_set(0x310531cc,4,1,1);/*open bist module clock*/
		reg_bit_set(0x31054000,23,1,1);
		/*AXI channel clock always on*/
		//reg_bit_set(0x327e00f8,16,10,0x0);
	}else if(flag == 0)/*stop*/
		{
		reg_bit_set(0x327e00c8,0, 16,0xffff);/*open auto light*/
		reg_bit_set(0x327e0230,10,1,1);//open smart light

		reg_bit_set(PUB_ACC_RDY,0,1,1);

		//reg_bit_set(0x327e0230,10,1,1);
		/*open bist clock*/
		reg_bit_set(0x310531cc,4,1,0);/*open bist module clock*/
		reg_bit_set(0x31054000,23,1,0);

		/*AXI channel clock depend HW(open lowpower)*/
	//	reg_bit_set(0x327e00f8,16,10,0x3ff);
	}
#else
;
#endif

}
void ddr_clear_area_space(int flag)//flag:	0:0x0 1:0xffffffff
{
	u32 bist_addr[3];
	u32 size;
	u32 bist_result=0;
	BIST_PARA bist_parameter;
	size=((dram_info.cs0_size+dram_info.cs1_size-0x100000)>>8)-1;  //0x20000000
	bist_addr[0]=0x0;
	bist_addr[1]=(u32)(dram_info.cs0_size/2);
	bist_addr[2]=(u32)(dram_info.cs0_size);

	bist_parameter.bist_bw_test_mode=0;/*BW*/
	bist_parameter.bist_mode=BIST_WRITE;/*READ or write or RW*/
	bist_parameter.bist_size=size;
	bist_parameter.bist_src=bist_addr;
	bist_parameter.data_pattern_mode=USER_DATA_PATTERN;/*SIPI/LFSR/USER DATA*/
	bist_parameter.user_pattern_data=flag;

	ddr_bist_init(&bist_parameter);  /*configure bist parameter*/
	bist_test_start();/*start bist*/

	bist_wait_done(BIST_CHN0);
	bist_wait_done(BIST_CHN1);
	bist_wait_done(BIST_CHN2);

	reg_bit_set(BIST_BASE_ADDR+0x00+BIST_CHN0*0x4000,1,1,0);	//Disable bist
	reg_bit_set(BIST_BASE_ADDR+0x00+BIST_CHN1*0x4000,1,1,0);	//Disable bist
	reg_bit_set(BIST_BASE_ADDR+0x00+BIST_CHN2*0x4000,1,1,0);	//Disable bist

	bist_clear(BIST_CHN0);
	bist_clear(BIST_CHN1);
	bist_clear(BIST_CHN2);

	bist_dis();


}
void  ddr_bist_read_entry()
{
	bist_prepare(1);

	//ddr_clear_area_space(1);//clear ddr space for Similar to simulation   0:write all 0  1:write all 1

	dmc_ddr_test_start(SIPI_DATA_PATTERN,0,BIST_READ);
}
void  ddr_bist_write_entry()
{
	bist_prepare(1);

	dmc_ddr_test_start(SIPI_DATA_PATTERN,0,BIST_WRITE);

}


void  pub_ls_entry()
{
	reg_bit_set(PUB_ACC_RDY,0,1,1);
	ddr_idle_entry();
	/* enable pub smart light sleep */
	ddr_srf_entry();
	//weizeng set
	reg_bit_set(DMC_CTL0_(0x124),0,3,0x0);
	reg_bit_set(DMC_CTL0_(0),8,2,0x1);/*close auto gate and open auto sleep*/
	reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE, 0, 16, 0x0);//set PMU register
	reg_bit_set(DDR_CHN_SLEEP_CTRL0,16,10,0x3ff);//DDR channel(AXI channel:0~9) low power mode
	/*close smart and force light*/
	reg_bit_set(LIGHT_SLEEP_ENABLE,10,1,0);//clear smart light
	reg_bit_set(PUB_APB_SLEEP_CTRL,29,2,0x2);//force light sleep and close force deep sleep
	/*sharkl5 judge smart light state*/
	// while(0x3F != (__raw_readl(REG32(REG_PMU_APB_LIGHT_SLEEP_MON)) & 0x3F));
	while(((__raw_readl(DMC_CTL0_(0xa0))>>6)&0x1f)!=0xb);
}
void  pub_ds_entry()
{
	//reg_bit_set(PD_PUB_SYS_CFG, 25, 1, 1);
	reinit_handler(1);
}
void pub_ds_exit()
{
	reinit_handler(0);
	ddr_idle_entry();
	ddr_idle_exit();
}

void  ddr_idle_exit()
{

	u32 val ,num, mr0;
	/*Step 1.setting lowpower*/
	reg_bit_set(DMC_CTL0_(0x0000), 8, 2, 0x3);//bit[9] auto gate bit[8] auto sleep
	reg_bit_set(DMC_CTL0_(0x0124), 0, 3, 0x5);	/*drf_auto_clk_stop_en_ahb : 1 */
							/*drf_auto_pwr_down_en_ahb : 0 */
							/*drf_auto_self_ref_en_ahb : 1 */
	/* enable per cs en */
	reg_bit_set(DMC_CTL0_(0x0124), 12, 2, 0x1);	/*bit [12]drf_ext_clk_ag_en*/
							/*bit [13]drf_auto_pwr_down_percs_en*/
	//  #ifdef LP4_PINMUX_CASE1
 	//  reg_bit_set(DMC_CTL0_(0x0124), 14, 1, 0x0);/*bit [14]drf_auto_self_refresh_percs_en*/
	//  #else
	reg_bit_set(DMC_CTL0_(0x0124), 14, 1, 0x1);
	//  #endif
	//pub sys smart lslp ena
	reg_bit_set(LIGHT_SLEEP_ENABLE,10,1,1);
	/* enable pub light sleep */
	reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE, 0, 16, 0xFFFF);
	reg_bit_set(DDR_CHN_SLEEP_CTRL0,16,10,0x3ff);
	wait_us(100);
}
void  ddr_pd_exit()
{
	ddr_idle_entry();
	ddr_idle_exit();


}
void  ddr_srf_exit()
{
	ddr_idle_entry();
	ddr_idle_exit();
}

void  pub_ls_exit()
{
	reg_bit_set(PUB_APB_SLEEP_CTRL,29,2,0x0);
	ddr_idle_entry();
	ddr_idle_exit();
}

void auto_gate_entry()
{
	u32 val ,num, mr0;
	ddr_idle_entry();/*Must entry Idle before you want Entry Self refresh */
	/*If PUB enter Ligh sleep,Memory must enter self refresh*/
	//set auto_gate_en --weizeng
	reg_bit_set(DMC_CTL0_(0),9,1,1);
	/*Step 1.setting lowpower*/
	reg_bit_set(DMC_CTL0_(0x0124), 0, 3, 0x0);	/*drf_auto_clk_stop_en_ahb : 0 */
							/*drf_auto_pwr_down_en_ahb : 0 */
							/*drf_auto_self_ref_en_ahb : 0 */
	/* disable per cs en */
	reg_bit_set(DMC_CTL0_(0x0124), 12, 3, 0x0); /*bit [12]drf_ext_clk_ag_en*/
	                                            /*bit [13]drf_auto_pwr_down_percs_en*/
	                                            /*bit [14]drf_auto_self_refresh_percs_en*/
	wait_us(100);
   // while(3 != ((__raw_readl(DMC_CTL0_(0x0124)) >> 24) & (0x3)));     //1:sleep 0:resuned; [24]:cs0, [25]:cs1.
	while(((__raw_readl(DMC_CTL0_(0xa0))>>6)&0x1f)!=0x0);
}
void auto_gate_exit()
{
	ddr_srf_exit();
}
void auto_ext_gate_selfrefresh_entry()
{
	u32 val ,num, mr0;
	ddr_idle_entry();/*Must entry Idle before you want Entry Self refresh */
	/*If PUB enter Ligh sleep,Memory must enter self refresh*/
	//set auto_gate_en --weizeng
	reg_bit_set(DMC_CTL0_(0),9,1,1);
	/*Step 1.setting lowpower*/
	reg_bit_set(DMC_CTL0_(0x0124), 0, 3, 0x5);	/*drf_auto_clk_stop_en_ahb : 1 */
							/*drf_auto_pwr_down_en_ahb : 0 */
							/*drf_auto_self_ref_en_ahb : 1 */
	/* disable per cs en */
	reg_bit_set(DMC_CTL0_(0x0124), 12, 3, 0x1);	/*bit [12]drf_ext_clk_ag_en*/
							/*bit [13]drf_auto_pwr_down_percs_en*/
							/*bit [14]drf_auto_self_refresh_percs_en*/
	wait_us(100);
	// while(3 != ((__raw_readl(DMC_CTL0_(0x0124)) >> 24) & (0x3)));	   //1:sleep 0:resuned; [24]:cs0, [25]:cs1.
	while(((__raw_readl(DMC_CTL0_(0xa0))>>6)&0x1f)!=0x1b);

}
void auto_ext_gate_selfrefresh_exit()
{
	ddr_srf_exit();
	reg_bit_set(0x310531cc,4,1,0);/*close bist module clock*/
}

void  ddr_bist_write_exit()
{
	dmc_ddr_test_stop();
	bist_prepare(0);

}

void  ddr_bist_read_exit()
{
	dmc_ddr_test_stop();
	bist_prepare(0);

}

static int sprd_strcmp(const char * cs,const char * ct)
{
	register signed char __res;

	while (1) {
	if(('\n' == *cs)||('\r' == *cs)){
                cs++;
                continue;
            }
	if ((__res = *cs - *ct++) != 0 || !*cs++)
		break;
	}

	return __res;
}

uint32 test_case_detect(char *uart_s)
{
    uint32 ret = 0xffff;
	if((0 == sprd_strcmp(uart_s, "0")) || (0 == sprd_strcmp(uart_s, "idle")))
		ret = 0;
	else if((0 == sprd_strcmp(uart_s, "1")) || (0 == sprd_strcmp(uart_s, "self refresh")))
		ret = 1;
	else if((0 == sprd_strcmp(uart_s, "2")) || (0 == sprd_strcmp(uart_s, "power down")))
		ret = 2;
	else if((0 == sprd_strcmp(uart_s, "3")) || (0 == sprd_strcmp(uart_s, "read")))
		ret = 3;
	else if((0 == sprd_strcmp(uart_s, "4")) || (0 == sprd_strcmp(uart_s, "write")))
		ret = 4;
	else if((0 == sprd_strcmp(uart_s, "5")) || (0 == sprd_strcmp(uart_s, "pub light sleep")))
		ret = 5;
	else if((0 == sprd_strcmp(uart_s, "6")) || (0 == sprd_strcmp(uart_s, "pub deep sleep")))
		ret = 6;
	else if((0 == sprd_strcmp(uart_s, "7")) || (0 == sprd_strcmp(uart_s, "auto gate")))
		ret=7;
	else if((0 == sprd_strcmp(uart_s, "8")) || (0 == sprd_strcmp(uart_s, "auto gate and ext auto gate+auto self refresh")))
		ret=8;
	else if(0 == sprd_strcmp(uart_s, "9"))
		ret = 9;
	return ret;
}

static uint32 ddr_freq_detect(char *uart_s)
{
	uint32 ret = 0xffff;
	if((0 == sprd_strcmp(uart_s, "0")) || (0 == sprd_strcmp(uart_s, "256")))
		 ret = 256;
	else if((0 == sprd_strcmp(uart_s, "1")) || (0 == sprd_strcmp(uart_s, "384")))
		ret = 384;
	else if((0 == sprd_strcmp(uart_s, "2")) || (0 == sprd_strcmp(uart_s, "512")))
		ret = 512;
	else if((0 == sprd_strcmp(uart_s, "3")) || (0 == sprd_strcmp(uart_s, "622")))
		ret = 622;
	else if((0 == sprd_strcmp(uart_s, "4")) || (0 == sprd_strcmp(uart_s, "768")))
		ret = 768;
	else if((0 == sprd_strcmp(uart_s, "5")) || (0 == sprd_strcmp(uart_s, "933")))
		ret = 933;
	else if((0 == sprd_strcmp(uart_s, "6")) || (0 == sprd_strcmp(uart_s, "1200")))
		ret = 1200;
	return ret;
}
//Set PUB Low Power seeting
//pub_sys_lightsleep.....xlsx
void consumption_pub_setting(void)
{
	dmc_print_str("\r\npub_low_power_setting\r\n");
//pub_qosc_ahb_rf
	//Disable debug Monitor Start
	reg_bit_set(0x31020280,1,1,0);
	//m1_qosc_cfg_clk_eb~m4_qosc_cfg_clk_eb
	reg_bit_set(0x31020408,8,1,0);
	reg_bit_set(0x31020608,8,1,0);
	reg_bit_set(0x31020B08,8,1,0);
	reg_bit_set(0x31020D08,8,1,0);
	reg_bit_set(0x3102001C,21,1,0);
	reg_bit_set(0x31020008,8,1,0);
//pub_apb_rf
	reg_bit_set(0x31054000,23,1,0);
	reg_bit_set(0x31054000,9,5,0);
	reg_bit_set(0x310531cc,3,1,0);
	reg_bit_set(0x310531cc,4,1,0);/*bist clock disable*/

//close ptm
	reg_bit_set(0x310531cc,6,3,0x0);


}
void wayne_bb_test()
{
	char * uart_string = 0;

	pwr_uart_put("\r\nPlease input wayne test case:");
	uart_string = pwr_uart_get();
	pwr_uart_put("\r\nUser's input: ");
	pwr_uart_put(uart_string);

	//wayne test -0115
	switch(uart_string[0])
	{
	case '1':
		//test_case_1
		reg_bit_set(DMC_PHY0_(0x0f4),21,2,0x0);//IBC &IB4==0(freq_fn*0xc0)
		reg_bit_set(DMC_PHY0_(0x1b4),21,2,0x0);
	break;
	case '2':
		//test_case_2
		reg_bit_set(DMC_PHY0_(0x0f4),23,1,0x1);//VREFI PD =1
		reg_bit_set(DMC_PHY0_(0x1b4),23,1,0x1);
		reg_bit_set(0x327D0348,1,1, 0x1);//VREFE--VREFE for lp3
		reg_bit_set(DMC_PHY0_(0), 8,4,0x1);//ZQ PD=1

	break;
	case '3':
	//test_case_3
		reg_bit_set(DMC_PHY0_(0x4),0,3,0x0);//ca drvp
		reg_bit_set(DMC_PHY0_(0x4),4,3,0x0);//ca drvn
		break;
	//test_case_4
	case '4':
		reg_bit_set(DMC_PHY0_(0x10),25,1,0x1);//PHY0
		reg_bit_set(DMC_PHY0_(0x1c),25,1,1);

		reg_bit_set(DMC_PHY0_(0x30),21,1,1);//PHY1
		reg_bit_set(DMC_PHY0_(0x3c),21,1,1);
		break;

	/*---------------*/
	default:
		pwr_uart_put("\r\nNO to do anything");
		}

}
void power_consumption_measure_entry()
{

	/*Attention:
	*This test base in ddr init Enable light sleep*/

	char * uart_string = 0;
	uint32 case_num = 0;
	uint32 ddr_freq = 0;
	uint32 uart_rx_buf_index = 0;
	uint32 ddr_freq_fn=0;

	if((dram_info.dram_type==DRAM_LP4)||(dram_info.dram_type==DRAM_LP4X))
		{
		//Close VRCG
		dmc_mrw(DRAM_MR_13,DRAM_CS_ALL,0x0);
		}


	consumption_pub_setting();




freq_change:
	reg_bit_set(PUB_ACC_RDY,0,1,0);//close accrdy
	g_uart_rx_buf_index = 0;
	__raw_writel(DMC_CTL0_(0x009c),0xdeadbeef);
	pwr_uart_put("\r\nIf you want change DDR frequency, type the number:	 ");
	if((dram_info.dram_type==DRAM_LP4)||(dram_info.dram_type==DRAM_LP4X))
		{
		pwr_uart_put("\r\n0:256M				  \r\n1:384M				  \r\n2:512M				  \r\n3:622M				  \r\n4:768M				  \r\n5:933M				  \r\n6:1200M	");	
		}
	else
		{
		pwr_uart_put("\r\n0:256M				  \r\n1:384M				  \r\n2:512M				  \r\n3:622M				  \r\n4:768M				  \r\n5:933M");
		}
	pwr_uart_put("\r\nAny other key will skip to change the DDR frequency.");
	uart_string = pwr_uart_get();
	pwr_uart_put("\r\nUser's input: ");
	pwr_uart_put(uart_string);
	//uart_rx_buf_index = g_uart_rx_buf_index;
	ddr_freq = ddr_freq_detect(uart_string);
	dmc_freq_sel_search(ddr_freq,&ddr_freq_fn);
	if(dram_info.dram_type == DRAM_LP3)
		{
		if(ddr_freq == 1200)
			{
			pwr_uart_put("\r\nError:LP3 MAX DDR freq 933,Try again!!");
			goto freq_change;
		}
	}
	if(0xffff != ddr_freq)
	{
		if(ddr_freq==DDR_CLK_1200M)
		{
			//vddcore change to 750mv
			regulator_set_voltage("vddcore",800);
			//dpll cfg and relock
			//dpll_cfg(DDR_CLK_1866M);
			dpll_cfg(DDR_CLK_1200M);
			//dfs to 1200m
			sw_dfs_go(ddr_freq_fn);
		}else
		{
			regulator_set_voltage("vddcore",750);
			dpll_cfg(DDR_CLK_1866M);
			sw_dfs_go(ddr_freq_fn);
		}
		pwr_uart_put("\r\nDDR Frequency scale sucess.");
		current_freq_fn=ddr_freq_fn;
		pwr_uart_put("\r\nCurrent FREQ=");
		print_Dec(ddr_freq);
		pwr_uart_put("\r\nCurrent FD=");
		print_Dec(current_freq_fn);
	}
	else
	{
		pwr_uart_put("\r\nChoose DDR Freqency Error, skip.");
		goto freq_change;
	}
	 pwr_dmc_reinit();//deep sleep prepare
	reg_bit_set(PUB_ACC_RDY,0,1,1);//open accrdy
uart_get:
	pwr_uart_put("\r\nDDR power consumption measure process.Please slect test case:     ");
	pwr_uart_put("\r\n0: idle+autogate");
	pwr_uart_put("\r\n1: auto gate+self refresh");
	pwr_uart_put("\r\n2: auto gate+power down");
	pwr_uart_put("\r\n3: read");
	pwr_uart_put("\r\n4: write");
	pwr_uart_put("\r\n5: pub light sleep");
	pwr_uart_put("\r\n6: pub deep sleep");

	pwr_uart_put("\r\n7: auto gate");
	pwr_uart_put("\r\n8: auto gate and ext auto gate+auto self refresh");

	pwr_uart_put("\r\n9: change DDR frequency");
	pwr_uart_put("\r\nType 0 or idle to slect idle case.     ");

	g_uart_rx_buf_index = uart_rx_buf_index;
	uart_string = pwr_uart_get();
	pwr_uart_put("\r\nUser's input: ");
	pwr_uart_put(uart_string);
	case_num = test_case_detect(uart_string);

	switch(case_num){
        	case 0:
//"idle":
            		ddr_idle_entry();
            		pwr_uart_put("\r\nDDR has stayed in idle status.");
            		pwr_uart_put("\r\nType any key to exit current status.");
            		pwr_uart_get();
            		pwr_uart_put("\r\nUser's input: ");
            		pwr_uart_put(uart_string);
            		pwr_uart_put(&(uart_rx_buf[g_uart_rx_buf_index]));
            		ddr_idle_exit();
            		break;
		case 1:
//"self refresh":
            		ddr_srf_entry();
            		pwr_uart_put("\r\nDDR has stayed in self refresh status.");
            		pwr_uart_put("\r\nType any key to exit current status.");
            		pwr_uart_get();
            		pwr_uart_put("\r\nUser's input: ");
            		pwr_uart_put(uart_string);
            		ddr_srf_exit();
            		break;
		case 2:
//"power down":
            		ddr_pd_entry();
            		pwr_uart_put("\r\nDDR has stayed in power down status.");
            		pwr_uart_put("\r\nType any key to exit current status.");
            		pwr_uart_get();
            		pwr_uart_put("\r\nUser's input: ");
            		pwr_uart_put(uart_string);
            		ddr_pd_exit();
            		break;
		case 3:
//"read":
            		ddr_bist_read_entry();
            		pwr_uart_put("\r\nDDR has stayed in burst read status, using bist modle.");
            		pwr_uart_put("\r\nType any key to exit current status.");
            		pwr_uart_get();
            		pwr_uart_put("\r\nUser's input: ");
            		pwr_uart_put(uart_string);
            		ddr_bist_read_exit();
			break;
		case 4:
//"write":
			ddr_bist_write_entry();
			pwr_uart_put("\r\nDDR has stayed in burst write status, using bist modle.");
			pwr_uart_put("\r\nType any key to exit current status.");
			pwr_uart_get();
			pwr_uart_put("\r\nUser's input: ");
			pwr_uart_put(uart_string);
			ddr_bist_write_exit();
			break;
		case 5:
//"pub light sleep":
			pub_ls_entry();
			pwr_uart_put("\r\nDDR has stayed in light sleep status.");
			pwr_uart_put("\r\nType any key to exit current status.");
			pwr_uart_get();
			pwr_uart_put("\r\nUser's input: ");
			pwr_uart_put(uart_string);
			pub_ls_exit();
			break;
		case 6:
//"pub deep sleep":
            		pub_ds_entry();
            		pwr_uart_put("\r\nDDR has stayed in deep sleep status.");
            		pwr_uart_put("\r\nType any key to exit current status.");
            		pwr_uart_get();
            		pwr_uart_put("\r\nUser's input: ");
            		pwr_uart_put(uart_string);
            		pub_ds_exit();
            		break;
		case 7:
//auto gate
			auto_gate_entry();
			pwr_uart_put("\r\nDDR has stayed in auto gate status.");
			pwr_uart_put("\r\nType any key to exit current status.");
			pwr_uart_get();
			pwr_uart_put("\r\nUser's input: ");
			pwr_uart_put(uart_string);
			auto_gate_exit();

			break;
		case 8:
//auto gate +ext auto gate+auto self refresh
			auto_ext_gate_selfrefresh_entry();
			pwr_uart_put("\r\nDDR has stayed in auto gate +ext auto gate+auto self refresh status.");
			pwr_uart_put("\r\nType any key to exit current status.");
			pwr_uart_get();
			pwr_uart_put("\r\nUser's input: ");
			pwr_uart_put(uart_string);
			auto_ext_gate_selfrefresh_exit();
			break;
		case 9:
// "change ddr frequency"
			goto freq_change;
			break;
		default :
			pwr_uart_put("\r\nInvalid option slected. Please type in again.");
			break;
    }
    goto uart_get;

}


#include "ddr_init.h"
#include "ddr_common.h"
#include "iwhale2_ddr_reinit.h"

#define PUB_POWER_ON				1
#define PUB_POWER_DOWN				0
//typedef unsigned long int	uint32;
#define PMU_DUMMY_REG				0xe60A2000

uint32 pub0_wakeup_freq ;
uint32 pub1_wakeup_freq ;

uint32 pub0_poweron_start_time;
uint32 pub0_poweron_end_time;
uint32 pub1_poweron_start_time;
uint32 pub1_poweron_end_time;

void bist_func_3rd(uint32 chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 bist_base_offset;
	uint32 i;
	uint32 bist_adr_base;

	REG32(0xc0018028+chn_offset) =0x2a;

	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;
		bist_adr_base = i*0x20000000;
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021a9;
		REG32(0xc00d0004+chn_offset+bist_base_offset) =0x3fF;
		REG32(0xc00d0008+chn_offset+bist_base_offset) =0x0;
		REG32(0xc00d000c+chn_offset+bist_base_offset) =0x0;
		REG32(0xc00d0010+chn_offset+bist_base_offset) =0xa55aaa55;
		REG32(0xc00d0014+chn_offset+bist_base_offset) =0xffffaa55;
		REG32(0xc00d0018+chn_offset+bist_base_offset) =0x1111aa55;
		REG32(0xc00d001c+chn_offset+bist_base_offset) =0xaaaaaa55;
		REG32(0xc00d0020+chn_offset+bist_base_offset) =0x1234aa55;
		REG32(0xc00d0024+chn_offset+bist_base_offset) =0x0000aa55;
		REG32(0xc00d0028+chn_offset+bist_base_offset) =0x01234567;
		REG32(0xc00d002c+chn_offset+bist_base_offset) =0x89abcdef;

		REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
		REG32(0xc00d0004+chn_offset+bist_base_offset) =0x3fF;
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021ad;
	}

	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021ab;
	}

	while((REG32(0xc00d00b0+chn_offset) & 0x3) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x4000) & 0x3) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x8000) & 0x3) != 0x2);

	REG32(0xc0018028+chn_offset) =0x0;

}

void bist_func_3wr(uint32 chn_num)
{
	uint32 bist_timeout=0;
	uint32 i;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 bist_base_offset;
	uint32 bist_adr_base;

	REG32(0xc0018028+chn_offset) =0x2a;
	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;
		bist_adr_base = i*0x20000000;

       		REG32(0xc00d0000+chn_offset+bist_base_offset)  =0x30021a1;
	        REG32(0xc00d0004+chn_offset+bist_base_offset)  =0x3fF;
      	        REG32(0xc00d0008+chn_offset+bist_base_offset)  =bist_adr_base;
    		REG32(0xc00d000c+chn_offset+bist_base_offset)  =0x0;
	        REG32(0xc00d0010+chn_offset+bist_base_offset)  =0xa55aaa55;
	        REG32(0xc00d0014+chn_offset+bist_base_offset)  =0xffffaa55;
    	        REG32(0xc00d0018+chn_offset+bist_base_offset)  =0x1111aa55;
	        REG32(0xc00d001c+chn_offset+bist_base_offset)  =0xaaaaaa55;
	        REG32(0xc00d0020+chn_offset+bist_base_offset)  =0x1234aa55;
	        REG32(0xc00d0024+chn_offset+bist_base_offset)  =0x0000aa55;
	        REG32(0xc00d0028+chn_offset+bist_base_offset)  =0x01234567;
	        REG32(0xc00d002c+chn_offset+bist_base_offset)  =0x89abcdef;

	        REG32(0xc00d0008+chn_offset+bist_base_offset)  =bist_adr_base;
	        REG32(0xc00d0004+chn_offset+bist_base_offset)  =0x3fF;
	        REG32(0xc00d0000+chn_offset+bist_base_offset)  =0x30021a5;
	}

	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;
		REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30021a3;
	}

	while((REG32(0xc00d00b0+chn_offset) & 0x3) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x4000) & 0x3) != 0x2);
	while((REG32(0xc00d00b0+chn_offset+0x8000) & 0x3) != 0x2);

	REG32(0xc0018028+chn_offset) =0x0;

}


uint32 clr_err[8];
void ret_clr_err(void)
{
	uint32 i;
	for(i=0;i<8;i++)
	{
		//REG32(TEST_BASE_ADDR1 + i) = REG32(TEST_BASE_ADDR1 +i);
		clr_err[i] = REG32(TEST_BASE_ADDR1 +i);
	}
}


uint32 is_lpddr4()
{
	if(REG32(PMU_DUMMY_REG))
	{

		return 0;
	}
	else
	{
		//return 0;
		return 0;
	}
}

void __data_move(uint32 src,uint32 dst,uint32 count)
{
	volatile uint32 i = 0;

	for(i = 0; i < count;i++)
	{
		REG32(dst+i*4) = REG32(src+i*4);
	}
}

#if 0
#define REG8(_x_)   (*(volatile unsigned char *)(_x_))
void ddr_pre_write_data()
{
	uint32 i;
	uint32 len;
	len = TEST_LEN;
#if 1
	for(i=0;i<len;i++)
	{
		REG8(TEST_BASE_ADDR1 + i) = i+1;
	}
#else
	RE32(TEST_BASE_ADDR1 + 0)=0x44332211;
	RE32(TEST_BASE_ADDR1 + 4)=0x88776655;
	RE32(TEST_BASE_ADDR1 + 8)=0xccbbaa99;
	RE32(TEST_BASE_ADDR1 + 0xc)=0x11ffeedd;
	RE32(TEST_BASE_ADDR1 + 0x10)=0x55443322;
	RE32(TEST_BASE_ADDR1 + 0x14)=0x66554433;
	RE32(TEST_BASE_ADDR1 + 0x18)=0x77665544;
#endif
}
#endif

#if 1
void ddr_pre_write_data()
{
	uint32 i;
	uint32 len;
	len = TEST_LEN;
	for(i=0;i<len;i+=0x04)
	{
		REG32(TEST_BASE_ADDR1 + i) = 0x5555aaaa;

	}
}
#endif

#if 0
uint32 data_re[64];
volatile uint32 tmp[64];
uint32 check_ddr_retention_data()
{
	uint32 i;
	uint32 len;
	//uint32 tmp;
	uint32 flag=1;
	len = TEST_LEN;
	//data_re_0 =*((volatile unsigned long long *)(TEST_BASE_ADDR1));
//	data_re_1 = REG32(TEST_BASE_ADDR1 + 1*4);
	for(i=0;i<(len/4);i++)
	{
		data_re[i] = REG32(TEST_BASE_ADDR1 + i*4);
		tmp[i] = ((i*4+1)<<0) | ((i*4+2)<<8) | ((i*4+3)<<16) | ((i*4+4)<<24);
		if(data_re[i] != tmp[i])
			flag = 0;
	}
	return flag;

}

#endif

uint32 data_wr[32];
void check_ddr_wr_data()
{
	uint32 i;
	uint32 len;
	uint32 tmp;
	len = TEST_LEN;
	for(i=0;i<32;i++)
	{
		data_wr[i] = REG32(TEST_BASE_ADDR1 + i*4);
	}
}


uint32 data_re_0;
uint32 data_re_1;

#define DDR_TEST_BASE_ADDR1     0x00000000
#define DDR_TEST_BASE_ADDR2     0x10000000
#define DDR_TEST_LEN		0x1000000  //16M
uint32 loop_times1 = 0;
uint32 loop_times2 = 0;
void  ddr_test()
{
	uint32 result = 0;
	#if 0
	result = bist_test(BIST_ALLWRC,BIST_ARM,DDR_TEST_LEN,DDR_TEST_BASE_ADDR2,0);
	result += bist_test(BIST_ONEWRC,BIST_ARM,DDR_TEST_LEN,DDR_TEST_BASE_ADDR2,0);
	if(result)
	{
		while(1);
	}
	#endif
	#if 0
	bist_func_all(0);
	#endif
	//bist_clr_err(0);
	bist_func_3rd(0);
   	loop_times1++;
        if(loop_times1 == 0xffffffff)
               loop_times2++;
}

#if 1
uint32 data_re[32];
uint32 check_ddr_retention_data()
{
	uint32 i;
	uint32 len;
	uint32 flag=1;
	len = TEST_LEN;
//	data_re_0 =*((volatile unsigned long long *)(TEST_BASE_ADDR1));
//	data_re_1 = REG32(TEST_BASE_ADDR1 + 1*4);
	for(i=0;i<32;i++)
	{
		data_re[i] = REG32(TEST_BASE_ADDR1 + i*4);
		if(data_re[i] != 0x5555aaaa)
			flag = 0;;
	}

	return flag;
}
#endif

typedef struct  {
volatile uint32 pub0_sleep_num;
volatile uint32 pub0_wakeup_num;
volatile uint32 pub0_power_off;
volatile uint32 ddr0_acc_flag;

volatile uint32 pub1_sleep_num;
volatile uint32 pub1_wakeup_num;
volatile uint32 pub1_power_off;
volatile uint32 ddr1_acc_flag;

volatile uint32 pub0_poweroff_step;
volatile uint32 pub0_poweron_step;
volatile uint32 pub1_poweroff_step;
volatile uint32 pub1_poweron_step;

volatile uint32 pub0_poweron_time_max;
volatile uint32 pub0_poweron_time_aver;
volatile uint32 pub1_poweron_time_max;
volatile uint32 pub1_poweron_time_aver;

volatile uint32 pub0_bist_result;
volatile uint32 pub1_bist_result;

volatile uint32 ddr0_data_check_res;
volatile uint32 ddr1_data_check_res;

volatile uint32 ddr0_acc_rdy_num;
volatile uint32 ddr1_acc_rdy_num;

volatile uint32 data_retention_pass;

volatile uint32 pub0_retention_counter;
volatile uint32 pub1_retention_counter;

volatile uint32 pll_release_fail;
volatile uint32 pll_release_success;

}Debug_info_Type;





//aon space: 20KB, 0x2000a000--0x2000EFFF
Debug_info_Type *debug_info  =  PARA_SAVE_ADDRESS;
volatile uint32 *ctl0_1      = 	PARA_SAVE_ADDRESS+PARA_SAVE_SIZE;
volatile uint32 *pi0_1       =  CTL0_REG_SAVE_ADDR+CTL0_REG_SAVE_SIZE;
volatile uint32 *phy0_1_f3   =	PI0_REG_SAVE_ADDR+PI0_REG_SAVE_SIZE;
volatile uint32 *phy0_2_f3   =	PHY0_REG1_SAVE_ADDR_F3+PHY0_REG1_SAVE_SIZE_F3;

volatile uint32 *phy1_1_f3   =PHY1_REG1_SAVE_ADDR_F3 ;
volatile uint32 *phy1_2_f3_1 =PHY1_REG2_SAVE_ADDR1_F3;
volatile uint32 *phy1_2_f3_2 =PHY1_REG2_SAVE_ADDR2_F3;
volatile uint32 *phy1_2_f3_3 =PHY1_REG2_SAVE_ADDR3_F3;
volatile uint32 *phy1_2_f3_4 =PHY1_REG2_SAVE_ADDR4_F3;
volatile uint32 *phy1_2_f3_5 =PHY1_REG2_SAVE_ADDR5_F3;
volatile uint32 *phy1_2_f3_6 =PHY1_REG2_SAVE_ADDR6_F3;
volatile uint32 *phy1_2_f3_7 =PHY1_REG2_SAVE_ADDR7_F3;
volatile uint32 *phy1_2_f3_8 =PHY1_REG2_SAVE_ADDR8_F3;



volatile uint32 *phy0_1_f2     =  PHY0_REG1_SAVE_ADDR_F2 ;
volatile uint32 *phy0_2_f2_1   = PHY0_REG2_SAVE_ADDR1_F2;
volatile uint32 *phy0_2_f2_2   = PHY0_REG2_SAVE_ADDR2_F2;
volatile uint32 *phy0_2_f2_3   = PHY0_REG2_SAVE_ADDR3_F2;
volatile uint32 *phy0_2_f2_4   = PHY0_REG2_SAVE_ADDR4_F2;
volatile uint32 *phy0_2_f2_5   = PHY0_REG2_SAVE_ADDR5_F2;
volatile uint32 *phy0_2_f2_6   = PHY0_REG2_SAVE_ADDR6_F2;
volatile uint32 *phy0_2_f2_7   = PHY0_REG2_SAVE_ADDR7_F2;
volatile uint32 *phy0_2_f2_8   = PHY0_REG2_SAVE_ADDR8_F2;

volatile uint32 *phy0_1_f1    =  PHY0_REG1_SAVE_ADDR_F1 ;
volatile uint32 *phy0_2_f1_1  =  PHY0_REG2_SAVE_ADDR1_F1;
volatile uint32 *phy0_2_f1_2  =  PHY0_REG2_SAVE_ADDR2_F1;
volatile uint32 *phy0_2_f1_3  =  PHY0_REG2_SAVE_ADDR3_F1;
volatile uint32 *phy0_2_f1_4  =  PHY0_REG2_SAVE_ADDR4_F1;
volatile uint32 *phy0_2_f1_5  =  PHY0_REG2_SAVE_ADDR5_F1;
volatile uint32 *phy0_2_f1_6  =  PHY0_REG2_SAVE_ADDR6_F1;
volatile uint32 *phy0_2_f1_7  =  PHY0_REG2_SAVE_ADDR7_F1;
volatile uint32 *phy0_2_f1_8  =  PHY0_REG2_SAVE_ADDR8_F1;

volatile uint32 *phy0_1_f0    =  PHY0_REG1_SAVE_ADDR_F0	;
volatile uint32 *phy0_2_f0_1  =  PHY0_REG2_SAVE_ADDR1_F0;
volatile uint32 *phy0_2_f0_2  =  PHY0_REG2_SAVE_ADDR2_F0;
volatile uint32 *phy0_2_f0_3  =  PHY0_REG2_SAVE_ADDR3_F0;
volatile uint32 *phy0_2_f0_4  =  PHY0_REG2_SAVE_ADDR4_F0;
volatile uint32 *phy0_2_f0_5  =  PHY0_REG2_SAVE_ADDR5_F0;
volatile uint32 *phy0_2_f0_6  =  PHY0_REG2_SAVE_ADDR6_F0;
volatile uint32 *phy0_2_f0_7  =  PHY0_REG2_SAVE_ADDR7_F0;
volatile uint32 *phy0_2_f0_8  =  PHY0_REG2_SAVE_ADDR8_F0;



void para_init(void)
{
	debug_info->pub0_sleep_num = 0;
	debug_info->pub0_wakeup_num = 0;
	debug_info->pub0_power_off = 1;

	debug_info->pub1_sleep_num = 0;
	debug_info->pub1_wakeup_num = 0;
	debug_info->pub1_power_off = 1;

	debug_info->pub0_poweron_time_max = 0;
	debug_info->pub0_poweron_time_aver = 0;
	debug_info->pub1_poweron_time_max = 0;
	debug_info->pub1_poweron_time_aver = 0;


	debug_info->pub0_bist_result = 0x80000000;
	debug_info->pub1_bist_result = 0x80000000;

	debug_info->pub0_poweroff_step = 0;
	debug_info->pub0_poweron_step = 0;
	debug_info->pub1_poweroff_step = 0;
	debug_info->pub1_poweron_step = 0;

	debug_info->ddr0_acc_rdy_num = 0;
	debug_info->ddr1_acc_rdy_num = 0;

	debug_info->data_retention_pass = 0;

	debug_info->pub0_retention_counter = 0;
	debug_info->pub1_retention_counter = 0;

	debug_info->pll_release_fail = 0;
	debug_info->pll_release_success = 0;

}




void ctl_save_register(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	__data_move(CANDS_CTL0_(0)+chn_offset, ctl0_1, 481);
}

void ctl_restore_register(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	__data_move( ctl0_1,CANDS_CTL0_(0)+chn_offset, 481);
}

void pi_save_register(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	__data_move(CANDS_PI0_(0)+chn_offset, pi0_1, 249);
}

void pi_restore_register(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	__data_move( pi0_1,CANDS_PI0_(0)+chn_offset, 249);
}

void rx_calibration_restore(DDR_CHANNEL_NUM_E chn_num)
{

	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	__data_move(&phy0_2_f0_1[56],CANDS_PHY0_(56)+chn_offset, 11);
	__data_move(&phy0_2_f0_2[56],CANDS_PHY0_(184)+chn_offset, 11);
	__data_move(&phy0_2_f0_3[56],CANDS_PHY0_(312)+chn_offset, 11);
	__data_move(&phy0_2_f0_4[56],CANDS_PHY0_(440)+chn_offset, 11);
}

void phy_save_register(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	REG32(CANDS_PHY0_(1024)+chn_offset) &= ~(0x1 << 0);
	REG32(CANDS_PHY0_(1024)+chn_offset) &= ~(0XFFFF << 8);
	/*select which frequcey set to update*/
	REG32(CANDS_PHY0_(1024)+chn_offset) |= (3 << 8);
	if(chn_num == 0)
	{
		__data_move( CANDS_PHY0_(1024)+chn_offset,phy0_1_f3, 84);
		__data_move( CANDS_PHY0_(0)+chn_offset,   phy0_2_f3,1024);
	}
	else
	{

		__data_move( CANDS_PHY0_(1024)+chn_offset,phy1_1_f3,84);
		__data_move( CANDS_PHY0_(0)+chn_offset,   phy1_2_f3_1,100);
		__data_move( CANDS_PHY0_(128)+chn_offset, phy1_2_f3_2,100);
		__data_move( CANDS_PHY0_(256)+chn_offset, phy1_2_f3_3,100);
		__data_move( CANDS_PHY0_(384)+chn_offset, phy1_2_f3_4,100);
		__data_move( CANDS_PHY0_(512)+chn_offset, phy1_2_f3_5,38);
		__data_move( CANDS_PHY0_(640)+chn_offset, phy1_2_f3_6,38);
		__data_move( CANDS_PHY0_(768)+chn_offset, phy1_2_f3_7,38);
		__data_move( CANDS_PHY0_(896)+chn_offset, phy1_2_f3_8,38);
	}
	if(chn_num == 0)
	{
		REG32(CANDS_PHY0_(1024)+chn_offset) &= ~(0x1 << 0);
		REG32(CANDS_PHY0_(1024)+chn_offset) &= ~(0XFFFF << 8);
		REG32(CANDS_PHY0_(1024)+chn_offset) |= (2 << 8);

		__data_move( CANDS_PHY0_(1024)+chn_offset,phy0_1_f2  , 84);
		__data_move( CANDS_PHY0_( 0 )+chn_offset, phy0_2_f2_1,100);
		__data_move( CANDS_PHY0_(128)+chn_offset, phy0_2_f2_2,100);
		__data_move( CANDS_PHY0_(256)+chn_offset, phy0_2_f2_3,100);
		__data_move( CANDS_PHY0_(384)+chn_offset, phy0_2_f2_4,100);
		__data_move( CANDS_PHY0_(512)+chn_offset, phy0_2_f2_5,38);
		__data_move( CANDS_PHY0_(640)+chn_offset, phy0_2_f2_6,38);
		__data_move( CANDS_PHY0_(768)+chn_offset, phy0_2_f2_7,38);
		__data_move( CANDS_PHY0_(896)+chn_offset, phy0_2_f2_8,38);

		REG32(CANDS_PHY0_(1024)+chn_offset) &= ~(0x1 << 0);
		REG32(CANDS_PHY0_(1024)+chn_offset) &= ~(0XFFFF << 8);
		REG32(CANDS_PHY0_(1024)+chn_offset) |= (1 << 8);

		__data_move( CANDS_PHY0_(1024)+chn_offset,phy0_1_f1  , 84);
		__data_move( CANDS_PHY0_(0)+chn_offset,   phy0_2_f1_1,100);
		__data_move( CANDS_PHY0_(128)+chn_offset, phy0_2_f1_2,100);
		__data_move( CANDS_PHY0_(256)+chn_offset, phy0_2_f1_3,100);
		__data_move( CANDS_PHY0_(384)+chn_offset, phy0_2_f1_4,100);
		__data_move( CANDS_PHY0_(512)+chn_offset, phy0_2_f1_5,38);
		__data_move( CANDS_PHY0_(640)+chn_offset, phy0_2_f1_6,38);
		__data_move( CANDS_PHY0_(768)+chn_offset, phy0_2_f1_7,38);
		__data_move( CANDS_PHY0_(896)+chn_offset, phy0_2_f1_8,38);

		REG32(CANDS_PHY0_(1024)+chn_offset) &= ~(0x1 << 0);
		REG32(CANDS_PHY0_(1024)+chn_offset) &= ~(0XFFFF << 8);
		REG32(CANDS_PHY0_(1024)+chn_offset) |= (0 << 8);

		__data_move( CANDS_PHY0_(1024)+chn_offset,phy0_1_f0  , 84);
		__data_move( CANDS_PHY0_(0)+chn_offset  , phy0_2_f0_1,100);
		__data_move( CANDS_PHY0_(128)+chn_offset, phy0_2_f0_2,100);
		__data_move( CANDS_PHY0_(256)+chn_offset, phy0_2_f0_3,100);
		__data_move( CANDS_PHY0_(384)+chn_offset, phy0_2_f0_4,100);
		__data_move( CANDS_PHY0_(512)+chn_offset, phy0_2_f0_5,38);
		__data_move( CANDS_PHY0_(640)+chn_offset, phy0_2_f0_6,38);
		__data_move( CANDS_PHY0_(768)+chn_offset, phy0_2_f0_7,38);
		__data_move( CANDS_PHY0_(896)+chn_offset, phy0_2_f0_8,38);

	}
}
void phy_restore_register(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	if(chn_num == 0)
	{
		__data_move( phy0_1_f3,CANDS_PHY0_(1024)+chn_offset, 84);
		__data_move( phy0_2_f3,CANDS_PHY0_(0)+chn_offset, 1024);
	}
	else
	{

		__data_move( phy1_1_f3,CANDS_PHY0_(1024)+chn_offset, 84);
		__data_move( phy1_2_f3_1,CANDS_PHY0_(0)+chn_offset, 100);
		__data_move( phy1_2_f3_2,CANDS_PHY0_(128)+chn_offset, 100);
		__data_move( phy1_2_f3_3,CANDS_PHY0_(256)+chn_offset, 100);
		__data_move( phy1_2_f3_4,CANDS_PHY0_(384)+chn_offset, 100);
		__data_move( phy1_2_f3_5,CANDS_PHY0_(512)+chn_offset, 38);
		__data_move( phy1_2_f3_6,CANDS_PHY0_(640)+chn_offset, 38);
		__data_move( phy1_2_f3_7,CANDS_PHY0_(768)+chn_offset, 38);
		__data_move( phy1_2_f3_8,CANDS_PHY0_(896)+chn_offset, 38);
	}
	if(chn_num == 0)
	{
		__data_move( phy0_1_f2,CANDS_PHY0_(1024)+chn_offset, 84);
		__data_move( phy0_2_f2_1,CANDS_PHY0_(0)+chn_offset, 100);
		__data_move( phy0_2_f2_2,CANDS_PHY0_(128)+chn_offset, 100);
		__data_move( phy0_2_f2_3,CANDS_PHY0_(256)+chn_offset, 100);
		__data_move( phy0_2_f2_4,CANDS_PHY0_(384)+chn_offset, 100);
		__data_move( phy0_2_f2_5,CANDS_PHY0_(512)+chn_offset, 38);
		__data_move( phy0_2_f2_6,CANDS_PHY0_(640)+chn_offset, 38);
		__data_move( phy0_2_f2_7,CANDS_PHY0_(768)+chn_offset, 38);
		__data_move( phy0_2_f2_8,CANDS_PHY0_(896)+chn_offset, 38);

		__data_move( phy0_1_f1,CANDS_PHY0_(1024)+chn_offset, 84);
		__data_move( phy0_2_f1_1,CANDS_PHY0_(0)+chn_offset, 100);
		__data_move( phy0_2_f1_2,CANDS_PHY0_(128)+chn_offset, 100);
		__data_move( phy0_2_f1_3,CANDS_PHY0_(256)+chn_offset, 100);
		__data_move( phy0_2_f1_4,CANDS_PHY0_(384)+chn_offset, 100);
		__data_move( phy0_2_f1_5,CANDS_PHY0_(512)+chn_offset, 38);
		__data_move( phy0_2_f1_6,CANDS_PHY0_(640)+chn_offset, 38);
		__data_move( phy0_2_f1_7,CANDS_PHY0_(768)+chn_offset, 38);
		__data_move( phy0_2_f1_8,CANDS_PHY0_(896)+chn_offset, 38);

		__data_move( phy0_1_f0,CANDS_PHY0_(1024)+chn_offset, 84);
		__data_move( phy0_2_f0_1,CANDS_PHY0_(0)+chn_offset, 100);
		__data_move( phy0_2_f0_2,CANDS_PHY0_(128)+chn_offset, 100);
		__data_move( phy0_2_f0_3,CANDS_PHY0_(256)+chn_offset, 100);
		__data_move( phy0_2_f0_4,CANDS_PHY0_(384)+chn_offset, 100);
		__data_move( phy0_2_f0_5,CANDS_PHY0_(512)+chn_offset, 38);
		__data_move( phy0_2_f0_6,CANDS_PHY0_(640)+chn_offset, 38);
		__data_move( phy0_2_f0_7,CANDS_PHY0_(768)+chn_offset, 38);
		__data_move( phy0_2_f0_8,CANDS_PHY0_(896)+chn_offset, 38);
	}
}

void set_for_dpslp_wkup_rst_modreg(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num ==0)?0:0x00800000;

	reg_bit_set(CANDS_CTL0_(188)+chn_offset,0,3,3);

	reg_bit_set(CANDS_CTL0_(183)+chn_offset,24,1,1);

	reg_bit_set(CANDS_CTL0_(183)+chn_offset,26,1,1);

	reg_bit_set(CANDS_CTL0_(183)+chn_offset,25,1,1);

	while((REG32(CANDS_CTL0_(292)+chn_offset)&(1<<26))!=(1<<26));
}


void pub_reinit(DDR_CHANNEL_NUM_E chn_num)
{

	uint32 ddr_access_result = 0;
	uint32 bist_result = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 i;
	/*STEP4*/
	ctl_phy_release(chn_num);// release ctl phy
	/*Initiate command processing in the controller. Set to 1 to initiate*/
	ctl0_1[0] &= ~(0x1 << 0);

	pi0_1[0] &= ~(0x1 << 0);

	/*--------------------start freq---------------*/
	#if 1
//	pub0_wakeup_freq = 3;
	if(chn_num == 0)
	{
		ctl0_1[32] &= ~(0x7 << 16);				//iwahle2 :Defines the initial DFI bus frequency.
		ctl0_1[32] |= (pub0_wakeup_freq<<16);

		ctl0_1[32] &= ~(0x7 << 24);				//iwahle2:Defines the DFI bus boot frequency.
		ctl0_1[32] |= (pub0_wakeup_freq<< 24);
	}
	else
	{
		ctl0_1[32] &= ~(0x7 << 16);				//iwahle2 :Defines the initial DFI bus frequency.
		ctl0_1[32] |= (pub1_wakeup_freq<<16);

		ctl0_1[32] &= ~(0x7 << 24);				//iwahle2:Defines the DFI bus boot frequency.
		ctl0_1[32] |= (pub1_wakeup_freq<< 24);
	}
	#endif

	#if 1
	ctl0_1[151] &= ~(0x1<<16);					// enables  power-down wakeup,
	#endif

	/*double check multicast enable/multicast index regs-----set */
	#if 1 //suwen
	phy0_1_f3[0] &=~(1<<0);
	phy0_1_f3[0] &= ~(0XFFFF << 8);
	phy0_1_f3[0] |= (3 << 8);

	phy0_1_f2[0] &=~(1<<0);
	phy0_1_f2[0] &= ~(0XFFFF << 8);
	phy0_1_f2[0] |= (2<< 8);

	phy0_1_f1[0] &=~(1<<0);
	phy0_1_f1[0] &= ~(0XFFFF << 8);
	phy0_1_f1[0] |= (1<< 8);

	phy0_1_f0[0] &=~(1<<0);
	phy0_1_f0[0] &= ~(0XFFFF << 8);
	phy0_1_f0[0] |= (0<< 8);

	//phy0_1_f3[82] |= (1 << 16);
	//phy0_1_f3[82] &=~(1 << 17);
	//phy0_1_f2[82] |= (1 << 16);
	//phy0_1_f2[82] &=~(1 << 17);
	//phy0_1_f1[82] |= (1 << 16);
	//phy0_1_f1[82] &=~(1 << 17);
	//phy0_1_f0[82] |= (1 << 16);
	//phy0_1_f0[82] &=~(1 << 17);
	#endif


	pi_restore_register(chn_num);
	ctl_restore_register(chn_num);

	phy_restore_register(chn_num);

	//reg_bit_set(0xe42c0000, 6, 1, 0);        //pub0_SRST
	//wait_us(1);


#ifndef DO_TRAINING
 	REG32(CANDS_CTL0_(32)+chn_offset) |=(0x1 << 0);		//no_phy_ind_train_init
 	REG32(CANDS_CTL0_(32)+chn_offset) &=~(0x1 << 8);	//no_phy_ind_train_init
#else
 	REG32(CANDS_PI0_(1)+chn_offset) |= (0x1 << 8);		//pi_init_lvl_en
 	REG32(CANDS_PI0_(1)+chn_offset) |= (0x1 << 0);		//pi_normal_lvl_seq
	reg_bit_set(CANDS_CTL0_(38), 0, 6, pub0_wakeup_freq);	//pi work freq
#endif

	/*STEP8*/
	REG32(CANDS_PHY0_(1050)+chn_offset) |= (1<< 10); 	    //lp4
	REG32(CANDS_CTL0_(102)+chn_offset) |=(0x1 << 16);	    //PWRUP_SREFRESH_EXIT


#ifndef FORCE_DEEP_SLEEP
	/*use for sw enter self-refresh*/
	reg_bit_set(CANDS_PHY0_(1050), 8, 4, 0x4);	        //PHY_SET_DFI_INPUT_0
	REG32(0xe42c0048) &=~(0x1 << 0);			//remove data retention
#endif

	/*Input enable mode bits for slice 0.Bit (0) enables the mode where theinput enables are always on*/
	REG32(CANDS_PHY0_(94)+chn_offset) &= ~(0x1 << 16);     	     //ie_always_on disable
	REG32(CANDS_PHY0_(94+0x200)+chn_offset) &= ~(0x1 << 16);     //ie_always_on disable
	REG32(CANDS_PHY0_(94+0x400)+chn_offset) &= ~(0x1 << 16);     //ie_always_on disable
	REG32(CANDS_PHY0_(94+0x600)+chn_offset) &= ~(0x1 << 16);     //ie_always_on disable

#ifdef RPULL
	reg_bit_set((CANDS_PHY0_(1074)+chn_offset), 29, 1, 0x1);     // phy_pad_dqs RPULL enable
#endif

        //for(i=0;i<4;i++) {
	//	reg_bit_set((CANDS_PHY0_(94)+chn_offset+i*0x200), 0, 4, 0x4); // phy_pad_ie_start
	//}

	//reg_bit_set((CANDS_PHY0_(1024)+chn_offset), 0, 1, 0x0);
	//reg_bit_set((CANDS_PHY0_(1024)+chn_offset), 8, 3, 0x3);
        //for(i=0;i<4;i++) {
	//	rddqs_latency_adjust_val = (REG32(CANDS_PHY0_(94)+chn_offset+i*0x200)>>16)&0xf-1;
	//	reg_bit_set((CANDS_PHY0_(94)+chn_offset+i*0x200), 8, 3, rddqs_latency_adjust_val);
	//}


	//REG32(CANDS_CTL0_(161)+chn_offset) |=(0x1 << 0);	//changsheng
	//REG32(CANDS_CTL0_(162)+chn_offset) |=(0x1 << 0);	//changsheng
#if 0
	REG32(CANDS_PHY0_(1093)+chn_offset) |= (1<<0);		// yu zhao
#endif

#ifdef DO_TRAINING
	//REG32(CANDS_PI0_(95)+chn_offset)  |= (0x1 << 16);		//pi_rdlvl_on_sref_exit
	//REG32(CANDS_PI0_(96)+chn_offset)  |= (0x1 << 0);		//pi_rdlvl_gate_on_sref_exit
	REG32(CANDS_PI0_(0)+chn_offset)  |= (0x1 << 0);		//yu zhao
#else
	REG32(CANDS_PI0_(0)+chn_offset)  &= ~(0x1 << 0);	//yu zhao
#endif

	reg_bit_set(CANDS_CTL0_(153), 24, 4, 0);		//LP AUTO ENTRT EN

	reg_bit_set(CANDS_PHY0_(1095), 8, 3, 5);		//PHY_CAL_CLK_SELECT_0 20-10-9:48
	 /*start init*/
	REG32(CANDS_CTL0_(0)+chn_offset)  |= (0x1 << 0);	//step9

	//wait ddr init done:The low power operation has been completed.
	while((REG32(CANDS_CTL0_(292)+chn_offset)&0x10) != 0x10);		//step10

	rx_calibration_restore(0);


	/*initial manual setup of the read dqs gate*/
#ifdef RPULL
	REG32(CANDS_PHY0_(35)+chn_offset) |= (0x1 << 24);   //rddqs_gate_init
	REG32(CANDS_PHY0_(163)+chn_offset) |= (0x1 << 24);  //rddqs_gate_init
	REG32(CANDS_PHY0_(291)+chn_offset) |= (0x1 << 24);  //rddqs_gate_init
	REG32(CANDS_PHY0_(419)+chn_offset) |= (0x1 << 24);  //rddqs_gate_init
#endif
	//reg_bit_set((CANDS_PHY0_(1074)+chn_offset), 29, 1, 0x0);     // phy_pad_dqs RPULL enable
	//reg_bit_set(CANDS_PHY0_(1026), 16, 1, 1);	    //sc_phy_mannual_update

#ifdef DO_TRAINING
	cands_do_sw_training(0);				//yu zhao
#endif

#if 0
	/*disable auto reset*/
	REG32(CANDS_PHY0_(23)+chn_offset)  |= (0x1 << 8);
	REG32(CANDS_PHY0_(151)+chn_offset) |= (0x1 << 8);
	REG32(CANDS_PHY0_(279)+chn_offset) |= (0x1 << 8);
	REG32(CANDS_PHY0_(407)+chn_offset) |= (0x1 << 8);
#endif


#ifdef DDR_TEST
	ddr_test();
#endif

	REG32(DDR0_ACC_RDY) |=(0x1<<0);

#ifdef MINICODE
	REG32(DDR0_ACC_RDY) |=(0x1<<0);
	ddr_pre_write_data();
	wait_us(100);
	ddr_access_result = check_ddr_retention_data();				//STEP10
	if(!ddr_access_result)
		while(1);
#endif
	if(ddr_access_result)
	{
		if(0 == chn_num)
			REG32(DDR0_ACC_RDY) |=(0x1<<0);
		else
			REG32(DDR1_ACC_RDY) |=(0x1<<0);

		debug_info->data_retention_pass = 1;
	}
	else
	{
		debug_info->data_retention_pass = 0;
	}

	if(chn_num)
	{

		pub0_poweron_end_time = REG32(0xe4050058);
	}
	else
	{

		pub1_poweron_end_time = REG32(0xe4050058);
	}

}

int pub0_power_on_and_reinit()
{

#ifdef FORCE_MODE
	if((REG32(PWR_STATE_DBG2) & (0x1F << 15))== (0x7 << 15))
	{
		#ifdef FORCE_DEEP_SLEEP
			/*STEP 1*/
			REG32(PUB0_SYS_SLEEP_CTRL) &= ~(0x1 << 2); // clear ddr_deep_sleep
		#else
			REG32(PD_PUB0_SYS_CFG) &= ~(0x1 << 24);
			REG32(PD_PUB0_SYS_CFG) &= ~(0x1 << 25);
		#endif
		/*STEP2*/
		REG32(PUB0_SYS_SLEEP_CTRL) |= (0x1 << 6); 		//DDR0_SLEEP_DISABLE
	}
	else
	{
		REG32(DDR0_ACC_RDY) |= (0x1 << 0);
		return 0;
	}
#endif

//	while((REG32(PD_PUB0_SYS_SHUTDOWN_MARK) & (0xF << 0)) != 0xF);//hosan-17
	/*STEP3*/
	while((REG32(PWR_STATE_DBG2) & (0x1F << 15)) != 0x0);

	//REG32(PD_PUB0_SYS_SHUTDOWN_MARK) &= ~(0xF); //hosan-17
        wait_us(10);
	pub_reinit(0);

	//REG32(DDR_SLEEP_CTRL) &= ~(0x1 << 0); 	//ddr0_umctl_eb
	//REG32(DDR_SLEEP_CTRL) &= ~(0x1 << 1); 	//ddr0_phy_eb --AUTO GATE

	REG32(PUB0_SYS_SLEEP_CTRL) &= ~(0x1 << 6);	//STEP12

	return 0;

}

void ctl_phy_reset(DDR_CHANNEL_NUM_E chn_num)
{
	if(chn_num == DDR_CHANNEL_0)
	{
		reg_bit_set(0xe42c0000, 6, 1, 1);		        //pub0_SRST
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 3, 1, 1);		//DDR0_UMCTL_SRST
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 5, 1, 1);		//DDR0_AHB_SRST
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 6, 1, 1);		//DDR0_PHY_SRST
	}
	else
	{
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 10, 1, 1);		//DDR0_UMCTL_SRST
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 12, 1, 1);		//DDR0_AHB_SRST
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 13, 1, 1);		//DDR0_PHY_SRST
	}
}

#if 1
 void ctl_phy_release(DDR_CHANNEL_NUM_E chn_num)
{
	if(chn_num == DDR_CHANNEL_0)
	{
		//clear ctl & phy & ahb reset
		reg_bit_set(0xe42c0000, 6, 1, 0);        //pub0_SRST
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 3, 1, 0);//DDR0_UMCTL_SRS
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 6, 1, 0);//DDR0_PHY_SRST
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 5, 1, 0);//DDR0_AHB_SRST
	}
	else
	{
		//clear ctl & phy & ahb reset
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 10, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 13, 1, 0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 12, 1, 0);
	}
}
#endif


void pub0_power_off()
{
	volatile uint32 i=1;
	REG32(DDR_SLEEP_CTRL) |= (0x1 << 0); 						//ddr0_umctl_eb
	REG32(DDR_SLEEP_CTRL) |= (0x1 << 1); 						//ddr0_phy_eb

	/*STEP1*/
	REG32(DDR_PHY_DATA_RET) |= (0x1 << 0); 						//ddr0_phy_retention_eb

	//REG32(PUB0_FORCE_SLEEP) |= (0x1 << 3);					//pub0_force_lightsleep  QA

#ifdef FORCE_DEEP_SLEEP
	/*STEP2*/
	REG32(PUB0_SYS_SLEEP_CTRL) &= ~(0x1 << 8);					//disable ddr0 auto deep sleep
#endif

#ifdef FORCE_DEEP_SLEEP
	/*STEP3*/
	REG32(PD_PUB0_SYS_CFG) |= (0x1 << 24);   	 			//PD_PUB0_SYS_AUTO_SHUTDOWN_EN

	/*STEP4*/
	REG32(PD_PUB0_FORCE_SLEEP) |= (0x1 <<2);  				//force deep sleep(refresh and power down
#else
	/*self-refresh with memory clock gating*/
	reg_bit_set(CANDS_CTL0_(141),0,9,0x2a);

	/*polling */
	while(((REG32(CANDS_CTL0_(292)) >> 0x5) &0x1 ) != 0x1);

	/*move io data retention*/
	REG32(0xe42c0048) |= (0x1 << 0);

	/*force pub power down*/
	REG32(PD_PUB0_SYS_CFG) &= ~(0x1 << 24);   	 			//PD_PUB0_SYS_AUTO_SHUTDOWN_EN
	REG32(PD_PUB0_SYS_CFG) |= (0x1 << 25);					//PD_PUB0_SYS_FORCE
#endif
	while((REG32(PWR_STATE_DBG2) & (0x1F << 15)) != (0x7 << 15));		//waitting until  done = 1

}


void ddr_reinit_prepare(uint32 chn_num)
{
	if(chn_num == 0)
	{
		REG32(DDR0_ACC_RDY) |= (0x1 << 0);
		//REG32(DDR0_LIGHT_ACC_RDY) |= (0x1 << 0);
		//reg_bit_set(DDR0_SLP_CFG,0,16,DDR0_SLEEP_WAIT_CNT);
		//reg_bit_set(DDR0_SLP_CFG,16,16,DDR0_PWR_DOWN_WAIT_CNT);
	        REG32(PD_PUB0_SYS_SHUTDOWN_MARK) &= ~(0xF);  	// clear status
		#ifdef FORCE_MODE
			reg_bit_set(PD_PUB0_SYS_PWR_CFG, 24, 2,0x0); //pub0 mode is force shutdown
		#else
			reg_bit_set(PD_PUB0_SYS_PWR_CFG, 24, 2,0x1); //power domain auto shut down when ap deep sleep
		#endif
	}
	else
	{
		REG32(DDR1_ACC_RDY) |= (0x1 << 0);
		//REG32(DDR1_LIGHT_ACC_RDY) |= (0x1 << 0);
		//reg_bit_set(DDR1_SLP_CFG,0,16,DDR0_SLEEP_WAIT_CNT);
		//reg_bit_set(DDR1_SLP_CFG,16,16,DDR0_PWR_DOWN_WAIT_CNT);

	       REG32(PD_PUB1_SYS_SHUTDOWN_MARK) &= ~(0xF);  	// clear status
		#ifdef FORCE_MODE
			reg_bit_set(PD_PUB1_SYS_PWR_CFG, 24, 2,0x0); //pub0 mode is force shutdown
		#else
			reg_bit_set(PD_PUB1_SYS_PWR_CFG, 24, 2,0x1); //power domain auto shut down when ap deep sleep
		#endif
	}

}



void pub0_reinit_handler(uint32 status)
{
	uint32 i=1;
	debug_info->pub0_retention_counter++;
	if(PUB_POWER_DOWN == status) 		 						/*hosan:pwoer off interrupt*/
	{
		if(debug_info->pub0_power_off)
		{
			#ifdef FORCE_MODE
//			clock_force_on(0);
			pub0_power_off();
			ctl_phy_reset(0);        					//rest phy and ctl
			#endif
		}
		debug_info->pub0_sleep_num++;
	}
	else													/*hosan:power on*/
	{
		if(debug_info->pub0_power_off)
		{
			pub0_poweron_start_time = REG32(0xe4050058);
//			clock_force_on(0);
		        //dis_lightsleep(0);  //add 12:25
			pub0_power_on_and_reinit(); 				/*hosan: power on and reinit*/
		}
		else
		{
			REG32(DDR0_ACC_RDY) |= (0x1 << 0);
		}
		debug_info->pub0_wakeup_num++;
	}
	debug_info->pub0_retention_counter--;
}

uint32 bist_cnt=0;
void DMC_Reinit(void)
{

	para_init();
//	ddr_pre_write_data();
//	ddr_reinit_prepare(0);						/*hosan:set pub0 power down auto/force mode */
//	clock_force_on(0);									/*hosan:pl0l force on*/

#ifdef RETENTION_FREQ
	pub0_wakeup_freq = 3;		//force F3 wakeup
#else
	pub0_wakeup_freq  = (REG32(CANDS_CTL0_(175)+0)>>16)&0x7;  //iwahle2
#endif

	phy_save_register(0);							//save phy register  new
	pi_save_register(0);
	ctl_save_register(0);
/*===================================================*/
	check_ddr_wr_data();
	/*aon timer*/

	bist_func_3wr(0);
	wait_us(10);
	while(1)
	{
		#if 1
		pub0_reinit_handler(0);
		__ddr_print("\r\npub0 sleep num:0x");
		ddr_print_u32_hex(REG32(0xE601A000));
        	wait_us(10);
		pub0_reinit_handler(1);
		__ddr_print("\r\npub0 wakeup num:0x");
		ddr_print_u32_hex(REG32(0xE601A004));
		wait_us(10);
		#endif

	}
}


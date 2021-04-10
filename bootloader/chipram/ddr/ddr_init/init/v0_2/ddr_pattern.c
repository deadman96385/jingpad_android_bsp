#include "ddr_init.h"
#include "../../timing/v0_2/ddr_timing.h"
#include <asm/arch/clk_para_config.h>

#define PHY_DS_CLOSE			0
#define BIST_START_ADDRESS		0
#define BIST_LEN					0x3fffff

extern const MCU_CLK_PARA_T mcu_clk_para;

void bist_pattern_run(void)
{
	uint32 bist_timeout=0;

	REG32(0xc0018028) =0x2a;

	while(1)
	{
		REG32(0xc00d0000) =0x30021a1;			//all write
		REG32(0xc00d0004) =BIST_LEN;
		REG32(0xc00d0008) =BIST_START_ADDRESS;
		REG32(0xc00d000c) =0x0;
		REG32(0xc00d0010) =0;//mcu_clk_para.bist_sipi_data_00;
		REG32(0xc00d0014) =0;//mcu_clk_para.bist_sipi_data_01;
		REG32(0xc00d0018) =0;//mcu_clk_para.bist_sipi_data_02;
		REG32(0xc00d001c) =0;//mcu_clk_para.bist_sipi_data_03;
		REG32(0xc00d0020) =0;//mcu_clk_para.bist_sipi_data_04;
		REG32(0xc00d0024) =0;//mcu_clk_para.bist_sipi_data_05;
		REG32(0xc00d0028) =0;//mcu_clk_para.bist_sipi_bit_pattern_0;
		REG32(0xc00d002c) =0;//mcu_clk_para.bist_sipi_bit_pattern_1;

		REG32(0xc00d0008) =BIST_START_ADDRESS;
		REG32(0xc00d0004) =BIST_LEN;
		REG32(0xc00d0000) =0x30021b5;
		REG32(0xc00d0000) =0x30021b3;

		while((REG32(0xc00d00b0) & 0x3) != 0x2);
	}

}

uint32 switch_timing_pattern_test_case(void)
{
	switch(0)//mcu_clk_para.test_case
	{
		case 0:	return 0;
		case 1:	return 1;
		case 2:	return 2;
		case 3:	return 3;
		default:	return 0;
	}
}

//extern uint32 switch_timing_pattern_test_case(void);
//extern void bist_pattern_run(void);
void timing_buget_test(void)
{
	uint32 i;

	switch(switch_timing_pattern_test_case())
	{
		case 0:		//no bist, no output, disable ds except clk
					//phy_pad_addr_drive - ddr202
					reg_bit_set(CANDS_PHY0_(1075),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1075),0,4,PHY_DS_CLOSE); 		//drive strength

					//phy_pad_cke_drive - ddr202
					reg_bit_set(CANDS_PHY0_(1082),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1082),0,4,PHY_DS_CLOSE); 		//drive strength

					//phy_pad_cs_drive   - ddr202
					reg_bit_set(CANDS_PHY0_(1086),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1086),0,4,PHY_DS_CLOSE); 		//drive strength

					//phy_pad_fdbk_drive - ddr202
					reg_bit_set(CANDS_PHY0_(1073),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1073),0,4,PHY_DS_CLOSE); 		//drive strength

					//phy_pad_rst_drive  - ddr202
					reg_bit_set(CANDS_PHY0_(1084),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1084),0,4,PHY_DS_CLOSE); 		//drive strength

					for(i=0;i<4;i++)
					{
					//phy_dq_tsel_select
					reg_bit_set(CANDS_PHY0_(6)+(i*0x200),0,24,(PHY_DS_CLOSE<<20) |(PHY_DS_CLOSE<<16)|
	                                                        (PHY_DS_CLOSE<<12)   |(PHY_DS_CLOSE<<8)    |
	                                                        (PHY_DS_CLOSE<<4)  |(PHY_DS_CLOSE) );
					//phy_dqs_tsel_select
					reg_bit_set(CANDS_PHY0_(7)+(i*0x200),0,24,(PHY_DS_CLOSE<<20) |(PHY_DS_CLOSE<<16)|
	                                                        (PHY_DS_CLOSE<<12)   |(PHY_DS_CLOSE<<8)    |
	                                                        (PHY_DS_CLOSE<<4)  |(PHY_DS_CLOSE) );
					}
					break;

		case 1:		//enable bist, io no output
					//phy_pad_clk_drive  - ddr203
					//reg_bit_set(CANDS_PHY0_(1076),4,4,PHY_DS_CLOSE); 		//drive strength
					//reg_bit_set(CANDS_PHY0_(1076),0,4,PHY_DS_CLOSE); 		//drive strength
					//phy_pad_addr_drive - ddr202
					reg_bit_set(CANDS_PHY0_(1075),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1075),0,4,PHY_DS_CLOSE); 		//drive strength

					//phy_pad_cke_drive - ddr202
					reg_bit_set(CANDS_PHY0_(1082),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1082),0,4,PHY_DS_CLOSE); 		//drive strength

					//phy_pad_cs_drive   - ddr202
					reg_bit_set(CANDS_PHY0_(1086),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1086),0,4,PHY_DS_CLOSE); 		//drive strength

					//phy_pad_fdbk_drive - ddr202
					reg_bit_set(CANDS_PHY0_(1073),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1073),0,4,PHY_DS_CLOSE); 		//drive strength

					//phy_pad_rst_drive  - ddr202
					reg_bit_set(CANDS_PHY0_(1084),4,4,PHY_DS_CLOSE); 		//drive strength
					reg_bit_set(CANDS_PHY0_(1084),0,4,PHY_DS_CLOSE); 		//drive strength

					for(i=0;i<4;i++)
					{
					//phy_dq_tsel_select
					reg_bit_set(CANDS_PHY0_(6)+(i*0x200),0,24,(PHY_DS_CLOSE<<20) |(PHY_DS_CLOSE<<16)|
	                                                        (PHY_DS_CLOSE<<12)   |(PHY_DS_CLOSE<<8)    |
	                                                        (PHY_DS_CLOSE<<4)  |(PHY_DS_CLOSE) );
					//phy_dqs_tsel_select
					reg_bit_set(CANDS_PHY0_(7)+(i*0x200),0,24,(PHY_DS_CLOSE<<20) |(PHY_DS_CLOSE<<16)|
	                                                        (PHY_DS_CLOSE<<12)   |(PHY_DS_CLOSE<<8)    |
	                                                        (PHY_DS_CLOSE<<4)  |(PHY_DS_CLOSE) );
					}

					bist_pattern_run();
					break;

		case 2:		//enable bist with io output
					bist_pattern_run();
					break;

		default:		break;
	}

	while(1);
}

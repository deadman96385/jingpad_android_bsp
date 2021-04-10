#include <sci_types.h>
#include "ddrc_r1p0.h"
#include "ddrc_r1p0_phy.h"
#include "ddrc_r1p0_common.h"

#define BIST_EN

#define BIST_BASE_ADDR		0x30080000
#define BIST_PORT_ADDR		0x300f004c

#define USER_PATT 0
#define SIPI_PATT 1
#define LFSR_PATT 2

#define DWORD 0
#define BYTE  1
#define HWORD 2
#define WORD  3

#define BIST_WRITE  0
#define BIST_READ   1
#define BIST_ALLWRC 2
#define BIST_ONEWRC 3

#define DDR_CHN0 0
#define DDR_CHN1 1

#define BIST_NUM_0 0
#define BIST_NUM_1 1
#define BIST_NUM_2 2
#define BIST_NUM_3 3



#define NORMAL_MODE	0
#define CYCLE_MODE	1

typedef struct __SHARKL3_BIST_INFO{
	u32 bist_num;
	u32 bist_addr[4];
	u32 bist_len;
	u32 bist_mode;
	u32 bist_bwtest_mode;
	u32 bist_pattern;
} SHARKL3_BIST_INFO;

enum BIST_MASTER_CH0{
    DPU_CH_EN = 2,
    CPU_CH_EN = 3
};
enum BIST_MASTER_CH1{
    MM_CH_EN = 0,
    GPU_CH_EN = 1,
    VSP_CH_EN = 7
};
enum BIST_MASTER_CH2{
    AP_PUBCP_CH_EN = 4,
    WTLCP_CH_EN = 5
};

enum BIST_MASTER_CH3{
	AON_WCN_CH_EN = 6
};

#define BIST_MASTER_CH0_EN 1
#define BIST_MASTER_CH1_EN 1
#define BIST_MASTER_CH2_EN 1
#define BIST_MASTER_CH3_EN 1

uint32 user_mode_pattern[] = {
#if (defined DDR_REINIT_TEST)
				0xA55Aaa55,
				0xFFFFaa55,
				0x1111AA55,
				0xAAAAAA55,
				0x12345678,
				0x00000055,
				0x1111AA55,
				0xAAAAAA55,
				0x12345678,
				0x00000055,
				0x1111AA55,
				0xAAAAAA55,
				0x12345678,
				0x00000055,
				0x1111AA55,
				0xAAAAAA55,
				0x1111AA55,
				0xAAAAAA55,
				0x12345678,
				0x00000055,
				0xA55AAA55,
				0xFFFFAA55,
				0x1111AA55,
				0xAAAAAA55,
				0x12345678,
				0x00000055,
				0x1111AA55,
				0xAAAAAA55,
				0x12345678,
				0x00000055,
				0x1111AA55,
				0xAAAAAA55
#endif
};

uint32 sipi_mode_pattern[] = {
				0xa55aaa55,//bist sipi data 0
				0xffffaa55,//bist sipi data 1
				0x1111aa55,//bist sipi data 2
				0xaaaaaa55,//bist sipi data 3
				0x12345678,//bist sipi data 4
				0x00000055//bist sipi data 5
				};

uint32 lfsr_mode_pattern[] = {
				0x12345678,
				0x89abcdef,
				0x8abce529,
				0xfbed20ec};

void bist_en(uint32 bist_num, uint32 port_num)
{
    uint32 enable_bit_set = 0;
    /*step 1. disable ddr axi chn lp*/
    reg_bits_set(REG_PUB_DDR_CHN_SLEEP_CTRL0, 16, 8, 0x0);

    /*enable pub bist axi clock and reg clock*/
    reg_bits_set(BIST_PORT_ADDR, 16, 2, 0x3);

    /*step 3. bist_mux_0/1 setting [0000]=bist chn0,[0001]=bist chn1,[]*/
    reg_bits_set(BIST_PORT_ADDR, 0, 4, 0);
    /*enable pub0 portx bist module*/
	switch (port_num)
	{
		case 0:
			REG32(BIST_PORT_ADDR) |= (0x1 << 4);
			break;
		case 1:
			REG32(BIST_PORT_ADDR) |= (0x1 << 5);
			break;
		case 2:
			REG32(BIST_PORT_ADDR) |= (0x1 << 6);
			break;
		case 3:
			REG32(BIST_PORT_ADDR) |= (0x1 << 7);
			break;
		case 4:
			REG32(BIST_PORT_ADDR) |= (0x1 << 8);
			break;
		case 5:
			REG32(BIST_PORT_ADDR) |= (0x1 << 9);
			break;
		case 6:
			REG32(BIST_PORT_ADDR) |= (0x1 << 10);
			break;
		case 7:
			REG32(BIST_PORT_ADDR) |= (0x1 << 11);
			break;
		default:
			break;

	}
}

void bist_dis(void)
{
    /*step 1. enable ddr axi chn lp*/
    reg_bits_set(REG_PUB_DDR_CHN_SLEEP_CTRL0, 16, 8, 0xff);

    //disable pub0 CA53 port bist module
    REG32(BIST_PORT_ADDR) = 0x0;
}

void bist_clear( uint32 bist_num)
{
	volatile uint32 val = 0;
	volatile uint32 offset = (bist_num*0x4000);

	//bit[1] bist start bit[2] bist clear
	reg_bits_set((BIST_BASE_ADDR + offset), 1, 2, 0x2);
}

void bist_trigger(uint32 bist_num)
{
	volatile uint32 offset = (bist_num*0x4000);
	//bit[1] bist start bit[2] bist clear
	reg_bits_set((BIST_BASE_ADDR + offset), 1, 2, 0x1);
}

void bist_wait_done(uint32 bist_num)
{
	volatile uint32 offset = (bist_num*0x4000);

	//wait bist done
	while((REG32((BIST_BASE_ADDR + 0xB0) + offset) & 0X2) != 0X2);
}

uint32 get_bist_result(uint32 bist_num)
{
	volatile uint32 val = 0;
	volatile uint32 offset = (bist_num*0x4000);

	//wait bist done
	while((REG32((BIST_BASE_ADDR + 0xB0) + offset)&0X2) != 0X2);

	if( (REG32((BIST_BASE_ADDR + 0xB0) + offset)&0X1) == 0x0 )
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void sipi_bit_pattern_sel(uint32 bist_num,uint32 pat_num)
{
	volatile uint32 i =0;
	volatile uint32 offset = (bist_num*0x4000);
	switch(pat_num)
	{
		case 0:
			REG32(BIST_BASE_ADDR+0x28+offset)=0xfffffff4;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0xffffffff;
			break;
		case 1:
			REG32(BIST_BASE_ADDR+0x28+offset)=0x01234567;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x89abcdef;
			break;
		case 2:
			REG32(BIST_BASE_ADDR+0x28+offset)=0xfedcba98;
			REG32(BIST_BASE_ADDR+0x2c+offset)=0x76543210;
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


void bist_set(uint32 bist_num,uint32 write_or_read,uint32 bist_patt, uint32 bist_mode,uint32 bist_len,uint32 bist_src)
{
	volatile uint32 i = 0;
	volatile uint32 val = 0;
	volatile uint32 offset = (bist_num * 0x4000);

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
	if(BIST_NUM_2 == bist_num)
	{
		val |= (3<<11); //0:byte  1:halfword  2:word  3:two word 4:four word
	}
	else
	{
		val |= (4<<11); //0:byte  1:halfword  2:word  3:two word 4:four word
	}
	val |= (bist_mode<<14); //0:normal bist mode  1:bist will not stop util bist_start is low
	val |= (0<<15); //the delay clk cycle between the two axi command
	val |= (3<<24); //bist write/read outstanding enable
	//val |= (1<<28); //data width mode

	REG32((BIST_BASE_ADDR + 0x00) + offset) = val;

	//set trans num
	//-2 fix bug for burst mode, end flag 0x3f bist return pass but not pass
	REG32((BIST_BASE_ADDR + 0x04) +offset) = (bist_len>>8) - 2;

	//set start address
	REG32((BIST_BASE_ADDR + 0x08) +offset) = bist_src;

	if(bist_patt==USER_PATT)
	{
		//set bist data pattern
		for(i = 0; i < 32; i++)
		{
			REG32((BIST_BASE_ADDR + 0x30 + i*4) + offset) = user_mode_pattern[i];
		}
	}
	if(bist_patt==SIPI_PATT)
	{
		//set sipi data pattern
		REG32((BIST_BASE_ADDR + 0x10) + offset) = sipi_mode_pattern[0];
		REG32((BIST_BASE_ADDR + 0x14) + offset) = sipi_mode_pattern[1];
		REG32((BIST_BASE_ADDR + 0x18) + offset) = sipi_mode_pattern[2];
		REG32((BIST_BASE_ADDR + 0x1C) + offset) = sipi_mode_pattern[3];
		REG32((BIST_BASE_ADDR + 0x20) + offset) = sipi_mode_pattern[4];
		REG32((BIST_BASE_ADDR + 0x24) + offset) = sipi_mode_pattern[5];
		sipi_bit_pattern_sel(bist_num, 1);
	}
	if(bist_patt==LFSR_PATT)
	{
		REG32((BIST_BASE_ADDR +0xcc) +offset) = lfsr_mode_pattern[0];
		REG32((BIST_BASE_ADDR +0xd0) +offset) = lfsr_mode_pattern[1];
		REG32((BIST_BASE_ADDR +0xd4) +offset) = lfsr_mode_pattern[2];
		REG32((BIST_BASE_ADDR +0xd8) +offset) = lfsr_mode_pattern[3];
	}
}

uint32 bist_test(SHARKL3_BIST_INFO *bist_info)
{
	volatile uint32 bist_result = 0;

	bist_en(BIST_NUM_1 , CPU_CH_EN);
	//bist_en(BIST_NUM_1 , MM_CH_EN);
	//bist_en(BIST_NUM_2 , CPU_CH_EN);
	//bist_en(BIST_NUM_3 , CPU_CH_EN);

	bist_clear(BIST_NUM_0);
	//bist_clear(BIST_NUM_1);
	//bist_clear(BIST_NUM_2);
	//bist_clear(BIST_NUM_3);

	bist_set(BIST_NUM_0,bist_info->bist_mode,bist_info->bist_pattern,bist_info->bist_bwtest_mode,bist_info->bist_len, bist_info->bist_addr[0]);
	//bist_set(BIST_NUM_1,bist_info->bist_mode,bist_info->bist_pattern,bist_info->bist_bwtest_mode,bist_info->bist_len, bist_info->bist_addr[1]);
	//bist_set(BIST_NUM_2,bist_info->bist_mode,bist_info->bist_pattern,bist_info->bist_bwtest_mode,bist_info->bist_len, bist_info->bist_addr[2]);
	//bist_set(BIST_NUM_3,bist_info->bist_mode,bist_info->bist_pattern,bist_info->bist_bwtest_mode,bist_info->bist_len, bist_info->bist_addr[3]);

	bist_trigger(BIST_NUM_0);
	//bist_trigger(BIST_NUM_1);
	//bist_trigger(BIST_NUM_2);
	//bist_trigger(BIST_NUM_3);


	bist_wait_done(BIST_NUM_0);
	//bist_wait_done(BIST_NUM_1);
	//bist_wait_done(BIST_NUM_2);
	//bist_wait_done(BIST_NUM_3);

	bist_result += get_bist_result(BIST_NUM_0);
	//bist_result += get_bist_result(BIST_NUM_1);
	//bist_result += get_bist_result(BIST_NUM_2);
	//bist_result += get_bist_result(BIST_NUM_3);

	if(bist_result >0)
	{
#ifndef DDR_SCAN_ENABLE
		dmc_print_str("\r bist test is fail\n");
		bist_dis();
		while(1);
#endif
	}else
	{
#ifndef DDR_SCAN_ENABLE
		dmc_print_str("\r bist test is ok \n");
#endif
	}

	bist_clear(BIST_NUM_0);
	//bist_clear(BIST_NUM_1);
	//bist_clear(BIST_NUM_2);
	//bist_clear(BIST_NUM_3);

	bist_dis();

	return bist_result;
}

uint32 bist_result_out=0;
uint32 bist_fail_num[8]={0};
SHARKL3_BIST_INFO bist_info;
#ifndef DDR_SCAN_ENABLE
void dmc_ddr_test(u32 bist_num)
{
	volatile uint32 i=0;
	uint32 test_num=0;
	uint64 chip_size;

	sdram_chip_whole_size(&chip_size);
	bist_info.bist_num  = bist_num;
	bist_info.bist_len = BIST_RESERVE_SIZE;
	bist_info.bist_addr[0] = chip_size - BIST_RESERVE_SIZE;
	bist_info.bist_addr[1] = 0x1000000;
	bist_info.bist_addr[2] = 0x2000000;
	bist_info.bist_addr[3] = 0x3000000;
	bist_info.bist_mode = BIST_ALLWRC;
	bist_info.bist_pattern = SIPI_PATT;
	bist_info.bist_bwtest_mode = NORMAL_MODE;
	//for(i=0;i<10;i++)
	{
		bist_fail_num[bist_num]+=bist_test(&bist_info);
		test_num++;
	}
}
#else
int dmc_ddr_test(u32 bist_num, u32 pattern, u32 addr)
{
        volatile uint32 i=0;
        uint32 test_num=0;
        uint64 chip_size;

        sdram_chip_whole_size(&chip_size);
        bist_info.bist_num  = bist_num;
        bist_info.bist_len = BIST_RESERVE_SIZE;
        bist_info.bist_addr[0] = addr;
        bist_info.bist_addr[1] = 0x1000000;
        bist_info.bist_addr[2] = 0x2000000;
        bist_info.bist_addr[3] = 0x3000000;
        bist_info.bist_mode = BIST_ALLWRC;
        bist_info.bist_pattern = pattern;
        bist_info.bist_bwtest_mode = NORMAL_MODE;
        //for(i=0;i<10;i++)
        {      bist_fail_num[bist_num]=0;
                bist_fail_num[bist_num]=bist_test(&bist_info);
                test_num++;
        }
		if(bist_fail_num[bist_num] >0)
			return 1;
		else
			return 0;
}
#endif
#if (defined DDR_REINIT_TEST)
int dmc_ddr_write(u32 bist_num)
{
	volatile uint32 i=0;
	uint32 test_num=0;
	//uint32 bist_len;
	//bist_len = 0x20000;
	bist_info.bist_num  = bist_num;
	bist_info.bist_len = 0x30000000;
	bist_info.bist_addr[0] = 0x0;
	bist_info.bist_addr[1] = 0x0000000;
	bist_info.bist_addr[2] = 0x2000000;
	bist_info.bist_addr[3] = 0x3000000;
	bist_info.bist_mode = BIST_WRITE;
	bist_info.bist_pattern = USER_PATT;
	bist_info.bist_bwtest_mode = NORMAL_MODE;
	//for(i=0;i<10;i++)
	{
		bist_fail_num[bist_num]+=bist_test(&bist_info);
		test_num++;
	}
        if(bist_fail_num[bist_num])
        {
            dmc_print_str("\r\nbist write fail\n");
        }else
        {
            dmc_print_str("\r\nbist write pass\n");
        }
}

int dmc_ddr_read(u32 bist_num)
{
	volatile uint32 i=0;
	uint32 test_num=0;
	//uint32 bist_len;
	//bist_len = 0x20000;
	bist_info.bist_num  = bist_num;
	bist_info.bist_len = 0x30000000;
	bist_info.bist_addr[0] = 0x0;
	bist_info.bist_addr[1] = 0x0000000;
	bist_info.bist_addr[2] = 0x2000000;
	bist_info.bist_addr[3] = 0x3000000;
	bist_info.bist_mode = BIST_READ;
	bist_info.bist_pattern = USER_PATT;
	bist_info.bist_bwtest_mode = NORMAL_MODE;
	//for(i=0;i<10;i++)
	{
		bist_fail_num[bist_num]+=bist_test(&bist_info);
		test_num++;
	}
        if(bist_fail_num[bist_num])
        {
            dmc_print_str("\r\nbist read fail\n");
        }else
        {
            dmc_print_str("\r\nbist read pass\n");
        }
}
#endif

#if (defined POWER_TEST)
uint32 bist_test_start(SHARKL3_BIST_INFO *bist_info)
{
	volatile uint32 bist_result = 0;

	bist_en(BIST_NUM_0 , CPU_CH_EN);
	bist_en(BIST_NUM_1 , MM_CH_EN);
	bist_en(BIST_NUM_2 , AP_PUBCP_CH_EN);
	bist_en(BIST_NUM_3 , AON_WCN_CH_EN);

	bist_clear(BIST_NUM_0);
	bist_clear(BIST_NUM_1);
	bist_clear(BIST_NUM_2);
	bist_clear(BIST_NUM_3);

	bist_set(BIST_NUM_0,bist_info->bist_mode,bist_info->bist_pattern,bist_info->bist_bwtest_mode,bist_info->bist_len, bist_info->bist_addr[0]);
	bist_set(BIST_NUM_1,bist_info->bist_mode,bist_info->bist_pattern,bist_info->bist_bwtest_mode,bist_info->bist_len, bist_info->bist_addr[1]);
	bist_set(BIST_NUM_2,bist_info->bist_mode,bist_info->bist_pattern,bist_info->bist_bwtest_mode,bist_info->bist_len, bist_info->bist_addr[2]);
	bist_set(BIST_NUM_3,bist_info->bist_mode,bist_info->bist_pattern,bist_info->bist_bwtest_mode,bist_info->bist_len, bist_info->bist_addr[3]);

	bist_trigger(BIST_NUM_0);
	bist_trigger(BIST_NUM_1);
	bist_trigger(BIST_NUM_2);
	bist_trigger(BIST_NUM_3);
}

int dmc_ddr_read_start(u32 bist_num)
{
	volatile uint32 i=0;
	uint32 test_num=0;
	//uint32 bist_len;
	//bist_len = 0x20000;
	bist_info.bist_num  = bist_num;
	bist_info.bist_len = 0x30000000;
	bist_info.bist_addr[0] = 0x0;
	bist_info.bist_addr[1] = 0x0000000;
	bist_info.bist_addr[2] = 0x2000000;
	bist_info.bist_addr[3] = 0x3000000;
	bist_info.bist_mode = BIST_READ;
	bist_info.bist_pattern = USER_PATT;
	bist_info.bist_bwtest_mode = NORMAL_MODE;
	//for(i=0;i<10;i++)
	{
		bist_test_start(&bist_info);
		test_num++;
	}
}

void  ddr_bist_read_entry()
{
    	volatile uint32 i=0;
	uint32 test_num=0;
	//uint32 bist_len;
	//bist_len = 0x20000;
	bist_info.bist_num  = BIST_NUM_0;
	bist_info.bist_len = 0x20000000;
	bist_info.bist_addr[0] = 0x0;
	bist_info.bist_addr[1] = bist_info.bist_addr[0] + bist_info.bist_len;
	bist_info.bist_addr[2] = bist_info.bist_addr[1] + bist_info.bist_len;
	bist_info.bist_addr[3] = bist_info.bist_addr[2] + bist_info.bist_len;
	bist_info.bist_mode = BIST_READ;
	bist_info.bist_pattern = SIPI_PATT;
	bist_info.bist_bwtest_mode = CYCLE_MODE;

	bist_test_start(&bist_info);
}
void  ddr_bist_write_entry()
{
     	volatile uint32 i=0;
	uint32 test_num=0;
	//uint32 bist_len;
	//bist_len = 0x20000;
	bist_info.bist_num  = BIST_NUM_0;
	bist_info.bist_len = 0x20000000;
	bist_info.bist_addr[0] = 0x0;
	bist_info.bist_addr[1] = bist_info.bist_addr[0] + bist_info.bist_len;
	bist_info.bist_addr[2] = bist_info.bist_addr[1] + bist_info.bist_len;
	bist_info.bist_addr[3] = bist_info.bist_addr[2] + bist_info.bist_len;
	bist_info.bist_mode = BIST_WRITE;
	bist_info.bist_pattern = SIPI_PATT;
	bist_info.bist_bwtest_mode = CYCLE_MODE;

	bist_test_start(&bist_info);
}
void bist_test_stop()
{
    bist_clear(BIST_NUM_0);
    bist_clear(BIST_NUM_1);
    bist_clear(BIST_NUM_2);
    bist_clear(BIST_NUM_3);

    bist_dis();
}

void  ddr_bist_read_exit()
{
    bist_test_stop();
}
void  ddr_bist_write_exit()
{
    bist_test_stop();
}
#endif

int ddrc_bist_test(u32 start, u32 end)
{
	return 0;
	if (end < start)
		return 1;
        bist_info.bist_num  = 0;
        bist_info.bist_len = end - start;
        bist_info.bist_addr[0] = start;
        bist_info.bist_mode = BIST_ALLWRC;
        bist_info.bist_pattern = SIPI_PATT;
        bist_info.bist_bwtest_mode = NORMAL_MODE;
        if(bist_test(&bist_info))
		return 1;
	else
		return 0;

}


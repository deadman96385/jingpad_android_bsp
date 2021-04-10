#include <sci_types.h>
#include <asm/arch/clk_para_config.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>
#include "ddrc_r1p0.h"
#include "ddr_test.h"
extern DRAM_CHIP_INFO ddr_chip_cur;

#ifdef MEM_DEBUG
void ddr_mem_test(void)
{
	int i;
	unsigned int regval;

	for (i = 0; i < MEM_TEST_LEN; i+=4)
	{
		REG32(SOURCE_ADDR + i) = SOURCE_ADDR + i;
		REG32(DST_ADDR + i) = SOURCE_ADDR + i;
	}

	while(1)
	{
		memset((void*)DST_ADDR, 0x0, MEM_TEST_LEN);
		for ( i = 0; i < MEM_TEST_LEN; i+= 1024)
		{
			sprd_memcpy((void*)(DST_ADDR + i), (void*)(SOURCE_ADDR + i), 1024);
			regval = sprd_memcmp((void*)(SOURCE_ADDR + i), (void*)(DST_ADDR + i),1024);
			if (regval)
			{
				dmc_print_str("little ddr copy failed\n");
				while(1);
			}
			else
			{
				//dmc_print_str("ddr copy pass\n");
			}
		}

		regval = sprd_memcmp((void*)(SOURCE_ADDR), (void*)(DST_ADDR),MEM_TEST_LEN);
		if (regval)
		{
			dmc_print_str("big ddr cmp failed\n");
			while(1);
		}
		else
		{
			dmc_print_str("big mem cmp pass\n");
		}
	}
}
#else
void ddr_mem_test(void)
{
	;
}
#endif
#ifdef CONFIG_FDL1
int ddr_scan_fdl1_test(int start, int end)
{
	int ret;

	dmc_print_str("bist scan start\r\n");

	if(start <= ddr_chip_cur.cs0_jedec_info->cs_size) {
		ret = ddrc_bist_test(0,start);
		if(ret != 0)
			return -1;
	} else {
		ret = ddrc_bist_test(0,ddr_chip_cur.cs0_jedec_info->cs_size);
		if(ret != 0)
			return -1;
		ret = ddrc_bist_test(ddr_chip_cur.cs0_jedec_info->cs_size, start);
		if(ret != 0)
			return -1;
	}

	if(end >= ddr_chip_cur.cs0_jedec_info->cs_size) {
		if(ddr_chip_cur.cs_num == 2) {
			ret = ddrc_bist_test(end, 0);
			if(ret != 0)
				return -1;
		}
	} else {
		ret = ddrc_bist_test(end,ddr_chip_cur.cs0_jedec_info->cs_size);
		if(ret != 0)
			return -1;
		if(ddr_chip_cur.cs_num == 2) {
			ret = ddrc_bist_test(ddr_chip_cur.cs0_jedec_info->cs_size, ddr_chip_cur.cs0_jedec_info->cs_size + ddr_chip_cur.cs1_jedec_info->cs_size);
			if(ret != 0)
				return -1;
		}
	}
	dmc_print_str("bist scan end\r\n");
	return 0;
}

#ifdef MEM_TEST
void ddr_write_read_test(void)
{
	u64 cs_size;
	u32 i, count;
	char  log_string[32];
	sdram_chip_whole_size(&cs_size);
	for(i = 0; i < cs_size ; i += 0x4)
	{
		*(volatile u32*)(DDR_START_ADDR_PHY + i) = DDR_START_ADDR_PHY + i;
	}
#ifdef SR_TEST
	count = 1;
	while(1)
	{
		if(count > (1<<10))
			break;
		dmc_print_str("self refresh wait begin...\r\n");
		dmc_sprd_delay(500000*count);
		count *= 2;
		dmc_print_str("count:");
		dmc_print_str(itoa_simple(count, log_string, 16));
		dmc_print_str("\r\n");
		dmc_print_str("self refresh wait end, data check\r\n");
#endif
		for(i = 0; i < cs_size; i += 0x4)
		{
			if(*(volatile u32*)(DDR_START_ADDR_PHY + i) != (DDR_START_ADDR_PHY + i))
			{
				while(1)
				{
					dmc_print_str("address:");
					dmc_print_str(itoa_simple((DDR_START_ADDR_PHY + i + 1), log_string, 16));
					dmc_print_str("data:");
					dmc_print_str(itoa_simple(*(volatile u32*)(DDR_START_ADDR_PHY + i), log_string, 16));
					dmc_print_str("\r\n");
					dmc_print_str("ddr write read test fail\r\n");
					dmc_sprd_delay(2000000);
				}
			}
		}
#ifdef SR_TEST
	}
#endif
}
#endif

struct sr_address{
u32 sr_start;
u32 sr_end;
};

#define TEST_RESERVE_START_INDEX0 (DDR_START_ADDR_PHY + 0x5F0000)
#define TEST_RESERVE_END_INDEX0 (DDR_START_ADDR_PHY + 0x8F0000)
//SPL_DDR_STACK      0x808f0000
#define TEST_RESERVE_START_INDEX1 (DDR_START_ADDR_PHY + 0x2000000)
#define TEST_RESERVE_END_INDEX1 (DDR_START_ADDR_PHY + 0x2100000)
//CHIPRAM_ENV_ADDR	0x82000000
#define TEST_RESERVE_START_INDEX2 (DDR_START_ADDR_PHY + 0x7003000)
#define TEST_RESERVE_END_INDEX2 (DDR_START_ADDR_PHY + 0x7103000)
//SPRD_EVM_TAG 0x87003004

//INDEX4 BIST_RESERVE_SIZE


#define TEST_PATTERN 0x12345678
//cs0 at least 128M,then can test cs1

int ddr_selfrefresh_test(u32 timeout)
{
	u64 cs_size;
	u32 i,j,count,sr_length;
	volatile u32 * start_base,* cs1_base;
	char  log_string[32];
	struct sr_address sr_add[]={
		{TEST_RESERVE_START_INDEX0,TEST_RESERVE_END_INDEX0},
		{TEST_RESERVE_START_INDEX1,TEST_RESERVE_END_INDEX1},
		{TEST_RESERVE_START_INDEX2,TEST_RESERVE_END_INDEX2},
		{0,0}
	};
	count = sizeof(sr_add)/sizeof(sr_add[0]);

	sdram_chip_whole_size(&cs_size);

	sr_add[count-1].sr_start = DDR_START_ADDR_PHY + (u32)cs_size - BIST_RESERVE_SIZE;
	sr_add[count-1].sr_end = DDR_START_ADDR_PHY + (u32)cs_size;

	start_base = DDR_START_ADDR_PHY;


	dmc_print_str("sr start\r\n");
	for(i = 0; i < count ; i++)
	{
		sr_length = sr_add[i].sr_start - (u32)start_base;

		for(j = 0; j < sr_length/4 ; j++)
		{
			*(start_base + j) = TEST_PATTERN;
		}
		dmc_print_str(itoa_simple((u32)start_base), log_string, 16);
		dmc_print_str(itoa_simple(((u32)start_base+sr_length)), log_string, 16);
		start_base = (volatile u32 *)sr_add[i].sr_end;
	}

	//timeout s
	dmc_sprd_delay(timeout);

	dmc_print_str("\r\n wait end, data check\r\n");

	start_base = DDR_START_ADDR_PHY;
	for(i = 0; i < count ; i++)
	{

		sr_length = sr_add[i].sr_start - (u32)start_base;

		for(j = 0; j < sr_length/4; j++)
		{
			if(*(start_base + j) != TEST_PATTERN)
			{
				dmc_print_str("sr test fail\r\n");
				return -1;
			}
		}
		dmc_print_str(itoa_simple((u32)start_base), log_string, 16);
		dmc_print_str(itoa_simple(((u32)start_base+sr_length)), log_string, 16);
		start_base = (volatile u32 *)sr_add[i].sr_end;
	}
	dmc_print_str("\r\n sr test pass\r\n");
	return 0;

}
#endif

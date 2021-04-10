#include "ddr_master_test.h"
#include <asm/types.h>
#include <common.h>

#include "dmc_sprd_r3p0_bist.h"
#include "dmc_sprd_r3p0.h"
static uint32 seed;
static uint32 result=0;
static uint32 locked =1;
void SetSeed(uint32 s)
{
    if(s == 0)
		seed = -1;
	else
		seed = s;
}

uint32 GetRandom()
{
    uint32 d;

	d=((seed >> 3)^seed)&0x1ffffffe;
	seed=(seed>>29)|d<<2;
	d=((seed>>3)^seed)&0xf;
	seed>>=3;
	seed|=d<<28;

	return seed;
}

uint32 test_error = 0;
#if 0
void test_walking_zero_seq(void)
{
	uint32 i;

	//case1 walking zero
    for(i=0;i<TEST_LEN;i+=0x80)
    {
		REG32(TEST_BASE_ADDR_1+ (i+0x0)) = 0xffffffff ^ (1<<0);
		REG32(TEST_BASE_ADDR_1+ (i+0x4)) = 0xffffffff ^ (1<<1);
		REG32(TEST_BASE_ADDR_1+ (i+0x8)) = 0xffffffff ^ (1<<2);
		REG32(TEST_BASE_ADDR_1+ (i+0xc)) = 0xffffffff ^ (1<<3);
		REG32(TEST_BASE_ADDR_1+ (i+0x10)) = 0xffffffff ^ (1<<4);
		REG32(TEST_BASE_ADDR_1+ (i+0x14)) = 0xffffffff ^ (1<<5);
		REG32(TEST_BASE_ADDR_1+ (i+0x18)) = 0xffffffff ^ (1<<6);
		REG32(TEST_BASE_ADDR_1+ (i+0x1c)) = 0xffffffff ^ (1<<7);
		REG32(TEST_BASE_ADDR_1+ (i+0x20)) = 0xffffffff ^ (1<<8);
		REG32(TEST_BASE_ADDR_1+ (i+0x24)) = 0xffffffff ^ (1<<9);
		REG32(TEST_BASE_ADDR_1+ (i+0x28)) = 0xffffffff ^ (1<<10);
		REG32(TEST_BASE_ADDR_1+ (i+0x2c)) = 0xffffffff ^ (1<<11);
		REG32(TEST_BASE_ADDR_1+ (i+0x30)) = 0xffffffff ^ (1<<12);
		REG32(TEST_BASE_ADDR_1+ (i+0x34)) = 0xffffffff ^ (1<<13);
		REG32(TEST_BASE_ADDR_1+ (i+0x38)) = 0xffffffff ^ (1<<14);
		REG32(TEST_BASE_ADDR_1+ (i+0x3c)) = 0xffffffff ^ (1<<15);
		REG32(TEST_BASE_ADDR_1+ (i+0x40)) = 0xffffffff ^ (1<<16);
		REG32(TEST_BASE_ADDR_1+ (i+0x44)) = 0xffffffff ^ (1<<17);
		REG32(TEST_BASE_ADDR_1+ (i+0x48)) = 0xffffffff ^ (1<<18);
		REG32(TEST_BASE_ADDR_1+ (i+0x4c)) = 0xffffffff ^ (1<<19);
		REG32(TEST_BASE_ADDR_1+ (i+0x50)) = 0xffffffff ^ (1<<20);
		REG32(TEST_BASE_ADDR_1+ (i+0x54)) = 0xffffffff ^ (1<<21);
		REG32(TEST_BASE_ADDR_1+ (i+0x58)) = 0xffffffff ^ (1<<22);
		REG32(TEST_BASE_ADDR_1+ (i+0x5c)) = 0xffffffff ^ (1<<23);
		REG32(TEST_BASE_ADDR_1+ (i+0x60)) = 0xffffffff ^ (1<<24);
		REG32(TEST_BASE_ADDR_1+ (i+0x64)) = 0xffffffff ^ (1<<25);
		REG32(TEST_BASE_ADDR_1+ (i+0x68)) = 0xffffffff ^ (1<<26);
		REG32(TEST_BASE_ADDR_1+ (i+0x6c)) = 0xffffffff ^ (1<<27);
		REG32(TEST_BASE_ADDR_1+ (i+0x70)) = 0xffffffff ^ (1<<28);
		REG32(TEST_BASE_ADDR_1+ (i+0x74)) = 0xffffffff ^ (1<<29);
		REG32(TEST_BASE_ADDR_1+ (i+0x78)) = 0xffffffff ^ (1<<30);
		REG32(TEST_BASE_ADDR_1+ (i+0x7c)) = 0xffffffff ^ (1<<31);
    }

	for(i=0;i<TEST_LEN;i+=0x80)
    {
		REG32(TEST_BASE_ADDR_2+ (i+0x0)) = 0xffffffff ^ (1<<0);
		REG32(TEST_BASE_ADDR_2+ (i+0x4)) = 0xffffffff ^ (1<<1);
		REG32(TEST_BASE_ADDR_2+ (i+0x8)) = 0xffffffff ^ (1<<2);
		REG32(TEST_BASE_ADDR_2+ (i+0xc)) = 0xffffffff ^ (1<<3);
		REG32(TEST_BASE_ADDR_2+ (i+0x10)) = 0xffffffff ^ (1<<4);
		REG32(TEST_BASE_ADDR_2+ (i+0x14)) = 0xffffffff ^ (1<<5);
		REG32(TEST_BASE_ADDR_2+ (i+0x18)) = 0xffffffff ^ (1<<6);
		REG32(TEST_BASE_ADDR_2+ (i+0x1c)) = 0xffffffff ^ (1<<7);
		REG32(TEST_BASE_ADDR_2+ (i+0x20)) = 0xffffffff ^ (1<<8);
		REG32(TEST_BASE_ADDR_2+ (i+0x24)) = 0xffffffff ^ (1<<9);
		REG32(TEST_BASE_ADDR_2+ (i+0x28)) = 0xffffffff ^ (1<<10);
		REG32(TEST_BASE_ADDR_2+ (i+0x2c)) = 0xffffffff ^ (1<<11);
		REG32(TEST_BASE_ADDR_2+ (i+0x30)) = 0xffffffff ^ (1<<12);
		REG32(TEST_BASE_ADDR_2+ (i+0x34)) = 0xffffffff ^ (1<<13);
		REG32(TEST_BASE_ADDR_2+ (i+0x38)) = 0xffffffff ^ (1<<14);
		REG32(TEST_BASE_ADDR_2+ (i+0x3c)) = 0xffffffff ^ (1<<15);
		REG32(TEST_BASE_ADDR_2+ (i+0x40)) = 0xffffffff ^ (1<<16);
		REG32(TEST_BASE_ADDR_2+ (i+0x44)) = 0xffffffff ^ (1<<17);
		REG32(TEST_BASE_ADDR_2+ (i+0x48)) = 0xffffffff ^ (1<<18);
		REG32(TEST_BASE_ADDR_2+ (i+0x4c)) = 0xffffffff ^ (1<<19);
		REG32(TEST_BASE_ADDR_2+ (i+0x50)) = 0xffffffff ^ (1<<20);
		REG32(TEST_BASE_ADDR_2+ (i+0x54)) = 0xffffffff ^ (1<<21);
		REG32(TEST_BASE_ADDR_2+ (i+0x58)) = 0xffffffff ^ (1<<22);
		REG32(TEST_BASE_ADDR_2+ (i+0x5c)) = 0xffffffff ^ (1<<23);
		REG32(TEST_BASE_ADDR_2+ (i+0x60)) = 0xffffffff ^ (1<<24);
		REG32(TEST_BASE_ADDR_2+ (i+0x64)) = 0xffffffff ^ (1<<25);
		REG32(TEST_BASE_ADDR_2+ (i+0x68)) = 0xffffffff ^ (1<<26);
		REG32(TEST_BASE_ADDR_2+ (i+0x6c)) = 0xffffffff ^ (1<<27);
		REG32(TEST_BASE_ADDR_2+ (i+0x70)) = 0xffffffff ^ (1<<28);
		REG32(TEST_BASE_ADDR_2+ (i+0x74)) = 0xffffffff ^ (1<<29);
		REG32(TEST_BASE_ADDR_2+ (i+0x78)) = 0xffffffff ^ (1<<30);
		REG32(TEST_BASE_ADDR_2+ (i+0x7c)) = 0xffffffff ^ (1<<31);
    }

	for(i=0;i<TEST_LEN;i+=0x80)
    {
		result += REG32(TEST_BASE_ADDR_1+ (i+0x0)) - REG32(TEST_BASE_ADDR_2+ (i+0x0));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4)) - REG32(TEST_BASE_ADDR_2+ (i+0x4));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x8)) - REG32(TEST_BASE_ADDR_2+ (i+0x8));
		result += REG32(TEST_BASE_ADDR_1+ (i+0xc)) - REG32(TEST_BASE_ADDR_2+ (i+0xc));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x10)) - REG32(TEST_BASE_ADDR_2+ (i+0x10));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x14)) - REG32(TEST_BASE_ADDR_2+ (i+0x14));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x18)) - REG32(TEST_BASE_ADDR_2+ (i+0x18));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x1c)) - REG32(TEST_BASE_ADDR_2+ (i+0x1c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x20)) - REG32(TEST_BASE_ADDR_2+ (i+0x20));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x24)) - REG32(TEST_BASE_ADDR_2+ (i+0x24));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x28)) - REG32(TEST_BASE_ADDR_2+ (i+0x28));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x2c)) - REG32(TEST_BASE_ADDR_2+ (i+0x2c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x30)) - REG32(TEST_BASE_ADDR_2+ (i+0x30));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x34)) - REG32(TEST_BASE_ADDR_2+ (i+0x34));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x38)) - REG32(TEST_BASE_ADDR_2+ (i+0x38));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x3c)) - REG32(TEST_BASE_ADDR_2+ (i+0x3c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x40)) - REG32(TEST_BASE_ADDR_2+ (i+0x40));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x44)) - REG32(TEST_BASE_ADDR_2+ (i+0x44));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x48)) - REG32(TEST_BASE_ADDR_2+ (i+0x48));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4c)) - REG32(TEST_BASE_ADDR_2+ (i+0x4c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x50)) - REG32(TEST_BASE_ADDR_2+ (i+0x50));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x54)) - REG32(TEST_BASE_ADDR_2+ (i+0x54));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x58)) - REG32(TEST_BASE_ADDR_2+ (i+0x58));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x5c)) - REG32(TEST_BASE_ADDR_2+ (i+0x5c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x60)) - REG32(TEST_BASE_ADDR_2+ (i+0x60));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x64)) - REG32(TEST_BASE_ADDR_2+ (i+0x64));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x68)) - REG32(TEST_BASE_ADDR_2+ (i+0x68));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x6c)) - REG32(TEST_BASE_ADDR_2+ (i+0x6c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x70)) - REG32(TEST_BASE_ADDR_2+ (i+0x70));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x74)) - REG32(TEST_BASE_ADDR_2+ (i+0x74));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x78)) - REG32(TEST_BASE_ADDR_2+ (i+0x78));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x7c)) - REG32(TEST_BASE_ADDR_2+ (i+0x7c));
		if(result)
		{
			//REG32(DEBUG_INFO_BASE + 0x10) = 0x55555555;			//error
			dmc_print_str("case 1 test fail!\r\n");
			test_error =1;
			while(1);
		}
    }

	if(result)
	{
		//REG32(DEBUG_INFO_BASE + 0x10) = 0x55555555;			//error
		dmc_print_str("case 1 test fail!\r\n");
		while(1);
	}
	dmc_print_str("case 1 test pass!\r\n");
}

void test_walking_zero_row_switch(void)
{
	uint32 i;

	//case4 walking zero switch row rw
	for(i=0;i<TEST_LEN;i+=0x80)
	{
		REG32(TEST_BASE_ADDR_2+ (i+0x0)) = REG32(TEST_BASE_ADDR_1+ (i+0x0)) = 0xffffffff ^ (1<<0);
		REG32(TEST_BASE_ADDR_2+ (i+0x4)) = REG32(TEST_BASE_ADDR_1+ (i+0x4)) = 0xffffffff ^ (1<<1);
		REG32(TEST_BASE_ADDR_2+ (i+0x8)) = REG32(TEST_BASE_ADDR_1+ (i+0x8)) = 0xffffffff ^ (1<<2);
		REG32(TEST_BASE_ADDR_2+ (i+0xc)) = REG32(TEST_BASE_ADDR_1+ (i+0xc)) = 0xffffffff ^ (1<<3);
		REG32(TEST_BASE_ADDR_2+ (i+0x10)) = REG32(TEST_BASE_ADDR_1+ (i+0x10)) = 0xffffffff ^ (1<<4);
		REG32(TEST_BASE_ADDR_2+ (i+0x14)) = REG32(TEST_BASE_ADDR_1+ (i+0x14)) = 0xffffffff ^ (1<<5);
		REG32(TEST_BASE_ADDR_2+ (i+0x18)) = REG32(TEST_BASE_ADDR_1+ (i+0x18)) = 0xffffffff ^ (1<<6);
		REG32(TEST_BASE_ADDR_2+ (i+0x1c)) = REG32(TEST_BASE_ADDR_1+ (i+0x1c)) = 0xffffffff ^ (1<<7);
		REG32(TEST_BASE_ADDR_2+ (i+0x20)) = REG32(TEST_BASE_ADDR_1+ (i+0x20)) = 0xffffffff ^ (1<<8);
		REG32(TEST_BASE_ADDR_2+ (i+0x24)) = REG32(TEST_BASE_ADDR_1+ (i+0x24)) = 0xffffffff ^ (1<<9);
		REG32(TEST_BASE_ADDR_2+ (i+0x28)) = REG32(TEST_BASE_ADDR_1+ (i+0x28)) = 0xffffffff ^ (1<<10);
		REG32(TEST_BASE_ADDR_2+ (i+0x2c)) = REG32(TEST_BASE_ADDR_1+ (i+0x2c)) = 0xffffffff ^ (1<<11);
		REG32(TEST_BASE_ADDR_2+ (i+0x30)) = REG32(TEST_BASE_ADDR_1+ (i+0x30)) = 0xffffffff ^ (1<<12);
		REG32(TEST_BASE_ADDR_2+ (i+0x34)) = REG32(TEST_BASE_ADDR_1+ (i+0x34)) = 0xffffffff ^ (1<<13);
		REG32(TEST_BASE_ADDR_2+ (i+0x38)) = REG32(TEST_BASE_ADDR_1+ (i+0x38)) = 0xffffffff ^ (1<<14);
		REG32(TEST_BASE_ADDR_2+ (i+0x3c)) = REG32(TEST_BASE_ADDR_1+ (i+0x3c)) = 0xffffffff ^ (1<<15);
		REG32(TEST_BASE_ADDR_2+ (i+0x40)) = REG32(TEST_BASE_ADDR_1+ (i+0x40)) = 0xffffffff ^ (1<<16);
		REG32(TEST_BASE_ADDR_2+ (i+0x44)) = REG32(TEST_BASE_ADDR_1+ (i+0x44)) = 0xffffffff ^ (1<<17);
		REG32(TEST_BASE_ADDR_2+ (i+0x48)) = REG32(TEST_BASE_ADDR_1+ (i+0x48)) = 0xffffffff ^ (1<<18);
		REG32(TEST_BASE_ADDR_2+ (i+0x4c)) = REG32(TEST_BASE_ADDR_1+ (i+0x4c)) = 0xffffffff ^ (1<<19);
		REG32(TEST_BASE_ADDR_2+ (i+0x50)) = REG32(TEST_BASE_ADDR_1+ (i+0x50)) = 0xffffffff ^ (1<<20);
		REG32(TEST_BASE_ADDR_2+ (i+0x54)) = REG32(TEST_BASE_ADDR_1+ (i+0x54)) = 0xffffffff ^ (1<<21);
		REG32(TEST_BASE_ADDR_2+ (i+0x58)) = REG32(TEST_BASE_ADDR_1+ (i+0x58)) = 0xffffffff ^ (1<<22);
		REG32(TEST_BASE_ADDR_2+ (i+0x5c)) = REG32(TEST_BASE_ADDR_1+ (i+0x5c)) = 0xffffffff ^ (1<<23);
		REG32(TEST_BASE_ADDR_2+ (i+0x60)) = REG32(TEST_BASE_ADDR_1+ (i+0x60)) = 0xffffffff ^ (1<<24);
		REG32(TEST_BASE_ADDR_2+ (i+0x64)) = REG32(TEST_BASE_ADDR_1+ (i+0x64)) = 0xffffffff ^ (1<<25);
		REG32(TEST_BASE_ADDR_2+ (i+0x68)) = REG32(TEST_BASE_ADDR_1+ (i+0x68)) = 0xffffffff ^ (1<<26);
		REG32(TEST_BASE_ADDR_2+ (i+0x6c)) = REG32(TEST_BASE_ADDR_1+ (i+0x6c)) = 0xffffffff ^ (1<<27);
		REG32(TEST_BASE_ADDR_2+ (i+0x70)) = REG32(TEST_BASE_ADDR_1+ (i+0x70)) = 0xffffffff ^ (1<<28);
		REG32(TEST_BASE_ADDR_2+ (i+0x74)) = REG32(TEST_BASE_ADDR_1+ (i+0x74)) = 0xffffffff ^ (1<<29);
		REG32(TEST_BASE_ADDR_2+ (i+0x78)) = REG32(TEST_BASE_ADDR_1+ (i+0x78)) = 0xffffffff ^ (1<<30);
		REG32(TEST_BASE_ADDR_2+ (i+0x7c)) = REG32(TEST_BASE_ADDR_1+ (i+0x7c)) = 0xffffffff ^ (1<<31);
	}

	for(i=0;i<TEST_LEN;i+=0x80)
	{
		result += REG32(TEST_BASE_ADDR_1+ (i+0x0)) - REG32(TEST_BASE_ADDR_2+ (i+0x0));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4)) - REG32(TEST_BASE_ADDR_2+ (i+0x4));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x8)) - REG32(TEST_BASE_ADDR_2+ (i+0x8));
		result += REG32(TEST_BASE_ADDR_1+ (i+0xc)) - REG32(TEST_BASE_ADDR_2+ (i+0xc));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x10)) - REG32(TEST_BASE_ADDR_2+ (i+0x10));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x14)) - REG32(TEST_BASE_ADDR_2+ (i+0x14));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x18)) - REG32(TEST_BASE_ADDR_2+ (i+0x18));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x1c)) - REG32(TEST_BASE_ADDR_2+ (i+0x1c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x20)) - REG32(TEST_BASE_ADDR_2+ (i+0x20));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x24)) - REG32(TEST_BASE_ADDR_2+ (i+0x24));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x28)) - REG32(TEST_BASE_ADDR_2+ (i+0x28));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x2c)) - REG32(TEST_BASE_ADDR_2+ (i+0x2c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x30)) - REG32(TEST_BASE_ADDR_2+ (i+0x30));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x34)) - REG32(TEST_BASE_ADDR_2+ (i+0x34));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x38)) - REG32(TEST_BASE_ADDR_2+ (i+0x38));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x3c)) - REG32(TEST_BASE_ADDR_2+ (i+0x3c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x40)) - REG32(TEST_BASE_ADDR_2+ (i+0x40));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x44)) - REG32(TEST_BASE_ADDR_2+ (i+0x44));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x48)) - REG32(TEST_BASE_ADDR_2+ (i+0x48));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4c)) - REG32(TEST_BASE_ADDR_2+ (i+0x4c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x50)) - REG32(TEST_BASE_ADDR_2+ (i+0x50));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x54)) - REG32(TEST_BASE_ADDR_2+ (i+0x54));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x58)) - REG32(TEST_BASE_ADDR_2+ (i+0x58));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x5c)) - REG32(TEST_BASE_ADDR_2+ (i+0x5c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x60)) - REG32(TEST_BASE_ADDR_2+ (i+0x60));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x64)) - REG32(TEST_BASE_ADDR_2+ (i+0x64));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x68)) - REG32(TEST_BASE_ADDR_2+ (i+0x68));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x6c)) - REG32(TEST_BASE_ADDR_2+ (i+0x6c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x70)) - REG32(TEST_BASE_ADDR_2+ (i+0x70));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x74)) - REG32(TEST_BASE_ADDR_2+ (i+0x74));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x78)) - REG32(TEST_BASE_ADDR_2+ (i+0x78));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x7c)) - REG32(TEST_BASE_ADDR_2+ (i+0x7c));
	}

	if(result)
	{
		//REG32(DEBUG_INFO_BASE + 0x10) = 0x55555555; 		//error
		dmc_print_str("case 2 test fail!\r\n");
		while(1);
	}
	dmc_print_str("case 2 test pass!\r\n");
}

void test_walking_one_seq(void)
{
	uint32 i;

	//case2 walking one
    for(i=0;i<TEST_LEN;i+=0x80)
    {
		REG32(TEST_BASE_ADDR_1+ (i+0x0)) = 0x00000000 | (1<<0);
		REG32(TEST_BASE_ADDR_1+ (i+0x4)) = 0x00000000 | (1<<1);
		REG32(TEST_BASE_ADDR_1+ (i+0x8)) = 0x00000000 | (1<<2);
		REG32(TEST_BASE_ADDR_1+ (i+0xc)) = 0x00000000 | (1<<3);
		REG32(TEST_BASE_ADDR_1+ (i+0x10)) = 0x00000000 | (1<<4);
		REG32(TEST_BASE_ADDR_1+ (i+0x14)) = 0x00000000 | (1<<5);
		REG32(TEST_BASE_ADDR_1+ (i+0x18)) = 0x00000000 | (1<<6);
		REG32(TEST_BASE_ADDR_1+ (i+0x1c)) = 0x00000000 | (1<<7);
		REG32(TEST_BASE_ADDR_1+ (i+0x20)) = 0x00000000 | (1<<8);
		REG32(TEST_BASE_ADDR_1+ (i+0x24)) = 0x00000000 | (1<<9);
		REG32(TEST_BASE_ADDR_1+ (i+0x28)) = 0x00000000 | (1<<10);
		REG32(TEST_BASE_ADDR_1+ (i+0x2c)) = 0x00000000 | (1<<11);
		REG32(TEST_BASE_ADDR_1+ (i+0x30)) = 0x00000000 | (1<<12);
		REG32(TEST_BASE_ADDR_1+ (i+0x34)) = 0x00000000 | (1<<13);
		REG32(TEST_BASE_ADDR_1+ (i+0x38)) = 0x00000000 | (1<<14);
		REG32(TEST_BASE_ADDR_1+ (i+0x3c)) = 0x00000000 | (1<<15);
		REG32(TEST_BASE_ADDR_1+ (i+0x40)) = 0x00000000 | (1<<16);
		REG32(TEST_BASE_ADDR_1+ (i+0x44)) = 0x00000000 | (1<<17);
		REG32(TEST_BASE_ADDR_1+ (i+0x48)) = 0x00000000 | (1<<18);
		REG32(TEST_BASE_ADDR_1+ (i+0x4c)) = 0x00000000 | (1<<19);
		REG32(TEST_BASE_ADDR_1+ (i+0x50)) = 0x00000000 | (1<<20);
		REG32(TEST_BASE_ADDR_1+ (i+0x54)) = 0x00000000 | (1<<21);
		REG32(TEST_BASE_ADDR_1+ (i+0x58)) = 0x00000000 | (1<<22);
		REG32(TEST_BASE_ADDR_1+ (i+0x5c)) = 0x00000000 | (1<<23);
		REG32(TEST_BASE_ADDR_1+ (i+0x60)) = 0x00000000 | (1<<24);
		REG32(TEST_BASE_ADDR_1+ (i+0x64)) = 0x00000000 | (1<<25);
		REG32(TEST_BASE_ADDR_1+ (i+0x68)) = 0x00000000 | (1<<26);
		REG32(TEST_BASE_ADDR_1+ (i+0x6c)) = 0x00000000 | (1<<27);
		REG32(TEST_BASE_ADDR_1+ (i+0x70)) = 0x00000000 | (1<<28);
		REG32(TEST_BASE_ADDR_1+ (i+0x74)) = 0x00000000 | (1<<29);
		REG32(TEST_BASE_ADDR_1+ (i+0x78)) = 0x00000000 | (1<<30);
		REG32(TEST_BASE_ADDR_1+ (i+0x7c)) = 0x00000000 | (1<<31);
    }

	for(i=0;i<TEST_LEN;i+=0x80)
    {
		REG32(TEST_BASE_ADDR_2+ (i+0x0)) = 0x00000000 | (1<<0);
		REG32(TEST_BASE_ADDR_2+ (i+0x4)) = 0x00000000 | (1<<1);
		REG32(TEST_BASE_ADDR_2+ (i+0x8)) = 0x00000000 | (1<<2);
		REG32(TEST_BASE_ADDR_2+ (i+0xc)) = 0x00000000 | (1<<3);
		REG32(TEST_BASE_ADDR_2+ (i+0x10)) = 0x00000000 | (1<<4);
		REG32(TEST_BASE_ADDR_2+ (i+0x14)) = 0x00000000 | (1<<5);
		REG32(TEST_BASE_ADDR_2+ (i+0x18)) = 0x00000000 | (1<<6);
		REG32(TEST_BASE_ADDR_2+ (i+0x1c)) = 0x00000000 | (1<<7);
		REG32(TEST_BASE_ADDR_2+ (i+0x20)) = 0x00000000 | (1<<8);
		REG32(TEST_BASE_ADDR_2+ (i+0x24)) = 0x00000000 | (1<<9);
		REG32(TEST_BASE_ADDR_2+ (i+0x28)) = 0x00000000 | (1<<10);
		REG32(TEST_BASE_ADDR_2+ (i+0x2c)) = 0x00000000 | (1<<11);
		REG32(TEST_BASE_ADDR_2+ (i+0x30)) = 0x00000000 | (1<<12);
		REG32(TEST_BASE_ADDR_2+ (i+0x34)) = 0x00000000 | (1<<13);
		REG32(TEST_BASE_ADDR_2+ (i+0x38)) = 0x00000000 | (1<<14);
		REG32(TEST_BASE_ADDR_2+ (i+0x3c)) = 0x00000000 | (1<<15);
		REG32(TEST_BASE_ADDR_2+ (i+0x40)) = 0x00000000 | (1<<16);
		REG32(TEST_BASE_ADDR_2+ (i+0x44)) = 0x00000000 | (1<<17);
		REG32(TEST_BASE_ADDR_2+ (i+0x48)) = 0x00000000 | (1<<18);
		REG32(TEST_BASE_ADDR_2+ (i+0x4c)) = 0x00000000 | (1<<19);
		REG32(TEST_BASE_ADDR_2+ (i+0x50)) = 0x00000000 | (1<<20);
		REG32(TEST_BASE_ADDR_2+ (i+0x54)) = 0x00000000 | (1<<21);
		REG32(TEST_BASE_ADDR_2+ (i+0x58)) = 0x00000000 | (1<<22);
		REG32(TEST_BASE_ADDR_2+ (i+0x5c)) = 0x00000000 | (1<<23);
		REG32(TEST_BASE_ADDR_2+ (i+0x60)) = 0x00000000 | (1<<24);
		REG32(TEST_BASE_ADDR_2+ (i+0x64)) = 0x00000000 | (1<<25);
		REG32(TEST_BASE_ADDR_2+ (i+0x68)) = 0x00000000 | (1<<26);
		REG32(TEST_BASE_ADDR_2+ (i+0x6c)) = 0x00000000 | (1<<27);
		REG32(TEST_BASE_ADDR_2+ (i+0x70)) = 0x00000000 | (1<<28);
		REG32(TEST_BASE_ADDR_2+ (i+0x74)) = 0x00000000 | (1<<29);
		REG32(TEST_BASE_ADDR_2+ (i+0x78)) = 0x00000000 | (1<<30);
		REG32(TEST_BASE_ADDR_2+ (i+0x7c)) = 0x00000000 | (1<<31);
    }

	for(i=0;i<TEST_LEN;i+=0x80)
    {
		result += REG32(TEST_BASE_ADDR_1+ (i+0x0)) - REG32(TEST_BASE_ADDR_2+ (i+0x0));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4)) - REG32(TEST_BASE_ADDR_2+ (i+0x4));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x8)) - REG32(TEST_BASE_ADDR_2+ (i+0x8));
		result += REG32(TEST_BASE_ADDR_1+ (i+0xc)) - REG32(TEST_BASE_ADDR_2+ (i+0xc));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x10)) - REG32(TEST_BASE_ADDR_2+ (i+0x10));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x14)) - REG32(TEST_BASE_ADDR_2+ (i+0x14));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x18)) - REG32(TEST_BASE_ADDR_2+ (i+0x18));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x1c)) - REG32(TEST_BASE_ADDR_2+ (i+0x1c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x20)) - REG32(TEST_BASE_ADDR_2+ (i+0x20));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x24)) - REG32(TEST_BASE_ADDR_2+ (i+0x24));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x28)) - REG32(TEST_BASE_ADDR_2+ (i+0x28));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x2c)) - REG32(TEST_BASE_ADDR_2+ (i+0x2c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x30)) - REG32(TEST_BASE_ADDR_2+ (i+0x30));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x34)) - REG32(TEST_BASE_ADDR_2+ (i+0x34));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x38)) - REG32(TEST_BASE_ADDR_2+ (i+0x38));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x3c)) - REG32(TEST_BASE_ADDR_2+ (i+0x3c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x40)) - REG32(TEST_BASE_ADDR_2+ (i+0x40));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x44)) - REG32(TEST_BASE_ADDR_2+ (i+0x44));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x48)) - REG32(TEST_BASE_ADDR_2+ (i+0x48));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4c)) - REG32(TEST_BASE_ADDR_2+ (i+0x4c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x50)) - REG32(TEST_BASE_ADDR_2+ (i+0x50));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x54)) - REG32(TEST_BASE_ADDR_2+ (i+0x54));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x58)) - REG32(TEST_BASE_ADDR_2+ (i+0x58));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x5c)) - REG32(TEST_BASE_ADDR_2+ (i+0x5c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x60)) - REG32(TEST_BASE_ADDR_2+ (i+0x60));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x64)) - REG32(TEST_BASE_ADDR_2+ (i+0x64));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x68)) - REG32(TEST_BASE_ADDR_2+ (i+0x68));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x6c)) - REG32(TEST_BASE_ADDR_2+ (i+0x6c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x70)) - REG32(TEST_BASE_ADDR_2+ (i+0x70));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x74)) - REG32(TEST_BASE_ADDR_2+ (i+0x74));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x78)) - REG32(TEST_BASE_ADDR_2+ (i+0x78));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x7c)) - REG32(TEST_BASE_ADDR_2+ (i+0x7c));
    }

	if(result)
	{
		//REG32(DEBUG_INFO_BASE + 0x10) = 0x55555555;			//error
		dmc_print_str("case 3 test fail!\r\n");
		while(1);
	}
	dmc_print_str("case 3 test pass!\r\n");
}

void test_walking_one_row_switch(void)
{
	uint32 i;

	//case5 walking one switch row rw
	for(i=0;i<TEST_LEN;i+=0x80)
	{
		REG32(TEST_BASE_ADDR_2+ (i+0x0)) = REG32(TEST_BASE_ADDR_1+ (i+0x0)) = 0x00000000 | (1<<0);
		REG32(TEST_BASE_ADDR_2+ (i+0x4)) = REG32(TEST_BASE_ADDR_1+ (i+0x4)) = 0x00000000 | (1<<1);
		REG32(TEST_BASE_ADDR_2+ (i+0x8)) = REG32(TEST_BASE_ADDR_1+ (i+0x8)) = 0x00000000 | (1<<2);
		REG32(TEST_BASE_ADDR_2+ (i+0xc)) = REG32(TEST_BASE_ADDR_1+ (i+0xc)) = 0x00000000 | (1<<3);
		REG32(TEST_BASE_ADDR_2+ (i+0x10)) =REG32(TEST_BASE_ADDR_1+ (i+0x10)) = 0x00000000 | (1<<4);
		REG32(TEST_BASE_ADDR_2+ (i+0x14)) =REG32(TEST_BASE_ADDR_1+ (i+0x14)) = 0x00000000 | (1<<5);
		REG32(TEST_BASE_ADDR_2+ (i+0x18)) =REG32(TEST_BASE_ADDR_1+ (i+0x18)) = 0x00000000 | (1<<6);
		REG32(TEST_BASE_ADDR_2+ (i+0x1c)) =REG32(TEST_BASE_ADDR_1+ (i+0x1c)) = 0x00000000 | (1<<7);
		REG32(TEST_BASE_ADDR_2+ (i+0x20)) =REG32(TEST_BASE_ADDR_1+ (i+0x20)) = 0x00000000 | (1<<8);
		REG32(TEST_BASE_ADDR_2+ (i+0x24)) =REG32(TEST_BASE_ADDR_1+ (i+0x24)) = 0x00000000 | (1<<9);
		REG32(TEST_BASE_ADDR_2+ (i+0x28)) =REG32(TEST_BASE_ADDR_1+ (i+0x28)) = 0x00000000 | (1<<10);
		REG32(TEST_BASE_ADDR_2+ (i+0x2c)) =REG32(TEST_BASE_ADDR_1+ (i+0x2c)) = 0x00000000 | (1<<11);
		REG32(TEST_BASE_ADDR_2+ (i+0x30)) =REG32(TEST_BASE_ADDR_1+ (i+0x30)) = 0x00000000 | (1<<12);
		REG32(TEST_BASE_ADDR_2+ (i+0x34)) =REG32(TEST_BASE_ADDR_1+ (i+0x34)) = 0x00000000 | (1<<13);
		REG32(TEST_BASE_ADDR_2+ (i+0x38)) =REG32(TEST_BASE_ADDR_1+ (i+0x38)) = 0x00000000 | (1<<14);
		REG32(TEST_BASE_ADDR_2+ (i+0x3c)) =REG32(TEST_BASE_ADDR_1+ (i+0x3c)) = 0x00000000 | (1<<15);
		REG32(TEST_BASE_ADDR_2+ (i+0x40)) =REG32(TEST_BASE_ADDR_1+ (i+0x40)) = 0x00000000 | (1<<16);
		REG32(TEST_BASE_ADDR_2+ (i+0x44)) =REG32(TEST_BASE_ADDR_1+ (i+0x44)) = 0x00000000 | (1<<17);
		REG32(TEST_BASE_ADDR_2+ (i+0x48)) =REG32(TEST_BASE_ADDR_1+ (i+0x48)) = 0x00000000 | (1<<18);
		REG32(TEST_BASE_ADDR_2+ (i+0x4c)) =REG32(TEST_BASE_ADDR_1+ (i+0x4c)) = 0x00000000 | (1<<19);
		REG32(TEST_BASE_ADDR_2+ (i+0x50)) =REG32(TEST_BASE_ADDR_1+ (i+0x50)) = 0x00000000 | (1<<20);
		REG32(TEST_BASE_ADDR_2+ (i+0x54)) =REG32(TEST_BASE_ADDR_1+ (i+0x54)) = 0x00000000 | (1<<21);
		REG32(TEST_BASE_ADDR_2+ (i+0x58)) =REG32(TEST_BASE_ADDR_1+ (i+0x58)) = 0x00000000 | (1<<22);
		REG32(TEST_BASE_ADDR_2+ (i+0x5c)) =REG32(TEST_BASE_ADDR_1+ (i+0x5c)) = 0x00000000 | (1<<23);
		REG32(TEST_BASE_ADDR_2+ (i+0x60)) =REG32(TEST_BASE_ADDR_1+ (i+0x60)) = 0x00000000 | (1<<24);
		REG32(TEST_BASE_ADDR_2+ (i+0x64)) =REG32(TEST_BASE_ADDR_1+ (i+0x64)) = 0x00000000 | (1<<25);
		REG32(TEST_BASE_ADDR_2+ (i+0x68)) =REG32(TEST_BASE_ADDR_1+ (i+0x68)) = 0x00000000 | (1<<26);
		REG32(TEST_BASE_ADDR_2+ (i+0x6c)) =REG32(TEST_BASE_ADDR_1+ (i+0x6c)) = 0x00000000 | (1<<27);
		REG32(TEST_BASE_ADDR_2+ (i+0x70)) =REG32(TEST_BASE_ADDR_1+ (i+0x70)) = 0x00000000 | (1<<28);
		REG32(TEST_BASE_ADDR_2+ (i+0x74)) =REG32(TEST_BASE_ADDR_1+ (i+0x74)) = 0x00000000 | (1<<29);
		REG32(TEST_BASE_ADDR_2+ (i+0x78)) =REG32(TEST_BASE_ADDR_1+ (i+0x78)) = 0x00000000 | (1<<30);
		REG32(TEST_BASE_ADDR_2+ (i+0x7c)) =REG32(TEST_BASE_ADDR_1+ (i+0x7c)) = 0x00000000 | (1<<31);
	}

	for(i=0;i<TEST_LEN;i+=0x80)
	{
		result += REG32(TEST_BASE_ADDR_1+ (i+0x0)) - REG32(TEST_BASE_ADDR_2+ (i+0x0));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4)) - REG32(TEST_BASE_ADDR_2+ (i+0x4));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x8)) - REG32(TEST_BASE_ADDR_2+ (i+0x8));
		result += REG32(TEST_BASE_ADDR_1+ (i+0xc)) - REG32(TEST_BASE_ADDR_2+ (i+0xc));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x10)) - REG32(TEST_BASE_ADDR_2+ (i+0x10));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x14)) - REG32(TEST_BASE_ADDR_2+ (i+0x14));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x18)) - REG32(TEST_BASE_ADDR_2+ (i+0x18));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x1c)) - REG32(TEST_BASE_ADDR_2+ (i+0x1c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x20)) - REG32(TEST_BASE_ADDR_2+ (i+0x20));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x24)) - REG32(TEST_BASE_ADDR_2+ (i+0x24));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x28)) - REG32(TEST_BASE_ADDR_2+ (i+0x28));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x2c)) - REG32(TEST_BASE_ADDR_2+ (i+0x2c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x30)) - REG32(TEST_BASE_ADDR_2+ (i+0x30));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x34)) - REG32(TEST_BASE_ADDR_2+ (i+0x34));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x38)) - REG32(TEST_BASE_ADDR_2+ (i+0x38));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x3c)) - REG32(TEST_BASE_ADDR_2+ (i+0x3c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x40)) - REG32(TEST_BASE_ADDR_2+ (i+0x40));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x44)) - REG32(TEST_BASE_ADDR_2+ (i+0x44));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x48)) - REG32(TEST_BASE_ADDR_2+ (i+0x48));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4c)) - REG32(TEST_BASE_ADDR_2+ (i+0x4c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x50)) - REG32(TEST_BASE_ADDR_2+ (i+0x50));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x54)) - REG32(TEST_BASE_ADDR_2+ (i+0x54));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x58)) - REG32(TEST_BASE_ADDR_2+ (i+0x58));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x5c)) - REG32(TEST_BASE_ADDR_2+ (i+0x5c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x60)) - REG32(TEST_BASE_ADDR_2+ (i+0x60));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x64)) - REG32(TEST_BASE_ADDR_2+ (i+0x64));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x68)) - REG32(TEST_BASE_ADDR_2+ (i+0x68));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x6c)) - REG32(TEST_BASE_ADDR_2+ (i+0x6c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x70)) - REG32(TEST_BASE_ADDR_2+ (i+0x70));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x74)) - REG32(TEST_BASE_ADDR_2+ (i+0x74));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x78)) - REG32(TEST_BASE_ADDR_2+ (i+0x78));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x7c)) - REG32(TEST_BASE_ADDR_2+ (i+0x7c));
	}

	if(result)
	{
		//REG32(DEBUG_INFO_BASE + 0x10) = 0x55555555; 		//error
		dmc_print_str("case 4 test fail!\r\n");
		while(1);
	}
	dmc_print_str("case 4 test pass!\r\n");
}

#endif

void test_random_row_switch(uint32 TEST_BASE_ADDR_1, uint32 TEST_BASE_ADDR_2)
{
	uint32 i;

	//case3 random test
	SetSeed(RANDOM_SEED_DATA);
	for(i=0;i<TEST_LEN;i+=0x80)
    {
		REG32(TEST_BASE_ADDR_2+ (i+0x0)) = REG32(TEST_BASE_ADDR_1+ (i+0x0)) =  GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x4)) = REG32(TEST_BASE_ADDR_1+ (i+0x4)) =  GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x8)) = REG32(TEST_BASE_ADDR_1+ (i+0x8)) =  GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0xc)) = REG32(TEST_BASE_ADDR_1+ (i+0xc)) =  GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x10)) = REG32(TEST_BASE_ADDR_1+ (i+0x10)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x14)) = REG32(TEST_BASE_ADDR_1+ (i+0x14)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x18)) = REG32(TEST_BASE_ADDR_1+ (i+0x18)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x1c)) = REG32(TEST_BASE_ADDR_1+ (i+0x1c)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x20)) = REG32(TEST_BASE_ADDR_1+ (i+0x20)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x24)) = REG32(TEST_BASE_ADDR_1+ (i+0x24)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x28)) = REG32(TEST_BASE_ADDR_1+ (i+0x28)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x2c)) = REG32(TEST_BASE_ADDR_1+ (i+0x2c)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x30)) = REG32(TEST_BASE_ADDR_1+ (i+0x30)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x34)) = REG32(TEST_BASE_ADDR_1+ (i+0x34)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x38)) = REG32(TEST_BASE_ADDR_1+ (i+0x38)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x3c)) = REG32(TEST_BASE_ADDR_1+ (i+0x3c)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x40)) = REG32(TEST_BASE_ADDR_1+ (i+0x40)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x44)) = REG32(TEST_BASE_ADDR_1+ (i+0x44)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x48)) = REG32(TEST_BASE_ADDR_1+ (i+0x48)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x4c)) = REG32(TEST_BASE_ADDR_1+ (i+0x4c)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x50)) = REG32(TEST_BASE_ADDR_1+ (i+0x50)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x54)) = REG32(TEST_BASE_ADDR_1+ (i+0x54)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x58)) = REG32(TEST_BASE_ADDR_1+ (i+0x58)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x5c)) = REG32(TEST_BASE_ADDR_1+ (i+0x5c)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x60)) = REG32(TEST_BASE_ADDR_1+ (i+0x60)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x64)) = REG32(TEST_BASE_ADDR_1+ (i+0x64)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x68)) = REG32(TEST_BASE_ADDR_1+ (i+0x68)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x6c)) = REG32(TEST_BASE_ADDR_1+ (i+0x6c)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x70)) = REG32(TEST_BASE_ADDR_1+ (i+0x70)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x74)) = REG32(TEST_BASE_ADDR_1+ (i+0x74)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x78)) = REG32(TEST_BASE_ADDR_1+ (i+0x78)) = GetRandom();
		REG32(TEST_BASE_ADDR_2+ (i+0x7c)) = REG32(TEST_BASE_ADDR_1+ (i+0x7c)) = GetRandom();
    }

	for(i=0;i<TEST_LEN;i+=0x80)
    {
		result += REG32(TEST_BASE_ADDR_1+ (i+0x0)) - REG32(TEST_BASE_ADDR_2+ (i+0x0));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4)) - REG32(TEST_BASE_ADDR_2+ (i+0x4));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x8)) - REG32(TEST_BASE_ADDR_2+ (i+0x8));
		result += REG32(TEST_BASE_ADDR_1+ (i+0xc)) - REG32(TEST_BASE_ADDR_2+ (i+0xc));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x10)) - REG32(TEST_BASE_ADDR_2+ (i+0x10));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x14)) - REG32(TEST_BASE_ADDR_2+ (i+0x14));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x18)) - REG32(TEST_BASE_ADDR_2+ (i+0x18));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x1c)) - REG32(TEST_BASE_ADDR_2+ (i+0x1c));

		result += REG32(TEST_BASE_ADDR_1+ (i+0x20)) - REG32(TEST_BASE_ADDR_2+ (i+0x20));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x24)) - REG32(TEST_BASE_ADDR_2+ (i+0x24));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x28)) - REG32(TEST_BASE_ADDR_2+ (i+0x28));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x2c)) - REG32(TEST_BASE_ADDR_2+ (i+0x2c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x30)) - REG32(TEST_BASE_ADDR_2+ (i+0x30));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x34)) - REG32(TEST_BASE_ADDR_2+ (i+0x34));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x38)) - REG32(TEST_BASE_ADDR_2+ (i+0x38));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x3c)) - REG32(TEST_BASE_ADDR_2+ (i+0x3c));

		result += REG32(TEST_BASE_ADDR_1+ (i+0x40)) - REG32(TEST_BASE_ADDR_2+ (i+0x40));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x44)) - REG32(TEST_BASE_ADDR_2+ (i+0x44));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x48)) - REG32(TEST_BASE_ADDR_2+ (i+0x48));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4c)) - REG32(TEST_BASE_ADDR_2+ (i+0x4c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x50)) - REG32(TEST_BASE_ADDR_2+ (i+0x50));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x54)) - REG32(TEST_BASE_ADDR_2+ (i+0x54));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x58)) - REG32(TEST_BASE_ADDR_2+ (i+0x58));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x5c)) - REG32(TEST_BASE_ADDR_2+ (i+0x5c));

		result += REG32(TEST_BASE_ADDR_1+ (i+0x60)) - REG32(TEST_BASE_ADDR_2+ (i+0x60));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x64)) - REG32(TEST_BASE_ADDR_2+ (i+0x64));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x68)) - REG32(TEST_BASE_ADDR_2+ (i+0x68));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x6c)) - REG32(TEST_BASE_ADDR_2+ (i+0x6c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x70)) - REG32(TEST_BASE_ADDR_2+ (i+0x70));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x74)) - REG32(TEST_BASE_ADDR_2+ (i+0x74));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x78)) - REG32(TEST_BASE_ADDR_2+ (i+0x78));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x7c)) - REG32(TEST_BASE_ADDR_2+ (i+0x7c));
    }

	if(result)
	{
		REG32(DEBUG_INFO_BASE + 0x10) = 0x55555555;			//error
		dmc_print_str("case 5 test fail!\r\n");
		while(1);
	}
	else
		dmc_print_str("case 5 test pass!\r\n");
}
#if 0
void test_block_seq_row_switch(void)
{
	uint32 i,j;

	j=255;

	for(i=0;i<TEST_LEN;i+=0x80)
    {
		REG32(TEST_BASE_ADDR_2+ (i+0x0)) = REG32(TEST_BASE_ADDR_1+ (i+0x0)) =  UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x4)) = REG32(TEST_BASE_ADDR_1+ (i+0x4)) =  UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x8)) = REG32(TEST_BASE_ADDR_1+ (i+0x8)) =  UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0xc)) = REG32(TEST_BASE_ADDR_1+ (i+0xc)) =  UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x10)) = REG32(TEST_BASE_ADDR_1+ (i+0x10)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x14)) = REG32(TEST_BASE_ADDR_1+ (i+0x14)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x18)) = REG32(TEST_BASE_ADDR_1+ (i+0x18)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x1c)) = REG32(TEST_BASE_ADDR_1+ (i+0x1c)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x20)) = REG32(TEST_BASE_ADDR_1+ (i+0x20)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x24)) = REG32(TEST_BASE_ADDR_1+ (i+0x24)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x28)) = REG32(TEST_BASE_ADDR_1+ (i+0x28)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x2c)) = REG32(TEST_BASE_ADDR_1+ (i+0x2c)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x30)) = REG32(TEST_BASE_ADDR_1+ (i+0x30)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x34)) = REG32(TEST_BASE_ADDR_1+ (i+0x34)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x38)) = REG32(TEST_BASE_ADDR_1+ (i+0x38)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x3c)) = REG32(TEST_BASE_ADDR_1+ (i+0x3c)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x40)) = REG32(TEST_BASE_ADDR_1+ (i+0x40)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x44)) = REG32(TEST_BASE_ADDR_1+ (i+0x44)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x48)) = REG32(TEST_BASE_ADDR_1+ (i+0x48)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x4c)) = REG32(TEST_BASE_ADDR_1+ (i+0x4c)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x50)) = REG32(TEST_BASE_ADDR_1+ (i+0x50)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x54)) = REG32(TEST_BASE_ADDR_1+ (i+0x54)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x58)) = REG32(TEST_BASE_ADDR_1+ (i+0x58)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x5c)) = REG32(TEST_BASE_ADDR_1+ (i+0x5c)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x60)) = REG32(TEST_BASE_ADDR_1+ (i+0x60)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x64)) = REG32(TEST_BASE_ADDR_1+ (i+0x64)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x68)) = REG32(TEST_BASE_ADDR_1+ (i+0x68)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x6c)) = REG32(TEST_BASE_ADDR_1+ (i+0x6c)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x70)) = REG32(TEST_BASE_ADDR_1+ (i+0x70)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x74)) = REG32(TEST_BASE_ADDR_1+ (i+0x74)) = UL_BYTE((~j));
		j--;
		REG32(TEST_BASE_ADDR_2+ (i+0x78)) = REG32(TEST_BASE_ADDR_1+ (i+0x78)) = UL_BYTE(j);
		REG32(TEST_BASE_ADDR_2+ (i+0x7c)) = REG32(TEST_BASE_ADDR_1+ (i+0x7c)) = UL_BYTE((~j));
		j--;
    }

	for(i=0;i<TEST_LEN;i+=0x80)
    {
		result += REG32(TEST_BASE_ADDR_1+ (i+0x0)) - REG32(TEST_BASE_ADDR_2+ (i+0x0));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4)) - REG32(TEST_BASE_ADDR_2+ (i+0x4));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x8)) - REG32(TEST_BASE_ADDR_2+ (i+0x8));
		result += REG32(TEST_BASE_ADDR_1+ (i+0xc)) - REG32(TEST_BASE_ADDR_2+ (i+0xc));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x10)) - REG32(TEST_BASE_ADDR_2+ (i+0x10));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x14)) - REG32(TEST_BASE_ADDR_2+ (i+0x14));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x18)) - REG32(TEST_BASE_ADDR_2+ (i+0x18));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x1c)) - REG32(TEST_BASE_ADDR_2+ (i+0x1c));

		result += REG32(TEST_BASE_ADDR_1+ (i+0x20)) - REG32(TEST_BASE_ADDR_2+ (i+0x20));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x24)) - REG32(TEST_BASE_ADDR_2+ (i+0x24));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x28)) - REG32(TEST_BASE_ADDR_2+ (i+0x28));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x2c)) - REG32(TEST_BASE_ADDR_2+ (i+0x2c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x30)) - REG32(TEST_BASE_ADDR_2+ (i+0x30));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x34)) - REG32(TEST_BASE_ADDR_2+ (i+0x34));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x38)) - REG32(TEST_BASE_ADDR_2+ (i+0x38));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x3c)) - REG32(TEST_BASE_ADDR_2+ (i+0x3c));

		result += REG32(TEST_BASE_ADDR_1+ (i+0x40)) - REG32(TEST_BASE_ADDR_2+ (i+0x40));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x44)) - REG32(TEST_BASE_ADDR_2+ (i+0x44));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x48)) - REG32(TEST_BASE_ADDR_2+ (i+0x48));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4c)) - REG32(TEST_BASE_ADDR_2+ (i+0x4c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x50)) - REG32(TEST_BASE_ADDR_2+ (i+0x50));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x54)) - REG32(TEST_BASE_ADDR_2+ (i+0x54));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x58)) - REG32(TEST_BASE_ADDR_2+ (i+0x58));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x5c)) - REG32(TEST_BASE_ADDR_2+ (i+0x5c));

		result += REG32(TEST_BASE_ADDR_1+ (i+0x60)) - REG32(TEST_BASE_ADDR_2+ (i+0x60));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x64)) - REG32(TEST_BASE_ADDR_2+ (i+0x64));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x68)) - REG32(TEST_BASE_ADDR_2+ (i+0x68));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x6c)) - REG32(TEST_BASE_ADDR_2+ (i+0x6c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x70)) - REG32(TEST_BASE_ADDR_2+ (i+0x70));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x74)) - REG32(TEST_BASE_ADDR_2+ (i+0x74));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x78)) - REG32(TEST_BASE_ADDR_2+ (i+0x78));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x7c)) - REG32(TEST_BASE_ADDR_2+ (i+0x7c));
    }

	if(result)
	{
		//REG32(DEBUG_INFO_BASE + 0x10) = 0x55555555;			//error
		dmc_print_str("case 6 test fail!\r\n");
		while(1);
	}
	dmc_print_str("case 6 test pass!\r\n");
}

void test_checkboard_row_switch(void)
{
	uint32 i;

	//case3 random test
 	for(i=0;i<TEST_LEN;i+=0x80)
    {
		REG32(TEST_BASE_ADDR_2+ (i+0x0)) = REG32(TEST_BASE_ADDR_1+ (i+0x0)) =  CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x4)) = REG32(TEST_BASE_ADDR_1+ (i+0x4)) =  CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x8)) = REG32(TEST_BASE_ADDR_1+ (i+0x8)) =  CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0xc)) = REG32(TEST_BASE_ADDR_1+ (i+0xc)) =  CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x10)) = REG32(TEST_BASE_ADDR_1+ (i+0x10)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x14)) = REG32(TEST_BASE_ADDR_1+ (i+0x14)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x18)) = REG32(TEST_BASE_ADDR_1+ (i+0x18)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x1c)) = REG32(TEST_BASE_ADDR_1+ (i+0x1c)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x20)) = REG32(TEST_BASE_ADDR_1+ (i+0x20)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x24)) = REG32(TEST_BASE_ADDR_1+ (i+0x24)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x28)) = REG32(TEST_BASE_ADDR_1+ (i+0x28)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x2c)) = REG32(TEST_BASE_ADDR_1+ (i+0x2c)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x30)) = REG32(TEST_BASE_ADDR_1+ (i+0x30)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x34)) = REG32(TEST_BASE_ADDR_1+ (i+0x34)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x38)) = REG32(TEST_BASE_ADDR_1+ (i+0x38)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x3c)) = REG32(TEST_BASE_ADDR_1+ (i+0x3c)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x40)) = REG32(TEST_BASE_ADDR_1+ (i+0x40)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x44)) = REG32(TEST_BASE_ADDR_1+ (i+0x44)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x48)) = REG32(TEST_BASE_ADDR_1+ (i+0x48)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x4c)) = REG32(TEST_BASE_ADDR_1+ (i+0x4c)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x50)) = REG32(TEST_BASE_ADDR_1+ (i+0x50)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x54)) = REG32(TEST_BASE_ADDR_1+ (i+0x54)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x58)) = REG32(TEST_BASE_ADDR_1+ (i+0x58)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x5c)) = REG32(TEST_BASE_ADDR_1+ (i+0x5c)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x60)) = REG32(TEST_BASE_ADDR_1+ (i+0x60)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x64)) = REG32(TEST_BASE_ADDR_1+ (i+0x64)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x68)) = REG32(TEST_BASE_ADDR_1+ (i+0x68)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x6c)) = REG32(TEST_BASE_ADDR_1+ (i+0x6c)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x70)) = REG32(TEST_BASE_ADDR_1+ (i+0x70)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x74)) = REG32(TEST_BASE_ADDR_1+ (i+0x74)) = CHECKERBOARD2;
		REG32(TEST_BASE_ADDR_2+ (i+0x78)) = REG32(TEST_BASE_ADDR_1+ (i+0x78)) = CHECKERBOARD1;
		REG32(TEST_BASE_ADDR_2+ (i+0x7c)) = REG32(TEST_BASE_ADDR_1+ (i+0x7c)) = CHECKERBOARD2;
    }

	for(i=0;i<TEST_LEN;i+=0x80)
    {
		result += REG32(TEST_BASE_ADDR_1+ (i+0x0)) - REG32(TEST_BASE_ADDR_2+ (i+0x0));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4)) - REG32(TEST_BASE_ADDR_2+ (i+0x4));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x8)) - REG32(TEST_BASE_ADDR_2+ (i+0x8));
		result += REG32(TEST_BASE_ADDR_1+ (i+0xc)) - REG32(TEST_BASE_ADDR_2+ (i+0xc));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x10)) - REG32(TEST_BASE_ADDR_2+ (i+0x10));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x14)) - REG32(TEST_BASE_ADDR_2+ (i+0x14));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x18)) - REG32(TEST_BASE_ADDR_2+ (i+0x18));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x1c)) - REG32(TEST_BASE_ADDR_2+ (i+0x1c));

		result += REG32(TEST_BASE_ADDR_1+ (i+0x20)) - REG32(TEST_BASE_ADDR_2+ (i+0x20));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x24)) - REG32(TEST_BASE_ADDR_2+ (i+0x24));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x28)) - REG32(TEST_BASE_ADDR_2+ (i+0x28));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x2c)) - REG32(TEST_BASE_ADDR_2+ (i+0x2c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x30)) - REG32(TEST_BASE_ADDR_2+ (i+0x30));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x34)) - REG32(TEST_BASE_ADDR_2+ (i+0x34));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x38)) - REG32(TEST_BASE_ADDR_2+ (i+0x38));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x3c)) - REG32(TEST_BASE_ADDR_2+ (i+0x3c));

		result += REG32(TEST_BASE_ADDR_1+ (i+0x40)) - REG32(TEST_BASE_ADDR_2+ (i+0x40));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x44)) - REG32(TEST_BASE_ADDR_2+ (i+0x44));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x48)) - REG32(TEST_BASE_ADDR_2+ (i+0x48));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x4c)) - REG32(TEST_BASE_ADDR_2+ (i+0x4c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x50)) - REG32(TEST_BASE_ADDR_2+ (i+0x50));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x54)) - REG32(TEST_BASE_ADDR_2+ (i+0x54));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x58)) - REG32(TEST_BASE_ADDR_2+ (i+0x58));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x5c)) - REG32(TEST_BASE_ADDR_2+ (i+0x5c));

		result += REG32(TEST_BASE_ADDR_1+ (i+0x60)) - REG32(TEST_BASE_ADDR_2+ (i+0x60));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x64)) - REG32(TEST_BASE_ADDR_2+ (i+0x64));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x68)) - REG32(TEST_BASE_ADDR_2+ (i+0x68));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x6c)) - REG32(TEST_BASE_ADDR_2+ (i+0x6c));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x70)) - REG32(TEST_BASE_ADDR_2+ (i+0x70));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x74)) - REG32(TEST_BASE_ADDR_2+ (i+0x74));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x78)) - REG32(TEST_BASE_ADDR_2+ (i+0x78));
		result += REG32(TEST_BASE_ADDR_1+ (i+0x7c)) - REG32(TEST_BASE_ADDR_2+ (i+0x7c));
    }

	if(result)
	{
		dmc_print_str("case 7 test fail!\r\n");
		while(1);
	}
	dmc_print_str("case 7 test pass!\r\n");
}
#endif
#if 0
int ddr_no_gate_test(u32 enable)
{
	u32 regval;
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	pdmc->dmc_cfg3 = enable;
}
int ddr_idle_test(void)
{
	u32 regval;
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	regval = pdmc->dmc_dcfg9;
	regval = u32_bits_set(regval, 0, 3, 0);
	pdmc->dmc_dcfg9 = regval;
}
int ddr_auto_power_down_test(void)
{
	u32 regval;
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	regval = pdmc->dmc_dcfg9;
	regval = u32_bits_set(regval, 0, 3, 3);
	pdmc->dmc_dcfg9 = regval;
}
int ddr_auto_self_refresh_test(void)
{
	u32 regval;
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	regval = pdmc->dmc_dcfg9;
	regval = u32_bits_set(regval, 0, 3, 5);
	pdmc->dmc_dcfg9 = regval;

}
int ddr_read_write_test(void)
{
	uint32 TEST_BASE_ADDR_1 = 0x80000000;
	uint32 TEST_BASE_ADDR_2 = 0xa0000000;
	int i;
	for(i = 0; i < 0x100; i++)
	{
		test_random_row_switch(TEST_BASE_ADDR_1, TEST_BASE_ADDR_2);
		dmc_print_str("master test pass!\r\n");
		if(TEST_BASE_ADDR_1 < 0xa0000000)
		{
			TEST_BASE_ADDR_1 += 0x8000000;
			TEST_BASE_ADDR_2 += 0x8000000;
		}
		else
		{
			TEST_BASE_ADDR_1 = 0x80000000;
			TEST_BASE_ADDR_2 = 0xa0000000;
		}
	}
}
int ddr_bist_test(void)
{

	if(0 != ddr_scan_online_sprd_r2p0())
	{
		dmc_print_str("error:-6\r\n");
		return -6;
	}
}

void delay(int x)
{
	volatile int i;
	volatile unsigned int val;
	for(i=0;i<x;i++)
	{
		val=*(volatile unsigned int *)0x402b00c4;  // readonly reg.
	}
}
int ddr_vref_test(void)
{
	u32 regval;
	int i;
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
retest:
	for(i=0; i <= 0x1f; i++)
	{
		regval = pdmc->dmc_cfg1;
		regval = u32_bits_set(regval, 20, 5, i);
		pdmc->dmc_cfg1 = regval;
		delay(100000);
	}
	delay(10);
	for(i=0x1f; i >= 0; i--)
	{
		regval = pdmc->dmc_cfg1;
		regval = u32_bits_set(regval, 20, 5, i);
		pdmc->dmc_cfg1 = regval;
		delay(100000);
	}
	goto retest;
}
int ddr_cke_high_test(void)
{
	u32 regval;
	int i;
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	regval = pdmc->dmc_dcfg9;
	regval = u32_bits_set(regval, 0, 3, 0);
	pdmc->dmc_dcfg9 = regval;

	while(1);
}
int ddr_cke_low_test(void)
{
	u32 regval;
	int i;
	DMC_R2P0_REG_INFO_PTR pdmc = (DMC_R2P0_REG_INFO_PTR)PUB_DMC_BASE;
	regval = pdmc->dmc_dcfg0;
	regval = u32_bits_set(regval, 14, 1, 0);
	pdmc->dmc_dcfg0 = regval;
	delay(300);
	while(1);
}
#endif
int ddr_close_umctl_auto_gate(void)
{
	REG32(0x402B00D0) &= 0xFFFFFF60;
}

int ddr_close_phy_auto_gate(void)
{
	REG32(0x402B00D0) &= 0xFFFFFF00;
}
int ddr_master_test(void)
{
	uint32 timer_s, timer_e;
#if 0//def CONFIG_POWER_TEST
	ddr_no_gate_test(0);
	dmc_print_str("master start no gate test!\r\n");
	ddr_no_gate_test(1);
	dmc_print_str("master start idle test!\r\n");
	ddr_idle_test();
	dmc_print_str("master start auto power donw test!\r\n");
	ddr_auto_power_down_test();
	dmc_print_str("master start auto self refresh test!\r\n");
	ddr_auto_self_refresh_test();
	dmc_print_str("master start read write test!\r\n");
	ddr_read_write_test();
	dmc_print_str("master start bist test!\r\n");
	ddr_bist_test();
#endif
	//ddr_close_umctl_auto_gate();
	//ddr_close_phy_auto_gate();
	//ddr_vref_test();
	//ddr_cke_low_test();
	//ddr_cke_high_test();
#ifdef CONFIG_MEM_TEST
	uint32 TEST_BASE_ADDR_1 = 0x80000000;
	uint32 TEST_BASE_ADDR_2 = 0x90000000;
	int i;
	//REG32(DEBUG_INFO_BASE + 0x10) = 0x00000000;
	//REG32(DEBUG_INFO_BASE + 0x14) = 0x00000000;
	//timer_s = REG32(0xe4230004);

	//test_walking_zero_seq();
	//test_walking_one_seq();

	//for(i = 0; i < 0x10000000; i++)
	dmc_print_str("start ddr master test!\r\n");
	//while(1)
	{
		test_random_row_switch(TEST_BASE_ADDR_1, TEST_BASE_ADDR_2);
		//test_random_row_switch(0xa0000000, 0xb0000000);
		//test_random_row_switch(0xc0000000, 0xd0000000);
		//test_random_row_switch(0xe0000000, 0xf0000000);
		dmc_print_str("master test pass!\r\n");
	#if 0
		if(TEST_BASE_ADDR_1 < 0xa0000000)
		{
			TEST_BASE_ADDR_1 += 0x8000000;
			TEST_BASE_ADDR_2 += 0x8000000;
		}
		else
		{
			TEST_BASE_ADDR_1 = 0x80000000;
			TEST_BASE_ADDR_2 = 0xa0000000;
		}
	#endif
	}
#endif
	//test_random_row_switch();
	//test_walking_zero_row_switch();
	//test_walking_one_row_switch();
	//test_block_seq_row_switch();
	//test_checkboard_row_switch();

	//REG32(DEBUG_INFO_BASE + 0x10) = 0xaaaaaaaa;
	dmc_print_str("master test pass!\r\n");
	//timer_e = REG32(0xe4230004);
	//REG32(DEBUG_INFO_BASE + 0x14) = timer_e - timer_s;

}

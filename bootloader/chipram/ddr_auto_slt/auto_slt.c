#include <common.h>
#include <adi.h>
#include "auto_slt_pattern.h"
#include <asm/arch/clk_para_config.h>



/********************************************************************************************************
*********************************************************************************************************
*********************************************************************************************************

											highly attention !!
			remember that if you compile ddr pattern code, you must disable lowpower config in umctl_28nm.c !!


*********************************************************************************************************
*********************************************************************************************************
*********************************************************************************************************/

#define DQ0				(1<<0)
#define DQ1				(1<<1)
#define DQ2				(1<<2)
#define DQ3				(1<<3)
#define DQ4				(1<<4)
#define DQ5				(1<<5)
#define DQ6				(1<<6)
#define DQ7				(1<<7)

#define DQ8				(1<<8)
#define DQ9				(1<<9)
#define DQ10			(1<<10)
#define DQ11			(1<<11)
#define DQ12			(1<<12)
#define DQ13			(1<<13)
#define DQ14			(1<<14)
#define DQ15			(1<<15)

#define DQ16			(1<<16)
#define DQ17			(1<<17)
#define DQ18			(1<<18)
#define DQ19			(1<<19)
#define DQ20			(1<<20)
#define DQ21			(1<<21)
#define DQ22			(1<<22)
#define DQ23			(1<<23)

#define DQ24			(1<<24)
#define DQ25			(1<<25)
#define DQ26			(1<<26)
#define DQ27			(1<<27)
#define DQ28			(1<<28)
#define DQ29			(1<<29)
#define DQ30			(1<<30)
#define DQ31			(1<<31)

#if defined(CONFIG_SCX35LT8)
#define PATTERN_SRC_A			0x101000
#else
#define PATTERN_SRC_A			0x1000
#endif
#define PATTERN_DST				0x80000000

#define REG32(x)   (*((volatile uint32 *)(x)))

//typedef unsigned int uint32;
typedef struct
{
    uint32 src_addr;
	uint32 dst_addr;
	uint32 data_len;
}BurstBistInfo;

extern void BurstTransfer(BurstBistInfo *p_burst_info);
extern void BurstTransfer_N(BurstBistInfo *p_burst_info);
extern void burst8_write_all(uint32 pattern, uint32 src, uint32 len);
extern void burst8_write_while1(pattern0,pattern1, pattern2,pattern3,pattern4,pattern5,pattern6,pattern7);
extern void burst8_write_one_burst(BurstBistInfo *p_burst_info);
extern void burst8_move(BurstBistInfo *p_burst_info);
extern void ddr_print(const unsigned char *string);
extern void wait_pclk(uint32 n_pclk);
static uint32 seed;

static DMC_UMCTL_REG_INFO_PTR_T umctl = (DMC_UMCTL_REG_INFO_PTR_T)0x30000000;
static DMC_PUBL_REG_INFO_PTR_T publ = (DMC_PUBL_REG_INFO_PTR_T)0x30010000;

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

void __burst8_rw(uint32 src, uint32 dst, uint32 len, uint32 mode)
{
    BurstBistInfo burst_info;
	uint32 burst_cnt;
	uint32 i;

	burst_info.src_addr = (uint32)src;
	burst_info.dst_addr = (uint32)dst;

	burst_cnt = len/32;
	burst_info.data_len = 8;

	if(mode==0)
	{
		for(i=0;i<burst_cnt;i++)
		{
	        BurstTransfer(&burst_info);
			burst_info.src_addr += 32;
			burst_info.dst_addr += 32;
		}
	}
	if(mode==1)
	{
        for(i=0;i<burst_cnt;i++)
		{
	        BurstTransfer_N(&burst_info);
			burst_info.src_addr += 32;
			burst_info.dst_addr += 32;
		}
	}
}


#ifdef		ARM_BURST_PATTERN_SUPPORT_ON
const PI_SI_PATTERN_TYP pi_si_para=
{
	.magic_header = PI_SI_MAGIC_HEADER,
	.pi_si_case_num = PI_SI_CASE,
	.magic_end = PI_SI_MAGIC_END
};

void ddr_auto_slt_test(void)
{
    uint32 i;
	BurstBistInfo burst_info;

	REG32(0x30000030) = 0;

	while(1)
	{
		switch(pi_si_para.pi_si_case_num)
		{
		/*****************************pll/dll jitter*****************/
		case 1:
		//code1,no bist,no output
		REG32(0x3001006c) = 0xaaaaaaaa; //address oe off
		REG32(0x30010070) = 0x55555555; //address pdd on
		REG32(0x30010074) = 0xaaaaaa05; //cs/ras/cas/we/ba/par oe off
		REG32(0x30010078) = 0x55555550; //cs/ras/cas/we/ba/par pdd on
		REG32(0x3001007c) = 0x55550000; //cke/odt oe off, pdd on
		REG32(0x3001007c) |= 0x0000aaaa; //cke/odt oe off, pdd on
		REG32(0x30010284) = 0x55555555; //dq pdd on
		REG32(0x30010304) = 0x55555555; //dq pdd on
		REG32(0x30010384) = 0x55555555; //dq pdd on
		REG32(0x30010404) = 0x55555555; //dq pdd on
		REG32(0x30010288) = 0xaaaaaaaa; //dq pdd on
		REG32(0x30010308) = 0xaaaaaaaa; //dq pdd on
		REG32(0x30010388) = 0xaaaaaaaa; //dq pdd on
		REG32(0x30010408) = 0xaaaaaaaa; //dq pdd on

		REG32(0x3001028c) = 0xa5a5; //dqs/dm oe off, pdd on
		REG32(0x3001030c) = 0xa5a5; //dqs/dm oe off, pdd on
		REG32(0x3001038c) = 0xa5a5; //dqs/dm oe off, pdd on
		REG32(0x3001040c) = 0xa5a5; //dqs/dm oe off, pdd on
		break;

		case 2:
		//code2,bist, no output
		REG32(0x3001006c) = 0xaaaaaaaa; //address oe off
		REG32(0x30010070) = 0x55555555; //address pdd on
		REG32(0x30010074) = 0xaaaaaa05; //cs/ras/cas/we/ba/par oe off
		REG32(0x30010078) = 0x55555550; //cs/ras/cas/we/ba/par pdd on
		REG32(0x3001007c) = 0x55550000; //cke/odt oe off, pdd on
		REG32(0x3001007c) |= 0x0000aaaa; //cke/odt oe off, pdd on
		REG32(0x30010284) = 0x55555555; //dq pdd on
		REG32(0x30010304) = 0x55555555; //dq pdd on
		REG32(0x30010384) = 0x55555555; //dq pdd on
		REG32(0x30010404) = 0x55555555; //dq pdd on
		REG32(0x30010288) = 0xaaaaaaaa; //dq pdd on
		REG32(0x30010308) = 0xaaaaaaaa; //dq pdd on
		REG32(0x30010388) = 0xaaaaaaaa; //dq pdd on
		REG32(0x30010408) = 0xaaaaaaaa; //dq pdd on

		REG32(0x3001028c) = 0xa5a5; //dqs/dm oe off, pdd on
		REG32(0x3001030c) = 0xa5a5; //dqs/dm oe off, pdd on
		REG32(0x3001038c) = 0xa5a5; //dqs/dm oe off, pdd on
		REG32(0x3001040c) = 0xa5a5; //dqs/dm oe off, pdd on

		burst8_write_while1(0x0, 0xffffffff, 0x0, 0xffffffff,
		0x0, 0xffffffff, 0x0, 0xffffffff);
		break;

		case 3:
		//code3,bist, output
		burst8_write_while1(0x0, 0xffffffff, 0x0, 0xffffffff,
		0x0, 0xffffffff, 0x0, 0xffffffff);
		break;

		case 4:
		/******************** pi **********************/
		//code4, dq0=random...,others=0
		seed = REG32(0x30010038);
		SetSeed(seed);

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed & DQ0;
			}
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 5:
		//code5, dq0=random..., dq1,dq2,dq4=0, others=0101 0101...
		seed = REG32(0x30010038);
		SetSeed(seed);

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed & DQ0;
				if(i%2)
				{
					REG32(PATTERN_SRC_A+i*4) |= 0xffffffe8;
				}
				else
				{
					REG32(PATTERN_SRC_A+i*4) |= 0x00000000;
				}
			}
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 6:
		//code6, dq0=random..., dq1,dq2,dq4=0, others=0011 0011...
		seed = REG32(0x30010038);
		SetSeed(seed);

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed & DQ0;
				if((i==2) || (i==3) || (i==6) || (i==7))
				{
					REG32(PATTERN_SRC_A+i*4) |= 0xffffffe8;
				}
				else
				{
					REG32(PATTERN_SRC_A+i*4) |= 0x00000000;
				}
			}
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 7:
		//code7, dq31=random..., dq1,dq2,dq4=0, others=1111 0000...
		seed = REG32(0x30010038);
		SetSeed(seed);

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed & DQ0;
				if(i<4)
				{
					REG32(PATTERN_SRC_A+i*4) |= 0xffffffe8;
				}
				else
				{
					REG32(PATTERN_SRC_A+i*4) |= 0x00000000;
				}
			}
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 8:
		//code8 dq31=random..., dq1,dq2,dq4=0, others=11111111 00000000...
		seed = REG32(0x30010038);
		SetSeed(seed);

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 16*4;
		while(1)
		{
			for(i=0;i<16;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed & DQ0;
				if(i<8)
				{
					REG32(PATTERN_SRC_A+i*4) |= 0xffffffe8;
				}
			}
			burst8_move(&burst_info);
		}
		break;

		case 9:
		//code9, dq0=random..., dq1,dq2,dq4=0, others=si pattern(random now)
		seed = REG32(0x30010038);
		SetSeed(seed);
		//for(i=0;i<352;i++)
		//{
		//	REG32(PATTERN_SRC_A+i*4) = PATTERN_SIA_ARRAY[i];
		//}
		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			//here 352 is the PATTERN_SIA_ARRAY[] size
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed;		//random all
				REG32(PATTERN_SRC_A+i*4) &= 0xffffffe9;		//clear dq1 dq2 dq4
				//REG32(PATTERN_SRC_A+i*4) &= 0xffffffe8;		//clear dq0 dq1 dq2 dq4
				//REG32(PATTERN_SRC_A+i*4) |= seed & DQ0;		//random dq0

			}
			//burst8_move(&burst_info);
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 10:
		//code10, dq0=0..., dq1,dq2,dq4=0, others=si pattern(random now)
		seed = REG32(0x30010038);
		SetSeed(seed);
		//here 352 is the PATTERN_SIA_ARRAY[] size
		//for(i=0;i<352;i++)
		//{
		//	REG32(PATTERN_SRC_A+i*4) = PATTERN_SIA_ARRAY[i];
		//	REG32(PATTERN_SRC_A+i*4) &= 0xffffffe8; 	//clear dq0 dq1 dq2 dq4
		//}
		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed;		//random all
				REG32(PATTERN_SRC_A+i*4) &= 0xffffffe8;		//clear dq0 dq1 dq2 dq4
				//REG32(PATTERN_SRC_A+i*4) &= 0xffffffe8;		//clear dq0 dq1 dq2 dq4
				//REG32(PATTERN_SRC_A+i*4) |= seed & DQ0;		//random dq0

			}
			//burst8_move(&burst_info);
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 11:
		//code11, dq0=1..., dq1,dq2,dq4=0, others=si pattern(random now)
		seed = REG32(0x30010038);
		SetSeed(seed);
		//here 352 is the PATTERN_SIA_ARRAY[] size
		//for(i=0;i<8;i++)
		//{
			//REG32(PATTERN_SRC_A+i*4) = PATTERN_SIA_ARRAY[i];
			//REG32(PATTERN_SRC_A+i*4) &= 0xffffffe9; 	//clear  dq1 dq2 dq4
			//REG32(PATTERN_SRC_A+i*4) |= DQ0;
		//}
		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed;		//random all
				REG32(PATTERN_SRC_A+i*4) &= 0xffffffe8;		//clear dq1 dq2 dq4
				REG32(PATTERN_SRC_A+i*4) |= DQ0;		//set DQ0
			}
			//burst8_move(&burst_info);
			burst8_write_one_burst(&burst_info);
		}
		break;

		/******************** cross talk **********************/
		case 12:
		//code12,dq11=random..., others=0
		seed = REG32(0x30010038);
		SetSeed(seed);

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed & DQ11;
			}
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 13:
		//code13,dq11=random..., others=1
		seed = REG32(0x30010038);
		SetSeed(seed);

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed & DQ11;
				REG32(PATTERN_SRC_A+i*4) |= 0xfffff7ff;
			}
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 14:
		//code14, dq11=random..., dq8,dq9,dq10,dq12,dq13,dq14=si pattern(random now), others=0
		seed = REG32(0x30010038);
		SetSeed(seed);

		//for(i=0;i<352;i++)
		//{
		//	REG32(PATTERN_SRC_A+i*4) = PATTERN_SIA_ARRAY[i];
		//	REG32(PATTERN_SRC_A+i*4) &= 0x00007700;
		//}
		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed;	//random all
				REG32(PATTERN_SRC_A+i*4) &= 0x00007f00;		//clear others
				//REG32(PATTERN_SRC_A+i*4) &= 0x00007700;		//clear all other bits
				//REG32(PATTERN_SRC_A+i*4) |= seed & DQ11;
			}
			burst8_write_one_burst(&burst_info);
			//burst8_move(&burst_info);
		}
		break;

		case 15:
		//code15, dq11=random..., dq8,dq9,dq10,dq12,dq13,dq14=si pattern(random now), others=1
		seed = REG32(0x30010038);
		SetSeed(seed);

		//for(i=0;i<352;i++)
		//{
		//	REG32(PATTERN_SRC_A+i*4) = PATTERN_SIA_ARRAY[i];
		//	REG32(PATTERN_SRC_A+i*4) &= 0x00007700;
		//}
		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed;	//random all
				REG32(PATTERN_SRC_A+i*4) |= 0xffff80ff;		//set others
				//REG32(PATTERN_SRC_A+i*4) &= 0x00007700;
				//REG32(PATTERN_SRC_A+i*4) |= seed & DQ11;
				//REG32(PATTERN_SRC_A+i*4) |= 0xffff80ff;
			}
			burst8_write_one_burst(&burst_info);
			//burst8_move(&burst_info);
		}
		break;

		case 16:
		//code16, dq11=1...,others=0
		for(i=0;i<8;i++)
		{
			REG32(PATTERN_SRC_A+i*4) = 0x00000800;
		}

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 17:
		//code17, dq11=0...,others=1...
		for(i=0;i<8;i++)
		{
			REG32(PATTERN_SRC_A+i*4) = 0xfffff7ff;
		}

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 18:
		//code18, dq11=1..., dq8,dq9,dq10,dq12,dq13,dq14=si pattern(random now), others=0
		seed = REG32(0x30010038);
		SetSeed(seed);
		//for(i=0;i<352;i++)
		//{
		//	REG32(PATTERN_SRC_A+i*4) = PATTERN_SIA_ARRAY[i];
		//	REG32(PATTERN_SRC_A+i*4) &= 0x00007700;
		//	REG32(PATTERN_SRC_A+i*4) |= DQ11;
		//}

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed;	//random all
				REG32(PATTERN_SRC_A+i*4) &= 0x00007f00;		//clear others
				REG32(PATTERN_SRC_A+i*4) |= DQ11;		//set DQ11;
			}
			burst8_write_one_burst(&burst_info);
			//burst8_move(&burst_info);
		}
		break;

		case 19:
		//code19, dq11=0..., dq8,dq9,dq10,dq12,dq13,dq14=si pattern(random now), others=1
		seed = REG32(0x30010038);
		SetSeed(seed);
		//for(i=0;i<352;i++)
		//{
		//	REG32(PATTERN_SRC_A+i*4) = PATTERN_SIA_ARRAY[i];
		//	REG32(PATTERN_SRC_A+i*4) &= 0x00007700;
		//	REG32(PATTERN_SRC_A+i*4) |= 0xffff80ff;
		//}

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			for(i=0;i<8;i++)
			{
				seed = GetRandom();
				REG32(PATTERN_SRC_A+i*4) = seed;	//random all
				REG32(PATTERN_SRC_A+i*4) |= 0xffff80ff;		//set others
				REG32(PATTERN_SRC_A+i*4) &= ~(DQ11);		//clear DQ11;
			}
			burst8_write_one_burst(&burst_info);
			//burst8_move(&burst_info);
		}
		break;

		/********************* isi ***********************/
		case 20:
		//code20, dq11=1110,1110,,other=0
		for(i=0;i<8;i++)
		{
			if((i==3) || (i==7))
			{
				REG32(PATTERN_SRC_A+i*4) = 0x00000000;
			}
			else
			{
				REG32(PATTERN_SRC_A+i*4) = 0x00000800;
			}
		}

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 21:
		//code21, dq11=1110,1110,other=1
		for(i=0;i<8;i++)
		{
			if((i==3) || (i==7))
			{
				REG32(PATTERN_SRC_A+i*4) = 0xfffff7ff;
			}
			else
			{
				REG32(PATTERN_SRC_A+i*4) = 0xffffffff;
			}
		}

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 22:
		//code22, dq11=1010,1010, other=0
		for(i=0;i<8;i++)
		{
			if(i%2)
			{
				REG32(PATTERN_SRC_A+i*4) = 0x00000800;
			}
			else
			{
				REG32(PATTERN_SRC_A+i*4) = 0x00000000;
			}
		}

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			burst8_write_one_burst(&burst_info);
		}
		break;

		case 23:
		//code23, dq11=1010,1010, other=1
		for(i=0;i<8;i++)
		{
			if(i%2)
			{
				REG32(PATTERN_SRC_A+i*4) = 0xffffffff;
			}
			else
			{
				REG32(PATTERN_SRC_A+i*4) = 0xfffff7ff;
			}
		}

		burst_info.src_addr = PATTERN_SRC_A;
		burst_info.dst_addr = PATTERN_DST;
		burst_info.data_len = 8*4;
		while(1)
		{
			burst8_write_one_burst(&burst_info);
		}
		break;

		}
	}
}
#endif

#ifdef PRODUCT_AUTO_SLT_CODE_SUPPORT_ON
uint32 test_len=0x100000;
uint32 burst_test_len=0x1800;   //6k iram 8k max
uint32 src_buf = 0x00000000;
uint32 dst_buf = 0x80000000;
uint32 src1,src2,dst1,dst2;

void ddr_auto_slt_test()
{
	uint32 i,j;
	uint32 value,Nvalue;
	uint32 count=2;

	REG32(0x1f10) = REG32(0x4023000c);   // start time count

	//UART 9600
	REG32(0x70100024) = 0xa94;
	REG32(0x70100028) = 0x0a;

	ddr_print("REV: SHARKL64-V1\r\n");
	//ddr_print("REV: SC7731G/SC7730S-V3\r\n");

	while(count>1)
	{
    count--;
	REG32(0x1f00) = 0x00000000;

	// single test
	//case2 walking ones and walking zeros addr flip
    for(i=0;i<test_len;i+=0x80)
    {
        for(j=0;j<32;j++)
        {
	        REG32(0x80000000+ (i+j*4)) = 0xffffffff ^ (1<<j);
			REG32(0x8ffffffc- (i+j*4)) = 0x00000000 | (1<<j);
        }

		for(j=0;j<32;j++)
        {
	        if((value = REG32(0x80000000+ (i+j*4))) != (0xffffffff ^ (1<<j)))
	        {
                REG32(0x1e00) = value;
				REG32(0x1f0c) = i;
				ddr_print("ERRORCODE=FAIL2 DDR");
				while(1);
               // test_flag = 0;
			   // return FALSE;
		    }

			if((value = REG32(0x8ffffffc- (i+j*4))) != (0x00000000 | (1<<j)))
	        {
                REG32(0x1e04) = value;
				REG32(0x1f0c) = i;
				ddr_print("ERRORCODE=FAIL2 DDR");
				while(1);
               // test_flag = 0;
			   // return FALSE;
		    }
        }
	}

	//case3 write address addr flip data flip
    for(i=0;i<test_len;i+=4)
    {
        REG32(0x80000000+i) = 0x80000000+i;
		REG32(0x8ffffffc-i) = 0x8ffffffc-i;
	}

	for(i=0;i<test_len;i+=4)
	{
        if((value = REG32(0x80000000+i))!=0x80000000+i)
        {
            REG32(0x1e08) = value;
			REG32(0x1f0c) = i;
			ddr_print("ERRORCODE=FAIL2 DDR");
			while(1);
            //test_flag = 0;
			//return FALSE;
		}
		if((value = REG32(0x8ffffffc-i))!=0x8ffffffc-i)
        {
            REG32(0x1e0c) = value;
			REG32(0x1f0c) = i;
			ddr_print("ERRORCODE=FAIL2 DDR");
			while(1);
            //test_flag = 0;
			//return FALSE;
		}
	}

	//case5 write after read  and read after write burst
    src1 = 0x80000000;
    dst1 = 0x83000000;
	src2 = 0x8ffffffc - test_len +4;
	dst2 = 0x87000000;

    __burst8_rw(src1,dst1,test_len,1);
	__burst8_rw(src2,dst2,test_len,1);

	for(i=0;i<test_len;i+=4)
	{
        if((value = REG32(0x83000000 + i)) != (~(REG32(0x80000000+i))))
        {
            REG32(0x1e24) = value;
			REG32(0x1f0c) = i;
			ddr_print("ERRORCODE=FAIL2 DDR");
			while(1);
		}

		if((value = REG32(0x87000000 - 4 + test_len - i)) != (~(REG32(0x8ffffffc-i))))
        {
            REG32(0x1e28) = value;
			REG32(0x1f0c) = i;
			ddr_print("ERRORCODE=FAIL2 DDR");
			while(1);
		}
	}

	//case7 long time access one row
    seed = REG32(0x30010038);
    SetSeed(seed);
	for(j=0;j<1000;j++)
	{
	    for(i=0;i<0xf8;i+=4)
	    {
	        seed = GetRandom();
	        REG32(0x80000000+i) = seed;
			REG32(0x800000f8+i) = seed;
		}
	}

	for(i=0;i<0xf8;i+=4)
	{
        if(REG32(0x80000000+i) != REG32(0x800000f8+i))
        {
			REG32(0x1E30) = i;
			ddr_print("ERRORCODE=FAIL2 DDR");
			while(1);
        }
	}

	//case8 ddr device cap fast charge decharge flip test
	for(i=0;i<test_len;i+=4)
	{
		for(j=5;j<0xc;j++)
		{
		    value = (j<<28)|(j<<24)|(j<<20)|(j<<16)|(j<<12)|(j<<8)|(j<<4)|(j<<0);

		    REG32(0X80000000+i) = value;
			REG32(0X80000000+i) = ~value;
			REG32(0X80000000+i) = value;
			REG32(0X80000000+i) = ~value;
		}

		Nvalue = ~value;
	    value = REG32(0X80000000+i);

		if(value != Nvalue)
		{
	        REG32(0x1e34) = value;
			REG32(0x1f0c) = i;
			ddr_print("ERRORCODE=FAIL2 DDR");
			while(1);
		}
	}

	//case9 burst write data squential test
	burst8_write_all(0xff00ff00,0x80000000,test_len);

	for(i=0;i<test_len;i+=4)
	{
        if(i%8)
        {
			if((value = REG32(0x80000000+i)) != 0x00ff00ff)
			{
	            REG32(0x1e38) = value;
			    REG32(0x1f0c) = i;
				ddr_print("ERRORCODE=FAIL2 DDR");
			    while(1);
			}
        }
		else
		{
            if((value = REG32(0x80000000+i)) != 0xff00ff00)
			{
	            REG32(0x1e3c) = value;
			    REG32(0x1f0c) = i;
				ddr_print("ERRORCODE=FAIL2 DDR");
			    while(1);
			}
		}
	}

    //ddr_print("ERRORCODE=PASS");
    REG32(0x1f00) = 0xffffffff;
	REG32(0x1f14) = REG32(0x4023000c);   // end time count

	}

   ddr_print("ERRORCODE=PASS DDR");
}
#endif

#ifdef DDR_REBOOT_TEST

#define ANA_REG_GLB_MCU_WR_PROT_VALUE   0x4003894c
#define ANA_REG_GLB_ARM_MODULE_EN	0x40038800
#define ANA_REG_GLB_RTC_CLK_EN		0x40038808

#define WDG_CTRL                0x40038048
#define WDG_LOAD_LOW            0x40038040
#define WDG_LOAD_HIGH           0x40038044
#define WDG_LOCK	        0x40038860

#define WDG_UNLOCK_KEY		0xE551
#define ANA_REG_GLB_PWR_WR_PROT_VALUE        0x40038950
#define ANA_REG_GLB_LDO_DCDC_PD 0x40038810

void __wdg_reset()
{
	volatile uint32 reg_val = 0;
	volatile uint32 reg_val_pd = 0;
#if 0
	/*unlock arch enable*/
	ANA_REG_SET(ANA_REG_GLB_MCU_WR_PROT_VALUE,0x3c4d);
	while((ANA_REG_GET(ANA_REG_GLB_MCU_WR_PROT_VALUE) & 0x8000) == 0x0);
#else
        /*unlock arch enable*/
        ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE,0x6e7f);

	reg_val_pd = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD);
	reg_val_pd |= (1<<7);
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD,reg_val_pd);

        wait_pclk(10000);

        reg_val_pd = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD);
        reg_val_pd &= ~(1<<7);
        ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD,reg_val_pd);

	wait_pclk(10000);
#endif
	/*first enable ana watch module*/
	reg_val = ANA_REG_GET(ANA_REG_GLB_ARM_MODULE_EN);
	reg_val |= (1 << 2);
	ANA_REG_SET(ANA_REG_GLB_ARM_MODULE_EN,reg_val);
	reg_val = ANA_REG_GET(ANA_REG_GLB_RTC_CLK_EN);
	reg_val |= (1 << 2);
	ANA_REG_SET(ANA_REG_GLB_RTC_CLK_EN,reg_val);

	/*second unlock watch module*/
	ANA_REG_SET(WDG_LOCK,0xe551);

	/*polling watchdog lock status*/
	//while((ANA_REG_GET(ANA_WTG_BASE+0x20) & 0x1) == 0x0);

	/*third load watch count*/
	ANA_REG_SET(WDG_LOAD_HIGH,0x0);
	ANA_REG_SET(WDG_LOAD_LOW,0x10);

	/*forth watchdog run and reset enable*/
	ANA_REG_SET(WDG_CTRL,0xe);

	/*lock watchdog for safe*/
	ANA_REG_SET(WDG_LOCK,0x0000);
}

void start_watchdog(uint32_t init_time_ms)
{
	//WDG_ClockOn();
    //WDG_ResetMCU();

	__wdg_reset();
}


#endif

#ifdef DDR_DCU_SUPPORT_ON
const DCU_PATTERN_TYP dcu_para=
{
	.magic_header = DCU_MAGIC_END,
	.dcu_pattern0[0] = 0x00000000, .dcu_pattern0[1] = 0x00000000, .dcu_pattern0[2] = 0x00000000, .dcu_pattern0[3] = 0x00000000,
	.dcu_pattern1[0] = 0x11111111, .dcu_pattern1[1] = 0x11111111, .dcu_pattern1[2] = 0x11111111, .dcu_pattern1[3] = 0x11111111,
	.dcu_pattern2[0] = 0x22222222, .dcu_pattern2[1] = 0x22222222, .dcu_pattern2[2] = 0x22222222, .dcu_pattern2[3] = 0x22222222,
	.dcu_pattern3[0] = 0x33333333, .dcu_pattern3[1] = 0x33333333, .dcu_pattern3[2] = 0x33333333, .dcu_pattern3[3] = 0x33333333,
	.dcu_pattern4[0] = 0x44444444, .dcu_pattern4[1] = 0x44444444, .dcu_pattern4[2] = 0x44444444, .dcu_pattern4[3] = 0x44444444,
	.dcu_pattern5[0] = 0x55555555, .dcu_pattern5[1] = 0x55555555, .dcu_pattern5[2] = 0x55555555, .dcu_pattern5[3] = 0x55555555,
	.dcu_pattern6[0] = 0x66666666, .dcu_pattern6[1] = 0x66666666, .dcu_pattern6[2] = 0x66666666, .dcu_pattern6[3] = 0x66666666,
	.dcu_pattern7[0] = 0x77777777, .dcu_pattern7[1] = 0x77777777, .dcu_pattern7[2] = 0x77777777, .dcu_pattern7[3] = 0x77777777,
	.magic_end = DCU_MAGIC_HEADER
};

static uint32 cache_word[6];

DCU_CMD_CACHE_TYP dcu_cmd_precharge = {
	.rpt		=	0,
	.dtp		=	20,
	.tag		=	0,
	.cmd		=	4,
	.rank		=	0,
	.bank		=	0,
	.addr		=	0,
	.mask		=	0,
	.data[0]	=	0,
	.data[1]	=	0,
	.data[2]	=	0,
	.data[3]	=	0,
};

DCU_CMD_CACHE_TYP dcu_cmd_active = {
	.rpt		=	0,
	.dtp		=	21,
	.tag		=	0,
	.cmd		=	6,
	.rank		=	0,
	.bank		=	0,
	.addr		=	0,
	.mask		=	0,
	.data[0]	=	0,
	.data[1]	=	0,
	.data[2]	=	0,
	.data[3]	=	0,
};

DCU_CMD_CACHE_TYP dcu_cmd_write = {
	.rpt		=	0,
	.dtp		=	28,
	.tag		=	0,
	.cmd		=	8,
	.rank		=	0,
	.bank		=	0,
	.addr		=	0,
	.mask		=	0,
	.data[0]	=	0,
	.data[1]	=	0,
	.data[2]	=	0,
	.data[3]	=	0,
};
//rpt:[3 -1:0]   dtp:[5 -1:0]	  tag:[2 -1:0]   cmd:[4 -1:0]   rank:[0:0]
//bank[3 -1:0]   addr:[16 -1:0]   mask[16 -1:0]   data[128 -1:0]

/*cmd cache reg description :
-----------------------------------
cache_word[0] [31:0]
data[0] : [31:0]
-----------------------------------
cache_word[1] [31:0]
data[1] : [31:0]
-----------------------------------
cache_word[2] [31:0]
data[2] : [31:0]
-----------------------------------
cache_word[3] [31:0]
data[3] : [31:0]
-----------------------------------
cache_word[4] [31:0]
addr : [31:16]
mask : [15:0]
-----------------------------------
cache_word[5] [31:0]
rpt : [17:15]
dtp : [14:10]
tag : [9:8]
cmd : [7:4]
rank : [3:3]
bank : [2:0]
*/
void dcu_cmd_generator(DCU_CMD_CACHE_TYP* dcu_cmd_struct, uint32* data_pattern)
{
	uint32 i;

	for(i=0;i<4;i++)
	{
		dcu_cmd_struct->data[i] = data_pattern[i];
	}

	cache_word[5] = dcu_cmd_struct->rpt<<15 | dcu_cmd_struct->dtp<<10 | dcu_cmd_struct->tag<<8 |
					dcu_cmd_struct->cmd<<4 | dcu_cmd_struct->rank<<3 | dcu_cmd_struct->bank<<0;
	cache_word[4] = dcu_cmd_struct->mask | dcu_cmd_struct->addr<<16;
	cache_word[3] = dcu_cmd_struct->data[0];
	cache_word[2] = dcu_cmd_struct->data[1];
	cache_word[1] = dcu_cmd_struct->data[2];
	cache_word[0] = dcu_cmd_struct->data[3];
}

void load_dcu_cmd(uint32 *cache_word_load)
{
	uint32 slice;

	for(slice=0;slice<6;slice++)
	{
		publ->publ_dcudr = cache_word_load[slice];
	}
}

void ddr_auto_slt_test(void)
{
	uint32 slice_num;

	umctl->umctl_rfshctl3 |= 1;
	umctl->umctl_dfiupd[0] |= 1<<31;

	publ->publ_dcutpr = 4;
	publ->publ_dcuar = 1<<10;		//set cache addr incremental

	dcu_cmd_generator(&dcu_cmd_precharge,&dcu_para.dcu_pattern0);
	load_dcu_cmd(cache_word);
	dcu_cmd_generator(&dcu_cmd_active,&dcu_para.dcu_pattern0);
	load_dcu_cmd(cache_word);

	//case1  all 01010101 01010101
	dcu_cmd_generator(&dcu_cmd_write,&dcu_para.dcu_pattern0);
	load_dcu_cmd(cache_word);
	dcu_cmd_generator(&dcu_cmd_write,&dcu_para.dcu_pattern1);
	load_dcu_cmd(cache_word);

	dcu_cmd_generator(&dcu_cmd_write,&dcu_para.dcu_pattern2);
	load_dcu_cmd(cache_word);
	dcu_cmd_generator(&dcu_cmd_write,&dcu_para.dcu_pattern3);
	load_dcu_cmd(cache_word);

	dcu_cmd_generator(&dcu_cmd_write,&dcu_para.dcu_pattern4);
	load_dcu_cmd(cache_word);
	dcu_cmd_generator(&dcu_cmd_write,&dcu_para.dcu_pattern5);
	load_dcu_cmd(cache_word);

	dcu_cmd_generator(&dcu_cmd_write,&dcu_para.dcu_pattern6);
	load_dcu_cmd(cache_word);
	dcu_cmd_generator(&dcu_cmd_write,&dcu_para.dcu_pattern7);
	load_dcu_cmd(cache_word);

	publ->publ_dculr = 0;
	publ->publ_dculr = (2<<0) | (9<<4) | (1<<16) | (1<<17);

	publ->publ_dcurr = (0<<4) | (9<<8) | (1<<0);

	while(1);
}
#endif

#ifdef DDR_BIST_TEST_SUPPORT_ON
void ddr_phy_bist_init()
{
	uint32 cs_num;

	cs_num = REG32(DDR_DFS_VAL_BASE);

	//set bist address
	publ->publ_bistar[0] = 0;

#if defined(DDR_LPDDR2)
    publ->publ_bistar[1] = 0x40;	//BL=4 addr incremental X00
    publ->publ_bistar[1] |= (cs_num-1)<<2;
	publ->publ_bistar[2] = 0x7000f3fc;	//end of addr to switch col, row and bank

	//set bist data length
	publ->publ_bistwcr = 0xfffe;
#endif

#if defined(DDR_LPDDR3)
    publ->publ_bistar[1] = 0x80;	//BL=8 addr incremental X000
    publ->publ_bistar[1] |= (cs_num-1)<<2;
	publ->publ_bistar[2] = 0x7000f3f8;	//end of addr to switch col, row and bank

	//set bist data length
	publ->publ_bistwcr = 0xfffc;
	
#endif

	//set bist mode register
	publ->publ_bistrr |= 1<<3;		//0:loopback mode  1:dram mode
	publ->publ_bistrr |= 1<<4;		//infinit run
	publ->publ_bistrr |= 1<<13;		//sotp if fail
	publ->publ_bistrr |= 1<<14;		//bist data compare
	publ->publ_bistrr |= 2<<17;		//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user

	publ->publ_bistlsr = 0x2345abcd;

	publ->publ_dtcr &= ~(0xf<<28);
	publ->publ_dtcr |= (0x2<<28);

	//config refresh timing for phy at 667M
	publ->publ_pgcr[2] &= ~(0x3ffff<<0);
	publ->publ_pgcr[2] |= (0x1452<<0);
	//bypass static read fifo
	publ->publ_pgcr[3] &= ~(0x1000018);
	//close auto selfrefresh
	umctl->umctl_rfshctl3 |= 1;
}

uint32 publ_bist_run(uint32 byte_run)
{
	uint32 i;
	uint32 count=0;
	uint32 result;

	//bist reset
	publ->publ_bistrr &= ~(7<<0);
	publ->publ_bistrr |= 3<<0;
	//select which byte to run
	publ->publ_bistrr &= ~(0xf<<19);
	publ->publ_bistrr |= byte_run<<0;
	//run bist
	publ->publ_bistrr &= ~(7<<0);
	publ->publ_bistrr |= 1<<0;

	for(i=0;i<1000;i++);

	while((publ->publ_bistgsr &0x4) == 0)
	{
		wait_pclk(1000);		//wait 1000 count 1000= 1s
		count++;
		if(count==1000)
		{
			break;
		}
	}
	
	if((publ->publ_bistgsr &0x4) == 0x4)
	{
		//error code
		result = 1;
	}
	else
	{
		result = 0;
	}

	//bist stop
	publ->publ_bistrr &= ~(7<<0);
	publ->publ_bistrr |= 2<<0;
	//reset phy
	publ->publ_pgcr[1] &= ~(1<<25);
	for(i=0;i<1000;i++);

	return result;
}

void ddr_auto_slt_test(void)
{
	uint32 i;
	uint32 count;

	for(i=0;i<4;i++)
	{
		REG32(DEBUG_INFO_BASE+i*4) = 0x00000000;		//test fail
	}
	REG32(DEBUG_INFO_BASE + 0x10) = 0x00000000;
	ddr_phy_bist_init();

	for(count=0;count<45;count++)
	{
		for(i=0;i<4;i++)
		{
			if(i%2)
			{
				publ->publ_bistlsr = 0x2345abcd;
			}
			else
			{
				publ->publ_bistlsr = 0xdcba5432;
			}
			if(publ_bist_run(i))
			{
				REG32(DEBUG_INFO_BASE+i*4) = 0x11111111;		//test fail
				REG32(DEBUG_INFO_BASE+0x10) = 0x11111111;
				goto out;
			}
			else
			{
				REG32(DEBUG_INFO_BASE+i*4) = 0xffffffff;		//test ok
			}
		}
	}

	REG32(DEBUG_INFO_BASE + 0x10) = 0xffffffff;

out:
	//dis reset phy
	publ->publ_pgcr[1] |= (1<<25);
	//open static read fifo
	publ->publ_pgcr[3] |=  (0x1000018);
	//enable auto selfrefresh
	umctl->umctl_rfshctl3 &= ~1;

}

#endif


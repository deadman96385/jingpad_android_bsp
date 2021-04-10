/******************************************************************************
** File Name:      umctl2_28nm.c                                             *
** Author:         kui.wang                                                  *
** DATE:           02/11/2014                                                *
** Copyright:      2010 Spreatrum, Incoporated. All Rights Reserved.         *
** Description:    Refer to uMCTL2 databook for detail                       *
******************************************************************************

******************************************************************************
**                        Edit History                                       *
** ------------------------------------------------------------------------- *
** DATE           NAME             DESCRIPTION                               *
** 02/11/2014     kui.wang       	 Create.                             *
******************************************************************************/
#include <common.h>
#include "dram_phy_28nm.h"
#include "asm/arch/clk_para_config.h"
#include <adi.h>


#ifdef CONFIG_SPX30G
#include "asm/arch/chip_x30g/__hardware-sc8830.h"
#include <power/pmic_glb_reg.h>
#endif

/**---------------------------------------------------------------------------*
 **                            Macro Define
 **---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*
 **                            LOCAL Variables
 **---------------------------------------------------------------------------*/
static DRAM_TYPE_E DDR_TYPE_LOCAL;
static DMC_UMCTL_REG_INFO_PTR_T umctl = (DMC_UMCTL_REG_INFO_PTR_T)0x30000000;
static DMC_PUBL_REG_INFO_PTR_T publ = (DMC_PUBL_REG_INFO_PTR_T)0x30010000;
static volatile unsigned int ddr_core_clk;
//MEM_IODS_E MEM_IO_DS = LPDDR2_DS_40R;
#define REG_AON_TOP_DDR_SLEEP_CTRL	0x402b00d0
#define REG_AON_TOP_DDR_CHN_SLEEP_CTRL0	0x402b00f8
#define REG_AON_TOP_DDR_OP_MODE_CFG	0x402b012c
#define REG_AON_TOP_DDR_PHY_RET_CFG	0x402b0130
#define DDR3_DLL_ON	1
#define PHY_PLL_BYPASS	1
//typedef unsigned int uint32;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#ifdef CONFIG_SCX35LT8
#define DDR_AUTO_DETECT_INFO_BASE	0x101f00
#else
#define DDR_AUTO_DETECT_INFO_BASE	0x1f00
#endif

dram_timing_t DDR_TIMING_INFO[] =
{
#ifdef DDR_LPDDR2
	{CLK_200MHZ, //ddr_clk
	 0x0d0B0D0A, //dramtmg0
	 DRAMTMG_1_200M, //dramtmg1
	 0x03060B09, //dramtmg2
	 0x00502000, //dramtmg3
	 DRAMTMG_4_200M, //dramtmg4
	 0x02020303, //dramtmg5
	 0x02020005, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000202, //dramtmg8
	 0x00180025, //rfshtmg_s
	 0x0018002c, //rfshtmg_l     /*for 1 cs 8g DDR */
	 0x00280001, //init0
	 0x00000000, //init1
	 0x00000705, //init2
	 0x00220004, //init3
#ifdef CONFIG_SP8830GEA
	 0x00030000, //init4
#else
	 0x00020000, //init4
#endif
	 0x00070002, //init5
	 0x06040000, //dfitmg0
	 0x00000022, //mr1
	 0x00000004,  //mr2
	 0x00000000, //odtcfg
	 0xe0480012, //zqctl0
	 0x00A0E4E2, //zqctl1
	 },

	{CLK_384MHZ, //ddr_clk
	 0x0F161B13, //dramtmg0
	 DRAMTMG_1_384M, //dramtmg1
	 0x03060A0A, //dramtmg2
	 0x00502000, //dramtmg3
	 DRAMTMG_4_384M, //dramtmg4
	 0x02020707, //dramtmg5
	 0x02020006, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000303, //dramtmg8
	 0x002E0035, //rfshtmg_s
	 0x002e0053, //rfshtmg_l	   /*for 1 cs 8g DDR */
	 0x004F0001, //init0
	 0x00000000, //init1
	 0x00000D05, //init2
	 0x00820004, //init3
#ifdef CONFIG_SP8830GEA
	 0x00030000, //init4
#else
	 0x00020000, //init4
#endif
	 0x000D0004, //init5
	 0x06040000, //dfitmg0
	 0x00000082, //mr1
	 0x00000004, //mr2
	 0x00000000, //odtcfg
	 0xe08B0023, //zqctl0
	 0x0141B775, //zqctl1
	 },


	{CLK_400MHZ, //ddr_clk
	 0x0F161B13, //dramtmg0
	 DRAMTMG_1_400M, //dramtmg1
	 0x03060A0A, //dramtmg2
	 0x00502000, //dramtmg3
	 DRAMTMG_4_400M, //dramtmg4
	 0x02020707, //dramtmg5
	 0x02020006, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000303, //dramtmg8
	 0x00300036, //rfshtmg_s
	 0x00300056, //rfshtmg_l     /*for 1 cs 8g DDR */
	 0x004F0001, //init0
	 0x00000000, //init1
	 0x00000D05, //init2
	 0x00820004, //init3
#ifdef CONFIG_SP8830GEA
	 0x00030000, //init4
#else
	 0x00020000, //init4
#endif
	 0x000D0004, //init5
	 0x06040000, //dfitmg0
	 0x00000082, //mr1
	 0x00000004, //mr2
	 0x00000000, //odtcfg
	 0xe0900024, //zqctl0
	 0x0141C9C4, //zqctl1
	 },

	{CLK_466MHZ, //ddr_clk
	 0x12191F15, //dramtmg0
	 DRAMTMG_1_466M, //dramtmg1
	 0x04070A0C, //dramtmg2
	 0x00502000, //dramtmg3
	 DRAMTMG_4_466M, //dramtmg4
	 0x02020808, //dramtmg5
	 0x02020007, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000404, //dramtmg8
	 0x00380041, //rfshtmg_s
	 0x00380064, //rfshtmg_l
	 0x005C0001, //init0
	 0x00000000, //init1
	 0x00000F05, //init2
	 0x00A20005, //init3
#ifdef CONFIG_SP8830GEA
	 0x00030000, //init4
#else
	 0x00020000, //init4
#endif
	 0x000F0005, //init5
	 0x06040002, //dfitmg0
	 0x000000A2, //mr1
	 0x00000005, //mr2
	 0x00000000, //odtcfg
	 0xe0A8002A, //zqctl0
	 0x0182154c, //zqctl1
	},

	{CLK_500MHZ, //ddr_clk
	 0x0F1A2217, //dramtmg0
	 DRAMTMG_1_500M, //dramtmg1
	 0x04070A0B, //dramtmg2
	 0x00502000, //dramtmg3
	 DRAMTMG_4_500M, //dramtmg4
	 0x02020808, //dramtmg5
	 0x02020007, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000404, //dramtmg8
	 0x003C0041, //rfshtmg_s
	 0x003C0069, //rfshtmg_l     /*for 1 cs 8g DDR */
	 0x00620001, //init0
	 0x00000000, //init1
	 0x00001005, //init2
	 0x00C20005, //init3
	 0x00020000, //init4
	 0x00100005, //init5
	 0x06040002, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x000000C2, //mr1
	 0x00000005,  //mr2
	 0x00000000, //odtcfg
	 0xe0B4002d, //zqctl0
	 0x01923c35, //zqctl1
	 },

	{CLK_533MHZ, //ddr_clk
	0x0F1C2419, //dramtmg0
	0x00050527, //dramtmg1
	0x04080B0B, //dramtmg2
	0x00502000, //dramtmg3
	0x0D020810, //dramtmg4
	0x02020808, //dramtmg5
	0x02020007, //dramtmg6
	0x00000202, //dramtmg7
	0x00000404, //dramtmg8
	0x00400046, //rfshtmg_s
	0x00400070, //rfshtmg_l
	0x00690001, //init0
	0x00000000, //init1
	0x00001105, //init2
	0x00C20006, //init3
#ifdef CONFIG_SP8830GEA
	0x00030000, //init4
#else
	0x00020000, //init4
#endif
	0x00110006, //init5
	0x06060002, //dfitmg0
	0x000000C2, //mr1
	0x00000006, //mr2
	0x00000000, //odtcfg
	0xe0c00030, //zqctl0
	0x01b2b1f9, //zqctl1
	},
#endif

#ifdef DDR_LPDDR3

#ifndef CONFIG_SPX30G
    {CLK_192MHZ, //ddr_clk
	 0x0E0A0D09, //dramtmg0
	 DRAMTMG_1_192M, //dramtmg1
	 0x03060A0C, //dramtmg2
	 0x00A0A000, //dramtmg3
	 DRAMTMG_4_192M, //dramtmg4
	 0x02020303, //dramtmg5
	 0x02020005, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000202, //dramtmg8
	 0x0017001b, //rfshtmg_s
	 0x0017002b, //rfshtmg_l	   /*for 1 cs 8g DDR */
	 0x00260001, //init0
	 0x00000000, //init1
	 0x00000605, //init2
	 0x00830004, //init3
	 0x00020000, //init4
	 0x00060002, //init5
	 0x06040000, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x00000083, //mr1
	 0x00000004,  //mr2
	 0x07020714, //odtcfg
	 0xe0460012, //zqctl0
	 0x00A0DBBB, //zqctl1
	 },
#endif
    {CLK_200MHZ, //ddr_clk
	 0x0E0A0D09, //dramtmg0
	 DRAMTMG_1_200M, //dramtmg1
	 0x03060A0C, //dramtmg2
	 0x00A0A000, //dramtmg3
	 DRAMTMG_4_200M, //dramtmg4
	 0x02020303, //dramtmg5
	 0x02020005, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000202, //dramtmg8
	 0x0018001c, //rfshtmg_s
	 0x0018002c, //rfshtmg_l     /*for 1 cs 8g DDR */
	 0x00280001, //init0
	 0x00000000, //init1
	 0x00000705, //init2
	 0x00830004, //init3
	 0x00020000, //init4
	 0x00070002, //init5
	 0x06040000, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x00000083, //mr1
	 0x00000004,  //mr2
	 0x07020714, //odtcfg
	 0xe0480012, //zqctl0
	 0x00A0E4E2, //zqctl1
	 },
#ifndef CONFIG_SPX30G
     {CLK_384MHZ, //ddr_clk
	 0x0F141A11, //dramtmg0
	 DRAMTMG_1_384M, //dramtmg1
	 0x03060B0C, //dramtmg2
	 0x00A0A000, //dramtmg3
	 DRAMTMG_4_384M, //dramtmg4
	 0x02020606, //dramtmg5
	 0x02020005, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000303, //dramtmg8
	 0x002E0034, //rfshtmg_s
	 0x002e0053, //rfshtmg_l	   /*for 1 cs 8g DDR */
	 0x004B0001, //init0
	 0x00000000, //init1
	 0x00000C05, //init2
	 0x00830004, //init3
	 0x00020000, //init4
	 0x000C0004, //init5
	 0x06040000, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x00000083, //mr1
	 0x00000004, //mr2
	 0x08020814, //odtcfg
	 0xe08B0023, //zqctl0
	 0x0141B775, //zqctl1
	 },
#endif
     {CLK_400MHZ, //ddr_clk
	 0x0F141B12, //dramtmg0
	 DRAMTMG_1_400M, //dramtmg1
	 0x03060B0C, //dramtmg2
	 0x00A0A000, //dramtmg3
	 DRAMTMG_4_400M, //dramtmg4
	 0x02020606, //dramtmg5
	 0x02020005, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000303, //dramtmg8
	 0x00300036, //rfshtmg_s
	 0x00300056, //rfshtmg_l     /*for 1 cs 8g DDR */
	 0x004F0001, //init0
	 0x00000000, //init1
	 0x00000D05, //init2
	 0x00830004, //init3
	 0x00020000, //init4
	 0x000D0004, //init5
	 0x06040000, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x00000083, //mr1
	 0x00000004, //mr2
	 0x08020814, //odtcfg
	 0xe0900024, //zqctl0
	 0x0141C9C4, //zqctl1
	 },
     {CLK_500MHZ, //ddr_clk
	 0x12192216, //dramtmg0
	 DRAMTMG_1_500M, //dramtmg1
	 0x04080C0D, //dramtmg2
	 0x00A0A000, //dramtmg3
	 DRAMTMG_4_500M, //dramtmg4
	 0x02020808, //dramtmg5
	 0x02020006, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000404, //dramtmg8
	 0x003C0043, //rfshtmg_s
	 0x003C006b, //rfshtmg_l     /*for 1 cs 8g DDR */
	 0x00620001, //init0
	 0x00000000, //init1
	 0x00001005, //init2
	 0x00C30006, //init3
	 0x00020000, //init4
	 0x00100005, //init5
	 0x06060002, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x000000C3, //mr1
	 0x00000006,  //mr2
	 0x0803081c, //odtcfg
	 0xe0B4002d, //zqctl0
	 0x01923c35, //zqctl1
	 },

	//add for pikel 533
	  {CLK_533MHZ, //ddr_clk
	   0x141B2418, //dramtmg0
	   DRAMTMG_1_533M, //dramtmg1
	   0x04080c0d, //dramtmg2
	   0x00a0a000, //dramtmg3
	   DRAMTMG_4_533M, //dramtmg4
	   0x02020808, //dramtmg5
	   0x02020006, //dramtmg6
	   0x00000202, //dramtmg7
	   0x00000404, //dramtmg8
	   0x00400048, //rfshtmg_s
	   0x00400072, //rfshtmg_l	   /*for 1 cs 8g DDR */
	   0x00690001, //init0
	   0x00000000, //init1
	   0x00001105, //init2
	   0x00C30006, //init3
	   0x00020000, //init4
	   0x00110006, //init5
	   0x06060002, //dfitmg0
	  //   0x00030202, //dfitmg1
	   0x000000C3, //mr1
	   0x00000006,	//mr2
	   0x0803081C, //odtcfg
	   0xe0c00030, //zqctl0
	   0x01b261f9, //zqctl1
	   },

#if defined(CONFIG_SC9630) || defined(CONFIG_SCX35L64)
	{CLK_600MHZ, //ddr_clk
	 0x141e291b, //dramtmg0
	 DRAMTMG_1_600M, //dramtmg1
	 0x05090D0f, //dramtmg2
	 0x00A0A000, //dramtmg3
	 DRAMTMG_4_600M, //dramtmg4
	 0x02020909, //dramtmg5
	 0x02020007, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000505, //dramtmg8
	 0x0049004e, //rfshtmg_s
	 0x0049007e, //rfshtmg_l    /*for 1 cs 8g DDR */
	 0x00760001, //init0
	 0x00000000, //init1
	 0x00001305, //init2
	 0x00e30007, //init3
	 0x00020000, //init4
	 0x00130006, //init5
	 0x06060002, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x000000e3, //mr1
	 0x00000007,  //mr2
	 0x0903091c, //odtcfg
	 0xe0d80036, //zqctl0
	 0x01e2aea6, //zqctl1
	 },

	{CLK_640MHZ, //ddr_clk
	 0x16202B1D, //dramtmg0
	 DRAMTMG_1_640M, //dramtmg1
	 0x060A0D10, //dramtmg2
	 0x00A0A000, //dramtmg3
	 DRAMTMG_4_640M, //dramtmg4
	 0x02020A0A, //dramtmg5
	 0x02020007, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000606, //dramtmg8
	 0x004d0056, //rfshtmg_s
	 0x004d0089, //rfshtmg_l    /*for 1 cs 8g DDR */
	 0x007D0001, //init0
	 0x00000000, //init1
	 0x00001405, //init2
	 0x00030018, //init3
	 0x00020000, //init4
	 0x00140007, //init5
	 0x06080004, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x00000003, //mr1
	 0x00000018,  //mr2
	 0x09040920, //odtcfg
	 0xe0E7003a, //zqctl0
	 0x0202DC6D, //zqctl1
	 },

	{CLK_667MHZ, //ddr_clk
	 0x17222d1e, //dramtmg0
	 DRAMTMG_1_667M, //dramtmg1
	 0x060A0D11, //dramtmg2
	 0x00A0A000, //dramtmg3
	 DRAMTMG_4_667M, //dramtmg4
	 0x02020b0b, //dramtmg5
	 0x02020008, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000505, //dramtmg8
	 0x00510057, //rfshtmg_s
	 0x0051008d, //rfshtmg_l    /*for 1 cs 8g DDR */
	 0x00830001, //init0
	 0x00000000, //init1
	 0x00001505, //init2
	 0x00230018, //init3
	 0x00020000, //init4
	 0x00150007, //init5
	 0x06080004, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x00000023, //mr1
	 0x00000018,  //mr2
	 0x09040920, //odtcfg
	 0xe0f1003d, //zqctl0
	 0x0222fb53, //zqctl1
	 },

	{CLK_800MHZ, //ddr_clk
	 0x18283624, //dramtmg0
	 DRAMTMG_1_800M, //dramtmg1
	 0x060c1011, //dramtmg2
	 0x00A0c000, //dramtmg3
	 DRAMTMG_4_800M, //dramtmg4
	 0x02020c0c, //dramtmg5
	 0x02020008, //dramtmg6
	 0x00000202, //dramtmg7
	 0x00000606, //dramtmg8
	 0x00610068, //rfshtmg_s
	 0x006100a8, //rfshtmg_l    /*for 1 cs 8g DDR */
	 0x009d0001, //init0
	 0x00000000, //init1
	 0x00001905, //init2
	 0x0043001a, //init3
	 0x00020000, //init4
	 0x00190008, //init5
	 0x060a0004, //dfitmg0
//	 0x00030202, //dfitmg1
	 0x00000043, //mr1
	 0x0000001a,  //mr2
	 0x0a040a28, //odtcfg
	 0xe1200048, //zqctl0
	 0x02839388, //zqctl1
	 },
#endif

#endif
};

#ifdef DDR_DFS_SUPPORT
typedef struct
{
	 uint32 ddr_clk;

	 //umctl reg
	 uint32 umctl_rfshtmg;
	 uint32 umctl_dramtmg0;
	 uint32 umctl_dramtmg1;
	 uint32 umctl_dramtmg2;
	 uint32 umctl_dramtmg3;
	 uint32 umctl_dramtmg4;
	 uint32 umctl_dramtmg5;
//	 uint32 umctl_dramtmg6;
	 uint32 umctl_dramtmg7;
	 uint32 umctl_dramtmg8;
	 uint32 umctl_dfitmg0;
	 uint32 umctl_init3;
	 uint32 umctl_zqctl0;
	 uint32 umctl_zqctl1;

	 //publ reg
	 uint32 publ_mr1;
	 uint32 publ_mr2;
	 uint32 publ_dx0gtr;
	 uint32 publ_dx1gtr;
	 uint32 publ_dx2gtr;
	 uint32 publ_dx3gtr;
	 uint32 publ_pgcr3;
	 uint32 publ_acmdlr;
	 uint32 publ_dx0mdlr;
	 uint32 publ_dx1mdlr;
	 uint32 publ_dx2mdlr;
	 uint32 publ_dx3mdlr;
	 uint32 publ_aclcdlr;
	 uint32 publ_dx0lcdlr0;
	 uint32 publ_dx1lcdlr0;
	 uint32 publ_dx2lcdlr0;
	 uint32 publ_dx3lcdlr0;
	 uint32 publ_dx0lcdlr1;
	 uint32 publ_dx1lcdlr1;
	 uint32 publ_dx2lcdlr1;
	 uint32 publ_dx3lcdlr1;
	 uint32 publ_dx0lcdlr2;
	 uint32 publ_dx1lcdlr2;
	 uint32 publ_dx2lcdlr2;
	 uint32 publ_dx3lcdlr2;
	 uint32 publ_dsgcr;
	 uint32 publ_dtpr0;
	 uint32 publ_dtpr1;
	 uint32 publ_dtpr2;
	uint32 publ_dtpr3;
	 uint32 reserved;
}ddr_dfs_val_t;
#endif

typedef struct mem_cs_info
{
	uint32 cs_number;
	uint32 cs0_size;//bytes
	uint32 cs1_size;//bytes
}mem_cs_info_t;

typedef struct {
	volatile unsigned int magic_header;
	volatile unsigned int ddr_lowpower_cfg;
	volatile unsigned int magic_ender;
	volatile unsigned int reg[3];
}ddr_lp_cfg;
/*
 BIT_0:PUB can power down
 BIT_1:PUBL can power down
 BIT_2:PHY can power down
*/
static ddr_lp_cfg lp_cfg=
{
	0x77778888,
	0x00000000,
	0x88887777,
#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
    0x402b005c,
	0x402b005c,
	0x402b005c,
#else
	0x402b006c,/*pub sys*/
	0x402b0140,/*publ cfg*/
	0x402b0144 /*phy cfg*/
#endif
};

#if defined(DDR_LPDDR2)
CLK_TYPE_E DDR_DFS_POINT[] =
{
	CLK_200MHZ,
	CLK_400MHZ,
	CLK_466MHZ,
	CLK_500MHZ,
	CLK_533MHZ,
};
#endif
#if defined(DDR_LPDDR3)
#if defined(CONFIG_SCX35LT8)
CLK_TYPE_E DDR_DFS_POINT[] =
{
	CLK_192MHZ,
	CLK_384MHZ,
	//CLK_600MHZ,
	//CLK_640MHZ,
	CLK_667MHZ,
	CLK_800MHZ,
};

#elif defined(CONFIG_SC9630) || defined(CONFIG_SCX35L64)
CLK_TYPE_E DDR_DFS_POINT[] =
{
    CLK_192MHZ,
//	CLK_200MHZ,
	CLK_384MHZ,
//	CLK_400MHZ,
	CLK_500MHZ,
	CLK_640MHZ,
};
//DDR3 FREQ POINT
#elif defined(CONFIG_SPX30G)
CLK_TYPE_E DDR_DFS_POINT[] =
{
    //CLK_192MHZ,
	CLK_200MHZ,
	//CLK_384MHZ,
	CLK_400MHZ,
	CLK_500MHZ,
	CLK_533MHZ,
};
#endif
#endif


#define REG32(x)   (*((volatile uint32 *)(x)))
#define UMCTL2_REG_GET(reg_addr)             (*((volatile uint32 *)(reg_addr)))
#define UMCTL2_REG_SET( reg_addr, value )    *(volatile uint32 *)(reg_addr) = value

/**---------------------------------------------------------------------------*
 **                            Local Functions
 **---------------------------------------------------------------------------*/
/**********************************************************************
 reboot function using for autodetec fail or training error
 this function first powerdown emmc & ddr
 then poweron emmc & ddr
 last enable watchdog for reset
**********************************************************************/

#ifdef CONFIG_NAND_SPL
#if defined(CONFIG_ADIE_SC2713) || defined(CONFIG_ADIE_SC2713S)
#define ANA_WTG_BASE    0x40038040
#define WDG_UNLOCK_KEY	0xE551
#define WDG_LOAD_LOW	(ANA_WTG_BASE+0x00)
#define WDG_LOAD_HIGH	(ANA_WTG_BASE+0x04)
#define WDG_CTRL		(ANA_WTG_BASE+0x08)
#define WDG_LOCK		(ANA_WTG_BASE+0x20)

void __wdg_reset()
{
	volatile uint32 reg_val = 0;
		volatile int i = 0;
		uint32 temp = 0;

//power down emmc(bit8) & power down vddmem(bit 11)
	reg_val = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD_RTCSET);
	reg_val |= ((1 << 8) |(1 << 11)); /* LDO_EMMCCORE_PD set in RTC CORE*/
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD_RTCSET,reg_val);

	reg_val = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD_RTCCLR);
	reg_val &= (~((1 << 8) |(1 << 11))); /* LDO_EMMCCORE_PD clear in RTC CORE */
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD_RTCCLR,reg_val);


//	wait_us(20 * 1000);
	wait_pclk(10000 * 50);

//power on emmc
	reg_val = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD_RTCSET);
	reg_val &= (~((1 << 8) |(1 << 11)));
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD_RTCSET,reg_val);

	reg_val = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD_RTCCLR);
	reg_val |= ((1 << 8) |(1 << 11));
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD_RTCCLR,reg_val);

	ddr_print("ddr emmc & vddm reboot OK \r\n");


//wdg_reset
	/*unlock arch enable*/
	ANA_REG_SET(ANA_REG_GLB_MCU_WR_PROT_VALUE,0x3c4d);

	/*first enable ana watch module*/
	reg_val = ANA_REG_GET(ANA_REG_GLB_ARM_MODULE_EN);
	reg_val |= (1 << 2);
	ANA_REG_SET(ANA_REG_GLB_ARM_MODULE_EN,reg_val);

	reg_val = ANA_REG_GET(ANA_REG_GLB_RTC_CLK_EN);
	reg_val |= (1 << 2); /* enable the  PCLK of watchdog */
	ANA_REG_SET(ANA_REG_GLB_RTC_CLK_EN,reg_val);

	/*second unlock watch module*/
	ANA_REG_SET(WDG_LOCK,WDG_UNLOCK_KEY);

	/*third load watch count*/
	ANA_REG_SET(WDG_LOAD_HIGH,0x0);
	ANA_REG_SET(WDG_LOAD_LOW,0x10);

	/*forth watchdog run and reset enable*/
	ANA_REG_SET(WDG_CTRL,0xe);

	/*lock watchdog for safe*/
	ANA_REG_SET(WDG_LOCK,0x0000);

	ddr_print("ddr watchdog reset OK \r\n");

}
#elif defined(CONFIG_ADIE_SC2723S) || defined(CONFIG_ADIE_SC2723)
#define ANA_REG_GLB_MCU_WR_PROT_VALUE   0x4003894c
#define ANA_REG_GLB_ARM_MODULE_EN	0x40038800
#define ANA_REG_GLB_RTC_CLK_EN		0x40038808

#define WDG_CTRL                0x40038048
#define WDG_LOAD_LOW            0x40038040
#define WDG_LOAD_HIGH           0x40038044
#define WDG_LOCK	        0x40038860

#define WDG_UNLOCK_KEY		0xE551
#define ANA_REG_GLB_PWR_WR_PROT_VALUE        0x40038950
#define ANA_REG_GLB_LDO_DCDC_PD              0x40038810
void __wdg_reset()
{
	volatile uint32 reg_val = 0;
	volatile uint32 reg_val_pd = 0;

/* power down emmc(bit 7) & vddmem(bit11) */
	/*unlock arch enable*/
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE,0x6e7f);

	reg_val_pd = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD);
	reg_val_pd |= ((1<<7) | (1 << 11));
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD,reg_val_pd);

	wait_pclk(10000 * 50);
/* power on emmc(bit 7) & vddmem(bit11) */
	reg_val_pd = ANA_REG_GET(ANA_REG_GLB_LDO_DCDC_PD);
	reg_val_pd &= (~((1<<7) | (1 << 11)));
	ANA_REG_SET(ANA_REG_GLB_LDO_DCDC_PD,reg_val_pd);

	wait_pclk(10000);

	ddr_print("ddr emmc & vddm reboot OK \r\n");

	/*first enable ana watch module*/
	reg_val = ANA_REG_GET(ANA_REG_GLB_ARM_MODULE_EN);
	reg_val |= (1 << 2);
	ANA_REG_SET(ANA_REG_GLB_ARM_MODULE_EN,reg_val);
	reg_val = ANA_REG_GET(ANA_REG_GLB_RTC_CLK_EN);
	reg_val |= (1 << 2);
	ANA_REG_SET(ANA_REG_GLB_RTC_CLK_EN,reg_val);

	/*second unlock watch module*/
	ANA_REG_SET(WDG_LOCK,0xe551);

	/*third load watch count*/
	ANA_REG_SET(WDG_LOAD_HIGH,0x0);
	ANA_REG_SET(WDG_LOAD_LOW,0x10);

	/*forth watchdog run and reset enable*/
	ANA_REG_SET(WDG_CTRL,0xe);

	/*lock watchdog for safe*/
	ANA_REG_SET(WDG_LOCK,0x0000);
}
#endif
#else
void __wdg_reset()
{
}
#endif

void wait_pclk(uint32 n_pclk)
{
    volatile uint32 i;
    volatile uint32 value;

    for(i = 0; i < n_pclk; i++)
    {
        value = REG32(0x30010018);
    }
    value = value;
}

uint32 dmc_reg_bits_set(uint32 addr,
			uint32 start_bitpos,
			uint32 bit_num,
			unsigned int value)
{
    /*create bit mask according to input param*/
    unsigned int bit_mask = (1<<bit_num)-1;
    unsigned int reg_data = *((volatile unsigned int*)(addr));

    reg_data &= ~(bit_mask<<start_bitpos);
    reg_data |= ((value&bit_mask)<<start_bitpos);

    *((volatile unsigned int*)(addr)) = reg_data;
    return 0;
}

#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
static void dram_clk_twpll_set(uint32 clk)
{
#ifdef CONFIG_SCX35LT8
    volatile uint32 reg_val;

    reg_val = REG32(0x402e0114);
    reg_val &= ~(1<<4);
    REG32(0x402e0114) = reg_val;

    reg_val = REG32(0x402b00b0);
    reg_val &= ~(1<<8);
    REG32(0x402b00b0) = reg_val;

    REG32(0x50820010) &= ~(0x7 << 0);

	if(clk == 768)
	{
	    REG32(0x50820010) |= 0x06;    //twpll 384M
	}
    else if(clk == 384)
    {
        REG32(0x50820010) |= 0x03;    //twpll 192M
	}
#else
    REG32(0x402d0058) &= ~(0x7 << 0);

	if(clk == 768)
	{
	    REG32(0x402d0058) |= 0x006;    //twpll 384M
	}
    else if(clk == 384)
    {
        REG32(0x402d0058) |= 0x003;    //twpll 192M
	}
#endif
}
#elif defined(CONFIG_SPX30G)
static void dram_clk_tdpll_set(uint32 clk)
{
    REG32(0x402d0024) &= ~((0x3 << 0) | (0x3 << 8));

	if(clk == 768)
	{
	    REG32(0x402d0024) |= 0x002;    //tdpll 768M    2 div
	}
    else if(clk == 384)
    {
        REG32(0x402d0024) |= 0x102;    //tdpll 768M    2 div
	}
}
#endif


static void dram_clk_set(unsigned int dll_clk)
{
	unsigned int reg_val,emc_div;
	volatile unsigned int i;
	/*first setup dpll freqency*/
//	reg_val = *(volatile unsigned int*)0x402E3004;
//	reg_val &= ~(0x7ff|(0x3 << 24));
//	reg_val |= ((clk >> 2)|(0x3 << 24));
//	*(volatile unsigned int*)0x402E3004 = reg_val;
//	reg_val = *(volatile unsigned int*)0x402E3074;
//	reg_val &= ~(0x3f);
//	reg_val |= (clk/26+1);
//	*(volatile unsigned int*)0x402E3074 = reg_val;
	/*wait for dpll stable*/
//	for(i=0;i<1000;i++);
	/*open ddr control clock gate*/
	*(volatile uint32*)0x402b00D0 |= (0x7 << 4);
	*(volatile uint32*)0x402b00D0 &= ~(0x7 << 0);
	/*second reset ddr phy for dll*/
	*(volatile uint32*)0x402b00D0 |= ((1 << 8)|(1 << 10)|(1 << 11)|(1 << 12));
#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
    if(dll_clk == 768)
    {
	    dram_clk_twpll_set(768);
    }
	else if(dll_clk == 384)
	{
		dram_clk_twpll_set(384);
	}
	else
	{
	    set_ddr_clk(dll_clk);
	}
#else
	/*third switch dpll to emc*/
//	reg_val = *(volatile unsigned int*)0x402D0024;
//	reg_val &= ~(0x003|(0x3 <<  8));
//	reg_val |= (0x003);
//	*(volatile unsigned int*)0x402D0024 = reg_val;
	/*wait for something*/
	if(dll_clk >= 600){
			reg_val = *(volatile unsigned int*)0x402d0024;
			reg_val &= ~(0x3 << 8);
		//	reg_val |= (emc_div << 8);
			*(volatile unsigned int*)0x402d0024 = reg_val;
		set_ddr_clk(dll_clk);
	} else {
		/*first find out emc div*/
		for(emc_div=1;emc_div<=3;emc_div++)
		{
			if(dll_clk*(emc_div+1) >= 600)
			{
				reg_val = *(volatile unsigned int*)0x402d0024;
				reg_val &= ~(0x3 << 8);
				reg_val |= (emc_div << 8);
				*(volatile unsigned int*)0x402d0024 = reg_val;
				set_ddr_clk(dll_clk*(emc_div+1));
				break;
			}
		}
	}
#endif

	for(i=0;i<1000;i++);
	/*forth release ddr phy for dll*/
	*(volatile uint32*)0x402b00D0 &= ~((1 << 8)|(1 << 10)|(1 << 11)|(1 << 12));

	ddr_core_clk = dll_clk/2;
}

static void umctl_ctl_en(unsigned int isEnable)
{
}

static void umctl_soft_reset(unsigned int isReset)
{
	volatile unsigned int i;
	unsigned int reg_val;

	if(isReset) {
		reg_val = *(volatile uint32*)(REG_AON_TOP_DDR_PHY_RET_CFG);
		reg_val &= ~(1 << 0);
		*(volatile uint32*)(REG_AON_TOP_DDR_PHY_RET_CFG) = reg_val;

		reg_val = *(volatile uint32*)(REG_AON_TOP_DDR_OP_MODE_CFG);
		#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
		reg_val &= ~(1 << 24);
		#else
		reg_val |= (1 << 24);
		#endif
		*(volatile uint32*)(REG_AON_TOP_DDR_OP_MODE_CFG) = reg_val;

		reg_val = *(volatile uint32*)(REG_AON_TOP_DDR_PHY_RET_CFG);
		reg_val |= (1 << 16);
		*(volatile uint32*)(REG_AON_TOP_DDR_PHY_RET_CFG) = reg_val;
		for(i=0;i<50;i++);

		reg_val = *(volatile uint32*)(REG_AON_TOP_DDR_SLEEP_CTRL);
		reg_val |= (0x1f << 8);

		*(volatile uint32*)(REG_AON_TOP_DDR_SLEEP_CTRL) = reg_val;
		for(i=0;i<50;i++);

		reg_val = *(volatile uint32*)(REG_AON_TOP_DDR_SLEEP_CTRL);
		reg_val &= ~(0x1800);
		*(volatile uint32*)(REG_AON_TOP_DDR_SLEEP_CTRL) = reg_val;
		for(i=0;i<50;i++);
	} else {
		reg_val = *(volatile uint32*)(REG_AON_TOP_DDR_PHY_RET_CFG);
		reg_val &= ~(1 << 16);
		*(volatile uint32*)(REG_AON_TOP_DDR_PHY_RET_CFG) = reg_val;
		for(i=0;i<50;i++);
	}
}

void umctl_basic_mode_init(DRAM_INFO_T *dram)
{
	DRAM_TYPE_E dram_type = (dram->dram_type & 0xf00);
	uint32 BL = dram->bl;
	uint32 width = dram->io_width;

	dmc_reg_bits_set((uint32)&umctl->umctl_mstr,24,4,(dram->cs_num==2)?3:1);
	/*set burst length*/
	dmc_reg_bits_set((uint32)&umctl->umctl_mstr,16,4,((BL==2)?0x1:0)|
						         ((BL==4)?0x2:0)|
						         ((BL==8)?0x4:0)|
						         ((BL==16)?0x8:0));
	/*set data bus width*/
	dmc_reg_bits_set((uint32)&umctl->umctl_mstr,12,2,((width==32)?0x00:0x00)|
						         ((width==16)?0x01:0x00)|
						         ((width== 8)?0x02:0x00));
	/*disable en_2t_timing_mode,use 1T timing as default.*/
	dmc_reg_bits_set((uint32)&umctl->umctl_mstr,10,1,0x00);
	/*burst_mode, 0--Sequential burst mode;1--Interleaved burst mode.*/
	dmc_reg_bits_set((uint32)&umctl->umctl_mstr,8,1,0);
	/*SDRAM selection for ddr2/ddr3/lpddr/lpddr2/lpddr3*/
	dmc_reg_bits_set((uint32)&umctl->umctl_mstr,0,4,((dram_type == DRAM_DDR3)?0x01:0x00) |
					            ((dram_type == DRAM_LPDDR1)?0x2:0x00)|
					            ((dram_type == DRAM_LPDDR2)?0x4:0x00)|
					            ((dram_type == DRAM_LPDDR3)?0x8:0x00));

	umctl->umctl_sched   = 0x00070c01;
	/*stagger_cs_en*/
	umctl->umctl_dimmctl = 0x00000000;
	umctl->umctl_rankctl = 0x00000663;
}

void umctl_poweron_init(CLK_TYPE_E dmc_clk,DRAM_INFO_T *dram)
{
    uint32 i;

    for(i = 0; i < ARRAY_SIZE(DDR_TIMING_INFO); i++)
	{
		if(dmc_clk == DDR_TIMING_INFO[i].ddr_clk)
		{
		    umctl->umctl_init[0] = DDR_TIMING_INFO[i].init0;
		    umctl->umctl_init[1] = DDR_TIMING_INFO[i].init1;
		    umctl->umctl_init[2] = DDR_TIMING_INFO[i].init2;
		    umctl->umctl_init[3] = DDR_TIMING_INFO[i].init3;
		    umctl->umctl_init[4] = DDR_TIMING_INFO[i].init4;
		    umctl->umctl_init[5] = DDR_TIMING_INFO[i].init5;
		}
	}
}

static void umctl_dramtiming_init(CLK_TYPE_E dmc_clk,DRAM_INFO_T *dram)
{

    uint32 i = 0;

	for(i = 0; i < ARRAY_SIZE(DDR_TIMING_INFO); i++)
	{
		if(dmc_clk == DDR_TIMING_INFO[i].ddr_clk)
		{
			umctl->umctl_dramtmg[0] = DDR_TIMING_INFO[i].dramtmg0;
			umctl->umctl_dramtmg[1] = DDR_TIMING_INFO[i].dramtmg1;
			umctl->umctl_dramtmg[2] = DDR_TIMING_INFO[i].dramtmg2;
			umctl->umctl_dramtmg[3] = DDR_TIMING_INFO[i].dramtmg3;
			umctl->umctl_dramtmg[4] = DDR_TIMING_INFO[i].dramtmg4;
			umctl->umctl_dramtmg[5] = DDR_TIMING_INFO[i].dramtmg5;
			umctl->umctl_dramtmg[6] = DDR_TIMING_INFO[i].dramtmg6;
			umctl->umctl_dramtmg[7] = DDR_TIMING_INFO[i].dramtmg7;
			umctl->umctl_dramtmg[8] = DDR_TIMING_INFO[i].dramtmg8;

		}
	}
}

#ifdef PIKEL_DRIVER_SUPPORT_ON
#define PIKEL_AON_CHIP_ID_ADDRESS	0x402e00fc
#define PIKEL_CHIP_ID 0x96320000
#define UMCTL_SWCTL				0x30000320
#define UMCTL_SWCTL_SWSTAT		0x30000324
#define DDR_UMCTL_EN			0x402B00D0
#define ADDRMAP_SIZE 7

typedef struct
{
	DRAM_TYPE_E 	dram_type;
	unsigned int	addrmap[ADDRMAP_SIZE];
}DRAM_INFO_ADDRMAP;

static uint32 get_chip_id()
{
	return *(volatile uint32 *)(PIKEL_AON_CHIP_ID_ADDRESS);
}

static void enter_quasi_mode()
{
	if(get_chip_id() == PIKEL_CHIP_ID)
	{
		//dmc_reg_bits_set(DDR_UMCTL_EN,1,1,1);
		REG32(UMCTL_SWCTL) = 0;
	}
}

DRAM_INFO_ADDRMAP dram_info_addrmap[]=
{
/*    type          	  addrmap0		  addrmap1		  addrmap2		  addrmap3		  addrmap4		  addrmap5		  addrmap6	*/
DRAM_LPDDR2_1CS_2G_X32,	 0X00001F1F,	 0X00070707,	 0X00000000,	 0X0F000000,	 0X00000F0F,	 0X06060606,	 0X0F0F0606,
DRAM_LPDDR2_1CS_4G_X32,	 0x00001F1F,	 0x00080808,	 0x00000000,	 0x00000000,	 0x00000F0F,	 0x07070707,	 0x0F0F0707,
DRAM_LPDDR3_1CS_4G_X32,	 0x00001F1F,	 0x00080808,	 0x00000000,	 0x00000000,	 0x00000F0F,	 0x07070707,	 0x0F0F0707,
DRAM_LPDDR2_2CS_2G_X32,	 0X00001F13,	 0X00070707,	 0X00000000,	 0X0F000000,	 0X00000F0F,	 0X06060606,	 0X0F0F0F06,
DRAM_LPDDR2_2CS_4G_X32,	 0X00001F14,	 0X00070707,	 0X00000000,	 0X0F000000,	 0X00000F0F,	 0X06060606,	 0X0F0F0606,
DRAM_LPDDR2_2CS_6G_X32,	 0x00001F15,	 0X00070707,	 0x00000000,	 0x11000000,	 0x00000F0F,	 0X06060606,	 0x0F0F0606,
DRAM_LPDDR2_2CS_8G_X32,	 0x00001F15,	 0x00080808,	 0x00000000,	 0x00000000,	 0x00000F0F,	 0x07070707,	 0x0F0F0707,
DRAM_LPDDR3_2CS_8G_X32,	 0x00001F15,	 0x00080808,	 0x00000000,	 0x00000000,	 0x00000F0F,	 0x07070707,	 0x0F0F0707,
DRAM_LPDDR2_2CS_12G_X32, 0x00001F16,	 0x00080808,	 0x00000000,	 0x00000000,	 0x00000F0F,	 0x07070707,	 0x0F070707,
DRAM_LPDDR2_2CS_16G_X32, 0x00001F16,	 0x00080808,	 0x00000000,	 0x00000000,	 0x00000F0F,	 0x07070707,	 0x0F070707,
DRAM_LPDDR2_1CS_8G_X32,	 0x00001F1f,	 0x00080808,	 0x00000000,	 0x00000000,	 0x00000F0F,	 0x07070707,	 0x0F070707,
DRAM_LPDDR3_1CS_8G_X32,	 0x00001F1f,	 0x00080808,	 0x00000000,	 0x00000000,	 0x00000F0F,	 0x07070707,	 0x0F070707,
DRAM_LPDDR3_1CS_6G_X32,	 0x00001F1f,	 0x00080808,	 0x00000000,	 0x00000000,	 0x00000F0F,	 0x07070707,	 0x0F070707,
DRAM_DDR3_1CS_2G_X8_4P,	 0x00001F1F,	 0x00080808,	 0x00000000,	 0x0F000000,	 0x00000F0F,	 0x07070707,	 0x07070707,
DRAM_DDR3_1CS_4G_X16_2P, 0x00001F1F,	 0x00080808,	 0x00000000,	 0x0F000000,	 0x00000F0F,	 0x07070707,	 0x0F070707,
};

static void umctl_addrmap_init_pikel(DRAM_INFO_T *dram)
{
	uint32 i,j;

	/*in order to remap ddr hole*/
	if(dram->dram_type == DRAM_LPDDR3_1CS_6G_X32)
	{
		REG32(0x30023000) = 0xfffff;
		for(i=0;i<10;i++)
		{
			REG32(0x30023008 + i*4) = 0x8a988a98;
		}
	}
	else
	{
		REG32(0x30023000) |= (1 << 10);
		REG32(0x3002301C) = 0xba98ba98;
	}

	for(i = 0; i < ARRAY_SIZE(dram_info_addrmap); i++)
	{
		if(dram_info_addrmap[i].dram_type == dram->dram_type)
		{
			for(j = 0; j < ADDRMAP_SIZE; j++)
			{
				umctl->umctl_addrmap[j] = dram_info_addrmap[i].addrmap[j];
			}
			break;
		}
	}
}

static void umctl_port_init_pikel(umctl2_port_info_t* port_info)
{
	uint32 i = 0;
	//*** the ddr controller channel external priority setting***//
	//priority value: 0x0~0xf
	//description: 0xf is highest priority, 0x0 is lowest priority
	//priority setting: port4 wr&rd (CPx DSP)      =
	//                  port5 wr&rd (CP0W)         =
	//                  port6 wr&rd (CP0 ARM)      =
	//                  port8 wr&rd (CP1 ARM)      =
	//                  port9 wr&rd (CP2)          >
	//                  port2 rd    (display/gsp)  =
	//                  port0 wr    (mm/dcam/vsp)  >
	//                  port0 rd    (mm/dcam/vsp)  >
	//                  port3 wr&rd (CA7)          >
	//                  port2 wr    (display/gsp)  =
	//                  port7 wr&rd (AP matrix)    >
	//                  port1 wr&rd (GPU)

	dmc_reg_bits_set(DDR_QOS_CFG1,  0,4,0x4); //chanel 0 wr qos, CA7
	dmc_reg_bits_set(DDR_QOS_CFG1,  4,4,0x4); //chanel 0 rd qos, CA7
	dmc_reg_bits_set(DDR_QOS_CFG1,  8,4,0x2); //chanel 1 wr qos, DISPLAY
	dmc_reg_bits_set(DDR_QOS_CFG1, 12,4,0xC); //chanel 1 rd qos, DISPLAY
	dmc_reg_bits_set(DDR_QOS_CFG1, 16,4,0x0); //chanel 2 wr qos, GPU/GSP
	dmc_reg_bits_set(DDR_QOS_CFG1, 20,4,0x0); //chanel 2 rd qos, GPU/gsp
	dmc_reg_bits_set(DDR_QOS_CFG1, 24,4,0xE); //chanel 3 wr qos,AP ZIP
	dmc_reg_bits_set(DDR_QOS_CFG1, 28,4,0xE); //chanel 3 rd qos, AP ZIP

	dmc_reg_bits_set(DDR_ID2QOS_SEL,4,1,0x1); //channel 4 qos select, 0:qos is for DDR_QOS_CFG1 1:qos is for DDR_ID2QOS_RCFG0
	dmc_reg_bits_set(DDR_ID2QOS_RCFG4,0,32,0x88048804); //channel 4 rd qos, vsp = 0x8, jpg = 8, dcam = 4;
	dmc_reg_bits_set(DDR_ID2QOS_WCFG4,0,32,0x66086608); //channel 4 wr qos, vsp = 0x6, jpg = 6, dcam = 8;

	dmc_reg_bits_set(DDR_ID2QOS_SEL,2,1,0x1); //channel 2 qos select, 0:qos is for DDR_QOS_CFG1 1:qos is for DDR_ID2QOS_RCFG1
	dmc_reg_bits_set(DDR_ID2QOS_RCFG2,0,32,0x02020202); //channel 2 rd qos, gsp = 0x2, gpu = 0;
	dmc_reg_bits_set(DDR_ID2QOS_WCFG2,0,32,0x02020202); //channel 2 wr qos, gsp = 0x2, gpu = 0;

	dmc_reg_bits_set(DDR_QOS_CFG2,  8,4,0xF); //chanel 4 wr qos, MM
	dmc_reg_bits_set(DDR_QOS_CFG2, 12,4,0xF); //chanel 5 rd qos, CP0ARM
	dmc_reg_bits_set(DDR_QOS_CFG2, 16,4,0xF); //chanel 6 wr qos, CP0 DSP
	dmc_reg_bits_set(DDR_QOS_CFG2, 20,4,0xF); //chanel 6 rd qos, CP0 DSP
	dmc_reg_bits_set(DDR_QOS_CFG2, 24,4,0xF); //chanel 7 wr qos, CP1ACCHARQ
	dmc_reg_bits_set(DDR_QOS_CFG2, 28,4,0xF); //chanel 7 rd qos, CP1ACCHARQ

	dmc_reg_bits_set(DDR_QOS_CFG3,  0,4,0xE); //chanel 8 wr qos, CP1 DSP
	dmc_reg_bits_set(DDR_QOS_CFG3,  4,4,0xE); //chanel 8 rd qos, CP1 DSP

	//umctl channel performance set
	//UMCTL2_REG_SET(UMCTL_PERFHPR0, 0x00000001);
	UMCTL2_REG_SET(UMCTL_PERFHPR1, 0x10000001);
	//UMCTL2_REG_SET(UMCTL_PERFLPR0, 0x00000100);
	UMCTL2_REG_SET(UMCTL_PERFLPR1, 0x10000100);
	//UMCTL2_REG_SET(UMCTL_PERFWR0,  0x00000020);
	UMCTL2_REG_SET(UMCTL_PERFWR1,  0x10000100);
	//umctl channel policy set
	UMCTL2_REG_SET(UMCTL_SCHED,0x00071501);//set low priority entry number

	dmc_reg_bits_set(UMCTL_PCCFG,4,1,1);//pagematch_limit
	dmc_reg_bits_set(UMCTL_PCCFG,0,1,0);//go2critical_en
	//UMCTL2_REG_SET(UMCTL_PCCFG,0X10);

	for(i = 0; ;i++)
	{
		if(port_info[i].rdwr_order == 0xff)
		{
			return;
		}
		//read priority
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,16,1,port_info[i].rdwr_order);   //rdwr_ordered_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,15,1,port_info[i].rd_hpr);	   //rd_port_hpr_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,14,1,port_info[i].rd_pagematch); //rd_port_pagematch_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,13,1,port_info[i].rd_urgent);    //rd_port_urgent_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,12,1,port_info[i].rd_aging);	   //rd_port_aging_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,11,1,port_info[i].rd_reorder_bypass);//read_reorder_bypass_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,0,10,port_info[i].rd_priority);  //rd_port_priority

		//write priority
		dmc_reg_bits_set(UMCTL_PCFGW_0+i*0xb0,14,1,port_info[i].wr_pagematch); //wr_port_pagematch_en
		dmc_reg_bits_set(UMCTL_PCFGW_0+i*0xb0,13,1,port_info[i].wr_urgent);    //wr_port_urgent_en
		dmc_reg_bits_set(UMCTL_PCFGW_0+i*0xb0,12,1,port_info[i].wr_aging);	   //wr_port_aging_en
		dmc_reg_bits_set(UMCTL_PCFGW_0+i*0xb0,0,10,port_info[i].wr_priority);  //wr_port_priority

		if(port_info[i].rd_hpr)
		{
			dmc_reg_bits_set(UMCTL_PCFGQOS_0+i*0xb0,16,2,0x2);
			dmc_reg_bits_set(UMCTL_PCFGQOS_0+i*0xb0,20,2,0x2);
		}
	}
}

/*
1. add for pikel
*/
void publ_acio_init()
{
	int i;
	for(i = 1; i < 6; i++)
	{
		publ->publ_aciocr[i] = 0;
	}
}

/*
1. add for pikel
*/
void publ_dxng_init()
{
	int i;
	for(i = 1; i < 4; i++)
	{
		publ->publ_dx0gcr[i] = 0;
		publ->publ_dx1gcr[i] = 0;
		publ->publ_dx2gcr[i] = 0;
		publ->publ_dx3gcr[i] = 0;
	}
}

static void is_pikel()
{
	int i;
	if(get_chip_id() == PIKEL_CHIP_ID)
	{
		for(i = 0; i <ARRAY_SIZE(DDR_DFS_POINT); i++)
		{
			DDR_DFS_POINT[i] = 0;
		}
		DDR_DFS_POINT[0] = CLK_192MHZ;
		DDR_DFS_POINT[1] = CLK_384MHZ;
		DDR_DFS_POINT[2] = CLK_533MHZ;
	}
}

#endif

static void umctl_addrmap_init(DRAM_INFO_T *dram)
{
	uint32 i;

#if defined(CONFIG_SPX30G)
	switch(dram->dram_type)
	{
		case DRAM_LPDDR3_1CS_6G_X32:
			REG32(0x30023000) = 0xfffff;
			for(i=0;i<10;i++)
			{
				REG32(0x30023008 + i*4) = 0x8a988a98;
			}
		break;

		case DRAM_LPDDR2_2CS_6G_X32:
			// to avoid dsp remap error
			dmc_reg_bits_set(0x30023000, 8, 2, 0x3);	//port4 cp0 dsp
			REG32(0x30023018) = 0x98989898;
		break;

		case DRAM_LPDDR3_2CS_12G_X32:
		case DRAM_LPDDR3_2CS_16G_X32:
		case DRAM_LPDDR3_2CS_8G_X16_2P:
			dmc_reg_bits_set(0x30023000, 8, 2, 0x3);	// DMC port remap enable
			REG32(0x30023018) = 0x98989898;	//  DMC port4 addr remap
		break;

		case DRAM_LPDDR3_2CS_6GX2_X32:
			REG32(0x30023000) = 0xfffff;
			for(i=0;i<10;i++)
			{
				REG32(0x30023008 + i*4) = 0xeeedca98;
			}
				REG32(0x30023018) = 0xca98ca98;			//port6 cp0 dsp
		break;
	}
#endif

#if defined(CONFIG_SC9630) || defined(CONFIG_SCX35L64)
	switch(dram->dram_type)
	{
		case DRAM_LPDDR3_1CS_6G_X32:
			REG32(0x30023000) = 0xfffff;
			for(i=0;i<10;i++)
			{
				REG32(0x30023008 + i*4) = 0x8a988a98;
			}
			break;

		case DRAM_LPDDR2_2CS_6G_X32:
			dmc_reg_bits_set(0x30023000, 12, 2, 0x3);
			dmc_reg_bits_set(0x30023000, 16, 2, 0x3);
			REG32(0x30023020) = 0x98989898;			//port6 cp0 dsp
			REG32(0x30023028) = 0x98989898;			//port8 cp1 dsp
			break;

		case DRAM_LPDDR3_2CS_12G_X32:
		case DRAM_LPDDR3_2CS_16G_X32:
		case DRAM_LPDDR3_2CS_8G_X16_2P:
			dmc_reg_bits_set(0x30023000, 12, 2, 0x3);
			dmc_reg_bits_set(0x30023000, 16, 2, 0x3);
			REG32(0x30023020) = 0xba98ba98;			//port6 cp0 dsp
			REG32(0x30023028) = 0xba98ba98;			//port8 cp1 dsp
			break;

		case DRAM_LPDDR3_2CS_6GX2_X32:
			REG32(0x30023000) = 0xfffff;
			for(i=0;i<10;i++)
			{
				REG32(0x30023008 + i*4) = 0xeeedca98;
			}
				REG32(0x30023020) = 0xca98ca98;			//port6 cp0 dsp
				REG32(0x30023028) = 0xca98ca98;			//port8 cp1 dsp
			break;
	}
#endif

	switch(dram->dram_type)
	{
//LPDDR2 PART
		case DRAM_LPDDR2_1CS_2G_X32:
			umctl->umctl_addrmap[0] = 0X00001F1F;
			umctl->umctl_addrmap[1] = 0X00060606;
			umctl->umctl_addrmap[2] = 0X00000000;
			umctl->umctl_addrmap[3] = 0X0F0F0000;
			umctl->umctl_addrmap[4] = 0X00000F0F;
			umctl->umctl_addrmap[5] = 0X05050505;
			umctl->umctl_addrmap[6] = 0X0F0F0505;
			break;
		case DRAM_LPDDR2_1CS_4G_X32:
		case DRAM_LPDDR3_1CS_4G_X32:
			umctl->umctl_addrmap[0] = 0x00001F1F;
			umctl->umctl_addrmap[1] = 0x00070707;
			umctl->umctl_addrmap[2] = 0x00000000;
			umctl->umctl_addrmap[3] = 0x0F000000;
			umctl->umctl_addrmap[4] = 0x00000F0F;
			umctl->umctl_addrmap[5] = 0x06060606;
			umctl->umctl_addrmap[6] = 0x0F0F0606;
			break;

		case DRAM_LPDDR2_1CS_4G_X16_2P:
			umctl->umctl_addrmap[0] = 0x00001F1F;
			umctl->umctl_addrmap[1] = 0x00080808;
			umctl->umctl_addrmap[2] = 0x00000000;
			umctl->umctl_addrmap[3] = 0x00000000;
			umctl->umctl_addrmap[4] = 0x00000F0F;
			umctl->umctl_addrmap[5] = 0x07070707;
			umctl->umctl_addrmap[6] = 0x0F0F0707;
			break;

		case DRAM_LPDDR2_2CS_2G_X32:
			umctl->umctl_addrmap[0] = 0X00001F13;
			umctl->umctl_addrmap[1] = 0X00060606;
			umctl->umctl_addrmap[2] = 0X00000000;
			umctl->umctl_addrmap[3] = 0X0F0F0000;
			umctl->umctl_addrmap[4] = 0X00000F0F;
			umctl->umctl_addrmap[5] = 0X05050505;
			umctl->umctl_addrmap[6] = 0X0F0F0505;
			break;
		case DRAM_LPDDR2_2CS_4G_X32:
			umctl->umctl_addrmap[0] = 0X00001F13;
			umctl->umctl_addrmap[1] = 0X00060606;
			umctl->umctl_addrmap[2] = 0X00000000;
			umctl->umctl_addrmap[3] = 0X0F0F0000;
			umctl->umctl_addrmap[4] = 0X00000F0F;
			umctl->umctl_addrmap[5] = 0X05050505;
			umctl->umctl_addrmap[6] = 0X0F0F0F05;
			break;
		case DRAM_LPDDR2_2CS_6G_X32:
			umctl->umctl_addrmap[0] = 0x00001F14;
			umctl->umctl_addrmap[1] = 0x00060606;
			umctl->umctl_addrmap[2] = 0x00000000;
			umctl->umctl_addrmap[3] = 0x0F110000;
			umctl->umctl_addrmap[4] = 0x00000F0F;
			umctl->umctl_addrmap[5] = 0x05050505;
			umctl->umctl_addrmap[6] = 0x0F0F0505;
			break;
		case DRAM_LPDDR2_2CS_8G_X32:
		case DRAM_LPDDR3_2CS_8G_X32:
			umctl->umctl_addrmap[0] = 0x00001F14;
			umctl->umctl_addrmap[1] = 0x00070707;
			umctl->umctl_addrmap[2] = 0x00000000;
			umctl->umctl_addrmap[3] = 0x00000000;
			umctl->umctl_addrmap[4] = 0x00000F0F;
			umctl->umctl_addrmap[5] = 0x06060606;
			umctl->umctl_addrmap[6] = 0x0F0F0606;
			break;
		case DRAM_LPDDR2_2CS_12G_X32:
		case DRAM_LPDDR2_2CS_16G_X32:
		case DRAM_LPDDR3_2CS_12G_X32:
			umctl->umctl_addrmap[0] = 0x00001F15;
			umctl->umctl_addrmap[1] = 0x00070707;
			umctl->umctl_addrmap[2] = 0x00000000;
			umctl->umctl_addrmap[3] = 0x0F000000;
			umctl->umctl_addrmap[4] = 0x00000F0F;
			umctl->umctl_addrmap[5] = 0x06060606;
			umctl->umctl_addrmap[6] = 0x0F060606;
			break;

	 case DRAM_LPDDR2_1CS_8G_X32:
	 case DRAM_LPDDR3_1CS_8G_X32:
	 case DRAM_LPDDR3_1CS_6G_X32:
			umctl->umctl_addrmap[0] = 0x00001F1f;
			umctl->umctl_addrmap[1] = 0x00070707;
			umctl->umctl_addrmap[2] = 0x00000000;
			umctl->umctl_addrmap[3] = 0x0F000000;
			umctl->umctl_addrmap[4] = 0x00000F0F;
			umctl->umctl_addrmap[5] = 0x06060606;
			umctl->umctl_addrmap[6] = 0x0F060606;
			break;

	 case DRAM_LPDDR3_2CS_6GX2_X32:
	 case DRAM_LPDDR3_2CS_16G_X32:
			umctl->umctl_addrmap[0] = 0x00001F15;
			umctl->umctl_addrmap[1] = 0x00070707;
			umctl->umctl_addrmap[2] = 0x00000000;
			umctl->umctl_addrmap[3] = 0x0F000000;
			umctl->umctl_addrmap[4] = 0x00000F0F;
			umctl->umctl_addrmap[5] = 0x06060606;
			umctl->umctl_addrmap[6] = 0x0F060606;
			break;

	 case DRAM_LPDDR3_2CS_8G_X16_2P:
			umctl->umctl_addrmap[0] = 0x00001F15;
			umctl->umctl_addrmap[1] = 0x00080808;
			umctl->umctl_addrmap[2] = 0x00000000;
			umctl->umctl_addrmap[3] = 0x00000000;
			umctl->umctl_addrmap[4] = 0x00000F0F;
			umctl->umctl_addrmap[5] = 0x07070707;
			umctl->umctl_addrmap[6] = 0x0F0F0707;
			break;
	}
}
/*
 * saved the ddr CS size info for kernel reserved space,
 * because the ddr training will corrupt the CS header data when ddr retention
 */
static int record_cs_info(DRAM_INFO_T *dram)
{
	u32 total_size;
	mem_cs_info_t * cs_info_ptr = (mem_cs_info_t *)DDR_DFS_VAL_BASE;
	if(!dram) {
		return -1;
	}
	cs_info_ptr->cs_number = 0;
	cs_info_ptr->cs0_size = 0;
	cs_info_ptr->cs1_size = 0;
	switch(dram->dram_type)
	{
	case DRAM_LPDDR2_1CS_2G_X32:
		cs_info_ptr->cs_number = 1;
		cs_info_ptr->cs0_size = 0x10000000;
		break;
	case DRAM_LPDDR2_1CS_4G_X32:
	case DRAM_LPDDR3_1CS_4G_X32:
		cs_info_ptr->cs_number = 1;
		cs_info_ptr->cs0_size = 0x20000000;
		break;
	case DRAM_LPDDR2_2CS_2G_X32:
		cs_info_ptr->cs_number = 2;
		cs_info_ptr->cs0_size = 0x08000000;
		cs_info_ptr->cs1_size = 0x08000000;
		break;
	case DRAM_LPDDR2_2CS_4G_X32:
		cs_info_ptr->cs_number = 2;
		cs_info_ptr->cs0_size = 0x10000000;
		cs_info_ptr->cs1_size = 0x10000000;
		break;
	case DRAM_LPDDR2_2CS_6G_X32:
		cs_info_ptr->cs_number = 2;
		cs_info_ptr->cs0_size = 0x20000000;
		cs_info_ptr->cs1_size = 0x10000000;
		break;
	case DRAM_LPDDR2_2CS_8G_X32:
	case DRAM_LPDDR3_2CS_8G_X32:
		cs_info_ptr->cs_number = 2;
		cs_info_ptr->cs0_size = 0x20000000;
		cs_info_ptr->cs1_size = 0x20000000;
		break;
	case DRAM_LPDDR2_1CS_8G_X32:
	case DRAM_LPDDR3_1CS_8G_X32:
	case DRAM_LPDDR2_1CS_4G_X16_2P:
		cs_info_ptr->cs_number = 1;
		cs_info_ptr->cs0_size = 0x40000000;
		break;
	case DRAM_LPDDR3_1CS_6G_X32:
		cs_info_ptr->cs_number = 1;
		cs_info_ptr->cs0_size = 0x30000000;
		break;
	case DRAM_LPDDR2_2CS_12G_X32:
	case DRAM_LPDDR3_2CS_12G_X32:
		cs_info_ptr->cs_number = 2;
		cs_info_ptr->cs0_size = 0x40000000;
		cs_info_ptr->cs1_size = 0x20000000;
		break;
	case DRAM_LPDDR3_2CS_6GX2_X32:
		cs_info_ptr->cs_number = 2;
		cs_info_ptr->cs0_size = 0x30000000;
		cs_info_ptr->cs1_size = 0x30000000;
		break;
	case DRAM_LPDDR3_2CS_16G_X32:
	case DRAM_LPDDR3_2CS_8G_X16_2P:
		cs_info_ptr->cs_number = 2;
		cs_info_ptr->cs0_size = 0x40000000;
		cs_info_ptr->cs1_size = 0x40000000-0x200000;
		break;
	case DRAM_LPDDR2_2CS_16G_X32:
		cs_info_ptr->cs_number = 2;
		cs_info_ptr->cs0_size = 0x40000000;
		cs_info_ptr->cs1_size = 0x40000000-0x200000;
		break;
	default:
		cs_info_ptr->cs_number = 1;
		cs_info_ptr->cs0_size = 0x20000000;
		break;
	}
#ifdef DDR_SIZE_FIXED_ON
       cs_info_ptr->cs_number = 1;
       total_size = cs_info_ptr->cs0_size + cs_info_ptr->cs1_size;
       cs_info_ptr->cs0_size = DDR_FIXED_SIZE;
       cs_info_ptr->cs1_size = 0;

       if (total_size < DDR_FIXED_SIZE)
       {
		cs_info_ptr->cs0_size = total_size;
       }
#endif
	return 0;
}
static void umctl_refresh_init(CLK_TYPE_E dmc_clk,DRAM_INFO_T *dram)
{
    uint32 i;

    for(i = 0; i < ARRAY_SIZE(DDR_TIMING_INFO); i++)
	{
		if(dmc_clk == DDR_TIMING_INFO[i].ddr_clk)
		{
            if(dram->row_num >= 15)
			{
                umctl->umctl_rfshtmg = DDR_TIMING_INFO[i].rfshtmg_l;
			}
			else
			{
                umctl->umctl_rfshtmg = DDR_TIMING_INFO[i].rfshtmg_s;
			}
		}
	}

	if(dmc_clk <= CLK_200MHZ)
	{
        umctl->umctl_rfshctl[0] &= ~(0x1f<<4);
        umctl->umctl_rfshctl[0] |= 0x1<<4;    //burst 2 refresh
	}

	umctl->umctl_rfshctl[1] = 0x10000;
}


static void umctl_zqctl_init(CLK_TYPE_E dmc_clk,DRAM_INFO_T *dram)
{
	uint32 i;

	for(i = 0; i < ARRAY_SIZE(DDR_TIMING_INFO); i++)
	{
		if(dmc_clk == DDR_TIMING_INFO[i].ddr_clk)
		{
            umctl->umctl_zqctl[0] = DDR_TIMING_INFO[i].zqctl0;
			umctl->umctl_zqctl[1] = DDR_TIMING_INFO[i].zqctl1;
		}
	}
}

static void umctl_dfi_init(CLK_TYPE_E dmc_clk,DRAM_INFO_T *dram)
{
    uint32 i;

     for(i = 0; i < ARRAY_SIZE(DDR_TIMING_INFO); i++)
	{
		if(dmc_clk == DDR_TIMING_INFO[i].ddr_clk)
		{
            umctl->umctl_dfitmg[0] = DDR_TIMING_INFO[i].dfitmg0;
		}
	}
	umctl->umctl_dfitmg[1] = 0x00030202;
	//dmc_reg_bits_set((uint32)&umctl->umctl_dfitmg[1],16, 5, dram->wl);
    //dmc_reg_bits_set((uint32)&umctl->umctl_dfitmg[1],8, 4, 2);
	//dmc_reg_bits_set((uint32)&umctl->umctl_dfitmg[1],0, 4, 2);

#ifdef PIKEL_DRIVER_SUPPORT_ON
	if(get_chip_id() == PIKEL_CHIP_ID)
	{
		umctl->umctl_dfilpcfg[0] = 0x0d00a100;
		umctl->umctl_hwlpctl = 0x00100003;
	}
	else
	{
		umctl->umctl_dfilpcfg[0] = 0x0700f000;
	}
#else
	umctl->umctl_dfilpcfg[0] = 0x0700f000;
#endif

	umctl->umctl_dfiupd[0] = 0x00400003;
	umctl->umctl_dfiupd[1] = 0x00020021;
	umctl->umctl_dfiupd[2] = 0x026904c9;
	umctl->umctl_dfiupd[3] = 0x030e051f;
}

static void umctl_odt_init(CLK_TYPE_E dmc_clk,DRAM_INFO_T *dram)
{
    uint32 i;
	DRAM_TYPE_E dram_type = (dram->dram_type & 0xf00);
	DDR_ACTIMING_T *ac_timing = (DDR_ACTIMING_T *)dram->ac_timing;
	/*wr odt hold*/
	dmc_reg_bits_set((uint32)&umctl->umctl_odtcfg,24,4,(dram->bl==8)?4:2);
	/*wr odt hold*/
	dmc_reg_bits_set((uint32)&umctl->umctl_odtcfg,16,4,0x0);
	/*rd odt hold*/
	dmc_reg_bits_set((uint32)&umctl->umctl_odtcfg, 8,4,(dram->bl==8)?4:2);
	/*rd odt delay*/
	dmc_reg_bits_set((uint32)&umctl->umctl_odtcfg, 2,4,(dram_type == DRAM_DDR3)?(dram->rl - dram->wl):0);
	/*wr odt block*/
	dmc_reg_bits_set((uint32)&umctl->umctl_odtcfg, 0,2,0x1);

	if(dram_type == DRAM_DDR3) {
		umctl->umctl_odtmap = 0x312;
	} else {
		umctl->umctl_odtmap = 0x000;
	}

	if(dram->dram_type == DRAM_LPDDR3)
	{
	    for(i = 0; i < ARRAY_SIZE(DDR_TIMING_INFO); i++)
		{
			if(dmc_clk == DDR_TIMING_INFO[i].ddr_clk)
			{
	            umctl->umctl_odtcfg = DDR_TIMING_INFO[i].odtcfg;
			}
		}
		umctl->umctl_odtmap = 0x00000101;
	}

}

static void umctl_performance_init(DRAM_INFO_T *dram)
{

}

static void umctl_trainctl_init(DRAM_INFO_T *dram)
{
}

static void umctl_tderate_init(DRAM_INFO_T *dram)
{
	/*tempurature derate configuration*/
}

static void umctl_port_en(UMCTL2_PORT_ID_E port,uint32 is_en)
{
	//umctl->umctl_pccfg = 0x00000011;
	//*(volatile uint32*)((uint32)&umctl->umctl_pcfgr0 + port * 0xb0) = 0x0001f000;
	//*(volatile uint32*)((uint32)&umctl->umctl_pcfgw0 + port * 0xb0) = 0x00004005;
	*(volatile uint32*)((uint32)&umctl->umctl_pctrl0 + port * 0xb0) = is_en;
}

void umctl_allport_en(uint32 is_en)
{
	unsigned int port;

	for(port=UMCTL2_PORT_MIN;port<UMCTL2_PORT_MAX;port++)
	{
		//*(volatile uint32*)((uint32)&umctl->umctl_pctrl0 + port * 0xb0) = is_en;
		umctl_port_en(port,is_en);
	}
}

static void umctl_port_init(umctl2_port_info_t* port_info)
{
	uint32 i = 0;
	//*** the ddr controller channel external priority setting***//
	//priority value: 0x0~0xf
	//description: 0xf is highest priority, 0x0 is lowest priority
	//priority setting: port4 wr&rd (CPx DSP)      =
	//                  port5 wr&rd (CP0W)         =
	//                  port6 wr&rd (CP0 ARM)      =
	//                  port8 wr&rd (CP1 ARM)      =
	//                  port9 wr&rd (CP2)          >
	//                  port2 rd    (display/gsp)  =
	//                  port0 wr    (mm/dcam/vsp)  >
	//                  port0 rd    (mm/dcam/vsp)  >
	//                  port3 wr&rd (CA7)          >
	//                  port2 wr    (display/gsp)  =
	//                  port7 wr&rd (AP matrix)    >
	//                  port1 wr&rd (GPU)
#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
	dmc_reg_bits_set(DDR_QOS_CFG1,  0,4,0x4); //chanel 0 wr qos, CA7
	dmc_reg_bits_set(DDR_QOS_CFG1,  4,4,0x4); //chanel 0 rd qos, CA7
	dmc_reg_bits_set(DDR_QOS_CFG1,  8,4,0x2); //chanel 1 wr qos, DISPLAY
	dmc_reg_bits_set(DDR_QOS_CFG1, 12,4,0xC); //chanel 1 rd qos, DISPLAY
	dmc_reg_bits_set(DDR_QOS_CFG1, 16,4,0x0); //chanel 2 wr qos, GPU/GSP
	dmc_reg_bits_set(DDR_QOS_CFG1, 20,4,0x0); //chanel 2 rd qos, GPU/gsp
	dmc_reg_bits_set(DDR_QOS_CFG1, 24,4,0xE); //chanel 3 wr qos,AP ZIP
	dmc_reg_bits_set(DDR_QOS_CFG1, 28,4,0xE); //chanel 3 rd qos, AP ZIP

	dmc_reg_bits_set(DDR_ID2QOS_SEL,4,1,0x1); //channel 4 qos select, 0:qos is for DDR_QOS_CFG1 1:qos is for DDR_ID2QOS_RCFG0
	dmc_reg_bits_set(DDR_ID2QOS_RCFG4,0,32,0x88048804); //channel 4 rd qos, vsp = 0x8, jpg = 8, dcam = 4;
	dmc_reg_bits_set(DDR_ID2QOS_WCFG4,0,32,0x66086608); //channel 4 wr qos, vsp = 0x6, jpg = 6, dcam = 8;

	dmc_reg_bits_set(DDR_ID2QOS_SEL,2,1,0x1); //channel 2 qos select, 0:qos is for DDR_QOS_CFG1 1:qos is for DDR_ID2QOS_RCFG1
	dmc_reg_bits_set(DDR_ID2QOS_RCFG2,0,32,0x02020202); //channel 2 rd qos, gsp = 0x2, gpu = 0;
	dmc_reg_bits_set(DDR_ID2QOS_WCFG2,0,32,0x02020202); //channel 2 wr qos, gsp = 0x2, gpu = 0;

	dmc_reg_bits_set(DDR_QOS_CFG2,  0,4,0xC); //chanel 4 wr qos, MM
	dmc_reg_bits_set(DDR_QOS_CFG2,  4,4,0x8); //chanel 4 rd qos, MM
	dmc_reg_bits_set(DDR_QOS_CFG2,  8,4,0xe); //chanel 5 wr qos, CP0ARM
	dmc_reg_bits_set(DDR_QOS_CFG2, 12,4,0xe); //chanel 5 rd qos, CP0ARM
	dmc_reg_bits_set(DDR_QOS_CFG2, 16,4,0xF); //chanel 6 wr qos, CP0 DSP
	dmc_reg_bits_set(DDR_QOS_CFG2, 20,4,0xF); //chanel 6 rd qos, CP0 DSP
	dmc_reg_bits_set(DDR_QOS_CFG2, 24,4,0xF); //chanel 7 wr qos, CP1ACCHARQ
	dmc_reg_bits_set(DDR_QOS_CFG2, 28,4,0xF); //chanel 7 rd qos, CP1ACCHARQ

	dmc_reg_bits_set(DDR_QOS_CFG3,  0,4,0xF); //chanel 8 wr qos, CP1 DSP
	dmc_reg_bits_set(DDR_QOS_CFG3,  4,4,0xF); //chanel 8 rd qos, CP1 DSP
	dmc_reg_bits_set(DDR_QOS_CFG3,  8,4,0xe); //chanel 9 wr qos, CP1CA5
	dmc_reg_bits_set(DDR_QOS_CFG3, 12,4,0xe); //chanel 9 rd qos, CP1CA5
#elif defined(CONFIG_SPX30G)
	dmc_reg_bits_set(DDR_QOS_CFG1,  0,4,0xc); //chanel 0 wr qos, mm/dcam/vsp
	dmc_reg_bits_set(DDR_QOS_CFG1,  4,4,0x8); //chanel 0 rd qos, mm/dcam/vsp
	dmc_reg_bits_set(DDR_QOS_CFG1,  8,4,0x0); //chanel 1 wr qos, GPU
	dmc_reg_bits_set(DDR_QOS_CFG1, 12,4,0x0); //chanel 1 rd qos, GPU
	dmc_reg_bits_set(DDR_QOS_CFG1, 16,4,0x2); //chanel 2 wr qos, display/gsp
	dmc_reg_bits_set(DDR_QOS_CFG1, 20,4,0xc); //chanel 2 rd qos, display/gsp
	dmc_reg_bits_set(DDR_QOS_CFG1, 24,4,0x4); //chanel 3 wr qos      , CA7
	dmc_reg_bits_set(DDR_QOS_CFG1, 28,4,0x4); //chanel 3 rd qos, CA7
	dmc_reg_bits_set(DDR_ID2QOS_SEL,0,1,0x1); //channel 0 qos select, 0:qos is for DDR_QOS_CFG1 1:qos is for DDR_ID2QOS_RCFG0
	dmc_reg_bits_set(DDR_ID2QOS_RCFG0,0,32,0x88048804); //channel 1 rd qos, vsp = 0x8, jpg = 8, dcam = 4;
	dmc_reg_bits_set(DDR_ID2QOS_WCFG0,0,32,0x66086608); //channel 1 wr qos, vsp = 0x6, jpg = 6, dcam = 8;

	dmc_reg_bits_set(DDR_ID2QOS_SEL,1,1,0x1); //channel 1 qos select, 0:qos is for DDR_QOS_CFG1 1:qos is for DDR_ID2QOS_RCFG1
	dmc_reg_bits_set(DDR_ID2QOS_RCFG1,0,32,0x02020202); //channel 1 rd qos, gsp = 0x2, gpu = 0;
	dmc_reg_bits_set(DDR_ID2QOS_WCFG1,0,32,0x02020202); //channel 1 wr qos, gsp = 0x2, gpu = 0;

	dmc_reg_bits_set(DDR_QOS_CFG2,  0,4,0xf); //chanel 4 wr qos, CPx DSP
	dmc_reg_bits_set(DDR_QOS_CFG2,  4,4,0xf); //chanel 4 rd qos, CPx DSP  HPR no use
	dmc_reg_bits_set(DDR_QOS_CFG2,  8,4,0xe); //chanel 5 wr qos, CP0W
	dmc_reg_bits_set(DDR_QOS_CFG2, 12,4,0xe); //chanel 5 rd qos, CP0W
	dmc_reg_bits_set(DDR_QOS_CFG2, 16,4,0xe); //chanel 6 wr qos, CP0 ARM
	dmc_reg_bits_set(DDR_QOS_CFG2, 20,4,0xe); //chanel 6 rd qos, CP0 ARM
	dmc_reg_bits_set(DDR_QOS_CFG2, 24,4,0x6); //chanel 7 wr qos, AP matrix
	dmc_reg_bits_set(DDR_QOS_CFG2, 28,4,0x6); //chanel 7 rd qos, AP matrix
	dmc_reg_bits_set(DDR_QOS_CFG3,  0,4,0xe); //chanel 8 wr qos, CP1 ARM
	dmc_reg_bits_set(DDR_QOS_CFG3,  4,4,0xe); //chanel 8 rd qos, CP1 ARM
	dmc_reg_bits_set(DDR_QOS_CFG3,  8,4,0xe); //chanel 9 wr qos, CP2
	dmc_reg_bits_set(DDR_QOS_CFG3, 12,4,0xe); //chanel 9 rd qos, CP2
#endif

	//umctl channel performance set
	//UMCTL2_REG_SET(UMCTL_PERFHPR0, 0x00000001);

#ifdef CONFIG_SPX30G
	UMCTL2_REG_SET(UMCTL_PERFHPR1, 0x10000001);
#else
	UMCTL2_REG_SET(UMCTL_PERFHPR1, 0x10000001);//sharkl & sharkl-t8 ramspeed optimize
#endif
	//UMCTL2_REG_SET(UMCTL_PERFLPR0, 0x00000100);
#ifdef CONFIG_SPX30G
	UMCTL2_REG_SET(UMCTL_PERFLPR1, 0x10000016);
#else
	UMCTL2_REG_SET(UMCTL_PERFLPR1, 0x10000100);//sharkl & sharkl-t8 ramspeed optimize
#endif
	//UMCTL2_REG_SET(UMCTL_PERFWR0,  0x00000020);
#ifdef CONFIG_SCX35LT8
	UMCTL2_REG_SET(UMCTL_PERFWR1,  0x10000080);
#else
	UMCTL2_REG_SET(UMCTL_PERFWR1,  0x10000100);
#endif
	//umctl channel policy set
#ifdef CONFIG_SPX30G
	UMCTL2_REG_SET(UMCTL_SCHED,0x08071501);//set low priority entry number
#else
	UMCTL2_REG_SET(UMCTL_SCHED,0x00071501);//set low priority entry number
#endif
	dmc_reg_bits_set(UMCTL_PCCFG,4,1,1);//pagematch_limit
	dmc_reg_bits_set(UMCTL_PCCFG,0,1,0);//go2critical_en
	//UMCTL2_REG_SET(UMCTL_PCCFG,0X10);

	for(i = 0; ;i++)
	{
		if(port_info[i].rdwr_order == 0xff)
		{
			return;
		}
		//read priority
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,16,1,port_info[i].rdwr_order);   //rdwr_ordered_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,15,1,port_info[i].rd_hpr);	   //rd_port_hpr_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,14,1,port_info[i].rd_pagematch); //rd_port_pagematch_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,13,1,port_info[i].rd_urgent);    //rd_port_urgent_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,12,1,port_info[i].rd_aging);	   //rd_port_aging_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,11,1,port_info[i].rd_reorder_bypass);//read_reorder_bypass_en
		dmc_reg_bits_set(UMCTL_PCFGR_0+i*0xb0,0,10,port_info[i].rd_priority);  //rd_port_priority

		//write priority
		dmc_reg_bits_set(UMCTL_PCFGW_0+i*0xb0,14,1,port_info[i].wr_pagematch); //wr_port_pagematch_en
		dmc_reg_bits_set(UMCTL_PCFGW_0+i*0xb0,13,1,port_info[i].wr_urgent);    //wr_port_urgent_en
		dmc_reg_bits_set(UMCTL_PCFGW_0+i*0xb0,12,1,port_info[i].wr_aging);	   //wr_port_aging_en
		dmc_reg_bits_set(UMCTL_PCFGW_0+i*0xb0,0,10,port_info[i].wr_priority);  //wr_port_priority
		#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
		if(port_info[i].rd_hpr)
		{
			dmc_reg_bits_set(UMCTL_PCFGQOS_0+i*0xb0,16,2,0x2);
			dmc_reg_bits_set(UMCTL_PCFGQOS_0+i*0xb0,20,2,0x2);
		}
		#elif defined(CONFIG_SPX30G)
		if(port_info[i].rd_hpr)
		{
			if(i==4)
			{
			  dmc_reg_bits_set(UMCTL_PCFGQOS_0+i*0xb0,16,2,0x1);
			  dmc_reg_bits_set(UMCTL_PCFGQOS_0+i*0xb0,20,2,0x1);
			}
			else
			{
			  dmc_reg_bits_set(UMCTL_PCFGQOS_0+i*0xb0,16,2,0x2);
			  dmc_reg_bits_set(UMCTL_PCFGQOS_0+i*0xb0,20,2,0x2);
			}
		}

		#endif
	}
}

void umctl_reg_init(CLK_TYPE_E dmc_clk,DRAM_INFO_T *dram,umctl2_port_info_t* port_info)
{
	umctl_basic_mode_init(dram);
	umctl_poweron_init(dmc_clk,dram);
	umctl_dramtiming_init(dmc_clk,dram);

#ifdef PIKEL_DRIVER_SUPPORT_ON
	if(get_chip_id() == PIKEL_CHIP_ID)
	{
		#ifndef CONFIG_SPX30G
		umctl_addrmap_init_pikel(dram);
		#endif
	}
	else
	{
		umctl_addrmap_init(dram);
	}
#else
	umctl_addrmap_init(dram);
#endif
	umctl_refresh_init(dmc_clk,dram);
	umctl_zqctl_init(dmc_clk,dram);
	umctl_dfi_init(dmc_clk,dram);
	umctl_odt_init(dmc_clk,dram);
	umctl_performance_init(dram);
	umctl_trainctl_init(dram);
	umctl_tderate_init(dram);

#ifdef PIKEL_DRIVER_SUPPORT_ON
	if(get_chip_id() == PIKEL_CHIP_ID)
	{
		umctl_port_init_pikel(port_info);
	}
	else
	{
		umctl_port_init(port_info);
	}
#else
	umctl_port_init(port_info);
#endif
}

void publ_basic_mode_init(DRAM_INFO_T *dram)
{
    DRAM_TYPE_E dram_type = (dram->dram_type & 0xf00);
	DDR_ACTIMING_T *ac_timing = dram->ac_timing;
	uint32 i = 0;

	/*data training address*/
	//publ->publ_dtar[0] = ((0x3f0 << 0)|(0x1fff << 12)|(0x7 << 28));
	#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
	publ->publ_iovcr[0] = 0x48484848;
	publ->publ_iovcr[1] = 0x48;
	#endif

	//set the DDR I/O mode to lpddr3
	dmc_reg_bits_set((uint32)&publ->publ_pgcr[1], 7, 2, 3);

	dmc_reg_bits_set((uint32)&publ->publ_pgcr[3], 3, 2, ac_timing->cntRDMode);
	dmc_reg_bits_set((uint32)&publ->publ_pgcr[3], 5, 4, ac_timing->cntRDDLY);

	#ifdef DDR_SCAN_SUPPORT_28NM
	//if make ddr scan we do not need to scan the second cs, we only training the 2nd cs to check if it working well or not
	publ->publ_dtcr	=	0x00003091 | ((dram->cs_num -1) << 25);
	#else
	publ->publ_dtcr	=	0x01003081 | ((dram->cs_num -1) << 25);
    #endif
	/*pubm2 read fifo bypass*/
	publ->publ_pgcr[3] |= (1 << 24);
	/*DQS gate extension*/
	dmc_reg_bits_set((uint32)&publ->publ_dsgcr, 6, 2, ac_timing->cntDQSGX);

	/*single data rate mode*/
	dmc_reg_bits_set((uint32)&publ->publ_dsgcr,19, 1, 1);
	#if PHY_PLL_BYPASS
	#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
	publ->publ_dsgcr &= ~(0x1 << 18);
	#else
	publ->publ_dsgcr |= (0x1 << 18);
	#endif
	/*pll power down*/
	dmc_reg_bits_set((uint32)&publ->publ_pllcr, 29, 3, 0x7);
	#else
	publ->publ_dsgcr &= ~(0x1 << 18);
	/*pll power on*/
	publ->publ_pllcr &= ~(0x07 << 29);
	#endif
	/* phy frequency select 166 ~ 275 */
	dmc_reg_bits_set((uint32)&publ->publ_pllcr, 19, 2, 0x3);
	/*ddr type & ddr bank config*/
	dmc_reg_bits_set((uint32)&publ->publ_dcr, 0, 3,((dram_type == DRAM_LPDDR2)?0:0)|
						  ((dram_type == DRAM_LPDDR3)?1:0)|
						  ((dram_type == DRAM_DDR2)?2:0)  |
						  ((dram_type == DRAM_DDR3)?3:0));

	dmc_reg_bits_set((uint32)&publ->publ_dcr, 3, 1,(dram_type == DRAM_LPDDR1)?0:1);
	/*programmable wait*/
	dmc_reg_bits_set((uint32)&publ->publ_zqcr, 8, 3, ac_timing->cntPGWAIT);
	/*output impedance divide select*/
	#ifdef CONFIG_SP8830GEA
	dmc_reg_bits_set((uint32)&publ->publ_zq0pr, 0, 4, 9); //ac
	dmc_reg_bits_set((uint32)&publ->publ_zq1pr, 0, 4, 9); //byte0/1
	dmc_reg_bits_set((uint32)&publ->publ_zq2pr, 0, 4, 9); //byte2/3
	#else
	dmc_reg_bits_set((uint32)&publ->publ_zq0pr, 0, 4, ac_timing->cntZQDIV); //ac
	dmc_reg_bits_set((uint32)&publ->publ_zq1pr, 0, 4, ac_timing->cntZQDIV); //byte0/1
	dmc_reg_bits_set((uint32)&publ->publ_zq2pr, 0, 4, ac_timing->cntZQDIV);	//byte2/3
	#endif
	//shut off odt
	dmc_reg_bits_set((uint32)&publ->publ_zq0pr, 4, 4, 0);
	dmc_reg_bits_set((uint32)&publ->publ_zq1pr, 4, 4, 0);
	dmc_reg_bits_set((uint32)&publ->publ_zq2pr, 4, 4, 0);

#if 1
	//shut off DXTEMOD odt
	*(volatile unsigned long*)(0X30010288) = 0Xaaaa;
	*(volatile unsigned long*)(0X30010308) = 0Xaaaa;
	*(volatile unsigned long*)(0X30010388) = 0Xaaaa;
	*(volatile unsigned long*)(0X30010408) = 0Xaaaa;
	*(volatile unsigned long*)(0X30010488) = 0Xaaaa;
	*(volatile unsigned long*)(0X30010508) = 0Xaaaa;
	*(volatile unsigned long*)(0X30010588) = 0Xaaaa;
	*(volatile unsigned long*)(0X30010608) = 0Xaaaa;
	*(volatile unsigned long*)(0X30010688) = 0Xaaaa;

	*(volatile unsigned long*)(0x300100ac) = 0;
#endif

	//zq calibration
	//publ->publ_pir |= ((1<<1)|(1<<0));
	//while((publ->publ_pgsr[0]&(0x1<<0)) != 0x1 );

	//delay line calibration
	//publ->publ_pir |= ((1<<5)|(1<<0));
	//while((publ->publ_pgsr[0]&(0x1<<0)) != 0x1 );

#if 1
	//zq power down
	dmc_reg_bits_set((uint32)&publ->publ_zqcr,2,1,1);
	for(i = 0; i < 100; i++);
	dmc_reg_bits_set((uint32)&publ->publ_zqcr,2,1,0);
	for(i = 0; i < 100; i++);

	//wait zq calibration done
	while((publ->publ_zq0sr&0x200) != 0x200);
	while((publ->publ_zq1sr&0x200) != 0x200);
	while((publ->publ_zq2sr&0x200) != 0x200);
#endif

#ifdef	CONFIG_SP8830GEA
	//set data slew rate
    dmc_reg_bits_set((uint32)&publ->publ_dxccr,13,2,3);

	//set ac slew rete
	dmc_reg_bits_set((uint32)&publ->publ_aciocr[0],30,2,3);
#else
	//set data slew rate
	dmc_reg_bits_set((uint32)&publ->publ_dxccr,13,2,0);

	//set ac slew rete
	dmc_reg_bits_set((uint32)&publ->publ_aciocr[0],30,2,0);
#endif

}

void publ_timing_init(DRAM_INFO_T *dram,CLK_TYPE_E dmc_clk)
{
	DDR_ACTIMING_T *ac_timing = (DDR_ACTIMING_T *)dram->ac_timing;

#if defined(DDR_LPDDR3)
#ifdef CONFIG_SCX35LT8
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 22, 4, 10);
#else
    dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 0, 4, 5);
    dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 4, 4, 5);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 8, 4, 11);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 12, 4, 9);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 16, 6, 29);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 22, 4, 8);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 26, 6, 47);

	dmc_reg_bits_set((uint32)&publ->publ_dtpr[2], 15, 4, 5);
#endif
	if(dmc_clk <= CLK_200MHZ)
	{
        dmc_reg_bits_set((uint32)&publ->publ_dtpr[1], 30, 2, 1);   //FOR LPDDR3 ODT turn on/off
		dmc_reg_bits_set((uint32)&publ->publ_dtpr[3], 0, 32, 0x11);
	}
	else if(dmc_clk <= CLK_400MHZ)
	{
        dmc_reg_bits_set((uint32)&publ->publ_dtpr[1], 30, 2, 1);   //FOR LPDDR3 ODT turn
		dmc_reg_bits_set((uint32)&publ->publ_dtpr[3], 0, 32, 0x1A);
	}
	else if(dmc_clk <= CLK_800MHZ)
	{
		dmc_reg_bits_set((uint32)&publ->publ_dtpr[1], 30, 2, 2);   //FOR LPDDR3 ODT turn
		dmc_reg_bits_set((uint32)&publ->publ_dtpr[3], 0, 32, 0x2b);
	}
#else
    dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 0, 4, 4);
    dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 4, 4, 4);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 8, 4, 15);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 12, 4, 12);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 16, 6, 22);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 22, 4, 6);
	dmc_reg_bits_set((uint32)&publ->publ_dtpr[0], 26, 6, 37);

	dmc_reg_bits_set((uint32)&publ->publ_dtpr[2], 15, 4, 3);
    if(dmc_clk <= CLK_200MHZ)
	{
		dmc_reg_bits_set((uint32)&publ->publ_dtpr[3], 0, 32, 0x11);
	}
	else if(dmc_clk <= CLK_400MHZ)
	{
		dmc_reg_bits_set((uint32)&publ->publ_dtpr[3], 0, 32, 0x1A);
	}
	else
	{
		dmc_reg_bits_set((uint32)&publ->publ_dtpr[3], 0, 32, 0x2b);
	}
#endif

}

void publ_mdr_init(CLK_TYPE_E dmc_clk,DRAM_INFO_T *dram)
{
    uint32 i;
	DRAM_TYPE_E dram_type = (dram->dram_type & 0xf00);
	DDR_ACTIMING_T *ac_timing = (DDR_ACTIMING_T *)dram->ac_timing;

	if(dram_type == DRAM_DDR3) {
		/*set publ burst len*/
		dmc_reg_bits_set((uint32)&publ->publ_mr[0], 0, 2,(dram->bl == 8)?0:2);
		/*cas latency */
		dmc_reg_bits_set((uint32)&publ->publ_mr[0], 4, 3, 4);
		/*dll reset*/
		dmc_reg_bits_set((uint32)&publ->publ_mr[0], 8, 1, 1);
		/*write recovery*/
		dmc_reg_bits_set((uint32)&publ->publ_mr[0], 9, 3, 4);
		publ->publ_mr[1] = 0x00000006;
		publ->publ_mr[2] = 0x00000008;

	} else if(dram_type == DRAM_LPDDR2) {
		publ->publ_mr[0] = 0x00000000;
		//publ->publ_mr[1] = ((0x2 << 0)|(/*0x4*/(ac_timing->tWR - 2)<< 5));
		//publ->publ_mr[2] = /*0x00000004*/dram->rl - 2; //400mhz:4 466mhz_533mhz:5
        
		for(i = 0; i < ARRAY_SIZE(DDR_TIMING_INFO); i++)
		{
			if(dmc_clk == DDR_TIMING_INFO[i].ddr_clk)
			{
                    publ->publ_mr[1] = DDR_TIMING_INFO[i].mr1;
					publ->publ_mr[2] = DDR_TIMING_INFO[i].mr2;
			}
		}
		dmc_reg_bits_set((uint32)&publ->publ_mr[3], 0, 4, 0x2);
	} else if(dram_type == DRAM_LPDDR3) {
		publ->publ_mr[0] = 0x00000000;
		//publ->publ_mr[1] = ((0x3 << 0)|(0x4 << 5));
		//publ->publ_mr[2] = 0x4;

		for(i = 0; i < ARRAY_SIZE(DDR_TIMING_INFO); i++)
		{
			if(dmc_clk == DDR_TIMING_INFO[i].ddr_clk)
			{
                    publ->publ_mr[1] = DDR_TIMING_INFO[i].mr1;
					publ->publ_mr[2] = DDR_TIMING_INFO[i].mr2;
			}
		}
		dmc_reg_bits_set((uint32)&publ->publ_mr[3], 0, 2, 0x2);
	}

}

void publ_eyetr_bitdeskew()
{
	volatile uint32 i = 0;
	volatile uint32 timeout = 9000;

	//shut off dfimisc to avoid umctl re-trigger
	umctl->umctl_dfimisc = 0x0;
	wait_pclk(50);

	//read fifo mode
	publ->publ_pgcr[3] &= ~(0x1000018);
	wait_pclk(50);

	//do read & write bit deskew
	publ->publ_pir |= 0xF001;
	wait_pclk(50);

	//wait training done
	while(timeout>0)
	{
		if((publ->publ_pgsr[0]&0xF01) == 0xF01)
		{
			break;
		}
		timeout--;
	}

	if(0 == timeout)
	{
		ddr_print("\r\nddr training not done!");
		__wdg_reset();
		while(1);
	}

	wait_pclk(50);

	//check if training error, hold
	if( publ->publ_pgsr[0] & 0x0F000000)
	{
		ddr_print("\r\nddr training error!");
		__wdg_reset();
		while(1);
	}

	//read fifo mode bypass
	publ->publ_pgcr[3] |=  (0x1000018);
	wait_pclk(50);

	//open dfimisc
	umctl->umctl_dfimisc = 0x1;
	wait_pclk(50);
}

void publ_reg_init(CLK_TYPE_E dmc_clk,DRAM_INFO_T *dram)
{
    // do not need for tshark
	//publ_poll_dllock();
	publ_basic_mode_init(dram);
	publ_timing_init(dram,dmc_clk);
	publ_mdr_init(dmc_clk,dram);
#ifdef PIKEL_DRIVER_SUPPORT_ON
	if(get_chip_id() == PIKEL_CHIP_ID)
	{
		publ_acio_init();
		publ_dxng_init();
	}
#endif
}

void ddr_lowpower_config(DRAM_INFO_T *dram)
{
	unsigned int i;
	DRAM_TYPE_E dram_type = (dram->dram_type & 0xf00);

	//close DM ODT
	publ->publ_dx0gcr[3] = 0x2000;
	publ->publ_dx1gcr[3] = 0x2000;
	publ->publ_dx2gcr[3] = 0x2000;
	publ->publ_dx3gcr[3] = 0x2000;

	if(dram_type != DRAM_DDR3) {
		publ->publ_aciocr[0] |= (1 << 27);
		publ->publ_aciocr[1] = 0xaaa00000;
		publ->publ_aciocr[2] = 0x55500000;

        if(dram->cs_num==2)
        {
		    publ->publ_aciocr[3] = 0x2aaaa0a8;     //can not be enable when use lpddr3
		    publ->publ_aciocr[4] = 0x15555054;
        }

		if(dram->cs_num==1)
	{
#ifdef CONFIG_SP9830AEB_5M_H100
		    publ->publ_aciocr[3] = 0x2aaaa0a8;     //can not be enable when use lpddr3
#else
		    publ->publ_aciocr[3] = 0x2aaaa8a8;     //can not be enable when use lpddr3
#endif
		    publ->publ_aciocr[4] = 0x15555454;
	}
		publ->publ_aciocr[5] = 0x005500aa;
	} else {
		publ->publ_aciocr[0] &= ~(1 << 27);
	}
	/*channel's clock gate config*/
	*(volatile unsigned int*)0x402b00f8 = 0xc00003ff;
	/*enter automatic powerdown*/
	umctl->umctl_pwrctl  = 0x0000000a;/*automatic power down*/

	//umctl->umctl_pwrctl  = 0x00000009;/*automatic self refresh*/

	umctl->umctl_hwlpctl = 0x00100003;/*hw lp enable*/ //bit[0] quasi bit[1] reset

#if defined(CONFIG_SPX30G)
	/*ligthsleep & deepsleep make selfrefresh close io*/
	//dmc_reg_bits_set((uint32)&publ->publ_dsgcr, 3, 2, 0x3);
	dmc_reg_bits_set((uint32)&publ->publ_dsgcr, 3, 2, 0x1);

	/*trigger enable*/
	umctl->umctl_dfilpcfg[0] = 0x0f00a100;
#endif

#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
#if PHY_PLL_BYPASS
	/*ligthsleep & deepsleep make selfrefresh close io*/
	//dmc_reg_bits_set((uint32)&publ->publ_dsgcr, 3, 2, 0x3);
	dmc_reg_bits_set((uint32)&publ->publ_dsgcr, 3, 2, 0x1);

	/*trigger enable*/

	umctl->umctl_dfilpcfg[0] = 0x0f00a100; //reset
#else
	//dmc_reg_bits_set((uint32)&publ->publ_dsgcr, 3, 2, 0x1);
	dmc_reg_bits_set((uint32)&publ->publ_dsgcr, 3, 2, 0x3);

	umctl->umctl_dfilpcfg[0] = 0x0f00f100; //reset

	publ->publ_ptr[0] = (128 << 21) | (512 <<  6) | 16;
	publ->publ_ptr[1] = (320 <<  16) | 1152;
#endif
#endif

#if defined(CONFIG_SC9630)|| defined(CONFIG_SCX35L64)
	/*ddr umctl retention enable*/
	*(volatile unsigned int*)0x402b012c |= ((1 << 25)|(1 << 28));
	*(volatile unsigned int*)0x402b0130 |= (1 << 0);
#else
    *(volatile unsigned int*)0x402b012c |= ((1 << 24)|(1 << 25)|(1 << 28));
#endif
	for(i=0;i<3;i++){
		/*double confirm clear force shutdown*/
		*(volatile unsigned int*)(lp_cfg.reg[i]) &= ~(1 << 25);
		if(lp_cfg.ddr_lowpower_cfg & (0x1 << i)){
			*(volatile unsigned int*)(lp_cfg.reg[i]) |= (1 << 24);
		} else {
			*(volatile unsigned int*)(lp_cfg.reg[i]) &= ~(1 << 24);
		}
	}
	/*close zq calibration*/
	dmc_reg_bits_set((uint32)&publ->publ_zqcr, 1, 2, 0x2);
}

#ifdef DDR_DFS_SUPPORT
void record_dfs_val(CLK_TYPE_E ddr_clk,uint32 record_base)
{
	//ddr_dfs_val_t dfs_val = {NULL};
	ddr_dfs_val_t dfs_val ;
	sprd_memset(&dfs_val , NULL , sizeof(ddr_dfs_val_t));
	uint32 i = 0;

	dfs_val.ddr_clk  = ddr_clk;

    //umctl regs
	dfs_val.umctl_rfshtmg    = umctl->umctl_rfshtmg;
	dfs_val.umctl_dramtmg0   = umctl->umctl_dramtmg[0];
	dfs_val.umctl_dramtmg1   = umctl->umctl_dramtmg[1];
	dfs_val.umctl_dramtmg2   = umctl->umctl_dramtmg[2];
	dfs_val.umctl_dramtmg3   = umctl->umctl_dramtmg[3];
	dfs_val.umctl_dramtmg4   = umctl->umctl_dramtmg[4];
	dfs_val.umctl_dramtmg5   = umctl->umctl_dramtmg[5];
//	dfs_val.umctl_dramtmg6   = umctl->umctl_dramtmg[6];
	dfs_val.umctl_dramtmg7   = umctl->umctl_dramtmg[7];
	dfs_val.umctl_dramtmg8   = umctl->umctl_dramtmg[8];
	dfs_val.umctl_dfitmg0    = umctl->umctl_dfitmg[0];
	dfs_val.umctl_init3      = umctl->umctl_init[3];
	dfs_val.umctl_zqctl0     = umctl->umctl_zqctl[0];
	dfs_val.umctl_zqctl1     = umctl->umctl_zqctl[1];

    //publ regs
    dfs_val.publ_mr1        = publ->publ_mr[1];
	dfs_val.publ_dx0gtr     = publ->publ_dx0gtr;
	dfs_val.publ_dx1gtr     = publ->publ_dx1gtr;
	dfs_val.publ_dx2gtr     = publ->publ_dx2gtr;
	dfs_val.publ_dx3gtr     = publ->publ_dx3gtr;
	dfs_val.publ_pgcr3      = publ->publ_pgcr[3];
	dfs_val.publ_acmdlr     = publ->publ_acmdlr;
	dfs_val.publ_dx0mdlr    = publ->publ_dx0mdlr;
	dfs_val.publ_dx1mdlr    = publ->publ_dx1mdlr;
	dfs_val.publ_dx2mdlr    = publ->publ_dx2mdlr;
	dfs_val.publ_dx3mdlr    = publ->publ_dx3mdlr;
	dfs_val.publ_aclcdlr    = publ->publ_aclcdlr;
	dfs_val.publ_dx0lcdlr0  = publ->publ_dx0lcdlr[0];
	dfs_val.publ_dx1lcdlr0  = publ->publ_dx1lcdlr[0];
	dfs_val.publ_dx2lcdlr0  = publ->publ_dx2lcdlr[0];
	dfs_val.publ_dx3lcdlr0  = publ->publ_dx3lcdlr[0];
	dfs_val.publ_dx0lcdlr1  = publ->publ_dx0lcdlr[1];
	dfs_val.publ_dx1lcdlr1  = publ->publ_dx1lcdlr[1];
	dfs_val.publ_dx2lcdlr1  = publ->publ_dx2lcdlr[1];
	dfs_val.publ_dx3lcdlr1  = publ->publ_dx3lcdlr[1];
	dfs_val.publ_dx0lcdlr2  = publ->publ_dx0lcdlr[2];
	dfs_val.publ_dx1lcdlr2  = publ->publ_dx1lcdlr[2];
	dfs_val.publ_dx2lcdlr2  = publ->publ_dx2lcdlr[2];
	dfs_val.publ_dx3lcdlr2  = publ->publ_dx3lcdlr[2];
	dfs_val.publ_dsgcr      = publ->publ_dsgcr;
	dfs_val.publ_dtpr0      = publ->publ_dtpr[0];
	dfs_val.publ_dtpr1      = publ->publ_dtpr[1];
	dfs_val.publ_dtpr2      = publ->publ_dtpr[2];
	dfs_val.publ_dtpr3      = publ->publ_dtpr[3];
	dfs_val.publ_mr2        = publ->publ_mr[2];


	for(i = 0; i<(sizeof(dfs_val)/4);i++)
	{
		REG32(record_base + i*4) = REG32((uint32)(&dfs_val)+i*4);
	}

}
#endif

//maddr: mrr address       vaddr: the final mrr value save address for example 0x1f00      oriaddr: the mrr value from dcu save address for example 0x1f04
uint32 read_mrr(uint32 cs, uint32 maddr, uint32 vaddr, uint32 oriaddr)
{
    uint32 i;
	uint32 value;

		dmc_reg_bits_set((uint32)&publ->publ_pgcr[3], 2, 1, 1);
		dmc_reg_bits_set((uint32)&publ->publ_pgcr[3], 3, 2, 0); //set to  asychronous read response for mrr operate
		dmc_reg_bits_set((uint32)&publ->publ_pgcr[3], 24, 1, 0); //set to  asychronous read response for mrr operate

		publ->publ_dcurr = 0x4;          //dcu reset
		publ->publ_dcurr = 0;            //NOP


		publ->publ_dcuar = 0x50;
		publ->publ_dcudr = 0xc0 | (cs << 3);
		publ->publ_dcuar = 0x40;
		publ->publ_dcudr = maddr << 16;
		publ->publ_dcurr = 0x400001;

		while((publ->publ_dcusr[0] & 0x1) != 1);

		publ->publ_dcuar = 0xa00;

		for(i=0;i<100;i++);
		value = publ->publ_dcudr;

        dmc_reg_bits_set((uint32)&publ->publ_pgcr[3], 2, 1, 0);

		REG32(oriaddr) = value;

#if defined(DDR_PINMAP_TYPE_0)
	value = (value>>11)&0x1 | (value>>8)&0x2 | (value>>8)&0x4 |
			(value>>5)&0x8 | (value>>9)&0x10 | (value>>7)&0x20 |
			(value>>9)&0x40 | (value>>7)&0x80;
#elif defined(DDR_PINMAP_TYPE_1)
	value = (value>>13)&0x1 | (value>>11)&0x2 | (value>>9)&0x4 |
            (value>>12)&0x8 | (value>>5)&0x10 | (value>>5)&0x20 |
			(value>>8)&0x40 | (value>>1)&0x80;

#elif defined(DDR_PINMAP_TYPE_2)
    value = (value>>12)&0x1 | (value>>14)&0x2 | (value>>7)&0x4 |
            (value>>10)&0x8 | (value>>7)&0x10 | (value>>3)&0x20 |
			(value>>8)&0x40 | (value>>3)&0x80;

#elif defined(DDR_PINMAP_TYPE_3)
    value = (value>>11)&0x1 | (value>>9)&0x2 | (value>>6)&0x4 |
            (value>>6)&0x8 | (value>>8)&0x10 | (value>>9)&0x20 |
			(value>>9)&0x40 | (value>>6)&0x80;
#elif defined(DDR_PINMAP_TYPE_4)
	value = (value>>15)&0x1 | (value>>11)&0x2 | (value>>7)&0x4 |
			(value>>10)&0x8 | (value>>7)&0x10 | (value>>3)&0x20 |
		    (value>>8)&0x40 | (value>>3)&0x80;
#endif

		REG32(vaddr) = value;

	return value;

}

#define UART1_TX_BUF_ADDR 0X70100000
#define UART1_TX_BUF_CNT ((REG32(0x70100000 + 0xc)>>8)&0xff)
void ddr_print(const unsigned char *string)
{
    unsigned char *s1 = NULL;

    s1 = string;

    while (*s1 != NULL)
    {
		//wait until uart1 tx fifo empty
		while(UART1_TX_BUF_CNT != 0);

		//put out char by uart1 tx fifo
		REG32(UART1_TX_BUF_ADDR) = *s1;
		s1++;
	}
}

void  __sdram_init(CLK_TYPE_E dmc_clk,umctl2_port_info_t* port_info,DRAM_INFO_T* dram, uint32 detect)
{
	volatile uint32 i = 0;
    dram_clk_set(dmc_clk << 1);

	 //enable umctl,publ,phy clock no need for tshark default value is enable
  //  umctl2_ctl_en(TRUE);

	umctl_soft_reset(TRUE);

	/*to dis-assert to not prevent dram init*/
	umctl->umctl_dfimisc = 0x0;

	/*to wait umctl in init status before we execute dram init*/
	while((umctl->umctl_stat & 0x7) != OPERATION_MODE_INIT);

	umctl_reg_init(dmc_clk,dram,port_info);

    //do publ init
	publ_reg_init(dmc_clk,dram);


	//release phy&publ soft reset
	i = *(volatile uint32*)(REG_AON_TOP_DDR_SLEEP_CTRL);
	i &= ~(0x500);
	*(volatile uint32*)(REG_AON_TOP_DDR_SLEEP_CTRL) = i;
	for(i=0;i<50;i++);


	//use umctl to init sdram
	while( (publ->publ_pgsr[0] & (0x1 << 0)) != 0x1 );

	publ->publ_pir |= ((1 << 18)|(1 << 0));
	while( (publ->publ_pgsr[0] & (0x1 << 0)) != 0x1 );


	//wait done
	//while( (publ->publ_pgsr[0] & (0x1 << 0)) != 0x1 );

	umctl->umctl_dfimisc = 0x1;
#ifdef PIKEL_DRIVER_SUPPORT_ON
	enter_quasi_mode();
#endif
	umctl_soft_reset(FALSE);

	//wait umctl until normal state
	while((umctl->umctl_stat & 0x7) != OPERATION_MODE_NORMAL);

	umctl_allport_en(1);

//#if 1
#ifdef CONFIG_NAND_SPL
    #ifndef DDR_SCAN_SUPPORT_28NM
	//first detect ddr type do not do ddr training or it may occur and while1
    if(detect == 0)
    {
		umctl->umctl_rfshctl3 |= 1;
		wait_pclk(100);

		//dqs_gating_training(dram);

		//publ_eye_training(dram);

		//publ_bit_deskew(dram);

		publ_eyetr_bitdeskew();
		umctl->umctl_rfshctl3 &= ~1;
    }
    //open zqcs zqcl
	umctl->umctl_zqctl[0] &= ~(3<<30);
	#endif
#endif

	if(detect==1)
	{
		umctl->umctl_hwlpctl &= ~(3<<0);//bit[0] quasi,bit[1] reset
		umctl->umctl_rfshctl3 |= 1<<0;
		umctl->umctl_dfiupd[0] |= 1<<31;
	}

	//ddr_lowpower_config(dram);

	/*work around wakeup from deepsleep cke can't not open*/
//	*(volatile uint32*)0x402b012c &= ~(1 << 24);
	return 0;
}


#ifdef DDR_AUTO_DETECT

#ifdef DDR_LPDDR2
static DDR_TYPE_E ddr_type_info[] = {S4_SDRAM};
static DDR_SIZE_E ddr_size_info[] = {SIZE_128MB,SIZE_256MB,SIZE_512MB,SIZE_1GB,SIZE_2GB,SIZE_4GB,SIZE_8GB,SIZE_16GB};
static DDR_WIDTH_E ddr_width_info[] = {WIDTH_X32,WIDTH_X16};
#endif

#ifdef DDR_LPDDR3
static DDR_TYPE_E ddr_type_info[] = {S8_SDRAM};
static DDR_SIZE_E ddr_size_info[] = {SIZE_4GB,SIZE_6GB,SIZE_8GB,SIZE_12GB,SIZE_16GB};
static DDR_WIDTH_E ddr_width_info[] = {WIDTH_X32,WIDTH_X16};
#endif

static DDR_INFO_STRUCT detect_info_cs0 = {NULL};
static DDR_INFO_STRUCT detect_info_cs1 = {NULL};
static DDR_INFO_STRUCT detect_info_final = {NULL};


uint32 is_detect_pass(uint32 mr_value, uint32 cs_num)
{
	uint32 i;
	uint32 check_result=0;
	DDR_INFO_STRUCT* detect_info;

	if(cs_num==0)
	{
		detect_info = &detect_info_cs0;
	}
	else
	{
		detect_info = &detect_info_cs1;
	}

	detect_info->mem_type = (mr_value & 0x3)>>0;
	detect_info->mem_size = (mr_value & 0x3c)>>2;
	detect_info->mem_width = (mr_value & 0xc0)>>6;

    for(i=0;i<sizeof(ddr_type_info)/sizeof(ddr_type_info[0]);i++)
    {
        if(detect_info->mem_type == ddr_type_info[i])
        {
            check_result |= 1<<0;
			break;
        }
	}


	for(i=0;i<sizeof(ddr_size_info)/sizeof(ddr_size_info[0]);i++)
	{
		if(detect_info->mem_size == ddr_size_info[i])
		{
			check_result |= 1<<1;
			break;
		}
	}


	for(i=0;i<sizeof(ddr_width_info)/sizeof(ddr_width_info[0]);i++)
	{
		if(detect_info->mem_width == ddr_width_info[i])
		{
			check_result |= 1<<2;
			break;
		}
	}

	if(check_result == 0x7)
	{
		return 1;
	}
	else
	    return 0;
}

void __sdram_auto_detect(void)
{
    uint32 mr_value;
    uint32 cs_num;
	uint32 mem_size;
	DRAM_INFO_T* dram_info = NULL;

    #ifdef DDR_LPDDR2
		DDR_TYPE_LOCAL = DRAM_LPDDR2_2CS_8G_X32;
    #endif

	#ifdef DDR_LPDDR3
		DDR_TYPE_LOCAL = DRAM_LPDDR3_2CS_8G_X32;
	#endif

	dram_info = get_dram_cfg(DDR_TYPE_LOCAL);

	__cal_actiming(dram_info,DDR_DFS_POINT[0]);
#ifdef PIKEL_DRIVER_SUPPORT_ON
	if(get_chip_id() == PIKEL_CHIP_ID)
	{
		__sdram_init(DDR_DFS_POINT[0], UMCTL2_PORT_CONFIG_PIKEL, dram_info, 1);
	}
	else
	{
		__sdram_init(DDR_DFS_POINT[0], UMCTL2_PORT_CONFIG, dram_info, 1);
	}
#else
	__sdram_init(DDR_DFS_POINT[0], UMCTL2_PORT_CONFIG, dram_info, 1);
#endif

	mr_value = read_mrr(0,8,DDR_AUTO_DETECT_INFO_BASE,DDR_AUTO_DETECT_INFO_BASE+4);

	if(!is_detect_pass(mr_value,0))
	{
		REG32(DDR_AUTO_DETECT_INFO_BASE+0x18) = 1;
		ddr_print("\r\nddr auto detect cs0 fail! retry detect");

		mr_value = REG32(0x80000000);
		mr_value = read_mrr(0,8,DDR_AUTO_DETECT_INFO_BASE+0x10,DDR_AUTO_DETECT_INFO_BASE+0x14);
		if(!is_detect_pass(mr_value,0))
		{
			ddr_print("\r\nddr auto detect cs0 fail!");
			__wdg_reset();
			while(1);
		}

	}
	cs_num = 0;
	ddr_print("\r\nddr auto detect cs0 ok!");

	mr_value = read_mrr(1,8,DDR_AUTO_DETECT_INFO_BASE+0x8,DDR_AUTO_DETECT_INFO_BASE+0xc);

    if(!is_detect_pass(mr_value,1))
	{
        ddr_print("\r\nddr auto detect cs1 fail!");
		detect_info_cs1.mem_size = 0;
	}
	else
	{
        cs_num++;
	}

    detect_info_final.mem_size = detect_info_cs0.mem_size+ detect_info_cs1.mem_size;
	detect_info_final.mem_type = detect_info_cs0.mem_type;
	detect_info_final.mem_width = detect_info_cs0.mem_width;

	//DDR_TYPE_LOCAL = (DDR_TYPE_LOCAL&0xf00) | (mem_size<<0) | (cs_num<<7);
	DDR_TYPE_LOCAL = (detect_info_final.mem_type<<8) | (detect_info_final.mem_size<<0) |
	                 (detect_info_final.mem_width<<5) | (cs_num<<7);
}

#endif


void sdram_init(void)
{
	#if defined(CONFIG_CLK_PARA)
	uint32 ddr_clk = mcu_clk_para.ddr_freq/1000000;
	#else
	uint32 ddr_clk = DDR_CLK ;
	#endif

	#ifdef DDR_DFS_SUPPORT
	uint32 i = 0;
	DRAM_INFO_T* dram_info = NULL;

#ifdef PIKEL_DRIVER_SUPPORT_ON
	is_pikel();
#endif

	//clear dfs value space
    for(i = 0; i < 256; i++)
	{
		REG32(DDR_DFS_VAL_BASE+i*4) = 0;
	}

	#ifdef DDR_AUTO_DETECT
		__sdram_auto_detect();
	#else
        DDR_TYPE_LOCAL = DDR_TYPE;
	#endif


	for(i = 0; i <ARRAY_SIZE(DDR_DFS_POINT); i++)
	{
	    dram_info = get_dram_cfg(DDR_TYPE_LOCAL);

		if(DDR_DFS_POINT[i] >= ddr_clk)
		{
			DDR_DFS_POINT[i] = ddr_clk;
		}

		__cal_actiming(dram_info,DDR_DFS_POINT[i]);
#ifdef PIKEL_DRIVER_SUPPORT_ON
		if(get_chip_id() == PIKEL_CHIP_ID)
		{
			__sdram_init(DDR_DFS_POINT[i], UMCTL2_PORT_CONFIG_PIKEL, dram_info,0);
		}
		else
		{
			__sdram_init(DDR_DFS_POINT[i], UMCTL2_PORT_CONFIG, dram_info,0);
		}
#else
		__sdram_init(DDR_DFS_POINT[i], UMCTL2_PORT_CONFIG, dram_info,0);
#endif

		record_dfs_val(DDR_DFS_POINT[i], DDR_DFS_VAL_BASE+sizeof(mem_cs_info_t)+sizeof(ddr_dfs_val_t)*i);
		if(DDR_DFS_POINT[i] >= ddr_clk)
		{
			REG32(DDR_DFS_VAL_BASE+sizeof(mem_cs_info_t)+sizeof(ddr_dfs_val_t)*(i+1)) = 0x12345678;
			break;
		}
	}

	REG32(DDR_DFS_VAL_BASE+sizeof(mem_cs_info_t)+sizeof(ddr_dfs_val_t)*ARRAY_SIZE(DDR_DFS_POINT)) = 0x12345678;

	#else
		DRAM_INFO * dram_info = NULL;

		dram_info = get_dram_cfg(DDR_TYPE_LOCAL);
		__cal_actiming(dram_info,ddr_clk);

#ifdef PIKEL_DRIVER_SUPPORT_ON
		if(get_chip_id() == PIKEL_CHIP_ID)
		{
			__sdram_init(ddr_clk, UMCTL2_PORT_CONFIG_PIKEL, dram_info,0);
		}
		else
		{
			__sdram_init(ddr_clk, UMCTL2_PORT_CONFIG, dram_info,0);
		}
#else
		__sdram_init(ddr_clk, UMCTL2_PORT_CONFIG, dram_info,0);
#endif

	#endif
	record_cs_info(dram_info);
	#ifdef DDR_SCAN_SUPPORT
		ddr_scan(dram_info);
		ddr_scan_data_update(DDR_CLK);
	#endif

	#ifndef DDR_SCAN_SUPPORT_28NM
	ddr_lowpower_config(dram_info);
	#endif
	
	#ifdef DDR_SCAN_SUPPORT_28NM
	ddr_scan_28nm(1);
	{
#ifdef PIKEL_DRIVER_SUPPORT_ON
		if(get_chip_id() == PIKEL_CHIP_ID)
		{
			__sdram_init_short(ddr_clk, UMCTL2_PORT_CONFIG_PIKEL, dram_info);
		}
		else
		{
			__sdram_init_short(ddr_clk, UMCTL2_PORT_CONFIG, dram_info);
		}
#else
		__sdram_init_short(ddr_clk, UMCTL2_PORT_CONFIG, dram_info);
#endif
	umctl->umctl_rfshctl3 |= 1;
	wait_pclk(100);
	publ_eyetr_bitdeskew();
	umctl->umctl_rfshctl3 &= ~1;
	}
	while(1);
	#endif
	//moved into __sdram_init
	//umctl2_low_power_open();
}

#ifdef DDR_SCAN_SUPPORT_28NM
void __sdram_init_short(CLK_TYPE_E dmc_clk,umctl2_port_info_t* port_info,DRAM_INFO_T* dram)
{
	volatile uint32 i = 0;

	umctl_soft_reset(TRUE);

	umctl->umctl_dfimisc = 0x0;

	while((umctl->umctl_stat & 0x7) != OPERATION_MODE_INIT);

	umctl_reg_init(dmc_clk,dram,port_info);

    //do publ init
	publ_reg_init(dmc_clk,dram);

	i = *(volatile uint32*)(REG_AON_TOP_DDR_SLEEP_CTRL);
	i &= ~(0x500);
	*(volatile uint32*)(REG_AON_TOP_DDR_SLEEP_CTRL) = i;
	for(i=0;i<50;i++);

	while( (publ->publ_pgsr[0] & (0x1 << 0)) != 0x1 );

	publ->publ_pir |= ((1 << 18)|(1 << 0));
	while( (publ->publ_pgsr[0] & (0x1 << 0)) != 0x1 );

	umctl->umctl_dfimisc = 0x1;

	umctl_soft_reset(FALSE);

	//wait umctl until normal state
	while((umctl->umctl_stat & 0x7) != OPERATION_MODE_NORMAL);

	umctl_allport_en(1);
}

void sdram_init_short()
{
	uint32 ddr_clk = mcu_clk_para.ddr_freq/1000000;
	DRAM_INFO_T* dram_info = NULL;
	dram_info = get_dram_cfg(DDR_TYPE_LOCAL);

#ifdef PIKEL_DRIVER_SUPPORT_ON
	if(get_chip_id() == PIKEL_CHIP_ID)
	{
		__sdram_init_short(ddr_clk,UMCTL2_PORT_CONFIG_PIKEL,dram_info);
	}
	else
	{
		__sdram_init_short(ddr_clk,UMCTL2_PORT_CONFIG,dram_info);
	}
#else
	__sdram_init_short(ddr_clk,UMCTL2_PORT_CONFIG,dram_info);
#endif
}
#endif


#ifndef _DRAM_PHY_28NM_H_
#define _DRAM_PHY_28NM_H_

#define NS2CLK_T(ns,clk)	(((clk)*(ns)+9999)/10000)
#define MAX(x,y)			(((x) > (y)) ? (x) : (y))

#define DDR_QOS_CFG1 0X30020010
#define DDR_QOS_CFG2 0X30020014
#define DDR_QOS_CFG3 0X30020018
#define DDR_ID2QOS_SEL 0X3002003C
#define DDR_ID2QOS_RCFG0 0X30020040
#define DDR_ID2QOS_WCFG0 0X30020080
#define DDR_ID2QOS_RCFG1 0X30020044
#define DDR_ID2QOS_WCFG1 0X30020084
#define DDR_ID2QOS_RCFG2 0X30020048
#define DDR_ID2QOS_WCFG2 0X30020088
#define DDR_ID2QOS_RCFG4 0X30020050
#define DDR_ID2QOS_WCFG4 0X30020090


#define UMCTL_BASE 0X30000000

//#define UMCTL_PERFHPR0 (UMCTL_BASE + 0x258)
#define UMCTL_PERFHPR1 (UMCTL_BASE + 0x25C)
//#define UMCTL_PERFLPR0 (UMCTL_BASE + 0x258)
#define UMCTL_PERFLPR1 (UMCTL_BASE + 0x264)
//#define UMCTL_PERFWR0  (UMCTL_BASE + 0x258)
#define UMCTL_PERFWR1  (UMCTL_BASE + 0x26C)

#define UMCTL_PCCFG    (UMCTL_BASE + 0x400)
#define UMCTL_PCFGR_0  (UMCTL_BASE + 0x0404+(0x00)*0xB0)
#define UMCTL_PCFGW_0  (UMCTL_BASE + 0x0408+(0x00)*0xB0)
#define UMCTL_PCFGQOS_0 (UMCTL_BASE + 0X494)
#define UMCTL_SCHED    (UMCTL_BASE + 0x250)


#define TRUE   1   /* Boolean true value. */
#define FALSE  0   /* Boolean false value. */

#if defined(DDR_LPDDR2)
//dramtmg_1: trc fast typi slow		dramtmg_4: trcd trp fast typi slow
#if defined(DDR_DEVICE_TYPE_FAST)
#define DRAMTMG_1_200M        0x0003030D
#define DRAMTMG_4_200M        0x04020404
#define DRAMTMG_1_384M        0x00040419
#define DRAMTMG_4_384M        0x07020508
#define DRAMTMG_1_400M        0x0004041A
#define DRAMTMG_4_400M        0x07020508
#define DRAMTMG_1_466M        0x0004051E
#define DRAMTMG_4_466M        0x0802060A
#define DRAMTMG_1_500M        0x00050520
#define DRAMTMG_4_500M        0x0902070A

#elif defined(DDR_DEVICE_TYPE_TYPI)
#define DRAMTMG_1_200M        0x0003030E
#define DRAMTMG_4_200M        0x04020405
#define DRAMTMG_1_384M        0x0004041A
#define DRAMTMG_4_384M        0x08020509
#define DRAMTMG_1_400M        0x0004041B
#define DRAMTMG_4_400M        0x0802050A
#define DRAMTMG_1_466M        0x00040520
#define DRAMTMG_4_466M        0x0A02060B
#define DRAMTMG_1_500M        0x00050522
#define DRAMTMG_4_500M        0x0A02070C

#elif defined(DDR_DEVICE_TYPE_SLOW)
#define DRAMTMG_1_200M        0x0003030F
#define DRAMTMG_4_200M        0x06020406
#define DRAMTMG_1_384M        0x0004041D
#define DRAMTMG_4_384M        0x0A02050C
#define DRAMTMG_1_400M        0x0004041E
#define DRAMTMG_4_400M        0x0B02050C
#define DRAMTMG_1_466M        0x00040523
#define DRAMTMG_4_466M        0x0D02060E
#define DRAMTMG_1_500M        0x00050525
#define DRAMTMG_4_500M        0x0D02070F

#else	//default type slow
#define DRAMTMG_1_200M        0x0003030F
#define DRAMTMG_4_200M        0x06020406
#define DRAMTMG_1_384M        0x0004041D
#define DRAMTMG_4_384M        0x0A02050C
#define DRAMTMG_1_400M        0x0004041E
#define DRAMTMG_4_400M        0x0B02050C
#define DRAMTMG_1_466M        0x00040523
#define DRAMTMG_4_466M        0x0D02060E
#define DRAMTMG_1_500M        0x00050525
#define DRAMTMG_4_500M        0x0D02070F
#endif

#elif defined(DDR_LPDDR3)

#if defined(DDR_DEVICE_TYPE_FAST)
#define DRAMTMG_1_192M        0x0003040D
#define DRAMTMG_4_192M        0x04040304
#define DRAMTMG_1_200M        0x0003040D
#define DRAMTMG_4_200M        0x04040304
#define DRAMTMG_1_384M        0x00030419
#define DRAMTMG_4_384M        0x07040508
#define DRAMTMG_1_400M        0x0003041A
#define DRAMTMG_4_400M        0x07040508
#define DRAMTMG_1_500M        0x00040420
#define DRAMTMG_4_500M        0x0904060A
#define DRAMTMG_1_533M        0x00040423
#define DRAMTMG_4_533M        0x0A04070B
#define DRAMTMG_1_600M        0x00050527
#define DRAMTMG_4_600M        0x0B04080C
#define DRAMTMG_1_640M        0x00050529
#define DRAMTMG_4_640M        0x0B04080D
#define DRAMTMG_1_667M        0x0006062B
#define DRAMTMG_4_667M        0x0C04090E
#define DRAMTMG_1_800M        0x00060634
#define DRAMTMG_4_800M        0x0E040A10

#elif defined(DDR_DEVICE_TYPE_TYPI)
#define DRAMTMG_1_192M        0x0003040D
#define DRAMTMG_4_192M        0x04040305
#define DRAMTMG_1_200M        0x0003040E
#define DRAMTMG_4_200M        0x04040305
#define DRAMTMG_1_384M        0x0003041A
#define DRAMTMG_4_384M        0x08040509
#define DRAMTMG_1_400M        0x0003041B
#define DRAMTMG_4_400M        0x0804050A
#define DRAMTMG_1_500M        0x00040422
#define DRAMTMG_4_500M        0x0A04060C
#define DRAMTMG_1_533M        0x00040424
#define DRAMTMG_4_533M        0x0B04070D
#define DRAMTMG_1_600M        0x00050529
#define DRAMTMG_4_600M        0x0C04080E
#define DRAMTMG_1_640M        0x0005052B
#define DRAMTMG_4_640M        0x0D04080F
#define DRAMTMG_1_667M        0x0006062D
#define DRAMTMG_4_667M        0x0E040910
#define DRAMTMG_1_800M        0x00060636
#define DRAMTMG_4_800M        0x10040A13

#elif defined(DDR_DEVICE_TYPE_SLOW)
#define DRAMTMG_1_192M        0x0003040F
#define DRAMTMG_4_192M        0x05040306
#define DRAMTMG_1_200M        0x0003040F
#define DRAMTMG_4_200M        0x06040306
#define DRAMTMG_1_384M        0x0003041D
#define DRAMTMG_4_384M        0x0A04050C
#define DRAMTMG_1_400M        0x0003041E
#define DRAMTMG_4_400M        0x0B04050C
#define DRAMTMG_1_500M        0x00040425
#define DRAMTMG_4_500M        0x0D04060F
#define DRAMTMG_1_533M        0x00040427
#define DRAMTMG_4_533M        0x0E040710
#define DRAMTMG_1_600M        0x0005052c
#define DRAMTMG_4_600M        0x10040812
#define DRAMTMG_1_640M        0x0005052F
#define DRAMTMG_4_640M        0x11040813
#define DRAMTMG_1_667M        0x00060631
#define DRAMTMG_4_667M        0x12040914
#define DRAMTMG_1_800M        0x0006063B
#define DRAMTMG_4_800M        0x15040A18

#else	//default type slow
#define DRAMTMG_1_192M        0x0003040F
#define DRAMTMG_4_192M        0x05040306
#define DRAMTMG_1_200M        0x0003040F
#define DRAMTMG_4_200M        0x06040306
#define DRAMTMG_1_384M        0x0003041D
#define DRAMTMG_4_384M        0x0A04050C
#define DRAMTMG_1_400M        0x0003041E
#define DRAMTMG_4_400M        0x0B04050C
#define DRAMTMG_1_500M        0x00040425
#define DRAMTMG_4_500M        0x0D04060F
#define DRAMTMG_1_533M        0x00040427
#define DRAMTMG_4_533M        0x0E040710
#define DRAMTMG_1_600M        0x0005052c
#define DRAMTMG_4_600M        0x10040812
#define DRAMTMG_1_640M        0x0005052F
#define DRAMTMG_4_640M        0x11040813
#define DRAMTMG_1_667M        0x00060631
#define DRAMTMG_4_667M        0x12040914
#define DRAMTMG_1_800M        0x0006063B
#define DRAMTMG_4_800M        0x15040A18
#endif
#endif

typedef struct
{
    unsigned long ddr_clk;
    unsigned long dramtmg0;
    unsigned long dramtmg1;
    unsigned long dramtmg2;
    unsigned long dramtmg3;
    unsigned long dramtmg4;
    unsigned long dramtmg5;

    unsigned long dramtmg6;
    unsigned long dramtmg7;
    unsigned long dramtmg8;
    unsigned long rfshtmg_s;
	unsigned long rfshtmg_l;

	unsigned long init0;
	unsigned long init1;
	unsigned long init2;
	unsigned long init3;
	unsigned long init4;
	unsigned long init5;

	unsigned long dfitmg0;
	unsigned long mr1;
	unsigned long mr2;
	unsigned long odtcfg;
	unsigned long zqctl0;
	unsigned long zqctl1;
}dram_timing_t;

typedef struct
{
    unsigned long int rdwr_order;
    unsigned long int rd_hpr;
    unsigned long int rd_pagematch;
    unsigned long int rd_urgent;
    unsigned long int rd_aging;
    unsigned long int rd_reorder_bypass;
    unsigned long int rd_priority;

    unsigned long int wr_pagematch;
    unsigned long int wr_urgent;
    unsigned long int wr_aging;
    unsigned long int wr_priority;
}umctl2_port_info_t;


//BIT0~BIT4: SIZE         BIT5~BIT6: WIDTH         BIT7: CS          BIT8~BIT9: TYPE
typedef enum
{
	//lpddr1
  DRAM_LPDDR1			  = 0x500, /*ALso called mobileDDR*/
  DRAM_LPDDR1_1CS_2G_X32  = 0x501,
  DRAM_LPDDR1_2CS_4G_X32  = 0x502,
#if 0
  //lpddr2
  DRAM_LPDDR2			  = 0x000,
  DRAM_LPDDR2_S2		  = 0x101,
  DRAM_LPDDR2_S4		  = 0x002,
#endif
  DRAM_LPDDR2			  = 0x000,
  DRAM_LPDDR2_1CS_1G_X32  = 0x004,
  DRAM_LPDDR2_1CS_2G_X32  = 0x005,
  DRAM_LPDDR2_1CS_4G_X32  = 0x006,
  DRAM_LPDDR2_1CS_8G_X32  = 0x007,
  DRAM_LPDDR2_1CS_16G_X32 = 0x008,
  DRAM_LPDDR2_1CS_32G_X32 = 0x009,
  DRAM_LPDDR2_2CS_2G_X32  = 0x088,
  DRAM_LPDDR2_2CS_4G_X32  = 0x08A,
  DRAM_LPDDR2_2CS_6G_X32  = 0x08B,
  DRAM_LPDDR2_2CS_8G_X32  = 0x08C,
  DRAM_LPDDR2_2CS_12G_X32 = 0x08D,
  DRAM_LPDDR2_2CS_16G_X32 = 0x08E,
  DRAM_LPDDR2_1CS_4G_X16_2P = 0x026,
  //lpddr3
  DRAM_LPDDR3			  = 0x300,
  DRAM_LPDDR3_1CS_4G_X32  = 0x306,
  DRAM_LPDDR3_1CS_6G_X32  = 0x30E,
  DRAM_LPDDR3_1CS_8G_X32  = 0x307,
  DRAM_LPDDR3_1CS_12G_X32  = 0x30D,
  DRAM_LPDDR3_1CS_16G_X32  = 0x308,
  DRAM_LPDDR3_1CS_32G_X32  = 0x309,
  DRAM_LPDDR3_2CS_8G_X32  = 0x38C,
  DRAM_LPDDR3_2CS_12G_X32 = 0x38D,
  DRAM_LPDDR3_2CS_6GX2_X32 = 0x39C,
  DRAM_LPDDR3_2CS_16G_X32 = 0x38E,
  DRAM_LPDDR3_2CS_8G_X16_2P = 0x3ac,

  //ddr2
  DRAM_DDR2 			  = 0x600,
  //ddr3
  DRAM_DDR3 			  = 0x400,
  DRAM_DDR3_1CS_2G_X8	  = 0x401,
  DRAM_DDR3_1CS_4G_X8	  = 0x402,
  DRAM_DDR3_1CS_8G_X8	  = 0x403,
  DRAM_DDR3_1CS_2G_X8_4P  = 0x404, //4-piece 2g bit ddr3 chips, 4 cs bonded into 1 cs, 8g bit together
  DRAM_DDR3_1CS_4G_X8_4P  = 0x405, //4-piece 4g bit ddr3 chips, 4 cs bonded into 1 cs, 16g bit together
  DRAM_DDR3_1CS_8G_X8_4P  = 0x406, //4-piece 8g bit ddr3 chips, 4 cs bonded into 1 cs, 32g bit together
  DRAM_DDR3_1CS_1G_X16	  = 0x407,
  DRAM_DDR3_1CS_2G_X16	  = 0x408,
  DRAM_DDR3_1CS_4G_X16	  = 0x409,
  DRAM_DDR3_1CS_8G_X16	  = 0x40A,
  DRAM_DDR3_2CS_2G_X16	  = 0x40B,
  DRAM_DDR3_2CS_4G_X16	  = 0x40C,
  DRAM_DDR3_2CS_8G_X16	  = 0x40D,
  DRAM_DDR3_2CS_16G_X16   = 0x40E,

  DRAM_DDR3_1CS_1G_X16_2P = 0x40F,
  DRAM_DDR3_1CS_2G_X16_2P = 0x410, //2-piece 2g bit ddr3 chips, 2 cs bonded into 1 cs, 4g bit together
  DRAM_DDR3_1CS_4G_X16_2P = 0x411, //2-piece 4g bit ddr3 chips, 2 cs bonded into 1 cs, 8g bit together
  DRAM_DDR3_1CS_8G_X16_2P = 0x412, //2-piece 8g bit ddr3 chips, 2 cs bonded into 1 cs, 16g bit together
}DRAM_TYPE_E;

typedef enum{
	CLK_24MHZ	= 24,
	CLK_26MHZ	= 26,
	CLK_38_4MHZ	= 38,
	CLK_48MHZ	= 48,
	CLK_64MHZ	= 64,
	CLK_76_8MHZ	= 77,
	CLK_96MHZ	= 96,
	CLK_100MHZ	= 100,
	CLK_153_6MHZ	= 154,
	CLK_150MHZ	= 150,
	CLK_166MHZ	= 166,
	CLK_192MHZ	= 192,
	CLK_200MHZ	= 200,
	CLK_250MHZ	= 250,
	CLK_267MHZ	= 267,
	CLK_300MHZ	= 300,
	CLK_332MHZ	= 332,
	CLK_333MHZ	= 333,
	CLK_384MHZ	= 384,
	CLK_400MHZ	= 400,
	CLK_427MHZ	= 427,
	CLK_450MHZ	= 450,
	CLK_464MHZ	= 464,
	CLK_466MHZ	= 466,
	CLK_467MHZ	= 467,
	CLK_500MHZ	= 500,
	CLK_525MHZ	= 525,
	CLK_533MHZ	= 533,
	CLK_537MHZ	= 537,
	CLK_540MHZ	= 540,
	CLK_550MHZ	= 550,
	CLK_600MHZ  = 600,
	CLK_640MHZ  = 640,
	CLK_667MHZ  = 667,
	CLK_800MHZ	= 800,
	CLK_1000MHZ	= 1000,
	EMC_CLK_400MHZ	= 400,
	EMC_CLK_450MHZ	= 450,
	EMC_CLK_500MHZ	= 500
}CLK_TYPE_E;

typedef enum
{
	DRAM_BT_SEQ = 0, //burst type = sequential(default)
	DRAM_BT_INTER= 1 //burst type = interleaved
}DRAM_BURSTTYPE_E;

typedef enum
{
	DRAM_WRAP   = 0, //warp mode
	DRAM_NOWRAP = 1  //no warp mode
}DRAM_WC_E;

typedef enum
{
/*Driver strength for lpddr1*/
	LPDDR1_DS_FULL,
	LPDDR1_DS_HALF,
	LPDDR1_DS_QUARTER,
	LPDDR1_DS_OCTANT,
	LPDDR1_DS_THREE_QUATERS,
/*Driver strength for lpddr2*/
	LPDDR2_DS_34R3 = 0x01,
	LPDDR2_DS_40R  = 0x02,
	LPDDR2_DS_48R  = 0x03,
	LPDDR2_DS_60R  = 0x04,
	LPDDR2_DS_68R6 = 0x05,
	LPDDR2_DS_80R  = 0x06,
	LPDDR2_DS_120R = 0x07,
/*Driver strength for ddr3*/
	DDR3_DS_40R    = 0x00,
	DDR3_DS_34R3   = 0x01
}MEM_IODS_E;

typedef enum
{
	PUBL_LPDDR1_DS_33OHM = 0xa,
	PUBL_LPDDR1_DS_31OHM = 0xb,
	PUBL_LPDDR1_DS_48OHM = 0xc,
	PUBL_LPDDR1_DS_43OHM = 0xd,
	PUBL_LPDDR1_DS_39OHM = 0xe,
	PUBL_LPDDR1_DS_55OHM = 0x5,
	PUBL_LPDDR1_DS_64OHM = 0x4,

	PUBL_LPDDR2_DS_MIN   = 0xd,
	PUBL_LPDDR2_DS_34OHM = 0xd,
	PUBL_LPDDR2_DS_40OHM = 0xb,
	PUBL_LPDDR2_DS_48OHM = 0x9,
	PUBL_LPDDR2_DS_60OHM = 0x7,
	PUBL_LPDDR2_DS_80OHM = 0x5,
	PUBL_LPDDR2_DS_MAX   = 0x5,

	PUBL_DDR3_DS_34OHM   = 0xd,
	PUBL_DDR3_DS_40OHM   = 0xb

}PUBL_DS_E;

typedef enum
{
	UMCTL2_PORT_MIN     = 0,
	UMCTL2_PORT_AP      = 0,
	UMCTL2_PORT_MM      = 1,
	UMCTL2_PORT_GPU     = 2,
	UMCTL2_PORT_CP2_P0  = 3,
	UMCTL2_PORT_CP1     = 4,
	UMCTL2_PORT_AP_MTX  = 5,
	UMCTL2_PORT_CP0     = 6,
	UMCTL2_PORT_CP2_P1  = 7,
	UMCTL2_PORT_CP0_MTX = 8,
	UMCTL2_PORT_DSP     = 9,
	UMCTL2_PORT_MAX     = 10
}UMCTL2_PORT_ID_E;

typedef enum
{
	OPERATION_MODE_INIT   = 0x0,
	OPERATION_MODE_NORMAL = 0x1,
	OPERATION_MODE_PD     = 0x2,
	OPERATION_MODE_SR     = 0x3,
	OPERATION_MODE_DPD    = 0x4
}OPERATION_MODE_E;

typedef enum
{
    S4_SDRAM = 0,
	S2_SDRAM = 1,
	N_NVM = 2,

	S8_SDRAM = 3
}DDR_TYPE_E;

typedef enum
{
    SIZE_64MB = 0,
	SIZE_128MB = 1,
	SIZE_256MB = 2,
	SIZE_512MB = 3,
	SIZE_1GB  =  4,
	SIZE_2GB  =  5,
	SIZE_4GB  =  6,
	SIZE_8GB  =  7,
	SIZE_16GB =  8,
	SIZE_32GB =  9,

	SIZE_6GB  =  14,
	SIZE_12GB =  13
}DDR_SIZE_E;

typedef enum
{
    WIDTH_X32 = 0,
	WIDTH_X16 = 1,
	WIDTH_X8 = 2
}DDR_WIDTH_E;

typedef struct
{
    unsigned int mem_size;
	unsigned int mem_width;
	unsigned int mem_type;
}DDR_INFO_STRUCT;

typedef struct
{
	unsigned int tREFI;		/*average refresh interval time between each row normal=7800ns*/
	unsigned int tMRD;		/*lpddr1:set lpddr2:sbz ddr3:set*/
	unsigned int tRAS;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tRC;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tRFC;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tRCD;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tRP;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tRRD;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tWR;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tWTR;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tXSR;		/*lpddr1:set lpddr2:set ddr3:sbz*/
	unsigned int tXP;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tCKE;		/*lpddr1:set lpddr2:set ddr3:set*/
	unsigned int tRFCab;		/*lpddr1:sbz lpddr2:set ddr3:sbz*/
	unsigned int tRFCpb;		/*lpddr1:sbz lpddr2:set ddr3:sbz*/
	unsigned int tZQINIT;		/*lpddr1:sbz lpddr2:set ddr3:set*/
	unsigned int tZQCL;		/*lpddr1:sbz lpddr2:set ddr3:sbz*/
	unsigned int tZQCS;		/*lpddr1:sbz lpddr2:set ddr3:set*/
	unsigned int tZQreset;		/*lpddr1:sbz lpddr2:set ddr3:sbz*/
	unsigned int tZQoper;		/*lpddr1:sbz lpddr2:sbz ddr3:set*/
	unsigned int tCKESR;		/*lpddr1:sbz lpddr2:set ddr3:sbz*/
	unsigned int tCCD;		/*lpddr1:sbz lpddr2:set ddr3:set*/
	unsigned int tRTP;		/*lpddr1:sbz lpddr2:set ddr3:set*/
	unsigned int tFAW;		/*lpddr1:sbz lpddr2:set ddr3:set*/
	unsigned int tDPD;		/*lpddr1:sbz lpddr2:set ddr3:sbz*/
	unsigned int tDQSCK;		/*lpddr1:sbz lpddr2:set ddr3:set*/
	unsigned int tDQSCKmax;		/*lpddr1:sbz lpddr2:set ddr3:sbz*/
	unsigned int tMRW;		/*lpddr1:sbz lpddr2:set ddr3:sbz*/
	unsigned int tMRR;		/*lpddr1:sbz lpddr2:set ddr3:sbz*/
	unsigned int tDLLK;		/*lpddr1:sbz lpddr2:sbz ddr3:set*/
	unsigned int tMOD;		/*lpddr1:sbz lpddr2:sbz ddr3:set*/
	unsigned int tXS;		/*lpddr1:sbz lpddr2:sbz ddr3:set*/
	unsigned int tCKSRE;		/*lpddr1:sbz lpddr2:sbz ddr3:set*/
	unsigned int tCKSRX;		/*lpddr1:sbz lpddr2:sbz ddr3:set*/
	unsigned int cntRDMode;
	unsigned int cntRDDLY;
	unsigned int cntDQSGX;
	unsigned int cntPGWAIT;
	unsigned int cntZQDIV;
}DDR_ACTIMING_T;

typedef struct
{
	DRAM_TYPE_E 	dram_type;
	unsigned int	cs_num;		/*ranks number*/
	unsigned int	bank_num;	/*banks number*/
	unsigned int	io_width;	/*bus width*/
	unsigned int	row_num;		/*row number*/
	unsigned int	wc;		/*wrap control*/
	unsigned int	bl;		/*burst length*/
	unsigned int	rl;		/*read cas latency*/
	unsigned int	wl;		/*write cas latency*/
	unsigned int	al;		/*ddr2 ddr3 only Posted CAS additive latency*/
	DDR_ACTIMING_T	*ac_timing;
	DDR_ACTIMING_T	*native_ac_timing;
}DRAM_INFO_T;

typedef struct
{
	volatile unsigned int umctl_mstr;	/* 0x0000 master register*/
	volatile unsigned int umctl_stat;	/* 0x0004 operating mode status*/
	volatile unsigned int umctl_resv0[2];	/* 0x0008 ~ 0x000c*/
	volatile unsigned int umctl_mrctrl[2];	/* 0x0010 ~ 0x0014 mode register control*/
	volatile unsigned int umctl_mrstat;	/* 0x0018 mode register status*/
	volatile unsigned int umctl_resv1;	/* 0x001c */
	volatile unsigned int umctl_derateen;	/* 0x0020 temperature derate enable*/
	volatile unsigned int umctl_derateint;	/* 0x0024 temperature derate interval*/
	volatile unsigned int umctl_resv2[2];	/* 0x0028 ~ 0x002c */
	volatile unsigned int umctl_pwrctl;	/* 0x0030 low power control*/
	volatile unsigned int umctl_pwrtmg;	/* 0x0034 low power timing*/
	volatile unsigned int umctl_hwlpctl;	/* 0x0038 hardware low power control*/
	volatile unsigned int umctl_resv3[5];	/* 0x003c ~ 0x004c */
	volatile unsigned int umctl_rfshctl[3];	/* 0x0050 ~ 0x0058 refresh control*/
	volatile unsigned int umctl_resv4;	/* 0x005c */
	volatile unsigned int umctl_rfshctl3;	/* 0x0060 refresh control*/
	volatile unsigned int umctl_rfshtmg;	/* 0x0064 refresh timing*/
	volatile unsigned int umctl_resv5[2];	/* 0x0068 ~ 0x006c */
	volatile unsigned int umctl_ecccfg[2];	/* 0x0070 ~ 0x0074 ecc configruation*/
	volatile unsigned int umctl_eccstat;	/* 0x0078 ecc status*/
	volatile unsigned int umctl_eccclr;	/* 0x007c ecc clear*/
	volatile unsigned int umctl_eccerrcnt;	/* 0x0080 ecc error count*/
	volatile unsigned int umctl_ecccaddr[2];/* 0x0084 ~ 0x0088 ecc corrected error address*/
	volatile unsigned int umctl_ecccsyn[3];	/* 0x008c ~ 0x0094 ecc corrected syndrome*/
	volatile unsigned int umctl_eccbitmask[3];	/* 0x0098 ~ 0x00a0 ecc corrected data bit mask*/
	volatile unsigned int umctl_eccuaddr[2];/* 0x00a4 ~ 0x00a8 ecc unorrected error address*/
	volatile unsigned int umctl_eccusyn[3];	/* 0x00ac ~ 0x00b4 ecc uncorrected syndrome*/
	volatile unsigned int umctl_eccpoisonaddr[2];	/* 0x00b8 ~ 0x00bc ecc data poisoning address*/
	volatile unsigned int umctl_parctl;	/* 0x00c0 parity control*/
	volatile unsigned int umctl_parstat;	/* 0x00c4 parity status*/
	volatile unsigned int umctl_resv6[2];	/* 0x00c8 ~ 0x00cc */
	volatile unsigned int umctl_init[8];	/* 0x00d0 ~ 0x00ec sdram initialization*/
	volatile unsigned int umctl_dimmctl;	/* 0x00f0 dimm control*/
	volatile unsigned int umctl_rankctl;	/* 0x00f4 rank control*/
	volatile unsigned int umctl_resv7[2];	/* 0x00f8 ~ 0x00fc*/
	volatile unsigned int umctl_dramtmg[12];/* 0x0100 ~ 0x012c sdram timing*/
	volatile unsigned int umctl_resv8[20];	/* 0x0130 ~ 0x017c */
	volatile unsigned int umctl_zqctl[3];	/* 0x0180 ~ 0x0188 zq control*/
	volatile unsigned int umctl_zqstat;	/* 0x018c zq status*/
	volatile unsigned int umctl_dfitmg[2];	/* 0x0190 ~ 0x0194 dfi timing*/
	volatile unsigned int umctl_dfilpcfg[2];/* 0x0198 ~ 0x019c dfi low power configruation*/
	volatile unsigned int umctl_dfiupd[4];	/* 0x01a0 ~ 0x01ac dfi update*/
	volatile unsigned int umctl_dfimisc;	/* 0x01b0 dfi miscellaneous control*/
	volatile unsigned int umctl_resv9[3];	/* 0x01b4 ~ 0x01bc */
	volatile unsigned int umctl_dbictl;	/* 0x01c0 dm/dbi control*/
	volatile unsigned int umctl_resv10[3];	/* 0x01c4 ~ 0x01cc */
	volatile unsigned int umctl_trainctl[3];/* 0x01d0 ~ 0x01d8 phy eval training control*/
	volatile unsigned int umctl_trainstat;	/* 0x01dc phy eval training status */
	volatile unsigned int umctl_resv11[8];	/* 0x01e0 ~ 0x01fc */
	volatile unsigned int umctl_addrmap[9];	/* 0x0200 ~ 0x0220 address map */
	volatile unsigned int umctl_resv12[7];	/* 0x0224 ~ 0x023c */
	volatile unsigned int umctl_odtcfg;	/* 0x0240 odt configruation */
	volatile unsigned int umctl_odtmap;	/* 0x0244 odt/rank map */
	volatile unsigned int umctl_resv13[2];	/* 0x0248 ~ 0x024c */
	volatile unsigned int umctl_sched;	/* 0x0250 scheduler control */
	volatile unsigned int umctl_resv14;	/* 0x0254 */
	volatile unsigned int umctl_perfhpr[2];	/* 0x0258 ~ 0x025c high priority read*/
	volatile unsigned int umctl_perflpr[2];	/* 0x0260 ~ 0x0264 low priority read */
	volatile unsigned int umctl_perfwr[2];	/* 0x0268 ~ 0x026c write cam */
	volatile unsigned int umctl_resv15[36];	/* 0x0270 ~ 0x02fc */
	volatile unsigned int umctl_dbg[2];	/* 0x0300 ~ 0x0304 debug*/
	volatile unsigned int umctl_dbgcam;	/* 0x0308 cam debug*/
	volatile unsigned int umctl_resv16[60];	/* 0x030c ~ 0x03f8 */
	volatile unsigned int umctl_pstat;	/* 0x03fc */
	volatile unsigned int umctl_pccfg;	/* 0x0400 port common configruation*/
	volatile unsigned int umctl_pcfgr0;	/* 0x0404 port 0 configruation read */
	volatile unsigned int umctl_pcfgw0;	/* 0x0408 port 0 configruation write*/
	volatile unsigned int umctl_pcfgc0;	/* 0x040c port 0 common configruation*/
	volatile unsigned int umctl_pcfgidmaskch0_0;	/* 0x0410 channel 0 port 0 configruation*/
	volatile unsigned int umctl_pcfgidvaluech0_0;	/* 0x0414 channel 0 port 0 configruation*/
	volatile unsigned int umctl_resv17[30];	/* 0x0418 ~ 0x048c */
	volatile unsigned int umctl_pctrl0;	/* 0x0490 port control */
}DMC_UMCTL_REG_INFO_T,*DMC_UMCTL_REG_INFO_PTR_T;

typedef struct
{
	volatile unsigned int publ_ridr;	/* 0x0000 revision identification*/
	volatile unsigned int publ_pir;		/* 0x0004 phy initialization*/
	volatile unsigned int publ_pgcr[4];	/* 0x0008 ~ 0x0014 phy general configruation*/
	volatile unsigned int publ_pgsr[2];	/* 0x0018 ~ 0x001c phy general status*/
	volatile unsigned int publ_pllcr;	/* 0x0020 pll control*/
	volatile unsigned int publ_ptr[5];	/* 0x0024 ~ 0x0034 phy timing*/
	volatile unsigned int publ_acmdlr;	/* 0x0038 ac master delay line*/
	volatile unsigned int publ_aclcdlr;	/* 0x003c ac local calibrated delay line*/
	volatile unsigned int publ_acbdlr[10];	/* 0x0040 ~ 0x0064 ac bit delay line*/
	volatile unsigned int publ_aciocr[6];	/* 0x0068 ~ 0x007c ac i/o configruation*/
	volatile unsigned int publ_dxccr;	/* 0x0080 datx8 common configruation*/
	volatile unsigned int publ_dsgcr;	/* 0x0084 datx8 system general configruation*/
	volatile unsigned int publ_dcr;		/* 0x0088 dram configruation*/
	volatile unsigned int publ_dtpr[4];	/* 0x008c ~ 0x0098 dram timing parameters*/
	volatile unsigned int publ_mr[4];	/* 0x009c ~ 0x00a8 mode register*/
	volatile unsigned int publ_odtcr;	/* 0x00ac odt configruation*/
	volatile unsigned int publ_dtcr;	/* 0x00b0 data training configruation*/
	volatile unsigned int publ_dtar[4];	/* 0x00b4 ~ 0x00c0 data training address*/
	volatile unsigned int publ_dtdr[2];	/* 0x00c4 ~ 0x00c8 data training data*/
	volatile unsigned int publ_dtedr[2];	/* 0x00cc ~ 0x00d0 data training address */
	volatile unsigned int publ_rdimmgcr[2];	/* 0x00d4 ~ 0x00d8 rdimm general configruation*/
	volatile unsigned int publ_rdimmcr[2];	/* 0x00dc ~ 0x00e0 rdimm control*/
	volatile unsigned int publ_gpr[2];	/* 0x00e4 ~ 0x00e8 general purpose*/
	volatile unsigned int publ_catr[2];	/* 0x00ec ~ 0x00f0 catr*/
	volatile unsigned int publ_dqsdr;	/* 0x00f4 dqs drift detection */
	volatile unsigned int publ_dtmr[2];	/* 0x00f8 ~ 0x00fc data training mask*/
	volatile unsigned int publ_resv0[32];	/* 0x0100 ~ 0x017c */
	volatile unsigned int publ_dcuar;	/* 0x0180 DCU address*/
	volatile unsigned int publ_dcudr;	/* 0x0184 DCU data*/
	volatile unsigned int publ_dcurr;	/* 0x0188 DCU run*/
	volatile unsigned int publ_dculr;	/* 0x018c DCU loop*/
	volatile unsigned int publ_dcugcr;	/* 0x0190 DCU general configruation*/
	volatile unsigned int publ_dcutpr;	/* 0x0194 DCU timing parameters*/
	volatile unsigned int publ_dcusr[2];	/* 0x0198 ~ 0x019c DCU status*/
	volatile unsigned int publ_resv1[8];	/* 0x01a0 ~ 0x01bc */
	volatile unsigned int publ_bistrr;	/* 0x01c0 BIST run*/
	volatile unsigned int publ_bistwcr;	/* 0x01c4 BIST word count*/
	volatile unsigned int publ_bistmskr[3];	/* 0x01c8 ~ 0x01d0 BIST mask*/
	volatile unsigned int publ_bistlsr;	/* 0x01d4 BIST LFSR seed*/
	volatile unsigned int publ_bistar[3];	/* 0x01d8 ~ 0x01e0 BIST address*/
	volatile unsigned int publ_bistudpr;	/* 0x01e4 BIST User data pattern*/
	volatile unsigned int publ_bistgsr;	/* 0x01e8 BIST general status*/
	volatile unsigned int publ_bistwer;	/* 0x01ec BIST word error*/
	volatile unsigned int publ_bistber[4];	/* 0x01f0 ~ 0x01fc BIST bit error*/
	volatile unsigned int publ_bistwcsr;	/* 0x0200 BIST word count status*/
	volatile unsigned int publ_bistfwr[3];	/* 0x0204 ~ 0x020c BIST fail word*/
	volatile unsigned int publ_resv2[10];	/* 0x0210 ~ 0x0234 catr*/
	volatile unsigned int publ_iovcr[2];	/* 0x0238 ~ 0x023c IO VREF control*/
	volatile unsigned int publ_zqcr;	/* 0x0240 zq impedance control*/
	volatile unsigned int publ_zq0pr;	/* 0x0244 zq impedance program*/
	volatile unsigned int publ_zq0dr;	/* 0x0248 zq impedance data*/
	volatile unsigned int publ_zq0sr;	/* 0x024c zq impedance status*/
	volatile unsigned int publ_resv3;	/* 0x0250 */
	volatile unsigned int publ_zq1pr;	/* 0x0254 zq impedance program*/
	volatile unsigned int publ_zq1dr;	/* 0x0258 zq impedance data*/
	volatile unsigned int publ_zq1sr;	/* 0x025c zq impedance status*/
	volatile unsigned int publ_resv4;	/* 0x0260 */
	volatile unsigned int publ_zq2pr;	/* 0x0264 zq impedance program*/
	volatile unsigned int publ_zq2dr;	/* 0x0268 zq impedance data*/
	volatile unsigned int publ_zq2sr;	/* 0x026c zq impedance status*/
	volatile unsigned int publ_resv5;	/* 0x0270 */
	volatile unsigned int publ_zq3pr;	/* 0x0274 zq impedance program*/
	volatile unsigned int publ_zq3dr;	/* 0x0278 zq impedance data*/
	volatile unsigned int publ_zq3sr;	/* 0x027c zq impedance status*/
	volatile unsigned int publ_dx0gcr[4];	/* 0x0280 ~ 0x028c datx8 general config*/
	volatile unsigned int publ_dx0gsr[3];	/* 0x0290 ~ 0x0298 datx8 general status*/
	volatile unsigned int publ_dx0bdlr[7];	/* 0x029c ~ 0x02b4 datx8 bit delay line*/
	volatile unsigned int publ_dx0lcdlr[3];	/* 0x02b8 ~ 0x02c0 datx8 local cal*/
	volatile unsigned int publ_dx0mdlr;	/* 0x02c4 datx8 master delay line*/
	volatile unsigned int publ_dx0gtr;	/* 0x02c8 datx8 general timing*/
	volatile unsigned int publ_resv6[13];	/* 0x02cc ~ 0x02fc */
	volatile unsigned int publ_dx1gcr[4];	/* 0x0300 ~ 0x030c datx8 general config*/
	volatile unsigned int publ_dx1gsr[3];	/* 0x0310 ~ 0x0318 datx8 general status*/
	volatile unsigned int publ_dx1bdlr[7];	/* 0x031c ~ 0x0334 datx8 bit delay line*/
	volatile unsigned int publ_dx1lcdlr[3];	/* 0x0338 ~ 0x0340 datx8 local cal*/
	volatile unsigned int publ_dx1mdlr;	/* 0x0344 datx8 master delay line*/
	volatile unsigned int publ_dx1gtr;	/* 0x0348 datx8 general timing*/
	volatile unsigned int publ_resv7[13];	/* 0x034c ~ 0x037c */
	volatile unsigned int publ_dx2gcr[4];	/* 0x0380 ~ 0x038c datx8 general config*/
	volatile unsigned int publ_dx2gsr[3];	/* 0x0390 ~ 0x0398 datx8 general status*/
	volatile unsigned int publ_dx2bdlr[7];	/* 0x039c ~ 0x03b4 datx8 bit delay line*/
	volatile unsigned int publ_dx2lcdlr[3];	/* 0x03b8 ~ 0x03c0 datx8 local cal*/
	volatile unsigned int publ_dx2mdlr;	/* 0x03c4 datx8 master delay line*/
	volatile unsigned int publ_dx2gtr;	/* 0x03c8 datx8 general timing*/
	volatile unsigned int publ_resv8[13];	/* 0x03cc ~ 0x03fc */
	volatile unsigned int publ_dx3gcr[4];	/* 0x0400 ~ 0x040c datx8 general config*/
	volatile unsigned int publ_dx3gsr[3];	/* 0x0410 ~ 0x0418 datx8 general status*/
	volatile unsigned int publ_dx3bdlr[7];	/* 0x041c ~ 0x0434 datx8 bit delay line*/
	volatile unsigned int publ_dx3lcdlr[3];	/* 0x0438 ~ 0x0440 datx8 local cal*/
	volatile unsigned int publ_dx3mdlr;	/* 0x0444 datx8 master delay line*/
	volatile unsigned int publ_dx3gtr;	/* 0x0448 datx8 general timing*/
	volatile unsigned int publ_resv9[13];	/* 0x044c ~ 0x047c */
	volatile unsigned int publ_dx4gcr[4];	/* 0x0480 ~ 0x048c datx8 general config*/
	volatile unsigned int publ_dx4gsr[3];	/* 0x0490 ~ 0x0498 datx8 general status*/
	volatile unsigned int publ_dx4bdlr[7];	/* 0x049c ~ 0x04b4 datx8 bit delay line*/
	volatile unsigned int publ_dx4lcdlr[3];	/* 0x04b8 ~ 0x04c0 datx8 local cal*/
	volatile unsigned int publ_dx4mdlr;	/* 0x04c4 datx8 master delay line*/
	volatile unsigned int publ_dx4gtr;	/* 0x04c8 datx8 general timing*/
	volatile unsigned int publ_resv10[13];	/* 0x04cc ~ 0x04fc */
	volatile unsigned int publ_dx5gcr[4];	/* 0x0500 ~ 0x050c datx8 general config*/
	volatile unsigned int publ_dx5gsr[3];	/* 0x0510 ~ 0x0518 datx8 general status*/
	volatile unsigned int publ_dx5bdlr[7];	/* 0x051c ~ 0x0534 datx8 bit delay line*/
	volatile unsigned int publ_dx5lcdlr[3];	/* 0x0538 ~ 0x0540 datx8 local cal*/
	volatile unsigned int publ_dx5mdlr;	/* 0x0544 datx8 master delay line*/
	volatile unsigned int publ_dx5gtr;	/* 0x0548 datx8 general timing*/
	volatile unsigned int publ_resv11[13];	/* 0x054c ~ 0x057c */
	volatile unsigned int publ_dx6gcr[4];	/* 0x0580 ~ 0x058c datx8 general config*/
	volatile unsigned int publ_dx6gsr[3];	/* 0x0590 ~ 0x0598 datx8 general status*/
	volatile unsigned int publ_dx6bdlr[7];	/* 0x059c ~ 0x05b4 datx8 bit delay line*/
	volatile unsigned int publ_dx6lcdlr[3];	/* 0x05b8 ~ 0x05c0 datx8 local cal*/
	volatile unsigned int publ_dx6mdlr;	/* 0x05c4 datx8 master delay line*/
	volatile unsigned int publ_dx6gtr;	/* 0x05c8 datx8 general timing*/
	volatile unsigned int publ_resv12[13];	/* 0x05cc ~ 0x05fc */
	volatile unsigned int publ_dx7gcr[4];	/* 0x0600 ~ 0x060c datx8 general config*/
	volatile unsigned int publ_dx7gsr[3];	/* 0x0610 ~ 0x0618 datx8 general status*/
	volatile unsigned int publ_dx7bdlr[7];	/* 0x061c ~ 0x0634 datx8 bit delay line*/
	volatile unsigned int publ_dx7lcdlr[3];	/* 0x0638 ~ 0x0640 datx8 local cal*/
	volatile unsigned int publ_dx7mdlr;	/* 0x0644 datx8 master delay line*/
	volatile unsigned int publ_dx7gtr;	/* 0x0648 datx8 general timing*/
	volatile unsigned int publ_resv13[13];	/* 0x064c ~ 0x067c */
	volatile unsigned int publ_dx8gcr[4];	/* 0x0680 ~ 0x068c datx8 general config*/
	volatile unsigned int publ_dx8gsr[3];	/* 0x0690 ~ 0x0698 datx8 general status*/
	volatile unsigned int publ_dx8bdlr[7];	/* 0x069c ~ 0x06b4 datx8 bit delay line*/
	volatile unsigned int publ_dx8lcdlr[3];	/* 0x06b8 ~ 0x06c0 datx8 local cal*/
	volatile unsigned int publ_dx8mdlr;	/* 0x06c4 datx8 master delay line*/
	volatile unsigned int publ_dx8gtr;	/* 0x06c8 datx8 general timing*/
	volatile unsigned int publ_resv14[13];	/* 0x06cc ~ 0x06fc */
}DMC_PUBL_REG_INFO_T,*DMC_PUBL_REG_INFO_PTR_T;

DRAM_INFO_T* get_dram_cfg(DRAM_TYPE_E dram_type);
void __cal_actiming(DRAM_INFO_T *dram,unsigned int clk);
extern umctl2_port_info_t UMCTL2_PORT_CONFIG[];
extern umctl2_port_info_t UMCTL2_PORT_CONFIG_PIKEL[];

#endif

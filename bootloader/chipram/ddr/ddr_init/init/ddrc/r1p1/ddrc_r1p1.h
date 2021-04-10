#ifndef __DDRC_SPRD_R1P1_H__
#define __DDRC_SPRD_R1P1_H__

#include "debug.h"
#include <sci_types.h>

#ifndef BIT
#define BIT(x)				(1 << (x))
#endif

#ifndef MAX
#define MAX(x,y)			(((x) > (y)) ? (x) : (y))
#endif
#ifndef REG32
#define REG32(_x_) (*(volatile uint32*)((uint64)(_x_)))
#endif

#ifdef DDR_SCAN_ENABLE
#define DDR_LOG_LVL_DEBUG
#endif
#define DDR_LOG_LVL_INFO
#define DDR_LOG_LVL_ERR
#define DDR_LOG_LVL_SCAN

#define FREQ_SEL_MASK 0xFF


#define GUCPHY_VREF_CA_RANGE 0x33

#define BIST_RESERVE_SIZE		0x40000
/*0=64B,1=128B,2=256B,3=512B,4=1k,5=2k,6=4k,7=8k*/
#define INTERLEAVE_SIZE 1
//#define PXP_DEBUG
#define SYNC_MODE

#define FREQ_POINT_NUM_MAX 8
#define DDR_RANK_NUM_MAX 2

//#define SINGLE_FREQ_INIT
#define MIN_FREQ_SEL	0
#define MAX_FREQ_SEL	7


#define DMC_REG_ADDR_BASE_PHY (0x31000000)
//#define PUB_AHB_ADDR_BASE_PHY (0x31030000)
#define PUB_AHB_ADDR_BASE_BIST 0x31070000
#define DMC_GUCPHY0_BASE		(0x31001000)
#define PMU_APB_BASE_ADDR		(0x32280000)
#define PUB_APB_BASE			(0x31050000)
#define PUB_AHB_BASE			(0x31030000)


#define REG_PUB_BIST_CTRL1				(PUB_APB_BASE + 0x004c)
#define REG_PUB_DDR_CHN_SLEEP_CTRL0	(PUB_APB_BASE + 0x3104)
#define REG_DMC_VOTE_CTRL				(PUB_APB_BASE + 0x31E0)
#define REG_DMC_RST_CTL				(PUB_APB_BASE + 0x3404)
#define REG_DMC_CLK_INIT_SW_CTRL		(PUB_APB_BASE + 0x4000)
#define REG_DMC_CLK_INIT_SW_START		(PUB_APB_BASE + 0x4004)
#define REG_DMC_CLK_STATE				(PUB_APB_BASE + 0x4008)
#define REG_DMC_CLK_INIT_CFG			(PUB_APB_BASE + 0x400C)
#define REG_PUB_DFS_PURE_SW_CTRL		(PUB_APB_BASE + 0x4100)
#define REG_PUB_DFS_SW_CTEL			(PUB_APB_BASE + 0x4104)
#define REG_PUB_DFS_SW_CTRL1			(PUB_APB_BASE + 0x4108)
#define REG_PUB_DFS_HW_CTRL			(PUB_APB_BASE + 0x4114)
#define REG_PMU_APB_CP_SOFT_RST		(PMU_APB_BASE_ADDR + 0x00b0)
#define REG_PMU_APB_DDR_PHY_RET_CFG	(PMU_APB_BASE_ADDR + 0x0130)
#define REG_PMU_APB_PUB_ACC_RDY		(PMU_APB_BASE_ADDR + 0x250)

#define DMC_GUCPHY1_BASE		(DMC_GUCPHY0_BASE+0x1000)
#define DDR_DRV_CFG 40

#define CHIP_RESET_CONTROL_BASE_ADDR		(0x32290000)
#define CHIP_RESET_CONTROL_KEY			(CHIP_RESET_CONTROL_BASE_ADDR + 0x0)
#define CHIP_RESET_CONTROL_ENABLE			(CHIP_RESET_CONTROL_BASE_ADDR + 0x04)
#define CHIP_RESET_CONTROL_STATUS			(CHIP_RESET_CONTROL_BASE_ADDR + 0x08)

#define DMC_MAP								(DMC_REG_ADDR_BASE_PHY + 0x130)
#define RF_PORT_PREFETCH_EN				(DMC_REG_ADDR_BASE_PHY + 0x10)
#define RF_HI_URGENT_EN					(DMC_REG_ADDR_BASE_PHY + 0x14)

typedef struct __DDRC_R1P1_REG_INFO {
	volatile unsigned int dmc_cfg0;						/*addr:0x0*/
	volatile unsigned int dmc_cfg1;						/*addr:0x4*/
	volatile unsigned int dmc_cfg2;						/*addr:0x8*/
	volatile unsigned int dmc_cfg3;						/*addr:0xc*/
	volatile unsigned int dmc_cfg4;						/*addr:0x10*/
	volatile unsigned int dmc_cfg5;						/*addr:0x14*/
	volatile unsigned int dmc_cfg6;						/*addr:0x18*/
	volatile unsigned int dmc_cfg7;						/*addr:0x1c*/

	volatile unsigned int dmc_cfg0_ach0;				/*addr:0x20*/
	volatile unsigned int dmc_cfg1_ach0;				/*addr:0x24*/
	volatile unsigned int dmc_cfg0_ach1;				/*addr:0x28*/
	volatile unsigned int dmc_cfg1_ach1;				/*addr:0x2c*/
	volatile unsigned int dmc_cfg0_ach2;				/*addr:0x30*/
	volatile unsigned int dmc_cfg1_ach2;				/*addr:0x34*/
	volatile unsigned int dmc_cfg0_ach3;				/*addr:0x38*/
	volatile unsigned int dmc_cfg1_ach3;				/*addr:0x3c*/
	volatile unsigned int dmc_cfg0_ach4;				/*addr:0x40*/
	volatile unsigned int dmc_cfg1_ach4;				/*addr:0x44*/
	volatile unsigned int dmc_cfg0_ach5;				/*addr:0x48*/
	volatile unsigned int dmc_cfg1_ach5;				/*addr:0x4c*/
	volatile unsigned int dmc_cfg0_ach6;				/*addr:0x50*/
	volatile unsigned int dmc_cfg1_ach6;				/*addr:0x54*/
	volatile unsigned int dmc_cfg0_ach7;				/*addr:0x58*/
	volatile unsigned int dmc_cfg1_ach7;				/*addr:0x5c*/

	volatile unsigned int pad1[15];						/*addr:0x60~0x98*/
	volatile unsigned int dmc_lock_cfg;					/*addr:0x9c*/
	volatile unsigned int dmc_sts0;						/*addr:0xa0*/
	volatile unsigned int dmc_sts1;						/*addr:0xa4*/
	volatile unsigned int dmc_sts2;						/*addr:0xa8*/
	volatile unsigned int dmc_sts3;						/*addr:0xac*/
	volatile unsigned int dmc_sts4;						/*addr:0xb0*/
	volatile unsigned int dmc_sts5;						/*addr:0xb4*/
	volatile unsigned int dmc_sts6;						/*addr:0xb8*/
	volatile unsigned int dmc_sts7;						/*addr:0xbc*/

	volatile unsigned int dmc_axi_chx_sts[8];				/*addr:0xc0~0xdc*/
	volatile unsigned int pad2[8];						/*addr:0xe0~0xfc*/

	volatile unsigned int dmc_dcfg0;					/*addr:0x100*/
	volatile unsigned int dmc_dcfg1;					/*addr:0x104*/
	volatile unsigned int dmc_dcfg2;					/*addr:0x108*/
	volatile unsigned int dmc_dcfg3;					/*addr:0x10c*/
	volatile unsigned int dmc_dcfg4;					/*addr:0x110*/
	volatile unsigned int dmc_dcfg5;					/*addr:0x114*/
	volatile unsigned int dmc_dcfg6;					/*addr:0x118*/
	volatile unsigned int dmc_dcfg7;					/*addr:0x11c*/
	volatile unsigned int dmc_dcfg8;					/*addr:0x120*/
	volatile unsigned int dmc_dcfg9;					/*addr:0x124*/
	volatile unsigned int dmc_dcfg10;				/*addr:0x128*/
	volatile unsigned int dmc_dcfg11;				/*addr:0x12c*/
	volatile unsigned int dmc_dcfg12;				/*addr:0x130*/
	volatile unsigned int dmc_dcfg13;				/*addr:0x134*/
	volatile unsigned int dmc_dcfg14;				/*addr:0x138*/
	volatile unsigned int dmc_dcfg15;				/*addr:0x13c*/
	volatile unsigned int dmc_dcfg16;				/*addr:0x140*/
	volatile unsigned int dmc_dcfg17;				/*addr:0x144*/
	volatile unsigned int dmc_dcfg18;				/*addr:0x148*/
	volatile unsigned int dmc_dcfg19;				/*addr:0x14c*/
	volatile unsigned int dmc_dcfg20;				/*addr:0x150*/

	volatile unsigned int pad3[11];						/*addr:0x154~0x17c*/
	volatile unsigned int dmc_dtmg_f[8][20+4]; /*addr:0x180~0x1cc*/
}DDRC_R1P1_REG_INFO, *DDRC_R1P1_REG_INFO_PTR;

typedef struct port_para {
	u8 timeout_pri_wr_chx; //write channel priority
	u8 timeout_thr_wr_chx; //channel write timeout
	u8 timeout_thr_rd_chx; //channel read timeout
	u8 timeout_pri_rd_chx; //read channel priority
	u8 bw_thr_chx;		   //threshold value
	u8 bw_holdoff_en_chx;  //enable bandwidth holdoff
}PORT_PARA;

typedef enum PLL_SOURCE{
	DPLL0=0,
	DPLL1,
	TWPLL
}DMC_PLL_SOURCE;


typedef enum CLK_TYPE{
	PUB_CLK_156M=156,
	PUB_CLK_160M=160,
	PUB_CLK_233M=233,
	PUB_CLK_256M=256,
	PUB_CLK_311M=311,
	PUB_CLK_384M=384,
	PUB_CLK_400M=400,
	PUB_CLK_512M=512,
	PUB_CLK_533M=533,
	PUB_CLK_622M=622,
	PUB_CLK_667M=667,
	PUB_CLK_768M=768,
	PUB_CLK_800M=800,
	PUB_CLK_933M=933,
	PUB_CLK_1024M=1024,
	PUB_CLK_1066M=1066,
	PUB_CLK_1333M=1333,
	PUB_CLK_1400M=1400,
	PUB_CLK_1500M=1500,
	PUB_CLK_1536M=1536,
	PUB_CLK_1600M=1600,
	PUB_CLK_1866M=1866
}DMC_CLK_TYPE;

typedef enum DESKEWPLL_STATUS
{
	DESKEW_BYAPSS=0,
	DESKEW_ON,
	DESKEW_OFF
}DMC_DESKEWPLL_STATUS;

typedef struct CLK_DFS_CFG{
	uint32 pll_sel;
	uint32 pll_div_sel;
	uint32 deskew_mode;
	uint32 x1_sel;
	uint32 d2_sel;
	uint32 mdll_sel;
	uint32 half_freq_mode;
}DMC_CLK_CFG;

typedef struct PUB_CLK_CFG{
	uint32 freq_num;
	DMC_CLK_TYPE ddr_clk;
	DMC_PLL_SOURCE pll_source;
	DMC_CLK_CFG  clk_cfg;
}DMC_PUB_CLK_CFG;

typedef struct dmc_local_timing_cfg {
	unsigned int clk;
	unsigned int dtmg[24];
}DDRC_R1P1_TIMING_CFG;

typedef struct dfs_freq_tab
{
	uint32 point_num;	//0:F0/1:F1/2:F2/3:F3
	uint32 freq;		//MHz
}dfs_freq_table;

typedef struct {
	u8 mr1;
	u8 mr2;
	u8 mr3;
	u8 mr11;
	u8 mr12;
	u8 mr14;
	u8 mr22;
}LPDDR4_ODT_CFG;

typedef struct __LPDDR4_MR_INFO {
	uint32 bl;			/*burst length*/
	uint32 bt;			/*burst type*/
	uint32 wc;			/*wrap*/
	uint32 nwr;		/*nwr*/
	uint32 rl;			/*read latency*/
	uint32 wl;			/*write latency*/
	uint32 ds;			/*driver strength*/
	uint32 dbi;
	LPDDR4_ODT_CFG *p_odt_cfg;
}LPDDR4_MR_INFO;

typedef enum __dmc_cmd_chn_index {
	CMD_CHN_0 = 1,
	CMD_CHN_1 = 2,
	CMD_CHN_BOTH = 3
}DMC_CMD_CHN_INDEX;

typedef enum __dmc_cmd_cs_index {
	CMD_CS_0,
	CMD_CS_1,
	CMD_CS_BOTH
}DMC_CMD_CS_INDEX;

typedef enum __DRAM_TYPE {
	LPDDR1=0x100,
	LPDDR2,
	LPDDR3,
	LPDDR4,
	LPDDR4X,
	LPDDR4Y,
}DRAM_TYPE;


typedef enum __DDR_PINMUX {
	LP4_PIN_MUX_CASE0 = 0,
	LP4_PIN_MUX_CASE1 = 1
}DDR_PINMUX_CASE;

typedef struct __DRAM_JEDEC_INFO {
	uint32 cs_index;
	uint32 bank;
	uint32 row;
	uint32 column;
	uint32 dw;
	uint64 cs_size;
}DRAM_JEDEC_INFO;

typedef struct __DRAM_CHIP_INFO {
	DRAM_TYPE chip_type;
	uint32 cs_num;
	DRAM_JEDEC_INFO *cs0_jedec_info;
	DRAM_JEDEC_INFO *cs1_jedec_info;
	DDR_PINMUX_CASE pinmux_case;
}DRAM_CHIP_INFO;

#define V_LOW 0x0
#define V_HIGH	0x1


#define LP4_PINMUX_CASE0  0
#define LP4_PINMUX_CASE1  1

#define    DRAM_LPDDR1 0x100
#define    DRAM_LPDDR2 0x101
#define    DRAM_LPDDR3 0x102
#define    DRAM_LPDDR4 0x103
#define    DRAM_LPDDR4X 0x104
#define    DRAM_LPDDR4Y 0x105


#if (CFG_DRAM_TYPE == DRAM_LPDDR4)
#define CFG_CS0_BANK_NUM	8
#define CFG_CS0_ROW_NUM		15
#define CFG_CS0_COLUMN_NUM	10
#define CFG_CS0_DQ_DW		16
#define CFG_CS0_AP_PIN_POS	10
#define CFG_CS0_SIZE	0x40000000

#define CFG_CS1_BANK_NUM	8
#define CFG_CS1_ROW_NUM		15
#define CFG_CS1_COLUMN_NUM	10
#define CFG_CS1_DQ_DW		16
#define CFG_CS1_AP_PIN_POS	10
#define CFG_CS1_SIZE	0x40000000
#elif(CFG_DRAM_TYPE == DRAM_LPDDR4X)
#ifdef CONFIG_UFS_BOOT
#define CFG_CS0_BANK_NUM	8
#define CFG_CS0_ROW_NUM		16
#define CFG_CS0_COLUMN_NUM	10
#define CFG_CS0_DQ_DW		16
#define CFG_CS0_AP_PIN_POS	10
#define CFG_CS0_SIZE	0x80000000 //2GB( X16 )

#define CFG_CS1_BANK_NUM	8
#define CFG_CS1_ROW_NUM		17
#define CFG_CS1_COLUMN_NUM	10
#define CFG_CS1_DQ_DW		8
#define CFG_CS1_AP_PIN_POS	10
#define CFG_CS1_SIZE	0x100000000 //4GB( x8 )
#else

#define CFG_CS0_BANK_NUM	8
#define CFG_CS0_ROW_NUM		16
#define CFG_CS0_COLUMN_NUM	10
#define CFG_CS0_DQ_DW		16
#define CFG_CS0_AP_PIN_POS	10
#define CFG_CS0_SIZE	0x80000000

#define CFG_CS1_BANK_NUM	8
#define CFG_CS1_ROW_NUM		16
#define CFG_CS1_COLUMN_NUM	10
#define CFG_CS1_DQ_DW		16
#define CFG_CS1_AP_PIN_POS	10
#define CFG_CS1_SIZE	0x80000000

#endif
#endif
struct interleave_cfg
{
	uint32 liner_base_ch0;
	uint32 liner_base_ch1;
	uint32 liner_base_ch2;
	uint32 liner_base_ch3;
	uint32 interleave_base;
	uint32 interleave_offset;
};

/*******************************/
/***vaule: 0:off			 ***/
/***	   1:240ohm			 ***/
/***	   2:120ohm			 ***/
/***	   3:80ohm			 ***/
/***	   4:60ohm			 ***/
/***	   5:48ohm			 ***/
/***	   6:40ohm			 ***/
/***	   7:34ohm			 ***/
/*******************************/
#define PHY_DS_OFF 0
#define PHY_DS_240 1
#define PHY_DS_120 2
#define PHY_DS_80  3
#define PHY_DS_60  4
#define PHY_DS_48  5
#define PHY_DS_40  6
#define PHY_DS_34  7

/*******************************/
/***vaule: 0:off			 ***/
/***	   1:240ohm			 ***/
/***	   2:120ohm			 ***/
/***	   3:80ohm			 ***/
/***	   4:60ohm			 ***/
/***	   5:48ohm			 ***/
/***	   6:40ohm			 ***/
/***	   7:RFU			 ***/
/*******************************/
#define PHY_DS_OFF 0
#define PHY_DS_240 1
#define PHY_DS_120 2
#define PHY_DS_80  3
#define PHY_DS_60  4
#define PHY_DS_48  5
#define PHY_DS_40  6
#define PHY_DS_34  7

/*default burst length*/
#define DEFAULT_LPDDR2_BL	4
#define DEFAULT_LPDDR3_BL	8
#define DEFAULT_LPDDR4_BL	16

#define MRR_BYTE_SWITCH_INDEX 0

#define RF_LINER_BASE_CH0_16G	0
#define RF_LINER_BASE_CH1_16G	  0
#define RF_LINER_BASE_CH2_16G	  0
#define RF_LINER_BASE_CH3_16G	  0
#define RF_INTERLEAVE_BASE_16G	  0
#define RF_INTERLEAVE_OFFSET_16G  0
#define RF_LINER_BASE_CH0_8G	  0
#define RF_LINER_BASE_CH1_8G	  0
#define RF_LINER_BASE_CH2_8G	  0
#define RF_LINER_BASE_CH3_8G	  0
#define RF_INTERLEAVE_BASE_8G	  0
#define RF_INTERLEAVE_OFFSET_8G   0
#define RF_LINER_BASE_CH0_4G	  0
#define RF_LINER_BASE_CH1_4G	  0
#define RF_LINER_BASE_CH2_4G	  0
#define RF_LINER_BASE_CH3_4G	  0
#define RF_INTERLEAVE_BASE_4G	  0
#define RF_INTERLEAVE_OFFSET_4G   0
#define RF_LINER_BASE_CH0_2G	  0
#define RF_LINER_BASE_CH1_2G	  0
#define RF_LINER_BASE_CH2_2G	  0
#define RF_LINER_BASE_CH3_2G	  0
#define RF_INTERLEAVE_BASE_2G	  0
#define RF_INTERLEAVE_OFFSET_2G   0
#define RF_LINER_BASE_CH0_1G	  0
#define RF_LINER_BASE_CH1_1G	  0
#define RF_LINER_BASE_CH2_1G	  0
#define RF_LINER_BASE_CH3_1G	  0
#define RF_INTERLEAVE_BASE_1G	  0
#define RF_INTERLEAVE_OFFSET_1G   0
#define RF_LINER_BASE_CH0_512M	  0
#define RF_LINER_BASE_CH1_512M	  0
#define RF_LINER_BASE_CH2_512M	  0
#define RF_LINER_BASE_CH3_512M	  0
#define RF_INTERLEAVE_BASE_512M   0
#define RF_INTERLEAVE_OFFSET_512M 0

void reset_dmc_fifo(void);
uint32 find_freq_num(uint32 clk_freq);
uint32 find_ddr_freq(uint32 num);
int ctrl_pre_set_seq(dfs_freq_table dfs_frequency[8]);
void axi_ch_cfg_seq(void);
void ctrl_post_set_seq(void);
void ddrc_phy_pre_set_seq(void);
void ddrc_phy_post_set_seq(void);
void dram_powerup_seq(uint32 clock);
void ddrc_phy_init_post_seq(void);
void ddrc_phy_init_seq(uint32 ddr_clk);

#endif


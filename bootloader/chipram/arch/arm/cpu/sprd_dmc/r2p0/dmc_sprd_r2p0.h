#ifndef __DMC_SPRD_R2P0_H__
#define __DMC_SPRD_R2P0_H__

#ifndef BIT
#define BIT(x)				(1 << (x))
#endif

#ifndef MAX
#define MAX(x,y)			(((x) > (y)) ? (x) : (y))
#endif

#ifndef REG32
#define REG32(x)   (*((volatile u32 *)(x)))
#endif

//#define DFS_EN

#define INIT_DDR_CLK 640

#define PUB_DMC_BASE			0x30000000
#define AON_APB_CTL_BASE		0x402E0000
#define ARM7_CLK_EMC_CTL		0x50820010
#define PMU_APB_SOFT_RESET      0x402b00b0
#define PMU_DDR_SLEEP_CTL		0x402b00d0
#define PMU_APB_UMC_RESET       0x402b0130
#define DMC_REG_ADDR_BASE_PHY		(PUB_DMC_BASE)
#define ADDR_CS_ROW_BANK_COLUMN
/*pub drv support:5(240ohm),10(120ohm),15(80ohm),20(60ohm),25(48ohm),30(40ohm)*/
#define DDR_DRV_CFG 30
/*mem drv support:34ohm,40ohm,48ohm,60ohm,80ohm*/
#define DDR_DRV_MEM_CFG 40
#define DDR_DLL_CFG 8
#define ARM7_SOFT_RESET  (BIT(8))

//#define REG_AON_APB_DPLL_CFG0	(AON_APB_CTL_BASE + 0x004c)
//#define REG_AON_APB_DPLL_CFG1	(AON_APB_CTL_BASE + 0x0050)
#define REG_AON_APB_EMC_CFG     (AON_APB_CTL_BASE + 0x0080)
#define REG_AON_APB_RST1	(AON_APB_CTL_BASE + 0x000C)
#define REG_AON_CLK_SF_DFS_CTL	(AON_APB_CTL_BASE + 0x00a0)


#define DMC_ZQ_CAL		(PUB_DMC_BASE + 0x8)
#define DMC_IO_ADDR_CTRL_AC	(PUB_DMC_BASE + 0x390)
#define DMC_IO_CLK_CTRL_AC	(PUB_DMC_BASE + 0x394)
#define DMC_IO_DQ_CTRL_DS	(PUB_DMC_BASE + 0x490)
#define DMC_IO_DQS_CTRL_DS	(PUB_DMC_BASE + 0x494)
#define DMC_ZQ_CALOVER		(BIT(17))
#define DLL_LOCK_BITMASK	(BIT(28))


#define MAX_CHANNEL_NUM 8

#define DDR_START_ADDR_PHY		0x80000000
#define PORT_BASE_ADDR			0x300e3000
#define DMC_AWQOS_8			(PORT_BASE_ADDR + 0x011C)
#define BIST_RESERVE_SIZE		0x40000
#define SYS_MAP_RESERVE_SIZE		0x200000
#define DLL_LOCK_TIME_COUNT		0x1000000

#define CHIP_VERSION
//#define PXP_VERSION
//#define ZEBU_VERSION
//#define FPGA_VERSION
//#define EDA_TEST

typedef struct port_para {
	u8	timeout_pri_wr_ch; //write channel priority
	u8	timeout_thr_wr_ch; //channel write timeout
	u8	timeout_thr_rd_ch; //channel read timeout
}PORT_PARA;

typedef struct __DMC_R2P0_REG_INFO {
	volatile unsigned int dmc_cfg0;				/*addr:0x0*/
	volatile unsigned int dmc_cfg1;				/*addr:0x4*/
	volatile unsigned int dmc_cfg2;				/*addr:0x8*/
	volatile unsigned int dmc_cfg3;				/*addr:0xc*/
	volatile unsigned int pad0[2];

	volatile unsigned int pad1[1];
	volatile unsigned int dmc_rcv_data;			/*addr:0x1c*/
	volatile unsigned int ahbaxireg[32];			/*addr:0x20*/
	volatile unsigned int dmc_sts0;				/*addr:0xa0*/
	volatile unsigned int dmc_sts1;				/*addr:0xa4*/
	volatile unsigned int dmc_sts2;				/*addr:0xa8*/
	volatile unsigned int dmc_sts3;				/*addr:0xac*/

	volatile unsigned int pad2[4];

	volatile unsigned int dmc_axi_chn_sts[16];		/*addr:0xc0*/

	volatile unsigned int dmc_dcfg0;			/*addr:0x100*/
	volatile unsigned int dmc_dcfg1;			/*addr:0x104*/
	volatile unsigned int dmc_dcfg2;			/*addr:0x108*/
	volatile unsigned int dmc_dcfg3;			/*addr:0x10c*/
	volatile unsigned int dmc_dcfg4;			/*addr:0x110*/
	volatile unsigned int dmc_dcfg5;			/*addr:0x114*/
	volatile unsigned int dmc_dcfg6;			/*addr:0x118*/
	volatile unsigned int dmc_dcfg7;			/*addr:0x11c*/
	volatile unsigned int dmc_dcfg8;			/*addr:0x120*/
	volatile unsigned int dmc_dcfg9;			/*addr:0x124*/
	volatile unsigned int dmc_dcfg10;			/*addr:0x128*/
	volatile unsigned int dmc_dcfg11;			/*addr:0x12c*/
	volatile unsigned int dmc_dcfg12;			/*addr:0x130*/

	volatile unsigned int pad3[19];
	volatile unsigned int dmc_bist[21];			/*addr:0x180*/
	volatile unsigned int pad4[11];
	volatile unsigned int dmc_dtmg_f[4][13+3];		/*addr:0x200*/

	volatile unsigned int dmc_cfg_dll_ac;			/*addr:0x300*/
	volatile unsigned int dmc_sts_dll_ac;			/*addr:0x304*/
	volatile unsigned int dmc_clkwr_dll_ac;			/*addr:0x308*/
	volatile unsigned int dmc_addr_out0_dll_ac;		/*addr:0x30c*/
	volatile unsigned int dmc_addr_out1_dll_ac;		/*addr:0x310*/
	volatile unsigned int dmc_addr_out2_dll_ac;		/*addr:0x314*/
	volatile unsigned int dmc_cmd_out_dll_ac;		/*addr:0x318*/

	volatile unsigned int pad5[25];
	volatile unsigned int dmc_iomux_sel_ac;			/*addr:0x380*/
	volatile unsigned int dmc_iomux_out_ac;			/*addr:0x384*/
	volatile unsigned int dmc_iomux_oe_ac;			/*addr:0x388*/
	volatile unsigned int dmc_iomux_ie_ac;			/*addr:0x38c*/
	volatile unsigned int dmc_io_addr_ctrl_ac;		/*addr:0x390*/
	volatile unsigned int dmc_io_clk_ctrl_ac;		/*addr:0x394*/

	volatile unsigned int pad6[26];
	volatile unsigned int dmc_cfg_dll_ds0;			/*addr:0x400*/
	volatile unsigned int dmc_sts_dll_ds0;			/*addr:0x404*/
	volatile unsigned int dmc_clkwr_dll_ds0;		/*addr:0x408*/
	volatile unsigned int dmc_dqsin_pos_dll_ds0;		/*addr:0x40c*/
	volatile unsigned int dmc_dqsin_neg_dll_ds0;		/*addr:0x410*/
	volatile unsigned int dmc_dqsgate_dll_ds0;		/*addr:0x414*/
	volatile unsigned int dmc_dq_out0_dl_ds0;		/*addr:0x418*/
	volatile unsigned int dmc_dq_out1_dl_ds0;		/*addr:0x41c*/
	volatile unsigned int dmc_dq_in0_dl_ds0;		/*addr:0x420*/
	volatile unsigned int dmc_dq_in1_dl_ds0;		/*addr:0x424*/
	volatile unsigned int dmc_dmdqs_inout_dl_ds0;		/*addr:0x428*/
	volatile unsigned int pad7[21];
	volatile unsigned int dmc_iomux_sel_ds0;		/*addr:0x480*/
	volatile unsigned int dmc_iomux_out_ds0;		/*addr:0x484*/
	volatile unsigned int dmc_iomux_oe_ds0;			/*addr:0x488*/
	volatile unsigned int dmc_iomux_ie_ds0;			/*addr:0x48c*/

	volatile unsigned int dmc_io_dq_ctrl_ds;		/*addr:0x490*/

	volatile unsigned int dmc_io_dqs_ctrl_ds;		/*addr:0x494*/

	volatile unsigned int pad8[26];
	volatile unsigned int dmc_cfg_dll_ds1;			/*addr:0x500*/
	volatile unsigned int dmc_sts_dll_ds1;			/*addr:0x504*/
	volatile unsigned int dmc_clkwr_dll_ds1;		/*addr:0x508*/
	volatile unsigned int dmc_dqsin_pos_dll_ds1;		/*addr:0x50c*/
	volatile unsigned int dmc_dqsin_neg_dll_ds1;		/*addr:0x510*/
	volatile unsigned int dmc_dqsgate_dll_ds1;		/*addr:0x514*/
	volatile unsigned int dmc_dq_out0_dl_ds1;		/*addr:0x518*/
	volatile unsigned int dmc_dq_out1_dl_ds1;		/*addr:0x51c*/
	volatile unsigned int dmc_dq_in0_dl_ds1;		/*addr:0x520*/
	volatile unsigned int dmc_dq_in1_dl_ds1;		/*addr:0x524*/
	volatile unsigned int dmc_dmdqs_inout_dl_ds1;		/*addr:0x528*/
	volatile unsigned int pad9[21];
	volatile unsigned int dmc_iomux_sel_ds1;		/*addr:0x580*/
	volatile unsigned int dmc_iomux_out_ds1;		/*addr:0x584*/
	volatile unsigned int dmc_iomux_oe_ds1;			/*addr:0x588*/
	volatile unsigned int dmc_iomux_ie_ds1;			/*addr:0x58c*/

	volatile unsigned int pad10[28];
	volatile unsigned int dmc_cfg_dll_ds2;			/*addr:0x600*/
	volatile unsigned int dmc_sts_dll_ds2;			/*addr:0x604*/
	volatile unsigned int dmc_clkwr_dll_ds2;		/*addr:0x608*/
	volatile unsigned int dmc_dqsin_pos_dll_ds2;		/*addr:0x60c*/
	volatile unsigned int dmc_dqsin_neg_dll_ds2;		/*addr:0x610*/
	volatile unsigned int dmc_dqsgate_dll_ds2;		/*addr:0x614*/
	volatile unsigned int dmc_dq_out0_dl_ds2;		/*addr:0x618*/
	volatile unsigned int dmc_dq_out1_dl_ds2;		/*addr:0x61c*/
	volatile unsigned int dmc_dq_in0_dl_ds2;		/*addr:0x620*/
	volatile unsigned int dmc_dq_in1_dl_ds2;		/*addr:0x624*/
	volatile unsigned int dmc_dmdqs_inout_dl_ds2;		/*addr:0x628*/
	volatile unsigned int pad11[21];
	volatile unsigned int dmc_iomux_sel_ds2;		/*addr:0x680*/
	volatile unsigned int dmc_iomux_out_ds2;		/*addr:0x684*/
	volatile unsigned int dmc_iomux_oe_ds2;			/*addr:0x688*/
	volatile unsigned int dmc_iomux_ie_ds2;			/*addr:0x68c*/

	volatile unsigned int pad12[28];
	volatile unsigned int dmc_cfg_dll_ds3;			/*addr:0x700*/
	volatile unsigned int dmc_sts_dll_ds3;			/*addr:0x704*/
	volatile unsigned int dmc_clkwr_dll_ds3;		/*addr:0x708*/
	volatile unsigned int dmc_dqsin_pos_dll_ds3;		/*addr:0x70c*/
	volatile unsigned int dmc_dqsin_neg_dll_ds3;		/*addr:0x710*/
	volatile unsigned int dmc_dqsgate_dll_ds3;		/*addr:0x714*/
	volatile unsigned int dmc_dq_out0_dl_ds3;		/*addr:0x718*/
	volatile unsigned int dmc_dq_out1_dl_ds3;		/*addr:0x71c*/
	volatile unsigned int dmc_dq_in0_dl_ds3;		/*addr:0x720*/
	volatile unsigned int dmc_dq_in1_dl_ds3;		/*addr:0x724*/
	volatile unsigned int dmc_dmdqs_inout_dl_ds3;		/*addr:0x728*/
	volatile unsigned int pad13[21];
	volatile unsigned int dmc_iomux_sel_ds3;		/*addr:0x780*/
	volatile unsigned int dmc_iomux_out_ds3;		/*addr:0x784*/
	volatile unsigned int dmc_iomux_oe_ds3;			/*addr:0x788*/
	volatile unsigned int dmc_iomux_ie_ds3;			/*addr:0x78c*/
}DMC_R2P0_REG_INFO, *DMC_R2P0_REG_INFO_PTR;

typedef struct __sdram_cs_pin_table {
	int pin_index;
	u32 cs_size;
}SDRAM_CS_PIN_TABLE;


typedef enum __dmc_cmd_cs_index {
	CMD_CS_0,
	CMD_CS_1,
	CMD_CS_BOTH
}DMC_CMD_CS_INDEX;


typedef struct dmc_local_timing_cfg {
	unsigned int clk;
	unsigned int dtmg[13];
}DMC_LOCAL_TIMING_CFG;


typedef struct dmc_delay_line_cfg {
	unsigned int dmc_cfg_dll_ac;	//0x300
	unsigned int dmc_cfg_dll_ds0;	//0x400
	unsigned int dmc_cfg_dll_ds1;	//0x500
	unsigned int dmc_cfg_dll_ds2;	//0x600
	unsigned int dmc_cfg_dll_ds3;	//0x700

	unsigned int dmc_clkwr_dll_ac;      //0x308

	unsigned int dmc_clkwr_dll_ds0;   //x0408
	unsigned int dmc_clkwr_dll_ds1;   //x0508
	unsigned int dmc_clkwr_dll_ds2;   //x0608
	unsigned int dmc_clkwr_dll_ds3;   //x0708

	unsigned int dmc_dqsin_pos_dll_ds0;	//0x40c
	unsigned int dmc_dqsin_pos_dll_ds1;	//0x50c
	unsigned int dmc_dqsin_pos_dll_ds2;	//0x60c
	unsigned int dmc_dqsin_pos_dll_ds3;	//0x70c

	unsigned int dmc_dqsin_neg_dll_ds0;	//0x410
	unsigned int dmc_dqsin_neg_dll_ds1;	//0x510
	unsigned int dmc_dqsin_neg_dll_ds2;	//0x610
	unsigned int dmc_dqsin_neg_dll_ds3;	//0x710

	unsigned int dmc_dqsgate_dll_ds0;		//0x414
	unsigned int dmc_dqsgate_dll_ds1;		//0x514
	unsigned int dmc_dqsgate_dll_ds2;		//0x614
	unsigned int dmc_dqsgate_dll_ds3;		//0x714
}DMC_DELAY_LINE_CFG;


typedef enum __LPDDR2_MANUFACTURE_ID
{
	LPDDR2_SAMSUNG = 0X1,
	LPDDR2_QIMONDA = 0X2,
	LPDDR2_ELPIDA = 0X3,
	LPDDR2_ETRON = 0X4,
	LPDDR2_NANYA = 0X5,
	LPDDR2_HYNIX = 0X6,
	LPDDR2_MOSEL = 0X7,
	LPDDR2_WINBOND = 0X8,
	LPDDR2_ESMT = 0X9,
	LPDDR2_SPANSION = 0XB,
	LPDDR2_SST = 0XC,
	LPDDR2_ZMOS = 0XD,
	LPDDR2_INTEL = 0XE,
	LPDDR2_NUMONYX = 0XFE,
	LPDDR2_MICRON = 0XFF,
}LPDDR2_MANUFACTURE_ID;

typedef enum __LPDDR3_MANUFACTURE_ID
{
	LPDDR3_SAMSUNG = 0X1,
	LPDDR3_QIMONDA = 0X2,
	LPDDR3_ELPIDA = 0X3,
	LPDDR3_ETRON = 0X4,
	LPDDR3_NANYA = 0X5,
	LPDDR3_HYNIX = 0X6,
	LPDDR3_MOSEL = 0X7,
	LPDDR3_WINBOND = 0X8,
	LPDDR3_ESMT = 0X9,
	LPDDR3_SPANSION = 0XB,
	LPDDR3_SST = 0XC,
	LPDDR3_ZMOS = 0XD,
	LPDDR3_INTEL = 0XE,
	LPDDR3_NUMONYX = 0XFE,
	LPDDR3_MICRON = 0XFF,
}LPDDR3_MANUFACTURE_ID;

typedef enum __DRAM_MANUFACTURE_ID
{
	DRAM_SAMSUNG = 0X1,
	DRAM_QIMONDA = 0X2,
	DRAM_ELPIDA = 0X3,
	DRAM_ETRON = 0X4,
	DRAM_NANYA = 0X5,
	DRAM_HYNIX = 0X6,
	DRAM_MOSEL = 0X7,
	DRAM_WINBOND = 0X8,
	DRAM_ESMT = 0X9,
	DRAM_SPANSION = 0XB,
	DRAM_SST = 0XC,
	DRAM_ZMOS = 0XD,
	DRAM_INTEL = 0XE,
	DRAM_NUMONYX = 0XFE,
	DRAM_MICRON = 0XFF,
}DRAM_MANUFACTURE_ID;


typedef enum __DRAM_TYPE {
	DRAM_DDR1,
	DRAM_DDR2,
	DRAM_DDR3,
	DRAM_DDR4,

	DRAM_LPDDR1=0x100,
	DRAM_LPDDR2,
	DRAM_LPDDR3,
	DRAM_LPDDR4

}DRAM_TYPE;

typedef struct __lpddr_jedec_originize {
	u32 cs_size;
	int dw;
	int bank;
	int row;
	int column;
}LPDDR_JEDEC_ORIGINIZE;

typedef struct __DRAM_JEDEC_INFO {
	int cs_index;
	int bank;
	int row;
	int column;
	int dw;
	int ap;			/*auto precharge pin index 10/11/12/13 */
	u32 cs_size;
}DRAM_JEDEC_INFO;

typedef struct __DRAM_JEDEC_ADDR {
	int cs;
	int bank;
	int row;
	int column;
}DRAM_JEDEC_ADDR;


typedef struct __DRAM_CHIP_INFO {
	DRAM_TYPE chip_type;
	DRAM_MANUFACTURE_ID manufacture_id;
	int cs_num;
	DRAM_JEDEC_INFO *cs0_jedec_info;
	DRAM_JEDEC_INFO *cs1_jedec_info;
	int unsymmetry;		/*unsymmetry ddr chip such as 6Gb/12Gb.0 symmetry chip. 1 unsymetry chip*/
}DRAM_CHIP_INFO;

typedef enum __DDR_UNSYMMETRY_MODE {
	DDR_6Gb_10_COL_MODE,
	DDR_6Gb_11_COL_MODE,
	DDR_12Gb_MODE,
}DDR_UNSYMMETRY_MODE;

typedef struct __LPDDR_MR_INFO {
	int bl;			/*burst length*/
	int bt;			/*burst type*/
	int wc;			/*wrap*/
	int nwr;		/*nwr*/
	int rl;			/*read latency*/
	int wl;			/*write latency*/
	int ds;			/*driver strength*/
}LPDDR_MR_INFO;


typedef enum __DMC_DRV_STRENGTH {
	DRV_34_OHM = 0x22,		/*34.3ohm*/
	DRV_40_OHM = 0x28,		/*40ohm*/
	DRV_48_OHM = 0x30,		/*48ohm*/
	DRV_60_OHM = 0x3c,		/*60ohm*/
	DRV_80_OHM = 0x50,		/*80ohm*/
	DRV_120_OHM = 0x78,		/*120ohm*/
}DMC_DRV_STRENGTH;


/*CA delay line*/
#define CFG_DLL_CLKWR_AC		0x80000008
#define CFG_DLL_CLKWR_DS0		0x80000008
#define CFG_DLL_CLKWR_DS1		0x80000008
#define CFG_DLL_CLKWR_DS2		0x80000008
#define CFG_DLL_CLKWR_DS3		0x80000008
#define CFG_DLL_DQSIN_POS_DS0	0x80000008
#define CFG_DLL_DQSIN_POS_DS1	0x80000008
#define CFG_DLL_DQSIN_POS_DS2	0x80000008
#define CFG_DLL_DQSIN_POS_DS3	0x80000008
#define CFG_DLL_DQSIN_NEG_DS0	0x80000008
#define CFG_DLL_DQSIN_NEG_DS1	0x80000008
#define CFG_DLL_DQSIN_NEG_DS2	0x80000008
#define CFG_DLL_DQSIN_NEG_DS3	0x80000008

#define DMC_DQSGATE_DL_DS0	0x80000008
#define DMC_DQSGATE_DL_DS1	0x80000008
#define DMC_DQSGATE_DL_DS2	0x80000008
#define DMC_DQSGATE_DL_DS3	0x80000008
/*default burst length*/
#define DEFAULT_LPDDR2_BL	8
#define DEFAULT_LPDDR3_BL	8
/*configed burst length.Uncommitted to enable it*/
//#define CFG_BL	4

#define CFG_DRAM_TYPE				DRAM_LPDDR3
#define CFG_IS_UNSYMMETRY_DRAM		0
#define CFG_UNSYMMETRY_DRAM_MODE	DDR_6Gb_10_COL_MODE

#define CFG_CS_NUM		1

#define CFG_CS0_BANK_NUM	8
#define CFG_CS0_ROW_NUM		15
#define CFG_CS0_COLUMN_NUM	10
#define CFG_CS0_DQ_DW		32
#define CFG_CS0_AP_PIN_POS	10
#define CFG_CS0_SIZE	0x40000000

#define CFG_CS1_BANK_NUM	8
#define CFG_CS1_ROW_NUM		14
#define CFG_CS1_COLUMN_NUM	10
#define CFG_CS1_DQ_DW		32
#define CFG_CS1_AP_PIN_POS	10
#define CFG_CS1_SIZE	0x20000000

#define MRR_BYTE_SWITCH_INDEX 0



DRAM_TYPE dmc_get_ddr_type(void);
int sdram_chip_cs_num(void);
int sdram_chip_data_width(void);
int sdram_cs_whole_size(int cs, u32 *size);
void dmc_sprd_delay(int x);


int trans_addr_to_jedec_addr(u32 addr, DRAM_JEDEC_ADDR *jedec_addr);
void reset_dmc_fifo(void);
//extern const MCU_CLK_PARA_T mcu_clk_para;
#endif

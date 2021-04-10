#ifndef __DMC_SPRD_R1P0_H__
#define __DMC_SPRD_R1P0_H__

#define DMC_REG_ADDR_BASE_PHY 0x30000000
#define ADDR_CS_ROW_BANK_COLUMN
#define DDR_DRV_CFG 48

#ifndef DDR_CLK
#define DDR_CLK 400
#endif

#define DMC_CAL_RESISTANCE_ORG 960						/*calibration orginal resistance value 960 ohm*/
#define DMC_CAL_FACTOR_MIN 		1
#define DMC_CAL_FACTOR_MAX 		32

#define MAX_CHANNEL_NUM 10

#define DDR_START_ADDR_PHY		0x80000000

#define BIST_RESERVE_SIZE 		0x40000
#define SYS_MAP_RESERVE_SIZE 	0x200000

typedef struct port_para{
	u8	timeout_pri_wr_ch;
	u8	timeout_thr_wr_ch;
	u8	timeout_thr_rd_ch;
}PORT_PARA;

typedef struct __PIKE_DMC_REG_INFO {
	volatile unsigned int dmc_cfg0;						/*addr:0x0*/
	volatile unsigned int dmc_cfg1;						/*addr:0x4*/
	volatile unsigned int pad0[6];			
	volatile unsigned int ahbaxireg[35];				/*addr:0x20*/
	volatile unsigned int dmc_sts3;						/*addr:0xac*/
	volatile unsigned int pad1[20];			
	volatile unsigned int dmc_dcfg0;					/*addr:0x100*/
	volatile unsigned int dmc_dcfg1;					/*addr:0x104*/
	volatile unsigned int dmc_dcfg2;					/*addr:0x108*/
	volatile unsigned int dmc_dcfg3;					/*addr:0x10c*/
	volatile unsigned int dmc_dcfg4;					/*addr:0x110*/	
	volatile unsigned int pad2[3];				
	volatile unsigned int dmc_lpcfg0;					/*addr:0x120*/
	volatile unsigned int dmc_lpcfg1;					/*addr:0x124*/
	volatile unsigned int dmc_lpcfg2;					/*addr:0x128*/
	volatile unsigned int dmc_lpcfg3;					/*addr:0x12c*/
	volatile unsigned int pad3[4];				
	volatile unsigned int dmc_dtmg_f0[11];				/*addr:0x140*/
	volatile unsigned int pad4[1];
	volatile unsigned int dmc_dtmg_f1[11];				/*addr:0x170*/
	volatile unsigned int pad5[1];
	volatile unsigned int dmc_dtmg_f2[11];				/*addr:0x1a0*/
	volatile unsigned int pad6[1];
	volatile unsigned int dmc_dtmg_f3[11];				/*addr:0x1d0*/
	volatile unsigned int pad7[1];	
	volatile unsigned int dmc_bist[27];					/*addr:0x200*/
	volatile unsigned int pad8[37];
	volatile unsigned int dmc_cfg_dll_ac;				/*addr:0x300*/
	volatile unsigned int dmc_sts_dll_ac;				/*addr:0x304*/
	volatile unsigned int dmc_clkwr_dll_ac;				/*addr:0x308*/
	volatile unsigned int dmc_addr_out0_dll_ac;			/*addr:0x30c*/
	volatile unsigned int pad9[1];
	volatile unsigned int dmc_addr_out1_dll_ac;			/*addr:0x314*/
	volatile unsigned int pad10[1];
	volatile unsigned int dmc_cmd_out0_dll_ac;			/*addr:0x31c*/
	volatile unsigned int pad11[1];
	volatile unsigned int dmc_cmd_out1_dll_ac;			/*addr:0x324*/
	volatile unsigned int pad12[54];
	volatile unsigned int dmc_cfg_dll_ds0;				/*addr:0x400*/
	volatile unsigned int dmc_sts_dll_ds0;				/*addr:0x404*/
	volatile unsigned int dmc_clkwr_dll_ds0;			/*addr:0x408*/
	volatile unsigned int dmc_dqsin_pos_dll_ds0;		/*addr:0x40c*/
	volatile unsigned int dmc_dqsin_neg_dll_ds0;		/*addr:0x410*/
	volatile unsigned int dmc_dqsgate_pre_dll_ds0;		/*addr:0x414*/
	volatile unsigned int dmc_dqsgate_pst_dll_ds0;		/*addr:0x418*/
	volatile unsigned int dmc_date_out_dll_ds0;			/*addr:0x41c*/
	volatile unsigned int pad13[1];
	volatile unsigned int dmc_data_in_dll_ds0;			/*addr:0x424*/
	volatile unsigned int pad14[1];
	volatile unsigned int dmc_dmdqs_inout_dll_ds0;		/*addr:0x42c*/
	volatile unsigned int pad15[52];
	volatile unsigned int dmc_cfg_dll_ds1;				/*addr:0x500*/
	volatile unsigned int dmc_sts_dll_ds1;				/*addr:0x504*/
	volatile unsigned int dmc_clkwr_dll_ds1;			/*addr:0x508*/
	volatile unsigned int dmc_dqsin_pos_dll_ds1;		/*addr:0x50c*/
	volatile unsigned int dmc_dqsin_neg_dll_ds1;		/*addr:0x510*/
	volatile unsigned int dmc_dqsgate_pre_dll_ds1;		/*addr:0x514*/
	volatile unsigned int dmc_dqsgate_pst_dll_ds1;		/*addr:0x518*/
	volatile unsigned int dmc_date_out_dll_ds1;			/*addr:0x51c*/
	volatile unsigned int pad16[1];
	volatile unsigned int dmc_data_in_dll_ds1;			/*addr:0x524*/
	volatile unsigned int pad17[1];
	volatile unsigned int dmc_dmdqs_inout_dll_ds1;		/*addr:0x52c*/
	volatile unsigned int pad18[52];	
	volatile unsigned int dmc_cfg_dll_ds2;				/*addr:0x600*/
	volatile unsigned int dmc_sts_dll_ds2;				/*addr:0x604*/
	volatile unsigned int dmc_clkwr_dll_ds2;			/*addr:0x608*/
	volatile unsigned int dmc_dqsin_pos_dll_ds2;		/*addr:0x60c*/
	volatile unsigned int dmc_dqsin_neg_dll_ds2;		/*addr:0x610*/
	volatile unsigned int dmc_dqsgate_pre_dll_ds2;		/*addr:0x614*/
	volatile unsigned int dmc_dqsgate_pst_dll_ds2;		/*addr:0x618*/
	volatile unsigned int dmc_date_out_dll_ds2;			/*addr:0x61c*/
	volatile unsigned int pad19[1];
	volatile unsigned int dmc_data_in_dll_ds2;			/*addr:0x624*/
	volatile unsigned int pad20[1];
	volatile unsigned int dmc_dmdqs_inout_dll_ds2;		/*addr:0x62c*/
	volatile unsigned int pad21[52];
	volatile unsigned int dmc_cfg_dll_ds3;				/*addr:0x700*/
	volatile unsigned int dmc_sts_dll_ds3;				/*addr:0x704*/
	volatile unsigned int dmc_clkwr_dll_ds3;			/*addr:0x708*/
	volatile unsigned int dmc_dqsin_pos_dll_ds3;		/*addr:0x70c*/
	volatile unsigned int dmc_dqsin_neg_dll_ds3;		/*addr:0x710*/
	volatile unsigned int dmc_dqsgate_pre_dll_ds3;		/*addr:0x714*/
	volatile unsigned int dmc_dqsgate_pst_dll_ds3;		/*addr:0x718*/
	volatile unsigned int dmc_date_out_dll_ds3;			/*addr:0x71c*/
	volatile unsigned int pad22[1];
	volatile unsigned int dmc_data_in_dll_ds3;			/*addr:0x724*/
	volatile unsigned int pad23[1];
	volatile unsigned int dmc_dmdqs_inout_dll_ds3;		/*addr:0x72c*/	
}PIKE_DMC_REG_INFO, *PIKE_DMC_REG_INFO_PTR;

typedef struct __dmc_character {
	int auto_gate;										/*auto close clock. 0 disable 1 enable*/
	int auto_sleep;										/*auto sleep. 0 disable 1 enable*/
	int cs_merge;										/*which cs will be merged to when enlarge cs size*/
	int cmd_queue_m;									/*command queue mode. 0 close 1 open*/
	int row_hit_detect;									/*row hit detect function. 0 disable 1 enable*/
	int clk_always_on;									/*clk is always on. 0 no 1 yes */
}DMC_CHARACTER;

typedef enum __dmc_cmd_cs_index {
	CMD_CS_0,
	CMD_CS_1,
	CMD_CS_BOTH
}DMC_CMD_CS_INDEX;

typedef struct dmc_jedec_timing_cfg {
	unsigned int tRRD;
	unsigned int tCCD;
	unsigned int tRCD;
	unsigned int tRP;
	unsigned int tRTR;
	unsigned int tWTR;
	unsigned int tRTW;
	unsigned int tRTP;
	unsigned int tRFC;
	unsigned int tWR;
	unsigned int tXSR;
	unsigned int tCKE;
	unsigned int tXP;
	unsigned int tMRD;
	unsigned int tFAW;
	unsigned int tRAS;		
}DMC_JEDEC_TIMING_CFG;

typedef struct dmc_local_timing_cfg {
	unsigned int dtmg4;
	unsigned int dtmg5;
	unsigned int dtmg6;
	unsigned int dtmg7;
	unsigned int dtmg8;
	unsigned int dtmg9;
	unsigned int dtmg10;
}DMC_LOCAL_TIMING_CFG;

typedef struct dmc_delay_line_cfg {
	unsigned int dmc_clkwr_dll_ac;
	
	unsigned int dmc_clkwr_dll_ds0;
	unsigned int dmc_clkwr_dll_ds1;
	unsigned int dmc_clkwr_dll_ds2;
	unsigned int dmc_clkwr_dll_ds3;
	
	unsigned int dmc_dqsin_pos_dll_ds0;
	unsigned int dmc_dqsin_pos_dll_ds1;
	unsigned int dmc_dqsin_pos_dll_ds2;
	unsigned int dmc_dqsin_pos_dll_ds3;
	
	unsigned int dmc_dqsin_neg_dll_ds0;
	unsigned int dmc_dqsin_neg_dll_ds1;
	unsigned int dmc_dqsin_neg_dll_ds2;
	unsigned int dmc_dqsin_neg_dll_ds3;
	
	unsigned int dmc_dqsgate_pre_dll_ds0;
	unsigned int dmc_dqsgate_pre_dll_ds1;
	unsigned int dmc_dqsgate_pre_dll_ds2;
	unsigned int dmc_dqsgate_pre_dll_ds3;
	
	unsigned int dmc_dqsgate_pst_dll_ds0;
	unsigned int dmc_dqsgate_pst_dll_ds1;
	unsigned int dmc_dqsgate_pst_dll_ds2;
	unsigned int dmc_dqsgate_pst_dll_ds3;
	
	unsigned int dmc_date_out_dll_ds0;
	unsigned int dmc_date_out_dll_ds1;
	unsigned int dmc_date_out_dll_ds2;
	unsigned int dmc_date_out_dll_ds3;

	unsigned int dmc_dmdqs_inout_dll_ds0;
	unsigned int dmc_dmdqs_inout_dll_ds1;
	unsigned int dmc_dmdqs_inout_dll_ds2;
	unsigned int dmc_dmdqs_inout_dll_ds3;

	unsigned int dmc_data_in_dll_ds0;
	unsigned int dmc_data_in_dll_ds1;
	unsigned int dmc_data_in_dll_ds2;
	unsigned int dmc_data_in_dll_ds3;

	unsigned int dmc_cfg_dll_ac;
	unsigned int dmc_cfg_dll_ds0;
	unsigned int dmc_cfg_dll_ds1;
	unsigned int dmc_cfg_dll_ds2;
	unsigned int dmc_cfg_dll_ds3;	

	unsigned int dmc_addr_out0_dll_ac;
	unsigned int dmc_addr_out1_dll_ac;
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
	DRAM_LPDDR4,
	
}DRAM_TYPE;

typedef struct __DRAM_JEDEC_INFO {
	int cs_index;
	int bank;
	int row;
	int column;
	int dw;
	int ap;			/*auto precharge pin index 10/11/12/13 */
	unsigned int cs_size;
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

typedef struct __LPDDR2_MR_INFO {
	int bl;			/*burst length*/
	int bt;			/*burst type*/
	int wc;			/*wrap*/
	int nwr;		/*nwr*/
	int rl;			/*read latency*/
	int wl;			/*write latency*/
	int ds;			/*driver strength*/
}LPDDR2_MR_INFO;

typedef struct __LPDDR3_MR_INFO {
	int bl;			/*burst length*/
	int bt;			/*burst type*/
	int wc;			/*wrap*/
	int nwr;		/*nwr*/
	int rl;			/*read latency*/
	int wl;			/*write latency*/
	int ds;			/*driver strength*/
}LPDDR3_MR_INFO;

typedef enum __DMC_DRV_STRENGTH {
	DRV_34_OHM = 0x22,		/*34.3ohm*/
	DRV_40_OHM = 0x28,		/*40ohm*/
	DRV_48_OHM = 0x30,		/*48ohm*/
	DRV_60_OHM = 0x3c,		/*60ohm*/
	DRV_80_OHM = 0x50,		/*80ohm*/
	DRV_120_OHM = 0x78,		/*120ohm*/
}DMC_DRV_STRENGTH;

typedef enum __PULL_RESIS_VAL {
	PULL_RESIS_660_OHM,
	PULL_RESIS_1000_OHM,
	PULL_RESIS_3000_OHM,
	PULL_RESIS_INFINITE_OHM,
}PULL_RESIS_VAL;

typedef struct mem_cs_info
{
	unsigned int cs_number;
	unsigned int cs0_size;//bytes
	unsigned int cs1_size;//bytes
}mem_cs_info_t;



DRAM_TYPE dmc_get_ddr_type(void);
int sdram_chip_cs_num(void);
int sdram_chip_data_width(void);
int sdram_cs_whole_size(int cs, unsigned int *size);



int trans_addr_to_jedec_addr(u32 addr, DRAM_JEDEC_ADDR *jedec_addr);
void reset_dmc_fifo(void);


//#define DDR_AUTO_DETECT

/*dmc io pin driver strength*/
#define DRV_PIN_POS_DQ_BYTE0	40
#define DRV_PIN_NEG_DQ_BYTE0	40

#define DRV_PIN_POS_DQ_BYTE1	DRV_PIN_POS_DQ_BYTE0
#define DRV_PIN_NEG_DQ_BYTE1	DRV_PIN_NEG_DQ_BYTE0

#define DRV_PIN_POS_DQ_BYTE2	DRV_PIN_POS_DQ_BYTE0
#define DRV_PIN_NEG_DQ_BYTE2	DRV_PIN_NEG_DQ_BYTE0

#define DRV_PIN_POS_DQ_BYTE3	DRV_PIN_POS_DQ_BYTE0
#define DRV_PIN_NEG_DQ_BYTE3	DRV_PIN_NEG_DQ_BYTE0

#define DRV_PIN_POS_DQS0_T		40
#define DRV_PIN_NEG_DQS0_T		40

#define DRV_PIN_POS_DQS0_C		DRV_PIN_POS_DQS0_T
#define DRV_PIN_NEG_DQS0_C		DRV_PIN_NEG_DQS0_T

#define DRV_PIN_POS_DQS1_T		DRV_PIN_POS_DQS0_T
#define DRV_PIN_NEG_DQS1_T		DRV_PIN_NEG_DQS0_T

#define DRV_PIN_POS_DQS1_C		DRV_PIN_POS_DQS0_T
#define DRV_PIN_NEG_DQS1_C		DRV_PIN_NEG_DQS0_T

#define DRV_PIN_POS_DQS2_T		DRV_PIN_POS_DQS0_T
#define DRV_PIN_NEG_DQS2_T		DRV_PIN_NEG_DQS0_T

#define DRV_PIN_POS_DQS2_C		DRV_PIN_POS_DQS0_T
#define DRV_PIN_NEG_DQS2_C		DRV_PIN_NEG_DQS0_T

#define DRV_PIN_POS_DQS3_T		DRV_PIN_POS_DQS0_T
#define DRV_PIN_NEG_DQS3_T		DRV_PIN_NEG_DQS0_T

#define DRV_PIN_POS_DQS3_C		DRV_PIN_POS_DQS0_T
#define DRV_PIN_NEG_DQS3_C		DRV_PIN_NEG_DQS0_T

#define DRV_PIN_POS_CA			48
#define DRV_PIN_NEG_CA			48

#define DRV_PIN_POS_CK_T		40
#define DRV_PIN_NEG_CK_T		40

#define DRV_PIN_POS_CK_C		DRV_PIN_POS_CK_T
#define DRV_PIN_NEG_CK_C		DRV_PIN_NEG_CK_T

#define DRV_PIN_POS_CS0			48
#define DRV_PIN_NEG_CS0			48

#define DRV_PIN_POS_CS1			DRV_PIN_POS_CS0
#define DRV_PIN_NEG_CS1			DRV_PIN_NEG_CS0

#define DRV_PIN_POS_CKE0		DRV_PIN_POS_CS0
#define DRV_PIN_NEG_CKE0		DRV_PIN_NEG_CS0
#if 0
#define DRV_PIN_POS_CKE1		40
#define DRV_PIN_NEG_CKE1		40
#endif

#define PULL_DQS0_T_RESIS_VAL	PULL_RESIS_3000_OHM
#define PULL_DQS0_C_RESIS_VAL	PULL_RESIS_3000_OHM
#define PULL_DQS1_T_RESIS_VAL	PULL_RESIS_3000_OHM
#define PULL_DQS1_C_RESIS_VAL	PULL_RESIS_3000_OHM
#define PULL_DQS2_T_RESIS_VAL	PULL_RESIS_3000_OHM
#define PULL_DQS2_C_RESIS_VAL	PULL_RESIS_3000_OHM
#define PULL_DQS3_T_RESIS_VAL	PULL_RESIS_3000_OHM
#define PULL_DQS3_C_RESIS_VAL	PULL_RESIS_3000_OHM

/*CA delay line*/
#define CFG_DLL_CLKWR_AC		0xc0030020
#define CFG_DLL_CLKWR_DS0		0x80000020
#define CFG_DLL_CLKWR_DS1		0x80000020
#define CFG_DLL_CLKWR_DS2		0x80000020
#define CFG_DLL_CLKWR_DS3		0x80000020
#define CFG_DLL_DQSIN_POS_DS0	0xc0050020
#define CFG_DLL_DQSIN_POS_DS1	0xc0050020
#define CFG_DLL_DQSIN_POS_DS2	0xc0050020
#define CFG_DLL_DQSIN_POS_DS3	0xc0050020
#define CFG_DLL_DQSIN_NEG_DS0	0xc0050020
#define CFG_DLL_DQSIN_NEG_DS1	0xc0050020
#define CFG_DLL_DQSIN_NEG_DS2	0xc0050020
#define CFG_DLL_DQSIN_NEG_DS3	0xc0050020

/*default burst length*/
#define DEFAULT_LPDDR2_BL	4
#define DEFAULT_LPDDR3_BL 	8
/*configed burst length.Uncommitted to enable it*/
//#define CFG_BL	4

#define CFG_DRAM_TYPE				DRAM_LPDDR3
#define CFG_IS_UNSYMMETRY_DRAM		0
#define CFG_UNSYMMETRY_DRAM_MODE	DDR_6Gb_10_COL_MODE

#define CFG_CS_NUM 		1

#define CFG_CS0_BANK_NUM	8
#define CFG_CS0_ROW_NUM		14
#define CFG_CS0_COLUMN_NUM	10
#define CFG_CS0_DQ_DW		32
#define CFG_CS0_AP_PIN_POS	10
#define CFG_CS0_SIZE	0x20000000

#define CFG_CS1_BANK_NUM	8
#define CFG_CS1_ROW_NUM		14
#define CFG_CS1_COLUMN_NUM	10
#define CFG_CS1_DQ_DW		32
#define CFG_CS1_AP_PIN_POS	10
#define CFG_CS1_SIZE	0x20000000

#define MRR_BYTE_SWITCH_INDEX 0

extern const MCU_CLK_PARA_T mcu_clk_para;

#endif

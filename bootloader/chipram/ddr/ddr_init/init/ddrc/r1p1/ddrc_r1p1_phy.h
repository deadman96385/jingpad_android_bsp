#ifndef _DDRC_R1P1_PHY_H__
#define _DDRC_R1P1_PHY_H__

typedef struct {
volatile uint32 cabt_enable;//CA Training
volatile uint32 gate_enable;//gate training
volatile uint32 reye_enable;//read eye training
volatile uint32 rdvref_train_enable;//read vref training
volatile uint32 weye_enable;//write eye training
volatile uint32 wrvref_train_enable;//write vref training
volatile uint32 perbitwr_enable ;
volatile uint32 perbitrd_enable;
volatile uint32 ca_perbit_enable;
volatile uint32 dll_half_mode;
}TRAIN_CFG_TABLE;

typedef struct{
	uint32 clk_freq;	//Mhz
	uint32 freq_index;
	uint8  dq_odt_en;
	uint8  ca_odt_en;
}DDR_CLK_ASSO_CFG;

typedef struct {
	volatile uint32 rank1_training_done;
	volatile uint32 iopvt_zq_cal_done;
	volatile uint32 caperbit_done;
	volatile uint32 rdperbit_done;
	volatile uint32 wrperbit_done;

	volatile uint32 ca_shorter_rank;
	volatile uint32 wr_shorter_rank;
	volatile uint32 wr_shorter_rank_db0;
	volatile uint32 wr_shorter_rank_db1;
}TRAIN_STATUS_TABLE;

typedef struct {
	uint32 rank;
	uint32 freq_sel;
}TRAIN_CONDITIONS_TABLE;

typedef enum TRAIN_ENABLE{
	BIT14_WVREF = 0x00004000,
	BIT13_WREYE = 0x00002000,
	BIT12_WPERB = 0x00001000,
	BIT11_RVREF  = 0x00000800,
	BIT10_RDEYE  = 0x00000400,
	BIT09_RPERB  = 0x00000200,
	BIT08_GATE    = 0x00000100,
	BIT06_CA        = 0x00000040,
	BIT05_CA_PERB = 0x00000020,
	BIT01_IOPVT   = 0x00000002
} TRAIN_ENABLE_BIT_SEL;

typedef enum TRAIN_DONE {
	BIT23_WREYE_DONE = 0x00800000,
	BIT21_WPERB_DONE = 0x00200000,
	BIT19_RDEYE_DONE  = 0x00080000,
	BIT17_RPERB_DONE  = 0x00020000,
	BIT15_GATE_DONE    = 0x00008000,
	BIT11_CA_DONE        = 0x00000800,
	BIT09_CA_PERB_DONE = 0x00000200,
	BIT02_IOPVT_DONE   = 0x00000004
} TRAIN_DONE_BIT_SEL;

#endif



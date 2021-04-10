#ifndef _DDRC_R1P0_PHY_H__
#define _DDRC_R1P0_PHY_H__

typedef struct {
	volatile u32 cabt_enable;//CA Training
	volatile u32 ca_perb_enable;//CA perbit training
	volatile u32 ca_vref_enable;//CA vref training
	volatile u32 gate_enable;//gate training
	volatile u32 reye_enable;//read eye training
	volatile u32 pbrd_enable;//read perbit training
	volatile u32 rdvref_train_enable;//read vref training
	volatile u32 weye_enable;//write eye training
	volatile u32 pbwr_enable;//write perbit training
	volatile u32 wrvref_train_enable;//write vref training
	volatile u32 gate_edge_mode;//gate window or edge mode
	volatile u32 final_odt_en;//last initial odt status

	volatile u32 cur_odt_on;
	volatile u32 perbitwr_enable ;
	volatile u32 perbitrd_enable;
	volatile u32 ca_perbit_enable;

	volatile u32 rank1_training_done;
	volatile u32 iopvt_zq_cal_done;
	volatile u32 CAPERBIT_DONE;
	volatile u32 RDPERBIT_DONE;
	volatile u32 WRPERBIT_DONE;

	volatile u32 CA_SHORTER_RANK;
	volatile u32 WR_SHORTER_RANK;
	volatile u32 WR_SHORTER_RANK_DB0;
	volatile u32 WR_SHORTER_RANK_DB1;
}TRAIN_STATUS_TABLE;

typedef struct {
    u32 rank;
    u32 flow_type;
    u32 wr_dsk_dll;
    u32 cur_odt_en;
    u32 mrw_en;
}TRAIN_CONDITIONS_TABLE;

typedef enum TRAIN_ENABLE{
	BIT14_WVREF = 0x00006000,
	BIT13_WREYE = 0X00002000,
	BIT12_WPERB = 0X00003000,
	BIT11_RVREF  = 0X00000C00,
	BIT10_RDEYE  = 0X00000400,
	BIT09_RPERB  = 0X00000600,
	BIT08_GATE    = 0X00000100,
	BIT06_CA        = 0X00000040,
	BIT05_CA_PERB = 0X00000060,
	BIT01_IOPVT   = 0X00000002
} TRAIN_ENABLE_BIT_SEL;

typedef enum TRAIN_DONE {
	BIT23_WREYE_DONE = 0X00800000,
	BIT21_WPERB_DONE = 0X00200000,
	BIT19_RDEYE_DONE  = 0X00080000,
	BIT17_RPERB_DONE  = 0X00020000,
	BIT15_GATE_DONE    = 0X00008000,
	BIT11_CA_DONE        = 0X00000800,
	BIT09_CA_PERB_DONE = 0X00000200,
	BIT02_IOPVT_DONE   = 0X00000004
} TRAIN_DONE_BIT_SEL;
/*Use for scan*/
typedef struct
{
	u32 PHY0_CA_E6;
	u32 PHY0_READ_EA;
	u32 PHY0_READ_EB;
	u32 PHY0_READ_ED;
	u32 PHY0_WRITE_E9;
	u32 PHY0_WRITE_EC;
	u32 PHY0_WRITE_EE;

	u32 PHY1_CA_E6;
	u32 PHY1_READ_EA;
	u32 PHY1_READ_EB;
	u32 PHY1_READ_ED;
	u32 PHY1_WRITE_E9;
	u32 PHY1_WRITE_EC;
	u32 PHY1_WRITE_EE;
}RANK0_TRAINING_SCAN;
#endif

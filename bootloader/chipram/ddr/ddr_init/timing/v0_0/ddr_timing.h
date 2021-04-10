#define CLK_166MHZ_FN 2
#define CLK_400MHZ_FN 1
#define CLK_640MHZ_FN 3
#define CLK_800MHZ_FN 0

typedef struct
{
	unsigned long freq_point;
	unsigned long ddr_clk;
	//ac timing
	unsigned long ADDITIVE_LAT;
	unsigned long CASLAT_LIN;
	unsigned long CKE_DELAY;
	unsigned long CKE_INACTIVE;
	unsigned long CKSRE;
	unsigned long CKSRX;
	unsigned long DLL_RST_ADJ_DLY;
	unsigned long DLL_RST_DELAY;
	unsigned long TCAENT;
	unsigned long TCAEXT;
	unsigned long TCACKEL;
	unsigned long TCACKEH;
	unsigned long TCAMRD;
	unsigned long TCCD;
	unsigned long TCKE;
	unsigned long TCKESR;
	unsigned long TDLL;
	unsigned long TDAL;
	unsigned long TDQSCK_MAX;
	unsigned long TDQSCK_MIN;
	unsigned long TFAW;
	unsigned long TINIT;
	unsigned long TINIT3;
	unsigned long TINIT4;
	unsigned long TINIT5;
	unsigned long TMOD;
	unsigned long TMRD;
	unsigned long TMRR;
	unsigned long TMRZ;
	unsigned long TMRRI;
	unsigned long TPDEX;
	unsigned long TRAS_MAX;
	unsigned long TRAS_MIN;
	unsigned long TRC;
	unsigned long TRCD;
	unsigned long TREF;
	unsigned long TREF_INTERVAL;
	unsigned long TRFC;
	unsigned long TRP;
	unsigned long TRP_AB_CSx;
	unsigned long TRRD;
	unsigned long TRST_PWRON;
	unsigned long TRTP;
	unsigned long TWR;
	unsigned long TWTR;
	unsigned long TXPDLL;
	unsigned long TXSNR;
	unsigned long TXSR;
	unsigned long RDLAT_ADJ;
	unsigned long R2R_DIFFCS_DLY;
	unsigned long R2R_SAMECS_DLY;
	unsigned long R2W_DIFFCS_DLY;
	unsigned long R2W_SAMECS_DLY;
	unsigned long W2R_DIFFCS_DLY;
	unsigned long W2R_SAMECS_DLY;
	unsigned long W2W_DIFFCS_DLY;
	unsigned long W2W_SAMECS_DLY;
	unsigned long WRLAT;
	unsigned long WRLAT_ADJ;
	unsigned long ZQINIT;
	unsigned long ZQCS;
	unsigned long ZQCL;
	unsigned long ZQRESET;
	unsigned long ZQ_INTERVAL;
	//dfi low power
	unsigned long LPI_TIMER_WAKEUP;
	unsigned long LPI_SR_MCCLK_GATE_WAKEUP;
	unsigned long LPI_SR_WAKEUP;
	unsigned long LPI_PD_WAKEUP;
	unsigned long TDFI_LP_RESP;
	unsigned long LPI_WAKEUP_TIMEOUT;
	unsigned long LP_AUTO_SR_MC_GATE_IDLE;
	unsigned long LP_AUTO_SR_IDLE;
	unsigned long LP_AUTO_PD_IDLE;
	//odt timing
	unsigned long TODTH_WR;
	unsigned long TODTL_2CMD;
	unsigned long TODTH_RD;
	unsigned long WR_TO_ODTH;
	unsigned long RD_TO_ODTH;
	//dfi timing
	unsigned long TDFI_CALVL_CAPTURE;
	unsigned long TDFI_CALVL_CC;
	unsigned long TDFI_CALVL_EN;
	unsigned long TDFI_CALVL_RESP;
	unsigned long TDFI_CALVL_MAX;
	unsigned long TDFI_CTRL_DELAY;
	unsigned long TDFI_CTRLUPD_INTERVAL;
	unsigned long TDFI_CTRLUPD_MAX;
	unsigned long TDFI_DRAM_CLK_ENABLE;
	unsigned long TDFI_DRAM_CLK_DISABLE;
	unsigned long TDFI_INIT_START;
	unsigned long TDFI_INIT_COMPLETE;
	unsigned long TDFI_PHY_RDLAT;
	unsigned long TDFI_PHY_WRDATA;
	unsigned long TDFI_PHYUPD_TYPE0;
	unsigned long TDFI_PHYUPD_TYPE1;
	unsigned long TDFI_PHYUPD_TYPE2;
	unsigned long TDFI_PHYUPD_TYPE3;
	unsigned long TDFI_PHYUPD_RESP;
	unsigned long TDFI_RDLVL_RR;
	unsigned long TDFI_RDLVL_EN;
	unsigned long TDFI_RDLVL_RESP;
	unsigned long TDFI_RDLVL_MAX;
	unsigned long TDFI_RDCSLAT;
	unsigned long TDFI_WRCSLAT;
	unsigned long TDFI_WRLVL_EN;
	unsigned long TDFI_WRLVL_WW;
	unsigned long TDFI_WRLVL_RESP;
	unsigned long TDFI_WRLVL_MAX;
	//leveling timing
	unsigned long CALVL_INTERVAL;
	unsigned long RDLVL_INTERVAL;
	unsigned long RDLVL_GATE_INTERVAL;
	unsigned long WRLVL_INTERVAL;
	//mode register
	unsigned long MR0_DATA_CSn;
	unsigned long MR1_DATA_CSn;
	unsigned long MR2_DATA_CSn;
	unsigned long MR3_DATA_CSn;
	unsigned long MR11_DATA_CSn;
	unsigned long MR16_DATA_CSn;
	unsigned long MR17_DATA_CSn;
}CANDS_CTL_TIMING_T;

typedef struct
{
	unsigned long freq_point;
	unsigned long ddr_clk;
	//silice 0~3 = byte0~3, slice 4 = addr/cmd
	unsigned long DEN_PHY_DQ_TIMING_REG;
	unsigned long DEN_PHY_DQS_TIMING_REG;
	unsigned long DEN_PHY_GATE_LPBK_CTRL_REG;
	unsigned long DEN_PHY_READ_CTRL_REG;
	unsigned long PHY_DLL_MASTER_CTRL_REG;
	unsigned long PHY_DLL_SLAVE_CTRL_REG;
	unsigned long DEN_PHY_IE_TIMING_REG;
	unsigned long PHY_LVL_DBG_CONT_REG;
	unsigned long PHY_LVL_CONFIG_REG;
	unsigned long PHY_WRLVL_CONFIG_REG;
	//phy core
	unsigned long DEN_PHY_CTRL_REG;
	unsigned long DEN_PHY_DESKEW_CTRL_REG;
	unsigned long DEN_PHY_DESKEW_BYPASS_REG;
	unsigned long DEN_PHY_CALVL_CTRL_REG;
	unsigned long DEN_PHY_LP_WAKEUP_REG;
	unsigned long DEN_PHY_PAD_TSEL_REG;
	unsigned long PHY_PAD_DRIVE_REG_0;
	unsigned long PHY_PAD_DRIVE_REG_1;
	unsigned long PHY_PAD_DRIVE_REG_2;
	unsigned long PHY_PAD_TERM_REG_0;
	unsigned long PHY_PAD_CAL_CTRL_REG0;
	unsigned long PHY_PAD_ATB_CTRL_REG_AC;
	unsigned long PHY_PAD_VREF_CTRL_REG_AC;
	unsigned long PHY_CDN_CAL_INTERVAL_REG_AC_0;
	unsigned long PHY_CDN_CAL_INTERVAL_REG_AC_1;
}CANDS_PHY_TIMING_T;



CANDS_CTL_TIMING_T *__get_ctl_timing_info();

CANDS_PHY_TIMING_T *__get_phy_timing_info();


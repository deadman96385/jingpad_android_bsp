#ifndef _LPDDR2_CFG_H__
#define _LPDDR2_CFG_H__

typedef struct __lpddr2_clk_timing {
    int tCK_AVG;		/*Average Clock Period*/
    int tCH_AVG;		/*Average high pulse width*/
    int tCL_AVG;		/*Average low pulse width*/
    int tCK_ABS;		/*Absolute Clock Period*/
    int tCH_ABS;		/*Absolute clock HIGH pulse width*/
    int tCL_ABS;		/*Absolute clock LOW pulse width*/
    int tJIT_PER;		/*Clock Period Jitter*/
    int tJIT_CC;		/*Maximum Clock Jitter between two consecutive clock cycles*/
    int tJIT_DUTY;		/*Duty cycle Jitter*/
    int tERR_2PER;		/*Cumulative error across 2 cycles*/
    int tERR_3PER;		/*Cumulative error across 3 cycles*/
    int tERR_4PER;		/*Cumulative error across 4 cycles*/
    int tERR_5PER;		/*Cumulative error across 5 cycles*/
    int tERR_6PER;		/*Cumulative error across 6 cycles*/
    int tERR_7PER;		/*Cumulative error across 7 cycles*/
    int tERR_8PER;		/*Cumulative error across 8 cycles*/
    int tERR_9PER;		/*Cumulative error across 9 cycles*/
    int tERR_10PER;		/*Cumulative error across 10 cycles*/
    int tERR_11PER;		/*Cumulative error across 11 cycles*/
    int tERR_12PER;		/*Cumulative error across 12 cycles*/    
}LPDDR2_CLK_TIMING;

typedef struct __lpddr2_zqcal_timing {
    int tZQINIT;		/*Initialization Calibration Time*/
    int tZQCL;			/*Long Calibration Time*/
    int tZQCS;			/*Short Calibration Time*/
    int tZQRESET;		/*Calibration Reset Time*/
}LPDDR2_ZQCAL_TIMING;

typedef struct __lpddr2_read_timing {
    int tDQSCK;			/*DQS output access time from CK_t/CK_c*/
    int tDQSCKDS;		/*DQSCK Delta Short*/
    int tDQSCKDM;		/*DQSCK Delta Medium*/
    int tDQSCKDL;		/*DQSCK Delta Long*/
    int tDQSQ;			/*DQS - DQ skew*/
    int tQHS;			/*Data hold skew factor*/
    int tQSH;			/*DQS Output High Pulse Width*/
    int tQSL;			/*DQS Output Low Pulse Width*/
    int tQHP;			/*Data Half Period*/
    int tQH;			/*DQ / DQS output hold time from DQS*/
    int tRPRE;			/*Read preamble*/
    int tRPST;			/*Read postamble*/
    int tLZ_DQS;		/*DQS low-Z from clock*/
    int tLZ_DQ;			/*DQ low-Z from clock*/
    int tHZ_DQS;		/*DQS high-Z from clock*/
    int tHZ_DQ;  		/*DQ high-Z from clock*/     
}LPDDR2_READ_TIMING;

typedef struct __lpddr2_write_timing {
    int tDH;			/*DQ and DM input hold time (Vref based)*/
    int tDS;			/*DQ and DM input setup time (Vref based)*/
    int tDIPW;			/*DQ and DM input pulse width*/
    int tDQSS;			/*Write command to 1st DQS latching transition*/
    int tDQSH;			/*DQS input high-level width*/
    int tDQSL;			/*DQS input low-level width*/
    int tDSS;			/*DQS falling edge to CK setup time*/
    int tDSH;			/*DQS falling edge hold time from CK*/
    int tWPST;			/*Write postamble*/
    int tWPRE; 			/*Write preamble*/
}LPDDR2_WRITE_TIMING;

typedef struct __lpddr2_cke_timing {
    int tCKE;			/*CKE min. pulse width (high and low pulse width)*/
    int tISCKE;			/*CKE input setup time*/
    int tIHCKE;			/*CKE input hold time*/
}LPDDR2_CKE_TIMING;

typedef struct __lpddr2_CA_timing {
    int tIS;			/*Address and control input setup time*/
    int tIH;			/*Address and control input hold time*/
    int tIPW;			/*Address and control input pulse width*/
}LPDDR2_CA_TIMING;

typedef struct __lpddr2_boot_timing { /*Boot Parameters 10-55MHz*/
    int tCK_B;
    int tISCKE_B;
    int tIHCKE_B;
    int tIS_B;
    int tIH_B;
    int tDQSCK_B;
    int tDQSQ_B;
    int tQHS_B;
}LPDDR2_BOOT_TIMING;

typedef struct __lpddr2_mr_timing {
    int tMRW;			/*MODE REGISTER Write command period*/
    int tMRR;			/*Mode Register Read command period*/
}LPDDR2_MR_TIMING;

typedef struct __lpddr2_core_timing {
    int tRL;			/*Read Latency*/
    int tWL;			/*Write Latency*/
    int tRC;			/*ACTIVE to ACTIVE command period*/
    int tCKESR;			/*CKE min. pulse width during Self-Refresh*/
    int tXSR;			/*Self refresh exit to next valid command delay*/
    int tXP;			/*Exit power down to next valid command delay*/
    int tCCD_S4;		/*LPDDR2-S4 CAS to CAS delay*/
    int tCCD_S2;		/*LPDDR2-S2 CAS to CAS delay*/
    int tRTP;			/*Internal Read to Precharge command delay*/
    int tRCD;			/*RAS to CAS Delay*/
    int tRP_PB;			/*Row Precharge Time -single bank-*/
    int tRP_AB_4BANK;		/*Row Precharge Time -all 4 bank-*/
    int tRP_AB_8BANK;		/*Row Precharge Time -all 8 bank-*/
    int tRAS;			/*Row Active Time*/
    int tWR;			/*Write Recovery Time*/
    int tWTR;			/*Internal Write to Read Command Delay*/
    int tRRD;			/*Active bank A to Active bank B*/
    int tFAW;			/*Four Bank Activate Window*/
    int tDPD;			/*Minimum Deep Power Down Time*/
}LPDDR2_CORE_TIMING;

typedef struct __lpddr2_jedec_originize {
	unsigned int cs_size;
	int dw;
	int bank;
	int row;
	int column;
}LPDDR2_JEDEC_ORIGINIZE;

#endif

#ifndef __LPDDR3_H__
#define __LPDDR3_H__

typedef struct __lpddr3_clk_timing {
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
}LPDDR3_CLK_TIMING;

typedef struct __lpddr3_zqcal_timing {
    int tZQINIT;		/*Initialization Calibration Time*/
    int tZQCL;			/*Long Calibration Time*/
    int tZQCS;			/*Short Calibration Time*/
    int tZQRESET;		/*Calibration Reset Time*/
}LPDDR3_ZQCAL_TIMING;

typedef struct __lpddr3_read_timing {
    int tDQSCK;			/*DQS output access time from CK_t/CK_c*/
    int tDQSCKDS;		/*DQSCK Delta Short*/
    int tDQSCKDM;		/*DQSCK Delta Medium*/
    int tDQSCKDL;		/*DQSCK Delta Long*/
    int tDQSQ;			/*DQS - DQ skew*/
    int tQSH;			/*DQS Output High Pulse Width*/
    int tQSL;			/*DQS Output Low Pulse Width*/
    int tQH;			/*DQ / DQS output hold time from DQS*/
    int tRPRE;			/*Read preamble*/
    int tRPST;			/*Read postamble*/
    int tLZ_DQS;		/*DQS low-Z from clock*/
    int tLZ_DQ;			/*DQ low-Z from clock*/
    int tHZ_DQS;		/*DQS high-Z from clock*/
    int tHZ_DQ;  		/*DQ high-Z from clock*/     
}LPDDR3_READ_TIMING;

typedef struct __lpddr3_write_timing {
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
}LPDDR3_WRITE_TIMING;

typedef struct __lpddr3_cke_timing {
    int tCKE;			/*CKE min. pulse width (high and low pulse width)*/
    int tISCKE;			/*CKE input setup time*/
    int tIHCKE;			/*CKE input hold time*/
    int tCPDED;			/*Command path disable delay*/
}LPDDR3_CKE_TIMING;

typedef struct __lpddr3_CA_timing {
    int tIS_CA;			/*Address and control input setup time*/
    int tIH_CA;			/*Address and control input hold time*/
    int tIS_CS;			/*Cs input setup time*/
    int tIH_CS;			/*Cs hold time*/
    int tIPW_CA;		/*Address and control input pulse width*/
    int tIPW_CS;		/*Address and control input pulse width*/
}LPDDR3_CA_TIMING;

typedef struct __lpddr3_boot_timing { /*Boot Parameters 10-55MHz*/
    int tCK_B;
    int tISCKE_B;
    int tIHCKE_B;
    int tIS_B;
    int tIH_B;
    int tDQSCK_B;
    int tDQSQ_B;
}LPDDR3_BOOT_TIMING;

typedef struct __lpddr3_mr_timing {
    int tMRW;			/*MODE REGISTER Write command period*/
    int tMRR;			/*Mode Register Read command period*/
    int tMRRI;			/*Additional time after tXP has expired until MRR command may be issued*/
}LPDDR3_MR_TIMING;

typedef struct __lpddr3_core_timing {
    int tRL;			/*Read Latency*/
    int tWL_SETA;		/*Write Latency SET A*/
    int tWL_SETb;		/*Write Latency SET B*/
    int tRC;			/*ACTIVE to ACTIVE command period*/
    int tCKESR;			/*CKE min. pulse width during Self-Refresh*/
    int tXSR;			/*Self refresh exit to next valid command delay*/
    int tXP;			/*Exit power down to next valid command delay*/
    int tCCD;			/*CAS to CAS delay*/
    int tRTP;			/*Internal Read to Precharge command delay*/
    int tRCD_FAST;		/*RAS to CAS Delay*/
    int tRCD_TYP;		/*RAS to CAS Delay*/
    int tRCD_SLOW;		/*RAS to CAS Delay*/
    int tRP_PB_FAST;		/*Row Precharge Time -single bank-*/
    int tRP_PB_TYP;		/*Row Precharge Time -single bank-*/
    int tRP_PB_SLOW;		/*Row Precharge Time -single bank-*/
    int tRP_AB_FAST;		/*Row Precharge Time -all bank-*/
    int tRP_AB_TYP;		/*Row Precharge Time -all bank-*/
    int tRP_AB_SLOW;		/*Row Precharge Time -all bank-*/
    int tRAS;			/*Row Active Time*/
    int tWR;			/*Write Recovery Time*/
    int tWTR;			/*Internal Write to Read Command Delay*/
    int tRRD;			/*Active bank A to Active bank B*/
    int tFAW;			/*Four Bank Activate Window*/
    int tDPD;			/*Minimum Deep Power Down Time*/
}LPDDR3_CORE_TIMING;


typedef struct __lpddr3_odt_timing {
    int tODT_ON;		/*Asynchronous RTT turn-on dely from ODT input*/
    int tODT_OFF;		/*Asynchronous RTT turn-off delay from ODT input*/
    int tAODT_ON;		/*Automatic RTT turn-on delay after READ data*/
    int tAODT_OFF;		/*Automatic RTT turn-off delay after READ data*/
    int tODT_D;			/*RTT disable delay from power down, selfrefresh, and deep power down entry*/
    int tODT_E;			/*RTT enable delay from power down and self refresh exit*/
}LPDDR3_ODT_TIMING;

typedef struct __lpddr3_ca_train_timing {
    int tCAMRD;			/*First CA calibration command after CA calibration mode is programmed*/
    int CAENT;			/*First CA calibration command after CKE is LOW*/
    int tCAEXT;			/*CA caibration exit command after CKE is HIGH*/
    int tCACKEL;		/*CKE LOW after CA calibration mode is programmed*/
    int tCACKEH;		/*CKE HIGH after the last CA calibration results are driven.*/
    int tADR;			/*Data out delay after CA training calibration command is programmed*/
    int tMRZ;			/*MRW CA exit command to DQ tri-state*/
    int tCACD;			/*CA calibration command to CA calibration command delay*/
}LPDDR3_CA_TRAIN_TIMING;

typedef struct __lpddr3_write_level_timing {
    int tWLDQSEN;		/*DQS_t/DQS_c delay after write levelingmode is programmed*/
    int tWLMRD;			/*First DQS_t/DQS_c edge after write leveling mode is programmed*/
    int tWLO;			/*Write leveling output delay*/
    int tWLH;			/*Write leveling hold time*/
    int tWLS;			/*Write leveling setup time*/
    int tMRD;			/*Mode register set command delay*/
}LPDDR3_WRITE_LEVEL_TIMING;

typedef struct __lpddr3_jedec_originize {
	unsigned int cs_size;
	int dw;
	int bank;
	int row;
	int column;
}LPDDR3_JEDEC_ORIGINIZE;

#endif

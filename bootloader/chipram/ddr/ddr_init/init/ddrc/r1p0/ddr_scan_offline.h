#ifndef DDR_SCAN_OFFLINE_H__
#define DDR_SCAN_OFFLINE_H__
#include "ddrc_r1p0.h"
/************************/
/*Chose LPDDR3 & LPDDR4 */
/*0:LPDDR3		*/
/*1:LPDDR4		*/
/************************/
#if (CFG_DRAM_TYPE == DRAM_LPDDR4)
#define DDR_SCAN_LPDDR4
#else
#define DDR_SCAN_LPDDR3
#endif
/*******************************************/
/*Enable & Disable write & read and ca scan*/
/*0:Open Scan CA and Close read & write    */
/*1:Open Scan read & write and  CA         */
/*******************************************/
#if 1
#define DDR_SCAN_WRITE
#define DDR_SCAN_READ
//#define DDR_SCAN_CA
#else
#define DDR_SCAN_CA
#endif
/***********************************/
/*Enable & Disable VDD LOOP        */
/*0:Close VDDQ&VDDCORE Set for scan*/
/*1:Open  VDDQ&VDDCORE Set for scan*/
/***********************************/
#if 0
#define DDR_SCAN_CONTAIN_VDD_LOOP
#endif
/****************************************/
/*Choose Differential Mode or CMOS Mode */
/*Only use for ddr scan                 */
/*CMOS Mode        : 1                  */
/*Differential Mode: 0                  */
/****************************************/
#if 0
#define DDR_SCAN_CMOS_MODE
#endif
/***********************************************/
/*Enable & Disable Dump Rd Register            */
/*Must open DDR_SCAN_CONTAIN_VDD_LOOP can valid*/
/*Enable  Dump       : 1                       */
/*Disable Dump       : 0                       */
/***********************************************/
#if 1
#define DDR_SCAN_DUMP_RD_REG_ENABLE
#endif
/****************************************/
/*RANK choise                           */
/*1:Scan rank0 &rank1			*/
/*0"Only scan rank0			*/
/****************************************/
#if 1
#define DDR_SCAN_DUAL_RANK
#endif
/****************************************/
/*DDR Scan some per stap                */
/****************************************/
/*X axis increase step*/
#define X_INCREASE_STEP 1
/*Vddq decrease step*/
#define VDDQ_PER_STEP 50
/*VddCore decrease step*/
#define VDDCORE_PER_STEP 50
/***************************************/
/*DDR Scan vddq and vddcore max value*/
/***************************************/
#define VDDQ_MAX   1300
#define VDDQ_MIN   1100
#define VDDCORE_MAX 1000
#define VDDCORE_MIN 750
/****************************************/
/*Open print through line and Training
**in  eye log  				*/
/****************************************/
//#define DDR_SCAN_PRINT_THROUGH_LINE

/*LOG Format*/
//#define LOG_FORMAT_VREF
/*ROM Format*/
#define ROM_START_ADDRESS 0x800000   //ROM address start
#define ROM_END_ADDRESS   0x0000FFFFF
/************************************************/
/*1:Open use for three bist pattern for scan    */
/*  Must be set (bist.c) bist pattern for       */
/*  global variable	:scan_bist_pattern	*/
/*  ex:bist_info.bist_pattern=scan_bist_pattern */
/*0:Only use for one bist pattern for scan      */
/************************************************/
#if 1
#define DDR_SCAN_LOOP_ALL_BIST_PATTERN
#endif
/****************************************/
/*Write & read & CA Scan Scope          */
/****************************************/
/*Write*/
#define PHY_VREFE_ADDRESS 0x402b00d0
#ifdef DDR_SCAN_LPDDR3
#define VREFE_DAC_MAX 0xff
#define VREFE_DAC_MIN 0x90
#else
#define VREFE_DAC_MAX 0x72
#define VREFE_DAC_MIN 0x00
#endif
/*Read*/
#define VREFI_DAC_MAX 0x7f   //default:0xff
#define VREFI_DAC_MIN 0x00
#define VREFI_OP_MAX  0x7f
#define VREFI_OP_MIN  0x00
/*CA*/
#ifdef DDR_SCAN_LPDDR4
#define CA_SCAN_MAX 0x72    /*LPDDR4X*/
#define CA_SCAN_MIN 0x00
#else
#define CA_SCAN_MAX 0xff	/*LPDDR3*/
#define CA_SCAN_MIN 0x90
#endif

#define PD_PUB_SYS_CFG                                          (PMU_APB_BASE_ADDR+0x005c)
#define PWR_STATUS2_DBG                                         (PMU_APB_BASE_ADDR+0x00c4)
//ZQ Calibration Register
#define PUPD_PHY0_IOPVT_CALIBRATION_RESULT 			(DMC_GUCPHY0_BASE+0x394)
#define PUPD_PHY1_IOPVT_CALIBRATION_RESULT 			(DMC_GUCPHY1_BASE+0x394)
//DUMP Rd only register offset start&end
#define RD_ONLY_OFFSET_START 0x358
#define RD_ONLY_OFFSET_END   0x42C

//mr_write
#define CANDS_CTL_REG_BASE      0X30000000
#define CANDS_CTL0_(i) (CANDS_CTL_REG_BASE + i*4)

//eye width
#define eye_open_value(step_value)  (((step_value)*(1000000/(ddr_sck[freq_sel]*2)))/255)
//Training Start in Scan eye
#define TRAINGING_EYE_START_VALUE(center,width) ((2*(center)-(width))/2)
//Training End in Scan eye
#define TRAINGING_EYE_END_VALUE(center,width) (((width)+2*(center))/2)
struct ca_result{
	u32 vref_dram_ca_result;
	u32 ca_pass_window;
	u32 ca_result_cfg_fine;
	u32 ca_result_cfg_coarse;
	u32 ca_eye_window_start;
	u32 ca_eye_window_end;
};

struct read_result{
	u32 deye_vref_db0_result;
//	u32 deye_vref_db1_result;
	u32 rd_db0_dqsn;
	u32 rd_db1_dqsn;
	u32 rd_db0_dqs;
	u32 rd_db1_dqs;
	u32 db0_rdq_pass_window;
	u32 db1_rdq_pass_window;
	u32 rd_db0_eye_window_start;
	u32 rd_db0_eye_window_end;
	u32 rd_db1_eye_window_start;
	u32 rd_db1_eye_window_end;
};

struct write_result{
	u32 vref_dram_adj_result;
	u32 db0_wdq_bt_result;
	u32 db1_wdq_bt_result;
	u32 db0_wdq_result;
	u32 db1_wdq_result;
	u32 db0_wdq_pass_window;
	u32 db1_wdq_pass_window;
	u32 wr_db0_eye_window_start;
	u32 wr_db0_eye_window_end;
	u32 wr_db1_eye_window_start;
	u32 wr_db1_eye_window_end;
};

typedef enum
{
  scan_write=0,scan_read=1,scan_ca=2
}scan_type;
typedef enum
{
  data_module_0=0,data_module_1=1,no_modeule=2
}data_mode;

typedef struct //read write Parameter
{
   u64 dmc_phy_base;     //PHY0 or PHY1
   u32 scan_num;         //Scan num use for loop
   data_mode data_module;//data module 0 or data module 1
   scan_type type;       //Scan type(write read and CA)
}scan_type_parameter;

/****use for SCAN CA :ROM***/
typedef struct
{
  u32 ca_scan_flag;
  u32 phy_num;
  u32 delay_num;
  u32 PHY_BASE;
}rom_store_area;


/*store bese delay parameter use for scan ca*/
typedef struct
{
   u32 best_delay;
   u32 best_vref;
   u32 best_width;
   u32 eye_width;
}best_value;

typedef struct
{
  	best_value Phy0_databyte0;
	best_value Phy0_databyte1;
	best_value Phy1_databyte0;
	best_value Phy1_databyte1;
}best_para;
/***VREF parameter**/
typedef struct
{
   u32 max_value;
   u32 min_value;
   u32 vref_address;
}vref_mes;
typedef struct
{
	u32 pass_flag;
	u32 fail_flag;
	u32 scan_vref;
	u32 train_vref;
	u32 train_dqs;
	u32 eye_start;
	u32 eye_end;

	scan_type type;       //Scan type(write read and CA)

}PRINT_BIST_PARA;

typedef struct   	/*use for store rom value*/
{
  u32 rom_start_flag;    /*use for Distinguish first start*/
  u32 vref_lv;           /*Store CA Scan Vref*/
  u32 old_vref_lv;       /*Use for print vref log*/
  u32 scan_x;            /*Bist x Axis*/
  u32 phy_num;           /*use for store phy num */
  u32 old_phy_num;       /*use for print phy log*/
                         /*use for print boundary*/
  u32 first_pass;		 /*store first get pass position*/
  u32 last_pass;         /*store last get pass position*/
  u32 center_pass;
  u32 window_fail_flag;  /*Detect window to small*/

  u32 read_write_end_flag; /*Avoid repeat call read & write function in scan ca*/

  struct ca_result	    ca_phy0_result; //sotre training result
  struct ca_result	    ca_phy1_result;

  best_para ca_best_para; //store best scan parameter

  u32 new_vddq;//use for vdd scan
  u32 old_vddq;
  u32 new_vddcore;
  u32 old_vddcore;
  u32 print_vddq_training_flag;
  u32 print_vddcore_training_flag;
  /*use for dual rank*/
  u32 rank_loop_num; /*Control rank Switch*/
  u32 SwitchRankTrainingFlag;/*Determine whether to execute Training(_start) flag*/
  u32 RankTrainingPrintFlag;/*Control print one time training result*/
  /*use for ddr_offline_scan_parameter */
  PRINT_BIST_PARA print_bist_para;

}rom_value;
/**DDR_SCAN_DUAL_RANK***/
/*LPDDR4X*/
typedef struct
{
	u32 interleave_mode;
	u32 linear_0;
	u32 linear_1;
	u32 interleave_base;
	uint64 bist_start;
}RankConfigure;
RankConfigure rank_configure[2]={
	{1,0x00,0x00,0x00,0x00},	/*CH0-CS0&CH1-CS0*/
	{1,0x00,0x00,0x00,0x60000000}     /*CH1-CS1&CH1-CS1*/
};
/*LPDDR3*/
uint64 rank_bist_addr[]={0x00,0x40000000};
/*******/
#ifndef DDR_SCAN_LPDDR4
const scan_type_parameter phy_scan_para_wr[]={
		{DMC_GUCPHY0_BASE,0xff,data_module_0,scan_write},
		{DMC_GUCPHY0_BASE,0xff,data_module_1,scan_write},
		{DMC_GUCPHY1_BASE,0xff,data_module_0,scan_write},
		{DMC_GUCPHY1_BASE,0xff,data_module_1,scan_write}
					};
#else
const scan_type_parameter phy_scan_para_wr[]={
		{DMC_GUCPHY0_BASE,0x1ff,data_module_0,scan_write},
		{DMC_GUCPHY0_BASE,0x1ff,data_module_1,scan_write},
		{DMC_GUCPHY1_BASE,0x1ff,data_module_0,scan_write},
		{DMC_GUCPHY1_BASE,0x1ff,data_module_1,scan_write}
					};
#endif
const scan_type_parameter phy_scan_para_rd[]={
		{DMC_GUCPHY0_BASE,0xff,data_module_0,scan_read},
		{DMC_GUCPHY0_BASE,0xff,data_module_1,scan_read},
		{DMC_GUCPHY1_BASE,0xff,data_module_0,scan_read},
		{DMC_GUCPHY1_BASE,0xff,data_module_1,scan_read}
                                    };
const scan_type_parameter phy_scan_para_ca[]={        //0xfff
#ifdef DDR_SCAN_LPDDR4
	{ DMC_GUCPHY0_BASE, 0x2ff, no_modeule, scan_ca }
#else
	{ DMC_GUCPHY0_BASE, 0xff, no_modeule, scan_ca }
#endif
};

/*use set vrefi value address offset for scan read*/
const u32 vrefi_offset[]={0x40,0x90,0xE0,0x130,0x180,0x1d0,0x220,0x270};
/*clk*/
const u32 ddr_sck[]={160,233,311,400,533,622,800,933};

#endif

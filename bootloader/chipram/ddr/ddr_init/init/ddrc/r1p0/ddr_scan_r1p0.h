#ifndef DDR_SCAN_R1P0_H__
#define DDR_SCAN_R1P0_H__

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
#define DDR_SCAN_WRITE
#define DDR_SCAN_READ
#define DDR_SCAN_CA

/*Open DRIVER_STRENGTH */
#define DRIVER_STRENGTH
/***********************************************/
/*Enable & Disable VREF SCAN           */
/*Enable  Dump       : 1                       */
/*Disable Dump       : 0                       */
/***********************************************/
#if 1
#define DDR_SCAN_VREF_ENABLE
#endif
/****************************************/
/*DDR Scan some per stap                */
/****************************************/
/*X axis increase step*/
#ifdef DDR_SCAN_LPDDR4
#define X_INCREASE_STEP 4
#else
#define X_INCREASE_STEP 2
#endif
/*WRITE VREF decrease step*/
#define WRITE_VREF_STEP 1
/*Read VREF decrease step*/
#define READ_VREF_STEP  1
/*CA VREF decrease step*/
#define CA_VREF_STEP 1

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
/*Open print through line in  eye log  */
/****************************************/
#define DDR_SCAN_PRINT_THROUGH_LINE

/*LOG Format*/
//#define LOG_FORMAT_VREF
/*ROM Format*/
#define ROM_START_ADDRESS 0x800000   //ROM address start
#define ROM_END_ADDRESS   0x0000FFFFF


#ifdef DDR_SCAN_LPDDR3
#define DRIVER_STRENGTH_DIFFERENCE 1
#else
#define DRIVER_STRENGTH_DIFFERENCE 4
#endif
/****************************************/
/*Write & read & CA Scan Scope          */
/****************************************/
/*Write*/
#define PHY_VREFE_ADDRESS 0x402b00d0
#ifdef DDR_SCAN_LPDDR3
#define VREFE_DAC_MAX 0xd9
#define VREFE_DAC_MIN 0xc7
#else
#define VREFE_DAC_MAX 0x59//0x72    0x50-0x9 ~ 0x50+0x9
#define VREFE_DAC_MIN 0x47//0x00
#endif
/*Read*/
#define VREFI_DAC_MAX 0xd9   //default:0xff
#define VREFI_DAC_MIN 0xc7
/*CA*/
#ifdef DDR_SCAN_LPDDR4
#define CA_SCAN_MAX 0x67    /*LPDDR4X 0x5e-0x9 ~ 0x5e+0x9*/
#define CA_SCAN_MIN 0x55
#else
#define CA_SCAN_MAX 0xd9	/*LPDDR3*/
#define CA_SCAN_MIN 0xc7
#endif

#define PD_PUB_SYS_CFG		(PMU_APB_BASE_ADDR+0x005c)
#define PWR_STATUS2_DBG		(PMU_APB_BASE_ADDR+0x00c4)
//ZQ Calibration Register
#define PUPD_PHY0_IOPVT_CALIBRATION_RESULT	(DMC_GUCPHY0_BASE+0x394)
#define PUPD_PHY1_IOPVT_CALIBRATION_RESULT	(DMC_GUCPHY1_BASE+0x394)
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
/*User scan print */
#define SCAN_ROW1_SYMBOL 0xc1000000
#define SCAN_ROW2_SYMBOL 0xc2000000
#define SCAN_ROW3_SYMBOL 0xc3000000
#define SCAN_ROW4_SYMBOL 0xc4000000
#define SCAN_ROW5_SYMBOL 0xc5000000
#define SCAN_COLUMN1_SYMBOL 0xb1000000
#define SCAN_COLUMN2_SYMBOL 0xb2000000
#define SCAN_COLUMN3_SYMBOL 0xb3000000
#define SCAN_COLUMN4_SYMBOL 0xb4000000

typedef enum __SCAN_IMTE_CODE {
	SCAN_ITEM_BYTE= 0 ,
	SCAN_ITEM_VREF,
	SCAN_ITEM_VREF1,  	/*lp4:ca*/
	SCAN_ITEM_VREF2,	/*lp4:write*/
	SCAN_ITEM_PHY,
	SCAN_ITEM_DS,
	SCAN_ITEM_CA_DL,
	SCAN_ITEM_WR_DL,
	SCAN_ITEM_RD_DL,

}SCAN_ITEM_CODE;
typedef enum __DRIVER_STRENGTH_VALUE{
#ifdef DDR_SCAN_LPDDR3
	DRIVER_STRENGTH_34=0x01,
	DRIVER_STRENGTH_40=0x02,
	DRIVER_STRENGTH_48=0x03
#else
	DRIVER_STRENGTH_60=0x04,
	DRIVER_STRENGTH_48=0x05,
	DRIVER_STRENGTH_40=0x06
#endif
}DRIVER_STRENGTH_VALUE;
#define SCAN_ITEM_OFFSET	8
struct ca_result
{
	u32 vref_dram_ca_result;
	u32 ca_pass_window;
	u32 ca_result_cfg_fine;
	u32 ca_result_cfg_coarse;
	u32 ca_eye_window_start;
	u32 ca_eye_window_end;
};

struct read_result
{
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

struct write_result
{
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
	scan_write = 0, scan_read = 1, scan_ca = 2
}scan_type;
typedef enum
{
	data_module_0 = 0, data_module_1 = 1, no_modeule = 2
}data_mode;

typedef struct //read ¡¢write Parameter
{
	u64 dmc_phy_base;     //PHY0 or PHY1
	u32 scan_num;         //Scan num use for loop
	data_mode data_module; //data module 0 or data module 1
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
typedef struct   /*use for store rom value*/
{
	u32 rom_start_flag;    /*use for Distinguish first start*/
	int vref_lv;           /*Store CA Scan Vref*/
	u32 old_vref_lv;       /*Use for print vref log*/
	u32 scan_x;            /*Bist x Axis*/
	u32 phy_num;           /*use for store phy num */
	u32 old_phy_num;       /*use for print phy log*/
	/*use for print boundary*/
	u32 first_pass;        /*store first get pass position*/
	u32 last_pass;         /*store last get pass position*/
	u32 center_pass;
	u32 pass_flag;
	u32 fail_flag;

	u32 window_fail_flag;  /*Detect window to small*/

	u32 read_write_end_flag; /*Avoid repeat call read & write function in scan ca*/

	struct ca_result	    ca_phy0_result; //sotre training result
	struct ca_result	    ca_phy1_result;

	best_para ca_best_para; //store best scan parameter

	DRIVER_STRENGTH_VALUE driver_strength; //use for driver strength
	DRIVER_STRENGTH_VALUE old_driver_strength;

	u32 print_vddq_training_flag;
	u32 print_vddcore_training_flag;

	//use for auto detect scan vref based on Training vref
	u32 scan_write_vref_max;
	u32 scan_write_vref_min;
	u32 scan_read_vref_max;
	u32 scan_read_vref_min;
	u32 scan_ca_vref_max;
	u32 scan_ca_vref_min;
}rom_value;

/*Driver strength---only for print*/
#ifdef DDR_SCAN_LPDDR3
const int driver_strength[]={
	34,40,48
};
#else
const int driver_strength[]={
	60,48,40
};
#endif

static const scan_type_parameter phy_scan_para_wr_lp3[]=   /*LP3*/
{
	{DMC_GUCPHY0_BASE,0xff,data_module_0,scan_write},
	{DMC_GUCPHY0_BASE,0xff,data_module_1,scan_write},
	{DMC_GUCPHY1_BASE,0xff,data_module_0,scan_write},
	{DMC_GUCPHY1_BASE,0xff,data_module_1,scan_write}
};
static const scan_type_parameter phy_scan_para_wr_lp4[] = {/*LP4*/
	{ DMC_GUCPHY0_BASE, 0x1ff, data_module_0, scan_write },
	{ DMC_GUCPHY0_BASE, 0x1ff, data_module_1, scan_write },
	{ DMC_GUCPHY1_BASE, 0x1ff, data_module_0, scan_write },
	{ DMC_GUCPHY1_BASE, 0x1ff, data_module_1, scan_write }
};

static const scan_type_parameter phy_scan_para_rd[] = {
	{ DMC_GUCPHY0_BASE, 0xff, data_module_0, scan_read },
	{ DMC_GUCPHY0_BASE, 0xff, data_module_1, scan_read },
	{ DMC_GUCPHY1_BASE, 0xff, data_module_0, scan_read },
	{ DMC_GUCPHY1_BASE, 0xff, data_module_1, scan_read }
};
static const scan_type_parameter phy_scan_para_ca_lp3[] = {        //0xfff

	{ DMC_GUCPHY0_BASE, 0xff, no_modeule, scan_ca }

};
static const scan_type_parameter phy_scan_para_ca_lp4[] = {        //0x2ff

	{ DMC_GUCPHY0_BASE, 0x1ff, no_modeule, scan_ca }


};
/*use set vrefi value address offset for scan read*/
static const u32 vrefi_offset[] = { 0x40, 0x90, 0xE0, 0x130, 0x180, 0x1d0, 0x220, 0x270 };
/*clk*/
static const u32 ddr_sck[] = { 160, 233, 311, 400, 533, 622, 800, 933 };
#endif

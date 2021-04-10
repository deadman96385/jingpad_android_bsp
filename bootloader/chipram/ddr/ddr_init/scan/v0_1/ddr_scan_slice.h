

#define NULL 0


typedef unsigned char   	uint8;
typedef unsigned short 	uint16;

#define SCAN_SLICE

#define public

#define ENCRPTY_LOG        0
#define PARAM_INFO_LOG   1
#define DEBUG_SCAN     	1

//#define BYPASS_MODE


#define RDDQ_EN    0
#define CA_EN    0

//#define DEFAULT_VALUE

#define SLICEX				0x00
#define DQZ					0x01
#define CHANNEL  			0x02
#define SLEW_RATE   			0x03
#define DRIVE_STRENGTH 	0x04
#define RDDQS_DLL       		0x05
#define WRDQS_DLL     		0x06
#define RLCDL_DLL 	 		0x07
#define WLCDL_DLL       		0x08
#define RDDQ_DLL      		0x09
#define WRDQ_DLL        		0x0a
#define CA_DLL		    		0x0b
#define RDDQS_RISE_DLL  	0x0c
#define RDDQS_FALL_DLL  	0x0d
#define DQ_VREF_PHY     		0x0e
#define CA_VREF_PHY			0x0f
#define DQ_VREF_DEVICE        0x10
#define CA_VREF_DEVICE	      0x11
#define WR_BYPASS_DLL			0x12
#define RDDQS_BYPASS_DLL		0x13

typedef enum
{
	MRW_SINGLE = 0,
	MRW_M16_M17 = 1,
	MRW_M0_M1_M2_M3_M11 = 2,
}MRW_TYPE_E;

typedef enum
{
	MRW_CS0 = 0,
	MRW_CS1 = 1,
	MRW_ALL_CS =2,
}MRW_CS_E;

typedef enum 
{
	SLEW_RATE0 = 0x7,
	SLEW_RATE1 = 0x5,
	SLEW_RATE2 = 0x3,
	//SLEW_RATE3 = 0x1,
}DS_SLEW_E;


void whale2_ddr_scan(uint32 ddr_clk);






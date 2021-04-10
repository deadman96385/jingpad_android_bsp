

#define NULL 0


typedef unsigned char   	uint8;
typedef unsigned short 	uint16;

//#define SCAN_SLICE

#define public

//#define ENCRPTY_LOG

//#define SIPI_BIST

typedef enum
{
	SLICEX=0x0,
	DQZ=0x1,
	CHANNEL=0x2,
	SLEW_RATE=0x3,
	DRIVE_STRENGTH=0x4,
	RDDQS_DLL=0x5,
	WRDQS_DLL=0x6,
	RLCDL_DLL=0x7,
	WLCDL_DLL=0x8,
	RDDQ_DLL=0x9,
	WRDQ_DLL=0xa,
	CA_DLL=0xb,
	RDDQS_RISE_DLL=0xc,
	RDDQS_FALL_DLL=0xd,
	DQ_VREF_PHY=0xe,
	CA_VREF_PHY=0xf,
	DQ_VREF_DEVICE=0x10,
	CA_VREF_DEVICE=0x11,
	WR_BYPASS_DLL=0x12,
	RDDQS_BYPASS_DLL=0x13
}SCAN_TYPE_E;

typedef enum
{
	SET_MODE=0,
	RESET_MODE=1

}DLL_MODE_E;



typedef enum
{
	NORMAL_MODE=0,
	BYPASS_MODE=1

}FREQ_MODE_E;


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
	SLEW_RATE0 = 0xf,
	SLEW_RATE1 = 0x5,
	SLEW_RATE2 = 0x3,
	//SLEW_RATE3 = 0x1,
}DS_SLEW_E;

typedef enum
{
	DRAM_8Gb =0x8,
	DRAM_12Gb =0x12,
	DRAM_16Gb = 0x16,
	DRAM_24Gb = 0x24,
	DRAM_32Gb = 0x32

}DDR_SIZE_E;


void ddr_scan(uint32 ddr_clk,uint32 scan_cs_num,uint32 type);






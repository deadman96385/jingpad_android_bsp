
/*************Memory Auto Detect***************/
#ifndef __DDRC_SPRD_R1P0_AUTO_DETECT_H__
#define __DDRC_SPRD_R1P0_AUTO_DETECT_H__
typedef enum __DDR_UNSYMMETRY_MODE {
	DDR_6Gb_10_COL_MODE,
	DDR_6Gb_11_COL_MODE,
	DDR_12Gb_MODE
}DDR_UNSYMMETRY_MODE;

typedef struct __lpddr_jedec_originize {
	u32 cs_size;
	int dw;
	int bank;
	int row;
	int column;
}LPDDR_JEDEC_ORIGINIZE;

typedef enum
{
	S16_SDRAM_LP4 = 0,
	S16_SDRAM_LP4X = 2,
	S16_SDRAM_LP4Y = 3
}DDR_TYPE_E;

typedef enum
{
	MR8_SIZE_64Mb = 0,
	MR8_SIZE_128Mb = 1,
	MR8_SIZE_256Mb = 2,
	MR8_SIZE_512Mb = 3,
	MR8_SIZE_1Gb  =  4,
	MR8_SIZE_2Gb  =  5,
	MR8_SIZE_4Gb  =  6,
	MR8_SIZE_8Gb  =  7,
	MR8_SIZE_16Gb =  8,
	MR8_SIZE_32Gb =  9,
	MR8_SIZE_6Gb  =  14,
	MR8_SIZE_12Gb =  13
}MR8_DDR_SIZE_E;

typedef enum
{
	LP4_MR8_SIZE_2Gb  =  0,
	LP4_MR8_SIZE_3Gb  =  1,
	LP4_MR8_SIZE_4Gb  =  2,
	LP4_MR8_SIZE_6Gb =  3,
	LP4_MR8_SIZE_8Gb =  4,
	LP4_MR8_SIZE_12Gb =  5,
	LP4_MR8_SIZE_16Gb =  6,
}LP4_MR8_DDR_SIZE_E;

typedef enum
{
	LP4_WIDTH_X16 = 0,
	LP4_WIDTH_X8 = 1
}LP4_DDR_WIDTH_E;

typedef enum
{
	WIDTH_X32 = 0,
	WIDTH_X16 = 1,
	WIDTH_X8 = 2
}DDR_WIDTH_E;

struct MR8_size_info
{
	uint32 mr8_size;
	uint64 mem_size;
};

struct ddr_detect_info
{
	uint64 mem_size;
	uint32 mem_width;
	uint32 mem_type;
	uint32 bank;
};

typedef struct
{
    uint32 v_min;
    uint32 v_max;
    uint32 ddr_type;
    uint32 ddr_pinmux_c;
}DDR_TYPE_ADC_DETECT;

struct ddr_type_t
{
	char gpio_1_value;
	char gpio_0_value;
	char ddr_type;
	char ddr_pinmux_c;
};

typedef struct
{
	u8	reg_val_mr5;
	u8	reg_val_mr6;
	u8	reg_val_mr7;
	u8	reg_val_mr8;
}MR_DEVICE_INFO;
typedef struct mr_auto_freq_sel
{
	MR_DEVICE_INFO mr_devices_info[2];
	u32	ddr_cs_num;
	u32	ddr_clk_sel;
}MR_AUTO_FREQ_SEL;
#define CFG_UNSYMMETRY_DRAM_MODE	DDR_6Gb_10_COL_MODE
#endif

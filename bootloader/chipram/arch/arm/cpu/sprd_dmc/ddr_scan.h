/******************************************************************************
 ** File Name:      sc8825_emc_cfg.h                                          *
 ** Author:         Johnny.Wang                                               *
 ** DATE:           2012/12/04                                                *
 ** Copyright:      2005 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:                                                              *
 ******************************************************************************/
#include <sci_types.h>
/* delete sc_reg_h */


typedef enum
{
	SCAN_STEP_MIN  = 0,
	SCAN_STEP_SUB3 = 0,
	SCAN_STEP_SUB2 = 1,
	SCAN_STEP_SUB1 = 2,
	SCAN_STEP_NOM  = 3,
	SCAN_STEP_DEF  = 3,
	SCAN_STEP_ADD1 = 4,
	SCAN_STEP_ADD2 = 5,
	SCAN_STEP_ADD3 = 6,
	SCAN_STEP_ADD4 = 7,
	SCAN_STEP_MAX  = 7
}SCAN_STEP_E;

typedef enum
{
	SCAN_PHS_MIN = 0,
	SCAN_PHS_DEF = 2,
	SCAN_PHS_36  = 0,
	SCAN_PHS_54  = 1,
	SCAN_PHS_72  = 2,
	SCAN_PHS_90  = 3,
	SCAN_PHS_108 = 4,
	SCAN_PHS_126 = 5,
	SCAN_PHS_144 = 6,
	SCAN_PHS_MAX = 6
}SCAN_PHS_E;

typedef enum
{
	SCAN_FAIL = 0,
	SCAN_PASS = 1
}SCAN_RESULT_E;

typedef enum
{
	DXN_MIN = 0,
	DXN0 = 0,
	DXN1 = 1,
	DXN2 = 2,
	DXN3 = 3,
	DXN_MAX = 4
}DXN_E;


typedef enum
{
	DRAM_0BIT       = 0,
	DRAM_64MBIT		= 0x00800000,
	DRAM_128MBIT    = 0x01000000,
	DRAM_256MBIT    = 0x02000000,
	DRAM_512MBIT    = 0x04000000,
	DRAM_1GBIT      = 0x08000000,
	DRAM_2GBIT      = 0x10000000,
	DRAM_4GBIT      = 0x20000000,
	DRAM_8GBIT      = 0x40000000,
	DRAM_16GBIT     = 0x80000000,
}DRAM_DENSITY_E;

#define SCAN_LEN ((SCAN_STEP_MAX+1)*(SCAN_PHS_MAX+1))


/******************************************************************************
 ** File Name:      sc8825_emc_cfg.h                                          *
 ** Author:         Johnny.Wang                                               *
 ** DATE:           2012/12/04                                                *
 ** Copyright:      2005 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:                                                              *
 ******************************************************************************/
#include <sci_types.h>
/* delete sc_reg_h */


#define DDR_SCAN_WLCDL_SUPPROT
#define DDR_SCAN_RLCDL_SUPPROT

//#define DDR_SCAN_WBDLL_SUPPROT
//#define DDR_SCAN_RBDLL_SUPPROT
#define DDR_SCAN_ACDDL_SUPPORT

/******************************************/
typedef struct
{
	uint16 puint16;
	void * pnull;
}pstruct_t;

typedef enum
{
	BIST_TYPE_BYTE = 0,
	BIST_TYPE_BIT  = 1,
	BIST_TYPE_AC   = 2
}BIST_TYPE_E;

typedef enum
{
	BIST_DS_34OHM = 0,
	BIST_DS_40OHM = 1,
	BIST_DS_48OHM = 2,
	BIST_DS_60OHM = 3,
	BIST_DS_80OHM = 4
}BIST_DS_E;

typedef enum
{
	//AD LCDL&BDL
	DLL_TYPE_AC_LCDL      = 0X000,
	DLL_TYPE_AC_CKBDLL    = 0X001,
	DLL_TYPE_AC_RASBDLL   = 0X002,
	DLL_TYPE_AC_CASBDLL   = 0X003,
	DLL_TYPE_AC_WEBDLL    = 0X004,
	DLL_TYPE_AC_PARBDLL   = 0X005,
	DLL_TYPE_AC_BABDLL    = 0X006,
	DLL_TYPE_AC_PDDBDLL   = 0X007,
	DLL_TYPE_AC_CSBDLL	  = 0X008,
	DLL_TYPE_AC_ODTBDLL	  = 0X009,
	DLL_TYPE_AC_CKEBDLL	  = 0X00A,
	DLL_TYPE_AC_ADDBDLL	  = 0X00B,
	//WRITE BDL
	DLL_TYPE_DX_DQWBDLL   = 0X010,
	DLL_TYPE_DX_DMWBDLL   = 0X011,
	DLL_TYPE_DX_DQSWBDLL  = 0X012,
	DLL_TYPE_DX_OEBDLL    = 0X013,
	//READ BDL
	DLL_TYPE_DX_RBDLL     = 0X100,
	DLL_TYPE_DX_DMRBDLL   = 0X101,
	DLL_TYPE_DX_DQSRBDLL  = 0X102,
	DLL_TYPE_DX_DQSNRBDLL = 0X103,
	DLL_TYPE_DX_PDDBDLL   = 0X104,
	DLL_TYPE_DX_PDRBDLL   = 0X105,
	DLL_TYPE_DX_TERBDLL   = 0X106,
	//DATA LCDL
	DLL_TYPE_DX_WDQDLCDL  = 0X200,
	DLL_TYPE_DX_RDQSLCDL  = 0X201,
	DLL_TYPE_DX_RDQSNLCDL = 0X202
}DLL_TYPE_E;




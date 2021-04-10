/******************************************************************************
 ** File Name:    common.h                                                    *
 ** Author:       Daniel.Ding                                                 *
 ** DATE:         3/9/2005                                                    *
 ** Copyright:    2005 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 9/1/2003      Daniel.Ding     Create.                                     *
 ******************************************************************************/
#ifndef _COMMON_H_
#define _COMMON_H_
/*----------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **-------------------------------------------------------------------------- */

#include "stdarg.h"
#include "linux/string.h"
#include <linux/types.h>
#include "sprd_debug.h"

/**---------------------------------------------------------------------------*
 **                             Compiler Flag                                 *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif
/**----------------------------------------------------------------------------*
**                               Micro Define                                 **
**----------------------------------------------------------------------------*/
#define	LOCAL		static
#define PUBLIC
#define TRUE   1   /* Boolean true value. */
#define FALSE  0   /* Boolean false value. */


/*
    Bit define
*/
#define BIT_0               0x00000001
#define BIT_1               0x00000002
#define BIT_2               0x00000004
#define BIT_3               0x00000008
#define BIT_4               0x00000010
#define BIT_5               0x00000020
#define BIT_6               0x00000040
#define BIT_7               0x00000080
#define BIT_8               0x00000100
#define BIT_9               0x00000200
#define BIT_10              0x00000400
#define BIT_11              0x00000800
#define BIT_12              0x00001000
#define BIT_13              0x00002000
#define BIT_14              0x00004000
#define BIT_15              0x00008000
#define BIT_16              0x00010000
#define BIT_17              0x00020000
#define BIT_18              0x00040000
#define BIT_19              0x00080000
#define BIT_20              0x00100000
#define BIT_21              0x00200000
#define BIT_22              0x00400000
#define BIT_23              0x00800000
#define BIT_24              0x01000000
#define BIT_25              0x02000000
#define BIT_26              0x04000000
#define BIT_27              0x08000000
#define BIT_28              0x10000000
#define BIT_29              0x20000000
#define BIT_30              0x40000000
#define BIT_31              0x80000000

#define REG32(x)                                    (*((volatile uint32_t *)(x)))


#define REG8(ChipReg)  ( *((volatile u8*) (ChipReg)))
#define CHIP_REG_OR(reg_addr, value)    (*(volatile u32 *)(reg_addr) |= (u32)(value))
#define CHIP_REG_AND(reg_addr, value)   (*(volatile u32 *)(reg_addr) &= (u32)(value))
#define CHIP_REG_GET(reg_addr)          (*(volatile u32 *)(reg_addr))
#define CHIP_REG_SET(reg_addr, value)   (*(volatile u32 *)(reg_addr)  = (u32)(value))


typedef enum{
TYPE_RESET = 0,           //bit[4:0]
TYPE_BACKLIGHT,         //bit[5]
TYPE_DSPEXCEPTION,  //bit[6]
TYPE_USB,                    //bit[7]
TYPE_MAX
}WDG_HW_FLAG_T;

typedef enum{
TDPLL_REF0 = 0,
TDPLL_REF1,
TDPLL_MAX,
}TDPLL_REF_T;

/**----------------------------------------------------------------------------*
**                             Data Prototype                                 **
**----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------*
**                         Local Function Prototype                           **
**----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------*
**                           Function Prototype                               **
**----------------------------------------------------------------------------*/

/**----------------------------------------------------------------------------*
**                         Compiler Flag                                      **
**----------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
/**---------------------------------------------------------------------------*/
#endif
// End


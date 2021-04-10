/******************************************************************************
 ** File Name:      pinmap.h                                                  *
 ** Author:         Richard.Yang                                              *
 ** DATE:           03/08/2004                                                *
 ** Copyright:      2004 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the structure of pin map.               *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 03/08/2004     Richard.Yang     Create.                                   *
 ******************************************************************************/

#ifndef _PINMAP_H_
#define _PINMAP_H_

#include <sci_types.h>
#include "sprd_reg.h"

typedef struct {
	uint32_t reg;
	uint32_t val;
} pinmap_t;

#define REG_PIN_GPIO87                   ( 0x02bc )
#define REG_PIN_GPIO141                   ( 0x0154 )

/* bits definitions for register REG_PIN_XXX */
#define BIT_PIN_SLP_AP                  ( BIT_13 )
#define BIT_PIN_SLP_CP0                 ( BIT_14 )
#define BIT_PIN_SLP_CP1                 ( BIT_15 )
#define BIT_PIN_SLP_CP2                 ( BIT_16 )
#define BITS_PIN_SLP(_x_)               ( ((_x_) << 13) & (BIT_13|BIT_14|BIT_15|BIT_16) )
#define BIT_PIN_WPU_SEL                 ( BIT_12 )
#define BITS_PIN_DS(_x_)                ( ((_x_) << 8) & (BIT_8|BIT_9|BIT_10) )
#define BIT_PIN_WPU                     ( BIT_7 )
#define BIT_PIN_WPD                     ( BIT_6 )
#define BITS_PIN_AF(_x_)                ( ((_x_) << 4) & (BIT_4|BIT_5) )
#define BIT_PIN_SLP_WPU                 ( BIT_3 )
#define BIT_PIN_SLP_WPD                 ( BIT_2 )
#define BIT_PIN_SLP_IE                  ( BIT_1 )
#define BIT_PIN_SLP_OE                  ( BIT_0 )

/* vars definitions for controller CTL_PIN */
#define BIT_PIN_NUL                     ( 0 )
#define BIT_PIN_SLP_NUL                 ( 0 )
#define BIT_PIN_SLP_Z                   ( 0 )
#define BIT_PIN_WPU_SEL                 ( BIT_12 )
#define BIT_PIN_WPUS                    ( BIT_12 )
#define BIT_PIN_NULL                    ( 0 )
#endif //_PINMAP_H_


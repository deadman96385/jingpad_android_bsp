/******************************************************************************
 ** File Name:      sprd_2731.h                                                  *
 ** Author:         mingming.Ji                                              *
 ** DATE:           01/15/2016                                                *
 ** Copyright:      2016 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the regiters of 2721.                *

 ******************************************************************************/

#ifndef _SPRD_2721_H_
#define _SPRD_2721_H_


#include "adi.h"
#include <asm/arch/sprd_reg.h>


/*here is the pinmap info of adie such as 2721*/
#define CTL_ANA_PIN_BASE			(ANA_PIN_BASE)


/* registers definitions for controller CTL_PIN */
#define REG_PIN_ANA_PTESTO			( 0x00 )
#define REG_PIN_ANA_ADI_SCLK			( 0x04 )
#define REG_PIN_ANA_ADI_D			( 0x08 )
#define REG_PIN_ANA_EXT_XTL_EN0			( 0x0c )
#define REG_PIN_ANA_EXT_XTL_EN1			( 0x10 )
#define REG_PIN_ANA_EXT_XTL_EN2			( 0x14 )
#define REG_PIN_ANA_DCDC_CPU_EN			( 0x18 )
#define REG_PIN_ANA_EXT_XTL_EN3			( 0x1c )
#define REG_PIN_ANA_TDIG			( 0x20 )
#define REG_PIN_ANA_CHIP_SLEEP			( 0x24 )
#define REG_PIN_ANA_CLK_32K			( 0x28 )
#define REG_PIN_ANA_ANA_INT			( 0x2c )
#define REG_PIN_ANA_AUD_ADSYNC			( 0x30 )
#define REG_PIN_ANA_AUD_ADD0			( 0x34 )
#define REG_PIN_ANA_AUD_DASYNC			( 0x38 )
#define REG_PIN_ANA_AUD_DAD0			( 0x3c )
#define REG_PIN_ANA_AUD_DAD1			( 0x40 )
#define REG_PIN_ANA_AUD_SCLK			( 0x44 )
#define REG_PIN_ANA_EXT_RST_B			( 0x48 )

/* bits definitions for register REG_PIN_XXX */
#define BITS_ANA_PIN_DS(_x_)                ( ((_x_) << 8) & (BIT_8|BIT_9) )
#define BIT_ANA_PIN_WPU                     ( BIT_7 )
#define BIT_ANA_PIN_WPD                     ( BIT_6 )
#define BITS_ANA_PIN_AF(_x_)                ( ((_x_) << 4) & (BIT_4|BIT_5) )
#define BIT_ANA_PIN_SLP_WPU                 ( BIT_3 )
#define BIT_ANA_PIN_SLP_WPD                 ( BIT_2 )
#define BIT_ANA_PIN_SLP_IE                  ( BIT_1 )
#define BIT_ANA_PIN_SLP_OE                  ( BIT_0 )

#define BIT_ANA_PIN_SLP_Z               	( 0 )
#define	BIT_ANA_PIN_NUL				( 0 )

#endif //_SPRD_2721_H_

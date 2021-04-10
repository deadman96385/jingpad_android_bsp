/******************************************************************************
 ** File Name:        adc_reg_v3.h                                    *
 ** Author:           Yi.Qiu                                                  *
 ** DATE:             09/16/2009                                              *
 ** Copyright:        2009 Spreatrum, Incoporated. All Rights Reserved.       *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE            NAME            DESCRIPTION                               *
 ** 09/16/2009    Yi.Qiu            Reconstruct ADC driver                    *
 ** 05/07/2010    Mingwei.zhang     Modify it for SC8800G.                    *
 ******************************************************************************/
#ifndef _ADC_REG_V3_H_
#define _ADC_REG_V3_H_

#include <asm/arch/sprd_reg.h>
#include <asm/arch/common.h>

/**---------------------------------------------------------------------------*
**                               Micro Define                                **
**---------------------------------------------------------------------------*/
/* ADC Ctronl Registers */
#define ADC_REG_BASE                        ADC_BASE 

#define ADC_CTRL                            (ADC_REG_BASE + 0x0000)
#define ADC_CS                              (ADC_REG_BASE + 0x0004)
#define ADC_HW_CH_CFG_SLOW(x)               (ADC_REG_BASE + 0x0008 + ((x)-1)*0x04)
#define ADC_HW_CH_CFG_FAST(x)               (ADC_REG_BASE + 0x0028 + ((x)-1)*0x04)
#define ADC_HW_CH_DELAY                     (ADC_REG_BASE + 0x0048)
#define ADC_DAT                             (ADC_REG_BASE + 0x004C)
#define ADC_INT_EN                          (ADC_REG_BASE + 0x0050)
#define ADC_INT_CLR                         (ADC_REG_BASE + 0x0054)
#define ADC_INT_STAT                        (ADC_REG_BASE + 0x0058)
#define ADC_INT_SRC                         (ADC_REG_BASE + 0x005C)

///ADC_CTRL
#define BIT_SW_CH_RUN_NUM(_X_)		((((_X_) - 1) & 0xF ) << 4)
#define SW_CH_NUM_MSK				(BIT(4) | BIT(5) | BIT(6) | BIT(7))
#define ADC_MODE_12B                        BIT_2
#define SW_CH_ON_BIT                        BIT_1
#define ADC_EN_BIT                          BIT_0

///ADC_CS bit map
#define ADC_SCALE_BIT                       BIT_5
#define ADC_CS_BIT_MSK                      0x1F

////ADC_TPC_CH_CTRL bit map

////ADC_INT_EN
#define ADC_IRQ_EN_BIT                      BIT_0
///ADC_INT_CLR bit map
#define ADC_IRQ_CLR_BIT                     BIT_0

#define ADC_IRQ_RAW_BIT                     BIT_0
//ADC_DAT bit map
#define ADC_DATA_MSK                        0xFFF

#define TPC_CHANNEL_X    2
#define TPC_CHANNEL_Y    3

#define ADC_CH_MAX_NUM                  8


/**---------------------------------------------------------------------------*/
#endif //_ADC_REG_V3_H_




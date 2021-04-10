/******************************************************************************
 ** File Name:    adi_reg_v3.h                                                *
 ** Author:       Tim.Luo                                                     *
 ** DATE:         03/03/2010                                                  *
 ** Copyright:    2005 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 03/03/2010    Tim.Luo         Create.                                     *
 ******************************************************************************/

#ifndef _ADI_REG_V3_H_
#define _ADI_REG_V3_H_

#include <asm/arch/sprd_reg.h>

//#define  SPRD_ADI_BASE	        SPRD_MISC_PHYS

#define  ADI_CTL_REG            (SPRD_ADI_BASE + 0x4 )
#define  ADI_CHANNEL_PRI        (SPRD_ADI_BASE + 0x8 )
#define  ADI_INT_EN             (SPRD_ADI_BASE + 0xC )
#define  ADI_INT_RAW_STS        (SPRD_ADI_BASE + 0x10)
#define  ADI_INT_MASK_STS       (SPRD_ADI_BASE + 0x14)
#define  ADI_INT_CLR            (SPRD_ADI_BASE + 0x18)
#define  ADI_GSSI_CTL0          (SPRD_ADI_BASE + 0x1C)
#define  ADI_GSSI_CTL1          (SPRD_ADI_BASE + 0x20)
#define  ADI_ARM_RD_CMD         (SPRD_ADI_BASE + 0x24)
#define  ADI_RD_DATA            (SPRD_ADI_BASE + 0x28)
#define  ADI_FIFO_STS           (SPRD_ADI_BASE + 0x2C)
#define  ADI_STS                (SPRD_ADI_BASE + 0x30)
#define  ADI_REQ_STS            (SPRD_ADI_BASE + 0x34)

//ADI_EIC
#define ADI_EIC_DATA		(ANA_EIC_BASE + 0x00)
#define ADI_EIC_MASK		(ANA_EIC_BASE + 0x04)

//ADI_CTL_REG
#define ANA_INT_STEAL_EN        BIT_0
#define ARM_SERCLK_EN           BIT_1
#define DSP_SERCLK_EN           BIT_2

//ADI_FIFO_STS
#define ADI_FIFO_EMPTY          BIT_10
#define ADI_FIFO_FULL           BIT_11

#endif  //_ADI_REG_V3_H_



/******************************************************************************
 ** File Name:    gpio_reg_v0.h                                            *
 ** Author:       Steve.Zhan                                                 *
 ** DATE:         06/05/2010                                                  *
 ** Copyright:    2010 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 06/05/2010    Steve.Zhan      Create.                                     *
 ******************************************************************************/
#ifndef _GPIO_REG_V0_H_
#define _GPIO_REG_V0_H_

#include <sci_types.h>
/*----------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **------------------------------------------------------------------------- */

/**---------------------------------------------------------------------------*
 **                             Compiler Flag                                 *
 **--------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif
/**---------------------------------------------------------------------------*
**                               Micro Define                                **
**---------------------------------------------------------------------------*/
#define GPIO_BASE                               SPRD_GPIO_PHYS
//GPIO_OFFSET
#define GPIO_DATA                               0x0000    //GPIO data register
#define GPIO_DMSK                               0x0004    //GPIO data mask register, GPIO pin can be read and write if the mask bit is "1"
#define GPIO_DIR                                0x0008    //"1" configure pin to be output"0" configure pin to be input
#define GPIO_IS                                 0x000C    //Interrupt sense register. "1" detect levels, "0" detect edges
#define GPIO_IBE                                0x0010    //Interrupt both edges register. "1" both edges trigger an interrupt, "0" interrupt generation event is controlled by GPIOIEN
#define GPIO_IEV                                0x0014    //Interrupt event register, "1" rising edges or high levels trigger interrupts, "0" falling edges or low levels trigger interrupts.
#define GPIO_IE                                 0x0018    //Interrupt mask register, "1" corresponding pin is not masked. "0" corresponding pin interrupt is masked
#define GPIO_RIS                                0x001C    //Row interrupt status, reflect the status of interrupts trigger conditions detection on pins (prior to masking). "1" interrupt condition met "0" condition not met
#define GPIO_MIS                                0x0020    //Masked interrupt status, "1" Interrupt active "0" interrupt not active
#define GPIO_IC                                 0x0024    //Interrupt clear, "1" clears edge detection interrupt. "0" has no effect.

//GPI_OFFSET
#define GPI_DATA                        0x0000    //GPI data register, original input signal, not through de-bounce path.
#define GPI_DMSK                        0x0004    //GPI data mask register. GPIDATA register can be read if the mask bit is "1"
#define GPI_IEV                         0x0014    //Interrupt event register, "1" high levels trigger interrupts, "0" low levels trigger interrupts.
#define GPI_IE                          0x0018    //Interrupt mask register, "1" corresponding pin is not masked. "0" corresponding pin interrupt is masked
#define GPI_RIS                         0x001C    //Row interrupt status, reflect the status of interrupts trigger conditions detection on pins (prior to masking). "1" interrupt condition met "0" condition not met
#define GPI_MIS                         0x0020    //Masked interrupt status, "1" Interrupt active "0" interrupt not active
#define GPI_IC                          0x0024    //Interrupt clear, "1" clears level detection interrupt. "0" has no effect.
#define GPI_0CTRL                       0x0028    //GPI0:...
#define GPI_1CTRL                       0x002C    //GPI1:...
#define GPI_2CTRL                       0x0030    //GPI2:...
#define GPI_3CTRL                       0x0034    //GPI3:...
#define GPI_4CTRL                       0x0038    //GPI4:...
#define GPI_5CTRL                       0x003C    //GPI5:...
#define GPI_6CTRL                       0x0040    //GPI4:...
#define GPI_7CTRL                       0x0044    //GPI5:...
#define GPI_TRIG                        0x0048
#define GPI_DEBOUNCE_BIT                 BIT_8
#define GPI_DEBOUNCE_PERIED                255

//GPO_OFFSET
#define GPO_DATA                        0x0000    //GPO data register
#define GPO_TRI                         0x0004    //0x08    GPOTRI  [15:0]  0xFFFF  GPO tri-status control; 1 normal output, 0 tri-status output

/*----------GPIO iterface Control Registers----------*/

//GPIO_OFFSET
#define GPIO_DATA                               0x0000    //GPIO data register
#define GPIO_DMSK                               0x0004    //GPIO data mask register, GPIO pin can be read and write if the mask bit is "1"
#define GPIO_DIR                                0x0008    //"1" configure pin to be output"0" configure pin to be input
#define GPIO_IS                                 0x000C    //Interrupt sense register. "1" detect levels, "0" detect edges
#define GPIO_IBE                                0x0010    //Interrupt both edges register. "1" both edges trigger an interrupt, "0" interrupt generation event is controlled by GPIOIEN
#define GPIO_IEV                                0x0014    //Interrupt event register, "1" rising edges or high levels trigger interrupts, "0" falling edges or low levels trigger interrupts.
#define GPIO_IE                                 0x0018    //Interrupt mask register, "1" corresponding pin is not masked. "0" corresponding pin interrupt is masked
#define GPIO_RIS                                0x001C    //Row interrupt status, reflect the status of interrupts trigger conditions detection on pins (prior to masking). "1" interrupt condition met "0" condition not met
#define GPIO_MIS                                0x0020    //Masked interrupt status, "1" Interrupt active "0" interrupt not active
#define GPIO_IC                                 0x0024    //Interrupt clear, "1" clears edge detection interrupt. "0" has no effect.

//GPIO ARM Control.
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

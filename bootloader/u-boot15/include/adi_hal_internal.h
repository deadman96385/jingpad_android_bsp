/******************************************************************************
 ** File Name:      adi_hal_internal.h                                                 *
 ** Author:         tim.luo                                             *
 ** DATE:           2/25/2010                                                *
 ** Copyright:      2010 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic operation interfaces of       *
 **                 Analog to Digital Module.                                       *
 **                                                                                             *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 2/25/2010     Tim Luo      Create.                                   *
 **                                                                                                *
 ******************************************************************************/


#ifndef _ADI_HAL_INTERNAL_H_
#define  _ADI_HAL_INTERNAL_H_

#include "adi.h"

#define		ADI_init	sci_adi_init

///for analog die register operation
#define ANA_REG_OR(reg_addr, value)     \
    do{\
        sci_adi_write(reg_addr, (unsigned short)(value), 0); \
    }while(0)
#define ANA_REG_MSK_OR(reg_addr, value, msk)        \
    do{\
        sci_adi_write(reg_addr, (unsigned short)((value)&(msk)), msk); \
    }while(0)
#define ANA_REG_AND(reg_addr, value)    \
    do{\
        sci_adi_write(reg_addr, 0, (unsigned short)(~(value))); \
    }while(0)
#define ANA_REG_BIC(reg_addr, value)    \
    do{\
        sci_adi_write(reg_addr, 0, (unsigned short)(value)); \
    }while(0)


#define ANA_REG_SET(reg_addr, value)    sci_adi_raw_write(reg_addr, (unsigned short)(value))

#define ANA_REG_GET(reg_addr)           sci_adi_read(reg_addr)

#define ANA_GET_CHIP_ID                 sci_get_adie_chip_id

#endif  //_ADI_HAL_INTERNAL_H_

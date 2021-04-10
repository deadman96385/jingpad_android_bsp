/******************************************************************************
 ** File Name:    rtc_reg_v3.h                                            *
 ** Author:       mingwei.zhang                                                 *
 ** DATE:         06/11/2010                                                  *
 ** Copyright:    2010 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 06/11/2010    mingwei.zhang   Create.                                     *
 ******************************************************************************/
#ifndef _RTC_REG_V3_H_
#define _RTC_REG_V3_H_

/**---------------------------------------------------------------------------*
**                               Micro Define                                **
**---------------------------------------------------------------------------*/
#include "asm/arch/sprd_reg.h"
#include <asm/arch/common.h>

////
/*----------Real Timer Counter Register----------*/
///
#define RTC_BASE      					ANA_RTC_BASE
#define ANA_RTC_SEC_CNT                 (RTC_BASE + 0x00)
#define ANA_RTC_MIN_CNT                 (RTC_BASE + 0x04)
#define ANA_RTC_HOUR_CNT                (RTC_BASE + 0x08)
#define ANA_RTC_DAY_CNT                 (RTC_BASE + 0x0C)
#define ANA_RTC_SEC_UPDATE              (RTC_BASE + 0x10)
#define ANA_RTC_MIN_UPDATE              (RTC_BASE + 0x14)
#define ANA_RTC_HOUR_UPDATE             (RTC_BASE + 0x18)
#define ANA_RTC_DAY_UPDATE              (RTC_BASE + 0x1C)
#define ANA_RTC_SEC_ALM                 (RTC_BASE + 0x20)
#define ANA_RTC_MIN_ALM                 (RTC_BASE + 0x24)
#define ANA_RTC_HOUR_ALM                (RTC_BASE + 0x28)
#define ANA_RTC_DAY_ALM                 (RTC_BASE + 0x2C)
#define ANA_RTC_INT_EN                  (RTC_BASE + 0x30)
#define ANA_RTC_INT_RSTS                (RTC_BASE + 0x34)
#define ANA_RTC_INT_CLR                 (RTC_BASE + 0x38)
#define ANA_RTC_INT_MSK                 (RTC_BASE + 0x3C)

#define ANA_RTC_SPG_VALUE               (RTC_BASE + 0x50)
#define ANA_RTC_SPG_UPD                 (RTC_BASE + 0x54)

//The corresponding bit of RTC_CTL register.
#define RTC_SEC_BIT                 BIT_0        //Sec int enable
#define RTC_MIN_BIT                 BIT_1        //Min int enable
#define RTC_HOUR_BIT                BIT_2        //Hour int enable
#define RTC_DAY_BIT                 BIT_3        //Day int enable
#define RTC_ALARM_BIT               BIT_4        //Alarm int enable
#define RTCCTL_HOUR_FMT_SEL         BIT_5        //Hour format select
//#define RTCCTL_EN                         BIT_6        //Rtc module enable

#define RTC_SEC_ACK_BIT             BIT_8        // Sec ack int enable
#define RTC_MIN_ACK_BIT             BIT_9        //Min ack int enable
#define RTC_HOUR_ACK_BIT            BIT_10        //Hour ack int enable
#define RTC_DAY_ACK_BIT             BIT_11        //Day ack int enable
#define RTC_SEC_ALM_ACK_BIT         BIT_12        //Sec alm ack int enable
#define RTC_MIN_ALM_ACK_BIT         BIT_13        //Min alm ack int enable
#define RTC_HOUR_ALM_ACK_BIT        BIT_14        //Hour alm ack int enable
#define RTC_DAY_ALM_ACK_BIT         BIT_15        //Day alm ack int enable

#define RTC_UPD_TIME_MASK (RTC_SEC_ACK_BIT | RTC_MIN_ACK_BIT | RTC_HOUR_ACK_BIT | RTC_DAY_ACK_BIT)
#define RTC_INT_ALL_MSK (0xFFFF&(~(BIT_5|BIT_6|BIT_7)))

#define RTC_SEC_MASK 0x3F
#define RTC_MIN_MASK 0x3F
#define RTC_HOUR_MASK 0x1F
#define RTC_DAY_MASK 0xFFFF

/**---------------------------------------------------------------------------*/
#endif //_RTC_REG_V3_H_



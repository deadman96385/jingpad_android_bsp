/******************************************************************************
 ** File Name:    sys_timer_reg_v0.h                                            *
 ** Author:       Steve.Zhan                                                 *
 ** DATE:         06/05/2010                                                  *
 ** Copyright:    2010 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 06/12/2010    hao.liu    Create.                                     *
 ******************************************************************************/
#ifndef _SYS_TIMER_REG_V5_H_
#define _SYS_TIMER_REG_V5_H_

/**---------------------------------------------------------------------------*
**                               Micro Define                                **
**---------------------------------------------------------------------------*/
/*----------System Count----------*/
#include "sprd_reg.h"

#define SYSTIMER_BASE                   (SPRD_SYSCNT_PHYS)

#define SYS_ALM                         (SYSTIMER_BASE + 0x0000)
#define SYS_CNT0                        (SYSTIMER_BASE + 0x0004)
#define SYS_CTL                         (SYSTIMER_BASE + 0x0008)
#define SYS_VALUE_SHDW                  (SYSTIMER_BASE + 0x000C)

#define SYSTEM_CURRENT_CLOCK (*((volatile u32 *)SYS_VALUE_SHDW) & 0xFFFFFFFF)

/**---------------------------------------------------------------------------*/
#endif
// End

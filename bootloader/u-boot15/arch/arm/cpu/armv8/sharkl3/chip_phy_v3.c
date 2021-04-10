/******************************************************************************
 ** File Name:      chip_phy_v3.c                                             *
 ** Author:         Richard Yang                                              *
 ** DATE:           08/14/2002                                                *
 ** Copyright:      2002 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic information on chip.          *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 08/14/2002     Richard.Yang     Create.                                   *
 ** 09/16/2003     Xueliang.Wang    Modify CR4013                             *
 ** 08/23/2004     JImmy.Jia        Modify for SC6600D                        *
 ******************************************************************************/

/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/
#include <asm/io.h>
#include "adi_hal_internal.h"
//#include "asm/arch/wdg_drvapi.h"
#include "asm/arch/sprd_reg.h"
#include "asm/arch/common.h"
#include "sprd_wdt.h"
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif

extern void wdt_reset_MCU(void);
extern uint32_t SCI_GetTickCount(void);

/*****************************************************************************/
// Description :    This function is used to reset MCU.
// Global resource dependence :
// Author :         Xueliang.Wang
// Note :
/*****************************************************************************/
void CHIP_ResetMCU (void)  //reset interrupt disable??
{
    // This loop is very important to let the reset process work well on V3 board
    // @Richard
    uint32_t i = 10000;

    start_watchdog(5);

    while (i--);

    wdt_reset_MCU();

    {
        volatile uint32_t tick1 = SCI_GetTickCount();
        volatile uint32_t tick2 = SCI_GetTickCount();

        while ( (tick2 - tick1) < 500)
        {
            tick2 = SCI_GetTickCount();
        }
    }
}

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

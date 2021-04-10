/******************************************************************************
 ** File Name:      cp_mode.c                                                 *
 ** Author:         Andrew.Yang                                               *
 ** DATE:           31/03/2014                                                *
 ** Copyright:      2014 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the logic interfaces called during boot,*
 **                 including reset mode setting, initialization etc.
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 31/03/2014     Andrew           Create.                                   *
 ******************************************************************************/

/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifndef _CP_BOOT_H_
#define  _CP_BOOT_H__


/**---------------------------------------------------------------------------*
 **                         Global variables                                  *
 **---------------------------------------------------------------------------*/

#define msleep(cnt) udelay(cnt*1000)
/**---------------------------------------------------------------------------*
 **                         Local variables                                   *
 **---------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------*
 **                     Local Function Prototypes                             *
 **---------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------*
 **                         Function Prototypes                               *
 **---------------------------------------------------------------------------*/
/*****************************************************************************/
//  Description:    Sets the different kinds of reset modes, used in normal p-
//                  ower up mode, watchdog reset mode and calibration mode etc.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
static inline void cp0_arm0_boot(void)
{
    u32 state;

      /* open cp0 pmu controller
    *((volatile u32*)REG_PMU_APB_PD_CP0_SYS_CFG ) &= ~BIT(25);
    msleep(50);
    *((volatile u32*)REG_PMU_APB_PD_CP0_SYS_CFG ) &= ~BIT(28);
    */

    *((volatile u32*)REG_PMU_APB_SLEEP_CTRL) &= ~ BIT(17);   /*clear cp0 sleep */
    *((volatile u32*)REG_PMU_APB_CP_SOFT_RST)|= BIT(0);   /* reset cp0 */
    msleep(50);
    *((volatile u32*)REG_PMU_APB_CP_SOFT_RST) &= ~ BIT(0); /* clear cp0 force shutdown */

    while(1)
    {
    state = *((volatile u32*)REG_PMU_APB_CP_SOFT_RST);
    if(!(state & BIT(0)))
      break;
    }
}

/*****************************************************************************/
//  Description:    Gets the current reset mode.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
static inline void cp1_boot(void)
{
    u32 state;
    *((volatile u32*)REG_AON_APB_APB_RST1) |= BIT(20);   /* reset cp1 */
    msleep(50);
    *((volatile u32*)REG_AON_APB_APB_RST1) &= ~ BIT(20);   /*clear reset cp1 */
    *((volatile u32*)REG_PMU_APB_SLEEP_CTRL) &= ~(BIT(18) | BIT(20));   /*clear cp1 sleep */

    *((volatile u32*)REG_PMU_APB_CP_SOFT_RST)|= BIT(1);   /* reset cp0 */
    msleep(50);
    *((volatile u32*)REG_PMU_APB_CP_SOFT_RST) &= ~ BIT(1); /* clear cp0 force shutdown */

    while(1)
    {
    state = *((volatile u32*)REG_PMU_APB_CP_SOFT_RST);
    if(!(state & BIT(1)))
      break;
    }
}
/*****************************************************************************/
//  Description:    Gets the current reset mode.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
void pmic_arm7_RAM_active(void)
{
    u32 state;
    *((volatile u32*)REG_AON_APB_ARM7_SYS_SOFT_RST) |= BIT(0);   /* 0x402e0114*/
    msleep(50);
    *((volatile u32*)REG_PMU_APB_CP_SOFT_RST)|= BIT(8);   /* reset arm7*/
    msleep(50);
    *((volatile u32*)REG_PMU_APB_CP_SOFT_RST) &= ~BIT(8); /* clear arm7*/
    while(1)
    {
        state = *((volatile u32*)REG_PMU_APB_CP_SOFT_RST);
        if(!(state & BIT(8)))
          break;
    }
}


/*****************************************************************************/
//  Description:    Gets the current reset mode.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
static inline void pmic_arm7_boot(void)
{
    u32 state;
    *((volatile u32*)REG_PMU_APB_SLEEP_CTRL) &= ~ BIT(21);   /*clear arm7 force sleep */
    *((volatile u32*)REG_AON_APB_ARM7_SYS_SOFT_RST) &= ~ BIT(0);   /* reset arm7 */
    msleep(50);
}


/*****************************************************************************/
//  Description:    After normal power on, the HW_RST flag should be reset in
//                  order to judge differrent reset conditions between normal
//                  power on reset and watchdog reset.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
static inline void cp2_boot()
{
}

/*****************************************************************************/
//  Description:    Before watchdog reset, writting HW_RST flag is uesed to j-
//                  udge differrent watchdog reset conditions between MCU reset
//                  and system-halted.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
static inline void cp0_arm1_boot(void)
{
}

static inline void cp0_arm2_boot(void)
{
}


/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#endif

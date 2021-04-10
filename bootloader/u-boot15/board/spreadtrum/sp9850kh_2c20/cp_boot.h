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

#define PUBCP_IRAM_ADDRESS 0x5001D000

static u32 g_loader[] = {
	 0xEE110F10, 0xE3C00005, 0xE3C00A01, 0xF57FF04F,
	 0xEE010F10, 0xF57FF06F, 0xEE110F30, 0xE3800802,
	 0xE3800801, 0xE3C00902, 0xEE010F30, 0xF57FF04F,
	 0xE3A00000, 0xEE070F15, 0xEE0F0F15, 0xE3A01000,
	 0xEE061F12, 0xF57FF06F, 0xE3A01000, 0xEE061F11,
	 0xE3A0103F, 0xEE061F51, 0xE3A01C13, 0xEE061F91,
	 0xE3A01001, 0xEE061F12, 0xF57FF06F, 0xE3A01000,
	 0xEE061F11, 0xE3A0102F, 0xEE061F51, 0xE3A01FC2,
	 0xEE061F91, 0xE3A01003, 0xEE061F12, 0xF57FF06F,
	 0xE3A01102, 0xEE061F11, 0xE3A0103D, 0xEE061F51,
	 0xE3A01FC2, 0xEE061F91, 0xEE110F30, 0xE3C00802,
	 0xE3C00801, 0xE3C00902, 0xEE010F30, 0xEE110F10,
	 0xE3800001, 0xF57FF04F, 0xEE010F10, 0xF57FF06F,
	 0xE51FF004, 0x8ba00600
};

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
extern int load_cp_boot_code(void *loader);
#else
inline int load_cp_boot_code(void *loader)
{
	return -1;
}
#endif

static inline void pubcp_boot(void)
{
	u32 state;
	u32 loader[0x32] = {0};
	u32 count = sizeof(loader)/sizeof(u32);

	if(load_cp_boot_code((void*)PUBCP_IRAM_ADDRESS))
	    memcpy((void*)PUBCP_IRAM_ADDRESS, g_loader, sizeof(g_loader));

	/*boot cr5 */
	*((volatile u32*)REG_PMU_APB_CP_SOFT_RST)|= BIT_1;   /* reset R5 */
	*((volatile u32*)REG_AON_APB_PCP_SOFT_RST) |= BIT_10; /*cr5 core soft reset*/

	msleep(50);

	/*power on*/
	//*((volatile u32*)REG_PMU_APB_PD_PUBCP_SYS_CFG) &= ~(BIT_25);/* clear R5 force shutdown */
	*((volatile u32*)REG_PMU_APB_PD_PUBCP_SYS_CFG) &= ~(BIT_24|BIT_25);/* clear R5 auto shutdown  deep sleep*/
	*((volatile u32*)REG_PMU_APB_SLEEP_CTRL) &= ~BIT_18;   /*clear R5 force sleep */

	msleep(50);
	/*reset*/
	*((volatile u32*)REG_PMU_APB_CP_SOFT_RST) &= ~BIT_1; /* pubcp soft reset */
	*((volatile u32*)REG_AON_APB_PCP_SOFT_RST) &= ~BIT_10; /*cr5 core soft reset*/

}

/*****************************************************************************/
//  Description:    Gets the current reset mode.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
void pmic_arm7_RAM_active(void)
{
    u32 state;

	/* sharkl2, arm7 sys hase been release by ddr, can't be reset agian, otherwise
      the system will hung */
	state = *((volatile u32*)REG_PMU_APB_CP_SOFT_RST);
	if(!(state & BIT(8)))
	  return;

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
	//memcpy((void*)0x50800000, g_loader, 0x90);
    u32 state;
    *((volatile u32*)REG_PMU_APB_SLEEP_CTRL) &= ~ BIT(21);   /*clear arm7 force sleep */
    *((volatile u32*)REG_AON_APB_ARM7_SYS_SOFT_RST) &= ~ BIT(0);   /* reset arm7 */
    msleep(50);
}


/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#endif

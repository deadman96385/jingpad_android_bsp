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

#define PUBCP_IRAM_ADDRESS 0xf0000

static u32 g_loader[] = {
	0xee110f10, 0xe3c00005, 0xe3c00a01, 0xf57ff04f,
	0xee010f10, 0xf57ff06f, 0xee110f30, 0xe3800802,
	0xe3800801, 0xe3c00902, 0xee010f30, 0xf57ff04f,
	0xe3a00000, 0xee070f15, 0xee0f0f15, 0xe3a01000,
	0xee061f12, 0xf57ff06f, 0xe3a01000, 0xee061f11,
	0xe3a0103f, 0xee061f51, 0xe3a01f42, 0xee061f91,
	0xee110f30, 0xe3c00802, 0xe3c00801, 0xe3c00902,
	0xee010f30, 0xee110f10, 0xe3800001, 0xf57ff04f,
	0xee010f10, 0xf57ff06f, 0xe51ff004, 0x8b800000
};

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
extern int get_cp_loader(u32 *count, u32 *loader);
#else
int get_cp_loader(u32 *count, u32 *loader)
{
	return -1;
}
#endif

static inline void pubcp_boot(void)
{
	u32 state;
	u32 loader[0x32] = {0};
	u32 count = sizeof(loader)/sizeof(u32);

	if(get_cp_loader(&count, loader) == 0)
	{
		memcpy((void *)PUBCP_IRAM_ADDRESS, loader, count * sizeof(u32));
	} else {
		printf("%s: get cp boot code failed, use default g_loader boot cp\n", __func__);
		memcpy((void*)PUBCP_IRAM_ADDRESS, g_loader, 0x90);
	}

	*((volatile u32*)REG_AON_APB_PCP_SOFT_RST) |= BIT_10; /*cr5 core soft reset*/
	msleep(50);
	*((volatile u32*)REG_AON_APB_PCP_SOFT_RST) &= ~BIT_10; /*cr5 core soft reset*/

	*((volatile u32*)REG_PMU_APB_SLEEP_CTRL) &= ~(BIT_19|BIT_20);   /*clear R5 force sleep */
	*((volatile u32*)REG_PMU_APB_PD_PUBCP_SYS_CFG) &= ~(BIT_24 | BIT_25);/* clear R5 force shutdown */

	*((volatile u32*)REG_PMU_APB_SYS_SOFT_RST)|= BIT_2;   /* reset R5 */
	msleep(50);
	*((volatile u32*)REG_PMU_APB_SYS_SOFT_RST) &= ~BIT_2; /* pubcp soft reset */

}

/*****************************************************************************/
//  Description:    Gets the current reset mode.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
void pmic_arm7_RAM_active(void)
{
	*((volatile u32*)REG_PMU_APB_SYS_SOFT_RST) |= BIT_1;   /* reset M4 */
}

/*****************************************************************************/
//  Description:    Gets the current reset mode.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
static inline void pmic_arm_m4_boot(void)
{
    u32 state;
	*((volatile u32*)REG_PMU_APB_SLEEP_CTRL) &= ~BIT_23;   /*clear M4 force sleep */
	*((volatile u32*)REG_PMU_APB_SYS_SOFT_RST) &= ~(BIT_1 | BIT_21);   /* reset M4 */
    msleep(50);
}

static inline void agdsp_boot(void)
{
   *((volatile u32*)REG_PMU_APB_PD_AGCP_SYS_CFG) &= ~BIT_25;
   *((volatile u32*)REG_PMU_APB_PD_AGCP_DSP_CFG) &= ~BIT_25;
   *((volatile u32*)REG_PMU_APB_SYS_SOFT_RST) &= ~BIT_28;
   *((volatile u32*)REG_PMU_APB_SLEEP_CTRL) &= ~(BIT_19 | BIT_21);
   *((volatile u32*)REG_AON_APB_AGCP_BOOT_PROT) |= BITS_AON_APB_AGCP_REG_PROT_VAL(0x9620);
   *((volatile u32*)REG_AON_APB_AGCP_DSP_CTRL0) = BITS_AON_APB_AGCP_DSP_BOOT_VECTOR(0x449d0040);
   *((volatile u32*)REG_AON_APB_AGCP_CTRL) |= BIT_0;
   *((volatile u32*)REG_AON_APB_AGCP_SOFT_RESET) &= ~BIT_1;
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

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

#define PUBCP_IRAM_ADDRESS 0xF000

static u32 g_loader[] = {
	0xee110f10, 0xe3c00005, 0xe3c00a01, 0xf57ff04f,
	0xee010f10, 0xf57ff06f, 0xee110f30, 0xe3800802,
	0xe3800801, 0xe3c00902, 0xee010f30, 0xf57ff04f,
	0xe3a00000, 0xee070f15, 0xee0f0f15, 0xe3a01000,
	0xee061f12, 0xf57ff06f, 0xe3a01000, 0xee061f11,
	0xe3a0103f, 0xee061f51, 0xe3a01f42, 0xee061f91,
	0xee110f30, 0xe3c00802, 0xe3c00801, 0xe3c00902,
	0xee010f30, 0xee110f10, 0xe3800001, 0xf57ff04f,
	0xee010f10, 0xf57ff06f, 0xe51ff004, 0x8b800600
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
	u32 count = sizeof(g_loader)/sizeof(u32);

	if(load_cp_boot_code((void*)PUBCP_IRAM_ADDRESS))
		memcpy((void*)PUBCP_IRAM_ADDRESS, g_loader, count);

	//TODO
}

/*****************************************************************************/
//  Description:    Gets the current reset mode.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
void pmic_arm7_RAM_active(void)
{
	/* orca cm4 sys reset is release default, can do nothing */
	*((volatile u32*)REG_AON_APB_CM4_SYS_SOFT_RST) &= ~BIT_AON_APB_CM4_SYS_SOFT_RST; /* sys reset */
}


/*****************************************************************************/
//  Description:    Gets the current reset mode.
//  Author:         Andrew.Yang
//  Note:
/*****************************************************************************/
static inline void sp_boot(void)
{
	*((volatile u32*)REG_AON_APB_CM4_SYS_SOFT_RST) &= ~BIT_AON_APB_CM4_CORE_SOFT_RST;   /* core release */
}

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#endif

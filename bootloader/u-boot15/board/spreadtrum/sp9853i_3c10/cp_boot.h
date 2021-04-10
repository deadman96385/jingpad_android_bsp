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

#define PUBCP_IRAM_ADDRESS 0xe6022000

static u32 g_loader[] = {
	0xee110f10, 0xe3c00005, 0xe3c00a01, 0xf57ff04f,
	0xee010f10, 0xf57ff06f, 0xee110f30, 0xe3800802,
	0xe3800801, 0xe3c00902, 0xee010f30, 0xf57ff04f,
	0xe3a00000, 0xee070f15, 0xee0f0f15, 0xe3a01000,
	0xee061f12, 0xf57ff06f, 0xe3a01000, 0xee061f11,
	0xe3a0103f, 0xee061f51, 0xe3a01f42, 0xee061f91,
	0xee110f30, 0xe3c00802, 0xe3c00801, 0xe3c00902,
	0xee010f30, 0xee110f10, 0xe3800001, 0xf57ff04f,
	0xee010f10, 0xf57ff06f, 0xe51ff004, 0x83000600
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
	if(load_cp_boot_code((void*)PUBCP_IRAM_ADDRESS))
		memcpy((void*)PUBCP_IRAM_ADDRESS, g_loader, 0x90);

	/* hold cr5 */
	*((volatile u32*)REG_COM_PMU_APB_SYS_SOFT_RESET) |= (BIT_COM_PMU_APB_PUBCP_SYS_SRST|BIT_COM_PMU_APB_PUBCP_CR5_SRST);
	*((volatile u32*)REG_COM_PMU_APB_SYS_SOFT_RESET) |= BIT_COM_PMU_APB_PUBCP_CR5_CORE_SRST;

	/* clear r5 sleep */
	*((volatile u32*)REG_PMU_APB_PUBCP_SYS_SLEEP_CTRL) &= ~BIT_PMU_APB_PUBCP_SYS_FORCE_DEEP_SLEEP;
	*((volatile u32*)REG_PMU_APB_PUBCP_SYS_SLEEP_CTRL) &= ~BIT_PMU_APB_PUBCP_SYS_FORCE_LIGHT_SLEEP0;
	*((volatile u32*)REG_PMU_APB_PUBCP_SYS_SLEEP_CTRL) &= ~BIT_PMU_APB_PUBCP_SYS_FORCE_DOZE_SLEEP;
	*((volatile u32*)REG_PMU_APB_PUBCP_SYS_SLEEP_CTRL) &= ~BIT_PMU_APB_PUBCP_SYS_FORCE_PUB_DEEP_SLEEP0;

	/* power up */
	*((volatile u32*)REG_PMU_APB_PD_PUBCP_SYS_PWR_CFG) &= ~(BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN | BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN);

	/* release cr5 */
	msleep(50);
	*((volatile u32*)REG_COM_PMU_APB_SYS_SOFT_RESET) &= ~(BIT_COM_PMU_APB_PUBCP_SYS_SRST|BIT_COM_PMU_APB_PUBCP_CR5_SRST);
	msleep(50);
	*((volatile u32*)REG_COM_PMU_APB_SYS_SOFT_RESET) &= ~BIT_COM_PMU_APB_PUBCP_CR5_CORE_SRST;
}

/* activation of PARM related iram  */
void pmic_arm7_RAM_active(void)
{
	/* enable ap access to cm4 permissions */
	*((volatile u32*)REG_COMMON_APB_SP_CFG_BUS) &= ~BIT_COMMON_APB_SP_CFG_BUS_SLEEP;
	/* hold cm4 */
	*((volatile u32*)REG_COM_PMU_APB_SYS_SOFT_RESET) |= (BIT_COM_PMU_APB_CM4_CORE_SRST | BIT_COM_PMU_APB_CM4_SYS_SRST);
	/* clear cm4 force sleep */
	*((volatile u32*)REG_PMU_APB_CM4_SYS_SLEEP_CTRL) &= ~(BIT_PMU_APB_CM4_SYS_FORCE_DEEP_SLEEP | BIT_PMU_APB_CM4_SYS_FORCE_DOZE_SLEEP);
}

static inline void parm_modem_boot(void)
{
	/*clear M4 software interrupt */
	*((volatile u32*)REG_COMMON_APB_SP_CFG_BUS) &= ~BIT_COMMON_APB_INT_REQ_CM4_SOFT;
	/* release cm4 */
	msleep(50);
	*((volatile u32*)REG_COM_PMU_APB_SYS_SOFT_RESET) &= ~(BIT_COM_PMU_APB_CM4_CORE_SRST | BIT_COM_PMU_APB_CM4_SYS_SRST);
}

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#endif

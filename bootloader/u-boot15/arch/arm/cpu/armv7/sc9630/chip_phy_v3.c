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
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif

/**---------------------------------------------------------------------------*
 **                         Macro defines.
 **---------------------------------------------------------------------------*/
#define DDR_PHY_IND_ADDR  0x30010184
#define DDR_PHY_IND_ADDR1 0x30040000
#define DDR_PHY_IND_ADDR2 0x402e3048
#define DDR_PHY_IND_PHY_ALIVE 0x00000001
/**---------------------------------------------------------------------------*
 **                         Struct defines.
 **---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*
 **                         Global variables                                  *
 **---------------------------------------------------------------------------*/

/**---------------------------------------------------------------------------*
 **                         Function Definitions                              *
 **---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*
 **                         Struct defines.
 **---------------------------------------------------------------------------*/
struct dcdc_core_ds_step_info{
	u32 ctl_reg;
	u32 ctl_sht;
	u32 cal_reg;
	u32 cal_sht;
};

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
    uint32 i = 10000;

	start_watchdog(5);

    while (i--);

    wdt_reset_MCU();

    {
        volatile uint32 tick1 = SCI_GetTickCount();
        volatile uint32 tick2 = SCI_GetTickCount();

        while ( (tick2 - tick1) < 500)
        {
            tick2 = SCI_GetTickCount();
        }
    }
}

void pmu_commom_config(void)
{
#if defined(CONFIG_ARCH_SCX35L)
#if defined(CONFIG_ARCH_SCX20L)
	//reserved register,need not config
        //CHIP_REG_SET(REG_PMU_APB_PD_CP0_SYS_CFG,
	//	0
	//);
        //removed ARM9_0 sys
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_ARM9_0_CFG,
		BIT_PD_CP0_ARM9_0_FORCE_SHUTDOWN |
		//BIT_PD_CP0_ARM9_0_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_ARM9_0_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_ARM9_0_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_ARM9_0_ISO_ON_DLY(0x02) |
		0
	);
	//removed ARM9_1 sys
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_ARM9_1_CFG,
		BIT_PD_CP0_ARM9_1_FORCE_SHUTDOWN |
		//BIT_PD_CP0_ARM9_1_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_ARM9_1_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_ARM9_1_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_ARM9_1_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_GSM_0_CFG,
		//BIT_PD_CP0_GSM_0_FORCE_SHUTDOWN |
		BIT_PD_CP0_GSM_0_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_GSM_0_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_GSM_0_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_GSM_0_ISO_ON_DLY(0x02) |
		0
	);
        //removed GSM_1 sys
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_GSM_1_CFG,
		BIT_PD_CP0_GSM_1_FORCE_SHUTDOWN |
		//BIT_PD_CP0_GSM_1_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_GSM_1_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_GSM_1_PWR_ON_SEQ_DLY(0x04) |
		BITS_PD_CP0_GSM_1_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_CEVA_0_CFG,
		//BIT_PD_CP0_CEVA_0_FORCE_SHUTDOWN |
		BIT_PD_CP0_CEVA_0_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_CEVA_0_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_CEVA_0_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_CEVA_0_ISO_ON_DLY(0x02) |
		0
	);
        //removed CEVA_1 sys
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_CEVA_1_CFG,
		BIT_PD_CP0_CEVA_1_FORCE_SHUTDOWN |
		//BIT_PD_CP0_CEVA_1_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_CEVA_1_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_CEVA_1_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_CEVA_1_ISO_ON_DLY(0x02) |
		0
	);
        //remove HU3GE sys
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_HU3GE_CFG,
		BIT_PD_CP0_HU3GE_FORCE_SHUTDOWN |
		//BIT_PD_CP0_HU3GE_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_HU3GE_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_HU3GE_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP0_HU3GE_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_TD_CFG,
		//BIT_PD_CP0_TD_FORCE_SHUTDOWN |
		BIT_PD_CP0_TD_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_TD_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_TD_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP0_TD_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C0_CFG,
		//BIT_PD_CA7_C0_WFI_SHUTDOWN_EN |
		//BIT_PD_CA7_C0_DBG_SHUTDOWN_EN |
		//BIT_PD_CA7_C0_FORCE_SHUTDOWN |
		BIT_PD_CA7_C0_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_C0_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_C0_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CA7_C0_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C1_CFG,
		//BIT_PD_CA7_C1_WFI_SHUTDOWN_EN |
		//BIT_PD_CA7_C1_DBG_SHUTDOWN_EN |
		BIT_PD_CA7_C1_FORCE_SHUTDOWN |
		//BIT_PD_CA7_C1_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_C1_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_C1_PWR_ON_SEQ_DLY(0x04) |
		BITS_PD_CA7_C1_ISO_ON_DLY(0x02) |
		0
	);
        //removed CA7_C2
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C2_CFG,
		//BIT_PD_CA7_C2_WFI_SHUTDOWN_EN |
		//BIT_PD_CA7_C2_DBG_SHUTDOWN_EN |
		BIT_PD_CA7_C2_FORCE_SHUTDOWN |
		//BIT_PD_CA7_C2_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_C2_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_C2_PWR_ON_SEQ_DLY(0x04) |
		BITS_PD_CA7_C2_ISO_ON_DLY(0x02) |
		0
	);
        //removed CA7_C2
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C3_CFG,
		//BIT_PD_CA7_C3_WFI_SHUTDOWN_EN |
		//BIT_PD_CA7_C3_DBG_SHUTDOWN_EN |
		BIT_PD_CA7_C3_FORCE_SHUTDOWN |
		//BIT_PD_CA7_C3_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_C3_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_C3_PWR_ON_SEQ_DLY(0x04) |
		BITS_PD_CA7_C3_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_AP_SYS_CFG,
		//BIT_PD_AP_SYS_FORCE_SHUTDOWN |
		BIT_PD_AP_SYS_AUTO_SHUTDOWN_EN |
		BITS_PD_AP_SYS_PWR_ON_DLY(0x08) |
		BITS_PD_AP_SYS_PWR_ON_SEQ_DLY(0x00) |
		BITS_PD_AP_SYS_ISO_ON_DLY(0x06) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_CFG ,
		BIT_PD_GPU_TOP_FORCE_SHUTDOWN |
		//BIT_PD_GPU_TOP_AUTO_SHUTDOWN_EN |
		BITS_PD_GPU_TOP_PWR_ON_DLY(0x08) |
		BITS_PD_GPU_TOP_PWR_ON_SEQ_DLY(0x00) |
		BITS_PD_GPU_TOP_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_MM_TOP_CFG,
		BIT_PD_MM_TOP_FORCE_SHUTDOWN |
		//BIT_PD_MM_TOP_AUTO_SHUTDOWN_EN |
		BITS_PD_MM_TOP_PWR_ON_DLY(0x08) |
		BITS_PD_MM_TOP_PWR_ON_SEQ_DLY(0x00) |
		BITS_PD_MM_TOP_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP1_CA5_CFG,
		//BIT_PD_CP1_CA5_FORCE_SHUTDOWN |
		BIT_PD_CP1_CA5_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_CA5_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_CA5_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_CA5_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP1_LTE_P1_CFG,
		//BIT_PD_CP1_LTE_P1_FORCE_SHUTDOWN |
		BIT_PD_CP1_LTE_P1_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_LTE_P1_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_LTE_P1_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_LTE_P1_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP1_LTE_P2_CFG,
		//BIT_PD_CP1_LTE_P2_FORCE_SHUTDOWN |
		BIT_PD_CP1_LTE_P2_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_LTE_P2_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_LTE_P2_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_LTE_P2_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP1_CEVA_CFG,
		//BIT_PD_CP1_CEVA_FORCE_SHUTDOWN |
		BIT_PD_CP1_CEVA_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_CEVA_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_CEVA_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_CEVA_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP1_COMWRAP_CFG,
		//BIT_PD_CP1_COMWRAP_FORCE_SHUTDOWN |
		BIT_PD_CP1_COMWRAP_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_COMWRAP_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_COMWRAP_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_COMWRAP_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_PUB_SYS_CFG,
		//BIT_PD_PUB_SYS_FORCE_SHUTDOWN |
		BIT_PD_PUB_SYS_AUTO_SHUTDOWN_EN |
		BITS_PD_PUB_SYS_PWR_ON_DLY(0x08) |
		BITS_PD_PUB_SYS_PWR_ON_SEQ_DLY(0x00) |
		BITS_PD_PUB_SYS_ISO_ON_DLY(0x06) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_TOP_CFG,
		//BIT_PD_CA7_TOP_DBG_SHUTDOWN_EN |
		//BIT_PD_CA7_TOP_FORCE_SHUTDOWN |
		BIT_PD_CA7_TOP_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_TOP_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_TOP_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CA7_TOP_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTL_WAIT_CNT,
		BITS_XTL1_WAIT_CNT(0x39) |
		BITS_XTL0_WAIT_CNT(0x39) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTLBUF_WAIT_CNT,
		BITS_XTLBUF1_WAIT_CNT(7) |
		BITS_XTLBUF0_WAIT_CNT(7) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT1,
		BITS_LTEPLL_WAIT_CNT(7) |
		BITS_TWPLL_WAIT_CNT(7) |
		BITS_DPLL_WAIT_CNT(7) |
		BITS_MPLL_WAIT_CNT(7) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT2,
		BITS_LVDSDIS_PLL_WAIT_CNT(7) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG0,
		BITS_VCP0_PWR_WAIT_CNT(0x17) |
		BITS_CP1_PWR_WAIT_CNT(0x17) |
		BITS_CP0_PWR_WAIT_CNT(0x17) |
		BITS_AP_PWR_WAIT_CNT(0x17) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG1,
		BITS_ARM7_PWR_WAIT_CNT(0x17) |
		BITS_VCP1_PWR_WAIT_CNT(0x17) |
		0
	);
#else
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_SYS_CFG,
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_ARM9_0_CFG,
		//BIT_PD_CP0_ARM9_0_FORCE_SHUTDOWN |
		BIT_PD_CP0_ARM9_0_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_ARM9_0_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_ARM9_0_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_ARM9_0_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_ARM9_1_CFG,
		//BIT_PD_CP0_ARM9_1_FORCE_SHUTDOWN |
		BIT_PD_CP0_ARM9_1_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_ARM9_1_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_ARM9_1_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_ARM9_1_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_GSM_0_CFG,
		//BIT_PD_CP0_GSM_0_FORCE_SHUTDOWN |
		BIT_PD_CP0_GSM_0_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_GSM_0_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_GSM_0_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_GSM_0_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_GSM_1_CFG,
		//BIT_PD_CP0_GSM_1_FORCE_SHUTDOWN |
		BIT_PD_CP0_GSM_1_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_GSM_1_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_GSM_1_PWR_ON_SEQ_DLY(0x04) |
		BITS_PD_CP0_GSM_1_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_CEVA_0_CFG,
		//BIT_PD_CP0_CEVA_0_FORCE_SHUTDOWN |
		BIT_PD_CP0_CEVA_0_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_CEVA_0_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_CEVA_0_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_CEVA_0_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_CEVA_1_CFG,
		//BIT_PD_CP0_CEVA_1_FORCE_SHUTDOWN |
		BIT_PD_CP0_CEVA_1_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_CEVA_1_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_CEVA_1_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CP0_CEVA_1_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_HU3GE_CFG,
		//BIT_PD_CP0_HU3GE_FORCE_SHUTDOWN |
		BIT_PD_CP0_HU3GE_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_HU3GE_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_HU3GE_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP0_HU3GE_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP0_TD_CFG,
		//BIT_PD_CP0_TD_FORCE_SHUTDOWN |
		BIT_PD_CP0_TD_AUTO_SHUTDOWN_EN |
		BITS_PD_CP0_TD_PWR_ON_DLY(0x08) |
		BITS_PD_CP0_TD_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP0_TD_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C0_CFG,
		//BIT_PD_CA7_C0_WFI_SHUTDOWN_EN |
		//BIT_PD_CA7_C0_DBG_SHUTDOWN_EN |
		//BIT_PD_CA7_C0_FORCE_SHUTDOWN |
		BIT_PD_CA7_C0_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_C0_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_C0_PWR_ON_SEQ_DLY(0x06) |
		BITS_PD_CA7_C0_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C1_CFG,
		//BIT_PD_CA7_C1_WFI_SHUTDOWN_EN |
		//BIT_PD_CA7_C1_DBG_SHUTDOWN_EN |
		BIT_PD_CA7_C1_FORCE_SHUTDOWN |
		//BIT_PD_CA7_C1_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_C1_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_C1_PWR_ON_SEQ_DLY(0x04) |
		BITS_PD_CA7_C1_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C2_CFG,
		//BIT_PD_CA7_C2_WFI_SHUTDOWN_EN |
		//BIT_PD_CA7_C2_DBG_SHUTDOWN_EN |
		BIT_PD_CA7_C2_FORCE_SHUTDOWN |
		//BIT_PD_CA7_C2_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_C2_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_C2_PWR_ON_SEQ_DLY(0x04) |
		BITS_PD_CA7_C2_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C3_CFG,
		//BIT_PD_CA7_C3_WFI_SHUTDOWN_EN |
		//BIT_PD_CA7_C3_DBG_SHUTDOWN_EN |
		BIT_PD_CA7_C3_FORCE_SHUTDOWN |
		//BIT_PD_CA7_C3_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_C3_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_C3_PWR_ON_SEQ_DLY(0x04) |
		BITS_PD_CA7_C3_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_AP_SYS_CFG,
		//BIT_PD_AP_SYS_FORCE_SHUTDOWN |
		BIT_PD_AP_SYS_AUTO_SHUTDOWN_EN |
		BITS_PD_AP_SYS_PWR_ON_DLY(0x08) |
		BITS_PD_AP_SYS_PWR_ON_SEQ_DLY(0x00) |
		BITS_PD_AP_SYS_ISO_ON_DLY(0x06) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_CFG ,
		BIT_PD_GPU_TOP_FORCE_SHUTDOWN |
		//BIT_PD_GPU_TOP_AUTO_SHUTDOWN_EN |
		BITS_PD_GPU_TOP_PWR_ON_DLY(0x08) |
		BITS_PD_GPU_TOP_PWR_ON_SEQ_DLY(0x00) |
		BITS_PD_GPU_TOP_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_MM_TOP_CFG,
		BIT_PD_MM_TOP_FORCE_SHUTDOWN |
		//BIT_PD_MM_TOP_AUTO_SHUTDOWN_EN |
		BITS_PD_MM_TOP_PWR_ON_DLY(0x08) |
		BITS_PD_MM_TOP_PWR_ON_SEQ_DLY(0x00) |
		BITS_PD_MM_TOP_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP1_CA5_CFG,
		//BIT_PD_CP1_CA5_FORCE_SHUTDOWN |
		BIT_PD_CP1_CA5_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_CA5_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_CA5_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_CA5_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP1_LTE_P1_CFG,
		//BIT_PD_CP1_LTE_P1_FORCE_SHUTDOWN |
		BIT_PD_CP1_LTE_P1_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_LTE_P1_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_LTE_P1_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_LTE_P1_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP1_LTE_P2_CFG,
		//BIT_PD_CP1_LTE_P2_FORCE_SHUTDOWN |
		BIT_PD_CP1_LTE_P2_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_LTE_P2_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_LTE_P2_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_LTE_P2_ISO_ON_DLY(0x04) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_CP1_CEVA_CFG,
		//BIT_PD_CP1_CEVA_FORCE_SHUTDOWN |
		BIT_PD_CP1_CEVA_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_CEVA_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_CEVA_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_CEVA_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP1_COMWRAP_CFG,
		//BIT_PD_CP1_COMWRAP_FORCE_SHUTDOWN |
		BIT_PD_CP1_COMWRAP_AUTO_SHUTDOWN_EN |
		BITS_PD_CP1_COMWRAP_PWR_ON_DLY(0x08) |
		BITS_PD_CP1_COMWRAP_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CP1_COMWRAP_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_PUB_SYS_CFG,
		//BIT_PD_PUB_SYS_FORCE_SHUTDOWN |
		BIT_PD_PUB_SYS_AUTO_SHUTDOWN_EN |
		BITS_PD_PUB_SYS_PWR_ON_DLY(0x08) |
		BITS_PD_PUB_SYS_PWR_ON_SEQ_DLY(0x00) |
		BITS_PD_PUB_SYS_ISO_ON_DLY(0x06) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_TOP_CFG,
		//BIT_PD_CA7_TOP_DBG_SHUTDOWN_EN |
		//BIT_PD_CA7_TOP_FORCE_SHUTDOWN |
		BIT_PD_CA7_TOP_AUTO_SHUTDOWN_EN |
		BITS_PD_CA7_TOP_PWR_ON_DLY(0x08) |
		BITS_PD_CA7_TOP_PWR_ON_SEQ_DLY(0x02) |
		BITS_PD_CA7_TOP_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTL_WAIT_CNT,
		BITS_XTL1_WAIT_CNT(0x39) |
		BITS_XTL0_WAIT_CNT(0x39) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTLBUF_WAIT_CNT,
		BITS_XTLBUF1_WAIT_CNT(7) |
		BITS_XTLBUF0_WAIT_CNT(7) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT1,
		BITS_LTEPLL_WAIT_CNT(7) |
		BITS_TWPLL_WAIT_CNT(7) |
		BITS_DPLL_WAIT_CNT(7) |
		BITS_MPLL_WAIT_CNT(7) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT2,
		BITS_LVDSDIS_PLL_WAIT_CNT(7) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG0,
		BITS_VCP0_PWR_WAIT_CNT(8) |
		BITS_CP1_PWR_WAIT_CNT(8) |
		BITS_CP0_PWR_WAIT_CNT(8) |
		BITS_AP_PWR_WAIT_CNT(0x17) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG1,
		BITS_ARM7_PWR_WAIT_CNT(8) |
		BITS_VCP1_PWR_WAIT_CNT(8) |
		0
	);
#endif
#endif
}


static void setup_autopd_mode(void)
{
	/*enable the emc auto gate en*/
	CHIP_REG_SET(REG_AON_APB_EMC_AUTO_GATE_EN,
		BIT_CP1_PUB_AUTO_GATE_EN |
		BIT_CP0_PUB_AUTO_GATE_EN |
		BIT_AP_PUB_AUTO_GATE_EN  |
		BIT_AON_APB_PUB_AUTO_GATE_EN |
		BIT_CP1_EMC_AUTO_GATE_EN |
		BIT_CP0_EMC_AUTO_GATE_EN |
		//BIT_AP_EMC_AUTO_GATE_EN |
		BIT_CA7_EMC_AUTO_GATE_EN |
		0
	);
}

static void dcdc_optimize_config(unsigned int para)
{
#if defined(CONFIG_ADIE_SC2723S) || defined(CONFIG_ADIE_SC2723)
	unsigned short dcdc_ctrl[]={
		0x1a80,/*core*/
		0x1a80,/*mem*/
		0x1c80,/*gen*/
		0x1a80,/*arm*/
		0x1a80,/*wpa*/
		0x1a80,/*rf*/
		0x1a80,/*con*/
		0x0808,/*mem & core*/
		0x0a08,/*arm & gen*/
		0x0808,/*con & rf*/
		//0x3008 /*wpa*/
	};
	unsigned int i;
	for(i=0;i<sizeof(dcdc_ctrl)/sizeof(dcdc_ctrl[0]);i++)
	{
		sci_adi_write(ANA_REG_GLB_DCDC_CTRL0 + (i << 2),dcdc_ctrl[i],0xffff);
	}
#endif
}

struct dcdc_sleep_reg_ctrl{
	volatile unsigned int magic_header;
	volatile unsigned int is_auto_ds;
	volatile unsigned int magic_ender;
};
struct dcdc_sleep_reg_ctrl ds_cfg=
{
	0x11119999,
	0x00000007,
	0x99991111
};
static void dcdc_core_ds_config(unsigned int para)
{
#if defined(CONFIG_ADIE_SC2723S) || defined(CONFIG_ADIE_SC2723)
	uint32 reg_val = 0;
	uint32 dcdc_core_ctl_ds = -1;
	uint32 dcdc_core_cal_ds = -1;
	uint32 dcdc_core_cal_adi = 0;
	uint32 dcdc_core_ctl_adi = -1;
	uint32 reg_val_cal = 0;
	static uint32 step_cal = 3;
	uint32 step_cal_flag = 0;

	static struct dcdc_core_ds_step_info step_info[5]={
		{ANA_REG_GLB_DCDC_SLP_CTRL2, 0,		ANA_REG_GLB_DCDC_SLP_CTRL4, 0},
		{ANA_REG_GLB_DCDC_SLP_CTRL2, 5,		ANA_REG_GLB_DCDC_SLP_CTRL4, 5},
		{ANA_REG_GLB_DCDC_SLP_CTRL2, 10,	ANA_REG_GLB_DCDC_SLP_CTRL4,10},
		{ANA_REG_GLB_DCDC_SLP_CTRL3, 0,		ANA_REG_GLB_DCDC_SLP_CTRL5, 0},
		{ANA_REG_GLB_DCDC_SLP_CTRL3, 5,		ANA_REG_GLB_DCDC_SLP_CTRL5, 5}
	};

	static char dcdc_core_down_volt[]={4,1,1,2,3,5,0,6};
	static char dcdc_core_up_volt[]={6,2,3,4,0,1,7,7};
	uint32 i;
	/*1100,700,800,900,1000,650,1200,1300*/
	static uint32 step_ratio[]={8,8,4,4,4};

	/*sleep dcdc cal transformer for sc2723*/
	dcdc_core_cal_adi = (ANA_REG_GET(ANA_REG_GLB_DCDC_CORE_ADI)) & 0x1F;
	/*step_cal = 3, so 3*3mV=9mV ~ 0.01V*/
	dcdc_core_cal_ds  = dcdc_core_cal_adi+step_cal;

	if(dcdc_core_cal_ds >= 0x1F) {
		/*if cal > 1,set step_cal_flag = 1,carry bit*/
		dcdc_core_cal_ds = dcdc_core_cal_ds - 0x1F;
		step_cal_flag = 0x1;
	} else {
		step_cal_flag = 0;
	}

	reg_val_cal = ANA_REG_GET(ANA_REG_GLB_DCDC_SLP_CTRL1);
	reg_val_cal &= ~ ( 0x1F << 5);
	reg_val_cal |= dcdc_core_cal_ds << 5;

	ANA_REG_SET(ANA_REG_GLB_DCDC_SLP_CTRL1, reg_val_cal);

	/*sleep dcdc ctl transformer for sc2723*/
	dcdc_core_ctl_adi = (ANA_REG_GET(ANA_REG_GLB_DCDC_CORE_ADI) >> 5) & 0x1F;
	if(0x1 == step_cal_flag) {
		/*if step_cal_flag = 1,the ctl will first down and after up, so it no change*/
		dcdc_core_ctl_ds  = dcdc_core_ctl_adi;
		step_cal_flag = 0;
	} else {
		dcdc_core_ctl_ds  = dcdc_core_down_volt[dcdc_core_ctl_adi];
	}

	reg_val = ANA_REG_GET(ANA_REG_GLB_DCDC_SLP_CTRL1);
	reg_val &= ~0x1F;
	reg_val |= dcdc_core_ctl_ds;

	ANA_REG_SET(ANA_REG_GLB_DCDC_SLP_CTRL1, reg_val);

	dcdc_core_ctl_ds = ANA_REG_GET(ANA_REG_GLB_DCDC_SLP_CTRL1) & 0x1F;
	dcdc_core_ctl_adi = (ANA_REG_GET(ANA_REG_GLB_DCDC_CORE_ADI) >> 5) & 0x1F;
	dcdc_core_cal_adi = (ANA_REG_GET(ANA_REG_GLB_DCDC_CORE_ADI)) & 0x1F;

	 if(dcdc_core_ctl_ds < dcdc_core_ctl_adi){
                for(i=0;i<5;i++) {
                        reg_val = dcdc_core_cal_adi + step_ratio[i];
                        if(reg_val <= 0x1F) {
                                sci_adi_write(step_info[i].ctl_reg,dcdc_core_ctl_ds<<step_info[i].ctl_sht,0x1F <<step_info[i].ctl_sht);
                                sci_adi_write(step_info[i].cal_reg,reg_val<<step_info[i].cal_sht,0x1F << step_info[i].cal_sht);
                                dcdc_core_cal_adi = reg_val;
                        } else {
                                sci_adi_write(step_info[i].ctl_reg,dcdc_core_up_volt[dcdc_core_ctl_ds]<<step_info[i].ctl_sht,
                                                                                                0x1F << step_info[i].ctl_sht);
                                sci_adi_write(step_info[i].cal_reg,(reg_val-0x1F)<<step_info[i].cal_sht,0x1F << step_info[i].cal_sht);
                                dcdc_core_ctl_ds = dcdc_core_up_volt[dcdc_core_ctl_ds];
				dcdc_core_cal_adi = reg_val - 0x1F;
                        }
                }
        } else {
                for(i=0;i<5;i++) {
                        /*every step should equal function mode*/
                        sci_adi_write(step_info[i].ctl_reg,dcdc_core_ctl_adi<<step_info[i].ctl_sht,0x1F << step_info[i].ctl_sht);
                        sci_adi_write(step_info[i].cal_reg,dcdc_core_cal_adi<<step_info[i].cal_sht,0x1F << step_info[i].cal_sht);
                }
        }

		reg_val =(ANA_REG_GET(ANA_REG_GLB_CHIP_ID_HIGH) & 0xFFFF) << 16;
		reg_val |= (ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW) & 0xFFFF);

	if(reg_val == 0x2723a000) {
		/*disable the DCDC_CORE_SLEEP_OUT_STEP for sc2723a000 otp no value*/
		ANA_REG_AND(ANA_REG_GLB_DCDC_SLP_CTRL0,~(0x3));
	} else {
		if(0x00000007 == ds_cfg.is_auto_ds) {
			/*enable the DCDC_CORE_SLEEP_OUT_STEP for dcdc core step down */
			ANA_REG_OR(ANA_REG_GLB_DCDC_SLP_CTRL0, 0x3);
		} else {
			/*disable the DCDC_CORE_SLEEP_OUT_STEP */
			ANA_REG_AND(ANA_REG_GLB_DCDC_SLP_CTRL0, ~(0x3));
		}
	}
#endif
}

static void setup_ap_cp_sync_sleep_code(unsigned int start_addr)
{
	unsigned int *sa = (unsigned int*)start_addr;
	/*always on the pub sys power*/
	CHIP_REG_AND(REG_PMU_APB_PD_PUB_SYS_CFG,~(0x3 << 24));
	/*set for indcate phy is alive*/
	CHIP_REG_OR(DDR_PHY_IND_ADDR1,DDR_PHY_IND_PHY_ALIVE);
	/** set flag for indicate phy is alive*/
	CHIP_REG_OR(DDR_PHY_IND_ADDR,DDR_PHY_IND_PHY_ALIVE);
	/* set flag for indicate phy is alive*/
	*(volatile unsigned int*)DDR_PHY_IND_ADDR2 = DDR_PHY_IND_PHY_ALIVE;
	/*close umctl and phy and publ auto retention*/
	*(volatile unsigned int*)REG_PMU_APB_DDR_OP_MODE_CFG &= ~((0x3 << 27)|(0x1 << 25));
}

void CSP_Init(unsigned int gen_para)
{
	unsigned int reg_val;
	setup_autopd_mode();
	pmu_commom_config();
	//calibrate_register_callback((void*)dcdc_core_ds_config);
	dcdc_core_ds_config(0x00000000);
	setup_ap_cp_sync_sleep_code(0x50001800);
	dcdc_optimize_config(0x00000000);
	/*open adi clock auto gate for power consume*/
//	reg_val = readl(ADI_GSSI_CTL0);
//	reg_val &= ~(0x1 << 30);
//	writel(reg_val,ADI_GSSI_CTL0);
	/*disable int ana dcd otp interrupt*/
//	ANA_REG_AND(REG_ANA_INTC_INT_EN,~BIT_DCDCOTP_INT_EN);
}
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

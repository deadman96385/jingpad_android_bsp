/******************************************************************************
 ** File Name:      pmu.c                                             *
 ** Author:         bruce_kui.wang                                             *
 ** DATE:           17/09/2016                                                *
 ** Copyright:      2016 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic information on chip.          *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 04/11/2014     Chris               Create.                                *
 ** 17/09/2016	   Bruce_kui           Code for iwhale2
 ******************************************************************************/

/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/
#include <asm/io.h>
#include <asm/arch/common.h>
#include "adi_hal_internal.h"
#include "asm/arch/sprd_reg.h"
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
#if 0
struct dcdc_core_ds_step_info{
	u32 ctl_reg;
	u32 ctl_sht;
	u32 cal_reg;
	u32 cal_sht;
};
#endif

void fixup_pmic_items(void)
{
      //add code here
}

#ifndef CONFIG_FPGA
void pmu_common_config(void)
{
	uint32_t reg_val;

	CHIP_REG_SET(REG_PMU_APB_CGM_PMU_SEL_CFG,
		BIT_PMU_APB_CGM_PMU_SEL_REG(0x01) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_TOP_PWR_CFG,
		//BIT_PMU_APB_PD_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_TOP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_TOP_PWR_ON_SEQ_DLY(0x00) |
		BIT_PMU_APB_PD_TOP_ISO_ON_DLY(0x0C) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_AON_SYS_PWR_CFG,
		//BIT_PMU_APB_AON_WAKEUP_POR |
		//BIT_PMU_APB_PD_AON_SYS_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_AON_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_AON_SYS_PWR_ON_DLY(0x00) |
		BIT_PMU_APB_PD_AON_SYS_PWR_ON_SEQ_DLY(0x00) |
		BIT_PMU_APB_PD_AON_SYS_ISO_ON_DLY(0x00) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_PUBCP_SYS_PWR_CFG,
		//BIT_PMU_APB_PD_PUBCP_SYS_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_PUBCP_SYS_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_P4_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_LTE_P4_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P4_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LTE_P4_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P4_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LTE_P4_PWR_ON_SEQ_DLY(0x05) |
		BIT_PMU_APB_PD_WTLCP_LTE_P4_ISO_ON_DLY(0x07) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_TGDSP_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_TGDSP_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_WTLCP_TGDSP_PD_SEL |		//default configure:0
		BIT_PMU_APB_PD_WTLCP_TGDSP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_TGDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_SEQ_DLY(0x0B) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_ISO_ON_DLY(0x01) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_HU3GE_B_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_HU3GE_B_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_HU3GE_B_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_SEQ_DLY(0x07) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_ISO_ON_DLY(0x03) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_AP_SYS_PWR_CFG,
		//BIT_PMU_APB_PD_AP_SYS_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_AP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_AP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_AP_SYS_ISO_ON_DLY(0x02) |
		0
	);

	reg_val	= CHIP_REG_GET(REG_PMU_APB_PD_PUB0_SYS_PWR_CFG) & 0xff000000;
	CHIP_REG_SET(REG_PMU_APB_PD_PUB0_SYS_PWR_CFG,
		//BIT_PMU_APB_PD_PUB0_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_PUB0_SYS_AUTO_SHUTDOWN_EN |
		//reg_val |
		BIT_PMU_APB_PD_PUB0_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_PUB0_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_PUB0_SYS_ISO_ON_DLY(0x04) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_P1_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_LTE_P1_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LTE_P1_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_ISO_ON_DLY(0x0A) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_VSP_SYS_PWR_CFG,
		//BIT_PMU_APB_PD_VSP_SYS_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_VSP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_VSP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_VSP_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_VSP_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_VSP_SYS_ISO_ON_DLY(0x02) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LDSP_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_LDSP_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_WTLCP_LDSP_PD_SEL |   		//default configure:0
		BIT_PMU_APB_PD_WTLCP_LDSP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_SEQ_DLY(0x0A) |
		BIT_PMU_APB_PD_WTLCP_LDSP_ISO_ON_DLY(0x02) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_PWR_CFG1,
		//BIT_PMU_APB_PD_GPU_TOP_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_GPU_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_GPU_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_GPU_TOP_ISO_ON_DLY(0x02) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_PWR_CFG0,
		BIT_PMU_APB_PD_GPU_TOP_SHUTDOWN_DLY(0x01) |
		BIT_PMU_APB_PD_GPU_TOP_RST_ASSERT_DLY(0x01) |
		BIT_PMU_APB_PD_GPU_TOP_RST_DEASSERT_DLY(0x01) |
		BIT_PMU_APB_PD_GPU_TOP_ISO_OFF_DLY(0x01) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_TD_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_TD_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_TD_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_TD_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_TD_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_TD_PWR_ON_SEQ_DLY(0x06) |
		BIT_PMU_APB_PD_WTLCP_TD_ISO_ON_DLY(0x06) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_BIA_PWR_CFG0,
		BIT_PMU_APB_PD_BIA_EFUSE_SENSE_BYPASS | //set 1
		//BIT_PMU_APB_PD_BIA_S0IX_SLP_ENA | 	//default configure
		//BIT_PMU_APB_PD_BIA_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_BIA_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_BIA_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_BIA_CORE_ON_DLY(0x01) |
		BIT_PMU_APB_PD_BIA_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_BIA_ISO_ON_DLY(0x03) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_BIA_PWR_CFG1,
		BIT_PMU_APB_PD_BIA_CGM_ON_DLY(0x3C) |
		BIT_PMU_APB_PD_BIA_CGM_OFF_DLY(0x01) |
		BIT_PMU_APB_PD_BIA_CORE_OFF_DLY(0x01) |
		BIT_PMU_APB_PD_BIA_ISO_OFF_DLY(0x01) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_BIA_PWR_CFG2,
		BIT_PMU_APB_PD_BIA_CPU_ON_DLY(0x96) |
		BIT_PMU_APB_PD_BIA_EFUSE_SENSE_DLY(0x01) |
		BIT_PMU_APB_PD_BIA_CPU_POWER_DLY(0x03) |
		BIT_PMU_APB_PD_BIA_TAP_POWER_DLY(0x01) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_BIA_PWR_CFG3,
		BIT_PMU_APB_PD_BIA_L2_ON_DLY(0x96) |
		BIT_PMU_APB_PD_BIA_L2_OFF_DLY(0xFA) |
		BIT_PMU_APB_PD_BIA_PLL_ON_DLY(0x0A) |
		BIT_PMU_APB_PD_BIA_PLL_OFF_DLY(0x01) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_BIA_PWR_CFG4,
		BIT_PMU_APB_PD_BIA_CPU_OFF_DLY(0xFA) |
		BIT_PMU_APB_PD_BIA_S0IX_CGM_ON_DLY(0x0D) |
		BIT_PMU_APB_PD_BIA_S0IX_CGM_OFF_DLY(0x01) |
		BIT_PMU_APB_PD_BIA_S0IX_WKUP_ASSERTON_DLY(0x01) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_BIA_PWR_CFG5,
		BIT_PMU_APB_PD_BIA_S0IX_DVFS_PWU_DLY(0x87) |
		BIT_PMU_APB_PD_BIA_S0IX_WKUP_DEASSERTOFF_DLY(0x01) |
		BIT_PMU_APB_PD_BIA_S0IX_WKUP_DEASSERTON_DLY(0x01) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_BIA_PWR_CFG6,
		BIT_PMU_APB_PD_BIA_CLK_UNLOCK_DLY(0x00) |
		BIT_PMU_APB_PD_BIA_CLK_LOCK_DLY(0x00) |
		//BIT_PMU_APB_PD_BIA_PWR_ON_HALT_DEBUG_MASK | 	//default congifure:0
		//BIT_PMU_APB_PD_BIA_S3_HALT_DEBUG_EN | 		//default configure:0
		//BIT_PMU_APB_PD_BIA_HALT_DEBUG_EXIT | 			//default configure:0
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_P3_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_LTE_P3_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P3_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LTE_P3_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P3_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LTE_P3_PWR_ON_SEQ_DLY(0x04) |
		BIT_PMU_APB_PD_WTLCP_LTE_P3_ISO_ON_DLY(0x08) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_SYS_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_SYS_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_SYS_ISO_ON_DLY(0x0B) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_P2_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_LTE_P2_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P2_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LTE_P2_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_P2_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LTE_P2_PWR_ON_SEQ_DLY(0x3) |
		BIT_PMU_APB_PD_WTLCP_LTE_P2_ISO_ON_DLY(0x09) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_CAM_SYS_PWR_CFG,
		//BIT_PMU_APB_PD_CAM_SYS_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CAM_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CAM_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CAM_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CAM_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_CAM_SYS_ISO_ON_DLY(0x02) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_ISP_TOP_PWR_CFG,
		//BIT_PMU_APB_PD_ISP_TOP_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_ISP_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_ISP_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_ISP_TOP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_ISP_TOP_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_ISP_TOP_ISO_ON_DLY(0x01) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_HU3GE_A_PWR_CFG,
		//BIT_PMU_APB_PD_WTLCP_HU3GE_A_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_HU3GE_A_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_SEQ_DLY(0x08) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_ISO_ON_DLY(0x04) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_XTL_WAIT_CNT0,
		BIT_PMU_APB_XTL0_WAIT_CNT(0x50) |
		BIT_PMU_APB_RC_WAIT_CNT(0x1E) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_XTLBUF_WAIT_CNT0,
		BIT_PMU_APB_XTLBUF0_WAIT_CNT(0x01) |
		BIT_PMU_APB_XTLBUF1_WAIT_CNT(0x08) |  //default configure: 0x8
		BIT_PMU_APB_XTLBUF2_WAIT_CNT(0x08) |  //default configure: 0x8
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT1,
		BIT_PMU_APB_MPLL0_WAIT_CNT(0x08) |
		BIT_PMU_APB_DPLL0_WAIT_CNT(0x08) |
		BIT_PMU_APB_DPLL1_WAIT_CNT(0x64) |   //default configure: 0x64
		BIT_PMU_APB_GPLL_WAIT_CNT(0x08) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT2,
		BIT_PMU_APB_MPLL2_WAIT_CNT(0x08) |
		BIT_PMU_APB_MPLL1_WAIT_CNT(0x08) |
		BIT_PMU_APB_DSPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_RPLL1_WAIT_CNT(0x64) |  //default configure: 0x64
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT3,
		BIT_PMU_APB_RPLL0_WAIT_CNT(0x08) |
		BIT_PMU_APB_LPLL0_WAIT_CNT(0x08) |
		BIT_PMU_APB_ISPPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_TWPLL_WAIT_CNT(0x08) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_WAIT_CNT_CFG1,
		//BIT_PMU_APB_AGCP_SYS_PWR_WAIT_CNT(0x01) | //not used, default configure: 0
		BIT_PMU_APB_WTLCP_SYS_PWR_WAIT_CNT(0x01) |
		BIT_PMU_APB_CM4_SYS_PWR_WAIT_CNT(0x01) |
		BIT_PMU_APB_AP_SYS_PWR_WAIT_CNT(0x09) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_WAIT_CNT_CFG0,
		BIT_PMU_APB_PUBCP_SYS_PWR_WAIT_CNT(0x00) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_PD_WAIT_CNT_CFG1,
		//BIT_PMU_APB_AGCP_SYS_PWR_PD_WAIT_CNT(0x07) |  //not used
		BIT_PMU_APB_WTLCP_SYS_PWR_PD_WAIT_CNT(0x07) |
		BIT_PMU_APB_CM4_SYS_PWR_PD_WAIT_CNT(0x00) |
		BIT_PMU_APB_AP_SYS_PWR_PD_WAIT_CNT(0x00) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_PD_WAIT_CNT_CFG0,
		BIT_PMU_APB_PUBCP_SYS_PWR_PD_WAIT_CNT(0x07) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_ST_DBG_DLY0,
		BIT_PMU_APB_CGM_OFF_DLY(0x00) |
		BIT_PMU_APB_CGM_ON_DLY(0x00) |
		BIT_PMU_APB_ISO_OFF_DLY(0x00) |
		BIT_PMU_APB_RST_DEASSERT_DLY(0x00) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_ST_DBG_DLY1,
		BIT_PMU_APB_SHUTDOWN_M_D_DLY(0x00) |
		BIT_PMU_APB_RST_ASSERT_DLY(0x00) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_ST_DBG_DLY2,
		BIT_PMU_APB_PWR_ST_CLK_DIV_CFG(0x0F) |
		BIT_PMU_APB_SLP_CTRL_CLK_DIV_CFG(0x80) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_DDR0_SLP_CFG,
		//BIT_PMU_APB_DDR0_PWR_DOWN_WAIT_CNT(0x0F) |  //default configure: 0
		BIT_PMU_APB_DDR0_SLEEP_WAIT_CNT(0x64) |
		0
	);

	CHIP_REG_OR(REG_COM_PMU_APB_USB3PHY_DISCONNECT_CTRL,
		BIT_COM_PMU_APB_USB3PHY_DISCONNECT |
		0
	);

	//add as cp required
	CHIP_REG_AND(REG_COM_PMU_APB_LDO_PWR_CTRL0,
		~(BIT_COM_PMU_APB_LDO1P2_FRC_ON |
		BIT_COM_PMU_APB_LDO1P2PLL_FRC_ON)
	);

	//add as cp required
	CHIP_REG_OR(REG_COM_PMU_APB_LDO_PWR_CTRL0,
		BIT_COM_PMU_APB_LDO1P2_SLP_PD_EN |
		BIT_COM_PMU_APB_LDO1P2PLL_SLP_PD_EN |
		0
	);
}


static void dcdc_core_ds_config(uint32_t core_cal_para, uint32_t core_ctrl_para)
{
	ANA_REG_SET(ANA_REG_GLB_DCDC_CORE_SLP_CTRL1,
		BITS_DCDC_CORE_CAL_DS_SW(core_cal_para)|
		BITS_DCDC_CORE_CTRL_DS_SW(core_ctrl_para)
	);
}


void CSP_Init(uint32_t gen_para)
{
	uint32_t reg_val;
	//setup_autopd_mode();
	pmu_common_config();
	dcdc_core_ds_config(0x10,0x2); //cali:16,ctl:0x2,vol:16*100/32mv+(400+2*100)=0.65V
}

#endif

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif



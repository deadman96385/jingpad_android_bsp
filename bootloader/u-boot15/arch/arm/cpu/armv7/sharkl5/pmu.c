/******************************************************************************
 ** File Name:      pmu.c                                                     *
 ** Author:         Deven.Sheng                                               *
 ** DATE:           16/11/2018                                                *
 ** Copyright:      2018 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic information on chip.          *
 ******************************************************************************/
#include <asm/io.h>
#include "adi_hal_internal.h"
#include "asm/arch-sharkl5/sprd_reg.h"
#include "asm/arch-sharkl5/common.h"


#define AON_IDLE_CLK_RCO_4M	0
#define AON_IDLE_CLK_4M_AON	1
#define AON_IDLE_CLK_13M_AON	2
#define AON_IDLE_CLK_RCO_25M	3
#define AON_IDLE_CLK_26M_AON	4
#define AON_IDLE_CLK_96M	5
#define AON_IDLE_CLK_RCO_100M	6
#define AON_IDLE_CLK_128M	7


// PMU power on/off sequence
void pmu_sequence_config(void)
{
	/* Sharkl5v2 low power typical parameter.xls 2019.02.11 4M */

	CHIP_REG_SET(REG_PMU_APB_PD_APCPU_TOP_CFG,
		//BIT_PMU_APB_PD_APCPU_TOP_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_TOP_PD_SEL |
		//BIT_PMU_APB_PD_APCPU_TOP_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_APCPU_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_TOP_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_APCPU_TOP_PWR_ON_SEQ_DLY(2) |
		BIT_PMU_APB_PD_APCPU_TOP_ISO_ON_DLY(30) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_APCPU_C0_CFG,
		//BIT_PMU_APB_PD_APCPU_C0_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_APCPU_C0_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_C0_PD_SEL |
		//BIT_PMU_APB_PD_APCPU_C0_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_APCPU_C0_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_C0_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_APCPU_C0_PWR_ON_SEQ_DLY(40) |
		BIT_PMU_APB_PD_APCPU_C0_ISO_ON_DLY(8) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_APCPU_C1_CFG,
		//BIT_PMU_APB_PD_APCPU_C1_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_APCPU_C1_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_C1_PD_SEL |
		BIT_PMU_APB_PD_APCPU_C1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_APCPU_C1_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_C1_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_APCPU_C1_PWR_ON_SEQ_DLY(39) |
		BIT_PMU_APB_PD_APCPU_C1_ISO_ON_DLY(9) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_APCPU_C2_CFG,
		//BIT_PMU_APB_PD_APCPU_C2_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_APCPU_C2_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_C2_PD_SEL |
		BIT_PMU_APB_PD_APCPU_C2_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_APCPU_C2_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_C2_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_APCPU_C2_PWR_ON_SEQ_DLY(38) |
		BIT_PMU_APB_PD_APCPU_C2_ISO_ON_DLY(10) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_APCPU_TOP_CFG2,
		BIT_PMU_APB_PD_APCPU_TOP_DCDC_PWR_ON_DLY(8) |
		BIT_PMU_APB_PD_APCPU_TOP_DCDC_PWR_OFF_DLY(8) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_AP_VSP_CFG,
		BIT_PMU_APB_PD_AP_VSP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_AP_VSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_AP_VSP_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_AP_VSP_PWR_ON_SEQ_DLY(4) |
		BIT_PMU_APB_PD_AP_VSP_ISO_ON_DLY(2) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_AP_SYS_CFG,
		//BIT_PMU_APB_PD_AP_SYS_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_AP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_SEQ_DLY(1) |
		BIT_PMU_APB_PD_AP_SYS_ISO_ON_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_MM_TOP_CFG,
		//BIT_PMU_APB_PD_MM_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_MM_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_MM_TOP_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_MM_TOP_PWR_ON_SEQ_DLY(2) |
		BIT_PMU_APB_PD_MM_TOP_ISO_ON_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GPU_RGX_DUST_CFG0,
		//BIT_PMU_APB_PD_GPU_RGX_DUST_PWRUP_ABORT |
		//BIT_PMU_APB_PD_GPU_RGX_DUST_PWRDWN_ABORT |
		//BIT_PMU_APB_PD_GPU_RGX_DUST_PD_SEL |
		BIT_PMU_APB_PD_GPU_RGX_DUST_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_GPU_RGX_DUST_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_GPU_RGX_DUST_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_GPU_RGX_DUST_PWR_ON_SEQ_DLY(40) |
		BIT_PMU_APB_PD_GPU_RGX_DUST_ISO_ON_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GPU_RGX_DUST_CFG1,
		BIT_PMU_APB_PD_GPU_RGX_DUST_SHUTDOWN_DLY(1) |
		BIT_PMU_APB_PD_GPU_RGX_DUST_RST_DEASSERT_DLY(1) |
		BIT_PMU_APB_PD_GPU_RGX_DUST_RST_ASSERT_DLY(1) |
		BIT_PMU_APB_PD_GPU_RGX_DUST_ISO_OFF_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_CFG0,
		//BIT_PMU_APB_PD_GPU_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_GPU_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_SEQ_DLY(1) |
		BIT_PMU_APB_PD_GPU_TOP_ISO_ON_DLY(2) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_CE_CFG,
		//BIT_PMU_APB_PD_WTLCP_LTE_CE_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_WTLCP_LTE_CE_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_CE_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_LTE_CE_PWR_ON_SEQ_DLY(6) |
		BIT_PMU_APB_PD_WTLCP_LTE_CE_ISO_ON_DLY(6) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_DPFEC_CFG,
		//BIT_PMU_APB_PD_WTLCP_LTE_DPFEC_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_WTLCP_LTE_DPFEC_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_DPFEC_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_LTE_DPFEC_PWR_ON_SEQ_DLY(10) |
		BIT_PMU_APB_PD_WTLCP_LTE_DPFEC_ISO_ON_DLY(2) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LDSP_CFG,
		//BIT_PMU_APB_PD_WTLCP_LDSP_PD_SEL |
		//BIT_PMU_APB_PD_WTLCP_LDSP_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_WTLCP_LDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_SEQ_DLY(26) |
		BIT_PMU_APB_PD_WTLCP_LDSP_ISO_ON_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_TGDSP_CFG,
		//BIT_PMU_APB_PD_WTLCP_TGDSP_PD_SEL |
		//BIT_PMU_APB_PD_WTLCP_TGDSP_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_WTLCP_TGDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_SEQ_DLY(25) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_ISO_ON_DLY(2) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_HU3GE_A_CFG,
		//BIT_PMU_APB_PD_WTLCP_HU3GE_A_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_SEQ_DLY(8) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_ISO_ON_DLY(4) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_HU3GE_B_CFG,
		//BIT_PMU_APB_PD_WTLCP_HU3GE_B_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_PWR_ON_SEQ_DLY(9) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_B_ISO_ON_DLY(3) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_PROC_CFG,
		//BIT_PMU_APB_PD_WTLCP_LTE_PROC_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_WTLCP_LTE_PROC_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LTE_PROC_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_LTE_PROC_PWR_ON_SEQ_DLY(2) |
		BIT_PMU_APB_PD_WTLCP_LTE_PROC_ISO_ON_DLY(10) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_TD_PROC_CFG,
		//BIT_PMU_APB_PD_WTLCP_TD_PROC_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_WTLCP_TD_PROC_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_TD_PROC_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_TD_PROC_PWR_ON_SEQ_DLY(4) |
		BIT_PMU_APB_PD_WTLCP_TD_PROC_ISO_ON_DLY(8) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_SYS_CFG,
		BIT_PMU_APB_PD_WTLCP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_SEQ_DLY(1) |
		BIT_PMU_APB_PD_WTLCP_SYS_ISO_ON_DLY(5) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_PUBCP_SYS_CFG,
		//BIT_PMU_APB_PD_PUBCP_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_SEQ_DLY(1) |
		BIT_PMU_APB_PD_PUBCP_SYS_ISO_ON_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_AUDCP_AUDDSP_CFG,
		//BIT_PMU_APB_PD_AUDCP_AUDDSP_PD_SEL |
		//BIT_PMU_APB_PD_AUDCP_AUDDSP_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_AUDCP_AUDDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_AUDCP_AUDDSP_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_AUDCP_AUDDSP_PWR_ON_SEQ_DLY(3) |
		BIT_PMU_APB_PD_AUDCP_AUDDSP_ISO_ON_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_AUDCP_SYS_CFG,
		BIT_PMU_APB_PD_AUDCP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_AUDCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_AUDCP_SYS_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_AUDCP_SYS_PWR_ON_SEQ_DLY(1) |
		BIT_PMU_APB_PD_AUDCP_SYS_ISO_ON_DLY(3) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CDMA_SYS_CFG,
		//BIT_PMU_APB_PD_CDMA_SYS_MEM_RET_SEL |
		//BIT_PMU_APB_PD_CDMA_SYS_MEM_RET_REG |
		BIT_PMU_APB_PD_CDMA_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CDMA_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CDMA_SYS_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_CDMA_SYS_PWR_ON_SEQ_DLY(1) |
		BIT_PMU_APB_PD_CDMA_SYS_ISO_ON_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_PUB_SYS_CFG,
		//BIT_PMU_APB_PD_PUB_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_PUB_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUB_SYS_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_PUB_SYS_PWR_ON_SEQ_DLY(1) |
		BIT_PMU_APB_PD_PUB_SYS_ISO_ON_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTL_WAIT_CNT,
		BIT_PMU_APB_XTLBUF1_WAIT_CNT(1) |
		BIT_PMU_APB_XTLBUF0_WAIT_CNT(1) |
		BIT_PMU_APB_XTL1_WAIT_CNT(70) |
		BIT_PMU_APB_XTL0_WAIT_CNT(70) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT0,
		BIT_PMU_APB_MPLL2_WAIT_CNT(30) |
		BIT_PMU_APB_MPLL1_WAIT_CNT(30) |
		BIT_PMU_APB_MPLL0_WAIT_CNT(30) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT1,
		BIT_PMU_APB_LTEPLL_WAIT_CNT(40) |
		BIT_PMU_APB_TWPLL_WAIT_CNT(40) |
		BIT_PMU_APB_DPLL1_WAIT_CNT(40) |
		BIT_PMU_APB_DPLL0_WAIT_CNT(4) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT2,
		BIT_PMU_APB_ISPPLL_WAIT_CNT(40) |
		BIT_PMU_APB_RPLL_WAIT_CNT(40) |
		BIT_PMU_APB_GPLL_WAIT_CNT(40) |
		BIT_PMU_APB_CPPLL_WAIT_CNT(40) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_CPPLL_RST_CTRL_CFG,
		//BIT_PMU_APB_CPPLL_RST_CTRL_BYPASS |
		BIT_PMU_APB_CPPLL_DELAY_PWR_ON(104) |
		BIT_PMU_APB_CPPLL_DELAY_EN_OFF(4) |
		BIT_PMU_APB_CPPLL_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG0,
		BIT_PMU_APB_AUDCP_PWR_WAIT_CNT(8) |
		BIT_PMU_APB_PUBCP_PWR_WAIT_CNT(8) |
		BIT_PMU_APB_WTLCP_PWR_WAIT_CNT(8) |
		BIT_PMU_APB_AP_PWR_WAIT_CNT(8) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG1,
		BIT_PMU_APB_CDMA_PWR_WAIT_CNT(8) |
		BIT_PMU_APB_SP_SYS_PWR_WAIT_CNT(40) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_RCO_CNT_WAIT_CFG,
		BIT_PMU_APB_RCO_WAIT_CNT(11) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PMU_CLK_DIV_CFG,
		BIT_PMU_APB_PWR_ST_CLK_DIV_CFG(15) |
		BIT_PMU_APB_SLP_CTRL_CLK_DIV_CFG(128) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_DGB_PARAMETER,
		BIT_PMU_APB_RAM_PWR_DLY(1) |
		BIT_PMU_APB_ISO_OFF_DLY(1) |
		BIT_PMU_APB_CGM_ON_DLY(1) |
		BIT_PMU_APB_RST_ASSERT_DLY(1) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_ANALOG_PHY_PD_CFG,
		//BIT_PMU_APB_CSI_2P2LANE_PD_REG |
		BIT_PMU_APB_PHY_PWR_DLY(1) |
		//BIT_PMU_APB_DSI_PD_REG |
		//BIT_PMU_APB_USB2PHY_PD_REG |
		//BIT_PMU_APB_CSI_4LANE_PD_REG |
		//BIT_PMU_APB_CSI_2LANE_PD_REG |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_APCPU_C7_CFG,
		//BIT_PMU_APB_PD_APCPU_C7_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_APCPU_C7_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_C7_PD_SEL |
		BIT_PMU_APB_PD_APCPU_C7_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_APCPU_C7_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_APCPU_C7_PWR_ON_DLY(1) |
		BIT_PMU_APB_PD_APCPU_C7_PWR_ON_SEQ_DLY(3) |
		BIT_PMU_APB_PD_APCPU_C7_ISO_ON_DLY(2) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_APCPU_TOP_CFG3,
		BIT_PMU_APB_APCPU_C7_RAM_PWR_DLY(2) |
		BIT_PMU_APB_PD_APCPU_C7_DCDC_PWR_ON_DLY(15) |
		BIT_PMU_APB_PD_APCPU_C7_DCDC_PWR_OFF_DLY(15) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_APCPU_TOP_RMA_CTRL,
		BIT_PMU_APB_APCPU_TOP_RAM_PWR_DLY(2) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_APCPU_MODE_ST_CFG,
		BIT_PMU_APB_APCPU_CORINTH_RAM_PWR_DLY(1) |
		BIT_PMU_APB_APCPU_CORE_RAM_PWR_DLY(1) |
		BIT_PMU_APB_APCPU_CORE_INITIAL_DLY(10) |
		BIT_PMU_APB_APCPU_CORINTH_INITIAL_DLY(10) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_CFG1,
		BIT_PMU_APB_PD_GPU_TOP_SHUTDOWN_DLY(0) |
		BIT_PMU_APB_PD_GPU_TOP_RST_DEASSERT_DLY(0) |
		BIT_PMU_APB_PD_GPU_TOP_RST_ASSERT_DLY(0) |
		BIT_PMU_APB_PD_GPU_TOP_ISO_OFF_DLY(0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_MPLL_WAIT_CLK_DIV_CFG,
		BIT_PMU_APB_MPLL_WAIT_CLK_DIV_CFG(0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_MPLL0_RST_CTRL_CFG,
		//BIT_PMU_APB_MPLL0_RST_CTRL_BYPASS |
		BIT_PMU_APB_MPLL0_DELAY_PWR_ON(104) |
		BIT_PMU_APB_MPLL0_DELAY_EN_OFF(4) |
		BIT_PMU_APB_MPLL0_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_MPLL1_RST_CTRL_CFG,
		//BIT_PMU_APB_MPLL1_RST_CTRL_BYPASS |
		BIT_PMU_APB_MPLL1_DELAY_PWR_ON(104) |
		BIT_PMU_APB_MPLL1_DELAY_EN_OFF(4) |
		BIT_PMU_APB_MPLL1_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_MPLL2_RST_CTRL_CFG,
		//BIT_PMU_APB_MPLL2_RST_CTRL_BYPASS |
		BIT_PMU_APB_MPLL2_DELAY_PWR_ON(104) |
		BIT_PMU_APB_MPLL2_DELAY_EN_OFF(4) |
		BIT_PMU_APB_MPLL2_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_DPLL0_RST_CTRL_CFG,
		//BIT_PMU_APB_DPLL0_RST_CTRL_BYPASS |
		BIT_PMU_APB_DPLL0_DELAY_PWR_ON(104) |
		BIT_PMU_APB_DPLL0_DELAY_EN_OFF(4) |
		BIT_PMU_APB_DPLL0_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_DPLL1_RST_CTRL_CFG,
		//BIT_PMU_APB_DPLL1_RST_CTRL_BYPASS |
		BIT_PMU_APB_DPLL1_DELAY_PWR_ON(104) |
		BIT_PMU_APB_DPLL1_DELAY_EN_OFF(4) |
		BIT_PMU_APB_DPLL1_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_TWPLL_RST_CTRL_CFG,
		//BIT_PMU_APB_TWPLL_RST_CTRL_BYPASS |
		BIT_PMU_APB_TWPLL_DELAY_PWR_ON(104) |
		BIT_PMU_APB_TWPLL_DELAY_EN_OFF(4) |
		BIT_PMU_APB_TWPLL_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_LTEPLL_RST_CTRL_CFG,
		//BIT_PMU_APB_LTEPLL_RST_CTRL_BYPASS |
		BIT_PMU_APB_LTEPLL_DELAY_PWR_ON(104) |
		BIT_PMU_APB_LTEPLL_DELAY_EN_OFF(4) |
		BIT_PMU_APB_LTEPLL_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_GPLL_RST_CTRL_CFG,
		//BIT_PMU_APB_GPLL_RST_CTRL_BYPASS |
		BIT_PMU_APB_GPLL_DELAY_PWR_ON(104) |
		BIT_PMU_APB_GPLL_DELAY_EN_OFF(4) |
		BIT_PMU_APB_GPLL_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_RPLL_RST_CTRL_CFG,
		//BIT_PMU_APB_RPLL_RST_CTRL_BYPASS |
		BIT_PMU_APB_RPLL_DELAY_PWR_ON(104) |
		BIT_PMU_APB_RPLL_DELAY_EN_OFF(4) |
		BIT_PMU_APB_RPLL_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_ISPPLL_RST_CTRL_CFG,
		//BIT_PMU_APB_ISPPLL_RST_CTRL_BYPASS |
		BIT_PMU_APB_ISPPLL_DELAY_PWR_ON(104) |
		BIT_PMU_APB_ISPPLL_DELAY_EN_OFF(4) |
		BIT_PMU_APB_ISPPLL_DELAY_RST_ASSERT(104) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_APCPU_MODE_ST_CFG1,
		BIT_PMU_APB_APCPU_CORE_RST_DEASSERT_DLY(2) |
		BIT_PMU_APB_APCPU_CORE_RST_ASSERT_DLY(2) |
		BIT_PMU_APB_APCPU_CORINTH_RST_DEASSERT_DLY(2) |
		BIT_PMU_APB_APCPU_CORINTH_RST_ASSERT_DLY(2) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_APCPU_MODE_ST_CFG2,
		BIT_PMU_APB_APCPU_CORE_CGM_OFF_DLY(2) |
		BIT_PMU_APB_APCPU_CORE_CGM_ON_DLY(2) |
		0
	);

	//PMU clock source: 0 - 32k, 1 - RCO100/25, 2 - XTL26/6
	CHIP_REG_SET(REG_PMU_APB_CGM_PMU_SEL,
		BIT_PMU_APB_CGM_PMU_SEL_REG(1) |
		0
	);
}

//PMU pad out select config
void pad_out_sel_config(void)
{
	CHIP_REG_SET(REG_PMU_APB_PAD_OUT_CHIP_SLEEP_CFG,
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_CDMA_AUTO_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_CDMA_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_POL_SEL |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_TOP_DVFS_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_PLL_PD_MASK |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_EXT_XTL_PD_MASK |
		BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_SP_SYS_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_AP_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_PUB_SYS_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_APCPU_C7_PD_MASK |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_APCPU_TOP_PD_MASK |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_WTLCP_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_PUBCP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_CHIP_SLEEP_AUDCP_DEEP_SLEEP_MASK |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PAD_OUT_XTL_EN0_CFG,
		BIT_PMU_APB_PAD_OUT_XTL_EN0_CDMA_AUTO_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_CDMA_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_XTL_EN0_POL_SEL |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_TOP_DVFS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_PLL_PD_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_EXT_XTL_PD_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_SP_SYS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_AP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_PUB_SYS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_APCPU_C7_PD_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_APCPU_TOP_PD_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_WTLCP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN0_PUBCP_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_XTL_EN0_AUDCP_DEEP_SLEEP_MASK |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PAD_OUT_XTL_EN1_CFG,
		BIT_PMU_APB_PAD_OUT_XTL_EN1_CDMA_AUTO_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_CDMA_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_XTL_EN1_POL_SEL |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_TOP_DVFS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_PLL_PD_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_EXT_XTL_PD_MASK |
		//BIT_PMU_APB_PAD_OUT_XTL_EN1_SP_SYS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_AP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_PUB_SYS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_APCPU_C7_PD_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_APCPU_TOP_PD_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_WTLCP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_PUBCP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_XTL_EN1_AUDCP_DEEP_SLEEP_MASK |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PAD_OUT_DCDC_ARM0_EN_CFG,
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_CDMA_AUTO_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_CDMA_DEEP_SLEEP_MASK |
		BIT_PMU_APB_DCDC_ARM0_PD_EN |
		//BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_POL_SEL |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_TOP_DVFS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_PLL_PD_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_EXT_XTL_PD_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_SP_SYS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_AP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_PUB_SYS_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_APCPU_C7_PD_MASK |
		//BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_APCPU_TOP_PD_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_WTLCP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_PUBCP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM0_EN_AUDCP_DEEP_SLEEP_MASK |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PAD_OUT_DCDC_ARM1_EN_CFG,
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_CDMA_AUTO_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_CDMA_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_POL_SEL |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_TOP_DVFS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_PLL_PD_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_EXT_XTL_PD_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_SP_SYS_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_AP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_PUB_SYS_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_APCPU_C7_PD_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_APCPU_TOP_PD_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_WTLCP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_PUBCP_DEEP_SLEEP_MASK |
		BIT_PMU_APB_PAD_OUT_DCDC_ARM1_EN_AUDCP_DEEP_SLEEP_MASK |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_DCXO_LP_DEEP_SLEEP_CFG,
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_CDMA_AUTO_DEEP_SLEEP_MASK |
		BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_CDMA_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_POL_SEL |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_TOP_DVFS_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_PLL_PD_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_EXT_XTL_PD_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_SP_SYS_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_AP_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_PUB_SYS_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_APCPU_C7_PD_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_APCPU_TOP_PD_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_WTLCP_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_PUBCP_DEEP_SLEEP_MASK |
		//BIT_PMU_APB_DCXO_LC_DEEP_SLEEP_AUDCP_DEEP_SLEEP_MASK |
		0
	);
}

//AON idle config
void aon_idle_config(void)
{
	uint32_t value = 0U;

	//Get register value and mask bit
	value = CHIP_REG_GET(REG_AON_APB_AON_APB_FREQ_CTRL) | BIT_AON_APB_AON_APB_IDLE_EN;

	//Enable aon idle
	CHIP_REG_SET(REG_AON_APB_AON_APB_FREQ_CTRL, value);

	//4M clock when aon idle
	CHIP_REG_SET(REG_AON_APB_AON_APB_CLK_SEL, AON_IDLE_CLK_RCO_4M);
}

//AON lpc config
void aon_lpc_config(void)
{
#if defined(CONFIG_AON_LPC_EN)
	CHIP_REG_OR(REG_AON_APB_APCPU_CLUSTER_ATB_LPC_CTRL, BIT_AON_APB_APCPU_CLUSTER_ATB_LP_EB);
	CHIP_REG_OR(REG_AON_APB_APCPU_CLUSTER_APB_LPC_CTRL, BIT_AON_APB_APCPU_CLUSTER_APB_LP_EB);
	CHIP_REG_OR(REG_AON_APB_APCPU_CLUSTER_GIC_LPC_CTRL, BIT_AON_APB_APCPU_CLUSTER_GIC_LP_EB);
	CHIP_REG_OR(REG_AON_APB_APCPU_CLUSTER_SCU_LPC_CTRL, BIT_AON_APB_APCPU_CLUSTER_SCU_LP_EB);

	//In WhaleK, Ken recommends not enabled the bit
	//CHIP_REG_OR(REG_AON_APB_APCPU_DBG_BLK_LPC_CTRL, BIT_AON_APB_APCPU_DBG_BLK_LP_EB);
	CHIP_REG_OR(REG_AON_APB_APCPU_DEBUG_PWR_LP_CTRL, BIT_AON_APB_APCPU_LP_EB_DEBUG_PWR);
	CHIP_REG_OR(REG_AON_APB_APCPU_GIC_COL_LP_CTRL, BIT_AON_APB_APCPU_LP_EB_GIC_COL);
	CHIP_REG_OR(REG_AON_APB_APCPU_GIC600_GIC_LPC_CTRL, BIT_AON_APB_APCPU_GIC600_GIC_LP_EB);
	CHIP_REG_OR(REG_AON_APB_APCPU_DDR_AB_LPC_CTRL, BIT_AON_APB_APCPU_DDR_AB_LP_EB);

	CHIP_REG_OR(REG_AON_APB_APCPU_TOP_MTX_M0_LPC_CTRL,
		BIT_AON_APB_APCPU_TOP_MTX_MIAN_LP_EB |
		BIT_AON_APB_APCPU_TOP_MTX_S3_LP_EB |
		BIT_AON_APB_APCPU_TOP_MTX_S2_LP_EB |
		BIT_AON_APB_APCPU_TOP_MTX_S1_LP_EB |
		BIT_AON_APB_APCPU_TOP_MTX_S0_LP_EB |
		BIT_AON_APB_APCPU_TOP_MTX_M3_LP_EB |
		BIT_AON_APB_APCPU_TOP_MTX_M2_LP_EB |
		BIT_AON_APB_APCPU_TOP_MTX_M1_LP_EB |
		BIT_AON_APB_APCPU_TOP_MTX_M0_LP_EB
	);

	CHIP_REG_OR(REG_AON_APB_AON_MTX_M0_LPC_CTRL, BIT_AON_APB_AON_MTX_M0_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_M1_LPC_CTRL, BIT_AON_APB_AON_MTX_M1_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_M2_LPC_CTRL, BIT_AON_APB_AON_MTX_M2_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_M3_LPC_CTRL, BIT_AON_APB_AON_MTX_M3_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_M4_LPC_CTRL, BIT_AON_APB_AON_MTX_M4_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_M5_LPC_CTRL, BIT_AON_APB_AON_MTX_M5_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_M6_LPC_CTRL, BIT_AON_APB_AON_MTX_M6_LP_EB);

	CHIP_REG_OR(REG_AON_APB_AON_MTX_MAIN_LPC_CTRL, BIT_AON_APB_AON_MTX_MAIN_LP_EB);

	CHIP_REG_OR(REG_AON_APB_AON_MTX_S0_LPC_CTRL, BIT_AON_APB_AON_MTX_S0_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_S1_LPC_CTRL, BIT_AON_APB_AON_MTX_S1_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_S2_LPC_CTRL, BIT_AON_APB_AON_MTX_S2_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_S3_LPC_CTRL, BIT_AON_APB_AON_MTX_S3_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_S4_LPC_CTRL, BIT_AON_APB_AON_MTX_S4_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_S5_LPC_CTRL, BIT_AON_APB_AON_MTX_S5_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_S6_LPC_CTRL, BIT_AON_APB_AON_MTX_S6_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_S7_LPC_CTRL, BIT_AON_APB_AON_MTX_S7_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_S8_LPC_CTRL, BIT_AON_APB_AON_MTX_S8_LP_EB);
	CHIP_REG_OR(REG_AON_APB_AON_MTX_S9_LPC_CTRL, BIT_AON_APB_AON_MTX_S9_LP_EB);
#endif
}

// AP lpc config
void ap_lpc_config(void)
{
#if defined(CONFIG_AP_LPC_EN)
	CHIP_REG_OR(REG_AP_AHB_DISP_ASYNC_BRG, BIT_AP_AHB_DISP_ASYNC_BRG_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_AP_ASYNC_BRG, BIT_AP_AHB_AP_ASYNC_BRG_LP_EB);

	CHIP_REG_OR(REG_AP_AHB_MERGE_M0_LPC, BIT_AP_AHB_MERGE_M0_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_MERGE_M1_LPC, BIT_AP_AHB_MERGE_M1_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_MERGE_S0_LPC, BIT_AP_AHB_CGM_MERGE_S0_AUTO_GATE_EN | BIT_AP_AHB_MERGE_S0_LP_EB);

	CHIP_REG_OR(REG_AP_AHB_M0_LPC, BIT_AP_AHB_MAIN_M0_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_M1_LPC, BIT_AP_AHB_MAIN_M1_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_M2_LPC, BIT_AP_AHB_MAIN_M2_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_M3_LPC, BIT_AP_AHB_MAIN_M3_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_M4_LPC, BIT_AP_AHB_MAIN_M4_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_M5_LPC, BIT_AP_AHB_MAIN_M5_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_M6_LPC, BIT_AP_AHB_MAIN_M6_LP_EB);

	CHIP_REG_OR(REG_AP_AHB_MAIN_LPC, BIT_AP_AHB_CGM_MATRIX_AUTO_GATE_EN | BIT_AP_AHB_MAIN_LP_EB);

	CHIP_REG_OR(REG_AP_AHB_S0_LPC, BIT_AP_AHB_CGM_MTX_S0_AUTO_GATE_EN | BIT_AP_AHB_MAIN_S0_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_S1_LPC, BIT_AP_AHB_CGM_MTX_S1_AUTO_GATE_EN | BIT_AP_AHB_MAIN_S1_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_S2_LPC, BIT_AP_AHB_CGM_MTX_S2_AUTO_GATE_EN | BIT_AP_AHB_MAIN_S2_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_S3_LPC, BIT_AP_AHB_CGM_MTX_S3_AUTO_GATE_EN | BIT_AP_AHB_MAIN_S3_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_S4_LPC, BIT_AP_AHB_CGM_MTX_S4_AUTO_GATE_EN | BIT_AP_AHB_MAIN_S4_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_S5_LPC, BIT_AP_AHB_CGM_MTX_S5_AUTO_GATE_EN | BIT_AP_AHB_MAIN_S5_LP_EB);
	CHIP_REG_OR(REG_AP_AHB_S6_LPC, BIT_AP_AHB_CGM_MTX_S6_AUTO_GATE_EN | BIT_AP_AHB_MAIN_S6_LP_EB);
#endif
}

// Clock auto gate
void clock_auto_gate(void)
{
#if defined(CONFIG_CLOCK_AUTO_GATE_EN)
	uint32_t value = 0U;

	CHIP_REG_OR(REG_AON_APB_AUTO_GATE_CTRL0,
		BIT_AON_APB_CGM_AP_AXI_APCPU_AUTO_GATE_SEL |
		BIT_AON_APB_CGM_AP_AXI_AUTO_GATE_SEL|
		BIT_AON_APB_CGM_APCPU_PMU_AUTO_GATE_SEL
	);

	value = CHIP_REG_GET(REG_AON_APB_AUTO_GATE_CTRL0) & ~(BIT_AON_APB_CGM_AP_AXI_FORCE_EN | BIT_AON_APB_CGM_APCPU_PMU_FORCE_EN);
	CHIP_REG_SET(REG_AON_APB_AUTO_GATE_CTRL0, value);

	value = CHIP_REG_GET(REG_AON_APB_AUTO_GATE_CTRL1) & ~BIT_AON_APB_CGM_TOP_DVFS_ROOT_FORCE_EN | BIT_AON_APB_CGM_TOP_DVFS_ROOT_AUTO_GATE_SEL;
	CHIP_REG_SET(REG_AON_APB_AUTO_GATE_CTRL1, value);

	CHIP_REG_OR(REG_AON_APB_AUTO_GATE_CTRL3,
		BIT_AON_APB_CGM_PERIPH_AUTO_GATE_EN |
		BIT_AON_APB_CGM_GIC_AUTO_GATE_EN |
		BIT_AON_APB_CGM_ACP_AUTO_GATE_EN |
		BIT_AON_APB_CGM_AXI_PERIPH_AUTO_GATE_EN |
		BIT_AON_APB_CGM_ACE_AUTO_GATE_EN |
		BIT_AON_APB_CGM_SCU_AUTO_GATE_EN |
		BIT_AON_APB_CGM_CORE3_AUTO_GATE_EN |
		BIT_AON_APB_CGM_CORE2_AUTO_GATE_EN |
		BIT_AON_APB_CGM_CORE1_AUTO_GATE_EN |
		BIT_AON_APB_CGM_CORE0_AUTO_GATE_EN
	);

	value = CHIP_REG_GET(REG_AON_APB_RC100M_CFG) & ~BIT_AON_APB_RC100M_FORCE_EN | BIT_AON_APB_RC100M_AUTO_GATE_EN;
	CHIP_REG_SET(REG_AON_APB_RC100M_CFG, value);

	value = CHIP_REG_GET(REG_TOP_DVFS_APB_TOP_DVFS_CLK_CTRL) & ~BIT_TOP_DVFS_APB_CGM_TOP_DVFS_FORCE_EN | BIT_TOP_DVFS_APB_CGM_TOP_DVFS_AUTO_GATE_SEL;
	CHIP_REG_SET(REG_TOP_DVFS_APB_TOP_DVFS_CLK_CTRL, value);

	value = CHIP_REG_GET(REG_APCPU_DVFS_APB_CGM_APCPU_DVFS_CLK_GATE_CTRL) & ~BIT_APCPU_DVFS_APB_CGM_APCPU_DVFS_FORCE_EN | BIT_APCPU_DVFS_APB_CGM_APCPU_DVFS_AUTO_GATE_SEL;
	CHIP_REG_SET(REG_APCPU_DVFS_APB_CGM_APCPU_DVFS_CLK_GATE_CTRL, value);

	value = CHIP_REG_GET(REG_AP_DVFS_APB_CGM_AP_DVFS_CLK_GATE_CTRL) & ~BIT_AP_DVFS_APB_CGM_AP_DVFS_FORCE_EN | BIT_AP_DVFS_APB_CGM_AP_DVFS_AUTO_GATE_SEL;
	CHIP_REG_SET(REG_AP_DVFS_APB_CGM_AP_DVFS_CLK_GATE_CTRL, value);
#endif
}

void apcpu_hw_dvfs_config(void)
{
	// Disable apcpu dvfs upd delay en bit
	CHIP_REG_AND(REG_APCPU_DVFS_APB_APCPU_FREQ_UPD_TYPE_CFG, ~(
		BIT_APCPU_DVFS_APB_APCPU_GIC_FREQ_UPD_DELAY_EN    |
		BIT_APCPU_DVFS_APB_APCPU_PERIPH_FREQ_UPD_DELAY_EN |
		BIT_APCPU_DVFS_APB_APCPU_ATB_FREQ_UPD_DELAY_EN    |
		BIT_APCPU_DVFS_APB_APCPU_SCU_FREQ_UPD_DELAY_EN    |
		BIT_APCPU_DVFS_APB_APCPU_CORE3_FREQ_UPD_DELAY_EN  |
		BIT_APCPU_DVFS_APB_APCPU_CORE2_FREQ_UPD_DELAY_EN  |
		BIT_APCPU_DVFS_APB_APCPU_CORE1_FREQ_UPD_DELAY_EN  |
		BIT_APCPU_DVFS_APB_APCPU_CORE0_FREQ_UPD_DELAY_EN
	));
}

void CSP_Init(uint32_t ddie_id, uint32_t adie_id)
{
	pmu_sequence_config();
	pad_out_sel_config();
	aon_idle_config();
	aon_lpc_config();
	ap_lpc_config();
	clock_auto_gate();
	apcpu_hw_dvfs_config();
}


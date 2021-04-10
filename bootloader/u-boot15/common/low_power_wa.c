/******************************************************************************
 ** File Name:      low_power_wa.c                                            *
 ** Author:         bruce_kui.wang                                            *
 ** DATE:           2017/01/17                                                *
 ** Copyright:      2017 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines low power wa configuration.             *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME               DESCRIPTION                             *
 ** 2017/01/17     bruce_kui.wang     Create.                                 *
 ******************************************************************************/

/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/
#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
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
#ifdef CONFIG_SOC_IWHALE2
void aon_lpc_config();
#endif
/**---------------------------------------------------------------------------*
 **                         Struct defines.
 **---------------------------------------------------------------------------*/

#ifdef CONFIG_SOC_IWHALE2
void aon_lpc_config()
{
	CHIP_REG_AND(REG_AON_LPC_APB_PUBCP2AON_W_LPC_CTRL,
		~BIT_AON_LPC_APB_PUBCP2AON_W_LP_EB);
	CHIP_REG_AND(REG_AON_LPC_APB_VSP2PUB0_SLICE_LPC_CTRL,
		~BIT_AON_LPC_APB_VSP2PUB0_SLICE_LP_EB);
	CHIP_REG_AND(REG_AON_LPC_APB_CAM2PUB0_SLICE_LPC_CTRL,
		~BIT_AON_LPC_APB_CAM2PUB0_SLICE_LP_EB);
	CHIP_REG_AND(REG_AON_LPC_APB_GPU2PUB0_SLICE_LPC_CTRL,
		~BIT_AON_LPC_APB_GPU2PUB0_SLICE_LP_EB);
	CHIP_REG_AND(REG_AON_LPC_APB_AP_BIA_PUB0_SLICE_LPC_CTRL,
		~BIT_AON_LPC_APB_AP_BIA_PUB0_SLICE_LP_EB);
	CHIP_REG_AND(REG_AON_LPC_APB_VSP2PUB1_SLICE_LPC_CTRL,
		~BIT_AON_LPC_APB_VSP2PUB1_SLICE_LP_EB);
	CHIP_REG_AND(REG_AON_LPC_APB_CAM2PUB1_SLICE_LPC_CTRL,
		~BIT_AON_LPC_APB_CAM2PUB1_SLICE_LP_EB);
	CHIP_REG_AND(REG_AON_LPC_APB_GPU2PUB1_SLICE_LPC_CTRL,
		~BIT_AON_LPC_APB_GPU2PUB1_SLICE_LP_EB);
	CHIP_REG_AND(REG_AON_LPC_APB_AP_BIA_PUB1_SLICE_LPC_CTRL,
		~BIT_AON_LPC_APB_AP_BIA_PUB1_SLICE_LP_EB);
}
#endif


#ifdef CONFIG_SOC_IWHALE2
void wakeup_source_enable()
{
	CHIP_REG_OR(REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN0,
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_CLK_32K_DET_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_BIA_TMR_EN |  //intel need
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB0_DFS_ERROR_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_STATALARM_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_AGCP_WDG_RST_EN |
		0
	);
	CHIP_REG_OR(REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN1,
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_ISP_CH0_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VSP_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_CPP_MMU_PF_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DJTAG_EN |
		0
	);
	CHIP_REG_OR(REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN2,
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_EIC_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_GPIO_EN |
		//BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DMA_AGCP_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MCDT_AGCP_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_BUSMON0_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_DMA_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_EMMC_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DCAM2ISP_IF_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_USB3_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_ANA_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MBOX_TAR_A53_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MBOX_SRC_A53_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AON_TMR_EN |  //intel need
		0
	);
	CHIP_REG_OR(REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN3,
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DMA_SEC_AP_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VSP_SYS_BUSMON_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_CAM_SYS_BUSMON_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SPI0_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_UART1_EN | //intel need
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VSP_MMU_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_GSP_MMU_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_GPIO_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_EIC_EN |
		0
	);
	return;
}
#elif defined(CONFIG_SPRD_SOC_SP9853I)
void wakeup_source_enable()
{
	CHIP_REG_OR(REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN0,
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_CLK_32K_DET_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_BIA_TMR_EN |  //intel need
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_PUB0_DFS_ERROR_EN |
		0
	);
	CHIP_REG_OR(REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN1,
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_ISP_CH0_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VSP_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DJTAG_EN |
		0
	);
	CHIP_REG_OR(REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN2,
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_EIC_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_IRQ_GPIO_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_BUSMON0_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_DMA_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_EMMC_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DCAM2ISP_IF_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_USB2_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_ANA_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_I2C_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MBOX_TAR_A53_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_MBOX_SRC_A53_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AON_TMR_EN |  //intel need
		0
	);
	CHIP_REG_OR(REG_PMU_APB_BASEIA_WAKEUP_SOURCE_EN3,
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_DMA_SEC_AP_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_VSP_SYS_BUSMON_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_CAM_SYS_BUSMON_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C5_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C4_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C2_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C1_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_I2C0_EN|
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_SPI0_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_AP_UART1_EN | //intel need
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_GPIO_EN |
		BIT_PMU_APB_BASEIA_WAKEUP_SOURCE_INT_REQ_SEC_EIC_EN |
		0
	);
}
#else
void wakeup_source_enable()
{
	return;
}
#endif
#if defined(CONFIG_SOC_IWHALE2) || defined(CONFIG_SPRD_SOC_SP9853I)
void ap_clk_doze_enable()
{
	CHIP_REG_OR(REG_AP_CLK_CGM_CTL_CFG,
		BIT_AP_CLK_CGM_DOZE_MODE_EN |
		0);
}
#else
void ap_clk_doze_enable()
{
	return;
}

#endif
#ifdef __cplusplus
}
#endif

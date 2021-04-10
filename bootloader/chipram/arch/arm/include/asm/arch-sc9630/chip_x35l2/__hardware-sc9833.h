/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __ASM_ARCH_HARDWARE_SC9630_H
#define __ASM_ARCH_HARDWARE_SC9630_H

#define LL_DEBUG_UART_PHYS		SPRD_UART1_PHYS
#define LL_DEBUG_UART_BASE		SPRD_UART1_BASE

#define SPRD_CORESIGHT_STM_PHYS		0x01000000
#define SPRD_CORESIGHT_PHYS		0x10000000
#define SPRD_CA7_GIC_PHYS		0x12000000
#define SPRD_DMA0_PHYS			0X20100000
#define SPRD_USB_PHYS			0X20200000
#define SPRD_SDIO0_PHYS			0X20300000
#define SPRD_SDIO1_PHYS			0X20400000
#define SPRD_SDIO2_PHYS			0X20500000
#define SPRD_EMMC_PHYS			0X20600000
#define SPRD_DRM_PHYS			0X20700000
#define SPRD_LCDC_PHYS			0X20800000
#define SPRD_GSP_PHYS			0X20A00000
#define SPRD_HWLOCK0_PHYS		0X20D00000
#define SPRD_AHB_PHYS			0X20E00000
#define SPRD_PUBLIC_CE_PHYS		0x21300000
#define SPRD_SECURE_CE_PHYS		0x21400000
#define SPRD_APCKG_PHYS			0x21500000
#define SPRD_DSI_PHYS			0x21800000
#define SPRD_CE_EFUSE_PHYS		0x21C00000
#define SPRD_LPDDR2_PHYS		0X30000000
#define SPRD_AXIBM0_PHYS		0X30040000
#define SPRD_AXIBM1_PHYS		0X30050000
#define SPRD_AXIBM2_PHYS		0X30060000
#define SPRD_AXIBM3_PHYS		0X30070000
#define SPRD_AXIBM4_PHYS		0X30080000
#define SPRD_AXIBM5_PHYS		0X30090000
#define SPRD_AXIBM6_PHYS		0X300A0000
#define SPRD_AXIBM7_PHYS		0X300B0000
#define SPRD_DFI_AXIBM_PHYS		0X300C0000
#define SPRD_PUB_PHYS			0X300E0000
#define SPRD_AUDIO_PHYS			0X40000000
#define SPRD_AUDIO_IF_PHYS		0X40010000
#define SPRD_VBC_PHYS			0X40020000
#define SPRD_SYSTIMER_CMP_PHYS		0X40040000
#define SPRD_GPTIMER0_PHYS		0X40050000
#define SPRD_HWLOCK1_PHYS		0X40060000
#define SPRD_MDAR_PHYS			0X40070000
#define SPRD_MBOX_PHYS			0x400A0000
#define SPRD_CP_TMR_PHYS		0x400B0000
#define SPRD_CP_SYST_PHYS		0x400C0000
#define SPRD_CP_WDG_PHYS		0x400D0000
#define SPRD_CP_ALL_EIC_PHYS		0x400E0000
#define SPRD_DEF_PHYS			0x400F0000
#define SPRD_INT_PHYS			0X40200000
#define SPRD_EIC_PHYS			0X40210000
#define SPRD_APTIMER0_PHYS		0X40220000
#define SPRD_SYSCNT_PHYS		0X40230000
#define SPRD_UIDEFUSE_PHYS		0X40240000
#define SPRD_KPD_PHYS			0X40250000
#define SPRD_PWM_PHYS			0X40260000
#define SPRD_BUS_MON_TIMER_PHYS		0X40270000
#define SPRD_GPIO_PHYS			0X40280000
#define SPRD_WDG_PHYS			0X40290000
#define SPRD_PIN_PHYS			0X402A0000
#define SPRD_PMU_PHYS			0X402B0000
//#define SPRD_IPI_PHYS			0X402C0000
#define SPRD_AONCKG_PHYS		0X402D0200
#define SPRD_AONAPB_PHYS		0X402E0000
#define SPRD_THM_PHYS			0X402F0000
//#define SPRD_AVSCA7_PHYS		0X40300000
#define SPRD_CA7WDG_PHYS		0X40310000
#define SPRD_APTIMER1_PHYS		0X40320000
#define SPRD_APTIMER2_PHYS		0X40330000
#define SPRD_DJTAG_PHYS			0x40340000
#define SPRD_ANA_TEST0_PHYS		0x40350000
#define SPRD_ANLG_PHY_G1		0x40350000
#define SPRD_ANLG_PHY_G2		0x40353000
#define SPRD_ANLG_PHY_G3		0x40356000
#define SPRD_ANLG_PHY_G5		0x40359000
#define SPRD_ANA_TEST1_PHYS		0x40360000
#define SPRD_EIC1_PHYS			0x40370000
#define SPRD_SEC_EIC_PHYS		0x40380000
#define SPRD_ADI_PHYS			0X403C0000
#define SPRD_ADISLAVE_PHYS		0X403C8000
#define SPRD_CA7TS0_PHYS		0X40400000
//#define SPRD_CA7TS1_PHYS		0X40410000
#define SPRD_SEC_TZPC_PHYS		0X40420000
#define SPRD_SEC_TIMER_PHYS		0X40430000
#define SPRD_SEC_RTC_PHYS		0X40440000
#define SPRD_SEC_WDG_PHYS		0X40450000
#define SPRD_SEC_REG_PHYS		0X40460000
#define SPRD_SERDES_CTL_PHYS		0X40470000
#define SPRD_CROSS_TRIGGER_PHYS		0X40480000
#define SPRD_SEC_GPIO_PHYS		0X40490000
#define SPRD_SERDES_TESTREG_PHYS	0X404A0000
#define SPRD_SERDES_APB_PHYS		0X404B0000
#define SPRD_PUB_CP_INTC_PHYS           0x404C0000
#define SPRD_WTL_CP_INTC_PHYS           0x404D0000
#define SPRD_TGDSP_INTC_PHYS            0x404E0000
#define SPRD_LDSP_INTC_PHYS             0x404F0000
#define SPRD_SHARE_RAM_WITH_CPS_PHYS    0x50000000
#define SPRD_ARM7_IRAM_PHYS             0x50800000
#define SPRD_ARM7_AHB_PHYS              0x50820000
#define SPRD_ARM7_SYSTIMER_PHYS		0x50880000
#define SPRD_ARM7_TIMER_PHYS		0x50890000
#define SPRD_ARM7_INT_PHYS		0x508A0000
#define SPRD_ARM7_EIC_PHYS		0x508B0000
#define SPRD_ARM7_WDG_PHYS		0x508C0000
#define SPRD_ARM7_UART_PHYS		0x508D0000
#define SPRD_ARM7_GPIO_PHYS		0x508E0000
#define SPRD_ARM7_INTC1_PHYS		0x508F0000
#define SPRD_MALI_PHYS			0X60000000
#define SPRD_GPUAPB_PHYS		0X60100000
#define SPRD_DCAM_PHYS			0X60800000
#define SPRD_VSP_PHYS			0X60900000
#define SPRD_ISP_PHYS			0X60A00000
#define SPRD_JPG_PHYS			0X60B00000
#define SPRD_CSI2_PHYS			0X60C00000
#define SPRD_MMAHB_PHYS			0X60D00000
#define SPRD_MMCKG_PHYS			0X60E00000
#define SPRD_CPP_PHYS			0x61000000
#define SPRD_CSI2X2_PHYS		0x61200000
#define SPRD_UART0_PHYS			0X70000000
#define SPRD_UART1_PHYS			0X70100000
#define SPRD_UART2_PHYS			0X70200000
#define SPRD_UART3_PHYS			0X70300000
#define SPRD_UART4_PHYS			0X70400000
#define SPRD_I2C0_PHYS			0X70500000
#define SPRD_I2C1_PHYS			0X70600000
#define SPRD_I2C2_PHYS			0X70700000
#define SPRD_I2C3_PHYS			0X70800000
#define SPRD_I2C4_PHYS			0X70900000
#define SPRD_SPI0_PHYS			0X70A00000
#define SPRD_SPI1_PHYS			0X70B00000
#define SPRD_SPI2_PHYS			0X70C00000
#define SPRD_IIS0_PHYS			0X70D00000
#define SPRD_IIS1_PHYS			0X70E00000
#define SPRD_IIS2_PHYS			0X70F00000
#define SPRD_IIS3_PHYS			0X71000000
#define SPRD_SIM0_PHYS			0X71100000
#define SPRD_APBREG_PHYS		0X71300000
#define SPRD_INTC0_PHYS			0X71400000
#define SPRD_INTC1_PHYS			0X71500000
#define SPRD_INTC2_PHYS			0X71600000
#define SPRD_INTC3_PHYS			0X71700000
/*FIXME:hongfeng.chen*/
#define SPRD_IRAM0_PHYS			0X0
#define SPRD_IRAM0_SIZE			SZ_8K
//#define SPRD_IRAM0H_PHYS		0X1000
#define SPRD_IRAM1_PHYS			0X50000000


//#define SPRD_IRAM0H_BASE		SCI_IOMAP(0x3d1000)
//#define SPRD_IRAM0H_PHYS		0X1000
//#define SPRD_IRAM0H_SIZE		SZ_4K
//#define SPRD_IRAM1_BASE			SCI_IOMAP(0x3e0000)
//#define SPRD_IRAM1_PHYS			0X50000000
//#define SPRD_IRAM1_SIZE			(SZ_32K + SZ_8K + SZ_4K + SZ_2K)

#define SPRD_MEMNAND_SYSTEM_PHYS	0x8c800000
#define SPRD_MEMNAND_SYSTEM_SIZE	(0xaa00000)
#define SPRD_MEMNAND_USERDATA_PHYS	0X97200000
#define SPRD_MEMNAND_USERDATA_SIZE	(0x6a00000)
#define SPRD_MEMNAND_CACHE_PHYS		(0X97200000+0x6a00000)
#define SPRD_MEMNAND_CACHE_SIZE		(0x2400000)


/* registers for watchdog ,RTC, touch panel, aux adc, analog die... */
#define SPRD_MISC_BASE			((unsigned int)SPRD_ADI_PHYS)
#define SPRD_MISC_PHYS			((unsigned int)SPRD_ADI_PHYS)
#define USB_REG_BASE			SPRD_USB_PHYS

#ifndef REGS_AHB_BASE
#define REGS_AHB_BASE			( SPRD_AHB_PHYS+ 0x200)
#endif

/* FIXME: jianjun.he */
#define SPRD_IRAM_PHYS		SPRD_IRAM0_PHYS + 0x1000
#define SPRD_IRAM_SIZE		SZ_4K
#define SPRD_GREG_PHYS		SPRD_AONAPB_PHYS
#define SPRD_GREG_SIZE		SZ_64K

#define SDIO0_BASE_ADDR         SPRD_SDIO0_BASE
#define SDIO1_BASE_ADDR         SPRD_SDIO1_BASE
#define SDIO2_BASE_ADDR         SPRD_SDIO2_BASE
#define SPRD_EMMC_BASE		SPRD_EMMC_PHYS
#define EMMC_BASE_ADDR          SPRD_EMMC_BASE

#ifndef REGS_GLB_BASE
#define REGS_GLB_BASE			( SPRD_GREG_BASE )
#endif

#define CHIP_ID_LOW_REG		(SPRD_AHB_PHYS+ 0xfc)

#define SPRD_GPTIMER_BASE	SPRD_GPTIMER0_PHYS
//#define REG_GLB_GEN0 		SPRD_AONAPB_BASE
#define SPRD_EFUSE_BASE		SPRD_UIDEFUSE_PHYS

#define SPRD_AONCKG_BASE		SPRD_AONCKG_PHYS
#define REGS_AP_AHB_BASE	SPRD_AHB_PHYS
#define REGS_AP_APB_BASE	SPRD_APBREG_PHYS
#define CTL_BASE_APB		REGS_AP_APB_BASE
#define REGS_AON_APB_BASE	SPRD_AONAPB_PHYS
#define REGS_GPU_APB_BASE	SPRD_GPUAPB_PHYS
#define REGS_MM_AHB_BASE	SPRD_MMAHB_PHYS
#define REGS_PMU_APB_BASE	SPRD_PMU_PHYS
#define REGS_AON_CLK_BASE	SPRD_AONCKG_PHYS
#define REGS_AP_CLK_BASE	SPRD_APBCKG_PHYS
#define REGS_GPU_CLK_BASE	SPRD_GPUCKG_PHYS
#define REGS_MM_CLK_BASE	SPRD_MMCKG_PHYS
#define REGS_PUB_APB_BASE	SPRD_PUB_PHYS
#define ARM_UART0_BASE		SPRD_UART0_PHYS
#define ARM_UART1_BASE		SPRD_UART1_PHYS
#define ARM_UART2_BASE		SPRD_UART2_PHYS
#define ARM_UART3_BASE		SPRD_UART3_PHYS

#define SIPC_SMEM_ADDR 		(CONFIG_PHYS_OFFSET + 120 * SZ_1M)

#define CPT_START_ADDR		(CONFIG_PHYS_OFFSET + 128 * SZ_1M)
#define CPT_TOTAL_SIZE		(SZ_1M * 18)
#define CPT_RING_ADDR		(CPT_START_ADDR + CPT_TOTAL_SIZE - SZ_4K)
#define CPT_RING_SIZE		(SZ_4K)
#define CPT_SMEM_SIZE		(SZ_1M * 2)
#define CPW_START_ADDR		(CONFIG_PHYS_OFFSET + 256 * SZ_1M)
#define CPW_TOTAL_SIZE		(SZ_1M * 33)
#define CPW_RING_ADDR		(CPW_START_ADDR + CPW_TOTAL_SIZE - SZ_4K)
#define CPW_RING_SIZE			(SZ_4K)
#define CPW_SMEM_SIZE		(SZ_1M * 2)
#define WCN_START_ADDR		(CONFIG_PHYS_OFFSET + 320 * SZ_1M)
#define WCN_TOTAL_SIZE		(SZ_1M * 5)
#define WCN_RING_ADDR		(WCN_START_ADDR + WCN_TOTAL_SIZE - SZ_4K)
#define WCN_RING_SIZE			(SZ_4K)
#define WCN_SMEM_SIZE		(SZ_1M * 2)
#endif

#define AON_EMMC_CLK_2X_CFG        0XF0
#define AON_SDIO0_CLK_2X_CFG       0XD8
#define AON_CLK_FREQ_1M                 0x0
#define AON_CLK_FREQ_26M               0x1
#define AON_CLK_FREQ_384M             0X3
#define AON_CLK_FREQ_200K_DIV      0X400
#define AON_CLK_FREQ_24M_DIV       0X700
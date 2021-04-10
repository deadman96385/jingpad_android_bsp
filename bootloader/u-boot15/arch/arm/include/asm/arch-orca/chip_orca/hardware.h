/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
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

#ifndef HARDWARE_H
#define HARDWARE_H

/* Address Mapping definitions for sub-system AP */
#define SPRD_AON_TOP_PHYS               (0x00000000)
#define SPRD_ROM_TOP_PHYS               (0x20000000)
#define SPRD_AHB_RF_PHYS                (0x21000000)
#define SPRD_CLK_TOP_PHYS               (0x21100000)
#define SPRD_DMA_AMST_TOP_PHYS          (0x21200000)
#define SPRD_NANDC_CTRL_PHYS            (0x21300000)
#define SPRD_USB3_0_PHYS                (0x21400000)
#define SPRD_AP_APB_RF_PHYS             (0x24000000)
#define SPRD_UART0_TOP_PHYS             (0x24100000)
#define SPRD_I2C0_TOP_PHYS              (0x24200000)
#define SPRD_I2C1_TOP_PHYS              (0x24300000)
#define SPRD_I2C2_TOP_PHYS              (0x24400000)
#define SPRD_I2C3_TOP_PHYS              (0x24500000)
#define SPRD_I2C4_TOP_PHYS              (0x24600000)
#define SPRD_SPI_HS0_TOP_PHYS           (0x24700000)
#define SPRD_SPI_HS1_TOP_PHYS           (0x24800000)
#define SPRD_SPI_HS2_TOP_PHYS           (0x24900000)
#define SPRD_U0_UNIT_PHYS               (0x24a00000)
#define SPRD_U1_UNIT_PHYS               (0x24a00020)
#define SPRD_U2_UNIT_PHYS               (0x24a00040)
#define SPRD_U3_UNIT_PHYS               (0x24a00060)
#define SPRD_SIM0_TOP_PHYS              (0x24b00000)
#define SPRD_SDIO_MST_TOP_PHYS          (0x26000000)
#define SPRD_EMMC_TOP_PHYS              (0x26100000)
#define SPRD_MMTX_WRAP_PHYS             (0x26200000)
#define SPRD_IPA_SYS_TOP_PHYS           (0x48000000)

/* Address Mapping definitions for sub-system IPA */
#define SPRD_AP_TOP_PHYS                (0x20000000)
#define SPRD_SRAM_TOP_PHYS              (0x28000000)
#define SPRD_IPA_AHB_RF_PHYS            (0x29000000)
#define SPRD_USB3_1_PHYS                (0x29100000)
#define SPRD_SDIO_SLV_TOP_PHYS          (0x2b000000)
#define SPRD_PCIE_WRAP_PHYS             (0x2b100000)
#define SPRD_PCIE_TOP_WRAP_PHYS         (0x2b200000)
#define SPRD_PAMU3_PHYS                 (0x2b300000)
#define SPRD_IMTX_WRAP_PHYS             (0x2b400000)
#define SPRD_PAM_WIFI_TOP_PHYS          (0x2b500000)
#define SPRD_IPA_TOP_PHYS               (0x2e000000)
#define SPRD_NRCP_TOP_PHYS              (0x48000000)
#define SPRD_PSCP_TOP_PHYS              (0x54000000)
#define SPRD_DDR_TOP_PHYS               (0x80000000)
#define SPRD_PCIEX2_WRAP_PHYS           (0x200000000)


/* Address Mapping definitions for sub-system AON */
#define SPRD_SP_IMC_0_0_PHYS            (0x00000000)
#define SPRD_SP_IMC_1_0_PHYS            (0x00008000)
#define SPRD_WCN_ADDA_TEST_TOP_PHYS     (0x06390000)
#define SPRD_IMC_0_0_PHYS               (0x60000000)
#define SPRD_IMC_1_0_PHYS               (0x60008000)
#define SPRD_SP_AHB_PHYS                (0x62010000)
#define SPRD_SP_CM4_DMA_PHYS            (0x62020000)
#define SPRD_CM4_TMR_TOP_PHYS           (0x620a0000)
#define SPRD_CM4_SYST_TOP_PHYS          (0x620b0000)
#define SPRD_SP_EIC_TOP_PHYS            (0x620c0000)
#define SPRD_CM4_WDG16_TOP_PHYS         (0x620d0000)
#define SPRD_CM4_UART0_TOP_PHYS         (0x620e0000)
#define SPRD_SP_EIC_GPIO_TOP_PHYS       (0x620f0000)
#define SPRD_SP_EIC1_TOP_PHYS           (0x62100000)
#define SPRD_AON_MTX_MAIN_MTX_WRAP_PHYS (0x63000000)

#define SPRD_AON_PERI_INTC_AP0_PHYS     (0x63020000)
#define SPRD_AON_PERI_INTC_AP1_PHYS     (0x63030000)
#define SPRD_AON_PERI_INTC_AP2_PHYS     (0x63040000)
#define SPRD_AON_PERI_INTC_AP3_PHYS     (0x63050000)
#define SPRD_AON_PERI_INTC_AP4_PHYS     (0x63060000)
#define SPRD_AON_PERI_INTC_AP5_PHYS     (0x63070000)
#define SPRD_AON_PERI_INTC_PSCP_PHYS    (0x630a0000)
#define SPRD_AON_PERI_INTC_NRCP_CR8_PHYS (0x630b0000)
#define SPRD_AON_PERI_INTC_AUDCP_PHYS   (0x630c0000)
#define SPRD_AON_PERI_INTC_NRCP_DSP_0_PHYS (0x630d0000)
#define SPRD_AON_PERI_INTC_NRCP_DSP_1_PHYS (0x630e0000)
#define SPRD_AON_PERI_INTC_NRCP_PHYS    (0x630f0000)
#define SPRD_AON_PERI_INTC_V3PS_PHYS    (0x63100000)
#define SPRD_AON_PERI_INTC_V3PHY_PHYS   (0x63110000)
#define SPRD_AON_PERI_INTC_V3MODEM_PHYS (0x63120000)
#define SPRD_PRE_DIV_CLK_RF_PHYS        (0x63170000)
#define SPRD_CLK_RF_PHYS                (0x63170200)
#define SPRD_AON_PERI_EIC_EXT0_PHYS     (0x631b0000)
#define SPRD_AON_PERI_EIC_EXT1_PHYS     (0x631c0000)
#define SPRD_AON_PERI_EIC_EXT2_PHYS     (0x631d0000)
#define SPRD_AON_PERI_EIC_EXT3_PHYS     (0x631e0000)
#define SPRD_AON_PERI_EIC_EXT4_PHYS     (0x631f0000)
#define SPRD_AON_PERI_EIC_EXT5_PHYS     (0x63200000)
#define SPRD_AON_PERI_SYST_PHYS         (0x63250000)
#define SPRD_AON_PERI_TMR_PHYS          (0x63260000)
#define SPRD_AON_PERI_BUSMON_CNT_START_TIMER1_PHYS (0x63270000)
#define SPRD_AON_PERI_BUSMON_CNT_START_TIMER2_PHYS (0x63280000)
#define SPRD_AON_PERI_I2C_PHYS          (0x632c0000)
#define SPRD_AON_PERI_GPIO_PHYS         (0x632d0000)
#define SPRD_AON_PERI_MAILBOX_TOP_PHYS  (0x63300000)
#define SPRD_BB_SW_RFSPI_MST_NR_PHYS    (0x63340000)
#define SPRD_BB_SW_RFSPI_MST_V3_PHYS    (0x63350000)
#define SPRD_AON_PERI_SCC_TOP_PHYS      (0x63360000)
#define SPRD_AON_PERI_EFUSE_TOP_WRAP_PHYS (0x63400000)
#define SPRD_THM0_PHYS                  (0x63410000)
#define SPRD_THM1_PHYS                  (0x63420000)
#define SPRD_THM2_PHYS                  (0x63430000)
#define SPRD_AON_MTX_APB_TO_APB_ASYNC_PIN_PHYS (0x63450000)
#define SPRD_ANALOG_TOP_GLB_PHYS        (0x63460000)
#define SPRD_ANALOG_G0_GLB_PHYS         (0x63470000)
#define SPRD_ANALOG_G1_GLB_PHYS         (0x63480000)
#define SPRD_ANALOG_G2_GLB_PHYS         (0x63490000)
#define SPRD_ANALOG_PCIE_GEN2_1T1R_PHYS (0x634a0000)
#define SPRD_ANALOG_G3_GLB_PHYS         (0x634b0000)
#define SPRD_ANALOG_G4_GLB_PHYS         (0x634c0000)
#define SPRD_ANALOG_USB30_0_2T2R_PHYS   (0x634d0000)
#define SPRD_ANALOG_USB30_1_2T2R_PHYS   (0x634e0000)
#define SPRD_ANALOG_G5_GLB_PHYS         (0x634f0000)
#define SPRD_ANALOG_G8_GLB_PHYS         (0x63500000)
#define SPRD_ANALOG_G9_GLB_PHYS         (0x63510000)
#define SPRD_ANALOG_G10_GLB_PHYS        (0x63520000)
#define SPRD_ANALOG_G11_GLB_PHYS        (0x63530000)
#define SPRD_ANALOG_MIPI_DSI_4LANE_0_PHYS (0x63540000)
#define SPRD_ANALOG_MIPI_DSI_4LANE_1_PHYS (0x63550000)
#define SPRD_ANALOG_MIPI_DSI_4LANE_2_PHYS (0x63560000)
#define SPRD_AON_SEC_PERI_APCPU_TS1_PHYS (0x63600000)
#define SPRD_AON_PERI_SERDES0_PHYS      (0x63610000)
#define SPRD_AON_PERI_SERDES1_PHYS      (0x63620000)
#define SPRD_AON_PERI_SERDES2_PHYS      (0x63630000)
#define SPRD_AON_REG_DBG_APB_PHYS       (0x63640000)
#define SPRD_AON_PERI_DJTAG_CTRL_PHYS   (0x63650000)
#define SPRD_AON_PERI_CHIP_RESET_CTRL_PHYS (0x63660000)
#define SPRD_AON_SEC_PERI_CLK_32K_DET_TOP_PHYS (0x63670000)
#define SPRD_REG_TRACE_MONITOR_WRAP_PHYS (0x63680000)
#define SPRD_AON_PERI_S5_APB_BUSMON_PHYS (0x63690000)
#define SPRD_AON_PERI_CPALL_EIC_PHYS    (0x63800000)
#define SPRD_AON_PERI_PSCP_WDG_PHYS     (0x63810000)
#define SPRD_AON_PERI_PSCP_SYST_PHYS    (0x63820000)
#define SPRD_AON_PERI_PSCP_TMR_PHYS     (0x63830000)
#define SPRD_AON_PERI_AP_TMR0_PHYS      (0x63900000)
#define SPRD_AON_PERI_AP_TMR1_PHYS      (0x63910000)
#define SPRD_AON_PERI_AP_TMR2_PHYS      (0x63920000)
#define SPRD_AON_PERI_AP_SYST_PHYS      (0x63930000)
#define SPRD_AON_PERI_APCPU_WDG_PHYS    (0x63940000)
#define SPRD_AON_PERI_AP_WDG_PHYS       (0x63950000)
#define SPRD_AON_PERI_AP_KPD_PHYS       (0x63960000)
#define SPRD_APCPU_CLK_PHYS             (0x63970000)
#define SPRD_AON_DVFS_TOP_PHYS          (0x63980000)
#define SPRD_APCPU_DVFS_TOP_PHYS        (0x63988000)
#define SPRD_AON_PERI_ADI_MST_PHYS      (0x63a00000)
#define SPRD_ADISLAVE_PHYS              (0x63a20000)
#define SPRD_AON_SPINLOCK_PHYS          (0x64000000)
#define SPRD_PMU_APB_RF_PHYS            (0x64010000)
#define SPRD_AON_APB_PHYS               (0x64020000)
#define SPRD_AON_S3_APB_BUSMON_PHYS     (0x64030000)
#define SPRD_CORESIGHT_STM_PHYS         (0x70000000)
#define SPRD_CORESIGHT_SEC_PHYS         (0x78000000)
#define SPRD_CORESIGHT_ETB              (0x78003000)

/* referenced by sdio_cfg.c */
#define SPRD_EMMC_BASE                                     SPRD_EMMC_TOP_PHYS
#define SPRD_SDIO0_BASE                                    SPRD_SDIO_MST_TOP_PHYS
/* referenced by sprd_musb2_def.h */
#define SPRD_USB_BASE                                      SPRD_USB3_1_PHYS
/* referenced by adi.c */
#define SPRD_MISC_PHYS                                     SPRD_AON_PERI_ADI_MST_PHYS
/* referenced by sprd_i2c.c, just tricky */
#define SPRD_I2C_BASE                                      SPRD_I2C0_TOP_PHYS
#define SPRD_I2C0_PHYS                                     SPRD_I2C0_TOP_PHYS
#define SPRD_I2C1_PHYS                                     SPRD_I2C1_TOP_PHYS
#define SPRD_I2C2_PHYS                                     SPRD_I2C2_TOP_PHYS
#define SPRD_I2C3_PHYS                                     SPRD_I2C3_TOP_PHYS
#define SPRD_I2C4_PHYS                                     SPRD_I2C4_TOP_PHYS
/* referenced by timer.c */
#define SPRD_APCPUTS0_BASE                                 SPRD_AON_SEC_PERI_APCPU_TS1_PHYS
#define SPRD_AON_TIMER_PHYS                                SPRD_AON_PERI_TMR_PHYS
#define SPRD_SYSCNT_PHYS                                   SPRD_AON_PERI_AP_SYST_PHYS
/* referenced by pmic.h */
#define SPRD_ADISLAVE_BASE                                 SPRD_ADISLAVE_PHYS
/* referenced by sprd_bl.c */
#define CTL_BASE_PWM                                       SPRD_U0_UNIT_PHYS
/* just tricky, on uart0 on sharkle */
#define SPRD_UART0_PHYS                                    SPRD_UART0_TOP_PHYS
#define SPRD_UART1_PHYS                                    SPRD_UART0_TOP_PHYS
#define SPRD_DSI_BASE                                      SPRD_ANALOG_MIPI_DSI_4LANE_0_PHYS
#define REGS_AON_APB_BASE                                  SPRD_AON_APB_PHYS
/* referenced by pinmap.h */
#define SPRD_PIN_PHYS                                      SPRD_AON_MTX_APB_TO_APB_ASYNC_PIN_PHYS
/* referenced by gpio_phy.c */
#define SPRD_GPIO_PHYS                                     SPRD_AON_PERI_GPIO_PHYS
/* referenced by ap_public_efuse.c */
#define SPRD_UIDEFUSE_PHYS                                 SPRD_AON_PERI_EFUSE_TOP_WRAP_PHYS
/* referenced by eic.c */
#define SPRD_EIC_PHYS                                      SPRD_AON_PERI_EIC_EXT0_PHYS
#define SPRD_EIC1_PHYS                                     SPRD_AON_PERI_EIC_EXT1_PHYS

#endif

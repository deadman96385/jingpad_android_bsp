#
# (C) Copyright 2000-2007
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

obj-$(CONFIG_ALI152X) += ali512x.o
obj-$(CONFIG_DS4510)  += ds4510.o
obj-$(CONFIG_CBMEM_CONSOLE) += cbmem_console.o
obj-$(CONFIG_CROS_EC) += cros_ec.o
obj-$(CONFIG_CROS_EC_LPC) += cros_ec_lpc.o
obj-$(CONFIG_CROS_EC_I2C) += cros_ec_i2c.o
obj-$(CONFIG_CROS_EC_SANDBOX) += cros_ec_sandbox.o
obj-$(CONFIG_CROS_EC_SPI) += cros_ec_spi.o
obj-$(CONFIG_FSL_DEBUG_SERVER) += fsl_debug_server.o
obj-$(CONFIG_FSL_IIM) += fsl_iim.o
obj-$(CONFIG_GPIO_LED) += gpio_led.o
obj-$(CONFIG_I2C_EEPROM) += i2c_eeprom.o
obj-$(CONFIG_FSL_MC9SDZ60) += mc9sdz60.o
obj-$(CONFIG_MXC_OCOTP) += mxc_ocotp.o
obj-$(CONFIG_MXS_OCOTP) += mxs_ocotp.o
obj-$(CONFIG_NS87308) += ns87308.o
obj-$(CONFIG_PDSP188x) += pdsp188x.o
ifdef CONFIG_DM_I2C
obj-$(CONFIG_SANDBOX) += i2c_eeprom_emul.o
endif
obj-$(CONFIG_SMSC_LPC47M) += smsc_lpc47m.o
obj-$(CONFIG_STATUS_LED) += status_led.o
obj-$(CONFIG_SANDBOX) += swap_case.o
obj-$(CONFIG_TWL4030_LED) += twl4030_led.o
obj-$(CONFIG_FSL_IFC) += fsl_ifc.o
obj-$(CONFIG_FSL_SEC_MON) += fsl_sec_mon.o
obj-$(CONFIG_PCA9551_LED) += pca9551_led.o
obj-$(CONFIG_SPRD_ADI) += adi.o check_reboot.o reset.o
# use haptic as vibrator if sc2705 exists
ifdef CONFIG_SPRD2705_CHARGE_IC
obj-y += sc2705_haptic.o
else
obj-$(CONFIG_SPRD_ADI) += vibrator.o
endif
obj-$(CONFIG_SPRD_ADC) += sprd_adc.o
obj-y += sprd_glb.o
ifdef CONFIG_SPRD_AP_NORMAL_EFUSE
obj-y += ap_public_efuse.o ap_secure_efuse.o otp_helper.o
else
ifdef CONFIG_SPRD_AP_IEFUSE_R1P0
obj-y += ap_iefuse.o otp_helper.o
else
obj-y += ap_efuse.o otp_helper.o
endif
endif
ifneq ($(CONFIG_ADIE_SC2723)$(CONFIG_ADIE_SC2723S)$(CONFIG_ADIE_SC2731)$(CONFIG_ADIE_SC2721)$(CONFIG_ADIE_SC2720)$(CONFIG_ADIE_SC2730),)
obj-y += pmic_efuse.o
endif
obj-y += pmic27xx_misc.o
obj-y += sprd_led.o
# board id for isharkl2
ifdef CONFIG_SPRD_SOC_SP9853I
obj-y += sprd_boardid_isharkl2.o
endif
# board id for sharkl2
ifdef CONFIG_SC9833
obj-y += sprd_boardid_sharkl2.o
endif
# board id for sharklj1
ifdef CONFIG_SOC_SHARKLJ1
obj-y += sprd_boardid_sharklj1.o
endif
# board id for 9820e(sharkle)
ifdef CONFIG_SPRD_SP9820E
obj-y += sprd_boardid_sp9820e.o
endif
# board id for 9832e(sharkle)
ifdef CONFIG_SPRD_SP9832E
obj-y += sprd_boardid_sp9832e.o
endif
# board id for 9850e(sharklep)
ifdef CONFIG_SPRD_SP9850E
obj-y += sprd_boardid_sp9850e.o
endif
# board id for pike2
ifdef CONFIG_SOC_PIKE2
obj-$(CONFIG_BOARDID_NATIVE) += sprd_boardid_pike2.o
obj-$(CONFIG_BOARDID_ITEL) += sprd_boardid_pike2_itel.o
endif
# board id for 9863a(sharkl3)
ifdef CONFIG_SOC_SHARKL3
obj-y += sprd_boardid_sharkl3.o
endif
# board id for orca
ifdef CONFIG_SOC_ORCA
obj-y += sprd_boardid_orca.o
endif
ifdef CONFIG_ADIE_SC2730
obj-y += sprd_clk_crystal_adaption.o
endif

#rfti for shakl2
ifdef CONFIG_SC9833
obj-y += sprd_rfti_sharkl2.o
endif

# feature of direct access prot for sharkl5pro haps
ifdef CONFIG_DIRECT_ACC_PROT
obj-y += sprd_apb_direct_acc_prot.o
endif

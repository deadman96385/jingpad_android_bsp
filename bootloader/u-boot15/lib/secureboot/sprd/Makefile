
obj-y += sec_string.o
obj-y += sprd_verify.o
obj-y += efuse_operate.o
obj-y += sec_efuse_api.o
ifdef CONFIG_SC9833
obj-y += sec_efuse_sharkl2.o
endif
ifdef CONFIG_SOC_SHARKLJ1
obj-y += sec_efuse_sharklj1.o
endif
ifneq ($(CONFIG_SOC_IWHALE2)$(CONFIG_SPRD_SOC_SP9853I), )
obj-y += sec_iefuse.o
endif
ifneq ($(CONFIG_SOC_PIKE2),)
obj-y += sec_efuse_pike2.o
obj-y += sec_efuse_pike2_drv.o
endif
ifneq ($(CONFIG_SOC_SHARKLE),)
obj-y += sec_efuse_sharkle.o
obj-y += sec_efuse_sharkle_drv.o
endif
ifneq ($(CONFIG_SOC_SHARKL3),)
obj-y += sec_efuse_sharkl3.o
obj-y += sec_efuse_sharkl3_drv.o
endif
ifneq ($(CONFIG_SOC_SHARKL5),)
obj-y += sec_efuse_sharkl5.o
obj-y += sec_efuse_sharkl5_drv.o
endif
ifneq ($(CONFIG_SOC_SHARKL5PRO),)
obj-y += sec_efuse_sharkl5pro.o
obj-y += sec_efuse_sharkl5pro_drv.o
endif
ifneq ($(CONFIG_SOC_ROC1),)
obj-y += sec_efuse_roc1.o
obj-y += sec_efuse_roc1_drv.o
endif
ifneq ($(CONFIG_SOC_ORCA),)
obj-y += sec_efuse_orca.o
obj-y += sec_efuse_orca_drv.o
endif

ifneq ($(CONFIG_SC9833)$(CONFIG_SOC_SHARKLJ1)$(CONFIG_SPRD_SOC_SP9853I),)
ccflags-y := -I$(srctree)/drivers/crypto/sprd/r3p0/inc
endif

ifneq ($(CONFIG_SOC_PIKE2)$(CONFIG_SOC_SHARKLE)$(CONFIG_SOC_SHARKL3)$(CONFIG_SOC_SHARKL5)$(CONFIG_SOC_ROC1)$(CONFIG_SOC_SHARKL5PRO),)
ccflags-y := -I$(srctree)/drivers/crypto/sprd/r2p0lite/inc
endif

ifneq ($(CONFIG_SOC_IWHALE2),)
ccflags-y := -I$(srctree)/drivers/crypto/sprd/r2p0/inc
endif


ifdef CONFIG_SECURE_EFUSE
ifneq ($(CONFIG_SOC_IWHALE2)$(CONFIG_SOC_ISHARKL2),)
obj-y	+= sec_iefuse.o
endif

obj-$(CONFIG_SOC_PIKE2)   += sec_efuse_pike2.o sec_efuse_pike2_drv.o

obj-$(CONFIG_ARCH_SCX35L2) += sec_efuse_sharkl2.o

obj-$(CONFIG_SOC_SHARKLJ1) += sec_efuse_sharklj1.o

obj-$(CONFIG_SOC_SHARKLE) += sec_efuse_sharkle.o sec_efuse_sharkle_drv.o

obj-$(CONFIG_SOC_SHARKL3) += sec_efuse_sharkl3.o sec_efuse_sharkl3_drv.o

obj-$(CONFIG_SOC_SHARKL5) += sec_efuse_sharkl5.o sec_efuse_sharkl5_drv.o

obj-$(CONFIG_SOC_SHARKL5PRO) += sec_efuse_sharkl5pro.o sec_efuse_sharkl5pro_drv.o

obj-$(CONFIG_SOC_ROC1) += sec_efuse_roc1.o sec_efuse_roc1_drv.o

obj-$(CONFIG_SOC_ORCA) += sec_efuse_orca.o sec_efuse_orca_drv.o
endif


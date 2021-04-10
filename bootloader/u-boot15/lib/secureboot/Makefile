
obj-y += common/
ifdef CONFIG_VBOOT_V2
obj-y += avb/
endif
ifdef CONFIG_SPRD_SECBOOT
obj-y += sprd/
endif
ifdef CONFIG_SANSA_SECBOOT
obj-y += sansa/
endif
ifdef CONFIG_SECURE_BOOT
	#pls add native document
obj-y += native/
endif
#need drivers/mmc/sprd_rpmb.o
obj-y += sprd_imgversion_comm.o
#ifdef TOS_TRUSTY
#ifdef CONFIG_EMMC_BOOT
obj-$(CONFIG_SPRD_RPMB) += sprd_imgversion.o
#endif
#endif

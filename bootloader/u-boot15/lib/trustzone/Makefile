
#obj-$(CONFIG_SECBOOT) += trustzone_enrty.o
#obj-$(CONFIG_SECBOOT) += trustzone_init.o
obj-$(CONFIG_SECBOOT) += uboot_drv_api.o

obj-$(CONFIG_CPU_V7) += tee_smc_call_v7.o
obj-$(CONFIG_ARM64) += tee_smc_call_v8.o
obj-y += tee_common_call.o

obj-y += uboot_drv_rpmb_comm.o
#ifdef TOS_TRUSTY
#ifdef CONFIG_EMMC_BOOT
obj-$(CONFIG_SPRD_RPMB) += uboot_drv_rpmb.o
#endif
#endif

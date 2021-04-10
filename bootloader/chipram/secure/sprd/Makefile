
ifndef CONFIG_SANSA_SECBOOT
ifneq ($(CONFIG_WHALE)$(CONFIG_WHALE2)$(CONFIG_SOC_IWHALE2)$(CONFIG_ARCH_SCX35L2)$(CONFIG_SOC_SHARKLJ1)$(CONFIG_SOC_PIKE2)$(CONFIG_SOC_SHARKLE)$(CONFIG_SOC_SHARKL3)$(CONFIG_SOC_ISHARKL2)$(CONFIG_SOC_SHARKL5)$(CONFIG_SOC_SHARKL5PRO)$(CONFIG_SOC_ROC1),)
CONFIG_SPRD_CE = y
else
#Software engine will be used as default engine.
CONFIG_SW_CRYPT = y
endif
endif

#If CONFIG_SPRD_CE is defined, the detailed SPRD CE should be selected according to chip's macro

obj-$(CONFIG_SPRD_CE)	+= pk1.o sec_string.o

ifneq ($(CONFIG_WHALE)$(CONFIG_WHALE2)$(CONFIG_SOC_IWHALE2),)
obj-$(CONFIG_SPRD_CE)	+= sprd_crypt_r1p0.o sprd_ce_r1p0.o
endif

ifneq ($(CONFIG_ARCH_SCX35L2)$(CONFIG_SOC_SHARKLJ1)$(CONFIG_SOC_ISHARKL2),)
obj-$(CONFIG_SPRD_CE)    += sprd_crypto_r3p0.o sprd_ce_r3p0.o sprd_pka_r3p0.o
endif

ifneq ($(CONFIG_SOC_PIKE2)$(CONFIG_SOC_SHARKLE)$(CONFIG_SOC_SHARKL3)$(CONFIG_SOC_SHARKL5)$(CONFIG_SOC_ROC1)$(CONFIG_SOC_SHARKL5PRO),)
obj-$(CONFIG_SPRD_CE)    += sprd_crypto_r2p0lite.o sprd_ce_r2p0lite.o sprd_pka_r3p0.o
endif

#add pss
ifneq ($(CONFIG_SOC_SHARKL5)$(CONFIG_SOC_SHARKL5PRO)$(CONFIG_SOC_ROC1),)
obj-$(CONFIG_SPRD_CE)    += sprd_pkcs1_mgf1.o sprd_pkcs1_pss.o sprd_pkcs1_v1_5.o
endif

#If CONFIG_SW_CRYPT is defined, software crypt engine will be used.
ifneq ($(CONFIG_SOC_ORCA),)
CFLAGS += -DCONFIG_SOC_ORCA
#Use crypto extension for sha256 to improve performance.
obj-$(CONFIG_SW_CRYPT)	+= pk1.o sec_string.o sprd_sha256_armv8.o sprd_sha256_core_armv8.o sprd_rsa_sw.o sprd_crypto_sw.o
obj-$(CONFIG_SW_CRYPT)	+= sprd_pkcs1_mgf1.o sprd_pkcs1_pss.o sprd_pkcs1_v1_5.o
else
obj-$(CONFIG_SW_CRYPT)	+= pk1.o sec_string.o sprd_sha256_sw.o sprd_rsa_sw.o
endif
obj-y += sprd_verify.o

obj-$(CONFIG_SECURE_EFUSE) += sec_efuse_api.o

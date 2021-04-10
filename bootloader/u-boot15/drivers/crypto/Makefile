#
# Copyright (c) 2013 Samsung Electronics Co., Ltd.
# 	http://www.samsung.com
#
# SPDX-License-Identifier:	GPL-2.0+
#

obj-$(CONFIG_EXYNOS_ACE_SHA)	+= ace_sha.o
obj-y += rsa_mod_exp/
obj-y += fsl/
ifneq ($(CONFIG_SC9833)$(CONFIG_SOC_SHARKLJ1)$(CONFIG_SPRD_SOC_SP9853I)$(CONFIG_SOC_IWHALE2)$(CONFIG_SOC_PIKE2)$(CONFIG_SOC_SHARKLE)$(CONFIG_SOC_SHARKL3)$(CONFIG_SOC_SHARKL5)$(CONFIG_SOC_ROC1)$(CONFIG_SOC_SHARKL5PRO)$(CONFIG_SOC_ORCA),)
obj-y += sprd/
endif

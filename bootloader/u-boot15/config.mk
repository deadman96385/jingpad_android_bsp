#
# (C) Copyright 2000-2013
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#
#########################################################################

# This file is included from ./Makefile and spl/Makefile.
# Clean the state to avoid the same flags added twice.
#
# (Tegra needs different flags for SPL.
#  That's the reason why this file must be included from spl/Makefile too.
#  If we did not have Tegra SoCs, build system would be much simpler...)
PLATFORM_RELFLAGS :=
PLATFORM_CPPFLAGS :=
PLATFORM_LDFLAGS :=
LDFLAGS :=
LDFLAGS_FINAL :=
OBJCOPYFLAGS :=
# clear VENDOR for tcsh
VENDOR :=
#########################################################################

ARCH := $(CONFIG_SYS_ARCH:"%"=%)
CPU := $(CONFIG_SYS_CPU:"%"=%)
ifdef CONFIG_SPL_BUILD
ifdef CONFIG_TEGRA
CPU := arm720t
endif
endif
BOARD := $(CONFIG_SYS_BOARD:"%"=%)
ifneq ($(CONFIG_SYS_VENDOR),)
VENDOR := $(CONFIG_SYS_VENDOR:"%"=%)
endif
ifneq ($(CONFIG_SYS_SOC),)
SOC := $(CONFIG_SYS_SOC:"%"=%)
endif

# Some architecture config.mk files need to know what CPUDIR is set to,
# so calculate CPUDIR before including ARCH/SOC/CPU config.mk files.
# Check if arch/$ARCH/cpu/$CPU exists, otherwise assume arch/$ARCH/cpu contains
# CPU-specific code.
CPUDIR=arch/$(ARCH)/cpu$(if $(CPU),/$(CPU),)

sinclude $(srctree)/arch/$(ARCH)/config.mk	# include architecture dependend rules
sinclude $(srctree)/$(CPUDIR)/config.mk		# include  CPU	specific rules

ifdef	SOC
sinclude $(srctree)/$(CPUDIR)/$(SOC)/config.mk	# include  SoC	specific rules
endif
ifneq ($(BOARD),)
ifdef	VENDOR
BOARDDIR = $(VENDOR)/$(BOARD)
else
BOARDDIR = $(BOARD)
endif
endif
ifdef	BOARD
sinclude $(srctree)/board/$(BOARDDIR)/config.mk	# include board specific rules
endif

ifeq ($(AUTOBOOT_FLAG), true)
PLATFORM_CPPFLAGS += -DCONFIG_AUTOBOOT
endif

ifdef FTRACE
PLATFORM_CPPFLAGS += -finstrument-functions -DFTRACE
endif

# Allow use of stdint.h if available
ifneq ($(USE_STDINT),)
PLATFORM_CPPFLAGS += -DCONFIG_USE_STDINT
endif

#########################################################################

RELFLAGS := $(PLATFORM_RELFLAGS)

OBJCOPYFLAGS += --gap-fill=0xff

PLATFORM_CPPFLAGS += $(RELFLAGS)
PLATFORM_CPPFLAGS += -pipe
PLATFORM_CPPFLAGS += $(UBOOT_DEBUG_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_SECURE_BOOT_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_TOS_TRUSTY_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_TEECFG_CUSTOM_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_CHIP_UID_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_FIREWALL_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_ARMV7_LPAE_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_KERNEL_CMDLINE_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_PCTOOL_CHECK_MULTI_FIXNV_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_PCTOOL_CHECK_WRITE_PROTECT_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_ROC1_CACHE_WA_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_CALIMODE_USE_BOOTIMG_FLAG)
PLATFORM_CPPFLAGS += $(UBOOT_HWFEATURE_FLAG)

LDFLAGS += $(PLATFORM_LDFLAGS)
LDFLAGS_FINAL += -Bstatic

export PLATFORM_CPPFLAGS
export RELFLAGS
export LDFLAGS_FINAL
export CONFIG_STANDALONE_LOAD_ADDR

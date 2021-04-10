#
# (C) Copyright 2006
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# (C) Copyright 2002
# Daniel Engström, Omicron Ceti AB, daniel@omicron.se.
#
# SPDX-License-Identifier:	GPL-2.0+
#

extra-y	= start.o
obj-$(CONFIG_X86_RESET_VECTOR) += resetvec.o start16.o
obj-y	+= interrupts.o cpu.o call64.o page64.o

obj-$(CONFIG_INTEL_BAYTRAIL) += baytrail/
obj-$(CONFIG_SYS_COREBOOT) += coreboot/
obj-$(CONFIG_QEMU) += qemu/
obj-$(CONFIG_NORTHBRIDGE_INTEL_SANDYBRIDGE) += ivybridge/
obj-$(CONFIG_NORTHBRIDGE_INTEL_IVYBRIDGE) += ivybridge/
obj-$(CONFIG_INTEL_QUARK) += quark/
obj-$(CONFIG_INTEL_QUEENSBAY) += queensbay/
obj-$(CONFIG_BASEIA) += baseia/
obj-y += irq.o lapic.o
obj-$(CONFIG_SMP) += mp_init.o
obj-y += mtrr.o
obj-$(CONFIG_PCI) += pci.o
obj-$(CONFIG_SMP) += sipi_vector.o
obj-y += turbo.o
obj-$(CONFIG_INTEL_MICROCODE) += microcode_intel.o
obj-$(CONFIG_TARGET_SP9861E_1H10) += dvfs.o
obj-$(CONFIG_TARGET_SP9861E_1H11) += dvfs.o
obj-$(CONFIG_TARGET_SP9861E_2H10) += dvfs.o
obj-$(CONFIG_TARGET_SP9861E_2H10_2705) += dvfs.o
obj-$(CONFIG_TARGET_SP9861E_3H10) += dvfs.o
obj-$(CONFIG_TARGET_SP9853I_1H10) += dvfs.o
obj-$(CONFIG_TARGET_SP9853I_9C10) += dvfs.o
obj-$(CONFIG_TARGET_SP9853I_10C10) += dvfs.o

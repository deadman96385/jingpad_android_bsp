#
# The MIT License (MIT)
# Copyright (c) 2008-2015 Travis Geiselbrecht
# Copyright (c) 2016, Spreadtrum Communications.
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files
# (the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge,
# publish, distribute, sublicense, and/or sell copies of the Software,
# and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

ifneq ($(CONFIG_SC9833)$(CONFIG_SOC_SHARKLJ1)$(CONFIG_SPRD_SOC_SP9853I),)
obj-y += sprd_crypto.o
ccflags-y := -I$(srctree)/drivers/crypto/sprd/r3p0/inc
endif

ifneq ($(CONFIG_SOC_PIKE2)$(CONFIG_SOC_SHARKLE)$(CONFIG_SOC_SHARKL3)$(CONFIG_SOC_SHARKL5)$(CONFIG_SOC_ROC1)$(CONFIG_SOC_SHARKL5PRO),)
ifneq ($(CONFIG_GET_CPU_SERIAL_NUMBER),)
obj-y += sprdsha256.o
endif
obj-y += sprd_crypto.o
ccflags-y := -I$(srctree)/drivers/crypto/sprd/r2p0lite/inc
endif

ifneq ($(CONFIG_SOC_IWHALE2),)
obj-y += sprd_crypto_r2p0.o
ccflags-y := -I$(srctree)/drivers/crypto/sprd/r2p0/inc
endif

ifneq ($(CONFIG_SOC_ORCA),)
obj-y += sprd_crypto_sw.o
ccflags-y := -I$(srctree)/drivers/crypto/sprd/sw/inc
endif

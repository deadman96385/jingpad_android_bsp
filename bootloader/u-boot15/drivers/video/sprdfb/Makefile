#
# (C) Copyright 2000-2007
# Haibing.Yang haibing.yang@spreadtrum.com
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

# obj-$(CONFIG_LCD) += sprdfb_backlight.o

## basic fb driver
obj-$(CONFIG_LCD) += sprdfb_main.o sprdfb_panel.o sprdfb_chip_common.o
obj-$(CONFIG_LCD) += sprdfb_rgb.o sprdfb_mipi.o sprdfb_dsi.o
ifeq ($(CONFIG_FB_SWDISPC), y)
	obj-$(CONFIG_LCD) += sprdfb_swdispc.o
else
	obj-$(CONFIG_LCD) += sprdfb_dispc.o
endif

## old panel interface
ifeq ($(CONFIG_LCD), y)
obj-$(CONFIG_I2C) += sprdfb_mcu.o sprdfb_i2c.o
obj-$(CONFIG_SPI) += sprdfb_spi.o
endif

## related to specific chip
ifeq ($(CONFIG_LCD), y)
obj-$(CONFIG_SC9836A) += sprdfb_chip_9630.o
obj-$(CONFIG_SC9838A) += sprdfb_chip_9630.o
obj-$(CONFIG_SC9630) += sprdfb_chip_9630.o
obj-$(CONFIG_SC8830) += sprdfb_chip_8830.o
obj-$(CONFIG_SC9001) += sprdfb_chip_9001.o
obj-$(CONFIG_SC9860) += sprdfb_chip_9860.o
obj-$(CONFIG_SC9833) += sprdfb_chip_9833.o
obj-$(CONFIG_SOC_SHARKLJ1) += sprdfb_chip_9851.o
obj-$(CONFIG_SOC_SHARKLE) += sprdfb_chip_9835.o
obj-$(CONFIG_SOC_SHARKL3) += sprdfb_chip_9855.o
obj-$(CONFIG_SOC_ROC1) += sprdfb_chip_710.o
obj-$(CONFIG_SOC_SHARKL5) += sprdfb_chip_510.o
obj-$(CONFIG_SOC_SHARKL5PRO) += sprdfb_chip_518.o
obj-$(CONFIG_SOC_IWHALE2) += sprdfb_chip_9861.o
obj-$(CONFIG_SPRD_SOC_SP9853I) += sprdfb_chip_9853i.o
obj-$(CONFIG_SOC_PIKE2) += sprdfb_chip_7731e.o

obj-$(CONFIG_ROUND_CORNER_SUPPORT) += sprdfb_round_corner.o
endif

## only related to FPGA
obj-$(CONFIG_FPGA)+= sprdfb_gpio2spi.o
obj-$(CONFIG_FPGA)+= sprdfb_usc28c_init.o

obj-y += lcd/
obj-y += dsi_1_21a/

#
# (C) Copyright 2000-2007
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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

obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_api.o mipi_dsih_hal.o

ifdef CONFIG_FB_USE_MEGACORES_MIPI_DPHY
ifdef CONFIG_SC9001
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy_megacores_whale.o
else
ifdef CONFIG_SC9860
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy_megacores_whale.o
else
ifdef CONFIG_SOC_SHARKLE
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy_megacores_whale.o
else
ifdef CONFIG_SOC_PIKE2
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy_megacores_whale.o
else
ifdef CONFIG_SOC_SHARKLJ1
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy_megacores_whale.o
else
ifdef CONFIG_SC9833
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy_megacores_whale.o
else
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy_megacores.o
endif
endif
endif
endif
endif
endif
else
ifdef CONFIG_DSIH_INTER_PHY
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy_intel.o
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy_intel_pll.o
else
obj-$(CONFIG_DSIH_VERSION_1P21A) += mipi_dsih_dphy.o
endif
endif

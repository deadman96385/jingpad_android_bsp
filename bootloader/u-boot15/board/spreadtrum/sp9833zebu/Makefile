#
# (C) Copyright 2009 DENX Software Engineering
# Author: John Rigby <jcrigby@gmail.com>
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#


obj-y	= sp9833zebu.o sprd_kp.o sprd_bl.o pinmap-sp9630.o sdio_cfg.o modem_entry.o lcd_printf.o

ifneq ($(CONFIG_ARCH_SCX35L2),y)
obj-y	= ldo_sleep.o
endif


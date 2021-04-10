#
# Copyright (c) 2013 Google, Inc
#
# SPDX-License-Identifier:	GPL-2.0+
#

obj-$(CONFIG_DM)	+= device.o lists.o root.o uclass.o util.o
ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_OF_CONTROL) += simple-bus.o
endif
obj-$(CONFIG_DM_DEVICE_REMOVE)	+= device-remove.o
obj-y	+= fdtaddr.o of_extra.o ofnode.o read.o
obj-$(CONFIG_OF_LIVE) += of_access.o of_addr.o

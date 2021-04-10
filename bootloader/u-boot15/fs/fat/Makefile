#
#
# SPDX-License-Identifier:	GPL-2.0+
#

obj-$(CONFIG_FS_FAT)	:= fat.o
obj-$(CONFIG_FAT_WRITE):= fat_write.o
obj-$(CONFIG_FAT_WRITE) += fat_format.o fat_check.o

ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_FS_FAT)	+= file.o
endif

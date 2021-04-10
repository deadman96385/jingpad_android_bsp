obj-y += dl_common.o dl_crc.o dl_channel.o dl_stdio.o packet.o

obj-y += dl_cmd_proc.o

obj-y += root_inspect.o
ifndef CONFIG_NAND_BOOT
obj-y += dl_operate.o sparse_img.o sparse_crc32.o
else
obj-y += dl_nand_operate.o dl_ubi.o parsemtdparts.o dl_mtdparts.o
endif

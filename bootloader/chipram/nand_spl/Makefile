obj-$(CONFIG_UFS_BOOT) += ufs/

ifdef CONFIG_DDR_BOOT
obj-y += ddr_boot.o
else
ifdef CONFIG_EMMC_BOOT
ifneq ($(CONFIG_MMC_V40),)
obj-y += emmc_boot.o mmc_v40.o part.o part_efi.o
endif
else
ifdef CONFIG_UFS_BOOT
obj-y += ufs_boot.o part.o part_efi.o
else
obj-y += nand_boot.o
ifdef CONFIG_DOLPHIN
obj-y += dolphin_nand.o
else
ifdef CONFIG_SPRD_NAND_R6P0
obj-y += sprd_nand_r6p0.o
else
ifdef CONFIG_SPRD_NAND_R5P0
obj-y += sprd_nand_r5p0.o
else
ifdef CONFIG_SC9630
obj-y += sc9630_nand.o
else
obj-y += sc8830_nand.o
endif
endif
endif
endif
endif
endif
endif

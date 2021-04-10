#ifndef __CONFIG_H
#define __CONFIG_H

#include <configs/soc-sprd-isharkl2.h>
#include <configs/x86-sprd-common.h>

#define CONFIG_SPRD_SOC_SP9853I

#define CONFIG_DTS_MEM_LAYOUT

/*******DDR CONFIG************************/
#define CONFIG_E820_AUTO_DETECT
#define CONFIG_NR_DRAM_BANKS	1
/* PHYS_SDRAM_1_SIZE =1.5G -3M, reserve 3M for ddr traning*/
#define PHYS_SDRAM_1_SIZE	0x5fd00000

/***********MEMORY LAYOUT****************/
#define SETUP_DATA_OFFSET 0x10
#define DEFAULT_SETUP_BASE 0x350c0000
#define DEFAULT_SETUP_DTB_ADDR 0x3b000000
#define DT_ADR 	DEFAULT_SETUP_DTB_ADDR + SETUP_DATA_OFFSET
#define RAMDISK_ADR 0X3b800000
#define KERNEL_ADR  0x35100000
#define BOOTIMG_ADR 0X39000000

/*for sysdump*/
#define CONFIG_SPRD_SYSDUMP
#define KERNEL_BASE    (KERNEL_ADR - 0x100000)
#define CONFIG_RAMDUMP_NO_SPLIT 1 /* Don't split sysdump file */
#define SYSDUMP_COPY_PADDR  (KERNEL_ADR-0x100000-0x20000000)
#define SYSDUMP_MAPPING_ADDR  0x60000000
#define SPLIT_MEM_REGION 0
#define CONFIG_SHA1

/*lcd config*/
#define CONFIG_LCD
#ifdef CONFIG_LCD
#define CONFIG_FB_ADDR 0x0
#define CONFIG_DSIH_INTER_PHY
#define CONFIG_DSIH_VERSION_1P21A
#define CONFIG_SPLASH_SCREEN
#define CONFIG_CMD_BMP
#define CONFIG_BMP_16BPP
#define LCD_BPP LCD_COLOR16
#define CONFIG_FB_LCD_NT35532_2_MIPI
#define LCM_NT35532_2_I2C_BUS_NUM  3
#define LCM_GPIO_AVDDEN 31

#define LCM_GPIO_RSTN   126
#define CONFIG_LCD_1080P
#endif
/*charge config*/
#define CONFIG_SPRD2705_CHARGE_IC
#define CONFIG_SPRDCHG_I2C_BUS 4

#define CONFIG_MISC_INIT_R
/**********vmm related***********/
#define VMM_RESERVE_SIZE 0

#define CONFIG_USB_UTMI_WIDTH_8

#endif /* __CONFIG_H */

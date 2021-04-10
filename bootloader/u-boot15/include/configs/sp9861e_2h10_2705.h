#ifndef __CONFIG_H
#define __CONFIG_H

#include <configs/x86-sprd-common.h>
#include <configs/soc-sprd-iwhale2.h>
#define CONFIG_SOC_IWHALE2

/*used in usb drv*/
#define CONFIG_USB_ENUM_IN_UBOOT
#define TMSC_16NM_FFPLL 0x5533166e /* USB3.0_PHY_TSMC_16NM */
#define USB3_PHY_TUNE1 0x919e9dec
#define USB3_PHY_TUNE2 0x0f0560fe

/*******DDR CONFIG************************/
#define CONFIG_E820_AUTO_DETECT
#define CONFIG_NR_DRAM_BANKS        1
#define PHYS_SDRAM_1_SIZE           0x60000000
/***********MEMORY LAYOUT****************/
#define SETUP_DATA_OFFSET           0x10
#define DT_ADR                      DEFAULT_SETUP_DTB_ADDR+SETUP_DATA_OFFSET
#define RAMDISK_ADR                 0x3b800000
#define KERNEL_ADR                  0x35100000
#define BOOTIMG_ADR                 0x39000000
#define DEFAULT_SETUP_DTB_ADDR      0x3b000000
#define DEFAULT_SETUP_BASE          0x350c0000
/****************************************/

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
#define LCM_GPIO_AVDDEN 171
#define LCM_GPIO_AVEEEN 172
#define LCM_GPIO_RSTN   126
#define CONFIG_LCD_1080P
#endif

#define CONFIG_DL_POWER_CONTROL

#define CONFIG_MISC_INIT_R
/**********vmm related***********/
#define VMM_RESERVE_SIZE 0

#undef CONFIG_SPRD2701_CHARGE_IC
#define CONFIG_SPRD2705_CHARGE_IC

#endif /* __CONFIG_H */

/*
 * (C) Copyright 2009 DENX Software Engineering
 * Author: John Rigby <jrigby@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

//#define CONFIG_SECURE_BOOT
//#define CONFIG_ROM_VERIFY_SPL

/* Flat Device Tree Definitions */
#define CONFIG_OF_LIBFDT
#define CONFIG_SPRD_PLATFORM

#define DT_PLATFROM_ID 9830
#define DT_HARDWARE_ID 1
#define DT_SOC_VER     0x20000

//only used in fdl2 .in uart download, the debug infors  from  serial will break the download process.

#define BOOT_NATIVE_LINUX_MODEM  1
#define CONFIG_SILENT_CONSOLE

/*
 * SPREADTRUM BIGPHONE board - SoC Configuration
 */
#define CONFIG_SC9630
#define CONFIG_ADIE_SC2723
#define CONFIG_ARCH_SCX35L

#define DFS_ON_ARM7
#define DFS_PARAM_SRC_ADDR     0x0001c0c
#define DFS_PARAM_TARGET_ADDR  0x50805400
#define DFS_PARAM_LEN  0x400

//#define CONFIG_SUPPORT_TDLTE
#define TDDSP_ADR       0x88020000
#define CONFIG_SUPPORT_LTE
//#define CONFIG_SUPPORT_WLTE
//#define CONFIG_SUPPORT_GSM

#define LTE_GDSP_LOAD_OFFSET	0x20000

#define LTE_FIXNV_SIZE 0x0006C000 // 272K the max size is 512k
#define LTE_RUNNV_SIZE 0x00090000 // 400k the max size is 512k
#define LTE_FIXNV_ADDR 0x8AA42000
#define LTE_RUNNV_ADDR (LTE_FIXNV_ADDR + LTE_FIXNV_SIZE)
#define LTE_MODEM_SIZE 0x00E00000
#define LTE_MODEM_ADDR 0x8AB48000
#define LTE_LDSP_SIZE  0x00300000
#define LTE_LDSP_ADDR  0x89900000
#define LTE_GDSP_SIZE  0x002E0000
#define LTE_GDSP_ADDR (0x89600000 + LTE_GDSP_LOAD_OFFSET)

#define WL_WARM_SIZE 0x00200000
#define WL_WARM_ADDR 0X8D900000

#define GSM_FIXNV_SIZE 0x20000
#define GSM_FIXNV_ADDR 0x88a90000
#define GSM_RUNNV_SIZE 0x40000
#define GSM_RUNNV_ADDR 0x88ab0000
#define GSM_MODEM_ADDR 0X88400000  //equal to WL_DSDA_WARM_ADDR
#define GSM_MODEM_SIZE 0x670000    //equal to WL_DSDA_WARM_SIZE
#define GSM_DSP_ADDR   0x88000000
#define GSM_DSP_SIZE   0x400000
#define FIXNV_SIZE     LTE_FIXNV_SIZE

#define CONFIG_DFS_ENABLE
#define DFS_ADDR    0x50800000
#define DFS_SIZE    32768 //32K

#ifdef SECURE_BOOT_ENABLE
#define MODEM_SIZE		(0x800000)
#define DSP_SIZE		(0x2E0000)
#endif

#define RUNTIMENV_SIZE		(3*128 * 1024)
#ifdef CONFIG_ROM_VERIFY_SPL
#define CONFIG_SPL_LOAD_LEN     (0x8000)	/* 32 KB */
#define CONFIG_BOOTINFO_LENGTH  (0x200)	/* 512 Bytes */
#define PUBKEY_BSC_BLOCK_INDEX  (CONFIG_SPL_LOAD_LEN - CONFIG_BOOTINFO_LENGTH * 2) / EMMC_SECTOR_SIZE
#define PUBKEY_VLR_BLOCK_INDEX  2
#define PUBKEY_READ_BLOCK_NUMS  1
#define CONFIG_SPL_HASH_LEN     (0x400)	/* 1KB */
#else
#define CONFIG_SPL_LOAD_LEN (0x6000)
#define PUBKEY_BSC_BLOCK_INDEX 0
#define PUBKEY_VLR_BLOCK_INDEX 0
#define PUBKEY_READ_BLOCK_NUMS (SEC_HEADER_MAX_SIZE / EMMC_SECTOR_SIZE)
#define CONFIG_SPL_HASH_LEN (0xC00) /* 3KB */
#endif

#define CP1_ZERO_MAP_ADR    0x50001000
#define CP1_EXEC_ADR        LTE_MODEM_ADDR

#define CONFIG_SYS_INIT_SP_ADDR     \
	(CONFIG_SYS_SDRAM_END - 0x10000 - GENERATED_GBL_DATA_SIZE)

#define CONFIG_SKIP_LOWLEVEL_INIT

/*
 * MMC definition
 */
#define CONFIG_EMMC_BOOT
#define CONFIG_SPRD_MMC
#define CONFIG_SUPPORT_EMMC_BOOT
#ifdef  CONFIG_EMMC_BOOT
#define EMMC_SECTOR_SIZE 512
#define CONFIG_FS_EXT4
#define CONFIG_EXT4_WRITE
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_EXT4_WRITE
#define CONFIG_EXT4_SPARSE_DOWNLOAD
#endif
#define CONFIG_CMD_FAT			1
#define CONFIG_FAT_WRITE		1
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_SDHCI
#define CONFIG_SYS_MMC_MAX_BLK_COUNT	0x1000
#define CONFIG_MMC_SDMA
#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION		1

/*timer*/
#define CONFIG_SYS_HZ			1000
#define CONFIG_SPRD_TIMER_CLK		1000 /*32768*/


/*
 * Memory Info
 */
/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 3 * 1024 * 1024)
/*
 * Board has 2 32MB banks of DRAM but there is a bug when using
 * both so only the first is configured
 */
#define CONFIG_NR_DRAM_BANKS	1
#define PHYS_SDRAM_1		0x80000000
#define PHYS_SDRAM_1_SIZE	0x20000000
#if (CONFIG_NR_DRAM_BANKS == 2)
#define PHYS_SDRAM_2		0x90000000
#define PHYS_SDRAM_2_SIZE	0x10000000
#endif
#define CONFIG_SYS_SDRAM_BASE PHYS_SDRAM_1
#define CONFIG_SYS_SDRAM_END (CONFIG_SYS_SDRAM_BASE + PHYS_SDRAM_1_SIZE)
/* 8MB DRAM test */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_1+0x0800000)
#define CONFIG_STACKSIZE	(256 * 1024)	/* regular stack */

/*
 * Flash & Environment
 */
/* No NOR flash present */
#define CONFIG_SYS_NO_FLASH	1
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE		(128 * 1024)

#define CONFIG_DDR_AUTO_DETECT
#define CONFIG_NR_DRAM_BANKS_ADDR_IN_IRAM    0x1C00   /* IRAM store ddr info */

/* U-Boot general configuration */
#define CONFIG_SYS_PROMPT	"=> "	/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size  */
/* Print buffer sz */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + \
		sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS	32	/* max number of command args */
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE
#define CONFIG_SYS_LONGHELP

#define CONFIG_LOADADDR		(CONFIG_SYS_TEXT_BASE - CONFIG_SYS_MALLOC_LEN - 4*1024*1024)	/* loadaddr env var */
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR

#define CONFIG_BOOTDELAY	0
#define CONFIG_BOOTCOMMAND "cboot normal"
#define CONFIG_EXTRA_ENV_SETTINGS				""

/*used in usb drv*/
#define CHIP_ENDIAN_LITTLE
#define _LITTLE_ENDIAN 1
#define CONFIG_USB_GADGET_SC8800G
#define CONFIG_USB_DWC
#define CONFIG_USB_GADGET_DUALSPEED
#define CONFIG_MODEM_CALIBERATE
#define CALIBRATE_ENUM_MS 3000
#define CALIBRATE_IO_MS 2000
#define CONFIG_DWC_OTG

/*lcd config*/
#define CONFIG_LCD
#ifdef  CONFIG_LCD
#define CONFIG_DSIH_VERSION_1P21A
#define CONFIG_SPLASH_SCREEN
#define LCD_BPP LCD_COLOR16
#define CONFIG_LCD_FWVGA
#define CONFIG_CMD_BMP

#define CONFIG_FB_LCD_OTM8019A_MIPI
#define CONFIG_SYS_WHITE_ON_BLACK
#ifdef  LCD_TEST_PATTERN
#define CONSOLE_COLOR_RED 0xf800
#define CONSOLE_COLOR_GREEN 0x07e0
#define CONSOLE_COLOR_YELLOW 0x07e0
#define CONSOLE_COLOR_BLUE 0x001f
#define CONSOLE_COLOR_MAGENTA 0x001f
#define CONSOLE_COLOR_CYAN 0x001f
#endif
#endif // CONFIG_LCD

/*for sysdump*/
#define CONFIG_SPRD_SYSDUMP
#define CONFIG_RAMDUMP_NO_SPLIT 1	/* Don't split sysdump file */
#define SPRD_SYSDUMP_MAGIC		RAMDISK_ADR
#define REAL_SDRAM_SIZE 0x40000000	/*dump 1G */


//#define LOW_BAT_ADC_LEVEL 782 /*phone battery adc value low than this value will not boot up*/
#define LOW_BAT_VOL            3400 /*phone battery voltage low than this value will not boot up*/
#define LOW_BAT_VOL_CHG        3300    //3.3V charger connect

#define PWR_KEY_DETECT_CNT 2 /*this should match the count of boot_pwr_check() function */
#define ALARM_LEAD_SET_MS 0 /* time set for alarm boot in advancd */

#define PHYS_OFFSET_ADDR			0x80000000
//#define TD_CP_OFFSET_ADDR			0x8000000	/*128*/
//#define TD_CP_SDRAM_SIZE			0x1200000	/*18M*/
//#define WCDMA_CP_OFFSET_ADDR		0x10000000	/*256M*/
//#define WCDMA_CP_SDRAM_SIZE		0x4000000	/*64M*/
#define GGE_CP_OFFSET_ADDR 		0x08000000       /*128M*/
#define GGE_CP_SDRAM_SIZE 		0x01600000 	/*22M*/
#define LTE_CP_OFFSET_ADDR      0x09600000     /*150M*/
#define LTE_CP_SDRAM_SIZE       0x04A80000     /*74.5M*/
#define PMIC_IRAM_ADDR 		0x50800000       /*pmic arm7 iram address remap at AP side*/
#define PMIC_IRAM_SIZE 		0x8000       /*32K*/
#define SIPC_APCP_RESET_ADDR_SIZE	0xC00	/*3K*/
#define SIPC_APCP_RESET_SIZE	0x1000	/*4K*/
#define CALIBRATION_CMDLINE_SIZE 0x400	/*1K*/
//#define SIPC_TD_APCP_START_ADDR		(PHYS_OFFSET_ADDR + TD_CP_OFFSET_ADDR + TD_CP_SDRAM_SIZE - SIPC_APCP_RESET_SIZE)	/*0x897FF000*/
//#define SIPC_WCDMA_APCP_START_ADDR	(PHYS_OFFSET_ADDR + WCDMA_CP_OFFSET_ADDR + WCDMA_CP_SDRAM_SIZE - SIPC_APCP_RESET_SIZE) /*0x93FFF000*/
#define SIPC_GGE_APCP_START_ADDR 	(PHYS_OFFSET_ADDR + GGE_CP_OFFSET_ADDR + GGE_CP_SDRAM_SIZE - SIPC_APCP_RESET_SIZE) 	/*0x895ff000*/
#define SIPC_LTE_APCP_START_ADDR    (0x8AA40000)
#define SIPC_PMIC_SIPC_START_ADDR   (0x5000B000)         /*0x50807400*/
#define CALIBRATION_FLAG_CP0        (0x88AF0000)
#define CALIBRATION_FLAG_CP1        (0x8AA41800)

/*7S reset config*/
#define CONFIG_7S_RST_MODULE_EN		1	//0:disable module; 1:enable module

#ifdef DEBUG
#define CONFIG_7S_RST_SW_MODE	1	//0:hw reset,1:arm reset,power keep on	//soft for debug version
#else
#define CONFIG_7S_RST_SW_MODE	0	//0:hw reset,1:arm reset,power keep on	//hard for user version
#endif

#define CONFIG_7S_RST_SHORT_MODE	1	//0:long press then release key to trigger;1:press key some time to trigger
#define CONFIG_7S_RST_2KEY_MODE		0	//0:1Key--Normal mode; 1:2KEY
#define CONFIG_7S_RST_THRESHOLD		7	//7S, hold key down for this time to trigger

 /*SMPL config*/
//#define CONFIG_SMPL_EN
#define CONFIG_SMPL_THRESHOLD 	0		//one step is 0.25S

#define DT_ADR          0x85400000
#define KERNEL_ADR      0x80008000
#define VLX_TAG_ADDR    0x82000100
#define RAMDISK_ADR     0x85500000
#define CONFIG_ARCH_SHARK
#define CONFIG_PREBOOT "role"
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_SEPARATE_DT

/* Chip Driver Macro Definitions Start*/
/*sprd adc*/
#define CONFIG_SPRD_ADC

/*sprd adi*/
#define CONFIG_SPRD_ADI

/*sprd gpio*/
#define CONFIG_SPRD_GPIO

/*sprd rtc*/
#define CONFIG_RTC_SPRD

/*sprd watchdog*/
#define CONFIG_HW_WATCHDOG
#define CONFIG_SPRD_WATCHDOG

 /*Serial Info*/
#define CONFIG_SPRD_UART		1
#define CONFIG_SYS_SC8800X_UART1	1
#define CONFIG_CONS_INDEX	1	/* use UART0 for console */
#define CONFIG_BAUDRATE		115200	/* Default baud rate */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_SPRD_UART_PORTS	{ (void *) (CONFIG_SYS_SERIAL0), (void *) (CONFIG_SYS_SERIAL1) }
#define CONFIG_SYS_SERIAL0		0x70000000
#define CONFIG_SYS_SERIAL1		0x70100000

/* Chip Driver Macro Definitions End*/

/*active arm7 ram before access to it*/
#define CONFIG_ARM7_RAM_ACTIVE


#endif /* __CONFIG_H */


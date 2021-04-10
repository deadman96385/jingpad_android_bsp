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

#include <asm/arch/soc_config.h>

#define CONFIG_X86 1
#define CONFIG_SOC_IWHALE2
#define CONFIG_ADIE_SC2731
//dual_backup
#define CONFIG_DUAL_BACKUP
#define IMAGE_HEAD_SIZE		(512)

/*these MACRO used for param transmit through researchdownload */
#define CONFIG_CLK_PARA
#ifdef CONFIG_CLK_PARA
#define MAGIC_HEADER	0x5555AAAA
#define MAGIC_END	0xAAAA5555
#define CONFIG_PARA_VERSION 2


#ifdef CONFIG_NAND_SPL
#define CLK_DDR_FREQ        1400000000//power on mode
#else
#define CLK_DDR_FREQ        1400000000//download mode
#endif

#define DCDC_MEM 1100
#define DDR_IP_CONFIG_FILE
//clk_list
#define CLK_LEVEL_COUNT_MAX  6
#define CLK_AXI_LEVEL 4
#define CLK_AXI_LEVEL_ID 3
#define CLK_DAP_LEVEL 6
#define CLK_DAP_LEVEL_ID 5
#define CLK_APB_LEVEL 4
#define CLK_APB_LEVEL_ID 3
#define CLK_AON_APB_LEVEL 6
#define CLK_AON_APB_LEVEL_ID 5

#endif

//only used in fdl2 .in uart download, the debug infors  from  serial will break the download process.
#define CONFIG_FDL2_PRINT        0
#define BOOT_NATIVE_LINUX        1
#define BOOT_NATIVE_LINUX_MODEM  1
#define CALIBRATION_FLAG         0x897FFC00
#define	CALIBRATION_FLAG_WCDMA	 0x93FFEC00
#define CONFIG_SILENT_CONSOLE
#define CONFIG_GPIOLIB 1
//#define NAND_DEBUG  
//#define DEBUG
#define CONFIG_SDRAMDISK
#define UBOOT_HASH_SIZE   0x200
#define U_BOOT_SPRD_VER 1
/*#define SPRD_EVM_TAG_ON 1*/
#ifdef SPRD_EVM_TAG_ON
#define SPRD_EVM_ADDR_START 0x00026000
#define SPRD_EVM_TAG(_x) (*(((unsigned long *)SPRD_EVM_ADDR_START)+_x) = *(volatile unsigned long *)0x87003004)
#endif
#define CONFIG_L2_OFF			1

#define BOOT_DEBUG 1

#define CONFIG_YAFFS2 1

#define BOOT_PART "boot"
//#define BOOT_PART "kernel"
#define RECOVERY_PART "recovery"
/*
 * SPREADTRUM BIGPHONE board - SoC Configuration
 */
//#define CONFIG_FPGA
//#define CONFIG_SPX35L64_FPGA
#define CONFIG_SCX35L64

#define CONFIG_SUPPORT_TDLTE
//#define CONFIG_SUPPORT_WLTE
#define CONFIG_SUPPORT_GSM

#define LTE_FIXNV_SIZE 0x20000
#define LTE_RUNNV_SIZE 0x40000
#define LTE_FIXNV_ADDR 0x8a310000
#define LTE_RUNNV_ADDR 0x8a330000
#define LTE_MODEM_SIZE 0x8f0000
#define LTE_MODEM_ADDR 0x89a00000
#define LTE_LDSP_SIZE  0x1c00000
#define LTE_LDSP_ADDR  0x8a380000
#define LTE_GDSP_SIZE 0x400000
#define LTE_GDSP_ADDR 0x89600000

#define WL_WARM_SIZE 0x670000
#define WL_WARM_ADDR 0X88400000

#define GSM_FIXNV_SIZE 0x20000
#define GSM_FIXNV_ADDR 0x88a90000
#define GSM_RUNNV_SIZE 0x40000
#define GSM_RUNNV_ADDR 0x88ab0000
#define GSM_MODEM_ADDR 0X88400000  //equal to WL_DSDA_WARM_ADDR
#define GSM_MODEM_SIZE 0x670000    //equal to WL_DSDA_WARM_SIZE
#define GSM_DSP_ADDR   0x88000000
#define GSM_DSP_SIZE   0x400000
#define FIXNV_SIZE  LTE_FIXNV_SIZE

#define CONFIG_SVC_STACK_TEMP	0xE6022600
#define CONFIG_TEMP_STACK_DDR	0xE6022800
#define CONFIG_CHIP_ENV_SET
#define CHIPRAM_ENV_ADDR		0x3d100000
#define LP4_SIZE_ENV_ADDR		0x3d200000
#define CONFIG_SPL_STACK		0x3d400000

#define CONFIG_CP0_ARM0_BOOT
#define CONFIG_CP1_BOOT
#define CHIP_ENDIAN_LITTLE
#define _LITTLE_ENDIAN 1

#define CONFIG_RAM512M

#define CONFIG_EMMC_BOOT
#define CONFIG_ARCH_SCX35L

#ifdef  CONFIG_EMMC_BOOT
#define EMMC_SECTOR_SIZE 512

#define CONFIG_FS_EXT4
#define CONFIG_EXT4_WRITE
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_EXT4_WRITE

//#define CONFIG_TIGER_MMC
#define CONFIG_UEFI_PARTITION
#define CONFIG_EXT4_SPARSE_DOWNLOAD
//#define CONFIG_EMMC_SPL
#define CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM ((CONFIG_SYS_NAND_U_BOOT_SIZE+EMMC_SECTOR_SIZE-1)/EMMC_SECTOR_SIZE)
#endif
/*for emmc partition*/
#define CONFIG_LOAD_PARTITION
/*
 * MMC definition
 */
#define CONFIG_CMD_MMC
#ifdef  CONFIG_CMD_MMC
#define CONFIG_CMD_FAT			1
#define CONFIG_FAT_WRITE		1
#define CONFIG_MMC			1
#define CONFIG_GENERIC_MMC		1
#define CONFIG_SDHCI			1
#define CONFIG_SDHCI_CTRL_NO_HISPD 	1 /* disable high speed control */
#define CONFIG_SYS_MMC_MAX_BLK_COUNT	0x1000
#define CONFIG_MMC_SDMA			1
#define CONFIG_MV_SDHCI			1
#define CONFIG_DOS_PARTITION		1
#define CONFIG_EFI_PARTITION		1
#define CONFIG_SYS_MMC_NUM		1
#define CONFIG_SYS_MMC_BASE		{0x20600000}
#define CONFIG_SYS_SD_BASE		0x20300000
#endif

#define BB_DRAM_TYPE_256MB_32BIT

#define CONFIG_SYS_HZ			1000
#define CONFIG_SPRD_TIMER_CLK		1000 /*32768*/

//#define CONFIG_SYS_HUSH_PARSER
#define CP0_ZERO_MAP_ADR    0x50000000
#define CP0_ARM0_EXEC_ADR        0x88400000 

#define CP1_ZERO_MAP_ADR    0x50001000
#define CP1_EXEC_ADR        0x89a00000

#ifdef CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2 "> "
#endif

#define FIXNV_SIZE		(128 * 1024)
#define PRODUCTINFO_SIZE	(16 * 1024)
#define MODEM_SIZE		(0x800000)
#define DSP_SIZE		(0x2E0000)
#define VMJALUNA_SIZE		(0x64000) /* 400K */
#define RUNTIMENV_SIZE		(3*128 * 1024)
#define CONFIG_SPL_LOAD_LEN	(0x6000)

#define PRODUCTINFO_ADR		0x80490000

/*#define CMDLINE_NEED_CONV */

#define WATCHDOG_LOAD_VALUE	0x4000
#define CONFIG_SYS_STACK_SIZE	0x400
//#define CONFIG_SYS_TEXT_BASZE  0x80f00000

//#define	CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* 256 kB for U-Boot */

/* NAND BOOT is the only boot method */
#define CONFIG_NAND_U_BOOT
#define DYNAMIC_CRC_TABLE
/* Start copying real U-boot from the second page */
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x40000
#define CONFIG_SYS_NAND_U_BOOT_SIZE	0x8A000
#define RAM_TYPPE_IS_SDRAM	0
//#define FPGA_TRACE_DOWNLOAD //for download image from trace

/* Load U-Boot to this address */
#define CONFIG_UBOOT_MAX_SIZE 0x100000
#define CONFIG_SYS_NAND_U_BOOT_DST	0x5ec00000
#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_NAND_U_BOOT_DST
#define CONFIG_SYS_SDRAM_BASE 0x80000000
#define CONFIG_SYS_SDRAM_END (CONFIG_SYS_SDRAM_BASE + 256*1024*1024)

#ifdef CONFIG_NAND_SPL
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_END - 0x40000)
#else

#define CONFIG_MMU_TABLE_ADDR (0x00020000)
#define CONFIG_SYS_INIT_SP_ADDR     \
	(CONFIG_SYS_SDRAM_END - 0x10000 - GENERATED_GBL_DATA_SIZE)

#define CONFIG_SKIP_LOWLEVEL_INIT
#endif

#define CONFIG_HW_WATCHDOG
//#define CONFIG_AUTOBOOT //used for FPGA test, auto boot other image
//#define CONFIG_DISPLAY_CPUINFO

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_INITRD_TAG		1

/*
 * Memory Info
 */
/* malloc() len */
#define CONFIG_SYS_MALLOC_LEN		(2 << 20)	/* 1 MiB */
/*
 * Board has 2 32MB banks of DRAM but there is a bug when using
 * both so only the first is configured
 */
#define CONFIG_NR_DRAM_BANKS	1

#define PHYS_SDRAM_1		0x80000000
#define PHYS_SDRAM_1_SIZE	0x10000000
#if (CONFIG_NR_DRAM_BANKS == 2)
#define PHYS_SDRAM_2		0x90000000
#define PHYS_SDRAM_2_SIZE	0x10000000
#endif
/* 8MB DRAM test */
#define CONFIG_SYS_MEMTEST_START	PHYS_SDRAM_1
#define CONFIG_SYS_MEMTEST_END		(PHYS_SDRAM_1+0x0800000)
#define CONFIG_STACKSIZE	(256 * 1024)	/* regular stack */

/*
 * Serial Info
 */
#define CONFIG_SPRD_UART		1
#define CONFIG_SYS_SC8800X_UART1	1
#define CONFIG_CONS_INDEX	1	/* use UART0 for console */
#define CONFIG_BAUDRATE		115200	/* Default baud rate */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_SPRD_SPI
#define CONFIG_SPRD_I2C

/*
 * Flash & Environment
 */
/* No NOR flash present */
#define CONFIG_SYS_MONITOR_LEN ((CONFIG_SYS_NAND_U_BOOT_OFFS)+(CONFIG_SYS_NAND_U_BOOT_SIZE))
#define CONFIG_SYS_NO_FLASH	1
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE (128 * 1024)
/*
#define	CONFIG_ENV_IS_IN_NAND
#define	CONFIG_ENV_OFFSET	CONFIG_SYS_MONITOR_LEN
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)
*/

/* DDR */
#define DDR_AUTO_DETECT
#ifndef CONFIG_CLK_PARA
#ifdef CONFIG_NAND_SPL
#define DDR_FREQ 1400000000      //power on freq
#else
#define DDR_FREQ 1400000000      //download freq
#endif
#endif
#define DRAM_LPDDR4
#define DDR_DFTYPE_LP4 DRAM_LPDDR4_2CS_16G_X32
#define DDR_DFTYPE_LP3 DRAM_LPDDR3_2CS_24G_X32_X16X4
//#define DDR_DFTYPE_LP3 DRAM_LPDDR3_2CS_16G_X32_X16X4
#define CONFIG_DDR_DOUBLE_PUB
#define CONFIG_DDR_IP_CONFIG_FILE
#if 0
#define DDR_CLK 464
//---these three macro below,only one can be open
//#define DDR_LPDDR1
#define DDR_LPDDR2
//#define DDR_DDR3

//#define DDR_AUTO_DETECT
#define DDR_TYPE DRAM_LPDDR2_2CS_8G_X32
//#define DDR_TYPE DRAM_LPDDR2_1CS_4G_X32
//#define DDR_TYPE DRAM_LPDDR2_1CS_8G_X32
//#define DDR_TYPE DRAM_LPDDR2_2CS_16G_X32
//#define DDR_TYPE DRAM_DDR3_1CS_2G_X8_4P
//#define DDR_TYPE DRAM_DDR3_1CS_4G_X16_2P


//#define DDR_2_CH

#define DDR3_DLL_ON TRUE
//#define DLL_BYPASS
#define DDR_APB_CLK 128
#define DDR_DFS_SUPPORT
#define DDR_DFS_VAL_BASE 0X1c00

//#define DDR_SCAN_SUPPORT
#define MEM_IO_DS LPDDR2_DS_40R

#define PUBL_LPDDR1_DS PUBL_LPDDR1_DS_48OHM
#define PUBL_LPDDR2_DS PUBL_LPDDR2_DS_40OHM
#define PUBL_DDR3_DS   PUBL_DDR3_DS_34OHM
#endif
/* NAND */
#define CONFIG_SPRD_NAND_REGS_BASE	(0x21100000)
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		(0x21100000)
//#define CONFIG_JFFS2_NAND
//#define CONFIG_SPRD_NAND_HWECC
#define CONFIG_SYS_NAND_HW_ECC
#define CONFIG_SYS_NAND_LARGEPAGE
//#define CONFIG_SYS_NAND_5_ADDR_CYCLE

#define CONFIG_SYS_64BIT_VSPRINTF

#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_PARTITIONS
#define CONFIG_MTD_DEVICE
#define CONFIG_CMD_UBI
#define CONFIG_RBTREE

/* U-Boot general configuration */
#define CONFIG_SYS_PROMPT	"=> "	/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size  */
/* Print buffer sz */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + \
		sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS	32	/* max number of command args */
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE
#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_LONGHELP

/* support OS choose */
#undef CONFIG_BOOTM_NETBSD 
#undef CONFIG_BOOTM_RTEMS

/* U-Boot commands */
#include <config_cmd_default.h>
#define CONFIG_CMD_NAND
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_NET
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_SETGETDCR

#define CONFIG_ENV_OVERWRITE

#ifdef SPRD_EVM_TAG_ON
#define CONFIG_BOOTDELAY	0
#else
#define CONFIG_BOOTDELAY	0
#define CONFIG_ZERO_BOOTDELAY_CHECK
#endif

#define xstr(s)	str(s)
#define str(s)	#s

#define MTDIDS_DEFAULT "nand0=sprd-nand"
#define MTDPARTS_DEFAULT "mtdparts=sprd-nand:256k(spl),512k(2ndbl),256k(params),512k(vmjaluna),10m(modem),3840k(fixnv),3840k(backupfixnv),5120k(dsp),3840k(runtimenv),10m(boot),10m(recovery),250m(system),180m(userdata),20m(cache),256k(misc),1m(boot_logo),1m(fastboot_logo),3840k(productinfo),512k(kpanic)"
#define CONFIG_BOOTARGS "mem=256M loglevel=1 console=ttyS1,115200n8 init=/init " MTDPARTS_DEFAULT

#define COPY_LINUX_KERNEL_SIZE	(0x600000)
#define LINUX_INITRD_NAME	"modem"

#define CONFIG_BOOTCOMMAND "cboot normal"
#define	CONFIG_EXTRA_ENV_SETTINGS				""	

#ifdef CONFIG_CMD_NET
#define CONFIG_IPADDR 192.168.10.2
#define CONFIG_SERVERIP 192.168.10.5
#define CONFIG_NETMASK 255.255.255.0
#define CONFIG_USBNET_DEVADDR 26:03:ee:00:87:9f
#define CONFIG_USBNET_HOSTADDR 9a:04:c7:d6:30:d0


#define CONFIG_NET_MULTI
#define CONFIG_CMD_DNS
#define CONFIG_CMD_NFS
#define CONFIG_CMD_RARP
#define CONFIG_CMD_PING
/*#define CONFIG_CMD_SNTP */
#endif

#define CONFIG_USB_CORE_IP_293A
#define CONFIG_USB_GADGET_SC8800G
#define CONFIG_USB_DWC
#define CONFIG_USB_GADGET_DUALSPEED
//#define CONFIG_USB_ETHER
#define CONFIG_CMD_FASTBOOT
#define SCRATCH_ADDR    (CONFIG_SYS_SDRAM_BASE + 0x100000)
#define FB_DOWNLOAD_BUF_SIZE           (CONFIG_SYS_NAND_U_BOOT_DST - SCRATCH_ADDR-0x800000)
#define SCRATCH_ADDR_EXT1              (CONFIG_SYS_NAND_U_BOOT_DST + 32*1024*1024)
#define FB_DOWNLOAD_BUF_EXT1_SIZE      (224*1024*1024)
#define CONFIG_MODEM_CALIBERATE

#define CONFIG_LCD
#ifdef  CONFIG_LCD
#define CONFIG_DSIH_VERSION_1P21A
#define CONFIG_SPLASH_SCREEN
#define LCD_BPP LCD_COLOR16
//#define CONFIG_LCD_HVGA   1
//#define CONFIG_LCD_QVGA   1
//#define CONFIG_LCD_QHD 1
#define CONFIG_LCD_PAD_1024 1
//#define CONFIG_LCD_720P 1
//#define CONFIG_LCD_INFO
//#define LCD_TEST_PATTERN
//#define CONFIG_LCD_LOGO
//#define CONFIG_FB_LCD_S6D0139
//#define CONFIG_FB_LCD_SSD2075_MIPI
#define CONFIG_FB_LCD_ILI6150_LVDS
#define CONFIG_FB_LCD_NT35516_MIPI
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

#define CONFIG_SPRD_SYSDUMP
#include <asm/sizes.h>
#define SPRD_SYSDUMP_MAGIC      ((PHYS_OFFSET_ADDR & (~(SZ_512M - 1))) + SZ_512M - SZ_1M)


#define CALIBRATE_ENUM_MS 3000
#define CALIBRATE_IO_MS 2000

//#define LOW_BAT_ADC_LEVEL 782 /*phone battery adc value low than this value will not boot up*/
#define LOW_BAT_VOL            3500 /*phone battery voltage low than this value will not boot up*/
#define LOW_BAT_VOL_CHG        3300    //3.3V charger connect

#define PWR_KEY_DETECT_CNT 12 /*this should match the count of boot_pwr_check() function */
#define ALARM_LEAD_SET_MS 0 /* time set for alarm boot in advancd */

#define PHYS_OFFSET_ADDR			0x80000000
//#define TD_CP_OFFSET_ADDR			0x8000000	/*128*/
//#define TD_CP_SDRAM_SIZE			0x1200000	/*18M*/
//#define WCDMA_CP_OFFSET_ADDR		0x10000000	/*256M*/
//#define WCDMA_CP_SDRAM_SIZE		0x4000000	/*64M*/
#define GGE_CP_OFFSET_ADDR 		0x08000000       /*128M*/
#define GGE_CP_SDRAM_SIZE 		0x01600000 	/*22M*/
#define LTE_CP_OFFSET_ADDR              0x09600000       /*150M*/
#define LTE_CP_SDRAM_SIZE 		0x06A00000       /*106M*/

#define SIPC_APCP_RESET_ADDR_SIZE	0xC00	/*3K*/
#define SIPC_APCP_RESET_SIZE	0x1000	/*4K*/
//#define SIPC_TD_APCP_START_ADDR		(PHYS_OFFSET_ADDR + TD_CP_OFFSET_ADDR + TD_CP_SDRAM_SIZE - SIPC_APCP_RESET_SIZE)	/*0x897FF000*/
//#define SIPC_WCDMA_APCP_START_ADDR	(PHYS_OFFSET_ADDR + WCDMA_CP_OFFSET_ADDR + WCDMA_CP_SDRAM_SIZE - SIPC_APCP_RESET_SIZE) /*0x93FFF000*/
#define SIPC_GGE_APCP_START_ADDR 	(PHYS_OFFSET_ADDR + GGE_CP_OFFSET_ADDR + GGE_CP_SDRAM_SIZE - SIPC_APCP_RESET_ADDR_SIZE) 	/*0x895ff000*/
#define SIPC_LTE_APCP_START_ADDR        (PHYS_OFFSET_ADDR + LTE_CP_OFFSET_ADDR + LTE_CP_SDRAM_SIZE - SIPC_APCP_RESET_ADDR_SIZE)         /*0x8ffff000*/

#define CONFIG_RAM_CONSOLE

#ifdef CONFIG_RAM_CONSOLE
#define CONFIG_RAM_CONSOLE_SIZE        0x80000
#define CONFIG_RAM_CONSOLE_START    (CONFIG_SYS_NAND_U_BOOT_START + 0x600000)
#endif

//#define CALIBRATION_FLAG           0x89700000

#define CONFIG_CMD_SOUND 1
#define CONFIG_CMD_FOR_HTC 1
#define CONFIG_SOUND_CODEC_SPRD_V3 1
#define CONFIG_SOUND_DAI_VBC_R2P0 1
/* #define CONFIG_SPRD_AUDIO_DEBUG */

#define CONFIG_RAMDUMP_NO_SPLIT 1 /* Don't split sysdump file */

//add firewall args
#define CONFIG_FIREWALL 1

//#define CONFIG_DFS_TIMING	1
#endif /* __CONFIG_H */

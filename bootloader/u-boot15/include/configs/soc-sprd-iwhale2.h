/*for device tree*/
#define DT_PLATFROM_ID 9868
#define DT_HARDWARE_ID 1
#define DT_SOC_VER     0x20000

/*only used in fdl2 .in uart download, the debug infors  from  serial will break the download process.*/
#define CONFIG_SILENT_CONSOLE

/*
 * SPREADTRUM BIGPHONE board - SoC Configuration
 */
#define CONFIG_ADIE_SC2731
#define PHYS_SDRAM_1           0x80000000

#define CHIP_ENDIAN_LITTLE
#define _LITTLE_ENDIAN 1

/*eMMC config, note that even UFS boards need these macros to support SD card*/
#define CONFIG_MMC
#define CONFIG_MMC_SDMA
#define CONFIG_EMMC_VERSION_R8P0
#define CONFIG_EMMC_RST_N_FUNCTION

/*file system config*/
#define CONFIG_FAT_WRITE
#define CONFIG_FS_EXT4

/*partition type*/
#define CONFIG_DOS_PARTITION
#define CONFIG_EFI_PARTITION

#define CONFIG_SYS_HZ			1000
#define CONFIG_SPRD_TIMER_CLK		1000 /*32768*/

/*for spreadtrum secure boot*/
#define CONFIG_SPL_LOAD_LEN (0x6000)
#define PUBKEY_BSC_BLOCK_INDEX 0
#define PUBKEY_VLR_BLOCK_INDEX 0
#define PUBKEY_READ_BLOCK_NUMS (SEC_HEADER_MAX_SIZE / EMMC_SECTOR_SIZE)
#define CONFIG_SPL_HASH_LEN (0xC00) /* 3KB */


#define CONFIG_SYS_SDRAM_BASE 0x0
#define CONFIG_SYS_SDRAM_END (CONFIG_SYS_SDRAM_BASE + PHYS_SDRAM_1_SIZE)

/* U-Boot general configuration */
#define CONFIG_SYS_PROMPT	"=> "	/* Monitor Command Prompt */
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE
#define CONFIG_SYS_LONGHELP

#define CONFIG_LOADADDR		(CONFIG_SYS_TEXT_BASE - CONFIG_SYS_MALLOC_LEN - 4*1024*1024)	/* loadaddr env var */

/*for speadtrum usb driver*/
#define CONFIG_USB_DOWNLOAD
#define CONFIG_USB_DWC3
#ifdef CONFIG_USB_DWC3
#define CONFIG_USB_DWC3_GADGET
#define CONFIG_USB_DWC3_SPRD_INTEL
#endif
#define CONFIG_USB_GADGET_SC8800G
#define CONFIG_USB_DWC
#define CONFIG_USB_GADGET_DUALSPEED

/*for pctool_mode_detect_uart*/
#define CONFIG_MODEM_CALIBERATE


/*for sysdump*/
/*#define CONFIG_SPRD_SYSDUMP*/
#define CONFIG_RAMDUMP_NO_SPLIT 1	/* Don't split sysdump file */
#define REAL_SDRAM_SIZE 0x40000000	/*dump 1G */


#define CALIBRATE_ENUM_MS 3000
#define CALIBRATE_IO_MS 2000


#define LOW_BAT_VOL            3400 /*phone battery voltage low than this value will not boot up*/
#define LOW_BAT_VOL_CHG        3300

#define PWR_KEY_DETECT_CNT 2 /*this should match the count of boot_pwr_check() function */
#define ALARM_LEAD_SET_MS 0 /* time set for alarm boot in advancd */

#define PHYS_OFFSET_ADDR			0x80000000


/*7S reset config*/
#define CONFIG_7S_RST_MODULE_EN		1

#ifdef DEBUG
#define CONFIG_7S_RST_SW_MODE	1	//0:hw reset,1:arm reset,power keep on	//soft for debug version
#else
#define CONFIG_7S_RST_SW_MODE	0	//0:hw reset,1:arm reset,power keep on	//hard for user version
#endif
#define CONFIG_7S_RST_SHORT_MODE	1
#define CONFIG_7S_RST_2KEY_MODE		0
#define CONFIG_7S_RST_THRESHOLD		7
/*i2c driver*/
#define CONFIG_SYS_I2C
#define CONFIG_SPRD_I2C_V2
#define CONFIG_SPRD_EXT_IC_POWER
#define CONFIG_SPRD2701_CHARGE_IC
#define CONFIG_SPRDCHG_I2C_BUS 3

/* SPRD VP DEBUG ANDROID     */
#define CONFIG_VP_DEBUG

#define CONFIG_PREBOOT "role"
#define CONFIG_BOARD_LATE_INIT

/* Chip Driver Macro Definitions Start*/
/*sprd adc*/
#define CONFIG_SPRD_ADC

/*sprd ap iefuse*/
#define CONFIG_SPRD_AP_IEFUSE_R1P0

/*sprd adi*/
#define CONFIG_SPRD_ADI
#define ADI_R3P0_VER

/*sprd gpio*/
#define CONFIG_SPRD_GPIO
#define CONFIG_SPRD_EIC_EXT1
#define CONFIG_SPRD_EIC_EXT2

#define CONFIG_CONS_INDEX		1 /* use UART1 for console */

/*sprd rtc*/
#define CONFIG_RTC_SPRD

/*sprd watchdog*/
#define CONFIG_HW_WATCHDOG
#define CONFIG_SPRD_WATCHDOG

/* sprd modem&dsp boot related macro definitions */
#define CONFIG_KERNEL_BOOT_CP
#define CONFIG_MEM_LAYOUT_DECOUPLING

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
#define BASE_TO_APBASE(addr)	((addr) - 0x80000000)
#endif

#define CONFIG_SUPPORT_LTE
#define CONFIG_ADVANCED_LTE

#define LTE_AGDSP_LOADER_OFFSET	0x000a0000
#define LTE_AGDSP_SIZE			0x260000
#define LTE_AGDSP_ADDR			(0x40000000 + LTE_AGDSP_LOADER_OFFSET)

#define LTE_TGDSP_LOADER_OFFSET	0x00020000
#define LTE_TGDSP_SIZE			(0x00600000 - LTE_TGDSP_LOADER_OFFSET)
#define LTE_TGDSP_ADDR			(LTE_AGDSP_ADDR + LTE_AGDSP_SIZE + LTE_TGDSP_LOADER_OFFSET)

#define LTE_LDSP_SIZE			0xc00000
#define LTE_LDSP_ADDR			(LTE_TGDSP_ADDR + LTE_TGDSP_SIZE)

#define LTE_MODEM_SIZE			0x01000000
#define LTE_MODEM_ADDR			0x03000000

#define LTE_FIXNV_SIZE			0x80000 //512K
#define LTE_FIXNV_ADDR			0x04020000
#define LTE_RUNNV_SIZE			0xa0000 //640K
#define LTE_RUNNV_ADDR			0x040a0000
#define FIXNV_SIZE				LTE_FIXNV_SIZE

#define LTE_CP_CMDLINE_ADDR		0x04140000

/* sprd cm4 boot related macro definitions */
#define CONFIG_DFS_ENABLE
#define DFS_ADDR		0xe6040000
#define DFS_SIZE		(256*1024) //256K

#define CONFIG_ARM7_RAM_ACTIVE	//active the cm4 iram
/* This is the offset from SRAM base address to save the
   vid values in order to program the vid registers on the
   resume path
*/
#define CONFIG_VID_OFFSET	0x1F00
#define USB_FIX_VERSION 1


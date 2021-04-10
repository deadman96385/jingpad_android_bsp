
/*for device tree*/
#define DT_PLATFROM_ID 9868
#define DT_HARDWARE_ID 1
#define DT_SOC_VER     0x20000

#define CONFIG_IDENT_STRING            "isharkl2"

#define CONFIG_SILENT_CONSOLE

/*
 * SPREADTRUM BIGPHONE board - SoC Configuration
 */
#define CONFIG_ADIE_SC2731
#define PHYS_SDRAM_1		0x80000000


#define CHIP_ENDIAN_LITTLE
#define _LITTLE_ENDIAN 1


/*
 * MMC definition
 */
#define CONFIG_MMC			1
#define CONFIG_MMC_SDMA			1
#define CONFIG_EMMC_VERSION_R8P0
#define CONFIG_EMMC_RST_N_FUNCTION
/*#define CONFIG_MMC_TRACE*/
/*sprdimageversion Dynamic acquisition rpmb's size*/
#define CONFIG_SPRD_RPMB

/* file system config */
#define CONFIG_FAT_WRITE		1
#define CONFIG_FS_EXT4

#define CONFIG_DOS_PARTITION		1
#define CONFIG_EFI_PARTITION		1



#define CONFIG_SYS_HZ			1000
#define CONFIG_SPRD_TIMER_CLK		1000 /*32768*/

#define CP0_ZERO_MAP_ADR    0x50000000
#define CP0_ARM0_EXEC_ADR        0x88400000

#define CP1_ZERO_MAP_ADR    0x50001000
#define CP1_EXEC_ADR        LTE_MODEM_ADDR


#define MODEM_SIZE		(0x800000)
#define DSP_SIZE		(0x2E0000)
#define RUNTIMENV_SIZE		(3*128 * 1024)

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

#define CONFIG_USB_DOWNLOAD
#define CONFIG_DWC_OTG
#define CONFIG_USB_GADGET_SC8800G
#define CONFIG_USB_DWC
#define CONFIG_USB_GADGET_DUALSPEED

#define CONFIG_MODEM_CALIBERATE


#define CALIBRATE_ENUM_MS 3001
#define CALIBRATE_IO_MS 3000


#define LOW_BAT_VOL            3400 /*phone battery voltage low than this value will not boot up*/
#define LOW_BAT_VOL_CHG        3300

#define PWR_KEY_DETECT_CNT 2 /*this should match the count of boot_pwr_check() function */
#define ALARM_LEAD_SET_MS 0 /* time set for alarm boot in advancd */

#define PHYS_OFFSET_ADDR			0x80000000

/*7S reset config*/
#define CONFIG_7S_RST_MODULE_EN		1	/* 0:disable module; 1:enable module */

#ifdef DEBUG
#define CONFIG_7S_RST_SW_MODE	1	/* 0:hw reset,1:arm reset,power keep on, soft for debug version */
#else
#define CONFIG_7S_RST_SW_MODE	0	/* 0:hw reset,1:arm reset,power keep on, hard for user version */
#endif
#define CONFIG_7S_RST_SHORT_MODE	1	/* 0:long press then release key to trigger;1:press key some time to trigger */
#define CONFIG_7S_RST_2KEY_MODE		1	/* 0:1Key--Normal mode; 1:2KEY */
#define CONFIG_7S_RST_THRESHOLD		7	/* 7S, hold key down for this time to trigger */
/*i2c driver*/
#define CONFIG_SYS_I2C
#define CONFIG_SPRD_I2C_V2

/* SPRD VP DEBUG ANDROID     */
#define CONFIG_VP_DEBUG
#define CONFIG_PREBOOT "role"
#define CONFIG_BOARD_LATE_INIT

/*sprd ap iefuse*/
#define CONFIG_SPRD_AP_IEFUSE_R1P0

/* Chip Driver Macro Definitions Start*/
/*sprd adc*/
#define CONFIG_SPRD_ADC


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
/* #define CONFIG_KERNEL_BOOT_CP */
#define CONFIG_KERNEL_BOOT_CP
#define CONFIG_MEM_LAYOUT_DECOUPLING

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
#define BASE_TO_APBASE(addr)	((addr) - 0x80000000)
#endif

#define CONFIG_SUPPORT_LTE
#define CONFIG_ADVANCED_LTE

#define LTE_AGDSP_LOADER_OFFSET		0x000a0000
#define LTE_AGDSP_SIZE			0x260000
#define LTE_AGDSP_ADDR			(0x00800000 + LTE_AGDSP_LOADER_OFFSET)

#define LTE_TGDSP_LOADER_OFFSET		0x00020000
#define LTE_TGDSP_SIZE			(0x00600000 - LTE_TGDSP_LOADER_OFFSET)
#define LTE_TGDSP_ADDR			(LTE_AGDSP_ADDR + LTE_AGDSP_SIZE + LTE_TGDSP_LOADER_OFFSET)

#define LTE_LDSP_SIZE			0xc00000
#define LTE_LDSP_ADDR			(LTE_TGDSP_ADDR + LTE_TGDSP_SIZE)

#define LTE_MODEM_SIZE			0x01000000
#define LTE_MODEM_ADDR			0x03000000

#define LTE_FIXNV_SIZE			0xc8000 //800K
#define LTE_FIXNV_ADDR			0x04020000
#define LTE_RUNNV_SIZE			0xe8000 //928K
#define LTE_RUNNV_ADDR			0x040e8000
#define FIXNV_SIZE			LTE_FIXNV_SIZE

#define LTE_CP_CMDLINE_ADDR		0x041d0000
#define CALIBRATION_FLAG_CP1  LTE_CP_CMDLINE_ADDR

/* sprd cm4 boot related macro definitions */
#define CONFIG_DFS_ENABLE
#define DFS_ADDR			0xe6040000
#define DFS_SIZE			(256*1024) //256K

#define CONFIG_ARM7_RAM_ACTIVE	//active the cm4 iram
/* This is the offset from SRAM base address to save the
   vid values in order to program the vid registers on the
   resume path
*/
#define CONFIG_VID_OFFSET	0x1F00


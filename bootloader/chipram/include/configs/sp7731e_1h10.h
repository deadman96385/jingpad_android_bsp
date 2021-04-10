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

//only used in fdl2 .in uart download, the debug infors  from  serial will break the download process.
//#define NAND_DEBUG  
//#define DEBUG

/*#define SPRD_EVM_TAG_ON 1*/
#ifdef SPRD_EVM_TAG_ON
#define SPRD_EVM_ADDR_START 0x00026000
#define SPRD_EVM_TAG(_x) (*(((unsigned long *)SPRD_EVM_ADDR_START)+_x) = *(volatile unsigned long *)0x87003004)
#endif

//#define CONFIG_SECURE_BOOT
//#define CONFIG_ROM_VERIFY_SPL

/*sharkl2 rpll default 13M*/
//#define CONFIG_SCX35L2_MDAR

/*no sec bin;use sec_header*/
#define CONFIG_DUAL_SPL
#ifdef CONFIG_DUAL_SPL
#define HASH_TEMP_LEN 32
#define UBOOT_HASH_SIZE        0x200
#define UBOOT_HASH_SIZE_OFFSET 0x08
#endif
/*
 * SPREADTRUM BIGPHONE board - SoC Configuration
 */
#define CONFIG_SOC_PIKE2
#define CONFIG_SC9630
#define CONFIG_CHIP_ENV_SET
#define CHIPRAM_ENV_ADDR	0x82000000

//#define CONFIG_SUPPORT_WLTE




#define CHIP_ENDIAN_LITTLE
#define _LITTLE_ENDIAN 1


#define CONFIG_EMMC_BOOT
#define CONFIG_ADIE_SC2720

#ifdef  CONFIG_EMMC_BOOT
#define EMMC_SECTOR_SIZE 512
#define CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM ((CONFIG_SYS_NAND_U_BOOT_SIZE+EMMC_SECTOR_SIZE-1)/EMMC_SECTOR_SIZE)
#endif
//
#define CONFIG_LOAD_PARTITION
//
/*
 * MMC definition
 */
#define CONFIG_CMD_MMC
#ifdef  CONFIG_CMD_MMC
#define CONFIG_EFI_PARTITION		1
#endif

//add atf args
#define SML_LOAD_MAX_SIZE       (1024*1024)
//defined in AndroidChipram.mk
//#define CONFIG_SML_LDADDR_START (0x94000000)

//add tos args
#define TOS_LOAD_MAX_SIZE       (6*1024*1024)
//defined in AndroidChipram.mk
//#define CONFIG_TOS_LDADDR_START (0x94100000)
#define IMAGE_HEAD_SIZE		(512)

//#define CONFIG_SYS_HUSH_PARSER



#ifdef CONFIG_SECURE_BOOT
#define CONFIG_SPL_LOAD_LEN	(0x8000)
#else
#define CONFIG_SPL_LOAD_LEN	(0x6000)
#endif 



/*#define CMDLINE_NEED_CONV */

//#define CONFIG_SYS_TEXT_BASZE  0x80f00000

//#define	CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* 256 kB for U-Boot */

/* NAND BOOT is the only boot method */
#define BOOT_FLAG_ADDRESS 0x50002C04
#define CONFIG_NAND_U_BOOT
/* Start copying real U-boot from the second page */
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x40000
#define CONFIG_SYS_NAND_U_BOOT_SIZE	0x90000
//#define FPGA_TRACE_DOWNLOAD //for download image from trace

/* Load U-Boot to this address */
#define CONFIG_UBOOT_MAX_SIZE 0x100000
#define CONFIG_SYS_NAND_U_BOOT_DST	0x9f000000
#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_NAND_U_BOOT_DST
#define CONFIG_SYS_SDRAM_BASE 0x80000000


#define CONFIG_HW_WATCHDOG
//#define CONFIG_AUTOBOOT //used for FPGA test, auto boot other image
//#define CONFIG_DISPLAY_CPUINFO


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

/* 8MB DRAM test */

/*
 * Serial Info
 */
#define CONFIG_SYS_SC8800X_UART1	1
/*
 * Flash & Environment
 */
/* No NOR flash present */
#define CONFIG_SYS_MONITOR_LEN ((CONFIG_SYS_NAND_U_BOOT_OFFS)+(CONFIG_SYS_NAND_U_BOOT_SIZE))
#define CONFIG_SYS_NO_FLASH	1
#define CONFIG_ENV_SIZE		(128 * 1024)	
/*
#define	CONFIG_ENV_OFFSET	CONFIG_SYS_MONITOR_LEN
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)
*/

/* DDR */
#define CONFIG_CLK_PARA

#ifndef CONFIG_CLK_PARA
#define DDR_CLK 640
#else
#define MAGIC_HEADER	0x5555AAAA
#define MAGIC_END	0xAAAA5555
#define CONFIG_PARA_VERSION 2
#define CLK_CA7_CORE    CLK_1300M
#define CLK_CA7_AXI     CLK_650M
#define CLK_CA7_DGB     CLK_650M
#define CLK_CA7_AHB     AHB_CLK_192M
#define CLK_CA7_APB     APB_CLK_128M
#define CLK_PUB_AHB     PUB_AHB_CLK_128M
#define CLK_AON_APB     AON_APB_CLK_128M
#define CLK_AP_AXI      AP_AXI_CLK_256M

#ifdef CONFIG_NAND_SPL
#define CLK_DDR_FREQ        533000000
#else
#define CLK_DDR_FREQ        166000000
#endif

#endif

#define DCDC_CORE 1000
#define DCDC_GEN	1875

//clk_list
#define CLK_LEVEL_COUNT_MAX  6
#define CLK_AP_AXI_LEVEL 5
#define CLK_AP_AXI_LEVEL_ID 4
#define CLK_AP_AHB_LEVEL 5
#define CLK_AP_AHB_LEVEL_ID 4
#define CLK_AP_APB_LEVEL 5
#define CLK_AP_APB_LEVEL_ID 4
#define CLK_AON_APB_LEVEL 3
#define CLK_AON_APB_LEVEL_ID 2

// for avoid disturb solution
#ifdef CONFIG_AVOID_DISTURB_SOLUTION
#define DISTURB_INFO_IRAM_BASE		0x5000f800
#define MODULE_CLK_NUM_IRAM_OFFSET	0x10
#define CUR_CLK_INFO_IRAM_OFFSET	0x20
#define CUR_CLK_INFO_END_IRAM_OFFSET	0xa0
#define REQ_INFO_IRAM_OFFSET		0x220
#define REQ_INFO_END_IRAM_OFFSET	0x800
#define DISTURBING_ID_NUM		0x5
#define DISTURBED_ID_NUM		0x6
#define EMMC_CLK_SRC_NUM		0x1	/* 0x6 */
#define NAND_CLK_SRC_NUM		0x1	/* 0x8 */
#define SDIO_CLK_SRC_NUM		0x1	/* 0x6 */
#define DSI_CLK_SRC_NUM			0x1
#define DDR_CLK_SRC_NUM			0x3
#endif

//--- for DDR
#define CFG_DRAM_TYPE	DRAM_LPDDR3
//---these three macro below,only one can be open
//#define DDR_LPDDR1
//#define DDR_LPDDR2
//#define DDR_DDR3
#define DDR_LPDDR3
#define DDR_PINMAP_TYPE_3
#define DDR_AUTO_DETECT
#ifdef  DDR_AUTO_DETECT
#define DDR_MR8_READ
#endif

/*
#ifdef DDR_MR8_READ
#define DDR_FREQ_AUTO_SEL
#endif
*/
//#define DDR_TYPE DRAM_LPDDR2_2CS_8G_X32
//#define DDR_TYPE DRAM_LPDDR2_1CS_4G_X32
//#define DDR_TYPE DRAM_LPDDR2_1CS_8G_X32
//#define DDR_TYPE DRAM_LPDDR2_2CS_16G_X32
//#define DDR_TYPE DRAM_LPDDR3_1CS_4G_X32
//#define DDR_TYPE DRAM_LPDDR3_1CS_6G_X32
//#define DDR_TYPE DRAM_LPDDR3_2CS_8G_X32
//#define DDR_TYPE DRAM_DDR3_1CS_2G_X8_4P
//#define DDR_TYPE DRAM_DDR3_1CS_4G_X16_2P

#define DDR_CLK0 533
#define DDR_CLK1 384
#define DDR_CLK2 256
#define DDR_CLK3 166
#define DDR_DPLL_CFG1 REG_AON_APB_DPLL_CFG1
#define DDR_DPLL_CFG2 REG_AON_APB_DPLL_CFG2

#define DDR_CA_SWAP_MAP0 0x76543210
#define DDR_CA_SWAP_MAP1 0x98

#ifdef DDR_FREQ_AUTO_SEL
#define DDR_REG_VAL_MR5_INDEX0 0x01
#define DDR_REG_VAL_MR6_INDEX0 0x06
#define DDR_REG_VAL_MR7_INDEX0 0
#define DDR_REG_VAL_MR8_INDEX0 0x1F
#define DDR_CS_NUM_VAL_INDEX0 1
#define MR_DDR_CLK_SEL_INDEX0 533

#define DDR_REG_VAL_MR5_INDEX1 0x05
#define DDR_REG_VAL_MR6_INDEX1 0x01
#define DDR_REG_VAL_MR7_INDEX1 0
#define DDR_REG_VAL_MR8_INDEX1 0x1B
#define DDR_CS_NUM_VAL_INDEX1 2
#define MR_DDR_CLK_SEL_INDEX1 533

#define DDR_REG_VAL_MR5_INDEX2 0
#define DDR_REG_VAL_MR6_INDEX2 0
#define DDR_REG_VAL_MR7_INDEX2 0
#define DDR_REG_VAL_MR8_INDEX2 0
#define DDR_CS_NUM_VAL_INDEX2 1
#define MR_DDR_CLK_SEL_INDEX2 533

#define DDR_REG_VAL_MR5_INDEX3 0
#define DDR_REG_VAL_MR6_INDEX3 0
#define DDR_REG_VAL_MR7_INDEX3 0
#define DDR_REG_VAL_MR8_INDEX3 0
#define DDR_CS_NUM_VAL_INDEX3 1
#define MR_DDR_CLK_SEL_INDEX3 533

#define DDR_REG_VAL_MR5_INDEX4 0
#define DDR_REG_VAL_MR6_INDEX4 0
#define DDR_REG_VAL_MR7_INDEX4 0
#define DDR_REG_VAL_MR8_INDEX4 0
#define DDR_CS_NUM_VAL_INDEX4 1
#define MR_DDR_CLK_SEL_INDEX4 533

#define DDR_REG_VAL_MR5_INDEX5 0
#define DDR_REG_VAL_MR6_INDEX5 0
#define DDR_REG_VAL_MR7_INDEX5 0
#define DDR_REG_VAL_MR8_INDEX5 0
#define DDR_CS_NUM_VAL_INDEX5 1
#define MR_DDR_CLK_SEL_INDEX5 533

#define DDR_REG_VAL_MR5_INDEX6 0
#define DDR_REG_VAL_MR6_INDEX6 0
#define DDR_REG_VAL_MR7_INDEX6 0
#define DDR_REG_VAL_MR8_INDEX6 0
#define DDR_CS_NUM_VAL_INDEX6 1
#define MR_DDR_CLK_SEL_INDEX6 533

#define DDR_REG_VAL_MR5_INDEX7 0
#define DDR_REG_VAL_MR6_INDEX7 0
#define DDR_REG_VAL_MR7_INDEX7 0
#define DDR_REG_VAL_MR8_INDEX7 0
#define DDR_CS_NUM_VAL_INDEX7 1
#define MR_DDR_CLK_SEL_INDEX7 533
#endif

/*
[24:0] select DQ swap mapping;
[25:24] select which data slice used for MRR read
*/
#define DDR_DQ_SWAP_MAP_BYTE0 0xfac688

/*
BB DQ[15:14]<-----mem bit[15:14]
BB DQ[13]<-----mem bit[13]
BB DQ[12]<-----mem bit[12]
BB DQ[11]<-----mem bit[11]
BB DQ[10]<-----mem bit[10]
BB DQ[9]<-----mem bit[9]
BB DQ[8]<-----mem bit[8]
eg: (((val & 0x0100)>> 8)<<10)
mem bit[8],BB DQ[10]
*/
#define DDR_DQ_SWAP_MAP_BYTE(val) \
		((val & 0xC000) |     \
		(((val & 0x2000)>> 13)<<13)| \
		(((val & 0x1000)>> 12)<<12)| \
		(((val & 0x0800)>> 11)<<11)  | \
		(((val & 0x0400)>> 10)<<10)  | \
		(val & 0x0200) | \
		(((val & 0x0100)>> 8)<<8) | \
		(val & 0x0FF))

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

/* NAND */
//#define CONFIG_JFFS2_NAND
//#define CONFIG_SPRD_NAND_HWECC
//#define CONFIG_SYS_NAND_5_ADDR_CYCLE


#define CONFIG_MTD_PARTITIONS

/* U-Boot general configuration */
#define CONFIG_SYS_PROMPT	"=> "	/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size  */
/* Print buffer sz */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + \
		sizeof(CONFIG_SYS_PROMPT) + 16)
/* Boot Argument Buffer Size */

/* support OS choose */
#undef CONFIG_BOOTM_NETBSD 
#undef CONFIG_BOOTM_RTEMS

/* U-Boot commands */
#include <config_cmd_default.h>
#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_NET
#undef CONFIG_CMD_SETGETDCR




#define xstr(s)	str(s)
#define str(s)	#s





//#define CONFIG_USB_ETHER


#include <asm/sizes.h>



//#define LOW_BAT_ADC_LEVEL 782 /*phone battery adc value low than this value will not boot up*/


//#define TD_CP_OFFSET_ADDR			0x8000000	/*128*/
//#define TD_CP_SDRAM_SIZE			0x1200000	/*18M*/
//#define WCDMA_CP_OFFSET_ADDR		0x10000000	/*256M*/
//#define WCDMA_CP_SDRAM_SIZE		0x4000000	/*64M*/





/* #define CONFIG_SPRD_AUDIO_DEBUG */


#endif /* __CONFIG_H */

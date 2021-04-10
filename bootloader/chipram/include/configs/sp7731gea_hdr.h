

#ifndef __CONFIG_BOARD_H
#define __CONFIG_BOARD_H

#include "./sp7731g_chip.h"

//#define DEBUG

/*#define SPRD_EVM_TAG_ON 1*/
#ifdef SPRD_EVM_TAG_ON
#define SPRD_EVM_ADDR_START 0x00026000
#define SPRD_EVM_TAG(_x) (*(((unsigned long *)SPRD_EVM_ADDR_START)+_x) = *(volatile unsigned long *)0x87003004)
#endif

/*
 * SPREADTRUM BIGPHONE board - SoC Configuration
 */
#define CONFIG_SP8830
#define CONFIG_SC8830
#define CONFIG_SPX30G
#define CONFIG_CHIP_ENV_SET
#define CHIPRAM_ENV_ADDR	0x5000b000
#define CONFIG_ADIE_SC2713S


#define CONFIG_CPLL_1024M
#define CONFIG_EMMC_BOOT

#ifdef  CONFIG_EMMC_BOOT
#define EMMC_SECTOR_SIZE 512


#define CONFIG_EFI_PARTITION
#define CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM ((CONFIG_SYS_NAND_U_BOOT_SIZE+EMMC_SECTOR_SIZE-1)/EMMC_SECTOR_SIZE)

#endif



//#define	CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* 256 kB for U-Boot */

/* NAND BOOT is the only boot method */
#define CONFIG_NAND_U_BOOT

/* Start copying real U-boot from the second page */
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x40000
#define CONFIG_SYS_NAND_U_BOOT_SIZE	0xa0000

//#define FPGA_TRACE_DOWNLOAD //for download image from trace

/* Load U-Boot to this address */
#define CONFIG_SYS_NAND_U_BOOT_DST	0x9f000000
#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_NAND_U_BOOT_DST
#define CONFIG_SYS_SDRAM_BASE 0x80000000




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
#define DDR_CLK 464
#else
#define MAGIC_HEADER	0x5555AAAA
#define MAGIC_END	0xAAAA5555
#define CONFIG_PARA_VERSION 1
#define CLK_CA7_CORE    CLK_1200M
#define CLK_CA7_AXI     CLK_400M
#define CLK_CA7_DGB     CLK_200M
#define CLK_CA7_AHB     AHB_CLK_192M
#define CLK_CA7_APB     APB_CLK_64M
#define CLK_PUB_AHB     PUB_AHB_CLK_153_6M
#define CLK_AON_APB     AON_APB_CLK_128M
#ifdef CONFIG_CPLL_1024M
#define DDR_FREQ        533000000
#else
#define DDR_FREQ        466000000
#endif
#define DCDC_ARM	1030
#ifdef CONFIG_CPLL_1024M
#define DCDC_CORE       930
#else
#define DCDC_CORE	900
#endif
#define DCDC_GEN       2400
#define CONFIG_VOL_PARA
#endif
#define TDPLL_SELECT_SWITCH
#define WPLL_SELECT_SWITCH

#define DDR_AUTO_DETECT

//---these three macro below,only one can be open
//#define DDR_LPDDR1
#define DDR_LPDDR2
//#define DDR_DDR3
#define DDR_PINMAP_TYPE_1
//#define DDR_AUTO_DETECT
//#define DDR_TYPE DRAM_LPDDR2_1CS_4G_X32
//#define DDR_TYPE DRAM_LPDDR2_1CS_8G_X32
//#define DDR_TYPE DRAM_LPDDR2_2CS_8G_X32
//#define DDR_TYPE DRAM_LPDDR2_2CS_16G_X32
//#define DDR_TYPE DRAM_DDR3_1CS_2G_X8_4P
//#define DDR_TYPE DRAM_DDR3_1CS_4G_X16_2P

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

//#define CONFIG_SYS_NAND_5_ADDR_CYCLE


#define CONFIG_MTD_PARTITIONS

#endif /* __CONFIG_BOARD_H */

/******************************************************************************
 ** File Name:    sprd_chipram_env.h                                          *
 ** Author:       spreadtrum                                                *
 ** DATE:         6/15/2014                                                    *
 ** Copyright:    2014 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
#ifndef _SPRD_CHIPRAM_ENV_H_
#define _SPRD_CHIPRAM_ENV_H_
typedef enum bootloader_mode {
	BOOTLOADER_MODE_UNKNOW = 0x100,
	BOOTLOADER_MODE_DOWNLOAD = 0x102,
	BOOTLOADER_MODE_LOAD =0x104
}boot_mode_t;
#define CHIPRAM_ENV_MAGIC	0x43454e56
typedef struct chipram_env {
	u32 magic; //0x43454e56
	boot_mode_t mode;
	u32 dram_size; //MB
	u64 vol_para_addr;
	u32 keep_charge;
	u32 reserved;
}chipram_env_t;
void chipram_env_set(u32 mode);
#endif

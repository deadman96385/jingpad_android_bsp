#ifndef _CHIPRAM_ENV_H_
#define _CHIPRAM_ENV_H_
#include <asm/arch/chip_releted_def.h>

typedef enum bootloader_mode {
	BOOTLOADER_MODE_UNKNOW = 0x100,
	BOOTLOADER_MODE_DOWNLOAD = 0x102,
	BOOTLOADER_MODE_LOAD =0x104
}boot_mode_t;

typedef enum boot_device {
	BOOT_DEVICE_EMMC = 0x205,
	BOOT_DEVICE_UFS =0x206
}boot_device_t;

#define CHIPRAM_ENV_MAGIC	0x43454e56
typedef struct chipram_env {
	u32 magic; //0x43454e56
	boot_mode_t mode;
	u32 dram_size; //MB
	u64 vol_para_addr;
	u32 keep_charge;
	u32 channel_sel;//usb,uart0,uart1
	u32 cs_number;
	u32 cs0_size;
	u32 cs1_size;
	u32 reserved;
}chipram_env_t;

typedef struct section_info{
	u32 type;
	u32 start_address_high;
	u32 start_address_low;
	u32 end_address_high;
	u32 end_address_low;
}section_info_t;

#define max_sec_number 8
typedef struct ddr_info {
	u32 section_number;
	struct section_info sec_info[max_sec_number];
}ddr_info_t;
chipram_env_t* get_chipram_env(void);
boot_mode_t get_boot_role(void);

#endif


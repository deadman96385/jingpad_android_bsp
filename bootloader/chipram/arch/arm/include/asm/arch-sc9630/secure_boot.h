#ifndef _SECURE_BOOT_H_
#define _SECURE_BOOT_H_

#define KEY_INFO_SIZ    (512)
#define CUSTOM_DATA_SIZ (1024)
#define VLR_INFO_SIZ    (512)
#define VLR_INFO_OFF    (512)

#define INTER_RAM_BEGIN                 0x50003000
#define CONFIG_SEC_LOAD_LEN             0xC00
#define CONFIG_SYS_NAND_U_BOOT_LOAD_LEN 0x80000

#define KEY_INFO_OFF (INTER_RAM_BEGIN + CONFIG_SPL_LOAD_LEN - KEY_INFO_SIZ - VLR_INFO_SIZ)
#define VLR_INFO_OFF (CONFIG_SYS_NAND_U_BOOT_START + CONFIG_SYS_NAND_U_BOOT_SIZE - VLR_INFO_SIZ)

#ifdef CONFIG_ROM_VERIFY_SPL
#define FDL2_CODE_OFF  (512 * 3)
#endif
#ifdef CONFIG_NAND_SPL
#define panic(x...)  do{}while(0)
#define printf(x...) do{}while(0)
#endif

//#define SECURE_BOOT_ENABLE

typedef struct{
	struct{
		uint32_t e;
		uint8_t  m[128];
		uint8_t  r2[128];
	}key;
	uint8_t reserved[4];
}bsc_info_t;

#define VLR_MAGIC (0x524C56FF)
typedef struct {
	uint32_t magic;
	uint8_t  hash[128];
	uint32_t setting;
	uint32_t length;
	uint8_t  reserved[20];
}vlr_info_t;

typedef struct
{
	uint32_t intermediate_hash[5];
	uint32_t length_low;
	uint32_t length_high;
	uint32_t msg_block_idx;
	uint32_t W[80];
}sha1context_32;

typedef struct {
	uint32_t ver;
	uint8_t  cap;
	void (*efuse_init)(void);
	void (*efuse_close)(void);
	uint32_t (*efuse_read)(uint32_t block_id, uint32_t *data);
	uint32_t (*sha1reset_32)(sha1context_32*);
	uint32_t (*sha1input_32)(sha1context_32*, const uint32_t*, uint32_t);
	uint32_t (*sha1result_32)(sha1context_32*, uint8_t*);
	void (*rsa_modpower)(uint32_t *p, uint32_t *m, uint32_t *r2, uint32_t e);
}rom_callback_func_t;

typedef struct {
	rom_callback_func_t *rom_callback;
	void (*secure_check)(uint8_t *data, uint32_t data_len, uint8_t *data_hash, uint8_t *data_key);
}sec_callback_func_t;

void secure_check(uint8_t *data, uint32_t data_len, uint8_t *data_hash, uint8_t *data_key);
int cal_md5(void *data, uint32_t len, void *harsh_data);
int secureboot_enabled(void);

#endif

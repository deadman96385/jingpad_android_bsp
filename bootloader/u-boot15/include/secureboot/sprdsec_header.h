
#ifndef __SPRDSEC_HEADER_H
#define __SPRDSEC_HEADER_H

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#define MAGIC_SIZE 8
#define VERSION_EBL 0
#define VERSION_NBL 1
#define CERTTYPE_CONTENT 0
#define CERTTYPE_KEY 1
#define CERTTYPE_PRIMDBG 2
#define CERTTYPE_DEVELOPDBG 3

//#define IRAM_BEGIN                 0x00009E00    // 0xa000 - 0x200
//#define UBOOT_START                0x9f6ffe00

//#define KEY_INFO_OFF (INTER_RAM_BEGIN + CONFIG_SPL_LOAD_LEN - KEY_INFO_SIZ - VLR_INFO_SIZ)
//#define VLR_INFO_OFF (CONFIG_SYS_NAND_U_BOOT_START + CONFIG_SYS_NAND_U_BOOT_SIZE - VLR_INFO_SIZ)

#if 0
typedef struct {

	uint32_t mMagicNum;	//0x42544844
	uint32_t mVersion;	//1//
	uint8_t mPayloadHash[32];	// sha256 hash val
	uint64_t mImgAddr;	// image loaded address
	uint32_t mImgSize;	// image size
	uint8_t reserved[460];	//460 + 13*4 = 512
} sys_img_header;
#endif
#define RSA_KEY_BITS_LEN_MAX 2048
#define RSA_KEY_BYTE_LEN_MAX (RSA_KEY_BITS_LEN_MAX>>3)
#define HASH_BYTE_LEN	 32
#define KEYCERT_HASH_LEN 72
#define CNTCERT_HASH_LEN 40
#define PRIMDBG_HASH_LEN 40
#define DEVEDBG_HASH_LEN 12

typedef struct sprdsignedimageheader {

	/* Magic number */
	uint8_t magic[MAGIC_SIZE];
	/* Version of this header format */
	uint32_t header_version_major;
	/* Version of this header format */
	uint32_t header_version_minor;

	/*image body, plain or cipher text */
	uint64_t payload_size;
	uint64_t payload_offset;

	/*offset from itself start */
	/*content certification size,if 0,ignore */
	uint64_t cert_size;
	uint64_t cert_offset;

	/*(opt)private content size,if 0,ignore */
	uint64_t priv_size;
	uint64_t priv_offset;

	/*(opt)debug/rma certification primary size,if 0,ignore */
	uint64_t cert_dbg_prim_size;
	uint64_t cert_dbg_prim_offset;

	/*(opt)debug/rma certification second size,if 0,ignore */
	uint64_t cert_dbg_developer_size;
	uint64_t cert_dbg_developer_offset;

} sprdsignedimageheader;

typedef struct sprd_rsapubkey {
	uint32_t keybit_len;	//1024/2048,max 2048
	uint32_t e;
	uint8_t mod[RSA_KEY_BYTE_LEN_MAX];
} sprd_rsapubkey;

#define  SPRD_RSAPUBKLEN  sizeof(sprd_rsapubkey)

typedef struct sprd_keycert {
	uint32_t certtype;	//1:key cert
	sprd_rsapubkey pubkey;	//pubkey for this cert, to verify signature in this cert
	uint8_t hash_data[HASH_BYTE_LEN];	//hash of current image data
	uint8_t hash_key[HASH_BYTE_LEN];	// hash of pubkey in next cert
	uint32_t type;
	uint32_t version;
	uint8_t signature[RSA_KEY_BYTE_LEN_MAX];	//signature of hash_data+hash_key
} sprd_keycert;

typedef struct sprd_contentcert {
	uint32_t certtype;	//0:content cert
	sprd_rsapubkey pubkey;	//pubkey for this cert, to verify signature in this cert
	uint8_t hash_data[HASH_BYTE_LEN];	//hash of image component
	uint32_t type;
	uint32_t version;
	uint8_t signature[RSA_KEY_BYTE_LEN_MAX];	//signature of hash_data
} sprd_contentcert;

typedef struct primary_debugcert {
	uint32_t cert_type;	//debug cert
	sprd_rsapubkey pubkey;	//pubkey for verify this signature

	uint8_t devkey_debug_hash_data[HASH_BYTE_LEN];	//hash of dev_pubkey
	uint32_t debug_mask;
	uint32_t reserved;

	uint8_t devkey_debug_signature[RSA_KEY_BYTE_LEN_MAX];	//signature of  debug_mask & reserved + hash of dev_pubkey

} primary_debugcert;

typedef struct developer_debugcert {
	uint32_t cert_type;	//debug cert

	sprd_rsapubkey dev_pubkey;	//developer pubkey

	uint32_t debug_mask;
	uint32_t uid0;
	uint32_t uid1;

	uint8_t dev_signature[RSA_KEY_BYTE_LEN_MAX];	//signature hash of uid0~uid1+debug_mask
} developer_debugcert;

#endif

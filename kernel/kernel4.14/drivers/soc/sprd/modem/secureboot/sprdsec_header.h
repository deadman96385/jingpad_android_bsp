#ifndef __SPRDSEC_HEADER_H
#define __SPRDSEC_HEADER_H

#include <asm-generic/int-ll64.h>

#define MAGIC_SIZE 8
#define CERTTYPE_CONTENT 0
#define CERTTYPE_KEY 1
#define RSA_KEY_BITS_LEN_MAX 2048
#define RSA_KEY_BYTE_LEN_MAX (RSA_KEY_BITS_LEN_MAX >> 3)
#define HASH_BYTE_LEN	 32
#define CRC_16 2
#define KEYCERT_HASH_LEN 72
#define CNTCERT_HASH_LEN 40

struct signed_img_header {
	u8 magic[MAGIC_SIZE];
	u32 header_version_major;
	u32 header_version_minor;
	u64 payload_size;
	u64 payload_offset;
	u64 cert_size;
	u64 cert_offset;
	u64 priv_size;
	u64 priv_offset;
	u64 cert_dbg_prim_size;
	u64 cert_dbg_prim_offset;
	u64 cert_dbg_developer_size;
	u64 cert_dbg_developer_offset;
};

struct sprd_rsapubkey {
	u32 keybit_len;
	u32 e;
	u8 mod[RSA_KEY_BYTE_LEN_MAX];
};

#define  SPRD_RSAPUBKLEN  sizeof(struct sprd_rsapubkey)

struct sprd_keycert {
	u32 certtype;
	struct sprd_rsapubkey pubkey;
	u8 hash_data[HASH_BYTE_LEN];
	u8 hash_key[HASH_BYTE_LEN];
	u32 type;
	u32 version;
	u8 signature[RSA_KEY_BYTE_LEN_MAX];
};

struct sprd_contentcert {
	u32 certtype;
	struct sprd_rsapubkey pubkey;
	u8 hash_data[HASH_BYTE_LEN];
	u32 type;
	u32 version;
	u8 signature[RSA_KEY_BYTE_LEN_MAX];
};

#endif

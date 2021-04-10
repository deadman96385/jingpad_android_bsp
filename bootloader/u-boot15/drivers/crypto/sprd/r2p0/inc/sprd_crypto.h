/*
 * sprd_crypt.h
 *
 *  Created on: 2015.12.21
 *      Author: feng.wang
 */
#ifndef _SPRD_CRYPTO_H_
#define _SPRD_CRYPTO_H_
#include <stdbool.h>

#define SPRD_DEFAULT_SRC_ADDR         0x98000000
#define SPRD_DEFAULT_DST_ADDR         0x99000000
#define SPRD_DEFAULT_KEY_ADDR         0x9A000000
//#define SPRD_DEFAULT_IV_ADDR          0x9A100000
#define SPRD_DEFAULT_SRC_LEN          524288 //1024 //64//65536 //1024 should be at the least because RSA need a 512*2 buffer to store N&D key.
#define SPRD_DEFAULT_DST_LEN          524288 //1024 //64//65536 //1024 should be at the least because RSA need a 512*2 buffer to store N&D key.
#define SPRD_DEFAULT_KEY_LEN          524288 //1024 //128//4096 it should be larger than or equal to 1024

#define SPRD_KEY_BUFFER_LEN           SPRD_DEFAULT_KEY_LEN
#define SPRD_RSA_BUFFER_LEN           SPRD_DEFAULT_SRC_LEN

enum sprd_crypt_status {
    SPRD_CRYPT_OK          = 0x00,
    SPRD_CRYPT_FAILED,
    SPRD_CRYPT_START,
    SPRD_CRYPT_DONE,
    SPRD_CRYPT_END,
    SPRD_CRYPT_ERR_LEN,
    SPRD_CRYPT_ERR_KEY,
    SPRD_CRYPT_ERR_CONT,
    SPRD_CRYPT_ERR_MODE,
    SPRD_CRYPT_ERR_ADDR,
    SPRD_CRYPT_ERR_ARG,
};

enum sprd_crypt_mode {
    SPRD_CRYPT_AES_ECB = 0,
    SPRD_CRYPT_AES_CBC,
    SPRD_CRYPT_AES_CTR,
    SPRD_CRYPT_AES_XTS,

    SPRD_CRYPT_TDES_ECB,
    SPRD_CRYPT_TDES_CBC,

    SPRD_CRYPT_HASH_MD5 ,
    SPRD_CRYPT_HASH_SHA1,
    SPRD_CRYPT_HASH_SHA224,
    SPRD_CRYPT_HASH_SHA256,
    SPRD_CRYPT_HASH_SHA384,
    SPRD_CRYPT_HASH_SHA512,
    SPRD_CRYPT_HASH_SHA512_224,
    SPRD_CRYPT_HASH_SHA512_256,

    SPRD_CRYPT_HMAC_MD5,
    SPRD_CRYPT_HMAC_SHA1,
    SPRD_CRYPT_HMAC_SHA224,
    SPRD_CRYPT_HMAC_SHA256,
    SPRD_CRYPT_HMAC_SHA384,
    SPRD_CRYPT_HMAC_SHA512,
    SPRD_CRYPT_HMAC_SHA512_224,
    SPRD_CRYPT_HMAC_SHA512_256,

    SPRD_CRYPT_RSA_ENC_1024,
    SPRD_CRYPT_RSA_ENC_2048,
    SPRD_CRYPT_RSA_ENC_3072,
    SPRD_CRYPT_RSA_ENC_4096,
    SPRD_CRYPT_RSA_DEC_1024,
    SPRD_CRYPT_RSA_DEC_2048,
    SPRD_CRYPT_RSA_DEC_3072,
    SPRD_CRYPT_RSA_DEC_4096,
    SPRD_CRYPT_RSA_KEY_GEN_PRIME_512,
    SPRD_CRYPT_RSA_KEY_GEN_PRIME_1024,
    SPRD_CRYPT_RSA_KEY_GEN_PRIME_1536,
    SPRD_CRYPT_RSA_KEY_GEN_PRIME_2048,

    SPRD_CRYPT_RNG_MIX,
    SPRD_CRYPT_RNG_TRUE,
    SPRD_CRYPT_RNG_PSEUDO,

    SPRD_CRYPT_NONE,
};

enum sprd_crypt {
    SPRD_CRYPT_ENC = 0,
    SPRD_CRYPT_DEC,
};

int sprd_crypt_init(void);
int sprd_crypt_set_mode(unsigned int mode);
int sprd_crypt_set_key(unsigned int mode, const unsigned char *key1, unsigned int key1_len, const unsigned char *key2, unsigned int key2_len);
int sprd_crypt_set_iv(unsigned int mode, const unsigned char *iv, unsigned char iv_len,  bool iv_rotate);
int sprd_crypt_set_crypt(unsigned int mode, bool encrypt);
int sprd_crypt_process(const const unsigned char *in, unsigned int in_len, unsigned char *out, unsigned int out_len, bool end);
int sprd_crypt_done(void);

int sprd_crypt_rng_read(unsigned char *out, unsigned int *out_len);

/* special for spl only
 * in, out, key1, key2 should be uncacheable memory.
 * only support SHA256, RSA public decrypt and AES CBC decrypt*/
int sprd_crypt_do(
        unsigned int mode,
        const unsigned char *in,
        unsigned int in_len,
        unsigned char *out,
        unsigned int *out_len,
        const unsigned char *key,
        unsigned int key_len,
        const unsigned char *iv,
        unsigned int iv_len);


int sprd_crypt_test(void);

#endif /* _SPRD_CRYPT_H_ */

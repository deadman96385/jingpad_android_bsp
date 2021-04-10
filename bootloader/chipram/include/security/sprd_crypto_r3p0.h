/*
* Copyright (c) 2016, Spreadtrum Communications.
*
* The above copyright notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef SPRD_CRYPTO_H
#define SPRD_CRYPTO_H

#include <linux/types.h>

#define SPRD_CRYPTO_LOG_TRACE(...)
#define SPRD_CRYPTO_LOG_DEBUG(...)
#define SPRD_CRYPTO_LOG_ERR(...)

#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif
#ifndef NULL
#define NULL ((void *)0)
#endif

#define SPRD_CRYPTO_MIN_DATA_LEN	0x8
#define SPRD_CRYPTO_MAX_DATA_LEN	0xFFFFF8

#define SPRD_CRYPTO_HASH_BUF_LEN	128
#define SPRD_CRYPTO_PKA_CMD_LEN		32//should be multiple of cache line, the size of item is 4 bytes.
#define SPRD_CRYPTO_MAX_AES_KEY_LEN	32
#define SPRD_CRYPTO_MAX_AES_IV_LEN	16
#define SPRD_CRYPTO_AES_BLOCK_SIZE	16
#define SPRD_CRYPTO_MAX_RNG_SIZE	512
#define SPRD_CRYPTO_MAX_RSA_SIZE	256
#define SPRD_CRYPTO_MAX_MAC_KEY_LEN	128
#define SPRD_CRYPTO_DUMP_SIZE		128

typedef int32_t		sprd_crypto_err_t;

enum sprd_crypto_status {
	SPRD_CRYPTO_SUCCESS = 0,		/* Success */
	SPRD_CRYPTO_ERROR   = 0xffff0000,	/* Generic Error */
	SPRD_CRYPTO_NOSUPPORT,			/* Scheme not support */
	SPRD_CRYPTO_INVALID_KEY,		/* Invalid Key in asymmetric scheme: RSA/DSA/ECCP/DH etc */
	SPRD_CRYPTO_INVALID_TYPE,		/* Invalid aes_type/des_type/authenc_type/hash_type/cbcmac_type/cmac_type */
	SPRD_CRYPTO_INVALID_CONTEXT,		/* Invalid context in multi-thread cipher/authenc/mac/hash etc */
	SPRD_CRYPTO_INVALID_PADDING,		/* Invalid sym_padding/rsassa_padding/rsaes_padding */
	SPRD_CRYPTO_INVALID_AUTHENTICATION,	/* Invalid authentication in AuthEnc(AES-CCM/AES-GCM)/asymmetric verify(RSA/DSA/ECCP DSA) */
	SPRD_CRYPTO_INVALID_ARG,		/* Invalid arguments */
	SPRD_CRYPTO_INVALID_PACKET,		/* Invalid packet in asymmetric enc/dec(RSA) */
	SPRD_CRYPTO_LENGTH_ERR,			/* Invalid Length in arguments */
	SPRD_CRYPTO_OUTOFMEM,			/* Memory alloc NULL */
	SPRD_CRYPTO_SHORT_BUFFER,		/* Output buffer is too short to store result */
	SPRD_CRYPTO_NULL,			/* NULL pointer in arguments */
	SPRD_CRYPTO_ERR_STATE,			/* Bad state in mulit-thread cipher/authenc/mac/hash etc */
	SPRD_CRYPTO_ERR_RESULT,			/* Bad result of test crypto */
};

typedef uint32_t			sprd_crypto_algo_t;
#define SPRD_CRYPTO_AES			0x00000000
#define SPRD_CRYPTO_AES_ECB		(SPRD_CRYPTO_AES + 0x0000)
#define SPRD_CRYPTO_AES_CBC		(SPRD_CRYPTO_AES + 0x0001)
#define SPRD_CRYPTO_AES_CTR		(SPRD_CRYPTO_AES + 0x0002)
#define SPRD_CRYPTO_AES_XTS		(SPRD_CRYPTO_AES + 0x0003)
#define SPRD_CRYPTO_AES_CMAC		(SPRD_CRYPTO_AES + 0x0004)
#define SPRD_CRYPTO_AES_GCM		(SPRD_CRYPTO_AES + 0x0005)
#define SPRD_CRYPTO_AES_GMAC		(SPRD_CRYPTO_AES + 0x0006)

#define SPRD_CRYPTO_TDES		0x01000000
#define SPRD_CRYPTO_TDES_ECB		(SPRD_CRYPTO_TDES + 0x0000)
#define SPRD_CRYPTO_TDES_CBC		(SPRD_CRYPTO_TDES + 0x0001)

#define SPRD_CRYPTO_HASH		0x02000000
#define SPRD_CRYPTO_HASH_MD5		(SPRD_CRYPTO_HASH + 0x0001)
#define SPRD_CRYPTO_HASH_SHA1		(SPRD_CRYPTO_HASH + 0x0002)
#define SPRD_CRYPTO_HASH_SHA224		(SPRD_CRYPTO_HASH + 0x0003)
#define SPRD_CRYPTO_HASH_SHA256		(SPRD_CRYPTO_HASH + 0x0004)
#define SPRD_CRYPTO_HASH_SHA384		(SPRD_CRYPTO_HASH + 0x0005)
#define SPRD_CRYPTO_HASH_SHA512		(SPRD_CRYPTO_HASH + 0x0006)
#define SPRD_CRYPTO_HASH_SHA512_224	(SPRD_CRYPTO_HASH + 0x0007)
#define SPRD_CRYPTO_HASH_SHA512_256	(SPRD_CRYPTO_HASH + 0x0008)
#define SPRD_CRYPTO_HASH_SM3		(SPRD_CRYPTO_HASH + 0x0009)

#define SPRD_CRYPTO_SM4			0x03000000
#define SPRD_CRYPTO_SM4_ECB		(SPRD_CRYPTO_SM4 + 0x0000)
#define SPRD_CRYPTO_SM4_CBC		(SPRD_CRYPTO_SM4 + 0x0001)
#define SPRD_CRYPTO_SM4_CTR		(SPRD_CRYPTO_SM4 + 0x0002)
#define SPRD_CRYPTO_SM4_XTS		(SPRD_CRYPTO_SM4 + 0x0003)
#define SPRD_CRYPTO_SM4_CFB		(SPRD_CRYPTO_SM4 + 0x0004)
#define SPRD_CRYPTO_SM4_OFB		(SPRD_CRYPTO_SM4 + 0x0005)

#define SPRD_CRYPTO_RC4			0x04000000

#define SPRD_CRYPTO_PKA			0x05000000
#define SPRD_CRYPTO_RSA			(SPRD_CRYPTO_PKA + 0x10000)
#define SPRD_CRYPTO_RSA_ENC_256		(SPRD_CRYPTO_RSA + 0x0000)
#define SPRD_CRYPTO_RSA_ENC_1024	(SPRD_CRYPTO_RSA + 0x0001)
#define SPRD_CRYPTO_RSA_ENC_2048	(SPRD_CRYPTO_RSA + 0x0002)
#define SPRD_CRYPTO_RSA_ENC_3072	(SPRD_CRYPTO_RSA + 0x0003)
#define SPRD_CRYPTO_RSA_ENC_4096	(SPRD_CRYPTO_RSA + 0x0004)
#define SPRD_CRYPTO_RSA_DEC_256		(SPRD_CRYPTO_RSA + 0x0005)
#define SPRD_CRYPTO_RSA_DEC_1024	(SPRD_CRYPTO_RSA + 0x0006)
#define SPRD_CRYPTO_RSA_DEC_2048	(SPRD_CRYPTO_RSA + 0x0007)
#define SPRD_CRYPTO_RSA_DEC_3072	(SPRD_CRYPTO_RSA + 0x0008)
#define SPRD_CRYPTO_RSA_DEC_4096	(SPRD_CRYPTO_RSA + 0x0009)

#define SPRD_CRYPTO_RSA_KEY_GEN		(SPRD_CRYPTO_PKA + 0x20000)
#define SPRD_CRYPTO_RSA_KEY_GEN_256	(SPRD_CRYPTO_RSA_KEY_GEN + 0x0000)
#define SPRD_CRYPTO_RSA_KEY_GEN_1024	(SPRD_CRYPTO_RSA_KEY_GEN + 0x0001)
#define SPRD_CRYPTO_RSA_KEY_GEN_2048	(SPRD_CRYPTO_RSA_KEY_GEN + 0x0002)
#define SPRD_CRYPTO_RSA_KEY_GEN_3072	(SPRD_CRYPTO_RSA_KEY_GEN + 0x0003)
#define SPRD_CRYPTO_RSA_KEY_GEN_4096	(SPRD_CRYPTO_RSA_KEY_GEN + 0x0004)

#define SPRD_CRYPTO_ECC             	(SPRD_CRYPTO_PKA + 0x30000)

#define SPRD_CRYPTO_RNG			(SPRD_CRYPTO_PKA + 0x40000)

#define SPRD_CRYPTO_MAC			0x06000000
#define SPRD_CRYPTO_HMAC		(SPRD_CRYPTO_MAC + 0x10000)
#define SPRD_CRYPTO_HMAC_MD5		(SPRD_CRYPTO_HMAC + 0x0001)
#define SPRD_CRYPTO_HMAC_SHA1		(SPRD_CRYPTO_HMAC + 0x0002)
#define SPRD_CRYPTO_HMAC_SHA224		(SPRD_CRYPTO_HMAC + 0x0003)
#define SPRD_CRYPTO_HMAC_SHA256		(SPRD_CRYPTO_HMAC + 0x0004)
#define SPRD_CRYPTO_HMAC_SHA384		(SPRD_CRYPTO_HMAC + 0x0005)
#define SPRD_CRYPTO_HMAC_SHA512		(SPRD_CRYPTO_HMAC + 0x0006)
#define SPRD_CRYPTO_HMAC_SHA512_224	(SPRD_CRYPTO_HMAC + 0x0007)
#define SPRD_CRYPTO_HMAC_SHA512_256	(SPRD_CRYPTO_HMAC + 0x0008)

#define SPRD_CRYPTO_MODE_LIMIT		0x07000000

#define SPRD_CRYPTO_MAIN_MODE_MASK  	0xFFFF0000
#define SPRD_CRYPTO_SUB_MODE_MASK   	0x0000FFFF
#define SPRD_CRYPTO_MAIN_MODE_OFFSET    16

enum sprd_crypto {
	SPRD_CRYPTO_ENC = 0,
	SPRD_CRYPTO_DEC = 1,
};

enum sprd_verify_res {
	SPRD_VERIFY_SUCCESS = 0,
	SPRD_VERIFY_FAILED
};

typedef struct {
	uint32_t decrypt;
	uint8_t *key1;
	uint32_t key1_len;
	uint8_t *key2;
	uint32_t key2_len;
	uint8_t *iv;
	uint32_t iv_len;
} sprd_aes_context_t;

typedef struct {
} sprd_hash_context_t;

typedef struct {
	uint8_t *key_n;
	uint8_t *key_eod;	//e or d
	uint32_t key_len;
	uint32_t pka_cmd[SPRD_CRYPTO_PKA_CMD_LEN];
} sprd_rsa_context_t;

typedef struct {
	sprd_crypto_algo_t algo;
	uint32_t continued;
	uint32_t end;

	union
	{
		sprd_aes_context_t aes;
		sprd_hash_context_t hash;
		sprd_rsa_context_t rsa;
	} info;

	uint8_t *in;
	uint32_t in_len;
	uint8_t *out;	//e or d
	uint32_t out_len;
} sprd_crypto_context_t;

sprd_crypto_err_t sprd_crypto_do(
        uint32_t algo,
        uint8_t *in,   uint32_t in_len,
        uint8_t *out,  uint32_t *out_len,
        uint8_t *key1, uint32_t key1_len,
	uint8_t *key2, uint32_t key2_len,
        uint8_t *iv,   uint32_t iv_len);

#define sprd_pal_memcpy sec_memcpy
#define sprd_pal_memset sec_memset
#define sprd_pal_memcmp sec_memcmp

enum {
	SPRD_HASH_MD5_SIZE		= 16,
	SPRD_HASH_SHA1_SIZE		= 20,
	SPRD_HASH_SHA224_SIZE		= 28,
	SPRD_HASH_SHA256_SIZE		= 32,
	SPRD_HASH_SHA384_SIZE		= 48,
	SPRD_HASH_SHA512_SIZE		= 64,
	SPRD_HASH_SHA512_224_SIZE	= 28,
	SPRD_HASH_SHA512_256_SIZE	= 32,
	SPRD_HASH_MAX_HASH_SIZE		= 64,
};

#define SPRD_HASH_SIZE(type)	((type) == SPRD_CRYPTO_HASH_MD5) ? (SPRD_HASH_MD5_SIZE) : \
				(((type) == SPRD_CRYPTO_HASH_SHA1) ? (SPRD_HASH_SHA1_SIZE) : \
				(((type) == SPRD_CRYPTO_HASH_SHA224) ? (SPRD_HASH_SHA224_SIZE) : \
				(((type) == SPRD_CRYPTO_HASH_SHA256) ? (SPRD_HASH_SHA256_SIZE) : \
				(((type) == SPRD_CRYPTO_HASH_SHA384) ? (SPRD_HASH_SHA384_SIZE) : \
				(((type) == SPRD_CRYPTO_HASH_SHA512) ? (SPRD_HASH_SHA512_SIZE) : \
				(((type) == SPRD_CRYPTO_HASH_SHA512_224) ? (SPRD_HASH_SHA512_224_SIZE) : \
				(((type) == SPRD_CRYPTO_HASH_SHA512_256) ? (SPRD_HASH_SHA512_256_SIZE) : (0))))))))

typedef enum {
	SPRD_RSA_NOPAD			= 0,

	SPRD_RSAES_PKCS1_V1_5		= 10,
	SPRD_RSAES_PKCS1_OAEP_MGF1	= 11,

	SPRD_RSASSA_PKCS1_V1_5		= 20,
	SPRD_RSASSA_PKCS1_PSS_MGF1	= 21,
} sprd_rsa_pad_type_t;

typedef struct {
	sprd_rsa_pad_type_t type;
	union {
		struct {
			sprd_crypto_algo_t type;
			const uint8_t *lparam;
			uint32_t lparamlen;
		} rsaes_oaep;

		struct {
			sprd_crypto_algo_t type;   /* md5/sha1/sha224/sha256/sha384/sha512 */
		} rsassa_v1_5;

		struct {
			sprd_crypto_algo_t type;   /* sha1/sha224/sha256/sha384/sha512 */
			sprd_crypto_algo_t mgf1_hash_type;   /* sha1/sha224/sha256/sha384/sha512 */
			uint32_t salt_len;
		} rsassa_pss;
	} pad;
} sprd_rsa_padding_t;

typedef struct {
	uint8_t *n;       /* Modulus */
	uint8_t *e;       /* Public exponent */
	uint32_t  n_len;
	uint32_t  e_len;
} sprd_rsa_pubkey_t;

/*
 * dig[in]:      the digest of message that was signed
 * dig_size[in]: the digest size in bytes
 * sig[in]:      the signature data
 * sig_size[in]: the length of the signature data (byte)
 */
sprd_crypto_err_t sprd_rsa_verify(const sprd_rsa_pubkey_t *pub_key,
                      const uint8_t *dig, uint32_t dig_size,
                      const uint8_t *sig, uint32_t sig_size,
                      sprd_rsa_padding_t padding, int32_t *result);

sprd_crypto_err_t sprd_crypto_test (void);

#endif /* SPRD_CRYPTO_H */

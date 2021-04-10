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

#include <sprd_pal_plat.h>
#include <sprd_crypto_log.h>

#ifndef R2P0LITE
#define R2P0LITE
#endif

#define SPRD_CRYPTO_MIN_DATA_LEN	0x8
#define SPRD_CRYPTO_MAX_DATA_LEN	0xFFF000

#define SPRD_CRYPTO_HASH_BUF_LEN	128
#define SPRD_CRYPTO_PKA_CMD_LEN		16 //size of item is 4 bytes.
#define SPRD_CRYPTO_MAX_RNG_SIZE	512
#define SPRD_CRYPTO_DUMP_SIZE		128
#define SPRD_CRYPTO_RSA_BUF_SIZE	512

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

#define SPRD_CRYPTO_ECC			(SPRD_CRYPTO_PKA + 0x30000)

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
	SPRD_VERIFY_FAILED = -1,
	SPRD_VERIFY_SUCCESS = 0
	//All values bigger than 0 should be special for secure boot.
};

typedef struct {
	uint8_t *dump;
} sprd_hash_context_t;

typedef struct {
	uint8_t *key_n;
	uint8_t *key_eod;	//e or d
	uint32_t key_len;
	uint32_t pka_cmd[SPRD_CRYPTO_PKA_CMD_LEN];
} sprd_rsa_context_t;

typedef struct {
	uint32_t pka_cmd[SPRD_CRYPTO_PKA_CMD_LEN];
} sprd_rng_context_t;

typedef struct {
	sprd_crypto_algo_t algo;
	uint32_t continued;
	uint32_t end;

	union
	{
		sprd_hash_context_t hash;
		sprd_rsa_context_t rsa;
		sprd_rng_context_t rng;
	} info;

	uint8_t *in;
	uint32_t in_len;
	uint8_t *out;	//e or d
	uint32_t out_len;
} sprd_crypto_context_t;

sprd_crypto_err_t
sprd_crypto_process (sprd_crypto_context_t *context);

void sprd_crypto_polling (void);
#ifdef R2P0LITE
void sprd_crypto_pka_polling (void);
#endif

sprd_crypto_err_t sprd_crypto_open (sprd_crypto_context_t* constext);
sprd_crypto_err_t sprd_crypto_close (sprd_crypto_context_t* constext);

void sprd_crypto_init (void);
void sprd_crypto_terminal(void);

sprd_crypto_err_t sprd_crypto_test (void);

#endif /* SPRD_CRYPTO_H */

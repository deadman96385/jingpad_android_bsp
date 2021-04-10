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

#ifndef SPRD_RSA_H
#define SPRD_RSA_H

#include <sprd_crypto.h>

typedef enum {
	SPRD_RSA_MODULUS          = 0x130,
	SPRD_RSA_PUBLIC_EXPONENT  = 0x230,
	SPRD_RSA_PRIVATE_EXPONENT = 0x330,
	SPRD_RSA_PRIME1           = 0x430,
	SPRD_RSA_PRIME2           = 0x530,
	SPRD_RSA_EXPONENT1        = 0x630,
	SPRD_RSA_EXPONENT2        = 0x730,
	SPRD_RSA_COEFFICIENT      = 0x830,
} sprd_rsa_key_attr_t;

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
			uint32_t salt_len;
		} rsassa_pss;
	} pad;
} sprd_rsa_padding_t;

typedef struct {
	uint8_t *n;       /* Modulus */
	uint8_t *e;       /* Public exponent */
	uint8_t *d;       /* Private exponent */
	uint32_t  n_len;
	uint32_t  e_len;
	uint32_t  d_len;
} sprd_rsa_keypair_t;

typedef struct {
	uint8_t *n;       /* Modulus */
	uint8_t *e;       /* Public exponent */
	uint32_t  n_len;
	uint32_t  e_len;
} sprd_rsa_pubkey_t;

/* RSA */
/*
 * e:  Public exponent
 * d:  Private exponent
 * n:  Modulus
 *
 * Optional CRT parameters
 * p, q:  N = pq
 * qp:  1/q mod p
 * dp:  d mod (p-1)
 * dq:  d mod (q-1)
 */

/*
 * keybits[in]: key length in bits
 * size[out]:   total size in bytes of rsa keypair
 */
sprd_crypto_err_t sprd_rsa_get_keypair_size(int32_t keybits, uint32_t *size);

/*
 * keybits[in]: key length in bits
 * size[out]:   total size in bytes of rsa public key
 */
sprd_crypto_err_t sprd_rsa_get_pubkey_size(int32_t keybits, uint32_t *size);

/*
 * Initialize RSA keypair
 *
 * keybits[in]:    rsa keypair length in bits
 * n/n_size[in]:   rsa modulus data and size in bytes
 * e/e_size[in]:   rsa public exponent data and size in bytes
 * d/d_size[in]:   rsa private exponent data and size in bytes
 * p/p_size[in]:   rsa prime1 data and size in bits, may be NULL/0
 * q/q_size[in]:   rsa prime2 data and size in bits, may be NULL/0
 * dp/dp_size[in]: rsa exponent2 data and size in bits, may be NULL/0
 * dq/dq_size[in]: rsa exponent2 data and size in bits, may be NULL/0
 * dq/dq_size[in]: rsa coefficient data and size in bits, may be NULL/0
 * keypair[out]:   output buffer, which is used to save initialized rsa key pair
 */
sprd_crypto_err_t sprd_rsa_init_keypair(int32_t keybits,
                      const uint8_t *n, uint32_t n_size,
                      const uint8_t *e, uint32_t e_size,
                      const uint8_t *d, uint32_t d_size,
                      const uint8_t *p, uint32_t p_size,
                      const uint8_t *q, uint32_t q_size,
                      const uint8_t *dp, uint32_t dp_size,
                      const uint8_t *dq, uint32_t dq_size,
                      const uint8_t *qp, uint32_t qp_size,
                      sprd_rsa_keypair_t *keypair);

/*
 * Initialize RSA public key
 *
 * keybits[in]:    rsa key length in bits
 * n/n_size[in]:   rsa modulus data and size in bytes
 * e/e_size[in]:   rsa public exponent data and size in bytes
 * pubkey[out]:    output buffer, which is used to save initialized rsa public key
 */
sprd_crypto_err_t sprd_rsa_init_pubkey(int32_t keybits,
                      const uint8_t *n, uint32_t n_size,
                      const uint8_t *e, uint32_t e_size,
                      sprd_rsa_pubkey_t *pubkey);

/*
 * Generate RSA keypair
 *
 * keybits[in]:   rsa key length in bits
 * e[in]:         optional, public exponent
 * e_size[in]:    optional, public exponent size in bytes
 * keypair[out]:  output buffer, which is used to save generated rsa key pair
 */
sprd_crypto_err_t sprd_rsa_gen_keypair(int32_t keybits,
                      const uint8_t *e, uint32_t e_size,
                      sprd_rsa_keypair_t *keypair);

sprd_crypto_err_t
sprd_rsa_key_gen(uint8_t* key_e, uint32_t key_e_len, int32_t key_len, uint8_t *key_n, uint8_t *key_d);

/*
 * Get key attribute
 *
 * attr[in]:      rsa key attribute ID
 * keypair[in]:   rsa keypair buffer
 * buffer[out]:   buffer, which is used to save required attribute
 * size[in/out]:  buffer max size and key attribute actual size in bytes
 */
sprd_crypto_err_t sprd_rsa_get_key_attr(sprd_rsa_key_attr_t attr,
                      sprd_rsa_keypair_t *keypair, void *buffer, uint32_t *size);

sprd_crypto_err_t sprd_rsa_public_encrypt(const sprd_rsa_pubkey_t *pub_key,
                      const uint8_t *src, uint32_t src_size,
                      uint8_t *dst, uint32_t *dst_size,
                      sprd_rsa_padding_t padding);
sprd_crypto_err_t sprd_rsa_private_decrypt(const sprd_rsa_keypair_t *priv_key,
                      const uint8_t *src, uint32_t src_size,
                      uint8_t *dst, uint32_t *dst_size,
                      sprd_rsa_padding_t padding);

/*
 * dig[in]:          the digest to sign
 * dig_size[in]:     the length of the digest to sign (byte)
 * sig[out]:         the signature data
 * sig_size[in/out]: the buffer size and resulting size of signature
 */
sprd_crypto_err_t sprd_rsa_sign(const sprd_rsa_keypair_t *priv_key,
                      const uint8_t *dig, uint32_t dig_size,
                      uint8_t *sig, uint32_t *sig_size, sprd_rsa_padding_t padding);

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

sprd_crypto_err_t
sprd_rsa_test (void);

#endif /* SPRD_RSA_H */

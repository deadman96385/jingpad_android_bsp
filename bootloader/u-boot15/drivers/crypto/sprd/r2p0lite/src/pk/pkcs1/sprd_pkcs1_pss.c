/*
* Copyright (c) 2017, Spreadtrum Communications.
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

#include <sprd_crypto.h>
#include <sprd_hash.h>
#include <sprd_rng.h>

#include <pkcs1/sprd_pkcs1.h>

#include "sprd_pkcs1_mgf1.h"

#define PSS_HASH_MIN SPRD_CRYPTO_HASH_SHA1
#define PSS_HASH_MAX SPRD_CRYPTO_HASH_SHA256

/**
   PKCS #1 v2.00 Signature Encoding
   @param msghash          The hash to encode
   @param msghashlen       The length of the hash (octets)
   @param saltlen          The length of the salt desired (octets)
   @param hash_type        The index of the hash desired
   @param mgf1_hash_type   The index of the mgf1 hash desired
   @param modulus_bitlen   The bit length of the RSA modulus
   @param out              [out] The destination of the encoding
   @param outlen           [in/out] The max size and resulting size of the encoded data
   @return CRYPT_OK if successful
*/
uint32_t sprd_pkcs1_pss_encode(const uint8_t *msghash, uint32_t msghashlen,
                            uint32_t saltlen, sprd_crypto_algo_t hash_type, sprd_crypto_algo_t mgf1_hash_type,
                            uint32_t modulus_bitlen,
                            uint8_t *out, uint32_t *outlen)
{
	uint8_t *DB, *mask, *salt, *hash;
	uint32_t x, y, hLen, modulus_len;
	uint32_t err;
	sprd_crypto_context_t md;

	if (msghash == NULL || out == NULL || outlen == NULL) {
		SPRD_CRYPTO_LOG_ERR("msghash or out or outlen invalid \n");
		return SPRD_CRYPTO_INVALID_ARG;
	}

	if(hash_type < PSS_HASH_MIN || hash_type > PSS_HASH_MAX) {
		SPRD_CRYPTO_LOG_ERR("hash_type invalid \n");
		return SPRD_CRYPTO_INVALID_ARG;
	}

	hLen        = SPRD_HASH_SIZE(hash_type);
	modulus_bitlen--;
	modulus_len = (modulus_bitlen>>3) + (modulus_bitlen & 7 ? 1 : 0);

	/* check sizes */
	if ((saltlen > modulus_len) || (modulus_len < hLen + saltlen + 2)) {
		SPRD_CRYPTO_LOG_ERR("saltlen/hLen invalid \n");
		return SPRD_CRYPTO_INVALID_ARG;
	}

	/* allocate ram for DB/mask/salt/hash of size modulus_len */
	DB   = sprd_pal_malloc(modulus_len*2);
	mask = sprd_pal_malloc(modulus_len);
	salt = sprd_pal_malloc(modulus_len);
	hash = sprd_pal_malloc(modulus_len);
	if (DB == NULL || mask == NULL || salt == NULL || hash == NULL) {
		if (DB != NULL) {
			sprd_pal_free(DB);
		}
		if (mask != NULL) {
			sprd_pal_free(mask);
		}
		if (salt != NULL) {
			sprd_pal_free(salt);
		}
		if (hash != NULL) {
			sprd_pal_free(hash);
		}
		return SPRD_CRYPTO_OUTOFMEM;
	}


	/* generate random salt */
	if (saltlen > 0) {
		err = sprd_rng_gen(salt, saltlen);
		if (err != SPRD_CRYPTO_SUCCESS) {
			SPRD_CRYPTO_LOG_ERR("get rng failed\n");
			goto LBL_ERR;
		}
	}

	/* M = (eight) 0x00 || msghash || salt, hash = H(M) */
	if ((err = sprd_hash_init(hash_type, &md)) != SPRD_CRYPTO_SUCCESS) {
		goto LBL_ERR;
	}
	sprd_pal_memset(DB, 0, 8);
	/* construct 8zeros|msghash|salt in one buffer
	 * because the uboot version config data end to 1 by default*/
	sprd_pal_memcpy(DB+8, msghash, msghashlen);
	sprd_pal_memcpy(DB+8+msghashlen, salt, saltlen);
	if ((err = sprd_hash_update(&md, DB, 8+msghashlen+saltlen)) != SPRD_CRYPTO_SUCCESS) {
		goto LBL_ERR;
	}
	if ((err = sprd_hash_final(&md, hash)) != SPRD_CRYPTO_SUCCESS) {
		goto LBL_ERR;
	}

	/* generate DB = PS || 0x01 || salt, PS == modulus_len - saltlen - hLen - 2 zero bytes */
	x = 0;
	sprd_pal_memset(DB + x, 0, modulus_len - saltlen - hLen - 2);
	x += modulus_len - saltlen - hLen - 2;
	DB[x++] = 0x01;
	sprd_pal_memcpy(DB + x, salt, saltlen);
	/* x += saltlen; */

	/* generate mask of length modulus_len - hLen - 1 from hash */
	if ((err = sprd_pkcs1_mgf1(mgf1_hash_type, hash, hLen, mask, modulus_len - hLen - 1)) != SPRD_CRYPTO_SUCCESS) {
		goto LBL_ERR;
	}

	/* xor against DB */
	for (y = 0; y < (modulus_len - hLen - 1); y++) {
		DB[y] ^= mask[y];
	}

	/* output is DB || hash || 0xBC */
	if (*outlen < modulus_len) {
		*outlen = modulus_len;
		err = SPRD_CRYPTO_SHORT_BUFFER;
		goto LBL_ERR;
	}

	/* DB len = modulus_len - hLen - 1 */
	y = 0;
	sprd_pal_memcpy(out + y, DB, modulus_len - hLen - 1);
	y += modulus_len - hLen - 1;

	/* hash */
	sprd_pal_memcpy(out + y, hash, hLen);
	y += hLen;

	/* 0xBC */
	out[y] = 0xBC;

	/* now clear the 8*modulus_len - modulus_bitlen most significant bits */
	out[0] &= 0xFF >> ((modulus_len<<3) - modulus_bitlen);

	/* store output size */
	*outlen = modulus_len;
	err = SPRD_CRYPTO_SUCCESS;
LBL_ERR:

	sprd_pal_free(hash);
	sprd_pal_free(salt);
	sprd_pal_free(mask);
	sprd_pal_free(DB);

	return err;
}

/**
   PKCS #1 v2.00 PSS decode
   @param  msghash         The hash to verify
   @param  msghashlen      The length of the hash (octets)
   @param  sig             The signature data (encoded data)
   @param  siglen          The length of the signature data (octets)
   @param  saltlen         The length of the salt used (octets)
   @param  hash_type       The index of the hash desired
   @param  mgf1_hash_type  The index of the mgf1 hash desired
   @param  modulus_bitlen  The bit length of the RSA modulus
   @param  res             [out] The result of the comparison, 1==valid, 0==invalid
   @return CRYPT_OK if successful (even if the comparison failed)
*/
uint32_t sprd_pkcs1_pss_decode(const uint8_t *msghash, uint32_t msghashlen,
			    const uint8_t *sig, uint32_t siglen,
                            uint32_t saltlen, sprd_crypto_algo_t hash_type, sprd_crypto_algo_t mgf1_hash_type,
                            uint32_t modulus_bitlen, int *res)
{
	uint8_t *DB, *mask, *salt, *hash;
	uint32_t x, y, hLen, modulus_len;
	uint32_t err;
	sprd_crypto_context_t md;

	if (msghash == NULL || res == NULL) {
		SPRD_CRYPTO_LOG_ERR("msghash or res invalid \n");
		return SPRD_CRYPTO_INVALID_ARG;
	}

	/* default to invalid */
	*res = SPRD_VERIFY_FAILED;

	/* ensure hash is valid */
	if(hash_type < PSS_HASH_MIN || hash_type > PSS_HASH_MAX) {
		SPRD_CRYPTO_LOG_ERR("hash_type invalid \n");
		return SPRD_CRYPTO_INVALID_ARG;
	}

	hLen = SPRD_HASH_SIZE(hash_type);
	modulus_bitlen--;
	modulus_len = (modulus_bitlen>>3) + (modulus_bitlen & 7 ? 1 : 0);

	/* check sizes */
	if ((saltlen > modulus_len) ||
			(modulus_len < hLen + saltlen + 2)) {
		return SPRD_CRYPTO_INVALID_ARG;
	}

	/* allocate ram for DB/mask/salt/hash of size modulus_len */
	DB   = sprd_pal_malloc(modulus_len);
	mask = sprd_pal_malloc(modulus_len*2);
	salt = sprd_pal_malloc(modulus_len);
	hash = sprd_pal_malloc(modulus_len);
	if (DB == NULL || mask == NULL || salt == NULL || hash == NULL) {
		if (DB != NULL) {
			sprd_pal_free(DB);
		}
		if (mask != NULL) {
			sprd_pal_free(mask);
		}
		if (salt != NULL) {
			sprd_pal_free(salt);
		}
		if (hash != NULL) {
			sprd_pal_free(hash);
		}
		return SPRD_CRYPTO_OUTOFMEM;
	}

	/* ensure the 0xBC byte */
	if (sig[siglen-1] != 0xBC) {
		err = SPRD_CRYPTO_INVALID_PACKET;
		goto LBL_ERR;
	}

	/* copy out the DB */
	x = 0;
	sprd_pal_memcpy(DB, sig + x, modulus_len - hLen - 1);
	x += modulus_len - hLen - 1;

	/* copy out the hash */
	sprd_pal_memcpy(hash, sig + x, hLen);
	/* x += hLen; */

	/* check the MSB */
	if ((sig[0] & ~(0xFF >> ((modulus_len<<3) - (modulus_bitlen)))) != 0) {
		err = SPRD_CRYPTO_INVALID_PACKET;
		goto LBL_ERR;
	}

	/* generate mask of length modulus_len - hLen - 1 from hash */
	if ((err = sprd_pkcs1_mgf1(mgf1_hash_type, hash, hLen, mask, modulus_len - hLen - 1)) != SPRD_CRYPTO_SUCCESS) {
		goto LBL_ERR;
	}

	/* xor against DB */
	for (y = 0; y < (modulus_len - hLen - 1); y++) {
		DB[y] ^= mask[y];
	}

	/* now clear the first byte [make sure smaller than modulus] */
	DB[0] &= 0xFF >> ((modulus_len<<3) - (modulus_bitlen));

	/* DB = PS || 0x01 || salt, PS == modulus_len - saltlen - hLen - 2 zero bytes */

	/* check for zeroes and 0x01 */
	for (x = 0; x < modulus_len - saltlen - hLen - 2; x++) {
		if (DB[x] != 0x00) {
			err = SPRD_CRYPTO_INVALID_PACKET;
			goto LBL_ERR;
		}
	}

	/* check for the 0x01 */
	if (DB[x++] != 0x01) {
		err = SPRD_CRYPTO_INVALID_PACKET;
		goto LBL_ERR;
	}

	/* M = (eight) 0x00 || msghash || salt, mask = H(M) */
	if ((err = sprd_hash_init(hash_type, &md)) != SPRD_CRYPTO_SUCCESS) {
		goto LBL_ERR;
	}
	sprd_pal_memset(mask, 0, 8);
	/* construct 8zeros|msghash|salt in one buffer
	 * because the uboot version config data end to 1 by default*/
	sprd_pal_memcpy(mask+8, msghash, msghashlen);
	sprd_pal_memcpy(mask+8+msghashlen, DB+x, saltlen);
	if ((err = sprd_hash_update(&md, mask, 8+msghashlen+saltlen)) != SPRD_CRYPTO_SUCCESS) {
		goto LBL_ERR;
	}
	if ((err = sprd_hash_final(&md, mask)) != SPRD_CRYPTO_SUCCESS) {
		goto LBL_ERR;
	}

	/* mask == hash means valid signature */
	if (sprd_pal_memcmp(mask, hash, hLen) == 0) {
		*res = SPRD_VERIFY_SUCCESS;
	}

	err = SPRD_CRYPTO_SUCCESS;
LBL_ERR:

	sprd_pal_free(hash);
	sprd_pal_free(salt);
	sprd_pal_free(mask);
	sprd_pal_free(DB);

	return err;
}

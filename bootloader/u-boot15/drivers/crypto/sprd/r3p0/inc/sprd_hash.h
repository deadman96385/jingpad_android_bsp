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

#ifndef SPRD_HASH_H
#define SPRD_HASH_H

#include <sprd_crypto.h>

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

sprd_crypto_err_t
sprd_hash_get_context_size(sprd_crypto_algo_t algo, uint32_t *size);

sprd_crypto_err_t
sprd_hash_init(sprd_crypto_algo_t algo, sprd_crypto_context_t *context);

sprd_crypto_err_t
sprd_hash_update(sprd_crypto_context_t *context, const uint8_t *in, uint32_t in_len);

sprd_crypto_err_t
sprd_hash_final(sprd_crypto_context_t *context, uint8_t *digest);

sprd_crypto_err_t
sprd_hash_reset(sprd_crypto_context_t *context);

sprd_crypto_err_t
sprd_hash_copy_context(sprd_crypto_context_t *dst_ctx, sprd_crypto_context_t *src_ctx);

sprd_crypto_err_t
sprd_hash_digest(sprd_crypto_algo_t type, const uint8_t *in, uint32_t in_len, uint8_t *digest);

sprd_crypto_err_t
sprd_hash_test (void);

#endif /* SPRD_HASH_H */

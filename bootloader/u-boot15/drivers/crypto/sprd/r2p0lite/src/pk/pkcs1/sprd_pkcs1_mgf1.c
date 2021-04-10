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

#include "sprd_pkcs1_mgf1.h"

#define MGF1_HASH_MIN SPRD_CRYPTO_HASH_SHA1
#define MGF1_HASH_MAX SPRD_CRYPTO_HASH_SHA256

#define MGF1_STORE32H(x, y) \
	do { (y)[0] = (unsigned char)(((x)>>24)&255); (y)[1] = (unsigned char)(((x)>>16)&255); \
	(y)[2] = (unsigned char)(((x)>>8)&255); (y)[3] = (unsigned char)((x)&255); } while(0)

/**
   Perform PKCS #1 MGF1 (internal)
   @param hash_idx    The index of the hash desired
   @param seed        The seed for MGF1
   @param seedlen     The length of the seed
   @param mask        [out] The destination
   @param masklen     The length of the mask desired
   @return CRYPT_OK if successful
*/
uint32_t sprd_pkcs1_mgf1(sprd_crypto_algo_t hash_type,
		const unsigned char *seed, unsigned long seedlen,
		unsigned char *mask, unsigned long masklen)
{
	unsigned long hLen, x;
	uint32_t counter;
	uint32_t err;
	sprd_crypto_context_t *md;
	unsigned char *buf;
	unsigned char *tmp;

	if (seed == NULL || mask == NULL) {
		SPRD_CRYPTO_LOG_ERR("seed or mask invalid \n");
		return SPRD_CRYPTO_INVALID_ARG;
	}

	/* ensure valid hash */
	if(hash_type < MGF1_HASH_MIN || hash_type > MGF1_HASH_MAX) {
		SPRD_CRYPTO_LOG_ERR("hash_type invalid \n");
		return SPRD_CRYPTO_INVALID_ARG;
	}

	/* get hash output size */
	hLen = SPRD_HASH_SIZE(hash_type);

	/* allocate memory */
	md  = sprd_pal_malloc(sizeof(sprd_crypto_context_t));
	buf = sprd_pal_malloc(hLen);
	tmp = sprd_pal_malloc(seedlen+4);
	if (md == NULL || buf == NULL || tmp == NULL) {
		if (md != NULL) {
			sprd_pal_free(md);
		}
		if (buf != NULL) {
			sprd_pal_free(buf);
		}
		if (tmp != NULL) {
			sprd_pal_free(tmp);
		}
		return SPRD_CRYPTO_OUTOFMEM;
	}
	sprd_pal_memcpy(tmp, seed, seedlen);

	/* start counter */
	counter = 0;

	while (masklen > 0) {
		/* handle counter */
		MGF1_STORE32H(counter, tmp+seedlen);
		++counter;

		/* get hash of seed || counter */
		if ((err = sprd_hash_init(hash_type, md)) != SPRD_CRYPTO_SUCCESS) {
			goto LBL_ERR;
		}
		if ((err = sprd_hash_update(md, tmp, seedlen+4)) != SPRD_CRYPTO_SUCCESS) {
			goto LBL_ERR;
		}
		if ((err = sprd_hash_final(md, buf)) != SPRD_CRYPTO_SUCCESS) {
			goto LBL_ERR;
		}

		/* store it */
		for (x = 0; x < hLen && masklen > 0; x++, masklen--) {
			*mask++ = buf[x];
		}
	}

	err = SPRD_CRYPTO_SUCCESS;
LBL_ERR:

	sprd_pal_free(buf);
	sprd_pal_free(md);
	sprd_pal_free(tmp);

	return err;
}

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

#include <sprd_crypto.h>
#include <sprd_hash.h>

static uint8_t buf[SPRD_CRYPTO_HASH_BUF_LEN] __attribute__ ((aligned(SPRD_PAL_CACHE_LINE)));
static uint8_t dump[SPRD_CRYPTO_DUMP_SIZE] __attribute__ ((aligned(SPRD_PAL_CACHE_LINE)));

sprd_crypto_err_t
sprd_hash_get_context_size(sprd_crypto_algo_t algo, uint32_t *size) {
	return sizeof(sprd_crypto_context_t);
}

sprd_crypto_err_t
sprd_hash_init(sprd_crypto_algo_t algo, sprd_crypto_context_t *context) {
	sprd_crypto_err_t err;

	SPRD_CRYPTO_LOG_TRACE("algo = 0x%x context = %p\n", algo, context);

	sprd_pal_memset(context, 0, sizeof(sprd_crypto_context_t));
	context->info.hash.dump = dump;
	sprd_pal_flush_by_vaddr(context->info.hash.dump, SPRD_CRYPTO_DUMP_SIZE);

	context->algo = algo;
	err = sprd_crypto_open(context);
	if (err == SPRD_CRYPTO_SUCCESS) {
		return err;
	} else {
		SPRD_CRYPTO_LOG_ERR("FAILED!\n");
		return SPRD_CRYPTO_ERROR;
	}
}

//precondition
sprd_crypto_err_t
sprd_hash_update(sprd_crypto_context_t *context, const uint8_t *in, uint32_t in_len) {
	sprd_crypto_err_t err;
	uint8_t *in_temp;
	uint32_t in_len_sum;

	SPRD_CRYPTO_LOG_TRACE("in = %p, in_len = %d \n", in, in_len);

	in_temp = (uint8_t*)in;
	in_len_sum = in_len;

	sprd_pal_clean_by_vaddr(in, in_len);
	sprd_pal_flush_by_vaddr(buf, SPRD_CRYPTO_HASH_BUF_LEN);

	while(in_len_sum > SPRD_CRYPTO_MAX_DATA_LEN) {
		context->end = 0;
		context->in = in_temp;
		context->in_len = SPRD_CRYPTO_MAX_DATA_LEN;
		context->out = NULL;
		context->out_len = 0;

		SPRD_CRYPTO_LOG_TRACE("end = %d, in_len_sum == %d\n", context->end, in_len_sum);

		err = sprd_crypto_process(context);
		if (err != SPRD_CRYPTO_SUCCESS) {
			SPRD_CRYPTO_LOG_ERR("sprd_crypt_process return 0x%x\n", err);
			goto failed;
		}

		SPRD_CRYPTO_LOG_TRACE("waiting for polling!\n");
		sprd_crypto_polling();

		in_temp += context->in_len;
		in_len_sum -= context->in_len;
	}

	context->end = 1;
	context->in = in_temp;
	context->in_len = in_len_sum;
	context->out = buf;
	context->out_len = SPRD_HASH_SIZE(context->algo);

	SPRD_CRYPTO_LOG_TRACE("end = %d, in_len_sum == %d\n", context->end, in_len_sum);

	err = sprd_crypto_process(context);
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("sprd_crypt_process return 0x%x\n", err);
		goto failed;
	}

	SPRD_CRYPTO_LOG_TRACE("waiting for polling!\n");
	sprd_crypto_polling();

	sprd_pal_invalidate_by_vaddr(buf, SPRD_CRYPTO_HASH_BUF_LEN);

	return SPRD_CRYPTO_SUCCESS;

failed:
	if (err != SPRD_CRYPTO_SUCCESS) {
		context->info.hash.dump = NULL;
		sprd_crypto_close(context);
	}

	return err;
}

sprd_crypto_err_t
sprd_hash_final(sprd_crypto_context_t *context, uint8_t *digest) {
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;

	SPRD_CRYPTO_LOG_TRACE("context = %p digest = %p!\n", context, digest);
	if (digest != NULL) {
		sprd_pal_memcpy(digest, buf, SPRD_HASH_SIZE(context->algo));
	}

	context->info.hash.dump = NULL;
	sprd_crypto_close(context);
	return err;
}

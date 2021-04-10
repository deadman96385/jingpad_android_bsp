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

static uint8_t buf[SPRD_CRYPTO_MAX_RNG_SIZE] __attribute__ ((aligned(SPRD_PAL_CACHE_LINE)));

sprd_crypto_err_t
sprd_rng_gen(uint8_t *out, uint32_t out_len) {
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;
	sprd_crypto_context_t context;
	uint8_t *out_temp;
	uint32_t count, len_temp;

	SPRD_CRYPTO_LOG_TRACE("out = %p, out_len = %d!\n", out, out_len);

	sprd_pal_memset(&context, 0, sizeof(sprd_crypto_context_t));
	context.algo = SPRD_CRYPTO_RNG;
	SPRD_CRYPTO_LOG_TRACE("algo = 0x%x context = %p\n", context.algo, &context);

	err = sprd_crypto_open(&context);
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("FAILED!\n");
		return SPRD_CRYPTO_ERROR;
	}

	context.continued = 0;
	context.end = 1;
	context.in = NULL;
	context.in_len = 0;
	context.out = buf;
	context.out_len = SPRD_CRYPTO_MAX_RNG_SIZE;
	sprd_pal_flush_by_vaddr(context.out, context.out_len);

	out_temp = out;
	count = (out_len + SPRD_CRYPTO_MAX_RNG_SIZE -1) / SPRD_CRYPTO_MAX_RNG_SIZE;
	while (count > 0) {
		len_temp = count > 1 ? SPRD_CRYPTO_MAX_RNG_SIZE : out_len - (out_temp - out);
		memset(buf, 0, SPRD_CRYPTO_MAX_RNG_SIZE);
		sprd_pal_flush_by_vaddr(buf, SPRD_CRYPTO_MAX_RNG_SIZE);
		err = sprd_crypto_process(&context);
		if (err != SPRD_CRYPTO_SUCCESS) {
			SPRD_CRYPTO_LOG_ERR("sprd_crypto_process return 0x%x\n", err);
			goto failed;
		}

		SPRD_CRYPTO_LOG_TRACE("waiting for sem_process!\n");
#ifndef R2P0LITE
		sprd_crypto_polling();
#else
		sprd_crypto_pka_polling();
#endif
		sprd_pal_invalidate_by_vaddr(buf, SPRD_CRYPTO_MAX_RNG_SIZE);

		sprd_pal_memcpy(out_temp, buf, len_temp);
		out_temp += len_temp;
		count--;
	}

failed:
	sprd_crypto_close(&context);
	return err;
}

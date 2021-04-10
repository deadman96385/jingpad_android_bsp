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
#include <sprd_ce.h>
#include <sprd_crypto.h>
#include <sprd_pka.h>

#define SPRD_CRYPTO_BUF_NUM	(8)

#define SPRD_CRYPTO_ARGCHK(x)   if (!(x)) return SPRD_CRYPTO_INVALID_ARG;

sprd_crypto_err_t
sprd_crypto_process(sprd_crypto_context_t *context) {
	sprd_crypto_err_t err;

	SPRD_CRYPTO_LOG_TRACE("in = %p, in_len = %d\n", context->in, context->in_len);
	SPRD_CRYPTO_LOG_TRACE("out = %p, out_len = %d\n", context->out, context->out_len);
	SPRD_CRYPTO_LOG_TRACE("end = %d, continued = %d\n", context->end, context->continued);

	//SPRD_CRYPTO_ARGCHK(context->info.algo < sizeof(s_algo_translation)/sizeof(struct algo_translation));

	SPRD_CRYPTO_LOG_TRACE("context->algo = 0x%x\n", context->algo);
	switch (context->algo & SPRD_CRYPTO_MAIN_MODE_MASK) {
	case SPRD_CRYPTO_HASH:
		SPRD_CRYPTO_LOG_TRACE("SPRD_CE_HASH\n");

		if (context->in_len == 0 && context->end == 0) {
			SPRD_CRYPTO_LOG_TRACE("hash(0)!\n");
			err = SPRD_CRYPTO_SUCCESS;
			goto failed;
		}

		break;

	case SPRD_CRYPTO_RSA:
		SPRD_CRYPTO_LOG_TRACE("SPRD_CE_RSA\n");

		if (context->info.rsa.key_n == NULL
			|| context->info.rsa.key_eod == 0
			|| context->info.rsa.key_len == 0) {
			SPRD_CRYPTO_LOG_ERR("Bad RSA key!\n");
			err = SPRD_CRYPTO_INVALID_ARG;
			goto failed;
		}

		SPRD_CRYPTO_LOG_TRACE("key1 = %p, key1_len = %d\n", context->info.rsa.key_n, context->info.rsa.key_len);
		SPRD_CRYPTO_LOG_TRACE("key2 = %p, key2_len = %d\n", context->info.rsa.key_eod, context->info.rsa.key_len);
		break;

	case SPRD_CRYPTO_RNG:
		SPRD_CRYPTO_LOG_TRACE("SPRD_CRYPTO_RNG\n");
		if (context->out_len != SPRD_CRYPTO_MAX_RNG_SIZE) {
			SPRD_CRYPTO_LOG_TRACE("Not request fixed-size-byte RNG!\n");
			err = SPRD_CRYPTO_INVALID_ARG;
			goto failed;
		}
		break;

	default:
		SPRD_CRYPTO_LOG_ERR("bad algo!\n");
		err = SPRD_CRYPTO_NOSUPPORT;
		goto failed;
		break;
	}

	sprd_ce_write_cmd(context);
	context->continued = 1;

	return SPRD_CRYPTO_SUCCESS;

failed:
	return err;
}

void sprd_crypto_polling (void) {
	sprd_ce_polling();
}

sprd_crypto_err_t
sprd_crypto_open(sprd_crypto_context_t* context) {
	sprd_ce_init();
	sprd_ce_open();
	SPRD_CRYPTO_LOG_TRACE("context = %p\n", context);
	return SPRD_CRYPTO_SUCCESS;
}

sprd_crypto_err_t
sprd_crypto_close(sprd_crypto_context_t* context) {
	sprd_ce_close();
	sprd_ce_terminal();
	SPRD_CRYPTO_LOG_TRACE("context = %p\n", context);
	return SPRD_CRYPTO_SUCCESS;
}

void sprd_crypto_init (void) {
}

void sprd_crypto_terminal (void) {
}

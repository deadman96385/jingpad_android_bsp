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
#include <sprd_rng.h>

sprd_crypto_err_t sprd_rng_test (void) {
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;
	static uint8_t buf[8192];
	uint32_t len[] = {511, 512, 2047, 2048, 4095, 4096, 6143, 6144, 8191, 8192, 0};
	uint32_t i = 0, len_temp;

	for (i = 0; len[i] != 0; i++) {
		err = sprd_rng_gen(buf, len[i]);
		if (err != SPRD_CRYPTO_SUCCESS) {
			SPRD_CRYPTO_LOG_ERR("****sprd_rng_test test[%d] FAILED!****\n", i);
			goto failed;
		}

		len_temp = len[i] / 2;

		SPRD_CRYPTO_LOG_TRACE("&buf[0] = %p, &buf[len_temp] = %p, len_temp = %d\n", &buf[0], &buf[len_temp], len_temp);
		if (sprd_pal_memcmp(&buf[0], &buf[len_temp], len_temp) == 0) {
			SPRD_CRYPTO_LOG_ERR("****sprd_rng_test test[%d] FAILED!****\n", i);
			err = SPRD_CRYPTO_ERR_RESULT;
			goto failed;
		}
	}

	return SPRD_CRYPTO_SUCCESS;

failed:
	return err;
}

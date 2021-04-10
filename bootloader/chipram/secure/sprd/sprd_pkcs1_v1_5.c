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

#include <security/sec_string.h>
#include "sprd_pkcs1.h"

/** PKCS #1 v1.5 decode.
 *
 *  msg              The encoded data to decode
 *  msglen           The length of the encoded data (octets)
 *  block_type       Block type to use in padding
 *  modulus_bitlen   The bit length of the RSA modulus
 *  out              [out] Destination of decoding
 *  outlen           [in/out] The max size and resulting size of the decoding
 *  is_valid         [out] Boolean whether the padding was valid
 *
 *  SPRD_CRYPTO_SUCCESS if successful (even if invalid)
 */
uint32_t sprd_pkcs1_v1_5_decode(const uint8_t *msg,
		uint32_t msglen,
		int32_t block_type,
		uint32_t  modulus_len,
		uint8_t *out,
		uint32_t  *outlen,
		int32_t *is_valid)
{
	uint32_t ps_len, i;
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;

	if (msg == NULL || msglen == 0) {
		SPRD_CRYPTO_LOG_ERR("msg is %p or msglen is %d\n", msg, msglen);
		return SPRD_CRYPTO_INVALID_ARG;
	}

	if (is_valid == NULL) {
		SPRD_CRYPTO_LOG_ERR("is_valid is NULL\n");
		return SPRD_CRYPTO_INVALID_ARG;
	}

	/* default to invalid packet */
	*is_valid = 0;

	/* test message size */
	if ((msglen > modulus_len) || (modulus_len < 11)) {
		SPRD_CRYPTO_LOG_ERR("msglen(%d) is too big or too small\n", msglen);
		return SPRD_CRYPTO_INVALID_PACKET;
	}

	/* separate encoded message */
	if ((msg[0] != 0x00) || (msg[1] != (uint8_t)block_type)) {
		SPRD_CRYPTO_LOG_ERR("bad msg[0](0x%x) or msg[1](0x%x)\n", msg[0], msg[1]);
		return SPRD_CRYPTO_INVALID_PACKET;
	}

	switch (block_type) {
		case SPRD_PKCS_1_EME:
			for (i = 2; i < modulus_len; i++) {
				/* separator */
				if (msg[i] == 0x00) { break; }
			}
			break;

		case SPRD_PKCS_1_EMSA:
			for (i = 2; i < modulus_len; i++) {
				if (msg[i] != 0xFF) { break; }
			}

			/* separator check */
			if (msg[i] != 0x00) {
				SPRD_CRYPTO_LOG_ERR("There was no 0x00 to separate ps from msg. msg[%d] = 0x%x\n", i, msg[i]);
				return SPRD_CRYPTO_INVALID_PACKET;
			}
			break;

		default:
			SPRD_CRYPTO_LOG_ERR("invalid block type in padding(0x%x)\n", block_type);
			return SPRD_CRYPTO_INVALID_PADDING;
	}

	ps_len = i++ - 2;
	if (i >= modulus_len) {
		SPRD_CRYPTO_LOG_ERR("There was no 0x00 to separate ps from msg. msg[%d] = 0x%x\n", i, msg[i]);
		return SPRD_CRYPTO_INVALID_PACKET;
	}

	if (ps_len < 8)
	{
		SPRD_CRYPTO_LOG_ERR("the length of ps(%d) is less than 8\n", ps_len);
		return SPRD_CRYPTO_INVALID_PACKET;
	}

	if (out == NULL || outlen == NULL
			|| *outlen < (msglen - (2 + ps_len + 1))) {
		SPRD_CRYPTO_LOG_ERR("out(%p) or outlen(%p) is less than required\n", out, outlen);
		return SPRD_CRYPTO_INVALID_ARG;
	}

	*outlen = (msglen - (2 + ps_len + 1));
	sprd_pal_memcpy(out, &msg[2 + ps_len + 1], *outlen);
	*is_valid = 1;

	return err;
}


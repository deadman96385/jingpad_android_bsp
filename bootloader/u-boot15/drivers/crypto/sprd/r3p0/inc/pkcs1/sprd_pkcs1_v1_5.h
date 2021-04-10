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

#ifndef SPRD_PKCS1_V1_5_H
#define SPRD_PKCS1_V1_5_H

#include <sprd_crypto.h>

enum sprd_pkcs_1_v1_5_padding_type
{
	SPRD_PKCS_1_EMSA   = 1,        /* Block type 1 (PKCS #1 v1.5 signature padding) */
	SPRD_PKCS_1_EME    = 2         /* Block type 2 (PKCS #1 v1.5 encryption padding) */
};

uint32_t sprd_pkcs1_v1_5_encode(const uint8_t *msg,
				      uint32_t msglen,
				      int32_t block_type,
				      uint32_t modulus_len,
				      uint8_t *out,
				      uint32_t *outlen);

uint32_t sprd_pkcs1_v1_5_decode(const uint8_t *msg,
				      uint32_t msglen,
				      int32_t block_type,
				      uint32_t modulus_len,
				      uint8_t *out,
				      uint32_t *outlen,
				      int32_t *is_valid);

#endif /* SPRD_PKCS1_V1_5_H */

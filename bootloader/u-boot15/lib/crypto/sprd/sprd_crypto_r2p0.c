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
#ifndef USE_HOSTCC
#include <linux/string.h>
#include <linux/stddef.h>
#else
#include <stdio.h>
#include <string.h>
#endif /* USE_HOSTCC */

void invert_char(unsigned char *src, int len)
{
	int i = 0, j = len - 1;
	unsigned char tmp;
	while (i < j) {
		tmp = src[i];
		src[i] = src[j];
		src[j] = tmp;
		i += 1;
		j -= 1;
	}
}

int padding_check_PKCS1_type_1(unsigned char *to, int tlen, const unsigned char *from, int flen, int num)
{
	int i, j;
	const unsigned char *p;

	p = from;
	if ((num != (flen + 1)) || (*(p++) != 01)) {
		//(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_BLOCK_TYPE_IS_NOT_01);
		return (-1);
	}

	/* scan over padding data */
	j = flen - 1;		/* one for type. */
	for (i = 0; i < j; i++) {
		if (*p != 0xff) {	/* should decrypt to 0xff */
			if (*p == 0) {
				p++;
				break;
			} else {
				//(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_BAD_FIXED_HEADER_DECRYPT);
				return (-1);
			}
		}
		p++;
	}

	if (i == j) {
		//(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_NULL_BEFORE_BLOCK_MISSING);
		return (-1);
	}

	if (i < 8) {
		//(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_BAD_PAD_BYTE_COUNT);
		return (-1);
	}
	i++;			/* Skip over the '\0' */
	j -= i;
	if (j > tlen) {
		//(RSA_F_RSA_PADDING_CHECK_PKCS1_TYPE_1,RSA_R_DATA_TOO_LARGE);
		return (-1);
	}
	memcpy(to, p, (unsigned int)j);

	return (j);
}

void sha256_csum_wd(const unsigned char *input,unsigned int ilen,unsigned char *output,unsigned int chunk_sz) {
	unsigned int outlen = 32;
	sprd_crypt_do(
		SPRD_CRYPT_HASH_SHA256,
		input, ilen,
		output, &outlen,
		NULL, 0,
		NULL, 0);
}

int RSA_PubDec(unsigned char *pub_E, unsigned char *mod_N, int bitLen_N, unsigned char *from, unsigned char *to) {
	unsigned int outlen = 256;
	unsigned char key[260];
	int byteLen_N = bitLen_N >> 3;
	unsigned char text[byteLen_N];

	memcpy(key, mod_N, 256);
	memcpy(key+256, pub_E, 4);
	invert_char(key+256,sizeof(unsigned int));
	sprd_crypt_do(
		SPRD_CRYPT_RSA_ENC_2048,
		from, 256,
		text, &outlen,
		key, 260,
		NULL, 0);
	return padding_check_PKCS1_type_1(to,byteLen_N,text+1,byteLen_N -1,byteLen_N);
}

int AES_CBC_Dec(unsigned char *ct, unsigned int ct_len, unsigned char *pt, unsigned int *pt_len,
		unsigned char *key, unsigned int key_len, unsigned char *iv, unsigned int iv_len) {

	return sprd_crypt_do(
		SPRD_CRYPT_AES_CBC,
		ct, ct_len,
		pt, pt_len,
		key, key_len,
		iv, iv_len);
}


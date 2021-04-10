/*
 * Copyright (c) 2019, Spreadtrum Communications.
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
 *
 * The header file for software implementation of rsa algorithm.
 *
 */

#include <malloc.h>
#include <common.h>

#define RSA_3	0x3L
#define RSA_F4	0x10001L

/*
 * Generate RSA keypair , return modulus and private exponent
 * Parameter:
 * [IN]pubExp: public expoenent, should be RSA_3 or RSA_F4,
 *             to be compatible wi * th rsa->e from openssl,
 *             the pubExp should be BIG-ENDIAN like [0~3]={0x00,0x01,0x00,0x01}
 * [IN]bitLen_N: 2048, ...
 * [OUT]mod_N: modulus ,length should be bitLen_N>>3 bytes
 * [OUT]prvExp: private exponent ,length should be bitLen_N>>3 bytes
 * Return value:
 *   true: generate success
 *   false: generate failed
 */
int RSA_Create(unsigned char *pubExp, int bitLen_N,
		unsigned char *mod_N, unsigned char *prvExp);

/*
 * Encrypt using private key with pkcs1 padding, Means signature
 * Parameter:
 * [IN]prvExp:  private exponent ,length should be bitLen_N>>3 bytes
 * [IN]mod_N:  modulus ,length should be bitLen_N>>3 bytes
 * [IN]bitLen_N: bit length of mod_N
 * [IN]from: clear text to be signed, MAX length is bitLen_N>>3-11
 *           due to will be padded using pkcs1
 * [IN]flen: data length of "from" buffer, MAX is  bitLen_N>>3-11
 * [OUT]to: signature, always be bitLen_N>>3 bytes length
 * Return value:
 *   true: sign success
 *   false: sign failed
 */
int RSA_PrvEnc(unsigned char *prvExp, unsigned char *mod_N,
		int bitLen_N, unsigned char *from, int flen, unsigned char *to);

/*
 * Encrypt using private key with no padding, Means signature
 * Parameter:
 * [IN]prvExp:  private exponent ,length should be bitLen_N>>3 bytes
 * [IN]mod_N:  modulus ,length should be bitLen_N>>3 bytes
 * [IN]bitLen_N: bit length of mod_N
 * [IN]from: clear text to be signed, MAX length is bitLen_N>>3
 * [IN]flen: data length of "from" buffer, MAX is  bitLen_N>>3
 * [OUT]to: signature, always be bitLen_N>>3 bytes length
 * Return value:
 *   true: sign success
 *   false: sign failed
 */
int RSA_PrvEnc_No_Pad(unsigned char *prvExp, unsigned char *mod_N,
		int bitLen_N, unsigned char *from, int flen, unsigned char *to);

/*
 * Decrypt using public key with pkcs1 padding,  Means verification
 * Parameter:
 * [IN]pubExp: public expoenent, should be RSA_3 or RSA_F4,
 *             to be compatible with rsa->e from openssl,
 *             the pubExp should be BIG-ENDIAN like [0~3] = {0x00,0x01,0x00,0x01}
 * [IN]mod_N: modulus ,length should be bitLen_N>>3 bytes
 * [IN]bitLen_N: bit length of mod_N
 * [IN]from: signature to be verified, always be bitLen_N>>3 bytes length
 * [OUT]to: clear text after public decryption
 * Return value:
 *   Bytes length of clear data in "to" buffer, MAX is  bitLen_N>>3-11
 */
int RSA_PubDec(unsigned char *pubExp, unsigned char *mod_N,
		int bitLen_N, unsigned char *from, unsigned char *to);

/*
 * Decrypt using public key with no padding, Means verification
 * Parameter:
 * [IN]pubExp: public expoenent, should be RSA_3 or RSA_F4,
 *             to be compatible with rsa->e from openssl,
 *             the pubExp should be BIG-ENDIAN like [0~3]={0x00,0x01,0x00,0x01}
 * [IN]mod_N: modulus ,length should be bitLen_N>>3 bytes
 * [IN]bitLen_N: bit length of mod_N
 * [IN]from: signature to be verified, always be bitLen_N>>3 bytes length
 * [OUT]to: clear text after public decryption
 * Return value:
 *   Bytes length of clear data in "to" buffer, MAX is  bitLen_N>>3
 */
int RSA_PubDec_No_Pad(unsigned char *pubExp, unsigned char *mod_N,
		int bitLen_N, unsigned char *from, unsigned char *to);

/*
 * Encrypt using public key with pkcs1 padding.
 * Parameter:
 * [IN]pubExp: public expoenent,should be RSA_3 or RSA_F4,
 *             to be compatible with rsa->e from openssl,
 *             the pubExp should be BIG-ENDIAN like [0~3] = {0x00,0x01,0x00,0x01}
 * [IN]mod_N: modulus ,length should be bitLen_N>>3 bytes
 * [IN]bitLen_N: bit length of mod_N
 * [IN]from: clear text to be signed, MAX length is bitLen_N>>3-11
 *           due to will be padded using pkcs1
 * [IN]int flen: data length of "from" buffer, MAX is  bitLen_N>>3-11
 * [OUT]to: cipher data, always be bitLen_N>>3 bytes length
 * Return value:
 *   true: encrypt success
 *   false: encrypt failed
 */
int RSA_PubEnc(unsigned char *pubExp, unsigned char *mod_N, int bitLen_N,
		unsigned char *from, int flen, unsigned char *to);

/*
 * Encrypt using public key with no padding.
 * Parameter:
 * [IN]pubExp: public expoenent,should be RSA_3 or RSA_F4,
 *             to be compatible with rsa->e from openssl,
 *             the pubExp should be BIG-ENDIAN like [0~3]={0x00,0x01,0x00,0x01}
 * [IN]mod_N: modulus ,length should be bitLen_N>>3 bytes
 * [IN]bitLen_N: bit length of mod_N
 * [IN]from: clear text to be signed, MAX length is bitLen_N>>3
 * [IN]int flen: data length of "from" buffer, MAX is  bitLen_N>>3
 * [OUT]to: cipher data, always be bitLen_N>>3 bytes length
 * Return value:
 *   true: encrypt success
 *   false: encrypt failed
 */
int RSA_PubEnc_No_Pad(unsigned char *pubExp, unsigned char *mod_N,
		int bitLen_N, unsigned char *from, int flen, unsigned char *to);

/*
 * Decrypt using private key with pkcs1 padding
 * Parameter:
 * [IN]prvExp: private exponent ,length should be bitLen_N>>3 bytes
 * [IN]mod_N: modulus ,length should be bitLen_N>>3 bytes
 * [IN]bitLen_N: bit length of mod_N
 * [IN]from: cipher data to be decrypted, always be bitLen_N>>3 bytes length
 * [OUT]to: clear text after public decryption
 * Return value:
 *   Bytes length of clear data in "to" buffer, MAX is  bitLen_N>>3-11
 */
int RSA_PrvDec(unsigned char *prvExp, unsigned char *mod_N, int bitLen_N,
		unsigned char *from, unsigned char *to);

/*
 * Decrypt using private key with no padding
 * Parameter:
 * [IN]prvExp: private exponent ,length should be bitLen_N>>3 bytes
 * [IN]mod_N: modulus ,length should be bitLen_N>>3 bytes
 * [IN]bitLen_N: bit length of mod_N
 * [IN]from: cipher data to be decrypted, always be bitLen_N>>3 bytes length
 * [OUT]to: clear text after public decryption
 * Return value:
 *   Bytes length of clear data in "to" buffer, MAX is  bitLen_N>>3-11
 */
int RSA_PrvDec_No_Pad(unsigned char *prvExp, unsigned char *mod_N,
		int bitLen_N, unsigned char *from, unsigned char *to);

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
 */

#include <security/sprd_verify.h>
#include <security/sprd_rsa.h>
#include <security/sprdsec_header.h>
#include <security/sec_string.h>
#include <security/sprd_sha.h>
#include <security/sec_common.h>
#if defined(CONFIG_WHALE2) || defined(CONFIG_IWHALE2)
#include <security/sprd_crypt_r1p0.h>
#endif
#include <security/pk1.h>
#include <security/sec_efuse_api.h>
#ifdef PKCS1_PSS_FLAG
#include <security/sprd_crypto_r3p0.h>
#define SPL_RSA_KEY_LEN 256
#endif

//#define SEC_DEBUG

#ifdef SEC_DEBUG
#define secf(fmt, args...) do { printf("%s(): ", __func__); printf(fmt, ##args); } while (0)
#else
#define secf(fmt, args...)
#endif

#define NON_TRUSTED_VERSION_MAX 223
#define TRUSTED_FIRMWARE        1
#define NON_TRUSTED_FIRMWARE    0
#define SEC_VERSION_INIT_VALUE  0x1234 // trust version init value
#define VERSION_INIT_VALUE      0xFFFF // non trust version init value
#define CHECK_BINARY_NUM        10

static uint32_t Trusted_rollback_version = SEC_VERSION_INIT_VALUE;
static uint32_t Non_Trusted_rollback_version = VERSION_INIT_VALUE;
static uint32_t Trusted_update_version[CHECK_BINARY_NUM] = {0};
static uint32_t Non_Trusted_update_version[CHECK_BINARY_NUM] = {0};
static uint32_t Trusted_update_index = 0;
static uint32_t Non_Trusted_update_index = 0;

void dumpHex(const char *title, uint8_t * data, int len)
{
	int i, j;
	int N = len / 16 + 1;
	secf("%s\n", title);
	secf("dumpHex:%d bytes", len);
	for (i = 0; i < N; i++) {
		secf("\r\n");
		for (j = 0; j < 16; j++) {
			if (i * 16 + j >= len)
				goto end;
			secf("%02x", data[i * 16 + j]);
		}
	}

end:
	secf("\r\n");
	return;
}

void cal_sha256(uint8_t * input, uint32_t bytes_num, uint8_t * output)
{

	if ((NULL != input) && (NULL != output)) {
		sha256_csum_wd(input, bytes_num, output, 0);
	} else {
		secf("\r\tthe pointer is error,pls check it\n");
	}
}

void sprd_update_swVersion(void)
{
	uint32_t i;
	uint32_t secure_update_version = 0;
	if(Trusted_update_index)//binary version is changed
	{
		secure_update_version = Trusted_update_version[0];
		for(i=1;i<Trusted_update_index;i++)
		{
			if(secure_update_version != Trusted_update_version[i])
			{
				secf("\r\sec rollback version not unified\n");
				return;
			}
		}
		//if(check_rollback_version(secure_update_version))
		if(secure_update_version>Trusted_rollback_version)
			sprd_set_version(SW_VERSION_COUNTER1,secure_update_version);
		Trusted_update_index = 0;
		Trusted_rollback_version = 0;
	}
}

bool sprd_anti_rollback(uint32_t certtype, uint32_t certversion)
{
	secf("image type = %d\n", certtype);
	if (certtype == TRUSTED_FIRMWARE) {
		if (Trusted_rollback_version == SEC_VERSION_INIT_VALUE){
			sprd_get_version(SW_VERSION_COUNTER1 ,&Trusted_rollback_version);
			secf("read efuse version: 0X%x\n", Trusted_rollback_version);
		}
		secf("Trusted_rollback_version = 0X%x  certversion = 0X%x\n",
				Trusted_rollback_version, certversion);
		if (certversion < Trusted_rollback_version) {
			secf("SEC ANTI_ROLLBACK ERR version = 0X%x\n", certversion);
			return false;
		} else {
			Trusted_update_version[Trusted_update_index] = certversion;
			Trusted_update_index++;
		}
	} else if (certtype == NON_TRUSTED_FIRMWARE) {
		if (Non_Trusted_rollback_version == VERSION_INIT_VALUE) {
			sprd_get_version(SW_VERSION_COUNTER2,&Non_Trusted_rollback_version);
			secf("read efuse version: %d\n", Non_Trusted_rollback_version);
		}
		secf("Non_Trusted_rollback_version = %d  certversion = %d\n",
				Non_Trusted_rollback_version, certversion);
		if ((certversion < Non_Trusted_rollback_version) ||
				(certversion > NON_TRUSTED_VERSION_MAX)) {
			secf("NOSEC ANTI_ROLLBACK ERR version = %d\n", certversion);
			return false;
		} else {
			Non_Trusted_update_version[Non_Trusted_update_index] = certversion;
			Non_Trusted_update_index++;
		}
	} else {
		secf("image type mismatch!! \n");
		return false;
	}
	return true;
}

#ifndef PKCS1_PSS_FLAG
bool sprd_verify_cert(uint8_t * hash_key_precert, uint8_t * hash_data, uint8_t * certptr)
{
	bool ret = false;

	uint8_t certtype = *certptr;

	uint8_t to[RSA_KEY_BYTE_LEN_MAX]; // store RSA_PubDec  result
	uint8_t temphash_data[HASH_BYTE_LEN];
	secf("cert type: %d\n",certtype);
	sec_memset(to, 0, RSA_KEY_BYTE_LEN_MAX);
	if ((certtype == CERTTYPE_CONTENT) || (certtype == CERTTYPE_KEY)) {

		if (certtype == CERTTYPE_KEY) {

			sprd_keycert *curcertptr = (sprd_keycert *) certptr;

			cal_sha256((uint8_t *) & (curcertptr->pubkey), SPRD_RSAPUBKLEN, temphash_data);

			if (sec_memcmp(hash_data, curcertptr->hash_data, HASH_BYTE_LEN)
					|| sec_memcmp(hash_key_precert, temphash_data, HASH_BYTE_LEN)
			   ) {
				secf("cmp hash of pubk diffent\r\n");
				return false;
			}

			RSA_PubDec((uint8_t *) & (curcertptr->pubkey.e),
					curcertptr->pubkey.mod, curcertptr->pubkey.keybit_len,
					curcertptr->signature, to);

			if (!sec_memcmp(curcertptr->hash_data, to, KEYCERT_HASH_LEN)) {
				secf("\nRSA verify Success\n");
			} else {
				secf("\nRSA verify err\n");
				return false;
			}
			ret = sprd_anti_rollback(curcertptr->type,curcertptr->version);
		}

		else if(certtype ==  CERTTYPE_CONTENT) {		//certtype is content

			sprd_contentcert *curcertptr = (sprd_contentcert *) certptr;

			cal_sha256((uint8_t *) & (curcertptr->pubkey), SPRD_RSAPUBKLEN, temphash_data);

			if (sec_memcmp(hash_data, curcertptr->hash_data, HASH_BYTE_LEN)
					|| sec_memcmp(hash_key_precert, temphash_data, HASH_BYTE_LEN)
			   ) {
				secf("cmp hash key diffent\r\n");
				return false;
			}

			int len = RSA_PubDec((uint8_t *) & (curcertptr->pubkey.e),
					curcertptr->pubkey.mod, curcertptr->pubkey.keybit_len,
					curcertptr->signature, to);

			if (!sec_memcmp(curcertptr->hash_data, to, len)) {
				secf("\nRSA verify Success\n");
			} else {
				secf("\nRSA verify Failed\n");
				return false;
			}
			ret = sprd_anti_rollback(curcertptr->type,curcertptr->version);
		}

	} else {
		secf("invalid cert type %d!!", certtype);
		ret = false;
	}

	return ret;
}
#else
bool sprd_verify_cert(uint8_t * hash_key_precert, uint8_t * hash_data, uint8_t * certptr)
{
	bool ret = false;

	uint8_t certtype = *certptr;
	uint8_t to[RSA_KEY_BYTE_LEN_MAX]; // store RSA_PubDec  result
	uint8_t temphash_data[HASH_BYTE_LEN];
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;
	sprd_rsa_pubkey_t pubkey;
	sprd_rsa_padding_t padding;
	int32_t result;
	uint8_t certhash[HASH_BYTE_LEN] = {0};

	unsigned char key_e[SPL_RSA_KEY_LEN];
	sec_memset(key_e, 0, SPL_RSA_KEY_LEN);

	padding.type = SPRD_RSASSA_PKCS1_PSS_MGF1;
	padding.pad.rsassa_pss.type = SPRD_CRYPTO_HASH_SHA256;
	padding.pad.rsassa_pss.mgf1_hash_type = SPRD_CRYPTO_HASH_SHA256;
	padding.pad.rsassa_pss.salt_len = 32;

	secf("cert type: %d\n",certtype);
	if ((certtype == CERTTYPE_CONTENT) || (certtype == CERTTYPE_KEY)) {

		if (certtype == CERTTYPE_KEY) {

			sprd_keycert *curcertptr = (sprd_keycert *) certptr;

			cal_sha256((uint8_t *) & (curcertptr->pubkey), SPRD_RSAPUBKLEN, temphash_data);

			if (sec_memcmp(hash_data, curcertptr->hash_data, HASH_BYTE_LEN)
					|| sec_memcmp(hash_key_precert, temphash_data, HASH_BYTE_LEN)
			   ) {
				secf("cmp hash of pubk diffent\r\n");
				return false;
			}
			sec_memcpy(key_e + (SPL_RSA_KEY_LEN-4),  (uint8_t *) & (curcertptr->pubkey.e), 4);
			pubkey.n = curcertptr->pubkey.mod;
			pubkey.n_len = (curcertptr->pubkey.keybit_len) >> 3;
			pubkey.e = key_e;
			pubkey.e_len = SPL_RSA_KEY_LEN;

			cal_sha256(curcertptr->hash_data, KEYCERT_HASH_LEN, certhash);
			err = sprd_rsa_verify((const sprd_rsa_pubkey_t*)(&pubkey),
					certhash, HASH_BYTE_LEN,
					(const uint8_t*)(curcertptr->signature), pubkey.n_len,
					padding, &result);

			if (err != SPRD_CRYPTO_SUCCESS) {
				secf("\nRSA verify err fail(%08x)\n", err);
				return false;
			}

			if (result != SPRD_VERIFY_SUCCESS) {
				secf("\nRSA verify err result(%08x)\n", result);
				return false;
			}

			secf("\nRSA verify Success\n");
			ret = sprd_anti_rollback(curcertptr->type,curcertptr->version);
		}

		else if(certtype ==  CERTTYPE_CONTENT) {             //certtype is content

			sprd_contentcert *curcertptr = (sprd_contentcert *) certptr;

			cal_sha256((uint8_t *) & (curcertptr->pubkey), SPRD_RSAPUBKLEN, temphash_data);

			if (sec_memcmp(hash_data, curcertptr->hash_data, HASH_BYTE_LEN)
					|| sec_memcmp(hash_key_precert, temphash_data, HASH_BYTE_LEN)
			   ) {
				secf("cmp hash key diffent\r\n");
				return false;
			}
			sec_memcpy(key_e + (SPL_RSA_KEY_LEN-4),  (uint8_t *) & (curcertptr->pubkey.e), 4);
			pubkey.n = curcertptr->pubkey.mod;
			pubkey.n_len = (curcertptr->pubkey.keybit_len) >> 3;
			pubkey.e = key_e;
			pubkey.e_len = SPL_RSA_KEY_LEN;

			cal_sha256(curcertptr->hash_data, CNTCERT_HASH_LEN, certhash);
			err = sprd_rsa_verify((const sprd_rsa_pubkey_t*)(&pubkey),
					certhash, HASH_BYTE_LEN,
					(const uint8_t*)(curcertptr->signature), pubkey.n_len,
					padding, &result);

			if (err != SPRD_CRYPTO_SUCCESS) {
				secf("\nRSA verify err fail(%08x)\n", err);
				return false;
			}

			if (result != SPRD_VERIFY_SUCCESS) {
				secf("\nRSA verify err result(%08x)\n", result);
				return false;
			}

			secf("\nRSA verify Success\n");
			ret = sprd_anti_rollback(curcertptr->type,curcertptr->version);
		}

	} else {
		secf("invalid cert type %d!!", certtype);
		ret = false;
	}

	return ret;
}
#endif

/*
 *  uint8_t *hash_key_precert: hash of of pub key in pre cert or OTP, used to verify the pub key in current image
 *  uint8_t *imgbuf: current image need to verify
 */
uint8_t *sprd_get_sechdr_addr(uint8_t * buf)
{
	if (NULL == buf) {
		secf("\r\t input of get_sechdr_Addr err\n");
	}
	sys_img_header *imghdr = (sys_img_header *) buf;
	uint8_t *sechdr = buf + imghdr->mImgSize + sizeof(sys_img_header);
	return sechdr;
}

uint8_t *sprd_get_code_addr(uint8_t * buf)
{
	sprdsignedimageheader *sechdr_addr = (sprdsignedimageheader *) sprd_get_sechdr_addr(buf);
	uint8_t *code_addr = buf + sechdr_addr->payload_offset;
	return code_addr;
}

uint8_t *sprd_get_cert_addr(uint8_t * buf)
{
	sprdsignedimageheader *sechdr_addr = (sprdsignedimageheader *) sprd_get_sechdr_addr(buf);
	uint8_t *cert_addr = buf + sechdr_addr->cert_offset;
	return cert_addr;
}

bool sprd_verify_img(uint8_t * hash_key_precert, uint8_t * imgbuf)
{
	sprdsignedimageheader *imghdr = (sprdsignedimageheader *) sprd_get_sechdr_addr(imgbuf);
	uint8_t *code_addr = sprd_get_code_addr(imgbuf);
	uint8_t soft_hash_data[HASH_BYTE_LEN];

	cal_sha256(code_addr, imghdr->payload_size, soft_hash_data);
	uint8_t *curcertptr = sprd_get_cert_addr(imgbuf);

	bool result = sprd_verify_cert(hash_key_precert, (uint8_t *) soft_hash_data, curcertptr);

	return result;
}

void sprd_get_hash_key(uint8_t * load_buf,uint8_t *hash_key)
{
	sprd_keycert *certtype = (sprd_keycert *)sprd_get_cert_addr((uint8_t *)load_buf);
	sec_memcpy(hash_key, certtype->hash_key, HASH_BYTE_LEN);
}

/*
 * function for dencrypt use aes
 */
/*this AES_KEY  only for test ,in the product ,it will change to read the efuse to get the aes key*/
#ifdef CONFIG_SOC_IWHALE2
void sprd_aes_dencrypt(uint8_t *img_buf)
{

	uint8_t AES_KEY[32] = { 0x57,0x70,0x44,0x3b,0x21,0xaa,0xaa,0x9e,0x8e,0xad,0x14,0x35,0xde,0x31,0xda,0x77, \
	                        0xfe,0x86,0x1d,0x5a,0xb1,0xf1,0x9a,0x8d,0xb4,0xd7,0xed,0xed,0x4c,0x15,0x2a,0x9d};
	/*this block is ready for aes iv*/
	uint8_t iv_enc[16];
	sys_img_header *img_h = (sys_img_header*)img_buf;
	sec_memcpy(iv_enc,img_h->reserved,16);
	uint32_t magic = img_h->mMagicNum;
	uint32_t imgsize = img_h->mImgSize;
	*(uint32_t*)&iv_enc[8] = *(uint32_t*)&iv_enc[8]^magic;
	*(uint32_t*)&iv_enc[12] = *(uint32_t*)&iv_enc[12]^imgsize;

	uint32_t plaintext_len = 0;
	uint32_t ciphertext_len = img_h->mImgSize;
	uint8_t *ciphertext = img_buf + sizeof(sys_img_header);
	uint8_t *plaintext = img_buf + sizeof(sys_img_header);

	AES_CBC_Dec(ciphertext,ciphertext_len,plaintext,&ciphertext_len,AES_KEY,32,iv_enc,16);
}
#endif

SecBoot_Result_Ret sprd_secure_check(uint8_t * current_img_addr,uint8_t * data_header)
{

	/*get current image's hash key & verify the downloading img */
	uint8_t *hash_key_next = NULL;
	uint8_t hash_key[HASH_BYTE_LEN];
	sec_memset(hash_key, 0, HASH_BYTE_LEN);
	sprd_get_hash_key(current_img_addr,hash_key);    // becarefull!    in chipram the firt parameter is IRAM,in uboot the first is uboot load addr

	hash_key_next = hash_key;

	/*
	 * add this block for aes dencrypt*/
	sys_img_header *img_h = NULL;
	img_h =  (sys_img_header*)data_header;
	uint8_t tmp[16];
	sec_memset(tmp,0,16);
#if 0
	sprd_keycert *certtype = (sprd_keycert *) sprd_get_cert_addr(data_header);

	if (CERTTYPE_KEY == certtype->certtype){
		sprd_get_hash_key(IRAM_BEGIN,hash_key);
		hash_key_next = hash_key;

	}else{
		hash_key_next = NULL;
	}
#endif
	if (false == sprd_verify_img(hash_key_next, data_header)) {
		secf("\r\t sprd_secure_check err\n");
		//while (1) ;
		return SECBOOT_VERIFY_FAIL;
	} else {
#ifdef CONFIG_SOC_IWHALE2
		if(sec_memcmp(img_h->reserved,tmp,16) != 0) /*this block is used for aes dencrypt*/
		{
			/*add aes dencrypt function*/
			sprd_aes_dencrypt(data_header);
			secf("sprd aes dencrypt finish\n");
			// while(1);
		}
#endif
		return SECBOOT_VERIFY_SUCCESS;
	}
}


#include <crypto/sprdrsa.h>
#include <secureboot/sprdsec_header.h>
#include <secureboot/sec_string.h>
#include <crypto/sprdsha.h>
#include <secureboot/sec_common.h>
#include <secureboot/sec_efuse_api.h>
#ifdef CONFIG_VBOOT_V2
#include "libavb.h"
#include <avb/uboot_avb_ops.h>
#include <avb/avb_sha.h>
#endif
#ifdef PKCS1_PSS_FLAG
#include <sprd_hash.h>
#include <sprd_rsa.h>
#endif
DECLARE_GLOBAL_DATA_PTR;

#define SEC_DEBUG

#ifdef SEC_DEBUG
#define secf(fmt, args...) do { printf("%s(): ", __func__); printf(fmt, ##args); } while (0)
#else
#define secf(fmt, args...)
#endif

/*####for anti-rollback######*/
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

/*####for anti-rollback end######*/
uint8_t to[RSA_KEY_BYTE_LEN_MAX] = { 0 };	// store RSA_PubDec  result

// for dat modem
#define MODEM_MAGIC           "SCI1"
#define MODEM_HDR_SIZE        12  // size of a block
#define SCI_TYPE_MODEM_BIN    1
#define SCI_TYPE_PARSING_LIB  2
#define MODEM_LAST_HDR        0x100
#define MODEM_SHA1_HDR        0x400
#define MODEM_SHA1_SIZE       20

typedef struct {
	unsigned int type_flags;
	unsigned int offset;
	unsigned int length;
} data_block_header_t;

extern fastboot_image_size;

void dumpHex(const char *title, uint8_t * data, int len)
{
	int i, j;
	int N = len / 16 + 1;
	printf("%s\n", title);
	printf("dumpHex:%d bytes", len);
	for (i = 0; i < N; i++) {
		printf("\r\n");
		for (j = 0; j < 16; j++) {
			if (i * 16 + j >= len)
				goto end;
			printf("%02x", data[i * 16 + j]);
		}
	}
end:	printf("\r\n");
	return;
}

void cal_sha256(uint8_t * input, uint32_t bytes_num, uint8_t * output)
{

	if ((NULL != input) && (NULL != output)) {
		sha256_csum_wd(input, bytes_num, output, NULL);
	} else {
		secf("\r\tthe pointer is error,pls check it\n");
	}
}

uint32_t check_rollback_version(uint32_t version)
{
	uint32_t temp = 1;
	uint32_t i;
	for(i=0;i<32;i++)
	{
		temp*=2;
		if(version == temp-1)
			return 1;
	}
	return 0;
}

void update_sec_version(void)
{
    int         i;
    uint32_t    nosecure_update_version = 0;

    if (Non_Trusted_update_index) {
        nosecure_update_version = Non_Trusted_update_version[0];
        for (i = 1;i < Non_Trusted_update_index; i++)
        {
            if (nosecure_update_version != Non_Trusted_update_version[i])
            {
                secf("\r\Nosec rollback version not unified\n");
                return;
            }
        }
        if (nosecure_update_version > Non_Trusted_rollback_version) {
            sprd_set_version(SW_VERSION_COUNTER2,nosecure_update_version);
        }
        Non_Trusted_update_index = 0;
        Non_Trusted_rollback_version = 0;
    }
}

bool sprd_anti_rollback(uint32_t certtype, uint32_t certversion)
{
    int ret = 0;
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
	 #ifdef CONFIG_NONTRUSTY_ANTIROLLBACK
		ret = sprd_get_imgversion(0, &Non_Trusted_rollback_version);
		if(!ret) {
			secf("read rpmb version: %d,ret = %d\n", Non_Trusted_rollback_version,ret);
		} else {
			secf(">>>>> Warning:read rollback version return error! ret = %d\n",ret);
			Non_Trusted_rollback_version = 0;
		}
	 #else
            sprd_get_version(SW_VERSION_COUNTER2,&Non_Trusted_rollback_version);
            secf("read efuse version: %d\n", Non_Trusted_rollback_version);
	 #endif
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

	uint8_t temphash_data[HASH_BYTE_LEN];
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
	uint8_t temphash_data[HASH_BYTE_LEN];
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;
	sprd_rsa_pubkey_t pubkey;
	sprd_rsa_padding_t padding;
	int32_t result;
	uint8_t certhash[HASH_BYTE_LEN] = {0};

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

	            pubkey.n = curcertptr->pubkey.mod;
	            pubkey.n_len = (curcertptr->pubkey.keybit_len) >> 3;
	            pubkey.e = (uint8_t *) & (curcertptr->pubkey.e);
	            pubkey.e_len = 4;

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
				//dumpHex("signature",curcertptr->signature,256);
				//dumpHex("pubkey",& (curcertptr->pubkey),260);
	            pubkey.n = curcertptr->pubkey.mod;
	            pubkey.n_len = (curcertptr->pubkey.keybit_len) >> 3;
	            pubkey.e = (uint8_t *) & (curcertptr->pubkey.e);
	            pubkey.e_len = 4;

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
 *  this function compare the first four bytes in image and return 1 if equals to
 *  MODEM_MAGIC
 */
static int is_packed_modem_image(uint8_t *data)
{
	if (sec_memcmp(data, (uint8_t*)MODEM_MAGIC, sizeof(MODEM_MAGIC)))
		return 0;
	return 1;
}

/*
 *  this function parse new packed modem image and return modem code offset and length
 */
static void get_modem_info(uint8_t *data, uint32_t *code_offset, uint32_t *code_len)
{
	uint32_t offset = 0, hdr_offset = 0, length = 0;
	uint8_t hdr_buf[MODEM_HDR_SIZE << 3] = {0};
	uint8_t read_len;
	uint8_t result = 0; // 0:OK, 1:not find, 2:some error occur
	data_block_header_t *hdr_ptr = NULL;

	read_len = sizeof(hdr_buf);
	sec_memcpy(hdr_buf, data, read_len);

    do {
      if (!hdr_offset) {
        if (memcmp(hdr_buf, MODEM_MAGIC, sizeof(MODEM_MAGIC))) {
          result = 2;
          secf("old image format!\n");
          break;
        }

        hdr_ptr = (data_block_header_t *)hdr_buf + 1;
        hdr_offset = MODEM_HDR_SIZE;
      } else {
        hdr_ptr = (data_block_header_t *)hdr_buf;
      }

      data_block_header_t* endp
          = (data_block_header_t*)(hdr_buf + sizeof hdr_buf);
      int found = 0;
      while (hdr_ptr < endp) {
        uint32_t type = (hdr_ptr->type_flags & 0xff);
        if (SCI_TYPE_MODEM_BIN == type) {
          found = 1;
          break;
        }

        /*  There is a bug (622472) in MODEM image generator.
         *  To recognize wrong SCI headers and correct SCI headers,
         *  we devise the workaround.
         *  When the MODEM image generator is fixed, remove #if 0.
         */
#if 0
        if (hdr_ptr->type_flags & MODEM_LAST_HDR) {
          result = 2;
          MODEM_LOGE("no modem image, error image header!!!\n");
          break;
        }
#endif
        hdr_ptr++;
      }
      if (!found) {
        result = 2;
        secf("no MODEM exe found in SCI header!");
      }

      if (result != 1) {
        break;
      }
    } while (1);

    if (!result) {
      offset = hdr_ptr->offset;
      if (hdr_ptr->type_flags & MODEM_SHA1_HDR) {
        offset += MODEM_SHA1_SIZE;
      }
      length = hdr_ptr->length;
    }

	*code_offset = offset;
	*code_len = length;
}


/*
uint8_t *hash_key_precert: hash of of pub key in pre cert or OTP, used to verify the pub key in current image
uint8_t *imgbuf: current image need to verify
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

uint8_t *sprd_get_cert_addr(uint8_t * buf)
{
	sprdsignedimageheader *sechdr_addr = (sprdsignedimageheader *) sprd_get_sechdr_addr(buf);
	uint8_t *cert_addr = buf + sechdr_addr->cert_offset;

	return cert_addr;
}

bool sprd_verify_img(uint8_t * hash_key_precert, uint8_t * imgbuf)
{
	sprdsignedimageheader *imghdr = (sprdsignedimageheader *) sprd_get_sechdr_addr(imgbuf);
	uint8_t *code_addr = imgbuf + imghdr->payload_offset;
	if (is_packed_modem_image(code_addr)) {
		secf("the image is new packed modem image\n");
		uint32_t modem_offset = 0;
		uint32_t modem_len = 0;
		get_modem_info(code_addr, &modem_offset, &modem_len);
		secf("modem offset: %d, length: %d\n", modem_offset, modem_len);
		code_addr += modem_offset;
	}
	uint8_t soft_hash_data[HASH_BYTE_LEN] = {0};
	cal_sha256(code_addr, imghdr->payload_size, soft_hash_data);
	uint8_t *curcertptr = imgbuf + imghdr->cert_offset;

	bool result = sprd_verify_cert(hash_key_precert, (uint8_t *) soft_hash_data, curcertptr);

	return result;
}

 void sprd_get_hash_key(uint8_t * load_buf,uint8_t *hash_key)
{
	sprd_keycert *certtype = (sprd_keycert *)sprd_get_cert_addr((uint8_t *)load_buf);
	sec_memcpy(hash_key, certtype->hash_key, HASH_BYTE_LEN);
}

#ifdef CONFIG_VBOOT_V2
/*
ubootkey_from
0:from ram
1:from emmc
*/
void sprd_get_vboot_key(uint8_t * load_buf,uint8_t *key,uint32_t ubootkey_from)
{
	uint8_t vboot_signed_part[4096];
	sprd_keycert * vboot_cert = 0; // = (sprd_vboot_keycert *)sprd_get_cert_addr((uint8_t *)load_buf);
	sprdsignedimageheader * vboot_signheader = 0;

	uint8_t *sechdr_addr = 0;
	uint8_t *cert_addr = 0;

	sys_img_header *imghdr = (sys_img_header *) load_buf;
	uint64_t sechdr_offset =  (uint64_t)(imghdr->mImgSize + sizeof(sys_img_header));

	if(ubootkey_from == GET_FROM_EMMC)
	{
		secf("sechdr_offset is 0x%llx.\n", sechdr_offset);
		memset(vboot_signed_part, 0, sizeof(vboot_signed_part));
		if (0 != common_raw_read("uboot", ((uint64_t)(sizeof(vboot_signed_part))), sechdr_offset, (char*)vboot_signed_part))
		{
			errorf("read uboot partition signed part fail\n");
			return;
		}

		sechdr_addr = vboot_signed_part;
		vboot_signheader = (sprdsignedimageheader *)(vboot_signed_part);
	}
	else
	{
		secf("load_buf is 0x%x.\n", load_buf);
		secf("sechdr_offset is 0x%llx.\n", sechdr_offset);
		sechdr_addr = (load_buf + sechdr_offset);
		secf("sechdr_addr is 0x%x.\n", sechdr_addr);

		vboot_signheader = (sprdsignedimageheader *)(sechdr_addr);
	}

	cert_addr = sechdr_addr + (vboot_signheader->cert_offset - sechdr_offset);

	secf("sechdr_addr: 0x%llx. cert_addr: 0x%llx. cert_addr: 0x%llx. cert_addr: 0x%x. \n", sechdr_addr, cert_addr, (uint64_t)cert_addr, (uint32_t)cert_addr);
	secf("sechdr_offset is 0x%llx, sechdr_addr->cert_offset is 0x%llx.\n", sechdr_offset, vboot_signheader->cert_offset);

	vboot_cert = (sprd_keycert *)cert_addr;
	dumpHex("cert_key", vboot_cert->hash_key, SPRD_RSA4096PUBK_HASHLEN);

	sec_memcpy(key, vboot_cert->hash_key, SPRD_RSA4096PUBK_HASHLEN);
}
#endif

void sprd_get_pubk(uint8_t *load_buf,uint8_t *pubk)
{
	sprd_keycert *certtype = (sprd_keycert*)sprd_get_cert_addr((uint8_t*)load_buf);
	sec_memcpy(pubk, (uint8_t*)&certtype->pubkey, sizeof(sprd_rsapubkey));
}
void sprd_secure_check(uint8_t * current_img_addr,uint8_t * data_header)
{

	/*get current image's hash key & verify the downloading img */
	uint8_t *hash_key_next = NULL;
	uint8_t hash_key[HASH_BYTE_LEN];
	sec_memset(hash_key, 0, HASH_BYTE_LEN);
	sprd_get_hash_key(current_img_addr,hash_key);    // becarefull!    in chipram the firt parameter is IRAM,in uboot the first is uboot load addr

	hash_key_next = hash_key;
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
		while (1) ;
	}
}

void sprd_dl_check(uint8_t * hash,uint8_t * data_header)
{

	/*get current image's hash key & verify the downloading img */
	uint8_t *hash_key_next = NULL;
	uint8_t hash_key[HASH_BYTE_LEN];
	sec_memset(hash_key, 0, HASH_BYTE_LEN);
	//sprd_get_hash_key(current_img_addr,hash_key);    // becarefull!    in chipram the firt parameter is IRAM,in uboot the first is uboot load addr

	hash_key_next = hash;

	if (false == sprd_verify_img(hash_key_next, data_header)) {
		secf("\r\t sprd_secure_check err\n");
		while (1) ;
	}
}

#ifdef CONFIG_VBOOT_V2
// to check hash in image header of vbmeta.img porting from
// emmc_boot.c int8_t sprd_hash_check(uint8_t *header)
int8_t check_sprdimgheader(uint8_t *header, uint8_t *payload)
{
    uint8_t         *hash_temp = NULL;
    sys_img_header  *img_header = (sys_img_header *)(header);
    AvbSHA256Ctx     sha256_ctx;

    //dumpHex("vbmeta footer", header, 512);
    //dumpHex("vbmeta payload", payload, 512);
    if (IMG_BAK_HEADER == img_header->mMagicNum) {
        avb_sha256_init(&sha256_ctx);
        avb_sha256_update(&sha256_ctx, payload, img_header->mImgSize);
        hash_temp = avb_sha256_final(&sha256_ctx);
        if (0 == memcmp(img_header->mPayloadHash, hash_temp, 32))
            return 0;
        else
            return -1;
    } else {
        return -1;
    }
}

void sprd_dl_vboot_verify(uint8_t *name,uint8_t *tocheck_name,uint8_t * header,uint8_t *code)
{
    uint8_t    pubk[SPRD_RSAPUBKLEN] = {0};
    uint8_t    hash[HASH_BYTE_LEN] = {0};
    int8_t     vb_ret = 0;
    uint32_t   offset = VBMETA_PARTITION_MAX_SIZE - sizeof(sys_img_header);
    uint8_t   *payload = header;

    secf("enter use partition name: %s . to check partition_name: %s. \n", name, tocheck_name);
    if (name) {
        if (strcmp("fdl2",name) == 0) {
            avb_ops_new_for_download();
            sprd_dl_secure_vboot_prepare();
            if (strcmp("vbmeta",tocheck_name) == 0) {
                secf("check vbmeta image.\n");
                // check dual backup hash for vbmeta.img
                if (check_sprdimgheader(header + offset, payload) == 0) {
                    vb_ret = avb_check_vbmeta(header, VBMETA_PARTITION_MAX_SIZE);
                } else {
                    secf("error:check dual backup hash failed for vbmeta.img.\n");
                    vb_ret = -1;
                }
            } else {
                vb_ret = avb_check_image(tocheck_name);
            }
            if (vb_ret != 0) {
                secf("check image failed. vb_ret = %d\n", vb_ret);
                while(1);
            }
        }
    }
}

void sprd_fb_secure_vboot_verify(uint8_t *name,uint8_t *partition_name,uint8_t * header,uint8_t *code)
{
    uint8_t           pubk[SPRD_RSAPUBKLEN] = {0};
    uint8_t           hash[HASH_BYTE_LEN] = {0};
    uint32_t          offset = VBMETA_PARTITION_MAX_SIZE - sizeof(sys_img_header);
    uint8_t          *payload = header;
    sys_img_header   *img_header = (sys_img_header *)(header + offset);

    secf("enter use partition name: %s . to check partition_name: %s. \n",name, partition_name);
    if (name && (strcmp("uboot", name) == 0)) {
        if (partition_name && (strcmp("vbmeta", partition_name) == 0)) {
            secf("check vbmeta image.\n");
            // check dual backup hash for vbmeta.img
            if (check_sprdimgheader(header + offset, payload) != 0) {
                secf("error:check dual backup hash failed for vbmeta.img.\n");
                while (1);
            }
            // header+sizeof(sys_img_header) will not be aigned to 4K for tos, so copy to gd->vbmeta_img_base
            memcpy(gd->vbmeta_img_base, header, img_header->mImgSize);
            sprd_fb_secure_vboot_prepare(partition_name, gd->vbmeta_img_base,
                                         gd->vbmeta_img_base, img_header);
        } else {
            // prepare verify infomation
            sprd_fb_secure_vboot_prepare(partition_name, header, gd->vbmeta_img_base, (sys_img_header*)header);
        }
        uboot_vboot_verify_img((VbootVerifyInfo*)vboot_verify_info, sizeof(VbootVerifyInfo));
    }
}
#endif

void sprd_dl_verify(uint8_t *name,uint8_t * header,uint8_t *code)
{
	uint8_t pubk[SPRD_RSAPUBKLEN] = {0};
	uint8_t hash[HASH_BYTE_LEN] = {0};

	secf("name: %s enter\r\n",name);
	if(name){/*splloader is spl partiton, uboot is uboot partition which img the pubk hash stored*/
		if(strcmp("splloader",name) == 0 || strcmp("fdl1",name) == 0){
		sprd_secure_check(IRAM_BEGIN,header); /*add first param*/
		}else if(strcmp("fdl2",name) == 0){
			sprd_secure_check((CONFIG_SYS_TEXT_BASE - 0x200),header);// first para is the addr
		}else if(strcmp("splloader0",name) == 0){
			/*if secboot is enable, the romcode will verify fdl1's pubk,sectool sign spl and fdl1 use the same pubkkey,so wo can use the pubk's hash to verify spl's pubk*/
			sprd_get_pubk(IRAM_BEGIN, pubk);
			cal_sha256(pubk, SPRD_RSAPUBKLEN, hash);
			sprd_dl_check(hash,header);
		}else if(strcmp("uboot",name) == 0){
			sprd_secure_check(CONFIG_SYS_TEXT_BASE - 0x200,header); //for fastboot
		}


	}
}

void sprd_fb_secure_verify(uint8_t *name,uint8_t * header,uint8_t *code)
{
	uint8_t pubk[SPRD_RSAPUBKLEN] = {0};
	uint8_t hash[HASH_BYTE_LEN] = {0};
	uint8_t ret = 1;
	sys_img_header *imghdr;
  uint32_t i;

	secf("name: %s enter\r\n",name);
	if(name){/*splloader is spl partiton, uboot is uboot partition which img the pubk hash stored*/
#ifdef TOS_TRUSTY
		secboot_param_set(header,img_verify_info_tos);
#else
		secboot_param_set(header,&img_verify_info);
#endif
		if(strcmp("splloader",name) == 0 || strcmp("fdl1",name) == 0){
#ifdef TOS_TRUSTY
		img_verify_info_tos->pubkeyhash = (uint8_t*)(gd->arg_start_base+PAGE_ALIGN);
		sprd_get_hash_key(IRAM_BEGIN,img_verify_info_tos->pubkeyhash);
#else
		if(0 !=common_raw_read("splloader",(uint64_t)SPL_IMAGE_SIZE, (uint64_t)0, (unsigned char *)(header+fastboot_image_size)))
			secf("splloader read error");
		sprd_get_hash_key((uint8_t *)(header+fastboot_image_size),img_verify_info.pubkeyhash);
#endif
		}else if(strcmp("fdl2",name) == 0|| strcmp("uboot",name) == 0){
#ifdef TOS_TRUSTY
			img_verify_info_tos->pubkeyhash = (uint8_t*)(gd->arg_start_base+PAGE_ALIGN);
			sprd_get_hash_key((CONFIG_SYS_TEXT_BASE - 0x200),img_verify_info_tos->pubkeyhash);
#else
			sprd_get_hash_key((CONFIG_SYS_TEXT_BASE - 0x200),img_verify_info.pubkeyhash);
#endif
		}else if(strcmp("splloader0",name) == 0){
#ifdef TOS_TRUSTY
        if (header) {
				imghdr =  (sys_img_header *) header;
				if (imghdr->mMagicNum != IMG_BAK_HEADER ) {
					secf("Invalid image");
					while(1);
				}
				for (i = 0; i < 32; i++) {
					if (imghdr->mPayloadHash[i] != 0) {
						secf("Invalid image");
						while(1);
					}
				}
			} else 	{
				secf("Image header empty");
				while(1);
			}

			img_verify_info_tos->pubkeyhash = (uint8_t*)(gd->arg_start_base+PAGE_ALIGN);
			memset(img_verify_info_tos->pubkeyhash,0xff,HASH_BYTE_LEN);
#else
			memset(img_verify_info.pubkeyhash,0xff,HASH_BYTE_LEN);
#endif
		}
#ifdef TOS_TRUSTY
		ret = uboot_verify_img((imgToVerifyInfo*)img_verify_info_tos,sizeof(imgToVerifyInfo));
		while(ret);
#else
		uboot_verify_img(&img_verify_info,sizeof(imgToVerifyInfo));
#endif
	}
}


void sprd_calc_hbk(void)
{
    unsigned int t_readValue = 0;
    char  *boot_mode_type_str;
    sys_img_header  *imghdr = NULL;

    boot_mode_type_str = getenv("bootmode");
    if (NULL != boot_mode_type_str) {
        if (!strncmp(boot_mode_type_str, "cali", 4)) {
            /**read spl image**/
#ifdef TOS_TRUSTY
            img_verify_info_tos->img_addr= (uint8_t*)(gd->arg_start_base+PAGE_ALIGN);
            imghdr = (sys_img_header *)IRAM_BEGIN;
            if (imghdr->mMagicNum != IMG_BAK_HEADER ) {
                printf("Invalid spl image, return");
                return;
            }
            img_verify_info_tos->img_len = (uint64_t)(imghdr->mImgSize + SYS_HEADER_SIZE + CERT_SIZE);
            img_verify_info_tos->flag = SPRD_FLAG;
            printf("spl imgsize = 0x%x\n", img_verify_info_tos->img_len);
            memcpy((unsigned char *)img_verify_info_tos->img_addr, IRAM_BEGIN,
                    img_verify_info_tos->img_len);
            printf("sprd_calc_hbk p1:%x, p2:%x,P3:%x\n",img_verify_info_tos->img_addr,img_verify_info_tos->img_len,img_verify_info_tos->flag);
            uboot_get_hbk(img_verify_info_tos,sizeof(imgToVerifyInfo));
#else
            //memcpy((unsigned char *)img_verify_info.img_addr,IRAM_BEGIN,SPL_IMAGE_SIZE);
            common_raw_read("splloader", (uint64_t)SPL_IMAGE_SIZE, (uint64_t)0, (unsigned char *)img_verify_info.img_addr);
            img_verify_info.img_len = SPL_IMAGE_SIZE;
            img_verify_info.flag = SPRD_FLAG;
            printf("sprd_calc_hbk p1:%llx, p2:%llx,P3:%x\n",img_verify_info.img_addr,img_verify_info.img_len,img_verify_info.flag);
            uboot_get_hbk(&img_verify_info,sizeof(imgToVerifyInfo));
#endif
        } else {
            printf("not in calibration mode\n");
        }
    }
}


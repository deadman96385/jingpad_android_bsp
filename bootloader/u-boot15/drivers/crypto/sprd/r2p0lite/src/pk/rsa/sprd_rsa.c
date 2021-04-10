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
#include <sprd_rsa.h>
#include <pkcs1/sprd_pkcs1.h>

static uint8_t buf[SPRD_CRYPTO_RSA_BUF_SIZE] __attribute__ ((aligned(SPRD_PAL_CACHE_LINE)));

sprd_crypto_err_t
sprd_rsa_nopad(uint32_t encrypt,
		     uint8_t *key1, uint32_t key1_len,
		     uint8_t *key2, uint32_t key2_len,
		     uint8_t *in, uint32_t in_len,
		     uint8_t *out, uint32_t *out_len) {
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;
	sprd_crypto_context_t context;

	SPRD_CRYPTO_LOG_TRACE("key1 = %p, key1_len = %d!\n", key1, key1_len);
	SPRD_CRYPTO_LOG_TRACE("key2 = %p, key2_len = %d!\n", key2, key2_len);
	SPRD_CRYPTO_LOG_TRACE("in = %p, in_len = %d!\n", in, in_len);
	SPRD_CRYPTO_LOG_TRACE("out = %p, out_len = %p!\n", out, out_len);

	sprd_pal_memset(&context, 0, sizeof(sprd_crypto_context_t));
	switch (key1_len) {
	case 32:
		context.algo = encrypt == 1 ? SPRD_CRYPTO_RSA_ENC_256 : SPRD_CRYPTO_RSA_DEC_256;
		break;
	case 128:
		context.algo = encrypt == 1 ? SPRD_CRYPTO_RSA_ENC_1024 : SPRD_CRYPTO_RSA_DEC_1024;
		break;
	case 256:
		context.algo = encrypt == 1 ? SPRD_CRYPTO_RSA_ENC_2048 : SPRD_CRYPTO_RSA_DEC_2048;
		break;
	case 384:
		context.algo = encrypt == 1 ? SPRD_CRYPTO_RSA_ENC_3072 : SPRD_CRYPTO_RSA_DEC_3072;
		break;
	case 512:
		context.algo = encrypt == 1 ? SPRD_CRYPTO_RSA_ENC_4096 : SPRD_CRYPTO_RSA_DEC_4096;
		break;
	default:
		SPRD_CRYPTO_LOG_ERR("bad key len!\n");
		return SPRD_CRYPTO_LENGTH_ERR;
	}

	SPRD_CRYPTO_LOG_TRACE("algo = 0x%x context = %p\n", context.algo, &context);

	err = sprd_crypto_open(&context);
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("FAILED!\n");
		return SPRD_CRYPTO_ERROR;
	}

	sprd_pal_memset(buf, 0, key1_len);
	sprd_pal_memcpy(buf + key1_len - key2_len, key2, key2_len);

	context.continued = 0;
	context.end = 1;
	context.info.rsa.key_n = key1;
	context.info.rsa.key_eod = buf;
	context.info.rsa.key_len = key1_len;
	context.in = in;
	context.in_len = in_len;
	context.out = buf;
	context.out_len = in_len;

	sprd_pal_clean_by_vaddr(context.info.rsa.key_n, context.info.rsa.key_len);
	sprd_pal_clean_by_vaddr(context.info.rsa.key_eod, context.info.rsa.key_len);
	sprd_pal_clean_by_vaddr(context.in, context.in_len);
	sprd_pal_flush_by_vaddr(context.out, context.out_len);

	err = sprd_crypto_process(&context);
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("sprd_crypto_process return 0x%x\n", err);
		goto failed;
	}

	SPRD_CRYPTO_LOG_TRACE("waiting for polling!\n");
#ifndef R2P0LITE
	sprd_crypto_polling();
#else
	sprd_crypto_pka_polling();
#endif
	sprd_pal_invalidate_by_vaddr(context.out, context.out_len);

	if (out_len != NULL) {
		*out_len = in_len;
	}
	sprd_pal_memcpy(out, buf, in_len);

failed:
	sprd_crypto_close(&context);
	return err;
}

sprd_crypto_err_t sprd_rsa_public_encrypt(const sprd_rsa_pubkey_t *pub_key,
                      const uint8_t *src, uint32_t src_size,
                      uint8_t *dst, uint32_t *dst_size,
                      sprd_rsa_padding_t padding) {
	if (pub_key == NULL) {
		SPRD_CRYPTO_LOG_ERR("Bad pub key(%p)!\n", pub_key);
		return SPRD_CRYPTO_INVALID_KEY;
	}

	if (src == NULL || src_size == 0) {
		SPRD_CRYPTO_LOG_ERR("Bad src(%p) or src_size(%d)\n", src, src_size);
		return SPRD_CRYPTO_INVALID_ARG;
	}

	if (dst == NULL) {
		SPRD_CRYPTO_LOG_ERR("Bad dst(%p)\n", dst);
		return SPRD_CRYPTO_INVALID_ARG;
	}
	switch(padding.type) {
	case SPRD_RSA_NOPAD:
		break;

	case SPRD_RSAES_PKCS1_V1_5:
	case SPRD_RSAES_PKCS1_OAEP_MGF1:
	default:
		SPRD_CRYPTO_LOG_ERR("Bad padding type(%d)!\n", padding.type);
		return SPRD_CRYPTO_INVALID_PADDING;
	}

	return sprd_rsa_nopad(1,
			pub_key->n, pub_key->n_len,
			pub_key->e, pub_key->e_len,
			(uint8_t*)src, src_size,
			dst, dst_size);
}

sprd_crypto_err_t sprd_rsa_private_decrypt(const sprd_rsa_keypair_t *priv_key,
                      const uint8_t *src, uint32_t src_size,
                      uint8_t *dst, uint32_t *dst_size,
                      sprd_rsa_padding_t padding) {
	if (priv_key == NULL) {
		SPRD_CRYPTO_LOG_ERR("Bad priv key(%p)!\n", priv_key);
		return SPRD_CRYPTO_INVALID_KEY;
	}

	if (src == NULL || src_size == 0) {
		SPRD_CRYPTO_LOG_ERR("Bad src(%p) or src_size(%d)\n", src, src_size);
		return SPRD_CRYPTO_INVALID_ARG;
	}

	if (dst == NULL) {
		SPRD_CRYPTO_LOG_ERR("Bad dst(%p)\n", dst);
		return SPRD_CRYPTO_INVALID_ARG;
	}

	switch(padding.type) {
	case SPRD_RSA_NOPAD:
		break;

	case SPRD_RSAES_PKCS1_V1_5:
	case SPRD_RSAES_PKCS1_OAEP_MGF1:
	default:
		SPRD_CRYPTO_LOG_ERR("Bad padding type(%d)!\n", padding.type);
		return SPRD_CRYPTO_INVALID_PADDING;
	}

	return sprd_rsa_nopad(0,
			priv_key->n, priv_key->n_len,
			priv_key->d, priv_key->n_len,
			(uint8_t*)src, src_size,
			dst, dst_size);
}

sprd_crypto_err_t sprd_rsa_sign(const sprd_rsa_keypair_t *priv_key,
                      const uint8_t *dig, uint32_t dig_size,
                      uint8_t *sig, uint32_t *sig_size, sprd_rsa_padding_t padding) {
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;
	uint8_t *temp, buf[512];
	uint32_t temp_len;
	if (priv_key == NULL) {
		SPRD_CRYPTO_LOG_ERR("Bad priv key(%p)!\n", priv_key);
		return SPRD_CRYPTO_INVALID_KEY;
	}

	if (dig == NULL || dig_size <= 0) {
		SPRD_CRYPTO_LOG_ERR("Bad dig(%p) or dig_size(%d)!\n", dig, dig_size);
		return SPRD_CRYPTO_INVALID_ARG;
	}

	if (sig == NULL || sig_size == NULL || *sig_size < priv_key->n_len) {
		SPRD_CRYPTO_LOG_ERR("Bad sig(%p) or sig_size(%p)!\n", sig, sig_size);
		return SPRD_CRYPTO_INVALID_ARG;
	}

	switch(padding.type) {
	case SPRD_RSA_NOPAD:
		temp = (uint8_t*)dig;
		temp_len = dig_size;
		break;

	case SPRD_RSASSA_PKCS1_V1_5:
		temp = buf;
		temp_len = priv_key->n_len;
		err = sprd_pkcs1_v1_5_encode(dig, dig_size,
				SPRD_PKCS_1_EMSA, priv_key->n_len,
				temp, &temp_len);
		if (err != SPRD_CRYPTO_SUCCESS) {
			SPRD_CRYPTO_LOG_ERR("rsa padding encode failed(0x%x)!\n", err);
			return err;
		}
		break;

	case SPRD_RSASSA_PKCS1_PSS_MGF1:
		temp = buf;
		temp_len = priv_key->n_len;
		err = sprd_pkcs1_pss_encode(dig, dig_size,padding.pad.rsassa_pss.salt_len,
					padding.pad.rsassa_pss.type,
					padding.pad.rsassa_pss.mgf1_hash_type,
					(priv_key->n_len)*8 /*needs bitlen*/,temp, &temp_len);
		if (err != SPRD_CRYPTO_SUCCESS) {
			SPRD_CRYPTO_LOG_ERR("rsa pss padding encode failed(0x%x)!\n", err);
			return err;
		}
		break;

	default:
		SPRD_CRYPTO_LOG_ERR("Bad padding type(%d)!\n", padding.type);
		return SPRD_CRYPTO_INVALID_PADDING;
	}

	return sprd_rsa_nopad(0,
			priv_key->n, priv_key->n_len,
			priv_key->d, priv_key->n_len,
			(uint8_t*)temp, temp_len,
			sig, sig_size);
}

sprd_crypto_err_t sprd_rsa_verify(const sprd_rsa_pubkey_t *pub_key,
                      const uint8_t *dig, uint32_t dig_size,
                      const uint8_t *sig, uint32_t sig_size,
                      sprd_rsa_padding_t padding, int32_t *result) {
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;
	uint8_t temp1[512], temp2[512];
	uint32_t temp1_len, temp2_len;
	int32_t is_valid;

	if (pub_key == NULL) {
		SPRD_CRYPTO_LOG_ERR("Bad pub key(%p)!\n", pub_key);
		return SPRD_CRYPTO_INVALID_KEY;
	}

	if (dig == NULL) {
		SPRD_CRYPTO_LOG_ERR("Bad dig(%p)!\n", dig);
		return SPRD_CRYPTO_INVALID_ARG;
	}

	if (sig == NULL || sig_size <= 0) {
		SPRD_CRYPTO_LOG_ERR("Bad sig(%p) or sig_size(%d)!\n", sig, sig_size);
		return SPRD_CRYPTO_INVALID_ARG;
	}

	if (result == NULL) {
		SPRD_CRYPTO_LOG_ERR("Bad result(%p)!\n", result);
		return SPRD_CRYPTO_INVALID_ARG;
	} else {
		*result = SPRD_VERIFY_FAILED;
	}

	err = sprd_rsa_nopad(1,
			pub_key->n, pub_key->n_len,
			pub_key->e, pub_key->e_len,
			(uint8_t*)sig, sig_size,
			temp1, &temp1_len);
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("sprd_rsa_nopad failed(0x%x)!\n", err);
		return err;
	}

	switch (padding.type) {
	case SPRD_RSA_NOPAD:
		if (dig_size == 0) {
			sprd_pal_memcpy((uint8_t *)dig, temp1, temp1_len);
			*result = temp1_len;
		} else {
			if (sprd_pal_memcmp(temp1, dig, dig_size) != 0) {
				*result = SPRD_VERIFY_FAILED;
			} else {
				*result = SPRD_VERIFY_SUCCESS;
			}
		}
		err = SPRD_CRYPTO_SUCCESS;
		break;

	case SPRD_RSASSA_PKCS1_V1_5:
		temp2_len = 512;
		err = sprd_pkcs1_v1_5_decode(temp1, temp1_len,
				SPRD_PKCS_1_EMSA, pub_key->n_len,
				temp2, &temp2_len, &is_valid);
		if (err != SPRD_CRYPTO_SUCCESS || is_valid == 0) {
			SPRD_CRYPTO_LOG_ERR("rsa padding decode failed(0x%x), is_valid(%d)!\n", err, is_valid);
			*result = SPRD_VERIFY_FAILED;
			return err;
		}

		if (dig_size == 0) {
			sprd_pal_memcpy((uint8_t*)dig, temp2, temp2_len);
			*result = temp2_len;
		} else {
			if (temp2_len != dig_size || sprd_pal_memcmp(temp2, dig, dig_size) != 0) {
				SPRD_CRYPTO_LOG_ERR("temp_len(%d) is not equal dig_size(%d) or memcmp is failed\n", temp2_len, dig_size);
				*result = SPRD_VERIFY_FAILED;
			} else {
				*result = SPRD_VERIFY_SUCCESS;
			}
		}
		break;


	case SPRD_RSASSA_PKCS1_PSS_MGF1:
		err = sprd_pkcs1_pss_decode(dig, dig_size,
				temp1, temp1_len,
				padding.pad.rsassa_pss.salt_len, padding.pad.rsassa_pss.type, padding.pad.rsassa_pss.mgf1_hash_type,
				(pub_key->n_len)*8 /*needs bitlen*/, result);
		break;

	default:
		SPRD_CRYPTO_LOG_ERR("Bad padding type(%d)!\n", padding.type);
		err = SPRD_CRYPTO_INVALID_PADDING;
		break;
	}

	return err;
}

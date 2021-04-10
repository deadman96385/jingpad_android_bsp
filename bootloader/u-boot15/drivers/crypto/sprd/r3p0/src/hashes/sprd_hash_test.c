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
#include <sprd_hash.h>

sprd_crypto_err_t
sprd_hash_test_md5 (void) {
	static struct {
		const char* msg;
		const uint8_t hash[16];
	} tests[] = {//0, 128, 131, 256, 260, 5, 384 389
		{ "",//0
		  { 0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04,
		    0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901",//128
		  { 0x1b, 0x60, 0x2d, 0x20, 0x3a, 0x9c, 0x0e, 0x59,
		    0x11, 0x99, 0x64, 0x74, 0x55, 0xfe, 0x24, 0xf9 } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "012",//131
		  { 0xa4, 0xf4, 0xd8, 0x26, 0x6d, 0x39, 0xd0, 0x46,
		    0x4c, 0x66, 0xa2, 0xa6, 0x58, 0xe4, 0xdc, 0x7e } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901",//256
		  { 0x79, 0x4e, 0xc7, 0xa4, 0xda, 0x4f, 0xd5, 0x9f,
		    0x72, 0x7d, 0xbc, 0x67, 0xf2, 0x6c, 0xe9, 0x83 } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "0123",//260
		  { 0x96, 0xd8, 0x8d, 0x94, 0x64, 0x55, 0x80, 0xd1,
		    0x60, 0x10, 0x46, 0x62, 0xd0, 0x3f, 0xdd, 0x54 } },
		{ "abcde",//5
		  { 0xab, 0x56, 0xb4, 0xd9, 0x2b, 0x40, 0x71, 0x3a,
		    0xcc, 0x5a, 0xf8, 0x99, 0x85, 0xd4, 0xb7, 0x86 } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901",//384
		  { 0x65, 0x7b, 0x9b, 0x28, 0x6b, 0x77, 0x87, 0x0b,
		    0x13, 0xf4, 0x4b, 0x00, 0xa1, 0xf0, 0x9a, 0xaf } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "01234",//389
		  { 0x58, 0x9d, 0x43, 0xd6, 0x6e, 0x9c, 0x37, 0x5b,
		    0xf0, 0x41, 0xa6, 0x31, 0x9f, 0x84, 0x8b, 0xc6 } },
		{ NULL, { 0 } }
	};

	int32_t i;
	uint8_t tmp[16];
	sprd_crypto_context_t md5;

	for (i = 0; tests[i].msg != NULL; i++) {
		sprd_hash_init(SPRD_CRYPTO_HASH_MD5, &md5);
		sprd_hash_update(&md5, (const uint8_t*)tests[i].msg, (uint32_t)sprd_pal_strlen(tests[i].msg));
		sprd_hash_final(&md5, tmp);
		if (sprd_pal_memcmp(tmp, tests[i].hash, 16) != 0) {
			SPRD_CRYPTO_LOG_DEBUG("md5 test[%d] FAILED\n", i);
			return SPRD_CRYPTO_ERR_RESULT;
		}
	}

	return SPRD_CRYPTO_SUCCESS;
}

sprd_crypto_err_t
sprd_hash_test_sha1 (void) {
	static const struct {
		const char *msg;
		unsigned char hash[20];
	} tests[] = {//0, 128, 131, 256, 260, 5, 384 389
		{ "",
		  { 0xda, 0x39, 0xa3, 0xee, 0x5e, 0x6b, 0x4b, 0x0d,
		    0x32, 0x55, 0xbf, 0xef, 0x95, 0x60, 0x18, 0x90,
		    0xaf, 0xd8, 0x07, 0x09 }
		},
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901",//128
		  { 0x0a, 0xe7, 0xb7, 0x73, 0x1c, 0xeb, 0xb8, 0xba,
		    0xee, 0x6f, 0xae, 0xcb, 0xab, 0x5d, 0x3c, 0x2c,
		    0x54, 0xb9, 0x5d, 0x89 }
		},
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901",//256
		  { 0x4f, 0xb5, 0x0f, 0xe2, 0xb0, 0x02, 0x9d, 0xab,
		    0xa3, 0x81, 0x41, 0x71, 0xb7, 0x7e, 0xf8, 0x13,
		    0x6a, 0x4e, 0xd2, 0x3a }
		},
		{ NULL, { 0 } }
	};

	int32_t i;
	uint8_t tmp[20];
	sprd_crypto_context_t sha1;

	for (i = 0; tests[i].msg != NULL; i++) {
		sprd_hash_init(SPRD_CRYPTO_HASH_SHA1, &sha1);
		sprd_hash_update(&sha1, (uint8_t *)tests[i].msg, (uint32_t)sprd_pal_strlen(tests[i].msg));
		sprd_hash_final(&sha1, tmp);
		if (sprd_pal_memcmp(tmp, tests[i].hash, 20) != 0) {
			SPRD_CRYPTO_LOG_DEBUG("sha1 test[%d] FAILED\n", i);
			return SPRD_CRYPTO_ERR_RESULT;
		}
	}

	return SPRD_CRYPTO_SUCCESS;
}

sprd_crypto_err_t
sprd_hash_test_sha224 (void) {
	static const struct {
		const char *msg;
		unsigned char hash[28];
	} tests[] = {//0, 128, 131, 256, 260, 5, 384 389
		{ "",
		  { 0xd1, 0x4a, 0x02, 0x8c, 0x2a, 0x3a, 0x2b, 0xc9,
		    0x47, 0x61, 0x02, 0xbb, 0x28, 0x82, 0x34, 0xc4,
		    0x15, 0xa2, 0xb0, 0x1f, 0x82, 0x8e, 0xa6, 0x2a,
		    0xc5, 0xb3, 0xe4, 0x2f } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901",//128
		  { 0x64, 0x5b, 0x78, 0xb8, 0x96, 0x0d, 0x9f, 0x42,
		    0x9b, 0x0f, 0x5e, 0x54, 0x11, 0xa1, 0x4f, 0xa4,
		    0x0a, 0x48, 0x22, 0x0f, 0x02, 0x3e, 0x70, 0x2b,
		    0xe1, 0x64, 0x50, 0xd7 } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901",//256
		  { 0x9e, 0x93, 0x8b, 0x13, 0xe5, 0x96, 0x14, 0x5d,
		    0x2f, 0xd7, 0x54, 0xe1, 0x99, 0xbd, 0x09, 0x7d,
		    0xf1, 0xd2, 0x4c, 0x02, 0x69, 0x91, 0xa9, 0x9a,
		    0xcc, 0xdb, 0x4c, 0x78 } },
		{ NULL, { 0 } }
	};

	int32_t i;
	uint8_t tmp[28];
	sprd_crypto_context_t sha224;

	for (i = 0; tests[i].msg != NULL; i++) {
		sprd_hash_init(SPRD_CRYPTO_HASH_SHA224, &sha224);
		sprd_hash_update(&sha224, (uint8_t *)tests[i].msg, (uint32_t)sprd_pal_strlen(tests[i].msg));
		sprd_hash_final(&sha224, tmp);
		if (sprd_pal_memcmp(tmp, tests[i].hash, 28) != 0) {
			SPRD_CRYPTO_LOG_DEBUG("sha224 test[%d] FAILED\n", i);
			return SPRD_CRYPTO_ERR_RESULT;
		}
	}

	return SPRD_CRYPTO_SUCCESS;
}


sprd_crypto_err_t
sprd_hash_test_sha256 (void) {
	static const struct {
		const char *msg;
		unsigned char hash[32];
	} tests[] = {//0, 128, 131, 256, 260, 5, 384 389
		{ "",//0
		  { 0xe3, 0xb0, 0xc4, 0x42, 0x98, 0xfc, 0x1c, 0x14,
		    0x9a, 0xfb, 0xf4, 0xc8, 0x99, 0x6f, 0xb9, 0x24,
		    0x27, 0xae, 0x41, 0xe4, 0x64, 0x9b, 0x93, 0x4c,
		    0xa4, 0x95, 0x99, 0x1b, 0x78, 0x52, 0xb8, 0x55 } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901",//128
		  { 0x86, 0x8c, 0xbc, 0x06, 0xd5, 0x01, 0x0f, 0x14,
		    0xff, 0xfb, 0x17, 0xb9, 0xf6, 0x7e, 0x87, 0xe2,
		    0x14, 0x5b, 0x08, 0xf1, 0x33, 0x72, 0xd3, 0x30,
		    0x5e, 0x65, 0x1d, 0x16, 0xb0, 0xd7, 0x12, 0xe6, } },
		{ "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901"
		  "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz012345678901",//256
		  { 0x3e, 0x36, 0x83, 0x70, 0x58, 0xcc, 0xe4, 0xdb,
		    0xb5, 0x6c, 0x5d, 0x7e, 0x61, 0xff, 0x37, 0xf0,
		    0xdc, 0x0a, 0x0e, 0x84, 0x31, 0xa4, 0xf9, 0x35,
		    0xc0, 0x0d, 0x0e, 0x3d, 0x61, 0x19, 0x83, 0xa0 } },
		{ NULL, { 0 } }
	};

	int32_t i;
	uint8_t tmp[32];
	sprd_crypto_context_t sha256;

	for (i = 0; tests[i].msg != NULL; i++) {
		sprd_hash_init(SPRD_CRYPTO_HASH_SHA256, &sha256);
		sprd_hash_update(&sha256, (uint8_t *)tests[i].msg, (uint32_t)sprd_pal_strlen(tests[i].msg));
		sprd_hash_final(&sha256, tmp);
		if (sprd_pal_memcmp(tmp, tests[i].hash, 32) != 0) {
			SPRD_CRYPTO_LOG_DEBUG("sha256 test[%d] FAILED\n", i);
			return SPRD_CRYPTO_ERR_RESULT;
		}
	}

	return SPRD_CRYPTO_SUCCESS;
}

sprd_crypto_err_t
sprd_hash_test_sha384 (void) {
	static const struct {
		const char *msg;
		unsigned char hash[48];
	} tests[] = {//0, 128, 131, 256, 260, 5, 384 389
		{ "",
		  { 0x38, 0xb0, 0x60, 0xa7, 0x51, 0xac, 0x96, 0x38,
		    0x4c, 0xd9, 0x32, 0x7e, 0xb1, 0xb1, 0xe3, 0x6a,
		    0x21, 0xfd, 0xb7, 0x11, 0x14, 0xbe, 0x07, 0x43,
		    0x4c, 0x0c, 0xc7, 0xbf, 0x63, 0xf6, 0xe1, 0xda,
		    0x27, 0x4e, 0xde, 0xbf, 0xe7, 0x6f, 0x65, 0xfb,
		    0xd5, 0x1a, 0xd2, 0xf1, 0x48, 0x98, 0xb9, 0x5b } },
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz12345678901234",//128
		  { 0x76, 0x53, 0x24, 0x9e, 0x76, 0x07, 0x8c, 0xf6,
		    0xef, 0x51, 0x02, 0xab, 0x70, 0xf0, 0xbf, 0x11,
		    0xa5, 0xd7, 0x4b, 0xe4, 0x9b, 0x5f, 0x8f, 0x5f,
		    0xa6, 0x8d, 0x34, 0x0b, 0x12, 0xde, 0x7e, 0x51,
		    0xe8, 0xb4, 0x65, 0xc8, 0x4a, 0x64, 0x1f, 0xd6,
		    0x2d, 0x9e, 0xd7, 0xa6, 0x94, 0xd4, 0xca, 0x71 } },
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890ABCDEFGH",//256B
		  { 0xe3, 0x3c, 0x2b, 0xb0, 0xd8, 0x94, 0x64, 0xcc,
		    0xde, 0xfd, 0x3d, 0x25, 0x9c, 0x0f, 0x38, 0xab,
		    0xdc, 0x35, 0xff, 0x97, 0xf6, 0x8c, 0x36, 0xe2,
		    0xdd, 0xd6, 0x2a, 0xa6, 0x08, 0x18, 0x4d, 0x90,
		    0xc4, 0xc3, 0x76, 0xc8, 0x89, 0x60, 0xc6, 0x95,
		    0xae, 0xf4, 0x3c, 0x90, 0xd3, 0xbe, 0xc5, 0x16 } },
		{ NULL, { 0 } }
	};

	int32_t i;
	uint8_t tmp[48];
	sprd_crypto_context_t sha384;

	for (i = 0; tests[i].msg != NULL; i++) {
		sprd_hash_init(SPRD_CRYPTO_HASH_SHA384, &sha384);
		sprd_hash_update(&sha384, (uint8_t *)tests[i].msg, (uint32_t)sprd_pal_strlen(tests[i].msg));
		sprd_hash_final(&sha384, tmp);
		if (sprd_pal_memcmp(tmp, tests[i].hash, 48) != 0) {
			SPRD_CRYPTO_LOG_DEBUG("sha384 test[%d] FAILED\n", i);
			return SPRD_CRYPTO_ERR_RESULT;
		}
	}

	return SPRD_CRYPTO_SUCCESS;
}

sprd_crypto_err_t
sprd_hash_test_sha512 (void) {
	static const struct {
		const char *msg;
		unsigned char hash[64];
	} tests[] = {//0, 128, 131, 256, 260, 5, 384 389
		{ "",
		  { 0xcf, 0x83, 0xe1, 0x35, 0x7e, 0xef, 0xb8, 0xbd,
		    0xf1, 0x54, 0x28, 0x50, 0xd6, 0x6d, 0x80, 0x07,
		    0xd6, 0x20, 0xe4, 0x05, 0x0b, 0x57, 0x15, 0xdc,
		    0x83, 0xf4, 0xa9, 0x21, 0xd3, 0x6c, 0xe9, 0xce,
		    0x47, 0xd0, 0xd1, 0x3c, 0x5d, 0x85, 0xf2, 0xb0,
		    0xff, 0x83, 0x18, 0xd2, 0x87, 0x7e, 0xec, 0x2f,
		    0x63, 0xb9, 0x31, 0xbd, 0x47, 0x41, 0x7a, 0x81,
		    0xa5, 0x38, 0x32, 0x7a, 0xf9, 0x27, 0xda, 0x3e } },
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz12345678901234",//128
		  { 0x97, 0x48, 0x74, 0xae, 0x1d, 0x1a, 0x31, 0x77,
		    0xf1, 0xe2, 0xdd, 0x03, 0xa2, 0x9e, 0x2e, 0x41,
		    0x15, 0x92, 0x6a, 0x7e, 0x82, 0x35, 0xd6, 0x04,
		    0x7e, 0x29, 0xac, 0x19, 0xa9, 0xf3, 0xcd, 0x1b,
		    0x48, 0xa4, 0xf3, 0xc8, 0xbd, 0x4a, 0x14, 0xfe,
		    0x25, 0x5f, 0xa7, 0x59, 0x01, 0x9d, 0x54, 0x4d,
		    0xad, 0x94, 0x76, 0x74, 0x39, 0x5c, 0x80, 0x8a,
		    0x8f, 0x43, 0x13, 0xb4, 0x53, 0x52, 0xb9, 0x78, } },
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890ABCDEFGH",//256B
		  { 0xf5, 0xcb, 0x00, 0xf6, 0x52, 0x6f, 0x43, 0x0f,
		    0xc9, 0x6c, 0x2e, 0xf6, 0x7f, 0xc1, 0x26, 0x4a,
		    0x3f, 0x1d, 0x25, 0x68, 0x85, 0x73, 0xba, 0xc2,
		    0x67, 0x02, 0x1a, 0xa2, 0x96, 0x2a, 0xa5, 0xf0,
		    0xee, 0x30, 0xfd, 0x7a, 0x2f, 0xf8, 0x50, 0x59,
		    0x05, 0x19, 0xbe, 0xa2, 0x39, 0x2d, 0xcc, 0xdb,
		    0x5e, 0x80, 0xf8, 0xec, 0xdf, 0x47, 0xfc, 0x9b,
		    0x42, 0xad, 0x5b, 0xc6, 0xb2, 0xd8, 0xf3, 0xc9, } },
		{ NULL, { 0 } }
	};

	int32_t i;
	uint8_t tmp[64];
	sprd_crypto_context_t sha512;

	for (i = 0; tests[i].msg != NULL; i++) {
		sprd_hash_init(SPRD_CRYPTO_HASH_SHA512, &sha512);
		sprd_hash_update(&sha512, (uint8_t *)tests[i].msg, (uint32_t)sprd_pal_strlen(tests[i].msg));
		sprd_hash_final(&sha512, tmp);
		if (sprd_pal_memcmp(tmp, tests[i].hash, 64) != 0) {
			SPRD_CRYPTO_LOG_DEBUG("512 test[%d] FAILED\n", i);
			return SPRD_CRYPTO_ERR_RESULT;
		}
	}

	return SPRD_CRYPTO_SUCCESS;
}

sprd_crypto_err_t
sprd_hash_test_sha512_224 (void) {
	static const struct {
		const char *msg;
		unsigned char hash[28];
	} tests[] = {//0, 128, 131, 256, 260, 5, 384 389
		{ "",
		  { 0x6e, 0xd0, 0xdd, 0x02, 0x80, 0x6f, 0xa8, 0x9e,
		    0x25, 0xde, 0x06, 0x0c, 0x19, 0xd3, 0xac, 0x86,
		    0xca, 0xbb, 0x87, 0xd6, 0xa0, 0xdd, 0xd0, 0x5c,
		    0x33, 0x3b, 0x84, 0xf4 } },
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz12345678901234",//128
		  { 0xcd, 0x11, 0x2c, 0xbe, 0x0d, 0x04, 0x38, 0x88,
		    0x8e, 0xfd, 0xab, 0x06, 0x7c, 0xed, 0x2b, 0x86,
		    0x39, 0xfa, 0x9e, 0x26, 0x66, 0x32, 0x89, 0xcb,
		    0x33, 0xae, 0xf9, 0x46 } },
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890ABCDEFGH",//256B
		  { 0x59, 0xa6, 0x5c, 0x94, 0x11, 0xfa, 0xdc, 0x43,
		    0x51, 0x7c, 0xf4, 0x0f, 0x67, 0x63, 0xde, 0xe2,
		    0x08, 0xb6, 0x2a, 0xf5, 0xd2, 0x1e, 0x56, 0xeb,
		    0x1c, 0x91, 0x25, 0x40 } },
		{ NULL, { 0 } }
	};

	int32_t i;
	uint8_t tmp[28];
	sprd_crypto_context_t sha512_224;

	for (i = 0; tests[i].msg != NULL; i++) {
		sprd_hash_init(SPRD_CRYPTO_HASH_SHA512_224, &sha512_224);
		sprd_hash_update(&sha512_224, (uint8_t *)tests[i].msg, (uint32_t)sprd_pal_strlen(tests[i].msg));
		sprd_hash_final(&sha512_224, tmp);
		if (sprd_pal_memcmp(tmp, tests[i].hash, 28) != 0) {
			SPRD_CRYPTO_LOG_DEBUG("sha512_224 test[%d] FAILED\n", i);
			return SPRD_CRYPTO_ERR_RESULT;
		}
	}

	return SPRD_CRYPTO_SUCCESS;
}

sprd_crypto_err_t
sprd_hash_test_sha512_256 (void) {
	static const struct {
		const char *msg;
		unsigned char hash[32];
	} tests[] = {//0, 128, 131, 256, 260, 5, 384 389
		{ "",
		  { 0xc6, 0x72, 0xb8, 0xd1, 0xef, 0x56, 0xed, 0x28,
		    0xab, 0x87, 0xc3, 0x62, 0x2c, 0x51, 0x14, 0x06,
		    0x9b, 0xdd, 0x3a, 0xd7, 0xb8, 0xf9, 0x73, 0x74,
		    0x98, 0xd0, 0xc0, 0x1e, 0xce, 0xf0, 0x96, 0x7a, } },
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz12345678901234",//128
		  { 0x45, 0x88, 0x1d, 0xef, 0xbc, 0x88, 0xb7, 0x5f,
		    0x4f, 0x54, 0xf4, 0xd7, 0x83, 0xb3, 0x8e, 0xdd,
		    0xaa, 0x51, 0xc9, 0x75, 0xb6, 0xc9, 0x29, 0x10,
		    0xc1, 0x85, 0x9a, 0xfe, 0xb9, 0xee, 0x98, 0x01, } },
		{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"
		  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890ABCDEFGH",//256B
		  { 0x94, 0x3b, 0x60, 0xcc, 0x97, 0xa5, 0x21, 0x7e,
		    0xaf, 0xfe, 0x79, 0xdb, 0x73, 0x76, 0x1e, 0x6e,
		    0x12, 0x02, 0x6f, 0x99, 0xe4, 0xd1, 0xf6, 0x5a,
		    0x0e, 0x07, 0x57, 0xc0, 0xe1, 0xe7, 0x81, 0xca, } },
		{ NULL, { 0 } }
	};

	int32_t i;
	uint8_t tmp[32];
	sprd_crypto_context_t sha512_256;

	for (i = 0; tests[i].msg != NULL; i++) {
		sprd_hash_init(SPRD_CRYPTO_HASH_SHA512_256, &sha512_256);
		sprd_hash_update(&sha512_256, (uint8_t *)tests[i].msg, (uint32_t)sprd_pal_strlen(tests[i].msg));
		sprd_hash_final(&sha512_256, tmp);
		if (sprd_pal_memcmp(tmp, tests[i].hash, 32) != 0) {
			SPRD_CRYPTO_LOG_DEBUG("sha512_256 test[%d] FAILED\n", i);
			return SPRD_CRYPTO_ERR_RESULT;
		}
	}

	return SPRD_CRYPTO_SUCCESS;
}

sprd_crypto_err_t
sprd_hash_test (void) {
	sprd_crypto_err_t err = SPRD_CRYPTO_SUCCESS;
	int32_t md5 = 0, sha1 = 0, sha224 = 0, sha256 = 0, sha384 = 0, sha512 = 0, sha512_224 = 0, sha512_256 = 0;

	SPRD_CRYPTO_LOG_ERR("SPRD_CRYPTO_HASH_MD5 is %d\n", SPRD_HASH_SIZE(SPRD_CRYPTO_HASH_MD5));
	SPRD_CRYPTO_LOG_ERR("SPRD_CRYPTO_HASH_SHA1 is %d\n", SPRD_HASH_SIZE(SPRD_CRYPTO_HASH_SHA1));
	SPRD_CRYPTO_LOG_ERR("SPRD_CRYPTO_HASH_SHA224 is %d\n", SPRD_HASH_SIZE(SPRD_CRYPTO_HASH_SHA224));
	SPRD_CRYPTO_LOG_ERR("SPRD_CRYPTO_HASH_SHA256 is %d\n", SPRD_HASH_SIZE(SPRD_CRYPTO_HASH_SHA256));
	SPRD_CRYPTO_LOG_ERR("SPRD_CRYPTO_HASH_SHA384 is %d\n", SPRD_HASH_SIZE(SPRD_CRYPTO_HASH_SHA384));
	SPRD_CRYPTO_LOG_ERR("SPRD_CRYPTO_HASH_SHA512 is %d\n", SPRD_HASH_SIZE(SPRD_CRYPTO_HASH_SHA512));
	SPRD_CRYPTO_LOG_ERR("SPRD_CRYPTO_HASH_SHA512_224 is %d\n", SPRD_HASH_SIZE(SPRD_CRYPTO_HASH_SHA512_224));
	SPRD_CRYPTO_LOG_ERR("SPRD_CRYPTO_HASH_SHA512_256 is %d\n", SPRD_HASH_SIZE(SPRD_CRYPTO_HASH_SHA512_256));

	err = sprd_hash_test_md5();
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("****sprd_hash_test_md5 FAILED!****\n");
		goto failed;
	} else {
		md5 = 1;
	}

	err = sprd_hash_test_sha1();
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("****sprd_hash_test_sha1 FAILED!****\n");
		goto failed;
	} else {
		sha1 = 1;
	}

	err = sprd_hash_test_sha224();
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("****sprd_hash_test_sha224 FAILED!****\n");
		goto failed;
	} else {
		sha224 = 1;
	}

	err = sprd_hash_test_sha256();
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("****sprd_hash_test_sha256 FAILED!****\n");
		goto failed;
	} else {
		sha256 = 1;
	}

	err = sprd_hash_test_sha384();
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("****sprd_hash_test_sha384 FAILED!****\n");
		goto failed;
	} else {
		sha384 = 1;
	}

	err = sprd_hash_test_sha512();
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("****sprd_hash_test_sha512 FAILED!****\n");
		goto failed;
	} else {
		sha512 = 1;
	}

	err = sprd_hash_test_sha512_224();
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("****sprd_hash_test_sha512_224 FAILED!****\n");
		goto failed;
	} else {
		sha512_224 = 1;
	}

	err = sprd_hash_test_sha512_256();
	if (err != SPRD_CRYPTO_SUCCESS) {
		SPRD_CRYPTO_LOG_ERR("****sprd_hash_test_sha512_256 FAILED!****\n");
		goto failed;
	} else {
		sha512_256 = 1;
	}

failed:
	if (md5 == 1) {
		SPRD_CRYPTO_LOG_WARN("sprd_hash_test_md5 pass!\n");
	}

	if (sha1 == 1) {
		SPRD_CRYPTO_LOG_WARN("sprd_hash_test_sha1 pass!\n");
	}

	if (sha224 == 1) {
		SPRD_CRYPTO_LOG_WARN("sprd_hash_test_sha224 pass!\n");
	}

	if (sha256 == 1) {
		SPRD_CRYPTO_LOG_WARN("sprd_hash_test_sha256 pass!\n");
	}

	if (sha384 == 1) {
		SPRD_CRYPTO_LOG_WARN("sprd_hash_test_sha384 pass!\n");
	}

	if (sha512 == 1) {
		SPRD_CRYPTO_LOG_WARN("sprd_hash_test_sha512 pass!\n");
	}

	if (sha512_224 == 1) {
		SPRD_CRYPTO_LOG_WARN("sprd_hash_test_sha512_224 pass!\n");
	}

	if (sha512_256 == 1) {
		SPRD_CRYPTO_LOG_WARN("sprd_hash_test_sha512_256 pass!\n");
	}
	return err;
}


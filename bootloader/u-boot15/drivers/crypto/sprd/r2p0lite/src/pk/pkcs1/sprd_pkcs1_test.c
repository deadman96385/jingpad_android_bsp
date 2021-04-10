/* *  Copyright 2016 (c) Spreadtrum Communications Inc.
*
*  This software is protected by copyright, international treaties and various patents.
*  Any copy, reproduction or otherwise use of this software must be authorized in a
*  license agreement and include this Copyright Notice and any other notices specified
*  in the license agreement. Any redistribution in binary form must be authorized in the
*  license agreement and include this Copyright Notice and any other notices specified
*  in the license agreement and/or in materials provided with the binary distribution.
*
*  created by vee.zhang <2016.10.15>
*/

#include <sprd_crypto.h>

#include "pkcs1/sprd_pkcs1.h"
#include "../ecc/sprd_ecc_utils.h"

static const uint8_t pubkey_n[] = {
	210, 136, 105, 162, 117, 171, 114, 146, 81, 242, 21, 222, 87, 60, 122, 176, 245,
	57, 213, 159, 196, 165, 40, 75, 146, 35, 114, 118, 25, 196, 150, 38, 40, 195,
	56, 109, 145, 47, 171, 117, 57, 220, 176, 186, 70, 175, 222, 65, 60, 65, 31, 88,
	93, 220, 27, 74, 73, 43, 112, 6, 242, 78, 38, 229, 58, 206, 200, 4, 196, 67, 8,
	141, 21, 141, 79, 214, 221, 179, 184, 64, 92, 8, 222, 68, 16, 97, 101, 68, 210,
	155, 217, 238, 78, 207, 202, 43, 16, 241, 194, 78, 28, 172, 124, 44, 111, 181,
	187, 71, 57, 190, 50, 109, 254, 170, 103, 126, 124, 156, 169, 36, 164, 186, 136,
	108, 66, 44, 147, 137
};

static const uint8_t pubkey_e[] = {1, 0, 1};

static const uint8_t test_message[] = {0, 0, 0, 0};

static const uint8_t test_message_sha1_hash[] = {
	144, 105, 202, 120, 231, 69, 10, 40, 81, 115, 67, 27, 62, 82, 197, 194, 82, 153,
	228, 115
};

static const uint8_t pkcs1_pss_emsa_data[] = {
	0x35, 0xac, 0x5c, 0x70, 0xbb, 0x17, 0xd8, 0x15, 0xc9, 0x69, 0xe1, 0xa5, 0xb9, 0xfa, 0xed, 0x10,
	0xd0, 0x5e, 0x0c, 0x04, 0xbc, 0xdf, 0x98, 0xe9, 0x25, 0xf0, 0xb4, 0x44, 0x1b, 0x32, 0xdd, 0x06,
	0xd1, 0xb7, 0xde, 0x0b, 0x3a, 0xa7, 0xaf, 0x12, 0x4d, 0x23, 0xb1, 0x73, 0x46, 0xbe, 0x1b, 0x0c,
	0x4a, 0xfd, 0x89, 0x91, 0x0e, 0x01, 0x87, 0x01, 0xc6, 0x74, 0x32, 0xa9, 0x2b, 0x7d, 0x67, 0xac,
	0xd5, 0xf2, 0x8a, 0x5e, 0xe9, 0xd7, 0x33, 0xd5, 0xca, 0xd9, 0xd4, 0xa7, 0x0e, 0x3f, 0x54, 0x88,
	0x0f, 0x11, 0x71, 0x2d, 0x84, 0x97, 0xc5, 0x08, 0x41, 0x2c, 0xbf, 0x2d, 0x47, 0x51, 0x3a, 0x15,
	0x4b, 0x0a, 0x64, 0x2d, 0x04, 0xfe, 0x7d, 0x15, 0xd3, 0x6d, 0x54, 0x3a, 0xc8, 0x29, 0x39, 0x92,
	0xa3, 0x0d, 0xfb, 0x73, 0x74, 0xfc, 0x85, 0x48, 0x48, 0x6a, 0x73, 0xd7, 0x9f, 0x2e, 0x9e, 0xbc,
};

int pkcs1_pss_emsa_test(void)
{
	int ret = -1;
	int res = -1;
	uint8_t out[512];
	uint32_t outlen = 512;
	/*unsigned char digest[192];*/

	CE_PF("----------pkcs1 pkcs1 pss emsa test ----------\n");

	ret = sprd_pkcs1_pss_decode(test_message_sha1_hash, 20,
				pkcs1_pss_emsa_data, 128, 0, SPRD_CRYPTO_HASH_SHA1,
				SPRD_CRYPTO_HASH_SHA1, 1024, &res);
	if (!ret && !res) {
		CE_PF("----------pkcs1 pss emsa pass2, ret = (%x) res = (%x)-----------\n", ret, res);
	} else {
		CE_PF("----------pkcs1 pss emsa fail2, ret = (%x) res = (%x)-----------\n", ret, res);
		return -2;
	}

	ret = -1;
	res = -1;
	outlen = 512;
	ret = sprd_pkcs1_pss_encode(test_message_sha1_hash, 20, 0,
				SPRD_CRYPTO_HASH_SHA1, SPRD_CRYPTO_HASH_SHA1, 1024, out, &outlen);
	if (!ret) {
		CE_PF("----------pkcs1 pss emsa pass3, ret = (%x) outlen = (%d)-----------\n", ret, outlen);
	} else {
		CE_PF("----------pkcs1 pss emsa fail3, ret = (%x) outlen = (%d)-----------\n", ret, outlen);
		return -3;
	}
	ret = sprd_pkcs1_pss_decode(test_message_sha1_hash, 20,
				out, outlen, 0, SPRD_CRYPTO_HASH_SHA1, SPRD_CRYPTO_HASH_SHA1, 1024, &res);
	if (!ret && !res) {
		CE_PF("----------pkcs1 pss emsa pass4, ret = (%x) res = (%x)-----------\n", ret, res);
	} else {
		CE_PF("----------pkcs1 pss emsa fail4, ret = (%x) res = (%x)-----------\n", ret, res);
		return -4;
	}

	return 0;
}

/*int pkcs1_test()*/
/*{*/
	/*int ret = 0;*/

	/*ret = pkcs1_pss_emsa_test();*/

	/*return ret;*/
/*}*/

#include <common.h>
#include <malloc.h>
#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include "secure_boot.h"
#include "sha1_32.h"
#ifndef USE_LEGENCY_RSA
#include <crypto/sprdrsa.h>
#endif

#define EFUSE_HASH_STARTID 2

static SHA1Context_32 s_sha = { 0 };
static uint32_t s_hash_data[32] = { 0 };

rom_callback_func_t *get_rom_callback(void)
{
	rom_callback_func_t *rom_callback = NULL;
#ifdef CONFIG_SCX35LT8
		rom_callback = (rom_callback_func_t *)(*((unsigned int*)0x00000020));
#else
		rom_callback = (rom_callback_func_t *)(*((unsigned int*)0xFFFF0020));
#endif
	return rom_callback;
}

int secureboot_enabled(void)
{
	//return 1;
#ifdef CONFIG_SECURE_BOOT
	uint32_t reg = 0;
	uint32_t bonding = REG32(REG_AON_APB_BOND_OPT0);
	if (bonding & BIT_2) {
		reg = __ddie_efuse_read(EFUSE_HASH_STARTID);
		if ((reg >> 31) & 0x1)
			return 1;
	}
#endif
	return 0;
}

#define MAKE_DWORD(a,b,c,d) (uint32_t)(((uint32_t)(a)<<24) | (uint32_t)(b)<<16 | ((uint32_t)(c)<<8) | ((uint32_t)(d)))
#ifdef USE_LEGENCY_RSA
void RSA_Decrypt(unsigned char *p, unsigned char *m, unsigned char *r2, unsigned char *e)
{
	rom_callback_func_t *rom_callback = NULL;
	unsigned int _e = 0;
	unsigned int _m[32];
	unsigned int _p[32];
	unsigned int _r2[32];
	int i = 0;

	_e = MAKE_DWORD(e[0], e[1], e[2], e[3]);

	for (i = 31; i >= 0; i--) {
		_m[31 - i] = MAKE_DWORD(m[4 * i], m[4 * i + 1], m[4 * i + 2], m[4 * i + 3]);
		_p[31 - i] = MAKE_DWORD(p[4 * i], p[4 * i + 1], p[4 * i + 2], p[4 * i + 3]);
		_r2[31 - i] = MAKE_DWORD(r2[4 * i], r2[4 * i + 1], r2[4 * i + 2], r2[4 * i + 3]);
	}

	RSA_ModPower(_p, _m, _r2, _e);
	for (i = 31; i >= 0; i--) {
		p[4 * (31 - i)] = (unsigned char)(_p[i] >> 24);
		p[4 * (31 - i) + 1] = (unsigned char)(_p[i] >> 16);
		p[4 * (31 - i) + 2] = (unsigned char)(_p[i] >> 8);
		p[4 * (31 - i) + 3] = (unsigned char)(_p[i]);
	}
}
#endif

int harshVerify(uint8_t * data, uint32_t data_len, uint8_t * data_hash, uint8_t * data_key)
{
	uint32_t i, soft_hash_data[32];
	uint32_t *data_ptr;
	uint8_t *data_ptr_u8;
	uint8_t *soft_hash;
	vlr_info_t *vlr_info;
	bsc_info_t *bsc_info;
	SHA1Context_32 sha;
	uint8_t hash_copy[128] = { 0 };

	vlr_info = (vlr_info_t *) data_hash;

	if (vlr_info->magic != VLR_MAGIC) {
		secf("hashVerify, vlr magic mismatch\r\n");
		return 0;
	}

	bsc_info = (bsc_info_t *) data_key;

	SHA1Reset_32(&sha);
	SHA1Input_32(&sha, (uint32_t *) data, data_len >> 2);
	SHA1Result_32(&sha, soft_hash_data);

	memcpy(hash_copy, vlr_info->hash, sizeof(vlr_info->hash));

#ifdef USE_LEGENCY_RSA
	RSA_Decrypt(hash_copy, bsc_info->key.m, bsc_info->key.r2, (unsigned char *)(&bsc_info->key.e));
	data_ptr = (uint32_t *) (&hash_copy[108]);
	for (i = 0; i < 5; i++) {
		//printf("[%3d] : %02X, %02X . \r\n", i, soft_hash_data[i], data_ptr[i]);
		if (soft_hash_data[i] != data_ptr[i]) {
			secf("hashVerify, mismatch\r\n");
			return 0;
		}
	}
#else
	uint8_t hash_outcome[100];
	int len = RSA_PubDec((unsigned char *)(&bsc_info->key.e), bsc_info->key.m, 1024, hash_copy, hash_outcome);
	data_ptr_u8 = &hash_outcome[len - 20];
	soft_hash= soft_hash_data;
	for (i = 0; i < 20; i++) {
		//printf("[%3d] : %02X, %02X . \r\n", i, soft_hash[i], data_ptr[i]);
		if (soft_hash[i] != data_ptr_u8[i]) {
			secf("hashVerify, mismatch\r\n");
			return 0;
		}
	}
#endif

	secf("hashVerify, succ\r\n");
	return 1;
}

void secure_check(uint8_t * data, uint32_t data_len, uint8_t * data_hash, uint8_t * data_key)
{
	if (0 == harshVerify(data, data_len, data_hash, data_key)) {
		while (1) ;
	}
}

void get_sec_callback(sec_callback_func_t * sec_callfunc)
{
	sec_callfunc->rom_callback = get_rom_callback();
	sec_callfunc->secure_check = secure_check;
}

int cal_sha1(void *data, uint32_t orig_len, void *hash_data)
{

	SHA1Context_32 sha;

	SHA1Reset_32(&sha);
	SHA1Input_32(&sha, (uint32_t *) data, orig_len >> 2);
	SHA1Result_32(&sha, hash_data);

	return 1;
}

#ifndef CONFIG_NAND_SPL
int cal_md5(void *data, uint32_t orig_len, void *harsh_data)
{
	return 0;
}
#endif

void Sec_SHA1_Start(void)
{
	secf("Enter \r\n");
	SHA1Reset_32(&s_sha);
	secf("Leave \r\n");
	return;
}

void Sec_SHA1_Update(void *data, uint32_t data_len)
{
	secf("Enter data_len = %d  hex is: 0x%x \r\n", data_len, data_len);
	SHA1Input_32(&s_sha, (uint32_t *) data, data_len >> 2);
	secf("Leave \r\n");
	return;
}

void Sec_SHA1_Finish(void)
{
	uint8_t i;

	secf("Enter \r\n");
	SHA1Result_32(&s_sha, s_hash_data);
	secf("Leave \r\n");
	return;
}

int hashVerify_system(uint8_t * data_hash, uint8_t * data_key)
{
	uint8_t i;
	uint32_t *data_ptr;
	vlr_info_t *vlr_info;
	bsc_info_t *bsc_info;
	uint8_t hash_copy[128] = { 0 };
	vlr_info = (vlr_info_t *) data_hash;
	bsc_info = (bsc_info_t *) data_key;
	if (vlr_info->magic != VLR_MAGIC) {
		secf("hashVerify_system, vlr magic mismatch\r\n");
		return 0;
	}
	memcpy(hash_copy, vlr_info->hash, sizeof(vlr_info->hash));
	RSA_Decrypt(hash_copy, bsc_info->key.m, bsc_info->key.r2, (unsigned char *)(&bsc_info->key.e));
	data_ptr = (uint32_t *) (&hash_copy[108]);
	for (i = 0; i < 5; i++) {
		secf("[%d]: %02X, %02X \r\n", i, s_hash_data[i], data_ptr[i]);
		if (s_hash_data[i] != data_ptr[i]) {
			secf("hashVerify_system, mismatch\r\n");
			return 0;
		}
	}
	secf("hashVerify_system, succ\r\n");
	return 1;
}

int secure_check_system(uint8_t * data_hash, uint8_t * data_key)
{
	return hashVerify_system(data_hash, data_key);
}

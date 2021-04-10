/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <sha256.h>

#include "loader_common.h"

#include "efuse_operate.h"
#include "secure_efuse.h"

#define RAND_MAX ((1U << 31) - 1)

static int g_seed = 0;

union sha_256{
  unsigned char sha256_char[32];
  unsigned int  sha256_int[8];
}sha256;

unsigned int masterkey[8];
static void init_rand(void ){
  int efuse_uid[4];
  memset(efuse_uid,    0x0, 16);
  efuse_uid_read(efuse_uid, 16);
  g_seed = efuse_uid[3];
}

static int get_rand(void){
  g_seed = (g_seed * 1103515245 + 12345) & RAND_MAX;
  return g_seed;
}


int secure_efuse_program_native(void){

  unsigned int aes256[8];
  int ret = 0;

  ret = calc_sha1_write_efuse();
  if(ret)
    return SHA1_ERR;
  #if 0
  ret = gene_aes256_write_efuse(aes256);
  if(ret)
    return AES256_ERR;
  ret = calc_sha256_write_rpmb(aes256, 32);
  if(ret)
    return SHA256_ERR;
  #endif
  return PROG_OK;
}



int calc_sha1_write_efuse(void){

  union sha_1{
    unsigned char sha1_char[24];
    unsigned int  sha1_int[6];
  }sha1;

  char sha1_string[41];
  int ret = 0;
  memset(&sha1,   0x0, 24);
  memset(sha1_string,   0x0, 41);
#ifdef CONFIG_SECURE_BOOT

//  -----   generate SHA1 key   -----
  get_spl_hash((void*)sha1.sha1_char);
  /*sprintf(sha1_string,"%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", sha1.sha1_char[0],
				sha1.sha1_char[1],
				sha1.sha1_char[2],
				sha1.sha1_char[3],
				sha1.sha1_char[4],
				sha1.sha1_char[5],
				sha1.sha1_char[6],
				sha1.sha1_char[7],
				sha1.sha1_char[8],
				sha1.sha1_char[9],
				sha1.sha1_char[10],
				sha1.sha1_char[11],
				sha1.sha1_char[12],
				sha1.sha1_char[13],
				sha1.sha1_char[14],
				sha1.sha1_char[15],
				sha1.sha1_char[16],
				sha1.sha1_char[17],
				sha1.sha1_char[18],
				sha1.sha1_char[19]);*/
  sprintf(sha1_string,"%08x%08x%08x%08x%08x", sha1.sha1_int[0],
				sha1.sha1_int[1],
				sha1.sha1_int[2],
				sha1.sha1_int[3],
				sha1.sha1_int[4]);
//  -----   write SHA1 key Efuse   -----
  ret = efuse_hash_write(sha1_string, 40);
  if(ret < 0){
    debugf("sha1 efuse write Error [%d]\n", ret);
    return SHA1_ERR;
  }
//block2 bit15
  if ( efuse_secure_is_enabled() ){
    debugf("enabled\n");
    return PROG_OK;
  }
  efuse_secure_enable();
#endif
  return PROG_OK;
}


int gene_aes256_write_efuse(unsigned int* aes256){

  int idx =0;
  int ret = 0;
  char aes_string[65];
  memset(aes_string, 0x0, 65);
//  -----   generate AES 256 key   -----
  init_rand();
  srand(idx+2);
  for(idx =0; idx <8; idx++){
    aes256[idx] = (get_rand() | rand());
  }
  sprintf(aes_string, "%08x%08x%08x%08x%08x%08x%08x%08x", aes256[0],
				aes256[1],
				aes256[2],
				aes256[3],
				aes256[4],
				aes256[5],
				aes256[6],
				aes256[7]);
//  -----   write SHA256 key efuse   -----
  ret = arm7_key_write(aes_string, 64);
  if(ret < 0){
    debugf("aes 256 write efuse Error[%x]\n", ret);
    return AES256_ERR;
  }
  return PROG_OK;
}

void hash_str_to_ul(void *dst,void *src,unsigned int count)
{
    int i;
    unsigned char tmp[9] = {0};
    unsigned int *pintdst = dst;

    memset(tmp, 0, sizeof(tmp));

    for (i = 0; i < count; i += 8) {
        strncpy((char*)tmp, (char*)&src[i], 8);
        *pintdst++ = (unsigned int)simple_strtoul(tmp, 0, 16);
    }
}

int calc_sha256_write_rpmb(const unsigned char *key, unsigned int keyLenth){

  char aes_string[65];
  unsigned int aes256[8];
  int i = 0;
  memset(aes_string, 0x0, 65);
  memset(aes256,     0x0, 32);
  memset(&sha256,    0x0, 32);

  arm7_key_read(aes_string, 64);
  hash_str_to_ul(aes256, aes_string, 64);
//  -----   calculate AES256 hash value   -----
#if defined(CONFIG_SHA256)
  sha256_csum_wd(aes256, 32, sha256.sha256_char, 5);
#endif
//  -----   write rpmb   -----------------------
  if(rpmb_write_key(sha256.sha256_char, 32) )
    return SHA256_ERR;
  return PROG_OK;
}

int read_master_key(void){

  char aes_string[65];
  memset(aes_string, 0x0, 65);
  memset(masterkey,  0x0, 32);

  arm7_key_read(aes_string, 64);

  hash_str_to_ul(masterkey, aes_string, 64);
  return PROG_OK;
}




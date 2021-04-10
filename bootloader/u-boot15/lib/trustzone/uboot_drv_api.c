/*
 * Copyright (c) 2013-2014, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "uboot_sec_drv.h"
#include <otp_helper.h>

/**
NOTICE, from now on, in order to satisfy all current TEEs,
we use smc32 call from uboot to tos, this is also the way for generic
TEE driver, there are two ways if you want to pass 64 bits addr to tos:
1. put 64 bits addr to your own structure, then pass structure's addr
2. seperate 64 bits addr to two 4 bytes value and put them into param,
   then call tee_smc_call
*/

int uboot_verify_img(unsigned long start_addr, uint32_t lenth)
{

  smc_param *param = tee_common_call(FUNCTYPE_VERIFY_IMG, (uint32_t)start_addr, lenth);
  if (param->a0!=NO_ERROR) {//SM_ERR_PANIC may be returned due to tos panic
  	printf("uboot_verify_img() return error:param->a0=%d\n",param->a0);
	while (1);
  }
  return param->a0;
}

int uboot_vboot_verify_img(unsigned long start_addr, uint32_t lenth)
{
  smc_param *param = tee_common_call(FUNCTYPE_VBOOT_VERIFY_IMG, (uint32_t)start_addr, lenth);
  if (param->a0!=NO_ERROR) {//SM_ERR_PANIC may be returned due to tos panic
	printf("uboot_vboot_verify_img() return error:param->a0=%d\n",param->a0);
	while (1);
  }
  return param->a0;
}

int uboot_verify_product_sn_signature(unsigned long start_addr, uint32_t lenth){
	smc_param *param = tee_common_call(FUNCTYPE_VERIFY_PRODUCT_SN_SIGNATURE, (uint32_t)start_addr, lenth);
	if (param->a0 != NO_ERROR) {
		printf("uboot_verify_product_sn_signature() return error:param->a0=%d\n",param->a0);
		while (1);
	}
	return param->a0;
}

int uboot_config_os_version(unsigned long start_addr, uint32_t lenth){
	smc_param *param = tee_common_call(FUNCTYPE_CONFIG_OS_VERSION, (uint32_t)start_addr, lenth);
	if (param->a0 != NO_ERROR) {
		printf("uboot_config_os_version() return error:param->a0=%d\n",param->a0);
		while (1);
	}
	return param->a0;
}

int uboot_set_root_of_trust(unsigned long start_addr, uint32_t lenth){
	smc_param *param = tee_common_call(FUNCTYPE_SET_ROOT_OF_TRUST, (uint32_t)start_addr, lenth);
	if (param->a0 != NO_ERROR) {
		printf("uboot_set_root_of_trust() return error:param->a0=%d\n",param->a0);
		while (1);
	}
	return param->a0;
}

int uboot_encrypt_data(uint64_t start_addr, uint64_t lenth){
  smc_param *param = tee_common_call(FUNCTYPE_CRYPTO_DATA, (uint32_t)start_addr, (uint32_t)lenth);
  return param->a0;
}

int uboot_verify_pwd(uint64_t start_addr, uint64_t lenth){
  smc_param *param = tee_common_call(FUNCTYPE_CHECK_PWD, (uint32_t)start_addr, (uint32_t)lenth);
  return param->a0;
}

int uboot_verify_lockstatus(uint64_t start_addr, uint64_t lenth){
  smc_param *param = tee_common_call(FUNCTYPE_CHECK_LOCK_STATUS, (uint32_t)start_addr, (uint32_t)lenth);
  return param->a0;
}

int uboot_vboot_set_ver(unsigned long start_addr, uint32_t lenth)
{
  smc_param *param = tee_common_call(FUNCTYPE_VBOOT_SET_VERSION, (uint32_t)start_addr, lenth);
  return param->a0;
}

static void disable_debug_control_signal(void)
{
#if defined (CONFIG_SPRD_SECBOOT)
	//sprd_ap_efuse_prog(BLOCK_NUM_3,DISABLE_SPRD_DEBUG_CONTROL);
#endif
#if defined (CONFIG_SANSA_SECBOOT)
    sprd_ap_efuse_prog(BLOCK_NUM_3,DISABLE_DX_DEBUG_CONTROL);
#endif
}

int uboot_program_efuse(uint64_t start_addr, uint64_t lenth){

  disable_debug_control_signal();

  ap_sansa_efuse_prog_power_on();

  smc_param *param = tee_common_call(FUNCTYPE_PROGRAM_EFUSE, (uint32_t)start_addr, (uint32_t)lenth);

  ap_sansa_efuse_power_off();
  printf("pro_ret=%x\n",param->a0);
  return param->a0;
}

int uboot_get_socid(uint64_t start_addr, uint64_t lenth){

  ap_sansa_efuse_prog_power_on();

  smc_param *param = tee_common_call(FUNCTYPE_GET_SOCID, (uint32_t)start_addr, (uint32_t)lenth);

  ap_sansa_efuse_power_off();
  return param->a0;
}

int uboot_update_swVersion(uint64_t start_addr, uint64_t lenth){

  smc_param *param = tee_common_call(FUNCTYPE_UPDATE_VERSION, (uint32_t)start_addr, (uint32_t)lenth);
  return param->a0;
}

int uboot_sansa_get_lcs(uint32_t *p_lcs){

   ap_sansa_efuse_prog_power_on();

   smc_param *param = tee_common_call(FUNCTYPE_GET_SANSA_LCS, 0, 0);
   *p_lcs = param->a2;

   ap_sansa_efuse_power_off();
   printf("lcsval=%d\n",param->a2);
   return param->a0;
}

int uboot_sansa_set_rma(uint32_t *p_rmaret){

   ap_sansa_efuse_prog_power_on();

   smc_param *param = tee_common_call(FUNCTYPE_SET_SANSA_RMA, 0, 0);

   *p_rmaret = param->a2;

   ap_sansa_efuse_power_off();
   printf("setrma=%d\n",param->a2);
   return param->a0;
}

int uboot_kce_program(uint64_t start_addr, uint64_t lenth){

  ap_sansa_efuse_prog_power_on();

  smc_param *param = tee_common_call(FUNCTYPE_KCE_PROGRAM, (uint32_t)start_addr, (uint32_t)lenth);

  ap_sansa_efuse_power_off();
  printf("kce_pro=%x\n",param->a0);
  return param->a0;
}

int uboot_get_hbk(uint64_t start_addr, uint64_t lenth){

#if defined (CONFIG_SANSA_SECBOOT)
  ap_sansa_efuse_prog_power_on();
#endif
  smc_param *param = tee_common_call(FUNCTYPE_GET_HBK, (uint32_t)start_addr, (uint32_t)lenth);
#if defined (CONFIG_SANSA_SECBOOT)
  ap_sansa_efuse_power_off();
#endif
  return param->a0;
}

/*add fastboot cmd for sharkl2*/
#ifdef CONFIG_SECBOOT
int get_lcs(uint32_t *p_lcs){
	smc_param *param = tee_common_call(FUNCTYPE_GET_LCS, p_lcs, sizeof(uint32_t));
	return param->a0;
}

int get_socid(uint64_t start_addr, uint64_t lenth){
	smc_param *param = tee_common_call(FUNCTYPE_GET_SOCID, (uint32_t)start_addr, (uint32_t)lenth);
	return param->a0;
}

int set_rma(void){
	smc_param *param = tee_common_call(FUNCTYPE_SET_RMA, 0, 0);
	return param->a0;
}
#endif


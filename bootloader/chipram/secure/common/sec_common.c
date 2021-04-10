#include <security/sprdsec_header.h>
#include <security/sprd_rsa.h>
#include <security/sec_string.h>
#include <security/sprd_sha.h>
#include <security/sec_common.h>
#ifdef CONFIG_SANSA_SECBOOT
#include <security/sansa/dx_header.h>
#include <security/sansa/secureboot_defs.h>
#include <security/sansa/bootimagesverifier_def.h>
#endif

imgToVerifyInfo img_verify_info = {0};

/****************************************************************************
 *this function is unify interface for tshak whale_sprd & sansa secboot plan
 * in boot process
 * tshak plan use the function which named secure_check need four param
 *
 * whale_sprd:
 *      ptr: address which the pre img loaded
 *       m : address which img will be verified loaded
 *       n : NULL
 *   data_len: NULL
 *
 *   sansa:
 *            need supplement
 *  tshark:
 *           need supplement
 *
 *
 * **************************************************************************/
SecBoot_Result_Ret secboot_verify(void *ptr,void *m,void *n,uint32_t data_len,SECURE_TYPE type)
{
    SecBoot_Result_Ret ret = SECBOOT_VERIFY_SUCCESS;
#ifdef CONFIG_SPRD_SECBOOT
	ret = sprd_secure_check((uint8_t *)ptr,(uint8_t *)m);
#endif
#ifdef CONFIG_SANSA_SECBOOT
	ret = sansa_secure_check(ptr,m,type);
#endif
#ifdef CONFIG_NORMAL_SECBOOT
	/*pls add thark progtamme interface*/
#endif

    return ret;
}
/*************************************************************************
 *dl_secure_verify: verify function in download process
 *
 *partition_name:  the partition name which pubkeyhash stored
 *
 *header: address of img which will be verified loaded
 *
 *code :   used for tshark plan
 *
 ************************************************************************/
void dl_secure_verify(void *partition_name,void *header,void *code)
{
#ifdef CONFIG_SPRD_SECBOOT

#endif
#ifdef CONFIG_SANSA_SECBOOT

#endif
#ifdef CONFIG_NORMAL_SECBOOT
	secure_verify(partition_name,header,code);
#endif
}
#if 0
int secboot_enable_check(void)
{
//#if defined (CONFIG_SECBOOT)
	uint32_t reg = 0;
	uint32_t bonding = REG32(REG_AON_APB_BOND_OPT0);
	 // uint32_t bonding = (*((volatile uint32_t *)(REG_AON_APB_BOND_OPT0)));
	if(bonding & BIT_2){
		reg = __ddie_efuse_read(EFUSE_HASH_STARTID);
		if ((reg >> 31) & 0x1)
			return 1;
	}
//#endif
	return 0;
}
#endif
void  secboot_param_set(uint64_t load_buf,imgToVerifyInfo *imginfo)
{
	imginfo->img_addr = load_buf;
	imginfo->img_len = 0xa00000;
	imginfo->hash_len = 32;
}

void secboot_get_pubkhash(uint64_t img_buf,imgToVerifyInfo *imginfo)
{
#if defined (CONFIG_SPRD_SECBOOT)
	sprd_get_hash_key((uint8_t *)img_buf,(uint8_t *)imginfo->pubkeyhash);//be carefull! the first param in chipram is not same as uboot64
#endif
#if defined (CONFIG_SANSA_SECBOOT)
	/*pls add sansa get pubkey hash  from pre imgage function or not */
#endif
}

void update_swVersion(void)
{
#ifdef CONFIG_SPRD_SECBOOT
	sprd_update_swVersion();
#endif
#ifdef CONFIG_SANSA_SECBOOT
	__efuse_prog_power_on();
	sansa_update_swVersion();
	__efuse_power_off();
#endif
}

void secboot_init(void)
{
#ifdef CONFIG_SANSA_SECBOOT
    sansa_enable_efuse_EB();
    set_swVsersion_parameter_init();
#endif
}


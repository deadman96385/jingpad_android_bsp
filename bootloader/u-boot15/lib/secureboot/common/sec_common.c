#include <linux/types.h>
#include <secureboot/sprdsec_header.h>
#include <crypto/sprdrsa.h>
#include <secureboot/sec_string.h>
#include <crypto/sprdsha.h>
#include <secure_verify.h>
#include <asm/arch/sprd_reg.h>
#include <secureboot/sec_common.h>
#include <otp_helper.h>
#include <fdtdec.h>
#ifdef CONFIG_VBOOT_V2
#include <avb/uboot_avb_ops.h>
#include <avb/avb_footer.h>
#include "../avb/libavb/avb_slot_verify.h"
#endif
#include "sprd_common_rw.h"
#include "loader_common.h"

DECLARE_GLOBAL_DATA_PTR;

#define EFUSE_HASH_STARTID 2

#ifdef TOS_TRUSTY
imgToVerifyInfo *img_verify_info_tos;
VbootVerifyInfo *vboot_verify_info;
VbootUnlockVerifyInfo *vboot_unlock_verify_info;
#else
VbootVerifyInfo vboot_verify_info_s = {0};
VbootVerifyInfo *vboot_verify_info = &vboot_verify_info_s;
VbootUnlockVerifyInfo vboot_unlock_verify_info;
#endif
imgToVerifyInfo img_verify_info = {0};
uint8_t pubkhash[32];
VbootVerInfo vboot_ver_info __attribute__((aligned(4096))); /*must be PAGE ALIGNED*/
unsigned char vboot_para_partition_name[SEC_MAX_PARTITION_NAME_LEN] __attribute__((aligned(4096))); /*must be PAGE ALIGNED*/

#ifdef CONFIG_VBOOT_SYSTEMASROOT
unsigned char g_vboot_sys_cmdline[SPRD_VBOOT_SYSTEM_CMDLINE_MAXSIZE];
#endif
extern AvbSlotVerifyData* avb_slot_data[2];

static uchar *const s_force_secure_check[] = {
    "splloader",
	"sml",
	"trustos",
	"teecfg",
#ifdef CONFIG_X86
	"mobilevisor",
	"mvconfig",
	"secvm",
#endif
	"uboot",
#ifdef CONFIG_VBOOT_V2
	"vbmeta",
#endif
	"boot",
	"recovery",
	"wl_modem",
	"wl_ldsp",
	"wmodem",
	"wl_gdsp",
	"wl_warm",
	"pm_sys",
	"tl_ldsp",
	"tl_tgdsp",
	"tl_modem",
	"l_modem",
	"l_ldsp",
	"l_gdsp",
	"l_warm",
	"l_tgdsp",
	"l_agdsp",
#ifdef SHARKL5_CDSP
	"l_cdsp",
#endif
	"wdsp",
	"w_modem",
	"w_gdsp",
	"dtb",
	"dtbo",
	#ifdef CONFIG_SUPPORT_WIFI
	"wcnmodem",
	#endif
	#ifdef CONFIG_SYSTEM_VERIFY
	"system",
	#endif
	NULL
};

extern enVerifiedState g_verifiedbootstate;
static void dl_secure_verify(void *partition_name,void *tocheck_partition_name,void *header,void *code)
{
#ifdef CONFIG_SPRD_SECBOOT
#ifdef CONFIG_VBOOT_V2
	if(tocheck_partition_name != ""){
		sprd_dl_vboot_verify(partition_name, tocheck_partition_name, header, code);
	}else{
		sprd_dl_verify(partition_name, header, code);
	}
#else
	sprd_dl_verify(partition_name, header, code);
#endif
#elif defined CONFIG_SANSA_SECBOOT
	sansa_enable_efuse_EB();
	sansa_dl_secure_verify(partition_name,header,code);
#else
	secure_verify(partition_name,header,code);
#endif
}

static void fb_secure_verify(void *partition_name,void *tocheck_partition_name,void *header,void *code)
{
#ifdef CONFIG_SPRD_SECBOOT
#ifdef CONFIG_VBOOT_V2
	if(tocheck_partition_name != ""){
		sprd_fb_secure_vboot_verify(partition_name, tocheck_partition_name, header, code);
	}else{
		sprd_fb_secure_verify(partition_name, header, code);
	}
#else
	sprd_fb_secure_verify(partition_name, header, code);
#endif
#elif defined CONFIG_SANSA_SECBOOT
	sansa_fb_secure_verify(partition_name,header,code);
#else
	secure_verify(partition_name,header,code);
#endif
}

static int _check_secure_part(uchar * partition_name)
{
	int i = 0;
	do {
		if (SEC_TRUE == strcmp(s_force_secure_check[i], partition_name))
			return SEC_TRUE;
		i++;
	}
	while (s_force_secure_check[i] != 0);

	return SEC_FALSE;
}

uint32_t reversebytes_uint32t(uint32_t value){
    return (value & 0x000000FFU) << 24 | (value & 0x0000FF00U) <<  8 |
           (value & 0x00FF0000U) >> 8  | (value & 0xFF000000U) >> 24;
}

uint64_t reversebytes_uint64t(uint64_t value){
    uint64_t low_uint64;
    uint32_t high_uint64 = (uint64_t)reversebytes_uint32t((uint32_t)value);
    low_uint64 = (uint64_t)reversebytes_uint32t((uint32_t)(value >> 32));
    return (high_uint64 << 32) + low_uint64;
}

int secure_load_partition(char *partition_name, uint64_t size, uint64_t offset, char *ram_addr)
{
    sys_img_header    img_header;
    int               img_size = 0;
    uint64_t          head_off = 0;
    uint64_t          head_len = sizeof(sys_img_header);
    AvbFooter    *footer = NULL;

    if ((0 == strcmp(partition_name, "boot"))||(0 == strcmp(partition_name, "dtbo")) ||
	(0 == strcmp(partition_name, "recovery"))){
#if (!defined CONFIG_VBOOT_V2)
        if (0 != common_raw_read(partition_name, SYS_HEADER_SIZE, 0, (char*)&img_header))
            goto error;
        img_size = img_header.mImgSize;
        if (0 != common_raw_read(partition_name, img_size+CERT_SIZE, 0, ram_addr))
            goto error;
#else
    if(0 == common_raw_read(partition_name, AVB_FOOTER_SIZE,  size-AVB_FOOTER_SIZE, ram_addr+size-AVB_FOOTER_SIZE)) {
        footer = ram_addr+size-AVB_FOOTER_SIZE;
        if (0 == memcmp(footer->magic, AVB_FOOTER_MAGIC, AVB_FOOTER_MAGIC_LEN)) {
            if(0 != common_raw_read(partition_name, reversebytes_uint64t(footer->vbmeta_offset) +
                reversebytes_uint64t(footer->vbmeta_size), 0, ram_addr)) {
                goto error;
            }
        } else {
            if (0 != common_raw_read(partition_name,size, offset, (u8*)ram_addr))
                goto error;
        }
    }else {
        if (0 != common_raw_read(partition_name,size, offset, (u8*)ram_addr))
            goto error;
    }
#endif
    }
#if (defined CONFIG_VBOOT_V2)
    else if (0 == strcmp(partition_name, "vbmeta")) {
        // read vbmeta header in footer
        head_off = VBMETA_PARTITION_MAX_SIZE - SYS_HEADER_SIZE;
        if (0 != common_raw_read("vbmeta", head_len, head_off, (u8*)&img_header)) {
            goto error;
        }
        img_size = img_header.mImgSize;
        // read vbmeta payload
        if (0 != common_raw_read("vbmeta", size, 0, (u8*)ram_addr)) goto error;
        // integrity check for vbmeta
        if (check_sprdimgheader((uint8_t *)&img_header, ram_addr) != 0) {
            // check failed, try to read vbmeta from vbmeta_bak
            // read vbmeta header in footer
            if (0 != common_raw_read("vbmeta_bak", head_len, head_off, (u8*)&img_header)) {
                goto error;
            }
            img_size = img_header.mImgSize;
            // read vbmeta payload
            if (0 != common_raw_read("vbmeta_bak", size, 0, (u8*)ram_addr)) goto error;
            // integrity check for vbmeta_bak
            if (check_sprdimgheader((uint8_t *)&img_header, ram_addr) != 0) {
                secf("error:check dual backup hash failed for vbmeta.img.\n");
                while (1);
            }
        }
    }
#endif
    else if (0 != common_raw_read(partition_name,size, offset, (u8*)ram_addr))
            goto error;
    return img_size;
error:
    errorf("read %s partition fail\n", partition_name);
    return -1;
}

static void secboot_get_pubkhash(uint64_t img_buf,uint64_t imginfo)
{
#if defined (CONFIG_SPRD_SECBOOT)
	sprd_get_hash_key((uint8_t *)img_buf,(uint8_t *)imginfo);//be carefull! the first param in chipram is not same as uboot64
#endif
#if defined (CONFIG_SANSA_SECBOOT)
	sansa_get_hash_key((uint8_t *)img_buf,(uint8_t *)imginfo);
#endif
}

void  secboot_param_set(uint64_t load_buf,imgToVerifyInfo *imginfo)
{
	imginfo->img_addr = load_buf;
	imginfo->img_len = SIMG_BUF;
	imginfo->hash_len = 32;
	imginfo->pubkeyhash = pubkhash;
#if defined(CONFIG_SPRD_SECBOOT) || defined(CONFIG_VBOOT_V2)
	imginfo->flag = SPRD_FLAG;
#endif
#ifdef CONFIG_SANSA_SECBOOT
    sansa_enable_efuse_EB();
	imginfo->flag = SANSA_FLAG;
#endif
}

int secure_efuse_program(void)
{
	int ret = 0;

#if defined(CONFIG_SANSA_SECBOOT)
			printf("###### secure_efuse_program ######\n");
			ret = secure_efuse_program_sansa();
#endif

#if defined(CONFIG_SPRD_SECBOOT)
			//ret = secure_efuse_program_sprd(); /*wait for efuse driver ready*/
#endif

#if defined(CONFIG_SECURE_BOOT)
			ret = secure_efuse_program_native();
#endif
	return ret;
}

VERIFY_RESULT dl_secure_process_flow(ulong * strip, unsigned char * part_name,
			uint32_t rcv_size, uint32_t total_size, unsigned char * buf)
{
	static uint32_t rcv_already = 0;
	int ret = 0;

	set_current_dl_partition((const char*)part_name);
#ifdef PRODUCT_USE_DYNAMIC_PARTITIONS
        if (0 == memcmp(part_name, BOOT_PART, strlen(part_name))){
               return VERIFY_NO_NEED;
        }
#endif

	if (SEC_FALSE == _check_secure_part(part_name))	{
	    debugf("%s partition isn't secure image need to verify \n",part_name);
		return VERIFY_NO_NEED;
	}
#ifdef CONFIG_SECURE_BOOT
	if (1 != secure_header_parser(buf)) {
		errorf("check secure image failed!! \n");
		return VERIFY_FAIL;
	}
#endif

	if (SEC_TRUE == strcmp("uboot", part_name)) {
		dl_secure_verify("splloader", "", buf, 0);
	} else if (SEC_TRUE == strcmp("splloader", part_name)) {
		dl_secure_verify("splloader0", "", buf, 0);
	}
#ifdef CONFIG_SECBOOT
	else if ((SEC_TRUE == strcmp("sml",part_name))||(SEC_TRUE == strcmp("trustos",part_name))
				||(SEC_TRUE == strcmp("teecfg",part_name))
				||(SEC_TRUE == strcmp("mobilevisor",part_name))
				||(SEC_TRUE == strcmp("mvconfig",part_name))
				||(SEC_TRUE == strcmp("secvm",part_name))){
			dl_secure_verify("fdl1","",buf,0);
	}
#endif
#ifdef CONFIG_SECURE_BOOT
	else if (0 == strcmp("system", part_name)) {
		if (0 == rcv_already) {
			Sec_SHA1_Start();
			*strip = VLR_CODE_OFF;
		}
		secure_verify_system_start("fdl2", buf, rcv_size);
		rcv_already += rcv_size;
		if (total_size == rcv_already) {
			debugf("Check system image \n");
			Sec_SHA1_Finish();
			ret = secure_verify_system_end("fdl2", buf, 0);
			debugf("secure_verify_system  ret = %d \n", ret);
			if (0 == ret)
				return VERIFY_FAIL;
			else
				return VERIFY_OK;
		}
	}
#endif
	else {
#ifdef CONFIG_VBOOT_V2
		if((0 == strcmp("splloader", part_name)) ||\
			(0 == strcmp("uboot", part_name)) ||\
			(0 == strcmp("sml", part_name)) ||\
			(0 == strcmp("teecfg", part_name)) ||\
			(0 == strcmp("trustos", part_name))) {
			dl_secure_verify("fdl2","",buf,0);
		} else {
			debugf("download vboot check images. \n");
			dl_secure_verify("fdl2",part_name,buf,0);
		}
#else
		dl_secure_verify("fdl2","",buf,0);
#endif
	}

	return VERIFY_OK;
}

VERIFY_RESULT fb_secure_process_flow(ulong * strip, unsigned char * part_name,
			uint32_t rcv_size, uint32_t total_size, unsigned char * buf)
{
	static uint32_t rcv_already = 0;
	int ret = 0;
	uint32_t rpmb_version = 0;

#ifdef PRODUCT_USE_DYNAMIC_PARTITIONS
        if ((0 == memcmp(part_name, BOOT_PART, strlen(part_name)))
                &&(get_lock_status() == VBOOT_STATUS_UNLOCK)){
               return VERIFY_NO_NEED;
        }
#endif

	if (SEC_FALSE == _check_secure_part(part_name)){
		debugf("%s not secure image need to verify \n",part_name);
		return VERIFY_NO_NEED;
		}
#ifdef CONFIG_SECURE_BOOT
	if (1 != secure_header_parser(buf)) {
		errorf("check secure image failed!! \n");
		return VERIFY_FAIL;
	}
#endif
	#ifdef CONFIG_NONTRUSTY_ANTIROLLBACK
		ret = sprd_get_imgversion(0, &rpmb_version);
		if(!ret) {
			debug("read rpmb version: %d,ret = %d\n", rpmb_version,ret);
		} else {
			debug(">>>>> Warning:read rollback version return error! ret = %d\n",ret);
			rpmb_version = 0;
		}
		debug("Transfer non_trusty rollback_version here! rpmb_version = %d\n",rpmb_version);
		uboot_vboot_set_ver(rpmb_version, sizeof(rpmb_version));
	#endif

	if (SEC_TRUE == strcmp("uboot", part_name)) {
		fb_secure_verify("splloader", "", buf, 0);
	} else if (SEC_TRUE == strcmp("splloader", part_name)) {
		fb_secure_verify("splloader0", "", buf, 0);
	}
#ifdef CONFIG_SECBOOT
	else if ((SEC_TRUE == strcmp("sml",part_name))||(SEC_TRUE == strcmp("trustos",part_name))
				||(SEC_TRUE == strcmp("teecfg",part_name))
				||(SEC_TRUE == strcmp("mobilevisor",part_name))
				||(SEC_TRUE == strcmp("mvconfig",part_name))
				||(SEC_TRUE == strcmp("secvm",part_name))) {
			fb_secure_verify("splloader","",buf,0);
	}
#endif
#ifdef CONFIG_SECURE_BOOT
	else if (0 == strcmp("system", part_name)) {
		if (0 == rcv_already) {
			Sec_SHA1_Start();
			*strip = VLR_CODE_OFF;
		}
		secure_verify_system_start("fdl2", buf, rcv_size);
		rcv_already += rcv_size;
		if (total_size == rcv_already) {
			debugf("Check system image \n");
			Sec_SHA1_Finish();
			ret = secure_verify_system_end("fdl2", buf, 0);
			debugf("secure_verify_system  ret = %d \n", ret);
			if (0 == ret)
				return VERIFY_FAIL;
			else
				return VERIFY_OK;
		}
	}
#endif
	else {
#ifdef CONFIG_VBOOT_V2
		if((0 == strcmp("splloader", part_name)) ||\
			(0 == strcmp("uboot", part_name)) ||\
			(0 == strcmp("sml", part_name)) ||\
			(0 == strcmp("teecfg", part_name)) ||\
			(0 == strcmp("trustos", part_name))) {
			fb_secure_verify("uboot","",buf,0);
		} else {
			debugf("fastboot download vboot check images. \n");
			fb_secure_verify("uboot",part_name,buf,0);
		}
#else
		fb_secure_verify("uboot","",buf,0);
#endif
	}

	return VERIFY_OK;
}

int get_secboot_base_from_dt(void)
{
	int str_len = 0, offset;
	unsigned long base, size;
	char nodename[256];
	char *pStr = NULL;
	const void *fdt_blob = gd->fdt_blob;
	int parentoffset = fdt_path_offset(fdt_blob, "/reserved-memory");

	if (parentoffset < 0) {
		debugf("fdt_reserved_mem_multimedia_parse: cann't find mm_reserved \n");
		return -1;
	}

	for (offset = fdt_first_subnode(fdt_blob, parentoffset);
		 offset >= 0; offset = fdt_next_subnode(fdt_blob, offset)) {
		sprintf(nodename, "%s", fdt_get_name(fdt_blob, offset, NULL));
		str_len = strlen(nodename);
		nodename[str_len] = '\0';

		pStr = strstr(nodename,"secboot-arg-mem");
		if (pStr) {
			if (fdtdec_decode_region(fdt_blob, offset, "reg", &base, &size) < 0) {
				debugf("cannot find reg prop, go to next node.\n" );
				goto next;
			}
			gd->arg_start_base = base;
		}

		pStr = strstr(nodename,"secboot-vbmeta-mem");
		if (pStr) {
			if (fdtdec_decode_region(fdt_blob, offset, "reg", &base, &size) < 0) {
				debugf("cannot find reg prop, go to next node.\n" );
				goto next;
			}
			gd->vbmeta_img_base = base;
		}

		pStr = strstr(nodename,"secboot-verify-mem");
		if (pStr) {
			if (fdtdec_decode_region(fdt_blob, offset, "reg", &base, &size) < 0) {
				debugf("cannot find reg prop, go to next node.\n" );
				goto next;
			}
			gd->verify_base = base;
		}

next:;
	}

	debugf("gd->arg_start_base: 0x%08x, gd->vbmeta_img_base: 0x%08x, gd->verify_base: 0x%08x\n",
					gd->arg_start_base, gd->vbmeta_img_base, gd->verify_base);

	if (!gd->arg_start_base || !gd->vbmeta_img_base || !gd->verify_base) {
		debugf("secboot base address error\n");
		return -1;
	}

#ifdef TOS_TRUSTY
	img_verify_info_tos = (imgToVerifyInfo *)gd->arg_start_base;
	vboot_verify_info = (VbootVerifyInfo *)gd->arg_start_base;
	vboot_unlock_verify_info = (VbootUnlockVerifyInfo *)gd->arg_start_base;
#endif

	return 0;
}


void secboot_init(char *partition_name)
{
	int ret = 0;
	uint32_t rpmb_version = 0;
	VERIFY_PROCESS_FLAG process_flag = VERIFY_PROCESS_BOOT;

	if (ret = get_secboot_base_from_dt()) {
		debugf("Getting secure boot base failed\n");
		while(ret);
	}

#if defined (CONFIG_SANSA_SECBOOT)
	sansa_calc_hbk();
#endif
#ifdef CONFIG_VBOOT_V2
	/*malloc one memory to vbmeta image buffer use. ok? 2KB*/
	debugf("gd->verify_base:0x%x, KERNEL_ADR:0x%x. \n", gd->verify_base, KERNEL_ADR);
	vboot_secure_process_prepare();
	vboot_secure_process_init(partition_name, gd->verify_base, gd->vbmeta_img_base, NULL, process_flag);
#endif
#ifdef CONFIG_SPRD_SECBOOT
#ifdef CONFIG_NONTRUSTY_ANTIROLLBACK
	ret = sprd_get_imgversion(0, &rpmb_version);
	if(!ret) {
		debug("read rpmb version: %d,ret = %d\n", rpmb_version,ret);
	} else {
		debug(">>>>> Warning:read rollback version return error! ret = %d\n",ret);
		rpmb_version = 0;
	}
	debug("Transfer non_trusty rollback_version here! rpmb_version = %d\n",rpmb_version);
	uboot_vboot_set_ver(rpmb_version, sizeof(rpmb_version));
#endif
#endif
}

void secboot_terminal(void)
{
	#if defined (CONFIG_SPRD_SECBOOT) || defined (CONFIG_VBOOT_V2)
	secboot_param_set(gd->verify_base,&img_verify_info);
	sprd_calc_hbk();
	#endif
}

#ifdef CONFIG_VBOOT_V2
static void vboot_replace_vbmeta_size_and_digest(void) {
    AvbSlotVerifyResult ret = AVB_SLOT_VERIFY_RESULT_OK;
	avb_ops_new();
	ret = (AvbSlotVerifyResult)avb_check_image(NULL);
	debugf("avb_check_image() ret is %d.\n", ret);

	if (((AVB_SLOT_VERIFY_RESULT_OK == ret) ||
		(VBOOT_STATUS_UNLOCK == get_lock_status())) &&
		avb_slot_data[0]) {
		debugf("avb_slot_data[0]->cmdline is %s.\n", avb_slot_data[0]->cmdline);

		const char * np_vbmeta_size = strstr(avb_slot_data[0]->cmdline, "androidboot.vbmeta.size");
		const char * np_vbmeta_digest = strstr(avb_slot_data[0]->cmdline, "androidboot.vbmeta.invalidate_on_error");
		const char * op_vbmeta_size = strstr(g_sprd_vboot_cmdline, "androidboot.vbmeta.size");
		const char * op_vbmeta_digest = strstr(g_sprd_vboot_cmdline, "androidboot.vbmeta.digest");

		if(np_vbmeta_size && np_vbmeta_digest &&
			op_vbmeta_size && op_vbmeta_digest) {
			strncpy((char *)op_vbmeta_size, np_vbmeta_size, (size_t)(np_vbmeta_digest - np_vbmeta_size));
			g_sprd_vboot_cmdline[SPRD_VBOOT_CMDLINE_MAXSIZE-1] = '\0';
			printf("g_sprd_vboot_cmdline is %s.\n", g_sprd_vboot_cmdline);
		}
	}

}
#endif

static char* bin2hex(const uint8_t* data, size_t data_len) {
	const char hex_digits[17] = "0123456789abcdef";
	char* hex_data;
	size_t n;

	hex_data = malloc(data_len * 2);
	if (hex_data == NULL) {
		return NULL;
	}

	for (n = 0; n < data_len; n++) {
		hex_data[n * 2] = hex_digits[data[n] >> 4];
		hex_data[n * 2 + 1] = hex_digits[data[n] & 0x0f];
	}

	return hex_data;
}

static void vboot_get_root_of_trust_str(char* root_of_trust, uint8_t* image_verify_result)
{
	char* additional_cmdline = root_of_trust;
	const char hex_digits[17] = "0123456789abcdef";
	char* pubkey = NULL;
	char* verify_result = NULL;
	uint32_t len = 0;

	if (root_of_trust == NULL || image_verify_result == NULL) {
		debugf("root_of_trust NULL.\n");
		return;
	}

	/* Initialize root_of_trust_str */
	memset(root_of_trust_str, 0, ROOT_OF_TRUST_MAXSIZE);

	/* Get vbmeta.pubkey */
	strcpy(additional_cmdline, "androidboot.vbmeta.pubkey");
	additional_cmdline = additional_cmdline + strlen("androidboot.vbmeta.pubkey");
	*additional_cmdline++= '=';
	if ((pubkey = bin2hex(g_sprd_vboot_key, g_sprd_vboot_key_len)) == NULL) {
		debugf("pubkey NULL.\n");
		return;
	}
	memcpy(additional_cmdline, (char *)pubkey, g_sprd_vboot_key_len*2);
	free(pubkey);
	additional_cmdline = additional_cmdline + g_sprd_vboot_key_len*2;
	*additional_cmdline++= ' ';

	/* Get verify.result */
	strcpy(additional_cmdline, "androidboot.verify.result");
	additional_cmdline = additional_cmdline + strlen("androidboot.verify.result");
	*additional_cmdline++= '=';
	len = sizeof(uint32_t);
	if ((verify_result = bin2hex((const int8_t*)image_verify_result, len)) == NULL) {
		debugf("verify_result NULL.\n");
		return;
	}
	memcpy(additional_cmdline, verify_result, len*2);
	free(verify_result);
	additional_cmdline = additional_cmdline + len*2;
	*additional_cmdline++= ' ';

	if (additional_cmdline - root_of_trust + strlen(g_sprd_vboot_cmdline)
			> ROOT_OF_TRUST_MAXSIZE) {
		debugf("root_of_trust overflow. \n");
		return;
	}

	/* Get command_line */
	memcpy(additional_cmdline, g_sprd_vboot_cmdline, strlen(g_sprd_vboot_cmdline));
}

void secboot_secure_process_flow(char *partition_name, uint64_t size, uint64_t offset, char *ram_addr)
{
    uint32_t ret = 1;
    static bool system_vendor_product_done = false;
    static bool dtb_dtbo_done = false;

#ifdef CONFIG_VBOOT_V2
	//vboot_secure_process_flow(partition_name);
#ifdef CONFIG_VBOOT_SYSTEMASROOT
    debug("check dtb & dtbo \n");
    if (!dtb_dtbo_done) {
        vboot_secure_process_flow("dtb");
        vboot_secure_process_flow("dtbo");
        dtb_dtbo_done = true;
    }
#elif defined PRODUCT_USE_DYNAMIC_PARTITIONS
    debug("verify boot check dtbo \n");
    if (!dtb_dtbo_done) {
        vboot_secure_process_flow("dtbo");
        dtb_dtbo_done = true;
    }
#endif

#ifdef CONFIG_DMVERITY_DISABLE
    debug("skip to check system & vendor version.\n");
#else
	//secboot_secure_process_flow may be called several times, but system/vendor,only need to be checked on time
    debug("begin to check system & vendor & product version.\n");
    if (!system_vendor_product_done && g_DeviceStatus != VBOOT_STATUS_UNLOCK)
    {
        if (0 != memcmp(partition_name, RECOVERY_PART, strlen(RECOVERY_PART)))
        {
#ifdef PRODUCT_USE_DYNAMIC_PARTITIONS
            vboot_secure_process_flow("vbmeta_system");
            vboot_secure_process_flow("vbmeta_vendor");
            vboot_verify_vbmeta("socko");
            vboot_verify_vbmeta("odmko");
#else
            vboot_verify_vbmeta("system");
            vboot_verify_vbmeta("vendor");
#endif
#if defined (BOARD_PRODUCTIMAGE_PARTITION_SIZE)
            vboot_verify_vbmeta("product");
#endif
        } else {
            debug("skip check system & vendor & product in recovery mode.\n");
        }
        system_vendor_product_done = true;
    }
#endif
#else
	if (-1 == secure_load_partition(partition_name,size,offset,ram_addr)){
		while(ret);
	}

#if defined (TOS_TRUSTY)
	secboot_param_set(gd->verify_base,img_verify_info_tos);
	img_verify_info_tos->pubkeyhash = (uint8_t*)gd->arg_start_base+PAGE_ALIGN;
	secboot_get_pubkhash(UBOOT_START,img_verify_info_tos->pubkeyhash);

	printf("p1:%llx, p2:%llx,P3:%llx,p4:%llx,p5:%llx\n",img_verify_info_tos->img_addr,img_verify_info_tos->img_len,img_verify_info_tos->pubkeyhash,img_verify_info_tos->hash_len,img_verify_info_tos->flag);
	ret = uboot_verify_img((imgToVerifyInfo*)img_verify_info_tos,sizeof(imgToVerifyInfo));
	while(ret);
#else
	secboot_param_set(gd->verify_base,&img_verify_info);
	secboot_get_pubkhash(UBOOT_START,img_verify_info.pubkeyhash);
	uboot_verify_img(&img_verify_info,sizeof(imgToVerifyInfo));
#endif
#endif

#ifdef CONFIG_VBOOT_V2
#ifdef PRODUCT_USE_DYNAMIC_PARTITIONS
	vboot_replace_vbmeta_size_and_digest();
#endif
#endif

	/* Get root_of_trust_str for KM4.0 */
	vboot_get_root_of_trust_str(root_of_trust_str,
			(uint8_t*)&(vboot_verify_info->verify_return_data->vboot_verify_ret));
}

#ifdef CONFIG_VBOOT_V2
void vboot_secure_process_init(char *partition_name, char *img_ram_addr, char * vbmeta_ram_addr, sys_img_header *header, VERIFY_PROCESS_FLAG flag)
{
	antirb_image_type tmp_type;
	uint64_t partition_size = 0;
	uint8_t * avb_vboot_key = NULL;
	uint32_t avb_vboot_key_len = 0;
	int img_size;

	if(!partition_name){
		debugf("para is invalid\n");
		return;
	}

	memset(vboot_verify_info, 0, sizeof(VbootVerifyInfo));

	/*public op1: when check vbmeta & other imgs(like boot.)*/
	if (-1 == secure_get_partition_size(partition_name, &partition_size)){
		debugf("get %s partition size fail\n", partition_name);
		return;
	}
	if(strcmp("vbmeta",partition_name) == 0){
		/*Info: when check vbmeta, img para should be null.*/
		vboot_verify_info->img_len = 0;
		vboot_verify_info->img_addr = NULL;

		vboot_verify_info->vbmeta_img_addr = vbmeta_ram_addr;

		switch (flag){
		case VERIFY_PROCESS_DOWNLOAD:
			debugf("In download mode\n");
			if (NULL == header){
				debugf("sys_img_header empty\n");
				return;
			}
			vboot_verify_info->vbmeta_img_len = header->mImgSize;
			break;

		case VERIFY_PROCESS_BOOT:
			debugf("In boot mode\n");
			img_size =  secure_load_partition("vbmeta",partition_size,
					(uint64_t)0, vboot_verify_info->vbmeta_img_addr);
			if (-1 == img_size){
				debugf("load vbmeata partition error\n");
				return;
			}
			vboot_verify_info->vbmeta_img_len = (uint32_t)(img_size);
			break;
		default:
			debugf("flag error\n");
			return;
		}

		debugf("partintion:%s, partition_size:0x%llx.\n", "vbmeta", vboot_verify_info->vbmeta_img_len);

		debugf("img_ram_addr:0x%x.   vbmeta_ram_addr:0x%x. \n", img_ram_addr, vbmeta_ram_addr);

		vboot_verify_info->vb_cmdline_addr = NULL;
		vboot_verify_info->vb_cmdline_len = 0;
	}else{
		vboot_verify_info->img_len = (uint32_t)partition_size;
		vboot_verify_info->img_addr = img_ram_addr;

		if (-1 == secure_get_partition_size("vbmeta", &partition_size)) {
			debugf("get vbmeta partition size fail\n");
			return;
		}

		vboot_verify_info->vbmeta_img_addr = vbmeta_ram_addr;

		img_size =  secure_load_partition("vbmeta",partition_size,
					(uint64_t)0, vboot_verify_info->vbmeta_img_addr);
		if (-1 == img_size){
			debugf("load vbmeta partition error\n");
			return;
		}

		vboot_verify_info->vbmeta_img_len = (uint32_t)(img_size);

		debugf("partintion:%s, partition_size:0x%llx\n", partition_name, vboot_verify_info->img_len);

		debugf("partintion:%s, partition_size:0x%llx.\n", "vbmeta", vboot_verify_info->vbmeta_img_len);

		debugf("img_ram_addr:0x%x.   vbmeta_ram_addr:0x%x. \n", img_ram_addr, vbmeta_ram_addr);


		memset((char *)g_sprd_vboot_cmdline, 0, sizeof(g_sprd_vboot_cmdline));
		vboot_verify_info->vb_cmdline_addr = (char *)g_sprd_vboot_cmdline;
		vboot_verify_info->vb_cmdline_len = sizeof(g_sprd_vboot_cmdline);

		memset(g_sprd_vboot_ret, 0, sizeof(g_sprd_vboot_ret));
		vboot_verify_info->verify_return_data = (VBootResultInfo *)g_sprd_vboot_ret;
		vboot_verify_info->verify_return_data_len = sizeof(VBootResultInfo);

		debugf("g_sprd_vboot_cmdline:0x%x.   g_sprd_vboot_cmdline_len:%d.   \n", (char *)g_sprd_vboot_cmdline, sizeof(g_sprd_vboot_cmdline));
		debugf("g_sprd_vboot_ret:0x%x.   g_sprd_vboot_ret_len:%d.   \n", g_sprd_vboot_ret, sizeof(g_sprd_vboot_ret));
	}

	/*public op2: when check vbmeta & other imgs(like boot.)*/
	vboot_verify_info->vbmeta_pubkey_addr = (char *)g_sprd_vboot_key;
	vboot_verify_info->vbmeta_pubkey_len = g_sprd_vboot_key_len;

	debugf("g_sprd_vboot_key:0x%x.   g_sprd_vboot_key_len:%d.   \n", g_sprd_vboot_key, g_sprd_vboot_key_len);

	//read version from rpmb block
	memset(&vboot_ver_info, 0, sizeof(VbootVerInfo));
	sprd_get_all_imgversion(&vboot_ver_info);
#ifdef CONFIG_VBOOT_DUMP
	debugf("dump vboot_ver_info.img_ver \n");
	do_hex_dump((void *)&vboot_ver_info, sizeof(VbootVerInfo));
#endif
	//pass the version msg to tos
	uboot_vboot_set_ver((VbootVerInfo*)(&vboot_ver_info),sizeof(VbootVerInfo));
}

/*
verify the vbmeta struct only, maily for hashtree image like system/vendor to do antirollback in bootloader
*/
void vboot_verify_vbmeta(char *partition_name)
{
    uint64_t     partition_size=0;
    char        *footer_buf;
    AvbFooter    footer;
    int8_t       vb_ret = 0;

    if (!partition_name) {
        debugf("Error: partition_name is null. \n");
        return;
    }
    debugf("partition_name: %s \n", partition_name);
    // step1:read avbfooter
    secure_get_partition_size(partition_name, &partition_size);
    footer_buf = vboot_verify_info->img_addr;
    if (-1 == secure_load_partition(partition_name, AVB_FOOTER_SIZE, partition_size-AVB_FOOTER_SIZE, footer_buf)){
        debugf("load %s partition error.\n", partition_name);
        goto fail;
    }
    // step2:read vbmeta according to the avbfooter
    if (!avb_footer_validate_and_byteswap((const AvbFooter*)footer_buf, &footer)) {
        debugf("Error validating footer.\n");
        goto fail;
    }
    debugf("footer.vbmeta_offset=0x%x,footer.vbmeta_size=0x%x\n",footer.vbmeta_offset,footer.vbmeta_size);
    vboot_verify_info->img_len=footer.vbmeta_size;
#ifdef CONFIG_VBOOT_DUMP
    dumpHex(partition_name,  (uchar *)vboot_verify_info->img_addr, AVB_FOOTER_SIZE);
#endif
    if(-1 == secure_load_partition(partition_name,footer.vbmeta_size, footer.vbmeta_offset,vboot_verify_info->img_addr)) {
        debugf("load %s partition error.\n", partition_name);
        goto fail;
    }
#ifdef CONFIG_VBOOT_DUMP
    dumpHex(partition_name, (uchar *)vboot_verify_info->img_addr, vboot_verify_info->img_len);
#endif
    memset(vboot_para_partition_name, 0, sizeof(vboot_para_partition_name));
    strcpy(vboot_para_partition_name, partition_name);
    vboot_verify_info->img_name = vboot_para_partition_name;
    vboot_verify_info->img_name_len = SEC_MAX_PARTITION_NAME_LEN;
    debugf("vboot_verify_info->img_name :%s. \n", vboot_verify_info->img_name);
    // step3:send the vbmeta struct and partname to tos to check the rollback version
    uboot_vboot_verify_img((VbootVerifyInfo*)vboot_verify_info,sizeof(VbootVerifyInfo));
#ifdef CONFIG_VBOOT_SYSTEMASROOT
    // step4: parse kernel cmdline from system image
    if(strcmp("system", partition_name) == 0) {
        debugf("parse kernel cmdline start\n");
        avb_ops_new();
        vb_ret = avb_check_image(partition_name);
        debugf("check image ret = %d\n", vb_ret);
        if (vb_ret != 0) goto fail;
        memset(g_vboot_sys_cmdline, 0, sizeof(g_vboot_sys_cmdline));
        strcpy(g_vboot_sys_cmdline, avb_slot_data[0]->cmdline);
        debugf("g_vboot_sys_cmdline: %s\n", g_vboot_sys_cmdline);
    }
#endif
    return;

fail:
    while (1);
}

void vboot_secure_process_flow_cm4(char *partition_name)
{
	int ret;
	uint32_t vboot_check_result;
	uint64_t partition_size=0;
	uint64_t temp_addr = 0;

	if(!partition_name)
	{
		debugf("Error: partition_name is null. \n");
		return;
	}

	ret = secure_get_partition_size(partition_name, &partition_size);
	debugf("ret = %d\n", ret);
	if (ret < 0) {
		debugf("secure_get_partition_size error!\n");
		return;
	}
	vboot_verify_info->img_len=partition_size;

	debugf("cm4 old img_addr:0x%llx.  len:0x%llx. \n", vboot_verify_info->img_addr, vboot_verify_info->img_len);
	temp_addr = vboot_verify_info->img_addr;
	vboot_verify_info->img_addr = DFS_ADDR;
	debugf("cm4 new img_addr:0x%llx.  len:0x%llx. \n", vboot_verify_info->img_addr, vboot_verify_info->img_len);
	/*partition load*/
	if (-1 == secure_load_partition(partition_name,vboot_verify_info->img_len, (uint64_t)0, vboot_verify_info->img_addr)) 
	{
		debugf("load %s partition error\n", partition_name);
		return;
	}

	memset(vboot_para_partition_name, 0, sizeof(vboot_para_partition_name));
	strcpy(vboot_para_partition_name, partition_name);
	vboot_verify_info->img_name = vboot_para_partition_name;
	vboot_verify_info->img_name_len = SEC_MAX_PARTITION_NAME_LEN;
	debugf("vboot_verify_info->img_name :%s. \n", (uint32_t)vboot_verify_info->img_name);

	vboot_verify_info->vboot_unlock_status = g_DeviceStatus;

	ret = uboot_vboot_verify_img((VbootVerifyInfo*)vboot_verify_info,sizeof(VbootVerifyInfo));
	debugf("g_sprd_vboot_cmdline len %d.\n", strlen(g_sprd_vboot_cmdline));
	debugf("g_sprd_vboot_cmdline is %s.\n", g_sprd_vboot_cmdline);
	vboot_verify_info->img_addr = temp_addr;

	/*for verify boot*/
	debugf("partion %s, verify_ret:0x%x\n",partition_name, vboot_verify_info->verify_return_data->vboot_verify_ret);
	vboot_check_result = vboot_verify_info->verify_return_data->vboot_verify_ret;

	if(g_DeviceStatus == VBOOT_STATUS_UNLOCK) {
		g_verifiedbootstate = v_state_orange;
	}
	else if(vboot_check_result == AVB_SLOT_VERIFY_RESULT_OK) {
		g_verifiedbootstate = v_state_green;
	}
	else if(vboot_check_result == AVB_SLOT_VERIFY_RESULT_ERROR_PUBLIC_KEY_REJECTED) {
		g_verifiedbootstate = v_state_yellow;
	}
	else {
		debugf("partion %s, verify_ret:0x%x is invalid.\n",partition_name, vboot_check_result);
		g_verifiedbootstate = v_state_red;
	}

}

void vboot_secure_process_flow(char *partition_name)
{
	int ret;
	uint32_t vboot_check_result;
	uint64_t partition_size=0;

	if(!partition_name)
	{
		debugf("Error: partition_name is null. \n");
		return;
	}

	if((strcmp("vbmeta_system",partition_name) == 0) || (strcmp("vbmeta_vendor",partition_name) == 0)) {
		vboot_verify_info->img_len = 4096;
	} else {
		ret = secure_get_partition_size(partition_name, &partition_size);
		debugf("ret = %d\n", ret);
		if (ret < 0) {
			debugf("secure_get_partition_size error!\n");
			return;
		}
		vboot_verify_info->img_len=partition_size;
	}

	debugf("img_addr:0x%llx.  len:0x%llx. \n", vboot_verify_info->img_addr, vboot_verify_info->img_len);

	/*partition load*/
	if (-1 == secure_load_partition(partition_name,vboot_verify_info->img_len, (uint64_t)0, vboot_verify_info->img_addr)) {
		debugf("load %s partition error\n", partition_name);
		return;
	}

#ifdef CONFIG_VBOOT_DUMP
	dumpHex("boot image",  (uchar *)vboot_verify_info->img_addr, 512);

	dumpHex("vbmeta image",  (uchar *)vboot_verify_info->vbmeta_img_addr, 512);

	dumpHex("vbmeta pubkey",  (uchar *)vboot_verify_info->vbmeta_pubkey_addr, 32);
#endif

	memset(vboot_para_partition_name, 0, sizeof(vboot_para_partition_name));
	strcpy(vboot_para_partition_name, partition_name);
	vboot_verify_info->img_name = vboot_para_partition_name;
	vboot_verify_info->img_name_len = SEC_MAX_PARTITION_NAME_LEN;
	debugf("vboot_verify_info->img_name :%s. \n", (uint32_t)vboot_verify_info->img_name);

	vboot_verify_info->vboot_unlock_status = g_DeviceStatus;

	ret = uboot_vboot_verify_img((VbootVerifyInfo*)vboot_verify_info,sizeof(VbootVerifyInfo));
	debugf("g_sprd_vboot_cmdline len %d.\n", strlen(g_sprd_vboot_cmdline));
	debugf("g_sprd_vboot_cmdline is %s.\n", g_sprd_vboot_cmdline);


	/*for verify boot*/
	debugf("partion %s, verify_ret:0x%x\n",partition_name, vboot_verify_info->verify_return_data->vboot_verify_ret);
	vboot_check_result = vboot_verify_info->verify_return_data->vboot_verify_ret;

	if(g_DeviceStatus == VBOOT_STATUS_UNLOCK) {
		g_verifiedbootstate = v_state_orange;
	}
	else if(vboot_check_result == AVB_SLOT_VERIFY_RESULT_OK) {
		g_verifiedbootstate = v_state_green;
	}
	else if(vboot_check_result == AVB_SLOT_VERIFY_RESULT_ERROR_PUBLIC_KEY_REJECTED) {
		g_verifiedbootstate = v_state_yellow;
	}
	else {
		debugf("partion %s, verify_ret:0x%x is invalid.\n",partition_name, vboot_check_result);
		g_verifiedbootstate = v_state_red;
	}

}

void vboot_secure_process_prepare(void)
{
	unsigned char sprd_vboot_key[SPRD_RSA4096PUBK_HASHLEN];
	sprd_get_vboot_key(UBOOT_START, sprd_vboot_key, GET_FROM_RAM);

#ifdef CONFIG_VBOOT_DUMP
	dumpHex("vboot pubk", sprd_vboot_key, SPRD_RSA4096PUBK_HASHLEN);
#endif
	avb_ops_set_vboot_key(sprd_vboot_key, sizeof(sprd_vboot_key));
}


void sprd_fb_secure_vboot_prepare(char *partition_name, char *img_ram_addr, char * vbmeta_ram_addr, sys_img_header *header)
{
	unsigned char sprd_vboot_key[SPRD_RSA4096PUBK_HASHLEN];
	uint64_t partition_size = 0;
	VERIFY_PROCESS_FLAG process_flag = VERIFY_PROCESS_DOWNLOAD;

	memset(vboot_verify_info, 0, sizeof(VbootVerifyInfo));

	/*from uboot get vboot key*/
	sprd_get_vboot_key((CONFIG_SYS_TEXT_BASE - 0x200), sprd_vboot_key, GET_FROM_RAM);

#ifdef CONFIG_VBOOT_DUMP
	dumpHex("vboot pubk", sprd_vboot_key, SPRD_RSA4096PUBK_HASHLEN);
#endif
	avb_ops_set_vboot_key(sprd_vboot_key, sizeof(sprd_vboot_key));

	secf("partition_name: %s, img_ram_addr: 0x%x, vbmeta_ram_addr:0x%x \r\n", partition_name, img_ram_addr, vbmeta_ram_addr);
	vboot_secure_process_init(partition_name, img_ram_addr, vbmeta_ram_addr, header, process_flag); //VBMETA_IMG_ADDR

	/*if it's not vbmeta image*/
	if(partition_name && (strcmp("vbmeta",partition_name) != 0)){
		if (secure_get_partition_size("vbmeta", &partition_size)) {
			secf("secure_get_partition_size fail\n");
			return;
		}
		if (-1 == secure_load_partition("vbmeta",partition_size, (uint64_t)0, vboot_verify_info->vbmeta_img_addr)){
			debugf("load vbmeta partition error\n");
			return;
		}
	}

	memset(vboot_para_partition_name, 0, sizeof(vboot_para_partition_name));
	strcpy(vboot_para_partition_name, partition_name);
	vboot_verify_info->img_name = vboot_para_partition_name;
	vboot_verify_info->img_name_len = SEC_MAX_PARTITION_NAME_LEN;

	memset(g_sprd_vboot_ret, 0, sizeof(g_sprd_vboot_ret));
	vboot_verify_info->verify_return_data = (VBootResultInfo *)g_sprd_vboot_ret;
	vboot_verify_info->verify_return_data_len = sizeof(VBootResultInfo);
	debugf("vboot_verify_info->img_name :%s. \n", vboot_verify_info->img_name);
}

void sprd_dl_secure_vboot_prepare(void)
{
	unsigned char sprd_vboot_key_in_uboot[SPRD_RSA4096PUBK_HASHLEN];

	memset(sprd_vboot_key_in_uboot, 0, sizeof(sprd_vboot_key_in_uboot));
	sprd_get_vboot_key((CONFIG_SYS_TEXT_BASE - 0x200), sprd_vboot_key_in_uboot, 0);

#ifdef CONFIG_VBOOT_DUMP
	debug("dump uboot key hash \n");
	do_hex_dump(sprd_vboot_key_in_uboot, SPRD_RSA4096PUBK_HASHLEN);
#endif
	avb_ops_set_vboot_key(sprd_vboot_key_in_uboot, sizeof(sprd_vboot_key_in_uboot));
}
#endif

void secboot_update_swVersion(void)
{
	uint32_t flag;
#ifdef CONFIG_SPRD_SECBOOT
	flag = SPRD_FLAG;
#endif
#ifdef CONFIG_SANSA_SECBOOT
	flag = SANSA_FLAG;
#endif

#ifdef CONFIG_SANSA_SECBOOT
	ap_sansa_efuse_prog_power_on();
#endif

	uboot_update_swVersion(&flag,sizeof(flag));

#ifdef CONFIG_SANSA_SECBOOT
	ap_sansa_efuse_power_off();
#endif

}

#ifdef CONFIG_SECBOOT
extern char product_sn_token[PRODUCT_SN_TOKEN_MAX_SIZE];
extern char product_sn_signature[PRODUCT_SN_SIGNATURE_SIZE];

int set_lock_status(unsigned int flag)
{
	unsigned char lock_flag[PDT_INFO_LOCK_FLAG_MAX_SIZE] __attribute__((aligned(4096)));
	unsigned char buffer[PDT_INFO_LOCK_FLAG_SECTION_SIZE];
        int ret;

	memset(lock_flag, 0, sizeof(lock_flag));
	memset(buffer, 0, sizeof(buffer));

	if (flag == VBOOT_STATUS_UNLOCK) {
		strcat(lock_flag, "VerifiedBoot-UNLOCK");
	} else if(flag == VBOOT_STATUS_LOCK) {
		strcat(lock_flag, "VerifiedBoot-LOCK");
	} else {
		debugf("lockflag is invalid.\n");
		return -2;
	}

	/*read from emmc*/
	if (common_raw_read(PRODUCTINFO_FILE_PATITION, PDT_INFO_LOCK_FLAG_SECTION_SIZE,
				PDT_INFO_LOCK_FLAG_OFFSET, (char *)buffer)) {
		debugf("read miscdata error.\n");
		return -1;
	}

	//dumpHex("data before encrypt.", lock_flag, PDT_INFO_LOCK_FLAG_MAX_SIZE);

#if defined CONFIG_VBOOT_V2
	ret = uboot_encrypt_data(lock_flag, PDT_INFO_LOCK_FLAG_MAX_SIZE);
	if (ret) {
		debugf("data encrypt error.\n");
		return -3;
	}
#endif

	//dumpHex("data after encrypt.", lock_flag, PDT_INFO_LOCK_FLAG_MAX_SIZE);

	/*data ready*/
	memcpy((char *)buffer , lock_flag, PDT_INFO_LOCK_FLAG_MAX_SIZE);

	/*write to emmc*/
	if (common_raw_write(PRODUCTINFO_FILE_PATITION, sizeof(buffer), sizeof(buffer),
				PDT_INFO_LOCK_FLAG_OFFSET, (char *)buffer)) {
		debugf("write miscdata error.\n");
		return -1;
	}

	return 0;
}

unsigned int get_lock_status(void)
{
	unsigned char lock_flag[PDT_INFO_LOCK_FLAG_SECTION_SIZE];
	int ret;

	memset(lock_flag, 0, sizeof(lock_flag));

	if (common_raw_read(PRODUCTINFO_FILE_PATITION, sizeof(lock_flag), PDT_INFO_LOCK_FLAG_OFFSET, (char *)lock_flag)) {
		debugf("read miscdata error.\n");
	}

	ret = sprd_sec_verify_lockstatus(lock_flag, PDT_INFO_LOCK_FLAG_MAX_SIZE);

	if(ret != 0) {
		g_DeviceStatus = VBOOT_STATUS_LOCK; /*default lock status.*/
	}
	else {
		g_DeviceStatus = VBOOT_STATUS_UNLOCK; /*unlock status.*/
	}

	return g_DeviceStatus;
}

int verify_product_sn_signature()
{
	int ret = -1;
	uint64_t partition_size = 0;
	uint32_t unlock_bootloader_result = 0;
	int img_size = -1;

#ifdef TOS_TRUSTY
#if defined CONFIG_VBOOT_V2
	memset(vboot_unlock_verify_info, 0,  sizeof(VbootUnlockVerifyInfo));
	vboot_secure_process_prepare();
	vboot_unlock_verify_info->vbmeta_pubkey_addr = g_sprd_vboot_key;
	vboot_unlock_verify_info->vbmeta_pubkey_len = g_sprd_vboot_key_len;

	if (-1 == secure_get_partition_size("vbmeta", &partition_size)){
		debugf("get vbmeta partition size fail\n");
		return -1;
	}

	vboot_unlock_verify_info->vbmeta_img_addr = gd->vbmeta_img_base;

	img_size =  secure_load_partition("vbmeta",partition_size,
			(uint64_t)0, vboot_unlock_verify_info->vbmeta_img_addr);
	if (-1 == img_size){
		debugf("load vbmeta partition error\n");
		return -1;
	}

	vboot_unlock_verify_info->vbmeta_img_len = (uint32_t)(img_size);
	vboot_unlock_verify_info->product_sn_addr = product_sn_token;
	vboot_unlock_verify_info->product_sn_len = PRODUCT_SN_TOKEN_MAX_SIZE;
	vboot_unlock_verify_info->product_sn_signature_addr = product_sn_signature;
	vboot_unlock_verify_info->product_sn_signature_len = PRODUCT_SN_SIGNATURE_SIZE;
	vboot_unlock_verify_info->verify_return_data = (VBootResultInfo *)g_sprd_vboot_ret;
	vboot_unlock_verify_info->verify_return_data_len = sizeof(VBootResultInfo);

	ret = uboot_verify_product_sn_signature((VbootUnlockVerifyInfo*)vboot_unlock_verify_info,
			sizeof(VbootUnlockVerifyInfo));
#endif
#else
	memset(&vboot_unlock_verify_info, 0,  sizeof(VbootUnlockVerifyInfo));
	vboot_secure_process_prepare();
	vboot_unlock_verify_info.vbmeta_pubkey_addr = g_sprd_vboot_key;
	vboot_unlock_verify_info.vbmeta_pubkey_len = g_sprd_vboot_key_len;

	if (-1 == secure_get_partition_size("vbmeta", &partition_size)){
		debugf("get vbmeta partition size fail\n");
		return -1;
	}

	vboot_unlock_verify_info.vbmeta_img_addr = gd->vbmeta_img_base;

	img_size =  secure_load_partition("vbmeta",partition_size,
			(uint64_t)0, vboot_unlock_verify_info.vbmeta_img_addr);
	if (-1 == img_size){
		debugf("load vbmeta partition error\n");
		return -1;
	}

	vboot_unlock_verify_info.vbmeta_img_len = (uint32_t)(img_size);
	vboot_unlock_verify_info.product_sn_addr = product_sn_token;
	vboot_unlock_verify_info.product_sn_len = PRODUCT_SN_TOKEN_MAX_SIZE;
	vboot_unlock_verify_info.product_sn_signature_addr = product_sn_signature;
	vboot_unlock_verify_info.product_sn_signature_len = PRODUCT_SN_SIGNATURE_SIZE;
	vboot_unlock_verify_info.verify_return_data = (VBootResultInfo *)g_sprd_vboot_ret;
	vboot_unlock_verify_info.verify_return_data_len = sizeof(VBootResultInfo);

	ret = uboot_verify_product_sn_signature((VbootUnlockVerifyInfo*)&vboot_unlock_verify_info,
			sizeof(VbootUnlockVerifyInfo));

#endif

	if (!ret) {
#ifdef TOS_TRUSTY
		unlock_bootloader_result = vboot_unlock_verify_info->verify_return_data->vboot_verify_ret;
#else
		unlock_bootloader_result = vboot_unlock_verify_info.verify_return_data->vboot_verify_ret;
#endif
		if (unlock_bootloader_result){
			debugf("uboot_verify_product_sn_signature unlock succeeded\n");
			return ret;
		} else {
			debugf("uboot_verify_product_sn_signature unlock failed\n");
			return -1;
		}
	}

	return ret;
}

int config_os_version(unsigned long *os_version, uint32_t os_version_len)
{
	int ret = -1;

	if (0 == ((*os_version)& 0xffffffff) || os_version_len != 4) {
		debugf("system version error\n");
		return -1;
	}

	ret = uboot_config_os_version((unsigned long)os_version, os_version_len);

	if (!ret) {
		debugf("uboot_config_os_version succeeded\n");
	} else {
		debugf("uboot_config_os_version failed\n");
	}

	return ret;
}

int set_root_of_trust(unsigned char *root_of_trust_str, uint32_t root_of_trust_len)
{
	int ret = -1;

	if (0 == ((*root_of_trust_str)& 0xffffffff)
	    || root_of_trust_len != ROOT_OF_TRUST_MAXSIZE) {
		debugf("root_of_trust information error\n");
		return -1;
	}

	ret = uboot_set_root_of_trust((unsigned long)root_of_trust_str, root_of_trust_len);

	if (!ret) {
		debugf("uboot_set_root_of_trust succeeded\n");
	} else {
		debugf("uboot_set_root_of_trust failed\n");
	}

	return ret;
}

#endif

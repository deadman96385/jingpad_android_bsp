#include <malloc.h>
#include "sansa_secure_boot.h"

DECLARE_GLOBAL_DATA_PTR;

void flush_dcache_area(void *va,size_t len)
{
	flush_dcache_range(va, (char *)va + len -1);
}

void invalidate_dcache_area(void *va,size_t len)
{
	invalidate_dcache_range(va, (char *)va + len -1);
}

static unsigned int SB_MemoryRead(uint64_t offset,uint8_t *memDst,uint32_t sizeToRead,void *context)
{
	uint8_t *load_addr = NULL;
	uint8_t *base_addr = NULL;

	base_addr = (uint8_t *)context;
	load_addr = offset + base_addr;
	if (load_addr != memDst) {
		memcpy(memDst,load_addr,sizeToRead);
	}

	return 0;
}

static DxError_t DX_SB_CertPkgInfoInit(DxSbCertInfo_t *certpkginfo, void *pubkeyhash)
{
	memcpy(certpkginfo->pubKeyHash, (uint8_t *)pubkeyhash, sizeof(HASH_Result_t));
	certpkginfo->initDataFlag = 1;
	return 0;
}

unsigned int DX_SecureBootVerify(void *imgaddr, void *pubkeyhash)
{
	uint8_t scheme_level = 0;
	uint32_t ret;
	DxSbCertInfo_t *p_certPkgInfo = &certPkgInfo;

	fmpreambleheader *fm_header = (fmpreambleheader *)((uint8_t *)imgaddr +((sys_img_header *)imgaddr)->mImgSize + sizeof(sys_img_header));

	if ((fm_header->certa_size <= 0)
		&&(fm_header->certb_size <= 0)
		&&(fm_header->certcnt_size <= 0)) {
		return 1;
	}

	if ((fm_header->certa_size > 0)
		&&(fm_header->certb_size > 0)
		&&(fm_header->certcnt_size > 0)) {
		scheme_level = 3;
	} else if ((fm_header->certa_size > 0)
		&&(fm_header->certb_size == 0)
		&&(fm_header->certcnt_size > 0)) {
		scheme_level = 2;
	} else if ((fm_header->certa_size == 0)
		&&(fm_header->certb_size == 0)
		&&(fm_header->certcnt_size > 0)) {
		scheme_level = 1;
	}

	switch (scheme_level) {
		case 3:
			ret = DX_SB_CertChainVerificationInit(p_certPkgInfo);
			if (ret != DX_OK) {
				return ret;
			}

			if (pubkeyhash != NULL) {
				ret = DX_SB_CertPkgInfoInit(p_certPkgInfo,pubkeyhash);
				if (ret != DX_OK) {
					return ret;
				}
			}

			ret = DX_SB_CertVerifySingle(SB_MemoryRead,imgaddr,
										CRYPTOCELL_SECURE_BASE,
										fm_header->certa_offset,
										p_certPkgInfo,
										tmp_workspace_buf,
										DX_DOUBLE_BUFFER_MAX_SIZE_IN_BYTES);
			if (ret != DX_OK) {
				return ret;
			}

			ret = DX_SB_CertVerifySingle(SB_MemoryRead,imgaddr,
										CRYPTOCELL_SECURE_BASE,
										fm_header->certb_offset,
										p_certPkgInfo,
										tmp_workspace_buf,
										DX_DOUBLE_BUFFER_MAX_SIZE_IN_BYTES);
			if (ret != DX_OK) {
				return ret;
			}

			ret = DX_SB_CertVerifySingle(SB_MemoryRead,imgaddr,
										CRYPTOCELL_SECURE_BASE,
										fm_header->certcnt_offset,
										p_certPkgInfo,
										tmp_workspace_buf,
										DX_DOUBLE_BUFFER_MAX_SIZE_IN_BYTES);
			if (ret != DX_OK) {
				return ret;
			}
			break;
		case 2:
			ret = DX_SB_CertChainVerificationInit(p_certPkgInfo);
			if (ret != DX_OK) {
				return ret;
			}

			ret = DX_SB_CertPkgInfoInit(p_certPkgInfo,pubkeyhash);
			if (ret != DX_OK) {
				return ret;
			}

			ret = DX_SB_CertVerifySingle(SB_MemoryRead,imgaddr,
										CRYPTOCELL_SECURE_BASE,
										fm_header->certa_offset,
										p_certPkgInfo,
										tmp_workspace_buf,
										DX_DOUBLE_BUFFER_MAX_SIZE_IN_BYTES);
			if (ret != DX_OK) {
				return ret;
			}

			ret = DX_SB_CertVerifySingle(SB_MemoryRead,imgaddr,
										CRYPTOCELL_SECURE_BASE,
										fm_header->certcnt_offset,
										p_certPkgInfo,
										tmp_workspace_buf,
										DX_DOUBLE_BUFFER_MAX_SIZE_IN_BYTES);
			if (ret != DX_OK) {
				return ret;
			}
			break;
		case 1:
			ret = DX_SB_CertChainVerificationInit(p_certPkgInfo);
			if (ret != DX_OK) {
				return ret;
			}

			ret = DX_SB_CertPkgInfoInit(p_certPkgInfo,pubkeyhash);
			if (ret != DX_OK) {
				return ret;
			}

			ret = DX_SB_CertVerifySingle(SB_MemoryRead,imgaddr,
										CRYPTOCELL_SECURE_BASE,
										fm_header->certcnt_offset,
										p_certPkgInfo,
										tmp_workspace_buf,
										DX_DOUBLE_BUFFER_MAX_SIZE_IN_BYTES);
			if (ret != DX_OK) {
				return ret;
			}
			break;
		default:
			break;
	}

	return ret;
}

void sansa_get_hash_key(uint8_t *root_addr,uint8_t *hash_key)
{
	uint8_t *pKeyCert = NULL;
	sys_img_header *img_hdr = (sys_img_header *)root_addr;
	fmpreambleheader *fm_header = (fmpreambleheader *)((uint8_t*)root_addr + img_hdr->mImgSize + sizeof(sys_img_header));
	if ((fm_header->certa_size > 0) && (fm_header->certb_size > 0)) {
		pKeyCert = (uint8_t*)root_addr + fm_header->certb_offset;
	} else if ((fm_header->certa_size > 0) && (fm_header->certb_size == 0)) {
		pKeyCert = (uint8_t*)root_addr + fm_header->certa_offset;
	}

	uint32_t offset = sizeof(DxSbCertHeader_t) + SB_RSA_MOD_SIZE_IN_WORDS*sizeof(uint32_t) + SB_RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_WORDS*sizeof(uint32_t) + sizeof(DxSbSwVersion_t);
	memcpy(hash_key,pKeyCert+offset, HASH_BYTE_LEN);
}

void sansa_get_nptr(uint8_t *root_addr, uint8_t *nptr)
{
	uint8_t *pKeyCert = NULL;
	sys_img_header *img_hdr = (sys_img_header *)root_addr;
	fmpreambleheader *fm_header = (fmpreambleheader *)((uint8_t*)root_addr + img_hdr->mImgSize + sizeof(sys_img_header));
	pKeyCert = (uint8_t*)root_addr + fm_header->certa_offset;

	uint32_t offset = sizeof(DxSbCertHeader_t);
	memcpy(nptr,pKeyCert+offset, N_REVNP_SIZE_IN_BYTES);
}

void sansa_secure_check(void *rootaddr, void *imgaddr)
{

	uint8_t *pHashKey = NULL;
	uint8_t hash_key[HASH_BYTE_LEN];
	if (rootaddr != NULL) {
		memset(hash_key, 0, HASH_BYTE_LEN);
		sansa_get_hash_key(rootaddr,hash_key);
		pHashKey = hash_key;
	}

	if (DX_OK != DX_SecureBootVerify((uint8_t*)imgaddr,(uint8_t*)pHashKey)) {
		while(1);
	}
}


void sansa_dl_check(void *rootaddr, void *imgaddr)
{
	uint8_t N_ptr[N_REVNP_SIZE_IN_BYTES] = {0};
	uint8_t pubkhash[HASH_BYTE_LEN] = {0};
	uint32_t err = 1;

	sansa_get_nptr((uint8_t*)rootaddr, N_ptr);
	err = DX_SB_CalcPublicKeyHASH(CRYPTOCELL_SECURE_BASE, N_ptr, pubkhash);

	if ((DX_OK != err) || (DX_OK != DX_SecureBootVerify((uint8_t*)imgaddr,pubkhash))) {
		while(1);
	}
}

void sansa_cpy_spl_to_iram(void *rootaddr, void *imgaddr)
{
	uint32_t len = 0;
	fmpreambleheader *fm_header = (fmpreambleheader *)((uint8_t *)imgaddr +((sys_img_header *)imgaddr)->mImgSize + sizeof(sys_img_header));
	len = sizeof(sys_img_header) + ((sys_img_header *)imgaddr)->mImgSize + sizeof(fmpreambleheader) + fm_header->certa_size + fm_header->certb_size + fm_header->certcnt_size + fm_header->cert_dbg_second_size;
	if ((uint8_t *)rootaddr != (uint8_t *)imgaddr) {
		memcpy((uint8_t *)rootaddr,(uint8_t *)imgaddr,len);
	}
}

void hexdump(const char *title, const unsigned char *s, int l)
{
    int n = 0;

    printf("%s", title);
    for (; n < l; ++n) {
        if ((n % 16) == 0)
            printf("\n%04x", n);
        printf(" %02x", s[n]);
    }
    printf("\n");
}

uint8_t *sansa_reassemble_packed_img(uint8_t *p_in)
{
    sys_img_header  *p_imgh = NULL;
    uint8_t         *p_out = gd->verify_base;
    uint32_t         header_len = sizeof(sys_img_header);
    uint32_t         in_off = 0, out_off = 0, new_size = 0;

    printf("%s enter\n", __FUNCTION__);
    p_imgh = (sys_img_header *)p_in;
    printf("%s, is_packed = %d\n",__FUNCTION__, p_imgh->is_packed);
    if (1 == p_imgh->is_packed) {
        printf("%s, packed image founded \n",__FUNCTION__);
        printf("%s, header_len = %d, mImgSize = %x mFirmwareSize = %x mFirmwareOff = %x\n",
               __FUNCTION__, header_len, p_imgh->mImgSize, p_imgh->mFirmwareSize, p_imgh->mFirmwareOff);
        memset(p_out, 0, MAX_PACKED_IMAGE_SIZE);
        // copy image header
        memcpy(p_out, p_in, header_len);
        // copy runtime firmware
        in_off  = p_imgh->mFirmwareOff;
        out_off = header_len;
        memcpy(p_out+out_off, p_in+in_off, p_imgh->mFirmwareSize);
        // copy content cert
        in_off  = header_len + p_imgh->mImgSize;
        out_off = header_len + p_imgh->mFirmwareSize;
        memcpy(p_out+out_off, p_in+in_off, 1024);
        // modify new header mImgSize
        new_size = p_imgh->mFirmwareSize;
        p_imgh = (sys_img_header *)p_out;
        p_imgh->mImgSize = new_size;
        printf("%s, reassemble done\n",__FUNCTION__);
        //hexdump("header:", p_out, 512);
        //printf("============================================================\n");
        //hexdump("cp img:", p_out+512, 512);
        //printf("============================================================\n");
        //hexdump("cert:", p_out+512+p_imgh->mImgSize, 1024);
    } else {
        printf("%s, no need reassemble\n",__FUNCTION__);
        p_out = p_in;
    }
    return p_out;
}

void sansa_dl_secure_verify(uint8_t *name, uint8_t *header, uint8_t *code)
{
    uint8_t    *p_new = NULL;

    printf("%s, name: %s\n",__FUNCTION__,name);
    if (name) {
        /*verify sml,trustos,uboot*/
        if ((strcmp("splloader",name) == 0) || (strcmp("fdl1",name) == 0)) {
            sansa_secure_check(IRAM_BEGIN, header);
        }
        /*verify boot,recovery,modem ..*/
        else if ((strcmp("uboot",name) == 0) || (strcmp("fdl2",name) == 0)) {
            printf("%s, header: 0x%x\n",__FUNCTION__, header);
            p_new = sansa_reassemble_packed_img(header);
            printf("%s, p_new: 0x%x\n",__FUNCTION__, p_new);
            sansa_secure_check((CONFIG_SYS_TEXT_BASE - 0x200), p_new);
            printf("%s, secure check done\n",__FUNCTION__);
        }
        /*verify spl*/
        else if (strcmp("splloader0",name) == 0) {
            sansa_secure_check(NULL, header);
        }
    }
}

void sansa_fb_secure_verify(uint8_t *name, uint8_t *header, uint8_t *code)
{
    uint8_t    *p_new = NULL;

    printf("%s, name: %s\n",__FUNCTION__,name);
    if (name) {
        memset(&img_verify_info, 0, sizeof(imgToVerifyInfo));
        secboot_param_set((uint8_t *)header,&img_verify_info);
        /*verify sml,trustos,uboot*/
        if (strcmp("splloader",name) == 0) {
            common_raw_read("splloader",SPL_IMAGE_SIZE, 0, (unsigned char *)gd->verify_base);
            sansa_get_hash_key(gd->verify_base,img_verify_info.pubkeyhash);
        }
        /*verify boot,recovery,modem ..*/
        else if (strcmp("uboot",name) == 0) {
            sansa_get_hash_key(UBOOT_START,img_verify_info.pubkeyhash);
            printf("%s, header: 0x%x\n",__FUNCTION__, header);
            p_new = sansa_reassemble_packed_img(header);
            printf("%s, p_new: 0x%x\n",__FUNCTION__, p_new);
            img_verify_info.img_addr = p_new;
        }
        /*verify spl*/
        else if (strcmp("splloader0",name) == 0) {
            //do nothing,read hash from efuse
        }
        uboot_verify_img(&img_verify_info,sizeof(imgToVerifyInfo));
    }
}


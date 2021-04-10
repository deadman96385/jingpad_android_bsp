#include "sansa_secure_boot.h"

int sec_strcmp(const char * cs,const char * ct)
{
	register signed char __res;

	while (1) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
	}

	return __res;
}

/*use this instead of memset ,they are the same*/
static void * sec_memset(void * string,int fill,uint32_t cnt)
{
	unsigned long *stl = (unsigned long *) string;
	unsigned long fl = 0;
	unsigned int i = 0;
	char *st8;

	/* do one word  a time while possible */
	if ( ((ulong)string & (sizeof(*stl) - 1)) == 0)
	{
		for (i = 0; i < sizeof(*stl); i++)
		{
			fl <<= 8;
			fl |= fill & 0xff;
		}
		while (cnt >= sizeof(*stl))
		{
			*stl++ = fl;
			cnt -= sizeof(*stl);
		}
	}
	/* fill 8 bits*/
	st8 = (char *)stl;
	while (cnt--)
	{
		*st8++ = fill;
	}

	return string;
}

/*use this instead of memcpy ,they are the same*/
static void * sec_memcpy(void *dst, const void *src, uint32_t cnt)
{
	unsigned long *dlt = (unsigned long *)dst, *slt = (unsigned long *)src;
	char *d8, *st8;

	/* while all data is aligned (common case), copy a word at a time */
	if ( (((ulong)dst | (ulong)src) & (sizeof(*dlt) - 1)) == 0) {
		while (cnt >= sizeof(*dlt)) {
			*dlt++ = *slt++;
			cnt -= sizeof(*dlt);
		}
	}
	/* copy the reset one byte at a time */
	d8 = (char *)dlt;
	st8 = (char *)slt;
	while (cnt--)
		*d8++ = *st8++;

	return dst;
}

static unsigned int SB_MemoryRead(uint64_t offset,uint8_t *memDst,uint32_t sizeToRead,void *context)
{
	uint8_t *load_addr = NULL;
	uint8_t *base_addr = NULL;

	base_addr = (uint8_t *)context;
	load_addr = offset + base_addr;
	if (load_addr != memDst) {
		sec_memcpy(memDst,load_addr,sizeToRead);
	}

	return 0;
}

static DxError_t DX_SB_CertPkgInfoInit(DxSbCertInfo_t *certpkginfo, void *pubkeyhash)
{
	sec_memcpy(certpkginfo->pubKeyHash, (uint8_t *)pubkeyhash, sizeof(HASH_Result_t));
	certpkginfo->initDataFlag = 1;
	return 0;
}

static uint8_t sansa_get_image_level(void *imgaddr)
{
	uint8_t level = 0;
	fmpreambleheader *fm_header = (fmpreambleheader *)((uint8_t *)imgaddr +((sys_img_header *)imgaddr)->mImgSize + sizeof(sys_img_header));

	if ((fm_header->certa_size <= 0)
		&&(fm_header->certb_size <= 0)
		&&(fm_header->certcnt_size <= 0)) {
		return 0;
	}

	if ((fm_header->certa_size > 0)
		&&(fm_header->certb_size > 0)
		&&(fm_header->certcnt_size > 0)) {
		level = 3;
	} else if ((fm_header->certa_size > 0)
		&&(fm_header->certb_size == 0)
		&&(fm_header->certcnt_size > 0)) {
		level = 2;
	} else if ((fm_header->certa_size == 0)
		&&(fm_header->certb_size == 0)
		&&(fm_header->certcnt_size > 0)) {
		level = 1;
	}
	return level;
}

unsigned int DX_SecureBootVerify(void *imgaddr, void *pubkeyhash)
{
	uint8_t level = 0;
	uint32_t ret;
	DxSbCertInfo_t *p_certPkgInfo = &certPkgInfo;

	level = sansa_get_image_level((uint8_t*)imgaddr);
	if (level == 0)
		return 1;

	fmpreambleheader *fm_header = (fmpreambleheader *)((uint8_t *)imgaddr +((sys_img_header *)imgaddr)->mImgSize + sizeof(sys_img_header));


	switch (level) {
		case 3:
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
	sec_memcpy(hash_key,pKeyCert+offset, HASH_BYTE_LEN);
}

static void sansa_get_cert_swVersion(uint8_t *pCert, DxSbSwVersion_t **pSwVersion)
{
	uint32_t offset = sizeof(DxSbCertHeader_t) + SB_RSA_MOD_SIZE_IN_WORDS*sizeof(uint32_t) + SB_RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_WORDS*sizeof(uint32_t);
	*pSwVersion = (DxSbSwVersion_t*)(pCert + offset);
}

static void update_IdAndSwVersion(DxSbSwVersion_t *dxSwVersion,SwVersionRecordInfo_t *versionInfo)
{
	if ((dxSwVersion != NULL)
		&& (versionInfo->num < CERT_NUM_MAX)) {
		versionInfo->swVersionInfo[versionInfo->num].id = dxSwVersion->id;
		versionInfo->swVersionInfo[versionInfo->num].swVersion = dxSwVersion->swVersion;
		versionInfo->num++;
	}
}

//0:sucess   1:error
static uint32_t sansa_update_cert_SwVersionRecordInfo(void *imgaddr,SwVersionRecordInfo_t *versionInfo)
{
	DxSbSwVersion_t *pSwVersionCertA = NULL;
	DxSbSwVersion_t *pSwVersionCertB = NULL;
	DxSbSwVersion_t *pSwVersionCertCnt = NULL;
	uint32_t error = 0;
	uint8_t level = 0;

	level = sansa_get_image_level((uint8_t*)imgaddr);
	if (level == 0) {
		return 1;
	}

	fmpreambleheader *fm_header = (fmpreambleheader *)((uint8_t *)imgaddr +((sys_img_header *)imgaddr)->mImgSize + sizeof(sys_img_header));	

	switch (level) {
		case 3:
			sansa_get_cert_swVersion((uint8_t*)imgaddr+fm_header->certa_offset, &pSwVersionCertA);
			update_IdAndSwVersion(pSwVersionCertA,versionInfo);

			sansa_get_cert_swVersion((uint8_t*)imgaddr+fm_header->certb_offset, &pSwVersionCertB);
			update_IdAndSwVersion(pSwVersionCertB,versionInfo);

			sansa_get_cert_swVersion((uint8_t*)imgaddr+fm_header->certcnt_offset, &pSwVersionCertCnt);
			update_IdAndSwVersion(pSwVersionCertCnt,versionInfo);
			break;
		case 2:
			sansa_get_cert_swVersion((uint8_t*)imgaddr+fm_header->certa_offset, &pSwVersionCertA);
			update_IdAndSwVersion(pSwVersionCertA,versionInfo);

			sansa_get_cert_swVersion((uint8_t*)imgaddr+fm_header->certcnt_offset, &pSwVersionCertCnt);
			update_IdAndSwVersion(pSwVersionCertCnt,versionInfo);
			break;
		case 1:
			sansa_get_cert_swVersion((uint8_t*)imgaddr+fm_header->certcnt_offset, &pSwVersionCertCnt);
			update_IdAndSwVersion(pSwVersionCertCnt,versionInfo);
			break;
		default:
			error = 1;
			break;
	}
	return error;
}

static uint32_t SwVersionRecordInfoInit(SwVersionRecordInfo_t *versionInfo)
{
	if (versionInfo == NULL)
		return 1;
	sec_memset(versionInfo,0,sizeof(SwVersionRecordInfo_t));
	return 0;
}

static uint32_t IdAndSwVersionCmp(SwVersionRecordInfo_t *versionInfo)
{
	int i;
	int num = versionInfo->num;
	int refVersion=versionInfo->swVersionInfo[0].swVersion;

	for(i=0;i<num;i++) {
		if(versionInfo->swVersionInfo[i].id !=	defSwVersionId) {
			break;
		}
	}
	if (i != num) goto Error;

	for(i=0;i<num;i++) {
		if(versionInfo->swVersionInfo[i].swVersion != refVersion) {
			break;
		}
	}
	if (i != num) goto Error;

	return 0;

Error:
	return 1;
}
static uint32_t sansa_sb_setSwVersionRecordInfo(void *rootaddr,void *imgaddr)
{
	SwVersionRecordInfo_t *p_swVersionRecordInfo = &swVersionRecordInfo;

	if (iNodeCounter == 0) {
		if (SwVersionRecordInfoInit(p_swVersionRecordInfo) != DX_OK)
			return 1;
		if (rootaddr != NULL) {
			iNodeCounter++;
			if (sansa_update_cert_SwVersionRecordInfo((uint8_t*)rootaddr,p_swVersionRecordInfo) != DX_OK)
				return 1;
		}
	}

	iNodeCounter++;

	if (sansa_update_cert_SwVersionRecordInfo((uint8_t*)imgaddr,p_swVersionRecordInfo) != DX_OK)
		return 1;
	return 0;
}

static uint32_t sansa_setSwVersionToOtp(SwVersionRecordInfo_t *versionInfo)
{
	uint32_t optVersion = 0;
	uint32_t curVersion = 0;

	if ((versionInfo == NULL) || (versionInfo->num == 0)) goto Error;

	if (DX_OK == IdAndSwVersionCmp(versionInfo)) {

		if (DX_OK != NVM_GetSwVersion(CRYPTOCELL_SECURE_BASE, defSwVersionId,&optVersion)) goto Error;

		curVersion = versionInfo->swVersionInfo[0].swVersion;
		if (curVersion > optVersion) {
			if (DX_OK != NVM_SetSwVersion(CRYPTOCELL_SECURE_BASE, defSwVersionId,curVersion)) goto Error;
		}
	}
	return 0;

Error:
	return 1;
}

SecBoot_Result_Ret sansa_secure_check(void *rootaddr, void *imgaddr, SECURE_TYPE type)
{

	uint8_t *pHashKey = NULL;
	uint8_t hash_key[HASH_BYTE_LEN];
	sec_memset(hash_key, 0, HASH_BYTE_LEN);
	sansa_get_hash_key(rootaddr,hash_key);
	pHashKey = hash_key;

	if (DX_OK != DX_SecureBootVerify((uint8_t*)imgaddr,(uint8_t*)pHashKey)) {
		return SECBOOT_VERIFY_FAIL;
	}

	if (type == SECURE_BOOT) {
		if (DX_OK != sansa_sb_setSwVersionRecordInfo((uint8_t*)rootaddr, (uint8_t*)imgaddr)) {
			return SECBOOT_SET_SWVERSION_FAIL;
		}
	}

	return SECBOOT_VERIFY_SUCCESS;
}

void sansa_update_swVersion(void)
{
	SwVersionRecordInfo_t *p_swVersionRecordInfo = &swVersionRecordInfo;

	if (DX_OK != sansa_setSwVersionToOtp(p_swVersionRecordInfo)) {
		while(1);
	}
}

void set_swVsersion_parameter_init(void)
{
	iNodeCounter = 0x0;
	defSwVersionId = DX_SW_VERSION_COUNTER1;
}
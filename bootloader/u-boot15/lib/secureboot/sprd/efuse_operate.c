#include <common.h>
#include "efuse_operate.h"
#include "secure_efuse.h"
#include <sprd_mmc.h>
#include <secureboot/sec_common.h>

DECLARE_GLOBAL_DATA_PTR;

#define DDIE_EFUSE		(0)
#define ARM7_EFUSE		(1)
#define ADIE_EFUSE		(2)
#define BLOCK_SIZE 		(4)
#define BLOCK_CHAR_COUNT	(8)

#define UID_BLOCK_START		(0)
#define UID_BLOCK_END		(1)
#define UID_BLOCK_LEN                  (UID_BLOCK_END - UID_BLOCK_START + 1)

#if defined (CONFIG_SECBOOT)
#define HASH_BLOCK_START             (80)
#define HASH_BLOCK_END                  (87)

#define SECURE_BOOT_BLOCK         (2)
#define SECURE_BOOT_BIT                 (0)
#else

#if defined(CONFIG_SC9838A)||defined(CONFIG_SP7720)||defined(CONFIG_PIKEB_J1MINI_3G)||defined(CONFIG_PIKEB_J1_3G)||defined(CONFIG_SP7731C)
#define HASH_BLOCK_START             (7)
#define HASH_BLOCK_END                  (11)

#define SECURE_BOOT_BLOCK         (2)
#define SECURE_BOOT_BIT                 (0)
#else
#define HASH_BLOCK_START             (2)
#define HASH_BLOCK_END                  (6)

#define SECURE_BOOT_BLOCK         (1)
#define SECURE_BOOT_BIT                 (18)
#endif

#endif
#ifdef CONFIG_WHALE2
#define SEC_ROLLBACK_BLOCK	88
#define NOSEC_ROLLBACK_BLOCK_START 89
#define NOSEC_ROLLBACK_BLOCK_END 95
#define SEC_ROLL_BIT	0x7fffffff //31bit
#define NOSEC_ROLL_BIT	0x7fffffff //31bit
#else
#define SEC_ROLLBACK_BLOCK	14
#define NOSEC_ROLLBACK_BLOCK_START 15
#define NOSEC_ROLLBACK_BLOCK_END 15
#define SEC_ROLL_BIT	0x000fffff //20bit
#define NOSEC_ROLL_BIT	0x7fffffff //31bit
#endif
#define ROLLBACK_VERSION_MAX  31


#define HASH_BLOCK_LEN                  (HASH_BLOCK_END - HASH_BLOCK_START + 1)

#define ARM7_KEY_START 		(0)
#define ARM7_KEY_END		(7)
#define ARM7_KEY_BLOCK_LEN                  (ARM7_KEY_END - ARM7_KEY_START + 1)

#define PROTECT__BIT 			(0X80000000)

//#define MIN(a, b)			((a) <= (b) ? (a) : (b))
#define TOLOWER(x) ((x) | 0x20)

#define isxdigit(c)    (('0' <= (c) && (c) <= '9')  || ('a' <= (c) && (c) <= 'f')  || ('A' <= (c) && (c) <= 'F'))
#define isdigit(c)    ('0' <= (c) && (c) <= '9')
//#define EFUSE_DEBUG
#ifdef EFUSE_DEBUG
#define UBOOT_EFUSE_LOG(format, arg...) printf( format, ## arg)
#else
#define UBOOT_EFUSE_LOG(format, arg...)
#endif
//extern u32 sprd_ap_efuse_read(int id,int blk_index);
//extern int sprd_ap_efuse_prog(int id,int blk_index,u32 val);
unsigned long strtoul(const char *cp,char  **endp, unsigned int base)
{
	unsigned long result = 0,value;
	if (!base) {
		base = 10;
		if (*cp == '0'){
			base = 8;
			cp++;
			if ((TOLOWER(*cp) == 'x') && isxdigit(cp[1])){
				cp++;
				base = 16;
			}
		}
	}else if (base == 16){
			if (cp[0] == '0' && TOLOWER(cp[1]) == 'x')
				cp += 2;
	}
	while (isxdigit(*cp) &&(value = isdigit(*cp) ? *cp-'0' : TOLOWER(*cp)-'a'+10) < base) {
			result = result*base + value;
			cp++;
	}
	if (endp)
		*endp = (char *)cp;
	return result;
}
void efuse_secure_enable(void)
{
	sprd_ap_efuse_prog(SECURE_BOOT_BLOCK, (1 << SECURE_BOOT_BIT));
}

int efuse_secure_is_enabled(void)
{
	u32 ret = sprd_ap_efuse_read(SECURE_BOOT_BLOCK);
	return (ret & (1 << SECURE_BOOT_BIT)) ? 1 : 0;
}
int efuse_convert_version(int efuse_val)
{
	int i;
	int version =1;
	if(!efuse_val)
		return 0;
	for(i=1;i<32;i++)
	{
		version*=2;
		if(version == efuse_val+1)
			return i;
	}
	return 0;
}
int efuse_rollback_version_read(int type)
{
	u32 ret = 0;
	u32 read_block = NOSEC_ROLLBACK_BLOCK_END;
	u32 version = 0;
	if(type)//no_sec_rollback
	{	
		do
		{
		ret = sprd_ap_efuse_read(read_block);
		version+=efuse_convert_version(ret&NOSEC_ROLL_BIT);
		read_block--;
		}
		while(((ret&NOSEC_ROLL_BIT)==NOSEC_ROLL_BIT)&&(read_block>=NOSEC_ROLLBACK_BLOCK_START));
	}
	else
	{
		ret = sprd_ap_efuse_read(SEC_ROLLBACK_BLOCK);
		version+=efuse_convert_version(ret&SEC_ROLL_BIT);
	}
	return version;
}

uint32_t version_convert_efuse(uint32_t version)
{
	uint32_t efuse = 1;
	uint32_t i;

	if(version == 0) //version 0 ->efuse 0
		return 0;
	if(version > ROLLBACK_VERSION_MAX) //version overflow
		return 0x7fffffff;
	for(i=0;i<version;i++)
	{
		efuse*=2;
	}
	return efuse-1;
}

int efuse_rollback_version_write(int type,int value)
{	

	u32 ret = 0;
	u32 write_block = NOSEC_ROLLBACK_BLOCK_END;
	u32 version = 0;
	
	if(type)//no_sec_rollback
	{
		do
		{
		version = version_convert_efuse(value&NOSEC_ROLL_BIT);
		ret= sprd_ap_efuse_prog(write_block, version);
		printf("efuse_unsec_prog ret =%x,version=%x\n",ret,version);
		value-=31;
		write_block--;
		}
		while((value>0)&&(write_block>=NOSEC_ROLLBACK_BLOCK_START));
		
	}
	else
	{
		version = version_convert_efuse(value&SEC_ROLL_BIT);
		ret= sprd_ap_efuse_prog(SEC_ROLLBACK_BLOCK, version);
		printf("efuse_sec_prog ret=%x,version=%x\n",ret,value);
	}
        return ret;
}

int arm7_key_write( char *key, u32 count)
{
	int i = 0, j = ARM7_KEY_START, len = 0;
	char buf[BLOCK_CHAR_COUNT+1] = { 0 };
	char *p = key;
	u32 value = 0, read_hash = 0;
	if ((0 == p) || (count < 1))
		return -1;
	UBOOT_EFUSE_LOG("%s()->Line:%d; hash string = %s, len = %d \n", __FUNCTION__, __LINE__, key, count);
	count = MIN(count,ARM7_KEY_BLOCK_LEN*BLOCK_CHAR_COUNT);
	for (i = 0; i < count; i += BLOCK_CHAR_COUNT) {
		memset(buf, 0, sizeof(buf));
		strncpy((char*)buf, (char*)&p[i], BLOCK_CHAR_COUNT);
		buf[BLOCK_CHAR_COUNT]='\0';
		value = (u32)(strtoul(buf, 0, 16));
		value &= 0x7fffffff;
		UBOOT_EFUSE_LOG("%s()->Line :%d value=%8x\n",__FUNCTION__, __LINE__,value);
		sprd_ap_efuse_prog(j, value);
		read_hash = sprd_ap_efuse_read(j);
		UBOOT_EFUSE_LOG("%s()->Line :%d read_hash=%8x\n",__FUNCTION__, __LINE__,read_hash);
		if(read_hash != value){
			UBOOT_EFUSE_LOG("%s()->Line:%d READ HASH != WRITE HASH\n", __FUNCTION__, __LINE__);
			return -2;
		}
		value  |= PROTECT__BIT;
		sprd_ap_efuse_prog(j,  PROTECT__BIT );
		read_hash = sprd_ap_efuse_read(j);
		if(read_hash != value){
			UBOOT_EFUSE_LOG("%s()->Line:%d READ HASH !=  value\n", __FUNCTION__, __LINE__);
			return -2;
		}
		len += BLOCK_CHAR_COUNT ;
		j++;
	}
	return len;
}

int arm7_key_read( char *key, u32 count)
{
	char values[ARM7_KEY_BLOCK_LEN*BLOCK_CHAR_COUNT+1] = { 0 };
	char tmp_hash[BLOCK_CHAR_COUNT + 1] = {0};
	u32 i = 0, len = 0,read_hash=0;
	char *p=  ( char*)&read_hash;
	UBOOT_EFUSE_LOG("%s()->Line:%d; count = %d \n", __FUNCTION__, __LINE__, count);

	if ((0 == key) || (count < 1))
		return -1;

	len = MIN(count, ARM7_KEY_BLOCK_LEN*BLOCK_CHAR_COUNT);
	for (i = ARM7_KEY_START; i <= ARM7_KEY_END; i++) {
		read_hash = sprd_ap_efuse_read(i);
		sprintf(tmp_hash,"%02x%02x%02x%02x",p[3],p[2],p[1],p[0]);
		tmp_hash[BLOCK_CHAR_COUNT] = '\0';
		UBOOT_EFUSE_LOG("%s()->Line:%d; block_id=%d,tmp_hash=%s\n", __FUNCTION__, __LINE__,i, tmp_hash);
		strncpy(&values[(i - ARM7_KEY_START) * BLOCK_CHAR_COUNT], tmp_hash, BLOCK_CHAR_COUNT);
	}
	values[ARM7_KEY_BLOCK_LEN*BLOCK_CHAR_COUNT] = '\0';
	UBOOT_EFUSE_LOG("values=%s\n",values);
	strncpy( key, values, len);
	UBOOT_EFUSE_LOG("%s()->Line:%d; hash = %s, len = %d \n", __FUNCTION__, __LINE__, key, len-1);

	return len;
}

int efuse_hash_write( char *hash, u32 count)
{
	int i = 0, j = HASH_BLOCK_START, len = 0;
	char buf[BLOCK_CHAR_COUNT+1] = { 0 };
	char *p = hash;
	u32 value = 0, read_hash = 0;
	if ((0 == p) || (count < 1))
		return -1;
	UBOOT_EFUSE_LOG("%s()->Line:%d; hash string = %s, len = %d \n", __FUNCTION__, __LINE__, hash, count);
	count = MIN(count,HASH_BLOCK_LEN*BLOCK_CHAR_COUNT);
	for (i = 0; i < count; i += BLOCK_CHAR_COUNT) {
		memset(buf, 0, sizeof(buf));
		strncpy((char*)buf, (char*)&p[i], BLOCK_CHAR_COUNT);
		buf[BLOCK_CHAR_COUNT]='\0';
		value = (u32)(strtoul(buf, 0, 16));
		value &= 0x7fffffff;
		UBOOT_EFUSE_LOG("%s()->Line :%d value=%8x\n",__FUNCTION__, __LINE__,value);
		sprd_ap_efuse_prog(j, value);
		read_hash = sprd_ap_efuse_read(j);
		UBOOT_EFUSE_LOG("%s()->Line :%d read_hash=%8x\n",__FUNCTION__, __LINE__,read_hash);
		if(read_hash != value){
			UBOOT_EFUSE_LOG("%s()->Line:%d READ HASH != WRITE HASH\n", __FUNCTION__, __LINE__);
			return -2;
		}
		value  |= PROTECT__BIT;
		sprd_ap_efuse_prog(j,  PROTECT__BIT );
		read_hash = sprd_ap_efuse_read(j);
		if(read_hash != value){
			UBOOT_EFUSE_LOG("%s()->Line:%d READ HASH !=  value\n", __FUNCTION__, __LINE__);
			return -2;
		}
		len += BLOCK_CHAR_COUNT ;
		j++;
	}
	return len;
}

int efuse_hash_read(char *hash, u32 count)
{
	char values[HASH_BLOCK_LEN*BLOCK_CHAR_COUNT+1] = { 0 };
	char tmp_hash[BLOCK_CHAR_COUNT + 1] = {0};
	u32 i = 0, len = 0,read_hash=0;
	char *p=  ( char*)&read_hash;
	UBOOT_EFUSE_LOG("%s()->Line:%d; count = %d \n", __FUNCTION__, __LINE__, count);

	if ((0 == hash) || (count < 1))
		return -1;

	len = MIN(count, HASH_BLOCK_LEN*BLOCK_CHAR_COUNT);
	for (i = HASH_BLOCK_START; i <= HASH_BLOCK_END; i++) {
		read_hash = sprd_ap_efuse_read( i );
		sprintf(tmp_hash,"%02x%02x%02x%02x",p[3],p[2],p[1],p[0]);
		tmp_hash[BLOCK_CHAR_COUNT] = '\0';
		UBOOT_EFUSE_LOG("%s()->Line:%d; block_id=%d,tmp_hash=%s\n", __FUNCTION__, __LINE__,i, tmp_hash);
		strncpy(&values[(i - HASH_BLOCK_START) * BLOCK_CHAR_COUNT], tmp_hash, BLOCK_CHAR_COUNT);
	}
	values[HASH_BLOCK_LEN*BLOCK_CHAR_COUNT] = '\0';
	UBOOT_EFUSE_LOG("values=%s\n",values);
	strncpy( hash, values, len);
	UBOOT_EFUSE_LOG("%s()->Line:%d; hash = %s, len = %d \n", __FUNCTION__, __LINE__, hash, len-1);

	return len;
}

int efuse_uid_read(char *uid, int count)
{
	char values[UID_BLOCK_LEN*BLOCK_CHAR_COUNT+1] = { 0 };
	char tmp_uid[BLOCK_CHAR_COUNT + 1] = {0};
	u32 i = 0, len = 0,read_uid=0;
	char *p=  ( char*)&read_uid;
	UBOOT_EFUSE_LOG("%s()->Line:%d; count = %d \n", __FUNCTION__, __LINE__, count);

	if ((0 == uid) || (count < 1))
		return -1;

	len = MIN(count, UID_BLOCK_LEN*BLOCK_CHAR_COUNT);
	for (i = UID_BLOCK_START; i <= UID_BLOCK_END; i++) {
		read_uid = sprd_ap_efuse_read(i);
		sprintf(tmp_uid,"%02x%02x%02x%02x",p[3],p[2],p[1],p[0]);
		tmp_uid[BLOCK_CHAR_COUNT] = '\0';
		UBOOT_EFUSE_LOG("%s()->Line:%d; block_id=%d,tmp_uid=%s\n", __FUNCTION__, __LINE__,i, tmp_uid);
		strncpy(&values[(i - UID_BLOCK_START) * BLOCK_CHAR_COUNT], tmp_uid, BLOCK_CHAR_COUNT);
	}
	values[UID_BLOCK_LEN*BLOCK_CHAR_COUNT] = '\0';
	UBOOT_EFUSE_LOG("values=%s\n",values);
	strncpy( uid, values, len);
	UBOOT_EFUSE_LOG("%s()->Line:%d; uid = %s, len = %d \n", __FUNCTION__, __LINE__, uid, len-1);

	return len;
}

#define  SOCID_SIZE_IN_WORDS 8 
#define	SPRD_PUBKEY_HASHLEN	(SPRD_RSAPUBKLEN-7)

imgToVerifyInfo g_imgToVerInfo = {0};
union sha_256{
  unsigned char sha256_char[32];
  unsigned int  sha256_int[8];
}sha256;
void load_spl(void)
{
	Emmc_Read(PARTITION_BOOT1, 0, SPL_EMMC_SECTOR_NUM, (unsigned char *)IRAM_BEGIN);
}
#if 0
void load_uboot(void)
{
	Emmc_Read(PARTITION_BOOT2, 0, UBOOT_EMMC_SECTOR_NUM, (unsigned char *) (CONFIG_SYS_TEXT_BASE - 0x200));
}
#endif
int secure_efuse_program_sprd(void)
{
	char sha256_string[65];
	uint8_t sprd_pubkey[SPRD_RSAPUBKLEN]={0,};

	memset(&sha256,    0x0, 32);
	memset(sha256_string,   0x0, 65);
	//unsigned char t_splImageBuf[SPL_IMAGE_SIZE];
	printf("###### secure_efuse_program_sprd ######\n");
	/**read spl image**/
	//Emmc_Read(PARTITION_BOOT1, 0, SPL_EMMC_SECTOR_NUM, (unsigned char *)gd->verify_base);
	if (common_raw_read("splloader",SPL_IMAGE_SIZE, 0, (unsigned char *)gd->verify_base)) {
		UBOOT_EFUSE_LOG("%s()->Line:%d; common_raw_read fail\n", __FUNCTION__, __LINE__);
		return -1;
	}
	sprd_get_pubk(gd->verify_base,sprd_pubkey);
	cal_sha256(sprd_pubkey,SPRD_PUBKEY_HASHLEN,sha256.sha256_char);
	sprintf(sha256_string,"%08x%08x%08x%08x%08x%08x%08x%08x", sha256.sha256_int[0],
	sha256.sha256_int[1],
	sha256.sha256_int[2],
	sha256.sha256_int[3],
	sha256.sha256_int[4],
	sha256.sha256_int[5],
	sha256.sha256_int[6],
	sha256.sha256_int[7]);
	//  -----   write SHA256 key Efuse   -----
	//dumpHex("sha256",&sha256,32);
	//dumpHex("sha256_string",sha256_string,64);
	//g_imgToVerInfo.img_addr = gd->verify_base;
	//g_imgToVerInfo.img_len = SPL_IMAGE_SIZE;
	g_imgToVerInfo.img_addr = sha256_string;
	g_imgToVerInfo.img_len = 64;
	g_imgToVerInfo.pubkeyhash = sha256_string;
	g_imgToVerInfo.hash_len = 64;
	g_imgToVerInfo.flag = SPRD_FLAG;
	printf("pubkeyhash = %x,flag = %x \n",g_imgToVerInfo.pubkeyhash,g_imgToVerInfo.flag);

	uboot_program_efuse(&g_imgToVerInfo,sizeof(imgToVerifyInfo));

	return PROG_OK;
}




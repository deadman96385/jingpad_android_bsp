#include <common.h>
#include "efuse_operate.h"

#define DDIE_EFUSE		(0)
#define ARM7_EFUSE		(1)
#define ADIE_EFUSE		(2)
#define BLOCK_SIZE 		(4)
#define BLOCK_CHAR_COUNT	(8)

#define UID_BLOCK_START		(0)
#define UID_BLOCK_END		(1)
#define UID_BLOCK_LEN                  (UID_BLOCK_END - UID_BLOCK_START + 1)

#if defined(CONFIG_SC9838A)||defined(CONFIG_SP7731C)
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
extern u32 efuse_read(int id,int blk_index);
extern int efuse_prog(int id,int blk_index,u32 val);
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
	efuse_prog(DDIE_EFUSE,SECURE_BOOT_BLOCK, (1 << SECURE_BOOT_BIT));
}

int efuse_secure_is_enabled(void)
{
	u32 ret = efuse_read(DDIE_EFUSE, SECURE_BOOT_BLOCK);
	return (ret & (1 << SECURE_BOOT_BIT)) ? 1 : 0;
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
		efuse_prog(ARM7_EFUSE, j, value);
		read_hash = efuse_read(ARM7_EFUSE, j);
		UBOOT_EFUSE_LOG("%s()->Line :%d read_hash=%8x\n",__FUNCTION__, __LINE__,read_hash);
		if(read_hash != value){
			UBOOT_EFUSE_LOG("%s()->Line:%d READ HASH != WRITE HASH\n", __FUNCTION__, __LINE__);
			return -2;
		}
		value  |= PROTECT__BIT;
		efuse_prog(ARM7_EFUSE, j,  PROTECT__BIT );
		read_hash = efuse_read(ARM7_EFUSE, j);
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
		read_hash = efuse_read(ARM7_EFUSE , i );
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
		efuse_prog(DDIE_EFUSE, j, value);
		read_hash = efuse_read(DDIE_EFUSE, j);
		UBOOT_EFUSE_LOG("%s()->Line :%d read_hash=%8x\n",__FUNCTION__, __LINE__,read_hash);
		if(read_hash != value){
			UBOOT_EFUSE_LOG("%s()->Line:%d READ HASH != WRITE HASH\n", __FUNCTION__, __LINE__);
			return -2;
		}
		value  |= PROTECT__BIT;
		efuse_prog(DDIE_EFUSE, j,  PROTECT__BIT );
		read_hash = efuse_read(DDIE_EFUSE, j);
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
		read_hash = efuse_read(DDIE_EFUSE , i );
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
		read_uid = efuse_read(DDIE_EFUSE , i );
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



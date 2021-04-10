#include <config.h>
#include <common.h>
#include <nand.h>
#include <boot_mode.h>
#include <asm/io.h>
//#include "../drivers/mmc/card_sdio.h"
#include <card_sdio.h>
#if defined(CONFIG_SCX35L64) || defined(CONFIG_CHIP_ENV_SET) || defined (CONFIG_WHALE)|| defined (CONFIG_WHALE2)
#include <asm/arch/sprd_chipram_env.h>
#endif
#include <asm/arch/secure_boot.h>
#include "../nand_spl/ufs/simfd_ufs.h"
#include <part.h>
#include <part_efi.h>
#include <security/sec_common.h>
#include <security/trustzone/trustzone.h>
#include <security/sprd_ce_ctrl.h>
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#ifdef CONFIG_TEECFG_CUSTOM
#include "teecfg_parse.h"
#include <security/trustzone/trustzone.h>
#define offset_of(TYPE, MEMBER)      ((size_t)&((TYPE *)0)->MEMBER)
extern void dmc_print_str(const char *string);
#endif
#define SECURE_HEADER_OFF 512


#ifdef CONFIG_DUAL_SPL
/* these parameter used to get the size of uboot.bin from sec header*/
#define SEHEADER_UBOOT_SIZE_OFFSET 0x30
#define BYTE3 0x03
#define BYTE2 0x02
#define BYTE1 0x01
#define BYTE0 0x0
uint8 hash_temp[HASH_TEMP_LEN]={0};
unsigned long uboot_size_no_hash=0;
uint8 *uboot_start_addr = CONFIG_SYS_NAND_U_BOOT_DST;//0x9f00_0000
uint8 *uboot_start_hash_addr = CONFIG_SYS_NAND_U_BOOT_DST-EMMC_SECTOR_SIZE;
uint8 *uboot_size_no_hash_addr=CONFIG_SYS_NAND_U_BOOT_DST-EMMC_SECTOR_SIZE+SEHEADER_UBOOT_SIZE_OFFSET;
BOOLEAN Spl_Hash_Exist(uint8 *p_hash,uint hash_len)
{
	uint32 i;
	for(i=0;i<hash_len;i++)
		{
		if(*(p_hash+i)!=0)
			return TRUE;
		}
	return FALSE;
}

#endif

#ifdef CONFIG_LOAD_PARTITION
int read_common_partition(block_dev_desc_t *dev, uchar * partition_name, uint32_t offsetsector, uint32_t size, uint8_t* buf)
{
	uint32_t count,left;
	disk_partition_t info;

	unsigned char left_buf[dev->blksz];
	count = size/dev->blksz;
	left = size %dev->blksz;

	if (NULL == buf)
		return -1;

	if (get_partition_info_by_name(dev, partition_name, &info))
		return -1;

	if(0!=count)
		if(FALSE == dev->block_read(dev->dev, info.start+offsetsector, count, buf))
			return -1;
	if (left) {
		if (TRUE== dev->block_read(dev->dev, info.start+offsetsector+count, 1, left_buf)){
			sprd_memcpy(buf+(count*dev->blksz), left_buf, left);
		}else{
			return -1;
		}
	}

	return 0;
}

int  load_common_partition(uchar * partition_name,uint32_t size, uint8_t* buf)
{
	int  i, retrys = 5;
	block_dev_desc_t *dev = NULL;
	dev = get_dev();

	if (NULL == dev)
		return -1;

	for(i =0; i<retrys; i++){
	if(0==read_common_partition(dev, partition_name, 0,size, buf))
		      break;
	}

	if(i == 5)
		return -1;

	return 0;
}

int load_partition_with_header(uchar* partition, uint32_t img_max_size, uint8_t* img_buf, sys_img_header* pHeader)
{
	int  i, retrys = 5;
	block_dev_desc_t *dev = NULL;
	uint32_t image_size;

	dev = get_dev();
	if (NULL == dev)
		return -1;

	/* first read header info */
	for(i = 0; i < retrys; i++){
		if(0==read_common_partition(dev, partition, 0, KEY_INFO_SIZ, pHeader))
			break;
	}
	if(i >= retrys)
		return -1;
	image_size = pHeader->mImgSize;
	#ifdef CONFIG_SECBOOT
	image_size = image_size + 1024; /*secure cert size*/
	#endif
	if (image_size > img_max_size) {
		return -2;
	}

	/* read image */
	for(i = 0; i < retrys; i++){
		if(0==read_common_partition(dev, partition, KEY_INFO_SIZ/dev->blksz,
				image_size, img_buf))
			break;
	}
	if(i >= retrys)
		return -3;

	return 0;
}
#endif

#ifdef CONFIG_DUAL_SPL
int Hash_Check(void)///add the hash_check
{
	uboot_size_no_hash=((*(uboot_size_no_hash_addr+BYTE3))<<24)|((*(uboot_size_no_hash_addr+BYTE2))<<16)|((*(uboot_size_no_hash_addr+BYTE1))<<8)|(*(uboot_size_no_hash_addr+BYTE0));
	sha256_csum_wd(uboot_start_addr,uboot_size_no_hash,hash_temp,NULL);
	if(0==sprd_memcmp(uboot_start_hash_addr+UBOOT_HASH_SIZE_OFFSET,hash_temp,HASH_TEMP_LEN))
	return 0;
	else
	return -1;
}
#endif//end hash_check

/*whale2 and new project,dual backup function  will this interface*/
#ifdef CONFIG_DUAL_BACKUP
/*secboot mode ,no need use this interface*/
#ifndef CONFIG_SECBOOT
BOOLEAN sprd_hash_exist(uint8 *p_hash,uint hash_len)
{
	uint32 i;
	for(i=0;i<hash_len;i++){
		if(*(p_hash+i)!=0)
			return TRUE;
	}
	return FALSE;
}

int8_t sprd_hash_check(uint8_t *header)
{
	uint8 hash_temp[32]={0};
	sys_img_header *img_header = (sys_img_header *)(header);
	if(sprd_hash_exist(img_header->mPayloadHash,32)){//exsit hash
		sha256_csum_wd((uint8_t *)(header+sizeof(sys_img_header)),img_header->mImgSize,hash_temp,NULL);
		if(0 == sprd_memcmp(img_header->mPayloadHash,hash_temp,32))
			return 0;
		else
			return -1;
	}
	return 0;//no need to check hash
}
#endif
#endif

#if defined(CONFIG_WHALE) || defined(CONFIG_WHALE2)
#define TMP_REG_AP_AHB_AHB_EB 0x20210000
#define TMP_BIT_AP_AHB_CC63P_EB (1<<23)
void disable_ahb_cc63_eb()
{
	(*(volatile uint32 *)TMP_REG_AP_AHB_AHB_EB) &= (uint32)(~TMP_BIT_AP_AHB_CC63P_EB);
}
#endif


#define   HWRST_POWERON_MASK 	(0xf0)

/*
* Definition of ANA_RST_STATUS(ANA_REG_GLB_POR_RST_MONITOR) register
* bit[0..7]: Reboot mode
* bit[9]: SYSDUMP enable/disable flag
*/

#define   HWRST_STATUS_RECOVERY                 (0x0020)
#define   HWRST_STATUS_FASTBOOT                 (0x0030)
#define   HWRST_STATUS_NORMAL                   (0x0040)
#define   HWRST_STATUS_ALARM                    (0x0050)
#define   HWRST_STATUS_SLEEP                    (0x0060)
#define   HWRST_STATUS_SPECIAL                  (0x0070)
#define   HWRST_STATUS_CALIBRATION              (0x0090)
#define   HWRST_STATUS_PANIC                    (0x0080)
#define   HWRST_STATUS_AUTODLOADER              (0x00a0)
#define   HWRST_STATUS_IQMODE                   (0x00b0)
#define   HWRST_STATUS_SPRDISK                  (0x00c0)
#define   HWRST_STATUS_NORMAL2                  (0x00f0)
#define   HWRST_STATUS_NORMAL3                  (0x00f1)
#define   HWRST_STATUS_SYSDUMPEN                (0x0200)
#define   HWRST_MOBILEVISOR                     (0x0001)
#define   HWRST_SECURITY                        (0x0002)

int8_t check_sprd_sysdump_sec()
{
#ifdef CONFIG_LOAD_TOS_ALONE
	uint32 reg_rst_moitor;
	uint32 wdt_temp;

	//step1: check if hw wdt rst pending
	ANA_REG_OR(ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_WDG_EN); //WDG enable
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN,    BIT_RTC_WDG_EN); //WDG Rtc enable

	wdt_temp = ANA_REG_GET(ANA_WDG_BASE+0x10);   //WDG_INT_RAW
	wdt_temp &= 0x8;  //bit3:wdg_rst_raw
	/* don't clear rst/int bit, uboot will read again */

	//step2: read sc2731 RST_MONITOR reg, 0x2E8
	reg_rst_moitor = ANA_REG_GET(ANA_REG_GLB_POR_RST_MONITOR);

	if(! (reg_rst_moitor & HWRST_STATUS_SYSDUMPEN))
		return 0;

	reg_rst_moitor &= 0xFF;

	//setp3: return status by HWRST
	if (wdt_temp) {    //hw wdt rst pending
		if ((reg_rst_moitor == HWRST_SECURITY)) {
			return 1;
		} else {
			return 0;
		}
	}

	return 0;
#else
	return 0;
#endif
}

#ifdef CONFIG_MOBILEVISOR
int8_t bootmode_check_sysdump()
{
	uint32 reg_rst_moitor;
	uint32 wdt_temp;
	uint32 src_flag;

	//step1: check if hw wdt rst pending
	ANA_REG_OR(ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_WDG_EN); //WDG enable
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN,    BIT_RTC_WDG_EN); //WDG Rtc enable

	wdt_temp = ANA_REG_GET(ANA_WDG_BASE+0x10);   //WDG_INT_RAW
	wdt_temp &= 0x8;  //bit3:wdg_rst_raw
	/* don't clear rst/int bit, uboot will read again */

	//step2: read sc2731 RST_MONITOR reg, 0x2E8
	reg_rst_moitor = ANA_REG_GET(ANA_REG_GLB_POR_RST_MONITOR);

	if(! (reg_rst_moitor & HWRST_STATUS_SYSDUMPEN))
		return 0;

	reg_rst_moitor &= 0xFF;

	//setp3: return status by HWRST
	if (wdt_temp) {    //hw wdt rst pending
		if ( (reg_rst_moitor==HWRST_STATUS_SPECIAL) || (reg_rst_moitor==HWRST_STATUS_PANIC) || (reg_rst_moitor==HWRST_STATUS_NORMAL2) ) {
			return 1;
		} else if ((reg_rst_moitor==HWRST_MOBILEVISOR) || (reg_rst_moitor==HWRST_SECURITY)) {
			return 1;
		} else {
			return 0;
		}
	}

	//step4: 7s reset or ext pin
	src_flag = ANA_REG_GET(ANA_REG_GLB_POR_SRC_FLAG);        //0x2F4
	src_flag &= 0xFFFF;
	if ( (src_flag&0x800) || ((src_flag&0x1080) == 0x1000) ) {   //7s reset
		return 1;
	} else if (reg_rst_moitor==HWRST_STATUS_NORMAL2) {
		return 1;
	} else {
		return 0;
	}
}
#endif

#ifdef CONFIG_TEECFG_CUSTOM
unsigned int get_tos_size(void)
{
	if (sprd_strcmp(TEECFG_HEADER_MAGIC, (unsigned char *)CONFIG_TEECFG_LDADDR_START) != 0) {
		dmc_print_str("teecfg header verify failed!\n");
		return 0;
	}

	return *((unsigned int *)(CONFIG_TEECFG_LDADDR_START + offset_of(tee_config_header_t, tos_size)));
}
#endif

void nand_boot(void)
{
	int ret;
	int i, j;
	block_dev_desc_t *dev = NULL;
	disk_partition_t info;
	__attribute__ ((noreturn)) void (*uboot) (void);
	int8_t sysdump_mode = 0, sysdump_security = 0;

#if 0
	unsigned int i = 0;
	for (i = 0xffffffff; i > 0;)
		i--;
#endif
	/*
	 * Init board specific nand support
	 */
#ifdef SPRD_EVM_TAG_ON
#if 0
	unsigned long int *ptr = (unsigned long int *)SPRD_EVM_ADDR_START - 8;
	int ijk = 0;
	for (ijk = 0; ijk < 28; ijk++) {
		*(ptr++) = 0x55555555;
	}
#endif
	SPRD_EVM_TAG(1);
#endif

	sysdump_security = check_sprd_sysdump_sec();
	if (!sysdump_security) {  //sysdump mode (tos panic) don't enable firewall
		sprd_firewall_config_pre();
	}

#ifdef CONFIG_EMMC_BOOT
#ifndef CONFIG_LOAD_PARTITION
#ifdef CONFIG_SECURE_BOOT
	if (TRUE == Emmc_Init()) {
		Emmc_Read(PARTITION_BOOT2, 2, (CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM + 1), (uint8 *) (CONFIG_SYS_NAND_U_BOOT_DST - KEY_INFO_SIZ));
		//Emmc_Read(PARTITION_BOOT2, 2, (CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM + 1), (uint8 *)(CONFIG_SYS_NAND_U_BOOT_DST));
		Emmc_Read(PARTITION_BOOT2, 1, 1, (uint8 *) VLR_INFO_OFF);
	}
#else
	if (TRUE == isSDCardBoot()) {
		if (TRUE == SD_Init()) {
			SD_CARD_Read(PARTITION_BOOT2, 0, CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM, (uint8 *) CONFIG_SYS_NAND_U_BOOT_DST);
		} else {

			if (TRUE == Emmc_Init()) {
				Emmc_Read(PARTITION_BOOT2, 0, CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM, (uint8 *) CONFIG_SYS_NAND_U_BOOT_DST);
			}
		}
	} else {
		if (TRUE == Emmc_Init()) {
			Emmc_Read(PARTITION_BOOT2, 0, CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM, (uint8 *) CONFIG_SYS_NAND_U_BOOT_DST);
		}
	}
#endif
#endif
#ifdef CONFIG_LOAD_PARTITION
		if(TRUE == Emmc_Init()){
#if CONFIG_SMLBOOT// whale
			load_partition_with_header("sml", SML_LOAD_MAX_SIZE,CONFIG_SML_LDADDR_START,(sys_img_header*)(CONFIG_SML_LDADDR_START-IMAGE_HEAD_SIZE));
			load_partition_with_header("trustos", TOS_LOAD_MAX_SIZE,CONFIG_TOS_LDADDR_START,(sys_img_header*)(CONFIG_TOS_LDADDR_START-IMAGE_HEAD_SIZE));
#endif

			if (!sysdump_security) {  //sysdump mode (tos panic) don't load tos and sml
#ifdef CONFIG_LOAD_TOS_ALONE
				load_partition_with_header("trustos", TOS_LOAD_MAX_SIZE,CONFIG_TOS_LDADDR_START,(sys_img_header*)(CONFIG_TOS_LDADDR_START-IMAGE_HEAD_SIZE));
#endif

#ifdef CONFIG_TEECFG_CUSTOM
				load_partition_with_header("teecfg", TEECFG_LOAD_MAX_SIZE, CONFIG_TEECFG_LDADDR_START, (sys_img_header *)(CONFIG_TEECFG_LDADDR_START - IMAGE_HEAD_SIZE));
#endif

#ifdef CONFIG_LOAD_ATF
				load_partition_with_header("sml", SML_LOAD_MAX_SIZE,CONFIG_SML_LDADDR_START,(sys_img_header*)(CONFIG_SML_LDADDR_START-IMAGE_HEAD_SIZE));
#endif
			}

			load_partition_with_header("uboot",CONFIG_UBOOT_MAX_SIZE,CONFIG_SYS_NAND_U_BOOT_DST,(sys_img_header*)(CONFIG_SYS_NAND_U_BOOT_DST - KEY_INFO_SIZ));

#ifdef CONFIG_MOBILEVISOR
		sysdump_mode = bootmode_check_sysdump();
		if (!sysdump_mode) {
			ddr_print_string("\r\nStart load vmm images from emmc\r\n");
			/* reserve KEY_INFO_SIZE for image loading area */
			ret = load_partition_with_header("secvm", CONFIG_SECVM_SIZE - KEY_INFO_SIZ,
				(uint8*)CONFIG_SECVM_ADDR,
				(sys_img_header*)(CONFIG_SECVM_ADDR - KEY_INFO_SIZ));
			if (ret < 0){
				ddr_print_string("load secvm fail\r\n");
				while(1);
			}
			ret = load_partition_with_header("mvconfig", CONFIG_MVCONFIG_SIZE - KEY_INFO_SIZ,
				(uint8*)CONFIG_MVCONFIG_ADDR,
				(sys_img_header*)(CONFIG_MVCONFIG_ADDR - KEY_INFO_SIZ));
			if (ret < 0){
				ddr_print_string("load mvconfig fail\r\n");
				while(1);
			}
			ret = load_partition_with_header("mobilevisor", CONFIG_MOBILEVISOR_SIZE - KEY_INFO_SIZ,
				(uint8*)CONFIG_MOBILEVISOR_ADDR,
				(sys_img_header*)(CONFIG_MOBILEVISOR_ADDR - KEY_INFO_SIZ));
			if (ret < 0){
				ddr_print_string("load mobilevisor fail\r\n");
				while(1);
			}
			ddr_print_string("Load vmm images succ\r\n");
		}
#endif
			#ifdef CONFIG_DUAL_SPL//only for tshark3 dual spl;
			if(Spl_Hash_Exist(uboot_start_hash_addr+UBOOT_HASH_SIZE_OFFSET,HASH_TEMP_LEN))
			{
				if(0!=Hash_Check())
				{
				load_partition_with_header("uboot_bak",CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM*EMMC_SECTOR_SIZE,CONFIG_SYS_NAND_U_BOOT_DST,(sys_img_header*)(CONFIG_SYS_NAND_U_BOOT_DST - EMMC_SECTOR_SIZE));
				if(0!=Hash_Check())
					while(1);
				}
			}
			#endif
		}
#endif
#endif

#ifdef CONFIG_UFS_BOOT
		if(0 == ufs_init()){
		load_partition_with_header("uboot",CONFIG_SYS_UFS_U_BOOT_SECTOR_NUM*UFS_SECTOR_SIZE,CONFIG_SYS_NAND_U_BOOT_DST,(sys_img_header*)(CONFIG_SYS_NAND_U_BOOT_DST - KEY_INFO_SIZ));
		}
#endif

/*whale2 and new project,dual backup function  will this interface*/
#ifdef CONFIG_DUAL_BACKUP
#ifdef CONFIG_SECBOOT
	/*sec boot ,dual-backup*/
#else
	/*no sec boot ,dual-backup*/
#ifdef CONFIG_SMLBOOT
	if(0 != sprd_hash_check((uint8_t*)(CONFIG_SML_LDADDR_START-IMAGE_HEAD_SIZE))){
		load_partition_with_header("sml_bak", SML_LOAD_MAX_SIZE,CONFIG_SML_LDADDR_START,(sys_img_header*)(CONFIG_SML_LDADDR_START-IMAGE_HEAD_SIZE));
		if(0 != sprd_hash_check((uint8_t*)(CONFIG_SML_LDADDR_START-IMAGE_HEAD_SIZE)))
			while(1);//sml hash check fail
	}

	if(0 != sprd_hash_check((uint8_t*)(CONFIG_TOS_LDADDR_START-IMAGE_HEAD_SIZE))){
		load_partition_with_header("trustos_bak", TOS_LOAD_MAX_SIZE,CONFIG_TOS_LDADDR_START,(sys_img_header*)(CONFIG_TOS_LDADDR_START-IMAGE_HEAD_SIZE));
		if(0 != sprd_hash_check((uint8_t*)(CONFIG_TOS_LDADDR_START-IMAGE_HEAD_SIZE)))
			while(1);//tos hash check fail
	}


#endif
	if(0 != sprd_hash_check((uint8_t*)(CONFIG_SYS_NAND_U_BOOT_DST-IMAGE_HEAD_SIZE))){
		load_partition_with_header("uboot_bak",CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM*EMMC_SECTOR_SIZE,CONFIG_SYS_NAND_U_BOOT_DST,(sys_img_header*)(CONFIG_SYS_NAND_U_BOOT_DST - EMMC_SECTOR_SIZE));
		if(0 != sprd_hash_check((uint8_t*)(CONFIG_SYS_NAND_U_BOOT_DST-IMAGE_HEAD_SIZE))){
#ifdef CONFIG_SD_BOOT
			if (TRUE == SD_Init()) {
				SD_CARD_Read( SDCARD_BOOT_SECTOR, CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM, (uint8_t *) CONFIG_SYS_NAND_U_BOOT_DST-EMMC_SECTOR_SIZE);
			}
#endif

		}
	}
#ifdef CONFIG_MOBILEVISOR
/*we now check hash of vmm image*/
	if (!sysdump_mode) {
		if(0 != sprd_hash_check((uint8_t*)(CONFIG_SECVM_ADDR-IMAGE_HEAD_SIZE))){
			while(1);
		}
		if(0 != sprd_hash_check((uint8_t*)(CONFIG_MVCONFIG_ADDR-IMAGE_HEAD_SIZE))){
			while(1);
		}
		if(0 != sprd_hash_check((uint8_t*)(CONFIG_MOBILEVISOR_ADDR-IMAGE_HEAD_SIZE))){
			while(1);
		}
	}
#endif
#endif
#endif

#ifdef CONFIG_SECBOOT

    secboot_init();

	if (!sysdump_security) { //sysdump mode (tos panic) don't verify tos and sml
#if defined(CONFIG_SMLBOOT)|| defined(CONFIG_LOAD_ATF)
		if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,(CONFIG_SML_LDADDR_START - IMAGE_HEAD_SIZE),NULL,NULL,SECURE_BOOT)))
		{
			/***secboot sml dual_backup***/
			load_partition_with_header("sml_bak", SML_LOAD_MAX_SIZE,CONFIG_SML_LDADDR_START,(sys_img_header*)(CONFIG_SML_LDADDR_START-IMAGE_HEAD_SIZE));
			if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,(CONFIG_SML_LDADDR_START - IMAGE_HEAD_SIZE),NULL,NULL,SECURE_BOOT)))
			{
				while(1);
			}
		}
#endif

#if defined(CONFIG_TEECFG_CUSTOM)
		if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN, (CONFIG_TEECFG_LDADDR_START - IMAGE_HEAD_SIZE), NULL, NULL, SECURE_BOOT)))
		{
			/***secboot teecfg dual_backup***/
			load_partition_with_header("teecfg_bak", TEECFG_LOAD_MAX_SIZE, CONFIG_TEECFG_LDADDR_START, (sys_img_header*)(CONFIG_TEECFG_LDADDR_START - IMAGE_HEAD_SIZE));
			if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN, (CONFIG_TEECFG_LDADDR_START - IMAGE_HEAD_SIZE), NULL, NULL, SECURE_BOOT)))
			{
				while(1);
			}
		}

		sprd_fw_attr fw_attr;
		fw_attr.tos_size = get_tos_size();
		sprd_firewall_config_attr(&fw_attr);
#endif

#if defined(CONFIG_SMLBOOT)|| defined(CONFIG_LOAD_TOS_ALONE)
		if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,(CONFIG_TOS_LDADDR_START - IMAGE_HEAD_SIZE),NULL,NULL,SECURE_BOOT)))
		{
			/***secboot tos dual_backup***/
			load_partition_with_header("trustos_bak", TOS_LOAD_MAX_SIZE,CONFIG_TOS_LDADDR_START,(sys_img_header*)(CONFIG_TOS_LDADDR_START-IMAGE_HEAD_SIZE));
			if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,(CONFIG_TOS_LDADDR_START - IMAGE_HEAD_SIZE),NULL,NULL,SECURE_BOOT)))
			{
				while(1);
			}
		}
#endif
	}

#ifdef CONFIG_MOBILEVISOR
	if (!sysdump_mode) {
		if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,(CONFIG_SECVM_ADDR - KEY_INFO_SIZ),NULL,NULL,SECURE_BOOT)))
		{
			while(1);
		}

		if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,(CONFIG_MVCONFIG_ADDR - KEY_INFO_SIZ),NULL,NULL,SECURE_BOOT)))
		{
			while(1);
		}

		if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,(CONFIG_MOBILEVISOR_ADDR - KEY_INFO_SIZ),NULL,NULL,SECURE_BOOT)))
		{
			while(1);
		}
	}
#endif
    if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,(CONFIG_SYS_NAND_U_BOOT_DST - SECURE_HEADER_OFF),NULL,NULL,SECURE_BOOT)))
    {
      /***secboot uboot dual_backup***/
      load_partition_with_header("uboot_bak",CONFIG_SYS_EMMC_U_BOOT_SECTOR_NUM*EMMC_SECTOR_SIZE,CONFIG_SYS_NAND_U_BOOT_DST,(sys_img_header*)(CONFIG_SYS_NAND_U_BOOT_DST - EMMC_SECTOR_SIZE));
      if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,(CONFIG_SYS_NAND_U_BOOT_DST - SECURE_HEADER_OFF),NULL,NULL,SECURE_BOOT)))
        {
         while(1);
        }
    }

if (!sysdump_mode)
	update_swVersion();

#endif
	/*
	 * Jump to U-Boot image
	 */
#ifdef SPRD_EVM_TAG_ON
	SPRD_EVM_TAG(3);
#endif


#if CONFIG_SMLBOOT || CONFIG_LOAD_ATF
	if (!sysdump_security) {
		uboot = (void *)CONFIG_SML_LDADDR_START;
	} else {
		uboot = (void *)CONFIG_SYS_NAND_U_BOOT_START;
	}
#else
#ifdef CONFIG_MOBILEVISOR
	if (sysdump_mode) {
		uboot = (void *)CONFIG_SYS_NAND_U_BOOT_START;
	} else {
		uboot = (void *)CONFIG_MOBILEVISOR_ADDR;
	}
#else
	uboot = (void *)CONFIG_SYS_NAND_U_BOOT_START;
#endif
#endif

#ifdef CONFIG_SECURE_BOOT
#if defined(CONFIG_SC8830) || defined(CONFIG_SC9630)  || defined(CONFIG_SCX35L64)
	typedef sec_callback_func_t *(*get_secure_checkfunc_t) (sec_callback_func_t *);
	sec_callback_func_t sec_callfunc;
	vlr_info_t *vlr_info = (vlr_info_t *) (VLR_INFO_OFF);
	get_secure_checkfunc_t *get_secure_func = (get_secure_checkfunc_t *) (INTER_RAM_BEGIN + 0x1C);
	(*get_secure_func) (&sec_callfunc);
	sec_callfunc.secure_check((CONFIG_SYS_NAND_U_BOOT_START - KEY_INFO_SIZ), vlr_info->length, vlr_info, KEY_INFO_OFF);
	//sec_callfunc.secure_check((CONFIG_SYS_NAND_U_BOOT_START),vlr_info->length, vlr_info, KEY_INFO_OFF);
#elif defined(CONFIG_FPGA)

#else
	secure_check(CONFIG_SYS_NAND_U_BOOT_START, 0, CONFIG_SYS_NAND_U_BOOT_START + CONFIG_SYS_NAND_U_BOOT_SIZE - VLR_INFO_OFF,
		     INTER_RAM_BEGIN + CONFIG_SPL_LOAD_LEN - KEY_INFO_SIZ - CUSTOM_DATA_SIZ);
#endif
#endif

    /* disable ahb ccp_en bit */
#if defined(CONFIG_EFUSE)
#if defined(CONFIG_WHALE) || defined(CONFIG_WHALE2)
    sync_efuse_ahb_ccp_eb();
#endif
#endif

#if defined(CONFIG_WHALE) || defined(CONFIG_WHALE2)
	disable_ahb_cc63_eb();
#endif
	disable_ahb_ce_eb();

	disable_ahb_ce_efs_eb();

#ifdef CONFIG_EMMC_BOOT
	/* disable emmc sd_clk */
	Emmc_DisSdClk();
#endif
	/***firewall set***/
	if (!sysdump_security) {  //sysdump mode (tos panic) don't enable firewall
		sprd_firewall_config();
	}

#if defined(CONFIG_SCX35L64)
#ifndef CONFIG_X86
	chipram_env_set(BOOTLOADER_MODE_LOAD);
	extern void switch64_and_set_pc(u32 addr);
	switch64_and_set_pc(CONFIG_SYS_NAND_U_BOOT_START);
#endif
#if  defined(CONFIG_CHIP_ENV_SET)
	chipram_env_set(BOOTLOADER_MODE_LOAD);
#endif
	(*uboot) ();
#else
#if  defined(CONFIG_CHIP_ENV_SET)
	chipram_env_set(BOOTLOADER_MODE_LOAD);
#endif

#if (CONFIG_LOAD_TOS_ALONE == 1) && !defined (CONFIG_ATF_BOOT_TOS)
	secure_sp_entry(CONFIG_TOS_LDADDR_START,CONFIG_SYS_NAND_U_BOOT_START);
#else
	(*uboot) ();
#endif
#endif
}

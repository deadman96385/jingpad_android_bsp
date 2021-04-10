#include "config.h"
#include "fdl_channel.h"
#include <packet.h>
#ifdef CONFIG_SECURE_BOOT
#include <asm/arch/secure_boot.h>
#endif
#include <security/sec_common.h>
#include <asm/arch/sprd_chipram_env.h>
#include <fdl_stdio.h>

extern void JumpToTarget(unsigned long addr);
#ifndef CONFIG_X86
#if defined CONFIG_SC8825 || defined CONFIG_SC8830 || defined(CONFIG_SC9630) || defined(CONFIG_SCX35L64) || defined(CONFIG_FDL_CHECK_SIGN)
#if defined (CONFIG_UBOOT_INTERTWINE_ADDR)
#define MEMORY_START		0x480000000
#else
#define MEMORY_START		0x80000000
#endif
#elif defined CONFIG_SC7710G2
#define MEMORY_START		0x00000000
#else
#define MEMORY_START		0x30000000
#endif
#define MEMORY_SIZE		0x40000000 /* 1G */
#else
#define MEMORY_START		0x00000000
#define MEMORY_SIZE		0xBFFFFFFF /* 1G */
#endif

#ifdef CONFIG_DUAL_SPL
uint8 hash_temp[HASH_TEMP_LEN]={0};
BOOLEAN Fdl_Hash_Exist(uint8 *p_hash,uint hash_len)
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

#if defined (CONFIG_UBOOT_INTERTWINE_ADDR)
typedef struct _DL_FILE_STATUS
{
    unsigned long int start_address;
    unsigned int total_size;
    unsigned int recv_size;
    unsigned long int next_address;
} DL_FILE_STATUS, *PDL_FILE_STATUS;
#else
typedef struct _DL_FILE_STATUS
{
    unsigned int start_address;
    unsigned int total_size;
    unsigned int recv_size;
    unsigned int next_address;
} DL_FILE_STATUS, *PDL_FILE_STATUS;
#endif

static DL_FILE_STATUS g_file;
static unsigned int chg_on_flag = 0;
#ifdef CONFIG_SECURE_BOOT
static unsigned int fdl1_image_offset = 1536;
#define SEC_HEADER_MAX_SIZE 4096
#endif

int sys_connect(PACKET_T *packet, void *arg)
{
    FDL_SendAckPacket(BSL_REP_ACK);
    return 1;
}

int data_start(PACKET_T *packet, void *arg)
{
    unsigned int *data = (unsigned int*)(packet->packet_body.content);
#if defined (CONFIG_UBOOT_INTERTWINE_ADDR)
	unsigned long int start_addr = 0;
#else
    unsigned int start_addr = *data;
#endif
    unsigned int file_size  = *(data + 1);
    chipram_env_t *p_env = (struct chipram_env *)CHIPRAM_ENV_ADDR;
#if defined (CHIP_ENDIAN_LITTLE)
#if defined (CONFIG_UBOOT_INTERTWINE_ADDR)
    start_addr = CONFIG_SYS_NAND_U_BOOT_DST - UBOOT_HASH_SIZE;
#else
    start_addr = EndianConv_32(start_addr);
#endif
    file_size  = EndianConv_32(file_size);
#endif

    if ((start_addr < MEMORY_START) || (start_addr >= MEMORY_START + MEMORY_SIZE))
    {
        while(1);
        FDL_SendAckPacket(BSL_REP_DOWN_DEST_ERROR);
        return 0;
    }

    if ((start_addr + file_size) > (MEMORY_START + MEMORY_SIZE))
    {
        while(1);
        FDL_SendAckPacket(BSL_REP_DOWN_SIZE_ERROR);
        return 0;
    }


	if (!chg_on_flag) {
		chg_on_flag = 0;
		p_env->keep_charge = 0;
	}

    g_file.start_address = start_addr;
    g_file.total_size = file_size;
    g_file.recv_size = 0;
    g_file.next_address = start_addr;

    FDL_memset((void*)start_addr, 0, file_size);
    if (!packet->ack_flag)
    {
        packet->ack_flag = 1;
        FDL_SendAckPacket(BSL_REP_ACK);
    }
    return 1;
}

int data_midst(PACKET_T *packet, void *arg)
{
    unsigned short data_len = packet->packet_body.size;

    if ((g_file.recv_size + data_len) > g_file.total_size) {
        FDL_SendAckPacket(BSL_REP_DOWN_SIZE_ERROR);
        return 0;
    }

    FDL_memcpy((void *)g_file.next_address, (const void*)(packet->packet_body.content), data_len);
    g_file.next_address += data_len;
    g_file.recv_size += data_len;
    if (!packet->ack_flag)
    {
        packet->ack_flag = 1;
        FDL_SendAckPacket(BSL_REP_ACK);
    }
    return 1;
}

int data_end(PACKET_T *packet, void *arg)
{
    if (!packet->ack_flag)
    {
        packet->ack_flag = 1;
        FDL_SendAckPacket(BSL_REP_ACK);
    }
    return 1;
}

int data_exec(PACKET_T *packet, void *arg)
{
//    JumpToTarget(g_file.start_address);
    typedef void(*entry)(void);
#if defined (CONFIG_X86) || defined (CONFIG_FDL_CHECK_SIGN)
	entry entry_func = g_file.start_address+UBOOT_HASH_SIZE;
#elif defined(CONFIG_DUAL_SPL)
	entry entry_func = g_file.start_address+UBOOT_HASH_SIZE;
	if(Fdl_Hash_Exist(g_file.start_address+UBOOT_HASH_SIZE_OFFSET,HASH_TEMP_LEN))
	{
	//add the sec_check
	sha256_csum_wd(g_file.start_address+UBOOT_HASH_SIZE,g_file.recv_size-UBOOT_HASH_SIZE,hash_temp,NULL);
	if(0!=sprd_memcmp(g_file.start_address+UBOOT_HASH_SIZE_OFFSET,hash_temp,HASH_TEMP_LEN))
		{
		FDL_SendAckPacket(BSL_REP_VERIFY_ERROR);
		while(1);
		}
	}
#else
	entry entry_func = g_file.start_address;
#endif

#ifdef CONFIG_SECURE_BOOT
    typedef sec_callback_func_t* (*get_secure_checkfunc_t) (sec_callback_func_t*);
    sec_callback_func_t     sec_callfunc;
    vlr_info_t*             vlr_info        = (vlr_info_t*)(g_file.start_address + 0x200);
    get_secure_checkfunc_t* get_secure_func = (get_secure_checkfunc_t*)(INTER_RAM_BEGIN+0x1c);
    (*get_secure_func)(&sec_callfunc);
#ifdef CONFIG_ROM_VERIFY_SPL
    sec_callfunc.secure_check(g_file.start_address + FDL2_CODE_OFF - 0x200, vlr_info->length, vlr_info, KEY_INFO_OFF);
    //FDL_memcpy((void *)(g_file.start_address - FDL2_CODE_OFF), g_file.start_address, FDL2_CODE_OFF);
    //FDL_memcpy((void *)g_file.start_address, g_file.start_address + FDL2_CODE_OFF, g_file.total_size - FDL2_CODE_OFF);    
    FDL_memcpy((void *)(CONFIG_SYS_SDRAM_BASE), g_file.start_address, FDL2_CODE_OFF);
	FDL_memcpy((void *)(g_file.start_address), g_file.start_address + FDL2_CODE_OFF, g_file.total_size - FDL2_CODE_OFF);
	#else
    sec_callfunc.secure_check(g_file.start_address + fdl1_image_offset, vlr_info->length, vlr_info, KEY_INFO_OFF);
    FDL_memcpy((void *)(g_file.start_address - SEC_HEADER_MAX_SIZE), g_file.start_address, SEC_HEADER_MAX_SIZE);
    FDL_memcpy((void *)g_file.start_address, g_file.start_address + fdl1_image_offset, g_file.total_size -fdl1_image_offset);
#endif
#endif

#if defined (CONFIG_ARCH_SCX35L2) || defined (CONFIG_SOC_PIKE2) || defined (CONFIG_SOC_IWHALE2) || defined(CONFIG_SOC_ISHARKL2) || defined (CONFIG_FDL_CHECK_SIGN)
#ifdef CONFIG_SECBOOT
	secboot_init();
	if(SECBOOT_VERIFY_SUCCESS != (secboot_verify(IRAM_BEGIN,g_file.start_address,NULL,NULL,SECURE_DOWNLOAD)))
	{
		while(1);
	}
#endif
#endif

#ifdef CONFIG_EXIT_FUN
	do_board_func();
#endif
#ifdef	CONFIG_SCX35L64
#ifndef CONFIG_X86
	extern void switch64_and_set_pc(u32 addr);
	switch64_and_set_pc(CONFIG_SYS_NAND_U_BOOT_START);
#else
    entry_func();
#endif
#else
    entry_func();
#endif
    return 0;
}

int set_baudrate(PACKET_T *packet, void *arg)
{
    unsigned int baudrate = *(unsigned int*)(packet->packet_body.content);
#if defined (CHIP_ENDIAN_LITTLE)
    baudrate = EndianConv_32(baudrate);
#endif
    if (!packet->ack_flag)
    {
        packet->ack_flag = 1;
        FDL_SendAckPacket(BSL_REP_ACK);
    }

    gFdlUsedChannel->SetBaudrate(gFdlUsedChannel, baudrate);

    return 0;
}

int set_chg_flag(PACKET_T *packet, void *arg)
{
	chipram_env_t *p_env = (struct chipram_env *)CHIPRAM_ENV_ADDR;
	if (!packet->ack_flag)
	{
		packet->ack_flag = 1;
		FDL_SendAckPacket(BSL_REP_ACK);
	}
	chg_on_flag = 1;
	p_env->keep_charge = 1;
	return 1;
}

#define FDL1_DDR_TSET_RESERVE_START	 0x5F0000
#define FDL1_DDR_TSET_RESERVE_END	 0x8F0000

extern int ddr_test(int start, int end);
int fdl1_ddr_test (void)
{
	if(0 != ddr_test(FDL1_DDR_TSET_RESERVE_START, FDL1_DDR_TSET_RESERVE_END))
		return -1;
	return 0;
}

int ddr_verify_start(PACKET_T *packet, void *arg)
{
	if( !fdl1_ddr_test() )
		FDL_SendAckPacket(BSL_REP_ACK);
	else
		FDL_SendAckPacket(BSL_DDR_VERIFY_FAIL);
#ifdef CONFIG_CHIP_ENV_SET
	chipram_env_set(BOOTLOADER_MODE_DOWNLOAD);
#endif
	return 0;
}

extern int ddr_sr_test(u32 timeout);

int ddr_sr_test_start(PACKET_T *packet, void *arg)
{
	unsigned int *data = (unsigned int*)(packet->packet_body.content);
	unsigned int time_out = *data;

	if(!ddr_sr_test(time_out))
		FDL_SendAckPacket(BSL_REP_ACK);
	else
		FDL_SendAckPacket(BSL_DDR_TEST_FAIL);
#ifdef CONFIG_CHIP_ENV_SET
	chipram_env_set(BOOTLOADER_MODE_DOWNLOAD);
#endif
	return 0;
}


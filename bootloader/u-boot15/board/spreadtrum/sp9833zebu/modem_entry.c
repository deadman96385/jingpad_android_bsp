#include <common.h>

#include <asm/arch/common.h>
//#include "normal_mode.h"
#include <asm/arch/sprd_reg.h>

#include "cp_boot.h"

#define CP0_ZERO_MAP_ADR    0x50000000
#define CP0_ARM0_EXEC_ADR        0x88400000

#define CP1_ZERO_MAP_ADR    0x50001000
#define CP1_EXEC_ADR        0x8ae00000

/*add macro for memset agdsp/tddsp/ldsp share memory*/
#define LDSP_SHARE_MEM_START 0xF2000//8k
#define TGDSP_SHARE_MEM_START 0xF4000//4k
#define AGDSP_SHARE_MEM_START 0xF5000//4k
#define MULTI_MODE_MEM_START 0xF6000//4k

#define PHYS_OFFSET_ADDR			0x80000000
//#define TD_CP_OFFSET_ADDR			0x8000000	/*128*/
//#define TD_CP_SDRAM_SIZE			0x1200000	/*18M*/
//#define WCDMA_CP_OFFSET_ADDR		0x10000000	/*256M*/
//#define WCDMA_CP_SDRAM_SIZE		0x4000000	/*64M*/
#define GGE_CP_OFFSET_ADDR 		0x08000000       /*128M*/
#define GGE_CP_SDRAM_SIZE 		0x01600000 	/*22M*/
#define LTE_CP_OFFSET_ADDR              0x09600000       /*150M*/
#define LTE_CP_SDRAM_SIZE 		0x06000000       /*96M*/
//#define PMIC_IRAM_ADDR 		0x50800000       /*pmic arm7 iram address remap at AP side*/
//#define PMIC_IRAM_SIZE 		0x8000       /*32K*/
#define SIPC_APCP_RESET_ADDR_SIZE	0xC00	/*3K*/
#define SIPC_APCP_RESET_SIZE	0x1000	/*4K*/
//#define SIPC_TD_APCP_START_ADDR		(PHYS_OFFSET_ADDR + TD_CP_OFFSET_ADDR + TD_CP_SDRAM_SIZE - SIPC_APCP_RESET_SIZE)	/*0x897FF000*/
//#define SIPC_WCDMA_APCP_START_ADDR	(PHYS_OFFSET_ADDR + WCDMA_CP_OFFSET_ADDR + WCDMA_CP_SDRAM_SIZE - SIPC_APCP_RESET_SIZE) /*0x93FFF000*/
//#define SIPC_GGE_APCP_START_ADDR 	(PHYS_OFFSET_ADDR + GGE_CP_OFFSET_ADDR + GGE_CP_SDRAM_SIZE - SIPC_APCP_RESET_SIZE) 	/*0x895ff000*/
#define SIPC_LTE_APCP_START_ADDR        (PHYS_OFFSET_ADDR + LTE_CP_OFFSET_ADDR + LTE_CP_SDRAM_SIZE - SIPC_APCP_RESET_SIZE)         /*0x8d5ff000*/
//#define SIPC_PMIC_APCP_START_ADDR        (PMIC_IRAM_ADDR+ PMIC_IRAM_SIZE+ - SIPC_APCP_RESET_ADDR_SIZE)         /*0x50807400*/

#define MAX_DYNAMIC_BIN_NAME_LEN 8
#define MAX_NAME_LEN 4
#define MAX_REGION_NUM 0x10
#define MAX_DYNAMIC_BIN_NUM 0x10
#define INVALID_FLAG 0x5a5a5a5a
#define MAGIC_NUMBER1 0x474D494D
#define MAGIC_NUMBER2 0x44414548
#define MAX_HEAD_LENGTH 0x800
#define MAX_SEARCH_LENGTH 0x4000

struct bin_info {
        u32 names[MAX_DYNAMIC_BIN_NAME_LEN];
        u32 tcm_load_base;
        u32 tcm_run_base;
        u32 ddr_load_base;
        u32 ddr_run_base;
        u32 offset1; /* tcm bin offset */
        u32 offset2; /* ddr bin offset */
        u32 size;
        u32 size2;
        u16 id;
        u16 status;
        u32 rw_base;
        u32 rw_length;
};

struct region_info{
        u32 names[MAX_NAME_LEN];
        u32 base;
        u32 size;
};

struct modem_image_head {
        u32 MAGIC1; /* MIMG */
        u32 MAGIC2; /* HEAD */
        u32 Version; /* V100 */
        u32 Count; /* region count */
        u32 Dbin_Count;
        struct region_info regions[MAX_REGION_NUM];
        struct bin_info bin_info[MAX_DYNAMIC_BIN_NUM];
        u32 reversed[1];
};

int cp_dynamic_loader(void)
{
        int i;
        u32 *magic1, *magic2;
        u32 baseaddress = LTE_MODEM_ADDR;
        struct modem_image_head *pmInfo;
        u32 jump_address;

        for(i=0; i<MAX_SEARCH_LENGTH/sizeof(u32); i++) {
                magic1 = (u32 *)(LTE_MODEM_ADDR+i*sizeof(u32));
                if(*magic1 == MAGIC_NUMBER1) {
                        magic2 = magic1+1;
                        if(*magic2 == MAGIC_NUMBER2)
                                break;
                }
        }
        if(i == MAX_SEARCH_LENGTH/sizeof(u32)) {
                debugf("dynamic load is not supported!\n");
                return -1;
        }

        pmInfo = (struct modem_image_head *)(LTE_MODEM_ADDR+i*sizeof(u32));
        jump_address = (u32)pmInfo + MAX_HEAD_LENGTH;
        g_loader[sizeof(g_loader)/sizeof(u32)-1] = jump_address;

        for(i = 0; i < pmInfo->Dbin_Count; i++) {
                struct bin_info *pBinInfo = &(pmInfo->bin_info[i]);
                if(pBinInfo->tcm_load_base != 0x5a5a5a5a)
                        memcpy((void*)pBinInfo->tcm_load_base, (void*)(baseaddress +
                              pBinInfo->offset1), pBinInfo->size);
                if(pBinInfo->ddr_load_base != 0x5a5a5a5a)
                        memcpy((void*)pBinInfo->ddr_load_base, (void*)(baseaddress +
                              pBinInfo->offset2), pBinInfo->size2);
        }

        return 0;
}

void cp_adr_remap(u32 cp_kernel_exec_addr, u32 cp_zero_map_addr)
{
    u32 data[3] = {0xe59f0000, 0xe12fff10,   cp_kernel_exec_addr};
    memcpy( cp_zero_map_addr, data, sizeof(data));      /* copy cp0 source code */
}

/*bug:533275  memset tg/l/agdsp share memory
root cause: In agdsp share IRAM memory ,this area exits command for agdsp,when interunpt happens
from ap or cp,the agdsp will use this area. While the area exit the dirty binary data ,ap or cp
do not clean up this area when interrupt happens at the right time,so error command will cause
unexcepted problems.*/

void memset_dsp_share_memory()
{
	memset((void *)LDSP_SHARE_MEM_START,0x0,0x2000);//8k
	memset((void *)TGDSP_SHARE_MEM_START,0x0,0x1000);//4k
	memset((void *)AGDSP_SHARE_MEM_START,0x0,0x1000);//4k
	memset((void *)MULTI_MODE_MEM_START,0x0,0x1000);//4k
}

void modem_entry()
{

	/*workaround,change wtlcp axi to 307.2M*/
	//REG32(REG_AON_APB_SUB_SYS_DBG_SIG7) = 0x09;

#ifndef CONFIG_KERNEL_BOOT_CP
	pmic_arm7_boot();
	//pubcp_boot();
	debugf("boot arm7 OK\n");
#else
	extern unsigned int g_charger_mode;
	if(g_charger_mode) {
		pmic_arm7_boot();
		debugf("boot arm7  OK\n");
	}
#endif
}

#ifdef CONFIG_MEM_LAYOUT_DECOUPLING
extern int get_ring_info(u64 *addr, u64 *size);
#else
int get_ring_info(u64 *addr, u64 *size)
{
	return -1;
}
#endif

void sipc_addr_reset()
{
	uint64_t addr;
	uint64_t size;

	if(get_ring_info(&addr, &size) == 0) {
		debugf("%s: ring addr = 0x%p, size = 0x%x\n", __func__, addr, size);
		memset((void *)addr, 0x0, size);
	} else {
		memset((void *)SIPC_LTE_APCP_START_ADDR, 0x0, SIPC_APCP_RESET_ADDR_SIZE);
	}

	return;
}


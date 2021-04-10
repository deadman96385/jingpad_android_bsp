
#include <sci_types.h>
extern void MMU_EnableIDCM (void);

const uint32 const_MMUTableStartAddr       = 0x81600000 - 16*1024;

// MMU page table starting address to be referred in mmu_asm.s
unsigned int *g_mmu_page_table;

void MMU_Init (unsigned pageBaseAddr)
{
    MMU_CacheEnable();
}

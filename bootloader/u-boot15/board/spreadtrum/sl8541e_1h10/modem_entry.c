#include <common.h>
#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>

#include "cp_boot.h"

/*add macro for memset agdsp/tddsp/ldsp share memory*/
#define DSP_BOOT_IRAM_START   0x11000//2k
#define LDSP_SHARE_MEM_START  0x11800//10k
#define TGDSP_SHARE_MEM_START 0x14000//4k
#define MULTI_MODE_MEM_START  0x15000//4k


/*bug:533275  memset tg/l/agdsp share memory
root cause: In agdsp share IRAM memory ,this area exits command for agdsp,when interunpt happens
from ap or cp,the agdsp will use this area. While the area exit the dirty binary data ,ap or cp
do not clean up this area when interrupt happens at the right time,so error command will cause
unexcepted problems.*/

void memset_dsp_share_memory()
{
	memset((void *)DSP_BOOT_IRAM_START,0x0,0x800);//2k
	memset((void *)LDSP_SHARE_MEM_START,0x0,0x2800);//10k
	memset((void *)TGDSP_SHARE_MEM_START,0x0,0x1000);//4k
	memset((void *)MULTI_MODE_MEM_START,0x0,0x1000);//4k
}

void modem_entry()
{
	memset_dsp_share_memory();

#ifndef CONFIG_KERNEL_BOOT_CP
	sp_boot();
	pubcp_boot();
	debugf("boot CP1 OK\n");
#else
	extern unsigned int g_charger_mode;
	if(g_charger_mode) {
		sp_boot();
		debugf("boot sp  OK\n");
	}
#endif
}


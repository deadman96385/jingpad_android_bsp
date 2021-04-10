#include <common.h>
#include <asm/arch/sprd_reg.h>
#include "cp_boot.h"

#define DSP_BOOT_IRAM_START		0x5000f000
#define TGDSP_SHARE_MEM_START	0x5000e000
#define MULTI_MODE_MEM_START	0x50010000


void memset_dsp_share_memory()
{
	memset((void *)DSP_BOOT_IRAM_START,0x0,0x1000);//4k
	memset((void *)TGDSP_SHARE_MEM_START,0x0,0x1000);//4k
	memset((void *)MULTI_MODE_MEM_START,0x0,0x800);//2k
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

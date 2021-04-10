#include <common.h>

#include <asm/arch/sprd_reg.h>

#include "cp_boot.h"

void modem_entry()
{
	agdsp_boot();
#ifndef CONFIG_KERNEL_BOOT_CP
	parm_modem_boot();
	pubcp_boot();
	debugf("boot CP1 OK\n");
#else
	extern unsigned int g_charger_mode;
	if(g_charger_mode) {
		parm_modem_boot();
		printf("boot CM4 OK\n");
	}
#endif
}


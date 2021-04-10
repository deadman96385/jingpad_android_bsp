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
#endif
}


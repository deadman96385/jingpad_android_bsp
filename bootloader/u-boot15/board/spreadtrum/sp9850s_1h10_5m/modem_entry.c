#include <common.h>

#include <asm/arch/common.h>
//#include "normal_mode.h"
#include <asm/arch/sprd_reg.h>

#include "cp_boot.h"

/*add macro for memset agdsp/tddsp/ldsp share memory*/
#define LDSP_SHARE_MEM_START 0xF2000//8k
#define TGDSP_SHARE_MEM_START 0xF4000//4k
#define AGDSP_SHARE_MEM_START 0xF5000//4k
#define MULTI_MODE_MEM_START 0xF6000//4k

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
	REG32(REG_AON_APB_SUB_SYS_DBG_SIG7) = 0x09;

	/*memset l/tg/agdsp share memory*/
	memset_dsp_share_memory();

	/*sipc addr clear*/
	sipc_addr_reset();
	agdsp_boot();
#ifndef CONFIG_KERNEL_BOOT_CP
	pmic_arm_m4_boot();
	pubcp_boot();
	debugf("boot CP1 OK\n");
#else
	extern unsigned int g_charger_mode;
	if(g_charger_mode) {
		pmic_arm_m4_boot();
		debugf("boot CM4 OK\n");
	}
#endif
}

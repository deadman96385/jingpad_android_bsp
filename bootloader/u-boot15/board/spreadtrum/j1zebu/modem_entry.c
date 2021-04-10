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



void memset_dsp_share_memory()
{
	memset((void *)LDSP_SHARE_MEM_START,0x0,0x2000);//8k
	memset((void *)TGDSP_SHARE_MEM_START,0x0,0x1000);//4k
	memset((void *)AGDSP_SHARE_MEM_START,0x0,0x1000);//4k
	memset((void *)MULTI_MODE_MEM_START,0x0,0x1000);//4k
}

void modem_entry()
{

}




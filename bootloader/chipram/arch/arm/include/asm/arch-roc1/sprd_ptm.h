#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <sci_types.h>
#include "sprd_reg.h"

#define PUB_BUS_CLK_EB		0x310531CC

#define PUB_PTM_EB		0x1C0

#define sprd_ptm_init()   \
	do{ \
		CHIP_REG_OR(PUB_BUS_CLK_EB, PUB_PTM_EB); \
	}while(0)

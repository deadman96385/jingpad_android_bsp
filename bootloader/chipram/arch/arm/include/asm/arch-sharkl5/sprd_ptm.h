#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <sci_types.h>
#include "sprd_reg.h"

#define PTM_CTL_BASE		SPRD_PERF_TRACE_PHYS
#define PTM_GRP_SEL		(PTM_CTL_BASE + 0x0020)

#define PTM_GRP_SEL_VAL		0x7fac688

#define sprd_ptm_init()   \
	do{ \
		CHIP_REG_SET(PTM_GRP_SEL, PTM_GRP_SEL_VAL); \
	}while(0)

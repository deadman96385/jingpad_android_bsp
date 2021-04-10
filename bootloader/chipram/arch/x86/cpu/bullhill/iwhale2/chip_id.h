#ifndef __CHIP_ID_H__
#define __CHIP_ID_H__

#ifdef   __cplusplus 
extern   "C" 
{ 
#endif

#include <sci_types.h>
#include <asm/arch/sprd_reg.h>

static uint32 get_chip_version(void)
{
	return REG32(REG_AON_APB_AON_VER_ID);
}

#ifdef   __cplusplus
}
#endif

#endif

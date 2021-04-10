#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>

static uint32_t sprd_get_chip_version(void)
{
	return REG32(REG_AON_APB_AON_VER_ID);
}

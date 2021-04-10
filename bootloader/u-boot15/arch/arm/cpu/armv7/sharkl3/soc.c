#include <common.h>

#ifndef CONFIG_SYS_DCACHE_OFF
void enable_caches(void)
{

	/* Enable D-cache. I-cache is already enabled in start.S */
	dcache_enable();
}
#endif


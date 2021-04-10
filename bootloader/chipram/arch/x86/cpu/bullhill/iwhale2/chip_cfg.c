
#include <sci_types.h>

unsigned int FDL_GetBootMode (void)
{
	uint32 bootMode = 0;
	bootMode = (* (volatile uint32 *) (0xE60227F0) >> 8) & 0xff;
	return bootMode;
}


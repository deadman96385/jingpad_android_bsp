
#include <sci_types.h>

uint32 FDL_GetBootMode (void)
{
    uint32 bootMode = 0;
#if defined(CONFIG_WHALE2)
    bootMode = (* (volatile uint32 *) (0x00027EF0) >> 8) & 0xff;
#else
    bootMode = (* (volatile uint32 *) (0x00006FF0) >> 8) & 0xff;
#endif
return bootMode;
}



#include <sci_types.h>

uint32 FDL_GetBootMode (void)
{
    uint32 bootMode = 0;
#ifdef BOOT_FLAG_ADDRESS
    bootMode = (* (volatile uint32 *) (BOOT_FLAG_ADDRESS) >> 8) & 0xff;
#else
    bootMode = (* (volatile uint32 *) (0x5000cff4) >> 8) & 0xff;
#endif
    return bootMode;
}

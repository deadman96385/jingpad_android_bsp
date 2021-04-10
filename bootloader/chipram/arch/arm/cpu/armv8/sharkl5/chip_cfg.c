
#include <sci_types.h>

uint32 FDL_GetBootMode (void)
{
    uint32 bootMode = 0;
    bootMode = (* (volatile uint32 *) (BOOT_FLAG_ADDRESS) >> 8) & 0xff;/*romcode addr*/
    return bootMode;
}



#include <sci_types.h>


uint32 FDL_GetBootMode (void)
{
    uint32 bootMode = 0;
    bootMode = (* (volatile uint32 *) (0x5000cff4) >> 8) & 0xff;
    return bootMode;
}


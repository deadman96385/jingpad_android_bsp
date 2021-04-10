#ifndef __FDL_STDIO_H_
#define ___FDL_STDIO_H

#include <sci_types.h>

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void*)0)
#endif /* __cplusplus */
#endif /* NULL */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/******************************************************************************
 * FDL_memcpy
 ******************************************************************************/
void *FDL_memcpy (void *dst, const void *src, unsigned int count);

/******************************************************************************
 * FDL_memset
 ******************************************************************************/
void *FDL_memset (void *dst, int c, unsigned int count);
unsigned short EndianConv_16 (unsigned short value);
unsigned int EndianConv_32 (unsigned int value);
unsigned long EndianConv_64 (unsigned long value);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* FDL_STDIO_H */


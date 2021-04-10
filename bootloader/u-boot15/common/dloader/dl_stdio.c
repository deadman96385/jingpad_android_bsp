#include <common.h>

void *FDL_memcpy (void *dst, const void *src, unsigned int count)
{
    void *ret = dst;
    unsigned int *tmp_dst = (unsigned int *) dst;
    unsigned int word_num, i;
    unsigned int value;

    while (count-->0)
    {
        * (char *) dst = * (char *) src;
        dst = (char *) dst + 1;
        src = (char *) src + 1;
    }


    return ret;
}

void *FDL_memset (void *dst, int c, unsigned int count)
{
    void *ret = dst;

    while (count--)
    {
        * (char *) dst = (char) c;
        dst = (char *) dst + 1;
    }

    return ret;
}

/*****************************************************************************/
//  Description:
//  Global resource dependence:
//  Author:         Daniel.Ding
//  Note:
/*****************************************************************************/
unsigned short EndianConv_16 (unsigned short value)
{
#ifdef _LITTLE_ENDIAN
    return (value >> 8 | value << 8);
#else
    return value;
#endif
}

unsigned int EndianConv_32 (unsigned int value)
{
#ifdef _LITTLE_ENDIAN
    unsigned int nTmp = 0;
	nTmp = (value >> 24 | value << 24);

    nTmp |= ( (value >> 8) & 0x0000FF00);
    nTmp |= ( (value << 8) & 0x00FF0000);
    return nTmp;
#else
    return value;
#endif
}


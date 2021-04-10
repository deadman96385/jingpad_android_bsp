#include <fdl_stdio.h>

#if defined (CONFIG_ARM64)
void * FDL_memcpy(void *dest, const void *src, unsigned int count)
{
    unsigned long *dl = (unsigned long *)dest, *sl = (unsigned long *)src;
    char *d8, *s8;

    if (src == dest)
        return dest;

    /* while all data is aligned (common case), copy a word at a time */
    if ( (((ulong)dest | (ulong)src) & (sizeof(*dl) - 1)) == 0) {
        while (count >= sizeof(*dl)) {
            *dl++ = *sl++;
            count -= sizeof(*dl);
        }
    }
    /* copy the reset one byte at a time */
    d8 = (char *)dl;
    s8 = (char *)sl;
    while (count--)
        *d8++ = *s8++;

    return dest;
}

#else
void *FDL_memcpy (void *dst, const void *src, unsigned int count)
{
    void *ret = dst;
    unsigned int *tmp_dst = (unsigned int *) dst;
    unsigned int word_num, i;
    unsigned int value;


#if ((defined(SC8800S_LITTLE_ENDIAN) && defined(_BIG_ENDIAN))) || (defined(FDL_ENDIAN_SWITCH))//temp for data swap in fdl1
    count =  count / 4;

    while (count-->0)
    {
        value = * (unsigned int *) src;
        *tmp_dst = ( (value & 0x000000ff) <<24) | ( (value & 0xff000000) >>24) | ( (value & 0x0000ff00) <<8) | ( (value & 0x00ff0000) >>8);
        tmp_dst = (unsigned int *) tmp_dst + 1;
        src = (unsigned int *) src + 1;
    }

#else

    while (count-->0)
    {
        * (char *) dst = * (char *) src;
        dst = (char *) dst + 1;
        src = (char *) src + 1;
    }

#endif


    return ret;
}
#endif


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

unsigned long EndianConv_64 (unsigned long value)
{
#ifdef _LITTLE_ENDIAN
    unsigned long nTmp = 0;
    nTmp = (value >> 56 | value << 56);
    nTmp |=  ((value >> 48) & 0x000000000000FF00);
    nTmp |=  ((value << 48) & 0x00FF000000000000);
    nTmp |=  ((value >> 24) & 0x0000000000FF0000);
    nTmp |=  ((value << 24) & 0x0000FF0000000000);
    nTmp |=  ((value >> 8)  & 0x00000000FF000000);
    nTmp |=  ((value << 8)  & 0x000000FF00000000);
    return nTmp;
#else
    return value;
#endif
}

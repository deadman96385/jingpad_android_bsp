#include <config.h>
#include <linux/types.h>

/*use this instead of memset ,they are the same*/
void * sprd_memset(void * string,int fill,size_t cnt)
{
	unsigned long *stl = (unsigned long *) string;
	unsigned long fl = 0;
	int i = 0;
	char *st8;

	/* do one word  a time while possible */
	if ( ((ulong)string & (sizeof(*stl) - 1)) == 0)
	{
		for (i = 0; i < sizeof(*stl); i++)
		{
			fl <<= 8;
			fl |= fill & 0xff;
		}
		while (cnt >= sizeof(*stl))
		{
			*stl++ = fl;
			cnt -= sizeof(*stl);
		}
	}
	/* fill 8 bits*/
	st8 = (char *)fl;
	while (cnt--)
	{
		*st8++ = fill;
	}

	return string;
}
void* memset(void* s, int c, size_t n)
{
    unsigned char* p = (unsigned char*) s;

    while (n > 0) {
    *p++ = (unsigned char) c;
    --n;
    }

    return s;
}

void * sprd_memcpy(void *dst, const void *src, size_t cnt)
{
	unsigned long *dlt = (unsigned long *)dst, *slt = (unsigned long *)src;
	char *d8, *st8;

	/* while all data is aligned (common case), copy a word at a time */
	if ( (((ulong)dst | (ulong)src) & (sizeof(*dlt) - 1)) == 0) {
		while (cnt >= sizeof(*dlt)) {
			*dlt++ = *slt++;
			cnt -= sizeof(*dlt);
		}
	}
	/* copy the reset one byte at a time */
	d8 = (char *)dlt;
	st8 = (char *)slt;
	while (cnt--)
		*d8++ = *st8++;

	return dst;
}
int sprd_strcmp(const char * cs,const char * ct)
{
	register signed char __res;

	while (1) {
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
	}

	return __res;
}
#if (defined(CONFIG_DUAL_SPL)||defined(CONFIG_DUAL_BACKUP))
int sprd_memcmp(void *s1, void *s2, int len)
{
       const int *p1, *q1;
       const char *p2, *q2;
       int off, mod;

       off = len >> 2;
       mod = len - (off << 2);

       if (mod > 0) {
               p2 = (const char *)s1;
               q2 = (const char *)s2;
               while (mod --) {
                       if (*p2 ++ != *q2 ++) {
                               return p2[-1] > q2[-1] ? 1 : -1;
                       }
               }
       }
       /* if p1 & q1 address don't align with 4 bytes,
          how about the efficiency ? */
       mod = len - (off << 2);
       p1 = (const int *)(s1 + mod);
       q1 = (const int *)(s2 + mod);

       while (off --) {
               if (*p1 ++ != *q1 ++) {
                       return p1[-1] > q1[-1] ? 1 : -1;
               }
       }

       return 0;
}
#endif



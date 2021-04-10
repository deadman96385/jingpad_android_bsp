

#ifndef __COMMON_H_
#define __COMMON_H_	1

#undef	_LINUX_CONFIG_H
#define _LINUX_CONFIG_H 1	/* avoid reading Linux autoconf.h file	*/

#ifndef __ASSEMBLY__		/* put C only stuff in this section */

typedef unsigned char		uchar;
typedef volatile unsigned long	vu_long;
typedef volatile unsigned short vu_short;
typedef volatile unsigned char	vu_char;

#include <config.h>
#include <linux/types.h>
#include <stdarg.h>
#include <asm/u-boot.h> /* boot information for Linux kernel */
//#include <asm/global_data.h>	/* global data used for startup functions */

#ifdef CONFIG_ARM
# include <asm/u-boot-arm.h>	/* ARM version to be fixed! */
#endif /* CONFIG_ARM */

/*
 * abs() handles unsigned and signed longs, ints, shorts and chars.  For all
 * input types abs() returns a signed long.
 * abs() should not be used for 64-bit types (s64, u64, long long) - use abs64()
 * for those.
 */
#define abs(x) ({						\
		long ret;					\
		if (sizeof(x) == sizeof(long)) {		\
			long __x = (x);				\
			ret = (__x < 0) ? -__x : __x;		\
		} else {					\
			int __x = (x);				\
			ret = (__x < 0) ? -__x : __x;		\
		}						\
		ret;						\
	})

#define DIV_ROUND_UP(n,d)	(((n) + (d) - 1) / (d))
#define rounddown(x, y) (				\
{							\
	typeof(x) __x = (x);				\
	__x - (__x % (y));				\
}							\
)

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)

#define __WARN() printf("warning @ %s: %d\n", __func__, __LINE__)

#define WARN_ON(condition) ({						\
	int __ret_warn_on = !!(condition);				\
	if (unlikely(__ret_warn_on))					\
		__WARN();						\
	unlikely(__ret_warn_on);					\
})


#define error(fmt, args...) do {					\
		printf("ERROR: " fmt "\nat %s:%d/%s()\n",		\
			##args, __FILE__, __LINE__, __func__);		\
} while (0)

#ifndef BUG
#define BUG() do { \
	printf("FAIL: bug at %s:%d/%s()!\n", __FILE__, __LINE__, __FUNCTION__); \
	panic("BUG!"); \
} while (0)
#define BUG_ON(cdt) do { if (unlikely((cdt)!=0)) BUG(); } while(0)
#endif /* BUG */

#define	TOTAL_MALLOC_LEN	CONFIG_SYS_MALLOC_LEN



#endif /* __ASSEMBLY__ */

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))




#endif	/* __COMMON_H_ */

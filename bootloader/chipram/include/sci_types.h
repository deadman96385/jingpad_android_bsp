#ifndef SCI_TYPES_H
#define SCI_TYPES_H

#include <linux/types.h>
#include <config.h>
#include <bits.h>
#include <clock_def.h>
#include <reg_io.h>

#define __align(_x) __attribute__((aligned(_x)))
#define __inline inline

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL  0
#endif

#ifndef bool
typedef int bool;
#endif

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

typedef int	BOOLEAN;
typedef unsigned char	uint8;
typedef unsigned short	uint16;
typedef unsigned int	uint32;
typedef unsigned long long	uint64;
typedef signed char	int8;
typedef signed short	int16;
typedef signed int	int32;
typedef signed long long	int64;

#define	LOCAL	static
#define PUBLIC

#define  MAX( _x, _y ) ( ((_x) > (_y)) ? (_x) : (_y) )

#define  MIN( _x, _y ) ( ((_x) < (_y)) ? (_x) : (_y) )

#endif

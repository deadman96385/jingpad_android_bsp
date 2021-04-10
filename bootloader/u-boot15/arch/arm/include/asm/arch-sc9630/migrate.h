#ifndef __MIGRATE_H__
#define __MIGRATE_H__
#include <linux/types.h>
#include <config.h>
#include <version.h>

#define _X_64
#define __align(_x) __attribute__((aligned(_x)))
#define __inline inline
#if 0
#define REG32(_x) (*(volatile unsigned int *)(_x))
#define PUBLIC
#define VOLATILE volatile
#define LOCAL       static
#define CONST       const
typedef unsigned char BOOLEAN;
typedef uint32_t uint32;
typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint64_t uint64;
typedef int32_t int32;
typedef int8_t int8;
typedef int16_t int16;
typedef int64_t int64;
#endif
#define sio_trace printf

#endif

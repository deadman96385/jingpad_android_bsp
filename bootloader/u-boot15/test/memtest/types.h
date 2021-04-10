/*
 * Very simple but very effective user-space memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2010 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains typedefs, structure, and union definitions.
 *
 */


#ifndef _TYPES_H_
#define _TYPES_H_

#include <config.h>
#include <linux/types.h>
#include <common.h>

#define rand32() ((unsigned int) rand() | ( (unsigned int) rand() << 16))

#ifndef CONFIG_ARM64
    #define rand_ul() rand32()
    #define UL_ONEBITS 0xffffffff
    #define UL_LEN 32
    #define CHECKERBOARD1 0x55555555
    #define CHECKERBOARD2 0xaaaaaaaa
    #define UL_BYTE(x) ((x | x << 8 | x << 16 | x << 24))
#else
    #define rand64() (((ul) rand32()) << 32 | ((ul) rand32()))
    #define rand_ul() rand64()
    #define UL_ONEBITS 0xffffffffffffffffUL
    #define UL_LEN 64
    #define CHECKERBOARD1 0x5555555555555555
    #define CHECKERBOARD2 0xaaaaaaaaaaaaaaaa
    #define UL_BYTE(x) (((ul)x | (ul)x<<8 | (ul)x<<16 | (ul)x<<24 | (ul)x<<32 | (ul)x<<40 | (ul)x<<48 | (ul)x<<56))
#endif


typedef unsigned long ul;
typedef unsigned long long ull;
typedef unsigned long volatile ulv;
typedef unsigned char volatile u8v;
typedef unsigned short volatile u16v;

struct test {
    char *name;
    int (*fp)();
};

union {
    unsigned char bytes[UL_LEN/8];
    ul val;
} mword8;

union {
    unsigned short u16s[UL_LEN/16];
    ul val;
} mword16;

typedef struct refresh_t_ {
	ulv *bufa;
	ulv *bufb;
	size_t count;
	int time;
	int use;
	int do_mlock;
}refresh_t, *lprefresh_t;

#define MODE_NORMAL 1
#define MODE_REFRESH 2

#endif

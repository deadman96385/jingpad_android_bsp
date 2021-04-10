/*
 * Very simple yet very effective memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2012 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains the declarations for the functions for the actual tests,
 * called from the main routine in memtester.c.  See other comments in that 
 * file.
 *
 */
#define UL_ONEBITS 0xffffffff
#define UL_LEN 32
#define CHECKERBOARD1 0x55555555
#define CHECKERBOARD2 0xaaaaaaaa
#define UL_BYTE(x) ((x | x << 8 | x << 16 | x << 24))

/* Function declaration. */

int test_stuck_address(unsigned int *bufa, unsigned int count);
int test_random_value(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_xor_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_sub_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_mul_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_div_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_or_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_and_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_seqinc_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_solidbits_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_checkerboard_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_blockseq_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_walkbits0_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_walkbits1_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_bitspread_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_bitflip_comparison(unsigned int *bufa, unsigned int *bufb, unsigned int count);
#ifdef TEST_NARROW_WRITES    
int test_8bit_wide_random(unsigned int *bufa, unsigned int *bufb, unsigned int count);
int test_16bit_wide_random(unsigned int *bufa, unsigned int *bufb, unsigned int count);
#endif
int test_bitflip_comparison_tiger(unsigned int *bufa, unsigned int *bufb, unsigned int count);

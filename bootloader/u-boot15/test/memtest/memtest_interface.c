/*
 * Very simple but very effective user-space memory tester.
 * Originally by Simon Kirby <sim@stormix.com> <sim@neato.org>
 * Version 2 by Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Version 3 not publicly released.
 * Version 4 rewrite:
 * Copyright (C) 2004-2012 Charles Cazabon <charlesc-memtester@pyropus.ca>
 * Licensed under the terms of the GNU General Public License version 2 (only).
 * See the file COPYING for details.
 *
 * This file contains the functions for the actual tests, called from the
 * main routine in memtester.c.  See other comments in that file.
 *
 */
#define TEST_NARROW_WRITES

#include "types.h"
#include "memtest_interface.h"
#include <loader_common.h>
#include <common.h>
#include <linux/input.h>

char progress[] = "-\\|/";
#define PROGRESSOFTEN 2500
#define ONE 0x00000001L

static int compare_20_times =0;
/* Function definitions. */

#define fprintf lcd_printf
#define printf lcd_printf

static ulv *sr_addr;
static ulv *dst_addr;
typedef long off_t;
off_t physaddrbase = 0x80000000;
int use_phys = 1;

struct memtest {
    char *name;
    int (*fp)();
};


struct memtest tests[] = {
	{ "stuck address",test_stuck_address},
	{ "Random Value", test_random_value },
	{ "Compare XOR", test_xor_comparison },
	{ "Compare SUB", test_sub_comparison },
	{ "Compare MUL", test_mul_comparison },
	{ "Compare DIV",test_div_comparison },
	{ "Compare OR", test_or_comparison },
	{ "Compare AND", test_and_comparison },
	{ "Compare seqinc", test_seqinc_comparison },
	{ "Compare solidbits", test_solidbits_comparison },
	{ "Compare checkerboard", test_checkerboard_comparison },
	{ "Compare blockseq", test_blockseq_comparison },
	{ "Compare walkbits0", test_walkbits0_comparison },
	{ "Compare walkbits1", test_walkbits1_comparison },
	{ "Compare bitspread", test_bitspread_comparison },
	{ "Compare bitflip", test_bitflip_comparison },
	{ "Compare 8bit wide random", test_8bit_wide_random },
	{ "Compare 16bit wide random", test_16bit_wide_random },
};

void readRepeat(ulv *p1, ulv *p2, ulv *bufa, ulv *bufb, size_t count,
		int n_repeat)
{
	int i = 0;
	int result = NULL;

	for (i = 0; i < n_repeat; i++)
	{
		result = (*p1 == *p2)?0:-1;
		if (result)
		{
			compare_20_times ++;
		}
	}
}

int compare_regions(ulv *bufa, ulv *bufb, size_t count)
{
	int r = 0;
	size_t i,j;
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	off_t physaddr;
	p1 = bufa;
	p2 = bufb;

	for (i = 0; i < count; i++, p1++, p2++) {
		if (*p1 != *p2) {
			//physaddr = sr_addr + (i * sizeof(ul));
			fprintf( "FAILURE: 0x%08lx != 0x%08lx at physical address "
				 "0x%08lx.\n",(ul) *p1, (ul) *p2, p1);
			while(1);
		}
	}
	return r;
}

int test_stuck_address(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	unsigned int j;
	size_t i;
	off_t physaddr;

	for (j = 0; j < 16; j++) {
		p1 = (ulv *) bufa;
		for (i = 0; i < count; i++) {
			*p1 = ((j + i) % 2) == 0 ? (ul) p1 : ~((ul) p1);
			p1++;
		}
		p1 = (ulv *) bufa;
		for (i = 0; i < count; i++, p1++) {
			if (*p1 != (((j + i) % 2) == 0 ? (ul) p1 : ~((ul) p1)))
			{
				//physaddr = sr_addr + (i * sizeof(ul));
				fprintf("FAILURE: possible bad address line at physical "
					"address 0x%08lx.\n", p1);
				while(1);
			}
		}
	}
	return 0;
}

int test_random_value(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	ul j = 0;
	size_t i;

	for (i = 0; i < count; i++) {
		*p1++ = *p2++ = rand_ul();
	}
	return compare_regions(bufa, bufb, count);
}

int test_xor_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	size_t i;
	ul q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ ^= q;
		*p2++ ^= q;
	}
	return compare_regions(bufa, bufb, count);
}

int test_sub_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	size_t i;
	ul q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ -= q;
		*p2++ -= q;
	}
	return compare_regions(bufa, bufb, count);
}

int test_mul_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	size_t i;
	ul q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ *= q;
		*p2++ *= q;
	}
	return compare_regions(bufa, bufb, count);
}

int test_div_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	size_t i;
	ul q = rand_ul();

	for (i = 0; i < count; i++) {
		if (!q) {
			q++;
		}
		*p1++ /= q;
		*p2++ /= q;
	}
	return compare_regions(bufa, bufb, count);
}

int test_or_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	size_t i;
	ul q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ |= q;
		*p2++ |= q;
	}
	return compare_regions(bufa, bufb, count);
}

int test_and_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	size_t i;
	ul q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ &= q;
		*p2++ &= q;
	}
	return compare_regions(bufa, bufb, count);
}

int test_seqinc_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	size_t i;
	ul q = rand_ul();

	for (i = 0; i < count; i++) {
		*p1++ = *p2++ = (i + q);
	}
	return compare_regions(bufa, bufb, count);
}

int test_solidbits_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	unsigned int j;
	ul q;
	size_t i;

	for (j = 0; j < 32; j++) {
		q = (j % 2) == 0 ? UL_ONEBITS : 0;
		p1 = (ulv *) bufa;
		p2 = (ulv *) bufb;
		for (i = 0; i < count; i++) {
			*p1++ = *p2++ = (i % 2) == 0 ? q : ~q;
		}
		if (compare_regions(bufa, bufb, count)) {
			return -1;
		}
	}
	return 0;
}

int test_checkerboard_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	unsigned int j;
	ul q;
	size_t i;

	for (j = 0; j < 32; j++) {
		q = (j % 2) == 0 ? CHECKERBOARD1 : CHECKERBOARD2;
		p1 = (ulv *) bufa;
		p2 = (ulv *) bufb;
		for (i = 0; i < count; i++) {
			*p1++ = *p2++ = (i % 2) == 0 ? q : ~q;
		}
		if (compare_regions(bufa, bufb, count)) {
			return -1;
		}
	}
	return 0;
}

int test_blockseq_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	unsigned int j;
	size_t i;

	for (j = 0; j < 256; j++) {
		p1 = (ulv *) bufa;
		p2 = (ulv *) bufb;
		for (i = 0; i < count; i++) {
			*p1++ = *p2++ = (ul) UL_BYTE(j);
		}
		if (compare_regions(bufa, bufb, count)) {
			return -1;
		}
	}
	return 0;
}

int test_walkbits0_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	unsigned int j;
	size_t i;
	for (j = 0; j < UL_LEN * 2; j++) {
		p1 = (ulv *) bufa;
		p2 = (ulv *) bufb;
		for (i = 0; i < count; i++) {
			if (j < UL_LEN) { /* Walk it up. */
				*p1++ = *p2++ = ONE << j;
			} else { /* Walk it back down. */
				*p1++ = *p2++ = ONE << (UL_LEN * 2 - j - 1);
			}
		}
		if (compare_regions(bufa, bufb, count)) {
			return -1;
		}
	}
	return 0;
}

int test_walkbits1_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	unsigned int j;
	size_t i;

	for (j = 0; j < UL_LEN * 2; j++) {
		p1 = (ulv *) bufa;
		p2 = (ulv *) bufb;
		for (i = 0; i < count; i++) {
			if (j < UL_LEN) { /* Walk it up. */
				*p1++ = *p2++ = UL_ONEBITS ^ (ONE << j);
			} else { /* Walk it back down. */
				*p1++ = *p2++ = UL_ONEBITS ^ (ONE << (UL_LEN * 2 - j - 1));
			}
		}
		if (compare_regions(bufa, bufb, count)) {
			return -1;
		}
	}
	return 0;
}

int test_bitspread_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	unsigned int j;
	size_t i;

	for (j = 0; j < UL_LEN * 2; j++) {
		p1 = (ulv *) bufa;
		p2 = (ulv *) bufb;
		for (i = 0; i < count; i++) {
			if (j < UL_LEN) { /* Walk it up. */
				*p1++ = *p2++ = (i % 2 == 0)
					? (ONE << j) | (ONE << (j + 2))
					: UL_ONEBITS ^ ((ONE << j)
							| (ONE << (j + 2)));
			} else { /* Walk it back down. */
				*p1++ = *p2++ = (i % 2 == 0)
					? ((ONE << (UL_LEN * 2 - 1 - j))
					   | (ONE << (UL_LEN * 2 + 1 - j)))
					: UL_ONEBITS ^ (ONE << (UL_LEN * 2 - 1 - j)
							| (ONE << (UL_LEN * 2 + 1 - j)));
			}
		}
		if (compare_regions(bufa, bufb, count)) {
			return -1;
		}
	}
	return 0;
}

int test_bitflip_comparison(ulv *bufa, ulv *bufb, size_t count) {
	ulv *p1 = bufa;
	ulv *p2 = bufb;
	unsigned int j, k;
	ul q;
	size_t i;

	for (k = 0; k < UL_LEN; k++) {
		q = ONE << k;
		for (j = 0; j < 8; j++) {
			q = ~q;
			p1 = (ulv *) bufa;
			p2 = (ulv *) bufb;
			for (i = 0; i < count; i++) {
				*p1++ = *p2++ = (i % 2) == 0 ? q : ~q;
			}
			if (compare_regions(bufa, bufb, count)) {
				return -1;
			}
		}
	}
	return 0;
}

void switch_for_tiger(ulv *p){
	char *r0;
	char *r1;
	char new_r0[4],new_r1[4];
	ulv *p_r = p;
	int i;

#define copy_byte(__x,__y) do{\
    __y = __x;}while(0)

/*Change method:
SW_original:
Word data:  0x77665544
Address 0x4:    7   6   5   4
Byte data:  0x77    0x66    0x55    0x44

Word data:  0x33221100
Address 0x0:    3   2   1   0
Byte data:  0x33    0x22    0x11    0x00

    |
    |
    V

SW_Swap:
Word data:  0x33772266
Address 0x4:    7   6   5   4
Byte data:  0x33    0x77    0x22    0x66

Word data:  0x11550044
Addrees 0x0:    3   2   1   0
Byte data:  0x11    0x55    0x00    0x44

r0_0 -> new_r0_1
r0_1 -> new_r0_3
r0_2 -> new_r1_1
r0_3 -> new_r1_3
r1_0 -> new_r0_0
r1_1 -> new_r0_2
r1_2 -> new_r1_0
r1_3 -> new_r1_2*/

    /*switch p,p-1*/
    r1 = (char *)(p_r--);
    r0 = (char *)p_r;
/*    printf("r1=0x%08lx,*r1=0x%08lx\n",r1,*(ulv*)r1);
    printf("r0=0x%08lx,*r0=0x%08lx\n",r0,*(ulv*)r0);*/
    copy_byte(r0[0],new_r0[1]);
    copy_byte(r0[1],new_r0[3]);
    copy_byte(r0[2],new_r1[1]);
    copy_byte(r0[3],new_r1[3]);
    copy_byte(r1[0],new_r0[0]);
    copy_byte(r1[1],new_r0[2]);
    copy_byte(r1[2],new_r1[0]);
    copy_byte(r1[3],new_r1[2]);
    for(i = 0; i < 4; i++){
        r0[i] = new_r0[i]; /*write back*/
        r1[i] = new_r1[i];
    }
/*    printf("r1=0x%08lx,*r1=0x%08lx\n",r1,*(ulv*)r1);
    printf("r0=0x%08lx,*r0=0x%08lx\n",r0,*(ulv*)r0);*/
}

int test_bitflip_comparison_tiger(ulv *bufa, ulv *bufb, size_t count) {
    ulv *p1 = bufa;
    ulv *p2 = bufb;
    /*ulv *temp;*/
    unsigned int j, k;
    ul q;
    size_t i;
    //printf("           ");
    if (sizeof(ulv) != 4){
        printf("This test only support for 32bit Architecture");
        return -1;
    }

    for (k = 0; k < UL_LEN; k++) {
        q = ONE << k;
        for (j = 0; j < 8; j++) {
            //printf("\b\b\b\b\b\b\b\b\b\b\b");
            q = ~q;
            //printf("setting %3u", k * 8 + j);
            p1 = (ulv *) bufa;
            p2 = (ulv *) bufb;
            for (i = 0; i < count; i++) {
                *p1++ = *p2++ = (i % 2) == 0 ? q : ~q;
                if ((i > 0) && ((i % 2) == 1)){  /*switch for tiger*/
                   /* *temp = 0x33221100;
                    *p1 = 0x77665544;
                    //printf("\nbefore switch: 0x%8X 0x%8X\n",*(ulv *)temp,*(ulv *)p1);
                    //printf("\nbefore switch p1 i=%d : 0x%08lX 0x%08lX\n",i,*(ulv *)(p1-1),*(ulv *)p1);
                    //printf("\nbefore switch p2 i=%d : 0x%08lX 0x%08lX\n",i,*(ulv *)(p2-1),*(ulv *)p2);*/
                    switch_for_tiger(p1-1);
		    switch_for_tiger(p2-1);
		    /*    printf("\nafter switch p1 i=%d : 0x%08lX 0x%08lX\n",i,*(ulv *)(p1-1),*(ulv *)p1);
                    printf("\nafter switch p2 i=%d : 0x%08lX 0x%08lX\n",i,*(ulv *)(p2-1),*(ulv *)p2);
                }else{
                    temp = p1;*/
                }
            }
            //printf("\b\b\b\b\b\b\b\b\b\b\b");
            //printf("testing %3u", k * 8 + j);
            if (compare_regions(bufa, bufb, count)) {
                return -1;
            }
        }
    }
    //printf("\b\b\b\b\b\b\b\b\b\b\b           \b\b\b\b\b\b\b\b\b\b\b");
    return 0;
}


#ifdef TEST_NARROW_WRITES
int test_8bit_wide_random(ulv* bufa, ulv* bufb, size_t count) {
    u8v *p1, *t;
    ulv *p2;
    int attempt;
    unsigned int b, j = 0;
    size_t i;

    for (attempt = 0; attempt < 2;  attempt++) {
        if (attempt & 1) {
            p1 = (u8v *) bufa;
            p2 = bufb;
        } else {
            p1 = (u8v *) bufb;
            p2 = bufa;
        }
        for (i = 0; i < count; i++) {
            t = mword8.bytes;
            *p2++ = mword8.val = rand_ul();
            for (b=0; b < UL_LEN/8; b++) {
                *p1++ = *t++;
            }
            if (!(i % PROGRESSOFTEN)) {
            }
        }
        if (compare_regions(bufa, bufb, count)) {
            return -1;
        }
    }
    return 0;
}

int test_16bit_wide_random(ulv* bufa, ulv* bufb, size_t count) {
    u16v *p1, *t;
    ulv *p2;
    int attempt;
    unsigned int b, j = 0;
    size_t i;

    for (attempt = 0; attempt < 2; attempt++) {
        if (attempt & 1) {
            p1 = (u16v *) bufa;
            p2 = bufb;
        } else {
            p1 = (u16v *) bufb;
            p2 = bufa;
        }
        for (i = 0; i < count; i++) {
            t = mword16.u16s;
            *p2++ = mword16.val = rand_ul();
            for (b = 0; b < UL_LEN/16; b++) {
                *p1++ = *t++;
            }
            if (!(i % PROGRESSOFTEN)) {
            }
        }
        if (compare_regions(bufa, bufb, count)) {
            return -1;
        }
    }
    return 0;
}
#endif

int compare_regions_tag(ulv *bufa, ulv *bufb, size_t count) {
    int r = 0;
    size_t i,j;
    ulv *p1 = bufa;
    ulv *p2 = bufb;
    off_t physaddr;

    for (j = 0; j < 20; j++)
    {
        p1 = bufa;
        p2 = bufb;

        for (i = 0; i < count; i++, p1++, p2++) {
            if (*p1 != *p2) {
#undef DEBUG_COMPARE
#           ifdef DEBUG_COMPARE
                printfTag("0x%08x: 0x%08lx  |  0x%08lx\n",i,*p1,*p2);
#           else
                if (use_phys) {
                    physaddr = physaddrbase + (i * sizeof(ul));
                    fprintf(fileno(stdout),
                            "Compare times: %d.\n",
                            (j+1));
                    fprintf(fileno(stdout),
                            "FAILURE: 0x%08lx != 0x%08lx at physical address "
                            "0x%08lx.\n",
                            (ul) *p1, (ul) *p2, physaddr);
                } else {
                    fprintf(fileno(stdout),
                            "Compare times: %d.\n",
                            (j+1));
                    fprintf(fileno(stdout),
                            "FAILURE: 0x%08lx != 0x%08lx at offset 0x%08lx.\n",
                            (ul) *p1, (ul) *p2, (ul) (i * sizeof(ul)));
                }

                readRepeat(p1, p2, bufa, bufb, count, 20);

                /* printf("Skipping to next test..."); */
                if (compare_20_times == 0){
                    r = -1;
                }else {
                    r = 0; /* complete the last comparison.*/
                }
#           endif
            }
        }

        if (compare_20_times == 0){
            j = 20; /* do not need compare 20 times; */
        }
    }
    return r;
}

void readRepeat_tag(ulv *p1, ulv *p2, ulv *bufa, ulv *bufb, size_t count, int n_repeat)
{
	int i = 0;
	char *pchar = NULL;

	for(i = 0; i < n_repeat; i++)
	{
		pchar = (*p1 == *p2)?"=":"!";
		fprintf(fileno(stdout),
			"ReadRepeat(%d): 0x%08lx %s= 0x%08lx \n",
			i, (ul) *p1, pchar, (ul) *p2);
	}
}

int compare_regions_const(ulv *bufa, size_t count, int value)
{
	ulv *p1 = bufa;
	size_t i;
	int res = 0;
	for (i = 0; i < count; i++, p1++)
	{
		if (*p1 != value)
		{
			res = -1;
		}
	}

	return res;
}

void ddr_mem_test(ulong dram_base, ulong dram_size, size_t test_len)
{
	ul regval;
	ul length;
	ulv *p;
	void volatile *buf = NULL;
	ul reboot_times;
	ul memblock;
	size_t halflen;
	size_t count;

	if (dram_size < 0x20000000)
	{
		buf = malloc(test_len);
		if (!buf)
		{
			fprintf("failed to alloc memtest space\n");
			while(1);
		}

	}
	/*****************************************************
	 * set reboot flag
	 */
	p = CONFIG_SYS_SDRAM_BASE;
	regval = *p;
	if(regval == 0xF9999999)
	{
		p++;
		reboot_times = *p;
		reboot_times++;
		*p = reboot_times;
	}
	else
	{
		*p = 0xF9999999;
		p++;
		*p = 1;
		reboot_times = 1;
	}

	if (dram_size < 0x20000000)
	{
		halflen = test_len / 2;
		sr_addr = (ulv *) buf;
		dst_addr = (ulv *) ((size_t)buf + halflen);
		count = halflen / sizeof(ul);

	} else {
		memblock = dram_size /(test_len * 2);
		regval = (reboot_times - 1) % memblock;
		sr_addr = (ulv *) (dram_base + regval * test_len);
		dst_addr = (ulv *) ((dram_base + (dram_size / 2)) + regval * test_len);
		count = test_len / sizeof(ul);
	}

	fprintf("dram_base 0x%08lx, dram_size 0x%08lx, test time %d,source address 0x%08lx,dest address 0x%08lx,test length 0x%08lx\n",
		dram_base,dram_size,reboot_times,sr_addr,dst_addr,test_len);

	length = sizeof(tests)/sizeof(struct memtest);
	for (regval=0; regval < length; regval++)
	{
		fprintf("%s test\n",tests[regval].name);
		if (!tests[regval].fp(dst_addr, sr_addr, count))
		{
			fprintf("%s test pass\n",tests[regval].name);
		}
		else
		{
			fprintf("%s test failed\n",tests[regval].name);
			while(1);
		}
	}

	if (dram_size < 0x20000000)
		free(buf);
}


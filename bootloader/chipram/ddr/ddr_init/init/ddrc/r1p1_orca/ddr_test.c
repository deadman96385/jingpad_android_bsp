#include <sci_types.h>
#include <asm/arch/clk_para_config.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>
#include "ddr_test.h"
#define MEM_DEBUG
#define SOURCE_ADDR 0x80000000
#define DST_ADDR    0x81000000
#define MEM_TEST_LEN 0x100000
#ifdef MEM_DEBUG

char progress[] = "-\\|/";
#define PROGRESSLEN 4
#define PROGRESSOFTEN 2500
#define ONE 0x00000001L

static int compare_20_times = 0;

struct memtest {
    char *name;
    int (*fp)();
};

struct memtest tests[] = {
    { "Random Value", test_random_value },
    { "Compare XOR", test_xor_comparison },
    { "Compare SUB", test_sub_comparison },
    { "Compare MUL", test_mul_comparison },
    { "Compare DIV",test_div_comparison },
    { "Compare OR", test_or_comparison },
    { "Compare AND", test_and_comparison },
    { NULL, NULL }
};

static uint32 seed = 0x2345abcd;

uint32 rand_u32()
{
    uint32 d;

	d=((seed >> 3)^seed)&0x1ffffffe;
	seed=(seed>>29)|d<<2;
	d=((seed>>3)^seed)&0xf;
	seed>>=3;
	seed|=d<<28;

	return seed;
}

static char  log_string[32];
static char *  toStrDec(u32 val)
{
	int i, j, num;
	u32 temp = val;

	num = 0;
	do
	{
		num++;
		temp /= 10;
	}while(temp >0);

	for (i = num-1; i >=0; i--)
	{
		temp = (val%10) + 0x30; val /= 10;
		log_string[i] = temp&0xff;
	}
	log_string[num] = ' ';
	log_string[num+1] = 0;
	return log_string;
}

static char *  toStrHex(u32 val)
{
	int i, j, num;
	u32 temp = val;

	log_string[0] = '0';
	log_string[1] = 'x';
	for (i = 0; i < 8; i++)
	{
		temp = (val >> ((7-i)*4)) & 0xf;
		if (temp < 0xa)
			log_string[2+i] = temp+0x30;
		else
			log_string[2+i] = 'A'+temp-0xa;
	}
	log_string[10] = ' ';
	log_string[11] = 0;
	return log_string;
}

static int  print_Dec(s32 val)
{
	if(val <0)
	{
		ddrc_print_str("-");
		val = 0 - val;
	}
	ddrc_print_str(toStrDec(val));
	return 0;
}

static int  print_Hex(u32 val)
{
	ddrc_print_str(toStrHex(val));
	return 0;
}
static int print_String(const char *string)
{
	ddrc_print_str(string);
	return 0;
}

void readRepeat(u32 *p1, u32 *p2, u32 *bufa, u32 *bufb, u32 count, int n_repeat) {
	int i = 0;
	int resu32t=0;

	for(i = 0; i < n_repeat; i++) {
		resu32t = (*p1 == *p2)? 0: -1;
		if (resu32t)
		{
			compare_20_times ++;
		//	print_String("ReadRepeat addr:");
		//	print_Hex((u32)*p1);
		//	print_String("!=");
		//	print_String("addr:");
		//	print_Hex((u32)*p2);
		//	print_String("\n");
		}
	}
}

int compare_regions(u32 *bufa, u32 *bufb, u32 count) {
    int r = 0;
    u32 i,j;
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    off_t physaddr;

    for (j = 0; j < 20; j++)
    {
        p1 = bufa;
        p2 = bufb;

        for (i = 0; i < count; i++, p1++, p2++)
	{
            if (*p1 != *p2)
	    {
                readRepeat(p1, p2, bufa, bufb, count, 10);

                /* printf("Skipping to next test..."); */
                if (compare_20_times == 10)
		{
                    //r = -1;
		    print_String("ddr compare failed\n");
		    while(1);
                }
		else
		{
                    r = 0; /* complete the last comparison.*/
                }
            }
        }

    }
    return r;
}

int test_stuck_address(u32 *bufa, u32 count)
{
    u32 *p1 = bufa;
    unsigned int j;
    u32  i;

    for (j = 0; j < 1; j++) {
        p1 = (u32*) bufa;
        for (i = 0; i < count; i++) {
            *p1 = ((j + i) % 2) == 0 ? (u32) p1 : ~((u32) p1);
            p1++;
        }
        p1 = (u32*) bufa;
        for (i = 0; i < count; i++, p1++) {
            if (*p1 != (((j + i) % 2) == 0 ? (u32) p1 : ~((u32) p1))) {
                    print_String("FAILURE: possible bad address line at physical address 0x:");
		    print_Hex((u32*)p1);
		    print_String("\n");
                while(1);
            }
        }
    }
    //print_String("Stuck address test pass\n");
    return 0;
}

int test_random_value(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    u32 j = 0;
    u32 i;

    for (i = 0; i < count; i++) {
        *p1++ = *p2++ = rand_u32();
    }
    return compare_regions(bufa, bufb, count);
}

int test_xor_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    u32 i;
    u32 q = rand_u32();

    for (i = 0; i < count; i++) {
        *p1++ ^= q;
        *p2++ ^= q;
    }
    return compare_regions(bufa, bufb, count);
}

int test_sub_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    u32 i;
    u32 q = rand_u32();

    for (i = 0; i < count; i++) {
        *p1++ -= q;
        *p2++ -= q;
    }
    return compare_regions(bufa, bufb, count);
}

int test_mul_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    u32 i;
    u32 q = rand_u32();

    for (i = 0; i < count; i++) {
        *p1++ *= q;
        *p2++ *= q;
    }
    return compare_regions(bufa, bufb, count);
}

int test_div_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    u32 i;
    u32 q = rand_u32();

    for (i = 0; i < count; i++) {
        if (!q) {
            q++;
        }
        *p1++ /= q;
        *p2++ /= q;
    }
    return compare_regions(bufa, bufb, count);
}

int test_or_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    u32 i;
    u32 q = rand_u32();

    for (i = 0; i < count; i++) {
        *p1++ |= q;
        *p2++ |= q;
    }
    return compare_regions(bufa, bufb, count);
}

int test_and_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    u32 i;
    u32 q = rand_u32();

    for (i = 0; i < count; i++) {
        *p1++ &= q;
        *p2++ &= q;
    }
    return compare_regions(bufa, bufb, count);
}

int test_seqinc_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    u32 i;
    u32 q = rand_u32();

    for (i = 0; i < count; i++) {
        *p1++ = *p2++ = (i + q);
    }
    return compare_regions(bufa, bufb, count);
}

int test_solidbits_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    unsigned int j;
    u32 q;
    u32 i;

    for (j = 0; j < 64; j++) {
        q = (j % 2) == 0 ? UL_ONEBITS : 0;
        p1 = (u32 *) bufa;
        p2 = (u32 *) bufb;
        for (i = 0; i < count; i++) {
            *p1++ = *p2++ = (i % 2) == 0 ? q : ~q;
        }
        if (compare_regions(bufa, bufb, count)) {
            return -1;
        }
    }
    return 0;
}

int test_checkerboard_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    unsigned int j;
    u32 q;
    u32 i;

    for (j = 0; j < 64; j++) {
        q = (j % 2) == 0 ? CHECKERBOARD1 : CHECKERBOARD2;
        p1 = (u32 *) bufa;
        p2 = (u32 *) bufb;
        for (i = 0; i < count; i++) {
            *p1++ = *p2++ = (i % 2) == 0 ? q : ~q;
        }
        if (compare_regions(bufa, bufb, count)) {
            return -1;
        }
    }
    return 0;
}

int test_blockseq_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    unsigned int j;
    u32 i;

    for (j = 0; j < 256; j++) {
        p1 = (u32 *) bufa;
        p2 = (u32 *) bufb;
        for (i = 0; i < count; i++) {
            *p1++ = *p2++ = (u32) UL_BYTE(j);
        }
        if (compare_regions(bufa, bufb, count)) {
            return -1;
        }
    }
    return 0;
}

int test_walkbits0_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    unsigned int j;
    u32 i;

    //printf("           ");
    for (j = 0; j < UL_LEN * 2; j++) {
        //printf("\b\b\b\b\b\b\b\b\b\b\b");
        p1 = (u32 *) bufa;
        p2 = (u32 *) bufb;
        //printf("setting %3u", j);
        for (i = 0; i < count; i++) {
            if (j < UL_LEN) { /* Walk it up. */
                *p1++ = *p2++ = ONE << j;
            } else { /* Walk it back down. */
                *p1++ = *p2++ = ONE << (UL_LEN * 2 - j - 1);
            }
        }
        //printf("\b\b\b\b\b\b\b\b\b\b\b");
        //printf("testing %3u", j);
        if (compare_regions(bufa, bufb, count)) {
            return -1;
        }
    }
    //printf("\b\b\b\b\b\b\b\b\b\b\b           \b\b\b\b\b\b\b\b\b\b\b");
    return 0;
}

int test_walkbits1_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    unsigned int j;
    u32 i;

    //printf("           ");
    for (j = 0; j < UL_LEN * 2; j++) {
        //printf("\b\b\b\b\b\b\b\b\b\b\b");
        p1 = (u32 *) bufa;
        p2 = (u32 *) bufb;
        //printf("setting %3u", j);
        for (i = 0; i < count; i++) {
            if (j < UL_LEN) { /* Walk it up. */
                *p1++ = *p2++ = UL_ONEBITS ^ (ONE << j);
            } else { /* Walk it back down. */
                *p1++ = *p2++ = UL_ONEBITS ^ (ONE << (UL_LEN * 2 - j - 1));
            }
        }
        //printf("\b\b\b\b\b\b\b\b\b\b\b");
        //printf("testing %3u", j);
        if (compare_regions(bufa, bufb, count)) {
            return -1;
        }
    }
    //printf("\b\b\b\b\b\b\b\b\b\b\b           \b\b\b\b\b\b\b\b\b\b\b");
    return 0;
}

int test_bitspread_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    unsigned int j;
    u32 i;

    //printf("           ");
    for (j = 0; j < UL_LEN * 2; j++) {
        //printf("\b\b\b\b\b\b\b\b\b\b\b");
        p1 = (u32 *) bufa;
        p2 = (u32 *) bufb;
        //printf("setting %3u", j);
        for (i = 0; i < count; i++) {
            if (j < UL_LEN) { /* Walk it up. */
                *p1++ = *p2++ = (i % 2 == 0)
                    ? (ONE << j) | (ONE << (j + 2))
                    : UL_ONEBITS ^ ((ONE << j)
                                    | (ONE << (j + 2)));
            } else { /* Walk it back down. */
                *p1++ = *p2++ = (i % 2 == 0)
                    ? (ONE << (UL_LEN * 2 - 1 - j)) | (ONE << (UL_LEN * 2 + 1 - j))
                    : UL_ONEBITS ^ (ONE << (UL_LEN * 2 - 1 - j)
                                    | (ONE << (UL_LEN * 2 + 1 - j)));
            }
        }
        //printf("\b\b\b\b\b\b\b\b\b\b\b");
        //printf("testing %3u", j);
        if (compare_regions(bufa, bufb, count)) {
            return -1;
        }
    }
    //printf("\b\b\b\b\b\b\b\b\b\b\b           \b\b\b\b\b\b\b\b\b\b\b");
    return 0;
}

int test_bitflip_comparison(u32 *bufa, u32 *bufb, u32 count) {
    u32 *p1 = bufa;
    u32 *p2 = bufb;
    unsigned int j, k;
    u32 q;
    u32 i;

    //printf("           ");
    for (k = 0; k < UL_LEN; k++) {
        q = ONE << k;
        for (j = 0; j < 8; j++) {
            //printf("\b\b\b\b\b\b\b\b\b\b\b");
            q = ~q;
            //printf("setting %3u", k * 8 + j);
            p1 = (u32 *) bufa;
            p2 = (u32 *) bufb;
            for (i = 0; i < count; i++) {
                *p1++ = *p2++ = (i % 2) == 0 ? q : ~q;
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
#if 0
//void switch_for_tiger(u32 *p){
//    char *r0;
//    char *r1;
//    char new_r0[4],new_r1[4];
//    u32 *p_r = p;
//    int i;
//#define copy_byte(__x,__y) do{\
//    __y = __x;}while(0)
//
///*Change method:
//SW_original:
//Word data:  0x77665544
//Address 0x4:    7   6   5   4
//Byte data:  0x77    0x66    0x55    0x44
//
//Word data:  0x33221100
//Address 0x0:    3   2   1   0
//Byte data:  0x33    0x22    0x11    0x00
//
//    |
//    |
//    V
//
//SW_Swap:
//Word data:  0x33772266
//Address 0x4:    7   6   5   4
//Byte data:  0x33    0x77    0x22    0x66
//
//Word data:  0x11550044
//Addrees 0x0:    3   2   1   0
//Byte data:  0x11    0x55    0x00    0x44
//
//r0_0 -> new_r0_1
//r0_1 -> new_r0_3
//r0_2 -> new_r1_1
//r0_3 -> new_r1_3
//r1_0 -> new_r0_0
//r1_1 -> new_r0_2
//r1_2 -> new_r1_0
//r1_3 -> new_r1_2*/
//
//    /*switch p,p-1*/
//    r1 = (char *)(p_r--);
//    r0 = (char *)p_r;
///*    printf("r1=0x%08lx,*r1=0x%08lx\n",r1,*(u32*)r1);
//    printf("r0=0x%08lx,*r0=0x%08lx\n",r0,*(u32*)r0);*/
//    copy_byte(r0[0],new_r0[1]);
//    copy_byte(r0[1],new_r0[3]);
//    copy_byte(r0[2],new_r1[1]);
//    copy_byte(r0[3],new_r1[3]);
//    copy_byte(r1[0],new_r0[0]);
//    copy_byte(r1[1],new_r0[2]);
//    copy_byte(r1[2],new_r1[0]);
//    copy_byte(r1[3],new_r1[2]);
//    for(i = 0; i < 4; i++){
//        r0[i] = new_r0[i]; /*write back*/
//        r1[i] = new_r1[i];
//    }
///*    printf("r1=0x%08lx,*r1=0x%08lx\n",r1,*(u32*)r1);
//    printf("r0=0x%08lx,*r0=0x%08lx\n",r0,*(u32*)r0);*/
//}
//
//int test_bitflip_comparison_tiger(u32 *bufa, u32 *bufb, u32 count) {
//    u32 *p1 = bufa;
//    u32 *p2 = bufb;
//    /*u32 *temp;*/
//    unsigned int j, k;
//    u32 q;
//    u32 i;
//    //printf("           ");
//    fflush(stdout);
//
//    if (sizeof(u32) != 4){
//        printf("This test only support for 32bit Architecture");
//        return -1;
//    }
//
//    for (k = 0; k < UL_LEN; k++) {
//        q = ONE << k;
//        for (j = 0; j < 8; j++) {
//            //printf("\b\b\b\b\b\b\b\b\b\b\b");
//            q = ~q;
//            //printf("setting %3u", k * 8 + j);
//            fflush(stdout);
//            p1 = (u32 *) bufa;
//            p2 = (u32 *) bufb;
//            for (i = 0; i < count; i++) {
//                *p1++ = *p2++ = (i % 2) == 0 ? q : ~q;
//                if ((i > 0) && ((i % 2) == 1)){  /*switch for tiger*/
//                   /* *temp = 0x33221100;
//                    *p1 = 0x77665544;
//                    //printf("\nbefore switch: 0x%8X 0x%8X\n",*(u32 *)temp,*(u32 *)p1);
//                    //printf("\nbefore switch p1 i=%d : 0x%08lX 0x%08lX\n",i,*(u32 *)(p1-1),*(u32 *)p1);
//                    //printf("\nbefore switch p2 i=%d : 0x%08lX 0x%08lX\n",i,*(u32 *)(p2-1),*(u32 *)p2);*/
//                    switch_for_tiger(p1-1);
//                    switch_for_tiger(p2-1);
//                /*    printf("\nafter switch p1 i=%d : 0x%08lX 0x%08lX\n",i,*(u32 *)(p1-1),*(u32 *)p1);
//                    printf("\nafter switch p2 i=%d : 0x%08lX 0x%08lX\n",i,*(u32 *)(p2-1),*(u32 *)p2);
//                }else{
//                    temp = p1;*/
//                }
//            }
//            //printf("\b\b\b\b\b\b\b\b\b\b\b");
//            //printf("testing %3u", k * 8 + j);
//            fflush(stdout);
//            if (compare_regions(bufa, bufb, count)) {
//                return -1;
//            }
//        }
//    }
//    //printf("\b\b\b\b\b\b\b\b\b\b\b           \b\b\b\b\b\b\b\b\b\b\b");
//    fflush(stdout);
//    return 0;
//}
//
//#ifdef TEST_NARROW_WRITES
//int test_8bit_wide_random(u32* bufa, u32* bufb, u32 count) {
//    u8v *p1, *t;
//    u32 *p2;
//    int attempt;
//    unsigned int b, j = 0;
//    u32 i;
//
//    putchar(' ');
//    fflush(stdout);
//    for (attempt = 0; attempt < 2;  attempt++) {
//        if (attempt & 1) {
//            p1 = (u8v *) bufa;
//            p2 = bufb;
//        } else {
//            p1 = (u8v *) bufb;
//            p2 = bufa;
//        }
//        for (i = 0; i < count; i++) {
//            t = mword8.bytes;
//            *p2++ = mword8.val = rand_u32();
//            for (b=0; b < UL_LEN/8; b++) {
//                *p1++ = *t++;
//            }
//            if (!(i % PROGRESSOFTEN)) {
//               // putchar('\b');
//                //putchar(progress[++j % PROGRESSLEN]);
//                fflush(stdout);
//            }
//        }
//        if (compare_regions(bufa, bufb, count)) {
//            return -1;
//        }
//    }
//    //printf("\b \b");
//    fflush(stdout);
//    return 0;
//}
//
//int test_16bit_wide_random(u32* bufa, u32* bufb, u32 count) {
//    u16v *p1, *t;
//    u32 *p2;
//    int attempt;
//    unsigned int b, j = 0;
//    u32 i;
//
//    putchar( ' ' );
//    fflush( stdout );
//    for (attempt = 0; attempt < 2; attempt++) {
//        if (attempt & 1) {
//            p1 = (u16v *) bufa;
//            p2 = bufb;
//        } else {
//            p1 = (u16v *) bufb;
//            p2 = bufa;
//        }
//        for (i = 0; i < count; i++) {
//            t = mword16.u16s;
//            *p2++ = mword16.val = rand_u32();
//            for (b = 0; b < UL_LEN/16; b++) {
//                *p1++ = *t++;
//            }
//            if (!(i % PROGRESSOFTEN)) {
//                //putchar('\b');
//                //putchar(progress[++j % PROGRESSLEN]);
//                fflush(stdout);
//            }
//        }
//        if (compare_regions(bufa, bufb, count)) {
//            return -1;
//        }
//    }
//    //printf("\b \b");
//    fflush(stdout);
//    return 0;
//}
//#endif
//
//extern int volatile bfinished;
//extern int mode;
//extern pthread_mutex_t mutex;
//int compare_regions_tag(u32 *bufa, u32 *bufb, u32 count) {
//    int r = 0;
//    u32 i,j;
//    u32 *p1 = bufa;
//    u32 *p2 = bufb;
//    off_t physaddr;
//
//    for (j = 0; j < 20; j++)
//    {
//        p1 = bufa;
//        p2 = bufb;
//
//        for (i = 0; i < count; i++, p1++, p2++) {
//            if (*p1 != *p2) {
//#undef DEBUG_COMPARE
//#           ifdef DEBUG_COMPARE
//                printfTag("0x%08x: 0x%08lx  |  0x%08lx\n",i,*p1,*p2);
//                fflush(stdout);
//#           else
//                if (use_phys) {
//                    physaddr = physaddrbase + (i * sizeof(u32));
//                    fprintf(fileno(stdout),
//                            "Compare times: %d.\n",
//                            (j+1));
//                    fprintf(fileno(stdout),
//                            "FAILURE: 0x%08lx != 0x%08lx at physical address "
//                            "0x%08lx.\n",
//                            (u32) *p1, (u32) *p2, physaddr);
//                } else {
//                    fprintf(fileno(stdout),
//                            "Compare times: %d.\n",
//                            (j+1));
//                    fprintf(fileno(stdout),
//                            "FAILURE: 0x%08lx != 0x%08lx at offset 0x%08lx.\n",
//                            (u32) *p1, (u32) *p2, (u32) (i * sizeof(u32)));
//                }
//
//                readRepeat(p1, p2, bufa, bufb, count, 20);
//
//                /* printf("Skipping to next test..."); */
//                if (compare_20_times == 0){
//                    r = -1;
//                }else {
//                    r = 0; /* complete the last comparison.*/
//                }
//#           endif
//            }
//        }
//
//        if (compare_20_times == 0){
//            j = 20; /* do not need compare 20 times; */
//        }
//    }
//    return r;
//}
//
//void readRepeat_tag(u32 *p1, u32 *p2, u32 *bufa, u32 *bufb, u32 count, int n_repeat) {
//	int i = 0;
//	char *pchar = NULL;
//
//	for(i = 0; i < n_repeat; i++) {
//		cacheflush((long)bufa, (long)bufa+count, 0);
//		cacheflush((long)bufb, (long)bufb+count, 0);
//		pchar = (*p1 == *p2)?"=":"!";
//        fprintf(fileno(stdout),
//                "ReadRepeat(%d): 0x%08lx %s= 0x%08lx \n",
//                i, (u32) *p1, pchar, (u32) *p2);
//	}
//}
//
//int compare_regions_const(u32 *bufa, u32 count, int value) {
//	u32 *p1 = bufa;
//	u32 i;
//	int res = 0;
//	for(i = 0; i < count; i++, p1++) {
//		if(*p1 != value) {
//			printfTag(TAG_REFRESH, "FAILURE: 0x%08lx != 0x%08lx at offset 0x%08lx.\n",
//						(u32) *p1, value, (u32) (i * sizeof(u32)));
//			res = -1;
//		}
//	}
//
//	return res;
//}
//
//int test_bitRefresh_comparison(lprefresh_t lprefresh) {
//    u32 *bufConst = lprefresh->bufa;
//    u32 *bufRandom = lprefresh->bufb;
//    u32 const_count = lprefresh->count/2;
//    u32 random_count = lprefresh->count/2;
//    u32 *p1 = bufConst;
//    u32 *p2 = bufConst+const_count;
//    u32 *p3 = bufRandom;
//    u32 *p4 = bufRandom+random_count;
//    u32 i;
//    u32 loop = 0;
//    int resu32t = 0;
//
//    for(i = 0; i < const_count; i++) {
//    	*p1++ = 0;
//    	*p2++ = 1;
//    }
//
//    for(i = 0; i < random_count; i++) {
//    	*p3++ = *p4++ = rand_u32();
//    }
//
//    do {
//    	pthread_mutex_lock(&mutex);
//
//        printfTag(TAG_REFRESH, "loop %lu :\n", loop++);
//        printfTag(TAG_REFRESH, "\n");
//        printfTag(TAG_REFRESH, "  %-20s: \n", "refresh");
//
//    	p1 = bufConst;
//    	p2 = bufConst+const_count;
//        p3 = bufRandom;
//        p4 = bufRandom+random_count;
//    	resu32t = compare_regions_const(p1, const_count, 0);
//    	resu32t |= compare_regions_const(p2, const_count, 1);
//    	resu32t |= compare_regions_tag(p3, p4, random_count);
//    	if (!resu32t) {
//    		printfTag(TAG_REFRESH, "  %-20s: ok\n", " ");
//    	}
//
//    	pthread_mutex_unlock(&mutex);
//
//    	sleep(lprefresh->time);
//    }while(!bfinished);
//
//    return 0;
//}
#endif

void ddr_memtester(void)
{
	u32 regval;
	//test_stuck_address((u32*)DST_ADDR, MEM_TEST_LEN);

	for (regval=0; ; regval++)
	{
		if (!tests[regval].name) break;
		if (!tests[regval].fp((u32 *)DST_ADDR, (u32 *)SOURCE_ADDR, MEM_TEST_LEN))
		{
			switch (regval)
			{
				case 0:
					print_String("Random Value ");
					break;
				case 1:
					print_String("Compare XOR ");
					break;
				case 2:
					print_String("Compare SUB ");
					break;
				case 3:
					print_String("Compare MUL ");
					break;
				case 4:
					print_String("Compare DIV ");
					break;
				case 5:
					print_String("Compare OR  ");
					break;
				case 6:
					print_String("Compare AND ");
					break;
			}
			print_String(" test pass\n");
		}
		else
		{
			switch (regval)
			{
				case 0:
					print_String("Random Value ");
					break;
				case 1:
					print_String("Compare XOR ");
					break;
				case 2:
					print_String("Compare SUB ");
					break;
				case 3:
					print_String("Compare MUL ");
					break;
				case 4:
					print_String("Compare DIV ");
					break;
				case 5:
					print_String("Compare OR  ");
					break;
				case 6:
					print_String("Compare AND ");
					break;
			}
			print_String(" test failed\n");
			while(1);
		}
	}

}

void ddr_mem_test(void)
{
	int i;
	unsigned int regval;

	for (i = 0; i < MEM_TEST_LEN; i+=4)
	{
		REG32(SOURCE_ADDR + i) = SOURCE_ADDR + i;
		REG32(DST_ADDR + i) = SOURCE_ADDR + i;
	}

	//while(1)
	{
		memset((void*)DST_ADDR, 0x0, MEM_TEST_LEN);
		for ( i = 0; i < MEM_TEST_LEN; i+= 1024)
		{
			sprd_memcpy((void*)(DST_ADDR + i), (void*)(SOURCE_ADDR + i), 1024);
			regval = sprd_memcmp((void*)(SOURCE_ADDR + i), (void*)(DST_ADDR + i),1024);
			if (regval)
			{
				ddrc_print_str("little ddr copy failed\n");
				while(1);
			}
			else
			{
				//ddrc_print_str("ddr copy pass\n");
			}
		}

		regval = sprd_memcmp((void*)(SOURCE_ADDR), (void*)(DST_ADDR),MEM_TEST_LEN);
		if (regval)
		{
			ddrc_print_str("big ddr cmp failed\n");
			while(1);
		}
		else
		{
			//ddrc_print_str("big mem cmp pass\n");
		}
	}
}
#else
void ddr_mem_test(void)
{
	;
}
#endif

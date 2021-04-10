/* ＤＤＲ　ＰＯＷＥＲ　ＴＥＳＴ */

/**************************************
 ;case                  nr      state
 ;
 ;CASE_BIST_READ        0       [done]
 ;CASE_BIST_WRITE,      1       [done]
 ;CASE_BIST_SIPI,       2       [x]
 ;CASE_POWER_DOWN1,     3       [done]
 ;CASE_POWER_DOWN2,     4       [done]
 ;CASE_POWER_DOWN3,     5       [done]
 ;CASE_POWER_DOWN4,     6       [done]=SR
 ;CASE_SELF_REFRESH,    7       [x]
 ;CASE_LIGHT_RETENTION, 8       [done]
 ;CASE_LIGHT,           9       [done]
 ;CASE_PUB_POWER_DOWN,  0xa     [x]
 ;CASE_CHANNEL_POWER,   0xb     [x]
 ;CASE_DEEP_SLEEP,      0xc     [done]
 ;CASE_IDLE,            0xd     [done]
 ;CASE_LIGHT_AUTO       0xe     [done]=smart light
 ;CASE_RPULL            0xf     [done]
 ;CASE_BYPASS_DESKEW,   0x10    [done]
 ;CASE_POWER_DOWN5,     0x11    [done]
 ;CASE_POWER_DOWN6,     0x12    [done]
 ;CASE_POWER_DOWN7,     0x13    [done]
 ;**************************************

 ;DFS freq
 ;
 ;0 - 233MHz
 ;1 - 364MHz
 ;2 - 622MHz
 ;3 - 933MHz
 ;**************************************
*/

#include "../../init/v0_2/ddr_init.h"
#include "../../timing/v0_2/ddr_timing.h"
#include "../../qos/v0_2/ddr_qos.h"

#ifdef POWER_TEST
//#define BUILD_TEST_BIN
/* you have trigger/command/frequency from this address */

#define PWRTEST_ARUGMENTS_ADDR (0xe6019200)
#define PWRTEST_TRIGGER (0x66bb)

enum pwrtest_case_t {
    CASE_BIST_READ = 0,
    CASE_BIST_WRITE,
    CASE_BIST_SIPI,
    CASE_POWER_DOWN1,
    CASE_POWER_DOWN2,
    CASE_POWER_DOWN3 = 5,
    CASE_POWER_DOWN4,
    CASE_SELF_REFRESH,
    CASE_LIGHT_WITH_RETENTION,
    CASE_LIGHT,
    CASE_PUB_POWER_DOWN = 0xA,
    CASE_CHANNEL_POWER,
    CASE_DEEP_SLEEP,
    CASE_IDLE,
    CASE_LIGHT_AUTO =0xE, /*it's so-called smart light*/
    CASE_RPULL =0xf,
    CASE_BYPASS_DESKEW =0x10,
    CASE_POWER_DOWN5,
    CASE_POWER_DOWN6,
    CASE_POWER_DOWN7,
    PWRTEST_CASE_NR
};

#ifndef BUILD_TEST_BIN
/* index freq/testcase in your trace script */
static enum pwrtest_case_t ddr_wait_pwrtest_cmd()
{
    volatile uint32* p = PWRTEST_ARUGMENTS_ADDR;
    while(*p != PWRTEST_TRIGGER)
	wait_us(1000);

    /* switch ddr freq if reqired to */
    if (*(p+1)>=0 && *(p+1)<=3) {
        __ddr_print("do dfs switch\n");
        dfs_go(0, *(p+1));
    } else {
        __ddr_print("no dfs\n");
    }

    return (*(p+2) < PWRTEST_CASE_NR) ?
        *(p+2) : CASE_IDLE;
}

#else

#define local_dfs_freq (2)
#define local_case_nr (CASE_DEEP_SLEEP)
static enum pwrtest_case_t ddr_wait_pwrtest_cmd()
{
    dfs_go(0, local_dfs_freq);
    wait_us(1000); /*1s in real*/
    return local_case_nr;
}
#endif

static void testcase_power_down5(int subcase)
{
    uint32 v1,v2;
    uint32 chn_offset = 0;

    switch(subcase) {
    case 1:
        v1=0x1000007; v2=0xff0001;
        break;
    case 2:
        v1=0x1000007; v2=0xff0101;
        break;
    case 3:
        v1=0x2000007; v2=0xff0207;
        break;
    case 4:
        v1=0x4000007; v2=0xff0207;
        break;
    }

    /*
    *(volatile uint32*)0xc0000264 = v1;
    *(volatile uint32*)0xc0000268 = v2;
    *(volatile uint32*)0xc000025c = 0x1f040f;
    *(volatile uint32*)0xc000026c = 0x4040000;
    *(volatile uint32*)0xc00030bc = 0x3010303;
    *(volatile uint32*)0xc00003b8 = 0x1815121f;
    */

    *(volatile uint32*)0xc0000234 = 0x4020000;
    *(volatile uint32*)0xc000023c = 0x4020000;
    *(volatile uint32*)0xc0000244 = 0x4020000;
    *(volatile uint32*)0xc000024c = 0x4020000;
    *(volatile uint32*)0xc0000254 = 0x4020000;

    *(volatile uint32*)0xc0000238 = 0x8080808;
    *(volatile uint32*)0xc0000240 = 0x8080808;
    *(volatile uint32*)0xc0000248 = 0x8080808;
    *(volatile uint32*)0xc0000250 = 0x8080808;
    *(volatile uint32*)0xc0000258 = 0x8080808;

    *(volatile uint32*)0xc0000264 = v1;
    *(volatile uint32*)0xc0000268 = v2;
    *(volatile uint32*)0xc000025c = 0x1f040f;
    *(volatile uint32*)0xc000026c = 0x4040000;
    *(volatile uint32*)0xc00030bc = 0x7010303;
    *(volatile uint32*)0xc00003b8 = 0x1815121f;

    *(volatile uint32*)0xe42c008c = 0x7f;
    *(volatile uint32*)0xc0014030 = 0x103f;
    *(volatile uint32*)0xc0014034 = 0x103f;
    *(volatile uint32*)0xc0014038 = 0x103f;
    *(volatile uint32*)0xc001403c = 0x103f;
    *(volatile uint32*)0xc0014040 = 0x103f;
    *(volatile uint32*)0xc0014044 = 0x103f;
    *(volatile uint32*)0xc0010004 = 0x18000000;
}

static void testcase_power_down6(int subcase)
{
    uint32 v1,v2;
    uint32 chn_offset = 0;

    switch(subcase) {
    case 1:
        v1=0x1000007; v2=0xff0001;
        break;
    case 2:
        v1=0x1000007; v2=0xff0101;
        break;
    case 3:
        v1=0x2000007; v2=0xff0207;
        break;
    case 4:
        v1=0x4000007; v2=0xff0207;
        break;
    }

    /*
    *(volatile uint32*)0xc0000264 = v1;
    *(volatile uint32*)0xc0000268 = v2;
    *(volatile uint32*)0xc000025c = 0x40f;
    *(volatile uint32*)0xc000026c = 0x4040000;
    *(volatile uint32*)0xc00030bc = 0x3010303;
    *(volatile uint32*)0xc00003b8 = 0x1815121f;
    */

    *(volatile uint32*)0xc0000234 = 0x4020000;
    *(volatile uint32*)0xc000023c = 0x4020000;
    *(volatile uint32*)0xc0000244 = 0x4020000;
    *(volatile uint32*)0xc000024c = 0x4020000;
    *(volatile uint32*)0xc0000254 = 0x4020000;

    *(volatile uint32*)0xc0000238 = 0x4040404;
    *(volatile uint32*)0xc0000240 = 0x4040404;
    *(volatile uint32*)0xc0000248 = 0x4040404;
    *(volatile uint32*)0xc0000250 = 0x4040404;
    *(volatile uint32*)0xc0000258 = 0x4040404;

    *(volatile uint32*)0xc0000264 = v1;
    *(volatile uint32*)0xc0000268 = v2;
    *(volatile uint32*)0xc000025c = 0x40f;
    *(volatile uint32*)0xc000026c = 0x4040000;
    *(volatile uint32*)0xc00030bc = 0x3010303;
    *(volatile uint32*)0xc00003b8 = 0x1815121f;

    *(volatile uint32*)0xe42c008c = 0x7f;
    *(volatile uint32*)0xc0014030 = 0x103f;
    *(volatile uint32*)0xc0014034 = 0x103f;
    *(volatile uint32*)0xc0014038 = 0x103f;
    *(volatile uint32*)0xc001403c = 0x103f;
    *(volatile uint32*)0xc0014040 = 0x103f;
    *(volatile uint32*)0xc0014044 = 0x103f;
    *(volatile uint32*)0xc0010004 = 0x18000000;
}

static void testcase_power_down7(int subcase)
{
    uint32 v1,v2;
    uint32 chn_offset = 0;

    switch(subcase) {
    case 1:
        v1=0x1000007; v2=0xff0001;
        break;
    case 2:
        v1=0x1000007; v2=0xff0101;
        break;
    case 3:
        v1=0x2000007; v2=0xff0207;
        break;
    case 4:
        v1=0x4000007; v2=0xff0207;
        break;
    }

    /*
    *(volatile uint32*)0xc0000264 = v1;
    *(volatile uint32*)0xc0000268 = v2;
    *(volatile uint32*)0xc000025c = 0x1f040f;
    *(volatile uint32*)0xc000026c = 0x4040000;
    *(volatile uint32*)0xc00030bc = 0x5010303;
    *(volatile uint32*)0xc00003b8 = 0x1815121f;
    */

    *(volatile uint32*)0xc0000234 = 0x4020000;
    *(volatile uint32*)0xc000023c = 0x4020000;
    *(volatile uint32*)0xc0000244 = 0x4020000;
    *(volatile uint32*)0xc000024c = 0x4020000;
    *(volatile uint32*)0xc0000254 = 0x4020000;

    *(volatile uint32*)0xc0000238 = 0x4040404;
    *(volatile uint32*)0xc0000240 = 0x4040404;
    *(volatile uint32*)0xc0000248 = 0x4040404;
    *(volatile uint32*)0xc0000250 = 0x4040404;
    *(volatile uint32*)0xc0000258 = 0x4040404;

    *(volatile uint32*)0xc0000264 = v1;
    *(volatile uint32*)0xc0000268 = v2;
    *(volatile uint32*)0xc000025c = 0x1f040f;
    *(volatile uint32*)0xc000026c = 0x4040000;
    *(volatile uint32*)0xc00030bc = 0xA010303;
    *(volatile uint32*)0xc00003b8 = 0x1815121f;

    *(volatile uint32*)0xe42c008c = 0x7f;
    *(volatile uint32*)0xc0014030 = 0x103f;
    *(volatile uint32*)0xc0014034 = 0x103f;
    *(volatile uint32*)0xc0014038 = 0x103f;
    *(volatile uint32*)0xc001403c = 0x103f;
    *(volatile uint32*)0xc0014040 = 0x103f;
    *(volatile uint32*)0xc0014044 = 0x103f;
    *(volatile uint32*)0xc0010004 = 0x18000000;
}

static void testcase_power_down(int subcase)
{
    uint32 v1,v2;
    uint32 chn_offset = 0;

    switch(subcase) {
    case 1:
        v1=0x1000007; v2=0xff0001;
        break;
    case 2:
        v1=0x1000007; v2=0xff0101;
        break;
    case 3:
        v1=0x2000007; v2=0xff0207;
        break;
    case 4:
        v1=0x4000007; v2=0xff0207;
        break;
    }

    /*
    *(volatile uint32*)0xc0000264 = v1;
    *(volatile uint32*)0xc0000268 = v2;
    *(volatile uint32*)0xc000025c = 0x1f040f;
    *(volatile uint32*)0xc000026c = 0x4040000;
    *(volatile uint32*)0xc00030bc = 0x3010303;
    *(volatile uint32*)0xc00003b8 = 0x1815121f;
    */

    *(volatile uint32*)0xc0000234 = 0x4020000;
    *(volatile uint32*)0xc000023c = 0x4020000;
    *(volatile uint32*)0xc0000244 = 0x4020000;
    *(volatile uint32*)0xc000024c = 0x4020000;
    *(volatile uint32*)0xc0000254 = 0x4020000;

    *(volatile uint32*)0xc0000238 = 0x8080808;
    *(volatile uint32*)0xc0000240 = 0x8080808;
    *(volatile uint32*)0xc0000248 = 0x8080808;
    *(volatile uint32*)0xc0000250 = 0x8080808;
    *(volatile uint32*)0xc0000258 = 0x8080808;

    *(volatile uint32*)0xc0000264 = v1;
    *(volatile uint32*)0xc0000268 = v2;
    *(volatile uint32*)0xc000025c = 0x1f040f;
    *(volatile uint32*)0xc000026c = 0x4040000;
    *(volatile uint32*)0xc00030bc = 0x7010303;
    *(volatile uint32*)0xc00003b8 = 0x1815121f;
}

void testcase_smart_light()
{
    int32 ivar;
    /*wakeup*/
    reg_bit_set(0xE42B0134, 12, 1, 0x0);

    /*AON*/
    reg_bit_set(0xE42E3044, 1, 1, 0x1);
    reg_bit_set(0xE42E3044, 3, 1, 0x1);
    reg_bit_set(0xE42E3044, 17, 12, 0xFFF);

    /*idle windows*/
    reg_bit_set(0xC0014030, 0, 1, 0x1);
    reg_bit_set(0xC0014030, 2, 10, 0x1);
    reg_bit_set(0xC0014034, 0, 1, 0x1);
    reg_bit_set(0xC0014034, 2, 10, 0x1);
    reg_bit_set(0xC001403c, 0, 1, 0x1);
    reg_bit_set(0xC001403c, 2, 10, 0x1);

    /*bypass AP_TOP*/
    reg_bit_set(0xE221001C, 0, 11, 0x7FF);
    /*bypass VSP,GPU,BIA*/
    reg_bit_set(0xE42C0070, 0, 4, 0xE);

    /*enable smart light*/
    reg_bit_set(0xE42B012C, 4, 1, 0x1);
    reg_bit_set(0xE42B0204, 0, 1, 0x1);

    while(1) {
        /*start HIGH*/
        ivar = 1000000;
        while(ivar--) {
            *(volatile int32*)(0x4) = 0x55aa;
            *(volatile int32*)(0x8) = 0x0;
            *(volatile int32*)(0xc) = 0x55aa;
            *(volatile int32*)(0x10) = 0x0;
            *(volatile int32*)(0x14) = 0x55aa;
            *(volatile int32*)(0x18) = 0x0;
            *(volatile int32*)(0x1c) = 0x55aa;
            *(volatile int32*)(0x20) = 0x0;
            *(volatile int32*)(0x24) = 0x55aa;
            *(volatile int32*)(0x28) = 0x0;
            *(volatile int32*)(0x2c) = 0x55aa;
            *(volatile int32*)(0x30) = 0x0;
        }

        /*start LOW*/
        wait_us(10000);
    }
}

static void bist_all_bm_read(uint32 chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 bist_base_offset;
	uint32 i;
	uint32 bist_adr_base;
    static uint64 ddr_data_width[100]={0};
	REG32(0xc0018028+chn_offset) =0x2a;

	while(1)
	{
		for(i=0;i<3;i++)
		{
			bist_base_offset = i*0x4000;
			bist_adr_base = (i*0x20000000)+(i*0x100);
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30027a9;
			REG32(0xc00d0004+chn_offset+bist_base_offset) =0x1fFfff;
			REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
			REG32(0xc00d000c+chn_offset+bist_base_offset) =0x0;
			REG32(0xc00d0010+chn_offset+bist_base_offset) =0x0ff0c3a5;
			REG32(0xc00d0014+chn_offset+bist_base_offset) =0xffffaa55;
			REG32(0xc00d0018+chn_offset+bist_base_offset) =0x1111aa55;
			REG32(0xc00d001c+chn_offset+bist_base_offset) =0xaaaaaa55;
			REG32(0xc00d0020+chn_offset+bist_base_offset) =0x1234aa55;
			REG32(0xc00d0024+chn_offset+bist_base_offset) =0x0000aa55;
			REG32(0xc00d0028+chn_offset+bist_base_offset) =0x00000000;
			REG32(0xc00d002c+chn_offset+bist_base_offset) =0x00000000;

			REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
			REG32(0xc00d0004+chn_offset+bist_base_offset) =0x1fFfff;
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30027ad;
		}

		for(i=0;i<3;i++)
		{
			bist_base_offset = i*0x4000;
            REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30027ab;
		}
        i=0;
		while((REG32(0xc00d00b0+chn_offset) & 0x2) != 0x2);
		while((REG32(0xc00d00b0+chn_offset+0x4000) & 0x2) != 0x2);
		while((REG32(0xc00d00b0+chn_offset+0x8000) & 0x2) != 0x2);
	}

	REG32(0xc0018028+chn_offset) =0x0;
}

static void bist_all_bm_write(uint32 chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	uint32 bist_base_offset;
	uint32 i;
	uint32 bist_adr_base;
    static uint64 ddr_data_width[100]={0};
	REG32(0xc0018028+chn_offset) =0x2a;

	while(1)
	{
		for(i=0;i<3;i++)
		{
			bist_base_offset = i*0x4000;
			bist_adr_base = (i*0x20000000)+(i*0x100);
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30027a1;
			REG32(0xc00d0004+chn_offset+bist_base_offset) =0x1fFfff;
			REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
			REG32(0xc00d000c+chn_offset+bist_base_offset) =0x0;
			REG32(0xc00d0010+chn_offset+bist_base_offset) =0x0ff0c3a5;
			REG32(0xc00d0014+chn_offset+bist_base_offset) =0xffffaa55;
			REG32(0xc00d0018+chn_offset+bist_base_offset) =0x1111aa55;
			REG32(0xc00d001c+chn_offset+bist_base_offset) =0xaaaaaa55;
			REG32(0xc00d0020+chn_offset+bist_base_offset) =0x1234aa55;
			REG32(0xc00d0024+chn_offset+bist_base_offset) =0x0000aa55;
			REG32(0xc00d0028+chn_offset+bist_base_offset) =0x00000000;
			REG32(0xc00d002c+chn_offset+bist_base_offset) =0x00000000;

			REG32(0xc00d0008+chn_offset+bist_base_offset) =bist_adr_base;
			REG32(0xc00d0004+chn_offset+bist_base_offset) =0x1fFfff;
			REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30027a5;
		}

		for(i=0;i<3;i++)
		{
			bist_base_offset = i*0x4000;
            REG32(0xc00d0000+chn_offset+bist_base_offset) =0x30027a3;
		}
        i=0;
		while((REG32(0xc00d00b0+chn_offset) & 0x2) != 0x2);
		while((REG32(0xc00d00b0+chn_offset+0x4000) & 0x2) != 0x2);
		while((REG32(0xc00d00b0+chn_offset+0x8000) & 0x2) != 0x2);
	}

	REG32(0xc0018028+chn_offset) =0x0;
}

void ddr_power_test()
{
	switch(ddr_wait_pwrtest_cmd()) {
        case CASE_SELF_REFRESH:
            /* useless */
            __ddr_print("case 7\n");
			break;
        case CASE_BIST_READ:
            __ddr_print("case 0\n");
            bist_all_bm_read(0);
            break;
        case CASE_BIST_WRITE:
            __ddr_print("case 1\n");
            bist_all_bm_write(0);
            break;
        case CASE_BIST_SIPI:
            __ddr_print("case 2\n");
            //bist_all_bm_read(0);
            break;
        case CASE_POWER_DOWN1:
            __ddr_print("case 3\n");
            testcase_power_down(1);
            break;
        case CASE_POWER_DOWN2:
            __ddr_print("case 4\n");
            testcase_power_down(2);
            break;
        case CASE_POWER_DOWN3:
            __ddr_print("case 5\n");
            testcase_power_down(3);
            break;
        case CASE_POWER_DOWN4:
            __ddr_print("case 6\n");
            testcase_power_down(4);
            break;
        case CASE_POWER_DOWN5:
            __ddr_print("case 17\n");
            testcase_power_down5(4);
            break;
        case CASE_POWER_DOWN6:
            __ddr_print("case 18\n");
            testcase_power_down6(4);
            break;
        case CASE_POWER_DOWN7:
            __ddr_print("case 19\n");
            testcase_power_down7(4);
            break;
        case CASE_LIGHT_AUTO:
            __ddr_print("case 13\n");
            testcase_smart_light();
            break;
        case CASE_LIGHT_WITH_RETENTION:
            __ddr_print("case 8\n");
            *(volatile uint32*)0xc00180bc = 0x1800000;
            reg_bit_set(0xE42C0008, 0, 5, 0x14);
            reg_bit_set(0xE42E013C, 21, 2, 0x3);
            reg_bit_set(0xE42B012C, 4, 1, 0x0);// disable auto sleep
            reg_bit_set(0xE42B012C, 3, 1, 0x1);// force to enter sleep mode
            break;
        case CASE_LIGHT:
            __ddr_print("case 9\n");
            *(volatile uint32*)0xc00180bc = 0x1800000;
            reg_bit_set(0xE42C0008, 0, 5, 0x14);
            reg_bit_set(0xE42E013C, 21, 2, 0x0);
            reg_bit_set(0xE42B012C, 4, 1, 0x0);// disable auto sleep
            reg_bit_set(0xE42B012C, 3, 1, 0x1);// force to enter sleep mode
            break;
        case CASE_PUB_POWER_DOWN:
            __ddr_print("case 10\n");
            /* useless */
            break;
        case CASE_CHANNEL_POWER:
            __ddr_print("case 11\n");
            /* useless */
            break;
        case CASE_DEEP_SLEEP:
            __ddr_print("case 12\n");
            reg_bit_set(0xE42B012C, 2, 1, 0x1);
            break;
        case CASE_RPULL:
            __ddr_print("case 15\n");
            *(volatile uint32*)0xC00030C8 =
                *(volatile uint32*)0xC00030C8 | 0x20000000;
            break;
        case CASE_BYPASS_DESKEW:
            __ddr_print("case 16\n");
            *(volatile uint32*)0xC0003058 =
                *(volatile uint32*)0xC0003058 | 0xff;
            break;
        case CASE_IDLE:
            __ddr_print("case 13\n");
			break;
	}

    while(1);
}
#endif

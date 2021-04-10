
#define	BIST_BASE_ADDR	0x31070000
#define	BIST_PORT_ADDR	0x31053400

#if 1
//USER PATTERN
#define	BIST_DATA_00_PATTERN		0xFFFFFFFF
#define	BIST_DATA_01_PATTERN		0x00000000
#define	BIST_DATA_02_PATTERN		0xFFFFFFFF
#define	BIST_DATA_03_PATTERN		0x00000000
#define	BIST_DATA_04_PATTERN		0x00000000
#define	BIST_DATA_05_PATTERN		0xFFFFFFFF
#define	BIST_DATA_06_PATTERN		0x00000000
#define	BIST_DATA_07_PATTERN		0xFFFFFFFF
#define	BIST_DATA_08_PATTERN		0x00000000
#define	BIST_DATA_09_PATTERN		0x00000000
#define	BIST_DATA_10_PATTERN		0xFFFFFFFF
#define	BIST_DATA_11_PATTERN		0xFFFFFFFF
#define	BIST_DATA_12_PATTERN		0xFFFFFFFF
#define	BIST_DATA_13_PATTERN		0xFFFFFFFF
#define	BIST_DATA_14_PATTERN		0x00000000
#define	BIST_DATA_15_PATTERN		0x00000000
#define	BIST_DATA_16_PATTERN		0xFFFFFFFF
#define	BIST_DATA_17_PATTERN		0xFFFFFFFF
#define	BIST_DATA_18_PATTERN		0xFFFFFFFF
#define	BIST_DATA_19_PATTERN		0xFFFFFFFF
#define	BIST_DATA_20_PATTERN		0x00000000
#define	BIST_DATA_21_PATTERN		0x00000000
#define	BIST_DATA_22_PATTERN		0x00000000
#define	BIST_DATA_23_PATTERN		0x00000000
#define	BIST_DATA_24_PATTERN		0x00000000
#define	BIST_DATA_25_PATTERN		0x00000000
#define	BIST_DATA_26_PATTERN		0x00000000
#define	BIST_DATA_27_PATTERN		0x00000000
#define	BIST_DATA_28_PATTERN		0xFFFFFFFF
#define	BIST_DATA_29_PATTERN		0xFFFFFFFF
#define	BIST_DATA_30_PATTERN		0xFFFFFFFF
#define	BIST_DATA_31_PATTERN		0xFFFFFFFF
#else
//USER PATTERN
#define	BIST_DATA_00_PATTERN		0x0
#define	BIST_DATA_01_PATTERN		0x00000000
#define	BIST_DATA_02_PATTERN		0x0
#define	BIST_DATA_03_PATTERN		0x00000000
#define	BIST_DATA_04_PATTERN		0x00000000
#define	BIST_DATA_05_PATTERN		0x0
#define	BIST_DATA_06_PATTERN		0x00000000
#define	BIST_DATA_07_PATTERN		0x0
#define	BIST_DATA_08_PATTERN		0x00000000
#define	BIST_DATA_09_PATTERN		0x00000000
#define	BIST_DATA_10_PATTERN		0x0
#define	BIST_DATA_11_PATTERN		0x0
#define	BIST_DATA_12_PATTERN		0x0
#define	BIST_DATA_13_PATTERN		0x0
#define	BIST_DATA_14_PATTERN		0x00000000
#define	BIST_DATA_15_PATTERN		0x00000000
#define	BIST_DATA_16_PATTERN		0x0
#define	BIST_DATA_17_PATTERN		0x0
#define	BIST_DATA_18_PATTERN		0x0
#define	BIST_DATA_19_PATTERN		0x0
#define	BIST_DATA_20_PATTERN		0x00000000
#define	BIST_DATA_21_PATTERN		0x00000000
#define	BIST_DATA_22_PATTERN		0x00000000
#define	BIST_DATA_23_PATTERN		0x00000000
#define	BIST_DATA_24_PATTERN		0x00000000
#define	BIST_DATA_25_PATTERN		0x00000000
#define	BIST_DATA_26_PATTERN		0x00000000
#define	BIST_DATA_27_PATTERN		0x00000000
#define	BIST_DATA_28_PATTERN		0x0
#define	BIST_DATA_29_PATTERN		0x0
#define	BIST_DATA_30_PATTERN		0x0
#define	BIST_DATA_31_PATTERN		0x0

#endif

//SIPI PATTERN
#define	BIST_SIPI_DATA_00			0x444444B0
#define	BIST_SIPI_DATA_01			0xBBBB4044
#define	BIST_SIPI_DATA_02			0x0FF0BBBB
#define	BIST_SIPI_DATA_03			0x0CC0AA00
#define	BIST_SIPI_DATA_04			0xFF000F0F
#define	BIST_SIPI_DATA_05			0x0000aa00
#define	BIST_SIPI_BIT_PATTERN_0		0x00000000
#define	BIST_SIPI_BIT_PATTERN_1		0x00000000

//LFSR PATTERN
#define	BIST_DATA_LFSR_SEED_L0	0x12345678
#define	BIST_DATA_LFSR_SEED_L1	0x89abcdef
#define	BIST_DATA_LFSR_SEED_H0	0x8abce529
#define	BIST_DATA_LFSR_SEED_H1	0xfbed20ec


#define	PORT0_CPU_EN						1    //CHN0, Priority high
#define	PORT1_GPU_EN						0    //CHN0, Priority low
#define	PORT2_DPU_DCAM_EN				1	//CHN1, Priority high
#define	PORT3_ISP_EN						0	//CHN2, Priority high
#define	PORT4_AP_VSP_AON_EN				0	//CHN1, Priority low
#define	PORT5_WTLCP_EN					1	//CHN2, Priority middle
#define	PORT6_PUBCP_AUDCP_EN			0	//CHN2, Priority low



enum BIST_DATA_SIZE
{
	BYTE=0,
	HALF_WORD,
	WORD,
	TWO_WORDS,
	FOUR_WORDS
};

enum BIST_DATA_PATTERN_MODE
{
	USER_DATA_PATTERN=0,
	SIPI_DATA_PATTERN,
	LFSR_DATA_PATTERN,
	XTK_DATA_PATTERN
};

enum BIST_MODE
{
	BIST_WRITE=0,
	BIST_READ,
	BIST_ALLWRC,
	BIST_ONEWRC
};

enum BIST_CHN_NUM
{
	BIST_CHN0=0,
	BIST_CHN1=1,
	BIST_CHN2=2
};

enum HW_TEST_CASE
{
	HW_TEST_CASE0=0,
	HW_TEST_CASE1,
	HW_TEST_CASE2,
	HW_TEST_CASE3,
};


#define UL_ONEBITS 0xffffffff
#define UL_LEN 32
#define CHECKERBOARD1 0x55555555
#define CHECKERBOARD2 0xaaaaaaaa
#define UL_BYTE(x) ((x | x << 8 | x << 16 | x << 24))

#define PROGRESSLEN 4
#define PROGRESSOFTEN 2500
#define ONE 0x00000001L

#define SOURCE_ADDR 0x80000000
#define DST_ADDR    0xC0000000
#define MEM_TEST_LEN 0x40000


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
void ddr_memtester(void);
void ddr_mem_test(void);
void dram_bist_test_for_hw(u32 test_case);
void dram_bist_test();
void dram_mem_test(u32 src_addr,u32 dst_addr);




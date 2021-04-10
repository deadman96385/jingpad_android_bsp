//#define DEBUG_INFO_BASE		0xE6000000
#define DEBUG_INFO_BASE			0x50003000
//#define TEST_BASE_ADDR_1		0x80000000
//#define TEST_BASE_ADDR_2		0xa0000000
#define TEST_LEN				(0x1000000)

#define RANDOM_SEED_DATA		0x2345abcd
#define IRAM_SPACE_FOR_TEST		(DEBUG_INFO_BASE + 0x1000)

#define UL_BYTE(x) ((x | x << 8 | x << 16 | x << 24))

#define CHECKERBOARD1 0x55555555
#define CHECKERBOARD2 0xaaaaaaaa
//#define CONFIG_POWER_TEST
#define CONFIG_MEM_TEST 1
typedef unsigned int uint32;
#define REG32(x)   (*((volatile uint32 *)(x)))



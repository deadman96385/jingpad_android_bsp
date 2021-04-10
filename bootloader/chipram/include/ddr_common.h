
#include <config.h>
#include <adi.h>
#include <asm/arch/sprd_reg.h>

#ifndef CONFIG_SOC_IWHALE2
#ifndef CONFIG_SOC_ISHARKL2
#ifndef uint32
typedef unsigned int				uint32;
#endif
#endif
#endif

#ifndef uint64
typedef unsigned long long 			uint64;
#endif

//#define REG32(_x_)	(*(volatile uint32*)(_x_))
#define REG32(_x_)	(*(volatile uint32*)((uint64)(_x_)))
#define BOOLEAN          unsigned char
#define TRUE		1
#define FALSE		0

#define NULL        0

#define CLK_24MHZ    24
#define CLK_26MHZ    26
#define CLK_38_4MHZ  38
#define CLK_48MHZ    48
#define CLK_64MHZ    64
#define CLK_76_8MHZ  77
#define CLK_96MHZ    96
#define CLK_100MHZ   100
#define CLK_153_6MHZ 154
#define CLK_150MHZ   150
#define CLK_166MHZ   166
#define CLK_192MHZ   192
#define CLK_200MHZ   200
#define CLK_250MHZ   250
#define CLK_333MHZ   333
#define CLK_400MHZ   400
#define CLK_427MHZ   427
#define CLK_450MHZ   450
#define CLK_500MHZ   500
#define CLK_525MHZ   525
#define CLK_533MHZ   533
#define CLK_537MHZ   537
#define CLK_540MHZ   540
#define CLK_550MHZ   550
#define CLK_640MHZ   640
#define CLK_667MHZ   667
#define CLK_800MHZ	 800
#define CLK_1000MHZ	 1000
#define EMC_CLK_400MHZ 400
#define EMC_CLK_450MHZ 450
#define EMC_CLK_500MHZ 500

#if defined (CONFIG_SOC_IWHALE2) || defined(CONFIG_SOC_ISHARKL2)
#define DDR_DUMMY_REG 0xE42E002C //BOOT_MODE read only
#else
#define DDR_DUMMY_REG 0x402E002C //BOOT_MODE read only
#endif

#if defined (CONFIG_SOC_IWHALE2) || defined(CONFIG_SOC_ISHARKL2)
#define UART0_TX_BUF_ADDR   0xE7100000
#define UART0_TX_BUF_CNT    ((REG32(UART0_TX_BUF_ADDR +0xc) >> 8)&0xff)
#define UARTO_CKD0          0xE7100024
#else
#define UART0_TX_BUF_ADDR   0x70100000
#define UART0_TX_BUF_CNT    ((REG32(UART0_TX_BUF_ADDR +0xc) >> 8)&0xff)
#define UARTO_CKD0          0x70100024
#endif

#define USER_MODE 0
#define SIPI_MODE 1
#define LFSR_MODE 2

#define DWORD 0
#define BYTE  1
#define HWORD 2
#define WORD  3

#define BIST_WRITE  0
#define BIST_READ   1
#define BIST_ALLWRC 2
#define BIST_ONEWRC 3

#define DDR_CHN0 0
#define DDR_CHN1 1

#define BIST_ARM 0
#define BIST_GPU 1

#if defined (CONFIG_SOC_IWHALE2) || defined(CONFIG_SOC_ISHARKL2)
#define ANA_REG_GLB_ARM_MOULE_EN	0xe4008c08
#define ANA_REG_GLB_RTC_CLK_EN		0xe4008c18
#define WDG_BASE_ADDR					0xe4008080

#define BIT_ANA_WDG_EN				(1<<2)
#define BIT_RTC_WDG_EN				(1<<2)

#define WDG_INT_EN_BIT				BIT(0)
#define WDG_CNT_EN_BIT			BIT(1)
#define WDG_NEW_VER_EN			BIT(2)
#define WDG_INT_CLEAR_BIT			BIT(0)
#define WDG_RST_CLEAR_BIT			BIT(3)
#define WDG_LD_BUSY_BIT			BIT(4)
#define WDG_RST_EN_BIT				BIT(3)
#define ANA_RST_STATUS				ANA_REG_GLB_POR_RST_MONITOR
#define ANA_AGEN					ANA_REG_GLB_ARM_MODULE_EN
#define ANA_RTC_CLK_EN				ANA_REG_GLB_RTC_CLK_EN
#define AGEN_WDG_EN				BIT_ANA_WDG_EN
#define AGEN_RTC_WDG_EN			BIT_RTC_WDG_EN
#define WDG_CLK						32768
#define WDG_UNLOCK_KEY			0xE551
#define WDG_LOAD_LOW				(WDG_BASE_ADDR + 0x00)
#define WDG_LOAD_HIGH				(WDG_BASE_ADDR + 0x04)
#define WDG_CTRL					(WDG_BASE_ADDR + 0x08)
#define WDG_INT_CLR				(WDG_BASE_ADDR + 0x0c)
#define WDG_INT_RAW				(WDG_BASE_ADDR + 0x10)
#define WDG_INT_MSK				(WDG_BASE_ADDR + 0x14)
#define WDG_CNT_LOW				(WDG_BASE_ADDR + 0x18)
#define WDG_CNT_HIGH				(WDG_BASE_ADDR + 0x1c)
#define WDG_LOCK					(WDG_BASE_ADDR + 0x20)
#else
#if defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2731R)
#define ANA_WTG_BASE    0x40038080
//#define WDG_BASE            (ANA_WDG_BASE)
#define WDG_UNLOCK_KEY	0xE551
#define WDG_LOAD_LOW	(ANA_WTG_BASE+0x00)
#define WDG_LOAD_HIGH	(ANA_WTG_BASE+0x04)
#define WDG_CTRL		(ANA_WTG_BASE+0x08)
#define WDG_LOCK		(ANA_WTG_BASE+0x20)
/*
#define WDG_BASE            (ANA_WDG_BASE)
#define WDG_LOAD_LOW        (WDG_BASE + 0x00)
#define WDG_LOAD_HIGH       (WDG_BASE + 0x04)
#define WDG_CTRL            (WDG_BASE + 0x08)
#define WDG_INT_CLR         (WDG_BASE + 0x0C)
#define WDG_INT_RAW         (WDG_BASE + 0x10)
#define WDG_INT_MSK         (WDG_BASE + 0x14)
#define WDG_CNT_LOW         (WDG_BASE + 0x18)
#define WDG_CNT_HIGH        (WDG_BASE + 0x1C)
#define WDG_LOCK            (WDG_BASE + 0x20)
#define WDG_CNT_RD_LOW      (WDG_BASE + 0x24)
#define WDG_CNT_RD_HIGH     (WDG_BASE + 0x28)
#define WDG_CNT_IRQV_LOW    (WDG_BASE + 0x2C)
#define WDG_CNT_IRQV_HIGH   (WDG_BASE + 0x30)
*/
#endif
#endif
void reg_bit_set(uint32 addr,uint32 start_bit,uint32 bits_num,uint32 val);
void wait_us(uint32 us);
void wait_10us(uint32 us_10);
uint32 __raw_readl(uint32 addr);
void __raw_writel(uint32 addr,uint32 val);
void __ddr_print(char * log);
void __ddr_wdg_reset();
void ddr_print_u32_hex(uint32 data);
uint32 bist_test();

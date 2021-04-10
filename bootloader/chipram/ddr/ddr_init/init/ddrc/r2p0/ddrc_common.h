#ifndef __DDR_COMMON_H
#define __DDR_COMMON_H

#include <sci_types.h>

typedef unsigned int u32;
typedef unsigned long ulong;
typedef unsigned long long u64;
typedef char boolean;

//#define REG32(_X_)	(*(volatile u32*)((u64)(_X_)))
#define TRUE		1
#define FALSE		0
//#define NULL		0

#define	DDR_CLK_26M		26
#define	DDR_CLK_256M		256
#define	DDR_CLK_311M		311
#define	DDR_CLK_384M		384
#define	DDR_CLK_512M		512
#define	DDR_CLK_622M		622
#define	DDR_CLK_768M		768
#define	DDR_CLK_933M		933
#define	DDR_CLK_1200M		1200
#define	DDR_CLK_1333M		1333
#define	DDR_CLK_1866M		1866



#define AP_AHB_RF_BASE_ADDR				0x20100000
#define DMC_CTL_REG_BASE_ADDR			0x31000000
#define DMC_PHY_REG_BASE_ADDR			0x31001000
#define PUB_QOSC_AHB_RF_BASE_ADDR		0x31020000
#define PUB_AHB_RF_BASE_ADDR			0x31030000
#define PUB_CTL_APB_BASE_ADDR			0x31050000
#define AON_APB_RF_BASE_ADDR			0x327d0000
#define PMU_APB_BASE_ADDR				0x327e0000
#define ANLG_PHY_GROUP_BASE_ADDR		0x32390000
#define ANLG_PHY_GROUP_RF_BASE_ADDR		0x323E0000



#define	DDR_SLP_CTRL_STATUS				(PMU_APB_BASE_ADDR+0x07b8)


#define UART1_TX_BUF_ADDR 				0X70100000


#define DMC_CTL0_(x)	(DMC_CTL_REG_BASE_ADDR+(x))
#define DMC_PHY0_(x)	(DMC_PHY_REG_BASE_ADDR+(x))

void dmc_print_str(const char *string);
int print_Dec(u32 val);
int print_Hex(u32 val);
int print_String(const char *string);
#endif

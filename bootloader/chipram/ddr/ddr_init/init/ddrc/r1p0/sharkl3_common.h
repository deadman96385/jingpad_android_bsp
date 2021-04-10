#ifndef _SHARKL3_COMMON_H

#define _SHARKL3_COMMON_H

#include "debug.h"
#if (defined DDR_REINIT_TEST) || (defined POWER_TEST) || (defined DFS_SUPPORT)
#include "sci_types.h"


//#ifndef uint32
//typedef unsigned int  uint32;
//#endif

#define REG32(x)						(*((volatile unsigned int*)(x)))

//#define TWPLL_CONFIG

//#define RUN_CM4
#define DMC_CTRL_BASE_ADDR			0x30000000
#define PERF_MONITOR_BASE_ADDR		0x30010000
#define DDR_BIST_CH_BASE_ADDR			0x30080000
#define MEM_FW_PUB_BASE_ADDR			0x30090000
#define DFI_BUSMON_BASE_ADDR			0x300c0000
#define PUB_AHB_RF_BASE_ADDR			0x300e0000
#define PUB_AHB_WRAP_RF_BASE_ADDR	0x300f0000
#define PUBSYS_TOP_BASE_ADDR			0x30200000
#define QOSC_BASE_ADDR				0x30210000
#define DDR_PHY_CH0_BASE_ADDR		0x30400000
#define DDR_PHY_CH1_BASE_ADDR		0x30410000


#define PMU_APB_BASE_ADDR				0x402b0000
#define AON_APB_RF_BASE_ADDR			0x402e0000

#define ANLG_PHY_GROUP_REG			0x40363000


#define PD_PUB_SYS_CFG							(PMU_APB_BASE_ADDR+0x005c)
#define PWR_STATUS2_DBG						(PMU_APB_BASE_ADDR+0x00c4)
#define PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE		(PMU_APB_BASE_ADDR+0x00c8)
#define DDR_OP_MODE_CFG						(PMU_APB_BASE_ADDR+0x012c)
#define DDR_PHY_RET_CFG						(PMU_APB_BASE_ADDR+0x0130)
#define PUB_ACC_RDY							(PMU_APB_BASE_ADDR+0x0250)
#define SLEEP_CTL2								(PMU_APB_BASE_ADDR+0x04a8)
#define DDR_SLP_CTRL_CFG0						(PMU_APB_BASE_ADDR+0x0648)


#define APB_EB2									(AON_APB_RF_BASE_ADDR+0x00b0)

#define DPLL0_CTRL0								(ANLG_PHY_GROUP_REG+0x0000)
#define DPLL0_CTRL1								(ANLG_PHY_GROUP_REG+0x0004)
#define DPLL0_CTRL2								(ANLG_PHY_GROUP_REG+0x0008)
#define DPLL0_CTRL3								(ANLG_PHY_GROUP_REG+0x000c)
#define DPLL1_CTRL0								(ANLG_PHY_GROUP_REG+0x0014)
#define DPLL1_CTRL1								(ANLG_PHY_GROUP_REG+0x0018)
#define DPLL1_CTRL2								(ANLG_PHY_GROUP_REG+0x001c)
#define DPLL1_CTRL3								(ANLG_PHY_GROUP_REG+0x0020)

#define DFS_SW_CTRL							(PUB_AHB_WRAP_RF_BASE_ADDR+0x0008)
#define DFS_PURE_SW_CTRL						(PUB_AHB_WRAP_RF_BASE_ADDR+0x0018)
#define DFS_SW_CTRL1							(PUB_AHB_WRAP_RF_BASE_ADDR+0x0030)
#define DFS_SW_CTRL2							(PUB_AHB_WRAP_RF_BASE_ADDR+0x0034)
#define DFS_HW_CTRL							(PUB_AHB_WRAP_RF_BASE_ADDR+0x0100)

#define DMC_RST_CTL								(PUBSYS_TOP_BASE_ADDR+0x0080)
#define DMC_CLK_INIT_SW_START					(PUBSYS_TOP_BASE_ADDR+0x0100)
#define DMC_CLK_STATE							(PUBSYS_TOP_BASE_ADDR+0x0104)
#define DMC_CLK_INIT_CFG						(PUBSYS_TOP_BASE_ADDR+0x0108)


#define DMC_CTL_(x)								(DMC_CTRL_BASE_ADDR+x*4)
#define MEM_FW_(X)								(MEM_FW_PUB_BASE_ADDR+X*4)
#define DFI_BUSMON_(X)							(DFI_BUSMON_BASE_ADDR+X*4)
#define DMC_PHY0_(x)							(DDR_PHY_CH0_BASE_ADDR+x*4)
#define DMC_PHY1_(x)							(DDR_PHY_CH1_BASE_ADDR+x*4)


#define IS_LPDDR4(x)    (((x&0xff000000) == 0x40000000)?TRUE:FALSE)
#define IS_LPDDR3(x)    (((x&0xff000000) == 0x30000000)?TRUE:FALSE)

enum RE_FREQ_CHECK_RET{
    SUCCESS=0,
    FAILURE=1
};

enum RE_DDR_TYPE
{
	LPDDR3=0x3,
	LPDDR4=0x4
};

enum RE_PLL_SOURCE
{
	DPLL0=0,
	DPLL1,
	TWPLL
};

enum RE_CLK_TYPE
{
	RE_CLK_156M=156,
	RE_CLK_160M=160,
	RE_CLK_233M=233,
	RE_CLK_311M=311,
	RE_CLK_384M=384,
	RE_CLK_400M=400,
	RE_CLK_512M=512,
	RE_CLK_533M=533,
	RE_CLK_622M=622,
	RE_CLK_768M=768,
	RE_CLK_800M=800,
	RE_CLK_933M=933,
	RE_CLK_1536M=1536,
	RE_CLK_1600M=1600,
};

enum RE_DESKEWPLL_STATUS
{
	DESKEW_OFF=0,
	DESKEW_ON,
	DESKEW_OFF_BYAPSS

};



struct RE_CLK_DFS_CFG
{
	uint32 pll_sel;
	uint32 dpll_div_sel;
	uint32 deskew_mode;
	uint32 x1_sel;
	uint32 d2_sel;
	uint32 half_freq_mode;
        uint32 updated;
};

struct RE_PUB_CLK_CFG
{
	uint32 freq_num;
	enum RE_CLK_TYPE ddr_clk;
	enum RE_PLL_SOURCE pll_source;
	enum RE_DESKEWPLL_STATUS deskewpll_status;
	uint32 ratio;
	struct RE_CLK_DFS_CFG  dfs_cfg;

};



extern void reg_bit_set(uint32 addr,uint32 start_bit,uint32 bits_num,uint32 val);
extern void wait_us(uint32 us);

#endif

#endif

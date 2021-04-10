#ifndef _ROC1_REINIT_H

#define _ROC1_REINIT_H
#include "debug.h"
#if (defined DDR_REINIT_TEST) || (defined POWER_TEST)
#include "roc1_common.h"

//#define DMA_CONFIG

#if !(defined POWER_TEST)
#define BIST_TEST_RE
#endif
#define DEBUG_REINIT

#define HIGH_LEVEL					1

#define DMC_CTRL_REG0_NUM			24
#define DMC_CTRL_REG1_NUM			220
#define MEM_FW_REG_NUM			279
#define MEM_FW_REG0_NUM			2 //0x0-0x4,0x100,0x200-0x21c,0x400-0x41c,0x800-0x844,0x1000-0x13c4
#define MEM_FW_REG1_NUM			1
#define MEM_FW_REG2_NUM			8
#define MEM_FW_REG3_NUM			8
#define MEM_FW_REG4_NUM			18
#define MEM_FW_REG5_NUM			242
#define DFI_BUMON_REG_NUM			37
#define DMC_PHY_REG_NUM			214

#define MEM_FW_REG_SECTION_NUM 6

#define REG_PMU_APB_SLEEP_STATUS 0x402B00D4

typedef enum
{
	PUB_POWERON,
	PUB_POWEROFF
}RE_PUB_STATUS;

struct RE_ddr_sys_info
{
	enum RE_DDR_TYPE ddr_type;
	uint32 ddr_clk;
	uint32 freq_num;
};

struct RE_ddr_debug_info
{
	uint32 pub_poweroff_state;
	uint32 reg_pmu_apb_sleep_status;
	uint32 pub_poweroff_time;
	uint32 pub_poweroff_num;
	uint32 pub_poweron_time;
	uint32 pub_poweron_num;
};


extern void DMC_ReInit(void);

#endif
#endif

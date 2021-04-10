#ifndef _ISHARKL2_COMMON_H

#define _ISHARKL2_COMMON_H

//#include <config.h>
//#include <adi_hal_internal.h>
//#include <asm/arch/sprd_reg.h>

#include "ddr_common.h"
#include "isharkl2_base_common.h"

#define	PD_PUB0_SYS_PWR_CFG			(AON_PMU_APB_BASE+0x44)

#define PMU_APB_DDR_SLEEP_CTRL 			(AON_COM_PMU_APB_BASE+0x8)
#define	PMU_APB_PUB0_SYS_SLEEP_CTRL		(AON_PMU_APB_BASE+0x12c)
#define	PUB0_APB_CGM_MCTRL_DIV			(PUB0_APB_RF_PUB0_BASE+0x4050)

#define PUB0_SYS_SLEEP_CTRL				(AON_PMU_APB_BASE + 0x012c)


#define PWR_STATE_DBG1					(AON_PMU_APB_BASE + 0x011c)
#define PWR_STATE_DBG2					(AON_PMU_APB_BASE + 0x0120)
#define PWR_STATE_DBG3					(AON_PMU_APB_BASE + 0x0124)
#define PWR_STATE_DBG4					(AON_PMU_APB_BASE + 0x0128)

#define IS_LPDDR4(x)    (((x&0xff000000) == 0x40000000)?TRUE:FALSE)
#define IS_LPDDR3(x)    (((x&0xff000000) == 0x30000000)?TRUE:FALSE)

#ifdef RUN_CM4
	#define PARA_SAVE_ADDRESS	0x2002a000
#else
	#define PARA_SAVE_ADDRESS	0xE602A000
#endif

/*-----------------------------need to ensure---------------------*/
#define DDR_INFO_SAVE_SIZE			20
#define DEBUG_REINIT_SAVE_SIZE		40
#define DEBUG_DFS_SAVE_SIZE		40
#define CTL0_REG_SAVE_SIZE			481
#define PI0_REG_SAVE_SIZE			249
#define PHY0_REG0_SAVE_SIZE		85
#define PHY0_REG1_SAVE_SIZE		101
#define PHY0_REG2_SAVE_SIZE		38


#define BW_OF(x,y,z) (x*2*4*y*z*10)		// x:ddr_clk(MHz)	y:rate(%)	z:timer_cycle(ms) 	ddr_clk*2*4*y*0.01*1000*1000*z*0.001
#define BW_UF(x,y,z) (x*2*4*y*z*10)		// x:ddr_clk(MHz)	y:rate(%)	z:timer_cycle(ms) 	ddr_clk*2*4*y*0.01*1000*1000*z*0.001



enum DRAM_TYPE_E
{
	LPDDR3=0x7,
	LPDDR4=0xb
};

#if 0
enum CLK_TYPE_E
{
	CLK_26M=26,
	CLK_233M=233,
	CLK_466M=466,
	CLK_622M=622,
	CLK_933M=933

};
#endif
enum SET_CONFG_E
{
	DISABLE=0,
	ENABLE=1
};

struct DDR_INFO_G
{
	enum DRAM_TYPE_E ddr_type;
	uint32 ddr_clk;
	uint32 freq_num;
	uint32 support_freq_num;
	uint32 bist_addr;
	uint32 init_done;
	uint32 sleep_flag;
	uint32 dfs_mode;
	uint32 hw_dfs_en;
	uint32 dfi_bm_timer;
	uint32 dfs_freq_en;    //bit[0]:f0, bit[1]:f1, bit[2]:f2 bit[3]:f3
};

struct DEBUG_REINIT_INFO_T
{
	volatile uint32 pub_poweroff_state;
	volatile uint32 pub_sleep_counter;
	volatile uint32 pub_wakeup_counter;
	volatile uint32 pub_poweron_step;
	volatile uint32 pub_poweroff_step;
	volatile uint32 pub_poweron_max_time;
	volatile uint32 pub_poweron_aver_time;
	volatile uint32 pub_poweroff_max_time;
	volatile uint32 pub_poweroff_aver_time;
	volatile uint32 state_selfrefresh;
	volatile uint32 poweron_bist_result;
};

struct DEBUG_DFS_INFO_T
{
	volatile uint32 dfs_freq_en;
	volatile uint32 dfs_f0_counter;
	volatile uint32 dfs_f1_counter;
	volatile uint32 dfs_f2_counter;
	volatile uint32 dfs_f3_counter;
	volatile uint32 dfs_step;
	volatile uint32 dfi_bm_step;
	volatile uint32 dfs_total_times;
	volatile uint32 dfs_sw_times;
};

struct DFS_INFO_C
{
	uint32 freq_clk;
	uint32 freq_num;
	uint32 ratio;
	uint32 scan_ratio;
	uint32 bm_of_threshold;
	uint32 bm_uf_threshold;
};

//aon space: 20KB, 0x2000a000--0x2000EFFF
struct IRAM_DDR_REG_INFO
{
	struct DDR_INFO_G  *ddr_info;
	struct DEBUG_REINIT_INFO_T *debug_reinit_info;
	struct DEBUG_DFS_INFO_T *debug_dfs_info;
	uint32 *ctl_reg;
	uint32 *pi_reg;
	uint32 *phy_reg[4][9];
};

extern struct IRAM_DDR_REG_INFO  iram_addr_info;
extern struct DDR_INFO_G  *ddr_info_g;
extern struct DEBUG_REINIT_INFO_T *reinit_info_g;
extern struct DEBUG_DFS_INFO_T	*dfs_info_g;
extern struct DFS_INFO_C *dfs_info_constant;
extern struct DFS_INFO_C  lp3_dfs_info[4];


//extern void reg_bit_set(uint32 addr,uint32 start_bit,uint32 bits_num,uint32 val);
//extern void wait_us(uint32 us);
extern uint32 cm4_bist_test();
extern void SCI_DisableIRQ();
extern void SCI_DisableFIQ();
#endif


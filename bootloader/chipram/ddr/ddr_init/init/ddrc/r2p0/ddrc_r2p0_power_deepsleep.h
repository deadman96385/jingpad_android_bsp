#ifndef _DDRC_R2P0_POWER_DEEPSLEEP_H__
#define _DDRC_R2P0_POWER_DEEPSLEEP_H__

#define DMC_PHY_REG_NUM 496

#define DMC_CTRL_REG0_NUM 24
#define DMC_CTRL_REG1_NUM 220

#define FORCE_DEEP_SLEEP
#define DISP_ASYNC_BRG			(0x20100000+0x0050)
#define AON_TOP_BASE_ADDR		(0x327D0000)
#define APCPU_DDR_AB_LPC_CTRL	(AON_TOP_BASE_ADDR+0x0324)
#define AUDCP2DDR_SLI_LPC_CTRL	(AON_TOP_BASE_ADDR+0x03dc)
#define DCAM2DDR_SLI_LPC_CTRL	(AON_TOP_BASE_ADDR+0x03ec)
#define GPU2DDR_SLI_LPC_CTRL	(AON_TOP_BASE_ADDR+0x03f4)
#define ISP2DDR_SLI_LPC_CTRL	(AON_TOP_BASE_ADDR+0x03f8)

#define PD_PUB_SYS_CFG			 (PMU_APB_BASE_ADDR+0x006c)
#define PUB_APB_SLEEP_CTRL		 (PMU_APB_BASE_ADDR+0x00cc)
#define PWR_STATUS4_DBG			 (PMU_APB_BASE_ADDR+0x00b8)
#define PUB_SYS_DEEP_SLEEP_POLL1 (PMU_APB_BASE_ADDR+0x00e0)
#define PUB_SYS_DEEP_SLEEP_SEL	 (PMU_APB_BASE_ADDR+0x0360)
#define DDR_SLEEP_CTRL 			 (PMU_APB_BASE_ADDR+0x00d0)
#define REG_SYS_DDR_PWR_HS_ACK	 (PMU_APB_BASE_ADDR+0X07a8)


#define FENCING_CTRL			(PUB_CTL_APB_BASE_ADDR+0x3358)
#define POWER_DMC_CTL0_(x)			(DMC_CTL_REG_BASE_ADDR+4*(x))


typedef enum
{
	LPDDR3=0x3,
	LPDDR4=0x4,
}DDR_TYPE;
struct ddr_sys_info
{
	DDR_TYPE ddr_type;
	uint32 ddr_clk;
	uint32 freq_num;
};
struct PUB_CLK_CFG
{
	uint32 freq_num;
	uint32 ddr_clk;
	uint32 half_freq_mode;
	uint32 emc_ckg_d2_sel_pure_sw;
	uint32 pure_sw_dfs_freq_sel;
	uint32 emc_ckg_sel_pure_sw;
	uint32 pure_sw_dfs_clk_mode;
};
#endif


#ifndef __AVOID_DISTURB_INFO_H__
#define __AVOID_DISTURB_INFO_H__

#include <sci_types.h>

#ifdef CONFIG_AVOID_DISTURB_SOLUTION

typedef struct {
	uint8 disturbing_id;
	uint8 disturbed_id;
} id_num_info_t __attribute__((aligned(1)));

typedef struct {
	uint8 ddr_clk_src_num;
	uint8 dsi_clk_src_num;
	uint8 sdio_clk_src_num;
	uint8 emmc_clk_src_num;
	uint8 nand_clk_src_num;
} clk_src_num_info_t __attribute__((aligned(1)));

typedef enum {
	PLL_ID_MPLL = 0,
	PLL_ID_DPLL,
	PLL_ID_TWPLL,
	PLL_ID_CPLL,
	PLL_ID_GPLL,
	PLL_ID_MAX = 16,
} pll_id_e;

typedef struct {
	uint32 time_stamp;
	uint8  state:4;		//on and off
	uint8  clk_mode:4;	// 0:Normal 1:SpreadSpectrum
	uint8  delt_freq_index;
	uint8  src_clk_index;
	uint8  pll_id;
} cur_info_t __attribute__((aligned(1)));

typedef struct {
	/* lower 4bits: positive change; higher 4bits: negative change */
	uint8 deltfreq_bitmap_spread;
	/* lower 4bits: positive change; higher 4bits: negative change */
	uint8 deltfreq_bitmap_normal;
	uint8 clk_freq_index;
	uint8 reserved;
} delfreq_bitmap_t __attribute__((aligned(1)));

typedef struct {
	/* PRIORITY_LEVEL_E, the priority of DISTURB_ID like GSM/WCDMA... */
	uint8 priority;
	/* DISTURBED_ID_E */
	uint8 source_id;
	/* spread or normal */
	uint8 prefer;
	uint8 reserved;
} avoidance_source_info_t __attribute__((aligned(1)));

typedef struct {
	avoidance_source_info_t source_info;
	delfreq_bitmap_t deltfreq[DDR_CLK_SRC_NUM];
} ddr_request_info_t __attribute__((aligned(1)));

typedef struct {
	avoidance_source_info_t source_info;
	delfreq_bitmap_t deltfreq[DSI_CLK_SRC_NUM];
} dsi_request_info_t __attribute__((aligned(1)));

typedef struct {
	avoidance_source_info_t source_info;
	delfreq_bitmap_t deltfreq[SDIO_CLK_SRC_NUM];
} sdio_request_info_t __attribute__((aligned(1)));

typedef struct {
	avoidance_source_info_t source_info;
	delfreq_bitmap_t deltfreq[EMMC_CLK_SRC_NUM];
} emmc_request_info_t __attribute__((aligned(1)));

typedef struct {
	avoidance_source_info_t source_info;
	delfreq_bitmap_t deltfreq[NAND_CLK_SRC_NUM];
} nand_request_info_t __attribute__((aligned(1)));

typedef struct {
	ddr_request_info_t ddr_request_info[DISTURBED_ID_NUM];
	dsi_request_info_t dsi_request_info[DISTURBED_ID_NUM];
	sdio_request_info_t sdio_request_info[DISTURBED_ID_NUM];
	emmc_request_info_t emmc_request_info[DISTURBED_ID_NUM];
	nand_request_info_t nand_request_info[DISTURBED_ID_NUM];
} request_info_t __attribute__((aligned(1)));

id_num_info_t id_num = {
	DISTURBING_ID_NUM,
	DISTURBED_ID_NUM
};

clk_src_num_info_t cs_num = {
	DDR_CLK_SRC_NUM,
	DSI_CLK_SRC_NUM,
	SDIO_CLK_SRC_NUM,
	EMMC_CLK_SRC_NUM,
	NAND_CLK_SRC_NUM
};

request_info_t request_info = {
	{
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
		},
	},
	{
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
	},
	{
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
	},
	{
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
	},
	{
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
		{
			.source_info = { 0, 0, 0, 0 },
			.deltfreq = {
				{ 0, 0, 0, 0 },
			},
		},
	},
};

void fill_iram_avoid_info(void)
{
	sprd_memset(DISTURB_INFO_IRAM_BASE, 0, REQ_INFO_END_IRAM_OFFSET);

	sprd_memcpy(DISTURB_INFO_IRAM_BASE, &id_num, sizeof(id_num));
	sprd_memcpy(DISTURB_INFO_IRAM_BASE + MODULE_CLK_NUM_IRAM_OFFSET, &cs_num, sizeof(cs_num));
	sprd_memcpy(DISTURB_INFO_IRAM_BASE + REQ_INFO_IRAM_OFFSET, &request_info, sizeof(request_info));
}
#else
void fill_iram_avoid_info(void) {}
#endif

#endif

#include <config.h>
#include <common.h>
#include <sci_types.h>
/* delete  chip_drv_common_io_h */
#include "chip_id.h"
#include <asm/arch/sprd_reg.h>

typedef enum {
	BIA_NOC = 0,
	AP_NOC,
	GPU_NOC,
	VSP_NOC,
	CAM_NOC,
	/* DISPC and CAM use the same big NOC */
	DISPC_NOC,
	/* GSP and VSP use the same big NOC */
	GSP_NOC,
	MAX_NOC
} NOC_ARCH;

/* It will be only used in none-interleave mode in project iwhale2 */
typedef enum {
	DDR_8G = 0,
	DDR_1G,
	DDR_1_5G,
	DDR_2G,
	DDR_3G,
	DDR_4G
} DDR_CAPACITY;

typedef enum {
	NORMAL_MODE = 0,
	FULL_MODE,
	MIXED_MODE
} INTERLEAVE_MODE;

typedef enum {
	SIZE_256 = 0,
	SIZE_512,
	SIZE_1K,
	SIZE_2K
} INTERLEAVE_SEL;

typedef enum {
	DDR_UNREMAPPED = 0,
	DDR_REMAPPED
} INTERLEAVE_REMAP;

typedef enum {
	USED_NOC = 0,
	BYPASSED_NOC
} NOC_BYPASS;

struct noc_cfg {
	DDR_CAPACITY		ddr_capacity;
	INTERLEAVE_MODE	interleave_mode;
	INTERLEAVE_SEL		interleave_sel;
	INTERLEAVE_REMAP	interleave_remap;
	NOC_BYPASS			noc_bypass;
};

#define NOC_INTERL_MOD_MASK	0x3

struct noc_cfg noc_dev[MAX_NOC];


/**
 * ddr_capacity_ctrl: config signel DDR capacity.
 *
 * this configuration will make pub0 and pub1 DDR addr continuly.
 * e.g. cap is 4G, the pub0 DDR addr range is 0 ~ 0x7FFFFFFF,
 * pub1 DDR addr range is 0x80000000 ~ 0xFFFFFFFF.
 * if do not config it, the pub1 DDR addr range is 0x10000000 ~ 0x17FFFFFFF
 */
void sprd_ddr_capacity_ctrl(DDR_CAPACITY cap)
{
	int i;

	CHIP_REG_SET(REG_AON_APB_BIA_NOC_CTRL,
		BIT_AON_APB_BIA_PUB_CHIP_DDR_CAPACITY_I(cap));
	CHIP_REG_SET(REG_AON_APB_AP_NOC_CTRL,
		BIT_AON_APB_AP_PUB_CHIP_DDR_CAPACITY_I(cap));
	CHIP_REG_SET(REG_AON_APB_GPU_DDR_CTRL,
		BIT_AON_APB_GPU_CHIP_DDR_CAPACITY_I(cap));
	CHIP_REG_SET(REG_AON_APB_VSP_DDR_CTRL,
		BIT_AON_APB_CHIP_DDR_CAPACITY_I_VSP(cap));
	CHIP_REG_SET(REG_AON_APB_CAM_DDR_CTRL,
		BIT_AON_APB_CHIP_DDR_CAPACITY_I_CAM(cap));
	for (i = 0; i < MAX_NOC; i++)
		noc_dev[i].ddr_capacity = cap;
}

/*
 * when config bia noc ctrl register, cpu should be in security mode
 */
void sprd_bia_noc_ctrl(unsigned long base, INTERLEAVE_MODE mod)
{
	CHIP_REG_AND(base, ~(BIT_AON_APB_BIA_PUB_INTERLEAVE_MODE(NOC_INTERL_MOD_MASK)));
	CHIP_REG_OR(base, BIT_AON_APB_BIA_PUB_INTERLEAVE_MODE(mod));
	noc_dev[BIA_NOC].interleave_mode = mod;
}

void sprd_ap_noc_ctrl(unsigned long base, INTERLEAVE_MODE mod, INTERLEAVE_SEL sel)
{
	CHIP_REG_AND(base, ~(BIT_AON_APB_AP_NOC_ADDR_SWAP_SEL(NOC_INTERL_MOD_MASK) |
						BIT_AON_APB_AP_PUB_INTERLEAVE_MODE(NOC_INTERL_MOD_MASK)));

	CHIP_REG_OR(base, BIT_AON_APB_AP_NOC_ADDR_SWAP_SEL(sel) |
						BIT_AON_APB_AP_PUB_INTERLEAVE_MODE(mod) |
						BIT_AON_APB_AP_INTERLEAVE_REMAP);
	noc_dev[AP_NOC].interleave_mode = mod;
	noc_dev[AP_NOC].interleave_sel = sel;
	noc_dev[BIA_NOC].interleave_sel = sel;
	noc_dev[AP_NOC].interleave_remap = DDR_REMAPPED;
	noc_dev[BIA_NOC].interleave_remap = DDR_REMAPPED;
}

void sprd_gpu_noc_ctrl(unsigned long base, INTERLEAVE_MODE mod, INTERLEAVE_SEL sel)
{
	CHIP_REG_AND(base, ~(BIT_AON_APB_GPU_INTERLEAVE_MODE(NOC_INTERL_MOD_MASK) |
						BIT_AON_APB_GPU_NOC_ADDR_SWAP_SEL(NOC_INTERL_MOD_MASK)));

	CHIP_REG_OR(base, BIT_AON_APB_GPU_INTERLEAVE_MODE(mod) |
						BIT_AON_APB_GPU_NOC_ADDR_SWAP_SEL(sel) |
						BIT_AON_APB_GPU_INTERLEAVE_REMAP);
	noc_dev[GPU_NOC].interleave_mode = mod;
	noc_dev[GPU_NOC].interleave_sel = sel;
	noc_dev[GPU_NOC].interleave_remap = DDR_REMAPPED;
}

void sprd_vsp_noc_ctrl(unsigned long base, INTERLEAVE_MODE mod, INTERLEAVE_SEL sel)
{
	CHIP_REG_AND(base, ~(BIT_AON_APB_VSP_INTERLEAVE_MODE(NOC_INTERL_MOD_MASK) |
						BIT_AON_APB_VSP_NOC_ADDR_SWAP_SEL(NOC_INTERL_MOD_MASK)));

	CHIP_REG_OR(base, BIT_AON_APB_VSP_INTERLEAVE_MODE(mod) |
						BIT_AON_APB_VSP_NOC_ADDR_SWAP_SEL(sel) |
						BIT_AON_APB_VSP_INTERLEAVE_REMAP);
	noc_dev[VSP_NOC].interleave_mode = mod;
	noc_dev[VSP_NOC].interleave_sel = sel;
	noc_dev[GSP_NOC].interleave_sel = sel;
	noc_dev[VSP_NOC].interleave_remap = DDR_REMAPPED;
	noc_dev[GSP_NOC].interleave_remap = DDR_REMAPPED;
}

void sprd_cam_noc_ctrl(unsigned long base, INTERLEAVE_MODE mod, INTERLEAVE_SEL sel)
{
	CHIP_REG_AND(base, ~(BIT_AON_APB_CAM_INTERLEAVE_MODE(NOC_INTERL_MOD_MASK) |
						BIT_AON_APB_CAM_NOC_ADDR_SWAP_SEL(NOC_INTERL_MOD_MASK)));

	CHIP_REG_OR(base, BIT_AON_APB_CAM_INTERLEAVE_MODE(mod) |
						BIT_AON_APB_CAM_NOC_ADDR_SWAP_SEL(sel) |
						BIT_AON_APB_CAM_INTERLEAVE_REMAP);
	noc_dev[CAM_NOC].interleave_mode = mod;
	noc_dev[CAM_NOC].interleave_sel = sel;
	noc_dev[DISPC_NOC].interleave_sel = sel;
	noc_dev[CAM_NOC].interleave_remap = DDR_REMAPPED;
	noc_dev[DISPC_NOC].interleave_remap = DDR_REMAPPED;
}

void sprd_dispc_noc_ctrl(unsigned long base, INTERLEAVE_MODE mod, INTERLEAVE_SEL sel)
{
	CHIP_REG_AND(base, ~(BIT_AON_APB_DISP_INTERLEAVE_MODE(NOC_INTERL_MOD_MASK)));

	CHIP_REG_OR(base, BIT_AON_APB_DISP_INTERLEAVE_MODE(mod));
	noc_dev[DISPC_NOC].interleave_mode = mod;
}

void sprd_gsp_noc_ctrl(unsigned long base, INTERLEAVE_MODE mod)
{
	CHIP_REG_AND(base, ~(BIT_AON_APB_GSP_INTERLEAVE_MODE(NOC_INTERL_MOD_MASK)));

	CHIP_REG_OR(base, BIT_AON_APB_GSP_INTERLEAVE_MODE(mod));
	noc_dev[GSP_NOC].interleave_mode = mod;
}

/**
 * noc_signel_chn_latency_config: config signel DDR channel NOC lentency.
 *
 * Makesure this NOC is used none-interleave mode, if true, disable NOC,
 * and enable NIC to reduce latency.
 */
void sprd_noc_chn_latency_config(void)
{
	int noc_arch;

	for (noc_arch = 0; noc_arch < MAX_NOC; noc_arch++) {
		if ((noc_dev[noc_arch].interleave_mode == NORMAL_MODE) &&
			(noc_dev[noc_arch].noc_bypass == USED_NOC)) {
			switch (noc_arch) {
			case BIA_NOC:
			case AP_NOC:
				if ((noc_dev[BIA_NOC].interleave_mode == NORMAL_MODE) &&
					(noc_dev[AP_NOC].interleave_mode == NORMAL_MODE)) {
					CHIP_REG_OR(REG_AON_APB_ACCDDR_LATENCY_REDUCE_SEL,
						BIT_AON_APB_BIA2DDR_LATENCY_REDUCE_SEL);
					noc_dev[BIA_NOC].noc_bypass = BYPASSED_NOC;
					noc_dev[AP_NOC].noc_bypass = BYPASSED_NOC;
				}
				break;
			case GPU_NOC:
				CHIP_REG_OR(REG_AON_APB_ACCDDR_LATENCY_REDUCE_SEL,
					BIT_AON_APB_GPU2DDR_LATENCY_REDUCE_SEL);
				noc_dev[noc_arch].noc_bypass = BYPASSED_NOC;
				break;
			case VSP_NOC:
			case GSP_NOC:
				if ((noc_dev[VSP_NOC].interleave_mode == NORMAL_MODE) &&
					(noc_dev[GSP_NOC].interleave_mode == NORMAL_MODE)) {
					CHIP_REG_OR(REG_AON_APB_ACCDDR_LATENCY_REDUCE_SEL,
						BIT_AON_APB_VSP2DDR_LATENCY_REDUCE_SEL);
					noc_dev[VSP_NOC].noc_bypass = BYPASSED_NOC;
					noc_dev[GSP_NOC].noc_bypass = BYPASSED_NOC;
				}
				break;
			case CAM_NOC:
			case DISPC_NOC:
				if ((noc_dev[CAM_NOC].interleave_mode == NORMAL_MODE) &&
					(noc_dev[DISPC_NOC].interleave_mode == NORMAL_MODE)) {
					CHIP_REG_OR(REG_AON_APB_ACCDDR_LATENCY_REDUCE_SEL,
						BIT_AON_APB_CAM2DDR_LATENCY_REDUCE_SEL);
					noc_dev[CAM_NOC].noc_bypass = BYPASSED_NOC;
					noc_dev[DISPC_NOC].noc_bypass = BYPASSED_NOC;
				}
				break;
			}
		}
	}
}

/**
 * noc_signel_chn_init: init signel DDR channel NOC configuration.
 *
 * This function will only be called in signel channel mode.
 * If the chip uses only one DDR(PUB0 DDR), this function must be
 * called.
 */
void sprd_noc_signel_chn_init(void)
{
	int i;

	/* Disable NOC, but enable NIC, so it will reduce latency,
	 * but there some bugs need to fix when use bypass mode:
	 * BIA needs always use noc mode.
	 */
	if (!get_chip_version()) {
		CHIP_REG_OR(REG_AON_APB_ACCDDR_LATENCY_REDUCE_SEL,
			BIT_AON_APB_GPU2DDR_LATENCY_REDUCE_SEL |
			BIT_AON_APB_CAM2DDR_LATENCY_REDUCE_SEL |
			BIT_AON_APB_VSP2DDR_LATENCY_REDUCE_SEL
			/*BIT_AON_APB_BIA2DDR_LATENCY_REDUCE_SEL*/);
		for (i = GPU_NOC; i < MAX_NOC; i++)
			noc_dev[i].noc_bypass = BYPASSED_NOC;
	} else if (get_chip_version() == 1) {
		CHIP_REG_OR(REG_AON_APB_ACCDDR_LATENCY_REDUCE_SEL,
			BIT_AON_APB_GPU2DDR_LATENCY_REDUCE_SEL |
			BIT_AON_APB_CAM2DDR_LATENCY_REDUCE_SEL |
			BIT_AON_APB_VSP2DDR_LATENCY_REDUCE_SEL |
			BIT_AON_APB_BIA2DDR_LATENCY_REDUCE_SEL);
		for (i = 0; i < MAX_NOC; i++)
			noc_dev[i].noc_bypass = BYPASSED_NOC;
	}
}

void sprd_noc_init(void)
{
#ifdef CONFIG_DDR_DOUBLE_PUB
	/* DDR capacity config.
	  * It will be only used in none-interleave mode, but it needs not to judge
	  * which modes it used, because it is not effect interleave mode.
	  */
	sprd_ddr_capacity_ctrl(DDR_4G);
	/* BIA/AP NOC config */
	sprd_bia_noc_ctrl(REG_AON_APB_BIA_NOC_CTRL, MIXED_MODE);
	sprd_ap_noc_ctrl(REG_AON_APB_AP_NOC_CTRL, MIXED_MODE, SIZE_256);
	/* GPU NOC config */
	sprd_gpu_noc_ctrl(REG_AON_APB_GPU_NOC_CTRL, MIXED_MODE, SIZE_256);
	/* VSP/CAM NOC config */
	sprd_vsp_noc_ctrl(REG_AON_APB_VSP_NOC_CTRL, FULL_MODE, SIZE_256);
	sprd_cam_noc_ctrl(REG_AON_APB_CAM_NOC_CTRL, FULL_MODE, SIZE_256);
	/* DISP NOC has no swap sel and remap configuration, it is based on CAM NOC */
	sprd_dispc_noc_ctrl(REG_AON_APB_DISP_NOC_CTRL, FULL_MODE, SIZE_256);
	/* GSP NOC has no swap sel and remap configuration, it is based on VSP NOC */
	sprd_gsp_noc_ctrl(REG_AON_APB_GSP_NOC_CTRL, FULL_MODE);
	/* scan all the NOC(s), if there are none-interleave mode, bypass them */
	sprd_noc_chn_latency_config();
#else
	sprd_noc_signel_chn_init();
#endif
}

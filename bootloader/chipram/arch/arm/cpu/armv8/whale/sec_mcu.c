/******************************************************************************
    David.Jia   2007.10.29      share_version_union

******************************************************************************/

#include <common.h>
#include <sci_types.h>
/* delete  chip_drv_common_io_h */
#include <adi.h>
#include <asm/arch/sprd_reg.h>

static void ApbClkConfig()
{
#if 0
	uint32 apb_cfg, i;
	apb_cfg = REG32(0x20000020);
	apb_cfg &= ~3;
	/* ap apb select 64m */
	apb_cfg |= 1;
	REG32(0x20000020) = apb_cfg;

	apb_cfg = REG32(0x402d0230);
	apb_cfg &= ~7;
	/* aon apb select 96m */
	apb_cfg |= 3;
	REG32(0x402d0230) = apb_cfg;

	for (i = 0; i < 0x100; i++) {
	}
#endif
}

static void SetMPllClk(uint32 clk)
{
	/* do nothing now */
	return;
}

static void McuClkConfig(uint32 arm_clk)
{
#if 0
	uint32 lit_mcu_cfg, i;

	SetMPllClk(arm_clk);

	lit_mcu_cfg = REG32(0x40880020);
	lit_mcu_cfg &= ~7;
	/* select mpll as mcu source */
	lit_mcu_cfg |= 6;

	REG32(0x40880020) = lit_mcu_cfg;

	for (i=0; i<0x100; i++){}
#endif
}

void SecClkConfig()
{
#if 0
	uint32 clk_cfg, i;

	REG32(REG_AP_APB_APB_EB) |= BIT_AP_CKG_EB;

	/* RPLL enable */
	clk_cfg = REG32(0x402b016c);
	/* all subsystem select RPLL0/1 */
	clk_cfg |= (0xfc00fc);
	REG32(0x402b016c) = clk_cfg;
	for (i = 0; i < 1000000; i++) {
	}
#if 0
	/* twpll configure */
	clk_cfg = REG32(0x40400060);
	clk_cfg &= ~(0xe0000000);
	clk_cfg |= 0x40000000;
	REG32(0x40400060) = clk_cfg;

	/* ltepll configure */
	clk_cfg = REG32(0x40400064);
	clk_cfg &= ~(0x38000000);
	clk_cfg |= 0x10000000;
	REG32(0x40400064) = clk_cfg;

	clk_cfg = REG32(0x4040006c);
	clk_cfg &= ~(0x38000000);
	clk_cfg |= 0x28000000;
	REG32(0x4040006c) = clk_cfg;
	
	for (i = 0; i < 1000000; i++) {
	}
#endif
	/* ace dbg and atb clk configure */
	clk_cfg = REG32(0x40880020);
	clk_cfg &= ~(7 << 8 | 7 << 12 | 7 << 16);
	clk_cfg |= (1 << 8) | (3 << 12) | (3 << 16);
	REG32(0x40880020) = clk_cfg;
	for (i = 0; i < 1000; i++) {
	}

	/* lit mcu clock configure */
	McuClkConfig(CLK_1000M);

	/* apb clock configure */
	ApbClkConfig();
#endif
}


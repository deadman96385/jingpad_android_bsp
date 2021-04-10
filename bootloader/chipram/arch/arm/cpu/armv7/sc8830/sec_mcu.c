/******************************************************************************
    David.Jia   2007.10.29      share_version_union

******************************************************************************/

#include <common.h>
#include <sci_types.h>
/* delete  chip_drv_common_io_h */
#include <adi.h>
#include <asm/arch/sprd_reg.h>

static void AhbClkConfig()
{
    uint32 ahb_cfg, i;
    ahb_cfg  = REG32(REG_AP_CLK_AP_AHB_CFG);
    ahb_cfg &=~3;
    ahb_cfg |= 2;  //ahb select 128M           0:26M 1:76M 2:128M 3:192M
    REG32(REG_AP_CLK_AP_AHB_CFG) = ahb_cfg;

    ahb_cfg  = REG32(REG_AON_CLK_PUB_AHB_CFG);
    ahb_cfg &=~3;
    ahb_cfg |= 2;  //pub ahb select 128M      0:26M 1:76M 2:128M 3:153M
    REG32(REG_AON_CLK_PUB_AHB_CFG) = ahb_cfg;

    for (i=0; i<0x100; i++);
}

static void ApbClkConfig()
{
    uint32 apb_cfg, i;
    apb_cfg  = REG32(REG_AP_CLK_AP_APB_CFG);
    apb_cfg &=~3;
    apb_cfg |= 1;  //apb select 64M            0:26M 1:64M 2:96M 3:128M
    REG32(REG_AP_CLK_AP_APB_CFG) = apb_cfg;

    apb_cfg = REG32(REG_AON_CLK_AON_APB_CFG);
    apb_cfg &=~3;
    apb_cfg |= 1;  //aon apb select 76M        0:26M 1:76M 2:96M 3:128M
    REG32(REG_AON_CLK_AON_APB_CFG) = apb_cfg;

    for (i=0; i<0x100; i++);
}

static void SetMPllClk (uint32 clk)
{
    uint32 mpll_cfg, pll_sft_cnt, i;

    REG32(REG_AON_APB_PLL_SOFT_CNT_DONE) &= ~1;

    mpll_cfg  = REG32(REG_AON_APB_MPLL_CFG);
    mpll_cfg &=~(3<<24);
    mpll_cfg |= (1<<24);
    clk /= 4000000;
    mpll_cfg &=~(0x7ff);
    mpll_cfg |= clk&0x7ff;
    REG32(REG_AON_APB_MPLL_CFG) = mpll_cfg;

    for (i=0; i<0x1000; i++){}

    REG32(REG_AON_APB_PLL_SOFT_CNT_DONE) |=  1;
}

static void McuClkConfig(uint32 arm_clk)
{
    uint32 ca7_ckg_cfg, i;

    SetMPllClk(arm_clk);

    ca7_ckg_cfg  =  REG32(REG_AP_AHB_CA7_CKG_CFG);
    ca7_ckg_cfg &= ~(7<<4);  //ap clk div = 0;
    ca7_ckg_cfg &= ~7;
    ca7_ckg_cfg |=  6; //a7 core select mcu MPLL       0:26M 1:(DPLL)533M 2:(CPLL)624M 3:(TDPLL)768M 4:(WIFIPLL)880M 5:(WPLL)921M 6:(MPLL)1200M
    REG32(REG_AP_AHB_CA7_CKG_CFG) = ca7_ckg_cfg;

    for (i=0; i<0x100; i++){}
}

void SecClkConfig()
{
    uint32 ca7_ckg_cfg, i;
    REG32(REG_AP_APB_APB_EB) |= BIT_AP_CKG_EB;		// CKG enable
    //AxiClkConfig
    ca7_ckg_cfg  = REG32(REG_AP_AHB_CA7_CKG_CFG);
    ca7_ckg_cfg &= ~(7<<8);
    ca7_ckg_cfg |= 1<<8;							//AXI=ARM/2
    REG32(REG_AP_AHB_CA7_CKG_CFG) = ca7_ckg_cfg;
    for (i=0; i<0x100; i++){}

    //DbgClkConfig
    ca7_ckg_cfg  =  REG32(REG_AP_AHB_CA7_CKG_CFG);
    ca7_ckg_cfg &= ~(7<<16);
    ca7_ckg_cfg |=  3<<16;							//DBG=ARM/4
    REG32(REG_AP_AHB_CA7_CKG_CFG) = ca7_ckg_cfg;
    for (i=0; i<0x100; i++){}
    McuClkConfig(CLK_1000M);

    AhbClkConfig();
    ApbClkConfig();
}


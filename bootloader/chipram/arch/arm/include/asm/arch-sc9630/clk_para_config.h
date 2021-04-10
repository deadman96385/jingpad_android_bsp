/******************************************************************************
 ** File Name:                                                                *
 ** Author:                                                                   *
 ** DATE:                                                                     *
 ** Copyright:      2002 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic input and output operations   *
 **                 on hardware, it can be treated as a hardware abstract     *
 **                 layer interface.                                          *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 06/12/2010                                                                *
 ******************************************************************************/

#ifndef _CLK_PARA_CONFIG_H_
#define _CLK_PARA_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif

enum clk_ap_ahb_sel
{
    AHB_CLK_26M,
    AHB_CLK_76_8M,
    AHB_CLK_128M,
    AHB_CLK_192M
};
enum clk_ap_apb_sel
{
    APB_CLK_26M,
    APB_CLK_64M,
    APB_CLK_96M,
    APB_CLK_128M,
};
enum clk_pub_ahb_sel
{
    PUB_AHB_CLK_26M,
    PUB_AHB_CLK_4M,
    PUB_AHB_CLK_96M,
    PUB_AHB_CLK_128M,

};
#if defined(CONFIG_SCX35LT8) || defined(CONFIG_ARCH_SCX35L2) || defined(CONFIG_SOC_PIKE2)
enum clk_aon_apb_sel
{
    AON_APB_CLK_4M,
    AON_APB_CLK_26M,
    AON_APB_CLK_96M,
    AON_APB_CLK_128M,
};
#else
enum clk_aon_apb_sel
{
    AON_APB_CLK_4M,
    AON_APB_CLK_26M,
    AON_APB_CLK_76_8M,
    AON_APB_CLK_96M,
};
#endif

#if defined(CONFIG_ARCH_SCX35L2) || defined(CONFIG_SOC_PIKE2)
enum clk_ap_axi_sel
{
	AP_AXI_CLK_26M,
	AP_AXI_CLK_76_8M,
	AP_AXI_CLK_128M,
	AP_AXI_CLK_256M,
};
#endif
typedef struct{
    volatile unsigned int magic_header;
    volatile unsigned char version;
    volatile unsigned char reserved0;
    volatile unsigned char reserved1;
    volatile unsigned char reserved2;
    volatile unsigned int core_freq;
    volatile unsigned int ddr_freq;
    volatile unsigned int axi_freq;
    volatile unsigned int dgb_freq;
    volatile unsigned int ahb_freq;
    volatile unsigned int apb_freq;
    volatile unsigned int pub_ahb_freq;
    volatile unsigned int aon_apb_freq;
#if defined(CONFIG_ARCH_SCX35L2) || defined(CONFIG_SOC_PIKE2)
    volatile unsigned int ap_axi_freq;
#endif
    volatile unsigned int dcdc_arm;
    volatile unsigned int dcdc_core;
    volatile unsigned int dcdc_mem;
    volatile unsigned int dcdc_gen;
    volatile unsigned int debug_flags[4];
    volatile unsigned int magic_end;
}MCU_CLK_PARA_T;

extern const MCU_CLK_PARA_T mcu_clk_para;

#ifdef __cplusplus
}
#endif

#endif

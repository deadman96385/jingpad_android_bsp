#ifndef __ARCH_ARM_ASM_ORCA_SPI__
#define __ARCH_ARM_ASM_ORCA_SPI__

#include <common.h>
#include <asm/arch/sprd_reg.h>
#include <asm/io.h>

struct sprd_spi{
	void * spi_eb;
	unsigned apb_base_eb;
	unsigned spi_rst;
	unsigned apb_base_rst;
	unsigned spi_clk_base;
	void * spi_base;
};

#define SPRD_SPI_NUM		3

struct sprd_spi sprd_spi[SPRD_SPI_NUM] = {
	{
		.spi_eb = (void *)BIT_AP_APB_SPI0_EB,
		.apb_base_eb = REG_AP_APB_APB_EB,
		.spi_rst = BIT_AP_APB_SPI0_SOFT_RST,
		.apb_base_rst =REG_AP_APB_APB_RST,
		.spi_clk_base = REG_AON_CLK_CORE_CGM_AP_SPI0_CFG,
		.spi_base = (void *)SPRD_SPI_HS0_TOP_PHYS
	}, {
		.spi_eb = (void *)BIT_AP_APB_SPI1_EB,
		.apb_base_eb = REG_AP_APB_APB_EB,
		.spi_rst = BIT_AP_APB_SPI1_SOFT_RST,
		.apb_base_rst =REG_AP_APB_APB_RST,
		.spi_clk_base = REG_AON_CLK_CORE_CGM_AP_SPI1_CFG,
		.spi_base = (void *)SPRD_SPI_HS1_TOP_PHYS
	}, {
		.spi_eb = (void *)BIT_AP_APB_SPI2_EB,
		.apb_base_eb = REG_AP_APB_APB_EB,
		.spi_rst = BIT_AP_APB_SPI2_SOFT_RST,
		.apb_base_rst =REG_AP_APB_APB_RST,
		.spi_clk_base = REG_AON_CLK_CORE_CGM_AP_SPI2_CFG,
		.spi_base = (void *)SPRD_SPI_HS2_TOP_PHYS
	},
};

#endif /*__ARCH_ARM_ASM_ORCA_SPI__*/

#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sci_types.h>
#include "adi_hal_internal.h"
#include <asm/arch/common.h>
#include <sprd_pmic_misc.h>

/*
	REG_AON_APB_BOND_OPT0  ==> romcode set
	REG_AON_APB_BOND_OPT1  ==> set it later

	!!! notice: these two registers can be set only one time!!!

	B1[0] : B0[0]
	0     : 0     Jtag enable
	0     : 1     Jtag disable
	1     : 0     Jtag enable
	1     : 1     Jtag enable
*/

/*************************************************
* 1 : enable jtag success                        *
* 0 : enable jtag fail                           *
*************************************************/
int sprd_jtag_enable()
{
	if (*((volatile unsigned int *)(REG_AON_APB_BOND_OPT0)) & 1)
	{
		*((volatile unsigned int *)(REG_AON_APB_BOND_OPT1)) = 1;
		if (!((*(volatile unsigned int *)(REG_AON_APB_BOND_OPT1)) & 1))
			return 0;
	}
	return 1;
}

/*************************************************
* 1 : disable jtag success                       *
* 0 : disable jtag fail                          *
*************************************************/
int sprd_jtag_disable()
{
	if (!(*((volatile unsigned int *)(REG_AON_APB_BOND_OPT0)) & 1))
	{
		return 0;
	}
	else
	{
		*((volatile unsigned int *)(REG_AON_APB_BOND_OPT1)) = 0;
		if (*((volatile unsigned int *)(REG_AON_APB_BOND_OPT1)) & 1)
			return 0;
		else
			return 1;
	}
}

static void ap_slp_cp_dbg_cfg()
{
	*((volatile unsigned int *)(REG_AP_AHB_MCU_PAUSE)) |= BIT_MCU_SLEEP_FOLLOW_CA7_EN; //when ap sleep, cp can continue debug
}

static void bb_bg_auto_en()
{
	*((volatile unsigned int *)(REG_AON_APB_RES_REG0)) |= 1<<8;
}

static void bb_ldo_auto_en()
{
	*((volatile unsigned int *)(REG_AON_APB_RES_REG0)) |= 1<<9;
}


#ifdef CONFIG_OF_LIBFDT
void scx35_pmu_reconfig(void)
{
	/* FIXME:
	 * turn on gpu/mm domain for clock device initcall, and then turn off asap.
	 */
	__raw_writel(__raw_readl(REG_PMU_APB_PD_MM_TOP_CFG)
		     & ~(BIT_PD_MM_TOP_FORCE_SHUTDOWN),
		     REG_PMU_APB_PD_MM_TOP_CFG);
#ifndef CONFIG_FPGA
    while (__raw_readl(REG_PMU_APB_PWR_STATUS0_DBG) & 0xf0000000) {};
#endif
	__raw_writel(__raw_readl(REG_PMU_APB_PD_GPU_TOP_CFG)
		     & ~(BIT_PD_GPU_TOP_FORCE_SHUTDOWN),
		     REG_PMU_APB_PD_GPU_TOP_CFG);
#ifndef CONFIG_FPGA
    while (__raw_readl(REG_PMU_APB_PWR_STATUS0_DBG) & 0x0f000000) {};
#endif
	__raw_writel(__raw_readl(REG_AON_APB_APB_EB0) | BIT_MM_EB |
		     BIT_GPU_EB, REG_AON_APB_APB_EB0);
#ifndef CONFIG_FPGA
        __raw_writel(__raw_readl(REG_MM_AHB_RF_AHB_EB) | BIT_CKG_EB,
                     REG_MM_AHB_RF_AHB_EB);
        __raw_writel(__raw_readl(REG_MM_AHB_RF_GEN_CKG_CFG)
                     | BIT_MM_MTX_AXI_CKG_EN | BIT_MM_AXI_CKG_EN,
                     REG_MM_AHB_RF_GEN_CKG_CFG);
#endif

#ifndef CONFIG_FPGA
	__raw_writel(__raw_readl(REG_MM_CLK_MM_AHB_CFG) | 0x3,
		     REG_MM_CLK_MM_AHB_CFG);
#endif
}

#else
void scx35_pmu_reconfig(void) {}
#endif

static void sprd_get_chipid(void)
{
#ifndef CONFIG_SP9830I
	debugf("chip id = %x\n",__raw_readl((void *)REG_AON_APB_AON_CHIP_ID));
#else
	unsigned int chip_id0 = 0, chip_id1 = 0, i = 0;
	char *p;
	char chip_id_buf[9];
	chip_id0 = __raw_readl((void *)REG_AON_APB_AON_CHIP_ID_L);
	chip_id1 = __raw_readl((void *)REG_AON_APB_AON_CHIP_ID_H);
	p = (char *)&chip_id1;
	for(i = 0; i < 4; i++)
		chip_id_buf[i] = *(p+3-i);
	p = (char *)&chip_id0;
	for(i = 0; i < 4; i++)
		chip_id_buf[i+4] = *(p+3-i);
	chip_id_buf[8] = 0;
	debugf("chip id = %s\n",chip_id_buf);
#endif
}

void misc_init()
{
	scx35_pmu_reconfig();
	ap_slp_cp_dbg_cfg();

	bb_bg_auto_en();
	bb_ldo_auto_en();

	pmic_misc_init();

	sprd_get_chipid();
}

typedef struct mem_cs_info
{
	uint32 cs_number;
	uint32 cs0_size;//bytes
	uint32 cs1_size;//bytes
}mem_cs_info_t;
PUBLIC int get_dram_cs_number(void)
{
	mem_cs_info_t *cs_info_ptr = 0x1C00;
	return cs_info_ptr->cs_number;
}
PUBLIC int get_dram_cs0_size(void)
{
	mem_cs_info_t *cs_info_ptr = 0x1C00;
	return cs_info_ptr->cs0_size;
}
#ifdef DFS_ON_ARM7
PUBLIC int cp_dfs_param_for_arm7(void)
{
	memcpy(DFS_PARAM_TARGET_ADDR, DFS_PARAM_SRC_ADDR, DFS_PARAM_LEN);
	return 0;
}
#endif

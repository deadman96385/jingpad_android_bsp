#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include "adi_hal_internal.h"
#include <asm/arch/common.h>
#include "sprd_chipid.h"
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

}

#else
void scx35_pmu_reconfig(void) {}
#endif


static enum chip_type chiptype;
void sprd_get_chipid(void)
{
	unsigned int chip_id0 = 0, chip_id1 = 0;

	for(chiptype = 0;chiptype < CHIP_TYPE_MAX;chiptype ++){

		chip_id0 = __raw_readl((void *)REG_AON_APB_AON_CHIP_ID0);
		if(chipid[chiptype].chipid_1)
			chip_id1 = __raw_readl((void *)REG_AON_APB_AON_CHIP_ID1);

		if((chip_id0 == chipid[chiptype].chipid_0)
			&& (chip_id1 == chipid[chiptype].chipid_1)){
			chipid[chiptype].ver_id = __raw_readl((void *)REG_AON_APB_AON_VER_ID);
			debugf("chip id = %s\n",chipid[chiptype].name);
			break;
		}
	}
	if(chiptype == CHIP_TYPE_MAX)
		debugf("unknown chip\n");
}

uint32_t sprd_get_chipid_h(void)
{
	if(chiptype != CHIP_TYPE_MAX)
		return chipid[chiptype].chipid_1;
	else
		return 65535;
}

uint32_t sprd_get_chipid_l(void)
{
	if(chiptype != CHIP_TYPE_MAX)
		return chipid[chiptype].chipid_0;
	else
		return 65535;
}

uint32_t sprd_get_chip_version(void)
{
	if(chiptype != CHIP_TYPE_MAX)
		return chipid[chiptype].ver_id;
	else
		return 65535;
}

static void sc9833_disable_clkautogate()
{
	__raw_writel(__raw_readl(REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG)
		     & ~(BIT_AP_AHB_CA7_CORE_AUTO_GATE_EN),
		     REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG);
}

static void memory_repair_once()
{
	CHIP_REG_OR(REG_PMU_APB_BISR_FORCE_SEL,BIT_PMU_APB_PD_AON_MEM_BISR_FORCE_SEL);
}

void misc_init()
{
	int chipid_l,chipid_h,version_id;
	scx35_pmu_reconfig();
	sc9833_disable_clkautogate();

	bb_bg_auto_en();
	bb_ldo_auto_en();

	pmic_misc_init();
	memory_repair_once();

	sprd_get_chipid();
	chipid_l = sprd_get_chipid_l();
	chipid_h = sprd_get_chipid_h();
	version_id = sprd_get_chip_version();

	if ((chipid_l != 65535) && (chipid_h != 65535) && (version_id != 65535))
		debugf("chipid_l = 0x%x chipid_h = 0x%x version_id = 0x%x\n",chipid_l,chipid_h,version_id);
	else
		debugf("unknow chipid\n");
}

typedef struct mem_cs_info
{
	uint32_t cs_number;
	uint32_t cs0_size;//bytes
	uint32_t cs1_size;//bytes
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

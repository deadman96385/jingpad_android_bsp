#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include "adi_hal_internal.h"
#include <asm/arch/common.h>
#include <otp_helper.h>
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
//	*((volatile unsigned int *)(REG_AP_AHB_MCU_PAUSE)) |= BIT_MCU_SLEEP_FOLLOW_APCPU_EN; //when ap sleep, cp can continue debug
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
	REG32(REG_AON_APB_APB_EB0) |= BIT_AON_APB_GPU_EB;
	REG32(REG_AON_APB_APB_EB1) |= BIT_AON_APB_DISP_EB;
	REG32(REG_AON_APB_APB_EB1) |= BIT_AON_APB_CAM_EB;
	REG32(REG_AON_APB_APB_EB1) |= BIT_AON_APB_VSP_EB;
}

#else
void scx35_pmu_reconfig(void) {}
#endif

#define KLT8	0x6B4C5438
#define KL	0x6B4C0000
#define SHAR	0x53686172
#define E2	0x65320000
#define WHAL	0x5768616C

int sprd_get_chipid(int *chip_id, int *version_id)
{

	unsigned int chip_id0 = 0, chip_id1 = 0;
	int ch_id;
	int ver_id;

	chip_id0 = __raw_readl((void *)REG_AON_APB_AON_CHIP_ID0);
	chip_id1 = __raw_readl((void *)REG_AON_APB_AON_CHIP_ID1);

	switch (chip_id1) {
	case SHAR:
		switch (chip_id0) {
		case KL:
			ch_id = 0x9830;
			break;
		case KLT8:
			ch_id = 0x9838;
			break;
		default:
			ch_id = 0;
			break;
		}
		break;

	case WHAL:
		switch (chip_id0) {
		case E2:
			ch_id = 0x9850;
			break;
		default:
			ch_id = 0;
			break;
		}
		break;

	default:
		ch_id = 0;
		break;
	}

	ver_id = __raw_readl((void *)REG_AON_APB_AON_VER_ID);

	if (!chip_id || !version_id) {
		debugf("chip id = 0x%x, VID = 0x%x\n",ch_id, ver_id);
		return 0;
	}

	*chip_id = ch_id;
	*version_id = ver_id;

	return 0;
}

#if defined CONFIG_SMT

void set_smt(void)
{
	if(0x00 == CONFIG_SMT_VALUE){
		__raw_writel(__raw_readl(JVT_MT_CFG) & (~(0x3)),JVT_MT_CFG);/*open smt*/
	}else if(0x01 == CONFIG_SMT_VALUE){
		__raw_writel(__raw_readl(JVT_MT_CFG) | 0x3,JVT_MT_CFG);/*close smt*/
	}else if(0x10 == CONFIG_SMT_VALUE){
		/*get config info from mmc*/
	}
}

#endif

void misc_init()
{
	scx35_pmu_reconfig();
	ap_slp_cp_dbg_cfg();

	bb_bg_auto_en();
	bb_ldo_auto_en();

	pmic_misc_init();

	sprd_get_chipid(NULL, NULL);
	sprd_uid_bin_info();

#if defined CONFIG_SMT
	set_smt();
#endif
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



#ifndef _SPRD_REG_H_
#define _SPRD_REG_H_

#ifndef BIT
#define BIT(x) (1<<(x))
#endif

#include <config.h>
#include "hardware.h"
#include "sprd_module_config.h"
#include <power/sprd_pmic/pmic_glb_reg.h>

#if defined(CONFIG_ARCH_SCX35L2)
	#include "chip_x35l2/__regs_ap_apb.h"
	#include "chip_x35l2/__regs_serdes_apb.h"
	#include "chip_x35l2/__regs_ap_ahb.h"
	#include "chip_x35l2/__regs_ap_clk.h"
	#include "chip_x35l2/__regs_mm_ahb_rf.h"
	#include "chip_x35l2/__regs_mm_clk.h"
	#include "chip_x35l2/__regs_gpu_apb.h"
	#include "chip_x35l2/__regs_aon_apb.h"
	#include "chip_x35l2/__regs_aon_clk.h"
	#include "chip_x35l2/__regs_aon_sec_apb.h"
	#include "chip_x35l2/__regs_ana_apb_rf.h"
	#include "chip_x35l2/__regs_pmu_apb.h"
	#include "chip_x35l2/__regs_pub_ahb.h"
	#include "chip_x35l2/__regs_pub_cp_ahb.h"
	#include "chip_x35l2/__regs_pub_cp_apb.h"
	#include "chip_x35l2/__regs_arm7_ahb.h"
	#include "chip_x35l2/__regs_anlg_phy_g1.h"
	#include "chip_x35l2/__regs_anlg_phy_g2.h"
	#include "chip_x35l2/__regs_anlg_phy_g3.h"
	#include "chip_x35l2/__regs_anlg_phy_g5.h"
#endif

#endif

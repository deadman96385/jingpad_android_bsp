
#ifndef _SPRD_REG_H_
#define _SPRD_REG_H_

#ifndef BIT
#define BIT(x) (1<<(x))
#endif

#include <config.h>
#include "hardware.h"
#include "sci_types.h"
#include "sprd_module_config.h"
#include <power/sprd_pmic/pmic_glb_reg.h>

#if defined(CONFIG_ARCH_SCX35L)
	#if defined CONFIG_ARCH_SCX20L

		#include "chip_x20l/__regs_ap_apb.h"
		#include "chip_x20l/__regs_ap_ahb_rf.h"
		#include "chip_x20l/__regs_ap_clk.h"
		#include "chip_x20l/__regs_mm_ahb_rf.h"
		#include "chip_x20l/__regs_mm_clk.h"
		#include "chip_x20l/__regs_gpu_apb_rf.h"
		#include "chip_x20l/__regs_gpu_clk.h"
		#include "chip_x20l/__regs_aon_apb_rf.h"
		#include "chip_x20l/__regs_ana_apb_if.h"
		#include "chip_x20l/__regs_aon_ckg.h"
		#include "chip_x20l/__regs_aon_clk.h"
		#include "chip_x20l/__regs_pmu_apb_rf.h"
		#include "chip_x20l/__regs_pub_apb.h"
	#else
		#include "chip_x35l/__regs_ap_apb.h"
		#include "chip_x35l/__regs_ap_ahb_rf.h"
		#include "chip_x35l/__regs_ap_clk.h"
		#include "chip_x35l/__regs_mm_ahb_rf.h"
		#include "chip_x35l/__regs_mm_clk.h"
		#include "chip_x35l/__regs_gpu_apb_rf.h"
		#include "chip_x35l/__regs_gpu_clk.h"
		#include "chip_x35l/__regs_aon_apb_rf.h"
		#include "chip_x35l/__regs_aon_ckg.h"
		#include "chip_x35l/__regs_aon_clk.h"
		#include "chip_x35l/__regs_pmu_apb_rf.h"
		#include "chip_x35l/__regs_pub_apb.h"
	#endif
#endif

#endif



#ifndef _SPRD_REG_H_
#define _SPRD_REG_H_

#ifndef BIT
#define BIT(x) (1<<x)
#endif

#include <config.h>
#include "hardware.h"
#include "sprd_module_config.h"
#include <power/sprd_pmic/pmic_glb_reg.h>

#if defined(CONFIG_TARGET_SP9861_VP) || defined(CONFIG_TARGET_SP9861) || defined(CONFIG_TARGET_SP9861E_1H10) || defined(CONFIG_TARGET_SP9861E_2H10) || defined(CONFIG_TARGET_SP9861E_2H10_2705) || defined(CONFIG_TARGET_SP9861E_1H11) || defined(CONFIG_TARGET_SP9861E_3H10)
#include "chip_iwhale2/__regs_ana_apb.h"
#include "chip_iwhale2/__regs_ap_apb.h"
#include "chip_iwhale2/__regs_aon_apb.h"
#include "chip_iwhale2/__regs_aon_clk.h"
#include "chip_iwhale2/__regs_aon_dbg_apb.h"
#include "chip_iwhale2/__regs_aon_lpc_apb.h"
#include "chip_iwhale2/__regs_aon_sec_apb.h"
#include "chip_iwhale2/__regs_ap_ahb.h"
#include "chip_iwhale2/__regs_ap_clk.h"
#include "chip_iwhale2/__regs_cam_sys_ahb.h"
#include "chip_iwhale2/__regs_disp_sys_ahb.h"
#include "chip_iwhale2/__regs_gpu_apb.h"
#include "chip_iwhale2/__regs_pmu_apb.h"
#include "chip_iwhale2/__regs_pub0_apb.h"
#include "chip_iwhale2/__regs_pub1_apb.h"
#include "chip_iwhale2/__regs_vsp_sys_ahb.h"
#include "chip_iwhale2/__regs_anlg_phy_g10.h"
#include "chip_iwhale2/__regs_anlg_phy_g12.h"
#include "chip_iwhale2/__regs_anlg_phy_g2.h"
#include "chip_iwhale2/__regs_anlg_phy_g4.h"
#include "chip_iwhale2/__regs_anlg_phy_g6.h"
#include "chip_iwhale2/__regs_anlg_phy_g8.h"
#include "chip_iwhale2/__regs_com_pmu_apb.h"
#include "chip_iwhale2/__regs_common_apb.h"
#include "chip_iwhale2/__regs_baseia_dvfs.h"
#include "chip_iwhale2/__regs_cam_clk.h"
#include "chip_iwhale2/__regs_dmc_bist_apb.h"
#include "chip_iwhale2/__regs_gpu_clk.h"
#include "chip_iwhale2/__regs_serdes_apb.h"
#include "chip_iwhale2/__regs_voltage0_map_apb.h"
#include "chip_iwhale2/__regs_voltage1_map_apb.h"
#include "chip_iwhale2/__regs_vsp_clk.h"

#else

#include "chip_isharkl2/__regs_anlg_phy_g10.h"
#include "chip_isharkl2/__regs_anlg_phy_g12.h"
#include "chip_isharkl2/__regs_anlg_phy_g2.h"
#include "chip_isharkl2/__regs_anlg_phy_g4.h"
#include "chip_isharkl2/__regs_anlg_phy_g6.h"
#include "chip_isharkl2/__regs_anlg_phy_g8.h"
#include "chip_isharkl2/__regs_aon_apb.h"
#include "chip_isharkl2/__regs_aon_clk.h"
#include "chip_isharkl2/__regs_aon_dbg_apb.h"
#include "chip_isharkl2/__regs_aon_lpc_apb.h"
#include "chip_isharkl2/__regs_aon_sec_apb.h"
#include "chip_isharkl2/__regs_ap_apb.h"
#include "chip_isharkl2/__regs_ap_ahb.h"
#include "chip_isharkl2/__regs_ap_clk.h"
#include "chip_isharkl2/__regs_baseia_dvfs.h"
#include "chip_isharkl2/__regs_cam_sys_ahb.h"
#include "chip_isharkl2/__regs_cam_clk.h"
#include "chip_isharkl2/__regs_common_apb.h"
#include "chip_isharkl2/__regs_com_pmu_apb.h"
#include "chip_isharkl2/__regs_disp_sys_ahb.h"
#include "chip_isharkl2/__regs_gpu_apb.h"
#include "chip_isharkl2/__regs_pmu_apb.h"
#include "chip_isharkl2/__regs_pub0_apb.h"
#include "chip_isharkl2/__regs_pre_div_clk_gen.h"
#include "chip_isharkl2/__regs_serdes_apb.h"
#include "chip_isharkl2/__regs_vsp_clk.h"
#include "chip_isharkl2/__regs_vsp_sys_ahb.h"

#endif
#endif


#ifndef _WHALE_REG_DEF_H_
#define _WHALE_REG_DEF_H_

#ifndef BIT
#define BIT(x) (1<<x)
#endif

#include <config.h>
#include "hardware.h"
#include <power/pmic_glb_reg.h>
#if defined CONFIG_WHALE
#include "chip_whale/__regs_ana_apb.h"
#include "chip_whale/__regs_aon_apb.h"
#include "chip_whale/__regs_aon_dbg_apb.h"
#include "chip_whale/__regs_aon_sec_apb.h"
#include "chip_whale/__regs_ap_ahb.h"
#include "chip_whale/__regs_ap_apb.h"
#include "chip_whale/__regs_pmu_apb.h"
#include "chip_whale/__regs_pub0_apb.h"
#include "chip_whale/__regs_pub1_apb.h"
#include "chip_whale/__regs_ana_efuse.h"
#elif defined(CONFIG_WHALE2)
#include "chip_whale2/__regs_ana_apb.h"
#include "chip_whale2/__regs_aon_apb.h"
#include "chip_whale2/__regs_aon_dbg_apb.h"
#include "chip_whale2/__regs_aon_sec_apb.h"
#include "chip_whale2/__regs_ap_ahb.h"
#include "chip_whale2/__regs_ap_apb.h"
#include "chip_whale2/__regs_pmu_apb.h"
#include "chip_whale2/__regs_pub0_apb.h"
#include "chip_whale2/__regs_pub1_apb.h"
#include "chip_whale2/__regs_ana_efuse.h"
#endif

#endif /*_WHALE_REG_DEF_H_*/



#ifndef _SC8830_REG_DEF_H_
#define _SC8830_REG_DEF_H_

#ifndef BIT
#define BIT(x) (1<<x)
#endif



#include "hardware.h"
#include <power/pmic_glb_reg.h>
#if defined CONFIG_SPX15
#include "chip_x15/__regs_ap_apb.h"
#include "chip_x15/__regs_ap_ahb.h"
#include "chip_x15/__regs_ap_clk.h"
#include "chip_x15/__regs_mm_ahb_rf.h"
#include "chip_x15/__regs_mm_clk.h"
#include "chip_x15/__regs_gpu_apb.h"
#include "chip_x15/__regs_gpu_clk.h"
#include "chip_x15/__regs_aon_apb.h"
#include "chip_x15/__regs_aon_ckg.h"
#include "chip_x15/__regs_aon_clk.h"
#include "chip_x15/__regs_pmu_apb.h"
#include "chip_x15/__regs_pub_apb.h"
#elif defined(CONFIG_SPX30G)
	#if defined(CONFIG_SPX20)
		#include "chip_x20/__regs_ap_apb.h"
		#include "chip_x20/__regs_ap_ahb.h"
		#include "chip_x20/__regs_ap_clk.h"
		#include "chip_x20/__regs_mm_ahb_rf.h"
		#include "chip_x20/__regs_mm_clk.h"
		#include "chip_x20/__regs_gpu_apb_rf.h"
		#include "chip_x20/__regs_gpu_clk.h"
		#include "chip_x20/__regs_aon_apb.h"
		#include "chip_x20/__regs_aon_ckg.h"
		#include "chip_x20/__regs_aon_clk.h"
		#include "chip_x20/__regs_pmu_apb.h"
		#include "chip_x20/__regs_pub_apb.h"
		#include "chip_x20/__regs_mdar.h"
	#else
		#if defined(CONFIG_SPX30G2)
                    #if defined(CONFIG_SPX30G3)
                          #include "chip_x30g/__regs_aon_apb_tshark3.h"
                          #include "chip_x30g/__regs_pmu_apb_tshark3.h"
                        #else
		          #include "chip_x30g/__regs_aon_apb_tshark2.h"
		          #include "chip_x30g/__regs_pmu_apb_tshark2.h"
                    #endif
                #include "chip_x30g/__regs_mm_ahb_rf_tshark2.h"
		#else
		#include "chip_x30g/__regs_mm_ahb_rf.h"
		#include "chip_x30g/__regs_aon_apb.h"
		#include "chip_x30g/__regs_pmu_apb.h"
		#endif

		#include "chip_x30g/__regs_ap_apb.h"
		#include "chip_x30g/__regs_ap_ahb.h"
		#include "chip_x30g/__regs_ap_clk.h"
		#include "chip_x30g/__regs_mm_clk.h"
		#include "chip_x30g/__regs_gpu_apb_rf.h"
		#include "chip_x30g/__regs_gpu_clk.h"
		#include "chip_x30g/__regs_aon_ckg.h"
		#include "chip_x30g/__regs_aon_clk.h"
		#include "chip_x30g/__regs_pub_apb.h"
	#endif
#else 
#include "chip_x35/sprd_reg_ap_apb.h"
#include "chip_x35/sprd_reg_ap_ahb.h"
#include "chip_x35/sprd_reg_ap_clk.h"
#include "chip_x35/sprd_reg_mm_ahb.h"
#include "chip_x35/sprd_reg_mm_clk.h"
#include "chip_x35/sprd_reg_gpu_apb.h"
#include "chip_x35/sprd_reg_gpu_clk.h"
#include "chip_x35/sprd_reg_aon_apb.h"
#include "chip_x35/sprd_reg_aon_ckg.h"
#include "chip_x35/sprd_reg_aon_clk.h"
#include "chip_x35/sprd_reg_pmu_apb.h"
#include "chip_x35/sprd_reg_pub_apb.h"
#endif
#endif


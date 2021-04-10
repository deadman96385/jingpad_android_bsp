/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-11-07 10:41:46
 *
 */


#ifndef GPU_APB_H
#define GPU_APB_H

#define CTL_BASE_GPU_APB 0x60100000


#define REG_GPU_APB_APB_RST             ( CTL_BASE_GPU_APB + 0x0000 )
#define REG_GPU_APB_CLK_GPU_CORE        ( CTL_BASE_GPU_APB + 0x0004 )
#define REG_GPU_APB_CLK_GPU_MEM         ( CTL_BASE_GPU_APB + 0x0008 )
#define REG_GPU_APB_CLK_GPU_SYS         ( CTL_BASE_GPU_APB + 0x000C )
#define REG_GPU_APB_GPU_NIC400_QOS      ( CTL_BASE_GPU_APB + 0x0010 )
#define REG_GPU_APB_LPC_AB_W            ( CTL_BASE_GPU_APB + 0x0014 )
#define REG_GPU_APB_LPC_M0              ( CTL_BASE_GPU_APB + 0x0018 )
#define REG_GPU_APB_LPC_S0              ( CTL_BASE_GPU_APB + 0x001C )
#define REG_GPU_APB_LPC_S1              ( CTL_BASE_GPU_APB + 0x0020 )
#define REG_GPU_APB_ASYBC_BRIDGE_TOP_W  ( CTL_BASE_GPU_APB + 0x0024 )

/* REG_GPU_APB_APB_RST */

#define BIT_GPU_APB_SYS_SOFT_RST_REQ_CORE       BIT(1)
#define BIT_GPU_APB_GPU_CORE_SOFT_RST           BIT(0)

/* REG_GPU_APB_CLK_GPU_CORE */

#define BIT_GPU_APB_CGM_GPU_CORE_FDIV_DENOM(x)  (((x) & 0xF) << 20)
#define BIT_GPU_APB_CGM_GPU_CORE_FDIV_NUM(x)    (((x) & 0xF) << 16)
#define BIT_GPU_APB_CGM_GPU_CORE_DIV(x)         (((x) & 0x7) << 8)
#define BIT_GPU_APB_CGM_GPU_CORE_SEL(x)         (((x) & 0x7) << 4)
#define BIT_GPU_APB_CGM_GPU_CORE_EB             BIT(0)

/* REG_GPU_APB_CLK_GPU_MEM */

#define BIT_GPU_APB_CGM_GPU_MEM_FDIV_DENOM(x)   (((x) & 0xF) << 20)
#define BIT_GPU_APB_CGM_GPU_MEM_FDIV_NUM(x)     (((x) & 0xF) << 16)
#define BIT_GPU_APB_CGM_GPU_MEM_DIV(x)          (((x) & 0x7) << 8)
#define BIT_GPU_APB_CGM_GPU_MEM_SEL(x)          (((x) & 0x7) << 4)
#define BIT_GPU_APB_CGM_GPU_MEM_EB              BIT(0)

/* REG_GPU_APB_CLK_GPU_SYS */

#define BIT_GPU_APB_CGM_GPU_SYS_DIV(x)          (((x) & 0x7) << 4)
#define BIT_GPU_APB_CGM_GPU_SYS_EB              BIT(0)

/* REG_GPU_APB_GPU_NIC400_QOS */

#define BIT_GPU_APB_GPU_QOS_SEL                 BIT(16)
#define BIT_GPU_APB_AWQOS_THRESHOLD_GPU(x)      (((x) & 0xF) << 12)
#define BIT_GPU_APB_ARQOS_THRESHOLD_GPU(x)      (((x) & 0xF) << 8)
#define BIT_GPU_APB_AWQOS_GPU(x)                (((x) & 0xF) << 4)
#define BIT_GPU_APB_ARQOS_GPU(x)                (((x) & 0xF))

/* REG_GPU_APB_LPC_AB_W */

#define BIT_GPU_APB_PU_NUM_AB_W(x)              (((x) & 0xFF) << 24)
#define BIT_GPU_APB_AXI_LP_CTRL_DISABLE         BIT(20)
#define BIT_GPU_APB_LP_EB_AB_W                  BIT(16)
#define BIT_GPU_APB_LP_NUM_AB_W(x)              (((x) & 0xFFFF))

/* REG_GPU_APB_LPC_M0 */

#define BIT_GPU_APB_PU_NUM_M0(x)                (((x) & 0xFF) << 24)
#define BIT_GPU_APB_LP_EB_M0                    BIT(16)
#define BIT_GPU_APB_LP_NUM_M0(x)                (((x) & 0xFFFF))

/* REG_GPU_APB_LPC_S0 */

#define BIT_GPU_APB_PU_NUM_S0(x)                (((x) & 0xFF) << 24)
#define BIT_GPU_APB_LP_EB_S0                    BIT(16)
#define BIT_GPU_APB_LP_NUM_S0(x)                (((x) & 0xFFFF))

/* REG_GPU_APB_LPC_S1 */

#define BIT_GPU_APB_PU_NUM_S1(x)                (((x) & 0xFF) << 24)
#define BIT_GPU_APB_LP_EB_S1                    BIT(16)
#define BIT_GPU_APB_LP_NUM_S1(x)                (((x) & 0xFFFF))

/* REG_GPU_APB_ASYBC_BRIDGE_TOP_W */

#define BIT_GPU_APB_RST_SUBSYS                  BIT(2)
#define BIT_GPU_APB_BRIDGE_TRANS_IDLE           BIT(1)
#define BIT_GPU_APB_AXI_DETECTOR_OVERFLOW       BIT(0)


#endif /* GPU_APB_H */



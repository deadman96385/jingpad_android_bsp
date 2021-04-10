/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-27 15:24:15
 *
 */


#ifndef PUB_AHB_WRAP_H
#define PUB_AHB_WRAP_H

#define CTL_BASE_PUB_AHB_WRAP 0x300F0000


#define REG_PUB_AHB_WRAP_PUB_AXI_QOS_REG_BK    ( CTL_BASE_PUB_AHB_WRAP + 0x0000 )
#define REG_PUB_AHB_WRAP_DFS_STATUS            ( CTL_BASE_PUB_AHB_WRAP + 0x0004 )
#define REG_PUB_AHB_WRAP_DFS_SW_CTRL           ( CTL_BASE_PUB_AHB_WRAP + 0x0008 )
#define REG_PUB_AHB_WRAP_RESERVED1             ( CTL_BASE_PUB_AHB_WRAP + 0x000C )
#define REG_PUB_AHB_WRAP_PUB_LP_GEN_CTRL       ( CTL_BASE_PUB_AHB_WRAP + 0x0010 )
#define REG_PUB_AHB_WRAP_RESERVED3             ( CTL_BASE_PUB_AHB_WRAP + 0x0014 )
#define REG_PUB_AHB_WRAP_DFS_PURE_SW_CTRL      ( CTL_BASE_PUB_AHB_WRAP + 0x0018 )
#define REG_PUB_AHB_WRAP_MEM_FW_INT            ( CTL_BASE_PUB_AHB_WRAP + 0x001C )
#define REG_PUB_AHB_WRAP_AXI_LPC_CTRL_0        ( CTL_BASE_PUB_AHB_WRAP + 0x0020 )
#define REG_PUB_AHB_WRAP_AXI_LPC_CTRL_1        ( CTL_BASE_PUB_AHB_WRAP + 0x0024 )
#define REG_PUB_AHB_WRAP_FENCING_CTRL          ( CTL_BASE_PUB_AHB_WRAP + 0x0028 )
#define REG_PUB_AHB_WRAP_WIFI_DFS_CTRL         ( CTL_BASE_PUB_AHB_WRAP + 0x002C )
#define REG_PUB_AHB_WRAP_DFS_SW_CTRL1          ( CTL_BASE_PUB_AHB_WRAP + 0x0030 )
#define REG_PUB_AHB_WRAP_DFS_SW_CTRL2          ( CTL_BASE_PUB_AHB_WRAP + 0x0034 )
#define REG_PUB_AHB_WRAP_DFS_SW_CTRL3          ( CTL_BASE_PUB_AHB_WRAP + 0x0038 )
#define REG_PUB_AHB_WRAP_PUB_DMC_MPU_INT       ( CTL_BASE_PUB_AHB_WRAP + 0x0040 )
#define REG_PUB_AHB_WRAP_DFS_INT_CTRL          ( CTL_BASE_PUB_AHB_WRAP + 0x0044 )
#define REG_PUB_AHB_WRAP_BASE_ADDR             ( CTL_BASE_PUB_AHB_WRAP + 0x0048 )
#define REG_PUB_AHB_WRAP_BIST_CTRL             ( CTL_BASE_PUB_AHB_WRAP + 0x004C )
#define REG_PUB_AHB_WRAP_BIST_CTRL_STATUS      ( CTL_BASE_PUB_AHB_WRAP + 0x0050 )
#define REG_PUB_AHB_WRAP_BUSMON_CLK_EN         ( CTL_BASE_PUB_AHB_WRAP + 0x0054 )
#define REG_PUB_AHB_WRAP_PUB_PERI_CLK_EN       ( CTL_BASE_PUB_AHB_WRAP + 0x0058 )
#define REG_PUB_AHB_WRAP_PUB_AXI_QOS_REG_1     ( CTL_BASE_PUB_AHB_WRAP + 0x005C )
#define REG_PUB_AHB_WRAP_RESERVED4             ( CTL_BASE_PUB_AHB_WRAP + 0x0060 )
#define REG_PUB_AHB_WRAP_DFS_HW_CTRL           ( CTL_BASE_PUB_AHB_WRAP + 0x0100 )
#define REG_PUB_AHB_WRAP_DFS_HW_CTRL1          ( CTL_BASE_PUB_AHB_WRAP + 0x0104 )
#define REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET0     ( CTL_BASE_PUB_AHB_WRAP + 0x0108 )
#define REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET1     ( CTL_BASE_PUB_AHB_WRAP + 0x010C )
#define REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET2     ( CTL_BASE_PUB_AHB_WRAP + 0x0110 )
#define REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET3     ( CTL_BASE_PUB_AHB_WRAP + 0x0114 )
#define REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET4     ( CTL_BASE_PUB_AHB_WRAP + 0x0118 )
#define REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET5     ( CTL_BASE_PUB_AHB_WRAP + 0x011C )
#define REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET6     ( CTL_BASE_PUB_AHB_WRAP + 0x0120 )
#define REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET7     ( CTL_BASE_PUB_AHB_WRAP + 0x0124 )
#define REG_PUB_AHB_WRAP_DFS_HW_CTRL2          ( CTL_BASE_PUB_AHB_WRAP + 0x0130 )

/* REG_PUB_AHB_WRAP_PUB_AXI_QOS_REG_BK */


/* REG_PUB_AHB_WRAP_DFS_STATUS */

#define BIT_PUB_AHB_WRAP_DFS_HW_MIN_FREQ_UP_FORCE_TRIG_ACK      BIT(30)
#define BIT_PUB_AHB_WRAP_DFS_USED_PLL(x)                        (((x) & 0x7) << 27)
#define BIT_PUB_AHB_WRAP_DFS_FC_SEL(x)                          (((x) & 0x7) << 24)
#define BIT_PUB_AHB_WRAP_SRC_AVAIL_PLL(x)                       (((x) & 0x7) << 21)
#define BIT_PUB_AHB_WRAP_DFS_URGENT_WAIT_TIMEOUT_FLAG           BIT(20)
#define BIT_PUB_AHB_WRAP_DFS_GIVEUP_INT_RAW                     BIT(19)
#define BIT_PUB_AHB_WRAP_INT_DFS_GIVEUP                         BIT(18)
#define BIT_PUB_AHB_WRAP_DFS_DENY_INT_RAW                       BIT(17)
#define BIT_PUB_AHB_WRAP_INT_DFS_DENY                           BIT(16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_LOCK                           BIT(15)
#define BIT_PUB_AHB_WRAP_DFS_LOCK_ACK                           BIT(14)
#define BIT_PUB_AHB_WRAP_HW_DFS_FSM_STATE(x)                    (((x) & 0x1F) << 8)
#define BIT_PUB_AHB_WRAP_HW_DFS_FSM_IDLE                        BIT(6)
#define BIT_PUB_AHB_WRAP_DFS_ERROR_INT_RAW                      BIT(5)
#define BIT_PUB_AHB_WRAP_INT_DFS_ERROR                          BIT(4)
#define BIT_PUB_AHB_WRAP_DFS_COMPLETE_INT_RAW                   BIT(3)
#define BIT_PUB_AHB_WRAP_INT_DFS_COMPLETE                       BIT(2)
#define BIT_PUB_AHB_WRAP_HW_DFS_EXIT_INT_RAW                    BIT(1)
#define BIT_PUB_AHB_WRAP_INT_HW_DFS_EXIT                        BIT(0)

/* REG_PUB_AHB_WRAP_DFS_SW_CTRL */

#define BIT_PUB_AHB_WRAP_PUB_DFS_SWITCH_TYPE                    BIT(31)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_SWITCH_PERIOD(x)            (((x) & 0xFF) << 22)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_RATIO_DEFAULT(x)            (((x) & 0x7F) << 15)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_RATIO(x)                    (((x) & 0x7F) << 8)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_DENY                        BIT(7)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_FRQ_SEL(x)                  (((x) & 0x7) << 4)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_RESP                        BIT(3)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_ACK                         BIT(2)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_REQ                         BIT(1)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_ENABLE                      BIT(0)

/* REG_PUB_AHB_WRAP_RESERVED1 */


/* REG_PUB_AHB_WRAP_PUB_LP_GEN_CTRL */

#define BIT_PUB_AHB_WRAP_HW_DFS_STOP_ENABLE                     BIT(5)
#define BIT_PUB_AHB_WRAP_HW_DFS_RESTART_ENABLE                  BIT(4)

/* REG_PUB_AHB_WRAP_RESERVED3 */


/* REG_PUB_AHB_WRAP_DFS_PURE_SW_CTRL */

#define BIT_PUB_AHB_WRAP_EMC_CKG_MODE_PURE_SW(x)                (((x) & 0x3) << 24)
#define BIT_PUB_AHB_WRAP_EMC_CKG_D2_SEL_PURE_SW(x)              (((x) & 0xF) << 20)
#define BIT_PUB_AHB_WRAP_PURE_SW_DFS_CLK_MODE(x)                (((x) & 0x3) << 18)
#define BIT_PUB_AHB_WRAP_PURE_SW_DFS_DENY                       BIT(16)
#define BIT_PUB_AHB_WRAP_PURE_SW_DFS_ACK                        BIT(15)
#define BIT_PUB_AHB_WRAP_PURE_SW_DFS_RESP                       BIT(14)
#define BIT_PUB_AHB_WRAP_PURE_SW_DFS_FC_REQ                     BIT(13)
#define BIT_PUB_AHB_WRAP_PURE_SW_DFS_REQ                        BIT(12)
#define BIT_PUB_AHB_WRAP_PURE_SW_DFS_FC_ACK                     BIT(11)
#define BIT_PUB_AHB_WRAP_PURE_SW_DFS_FRQ_SEL(x)                 (((x) & 0x7) << 8)
#define BIT_PUB_AHB_WRAP_EMC_CKG_SEL_PURE_SW(x)                 (((x) & 0x7F) << 1)
#define BIT_PUB_AHB_WRAP_DFS_SW_DFS_MODE                        BIT(0)

/* REG_PUB_AHB_WRAP_MEM_FW_INT */

#define BIT_PUB_AHB_WRAP_MEM_FW_INT_RAW                         BIT(3)
#define BIT_PUB_AHB_WRAP_INT_MEM_FW                             BIT(2)
#define BIT_PUB_AHB_WRAP_MEM_FW_INT_CLR                         BIT(1)
#define BIT_PUB_AHB_WRAP_MEM_FW_INT_EN                          BIT(0)

/* REG_PUB_AHB_WRAP_AXI_LPC_CTRL_0 */

#define BIT_PUB_AHB_WRAP_LP_FORCE_AON_WCN_ETR_S0                BIT(13)
#define BIT_PUB_AHB_WRAP_LP_EB_AON_WCN_ETR_S0                   BIT(12)
#define BIT_PUB_AHB_WRAP_LP_FORCE_AON_WCN_ETR_M2                BIT(11)
#define BIT_PUB_AHB_WRAP_LP_EB_AON_WCN_ETR_M2                   BIT(10)
#define BIT_PUB_AHB_WRAP_LP_FORCE_AON_WCN_ETR_M1                BIT(9)
#define BIT_PUB_AHB_WRAP_LP_EB_AON_WCN_ETR_M1                   BIT(8)
#define BIT_PUB_AHB_WRAP_LP_FORCE_AON_WCN_ETR_M0                BIT(7)
#define BIT_PUB_AHB_WRAP_LP_EB_AON_WCN_ETR_M0                   BIT(6)
#define BIT_PUB_AHB_WRAP_LP_FORCE_CP_S0                         BIT(5)
#define BIT_PUB_AHB_WRAP_LP_EB_CP_S0                            BIT(4)
#define BIT_PUB_AHB_WRAP_LP_FORCE_CP_M1                         BIT(3)
#define BIT_PUB_AHB_WRAP_LP_EB_CP_M1                            BIT(2)
#define BIT_PUB_AHB_WRAP_LP_FORCE_CP_M0                         BIT(1)
#define BIT_PUB_AHB_WRAP_LP_EB_CP_M0                            BIT(0)

/* REG_PUB_AHB_WRAP_AXI_LPC_CTRL_1 */

#define BIT_PUB_AHB_WRAP_LP_NUM(x)                              (((x) & 0xFFFF))

/* REG_PUB_AHB_WRAP_FENCING_CTRL */

#define BIT_PUB_AHB_WRAP_DDR_FENCING_EN                         BIT(30)
#define BIT_PUB_AHB_WRAP_FENCING_CHNL_IDLE_CNT(x)               (((x) & 0x3FFFFFFF))

/* REG_PUB_AHB_WRAP_WIFI_DFS_CTRL */

#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_LOCK_REQ                    BIT(29)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_LOCK_MODE                   BIT(28)
#define BIT_PUB_AHB_WRAP_WIFI_DFS_TIMEOUT_FLAG                  BIT(25)
#define BIT_PUB_AHB_WRAP_WIFI_DFS_ACK                           BIT(24)
#define BIT_PUB_AHB_WRAP_WIFI_DFS_URGENCY_CTRL_EN(x)            (((x) & 0x3) << 22)
#define BIT_PUB_AHB_WRAP_WIFI_FIFO_URGENCY_CTRL_EN(x)           (((x) & 0x3) << 20)
#define BIT_PUB_AHB_WRAP_WIFI_DFS_SW_REQ                        BIT(19)
#define BIT_PUB_AHB_WRAP_WIFI_DFS_MODE                          BIT(18)
#define BIT_PUB_AHB_WRAP_WIFI_DFS_TIMEOUT_EN                    BIT(17)
#define BIT_PUB_AHB_WRAP_WIFI_DFS_TIMEOUT_PERIOD(x)             (((x) & 0xFFFF) << 1)
#define BIT_PUB_AHB_WRAP_WIFI_DFS_HW_BYPASS                     BIT(0)

/* REG_PUB_AHB_WRAP_DFS_SW_CTRL1 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_CLK_MODE_DEFAULT(x)         (((x) & 0x3) << 18)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_CLK_MODE(x)                 (((x) & 0x3) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_RATIO_D2_DEFAULT(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_RATIO_D2(x)                 (((x) & 0xF))

/* REG_PUB_AHB_WRAP_DFS_SW_CTRL2 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_DDL_ADJS_DEFAULT(x)         (((x) & 0x1FF) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_DDL_ADJS(x)                 (((x) & 0x1FF))

/* REG_PUB_AHB_WRAP_DFS_SW_CTRL3 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_URGENT_WAIT_TIMEOUT_PERIOD(x)  (((x) & 0x3FF) << 18)
#define BIT_PUB_AHB_WRAP_PUB_DFS_URGENT_WAIT_TIMEOUT_EN         BIT(17)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_URGENT_WAIT_EN              BIT(16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_SW_URGENT_DENY_EN(x)           (((x) & 0xFFFF))

/* REG_PUB_AHB_WRAP_PUB_DMC_MPU_INT */

#define BIT_PUB_AHB_WRAP_INT_DMC_MPU_VIO                        BIT(3)
#define BIT_PUB_AHB_WRAP_DMC_MPU_VIO_INT_RAW                    BIT(2)
#define BIT_PUB_AHB_WRAP_DMC_MPU_VIO_INT_CLR                    BIT(1)
#define BIT_PUB_AHB_WRAP_DMC_MPU_VIO_INT_EN                     BIT(0)

/* REG_PUB_AHB_WRAP_DFS_INT_CTRL */

#define BIT_PUB_AHB_WRAP_DFS_GIVEUP_INT_CLR                     BIT(9)
#define BIT_PUB_AHB_WRAP_DFS_GIVEUP_INT_EN                      BIT(8)
#define BIT_PUB_AHB_WRAP_DFS_DENY_INT_CLR                       BIT(7)
#define BIT_PUB_AHB_WRAP_DFS_DENY_INT_EN                        BIT(6)
#define BIT_PUB_AHB_WRAP_DFS_ERROR_INT_CLR                      BIT(5)
#define BIT_PUB_AHB_WRAP_DFS_ERROR_INT_EN                       BIT(4)
#define BIT_PUB_AHB_WRAP_DFS_COMPLETE_INT_CLR                   BIT(3)
#define BIT_PUB_AHB_WRAP_DFS_COMPLETE_INT_EN                    BIT(2)
#define BIT_PUB_AHB_WRAP_HW_DFS_EXIT_INT_CLR                    BIT(1)
#define BIT_PUB_AHB_WRAP_HW_DFS_EXIT_INT_EN                     BIT(0)

/* REG_PUB_AHB_WRAP_BASE_ADDR */

#define BIT_PUB_AHB_WRAP_PUB_CP_BASE_ADDR(x)                    (((x) & 0x1F) << 24)
#define BIT_PUB_AHB_WRAP_WTL_CP_BASE_ADDR(x)                    (((x) & 0x1F) << 16)
#define BIT_PUB_AHB_WRAP_WCN_BASE_ADDR(x)                       (((x) & 0x1F) << 8)
#define BIT_PUB_AHB_WRAP_AON_BASE_ADDR(x)                       (((x) & 0x1F))

/* REG_PUB_AHB_WRAP_BIST_CTRL */

#define BIT_PUB_AHB_WRAP_PUB_BIST_EB_AXI                        BIT(17)
#define BIT_PUB_AHB_WRAP_PUB_BIST_EB_REG                        BIT(16)
#define BIT_PUB_AHB_WRAP_BIST_VSP_EN                            BIT(11)
#define BIT_PUB_AHB_WRAP_BIST_WCN_AON_EN                        BIT(10)
#define BIT_PUB_AHB_WRAP_BIST_WTL_PUBCP_EN                      BIT(9)
#define BIT_PUB_AHB_WRAP_BIST_AP_EN                             BIT(8)
#define BIT_PUB_AHB_WRAP_BIST_CPU_EN                            BIT(7)
#define BIT_PUB_AHB_WRAP_BIST_DPU_EN                            BIT(6)
#define BIT_PUB_AHB_WRAP_BIST_GPU_EN                            BIT(5)
#define BIT_PUB_AHB_WRAP_BIST_MM_EN                             BIT(4)
#define BIT_PUB_AHB_WRAP_BIST_MUX_1(x)                          (((x) & 0x3) << 2)
#define BIT_PUB_AHB_WRAP_BIST_MUX_0(x)                          (((x) & 0x3))

/* REG_PUB_AHB_WRAP_BIST_CTRL_STATUS */

#define BIT_PUB_AHB_WRAP_DSKPLL_BIST_CNT(x)                     (((x) & 0xFFFF) << 16)
#define BIT_PUB_AHB_WRAP_BIST_FAIL_3                            BIT(3)
#define BIT_PUB_AHB_WRAP_BIST_FAIL_2                            BIT(2)
#define BIT_PUB_AHB_WRAP_BIST_FAIL_1                            BIT(1)
#define BIT_PUB_AHB_WRAP_BIST_FAIL_0                            BIT(0)

/* REG_PUB_AHB_WRAP_BUSMON_CLK_EN */

#define BIT_PUB_AHB_WRAP_BUSMON_EB_ATCLK                        BIT(4)
#define BIT_PUB_AHB_WRAP_BUSMON_CH_SOFT_RST                     BIT(3)
#define BIT_PUB_AHB_WRAP_BUSMON_SOFT_RST                        BIT(2)
#define BIT_PUB_AHB_WRAP_BUSMON_EB_AXI                          BIT(1)
#define BIT_PUB_AHB_WRAP_BUSMON_EB_REG                          BIT(0)

/* REG_PUB_AHB_WRAP_PUB_PERI_CLK_EN */

#define BIT_PUB_AHB_WRAP_RESERVE_CLK_EB(x)                      (((x) & 0xFFF) << 4)
#define BIT_PUB_AHB_WRAP_QOS_SLV_CLK_EB                         BIT(3)
#define BIT_PUB_AHB_WRAP_AXI_DEBUG_TCK_EB                       BIT(2)
#define BIT_PUB_AHB_WRAP_OT_CLK_EB                              BIT(1)
#define BIT_PUB_AHB_WRAP_FW_EB_APB                              BIT(0)

/* REG_PUB_AHB_WRAP_PUB_AXI_QOS_REG_1 */

#define BIT_PUB_AHB_WRAP_AWQOS_THRESHOLD_PUBCP(x)               (((x) & 0xF) << 28)
#define BIT_PUB_AHB_WRAP_ARQOS_THRESHOLD_PUBCP(x)               (((x) & 0xF) << 24)

/* REG_PUB_AHB_WRAP_RESERVED4 */


/* REG_PUB_AHB_WRAP_DFS_HW_CTRL */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_DDL_ADJS_DEFAULT(x)         (((x) & 0x1FF) << 22)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_CLK_MODE_DEFAULT(x)         (((x) & 0x3) << 20)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_RATIO_D2_DEFAULT(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_RATIO_DEFAULT(x)            (((x) & 0x7F) << 8)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_INITIAL_FREQ(x)             (((x) & 0x7) << 4)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_STOP                        BIT(2)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_START                       BIT(1)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_ENABLE                      BIT(0)

/* REG_PUB_AHB_WRAP_DFS_HW_CTRL1 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_MIN_FREQ_UP_FORCE_TRIG      BIT(28)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_BWMON_MIN_EN                BIT(27)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_BWMON_MIN_FREQ(x)           (((x) & 0x7) << 24)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_AVAIL_FREQ_EN(x)            (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_CHECK_PLL_EN                BIT(12)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_MIN_FREQ_UP(x)              (((x) & 0x7) << 8)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_MIN_FREQ_DN(x)              (((x) & 0x7) << 4)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_MIN_EN_UP                   BIT(3)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_MIN_EN_DN                   BIT(2)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_MIN_LOAD                    BIT(1)
#define BIT_PUB_AHB_WRAP_PUB_DFS_LP_PROT_EN                     BIT(0)

/* REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET0 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F3_RATIO(x)                 (((x) & 0x7F) << 24)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F2_RATIO(x)                 (((x) & 0x7F) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F1_RATIO(x)                 (((x) & 0x7F) << 8)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F0_RATIO(x)                 (((x) & 0x7F))

/* REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET1 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F7_RATIO(x)                 (((x) & 0x7F) << 24)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F6_RATIO(x)                 (((x) & 0x7F) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F5_RATIO(x)                 (((x) & 0x7F) << 8)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F4_RATIO(x)                 (((x) & 0x7F))

/* REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET2 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F7_RATIO_D2(x)              (((x) & 0xF) << 28)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F6_RATIO_D2(x)              (((x) & 0xF) << 24)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F5_RATIO_D2(x)              (((x) & 0xF) << 20)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F4_RATIO_D2(x)              (((x) & 0xF) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F3_RATIO_D2(x)              (((x) & 0xF) << 12)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F2_RATIO_D2(x)              (((x) & 0xF) << 8)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F1_RATIO_D2(x)              (((x) & 0xF) << 4)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F0_RATIO_D2(x)              (((x) & 0xF))

/* REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET3 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F7_CLK_MODE(x)              (((x) & 0x3) << 14)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F6_CLK_MODE(x)              (((x) & 0x3) << 12)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F5_CLK_MODE(x)              (((x) & 0x3) << 10)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F4_CLK_MODE(x)              (((x) & 0x3) << 8)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F3_CLK_MODE(x)              (((x) & 0x3) << 6)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F2_CLK_MODE(x)              (((x) & 0x3) << 4)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F1_CLK_MODE(x)              (((x) & 0x3) << 2)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F0_CLK_MODE(x)              (((x) & 0x3))

/* REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET4 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F1_DDL_ADJS(x)              (((x) & 0x1FF) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F0_DDL_ADJS(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET5 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F3_DDL_ADJS(x)              (((x) & 0x1FF) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F2_DDL_ADJS(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET6 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F5_DDL_ADJS(x)              (((x) & 0x1FF) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F4_DDL_ADJS(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_WRAP_DFS_HW_RATIO_SET7 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F7_DDL_ADJS(x)              (((x) & 0x1FF) << 16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_F6_DDL_ADJS(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_WRAP_DFS_HW_CTRL2 */

#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_URGENT_WAIT_EN              BIT(16)
#define BIT_PUB_AHB_WRAP_PUB_DFS_HW_URGENT_DENY_EN(x)           (((x) & 0xFFFF))


#endif /* PUB_AHB_WRAP_H */


/*
 * Copyright (C) 2019 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2019-01-07 15:09:47
 *
 */


#ifndef PUB_APB_H
#define PUB_APB_H

#define CTL_BASE_PUB_APB 0x300E0000


#define REG_PUB_APB_BUSMON_CNT_START            ( CTL_BASE_PUB_APB + 0x0000 )
#define REG_PUB_APB_BUSMON_CFG                  ( CTL_BASE_PUB_APB + 0x0004 )
#define REG_PUB_APB_DDR_EB                      ( CTL_BASE_PUB_APB + 0x0008 )
#define REG_PUB_APB_DDR_SOFT_RST                ( CTL_BASE_PUB_APB + 0x000C )
#define REG_PUB_APB_SYS_ENDIAN_CTRL             ( CTL_BASE_PUB_APB + 0x3090 )
#define REG_PUB_APB_DMC_DUMMY_REG0              ( CTL_BASE_PUB_APB + 0x30A0 )
#define REG_PUB_APB_DMC_DUMMY_REG1              ( CTL_BASE_PUB_APB + 0x30A4 )
#define REG_PUB_APB_DMC_DUMMY_REG2              ( CTL_BASE_PUB_APB + 0x30A8 )
#define REG_PUB_APB_DMC_DUMMY_REG3              ( CTL_BASE_PUB_APB + 0x30AC )
#define REG_PUB_APB_DMC_REMAP_EN                ( CTL_BASE_PUB_APB + 0x32A8 )
#define REG_PUB_APB_DMC_PORT0_REMAP_ADDR_0      ( CTL_BASE_PUB_APB + 0x32AC )
#define REG_PUB_APB_DMC_PORT0_REMAP_ADDR_1      ( CTL_BASE_PUB_APB + 0x32B0 )
#define REG_PUB_APB_DMC_PORT1_REMAP_ADDR_0      ( CTL_BASE_PUB_APB + 0x32B4 )
#define REG_PUB_APB_DMC_PORT1_REMAP_ADDR_1      ( CTL_BASE_PUB_APB + 0x32B8 )
#define REG_PUB_APB_DMC_PORT2_REMAP_ADDR_0      ( CTL_BASE_PUB_APB + 0x32BC )
#define REG_PUB_APB_DMC_PORT2_REMAP_ADDR_1      ( CTL_BASE_PUB_APB + 0x32C0 )
#define REG_PUB_APB_DMC_PORT3_REMAP_ADDR_0      ( CTL_BASE_PUB_APB + 0x32C4 )
#define REG_PUB_APB_DMC_PORT3_REMAP_ADDR_1      ( CTL_BASE_PUB_APB + 0x32C8 )
#define REG_PUB_APB_DMC_PORT4_REMAP_ADDR_0      ( CTL_BASE_PUB_APB + 0x32CC )
#define REG_PUB_APB_DMC_PORT4_REMAP_ADDR_1      ( CTL_BASE_PUB_APB + 0x32D0 )
#define REG_PUB_APB_DMC_PORT5_REMAP_ADDR_0      ( CTL_BASE_PUB_APB + 0x32D4 )
#define REG_PUB_APB_DMC_PORT5_REMAP_ADDR_1      ( CTL_BASE_PUB_APB + 0x32D8 )
#define REG_PUB_APB_DMC_PORT6_REMAP_ADDR_0      ( CTL_BASE_PUB_APB + 0x32DC )
#define REG_PUB_APB_DMC_PORT6_REMAP_ADDR_1      ( CTL_BASE_PUB_APB + 0x32E0 )
#define REG_PUB_APB_PUB_DMC_MPU_INT             ( CTL_BASE_PUB_APB + 0x32E8 )
#define REG_PUB_APB_PUB_AXI_QOS_REG             ( CTL_BASE_PUB_APB + 0x32EC )
#define REG_PUB_APB_DFS_INT_CTRL                ( CTL_BASE_PUB_APB + 0x32F0 )
#define REG_PUB_APB_DFS_STATUS                  ( CTL_BASE_PUB_APB + 0x32F4 )
#define REG_PUB_APB_DFS_SW_CTRL                 ( CTL_BASE_PUB_APB + 0x32F8 )
#define REG_PUB_APB_DFS_FC_REQ_DELAY            ( CTL_BASE_PUB_APB + 0x32FC )
#define REG_PUB_APB_DFS_HW_CTRL                 ( CTL_BASE_PUB_APB + 0x3300 )
#define REG_PUB_APB_DFS_HW_FRQ_RATIO            ( CTL_BASE_PUB_APB + 0x3334 )
#define REG_PUB_APB_DFS_PURE_SW_CTRL            ( CTL_BASE_PUB_APB + 0x3338 )
#define REG_PUB_APB_MEM_FW_INT                  ( CTL_BASE_PUB_APB + 0x333C )
#define REG_PUB_APB_AXI_LPC_CTRL_0              ( CTL_BASE_PUB_APB + 0x3340 )
#define REG_PUB_APB_AXI_LPC_CTRL_1              ( CTL_BASE_PUB_APB + 0x3344 )
#define REG_PUB_APB_FENCING_CTRL                ( CTL_BASE_PUB_APB + 0x3348 )
#define REG_PUB_APB_BASE_ADDR                   ( CTL_BASE_PUB_APB + 0x334C )
#define REG_PUB_APB_WIFI_DFS_CTRL               ( CTL_BASE_PUB_APB + 0x3350 )
#define REG_PUB_APB_DFS_SW_GFREE_CFG            ( CTL_BASE_PUB_APB + 0x3354 )
#define REG_PUB_APB_PUB_CLK_CTRL                ( CTL_BASE_PUB_APB + 0x5000 )
#define REG_PUB_APB_AON_WCN_BASE_ADDR           ( CTL_BASE_PUB_APB + 0x5004 )
#define REG_PUB_APB_PUBCP_WT_LCP_BASE_ADDR      ( CTL_BASE_PUB_APB + 0x5008 )
#define REG_PUB_APB_PUB_AXI_QOS_REG_1           ( CTL_BASE_PUB_APB + 0x500C )
#define REG_PUB_APB_DMC_URGENT_QOS_0            ( CTL_BASE_PUB_APB + 0x5010 )
#define REG_PUB_APB_DMC_URGENT_QOS_1            ( CTL_BASE_PUB_APB + 0x5014 )
#define REG_PUB_APB_DDR_IP_SOFT_RST             ( CTL_BASE_PUB_APB + 0x5108 )
#define REG_PUB_APB_DFS_SW_CTRL_1               ( CTL_BASE_PUB_APB + 0x510C )
#define REG_PUB_APB_PTEST_DSKPLL_BIST_CNT       ( CTL_BASE_PUB_APB + 0x5200 )
#define REG_PUB_APB_DFS_DSKPLL_PD_CTRL          ( CTL_BASE_PUB_APB + 0x5204 )
#define REG_PUB_APB_DDR_FRQ_TO_AON_GET          ( CTL_BASE_PUB_APB + 0x5208 )
#define REG_PUB_APB_DMC_BIST_PORT_EN            ( CTL_BASE_PUB_APB + 0x5300 )

/* REG_PUB_APB_BUSMON_CNT_START */


/* REG_PUB_APB_BUSMON_CFG */

#define BIT_PUB_APB_BUSMON_EB                     BIT(23)
#define BIT_PUB_APB_PUB_BUSMON6_EB                BIT(22)
#define BIT_PUB_APB_PUB_BUSMON5_EB                BIT(21)
#define BIT_PUB_APB_PUB_BUSMON4_EB                BIT(20)
#define BIT_PUB_APB_PUB_BUSMON3_EB                BIT(19)
#define BIT_PUB_APB_PUB_BUSMON2_EB                BIT(18)
#define BIT_PUB_APB_PUB_BUSMON1_EB                BIT(17)
#define BIT_PUB_APB_PUB_BUSMON0_EB                BIT(16)
#define BIT_PUB_APB_BUSMON_SOFT_RST               BIT(7)
#define BIT_PUB_APB_PUB_BUSMON6_SOFT_RST          BIT(6)
#define BIT_PUB_APB_PUB_BUSMON5_SOFT_RST          BIT(5)
#define BIT_PUB_APB_PUB_BUSMON4_SOFT_RST          BIT(4)
#define BIT_PUB_APB_PUB_BUSMON3_SOFT_RST          BIT(3)
#define BIT_PUB_APB_PUB_BUSMON2_SOFT_RST          BIT(2)
#define BIT_PUB_APB_PUB_BUSMON1_SOFT_RST          BIT(1)
#define BIT_PUB_APB_PUB_BUSMON0_SOFT_RST          BIT(0)

/* REG_PUB_APB_DDR_EB */


/* REG_PUB_APB_DDR_SOFT_RST */


/* REG_PUB_APB_SYS_ENDIAN_CTRL */


/* REG_PUB_APB_DMC_DUMMY_REG0 */

#define BIT_PUB_APB_DMC_DUMMY_REG0(x)             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_DUMMY_REG1 */

#define BIT_PUB_APB_DMC_DUMMY_REG1(x)             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_DUMMY_REG2 */

#define BIT_PUB_APB_DMC_DUMMY_REG2(x)             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_DUMMY_REG3 */

#define BIT_PUB_APB_DMC_DUMMY_REG3(x)             (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_REMAP_EN */

#define BIT_PUB_APB_DMC_REMAP_EN(x)               (((x) & 0x3FFF))

/* REG_PUB_APB_DMC_PORT0_REMAP_ADDR_0 */

#define BIT_PUB_APB_DMC_PORT0_REMAP_ADDR_0(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT0_REMAP_ADDR_1 */

#define BIT_PUB_APB_DMC_PORT0_REMAP_ADDR_1(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT1_REMAP_ADDR_0 */

#define BIT_PUB_APB_DMC_PORT1_REMAP_ADDR_0(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT1_REMAP_ADDR_1 */

#define BIT_PUB_APB_DMC_PORT1_REMAP_ADDR_1(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT2_REMAP_ADDR_0 */

#define BIT_PUB_APB_DMC_PORT2_REMAP_ADDR_0(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT2_REMAP_ADDR_1 */

#define BIT_PUB_APB_DMC_PORT2_REMAP_ADDR_1(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT3_REMAP_ADDR_0 */

#define BIT_PUB_APB_DMC_PORT3_REMAP_ADDR_0(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT3_REMAP_ADDR_1 */

#define BIT_PUB_APB_DMC_PORT3_REMAP_ADDR_1(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT4_REMAP_ADDR_0 */

#define BIT_PUB_APB_DMC_PORT4_REMAP_ADDR_0(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT4_REMAP_ADDR_1 */

#define BIT_PUB_APB_DMC_PORT4_REMAP_ADDR_1(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT5_REMAP_ADDR_0 */

#define BIT_PUB_APB_DMC_PORT5_REMAP_ADDR_0(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT5_REMAP_ADDR_1 */

#define BIT_PUB_APB_DMC_PORT5_REMAP_ADDR_1(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT6_REMAP_ADDR_0 */

#define BIT_PUB_APB_DMC_PORT6_REMAP_ADDR_0(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_DMC_PORT6_REMAP_ADDR_1 */

#define BIT_PUB_APB_DMC_PORT6_REMAP_ADDR_1(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_APB_PUB_DMC_MPU_INT */

#define BIT_PUB_APB_INT_DMC_MPU_VIO               BIT(3)
#define BIT_PUB_APB_DMC_MPU_VIO_INT_RAW           BIT(2)
#define BIT_PUB_APB_DMC_MPU_VIO_INT_CLR           BIT(1)
#define BIT_PUB_APB_DMC_MPU_VIO_INT_EN            BIT(0)

/* REG_PUB_APB_PUB_AXI_QOS_REG */

#define BIT_PUB_APB_AWQOS_THRESHOLD_CP(x)         (((x) & 0xF) << 28)
#define BIT_PUB_APB_ARQOS_THRESHOLD_CP(x)         (((x) & 0xF) << 24)
#define BIT_PUB_APB_AWQOS_THRESHOLD_AON_WCN(x)    (((x) & 0xF) << 20)
#define BIT_PUB_APB_ARQOS_THRESHOLD_AON_WCN(x)    (((x) & 0xF) << 16)
#define BIT_PUB_APB_AWQOS_WCN(x)                  (((x) & 0xF) << 12)
#define BIT_PUB_APB_ARQOS_WCN(x)                  (((x) & 0xF) << 8)
#define BIT_PUB_APB_AWQOS_AON(x)                  (((x) & 0xF) << 4)
#define BIT_PUB_APB_ARQOS_AON(x)                  (((x) & 0xF))

/* REG_PUB_APB_DFS_INT_CTRL */

#define BIT_PUB_APB_DFS_ERROR_INT_CLR             BIT(5)
#define BIT_PUB_APB_DFS_ERROR_INT_EN              BIT(4)
#define BIT_PUB_APB_DFS_COMPLETE_INT_CLR          BIT(3)
#define BIT_PUB_APB_DFS_COMPLETE_INT_EN           BIT(2)
#define BIT_PUB_APB_HW_DFS_EXIT_INT_CLR           BIT(1)
#define BIT_PUB_APB_HW_DFS_EXIT_INT_EN            BIT(0)

/* REG_PUB_APB_DFS_STATUS */

#define BIT_PUB_APB_HW_DFS_FSM_STATE(x)           (((x) & 0xF) << 7)
#define BIT_PUB_APB_HW_DFS_FSM_IDLE               BIT(6)
#define BIT_PUB_APB_DFS_ERROR_INT_RAW             BIT(5)
#define BIT_PUB_APB_INT_DFS_ERROR                 BIT(4)
#define BIT_PUB_APB_DFS_COMPLETE_INT_RAW          BIT(3)
#define BIT_PUB_APB_INT_DFS_COMPLETE              BIT(2)
#define BIT_PUB_APB_HW_DFS_EXIT_INT_RAW           BIT(1)
#define BIT_PUB_APB_INT_HW_DFS_EXIT               BIT(0)

/* REG_PUB_APB_DFS_SW_CTRL */

#define BIT_PUB_APB_PUB_DFS_SW_CLK_MODE_DEFAULT   BIT(30)
#define BIT_PUB_APB_PUB_DFS_SW_CLK_MODE           BIT(29)
#define BIT_PUB_APB_PUB_DFS_SW_RATIO_DEFAULT(x)   (((x) & 0x7FF) << 18)
#define BIT_PUB_APB_PUB_DFS_SW_RATIO(x)           (((x) & 0x7FF) << 7)
#define BIT_PUB_APB_PUB_DFS_SW_FRQ_SEL(x)         (((x) & 0x7) << 4)
#define BIT_PUB_APB_PUB_DFS_SW_RESP               BIT(3)
#define BIT_PUB_APB_PUB_DFS_SW_ACK                BIT(2)
#define BIT_PUB_APB_PUB_DFS_SW_REQ                BIT(1)
#define BIT_PUB_APB_PUB_DFS_SW_ENABLE             BIT(0)

/* REG_PUB_APB_DFS_FC_REQ_DELAY */

#define BIT_PUB_APB_DFS_FC_REQ_DELAY(x)           (((x) & 0x7))

/* REG_PUB_APB_DFS_HW_CTRL */


/* REG_PUB_APB_DFS_HW_FRQ_RATIO */


/* REG_PUB_APB_DFS_PURE_SW_CTRL */

#define BIT_PUB_APB_PURE_SW_DFS_ACK               BIT(20)
#define BIT_PUB_APB_PURE_SW_DFS_RESP              BIT(19)
#define BIT_PUB_APB_PURE_SW_DFS_FC_REQ            BIT(18)
#define BIT_PUB_APB_PURE_SW_DFS_REQ               BIT(17)
#define BIT_PUB_APB_PURE_SW_DFS_FC_ACK            BIT(16)
#define BIT_PUB_APB_PURE_SW_DFS_FRQ_SEL(x)        (((x) & 0x7) << 13)
#define BIT_PUB_APB_EMC_CKG_MODE_PURE_SW          BIT(12)
#define BIT_PUB_APB_EMC_CKG_SEL_PURE_SW(x)        (((x) & 0x7FF) << 1)
#define BIT_PUB_APB_DFS_SW_DFS_MODE               BIT(0)

/* REG_PUB_APB_MEM_FW_INT */

#define BIT_PUB_APB_MEM_FW_INT_RAW                BIT(3)
#define BIT_PUB_APB_INT_MEM_FW                    BIT(2)
#define BIT_PUB_APB_MEM_FW_INT_CLR                BIT(1)
#define BIT_PUB_APB_MEM_FW_INT_EN                 BIT(0)

/* REG_PUB_APB_AXI_LPC_CTRL_0 */

#define BIT_PUB_APB_LP_FORCE_DISP_DCAM_S0         BIT(17)
#define BIT_PUB_APB_LP_EB_DISP_DCAM_S0            BIT(16)
#define BIT_PUB_APB_LP_FORCE_DISP_DCAM_M1         BIT(15)
#define BIT_PUB_APB_LP_EB_DISP_DCAM_M1            BIT(14)
#define BIT_PUB_APB_LP_FORCE_DISP_DCAM_M0         BIT(13)
#define BIT_PUB_APB_LP_EB_DISP_DCAM_M0            BIT(12)
#define BIT_PUB_APB_LP_FORCE_AON_WCN_S0           BIT(11)
#define BIT_PUB_APB_LP_EB_AON_WCN_S0              BIT(10)
#define BIT_PUB_APB_LP_FORCE_AON_WCN_M1           BIT(9)
#define BIT_PUB_APB_LP_EB_AON_WCN_M1              BIT(8)
#define BIT_PUB_APB_LP_FORCE_AON_WCN_M0           BIT(7)
#define BIT_PUB_APB_LP_EB_AON_WCN_M0              BIT(6)
#define BIT_PUB_APB_LP_FORCE_CP_S0                BIT(5)
#define BIT_PUB_APB_LP_EB_CP_S0                   BIT(4)
#define BIT_PUB_APB_LP_FORCE_CP_M1                BIT(3)
#define BIT_PUB_APB_LP_EB_CP_M1                   BIT(2)
#define BIT_PUB_APB_LP_FORCE_CP_M0                BIT(1)
#define BIT_PUB_APB_LP_EB_CP_M0                   BIT(0)

/* REG_PUB_APB_AXI_LPC_CTRL_1 */

#define BIT_PUB_APB_LP_NUM(x)                     (((x) & 0xFFFF))

/* REG_PUB_APB_FENCING_CTRL */

#define BIT_PUB_APB_DDR_FENCING_EN                BIT(30)
#define BIT_PUB_APB_FENCING_CHNL_IDLE_CNT(x)      (((x) & 0x3FFFFFFF))

/* REG_PUB_APB_BASE_ADDR */


/* REG_PUB_APB_WIFI_DFS_CTRL */

#define BIT_PUB_APB_WIFI_DFS_TIMEOUT_FLAG         BIT(23)
#define BIT_PUB_APB_WIFI_DFS_ACK                  BIT(22)
#define BIT_PUB_APB_WIFI_DFS_URGENCY_CTRL_EN      BIT(21)
#define BIT_PUB_APB_WIFI_FIFO_URGENCY_CTRL_EN     BIT(20)
#define BIT_PUB_APB_WIFI_DFS_SW_REQ               BIT(19)
#define BIT_PUB_APB_WIFI_DFS_MODE                 BIT(18)
#define BIT_PUB_APB_WIFI_DFS_TIMEOUT_EN           BIT(17)
#define BIT_PUB_APB_WIFI_DFS_TIMEOUT_PERIOD(x)    (((x) & 0xFFFF) << 1)
#define BIT_PUB_APB_WIFI_DFS_HW_BYPASS            BIT(0)

/* REG_PUB_APB_DFS_SW_GFREE_CFG */

#define BIT_PUB_APB_CGM_DFS_GFREE_SWITCH_SW_EN    BIT(24)
#define BIT_PUB_APB_CGM_DFS_GFREE_SWITCH_DIV(x)   (((x) & 0xF) << 20)
#define BIT_PUB_APB_CGM_DFS_GFREE_SWITCH_SEL      BIT(19)
#define BIT_PUB_APB_GFREE_SW_OPEN_DELAY(x)        (((x) & 0x1FF) << 10)
#define BIT_PUB_APB_GFREE_SW_CLOSE_DELAY(x)       (((x) & 0x1FF) << 1)
#define BIT_PUB_APB_GFREE_SW_CTRL_BYPASS          BIT(0)

/* REG_PUB_APB_PUB_CLK_CTRL */

#define BIT_PUB_APB_DMC_BIST_CLK_EB               BIT(26)
#define BIT_PUB_APB_DDR_CLK_EN                    BIT(25)
#define BIT_PUB_APB_DMC_X2_DELAY_SEL              BIT(24)
#define BIT_PUB_APB_DFS_CLK_AG_EN                 BIT(16)
#define BIT_PUB_APB_DMC_2X_CLK_AG_EN              BIT(10)
#define BIT_PUB_APB_DMC_D2_CLK_AG_EN              BIT(9)
#define BIT_PUB_APB_DMC_1X_CLK_AG_EN              BIT(8)
#define BIT_PUB_APB_PTM_KEEP_DMC_CLK_FREE_EN      BIT(2)
#define BIT_PUB_APB_CHN_DMC_STOP_CG_EN            BIT(1)
#define BIT_PUB_APB_DMC_SREF_AUTO_GATE_EN         BIT(0)

/* REG_PUB_APB_AON_WCN_BASE_ADDR */

#define BIT_PUB_APB_WCN_BASE_ADDR(x)              (((x) & 0xFFF) << 16)
#define BIT_PUB_APB_AON_BASE_ADDR(x)              (((x) & 0xFFF))

/* REG_PUB_APB_PUBCP_WT_LCP_BASE_ADDR */

#define BIT_PUB_APB_PUB_CP_BASE_ADDR(x)           (((x) & 0xFFF) << 16)
#define BIT_PUB_APB_WTL_CP_BASE_ADDR(x)           (((x) & 0xFFF))

/* REG_PUB_APB_PUB_AXI_QOS_REG_1 */

#define BIT_PUB_APB_AWQOS_THRESHOLD_DISP_DCAM(x)  (((x) & 0xF) << 4)
#define BIT_PUB_APB_ARQOS_THRESHOLD_DISP_DCAM(x)  (((x) & 0xF))

/* REG_PUB_APB_DMC_URGENT_QOS_0 */

#define BIT_PUB_APB_ARQOS_URGENT_CH3(x)           (((x) & 0xF) << 28)
#define BIT_PUB_APB_AWQOS_URGENT_CH3(x)           (((x) & 0xF) << 24)
#define BIT_PUB_APB_ARQOS_URGENT_CH2(x)           (((x) & 0xF) << 20)
#define BIT_PUB_APB_AWQOS_URGENT_CH2(x)           (((x) & 0xF) << 16)
#define BIT_PUB_APB_ARQOS_URGENT_CH1(x)           (((x) & 0xF) << 12)
#define BIT_PUB_APB_AWQOS_URGENT_CH1(x)           (((x) & 0xF) << 8)
#define BIT_PUB_APB_ARQOS_URGENT_CH0(x)           (((x) & 0xF) << 4)
#define BIT_PUB_APB_AWQOS_URGENT_CH0(x)           (((x) & 0xF))

/* REG_PUB_APB_DMC_URGENT_QOS_1 */

#define BIT_PUB_APB_ARQOS_URGENT_CH7(x)           (((x) & 0xF) << 28)
#define BIT_PUB_APB_AWQOS_URGENT_CH7(x)           (((x) & 0xF) << 24)
#define BIT_PUB_APB_ARQOS_URGENT_CH6(x)           (((x) & 0xF) << 20)
#define BIT_PUB_APB_AWQOS_URGENT_CH6(x)           (((x) & 0xF) << 16)
#define BIT_PUB_APB_ARQOS_URGENT_CH5(x)           (((x) & 0xF) << 12)
#define BIT_PUB_APB_AWQOS_URGENT_CH5(x)           (((x) & 0xF) << 8)
#define BIT_PUB_APB_ARQOS_URGENT_CH4(x)           (((x) & 0xF) << 4)
#define BIT_PUB_APB_AWQOS_URGENT_CH4(x)           (((x) & 0xF))

/* REG_PUB_APB_DDR_IP_SOFT_RST */

#define BIT_PUB_APB_DMC_PHY_SOFT_RST              BIT(1)
#define BIT_PUB_APB_DMC_SOFT_RST                  BIT(0)

/* REG_PUB_APB_DFS_SW_CTRL_1 */

#define BIT_PUB_APB_PUB_DFS_SW_SWITCH_PERIOD(x)   (((x) & 0xFFF))

/* REG_PUB_APB_PTEST_DSKPLL_BIST_CNT */

#define BIT_PUB_APB_PTEST_DSKPLL_BIST_CNT(x)      (((x) & 0xFFFF))

/* REG_PUB_APB_DFS_DSKPLL_PD_CTRL */

#define BIT_PUB_APB_R_PLL_SLEEP_PD_L              BIT(17)
#define BIT_PUB_APB_R_PLL_PD_L_AHEAD_EN           BIT(16)
#define BIT_PUB_APB_DFS_DSKPLL_PD_L_CNT(x)        (((x) & 0x3FF))

/* REG_PUB_APB_DDR_FRQ_TO_AON_GET */

#define BIT_PUB_APB_PUB_DFS_FRQ_SEL_VALID_SW      BIT(0)

/* REG_PUB_APB_DMC_BIST_PORT_EN */

#define BIT_PUB_APB_BIST_FAIL_FLAG_CH1            BIT(9)
#define BIT_PUB_APB_BIST_FAIL_FLAG_CH0            BIT(8)
#define BIT_PUB_APB_BIST_PORT6_EN                 BIT(6)
#define BIT_PUB_APB_BIST_PORT5_EN                 BIT(5)
#define BIT_PUB_APB_BIST_PORT4_EN                 BIT(4)
#define BIT_PUB_APB_BIST_PORT3_EN                 BIT(3)
#define BIT_PUB_APB_BIST_PORT2_EN                 BIT(2)
#define BIT_PUB_APB_BIST_PORT1_EN                 BIT(1)
#define BIT_PUB_APB_BIST_PORT0_EN                 BIT(0)


#endif /* PUB_APB_H */



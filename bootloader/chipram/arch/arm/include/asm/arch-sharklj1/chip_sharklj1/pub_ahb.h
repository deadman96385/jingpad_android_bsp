/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-05-30 15:03:07
 *
 */


#ifndef PUB_AHB_H
#define PUB_AHB_H

#define CTL_BASE_PUB_AHB 0x300E0000


#define REG_PUB_AHB_BUSMON_CNT_START         ( CTL_BASE_PUB_AHB + 0x0000 )
#define REG_PUB_AHB_BUSMON_CFG               ( CTL_BASE_PUB_AHB + 0x0004 )
#define REG_PUB_AHB_DMC_PORT_REMAP_EN        ( CTL_BASE_PUB_AHB + 0x3000 )
#define REG_PUB_AHB_DMC_PORTS_MPU_EN         ( CTL_BASE_PUB_AHB + 0x3004 )
#define REG_PUB_AHB_DMC_PORT0_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x3008 )
#define REG_PUB_AHB_DMC_PORT1_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x300C )
#define REG_PUB_AHB_DMC_PORT2_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x3010 )
#define REG_PUB_AHB_DMC_PORT3_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x3014 )
#define REG_PUB_AHB_DMC_PORT4_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x3018 )
#define REG_PUB_AHB_DMC_PORT5_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x301C )
#define REG_PUB_AHB_DMC_PORT6_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x3020 )
#define REG_PUB_AHB_DMC_PORT7_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x3024 )
#define REG_PUB_AHB_DMC_PORT8_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x3028 )
#define REG_PUB_AHB_DMC_PORT9_ADDR_REMAP_0   ( CTL_BASE_PUB_AHB + 0x302C )
#define REG_PUB_AHB_DMC_PORT0_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x3030 )
#define REG_PUB_AHB_DMC_PORT1_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x3034 )
#define REG_PUB_AHB_DMC_PORT2_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x3038 )
#define REG_PUB_AHB_DMC_PORT3_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x303C )
#define REG_PUB_AHB_DMC_PORT4_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x3040 )
#define REG_PUB_AHB_DMC_PORT5_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x3044 )
#define REG_PUB_AHB_DMC_PORT6_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x3048 )
#define REG_PUB_AHB_DMC_PORT7_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x3050 )
#define REG_PUB_AHB_DMC_PORT8_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x3054 )
#define REG_PUB_AHB_DMC_PORT9_MPU_RANGE      ( CTL_BASE_PUB_AHB + 0x3058 )
#define REG_PUB_AHB_DMC_PORT0_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x305C )
#define REG_PUB_AHB_DMC_PORT1_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x3060 )
#define REG_PUB_AHB_DMC_PORT2_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x3064 )
#define REG_PUB_AHB_DMC_PORT3_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x3068 )
#define REG_PUB_AHB_DMC_PORT4_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x306C )
#define REG_PUB_AHB_DMC_PORT5_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x3070 )
#define REG_PUB_AHB_DMC_PORT6_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x3074 )
#define REG_PUB_AHB_DMC_PORT7_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x3078 )
#define REG_PUB_AHB_DMC_PORT8_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x307C )
#define REG_PUB_AHB_DMC_PORT9_DUMP_ADDR      ( CTL_BASE_PUB_AHB + 0x3080 )
#define REG_PUB_AHB_SYS_ENDIAN_CTRL          ( CTL_BASE_PUB_AHB + 0x3090 )
#define REG_PUB_AHB_DMC_DUMMY_REG0           ( CTL_BASE_PUB_AHB + 0x30A0 )
#define REG_PUB_AHB_DMC_DUMMY_REG1           ( CTL_BASE_PUB_AHB + 0x30A4 )
#define REG_PUB_AHB_DMC_QOS_SEL              ( CTL_BASE_PUB_AHB + 0x3100 )
#define REG_PUB_AHB_DMC_ARQOS_0_7            ( CTL_BASE_PUB_AHB + 0x3110 )
#define REG_PUB_AHB_DMC_ARQOS_8              ( CTL_BASE_PUB_AHB + 0x3114 )
#define REG_PUB_AHB_DMC_AWQOS_0_7            ( CTL_BASE_PUB_AHB + 0x3118 )
#define REG_PUB_AHB_DMC_AWQOS_8              ( CTL_BASE_PUB_AHB + 0x311C )
#define REG_PUB_AHB_DMC_ARQOS_0_ID           ( CTL_BASE_PUB_AHB + 0x3120 )
#define REG_PUB_AHB_DMC_ARQOS_1_ID           ( CTL_BASE_PUB_AHB + 0x3124 )
#define REG_PUB_AHB_DMC_ARQOS_2_ID           ( CTL_BASE_PUB_AHB + 0x3128 )
#define REG_PUB_AHB_DMC_ARQOS_3_ID           ( CTL_BASE_PUB_AHB + 0x312C )
#define REG_PUB_AHB_DMC_ARQOS_4_ID           ( CTL_BASE_PUB_AHB + 0x3130 )
#define REG_PUB_AHB_DMC_ARQOS_5_ID           ( CTL_BASE_PUB_AHB + 0x3134 )
#define REG_PUB_AHB_DMC_ARQOS_6_ID           ( CTL_BASE_PUB_AHB + 0x3138 )
#define REG_PUB_AHB_DMC_ARQOS_7_ID           ( CTL_BASE_PUB_AHB + 0x313C )
#define REG_PUB_AHB_DMC_ARQOS_8_ID           ( CTL_BASE_PUB_AHB + 0x3140 )
#define REG_PUB_AHB_DMC_AWQOS_0_ID           ( CTL_BASE_PUB_AHB + 0x3150 )
#define REG_PUB_AHB_DMC_AWQOS_1_ID           ( CTL_BASE_PUB_AHB + 0x3154 )
#define REG_PUB_AHB_DMC_AWQOS_2_ID           ( CTL_BASE_PUB_AHB + 0x3158 )
#define REG_PUB_AHB_DMC_AWQOS_3_ID           ( CTL_BASE_PUB_AHB + 0x315C )
#define REG_PUB_AHB_DMC_AWQOS_4_ID           ( CTL_BASE_PUB_AHB + 0x3160 )
#define REG_PUB_AHB_DMC_AWQOS_5_ID           ( CTL_BASE_PUB_AHB + 0x3164 )
#define REG_PUB_AHB_DMC_AWQOS_6_ID           ( CTL_BASE_PUB_AHB + 0x3168 )
#define REG_PUB_AHB_DMC_AWQOS_7_ID           ( CTL_BASE_PUB_AHB + 0x316C )
#define REG_PUB_AHB_DMC_AWQOS_8_ID           ( CTL_BASE_PUB_AHB + 0x3170 )
#define REG_PUB_AHB_DMC_EXT_LPCTRL_CFG       ( CTL_BASE_PUB_AHB + 0x31A0 )
#define REG_PUB_AHB_DMC_EXT_LPCTRL_SEQL      ( CTL_BASE_PUB_AHB + 0x31A4 )
#define REG_PUB_AHB_DMC_EXT_LPCTRL_SEQH      ( CTL_BASE_PUB_AHB + 0x31A8 )
#define REG_PUB_AHB_DMC_EXT_LPCTRL_STEP      ( CTL_BASE_PUB_AHB + 0x31AC )
#define REG_PUB_AHB_QOS_SELECT               ( CTL_BASE_PUB_AHB + 0x31B0 )
#define REG_PUB_AHB_DMC_PORTS_MPU_SEL        ( CTL_BASE_PUB_AHB + 0x31B4 )
#define REG_PUB_AHB_DMC_PORT0_ADDR_REMAP_1   ( CTL_BASE_PUB_AHB + 0x31B8 )
#define REG_PUB_AHB_DMC_PORT1_ADDR_REMAP_1   ( CTL_BASE_PUB_AHB + 0x31BC )
#define REG_PUB_AHB_DMC_PORT2_ADDR_REMAP_1   ( CTL_BASE_PUB_AHB + 0x31C0 )
#define REG_PUB_AHB_DMC_PORT3_ADDR_REMAP_1   ( CTL_BASE_PUB_AHB + 0x31C4 )
#define REG_PUB_AHB_DMC_PORT4_ADDR_REMAP_1   ( CTL_BASE_PUB_AHB + 0x31C8 )
#define REG_PUB_AHB_DMC_PORT5_ADDR_REMAP_1   ( CTL_BASE_PUB_AHB + 0x31CC )
#define REG_PUB_AHB_DMC_PORT6_ADDR_REMAP_1   ( CTL_BASE_PUB_AHB + 0x31D0 )
#define REG_PUB_AHB_DMC_PORT7_ADDR_REMAP_1   ( CTL_BASE_PUB_AHB + 0x31D4 )
#define REG_PUB_AHB_DMC_MPU_INT              ( CTL_BASE_PUB_AHB + 0x31D8 )
#define REG_PUB_AHB_DMC_PORT0_MPU_VIO_WADDR  ( CTL_BASE_PUB_AHB + 0x3200 )
#define REG_PUB_AHB_DMC_PORT0_MPU_VIO_RADDR  ( CTL_BASE_PUB_AHB + 0x3204 )
#define REG_PUB_AHB_DMC_PORT1_MPU_VIO_WADDR  ( CTL_BASE_PUB_AHB + 0x3208 )
#define REG_PUB_AHB_DMC_PORT1_MPU_VIO_RADDR  ( CTL_BASE_PUB_AHB + 0x320C )
#define REG_PUB_AHB_DMC_PORT2_MPU_VIO_WADDR  ( CTL_BASE_PUB_AHB + 0x3210 )
#define REG_PUB_AHB_DMC_PORT2_MPU_VIO_RADDR  ( CTL_BASE_PUB_AHB + 0x3214 )
#define REG_PUB_AHB_DMC_PORT3_MPU_VIO_WADDR  ( CTL_BASE_PUB_AHB + 0x3218 )
#define REG_PUB_AHB_DMC_PORT3_MPU_VIO_RADDR  ( CTL_BASE_PUB_AHB + 0x321C )
#define REG_PUB_AHB_DMC_PORT4_MPU_VIO_WADDR  ( CTL_BASE_PUB_AHB + 0x3220 )
#define REG_PUB_AHB_DMC_PORT4_MPU_VIO_RADDR  ( CTL_BASE_PUB_AHB + 0x3224 )
#define REG_PUB_AHB_DMC_PORT5_MPU_VIO_WADDR  ( CTL_BASE_PUB_AHB + 0x3228 )
#define REG_PUB_AHB_DMC_PORT5_MPU_VIO_RADDR  ( CTL_BASE_PUB_AHB + 0x322C )
#define REG_PUB_AHB_DMC_PORT6_MPU_VIO_WADDR  ( CTL_BASE_PUB_AHB + 0x3230 )
#define REG_PUB_AHB_DMC_PORT6_MPU_VIO_RADDR  ( CTL_BASE_PUB_AHB + 0x3234 )
#define REG_PUB_AHB_DMC_PORT7_MPU_VIO_WADDR  ( CTL_BASE_PUB_AHB + 0x3238 )
#define REG_PUB_AHB_DMC_PORT7_MPU_VIO_RADDR  ( CTL_BASE_PUB_AHB + 0x323C )
#define REG_PUB_AHB_DMC_PORT0_MPU_VIO_WCMD   ( CTL_BASE_PUB_AHB + 0x3240 )
#define REG_PUB_AHB_DMC_PORT0_MPU_VIO_RCMD   ( CTL_BASE_PUB_AHB + 0x3244 )
#define REG_PUB_AHB_DMC_PORT1_MPU_VIO_WCMD   ( CTL_BASE_PUB_AHB + 0x3248 )
#define REG_PUB_AHB_DMC_PORT1_MPU_VIO_RCMD   ( CTL_BASE_PUB_AHB + 0x324C )
#define REG_PUB_AHB_DMC_PORT2_MPU_VIO_WCMD   ( CTL_BASE_PUB_AHB + 0x3250 )
#define REG_PUB_AHB_DMC_PORT2_MPU_VIO_RCMD   ( CTL_BASE_PUB_AHB + 0x3254 )
#define REG_PUB_AHB_DMC_PORT3_MPU_VIO_WCMD   ( CTL_BASE_PUB_AHB + 0x3258 )
#define REG_PUB_AHB_DMC_PORT3_MPU_VIO_RCMD   ( CTL_BASE_PUB_AHB + 0x325C )
#define REG_PUB_AHB_DMC_PORT4_MPU_VIO_WCMD   ( CTL_BASE_PUB_AHB + 0x3260 )
#define REG_PUB_AHB_DMC_PORT4_MPU_VIO_RCMD   ( CTL_BASE_PUB_AHB + 0x3264 )
#define REG_PUB_AHB_DMC_PORT5_MPU_VIO_WCMD   ( CTL_BASE_PUB_AHB + 0x3268 )
#define REG_PUB_AHB_DMC_PORT5_MPU_VIO_RCMD   ( CTL_BASE_PUB_AHB + 0x326C )
#define REG_PUB_AHB_DMC_PORT6_MPU_VIO_WCMD   ( CTL_BASE_PUB_AHB + 0x3270 )
#define REG_PUB_AHB_DMC_PORT6_MPU_VIO_RCMD   ( CTL_BASE_PUB_AHB + 0x3274 )
#define REG_PUB_AHB_DMC_PORT7_MPU_VIO_WCMD   ( CTL_BASE_PUB_AHB + 0x3278 )
#define REG_PUB_AHB_DMC_PORT7_MPU_VIO_RCMD   ( CTL_BASE_PUB_AHB + 0x327C )
#define REG_PUB_AHB_PUB_DMC_MPU_INT          ( CTL_BASE_PUB_AHB + 0x3280 )
#define REG_PUB_AHB_AAM_LPC_CTRL_M0          ( CTL_BASE_PUB_AHB + 0x3800 )
#define REG_PUB_AHB_AAM_LPC_CTRL_M1          ( CTL_BASE_PUB_AHB + 0x3804 )
#define REG_PUB_AHB_AAM_LPC_CTRL_S0          ( CTL_BASE_PUB_AHB + 0x3808 )
#define REG_PUB_AHB_GGM_LPC_CTRL_M0          ( CTL_BASE_PUB_AHB + 0x3810 )
#define REG_PUB_AHB_GGM_LPC_CTRL_M1          ( CTL_BASE_PUB_AHB + 0x3814 )
#define REG_PUB_AHB_GGM_LPC_CTRL_S0          ( CTL_BASE_PUB_AHB + 0x3818 )

/* REG_PUB_AHB_BUSMON_CNT_START */

#define BIT_PUB_AHB_PUB_BUSMON_CNT_START       BIT(0)

/* REG_PUB_AHB_BUSMON_CFG */

#define BIT_PUB_AHB_PUB_BUSMON9_EB             BIT(25)
#define BIT_PUB_AHB_PUB_BUSMON8_EB             BIT(24)
#define BIT_PUB_AHB_PUB_BUSMON7_EB             BIT(23)
#define BIT_PUB_AHB_PUB_BUSMON6_EB             BIT(22)
#define BIT_PUB_AHB_PUB_BUSMON5_EB             BIT(21)
#define BIT_PUB_AHB_PUB_BUSMON4_EB             BIT(20)
#define BIT_PUB_AHB_PUB_BUSMON3_EB             BIT(19)
#define BIT_PUB_AHB_PUB_BUSMON2_EB             BIT(18)
#define BIT_PUB_AHB_PUB_BUSMON1_EB             BIT(17)
#define BIT_PUB_AHB_PUB_BUSMON0_EB             BIT(16)
#define BIT_PUB_AHB_PUB_BUSMON9_SOFT_RST       BIT(9)
#define BIT_PUB_AHB_PUB_BUSMON8_SOFT_RST       BIT(8)
#define BIT_PUB_AHB_PUB_BUSMON7_SOFT_RST       BIT(7)
#define BIT_PUB_AHB_PUB_BUSMON6_SOFT_RST       BIT(6)
#define BIT_PUB_AHB_PUB_BUSMON5_SOFT_RST       BIT(5)
#define BIT_PUB_AHB_PUB_BUSMON4_SOFT_RST       BIT(4)
#define BIT_PUB_AHB_PUB_BUSMON3_SOFT_RST       BIT(3)
#define BIT_PUB_AHB_PUB_BUSMON2_SOFT_RST       BIT(2)
#define BIT_PUB_AHB_PUB_BUSMON1_SOFT_RST       BIT(1)
#define BIT_PUB_AHB_PUB_BUSMON0_SOFT_RST       BIT(0)

/* REG_PUB_AHB_DMC_PORT_REMAP_EN */

#define BIT_PUB_AHB_DMC_PORTS_REMAP_EN(x)      (((x) & 0xFFFFF))

/* REG_PUB_AHB_DMC_PORTS_MPU_EN */

#define BIT_PUB_AHB_DMC_PORTS_MPU_EN(x)        (((x) & 0xFFFFF))

/* REG_PUB_AHB_DMC_PORT0_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT0_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT1_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT1_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT2_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT2_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT3_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT3_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT4_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT4_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT5_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT5_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT6_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT6_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT7_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT7_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT8_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT8_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT9_ADDR_REMAP_0 */

#define BIT_PUB_AHB_DMC_PORT9_ADDR_REMAP_0(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT0_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT0_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT1_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT1_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT2_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT2_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT3_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT3_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT4_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT4_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT5_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT5_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT6_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT6_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT7_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT7_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT8_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT8_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT9_MPU_RANGE */

#define BIT_PUB_AHB_DMC_PORT9_MPU_RANGE(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT0_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT0_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT1_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT1_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT2_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT2_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT3_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT3_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT4_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT4_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT5_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT5_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT6_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT6_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT7_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT7_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT8_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT8_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT9_DUMP_ADDR */

#define BIT_PUB_AHB_DMC_PORT9_DUMP_ADDR(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_SYS_ENDIAN_CTRL */

#define BIT_PUB_AHB_ENDIAN_SEL_CH9             BIT(0)

/* REG_PUB_AHB_DMC_DUMMY_REG0 */

#define BIT_PUB_AHB_DMC_DUMMY_REG0(x)          (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_DUMMY_REG1 */

#define BIT_PUB_AHB_DMC_DUMMY_REG1(x)          (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_QOS_SEL */

#define BIT_PUB_AHB_DMC_QOS_SEL(x)             (((x) & 0x1FF) << 16)
#define BIT_PUB_AHB_DMC_ID_SEL(x)              (((x) & 0x1FF))

/* REG_PUB_AHB_DMC_ARQOS_0_7 */

#define BIT_PUB_AHB_DMC_ARQOS_7(x)             (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_ARQOS_6(x)             (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_ARQOS_4(x)             (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_ARQOS_3(x)             (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_ARQOS_1(x)             (((x) & 0xF) << 4)

/* REG_PUB_AHB_DMC_ARQOS_8 */


/* REG_PUB_AHB_DMC_AWQOS_0_7 */

#define BIT_PUB_AHB_DMC_AWQOS_7(x)             (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_AWQOS_6(x)             (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_AWQOS_4(x)             (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_AWQOS_3(x)             (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_AWQOS_1(x)             (((x) & 0xF) << 4)

/* REG_PUB_AHB_DMC_AWQOS_8 */


/* REG_PUB_AHB_DMC_ARQOS_0_ID */


/* REG_PUB_AHB_DMC_ARQOS_1_ID */

#define BIT_PUB_AHB_DMC_ARQOS_1_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_ARQOS_1_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_ARQOS_1_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_ARQOS_1_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_ARQOS_1_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_ARQOS_1_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_ARQOS_1_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_ARQOS_1_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_ARQOS_2_ID */


/* REG_PUB_AHB_DMC_ARQOS_3_ID */

#define BIT_PUB_AHB_DMC_ARQOS_3_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_ARQOS_3_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_ARQOS_3_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_ARQOS_3_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_ARQOS_3_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_ARQOS_3_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_ARQOS_3_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_ARQOS_3_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_ARQOS_4_ID */

#define BIT_PUB_AHB_DMC_ARQOS_4_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_ARQOS_4_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_ARQOS_4_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_ARQOS_4_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_ARQOS_4_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_ARQOS_4_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_ARQOS_4_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_ARQOS_4_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_ARQOS_5_ID */

#define BIT_PUB_AHB_DMC_ARQOS_5_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_ARQOS_5_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_ARQOS_5_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_ARQOS_5_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_ARQOS_5_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_ARQOS_5_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_ARQOS_5_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_ARQOS_5_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_ARQOS_6_ID */

#define BIT_PUB_AHB_DMC_ARQOS_6_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_ARQOS_6_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_ARQOS_6_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_ARQOS_6_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_ARQOS_6_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_ARQOS_6_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_ARQOS_6_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_ARQOS_6_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_ARQOS_7_ID */

#define BIT_PUB_AHB_DMC_ARQOS_7_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_ARQOS_7_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_ARQOS_7_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_ARQOS_7_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_ARQOS_7_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_ARQOS_7_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_ARQOS_7_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_ARQOS_7_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_ARQOS_8_ID */


/* REG_PUB_AHB_DMC_AWQOS_0_ID */


/* REG_PUB_AHB_DMC_AWQOS_1_ID */

#define BIT_PUB_AHB_DMC_AWQOS_1_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_AWQOS_1_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_AWQOS_1_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_AWQOS_1_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_AWQOS_1_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_AWQOS_1_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_AWQOS_1_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_AWQOS_1_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_AWQOS_2_ID */


/* REG_PUB_AHB_DMC_AWQOS_3_ID */

#define BIT_PUB_AHB_DMC_AWQOS_3_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_AWQOS_3_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_AWQOS_3_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_AWQOS_3_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_AWQOS_3_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_AWQOS_3_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_AWQOS_3_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_AWQOS_3_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_AWQOS_4_ID */

#define BIT_PUB_AHB_DMC_AWQOS_4_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_AWQOS_4_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_AWQOS_4_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_AWQOS_4_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_AWQOS_4_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_AWQOS_4_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_AWQOS_4_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_AWQOS_4_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_AWQOS_5_ID */


/* REG_PUB_AHB_DMC_AWQOS_6_ID */

#define BIT_PUB_AHB_DMC_AWQOS_6_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_AWQOS_6_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_AWQOS_6_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_AWQOS_6_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_AWQOS_6_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_AWQOS_6_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_AWQOS_6_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_AWQOS_6_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_AWQOS_7_ID */

#define BIT_PUB_AHB_DMC_AWQOS_7_ID7(x)         (((x) & 0xF) << 28)
#define BIT_PUB_AHB_DMC_AWQOS_7_ID6(x)         (((x) & 0xF) << 24)
#define BIT_PUB_AHB_DMC_AWQOS_7_ID5(x)         (((x) & 0xF) << 20)
#define BIT_PUB_AHB_DMC_AWQOS_7_ID4(x)         (((x) & 0xF) << 16)
#define BIT_PUB_AHB_DMC_AWQOS_7_ID3(x)         (((x) & 0xF) << 12)
#define BIT_PUB_AHB_DMC_AWQOS_7_ID2(x)         (((x) & 0xF) << 8)
#define BIT_PUB_AHB_DMC_AWQOS_7_ID1(x)         (((x) & 0xF) << 4)
#define BIT_PUB_AHB_DMC_AWQOS_7_ID0(x)         (((x) & 0xF))

/* REG_PUB_AHB_DMC_AWQOS_8_ID */


/* REG_PUB_AHB_DMC_EXT_LPCTRL_CFG */

#define BIT_PUB_AHB_SOFT_CMD_NUM(x)            (((x) & 0x7) << 8)
#define BIT_PUB_AHB_SOFT_CMD_FC_SEL(x)         (((x) & 0x3) << 4)
#define BIT_PUB_AHB_SOFT_CMD_RESP              BIT(3)
#define BIT_PUB_AHB_SOFT_CMD_DONE              BIT(2)
#define BIT_PUB_AHB_SOFT_CMD_START             BIT(0)

/* REG_PUB_AHB_DMC_EXT_LPCTRL_SEQL */

#define BIT_PUB_AHB_SOFT_CMD_SEQL(x)           (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_EXT_LPCTRL_SEQH */

#define BIT_PUB_AHB_SOFT_CMD_SEQH(x)           (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_EXT_LPCTRL_STEP */

#define BIT_PUB_AHB_SOFT_CMD_STEP(x)           (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_QOS_SELECT */

#define BIT_PUB_AHB_DRAM_SPACE                 BIT(5)
#define BIT_PUB_AHB_AP_AON_QOS_SEL             BIT(4)
#define BIT_PUB_AHB_CPU_QOS_SEL                BIT(3)
#define BIT_PUB_AHB_GGM_QOS_SEL                BIT(2)
#define BIT_PUB_AHB_PUBCP_QOS_SEL              BIT(1)
#define BIT_PUB_AHB_WTLCP_QOS_SEL              BIT(0)

/* REG_PUB_AHB_DMC_PORTS_MPU_SEL */

#define BIT_PUB_AHB_DMC_PORTS_MPU_SEL(x)       (((x) & 0xFFFFF))

/* REG_PUB_AHB_DMC_PORT0_ADDR_REMAP_1 */

#define BIT_PUB_AHB_DMC_PORT0_ADDR_REMAP_1(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT1_ADDR_REMAP_1 */

#define BIT_PUB_AHB_DMC_PORT1_ADDR_REMAP_1(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT2_ADDR_REMAP_1 */

#define BIT_PUB_AHB_DMC_PORT2_ADDR_REMAP_1(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT3_ADDR_REMAP_1 */

#define BIT_PUB_AHB_DMC_PORT3_ADDR_REMAP_1(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT4_ADDR_REMAP_1 */

#define BIT_PUB_AHB_DMC_PORT4_ADDR_REMAP_1(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT5_ADDR_REMAP_1 */

#define BIT_PUB_AHB_DMC_PORT5_ADDR_REMAP_1(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT6_ADDR_REMAP_1 */

#define BIT_PUB_AHB_DMC_PORT6_ADDR_REMAP_1(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT7_ADDR_REMAP_1 */

#define BIT_PUB_AHB_DMC_PORT7_ADDR_REMAP_1(x)  (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_MPU_INT */

#define BIT_PUB_AHB_DMC_MPU_VIO_REQ_INT_RW(x)  (((x) & 0xFFFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_INT_CLR        BIT(1)
#define BIT_PUB_AHB_DMC_MPU_VIO_INT_EN         BIT(0)

/* REG_PUB_AHB_DMC_PORT0_MPU_VIO_WADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWADDR0(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT0_MPU_VIO_RADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARADDR0(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT1_MPU_VIO_WADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWADDR1(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT1_MPU_VIO_RADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARADDR1(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT2_MPU_VIO_WADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWADDR2(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT2_MPU_VIO_RADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARADDR2(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT3_MPU_VIO_WADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWADDR3(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT3_MPU_VIO_RADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARADDR3(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT4_MPU_VIO_WADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWADDR4(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT4_MPU_VIO_RADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARADDR4(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT5_MPU_VIO_WADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWADDR5(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT5_MPU_VIO_RADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARADDR5(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT6_MPU_VIO_WADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWADDR6(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT6_MPU_VIO_RADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARADDR6(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT7_MPU_VIO_WADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWADDR7(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT7_MPU_VIO_RADDR */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARADDR7(x)     (((x) & 0xFFFFFFFF))

/* REG_PUB_AHB_DMC_PORT0_MPU_VIO_WCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWID0(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWBURST0(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWSIZE0(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWLEN0(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT0_MPU_VIO_RCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARID0(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARBURST0(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARSIZE0(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARLEN0(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT1_MPU_VIO_WCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWID1(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWBURST1(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWSIZE1(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWLEN1(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT1_MPU_VIO_RCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARID1(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARBURST1(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARSIZE1(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARLEN1(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT2_MPU_VIO_WCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWID2(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWBURST2(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWSIZE2(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWLEN2(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT2_MPU_VIO_RCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARID2(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARBURST2(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARSIZE2(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARLEN2(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT3_MPU_VIO_WCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWID3(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWBURST3(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWSIZE3(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWLEN3(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT3_MPU_VIO_RCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARID3(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARBURST3(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARSIZE3(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARLEN3(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT4_MPU_VIO_WCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWID4(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWBURST4(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWSIZE4(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWLEN4(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT4_MPU_VIO_RCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARID4(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARBURST4(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARSIZE4(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARLEN4(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT5_MPU_VIO_WCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWID5(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWBURST5(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWSIZE5(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWLEN5(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT5_MPU_VIO_RCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARID5(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARBURST5(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARSIZE5(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARLEN5(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT6_MPU_VIO_WCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWID6(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWBURST6(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWSIZE6(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWLEN6(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT6_MPU_VIO_RCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARID6(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARBURST6(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARSIZE6(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARLEN6(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT7_MPU_VIO_WCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_AWID7(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWBURST7(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWSIZE7(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_AWLEN7(x)      (((x) & 0xFF))

/* REG_PUB_AHB_DMC_PORT7_MPU_VIO_RCMD */

#define BIT_PUB_AHB_DMC_MPU_VIO_ARID7(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARBURST7(x)    (((x) & 0x3) << 12)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARSIZE7(x)     (((x) & 0x7) << 8)
#define BIT_PUB_AHB_DMC_MPU_VIO_ARLEN7(x)      (((x) & 0xFF))

/* REG_PUB_AHB_PUB_DMC_MPU_INT */

#define BIT_PUB_AHB_INT_DMC_MPU_VIO            BIT(1)
#define BIT_PUB_AHB_DMC_MPU_VIO_INT_RAW        BIT(0)

/* REG_PUB_AHB_AAM_LPC_CTRL_M0 */

#define BIT_PUB_AHB_AAM_M0_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_PUB_AHB_AAM_M0_IN_LP               BIT(8)
#define BIT_PUB_AHB_AAM_M0_LP_FORCE            BIT(2)
#define BIT_PUB_AHB_AAM_M0_LP_ACTIVE_SYNC_SEL  BIT(1)
#define BIT_PUB_AHB_AAM_M0_LP_EB               BIT(0)

/* REG_PUB_AHB_AAM_LPC_CTRL_M1 */

#define BIT_PUB_AHB_AAM_M1_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_PUB_AHB_AAM_M1_IN_LP               BIT(8)
#define BIT_PUB_AHB_AAM_M1_LP_FORCE            BIT(2)
#define BIT_PUB_AHB_AAM_M1_LP_ACTIVE_SYNC_SEL  BIT(1)
#define BIT_PUB_AHB_AAM_M1_LP_EB               BIT(0)

/* REG_PUB_AHB_AAM_LPC_CTRL_S0 */

#define BIT_PUB_AHB_AAM_S0_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_PUB_AHB_AAM_S0_IN_LP               BIT(8)
#define BIT_PUB_AHB_AAM_S0_LP_FORCE            BIT(2)
#define BIT_PUB_AHB_AAM_S0_LP_ACTIVE_SYNC_SEL  BIT(1)
#define BIT_PUB_AHB_AAM_S0_LP_EB               BIT(0)

/* REG_PUB_AHB_GGM_LPC_CTRL_M0 */

#define BIT_PUB_AHB_GGM_M0_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_PUB_AHB_GGM_M0_IN_LP               BIT(8)
#define BIT_PUB_AHB_GGM_M0_LP_FORCE            BIT(2)
#define BIT_PUB_AHB_GGM_M0_LP_ACTIVE_SYNC_SEL  BIT(1)
#define BIT_PUB_AHB_GGM_M0_LP_EB               BIT(0)

/* REG_PUB_AHB_GGM_LPC_CTRL_M1 */

#define BIT_PUB_AHB_GGM_M1_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_PUB_AHB_GGM_M1_IN_LP               BIT(8)
#define BIT_PUB_AHB_GGM_M1_LP_FORCE            BIT(2)
#define BIT_PUB_AHB_GGM_M1_LP_ACTIVE_SYNC_SEL  BIT(1)
#define BIT_PUB_AHB_GGM_M1_LP_EB               BIT(0)

/* REG_PUB_AHB_GGM_LPC_CTRL_S0 */

#define BIT_PUB_AHB_GGM_S0_LP_NUM(x)           (((x) & 0xFFFF) << 16)
#define BIT_PUB_AHB_GGM_S0_IN_LP               BIT(8)
#define BIT_PUB_AHB_GGM_S0_LP_FORCE            BIT(2)
#define BIT_PUB_AHB_GGM_S0_LP_ACTIVE_SYNC_SEL  BIT(1)
#define BIT_PUB_AHB_GGM_S0_LP_EB               BIT(0)


#endif /* PUB_AHB_H */


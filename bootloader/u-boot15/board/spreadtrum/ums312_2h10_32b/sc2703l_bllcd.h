// SPDX-License-Identifier: GPL-2.0+
/*
 * LCD, WLED device driver registers for SC2703L
 *
 * Copyright (c) 2018 Dialog Semiconductor.
 */

#ifndef __SC2703L_DISPLAY_REGISTERS_H
#define __SC2703L_DISPLAY_REGISTERS_H

//#include <linux/bitops.h>

#define SC2703L_SYSCTRL_EVENT                   0x00
#define SC2703L_SYSCTRL_STATUS                  0x01
#define SC2703L_SYSCTRL_IRQ_MASK                0x02
#define SC2703L_SYSCTRL_CHIP_ID                 0x03
#define SC2703L_SYSCTRL_DISPLAY_ACTIVE          0x08
#define SC2703L_SYSCTRL_DISPLAY_STATUS          0x09
#define SC2703L_SYSCTRL_SEQ_MODE_CONTROL1       0x0a
#define SC2703L_DISPLAY_EVENT_A                 0x40
#define SC2703L_DISPLAY_STATUS_A                0x41
#define SC2703L_DISPLAY_IRQ_MASK_A              0x42
#define SC2703L_DISPLAY_CONFIG1                 0x43
#define SC2703L_DISPLAY_CONFIG2                 0x44
#define SC2703L_DISPLAY_CONFIG3                 0x45
#define SC2703L_DISPLAY_CONFIG4                 0x46
#define SC2703L_DISPLAY_CONFIG5                 0x47
#define SC2703L_DISPLAY_CONFIG6                 0x48
#define SC2703L_DISPLAY_BOOST_VOLTAGE           0x50
#define SC2703L_DISPLAY_BOOST_SLEW_RATE         0x51
#define SC2703L_DISPLAY_BOOST_CONFIG1           0x52
#define SC2703L_DISPLAY_CP_VOLTAGE              0x60
#define SC2703L_DISPLAY_CP_SLEW_RATE            0x61
#define SC2703L_DISPLAY_CP_CONFIG8              0x69
#define SC2703L_DISPLAY_CP_CONFIG9              0x6a
#define SC2703L_DISPLAY_LDO_VOLTAGE             0x73
#define SC2703L_DISPLAY_LDO_SLEW_RATE           0x74
#define SC2703L_WLED_EVENT                      0x80
#define SC2703L_WLED_STATUS                     0x81
#define SC2703L_WLED_IRQ_MASK                   0x82
#define SC2703L_WLED_CONFIG1                    0x83
#define SC2703L_WLED_CONFIG2                    0x84
#define SC2703L_WLED_CONFIG3                    0x85
#define SC2703L_WLED_CONFIG4                    0x86
#define SC2703L_WLED_CONFIG5                    0x87
#define SC2703L_WLED_CONFIG6                    0x88
#define SC2703L_WLED_CONFIG7                    0x89
#define SC2703L_WLED_CONFIG9                    0x8B
#define SC2703L_WLED_BOOST_CONTROL1             0x90
#define SC2703L_WLED_BOOST_CONTROL2             0x91

/* SC2703L_SYSCTRL_EVENT = 0x00 */
#define SC2703L_EVT_VSYS_UV_OT_VREF_FLT_SHIFT         1
#define SC2703L_EVT_VSYS_UV_OT_VREF_FLT_MASK          (0x1 << 1)
#define SC2703L_EVT_CHCR_SHIFT                        2
#define SC2703L_EVT_CHCR_MASK                         (0x1 << 2)
#define SC2703L_EVT_VDDIO_FLT_SHIFT                   3
#define SC2703L_EVT_VDDIO_FLT_MASK                    (0x1 << 3)
#define SC2703L_EVT_SYS_WDT_SHIFT                     4
#define SC2703L_EVT_SYS_WDT_MASK                      (0x1 << 4)
/* SC2703L_SYSCTRL_STATUS = 0x01 */
#define SC2703L_VSYS_UV_OT_VREF_FLT_SHIFT             1
#define SC2703L_VSYS_UV_OT_VREF_FLT_MASK              (0x1 << 1)
#define SC2703L_VDDIO_FLT_SHIFT                       3
#define SC2703L_VDDIO_FLT_MASK                        (0x1 << 3)
#define SC2703L_SYS_WDT_TIMEOUT_SHIFT                 4
#define SC2703L_SYS_WDT_TIMEOUT_MASK                  (0x1 << 4)
/* SC2703L_SYSCTRL_IRQ_MASK = 0x02 */
#define SC2703L_M_VSYS_UV_OT_VREF_FLT_SHIFT           1
#define SC2703L_M_VSYS_UV_OT_VREF_FLT_MASK            (0x1 << 1)
#define SC2703L_M_CHCR_SHIFT                          2
#define SC2703L_M_CHCR_MASK                           (0x1 << 2)
#define SC2703L_M_VDDIO_FLT_SHIFT                     3
#define SC2703L_M_VDDIO_FLT_MASK                      (0x1 << 3)
#define SC2703L_M_SYS_WDT_SHIFT                       4
#define SC2703L_M_SYS_WDT_MASK                        (0x1 << 4)
/* SC2703L_SYSCTRL_CHIP_ID = 0x03 */
#define SC2703L_MRC_SHIFT                             0
#define SC2703L_MRC_MASK                              (0xF << 0)
#define SC2703L_TRC_SHIFT                             4
#define SC2703L_TRC_MASK                              (0xF << 4)
/* SC2703L_SYSCTRL_DISPLAY_ACTIVE = 0x08 */
#define SC2703L_DISPLAY_EN_SHIFT                      0
#define SC2703L_DISPLAY_EN_MASK                       (0x1 << 0)
#define SC2703L_WLED_EN_SHIFT                         1
#define SC2703L_WLED_EN_MASK                          (0x1 << 1)
/* SC2703L_SYSCTRL_DISPLAY_STATUS = 0x09 */
#define SC2703L_DISPLAY_IS_ACTIVE_SHIFT               0
#define SC2703L_DISPLAY_IS_ACTIVE_MASK                (0x1 << 0)
#define SC2703L_WLED_IS_ACTIVE_SHIFT                  1
#define SC2703L_WLED_IS_ACTIVE_MASK                   (0x1 << 1)
#define SC2703L_DISPLAY_IS_PG_SHIFT                   4
#define SC2703L_DISPLAY_IS_PG_MASK                    (0x1 << 4)
#define SC2703L_WLED_IS_PG_SHIFT                      5
#define SC2703L_WLED_IS_PG_MASK                       (0x1 << 5)
/* SC2703L_SYSCTRL_SEQ_MODE_CONTROL1 = 0x0a */
#define SC2703L_COREBUCK_POWER_CTRL_SELECT_SHIFT      0
#define SC2703L_COREBUCK_POWER_CTRL_SELECT_MASK       (0x1 << 0)
#define SC2703L_COREBUCK_RST_N_CTRL_SELECT_SHIFT      1
#define SC2703L_COREBUCK_RST_N_CTRL_SELECT_MASK       (0x1 << 1)
#define SC2703L_DISPLAY_POWER_CTRL_SELECT_SHIFT       2
#define SC2703L_DISPLAY_POWER_CTRL_SELECT_MASK        (0x1 << 2)
#define SC2703L_WLED_POWER_CTRL_SELECT_SHIFT          3
#define SC2703L_WLED_POWER_CTRL_SELECT_MASK           (0x1 << 3)
#define SC2703L_COREBUCK_EN_CTRL_SELECT_SHIFT         4
#define SC2703L_COREBUCK_EN_CTRL_SELECT_MASK          (0x1 << 4)
/* SC2703L_DISPLAY_EVENT_A = 0x40 */
#define SC2703L_EVT_BOOST_OVP_SHIFT                   0
#define SC2703L_EVT_BOOST_OVP_MASK                    (0x1 << 0)
#define SC2703L_EVT_BOOST_OCP_SHIFT                   1
#define SC2703L_EVT_BOOST_OCP_MASK                    (0x1 << 1)
#define SC2703L_EVT_BOOST_UVP_SHIFT                   2
#define SC2703L_EVT_BOOST_UVP_MASK                    (0x1 << 2)
#define SC2703L_EVT_DLDO_SC_SHIFT                     3
#define SC2703L_EVT_DLDO_SC_MASK                      (0x1 << 3)
#define SC2703L_EVT_CP_OVP_SHIFT                      4
#define SC2703L_EVT_CP_OVP_MASK                       (0x1 << 4)
#define SC2703L_EVT_CP_UVP_SHIFT                      5
#define SC2703L_EVT_CP_UVP_MASK                       (0x1 << 5)
/* SC2703L_DISPLAY_STATUS_A = 0x41 */
#define SC2703L_BOOST_OVP_SHIFT                       0
#define SC2703L_BOOST_OVP_MASK                        (0x1 << 0)
#define SC2703L_BOOST_OCP_SHIFT                       1
#define SC2703L_BOOST_OCP_MASK                        (0x1 << 1)
#define SC2703L_BOOST_UVP_SHIFT                       2
#define SC2703L_BOOST_UVP_MASK                        (0x1 << 2)
#define SC2703L_DLDO_SC_SHIFT                         3
#define SC2703L_DLDO_SC_MASK                          (0x1 << 3)
#define SC2703L_CP_OVP_SHIFT                          4
#define SC2703L_CP_OVP_MASK                           (0x1 << 4)
#define SC2703L_CP_UVP_SHIFT                          5
#define SC2703L_CP_UVP_MASK                           (0x1 << 5)
/* SC2703L_DISPLAY_IRQ_MASK_A = 0x42 */
#define SC2703L_M_BOOST_OVP_SHIFT                     0
#define SC2703L_M_BOOST_OVP_MASK                      (0x1 << 0)
#define SC2703L_M_BOOST_OCP_SHIFT                     1
#define SC2703L_M_BOOST_OCP_MASK                      (0x1 << 1)
#define SC2703L_M_BOOST_UVP_SHIFT                     2
#define SC2703L_M_BOOST_UVP_MASK                      (0x1 << 2)
#define SC2703L_M_DLDO_SC_SHIFT                       3
#define SC2703L_M_DLDO_SC_MASK                        (0x1 << 3)
#define SC2703L_M_CP_OVP_SHIFT                        4
#define SC2703L_M_CP_OVP_MASK                         (0x1 << 4)
#define SC2703L_M_CP_UVP_SHIFT                        5
#define SC2703L_M_CP_UVP_MASK                         (0x1 << 5)
/* SC2703L_DISPLAY_CONFIG1 = 0x43 */
#define SC2703L_SEQ_UP_SIMULTANOUS_SHIFT              0
#define SC2703L_SEQ_UP_SIMULTANOUS_MASK               (0x1 << 0)
#define SC2703L_SEQ_DN_SIMULTANOUS_SHIFT              1
#define SC2703L_SEQ_DN_SIMULTANOUS_MASK               (0x1 << 1)
#define SC2703L_UP_VPOS_VNEG_SHIFT                    2
#define SC2703L_UP_VPOS_VNEG_MASK                     (0x1 << 2)
#define SC2703L_DN_VPOS_VNEG_SHIFT                    3
#define SC2703L_DN_VPOS_VNEG_MASK                     (0x1 << 3)
/* SC2703L_DISPLAY_CONFIG2 = 0x44 */
#define SC2703L_UP_DELAY_SRC_SHIFT                    0
#define SC2703L_UP_DELAY_SRC_MASK                     (0x7F << 0)
#define SC2703L_UP_DELAY_SRC_SCALE_SHIFT              7
#define SC2703L_UP_DELAY_SRC_SCALE_MASK               (0x1 << 7)
/* SC2703L_DISPLAY_CONFIG3 = 0x45 */
#define SC2703L_UP_DELAY_POS_NEG_SHIFT                0
#define SC2703L_UP_DELAY_POS_NEG_MASK                 (0x7F << 0)
#define SC2703L_UP_DELAY_POS_NEG_SCALE_SHIFT          7
#define SC2703L_UP_DELAY_POS_NEG_SCALE_MASK           (0x1 << 7)
/* SC2703L_DISPLAY_CONFIG4 = 0x46 */
#define SC2703L_DN_DELAY_SRC_SHIFT                    0
#define SC2703L_DN_DELAY_SRC_MASK                     (0x7F << 0)
#define SC2703L_DN_DELAY_SRC_SCALE_SHIFT              7
#define SC2703L_DN_DELAY_SRC_SCALE_MASK               (0x1 << 7)
/* SC2703L_DISPLAY_CONFIG5 = 0x47 */
#define SC2703L_DN_DELAY_POS_NEG_SHIFT                0
#define SC2703L_DN_DELAY_POS_NEG_MASK                 (0x7F << 0)
#define SC2703L_DN_DELAY_POS_NEG_SCALE_SHIFT          7
#define SC2703L_DN_DELAY_POS_NEG_SCALE_MASK           (0x1 << 7)
/* SC2703L_DISPLAY_CONFIG6 = 0x48 */
#define SC2703L_BOOST_MAP_SHIFT                       0
#define SC2703L_BOOST_MAP_MASK                        (0x3 << 0)
#define SC2703L_LDO_MAP_SHIFT                         2
#define SC2703L_LDO_MAP_MASK                          (0x3 << 2)
#define SC2703L_CP_MAP_SHIFT                          4
#define SC2703L_CP_MAP_MASK                           (0x3 << 4)
#define SC2703L_MAP_SWITCH_ENABLE_SHIFT               7
#define SC2703L_MAP_SWITCH_ENABLE_MASK                (0x1 << 7)
/* SC2703L_DISPLAY_BOOST_VOLTAGE = 0x50 */
#define SC2703L_BOOST_VOLTAGE_SHIFT                   0
#define SC2703L_BOOST_VOLTAGE_MASK                    (0xFF << 0)
/* SC2703L_DISPLAY_BOOST_SLEW_RATE = 0x51 */
#define SC2703L_BOOST_SLEW_RATE_SHIFT                 0
#define SC2703L_BOOST_SLEW_RATE_MASK                  (0x7 << 0)
/* SC2703L_DISPLAY_BOOST_CONFIG1 = 0x52 */
#define SC2703L_BOOST_SEL_POC_LIMIT_SHIFT             0
#define SC2703L_BOOST_SEL_POC_LIMIT_MASK              (0x7 << 0)
/* SC2703L_DISPLAY_CP_VOLTAGE = 0x60 */
#define SC2703L_CP_VOLTAGE_SHIFT                      0
#define SC2703L_CP_VOLTAGE_MASK                       (0xFF << 0)
/* SC2703L_DISPLAY_CP_SLEW_RATE = 0x61 */
#define SC2703L_CP_SLEW_RATE_SHIFT                    0
#define SC2703L_CP_SLEW_RATE_MASK                     (0x7 << 0)
/* SC2703L_DISPLAY_CP_CONFIG8 = 0x69 */
#define SC2703L_CP_SEL_RON_MN2_NM_SHIFT               2
#define SC2703L_CP_SEL_RON_MN2_NM_MASK                (0x3 << 2)
#define SC2703L_CP_SEL_RON_MP1_NM_SHIFT               6
#define SC2703L_CP_SEL_RON_MP1_NM_MASK                (0x3 << 6)
/* SC2703L_DISPLAY_CP_CONFIG9 = 0x6a */
#define SC2703L_CP_DIN_SPARE_SHIFT                    0
#define SC2703L_CP_DIN_SPARE_MASK                     (0xF << 0)
#define SC2703L_CP_OUTN_SHRT_PNGD_N5V_SHIFT           5
#define SC2703L_CP_OUTN_SHRT_PNGD_N5V_MASK            (0x1 << 5)
/* SC2703L_DISPLAY_LDO_VOLTAGE = 0x73 */
#define SC2703L_LDO_VOLTAGE_SHIFT                     0
#define SC2703L_LDO_VOLTAGE_MASK                      (0xFF << 0)
/* SC2703L_DISPLAY_LDO_SLEW_RATE = 0x74 */
#define SC2703L_LDO_SLEW_RATE_SHIFT                   0
#define SC2703L_LDO_SLEW_RATE_MASK                    (0x7 << 0)
/* SC2703L_WLED_EVENT = 0x80 */
#define SC2703L_EVT_WLED_OC_SHIFT                     0
#define SC2703L_EVT_WLED_OC_MASK                      (0x1 << 0)
#define SC2703L_EVT_WLED_OV_SHIFT                     1
#define SC2703L_EVT_WLED_OV_MASK                      (0x1 << 1)
#define SC2703L_EVT_WLED_UV_SHIFT                     2
#define SC2703L_EVT_WLED_UV_MASK                      (0x1 << 2)
/* SC2703L_WLED_STATUS = 0x81 */
#define SC2703L_WLED_OC_SHIFT                         0
#define SC2703L_WLED_OC_MASK                          (0x1 << 0)
#define SC2703L_WLED_OV_SHIFT                         1
#define SC2703L_WLED_OV_MASK                          (0x1 << 1)
#define SC2703L_WLED_UV_SHIFT                         2
#define SC2703L_WLED_UV_MASK                          (0x1 << 2)
/* SC2703L_WLED_IRQ_MASK = 0x82 */
#define SC2703L_M_WLED_OC_SHIFT                       0
#define SC2703L_M_WLED_OC_MASK                        (0x1 << 0)
#define SC2703L_M_WLED_OV_SHIFT                       1
#define SC2703L_M_WLED_OV_MASK                        (0x1 << 1)
#define SC2703L_M_WLED_UV_SHIFT                       2
#define SC2703L_M_WLED_UV_MASK                        (0x1 << 2)
/* SC2703L_WLED_CONFIG1 = 0x83 */
#define SC2703L_WLED_MODE_SHIFT                       0
#define SC2703L_WLED_MODE_MASK                        (0x4 << 0)
#define SC2703L_WLED_IDAC_EN_SHIFT                    3
#define SC2703L_WLED_IDAC_EN_MASK                     (0x1 << 3)
#define SC2703L_IDAC_LINEAR_SHIFT                     4
#define SC2703L_IDAC_LINEAR_MASK                      (0x1 << 4)
/* SC2703L_WLED_CONFIG2 = 0x84 */
#define SC2703L_IDAC_TARGET_SHIFT                     0
#define SC2703L_IDAC_TARGET_MASK                      (0xFF << 0)
/* SC2703L_WLED_CONFIG3 = 0x85 */
#define SC2703L_IDAC_RAMP_RATE_SHIFT                  0
#define SC2703L_IDAC_RAMP_RATE_MASK                   (0xF << 0)
#define SC2703L_PWM_IN_FREQ_RANGE_SHIFT               4
#define SC2703L_PWM_IN_FREQ_RANGE_MASK                (0x1 << 4)
#define SC2703L_PWM_OUT_FREQ_STEP_SHIFT               5
#define SC2703L_PWM_OUT_FREQ_STEP_MASK                (0x7 << 5)
/* SC2703L_WLED_CONFIG4 = 0x86 */
#define SC2703L_PWM_IN_DUTY_THRESHOLD_SHIFT           0
#define SC2703L_PWM_IN_DUTY_THRESHOLD_MASK            (0xFF << 0)
/* SC2703L_WLED_CONFIG5 = 0x87 */
#define SC2703L_PWM_OUT_DUTY_SHIFT                    0
#define SC2703L_PWM_OUT_DUTY_MASK                     (0xFF << 0)
/* SC2703L_WLED_CONFIG6 = 0x88 */
#define SC2703L_WLED_PANIC_VTH_SHIFT                  0
#define SC2703L_WLED_PANIC_VTH_MASK                   (0x3 << 0)
#define SC2703L_WLED_PANIC_EN_SHIFT                   2
#define SC2703L_WLED_PANIC_EN_MASK                    (0x1 << 2)
/* SC2703L_WLED_CONFIG7 = 0x89 */
#define SC2703L_IDAC_RAMP_DIS_SHIFT                   0
#define SC2703L_IDAC_RAMP_DIS_MASK                    (0x1 << 0)
#define SC2703L_PWM_THRESHOLD_PLUS_SHIFT              1
#define SC2703L_PWM_THRESHOLD_PLUS_MASK               (0x1 << 1)
#define SC2703L_WLED_DISCHARGE_SEL_SHIFT              2
#define SC2703L_WLED_DISCHARGE_SEL_MASK               (0x7 << 2)
#define SC2703L_WLED_PANIC_PERIOD_SHIFT               5
#define SC2703L_WLED_PANIC_PERIOD_MASK                (0x3 << 5)
/* SC2703L_WLED_BOOST_CONTROL1 = 0x90 */
#define SC2703L_SEL_POC_LIMIT_SHIFT                   0
#define SC2703L_SEL_POC_LIMIT_MASK                    (0x3 << 0)
#define SC2703L_SEL_OVP_TH_SHIFT                      2
#define SC2703L_SEL_OVP_TH_MASK                       (0x1 << 2)
#define SC2703L_PANIC_FB_SEL_SHIFT                    3
#define SC2703L_PANIC_FB_SEL_MASK                     (0x3 << 3)
#define SC2703L_VDAC_SLEW_RATE_SHIFT                  5
#define SC2703L_VDAC_SLEW_RATE_MASK                   (0x7 << 5)
/* SC2703L_WLED_BOOST_CONTROL2 = 0x91 */
#define SC2703L_VDAC_SEL_SHIFT                        0
#define SC2703L_VDAC_SEL_MASK                         (0xFF << 0)

#endif /* __SC2703L_DISPLAY_REGISTERS_H */

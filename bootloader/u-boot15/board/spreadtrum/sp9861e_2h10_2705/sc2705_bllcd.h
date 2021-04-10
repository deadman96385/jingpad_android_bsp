/*
 * registers.h - LCD, WLED REGISTERS H for SC2705
 * Copyright (c) 2017 Dialog Semiconductor.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __SC2705_DISPLAY_REGISTERS_H
#define __SC2705_DISPLAY_REGISTERS_H

#include <linux/bitops.h>

#define SC2705_LCD_STATUS_A                       0x00
#define SC2705_LCD_STATUS_B                       0x01
#define SC2705_LCD_STATUS_C                       0x02
#define SC2705_LCD_STATUS_D                       0x03
#define SC2705_LCD_STATUS_E                       0x04
#define SC2705_LCD_EVENT_A                        0x05
#define SC2705_LCD_EVENT_B                        0x06
#define SC2705_LCD_EVENT_C                        0x07
#define SC2705_LCD_EVENT_D                        0x08
#define SC2705_LCD_EVENT_E                        0x09
#define SC2705_LCD_IRQ_MASK_A                     0x0A
#define SC2705_LCD_IRQ_MASK_B                     0x0B
#define SC2705_LCD_IRQ_MASK_C                     0x0C
#define SC2705_LCD_IRQ_MASK_D                     0x0D
#define SC2705_LCD_IRQ_MASK_E                     0x0E
#define SC2705_I2C_CONFIG                     0x0F
#define SC2705_SUPPLY_SEQ_MODE_CONTROL        0x18
#define SC2705_SUPPLY_ACTIVE                  0x19
#define SC2705_SUPPLY_STATUS                  0x1A
#define SC2705_WLED_CONFIG1                   0x20
#define SC2705_WLED_CONFIG2                   0x21
#define SC2705_WLED_CONFIG3                   0x22
#define SC2705_WLED_CONFIG4                   0x23
#define SC2705_WLED_CONFIG5                   0x24
#define SC2705_WLED_CONFIG6                   0x25
#define SC2705_WLED_CONFIG7                   0x26
#define SC2705_WLED_CONFIG8                   0x27
#define SC2705_WLED_CONFIG9                   0x28
#define SC2705_WLED_CONFIG10                  0x29
#define SC2705_BOOST_CONTROL1                 0x30
#define SC2705_DISPLAY_CONFIG1                0x40
#define SC2705_DISPLAY_CONFIG2                0x41
#define SC2705_DISPLAY_CONFIG3                0x42
#define SC2705_DISPLAY_CONFIG4                0x43
#define SC2705_DISPLAY_CONFIG5                0x44
#define SC2705_DISPLAY_CONFIG6                0x45
#define SC2705_DISPLAY_CONFIG7                0x46
#define SC2705_DISPLAY_CONFIG8                0x47
#define SC2705_DISPLAY_CONFIG9                0x48
#define SC2705_BOOST_VOLTAGE                  0x50
#define SC2705_BOOST_SLEW_RATE                0x51
#define SC2705_BOOST_CONFIG1                  0x52
#define SC2705_INV_VOLTAGE                    0x5F
#define SC2705_INV_SLEW_RATE                  0x60
#define SC2705_INV_CONFIG1                    0x61
#define SC2705_INV_CONFIG2                    0x62
#define SC2705_CP_VOLTAGE                     0x6B
#define SC2705_CP_SLEW_RATE                   0x6C
#define SC2705_CP_CONFIG1                     0x6D
#define SC2705_CP_CONFIG2                     0x6E
#define SC2705_CP_CONFIG3                     0x6F
#define SC2705_CP_CONFIG4                     0x70
#define SC2705_CP_CONFIG5                     0x71
#define SC2705_CP_CONFIG6                     0x72
#define SC2705_CP_CONFIG7                     0x73
#define SC2705_CP_CONFIG8                     0x74
#define SC2705_CP_CONFIG9                     0x75
#define SC2705_CP_CONFIG10                    0x76
#define SC2705_CP_CONFIG11                    0x77
#define SC2705_CP_CONFIG12                    0x78
#define SC2705_CP_CONFIG13                    0x79
#define SC2705_CP_CONFIG14                    0x7A
#define SC2705_CP_CONFIG15                    0x7B
#define SC2705_CP_CONFIG16                    0x7C
#define SC2705_CP_CONFIG17                    0x7D
#define SC2705_LDO_VOLTAGE                    0x8F
#define SC2705_LDO_SLEW_RATE                  0x90
#define SC2705_LDO_CONFIG1                    0x91
#define SC2705_CHIP_FAULT_DEB                 0xA0
#define SC2705_DISPLAY_BOOST_DEB_CONFIG       0xA1
#define SC2705_DISPLAY_LDO_INV_DEB_CONFIG     0xA2
#define SC2705_DISPLAY_CP_DEB_CONFIG          0xA3
#define SC2705_WLED_DEB_CONFIG                0xA4

/* SC2705_STATUS_A = 0x00 */
#define SC2705_VSYS_UV_OT_VREF_FLT_SHIFT      0
#define SC2705_VSYS_UV_OT_VREF_FLT_MASK       BIT(0)
#define SC2705_DISPLAY_TYPE_SHIFT             1
#define SC2705_DISPLAY_TYPE_MASK              BIT(1)
#define SC2705_VDDIO_FLT_SHIFT                4
#define SC2705_VDDIO_FLT_MASK                 BIT(4)
#define SC2705_SYS_WDT_TIMEOUT_SHIFT          7
#define SC2705_SYS_WDT_TIMEOUT_MASK           BIT(7)

/* SC2705_STATUS_B = 0x01 */
#define SC2705_WLED_OC_SHIFT                  0
#define SC2705_WLED_OC_MASK                   BIT(0)
#define SC2705_WLED_OV_SHIFT                  1
#define SC2705_WLED_OV_MASK                   BIT(1)
#define SC2705_WLED_UV_SCP_SHIFT              2
#define SC2705_WLED_UV_SCP_MASK               BIT(2)

/* SC2705_STATUS_C = 0x02 */
#define SC2705_BOOST_OVP_SHIFT                0
#define SC2705_BOOST_OVP_MASK                 BIT(0)
#define SC2705_BOOST_SCP_SHIFT                1
#define SC2705_BOOST_SCP_MASK                 BIT(1)
#define SC2705_BOOST_UVP_SHIFT                2
#define SC2705_BOOST_UVP_MASK                 BIT(2)

/* SC2705_STATUS_D = 0x03 */
#define SC2705_CP_OVP_SHIFT                   0
#define SC2705_CP_OVP_MASK                    BIT(0)
#define SC2705_CP_SCP_SHIFT                   1
#define SC2705_CP_SCP_MASK                    BIT(1)
#define SC2705_CP_UVP_SHIFT                   2
#define SC2705_CP_UVP_MASK                    BIT(2)

/* SC2705_STATUS_E = 0x04 */
#define SC2705_INV_OVP_SHIFT                  0
#define SC2705_INV_OVP_MASK                   BIT(0)
#define SC2705_INV_SCP_SHIFT                  1
#define SC2705_INV_SCP_MASK                   BIT(1)
#define SC2705_DLDO_LDO_SC_SHIFT              3
#define SC2705_DLDO_LDO_SC_MASK               BIT(3)

/* SC2705_EVENT_A = 0x05 */
#define SC2705_E_VSYS_UV_OT_VREF_FLT_SHIFT    0
#define SC2705_E_VSYS_UV_OT_VREF_FLT_MASK     BIT(0)
#define SC2705_E_CHCR_SHIFT                   3
#define SC2705_E_CHCR_MASK                    BIT(3)
#define SC2705_E_VDDIO_FLT_SHIFT              4
#define SC2705_E_VDDIO_FLT_MASK               BIT(4)
#define SC2705_E_SYS_WDT_SHIFT                7
#define SC2705_E_SYS_WDT_MASK                 BIT(7)

/* SC2705_EVENT_B = 0x06 */
#define SC2705_E_OC_SHIFT                     0
#define SC2705_E_OC_MASK                      BIT(0)
#define SC2705_E_OV_SHIFT                     1
#define SC2705_E_OV_MASK                      BIT(1)
#define SC2705_E_UV_SCP_SHIFT                 2
#define SC2705_E_UV_SCP_MASK                  BIT(2)

/* SC2705_EVENT_C = 0x07 */
#define SC2705_E_BOOST_OVP_FLT_SHIFT          0
#define SC2705_E_BOOST_OVP_FLT_MASK           BIT(0)
#define SC2705_E_BOOST_SCP_FLT_SHIFT          1
#define SC2705_E_BOOST_SCP_FLT_MASK           BIT(1)
#define SC2705_E_BOOST_UVP_FLT_SHIFT          2
#define SC2705_E_BOOST_UVP_FLT_MASK           BIT(2)

/* SC2705_EVENT_D = 0x08 */
#define SC2705_E_CP_OVP_FLT_SHIFT             0
#define SC2705_E_CP_OVP_FLT_MASK              BIT(0)
#define SC2705_E_CP_SCP_FLT_SHIFT             1
#define SC2705_E_CP_SCP_FLT_MASK              BIT(1)
#define SC2705_E_CP_UVP_FLT_SHIFT             2
#define SC2705_E_CP_UVP_FLT_MASK              BIT(2)

/* SC2705_EVENT_E = 0x09 */
#define SC2705_E_INV_OVP_FLT_SHIFT            0
#define SC2705_E_INV_OVP_FLT_MASK             BIT(0)
#define SC2705_E_INV_SCP_FLT_SHIFT            1
#define SC2705_E_INV_SCP_FLT_MASK             BIT(1)
#define SC2705_E_DLDO_LDO_SC_FLT_SHIFT        3
#define SC2705_E_DLDO_LDO_SC_FLT_MASK         BIT(3)

/* SC2705_IRQ_MASK_A = 0x0A */
#define SC2705_M_VSYS_UV_OT_VREF_FLT_SHIFT    0
#define SC2705_M_VSYS_UV_OT_VREF_FLT_MASK     BIT(0)
#define SC2705_M_CHCR_SHIFT                   3
#define SC2705_M_CHCR_MASK                    BIT(3)
#define SC2705_M_VDDIO_FLT_SHIFT              4
#define SC2705_M_VDDIO_FLT_MASK               BIT(4)
#define SC2705_M_SYS_WDT_SHIFT                7
#define SC2705_M_SYS_WDT_MASK                 BIT(7)

/* SC2705_IRQ_MASK_B = 0x0B */
#define SC2705_M_OC_SHIFT                     0
#define SC2705_M_OC_MASK                      BIT(0)
#define SC2705_M_OV_SHIFT                     1
#define SC2705_M_OV_MASK                      BIT(1)
#define SC2705_M_UV_SCP_SHIFT                 2
#define SC2705_M_UV_SCP_MASK                  BIT(2)
#define SC2705_E_OC_AUTO_SHUTDOWN_SHIFT       4
#define SC2705_E_OC_AUTO_SHUTDOWN_MASK        BIT(4)
#define SC2705_E_OV_AUTO_SHUTDOWN_SHIFT       5
#define SC2705_E_OV_AUTO_SHUTDOWN_MASK        BIT(5)
#define SC2705_E_UV_SCP_AUTO_SHUTDOWN_SHIFT   6
#define SC2705_E_UV_SCP_AUTO_SHUTDOWN_MASK    BIT(6)

/* SC2705_IRQ_MASK_C = 0x0C */
#define SC2705_M_BOOST_OVP_FLT_SHIFT          0
#define SC2705_M_BOOST_OVP_FLT_MASK           BIT(0)
#define SC2705_M_BOOST_SCP_FLT_SHIFT          1
#define SC2705_M_BOOST_SCP_FLT_MASK           BIT(1)
#define SC2705_M_BOOST_UVP_FLT_SHIFT          2
#define SC2705_M_BOOST_UVP_FLT_MASK           BIT(2)
#define SC2705_E_BOOST_OVP_AUTO_SHUTDOWN_SHIFT 4
#define SC2705_E_BOOST_OVP_AUTO_SHUTDOWN_MASK BIT(4)
#define SC2705_E_BOOST_SCP_AUTO_SHUTDOWN_SHIFT 5
#define SC2705_E_BOOST_SCP_AUTO_SHUTDOWN_MASK BIT(5)
#define SC2705_E_BOOST_UVP_AUTO_SHUTDOWN_SHIFT 6
#define SC2705_E_BOOST_UVP_AUTO_SHUTDOWN_MASK BIT(6)

/* SC2705_IRQ_MASK_D = 0x0D */
#define SC2705_M_CP_OVP_FLT_SHIFT             0
#define SC2705_M_CP_OVP_FLT_MASK              BIT(0)
#define SC2705_M_CP_SCP_FLT_SHIFT             1
#define SC2705_M_CP_SCP_FLT_MASK              BIT(1)
#define SC2705_M_CP_UVP_FLT_SHIFT             2
#define SC2705_M_CP_UVP_FLT_MASK              BIT(2)
#define SC2705_E_CP_OVP_AUTO_SHUTDOWN_SHIFT   4
#define SC2705_E_CP_OVP_AUTO_SHUTDOWN_MASK    BIT(4)
#define SC2705_E_CP_SCP_AUTO_SHUTDOWN_SHIFT   5
#define SC2705_E_CP_SCP_AUTO_SHUTDOWN_MASK    BIT(5)
#define SC2705_E_CP_UVP_AUTO_SHUTDOWN_SHIFT   6
#define SC2705_E_CP_UVP_AUTO_SHUTDOWN_MASK    BIT(6)

/* SC2705_IRQ_MASK_E = 0x0E */
#define SC2705_M_INV_OVP_FLT_SHIFT            0
#define SC2705_M_INV_OVP_FLT_MASK             BIT(0)
#define SC2705_M_INV_SCP_FLT_SHIFT            1
#define SC2705_M_INV_SCP_FLT_MASK             BIT(1)
#define SC2705_M_DLDO_LDO_SC_FLT_SHIFT        3
#define SC2705_M_DLDO_LDO_SC_FLT_MASK         BIT(3)
#define SC2705_E_INVERTER_OVP_AUTO_SHUTDOWN_SHIFT 4
#define SC2705_E_INVERTER_OVP_AUTO_SHUTDOWN_MASK BIT(4)
#define SC2705_E_INVERTER_SCP_AUTO_SHUTDOWN_SHIFT 5
#define SC2705_E_INVERTER_SCP_AUTO_SHUTDOWN_MASK BIT(5)
#define SC2705_E_DLDO_LDO_SC_AUTO_SHUTDOWN_SHIFT 7
#define SC2705_E_DLDO_LDO_SC_AUTO_SHUTDOWN_MASK BIT(7)

/* SC2705_I2C_CONFIG = 0x0F */
#define SC2705_IF_BASE_ADDR_SHIFT             0
#define SC2705_IF_BASE_ADDR_MASK              (0x7 << 0)
#define SC2705_I2CMS_SPEED_SHIFT              3
#define SC2705_I2CMS_SPEED_MASK               BIT(3)
#define SC2705_WRITE_MODE_SHIFT               4
#define SC2705_WRITE_MODE_MASK                BIT(4)
#define SC2705_I2C_TO_EN_CTL_SHIFT            5
#define SC2705_I2C_TO_EN_CTL_MASK             BIT(5)
#define SC2705_I2CMS_DISABLE_SHIFT            6
#define SC2705_I2CMS_DISABLE_MASK             BIT(6)
#define SC2705_I2C_USE_DEFAULT_ADDR_SHIFT     7
#define SC2705_I2C_USE_DEFAULT_ADDR_MASK      BIT(7)

/* SC2705_SUPPLY_SEQ_MODE_CONTROL = 0x18 */
#define SC2705_POWER_SEQ_CTRL_MODE_SHIFT      0
#define SC2705_POWER_SEQ_CTRL_MODE_MASK       (0x3 << 0)

/* SC2705_SUPPLY_ACTIVE = 0x19 */
#define SC2705_DISPLAY_EN_SHIFT               0
#define SC2705_DISPLAY_EN_MASK                BIT(0)
#define SC2705_WLED_EN_SHIFT                  1
#define SC2705_WLED_EN_MASK                   BIT(1)

/* SC2705_SUPPLY_STATUS = 0x1A */
#define SC2705_DISPLAY_IS_ACTIVE_SHIFT        0
#define SC2705_DISPLAY_IS_ACTIVE_MASK         BIT(0)
#define SC2705_WLED_IS_ACTIVE_SHIFT           1
#define SC2705_WLED_IS_ACTIVE_MASK            BIT(1)
#define SC2705_DISPLAY_IS_PG_SHIFT            2
#define SC2705_DISPLAY_IS_PG_MASK             BIT(2)
#define SC2705_WLED_IS_PG_SHIFT               3
#define SC2705_WLED_IS_PG_MASK                BIT(3)

/* SC2705_WLED_CONFIG1 = 0x20 */
#define SC2705_WLED_MODE_SHIFT                0
#define SC2705_WLED_MODE_MASK                 (0x7 << 0)
#define SC2705_WLED_STR1_EN_SHIFT             3
#define SC2705_WLED_STR1_EN_MASK              BIT(3)
#define SC2705_WLED_STR2_EN_SHIFT             4
#define SC2705_WLED_STR2_EN_MASK              BIT(4)
#define SC2705_PWM_POLARITY_SHIFT             5
#define SC2705_PWM_POLARITY_MASK              BIT(5)
#define SC2705_WLED_IDAC_TRIM_ENHANCE_SHIFT   6
#define SC2705_WLED_IDAC_TRIM_ENHANCE_MASK    (0x3 << 6)

/* SC2705_WLED_CONFIG2 = 0x21 */
#define SC2705_IDAC_TARGET_H_SHIFT            0
#define SC2705_IDAC_TARGET_H_MASK             (0x7 << 0)
#define SC2705_IDAC_LINEAR_SHIFT              3
#define SC2705_IDAC_LINEAR_MASK               BIT(3)
#define SC2705_IDAC_RAMP_DIS_SHIFT            4
#define SC2705_IDAC_RAMP_DIS_MASK             BIT(4)
#define SC2705_IDAC_RAMP_PWM_COMPL_SHIFT      5
#define SC2705_IDAC_RAMP_PWM_COMPL_MASK       BIT(5)
#define SC2705_IDAC_CLK_POLARITY_SHIFT        6
#define SC2705_IDAC_CLK_POLARITY_MASK         BIT(6)
#define SC2705_WLED_HALF_CLK_EN_SHIFT         7
#define SC2705_WLED_HALF_CLK_EN_MASK          BIT(7)

/* SC2705_WLED_CONFIG3 = 0x22 */
#define SC2705_IDAC_TARGET_L_SHIFT            0
#define SC2705_IDAC_TARGET_L_MASK             (0xFF << 0)

/* SC2705_WLED_CONFIG4 = 0x23 */
#define SC2705_IDAC_RAMP_RATE_SHIFT           0
#define SC2705_IDAC_RAMP_RATE_MASK            (0xF << 0)
#define SC2705_PWM_IN_FREQ_RANGE_SHIFT        4
#define SC2705_PWM_IN_FREQ_RANGE_MASK         (0x3 << 4)
#define SC2705_WLED_OPEN_LED_SHIFT            6
#define SC2705_WLED_OPEN_LED_MASK             (0x3 << 6)

/* SC2705_WLED_CONFIG5 = 0x24 */
#define SC2705_PWM_IN_DUTY_THRESHOLD_SHIFT    0
#define SC2705_PWM_IN_DUTY_THRESHOLD_MASK     (0xFF << 0)

/* SC2705_WLED_CONFIG6 = 0x25 */
#define SC2705_PWM_OUT_FREQ_STEP_SHIFT        0
#define SC2705_PWM_OUT_FREQ_STEP_MASK         (0xFF << 0)

/* SC2705_WLED_CONFIG7 = 0x26 */
#define SC2705_PWM_OUT_DUTY_SHIFT             0
#define SC2705_PWM_OUT_DUTY_MASK              (0xFF << 0)

/* SC2705_WLED_CONFIG8 = 0x27 */
#define SC2705_DISCON_STR1_SHIFT              0
#define SC2705_DISCON_STR1_MASK               BIT(0)
#define SC2705_DISCON_STR2_SHIFT              1
#define SC2705_DISCON_STR2_MASK               BIT(1)
#define SC2705_STR1_MASTER_SHIFT              2
#define SC2705_STR1_MASTER_MASK               BIT(2)
#define SC2705_STR2_MASTER_SHIFT              3
#define SC2705_STR2_MASTER_MASK               BIT(3)
#define SC2705_IDAC_FORCE_ON_SHIFT            4
#define SC2705_IDAC_FORCE_ON_MASK             BIT(4)
#define SC2705_IDAC_CLK_FORCE_OFF_SHIFT       5
#define SC2705_IDAC_CLK_FORCE_OFF_MASK        BIT(5)
#define SC2705_PHY_CLK_FORCE_OFF_SHIFT        6
#define SC2705_PHY_CLK_FORCE_OFF_MASK         BIT(6)

/* SC2705_WLED_CONFIG9 = 0x28 */
#define SC2705_PWM_IN_DUTY_SHIFT              0
#define SC2705_PWM_IN_DUTY_MASK               (0xFF << 0)

/* SC2705_WLED_CONFIG10 = 0x29 */
#define SC2705_WLED_PANIC_EN_SHIFT            0
#define SC2705_WLED_PANIC_EN_MASK             BIT(0)
#define SC2705_WLED_PANIC_TH_SHIFT            1
#define SC2705_WLED_PANIC_TH_MASK             (0x3 << 1)
#define SC2705_WLED_TEST_MODE_SHIFT           3
#define SC2705_WLED_TEST_MODE_MASK            (0x1F << 3)

/* SC2705_BOOST_CONTROL1 = 0x30 */
#define SC2705_VREF_CLIM_SHIFT                0
#define SC2705_VREF_CLIM_MASK                 (0x3 << 0)
#define SC2705_VREF_OVP_SHIFT                 2
#define SC2705_VREF_OVP_MASK                  (0x3 << 2)
#define SC2705_CSGAIN_SEL_SHIFT               4
#define SC2705_CSGAIN_SEL_MASK                (0x7 << 4)

/* SC2705_DISPLAY_CONFIG1 = 0x40 */
#define SC2705_SEQ_UP_SIMULTANOUS_SHIFT       0
#define SC2705_SEQ_UP_SIMULTANOUS_MASK        BIT(0)
#define SC2705_SEQ_DN_SIMULTANOUS_SHIFT       1
#define SC2705_SEQ_DN_SIMULTANOUS_MASK        BIT(1)
#define SC2705_UP_VPOS_VNEG_SHIFT             2
#define SC2705_UP_VPOS_VNEG_MASK              BIT(2)
#define SC2705_DN_VPOS_VNEG_SHIFT             3
#define SC2705_DN_VPOS_VNEG_MASK              BIT(3)
#define SC2705_PHY_CLK_ON_SHIFT               5
#define SC2705_PHY_CLK_ON_MASK                BIT(5)
#define SC2705_MAP_SWITCH_ENABLE_SHIFT        7
#define SC2705_MAP_SWITCH_ENABLE_MASK         BIT(7)

/* SC2705_DISPLAY_CONFIG2 = 0x41 */
#define SC2705_UP_DELAY_1_SHIFT               0
#define SC2705_UP_DELAY_1_MASK                (0x7F << 0)
#define SC2705_UP_DELAY_1_SCALE_SHIFT         7
#define SC2705_UP_DELAY_1_SCALE_MASK          BIT(7)

/* SC2705_DISPLAY_CONFIG3 = 0x42 */
#define SC2705_UP_DELAY_2_SHIFT               0
#define SC2705_UP_DELAY_2_MASK                (0x7F << 0)
#define SC2705_UP_DELAY_2_SCALE_SHIFT         7
#define SC2705_UP_DELAY_2_SCALE_MASK          BIT(7)

/* SC2705_DISPLAY_CONFIG4 = 0x43 */
#define SC2705_UP_DELAY_3_SHIFT               0
#define SC2705_UP_DELAY_3_MASK                (0x7F << 0)
#define SC2705_UP_DELAY_3_SCALE_SHIFT         7
#define SC2705_UP_DELAY_3_SCALE_MASK          BIT(7)

/* SC2705_DISPLAY_CONFIG5 = 0x44 */
#define SC2705_DN_DELAY_1_SHIFT               0
#define SC2705_DN_DELAY_1_MASK                (0x7F << 0)
#define SC2705_DN_DELAY_1_SCALE_SHIFT         7
#define SC2705_DN_DELAY_1_SCALE_MASK          BIT(7)

/* SC2705_DISPLAY_CONFIG6 = 0x45 */
#define SC2705_DN_DELAY_2_SHIFT               0
#define SC2705_DN_DELAY_2_MASK                (0x7F << 0)
#define SC2705_DN_DELAY_2_SCALE_SHIFT         7
#define SC2705_DN_DELAY_2_SCALE_MASK          BIT(7)

/* SC2705_DISPLAY_CONFIG7 = 0x46 */
#define SC2705_DN_DELAY_3_SHIFT               0
#define SC2705_DN_DELAY_3_MASK                (0x7F << 0)
#define SC2705_DN_DELAY_3_SCALE_SHIFT         7
#define SC2705_DN_DELAY_3_SCALE_MASK          BIT(7)

/* SC2705_DISPLAY_CONFIG8 = 0x47 */
#define SC2705_BOOST_MAP_SHIFT                0
#define SC2705_BOOST_MAP_MASK                 (0x3 << 0)
#define SC2705_INV_MAP_SHIFT                  2
#define SC2705_INV_MAP_MASK                   (0x3 << 2)
#define SC2705_CP_MAP_SHIFT                   4
#define SC2705_CP_MAP_MASK                    (0x3 << 4)
#define SC2705_LDO_MAP_SHIFT                  6
#define SC2705_LDO_MAP_MASK                   (0x3 << 6)

/* SC2705_DISPLAY_CONFIG9 = 0x48 */
#define SC2705_SWIRE_EN_SHIFT                 0
#define SC2705_SWIRE_EN_MASK                  BIT(0)
#define SC2705_SWIRE_START_VOLTAGE_SHIFT      4
#define SC2705_SWIRE_START_VOLTAGE_MASK       (0xF << 4)

/* SC2705_BOOST_VOLTAGE = 0x50 */
#define SC2705_BOOST_VOLTAGE_SHIFT            0
#define SC2705_BOOST_VOLTAGE_MASK             (0xFF << 0)

/* SC2705_BOOST_SLEW_RATE = 0x51 */
#define SC2705_BOOST_SLEW_RATE_SHIFT          0
#define SC2705_BOOST_SLEW_RATE_MASK           (0x7 << 0)

/* SC2705_BOOST_CONFIG1 = 0x52 */
#define SC2705_BOOST_SEL_POC_LIMIT_SHIFT      0
#define SC2705_BOOST_SEL_POC_LIMIT_MASK       (0x7 << 0)
#define SC2705_BOOST_SEL_ISLOPE_SHIFT         4
#define SC2705_BOOST_SEL_ISLOPE_MASK          (0xF << 4)

/* SC2705_INV_VOLTAGE = 0x5F */
#define SC2705_INV_VOLTAGE_SHIFT              0
#define SC2705_INV_VOLTAGE_MASK               (0xFF << 0)

/* SC2705_INV_SLEW_RATE = 0x60 */
#define SC2705_INV_SLEW_RATE_SHIFT            0
#define SC2705_INV_SLEW_RATE_MASK             (0x7 << 0)

/* SC2705_INV_CONFIG1 = 0x61 */
#define SC2705_INV_SEL_LSLOPE_SHIFT           0
#define SC2705_INV_SEL_LSLOPE_MASK            (0xF << 0)
#define SC2705_INV_SEL_POC_LIMIT_SHIFT        4
#define SC2705_INV_SEL_POC_LIMIT_MASK         (0x3 << 4)
#define SC2705_INV_SEL_NOC_LIMIT_SHIFT        6
#define SC2705_INV_SEL_NOC_LIMIT_MASK         (0x3 << 6)

/* SC2705_INV_CONFIG2 = 0x62 */
#define SC2705_INV_SEL_MIN_OFF_SHIFT          3
#define SC2705_INV_SEL_MIN_OFF_MASK           BIT(3)
#define SC2705_INV_EXP_UVOV_SHIFT             4
#define SC2705_INV_EXP_UVOV_MASK              BIT(4)
#define SC2705_INV_PROT_MASK_B_SHIFT          5
#define SC2705_INV_PROT_MASK_B_MASK           BIT(5)
#define SC2705_INV_SCP_DET_SHIFT              7
#define SC2705_INV_SCP_DET_MASK               BIT(7)

/* SC2705_CP_VOLTAGE = 0x6B */
#define SC2705_CP_VOLTAGE_SHIFT               0
#define SC2705_CP_VOLTAGE_MASK                (0xFF << 0)

/* SC2705_CP_SLEW_RATE = 0x6C */
#define SC2705_CP_SLEW_RATE_SHIFT             0
#define SC2705_CP_SLEW_RATE_MASK              (0x7 << 0)

/* SC2705_CP_CONFIG1 = 0x6D */
#define SC2705_CP_SCP_DET_SHIFT               2
#define SC2705_CP_SCP_DET_MASK                BIT(2)
#define SC2705_CP_EN_DELAY_SHIFT              3
#define SC2705_CP_EN_DELAY_MASK               BIT(3)
#define SC2705_CP_MODE_SHIFT                  5
#define SC2705_CP_MODE_MASK                   BIT(5)

/* SC2705_CP_CONFIG2 = 0x6E */
#define SC2705_CP_EXP_UVOV_SHIFT              1
#define SC2705_CP_EXP_UVOV_MASK               BIT(1)
#define SC2705_CP_TST_NTEST_VINP_SHIFT        2
#define SC2705_CP_TST_NTEST_VINP_MASK         BIT(2)
#define SC2705_CP_TST_NTEST_VPOS_SHIFT        3
#define SC2705_CP_TST_NTEST_VPOS_MASK         BIT(3)
#define SC2705_CP_DCTRL_SSTART_SHIFT          4
#define SC2705_CP_DCTRL_SSTART_MASK           BIT(4)
#define SC2705_CP_DCTRL_SSOK_SHIFT            5
#define SC2705_CP_DCTRL_SSOK_MASK             BIT(5)
#define SC2705_CP_SEL_LVH_VINP_FORCE_EN_SHIFT 6
#define SC2705_CP_SEL_LVH_VINP_FORCE_EN_MASK  BIT(6)
#define SC2705_CP_SEL_LVH_VPOS_FORCE_EN_SHIFT 7
#define SC2705_CP_SEL_LVH_VPOS_FORCE_EN_MASK  BIT(7)

/* SC2705_CP_CONFIG3 = 0x6F */
#define SC2705_CP_SEL_MOFFT_SHIFT             0
#define SC2705_CP_SEL_MOFFT_MASK              (0x1F << 0)
#define SC2705_CP_CLK_PH_SEL_SHIFT            6
#define SC2705_CP_CLK_PH_SEL_MASK             (0x3 << 6)

/* SC2705_CP_CONFIG4 = 0x70 */
#define SC2705_CP_SEL_MONT_LOAD1_SHIFT        0
#define SC2705_CP_SEL_MONT_LOAD1_MASK         (0x1F << 0)

/* SC2705_CP_CONFIG5 = 0x71 */
#define SC2705_CP_SEL_MONT_LOAD2_SHIFT        0
#define SC2705_CP_SEL_MONT_LOAD2_MASK         (0x1F << 0)

/* SC2705_CP_CONFIG6 = 0x72 */
#define SC2705_CP_SEL_MONT_LOAD3_SHIFT        0
#define SC2705_CP_SEL_MONT_LOAD3_MASK         (0x1F << 0)

/* SC2705_CP_CONFIG7 = 0x73 */
#define SC2705_CP_SEL_MONT_LOAD4_SHIFT        0
#define SC2705_CP_SEL_MONT_LOAD4_MASK         (0x1F << 0)

/* SC2705_CP_CONFIG8 = 0x74 */
#define SC2705_CP_SEL_MONT_DAC0V2_SHIFT       0
#define SC2705_CP_SEL_MONT_DAC0V2_MASK        (0x1F << 0)

/* SC2705_CP_CONFIG9 = 0x75 */
#define SC2705_CP_SEL_MONT_DAC0V4_SHIFT       0
#define SC2705_CP_SEL_MONT_DAC0V4_MASK        (0x1F << 0)

/* SC2705_CP_CONFIG10 = 0x76 */
#define SC2705_CP_SEL_MONT_DAC0V6_SHIFT       0
#define SC2705_CP_SEL_MONT_DAC0V6_MASK        (0x1F << 0)

/* SC2705_CP_CONFIG11 = 0x77 */
#define SC2705_CP_SEL_MONT_DAC0V8_SHIFT       0
#define SC2705_CP_SEL_MONT_DAC0V8_MASK        (0x1F << 0)

/* SC2705_CP_CONFIG12 = 0x78 */
#define SC2705_CP_SEL_MONT_DAC1V0_SHIFT       0
#define SC2705_CP_SEL_MONT_DAC1V0_MASK        (0x1F << 0)

/* SC2705_CP_CONFIG13 = 0x79 */
#define SC2705_CP_SEL_MONT_DAC1V2_SHIFT       0
#define SC2705_CP_SEL_MONT_DAC1V2_MASK        (0x1F << 0)

/* SC2705_CP_CONFIG14 = 0x7A */
#define SC2705_CP_SEL_RON_MN1_SS_H_SHIFT      0
#define SC2705_CP_SEL_RON_MN1_SS_H_MASK       (0x3 << 0)
#define SC2705_CP_SEL_RON_MPOUT_SS_H_SHIFT    2
#define SC2705_CP_SEL_RON_MPOUT_SS_H_MASK     (0x3 << 2)
#define SC2705_CP_SEL_RON_MP2_SS_H_SHIFT      4
#define SC2705_CP_SEL_RON_MP2_SS_H_MASK       (0x3 << 4)
#define SC2705_CP_QKRSP_PH1_SHIFT             6
#define SC2705_CP_QKRSP_PH1_MASK              BIT(6)
#define SC2705_CP_QKRSP_PH2_SHIFT             7
#define SC2705_CP_QKRSP_PH2_MASK              BIT(7)

/* SC2705_CP_CONFIG15 = 0x7B */
#define SC2705_CP_SEL_RON_MN1_SS_SHIFT        0
#define SC2705_CP_SEL_RON_MN1_SS_MASK         (0x3 << 0)
#define SC2705_CP_SEL_RON_MN1_NM_SHIFT        2
#define SC2705_CP_SEL_RON_MN1_NM_MASK         (0x3 << 2)
#define SC2705_CP_SEL_RON_MN2_SS_SHIFT        4
#define SC2705_CP_SEL_RON_MN2_SS_MASK         (0x3 << 4)
#define SC2705_CP_SEL_RON_MN2_NM_SHIFT        6
#define SC2705_CP_SEL_RON_MN2_NM_MASK         (0x3 << 6)

/* SC2705_CP_CONFIG16 = 0x7C */
#define SC2705_CP_SEL_RON_MP1_SS_SHIFT        0
#define SC2705_CP_SEL_RON_MP1_SS_MASK         (0x3 << 0)
#define SC2705_CP_SEL_RON_MP1_NM_SHIFT        2
#define SC2705_CP_SEL_RON_MP1_NM_MASK         (0x3 << 2)
#define SC2705_CP_SEL_RON_MP2_SS_SHIFT        4
#define SC2705_CP_SEL_RON_MP2_SS_MASK         (0x3 << 4)
#define SC2705_CP_SEL_RON_MP2_NM_SHIFT        6
#define SC2705_CP_SEL_RON_MP2_NM_MASK         (0x3 << 6)

/* SC2705_CP_CONFIG17 = 0x7D */
#define SC2705_CP_SEL_RON_MPOUT_SS_SHIFT      0
#define SC2705_CP_SEL_RON_MPOUT_SS_MASK       (0x3 << 0)
#define SC2705_CP_SEL_RON_MPOUT_NM_SHIFT      2
#define SC2705_CP_SEL_RON_MPOUT_NM_MASK       (0x3 << 2)
#define SC2705_CP_SWELL_OFF_B_FORCE_ON_SHIFT  4
#define SC2705_CP_SWELL_OFF_B_FORCE_ON_MASK   BIT(4)
#define SC2705_CP_SWELL_OFF_B_FORCE_OFF_SHIFT 5
#define SC2705_CP_SWELL_OFF_B_FORCE_OFF_MASK  BIT(5)
#define SC2705_CP_VOUT_DISCHARGE_GATE_CTRL_FORCE_ON_SHIFT 6
#define SC2705_CP_VOUT_DISCHARGE_GATE_CTRL_FORCE_ON_MASK BIT(6)
#define SC2705_CP_VOUT_DISCHARGE_GATE_CTRL_FORCE_OFF_SHIFT 7
#define SC2705_CP_VOUT_DISCHARGE_GATE_CTRL_FORCE_OFF_MASK BIT(7)

/* SC2705_LDO_VOLTAGE = 0x8F */
#define SC2705_LDO_VOLTAGE_SHIFT              0
#define SC2705_LDO_VOLTAGE_MASK               (0xFF << 0)

/* SC2705_LDO_SLEW_RATE = 0x90 */
#define SC2705_LDO_SLEW_RATE_SHIFT            0
#define SC2705_LDO_SLEW_RATE_MASK             (0x7 << 0)

/* SC2705_LDO_CONFIG1 = 0x91 */
#define SC2705_DLDO_OCSEL_SHIFT               0
#define SC2705_DLDO_OCSEL_MASK                (0x3 << 0)
#define SC2705_DLDO_EN_VOUT_DISCHARGE_FORCE_ON_SHIFT 2
#define SC2705_DLDO_EN_VOUT_DISCHARGE_FORCE_ON_MASK BIT(2)
#define SC2705_DLDO_EN_VOUT_DISCHARGE_FORCE_OFF_SHIFT 3
#define SC2705_DLDO_EN_VOUT_DISCHARGE_FORCE_OFF_MASK BIT(3)
#define SC2705_DLDO_TEST_SC_SHIFT             4
#define SC2705_DLDO_TEST_SC_MASK              BIT(4)
#define SC2705_DLDO_DVC_OV_SHIFT              5
#define SC2705_DLDO_DVC_OV_MASK               BIT(5)
#define SC2705_DLDO_EN_FORCE_ON_SHIFT         6
#define SC2705_DLDO_EN_FORCE_ON_MASK          BIT(6)
#define SC2705_DLDO_EN_FORCE_OFF_SHIFT        7
#define SC2705_DLDO_EN_FORCE_OFF_MASK         BIT(7)

/* SC2705_CHIP_FAULT_DEB = 0xA0 */
#define SC2705_VSYS_UV_OT_VREF_FAULT_DEB_MODE_SHIFT 0
#define SC2705_VSYS_UV_OT_VREF_FAULT_DEB_MODE_MASK (0x3 << 0)
#define SC2705_VSYS_UV_OT_VREF_FAULT_DEB_TIME_SHIFT 2
#define SC2705_VSYS_UV_OT_VREF_FAULT_DEB_TIME_MASK (0x3 << 2)
#define SC2705_VDDIO_FAULT_DEB_MODE_SHIFT     4
#define SC2705_VDDIO_FAULT_DEB_MODE_MASK      (0x3 << 4)
#define SC2705_VDDIO_FAULT_DEB_TIME_SHIFT     6
#define SC2705_VDDIO_FAULT_DEB_TIME_MASK      (0x3 << 6)

/* SC2705_DISPLAY_BOOST_DEB_CONFIG = 0xA1 */
#define SC2705_DISPLAY_BOOST_OVP_DEB_SHIFT    0
#define SC2705_DISPLAY_BOOST_OVP_DEB_MASK     (0x3 << 0)
#define SC2705_DISPLAY_BOOST_UVP_DEB_SHIFT    2
#define SC2705_DISPLAY_BOOST_UVP_DEB_MASK     (0x3 << 2)
#define SC2705_DISPLAY_BOOST_SCP_DEB_SHIFT    6
#define SC2705_DISPLAY_BOOST_SCP_DEB_MASK     (0x3 << 6)

/* SC2705_DISPLAY_LDO_INV_DEB_CONFIG = 0xA2 */
#define SC2705_DISPLAY_INV_OVP_DEB_SHIFT      0
#define SC2705_DISPLAY_INV_OVP_DEB_MASK       (0x3 << 0)
#define SC2705_DISPLAY_INV_SCP_DEB_SHIFT      2
#define SC2705_DISPLAY_INV_SCP_DEB_MASK       (0x3 << 2)
#define SC2705_DISPLAY_LDO_SC_DEB_SHIFT       6
#define SC2705_DISPLAY_LDO_SC_DEB_MASK        (0x3 << 6)

/* SC2705_DISPLAY_CP_DEB_CONFIG = 0xA3 */
#define SC2705_DISPLAY_CP_OVP_DEB_SHIFT       0
#define SC2705_DISPLAY_CP_OVP_DEB_MASK        (0x3 << 0)
#define SC2705_DISPLAY_CP_UVP_DEB_SHIFT       2
#define SC2705_DISPLAY_CP_UVP_DEB_MASK        (0x3 << 2)
#define SC2705_DISPLAY_CP_SCP_DEB_SHIFT       6
#define SC2705_DISPLAY_CP_SCP_DEB_MASK        (0x3 << 6)

/* SC2705_WLED_DEB_CONFIG = 0xA4 */
#define SC2705_WLED_OVP_DEB_SHIFT             0
#define SC2705_WLED_OVP_DEB_MASK              (0x3 << 0)
#define SC2705_WLED_UVP_DEB_SHIFT             2
#define SC2705_WLED_UVP_DEB_MASK              (0x3 << 2)
#define SC2705_WLED_OLED_DEB_SHIFT            4
#define SC2705_WLED_OLED_DEB_MASK             (0x3 << 4)
#define SC2705_WLED_OCP_DEB_SHIFT             6
#define SC2705_WLED_OCP_DEB_MASK              BIT(6)

#endif /* __SC2705_DISPLAY_REGISTERS_H */

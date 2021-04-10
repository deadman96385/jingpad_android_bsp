/*
 * Copyright (C) 2018 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-08-08 21:19:06
 *
 */


#ifndef _SC2730_GLB_H
#define _SC2730_GLB_H

#define CTL_BASE_ANA_GLB		ANA_REGS_GLB_BASE

#define ANA_REG_GLB_CHIP_ID_LOW           (CTL_BASE_ANA_GLB + 0x0000)
#define ANA_REG_GLB_CHIP_ID_HIGH          (CTL_BASE_ANA_GLB + 0x0004)
#define ANA_REG_GLB_MODULE_EN0            (CTL_BASE_ANA_GLB + 0x0008)
#define ANA_REG_GLB_ARM_CLK_EN0           (CTL_BASE_ANA_GLB + 0x000C)
#define ANA_REG_GLB_RTC_CLK_EN0           (CTL_BASE_ANA_GLB + 0x0010)
#define ANA_REG_GLB_SOFT_RST0             (CTL_BASE_ANA_GLB + 0x0014)
#define ANA_REG_GLB_SOFT_RST1             (CTL_BASE_ANA_GLB + 0x0018)
#define ANA_REG_GLB_POWER_PD_SW           (CTL_BASE_ANA_GLB + 0x001C)
#define ANA_REG_GLB_POWER_PD_HW           (CTL_BASE_ANA_GLB + 0x0020)
#define ANA_REG_GLB_SOFT_RST_HW           (CTL_BASE_ANA_GLB + 0x0024)
#define ANA_REG_GLB_RESERVED_REG0         (CTL_BASE_ANA_GLB + 0x0028)
#define ANA_REG_GLB_RESERVED_REG1         (CTL_BASE_ANA_GLB + 0x002C)
#define ANA_REG_GLB_RESERVED_REG2         (CTL_BASE_ANA_GLB + 0x0030)
#define ANA_REG_GLB_RESERVED_REG3         (CTL_BASE_ANA_GLB + 0x0034)
#define ANA_REG_GLB_DCDC_CPU_REG0         (CTL_BASE_ANA_GLB + 0x0038)
#define ANA_REG_GLB_DCDC_CPU_REG1         (CTL_BASE_ANA_GLB + 0x003C)
#define ANA_REG_GLB_DCDC_CPU_REG2         (CTL_BASE_ANA_GLB + 0x0040)
#define ANA_REG_GLB_DCDC_CPU_VOL          (CTL_BASE_ANA_GLB + 0x0044)
#define ANA_REG_GLB_DCDC_GPU_REG0         (CTL_BASE_ANA_GLB + 0x0048)
#define ANA_REG_GLB_DCDC_GPU_REG1         (CTL_BASE_ANA_GLB + 0x004C)
#define ANA_REG_GLB_DCDC_GPU_REG2         (CTL_BASE_ANA_GLB + 0x0050)
#define ANA_REG_GLB_DCDC_GPU_VOL          (CTL_BASE_ANA_GLB + 0x0054)
#define ANA_REG_GLB_DCDC_CORE_REG0        (CTL_BASE_ANA_GLB + 0x0058)
#define ANA_REG_GLB_DCDC_CORE_REG1        (CTL_BASE_ANA_GLB + 0x005C)
#define ANA_REG_GLB_DCDC_CORE_REG2        (CTL_BASE_ANA_GLB + 0x0060)
#define ANA_REG_GLB_DCDC_CORE_VOL         (CTL_BASE_ANA_GLB + 0x0064)
#define ANA_REG_GLB_DCDC_MODEM_REG0       (CTL_BASE_ANA_GLB + 0x0068)
#define ANA_REG_GLB_DCDC_MODEM_REG1       (CTL_BASE_ANA_GLB + 0x006C)
#define ANA_REG_GLB_DCDC_MODEM_REG2       (CTL_BASE_ANA_GLB + 0x0070)
#define ANA_REG_GLB_DCDC_MODEM_VOL        (CTL_BASE_ANA_GLB + 0x0074)
#define ANA_REG_GLB_DCDC_MEM_REG0         (CTL_BASE_ANA_GLB + 0x0078)
#define ANA_REG_GLB_DCDC_MEM_REG1         (CTL_BASE_ANA_GLB + 0x007C)
#define ANA_REG_GLB_DCDC_MEM_REG2         (CTL_BASE_ANA_GLB + 0x0080)
#define ANA_REG_GLB_DCDC_MEM_VOL          (CTL_BASE_ANA_GLB + 0x0084)
#define ANA_REG_GLB_DCDC_MEMQ_REG0        (CTL_BASE_ANA_GLB + 0x0088)
#define ANA_REG_GLB_DCDC_MEMQ_REG1        (CTL_BASE_ANA_GLB + 0x008C)
#define ANA_REG_GLB_DCDC_MEMQ_REG2        (CTL_BASE_ANA_GLB + 0x0090)
#define ANA_REG_GLB_DCDC_MEMQ_VOL         (CTL_BASE_ANA_GLB + 0x0094)
#define ANA_REG_GLB_DCDC_GEN0_REG0        (CTL_BASE_ANA_GLB + 0x0098)
#define ANA_REG_GLB_DCDC_GEN0_REG1        (CTL_BASE_ANA_GLB + 0x009C)
#define ANA_REG_GLB_DCDC_GEN0_REG2        (CTL_BASE_ANA_GLB + 0x00A0)
#define ANA_REG_GLB_DCDC_GEN0_VOL         (CTL_BASE_ANA_GLB + 0x00A4)
#define ANA_REG_GLB_DCDC_GEN1_REG0        (CTL_BASE_ANA_GLB + 0x00A8)
#define ANA_REG_GLB_DCDC_GEN1_REG1        (CTL_BASE_ANA_GLB + 0x00AC)
#define ANA_REG_GLB_DCDC_GEN1_REG2        (CTL_BASE_ANA_GLB + 0x00B0)
#define ANA_REG_GLB_DCDC_GEN1_VOL         (CTL_BASE_ANA_GLB + 0x00B4)
#define ANA_REG_GLB_DCDC_WPA_REG0         (CTL_BASE_ANA_GLB + 0x00B8)
#define ANA_REG_GLB_DCDC_WPA_REG1         (CTL_BASE_ANA_GLB + 0x00BC)
#define ANA_REG_GLB_DCDC_WPA_REG2         (CTL_BASE_ANA_GLB + 0x00C0)
#define ANA_REG_GLB_DCDC_WPA_REG3         (CTL_BASE_ANA_GLB + 0x00C4)
#define ANA_REG_GLB_DCDC_WPA_VOL          (CTL_BASE_ANA_GLB + 0x00C8)
#define ANA_REG_GLB_DCDC_WPA_DCMB         (CTL_BASE_ANA_GLB + 0x00CC)
#define ANA_REG_GLB_DCDC_SRAM_REG0        (CTL_BASE_ANA_GLB + 0x00D0)
#define ANA_REG_GLB_DCDC_SRAM_REG1        (CTL_BASE_ANA_GLB + 0x00D4)
#define ANA_REG_GLB_DCDC_SRAM_REG2        (CTL_BASE_ANA_GLB + 0x00D8)
#define ANA_REG_GLB_DCDC_SRAM_VOL         (CTL_BASE_ANA_GLB + 0x00DC)
#define ANA_REG_GLB_RESERVED_REG4         (CTL_BASE_ANA_GLB + 0x00E0)
#define ANA_REG_GLB_DCDC_CH_CTRL          (CTL_BASE_ANA_GLB + 0x00E4)
#define ANA_REG_GLB_DCDC_CTRL             (CTL_BASE_ANA_GLB + 0x00E8)
#define ANA_REG_GLB_DCDC_CLK_CTRL         (CTL_BASE_ANA_GLB + 0x00EC)
#define ANA_REG_GLB_RESERVED_REG5         (CTL_BASE_ANA_GLB + 0x00F0)
#define ANA_REG_GLB_RESERVED_REG6         (CTL_BASE_ANA_GLB + 0x00F4)
#define ANA_REG_GLB_RESERVED_REG7         (CTL_BASE_ANA_GLB + 0x00F8)
#define ANA_REG_GLB_RESERVED_REG8         (CTL_BASE_ANA_GLB + 0x00FC)
#define ANA_REG_GLB_LDO_AVDD18_REG0       (CTL_BASE_ANA_GLB + 0x0100)
#define ANA_REG_GLB_LDO_AVDD18_REG1       (CTL_BASE_ANA_GLB + 0x0104)
#define ANA_REG_GLB_LDO_AVDD18_REG2       (CTL_BASE_ANA_GLB + 0x0108)
#define ANA_REG_GLB_LDO_VDDRF1V8_REG0     (CTL_BASE_ANA_GLB + 0x010C)
#define ANA_REG_GLB_LDO_VDDRF1V8_REG1     (CTL_BASE_ANA_GLB + 0x0110)
#define ANA_REG_GLB_LDO_VDDRF1V8_REG2     (CTL_BASE_ANA_GLB + 0x0114)
#define ANA_REG_GLB_LDO_VDDCAMIO_REG0     (CTL_BASE_ANA_GLB + 0x0118)
#define ANA_REG_GLB_LDO_VDDWCN_REG0       (CTL_BASE_ANA_GLB + 0x011C)
#define ANA_REG_GLB_LDO_VDDWCN_REG1       (CTL_BASE_ANA_GLB + 0x0120)
#define ANA_REG_GLB_LDO_VDDWCN_REG2       (CTL_BASE_ANA_GLB + 0x0124)
#define ANA_REG_GLB_LDO_VDDCAMD1_REG0     (CTL_BASE_ANA_GLB + 0x0128)
#define ANA_REG_GLB_LDO_VDDCAMD1_REG1     (CTL_BASE_ANA_GLB + 0x012C)
#define ANA_REG_GLB_LDO_VDDCAMD1_REG2     (CTL_BASE_ANA_GLB + 0x0130)
#define ANA_REG_GLB_LDO_VDDCAMD0_REG0     (CTL_BASE_ANA_GLB + 0x0134)
#define ANA_REG_GLB_LDO_VDDCAMD0_REG1     (CTL_BASE_ANA_GLB + 0x0138)
#define ANA_REG_GLB_LDO_VDDCAMD0_REG2     (CTL_BASE_ANA_GLB + 0x013C)
#define ANA_REG_GLB_LDO_VRF1V25_REG0      (CTL_BASE_ANA_GLB + 0x0140)
#define ANA_REG_GLB_LDO_VDDRF1V25_REG1    (CTL_BASE_ANA_GLB + 0x0144)
#define ANA_REG_GLB_LDO_VRF1V25_REG2      (CTL_BASE_ANA_GLB + 0x0148)
#define ANA_REG_GLB_LDO_AVDD12_REG0       (CTL_BASE_ANA_GLB + 0x014C)
#define ANA_REG_GLB_LDO_AVDD12_REG1       (CTL_BASE_ANA_GLB + 0x0150)
#define ANA_REG_GLB_LDO_AVDD12_REG2       (CTL_BASE_ANA_GLB + 0x0154)
#define ANA_REG_GLB_LDO_VDDCAMA0_REG0     (CTL_BASE_ANA_GLB + 0x0158)
#define ANA_REG_GLB_LDO_VDDCAMA0_REG1     (CTL_BASE_ANA_GLB + 0x015C)
#define ANA_REG_GLB_LDO_VDDCAMA0_REG2     (CTL_BASE_ANA_GLB + 0x0160)
#define ANA_REG_GLB_LDO_VDDCAMA1_REG0     (CTL_BASE_ANA_GLB + 0x0164)
#define ANA_REG_GLB_LDO_VDDCAMA1_REG1     (CTL_BASE_ANA_GLB + 0x0168)
#define ANA_REG_GLB_LDO_VDDCAMA1_REG2     (CTL_BASE_ANA_GLB + 0x016C)
#define ANA_REG_GLB_LDO_VDDCAMMOT_REG0    (CTL_BASE_ANA_GLB + 0x0170)
#define ANA_REG_GLB_LDO_VDDCAMMOT_REG1    (CTL_BASE_ANA_GLB + 0x0174)
#define ANA_REG_GLB_LDO_VDDCAMMOT_REG2    (CTL_BASE_ANA_GLB + 0x0178)
#define ANA_REG_GLB_LDO_VDDSIM0_REG0      (CTL_BASE_ANA_GLB + 0x017C)
#define ANA_REG_GLB_LDO_VDDSIM0_REG1      (CTL_BASE_ANA_GLB + 0x0180)
#define ANA_REG_GLB_LDO_VDDSIM0_REG2      (CTL_BASE_ANA_GLB + 0x0184)
#define ANA_REG_GLB_LDO_VDDSIM1_REG0      (CTL_BASE_ANA_GLB + 0x0188)
#define ANA_REG_GLB_LDO_VDDSIM1_REG1      (CTL_BASE_ANA_GLB + 0x018C)
#define ANA_REG_GLB_LDO_VDDSIM1_REG2      (CTL_BASE_ANA_GLB + 0x0190)
#define ANA_REG_GLB_LDO_VDDSIM2_REG0      (CTL_BASE_ANA_GLB + 0x0194)
#define ANA_REG_GLB_LDO_VDDSIM2_REG1      (CTL_BASE_ANA_GLB + 0x0198)
#define ANA_REG_GLB_LDO_VDDSIM2_REG2      (CTL_BASE_ANA_GLB + 0x019C)
#define ANA_REG_GLB_LDO_VDDEMMCCORE_REG0  (CTL_BASE_ANA_GLB + 0x01A0)
#define ANA_REG_GLB_LDO_VDDEMMCCORE_REG1  (CTL_BASE_ANA_GLB + 0x01A4)
#define ANA_REG_GLB_LDO_VDDEMMCCORE_REG2  (CTL_BASE_ANA_GLB + 0x01A8)
#define ANA_REG_GLB_LDO_VDDSDCORE_REG0    (CTL_BASE_ANA_GLB + 0x01AC)
#define ANA_REG_GLB_LDO_VDDSDCORE_REG1    (CTL_BASE_ANA_GLB + 0x01B0)
#define ANA_REG_GLB_LDO_VDDSDCORE_REG2    (CTL_BASE_ANA_GLB + 0x01B4)
#define ANA_REG_GLB_LDO_VDDSDIO_REG0      (CTL_BASE_ANA_GLB + 0x01B8)
#define ANA_REG_GLB_LDO_VDDSDIO_REG1      (CTL_BASE_ANA_GLB + 0x01BC)
#define ANA_REG_GLB_LDO_VDDSDIO_REG2      (CTL_BASE_ANA_GLB + 0x01C0)
#define ANA_REG_GLB_LDO_VDD28_REG0        (CTL_BASE_ANA_GLB + 0x01C4)
#define ANA_REG_GLB_LDO_VDD28_REG1        (CTL_BASE_ANA_GLB + 0x01C8)
#define ANA_REG_GLB_LDO_VDD28_REG2        (CTL_BASE_ANA_GLB + 0x01CC)
#define ANA_REG_GLB_LDO_VDDWIFIPA_REG0    (CTL_BASE_ANA_GLB + 0x01D0)
#define ANA_REG_GLB_LDO_VDDWIFIPA_REG1    (CTL_BASE_ANA_GLB + 0x01D4)
#define ANA_REG_GLB_LDO_VDDWIFIPA_REG2    (CTL_BASE_ANA_GLB + 0x01D8)
#define ANA_REG_GLB_LDO_VDD18_DCXO_REG0   (CTL_BASE_ANA_GLB + 0x01DC)
#define ANA_REG_GLB_LDO_VDD18_DCXO_REG1   (CTL_BASE_ANA_GLB + 0x01E0)
#define ANA_REG_GLB_LDO_VDD18_DCXO_REG2   (CTL_BASE_ANA_GLB + 0x01E4)
#define ANA_REG_GLB_LDO_VDDUSB33_REG0     (CTL_BASE_ANA_GLB + 0x01E8)
#define ANA_REG_GLB_LDO_VDDUSB33_REG1     (CTL_BASE_ANA_GLB + 0x01EC)
#define ANA_REG_GLB_LDO_VDDUSB33_REG2     (CTL_BASE_ANA_GLB + 0x01F0)
#define ANA_REG_GLB_LDO_VDDLDO0_REG0      (CTL_BASE_ANA_GLB + 0x01F4)
#define ANA_REG_GLB_LDO_VDDLDO0_REG1      (CTL_BASE_ANA_GLB + 0x01F8)
#define ANA_REG_GLB_LDO_VDDLDO0_REG2      (CTL_BASE_ANA_GLB + 0x01FC)
#define ANA_REG_GLB_LDO_VDDLDO1_REG0      (CTL_BASE_ANA_GLB + 0x0200)
#define ANA_REG_GLB_LDO_VDDLDO1_REG1      (CTL_BASE_ANA_GLB + 0x0204)
#define ANA_REG_GLB_LDO_VDDLDO1_REG2      (CTL_BASE_ANA_GLB + 0x0208)
#define ANA_REG_GLB_LDO_VDDLDO2_REG0      (CTL_BASE_ANA_GLB + 0x020C)
#define ANA_REG_GLB_LDO_VDDLDO2_REG1      (CTL_BASE_ANA_GLB + 0x0210)
#define ANA_REG_GLB_LDO_VDDLDO2_REG2      (CTL_BASE_ANA_GLB + 0x0214)
#define ANA_REG_GLB_RESERVED_REG9         (CTL_BASE_ANA_GLB + 0x0218)
#define ANA_REG_GLB_RESERVED_REG10        (CTL_BASE_ANA_GLB + 0x021C)
#define ANA_REG_GLB_RESERVED_REG11        (CTL_BASE_ANA_GLB + 0x0220)
#define ANA_REG_GLB_RESERVED_REG12        (CTL_BASE_ANA_GLB + 0x0224)
#define ANA_REG_GLB_LDO_RTC_CTRL          (CTL_BASE_ANA_GLB + 0x0228)
#define ANA_REG_GLB_LDO_CH_CTRL           (CTL_BASE_ANA_GLB + 0x022C)
#define ANA_REG_GLB_RESERVED_REG13        (CTL_BASE_ANA_GLB + 0x0230)
#define ANA_REG_GLB_RESERVED_REG14        (CTL_BASE_ANA_GLB + 0x0234)
#define ANA_REG_GLB_RESERVED_REG15        (CTL_BASE_ANA_GLB + 0x0238)
#define ANA_REG_GLB_RESERVED_REG16        (CTL_BASE_ANA_GLB + 0x023C)
#define ANA_REG_GLB_RESERVED_REG17        (CTL_BASE_ANA_GLB + 0x0240)
#define ANA_REG_GLB_SLP_WAIT_DCDCCPU      (CTL_BASE_ANA_GLB + 0x0244)
#define ANA_REG_GLB_SLP_CTRL              (CTL_BASE_ANA_GLB + 0x0248)
#define ANA_REG_GLB_SLP_DCDC_PD_CTRL      (CTL_BASE_ANA_GLB + 0x024C)
#define ANA_REG_GLB_SLP_LDO_PD_CTRL0      (CTL_BASE_ANA_GLB + 0x0250)
#define ANA_REG_GLB_SLP_LDO_PD_CTRL1      (CTL_BASE_ANA_GLB + 0x0254)
#define ANA_REG_GLB_SLP_DCDC_LP_CTRL      (CTL_BASE_ANA_GLB + 0x0258)
#define ANA_REG_GLB_SLP_LDO_LP_CTRL0      (CTL_BASE_ANA_GLB + 0x025C)
#define ANA_REG_GLB_SLP_LDO_LP_CTRL1      (CTL_BASE_ANA_GLB + 0x0260)
#define ANA_REG_GLB_DCDC_CORE_SLP_CTRL0   (CTL_BASE_ANA_GLB + 0x0264)
#define ANA_REG_GLB_DCDC_CORE_SLP_CTRL1   (CTL_BASE_ANA_GLB + 0x0268)
#define ANA_REG_GLB_DCDC_GPU_SLP_CTRL0    (CTL_BASE_ANA_GLB + 0x026C)
#define ANA_REG_GLB_DCDC_GPU_SLP_CTRL1    (CTL_BASE_ANA_GLB + 0x0270)
#define ANA_REG_GLB_DCDC_CPU_SLP_CTRL0    (CTL_BASE_ANA_GLB + 0x0274)
#define ANA_REG_GLB_DCDC_CPU_SLP_CTRL1    (CTL_BASE_ANA_GLB + 0x0278)
#define ANA_REG_GLB_DCDC_MODEM_SLP_CTRL0  (CTL_BASE_ANA_GLB + 0x027C)
#define ANA_REG_GLB_DCDC_MODEM_SLP_CTRL1  (CTL_BASE_ANA_GLB + 0x0280)
#define ANA_REG_GLB_DCDC_SRAM_SLP_CTRL0   (CTL_BASE_ANA_GLB + 0x0284)
#define ANA_REG_GLB_DCDC_SRAM_SLP_CTRL1   (CTL_BASE_ANA_GLB + 0x0288)
#define ANA_REG_GLB_DCDC_XTL_EN           (CTL_BASE_ANA_GLB + 0x028C)
#define ANA_REG_GLB_DCDC_XTL_EN0          (CTL_BASE_ANA_GLB + 0x0290)
#define ANA_REG_GLB_DCDC_XTL_EN1          (CTL_BASE_ANA_GLB + 0x0294)
#define ANA_REG_GLB_DCDC_XTL_EN2          (CTL_BASE_ANA_GLB + 0x0298)
#define ANA_REG_GLB_DCDC_XTL_EN3          (CTL_BASE_ANA_GLB + 0x029C)
#define ANA_REG_GLB_LDO_XTL_EN0           (CTL_BASE_ANA_GLB + 0x02A0)
#define ANA_REG_GLB_LDO_XTL_EN1           (CTL_BASE_ANA_GLB + 0x02A4)
#define ANA_REG_GLB_LDO_XTL_EN2           (CTL_BASE_ANA_GLB + 0x02A8)
#define ANA_REG_GLB_LDO_XTL_EN3           (CTL_BASE_ANA_GLB + 0x02AC)
#define ANA_REG_GLB_LDO_XTL_EN4           (CTL_BASE_ANA_GLB + 0x02B0)
#define ANA_REG_GLB_LDO_XTL_EN5           (CTL_BASE_ANA_GLB + 0x02B4)
#define ANA_REG_GLB_LDO_XTL_EN6           (CTL_BASE_ANA_GLB + 0x02B8)
#define ANA_REG_GLB_LDO_XTL_EN7           (CTL_BASE_ANA_GLB + 0x02BC)
#define ANA_REG_GLB_LDO_XTL_EN8           (CTL_BASE_ANA_GLB + 0x02C0)
#define ANA_REG_GLB_LDO_XTL_EN9           (CTL_BASE_ANA_GLB + 0x02C4)
#define ANA_REG_GLB_LDO_XTL_EN10          (CTL_BASE_ANA_GLB + 0x02C8)
#define ANA_REG_GLB_LDO_XTL_EN11          (CTL_BASE_ANA_GLB + 0x02CC)
#define ANA_REG_GLB_LDO_XTL_EN12          (CTL_BASE_ANA_GLB + 0x02D0)
#define ANA_REG_GLB_DCXO_XTL_EN           (CTL_BASE_ANA_GLB + 0x02D4)
#define ANA_REG_GLB_RESERVED_REG18        (CTL_BASE_ANA_GLB + 0x02D8)
#define ANA_REG_GLB_RESERVED_REG19        (CTL_BASE_ANA_GLB + 0x02DC)
#define ANA_REG_GLB_RESERVED_REG20        (CTL_BASE_ANA_GLB + 0x02E0)
#define ANA_REG_GLB_TSX_CTRL_REG0         (CTL_BASE_ANA_GLB + 0x02E4)
#define ANA_REG_GLB_TSX_CTRL_REG1         (CTL_BASE_ANA_GLB + 0x02E8)
#define ANA_REG_GLB_TSX_CTRL0             (CTL_BASE_ANA_GLB + 0x02EC)
#define ANA_REG_GLB_TSX_CTRL1             (CTL_BASE_ANA_GLB + 0x02F0)
#define ANA_REG_GLB_TSX_CTRL2             (CTL_BASE_ANA_GLB + 0x02F4)
#define ANA_REG_GLB_TSX_CTRL3             (CTL_BASE_ANA_GLB + 0x02F8)
#define ANA_REG_GLB_TSX_CTRL4             (CTL_BASE_ANA_GLB + 0x02FC)
#define ANA_REG_GLB_TSX_CTRL5             (CTL_BASE_ANA_GLB + 0x0300)
#define ANA_REG_GLB_TSX_CTRL6             (CTL_BASE_ANA_GLB + 0x0304)
#define ANA_REG_GLB_TSX_CTRL7             (CTL_BASE_ANA_GLB + 0x0308)
#define ANA_REG_GLB_TSX_CTRL8             (CTL_BASE_ANA_GLB + 0x030C)
#define ANA_REG_GLB_TSX_CTRL9             (CTL_BASE_ANA_GLB + 0x0310)
#define ANA_REG_GLB_TSX_CTRL10            (CTL_BASE_ANA_GLB + 0x0314)
#define ANA_REG_GLB_TSX_CTRL11            (CTL_BASE_ANA_GLB + 0x0318)
#define ANA_REG_GLB_TSX_CTRL12            (CTL_BASE_ANA_GLB + 0x031C)
#define ANA_REG_GLB_TSX_CTRL13            (CTL_BASE_ANA_GLB + 0x0320)
#define ANA_REG_GLB_TSX_CTRL14            (CTL_BASE_ANA_GLB + 0x0324)
#define ANA_REG_GLB_RESERVED_REG21        (CTL_BASE_ANA_GLB + 0x0328)
#define ANA_REG_GLB_RESERVED_REG22        (CTL_BASE_ANA_GLB + 0x032C)
#define ANA_REG_GLB_RESERVED_REG23        (CTL_BASE_ANA_GLB + 0x0330)
#define ANA_REG_GLB_TSEN_CTRL0            (CTL_BASE_ANA_GLB + 0x0334)
#define ANA_REG_GLB_TSEN_CTRL1            (CTL_BASE_ANA_GLB + 0x0338)
#define ANA_REG_GLB_TSEN_CTRL2            (CTL_BASE_ANA_GLB + 0x033C)
#define ANA_REG_GLB_TSEN_CTRL3            (CTL_BASE_ANA_GLB + 0x0340)
#define ANA_REG_GLB_TSEN_CTRL4            (CTL_BASE_ANA_GLB + 0x0344)
#define ANA_REG_GLB_TSEN_CTRL5            (CTL_BASE_ANA_GLB + 0x0348)
#define ANA_REG_GLB_RESERVED_REG_CORE     (CTL_BASE_ANA_GLB + 0x034C)
#define ANA_REG_GLB_RESERVED_REG_RTC      (CTL_BASE_ANA_GLB + 0x0350)
#define ANA_REG_GLB_BG_CTRL               (CTL_BASE_ANA_GLB + 0x0354)
#define ANA_REG_GLB_DCDC_VLG_SEL0         (CTL_BASE_ANA_GLB + 0x0358)
#define ANA_REG_GLB_DCDC_VLG_SEL1         (CTL_BASE_ANA_GLB + 0x035C)
#define ANA_REG_GLB_LDO_VLG_SEL0          (CTL_BASE_ANA_GLB + 0x0360)
#define ANA_REG_GLB_LDO_VLG_SEL1          (CTL_BASE_ANA_GLB + 0x0364)
#define ANA_REG_GLB_CLK32KLESS_CTRL0      (CTL_BASE_ANA_GLB + 0x0368)
#define ANA_REG_GLB_CLK32KLESS_CTRL1      (CTL_BASE_ANA_GLB + 0x036C)
#define ANA_REG_GLB_CLK32KLESS_CTRL2      (CTL_BASE_ANA_GLB + 0x0370)
#define ANA_REG_GLB_CLK32KLESS_CTRL3      (CTL_BASE_ANA_GLB + 0x0374)
#define ANA_REG_GLB_XTL_WAIT_CTRL0        (CTL_BASE_ANA_GLB + 0x0378)
#define ANA_REG_GLB_CLK_26M_SEL           (CTL_BASE_ANA_GLB + 0x037C)
#define ANA_REG_GLB_RGB_CTRL0             (CTL_BASE_ANA_GLB + 0x0380)
#define ANA_REG_GLB_IB_CTRL               (CTL_BASE_ANA_GLB + 0x0384)
#define ANA_REG_GLB_KPLED_CTRL0           (CTL_BASE_ANA_GLB + 0x0388)
#define ANA_REG_GLB_KPLED_CTRL1           (CTL_BASE_ANA_GLB + 0x038C)
#define ANA_REG_GLB_VIBR_CTRL0            (CTL_BASE_ANA_GLB + 0x0390)
#define ANA_REG_GLB_AUDIO_CTRL0           (CTL_BASE_ANA_GLB + 0x0394)
#define ANA_REG_GLB_CHGR_CTRL             (CTL_BASE_ANA_GLB + 0x0398)
#define ANA_REG_GLB_CHGR_STATUS           (CTL_BASE_ANA_GLB + 0x039C)
#define ANA_REG_GLB_CHGR_DET_FGU_CTRL     (CTL_BASE_ANA_GLB + 0x03A0)
#define ANA_REG_GLB_OVLO_CTRL             (CTL_BASE_ANA_GLB + 0x03A4)
#define ANA_REG_GLB_MIXED_CTRL            (CTL_BASE_ANA_GLB + 0x03A8)
#define ANA_REG_GLB_POR_RST_MONITOR       (CTL_BASE_ANA_GLB + 0x03AC)
#define ANA_REG_GLB_WDG_RST_MONITOR       (CTL_BASE_ANA_GLB + 0x03B0)
#define ANA_REG_GLB_POR_PIN_RST_MONITOR   (CTL_BASE_ANA_GLB + 0x03B4)
#define ANA_REG_GLB_POR_SRC_FLAG          (CTL_BASE_ANA_GLB + 0x03B8)
#define ANA_REG_GLB_POR_OFF_FLAG          (CTL_BASE_ANA_GLB + 0x03BC)
#define ANA_REG_GLB_POR_7S_CTRL           (CTL_BASE_ANA_GLB + 0x03C0)
#define ANA_REG_GLB_HWRST_RTC             (CTL_BASE_ANA_GLB + 0x03C4)
#define ANA_REG_GLB_ARCH_EN               (CTL_BASE_ANA_GLB + 0x03C8)
#define ANA_REG_GLB_MCU_WR_PROT_VALUE     (CTL_BASE_ANA_GLB + 0x03CC)
#define ANA_REG_GLB_PWR_WR_PROT_VALUE     (CTL_BASE_ANA_GLB + 0x03D0)
#define ANA_REG_GLB_DCDC_WR_PROT_VALUE    (CTL_BASE_ANA_GLB + 0x03D4)
#define ANA_REG_GLB_TSX_WR_PROT_VALUE     (CTL_BASE_ANA_GLB + 0x03D8)
#define ANA_REG_GLB_SMPL_CTRL0            (CTL_BASE_ANA_GLB + 0x03DC)
#define ANA_REG_GLB_SMPL_CTRL1            (CTL_BASE_ANA_GLB + 0x03E0)
#define ANA_REG_GLB_RTC_RST0              (CTL_BASE_ANA_GLB + 0x03E4)
#define ANA_REG_GLB_RTC_RST1              (CTL_BASE_ANA_GLB + 0x03E8)
#define ANA_REG_GLB_RTC_RST2              (CTL_BASE_ANA_GLB + 0x03EC)
#define ANA_REG_GLB_RTC_CLK_STOP          (CTL_BASE_ANA_GLB + 0x03F0)
#define ANA_REG_GLB_VBAT_DROP_CNT         (CTL_BASE_ANA_GLB + 0x03F4)
#define ANA_REG_GLB_SWRST_CTRL0           (CTL_BASE_ANA_GLB + 0x03F8)
#define ANA_REG_GLB_HW_RST_CTRL           (CTL_BASE_ANA_GLB + 0x03FC)
#define ANA_REG_GLB_SWRST_CTRL1           (CTL_BASE_ANA_GLB + 0x0400)
#define ANA_REG_GLB_OTP_CTRL              (CTL_BASE_ANA_GLB + 0x0404)
#define ANA_REG_GLB_FREE_TIMER_LOW        (CTL_BASE_ANA_GLB + 0x0408)
#define ANA_REG_GLB_FREE_TIMER_HIGH       (CTL_BASE_ANA_GLB + 0x040C)
#define ANA_REG_GLB_LOW_PWR_CLK32K_CTRL   (CTL_BASE_ANA_GLB + 0x0410)
#define ANA_REG_GLB_VOL_TUNE_CTRL_CORE    (CTL_BASE_ANA_GLB + 0x0414)
#define ANA_REG_GLB_VOL_TUNE_CTRL_CPU     (CTL_BASE_ANA_GLB + 0x0418)
#define ANA_REG_GLB_VOL_TUNE_CTRL_GPU     (CTL_BASE_ANA_GLB + 0x041C)
#define ANA_REG_GLB_VOL_TUNE_CTRL_MODEM   (CTL_BASE_ANA_GLB + 0x0420)
#define ANA_REG_GLB_DCDC_DVFS_EN          (CTL_BASE_ANA_GLB + 0x0424)
#define ANA_REG_GLB_DCDC_DVS_REG0         (CTL_BASE_ANA_GLB + 0x0428)
#define ANA_REG_GLB_DCDC_DVS_REG1         (CTL_BASE_ANA_GLB + 0x042C)
#define ANA_REG_GLB_DCDC_DVS_REG2         (CTL_BASE_ANA_GLB + 0x0430)
#define ANA_REG_GLB_DCDC_DVS_REG3         (CTL_BASE_ANA_GLB + 0x0434)
#define ANA_REG_GLB_ENDURA_REG0           (CTL_BASE_ANA_GLB + 0x0438)
#define ANA_REG_GLB_ENDURA_REG1           (CTL_BASE_ANA_GLB + 0x043C)
#define ANA_REG_GLB_ENDURA_REG2           (CTL_BASE_ANA_GLB + 0x0440)
#define ANA_REG_GLB_ENDURA_REG3           (CTL_BASE_ANA_GLB + 0x0444)
#define ANA_REG_GLB_ENDURA_REG4           (CTL_BASE_ANA_GLB + 0x0448)

#define ANA_REG_GLB_ARM_MODULE_EN               ANA_REG_GLB_MODULE_EN0
#define ANA_REG_GLB_RTC_CLK_EN                  ANA_REG_GLB_RTC_CLK_EN0
#define ANA_REG_GLB_LDO_SD_PD_REG	ANA_REG_GLB_LDO_VDDSDCORE_REG0
#define ANA_REG_GLB_LDO_SDIO_PD_REG	ANA_REG_GLB_LDO_VDDSDIO_REG0
#define ANA_REG_GLB_LDO_SD_REG1		ANA_REG_GLB_LDO_VDDSDCORE_REG1
#define ANA_REG_GLB_LDO_SDIO_REG1	ANA_REG_GLB_LDO_VDDSDIO_REG1
/* ANA_REG_GLB_CHIP_ID_LOW */

#define BITS_CHIP_ID_LOW(x)                       (((x) & 0xFFFF))

/* ANA_REG_GLB_CHIP_ID_HIGH */

#define BITS_CHIP_ID_HIGH(x)                      (((x) & 0xFFFF))

/* ANA_REG_GLB_MODULE_EN0 */

#define BIT_TYPEC_EN                             BIT(14)
#define BIT_PD_EN                                BIT(13)
#define BIT_TMR_EN                               BIT(12)
#define BIT_FAST_CHG_EN                          BIT(11)
#define BIT_BLTC_EN                              BIT(9)
#define BIT_PINREG_EN                            BIT(8)
#define BIT_FGU_EN                               BIT(7)
#define BIT_EFS_EN                               BIT(6)
#define BIT_ADC_EN                               BIT(5)
#define BIT_AUD_EN                               BIT(4)
#define BIT_EIC_EN                               BIT(3)
#define BIT_WDG_EN                               BIT(2)
#define BIT_RTC_EN                               BIT(1)
#define BIT_CAL_EN                               BIT(0)

#define BIT_ANA_WDG_EN                   BIT_WDG_EN
/*ANA_REG_GLB_ARM_CLK_EN0 */

#define BIT_CLK_PD_SEL                           BIT(10)
#define BIT_CLK_PD_EN                            BIT(9)
#define BIT_CLK_TSEN_ADC_EN                      BIT(8)
#define BIT_CLK_AUD_SCLK_EN                      BIT(7)
#define BIT_CLK_AUXAD_EN                         BIT(6)
#define BIT_CLK_AUXADC_EN                        BIT(5)
#define BITS_CLK_CAL_SRC_SEL(x)                   (((x) & 0x3) << 3)
#define BIT_CLK_CAL_EN                           BIT(2)
#define BIT_CLK_AUD_IF_6P5M_EN                   BIT(1)
#define BIT_CLK_AUD_IF_EN                        BIT(0)

/* ANA_REG_GLB_RTC_CLK_EN0 */

#define BIT_RTC_PD_EN                            BIT(15)
#define BIT_RTC_TYPEC_EN                         BIT(14)
#define BIT_RTC_TMR_EN                           BIT(13)
#define BIT_RTC_EFS_EN                           BIT(11)
#define BIT_RTC_BLTC_EN                          BIT(7)
#define BIT_RTC_FGU_EN                           BIT(6)
#define BIT_RTC_FAST_CHG_EN                      BIT(4)
#define BIT_RTC_EIC_EN                           BIT(3)
#define BIT_RTC_WDG_EN                           BIT(2)
#define BIT_RTC_RTC_EN                           BIT(1)
#define BIT_RTC_ARCH_EN                          BIT(0)

/* ANA_REG_GLB_SOFT_RST0 */

#define BIT_AUDRX_SOFT_RST                       BIT(13)
#define BIT_AUDTX_SOFT_RST                       BIT(12)
#define BIT_BLTC_SOFT_RST                        BIT(9)
#define BIT_AUD_SOFT_RST                         BIT(8)
#define BIT_EFS_SOFT_RST                         BIT(7)
#define BIT_ADC_SOFT_RST                         BIT(6)
#define BIT_FGU_SOFT_RST                         BIT(4)
#define BIT_EIC_SOFT_RST                         BIT(3)
#define BIT_WDG_SOFT_RST                         BIT(2)
#define BIT_RTC_SOFT_RST                         BIT(1)
#define BIT_CAL_SOFT_RST                         BIT(0)

/* ANA_REG_GLB_SOFT_RST1 */

#define BIT_TYPEC_SOFT_RST                       BIT(3)
#define BIT_PD_SOFT_RST                          BIT(2)
#define BIT_TMR_SOFT_RST                         BIT(1)
#define BIT_FAST_CHG_SOFT_RST                    BIT(0)

/* ANA_REG_GLB_POWER_PD_SW */

#define BIT_DCDC_SRAM_PD                         BIT(13)
#define BIT_DCDC_MEMQ_PD                         BIT(12)
#define BIT_DCDC_MODEM_PD                        BIT(11)
#define BIT_LDO_VDD18_DCXO_PD                    BIT(10)
#define BIT_LDO_EMM_PD                           BIT(9)
#define BIT_DCDC_GEN0_PD                         BIT(8)
#define BIT_DCDC_GEN1_PD                         BIT(7)
#define BIT_DCDC_MEM_PD                          BIT(6)
#define BIT_DCDC_CORE_PD                         BIT(5)
#define BIT_DCDC_CPU_PD                          BIT(4)
#define BIT_DCDC_GPU_PD                          BIT(3)
#define BIT_LDO_AVDD18_PD                        BIT(2)
#define BIT_LDO_VDD28_PD                         BIT(1)
#define BIT_BG_PD                                BIT(0)

/* ANA_REG_GLB_POWER_PD_HW */

#define BIT_PWR_OFF_SEQ_EN                       BIT(0)

/* ANA_REG_GLB_SOFT_RST_HW */

#define BIT_REG_SOFT_RST                         BIT(0)

/* ANA_REG_GLB_RESERVED_REG0 */


/* ANA_REG_GLB_RESERVED_REG1 */


/* ANA_REG_GLB_RESERVED_REG2 */


/* ANA_REG_GLB_RESERVED_REG3 */


/* ANA_REG_GLB_DCDC_CPU_REG0 */

#define BITS_DCDC_CPU_DEADTIME(x)                 (((x) & 0x3) << 14)
#define BITS_DCDC_CPU_PDRSLOW(x)                  (((x) & 0xF) << 4)
#define BIT_DCDC_CPU_PFMB                        BIT(2)
#define BIT_DCDC_CPU_DCMB                        BIT(1)

/* ANA_REG_GLB_DCDC_CPU_REG1 */

#define BITS_DCDC_CPU_CF(x)                       (((x) & 0x3) << 4)
#define BITS_DCDC_CPU_CL_CTRL(x)                  (((x) & 0x3))

/* ANA_REG_GLB_DCDC_CPU_REG2 */

#define BITS_DCDC_CPU_STBOP(x)                    (((x) & 0x7F) << 6)
#define BITS_DCDC_CPU_ZCD(x)                      (((x) & 0x3) << 4)
#define BITS_DCDC_CPU_PFMAD(x)                    (((x) & 0xF))

/* ANA_REG_GLB_DCDC_CPU_VOL */

#define BIT_CLK_SEL_CPU                          BIT(15)
#define BITS_FRACTION_DIV_CPU(x)                  (((x) & 0xF) << 11)
#define BITS_INTEGER_DIV_CPU(x)                   (((x) & 0x3) << 9)
#define BITS_DCDC_CPU_CTRL(x)                     (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_GPU_REG0 */

#define BITS_DCDC_GPU_DEADTIME(x)                 (((x) & 0x3) << 14)
#define BITS_DCDC_GPU_PDRSLOW(x)                  (((x) & 0xF) << 4)
#define BIT_DCDC_GPU_PFMB                        BIT(2)
#define BIT_DCDC_GPU_DCMB                        BIT(1)

/* ANA_REG_GLB_DCDC_GPU_REG1 */

#define BITS_DCDC_GPU_CF(x)                       (((x) & 0x3) << 4)
#define BITS_DCDC_GPU_CL_CTRL(x)                  (((x) & 0x3))

/* ANA_REG_GLB_DCDC_GPU_REG2 */

#define BITS_DCDC_GPU_STBOP(x)                    (((x) & 0x7F) << 6)
#define BITS_DCDC_GPU_ZCD(x)                      (((x) & 0x3) << 4)
#define BITS_DCDC_GPU_PFMAD(x)                    (((x) & 0xF))

/* ANA_REG_GLB_DCDC_GPU_VOL */

#define BIT_CLK_SEL_GPU                          BIT(15)
#define BITS_FRACTION_DIV_GPU(x)                  (((x) & 0xF) << 11)
#define BITS_INTEGER_DIV_GPU(x)                   (((x) & 0x3) << 9)
#define BITS_DCDC_GPU_CTRL(x)                     (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_CORE_REG0 */

#define BITS_DCDC_CORE_DEADTIME(x)                (((x) & 0x3) << 14)
#define BITS_DCDC_CORE_PDRSLOW(x)                 (((x) & 0xF) << 4)
#define BIT_DCDC_CORE_PFMB                       BIT(2)
#define BIT_DCDC_CORE_DCMB                       BIT(1)

/* ANA_REG_GLB_DCDC_CORE_REG1 */

#define BITS_DCDC_CORE_CF(x)                      (((x) & 0x3) << 4)
#define BITS_DCDC_CORE_CL_CTRL(x)                 (((x) & 0x3))

/* ANA_REG_GLB_DCDC_CORE_REG2 */

#define BITS_DCDC_CORE_STBOP(x)                   (((x) & 0x7F) << 6)
#define BITS_DCDC_CORE_ZCD(x)                     (((x) & 0x3) << 4)
#define BITS_DCDC_CORE_PFMAD(x)                   (((x) & 0xF))

/* ANA_REG_GLB_DCDC_CORE_VOL */

#define BIT_CLK_SEL_CORE                         BIT(15)
#define BITS_FRACTION_DIV_CORE(x)                 (((x) & 0xF) << 11)
#define BITS_INTEGER_DIV_CORE(x)                  (((x) & 0x3) << 9)
#define BITS_DCDC_CORE_CTRL(x)                    (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_MODEM_REG0 */

#define BITS_DCDC_MODEM_DEADTIME(x)               (((x) & 0x3) << 14)
#define BITS_DCDC_MODEM_PDRSLOW(x)                (((x) & 0xF) << 4)
#define BIT_DCDC_MODEM_PFMB                      BIT(2)
#define BIT_DCDC_MODEM_DCMB                      BIT(1)

/* ANA_REG_GLB_DCDC_MODEM_REG1 */

#define BITS_DCDC_MODEM_CF(x)                     (((x) & 0x3) << 4)
#define BITS_DCDC_MODEM_CL_CTRL(x)                (((x) & 0x3))

/* ANA_REG_GLB_DCDC_MODEM_REG2 */

#define BITS_DCDC_MODEM_STBOP(x)                  (((x) & 0x7F) << 6)
#define BITS_DCDC_MODEM_ZCD(x)                    (((x) & 0x3) << 4)
#define BITS_DCDC_MODEM_PFMAD(x)                  (((x) & 0xF))

/* ANA_REG_GLB_DCDC_MODEM_VOL */

#define BIT_CLK_SEL_MODEM                        BIT(15)
#define BITS_FRACTION_DIV_MODEM(x)                (((x) & 0xF) << 11)
#define BITS_INTEGER_DIV_MODEM(x)                 (((x) & 0x3) << 9)
#define BITS_DCDC_MODEM_CTRL(x)                   (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_MEM_REG0 */

#define BITS_DCDC_MEM_DEADTIME(x)                 (((x) & 0x3) << 14)
#define BITS_DCDC_MEM_PDRSLOW(x)                  (((x) & 0xF) << 4)
#define BIT_DCDC_MEM_PFMB                        BIT(2)
#define BIT_DCDC_MEM_DCMB                        BIT(1)

/* ANA_REG_GLB_DCDC_MEM_REG1 */

#define BITS_DCDC_MEM_CF(x)                       (((x) & 0x3) << 4)
#define BITS_DCDC_MEM_CL_CTRL(x)                  (((x) & 0x3))

/* ANA_REG_GLB_DCDC_MEM_REG2 */

#define BITS_DCDC_MEM_STBOP(x)                    (((x) & 0x7F) << 6)
#define BITS_DCDC_MEM_ZCD(x)                      (((x) & 0x3) << 4)
#define BITS_DCDC_MEM_PFMAD(x)                    (((x) & 0xF))

/* ANA_REG_GLB_DCDC_MEM_VOL */

#define BITS_DCDC_MEM_CTRL(x)                     (((x) & 0xFF))

/* ANA_REG_GLB_DCDC_MEMQ_REG0 */

#define BITS_DCDC_MEMQ_DEADTIME(x)                (((x) & 0x3) << 14)
#define BITS_DCDC_MEMQ_PDRSLOW(x)                 (((x) & 0xF) << 4)
#define BIT_DCDC_MEMQ_PFMB                       BIT(2)
#define BIT_DCDC_MEMQ_DCMB                       BIT(1)

/* ANA_REG_GLB_DCDC_MEMQ_REG1 */

#define BITS_DCDC_MEMQ_CF(x)                      (((x) & 0x3) << 4)
#define BITS_DCDC_MEMQ_CL_CTRL(x)                 (((x) & 0x3))

/* ANA_REG_GLB_DCDC_MEMQ_REG2 */

#define BITS_DCDC_MEMQ_STBOP(x)                   (((x) & 0x7F) << 6)
#define BITS_DCDC_MEMQ_ZCD(x)                     (((x) & 0x3) << 4)
#define BITS_DCDC_MEMQ_PFMAD(x)                   (((x) & 0xF))

/* ANA_REG_GLB_DCDC_MEMQ_VOL */

#define BITS_DCDC_MEMQ_CTRL(x)                    (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_GEN0_REG0 */

#define BITS_DCDC_GEN0_DEADTIME(x)                (((x) & 0x3) << 14)
#define BITS_DCDC_GEN0_PDRSLOW(x)                 (((x) & 0xF) << 4)
#define BIT_DCDC_GEN0_PFMB                       BIT(2)
#define BIT_DCDC_GEN0_DCMB                       BIT(1)

/* ANA_REG_GLB_DCDC_GEN0_REG1 */

#define BITS_DCDC_GEN0_CF(x)                      (((x) & 0x3) << 4)
#define BITS_DCDC_GEN0_CL_CTRL(x)                 (((x) & 0x3))

/* ANA_REG_GLB_DCDC_GEN0_REG2 */

#define BITS_DCDC_GEN0_STBOP(x)                   (((x) & 0x7F) << 6)
#define BITS_DCDC_GEN0_ZCD(x)                     (((x) & 0x3) << 4)
#define BITS_DCDC_GEN0_PFMAD(x)                   (((x) & 0xF))

/* ANA_REG_GLB_DCDC_GEN0_VOL */

#define BITS_DCDC_GEN0_CTRL(x)                    (((x) & 0xFF))

/* ANA_REG_GLB_DCDC_GEN1_REG0 */

#define BITS_DCDC_GEN1_DEADTIME(x)                (((x) & 0x3) << 14)
#define BITS_DCDC_GEN1_PDRSLOW(x)                 (((x) & 0xF) << 4)
#define BIT_DCDC_GEN1_PFMB                       BIT(2)
#define BIT_DCDC_GEN1_DCMB                       BIT(1)

/* ANA_REG_GLB_DCDC_GEN1_REG1 */

#define BITS_DCDC_GEN1_CF(x)                      (((x) & 0x3) << 4)
#define BITS_DCDC_GEN1_CL_CTRL(x)                 (((x) & 0x3))

/* ANA_REG_GLB_DCDC_GEN1_REG2 */

#define BITS_DCDC_GEN1_STBOP(x)                   (((x) & 0x7F) << 6)
#define BITS_DCDC_GEN1_ZCD(x)                     (((x) & 0x3) << 4)
#define BITS_DCDC_GEN1_PFMAD(x)                   (((x) & 0xF))

/* ANA_REG_GLB_DCDC_GEN1_VOL */

#define BITS_DCDC_GEN1_CTRL(x)                    (((x) & 0xFF))

/* ANA_REG_GLB_DCDC_WPA_REG0 */

#define BITS_DCDC_WPA_DEADTIME(x)                 (((x) & 0x3) << 14)
#define BITS_DCDC_WPA_PDRSLOW(x)                  (((x) & 0xF) << 4)
#define BITS_DCDC_WPA_CF(x)                       (((x) & 0x3) << 2)
#define BITS_DCDC_WPA_CL_CTRL(x)                  (((x) & 0x3))

/* ANA_REG_GLB_DCDC_WPA_REG1 */

#define BIT_DCDC_WPA_BPOUT_SOFTW                 BIT(15)
#define BITS_DCDC_WPA_VBAT_DIV(x)                 (((x) & 0x7) << 12)
#define BIT_DCDC_WPA_BPEN                        BIT(11)
#define BIT_DCDC_WPA_BPMODE                      BIT(10)
#define BIT_DCDC_WPA_DEGEN                       BIT(9)
#define BIT_DCDC_WPA_APTEN                       BIT(8)
#define BITS_DCDC_WPA_DEBC_SEL(x)                 (((x) & 0x3) << 6)
#define BITS_DCDC_WPA_FRTHRD(x)                   (((x) & 0x3) << 4)
#define BIT_DCDC_WPA_FREN                        BIT(3)
#define BIT_DCDC_WPA_DEG_CUR_SEL                 BIT(2)
#define BIT_DCDC_WPA_PFMB                        BIT(1)
#define BIT_DCDC_WPA_APT2P5XEN                   BIT(0)

/* ANA_REG_GLB_DCDC_WPA_REG2 */

#define BIT_DCDC_WPA_PD                          BIT(5)
#define BITS_DCDC_WPA_VREF_CAL(x)                 (((x) & 0x1F))

/* ANA_REG_GLB_DCDC_WPA_REG3 */

#define BITS_DCDC_WPA_STBOP(x)                    (((x) & 0x7F) << 6)
#define BITS_DCDC_WPA_ZCD(x)                      (((x) & 0x3) << 4)
#define BITS_DCDC_WPA_PFMAD(x)                    (((x) & 0xF))

/* ANA_REG_GLB_DCDC_WPA_VOL */

#define BITS_DCDC_WPA_FR_CUR_CTRL(x)              (((x) & 0x3) << 10)
#define BITS_DCDC_WPA_FR_EMI_CTRL(x)              (((x) & 0x3) << 8)
#define BITS_DCDC_WPA_CTRL(x)                     (((x) & 0xFF))

/* ANA_REG_GLB_DCDC_WPA_DCMB */

#define BIT_DCDC_WPA_DCMB                        BIT(0)

/* ANA_REG_GLB_DCDC_SRAM_REG0 */

#define BITS_DCDC_SRAM_DEADTIME(x)                (((x) & 0x3) << 14)
#define BITS_DCDC_SRAM_PDRSLOW(x)                 (((x) & 0xF) << 4)
#define BIT_DCDC_SRAM_PFMB                       BIT(2)
#define BIT_DCDC_SRAM_DCMB                       BIT(1)

/* ANA_REG_GLB_DCDC_SRAM_REG1 */

#define BITS_DCDC_SRAM_CF(x)                      (((x) & 0x3) << 4)
#define BITS_DCDC_SRAM_CL_CTRL(x)                 (((x) & 0x3))

/* ANA_REG_GLB_DCDC_SRAM_REG2 */

#define BITS_DCDC_SRAM_STBOP(x)                   (((x) & 0x7F) << 6)
#define BITS_DCDC_SRAM_ZCD(x)                     (((x) & 0x3) << 4)
#define BITS_DCDC_SRAM_PFMAD(x)                   (((x) & 0xF))

/* ANA_REG_GLB_DCDC_SRAM_VOL */

#define BITS_DCDC_SRAM_CTRL(x)                    (((x) & 0x1FF))

/* ANA_REG_GLB_RESERVED_REG4 */


/* ANA_REG_GLB_DCDC_CH_CTRL */

#define BITS_DCDC_CAL_SEL(x)                      (((x) & 0xF))

/* ANA_REG_GLB_DCDC_CTRL */

#define BITS_DCDC_OSCCLK_OPTION(x)                (((x) & 0x3) << 11)
#define BITS_DCDC_ILIMITCAL(x)                    (((x) & 0x1F) << 6)
#define BIT_DCDC_CLSEL                           BIT(5)

/* ANA_REG_GLB_DCDC_CLK_CTRL */

#define BIT_DCDC_6MCLKOUT_EN                     BIT(13)
#define BITS_DCDC_6MFRECAL_SW(x)                  (((x) & 0x1F) << 7)
#define BIT_DCDC_CLK_SP_SEL                      BIT(1)
#define BIT_DCDC_CLK_SP_EN                       BIT(0)

/* ANA_REG_GLB_RESERVED_REG5 */


/* ANA_REG_GLB_RESERVED_REG6 */


/* ANA_REG_GLB_RESERVED_REG7 */


/* ANA_REG_GLB_RESERVED_REG8 */


/* ANA_REG_GLB_LDO_AVDD18_REG0 */


/* ANA_REG_GLB_LDO_AVDD18_REG1 */

#define BITS_LDO_AVDD18_V(x)                      (((x) & 0x3F))

/* ANA_REG_GLB_LDO_AVDD18_REG2 */

#define BIT_LDO_AVDD18_SHPT_PD                   BIT(5)
#define BITS_LDO_AVDD18_REFTRIM(x)                (((x) & 0x1F))

/* ANA_REG_GLB_LDO_VDDRF1V8_REG0 */

#define BIT_LDO_VDDRF1V8_PD                      BIT(0)

/* ANA_REG_GLB_LDO_VDDRF1V8_REG1 */

#define BITS_LDO_VDDRF1V8_V(x)                    (((x) & 0x3F))

/* ANA_REG_GLB_LDO_VDDRF1V8_REG2 */

#define BIT_LDO_VDDRF1V8_SHPT_PD                 BIT(5)
#define BITS_LDO_VDDRF1V8_REFTRIM(x)              (((x) & 0x1F))

/* ANA_REG_GLB_LDO_VDDCAMIO_REG0 */

#define BIT_LDO_VDDCAMIO_PD                      BIT(0)

/* ANA_REG_GLB_LDO_VDDWCN_REG0 */

#define BIT_LDO_VDDWCN_PD                        BIT(0)

/* ANA_REG_GLB_LDO_VDDWCN_REG1 */

#define BITS_LDO_VDDWCN_V(x)                      (((x) & 0x3F))

/* ANA_REG_GLB_LDO_VDDWCN_REG2 */

#define BIT_LDO_VDDWCN_SHPT_PD                   BIT(5)
#define BITS_LDO_VDDWCN_REFTRIM(x)                (((x) & 0x1F))

/* ANA_REG_GLB_LDO_VDDCAMD1_REG0 */

#define BIT_LDO_VDDCAMD1_PD                      BIT(0)

/* ANA_REG_GLB_LDO_VDDCAMD1_REG1 */

#define BITS_LDO_VDDCAMD1_V(x)                    (((x) & 0x1F))

/* ANA_REG_GLB_LDO_VDDCAMD1_REG2 */

#define BIT_LDO_VDDCAMD1_SHPT_PD                 BIT(5)
#define BITS_LDO_VDDCAMD1_REFTRIM(x)              (((x) & 0x1F))

/* ANA_REG_GLB_LDO_VDDCAMD0_REG0 */

#define BIT_LDO_VDDCAMD0_PD                      BIT(0)

/* ANA_REG_GLB_LDO_VDDCAMD0_REG1 */

#define BITS_LDO_VDDCAMD0_V(x)                    (((x) & 0x1F))

/* ANA_REG_GLB_LDO_VDDCAMD0_REG2 */

#define BIT_LDO_VDDCAMD0_SHPT_PD                 BIT(5)
#define BITS_LDO_VDDCAMD0_REFTRIM(x)              (((x) & 0x1F))

/* ANA_REG_GLB_LDO_VRF1V25_REG0 */

#define BIT_LDO_VDDRF1V25_PD                     BIT(0)

/* ANA_REG_GLB_LDO_VDDRF1V25_REG1 */

#define BITS_LDO_VDDRF1V25_V(x)                   (((x) & 0x1F))

/* ANA_REG_GLB_LDO_VRF1V25_REG2 */

#define BIT_LDO_VDDRF1V25_SHPT_PD                BIT(5)
#define BITS_LDO_VDDRF1V25_REFTRIM(x)             (((x) & 0x1F))

/* ANA_REG_GLB_LDO_AVDD12_REG0 */

#define BIT_LDO_AVDD12_PD                        BIT(0)

/* ANA_REG_GLB_LDO_AVDD12_REG1 */

#define BITS_LDO_AVDD12_V(x)                      (((x) & 0x1F))

/* ANA_REG_GLB_LDO_AVDD12_REG2 */

#define BIT_LDO_AVDD12_SHPT_PD                   BIT(5)
#define BITS_LDO_AVDD12_REFTRIM(x)                (((x) & 0x1F))

/* ANA_REG_GLB_LDO_VDDCAMA0_REG0 */

#define BIT_LDO_VDDCAMA0_PD                      BIT(0)

/* ANA_REG_GLB_LDO_VDDCAMA0_REG1 */

#define BITS_LDO_VDDCAMA0_V(x)                    (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDCAMA0_REG2 */

#define BITS_LDO_VDDCAMA0_REFTRIM(x)              (((x) & 0x1F) << 2)
#define BIT_LDO_VDDCAMA0_SHPT_PD                 BIT(1)

/* ANA_REG_GLB_LDO_VDDCAMA1_REG0 */

#define BIT_LDO_VDDCAMA1_PD                      BIT(0)

/* ANA_REG_GLB_LDO_VDDCAMA1_REG1 */

#define BITS_LDO_VDDCAMA1_V(x)                    (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDCAMA1_REG2 */

#define BITS_LDO_VDDCAMA1_REFTRIM(x)              (((x) & 0x1F) << 2)
#define BIT_LDO_VDDCAMA1_SHPT_PD                 BIT(1)

/* ANA_REG_GLB_LDO_VDDCAMMOT_REG0 */

#define BIT_LDO_VDDCAMMOT_PD                     BIT(0)

/* ANA_REG_GLB_LDO_VDDCAMMOT_REG1 */

#define BITS_LDO_VDDCAMMOT_V(x)                   (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDCAMMOT_REG2 */

#define BIT_LDO_VDDCAMMOT_SHPT_PD                BIT(6)
#define BITS_LDO_VDDCAMMOT_REFTRIM(x)             (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDSIM0_REG0 */

#define BIT_LDO_VDDSIM0_PD                       BIT(0)

/* ANA_REG_GLB_LDO_VDDSIM0_REG1 */

#define BITS_LDO_VDDSIM0_V(x)                     (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDSIM0_REG2 */

#define BIT_LDO_VDDSIM0_SHPT_PD                  BIT(6)
#define BITS_LDO_VDDSIM0_REFTRIM(x)               (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDSIM1_REG0 */

#define BIT_LDO_VDDSIM1_PD                       BIT(0)

/* ANA_REG_GLB_LDO_VDDSIM1_REG1 */

#define BITS_LDO_VDDSIM1_V(x)                     (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDSIM1_REG2 */

#define BIT_LDO_VDDSIM1_SHPT_PD                  BIT(6)
#define BITS_LDO_VDDSIM1_REFTRIM(x)               (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDSIM2_REG0 */

#define BIT_LDO_VDDSIM2_PD                       BIT(0)

/* ANA_REG_GLB_LDO_VDDSIM2_REG1 */

#define BITS_LDO_VDDSIM2_V(x)                     (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDSIM2_REG2 */

#define BIT_LDO_VDDSIM2_SHPT_PD                  BIT(6)
#define BITS_LDO_VDDSIM2_REFTRIM(x)               (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDEMMCCORE_REG0 */

#define BIT_LDO_VDDEMMCCORE_PD                   BIT(0)

/* ANA_REG_GLB_LDO_VDDEMMCCORE_REG1 */

#define BITS_LDO_VDDEMMCCORE_V(x)                 (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDEMMCCORE_REG2 */

#define BIT_LDO_VDDEMMCCORE_SHPT_PD              BIT(6)
#define BITS_LDO_VDDEMMCCORE_REFTRIM(x)           (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDSDCORE_REG0 */

#define BIT_LDO_VDDSDCORE_PD                     BIT(0)
#define BIT_LDO_SDCORE_PD                     BIT_LDO_VDDSDCORE_PD

/* ANA_REG_GLB_LDO_VDDSDCORE_REG1 */

#define BITS_LDO_VDDSDCORE_V(x)                   (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDSDCORE_REG2 */

#define BITS_LDO_VDDSDCORE_CL_ADJ(x)              (((x) & 0x1F) << 7)
#define BIT_LDO_VDDSDCORE_SHPT_PD                BIT(6)
#define BITS_LDO_VDDSDCORE_REFTRIM(x)             (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDSDIO_REG0 */

#define BIT_LDO_VDDSDIO_PD                       BIT(0)
#define BIT_LDO_SDIO_PD                       BIT_LDO_VDDSDIO_PD

/* ANA_REG_GLB_LDO_VDDSDIO_REG1 */

#define BITS_LDO_VDDSDIO_V(x)                     (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDSDIO_REG2 */

#define BIT_LDO_VDDSDIO_SHPT_PD                  BIT(6)
#define BITS_LDO_VDDSDIO_REFTRIM(x)               (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDD28_REG0 */


/* ANA_REG_GLB_LDO_VDD28_REG1 */

#define BITS_LDO_VDD28_V(x)                       (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDD28_REG2 */

#define BIT_LDO_VDD28_SHPT_PD                    BIT(6)
#define BITS_LDO_VDD28_REFTRIM(x)                 (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDWIFIPA_REG0 */

#define BIT_LDO_VDDWIFIPA_PD                     BIT(0)

/* ANA_REG_GLB_LDO_VDDWIFIPA_REG1 */

#define BITS_LDO_VDDWIFIPA_V(x)                   (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDWIFIPA_REG2 */

#define BIT_LDO_VDDWIFIPA_SHPT_PD                BIT(6)
#define BITS_LDO_VDDWIFIPA_REFTRIM(x)             (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDD18_DCXO_REG0 */


/* ANA_REG_GLB_LDO_VDD18_DCXO_REG1 */

#define BITS_LDO_VDD18_DCXO_V(x)                  (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDD18_DCXO_REG2 */

#define BITS_LDO_VDD18_DCXO_REFTRIM_LP(x)         (((x) & 0xF) << 7)
#define BIT_LDO_VDD18_DCXO_SHPT_PD               BIT(6)
#define BITS_LDO_VDD18_DCXO_REFTRIM(x)            (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDUSB33_REG0 */

#define BIT_LDO_VDDUSB33_PD                      BIT(0)

/* ANA_REG_GLB_LDO_VDDUSB33_REG1 */

#define BITS_LDO_VDDUSB33_V(x)                    (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDUSB33_REG2 */

#define BIT_LDO_VDDUSB33_SHPT_PD                 BIT(6)
#define BITS_LDO_VDDUSB33_REFTRIM(x)              (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDLDO0_REG0 */

#define BIT_LDO_VDDLDO0_PD                       BIT(0)

/* ANA_REG_GLB_LDO_VDDLDO0_REG1 */

#define BITS_LDO_VDDLDO0_V(x)                     (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDLDO0_REG2 */

#define BIT_LDO_VDDLDO0_SHPT_PD                  BIT(6)
#define BITS_LDO_VDDLDO0_REFTRIM(x)               (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDLDO1_REG0 */

#define BIT_LDO_VDDLDO1_PD                       BIT(0)

/* ANA_REG_GLB_LDO_VDDLDO1_REG1 */

#define BITS_LDO_VDDLDO1_V(x)                     (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDLDO1_REG2 */

#define BIT_LDO_VDDLDO1_SHPT_PD                  BIT(6)
#define BITS_LDO_VDDLDO1_REFTRIM(x)               (((x) & 0x1F) << 1)

/* ANA_REG_GLB_LDO_VDDLDO2_REG0 */

#define BIT_LDO_VDDLDO2_PD                       BIT(0)

/* ANA_REG_GLB_LDO_VDDLDO2_REG1 */

#define BITS_LDO_VDDLDO2_V(x)                     (((x) & 0xFF))

/* ANA_REG_GLB_LDO_VDDLDO2_REG2 */

#define BIT_LDO_VDDLDO2_SHPT_PD                  BIT(6)
#define BITS_LDO_VDDLDO2_REFTRIM(x)               (((x) & 0x1F) << 1)

/* ANA_REG_GLB_RESERVED_REG9 */


/* ANA_REG_GLB_RESERVED_REG10 */


/* ANA_REG_GLB_RESERVED_REG11 */


/* ANA_REG_GLB_RESERVED_REG12 */


/* ANA_REG_GLB_LDO_RTC_CTRL */

#define BITS_RC1M_CAL(x)                          (((x) & 0x7F) << 9)
#define BITS_LDO_RTC_CAL(x)                       (((x) & 0x1F) << 4)
#define BITS_LDO_RTC_V(x)                         (((x) & 0x3) << 2)
#define BITS_VBATBK_V(x)                          (((x) & 0x3))

/* ANA_REG_GLB_LDO_CH_CTRL */

#define BITS_LDODCDC_CAL_SEL(x)                   (((x) & 0x7) << 11)
#define BITS_LDOA_CAL_SEL(x)                      (((x) & 0xF) << 7)
#define BITS_LDOB_CAL_SEL(x)                      (((x) & 0x7) << 4)

/* ANA_REG_GLB_RESERVED_REG13 */


/* ANA_REG_GLB_RESERVED_REG14 */


/* ANA_REG_GLB_RESERVED_REG15 */


/* ANA_REG_GLB_RESERVED_REG16 */


/* ANA_REG_GLB_RESERVED_REG17 */


/* ANA_REG_GLB_SLP_WAIT_DCDCCPU */

#define BITS_SLP_IN_WAIT_DCDCCPU(x)               (((x) & 0xFF) << 8)
#define BITS_SLP_OUT_WAIT_DCDCCPU(x)              (((x) & 0xFF))

/* ANA_REG_GLB_SLP_CTRL */

#define BIT_LDO_XTL_EN                           BIT(2)
#define BIT_SLP_IO_EN                            BIT(1)
#define BIT_SLP_LDO_PD_EN                        BIT(0)

/* ANA_REG_GLB_SLP_DCDC_PD_CTRL */

#define BIT_SLP_DCDCMODEM_PD_EN                  BIT(10)
#define BIT_SLP_DCDCMEMQ_PD_EN                   BIT(9)
#define BIT_SLP_DCDCSRAM_PD_EN                   BIT(8)
#define BIT_SLP_DCDCSRAM_DROP_EN                 BIT(7)
#define BIT_SLP_DCDCMODEM_DROP_EN                BIT(6)
#define BIT_SLP_DCDCGPU_DROP_EN                  BIT(5)
#define BIT_SLP_DCDCCORE_DROP_EN                 BIT(4)
#define BIT_SLP_DCDCWPA_PD_EN                    BIT(3)
#define BIT_SLP_DCDCGPU_PD_EN                    BIT(2)
#define BIT_SLP_DCDCCPU_PD_EN                    BIT(1)
#define BIT_SLP_DCDCGEN1_PD_EN                   BIT(0)

/* ANA_REG_GLB_SLP_LDO_PD_CTRL0 */

#define BIT_SLP_LDO_VDDRF1V8_PD_EN               BIT(14)
#define BIT_SLP_LDO_VDDRF1V25_PD_EN              BIT(13)
#define BIT_SLP_LDO_VDDEMMCCORE_PD_EN            BIT(12)
#define BIT_SLP_LDO_VDD18_DCXO_PD_EN             BIT(11)
#define BIT_SLP_LDO_VDDWIFIPA_PD_EN              BIT(10)
#define BIT_SLP_LDO_VDD28_PD_EN                  BIT(9)
#define BIT_SLP_LDO_VDDSDCORE_PD_EN              BIT(8)
#define BIT_SLP_LDO_VDDSDIO_PD_EN                BIT(7)
#define BIT_SLP_LDO_VDDUSB33_PD_EN               BIT(6)
#define BIT_SLP_LDO_VDDCAMMOT_PD_EN              BIT(5)
#define BIT_SLP_LDO_VDDCAMIO_PD_EN               BIT(4)
#define BIT_SLP_LDO_VDDCAMD0_PD_EN               BIT(3)
#define BIT_SLP_LDO_VDDCAMA0_PD_EN               BIT(2)
#define BIT_SLP_LDO_VDDSIM2_PD_EN                BIT(1)
#define BIT_SLP_LDO_VDDSIM1_PD_EN                BIT(0)

/* ANA_REG_GLB_SLP_LDO_PD_CTRL1 */

#define BIT_SLP_LDO_VDDLDO2_PD_EN                BIT(8)
#define BIT_SLP_LDO_AVDD12_PD_EN                 BIT(7)
#define BIT_SLP_LDO_VDDWCN_PD_EN                 BIT(6)
#define BIT_SLP_LDO_VDDLDO0_PD_EN                BIT(5)
#define BIT_SLP_LDO_VDDCAMD1_PD_EN               BIT(4)
#define BIT_SLP_LDO_VDDCAMA1_PD_EN               BIT(3)
#define BIT_SLP_LDO_VDDSIM0_PD_EN                BIT(2)
#define BIT_SLP_LDO_AVDD18_PD_EN                 BIT(1)
#define BIT_SLP_LDO_VDDLDO1_PD_EN                BIT(0)

/* ANA_REG_GLB_SLP_DCDC_LP_CTRL */

#define BIT_SLP_DCDCSRAM_LP_EN                   BIT(9)
#define BIT_SLP_DCDCMODEM_LP_EN                  BIT(8)
#define BIT_SLP_DCDCMEMQ_LP_EN                   BIT(7)
#define BIT_SLP_DCDCMEM_LP_EN                    BIT(6)
#define BIT_SLP_DCDCGPU_LP_EN                    BIT(5)
#define BIT_SLP_DCDCCORE_LP_EN                   BIT(4)
#define BIT_SLP_DCDCCPU_LP_EN                    BIT(3)
#define BIT_SLP_DCDCGEN1_LP_EN                   BIT(2)
#define BIT_SLP_DCDCGEN0_LP_EN                   BIT(1)
#define BIT_SLP_DCDCWPA_LP_EN                    BIT(0)

/* ANA_REG_GLB_SLP_LDO_LP_CTRL0 */

#define BIT_SLP_LDO_VDDRF1V8_LP_EN               BIT(14)
#define BIT_SLP_LDO_VDDRF1V25_LP_EN              BIT(13)
#define BIT_SLP_LDO_VDDEMMCCORE_LP_EN            BIT(12)
#define BIT_SLP_LDO_VDD18_DCXO_LP_EN             BIT(11)
#define BIT_SLP_LDO_VDDWIFIPA_LP_EN              BIT(10)
#define BIT_SLP_LDO_VDD28_LP_EN                  BIT(9)
#define BIT_SLP_LDO_VDDSDCORE_LP_EN              BIT(8)
#define BIT_SLP_LDO_VDDSDIO_LP_EN                BIT(7)
#define BIT_SLP_LDO_VDDUSB33_LP_EN               BIT(6)
#define BIT_SLP_LDO_VDDCAMMOT_LP_EN              BIT(5)
#define BIT_SLP_LDO_VDDCAMD0_LP_EN               BIT(3)
#define BIT_SLP_LDO_VDDCAMA0_LP_EN               BIT(2)
#define BIT_SLP_LDO_VDDSIM2_LP_EN                BIT(1)
#define BIT_SLP_LDO_VDDSIM1_LP_EN                BIT(0)

/* ANA_REG_GLB_SLP_LDO_LP_CTRL1 */

#define BIT_SLP_LDO_VDDLDO2_LP_EN                BIT(8)
#define BIT_SLP_LDO_AVDD12_LP_EN                 BIT(7)
#define BIT_SLP_LDO_VDDWCN_LP_EN                 BIT(6)
#define BIT_SLP_LDO_VDDCAMD1_LP_EN               BIT(5)
#define BIT_SLP_LDO_VDDCAMA1_LP_EN               BIT(4)
#define BIT_SLP_LDO_VDDLDO0_LP_EN                BIT(3)
#define BIT_SLP_LDO_VDDSIM0_LP_EN                BIT(2)
#define BIT_SLP_LDO_AVDD18_LP_EN                 BIT(1)
#define BIT_SLP_LDO_VDDLDO1_LP_EN                BIT(0)

/* ANA_REG_GLB_DCDC_CORE_SLP_CTRL0 */

#define BITS_DCDC_CORE_SLP_STEP_DELAY(x)          (((x) & 0x3) << 12)
#define BITS_DCDC_CORE_SLP_STEP_NUM(x)            (((x) & 0xF) << 8)
#define BITS_DCDC_CORE_SLP_STEP_VOL(x)            (((x) & 0x1F) << 3)
#define BIT_DCDC_CORE_SLP_STEP_EN                BIT(0)

/* ANA_REG_GLB_DCDC_CORE_SLP_CTRL1 */

#define BITS_DCDC_CORE_CTRL_DS_SW(x)              (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_GPU_SLP_CTRL0 */

#define BITS_DCDC_GPU_SLP_STEP_DELAY(x)           (((x) & 0x3) << 12)
#define BITS_DCDC_GPU_SLP_STEP_NUM(x)             (((x) & 0xF) << 8)
#define BITS_DCDC_GPU_SLP_STEP_VOL(x)             (((x) & 0x1F) << 3)
#define BIT_DCDC_GPU_SLP_STEP_EN                 BIT(0)

/* ANA_REG_GLB_DCDC_GPU_SLP_CTRL1 */

#define BITS_DCDC_GPU_CTRL_DS_SW(x)               (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_CPU_SLP_CTRL0 */


/* ANA_REG_GLB_DCDC_CPU_SLP_CTRL1 */


/* ANA_REG_GLB_DCDC_MODEM_SLP_CTRL0 */

#define BITS_DCDC_MODEM_SLP_STEP_DELAY(x)         (((x) & 0x3) << 12)
#define BITS_DCDC_MODEM_SLP_STEP_NUM(x)           (((x) & 0xF) << 8)
#define BITS_DCDC_MODEM_SLP_STEP_VOL(x)           (((x) & 0x1F) << 3)
#define BIT_DCDC_MODEM_SLP_STEP_EN               BIT(0)

/* ANA_REG_GLB_DCDC_MODEM_SLP_CTRL1 */

#define BITS_DCDC_MODEM_CTRL_DS_SW(x)             (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_SRAM_SLP_CTRL0 */

#define BITS_DCDC_SRAM_SLP_STEP_DELAY(x)          (((x) & 0x3) << 12)
#define BITS_DCDC_SRAM_SLP_STEP_NUM(x)            (((x) & 0xF) << 8)
#define BITS_DCDC_SRAM_SLP_STEP_VOL(x)            (((x) & 0x1F) << 3)
#define BIT_DCDC_SRAM_SLP_STEP_EN                BIT(0)

/* ANA_REG_GLB_DCDC_SRAM_SLP_CTRL1 */

#define BITS_DCDC_SRAM_CTRL_DS_SW(x)              (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_XTL_EN */

#define BIT_DCDC_CORE_EXT_XTL0_EN                BIT(15)
#define BIT_DCDC_CORE_EXT_XTL1_EN                BIT(14)
#define BIT_DCDC_CORE_EXT_XTL2_EN                BIT(13)
#define BIT_DCDC_CORE_EXT_XTL3_EN                BIT(12)
#define BIT_DCDC_CORE_EXT_XTL4_EN                BIT(11)
#define BIT_DCDC_CORE_EXT_XTL5_EN                BIT(10)
#define BIT_DCDC_WPA_EXT_XTL0_EN                 BIT(5)
#define BIT_DCDC_WPA_EXT_XTL1_EN                 BIT(4)
#define BIT_DCDC_WPA_EXT_XTL2_EN                 BIT(3)
#define BIT_DCDC_WPA_EXT_XTL3_EN                 BIT(2)
#define BIT_DCDC_WPA_EXT_XTL4_EN                 BIT(1)
#define BIT_DCDC_WPA_EXT_XTL5_EN                 BIT(0)

/* ANA_REG_GLB_DCDC_XTL_EN0 */

#define BIT_DCDC_GEN0_EXT_XTL0_EN                BIT(15)
#define BIT_DCDC_GEN0_EXT_XTL1_EN                BIT(14)
#define BIT_DCDC_GEN0_EXT_XTL2_EN                BIT(13)
#define BIT_DCDC_GEN0_EXT_XTL3_EN                BIT(12)
#define BIT_DCDC_GEN0_EXT_XTL4_EN                BIT(11)
#define BIT_DCDC_GEN0_EXT_XTL5_EN                BIT(10)
#define BIT_DCDC_SRAM_EXT_XTL0_EN                BIT(5)
#define BIT_DCDC_SRAM_EXT_XTL1_EN                BIT(4)
#define BIT_DCDC_SRAM_EXT_XTL2_EN                BIT(3)
#define BIT_DCDC_SRAM_EXT_XTL3_EN                BIT(2)
#define BIT_DCDC_SRAM_EXT_XTL4_EN                BIT(1)
#define BIT_DCDC_SRAM_EXT_XTL5_EN                BIT(0)

/* ANA_REG_GLB_DCDC_XTL_EN1 */

#define BIT_DCDC_CPU_EXT_XTL0_EN                 BIT(15)
#define BIT_DCDC_CPU_EXT_XTL1_EN                 BIT(14)
#define BIT_DCDC_CPU_EXT_XTL2_EN                 BIT(13)
#define BIT_DCDC_CPU_EXT_XTL3_EN                 BIT(12)
#define BIT_DCDC_CPU_EXT_XTL4_EN                 BIT(11)
#define BIT_DCDC_CPU_EXT_XTL5_EN                 BIT(10)
#define BIT_DCDC_GPU_EXT_XTL0_EN                 BIT(5)
#define BIT_DCDC_GPU_EXT_XTL1_EN                 BIT(4)
#define BIT_DCDC_GPU_EXT_XTL2_EN                 BIT(3)
#define BIT_DCDC_GPU_EXT_XTL3_EN                 BIT(2)
#define BIT_DCDC_GPU_EXT_XTL4_EN                 BIT(1)
#define BIT_DCDC_GPU_EXT_XTL5_EN                 BIT(0)

/* ANA_REG_GLB_DCDC_XTL_EN2 */

#define BIT_DCDC_MEM_EXT_XTL0_EN                 BIT(15)
#define BIT_DCDC_MEM_EXT_XTL1_EN                 BIT(14)
#define BIT_DCDC_MEM_EXT_XTL2_EN                 BIT(13)
#define BIT_DCDC_MEM_EXT_XTL3_EN                 BIT(12)
#define BIT_DCDC_MEM_EXT_XTL4_EN                 BIT(11)
#define BIT_DCDC_MEM_EXT_XTL5_EN                 BIT(10)
#define BIT_DCDC_GEN1_EXT_XTL0_EN                BIT(5)
#define BIT_DCDC_GEN1_EXT_XTL1_EN                BIT(4)
#define BIT_DCDC_GEN1_EXT_XTL2_EN                BIT(3)
#define BIT_DCDC_GEN1_EXT_XTL3_EN                BIT(2)
#define BIT_DCDC_GEN1_EXT_XTL4_EN                BIT(1)
#define BIT_DCDC_GEN1_EXT_XTL5_EN                BIT(0)

/* ANA_REG_GLB_DCDC_XTL_EN3 */

#define BIT_DCDC_MEMQ_EXT_XTL0_EN                BIT(15)
#define BIT_DCDC_MEMQ_EXT_XTL1_EN                BIT(14)
#define BIT_DCDC_MEMQ_EXT_XTL2_EN                BIT(13)
#define BIT_DCDC_MEMQ_EXT_XTL3_EN                BIT(12)
#define BIT_DCDC_MEMQ_EXT_XTL4_EN                BIT(11)
#define BIT_DCDC_MEMQ_EXT_XTL5_EN                BIT(10)
#define BIT_DCDC_MODEM_EXT_XTL0_EN               BIT(5)
#define BIT_DCDC_MODEM_EXT_XTL1_EN               BIT(4)
#define BIT_DCDC_MODEM_EXT_XTL2_EN               BIT(3)
#define BIT_DCDC_MODEM_EXT_XTL3_EN               BIT(2)
#define BIT_DCDC_MODEM_EXT_XTL4_EN               BIT(1)
#define BIT_DCDC_MODEM_EXT_XTL5_EN               BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN0 */

#define BIT_LDO_VDD18_DCXO_EXT_XTL0_EN           BIT(15)
#define BIT_LDO_VDD18_DCXO_EXT_XTL1_EN           BIT(14)
#define BIT_LDO_VDD18_DCXO_EXT_XTL2_EN           BIT(13)
#define BIT_LDO_VDD18_DCXO_EXT_XTL3_EN           BIT(12)
#define BIT_LDO_VDD18_DCXO_EXT_XTL4_EN           BIT(11)
#define BIT_LDO_VDD18_DCXO_EXT_XTL5_EN           BIT(10)
#define BIT_LDO_VDD28_EXT_XTL0_EN                BIT(5)
#define BIT_LDO_VDD28_EXT_XTL1_EN                BIT(4)
#define BIT_LDO_VDD28_EXT_XTL2_EN                BIT(3)
#define BIT_LDO_VDD28_EXT_XTL3_EN                BIT(2)
#define BIT_LDO_VDD28_EXT_XTL4_EN                BIT(1)
#define BIT_LDO_VDD28_EXT_XTL5_EN                BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN1 */

#define BIT_LDO_VDDRF1V8_EXT_XTL0_EN             BIT(15)
#define BIT_LDO_VDDRF1V8_EXT_XTL1_EN             BIT(14)
#define BIT_LDO_VDDRF1V8_EXT_XTL2_EN             BIT(13)
#define BIT_LDO_VDDRF1V8_EXT_XTL3_EN             BIT(12)
#define BIT_LDO_VDDRF1V8_EXT_XTL4_EN             BIT(11)
#define BIT_LDO_VDDRF1V8_EXT_XTL5_EN             BIT(10)
#define BIT_LDO_VDDRF1V25_EXT_XTL0_EN            BIT(5)
#define BIT_LDO_VDDRF1V25_EXT_XTL1_EN            BIT(4)
#define BIT_LDO_VDDRF1V25_EXT_XTL2_EN            BIT(3)
#define BIT_LDO_VDDRF1V25_EXT_XTL3_EN            BIT(2)
#define BIT_LDO_VDDRF1V25_EXT_XTL4_EN            BIT(1)
#define BIT_LDO_VDDRF1V25_EXT_XTL5_EN            BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN2 */

#define BIT_LDO_VDDSIM0_EXT_XTL0_EN              BIT(15)
#define BIT_LDO_VDDSIM0_EXT_XTL1_EN              BIT(14)
#define BIT_LDO_VDDSIM0_EXT_XTL2_EN              BIT(13)
#define BIT_LDO_VDDSIM0_EXT_XTL3_EN              BIT(12)
#define BIT_LDO_VDDSIM0_EXT_XTL4_EN              BIT(11)
#define BIT_LDO_VDDSIM0_EXT_XTL5_EN              BIT(10)
#define BIT_LDO_VDDSIM1_EXT_XTL0_EN              BIT(5)
#define BIT_LDO_VDDSIM1_EXT_XTL1_EN              BIT(4)
#define BIT_LDO_VDDSIM1_EXT_XTL2_EN              BIT(3)
#define BIT_LDO_VDDSIM1_EXT_XTL3_EN              BIT(2)
#define BIT_LDO_VDDSIM1_EXT_XTL4_EN              BIT(1)
#define BIT_LDO_VDDSIM1_EXT_XTL5_EN              BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN3 */

#define BIT_LDO_VDDSIM2_EXT_XTL0_EN              BIT(15)
#define BIT_LDO_VDDSIM2_EXT_XTL1_EN              BIT(14)
#define BIT_LDO_VDDSIM2_EXT_XTL2_EN              BIT(13)
#define BIT_LDO_VDDSIM2_EXT_XTL3_EN              BIT(12)
#define BIT_LDO_VDDSIM2_EXT_XTL4_EN              BIT(11)
#define BIT_LDO_VDDSIM2_EXT_XTL5_EN              BIT(10)
#define BIT_LDO_AVDD12_EXT_XTL0_EN               BIT(5)
#define BIT_LDO_AVDD12_EXT_XTL1_EN               BIT(4)
#define BIT_LDO_AVDD12_EXT_XTL2_EN               BIT(3)
#define BIT_LDO_AVDD12_EXT_XTL3_EN               BIT(2)
#define BIT_LDO_AVDD12_EXT_XTL4_EN               BIT(1)
#define BIT_LDO_AVDD12_EXT_XTL5_EN               BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN4 */

#define BIT_LDO_VDDCAMMOT_EXT_XTL0_EN            BIT(15)
#define BIT_LDO_VDDCAMMOT_EXT_XTL1_EN            BIT(14)
#define BIT_LDO_VDDCAMMOT_EXT_XTL2_EN            BIT(13)
#define BIT_LDO_VDDCAMMOT_EXT_XTL3_EN            BIT(12)
#define BIT_LDO_VDDCAMMOT_EXT_XTL4_EN            BIT(11)
#define BIT_LDO_VDDCAMMOT_EXT_XTL5_EN            BIT(10)
#define BIT_LDO_VDDCAMIO_EXT_XTL0_EN             BIT(5)
#define BIT_LDO_VDDCAMIO_EXT_XTL1_EN             BIT(4)
#define BIT_LDO_VDDCAMIO_EXT_XTL2_EN             BIT(3)
#define BIT_LDO_VDDCAMIO_EXT_XTL3_EN             BIT(2)
#define BIT_LDO_VDDCAMIO_EXT_XTL4_EN             BIT(1)
#define BIT_LDO_VDDCAMIO_EXT_XTL5_EN             BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN5 */

#define BIT_LDO_VDDCAMA0_EXT_XTL0_EN             BIT(15)
#define BIT_LDO_VDDCAMA0_EXT_XTL1_EN             BIT(14)
#define BIT_LDO_VDDCAMA0_EXT_XTL2_EN             BIT(13)
#define BIT_LDO_VDDCAMA0_EXT_XTL3_EN             BIT(12)
#define BIT_LDO_VDDCAMA0_EXT_XTL4_EN             BIT(11)
#define BIT_LDO_VDDCAMA0_EXT_XTL5_EN             BIT(10)
#define BIT_LDO_VDDCAMA1_EXT_XTL0_EN             BIT(5)
#define BIT_LDO_VDDCAMA1_EXT_XTL1_EN             BIT(4)
#define BIT_LDO_VDDCAMA1_EXT_XTL2_EN             BIT(3)
#define BIT_LDO_VDDCAMA1_EXT_XTL3_EN             BIT(2)
#define BIT_LDO_VDDCAMA1_EXT_XTL4_EN             BIT(1)
#define BIT_LDO_VDDCAMA1_EXT_XTL5_EN             BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN6 */

#define BIT_LDO_VDDCAMD0_EXT_XTL0_EN             BIT(15)
#define BIT_LDO_VDDCAMD0_EXT_XTL1_EN             BIT(14)
#define BIT_LDO_VDDCAMD0_EXT_XTL2_EN             BIT(13)
#define BIT_LDO_VDDCAMD0_EXT_XTL3_EN             BIT(12)
#define BIT_LDO_VDDCAMD0_EXT_XTL4_EN             BIT(11)
#define BIT_LDO_VDDCAMD0_EXT_XTL5_EN             BIT(10)
#define BIT_LDO_VDDCAMD1_EXT_XTL0_EN             BIT(5)
#define BIT_LDO_VDDCAMD1_EXT_XTL1_EN             BIT(4)
#define BIT_LDO_VDDCAMD1_EXT_XTL2_EN             BIT(3)
#define BIT_LDO_VDDCAMD1_EXT_XTL3_EN             BIT(2)
#define BIT_LDO_VDDCAMD1_EXT_XTL4_EN             BIT(1)
#define BIT_LDO_VDDCAMD1_EXT_XTL5_EN             BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN7 */

#define BIT_LDO_VDDSDIO_EXT_XTL0_EN              BIT(15)
#define BIT_LDO_VDDSDIO_EXT_XTL1_EN              BIT(14)
#define BIT_LDO_VDDSDIO_EXT_XTL2_EN              BIT(13)
#define BIT_LDO_VDDSDIO_EXT_XTL3_EN              BIT(12)
#define BIT_LDO_VDDSDIO_EXT_XTL4_EN              BIT(11)
#define BIT_LDO_VDDSDIO_EXT_XTL5_EN              BIT(10)
#define BIT_LDO_VDDSDCORE_EXT_XTL0_EN            BIT(5)
#define BIT_LDO_VDDSDCORE_EXT_XTL1_EN            BIT(4)
#define BIT_LDO_VDDSDCORE_EXT_XTL2_EN            BIT(3)
#define BIT_LDO_VDDSDCORE_EXT_XTL3_EN            BIT(2)
#define BIT_LDO_VDDSDCORE_EXT_XTL4_EN            BIT(1)
#define BIT_LDO_VDDSDCORE_EXT_XTL5_EN            BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN8 */

#define BIT_LDO_VDDEMMCCORE_EXT_XTL0_EN          BIT(15)
#define BIT_LDO_VDDEMMCCORE_EXT_XTL1_EN          BIT(14)
#define BIT_LDO_VDDEMMCCORE_EXT_XTL2_EN          BIT(13)
#define BIT_LDO_VDDEMMCCORE_EXT_XTL3_EN          BIT(12)
#define BIT_LDO_VDDEMMCCORE_EXT_XTL4_EN          BIT(11)
#define BIT_LDO_VDDEMMCCORE_EXT_XTL5_EN          BIT(10)
#define BIT_LDO_VDDUSB33_EXT_XTL0_EN             BIT(5)
#define BIT_LDO_VDDUSB33_EXT_XTL1_EN             BIT(4)
#define BIT_LDO_VDDUSB33_EXT_XTL2_EN             BIT(3)
#define BIT_LDO_VDDUSB33_EXT_XTL3_EN             BIT(2)
#define BIT_LDO_VDDUSB33_EXT_XTL4_EN             BIT(1)
#define BIT_LDO_VDDUSB33_EXT_XTL5_EN             BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN9 */

#define BIT_LDO_VDDKPLED_EXT_XTL0_EN             BIT(15)
#define BIT_LDO_VDDKPLED_EXT_XTL1_EN             BIT(14)
#define BIT_LDO_VDDKPLED_EXT_XTL2_EN             BIT(13)
#define BIT_LDO_VDDKPLED_EXT_XTL3_EN             BIT(12)
#define BIT_LDO_VDDKPLED_EXT_XTL4_EN             BIT(11)
#define BIT_LDO_VDDKPLED_EXT_XTL5_EN             BIT(10)
#define BIT_LDO_VDDVIB_EXT_XTL0_EN               BIT(5)
#define BIT_LDO_VDDVIB_EXT_XTL1_EN               BIT(4)
#define BIT_LDO_VDDVIB_EXT_XTL2_EN               BIT(3)
#define BIT_LDO_VDDVIB_EXT_XTL3_EN               BIT(2)
#define BIT_LDO_VDDVIB_EXT_XTL4_EN               BIT(1)
#define BIT_LDO_VDDVIB_EXT_XTL5_EN               BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN10 */

#define BIT_LDO_VDDWCN_EXT_XTL0_EN               BIT(15)
#define BIT_LDO_VDDWCN_EXT_XTL1_EN               BIT(14)
#define BIT_LDO_VDDWCN_EXT_XTL2_EN               BIT(13)
#define BIT_LDO_VDDWCN_EXT_XTL3_EN               BIT(12)
#define BIT_LDO_VDDWCN_EXT_XTL4_EN               BIT(11)
#define BIT_LDO_VDDWCN_EXT_XTL5_EN               BIT(10)
#define BIT_LDO_AVDD18_EXT_XTL0_EN               BIT(5)
#define BIT_LDO_AVDD18_EXT_XTL1_EN               BIT(4)
#define BIT_LDO_AVDD18_EXT_XTL2_EN               BIT(3)
#define BIT_LDO_AVDD18_EXT_XTL3_EN               BIT(2)
#define BIT_LDO_AVDD18_EXT_XTL4_EN               BIT(1)
#define BIT_LDO_AVDD18_EXT_XTL5_EN               BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN11 */

#define BIT_LDO_VDDLDO0_EXT_XTL0_EN              BIT(15)
#define BIT_LDO_VDDLDO0_EXT_XTL1_EN              BIT(14)
#define BIT_LDO_VDDLDO0_EXT_XTL2_EN              BIT(13)
#define BIT_LDO_VDDLDO0_EXT_XTL3_EN              BIT(12)
#define BIT_LDO_VDDLDO0_EXT_XTL4_EN              BIT(11)
#define BIT_LDO_VDDLDO0_EXT_XTL5_EN              BIT(10)
#define BIT_LDO_VDDWIFIPA_EXT_XTL0_EN            BIT(5)
#define BIT_LDO_VDDWIFIPA_EXT_XTL1_EN            BIT(4)
#define BIT_LDO_VDDWIFIPA_EXT_XTL2_EN            BIT(3)
#define BIT_LDO_VDDWIFIPA_EXT_XTL3_EN            BIT(2)
#define BIT_LDO_VDDWIFIPA_EXT_XTL4_EN            BIT(1)
#define BIT_LDO_VDDWIFIPA_EXT_XTL5_EN            BIT(0)

/* ANA_REG_GLB_LDO_XTL_EN12 */

#define BIT_LDO_VDDLDO2_EXT_XTL0_EN              BIT(15)
#define BIT_LDO_VDDLDO2_EXT_XTL1_EN              BIT(14)
#define BIT_LDO_VDDLDO2_EXT_XTL2_EN              BIT(13)
#define BIT_LDO_VDDLDO2_EXT_XTL3_EN              BIT(12)
#define BIT_LDO_VDDLDO2_EXT_XTL4_EN              BIT(11)
#define BIT_LDO_VDDLDO2_EXT_XTL5_EN              BIT(10)
#define BIT_LDO_VDDLDO1_EXT_XTL0_EN              BIT(5)
#define BIT_LDO_VDDLDO1_EXT_XTL1_EN              BIT(4)
#define BIT_LDO_VDDLDO1_EXT_XTL2_EN              BIT(3)
#define BIT_LDO_VDDLDO1_EXT_XTL3_EN              BIT(2)
#define BIT_LDO_VDDLDO1_EXT_XTL4_EN              BIT(1)
#define BIT_LDO_VDDLDO1_EXT_XTL5_EN              BIT(0)

/* ANA_REG_GLB_DCXO_XTL_EN */

#define BIT_TSX_XO_EXT_XTL0_EN                   BIT(15)
#define BIT_TSX_XO_EXT_XTL1_EN                   BIT(14)
#define BIT_TSX_XO_EXT_XTL2_EN                   BIT(13)
#define BIT_TSX_XO_EXT_XTL3_EN                   BIT(12)
#define BIT_TSX_XO_EXT_XTL4_EN                   BIT(11)
#define BIT_TSX_XO_EXT_XTL5_EN                   BIT(10)
#define BIT_XO_EXT_XTL0_EN                       BIT(5)
#define BIT_XO_EXT_XTL1_EN                       BIT(4)
#define BIT_XO_EXT_XTL2_EN                       BIT(3)
#define BIT_XO_EXT_XTL3_EN                       BIT(2)
#define BIT_XO_EXT_XTL4_EN                       BIT(1)
#define BIT_XO_EXT_XTL5_EN                       BIT(0)

/* ANA_REG_GLB_RESERVED_REG18 */


/* ANA_REG_GLB_RESERVED_REG19 */


/* ANA_REG_GLB_RESERVED_REG20 */


/* ANA_REG_GLB_TSX_CTRL_REG0 */

#define BIT_DCXO_26M_REF_OUT0_PIN_EXT_XTL5_EN    BIT(15)
#define BIT_DCXO_26M_REF_OUT0_PIN_EXT_XTL4_EN    BIT(14)
#define BIT_DCXO_26M_REF_OUT0_PIN_EXT_XTL3_EN    BIT(13)
#define BIT_DCXO_26M_REF_OUT0_PIN_EXT_XTL2_EN    BIT(12)
#define BIT_DCXO_26M_REF_OUT0_PIN_EXT_XTL1_EN    BIT(11)
#define BIT_DCXO_26M_REF_OUT0_PIN_EXT_XTL0_EN    BIT(10)
#define BIT_DCXO_26M_REF_OUT1_PIN_EXT_XTL5_EN    BIT(9)
#define BIT_DCXO_26M_REF_OUT1_PIN_EXT_XTL4_EN    BIT(8)
#define BIT_DCXO_26M_REF_OUT1_PIN_EXT_XTL3_EN    BIT(7)
#define BIT_DCXO_26M_REF_OUT1_PIN_EXT_XTL2_EN    BIT(6)
#define BIT_DCXO_26M_REF_OUT1_PIN_EXT_XTL1_EN    BIT(5)
#define BIT_DCXO_26M_REF_OUT1_PIN_EXT_XTL0_EN    BIT(4)

/* ANA_REG_GLB_TSX_CTRL_REG1 */

#define BIT_DCXO_26M_REF_OUT2_PIN_EXT_XTL5_EN    BIT(15)
#define BIT_DCXO_26M_REF_OUT2_PIN_EXT_XTL4_EN    BIT(14)
#define BIT_DCXO_26M_REF_OUT2_PIN_EXT_XTL3_EN    BIT(13)
#define BIT_DCXO_26M_REF_OUT2_PIN_EXT_XTL2_EN    BIT(12)
#define BIT_DCXO_26M_REF_OUT2_PIN_EXT_XTL1_EN    BIT(11)
#define BIT_DCXO_26M_REF_OUT2_PIN_EXT_XTL0_EN    BIT(10)
#define BIT_DCXO_26M_REF_OUT3_PIN_EXT_XTL5_EN    BIT(9)
#define BIT_DCXO_26M_REF_OUT3_PIN_EXT_XTL4_EN    BIT(8)
#define BIT_DCXO_26M_REF_OUT3_PIN_EXT_XTL3_EN    BIT(7)
#define BIT_DCXO_26M_REF_OUT3_PIN_EXT_XTL2_EN    BIT(6)
#define BIT_DCXO_26M_REF_OUT3_PIN_EXT_XTL1_EN    BIT(5)
#define BIT_DCXO_26M_REF_OUT3_PIN_EXT_XTL0_EN    BIT(4)

/* ANA_REG_GLB_TSX_CTRL0 */

#define BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL5_EN    BIT(15)
#define BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL4_EN    BIT(14)
#define BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL3_EN    BIT(13)
#define BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL2_EN    BIT(12)
#define BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL1_EN    BIT(11)
#define BIT_DCXO_26M_REF_OUT4_PIN_EXT_XTL0_EN    BIT(10)
#define BIT_SLP_DCXO_26M_REF_OUT4_EN             BIT(9)
#define BIT_SLP_DCXO_26M_REF_OUT3_EN             BIT(8)
#define BIT_SLP_DCXO_26M_REF_OUT2_EN             BIT(7)
#define BIT_SLP_DCXO_26M_REF_OUT1_EN             BIT(6)
#define BIT_SLP_DCXO_26M_REF_OUT0_EN             BIT(5)
#define BITS_DCXO_26M_REF_OUT_EN(x)               (((x) & 0x1F))

/* ANA_REG_GLB_TSX_CTRL1 */

#define BIT_DCXO_26M_REF_OUT4_EXT_XTL1_EN        BIT(10)
#define BIT_DCXO_26M_REF_OUT3_EXT_XTL1_EN        BIT(9)
#define BIT_DCXO_26M_REF_OUT2_EXT_XTL1_EN        BIT(8)
#define BIT_DCXO_26M_REF_OUT1_EXT_XTL1_EN        BIT(7)
#define BIT_DCXO_26M_REF_OUT0_EXT_XTL1_EN        BIT(6)
#define BIT_DCXO_26M_REF_OUT4_EXT_XTL0_EN        BIT(4)
#define BIT_DCXO_26M_REF_OUT3_EXT_XTL0_EN        BIT(3)
#define BIT_DCXO_26M_REF_OUT2_EXT_XTL0_EN        BIT(2)
#define BIT_DCXO_26M_REF_OUT1_EXT_XTL0_EN        BIT(1)
#define BIT_DCXO_26M_REF_OUT0_EXT_XTL0_EN        BIT(0)

/* ANA_REG_GLB_TSX_CTRL2 */

#define BIT_DCXO_26M_REF_OUT4_EXT_XTL3_EN        BIT(10)
#define BIT_DCXO_26M_REF_OUT3_EXT_XTL3_EN        BIT(9)
#define BIT_DCXO_26M_REF_OUT2_EXT_XTL3_EN        BIT(8)
#define BIT_DCXO_26M_REF_OUT1_EXT_XTL3_EN        BIT(7)
#define BIT_DCXO_26M_REF_OUT0_EXT_XTL3_EN        BIT(6)
#define BIT_DCXO_26M_REF_OUT4_EXT_XTL2_EN        BIT(4)
#define BIT_DCXO_26M_REF_OUT3_EXT_XTL2_EN        BIT(3)
#define BIT_DCXO_26M_REF_OUT2_EXT_XTL2_EN        BIT(2)
#define BIT_DCXO_26M_REF_OUT1_EXT_XTL2_EN        BIT(1)
#define BIT_DCXO_26M_REF_OUT0_EXT_XTL2_EN        BIT(0)

/* ANA_REG_GLB_TSX_CTRL3 */

#define BIT_SLP_DCXO_LP_EN                       BIT(15)
#define BIT_DCXO_26M_REF_OUT4_EXT_XTL5_EN        BIT(14)
#define BIT_DCXO_26M_REF_OUT3_EXT_XTL5_EN        BIT(13)
#define BIT_DCXO_26M_REF_OUT2_EXT_XTL5_EN        BIT(12)
#define BIT_DCXO_26M_REF_OUT1_EXT_XTL5_EN        BIT(11)
#define BIT_DCXO_26M_REF_OUT0_EXT_XTL5_EN        BIT(10)
#define BIT_DCXO_26M_REF_OUT4_EXT_XTL4_EN        BIT(8)
#define BIT_DCXO_26M_REF_OUT3_EXT_XTL4_EN        BIT(7)
#define BIT_DCXO_26M_REF_OUT2_EXT_XTL4_EN        BIT(6)
#define BIT_DCXO_26M_REF_OUT1_EXT_XTL4_EN        BIT(5)
#define BIT_DCXO_26M_REF_OUT0_EXT_XTL4_EN        BIT(4)
#define BIT_DCXO_CORE_AML_CAL_EN                 BIT(3)
#define BITS_CLK_DCXO_SEL(x)                      (((x) & 0x7))

/* ANA_REG_GLB_TSX_CTRL4 */

#define BITS_DCXO_26M_REF_BUF2_DRV_LEVEL_CTRL(x)  (((x) & 0x7) << 13)
#define BITS_DCXO_26M_REF_BUF3_DRV_LEVEL_CTRL(x)  (((x) & 0x7) << 10)
#define BIT_DCXO_32K_DIV_MODE_SEL                BIT(9)
#define BIT_DCXO_32K_CLKIN_26M_INV_CTRL          BIT(8)
#define BITS_DCXO_CORE_AML_CTRL(x)                (((x) & 0xF) << 4)
#define BIT_DCXO_CORE_AML_CAL_OK_FLAG            BIT(3)
#define BITS_DCXO_26M_REF_BUF4_DRV_LEVEL_CTRL(x)  (((x) & 0x7))

/* ANA_REG_GLB_TSX_CTRL5 */

#define BITS_DCXO_CORE_AML_CAL_CTRL_HP(x)         (((x) & 0xFF))

/* ANA_REG_GLB_TSX_CTRL6 */

#define BITS_DCXO_CORE_AML_CAL_CTRL_LP(x)         (((x) & 0xFF))

/* ANA_REG_GLB_TSX_CTRL7 */


/* ANA_REG_GLB_TSX_CTRL8 */

#define BIT_DCXO_CORE_GM_HELPER_HP               BIT(0)

/* ANA_REG_GLB_TSX_CTRL9 */

#define BIT_DCXO_CORE_GM_HELPER_LP               BIT(0)

/* ANA_REG_GLB_TSX_CTRL10 */

#define BITS_DCXO_CORE_CBANK_HP(x)                (((x) & 0xFF))

/* ANA_REG_GLB_TSX_CTRL11 */

#define BITS_DCXO_CORE_CBANK_LP(x)                (((x) & 0xFF))

/* ANA_REG_GLB_TSX_CTRL12 */

#define BITS_DCXO_32K_FRAC_DIV_RATIO_CTRL_HP(x)   (((x) & 0xFFF))

/* ANA_REG_GLB_TSX_CTRL13 */

#define BITS_DCXO_32K_FRAC_DIV_RATIO_CTRL_LP(x)   (((x) & 0xFFF))

/* ANA_REG_GLB_TSX_CTRL14 */

#define BIT_DCXO_CORE_BUF_MODE_SEL               BIT(15)
#define BIT_DCXO_26M_REF_BUF2_DIV_MODE_SEL       BIT(14)
#define BIT_DCXO_26M_REF_BUF3_DIV_MODE_SEL       BIT(13)
#define BIT_DCXO_26M_REF_BUF4_DIV_MODE_SEL       BIT(12)
#define BIT_DCXO_LP_CAL_EN                       BIT(11)
#define BITS_DCXO_26M_REF_BUF_OUTPUT_BYPASS(x)    (((x) & 0x1F) << 6)
#define BITS_DCXO_26M_REF_BUF0_DRV_LEVEL_CTRL(x)  (((x) & 0x7) << 3)
#define BITS_DCXO_26M_REF_BUF1_DRV_LEVEL_CTRL(x)  (((x) & 0x7))

/* ANA_REG_GLB_RESERVED_REG21 */


/* ANA_REG_GLB_RESERVED_REG22 */


/* ANA_REG_GLB_RESERVED_REG23 */


/* ANA_REG_GLB_TSEN_CTRL0 */

#define BIT_TSEN_ADCLDO_EN                       BIT(15)
#define BITS_TSEN_CLKSEL(x)                       (((x) & 0x3) << 11)
#define BITS_TSEN_CHOP_CLKSEL(x)                  (((x) & 0x3) << 9)
#define BITS_TSEN_ADCLDO_V(x)                     (((x) & 0xF) << 5)
#define BIT_TSEN_CLK_SRC_SEL                     BIT(4)
#define BIT_TSEN_CLK_DUTY_CRC_EN                 BIT(3)
#define BITS_TSEN_CLK_PHASE_SEL(x)                (((x) & 0x7))

/* ANA_REG_GLB_TSEN_CTRL1 */

#define BIT_TSEN_DATA_EDGE_SEL                   BIT(15)
#define BIT_TSEN_UGBUF_EN                        BIT(14)
#define BIT_TSEN_INPUT_EN                        BIT(13)
#define BIT_TSEN_SDADC_EN                        BIT(11)
#define BIT_TSEN_UGBUF_CHOP_EN                   BIT(10)
#define BIT_TSEN_SDADC_CHOP_EN                   BIT(9)
#define BIT_CLK_26M_TESN_EN                      BIT(7)
#define BIT_UGBUF_CTRL                           BIT(6)

/* ANA_REG_GLB_TSEN_CTRL2 */

#define BIT_TSEN_CLK_SOFT_RST                    BIT(8)
#define BIT_TSEN_CH_THM_SEL                      BIT(7)
#define BIT_TSEN_CLK_PHASE_MODE_SEL              BIT(6)
#define BITS_TSEN_SDADC_CTRL1(x)                  (((x) & 0xF) << 2)
#define BIT_TSEN_INPUT_RC_EN                     BIT(1)
#define BIT_CLK_TSEN_SEL                         BIT(0)

/* ANA_REG_GLB_TSEN_CTRL3 */

#define BIT_TSEN_SEL_CH                          BIT(4)
#define BIT_TSEN_SEL_EN                          BIT(3)
#define BITS_TSEN_TIME_SEL(x)                     (((x) & 0x3) << 1)
#define BIT_TSEN_EN                              BIT(0)

/* ANA_REG_GLB_TSEN_CTRL4 */

#define BITS_TSEN_OUT(x)                          (((x) & 0xFFFF))

/* ANA_REG_GLB_TSEN_CTRL5 */

#define BITS_OSC_OUT(x)                           (((x) & 0xFFFF))

/* ANA_REG_GLB_RESERVED_REG_CORE */

#define BITS_RESERVED_CORE(x)                     (((x) & 0xFFFF))

/* ANA_REG_GLB_RESERVED_REG_RTC */

#define BITS_RESERVED_RTC(x)                      (((x) & 0xFFFF))

/* ANA_REG_GLB_BG_CTRL */

#define BIT_BG_CHOP_EN                           BIT(0)

/* ANA_REG_GLB_DCDC_VLG_SEL0 */

#define BIT_DCDC_MODEM_PFMAD_SW_SEL              BIT(15)
#define BIT_DCDC_MEMQ_PFMAD_SW_SEL               BIT(14)
#define BIT_DCDC_GPU_PFMAD_SW_SEL                BIT(13)
#define BIT_DCDC_CPU_PFMAD_SW_SEL                BIT(12)
#define BIT_DCDC_CORE_PFMAD_SW_SEL               BIT(11)
#define BIT_DCDC_GEN1_PFMAD_SW_SEL               BIT(10)
#define BIT_DCDC_GEN0_PFMAD_SW_SEL               BIT(9)
#define BIT_DCDC_MEM_PFMAD_SW_SEL                BIT(8)
#define BIT_DCDC_WPA_PFMAD_SW_SEL                BIT(7)
#define BIT_DCDC_6MFRECAL_SW_SEL                 BIT(6)
#define BIT_DCDC_WPA_VREF_CAL_SW_SEL             BIT(5)
#define BIT_DCDC_MEMQ_SW_SEL                     BIT(4)
#define BIT_DCDC_GEN0_SW_SEL                     BIT(3)
#define BIT_DCDC_GEN1_SW_SEL                     BIT(2)
#define BIT_DCDC_CORE_SLP_SW_SEL                 BIT(1)
#define BIT_DCDC_CORE_NOR_SW_SEL                 BIT(0)

/* ANA_REG_GLB_DCDC_VLG_SEL1 */

#define BIT_DCDC_SRAM_PFMAD_SW_SEL               BIT(5)
#define BIT_DCDC_SRAM_SW_SEL                     BIT(4)
#define BIT_DCDC_MODEM_SW_SEL                    BIT(3)
#define BIT_DCDC_MEM_SW_SEL                      BIT(2)
#define BIT_DCDC_GPU_SW_SEL                      BIT(1)
#define BIT_DCDC_CPU_SW_SEL                      BIT(0)

/* ANA_REG_GLB_LDO_VLG_SEL0 */

#define BIT_LDO_VDDSDCORE_CL_SW_SEL              BIT(15)
#define BIT_LDO_VDDLDO1_SW_SEL                   BIT(14)
#define BIT_LDO_VDDLDO0_SW_SEL                   BIT(13)
#define BIT_LDO_VDDUSB33_SW_SEL                  BIT(12)
#define BIT_LDO_VDD18_DCXO_SW_SEL                BIT(11)
#define BIT_LDO_VDDWIFIPA_SW_SEL                 BIT(10)
#define BIT_LDO_VDD28_SW_SEL                     BIT(9)
#define BIT_LDO_VDDSDIO_SW_SEL                   BIT(8)
#define BIT_LDO_VDDSDCORE_SW_SEL                 BIT(7)
#define BIT_LDO_VDDEMMCCORE_SW_SEL               BIT(6)
#define BIT_LDO_VDDSIM2_SW_SEL                   BIT(5)
#define BIT_LDO_VDDSIM1_SW_SEL                   BIT(4)
#define BIT_LDO_VDDSIM0_SW_SEL                   BIT(3)
#define BIT_LDO_VDDCAMMOT_SW_SEL                 BIT(2)
#define BIT_LDO_VDDCAMA1_SW_SEL                  BIT(1)
#define BIT_LDO_VDDCAMA0_SW_SEL                  BIT(0)

/* ANA_REG_GLB_LDO_VLG_SEL1 */

#define BIT_LDO_VDDLDO2_SW_SEL                   BIT(10)
#define BIT_LDO_RTC_CAL_SW_SEL                   BIT(9)
#define BIT_LDO_VDDKPLED_SW_SEL                  BIT(8)
#define BIT_LDO_VDDVIBR_SW_SEL                   BIT(7)
#define BIT_LDO_AVDD12_SW_SEL                    BIT(6)
#define BIT_LDO_VDDRF1V25_SW_SEL                 BIT(5)
#define BIT_LDO_VDDCAMD1_SW_SEL                  BIT(4)
#define BIT_LDO_VDDCAMD0_SW_SEL                  BIT(3)
#define BIT_LDO_VDDWCN_SW_SEL                    BIT(2)
#define BIT_LDO_VDDRF1V8_SW_SEL                  BIT(1)
#define BIT_LDO_AVDD18_SW_SEL                    BIT(0)

/* ANA_REG_GLB_CLK32KLESS_CTRL0 */

#define BIT_TSX_MODE                             BIT(15)
#define BIT_RC_MODE_WR_ACK_FLAG                  BIT(14)
#define BIT_XO_LOW_CUR_FLAG                      BIT(13)
#define BIT_XO_LOW_CUR_FRC_RTCSET                BIT(12)
#define BIT_XO_LOW_CUR_FRC_RTCCLR                BIT(11)
#define BIT_RC_MODE_WR_ACK_FLAG_CLR              BIT(10)
#define BIT_XO_LOW_CUR_FLAG_CLR                  BIT(9)
#define BIT_XO_LOW_CUR_CNT_CLR                   BIT(8)
#define BIT_LDO_VDD18_DCXO_LP_EN_RTCSET          BIT(7)
#define BIT_LDO_VDD18_DCXO_LP_EN_RTCCLR          BIT(6)
#define BIT_SLP_XO_LOW_CUR_EN                    BIT(5)
#define BIT_RTC_MODE                             BIT(4)
#define BIT_OPT_TCXO                             BIT(3)
#define BIT_OPT_26_52                            BIT(2)
#define BIT_RC_32K_SEL                           BIT(1)
#define BIT_RC_32K_EN                            BIT(0)

/* ANA_REG_GLB_CLK32KLESS_CTRL1 */

#define BITS_RC_MODE(x)                           (((x) & 0xFFFF))

/* ANA_REG_GLB_CLK32KLESS_CTRL2 */

#define BITS_XO_LOW_CUR_CNT_LOW(x)                (((x) & 0xFFFF))

/* ANA_REG_GLB_CLK32KLESS_CTRL3 */

#define BITS_XO_LOW_CUR_CNT_HIGH(x)               (((x) & 0xFFFF))

/* ANA_REG_GLB_XTL_WAIT_CTRL0 */

#define BIT_EXT_XTL5_FOR_26M_EN                  BIT(15)
#define BIT_EXT_XTL4_FOR_26M_EN                  BIT(14)
#define BIT_EXT_XTL3_FOR_26M_EN                  BIT(13)
#define BIT_EXT_XTL2_FOR_26M_EN                  BIT(12)
#define BIT_EXT_XTL1_FOR_26M_EN                  BIT(11)
#define BIT_EXT_XTL0_FOR_26M_EN                  BIT(10)
#define BIT_SLP_XTLBUF_PD_EN                     BIT(9)
#define BIT_XTL_EN                               BIT(8)
#define BITS_XTL_WAIT(x)                          (((x) & 0xFF))

/* ANA_REG_GLB_CLK_26M_SEL */

#define BIT_OPT_L5                               BIT(2)
#define BIT_OPT_WK                               BIT(1)
#define BIT_CLK_26M_SOURCE_SEL                   BIT(0)

/* ANA_REG_GLB_RGB_CTRL0 */

#define BIT_SLP_RGB_PD_EN                        BIT(2)

/* ANA_REG_GLB_IB_CTRL */

#define BIT_BATDET_CUR_EN                        BIT(13)
#define BITS_BATDET_CUR_I(x)                      (((x) & 0x7) << 9)
#define BITS_IB_TRIM(x)                           (((x) & 0x7F) << 2)
#define BIT_IB_TRIM_EM_SEL                       BIT(1)
#define BIT_IB_REX_EN                            BIT(0)

/* ANA_REG_GLB_KPLED_CTRL0 */

#define BITS_KPLED_V(x)                           (((x) & 0xF) << 12)
#define BIT_KPLED_PD                             BIT(11)
#define BIT_KPLED_PULLDOWN_EN                    BIT(10)

/* ANA_REG_GLB_KPLED_CTRL1 */

#define BIT_LDO_VDDKPLED_PD                      BIT(15)
#define BITS_LDO_VDDKPLED_V(x)                    (((x) & 0xFF) << 7)
#define BITS_LDO_VDDKPLED_REFTRIM(x)              (((x) & 0x1F) << 2)
#define BIT_SLP_LDO_VDDKPLED_PD_EN               BIT(1)
#define BIT_LDO_VDDKPLED_SHPT_PD                 BIT(0)

/* ANA_REG_GLB_VIBR_CTRL0 */

#define BIT_LDO_VDDVIB_SHPT_PD                   BIT(15)
#define BIT_SLP_LDO_VDDVIB_PD_EN                 BIT(14)
#define BIT_LDO_VDDVIB_PD                        BIT(13)
#define BITS_LDO_VDDVIB_REFTRIM(x)                (((x) & 0x1F) << 8)
#define BITS_LDO_VDDVIB_V(x)                      (((x) & 0xFF))

/* ANA_REG_GLB_AUDIO_CTRL0 */

#define BIT_CLK_AUD_IF_TX_INV_EN                 BIT(3)
#define BIT_CLK_AUD_IF_RX_INV_EN                 BIT(2)
#define BIT_CLK_AUD_IF_6P5M_TX_INV_EN            BIT(1)
#define BIT_CLK_AUD_IF_6P5M_RX_INV_EN            BIT(0)

/* ANA_REG_GLB_CHGR_CTRL */

#define BIT_CHGR_PD                              BIT(0)

/* ANA_REG_GLB_CHGR_STATUS */

#define BIT_CHGR_INT_EN                          BIT(13)
#define BIT_NON_DCP_INT                          BIT(12)
#define BIT_CHG_DET_DONE                         BIT(11)
#define BIT_DP_LOW                               BIT(10)
#define BIT_DCP_DET                              BIT(9)
#define BIT_CHG_DET                              BIT(8)
#define BIT_SDP_INT                              BIT(7)
#define BIT_DCP_INT                              BIT(6)
#define BIT_CDP_INT                              BIT(5)
#define BIT_CHGR_INT                             BIT(2)
#define BIT_DCP_SWITCH_EN                        BIT(1)

/* ANA_REG_GLB_CHGR_DET_FGU_CTRL */

#define BIT_DP_DM_FC_ENB                         BIT(14)
#define BIT_FGUA_SOFT_RST                        BIT(13)
#define BIT_LDO_FGU_PD                           BIT(12)
#define BITS_CHG_INT_DELAY(x)                     (((x) & 0x7) << 9)
#define BIT_DP_DM_AUX_EN                         BIT(1)
#define BIT_DP_DM_BC_ENB                         BIT(0)

/* ANA_REG_GLB_OVLO_CTRL */

#define BITS_VBAT_CRASH_V(x)                      (((x) & 0x3) << 10)
#define BIT_OVLO_EN                              BIT(9)
#define BITS_OVLO_V(x)                            (((x) & 0x3) << 2)
#define BITS_OVLO_T(x)                            (((x) & 0x3))

/* ANA_REG_GLB_MIXED_CTRL */

#define BIT_XOSC32K_CTL                          BIT(12)
#define BITS_BATON_T(x)                           (((x) & 0x3) << 10)
#define BIT_BATDET_OK                            BIT(8)
#define BIT_VBAT_OK                              BIT(4)
#define BIT_ALL_GPI_DEB                          BIT(3)
#define BIT_GPI_DEBUG_EN                         BIT(2)
#define BIT_ALL_INT_DEB                          BIT(1)
#define BIT_INT_DEBUG_EN                         BIT(0)

/* ANA_REG_GLB_POR_RST_MONITOR */

#define BITS_POR_RST_MONITOR(x)                   (((x) & 0xFFFF))

/* ANA_REG_GLB_WDG_RST_MONITOR */

#define BITS_WDG_RST_MONITOR(x)                   (((x) & 0xFFFF))

/* ANA_REG_GLB_POR_PIN_RST_MONITOR */

#define BITS_POR_PIN_RST_MONITOR(x)               (((x) & 0xFFFF))

/* ANA_REG_GLB_POR_SRC_FLAG */

#define BIT_POR_SW_FORCE_ON                      BIT(15)
#define BIT_REG_SOFT_RST_FLG_CLR                 BIT(14)
#define BITS_POR_SRC_FLAG(x)                      (((x) & 0x3FFF))

/* ANA_REG_GLB_POR_OFF_FLAG */

#define BIT_POR_CHIP_PD_FLAG                     BIT(13)
#define BIT_POR_CHIP_PD_FLAG_CLR                 BIT(12)
#define BIT_UVLO_CHIP_PD_FLAG                    BIT(11)
#define BIT_UVLO_CHIP_PD_FLAG_CLR                BIT(10)
#define BIT_HARD_7S_CHIP_PD_FLAG                 BIT(9)
#define BIT_HARD_7S_CHIP_PD_FLAG_CLR             BIT(8)
#define BIT_SW_CHIP_PD_FLAG                      BIT(7)
#define BIT_SW_CHIP_PD_FLAG_CLR                  BIT(6)
#define BIT_HW_CHIP_PD_FLAG                      BIT(5)
#define BIT_HW_CHIP_PD_FLAG_CLR                  BIT(4)
#define BIT_OTP_CHIP_PD_FLAG                     BIT(3)
#define BIT_OTP_CHIP_PD_FLAG_CLR                 BIT(2)

/* ANA_REG_GLB_POR_7S_CTRL */

#define BIT_PBINT_7S_FLAG_CLR                    BIT(15)
#define BIT_EXT_RSTN_FLAG_CLR                    BIT(14)
#define BIT_CHGR_INT_FLAG_CLR                    BIT(13)
#define BIT_PBINT2_FLAG_CLR                      BIT(12)
#define BIT_PBINT_FLAG_CLR                       BIT(11)
#define BIT_KEY2_7S_RST_EN                       BIT(9)
#define BIT_PBINT_7S_RST_SWMODE                  BIT(8)
#define BITS_PBINT_7S_RST_THRESHOLD(x)            (((x) & 0xF) << 4)
#define BIT_EXT_RSTN_MODE                        BIT(3)
#define BIT_PBINT_7S_AUTO_ON_EN                  BIT(2)
#define BIT_PBINT_7S_RST_DISABLE                 BIT(1)
#define BIT_PBINT_7S_RST_MODE                    BIT(0)

/* ANA_REG_GLB_HWRST_RTC */

#define BITS_HWRST_RTC_REG_STS(x)                 (((x) & 0xFF) << 8)
#define BITS_HWRST_RTC_REG_SET(x)                 (((x) & 0xFF))

/* ANA_REG_GLB_ARCH_EN */

#define BIT_ARCH_EN                              BIT(0)

/* ANA_REG_GLB_MCU_WR_PROT_VALUE */

#define BIT_MCU_WR_PROT                          BIT(15)
#define BITS_MCU_WR_PROT_VALUE(x)                 (((x) & 0x7FFF))

/* ANA_REG_GLB_PWR_WR_PROT_VALUE */

#define BIT_PWR_WR_PROT                          BIT(15)
#define BITS_PWR_WR_PROT_VALUE(x)                 (((x) & 0x7FFF))

/* ANA_REG_GLB_DCDC_WR_PROT_VALUE */

#define BIT_DCDC_WR_PROT                         BIT(15)
#define BITS_DCDC_WR_PROT_VALUE(x)                (((x) & 0x7FFF))

/* ANA_REG_GLB_TSX_WR_PROT_VALUE */

#define BIT_TSX_WR_PROT                          BIT(15)
#define BITS_TSX_WR_PROT_VALUE(x)                 (((x) & 0x7FFF))

/* ANA_REG_GLB_SMPL_CTRL0 */

#define BITS_SMPL_MODE(x)                         (((x) & 0xFFFF))

/* ANA_REG_GLB_SMPL_CTRL1 */

#define BIT_SMPL_PWR_ON_FLAG                     BIT(15)
#define BIT_SMPL_MODE_WR_ACK_FLAG                BIT(14)
#define BIT_SMPL_PWR_ON_FLAG_CLR                 BIT(13)
#define BIT_SMPL_MODE_WR_ACK_FLAG_CLR            BIT(12)
#define BIT_SMPL_PWR_ON_SET                      BIT(11)
#define BIT_SMPL_EN                              BIT(0)

/* ANA_REG_GLB_RTC_RST0 */

#define BITS_RTC_CLK_FLAG_SET(x)                  (((x) & 0xFFFF))

/* ANA_REG_GLB_RTC_RST1 */

#define BITS_RTC_CLK_FLAG_CLR(x)                  (((x) & 0xFFFF))

/* ANA_REG_GLB_RTC_RST2 */

#define BITS_RTC_CLK_FLAG_RTC(x)                  (((x) & 0xFFFF))

/* ANA_REG_GLB_RTC_CLK_STOP */

#define BIT_RTC_CLK_STOP_FLAG                    BIT(7)
#define BITS_RTC_CLK_STOP_THRESHOLD(x)            (((x) & 0x7F))

/* ANA_REG_GLB_VBAT_DROP_CNT */

#define BITS_VBAT_DROP_CNT(x)                     (((x) & 0xFFF))

/* ANA_REG_GLB_SWRST_CTRL0 */

#define BIT_SW_RST_DCDCSRAM_PD_EN                BIT(9)
#define BIT_EXT_RSTN_PD_EN                       BIT(8)
#define BIT_PB_7S_RST_PD_EN                      BIT(7)
#define BIT_REG_RST_PD_EN                        BIT(6)
#define BIT_WDG_RST_PD_EN                        BIT(5)
#define BIT_REG_RST_EN                           BIT(4)
#define BITS_SW_RST_PD_THRESHOLD(x)               (((x) & 0xF))

/* ANA_REG_GLB_HW_RST_CTRL */

#define BIT_HW_OFF_RST_EN                        BIT(0)

/* ANA_REG_GLB_SWRST_CTRL1 */

#define BIT_SW_RST_DCDCGPU_PD_EN                 BIT(15)
#define BIT_SW_RST_DCDCMODEM_PD_EN               BIT(14)
#define BIT_SW_RST_DCDCMEMQ_PD_EN                BIT(13)
#define BIT_SW_RST_DCDCMEM_PD_EN                 BIT(12)
#define BIT_SW_RST_DCDCGEN1_PD_EN                BIT(11)
#define BIT_SW_RST_DCDCGEN0_PD_EN                BIT(10)
#define BIT_SW_RST_DCDCCORE_PD_EN                BIT(9)
#define BIT_SW_RST_LDO_AVDD12_PD_EN              BIT(8)
#define BIT_SW_RST_LDOVDD18_DCXO_PD_EN           BIT(7)
#define BIT_SW_RST_LDO_VDD28_PD_EN               BIT(6)
#define BIT_SW_RST_LDO_AVDD18_PD_EN              BIT(5)
#define BIT_SW_RST_LDOVDD_RF1V8_PD_EN            BIT(4)
#define BIT_SW_RST_LDOVDD_USB33_PD_EN            BIT(3)
#define BIT_SW_RST_LDOVDD_EMMCCORE_PD_EN         BIT(2)
#define BIT_SW_RST_LDOVDD_SDIO_PD_EN             BIT(1)
#define BIT_SW_RST_LDOVDD_SDCORE_PD_EN           BIT(0)

/* ANA_REG_GLB_OTP_CTRL */

#define BITS_OTP_OP(x)                            (((x) & 0x3) << 1)
#define BIT_OTP_EN                               BIT(0)

/* ANA_REG_GLB_FREE_TIMER_LOW */

#define BITS_TIMER_LOW(x)                         (((x) & 0xFFFF))

/* ANA_REG_GLB_FREE_TIMER_HIGH */

#define BITS_TIMER_HIGH(x)                        (((x) & 0xFFFF))

/* ANA_REG_GLB_LOW_PWR_CLK32K_CTRL */

#define BIT_AUTO_SWITCH_TO_RC_EN                 BIT(14)
#define BITS_MONITOR_ACCURACY(x)                  (((x) & 0x7) << 11)
#define BITS_TIME_BETWEEN_CALIBRATION(x)          (((x) & 0xF) << 7)
#define BITS_TIME_FOR_CALIBRATION(x)              (((x) & 0x3) << 5)
#define BITS_TIME_FOR_DCXO_STABLE(x)              (((x) & 0xF) << 1)
#define BIT_LOW_PWR_CLK32K_EN                    BIT(0)

/* ANA_REG_GLB_VOL_TUNE_CTRL_CORE */

#define BIT_CORE_CLK_SEL                         BIT(14)
#define BITS_CORE_STEP_DELAY(x)                   (((x) & 0x3) << 12)
#define BITS_CORE_STEP_NUM(x)                     (((x) & 0xF) << 8)
#define BITS_CORE_STEP_VOL(x)                     (((x) & 0x1F) << 3)
#define BIT_CORE_VOL_TUNE_START                  BIT(2)
#define BIT_CORE_VOL_TUNE_FLAG                   BIT(1)
#define BIT_CORE_VOL_TUNE_EN                     BIT(0)

/* ANA_REG_GLB_VOL_TUNE_CTRL_CPU */

#define BIT_CPU_CLK_SEL                          BIT(14)
#define BITS_CPU_STEP_DELAY(x)                    (((x) & 0x3) << 12)
#define BITS_CPU_STEP_NUM(x)                      (((x) & 0xF) << 8)
#define BITS_CPU_STEP_VOL(x)                      (((x) & 0x1F) << 3)
#define BIT_CPU_VOL_TUNE_START                   BIT(2)
#define BIT_CPU_VOL_TUNE_FLAG                    BIT(1)
#define BIT_CPU_VOL_TUNE_EN                      BIT(0)

/* ANA_REG_GLB_VOL_TUNE_CTRL_GPU */

#define BIT_GPU_CLK_SEL                          BIT(14)
#define BITS_GPU_STEP_DELAY(x)                    (((x) & 0x3) << 12)
#define BITS_GPU_STEP_NUM(x)                      (((x) & 0xF) << 8)
#define BITS_GPU_STEP_VOL(x)                      (((x) & 0x1F) << 3)
#define BIT_GPU_VOL_TUNE_START                   BIT(2)
#define BIT_GPU_VOL_TUNE_FLAG                    BIT(1)
#define BIT_GPU_VOL_TUNE_EN                      BIT(0)

/* ANA_REG_GLB_VOL_TUNE_CTRL_MODEM */

#define BIT_MODEM_CLK_SEL                        BIT(14)
#define BITS_MODEM_STEP_DELAY(x)                  (((x) & 0x3) << 12)
#define BITS_MODEM_STEP_NUM(x)                    (((x) & 0xF) << 8)
#define BITS_MODEM_STEP_VOL(x)                    (((x) & 0x1F) << 3)
#define BIT_MODEM_VOL_TUNE_START                 BIT(2)
#define BIT_MODEM_VOL_TUNE_FLAG                  BIT(1)
#define BIT_MODEM_VOL_TUNE_EN                    BIT(0)

/* ANA_REG_GLB_DCDC_DVFS_EN */

#define BIT_DCDC_CPU_DVFS_EN                     BIT(3)
#define BIT_DCDC_GPU_DVFS_EN                     BIT(2)
#define BIT_DCDC_CORE_DVFS_EN                    BIT(1)
#define BIT_DCDC_MODEM_DVFS_EN                   BIT(0)

/* ANA_REG_GLB_DCDC_DVS_REG0 */

#define BIT_MEMQ_SYNC_MODE                       BIT(10)
#define BIT_SRAM_SYNC_MODE                       BIT(9)
#define BITS_START_POINT(x)                       (((x) & 0x1FF))

/* ANA_REG_GLB_DCDC_DVS_REG1 */

#define BITS_GAP(x)                               (((x) & 0x3FF))

/* ANA_REG_GLB_DCDC_DVS_REG2 */

#define BITS_DELAY_TIME_UP(x)                     (((x) & 0xFFFF))

/* ANA_REG_GLB_DCDC_DVS_REG3 */

#define BITS_DELAY_TIME_DOWN(x)                   (((x) & 0xFFFF))

/* ANA_REG_GLB_ENDURA_REG0 */

#define BIT_TOP_TRIM_SW_SEL                      BIT(14)
#define BITS_TOP_TRIM(x)                          (((x) & 0x3FFF))

/* ANA_REG_GLB_ENDURA_REG1 */

#define BITS_ENDURA_OPTION_O(x)                   (((x) & 0xFF))

/* ANA_REG_GLB_ENDURA_REG2 */

#define BITS_ENDURA_OPTION_I_AD(x)                (((x) & 0xFF))

/* ANA_REG_GLB_ENDURA_REG3 */

#define BITS_ENDURA_OPTION_I_D(x)                 (((x) & 0xFF))

/* ANA_REG_GLB_ENDURA_REG4 */

#define BIT_ENDURA_OPTION_I_C                    BIT(0)


#endif /* _SC2730_GLB_H */



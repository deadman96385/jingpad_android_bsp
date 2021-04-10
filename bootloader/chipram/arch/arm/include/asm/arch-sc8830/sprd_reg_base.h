/******************************************************************************
 ** File Name:      sprd_reg_base.h                                           *
 ** Author:         Tim.Luo                                                   *
 ** DATE:           07/08/2010                                                *
 ** Copyright:      2010 Spreadtrum, Incoporated. All Rights Reserved.        *
 ** Description:                                                              *
 **                                                                           *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 07/08/2010     Tim.Luo          Create.                                   *
  ******************************************************************************/

#ifndef _SPRD_REG_BASE_H_
#define _SPRD_REG_BASE_H_

#ifdef   __cplusplus
extern "C" {
#endif
/**---------------------------------------------------------------------------*
 **                         Constant Variables                                *
 **---------------------------------------------------------------------------*/
/*----------memory map address----------*/
//Memory Address Map.

#define CTL_BASE_IRAM           0x00000000
#define CTL_BASE_IRAM_END       0x00001FFF
#define IRAM_SIZE               (CTL_BASE_IRAM_END+1-CTL_BASE_IRAM)
#define CTL_BASE_CORE_STM       0x01000000
#define CTL_BASE_CORE_SIGHT     0x10000000
#define CTL_BASE_MP4            0x12000000
//#define CTL_BASE_CPU            0x10600000
//#define CTL_BASE_L2_CACHE       0x10800000
#define CTL_BASE_DMA            0x20100000
#define CTL_BASE_USB            0x20200000

#define CTL_BASE_SDIO0          0x20300000
#define CTL_BASE_SDIO           CTL_BASE_SDIO0
#define CTL_BASE_SDIO1          0x20400000
#define CTL_BASE_SDIO2          0x20500000
#define CTL_BASE_EMMC           0x20600000
#define CTL_BASE_DRM            0x20700000

#define CTL_BASE_DISP0          0x20800000
#define CTL_BASE_DISP           CTL_BASE_DISP0
#define CTL_BASE_DISP1          0x20900000
#define CTL_BASE_GSP            0x20A00000
#define CTL_BASE_NFC            0x20B00000

#define CTL_BASE_SPIN_LCK       0x20C00000
#define CTL_BASE_AHB            0x20D00000
#define CTL_BASE_AXI_BUSMON0    0x20E00000
#define CTL_BASE_AXI_BUSMON1    0x20F00000
#define CTL_BASE_AXI_BUSMON2    0x21000000

#define CTL_BASE_DSI            0x21800000
#define CTL_BASE_GPS            0x21C00000

#define CTL_BASE_LPDDR2_CTL      0x30000000
#define CTL_BASE_LPDDR2_PHY_PUBL 0x30010000
#define CTL_BASE_PUB_APB         0x30020000
#define CTL_BASE_PUB_AXI_BUSMON0 0x30040000
#define CTL_BASE_PUB_AXI_BUSMON1 0x30050000
#define CTL_BASE_PUB_AXI_BUSMON2 0x30060000
#define CTL_BASE_PUB_AXI_BUSMON3 0x30070000
#define CTL_BASE_PUB_AXI_BUSMON4 0x30080000
#define CTL_BASE_PUB_AXI_BUSMON5 0x30090000
#define CTL_BASE_PUB_AXI_BUSMON6 0x300A0000
#define CTL_BASE_PUB_AXI_BUSMON7 0x300B0000
#define CTL_BASE_PUB_AXI_BUSMON8 0x300C0000
#define CTL_BASE_PUB_AXI_BUSMON9 0x300D0000
#define CTL_BASE_AUDIO           0x40000000
#define CTL_BASE_AUDIO_IF        0x40010000
#define CTL_BASE_VBC             0x40020000
#define CTL_BASE_ADI             0x40030000
#define CTL_BASE_AON_SYS_TMR     0x40040000
#define CTL_BASE_AON_TMR         0x40050000
#define CTL_BASE_SPIN_LCK        0x40060000
#define CTL_BASE_RF_SPI          0x40070000
#define CTL_BASE_AON_I2C         0x40080000
#define CTL_BASE_INT             0x40200000
#define CTL_BASE_AP_TMR0         0x40220000
#define CTL_BASE_AP_SYS_TMR      0x40230000
#define CTL_BASE_EFUSE           0x40240000
#define CTL_BASE_KEYPAD          0x40250000
#define CTL_BASE_PWM             0x40260000
#define CTL_BASE_FM              0x40270000
#define CTL_BASE_GPIO            0x40280000
#define CTL_BASE_AP_WDG          0x40290000
#define CTL_BASE_PIN_REG         0x402A0000
#define CTL_BASE_PMU             0x402B0000
#define CTL_BASE_IPI             0x402C0000
#define CTL_BASE_AON_CKG         0x402D0000
#define CTL_BASE_AON_APB         0x402E0000
#define CTL_BASE_GLB_REG         CTL_BASE_AON_APB
#define CTL_BASE_THM             0x402F0000
#define CTL_BASE_AVS_CA7         0x40300000
#define CTL_BASE_AVS_TOP         0x40310000
#define CTL_BASE_CA7_WDG         0x40320000
#define CTL_BASE_AP_TMR1         0x40330000
#define CTL_BASE_AP_TMR2         0x40340000
#define CTL_BASE_CA7_TS0         0x40400000
#define CTL_BASE_CA7_TS1         0x40410000

#define CTL_BASE_SHARE_MEM0      0x50000000	//cp0 w     share mem
#define CTL_BASE_SHARE_MEM1      0x50001000	//cp1 td    share men
#define CTL_BASE_SHARE_MEM2      0x50002000	//cp2 trout share mem
#define CTL_BASE_SHARE_MEM_ALL   0x50003000	//cp  all,      can access
#define CTL_BASE_SHARE_MEM       CTL_BASE_SHARE_MEM0

#define CTL_BASE_MALI           0x60000000
#define CTL_BASE_GPU_APB        0x60100000
#define CTL_BASE_GPU_CKG        0x60200000
#define CTL_BASE_DCAM           0x60800000
#define CTL_BASE_VSP            0x60900000
#define CTL_BASE_ISP            0x60A00000
#define CTL_BASE_JPG            0x60B00000
#define CTL_BASE_CSI2           0x60C00000
#define CTL_BASE_MM_AHB         0x60D00000
#define CTL_BASE_MM_CKG         0x60E00000

#define CTL_BASE_UART0          0x70000000
#define CTL_BASE_UART           CTL_BASE_UART0
#define CTL_BASE_UART1          0x70100000
#define CTL_BASE_UART2          0x70200000
#define CTL_BASE_UART3          0x70300000
#define CTL_BASE_UART4          0x70400000

#define CTL_BASE_DDR            CTL_BASE_LPDDR2_CTL
#define CTL_BASE_DDR_PHY        CTL_BASE_LPDDR2_PHY_PUBL
#define CTL_BASE_KPD            CTL_BASE_KEYPAD

#define CTL_BASE_IIC0       0x70500000
#define CTL_BASE_IIC        CTL_BASE_IIC0
#define CTL_BASE_I2C        CTL_BASE_IIC
#define CTL_BASE_IIC1       0x70600000
#define CTL_BASE_IIC2       0x70700000
#define CTL_BASE_IIC3       0x70800000
#define CTL_BASE_IIC4       0x70900000

#define CTL_BASE_SPI0       0x70A01000
#define CTL_BASE_SPI        CTL_BASE_SPI0
#define CTL_BASE_SPI1       0x70B02000
#define CTL_BASE_SPI2       0x70C00000

#define CTL_BASE_IIS0        0x70D00000
#define CTL_BASE_IIS         CTL_BASE_IIS0
#define CTL_BASE_I2S         CTL_BASE_IIS
#define CTL_BASE_IIS1        0x70E00000
#define CTL_BASE_IIS2        0x70F00000
#define CTL_BASE_IIS3        0x71000000

#define CTL_BASE_SIM0        0x71100000
#define CTL_BASE_SIM         CTL_BASE_SIM0
#define CTL_BASE_SIM1        CTL_BASE_SIM0

#define CTL_BASE_AP_CKG      0x71200000
#define CTL_BASE_APB         0x71300000

#define CTL_BASE_INTC0       0x71401000
#define CTL_BASE_INTC        CTL_BASE_INTC0
#define CTL_BASE_INTC1       0x71500000
#define CTL_BASE_INTC2       0x71600000
#define CTL_BASE_INTC3       0x71700000

#define CTL_BASE_EMC0        0x80000000
#define CTL_BASE_EMC         CTL_BASE_EMC0
#define CTL_BASE_EMC1        0x90000000
#define CTL_BASE_EMC2        0xA0000000
#define CTL_BASE_EMC3        0xB0000000
#define CTL_BASE_EMC4        0xC0000000
#define CTL_BASE_EMC5        0xD0000000
#define CTL_BASE_EMC6        0xE0000000
#define CTL_BASE_EMC7        0xF0000000

#define CTL_BASE_CP_DSP      0xFFE00000
#define CTL_BASE_IROM        0xFFFF0000

#define IRAM_BASE            (CTL_BASE_IRAM)
#define ARM_VBC_BASE         CTL_BASE_VBC
#define SYSTIMER_BASE        CTL_BASE_AP_SYS_TMR	//System timer
#define TIMER_CTL_BASE       CTL_BASE_GLB_TMR	//Timer0 (RTC)
#define PIN_CTL_BASE         CTL_BASE_PIN_REG
#define ARM_UART0_BASE       CTL_BASE_UART0
#define ARM_UART1_BASE       CTL_BASE_UART1
#define ARM_UART2_BASE       CTL_BASE_UART2
#define ARM_UART3_BASE       CTL_BASE_UART3
#define ARM_UART4_BASE       CTL_BASE_UART4
#define I2C_BASE             CTL_BASE_IIC0
#define I2C0_BASE            CTL_BASE_IIC0
#define I2C1_BASE            CTL_BASE_IIC1
#define I2C2_BASE            CTL_BASE_IIC2
#define I2C3_BASE            CTL_BASE_IIC3
#define I2C4_BASE            CTL_BASE_IIC4

#define SPI_BASE             CTL_BASE_SPI0	// SPI0:0x8E002000   SPI1:0x8E003000
#define SPI1_BASE            CTL_BASE_SPI1
#define SPI2_BASE            CTL_BASE_SPI2
#define IIS_BASE             CTL_BASE_IIS0
#define IIS1_BASE            CTL_BASE_IIS1
#define IIS2_BASE            CTL_BASE_IIS2
#define IIS3_BASE            CTL_BASE_IIS3
#define SIM0_BASE            CTL_BASE_SIM0	//SIM0
#define SIM1_BASE            CTL_BASE_SIM1	//SIM1
#define KPD_BASE             CTL_BASE_KEYPAD
#define EFUSE_BASE           CTL_BASE_EFUSE
#define GPIO_BASE            CTL_BASE_GPIO
#define PWM_BASE             CTL_BASE_PWM
#define GREG_BASE            CTL_BASE_GLB_REG

#define TPC_BASE             0x42000280	//Touch Panel Controller
#define GEA_BASE             0x8D000000
#define EPT_BASE             GEA_BASE	//need confirm

#define EMC_BASE             CTL_BASE_EMC0
#define DMAC_BASE            CTL_BASE_DMA
#define DCAM_BASE            CTL_BASE_DCAM
#define USB_BASE             CTL_BASE_USB
#define BUSMON0_BASE         CTL_BASE_AXI_BUSMON0
#define BUSMON1_BASE         CTL_BASE_AXI_BUSMON1
#define SDIO0_BASE           CTL_BASE_SDIO0
#define SDIO1_BASE           CTL_BASE_SDIO1
#define LCDC_BASE            CTL_BASE_DISP
#define ROTATION_BASE        0x20800000
#define AHB_REG_BASE         CTL_BASE_AHB
#define AXI_BUSMON0_BASE     CTL_BASE_AXI_BUSMON0
#define AXI_BUSMON1_BASE     CTL_BASE_AXI_BUSMON1
#define SPINLOCK_BASE        CTL_BASE_SPIN_LCK
#define DRMC_BASE            CTL_BASE_DRM
#define VSPC_BASE            CTL_BASE_VSP

#define CP_DMAC_BASE         0x30100000
#define CP_BUSMON0_BASE      0x30200000
#define CP_BUSMON1_BASE      0x30201000
#define CP_INTC_BASE         0x30300000
#define CP_SYSTMR_BASE       0x30301000
#define CP_WDG_BASE          0x30302000
#define CP_GPIO_BASE         0x30303000
#define CP_GLBREG_BASE       0x30304000
#define CP_GRTC_BASE         0x31000000

#define SDIO2_BASE           CTL_BASE_SDIO2
#define EMMC_BASE            CTL_BASE_EMMC

#define SDIO0_BASE_ADDR      CTL_BASE_SDIO0
#define SDIO1_BASE_ADDR      CTL_BASE_SDIO1
#define SDIO2_BASE_ADDR      CTL_BASE_SDIO2
#define EMMC_BASE_ADDR       CTL_BASE_EMMC
#define SD_BASE_ADDR            CTL_BASE_SDIO0

#define DISPC_BASE           CTL_BASE_DISP
#define ISPC_BASE            CTL_BASE_ISP
#define INTC0_BASE           CTL_BASE_INTC0
#define INTC1_BASE           CTL_BASE_INTC1
#define INTC2_BASE           CTL_BASE_INTC2
#define INTC3_BASE           CTL_BASE_INTC3
#define CP_GLB_REG_BASE      CTL_BASE_GLB_REG
#define GRTC_BASE            CTL_BASE_GLB_TMR
#define ADIM_BASE            CTL_BASE_ADI
#define ADI_BASE             CTL_BASE_ADI

#define USB_REG_BASE         CTL_BASE_USB
#define VBC_BASE             CTL_BASE_VBC
#define AUDIOTOP_BASE        CTL_BASE_AUDIO
#define AUDIOIF_BASE         CTL_BASE_AUDIO_IF
#define UART0_BASE           CTL_BASE_UART0
#define UART1_BASE           CTL_BASE_UART1
#define SIM0_BASE            CTL_BASE_SIM0
#define I2C0_BASE            CTL_BASE_IIC0
#define I2C1_BASE            CTL_BASE_IIC1
#define I2C2_BASE            CTL_BASE_IIC2
#define I2C3_BASE            CTL_BASE_IIC3
#define KPD_BASE             CTL_BASE_KEYPAD
#define SYSTIMER_BASE        CTL_BASE_AP_SYS_TMR
#define PWM_BASE             CTL_BASE_PWM
#define EFUSE_BASE           CTL_BASE_EFUSE
#define GPIO_BASE            CTL_BASE_GPIO
#define IPI_BASE             0x4A002000
#define GLBREG_BASE          CTL_BASE_GLB_REG
#define PINREG_BASE          CTL_BASE_PIN_REG
#define UART2_BASE           CTL_BASE_UART2
#define IIS0_BASE            CTL_BASE_IIS0
#define SPI0_BASE            CTL_BASE_SPI0
#define SPI1_BASE            CTL_BASE_SPI1
#define IIS1_BASE            CTL_BASE_IIS1
#define UART3_BASE           CTL_BASE_UART3
#define SPI2_BASE            CTL_BASE_SPI2
#define SHAREMEM_BASE        CTL_BASE_SHARE_MEM
#define MIPIDSIC_BASE        0x50100000
#define MIPICSIC_BASE        0x50101000
#define LPDDR2C_BASE         CTL_BASE_LPDDR2_CTL
#define LPDDR2P_BASE         CTL_BASE_LPDDR2_PHY_PUBL
#define NANDC_BASE           CTL_BASE_NFC
#define DISPC_CTL_BEGIN         CTL_BASE_DISP0

#ifdef   __cplusplus
}
#endif
#endif				//_SPRD_REG_BASE_H_

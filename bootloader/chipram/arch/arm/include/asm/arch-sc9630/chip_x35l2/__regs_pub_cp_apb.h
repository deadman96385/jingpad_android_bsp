/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _PUB_CP_APB_REG_H
#define _PUB_CP_APB_REG_H

#define CTL_BASE_PUB_CP_APB 0x40080000


#define REG_PUB_CP_APB_IRQ_FROM_CR5_STS       ( CTL_BASE_PUB_CP_APB + 0x0000 )
#define REG_PUB_CP_APB_APB_EB0                ( CTL_BASE_PUB_CP_APB + 0x0008 )
#define REG_PUB_CP_APB_APB_RST0               ( CTL_BASE_PUB_CP_APB + 0x0014 )
#define REG_PUB_CP_APB_APB_MCU_RST            ( CTL_BASE_PUB_CP_APB + 0x0018 )
#define REG_PUB_CP_APB_APB_CLK_SEL0           ( CTL_BASE_PUB_CP_APB + 0x001C )
#define REG_PUB_CP_APB_APB_CLK_DIV0           ( CTL_BASE_PUB_CP_APB + 0x0020 )
#define REG_PUB_CP_APB_APB_ARCH_EB            ( CTL_BASE_PUB_CP_APB + 0x0024 )
#define REG_PUB_CP_APB_APB_MISC_CTL1          ( CTL_BASE_PUB_CP_APB + 0x002C )
#define REG_PUB_CP_APB_APB_PIN_SEL            ( CTL_BASE_PUB_CP_APB + 0x0040 )
#define REG_PUB_CP_APB_APB_SLP_CTL            ( CTL_BASE_PUB_CP_APB + 0x0044 )
#define REG_PUB_CP_APB_APB_SLP_STS            ( CTL_BASE_PUB_CP_APB + 0x0050 )
#define REG_PUB_CP_APB_APB_ROM_PD_CTL         ( CTL_BASE_PUB_CP_APB + 0x0054 )
#define REG_PUB_CP_APB_APB_MEM_LP_CTRL0       ( CTL_BASE_PUB_CP_APB + 0x0058 )
#define REG_PUB_CP_APB_APB_MEM_LP_CTRL1       ( CTL_BASE_PUB_CP_APB + 0x005C )
#define REG_PUB_CP_APB_APB_RSV_REG0           ( CTL_BASE_PUB_CP_APB + 0x0060 )
#define REG_PUB_CP_APB_MDAR_RFFE_INT_STS      ( CTL_BASE_PUB_CP_APB + 0x0064 )
#define REG_PUB_CP_APB_APB_HWRST              ( CTL_BASE_PUB_CP_APB + 0x0080 )
#define REG_PUB_CP_APB_APB_ARM_BOOT_ADDR      ( CTL_BASE_PUB_CP_APB + 0x0084 )

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_IRQ_FROM_CR5_STS
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_DMA_LINK1_INT                         BIT(9)
#define BIT_PUB_CP_APB_SEC1_INT                              BIT(8)
#define BIT_PUB_CP_APB_NPMUIRQ0                              BIT(2)
#define BIT_PUB_CP_APB_NCTIIRQ0                              BIT(1)
#define BIT_PUB_CP_APB_L2_INT                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_EB0
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_EPT1_EB                               BIT(20)
#define BIT_PUB_CP_APB_EIC_RTC_EB                            BIT(19)
#define BIT_PUB_CP_APB_EIC_EB                                BIT(18)
#define BIT_PUB_CP_APB_RFFE_EB                               BIT(17)
#define BIT_PUB_CP_APB_EPT0_EB                               BIT(16)
#define BIT_PUB_CP_APB_GPIO_EB                               BIT(15)
#define BIT_PUB_CP_APB_TMR_RTC_EB                            BIT(14)
#define BIT_PUB_CP_APB_TMR_EB                                BIT(13)
#define BIT_PUB_CP_APB_SYSTMR_RTC_EB                         BIT(12)
#define BIT_PUB_CP_APB_SYSTMR_EB                             BIT(11)
#define BIT_PUB_CP_APB_IIS0_EB                               BIT(7)
#define BIT_PUB_CP_APB_SIM2_EB                               BIT(6)
#define BIT_PUB_CP_APB_SIM1_EB                               BIT(5)
#define BIT_PUB_CP_APB_SIM0_EB                               BIT(4)
#define BIT_PUB_CP_APB_SDIO_EB                               BIT(3)
#define BIT_PUB_CP_APB_UART0_EB                              BIT(2)
#define BIT_PUB_CP_APB_WDG_RTC_EB                            BIT(1)
#define BIT_PUB_CP_APB_WDG_EB                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_RST0
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_EIC_SOFT_RST                          BIT(16)
#define BIT_PUB_CP_APB_RFFE_SOFT_RST                         BIT(15)
#define BIT_PUB_CP_APB_EPT1_SOFT_RST                         BIT(14)
#define BIT_PUB_CP_APB_EPT0_SOFT_RST                         BIT(13)
#define BIT_PUB_CP_APB_GPIO_SOFT_RST                         BIT(12)
#define BIT_PUB_CP_APB_TMR_SOFT_RST                          BIT(11)
#define BIT_PUB_CP_APB_SYSTMR_SOFT_RST                       BIT(10)
#define BIT_PUB_CP_APB_IIS0_SOFT_RST                         BIT(6)
#define BIT_PUB_CP_APB_SIM2_SOFT_RST                         BIT(5)
#define BIT_PUB_CP_APB_SIM1_SOFT_RST                         BIT(4)
#define BIT_PUB_CP_APB_SIM0_SOFT_RST                         BIT(3)
#define BIT_PUB_CP_APB_SDIO_SOFT_RST                         BIT(2)
#define BIT_PUB_CP_APB_UART0_SOFT_RST                        BIT(1)
#define BIT_PUB_CP_APB_WDG_SOFT_RST                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_MCU_RST
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_MCU_SOFT_RST_SET                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_CLK_SEL0
// Register Offset : 0x001C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_CLK_IIS0_PAD_SEL                      BIT(16)
#define BIT_PUB_CP_APB_CLK_IIS0_SEL(x)                       (((x) & 0x3) << 4)
#define BIT_PUB_CP_APB_CLK_UART0_SEL(x)                      (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_CLK_DIV0
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_CLK_IIS0_DIV(x)                       (((x) & 0x3F) << 8)
#define BIT_PUB_CP_APB_CLK_UART0_DIV(x)                      (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_ARCH_EB
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_RTC_ARCH_EB                           BIT(1)
#define BIT_PUB_CP_APB_APB_ARCH_EB                           BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_MISC_CTL1
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_BUFON_CTRL(x)                         (((x) & 0x7) << 4)
#define BIT_PUB_CP_APB_SIM2_CLK_POLARITY                     BIT(3)
#define BIT_PUB_CP_APB_SIM1_CLK_POLARITY                     BIT(2)
#define BIT_PUB_CP_APB_SIM0_CLK_POLARITY                     BIT(1)
#define BIT_PUB_CP_APB_ROM_CLK_EN                            BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_PIN_SEL
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_DJTAG_PIN_IN_SEL                      BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_SLP_CTL
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_APB_PERI_FRC_ON                       BIT(20)
#define BIT_PUB_CP_APB_APB_PERI_FRC_SLP                      BIT(16)
#define BIT_PUB_CP_APB_CHIP_SLP_ARM_CLR                      BIT(4)
#define BIT_PUB_CP_APB_MCU_FORCE_DEEP_SLEEP                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_SLP_STS
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_MCU_PERI_STOP                         BIT(27)
#define BIT_PUB_CP_APB_CHIP_SLEEP_REC_ARM                    BIT(16)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_ROM_PD_CTL
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_ROM_FORCE_ON                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_MEM_LP_CTRL0
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_APB_MEM_LP_CTRL0(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_MEM_LP_CTRL1
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_APB_MEM_LP_CTRL1(x)                   (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_RSV_REG0
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_APB_RSV_REG0(x)                       (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_MDAR_RFFE_INT_STS
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_RFFE_IRQ                              BIT(1)
#define BIT_PUB_CP_APB_MDAR_IRQ                              BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_HWRST
// Register Offset : 0x0080
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_HWRST_REG(x)                          (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_PUB_CP_APB_APB_ARM_BOOT_ADDR
// Register Offset : 0x0084
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_PUB_CP_APB_ARMBOOT_ADDR(x)                       (((x) & 0xFFFF))


#endif // _PUB_CP_APB_REG_H

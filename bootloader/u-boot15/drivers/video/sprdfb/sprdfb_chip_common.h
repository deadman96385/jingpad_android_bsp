/******************************************************************************
 ** File Name:    sprdfb_chip_common.h                                     *
 ** Author:       congfu.zhao                                           *
 ** DATE:         30/04/2013                                        *
 ** Copyright:    2013 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:                                                    *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                       *

 ******************************************************************************/
#ifndef __DISPC_CHIP_COM_H_
#define __DISPC_CHIP_COM_H_

#include <common.h>
#include <asm/io.h>
#include <asm/errno.h>
#include <sprd_regulator.h>
#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>
#include <linux/types.h>
#include <lcd.h>

#ifdef CONFIG_SPX15
#include "sprdfb_chip_7715.h"
#elif defined(CONFIG_SC8830)
#include "sprdfb_chip_8830.h"
#endif

#ifdef CONFIG_SC8825
#include "sprdfb_chip_8825.h"
#endif

#ifdef CONFIG_SC7710G2
#include "sprdfb_chip_7710.h"
#endif

#if defined(CONFIG_SC9630) || defined(CONFIG_SC9836A) || defined(CONFIG_SC9838A)
#include "sprdfb_chip_9630.h"
#define SPRDFB_SUPPORT_LVDS_PANEL
#endif

#ifdef CONFIG_SC9001 
#include "sprdfb_chip_9001.h"
#endif

#ifdef CONFIG_SC9860
#include "sprdfb_chip_9860.h"
#endif

#ifdef CONFIG_SC9833
#include "sprdfb_chip_9833.h"
#endif

#ifdef CONFIG_SOC_SHARKLJ1
#include "sprdfb_chip_9851.h"
#endif

#ifdef CONFIG_SOC_SHARKLE
#include "sprdfb_chip_9835.h"

#endif

#ifdef CONFIG_SOC_IWHALE2
#include "sprdfb_chip_9861.h"
#endif

#ifdef CONFIG_SPRD_SOC_SP9853I
#include "sprdfb_chip_9853i.h"
#endif

#ifdef CONFIG_SOC_PIKE2
#include "sprdfb_chip_7731e.h"
#endif

#ifdef CONFIG_SOC_SHARKL3
#include "sprdfb_chip_9855.h"
#endif

#ifdef CONFIG_SOC_ROC1
#include "sprdfb_chip_710.h"
#endif

#ifdef CONFIG_SOC_SHARKL5
#include "sprdfb_chip_510.h"
#endif

#ifdef CONFIG_SOC_SHARKL5PRO
#include "sprdfb_chip_518.h"
#endif

void __raw_bits_or(unsigned int v, unsigned int a);
void __raw_bits_and(unsigned int v, unsigned int a);
void __raw_bits_set_value(unsigned int reg, unsigned int value, unsigned int bit, unsigned int mask);
void dispc_pll_clk_set(unsigned int clk_src, unsigned int clk_div);
#if !(defined(CONFIG_SOC_IWHALE2) || defined(CONFIG_SPRD_SOC_SP9853I))
void dispc_dbi_clk_set(unsigned int clk_src, unsigned int clk_div);
#endif
void dispc_dpi_clk_set(unsigned int clk_src, unsigned int clk_div);

#endif

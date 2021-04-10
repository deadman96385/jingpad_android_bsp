/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:54:21
 *
 */


#ifndef AUD_CP_APB_H
#define AUD_CP_APB_H

#define CTL_BASE_AUD_CP_APB 0x0150D000


#define REG_AUD_CP_APB_APB_EB         ( CTL_BASE_AUD_CP_APB + 0x0000 )
#define REG_AUD_CP_APB_APB_RST        ( CTL_BASE_AUD_CP_APB + 0x0004 )
#define REG_AUD_CP_APB_AON_BUS_CTRL0  ( CTL_BASE_AUD_CP_APB + 0x0008 )
#define REG_AUD_CP_APB_SLEEP_CTRL0    ( CTL_BASE_AUD_CP_APB + 0x000C )
#define REG_AUD_CP_APB_SLEEP_STATUS   ( CTL_BASE_AUD_CP_APB + 0x0014 )
#define REG_AUD_CP_APB_INT_MASK       ( CTL_BASE_AUD_CP_APB + 0x0018 )
#define REG_AUD_CP_APB_MEM_SLP        ( CTL_BASE_AUD_CP_APB + 0x001C )
#define REG_AUD_CP_APB_AON_RESERVED   ( CTL_BASE_AUD_CP_APB + 0x0020 )
#define REG_AUD_CP_APB_IRAM_ENDIAN    ( CTL_BASE_AUD_CP_APB + 0x0024 )

/* REG_AUD_CP_APB_APB_EB */

#define BIT_AUD_CP_APB_TMR1_EB              BIT(6)
#define BIT_AUD_CP_APB_TMR0_EB              BIT(5)
#define BIT_AUD_CP_APB_RTC_WDG_EB           BIT(2)
#define BIT_AUD_CP_APB_WDG_EB               BIT(1)

/* REG_AUD_CP_APB_APB_RST */

#define BIT_AUD_CP_APB_TMR1_SOFT_RST        BIT(3)
#define BIT_AUD_CP_APB_TMR0_SOFT_RST        BIT(2)
#define BIT_AUD_CP_APB_WDG_SOFT_RST         BIT(1)

/* REG_AUD_CP_APB_AON_BUS_CTRL0 */

#define BIT_AUD_CP_APB_AXI_LP_CTRL_DISABLE  BIT(16)
#define BIT_AUD_CP_APB_OCEM_RST_MASK        BIT(1)

/* REG_AUD_CP_APB_SLEEP_CTRL0 */


/* REG_AUD_CP_APB_SLEEP_STATUS */

#define BIT_AUD_CP_APB_DSP_STATUS(x)        (((x) & 0x3FF) << 19)

/* REG_AUD_CP_APB_INT_MASK */

#define BIT_AUD_CP_APB_WAKE_INT_MSK(x)      (((x) & 0xFFFF))

/* REG_AUD_CP_APB_MEM_SLP */


/* REG_AUD_CP_APB_AON_RESERVED */

#define BIT_AUD_CP_APB_HIGH_RESERVED(x)     (((x) & 0xFFFF) << 16)
#define BIT_AUD_CP_APB_LOW_RESERVED(x)      (((x) & 0xFFFF))

/* REG_AUD_CP_APB_IRAM_ENDIAN */

#define BIT_AUD_CP_APB_IRAM_ENDIAN_SEL      BIT(0)


#endif /* AUD_CP_APB_H */



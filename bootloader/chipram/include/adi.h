/* * Copyright (C) 2012 Spreadtrum Communications Inc.
 */

#ifndef __ADI_H__
#define __ADI_H__

#include <sci_types.h>

#if defined(CONFIG_FPGA)
static inline void sci_adi_init(void) {}
static inline int sci_adi_read(u32 reg) { return 0; }
static inline int sci_adi_write_fast(u32 reg, u16 val, u32 sync) { return 0; }
static inline int sci_adi_write(u32 reg, u16 or_val, u16 clear_msk) { return 0; }
static inline int sci_adi_raw_write(u32 reg, u16 val) { return 0; }
static inline int sci_adi_set(u32 reg, u16 bits) { return 0; }
static inline int sci_adi_clr(u32 reg, u16 bits) { return 0; }
#else
void sci_adi_init(void);
int sci_adi_read(u32 reg);

/*
 * WARN: the arguments (reg, value) is different from
 * the general __raw_writel(value, reg)
 * For sci_adi_write_fast: if set sync 1, then this function will
 * return until the val have reached hardware.otherwise, just
 * async write(is maybe in software buffer)
 */
int sci_adi_write_fast(u32 reg, u16 val, u32 sync);
int sci_adi_write(u32 reg, u16 or_val, u16 clear_msk);

static inline int sci_adi_raw_write(u32 reg, u16 val)
{
	return sci_adi_write_fast(reg, val, 1);
}

static inline int sci_adi_set(u32 reg, u16 bits)
{
	return sci_adi_write(reg, bits, 0);
}

static inline int sci_adi_clr(u32 reg, u16 bits)
{
	return sci_adi_write(reg, 0, bits);
}
#endif

///for analog die register operation
#define ANA_REG_OR(reg_addr, value)     \
    do{\
        sci_adi_write(reg_addr, (unsigned short)(value), 0); \
    }while(0)
#define ANA_REG_MSK_OR(reg_addr, value, msk)        \
    do{\
        sci_adi_write(reg_addr, (unsigned short)((value)&(msk)), msk); \
    }while(0)
#define ANA_REG_AND(reg_addr, value)    \
    do{\
        sci_adi_write(reg_addr, 0, (unsigned short)(~(value))); \
    }while(0)
#define ANA_REG_BIC(reg_addr, value)    \
    do{\
        sci_adi_write(reg_addr, 0, (unsigned short)(value)); \
    }while(0)

#define ANA_REG_SET(reg_addr, value)    sci_adi_raw_write(reg_addr, (unsigned short)(value))

#define ANA_REG_GET(reg_addr)           sci_adi_read(reg_addr)

#endif


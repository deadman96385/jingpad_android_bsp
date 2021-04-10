#ifdef SPRD_TIMER_H
#define SPRD_TIMER_H

#include <asm/arch/sprd_reg.h>
#include <sci_types.h>

void timer_init(void);
void udelay(uint32 us);
void mdelay(uint32 ms);
uint32 sprd_get_syscnt(void);

#endif //SPRD_TIMER_H

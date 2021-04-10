

#ifndef __ASM_ARM_IO_H__
#define __ASM_ARM_IO_H__

#ifdef __KERNEL__

#define __raw_writel(val,add)		(*(volatile unsigned int *)(add) = (val))
#define writel(val,add)					(*(volatile unsigned int *)(add) = (val))

#define __raw_readl(add)			(*(volatile unsigned int *)(add))
#define readl(add)					(*(volatile unsigned int *)(add))

#endif
#endif


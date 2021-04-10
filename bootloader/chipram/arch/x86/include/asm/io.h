

#ifndef __ASM_ARM_IO_H__
#define __ASM_ARM_IO_H__

#ifdef __KERNEL__

#define __raw_writel(val,add)		(*(volatile unsigned int *)(add) = (val))
#define writel(val,add)					(*(volatile unsigned int *)(add) = (val))

#define __raw_readl(add)			(*(volatile unsigned int *)(add))
#define readl(add)					(*(volatile unsigned int *)(add))

static inline unsigned int inl(int port)
{
	unsigned long val;
	__asm__ __volatile__("inl %w1, %k0" : "=a"(val) : "Nd"(port));
	return val;
}

static inline unsigned short inw(int port)
{
	unsigned short val;
	__asm__ __volatile__("inw %w1, %w0" : "=a"(val) : "Nd"(port));
	return val;
}

static inline unsigned char inb(int port)
{
	unsigned char val;
	__asm__ __volatile__("inb %w1, %b0" : "=a"(val) : "Nd"(port));
	return val;
}

static inline void outl(unsigned int val, int port)
{
	__asm__ __volatile__("outl %k0, %w1" : : "a"(val), "Nd"(port));
}

static inline void outw(unsigned short val, int port)
{
	__asm__ __volatile__("outw %w0, %w1" : : "a"(val), "Nd"(port));
}

static inline void outb(unsigned char val, int port)
{
	__asm__ __volatile__("outb %b0, %w1" : : "a"(val), "Nd"(port));
}

#endif
#endif


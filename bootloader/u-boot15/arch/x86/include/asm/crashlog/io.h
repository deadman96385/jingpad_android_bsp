/*
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _IO_H
#define _IO_H

#define readb(addr) (*(volatile unsigned char *) (addr))
#define readw(addr) (*(volatile unsigned short *) (addr))
#define readl(addr) (*(volatile unsigned int *) (addr))
#define readq(addr) (*(volatile uint64_t *) (addr))
#define __raw_readb readb
#define __raw_readw readw
#define __raw_readl readl
#define __raw_readq readq

#define writeb(b,addr) (*(volatile unsigned char *) (addr) = (b))
#define writew(b,addr) (*(volatile unsigned short *) (addr) = (b))
#define writel(b,addr) (*(volatile unsigned int *) (addr) = (b))
#define writeq(b,addr) (*(volatile uint64_t *) (addr) = (b))
#define __raw_writeb writeb
#define __raw_writew writew
#define __raw_writel writel
#define __raw_writeq writeq

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

#endif /* _IO_H */

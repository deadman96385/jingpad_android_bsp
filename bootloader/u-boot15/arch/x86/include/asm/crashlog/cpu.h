/*
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _CPU_H
#define _CPU_H

#include <asm/crashlog/mtrr.h>

int ucode_update(void *a);
#ifdef USE_UCODE
extern char _ucode_start;
#endif

static inline void spin_loop_hint(void)
{
	asm volatile ("pause");
}

static inline void cpuid(unsigned op, unsigned *a, unsigned *b, unsigned *c,
			unsigned *d)
{
	asm volatile (
		"cpuid"
		: "=a" (*a), "=b" (*b), "=c" (*c), "=d" (*d)
		: "a" (op));
}

static inline void cpuid_ext(unsigned op, unsigned ext, unsigned *a,
			unsigned *b, unsigned *c, unsigned *d)
{
	asm volatile (
		"cpuid"
		: "=a" (*a), "=b" (*b), "=c" (*c), "=d" (*d)
		: "a" (op), "c" (ext));
}

static inline unsigned long cr0_read(void)
{
	unsigned long r;
	__asm__ __volatile__(
			"mov %%cr0, %0"
			: "=r" (r));
	return r;
}

static inline void cr0_write(unsigned long r)
{
	__asm__ __volatile__(
			"mov %0, %%cr0"
			:: "r" (r));
}

static inline unsigned long cr2_read(void)
{
	unsigned long r;
	__asm__ __volatile__(
			"mov %%cr2, %0"
			: "=r" (r));
	return r;
}

static inline unsigned long cr3_read(void)
{
	unsigned long r;
	__asm__ __volatile__(
			"mov %%cr3, %0"
			: "=r" (r));
	return r;
}

static inline void cr3_write(unsigned long r)
{
	__asm__ __volatile__(
			"mov %0, %%cr3"
			:: "r" (r));
}

static inline unsigned long cr4_read(void)
{
	unsigned long r;
	__asm__ __volatile__(
			"mov %%cr4, %0"
			: "=r" (r));
	return r;
}

static inline void cr4_write(unsigned long r)
{
	__asm__ __volatile__(
			"mov %0, %%cr4"
			:: "r" (r));
}

#ifdef X86_64
static inline unsigned long cr8_read(void)
{
	unsigned long r;
	__asm__ __volatile__(
			"mov %%cr8, %0"
			: "=r" (r));
	return r;
}

static inline void cr8_write(unsigned long r)
{
	__asm__ __volatile__(
			"mov %0, %%cr8"
			:: "r" (r));
}
#endif

static inline void fpu_init(void)
{
	__asm__ __volatile__("finit");
}

void cpu_ap_init(void);
void _cpu_init(void);
void cpu_resume(void);

void enable_cache(void);
void disable_cache(void);

int get_cpu_count(void);

int mp_init(void (*ap_main)(int cpu_n));

int get_cpu_num(void);
#endif /* _CPU_H */

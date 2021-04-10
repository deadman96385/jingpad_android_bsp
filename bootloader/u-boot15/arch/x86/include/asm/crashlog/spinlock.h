/*
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _SPINLOCK_H
#define _SPINLOCK_H

typedef int spinlock_t;

#define DEFINE_SPINLOCK(x)	spinlock_t x = 0

static inline void spin_lock_init(spinlock_t *lock)
{
	*lock = 0;
}

static inline void spin_lock(spinlock_t *lock)
{
	asm volatile(
		"1:	cmpb	$0, %0;"
		"	je	2f;"
		"	pause;"
		"	jmp	1b;"
		"2:;"
		"	movb	$1, %%al;"
		"	xchgb	%%al, %0;"
		"	cmp	$0, %%al;"
		"	jne	1b"
		:"+m" (*lock) :: "memory", "eax");
}

static inline void spin_unlock(spinlock_t *lock)
{
	asm volatile(
		"mov	$0, %%al;"
		"xchgb	%%al, %0"
		: "=m" (*lock) :: "memory", "eax");
}

static inline void spin_lock_irqsave(spinlock_t *lock, unsigned long *flags)
{
	unsigned long _flags;
	__asm__ __volatile__(
			"pushf;"
			"cli;"
			"pop %0"
			: "=m"(_flags));
	spin_lock(lock);
	*flags = _flags;
}

static inline void spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags)
{
	spin_unlock(lock);
	__asm__ __volatile__(
			"push %0;"
			"popf"
			:: "m"(flags));
}
#endif

/*
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _ATOMIC_H
#define _ATOMIC_H

typedef volatile int atomic_t;

static inline void atomic_inc(atomic_t *a)
{
	__asm__ __volatile("lock incl %0" : "+m" (*a):: "memory");
}

static inline void atomic_dec(atomic_t *a)
{
	__asm__ __volatile("lock decl %0" : "+m" (*a):: "memory");
}

static inline void atomic_add(atomic_t *a, int x)
{
	__asm__ __volatile("lock addl %1, %0" : "+m" (*a) : "r"(x) : "memory");
}

static inline void atomic_sub(atomic_t *a, int x)
{
	__asm__ __volatile("lock subl %1, %0" : "+m" (*a) : "r"(x) : "memory");
}

static inline void atomic_set(atomic_t *a, int x)
{
	*a = x;
}

static inline int atomic_get(atomic_t *a)
{
	return *a;
}
#endif /* _ATOMIC_H */

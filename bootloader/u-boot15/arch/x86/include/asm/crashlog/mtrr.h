/*
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _MTRR_H
#define _MTRR_H

#define IA32_MTRRCAP		0xfe
#define MSR_MTRR_DEF_TYPE	0x2ff
#define MTRR_PHYSBASE0		0x200

#define MTRR_TYPE_MASK		0xff
#define MTRR_TYPE_UC		0x0
#define MTRR_TYPE_WP		0x5
#define MTRR_TYPE_WB		0x6
#define MTRR_FIX_RANGE_ENABLE	(1 << 10)
#define MTRR_ENABLE		(1 << 11)

#define MTRR_FIX4K_C8000	0x269

#define MTRR_PHYS_MASK_VALID	(1 << 11)

#ifndef __ASSEMBLER__

struct mtrr_mem {
	uint64_t addr;
	uint64_t size;
	unsigned type;
};

void mtrr_set_variable_index(int r, uint64_t base, uint64_t size, unsigned type);
int mtrr_set_variable(uint64_t base, uint64_t size, unsigned type);
void mtrr_enable(void);
void mtrr_disable(void);
void mtrr_mem_setup(struct mtrr_mem *m);
#endif

#endif /* _MTRR_H */

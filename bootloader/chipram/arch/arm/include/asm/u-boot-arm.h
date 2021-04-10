


#ifndef _U_BOOT_ARM_H_
#define _U_BOOT_ARM_H_	1

/* for the following variables, see start.S */
extern ulong _bss_start_ofs;	/* BSS start relative to _start */
extern ulong _bss_end_ofs;		/* BSS end relative to _start */
extern ulong IRQ_STACK_START;	/* top of IRQ stack */
extern ulong FIQ_STACK_START;	/* top of FIQ stack */
extern ulong _TEXT_BASE;	/* code start */

int	dram_init (void);

#endif	/* _U_BOOT_ARM_H_ */
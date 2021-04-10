#include <config.h>

.global	g_mmu_page_table
.global	MMU_CacheEnable
.global	MMU_CacheDisable
.global	MMU_CacheFlush

#define IA32_MTRR_DEF_TYPE_MSR 0x2FF
#define IA32_MTRR_PHYSBASE0_MSR 0x200
#define IA32_MTRR_PHYSMASK0_MSR 0x201

.code32

Dcache_InvalRegion:
	ret

Dcache_CleanRegion:
	ret

MMU_CacheEnable:
	pushl	%ecx
	pushl	%ebx

/* assuming 32-bit physical address, set mask bits [63:32] to 0 */
	movl	$0x00000000, %ebx

/* check if actual physical address width is specified in CPUID */
	movl	$0x80000000, %eax
	cpuid
	cmpl	$0x80000008, %eax
	jb	_no_address_width_info

/* CPUID 0x80000008 returns physical address width in EAX [7:0] */
	movl	$0x80000008, %eax
	cpuid

/* mask bits [63:32] <= (1 << (N - 32)) - 1 */
	subb	$32, %al
	jc	_no_address_width_info
	movb	%al, %cl
	movl	$1, %eax
	shll	%cl, %eax
	decl	%eax
	movl	%eax, %ebx
_no_address_width_info:

/*
 *  Make all DRAM writeback-cachable,
 *  except for SYS_DRAM area used for DMA transfers (256MB)
 */

	movl	$IA32_MTRR_PHYSBASE0_MSR, %ecx

/* Variable Range MTRR #0: FFFF8000-FFFFFFFF, WP */

	movl	$0, %edx
	movl	$0xFFFF8005, %eax
	wrmsr
	incl	%ecx
	movl	%ebx, %edx
	movl	$0xFFFF8800, %eax
	wrmsr
	incl	%ecx

/* Variable Range MTRR #1: FFFB0000-FFFBFFFF, WB */

	movl	$0, %edx
	movl	$0xFFFB0006, %eax
	wrmsr
	incl	%ecx
	movl	%ebx, %edx
	movl	$0xFFFF0800, %eax
	wrmsr
	incl	%ecx

/* Variable Range MTRR #2: 00000000-7FFFFFFF, WB */

	movl	$0, %edx
	movl	$0x00000006, %eax
	wrmsr
	incl	%ecx
	movl	%ebx, %edx
	movl	$0x80000800, %eax
	wrmsr
	incl	%ecx

/* Variable Range MTRR #3: 80000000-BFFFFFFF, WB */

	movl	$0, %edx
	movl	$0x80000006, %eax
	wrmsr
	incl	%ecx
	movl	%ebx, %edx
	movl	$0xC0000800, %eax
	wrmsr
	incl	%ecx

#if ((CONFIG_SYS_SDRAM_BASE & 0x0FFFFFFF) != 0)
#error "SYS_DRAM_BASE must be 256MB aligned"
#endif

/* Variable Range MTRR #4: SYS_SDRAM (256MB), UC */

	movl	$(CONFIG_SYS_SDRAM_BASE >> 32), %edx
	movl	$(CONFIG_SYS_SDRAM_BASE & 0xF0000000), %eax
	wrmsr
	incl	%ecx
	movl	%ebx, %edx
	movl	$0xF0000800, %eax
	wrmsr
	incl	%ecx

	xorl	%edx, %edx
	xorl	%eax, %eax

/* Variable Range MTRR #5: disable */

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

/* Variable Range MTRR #6: disable */

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

/* Variable Range MTRR #7: disable */

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

	movl	$IA32_MTRR_DEF_TYPE_MSR, %ecx
	rdmsr
/* clear all non-reserved fields */
	andl	$0xFFFFF300, %eax
/* enable MTRR */
	orl	$(1 << 11), %eax
	wrmsr

/* clear CD and NW */
	movl	%cr0, %eax
	andl	$0x9FFFFFFF, %eax
	movl	%eax, %cr0

	popl	%ebx
	popl	%ecx

	ret

MMU_CacheDisable:

	movl	%cr0, %eax
	orl	$0x60000000, %eax
	movl	%eax, %cr0
	wbinvd

	ret

MMU_CacheFlush:

	wbinvd
	ret

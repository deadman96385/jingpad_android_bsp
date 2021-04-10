/*
 *  U-boot - x86 S3 Suspend/Resume Code
 *
 * (C) Copyright 2015
 * Intel Corporation
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

.global _resume_cpus
.global _resume_start
.global _resume_entry
.global _resume_end
.global stop_this_cpu_normal
.global stop_this_cpu_sram

#include <config.h>
#include <asm/processor-flags.h>
#include <asm/msr-index.h>

#if CONFIG_RESERVED_RAM_START > 0xF0000
#error RESERVED_RAM_START must be at 0xF0000 or below
#endif

#if (CONFIG_RESERVED_RAM_START & 0xFFF) != 0
#error RESERVED_RAM_START must be 4K aligned
#endif

#define VID_TABLE_DATA (CONFIG_BASEIA_SRAM + CONFIG_VID_OFFSET)
#define RESUME_POINTER (CONFIG_BASEIA_SRAM + 0x1FE0)

/* AP startup vector is at the end of reserved area - 4K */

#define SIPI_VECTOR ((CONFIG_RESERVED_RAM_START + 0xF000) >> 12)

/* Real mode code segment base */

#define RM_BASE (CONFIG_RESERVED_RAM_START + 0xF000)

/* Macro for translating address to the copy in SRAM */

#define SRAM_ADDRESS(x) (x - _resume_start) + CONFIG_BASEIA_SRAM

#define IA32_MTRRCAP 0x00FE
#define IA32_MTRR_DEF_TYPE 0x02FF
#define IA32_MTRR_PHYSBASE0 0x0200

#define HPET_BASE 0xFED00000

#define HPET_GCID 0x00
#define HPET_GCFG 0x10
#define HPET_MCV  0xF0

#define ICR_LOW 0xFEE00300

/* DDR ready flag address on PMU */
#define DDR0_ACC_RDY 0xe42b02cc

#define ADDR_DVFS_EN_MOD0	0xE44B0000
#define ADDR_DVFS_EN_MOD1	0xE44C0000

/*
 *  the following part is to be copied to SRAM on startup
 *  and executed from there on resume
 */

.text

.code32

/*
 *  32-bit S3 resume entry is called from Boot ROM
 *  address is read from BIA_DAT1 register
 */

_resume_start:
_unexpected_wake:
	jmp	_unexpected_wake
_resume_entry:
	movl	$SRAM_ADDRESS(_unexpected_wake), AON_APB_DAT_1

#port 0x1b
# reg-mask-val = <0x0 0x00000014 0x00000014>
#		<0x1 0x00010000 0x00010000>
#needs further opt if this is final solution
_set_pmi2axi:
	mov    $0x800000d0,%esi
	mov    $0xcf8,%ebx
	mov    %esi,%eax
	mov    %ebx,%edx
	out    %eax,(%dx)
	mov    $0xcfc,%ecx
	mov    $0x61b00f0,%eax
	mov    %ecx,%edx
	out    %eax,(%dx)
	mov    $0x800000d4,%edi
	mov    %edi,%eax
	mov    %ebx,%edx
	out    %eax,(%dx)
	mov    %ecx,%edx
	in     (%dx),%eax
	and    $0xffffffeb,%eax
	mov    %eax,%ebp
	mov    %edi,%eax
	mov    %ebx,%edx
	out    %eax,(%dx)
	mov    %ebp,%eax
	or     $0x14,%eax
	mov    %ecx,%edx
	out    %eax,(%dx)
	mov    %esi,%eax
	mov    %ebx,%edx
	out    %eax,(%dx)
	mov    $0x71b00f0,%eax
	mov    %ecx,%edx
	out    %eax,(%dx)
	mov    %esi,%eax
	mov    %ebx,%edx
	out    %eax,(%dx)
	mov    $0x61b01f0,%eax
	mov    %ecx,%edx
	out    %eax,(%dx)
	mov    %edi,%eax
	mov    %ebx,%edx
	out    %eax,(%dx)
	mov    %ecx,%edx
	in     (%dx),%eax
	and    $0xfffeffff,%eax
	mov    %eax,%ebp
	mov    %edi,%eax
	mov    %ebx,%edx
	out    %eax,(%dx)
	mov    %ebp,%eax
	or     $0x10000,%eax
	mov    %ecx,%edx
	out    %eax,(%dx)
	mov    %esi,%eax
	mov    %ebx,%edx
	out    %eax,(%dx)
	mov    $0x71b01f0,%eax
	mov    %ecx,%edx
	out    %eax,(%dx)

	movl	$SRAM_ADDRESS(_set_stack), %ebp
	jmp	mtrr_setup

_set_stack:

	movl	$(VID_TABLE_DATA), %esp

	movl	$(VID_TABLE_DATA), %esi

	movl	$ADDR_DVFS_EN_MOD0, %ebx
	movl	$SRAM_ADDRESS(vmi_offsets), %edx
	movl	$(vmi_off_end - vmi_offsets), %ecx
_next_vid0:
	xorl	%eax, %eax
	movb	(%edx), %al
	incl	%edx
	movl	%eax, %edi
	movl	(%esi), %eax
	addl	$4, %esi
	movl	%eax, (%ebx, %edi)
	loop	_next_vid0

	movl	$ADDR_DVFS_EN_MOD1, %ebx
	movl	$SRAM_ADDRESS(vmi_offsets), %edx
	movl	$(vmi_off_end - vmi_offsets), %ecx
_next_vid1:
	xorl	%eax, %eax
	movb	(%edx), %al
	incl	%edx
	movl	%eax, %edi
	movl	(%esi), %eax
	addl	$4, %esi
	movl	%eax, (%ebx, %edi)
	loop	_next_vid1

/* wait for DRAM wake */
_wait_ddr:
        movl    DDR0_ACC_RDY, %eax
        testl   $0x1, %eax
        jnz     1f
        pause
        jmp     _wait_ddr
1:
/* update ucode on BSP and APs */

	call	hpet_init

	call	ucode_update
	testl	%eax, %eax
	jnz	_bsp_update_fail
	call	bios_reset_done

_bsp_update_fail:

/* copy AP startup code to the reserved DRAM area */

	movl	$(SIPI_VECTOR << 12), %edi
	movl	$SRAM_ADDRESS(_startup2_start), %esi
	movl	$(_startup2_end - _startup2_start), %ecx
	addl	$3, %ecx
	shrl	$2, %ecx
	cld
	rep	movsd

	call	update_other_cpus

/*
 *  if the kernel resume entry point is above 1 MB, there is 32-bit code
 */

	movl	$(RESUME_POINTER), %esi

/* get the trampoline IA-32e page tables */

	movl	8 (%esi), %eax
	andl	$0xfffff000, %eax
	jz	_no_64bit_entry

/* check the tables: translate address 0 */

	movl	$4, %ecx
_next_level:
	movl	%eax, %ebx
	movl	(%ebx), %eax
	movl	4 (%ebx), %edx
	testl	%edx, %edx
	jnz	_no_64bit_entry
	testl	%eax, %eax
	jz	_no_64bit_entry
	test	$1, %eax
	jz	_no_64bit_entry
	testb	$0x80, %al
	jnz	_large_page
	andl	$0xfffff000, %eax
	loop	_next_level
_large_page:
	andl	$0xfffff000, %eax
	jnz	_no_64bit_entry

/* swith to a short version of resume GDT, first 4 entries */

	push	$SRAM_ADDRESS(resume_gdt)
	push	$0x001f0000
	lgdtl	2 (%esp)
	addl	$8, %esp

	movl	8 (%esi), %eax
	movl	%eax, %cr3

/* set IA32_EFER.LME */
	movl	$0xC0000080, %ecx
	rdmsr
	orb	$1, %ah
	wrmsr

/* set CR4.PSE and CR4.PAE */

	movl	%cr4, %eax
	or	$0x30, %eax
	mov	%eax, %cr4

/* set CR0.PG */

	movl	%cr0, %eax
	orl	$0x80000000, %eax
	movl	%eax, %cr0

	ljmp	$0x10, $SRAM_ADDRESS(_start64)

_no_64bit_entry:

	movl	0x10 (%esi), %eax
	cmpl	$(0x100000), %eax
	jb	_use_rm_entry
	jmpl	*%eax

_use_rm_entry:

/*
 *  copy kernel resume entry point address to the reserved area,
 *  converting to a real mode logical address
 *  i.e. 0009A1D0 -> 9A00:01D0
 */

	movl	$0x200, %ebx
	leal	RM_BASE (%ebx), %edi
	movl	(%esi), %eax
	movl	%eax, %edx
	andl	$0x000FF000, %edx
	shll	$12, %edx
	andl	$0x00000FFF, %eax
	orl	%edx, %eax
	movl	%eax, (%edi)

/* jump to 16-bit code that will switch to real mode */

	movl	$SRAM_ADDRESS(gdt_ptr), %esi
	lgdt	(%esi)
	movl	$0x28, %eax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %ss
	movl	$0x1000, %esp
	mov	%ax, %fs
	mov	%ax, %gs
	ljmp	$0x20, $(_switch_to_real - _startup2_start)

.code64

_start64:
	movq	$0xffffffff, %rax
	andq	%rax, %rsi
	movq	(%rsi), %rbx
	jmp	*%rbx

/* this part is to be copied into reserved DRAM area */

	.align 16

.code16

/*
 *  AP startup entry
 *  CS:IP = VV00:0000, where VV is SIPI_VECTOR
 */

_startup2_start:

	wbinvd

	/* load the temporary Global Descriptor Table */

	movw	$(gdt_ptr - _startup2_start), %bx
	data32	cs	lgdt	(%bx)

	movw	$(idt_ptr - _startup2_start), %bx
	data32	cs	lidt	(%bx)

	/* Enable protected mode */
	movl	%cr0, %eax
	orb	$1, %al
	movl	%eax, %cr0

	movw	$0x18, %ax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %ss
	nop
	mov	%ax, %fs
	mov	%ax, %gs

	/* jump to the 32bit AP startup code */

	data32	ljmp	$0x08, $SRAM_ADDRESS(ap_startup32)

	.align	8

	.word	0
gdt_ptr:
	.word	6 * 8 - 1	/* limit (6 GDT entries) */
gdt_ptr_base:
	.long	SRAM_ADDRESS(resume_gdt)	/* base */

	.word	0
idt_ptr:
	.word	0		/* limit */
	.long	0		/* base */

	.align	8

hpet_mhz:
	.quad	0

_resume_cpus:
	.long	1

cpu_started:
	.long	0

cpu_updated:
	.long	0

vmi_offsets:
	.byte	0x00, 0x14, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34, 0x38, 0x3c, 0x60, 0x64
vmi_off_end:

	.align 16

/*
 * 16-bit code for switching to real mode
 */

.code16

_switch_to_real:
	movl	%cr0, %eax
	andb	$0xFE, %al
	movl	%eax, %cr0
	ljmp	$(RM_BASE >> 4), $(_real_switch_jump - _startup2_start)

_real_switch_jump:
	movw	$(RM_BASE >> 4), %ax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %ss
	nop
	mov	%ax, %fs
	mov	%ax, %gs

	ljmp	*(%bx)

_real_switch_end:

_startup2_end:

	.align 16

resume_gdt:
	/*
	 * The GDT table ...
	 *
	 *	 Selector	Type
	 *	 0x00		NULL
	 *	 0x08		Unused
	 *	 0x10		32-bit code
	 *	 0x18		32-bit data/stack
	 *	 0x20		16-bit code, base=$RM_BASE
	 *	 0x28		16-bit data, base=$RM_BASE
	 */
	/* The NULL Desciptor - Mandatory */
	.word	0x0000		/* limit_low */
	.word	0x0000		/* base_low */
	.byte	0x00		/* base_middle */
	.byte	0x00		/* access */
	.byte	0x00		/* flags + limit_high */
	.byte	0x00		/* base_high */

	/*
	 * The 32-bit Code Segment Descriptor:
	 * - Base   = 0x00000000
	 * - Size   = 4GB
	 * - Access = Present, Ring 0, Exec (Code), Readable
	 * - Flags  = 4kB Granularity, 32-bit
	 */
	.word	0xffff		/* limit_low */
	.word	0x0000		/* base_low */
	.byte	0x00		/* base_middle */
	.byte	0x9b		/* access */
	.byte	0xcf		/* flags + limit_high */
	.byte	0x00		/* base_high */

	/*
	 * The 64-bit Code Segment Descriptor:
	 * - Base   = 0x00000000
	 * - Size   = 4GB
	 * - Access = Present, Ring 0, Exec (Code), Readable
	 * - Flags  = 4kB Granularity, L
	 */
	.word	0xffff		/* limit_low */
	.word	0x0000		/* base_low */
	.byte	0x00		/* base_middle */
	.byte	0x9b		/* access */
	.byte	0xaf		/* flags + limit_high */
	.byte	0x00		/* base_high */

	/*
	 * The Data Segment Descriptor:
	 * - Base   = 0x00000000
	 * - Size   = 4GB
	 * - Access = Present, Ring 0, Non-Exec (Data), Writable
	 * - Flags  = 4kB Granularity, 32-bit
	 */
	.word	0xffff		/* limit_low */
	.word	0x0000		/* base_low */
	.byte	0x00		/* base_middle */
	.byte	0x93		/* access */
	.byte	0xcf		/* flags + limit_high */
	.byte	0x00		/* base_high */

	/*
	 * The Code Segment Descriptor (Real Mode Switch):
	 * - Base   = 0x00000000
	 * - Size   = 64KB
	 * - Access = Present, Ring 0, Exec (Code), Readable
	 * - Flags  = Byte Granularity, 16-bit
	 */
	.word	0xffff		/* limit_low */
	.word	RM_BASE & 0xffff	/* base_low */
	.byte	RM_BASE >> 16	/* base_middle */
	.byte	0x9b		/* access */
	.byte	0x00		/* flags + limit_high */
	.byte	0x00		/* base_high */

	/*
	 * The Data Segment Descriptor (Real Mode Switch):
	 * - Base   = 0x00000000
	 * - Size   = 64KB
	 * - Access = Present, Ring 0, Non-Exec (Data), Writable
	 * - Flags  = Byte Granularity
	 */
	.word	0xffff		/* limit_low */
	.word	RM_BASE & 0xffff	/* base_low */
	.byte	RM_BASE >> 16	/* base_middle */
	.byte	0x93		/* access */
	.byte	0x00		/* flags + limit_high */
	.byte	0x00		/* base_high */

.code32

ap_startup32:

	movl	$SRAM_ADDRESS(ap_update32), %ebp
	jmp	mtrr_setup

ap_update32:

/* get next available number, incrementing total CPU count */

	movl	$SRAM_ADDRESS(cpu_started), %ebx
	movl	$1, %eax
	lock	xadd	%eax, (%ebx)
	movl	%eax, %edi

/*
 *  wait for our turn to update microcode
 *  (this CPU's number is equal to cpu_updated)
 */

	movl	$SRAM_ADDRESS(cpu_updated), %ebx

_wait_update_turn:
	pause
	cmpl	%edi, (%ebx)
	jne	_wait_update_turn

/* all non-boot CPUs use the same stack area */

	movl	$(CONFIG_RESERVED_RAM_START + 0xFFFC), %esp

/* update ucode on AP */

	call	ucode_update

/* increment cpu_updated */

	movl	$SRAM_ADDRESS(cpu_updated), %ebx
	lock	incl	(%ebx)

/* enter C6FS state */

_resume_stop_ap:
	movl	$0xe2, %ecx
	rdmsr
	orl	$0x80f, %eax
	wrmsr
_hang_loop:
	xorl	%edx, %edx
	xorl	%ecx, %ecx
	movl	$(CONFIG_RESERVED_RAM_START), %eax
	monitor
	xorl	%ecx, %ecx
	movl	$0x52, %eax
	mwait
	jmp	_hang_loop

/*
 *  CPU microcode update
 *  Called by BSP and AP
 *  Return value:
 *    -1  Update error
 *     0  Successfully updated
 *     1  The same revision has already been applied
 */

ucode_update:

/* Microcode data is at the beginning of reserved DRAM area */

	movl	$CONFIG_RESERVED_RAM_START, %esi

/* Check microcode version before updating */

	xorl	%eax, %eax
	xorl	%edx, %edx
	movl	$MSR_IA32_UCODE_REV, %ecx
	wrmsr

	movl	$1, %eax
	cpuid

	movl	$MSR_IA32_UCODE_REV, %ecx
	rdmsr

	cmpl	4 (%esi), %edx
	jne	_do_update

	movl	$1, %eax
	jmp	_update_ret

_do_update:

/* Update microcode */

	leal	0x30 (%esi), %eax
	xorl	%edx, %edx
	movl	$MSR_IA32_UCODE_WRITE, %ecx
	wrmsr

/* Check microcode version after updating */

	xorl	%eax, %eax
	xorl	%edx, %edx
	movl	$MSR_IA32_UCODE_REV, %ecx
	wrmsr

	movl	$1, %eax
	cpuid

	movl	$MSR_IA32_UCODE_REV, %ecx
	rdmsr

	cmpl	4 (%esi), %edx
	je	_updated_ok

	movl	$(0xFFFFFFFF), %eax
	jmp	_update_ret

_updated_ok:
	xorl	%eax, %eax

_update_ret:

	ret

bios_reset_done:

/*
 *  IOSF Message Data:
 *    bit [0] (BIOS_RESET_DONE)
 */

	movl	$0x800000D4, %eax
	movl	$0xCF8, %edx
	outl	%eax, %dx

	movl	$0x00000001, %eax
	movl	$0xCFC, %edx
	outl	%eax, %dx

/*
 *  IOSF Message Control:
 *    opcode 0x07 (Write), port 0x04 (Punit),
 *    offset 0x05 (PUNIT_BIOS_RESET_CPL)
 */

	movl	$0x800000D0, %eax
	movl	$0xCF8, %edx
	outl	%eax, %dx

	movl	$0x070405F0, %eax
	movl	$0xCFC, %edx
	outl	%eax, %dx

	ret

/* 32-bit entry called from boot ROM on S3 resume */

_resume_s3:

update_other_cpus:
	movl	$1, %eax
	movl	$SRAM_ADDRESS(cpu_started), %ebx
	movl	%eax, (%ebx)
	movl	$SRAM_ADDRESS(cpu_updated), %ebx
	movl	%eax, (%ebx)

	movl	$ICR_LOW, %esi

/* broadcast Init IPI to all APs */

	movl	$0x000C4500, %eax
	mov	%eax, (%esi)

/*  1-millisecond delay loop
 *  (IA SDM specifies 10 milliseconds)
 */

	movl	$1000, %eax
	call	hpet_udelay

/* broadcast first Startup IPI to all APs */

	movl	$(0x000C4600 | SIPI_VECTOR), %eax
	mov	%eax, (%esi)

/* 200-microsecond delay loop */

	movl	$200, %eax
	call	hpet_udelay

/* broadcast second Startup IPI to all APs */

	movl	$(0x000C4600 | SIPI_VECTOR), %eax
	mov	%eax, (%esi)

/* 200-microsecond delay loop */

	movl	$200, %eax
	call	hpet_udelay

/* wait for APs to start */
	movl	SRAM_ADDRESS(_resume_cpus), %eax
	movl	$SRAM_ADDRESS(cpu_started), %ebx
_wait_for_ap_startup:
	pause
	cmpl	%eax, (%ebx)
	jb	_wait_for_ap_startup

/* wait for ucode update on all APs */

_wait_for_ap_update:
	pause
	movl	$SRAM_ADDRESS(cpu_started), %ebx
	movl	(%ebx), %eax
	movl	$SRAM_ADDRESS(cpu_updated), %ebx
	cmpl	(%ebx), %eax
	jne	_wait_for_ap_update

	ret

hpet_init:
	push	%esi
	push	%edi
	push	%ebx
	movl	$HPET_BASE, %ebx

/* get Counter Tick Period (GCID.CTP) in femtoseconds (10^-15 s) */

	movl	HPET_GCID + 4 (%ebx), %eax
	testl	%eax, %eax
	jz	_hpet_init_error
	movl	%eax, %ecx

/* compute frequency in MHz as 64-bit fixed point number */
/* f_mhz_32 = 10^9 * 2^32 / GCID.CTP */

	movl	$1000000000, %eax
	xorl	%edx, %edx
	divl	%ecx
	movl	%eax, %edi
	xorl	%eax, %eax
	divl	%ecx
	movl	%eax, %esi

/*
 * after integer division, round to nearest:
 * if (reminder >= divisor / 2) quotient += 1;
 *
 * for GCID.CTP = 0x0429B17F (69841269),
 * the result will be 0x0000000E51743D97 (14.3181799 MHz)
 *   integer part:  0x0000000E (14)
 *   fraction part: 0x51743D97 (0.3181799 * 2^32)
 */

	movl	%ecx, %eax
	shrl	$1, %eax
	cmpl	%eax, %edx
	cmc
	adcl	$0, %esi
	adcl	$0, %edi

	movl	$1, %eax
	movl	%eax, HPET_GCFG (%ebx)

	movl	$SRAM_ADDRESS(hpet_mhz), %ebx

	movl	%esi, (%ebx)
	movl	%edi, 4 (%ebx)

_hpet_init_error:
	pop	%ebx
	pop	%edi
	pop	%esi
	ret

/*
 *  udelay - delay in microseconds
 *  Arguments: t_us in %eax
 */

hpet_udelay:
	push	%esi
	push	%edi
	push	%ebx
	push	%edx
	push	%ecx

/*
 *  %ecx = t_us
 */

	movl	%eax, %ecx

/*
 *  read HPET counter
 *  %esi = t_0
 */

	movl	$HPET_BASE, %ebx
	movl	HPET_MCV (%ebx), %eax
	movl	%eax, %esi

/*
 *  compute number of ticks to wait:
 *  N = t_us * f_MHz
 */

	movl	$SRAM_ADDRESS(hpet_mhz), %ebx
	movl	(%ebx), %eax
	mull	%ecx
	addl	$0x80000000, %eax
	adcl	$0, %edx
	movl	%edx, %edi
	movl	4 (%ebx), %eax
	mull	%ecx
	addl	%eax, %edi

/* wait for N ticks */

	movl	$HPET_BASE, %ebx
_hpet_udelay_wait:
	pause
	movl	HPET_MCV (%ebx), %eax
	subl	%esi, %eax
	cmpl	%edi, %eax
	jb	_hpet_udelay_wait
_hpet_udelay_done:
	pop	%ecx
	pop	%edx
	pop	%ebx
	pop	%edi
	pop	%esi
	ret

/*
 *  MTRR setup
 *  Called by BSP and AP
 *  Return address in %ebp
 */

mtrr_setup:

/* disable cache */

	movl	%cr0, %eax
	orl	$0x60000000, %eax
	movl	%eax, %cr0
	wbinvd

/* disable MTRR */

	xorl	%eax, %eax
	xorl	%edx, %edx
	movl	$IA32_MTRR_DEF_TYPE, %ecx
	wrmsr

/* get the physical address mask [63:32] */

	xorl	%edi, %edi
	movl	$0x80000000, %eax
	cpuid
	cmpl	$0x80000008, %eax
	jb	no_address_info
	movl	$0x80000008, %eax
	cpuid
	subb	$32, %al
	jb	no_address_info
	movb	%al, %cl
	movl	$1, %edi
	shll	%cl, %edi
	decl	%edi
no_address_info:
	movl	%edi, %ebx

/* get the number of MTRR */

	movl	$IA32_MTRRCAP, %ecx
	rdmsr
	andl	$0xFF, %eax
	movl	%eax, %edi

	movl	$IA32_MTRR_PHYSBASE0, %ecx
	xorl	%esi, %esi

/* Variable Range MTRR #0: FFFF0000-FFFFFFFF, WP (ROM) */

	movl	$0, %edx
	movl	$0xFFFF0005, %eax
	wrmsr
	incl	%ecx

	movl	%ebx, %edx
	movl	$0xFFFF0800, %eax
	wrmsr
	incl	%ecx

	incl	%esi


/* Variable Range MTRR #1: xxxx0000-xxxxFFFF, WP (SRAM) */

	movl	$0, %edx
	movl	$(CONFIG_BASEIA_SRAM + 0x005), %eax
	wrmsr
	incl	%ecx

	movl	%ebx, %edx
	movl	$0xFFFF0800, %eax
	wrmsr
	incl	%ecx

	incl	%esi

/* Variable Range MTRR #2: 00000000-7FFFFFFF, WB (DRAM) */

	movl	$0, %edx
	movl	$0x00000006, %eax
	wrmsr
	incl	%ecx

	movl	%ebx, %edx
	movl	$0x80000800, %eax
	wrmsr
	incl	%ecx

	incl	%esi

/* disable the rest of Variable Range MTRR */

	xorl	%eax, %eax
	xorl	%edx, %edx

_mtrr_next:
	cmpl	%edi, %esi
	jnb	_mtrr_enable

	wrmsr
	incl	%ecx
	wrmsr
	incl	%ecx

	incl	%esi
	jmp	_mtrr_next

_mtrr_enable:
	movl	$IA32_MTRR_DEF_TYPE, %ecx
	rdmsr
	orl	$(1 << 11), %eax
	wrmsr

/* clear CD and NW */

	movl	%cr0, %eax
	andl	$0x9FFFFFFF, %eax
	movl	%eax, %cr0

	jmpl	*%ebp

_resume_end:

/**
 *  stop_this_cpu_sram() - jump to SRAM code that will keep this CPU in C6FS
 */
stop_this_cpu_sram:
	movl	$SRAM_ADDRESS(_resume_stop_ap), %ebx
	calll	*%ebx
	ret

stop_this_cpu_normal:
	calll   _resume_stop_ap
	ret


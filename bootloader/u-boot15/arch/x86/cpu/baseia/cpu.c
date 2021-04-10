/*
 * Copyright (C) 2015, Intel Corporation
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * Based on code from coreboot
 */
#define DEBUG

#include <common.h>
#include <cpu.h>
#include <dm.h>
#include <asm/cpu.h>
#include <asm/lapic.h>
#include <asm/mp.h>
#include <asm/msr.h>
#include <asm/bootparam.h>
#include <asm/microcode.h>
#include <asm/mv/mobilevisor.h>
#include <chipram_env.h>

#ifdef CONFIG_BASEIA_S3
#define RESERVED_RAM_SIZE 0x10000
#define RESUME_ENTRY_P (CONFIG_BASEIA_SRAM + 0x1FF8)
/* Macro for translating address to the copy in SRAM */
#define SRAM_ADDRESS(x) (x - _resume_start) + CONFIG_BASEIA_SRAM
extern char _resume_start[], _resume_entry[], _resume_end[];
extern int _resume_cpus;
#endif

#ifdef CONFIG_SMP
static int enable_smis(struct udevice *cpu, void *unused)
{
	return 0;
}

static struct mp_flight_record mp_steps[] = {
	MP_FR_BLOCK_APS(mp_init_cpu, NULL, mp_init_cpu, NULL),
	/* Wait for APs to finish initialization before proceeding. */
	MP_FR_BLOCK_APS(NULL, NULL, enable_smis, NULL),
};

static int detect_num_cpus(void)
{
	int ecx = 0;

	/*
	 * Use the algorithm described in Intel 64 and IA-32 Architectures
	 * Software Developer's Manual Volume 3 (3A, 3B & 3C): System
	 * Programming Guide, Jan-2015. Section 8.9.2: Hierarchical Mapping
	 * of CPUID Extended Topology Leaf.

	 */
	while (1) {
		struct cpuid_result leaf_b;

		leaf_b = cpuid_ext(0xb, ecx);

		/*
		 * BaseIA doesn't have hyperthreading so just determine the
		 * number of cores by from level type (ecx[15:8] == * 2)
		 */
		if ((leaf_b.ecx & 0xff00) == 0x0200)
			return leaf_b.ebx & 0xffff;
		ecx++;
	}
}

static int baseia_init_cpus(void)
{
	struct mp_params mp_params;

	lapic_setup();

	mp_params.num_cpus = detect_num_cpus();
	debug("num of cpus detected %d\n", mp_params.num_cpus);

	mp_params.parallel_microcode_load = 0,
		mp_params.flight_plan = &mp_steps[0];
	mp_params.num_records = ARRAY_SIZE(mp_steps);
	mp_params.microcode_pointer = gd->arch.microcode_data;

	if (mp_init(&mp_params)) {
		printf("Warning: MP init failure\n");
		return -EIO;
	}

	return 0;
}
#endif

static void bios_reset_done(void)
{
	/* IOSF Message Data:
	 *  bit [0] (BIOS_RESET_DONE)
	 */
	outl(0x800000D4, 0xCF8);
	outl(0x00000001, 0xCFC);

	/* IOSF Message Control:
	 *  opcode 0x07 (Write), port 0x04 (Punit),
	 *  offset 0x05 (PUNIT_BIOS_RESET_CPL)
	 */
	outl(0x800000D0, 0xCF8);
	outl(0x070405F0, 0xCFC);
}

int x86_init_cpus(void)
{
	printf("U-boot run in %s mode\n",
		is_x86_mobilevisor()?"vmm guest":"native");

	if (microcode_update() >= 0)
		bios_reset_done();

#ifdef CONFIG_BASEIA_S3
	if(!is_x86_mobilevisor()) {
		boot_mode_t boot_role;
		chipram_env_t* cr_env = get_chipram_env();

		boot_role = cr_env->mode;
		stop_this_cpu = stop_this_cpu_normal;
		if(boot_role != BOOTLOADER_MODE_DOWNLOAD) {
			stop_this_cpu = stop_this_cpu_sram;
			_resume_cpus = detect_num_cpus();

			/* Copy S3 resume code into SRAM */
			memcpy((void *) CONFIG_BASEIA_SRAM, (const void *) _resume_start,
				_resume_end - _resume_start);

			/*
			*  Write resume entry point address to SRAM and store it there, kernel
			*  will read it from SRAM and programe it to AON_APB_DAT_1 at late
			*  stage of S3. On CPU reset, the boot ROM will jump there if reset
			*  reason is S3.
			*/
			writel(SRAM_ADDRESS(_resume_entry), RESUME_ENTRY_P);
		}

		/* Copy CPU microcode data into the reserved DRAM area */
		if (gd->arch.microcode_size <= RESERVED_RAM_SIZE) {
			memcpy((void *) CONFIG_RESERVED_RAM_START,
				gd->arch.microcode_data,
				gd->arch.microcode_size);
		} else {
			printf("Microcode data does not fit"
				" into reserved DRAM area\n");
		}
	}

#endif
#ifndef CONFIG_MOBILEVISOR
	/* enable lbr */
	{
		unsigned low, high;
		rdmsr(MSR_IA32_DEBUGCTLMSR, low, high);
		wrmsr(MSR_IA32_DEBUGCTLMSR, low | DEBUGCTLMSR_LBR, high);
	}
#endif

#ifdef CONFIG_SMP
	debug("Init additional CPUs class %d\n", UCLASS_CPU);
	if(!is_x86_mobilevisor())
		baseia_init_cpus();
#endif

	return 0;
}

int cpu_x86_baseia_probe(struct udevice *dev)
{
	debug("Init:%s:%s\n", dev->driver->name, dev->name);

	gd->arch.hardware_subarch = X86_SUBARCH_BASEIA;

	return 0;
}

static unsigned bus_freq(void)
{
	msr_t clk_info = msr_read(MSR_BSEL_CR_OVERCLOCK_CONTROL);

	switch (clk_info.lo & 0x3) {
	case 0:
		return 266600000;
	case 1:
		return 133300000;
	case 2:
		return 200000000;
	case 3:
		return 166666666;
	default:
		return 0;
	}
}

static unsigned long tsc_freq(void)
{
	msr_t platform_info;
	ulong bclk = bus_freq();

	if (!bclk)
		return 0;

	platform_info = msr_read(MSR_PLATFORM_INFO);

	return bclk * ((platform_info.lo >> 8) & 0xff);
}

int baseia_get_info(struct udevice *dev, struct cpu_info *info)
{
	info->cpu_freq = tsc_freq();
	info->features = 1 << CPU_FEAT_L1_CACHE | 1 << CPU_FEAT_MMU;

	return 0;
}

int cpu_x86_baseia_bind(struct udevice *dev)
{
	struct cpu_platdata *plat = dev_get_parent_platdata(dev);

	plat->cpu_id = fdtdec_get_int(gd->fdt_blob, dev_of_offset(dev),
			"intel,apic-id", -1);

	return 0;
}

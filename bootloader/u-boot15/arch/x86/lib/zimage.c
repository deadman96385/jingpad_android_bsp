/*
 * Copyright (c) 2011 The Chromium OS Authors.
 * (C) Copyright 2002
 * Daniel Engström, Omicron Ceti AB, <daniel@omicron.se>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * Linux x86 zImage and bzImage loading
 *
 * based on the procdure described in
 * linux/Documentation/i386/boot.txt
 */

#include <common.h>
#include <android_bootimg.h>
#include <asm/cpu.h>
#include <asm/io.h>
#include <asm/ptrace.h>
#include <asm/zimage.h>
#include <asm/byteorder.h>
#include <asm/bootm.h>
#include <asm/bootparam.h>
#ifdef CONFIG_SYS_COREBOOT
#include <asm/arch/timestamp.h>
#endif
#include <linux/compiler.h>
#include <malloc.h>
#include <libfdt.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * Memory lay-out:
 *
 * relative to setup_base (which is 0x90000 currently)
 *
 *	0x0000-0x7FFF	Real mode kernel
 *	0x8000-0x8FFF	Stack and heap
 *	0x9000-0x90FF	Kernel command line
 */
#define COMMAND_LINE_OFFSET	0x9000
#define HEAP_END_OFFSET		0x8e00

#define COMMAND_LINE_SIZE	2048

/*
 * Install a default e820 table with 3 entries as follows:
 *
 *	0x000000-0x0a0000	Useable RAM
 *	0x0a0000-0x100000	Reserved for ISA
 *	0x100000-gd->ram_size	Useable RAM
 */
__weak unsigned install_e820_map(unsigned max_entries,
				 struct e820entry *entries)
{
	entries[0].addr = 0;
	entries[0].size = ISA_START_ADDRESS;
	entries[0].type = E820_RAM;
	entries[1].addr = ISA_START_ADDRESS;
	entries[1].size = ISA_END_ADDRESS - ISA_START_ADDRESS;
	entries[1].type = E820_RESERVED;
	entries[2].addr = ISA_END_ADDRESS;
	entries[2].size = gd->ram_size - ISA_END_ADDRESS;
	entries[2].type = E820_RAM;

	return 3;
}

static void build_command_line(char *command_line, int auto_boot)
{
	char *env_command_line;

	command_line[0] = '\0';

	env_command_line =  getenv("bootargs");
    if (!env_command_line) {
        printf("error: getenv(bootargs) return null\n");
        return;
    }

	/* set console= argument if we use a serial console */
	if (!strstr(env_command_line, "console=")) {
		if (!strcmp(getenv("stdout"), "serial")) {

			/* We seem to use serial console */
			sprintf(command_line, "console=ttyS0,%s ",
				getenv("baudrate"));
		}
	}

	if (auto_boot)
		strcat(command_line, "auto ");

    strcat(command_line, env_command_line);

	printf("Kernel command line: \"%s\"\n", command_line);
}

static int kernel_magic_ok(struct setup_header *hdr)
{
	if (KERNEL_MAGIC != hdr->boot_flag) {
		printf("Error: Invalid Boot Flag "
			"(found 0x%04x, expected 0x%04x)\n",
			hdr->boot_flag, KERNEL_MAGIC);
		return 0;
	} else {
		printf("Valid Boot Flag\n");
		return 1;
	}
}

static int get_boot_protocol(struct setup_header *hdr)
{
	if (hdr->header == KERNEL_V2_MAGIC) {
		printf("Magic signature found\n");
		return hdr->version;
	} else {
		/* Very old kernel */
		printf("Magic signature not found\n");
		return 0x0100;
	}
}

struct boot_params *load_zimage(uint32_t image_paddr, unsigned long kernel_size,
				uint64_t *load_addressp)
{
	ulong image_virt = 0;
	ulong address = (ulong) *load_addressp;
	ulong image_size;
	struct boot_params *setup_base;
	int setup_size;
	int bootproto;
	int big_image;
	int remapped = 0;
	int moving = 1;
	void *dest;

	if (image_paddr > 0xffffffff) {
		if (!cpu_has_64bit()) {
			printf("Error: kernel image is out of CPU address space\n");
		}
		/* map the setup data to 32-bit virtual address space */
		image_virt = (ulong)
			cpu_page_remap(CONFIG_IMAGE_VIRT_ADDR, 0x20000, image_paddr);

		cpu_paging_enable();
		remapped = 1;
	} else {
		image_virt = (ulong) image_paddr;
	}

	struct boot_params *params = (struct boot_params *) image_virt;
	struct setup_header *hdr = &params->hdr;

	/* base address for real-mode segment */
	setup_base = (struct boot_params *)DEFAULT_SETUP_BASE;

	if (!kernel_magic_ok(hdr)) {
		if (remapped) {
			cpu_paging_disable();
		}

		return 0;
	}

	/* determine size of setup */
	if (0 == hdr->setup_sects) {
		printf("Setup Sectors = 0 (defaulting to 4)\n");
		setup_size = 5 * 512;
	} else {
		setup_size = (hdr->setup_sects + 1) * 512;
	}

	printf("Setup Size = 0x%8.8lx\n", (ulong)setup_size);

	if (setup_size > SETUP_MAX_SIZE)
		printf("Error: Setup is too large (%d bytes)\n", setup_size);

	/* determine boot protocol version */
	bootproto = get_boot_protocol(hdr);

	printf("Using boot protocol version %x.%02x\n",
	       (bootproto & 0xff00) >> 8, bootproto & 0xff);

	if (bootproto >= 0x0200) {
		if (hdr->setup_sects >= 15) {
			printf("Linux kernel version %s\n",
				(char *)params +
				hdr->kernel_version + 0x200);
		} else {
			printf("Setup Sectors < 15 - "
				"Cannot print kernel version.\n");
		}
	}

	/* Determine image type */
	big_image = (bootproto >= 0x0200) &&
		    (hdr->loadflags & BIG_KERNEL_FLAG);

	/* Determine load address */
	if (big_image)
		*load_addressp = KERNEL_ADR;
	else
		*load_addressp = ZIMAGE_LOAD_ADDR;

#ifdef CONFIG_LOAD_ADDRESS_OVERRIDE
	*load_addressp = CONFIG_LOAD_ADDRESS;
	if (*load_addressp > 0xffffffff)
		remapped = 1;
#endif

	printf("Building boot_params at 0x%8.8lx\n", (ulong)setup_base);
	memset(setup_base, 0, sizeof(*setup_base));
	setup_base->hdr = params->hdr;

	if (bootproto >= 0x0204)
		kernel_size = hdr->syssize * 16;
	else
		kernel_size -= setup_size;

	if (bootproto == 0x0100) {
		/*
		 * A very old kernel MUST have its real-mode code
		 * loaded at 0x90000
		 */
		if ((u32)setup_base != 0x90000) {
			/* Copy the real-mode kernel */
			memmove((void *)0x90000, setup_base, setup_size);

			/* Copy the command line */
			memmove((void *)0x99000,
				(u8 *)setup_base + COMMAND_LINE_OFFSET,
				COMMAND_LINE_SIZE);

			 /* Relocated */
			setup_base = (struct boot_params *)0x90000;
		}

		/* It is recommended to clear memory up to the 32K mark */
		memset((u8 *)0x90000 + setup_size, 0,
		       SETUP_MAX_SIZE - setup_size);
	}

	if (big_image) {
		if (kernel_size > BZIMAGE_MAX_SIZE) {
			printf("Error: bzImage kernel too big! "
				"(size: %ld, max: %d)\n",
				kernel_size, BZIMAGE_MAX_SIZE);
			return 0;
		}
	} else if ((kernel_size) > ZIMAGE_MAX_SIZE) {
		printf("Error: zImage kernel too big! (size: %ld, max: %d)\n",
		       kernel_size, ZIMAGE_MAX_SIZE);
		return 0;
	}

	printf("Loading %s at address 0x%llx (%ld bytes)\n",
	       big_image ? "bzImage" : "zImage", *load_addressp, kernel_size);

	if (moving) {
		image_size = setup_size + kernel_size;
		if (remapped) {
			cpu_paging_disable();
			/* only setup data is mapped at this point */
			/* map the whole kernel image to 32-bit space */
			image_virt = cpu_page_remap(image_virt, image_size, image_paddr);
			address = cpu_page_remap(CONFIG_LOAD_VIRT_ADDR, kernel_size, *load_addressp);
			cpu_paging_enable();
		} else {
			image_virt = (ulong) image_paddr;
			address = (ulong) *load_addressp;
		}

		dest = (void *) address;
		memmove(dest, (void *) (image_virt + setup_size), kernel_size);
	}

	if (remapped) {
		cpu_paging_disable();
	}

	return setup_base;
}

int image_check64(struct boot_params *setup_base)
{
	struct setup_header *hdr = &setup_base->hdr;
	int bootproto = get_boot_protocol(hdr);

	if (bootproto < 0x020c)
		return 0;

	if (hdr->xloadflags & XLF_KERNEL_64)
		return 1;

	return 0;
}

int setup_zimage(struct boot_params *setup_base, char *cmd_line, int auto_boot,
		 unsigned long initrd_addr, unsigned long initrd_size)
{
	struct setup_header *hdr = &setup_base->hdr;
	int bootproto = get_boot_protocol(hdr);
#ifdef CONFIG_E820_AUTO_DETECT
	setup_base->e820_entries = install_e820_map_auto_detect(
		ARRAY_SIZE(setup_base->e820_map), setup_base->e820_map);
#else
	setup_base->e820_entries = install_e820_map(
		ARRAY_SIZE(setup_base->e820_map), setup_base->e820_map);
#endif
	void *fdt_blob = (u8*)DT_ADR;

	printf("Selected fdt_blob address 0x%x\n", fdt_blob);
	if (fdt_check_header(fdt_blob) < 0) {
		printf("Selected fdt_blob invalid, revert to default\n");
		fdt_blob = gd->fdt_blob;
	}

	/* if FDT then pass it to the kernel setup header */
	if (fdt_blob) {
		struct setup_data *sd;
		/* use setup_dtb_addr if defined */
		sd = DEFAULT_SETUP_DTB_ADDR;
		sd->next = 0;
		sd->type = SETUP_DTB;
		sd->len = fdt_totalsize(fdt_blob);
		memcpy(sd->data, fdt_blob, sd->len);
		/* we assume this is the only one setup_data entry */
		hdr->setup_data = (__u32)sd;
	}

	if (gd->arch.hardware_subarch)
		hdr->hardware_subarch = gd->arch.hardware_subarch;

	if (bootproto == 0x0100) {
		setup_base->screen_info.cl_magic = COMMAND_LINE_MAGIC;
		setup_base->screen_info.cl_offset = COMMAND_LINE_OFFSET;
	}
	if (bootproto >= 0x0200) {
		hdr->type_of_loader = 8;

		if (initrd_addr) {
			printf("Initial RAM disk at linear address "
			       "0x%08lx, size %ld bytes\n",
			       initrd_addr, initrd_size);

			hdr->ramdisk_image = initrd_addr;
			hdr->ramdisk_size = initrd_size;
		}
	}

	if (bootproto >= 0x0201) {
		hdr->heap_end_ptr = HEAP_END_OFFSET;
		hdr->loadflags |= HEAP_FLAG;
	}

	if (cmd_line) {
		if (bootproto >= 0x0202) {
			hdr->cmd_line_ptr = (uintptr_t)cmd_line;
		} else if (bootproto >= 0x0200) {
			setup_base->screen_info.cl_magic = COMMAND_LINE_MAGIC;
			setup_base->screen_info.cl_offset =
				(uintptr_t)cmd_line - (uintptr_t)setup_base;

			hdr->setup_move_size = 0x9100;
		}

		/* build command line at COMMAND_LINE_OFFSET */
		build_command_line(cmd_line, auto_boot);
	}

	return 0;
}

void setup_pcat_compatibility(void)
	__attribute__((weak, alias("__setup_pcat_compatibility")));

void __setup_pcat_compatibility(void)
{
}

int do_zboot(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	struct boot_params *base_ptr;
	struct boot_img_hdr *boot_hdr;
	uint32_t bzImage_addr = 0;
	uint64_t load_address = 0;
	char *s;
	ulong bzImage_size = 0;
	ulong initrd_addr = 0;
	ulong initrd_size = 0;
	ulong dtb_size = 0;
	uint32_t dt_img_adr = DT_ADR;
	int image_64bit = 0;


	disable_interrupts();

	/* Setup board for maximum PC/AT Compatibility */
	setup_pcat_compatibility();

	if (argc >= 2) {
		/* argv[1] holds the address of the bzImage */
		s = argv[1];
	} else {
		s = getenv("fileaddr");
	}

	if (s)
		bzImage_addr = simple_strtoull(s, NULL, 16);

	if (argc >= 3) {
		/* argv[2] holds the size of the bzImage */
		bzImage_size = simple_strtoul(argv[2], NULL, 16);
	}

	if (argc >= 4)
		initrd_addr = simple_strtoul(argv[3], NULL, 16);
	if (argc >= 5)
		initrd_size = simple_strtoul(argv[4], NULL, 16);
#ifdef CONFIG_VP_DEBUG
	boot_hdr = malloc(512*4);
	memcpy((void *)boot_hdr,(const void *)BOOTIMG_ADR,512*4);
	if (!memcmp(boot_hdr->magic, BOOT_MAGIC, BOOT_MAGIC_SIZE)) {
		bzImage_size = (boot_hdr->kernel_size + (KERNL_PAGE_SIZE-1))&(~(KERNL_PAGE_SIZE -1));
		initrd_size = (boot_hdr->ramdisk_size + (KERNL_PAGE_SIZE-1))&(~(KERNL_PAGE_SIZE -1));
		dtb_size = (boot_hdr->dt_size + (KERNL_PAGE_SIZE-1))&(~(KERNL_PAGE_SIZE -1));
		memcpy((void *)KERNEL_ADR,(const void *)BOOTIMG_ADR+512*4,bzImage_size);
		memcpy((void *)RAMDISK_ADR,(const void *)BOOTIMG_ADR+512*4+bzImage_size,initrd_size);
		memcpy((void *)DT_ADR,(const void *)BOOTIMG_ADR+512*4+bzImage_size+initrd_size,dtb_size);

		if(load_dtb((uint64_t) DT_ADR, dt_img_adr) < 0)
			printf("\nWARNING:load dtb from bootimg failed!\n");
		debugf("\nthe kernel is loading in the address:%x,size is %d\n",KERNEL_ADR,bzImage_size);
		debugf("\nthe ramdisk is loading in the address:%x,size is %d\n",RAMDISK_ADR,initrd_size);
		debugf("\nthe dtb is loading in the address:%x,size is %d\n",DT_ADR,dtb_size);
	}
	free(boot_hdr);
#endif
	/* Lets look for */
	base_ptr = load_zimage(bzImage_addr, bzImage_size, &load_address);

	if (!base_ptr) {
		puts("## Kernel loading failed ...\n");
		return -1;
	}
	if (setup_zimage(base_ptr, (char *)base_ptr + COMMAND_LINE_OFFSET,
			0, initrd_addr, initrd_size)) {
		puts("Setting up boot parameters failed ...\n");
		return -1;
	}

	image_64bit = image_check64(base_ptr);

	/* we assume that the kernel is in place */
	return boot_linux_kernel((ulong)base_ptr, load_address, image_64bit);
}

U_BOOT_CMD(
	zboot, 5, 0,	do_zboot,
	"Boot bzImage",
	"[addr] [size] [initrd addr] [initrd size]\n"
	"      addr -        The optional starting address of the bzimage.\n"
	"                    If not set it defaults to the environment\n"
	"                    variable \"fileaddr\".\n"
	"      size -        The optional size of the bzimage. Defaults to\n"
	"                    zero.\n"
	"      initrd addr - The address of the initrd image to use, if any.\n"
	"      initrd size - The size of the initrd image to use, if any.\n"
);

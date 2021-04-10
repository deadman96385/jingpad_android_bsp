/*
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")

OUTPUT_ARCH(arm)
//umctl_fpga.o           (.bss)
                dram_cfg_fpga.o      (.bss)
*/
OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
	. = 0x0000d000;

	. = ALIGN(8);
	.text :
	{
		init64.o (.text*)
		*(.text*)
	}

	. = ALIGN(8);
	.rodata : { *(.rodata*) }

	. = ALIGN(8);
	.data : { *(.data*) }

	. = ALIGN(8);
	. = . + 3k;
	. = 0x81000000;
	__bss0_start = .;
		.bss0 :
		{
			packet.o(.bss*)
		}
		__bss0_end = .;


	. = ALIGN(8);
	. = 0x00023000;
	__bss1_start = .;
		.bss1 :
		{
			*(.bss*)
		}
		__bss1_end = .;
	}

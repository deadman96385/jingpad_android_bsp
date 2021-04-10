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
	. = 0x0000a000;

	. = ALIGN(8);
	.text :
	{
		fdl_start.o (.text)
		*(.text)
	}

	. = ALIGN(8);
	.rodata : { *(.rodata) }

	. = ALIGN(8);
	.data : { *(.data) }

	. = ALIGN(8);
	. = . + 3k;
	__bss1_start = .;
	.bss1 :
	{ 
		*(.bss)
	}
        . = 0x0001f000;
	__bss1_end = .;
}

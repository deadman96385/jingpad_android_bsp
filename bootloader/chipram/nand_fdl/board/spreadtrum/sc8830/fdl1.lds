
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x50000000;

	. = ALIGN(4);
	.text :
	{
		fdl_start.o (.text)
		*(.text)
	}

	. = ALIGN(4);
	.rodata : { *(.rodata) }

	. = ALIGN(4);
	.data : { *(.data) }

	. = ALIGN(4);
       .fdl1_version : { *(.fdl1_version) }
       . = ALIGN(4);
	__bss0_start = .;
	.bss0 :
	{
		umctl.o           (.bss)
                dram_cfg.o      (.bss)
		adi.o	(.bss)
	}
	__bss0_end = .;

	. = 0x81000000;
	. = ALIGN(4);
	__bss1_start = .;
	.bss1 :
	{ 
		*(.bss)
	}
	__bss1_end = .;
}

OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS
{
	. = 0xFFFB0000;

	. = ALIGN(4);
	.text :
	{
		init.o (.text)
		*(.text)
	}

	. = ALIGN(4);
	.rodata : { *(.rodata) }

	. = ALIGN(4);
	.data : { *(.data) }

	. = ALIGN(4);
	__bss0_start = .;
	.bss0 :
	{
		umctl_28nm.o           (.bss)
                dram_cfg_28nm.o      (.bss)
		drv_usb.o 	(.bss)
		virtual_com.o 	(.bss)
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

OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS
{
	. = 0xFFFB0000;

	. = ALIGN(4);
	.text1 :
	{
		sec_start.o	(.text)
		sec_boot.o	(.text)
		sec_mcu.o	(.text)
	}

	. = 0xFFFB8000;
	. = ALIGN(4);
	.text2 :
	{
		*(.text)
	}

	. = ALIGN(4);
	.data : {
		*(.data)
	}

	. = ALIGN(4);
	.rel.dyn : {
		__rel_dyn_start = .;
		*(.rel*)
		__rel_dyn_end = .;
	}

	.dynsym : {
		__dynsym_start = .;
		*(.dynsym)
	}

	.bss : {
		__bss_start = .;
		*(.bss)
		 . = ALIGN(4);
		__bss_end = .;
	}

	/DISCARD/ : { *(.dynstr*) }
	/DISCARD/ : { *(.dynamic*) }
	/DISCARD/ : { *(.plt*) }
	/DISCARD/ : { *(.interp*) }
	/DISCARD/ : { *(.gnu*) }
}

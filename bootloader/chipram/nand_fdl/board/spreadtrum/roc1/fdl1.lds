OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
	. = 0x5700;

	. = ALIGN(8);
	.text :
	{
		FDL_STARTDIR/fdl_start.o (.text*)
		*(.text*)
	}

	. = ALIGN(8);
	.rodata : { *(.rodata*) }

	. = ALIGN(8);
	.data : { *(.data*) }

#if defined (_FDL_ROC1_HAPS_)
	. = ALIGN(8);
#else
	. = 0x20b10000;
	. = ALIGN(8);
#endif
	. = . + 3k;
	__bss0_start = .;
		.bss0 :
		{
			*(.bss*)
		}
		__bss0_end = .;


	. = ALIGN(8);
	__bss1_start = .;
		.bss1 :
		{
			*(.bss*)
		}
		__bss1_end = .;
	}

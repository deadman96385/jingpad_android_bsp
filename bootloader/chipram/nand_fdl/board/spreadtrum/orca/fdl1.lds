OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
	. = 0x28007200;

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

	. = ALIGN(8);
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

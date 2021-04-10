
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SECTIONS
{
	. = 0x50003000;

	. = ALIGN(4);
	.text :
	{
		sec_start_common.o	(.text)
		sec_boot.o (.text)
		. = ALIGN(256);
		init_sec.o (.text)
		*(.text)
	}

	. = ALIGN(4);
	.rodata : { *(.rodata) }

	. = ALIGN(4);
	.data : { *(.data) }

    . = 0x5000B000;
	. = ALIGN(4);
	__bss0_start = .;
	.bss0 :
	{
		adi.o	(.bss)
		dmc_sprd_r1p0.o	(.bss)
		dmc_sprd_r1p0_bist.o (.bss)
		dmc_sprd_misc.o	(.bss)
		lpddr2_cfg.o	(.bss)
		lpddr3_cfg.o	(.bss)
		dmc_pin_cfg.o	(.bss)
		ddr_scan_online_sprd_r1p0.o	(.bss)
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

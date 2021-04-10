/*
 * Copyright (C) 2015 Intel, Inc
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 */

#include <common.h>
#include <asm/e820.h>
#include <asm/post.h>
#include <fdtdec.h>
#include <chipram_env.h>

#include <asm/arch/sprd_reg.h>

#define E820_MAP_NAME "intel,e820_map"
#define E820_ITEMS "e820_map"

/* element array: addr(64), size(64), type(32)*/
#define E820_ITEM_SIZE (8 + 8 + 4)

#define U32_TO_U64(val1,val2)	(u64)((((u64)(val1))<<32)|((u64)(val2)))

ddr_info_t local_ddr_range;

#ifdef CONFIG_SPRD_SOC_SP9853I
static uint64_t real_ram_size_x86 = 0x80000000;
#endif

static unsigned install_e820_map_fdt(unsigned max_entries,
			struct e820entry *entries)
{
	int node, count, i;
	const void *array;

	node = fdt_node_offset_by_compatible(gd->fdt_blob, -1, E820_MAP_NAME);
	if (node < 0) {
		debug("%s, find %s fail: %d!\n", __func__, E820_MAP_NAME, node);
		return 0;
	}

	/* parse map list */
	array = fdt_getprop(gd->fdt_blob, node, E820_ITEMS, &count);
	count /= E820_ITEM_SIZE;
	count = min(count, (int)max_entries);

	for (i = 0; i < count; i++) {
		entries->addr = fdt64_to_cpu(*((uint64_t *)array));
		array += sizeof(uint64_t);
		entries->size = fdt64_to_cpu(*((uint64_t *)array));
		array += sizeof(uint64_t);
		entries->type = fdt32_to_cpu(*((uint32_t *)array));
		array += sizeof(uint32_t);

		entries++;
	}

	printf("%s, found %d e820 entries\n", __func__, count);
	return count;
}

unsigned install_e820_map(unsigned max_entries, struct e820entry *entries)
{
	u8 e820_entries = 0;

	e820_entries = install_e820_map_fdt(max_entries, entries);
	if (e820_entries)
		return e820_entries;

	printf("%s, !!!!!ERROR!!!!! found %d e820 entries in DTS file! \n", __func__, e820_entries);
	return e820_entries > max_entries ? max_entries : e820_entries;
}

void setup_chipram_ddr_range(void)
{
	ddr_info_t * env = CHIPRAM_DDR_RANGE_LOCATION;

	local_ddr_range = * env;

}

ddr_info_t* get_ddr_range(void)
{
	return &local_ddr_range;
}

unsigned install_e820_map_auto_detect(unsigned max_entries, struct e820entry *entries)
{
	extern ddr_info_t* get_ddr_range(void);
	u8 e820_entries_detect = 0;
	u8 e820_entries_dts = 0;
	int i=0;
	ddr_info_t* ddr_info = get_ddr_range();
	e820_entries_detect=ddr_info->section_number;
	/*the first part of ddr,may be reserved for vmm in vmm board*/
	e820_entries_dts = install_e820_map_fdt(max_entries, entries);
	entries = entries + e820_entries_dts;
	entries->addr = U32_TO_U64(ddr_info->sec_info[0].start_address_high,ddr_info->sec_info[0].start_address_low)+VMM_RESERVE_SIZE;
	entries->size  = U32_TO_U64(ddr_info->sec_info[0].end_address_high,ddr_info->sec_info[0].end_address_low)-entries->addr+0x1;
	entries->type  = E820_RAM;
	entries++;

	for (i = 1; i < e820_entries_detect; i++) {
		entries->addr = U32_TO_U64(ddr_info->sec_info[i].start_address_high,ddr_info->sec_info[i].start_address_low);
		entries->size  = U32_TO_U64(ddr_info->sec_info[i].end_address_high,ddr_info->sec_info[i].end_address_low)-entries->addr+0x1;
		entries->type  = E820_RAM;
		entries++;
	}
	return e820_entries_dts+e820_entries_detect;
}

int dram_init(void)
{
#ifdef CONFIG_SPRD_SOC_SP9853I
	u64 ddr_size = 0, start_addr;
	u8 e820_entries_detect = 0;
	int i = 0;
	setup_chipram_ddr_range();
	ddr_info_t* ddr_info = get_ddr_range();
	e820_entries_detect = ddr_info->section_number;

	for (i = 0; i < e820_entries_detect; i++) {
		start_addr = U32_TO_U64(ddr_info->sec_info[i].start_address_high,ddr_info->sec_info[i].start_address_low);
		ddr_size += U32_TO_U64(ddr_info->sec_info[i].end_address_high,ddr_info->sec_info[i].end_address_low)-start_addr+0x1;
	}
	real_ram_size_x86 = ddr_size - VMM_RESERVE_SIZE;
#endif

	gd->ram_size = PHYS_SDRAM_1_SIZE;
	post_code(POST_DRAM);

	return 0;
}

#ifdef CONFIG_SPRD_SOC_SP9853I
uint64_t get_real_ram_size_x86(void)
{
	return real_ram_size_x86;
}
#endif



void dram_init_banksize(void)
{
	gd->bd->bi_dram[0].start = 0; 
	gd->bd->bi_dram[0].size = PHYS_SDRAM_1_SIZE;

#ifdef CONFIG_SP9861_DDR4G
    #ifdef CONFIG_SP9861_DDR4G_SINGLE	/*single channel ddr 4g memory map*/
    	gd->bd->bi_dram[1].start = 0x40000000;
    	gd->bd->bi_dram[1].size  = PHYS_SDRAM_1_SIZE;

    	gd->bd->bi_dram[2].start = 0x80000000;
    	gd->bd->bi_dram[2].size  = PHYS_SDRAM_1_SIZE;

    	gd->bd->bi_dram[3].start = 0x100000000;
    	gd->bd->bi_dram[3].size  = PHYS_SDRAM_1_SIZE;
    #elif CONFIG_SP9861_DDR4G_INTERLEAVE	/*interleave memory map*/
    	gd->bd->bi_dram[1].start = 0x140000000; /*non interleave area for memdisk*/
    	gd->bd->bi_dram[1].size  = PHYS_SDRAM_1_SIZE;

    	gd->bd->bi_dram[2].start = 0x2C0000000;
    	gd->bd->bi_dram[2].size  = PHYS_SDRAM_1_SIZE;

    	gd->bd->bi_dram[3].start = 0x300000000;
    	gd->bd->bi_dram[3].size  = PHYS_SDRAM_1_SIZE;
    #else	/*noninterleave memory map*/
        gd->bd->bi_dram[1].start = 0x40000000;
        gd->bd->bi_dram[1].size  = PHYS_SDRAM_1_SIZE;

        gd->bd->bi_dram[2].start = 0x140000000;
        gd->bd->bi_dram[2].size  = PHYS_SDRAM_1_SIZE;

        gd->bd->bi_dram[3].start = 0x180000000;
        gd->bd->bi_dram[3].size  = PHYS_SDRAM_1_SIZE;
    #endif
#endif

#ifdef CONFIG_SP9853I_DDR4G
    gd->bd->bi_dram[1].start = 0x40000000;
    gd->bd->bi_dram[1].size  = PHYS_SDRAM_1_SIZE;

    gd->bd->bi_dram[2].start = 0x80000000;
    gd->bd->bi_dram[2].size  = PHYS_SDRAM_1_SIZE;

    gd->bd->bi_dram[3].start = 0x100000000;
    gd->bd->bi_dram[3].size  = PHYS_SDRAM_1_SIZE;
#endif
}

ulong board_get_usable_ram_top(ulong total_size)
{
	return gd->ram_size;
}

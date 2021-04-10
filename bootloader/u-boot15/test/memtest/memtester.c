#include <loader_common.h>
#include <chipram_env.h>

extern void reset_cpu (ulong ignored);
ulong sdram_base = CONFIG_SYS_SDRAM_BASE;
ulong ram_size;
#define TEST_LEN 0x100000
#define RAM256 0x20000000
extern void modem_entry(void);

void get_ddr_size(void)
{
#ifdef CONFIG_DDR_AUTO_DETECT
	ulong sdram_base = CONFIG_SYS_SDRAM_BASE;
	ulong sdram_size = 0;
	chipram_env_t * env = CHIPRAM_ENV_LOCATION;
	if (CHIPRAM_ENV_MAGIC != env->magic) {
		printf("Chipram magic wrong , ddr data may be broken\n");
		return 0;
	}

	ram_size = 0;

	if (env->cs_number == 1) {
		ram_size += env->cs0_size;
		debugf("dram cs0 size %x\n",env->cs0_size);
	} else if(env->cs_number == 2){
		ram_size += env->cs0_size;
		ram_size += env->cs1_size;
		debugf("dram cs0 size 0x%x dram cs1 size 0x%x\n",env->cs0_size, env->cs1_size);

	}
#else
	ram_size = REAL_SDRAM_SIZE;
#endif
}
/*
 *U-Boot code: 9F000000 -> 9F09BE60  BSS: -> 9F252028
 *TLB table from 9fff0000 to 9fff1000
 *Top of RAM usable for U-Boot at: 9fff0000
 *Reserving 5128k for malloc() at: 9faee000
 *Reserving 72 Bytes for Board Info at: 9faedfb8
 *Reserving 336 Bytes for Global Data at: 9faede68
 *Reserving 5984 Bytes for FDT at: 9faec708
 *New Stack Pointer is: 9faec700
 * */
void ddr_memtester(void)
{
	int i;
	printf("DDR mem test start\n");
	lcd_printf("DDR mem test start\n");
	get_ddr_size();
	//boot cp
	modem_entry();
	if (ram_size < RAM256)
	{
		ddr_mem_test(sdram_base, ram_size, TEST_LEN);
	}
	else
	{
		ddr_mem_test((sdram_base + RAM256), (ram_size - RAM256), TEST_LEN);
	}
	lcd_printf("DDR mem test pass\n");
	reset_cpu(0);
	while(1)
	{
		i = 1;
	}
}

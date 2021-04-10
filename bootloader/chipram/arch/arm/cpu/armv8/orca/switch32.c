#include "config.h"
#include <asm/arch/sprd_reg.h>
#include "armv8_switch.h"
/*
 * never return
 * */
int switch_to_aarch32(void)
{
	arm_secure_state_switch(SECURE_STATE);
	arm_spsr_set(TYPE_SVC | EXECUTE_STATE_AARCH32);
	arm_elr_set(CONFIG_SYS_NAND_U_BOOT_DST);
	arm_eret_1();

	return 0;
}

int do_board_func(void)
{
	switch_to_aarch32();
	return 0;
}

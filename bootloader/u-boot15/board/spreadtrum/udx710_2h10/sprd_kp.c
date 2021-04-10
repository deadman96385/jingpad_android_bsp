#include <common.h>
#include <malloc.h>
#include "key_map.h"
#include <boot_mode.h>
#include <asm/arch/mfp.h>
#include <asm/arch/common.h>
#include <asm/arch/sprd_eic.h>

void board_keypad_init(void)
{
}

unsigned char board_key_scan(void)
{
	return KEY_RESERVED;
}

unsigned int check_key_boot(unsigned char key)
{
      return 0;
}


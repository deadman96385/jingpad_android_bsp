#include <config.h>
#include <sci_types.h>

/**********keypad registe for boot moder************/
#define KEYPAD_BASE                              0x40250000
#define KEYPAD_INT_RAW_STATUS                    (KEYPAD_BASE + 0x08)
#define KEYPAD_STATUS                         	 (KEYPAD_BASE + 0x2C)

/******************judge the boot mode**************/
PUBLIC BOOLEAN isSDCardBoot(void)
{
	uint32 s_keypad_raw_status = 0;
	uint32 s_keypad_status = 0;

	SDIO_Mdelay(20);

	s_keypad_raw_status = *(volatile uint32 *)(KEYPAD_INT_RAW_STATUS);
	s_keypad_status = *(volatile uint32 *)(KEYPAD_STATUS);

	if (((s_keypad_raw_status & 0x03) == 0x03) && (((s_keypad_status & 0x7777) == 0x0001) || ((s_keypad_status & 0x7777) == 0x0100))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

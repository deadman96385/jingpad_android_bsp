#include <common.h>
#include <linux/input.h>
#include <linux/kernel.h>
#include <boot_mode.h>
#include <asm/arch/common.h>
#include <asm/arch/sprd_eic.h>

#include <sprd_kp.h>

/* TODO:
 * modify keys here for different board
 * an empty key_info must be at the end
 */
static struct key_info KEYS[] = {
	{
		.tag = "Volume Up",
		.offset = SPRD_DDIE_EIC_EXTINT3,
		.type = TYPE_EIC,
		.keycode = KEY_VOLUMEUP,
		.active = 0,
	},
	{
		.tag = "Volume Down",
		.offset = 2, // TODO: refer to sprd_eic.h for EIC name
		.type = TYPE_EIC,
		.keycode = KEY_VOLUMEDOWN,
		.active = 0,
	},
	{
		.keycode = KEY_RESERVED,
	}
};

DEFAULT_SPRD_KEYPAD_FUNC(KEYS);
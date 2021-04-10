#include <common.h>
#include <linux/input.h>
#include <linux/kernel.h>
#include <boot_mode.h>
#include <asm/arch/common.h>
#include <asm/arch/sprd_eic.h>


enum key_type {
	TYPE_EIC,
	TYPE_GPIO,
};

struct key_info {
	const char *tag;
	const uint32_t offset;
	const uint32_t type;
	const uint32_t keycode;
	const uint32_t active;
};

/* TODO: modify keys here for different board */
static struct key_info KEYS[] = {
	{
		.tag = "Volume Up",
		.offset = EIC_KEY2_7S_RST_EXT_RSTN_ACTIVE,
		.type = TYPE_EIC,
		.keycode = KEY_VOLUMEUP,
		.active = 1,
	},
	{
		.tag = "Volume Down",
		.offset = SPRD_DDIE_EIC_KEYIN0,
		.type = TYPE_EIC,
		.keycode = KEY_VOLUMEDOWN,
		.active = 0,
	},
};

#if defined(CONFIG_FPGA)
void board_keypad_init(void)
{
}
#else
void board_keypad_init(void)
{
	uint32_t i;

	for (i = 0; i < ARRAY_SIZE(KEYS); i++) {
		if (KEYS[i].type == TYPE_GPIO) {
			sprd_gpio_request(NULL, KEYS[i].offset);
			/* a GPIO pin for key is always used as INPUT pin */
			sprd_gpio_direction_input(NULL, KEYS[i].offset);
		}
	}

	printf("[KEY] init!\n");
}
#endif

#if defined(CONFIG_FPGA)
unsigned char board_key_scan(void)
{
	return KEY_RESERVED;
}
#else
unsigned char board_key_scan(void)
{
	uint32_t i, keycode = KEY_RESERVED;
	int val = 0;

	/* TODO: high or low */
	for (i = 0; i < ARRAY_SIZE(KEYS); i++) {
		if (KEYS[i].type == TYPE_GPIO) {
			val = sprd_gpio_get(NULL, KEYS[i].offset);
		} else if (KEYS[i].type == TYPE_EIC) {
			sprd_eic_request(KEYS[i].offset);
			udelay(3000);
			val = sprd_eic_get(KEYS[i].offset);
		}
		debugf("[KEYS] i=%d, value=%d\n", i, val);
		if (val < 0) {
			errorf("[KEY] fail to get value for %s!", KEYS[i].tag);
			continue;
		}
		if (!!val == KEYS[i].active)
			break;
	}

	if (i == ARRAY_SIZE(KEYS)) {
		printf("[KEY] no key pressed!\n");
	} else {
		printf("[KEY] %s pressed!\n", KEYS[i].tag);
		keycode = KEYS[i].keycode;
	}

	return keycode;
}
#endif

unsigned int check_key_boot(unsigned char key)
{
	if(KEY_VOLUMEUP == key)
		return CMD_FACTORYTEST_MODE;
	else if(KEY_HOME == key)
		return CMD_FASTBOOT_MODE;
	else if(KEY_VOLUMEDOWN== key)
		return CMD_RECOVERY_MODE;
	else
		return 0;
}

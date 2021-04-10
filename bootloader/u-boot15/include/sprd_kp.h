#ifndef __SPRD_KP_H__
#define __SPRD_KP_H__

#include <linux/input.h>

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

#if defined(CONFIG_FPGA)
static inline void sprd_kp_init(struct key_info *keys)
{
}
static inline unsigned char sprd_kp_scan(struct key_info *keys)
{
	return KEY_RESERVED;
}
#else
void sprd_kp_init(struct key_info *keys);
unsigned char sprd_kp_scan(struct key_info *keys);
#endif
unsigned int sprd_kp_checkmode(unsigned char keycode);

/* use this MACRO to quickly define keypad function
 * define your own keypad function if you have some special feature */
#define DEFAULT_SPRD_KEYPAD_FUNC(KEYS) \
void board_keypad_init(void) { sprd_kp_init(KEYS); } \
unsigned char board_key_scan(void) { return sprd_kp_scan(KEYS); } \
unsigned int check_key_boot(unsigned char key) {\
	return sprd_kp_checkmode(key);\
}

#endif

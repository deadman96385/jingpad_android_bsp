#ifndef _KEY_MAP_H_
#define _KEY_MAP_H_

#include <linux/input.h>

static unsigned char board_key_map[]={
#if 0
    0x27, KEY_HOME,
    0x42, KEY_BACK,
    0x41, KEY_VOLUMEUP,
#else
//    0x00, KEY_BACK,//DOWN
    0x01, KEY_HOME,//CAM
//    0x10, KEY_MENU,//UP
#endif
    0x10, KEY_VOLUMEUP,
    0x00, KEY_VOLUMEDOWN,
};

#define CONFIG_KEYPAD_ROW_CNT 5
#define CONFIG_KEYPAD_COL_CNT 5
#define CONFIG_KEYPAD_LONG_CNT 0xc
#define CONFIG_KEYPAD_DEBOUNCE_CNT 0x5
#endif //_KEY_MAP_H_

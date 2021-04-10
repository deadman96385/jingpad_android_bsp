#ifndef __SPRD_LED_H__
#define __SPRD_LED_H__

#include <common.h>

#define BRIGHTNESS_MAX (255)

typedef enum {
	Red,
	Green,
	Blue,
} LedType;

void sprd_led_init(void);
void sprd_led_set_brightness(LedType type, uint32_t brightness);
void sprd_led_disable(LedType type);
void sprd_led_pattern_clear(LedType type);
void sprd_led_pattern_set(LedType type, uint32_t brightness);

#endif

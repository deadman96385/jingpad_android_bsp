#include <loader_common.h>
#include <boot_mode.h>
#include <sprd_led.h>

#ifdef CONFIG_CHG_LED
void sprdbat_chg_led(int on)
{
	if(on)
		sprd_led_set_brightness(Red, 255);
	else {
		sprd_led_set_brightness(Red, 0);
		sprd_led_disable(Red);
	}
}
#else
void sprdbat_chg_led(int on){};
#endif

#ifdef CONFIG_SHOW_CHGLOGO
#define CHG_LOGO_TIME 15
void sprdbat_show_chglogo(void)
{
	static int lcd_on = 0;
	static int on_cnt = 0;
	static int init_flag = 0;
	extern int drv_lcd_init (void);
	extern void lcd_enable(void);

	if (!init_flag) {
		init_flag = 1;
		lcd_on = 1;
		on_cnt = CHG_LOGO_TIME;
		drv_lcd_init();
		lcd_splash(CHARGER_LOGO_PART);
		lcd_enable();
		set_backlight(BACKLIGHT_ON);
		sprdbat_chg_led(1);
	}

	if (on_cnt > 0)
		on_cnt--;

	if (!power_button_pressed()) {
		printf("power key pressed show chg logo\n");
		on_cnt = CHG_LOGO_TIME;
	}

	if (on_cnt > 0) {
		if(!lcd_on) {
			set_backlight(BACKLIGHT_ON);
			lcd_on = 1;
		}
	} else {
		if(lcd_on) {
			set_backlight(BACKLIGHT_OFF);
			lcd_on = 0;
		}
	}
}
#else
void sprdbat_show_chglogo(void)
{
	static int init_flag = 0;

	if (!init_flag) {
		init_flag = 1;
		sprdbat_chg_led(1);
	}
}
#endif


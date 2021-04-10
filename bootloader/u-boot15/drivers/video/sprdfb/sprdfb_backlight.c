/*
 * (C) Copyright 2014
 *
 *  yaochuan.li@spreadtrum.com
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include "sprdfb_chip_common.h"
#include "sprdfb.h"

#define WHTLED_CTL              ANA_LED_CTL
#define WHTLED_PD_SET           BIT_0
#define WHTLED_PD_RST           BIT_1
#define WHTLED_V_SHIFT          2
#define WHTLED_V_MSK            (0x1F << WHTLED_V_SHIFT)

#if 0
static void LCD_SetPwmRatio(unsigned short value)
{
#if defined CONFIG_SC8830 || (defined CONFIG_SC9630)
	// to do
#else
	__raw_bits_or(CLK_PWM0_EN, GR_CLK_EN);
	__raw_bits_or(CLK_PWM0_SEL, GR_CLK_EN);
	__raw_bits_or(PIN_PWM0_MOD_VALUE, CPC_LCD_PWM_REG);
	__raw_writel(LCD_PWM_PRESCALE_VALUE, SPRD_PWM0_PRESCALE);
	__raw_writel(value, SPRD_PWM0_CNT);
	__raw_writel(PWM_REG_MSK_VALUE, SPRD_PWM0_PAT_LOW);
	__raw_writel(PWM_REG_MSK_VALUE, SPRD_PWM0_PAT_HIG);
	__raw_bits_or(LCD_PWM0_EN, SPRD_PWM0_PRESCALE);
#endif
}

void LCD_SetBackLightBrightness( unsigned long  value)
{
	unsigned long duty_mod= 0;
	if(value > LCD_PWM_MOD_VALUE)
		value = LCD_PWM_MOD_VALUE;

/*
	if(value < 0)
		value = 0;
*/

	duty_mod = (value << 8) | LCD_PWM_MOD_VALUE;
	LCD_SetPwmRatio(duty_mod);
}

static uint32 get_adie_chipid(void)
{
       uint32 chip_id;
       chip_id = (ANA_REG_GET(ANA_REG_GLB_CHIP_ID_HIGH) & 0xffff) << 16;
       chip_id |= ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW) & 0xffff;
       return chip_id;
}

void sprd_white_led_init(void)
{
	__raw_writel(0xc000,0x400388d8);

	__raw_writel(0x0100,0x40038020);
	__raw_writel(0xffff,0x40038024);
	__raw_writel(0xffff,0x4003802c);
	__raw_writel(0xffff,0x40038030);

	__raw_writel(0x0100,0x40038020);

	__raw_writel(0x0081,0x400388d4);
//	__raw_writel(0xff80,0x400388d8);
}
#endif

void set_backlight(uint32_t value)
{
#if 0
#if (defined(CONFIG_SP8830GGA) || \
	defined(CONFIG_SP8830GEA) || \
	defined(CONFIG_SP7730GGA) || \
	defined(CONFIG_SC9620OPENPHONE))

	/*backlight is driven by PWMD (PWMD=PWM3) */
	__raw_bits_or((0x1 << 0), 0x402d0044);//use ext_26m for clk_pwm3 parent clk
	if(0 == value) {
		__raw_writel(0x0000, 0x40260060);
		printf("sprd backlight power off. brightness = %d (use PWM3 for external backlight control)\n", value);
	} else {
		value = (value & 0xff) >> 2;
		/*enbale pwm3*/
		__raw_bits_or((0x1 << 7), 0x402e0000);
		/*config pwm3*/
		__raw_writel((value << 8) | 0xff, 0x40260064);
		__raw_writel(0xffff, 0x4026006c);
		__raw_writel(0xffff, 0x40260070);
		__raw_writel(0x0100, 0x40260060);
		printf("sprd backlight power on. brightness = %d (use PWM3 for external backlight control)\n", value);
	}

#endif

#if (defined(CONFIG_SP8830) || defined(CONFIG_SPX15))

int white_led = 0;
#if (defined(CONFIG_SPX15))
	#if (defined(CONFIG_EMMC_BOOT))
		uint32 chip_id;
		chip_id = get_adie_chipid();
		printf("adie chip id: 0x%08X\n", chip_id);
		if(0x2711A000 == chip_id) {
			white_led = 1;
			printf("CONFIG_EMMC_BOOT is set, and the adie chip id is 0x2711A000, therefore, white_led=1\n");
		}
		else {
			white_led = 0;
			printf("CONFIG_EMMC_BOOT is set, but the adie chip id is NOT 0x2711A000, therefore, white_led=0\n");
		}
	#else
		white_led = 0;
		printf("CONFIG_EMMC_BOOT is NOT set, therefore, white_led=0\n");
	#endif
#else
	white_led = 1;
	printf("CONFIG_SP8830 is set and CONFIG_SPX15 is NOT set, therefore, white_led=1\n");
#endif

#if (defined(CONFIG_SPX15))
	if(1 == white_led) {
		/*backlight is driven by whiteled */
		sprd_white_led_init();
		if (value == 0) {
			ANA_REG_SET(0x400388d4,0);
			printf("sprd backlight power off (SPX15 use WHITE_LED backlight control)\n");
		} else {
			__raw_writel(0x0181,0x400388d4);
			__raw_writel(0x0480,0x400388d8);
			printf("sprd backlight power on (SPX15 use WHITE_LED backlight control)\n");
		}
	//============================================both white led and pwm
		{
			/*backlight is driven by PWMC (PWMC=PWM2) */
			__raw_bits_or((0x1 << 0), 0x402d0040);//use ext_26m for clk_pwm2 parent clk
			if(0 == value) {
				__raw_writel(0x0000, 0x40260040);
				printf("sprd backlight power off (SPX15 use PWM2 for external backlight control)\n");
			}
			else {
				value = (value & 0xff) >> 2;
				/*enbale pwm2*/
				__raw_bits_or((0x1 << 6), 0x402e0000);
				/*config pwm2*/
				__raw_writel((value << 8) | 0xff, 0x40260044);
				__raw_writel(0xffff, 0x4026004c);
				__raw_writel(0xffff, 0x40260050);
				__raw_writel(0x0100, 0x40260040);
				printf("sprd backlight power on (SPX15 use PWM2 for external backlight control)\n");
			}
		}
	//============================================both white led and pwm
	}
	else {
		/*backlight is driven by PWMC (PWMC=PWM2) */
		__raw_bits_or((0x1 << 0), 0x402d0040);//use ext_26m for clk_pwm2 parent clk
		if(0 == value) {
			__raw_writel(0x0000, 0x40260040);
			printf("sprd backlight power off (SPX15 use PWM2 for external backlight control)\n");
		}
		else {
			value = (value & 0xff) >> 2;
			/*enbale pwm2*/
			__raw_bits_or((0x1 << 6), 0x402e0000);
			/*config pwm2*/
			__raw_writel((value << 8) | 0xff, 0x40260044);
			__raw_writel(0xffff, 0x4026004c);
			__raw_writel(0xffff, 0x40260050);
			__raw_writel(0x0100, 0x40260040);
			printf("sprd backlight power on (SPX15 use PWM2 for external backlight control)\n");
		}
	}
#else
	/*backlight is driven by whiteled */
	if (value == 0) {
		ANA_REG_SET(0x40038894,0);
		printf("sprd backlight power off (SP8830 use WHITE_LED backlight control)\n");
	} else {
		ANA_REG_SET(0x40038894,(ANA_REG_GET(0x40038894)|(0x3 << 7)));
		printf("sprd backlight power on (SP8830 use WHITE_LED backlight control)\n");
	}
#endif

#elif defined(CONFIG_KANAS_W) || defined(CONFIG_KANAS_TD)
	FB_PRINT("set_backlight\n");
	/* GPIO214 */
#define BACKLIGHT_GPIO 214
	static int is_init = 0;

	if (!is_init) {
		sprd_gpio_request(NULL, BACKLIGHT_GPIO);
		sprd_gpio_direction_output(NULL, BACKLIGHT_GPIO, 0);
		is_init = 1;
	}

	if (0 == value) {
		sprd_gpio_set(NULL, BACKLIGHT_GPIO, 0);
	}
	else {
		sprd_gpio_set(NULL, BACKLIGHT_GPIO, 1);
	}
#endif

#if defined (CONFIG_POCKET2) || defined (CONFIG_CORSICA_VE) ||defined (CONFIG_VIVALTO) || defined (CONFIG_YOUNG2)
	FB_PRINT("sprdfb: [%s] turn on the backlight\n", __FUNCTION__);

	sprd_gpio_request(NULL, 190);
	sprd_gpio_direction_output(NULL, 190, 0);
	if(0 == value){
		sprd_gpio_set(NULL, 190, 0);
	}else
	{
	    sprd_gpio_set(NULL, 190, 1);
	}
#endif
#if defined (CONFIG_SP8825) || defined (CONFIG_SP8825EA) || defined (CONFIG_SP8825EB) ||defined(CONFIG_GARDA)
	__raw_writel(0x101, 0x4C000138);
	__raw_bits_or((1<<5), 0x4B000008);
	__raw_bits_or((1<<8), 0x4A000384);
	__raw_bits_or((1<<8), 0x4A000388);
	__raw_bits_or((1<<8), 0x4A000380);
#endif


#ifdef CONFIG_SC8810_OPENPHONE
	ANA_REG_AND(WHTLED_CTL, ~(WHTLED_PD_SET | WHTLED_PD_RST));
	ANA_REG_OR(WHTLED_CTL,  WHTLED_PD_RST);
	ANA_REG_MSK_OR (WHTLED_CTL, ( (value << WHTLED_V_SHIFT) &WHTLED_V_MSK), WHTLED_V_MSK);
#elif CONFIG_MACH_CORI
	__raw_bits_or((1<<5),  0x8B000008);
	__raw_bits_or((1<<10), 0x8A000384);
	__raw_bits_or((1<<10), 0x8A000388);
	__raw_bits_or((1<<10), 0x8A000380);
#else
	//if (gpio_request(143, "LCD_BL")) {
	//	FB_PRINT("Failed ro request LCD_BL GPIO_%d \n",
	//		143);
	//	return -ENODEV;
	//}
	//gpio_direction_output(143, 1);
	//gpio_set_value(143, 1);
	//__raw_bits_or((1<<5),  0x8B000008);
	//__raw_bits_or((1<<15), 0x8A000384);
	//__raw_bits_or((1<<15), 0x8A000388);
	//__raw_bits_or((1<<15), 0x8A000380);
#ifndef CONFIG_SP8810EA
	LCD_SetBackLightBrightness(value);
#else
	__raw_writel(0x101, 0x8C0003e0);
	__raw_bits_or((1<<5),  0x8B000008);
	__raw_bits_or((1<<15), 0x8A000384);
	__raw_bits_or((1<<15), 0x8A000388);
	__raw_bits_or((1<<15), 0x8A000380);
#endif

#endif
#endif
}

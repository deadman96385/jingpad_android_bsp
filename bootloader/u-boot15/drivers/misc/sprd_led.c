#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>
#include <sprd_led.h>

#define ANA_BLTC_CTRL     SCI_ADDR(ANA_BLTC_BASE, 0x0000)

#define ANA_BLTC_R_DUTY   SCI_ADDR(ANA_BLTC_BASE, 0x0008)
#define ANA_BLTC_R_CURVE0 SCI_ADDR(ANA_BLTC_BASE, 0x000c)
#define ANA_BLTC_R_CURVE1 SCI_ADDR(ANA_BLTC_BASE, 0x0010)

#define ANA_BLTC_G_DUTY   SCI_ADDR(ANA_BLTC_BASE, 0x0018)
#define ANA_BLTC_G_CURVE0 SCI_ADDR(ANA_BLTC_BASE, 0x001c)
#define ANA_BLTC_G_CURVE1 SCI_ADDR(ANA_BLTC_BASE, 0x0020)

#define ANA_BLTC_B_DUTY   SCI_ADDR(ANA_BLTC_BASE, 0x0028)
#define ANA_BLTC_B_CURVE0 SCI_ADDR(ANA_BLTC_BASE, 0x002c)
#define ANA_BLTC_B_CURVE1 SCI_ADDR(ANA_BLTC_BASE, 0x0030)

#define ANA_BLTC_STS      SCI_ADDR(ANA_BLTC_BASE, 0x0034)

#define BLTC_EN          BIT(9)
#define RTC_BLTC_EN      BIT(7)
#define RGB_PD_SW        BIT(0)
#define RGB_V            (0x1f0)
#define WHTLED_PD        BIT(0)
#define WHTLED_SERIES_EN BIT(8)
#define R_RUN            BIT(0)
#define R_TYPE           BIT(1)
#define G_RUN            BIT(4)
#define G_TYPE           BIT(5)
#define B_RUN            BIT(8)
#define B_TYPE           BIT(9)
#define RGB_CURRENT_MASK (0x3F)  /*for sc2720*/
#define RGB_CURRENT_V (0x02)  /*for sc2720, mA:1.68+0.84*n*/
#define SC2730_RGB_PD_SW BIT(12)
#define SC2730_RGB_HW_PD BIT(13)
#define SC2730_RGB_V     (0xf8)

#define SPRD_LED_RISING   1
#define SPRD_LED_FALLING  1
#define SPRD_LED_HIGH     2
#define SPRD_LED_LOW      3

#ifdef CONFIG_NONE_LED

void sprd_led_init(void) {}
void sprd_led_disable(LedType type) {}
void sprd_led_set_brightness(LedType type, uint32_t brightness) {}
void sprd_led_pattern_clear(LedType type) {}
void sprd_led_pattern_set(LedType type, uint32_t brightness) {}

#else

static uint32_t init = 0;

void sprd_led_init(void)
{
#if defined(CONFIG_ADIE_SC2731)
	ANA_REG_OR(ANA_REG_GLB_MODULE_EN0, BLTC_EN);
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN0, RTC_BLTC_EN);
	ANA_REG_BIC(ANA_REG_GLB_RGB_CTRL, RGB_PD_SW);
	ANA_REG_BIC(ANA_REG_GLB_RGB_CTRL, RGB_V);
	ANA_REG_OR(ANA_REG_GLB_WHTLED_CTRL, WHTLED_PD);
	ANA_REG_OR(ANA_REG_GLB_WHTLED_CTRL, WHTLED_SERIES_EN);

#elif defined(CONFIG_ADIE_SC2730)
	ANA_REG_OR(ANA_REG_GLB_MODULE_EN0, BLTC_EN);
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN0, RTC_BLTC_EN);
	ANA_REG_BIC(ANA_BLTC_CTRL, SC2730_RGB_PD_SW);
	ANA_REG_BIC(ANA_BLTC_CTRL, SC2730_RGB_HW_PD);
	ANA_REG_BIC(ANA_BLTC_STS, SC2730_RGB_V);

#elif defined(CONFIG_ADIE_SC2721)
	ANA_REG_OR(ANA_REG_GLB_MODULE_EN0, BLTC_EN);
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN0, RTC_BLTC_EN);
	ANA_REG_BIC(ANA_REG_GLB_RGB_CTRL, RGB_PD_SW);
	ANA_REG_BIC(ANA_REG_GLB_RGB_CTRL, RGB_V);

#elif defined(CONFIG_ADIE_SC2720)
	ANA_REG_OR(ANA_REG_GLB_MODULE_EN0, BLTC_EN);
	ANA_REG_OR(ANA_REG_GLB_RTC_CLK_EN0, RTC_BLTC_EN);
	ANA_REG_BIC(ANA_REG_GLB_RGB_CTRL, RGB_PD_SW);
	ANA_REG_BIC(ANA_REG_GLB_SOFT_RST0, BIT_BLTC_SOFT_RST);
	/*current*/
	ANA_REG_MSK_OR(ANA_BLTC_BASE+0x38, RGB_CURRENT_V, RGB_CURRENT_MASK);
	ANA_REG_MSK_OR(ANA_BLTC_BASE+0x3C, RGB_CURRENT_V, RGB_CURRENT_MASK);
	ANA_REG_MSK_OR(ANA_BLTC_BASE+0x40, RGB_CURRENT_V, RGB_CURRENT_MASK);

#endif
	printf("[LED] init led]");
	init = 1;
}

void sprd_led_disable(LedType type)
{

	uint32_t bits;

	if (!init)
		return;

	switch (type) {
	case Red:
		bits = R_RUN | R_TYPE;
		break;
	case Green:
		bits = G_RUN | G_TYPE;
		break;
	case Blue:
		bits = B_RUN | B_TYPE;
		break;
	default:
		break;
	}

	ANA_REG_BIC(ANA_BLTC_CTRL, bits);
	printf("[LED] disable led, type=%d\n", type);
}

void sprd_led_set_brightness(LedType type, uint32_t brightness)
{
	uint32_t bits, reg;

	if (!init)
		return;

	if (brightness > BRIGHTNESS_MAX)
		brightness = BRIGHTNESS_MAX;

	switch (type) {
	case Red:
		bits = R_RUN | R_TYPE;
		reg = ANA_BLTC_R_DUTY;
		break;
	case Green:
		bits = G_RUN | G_TYPE;
		reg = ANA_BLTC_G_DUTY;
		break;
	case Blue:
		bits = B_RUN | B_TYPE;
		reg = ANA_BLTC_B_DUTY;
		break;
	default:
		break;
	}

	ANA_REG_OR(ANA_BLTC_CTRL, bits);
	ANA_REG_MSK_OR(reg, (brightness << 8) | 0xFF, 0xFFFF);
	printf("[LED] set brightness, type=%d, brightness=%u\n", type, brightness);
}

void sprd_led_pattern_clear(LedType type)
{
	uint32_t bits, curve0_reg, curve1_reg;

	if (!init)
		return;

	switch (type) {
	case Red:
		bits = R_RUN | R_TYPE;
		curve0_reg = ANA_BLTC_R_CURVE0;
		curve1_reg = ANA_BLTC_R_CURVE1;
		break;
	case Green:
		bits = G_RUN | G_TYPE;
		curve0_reg = ANA_BLTC_G_CURVE0;
		curve1_reg = ANA_BLTC_G_CURVE1;
		break;
	case Blue:
		bits = B_RUN | B_TYPE;
		curve0_reg = ANA_BLTC_B_CURVE0;
		curve1_reg = ANA_BLTC_B_CURVE1;
		break;
	default:
		break;
	}

	ANA_REG_OR(curve0_reg, 0);
	ANA_REG_OR(curve1_reg, 0);
	ANA_REG_BIC(ANA_BLTC_CTRL, bits);
	printf("[LED] pattern clear, type=%d\n", type);

}

void sprd_led_pattern_set(LedType type, uint32_t brightness)
{
	uint32_t bits, curve0_reg, curve1_reg, reg;

	if (!init)
		return;

	switch (type) {
	case Red:
		bits = R_RUN ;
		curve0_reg = ANA_BLTC_R_CURVE0;
		curve1_reg = ANA_BLTC_R_CURVE1;
		reg = ANA_BLTC_R_DUTY;
		break;
	case Green:
		bits = G_RUN;
		curve0_reg = ANA_BLTC_G_CURVE0;
		curve1_reg = ANA_BLTC_G_CURVE1;
		reg = ANA_BLTC_G_DUTY;
		break;
	case Blue:
		bits = B_RUN;
		curve0_reg = ANA_BLTC_B_CURVE0;
		curve1_reg = ANA_BLTC_B_CURVE1;
		reg = ANA_BLTC_B_DUTY;
		break;
	default:
		break;
	}
	sprd_led_pattern_clear(type);
	ANA_REG_OR(curve0_reg, (SPRD_LED_FALLING << 8) | SPRD_LED_RISING);
	ANA_REG_OR(curve1_reg, (SPRD_LED_LOW << 8) | SPRD_LED_HIGH);
	ANA_REG_OR(reg, (brightness << 8) | 0xFF);
	ANA_REG_OR(ANA_BLTC_CTRL, bits);
	printf("[LED] pattern set, type=%d, brightness=%d, rising=%d, high=%d, falling=%d, low=%d\n",
	       type, brightness,SPRD_LED_RISING,SPRD_LED_HIGH,SPRD_LED_FALLING,SPRD_LED_LOW);

}

#endif

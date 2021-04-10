#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>


#ifndef CONFIG_BACKLIGHT_WHTLED
#define PWM_INDEX  1

/*r3p0*/

#define PWM_PRESCALE	(0x0000)
#define PWM_MOD		(0x0004)
#define PWM_DUTY		(0x0008)
#define PWM_DIV			(0x000c)
#define PWM_PAT_LOW	(0x0010)
#define PWM_PAT_HIGH	(0x0014)
#define PWM_ENABLE 	(0x0018)
#define PWM_VERSION	(0x001c)

#define PWM2_SCALE		0x0
#define PWM_MOD_MAX 0xff
#define PWM_REG_MSK 0xffff

#else

#define REG_BLTC_BASE           0x40388180
#define REG_BLTC_R_PRESCL       (REG_BLTC_BASE + 0x004)
#define REG_BLTC_R_DUTY         (REG_BLTC_BASE + 0x008)
#define REG_BLTC_R_CURVE0       (REG_BLTC_BASE + 0x00C)
#define REG_BLTC_R_CURVE1       (REG_BLTC_BASE + 0x010)
#define REG_BLTC_G_PRESCL       (REG_BLTC_BASE + 0x014)
#define REG_BLTC_G_DUTY         (REG_BLTC_BASE + 0x018)
#define REG_BLTC_G_CURVE0       (REG_BLTC_BASE + 0x01C)
#define REG_BLTC_G_CURVE1       (REG_BLTC_BASE + 0x020)
#define REG_BLTC_B_PRESCL       (REG_BLTC_BASE + 0x024)
#define REG_BLTC_B_DUTY         (REG_BLTC_BASE + 0x028)
#define REG_BLTC_B_CURVE0       (REG_BLTC_BASE + 0x02C)
#define REG_BLTC_B_CURVE1       (REG_BLTC_BASE + 0x030)
#define REG_BLTC_STS            (REG_BLTC_BASE + 0x034)

#define CTL_BASE_ANA_GLB 	0x40388C00
#define ANA_REG_GLB_MODULE_EN0  (CTL_BASE_ANA_GLB + 0x0008)
#define ANA_REG_GLB_RTC_CLK_EN0 (CTL_BASE_ANA_GLB + 0x0010)
#define ANA_REG_GLB_RGB_CTRL    (CTL_BASE_ANA_GLB + 0x02A0)

#define BITS_RGB_V(x)           (((x) & 0x1F) << 4)
#define BIT_BLTC_EN             BIT(9)
#define BIT_RTC_BLTC_EN         BIT(7)
#define X_DUTY			100
#define X_MODE			(X_DUTY - 1)
#define X_CURRENT		0x1F	/*0 ~ 0x1F*/

static void bltc_write(u32 value, u32 reg)
{
	__raw_writel(value, reg);
	udelay(100);
}

static void bltc_bits_or(u32 value, u32 reg)
{
	__raw_writel((ANA_REG_GET(reg) | value), reg);
	udelay(100);
}
#endif

static inline uint32_t pwm_read(int index, uint32_t reg)
{
	return __raw_readl(CTL_BASE_PWM + index * 0x20 + reg);
}

static void pwm_write(int index, uint32_t value, uint32_t reg)
{
	__raw_writel(value, CTL_BASE_PWM + index * 0x20 + reg);
}

void set_backlight(uint32_t brightness)
{
#ifndef CONFIG_BACKLIGHT_WHTLED
	int index = PWM_INDEX;

	__raw_bits_or((0x1 << 0), REG_AON_CLK_CORE_CGM_PWM0_CFG + index * 4);//ext_26m select
	__raw_bits_or(((1 << PWM_INDEX) << 4), REG_AON_APB_APB_EB0); //PWMx EN


	if (0 == brightness) {
		pwm_write(index, 0, PWM_ENABLE);
		printf("sprd backlight power off. pwm_index=%d  brightness=%d\n", index, brightness);
	} else {
		pwm_write(index, PWM2_SCALE, PWM_PRESCALE);
		pwm_write(index, PWM_MOD_MAX, PWM_MOD);
		pwm_write(index,  brightness, PWM_DUTY);

		pwm_write(index, PWM_REG_MSK, PWM_PAT_LOW);
		pwm_write(index, PWM_REG_MSK, PWM_PAT_HIGH);
		pwm_write(index, 1, PWM_ENABLE);
		printf("sprd backlight power on. pwm_index=%d  brightness=%d\n", index, brightness);
	}
#else

	u32 duty = brightness * X_DUTY / 0xFF;

	duty = ((duty ? duty : 1) << 8) | X_MODE;

	bltc_write(0x0, ANA_REG_GLB_RGB_CTRL);

	/*SET BLTC prescale coefficient, no prescl(0 -> 1rtc_clk)*/
	bltc_write(0x0, REG_BLTC_R_PRESCL);
	bltc_write(0x0, REG_BLTC_G_PRESCL);
	bltc_write(0x0, REG_BLTC_B_PRESCL);

	/*SET BLTC Output RISE/FALL Time*/
	bltc_write(0x0, REG_BLTC_R_CURVE0);
	bltc_write(0x0, REG_BLTC_G_CURVE0);
	bltc_write(0x0, REG_BLTC_B_CURVE0);

	/*SET BLTC Output HIGH/LOW Time*/
	bltc_write(0x0, REG_BLTC_R_CURVE1);
	bltc_write(0x0, REG_BLTC_G_CURVE1);
	bltc_write(0x0, REG_BLTC_B_CURVE1);

	/*SET BLTC DUTY(duty_counter + mod_counter)*/
	bltc_write(duty, REG_BLTC_R_DUTY);
	bltc_write(duty, REG_BLTC_G_DUTY);
	bltc_write(duty, REG_BLTC_B_DUTY);

	bltc_write(0x333, REG_BLTC_BASE);

	/*USE MAX CURRENT 85.71mA= {(1.69+0.84*32)*3}*/
	/*AS THE backlight DEFAULT OUTPUT CURRENT*/
	bltc_write(BITS_RGB_V(X_CURRENT), ANA_REG_GLB_RGB_CTRL);

	bltc_bits_or(BIT_BLTC_EN, ANA_REG_GLB_MODULE_EN0);

	bltc_bits_or(BIT_RTC_BLTC_EN, ANA_REG_GLB_RTC_CLK_EN0);

	printf("sprd backlight power on. bltc pwm brightness=%d\n", brightness);

#endif
	return;
}

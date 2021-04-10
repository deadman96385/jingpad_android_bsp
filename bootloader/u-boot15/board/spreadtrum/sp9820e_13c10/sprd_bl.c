#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <adi_hal_internal.h>

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
	u32 bl_brightness, led_level;
	u32 reg_val;

	printf("sprd backlight power brightness=%d\n", brightness);
	__raw_writel(0x0,0x40388EA0);

	if(0==brightness){
	__raw_writel(0x0005,0x40388EA0);
	}
	else
	{
	reg_val = ANA_REG_GET(0x40388C08);
	reg_val = reg_val | 0x200;
	__raw_writel(reg_val,0x40388C08);			//bltc en bit
	udelay(100);

	reg_val = ANA_REG_GET(0x40388C10);
	reg_val = reg_val | 0x80;
	__raw_writel(reg_val,0x40388C10);			//bltc rtc en bit
	udelay(100);

	if(brightness <= 16)
	{
		__raw_writel(0,0x40388EA0);			//enable RGB LED
		udelay(100);
	}
	else
	{
		reg_val = (80 * brightness * 100) / 255 / 3;
		reg_val = (reg_val -169) / 84;
		reg_val = reg_val << 4;
		__raw_writel(reg_val,0x40388EA0);		//enable RGB LED
		udelay(100);
	}

	__raw_writel(0xfff,0x40388180);				//enable bltc modules
	udelay(100);

	}
#endif
	return;
}

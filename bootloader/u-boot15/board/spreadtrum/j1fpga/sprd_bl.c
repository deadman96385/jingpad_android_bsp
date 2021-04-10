#include <common.h>
#include <asm/arch/hardware.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>

#define PWM_INDEX 0

#define PWM_PRESCALE (0x0000)
#define PWM_CNT (0x0004)
#define PWM_PAT_LOW (0x000C)
#define PWM_PAT_HIG (0x0010)

#define PWM_ENABLE (1 << 8)
#define PWM2_SCALE 0x0
#define PWM_REG_MSK 0xffff
#define PWM_MOD_MAX 0xff


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
#ifndef CONFIG_FPGA
	int index = PWM_INDEX;
	__raw_bits_or((0x1 << 0), REG_AON_CLK_CORE_clk_pwm0_cfg + index * 4);//ext_26m select

	if (0 == brightness) {
		pwm_write(index, 0, PWM_PRESCALE);
		printf("sprd backlight power off. pwm_index=%d  brightness=%d\n", index, brightness);
	} else {
		__raw_bits_or((0x1 << (index+4)), REG_AON_APB_APB_EB0); //PWMx EN

		pwm_write(index, PWM2_SCALE, PWM_PRESCALE);
		pwm_write(index, (brightness << 8) | PWM_MOD_MAX, PWM_CNT);
		pwm_write(index, PWM_REG_MSK, PWM_PAT_LOW);
		pwm_write(index, PWM_REG_MSK, PWM_PAT_HIG);
		pwm_write(index, PWM_ENABLE, PWM_PRESCALE);
		printf("sprd backlight power on. pwm_index=%d  brightness=%d\n", index, brightness);
	}

	return;
#endif
}

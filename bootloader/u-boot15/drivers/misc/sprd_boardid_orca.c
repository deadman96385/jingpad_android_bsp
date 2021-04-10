#include <common.h>
#include <sprd_adc.h>
#include "otp_helper.h"
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>

#define HB_GPIO    8
#define MB_GPIO    7
#define LB_GPIO    6

#define option6_check  BIT(4)

extern int sprd_gpio_request(struct gpio_chip *chip, unsigned offset);
extern int sprd_gpio_direction_input(struct gpio_chip *chip, unsigned offset);
extern int sprd_gpio_get(struct gpio_chip *chip, unsigned offset);

static unsigned int gpio_state(unsigned int GPIO_NUM)
{
	int value = 0 ;

	sprd_gpio_request(NULL, GPIO_NUM);
	sprd_gpio_direction_input(NULL, GPIO_NUM);
	value = sprd_gpio_get(NULL,GPIO_NUM);

	return value > 0;
}

/*check option 6 value*/
static int first_check(void)
{
	unsigned int reg_val = 0;
	int  option_value;

	reg_val = ANA_REG_GET(ANA_REG_GLB_CLK32KLESS_CTRL0);

	option_value = ( reg_val & option6_check ) >> 4;

	return option_value;
}


/*check gpio 8 value*/
static int second_check(void)
{
	unsigned int gpio_value = 0;

	gpio_value = gpio_state(HB_GPIO);

	return gpio_value;
}

/*check gpio 6 and 7 value*/
static int third_check(void)
{
	unsigned int gpio_val = 0;
	unsigned int shift_bit = 0;

	gpio_val |= gpio_state(LB_GPIO) << shift_bit;
	shift_bit++;

	gpio_val |= gpio_state(MB_GPIO) << shift_bit;
	shift_bit++;

	return gpio_val;
}

/* Return board id */
int sprd_get_versionid(void)
{
	int first_check_value, second_check_value, third_check_value;

	first_check_value = first_check();
	second_check_value = second_check();

	if (first_check_value == 1)
		return 0;	/*udx710_1h10 */
	else if (second_check_value==1)
		return 1;	/*udx710_2h10*/
	else {
		third_check_value = third_check();
			if (third_check_value ==0)
				return 2;	/*udx710_3h10*/
			if (third_check_value ==1)
				return 3;	/*reserved*/
			if (third_check_value ==2)
				return 4;	/*reserved*/
			if (third_check_value ==3)
				return 5;	/*reserved*/
		}
}

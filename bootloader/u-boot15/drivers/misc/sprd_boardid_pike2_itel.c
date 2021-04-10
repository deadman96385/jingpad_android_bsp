#include <common.h>
#include <sprd_adc.h>
#include "otp_helper.h"

#define MB_GPIO    49
#define LB_GPIO    48
#define ADC_CHANNEL_FOR_NV    3

typedef enum k_less {
	K32 = 0,
	K_LESS,
}k_less_t;

typedef enum crystal_type {
	VCTCXO = 0,
	DCXO,
	TSX,
	TCXO,
}crystal_type_t;

struct clock_table {
	k_less_t k32_less_data;
	crystal_type_t crystal_data;
};

static const struct clock_table clock_table[] = {
	{K_LESS, TSX},
	{K_LESS, DCXO},
	{K32, TCXO},
	{K_LESS, TSX},
};

static const int adc2deltanv_table[] = {
	-1, /* reserved */
	-1, /* reserved */
	-1, /* reserved */
	3, /* hw_ver03.nv */
	-1, /* reserved */
	2, /* hw_ver02.nv */
	1, /* hw_ver01.nv */
	0 /* hw_ver00.nv */
};

extern int sprd_gpio_request(struct gpio_chip *chip, unsigned offset);
extern int sprd_gpio_direction_input(struct gpio_chip *chip, unsigned offset);
extern int sprd_gpio_get(struct gpio_chip *chip, unsigned offset);

static int gpio_state(unsigned int GPIO_NUM)
{
	int value = 0;

	sprd_gpio_request(NULL, GPIO_NUM);
	sprd_gpio_direction_input(NULL, GPIO_NUM);
	value = sprd_gpio_get(NULL,GPIO_NUM);

	if(value != 0)
	{
	/* value may be -EINVAL in theory when gpio num is wrong! */
		return 1;
	}
	else
	{
		return 0;
	}
}

static int get_adc_value_board(int channel)
{
	int adc_value = 0,level = 0;
	int vol = 0;

	adc_value = pmic_adc_get_value_by_isen(channel,0,15,2000);
	vol = sprd_chan_small_adc_to_vol(channel, 0 , 0 ,adc_value);
	debugf("The voltage is = %d\n",vol);

	if (vol <= 0 || vol >= 1200) {
		errorf("vol is out of ranger [0~1200]\n");
		return -1;
	}

	if (vol >= 9 && vol <= 31)
		level = 0;
	if (vol >= 180 && vol <= 220)
		level = 1;
	if (vol >= 275 && vol <= 325)
		level = 2;
	if (vol >= 370 && vol <= 430)
		level = 3;
	if (vol >= 560 && vol <= 640)
		level = 4;
	if (vol >= 731 && vol <= 829)
		level = 5;
	if (vol >= 883 && vol <= 997)
		level = 6;
	if (vol >= 1054 && vol <= 1186)
		level = 7;

	debugf("level = %d\n",level);

	if(level < 0 || level > 7) {
		errorf("Adc value of rf band if is wrong, the rfboard.id will be set to -1\n");
		return -1;
	}

	return adc2deltanv_table[level];
}

static int get_clockid(void)
{
	int gpio_val = 0;
	int shift_bit = 0;

	gpio_val |= gpio_state(LB_GPIO);
	shift_bit++;

	gpio_val |= gpio_state(MB_GPIO) << shift_bit;

	return gpio_val;
}

/* Return rf band info */
int sprd_get_bandinfo(void)
{
	int rfid = 0;

	rfid = get_adc_value_board(ADC_CHANNEL_FOR_NV);
	debugf("rfboard.id = %d\n", rfid);

	return rfid;
}

/* Return crystal type */
int sprd_get_crystal(void)
{
	int id = get_clockid();

	return clock_table[id].crystal_data;
}

/* Return 32k less or not */
int sprd_get_32k(void)
{
/* sw auto-adaption */
#ifdef CONFIG_BOARD_ID
	int id = get_clockid();

	return clock_table[id].k32_less_data;
#else
/* dedicate definition */
#ifdef CONFIG_32K_TYPE
        return CONFIG_32K_TYPE;
#else
/* default setting */
        return K_LESS;
#endif
#endif
}

/* Return board id */
int sprd_get_boardid(void)
{
	return get_clockid();
}

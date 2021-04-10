#include <common.h>
#include <sprd_adc.h>
#include "otp_helper.h"

#define MB_GPIO   141
#define LB_GPIO   140
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
	{K_LESS, TSX},
	{K32, TCXO},
};

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

static int get_adc_value_board(int channel)
{
	int adc_value=0,vol = 0;

	adc_value = pmic_adc_get_value_by_isen(channel,0,15,2000);
	vol = sprd_chan_small_adc_to_vol(channel, 0 , 0 ,adc_value);
	debugf("result = %d\n",vol);

	if (vol <= 0 || vol >= 1200) {
		errorf("vol is out of ranger [0~1200]\n");
		return -1;
	}

	if (vol >0 && vol <= 100)
		vol = 0;
	if (vol > 100 && vol <= 250 )
		vol = 1;
	if (vol > 250 && vol <= 400)
		vol = 2;
	if (vol > 400 && vol <= 500)
		vol = 3;
	if (vol > 500 && vol <= 700)
		vol = 4;
	if (vol > 700 && vol <= 800)
		vol = 5;
	if (vol > 900 && vol <= 1000)
		vol = 6;
	if (vol > 1000 && vol < 1200)
		vol = 7;

	return vol;
}

static int get_clockid(void)
{
	unsigned int gpio_val = 0;
	unsigned int shift_bit = 0;

	gpio_val |= gpio_state(LB_GPIO) << shift_bit;
	shift_bit++;

	gpio_val |= gpio_state(MB_GPIO) << shift_bit;
	shift_bit++;

	return gpio_val;
}

/* Return rf band info */
int sprd_get_bandinfo(void)
{
	unsigned int adc_val = 0;

	adc_val = get_adc_value_board(ADC_CHANNEL_FOR_NV);
	debugf("adc_val: %d\n", adc_val);

	return adc_val;
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

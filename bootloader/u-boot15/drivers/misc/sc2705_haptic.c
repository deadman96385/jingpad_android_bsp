#include <common.h>
#include <i2c.h>
#include <linux/types.h>

#if defined(CONFIG_SPRD_SOC_SP9853I)
#define SC2705_I2C_BUS_ISHARKL2 4
#else
#define SC2705_I2C_BUS 3
#endif

#define SC2705_HAPTIC_I2C_ADDR 0x4A

#ifndef BIT
#define BIT(x) (1 << (x))
#endif
#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#endif

#define H_IRQ_EVENT1			0x03
#define H_IRQ_EVENT_WARNING_DIAG	0x04
#define H_IRQ_EVENT_PAT_DIAG		0x05
#define H_IRQ_MASK1			0x07
#define H_FRQ_LRA_PER_H			0x0A
#define H_FRQ_LRA_PER_L			0x0B
#define H_ACTUATOR1			0x0C
#define H_ACTUATOR2			0x0D
#define H_ACTUATOR3			0x0E
#define H_CALIB_V2I_H			0x0F
#define H_CALIB_V2I_L			0x10
#define H_TOP_CFG1			0X13
#define H_TOP_CTL1			0x21
#define H_TOP_CTL2			0x22
#define H_TRIM1				0x53
#define H_TRIM2				0x54

/* H_IRQ_MASK1 */
#define SEQ_CONTINUE_M	BIT(0)
#define SOFT_SHUTDOWN_M	BIT(1)
#define PAT_DONE_M	BIT(2)
#define CALIB_DONE_M	BIT(3)
#define PAT_FAULT_M	BIT(4)
#define WARNING_M	BIT(5)
#define ACTUATOR_M	BIT(6)
#define OC_M		BIT(7)

/* H_TOP_CFG1 */
#define AMP_PID_EN	BIT(0)
#define RAPID_STOP_EN	BIT(1)
#define ACCELERATION_EN	BIT(2)
#define FREQ_TRACK_EN	BIT(3)
#define ACTUATOR_TYPE	BIT(4)

/* H_TOP_CTL1 */
#define OPERATION_MODE_MSK	(BIT(3) - 1)
#define OPERATION_MODE_INACTIVE	0
#define OPERATION_MODE_DRO	1
#define OPERATION_MODE_PWM	2
#define OPERATION_MODE_WV_M	3
#define OPERATION_MODE_WV_E	4
#define OPERATION_MODE_WV_D	5
#define PATTERN_INACTIVE_MODE	BIT(3)
#define SEQ_START		BIT(4)
#define CALIB_REQ		BIT(5)

static const unsigned char LRA_OHMS[] = {
	/* Ohms, values */
	42,	/* 0 */
	28,	/* 1 */
	19,	/* 2 */
	0,	/* 3 */
};

typedef enum {
	LRA,
	ERM_BAR,
	ERM_COIN,
} vibrator_type_t;

typedef struct {
	vibrator_type_t type;
	unsigned int resonant_freq;
	unsigned int normal_voltage;
	unsigned int normal_current;
	unsigned int max_voltage;
	unsigned int impedance;
	unsigned int filter_res_trim;
} vibrator_data_t;

/* TODO: configure this in each board */
static vibrator_data_t vibrator = {
	.type = LRA,
	.resonant_freq = 242,
	.normal_voltage = 2500,
	.normal_current = 130,
	.max_voltage = 2800,
	.impedance = 3,
	.filter_res_trim = 0,
};

void set_vibrator(int on)
{
	unsigned int old, value, read;

	old = i2c_get_bus_num();
	printf("haptic i2c adapter num: %d\n", old);

#if defined(CONFIG_SPRD_SOC_SP9853I)
	i2c_set_bus_num(3);
	i2c_set_bus_num(SC2705_I2C_BUS_ISHARKL2);
#else
	i2c_set_bus_num(SC2705_I2C_BUS);
#endif

	value = i2c_reg_read(SC2705_HAPTIC_I2C_ADDR, H_IRQ_EVENT1);
	read = i2c_reg_read(SC2705_HAPTIC_I2C_ADDR, H_IRQ_EVENT_WARNING_DIAG);
	read = i2c_reg_read(SC2705_HAPTIC_I2C_ADDR, H_IRQ_EVENT_PAT_DIAG);
	printf("haptic error code: 0x%02X\n", value);
	if (value)
		i2c_reg_write(SC2705_HAPTIC_I2C_ADDR,
			      H_IRQ_EVENT1, (value & 0xFF));
	value = on ? 0x7F : 0x00;
	i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_TOP_CTL2, value);

	i2c_set_bus_num(old);

	printf("haptic %s\n", on ? "on" : "off");
}

void vibrator_hw_init(void)
{
	unsigned int old, value, i;
	unsigned char read;

	/* TODO: check vibrator values */

	old = i2c_get_bus_num();
	printf("init i2c adapter num: %d\n", old);

#if defined(CONFIG_SPRD_SOC_SP9853I)
        i2c_set_bus_num(3);
        i2c_set_bus_num(SC2705_I2C_BUS_ISHARKL2);
#else
        i2c_set_bus_num(SC2705_I2C_BUS);
#endif

	if (vibrator.type == LRA) {
		/* LRA type */
		i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_TOP_CFG1,
			      FREQ_TRACK_EN
			      | ACCELERATION_EN
			      | RAPID_STOP_EN);
		/* resonant_freq */
		value = 1000000000 / vibrator.resonant_freq / 2 / 665;
		i2c_reg_write(SC2705_HAPTIC_I2C_ADDR,
			      H_FRQ_LRA_PER_H, (value >> 7) & 0xFF);
		i2c_reg_write(SC2705_HAPTIC_I2C_ADDR,
			      H_FRQ_LRA_PER_H, value & 0x7F);
	} else if (vibrator.type == ERM_COIN) {
		/* TODO: need to tune ERM_COIN type */
	} else {
		/* TODO: need to tune ERM_BAR type */
	}
	/* normal_voltage */
	value = vibrator.normal_voltage * 1000 / 23400 + 1;
	i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_ACTUATOR1, value & 0xFF);
	/* max_voltage */
	value = vibrator.max_voltage * 1000 / 23400 + 1;
	i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_ACTUATOR2, value & 0xFF);
	/* normal_current */
	value = (vibrator.normal_current * 1000 - 28600) / 7200;
	i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_ACTUATOR3, value & 0x1F);
	/* DRO mode */
	i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_TOP_CTL1,
		      OPERATION_MODE_DRO
		      | PATTERN_INACTIVE_MODE);
	/* idac gain */
	value = vibrator.impedance * (value + 4) * 3 * 10000;
	read = i2c_reg_read(SC2705_HAPTIC_I2C_ADDR, H_TRIM1);
	read = (read >> 4) & 0x0F;
	value = value / (183 * 4 * (58 + read));
	i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_CALIB_V2I_H,
		      (value >> 8) & 0xFF);
	i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_CALIB_V2I_L,
		      value & 0xFF);

	for (i = 0; i < ARRAY_SIZE(LRA_OHMS); i++) {
		if (vibrator.impedance > LRA_OHMS[i]) {
			value = i;
			break;
		}
	}
	value = ((value << 2) | vibrator.filter_res_trim) & 0x0F;
	read = i2c_reg_read(SC2705_HAPTIC_I2C_ADDR, H_TRIM2);
	i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_TRIM2, read | value);

	i2c_reg_write(SC2705_HAPTIC_I2C_ADDR, H_IRQ_MASK1,
		      ~(PAT_DONE_M | PAT_FAULT_M));

	i2c_set_bus_num(old);

	printf("haptic init\n");
}

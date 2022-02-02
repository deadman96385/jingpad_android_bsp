// SPDX-License-Identifier: GPL-2.0+
/*
 * DA9121 Single-channel dual-phase buck converter
 * Copyright (C) 2019  Dialog Semiconductor
 *
 * Author: Steve Twiss, Dialog Semiconductor
 */

#include <linux/bitops.h>
#include <linux/debugfs.h>
#include <linux/err.h>
#include <linux/gpio/consumer.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/regulator/driver.h>
#include <linux/regmap.h>
#include <linux/regulator/of_regulator.h>
#include <linux/workqueue.h>

/* Registers */

#define DA9121_REG_SYS_STATUS_0		0x01
#define DA9121_REG_SYS_STATUS_1		0x02
#define DA9121_REG_SYS_STATUS_2		0x03
#define DA9121_REG_SYS_EVENT_0		0x04
#define DA9121_REG_SYS_EVENT_1		0x05
#define DA9121_REG_SYS_EVENT_2		0x06
#define DA9121_REG_SYS_MASK_0		0x07
#define DA9121_REG_SYS_MASK_1		0x08
#define DA9121_REG_SYS_MASK_2		0x09
#define DA9121_REG_SYS_MASK_3		0x0a
#define DA9121_REG_SYS_CONFIG_0		0x0b
#define DA9121_REG_SYS_CONFIG_1		0x0c
#define DA9121_REG_SYS_CONFIG_2		0x0d
#define DA9121_REG_SYS_CONFIG_3		0x0e
#define DA9121_REG_SYS_GPIO0_0		0x10
#define DA9121_REG_SYS_GPIO0_1		0x11
#define DA9121_REG_SYS_GPIO1_0		0x12
#define DA9121_REG_SYS_GPIO1_1		0x13
#define DA9121_REG_SYS_GPIO2_0		0x14
#define DA9121_REG_SYS_GPIO2_1		0x15
#define DA9121_REG_BUCK_BUCK1_0		0x20
#define DA9121_REG_BUCK_BUCK1_1		0x21
#define DA9121_REG_BUCK_BUCK1_2		0x22
#define DA9121_REG_BUCK_BUCK1_3		0x23
#define DA9121_REG_BUCK_BUCK1_4		0x24
#define DA9121_REG_BUCK_BUCK1_5		0x25
#define DA9121_REG_BUCK_BUCK1_6		0x26
#define DA9121_REG_BUCK_BUCK1_7		0x27
#define DA9121_REG_OTP_DEVICE_ID	0x48
#define DA9121_REG_OTP_VARIANT_ID	0x49
#define DA9121_REG_OTP_CUSTOMER_ID	0x4a
#define DA9121_REG_OTP_CONFIG_ID	0x4b

/* Register bits */

/* DA9121_REG_SYS_STATUS_0 */

#define DA9121_MASK_SYS_STATUS_0_TEMP_CRIT		BIT(1)
#define DA9121_MASK_SYS_STATUS_0_TEMP_WARN		BIT(0)

/* DA9121_REG_SYS_STATUS_1 */

#define DA9121_MASK_SYS_STATUS_1_PG1			BIT(3)
#define DA9121_MASK_SYS_STATUS_1_OV1			BIT(2)
#define DA9121_MASK_SYS_STATUS_1_UV1			BIT(1)
#define DA9121_MASK_SYS_STATUS_1_OC1			BIT(0)

/* DA9121_REG_SYS_STATUS_2 */

#define DA9121_MASK_SYS_STATUS_2_GPIO2			BIT(2)
#define DA9121_MASK_SYS_STATUS_2_GPIO1			BIT(1)
#define DA9121_MASK_SYS_STATUS_2_GPIO0			BIT(0)

/* DA9121_REG_SYS_EVENT_0 */

#define DA9121_MASK_SYS_EVENT_0_E_TEMP_CRIT		BIT(1)
#define DA9121_MASK_SYS_EVENT_0_E_TEMP_WARN		BIT(0)

/* DA9121_REG_SYS_EVENT_1 */

#define DA9121_MASK_SYS_EVENT_1_E_PG1			BIT(3)
#define DA9121_MASK_SYS_EVENT_1_E_OV1			BIT(2)
#define DA9121_MASK_SYS_EVENT_1_E_UV1			BIT(1)
#define DA9121_MASK_SYS_EVENT_1_E_OC1			BIT(0)

/* DA9121_REG_SYS_EVENT_2 */

#define DA9121_MASK_SYS_EVENT_2_E_GPIO2			BIT(2)
#define DA9121_MASK_SYS_EVENT_2_E_GPIO1			BIT(1)
#define DA9121_MASK_SYS_EVENT_2_E_GPIO0			BIT(0)

/* DA9121_REG_SYS_MASK_0 */

#define DA9121_MASK_SYS_MASK_0_M_TEMP_CRIT		BIT(1)
#define DA9121_MASK_SYS_MASK_0_M_TEMP_WARN		BIT(0)

/* DA9121_REG_SYS_MASK_1 */

#define DA9121_MASK_SYS_MASK_1_M_PG1			BIT(3)
#define DA9121_MASK_SYS_MASK_1_M_OV1			BIT(2)
#define DA9121_MASK_SYS_MASK_1_M_UV1			BIT(1)
#define DA9121_MASK_SYS_MASK_1_M_OC1			BIT(0)

/* DA9121_REG_SYS_MASK_2 */

#define DA9121_MASK_SYS_MASK_2_M_GPIO2			BIT(2)
#define DA9121_MASK_SYS_MASK_2_M_GPIO1			BIT(1)
#define DA9121_MASK_SYS_MASK_2_M_GPIO0			BIT(0)

/* DA9122_REG_SYS_MASK_3 */

#define DA9121_MASK_SYS_MASK_3_M_VR_HOT			BIT(3)
#define DA9121_MASK_SYS_MASK_3_M_PG1_STAT		BIT(0)

/* DA9121_REG_SYS_CONFIG_2 */

#define DA9121_MASK_SYS_CONFIG_2_OC_LATCHOFF		0x60
#define DA9121_MASK_SYS_CONFIG_2_OC_DVC_MASK		BIT(4)
#define DA9121_MASK_SYS_CONFIG_2_PG_DVC_MASK		0xc0

/* DA9121_REG_SYS_CONFIG_3 */

#define DA9121_MASK_SYS_CONFIG_3_OSC_TUNE		0X70
#define DA9121_MASK_SYS_CONFIG_3_I2C_TIMEOUT		BIT(1)

/* DA9121_REG_SYS_GPIO0_0 */

#define DA9121_MASK_SYS_GPIO0_0_GPIO0_MODE		0X1e
#define DA9121_MASK_SYS_GPIO0_0_GPIO0_OBUF		BIT(0)

/* DA9121_REG_SYS_GPIO0_1 */

#define DA9121_MASK_SYS_GPIO0_1_GPIO0_DEB_FALL		BIT(7)
#define DA9121_MASK_SYS_GPIO0_1_GPIO0_DEB_RISE		BIT(6)
#define DA9121_MASK_SYS_GPIO0_1_GPIO0_DEB		0x30
#define DA9121_MASK_SYS_GPIO0_1_GPIO0_PUPD		BIT(3)
#define DA9121_MASK_SYS_GPIO0_1_GPIO0_POL		BIT(2)
#define DA9121_MASK_SYS_GPIO0_1_GPIO0_TRIG		0x03

/* DA9121_REG_SYS_GPIO1_0 */

#define DA9121_MASK_SYS_GPIO1_0_GPIO1_MODE		0x1e
#define DA9121_MASK_SYS_GPIO1_0_GPIO1_OBUF		BIT(0)

/* DA9121_REG_SYS_GPIO1_1 */

#define DA9121_MASK_SYS_GPIO1_1_GPIO1_DEB_FALL		BIT(7)
#define DA9121_MASK_SYS_GPIO1_1_GPIO1_DEB_RISE		BIT(6)
#define DA9121_MASK_SYS_GPIO1_1_GPIO1_DEB		0x30
#define DA9121_MASK_SYS_GPIO1_1_GPIO1_PUPD		BIT(3)
#define DA9121_MASK_SYS_GPIO1_1_GPIO1_POL		BIT(2)
#define DA9121_MASK_SYS_GPIO1_1_GPIO1_TRIG		0x03

/* DA9121_REG_SYS_GPIO2_0 */

#define DA9121_MASK_SYS_GPIO2_0_GPIO2_MODE		0x1e
#define DA9121_MASK_SYS_GPIO2_0_GPIO2_OBUF		BIT(0)

/* DA9121_REG_SYS_GPIO2_1 */

#define DA9121_MASK_SYS_GPIO2_1_GPIO2_DEB_FALL		BIT(7)
#define DA9121_MASK_SYS_GPIO2_1_GPIO2_DEB_RISE		BIT(6)
#define DA9121_MASK_SYS_GPIO2_1_GPIO2_DEB		0x30
#define DA9121_MASK_SYS_GPIO2_1_GPIO2_PUPD		BIT(3)
#define DA9121_MASK_SYS_GPIO2_1_GPIO2_POL		BIT(2)
#define DA9121_MASK_SYS_GPIO2_1_GPIO2_TRIG		0x03

/* DA9121_REG_BUCK_BUCK1_0 */

#define DA9121_MASK_BUCK_BUCK1_0_CH1_SR_DVC_DWN		0x70
#define DA9121_MASK_BUCK_BUCK1_0_CH1_SR_DVC_UP		0x0e
#define DA9121_MASK_BUCK_BUCK1_0_CH1_EN			BIT(0)

/* DA9121_REG_BUCK_BUCK1_1 */

#define DA9121_MASK_BUCK_BUCK1_1_CH1_SR_SHDN		0x70
#define DA9121_MASK_BUCK_BUCK1_1_CH1_SR_STARTUP		0x0e
#define DA9121_MASK_BUCK_BUCK1_1_CH1_PD_DIS		BIT(0)

/* DA9121_REG_BUCK_BUCK1_2 */

#define DA9121_MASK_BUCK_BUCK1_2_CH1_ILIM		0x0f

/* DA9121_REG_BUCK_BUCK1_3 */

#define DA9121_MASK_BUCK_BUCK1_3_CH1_VMAX		0xff

/* DA9121_REG_BUCK_BUCK1_4 */

#define DA9121_MASK_BUCK_BUCK1_4_CH1_VSEL		BIT(4)
#define DA9121_MASK_BUCK_BUCK1_4_CH1_B_MODE		0x0c
#define DA9121_MASK_BUCK_BUCK1_4_CH1_A_MODE		0x03

/* DA9121_REG_BUCK_BUCK1_5 */

#define DA9121_MASK_BUCK_BUCK1_5_CH1_A_VOUT		0xff

/* DA9121_REG_BUCK_BUCK1_6 */

#define DA9121_MASK_BUCK_BUCK1_6_CH1_B_VOUT		0xff

/* DA9121_REG_OTP_DEVICE_ID */

#define DA9121_MASK_OTP_DEVICE_ID_DEV_ID		0xff

/* DA9121_REG_OTP_VARIANT_ID */

#define DA9121_SHIFT_OTP_VARIANT_ID_MRC			4
#define DA9121_MASK_OTP_VARIANT_ID_MRC			0xf0
#define DA9121_SHIFT_OTP_VARIANT_ID_VRC			0
#define DA9121_MASK_OTP_VARIANT_ID_VRC			0x0f

/* DA9121_REG_OTP_CUSTOMER_ID */

#define DA9121_MASK_OTP_CUSTOMER_ID_CUST_ID		0xff

/* DA9121_REG_OTP_CONFIG_ID */

#define DA9121_MASK_OTP_CONFIG_ID_CONFIG_REV		0xff

/* Minimum, maximum and default polling millisecond periods are provided
 * here as an example. It is expected that any final implementation will
 * include a modification of these settings to match the required
 * application.
 */
#define DA9121_DEFAULT_POLLING_PERIOD_MS	3000
#define DA9121_MAX_POLLING_PERIOD_MS		10000
#define DA9121_MIN_POLLING_PERIOD_MS		1000

/* Device ID list */
#define DA9121_DEVICE_ID	0x5
#define DA9121_VARIANT_MRC_BASE	0x2
#define DA9121_VARIANT_VRC	0x1

/* Regulator IDs */
enum {
	DA9121_ID_BUCK1,
	DA9121_MAX_REGULATORS,
};

/* Device tree data */
struct da9121_dt_data {
	unsigned int num_matches;
	int gpio_ren[DA9121_MAX_REGULATORS];
	struct device_node *reg_node[DA9121_MAX_REGULATORS];
	struct regulator_init_data *init_data[DA9121_MAX_REGULATORS];
};

/* Chip data */
struct da9121 {
	struct device *dev;
	struct delayed_work work;
	struct regmap *regmap;
	struct da9121_dt_data *dt_data;
	struct regulator_dev *rdev[DA9121_MAX_REGULATORS];
	unsigned int persistent[2];
	unsigned int passive_delay;
	int chip_irq;
};

#define DA9121_BUCK1_MIN_UV	300000
#define DA9121_BUCK1_MAX_UV	1900000
#define DA9121_BUCK1_MIN_INDEX	30
#define DA9121_BUCK1_MAX_INDEX	190

/* Voltage range LUT for DA9121 BUCK1 (uV) */
static const int da9121_buck_voltage_lut[] = {
	-EACCES, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EACCES, 300000, 310000,
	320000, 330000, 340000, 350000, 360000, 370000, 380000, 390000, 400000,
	410000, 420000, 430000, 440000, 450000, 460000, 470000, 480000, 490000,
	500000, 510000, 520000, 530000, 540000, 550000, 560000, 570000, 580000,
	590000, 600000, 610000, 620000, 630000, 640000, 650000, 660000, 670000,
	680000, 690000, 700000, 710000, 720000, 730000, 740000, 750000, 760000,
	770000, 780000, 790000, 800000, 810000, 820000, 830000, 840000, 850000,
	860000, 870000, 880000, 890000, 900000, 910000, 920000, 930000, 940000,
	950000, 960000, 970000, 980000, 990000, 1000000, 1010000, 1020000,
	1030000, 1040000, 1050000, 1060000, 1070000, 1080000, 1090000, 1100000,
	1110000, 1120000, 1130000, 1140000, 1150000, 1160000, 1170000, 1180000,
	1190000, 1200000, 1210000, 1220000, 1230000, 1240000, 1250000, 1260000,
	1270000, 1280000, 1290000, 1300000, 1310000, 1320000, 1330000, 1340000,
	1350000, 1360000, 1370000, 1380000, 1390000, 1400000, 1410000, 1420000,
	1430000, 1440000, 1450000, 1460000, 1470000, 1480000, 1490000, 1500000,
	1510000, 1520000, 1530000, 1540000, 1550000, 1560000, 1570000, 1580000,
	1590000, 1600000, 1610000, 1620000, 1630000, 1640000, 1650000, 1660000,
	1670000, 1680000, 1690000, 1700000, 1710000, 1720000, 1730000, 1740000,
	1750000, 1760000, 1770000, 1780000, 1790000, 1800000, 1810000, 1820000,
	1830000, 1840000, 1850000, 1860000, 1870000, 1880000, 1890000, 1900000,
	-EACCES, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL, -EINVAL,
	-EACCES,
};

#define DA9121_BUCK_ILIM_MIN_UV	3500000
#define DA9121_BUCK_ILIM_MAX_UV	10000000
#define DA9121_BUCK_ILIM_MIN_INDEX	1
#define DA9121_BUCK_ILIM_MAX_INDEX	14

/* Current limit range LUT for DA9121 BUCK1 (uA) */
static const int da9121_buck_current_limit_lut[] = {
	-EACCES,
	3500000, 4000000, 4500000, 5000000, 5500000, 6000000, 6500000,
	7000000, 7500000, 8000000, 8500000, 9000000, 9500000, 10000000,
	-EINVAL,
};

static void da9121_status_poll_on(struct work_struct *work)
{
	struct da9121 *chip = container_of(work, struct da9121, work.work);
	enum { R0 = 0, R1, R2, REG_MAX_NUM };
	int status[REG_MAX_NUM] = { };
	int clear[REG_MAX_NUM] = { };
	unsigned long delay;
	int i;
	int ret;

	/* If persistent-notification, status will be true
	 * If not persistent-notification any longer, status will be false
	 */
	ret = regmap_bulk_read(chip->regmap, DA9121_REG_SYS_STATUS_0,
			       (void *)status, (size_t)R1);
	if (ret < 0) {
		dev_err(chip->dev,
			"Failed to read STATUS registers: %d\n", ret);
		return;
	}

	/* 0 TEMP_CRIT */
	if ((chip->persistent[R0] & DA9121_MASK_SYS_EVENT_0_E_TEMP_CRIT) &&
	    !(status[R0] & DA9121_MASK_SYS_STATUS_0_TEMP_CRIT)) {
		clear[R0] |= DA9121_MASK_SYS_MASK_0_M_TEMP_CRIT;
		chip->persistent[R0] &= ~DA9121_MASK_SYS_EVENT_0_E_TEMP_CRIT;
	}
	/* 0 TEMP_WARN */
	if ((chip->persistent[R0] & DA9121_MASK_SYS_EVENT_0_E_TEMP_WARN) &&
	    !(status[R0] & DA9121_MASK_SYS_STATUS_0_TEMP_WARN)) {
		clear[R0] |= DA9121_MASK_SYS_MASK_0_M_TEMP_WARN;
		chip->persistent[R0] &= ~DA9121_MASK_SYS_EVENT_0_E_TEMP_WARN;
	}
	/* 1 OV1 */
	if ((chip->persistent[R1] & DA9121_MASK_SYS_EVENT_1_E_OV1) &&
	    !(status[R1] & DA9121_MASK_SYS_STATUS_1_OV1)) {
		clear[R1] |= DA9121_MASK_SYS_MASK_1_M_OV1;
		chip->persistent[R1] &= ~DA9121_MASK_SYS_EVENT_1_E_OV1;
	}
	/* 1 UV1 */
	if ((chip->persistent[R1] & DA9121_MASK_SYS_EVENT_1_E_UV1) &&
	    !(status[R1] & DA9121_MASK_SYS_STATUS_1_UV1)) {
		clear[R1] |= DA9121_MASK_SYS_MASK_1_M_UV1;
		chip->persistent[R1] &= ~DA9121_MASK_SYS_EVENT_1_E_UV1;
	}
	/* 1 OC1 */
	if ((chip->persistent[R1] & DA9121_MASK_SYS_EVENT_1_E_OC1) &&
	    !(status[R1] & DA9121_MASK_SYS_STATUS_1_OC1)) {
		clear[R1] |= DA9121_MASK_SYS_MASK_1_M_OC1;
		chip->persistent[R1] &= ~DA9121_MASK_SYS_EVENT_1_E_OC1;
	}

	for (i = R0; i < REG_MAX_NUM - 1; i++) {
		if (clear[i]) {
			unsigned int reg = DA9121_REG_SYS_MASK_0 + i;
			unsigned int mbit = clear[i];

			ret = regmap_update_bits(chip->regmap, reg, mbit, 0);
			if (ret < 0) {
				dev_err(chip->dev,
					"Failed to unmask 0x%02x %d\n",
					reg, ret);
				return;
			}
		}
	}

	if (chip->persistent[R0] | chip->persistent[R1]) {
		delay = msecs_to_jiffies(chip->passive_delay);
		queue_delayed_work(system_freezable_wq, &chip->work, delay);
	}
}

static int da9121_get_voltage_buck(struct regulator_dev *rdev)
{
	struct da9121 *chip = rdev_get_drvdata(rdev);
	unsigned int val;
	int ret;

	ret = regmap_read(chip->regmap, DA9121_REG_BUCK_BUCK1_5, &val);
	if (ret < 0) {
		dev_err(chip->dev,
			"Cannot read BUCK_BUCK1_5 register: %d\n", ret);
		return ret;
	}

	val &= DA9121_MASK_BUCK_BUCK1_5_CH1_A_VOUT;

	return da9121_buck_voltage_lut[val];
}

static int da9121_floor_selector(struct regulator_dev *rdev, const int *lut,
				 unsigned int offset, unsigned int length,
		int min, int max,
		unsigned int *selector)
{
	struct da9121 *chip = rdev_get_drvdata(rdev);
	unsigned int i;
	unsigned int sel = 0;

	if (lut[offset] > max || lut[offset + length - 1] < min) {
		dev_err(chip->dev,
			"Requested voltage out of regulator capability\n");
		return -EINVAL;
	}

	for (i = offset; i < offset + length; i++) {
		if (lut[i] >= min) {
			sel = i;
			break;
		}
	}

	if (lut[sel] > max)
		return -EINVAL;

	*selector = sel;

	return 0;
}

static int da9121_set_voltage_buck(struct regulator_dev *rdev,
				   int min_uv, int max_uv,
				   unsigned int *selector)
{
	struct da9121 *chip = rdev_get_drvdata(rdev);
	unsigned int sel;
	unsigned int offset = DA9121_BUCK1_MIN_INDEX;
	unsigned int length = DA9121_BUCK1_MAX_INDEX -
		DA9121_BUCK1_MIN_INDEX + 1;
	int ret;

	if (min_uv < DA9121_BUCK1_MIN_UV ||
	    max_uv > DA9121_BUCK1_MAX_UV)
		return -EINVAL;

	ret = da9121_floor_selector(rdev, da9121_buck_voltage_lut,
				    offset, length, min_uv, max_uv, &sel);
	if (ret < 0)
		return ret;

	ret = regmap_update_bits(chip->regmap,
				 DA9121_REG_BUCK_BUCK1_5,
				 DA9121_MASK_BUCK_BUCK1_5_CH1_A_VOUT, sel);
	if (ret < 0) {
		dev_err(chip->dev,
			"Cannot update BUCK register: %d\n", ret);
		return ret;
	}

	*selector = sel;

	return ret;
}

static int da9121_get_current_limit(struct regulator_dev *rdev)
{
	int id = rdev_get_id(rdev);
	struct da9121 *chip = rdev_get_drvdata(rdev);
	unsigned int reg;
	unsigned int val;
	int ret;

	switch (id) {
	case DA9121_ID_BUCK1:
		reg = DA9121_REG_BUCK_BUCK1_2;
		break;
	default:
		dev_err(chip->dev, "Invalid regulator ID\n");
		return -EINVAL;
	}

	ret = regmap_read(chip->regmap, reg, &val);
	if (ret < 0) {
		dev_err(chip->dev, "Cannot read BUCK register: %d\n", ret);
		return ret;
	}

	if (val >= ARRAY_SIZE(da9121_buck_current_limit_lut))
		return -EINVAL;

	ret = da9121_buck_current_limit_lut[val];

	return ret;
}

static int da9121_ceiling_selector(struct regulator_dev *rdev, const int *lut,
				   unsigned int offset, unsigned int length,
				   int min, int max,
				   unsigned int *selector)
{
	struct da9121 *chip = rdev_get_drvdata(rdev);
	unsigned int i;
	unsigned int sel = 0;

	if (lut[offset] > max || lut[offset + length - 1] < min) {
		dev_err(chip->dev,
			"Requested voltage out of regulator capability\n");
		return -EINVAL;
	}

	for (i = offset + length - 1; i >= offset; i--) {
		if (lut[i] <= max) {
			sel = i;
			break;
		}
	}

	if (lut[sel] < min)
		return -EINVAL;

	*selector = sel;

	return 0;
}

static int da9121_set_current_limit(struct regulator_dev *rdev,
				    int min_ua, int max_ua)
{
	int id = rdev_get_id(rdev);
	struct da9121 *chip = rdev_get_drvdata(rdev);
	unsigned int sel;
	unsigned int reg;
	unsigned int mask;
	unsigned int offset = DA9121_BUCK_ILIM_MIN_INDEX;
	unsigned int length = DA9121_BUCK_ILIM_MAX_INDEX -
		DA9121_BUCK_ILIM_MIN_INDEX + 1;
	int ret;

	if (min_ua < DA9121_BUCK_ILIM_MIN_UV ||
	    max_ua > DA9121_BUCK_ILIM_MAX_UV)
		return -EINVAL;

	ret = da9121_ceiling_selector(rdev, da9121_buck_current_limit_lut,
				      offset, length, min_ua, max_ua, &sel);
	if (ret < 0)
		return ret;

	switch (id) {
	case DA9121_ID_BUCK1:
		reg = DA9121_REG_BUCK_BUCK1_2;
		mask = DA9121_MASK_BUCK_BUCK1_2_CH1_ILIM;
		break;
	default:
		dev_err(chip->dev, "Invalid regulator ID\n");
		return -EINVAL;
	}

	ret = regmap_update_bits(chip->regmap, reg, mask, (unsigned int)sel);
	if (ret < 0)
		dev_err(chip->dev, "Cannot update BUCK register: %d\n", ret);

	return ret;
}

static const struct regulator_ops da9121_buck_ops = {
	.enable = regulator_enable_regmap,
	.disable = regulator_disable_regmap,
	.is_enabled = regulator_is_enabled_regmap,
	.get_voltage = da9121_get_voltage_buck,
	.set_voltage = da9121_set_voltage_buck,
	.get_current_limit = da9121_get_current_limit,
	.set_current_limit = da9121_set_current_limit,
};

static struct dentry *debugfs_root;

static int debugfs_enable_get(void *data, u64 *val)
{
	struct regulator_dev *rdev = data;

	if (rdev && rdev->desc->ops->is_enabled)
		*val = rdev->desc->ops->is_enabled(rdev);
	else
		*val = ~0ULL;
	return 0;
}

static int debugfs_enable_set(void *data, u64 val)
{
	struct regulator_dev *rdev = data;

	if (rdev && rdev->desc->ops->enable && rdev->desc->ops->disable) {
		if (val)
			rdev->desc->ops->enable(rdev);
		else
			rdev->desc->ops->disable(rdev);
	}

	return 0;
}

static int debugfs_voltage_get(void *data, u64 *val)
{
	int ret;
	struct regulator_dev *rdev = data;

	ret = rdev->desc->ops->get_voltage(rdev);
	*val = ret / 1000;

	return 0;
}

static int debugfs_voltage_set(void *data, u64 val)
{
	unsigned int selector = 0;
	struct regulator_dev *rdev = data;

	val = val * 1000;

	return rdev->desc->ops->set_voltage(rdev,
					    val - rdev->desc->uV_step / 2,
					    val + rdev->desc->uV_step / 2,
					    &selector);
}

DEFINE_SIMPLE_ATTRIBUTE(fops_enable,
			debugfs_enable_get, debugfs_enable_set, "%llu\n");
DEFINE_SIMPLE_ATTRIBUTE(fops_ldo,
			debugfs_voltage_get, debugfs_voltage_set, "%llu\n");

static void da9121_regulator_debugfs_init(struct regulator_dev *rdev)
{
	debugfs_root = debugfs_create_dir(rdev->desc->name, NULL);

	if (IS_ERR_OR_NULL(debugfs_root)) {
		dev_warn(&rdev->dev, "Failed to create debugfs directory\n");
		rdev->debugfs = NULL;
		return;
	}

	debugfs_create_file("enable", S_IRUGO | S_IWUSR,
			    debugfs_root, rdev, &fops_enable);
	debugfs_create_file("voltage", S_IRUGO | S_IWUSR,
			    debugfs_root, rdev, &fops_ldo);
}

static struct of_regulator_match da9121_matches[] = {
	[DA9121_ID_BUCK1] = { .name = "buck1" },
};

/* DA9121 regulator model */
static struct regulator_desc da9121_regulators[] = {
	{
		.id = DA9121_ID_BUCK1,
		.name = "DA9121 BUCK1",
		.of_match = (const char *)&da9121_matches[DA9121_ID_BUCK1].name,
		.regulators_node = "regulators",
		.ops = &da9121_buck_ops,
		.type = REGULATOR_VOLTAGE,
		.enable_reg = DA9121_REG_BUCK_BUCK1_0,
		.enable_mask = DA9121_MASK_BUCK_BUCK1_0_CH1_EN,
		.owner = THIS_MODULE,
	}
};

static int da9121_parse_regulators_dt(struct da9121 *chip)
{
	struct da9121_dt_data *data = NULL;
	struct device_node *node;
	int num_matches;
	struct gpio_desc *gpio_enable;
	int i, n;

	node = of_get_child_by_name(chip->dev->of_node, "regulators");
	if (!node) {
		dev_err(chip->dev, "Regulators node not found\n");
		return -ENODEV;
	}

	num_matches = of_regulator_match(chip->dev, node, da9121_matches,
					 ARRAY_SIZE(da9121_matches));
	of_node_put(node);
	if (num_matches < 0) {
		dev_err(chip->dev, "Failed while matching regulators\n");
		return -EINVAL;
	}

	/* interrupt assumptions require at least one buck to be configured */
	if (num_matches == 0) {
		dev_err(chip->dev, "Did not match any regulators in the DT\n");
		return 0;
	}

	data = devm_kzalloc(chip->dev,
			    sizeof(struct da9121_dt_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->num_matches = (unsigned int)num_matches;

	n = 0;
	for (i = 0; i < ARRAY_SIZE(da9121_matches); i++) {
		if (!da9121_matches[i].init_data)
			continue;

		data->init_data[n] = da9121_matches[i].init_data;
		data->reg_node[n] = da9121_matches[i].of_node;

		gpio_enable = devm_gpiod_get(chip->dev, "enable",
					     GPIOD_OUT_LOW);
		if (IS_ERR(gpio_enable))
			data->gpio_ren[n] = -EINVAL;
		else
			data->gpio_ren[n] = desc_to_gpio(gpio_enable);
		n++;
	}

	chip->dt_data = data;

	return 0;
}

static inline int da9121_handle_notifier(
		struct da9121 *chip, struct regulator_dev *rdev,
		unsigned int event_bank, unsigned int event, unsigned int ebit)
{
	enum { R0 = 0, R1, R2, REG_MAX_NUM };
	unsigned long notification = 0;
	int ret;

	if (!(event & ebit)) {
		dev_warn(chip->dev,
			 "Invalid event or ebit 0x%02x\n",
			 event & ebit);
		return 0;
	}

	switch (event_bank) {
	case DA9121_REG_SYS_EVENT_0:
		switch (event & ebit) {
		case DA9121_MASK_SYS_EVENT_0_E_TEMP_CRIT:
			chip->persistent[R0] |=
				DA9121_MASK_SYS_EVENT_0_E_TEMP_CRIT;
			notification |= REGULATOR_EVENT_OVER_TEMP |
					REGULATOR_EVENT_DISABLE;
			break;
		case DA9121_MASK_SYS_EVENT_0_E_TEMP_WARN:
			chip->persistent[R0] |=
				DA9121_MASK_SYS_EVENT_0_E_TEMP_WARN;
			notification |= REGULATOR_EVENT_OVER_TEMP;
			break;
		default:
			dev_warn(chip->dev,
				 "Unhandled event in bank0 0x%02x\n",
				 event & ebit);
			ret = -EINVAL;
			break;
		}
		break;
	case DA9121_REG_SYS_EVENT_1:
		switch (event & ebit) {
		case DA9121_MASK_SYS_EVENT_1_E_OV1:
			chip->persistent[R1] |= DA9121_MASK_SYS_EVENT_1_E_OV1;
			notification |= REGULATOR_EVENT_REGULATION_OUT;
			break;
		case DA9121_MASK_SYS_EVENT_1_E_UV1:
			chip->persistent[R1] |= DA9121_MASK_SYS_EVENT_1_E_UV1;
			notification |= REGULATOR_EVENT_UNDER_VOLTAGE;
			break;
		case DA9121_MASK_SYS_EVENT_1_E_OC1:
			chip->persistent[R1] |= DA9121_MASK_SYS_EVENT_1_E_OC1;
			notification |= REGULATOR_EVENT_OVER_CURRENT;
			break;
		default:
			dev_warn(chip->dev,
				 "Unhandled event in bank1 0x%02x\n",
				 event & ebit);
			ret = -EINVAL;
			break;
		}
		break;
	default:
		dev_warn(chip->dev,
			 "Unhandled event bank 0x%02x\n", event_bank);
		ret = -EINVAL;
	}

	mutex_lock(&rdev->mutex);
	regulator_notifier_call_chain(rdev, notification, NULL);
	mutex_unlock(&rdev->mutex);

	return ret;
}

static irqreturn_t da9121_irq_handler(int irq, void *data)
{
	struct da9121 *chip = data;
	struct regulator_dev *rdev;
	enum { R0 = 0, R1, R2, REG_MAX_NUM };
	int event[REG_MAX_NUM] = { };
	int handled[REG_MAX_NUM] =  { };
	int mask[REG_MAX_NUM] = { };
	int ret = IRQ_NONE;
	int i;
	int err;

	err = regmap_bulk_read(chip->regmap, DA9121_REG_SYS_EVENT_0,
			       (void *)event, (size_t)R1);
	if (err < 0) {
		dev_err(chip->dev, "Failed to read EVENT registers %d\n", err);
		return IRQ_NONE;
	}

	err = regmap_bulk_read(chip->regmap, DA9121_REG_SYS_MASK_0,
			       (void *)mask, (size_t)R1);
	if (err < 0) {
		dev_err(chip->dev,
			"Failed to read MASK registers: %d\n", ret);
		return IRQ_NONE;
	}

	rdev = chip->rdev[DA9121_ID_BUCK1];

	/* 0 TEMP_CRIT */
	if (!(mask[R0] & DA9121_MASK_SYS_MASK_0_M_TEMP_CRIT) &&
	    (event[R0] & DA9121_MASK_SYS_EVENT_0_E_TEMP_CRIT)) {
		err = da9121_handle_notifier(chip, rdev,
					     DA9121_REG_SYS_EVENT_0, event[R0],
					     DA9121_MASK_SYS_EVENT_0_E_TEMP_CRIT);
		if (!err) {
			handled[R0] |= DA9121_MASK_SYS_EVENT_0_E_TEMP_CRIT;
			ret = IRQ_HANDLED;
		}
	}

	/* 0 TEMP_WARN */
	if (!(mask[R0] & DA9121_MASK_SYS_MASK_0_M_TEMP_WARN) &&
	    (event[R0] & DA9121_MASK_SYS_EVENT_0_E_TEMP_WARN)) {
		err = da9121_handle_notifier(chip, rdev,
					     DA9121_REG_SYS_EVENT_0, event[R0],
					     DA9121_MASK_SYS_EVENT_0_E_TEMP_WARN);
		if (!err) {
			handled[R0] |= DA9121_MASK_SYS_EVENT_0_E_TEMP_WARN;
			ret = IRQ_HANDLED;
		}
	}

	/* 1 PG1 */
	if (!(mask[R1] & DA9121_MASK_SYS_MASK_1_M_PG1) &&
	    (event[R1] & DA9121_MASK_SYS_EVENT_1_E_PG1)) {
		dev_warn(chip->dev, "Handled E_PG1\n");
		handled[R1] |= DA9121_MASK_SYS_EVENT_1_E_PG1;
		ret = IRQ_HANDLED;
	}

	/* 1 OV1 */
	if (!(mask[R1] & DA9121_MASK_SYS_MASK_1_M_OV1) &&
	    (event[R1] & DA9121_MASK_SYS_EVENT_1_E_OV1)) {
		err = da9121_handle_notifier(chip, rdev,
					     DA9121_REG_SYS_EVENT_1, event[R1],
					     DA9121_MASK_SYS_EVENT_1_E_OV1);
		if (!err) {
			handled[R1] |= DA9121_MASK_SYS_EVENT_1_E_OV1;
			ret = IRQ_HANDLED;
		}
	}

	/* 1 UV1 */
	if (!(mask[R1] & DA9121_MASK_SYS_MASK_1_M_UV1) &&
	    (event[R1] & DA9121_MASK_SYS_EVENT_1_E_UV1)) {
		err = da9121_handle_notifier(chip, rdev,
					     DA9121_REG_SYS_EVENT_1, event[R1],
					     DA9121_MASK_SYS_EVENT_1_E_UV1);
		if (!err) {
			handled[R1] |= DA9121_MASK_SYS_EVENT_1_E_UV1;
			ret = IRQ_HANDLED;
		}
	}

	/* 1 OC1 */
	if (!(mask[R1] & DA9121_MASK_SYS_MASK_1_M_OC1) &&
	    (event[R1] & DA9121_MASK_SYS_EVENT_1_E_OC1)) {
		err = da9121_handle_notifier(chip, rdev,
					     DA9121_REG_SYS_EVENT_1, event[R1],
					     DA9121_MASK_SYS_EVENT_1_E_OC1);
		if (!err) {
			handled[R1] |= DA9121_MASK_SYS_EVENT_1_E_OC1;
			ret = IRQ_HANDLED;
		}
	}

	/* DA9121_REG_SYS_EVENT_2 */
	if (!(mask[R2] & DA9121_MASK_SYS_MASK_2_M_GPIO2) &&
	    (event[R2] & DA9121_MASK_SYS_EVENT_2_E_GPIO2)) {
		dev_warn(chip->dev, "Handled E_GPIO2\n");
		handled[R2] |= DA9121_MASK_SYS_EVENT_2_E_GPIO2;
		ret = IRQ_HANDLED;
	}

	if (!(mask[R2] & DA9121_MASK_SYS_MASK_2_M_GPIO1) &&
	    (event[R2] & DA9121_MASK_SYS_EVENT_2_E_GPIO1)) {
		dev_warn(chip->dev, "Handled E_GPIO1\n");
		handled[R2] |= DA9121_MASK_SYS_EVENT_2_E_GPIO1;
		ret = IRQ_HANDLED;
	}

	if (!(mask[R2] & DA9121_MASK_SYS_MASK_2_M_GPIO0) &&
	    (event[R2] & DA9121_MASK_SYS_EVENT_2_E_GPIO0)) {
		dev_warn(chip->dev, "Handled E_GPIO0\n");
		handled[R2] |= DA9121_MASK_SYS_EVENT_2_E_GPIO0;
		ret = IRQ_HANDLED;
	}

	/* Mask the interrupts for persistent events OV, OC, UV, WARN, CRIT */
	for (i = R0; i < REG_MAX_NUM - 1; i++) {
		if (handled[i]) {
			unsigned int reg = DA9121_REG_SYS_MASK_0 + i;
			unsigned int mbit = handled[i];

			err = regmap_update_bits(chip->regmap, reg, mbit, mbit);
			if (err < 0) {
				dev_err(chip->dev,
					"Failed to mask 0x%02x interrupt %d\n",
					reg, err);
				return IRQ_NONE;
			}
		}
	}

	/* clear the events */
	if (handled[R0] | handled[R1] | handled[R2]) {
		err = regmap_bulk_write(chip->regmap, DA9121_REG_SYS_EVENT_0,
					(const void *)handled,
					(size_t)REG_MAX_NUM);
		if (err < 0) {
			dev_err(chip->dev, "Fail to write EVENTs %d\n", err);
			return IRQ_NONE;
		}
	}

	queue_delayed_work(system_freezable_wq, &chip->work, 0);

	return ret;
}

static int da9121_set_regulator_config(struct da9121 *chip)
{
	struct regulator_config config = { };
	unsigned int max_matches = chip->dt_data->num_matches;
	int ret;
	int i;

	if (max_matches > 1) {
		dev_err(chip->dev, "Too many regulators in the DT\n");
		return -EINVAL;
	}

	for (i = 0; i < max_matches; i++) {
		int id = da9121_regulators[i].id;
		int gpio_ren = chip->dt_data->gpio_ren[id];

		config.init_data = chip->dt_data->init_data[i];
		config.dev = chip->dev;
		config.driver_data = chip;
		config.regmap = chip->regmap;
		config.of_node = chip->dt_data->reg_node[i];

		switch (id) {
		case DA9121_ID_BUCK1:
			config.ena_gpio = gpio_ren;
			break;
		default:
			dev_err(chip->dev, "Invalid regulator ID\n");
			return -EINVAL;
		}

		chip->rdev[i] = devm_regulator_register(chip->dev,
							&da9121_regulators[i],
							&config);
		if (IS_ERR(chip->rdev[i])) {
			dev_err(chip->dev, "Failed to register regulator\n");
			ret = PTR_ERR(chip->rdev[i]);
			return ret;
		}

		da9121_regulator_debugfs_init(chip->rdev[i]);
	}

	return 0;
}

/* DA9121 chip register model */
static const struct regmap_range da9121_readable_ranges[] = {
	regmap_reg_range(DA9121_REG_SYS_STATUS_0, DA9121_REG_SYS_MASK_3),
	regmap_reg_range(DA9121_REG_SYS_CONFIG_2, DA9121_REG_SYS_CONFIG_3),
	regmap_reg_range(DA9121_REG_SYS_GPIO0_0, DA9121_REG_SYS_GPIO2_1),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_0, DA9121_REG_BUCK_BUCK1_6),
	regmap_reg_range(DA9121_REG_OTP_DEVICE_ID, DA9121_REG_OTP_CONFIG_ID),
};

static const struct regmap_range da9121_writeable_ranges[] = {
	regmap_reg_range(DA9121_REG_SYS_EVENT_0, DA9121_REG_SYS_MASK_3),
	regmap_reg_range(DA9121_REG_SYS_CONFIG_2, DA9121_REG_SYS_CONFIG_3),
	regmap_reg_range(DA9121_REG_SYS_GPIO0_0, DA9121_REG_SYS_GPIO2_1),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_0, DA9121_REG_BUCK_BUCK1_2),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_4, DA9121_REG_BUCK_BUCK1_6),
	regmap_reg_range(DA9121_REG_OTP_CUSTOMER_ID, DA9121_REG_OTP_CONFIG_ID),
};

static const struct regmap_range da9121_volatile_ranges[] = {
	regmap_reg_range(DA9121_REG_SYS_STATUS_0, DA9121_REG_SYS_EVENT_2),
	regmap_reg_range(DA9121_REG_SYS_GPIO0_0, DA9121_REG_SYS_GPIO2_1),
	regmap_reg_range(DA9121_REG_BUCK_BUCK1_0, DA9121_REG_BUCK_BUCK1_6),
};

static const struct regmap_access_table da9121_readable_table = {
	.yes_ranges = da9121_readable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9121_readable_ranges),
};

static const struct regmap_access_table da9121_writeable_table = {
	.yes_ranges = da9121_writeable_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9121_writeable_ranges),
};

static const struct regmap_access_table da9121_volatile_table = {
	.yes_ranges = da9121_volatile_ranges,
	.n_yes_ranges = ARRAY_SIZE(da9121_volatile_ranges),
};

/* DA9121 regmap config */
static struct regmap_config da9121_regmap_config = {
	.reg_bits = 8,
	.val_bits = 8,
	.max_register = DA9121_REG_OTP_CONFIG_ID,
	.rd_table = &da9121_readable_table,
	.wr_table = &da9121_writeable_table,
	.volatile_table = &da9121_volatile_table,
	.cache_type = REGCACHE_RBTREE,
};

static int da9121_assign_chip_model(struct i2c_client *i2c,
				    struct da9121 *chip)
{
	int ret = 0;

	chip->dev = &i2c->dev;
	chip->regmap = devm_regmap_init_i2c(i2c, &da9121_regmap_config);
	if (IS_ERR(chip->regmap)) {
		ret = PTR_ERR(chip->regmap);
		dev_err(chip->dev, "Failed to configure a register map: %d\n",
			ret);
	}

	return ret;
}

static int da9121_verify_chip_model(struct da9121 *chip)
{
	unsigned int device_id;
	unsigned int variant_id;
	unsigned int variant_mrc, variant_vrc;
	char *type;
	int ret;

	ret = regmap_read(chip->regmap, DA9121_REG_OTP_DEVICE_ID, &device_id);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to read device ID: %d\n", ret);
		return ret;
	}

	if (device_id != DA9121_DEVICE_ID) {
		dev_err(chip->dev, "Invalid device ID: 0x%02x\n", device_id);
		return -ENODEV;
	}

	ret = regmap_read(chip->regmap, DA9121_REG_OTP_VARIANT_ID, &variant_id);
	if (ret < 0) {
		dev_err(chip->dev, "Cannot read chip variant id.\n");
		return ret;
	}

	variant_vrc = variant_id & DA9121_MASK_OTP_VARIANT_ID_VRC;

	switch (variant_vrc) {
	case DA9121_VARIANT_VRC:
		type = "DA9121";
		break;
	default:
		type = "Unknown";
		break;
	}

	dev_dbg(chip->dev,
		"Device detected (device-ID: 0x%02X, var-ID: 0x%02X, %s)\n",
		 device_id, variant_id, type);

	variant_mrc = (variant_id & DA9121_MASK_OTP_VARIANT_ID_MRC) >>
		DA9121_SHIFT_OTP_VARIANT_ID_MRC;

	if (variant_mrc < DA9121_VARIANT_MRC_BASE) {
		dev_err(chip->dev,
			"Cannot support variant MRC: 0x%02X\n", variant_mrc);
		return -ENODEV;
	}

	return 0;
}

static int da9121_set_irq_masks(struct da9121 *chip, bool mask_irqs)
{
	unsigned int mask0, update0;
	unsigned int mask1, update1;
	unsigned int mask3;
	int ret;

	if (!chip->chip_irq) {
		dev_err(chip->dev, "Fail to get IRQ: %d\n",
			chip->chip_irq);
		return 0;
	}

	mask0 = DA9121_MASK_SYS_MASK_0_M_TEMP_CRIT |
		DA9121_MASK_SYS_MASK_0_M_TEMP_WARN;

	mask1 = DA9121_MASK_SYS_MASK_1_M_OV1 |
		DA9121_MASK_SYS_MASK_1_M_UV1 |
		DA9121_MASK_SYS_MASK_1_M_OC1;

	if (mask_irqs) {
		update0 = mask0;
		update1 = mask1;
	} else {
		update0 = 0;
		update1 = 0;
	}

	ret = regmap_update_bits(chip->regmap,
				 DA9121_REG_SYS_MASK_0,
				 mask0,
				 update0);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to write MASK 0 reg %d\n",
			ret);
		return ret;
	}

	ret = regmap_update_bits(chip->regmap,
				 DA9121_REG_SYS_MASK_1,
				 mask1,
				 update1);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to write MASK 1 reg %d\n",
			ret);
		return ret;
	}

	/* permanently disable IRQs for VR_HOT and PG1_STAT */
	mask3 = DA9121_MASK_SYS_MASK_3_M_VR_HOT |
		DA9121_MASK_SYS_MASK_3_M_PG1_STAT;

	ret = regmap_update_bits(chip->regmap,
				 DA9121_REG_SYS_MASK_3,
				 mask3,
				 mask3);
	if (ret < 0) {
		dev_err(chip->dev, "Failed to write MASK 3 reg %d\n",
			ret);
		return ret;
	}

	return 0;
}

static int da9121_config_irq(struct i2c_client *i2c,
			     struct da9121 *chip)
{
	struct gpio_desc *gpio_buck;
	unsigned int p_delay = DA9121_DEFAULT_POLLING_PERIOD_MS;
	int ret;

	gpio_buck = devm_gpiod_get(chip->dev, "buck", GPIOD_IN);
	ret = PTR_ERR_OR_ZERO(gpio_buck);

	switch (ret) {
	case 0:
		chip->chip_irq = gpiod_to_irq(gpio_buck);
		break;
	case -ENOENT:
		ret = 0;
		break;
	default:
		dev_err(chip->dev, "Failed to find buck gpio: %d\n", ret);
		/* fall through */
	case -EPROBE_DEFER:
		return ret;
	}

	if (!chip->chip_irq) {
		dev_err(chip->dev, "Fail to get IRQ: %d\n",
			chip->chip_irq);
		return 0;
	}

	if (!of_property_read_u32(chip->dev->of_node,
				  "dlg,irq-polling-delay-passive",
				  &p_delay)) {
		if (p_delay < DA9121_MIN_POLLING_PERIOD_MS ||
		    p_delay > DA9121_MAX_POLLING_PERIOD_MS) {
			dev_warn(chip->dev,
				 "Out-of-range polling period %d ms\n",
				 p_delay);
			p_delay = DA9121_DEFAULT_POLLING_PERIOD_MS;
		}
	}

	chip->passive_delay = p_delay;

	ret = devm_request_threaded_irq(chip->dev,
					chip->chip_irq, NULL,
					da9121_irq_handler,
					IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					"da9121", chip);
	if (ret != 0) {
		dev_err(chip->dev, "Failed IRQ request: %d\n",
			chip->chip_irq);
		return ret;
	}

	ret = da9121_set_irq_masks(chip, false);
	if (ret != 0) {
		dev_err(chip->dev, "Failed to set IRQ masks: %d\n",
			ret);
		return ret;
	}

	INIT_DELAYED_WORK(&chip->work, da9121_status_poll_on);
	dev_dbg(chip->dev, "Interrupt polling period set at %d ms\n",
		chip->passive_delay);

	return ret;
}

static const struct of_device_id da9121_dt_ids[] = {
	{ .compatible = "dlg,da9121" },
	{},
};
MODULE_DEVICE_TABLE(of, da9121_dt_ids);

static int da9121_i2c_probe(struct i2c_client *i2c,
			    const struct i2c_device_id *id)
{
	struct da9121 *chip;
	int ret;

	chip = devm_kzalloc(&i2c->dev, sizeof(struct da9121), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	ret = da9121_assign_chip_model(i2c, chip);
	if (ret < 0)
		return ret;

	ret = da9121_verify_chip_model(chip);
	if (ret < 0)
		return ret;

	ret = da9121_set_irq_masks(chip, true);
	if (ret != 0) {
		dev_err(chip->dev, "Failed to set IRQ masks: %d\n", ret);
		return ret;
	}

	ret = da9121_parse_regulators_dt(chip);
	if (ret < 0)
		return ret;

	ret = da9121_set_regulator_config(chip);
	if (ret < 0)
		return ret;

	ret = da9121_config_irq(i2c, chip);
	if (ret < 0)
		return ret;

	return ret;
}

static int da9121_i2c_remove(struct i2c_client *i2c)
{
	struct da9121 *chip = i2c_get_clientdata(i2c);
	int ret;

	ret = da9121_set_irq_masks(chip, true);
	if (ret != 0) {
		dev_err(chip->dev, "Failed to set IRQ masks: %d\n", ret);
		return ret;
	}

	cancel_delayed_work(&chip->work);
	debugfs_remove_recursive(debugfs_root);

	return 0;
}

static struct i2c_driver da9121_regulator_driver = {
	.driver = {
		.name = "da9121-regulator",
		.of_match_table = da9121_dt_ids,
	},
	.probe = da9121_i2c_probe,
	.remove = da9121_i2c_remove,
};

module_i2c_driver(da9121_regulator_driver);

MODULE_AUTHOR("Steve Twiss <stwiss.opensource@diasemi.com>");
MODULE_DESCRIPTION("DA9121 Buck regulator driver");
MODULE_LICENSE("GPL v2");

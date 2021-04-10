/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 */
#include <common.h>
#include <linux/types.h>
#include "sprdfb.h"

#define SPRDFB_I2C_TRY_NUM (4)
#define msleep(ms) udelay(ms*1000)

uint16_t sprdfb_i2c_init(struct sprdfb_device *dev)
{
	I2C_Init(10);
	return 1;
}

uint16_t sprdfb_i2c_uninit(struct sprdfb_device *dev)
{

	return 1;
}


/*write i2c, reg is 8 bit, val is 8 bit*/
static int32_t sprdfb_i2c_write_8bits(uint8_t addr, uint8_t reg, uint8_t val)
{
	uint8_t buf_w[2];
	uint32_t i = 0;
	int32_t ret = -1;

	if (0xFF == reg) {
		mdelay(val);
		FB_PRINT("sprdfb: [%s], sleep %d\n", __FUNCTION__,  val);
		return 0;
	}

	buf_w[0] = reg;
	buf_w[1] = val;
	for (i = 0; i < SPRDFB_I2C_TRY_NUM; i++) {
		ret = I2C_WriteCmdArr(addr, buf_w, 2, TRUE);
		if (ret != ERR_I2C_NONE) {
			printf("sprdfb:[%s] write panel reg fai, ret : %d, I2C w addr: 0x%x, \n",
			     __FUNCTION__, ret, addr);
			ret = -1;
			msleep(20);
		}else{
			ret = 0;
			break;
		}
	}
	return ret;
}


/*read i2c, reg is 8 bit, val is 8 bit*/
static int32_t sprdfb_i2c_read_8bits(uint8_t addr, uint8_t reg, uint8_t *val)
{
	uint32_t i;
	int32_t ret = -1;

	for (i = 0; i < SPRDFB_I2C_TRY_NUM; i++) {
		ret = I2C_WriteCmd(addr, reg , TRUE);
		if (ret != ERR_I2C_NONE) {
			printf("sprdfb:[%s]: read i2c reg fail(1), ret: %d, I2C r addr: 0x%x \n",
			     __FUNCTION__, ret, addr);
			*val = 0xff;
			ret = -1;
			msleep(20);
		}else{
			ret = 0;
			break;
		}
	}

	for (i = 0; i < SPRDFB_I2C_TRY_NUM; i++) {
		ret = I2C_ReadCmd(addr, *val, TRUE);
		if (ret != ERR_I2C_NONE) {
			printf("sprdfb:[%s]: read i2c reg fail(2), ret: %d, I2C r addr: 0x%x \n",
			     __FUNCTION__, ret, addr);
			*val = 0xff;
			ret = -1;
			msleep(20);
		}else{
			ret = 0;
			break;
		}
	}
	return ret;
}


/*write i2c, reg is 8 or 16 bit, val is 8 or 16bit*/
static int32_t sprdfb_i2c_write_16bits(uint8_t addr, uint16_t reg, BOOLEAN reg_is_8bit, uint16_t val, BOOLEAN val_is_8bit)
{
	uint8_t cmd[4] = { 0 };
	uint32_t i = 0;
	uint32_t cmd_num = 0;
	int32_t ret = -1;

	if ((reg_is_8bit && (0xff == reg))||(!reg_is_8bit &&(0xffff == reg))) {
		mdelay(val);
		FB_PRINT("sprdfb: [%s], sleep %d\n", __FUNCTION__,  val);
		return 0;
	}

	if (!reg_is_8bit) {
		cmd[cmd_num++] = (uint8_t) ((reg >> 8) & 0xff);
		cmd[cmd_num++] = (uint8_t) (reg & 0xff);
	} else {
		cmd[cmd_num++] = (uint8_t) reg;
	}

	if (!val_is_8bit) {
		cmd[cmd_num++] = (uint8_t) ((val >> 8) & 0xff);
		cmd[cmd_num++] = (uint8_t) (val & 0xff);
	} else {
		cmd[cmd_num++] = (uint8_t) val;
	}

	for (i = 0; i < SPRDFB_I2C_TRY_NUM; i++) {
		ret = I2C_WriteCmdArr(addr, cmd, cmd_num, TRUE);
		if (ret != ERR_I2C_NONE) {
			printf("srpdfb [%s]: write sensor reg fai, ret : %d, I2C w addr: 0x%x, \n",
				__FUNCTION__, ret, addr);
			ret = -1;
			msleep(20);
		} else {
			ret = 0;
			break;
		}
	}
	return ret;
}


/*read i2c, reg is 8 or 16 bit, val is 8 or 16bit*/
static int32_t sprdfb_i2c_read_16bits(uint8_t addr, uint16_t reg, BOOLEAN reg_is_8bit, uint16_t *val, BOOLEAN val_is_8bit)
{
	uint32_t i = 0;
	uint8_t cmd[2] = { 0 };
	uint16_t w_cmd_num = 0;
	uint16_t r_cmd_num = 0;
	uint8_t buf_r[2] = { 0 };
	int32_t ret = -1;

	if (!reg_is_8bit) {
		cmd[w_cmd_num++] = (uint8_t) ((reg >> 8) & 0xff);
		cmd[w_cmd_num++] = (uint8_t) (reg & 0xff);
	} else {
		cmd[w_cmd_num++] = (uint8_t) reg;
	}

	if (!val_is_8bit) {
		r_cmd_num = 2;
	} else {
		r_cmd_num = 1;
	}

	for (i = 0; i < SPRDFB_I2C_TRY_NUM; i++) {
		ret = I2C_WriteCmdArr(addr, cmd, w_cmd_num, TRUE);
		if (ret != ERR_I2C_NONE) {
			printf("srpdfb [%s]: read panel reg fail(1), ret : %d, I2C w addr: 0x%x, \n",
			     __FUNCTION__,ret, addr);
			*val = 0xffff;
			ret = -1;
			msleep(20);
		} else {
			*val = (r_cmd_num == 1) ? (uint16_t) buf_r[0]
			    : (uint16_t) ((buf_r[0] << 8) + buf_r[1]);
			ret = 0;
			break;
		}
	}

	for (i = 0; i < SPRDFB_I2C_TRY_NUM; i++) {
		ret = I2C_ReadCmdArr(addr, buf_r, r_cmd_num, TRUE);
		if (ret != ERR_I2C_NONE) {
			printf("srpdfb [%s]: read panel reg fail(2), ret : %d, I2C w addr: 0x%x, \n",
			     __FUNCTION__,ret, addr);
			*val = 0xffff;
			ret = -1;
			msleep(20);
		} else {
			*val = (r_cmd_num == 1) ? (uint16_t) buf_r[0]
			    : (uint16_t) ((buf_r[0] << 8) + buf_r[1]);
			ret = 0;
			break;
		}
	}
	return ret;
}


/*write i2c with burst mode*/
static int32_t sprdfb_i2c_write_burst(uint8_t addr, uint8_t* buf, int num)
{
	uint32_t i = 0;
	int32_t ret = -1;

	for (i = 0; i < SPRDFB_I2C_TRY_NUM; i++) {
		ret = I2C_WriteCmdArr(addr, buf, num, TRUE);
		if (ret != ERR_I2C_NONE) {
			printf("srpdfb [%s]: write i2c reg fail, ret : %d, I2C w addr: 0x%x, \n",
				__FUNCTION__, ret, addr);
			ret = -1;
			msleep(20);
		} else {
			ret = 0;
			break;
		}
	}

	return ret;
}

struct ops_i2c sprdfb_i2c_ops = {
	.i2c_write_8bits = sprdfb_i2c_write_8bits,
	.i2c_read_8bits = sprdfb_i2c_read_8bits,
	.i2c_write_16bits = sprdfb_i2c_write_16bits,
	.i2c_read_16bits = sprdfb_i2c_read_16bits,
	.i2c_write_burst = sprdfb_i2c_write_burst,
};


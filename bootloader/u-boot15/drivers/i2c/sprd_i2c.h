/*
 * sprd i2c 2015-5-26
 * 
 * liulanqing
 * 
 */

#ifndef __SPI_I2C_H__
#define __SPI_I2C_H__
/*Note: The defined below are for tiger and later chipset. */
/*If we don't use cmd buffer function, the define work well for the old chipset*/
/*register offset*/
#define I2C_CTL	0x0000
#define I2C_CMD	0x0004
#define I2C_CLKD0	0x0008
#define I2C_CLKD1	0x000C
#define I2C_RST	0x0010
#define I2C_CMD_BUF	0x0014
#define I2C_CMD_BUF_CTL	0x0018
#define I2C_STA_STO_DVD  0X001C

/*The corresponding bit of I2C_CTL register*/
#define I2C_CTL_INT	(1 << 0)	/* I2c interrupt */
#define I2C_CTL_ACK	(1 << 1)	/* I2c received ack value */
#define I2C_CTL_BUSY	 (1 << 2)	/* I2c data line value */
#define I2C_CTL_IE	(1 << 3)	/* I2c interrupt enable */
#define I2C_CTL_EN	(1 << 4)	/* I2c module enable */
#define I2C_CTL_SCL_LINE	(1 << 5)	/*scl line signal */
#define I2C_CTL_SDA_LINE	(1 << 6)	/* sda line signal */
#define I2C_CTL_NOACK_INT_EN	(1 << 7)	/* no ack int enable */
#define I2C_CTL_NOACK_INT_STS		(1 << 8)	/* no ack int status */
#define I2C_CTL_NOACK_INT_CLR	(1 << 9)	/* no ack int clear */
#define I2C_CTL_DUTY			(1 << 11)		 /* I2c DUTY*/


/*The corresponding bit of I2C_CMD register*/
#define I2C_CMD_INT_ACK	(1 << 0)	/* I2c interrupt clear bit */
#define I2C_CMD_TX_ACK	(1 << 1)	/* I2c transmit ack that need to be send */
#define I2C_CMD_WRITE	(1 << 2)	/* I2c write command */
#define I2C_CMD_READ	(1 << 3)	/* I2c read command */
#define I2C_CMD_STOP	(1 << 4)	/* I2c stop command */
#define I2C_CMD_START	(1 << 5)	/* I2c start command */
#define I2C_CMD_ACK	(1 << 6)	/* I2c received ack  value */
#define I2C_CMD_BUSY	(1 << 7)	/* I2c busy in exec commands */
#define I2C_CMD_DATA	0xFF00	/* I2c data received or data need to be transmitted */

/*The corresponding bit of I2C_RST register*/
#define I2C_RST_RST	(1 << 0)	/* I2c reset bit */

/*The corresponding bit of I2C_CMD_BUF_CTL register*/
#define I2C_CTL_CMDBUF_EN	(1 << 0)	/* Enable the cmd buffer mode */
#define I2C_CTL_CMDBUF_EXEC	(1 << 1)	/* Start to exec the cmd in the cmd buffer */

#endif  //__SPI_I2C_H__

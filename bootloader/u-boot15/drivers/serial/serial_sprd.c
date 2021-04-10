/*
 * (C) Copyright 2004
 */
#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <serial.h>
#include <linux/compiler.h>
#include "serial_sprd.h"
#include <dl_channel.h>


typedef struct UartPort
{
	void *regbase;
	void *apbbase;
	unsigned  int eb;
	int id;
	unsigned long int baudRate;
}uart_t;


#define CONSOLE_PORT CONFIG_CONS_INDEX
#define NUM_PORTS (sizeof(port)/sizeof(port[0]))
#define ARM_APB_CLK    26000000UL

DECLARE_GLOBAL_DATA_PTR;

static uart_t  port[] = {
	{
		(void *)(SPRD_UART0_PHYS),
		(void *)REG_AP_APB_APB_EB,
		BIT_UART0_EB,
		0,
	},
	{
		(void *)(SPRD_UART1_PHYS),
		(void *)REG_AP_APB_APB_EB,
		BIT_UART1_EB,
		1,
	}
};

static struct sprd_uart_regs *sprd_get_regs(int num)
{
	return (struct sprd_uart_regs *)(port[num].regbase);
}

static void sprd_apb_eb(int num)
{
	u32 temp = readl(port[num].apbbase);

	writel(temp |port[num].eb, port[num].apbbase);
}

static int sprd_init( int num, u32 baudrate)
{
	struct sprd_uart_regs *regs = sprd_get_regs(num);

	/* Set port for 8 bit, one stop, no parity  */
	writel(UARTCTL_BL8BITS | UARTCTL_SL1BITS, &regs->uart_ctrl0);
	/* Set baud rate  */
	writel(baudrate, &regs->uart_ckd0);
	return 0;
}

static int sprd_serial_init(void)
{
	u32 divider = ARM_APB_CLK / CONFIG_BAUDRATE;

	/* Enable UART*/
	sprd_apb_eb(CONSOLE_PORT);
#ifdef CONFIG_ZEBU
	printf("Using uart baudrate setting in SML\n");
#else
	sprd_init(CONSOLE_PORT, divider);
#endif
    return 0;
}

static void	sprd_serial_setbrg(void)
{
}

static void sprd_putc (int portnum, char c)
{
	struct sprd_uart_regs *regs = sprd_get_regs(portnum);

	while ( ((readl(&regs->uart_sts1) >> 8) & 0xff ))
	/* wait for room in the tx FIFO */ ;
	writeb(c, &regs->uart_txd);
	/* Ensure the last byte is written successfully */
	while ( ((readl(&regs->uart_sts1) >> 8) & 0xff ));
	return 0;
}

static int sprd_getc (int portnum)
{
	struct sprd_uart_regs *regs = sprd_get_regs(portnum);
	while (!(readl(&regs->uart_sts1) & 0xff))
	/* wait for character to arrive */ ;
	return (readb(&regs->uart_rxd) & 0xff);
}

static int sprd_tstc (int portnum)
{
	struct sprd_uart_regs *regs = sprd_get_regs(portnum);
	/* If receive fifo is empty, return false */
	return (readl(&regs->uart_sts1) & 0xff);
}

static int sprd_serial_getc(void)
{
	return sprd_getc (CONSOLE_PORT);
}

/*
 *  * Test whether a character is in the RX buffer
 *   */
static int sprd_serial_tstc(void)
{
	return sprd_tstc (CONSOLE_PORT);
}
static void	sprd_serial_putc(const char c)
{
	if (c == '\n')
		sprd_putc (CONSOLE_PORT, '\r');

	sprd_putc (CONSOLE_PORT, c);
}

static struct serial_device sprd_serial_drv = {
	.name	= "sprd_serial",
	.start	= sprd_serial_init,
	.stop	= NULL,
	.setbrg	= sprd_serial_setbrg,
	.getc	= sprd_serial_getc,
	.tstc	= sprd_serial_tstc,
	.putc	= sprd_serial_putc,
	.puts	= default_serial_puts,
};

void sprd_uart_initialize(void)
{
	serial_register(&sprd_serial_drv);
}
__weak struct serial_device *default_serial_console(void)
{
	return &sprd_serial_drv;
}


/*
   for uart download
*/
static unsigned int sprd_getHwDivider (unsigned int baudrate)
{
    return (unsigned int) (ARM_APB_CLK / baudrate  );
}

static int sprd_setBaudrate (struct FDL_ChannelHandler  *channel,  unsigned int baudrate)
{
	unsigned int divider;
	uart_t *port  = (uart_t *) channel->priv;
	struct sprd_uart_regs *regs = (struct sprd_uart_regs *)(port->regbase);

	divider = sprd_getHwDivider (baudrate);
	/* Set baud rate  */
	 regs->uart_ckd0 = LWORD (divider);

	 return 0;
}

static int sprd_read (struct FDL_ChannelHandler  *channel, const unsigned char *buf, unsigned int len)
{
	unsigned char *pstart = (unsigned char *) buf;
	const unsigned char *pend = pstart + len;
	uart_t *port  = (uart_t *) channel->priv;
	volatile struct sprd_uart_regs *regs = (struct sprd_uart_regs *)(port->regbase);

	while ( (pstart < pend)&& ((regs->uart_sts1)&0xff)){
	    *pstart++ = (regs->uart_rxd);
	}

	return pstart - (unsigned char *) buf;
}

static char sprd_getChar (struct FDL_ChannelHandler  *channel)
{
	uart_t *port  = (uart_t *) channel->priv;
	volatile  struct sprd_uart_regs *regs = (struct sprd_uart_regs *)(port->regbase);
	while(!((regs->uart_sts1)&0xff)){
	}
	return (regs->uart_rxd);
}

static int sprd_getSingleChar (struct FDL_ChannelHandler  *channel)
{
	char ch;
	uart_t *port  = (uart_t *) channel->priv;
	volatile struct sprd_uart_regs *regs = (struct sprd_uart_regs *)(port->regbase);

	while(!((regs->uart_sts1)&0xff)){
	}
	ch  = (regs->uart_rxd);
	return ch;

}
static int sprd_write (struct FDL_ChannelHandler  *channel, const unsigned char *buf, unsigned int len)
{
	const unsigned char *pstart = (const unsigned char *) buf;
	const unsigned char *pend = pstart + len;
	uart_t *port  = (uart_t *) channel->priv;
	volatile struct sprd_uart_regs *regs = (volatile struct sprd_uart_regs *)(port->regbase);
	unsigned char tx_fifo_cnt = 0;

	while (pstart < pend){
		while ((((regs->uart_sts1)>>8)&0xff)){
		}
		regs->uart_txd = (*pstart);
		++pstart;
	}

	while ((((regs->uart_sts1)>>8)&0xff)){
	}

	return pstart - (const unsigned char *) buf;
}

static int sprd_putChar (struct FDL_ChannelHandler  *channel, const unsigned char ch)
{
	uart_t *port  = (uart_t *) channel->priv;
	volatile struct sprd_uart_regs *regs = (struct sprd_uart_regs *)(port->regbase);
	while (((regs->uart_sts1)>>8)&0xff){
	}
	regs->uart_txd  = ch;
	/* Ensure the last byte is written successfully */
	while (((regs->uart_sts1)>>8)&0xff){
	/* Do nothing */
	}
	return 0;
}
static int sprd_close (struct FDL_ChannelHandler  *channel)
{
	return 0;
}
static int sprd_open (struct FDL_ChannelHandler  *channel, unsigned int baudrate)
{
	uart_t *port  = (uart_t *) channel->priv;
	u32 divider = ARM_APB_CLK / baudrate;

	sprd_apb_eb(port->id);
	sprd_init(port->id, divider);
    return 0;
}

/****
   FDL2 download struct
***/
FDL_ChannelHandler_T  gUart1Channel = {
	.Open = sprd_open,
	.Read = sprd_read,
	.GetChar = sprd_getChar,
	.GetSingleChar = sprd_getSingleChar,
	.Write = sprd_write,
	.PutChar = sprd_putChar,
	.SetBaudrate =sprd_setBaudrate,
	.DisableHDLC = NULL,
	.Close = sprd_close,
	.priv = &port[0],
};
FDL_ChannelHandler_T  gUart0Channel = {
	.Open = sprd_open,
	.Read = sprd_read,
	.GetChar = sprd_getChar,
	.GetSingleChar = sprd_getSingleChar,
	.Write = sprd_write,
	.PutChar = sprd_putChar,
	.SetBaudrate =sprd_setBaudrate,
	.DisableHDLC = NULL,
	.Close = sprd_close,
	.priv = &port[1],
};

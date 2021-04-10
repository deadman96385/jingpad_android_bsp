#include <common.h>
#include <asm/crashlog/cpu.h>
#include <asm/crashlog/io.h>
#include <asm/crashlog/atomic.h>
#include <asm/crashlog/spinlock.h>

/* max. dump size in 32-bit words */
#define MAX_CRASH_LOG 1024

#define CRASH_REG_CTRL 0x158
#define CRASH_REG_DATA 0x153

#define PORT_ID_PUNIT  0x04

#define OP_PUNIT_READ  0x06
#define OP_PUNIT_WRITE 0x07

#define CONFIG_MCR  0xd0
#define CONFIG_MDR  0xd4
#define CONFIG_MCRX 0xd8

#define CRASH_CTRL_RUN_BUSY (1 << 31)
#define CRASH_CTRL_START    (1 << 5)
#define CRASH_CTRL_END      (1 << 4)
#define CRASH_CTRL_SKIP     (1 << 3)
#define CRASH_CTRL_STOP     (1 << 2)
#define CRASH_CTRL_VALID_EN (1 << 1)
#define CRASH_CTRL_VALID    (1)

static uint32_t crash_data[MAX_CRASH_LOG];

static DEFINE_SPINLOCK(msg_lock);
static DEFINE_SPINLOCK(pci_config_lock);

static atomic_t cpus_started = 1;

/**
 * config_read() - Read 32-bit PCI configuration register of device 0/0/0
 * @offset: Configuration register offset (8 bits)
 *
 * Return: Configuration register value
 */
static uint32_t config_read(uint32_t offset)
{
	uint32_t data;

	spin_lock(&pci_config_lock);
	outl(0x80000000 | offset, 0xcf8);
	data = inl(0xcfc);
	spin_unlock(&pci_config_lock);

	return data;
}

/**
 * config_write() - Write 32-bit PCI configuration register of device 0/0/0
 * @offset: Configuration register offset (8 bits)
 * @data: Value to write (32 bits)
 */
static void config_write(uint32_t offset, uint32_t data)
{
	spin_lock(&pci_config_lock);
	outl(0x80000000 | offset, 0xcf8);
	outl(data, 0xcfc);
	spin_unlock(&pci_config_lock);
}

/**
 * punit_reg_read() - Read P-unit register on IOSF bus
 * @offset: register offset (32 bits)
 *
 * Return: Register value (32 bits)
 */
static uint32_t punit_reg_read(uint32_t offset)
{
	uint32_t command = 0xf0;
	uint32_t data;

	command |= OP_PUNIT_READ << 24;
	command |= PORT_ID_PUNIT << 16;
	command |= (offset & 0xff) << 8;

	spin_lock(&msg_lock);
	config_write(CONFIG_MCRX, offset & 0xffffff00);
	config_write(CONFIG_MCR, command);
	data = config_read(CONFIG_MDR);
	spin_unlock(&msg_lock);

	return data;
}

/**
 * punit_reg_read() - Read P-unit register on IOSF bus
 * @offset: register offset (32 bits)
 * @data: value to write (32 bits)
 */
static void punit_reg_write(uint32_t offset, uint32_t data)
{
	uint32_t command = 0xf0;

	command |= OP_PUNIT_WRITE << 24;
	command |= PORT_ID_PUNIT << 16;
	command |= (offset & 0xff) << 8;

	spin_lock(&msg_lock);
	config_write(CONFIG_MDR, data);
	config_write(CONFIG_MCRX, offset & 0xffffff00);
	config_write(CONFIG_MCR, command);
	spin_unlock(&msg_lock);
}

/**
 * crash_data_receive() - Receive crash log data from P-unit
 * @data: buffer for crash log data
 * @n_max: buffer size in 32-bit words
 *
 * Return: Number of 32-bit words received
 */
int crash_data_receive(uint32_t *data, int n_max)
{
	uint32_t ctrl;
	int i, t;

	ctrl = CRASH_CTRL_START;
	punit_reg_write(CRASH_REG_CTRL, ctrl);

	for (t = 0; t < 1000; t += 1) {
		ctrl = punit_reg_read(CRASH_REG_CTRL);

		if (ctrl & CRASH_CTRL_VALID_EN)
			break;
	}

	if (!(ctrl & CRASH_CTRL_VALID_EN))
		return -1;

	/* check if data available */
	if (!(ctrl & CRASH_CTRL_VALID))
		return 0;

	for (i = 0; i < n_max; i += 1)	{
		for (t = 0; t < 1000; t += 1) {
			ctrl = punit_reg_read(CRASH_REG_CTRL);

			if (ctrl & CRASH_CTRL_RUN_BUSY)
				break;

			if (ctrl & CRASH_CTRL_STOP)
				break;
		}

		/* data transfer complete */
		if (ctrl & CRASH_CTRL_STOP)
			break;

		if (!(ctrl & CRASH_CTRL_RUN_BUSY)) {
			printf("crashlog timeout\n");
			break;
		}

		data[i] = punit_reg_read(CRASH_REG_DATA);
		ctrl &= ~CRASH_CTRL_RUN_BUSY;
		punit_reg_write(CRASH_REG_CTRL, ctrl);
	}

	/* acknowledge end of transfer */
	ctrl |= CRASH_CTRL_END;
	punit_reg_write(CRASH_REG_CTRL, ctrl);

	return i;
}

void mp_callback()
{
	atomic_inc(&cpus_started);

	while (1) {
		asm volatile("hlt");
	}
}

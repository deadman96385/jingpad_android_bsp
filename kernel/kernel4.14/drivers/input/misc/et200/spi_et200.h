#ifndef __ET200_SPI_DRV__
#define __ET200_SPI_DRV__

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>

#include <linux/spi/spi.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/of_gpio.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>

//#include <mt-plat/mt_gpio.h>

//#include <mt_spi.h>
//#include "mt_spi_hal.h"

#include <linux/miscdevice.h>
#include <asm/ioctl.h>

#include <linux/sched.h>


#define ET200_SPI_USE_MMAP

#define ET200_DEBUG

#ifdef ET200_DEBUG
#define SPI_MSG_DUMP
#define ET200_SPI_TRACE  (printk(KERN_ALERT"["ET200_NAME"]:%5d: <%s> IN\n", __LINE__, __func__))
#define ET200_SPI_TRACE_OUT  (printk(KERN_ALERT"["ET200_NAME"]:%5d: <%s> OUT\n", __LINE__, __func__))
#define ET200_SPI_INFO(fmt, args...)  (printk(KERN_INFO "["ET200_NAME"]:%5d: <%s> " fmt, __LINE__, __func__,##args))
#define ET200_SPI_ARRAY_WITH_PREFIX(prefix, buffer, length)   \
	do{                                                 \
		ET200_SPI_INFO("%s\n", prefix);                    \
		print_hex_dump(KERN_ALERT, "["ET200_NAME"]",       \
			DUMP_PREFIX_OFFSET, 16, 1,                  \
			buffer,                                     \
			min_t(size_t, length, 1024),                \
			true);                                      \
	}while(0)
#else 
#define ET200_SPI_TRACE
#define ET200_SPI_TRACE_OUT
#define ET200_SPI_INFO(fmt, args...)
#define ET200_SPI_ARRAY_WITH_PREFIX(prefix, buffer, length)    \
	do{                                                 	\
	}while(0)
#endif
#define ET200_SPI_ERR(fmt, args...)  (printk(KERN_ALERT "["ET200_NAME"]:%5d: <%s> " fmt, __LINE__, __func__,##args))

/*
#define    GPIO_SPI_RB_GPIO           	    (65|0x80000000)	//EINT4
#define    GPIO_SPI_WAKEUP_GPIO             (66|0x80000000)	//EINT3

#define    GPIO_TEST_THREE_GPIO             (112|0x80000000)
#define    GPIO_TEST_FOUR_GPIO         	    (109|0x80000000)

#define    GPIO_SPI_CS_PIN                  (237|0x80000000)
#define    GPIO_SPI_SCK_PIN                 (234|0x80000000)
#define    GPIO_SPI_MOSI_PIN                (236|0x80000000)
#define    GPIO_SPI_MISO_PIN                (235|0x80000000)
*/

#define    MAX_PACKET_LEN	1024			//max packet len on mtk6572
#define    MAX_TRANSFER_LEN	(256*MAX_PACKET_LEN)	//max transfer len on mtk6572

#define    XFER_BUF_SIZE	256*1024
#define    BITS_PER_WORD	8
#define    ET200_NAME		"et200_spi"
#define    ET200_DESC		"et200 chip driver"
#define    ET200_VERSION	"1.0"

#define ET200_IOCTL_MAGIC 0xa5
#define ET200_CHIP_CON_NEW 213

/*spi config*/
#if 0
static struct mt_chip_conf et200_spi_conf=
{
	.setuptime = 4, 
	.holdtime = 4,  
	.high_time = 2,
	.low_time =  2,
	//de-assert mode
	/*
	.cs_idletime = 30, 
	.pause = 0,
	.deassert = 1,
	*/

	//pause mode
	///*		
	.cs_idletime = 1,
	.pause = 1,
	.deassert = 0,
	//*/

	.cpol = 1,
	.cpha = 1,

	.rx_mlsb = 1,  
	.tx_mlsb = 1,

	.tx_endian = 0, 
	.rx_endian = 0,

	.com_mod = DMA_TRANSFER,   //DMA_TRANSFER FIFO_TRANSFER
	
	.finish_intr = 1,
	.ulthigh = 0,
	.tckdly = 2,
};
#endif 
struct veb_et200_data {
	struct spi_device    *spi;
	struct miscdevice 	*miscdev;
	struct mutex        dev_lock;
	u8            *buffer;

#define ET200_MMAP_SIZE       0x200000
	struct mutex 		mmap_lock;
	void 				*mmap_addr;
#define ET200_ALREADY_MAPPED	0x5a
#define ET200_NOT_MAPPED		0	
	u8					mmapped;
};

#define CRC8 1
#define CRC16 2
#define CRC32 3

typedef struct
{
    int len;
    int iCrc;
    unsigned char *recv;
    unsigned char b_con;
}et200_duplex_con;



#endif

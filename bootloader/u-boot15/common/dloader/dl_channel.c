#include <dl_channel.h>
#include <config.h>
//#include <usb/usb_boot.h>

#define BOOT_FLAG_USB                   (0x5A)
#define BOOT_FLAG_UART1                 (0x6A)
#define BOOT_FLAG_UART0                 (0x7A)


/******************************************************************************/
//  Description:    find a useable channel
//  Global resource dependence:
//  Author:         junqiang.wang
//  Note:
/******************************************************************************/
extern struct FDL_ChannelHandler gUart0Channel, gUart1Channel;
extern struct FDL_ChannelHandler gUSBChannel;

struct FDL_ChannelHandler *FDL_ChannelGet()
{
    unsigned int bootMode = 0;
    char ch;

    struct FDL_ChannelHandler *channel;
	bootMode = BOOT_FLAG_USB;
#ifdef CONFIG_UART_DOWNLOAD
	bootMode = BOOT_FLAG_UART1;
#endif

    switch (bootMode)
    {
        case BOOT_FLAG_UART1:
            channel = &gUart1Channel;
            channel -> Open(channel, 115200);
            break;
        case BOOT_FLAG_UART0:
            channel = &gUart0Channel;
            break;
        case BOOT_FLAG_USB:
            channel = &gUSBChannel;
            break;
        default:
            channel = &gUSBChannel;
            break;
    }
    return channel;
}

struct FDL_ChannelHandler *FDL_USBChannel()
{
	return &gUSBChannel;
}


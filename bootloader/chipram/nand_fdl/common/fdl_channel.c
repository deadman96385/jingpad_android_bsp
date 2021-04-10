#include <fdl_channel.h>
#include <sci_types.h>

extern struct FDL_ChannelHandler gUSBChannel;
extern struct FDL_ChannelHandler gUart0Channel;
extern struct FDL_ChannelHandler gUart1Channel;

//#define FDL_UART0_CHANNEL_USE

/******************************************************************************/
//  Description:    find a useable channel
//  Global resource dependence:
//  Author:         junqiang.wang
//  Note:
/******************************************************************************/
PUBLIC struct FDL_ChannelHandler *FDL_ChannelGet()
{
    uint32 bootMode = 0;
    char ch;

    struct FDL_ChannelHandler *channel;
    bootMode = FDL_GetBootMode();

    switch (bootMode)
    {
        case BOOT_FLAG_UART1:
            channel = &gUart1Channel;
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
PUBLIC struct FDL_ChannelHandler *FDL_USBChannel(void)
{
	return &gUSBChannel;
}

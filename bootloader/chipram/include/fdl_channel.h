#ifndef __FDL_CHANNEL_H_
#define __FDL_CHANNEL_H_
typedef enum channe_mode_sel{
	BOOT_FLAG_USB = 0x5A,
	BOOT_FLAG_UART1 = 0x6A,
	BOOT_FLAG_UART0 = 0x7A
}chan_mode_s;

typedef struct FDL_ChannelHandler
{
    int (*Open) (struct FDL_ChannelHandler *channel, unsigned int  baudrate);
    int (*Read) (struct FDL_ChannelHandler *channel, const unsigned char *buf, unsigned int  len);
    char (*GetChar) (struct FDL_ChannelHandler *channel);
    int (*GetSingleChar) (struct FDL_ChannelHandler *channel);
    int (*Write) (struct FDL_ChannelHandler *channel, const unsigned char *buf, unsigned int  len);
    int (*PutChar) (struct FDL_ChannelHandler *channel, const unsigned char ch);
    int (*SetBaudrate) (struct FDL_ChannelHandler *channel, unsigned int  baudrate);
    int (*Close) (struct FDL_ChannelHandler *channel);
    void   *priv;
} FDL_ChannelHandler_T;

struct FDL_ChannelHandler *FDL_ChannelGet();
struct FDL_ChannelHandler *FDL_USBChannel(void);
extern unsigned int FDL_GetBootMode (void);

#endif

#ifndef __FDL_CHANNEL_H_
#define __FDL_CHANNEL_H_


typedef struct FDL_ChannelHandler
{
    int (*Open) (struct FDL_ChannelHandler *channel, unsigned int  baudrate);
    int (*Read) (struct FDL_ChannelHandler *channel, const unsigned char *buf, unsigned int  len);
    int (*StartReadRawData) (struct FDL_ChannelHandler *channel, const unsigned char *buf, unsigned int  len);
    int (*FinishReadRawData) (struct FDL_ChannelHandler *channel, const unsigned char *buf, unsigned int  len);
    char (*GetChar) (struct FDL_ChannelHandler *channel);
    int (*GetSingleChar) (struct FDL_ChannelHandler *channel);
    int (*Write) (struct FDL_ChannelHandler *channel, const unsigned char *buf, unsigned int  len);
    int (*PutChar) (struct FDL_ChannelHandler *channel, const unsigned char ch);
    int (*SetBaudrate) (struct FDL_ChannelHandler *channel, unsigned int  baudrate);
    int (*DisableHDLC) (struct FDL_ChannelHandler *channel, int  disabled);
    int (*SupportRawDataProc) (struct fdl_channelhandler  *channel);
    int (*Close) (struct FDL_ChannelHandler *channel);
    void   *priv;
} FDL_ChannelHandler_T;

struct FDL_ChannelHandler *FDL_ChannelGet();
struct FDL_ChannelHandler *FDL_USBChannel();

#endif

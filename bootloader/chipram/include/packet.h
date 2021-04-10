
#ifndef PACKET_H
#define PACKET_H

#include <cmd_def.h>
#include <asm/arch/soc_config.h>


typedef enum
{
    PKT_NONE = 0,
    PKT_HEAD,
    PKT_GATHER,
    PKT_RECV,
    PKT_ERROR
} pkt_flag_s;

struct PACKET_BODY_tag
{
    unsigned short  type;
    unsigned short  size;
#ifndef FPGA_TRACE_DOWNLOAD
    unsigned char   content[ MAX_PKT_SIZE ];
#else
    char*    content;
#endif
};

typedef struct PACKET_tag
{
    struct PACKET_tag      *next;

    int     pkt_state;  // used by recv handle, see pkt_flag_s
    int     data_size;
    int     ack_flag;
    struct PACKET_BODY_tag packet_body;
#if 0
    struct PACKET_BODY_tag
    {
        unsigned short  type;
        unsigned short  size;
        unsigned char   content[ MAX_PKT_SIZE ];
    } packet_body;
#endif
} PACKET_T;

#define PACKET_HEADER_SIZE   4   // (type + size)


void FDL_PacketInit (void);

PACKET_T *FDL_MallocPacket (void);

void FDL_FreePacket (PACKET_T *ptr);

// Receive a packet, after handle it, should call FDL_FreePacket to release it.
PACKET_T   *FDL_GetPacket (void);

//
// This function be called when system is in idle to process the input char.
//
void FDL_PacketDoIdle (void);

// send the packet.
void FDL_SendPacket (PACKET_T *packet_ptr);

void FDL_SendAckPacket (cmd_pkt_type pkt_type);

extern struct FDL_ChannelHandler *gFdlUsedChannel;
#endif  // PACKET_H


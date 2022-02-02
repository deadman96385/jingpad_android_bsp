#ifndef _PAM_WIFI_PAM_WIFI_REG_H
#define _PAM_WIFI_PAM_WIFI_REG_H

#define BIT_(x) ((u32 )((u32 )1 << x))

extern u64 pam_wifi_base_addr_remap;
#define PAM_WIFI_REG_BASE  pam_wifi_base_addr_remap

//[14:8] == 7'b000_0000
#define PSEL_RF              (PAM_WIFI_REG_BASE+(0x00<<8))
//[14:7] == 8'b000_0001_0       
#define PSEL_DL_TYPE1           (PAM_WIFI_REG_BASE+(0x100))
//[14:7] == 8'b000_0001_1
#define PSEL_DL_TYPE2           (PAM_WIFI_REG_BASE+(0x180))
//[14:7] == 8'b000_0010_0
#define PSEL_DL_TYPE3           (PAM_WIFI_REG_BASE+(0x200))
//[14:7] == 8'b000_0010_1
#define PSEL_DL_TYPE4           (PAM_WIFI_REG_BASE+(0x280))
//[14:7] == 8'b000_0011_0
#define PSEL_DL_FREE         (PAM_WIFI_REG_BASE+(0x300))
//[14:7] == 8'b000_0011_1
#define PSEL_UL              (PAM_WIFI_REG_BASE+(0x380))

//[14:11] == 4'b000_1
#define PSEL_RAM1            (PAM_WIFI_REG_BASE+(0x800))
//[14:11] == 4'b001_0
#define PSEL_RAM2            (PAM_WIFI_REG_BASE+(0x1000))
//[14:11] == 4'b001_1
#define PSEL_RAM3            (PAM_WIFI_REG_BASE+(0x1800))
//[14:11] == 4'b010_0
#define PSEL_RAM4            (PAM_WIFI_REG_BASE+(0x2000))
//[14:9] == 6'b010_100
#define PSEL_RAM5            (PAM_WIFI_REG_BASE+(0x2800))
//[14:9] == 6'b010_110
#define PSEL_RAM6            (PAM_WIFI_REG_BASE+(0x2c00))

#define REG_UL_AP_FILLED_FIFO_BASE_ADDRL       (PAM_WIFI_REG_BASE + 0x0000)
#define REG_UL_AP_FILLED_FIFO_BASE_ADDRH       (PAM_WIFI_REG_BASE + 0x0004)
#define REG_UL_AP_FREE_FIFO_BASE_ADDRL       (PAM_WIFI_REG_BASE + 0x0008)
#define REG_UL_AP_FREE_FIFO_BASE_ADDRH       (PAM_WIFI_REG_BASE + 0x000C)
#define REG_DL_AP_FILLED_FIFO_BASE_ADDRL       (PAM_WIFI_REG_BASE + 0x0010)
#define REG_DL_AP_FILLED_FIFO_BASE_ADDRH       (PAM_WIFI_REG_BASE + 0x0014)
#define REG_DL_AP_FREE_FIFO_BASE_ADDRL       (PAM_WIFI_REG_BASE + 0x0018)
#define REG_DL_AP_FREE_FIFO_BASE_ADDRH       (PAM_WIFI_REG_BASE + 0x001C)
#define REG_UL_AP_FREE_FIFO_STS_BASE_ADDRL       (PAM_WIFI_REG_BASE + 0x0020)
#define REG_UL_AP_FREE_FIFO_STS_BASE_ADDRH       (PAM_WIFI_REG_BASE + 0x0024)
#define REG_UL_AP_FILLED_FIFO_STS_BASE_ADDRL       (PAM_WIFI_REG_BASE + 0x0028)
#define REG_UL_AP_FILLED_FIFO_STS_BASE_ADDRH       (PAM_WIFI_REG_BASE + 0x002C)
#define REG_DL_AP_FREE_FIFO_STS_BASE_ADDRL       (PAM_WIFI_REG_BASE + 0x0030)
#define REG_DL_AP_FREE_FIFO_STS_BASE_ADDRH       (PAM_WIFI_REG_BASE + 0x0034)
#define REG_DL_AP_FILLED_FIFO_STS_BASE_ADDRL       (PAM_WIFI_REG_BASE + 0x0038)
#define REG_DL_AP_FILLED_FIFO_STS_BASE_ADDRH       (PAM_WIFI_REG_BASE + 0x003C)
#define REG_CFG_UL_FILLED_BUFFER_CTRL       (PAM_WIFI_REG_BASE + 0x0040)
#define REG_CFG_UL_FREE_BUFFER_CTRL       (PAM_WIFI_REG_BASE + 0x0044)
#define REG_CFG_DL_BUFFER_CTRL       (PAM_WIFI_REG_BASE + 0x0048)
#define REG_DDR_MAPPING_OFFSET_L	(PAM_WIFI_REG_BASE + 0x004C)
#define REG_DDR_MAPPING_OFFSET_H	(PAM_WIFI_REG_BASE + 0x0050)
#define REG_MSDU_BASE_ADDRL		(PAM_WIFI_REG_BASE + 0x0054)
#define REG_MSDU_BASE_ADDRH		(PAM_WIFI_REG_BASE + 0x0058)
#define REG_UL_NODE_INFO_CONFIG	(PAM_WIFI_REG_BASE + 0x005C)
#define REG_CFG_START				(PAM_WIFI_REG_BASE + 0x0060)
#define REG_AXI_MST_CFG			(PAM_WIFI_REG_BASE + 0x0064)
#define REG_AXI_OS_CFG				(PAM_WIFI_REG_BASE + 0x0068)
#define REG_CH_WR_PRIO				(PAM_WIFI_REG_BASE + 0x006C)
#define REG_CH_RD_PRIO				(PAM_WIFI_REG_BASE + 0x0070)
#define REG_BUFFER_TIMEOUT_VAL           ( PAM_WIFI_REG_BASE + 0x0074 )
#define REG_IP_VER                       ( PAM_WIFI_REG_BASE + 0x0078 )
#define REG_INT_EN                       ( PAM_WIFI_REG_BASE + 0x007C )
#define REG_INT_CLR                      ( PAM_WIFI_REG_BASE + 0x0080 )
#define REG_INT_RAW                      ( PAM_WIFI_REG_BASE + 0x0084 )
#define REG_INT_STS                      ( PAM_WIFI_REG_BASE + 0x0088 )
#define REG_IPI_CLR_BASE_ADDRL                    ( PAM_WIFI_REG_BASE + 0x008C )
#define REG_IPI_CLR_BASE_ADDRH                    ( PAM_WIFI_REG_BASE + 0x0090 )
#define REG_COMMON_FIFO_STS_UPDATE                ( PAM_WIFI_REG_BASE + 0x0094 )
#define REG_TOS_PRIO                              ( PAM_WIFI_REG_BASE + 0x0098 )
#define REG_SW_DEBUG_MEM_BASE_ADDR                ( PAM_WIFI_REG_BASE + 0x009C )
#define REG_INDEX_SEARCH_DEPTH                    ( PAM_WIFI_REG_BASE + 0x00A0 )
#define REG_INDEX_MISS_ADDR_L                     ( PAM_WIFI_REG_BASE + 0x00A4 )
#define REG_INDEX_MISS_ADDR_H                     ( PAM_WIFI_REG_BASE + 0x00A8 )
#define REG_COMMON_FIFO_OFFSET                    ( PAM_WIFI_REG_BASE + 0x00AC )
#define REG_SW_DEBUG_CURT_STS                     ( PAM_WIFI_REG_BASE + 0x00B0 )
#define REG_SW_DEBUG_RESP_ERROR                   ( PAM_WIFI_REG_BASE + 0x00B4 )
#define REG_DUMMY_REG                             ( PAM_WIFI_REG_BASE + 0x00B8 )

#define REG_UL_AP_FILLED_FIFO_BASE_ADDRL_RST_VAL          0x00000000
#define REG_UL_AP_FILLED_FIFO_BASE_ADDRH_RST_VAL          0x00000000
#define REG_UL_AP_FREE_FIFO_BASE_ADDRL_RST_VAL            0x00000000
#define REG_UL_AP_FREE_FIFO_BASE_ADDRH_RST_VAL            0x00000000
#define REG_DL_AP_FILLED_FIFO_BASE_ADDRL_RST_VAL          0x00000000
#define REG_DL_AP_FILLED_FIFO_BASE_ADDRH_RST_VAL          0x00000000
#define REG_DL_AP_FREE_FIFO_BASE_ADDRL_RST_VAL            0x00000000
#define REG_DL_AP_FREE_FIFO_BASE_ADDRH_RST_VAL            0x00000000
#define REG_UL_AP_FREE_STS_BASE_ADDRL_RST_VAL             0x00000000
#define REG_UL_AP_FREE_STS_BASE_ADDRH_RST_VAL             0x00000000
#define REG_UL_AP_FILLED_STS_BASE_ADDRL_RST_VAL           0x00000000
#define REG_UL_AP_FILLED_STS_BASE_ADDRH_RST_VAL           0x00000000
#define REG_DL_AP_FREE_STS_BASE_ADDRL_RST_VAL             0x00000000
#define REG_DL_AP_FREE_STS_BASE_ADDRH_RST_VAL             0x00000000
#define REG_DL_AP_FILLED_STS_BASE_ADDRL_RST_VAL           0x00000000
#define REG_DL_AP_FILLED_STS_BASE_ADDRH_RST_VAL           0x00000000
#define REG_CFG_UL_FILLED_BUFFER_CTRL_RST_VAL             0x00000000
#define REG_CFG_UL_FREE_BUFFER_CTRL_RST_VAL               0x00000000
#define REG_CFG_DL_BUFFER_CTRL_RST_VAL                    0x00000000
#define REG_DDR_MAPPING_OFFSET_L_RST_VAL                  0x00000000
#define REG_DDR_MAPPING_OFFSET_H_RST_VAL                  0x00000000
#define REG_MSDU_BASE_ADDRL_RST_VAL                       0x00000000
#define REG_MSDU_BASE_ADDRH_RST_VAL                       0x00000000
#define REG_UL_NODE_INFO_CONFIG_RST_VAL                   0x08000000
#define REG_CFG_START_RST_VAL                             0x00000000
#define REG_AXI_MST_CFG_RST_VAL                           0x00003348
#define REG_AXI_OS_CFG_RST_VAL                            0x00003F3F
#define REG_CH_WR_PRIO_RST_VAL                            0x00000000
#define REG_CH_RD_PRIO_RST_VAL                            0x00000000
#define REG_BUFFER_TIMEOUT_VAL_RST_VAL           0x000F4240
#define REG_IP_VER_RST_VAL                       0x00010000
#define REG_INT_EN_RST_VAL                       0x00000000
#define REG_INT_CLR_RST_VAL                      0x00000000
#define REG_INT_RAW_RST_VAL                      0x00000000
#define REG_INT_STS_RST_VAL                      0x00000000
#define REG_IPI_CLR_BASE_ADDRL_RST_VAL                    0x00000000
#define REG_IPI_CLR_BASE_ADDRH_RST_VAL                    0x00000000
#define REG_COMMON_FIFO_STS_UPDATE_RST_VAL                0x00020002
#define REG_TOS_PRIO_RST_VAL                              0x0002C458
#define REG_SW_DEBUG_MEM_BASE_ADDR_RST_VAL                0x00000000
#define REG_INDEX_SEARCH_DEPTH_RST_VAL                    0x0000007F
#define REG_INDEX_MISS_ADDR_L_RST_VAL                     0x00000000
#define REG_INDEX_MISS_ADDR_H_RST_VAL                     0x00000000
#define REG_COMMON_FIFO_OFFSET_RST_VAL                    0x00001503
#define REG_SW_DEBUG_CURT_STS_RST_VAL                     0x00000000
#define REG_SW_DEBUG_RESP_ERROR_RST_VAL                   0x00000000
#define REG_DUMMY_REG_RST_VAL                             0x00000000

#define REG_UL_AP_FILLED_FIFO_BASE_ADDRL_MASK          0xFFFFFFFF
#define REG_UL_AP_FILLED_FIFO_BASE_ADDRH_MASK          0x000000FF
#define REG_UL_AP_FREE_FIFO_BASE_ADDRL_MASK            0xFFFFFFFF
#define REG_UL_AP_FREE_FIFO_BASE_ADDRH_MASK            0x000000FF
#define REG_DL_AP_FILLED_FIFO_BASE_ADDRL_MASK          0xFFFFFFFF
#define REG_DL_AP_FILLED_FIFO_BASE_ADDRH_MASK          0x000000FF
#define REG_DL_AP_FREE_FIFO_BASE_ADDRL_MASK            0xFFFFFFFF
#define REG_DL_AP_FREE_FIFO_BASE_ADDRH_MASK            0x000000FF
#define REG_UL_AP_FREE_STS_BASE_ADDRL_MASK             0xFFFFFFFF
#define REG_UL_AP_FREE_STS_BASE_ADDRH_MASK             0x000000FF
#define REG_UL_AP_FILLED_STS_BASE_ADDRL_MASK           0xFFFFFFFF
#define REG_UL_AP_FILLED_STS_BASE_ADDRH_MASK           0x000000FF
#define REG_DL_AP_FREE_STS_BASE_ADDRL_MASK             0xFFFFFFFF
#define REG_DL_AP_FREE_STS_BASE_ADDRH_MASK             0x000000FF
#define REG_DL_AP_FILLED_STS_BASE_ADDRL_MASK           0xFFFFFFFF
#define REG_DL_AP_FILLED_STS_BASE_ADDRH_MASK           0x000000FF
#define REG_CFG_UL_FILLED_BUFFER_CTRL_MASK             0x000007FF
#define REG_CFG_UL_FREE_BUFFER_CTRL_MASK               0x7FFFFFFF
#define REG_CFG_DL_BUFFER_CTRL_MASK                    0x0007FFFF
#define REG_DDR_MAPPING_OFFSET_L_MASK                  0xFFFFFFFF
#define REG_DDR_MAPPING_OFFSET_H_MASK                  0x000000FF
#define REG_MSDU_BASE_ADDRL_MASK                       0xFFFFFFFF
#define REG_MSDU_BASE_ADDRH_MASK                       0x000FFFFF
#define REG_UL_NODE_INFO_CONFIG_MASK                   0xFFFFFFFF
#define REG_CFG_START_MASK                             0x0003000F
#define REG_AXI_MST_CFG_MASK                           0x00FFFFFD
#define REG_AXI_OS_CFG_MASK                            0x00003F3F
#define REG_CH_WR_PRIO_MASK                            0x0FFFFFFF
#define REG_CH_RD_PRIO_MASK                            0x0FFFFFFF
#define REG_BUFFER_TIMEOUT_VAL_MASK           0xFFFFFFFF
#define REG_IP_VER_MASK                       0xFFFFFFFF
#define REG_INT_EN_MASK                       0x000000FF
#define REG_INT_CLR_MASK                      0x000000FF
#define REG_INT_RAW_MASK                      0x000000FF
#define REG_INT_STS_MASK                      0x000000FF
#define REG_IPI_CLR_BASE_ADDRL_MASK                    0xFFFFFFFF
#define REG_IPI_CLR_BASE_ADDRH_MASK                    0x00FF00FF
#define REG_COMMON_FIFO_STS_UPDATE_MASK                0xFFFFFFFF
#define REG_TOS_PRIO_MASK                              0x0003FFFF
#define REG_SW_DEBUG_MEM_BASE_ADDR_MASK                0xFFFFFFFF
#define REG_INDEX_SEARCH_DEPTH_MASK                    0x0000007F
#define REG_INDEX_MISS_ADDR_L_MASK                     0xFFFFFFFF
#define REG_INDEX_MISS_ADDR_H_MASK                     0x00FF00FF
#define REG_COMMON_FIFO_OFFSET_MASK                    0x0000FFFF
#define REG_SW_DEBUG_CURT_STS_MASK                     0x07FFFFFF
#define REG_SW_DEBUG_RESP_ERROR_MASK                   0x7FFFFFFF
#define REG_DUMMY_REG_MASK                             0xFFFFFFFF

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_UL_AP_FILLED_FIFO_BASE_ADDRL
// Register Offset : 0x0000
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_UL_AP_FILLED_FIFO_BASE_ADDRL_UL_AP_FILLED_FIFO_BASE_ADDRL(_X_)       ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_UL_AP_FILLED_FIFO_BASE_ADDRH
// Register Offset : 0x0004
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_UL_AP_FILLED_FIFO_BASE_ADDRH_UL_AP_FILLED_FIFO_BASE_ADDRH(_X_)       ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_UL_AP_FREE_FIFO_BASE_ADDRL
// Register Offset : 0x0008
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_UL_AP_FREE_FIFO_BASE_ADDRL_UL_AP_FREE_FIFO_BASE_ADDRL(_X_)           ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_UL_AP_FREE_FIFO_BASE_ADDRH
// Register Offset : 0x000C
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_UL_AP_FREE_FIFO_BASE_ADDRH_UL_AP_FREE_FIFO_BASE_ADDRH(_X_)           ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DL_AP_FILLED_FIFO_BASE_ADDRL
// Register Offset : 0x0010
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DL_AP_FILLED_FIFO_BASE_ADDRL_DL_AP_FILLED_FIFO_BASE_ADDRL(_X_)       ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DL_AP_FILLED_FIFO_BASE_ADDRH
// Register Offset : 0x0014
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DL_AP_FILLED_FIFO_BASE_ADDRH_DL_AP_FILLED_FIFO_BASE_ADDRH(_X_)       ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DL_AP_FREE_FIFO_BASE_ADDRL
// Register Offset : 0x0018
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DL_AP_FREE_FIFO_BASE_ADDRL_DL_AP_FREE_FIFO_BASE_ADDRL(_X_)           ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DL_AP_FREE_FIFO_BASE_ADDRH
// Register Offset : 0x001C
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DL_AP_FREE_FIFO_BASE_ADDRH_DL_AP_FREE_FIFO_BASE_ADDRH(_X_)           ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_UL_AP_FREE_STS_BASE_ADDRL
// Register Offset : 0x0020
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_UL_AP_FREE_STS_BASE_ADDRL_UL_AP_FREE_STS_BASE_ADDRL(_X_)             ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_UL_AP_FREE_STS_BASE_ADDRH
// Register Offset : 0x0024
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_UL_AP_FREE_STS_BASE_ADDRH_UL_AP_FREE_STS_BASE_ADDRH(_X_)             ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_UL_AP_FILLED_STS_BASE_ADDRL
// Register Offset : 0x0028
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_UL_AP_FILLED_STS_BASE_ADDRL_UL_AP_FILLED_STS_BASE_ADDRL(_X_)         ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_UL_AP_FILLED_STS_BASE_ADDRH
// Register Offset : 0x002C
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_UL_AP_FILLED_STS_BASE_ADDRH_UL_AP_FILLED_STS_BASE_ADDRH(_X_)         ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DL_AP_FREE_STS_BASE_ADDRL
// Register Offset : 0x0030
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DL_AP_FREE_STS_BASE_ADDRL_DL_AP_FREE_STS_BASE_ADDRL(_X_)             ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DL_AP_FREE_STS_BASE_ADDRH
// Register Offset : 0x0034
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DL_AP_FREE_STS_BASE_ADDRH_DL_AP_FREE_STS_BASE_ADDRH(_X_)             ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DL_AP_FILLED_STS_BASE_ADDRL
// Register Offset : 0x0038
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DL_AP_FILLED_STS_BASE_ADDRL_DL_AP_FILLED_STS_BASE_ADDRL(_X_)         ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DL_AP_FILLED_STS_BASE_ADDRH
// Register Offset : 0x003C
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DL_AP_FILLED_STS_BASE_ADDRH_DL_AP_FILLED_STS_BASE_ADDRH(_X_)         ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_CFG_UL_FILLED_BUFFER_CTRL
// Register Offset : 0x0040
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_CFG_UL_FILLED_BUFFER_CTRL_CFG_UL_CP_FILLED_BUFFER_WATERMARK(_X_)     (((_X_) << 6) & 0x000007C0)
#define    BIT_PAM_WIFI_CFG_UL_FILLED_BUFFER_CTRL_CFG_UL_AP_FILLED_BUFFER_WATERMARK(_X_)     (((_X_) << 1) & 0x0000003E)
#define    BIT_PAM_WIFI_CFG_UL_FILLED_BUFFER_CTRL_CFG_UL_FILLED_BUFFER_CLR                   (BIT_(0))

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL
// Register Offset : 0x0044
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE4_BUFFER_WATERMARK(_X_)        (((_X_) << 26) & 0x7C000000)
#define    BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE3_BUFFER_WATERMARK(_X_)        (((_X_) << 21) & 0x03E00000)
#define    BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE2_BUFFER_WATERMARK(_X_)        (((_X_) << 16) & 0x001F0000)
#define    BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE1_BUFFER_WATERMARK(_X_)        (((_X_) << 11) & 0x0000F800)
#define    BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_UL_CP_FREE_BUFFER_WATERMARK(_X_)         (((_X_) << 6) & 0x000007C0)
#define    BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_UL_AP_FREE_BUFFER_WATERMARK(_X_)         (((_X_) << 1) & 0x0000003E)
#define    BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_UL_FREE_BUFFER_CLR                       (BIT_(0))

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_CFG_DL_BUFFER_CTRL
// Register Offset : 0x0048
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_NODE_FIFO_CLR                                     (BIT_(18))
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_INDEX_FIFO_CLR                                    (BIT_(17))
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_CFG_DL_CP_TYPE4_BUFFER_CLR                        (BIT_(16))
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_CFG_DL_CP_TYPE3_BUFFER_CLR                        (BIT_(15))
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_CFG_DL_CP_TYPE2_BUFFER_CLR                        (BIT_(14))
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_CFG_DL_CP_TYPE1_BUFFER_CLR                        (BIT_(13))
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_CFG_DL_CP_FREE_BUFFER_CLR                         (BIT_(12))
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_CFG_DL_AP_FILLED_BUFFER_CLR                       (BIT_(11))
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_CFG_DL_AP_FREE_BUFFER_CLR                         (BIT_(10))
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_CFG_DL_AP_FILLED_BUFFER_WATERMARK(_X_)            (((_X_) << 5) & 0x000003E0)
#define    BIT_PAM_WIFI_CFG_DL_BUFFER_CTRL_CFG_DL_AP_FREE_BUFFER_WATERMARK(_X_)              ((_X_) & 0x0000001F)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DDR_MAPPING_OFFSET_L
// Register Offset : 0x004C
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DDR_MAPPING_OFFSET_L_DDR_MAPPING_OFFSET_L(_X_)                       ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DDR_MAPPING_OFFSET_H
// Register Offset : 0x0050
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DDR_MAPPING_OFFSET_H_DDR_MAPPING_OFFSET_H(_X_)                       ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_MSDU_BASE_ADDRL
// Register Offset : 0x0054
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_MSDU_BASE_ADDRL_MSDU_BASE_ADDRL(_X_)                                 ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_MSDU_BASE_ADDRH
// Register Offset : 0x0058
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_MSDU_BASE_ADDRH_UL_OFFSET(_X_)                                       (((_X_) << 8) & 0x000FFF00)
#define    BIT_PAM_WIFI_MSDU_BASE_ADDRH_MSDU_BASE_ADDRH(_X_)                                 ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_UL_NODE_INFO_CONFIG
// Register Offset : 0x005C
// Description     : 
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_UL_NODE_INFO_CONFIG_MSDU_LENGTH(_X_)                                 (((_X_) << 26) & 0xFC000000)
#define    BIT_PAM_WIFI_UL_NODE_INFO_CONFIG_OFFSET_BEFORE_MSDU(_X_)                          (((_X_) << 18) & 0x03FC0000)
#define    BIT_PAM_WIFI_UL_NODE_INFO_CONFIG_UL_NET_ID(_X_)                                   (((_X_) << 10) & 0x0003FC00)
#define    BIT_PAM_WIFI_UL_NODE_INFO_CONFIG_UL_DST_ID(_X_)                                   (((_X_) << 5) & 0x000003E0)
#define    BIT_PAM_WIFI_UL_NODE_INFO_CONFIG_UL_SRC_ID(_X_)                                   ((_X_) & 0x0000001F)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_CFG_START
// Register Offset : 0x0060
// Description     : 
//---------------------------------------------------------------------------
#define    BIT_PAM_WIFI_CFG_START_PAM_WIFI_TABLE_RD_STOP_EN_MSB                              (17)

#define    BIT_PAM_WIFI_CFG_START_PAM_WIFI_TABLE_RD_STOP                                     (BIT_(17))
#define    BIT_PAM_WIFI_CFG_START_SOFT_TABLE_UPDATE_REQ                                      (BIT_(16))
#define    BIT_PAM_WIFI_CFG_START_PAM_WIFI_PAUSE_DONE                                        (BIT_(3))
#define    BIT_PAM_WIFI_CFG_START_PAM_WIFI_PAUSE_REQ                                         (BIT_(2))
#define    BIT_PAM_WIFI_CFG_START_PAM_WIFI_STOP                                              (BIT_(1))
#define    BIT_PAM_WIFI_CFG_START_PAM_WIFI_START                                             (BIT_(0))

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_AXI_MST_CFG
// Register Offset : 0x0064
// Description     : AXI master configuration
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_AXI_MST_CFG_RF_CACHE_WR(_X_)                                         (((_X_) << 20) & 0x00F00000)
#define    BIT_PAM_WIFI_AXI_MST_CFG_RF_CACHE_RD(_X_)                                         (((_X_) << 16) & 0x000F0000)
#define    BIT_PAM_WIFI_AXI_MST_CFG_RF_QOS_WR(_X_)                                           (((_X_) << 12) & 0x0000F000)
#define    BIT_PAM_WIFI_AXI_MST_CFG_RF_QOS_RD(_X_)                                           (((_X_) << 8) & 0x00000F00)
#define    BIT_PAM_WIFI_AXI_MST_CFG_RF_PROT_WR(_X_)                                          (((_X_) << 5) & 0x000000E0)
#define    BIT_PAM_WIFI_AXI_MST_CFG_RF_PROT_RD(_X_)                                          (((_X_) << 2) & 0x0000001C)
#define    BIT_PAM_WIFI_AXI_MST_CFG_RF_AXI_MST_EN                                            (BIT_(0))

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_AXI_OS_CFG
// Register Offset : 0x0068
// Description     : AXI outstanding configuration
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_AXI_OS_CFG_RF_AXI_OS_WR(_X_)                                         (((_X_) << 8) & 0x00003F00)
#define    BIT_PAM_WIFI_AXI_OS_CFG_RF_AXI_OS_RD(_X_)                                         ((_X_) & 0x0000003F)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_CH_WR_PRIO
// Register Offset : 0x006C
// Description     : CH_WR_PRIO
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_CH_WR_PRIO_CH14_WR_PRIORITY(_X_)                                     (((_X_) << 26) & 0x0C000000)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH13_WR_PRIORITY(_X_)                                     (((_X_) << 24) & 0x03000000)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH12_WR_PRIORITY(_X_)                                     (((_X_) << 22) & 0x00C00000)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH11_WR_PRIORITY(_X_)                                     (((_X_) << 20) & 0x00300000)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH10_WR_PRIORITY(_X_)                                     (((_X_) << 18) & 0x000C0000)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH9_WR_PRIORITY(_X_)                                      (((_X_) << 16) & 0x00030000)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH8_WR_PRIORITY(_X_)                                      (((_X_) << 14) & 0x0000C000)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH7_WR_PRIORITY(_X_)                                      (((_X_) << 12) & 0x00003000)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH6_WR_PRIORITY(_X_)                                      (((_X_) << 10) & 0x00000C00)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH5_WR_PRIORITY(_X_)                                      (((_X_) << 8) & 0x00000300)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH4_WR_PRIORITY(_X_)                                      (((_X_) << 6) & 0x000000C0)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH3_WR_PRIORITY(_X_)                                      (((_X_) << 4) & 0x00000030)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH2_WR_PRIORITY(_X_)                                      (((_X_) << 2) & 0x0000000C)
#define    BIT_PAM_WIFI_CH_WR_PRIO_CH1_WR_PRIORITY(_X_)                                      ((_X_) & 0x00000003)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_CH_RD_PRIO
// Register Offset : 0x0070
// Description     : CH_RD_PRIO
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_CH_RD_PRIO_CH14_RD_PRIORITY(_X_)                                     (((_X_) << 26) & 0x0C000000)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH13_RD_PRIORITY(_X_)                                     (((_X_) << 24) & 0x03000000)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH12_RD_PRIORITY(_X_)                                     (((_X_) << 22) & 0x00C00000)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH11_RD_PRIORITY(_X_)                                     (((_X_) << 20) & 0x00300000)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH10_RD_PRIORITY(_X_)                                     (((_X_) << 18) & 0x000C0000)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH9_RD_PRIORITY(_X_)                                      (((_X_) << 16) & 0x00030000)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH8_RD_PRIORITY(_X_)                                      (((_X_) << 14) & 0x0000C000)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH7_RD_PRIORITY(_X_)                                      (((_X_) << 12) & 0x00003000)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH6_RD_PRIORITY(_X_)                                      (((_X_) << 10) & 0x00000C00)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH5_RD_PRIORITY(_X_)                                      (((_X_) << 8) & 0x00000300)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH4_RD_PRIORITY(_X_)                                      (((_X_) << 6) & 0x000000C0)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH3_RD_PRIORITY(_X_)                                      (((_X_) << 4) & 0x00000030)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH2_RD_PRIORITY(_X_)                                      (((_X_) << 2) & 0x0000000C)
#define    BIT_PAM_WIFI_CH_RD_PRIO_CH1_RD_PRIORITY(_X_)                                      ((_X_) & 0x00000003)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_PAM_WIFI_BUFFER_TIMEOUT_VAL
// Register Offset : 0x0074
// Description     : pam_wifi_buffer_timeout_val
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_PAM_WIFI_BUFFER_TIMEOUT_VAL_PAM_WIFI_BUFFER_TIMEOUT_VAL(_X_)         ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_PAM_WIFI_IP_VER
// Register Offset : 0x0078
// Description     : pam_wifi_ip_ver
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_PAM_WIFI_IP_VER_PAM_WIFI_IP_VER(_X_)                                 ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_PAM_WIFI_INT_EN
// Register Offset : 0x007C
// Description     : pam_wifi_int_en
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_PAM_WIFI_INT_EN_INT_EN_DL_INDEX_MISS                                 (BIT_(7))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_EN_INT_EN_DL_FILL_TYPE4                                 (BIT_(6))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_EN_INT_EN_DL_FILL_TYPE3                                 (BIT_(5))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_EN_INT_EN_DL_FILL_TYPE2                                 (BIT_(4))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_EN_INT_EN_DL_FILL_TYPE1                                 (BIT_(3))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_EN_INT_EN_DL_FREE                                       (BIT_(2))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_EN_INT_EN_UL_FILL                                       (BIT_(1))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_EN_INT_EN_UL_FREE                                       (BIT_(0))

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_PAM_WIFI_INT_CLR
// Register Offset : 0x0080
// Description     : pam_wifi_int_clr
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_PAM_WIFI_INT_CLR_INT_CLR_DL_INDEX_MISS                               (BIT_(7))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_CLR_INT_CLR_DL_FILL_TYPE4                               (BIT_(6))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_CLR_INT_CLR_DL_FILL_TYPE3                               (BIT_(5))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_CLR_INT_CLR_DL_FILL_TYPE2                               (BIT_(4))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_CLR_INT_CLR_DL_FILL_TYPE1                               (BIT_(3))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_CLR_INT_CLR_DL_FREE                                     (BIT_(2))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_CLR_INT_CLR_UL_FILL                                     (BIT_(1))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_CLR_INT_CLR_UL_FREE                                     (BIT_(0))

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_PAM_WIFI_INT_RAW
// Register Offset : 0x0084
// Description     : pam_wifi_int_raw
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_PAM_WIFI_INT_RAW_INT_RAW_DL_INDEX_MISS                               (BIT_(7))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_RAW_INT_RAW_DL_FILL_TYPE4                               (BIT_(6))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_RAW_INT_RAW_DL_FILL_TYPE3                               (BIT_(5))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_RAW_INT_RAW_DL_FILL_TYPE2                               (BIT_(4))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_RAW_INT_RAW_DL_FILL_TYPE1                               (BIT_(3))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_RAW_INT_RAW_DL_FREE                                     (BIT_(2))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_RAW_INT_RAW_UL_FILL                                     (BIT_(1))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_RAW_INT_RAW_UL_FREE                                     (BIT_(0))

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_PAM_WIFI_INT_STS
// Register Offset : 0x0088
// Description     : pam_wifi_int_sts
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_PAM_WIFI_INT_STS_INT_STS_DL_INDEX_MISS                               (BIT_(7))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_STS_INT_STS_DL_FILL_TYPE4                               (BIT_(6))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_STS_INT_STS_DL_FILL_TYPE3                               (BIT_(5))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_STS_INT_STS_DL_FILL_TYPE2                               (BIT_(4))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_STS_INT_STS_DL_FILL_TYPE1                               (BIT_(3))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_STS_INT_STS_DL_FREE                                     (BIT_(2))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_STS_INT_STS_UL_FILL                                     (BIT_(1))
#define    BIT_PAM_WIFI_PAM_WIFI_INT_STS_INT_STS_UL_FREE                                     (BIT_(0))

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_IPI_CLR_BASE_ADDRL
// Register Offset : 0x008C
// Description     : ipi_clr_base_addrl
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_IPI_CLR_BASE_ADDRL_IPI_CLR_BASE_ADDRL(_X_)                           ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_IPI_CLR_BASE_ADDRH
// Register Offset : 0x0090
// Description     : ipi_clr_base_addrh
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_IPI_CLR_BASE_ADDRH_IPI_CLR_BIT(_X_)                                  (((_X_) << 16) & 0x00FF0000)
#define    BIT_PAM_WIFI_IPI_CLR_BASE_ADDRH_IPI_CLR_BASE_ADDRH(_X_)                           ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_COMMON_FIFO_STS_UPDATE
// Register Offset : 0x0094
// Description     : common_fifo_sts_update
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_COMMON_FIFO_STS_UPDATE_RX_COMMON_FIFO_WR_FULL(_X_)                   (((_X_) << 16) & 0xFFFF0000)
#define    BIT_PAM_WIFI_COMMON_FIFO_STS_UPDATE_TX_COMMON_FIFO_CLR(_X_)                       ((_X_) & 0x0000FFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_TOS_PRIO
// Register Offset : 0x0098
// Description     : tos_prio
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_2_1(_X_)                                           (((_X_) << 15) & 0x00038000)
#define    BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_2_0(_X_)                                           (((_X_) << 12) & 0x00007000)
#define    BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_1_1(_X_)                                           (((_X_) << 9) & 0x00000E00)
#define    BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_1_0(_X_)                                           (((_X_) << 6) & 0x000001C0)
#define    BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_0_1(_X_)                                           (((_X_) << 3) & 0x00000038)
#define    BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_0_0(_X_)                                           ((_X_) & 0x00000007)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_SW_DEBUG_MEM_BASE_ADDR
// Register Offset : 0x009C
// Description     : sw_debug_mem_base_addr
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_SW_DEBUG_MEM_BASE_ADDR_SW_DEBUG_MEM_BASE_ADDR(_X_)                   ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_INDEX_SEARCH_DEPTH
// Register Offset : 0x00A0
// Description     : index_search_depth
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_INDEX_SEARCH_DEPTH_INDEX_SEARCH_DEPTH(_X_)                           ((_X_) & 0x0000007F)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_INDEX_MISS_ADDR_L
// Register Offset : 0x00A4
// Description     : index_miss_addr_l
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_INDEX_MISS_ADDR_L_INDEX_MISS_ADDR_L(_X_)                             ((_X_) & 0xFFFFFFFF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_INDEX_MISS_ADDR_H
// Register Offset : 0x00A8
// Description     : index_miss_addr_h
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_INDEX_MISS_ADDR_H_INDEX_MISS_CNT(_X_)                                (((_X_) << 16) & 0x00FF0000)
#define    BIT_PAM_WIFI_INDEX_MISS_ADDR_H_INDEX_MISS_ADDR_H(_X_)                             ((_X_) & 0x000000FF)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_COMMON_FIFO_OFFSET
// Register Offset : 0x00AC
// Description     : common_fifo_offset
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_COMMON_FIFO_OFFSET_RX_COMMON_FIFO_WPTR_OFFSET(_X_)                   (((_X_) << 12) & 0x0000F000)
#define    BIT_PAM_WIFI_COMMON_FIFO_OFFSET_TX_COMMON_FIFO_RPTR_OFFSET(_X_)                   (((_X_) << 8) & 0x00000F00)
#define    BIT_PAM_WIFI_COMMON_FIFO_OFFSET_RX_COMMON_FIFO_OFFSET(_X_)                        (((_X_) << 4) & 0x000000F0)
#define    BIT_PAM_WIFI_COMMON_FIFO_OFFSET_TX_COMMON_FIFO_OFFSET(_X_)                        ((_X_) & 0x0000000F)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_SW_DEBUG_CURT_STS
// Register Offset : 0x00B0
// Description     : sw_debug_curt_sts
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_SW_DEBUG_CURT_STS_DEBUG_MSDU_CURT_STS(_X_)                           (((_X_) << 23) & 0x07800000)
#define    BIT_PAM_WIFI_SW_DEBUG_CURT_STS_DEBUG_SE_CURT_STS(_X_)                             (((_X_) << 20) & 0x00700000)
#define    BIT_PAM_WIFI_SW_DEBUG_CURT_STS_DL_AP_DEBUG_PUT_PTR_CURT_STS(_X_)                  (((_X_) << 15) & 0x000F8000)
#define    BIT_PAM_WIFI_SW_DEBUG_CURT_STS_DL_AP_DEBUG_GET_PTR_CURT_STS(_X_)                  (((_X_) << 10) & 0x00007C00)
#define    BIT_PAM_WIFI_SW_DEBUG_CURT_STS_UL_AP_DEBUG_PUT_PTR_CURT_STS(_X_)                  (((_X_) << 5) & 0x000003E0)
#define    BIT_PAM_WIFI_SW_DEBUG_CURT_STS_UL_AP_DEBUG_GET_PTR_CURT_STS(_X_)                  ((_X_) & 0x0000001F)

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_SW_DEBUG_RESP_ERROR
// Register Offset : 0x00B4
// Description     : sw_debug_int
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_SW_DEBUG_RESP_ERROR_DEBUG_CH_WR_REQ(_X_)                             (((_X_) << 18) & 0x7FFC0000)
#define    BIT_PAM_WIFI_SW_DEBUG_RESP_ERROR_DEBUG_CH_RD_REQ(_X_)                             (((_X_) << 4) & 0x0003FFF0)
#define    BIT_PAM_WIFI_SW_DEBUG_RESP_ERROR_IP_RRESP_ERROR_INT_CLR                           (BIT_(3))
#define    BIT_PAM_WIFI_SW_DEBUG_RESP_ERROR_IP_BRESP_ERROR_INT_CLR                           (BIT_(2))
#define    BIT_PAM_WIFI_SW_DEBUG_RESP_ERROR_IP_RRESP_ERROR_INT_STS                           (BIT_(1))
#define    BIT_PAM_WIFI_SW_DEBUG_RESP_ERROR_IP_BRESP_ERROR_INT_STS                           (BIT_(0))

//---------------------------------------------------------------------------
// Register Name   : REG_PAM_WIFI_PAM_WIFI_DUMMY_REG
// Register Offset : 0x00B8
// Description     : dummy_reg
//---------------------------------------------------------------------------

#define    BIT_PAM_WIFI_DUMMY_REG_DUMMY_REG(_X_)                                             ((_X_) & 0xFFFFFFFF)
#endif

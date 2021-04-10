/******************************************************************************
 ** File Name:    sdio_reg_v3.h                                           *
 ** Author:       Binggo.Zhou                                               *
 ** DATE:         02/03/2010                                                  *
 ** Copyright:    2005 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 02/03/2010    Binggo.Zhou     Create.                                     *
 ******************************************************************************/


#ifndef _SDIO_REG_V3_H_
#define _SDIO_REG_V3_H_

typedef struct
{

    volatile uint32 DMA_BLK_COUNT;
    volatile uint32 DMA_BLK_SIZE;
    volatile uint32 CMD_ARGUMENT;
    volatile uint32 CMD_TRANSMODE;
    volatile uint32 RSP0;
    volatile uint32 RSP1;
    volatile uint32 RSP2;
    volatile uint32 RSP3;
    volatile uint32 BUFFER_PORT;
    volatile uint32 PRESENT_STAT;
    volatile uint32 HOST_CTL1;
    volatile uint32 EMMC_CLK_CTRL;
    volatile uint32 INT_STA;
    volatile uint32 INT_STA_EN;
    volatile uint32 INT_SIG_EN;
    volatile uint32 HOST_CTL2;
    volatile uint32 CAPBILITY;
    volatile uint32 CAPBILITY_RES;
    volatile uint32 EMMC_SDHC_RED48;
    volatile uint32 EMMC_SDHC_RED4C;
    volatile uint32 EMMC_FORCE_EVT;
    volatile uint32 EMMC_ADMA_ERR;
    volatile uint32 EMMC_ADMA2_ADDR_L;
    volatile uint32 EMMC_ADMA2_ADDR_H;
}
SDIO_REG_CFG;


//---

//=====
//define transfer mode and command mode...
//command mode
#define SDIO_CMD_TYPE_ABORT	(3<<22)
#define SDIO_CMD_TYPE_RESUME	(2<<22)
#define SDIO_CMD_TYPE_SUSPEND	(1<<22)
#define SDIO_CMD_TYPE_NML	(0<<22)

#define SDIO_CMD_DATA_PRESENT	BIT_21

#define SDIO_CMD_INDEX_CHK	BIT_20
#define SDIO_CMD_CRC_CHK	BIT_19
#define SDIO_CMD_NO_RSP		(0x00<<16)
#define SDIO_CMD_RSP_136	(0x01<<16)
#define SDIO_CMD_RSP_48		(0x02<<16)
#define SDIO_CMD_RSP_48_BUSY	(0x03<<16)

#define SDIO_NO_RSP	0x0;
#define SDIO_R1		( SDIO_CMD_RSP_48 | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R2		( SDIO_CMD_RSP_136 | SDIO_CMD_CRC_CHK )
#define SDIO_R3		SDIO_CMD_RSP_48
#define SDIO_R4		SDIO_CMD_RSP_48
#define SDIO_R5		( SDIO_CMD_RSP_48 | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R6		( SDIO_CMD_RSP_48 | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R7		( SDIO_CMD_RSP_48 | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R1B	( SDIO_CMD_RSP_48_BUSY | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )
#define SDIO_R5B	( SDIO_CMD_RSP_48_BUSY | SDIO_CMD_INDEX_CHK | SDIO_CMD_CRC_CHK )

//transfer mode
#define SDIO_TRANS_COMP_ATA         BIT_6
#define SDIO_TRANS_MULTIBLK         BIT_5
#define SDIO_TRANS_DIR_READ         BIT_4
#define SDIO_TRANS_AUTO_CMD12_EN        BIT_2
#define SDIO_TRANS_BLK_CNT_EN           BIT_1
#define SDIO_TRANS_DMA_EN               BIT_0

#define NULL			0x0 

/********** dma mode **************/
#define EMMC_SDMA_MODE             0x00000018

/********** datawidth ***************/
#define EMMC_ENABLE_64BIT         0x20000000


/**************************   Card info   *********************************/
#define CARD_DATA_BLOCK_LEN				512

#define PARTITION_ENABLE_BOOT1_OFFSET	3
#define PARTITION_CFG_ENABLE_BOOT1	(1 << PARTITION_ENABLE_BOOT1_OFFSET)

#define PARTITION_CFG_ACCESS_USER	0
#define PARTITION_CFG_ACCESS_BOOT1	1
#define PARTITION_CFG_ACCESS_BOOT2	2
#define PARTITION_CFG_ACCESS_RPMB	3
#define PARTITION_CFG_ACCESS_GEN_P1	4
#define PARTITION_CFG_ACCESS_GEN_P2	5
#define PARTITION_CFG_ACCESS_GEN_P3	6
#define PARTITION_CFG_ACCESS_GEN_P4	7

#define EXT_CSD_CARD_WIDTH_1_BIT	0
#define EXT_CSD_CARD_WIDTH_4_BIT	1
#define EXT_CSD_CARD_WIDTH_8_BIT	2

#define CMD6_BIT_MODE_OFFSET_ACCESS	24
#define CMD6_BIT_MODE_MASK_ACCESS	0x03000000
#define CMD6_BIT_MODE_OFFSET_INDEX	16
#define CMD6_BIT_MODE_MASK_INDEX	0x00FF0000
#define CMD6_BIT_MODE_OFFSET_VALUE	8
#define CMD6_BIT_MODE_MASK_VALUE	0x0000FF00
#define CMD6_BIT_MODE_OFFSET_CMD_SET	0
#define CMD6_BIT_MODE_MASK_CMD_SET	0x00000003

#define CMD6_ACCESS_MODE_COMMAND_SET	(0 << CMD6_BIT_MODE_OFFSET_ACCESS)
#define CMD6_ACCESS_MODE_SET_BITS	(1 << CMD6_BIT_MODE_OFFSET_ACCESS)
#define CMD6_ACCESS_MODE_CLEAR_BITS	(2 << CMD6_BIT_MODE_OFFSET_ACCESS)
#define CMD6_ACCESS_MODE_WRITE_BYTE	(3 << CMD6_BIT_MODE_OFFSET_ACCESS)
#define CMD6_CMD_SET			(1 << CMD6_BIT_MODE_OFFSET_CMD_SET)

#define EXT_CSD_PARTITION_CFG_INDEX	179
#define EXT_CSD_BUS_WIDTH_INDEX		183			/* R/W */
#define EXT_CSD_HS_TIMING_INDEX		185			/* R/W */
#define EXT_CSD_CARD_TYPE_INDEX		196			/* RO */
#define EXT_CSD_SEC_CNT_INDEX		212			/* RO, 4 bytes */

#define SECTOR_MODE			0x40000000
#define BYTE_MODE			0x00000000

/**************************   control info    *******************************/
typedef enum
{
	PARTITION_USER,
	PARTITION_BOOT1,
	PARTITION_BOOT2,
	PARTITION_RPMB,
	PARTITION_GENERAL_P1,
	PARTITION_GENERAL_P2,
	PARTITION_GENERAL_P3,
	PARTITION_GENERAL_P4,
	PARTITION_MAX
} CARD_Partition_e;

typedef struct
{
	uint8	*data_buf;	/* the buffer address */
	uint32	blk_len;		/* block size */
	uint32	blk_num;		/* block number */
} DATA_Param_t;

typedef enum
{
	SDIO_ERR_NONE		= 0,
	SDIO_ERR_RSP		= BIT_0,
	SDIO_ERR_CMD12		= BIT_1,
	SDIO_ERR_CUR_LIMIT	= BIT_2,
	SDIO_ERR_DATA_END	= BIT_3,
	SDIO_ERR_DATA_CRC	= BIT_4,
	SDIO_ERR_DATA_TIMEOUT	= BIT_5,
	SDIO_ERR_CMD_INDEX	= BIT_6,
	SDIO_ERR_CMD_END	= BIT_7,
	SDIO_ERR_CMD_CRC	= BIT_8,
	SDIO_ERR_CMD_TIMEOUT	= BIT_9
} SDIO_Error_e;

/**************************   card info    *********************************/
typedef enum
{
	RST_CMD_LINE,
	RST_DAT_LINE,
	RST_CMD_DAT_LINE,
	RST_ALL,
	RST_MODULE
} SDIO_Rst_e;

/**************************   emmc base handle    **************************/
typedef enum
{
	SDIO_BUS_1_BIT,
	SDIO_BUS_4_BIT,
	SDIO_BUS_8_BIT
} SDIO_BusWidth_e;

typedef enum
{
	SDIO_OFF,
	SDIO_ON
} SDIO_OnOff_e;

typedef void (*SDIO_CALLBACK)(uint32 msg, uint32 errCode);

typedef struct
{
	volatile SDIO_REG_CFG	*host_cfg;	/* register configuration */
	BOOLEAN			open_flag;	/* open flag */
	uint32			base_clock;	/* base clock */
	uint32			sd_clock;
	uint32			err_filter;
	SDIO_CALLBACK		sig_callBack;
	volatile uint32		card_event;
	volatile uint32		card_errCode;

	uint16			rca;			/* card RCA */
	SDIO_BusWidth_e		bus_width;	/* card used bus width */
	uint32			block_len;	/* card block length */
	CARD_Partition_e	cur_partition;	/* card current partition */
} SDIO_Handle_t, *SDIO_Hd_Ptr;

/**************************   cmd info    *********************************/
#define TRANS_MODE_CMPLETE_SIG_EN	BIT_0
#define TRANS_MODE_MULTI_BLOCK		BIT_1
#define TRANS_MODE_READ			BIT_2
#define TRANS_MODE_CMD12_EN		BIT_3
#define TRANS_MODE_BLOCK_COUNT_EN	BIT_4
#define TRANS_MODE_DMA_EN		BIT_5
#define CMD_HAVE_DATA			BIT_6

typedef enum
{
	CMD_NO_RSP = 0,
	CMD_RSP_R1,
	CMD_RSP_R2,
	CMD_RSP_R3,
	CMD_RSP_R4,
	CMD_RSP_R5,
	CMD_RSP_R6,
	CMD_RSP_R7,
	CMD_RSP_R1B,
	CMD_RSP_R5B
} CARD_CmdRsp_e;

typedef enum
{
	CMD_TYPE_NORMAL = 0,
	CMD_TYPE_SUSPEND,
	CMD_TYPE_RESUME,
	CMD_TYPE_ABORT
} SDIO_CmdType_e;

#define SIG_ERR		BIT_0
#define SIG_CARD_IN	BIT_1
#define SIG_CARD_INSERT	BIT_2
#define SIG_CARD_REMOVE	BIT_3
#define SIG_BUF_RD_RDY	BIT_4
#define SIG_BUF_WD_RDY	BIT_5
#define SIG_DMA_INT	BIT_6
#define SIG_BLK_CAP	BIT_7
#define SIG_TRANS_CMP	BIT_8
#define SIG_CMD_CMP	BIT_9
#define SIG_ALL		(SIG_ERR | SIG_CARD_IN | SIG_CARD_INSERT \
			| SIG_CARD_REMOVE | SIG_BUF_RD_RDY \
			| SIG_BUF_WD_RDY | SIG_DMA_INT \
			| SIG_BLK_CAP | SIG_TRANS_CMP \
			| SIG_CMD_CMP)

#define ERR_RSP		BIT_0
#define ERR_CMD12	BIT_1
#define ERR_CUR_LIMIT	BIT_2
#define ERR_DATA_END	BIT_3
#define ERR_DATA_CRC	BIT_4
#define ERR_DATA_TIMEOUT	BIT_5
#define ERR_CMD_INDEX	BIT_6
#define ERR_CMD_END	BIT_7
#define ERR_CMD_CRC	BIT_8
#define ERR_CMD_TIMEOUT	BIT_9
#define ERR_ALL		(ERR_CMD12 | ERR_CUR_LIMIT \
			| ERR_DATA_END | ERR_DATA_CRC \
			| ERR_DATA_TIMEOUT | ERR_CMD_INDEX \
			| ERR_CMD_END | ERR_CMD_CRC \
			| ERR_CMD_TIMEOUT)

//	response Name		cmd int filter,rsp		,cmd error filter
#define CARD_SDIO_NO_RSP	SIG_CMD_CMP,CMD_NO_RSP	,NULL
#define CARD_SDIO_R1		SIG_CMD_CMP,CMD_RSP_R1	,ERR_CMD_INDEX|	ERR_CMD_END|	ERR_CMD_CRC|	ERR_CMD_TIMEOUT
#define CARD_SDIO_R2		SIG_CMD_CMP,CMD_RSP_R2	,		ERR_CMD_END|	ERR_CMD_CRC|	ERR_CMD_TIMEOUT
#define CARD_SDIO_R3		SIG_CMD_CMP,CMD_RSP_R3	,		ERR_CMD_END|			ERR_CMD_TIMEOUT
#define CARD_SDIO_R4		SIG_CMD_CMP,CMD_RSP_R4	,ERR_CMD_INDEX|	ERR_CMD_END|	ERR_CMD_CRC|	ERR_CMD_TIMEOUT
#define CARD_SDIO_R5		SIG_CMD_CMP,CMD_RSP_R5	,ERR_CMD_INDEX|	ERR_CMD_END|	ERR_CMD_CRC|	ERR_CMD_TIMEOUT
#define CARD_SDIO_R6		SIG_CMD_CMP,CMD_RSP_R6	,ERR_CMD_INDEX|	ERR_CMD_END|	ERR_CMD_CRC|	ERR_CMD_TIMEOUT
#define CARD_SDIO_R7		SIG_CMD_CMP,CMD_RSP_R7	,ERR_CMD_INDEX|	ERR_CMD_END|	ERR_CMD_CRC|	ERR_CMD_TIMEOUT
#define CARD_SDIO_R1B		SIG_CMD_CMP,CMD_RSP_R1B	,ERR_CMD_INDEX|	ERR_CMD_END|	ERR_CMD_CRC|	ERR_CMD_TIMEOUT


#define     SDIO_BASE_CLK_26M       26000000            // 26  MHz
#define     SDIO_CLK_48M            48000000        // 48  MHz

typedef enum {
	// cmdindex,rsp,transmode
	CARD_CMD0_GO_IDLE_STATE,
	CARD_CMD1_SEND_OP_COND,	/* MMC */
	CARD_CMD2_ALL_SEND_CID,
	CARD_CMD3_SET_RELATIVE_ADDR,	/* MMC */
	CARD_CMD6_APP_SET_BUS_WIDTH,
	CARD_CMD7_SELECT_DESELECT_CARD,
	CARD_CMD8_IF_COND_SD,
	CARD_CMD12_STOP_TRANSMISSION,	/* It is auto performed by Host */
	CARD_CMD13_SEND_STATUS,
	CARD_CMD16_SET_BLOCKLEN,
	CARD_CMD18_READ_MULTIPLE_BLOCK,
	CARD_ACMD6_SET_EXT_CSD,
	CARD_ACMD41_SEND_OP_COND,
	CARD_ACMD55_APP_CMD,
	CARD_CMD8_IF_COND_MMC,
	CARD_CMDMAX
} CARD_Cmd_e;


typedef struct
{
	CARD_Cmd_e	cmd;
	uint32		cmd_index;
	uint32		int_filter;
	CARD_CmdRsp_e	response;
	uint32		err_filter;
	uint32		transmode;
} CARD_CmdCtlFlg_t;

static const CARD_CmdCtlFlg_t s_cmdDetail[] = {
	// cmdindex,rsp,transmode
	//#define CMDname                       cmdindex    ,data int filter    +   (cmd int filter+)rsp(+cmd error filter) + ,data error filter			,transmode
	{CARD_CMD0_GO_IDLE_STATE	,0	,NULL		| CARD_SDIO_NO_RSP	|NULL						,NULL},
	{CARD_CMD1_SEND_OP_COND		,1	,NULL		| CARD_SDIO_R3		|NULL						,NULL},
	{CARD_CMD2_ALL_SEND_CID		,2	,NULL		| CARD_SDIO_R2		|NULL						,NULL},
	{CARD_CMD3_SET_RELATIVE_ADDR	,3	,NULL		| CARD_SDIO_R1		|NULL						,NULL},
	{CARD_CMD6_APP_SET_BUS_WIDTH	,6	,NULL		| CARD_SDIO_R1		|NULL						,NULL},
	{CARD_CMD7_SELECT_DESELECT_CARD	,7	,NULL		| CARD_SDIO_R1		|NULL						,NULL},
	{CARD_CMD8_IF_COND_SD		,8	,NULL		| CARD_SDIO_R7		|NULL						,NULL},
	{CARD_CMD12_STOP_TRANSMISSION	,12	,SIG_TRANS_CMP	| CARD_SDIO_R1B		|NULL						,NULL},	//It is auto performed by Host
	{CARD_CMD13_SEND_STATUS		,13	,NULL		| CARD_SDIO_R1		|NULL						,NULL},
	{CARD_CMD16_SET_BLOCKLEN	,16	,NULL		| CARD_SDIO_R1		|NULL						,NULL},
	{CARD_CMD18_READ_MULTIPLE_BLOCK	,18	,SIG_TRANS_CMP	| CARD_SDIO_R1		|ERR_DATA_END | ERR_DATA_CRC | ERR_DATA_TIMEOUT	,TRANS_MODE_MULTI_BLOCK | TRANS_MODE_READ | TRANS_MODE_BLOCK_COUNT_EN | TRANS_MODE_DMA_EN | CMD_HAVE_DATA},
	{CARD_ACMD6_SET_EXT_CSD		,6	,NULL		| CARD_SDIO_R1B		|NULL						,NULL},
	{CARD_ACMD41_SEND_OP_COND	,41	,NULL		| CARD_SDIO_R3		|NULL						,NULL},
	{CARD_ACMD55_APP_CMD		,55	,NULL		| CARD_SDIO_R1		|NULL						,NULL},
	{CARD_CMD8_IF_COND_MMC		,8	,SIG_TRANS_CMP		| CARD_SDIO_R1		|ERR_DATA_END | ERR_DATA_CRC | ERR_DATA_TIMEOUT	, TRANS_MODE_READ | TRANS_MODE_DMA_EN | CMD_HAVE_DATA},
	{CARD_CMDMAX			,0	,NULL		| CARD_SDIO_NO_RSP	|NULL						,NULL}
};

#endif //_SDIO_REG_V3_H_


#ifndef _SPRD_UFS_H
#define _SPRD_UFS_H

#include <asm/types.h>


/* UFS DEVICE Spec Versions */
#define UFS_DEVICE_SPEC_1_1	0x0110
#define UFS_DEVICE_SPEC_2_0	0x0200

/* Versions of UFSHCI specification that the controller implementation supports */
#define DWC_UFS_HC_VERSION_1_1 0x00010100
#define DWC_UFS_HC_VERSION_2_0 0x00000200
#define DWC_UFS_HC_VERSION_2_1 0x00000210

/* General Macros Used in Driver */
#define BIT(n)                 (1L     << (n))
#define LOWER_32_BITS(x)       ((uint32_t)((x)    &  0xFFFFFFFFUL))
#define UPPER_32_BITS(x)       ((uint32_t)((x)    >> 32))
#define UIC_GET_CMD                                0x1
#define UIC_SET_CMD                                0x2
#define UIC_PEER_GET_CMD                                0x3
#define UIC_ENDPOINT_RESET_CMD   0x15
#define UIC_LINK_STARTUP_CMD   0x16
#define UIC_EXIT_HIBERNATE     0x18
#define MAX_PRDT_ENTRIES       128
#define PRDT_BUFFER_SIZE       SZ_256K
#define TOTAL_PRDT_CAP		((MAX_PRDT_ENTRIES) * (PRDT_BUFFER_SIZE))
#define LOGICAL_BLK_SIZE       4096
#define NUM_OF_DESC            1
#define ALIGN_SIZE             1024
#define LOOPBACK_DEFAULT       0xb01
#define CLK_DIV_DEFAULT        0x1A
#define DISABLE_CLK_GATE     0x101B6000
#define RETRY_CNT              2000
#define RW_RETRY_CNT     200000
#define HCE_RESET              0x1
#define SENSE_KEY_INDEX        2
#define CMD_DESC_ALIGNMENT     128
#define ALIGNED_UPIU_SIZE      512
#define SCSI_TRANS_TYPE        0x21
#define NOP_TRANS_TYPE         0x20
#define UNIT_DESCS_COUNT       8
#define RPMB_DATA_SIZE         256
#define RPMB_FRAME_SIZE        512
#define CAPCITY_ADJ_FACTOR 1
#define PWR_LOCAL   1



#define UFS_MAX_LU_NUM    8
#define UFS_MAX_CARD_NUM   0
#define UFS_MAX_DEV_NUM ((UFS_MAX_LU_NUM) + (UFS_MAX_CARD_NUM))
#define LU_INFO_DIFF    0
#define LU_INFO_SAME  1
#define LU_INFO_ILLEGAL  -1

#define LOCK_CONFIGURATION    1
#define BOOT_LU_A_ENABLE	1

/*Uni-Pro DME*/
#define PA_ACTIVETXDATALANES	0x1560
#define PA_CONNECTEDTXDATALANES	0x1561
#define PA_TXGEAR		0x1568
#define PA_TXTERMINATION	0x1569
#define PA_HSSERIES		0x156A
#define PA_PWRMODE		0x1571
#define PA_ACTIVERXDATALANES	0x1580
#define PA_CONNECTEDRXDATALANES	0x1581
#define PA_RXGEAR		0x1583
#define PA_RXTERMINATION	0x1584
#define PA_MAXRXPWMGEAR		0x1586
#define PA_MAXRXHSGEAR		0x1587

/*
 * UFSStatus/Error Macros used as return values for all functions
 */
enum {
	UFS_SUCCESS			 =  0x0,
	/* OCS   ERROR Macros */
	UFS_INVALID_CMD_TABLE_ATTR	 = -0x1,
	UFS_INVALID_PRDT_ATTR		 = -0x2,
	UFS_MISMATCH_DATA_BUF_SIZE	 = -0x3,
	UFS_MISMATCH_RESP_UPIU_SIZE	 = -0x4,
	UFS_COMMUNICATION_FAILURE	 = -0x5,
	UFS_ABORTED			 = -0x6,
	UFS_FATAL_ERROR			 = -0x7,

	/* General Errors */
	UFS_TIMEOUT			 = -0x8,
	UFS_INVALID_RESPONSE	 = -0x9,
	UFS_UNKNOWN                  = -0xa,
	UFS_CHECK_CONDITOIN		 = -0xb,
	UFS_INVALID_OCS		 = -0xf,
	UFS_CONFIG_DESC_LOCKED       = -0x10,
	UFS_INVALID_PARTITIONING     = -0x11,
	UFS_TARGET_FAILURE           = -0x12,
	UFS_SBF_ERROR                = -0x13,
	UFS_HCF_ERROR                = -0x14,
	UFS_DF_ERROR                 = -0x15,
	UFS_UNSUPPORTED_LB_SIZE      = -0x16,
	UFS_FDEVICE_INIT_FAIL        = -0x17,

	/* Query resp errors */
	UFS_NON_READABLE_PARAM       = -0xf6,
	UFS_NON_WRITABLE_PARAM       = -0xf7,
	UFS_WRITTEN_PARAM            = -0xf8,
	UFS_INVALID_LENGTH           = -0xf9,
	UFS_INVALID_VALUE            = -0xfa,
	UFS_INVALID_SELECTOR         = -0xfb,
	UFS_INVALID_INDEX            = -0xfc,
	UFS_INVALID_IDN              = -0xfd,
	UFS_INVALID_OPCODE           = -0xfe,
	UFS_GENERAL_FAILURE          = -0xff,

	/* Sense Data Errors */
	UFS_RECOVERED_ERROR          = -0x21,
	UFS_LUN_NOT_READY            = -0x22,
	UFS_MEDIUM_ERROR             = -0x23,
	UFS_HARDWARE_ERROR           = -0x24,
	UFS_ILLEGAL_REQUEST          = -0x25,
	UFS_UNIT_ATTENTION           = -0x26,
	UFS_DATA_PROTECT             = -0x27,
	UFS_BLANK_CHECK              = -0x28,
	UFS_VENDOR_SPECIFIC          = -0x29,
	UFS_ABORTED_CMD              = -0x2b,
	UFS_VOLUME_OVERFLOW          = -0x2d,
	UFS_MISCOMPARE               = -0x2e,

	/* RPMB Operation Results */
	UFS_RPMB_GENERAL_FAILURE     = -0x31,
	UFS_AUTHENTICATION_FAILURE   = -0x32,
	UFS_COUNTER_FAILURE          = -0x33,
	UFS_ADDRESS_FAILURE          = -0x34,
	UFS_WRITE_FAILURE            = -0x35,
	UFS_READ_FAILURE             = -0x36,
	UFS_AUTH_KEY_NOT_PROGRAMMED  = -0x37,
	UFS_RPMB_WR_COUNTER_EXPIRED  = -0x38,
	UFS_NONCE_MISMATCH           = -0x39,
	UFS_MAC_MISMATCH             = -0x3a

};

enum lu_bootable {
	NONE_BOOT       = 0x00,
	MAIN_BOOT   = 0x01,
	ALTERNATE_BOOT      = 0x02
};

enum lu_memory_type {
	NORMAL_MEMORY = 0x00,
	SYS_CODE_MEMORY = 0x01,
	NON_PERSISTENT_MEMORY = 0x02,
	ENHANCED_MEMORY_1 = 0x03,
	ENHANCED_MEMORY_2 = 0x04,
	ENHANCED_MEMORY_3 = 0x05,
	ENHANCED_MEMORY_4 = 0x06
};

enum lu_provisioning_type {
	PROV_DISABLE = 0x00,
	PROV_ENABLE = 0x02,
	PROV_ENABLE_WITH_TPRZ = 0x03
};
#if 1
enum lu_write_protect {
	WRITE_NO_PROTECT = 0x0,
	WRITE_PROTECT_POWERON = 0x1,
	WRITE_PROTECT_PERMANENT = 0x2,
	WRITE_PROTECT_EXTENSION = 0x3
};

enum lu_data_reliability {
	DATA_PROTECTED,
	DATA_NO_PROTECTED
};

struct lu_specific_cfg_tbl {
	int 			lu_index;
	enum lu_bootable bootable;
	uint32_t               log2blksz;
	uint64_t               blkcnt;
	uint16_t 		   lu_context;
	enum lu_memory_type memory_type;
};

struct lu_common_cfg_tbl {
	enum lu_write_protect write_protect;
	enum lu_provisioning_type provisioning_type;
	enum lu_data_reliability data_reliability;
};
#endif

struct lu_info_tbl {
	int 			lu_index;
	enum lu_bootable bootable;
	enum lu_write_protect write_protect;
	enum lu_memory_type memory_type;
	enum lu_provisioning_type provisioning_type;
	enum lu_data_reliability data_reliability;
	uint32_t               log2blksz;
	uint64_t               blkcnt;
	uint32_t		   erase_block_sz;
	uint16_t 		   lu_context;
};


struct ufs_driver_info {
	void			*base_addr;
	struct dwc_ufs_tcd      *cmd_desc;
	struct dwc_ufs_utrd     *utrd_desc;
	struct dwc_ufs_utmrd    *utm_desc;
	uint8_t                 unit_offset;  /* Offset of first Unit Configuration Desc */
	uint8_t                 unit_length;  /* Length Of Configuration Unit Descriptor */
	uint8_t		   lu_num;
	uint8_t		   wlu_num;
	uint8_t		   boot_enable;
	uint8_t		   max_context;
	uint16_t 		wSpecVersion; /* Device Specification version */
    	uint32_t 		dwc_ufs_version; /* Versions of UFSHCI specification that the controller implementation supports*/
	uint32_t		   alloc_unit_sz;  /*in unit of 512 bytes*/
	uint32_t		prdt_entry_size;   /*Physical Region Description Table entry size, unit of bytes*/
	uint64_t		max_prdt_cap;   /*Physical Region Description Table total capability, unit of bytes*/
	uint64_t		dev_total_cap;   /*total capacity, in unit of 512 bytes*/

	block_dev_desc_t  block_dev[UFS_MAX_DEV_NUM];
	struct lu_info_tbl       lu_info[UFS_MAX_LU_NUM];
} ;


/*Put it here temporarily*/
#define REG_BASE_ADDRESS         0x71900000

/* UFSHCD Registers Offsets */
#define DW_UFS_CAP        0x00
#define DW_UFS_VER        0x08
#define DW_UFS_IS         0x20
#define DW_UFS_HCS        0x30
#define DW_UFS_HCE        0x34
#define DW_UFS_UTRLBA     0x50
#define DW_UFS_UTRLBAU    0x54
#define DW_UFS_UTRLDBR    0x58
#define DW_UFS_UTRLCLR    0x5C
#define DW_UFS_UTRLRSR    0x60
#define DW_UFS_UTMRLBA    0x70
#define DW_UFS_UTMRLBAU   0x74
#define DW_UFS_UTMRLDBR   0x78
#define DW_UFS_UTMRLRSR   0x80
#define DW_UFS_UICCMD     0x90
#define DW_UFS_UICCMDARG1 0x94
#define DW_UFS_UICCMDARG2 0x98
#define DW_UFS_UICCMDARG3 0x9C
#define DW_UFS_RESET_MISC 0xB0
#define DW_UFS_OCPTHRTL   0xC0
#define DW_UFS_LBMCFG     0xF0
#define DW_UFS_HCLKDIV    0xFC

/*
 * Register Fields
 */
#define DW_UFS_HCS_DP    BIT(0)
#define DW_UFS_IS_UE	 BIT(2)
#define DW_UFS_IS_UPMS   BIT(4)
#define DW_UFS_IS_UCCS   BIT(10)
#define DW_UFS_IS_DFES   BIT(11)
#define DW_UFS_IS_HCFES   BIT(16)
#define DW_UFS_IS_SBFES   BIT(17)
#define DW_UFS_HCS_UCRDY BIT(3)
#define DW_UFS_CAPS_64AS BIT(24)

#define IS_FATAL_ERROR	(DW_UFS_IS_DFES |\
				DW_UFS_IS_HCFES |\
				DW_UFS_IS_SBFES)

/* UFS Command Opcodes */
#define READ_DESC_OPCODE   0x1
#define WRITE_DESC_OPCODE  0x2
#define READ_ATTR_OPCODE   0x3
#define WRITE_ATTR_OPCODE  0x4
#define READ_FLAG_OPCODE   0x5
#define SET_FLAG_OPCODE    0x6
#define CLEAR_FLAG_OPCODE  0x7
#define TOGGLE_FLAG_OPCODE 0x8

/* Descriptor Idn's */
#define DEVICE_DESC        0x00
#define CONFIGURATION_DESC 0x01
#define UNIT_DESC          0x02
#define GEOMETRY_DESC      0x07

#define DEVICE_DESC_LENGTH 0x1f
#define UNIT_DESC_LENGTH   0x23
#define GEOMETRY_DESC_LENGTH 0x44
#define CONFIGURATION_DESC_LENGTH 0x90

#define STANDARD_RD_REQ 0x01
#define STANDARD_WR_REQ 0x81

/* UTP Transfer Request Data Direction (DD) */
enum {
	UTP_NO_DATA_TRANSFER	= 0x00,
	UTP_HOST_TO_DEVICE	= 0x02,
	UTP_DEVICE_TO_HOST	= 0x04
};

/* UPIU Read/Write flags */
enum {
	UPIU_CMD_FLAGS_NONE	= 0x00,
	UPIU_CMD_FLAGS_WRITE	= 0x20,
	UPIU_CMD_FLAGS_READ	= 0x40
};

enum {
	UTP_SCSI_COMMAND		= 0x00,
	UTP_NATIVE_UFS_COMMAND		= BIT(4),
	UTP_DEVICE_MANAGEMENT_FUNCTION	= (2 << 4)
};

enum {
	UTP_UFS_STORAGE_COMMAND		= BIT(4)
};

enum flags_id {
	FDEVICE_INIT    = 0x1,
	FPERMANANT_WPEN = 0x2,
	FPOWERON_WPEN   = 0x3,
	FBG_OPSEN       = 0x4,
	FPURGE_OPSEN    = 0x6,
	FPHYRES_REMOVAL = 0x8,
	FBUSY_RTC       = 0x9
};

enum tm_task_type {
	ABORT_TASK       = 0x1,
	ABORT_TASK_SET   = 0x2,
	CLEAR_TASK_SET   = 0x4,
	LUN_RESET        = 0x8,
	QUERY_TASK       = 0x80,
	QUERY_TASK_SET   = 0x80
};

enum attr_id {
	B_BOOT_LUNEN              = 0x0,
	B_CURRENT_PM              = 0x2,
	B_ACTIV_ICC_LEVEL         = 0x3,
	B_OUT_OF_ORDER_DATAEN     = 0x4,
	B_BCKGND_OPS_STATUS       = 0x5,
	B_PURGE_STATUS            = 0x6,
	B_MAX_DATA_IN_SIZE        = 0x7,
	B_MAX_DATA_OUT_SIZE       = 0x8,
	D_DYN_CAP_NEEDED          = 0x9,
	B_REFCLK_FREQ             = 0xA,
	B_CONFIG_DESC_LOCK        = 0xB,
	B_MAX_NUM_OF_RTT          = 0xC,
	W_EXCEPTION_EVENT_CONTROL = 0xD,
	W_EXCEPTION_EVENT_STATUS  = 0xE,
	D_SECONDS_PASSED          = 0xF,
	W_CONTEXT_CONF            = 0x10,
	D_CORR_PRG_BLKNUM         = 0x11
};

enum dma_data_direction {
	DMA_BIDIRECTIONAL = 0,
	DMA_TO_DEVICE     = 1,
	DMA_FROM_DEVICE   = 2,
	DMA_NONE          = 3
};

/* Operation Type for RPMB tasks */
enum opn_type {
WRITE_COUNTER_READ   = 0x00,
WRITE_RPMB_DATA      = 0x01,
READ_RPMB_DATA       = 0x02,
RESULT_REGISTER_READ = 0x03,
AUTH_KEY_DATA        = 0x04
};

struct ufs_pa_layer_attr {
	uint32_t gear_rx;
	uint32_t gear_tx;
	uint32_t lane_rx;
	uint32_t lane_tx;
	uint32_t pwr_rx;
	uint32_t pwr_tx;
	uint32_t hs_rate;
};

/* PA power modes */
enum {
	FAST_MODE	= 1,
	SLOW_MODE	= 2,
	FASTAUTO_MODE	= 4,
	SLOWAUTO_MODE	= 5,
	UNCHANGED	= 7,
};

/* PA TX/RX Frequency Series */
enum {
	PA_HS_MODE_A	= 1,
	PA_HS_MODE_B	= 2,
};

enum ufs_hs_gear_tag {
	UFS_HS_DONT_CHANGE,	/* Don't change Gear */
	UFS_HS_G1,		/* HS Gear 1 (default for reset) */
	UFS_HS_G2,		/* HS Gear 2 */
	UFS_HS_G3,		/* HS Gear 3 */
};

/*
 * Host byte codes
 * SCSI status Macros for SCSI result
 */

#define DID_OK          0x00	/* NO error */
#define DID_ERROR       0x07	/* Internal error */

/* SCSI Status Macros */
#define SAM_STAT_GOOD            0x00
#define SAM_STAT_CHECK_CONDITION 0x02

/*
 * Command UPIU Structure
 */
struct dwc_ufs_cmd_upiu
{
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t cmd_set_type;	/* Only LS nibble is valid. Others Reserved */
	uint8_t reserved_1[3];
	uint8_t tot_ehs_len;
	uint8_t reserved_2;
	uint16_t data_seg_len;
	uint32_t exp_data_xfer_len;
	uint8_t cdb[16];		/* UFS/SCSI command descriptor block */
};

/*
 * Query UPIU Structure
 */
struct dwc_ufs_query_upiu
{
	uint8_t trans_type;
	uint8_t flags;
	uint8_t reserved_1;
	uint8_t task_tag;
	uint8_t reserved_2;
	uint8_t query_func;
	uint8_t query_resp; /* valid only wen used for response */
	uint8_t reserved_3;
	uint8_t tot_ehs_len;
	uint8_t reserved_4;
	uint16_t data_seg_len;
	uint8_t tsf[16];
	uint8_t reserved_5[4];
};

/*
 * NOP OUT UPIU Structure
 */
struct dwc_ufs_nop_req_upiu
{
	uint8_t trans_type;
	uint8_t flags;
	uint8_t reserved_1;
	uint8_t task_tag;
	uint8_t reserved_2[4];
	uint8_t tot_ehs_len;
	uint8_t reserved_3;
	uint16_t data_seg_len;
	uint8_t reserved_4[20];
};

/*
 * NOP IN UPIU Structure
 */
struct dwc_ufs_nop_resp_upiu
{
	uint8_t trans_type;
	uint8_t flags;
	uint8_t reserved_1;
	uint8_t task_tag;
	uint8_t reserved_2[2];
	uint8_t response;
	uint8_t reserved_3;
	uint8_t tot_ehs_len;
	uint8_t device_info;
	uint16_t data_seg_len;
	uint8_t reserved_4[20];
};

/*
 * Transfer Response UPIU Structure
 */
struct dwc_ufs_xfer_resp_upiu
{
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t cmd_set_type;	/* Only LS nibble is valid. Others Reserved */
	uint8_t reserved_1;
	uint8_t response;
	uint8_t status;		/* This is SCSI status */
	uint8_t tot_ehs_len;
	uint8_t device_info;
	uint16_t data_seg_len;
	uint32_t residual_xfer_count;
	uint8_t reserved_2[4];
	uint8_t reserved_3[4];
	uint8_t reserved_4[4];
	uint8_t reserved_5[4];
	uint16_t sense_data_len;
	uint8_t sense_data[18];
};

struct dwc_ufs_prd {
	uint32_t    base_addr;
	uint32_t    upper_addr;
	uint32_t    reserved1;
	uint32_t    size;
};

/*
 * Command Descriptor Structure
 */
struct dwc_ufs_tcd {
	uint8_t            command_upiu[ALIGNED_UPIU_SIZE];
	uint8_t            response_upiu[ALIGNED_UPIU_SIZE];
	struct dwc_ufs_prd prdt_table[MAX_PRDT_ENTRIES];
};

struct dwc_ufs_utrd {
	uint8_t reserved_1[3];
	uint8_t ct_and_flags;
	uint8_t reserved_2[4];
	uint8_t ocs;
	uint8_t reserved_3[3];
	uint8_t reserved_4[4];

	uint32_t ucdba;        /* Only bits 31:7 are valid; 128B Aligned addr */
	uint32_t ucdbau;
	uint16_t resp_upiu_length;
	uint16_t resp_upiu_offset;

	uint16_t prdt_length;
	uint16_t prdt_offset;
};

/**
 * dwc_ufs_tm_req_upiu
 * Task Management Request UPIU structure
 * Size of this structure is 32 bytes
 * The data structure should support 32 bit or 64 bit memory buffer address
 * space. This structure is in BIG ENDINA Format
 */
struct dwc_ufs_tm_req_upiu
{
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t reserved_1;
	uint8_t tm_fn;
	uint8_t reserved_2[2];
	uint8_t tot_ehs_len;
	uint8_t reserved_3;
	uint16_t data_seg_len;
	uint32_t input_param_1;
	uint32_t input_param_2;
	uint32_t input_param_3;
	uint32_t reserved_4;
	uint32_t reserved_5;
};

/**
 * dwc_ufs_tm_resp_upiu
 * Task Management Response UPIU structure
 * Size of this structure is 32 bytes
 * The data structure should support 32 bit or 64 bit memory buffer address
 * space. This structure is in BIG ENDINA Format
 */
struct dwc_ufs_tm_resp_upiu
{
	uint8_t trans_type;
	uint8_t flags;
	uint8_t lun;
	uint8_t task_tag;
	uint8_t reserved_1[2];
	uint8_t response;
	uint8_t reserved_2;
	uint8_t tot_ehs_len;
	uint8_t reserved_3;
	uint16_t data_seg_len;
	uint32_t output_param_1;
	uint32_t output_param_2;
	uint8_t reserved_4[4];
	uint8_t reserved_5[4];
	uint8_t reserved_6[4];
};

struct dwc_ufs_utmrd {
	uint8_t reserved_1[3];
	uint8_t intr_flag;   /* only one bit is valid */
	uint32_t reserved_2;
	uint8_t ocs;
	uint8_t reserved_3[3];
	uint32_t reserved_4;

	struct dwc_ufs_tm_req_upiu tm_req_upiu;
	struct dwc_ufs_tm_resp_upiu tm_resp_upiu;
};

struct pwrModeParams
{
	uint8_t txGear;
	uint8_t rxGear;
	uint8_t hsSeries;
	uint8_t txLanes;
	uint8_t rxLanes;
	uint8_t pwrMode;
};

struct partitionDesc
{
	uint8_t bootLunId;
	uint8_t writeProtect;
	uint8_t memoryType;
	uint8_t dataReliability;
	uint8_t blockSize;            /* bLogicalBlocksize Def: 4096 */
	uint8_t provType;            /* Fully provisioning or Thin provisioning */
	uint16_t pad_1;               /* Padding for 32 bit alignment */
	uint32_t lu_capacity;	      /* Capacity of LUN for provisioning in Mega bytes */
	uint32_t dNumAllocUnits;      /* Used internally by driver */
};

struct partitionDescTable {
	uint8_t bNumberLU;            /* Used internally by driver */
	uint8_t bAllocationUnitSize;  /* Used internally by driver */
	uint32_t dSegmentSize;        /* used internally by driver */
	struct partitionDesc *partitionDescPtr[8];
};

struct desc_params
{
	void                 *req_upiu;
	struct partitionDesc **part_desc;
	uint8_t              opcode;
	uint8_t              desc_idn;
	uint8_t              desc_index;
	uint8_t              length;
};


struct ufs_dev_desc_tbl {
	uint8_t	bLength;
	uint8_t	bDescriptorType;
	uint8_t	bDevice;
	uint8_t	bDeviceClass;
	uint8_t	bDeviceSubClass;
	uint8_t	bProtocol;
	uint8_t	bNumberLU;
	uint8_t	bNumberWLU;
	uint8_t	bBootEnable;
	uint8_t	bDescrAccessEn;
	uint8_t	bInitPowerMode;
	uint8_t	bHighPriorityLUN;
	uint8_t	bSecureRemovalType;
	uint8_t	bSecurityLU;
	uint8_t	bBackgroundOpsTermLat;
	uint8_t	bInitActiveICCLevel;
	uint16_t	wSpecVersion;
	uint16_t	wManufactureDate;
	uint8_t	iManufacturerName;
	uint8_t	iProductName;
	uint8_t	iSerialNumber;
	uint8_t	iOemID;
	uint16_t	wManufacturerID;
	uint8_t	bUD0BaseOffset;
	uint8_t	bUDConfigPLength;
	uint8_t	bDeviceRTTCap;
	uint16_t	wPeriodicRTCUpdate;
	uint8_t	reserved[35];
} __attribute__ ((packed));

struct ufs_geo_desc_tbl {
	uint8_t	bLength;
	uint8_t	bDescriptorType;
	uint8_t	bMediaTechnology;
	uint8_t	reserved_1;
	uint64_t	qTotalRawDeviceCapacity;
	uint8_t	reserved_2;
	uint32_t	dSegmentSize;
	uint8_t	bAllocationUnitSize;
	uint8_t	bMinAddrBlockSize;
	uint8_t	bOptimalReadBlockSize;
	uint8_t	bOptimalWriteBlockSize;
	uint8_t	bMaxInBufferSize;
	uint8_t	bMaxOutBufferSize;
	uint8_t	bRPMB_ReadWriteSize;
	uint8_t	reserved_3;
	uint8_t	bDataOrdering;
	uint8_t	bMaxContexIDNumber;
	uint8_t	bSysDataTagUnitSize;
	uint8_t	bSysDataTagResSize;
	uint8_t	bSupportedSecRTypes;
	uint16_t	wSupportedMemoryTypes;
	uint32_t	dSystemCodeMaxNAllocU;
	uint8_t	ignored[32];
} __attribute__ ((packed));


struct ufs_unit_desc_tbl {
	uint8_t	bLength;
	uint8_t	bDescriptorType;
	uint8_t	bUnitIndex;
	uint8_t	bLUEnable;
	uint8_t	bBootLunID;
	uint8_t	bLUWriteProtect;
	uint8_t	bLUQueueDepth;
	uint8_t	reserved;
	uint8_t	bMemoryType;
	uint8_t	bDataReliability;
	uint8_t	bLogicalBlockSize;
	uint64_t	qLogicalBlockCount;
	uint32_t	dEraseBlockSize;
	uint8_t	bProvisioningType;
	uint64_t	qPhyMemResourceCount;
	uint16_t	wContextCapabilities;
	uint8_t	bLargeUnitGranularity_M1;
} __attribute__ ((packed));

struct ufs_unit_cfg_tbl {
	uint8_t	bLUEnable;
	uint8_t	bBootLunID;
	uint8_t	bLUWriteProtect;
	uint8_t	bMemoryType;
	uint32_t	dNumAllocUnits;
	uint8_t	bDataReliability;
	uint8_t	bLogicalBlockSize;
	uint8_t	bProvisioningType;
	uint16_t	wContextCapabilities;
	uint8_t	reserved[3];
}  __attribute__ ((packed));

struct ufs_cfg_desc_tbl {
	uint8_t	bLength;
	uint8_t	bDescriptorType;
	uint8_t	reserved_1;
	uint8_t	bBootEnable;
	uint8_t	bDescrAccessEn;
	uint8_t	bInitPowerMode;
	uint8_t	bHighPriorityLUN;
	uint8_t	bSecureRemovalType;
	uint8_t	bInitActiveICCLevel;
	uint16_t	wPeriodicRTCUpdate;
	uint8_t	reserved_2[5];
	struct ufs_unit_cfg_tbl	unit_cfg[UFS_MAX_LU_NUM];
} __attribute__ ((packed));

struct um_block_descriptor {
	uint64_t um_block_addr;
	uint32_t um_block_sz;
	uint32_t   reserve;
} __attribute__ ((packed));


struct unmap_para_list {
	uint16_t um_data_len;
	uint16_t um_block_desc_len;
	uint32_t   reserve;
	/*support only one block descriptor*/
	struct um_block_descriptor ub_desc;
} __attribute__ ((packed));

#define uswap_16(x) \
        ((((x) & 0xff00) >> 8) | \
         (((x) & 0x00ff) << 8))
#define uswap_32(x) \
        ((((x) & 0xff000000) >> 24) | \
         (((x) & 0x00ff0000) >>  8) | \
         (((x) & 0x0000ff00) <<  8) | \
         (((x) & 0x000000ff) << 24))
#define _uswap_64(x, sfx) \
        ((((x) & 0xff00000000000000##sfx) >> 56) | \
         (((x) & 0x00ff000000000000##sfx) >> 40) | \
         (((x) & 0x0000ff0000000000##sfx) >> 24) | \
         (((x) & 0x000000ff00000000##sfx) >>  8) | \
         (((x) & 0x00000000ff000000##sfx) <<  8) | \
         (((x) & 0x0000000000ff0000##sfx) << 24) | \
         (((x) & 0x000000000000ff00##sfx) << 40) | \
         (((x) & 0x00000000000000ff##sfx) << 56))
# define uswap_64(x) _uswap_64(x, ull)
# define cpu_to_le16(x)         (x)
# define cpu_to_le32(x)         (x)
# define cpu_to_le64(x)         (x)
# define le16_to_cpu(x)         (x)
# define le32_to_cpu(x)         (x)
# define le64_to_cpu(x)         (x)
# define cpu_to_be16(x)         uswap_16(x)
# define cpu_to_be32(x)         uswap_32(x)
# define cpu_to_be64(x)         uswap_64(x)
# define be16_to_cpu(x)         uswap_16(x)
# define be32_to_cpu(x)         uswap_32(x)
# define be64_to_cpu(x)         uswap_64(x)



#endif

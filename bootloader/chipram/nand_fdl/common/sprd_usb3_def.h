/******************************************************************************

  Copyright (C), 2001-2014, Spreatrum Communications Inc.

 ******************************************************************************
  File Name     : sprd_usb3_def.h
  Version       : 1.0 Beta
  Author        : Miao.Zhu
  Created       : 2014/12/25
  Last Modified :
  Description   : This file provides most structures, resigter, USB protocols
  and etc. definitions for USB3.0
  Function List : NA
  History       :
  1.Date        : 2014/12/25
    Author      : Miao.Zhu
    Modification: Created file
******************************************************************************/
#ifndef __USB3_TYPES_H__
#define __USB3_TYPES_H__

typedef unsigned char uByte;
typedef unsigned char uWord[2];
typedef unsigned char uDWord[4];
#define UGETW(w) ((w)[0] | ((w)[1] << 8))

#define upper_32_bits(n) (u32)(((n) >> 16) >> 16)
#define lower_32_bits(n) (u32)(n)

#define UPACKED		__attribute__ ((__packed__))

#define __iomem /* */

/** USB3.0 speed */
#define USB_SPEED_UNKNOWN	0
#define USB_SPEED_LOW       1
#define USB_SPEED_FULL		2
#define USB_SPEED_HIGH		3
#define USB_SPEED_SUPER	    4


/** Maxpacket size for EP0, defined by USB3 spec */
#define MAX_EP0_SIZE	512

/** Maxpacket size for any EP, defined by USB3 spec */
#define MAX_PACKET_SIZE	1024

/**
 * States of EP0
 */
typedef enum ep0_state {
	EP0_IDLE,
	EP0_IN_DATA_PHASE,
	EP0_OUT_DATA_PHASE,
	EP0_IN_WAIT_NRDY,
	EP0_OUT_WAIT_NRDY,
	EP0_IN_STATUS_PHASE,
	EP0_OUT_STATUS_PHASE,
	EP0_STALL,
} ep0state_e;

typedef enum pcd_state {
	PCD_STATE_UNCONNECTED,	/* no host */
	PCD_STATE_DEFAULT,
	PCD_STATE_ADDRESSED,
	PCD_STATE_CONFIGURED,
} pcdstate_e;

typedef struct {
	uByte		bmRequestType;
	uByte		bRequest;
	uWord		wValue;
	uWord		wIndex;
	uWord		wLength;
} UPACKED usb_device_request_t;

#define UT_GET_DIR(a) ((a) & 0x80)
#define UT_WRITE		0x00
#define UT_READ			0x80

#define UT_GET_TYPE(a) ((a) & 0x60)
#define UT_STANDARD		0x00
#define UT_CLASS		0x20
#define UT_VENDOR		0x40

#define UT_GET_RECIPIENT(a) ((a) & 0x1f)
#define UT_DEVICE		0x00
#define UT_INTERFACE		0x01
#define UT_ENDPOINT		0x02
#define UT_OTHER		0x03

#define UR_GET_STATUS		0x00
#define UR_CLEAR_FEATURE	0x01
#define UR_SET_FEATURE		0x03
#define UR_SET_ADDRESS		0x05
#define UR_GET_DESCRIPTOR	0x06
#define UR_SET_CONFIG		0x09
#define UR_GET_INTERFACE	0x0a
#define UR_SET_INTERFACE	0x0b
#define UR_SYNCH_FRAME		0x0c
#define UR_SET_SEL		0x30
#define UF_U1_ENABLE		48
#define UF_U2_ENABLE		49

struct usb3_device;
struct usb3_pcd;

#ifdef USB3_DEBUG
/**
 * This enum represents the bit fields of the Core SoC Bus Configuration 0
 * Register (GSBUSCFG0).
 */
typedef enum gsbuscfg0_data {
    /** Bus Burst Len			<i>Access: R_W</i>.
     * - 0:   single
     * - 1:   incr
     * - 3:   incr4
     * - 7:   incr8
     * - 15:  incr16
     * - 31:  incr32  (non-AHB mode only)
     * - 63:  incr64  (non-AHB mode only)
     * - 127: incr128 (non-AHB mode only)
     * - 255: incr256 (non-AHB mode only)
     */
    SBUSCFG0_HBURSTLEN_BITS		= 0x000000ff,
    SBUSCFG0_HBURSTLEN_SHIFT		= 0,

    SBUSCFG0_INT_DMA_BURST_SINGLE	= 0,
    SBUSCFG0_INT_DMA_BURST_INCR		= 1,
    SBUSCFG0_INT_DMA_BURST_INCR4	= 3,
    SBUSCFG0_INT_DMA_BURST_INCR8	= 7,
    SBUSCFG0_INT_DMA_BURST_INCR16	= 15,
    SBUSCFG0_INT_DMA_BURST_INCR32	= 31,
    SBUSCFG0_INT_DMA_BURST_INCR64	= 63,
    SBUSCFG0_INT_DMA_BURST_INCR128	= 127,
    SBUSCFG0_INT_DMA_BURST_INCR256	= 255,

    /** Descriptor Write is Posted		<i>Access: R_W</i> */
    SBUSCFG0_DES_WR_POST_BIT		= 0x00000100,
    SBUSCFG0_DES_WR_POST_SHIFT		= 8,

    /** Data Write is Posted		<i>Access: R_W</i> */
    SBUSCFG0_DAT_WR_POST_BIT		= 0x00000200,
    SBUSCFG0_DAT_WR_POST_SHIFT		= 9,

    /** Descriptor Access is Big-Endian	<i>Access: R_W</i> */
    SBUSCFG0_DES_BIG_END_BIT		= 0x00000400,
    SBUSCFG0_DES_BIG_END_SHIFT		= 10,

    /** Data Access is Big-Endian		<i>Access: R_W</i> */
    SBUSCFG0_DAT_BIG_END_BIT		= 0x00000800,
    SBUSCFG0_DAT_BIG_END_SHIFT		= 11,

    /** Store and Forward Mode		<i>Access: R_W</i> */
    SBUSCFG0_STORE_AND_FORWARD_BIT	= 0x00001000,
    SBUSCFG0_STORE_AND_FORWARD_SHIFT	= 12,

    /** Force Single Request		<i>Access: R_W</i> */
    SBUSCFG0_SING_REQ_BIT		= 0x00004000,
    SBUSCFG0_SING_REQ_SHIFT		= 14,

    /** Descriptor Readback Enable		<i>Access: R_W</i> */
    SBUSCFG0_READ_AFTER_WRITE_BIT	= 0x00008000,
    SBUSCFG0_READ_AFTER_WRITE_SHIFT	= 15,

    /** Descriptor Write Request Info	<i>Access: R_W</i> */
    SBUSCFG0_DES_WR_REQ_INFO_BITS	= 0x000f0000,
    SBUSCFG0_DES_WR_REQ_INFO_SHIFT	= 16,

    /** Data Write Request Info		<i>Access: R_W</i> */
    sBUSCFG0_DAT_WR_REQ_INFO_BITS	= 0x00f00000,
    sBUSCFG0_DAT_WR_REQ_INFO_SHIFT	= 20,

    /** Descriptor Read Request Info	<i>Access: R_W</i> */
    SBUSCFG0_DES_RD_REQ_INFO_BITS	= 0x0f000000,
    SBUSCFG0_DES_RD_REQ_INFO_SHIFT	= 24,

    /** Data Read Request Info		<i>Access: R_W</i> */
    SBUSCFG0_DAT_RD_REQ_INFO_BITS	= 0xf0000000,
    SBUSCFG0_DAT_RD_REQ_INFO_SHIFT	= 28,
} gsbuscfg0_data_t;

/**
 * This enum represents the bit fields of the Core SoC Bus Configuration 1
 * Register (GSBUSCFG1).
 */
typedef enum gsbuscfg1_data {
    /** OCP Address Space For Descriptor	<i>Access: R_W</i> */
    SBUSCFG1_DES_ADDR_SPC_BITS		= 0x0000000f,
    SBUSCFG1_DES_ADDR_SPC_SHIFT		= 0,

    /** OCP Address Space For Data		<i>Access: R_W</i> */
    SBUSCFG1_DAT_ADDR_SPC_BITS		= 0x000000f0,
    SBUSCFG1_DAT_ADDR_SPC_SHIFT		= 4,
} gsbuscfg1_data_t;

/**
 * This enum represents the bit fields of the Core Tx Threshold Control
 * Register (GTXTHRCFG).
 */
typedef enum gtxthrcfg_data {
    /** Maximum Tx Burst Size		<i>Access: R_W</i> */
    TXTHRCTL_USB_MAX_TX_BURST_SIZE_BITS		= 0x00ff0000,
    TXTHRCTL_USB_MAX_TX_BURST_SIZE_SHIFT	= 16,

    /** Tx Multi-Packet Threshold Count	<i>Access: R_W</i> */
    TXTHRCTL_USB_TX_PKT_CNT_BITS		= 0x1f000000,
    TXTHRCTL_USB_TX_PKT_CNT_SHIFT		= 24,

    /** Tx Multi-Packet Threshold Enable	<i>Access: R_W</i> */
    TXTHRCTL_USB_TX_PKT_CNT_EN_BIT		= 0x20000000,
    TXTHRCTL_USB_TX_PKT_CNT_EN_SHIFT		= 29,
} gtxthrcfg_data_t;

/**
 * This enum represents the bit fields of the Core Rx Threshold Control
 * Register (GRXTHRCFG).
 */
typedef enum grxthrcfg_data {
    /** Maximum Rx Burst Size		<i>Access: R_W</i> */
    RXTHRCTL_USB_MAX_RX_BURST_SIZE_BITS		= 0x00f80000,
    RXTHRCTL_USB_MAX_RX_BURST_SIZE_SHIFT	= 19,

    /** Rx Multi-Packet Threshold Count	<i>Access: R_W</i> */
    RXTHRCTL_USB_RX_PKT_CNT_BITS		= 0x0f000000,
    RXTHRCTL_USB_RX_PKT_CNT_SHIFT		= 24,

    /** Rx Multi-Packet Threshold Enable	<i>Access: R_W</i> */
    RXTHRCTL_USB_RX_PKT_CNT_EN_BIT		= 0x20000000,
    RXTHRCTL_USB_RX_PKT_CNT_EN_SHIFT		= 29,
} grxthrcfg_data_t;
#endif
/**
 * This enum represents the bit fields of the Core Control
 * Register (GCTL).
 */
typedef enum gctl_data {
    /** Disable Clock Gating		<i>Access: R_W</i> */
    GCTL_DSBL_CLCK_GTNG_BIT	= 0x00000001,
    GCTL_DSBL_CLCK_GTNG_SHIFT	= 0,

    /** Global Hibernation Enable		<i>Access: R_W</i> */
    GCTL_GBL_HIBER_EN_BIT	= 0x00000002,
    GCTL_GBL_HIBER_EN_SHIFT	= 1,

    /** Disable Scrambling			<i>Access: R_W</i> */
    GCTL_DIS_SCRAMBLE_BIT	= 0x00000008,
    GCTL_DIS_SCRAMBLE_SHIFT	= 3,

    /** Scale-down Mode			<i>Access: R_W</i> */
    GCTL_SCALE_DOWN_BITS	= 0x00000030,
    GCTL_SCALE_DOWN_SHIFT	= 4,

    /** RAM Clock Select			<i>Access: R_W</i> */
    GCTL_RAM_CLK_SEL_BITS	= 0x000000c0,
    GCTL_RAM_CLK_SEL_SHIFT	= 6,

    /** Debug Attach			<i>Access: R_W</i> */
    GCTL_DEBUG_ATTACH_BIT	= 0x00000100,
    GCTL_DEBUG_ATTACH_SHIFT	= 8,

    /** Disable U1/U2 Timer Scaledown	<i>Access: R_W</i> */
    GCTL_U1U2_TIMER_SCALE_BIT	= 0x00000200,
    GCTL_U1U2_TIMER_SCALE_SHIFT	= 9,

    /** SOF ITP SYNC			<i>Access: R_W</i> */
    GCTL_SOFITPSYNC_BIT		= 0x00000400,
    GCTL_SOFITPSYNC_SHIFT	= 10,

    /** Core Soft Reset			<i>Access: R_W</i> */
    GCTL_CORE_SOFT_RST_BIT	= 0x00000800,
    GCTL_CORE_SOFT_RST_SHIFT	= 11,

    /** Port Capability Direction		<i>Access: R_W</i> */
    GCTL_PRT_CAP_DIR_BITS	= 0x00003000,
    GCTL_PRT_CAP_DIR_SHIFT	= 12,

    /** Port Capability Values */
    GCTL_PRT_CAP_HOST		= 1,
    GCTL_PRT_CAP_DEVICE		= 2,
    GCTL_PRT_CAP_OTG		= 3,

    /** Frame Scale Down			<i>Access: R_W</i> */
    GCTL_FRMSCLDWN_BITS		= 0x0000c000,
    GCTL_FRMSCLDWN_SHIFT	= 14,

    /** U2 Reset ECN			<i>Access: R_W</i> */
    GCTL_U2RSTECN_BIT		= 0x00010000,
    GCTL_U2RSTECN_SHIFT		= 16,

    /** Bypass SetAddress			<i>Access: R_W</i> */
    GCTL_BYPSSETADDR_BIT	= 0x00020000,
    GCTL_BYPSSETADDR_SHIFT	= 17,

    /** Master Filter Bypass		<i>Access: R_W</i> */
    GCTL_MASTERFILTBYPASS_BIT	= 0x00040000,
    GCTL_MASTERFILTBYPASS_SHIFT	= 18,

    /** Power Down Scale			<i>Access: R_W</i> */
    GCTL_PWR_DN_SCALE_BITS	= 0xfff80000,
    GCTL_PWR_DN_SCALE_SHIFT	= 19,
} gctl_data_t;

/**
 * This enum represents the bit fields of the Core Interrupt Mask
 * Register (GEVTEN).
 */
typedef enum gevten_data {
    /** ULPI Carkit Event Enable		<i>Access: R_W</i> */
    GEVTEN_ULPI_CK_EVT_EN_BIT	= 0x00000001,
    GEVTEN_ULPI_CK_EVT_SHIFT	= 0,

    /** I2C Event Enable			<i>Access: R_W</i> */
    GEVTEN_I2C_EVT_EN_BIT	= 0x00000002,
    GEVTEN_I2C_EVT_EN_SHIFT	= 1,
} gevten_data_t;

/**
 * This enum represents the bit fields of the Core Status
 * Register (GSTS).
 */
typedef enum gsts_data {
    /** Current Mode			<i>Access: RO</i>.
     * - 0: Device Mode
     * - 1: Host Mode
     * - 2: DRD Mode
     */
    GSTS_CURMODE_BITS		= 0x00000003,
    GSTS_CURMODE_SHIFT		= 0,

    GSTS_DEVICE_MODE		= 0,
    GSTS_HOST_MODE		= 1,
    GSTS_DRD_MODE		= 2,

    /** Bus Error Address Valid		<i>Access: RO</i> */
    GSTS_BUS_ERR_ADDR_VLD_BIT	= 0x00000010,
    GSTS_BUS_ERR_ADDR_VLD_SHIFT	= 4,

    /** CSR Timeout */
    GSTS_CSR_TIMEOUT_BIT	= 0x00000020,
    GSTS_CSR_TIMEOUT_SHIFT	= 5,

    /** Device Interrupt Pending */
    GSTS_DEV_EVT_PENDING_BIT	= 0x00000040,
    GSTS_DEV_EVT_PENDING_SHIFT	= 6,

    /** Host Interrupt Pending */
    GSTS_HOST_EVT_PENDING_BIT	= 0x00000080,
    GSTS_HOST_EVT_PENDING_SHIFT	= 7,

    /** ADP Interrupt Pending */
    GSTS_ADP_EVT_PENDING_BIT	= 0x00000100,
    GSTS_ADP_EVT_PENDING_SHIFT	= 8,

    /** BC Interrupt Pending */
    GSTS_BC_EVT_PENDING_BIT	= 0x00000200,
    GSTS_BC_EVT_PENDING_SHIFT	= 9,

    /** OTG Interrupt Pending */
    GSTS_OTG_EVT_PENDING_BIT	= 0x00000400,
    GSTS_OTG_EVT_PENDING_SHIFT	= 10,

    /** SSIC Interrupt Pending */
    GSTS_SSIC_IP_BIT		= 0x00000800,
    GSTS_SSIC_IP_SHIFT		= 11,

    /** Current BELT Value			<i>Access: RO</i> */
    GSTS_CBELT_BITS		= 0xfff00000,
    GSTS_CBELT_SHIFT		= 20,
} gsts_data_t;

#ifdef USB3_DEBUG
/**
 * This enum represents the bit fields of the Hardware Parameters 0
 * Register (GHWPARAMS0).
 */
typedef enum ghwparams0_data {
    HWP0_MODE_BITS		= 0x00000007,
    HWP0_MODE_SHIFT		= 0,

    HWP0_MBUS_TYPE_BITS		= 0x00000038,
    HWP0_MBUS_TYPE_SHIFT	= 3,

    HWP0_SBUS_TYPE_BITS		= 0x000000c0,
    HWP0_SBUS_TYPE_SHIFT	= 6,

    HWP0_MDWIDTH_BITS		= 0x0000ff00,
    HWP0_MDWIDTH_SHIFT		= 8,

    HWP0_SDWIDTH_BITS		= 0x00ff0000,
    HWP0_SDWIDTH_SHIFT		= 16,

    HWP0_AWIDTH_BITS		= 0x3f000000,
    HWP0_AWIDTH_SHIFT		= 24,
} ghwparams0_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 1
 * Register (GHWPARAMS1).
 */
typedef enum ghwparams1_data {
    HWP1_IDWIDTH_M1_BITS		= 0x00000007,
    HWP1_IDWIDTH_M1_SHIFT		= 0,

    HWP1_BURSTWIDTH_M1_BITS		= 0x00000038,
    HWP1_BURSTWIDTH_M1_SHIFT		= 3,

    HWP1_DATAINFOWIDTH_BITS		= 0x000001c0,
    HWP1_DATAINFOWIDTH_SHIFT		= 6,

    HWP1_REQINFOWIDTH_BITS		= 0x00000e00,
    HWP1_REQINFOWIDTH_SHIFT		= 9,

    HWP1_ASPACEWIDTH_BITS		= 0x00007000,
    HWP1_ASPACEWIDTH_SHIFT		= 12,

    HWP1_DEV_NUM_INT_BITS		= 0x001f8000,
    HWP1_DEV_NUM_INT_SHIFT		= 15,

    HWP1_NUM_RAMS_BITS			= 0x00600000,
    HWP1_NUM_RAMS_SHIFT			= 21,

    HWP1_SPRAM_TYP_BIT			= 0x00800000,
    HWP1_SPRAM_TYP_SHIFT		= 23,

    HWP1_EN_PWROPT_BITS			= 0x03000000,
    HWP1_EN_PWROPT_SHIFT		= 24,

    EN_PWROPT_NONE		= 0,
    EN_PWROPT_CLK_GATING_ONLY	= 1,
    EN_PWROPT_HIBERNATION	= 2,

    HWP1_MAC_PHY_CLKS_SYNC_BIT		= 0x04000000,
    HWP1_MAC_PHY_CLKS_SYNC_SHIFT	= 26,

    HWP1_MAC_RAM_CLKS_SYNC_BIT		= 0x08000000,
    HWP1_MAC_RAM_CLKS_SYNC_SHIFT	= 27,

    HWP1_RAM_BUS_CLKS_SYNC_BIT		= 0x10000000,
    HWP1_RAM_BUS_CLKS_SYNC_SHIFT	= 28,

    HWP1_RM_OPT_FEATURES_BIT		= 0x40000000,
    HWP1_RM_OPT_FEATURES_SHIFT		= 30,
} ghwparams1_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 2
 * Register (GHWPARAMS2).
 */
typedef enum ghwparams2_data {
    HWP2_USERID_BITS	= 0xffffffff,
    HWP2_USERID_SHIFT	= 0,
} ghwparams2_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 3
 * Register (GHWPARAMS3).
 */
typedef enum ghwparams3_data {
    HWP3_SSPHY_IFC_BITS		= 0x00000003,
    HWP3_SSPHY_IFC_SHIFT	= 0,

    HWP3_HSPHY_IFC_BITS		= 0x0000000c,
    HWP3_HSPHY_IFC_SHIFT	= 2,

    HWP3_FSPHY_IFC_BITS		= 0x00000030,
    HWP3_FSPHY_IFC_SHIFT	= 4,

    HWP3_HSPHY_DWIDTH_BITS	= 0x000000c0,
    HWP3_HSPHY_DWIDTH_SHIFT	= 6,

    HWP3_VEND_CTL_IFC_BIT	= 0x00000400,
    HWP3_VEND_CTL_IFC_SHIFT	= 10,

    HWP3_ULPI_CARKIT_BIT	= 0x00000800,
    HWP3_ULPI_CARKIT_SHIFT	= 11,

    HWP3_NUM_EPS_BITS		= 0x0003f000,
    HWP3_NUM_EPS_SHIFT		= 12,

    HWP3_NUM_IN_EPS_BITS	= 0x007c0000,
    HWP3_NUM_IN_EPS_SHIFT	= 18,

    HWP3_TOT_XFR_RSRC_BITS	= 0x7f800000,
    HWP3_TOT_XFR_RSRC_SHIFT	= 23,
} ghwparams3_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 4
 * Register (GHWPARAMS4).
 */
typedef enum ghwparams4_data {
    HWP4_TRBS_PER_XFER_BITS	= 0x0000003f,
    HWP4_TRBS_PER_XFER_SHIFT	= 0,

    HWP4_HIBER_SPAD_BITS	= 0x0001e000,
    HWP4_HIBER_SPAD_SHIFT	= 13,

    HWP4_NUM_SS_USB_INST_BITS	= 0x001e0000,
    HWP4_NUM_SS_USB_INST_SHIFT	= 17,

    HWP4_EN_ISOC_SUPT_BIT	= 0x00800000,
    HWP4_EN_ISOC_SUPT_SHIFT	= 23,

    HWP4_BMU_PTL_DEPTH_BITS	= 0x0f000000,
    HWP4_BMU_PTL_DEPTH_SHIFT	= 24,

    HWP4_BMU_LSP_DEPTH_BITS	= 0xf0000000,
    HWP4_BMU_LSP_DEPTH_SHIFT	= 28,
} ghwparams4_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 5
 * Register (GHWPARAMS5).
 */
typedef enum ghwparams5_data {
    HWP5_BMU_BUSGM_DEPTH_BITS	= 0x0000000f,
    HWP5_BMU_BUSGM_DEPTH_SHIFT	= 0,

    HWP5_RXQ_FIFO_DEPTH_BITS	= 0x000003f0,
    HWP5_RXQ_FIFO_DEPTH_SHIFT	= 4,

    HWP5_TXQ_FIFO_DEPTH_BITS	= 0x0000fc00,
    HWP5_TXQ_FIFO_DEPTH_SHIFT	= 10,

    HWP5_DWQ_FIFO_DEPTH_BITS	= 0x003f0000,
    HWP5_DWQ_FIFO_DEPTH_SHIFT	= 16,

    HWP5_DFQ_FIFO_DEPTH_BITS	= 0x0fc00000,
    HWP5_DFQ_FIFO_DEPTH_SHIFT	= 22,
} ghwparams5_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 6
 * Register (GHWPARAMS6).
 */
typedef enum ghwparams6_data {
    HWP6_PSQ_FIFO_DEPTH_BITS	= 0x0000003f,
    HWP6_PSQ_FIFO_DEPTH_SHIFT	= 0,

    HWP6_EN_DBG_PORTS_BIT	= 0x00000040,
    HWP6_EN_DBG_PORTS_SHIFT	= 6,

    HWP6_EN_FPGA_BIT		= 0x00000080,
    HWP6_EN_FPGA_SHIFT		= 7,

    HWP6_EN_SRP_BIT		= 0x00000400,
    HWP6_EN_SRP_SHIFT		= 10,

    HWP6_EN_HNP_BIT		= 0x00000800,
    HWP6_EN_HNP_SHIFT		= 11,

    HWP6_EN_ADP_BIT		= 0x00001000,
    HWP6_EN_ADP_SHIFT		= 12,

    HWP6_EN_OTG_BIT		= 0x00002000,
    HWP6_EN_OTG_SHIFT		= 13,

    HWP6_EN_BC_BIT		= 0x00004000,
    HWP6_EN_BC_SHIFT		= 14,

    HWP6_EN_BUS_FILTERS_BIT	= 0x00008000,
    HWP6_EN_BUS_FILTERS_SHIFT	= 15,

    HWP6_RAM0_DEPTH_BITS	= 0xffff0000,
    HWP6_RAM0_DEPTH_SHIFT	= 16,
} ghwparams6_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 7
 * Register (GHWPARAMS7).
 */
typedef enum ghwparams7_data {
    HWP7_RAM1_DEPTH_BITS	= 0x0000ffff,
    HWP7_RAM1_DEPTH_SHIFT	= 0,

    HWP7_RAM2_DEPTH_BITS	= 0xffff0000,
    HWP7_RAM2_DEPTH_SHIFT	= 16,
} ghwparams7_data_t;

/**
 * This enum represents the bit fields of the Hardware Parameters 8
 * Register (GHWPARAMS8).
 */
typedef enum ghwparams8_data {
    HWP8_DCACHE_DEPTH_BITS	= 0xffffffff,
    HWP8_DCACHE_DEPTH_SHIFT	= 0,
} ghwparams8_data_t;

/**
 * This enum represents the bit fields of the Debug Queue/FIFO Space
 * Register (GDBGFIFOSPACE).
 */
typedef enum gdbgfifospace_data {
    /** FIFO/Queue Select			<i>Access: R_W</i> */
    DBGFIFOSPACE_FIFO_QUEUE_SEL_BITS	= 0x000000ff,
    DBGFIFOSPACE_FIFO_QUEUE_SEL_SHIFT	= 0,

    /*   0 - 31  TxFIFO Number   */
    /*  32 - 63  RxFIFO Number   */
    /*  64 - 95  TxReqQ Number   */
    /*  96 - 127 RxReqQ Number   */
    /* 128 - 159 RxInfoQ Number  */
    /* 160       DescFetchQ      */
    /* 161       EventQ          */
    /* 162       ProtocolStatusQ */

    /** Space Available			<i>Access: R</i> */
    DBGFIFOSPACE_SPACE_AVAIL_BITS	= 0xffff0000,
    DBGFIFOSPACE_SPACE_AVAIL_SHIFT	= 16,
} gdbgfifospace_data_t;

/**
 * This enum represents the bit fields of the Debug LTSSM
 * Register (GDBGLTSSM).
 */
typedef enum gdbgltssm_data {
    /** Pipe Status				<i>Access: R</i> */
    DBGLTSSM_PIPE_STATUS_BITS		= 0x0003ffff,
    DBGLTSSM_PIPE_STATUS_SHIFT		= 0,

    /** LTDB SubState			<i>Access: R</i> */
    DBGLTSSM_LTDB_SUB_STATE_BITS	= 0x003c0000,
    DBGLTSSM_LTDB_SUB_STATE_SHIFT	= 18,

    /** LTDB State				<i>Access: R</i> */
    DBGLTSSM_LTDB_STATE_BITS		= 0x03c00000,
    DBGLTSSM_LTDB_STATE_SHIFT		= 22,

    /** LTDB Timeout			<i>Access: R</i> */
    DBGLTSSM_LTDB_TIMEOUT_BIT		= 0x04000000,
    DBGLTSSM_LTDB_TIMEOUT_SHIFT		= 26,
} gdbgltssm_data_t;

/**
 * This enum represents the bit fields of the Core RMMI PHY Control
 * Registers (GUSB3RMMICTLn).
 */
typedef enum gusb3rmmictl_data {
    RMMICTL_MPHY_STATE_BITS		= 0x0e000000,
    RMMICTL_MPHY_STATE_SHIFT		= 25,

#define MPHY_STATE_DISABLED		0
#define MPHY_STATE_HIBERN8		1
#define MPHY_STATE_SLEEP		2
#define MPHY_STATE_STALL		3
#define MPHY_STATE_PWM_BURST	4
#define MPHY_STATE_HS_BURST		5
#define MPHY_STATE_LINE_CFG		6
#define MPHY_STATE_LINE_RESET	7

    RMMICTL_AUTO_EXIT_RRAP_BIT		= 0x10000000,
    RMMICTL_AUTO_EXIT_RRAP_SHIFT	= 28,

    RMMICTL_AUTO_ROM_RRAP_BIT		= 0x20000000,
    RMMICTL_AUTO_ROM_RRAP_SHIFT		= 29,

    RMMICTL_AUTO_EXIT_H8_BIT		= 0x40000000,
    RMMICTL_AUTO_EXIT_H8_SHIFT		= 30,

    RMMICTL_AUTO_ROM_H8_BIT		= 0x80000000,
    RMMICTL_AUTO_ROM_H8_SHIFT		= 31,
} gusb3rmmictl_data_t;

#endif

/**
 * This enum represents the bit fields of the Core USB2 PHY Configuration
 * Registers (GUSB2PHYCFGn).
 */
typedef enum gusb2phycfg_data {
    /** HS/FS Timeout Calibration			<i>Access: R_W</i> */
    USB2PHYCFG_TOUT_CAL_BITS		= 0x00000007,
    USB2PHYCFG_TOUT_CAL_SHIFT		= 0,

    /** UTMI+ PHY Intf Width (8-bit/16-bit) SelecT	<i>Access: R_W</i> */
    USB2PHYCFG_16B_PHY_IF_BIT		= 0x00000008,
    USB2PHYCFG_16B_PHY_IF_SHIFT		= 3,
    /*--------*/
    /** ULPI DDR Select				<i>Access: R_W</i> */
    USB2PHYCFG_DDR_SEL_BIT		= 0x00000008,
    USB2PHYCFG_DDR_SEL_SHIFT		= 3,

    /** UTMI+ / ULPI Select				<i>Access: R_W</i> */
    USB2PHYCFG_UTMI_ULPI_BIT		= 0x00000010,
    USB2PHYCFG_UTMI_ULPI_SHIFT		= 4,

    /** Full-speed Serial Interface Select		<i>Access: R_W</i> */
    USB2PHYCFG_FSINTF_BIT		= 0x00000020,
    USB2PHYCFG_FSINTF_SHIFT		= 5,

    /** Suspend USB2 Phy				<i>Access: R_W</i> */
    USB2PHYCFG_SUS_PHY_BIT		= 0x00000040,
    USB2PHYCFG_SUS_PHY_SHIFT		= 6,

    /** USB2.0 HS PHY/USB1.1 FS Serial Xcvr Select	<i>Access: R_W</i> */
    USB2PHYCFG_PHY_SEL_BIT		= 0x00000080,
    USB2PHYCFG_PHY_SEL_SHIFT		= 7,

    /** Enable UTMI Sleep				<i>Access: R_W</i> */
    USB2PHYCFG_ENBL_SLP_M_BIT		= 0x00000100,
    USB2PHYCFG_ENBL_SLP_M_SHIFT		= 8,

    /** USB2.0 Turnaround Time			<i>Access: R_W</i> */
    USB2PHYCFG_USB_TRD_TIM_BITS		= 0x00003c00,
    USB2PHYCFG_USB_TRD_TIM_SHIFT	= 10,

    /** PHY Low-power Clock Select			<i>Access: R_W</i> */
    USB2PHYCFG_PHY_LPWR_CLK_SEL_BIT	= 0x00004000,
    USB2PHYCFG_PHY_LPWR_CLK_SEL_SHIFT	= 14,

    /** ULPI Auto Resume				<i>Access: R_W</i> */
    USB2PHYCFG_ULPI_AUTO_RES_BIT	= 0x00008000,
    USB2PHYCFG_ULPI_AUTO_RES_SHIFT	= 15,

    /** ULPI Clock SuspendM				<i>Access: R_W</i> */
    USB2PHYCFG_ULPI_CLK_SUS_M_BIT	= 0x00010000,
    USB2PHYCFG_ULPI_CLK_SUS_M_SHIFT	= 16,

    /** ULPI External Vbus Drive			<i>Access: R_W</i> */
    USB2PHYCFG_ULPI_EXT_VBUS_DRV_BIT	= 0x00020000,
    USB2PHYCFG_ULPI_EXT_VBUS_DRV_SHIFT	= 17,

    /** ULPI External Vbus Indicator		<i>Access: R_W</i> */
    USB2PHYCFG_ULPI_EXT_VBUS_IND_BIT	= 0x00040000,
    USB2PHYCFG_ULPI_EXT_VBUS_IND_SHIFT	= 18,

    /** PHY Interrupt Number			<i>Access: R_W</i> */
    USB2PHYCFG_PHY_INTR_NUM_BITS	= 0x01f80000,
    USB2PHYCFG_PHY_INTR_NUM_SHIFT	= 19,

    /** OTG Interrupt Number			<i>Access: R_W</i> */
    USB2PHYCFG_OTG_INTR_NUM_BITS	= 0x7e000000,
    USB2PHYCFG_OTG_INTR_NUM_SHIFT	= 25,

    /** PHY Soft Reset				<i>Access: R_W</i> */
    USB2PHYCFG_PHY_SOFT_RST_BIT		= 0x80000000,
    USB2PHYCFG_PHY_SOFT_RST_SHIFT	= 31,
} gusb2phycfg_data_t;

#ifdef USB3_DEBUG
/**
 * This enum represents the bit fields in the USB2 I2C Control
 * Registers (GUSB2I2CCTLn).
 */
typedef enum gusb2i2cctl_data {
    /** All bits are reserved */
    USB2I2C_RSVD_BITS		= 0xffffffff,
    USB2I2C_RSVD_SHIFT		= 0,
} gusb2i2cctl_data_t;

/**
 * This enum represents the bit fields in the USB2 Phy Vendor Control
 * Registers (GUSB2PHYACCn).
 */
typedef enum gusb2phyacc_data {
    /** Register Data			<i>Access: R_W</i> */
    USB2PHY_REGDATA_BITS	= 0x000000ff,
    USB2PHY_REGDATA_SHIFT	= 0,

    /** UTMI+ Vendor Ctrl Register Address	<i>Access: R_W</i> */
    USB2PHY_VCTRL_BITS		= 0x0000ff00,
    USB2PHY_VCTRL_SHIFT		= 8,
    /*--------*/
    /** ULPI Extended Register Address	<i>Access: R_W</i> */
    USB2PHY_EXTREGADDR_BITS	= 0x00003f00,
    USB2PHY_EXTREGADDR_SHIFT	= 8,

    /** Register Address			<i>Access: R_W</i> */
    USB2PHY_REGADDR_BITS	= 0x003f0000,
    USB2PHY_REGADDR_SHIFT	= 16,

    /** Register Write			<i>Access: R_W</i> */
    USB2PHY_REGWR_BIT		= 0x00400000,
    USB2PHY_REGWR_SHIFT		= 22,

    /** VStatus Busy			<i>Access: RO</i> */
    USB2PHY_VSTSBSY_BIT		= 0x00800000,
    USB2PHY_VSTSBSY_SHIFT	= 23,

    /** VStatus Done			<i>Access: R_SS_SC</i> */
    USB2PHY_VSTSDONE_BIT	= 0x01000000,
    USB2PHY_VSTSDONE_SHIFT	= 24,

    /** New Register Request		<i>Access: R_WS_SC</i> */
    USB2PHY_NEWREGREQ_BIT	= 0x02000000,
    USB2PHY_NEWREGREQ_SHIFT	= 25,

    /** Disable ULPI Drivers		<i>Access: R_WS_SC</i> */
    USB2PHY_DIS_ULPI_DRVR_BIT	= 0x04000000,
    USB2PHY_DIS_ULPI_DRVR_SHIFT	= 26,
} gusb2phyacc_data_t;
#endif
/**
 * This enum represents the bit fields of the USB3 Pipe Control
 * Registers (GUSB3PIPECTLn).
 */
typedef enum gusb3pipectl_data {
    /** Elastic Buffer Mode			<i>Access: R_W</i> */
    PIPECTL_ELAS_BUF_MODE_BIT		= 0x00000001,
    PIPECTL_ELAS_BUF_MODE_SHIFT		= 0,

    /** Tx De-Emphasis			<i>Access: R_W</i> */
    PIPECTL_TX_DEMPH_BITS		= 0x00000006,
    PIPECTL_TX_DEMPH_SHIFT		= 1,

    /** Tx Margin				<i>Access: R_W</i> */
    PIPECTL_TX_MARGIN_BITS		= 0x00000038,
    PIPECTL_TX_MARGIN_SHIFT		= 3,

    /** Tx Swing				<i>Access: R_W</i> */
    PIPECTL_TX_SWING_BIT		= 0x00000040,
    PIPECTL_TX_SWING_SHIFT		= 6,

    /** USB3 SSIC Enable			<i>Access: R_W</i> */
    PIPECTL_SSIC_EN_BIT			= 0x00000080,
    PIPECTL_SSIC_EN_SHIFT		= 7,

    /** LFPS Filter				<i>Access: R_W</i> */
    PIPECTL_LFPS_FILTER_BIT		= 0x00000200,
    PIPECTL_LFPS_FILTER_SHIFT		= 9,

    /** P3 Exit Signal In P2		<i>Access: R_W</i> */
    PIPECTL_P3_EX_SIG_P2_BIT		= 0x00000400,
    PIPECTL_P3_EX_SIG_P2_SHIFT		= 10,

    /** P3-P2 Transitions OK		<i>Access: R_W</i> */
    PIPECTL_P3_P2_TRAN_OK_BIT		= 0x00000800,
    PIPECTL_P3_P2_TRAN_OK_SHIFT		= 11,

    /** LFPS P0 Align			<i>Access: R_W</i> */
    PIPECTL_LFPS_P0_ALGN_BIT		= 0x00001000,
    PIPECTL_LFPS_P0_ALGN_SHIFT		= 12,

    /** Pipe Data Width			<i>Access: R_W</i> */
    PIPECTL_DATA_WIDTH_BITS		= 0x00018000,
    PIPECTL_DATA_WIDTH_SHIFT		= 15,

    /** Suspend USB3 Phy			<i>Access: R_W</i> */
    PIPECTL_SUS_PHY_BIT			= 0x00020000,
    PIPECTL_SUS_PHY_SHIFT		= 17,

    PIPECTL_DELAY_PHY_PW_CHG_BIT = 0x00040000,
    PIPECTL_DELAY_PHY_PW_CHG_SHIFT = 18,

    PIPECTL_REQUEST_P1P2P3_BIT = 0x01000000,
    PIPECTL_REQUEST_P1P2P3_SHIFT = 24,
    /** PHY Soft Reset			<i>Access: R_W</i> */
    PIPECTL_PHY_SOFT_RST_BIT		= 0x80000000,
    PIPECTL_PHY_SOFT_RST_SHIFT		= 31,
} gusb3pipectl_data_t;

/**
 * This enum represents the bit fields in the FIFO Size Registers.
 */
typedef enum gfifosize_data {
    /** Depth				<i>Access: R_W</i> */
    FIFOSZ_DEPTH_BITS		= 0x0000ffff,
    FIFOSZ_DEPTH_SHIFT		= 0,

    /** Starting Address			<i>Access: RO or R_W</i> */
    FIFOSZ_STARTADDR_BITS	= 0xffff0000,
    FIFOSZ_STARTADDR_SHIFT	= 16,
} gfifosize_data_t;

/**
 * This enum represents the bit fields of the Event Buffer Size
 * Registers (GEVENTSIZn).
 */
typedef enum geventsiz_data {
    /** Event Buffer Size			<i>Access: R_W</i> */
    EVENTSIZ_SIZ_BITS		= 0x0000ffff,
    EVENTSIZ_SIZ_SHIFT		= 0,

    /** Event Interrupt Mask (1 == disable)	<i>Access: R_W</i> */
    EVENTSIZ_INT_MSK_BIT	= 0x80000000,
    EVENTSIZ_INT_MSK_SHIFT	= 31,
} geventsiz_data_t;

/**
 * This enum represents the bit fields of the Event Buffer Count
 * Registers (GEVENTCNTn).
 */
typedef enum geventcnt_data {
    /** Event Count				<i>Access: R_W</i> */
    EVENTCNT_CNT_BITS		= 0x0000ffff,
    EVENTCNT_CNT_SHIFT		= 0,
} geventcnt_data_t;

/**
 * This enum represents the bit fields of a generic Event Buffer entry.
 */
typedef enum gevent_data {
    /** Non-Endpoint Specific Event flag */
    EVENT_NON_EP_BIT			= 0x01,
    EVENT_NON_EP_SHIFT			= 0,

    /** Non-Endpoint Specific Event Type */
    EVENT_INTTYPE_BITS			= 0xfe,
    EVENT_INTTYPE_SHIFT			= 1,

    /** Non-Endpoint Specific Event Type values */
    EVENT_DEV_INT		= 0,	/** @< */
    EVENT_OTG_INT		= 1,	/** @< */
    EVENT_CARKIT_INT		= 3,	/** @< */
    EVENT_I2C_INT		= 4,
} gevent_data_t;

/**
 * This enum represents the non-generic bit fields of an Event Buffer entry
 * for Device Specific events (DEVT).
 */
typedef enum devt_data {
    /** Device Specific Event Type */
    DEVT_BITS				= 0x00000f00,
    DEVT_SHIFT				= 8,

    /** Device Specific Event Type values */
    DEVT_DISCONN		= 0,	/** @< */
    DEVT_USBRESET		= 1,	/** @< */
    DEVT_CONNDONE		= 2,	/** @< */
    DEVT_ULST_CHNG		= 3,	/** @< */
    DEVT_WKUP			= 4,	/** @< */
    DEVT_HIBER_REQ		= 5,	/** @< */
    DEVT_U3_L2L1_SUSP		= 6,	/** @< */
    DEVT_SOF			= 7,	/** @< */
    DEVT_ERRATICERR		= 9,	/** @< */
    DEVT_CMD_CMPL		= 10,	/** @< */
    DEVT_OVERFLOW		= 11,	/** @< */
    DEVT_VNDR_DEV_TST_RCVD	= 12,	/** @< */
    DEVT_INACT_TIMEOUT_RCVD	= 13,

    /** Event Information */
    DEVT_EVT_INFO_BITS			= 0xffff0000,
    DEVT_EVT_INFO_SHIFT			= 16,

    /** USB/Link State */
    DEVT_ULST_STATE_BITS		= 0x000f0000,
    DEVT_ULST_STATE_SHIFT		= 16,

    /** USB/Link State values in SS */
    LINK_STATE_U0		= 0,	/** @< */
    LINK_STATE_U1		= 1,	/** @< */
    LINK_STATE_U2		= 2,	/** @< */
    LINK_STATE_U3		= 3,	/** @< */
    LINK_STATE_SS_DIS		= 4,	/** @< */
    LINK_STATE_RX_DET		= 5,	/** @< */
    LINK_STATE_SS_INACT		= 6,	/** @< */
    LINK_STATE_POLL		= 7,	/** @< */
    LINK_STATE_RECOV		= 8,	/** @< */
    LINK_STATE_HRESET		= 9,	/** @< */
    LINK_STATE_CMPLY		= 10,	/** @< */
    LINK_STATE_LPBK		= 11,	/** @< */
    LINK_STATE_RESET		= 14,	/** @< */
    LINK_STATE_RESUME		= 15,

    /** USB/Link State values in HS/FS/LS */
    LINK_STATE_ON		= 0,	/** @< */
    LINK_STATE_SLEEP		= 2,	/** @< */
    LINK_STATE_SUSPEND		= 3,	/** @< */
    LINK_STATE_EARLY_SUSPEND	= 5,

    DEVT_ULST_SS_BIT			= 0x00100000,
    DEVT_ULST_SS_SHIFT			= 20,

#define DEVT_HIBER_STATE_BITS	DEVT_ULST_STATE_BITS
#define DEVT_HIBER_STATE_SHIFT	DEVT_ULST_STATE_SHIFT

#define DEVT_HIBER_SS_BIT		DEVT_ULST_SS_BIT
#define DEVT_HIBER_SS_SHIFT		DEVT_ULST_SS_SHIFT

    DEVT_HIBER_HIRD_BITS		= 0x0f000000,
    DEVT_HIBER_HIRD_SHIFT		= 24,
} devt_data_t;

/**
 * This enum represents the bit fields of an Event Buffer entry for
 * Endpoint Specific events (DEPEVT).
 */
typedef enum depevt_data {
    /** Endpoint Number */
    DEPEVT_EPNUM_BITS			= 0x0000003e,
    DEPEVT_EPNUM_SHIFT			= 1,

    /** Endpoint Event Type */
    DEPEVT_INTTYPE_BITS			= 0x000003c0,
    DEPEVT_INTTYPE_SHIFT		= 6,

    /** Endpoint Event Type values */
    DEPEVT_XFER_CMPL		= 1,	/** @< */
    DEPEVT_XFER_IN_PROG		= 2,	/** @< */
    DEPEVT_XFER_NRDY		= 3,	/** @< */
    DEPEVT_FIFOXRUN		= 4,	/** @< */
    DEPEVT_STRM_EVT		= 6,	/** @< */
    DEPEVT_EPCMD_CMPL		= 7,

    /** Event Status for Start Xfer Command */
    DEPEVT_NO_MORE_RSCS_BIT		= 0x00001000,
    DEPEVT_NO_MORE_RSCS_SHIFT		= 12,
    DEPEVT_ISOC_TIME_PASSED_BIT		= 0x00002000,
    DEPEVT_ISOC_TIME_PASSED_SHIFT	= 13,

    /** Event Status for Stream Event */
    DEPEVT_STRM_EVT_BITS		= 0x0000f000,
    DEPEVT_STRM_EVT_SHIFT		= 12,

    /** Stream Event Status values */
    DEPEVT_STRM_FOUND		= 1,	/** @< */
    DEPEVT_STRM_NOT_FOUND	= 2,

    /** Event Status for Xfer Complete or Xfer In Progress Event */
    DEPEVT_BUS_ERR_BIT			= 0x00001000,
    DEPEVT_BUS_ERR_SHIFT		= 12,
    DEPEVT_SHORT_PKT_BIT		= 0x00002000,
    DEPEVT_SHORT_PKT_SHIFT		= 13,
    DEPEVT_IOC_BIT			= 0x00004000,
    DEPEVT_IOC_SHIFT			= 14,
    DEPEVT_LST_BIT			= 0x00008000,
    DEPEVT_LST_SHIFT			= 15,
#define DEPEVT_MISSED_ISOC_BIT	DEPEVT_LST_BIT
#define DEPEVT_MISSED_ISOC_SHIFT	DEPEVT_LST_SHIFT

    /** Event Status for Xfer Not Ready Event */
    DEPEVT_CTRL_BITS			= 0x00003000,
    DEPEVT_CTRL_SHIFT			= 12,
    DEPEVT_XFER_ACTIVE_BIT		= 0x00008000,
    DEPEVT_XFER_ACTIVE_SHIFT		= 15,

    /** Xfer Not Ready Event Status values */
    DEPEVT_CTRL_SETUP		= 0,	/** @< */
    DEPEVT_CTRL_DATA		= 1,	/** @< */
    DEPEVT_CTRL_STATUS		= 2,

    /** Stream ID */
    DEPEVT_STRM_ID_BITS			= 0xffff0000,
    DEPEVT_STRM_ID_SHIFT		= 16,

    /** Isoc uFrame Number (for Xfer Not Ready on Isoc EP) */
    DEPEVT_ISOC_UFRAME_NUM_BITS		= 0xffff0000,
    DEPEVT_ISOC_UFRAME_NUM_SHIFT	= 16,

    /** Xfer Resource Index (for Start Xfer Command) */
    DEPEVT_XFER_RSC_IDX_BITS		= 0x007f0000,
    DEPEVT_XFER_RSC_IDX_SHIFT		= 16,

    /** Current Data Sequence Number (for Get Endpoint State Command) */
    DEPEVT_CUR_DAT_SEQ_NUM_BITS		= 0x001f0000,
    DEPEVT_CUR_DAT_SEQ_NUM_SHIFT	= 16,

    /** Flow Control State (for Get Endpoint State Command) */
    DEPEVT_FLOW_CTRL_BIT		= 0x00200000,
    DEPEVT_FLOW_CTRL_SHIFT		= 21,
} depevt_data_t;

/**
 * This enum represents the non-generic bit fields of an Event Buffer entry
 * for other Core events (GEVT).
 */
typedef enum gevt_data {
    /** PHY Port Number */
    GINT_PHY_PORT_BITS		= 0xf00,
    GINT_PHY_PORT_SHIFT		= 8,
} gevt_data_t;

/**
 * This struct represents the 32-bit register fields of the Event Buffer
 * Registers (GEVENTBUFn).
 */
typedef struct geventbuf_data
{
    /** Event Buffer Address Register Low Word */
    volatile u32 geventadr_lo;

    /** Event Buffer Address Register High Word */
    volatile u32 geventadr_hi;

    /** Event Buffer Size Register.
     * Fields defined in enum @ref geventsiz_data. */
    volatile u32 geventsiz;

    /** Event Buffer Count Register.
     * Fields defined in enum @ref geventcnt_data. */
    volatile u32 geventcnt;
}
geventbuf_data_t;

/***************************** Register Addresses Map ******************************
** 0x0_0000 to 0x0_7FFF     xHCI Registers (Xxxxx)
    * 0 to CAPLENGTH -1         eXtensible Host Controller Capability Registers
    * CAPLENGTH to RTSOFF - 1   Host Controller Operational Registers
    * RTSOFF to DBOFF - 1       Controller Runtime Registers
    * DBOFF to (xECP*4-1)       Doorbell Register
    * xECP*4 to 0x0_7FFF        xHCI Extended Capabilities
** 0x0_C100 to 0x0_C6FF     Global Registers (Gxxxx)
** 0x0_C700 to 0x0_CBFF     Device Registers (Dxxxx)
** 0x0_CC00 to 0x0_CCFF     OTG and Battery Charger Registers (Oxxxx/Axxxx/Bxxxx)
** 0x0_CD00 to 0x0_CFFF     Unused/Aliased
** 0x4_0000 to 0x7_FFFF     Internal RAM 0 - Debug Access (256KB)
** 0x8_0000 to 0xB_FFFF     Internal RAM 1 - Debug Access (256KB)
** 0xC_0000 to 0xF_FFFF     Internal RAM 2 - Debug Access (256KB)
**/


/**
 * Core Global Registers	<i>Offsets 100h-5FCh</i>.
 *
 * The usb3_core_global_regs structure defines the size
 * and relative field offsets for the Core Global Registers.
 */
typedef struct usb3_core_global_regs
{

#define CORE_GLOBAL_REG_OFFSET	0xC100

    /** Core BIU Configuration 0 Register	<i>Offset: C100h</i>.
     * Fields defined in enum @ref gsbuscfg0_data. */
    volatile u32 gsbuscfg0;

    /** Core BIU Configuration 1 Register	<i>Offset: C104h</i>.
     * Fields defined in enum @ref gsbuscfg1_data. */
    volatile u32 gsbuscfg1;

    /** Core Tx Threshold Control Register	<i>Offset: C108h</i>.
     * Fields defined in enum @ref gtxthrcfg_data. */
    volatile u32 gtxthrcfg;

    /** Core Threshold Control Register	<i>Offset: C10Ch</i>.
     * Fields defined in enum @ref grxthrcfg_data. */
    volatile u32 grxthrcfg;

    /** Core Control Register		<i>Offset: C110h</i>.
     * Fields defined in enum @ref gctl_data. */
    volatile u32 gctl;

    /* Debug global power management status <i>Offset: C114h</i>.*
    * gives information on which event caused the hibernation exit */
    volatile u32 gpmsts;

    /** Core Interrupt Mask Register	<i>Offset: C114h</i>.
     * Fields defined in enum @ref gevten_data.
    volatile u32 gevten;
    */
    /** Core Status Register		<i>Offset: C118h</i>.
     * Fields defined in enum @ref gsts_data. */
    volatile u32 gsts;

    /** User Control Register1		<i>Offset: C11Ch</i> */
    volatile u32 guctl1;

    /** Synopsys ID Register		<i>Offset: C120h</i> */
    volatile u32 gsnpsid;

    /** General Purpose I/O Register	<i>Offset: C124h</i> */
    volatile u32 ggpio;

    /** User ID Register			<i>Offset: C128h</i> */
    volatile u32 guid;

    /** User Control Register		<i>Offset: C12Ch</i> */
    volatile u32 guctl;

    /** Bus Error Address Register		<i>Offset: C130h</i> */
    volatile u32 gbuserraddrlo;

    /** Bus Error Address Register		<i>Offset: C134h</i> */
    volatile u32 gbuserraddrhi;

    /** SS Port to Bus Instance Mapping Register	<i>Offset: C138h</i> */
    volatile u32 gprtbimap_lo;

    /** SS Port to Bus Instance Mapping Register	<i>Offset: C13Ch</i> */
    volatile u32 gprtbimap_hi;

    /** Hardware Parameter 0 Register	<i>Offset: C140h</i>.
     * Fields defined in enum @ref ghwparams0_data. */
    volatile u32 ghwparams0;

    /** Hardware Parameter 1 Register	<i>Offset: C144h</i>.
     * Fields defined in enum @ref ghwparams1_data. */
    volatile u32 ghwparams1;

    /** Hardware Parameter 2 Register	<i>Offset: C148h</i>.
     * Fields defined in enum @ref ghwparams2_data. */
    volatile u32 ghwparams2;

    /** Hardware Parameter 3 Register	<i>Offset: C14Ch</i>.
     * Fields defined in enum @ref ghwparams3_data. */
    volatile u32 ghwparams3;

    /** Hardware Parameter 4 Register	<i>Offset: C150h</i>.
     * Fields defined in enum @ref ghwparams4_data. */
    volatile u32 ghwparams4;

    /** Hardware Parameter 5 Register	<i>Offset: C154h</i>.
     * Fields defined in enum @ref ghwparams5_data. */
    volatile u32 ghwparams5;

    /** Hardware Parameter 6 Register	<i>Offset: C158h</i>.
     * Fields defined in enum @ref ghwparams6_data. */
    volatile u32 ghwparams6;

    /** Hardware Parameter 7 Register	<i>Offset: C15Ch</i>.
     * Fields defined in enum @ref ghwparams7_data. */
    volatile u32 ghwparams7;

    /** Debug Queue/FIFO Space Register	<i>Offset: C160h</i>.
     * Fields defined in enum @ref gdbgfifospace_data. */
    volatile u32 gdbgfifospace;

    /** Debug LTSSM Register		<i>Offset: C164h</i>.
     * Fields defined in enum @ref gdbgltssm_data */
    volatile u32 gdbgltssm;

    /** Debug LNMCC Register		<i>Offset: C168h</i> */
    volatile u32 gdbglnmcc;

    /** Debug BMU Register			<i>Offset: C16Ch</i> */
    volatile u32 gdbgbmu;

    /** Debug LSP Mux Register		<i>Offset: C170h</i> */
    volatile u32 gdbglspmux;

    /** Debug LSP Register			<i>Offset: C174h</i> */
    volatile u32 gdbglsp;

    /** Debug EP Info 0 Register		<i>Offset: C178h</i> */
    volatile u32 gdbgepinfo0;

    /** Debug EP Info 1 Register		<i>Offset: C17Ch</i> */
    volatile u32 gdbgepinfo1;

    /** HS Port to Bus Instance Mapping Register	<i>Offset: C180h</i> */
    volatile u32 gprtbimap_hs_lo;

    /** HS Port to Bus Instance Mapping Register	<i>Offset: C184h</i> */
    volatile u32 gprtbimap_hs_hi;

    /** FS Port to Bus Instance Mapping Register	<i>Offset: C188h</i> */
    volatile u32 gprtbimap_fs_lo;

    /** FS Port to Bus Instance Mapping Register	<i>Offset: C18Ch</i> */
    volatile u32 gprtbimap_fs_hi;

    /** reserved				<i>Offset: C190h-C1BCh</i> */
    volatile u32 reserved4[12];

    /** Global RMMI PHY Control Register	<i>Offset: C1C0h-C200h</i> */
    volatile u32 gusb3rmmictl[16];

    /** USB2 Configuration Registers	<i>Offset: C200h-C23Ch</i>.
     * Fields defined in enum @ref gusb2phycfg_data. */
    volatile u32 gusb2phycfg[16];

    /** USB2 I2C Access Registers		<i>Offset: C240h-C27Ch</i>.
     * Fields defined in enum @ref gusb2i2cctl_data. */
    volatile u32 gusb2i2cctl[16];

    /** USB2 PHY Vendor Control Registers	<i>Offset: C280h-C2BCh</i>.
     * Fields defined in enum @ref gusb2phyacc_data. */
    volatile u32 gusb2phyacc[16];

    /** USB3 Pipe Control Registers		<i>Offset: C2C0h-C2FCh</i>.
     * Fields defined in enum @ref gusb3pipectl_data. */
    volatile u32 gusb3pipectl[16];

    /** Transmit FIFO Size Registers	<i>Offset: C300h-C37Ch</i>.
     * Fields defined in enum @ref gfifosize_data. */
    volatile u32 gtxfifosiz[32];

    /** Receive FIFO Size Registers		<i>Offset: C380h-C3FC0h</i>.
     * Fields defined in enum @ref gfifosize_data. */
    volatile u32 grxfifosiz[32];

    /** Event Buffer Registers		<i>Offset: C400h-C5FCh</i>.
     * Fields defined in struct @ref geventbuf_data. */
    struct geventbuf_data geventbuf[32];

    /** Hardware Parameter 8 Register	<i>Offset: C600h</i>.
     * Fields defined in enum @ref ghwparams8_data. */
    volatile u32 ghwparams8;

    volatile u32 reserved5[4];

    /** Device TX FIFO DMA Priority Register <i>Offset: C610h</i>.*/
    volatile u32 gtxfifopridev;

    volatile u32 reserved6[2];

    /** Host TX FIFO DMA Priority Register <i>Offset: C618h</i>. */
    volatile u32 gtxfifoprihst;

    /** Host RX FIFO DMA Priority Register <i>Offset: C61Ch</i>. */
    volatile u32 grxfifoprihst;

    /** Host Debug Capability FIFO DMA Priority Register <i>Offset: C620h</i>. */
    volatile u32 gfifopribc;

    /** Host FIFO DMA High-Low Priority Ratio Register <i>Offset: C624h</i>. */
    volatile u32 gdmahlratio;

    volatile u32 reserved7[3];

    /** Frame Length Adjustment Register <i>Offset: C630h</i>. */
    volatile u32 gfladj;
}
usb3_core_global_regs_t;


/****************************************************************************/
/* Device Global Registers */

/**
 * This enum represents the bit fields in the Device Configuration
 * Register (DCFG).
 */
typedef enum dcfg_data {
    /** Device Speed			<i>Access: R_W</i> */
    DCFG_DEVSPD_BITS		= 0x000007,
    DCFG_DEVSPD_SHIFT		= 0,

    /** Device Speed values */
    SPEED_HS_PHY_30MHZ_OR_60MHZ		= 0,	/** @< */
    SPEED_FS_PHY_30MHZ_OR_60MHZ		= 1,	/** @< */
    SPEED_SS_PHY_125MHZ_OR_250MHZ	= 4,

    /** Device Address			<i>Access: R_W</i> */
    DCFG_DEVADDR_BITS		= 0x0003f8,
    DCFG_DEVADDR_SHIFT		= 3,

    /** Periodic Frame Interval		<i>Access: R_W</i> */
    DCFG_PER_FR_INTVL_BITS	= 0x000c00,
    DCFG_PER_FR_INTVL_SHIFT	= 10,

    /** Periodic Frame Interval values */
    DCFG_PER_FR_INTVL_80		= 0,	/** @< */
    DCFG_PER_FR_INTVL_85		= 1,	/** @< */
    DCFG_PER_FR_INTVL_90		= 2,	/** @< */
    DCFG_PER_FR_INTVL_95		= 3,

    /** Device Interrupt Number		<i>Access: R_W</i> */
    DCFG_DEV_INTR_NUM_BITS	= 0x01f000,
    DCFG_DEV_INTR_NUM_SHIFT	= 12,

    /** Number of Receive Buffers		<i>Access: R_W</i> */
    DCFG_NUM_RCV_BUF_BITS	= 0x3e0000,
    DCFG_NUM_RCV_BUF_SHIFT	= 17,

    /** LPM Capable				<i>Access: R_W</i> */
    DCFG_LPM_CAP_BIT		= 0x400000,
    DCFG_LPM_CAP_SHIFT		= 22,
} dcfg_data_t;

/**
 * This enum represents the bit fields in the Device Control
 * Register (DCTL).
 */
typedef enum dctl_data {
    /** Soft Disconnect			<i>Access: R_W</i> */
    DCTL_SFT_DISCONN_BIT		= 0x00000001,
    DCTL_SFT_DISCONN_SHIFT		= 0,

    /** Test Control			<i>Access: R_W</i> */
    DCTL_TSTCTL_BITS			= 0x0000001e,
    DCTL_TSTCTL_SHIFT			= 1,

    /** USB/Link State Change Request	<i>Access: R_W</i> */
    DCTL_ULST_CHNG_REQ_BITS		= 0x000001e0,
    DCTL_ULST_CHNG_REQ_SHIFT		= 5,

    /** Requested Link State Transition/Action In SS Mode */
    LINK_STATE_REQ_NO_ACTION		= 0,	/** @< */
    LINK_STATE_REQ_SS_DISABLED		= 4,	/** @< */
    LINK_STATE_REQ_RX_DETECT		= 5,	/** @< */
    LINK_STATE_REQ_INACTIVE		= 6,	/** @< */
    LINK_STATE_REQ_RECOVERY		= 8,	/** @< */
    LINK_STATE_REQ_COMPLIANCE		= 10,	/** @< */
    LINK_STATE_REQ_LOOPBACK		= 11,	/** @< */
    LINK_STATE_REQ_HOST_MODE_ONLY	= 15,

    /** Requested Link State Transition/Action In HS/FS/LS Mode */
    LINK_STATE_REQ_REMOTE_WAKEUP	= 8,

    /** U1/U2 control			<i>Access: R_W</i> */
    DCTL_ACCEPT_U1_EN_BIT		= 0x00000200,
    DCTL_ACCEPT_U1_EN_SHIFT		= 9,
    DCTL_INIT_U1_EN_BIT			= 0x00000400,
    DCTL_INIT_U1_EN_SHIFT		= 10,
    DCTL_ACCEPT_U2_EN_BIT		= 0x00000800,
    DCTL_ACCEPT_U2_EN_SHIFT		= 11,
    DCTL_INIT_U2_EN_BIT			= 0x00001000,
    DCTL_INIT_U2_EN_SHIFT		= 12,

    /** Controller Save State		<i>Access: R_W</i> */
    DCTL_CSS_BIT			= 0x00010000,
    DCTL_CSS_SHIFT			= 16,

    /** Controller Restore State		<i>Access: R_W</i> */
    DCTL_CRS_BIT			= 0x00020000,
    DCTL_CRS_SHIFT			= 17,

    /** L1 Hibernation Enable		<i>Access: R_W</i> */
    DCTL_L1_HIBER_EN_BIT		= 0x00040000,
    DCTL_L1_HIBER_EN_RES_SHIFT		= 18,

    /** Keep Connect (for hibernation)	<i>Access: R_W</i> */
    DCTL_KEEP_CONNECT_BIT		= 0x00080000,
    DCTL_KEEP_CONNECT_SHIFT		= 19,

    /** LPM NYET Response Threshold		<i>Access: R_W</i> */
    DCTL_LPM_NYET_THRESH_BITS		= 0x00f00000,
    DCTL_LPM_NYET_THRESH_SHIFT		= 20,

    /** LPM Response			<i>Access: R_W</i> */
    DCTL_APP_L1_RES_BIT			= 0x00800000,
    DCTL_APP_L1_RES_SHIFT		= 23,

    /* HIRD Threshold			<i>Access: R_W</i> */
    DCTL_HIRD_THR_BITS			= 0x1f000000,
    DCTL_HIRD_THR_SHIFT			= 24,

    /** Light Soft Reset			<i>Access: R_W</i> */
    DCTL_LSFT_RST_BIT			= 0x20000000,
    DCTL_LSFT_RST_SHIFT			= 29,

    /** Core Soft Reset			<i>Access: R_W</i> */
    DCTL_CSFT_RST_BIT			= 0x40000000,
    DCTL_CSFT_RST_SHIFT			= 30,

    /** Run/Stop				<i>Access: R_W</i> */
    DCTL_RUN_STOP_BIT			= 0x80000000,
    DCTL_RUN_STOP_SHIFT			= 31,
} dctl_data_t;

/**
 * This enum represents the bit fields of the Device Event Enable
 * Register (DEVTEN).
 */
typedef enum devten_data {
    /** Disconnect Detected Event Enable	<i>Access: R_W</i> */
    DEVTEN_DISCONN_BIT		= 0x0001,
    DEVTEN_DISCONN_SHIFT	= 0,

    /** USB Reset Enable			<i>Access: R_W</i> */
    DEVTEN_USBRESET_BIT		= 0x0002,
    DEVTEN_USBRESET_SHIFT	= 1,

    /** Connect Done Enable			<i>Access: R_W</i> */
    DEVTEN_CONNDONE_BIT		= 0x0004,
    DEVTEN_CONNDONE_SHIFT	= 2,

    /** USB/Link State Change Event Enable	<i>Access: R_W</i> */
    DEVTEN_ULST_CHNG_BIT	= 0x0008,
    DEVTEN_ULST_CHNG_SHIFT	= 3,

    /** Resume/Remote-Wakeup Event Enable	<i>Access: R_W</i> */
    DEVTEN_WKUP_BIT		= 0x0010,
    DEVTEN_WKUP_SHIFT		= 4,

    /** Hibernation Request Event Enable	<i>Access: R_W</i> */
    DEVTEN_HIBER_REQ_BIT	= 0x0020,
    DEVTEN_HIBER_REQ_SHIFT	= 5,

    /** End of Periodic Frame Event Enable	<i>Access: R_W</i> */
    DEVTEN_U3_L2L1_SUSP_BIT	= 0x0040,
    DEVTEN_U3_L2L1_SUSP_SHIFT	= 6,

    /** Start of (Micro)Frame Enable	<i>Access: R_W</i> */
    DEVTEN_SOF_BIT		= 0x0080,
    DEVTEN_SOF_SHIFT		= 7,

    /** Erratic Error Event Enable		<i>Access: R_W</i> */
    DEVTEN_ERRATICERR_BIT	= 0x0200,
    DEVTEN_ERRATICERR_SHIFT	= 9,

    /** U2 Inactivity Timeout Enable	<i>Access: R_W</i> */
    DEVTEN_INACT_TIMEOUT_BIT	= 0x2000,
    DEVTEN_INACT_TIMEOUT_SHIFT	= 13,
} devten_data_t;

/**
 * This enum represents the bit fields in the Device Status
 * Register (DSTS).
 */
typedef enum dsts_data {
    /** Connected Speed			<i>Access: RO</i>.
     * (see enum @ref dcfg_data for values) */
    DSTS_CONNSPD_BITS		= 0x00000007,
    DSTS_CONNSPD_SHIFT		= 0,

    /** (Micro)Frame Number of Received SOF	<i>Access: RO</i> */
    DSTS_SOF_FN_BITS		= 0x0001fff8,
    DSTS_SOF_FN_SHIFT		= 3,

    /** RX Fifo Empty			<i>Access: RO</i> */
    DSTS_RXFIFO_EMPTY_BIT	= 0x00020000,
    DSTS_RXFIFO_EMPTY_SHIFT	= 17,

    /** USB/Link State			<i>Access: RO</i> */
    DSTS_USBLNK_STATE_BITS	= 0x003c0000,
    DSTS_USBLNK_STATE_SHIFT	= 18,

    /** USB/Link State values same as for devt_data_t */

    /** Device Controller Halted		<i>Access: RO</i> */
    DSTS_DEV_CTRL_HLT_BIT	= 0x00400000,
    DSTS_DEV_CTRL_HLT_SHIFT	= 22,

    /** Core Idle				<i>Access: RO</i> */
    DSTS_CORE_IDLE_BIT		= 0x00800000,
    DSTS_CORE_IDLE_SHIFT	= 23,

    /** Save State Status			<i>Access: RO</i> */
    DSTS_SSS_BIT		= 0x01000000,
    DSTS_SSS_SHIFT		= 24,

    /** Restore State Status		<i>Access: RO</i> */
    DSTS_RSS_BIT		= 0x02000000,
    DSTS_RSS_SHIFT		= 25,

    /** Save/Restore Error			<i>Access: RO</i> */
    DSTS_SRE_BIT		= 0x10000000,
    DSTS_SRE_SHIFT		= 28,

    /** Link-state Not Ready		<i>Access: RO</i> */
    DSTS_LNR_BIT		= 0x20000000,
    DSTS_LNR_SHIFT		= 29,
} dsts_data_t;

/**
 * This enum represents the bit fields in the Device Generic Command Parameter
 * Register (DGCMDPARn) for the various commands.
 */
typedef enum dgcmdpar_data {
    /** Periodic Parameters - for DGCMD_SET_PERIODIC_PARAMS command */
    DGCMD_PER_PARAM_SEL_BITS		= 0x000003ff,
    DGCMD_PER_PARAM_SEL_SHIFT		= 0,

    /** Host Role Request - for DGCMD_XMIT_HOST_ROLE_REQUEST command */
    DGCMDPAR_HOST_ROLE_REQ_BITS		= 0x00000003,
    DGCMDPAR_HOST_ROLE_REQ_SHIFT	= 0,

    /** RSP Phase values - for DGCMD_XMIT_HOST_ROLE_REQUEST (older
     * cores) or DGCMD_HOST_ROLE_REQ_DEV_NOTIF (newer cores) */
    DGCMDPAR_HOST_ROLE_REQ_INITIATE		= 1,	/** @< */
    DGCMDPAR_HOST_ROLE_REQ_CONFIRM		= 2,

    /** Notification Type - for DGCMD_XMIT_DEV_NOTIF command */
    DGCMDPAR_DEV_NOTIF_TYPE_BITS	= 0x0000000f,
    DGCMDPAR_DEV_NOTIF_TYPE_SHIFT	= 0,

    /** Notification Type values - for DGCMD_XMIT_DEV_NOTIF command */
    DGCMD_FUNCTION_WAKE_DEV_NOTIF		= 1,	/** @< */
    DGCMD_LATENCY_TOL_DEV_NOTIF			= 2,	/** @< */
    DGCMD_BUS_INTVL_ADJ_DEV_NOTIF		= 3,	/** @< */
    DGCMD_HOST_ROLE_REQ_DEV_NOTIF		= 4,

    /** Notification Parameters - for DGCMD_XMIT_DEV_NOTIF command */
    DGCMDPAR_DEV_NOTIF_PARAM_BITS	= 0xfffffff0,
    DGCMDPAR_DEV_NOTIF_PARAM_SHIFT	= 4,

    /** Best Effort Latency Tolerance Value - for
     * DGCMD_LATENCY_TOL_DEV_NOTIF command type */
    DGCMDPAR_BELT_VALUE_BITS		= 0x000003ff,
    DGCMDPAR_BELT_VALUE_SHIFT		= 0,

    /** Best Effort Latency Tolerance Scale - for
     * DGCMD_LATENCY_TOL_DEV_NOTIF command type */
    DGCMDPAR_BELT_SCALE_BITS		= 0x00000c00,
    DGCMDPAR_BELT_SCALE_SHIFT		= 10,

    /** Latency Scale values (ns) */
    LATENCY_VALUE_MULT_1024			= 1,	/** @< */
    LATENCY_VALUE_MULT_32768			= 2,	/** @< */
    LATENCY_VALUE_MULT_1048576			= 3,
} dgcmdpar_data_t;

/**
 * This enum represents the bit fields in the Device Generic Command
 * Register (DGCMDn).
 */
typedef enum dgcmd_data {
    /** Command Type			<i>Access: R_W</i> */
    DGCMD_TYP_BITS			= 0x0ff,
    DGCMD_TYP_SHIFT			= 0,

    /** Command Type values */
    DGCMD_SET_PERIODIC_PARAMS			= 2,	/** @< */
    DGCMD_XMIT_FUNC_WAKE_DEV_NOTIF		= 3,	/** @< */
    DGCMD_SET_SCRATCHPAD_ARRAY_ADR_LO		= 4,	/** @< */
    DGCMD_SET_SCRATCHPAD_ARRAY_ADR_HI		= 5,	/** @< */
    DGCMD_XMIT_HOST_ROLE_REQUEST		= 6,	/** @< */
    DGCMD_XMIT_DEV_NOTIF			= 7,	/** @< */
    DGCMD_SELECTED_FIFO_FLUSH			= 9,	/** @< */
    DGCMD_ALL_FIFO_FLUSH			= 10,	/** @< */
    DGCMD_SET_EP_NRDY				= 12,	/** @< */
    DGCMD_RUN_SOC_BUS_LOOPBK_TST		= 16,

    /** Command Interrupt on Complete	<i>Access: R_W</i> */
    DGCMD_IOC_BIT			= 0x100,
    DGCMD_IOC_SHIFT			= 8,

    /** Command Active			<i>Access: R_W</i> */
    DGCMD_ACT_BIT			= 0x400,
    DGCMD_ACT_SHIFT			= 10,

    /** Command Status			<i>Access: R_W</i> */
    DGCMD_STS_BITS			= 0xf000,
    DGCMD_STS_SHIFT			= 12,

    /** Command Status values */
    DGCMD_STS_ERROR				= 15,
} dgcmd_data_t;

/**
 * This enum represents the bit fields in the Device Endpoint Mapping
 * Registers (DEPMAPn).
 */
typedef enum depmap_data {
    /** Resource Number			<i>Access: R_W / RO</i> */
    EPMAP_RES_NUM_BITS		= 0x1f,
    EPMAP_RES_NUM_SHIFT		= 0,
} depmap_data_t;

/**
 * Device Global Registers	<i>Offsets 700h-7FCh</i>.
 *
 * The following structures define the size and relative field offsets
 * for the Device Mode Global Registers.
 */
typedef struct usb3_dev_global_regs
{

#define DEV_GLOBAL_REG_OFFSET	0xC700

    /** Device Configuration Register		<i>Offset: C700h</i>.
     * Fields defined in enum @ref dcfg_data. */
    volatile u32 dcfg;

    /** Device Control Register			<i>Offset: C704h</i>.
     * Fields defined in enum @ref dctl_data. */
    volatile u32 dctl;

    /** Device All Endpoints Interrupt Mask Register <i>Offset: C708h</i>.
     * Fields defined in enum @ref devten_data. */
    volatile u32 devten;

    /** Device Status Register			<i>Offset: C70Ch</i>.
     * Fields defined in enum @ref dsts_data. */
    volatile u32 dsts;

    /** Device Generic Command Parameter Register	<i>Offset: C710h</i>.
     * Fields defined in enum @ref dgcmdpar_data. */
    volatile u32 dgcmdpar;

    /** Device Generic Command Register		<i>Offset: C714h</i>.
     * Fields defined in enum @ref dgcmd_data. */
    volatile u32 dgcmd;

    /** reserved				<i>Offset: C718h-C71Ch</i> */
    volatile u32 reserved[2];

    /** Device Active Logical Endpoint Enable Register <i>Offset: C720h</i>.
     * One bit per logical endpoint, bit0=EP0 ... bit31=EP31. */
    volatile u32 dalepena;

    /** reserved				<i>Offset: C724h-C7FCh</i> */
    volatile u32 reserved1[54];

    /** Device Physical Endpoint-n Command Parameter 2 Register <i>Offset: C800</i> */
}
usb3_dev_global_regs_t;


/****************************************************************************/
/* Device Endpoint Specific Registers */

/**
 * This enum represents the bit fields in the Device Endpoint Command
 * Parameter 1 Register (DEPCMDPAR1n) for the Set Endpoint Configuration
 * (DEPCFG) command.
 */
typedef enum depcfgpar1_data {
    /** Interrupt number */
    EPCFG1_INTRNUM_BITS		= 0x0000003f,
    EPCFG1_INTRNUM_SHIFT	= 0,

    /** Stream Completed */
    EPCFG1_XFER_CMPL_BIT	= 0x00000100,
    EPCFG1_XFER_CMPL_SHIFT	= 8,

    /** Stream In Progress */
    EPCFG1_XFER_IN_PROG_BIT	= 0x00000200,
    EPCFG1_XFER_IN_PROG_SHIFT	= 9,

    /** Stream Not Ready */
    EPCFG1_XFER_NRDY_BIT	= 0x00000400,
    EPCFG1_XFER_NRDY_SHIFT	= 10,

    /** Rx FIFO Underrun / Tx FIFO Overrun */
    EPCFG1_FIFOXRUN_BIT		= 0x00000800,
    EPCFG1_FIFOXRUN_SHIFT	= 11,

    /** Back-to-Back Setup Packets Received	 */
    EPCFG1_SETUP_PNDG_BIT	= 0x00001000,
    EPCFG1_SETUP_PNDG_SHIFT	= 12,

    /** Endpoint Command Complete */
    EPCFG1_EPCMD_CMPL_BIT	= 0x00002000,
    EPCFG1_EPCMD_CMPL_SHIFT	= 13,

    /** Endpoint bInterval */
    EPCFG1_BINTERVAL_BITS	= 0x00ff0000,
    EPCFG1_BINTERVAL_SHIFT	= 16,

    /** Endpoint Stream Capability */
    EPCFG1_STRM_CAP_BIT		= 0x01000000,
    EPCFG1_STRM_CAP_SHIFT	= 24,

    /** Endpoint Direction */
    EPCFG1_EP_DIR_BIT		= 0x02000000,
    EPCFG1_EP_DIR_SHIFT		= 25,

    /** Endpoint Number */
    EPCFG1_EP_NUM_BITS		= 0x3c000000,
    EPCFG1_EP_NUM_SHIFT		= 26,
} depcfgpar1_data_t;

/**
 * This enum represents the bit fields in the Device Endpoint Command
 * Parameter 0 Register (DEPCMDPAR0n) for the Set Endpoint Configuration
 * (EPCMD_SET_EP_CFG) command.
 */
typedef enum depcfgpar0_data {
    /** Endpoint Type			<i>Access: R_W</i> */
    EPCFG0_EPTYPE_BITS			= 0x00000006,
    EPCFG0_EPTYPE_SHIFT			= 1,

    /** Endpoint Type values */
    USB3_EP_TYPE_CONTROL	= 0,	/** @< */
    USB3_EP_TYPE_ISOC		= 1,	/** @< */
    USB3_EP_TYPE_BULK		= 2,	/** @< */
    USB3_EP_TYPE_INTR		= 3,

    /** Maximum Packet Size			<i>Access: R_W</i> */
    EPCFG0_MPS_BITS			= 0x00003ff8,
    EPCFG0_MPS_SHIFT			= 3,

    /** Flow Control State			<i>Access: R_W</i> */
    EPCFG0_FLOW_CTRL_STATE_BIT		= 0x00010000,
    EPCFG0_FLOW_CTRL_STATE_SHIFT	= 16,

    /** Tx Fifo Number (IN endpoints only)	<i>Access: R_W</i> */
    EPCFG0_TXFNUM_BITS			= 0x003e0000,
    EPCFG0_TXFNUM_SHIFT			= 17,

    /** Burst Size				<i>Access: R_W</i> */
    EPCFG0_BRSTSIZ_BITS			= 0x03c00000,
    EPCFG0_BRSTSIZ_SHIFT		= 22,

    /** Data Sequence Num (old)		<i>Access: R_W</i> */
    EPCFG0_DSNUM_BITS			= 0x7c000000,
    EPCFG0_DSNUM_SHIFT			= 26,

    /** Ignore Data Sequence Num (old)	<i>Access: R_W</i> */
    EPCFG0_IGN_DSNUM_BIT		= 0x80000000,
    EPCFG0_IGN_DSNUM_SHIFT		= 31,

    /** Config Action (new)			<i>Access: R_W</i> */
    EPCFG0_CFG_ACTION_BITS		= 0xc0000000,
    EPCFG0_CFG_ACTION_SHIFT		= 30,

    /** Config Action values (new) */
    CFG_ACTION_INIT		= 0,	/** @< */
    CFG_ACTION_RESTORE		= 1,	/** @< */
    CFG_ACTION_MODIFY		= 2,
} depcfgpar0_data_t;

/**
 * This enum represents the bit fields in the Device Endpoint Command
 * Register (DEPCMDn).
 */
typedef enum depcmd_data {
    /** Command Type			<i>Access: R_W</i> */
    EPCMD_TYP_BITS		= 0x0ff,
    EPCMD_TYP_SHIFT		= 0,

    /** Command Type values */
    EPCMD_SET_EP_CFG	= 1,	/** @< */
    EPCMD_SET_XFER_CFG	= 2,	/** @< */
    EPCMD_GET_EP_STATE	= 3,	/** @< */
    EPCMD_SET_STALL	= 4,	/** @< */
    EPCMD_CLR_STALL	= 5,	/** @< */
    EPCMD_START_XFER	= 6,	/** @< */
    EPCMD_UPDATE_XFER	= 7,	/** @< */
    EPCMD_END_XFER	= 8,	/** @< */
    EPCMD_START_NEW_CFG	= 9,

    /** Command Interrupt on Complete	<i>Access: R_W</i> */
    EPCMD_IOC_BIT		= 0x100,
    EPCMD_IOC_SHIFT		= 8,

    /** Command Active			<i>Access: R_W</i> */
    EPCMD_ACT_BIT		= 0x400,
    EPCMD_ACT_SHIFT		= 10,

    /** High Priority / Force RM Bit	<i>Access: R_W</i> */
    EPCMD_HP_FRM_BIT		= 0x800,
    EPCMD_HP_FRM_SHIFT		= 11,

    /** Command Completion Status		<i>Access: R_W</i> */
    EPCMD_CMPL_STS_BITS		= 0xf000,
    EPCMD_CMPL_STS_SHIFT	= 12,

    /** Stream Number or uFrame (input)	<i>Access: R_W</i> */
    EPCMD_STR_NUM_OR_UF_BITS	= 0xffff0000,
    EPCMD_STR_NUM_OR_UF_SHIFT	= 16,

    /** Transfer Resource Index (output)	<i>Access: R_W</i> */
    EPCMD_XFER_RSRC_IDX_BITS	= 0x007f0000,
    EPCMD_XFER_RSRC_IDX_SHIFT	= 16,
} depcmd_data_t;

/**
 * Device Endpoint Specific Registers <i>Offsets 800h-9ECh for OUT,
 *						 810h-9FCh for IN</i>.
 * There will be one set of endpoint registers per logical endpoint
 * implemented.
 */
typedef struct usb3_dev_ep_regs
{

#define DEV_OUT_EP_REG_OFFSET	0xC800
#define DEV_IN_EP_REG_OFFSET	0xC810
#define EP_REG_OFFSET		0x20

    /** Device Endpoint Command Parameter 2 Register <i>Offset: C800h/C810h +
     *					(ep_num * 20h) + 00h</i> */
    volatile u32 depcmdpar2;

    /** Device Endpoint Command Parameter 1 Register <i>Offset: C800h/C810h +
     *					(ep_num * 20h) + 04h</i> */
    volatile u32 depcmdpar1;

    /** Device Endpoint Command Parameter 0 Register <i>Offset: C800h/C810h +
     *					(ep_num * 20h) + 08h</i> */
    volatile u32 depcmdpar0;

    /** Device Endpoint Command Register	<i>Offset: C800h/C810h +
     *					(ep_num * 20h) + 0Ch</i>.
     * Fields defined in enum @ref depcmd_data. */
    volatile u32 depcmd;

    /** reserved				<i>Offset: C800h/C810h +
     *					(ep_num * 20h) + 10h-1Ch</i> */
    volatile u32 reserved[4];
}
usb3_dev_ep_regs_t;

/****************************************************************************/
/* DMA Descriptor Specific Structures */

/**
 * This enum represents the bit fields in the DMA Descriptor
 * Status quadlet.
 */
typedef enum desc_sts_data {
    /** Transfer Count */
    DSCSTS_XFRCNT_BITS	= 0x00ffffff,
    DSCSTS_XFRCNT_SHIFT	= 0,

    /** Packet Count Minus 1 (for HS IN transfers) */
    DSCSTS_PCM1_BITS	= 0x03000000,
    DSCSTS_PCM1_SHIFT	= 24,

    /** Transfer Request Block Response */
    DSCSTS_TRBRSP_BITS	= 0xf0000000,
    DSCSTS_TRBRSP_SHIFT	= 28,

    /** Response values */
    TRBRSP_MISSED_ISOC_IN	= 1,	/** @< */
    TRBRSP_SETUP_PEND		= 2,	/** @< */
    TRBRSP_XFER_IN_PROG		= 4,
} desc_sts_data_t;

/**
 * This enum represents the bit fields in the DMA Descriptor
 * Control quadlet.
 */
typedef enum desc_ctl_data {
    /** Hardware-Owned bit */
    DSCCTL_HWO_BIT		= 0x00000001,
    DSCCTL_HWO_SHIFT		= 0,

    /** Last Descriptor bit */
    DSCCTL_LST_BIT		= 0x00000002,
    DSCCTL_LST_SHIFT		= 1,

    /** Chain Buffer bit */
    DSCCTL_CHN_BIT		= 0x00000004,
    DSCCTL_CHN_SHIFT		= 2,

    /** Continue on Short Packet bit */
    DSCCTL_CSP_BIT		= 0x00000008,
    DSCCTL_CSP_SHIFT		= 3,

    /** Transfer Request Block Control field */
    DSCCTL_TRBCTL_BITS		= 0x000003f0,
    DSCCTL_TRBCTL_SHIFT		= 4,

    /** Transfer Request Block Control types */
    DSCCTL_TRBCTL_NORMAL		= 1,	/** @< */
    DSCCTL_TRBCTL_SETUP			= 2,	/** @< */
    DSCCTL_TRBCTL_STATUS_2		= 3,	/** @< */
    DSCCTL_TRBCTL_STATUS_3		= 4,	/** @< */
    DSCCTL_TRBCTL_CTLDATA_1ST		= 5,	/** @< */
    DSCCTL_TRBCTL_ISOC_1ST		= 6,	/** @< */
    DSCCTL_TRBCTL_ISOC			= 7,	/** @< */
    DSCCTL_TRBCTL_LINK			= 8,

    /** Interrupt on Short Packet bit */
    DSCCTL_ISP_BIT		= 0x00000400,
    DSCCTL_ISP_SHIFT		= 10,
#define DSCCTL_IMI_BIT	DSCCTL_ISP_BIT
#define DSCCTL_IMI_SHIFT	DSCCTL_ISP_SHIFT

    /** Interrupt on Completion bit */
    DSCCTL_IOC_BIT		= 0x00000800,
    DSCCTL_IOC_SHIFT		= 11,

    /** Stream ID / SOF Number */
    DSCCTL_STRMID_SOFN_BITS	= 0x3fffc000,
    DSCCTL_STRMID_SOFN_SHIFT	= 14,
} desc_ctl_data_t;

/**
 * DMA Descriptor structure
 *
 * DMA Descriptor structure contains 4 quadlets:
 * Buffer Pointer Low address, Buffer Pointer High address, Status, and Control.
 */
typedef struct usb3_dma_desc
{
    /** Buffer Pointer - Low address quadlet */
    u32	bptl;

    /** Buffer Pointer - High address quadlet */
    u32	bpth;

    /** Status quadlet. Fields defined in enum @ref desc_sts_data. */
    u32	status;

    /** Control quadlet. Fields defined in enum @ref desc_ctl_data. */
    u32	control;
}
usb3_dma_desc_t;

/**
 * The <code>ep</code> structure represents the state of a single EP
 * when acting in device mode. It contains the data items needed for an EP
 * to be activated and transfer packets.
 */
typedef struct ep {
	/** Pointer to PCD */
	struct usb3_pcd *pcd;

	/** Pointer to OUT EP register */
	usb3_dev_ep_regs_t __iomem *out_ep_reg;

	/** Pointer to IN EP register */
	usb3_dev_ep_regs_t __iomem *in_ep_reg;

	/** Physical EP number */
	u8 phys;

	/** USB EP number */
	u8 num;

	/** EP type: 0 - Control, 1 - ISOC, 2 - BULK, 3 - INTR */
	u8 type;

	/** 'bInterval' value for Isoc EPs */
	u8 intvl;

	/** Max Packet bytes */
	u16 maxpacket;

	/** 'mult' value for SS Isoc EPs */
	u8 mult;

	/** Max burst size for SS EPs (0 - 15, actual burst is 1 - 16) */
	u8 maxburst;

	/** Number of streams for SS Bulk EPs (0 - 16, actual number is 2^n) */
	u8 num_streams;

	/** Tx FIFO # for IN EPs */
	u8 tx_fifo_num;

	/** @{ */
	/** Transfer Resource Index from the Start Transfer command */
	u8 tri_out;
	u8 tri_in;
	/** @} */

	/** @{ */
	/** Status of the queue */
	unsigned int stopped		: 1;
	//unsigned int disabling		: 1;
	//unsigned int queue_sof		: 1;
	/** @} */

	/** @{ */
	/** Send ZLP */
	unsigned int send_zlp		: 1;

	/** Stall clear flag */
	unsigned int stall_clear_flag	: 1;

	/** True if 3-stage control transfer */
	unsigned int three_stage	: 1;

	/** True if transfer has been started on EP */
	unsigned int xfer_started	: 1;
	/** @} */

	/** EP direction 0 = OUT */
	unsigned int is_in		: 1;

	/** EP active */
	unsigned int active		: 1;

	/** True if TRB array has a link TRB at the end */
	//unsigned int desc_link		: 1;

	/** DATA start PID for INTR and BULK EP */
	unsigned int data_pid_start	: 1;

	/** EP has been enabled for this configuration */
	//unsigned int ena_once		: 1;

	/** EP was in stalled state when entering hibernation */
	//unsigned int stalled_save	: 1;

	/** Pointer to USB EP descriptor */
	//const usb_endpoint_descriptor_t *usb_ep_desc;

	/** @{ */
	/** Array of DMA descriptors (TRBs) for this EP */
	usb3_dma_desc_t *dma_desc;
	//int desc_size;
	//int num_desc;
	/** @} */

	/** Number of DMA descriptors available */
	//int desc_avail;

	/** Index to next free DMA descriptor in array */
	//int desc_idx;

} ep_t;

/** PCD EP structure.
 * This structure describes an EP, there is an array of EP pointers in the
 * PCD structure.
 */
typedef struct usb3_pcd_ep {
	/** usb3 EP data */
	ep_t ep;

} usb3_pcd_ep_t;

/** usb3 PCD Structure.
 * This structure encapsulates the data for the usb3 PCD.
 */
typedef struct usb3_pcd {
	/** The DWC otg device pointer */
	struct usb3_device *usb3_dev;

	/** USB3 link state */
    //int link_state;

	/** State of the device */
	pcdstate_e state;

	/** State of EP0 */
	ep0state_e ep0state;

	/** EP0 Status Request is pending */
	unsigned int ep0_status_pending		: 1;

	/** EP0 */
	usb3_pcd_ep_t* ep0;

	/** OUT and IN EPs (not including EP0) */
	usb3_pcd_ep_t *out_ep, *in_ep;

	/** Pointer to device Global registers.
	 * Device Global Registers starting at offset C700h
	 */
	usb3_dev_global_regs_t __iomem *dev_global_regs;

	/** Device Logical OUT EP-Specific Registers C800h-C9ECh */
	usb3_dev_ep_regs_t __iomem *out_ep_regs;

	/** Device Logical IN EP-Specific Registers C810h-C9FCh */
	usb3_dev_ep_regs_t __iomem *in_ep_regs;

	/** Device configuration information */

	u8 speed;	/**< Device Speed - 0:Unk 1:LS 2:FS 3:HS 4:Var 5:SS */

	/**
	 * Pointers to the DMA Descriptors for EP0 Control transfers
	 * (virtual and physical)
	 */

	/** @{ */
	/** Descriptor for SETUP packets */
	usb3_dma_desc_t* ep0_setup_desc;
	/** @} */

	/** @{ */
	/** Descriptor for Data Out or Status Out phases */
	usb3_dma_desc_t* ep0_out_desc;
	/** @} */

	/** @{ */
	/** Descriptor for Data In or Status In phases */
	usb3_dma_desc_t* ep0_in_desc;
	/** @} */
    /** @{ */
    /** Activated configuration */
    u8* config;
	/** @} */

	/** @{ */
	/** SETUP packet buffer for EP0 */
	union setup_pkt {
		usb_device_request_t req;
		u32 d32[2];
		char d8[8];
	} *ep0_setup_pkt;
	/** @} */
} usb3_pcd_t;

/**
 * This structure is a wrapper that encapsulates the driver components used to
 * manage a single usb3 controller.
 */
typedef struct usb3_device {

	/** Base address returned from ioremap() */
	volatile u8 __iomem *base;

	/** PCD structure */
	struct usb3_pcd pcd;

	/** Core Global registers starting at offset C100h */
	usb3_core_global_regs_t __iomem *core_global_regs;

	/** @{ */
#define EVENT_BUF_SIZE	64	// size in dwords
	/** Event Buffers for receiving interrupts. Up to 32 buffers are
	 * supported by the hardware, but we only use 1.
	 */
	u32 *event_ptr; // save pending event addr
	u32 *event_buf;
    u32 event_size; // size in dwords
	/** @} */
} usb3_device_t;

/** @{ */
/** PCD accessor functions */
#define usb3_ep0_setup_desc(pcd)		(pcd)->ep0_setup_desc
#define usb3_ep0_out_desc(pcd)		(pcd)->ep0_out_desc
#define usb3_ep0_in_desc(pcd)		(pcd)->ep0_in_desc
#define usb3_ep0_setup_pkt(pcd)		(pcd)->ep0_setup_pkt
/** @} */

/** @{ */
/**
 * Register read/write.
 */
static inline u32 reg_rd32(volatile u32 __iomem *adr)
{
	return *adr;
}

static inline void reg_wr32(volatile u32 __iomem *adr, u32 val)
{
	*adr = val;
}
/** @} */


#endif

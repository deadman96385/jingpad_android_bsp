#ifndef _PAM_WIFI_TESTCASE_H
#define _PAM_WIFI_TESTCASE_H

#include <linux/io.h>
#include <linux/sipa.h>
#include "pam_wifi.h"
//#include "sipa_hal_priv.h"
#include <misc/marlin_platform.h>
#include "sprdwl.h"
#include "core_sc2355.h"
#include "if_sc2355.h"
#include "tx_msg_sc2355.h"
#include "qos.h"
#include <linux/platform_device.h>
#include <linux/of_address.h>
#include <linux/io.h>
#include <linux/regmap.h>
#include <linux/mfd/syscon.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <net/ip.h>
#include <linux/kthread.h>

typedef int BOOLEAN ;
/* bitmap for the highest byte of 40 bit-wide address */
#define PAM_BITS_LOWADDR32			32
#define PAM_MASK_LOWADDR32			GENMASK(31, 0)
#define PAM_MASK_ADDR32_LSB			GENMASK(7, 0)
#define PTR_MASK(depth) (depth | (depth - 1))

/*Common fifo reg*/
#define PAMWIFI_COMMON_RX_FIFO_DEPTH		0x00
#define PAMWIFI_COMMON_RX_FIFO_WR			0x04
#define PAMWIFI_COMMON_RX_FIFO_RD			0x08
#define PAMWIFI_COMMON_TX_FIFO_DEPTH		0x0C
#define PAMWIFI_COMMON_TX_FIFO_WR			0x10
#define PAMWIFI_COMMON_TX_FIFO_RD			0x14
#define PAMWIFI_COMMON_RX_FIFO_ADDRL		0x18
#define PAMWIFI_COMMON_RX_FIFO_ADDRH		0x1C
#define PAMWIFI_COMMON_TX_FIFO_ADDRL		0x20
#define PAMWIFI_COMMON_TX_FIFO_ADDRH		0x24
#define PAMWIFI_PERFETCH_FIFO_CTL				0x28
#define PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE	0x2C
#define PAMWIFI_INT_GEN_CTL_EN				0x30

#define PAMWIFI_TXFIFO_INT_THRESHOLD_ONESHOT_EN	(1l << 11)
#define PAMWIFI_TXFIFO_INT_THRESHOLD_SW_EN		(1l << 10)
#define PAMWIFI_TXFIFO_INT_DELAY_TIMER_SW_EN	(1l << 9)
#define PAMWIFI_TXFIFO_FULL_INT_EN				(1l << 8)
#define PAMWIFI_TXFIFO_OVERFLOW_EN				(1l << 7)
#define PAMWIFI_ERRORCODE_IN_TX_FIFO_EN			(1l << 6)
//#define IPA_DROP_PACKET_OCCUR_INT_EN		(1l << 5)
//#define IPA_RX_FIFO_INT_EXIT_FLOW_CTRL_EN	(1l << 4)
//#define IPA_RX_FIFO_INT_ENTER_FLOW_CTRL_EN	(1l << 3)
#define PAMWIFI_TX_FIFO_INTR_SW_BIT_EN			(1l << 2)
#define PAMWIFI_TX_FIFO_THRESHOLD_EN			(1l << 1)
#define PAMWIFI_TX_FIFO_DELAY_TIMER_EN			(1l << 0)
#define PAMWIFI_INT_EN_BIT_GROUP				0x00000FFFl

struct sipa_cmn_fifo_tag {
	u32 depth;
	u32 wr;
	u32 rd;
	bool in_iram;

	u32 fifo_base_addr_l;
	u32 fifo_base_addr_h;

	void *virtual_addr;
	u64 fifo_reg_base;
};

struct sipa_node_description_tag {
	/*soft need to set*/
	u64 address : 40;
	/*soft need to set*/
	u32 length : 20;
	/*soft need to set*/
	u16 offset : 12;
	/*soft need to set*/
	u8	net_id;
	/*soft need to set*/
	u8	src : 5;
	/*soft need to set*/
	u8	dst : 5;
	u8	prio : 3;
	u8	bear_id : 7;
	/*soft need to set*/
	u8	intr : 1;
	/*soft need to set*/
	u8	indx : 1;
	u8	err_code : 4;
	u32 reserved : 22;
}__packed;

enum sipa_cmn_fifo_index {
	SIPA_FIFO_USB_UL = 0, /*PAM_U3 -> IPA*/
	SIPA_FIFO_SDIO_UL,
	SIPA_FIFO_AP_IP_UL, /*AP -> IPA*/
	SIPA_FIFO_PCIE_UL,
	/* UL PCIE 0 ~ 3*/
	SIPA_FIFO_REMOTE_PCIE_CTRL0_UL,
	SIPA_FIFO_REMOTE_PCIE_CTRL1_UL,
	SIPA_FIFO_REMOTE_PCIE_CTRL2_UL,
	SIPA_FIFO_REMOTE_PCIE_CTRL3_UL,
	SIPA_FIFO_AP_ETH_DL, /*ap_dev -> IPA*/
	/* DL mAP PCIE 0 ~ 3*/
	SIPA_FIFO_LOCAL_PCIE_CTRL0_DL,
	SIPA_FIFO_LOCAL_PCIE_CTRL1_DL,
	SIPA_FIFO_LOCAL_PCIE_CTRL2_DL,
	SIPA_FIFO_LOCAL_PCIE_CTRL3_DL,
	SIPA_FIFO_WIFI_UL,
	SIPA_FIFO_CP_DL, /*PAM_IPA -> IPA*/
	SIPA_FIFO_USB_DL, /*IPA -> PAM_U3*/
	SIPA_FIFO_SDIO_DL,
	SIPA_FIFO_AP_IP_DL, /*IPA -> AP*/
	SIPA_FIFO_PCIE_DL,
	/* DL PCIE 0 ~ 3*/
	SIPA_FIFO_REMOTE_PCIE_CTRL0_DL,
	SIPA_FIFO_REMOTE_PCIE_CTRL1_DL,
	SIPA_FIFO_REMOTE_PCIE_CTRL2_DL,
	SIPA_FIFO_REMOTE_PCIE_CTRL3_DL,
	SIPA_FIFO_AP_ETH_UL, /*IPA -> ap_dev*/
	/* UL mAP PCIE 0 ~ 3*/
	SIPA_FIFO_LOCAL_PCIE_CTRL0_UL,
	SIPA_FIFO_LOCAL_PCIE_CTRL1_UL,
	SIPA_FIFO_LOCAL_PCIE_CTRL2_UL,
	SIPA_FIFO_LOCAL_PCIE_CTRL3_UL,
	SIPA_FIFO_WIFI_DL,
	SIPA_FIFO_CP_UL, /*IPA -> PAM_IPA*/
	SIPA_FIFO_MAX
};

/*
enum term_id_tag {
	term_usb_ul, //PAM_USB -> IPA
	term_sdio_ul,
	term_ap_ip_tx, //mAP_DL_Tx src:ap dst:cp AP -> CP
	term_pcie_ul,
	term_pcie_ul_ch0,
	term_pcie_ul_ch1,
	term_pcie_ul_ch2,
	term_pcie_ul_ch3,
	term_ap_eth_tx, //mAP_UL_Tx AP -> IPA src:ap dst:usb/wifi
	term_ap_pcie_dl_ch0,
	term_ap_pcie_dl_ch1,
	term_ap_pcie_dl_ch2,
	term_ap_pcie_dl_ch3,
	term_wifi_ul,
	term_wiap_ul, //IPA -> PAM_IPA
	term_usb_dl, //IPA -> PAM_USB
	term_sdio_dl,
	term_ap_ip_rx, //mAP_DL_Rx src:cp dst:mAP IPA -> AP
	term_pcie_dl,
	term_pcie_dl_ch0,
	term_pcie_dl_ch1,
	term_pcie_dl_ch2,
	term_pcie_dl_ch3,
	term_ap_eth_rx, //mAP_UL_Rx src:non-cp dst:mAP IPA -> AP
	term_ap_pcie_ul_ch0,
	term_ap_pcie_ul_ch1,
	term_ap_pcie_ul_ch2,
	term_ap_pcie_ul_ch3,
	term_wifi_dl,
	term_wiap_dl, //PAM_IPA -> IPA
	term_max,
};
*/

struct data_pkt_tag {
	struct data_pkt_tag *next;

	u8 *head_ptr;
	u32 total_len;
	u8 *data_ptr;
	u32 data_len;
	u8 netid;
	u8 err_code;
	u8 bear_id;
	u8 prio;
	u8 dst;
	u8 src;
	u8 stat;
	u8 indx;

	u32 context;
};

enum dl_fifo_type {
	dl_fifo_free,
	dl_tx_fifo_type1,
	dl_tx_fifo_type2,
	dl_tx_fifo_type3,
	dl_tx_fifo_type4,
};

struct ipa_cmn_tx_fifo_t {
	struct sipa_node_description_tag *fifo_base;

	u32 depth;
	u32 depth_mask;
	u32 max_depth;
	u32 wr;
	u32 rd;

	u32 fifo_base_addr_l;
	u32 fifo_base_addr_h;
};

struct ipa_cmn_rx_fifo_t {
	struct sipa_node_description_tag *fifo_base;

	u32 depth;
	u32 depth_mask;
	u32 max_depth;
	u32 wr;
	u32 rd;

	u32 fifo_base_addr_l;
	u32 fifo_base_addr_h;
};

/*
struct ipa_receiver_t {
	const char *fifo_name;

	enum sipa_cmn_fifo_index term_id;
	enum sipa_cmn_fifo_index term_id_send;

	u32 state;
	u32 pending;
	u32 is_dma;
	u32 dst;
	u32 cur;
	u64 fifo_reg_base;

	struct ipa_cmn_rx_fifo_t rx_fifo;
	struct ipa_cmn_tx_fifo_t tx_fifo;

	ipa_callback_func_t errcode_callback;
	ipa_callback_func_t drop_occur_callback;
	ipa_callback_func_t flow_ctrl_callback;
	ipa_callback_func_t intr_callback;
	ipa_callback_func_t threshold_callback;
	ipa_callback_func_t delay_timer_callback;
	ipa_callback_func_t txfifo_overflow_callback;
	ipa_callback_func_t txfifo_full_callback;

	void *cookie;
};
*/

#define PAM_WIFI_UL_TX_FIFO_DEPTH		512
#define PAM_WIFI_UL_RX_FIFO_DEPTH		512
#define PAM_WIFI_DL_TX_FIFO_DEPTH		512
#define PAM_WIFI_DL_RX_FIFO_DEPTH		512

#define BITINT_EN_DL_INDEX_MISS                                 (BIT_(7))
#define BITINT_EN_DL_FILL_TYPE4                                 (BIT_(6))
#define BITINT_EN_DL_FILL_TYPE3                                 (BIT_(5))
#define BITINT_EN_DL_FILL_TYPE2                                 (BIT_(4))
#define BITINT_EN_DL_FILL_TYPE1                                 (BIT_(3))
#define BITINT_EN_DL_FREE                                       (BIT_(2))
#define BITINT_EN_UL_FILL                                       (BIT_(1))
#define BITINT_EN_UL_FREE                                       (BIT_(0))

enum pam_wifi_term_id {
	pam_wifi_term_ul,
	pam_wifi_term_dl,
	pam_wifi_term_max,
};

struct pam_wifi_sender {
	const char *fifo_name;

	enum pam_wifi_term_id pam_wifi_term_id;
	enum pam_wifi_term_id pam_wifi_term_id_recv;

	u32 state;
	u32 pending;
	u32 is_dma;
	u32 dst;
	u32 cur;

	/*match with rx_fifo*/
	u64 dl_free_fifo_reg_base;
	u64 dl_tx_type1_fifo_reg_base;
	u64 dl_tx_type2_fifo_reg_base;
	u64 dl_tx_type3_fifo_reg_base;
	u64 dl_tx_type4_fifo_reg_base;

	struct sipa_cmn_fifo_tag dl_free_fifo;
	struct sipa_cmn_fifo_tag tx_fifo_type1;
	struct sipa_cmn_fifo_tag tx_fifo_type2;
	struct sipa_cmn_fifo_tag tx_fifo_type3;
	struct sipa_cmn_fifo_tag tx_fifo_type4;

	void *threshold_callback;
	void *delay_timer_callback;
};

struct pam_wifi_send_ops {
	u32 (*open)(enum pam_wifi_term_id id, void *cookie);
	u32 (*close)(enum pam_wifi_term_id id);
	u32 (*send)(enum pam_wifi_term_id id, struct data_pkt_tag *node, u32 force_intr, u32 num, enum dl_fifo_type p_dl_fifo_type);
	//u32 (*reset)(enum pam_wifi_term_id id);
	u32(*set_rx_depth)(enum pam_wifi_term_id id, u32 depth);
	u32(*set_tx_depth)(enum pam_wifi_term_id id, u32 depth);
	u32(*get_tx_fifo_wr_rd_ptr)(enum pam_wifi_term_id id, u32 *rx_rd, u32 *rx_wr, enum dl_fifo_type p_dl_fifo_type);
	u32 (*set_interrupt_timeout)(enum pam_wifi_term_id id, u32 enable, u32 time,enum dl_fifo_type p_dl_fifo_type,
			void *cb);
	u32 (*set_interrupt_threshold)(enum pam_wifi_term_id id, u32 enable, u32 cnt, enum dl_fifo_type p_dl_fifo_type,
			void *cb);

};

struct pam_wifi_global_ops {

};

struct pam_wifi_sender_device {
	struct pam_wifi_sender term_sender[pam_wifi_term_max];

	struct pam_wifi_send_ops send_ops;
	struct pam_wifi_global_ops *ops;
};

#define IPA_MAP_CP 0x18
#define IPA_WI_AP0_ROC_AP 0x0C



#define PAM_WIFI_DL_TX_FIFO_ADDRL 0
#define PAM_WIFI_DL_TX_FIFO_ADDRH 0

#define PAM_WIFI_DL_RX_FIFO_ADDRL 0
#define PAM_WIFI_DL_RX_FIFO_ADDRH 0

#define PAM_WIFI_UL_TX_FIFO_ADDRL 0
#define PAM_WIFI_UL_TX_FIFO_ADDRH 0

#define PAM_WIFI_UL_RX_FIFO_ADDRL 0
#define PAM_WIFI_UL_RX_FIFO_ADDRH 0

struct pam_wifi_receiver {
	const char *fifo_name;

	enum pam_wifi_term_id pam_wifi_term_id;
	enum pam_wifi_term_id pam_wifi_term_id_recv;

	u32 state;
	u32 pending;
	u32 is_dma;
	u32 dst;
	u32 cur;

	u64 fifo_reg_base;

	struct sipa_cmn_fifo_tag rx_fifo;
	struct sipa_cmn_fifo_tag tx_fifo;

	void *threshold_callback;
	void *delay_timer_callback;
};

struct pam_wifi_receiver_ops {
	u32 (*open)(enum pam_wifi_term_id id, void *cookie);
	u32 (*close)(enum pam_wifi_term_id id);
	u32 (*reset)(enum pam_wifi_term_id id);
	u32(*set_rx_depth)(enum pam_wifi_term_id id, u32 depth);
	u32(*set_tx_depth)(enum pam_wifi_term_id id, u32 depth);
	u32(*set_rx_tx_fifo_wr_rd_ptr)(enum pam_wifi_term_id id, u32 rx_rd, u32 rx_wr,
		u32 tx_rd, u32 tx_wr);
	u32 (*set_interrupt_timeout)(enum pam_wifi_term_id id, u32 enable, u32 time,
			void *cb);
	u32 (*set_interrupt_threshold)(enum pam_wifi_term_id id, u32 enable, u32 cnt,
			void *cb);
	u32 (*recv)(enum pam_wifi_term_id id, struct data_pkt_tag *node, u32 force_intr, u32 num);
};

struct pam_wifi_receiver_device {
	struct pam_wifi_receiver term_receiver[pam_wifi_term_max];

	struct pam_wifi_receiver_ops recv_ops;
	struct pam_wifi_global_ops *ops;
};

/***************IRAM************************************/
#define TERM_WIFI_UL_TX_FIFO_DEPTH			1024
#define TERM_WIFI_UL_RX_FIFO_DEPTH			1024

/***************IRAM************************************/
#define	TERM_WIFI_DL_TX_FIFO_DEPTH			1024
#define	TERM_WIFI_DL_RX_FIFO_DEPTH			1024
#define BUFF_SIZE		(2048)
#define HEADER_OFFSET			0x40

//*********************Original msdu location in the memory***********
#define MAX_MSDU_NUMBER 16
//length of msdu header,increased by 64bit. Min:2,Max:6
#define CUR_MSDU_LENGTH 3
#define MAX_ONE_MSDU_LENGTH CUR_MSDU_LENGTH*8


//typedef u32 (*ipa_callback_func_t)(enum sipa_term_type evt, void *param, void* cookie);

struct pam_wifi_tos_prio{
    u8 tos_prio_2_1;
    u8 tos_prio_2_0;
    u8 tos_prio_1_1;
    u8 tos_prio_1_0;
    u8 tos_prio_0_1;
    u8 tos_prio_0_0;
};

struct sprdwl_pam_wifi_miss_node_tag {
	void *data;
	u32 cnt;
};

#define PAM_WIFI_HW_LOCK_TO           20*1000
void pam_wifi_update_router_table(struct sprdwl_sta_lut_ind *sta_lut, struct sprdwl_priv *priv, int flag);
void ipa_to_pam_wifi_init(struct sprdwl_priv *priv, struct platform_device *pdev);
void sprdwl_pam_wifi_miss_node_send(void *data);
irqreturn_t pam_wifi_miss_handle(int irq, void *dev);
int sprdwl_roc1_pkt_checksum(struct sk_buff *skb, struct net_device *ndev);
void sipa_wifi_notify_cb(void *priv, enum sipa_evt_type evt,
                               unsigned long data);
void sprdwl_pamwifi_probe(struct platform_device *pdev);
void sprdwl_pamwifi_init(struct sprdwl_vif *vif, struct platform_device *pdev);
void sprdwl_deinit_pamwifi_fifo(struct sprdwl_priv *priv, struct platform_device *pdev);
int sprdwl_xmit_to_ipa_pamwifi(struct sk_buff *skb, struct net_device *ndev);
u32 pam_wifi_update_tx_fifo_wptr(u64 fifo_base, u32 wptr);
u32 check_pamwifi_ipa_fifo_status(void);
void clear_reg_bits(u64 u4_addr, u32 mask);
u32 pam_wifi_enable(void);
u32 pam_wifi_disable(void);
#endif

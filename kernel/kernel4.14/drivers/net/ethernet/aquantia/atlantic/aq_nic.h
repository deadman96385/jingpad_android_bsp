/*
 * aQuantia Corporation Network Driver
 * Copyright (C) 2014-2017 aQuantia Corporation. All rights reserved
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */

/* File aq_nic.h: Declaration of common code for NIC. */

#ifndef AQ_NIC_H
#define AQ_NIC_H

#include "aq_common.h"
#include "aq_rss.h"
#include "aq_hw.h"

#include <linux/semaphore.h>
#include <linux/workqueue.h>

struct aq_ring_s;
struct aq_hw_ops;
struct aq_fw_s;
struct aq_vec_s;
struct aq_ptp_s;

struct aq_nic_cfg_s {
	const struct aq_hw_caps_s *aq_hw_caps;
	u64 features;
	u32 rxds;		/* rx ring size, descriptors # */
	u32 txds;		/* tx ring size, descriptors # */
	u32 vecs;		/* allocated rx/tx vectors */
	u32 link_irq_vec;
	u32 irq_type;
	u32 itr;
	u16 rx_itr;
	u16 tx_itr;
	u32 rxpageorder;
	u32 num_rss_queues;
	u32 mtu;
	u32 flow_control;
	u32 link_speed_msk;
	u32 wol;
	bool is_vlan_rx_strip;
	bool is_vlan_tx_insert;
	u16 is_mc_list_enabled;
	u16 mc_list_count;
	/* Bitmask of currently assigned vlan filters from linux */
	unsigned long active_vlans[BITS_TO_LONGS(VLAN_N_VID)];
	bool is_autoneg;
	bool is_polling;
	bool is_rss;
	bool is_lro;
	u32 priv_flags;
	u8  tcs;
	struct aq_rss_parameters aq_rss;
	u32 eee_speeds;
	u8 force_host_boot;
	u16 fw_did;
	u32 fw_sid;
	const struct firmware *fw_image;
};

#define AQ_NIC_FLAG_STARTED     0x00000004U
#define AQ_NIC_FLAG_STOPPING    0x00000008U
#define AQ_NIC_FLAG_RESETTING   0x00000010U
#define AQ_NIC_FLAG_CLOSING     0x00000020U
#define AQ_NIC_PTP_AVAILABLE    0x01000000U
#define AQ_NIC_PTP_DPATH_UP     0x02000000U
#define AQ_NIC_LINK_DOWN        0x04000000U
#define AQ_NIC_FLAG_ERR_UNPLUG  0x40000000U
#define AQ_NIC_FLAG_ERR_HW      0x80000000U

#define AQ_NIC_QUIRK_BAD_PTP BIT(0)

#ifdef PCI_DEBUG
#define AQ_NIC_PCI_RESOURCE_BUSY 0x00800000U
#endif
#define AQ_NIC_WOL_ENABLED           BIT(0)

#define AQ_NIC_TCVEC2RING(_NIC_, _TC_, _VEC_) \
	((_TC_) * AQ_CFG_TCS_MAX + (_VEC_))

#define aq_nic_print(aq_nic, level, type, args...) \
	netif_level(level, (aq_nic), type, (aq_nic)->ndev, ##args)

#define AQ_NIC_MAX	32

struct aq_hw_rx_fl2 {
	struct aq_rx_filter_vlan aq_vlans[HW_ATL_VLAN_MAX_FILTERS];
};

struct aq_hw_rx_fl3l4 {
	u8   active_ipv4;
	u8   active_ipv6:2;
	bool is_ipv6;
};

struct aq_hw_rx_fltrs_s {
	struct hlist_head     filter_list;
	u16                   active_filters;
	struct aq_hw_rx_fl2   fl2;
	struct aq_hw_rx_fl3l4 fl3l4;
};

struct aq_nic_s {
	atomic_t flags;
	u32 msg_enable;
	struct aq_vec_s *aq_vec[AQ_CFG_VECS_MAX];
	struct aq_ring_s *aq_ring_tx[AQ_CFG_VECS_MAX * AQ_CFG_TCS_MAX];
	struct aq_hw_s *aq_hw;
	struct net_device *ndev;
	unsigned int aq_vecs;
	unsigned int packet_filter;
	unsigned int power_state;
	u8 port;
	const struct aq_hw_ops *aq_hw_ops;
	const struct aq_fw_ops *aq_fw_ops;
	struct aq_nic_cfg_s aq_nic_cfg;
	struct timer_list polling_timer;
	struct aq_hw_link_status_s link_status;
	struct {
		u32 count;
		u8 ar[AQ_HW_MULTICAST_ADDRESS_MAX][ETH_ALEN];
	} mc_list;
	/* Bitmask of currently assigned vlans from linux */
	unsigned long active_vlans[BITS_TO_LONGS(VLAN_N_VID)];

	struct pci_dev *pdev;
	unsigned int msix_entry_mask;
	u32 irqvecs;
#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 7, 0)
	unsigned int irq_type;
	struct msix_entry msix_entry[AQ_CFG_PCI_FUNC_MSIX_IRQS];
#endif
	struct mutex fwreq_mutex;

	struct timer_list service_timer;
	struct work_struct service_task;

	/* PTP support */
	struct aq_ptp_s *aq_ptp;
	struct aq_hw_rx_fltrs_s aq_hw_rx_fltrs;
	struct work_struct link_update_task;
	u32 dump_flag;
};

static inline struct device *aq_nic_get_dev(struct aq_nic_s *self)
{
	return self->ndev->dev.parent;
}

extern unsigned int aq_rx_refill_thres;

void aq_nic_ndev_init(struct aq_nic_s *self);
struct aq_nic_s *aq_nic_alloc_hot(struct net_device *ndev);
void aq_nic_set_tx_ring(struct aq_nic_s *self, unsigned int idx,
			struct aq_ring_s *ring);
struct net_device *aq_nic_get_ndev(struct aq_nic_s *self);
int aq_nic_init(struct aq_nic_s *self);
void aq_nic_cfg_start(struct aq_nic_s *self);
int aq_nic_ndev_register(struct aq_nic_s *self);
void aq_nic_ndev_free(struct aq_nic_s *self);
int aq_nic_start(struct aq_nic_s *self);
int aq_nic_xmit(struct aq_nic_s *self, struct sk_buff *skb);
int aq_nic_get_regs(struct aq_nic_s *self, struct ethtool_regs *regs, void *p);
int aq_nic_get_regs_count(struct aq_nic_s *self);
void aq_nic_get_stats(struct aq_nic_s *self, u64 *data);
int aq_nic_stop(struct aq_nic_s *self);
void aq_nic_deinit(struct aq_nic_s *self);
void aq_nic_free_hot_resources(struct aq_nic_s *self);
void aq_nic_free_vectors(struct aq_nic_s *self);
int aq_nic_set_mtu(struct aq_nic_s *self, int new_mtu);
int aq_nic_set_mac(struct aq_nic_s *self, struct net_device *ndev);
int aq_nic_set_packet_filter(struct aq_nic_s *self, unsigned int flags);
int aq_nic_set_multicast_list(struct aq_nic_s *self, struct net_device *ndev);
unsigned int aq_nic_get_link_speed(struct aq_nic_s *self);
unsigned int aq_nic_map_skb(struct aq_nic_s *self, struct sk_buff *skb,
		struct aq_ring_s *ring);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4, 6, 0)
void aq_nic_get_link_ksettings(struct aq_nic_s *self,
			       struct ethtool_link_ksettings *cmd);
int aq_nic_set_link_ksettings(struct aq_nic_s *self,
			      const struct ethtool_link_ksettings *cmd);
#else
void aq_nic_get_link_settings(struct aq_nic_s *self, struct ethtool_cmd *cmd);
int aq_nic_set_link_settings(struct aq_nic_s *self, struct ethtool_cmd *cmd);
#endif
struct aq_nic_cfg_s *aq_nic_get_cfg(struct aq_nic_s *self);
u32 aq_nic_get_fw_version(struct aq_nic_s *self);
int aq_nic_set_loopback(struct aq_nic_s *self);
int aq_nic_set_downshift(struct aq_nic_s *self);
int aq_nic_change_pm_state(struct aq_nic_s *self, pm_message_t *pm_msg);
int aq_nic_update_interrupt_moderation_settings(struct aq_nic_s *self);
void aq_nic_shutdown(struct aq_nic_s *self);
void aq_nic_parse_parameters(struct aq_nic_s *self, unsigned int nic_id);
void aq_nic_request_firmware(struct aq_nic_s *self);
#endif /* AQ_NIC_H */

/*
 * Copyright (C) 2019 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#define pr_fmt(fmt) "sipa_eth: " fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/udp.h>
#include <linux/if_arp.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/of_device.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <net/tcp.h>
#include <net/udp.h>
#include <net/ip.h>
#include <net/ipv6.h>
#include <net/ip6_checksum.h>
#include "sipa_eth.h"

/* Device status */
#define DEV_ON 1
#define DEV_OFF 0

#define SIPA_ETH_NAPI_WEIGHT 64
#define SIPA_ETH_IFACE_PREF "sipa_eth"
#define SIPA_ETH_VPCIE_PREF "vpcie"
#define SIPA_ETH_VPCIE_IDX 8

static unsigned long queue_lock_flags;
static spinlock_t queue_lock; /* spin-lock for queue status protection */
static struct dentry *root;
static int sipa_eth_debugfs_mknod(void *root, void *data);
static void sipa_eth_rx_handler (void *priv);
static u64 gro_enable;

static inline void sipa_eth_dt_stats_init(struct sipa_eth_dtrans_stats *stats)
{
	memset(stats, 0, sizeof(*stats));
}

static inline void sipa_eth_rx_stats_update(
			struct sipa_eth_dtrans_stats *stats, u32 len)
{
	stats->rx_sum += len;
	stats->rx_cnt++;
}

static inline void sipa_eth_tx_stats_update(
			struct sipa_eth_dtrans_stats *stats, u32 len)
{
	stats->tx_sum += len;
	stats->tx_cnt++;
}

static void sipa_eth_rx_csum(struct sk_buff *skb, unsigned int real_len)
{
	struct iphdr *iph;
	struct ipv6hdr *ipv6h;
	bool csum_ready = false;

	if (!(ntohs(skb->protocol) == ETH_P_IP ||
	      ntohs(skb->protocol) == ETH_P_IPV6))
		return;

	/*
	 * Downlink skb with csum 0, we need the IP stack help to
	 * calculate csum
	 */
	if (!skb->csum) {
		skb->ip_summed = CHECKSUM_NONE;
		return;
	}

	switch (ntohs(skb->protocol)) {
	case ETH_P_IP:
		iph = ip_hdr(skb);
		if (iph->protocol == IPPROTO_TCP) {
			if (!tcp_v4_check(real_len - ip_hdrlen(skb),
					  iph->saddr, iph->daddr,
					  skb->csum))
				csum_ready = true;
			else
				pr_debug("ipv4 rx tcp chechsum fail\n");
		} else if (iph->protocol == IPPROTO_UDP) {
			if (!udp_v4_check(real_len - ip_hdrlen(skb),
					  iph->saddr, iph->daddr,
					  skb->csum))
				csum_ready = true;
			else
				pr_debug("ipv4 rx udp chechsum fail\n");
		}
		break;
	case ETH_P_IPV6:
		ipv6h = ipv6_hdr(skb);
		if (ipv6_ext_hdr(ipv6h->nexthdr)) {
			skb->ip_summed = CHECKSUM_NONE;
			return;
		}

		if (ipv6h->nexthdr == NEXTHDR_TCP) {
			if (!tcp_v6_check(htons(ipv6h->payload_len),
					  &ipv6h->saddr, &ipv6h->daddr,
					  skb->csum))
				csum_ready = true;
			else
				pr_debug("ipv6 rx tcp chechsum fail\n");
		} else if (ipv6h->nexthdr == NEXTHDR_UDP) {
			if (!udp_v6_check(htons(ipv6h->payload_len),
					  &ipv6h->saddr, &ipv6h->daddr,
					  skb->csum))
				csum_ready = true;
			else
				pr_debug("ipv6 rx tcp chechsum fail\n");
		}
		break;
	}

	if (csum_ready)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	else
		skb->ip_summed = CHECKSUM_NONE;
}

static void sipa_eth_prepare_skb(struct SIPA_ETH *sipa_eth, struct sk_buff *skb)
{
	struct iphdr *iph;
	struct ipv6hdr *ipv6h;
	struct ethhdr *peth;
	struct net_device *dev;
	struct sipa_eth_init_data *pdata = sipa_eth->pdata;
	unsigned int real_len = 0;
	unsigned int payload_len;
	bool ip_arp = true;
	bool v4v6 = false;

	dev = sipa_eth->netdev;

	if (!strncmp(dev->name, SIPA_ETH_VPCIE_PREF, strlen(SIPA_ETH_VPCIE_PREF))) {
		skb->protocol = eth_type_trans(skb, dev);
		skb_reset_network_header(skb);

		/* It is a workaround for asic design defect,
		 * the skb length is fixed to 1600 bytes received from IPA,
		 * so we have to figure out the real len for each pkt.
		 * Currently we support v4,v6,arp protocols only.
		 * Vpcie0 has type APHDR_ETHER, so we need examine arp.
		 */
		switch (ntohs(skb->protocol)) {
		case ETH_P_IP:
			iph = ip_hdr(skb);
			real_len = ntohs(iph->tot_len);
			break;
		case ETH_P_IPV6:
			ipv6h = ipv6_hdr(skb);
			payload_len = ntohs(ipv6h->payload_len);
			real_len = payload_len + sizeof(struct ipv6hdr);
			break;
		case ETH_P_ARP:
			real_len = arp_hdr_len(dev);
			break;
		default:
			ip_arp = false;
			pr_info("skb %p, vpcie just support v4/v6/arp\n", skb);
			break;
		}

		if (ip_arp)
			skb_trim(skb, real_len);

		goto out;
	}
	/*
	 * sipa_eth is rawip
	 * The purpose of adding a fake mac header is
	 * to prevent a "out-of order" issue
	 * when doing napi_gro_receive.
	 *
	 * On ORCA CPE, ASIC has set a 14byte offset
	 * in a skb for mac header,
	 * but the content of this mac header is not initialized,
	 * so we need to fulfill this offset with a fake mac header.
	 *
	 * On Roc1+Orca, a skb arrives at sipa_eth
	 * has no mac header or a offset.
	 * But it has a 64 byte header room,
	 * We have to take advantage of the 64-byte header room,
	 * because the information in the header room
	 * is no longer useful for IP layer.
	 */
	if (pdata->mac_h) {
		skb_reset_mac_header(skb);
		peth = (struct ethhdr *)skb->data;
	} else {
		peth = (struct ethhdr *)skb_push(skb, ETH_HLEN);
		skb_reset_mac_header(skb);
	}
	ether_addr_copy(peth->h_source, "12345");
	ether_addr_copy(peth->h_dest, "54321");

	skb_set_network_header(skb, ETH_HLEN);
	iph = ip_hdr(skb);
	if (iph->version == 4) {
		skb->protocol = htons(ETH_P_IP);
		real_len = ntohs(iph->tot_len);
		v4v6 = true;
	} else {
		ipv6h = ipv6_hdr(skb);
		if (ipv6h->version == 6) {
			skb->protocol = htons(ETH_P_IPV6);
			payload_len = ntohs(ipv6h->payload_len);
			real_len = payload_len + sizeof(struct ipv6hdr);
			v4v6 = true;
		} else {
			pr_warn("skb %p is neither v4 nor v6\n", skb);
		}
	}
	sipa_eth_rx_csum(skb, real_len);

	peth->h_proto = skb->protocol;
	skb_pull_inline(skb, ETH_HLEN);

	/* resize the skb->len to a real one */
	if (v4v6)
		skb_trim(skb, real_len);

out:
	skb->dev = dev;
}

static int sipa_eth_rx(struct SIPA_ETH *sipa_eth, int budget)
{
	struct sk_buff *skb;
	struct net_device *dev;
	struct sipa_eth_dtrans_stats *dt_stats;
	int skb_cnt = 0;
	int ret;

	dt_stats = &sipa_eth->dt_stats;

	if (!sipa_eth) {
		pr_err("no sipa_eth device\n");
		return -EINVAL;
	}

	dev = sipa_eth->netdev;
	atomic_set(&sipa_eth->rx_evt, 0);
	while (skb_cnt < budget) {
		ret = sipa_nic_rx(sipa_eth->nic_id, &skb);

		if (ret) {
			switch (ret) {
			case -ENODEV:
				pr_err("fail to find dev");
				sipa_eth->stats.rx_errors++;
				dt_stats->rx_fail++;
				break;
			case -ENODATA:
				atomic_set(&sipa_eth->rx_busy, 0);
				break;
			}
			break;
		}

		if (!skb) {
			pr_err("recv skb is null\n");
			return -EINVAL;
		}

		sipa_eth_prepare_skb(sipa_eth, skb);

		sipa_eth->stats.rx_packets++;
		sipa_eth->stats.rx_bytes += skb->len;
		sipa_eth_rx_stats_update(dt_stats, skb->len);

		if (gro_enable)
			napi_gro_receive(&sipa_eth->napi, skb);
		else
			netif_receive_skb(skb);

		skb_cnt++;
	}

	return skb_cnt;
}

static int sipa_eth_rx_poll_handler(struct napi_struct *napi, int budget)
{
	struct SIPA_ETH *sipa_eth = container_of(napi, struct SIPA_ETH, napi);
	int tmp = 0, pkts;

	/* If the number of pkt is more than weight(64),
	 * we cannot read them all with a single poll.
	 * When the return value of poll func equals to weight(64),
	 * napi structure invokes the poll func one more time by
	 * __raise_softirq_irqoff.(See napi_poll for details)
	 * So do not do napi_complete in that case.
	 */
READ_AGAIN:
	/* For example:
	 * pkts = 60, tmp = 60, budget = 4
	 * if rx_evt is true, we goto READ_AGAIN,
	 * pkts = 4, tmp = 64, budget = 0,
	 * then we goto out, return 64 to napi,
	 * In that case, we force napi to do polling again.
	 */
	pkts = sipa_eth_rx(sipa_eth, budget);
	tmp += pkts;
	budget -= pkts;
	/*
	 * If budget is 0 here, means we has not finished reading yet,
	 * so we should return a weight-number(64) to napi to ask it
	 * do another polling.
	 */
	if (!budget)
		goto out;

	/* Due to a cuncurrency issue, we have to do napi_complete
	 * cautiously. If a socket is in the process of napi polling,
	 * a SIPA_RECEIVE is arriving to trigger another socket to do receiving,
	 * we must record it because it will be blocked by rx_busy
	 * at the first beginning.
	 * Since this SIPA_RECEIVE notification is a one-shot behaviour
	 * in sipa_nic. if we chose to ignore this event, we may lose
	 * the chance to receive forever.
	 */
	if (atomic_read(&sipa_eth->rx_evt))
		goto READ_AGAIN;

	/* If the number of budget is more than 0, it means the pkts
	 * we received is smaller than napi weight(64).
	 * Then we are okay to do napi_complete.
	 */
	if (budget) {
		napi_complete(napi);
		/* Test in a lab,  ten threads of TCP streams,
		 * TPUT reaches to 1Gbps, another edge case occurs,
		 * rx_busy might be 0, and rx_evt might be 1,
		 * after we do napi_complete.
		 * So do rx_handler manually to prevent
		 * sipa_eth from stopping receiving pkts.
		 */
		if (atomic_read(&sipa_eth->rx_evt) || atomic_read(&sipa_eth->rx_busy)) {
			pr_debug("rx evt recv after napi complete");
			atomic_set(&sipa_eth->rx_evt, 0);
			napi_schedule(&sipa_eth->napi);
		}
	}

out:
	return tmp;
}

static void sipa_eth_rx_handler (void *priv)
{
	struct SIPA_ETH *sipa_eth = (struct SIPA_ETH *)priv;

	if (!sipa_eth) {
		pr_err("data is NULL\n");
		return;
	}

	if (!atomic_cmpxchg(&sipa_eth->rx_busy, 0, 1)) {
		atomic_set(&sipa_eth->rx_evt, 0);
		napi_schedule(&sipa_eth->napi);
		/* Trigger a NET_RX_SOFTIRQ softirq directly,
		 * or there will be a delay
		 */
		raise_softirq(NET_RX_SOFTIRQ);
	}
}

static void sipa_eth_flowctrl_handler(void *priv, int flowctrl)
{
	struct SIPA_ETH *sipa_eth = (struct SIPA_ETH *)priv;
	struct net_device *dev = sipa_eth->netdev;

	if (flowctrl) {
		netif_stop_queue(dev);
	} else if (netif_queue_stopped(dev)) {
		spin_lock_irqsave(&queue_lock, queue_lock_flags);
		netif_wake_queue(dev);
		spin_unlock_irqrestore(&queue_lock, queue_lock_flags);
		pr_info("wakeup queue on dev %s\n", dev->name);
	}
}

static void sipa_eth_notify_cb(void *priv, enum sipa_evt_type evt,
			       unsigned long data)
{
	struct SIPA_ETH *sipa_eth = (struct SIPA_ETH *)priv;

	switch (evt) {
	case SIPA_RECEIVE:
		pr_debug("dev %s recv SIPA_RECEIVE\n", sipa_eth->netdev->name);
		atomic_set(&sipa_eth->rx_evt, 1);
		sipa_eth_rx_handler(priv);
		break;
	case SIPA_LEAVE_FLOWCTRL:
		pr_info("dev %s SIPA LEAVE FLOWCTRL\n", sipa_eth->netdev->name);
		sipa_eth_flowctrl_handler(priv, 0);
		break;
	case SIPA_ENTER_FLOWCTRL:
		pr_info("dev %s SIPA ENTER FLOWCTRL\n", sipa_eth->netdev->name);
		sipa_eth_flowctrl_handler(priv, 1);
		break;
	default:
		break;
	}
}

static int sipa_eth_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct SIPA_ETH *sipa_eth = netdev_priv(dev);
	struct sipa_eth_init_data *pdata = sipa_eth->pdata;
	struct sipa_eth_dtrans_stats *dt_stats;
	int ret = 0;
	int netid;
	struct ethhdr *peth;

	dt_stats = &sipa_eth->dt_stats;
	if (sipa_eth->state != DEV_ON) {
		pr_err("called when %s is down\n", dev->name);
		dt_stats->tx_fail++;
		netif_carrier_off(dev);
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	netid = pdata->netid;
	peth = eth_hdr(skb);
	/* eth is rawip, so pull 14 bytes */
	if (!pdata->mac_h)
		skb_pull_inline(skb, ETH_HLEN);

	/* calculate uplink ipv6 pkt with extension header */
	if (ntohs(peth->h_proto) == ETH_P_IPV6) {
		struct ipv6hdr *ipv6h = ipv6_hdr(skb);

		if (ipv6_ext_hdr(ipv6h->nexthdr)) {
			if (skb->ip_summed == CHECKSUM_PARTIAL)
				skb_checksum_help(skb);
		}
	}

	ret = sipa_nic_tx(sipa_eth->nic_id, pdata->term_type, netid, skb);
	if (unlikely(ret != 0)) {
		if (ret == -EAGAIN || ret == -EINPROGRESS) {
			/*
			 * resume skb, otherwise
			 * we may pull this skb ETH_HLEN-bytes twice
			 */
			if (!pdata->mac_h)
				skb_push(skb, ETH_HLEN);
			dt_stats->tx_fail++;
			sipa_eth->stats.tx_errors++;
			spin_lock_irqsave(&queue_lock, queue_lock_flags);
			if (sipa_nic_check_flow_ctrl(sipa_eth->nic_id)) {
				netif_stop_queue(dev);
				pr_info("stop queue on dev %s\n", dev->name);
			}
			spin_unlock_irqrestore(&queue_lock, queue_lock_flags);
			sipa_nic_trigger_flow_ctrl_work(sipa_eth->nic_id, ret);
			return NETDEV_TX_BUSY;
		}
		pr_err("fail to send skb, dev 0x%p eth 0x%p nic_id %d, ret %d\n",
		       dev, sipa_eth, sipa_eth->nic_id, ret);
		goto err;
	}

	/* update netdev statistics */
	sipa_eth->stats.tx_packets++;
	sipa_eth->stats.tx_bytes += skb->len;
	sipa_eth_tx_stats_update(dt_stats, skb->len);

	return NETDEV_TX_OK;

err:
	sipa_eth->netdev->stats.tx_dropped++;
	dev_kfree_skb_any(skb);
	return NETDEV_TX_OK;
}

/* Open interface */
static int sipa_eth_open(struct net_device *dev)
{
	struct SIPA_ETH *sipa_eth = netdev_priv(dev);
	struct sipa_eth_init_data *pdata = sipa_eth->pdata;
	int ret = 0;

	pr_info("dev 0x%p eth 0x%p open %s netid %d term %d mac_h %d\n",
		dev, sipa_eth, dev->name, pdata->netid, pdata->term_type,
		pdata->mac_h);
	ret = sipa_nic_open(
		pdata->term_type,
		pdata->netid,
		sipa_eth_notify_cb,
		(void *)sipa_eth);

	if (ret < 0)
		return -EINVAL;

	sipa_eth->nic_id = ret;
	sipa_eth->state = DEV_ON;

	sipa_eth_dt_stats_init(&sipa_eth->dt_stats);
	memset(&sipa_eth->stats, 0, sizeof(sipa_eth->stats));

	if (!netif_carrier_ok(sipa_eth->netdev)) {
		pr_info("set netif_carrier_on\n");
		netif_carrier_on(sipa_eth->netdev);
	}

	atomic_set(&sipa_eth->rx_busy, 0);
	netif_start_queue(dev);
	napi_enable(&sipa_eth->napi);

	return 0;
}

/* Close interface */
static int sipa_eth_close(struct net_device *dev)
{
	struct SIPA_ETH *sipa_eth = netdev_priv(dev);

	pr_info("close %s!\n", dev->name);

	sipa_nic_close(sipa_eth->nic_id);
	sipa_eth->state = DEV_OFF;

	napi_disable(&sipa_eth->napi);
	netif_stop_queue(dev);

	return 0;
}

static struct net_device_stats *sipa_eth_get_stats(struct net_device *dev)
{
	struct SIPA_ETH *sipa_eth = netdev_priv(dev);

	return &sipa_eth->stats;
}

static const struct net_device_ops sipa_eth_ops = {
	.ndo_open = sipa_eth_open,
	.ndo_stop = sipa_eth_close,
	.ndo_start_xmit = sipa_eth_start_xmit,
	.ndo_get_stats = sipa_eth_get_stats,
};

static int sipa_eth_parse_dt(
	struct sipa_eth_init_data **init,
	struct device *dev)
{
	struct sipa_eth_init_data *pdata = NULL;
	struct device_node *np = dev->of_node;
	int ret;
	u32 udata, id;
	s32 sdata;

	if (!np)
		pr_err("dev of_node np is null\n");

	pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	id = of_alias_get_id(np, "eth");
	switch (id) {
	case 0 ... 7:
		snprintf(pdata->name, IFNAMSIZ, "%s%d",
			 SIPA_ETH_IFACE_PREF, id);
		break;
	case 8 ... 11:
		snprintf(pdata->name, IFNAMSIZ, "%s%d",
			 SIPA_ETH_VPCIE_PREF, id - SIPA_ETH_VPCIE_IDX);
		break;
	default:
		pr_err("wrong alias id from dts, id %d\n", id);
		return -EINVAL;
	}

	ret = of_property_read_s32(np, "sprd,netid", &sdata);
	if (ret) {
		pr_err("read sprd,netid ret %d\n", ret);
		return ret;
	}
	/* dts reflect */
	pdata->netid = sdata - 1;

	ret = of_property_read_u32(np, "sprd,term-type", &udata);
	if (ret) {
		pr_err("read sprd,term-type ret %d\n", ret);
		return ret;
	}

	pdata->term_type = udata;

	pdata->mac_h = of_property_read_bool(np, "sprd,mac-header");

	*init = pdata;
	pr_debug("after dt parse, name %s netid %d term-type %d mac_h %d\n",
		 pdata->name, pdata->netid, pdata->term_type, pdata->mac_h);
	return 0;
}

static void s_setup(struct net_device *dev)
{
	ether_setup(dev);
	/*
	 * avoid mdns to be send
	 * also disable arp
	 */
	if (!strncmp(dev->name,
		     SIPA_ETH_IFACE_PREF,
		     strlen(SIPA_ETH_IFACE_PREF))) {
		dev->flags |= IFF_NOARP;
		dev->flags &= ~(IFF_BROADCAST | IFF_MULTICAST);
	}
}

static int sipa_eth_probe(struct platform_device *pdev)
{
	struct sipa_eth_init_data *pdata = pdev->dev.platform_data;
	struct net_device *netdev;
	struct SIPA_ETH *sipa_eth;
	char ifname[IFNAMSIZ];
	int ret;

	if (pdev->dev.of_node && !pdata) {
		ret = sipa_eth_parse_dt(&pdata, &pdev->dev);
		if (ret) {
			pr_err("failed to parse device tree, ret=%d\n", ret);
			return ret;
		}
		pdev->dev.platform_data = pdata;
	}

	strlcpy(ifname, pdata->name, IFNAMSIZ);
	netdev = alloc_netdev(
		sizeof(struct SIPA_ETH),
		ifname,
		NET_NAME_UNKNOWN,
		s_setup);

	if (!netdev) {
		pr_err("alloc_netdev() failed.\n");
		return -ENOMEM;
	}

	/*
	 * If net_device's type is ARPHRD_ETHER, the ipv6 interface identifier
	 * specified by the network will be covered by addrconf_ifid_eui48,
	 * this will casue ipv6 fail in some test environment.
	 * So set the sipa_eth net_device's type to ARPHRD_RAWIP here.
	 */
	if (!strncmp(netdev->name, SIPA_ETH_IFACE_PREF, strlen(SIPA_ETH_IFACE_PREF)))
		netdev->type = ARPHRD_RAWIP;
	else
		netdev->type = ARPHRD_ETHER;

	sipa_eth = netdev_priv(netdev);
	sipa_eth_dt_stats_init(&sipa_eth->dt_stats);
	sipa_eth->netdev = netdev;
	sipa_eth->pdata = pdata;
	atomic_set(&sipa_eth->rx_busy, 0);
	atomic_set(&sipa_eth->rx_evt, 0);
	netdev->netdev_ops = &sipa_eth_ops;
	netdev->watchdog_timeo = 1 * HZ;
	netdev->irq = 0;
	netdev->dma = 0;

	random_ether_addr(netdev->dev_addr);

	netif_napi_add(netdev,
		       &sipa_eth->napi,
		       sipa_eth_rx_poll_handler,
		       SIPA_ETH_NAPI_WEIGHT);
	netdev->hw_features |= NETIF_F_RXCSUM | NETIF_F_IP_CSUM |
		NETIF_F_IPV6_CSUM;
	netdev->features = netdev->hw_features;

	/* Register new Ethernet interface */
	ret = register_netdev(netdev);
	if (ret) {
		pr_err("register_netdev() failed (%d)\n", ret);
		netif_napi_del(&sipa_eth->napi);
		free_netdev(netdev);
		return ret;
	}

	sipa_eth->state = DEV_OFF;
	/* Set link as disconnected */
	netif_carrier_off(netdev);
	platform_set_drvdata(pdev, sipa_eth);
	sipa_eth_debugfs_mknod(root, (void *)sipa_eth);
	return 0;
}

/* Cleanup Ethernet device driver. */
static int sipa_eth_remove(struct platform_device *pdev)
{
	struct SIPA_ETH *sipa_eth = platform_get_drvdata(pdev);

	netif_napi_del(&sipa_eth->napi);
	unregister_netdev(sipa_eth->netdev);
	free_netdev(sipa_eth->netdev);
	platform_set_drvdata(pdev, NULL);

	return 0;
}

static const struct of_device_id sipa_eth_match_table[] = {
	{ .compatible = "sprd,sipa_eth"},
	{ }
};

static struct platform_driver sipa_eth_driver = {
	.probe = sipa_eth_probe,
	.remove = sipa_eth_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name = SIPA_ETH_IFACE_PREF,
		.of_match_table = sipa_eth_match_table
	}
};

static int sipa_eth_debug_show(struct seq_file *m, void *v)
{
	struct SIPA_ETH *sipa_eth = (struct SIPA_ETH *)(m->private);
	struct sipa_eth_dtrans_stats *stats;
	struct sipa_eth_init_data *pdata;

	if (!sipa_eth) {
		pr_err("invalid data, sipa_eth is NULL\n");
		return -EINVAL;
	}
	pdata = sipa_eth->pdata;
	stats = &sipa_eth->dt_stats;

	seq_puts(m, "*************************************************\n");
	seq_printf(m, "DEVICE: %s, term_type %d, netid %d, state %s mac_h %d\n",
		   pdata->name, pdata->term_type, pdata->netid,
		   sipa_eth->state == DEV_ON ? "UP" : "DOWN", pdata->mac_h);
	seq_puts(m, "\nRX statistics:\n");
	seq_printf(m, "rx_sum=%u, rx_cnt=%u\n",
		   stats->rx_sum,
		   stats->rx_cnt);
	seq_printf(m, "rx_fail=%u\n",
		   stats->rx_fail);

	seq_printf(m, "rx_busy=%d\n", atomic_read(&sipa_eth->rx_busy));
	seq_printf(m, "rx_evt=%d\n", atomic_read(&sipa_eth->rx_evt));

	seq_puts(m, "\nTX statistics:\n");
	seq_printf(m, "tx_sum=%u, tx_cnt=%u\n",
		   stats->tx_sum,
		   stats->tx_cnt);
	seq_printf(m, "tx_fail=%u\n",
		   stats->tx_fail);

	seq_printf(m, "flowctl=%s\n",
		   netif_queue_stopped(sipa_eth->netdev) ? "true" : "false");
	seq_puts(m, "*************************************************\n");

	return 0;
}

static int sipa_eth_debug_open(struct inode *inode, struct file *file)
{
	return single_open(file, sipa_eth_debug_show, inode->i_private);
}

static const struct file_operations sipa_eth_debug_fops = {
	.open = sipa_eth_debug_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int debugfs_gro_enable_get(void *data, u64 *val)
{
	*val = *(u64 *)data;
	return 0;
}

static int debugfs_gro_enable_set(void *data, u64 val)
{
	*(u64 *)data = val;
	return 0;
}

DEFINE_SIMPLE_ATTRIBUTE(fops_gro_enable,
			debugfs_gro_enable_get,
			debugfs_gro_enable_set,
			"%llu\n");

static int sipa_eth_debugfs_mknod(void *root, void *data)
{
	struct SIPA_ETH *sipa_eth = (struct SIPA_ETH *)data;
	struct dentry *subroot;

	if (!sipa_eth)
		return -ENODEV;

	if (!root)
		return -ENXIO;

	subroot = debugfs_create_dir(sipa_eth->netdev->name, (struct dentry *)root);
	if (!subroot)
		return -ENOMEM;

	debugfs_create_file("stats",
			    0444,
			    subroot,
			    data,
			    &sipa_eth_debug_fops);

	debugfs_create_file("gro_enable",
			    0600,
			    (struct dentry *)root,
			    &gro_enable,
			    &fops_gro_enable);

	return 0;
}

static void __init sipa_eth_debugfs_init(void)
{
	root = debugfs_create_dir(SIPA_ETH_IFACE_PREF, NULL);
	if (!root)
		pr_err("failed to create sipa_eth debugfs dir\n");
}

static int __init sipa_eth_init(void)
{
	sipa_eth_debugfs_init();
	spin_lock_init(&queue_lock);
	return platform_driver_register(&sipa_eth_driver);
}

static void __exit sipa_eth_exit(void)
{
	platform_driver_unregister(&sipa_eth_driver);
}

module_init(sipa_eth_init);
module_exit(sipa_eth_exit);

MODULE_AUTHOR("Wade.Shu");
MODULE_DESCRIPTION("Unisoc Ethernet device driver for IPA");
MODULE_LICENSE("GPL v2");

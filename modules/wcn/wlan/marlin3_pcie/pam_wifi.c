#ifdef ENABLE_PAM_WIFI
#include "pam_wifi_driver.h"
#include <linux/dma-direction.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>

struct pam_wifi_sender_device pam_wifi_dl_fifo_sender_dev = {
		{
			{
				.fifo_name = "pam_wifi_dl",
				.pam_wifi_term_id = pam_wifi_term_dl,
				.pam_wifi_term_id_recv = SIPA_FIFO_WIFI_DL,
				.state = 0,
				.pending = 0,
				.is_dma = 1,
				.cur = IPA_MAP_CP,
				.dst = IPA_WI_AP0_ROC_AP,
			/*.dl_free_fifo_reg_base = PSEL_DL_FREE,
				.dl_tx_type1_fifo_reg_base = PSEL_DL_TYPE1,
				.dl_tx_type2_fifo_reg_base = PSEL_DL_TYPE2,
				.dl_tx_type3_fifo_reg_base = PSEL_DL_TYPE3,
				.dl_tx_type4_fifo_reg_base = PSEL_DL_TYPE4,*/
				.dl_free_fifo_reg_base = 0,
				.dl_tx_type1_fifo_reg_base = 0,
				.dl_tx_type2_fifo_reg_base = 0,
				.dl_tx_type3_fifo_reg_base = 0,
				.dl_tx_type4_fifo_reg_base = 0,
			/*rx_fifo*/
			{
				.depth = PAM_WIFI_DL_RX_FIFO_DEPTH,
				.wr = 0,
				.rd = 0,
				.fifo_base_addr_l = PAM_WIFI_DL_RX_FIFO_ADDRL,
				.fifo_base_addr_h = PAM_WIFI_DL_RX_FIFO_ADDRH,
			},
			/*tx_fifo for type1*/
			{
				.depth = PAM_WIFI_DL_TX_FIFO_DEPTH,
				.wr = 0,
				.rd = 0,
				.fifo_base_addr_l = PAM_WIFI_DL_TX_FIFO_ADDRL,
				.fifo_base_addr_h = PAM_WIFI_DL_TX_FIFO_ADDRH,
			},
			/*tx_fifo for type2*/
			{
				.depth = PAM_WIFI_DL_TX_FIFO_DEPTH,
				.wr = 0,
				.rd = 0,
				.fifo_base_addr_l = PAM_WIFI_DL_TX_FIFO_ADDRL,
				.fifo_base_addr_h = PAM_WIFI_DL_TX_FIFO_ADDRH,
			},
			/*tx_fifo for type3*/
			{
				.depth = PAM_WIFI_DL_TX_FIFO_DEPTH,
				.wr = 0,
				.rd = 0,
				.fifo_base_addr_l = PAM_WIFI_DL_TX_FIFO_ADDRL,
				.fifo_base_addr_h = PAM_WIFI_DL_TX_FIFO_ADDRH,
			},
			/*tx_fifo for type4*/
			{
				.depth = PAM_WIFI_DL_TX_FIFO_DEPTH,
				.wr = 0,
				.rd = 0,
				.fifo_base_addr_l = PAM_WIFI_DL_TX_FIFO_ADDRL,
				.fifo_base_addr_h = PAM_WIFI_DL_TX_FIFO_ADDRH,
			},
			},
		},
		{
			.open = NULL,
			.close = NULL,
			.set_rx_depth = NULL,
			.set_tx_depth = NULL,
			.set_interrupt_timeout		= NULL,
			.set_interrupt_threshold	= NULL,
			.send						= NULL,
		},
			.ops = NULL,
};

struct pam_wifi_receiver_device pam_wifi_ul_fifo_receiver_dev = {
	{
			{
				.fifo_name = "pam_wifi_ul",
				.pam_wifi_term_id = pam_wifi_term_ul,
				.pam_wifi_term_id_recv = SIPA_FIFO_WIFI_UL,
				.state = 0,
				.pending = 0,
				.is_dma = 1,
				.cur = IPA_MAP_CP,
				.dst = IPA_WI_AP0_ROC_AP,

				//.fifo_reg_base = PSEL_UL,
				.fifo_reg_base = 0,
			/*rx_fifo*/
			{
				.depth = PAM_WIFI_UL_RX_FIFO_DEPTH,
				.wr = 0,
				.rd = 0,
				.fifo_base_addr_l = PAM_WIFI_UL_RX_FIFO_ADDRL,
				.fifo_base_addr_h = PAM_WIFI_UL_RX_FIFO_ADDRH,
			},
			/*tx_fifo*/
			{
				.depth = PAM_WIFI_UL_TX_FIFO_DEPTH,
				.wr = 0,
				.rd = 0,
				.fifo_base_addr_l = PAM_WIFI_UL_TX_FIFO_ADDRL,
				.fifo_base_addr_h = PAM_WIFI_UL_TX_FIFO_ADDRH,
			},
		},
	},
	{
			.open = NULL,
			.close = NULL,
			.set_rx_depth = NULL,
			.set_tx_depth = NULL,
			.set_interrupt_timeout		= NULL,
			.set_interrupt_threshold	= NULL,
			.recv						= NULL,
	},
			.ops = NULL,
};

u8 term_pam_wifi_only_msdu_header[PAM_WIFI_DL_TX_FIFO_DEPTH * 16];

//u8 term_pam_wifi_miss_node_infor[PAM_WIFI_DL_TX_FIFO_DEPTH * 16];

u8 term_pam_wifi_inn_ul_data_buf[PAM_WIFI_UL_TX_FIFO_DEPTH][2048];



inline void  enable_ul_free_fifo(void)
{
	//*(volatile u32 *)REG_INT_EN |= BITINT_EN_UL_FREE;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 |= BITINT_EN_UL_FREE;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void enable_ul_fill_fifo(void)
{
	//*(volatile u32 *)REG_INT_EN |= BITINT_EN_UL_FILL;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 |= BITINT_EN_UL_FILL;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void enbale_dl_free_fifo(void)
{
	//*(volatile u32 *)REG_INT_EN |= BITINT_EN_DL_FREE;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 |= BITINT_EN_DL_FREE;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void enbale_dl_fill_fifo_type1(void)
{
	//*(volatile u32 *)REG_INT_EN |= BITINT_EN_DL_FILL_TYPE1;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 |= BITINT_EN_DL_FILL_TYPE1;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void enbale_dl_fill_fifo_type2(void)
{
	//*(volatile u32 *)REG_INT_EN |= BITINT_EN_DL_FILL_TYPE2;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 |= BITINT_EN_DL_FILL_TYPE2;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void enbale_dl_fill_fifo_type3(void)
{
	//*(volatile u32 *)REG_INT_EN |= BITINT_EN_DL_FILL_TYPE3;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 |= BITINT_EN_DL_FILL_TYPE3;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void enbale_dl_fill_fifo_type4(void)
{
	//*(volatile u32 *)REG_INT_EN |= BITINT_EN_DL_FILL_TYPE4;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 |= BITINT_EN_DL_FILL_TYPE4;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void enable_dl_miss(void)
{
	//*(volatile u32 *)REG_INT_EN |= BITINT_EN_DL_INDEX_MISS;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 |= BITINT_EN_DL_INDEX_MISS;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void disable_ul_free_fifo(void)
{
	//*(volatile u32 *)REG_INT_EN &= ~BITINT_EN_UL_FREE;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 &= ~BITINT_EN_UL_FREE;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void disable_ul_fill_fifo(void)
{
       //*(volatile u32 *)REG_INT_EN &= ~BITINT_EN_UL_FILL;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 &= ~BITINT_EN_UL_FILL;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void disable_dl_free_fifo(void)
{
	//*(volatile u32 *)REG_INT_EN &= ~BITINT_EN_DL_FREE;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 &= ~BITINT_EN_DL_FREE;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void disable_dl_fill_fifo_type1(void)
{
	//*(volatile u32 *)REG_INT_EN &= ~BITINT_EN_DL_FILL_TYPE1;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 &= ~BITINT_EN_DL_FILL_TYPE1;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void disable_dl_fill_fifo_type2(void)
{
	//*(volatile u32 *)REG_INT_EN &= ~BITINT_EN_DL_FILL_TYPE2;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 &= ~BITINT_EN_DL_FILL_TYPE2;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void disable_dl_fill_fifo_type3(void)
{
	//*(volatile u32 *)REG_INT_EN &= ~BITINT_EN_DL_FILL_TYPE3;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 &= ~BITINT_EN_DL_FILL_TYPE3;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void disable_dl_fill_fifo_type4(void)
{
	//*(volatile u32 *)REG_INT_EN &= ~BITINT_EN_DL_FILL_TYPE4;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 &= ~BITINT_EN_DL_FILL_TYPE4;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

inline void disable_dl_index_miss(void)
{
	//*(volatile u32 *)REG_INT_EN &= ~BITINT_EN_DL_INDEX_MISS;
	u32 value1 = readl_relaxed((void *)REG_INT_EN);
	value1 &= ~BITINT_EN_DL_INDEX_MISS;
	writel_relaxed(value1, (void *)REG_INT_EN);
}

static inline u32 pam_wifi_set_rx_fifo_total_depth(u64 fifo_base, u32 depth)
{
	u32 tmp;

	if (depth > 0xFFFF)
		return -1;
	/*else {
		tmp = (*((volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_DEPTH)));
		tmp &= 0x0000FFFF;
		tmp |= (depth << 16);
		*(volatile u32*)(fifo_base + PAMWIFI_COMMON_RX_FIFO_DEPTH) = tmp;
		if ((*(volatile u32 *)(fifo_base+ PAMWIFI_COMMON_RX_FIFO_DEPTH) & 0xFFFF0000l) == tmp)
			return 0;
		else return -1;
	}*/
	else {
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_DEPTH));
		tmp &= 0x0000FFFF;
		tmp |= (depth << 16);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_DEPTH));
	}
	return 1;
}

/*****************************************************************************
 * Description: set rx fifo address of iram.
 * Input:
 *   fifo_base: Need to set rx fifo address of the FIFO, the base
 *              address of the FIFO.
 *   addr_l: low 32 bit.
 *   addr_h: high 8 bit.
 * return:
 *   TRUE: update rx fifo address of iram successfully.
 *   FALSE: update rx fifo address of iram failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_set_rx_fifo_addr(u64 fifo_base, u32 addr_l, u32 addr_h)
{
	/**(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_ADDRL) = addr_l;
	*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_ADDRH) = addr_h;

	if ((*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_ADDRL)) == addr_l &&
			(*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_ADDRH)) == addr_h)
		return TRUE;
	else
		return FALSE;*/
	writel_relaxed(addr_l, (void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_ADDRL));
	writel_relaxed(addr_h, (void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_ADDRH));
	return 1;
}


/*****************************************************************************
 * Description: set tx fifo total depth.
 * Input:
 *   fifo_base: Need to set tx fifo empty status of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   TRUE: set tx fifo total depth successfully.
 *   FALSE: set tx fifo total_depth failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_set_tx_fifo_total_depth(u64 fifo_base, u32 depth)
{
	u32 tmp;

	if (depth > 0xFFFF)
		return FALSE;
	else {
		/*
		tmp = (*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_DEPTH));
		tmp &= 0x0000FFFF;
		tmp |= (depth << 16);
		*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_DEPTH) = tmp;
		if ((*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_DEPTH)) == tmp)
			return TRUE;
		else
			return FALSE;
		*/
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_DEPTH));
		tmp &= 0x0000FFFF;
		tmp |= (depth << 16);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_DEPTH));
	}
	return 1;
}

/*****************************************************************************
 * Description: get tx fifo filled depth.
 * Input:
 *   fifo_base: Need to get tx fifo filled depth of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   The tx fifo filled depth.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_get_tx_fifo_filled_depth(u64 fifo_base)
{
	//return (*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_DEPTH)) & 0x0000FFFF;
	return (readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_DEPTH))) & 0x0000FFFF;
}

/*****************************************************************************
 * Description: set tx fifo address of iram.
 * Input:
 *   fifo_base: Need to set tx fifo address of the FIFO, the base
 *              address of the FIFO.
 *   addr_l: low 32 bit.
 *   addr_h: high 8 bit.
 * return:
 *   TRUE: update tx fifo address of iram successfully.
 *   FALSE: update tx fifo address of iram failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_set_tx_fifo_addr(u64 fifo_base, u32 addr_l, u32 addr_h)
{
	/**(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_ADDRL) = addr_l;
	*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_ADDRH) = addr_h;

	if ((*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_ADDRL)) == addr_l &&
			(*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_ADDRH)) == addr_h)
		return TRUE;
	else
		return FALSE;*/
	writel_relaxed(addr_l, (void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_ADDRL));
	writel_relaxed(addr_h, (void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_ADDRH));
	return 1;
}

/*****************************************************************************
 * Description: Get current term number.
 * Input:
 *   fifo_base: Need to get current term number of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   Current term number.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_get_cur_term_num(u64 fifo_base)
{
	//return ((*(volatile u32 *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL)) & 0x0003E000) >> 13;
	return (readl_relaxed((void *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL))) & 0x0003E000 >> 13;
}

/*****************************************************************************
 * Description: Set current term number.
 * Input:
 *   fifo_base: Need to set current term number of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   TRUE: Set successfully.
 *   FALSE: Set failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_set_cur_term_num(u64 fifo_base, u32 num)
{
	u32 tmp = 0;

	if (num > 0x1F)
		return FALSE;
	else {
		/*tmp = *(volatile u32 *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL);
		tmp &= 0xFFFC1FFF;
		tmp |= (num << 13);
		*(volatile u32 *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL) = tmp;

		if ((((*(volatile u32 *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL))
				& 0x0003E000) >> 13) == num)
			return TRUE;
		else
			return FALSE;*/
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL));
		tmp &= 0xFFFC1FFF;
		tmp |= (num << 13);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL));
	}
	return 1;
}

/*****************************************************************************
 * Description: Get dst term number.
 * Input:
 *   fifo_base: Need to get dst term number of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   Dst term number.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_get_dst_term_num(u64 fifo_base)
{
	//return ((*(volatile u32 *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL)) & 0x00001F00) >> 8;
	return (readl_relaxed((void *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL))) & 0x00001F00 >> 8;
}

/*****************************************************************************
 * Description: Set dst term number.
 * Input:
 *   fifo_base: Need to set dst term number of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   TRUE: Set successfully.
 *   FALSE: Set failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_set_dst_term_num(u64 fifo_base, u32 num)
{
	u32 tmp = 0;

	if (num > 0x1F)
		return FALSE;
	else {
		/*tmp = *(volatile u32 *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL);
		tmp &= 0xFFFFE0FF;
		tmp |= (num << 8);
		*(volatile u32 *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL) = tmp;

		if ((((*(volatile u32 *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL))
				& 0x00001F00) >> 8) == num)
			return TRUE;
		else
			return FALSE;*/
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL));
		tmp &= 0xFFFFE0FF;
		tmp |= (num << 8);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_PERFETCH_FIFO_CTL));
	}
	return 1;
}

/*****************************************************************************
 * Description: Disable interrupt bit.
 * Input:
 *   fifo_base: Need to Disable interrupr bit of the FIFO, the base
 *              address of the FIFO.
 *   int_bit: The interrupt bit that need to disable.
 * return:
 *   TRUE: Disable successfully.
 *   FALSE: Disable failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_disable_int_bit(u64 fifo_base, u32 int_bit)
{
	u32 ret = 0;
    printk("%s\n", __func__);
	/* *((volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN)) &= (~int_bit);
	ret = (*(volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN)) & int_bit;*/
	ret = readl_relaxed((void *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN));
	ret &= (~int_bit);
	writel_relaxed(ret, (void *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN));
	ret = readl_relaxed((void *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN));
	ret &= int_bit;
	if (!ret) {
		ret = TRUE;
	} else {
		ret = FALSE;
		printk("Disable interrupt bit = 0x%x set failed!\n", int_bit);
	}

	return ret;
}

static u32 ipa_pkt_to_node(struct data_pkt_tag *pkt, u32 force_intr, struct sipa_node_description_tag *node)
{
	node->address	= (u64)(pkt->head_ptr) & 0xFFFFFFFFFFll;
	node->length	= pkt->data_len;
	node->offset	= (u16)(((u64)pkt->data_ptr - (u64)pkt->head_ptr) & 0x0FFF);
	node->net_id	= pkt->netid;
	node->src		= (pkt->src & 0x1F);
	node->dst		= (pkt->dst & 0x1F);
	node->prio		= (pkt->prio & 0x07);
	//node->bear_id	= (pkt->bear_id & 0x7F);
	if (force_intr)
		node->intr = 1;
	else
		node->intr = 0;
	node->indx = pkt->indx & 0x01;
	node->err_code	= pkt->err_code;

	return TRUE;
}

inline static u32 ipa_node_to_pkt(struct sipa_node_description_tag *node, struct data_pkt_tag *pkt)
{
	pkt->dst		= node->dst;
	pkt->head_ptr	= (u8 *)(u64)(node->address);
	pkt->data_ptr	= (u8 *)(u64)(node->address + node->offset);
	pkt->data_len	= node->length;
	pkt->netid		= node->net_id;
	pkt->src		= node->src;
	pkt->dst		= node->dst;
	pkt->prio		= node->prio;
	//pkt->bear_id	= node->bear_id;
	pkt->err_code	= node->err_code;
	pkt->total_len	= node->length + node->offset;

	return TRUE;
}

/*****************************************************************************
 * Description: get rx fifo full status.
 * Input:
 *   fifo_base: Need to get rx fifo full status of the FIFO, the base address
 *              of the FIFO.
 * return:
 *   1: rx fifo full.
 *   0: rx fifo not full.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_get_rx_fifo_full_status(u64 fifo_base)
{
	//return (*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_WR)) & 0x00000001;
	return (readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_WR))) & 0x00000001;
}

/*****************************************************************************
 * Description: get rx fifo total depth.
 * Input:
 *   fifo_base: Need to get total depth of the fifo, the base address of the
 *              FIFO.
 * return: The size of toal depth.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_get_rx_fifo_total_depth(u64 fifo_base)
{
	//return (*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_DEPTH) >> 16) & 0x0000FFFF;
	return (readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_DEPTH)) >> 16) & 0x0000FFFF;
}

/*****************************************************************************
 * Description: get rx fifo filled depth.
 * Input:
 *   fifo_base: Need to get filled depth of the FIFO, the base address of the
 *              FIFO.
 * return:
 *   TRUE: The size of rx filled depth
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_get_rx_fifo_filled_depth(u64 fifo_base)
{
	//return (*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_DEPTH)) & 0x0000FFFF;
	return (readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_DEPTH))) & 0x0000FFFF;
}



//change ?????
static void pam_wifi_init_receiver_rx_fifo_node(enum pam_wifi_term_id id, struct sipa_node_description_tag *node,
				u32 num)
{
	int i = 0;
	u8 (*buf)[BUFF_SIZE];

	switch (id) {
		case pam_wifi_term_ul:
			buf = term_pam_wifi_inn_ul_data_buf;
			break;
		default:
			buf = NULL;
			break;
	}

	printk("id = %d, buf addr = 0x%llx", id, (u64)buf);
	if (buf) {
		for (i = 0; i < num; i++) {
			(node + i)->address = (u64)(buf + i);
			(node + i)->offset	= HEADER_OFFSET;
		}
	}
}

/*****************************************************************************
 * Description: update rx fifo read pointer.
 * Input:
 *   fifo_base: Need to update rx fifo read pointer of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   TRUE: update rx fifo read pointer successfully,
 *   FALSE: update rx fifo read pointer failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_update_rx_fifo_rptr(u64 fifo_base, u32 rptr)
{
	u32 tmp = 0;

	if (rptr > 0xFFFF)
		return FALSE;
	else {
		/* tmp = *(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_RD);
		tmp &= 0x0000FFFF;
		tmp |= (rptr << 16);
		*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_RD) = tmp;
		if (((*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_RD)) >> 16)
				== rptr)
			return TRUE;
		else
			return FALSE; */
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_RD));
		tmp &= 0x0000FFFF;
		tmp |= (rptr << 16);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_RD));
	}
	return 1;
}

/*****************************************************************************
 * Description: update tx fifo read pointer.
 * Input:
 *   fifo_base: Need to update tx fifo read pointer of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   TRUE: update tx fifo read pointer successfully.
 *   FALSE: update tx fifo read pointer failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_update_tx_fifo_rptr(u64 fifo_base, u32 rptr)
{
	u32 tmp = 0;

	if (tmp > 0xFFFF)
		return FALSE;
	else {
		/*tmp = *(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD);
		tmp &= 0x0000FFFF;
		tmp |= (rptr << 16);
        printk("pam_wifi_phy_update_tx_fifo_rptr tmp = 0x%04x\n", tmp);
		*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD) = tmp;
		if (((*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD)) >> 16) == rptr)
			return TRUE;
		else
			return FALSE;*/
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD));
		tmp &= 0x0000FFFF;
		tmp |= (rptr << 16);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD));
	}
	return 1;
}

/*****************************************************************************
 * Description: get tx fifo empty status.
 * Input:
 *   fifo_base: Need to get tx fifo empty status of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   The empty status of tx fifo.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_get_tx_fifo_empty_status(u64 fifo_base)
{
	//return (*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x00000001;
	return (readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD))) & 0x00000001;
}

u32 pam_wifi_update_tx_fifo_wptr(u64 fifo_base, u32 wptr)
{
	u32 tmp = 0;

	if (tmp > 0xFFFF)
		return FALSE;
	else {
		/*tmp = *(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD);
		tmp &= 0x0000FFFF;
		tmp |= (rptr << 16);
        printk("pam_wifi_phy_update_tx_fifo_rptr tmp = 0x%04x\n", tmp);
		*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD) = tmp;
		if (((*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD)) >> 16) == rptr)
			return TRUE;
		else
			return FALSE;*/
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_WR));
		tmp &= 0x0000FFFF;
		tmp |= BIT_(1);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_WR));
		tmp |= (wptr << 16);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_WR));
		tmp &= ~ BIT_(1);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_WR));
	}
	return 1;
}

/*****************************************************************************
 * Description: update rx fifo write pointer.
 * Input:
 *   fifo_base: Need to update rx fifo write pointer of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   TRUE: update rx fifo write pointer successfully,
 *   FALSE: update rx fifo write pointer failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_update_rx_fifo_wptr(u64 fifo_base, u32 wptr)
{
	u32 tmp = 0;

	if (wptr > 0xFFFF)
		return FALSE;
	else {
		/*tmp = *(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_WR);
		tmp &= 0x0000FFFF;
		tmp |= (wptr << 16);
		*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_WR) = tmp;
		if (((*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_WR)) >> 16)
				== wptr)
			return TRUE;
		else
			return FALSE;*/
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_WR));
		tmp &= 0x0000FFFF;
		tmp |= (wptr << 16);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_COMMON_RX_FIFO_WR));
	}
	return 1;
}


u32 pam_wifi_fifo_sender_open(enum pam_wifi_term_id id, void *cookie)
{
	int i =0;
	u64 fifo_reg_base = 0;
	u32 dl_fifo_depth = 0;
	u32 dl_fifo_base_addr_l = 0;
	u32 dl_fifo_base_addr_h = 0;

	enum dl_fifo_type p_dl_fifo_type = dl_tx_fifo_type1;
	struct pam_wifi_sender *pam_wifi_term_sender = NULL;

	printk("%s,pam_wifi_fifo_sender_open!\n", __func__);

	for(i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("%s,cant find matched term id!\n", __func__);
		return false;
	}

	pam_wifi_term_sender = & (pam_wifi_dl_fifo_sender_dev.term_sender[i]);

	if (pam_wifi_term_sender->state == TRUE) {
		printk("%s, already opened!\n", __func__);
		return true;
	}

	/*.dl_free_fifo_reg_base = PSEL_DL_FREE,
		.dl_tx_type1_fifo_reg_base = PSEL_DL_TYPE1,
		.dl_tx_type2_fifo_reg_base = PSEL_DL_TYPE2,
		.dl_tx_type3_fifo_reg_base = PSEL_DL_TYPE3,
		.dl_tx_type4_fifo_reg_base = PSEL_DL_TYPE4,*/
	pam_wifi_term_sender->dl_free_fifo_reg_base = PSEL_DL_FREE;
	pam_wifi_term_sender->dl_tx_type1_fifo_reg_base = PSEL_DL_TYPE1;
	pam_wifi_term_sender->dl_tx_type2_fifo_reg_base = PSEL_DL_TYPE2;
	pam_wifi_term_sender->dl_tx_type3_fifo_reg_base = PSEL_DL_TYPE3;
	pam_wifi_term_sender->dl_tx_type4_fifo_reg_base = PSEL_DL_TYPE4;
    //*******************Set the Common FIFO RX Part*****************
	fifo_reg_base = pam_wifi_term_sender->dl_free_fifo_reg_base;
	dl_fifo_depth = pam_wifi_term_sender->dl_free_fifo.depth;
	dl_fifo_base_addr_l = pam_wifi_term_sender->dl_free_fifo.fifo_base_addr_l;
	dl_fifo_base_addr_h = pam_wifi_term_sender->dl_free_fifo.fifo_base_addr_h;

	pam_wifi_set_rx_fifo_total_depth(fifo_reg_base, dl_fifo_depth);
	pam_wifi_set_rx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);
	pam_wifi_update_rx_fifo_rptr(fifo_reg_base, 0);
	pam_wifi_update_rx_fifo_wptr(fifo_reg_base, 0);

	pam_wifi_term_sender->dl_free_fifo.rd = 0;
	pam_wifi_term_sender->dl_free_fifo.wr = 0;
    //*******************END Set the Common FIFO RX Part***************

    //*******************END Set the Common FIFO TX Part***************

	for(i=dl_fifo_free;i<(dl_tx_fifo_type4+1);i++)
	{
		p_dl_fifo_type = i;
		if(p_dl_fifo_type == dl_fifo_free)
		{
			fifo_reg_base = pam_wifi_term_sender->dl_free_fifo_reg_base;
			dl_fifo_depth = pam_wifi_term_sender->dl_free_fifo.depth;
			dl_fifo_base_addr_l = pam_wifi_term_sender->dl_free_fifo.fifo_base_addr_l;
			dl_fifo_base_addr_h = pam_wifi_term_sender->dl_free_fifo.fifo_base_addr_h;

#if 1
			if (pam_wifi_term_sender->pam_wifi_term_id != pam_wifi_term_dl)
			{
				pam_wifi_term_sender->tx_fifo_type1.wr = dl_fifo_depth;
			}
#endif
		}
		else if(p_dl_fifo_type == dl_tx_fifo_type1)
		{
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type1_fifo_reg_base;
			dl_fifo_depth = pam_wifi_term_sender->tx_fifo_type1.depth;
			dl_fifo_base_addr_l = pam_wifi_term_sender->tx_fifo_type1.fifo_base_addr_l;
			dl_fifo_base_addr_h = pam_wifi_term_sender->tx_fifo_type1.fifo_base_addr_h;
#if 1
			if (pam_wifi_term_sender->pam_wifi_term_id != pam_wifi_term_dl)
			{
				pam_wifi_term_sender->tx_fifo_type1.wr = dl_fifo_depth;
			}
#endif
		}
		else if(p_dl_fifo_type == dl_tx_fifo_type2)
		{
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type2_fifo_reg_base;
			dl_fifo_depth = pam_wifi_term_sender->tx_fifo_type2.depth;
			dl_fifo_base_addr_l = pam_wifi_term_sender->tx_fifo_type2.fifo_base_addr_l;
			dl_fifo_base_addr_h = pam_wifi_term_sender->tx_fifo_type2.fifo_base_addr_h;
#if 1
			if (pam_wifi_term_sender->pam_wifi_term_id != pam_wifi_term_dl)
			{
				pam_wifi_term_sender->tx_fifo_type2.wr = dl_fifo_depth;
			}
#endif
		}
		else if(p_dl_fifo_type == dl_tx_fifo_type3)
		{
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type3_fifo_reg_base;
			dl_fifo_depth = pam_wifi_term_sender->tx_fifo_type3.depth;
			dl_fifo_base_addr_l = pam_wifi_term_sender->tx_fifo_type3.fifo_base_addr_l;
			dl_fifo_base_addr_h = pam_wifi_term_sender->tx_fifo_type3.fifo_base_addr_h;

#if 1
                	if (pam_wifi_term_sender->pam_wifi_term_id != pam_wifi_term_dl)
			{
				pam_wifi_term_sender->tx_fifo_type3.wr = dl_fifo_depth;
                        }
#endif
		}
		else if(p_dl_fifo_type == dl_tx_fifo_type4)
		{
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type4_fifo_reg_base;
			dl_fifo_depth = pam_wifi_term_sender->tx_fifo_type4.depth;
			dl_fifo_base_addr_l = pam_wifi_term_sender->tx_fifo_type4.fifo_base_addr_l;
			dl_fifo_base_addr_h = pam_wifi_term_sender->tx_fifo_type4.fifo_base_addr_h;

#if 1
			if (pam_wifi_term_sender->pam_wifi_term_id != pam_wifi_term_dl)
			{
				pam_wifi_term_sender->tx_fifo_type4.wr = dl_fifo_depth;
                        }
#endif
		}
		else
                {
                    printk("\n");
                }

        	pam_wifi_set_tx_fifo_total_depth(fifo_reg_base, dl_fifo_depth);
        	pam_wifi_set_tx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);

        	pam_wifi_update_tx_fifo_rptr(fifo_reg_base, 0);
        	pam_wifi_update_tx_fifo_wptr(fifo_reg_base, dl_fifo_depth);
        }

        pam_wifi_term_sender->tx_fifo_type1.rd = 0;
        pam_wifi_term_sender->tx_fifo_type2.rd = 0;
        pam_wifi_term_sender->tx_fifo_type3.rd = 0;
        pam_wifi_term_sender->tx_fifo_type4.rd = 0;
    //*******************END Set the Common FIFO TX Part***************

#if 1
	pam_wifi_set_cur_term_num(fifo_reg_base, pam_wifi_term_sender->cur);
	pam_wifi_set_dst_term_num(fifo_reg_base, pam_wifi_term_sender->dst);
#endif

	pam_wifi_term_sender->state = TRUE;
	return TRUE;
}

static u32 pam_wifi_fifo_sender_hal_close(enum pam_wifi_term_id id)
{
	int i = 0;
    	u64 fifo_reg_base =0;
    	//u32 dl_fifo_depth =0;

    	enum dl_fifo_type p_dl_fifo_type =dl_fifo_free;
	struct pam_wifi_sender *pam_wifi_term_sender = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_sender = &(pam_wifi_dl_fifo_sender_dev.term_sender[i]);

	//*******************Set the Common FIFO RX Part*****************
	fifo_reg_base = pam_wifi_term_sender->dl_free_fifo_reg_base;
	pam_wifi_set_rx_fifo_total_depth(fifo_reg_base, 0);
	//*******************END Set the Common FIFO RX Part***************

	//******************END Set the Common FIFO TX Part***************
	for(i=dl_tx_fifo_type1;i<(dl_tx_fifo_type4+1);i++)
        {
		p_dl_fifo_type = i;
		if(p_dl_fifo_type == dl_tx_fifo_type1)
                {
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type1_fifo_reg_base;
                }
		else if(p_dl_fifo_type == dl_tx_fifo_type2)
                {
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type2_fifo_reg_base;
                }
		else if(p_dl_fifo_type == dl_tx_fifo_type3)
                {
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type3_fifo_reg_base;
                }
		else if(p_dl_fifo_type == dl_tx_fifo_type4)
                {
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type4_fifo_reg_base;
                }
		else
                {
			printk("pam_wifi_cp0_fifo_sender_hal_open error p_dl_fifo_type <%d>\n", p_dl_fifo_type);
                }

            pam_wifi_set_tx_fifo_total_depth(fifo_reg_base, 0);
	}
    //*******************END Set the Common FIFO TX Part***************

	pam_wifi_term_sender->state = FALSE;

	return TRUE;
}

#if 0
static u32 pam_wifi_fifo_sender_hal_reset_fifo(enum pam_wifi_term_id id)
{
	int i = 0;
    u64 fifo_reg_base =0;
    u32 dl_fifo_depth =0;
    u32 dl_fifo_base_addr_l =0;
    u32 dl_fifo_base_addr_h =0;

    	enum dl_fifo_type p_dl_fifo_type =dl_tx_fifo_type1;
	struct pam_wifi_sender *pam_wifi_term_sender = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_sender = &(pam_wifi_dl_fifo_sender_dev.term_sender[i]);

    //*******************Set the Common FIFO RX Part*****************
    fifo_reg_base = pam_wifi_term_sender->dl_free_fifo_reg_base;
    dl_fifo_depth = pam_wifi_term_sender->dl_free_fifo.depth;
    dl_fifo_base_addr_l = pam_wifi_term_sender->dl_free_fifo.fifo_base_addr_l;
    dl_fifo_base_addr_h = pam_wifi_term_sender->dl_free_fifo.fifo_base_addr_h;

    pam_wifi_set_rx_fifo_total_depth(fifo_reg_base, dl_fifo_depth);
    pam_wifi_set_rx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);

    pam_wifi_update_rx_fifo_rptr(fifo_reg_base, 0);
    pam_wifi_update_rx_fifo_wptr(fifo_reg_base, 0);

    pam_wifi_term_sender->dl_free_fifo.rd = 0;
    pam_wifi_term_sender->dl_free_fifo.wr = 0;
    //*******************END Set the Common FIFO RX Part***************

    //*******************Set the Common FIFO TX Part*******************

    //*******************END Set the Common FIFO TX Part************** 

    //*******************Set the Common FIFO TX Part***************
    for(i=dl_tx_fifo_type1;i<(dl_tx_fifo_type4+1);i++)
        {
            p_dl_fifo_type = i;
            if(p_dl_fifo_type == dl_tx_fifo_type1)
                {
                    fifo_reg_base = pam_wifi_term_sender->dl_tx_type1_fifo_reg_base;
                    dl_fifo_depth = pam_wifi_term_sender->tx_fifo_type1.depth;
                    dl_fifo_base_addr_l = pam_wifi_term_sender->tx_fifo_type1.fifo_base_addr_l;
                    dl_fifo_base_addr_h = pam_wifi_term_sender->tx_fifo_type1.fifo_base_addr_h;

                	pam_wifi_term_sender->tx_fifo_type1.rd = 0;
                	pam_wifi_term_sender->tx_fifo_type1.wr = dl_fifo_depth;
                }
            else if(p_dl_fifo_type == dl_tx_fifo_type2)
                {
                    fifo_reg_base = pam_wifi_term_sender->dl_tx_type2_fifo_reg_base;
                    dl_fifo_depth = pam_wifi_term_sender->tx_fifo_type2.depth;
                    dl_fifo_base_addr_l = pam_wifi_term_sender->tx_fifo_type2.fifo_base_addr_l;
                    dl_fifo_base_addr_h = pam_wifi_term_sender->tx_fifo_type2.fifo_base_addr_h;

                	pam_wifi_term_sender->tx_fifo_type2.rd = 0;
                	pam_wifi_term_sender->tx_fifo_type2.wr = dl_fifo_depth;
                }
            else if(p_dl_fifo_type == dl_tx_fifo_type3)
                {
                    fifo_reg_base = pam_wifi_term_sender->dl_tx_type3_fifo_reg_base;
                    dl_fifo_depth = pam_wifi_term_sender->tx_fifo_type3.depth;
                    dl_fifo_base_addr_l = pam_wifi_term_sender->tx_fifo_type3.fifo_base_addr_l;
                    dl_fifo_base_addr_h = pam_wifi_term_sender->tx_fifo_type3.fifo_base_addr_h;

                	pam_wifi_term_sender->tx_fifo_type3.rd = 0;
                	pam_wifi_term_sender->tx_fifo_type3.wr = dl_fifo_depth;
                }
            else if(p_dl_fifo_type == dl_tx_fifo_type4)
                {
                    fifo_reg_base = pam_wifi_term_sender->dl_tx_type4_fifo_reg_base;
                    dl_fifo_depth = pam_wifi_term_sender->tx_fifo_type4.depth;
                    dl_fifo_base_addr_l = pam_wifi_term_sender->tx_fifo_type4.fifo_base_addr_l;
                    dl_fifo_base_addr_h = pam_wifi_term_sender->tx_fifo_type4.fifo_base_addr_h;

                	pam_wifi_term_sender->tx_fifo_type4.rd = 0;
                	pam_wifi_term_sender->tx_fifo_type4.wr = dl_fifo_depth;
                }
            else
                {
                    printk("pam_wifi_cp0_fifo_sender_hal_open error p_dl_fifo_type <%d>\n", p_dl_fifo_type);
                }
        	pam_wifi_set_tx_fifo_total_depth(fifo_reg_base, dl_fifo_depth);
        	pam_wifi_set_tx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);

        	pam_wifi_update_tx_fifo_rptr(fifo_reg_base, 0);
        	pam_wifi_update_tx_fifo_wptr(fifo_reg_base, dl_fifo_depth);
	}

	pam_wifi_term_sender->state = TRUE;

	return TRUE;
}
#endif

static u32 pam_wifi_fifo_sender_hal_set_rx_depth(enum pam_wifi_term_id id, u32 depth)
{
	u32 i = 0, ret = 0;
	u64 fifo_reg_base =0;

	struct pam_wifi_sender *pam_wifi_term_sender = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_sender = &(pam_wifi_dl_fifo_sender_dev.term_sender[i]);

	//*******************Set the Common FIFO RX Part*****************
	fifo_reg_base = pam_wifi_term_sender->dl_free_fifo_reg_base;
	pam_wifi_update_rx_fifo_rptr(fifo_reg_base, 0);
	pam_wifi_update_rx_fifo_wptr(fifo_reg_base, 0);

    	ret = pam_wifi_set_rx_fifo_total_depth(fifo_reg_base, depth);

    	pam_wifi_term_sender->dl_free_fifo.rd = 0;
	pam_wifi_term_sender->dl_free_fifo.wr = 0;
    	//*******************END Set the Common FIFO RX Part***************
	return ret;
}

static u32 pam_wifi_fifo_sender_hal_set_tx_depth(enum pam_wifi_term_id id, u32 depth)
{
	u32 i = 0, ret = 0;
    	u64 fifo_reg_base =0;

	enum dl_fifo_type p_dl_fifo_type =dl_tx_fifo_type1;
	struct pam_wifi_sender *pam_wifi_term_sender = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_sender = &(pam_wifi_dl_fifo_sender_dev.term_sender[i]);

    //*******************Set the Common FIFO TX Part*******************
	for(i=dl_tx_fifo_type1;i<(dl_tx_fifo_type4+1);i++)
        {
		p_dl_fifo_type = i;
		if(p_dl_fifo_type == dl_tx_fifo_type1)
                {
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type1_fifo_reg_base;
                }
		else if(p_dl_fifo_type == dl_tx_fifo_type2)
                {
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type2_fifo_reg_base;
		}
		else if(p_dl_fifo_type == dl_tx_fifo_type3)
		{
			fifo_reg_base = pam_wifi_term_sender->dl_tx_type3_fifo_reg_base;
                }
		else if(p_dl_fifo_type == dl_tx_fifo_type4)
                {
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type4_fifo_reg_base;
                }
		else
		{
                    printk("pam_wifi_cp0_fifo_sender_hal_open error p_dl_fifo_type <%d>\n", p_dl_fifo_type);
                }
        	ret = pam_wifi_set_tx_fifo_total_depth(fifo_reg_base, depth);
        	pam_wifi_update_tx_fifo_rptr(fifo_reg_base, 0);
        	pam_wifi_update_tx_fifo_wptr(fifo_reg_base, depth);
        }

	pam_wifi_term_sender->tx_fifo_type1.rd = 0;
	pam_wifi_term_sender->tx_fifo_type1.wr = depth;

	pam_wifi_term_sender->tx_fifo_type2.rd = 0;
	pam_wifi_term_sender->tx_fifo_type2.wr = depth;

	pam_wifi_term_sender->tx_fifo_type3.rd = 0;
	pam_wifi_term_sender->tx_fifo_type3.wr = depth;

	pam_wifi_term_sender->tx_fifo_type4.rd = 0;
	pam_wifi_term_sender->tx_fifo_type4.wr = depth;
    //*******************END Set the Common FIFO TX Part**************
	return ret;
}

static u32 pam_wifi_sender_put_pkt_to_fifo(struct pam_wifi_sender *sender_cfg, u32 force_intr,
					struct data_pkt_tag *pkt, u32 num,enum dl_fifo_type p_dl_fifo_type)
{
	u64 fifo_reg_base = 0;
	u32 i = 0, ret = 0, index = 0, left_cnt = 0;
	struct sipa_node_description_tag *node;

	node = (struct sipa_node_description_tag *)(((u64)(sender_cfg->dl_free_fifo.fifo_base_addr_h) << 32) |
			(sender_cfg->dl_free_fifo.fifo_base_addr_l));
	if(p_dl_fifo_type == dl_fifo_free)
        {
		fifo_reg_base = sender_cfg->dl_free_fifo_reg_base;
        }
	else if(p_dl_fifo_type == dl_tx_fifo_type1)
        {
		fifo_reg_base = sender_cfg->dl_tx_type1_fifo_reg_base;
        }
	else if(p_dl_fifo_type == dl_tx_fifo_type2)
        {
		fifo_reg_base = sender_cfg->dl_tx_type2_fifo_reg_base;
        }
	else if(p_dl_fifo_type == dl_tx_fifo_type3)
        {
		fifo_reg_base = sender_cfg->dl_tx_type3_fifo_reg_base;
        }
	else if(p_dl_fifo_type == dl_tx_fifo_type4)
        {
		fifo_reg_base = sender_cfg->dl_tx_type4_fifo_reg_base;
        }
	else
        {
		printk("pam_wifi_cp0_fifo_sender_hal_open error p_dl_fifo_type <%d>\n", p_dl_fifo_type);
        }

	if (pam_wifi_get_rx_fifo_full_status(fifo_reg_base)) {
        printk("fifo_id = %d is full\n", sender_cfg->pam_wifi_term_id);
		return FALSE;
	}

	left_cnt = pam_wifi_get_rx_fifo_total_depth(fifo_reg_base) -
				pam_wifi_get_rx_fifo_filled_depth(fifo_reg_base);

	if (left_cnt < num)
		num = left_cnt;
	for (i = 0; i < num; i++) {
		index = (sender_cfg->dl_free_fifo.wr + i) & (sender_cfg->dl_free_fifo.depth - 1);
		ipa_pkt_to_node(pkt + i, force_intr, node + index);
	}

	sender_cfg->dl_free_fifo.wr = (sender_cfg->dl_free_fifo.wr + num) & PTR_MASK(sender_cfg->dl_free_fifo.depth);
	ret = pam_wifi_update_rx_fifo_wptr(fifo_reg_base, sender_cfg->dl_free_fifo.wr);

	if (ret == FALSE)
		printk("pam_wifi_phy_update_rx_fifo_rptr fail\n");

	return num;
}

/*****************************************************************************
 * Description: Send Node to rx fifo.
 * Input:
 *   id: The FIFO id that need to be operated.
 *   pkt: The node address that need send to rx fifo.
 *   num: The number of need to send.
 * OUTPUT:
 *   The number that has sent to rx fifo successful.
 * Note:
*****************************************************************************/
static u32 pam_wifi_fifo_sender_hal_send(enum pam_wifi_term_id id, struct data_pkt_tag *node, u32 force_intr, u32 num, enum dl_fifo_type p_dl_fifo_type)
{
	u32 i = 0, ret = 0;
	struct pam_wifi_sender *pam_wifi_term_sender = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_sender = &(pam_wifi_dl_fifo_sender_dev.term_sender[i]);

    //To be changed for special FIFO:5 TX or RX?

	ret = pam_wifi_sender_put_pkt_to_fifo(pam_wifi_term_sender, force_intr, node, num, p_dl_fifo_type);

	return ret;
}

/*****************************************************************************
 * Description: Set tx fifo interrupt threshold of value.
 * Input:
 *   fifo_base: Need to get threshold interrupt value of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   TRUE: set successfully.
 *   FALSE: set failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_set_tx_fifo_interrupt_threshold(u64 fifo_base, u32 threshold)
{
	u32 tmp = 0;

	if (threshold > 0xFFFF)
		return FALSE;
	else {
		/* tmp = *(volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE);
		tmp &= 0x0000FFFF;
		tmp |= (threshold << 16);
		*(volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE) = tmp;

		if (((*(volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE))
				>> 16) == threshold)
			return TRUE;
		else
			return FALSE;*/
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
		tmp &= 0x0000FFFF;
		tmp |= (threshold << 16);
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	}
	return 1;
}

/*****************************************************************************
 * Description: Enable interrupt bit.
 * Input:
 *   fifo_base: Need to enable interrupr bit of the FIFO, the base
 *              address of the FIFO.
 *   int_bit: The interrupt bit that need to enable.
 * return:
 *   TRUE: Enable successfully.
 *   FALSE: Enable successfully.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_enable_int_bit(u64 fifo_base, u32 int_bit)
{
	u32 ret = 0;
	printk("%s\n", __func__);
	//*((volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN)) |= int_bit;
    //ret = (*(volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN));
    //printk("%s PAMWIFI_INT_GEN_CTL_EN value:<%x>\n", __func__,ret);
	//ret = ((*(volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN)) & int_bit);
	ret = readl_relaxed((void *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN));
	ret |= int_bit;
	writel_relaxed(ret, (void *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN));
	ret = readl_relaxed((void *)(fifo_base + PAMWIFI_INT_GEN_CTL_EN));
	if (ret) {
		ret = TRUE;
        printk("%s ret = TRUE\n", __func__);
	} else {
		ret = FALSE;
		printk("Enable interrupt bit = 0x%x set failed!\n", int_bit);
	}

	return ret;
}

static u32 pam_wifi_fifo_sender_hal_set_interrupt_threshold(enum pam_wifi_term_id id, u32 enable,
				u32 cnt, enum dl_fifo_type p_dl_fifo_type, void *cb)
{
	u64 fifo_reg_base = 0;
	u32 i = 0, ret = 0;
	struct pam_wifi_sender *pam_wifi_term_sender = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_sender = &(pam_wifi_dl_fifo_sender_dev.term_sender[i]);

	if(p_dl_fifo_type == dl_fifo_free)
        {
		fifo_reg_base = pam_wifi_term_sender->dl_free_fifo_reg_base;
        }
	else if(p_dl_fifo_type == dl_tx_fifo_type1)
        {
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type1_fifo_reg_base;
        }
	else if(p_dl_fifo_type == dl_tx_fifo_type2)
        {
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type2_fifo_reg_base;
        }
	else if(p_dl_fifo_type == dl_tx_fifo_type3)
        {
            fifo_reg_base = pam_wifi_term_sender->dl_tx_type3_fifo_reg_base;
        }
	else if(p_dl_fifo_type == dl_tx_fifo_type4)
        {
            fifo_reg_base = pam_wifi_term_sender->dl_tx_type4_fifo_reg_base;
        }
	else
        {
            printk("pam_wifi_cp0_fifo_sender_hal_open error p_dl_fifo_type <%d>\n", p_dl_fifo_type);
        }

#if 1
	if (enable) {
		pam_wifi_term_sender->threshold_callback = cb;
		ret = pam_wifi_set_tx_fifo_interrupt_threshold(fifo_reg_base, cnt);
		if (ret)
			ret = pam_wifi_enable_int_bit(fifo_reg_base,PAMWIFI_TXFIFO_INT_THRESHOLD_ONESHOT_EN | PAMWIFI_TX_FIFO_THRESHOLD_EN);
		else
			ret = FALSE;
	} else {
		pam_wifi_term_sender->threshold_callback = NULL;
		ret = pam_wifi_disable_int_bit(fifo_reg_base,PAMWIFI_TXFIFO_INT_THRESHOLD_ONESHOT_EN);
	}
#endif

	return ret;
}

/*****************************************************************************
 * Description: Set tx fifo interrupt of delay timer value.
 * Input:
 *   fifo_base: Need to set delay timer interrupt of the FIFO, the base
 *              address of the FIFO.
 *   threshold: The overflow value that need to set.
 * return:
 *   TRUE: Set successfully.
 *   FALSE: set failed.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_set_tx_fifo_interrupt_delay_timer(u64 fifo_base, u32 threshold)
{
	u32 tmp = 0;

	if (threshold > 0xFFFF)
		return FALSE;
	else {
		/*tmp = *(volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE);
		tmp &= 0xFFFF0000;
		tmp |= threshold;
		*(volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE) = tmp;

		if (((*(volatile u32 *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE))
				& 0x0000FFFF) == threshold)
			return TRUE;
		else
			return FALSE;*/
		tmp = readl_relaxed((void *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
		tmp &= 0xFFFF0000;
		tmp |= threshold;
		writel_relaxed(tmp, (void *)(fifo_base + PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	}
	return 1;
}

static u32 pam_wifi_fifo_sender_hal_set_interrupt_timeout(enum pam_wifi_term_id id, u32 enable,
				u32 time,enum dl_fifo_type p_dl_fifo_type, void *cb)
{
       u64 fifo_reg_base = 0;
	u32 i = 0, ret = 0;
	struct pam_wifi_sender *pam_wifi_term_sender = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_sender = &(pam_wifi_dl_fifo_sender_dev.term_sender[i]);

	if(p_dl_fifo_type == dl_fifo_free)
	{
		fifo_reg_base = pam_wifi_term_sender->dl_free_fifo_reg_base;
	}
	else if(p_dl_fifo_type == dl_tx_fifo_type1)
	{
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type1_fifo_reg_base;
	}
	else if(p_dl_fifo_type == dl_tx_fifo_type2)
	{
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type2_fifo_reg_base;
	}
	else if(p_dl_fifo_type == dl_tx_fifo_type3)
	{
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type3_fifo_reg_base;
	}
    	else if(p_dl_fifo_type == dl_tx_fifo_type4)
 	{
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type4_fifo_reg_base;
        }
	else
        {
		printk("pam_wifi_cp0_fifo_sender_hal_open error p_dl_fifo_type <%d>\n", p_dl_fifo_type);
        }

#if 1
	if (enable) {
		pam_wifi_term_sender->delay_timer_callback = cb;
		ret = pam_wifi_set_tx_fifo_interrupt_delay_timer(fifo_reg_base, time);
		if (ret)
			ret = pam_wifi_enable_int_bit(fifo_reg_base,PAMWIFI_TX_FIFO_DELAY_TIMER_EN | PAMWIFI_TXFIFO_INT_DELAY_TIMER_SW_EN);
		else
			ret = FALSE;
	} else {
		pam_wifi_term_sender->delay_timer_callback = NULL;
		ret = pam_wifi_disable_int_bit(fifo_reg_base,PAMWIFI_TXFIFO_INT_DELAY_TIMER_SW_EN);
	}
#endif
    	return ret;
}

/*****************************************************************************
 * Description: get tx fifo write pointer.
 * Input:
 *   fifo_base: Need to get tx fifo write pointer of the FIFO, the base
 *              address of the FIFO.
 * return:
 *   The write pointer of rx fifo.
 * Note:
*****************************************************************************/
static inline u32 pam_wifi_phy_get_tx_fifo_rptr(u64 fifo_base)
{
	//return (*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD) >> 16);
	return readl_relaxed((void*)(fifo_base + PAMWIFI_COMMON_TX_FIFO_RD)) >> 16;
}

static inline u32 pam_wifi_phy_get_tx_fifo_wptr(u64 fifo_base)
{
	//return (*(volatile u32 *)(fifo_base + PAMWIFI_COMMON_TX_FIFO_WR) >> 16);
	return readl_relaxed((void*)(fifo_base + PAMWIFI_COMMON_TX_FIFO_WR)) >> 16;
}

static u32 pam_wifi_cp0_fifo_sender_hal_get_tx_ptr(enum pam_wifi_term_id id, u32 *wr, u32 *rd, enum dl_fifo_type p_dl_fifo_type)
{
	u32 i = 0;
	u64 fifo_reg_base =0;
	struct pam_wifi_sender *pam_wifi_term_sender = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_sender = &(pam_wifi_dl_fifo_sender_dev.term_sender[i]);

	if(p_dl_fifo_type == dl_tx_fifo_type1)
	{
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type1_fifo_reg_base;
	}
	else if(p_dl_fifo_type == dl_tx_fifo_type2)
	{
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type2_fifo_reg_base;
        }
	else if(p_dl_fifo_type == dl_tx_fifo_type3)
	{
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type3_fifo_reg_base;
	}
	else if(p_dl_fifo_type == dl_tx_fifo_type4)
	{
		fifo_reg_base = pam_wifi_term_sender->dl_tx_type4_fifo_reg_base;
	}
	else
	{
		printk("pam_wifi_cp0_fifo_sender_hal_get_tx_ptr error p_dl_fifo_type <%d>\n", p_dl_fifo_type);
	}

	if (rd != NULL)
		*rd = pam_wifi_phy_get_tx_fifo_rptr(fifo_reg_base);
	if (wr != NULL)
		*wr = pam_wifi_phy_get_tx_fifo_wptr(fifo_reg_base);

	return TRUE;
}

u8 term_pam_wifi_inn_dl_tx_type1_fifo_buf[PAM_WIFI_DL_TX_FIFO_DEPTH * 16];
u8 term_pam_wifi_inn_dl_tx_type2_fifo_buf[PAM_WIFI_DL_TX_FIFO_DEPTH * 16];
u8 term_pam_wifi_inn_dl_tx_type3_fifo_buf[PAM_WIFI_DL_TX_FIFO_DEPTH * 16];
u8 term_pam_wifi_inn_dl_tx_type4_fifo_buf[PAM_WIFI_DL_TX_FIFO_DEPTH * 16];
u8 term_pam_wifi_inn_dl_rx_free_buf[PAM_WIFI_DL_RX_FIFO_DEPTH * 16];
u8 term_pam_wifi_inn_dl_data_buf[PAM_WIFI_DL_TX_FIFO_DEPTH][2048];

u8 term_pam_wifi_inn_ul_tx_fifo_buf[PAM_WIFI_UL_TX_FIFO_DEPTH * 8];
u8 term_pam_wifi_inn_ul_rx_fifo_buf[PAM_WIFI_UL_RX_FIFO_DEPTH * 8];
u8 term_pam_wifi_inn_ul_data_buf[PAM_WIFI_UL_TX_FIFO_DEPTH][2048];

unsigned long mm_virt_to_phys_pam_wifi(struct device *dev, void *buffer, size_t size,
			      enum dma_data_direction direction)
{
	u64 pa = 0;

//again:
	mb();

	pa = virt_to_phys(buffer);//dma_map_single(dev, buffer, size, DMA_NONE);
	//if (dma_mapping_error(dev, pa))
	//	goto again;

	return pa;
}

#if 0
static u32 pam_wifi_sender_init_ddr_fifo(struct platform_device *pdev)
{
	//int i = 0;
	//struct sipa_node_description_tag *node_ptr = NULL;

	unsigned long pcie_addr = 0;

	/*pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_rx_free_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].dl_free_fifo.fifo_base_addr_l =
			(u32)(pcie_addr & 0xFFFFFFFFl);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].dl_free_fifo.fifo_base_addr_h =
			(u32)(pcie_addr >> 32);
	pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_tx_type1_fifo_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type1.fifo_base_addr_l =
			(u32)(pcie_addr & 0xFFFFFFFFl);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type1.fifo_base_addr_h =
			(u32)(pcie_addr >> 32);

	pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_tx_type2_fifo_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type2.fifo_base_addr_l =
			(u32)(pcie_addr & 0xFFFFFFFFl);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type2.fifo_base_addr_h =
			(u32)(pcie_addr >> 32);

	pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_tx_type3_fifo_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type3.fifo_base_addr_l =
			(u32)(pcie_addr & 0xFFFFFFFFl);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type3.fifo_base_addr_h =
			(u32)(pcie_addr >> 32);

	pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_tx_type4_fifo_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type4.fifo_base_addr_l =
			(u32)(pcie_addr & 0xFFFFFFFFl);
	pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type4.fifo_base_addr_h =
			(u32)(pcie_addr >> 32); */

	pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_rx_free_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	writel_relaxed((u32)(pcie_addr & 0xFFFFFFFFl), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].dl_free_fifo.fifo_base_addr_l));
	writel_relaxed((u32)(pcie_addr >> 32), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].dl_free_fifo.fifo_base_addr_h));

	pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_tx_type1_fifo_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	writel_relaxed((u32)(pcie_addr & 0xFFFFFFFFl), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type1.fifo_base_addr_l));
	writel_relaxed((u32)(pcie_addr >> 32), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type1.fifo_base_addr_h));

	pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_tx_type2_fifo_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	writel_relaxed((u32)(pcie_addr & 0xFFFFFFFFl), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type2.fifo_base_addr_l));
	writel_relaxed((u32)(pcie_addr >> 32), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type2.fifo_base_addr_h));

	pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_tx_type3_fifo_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	writel_relaxed((u32)(pcie_addr & 0xFFFFFFFFl), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type3.fifo_base_addr_l));
	writel_relaxed((u32)(pcie_addr >> 32), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type3.fifo_base_addr_h));

	pcie_addr = mm_virt_to_phys_pam_wifi(&pdev->dev, term_pam_wifi_inn_dl_tx_type4_fifo_buf,
		PAM_WIFI_DL_RX_FIFO_DEPTH * 16, DMA_BIDIRECTIONAL);
	writel_relaxed((u32)(pcie_addr & 0xFFFFFFFFl), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type4.fifo_base_addr_l));
	writel_relaxed((u32)(pcie_addr >> 32), (void *)(pam_wifi_dl_fifo_sender_dev.term_sender[0].tx_fifo_type4.fifo_base_addr_h));

	memset(term_pam_wifi_inn_dl_data_buf, 0xE7, sizeof(term_pam_wifi_inn_dl_data_buf));
   //tx_fifo change to tx_fifo_type1 ~ tx_fifo_type4

    #if 0
	node_ptr = (struct sipa_node_description_tag *)term_pam_wifi_inn_dl_rx_free_buf;
	for (i = 0; i < TERM_AP_IP_TX_TX_FIFO_DEPTH; i++) {
		term_ap_ip_tx_def_node.address = (u64)(term_ap_ip_tx_data_buf[i]);
		memcpy((node_ptr + i), &term_ap_ip_tx_def_node, sizeof(term_ap_ip_tx_def_node));
	}
    #endif
	return 1;
}
#endif

u32 pam_wifi_sender_fifo_init(void)
{
	pam_wifi_dl_fifo_sender_dev.send_ops.open =
			pam_wifi_fifo_sender_open;

	pam_wifi_dl_fifo_sender_dev.send_ops.close =
			pam_wifi_fifo_sender_hal_close;

	/*pam_wifi_dl_fifo_sender_dev.send_ops.reset =
		pam_wifi_fifo_sender_hal_reset_fifo;*/

	pam_wifi_dl_fifo_sender_dev.send_ops.set_rx_depth =
		pam_wifi_fifo_sender_hal_set_rx_depth;

	pam_wifi_dl_fifo_sender_dev.send_ops.set_tx_depth =
		pam_wifi_fifo_sender_hal_set_tx_depth;
	pam_wifi_dl_fifo_sender_dev.send_ops.send =
			pam_wifi_fifo_sender_hal_send;

	pam_wifi_dl_fifo_sender_dev.send_ops.set_interrupt_threshold =
		pam_wifi_fifo_sender_hal_set_interrupt_threshold;

	pam_wifi_dl_fifo_sender_dev.send_ops.set_interrupt_timeout =
			pam_wifi_fifo_sender_hal_set_interrupt_timeout;
	pam_wifi_dl_fifo_sender_dev.send_ops.get_tx_fifo_wr_rd_ptr =
			pam_wifi_cp0_fifo_sender_hal_get_tx_ptr;
/*
	//pam_wifi_dl_fifo_sender_dev.send_ops.enable_flowctrl_interrupt = pam_wifi_cp0_fifo_sender_hal_enable_flowctrl_interrupt;

	pam_wifi_dl_fifo_sender_dev.send_ops.get_left_cnt =
			pam_wifi_fifo_sender_hal_get_left_cnt;

	pam_wifi_dl_fifo_sender_dev.send_ops.get =
			pam_wifi_cp0_fifo_sender_hal_get;

	//pam_wifi_dl_fifo_sender_dev.send_ops.set_interrupt_drop_packet =pam_wifi_cp0_fifo_sender_hal_set_interrupt_drop_packet;

	pam_wifi_dl_fifo_sender_dev.send_ops.set_interrupt_error_code =
			pam_wifi_cp0_fifo_sender_hal_set_interrupt_error_code;

	pam_wifi_dl_fifo_sender_dev.send_ops.set_interrupt_intr =
			pam_wifi_cp0_fifo_sender_hal_set_interrupt_intr;

	pam_wifi_dl_fifo_sender_dev.send_ops.set_interrupt_txfifo_full =
			pam_wifi_cp0_fifo_sender_hal_set_interrupt_txfifo_full;

	pam_wifi_dl_fifo_sender_dev.send_ops.set_interrupt_txfifo_overflow =
			pam_wifi_cp0_fifo_sender_hal_set_interrupt_txfifo_overflow;

	pam_wifi_dl_fifo_sender_dev.send_ops.get_rx_fifo_wr_rd_ptr =
			pam_wifi_cp0_fifo_sender_hal_get_rx_ptr;

	pam_wifi_dl_fifo_sender_dev.send_ops.get_filled_depth =
			pam_wifi_cp0_fifo_sender_hal_get_filled_depth;

	pam_wifi_dl_fifo_sender_dev.send_ops.get_full_empty_status =
			pam_wifi_cp0_fifo_sender_hal_get_full_empty_status;

	pam_wifi_dl_fifo_sender_dev.send_ops.set_rx_tx_fifo_wr_rd_ptr =
			pam_wifi_cp0_fifo_sender_set_rx_tx_fifo_wr_rd_ptr;

	pam_wifi_dl_fifo_sender_dev.send_ops.set_cur_dst_term =
			pam_wifi_cp0_fifo_sender_hal_set_src_dst_term;
*/
	return TRUE;
}

static u32 pam_wifi_fifo_receiver_hal_open(enum pam_wifi_term_id id, void *cookie)
{
	int i = 0;
	struct pam_wifi_receiver *pam_wifi_term_receiver = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_ul_fifo_receiver_dev.term_receiver[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_receiver = &(pam_wifi_ul_fifo_receiver_dev.term_receiver[i]);
	//.fifo_reg_base = PSEL_UL,
	pam_wifi_term_receiver->fifo_reg_base = PSEL_UL;

	if (pam_wifi_term_receiver->state == TRUE) {
		printk("%s has already opened, don't need open again\n", pam_wifi_term_receiver->fifo_name);
		return TRUE;
	}
	pam_wifi_set_rx_fifo_total_depth(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->rx_fifo.depth);

	pam_wifi_set_rx_fifo_addr(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->rx_fifo.fifo_base_addr_l,
		pam_wifi_term_receiver->rx_fifo.fifo_base_addr_h);

	pam_wifi_set_tx_fifo_total_depth(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->tx_fifo.depth);
	pam_wifi_set_tx_fifo_addr(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->tx_fifo.fifo_base_addr_l,
		pam_wifi_term_receiver->tx_fifo.fifo_base_addr_h);

    //For the IPA_INT_EN_BIT_GROUP
#if 1
	if (id != pam_wifi_term_dl) {
		pam_wifi_update_tx_fifo_rptr(pam_wifi_term_receiver->fifo_reg_base, 0);
		pam_wifi_update_tx_fifo_wptr(pam_wifi_term_receiver->fifo_reg_base, 0);
	} else {
		pam_wifi_update_rx_fifo_rptr(pam_wifi_term_receiver->fifo_reg_base, 0);
		pam_wifi_update_rx_fifo_wptr(pam_wifi_term_receiver->fifo_reg_base, 0);
	}
	pam_wifi_set_cur_term_num(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->cur);
	pam_wifi_set_dst_term_num(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->dst);

	pam_wifi_disable_int_bit(pam_wifi_term_receiver->fifo_reg_base, PAMWIFI_INT_EN_BIT_GROUP);
#endif

#if 1
	if (pam_wifi_term_receiver->is_dma) {
		if (id != pam_wifi_term_dl)
        {
			pam_wifi_init_receiver_rx_fifo_node(id,
				(struct sipa_node_description_tag *)((u64)pam_wifi_term_receiver->rx_fifo.fifo_base_addr_l |
				((u64)pam_wifi_term_receiver->rx_fifo.fifo_base_addr_h << 32)),
				pam_wifi_term_receiver->rx_fifo.depth);
        }
    else
        {
			pam_wifi_init_receiver_rx_fifo_node(id,
				(struct sipa_node_description_tag *)((u64)pam_wifi_term_receiver->tx_fifo.fifo_base_addr_l |
				((u64)pam_wifi_term_receiver->tx_fifo.fifo_base_addr_h << 32)),
				pam_wifi_term_receiver->tx_fifo.depth); 
        }

		if (id != pam_wifi_term_dl) {
			pam_wifi_update_rx_fifo_rptr(pam_wifi_term_receiver->fifo_reg_base, 0);

			pam_wifi_term_receiver->rx_fifo.rd = 0;
			pam_wifi_term_receiver->rx_fifo.wr = pam_wifi_term_receiver->rx_fifo.depth;
		} else {
			pam_wifi_update_tx_fifo_rptr(pam_wifi_term_receiver->fifo_reg_base, 0);
			pam_wifi_update_tx_fifo_wptr(pam_wifi_term_receiver->fifo_reg_base,
				pam_wifi_term_receiver->tx_fifo.depth);
			pam_wifi_term_receiver->tx_fifo.rd = 0;
			pam_wifi_term_receiver->tx_fifo.wr = pam_wifi_term_receiver->tx_fifo.depth;
		}
	} else {
		pam_wifi_update_rx_fifo_rptr(pam_wifi_term_receiver->fifo_reg_base, 0);
		pam_wifi_update_rx_fifo_wptr(pam_wifi_term_receiver->fifo_reg_base, 0);
		pam_wifi_term_receiver->rx_fifo.rd = 0;
		pam_wifi_term_receiver->rx_fifo.wr = 0;
	}

	if (id != pam_wifi_term_dl) {
		pam_wifi_term_receiver->tx_fifo.rd = 0;
		pam_wifi_term_receiver->tx_fifo.wr = 0;
	} else {
		pam_wifi_term_receiver->rx_fifo.rd = 0;
		pam_wifi_term_receiver->rx_fifo.wr = 0;
	}
#endif
	pam_wifi_term_receiver->state = TRUE;

	return TRUE;
}

static u32 pam_wifi_fifo_receiver_hal_close(enum pam_wifi_term_id id)
{
	int i = 0;
	struct pam_wifi_receiver *pam_wifi_term_receiver = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_ul_fifo_receiver_dev.term_receiver[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_receiver = &(pam_wifi_ul_fifo_receiver_dev.term_receiver[i]);

	pam_wifi_set_rx_fifo_total_depth(pam_wifi_term_receiver->fifo_reg_base, 0);
	pam_wifi_set_tx_fifo_total_depth(pam_wifi_term_receiver->fifo_reg_base, 0);

	//For the IPA_INT_EN_BIT_GROUP
	#if 1
	pam_wifi_disable_int_bit(pam_wifi_term_receiver->fifo_reg_base, PAMWIFI_INT_EN_BIT_GROUP);
	#endif

	pam_wifi_term_receiver->state = FALSE;

	return TRUE;
}

static u32 pam_wifi_fifo_receiver_hal_reset_fifo(enum pam_wifi_term_id id)
{
	int i = 0;
	struct pam_wifi_receiver *pam_wifi_term_receiver = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_ul_fifo_receiver_dev.term_receiver[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_receiver = &(pam_wifi_ul_fifo_receiver_dev.term_receiver[i]);

	pam_wifi_set_rx_fifo_total_depth(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->rx_fifo.depth);
	pam_wifi_set_rx_fifo_addr(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->rx_fifo.fifo_base_addr_l,
		pam_wifi_term_receiver->rx_fifo.fifo_base_addr_h);

	pam_wifi_set_tx_fifo_total_depth(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->tx_fifo.depth);
	pam_wifi_set_tx_fifo_addr(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->tx_fifo.fifo_base_addr_l,
		pam_wifi_term_receiver->tx_fifo.fifo_base_addr_h);

	pam_wifi_update_rx_fifo_rptr(pam_wifi_term_receiver->fifo_reg_base, 0);
	pam_wifi_update_rx_fifo_wptr(pam_wifi_term_receiver->fifo_reg_base,
		pam_wifi_term_receiver->tx_fifo.depth);

	pam_wifi_update_tx_fifo_rptr(pam_wifi_term_receiver->fifo_reg_base, 0);
	pam_wifi_update_tx_fifo_wptr(pam_wifi_term_receiver->fifo_reg_base, 0);
	//For the IPA_INT_EN_BIT_GROUP
#if 1
	pam_wifi_disable_int_bit(pam_wifi_term_receiver->fifo_reg_base, PAMWIFI_INT_EN_BIT_GROUP);
#endif
	pam_wifi_term_receiver->rx_fifo.rd = 0;
	pam_wifi_term_receiver->rx_fifo.wr = pam_wifi_term_receiver->tx_fifo.depth;
	pam_wifi_term_receiver->tx_fifo.rd = 0;
	pam_wifi_term_receiver->tx_fifo.wr = 0;

	pam_wifi_term_receiver->state = TRUE;

	return TRUE;
}

static u32 pam_wifi_fifo_receiver_hal_set_rx_depth(enum pam_wifi_term_id id, u32 depth)
{
	u32 i = 0, ret = 0;
	struct pam_wifi_receiver *pam_wifi_term_receiver = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_ul_fifo_receiver_dev.term_receiver[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_receiver = &(pam_wifi_ul_fifo_receiver_dev.term_receiver[i]);

	ret = pam_wifi_set_rx_fifo_total_depth(pam_wifi_term_receiver->fifo_reg_base, depth);

	pam_wifi_term_receiver->rx_fifo.rd = 0;
	pam_wifi_update_rx_fifo_rptr(pam_wifi_term_receiver->fifo_reg_base, 0);

#if 1
	if (pam_wifi_term_receiver->is_dma) {
		pam_wifi_term_receiver->rx_fifo.wr = depth;
		pam_wifi_init_receiver_rx_fifo_node(id,
			(struct sipa_node_description_tag *)((u64)pam_wifi_term_receiver->rx_fifo.fifo_base_addr_l |
			((u64)pam_wifi_term_receiver->rx_fifo.fifo_base_addr_h << 32)),
			pam_wifi_term_receiver->rx_fifo.depth);
	} else {
		pam_wifi_term_receiver->rx_fifo.wr = 0;
	}
#endif
	pam_wifi_update_rx_fifo_wptr(pam_wifi_term_receiver->fifo_reg_base,
			pam_wifi_term_receiver->rx_fifo.wr);

	return ret;
}

static u32 pam_wifi_fifo_receiver_hal_set_tx_depth(enum pam_wifi_term_id id, u32 depth)
{
	u32 i = 0, ret = 0;
	struct pam_wifi_receiver *pam_wifi_term_receiver = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_ul_fifo_receiver_dev.term_receiver[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_receiver = &(pam_wifi_ul_fifo_receiver_dev.term_receiver[i]);

	pam_wifi_update_tx_fifo_rptr(pam_wifi_term_receiver->fifo_reg_base, 0);
	pam_wifi_update_tx_fifo_wptr(pam_wifi_term_receiver->fifo_reg_base, 0);

	ret = pam_wifi_set_tx_fifo_total_depth(pam_wifi_term_receiver->fifo_reg_base, depth);
	pam_wifi_term_receiver->tx_fifo.rd = 0;
	pam_wifi_term_receiver->tx_fifo.wr = 0;

	return ret;
}


//=====================================PAM WIFI related fifo function========================================
static u32 pam_wifi_receiver_recv_pkt_from_fifo(struct pam_wifi_receiver *receiver_cfg, struct data_pkt_tag *pkt, u32 num)
{
	struct sipa_node_description_tag *node;
	u32 i = 0, ret = 0, index = 0, left_cnt = 0;

	node = (struct sipa_node_description_tag *)(((u64)(receiver_cfg->tx_fifo.fifo_base_addr_h) << 32) |
			(receiver_cfg->tx_fifo.fifo_base_addr_l));

	if (pam_wifi_get_tx_fifo_empty_status(receiver_cfg->fifo_reg_base)) {
		printk("fifo_id = %d is empty\n", receiver_cfg->pam_wifi_term_id);
		return FALSE;
	}

	left_cnt = pam_wifi_get_tx_fifo_filled_depth(receiver_cfg->fifo_reg_base);
	if (left_cnt < num) {
		printk("fifo_id = %d don't have enough space, only have %d nodes\n", receiver_cfg->pam_wifi_term_id, left_cnt);
		num = left_cnt;
	}

	for (i = 0; i < num; i++) {
		index = (receiver_cfg->tx_fifo.rd + i) & (receiver_cfg->tx_fifo.depth - 1);
		ipa_node_to_pkt(node + index, pkt + i);
	}

	receiver_cfg->tx_fifo.rd = (receiver_cfg->tx_fifo.rd + num) & PTR_MASK(receiver_cfg->tx_fifo.depth);
	ret = pam_wifi_update_tx_fifo_rptr(receiver_cfg->fifo_reg_base, receiver_cfg->tx_fifo.rd);
	if (ret == FALSE)
		printk("update tx fifo rptr fail !!!\n");

	return num;
}

/*****************************************************************************
 * Description: Receive Node from tx fifo.
 * Input:
 *   id: The FIFO id that need to be operated.
 *   pkt: The node that need to be stored address.
 *   num: The num of receive.
 * OUTPUT:
 *   The num that has be received from tx fifo successful.
 * Note:
*****************************************************************************/
static u32 pam_wifi_fifo_receiver_hal_recv(enum pam_wifi_term_id id , struct data_pkt_tag *node,
				u32 force_intr, u32 num)
{
	u32 i = 0, ret = 0;
	struct pam_wifi_receiver *pam_wifi_term_receiver = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_ul_fifo_receiver_dev.term_receiver[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_receiver = &(pam_wifi_ul_fifo_receiver_dev.term_receiver[i]);

	ret = pam_wifi_receiver_recv_pkt_from_fifo(pam_wifi_term_receiver, node, num);

	return ret;
}

static u32 pam_wifi_fifo_receiver_hal_set_interrupt_threshold(enum pam_wifi_term_id id, u32 enable,
				u32 cnt, void *cb)
{
	u32 i = 0, ret = 0;
	struct pam_wifi_receiver *pam_wifi_term_receiver = NULL;

	printk("%s\n", __func__);
	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_ul_fifo_receiver_dev.term_receiver[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_receiver = &(pam_wifi_ul_fifo_receiver_dev.term_receiver[i]);

	//For the IPA_TXFIFO_INT_THRESHOLD_ONESHOT_EN and IPA_TX_FIFO_THRESHOLD_EN
	#if 1
	if (enable) {
		pam_wifi_term_receiver->threshold_callback = cb;
		ret = pam_wifi_set_tx_fifo_interrupt_threshold(pam_wifi_term_receiver->fifo_reg_base, cnt);
		if (ret)
            {
                printk("%s (ret) true\n", __func__);
                //PAMWIFI_TXFIFO_INT_THRESHOLD_ONESHOT_EN is of no use for PAM WIFI from KAN Zheng
                ret = pam_wifi_enable_int_bit(pam_wifi_term_receiver->fifo_reg_base,PAMWIFI_TX_FIFO_THRESHOLD_EN);
            }
		else
            {
			    ret = FALSE;
                printk("%s (ret) FALSE\n", __func__);
            }
        printk("%s enable,fifo_reg_base:<0x%llx>\n", __func__,pam_wifi_term_receiver->fifo_reg_base);
	} else {
		pam_wifi_term_receiver->threshold_callback = NULL;
		ret = pam_wifi_disable_int_bit(pam_wifi_term_receiver->fifo_reg_base,PAMWIFI_TXFIFO_INT_THRESHOLD_ONESHOT_EN);
        printk("%s disable,fifo_reg_base:<0x%llx>\n", __func__,pam_wifi_term_receiver->fifo_reg_base);
	}
#endif

	return ret;
}

static u32 pam_wifi_fifo_receiver_hal_set_interrupt_timeout(enum pam_wifi_term_id id, u32 enable,
				u32 time, void *cb)
{
	u32 i = 0, ret = 0;
	struct pam_wifi_receiver *pam_wifi_term_receiver = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (id == pam_wifi_ul_fifo_receiver_dev.term_receiver[i].pam_wifi_term_id)
			break;
	}

	if (i >= pam_wifi_term_max) {
		printk("don't have this term id : %d\n", id);
		return FALSE;
	}

	pam_wifi_term_receiver = &(pam_wifi_ul_fifo_receiver_dev.term_receiver[i]);

    //For the IPA_TXFIFO_INT_DELAY_TIMER_SW_EN and IPA_TX_FIFO_DELAY_TIMER_EN
    #if 1
	if (enable) {
		pam_wifi_term_receiver->delay_timer_callback = cb;
		ret = pam_wifi_set_tx_fifo_interrupt_delay_timer(pam_wifi_term_receiver->fifo_reg_base, time);
		if (ret)
			ret = pam_wifi_enable_int_bit(pam_wifi_term_receiver->fifo_reg_base,
				PAMWIFI_TXFIFO_INT_DELAY_TIMER_SW_EN | PAMWIFI_TX_FIFO_DELAY_TIMER_EN);
		else
			ret = FALSE;
	} else {
		pam_wifi_term_receiver->delay_timer_callback = NULL;
		ret = pam_wifi_disable_int_bit(pam_wifi_term_receiver->fifo_reg_base,
				PAMWIFI_TXFIFO_INT_DELAY_TIMER_SW_EN);
	}
    #endif

    return ret;
}

#if 0
static u32 pam_wifi_receiver_init_ddr_fifo(void)
{
	//int i = 0;
	//struct sipa_node_description_tag *node_ptr = NULL;

#ifdef LPDDR4_TEST
	pam_wifi_ul_fifo_receiver_dev.term_receiver[0].tx_fifo.fifo_base_addr_l =
			(u32)(0x80000000);
	pam_wifi_ul_fifo_receiver_dev.term_receiver[0].tx_fifo.fifo_base_addr_h =
			(u32)(0x0);
#else
	pam_wifi_ul_fifo_receiver_dev.term_receiver[0].tx_fifo.fifo_base_addr_l =
			(u32)((u64)term_pam_wifi_inn_ul_tx_fifo_buf & 0xFFFFFFFFl);
	pam_wifi_ul_fifo_receiver_dev.term_receiver[0].tx_fifo.fifo_base_addr_h =
			(u32)((u64)term_pam_wifi_inn_ul_tx_fifo_buf >> 32);
#endif

	pam_wifi_ul_fifo_receiver_dev.term_receiver[0].rx_fifo.fifo_base_addr_l =
			(u32)((u64)term_pam_wifi_inn_ul_rx_fifo_buf & 0xFFFFFFFFl);
	pam_wifi_ul_fifo_receiver_dev.term_receiver[0].rx_fifo.fifo_base_addr_h =
			(u32)((u64)term_pam_wifi_inn_ul_rx_fifo_buf >> 32);
    #if 0
    //Where can i use the term_pam_wifi_inn_ul_data_buf???
    memset(term_pam_wifi_inn_ul_data_buf, 0x88, sizeof(term_pam_wifi_inn_ul_data_buf));
	node_ptr = (struct sipa_node_description_tag *)term_pam_wifi_inn_ul_tx_fifo_buf;
	for (i = 0; i < TERM_WIFI_UL_TX_FIFO_DEPTH; i++) {
		pam_term_wifi_ul_def_node.address = (u64)(term_pam_wifi_inn_ul_data_buf[i]);
		memcpy((node_ptr + i), &pam_term_wifi_ul_def_node, sizeof(pam_term_wifi_ul_def_node));
	}
    #endif
	return 1;
}
#endif

u32 pam_wifi_receiver_fifo_init(void)
{

	pam_wifi_ul_fifo_receiver_dev.recv_ops.open =
		pam_wifi_fifo_receiver_hal_open;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.close =
		pam_wifi_fifo_receiver_hal_close;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.reset =
	pam_wifi_fifo_receiver_hal_reset_fifo;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_rx_depth =
		pam_wifi_fifo_receiver_hal_set_rx_depth;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_tx_depth =
		pam_wifi_fifo_receiver_hal_set_tx_depth;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.recv =
		pam_wifi_fifo_receiver_hal_recv;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_interrupt_threshold =
		pam_wifi_fifo_receiver_hal_set_interrupt_threshold;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_interrupt_timeout =
		pam_wifi_fifo_receiver_hal_set_interrupt_timeout;
	/*

	//pam_wifi_ul_fifo_receiver_dev.recv_ops.enable_flowctrl_interrupt =pam_wifi_cp0_fifo_receiver_hal_enable_flowctrl_interrupt;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.get_left_cnt =
		pam_wifi_cp0_fifo_receiver_hal_get_left_cnt;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.put =
		pam_wifi_cp0_fifo_receiver_hal_put;

	//pam_wifi_ul_fifo_receiver_dev.recv_ops.set_interrupt_drop_packet = pam_wifi_cp0_fifo_receiver_hal_set_interrupt_drop_packet;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_interrupt_error_code =
		pam_wifi_cp0_fifo_receiver_hal_set_interrupt_error_code;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_interrupt_intr =
		pam_wifi_cp0_fifo_receiver_hal_set_interrupt_intr;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_interrupt_txfifo_full =
		pam_wifi_cp0_fifo_receiver_hal_set_interrupt_txfifo_full;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_interrupt_txfifo_overflow =
		pam_wifi_cp0_fifo_receiver_hal_set_interrupt_txfifo_overflow;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.get_rx_fifo_wr_rd_ptr =
		pam_wifi_cp0_fifo_receiver_hal_get_rx_ptr;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.get_tx_fifo_wr_rd_ptr =
		pam_wifi_cp0_fifo_receiver_hal_get_tx_ptr;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.get_filled_depth =
		pam_wifi_cp0_fifo_receiver_hal_get_filled_depth;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.get_full_empty_status =
		pam_wifi_cp0_fifo_receiver_hal_get_full_empty_status;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_rx_tx_fifo_wr_rd_ptr =
		pam_wifi_cp0_fifo_receiver_hal_set_rx_tx_fifo_wr_rd_ptr;

	pam_wifi_ul_fifo_receiver_dev.recv_ops.set_cur_dst_term =
		pam_wifi_cp0_fifo_receiver_hal_set_src_dst_term;

    */
	//pam_wifi_receiver_init_ddr_fifo();
	return TRUE;
}

#if 0
static struct pam_wifi_sender *pam_wifi_get_sender_instance(enum pam_wifi_term_id id)
{
	int i = 0;
	struct pam_wifi_sender *ipa_send = NULL;

	for (i = 0; i < pam_wifi_term_max; i++) {
		if (pam_wifi_dl_fifo_sender_dev.term_sender[i].pam_wifi_term_id == id) {
			ipa_send = (struct pam_wifi_sender *)(&(pam_wifi_dl_fifo_sender_dev.term_sender[i]));
            printk("pam_wifi_get_sender_instance i:<%d>!!\n",i);
            break;
		}
	}

	return ipa_send;
}
#endif

u32 pam_wifi_enable(void)
{
	enable_ul_free_fifo();
	//enable_ul_fill_fifo();
	//enbale_dl_free_fifo();
	enbale_dl_fill_fifo_type1();
	enbale_dl_fill_fifo_type2();
	enbale_dl_fill_fifo_type3();
	enbale_dl_fill_fifo_type4();
	enable_dl_miss();

	return TRUE;
}

u32 pam_wifi_disable(void)
{
	disable_ul_free_fifo();
	//disable_ul_fill_fifo();
	//disable_dl_free_fifo();
	disable_dl_fill_fifo_type1();
	disable_dl_fill_fifo_type2();
	disable_dl_fill_fifo_type3();
	disable_dl_fill_fifo_type4();
	disable_dl_index_miss();

	return TRUE;
}

/*
void config_tos_prio(struct pam_wifi_tos_prio pam_wifi_tos_prio_value)
{
    u32 temp = 0;
    temp = readl_relaxed((void *)REG_TOS_PRIO);
    temp &= ~REG_TOS_PRIO_MASK;
    temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_2_1(pam_wifi_tos_prio_value.tos_prio_2_1);
    temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_2_0(pam_wifi_tos_prio_value.tos_prio_2_0);
    temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_1_1(pam_wifi_tos_prio_value.tos_prio_1_1);
    temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_1_0(pam_wifi_tos_prio_value.tos_prio_1_0);
    temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_0_1(pam_wifi_tos_prio_value.tos_prio_0_1);
    temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_0_0(pam_wifi_tos_prio_value.tos_prio_0_0);
    writel_relaxed(temp, (void *)REG_TOS_PRIO);
}*/

/*****************************************************************************/
/** \ingroup  HWDRVR_COM                                                                 */
/** This function sets register specific field(1 or multiple bits) to all one   */
/*****************************************************************************/
void set_reg_bits_all_one(u64 u4_addr, u32 mask)
{
    u32 u4_temp;
    /* Read the value into a local var */
    u4_temp = readl_relaxed((void *)u4_addr);

    /* set the value to one at bit positions */
    u4_temp |= mask;

   /* Set the correct value */
   writel_relaxed(u4_temp, (void *)u4_addr);
}
EXPORT_SYMBOL(set_reg_bits_all_one);

/*****************************************************************************/
/** \ingroup  HWDRVR_COM                                                     */
/** This function clears register specific field to all zero             */
/*****************************************************************************/
void clear_reg_bits(u64 u4_addr, u32 mask)
{
     u32 u4_temp;

     /* Read the value into a local var */
     u4_temp = readl_relaxed((void *)u4_addr);

     /* clear the value at bit positions */
     u4_temp &= ~mask;

     /* Set the correct value */
     writel_relaxed(u4_temp, (void *)u4_addr);
}

/**
*******************************************************************************
* \ingroup  HWDRVR_COM
* This function sets the value corresponding to a particular bit position
* in a HW register to the given bit value
*******************************************************************************
*/
void set_reg_bits_to_val(u64 u4_addr, u32 u4_mask, u32 u4_lsb, u32 u4_value)
{
    u32 u4_temp;

    /* Read the value into a local var */
    u4_temp = readl_relaxed((void *)u4_addr);

    /* Clear the value at bit positions */
    u4_temp &= ~u4_mask;

    /* Update the local variable */
    u4_temp |= ((u4_value << u4_lsb) & u4_mask);

    /* Set the correct value */
    writel_relaxed(u4_temp, (void *)u4_addr);
}

u32 get_reg_bits_to_val(u64 u4_addr, u32 u4_mask, u32 u4_lsb)
{
    u32 u4_temp;

    /* Read the value into a local var */
    u4_temp = readl_relaxed((void *)u4_addr);

    u4_temp &= u4_mask;

    /* Update the local variable */
    u4_temp = (u4_temp>>u4_lsb);

    /* Set the correct value */
    return u4_temp;
}

/**
*******************************************************************************
* \ingroup  HWDRVR_COM
* This function sets the value corresponding to a particular bit position
* in a HW register to the given bit value
*******************************************************************************
*/
u8 get_reg_bit(u64 u4_addr, u8 u1_lsb)
{
   u32 u4_temp = readl_relaxed((void *)u4_addr);

   return ((u4_temp >> u1_lsb) & BIT_(0));
}

u32 pam_wifi_get_buffer_timeout_val (void)
{
    return readl_relaxed((void *)REG_BUFFER_TIMEOUT_VAL);
}

void add_calib_delay(u32  delay)
{
    u32 i = 0;
    u32 j = 0;
    //38 is to be checked
    u32 delay_thresh = 38 * delay;

    for(i = 0; i < delay_thresh; i++)
    {
        j += pam_wifi_get_buffer_timeout_val();
    }
}

/**
*******************************************************************************
* \ingroup  HWDRVR_COM
* This function wait register specific field till it changes to desired value, or timeout.
* Return FALSE if timeout, return TRUE if register changes to desired value before timeout.
*******************************************************************************
*/
BOOLEAN wait_reg(u64 u4_addr, u32 u4_mask, u32 u4_lsb, u32 u4_value, u32 u4_microsec_timeout)
{
    u32 u4_temp, u4_timeout_cnt , u4_temp_cnt =0;
    u32 u4_worst_timeout_cnt = 100000;/*worst timeout count =10^5 , 10us per one, total 1s*/

    //if(0 == u4_microsec_timeout)
    //{
        u4_timeout_cnt = u4_worst_timeout_cnt;
    //}
    //else
    //{
    //    u4_timeout_cnt = u4_microsec_timeout/10 + 1;
    //}

    u4_temp = ((u4_value << u4_lsb) & u4_mask);

    while (u4_temp != (readl_relaxed((void *)u4_addr) & u4_mask))
    {
        if(u4_temp_cnt >= u4_timeout_cnt)
        {
            if(u4_temp_cnt >= u4_worst_timeout_cnt)
            {
                //SCI_ASSERT(0);
                printk("wait_reg return FALSE!!\n");
            }
            return FALSE;
        }

        add_calib_delay(1);/*10us*/
        u4_temp_cnt ++;
    }
    return TRUE;
}

BOOLEAN pam_wifi_table_lock(void)
{
    set_reg_bits_all_one(REG_CFG_START,BIT_PAM_WIFI_CFG_START_SOFT_TABLE_UPDATE_REQ);
    if (FALSE == wait_reg(REG_CFG_START, BIT_PAM_WIFI_CFG_START_PAM_WIFI_TABLE_RD_STOP,
	                            BIT_PAM_WIFI_CFG_START_PAM_WIFI_TABLE_RD_STOP_EN_MSB, 1, PAM_WIFI_HW_LOCK_TO))
	{
	    clear_reg_bits(REG_CFG_START, BIT_PAM_WIFI_CFG_START_SOFT_TABLE_UPDATE_REQ);

	    printk("pam_wifi_table_update access lock fail !!\n");
	    return FALSE;
	}
	return 1;
}

BOOLEAN pam_wifi_table_unlock(void)
{
    clear_reg_bits(REG_CFG_START, BIT_PAM_WIFI_CFG_START_SOFT_TABLE_UPDATE_REQ);
	return 1;
}

BOOLEAN pam_wifi_table_update(enum dl_fifo_type dl_fifo_type)
{
	if(pam_wifi_table_lock() == FALSE)
	{
		printk("%s pam_wifi_table_lock FALSE\n", __func__);
		return FALSE;
	}
	else
	{
		printk("%s pam_wifi_table_lock TRUE\n", __func__);
	}

	writel_relaxed(0x11da4540, (void *)PSEL_RAM1);
	writel_relaxed(0x00003322, (void *)(PSEL_RAM1+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x0c));

	writel_relaxed(0x44da4540,(void *)( PSEL_RAM2));
	writel_relaxed(0x00006655, (void *)(PSEL_RAM2+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM2+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM2+0x0c));

	writel_relaxed(0x00000000, (void *)PSEL_RAM5);
	writel_relaxed(0x00000000, (void *)PSEL_RAM5+0x04);
	writel_relaxed(0x00000000, (void *)PSEL_RAM5+0x08);
	writel_relaxed(0x00000000, (void *)PSEL_RAM5+0x0c);

	writel_relaxed(0x00000000, (void *)(PSEL_RAM3));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x0c));

	writel_relaxed(0x00000000, (void *)(PSEL_RAM4));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x0c));

	writel_relaxed(0x00000000, (void *)(PSEL_RAM6));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x0c));

	pam_wifi_table_unlock();
	return 1;
}

void configure_ddr_mapping_offset(u32 mapping_offset_l, u32 mapping_offset_h)
{
	writel_relaxed(mapping_offset_l, (void *)REG_DDR_MAPPING_OFFSET_L);
	writel_relaxed(mapping_offset_h, (void *)REG_DDR_MAPPING_OFFSET_H);
}

u32 check_pamwifi_ipa_fifo_status(void)
{
	u32 /*ipa_dl_fill_wr, ipa_dl_fill_rd, ipa_dl_free_wr, ipa_dl_free_rd,
			ipa_ul_fill_wr, ipa_ul_fill_rd, ipa_ul_free_wr, ipa_ul_free_rd,*/
			pamwifi_dl_type1_wr, pamwifi_dl_type1_rd,
			pamwifi_dl_type2_wr, pamwifi_dl_type2_rd,
			pamwifi_dl_type3_wr, pamwifi_dl_type3_rd,
			pamwifi_dl_type4_wr, pamwifi_dl_type4_rd,
			pamwifi_dl_free_wr, pamwifi_dl_free_rd,
			pamwifi_ul_fill_wr, pamwifi_ul_fill_rd,
			pamwifi_ul_free_wr, pamwifi_ul_free_rd, value;

	pamwifi_dl_type1_wr = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_dl_type1_rd = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_dl_type2_wr = (readl_relaxed((void *)(PSEL_DL_TYPE2 + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_dl_type2_rd = (readl_relaxed((void *)(PSEL_DL_TYPE2 + PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_dl_type3_wr = (readl_relaxed((void *)(PSEL_DL_TYPE3 + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_dl_type3_rd = (readl_relaxed((void *)(PSEL_DL_TYPE3 + PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_dl_type4_wr = (readl_relaxed((void *)(PSEL_DL_TYPE4 + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_dl_type4_rd = (readl_relaxed((void *)(PSEL_DL_TYPE4 + PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_dl_free_wr = (readl_relaxed((void *)(PSEL_DL_FREE+ PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_dl_free_rd = (readl_relaxed((void *)(PSEL_DL_FREE+ PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_ul_fill_wr = (readl_relaxed((void *)(PSEL_UL+ PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_ul_fill_rd = (readl_relaxed((void *)(PSEL_UL+ PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_ul_free_wr = (readl_relaxed((void *)(PSEL_UL + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	pamwifi_ul_free_rd = (readl_relaxed((void *)(PSEL_UL + PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
#if 0
	ipa_dl_fill_wr = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	ipa_dl_fill_rd = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
	ipa_dl_free_wr = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	ipa_dl_free_rd = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
	ipa_ul_fill_wr = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	ipa_ul_fill_rd = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
	ipa_ul_free_wr = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_TX_FIFO_RD)) & 0x0000FFFF);
	ipa_ul_free_rd = (readl_relaxed((void *)(PSEL_DL_TYPE1 + PAMWIFI_COMMON_RX_FIFO_RD)) & 0x0000FFFF);
#endif

	value = (pamwifi_dl_type1_wr == pamwifi_dl_type1_rd) & (pamwifi_dl_type2_wr == pamwifi_dl_type2_rd) &
		(pamwifi_dl_type3_wr == pamwifi_dl_type3_rd) & (pamwifi_dl_type4_wr == pamwifi_dl_type4_rd) &
		(pamwifi_dl_free_wr == pamwifi_dl_free_rd) & (pamwifi_ul_fill_wr == pamwifi_ul_fill_rd) &
		(pamwifi_ul_free_wr == pamwifi_ul_free_rd) /*& (ipa_dl_fill_wr == ipa_dl_fill_rd) &
		(ipa_dl_free_wr == ipa_dl_free_rd) & (ipa_ul_fill_wr == ipa_ul_fill_rd) &
		(ipa_ul_free_wr == ipa_ul_free_rd)*/;
	return value;
}
EXPORT_SYMBOL(check_pamwifi_ipa_fifo_status);

dma_addr_t dl_type1_phy_addr;
dma_addr_t dl_type2_phy_addr;
dma_addr_t dl_type3_phy_addr;
dma_addr_t dl_type4_phy_addr;
dma_addr_t dl_free_phy_addr;
dma_addr_t ul_tx_phy_addr;
dma_addr_t ul_rx_phy_addr;

void *dl_type1_virt_addr;
void * dl_type2_virt_addr;
void * dl_type3_virt_addr;
void * dl_type4_virt_addr;
void * dl_free_virt_addr;
void * ul_tx_virt_addr;
void * ul_rx_virt_addr;

u8 *term_pam_wifi_miss_node_infor = NULL;
dma_addr_t term_pam_wifi_miss_node_infor_phy_addr;

u32 * pam_wifi_msdu_header_info;
dma_addr_t term_pam_wifi_msdu_header_buf;
u32 term_pam_wifi_msdu_header_buf_tmp[MAX_MSDU_NUMBER*MAX_ONE_MSDU_LENGTH] =
{
    0x00000000,0x000b0000,0x000000F0,0x00000000,0x30303030,
    //0xFFFFFFFF,0xFF0bFFFF,0xFFFFFFFF,0xFFFFFFFF,0x30303030,//Just for test
    0x72fa3030,0xae7a813f,0x11110008,0x11111111,0x11111111,
    0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,
    0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,
    0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,
};

#define    REG_PAM_WIFI_PAM_WIFI_INDEX_MISS_ADDR_L                     ( PAM_WIFI_REG_BASE + 0x00A4 )
#define    REG_PAM_WIFI_PAM_WIFI_INDEX_MISS_ADDR_H                     ( PAM_WIFI_REG_BASE + 0x00A8 )

void config_index_miss_addr(struct platform_device *pdev)
{
	term_pam_wifi_miss_node_infor = dma_alloc_coherent(&pdev->dev, 10*sizeof(struct sipa_node_description_tag), &term_pam_wifi_miss_node_infor_phy_addr, GFP_KERNEL);
	writel_relaxed((u32)((u64)term_pam_wifi_miss_node_infor_phy_addr & 0xFFFFFFFFl), (void *)REG_PAM_WIFI_PAM_WIFI_INDEX_MISS_ADDR_L);
	writel_relaxed((u32)((u64)term_pam_wifi_miss_node_infor_phy_addr >> 32), (void *)REG_PAM_WIFI_PAM_WIFI_INDEX_MISS_ADDR_H);
}

#define    REG_PAM_WIFI_PAM_WIFI_TOS_PRIO                              ( PAM_WIFI_REG_BASE + 0x0098 )
#define    REG_PAM_WIFI_PAM_WIFI_TOS_PRIO_MASK                              0x0003FFFF
void config_tos_prio(void)
{
#if 0
	u32 temp = 0;
	temp = readl_relaxed((void *)REG_PAM_WIFI_PAM_WIFI_TOS_PRIO);
	temp &= ~REG_PAM_WIFI_PAM_WIFI_TOS_PRIO_MASK;
	temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_0_0(0x0);
	temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_0_1(0x3);
	temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_1_0(0x1);
	temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_1_1(0x2);
	temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_2_0(0x7);
	temp |= BIT_PAM_WIFI_TOS_PRIO_TOS_PRIO_2_1(0x6);
	writel_relaxed(temp, (void *)REG_PAM_WIFI_PAM_WIFI_TOS_PRIO);
#endif
}
#if 0
//u8 *ipi_clr_base = NULL;
//dma_addr_t ipi_clr_base_phy;
extern void clear_mh_buffer(void *buffer);
unsigned long pamwifi_virt_to_phys(struct device *dev, void *buffer, size_t size,
			      enum dma_data_direction direction)
{
	dma_addr_t pa = 0;

again:
	if (direction == DMA_FROM_DEVICE)
		clear_mh_buffer(buffer);

	mb();

	pa = dma_map_single(dev, buffer, size, direction);


	if (unlikely(dma_mapping_error(dev, pa))) {
		wl_err("%s: dma_mapping_error\n", __func__);
		goto again;
	}

	return pa;
}
#endif

extern struct sprdwl_intf_sc2355 g_intf_sc2355;
void pam_wifi_msdu_init(struct sprdwl_priv *priv)
{
#define MSDU_HEADER_LEN 16
	struct sprdwl_vif *vif;
	struct tx_msdu_dscr  *tmp_msdu_header;
	unsigned char *msdu_dscr;
	int i = 0, j = 0;

	vif = mode_to_vif(priv, SPRDWL_MODE_AP);
	if (!vif) {
		printk("get vif fail!");
		return;
		}

	if (!pam_wifi_msdu_header_info) {
		wl_err("pamwifi msdu dma_alloc_coherent err\n");
		return;
	}

	msdu_dscr = (unsigned char *)pam_wifi_msdu_header_info;
	tmp_msdu_header = (struct tx_msdu_dscr *)(msdu_dscr + 5);

#if 0
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j <4; j++)
		{
			((struct tx_msdu_dscr  *)((char *)msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr)))->common.type = SPRDWL_TYPE_DATA;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->common.direction_ind = 0;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->common.need_rsp = 0;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->common.interface = vif->ctx_id;
			//msdu_dscr->pkt_len = cpu_to_le16(skb->len - DSCR_LEN);
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->offset = DSCR_LEN;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->tx_ctrl.sw_rate = 0;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->tx_ctrl.wds = 0;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->tx_ctrl.swq_flag = 0;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->tx_ctrl.rsvd = 0;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->tx_ctrl.next_buffer_type = 0;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->tx_ctrl.pcie_mh_readcomp = 1;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->buffer_info.msdu_tid = 0;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->buffer_info.mac_data_offset = 0;
			(msdu_dscr + (i * 8 + j) * sizeof(struct tx_msdu_dscr))->sta_lut_index = i;
		}
		(msdu_dscr + (i * 8 + 0) * sizeof(struct tx_msdu_dscr))->buffer_info.msdu_tid = prio_0;
		(msdu_dscr + (i * 8 + 1) * sizeof(struct tx_msdu_dscr))->buffer_info.msdu_tid = prio_1;
		(msdu_dscr + (i * 8 + 2) * sizeof(struct tx_msdu_dscr))->buffer_info.msdu_tid = prio_1;
		(msdu_dscr + (i * 8 + 3) * sizeof(struct tx_msdu_dscr))->buffer_info.msdu_tid = prio_6;
		sprdwl_hex_dump("msdu dump:", (unsigned char *)(msdu_dscr + i*8*sizeof(struct tx_msdu_dscr)), sizeof(struct tx_msdu_dscr)*4);
	}
#endif
	for (i = 0; i < 8; i++) {
		for (j = 0; j <4; j++) {
				//*(msdu_dscr + 4 + (i * 8 + j) * MSDU_HEADER_LEN) = 1 << 7;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->common.type = SPRDWL_TYPE_DATA;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->common.direction_ind = 0;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->common.need_rsp = 0;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->common.interface = vif->ctx_id;
				//msdu_dscr->pkt_len = cpu_to_le16(skb->len - DSCR_LEN);
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->offset = DSCR_LEN;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->tx_ctrl.sw_rate = 0;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->tx_ctrl.wds = 0;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->tx_ctrl.swq_flag = 0;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->tx_ctrl.rsvd = 0;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->tx_ctrl.next_buffer_type = 0;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->tx_ctrl.pcie_mh_readcomp = 1;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->buffer_info.msdu_tid = 0;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->buffer_info.mac_data_offset = 0;
				((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + j) * MSDU_HEADER_LEN))->sta_lut_index = i + 6;
			}
			((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + 0) * MSDU_HEADER_LEN))->buffer_info.msdu_tid = prio_0;
			((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + 1) * MSDU_HEADER_LEN))->buffer_info.msdu_tid = prio_1;
			((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + 2) * MSDU_HEADER_LEN))->buffer_info.msdu_tid = prio_4;
			((struct tx_msdu_dscr  *)((char *)tmp_msdu_header + (i * 4 + 3) * MSDU_HEADER_LEN))->buffer_info.msdu_tid = prio_6;
			sprdwl_hex_dump("msdu dump:", msdu_dscr, 4*16);
	}
}

//u8 router_table_bitmap[256];
void pam_wifi_update_router_table(struct sprdwl_sta_lut_ind *sta_lut, struct sprdwl_priv *priv, int flag)
{
	struct sprdwl_vif *vif;
	u32 da_l = 0, da_h = 0, sa_l = 0, sa_h = 0/*, tos*/;
	int i;
	u8 router_lut;
	u32 ctx_id;

	vif = mode_to_vif(priv, SPRDWL_MODE_AP);
	router_lut = sta_lut->sta_lut_index - 6;

	da_l = (u32)(sta_lut->ra[0] |(sta_lut->ra[1] << 8) |(sta_lut->ra[2] << 16) |
		(sta_lut->ra[3] << 24));
	da_h = (u32)(sta_lut->ra[4] | (sta_lut->ra[5] << 8));
	sa_l = (u32)(vif->ndev->dev_addr[0] |(vif->ndev->dev_addr[1] << 8) |(vif->ndev->dev_addr[2] << 16) |
		(vif->ndev->dev_addr[3] << 24));
	sa_h = (u32)(vif->ndev->dev_addr[4]  | (vif->ndev->dev_addr[5] << 8));
	ctx_id = (u32)(vif->ctx_id << 29);
	if(pam_wifi_table_lock() == FALSE)
        {
            printk("%s pam_wifi_table_lock FALSE\n", __func__);
        }
    else
        {
            printk("%s pam_wifi_table_lock TRUE\n", __func__);
        }


	if (flag == 0) {
		for(i = 0; i < 8; i++) {
			//tos = i << 5;
			writel_relaxed(da_l, (void *)(PSEL_RAM1 + 16 * (router_lut * 8 + i)));
			writel_relaxed(da_h, (void *)(PSEL_RAM1+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(ctx_id, (void *)(PSEL_RAM1+0x0c + 16 * (router_lut * 8 + i)));
			writel_relaxed(sa_l, (void *)(PSEL_RAM2 + 16 * (router_lut * 8 + i)));
			writel_relaxed(sa_h, (void *)(PSEL_RAM2+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM2+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM2+0x0c + 16 * (router_lut * 8 + i)));
			//writel_relaxed(tos, (void *)(PSEL_RAM5 + 16 * (router_lut * 8 + i)));
			//writel_relaxed(0x00000000, (void *)(PSEL_RAM5+0x04 + 16 * (router_lut * 8 + i)));
			//writel_relaxed(0x00000000, (void *)(PSEL_RAM5+0x08 + 16 * (router_lut * 8 + i)));
			//writel_relaxed(0x00000000, (void *)(PSEL_RAM5+0x0c + 16 * (router_lut * 8 + i)));

			writel_relaxed(da_l, (void *)(PSEL_RAM3+ 16 * (router_lut * 8 + i)));
			writel_relaxed(da_h, (void *)(PSEL_RAM3+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(ctx_id, (void *)(PSEL_RAM3+0x0c + 16 * (router_lut * 4 + i)));
			writel_relaxed(sa_l, (void *)(PSEL_RAM4 + 16 * (router_lut * 8 + i)));
			writel_relaxed(sa_h, (void *)(PSEL_RAM4+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x0c + 16 * (router_lut * 8 + i)));
			//writel_relaxed(tos, (void *)(PSEL_RAM6 + 16 * (router_lut * 8 + i)));
			//writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x04 + 16 * (router_lut * 8 + i)));
			//writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x08 + 16 * (router_lut * 8 + i)));
			//writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x0c + 16 * (router_lut * 8 + i)));
		}
		writel_relaxed(0x00000000 + router_lut * 4, (void *)(PSEL_RAM5 + 4 * (router_lut * 8 + 0)));
		writel_relaxed(0x00001002 + router_lut * 4, (void *)(PSEL_RAM5 + 4 * (router_lut * 8 + 1)));
		writel_relaxed(0x00002002 + router_lut * 4, (void *)(PSEL_RAM5 + 4 * (router_lut * 8 + 2)));
		writel_relaxed(0x00003000 + router_lut * 4, (void *)(PSEL_RAM5 + 4 * (router_lut * 8 + 3)));
		writel_relaxed(0x00004004 + router_lut * 4, (void *)(PSEL_RAM5 + 4 * (router_lut * 8 + 4)));
		writel_relaxed(0x00005004 + router_lut * 4, (void *)(PSEL_RAM5 + 4 * (router_lut * 8 + 5)));
		writel_relaxed(0x00006006 + router_lut * 4, (void *)(PSEL_RAM5 + 4 * (router_lut * 8 + 6)));
		writel_relaxed(0x00007006 + router_lut * 4, (void *)(PSEL_RAM5 + 4 * (router_lut * 8 + 7)));

		writel_relaxed(0x00000000 + router_lut * 4, (void *)(PSEL_RAM6 + 4 * (router_lut * 8 + 0)));
		writel_relaxed(0x00001002 + router_lut * 4, (void *)(PSEL_RAM6 + 4 * (router_lut * 8 + 1)));
		writel_relaxed(0x00002002 + router_lut * 4, (void *)(PSEL_RAM6 + 4 * (router_lut * 8 + 2)));
		writel_relaxed(0x00003000 + router_lut * 4, (void *)(PSEL_RAM6 + 4 * (router_lut * 8 + 3)));
		writel_relaxed(0x00004004 + router_lut * 4, (void *)(PSEL_RAM6 + 4 * (router_lut * 8 + 4)));
		writel_relaxed(0x00005004 + router_lut * 4, (void *)(PSEL_RAM6 + 4 * (router_lut * 8 + 5)));
		writel_relaxed(0x00006006 + router_lut * 4, (void *)(PSEL_RAM6 + 4 * (router_lut * 8 + 6)));
		writel_relaxed(0x00007006 + router_lut * 4, (void *)(PSEL_RAM6 + 4 * (router_lut * 8 + 7)));
	}else if (flag == 1) {
		for(i = 0; i < 8; i++) {
			writel_relaxed(0x00000000, (void *)(PSEL_RAM1 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x0c + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM2 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM2+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM2+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM2+0x0c + 16 * (router_lut * 8 + i)));
			/*writel_relaxed(0x00000000, (void *)(PSEL_RAM5 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM5+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM5+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM5+0x0c + 16 * (router_lut * 8 + i)));*/
			writel_relaxed(0x00000000, (void *)(PSEL_RAM5 + 4 * (router_lut * 8 + i)));

			writel_relaxed(0x00000000, (void *)(PSEL_RAM3+ 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x0c + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM4 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x0c + 16 * (router_lut * 8 + i)));
			/*writel_relaxed(0x00000000, (void *)(PSEL_RAM6 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x04 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x08 + 16 * (router_lut * 8 + i)));
			writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x0c + 16 * (router_lut * 8 + i)));*/
			writel_relaxed(0x00000000, (void *)(PSEL_RAM6 + 4 * (router_lut * 8 + i)));
		}
	}

	/*eg. da:40:45:da:11:22:33
	writel_relaxed(0x11da4540, (void *)PSEL_RAM1);
	writel_relaxed(0x00003322, (void *)(PSEL_RAM1+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x0c));	*/

	/*
	writel_relaxed(0x11da4540, (void *)PSEL_RAM1);
	writel_relaxed(0x00003322, (void *)(PSEL_RAM1+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM1+0x0c));

	writel_relaxed(0x44da4540,(void *)( PSEL_RAM2));
	writel_relaxed(0x00006655, (void *)(PSEL_RAM2+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM2+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM2+0x0c));

	writel_relaxed(0x00000000, (void *)PSEL_RAM5);
	writel_relaxed(0x00000000, (void *)PSEL_RAM5+0x04);
	writel_relaxed(0x00000000, (void *)PSEL_RAM5+0x08);
	writel_relaxed(0x00000000, (void *)PSEL_RAM5+0x0c);

	writel_relaxed(0x00000000, (void *)(PSEL_RAM3));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM3+0x0c));

	writel_relaxed(0x00000000, (void *)(PSEL_RAM4));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM4+0x0c));

	writel_relaxed(0x00000000, (void *)(PSEL_RAM6));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x04));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x08));
	writel_relaxed(0x00000000, (void *)(PSEL_RAM6+0x0c));
	*/

	/*ether_addr_copy(da, sta_lut->ra);
	ether_addr_copy(sa, vif->ndev->dev_addr);*/

	pam_wifi_table_unlock();
}

void ipa_to_pam_wifi_init(struct sprdwl_priv *priv, struct platform_device *pdev)
{
	u64 temp = 0;
	int i;
	//u32 ipi_clr_base_addrl = 0;
	//u32 ipi_clr_base_addrh = 0;
	u32 value_index_search_depth = 8;
	u32 value_cfg_ul_ap_filled_buffer_watermark = 1;
	u32 value_cfg_ul_cp_filled_buffer_watermark = 1;
	u32 value_cfg_ul_ap_free_buffer_watermark = 1;
	u32 value_cfg_ul_cp_free_buffer_watermark = 1;
	u32 value_cfg_dl_cp_type1_buffer_watermark = 1;
	u32 value_cfg_dl_cp_type2_buffer_watermark = 1;
	u32 value_cfg_dl_cp_type3_buffer_watermark = 1;
	u32 value_cfg_dl_cp_type4_buffer_watermark = 1;
	u32 pam_tx_intr_threshold = 1 << 16;
	u32 pam_tx_intr_threshold_en = 2;
	u32 pam_tx_intr_threshold_delay = 0xffff;
	u32 pam_tx_intr_threshold_delay_en = 0;
	u32 temp_threshold_value;
	u32 depth;
	u32 node_info_config;
	u32 msdu_offset;
	u32 tmp_fifo_depth = 2048;

	pam_wifi_sender_fifo_init();
	config_index_miss_addr(pdev);
	config_tos_prio();

	//************************* PAM WIFI related configuration***************************************
	//*********Set the IPI interrupt related***********************
	//Set the IPI inter register related
	/*ipi_clr_base = dma_alloc_coherent(&pdev->dev,
											 sizeof(u32),
											 &ipi_clr_base_phy, GFP_KERNEL);
	memset(ipi_clr_base, 0x0, sizeof(u32));
	ipi_clr_base_addrl = (u32)(ipi_clr_base_phy & 0xffffffff);
	writel_relaxed(ipi_clr_base_addrl, (void *)REG_IPI_CLR_BASE_ADDRL);
	ipi_clr_base_addrh = (u32)((ipi_clr_base_phy >> 32) & 0xff);
	writel_relaxed(ipi_clr_base_addrh, (void *)REG_IPI_CLR_BASE_ADDRH);*/
	writel_relaxed(0xF8000010, (void *)REG_IPI_CLR_BASE_ADDRL);
	writel_relaxed(0x10003, (void *)REG_IPI_CLR_BASE_ADDRH);
	//**************************end*************************************************************

		/* IPA common FIFOs IRAM addresses */
	sipa_get_ep_info(SIPA_EP_WIFI, &priv->sipa_info);

	depth = priv->sipa_info.dl_fifo.fifo_depth;
	priv->sipa_params.recv_param.tx_enter_flowctrl_watermark = depth - depth / 4;
	priv->sipa_params.recv_param.tx_leave_flowctrl_watermark = depth / 2;
	priv->sipa_params.recv_param.flow_ctrl_cfg = 1;
	priv->sipa_params.send_param.flow_ctrl_irq_mode = 2;
	priv->sipa_params.send_param.tx_intr_threshold = 10;//priv->max_dl_pkts;
	priv->sipa_params.send_param.tx_intr_delay_us = 5;
	priv->sipa_params.recv_param.tx_intr_threshold = 10;
	priv->sipa_params.recv_param.tx_intr_delay_us = 5;
	priv->sipa_params.id = SIPA_EP_WIFI;
	//sipa_pam_connect(&priv->sipa_params, &priv->sipa_info);
	sipa_pam_connect(&priv->sipa_params);

#if 1
	writel_relaxed(priv->sipa_info.dl_fifo.tx_fifo_base_addr & PAM_MASK_LOWADDR32, (void *)REG_DL_AP_FILLED_FIFO_BASE_ADDRL);
	writel_relaxed((priv->sipa_info.dl_fifo.tx_fifo_base_addr >> PAM_BITS_LOWADDR32) & PAM_MASK_ADDR32_LSB, (void *)REG_DL_AP_FILLED_FIFO_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.dl_fifo.rx_fifo_base_addr & PAM_MASK_LOWADDR32, (void *)REG_DL_AP_FREE_FIFO_BASE_ADDRL);
	writel_relaxed((priv->sipa_info.dl_fifo.rx_fifo_base_addr >> PAM_BITS_LOWADDR32) & PAM_MASK_ADDR32_LSB, (void *)REG_DL_AP_FREE_FIFO_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.ul_fifo.tx_fifo_base_addr & PAM_MASK_LOWADDR32, (void *)REG_UL_AP_FREE_FIFO_BASE_ADDRL);
	writel_relaxed((priv->sipa_info.ul_fifo.tx_fifo_base_addr >> PAM_BITS_LOWADDR32) & PAM_MASK_ADDR32_LSB, (void *)REG_UL_AP_FREE_FIFO_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.ul_fifo.rx_fifo_base_addr & PAM_MASK_LOWADDR32, (void *)REG_UL_AP_FILLED_FIFO_BASE_ADDRL);
	writel_relaxed((priv->sipa_info.ul_fifo.rx_fifo_base_addr >> PAM_BITS_LOWADDR32) & PAM_MASK_ADDR32_LSB, (void *)REG_UL_AP_FILLED_FIFO_BASE_ADDRH);



	/* IPA common FIFOs registers */  /*to be modify*/
	writel_relaxed(priv->sipa_info.ul_fifo.fifo_sts_addr & PAM_MASK_LOWADDR32, (void *)REG_UL_AP_FREE_FIFO_STS_BASE_ADDRL);
	writel_relaxed(0, (void *)REG_UL_AP_FREE_FIFO_STS_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.ul_fifo.fifo_sts_addr & PAM_MASK_LOWADDR32, (void *)REG_UL_AP_FILLED_FIFO_STS_BASE_ADDRL);
	writel_relaxed(0, (void *)REG_UL_AP_FILLED_FIFO_STS_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.dl_fifo.fifo_sts_addr & PAM_MASK_LOWADDR32, (void *)REG_DL_AP_FILLED_FIFO_STS_BASE_ADDRL);
	writel_relaxed(0, (void *)REG_DL_AP_FILLED_FIFO_STS_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.dl_fifo.fifo_sts_addr & PAM_MASK_LOWADDR32, (void *)REG_DL_AP_FREE_FIFO_STS_BASE_ADDRL);
	writel_relaxed(0, (void *)REG_DL_AP_FREE_FIFO_STS_BASE_ADDRH);
#else
	writel_relaxed(priv->sipa_info.dl_fifo.tx_fifo_base_addr & PAM_MASK_LOWADDR32, (void *)REG_UL_AP_FREE_FIFO_BASE_ADDRL);
	writel_relaxed((priv->sipa_info.dl_fifo.tx_fifo_base_addr >> PAM_BITS_LOWADDR32) & PAM_MASK_ADDR32_LSB, (void *)REG_UL_AP_FREE_FIFO_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.dl_fifo.rx_fifo_base_addr & PAM_MASK_LOWADDR32, (void *)REG_UL_AP_FILLED_FIFO_BASE_ADDRL);
	writel_relaxed((priv->sipa_info.dl_fifo.rx_fifo_base_addr >> PAM_BITS_LOWADDR32) & PAM_MASK_ADDR32_LSB, (void *)REG_UL_AP_FILLED_FIFO_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.ul_fifo.tx_fifo_base_addr & PAM_MASK_LOWADDR32, (void *)REG_DL_AP_FILLED_FIFO_BASE_ADDRL);
	writel_relaxed((priv->sipa_info.ul_fifo.tx_fifo_base_addr >> PAM_BITS_LOWADDR32) & PAM_MASK_ADDR32_LSB, (void *)REG_DL_AP_FILLED_FIFO_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.ul_fifo.rx_fifo_base_addr & PAM_MASK_LOWADDR32, (void *)REG_DL_AP_FREE_FIFO_BASE_ADDRL);
	writel_relaxed((priv->sipa_info.ul_fifo.rx_fifo_base_addr >> PAM_BITS_LOWADDR32) & PAM_MASK_ADDR32_LSB, (void *)REG_DL_AP_FREE_FIFO_BASE_ADDRH);

	/* IPA common FIFOs registers */  /*to be modify*/
	writel_relaxed(priv->sipa_info.ul_fifo.fifo_sts_addr & PAM_MASK_LOWADDR32, (void *)REG_DL_AP_FREE_FIFO_STS_BASE_ADDRL);
	writel_relaxed(0, (void *)REG_DL_AP_FREE_FIFO_STS_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.ul_fifo.fifo_sts_addr & PAM_MASK_LOWADDR32, (void *)REG_DL_AP_FILLED_FIFO_STS_BASE_ADDRL);
	writel_relaxed(0, (void *)REG_DL_AP_FILLED_FIFO_STS_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.dl_fifo.fifo_sts_addr & PAM_MASK_LOWADDR32, (void *)REG_UL_AP_FILLED_FIFO_STS_BASE_ADDRL);
	writel_relaxed(0, (void *)REG_UL_AP_FILLED_FIFO_STS_BASE_ADDRH);

	writel_relaxed(priv->sipa_info.dl_fifo.fifo_sts_addr & PAM_MASK_LOWADDR32, (void *)REG_UL_AP_FREE_FIFO_STS_BASE_ADDRL);
	writel_relaxed(0, (void *)REG_UL_AP_FREE_FIFO_STS_BASE_ADDRH);
#endif

	//Set the Common fifo PAM WIFI Common_Tx_FIFO_AddrL/Common_Tx_FIFO_AddrH
	//**********************************UL Part******************************************************************
	//pcie_addr = virt_to_phys(term_pam_wifi_inn_ul_tx_fifo_buf);
	//ul_tx_virt_addr = dma_alloc_coherent(&pdev->dev, 10*sizeof(struct sipa_node_description_tag), &ul_tx_phy_addr, GFP_KERNEL);
	ul_tx_virt_addr = dma_alloc_coherent(&pdev->dev, tmp_fifo_depth*sizeof(dma_addr_t), &ul_tx_phy_addr, GFP_KERNEL);
	writel_relaxed((u32)(ul_tx_phy_addr & 0xFFFFFFFFl), (void *)(PSEL_UL+PAMWIFI_COMMON_TX_FIFO_ADDRL));
	writel_relaxed((u32)(ul_tx_phy_addr >> 32), (void *)(PSEL_UL+PAMWIFI_COMMON_TX_FIFO_ADDRH));
	pam_wifi_set_tx_fifo_total_depth(PSEL_UL, tmp_fifo_depth);
	//pam_wifi_set_rx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);
	pam_wifi_update_tx_fifo_rptr(PSEL_UL, 0);

	skb_queue_head_init(&priv->buffer_list);

	for(i = 0; i < 500; i++) {
		unsigned long pcie_addr = 0;
		struct sk_buff *skb = NULL/*, *temp_skb = NULL*/;
		//struct sipa_node_description_tag *sipa_node;
		//int *tmp_offset;

		skb = dev_alloc_skb(SPRDWL_MAX_DATA_RXLEN);

		if (skb) {
#if 0
			/*4+16*/
			if (skb_headroom(skb) < 20) {
				temp_skb = skb;
				wl_err("%s, realloc skb headroom!\n", __func__);
				skb = skb_realloc_headroom(skb, 20);
				kfree_skb(temp_skb);
				if (skb == NULL) {
					wl_err("%s:%d failed to unshare skbuff: NULL\n",
					   __func__, __LINE__);
					return;
				}
			}
#endif
			/*TODO: if parts of skb alloc succ?*/
			skb_queue_tail(&priv->buffer_list, skb);

			pcie_addr = dma_map_single(&pdev->dev,
					    /*skb->head, skb->len + skb_headroom(skb)*/skb->data, skb->len,
					    DMA_FROM_DEVICE);
			*((unsigned long *)ul_tx_virt_addr + i) = pcie_addr;

			//tmp_offset = (int *)(skb->data - 20);
			/*offset of virtual node*/
			//*tmp_offset = 0x10;

			if(i < 20)
				wl_err("ul tx pcie_addr1:%lu\n", pcie_addr);
#if 0
			//skb_push(skb, 16);
			sipa_node = (struct sipa_node_description_tag *)(skb->data - 16);
			/*pcie_addr = dma_map_single(&pdev->dev,
					    skb->head, skb->len + skb_headroom(skb),
					    DMA_FROM_DEVICE);*/

			sipa_node->address = pcie_addr - 16;
			sipa_node->length = skb->len;
			sipa_node->offset = 16;
			sipa_node->net_id = 0;
			sipa_node->src = SIPA_TERM_WIFI;
			sipa_node->dst = 0;
			sipa_node->prio = 0;
			sipa_node->bear_id = 0;
			sipa_node->intr = 0;
			sipa_node->indx = 0;
			sipa_node->reserved = 0;
#endif
		}
	}

	temp_threshold_value = readl_relaxed((void *)(PSEL_UL+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value |= pam_tx_intr_threshold;
	temp_threshold_value |= pam_tx_intr_threshold_delay;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_UL+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value = readl_relaxed((void *)(PSEL_UL+PAMWIFI_INT_GEN_CTL_EN));
	temp_threshold_value |= pam_tx_intr_threshold_en;
	temp_threshold_value |= pam_tx_intr_threshold_delay_en;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_UL+PAMWIFI_INT_GEN_CTL_EN));

	ul_rx_virt_addr = dma_alloc_coherent(&pdev->dev, tmp_fifo_depth*sizeof(dma_addr_t), &ul_rx_phy_addr, GFP_KERNEL);
	writel_relaxed((u32)(ul_rx_phy_addr & 0xFFFFFFFFl), (void *)(PSEL_UL+PAMWIFI_COMMON_RX_FIFO_ADDRL));
	writel_relaxed((u32)(ul_rx_phy_addr >> 32), (void *)(PSEL_UL+PAMWIFI_COMMON_RX_FIFO_ADDRH));
	pam_wifi_set_rx_fifo_total_depth(PSEL_UL, tmp_fifo_depth);
	//pam_wifi_set_rx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);
	pam_wifi_update_rx_fifo_rptr(PSEL_UL, 0);
	pam_wifi_update_rx_fifo_wptr(PSEL_UL, 0);
	//**********************************UL Part******************************************************************

	//**********************************DL Part******************************************************************
	//PSEL_DL_TYPE1
	//pcie_addr = virt_to_phys(term_pam_wifi_inn_dl_rx_free_buf);
	//dl_type1_virt_addr = dma_alloc_coherent(&pdev->dev, 10*sizeof(struct sipa_node_description_tag), &dl_type1_phy_addr, GFP_KERNEL);
	dl_type1_virt_addr = dma_alloc_coherent(&pdev->dev, tmp_fifo_depth*sizeof(dma_addr_t), &dl_type1_phy_addr, GFP_KERNEL);
	printk("%s, dl_type1_virt_addr: 0x%llx\n", __func__, dl_type1_phy_addr);
	writel_relaxed((u32)(dl_type1_phy_addr & 0xFFFFFFFFl), (void *)(PSEL_DL_TYPE1+PAMWIFI_COMMON_TX_FIFO_ADDRL));
	writel_relaxed((u32)(dl_type1_phy_addr >> 32), (void *)(PSEL_DL_TYPE1+PAMWIFI_COMMON_TX_FIFO_ADDRH));
	pam_wifi_set_tx_fifo_total_depth(PSEL_DL_TYPE1, tmp_fifo_depth);
	//pam_wifi_set_rx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);
	pam_wifi_update_tx_fifo_rptr(PSEL_DL_TYPE1, 0);
	pam_wifi_update_tx_fifo_wptr(PSEL_DL_TYPE1, 0);
	/*writel_relaxed(pam_tx_intr_threshold, (void *)(PSEL_DL_TYPE1+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	writel_relaxed(pam_tx_intr_threshold_en, (void *)(PSEL_DL_TYPE1+PAMWIFI_INT_GEN_CTL_EN));*/
	temp_threshold_value = readl_relaxed((void *)(PSEL_DL_TYPE1+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value |= pam_tx_intr_threshold;
	temp_threshold_value |= pam_tx_intr_threshold_delay;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_DL_TYPE1+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value = readl_relaxed((void *)(PSEL_DL_TYPE1+PAMWIFI_INT_GEN_CTL_EN));
	temp_threshold_value |= pam_tx_intr_threshold_en;
	temp_threshold_value |= pam_tx_intr_threshold_delay_en;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_DL_TYPE1+PAMWIFI_INT_GEN_CTL_EN));


	//PSEL_DL_TYPE2
	//pcie_addr = virt_to_phys(term_pam_wifi_inn_dl_tx_type2_fifo_buf);
	//dl_type2_virt_addr = dma_alloc_coherent(&pdev->dev, 10*sizeof(struct sipa_node_description_tag), &dl_type2_phy_addr, GFP_KERNEL);
	dl_type2_virt_addr = dma_alloc_coherent(&pdev->dev, tmp_fifo_depth*sizeof(dma_addr_t), &dl_type2_phy_addr, GFP_KERNEL);
	writel_relaxed((u32)(dl_type2_phy_addr & 0xFFFFFFFFl), (void *)(PSEL_DL_TYPE2+PAMWIFI_COMMON_TX_FIFO_ADDRL));
	writel_relaxed((u32)(dl_type2_phy_addr >> 32), (void *)(PSEL_DL_TYPE2+PAMWIFI_COMMON_TX_FIFO_ADDRH));
	pam_wifi_set_tx_fifo_total_depth(PSEL_DL_TYPE2, tmp_fifo_depth);
	//pam_wifi_set_rx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);
	pam_wifi_update_tx_fifo_rptr(PSEL_DL_TYPE2, 0);
	pam_wifi_update_tx_fifo_wptr(PSEL_DL_TYPE2, 0);
	/*writel_relaxed(pam_tx_intr_threshold, (void *)(PSEL_DL_TYPE2+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	writel_relaxed(pam_tx_intr_threshold_en, (void *)(PSEL_DL_TYPE2+PAMWIFI_INT_GEN_CTL_EN));*/
	temp_threshold_value = readl_relaxed((void *)(PSEL_DL_TYPE2+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value |= pam_tx_intr_threshold;
	temp_threshold_value |= pam_tx_intr_threshold_delay;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_DL_TYPE2+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value = readl_relaxed((void *)(PSEL_DL_TYPE2+PAMWIFI_INT_GEN_CTL_EN));
	temp_threshold_value |= pam_tx_intr_threshold_en;
	temp_threshold_value |= pam_tx_intr_threshold_delay_en;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_DL_TYPE2+PAMWIFI_INT_GEN_CTL_EN));

	//PSEL_DL_TYPE3
	//pcie_addr = virt_to_phys(term_pam_wifi_inn_dl_tx_type3_fifo_buf);
	//dl_type3_virt_addr = dma_alloc_coherent(&pdev->dev, 10*sizeof(struct sipa_node_description_tag), &dl_type3_phy_addr, GFP_KERNEL);
	dl_type3_virt_addr = dma_alloc_coherent(&pdev->dev, tmp_fifo_depth*sizeof(dma_addr_t), &dl_type3_phy_addr, GFP_KERNEL);
	writel_relaxed((u32)(dl_type3_phy_addr & 0xFFFFFFFFl), (void *)(PSEL_DL_TYPE3+PAMWIFI_COMMON_TX_FIFO_ADDRL));
	writel_relaxed((u32)(dl_type3_phy_addr >> 32), (void *)(PSEL_DL_TYPE3+PAMWIFI_COMMON_TX_FIFO_ADDRH));
	pam_wifi_set_tx_fifo_total_depth(PSEL_DL_TYPE3, tmp_fifo_depth);
	//pam_wifi_set_rx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);
	pam_wifi_update_tx_fifo_rptr(PSEL_DL_TYPE3, 0);
	pam_wifi_update_tx_fifo_wptr(PSEL_DL_TYPE3, 0);
	/*writel_relaxed(pam_tx_intr_threshold, (void *)(PSEL_DL_TYPE3+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	writel_relaxed(pam_tx_intr_threshold_en, (void *)(PSEL_DL_TYPE3+PAMWIFI_INT_GEN_CTL_EN));*/
	temp_threshold_value = readl_relaxed((void *)(PSEL_DL_TYPE3+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value |= pam_tx_intr_threshold;
	temp_threshold_value |= pam_tx_intr_threshold_delay;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_DL_TYPE3+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value = readl_relaxed((void *)(PSEL_DL_TYPE3+PAMWIFI_INT_GEN_CTL_EN));
	temp_threshold_value |= pam_tx_intr_threshold_en;
	temp_threshold_value |= pam_tx_intr_threshold_delay_en;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_DL_TYPE3+PAMWIFI_INT_GEN_CTL_EN));

	//PSEL_DL_TYPE4
	//pcie_addr = virt_to_phys(term_pam_wifi_inn_dl_tx_type4_fifo_buf);
	//dl_type4_virt_addr = dma_alloc_coherent(&pdev->dev, 10*sizeof(struct sipa_node_description_tag), &dl_type4_phy_addr, GFP_KERNEL);
	dl_type4_virt_addr = dma_alloc_coherent(&pdev->dev, tmp_fifo_depth*sizeof(dma_addr_t), &dl_type4_phy_addr, GFP_KERNEL);
	writel_relaxed((u32)(dl_type4_phy_addr & 0xFFFFFFFFl), (void *)(PSEL_DL_TYPE4+PAMWIFI_COMMON_TX_FIFO_ADDRL));
	writel_relaxed((u32)(dl_type4_phy_addr >> 32), (void *)(PSEL_DL_TYPE4+PAMWIFI_COMMON_TX_FIFO_ADDRH));
	pam_wifi_set_tx_fifo_total_depth(PSEL_DL_TYPE4, tmp_fifo_depth);
	//pam_wifi_set_rx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);
	pam_wifi_update_tx_fifo_rptr(PSEL_DL_TYPE4, 0);
	pam_wifi_update_tx_fifo_wptr(PSEL_DL_TYPE4, 0);
	/*writel_relaxed(pam_tx_intr_threshold, (void *)(PSEL_DL_TYPE4+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	writel_relaxed(pam_tx_intr_threshold_en, (void *)(PSEL_DL_TYPE4+PAMWIFI_INT_GEN_CTL_EN));*/
	temp_threshold_value = readl_relaxed((void *)(PSEL_DL_TYPE4+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value |= pam_tx_intr_threshold;
	temp_threshold_value |= pam_tx_intr_threshold_delay;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_DL_TYPE4+PAMWIFI_INT_GEN_CTL_TX_FIFO_VALUE));
	temp_threshold_value = readl_relaxed((void *)(PSEL_DL_TYPE4+PAMWIFI_INT_GEN_CTL_EN));
	temp_threshold_value |= pam_tx_intr_threshold_en;
	temp_threshold_value |= pam_tx_intr_threshold_delay_en;
	writel_relaxed(temp_threshold_value, (void *)(PSEL_DL_TYPE4+PAMWIFI_INT_GEN_CTL_EN));

	//PSEL_DL_FREE
	//pcie_addr = virt_to_phys(term_pam_wifi_inn_dl_tx_type2_fifo_buf);
	//dl_free_virt_addr = dma_alloc_coherent(&pdev->dev, 10*sizeof(struct sipa_node_description_tag), &dl_free_phy_addr, GFP_KERNEL);
	dl_free_virt_addr = dma_alloc_coherent(&pdev->dev, tmp_fifo_depth*sizeof(dma_addr_t), &dl_free_phy_addr, GFP_KERNEL);
	printk("%s, dl_free_phy_addr: 0x%llx\n", __func__, dl_free_phy_addr);
	writel_relaxed((u32)(dl_free_phy_addr & 0xFFFFFFFFl), (void *)(PSEL_DL_FREE+PAMWIFI_COMMON_RX_FIFO_ADDRL));
	writel_relaxed((u32)(dl_free_phy_addr >> 32), (void *)(PSEL_DL_FREE+PAMWIFI_COMMON_RX_FIFO_ADDRH));
	pam_wifi_set_rx_fifo_total_depth(PSEL_DL_FREE, tmp_fifo_depth);
	//pam_wifi_set_rx_fifo_addr(fifo_reg_base,dl_fifo_base_addr_l, dl_fifo_base_addr_h);
	pam_wifi_update_rx_fifo_rptr(PSEL_DL_FREE, 0);
	pam_wifi_update_rx_fifo_wptr(PSEL_DL_FREE, 0);

	//**********************************DL Part******************************************************************

	//************************* Set ul free buffer****************************************************
	//ul free buffer的水标设一下，1就可以
	//Set the 0x40:REG_CFG_UL_FILLED_BUFFER_CTRL
	temp = readl_relaxed((void *)REG_CFG_UL_FILLED_BUFFER_CTRL);
	temp &= ~(BIT_PAM_WIFI_CFG_UL_FILLED_BUFFER_CTRL_CFG_UL_AP_FILLED_BUFFER_WATERMARK(0));
	temp &= ~(BIT_PAM_WIFI_CFG_UL_FILLED_BUFFER_CTRL_CFG_UL_CP_FILLED_BUFFER_WATERMARK(0));

	temp |=BIT_PAM_WIFI_CFG_UL_FILLED_BUFFER_CTRL_CFG_UL_AP_FILLED_BUFFER_WATERMARK(value_cfg_ul_ap_filled_buffer_watermark);
	temp |=BIT_PAM_WIFI_CFG_UL_FILLED_BUFFER_CTRL_CFG_UL_CP_FILLED_BUFFER_WATERMARK(value_cfg_ul_cp_filled_buffer_watermark);

	writel_relaxed(temp, (void *)REG_CFG_UL_FILLED_BUFFER_CTRL);

	//Set the 0x44:REG_CFG_UL_FREE_BUFFER_CTRL
	temp = readl_relaxed((void *)REG_CFG_UL_FREE_BUFFER_CTRL);
	temp &= ~(BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_UL_AP_FREE_BUFFER_WATERMARK(0));
	temp &= ~(BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_UL_CP_FREE_BUFFER_WATERMARK(0));

	temp &= ~(BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE1_BUFFER_WATERMARK(0));
	temp &= ~(BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE2_BUFFER_WATERMARK(0));
	temp &= ~(BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE3_BUFFER_WATERMARK(0));
	temp &= ~(BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE4_BUFFER_WATERMARK(0));
 
	temp |=BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_UL_AP_FREE_BUFFER_WATERMARK(value_cfg_ul_ap_free_buffer_watermark);
	temp |=BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_UL_CP_FREE_BUFFER_WATERMARK(value_cfg_ul_cp_free_buffer_watermark);

	temp |=BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE1_BUFFER_WATERMARK(value_cfg_dl_cp_type1_buffer_watermark);
	temp |=BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE2_BUFFER_WATERMARK(value_cfg_dl_cp_type2_buffer_watermark);
	temp |=BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE3_BUFFER_WATERMARK(value_cfg_dl_cp_type3_buffer_watermark);
	temp |=BIT_PAM_WIFI_CFG_UL_FREE_BUFFER_CTRL_CFG_DL_CP_TYPE4_BUFFER_WATERMARK(value_cfg_dl_cp_type4_buffer_watermark);

	writel_relaxed(temp, (void *)REG_CFG_UL_FREE_BUFFER_CTRL);

	//*************************Configure the INDEX/MSDU table match**********************************
	//use the default value
	//Set the msdu_length in the UL_node_info_config
	#if 0
	temp = readl_relaxed(REG_PAM_WIFI_PAM_WIFI_UL_NODE_INFO_CONFIG);
	temp &= ~(BIT_PAM_WIFI_UL_NODE_INFO_CONFIG_MSDU_LENGTH(0));
	//value_cfg_node_info_config_msdu_length means msdu length is 2*8 = 16 bit?
	temp |=BIT_PAM_WIFI_UL_NODE_INFO_CONFIG_MSDU_LENGTH(CUR_MSDU_LENGTH);
	writel_relaxed(temp, REG_PAM_WIFI_PAM_WIFI_UL_NODE_INFO_CONFIG);
	#endif

	//*************************5> Configure the msdu_header_buf table************************************
	pam_wifi_msdu_header_info = dma_alloc_coherent(&pdev->dev, 8*4*16,
											 &term_pam_wifi_msdu_header_buf, GFP_KERNEL);
	//memcpy(pam_wifi_msdu_header_info, term_pam_wifi_msdu_header_buf_tmp, MAX_MSDU_NUMBER*MAX_ONE_MSDU_LENGTH);
	writel_relaxed((u32)((u64)term_pam_wifi_msdu_header_buf & 0xFFFFFFFFl), (void *)REG_MSDU_BASE_ADDRL);
	writel_relaxed((u32)((u64)term_pam_wifi_msdu_header_buf >> 32), (void *)REG_MSDU_BASE_ADDRH);
	//pam_wifi_msdu_init(priv);

	//*************************6> Configure index search depth*******************************************
	temp = readl_relaxed((void *)REG_INDEX_SEARCH_DEPTH);
	temp &= ~REG_INDEX_SEARCH_DEPTH_MASK;
	temp |= BIT_PAM_WIFI_INDEX_SEARCH_DEPTH_INDEX_SEARCH_DEPTH(value_index_search_depth);
	writel_relaxed(temp, (void *)REG_INDEX_SEARCH_DEPTH);

	/*config router table*/
	//pam_wifi_table_update(dl_tx_fifo_type1);

	/*init node info config*/
	node_info_config = readl_relaxed((void *)REG_UL_NODE_INFO_CONFIG) & (~0x3FFFF);
	node_info_config |= (u32)SIPA_TERM_WIFI;
	node_info_config |= 0xFF << 10;
	writel_relaxed(node_info_config, (void *)REG_UL_NODE_INFO_CONFIG);

	/*config msdu offset     0x52+0x10    msdu+node len*/
	msdu_offset = readl_relaxed((void *)REG_MSDU_BASE_ADDRH);
	msdu_offset &= 0xFF;
	//msdu_offset |= 0x00006200;
	msdu_offset |= 0x00001000;
	writel_relaxed(msdu_offset, (void *)REG_MSDU_BASE_ADDRH);
}

void sprdwl_pam_wifi_miss_node_send(void *data)
{
	struct sprdwl_pam_wifi_miss_node_tag *temp_data =  (struct sprdwl_pam_wifi_miss_node_tag *)data;
	struct sipa_node_description_tag *temp_node = (struct sipa_node_description_tag *)temp_data->data;
	u32 cnt;
	int i ;
	dma_addr_t skb_phy_addr;
	u16 offset;
	unsigned char * virt_addr;

	cnt = temp_data->cnt;
	for(i = 0; i < cnt; i++) {
		offset = (temp_node + i * sizeof(struct sipa_node_description_tag))->offset;
		skb_phy_addr = (temp_node + i * sizeof(struct sipa_node_description_tag))->address + offset;
		virt_addr = phys_to_virt(skb_phy_addr);
		printk("%s, test, da:%02x:%02x:%02x:%02x:%02x:%02x, sa:%02x:%02x:%02x:%02x:%02x:%02x\n",
				__func__, virt_addr[0], virt_addr[1], virt_addr[2],
				virt_addr[3], virt_addr[4], virt_addr[5],
				virt_addr[6], virt_addr[7], virt_addr[8],
				virt_addr[9], virt_addr[10], virt_addr[11]);
	}
}

#if 0
int pam_wifi_miss_irq;
#endif
irqreturn_t pam_wifi_miss_handle(int irq, void *dev)
{
	//unsigned long irq_flags;

	wl_info("%s, %d, enter!\n", __func__, __LINE__);
	//local_irq_save(irq_flags);
	//local_irq_restore(irq_flags);
	disable_irq_nosync(irq);
	irq_set_irq_type(irq, IRQF_TRIGGER_RISING);
	enable_irq(irq);
#if 0
	u8 cnt;
	u32 temp;
	u8 *restore_pam_wifi_miss_node;
	struct sprdwl_work *misc_work;
	struct sprdwl_pam_wifi_miss_node_tag pam_wifi_miss_node;
	struct sprdwl_intf *intf = (struct sprdwl_intf *)g_intf_sc2355.intf;
	struct sprdwl_priv *priv = intf->priv;

	cnt = (readl_relaxed((void*)(pam_wifi_base_addr_remap + 0xA8)) >> 16) & 0xF;
	restore_pam_wifi_miss_node = kzalloc(cnt * sizeof(struct sipa_node_description_tag), GFP_KERNEL);
	memcpy(restore_pam_wifi_miss_node, term_pam_wifi_miss_node_infor, cnt * sizeof(struct sipa_node_description_tag));

	sprdwl_hex_dump("pam wifi test", restore_pam_wifi_miss_node, cnt * sizeof(struct sipa_node_description_tag));

	misc_work = sprdwl_alloc_work(4 + sizeof(struct sipa_node_description_tag));
	if(misc_work) {
		//misc_work->vif = vif;
		misc_work->id = SPRDWL_PAM_WIFI_MISS_NODE_WORK;
		pam_wifi_miss_node.data = restore_pam_wifi_miss_node;
		pam_wifi_miss_node.cnt = cnt;
		memcpy(misc_work->data, &pam_wifi_miss_node, 4 + sizeof(struct sipa_node_description_tag));
		sprdwl_queue_work(priv , misc_work);
	}

	temp = readl_relaxed((void *)(pam_wifi_base_addr_remap + 0x80));
	temp &= ~0x80;
	temp |= BIT(7);
	writel_relaxed(temp, (void *)(pam_wifi_base_addr_remap + 0x80));
#endif
	wl_info("%s, %d, exit!\n", __func__, __LINE__);
	return IRQ_HANDLED;
}

int sprdwl_roc1_pkt_checksum(struct sk_buff *skb, struct net_device *ndev)
{
	struct udphdr *udphdr;
	struct tcphdr *tcphdr;
	struct iphdr *iphdr;
	struct ipv6hdr *ipv6hdr;
	__sum16 checksum = 0;
	unsigned char iphdrlen = 0;
	struct ethhdr *ethhdr = (struct ethhdr *)skb->data;

	if (ethhdr->h_proto == htons(ETH_P_IPV6)) {
		ipv6hdr = (struct ipv6hdr *)(skb->data + ETHER_HDR_LEN);
		iphdrlen = sizeof(*ipv6hdr);
	} else if (ethhdr->h_proto == htons(ETH_P_IP)) {
		iphdr = (struct iphdr *)(skb->data + ETHER_HDR_LEN);
		iphdrlen = ip_hdrlen(skb);
	}
	udphdr = (struct udphdr *)(skb->data + ETHER_HDR_LEN + iphdrlen);
	tcphdr = (struct tcphdr *)(skb->data + ETHER_HDR_LEN + iphdrlen);

	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		checksum =
		(__force __sum16)do_csum(
		skb->data + ETHER_HDR_LEN + iphdrlen,
		skb->len - ETHER_HDR_LEN - iphdrlen);
		if ((ethhdr->h_proto == htons(ETH_P_IPV6) && ipv6hdr->nexthdr == IPPROTO_UDP) ||
			(ethhdr->h_proto == htons(ETH_P_IP) && iphdr->protocol != IPPROTO_UDP)) {
			udphdr->check = ~checksum;
			wl_info("csum:%x,udp check:%x\n",
			checksum, udphdr->check);
		} else if ((ethhdr->h_proto == htons(ETH_P_IPV6) && ipv6hdr->nexthdr == IPPROTO_TCP) ||
		(ethhdr->h_proto == htons(ETH_P_IP) && iphdr->protocol != IPPROTO_TCP)) {
			tcphdr->check = ~checksum;
			wl_info("csum:%x,tcp check:%x\n",
			checksum, tcphdr->check);
		} else
			return 1;

		skb->ip_summed = CHECKSUM_NONE;
		return 0;
	}
	return 1;
}

u64 pam_wifi_base_addr_remap;
extern struct device *sprdwl_dev;
void sprdwl_pamwifi_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct regmap *sys_regmap;
	u32 reg_info[2];
	int ret;

	/*pam wifi reg remap*/

	sys_regmap = syscon_regmap_lookup_by_name(pdev->dev.of_node,
				       "enable");
	if (IS_ERR(sys_regmap))
		pr_err("%s :get sys regmap fail!\n", __func__);
	ret = syscon_get_args_by_name(pdev->dev.of_node,
								  "enable", 2,
								  reg_info);

	if (sys_regmap) {
		ret = regmap_update_bits(sys_regmap,
							reg_info[0],
							reg_info[1],
							reg_info[1]);
		if (ret < 0) {
			wl_err("%s: regmap update bits failed", __func__);
			return;
		}
	}

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pam_wifi_reg_base_remap");
	if (!res) {
		wl_err("wifi get res fail!\n");
		return;
	}
	pam_wifi_base_addr_remap = (unsigned long)devm_ioremap_nocache(sprdwl_dev, res ->start, resource_size(res));
	wl_info("pam_wifi_base_addr_remap=0x%llx\n",
		pam_wifi_base_addr_remap);
#if 0
	/*register pam wifi miss irq*/
	pam_wifi_miss_irq = platform_get_irq_byname(pdev, "pam-wifi-miss-irq-gpio");

	ret = request_irq(pam_wifi_miss_irq,
			pam_wifi_miss_handle,
			IRQF_TRIGGER_RISING | IRQF_NO_SUSPEND,
			"pam_wifi_miss_irq",
			NULL);
	if (ret != 0)
		wl_err("pam_wifi_miss_irq-%d err!!!", pam_wifi_miss_irq);
#endif
}

static void sipa_wifi_prepare_skb(struct sprdwl_vif *vif, struct sk_buff *skb)
{
	struct iphdr *iph;
	struct ipv6hdr *ipv6h;
	struct ethhdr *ethh;
	struct net_device *net = vif->ndev;
	unsigned int real_len = 0;
	unsigned int payload_len = 0;
	bool ip_arp = true;

	skb_reset_mac_header(skb);
	ethh = eth_hdr(skb);

	skb->protocol = eth_type_trans(skb, net);
	skb_reset_network_header(skb);

	switch (ntohs(ethh->h_proto)) {
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
		real_len = arp_hdr_len(net);
		break;
	default:
		ip_arp = false;
		pr_debug("skb %p is neither v4 nor v6 nor arp\n", skb);
		break;
	}

	/* resize the skb->len to a real one */
	if (ip_arp)
		skb_trim(skb, real_len);

	/* TODO chechsum ... */
	skb->ip_summed = CHECKSUM_NONE;
	skb->dev = net;
}

static void sipa_wifi_rx_handler (struct sprdwl_priv *priv)
{
	struct sprdwl_vif *vif;
	int ret;
	struct sk_buff *skb;
	struct net_device *net;

	vif = mode_to_vif(priv, SPRDWL_MODE_AP);
	net = vif->ndev;
	if (!priv) {
		wl_err("%s sipa_wifi dev is NULL\n", __func__);
		return;
	}
	ret = sipa_nic_rx(priv->nic_id, &skb);
	if (ret) {
		switch (ret) {
		case -ENODEV:
			wl_err("sipa wifi fail to find dev");
			break;
		case -ENODATA:
			wl_err("sipa wifi no more skb to recv");
			break;
		}
	}
	if (!skb) {
			wl_err("sipa wifi recv skb is null\n");
			return;// -EINVAL;
	}
	sipa_wifi_prepare_skb(vif, skb);
	netif_receive_skb(skb);
}

void sipa_wifi_notify_cb(void *priv, enum sipa_evt_type evt,
                               unsigned long data)
{
        struct sprdwl_priv *dev_priv = (struct sprdwl_priv *)priv;

        switch (evt) {
        case SIPA_RECEIVE:
                wl_err("sipa_wifi SIPA_RECEIVE evt received\n");
                //sipa_wifi_rx_handler(priv);
                wake_up(&dev_priv->sipa_recv_wq);
                break;
        case SIPA_LEAVE_FLOWCTRL:
                wl_err("sipa_wifi SIPA LEAVE FLOWCTRL\n");
                //sipa_wifi_flowctrl_handler(priv, 0);
                break;
        case SIPA_ENTER_FLOWCTRL:
                wl_err("sipa_wifi SIPA ENTER FLOWCTRL\n");
                //sipa_wifi_flowctrl_handler(priv, 1);
                break;
        default:
                break;
        }
}

extern int sipa_nic_rx_has_data(enum sipa_nic_id nic_id);
static int recv_thread(void *data)
{
	struct sprdwl_priv *priv = (struct sprdwl_priv *)data;
	while (!kthread_should_stop()) {
		pr_info("sprd wlan0 recv thread, %s\n", __func__);
		wait_event_interruptible(priv->sipa_recv_wq,
			sipa_nic_rx_has_data(priv->nic_id) || priv->kthread_stop == 1);
		if (priv->kthread_stop == 1)
			break;
		else
			sipa_wifi_rx_handler(priv);
	}
	return 0;
}

void sprdwl_pamwifi_init(struct sprdwl_vif *vif, struct platform_device *pdev)
{
	int ret;
	struct sprdwl_priv *priv = vif->priv;

	//ipa_to_pam_wifi_init(priv, pdev);
	init_waitqueue_head(&priv->sipa_recv_wq);
	priv->recv_thread = kthread_create(recv_thread, (void *)priv,"sprd_wlan0_recv");
	if (IS_ERR(priv->recv_thread)) {
		wl_err("Failed to create kthread: sprd_wlan0_recv\n");
		ret = PTR_ERR(priv->recv_thread);
		return;
	}
	priv->kthread_stop = 0;
	wake_up_process(priv->recv_thread);

	pam_wifi_msdu_init(priv);
	pam_wifi_enable();
	//clear_reg_bits(REG_CFG_START, BIT_PAM_WIFI_CFG_START_PAM_WIFI_STOP);
	set_reg_bits_all_one(REG_CFG_START,  BIT_PAM_WIFI_CFG_START_PAM_WIFI_START);
	ret = sipa_nic_open(
                SIPA_TERM_WIFI,
                -1,
                sipa_wifi_notify_cb,
                (void *)priv);
	wl_info("%s, nic_id: %d\n", __func__, ret);
	priv->nic_id = ret;
	//priv->state = DEV_ON;
	if (!netif_carrier_ok(vif->ndev))
		netif_carrier_on(vif->ndev);
	netif_start_queue(vif->ndev);
}

void sprdwl_deinit_pamwifi_fifo(struct sprdwl_priv *priv, struct platform_device *pdev)
{
#if 0
	u32 value = 0;
	int timeout = 10;

	sipa_disconnect(SIPA_EP_WIFI, SIPA_DISCONNECT_START);
	//value = readl_relaxed(pamu3->base + PAM_U3_CTL0);
		/*DL fill wr/rd == free wr/rd
		UL fill wr/rd == free wr/rd
		IPA DL/UL as so*/
	value = check_pamwifi_ipa_fifo_status();
	wl_info("Start to close Pam wifi!\n");
	while(!value) {
		value = check_pamwifi_ipa_fifo_status();
		if (!timeout--) {
			wl_err("Pam wifi close fail!\n");
			return;
		}
		wl_err("Pam wifi closing!\n");
		usleep_range(10, 15);
	}
	sipa_disconnect( SIPA_EP_WIFI, SIPA_DISCONNECT_END);
	wl_err("%d,Pam wifi close success!!\n", __LINE__);
	/*stop pam wifi*/
	clear_reg_bits(REG_CFG_START, BIT_PAM_WIFI_CFG_START_PAM_WIFI_START);
	//set_reg_bits_all_one(REG_CFG_START,  BIT_PAM_WIFI_CFG_START_PAM_WIFI_STOP);
#endif
	skb_queue_purge(&priv->buffer_list);
#if 0
	disable_irq(pam_wifi_miss_irq);
	free_irq(pam_wifi_miss_irq, NULL);
#endif
	dma_free_coherent(&pdev->dev, 512*sizeof(dma_addr_t), ul_tx_virt_addr, ul_tx_phy_addr);
	dma_free_coherent(&pdev->dev, 512*sizeof(dma_addr_t), ul_rx_virt_addr, ul_rx_phy_addr);
	dma_free_coherent(&pdev->dev, 512*sizeof(dma_addr_t), dl_type1_virt_addr, dl_type1_phy_addr);
	dma_free_coherent(&pdev->dev, 512*sizeof(dma_addr_t), dl_type2_virt_addr, dl_type2_phy_addr);
	dma_free_coherent(&pdev->dev, 512*sizeof(dma_addr_t), dl_type3_virt_addr, dl_type3_phy_addr);
	dma_free_coherent(&pdev->dev, 512*sizeof(dma_addr_t), dl_type4_virt_addr, dl_type4_phy_addr);
	dma_free_coherent(&pdev->dev, 512*sizeof(dma_addr_t), dl_free_virt_addr, dl_free_phy_addr);
	dma_free_coherent(&pdev->dev, 8*4*16, pam_wifi_msdu_header_info, term_pam_wifi_msdu_header_buf);
	/*devm_iounmap(struct device *dev, void __iomem *addr)*/
	devm_iounmap(sprdwl_dev, (void __iomem *)pam_wifi_base_addr_remap);
	wl_err("%d,Pam wifi close success!!\n", __LINE__);
}

int sprdwl_xmit_to_ipa_pamwifi(struct sk_buff *skb, struct net_device *ndev)
{
	struct sprdwl_vif *vif = netdev_priv(ndev);
	struct sprdwl_intf *intf = (struct sprdwl_intf *)vif->priv->hw_priv;
	unsigned char lut_index;
	struct ethhdr *ethhdr = (struct ethhdr *)skb->data;
	int ret = 0;

	/*filter pkt to pam wifi*/
	if (ethhdr->h_proto == htons(ETH_P_IP)) {
		intf->skb_da = skb->data;
		lut_index = sprdwl_find_lut_index(intf, vif);
		if(lut_index > 5) {
			//struct eth_dev *dev = netdev_priv(vif->ndev);

			if (skb_headroom(skb) < (32 + NET_IP_ALIGN)) {
				struct sk_buff *tmp_skb = skb;

				skb = skb_realloc_headroom(skb, 32 + NET_IP_ALIGN);
				dev_kfree_skb(tmp_skb);
				if (!skb) {
					netdev_err(ndev,
						   "%send to pam wifi, skb_realloc_headroom failed\n",
						   __func__);
					return NETDEV_TX_OK;
				}
			}
			ret = sipa_nic_tx(vif->priv->nic_id, SIPA_TERM_WIFI, -1, skb);
			if (unlikely(ret != 0)) {
				wl_err("sipa_wifi fail to send skb, ret %d\n", ret);
				if (ret == -ENOMEM || ret == -EAGAIN) {
					//netif_stop_queue(net);
					return NETDEV_TX_BUSY;
				}
			}
			//wl_err("sipa_wifi succ to send skb, ret %d\n", lut_index);
			wl_err("%s, sipa_wifi succ to send skb, lut_index: %u, macaddr:%02x:%02x:%02x:%02x:%02x:%02x, %02x:%02x:%02x:%02x:%02x:%02x\n",
				__func__, lut_index, skb->data[0], skb->data[1], skb->data[2],
				skb->data[3], skb->data[4], skb->data[5], skb->data[6], skb->data[7], skb->data[8],
				skb->data[9], skb->data[10], skb->data[11]);
			//sprdwl_hex_dump("sprdwl xmit dump:", skb->data, 100);
			return NETDEV_TX_OK;
		}
	}
	if (ethhdr->h_proto == htons(ETH_P_IPV6) ||ethhdr->h_proto == htons(ETH_P_IP)) {
			wl_err("ip pkt send by driver");
			sprdwl_roc1_pkt_checksum(skb, ndev);
	}
	wl_err("%s, macaddr:%02x:%02x:%02x:%02x:%02x:%02x, %02x:%02x:%02x:%02x:%02x:%02x\n",
			__func__, skb->data[0], skb->data[1], skb->data[2],
			skb->data[3], skb->data[4], skb->data[5], skb->data[6], skb->data[7], skb->data[8],
			skb->data[9], skb->data[10], skb->data[11]);
	//sprdwl_hex_dump("sprdwl xmit dump:", skb->data, 100);
	sprdwl_xmit_data2cmd_wq(skb, ndev);

	return NETDEV_TX_OK;
}
#endif


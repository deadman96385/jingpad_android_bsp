#include <asm/io.h>
#include <common.h>
#include <errno.h>
#include <linux/pci/pcie_sprd.h>

#define SPRD_PCIE_BASE				0x2b100000
#define PCIE_PHY_DBG_R1				0x72c
#define PCIE_PHY_DBG_R1_LINK_UP			(0x1 << 4)
#define PCIE_PHY_DBG_R1_LINK_IN_TRAINING	(0x1 << 29)

#define PCIE_MISC_CTRL1_OFF	0x8bc
#define PCIE_DBI_RO_WR_EN	(0x1 << 0)

#define SPRD_PCIE_DBI2	0x8000
#define PCIE_BAR0	0x10
#define PCIE_BAR_EN	0x1

#define BAR_NUM		0x6

static int sprd_pcie_linkup(void)
{
	u32 val;

	val = readl(SPRD_PCIE_BASE + PCIE_PHY_DBG_R1);
	return ((val & PCIE_PHY_DBG_R1_LINK_UP) &&
		(!(val & PCIE_PHY_DBG_R1_LINK_IN_TRAINING)));
}

static void sprd_pcie_dbi_ro_wr_en(void)
{
	u32 val;

	val = readl(SPRD_PCIE_BASE + PCIE_MISC_CTRL1_OFF);
	val |= PCIE_DBI_RO_WR_EN;
	writel(val, SPRD_PCIE_BASE + PCIE_MISC_CTRL1_OFF);
}

static void sprd_pcie_dbi_ro_wr_dis(void)
{
	u32 val;

	val = readl(SPRD_PCIE_BASE + PCIE_MISC_CTRL1_OFF);
	val &= ~PCIE_DBI_RO_WR_EN;
	writel(val, SPRD_PCIE_BASE + PCIE_MISC_CTRL1_OFF);
}

/* split one 64 bit BAR into two 32 bit BARs */
int sprd_pcie_split_bar(void)
{
	u32 val, bar_offset;
	int i;

	if (!sprd_pcie_linkup())
		printf("%s: pcie link fail, ignore it and go on...\n",
			__func__);

	for (i = 0; i < BAR_NUM; i++) {
		bar_offset = PCIE_BAR0 + (i * 4);
		val = readl(SPRD_PCIE_BASE + bar_offset);
		if (val & 0x4) {
			val &= ~0x4;
			sprd_pcie_dbi_ro_wr_en();
			writel(val, SPRD_PCIE_BASE + bar_offset);
			sprd_pcie_dbi_ro_wr_dis();
			/*
			 * enable the new BAR:
			 * e.g. BAR0 -> BAR0 + BAR1, enable BAR1)
			 */
			writel(PCIE_BAR_EN, (SPRD_PCIE_BASE +
					     SPRD_PCIE_DBI2 + bar_offset + 4));
		}

		val = readl(SPRD_PCIE_BASE + bar_offset);
		if (val & 0x4) {
			printf("%s: split bar%d fail, please check!\n",
				__func__, i);
			return -EINVAL;
		}
	}

	return 0;
}

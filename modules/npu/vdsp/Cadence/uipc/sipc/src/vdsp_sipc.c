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

#include <linux/debugfs.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/wait.h>
#include <linux/sizes.h>

#include "vdsp_sipc.h"
#include "vdsp_sipc_priv.h"

#define IPI_BAMK	"ipi"

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "[VDSP]VDSP_SIPC: %d %d %s : "\
	fmt, current->pid, __LINE__, __func__

#if defined(CONFIG_DEBUG_FS)
void vdsp_sipc_debug_putline(struct seq_file *m, char c, int n)
{
	char buf[300];
	int i, max, len;

	/* buf will end with '\n' and 0 */
	max = ARRAY_SIZE(buf) - 2;
	len = (n > max) ? max : n;

	for (i = 0; i < len; i++)
		buf[i] = c;

	buf[i] = '\n';
	buf[i + 1] = 0;

	seq_puts(m, buf);
}
EXPORT_SYMBOL_GPL(vdsp_sipc_debug_putline);
#endif

typedef void(*vdsp_sipc_handle)(u8 dst, u64 msg);

void vdsp_sipc_register_trigger(u8 dst, vdsp_sipc_handle cb)
{
	struct smsg_ipc *ipc;

	ipc = vdsp_smsg_ipcs[dst];

	pr_info("%s\n", __func__);
	ipc->txirq_trigger = cb;
#ifdef TEST_OPENSELT
	complete(&ipc->thread_com);
#endif
}
EXPORT_SYMBOL_GPL(vdsp_sipc_register_trigger);

/* DON'T NEED TO CLEAR INTERRUPT */
static u32 sipc_rxirq_status(u8 dst)
{
	return 0;
}

static void sipc_rxirq_clear(u8 dst)
{

}

static void sipc_txirq_trigger(u8 dst, u64 msg)
{
	struct smsg_ipc *ipc;

	ipc = vdsp_smsg_ipcs[dst];

	if (ipc) {
		pr_info("sipc_txirq_trigger send irq 77777\n");
		ipc->vdsp_ipi_desc->ops->irq_send(7);
	}
}

static int sipc_parse_dt(struct smsg_ipc *ipc,
	struct device_node *np, struct device *dev)
{
	u32 val[3];
	int ret;
	const char *type;

	/* get name */
	ret = of_property_read_string(np, "sprd,name", &ipc->name);
	if (ret)
		return ret;

	pr_info("sipc: name=%s\n", ipc->name);

	/* get sipc type, optional */
	if (of_property_read_string(np, "sprd,type", &type) == 0) {
		pr_info("sipc: type=%s\n", type);
		if (strcmp(IPI_BAMK, type) == 0)
			ipc->type = SIPC_BASE_IPI;
		else
			ipc->type = SIPC_BASE_NR;
	}

	/* get sipc client, optional */
	if (of_property_read_u32_array(np, "sprd,client", val, 1) == 0) {
		ipc->client = (u8)val[0];
		pr_info("sipc: client=%d\n", ipc->client);
	} else {
		ipc->client = 0;
	}

	/* get sipc dst */
	ret = of_property_read_u32_array(np, "sprd,dst", val, 1);
	if (!ret) {
		ipc->dst = (u8)val[0];
		pr_info("sipc: dst =%d\n", ipc->dst);
	}

	if (ret || ipc->dst >= VDSP_SIPC_ID_NR) {
		pr_err("sipc: dst err, ret =%d.\n", ret);
		return ret;
	}

	/* get smem type */
	ret = of_property_read_u32_array(np,
					 "sprd,smem-type",
					 &ipc->smem_type,
					 1);
	if (ret)
		ipc->smem_type = SMEM_LOCAL;

	pr_info("sipc: smem_type = %d, ret =%d\n", ipc->smem_type, ret);

	/* get smem info */
	ret = of_property_read_u32_array(np,
					 "sprd,smem-info",
					 val,
					 3);
	if (ret) {
		pr_err("sipc: parse smem info failed.\n");
		return ret;
	}
	ipc->smem_base = val[0];
	ipc->dst_smem_base = val[1];
	ipc->smem_size = val[2];
	pr_info("sipc: smem_base=0x%x, dst_smem_base=0x%x, smem_size=0x%x\n",
		ipc->smem_base, ipc->dst_smem_base, ipc->smem_size);

	/* try to get high_offset */
	ret = of_property_read_u32_array(np,
					 "sprd,high-offset",
					 val,
					 2);
	if (!ret) {
		ipc->high_offset = val[0];
		ipc->dst_high_offset = val[1];
	} else {
		ipc->high_offset = 1;
		ipc->dst_high_offset = 1;
	}
	pr_info("sipc:  high_offset=0x%x, dst_high_offset=0x%x\n",
		ipc->high_offset, ipc->dst_high_offset);


	return 0;
}

static int sipc_probe(struct platform_device *pdev)
{
	struct smsg_ipc *ipc;
	struct device_node *np;

	if (pdev->dev.of_node) {
		np = pdev->dev.of_node;
		ipc = devm_kzalloc(&pdev->dev,
			sizeof(struct smsg_ipc),
			GFP_KERNEL);
		if (!ipc)
			return -ENOMEM;

		if (sipc_parse_dt(ipc, np, &pdev->dev)) {
			pr_err("%s: failed to parse dt!\n", __func__);
			return -ENODEV;
		}

		ipc->rxirq_status = sipc_rxirq_status;
		ipc->rxirq_clear = sipc_rxirq_clear;
		ipc->txirq_trigger = sipc_txirq_trigger;
		init_waitqueue_head(&ipc->suspend_wait);
		spin_lock_init(&ipc->suspend_pinlock);
		spin_lock_init(&ipc->txpinlock);

		ipc->vdsp_ipi_desc = get_vdsp_ipi_ctx_desc();
		if (!ipc->vdsp_ipi_desc) {
			pr_err("get ipi desc error\n");
		}
		ipc->vdsp_mem_desc = get_vdsp_mem_ctx_desc(NULL);
		if (!ipc->vdsp_mem_desc) {
			pr_err("get mem desc error\n");
		}

		vdsp_smsg_ipc_create(ipc);
		platform_set_drvdata(pdev, ipc);
	}
	return 0;
}

static int sipc_remove(struct platform_device *pdev)
{
	struct smsg_ipc *ipc = platform_get_drvdata(pdev);

	vdsp_smsg_ipc_destroy(ipc);

	devm_kfree(&pdev->dev, ipc);
	return 0;
}

static const struct of_device_id sipc_match_table[] = {
	{ .compatible = "sprd,vdsp_sipc", },
	{ },
};

static struct platform_driver sipc_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "vdsp_sipc",
		.of_match_table = sipc_match_table,
	},
	.probe = sipc_probe,
	.remove = sipc_remove,
};

static int __init sipc_init(void)
{
	vdsp_smsg_init_channel2index();
	return platform_driver_register(&sipc_driver);
}

static void __exit sipc_exit(void)
{
	platform_driver_unregister(&sipc_driver);
}

subsys_initcall_sync(sipc_init);
module_exit(sipc_exit);

MODULE_AUTHOR("Camera System Design");
MODULE_DESCRIPTION("SIPC/SMSG driver");
MODULE_LICENSE("GPL v2");

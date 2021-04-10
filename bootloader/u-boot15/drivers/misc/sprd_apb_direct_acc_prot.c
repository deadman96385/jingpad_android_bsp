/*
 * sprd_apb_direct_acc_prot.c - interface internal to protect AON/PMU APB direct access space
 * against overwriten .
 *
 * Copyright (C) 2019 Unisoc Inc.
 *
 * Author:westbobo.zhou<westbobo.zhou@unisoc.com>
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

#include <common.h>
#include <errno.h>
#include <asm/io.h>
#include <asm/system.h>
#include <asm/arch/sprd_reg.h>

#pragma pack(1)
/**
 *struct sprd_prot_lock_status - status of lock
 *@local_lock:		     	When specific bit is '1', it means a master id already obtain lock
 *@lock_enable:			1'means apb_direct_acc_prot can take effect
 *@lock_write_no_permission:	Event happens that a master want to write register but doesn't obtain lock
 *@lock_read_no_permission:	Event happens that a master want to read register but doesn't obtain lock
 *@big_lit_lock_sel:		Indicates lock space if 12K or 4K,0:4K, 1:12K
 *@direct_acc_disable:		Indicates wether current master ID can access or not,1:cannot access,0:can access
 *@firewall_fail_irq:		Indicates a master wants to access without license of firewall
 *@clear_lock_fail_irq:		Event happens that a master want remove lock without matching the stored master ID
 *@grab_lock_fail_irq:		Event happens that a master want to grab a lock but the lock already obtained by another.
 *@corss_switch_fail_irq:	Event happens that a master want to switch space from 4K to 12K or 12K to 4k but can't access
 */
struct sprd_prot_lock_status {
	uint32_t local_lock:15;
	uint32_t lock_enable:1;
	uint32_t lock_write_no_permission:1;
	uint32_t lock_read_no_permission:1;
	uint32_t big_lit_lock_sel:1;
	uint32_t direct_acc_disable:1;
	uint32_t firewall_fail_irq:1;
	uint32_t clear_lock_fail_irq:1;
	uint32_t grab_lock_fail_irq:1;
	uint32_t corss_switch_fail_irq:1;
};
#pragma pack()

/**
 *enum sprd_apb_type - apb type support direct access prot lock
 *@RESET_APB:	non apb
 *@AON_APB: 	aon apb
 *@PMU_APB:	pmu apb
 *APB_CNT:	number of app
*/
enum sprd_apb_type {
	RESET_APB,
	AON_APB,
	PMU_APB,
	APB_CNT
};

#define EVT_ENABLE                      0x3f
#define DAP_LOCK_MAGIC_SHIFT            16
#define LATEST_MASTER_ID_RECORD         BIT(15)
#define PROT_LOCK_ENABLE                BIT(15)
#define MAGIC_LOCK_ALL                  0x898c
#define MAGIC_UNLOCK_SC                 (~0x898c)
#define MAGIC_LOCK_DIRECT_ACCESS        0x6896
#define MAGIC_RELEASE_DIRECT_ACCESS     (~0x6896)
#define DIRCET_ACC_LOCK_MAGIC           (MAGIC_LOCK_DIRECT_ACCESS << DAP_LOCK_MAGIC_SHIFT)

#define DIRECT_ACCESS_BASE              0x0
#define LOCK_CMD_AND_STATUS_BASE        0xff0
#define LOCK_INT_EVT_EN_BASE            0xff4
#define LOCK_INT_CLR_BASE               0xff8
#define LOCK_DEBUG_SHAPSHOT_IF_BASE     0xffc
#define AON_ACC_SPACE_BASE              (REG_AON_APB_APB_EB0 + DIRECT_ACCESS_BASE)
#define AON_LOCK_CMD_AND_STATUS_BASE    (REG_AON_APB_APB_EB0 + LOCK_CMD_AND_STATUS_BASE)
#define AON_LOCK_INT_EVT_EN_BASE        (REG_AON_APB_APB_EB0 + LOCK_INT_EVT_EN_BASE)
#define AON_LOCK_INT_CLR_BASE           (REG_AON_APB_APB_EB0 + LOCK_INT_CLR_BASE)
#define AON_LOCK_DEBUG_SHAPSHOT_IF_BASE (REG_AON_APB_APB_EB0 + LOCK_DEBUG_SHAPSHOT_IF_BASE)
#define PMU_ACC_SPACE_BASE              (REG_PMU_APB_PD_APCPU_TOP_CFG + DIRECT_ACCESS_BASE)
#define PMU_LOCK_CMD_AND_STATUS_BASE    (REG_PMU_APB_PD_APCPU_TOP_CFG + LOCK_CMD_AND_STATUS_BASE)
#define PMU_LOCK_INT_EVT_EN_BASE        (REG_PMU_APB_PD_APCPU_TOP_CFG + LOCK_INT_EVT_EN_BASE)
#define PMU_LOCK_INT_CLR_BASE           (REG_PMU_APB_PD_APCPU_TOP_CFG + LOCK_INT_CLR_BASE)
#define PMU_LOCK_DEBUG_SHAPSHOT_IF_BASE (REG_PMU_APB_PD_APCPU_TOP_CFG + LOCK_DEBUG_SHAPSHOT_IF_BASE)

/*
 *direct_acc_prot_lock -- use to enbale direct access space lock of AON/PMU APB
 *@crtl_apb:apb type supported, AON_APB or PMU_APB
 *@addr: direct access space, AON_ACC_SPACE_BASE or PMU_ACC_SPACE_BASE
 *return: void
 */
void direct_acc_prot_lock(enum sprd_apb_type crtl_apb, uint32_t addr)
{
	uint32_t val;
	struct sprd_prot_lock_status rd_lock_status;

	if (crtl_apb != AON_APB && crtl_apb != PMU_APB) {
		printf("%s, the APB has not supported\r\n", __func__);
		return;
	} else if (addr != AON_ACC_SPACE_BASE && addr != PMU_ACC_SPACE_BASE) {
		printf("%s, direct base address error!!!addr:0x%x\r\n", __func__, addr);
		return;
	}

	/* APB LOCK enable */
	val = DIRCET_ACC_LOCK_MAGIC;
	val |= PROT_LOCK_ENABLE;
	__raw_writel(val, addr + LOCK_CMD_AND_STATUS_BASE);

	/* record latest master id */
	val = __raw_readl(addr + LOCK_INT_EVT_EN_BASE);
	val |= LATEST_MASTER_ID_RECORD;
	/* enable event */
	val |= EVT_ENABLE;
	__raw_writel(val, addr + LOCK_INT_EVT_EN_BASE);

	val = __raw_readl(addr + LOCK_CMD_AND_STATUS_BASE);
	memcpy(&rd_lock_status, &val, sizeof(uint32_t));
	val = __raw_readl(addr + LOCK_INT_EVT_EN_BASE);
	printf("%s:%s APB lock EVT status:0x%x \r\n", __func__, crtl_apb == AON_APB ? "AON" : "PMU", val);
	if (rd_lock_status.lock_enable)
		printf("%s,%s APB LOCK successfully\r\n", __func__, crtl_apb == AON_APB ? "AON" : "PMU");
	else
		printf("%s,%s APB LOCK failed\r\n", __func__, crtl_apb == AON_APB ? "AON" : "PMU");
}

/*
 *direct_acc_prot_enable -- interface to enable direcc access lock ,both AON and PMU APB
 *@var:void
 *return: void
 */
void direct_acc_prot_enable(void)
{
	/* AON APB LOCK enable  */
	direct_acc_prot_lock(AON_APB, AON_ACC_SPACE_BASE);
	/* PMU APB LOCK enable */
	direct_acc_prot_lock(PMU_APB, PMU_ACC_SPACE_BASE);
}

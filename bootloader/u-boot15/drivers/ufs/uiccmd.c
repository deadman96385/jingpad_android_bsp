
#include <common.h>
#include "uiccmd.h"
#include <sprd_ufs.h>
#include "ip_env.h"

/***************************************************************
 *
 * send_uic_command
 * Description: Programs the Command Argument and the Command
 *     Register to send the DME_LINK_STARTUP command 
 *     to the device
 *
 ***************************************************************/
static void send_uic_command(uint32_t command, uint32_t arg1, uint32_t arg2, uint32_t arg3)
{

	ufs_writel(DW_UFS_UICCMDARG1,arg1);
	ufs_writel(DW_UFS_UICCMDARG2,arg2);
	ufs_writel(DW_UFS_UICCMDARG3,arg3);

	ufs_writel(DW_UFS_UICCMD,(command & 0xFF));
}

static int wait_uic_complete(void)
{
	int retry = 100;
	uint32_t uccs_intr_res = 0;

	/*wait for the UIC Command to complete by checking UCCS field*/
	while(retry > 0) {
		udelay(1000);
		uccs_intr_res = ufs_readl(DW_UFS_IS) & DW_UFS_IS_UCCS;
		if (uccs_intr_res) {
			ufs_writel(DW_UFS_IS, uccs_intr_res);
			break;
		}
		retry--;
	}

	if (0 == retry)
		return UFS_TIMEOUT;
	else
		return UFS_SUCCESS;

}


uint32_t dme_get(uint32_t mib)
{
	mib = (mib << 16) | ((mib >> 16) & 0x0000FFFF);
	send_uic_command(UIC_GET_CMD, mib, 0, 0);
	wait_uic_complete();

	return ufs_readl(DW_UFS_UICCMDARG3);
}

void dme_set(uint32_t mib, uint32_t value)
{
	mib = (mib << 16) | ((mib >> 16) & 0x0000FFFF);
	send_uic_command(UIC_SET_CMD, mib, 0, value);

	wait_uic_complete();

	/*return with no error*/
	return;
}

uint32_t dme_peer_get(uint32_t mib)
{
	mib = (mib << 16) | ((mib >> 16) & 0x0000FFFF);
	send_uic_command(UIC_PEER_GET_CMD, mib, 0, 0);
	wait_uic_complete();

	return ufs_readl(DW_UFS_UICCMDARG3);
}

int dme_endpoint_reset(void)
{
	send_uic_command(UIC_ENDPOINT_RESET_CMD, 0, 0, 0);
	return wait_uic_complete();
}


void dme_link_startup(void)
{
	send_uic_command(UIC_LINK_STARTUP_CMD, 0, 0, 0);
	wait_uic_complete();
}

void dme_hibernate_exit(void)
{
	send_uic_command(UIC_EXIT_HIBERNATE, 0, 0, 0);
	wait_uic_complete();
}



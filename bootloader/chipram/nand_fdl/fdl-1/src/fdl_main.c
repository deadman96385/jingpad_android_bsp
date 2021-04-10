/******************************************************************************
 ** File Name:      FDL_main.c                                                 *
 ** Author:         weihua.wang                                                  *
 ** DATE:           27/06/2005                                               *
 ** Copyright:      2001 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:                                                              *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ******************************************************************************/

/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/
#include <sci_types.h>
#include "../inc/fdl_main.h"
#include <cmd_def.h>
#include <packet.h>
#include <dl_engine.h>
#include "../inc/fdl_command.h"
#include <fdl_channel.h>
#include <asm/arch/sprd_reg.h>
#include <fdl_stdio.h>
#include "sprd_usb_drv.h"
#if defined (CONFIG_AUTODLOADER)
#include <adi.h>
#endif/*CONFIG_AUTODLOADER*/
#if (defined(CONFIG_SCX35L64) || defined (CONFIG_CHIP_ENV_SET) ) || defined(CONFIG_WHALE)|| defined (CONFIG_WHALE2)
#include <asm/arch/sprd_chipram_env.h>
#endif

static const char VERSION_STR[] = {"Spreadtrum Boot Block version 1.1"};
#ifdef CONFIG_USB_RESET
char fdl1_usb_reset[] __attribute__((section("fdl1_version"))) = {"##PORT-SECOND-ENUM##"};
#else
char fdl1_usb_reset[] __attribute__((section("fdl1_version"))) = {"00000000000000000000"};
#endif
#define printf(x...) do{}while(0)
static void error(void)
{
    printf("The first FDL failed!\r\n");
    for (;;) /*Do nothing*/;
}


#if defined (CONFIG_AUTODLOADER)
#ifdef HWRST_STATUS_AUTODLOADER
#undef HWRST_STATUS_AUTODLOADER
#endif
#define HWRST_STATUS_AUTODLOADER (0xa0)
int fdl1_check_autodloader(void)
{
	unsigned rst_mode= 0;
	rst_mode = ANA_REG_GET(ANA_REG_GLB_POR_RST_MONITOR);
	if(rst_mode == HWRST_STATUS_AUTODLOADER){
		ANA_REG_SET(ANA_REG_GLB_POR_RST_MONITOR, 0); //clear flag
		return 1;
	}
	return 0;
}
#endif/*CONFIG_AUTODLOADER*/
int main(void)
{
    PACKET_T *packet;

    FDL_PacketInit();
    FDL_DlInit();

	if (BOOT_FLAG_USB == FDL_GetBootMode())
		usb_init(USB_REG_BASE);

    FDL_DlReg(BSL_DDR_VERIFY,    ddr_verify_start, 0);
    FDL_DlReg(BSL_DDR_SR_TEST,    ddr_sr_test_start, 0);
    FDL_DlReg(BSL_CMD_CONNECT,    sys_connect,  0);
    FDL_DlReg(BSL_CMD_START_DATA, data_start,   0);
    FDL_DlReg(BSL_CMD_MIDST_DATA, data_midst,   0);
    FDL_DlReg(BSL_CMD_EXEC_DATA,  data_exec,    0);
    FDL_DlReg(BSL_CMD_END_DATA,   data_end,     0);
    FDL_DlReg(BSL_SET_BAUDRATE,   set_baudrate, 0);
    FDL_DlReg(BSL_CMD_OFF_CHG,    set_chg_flag, 0);
    for (;;)
    {
        char ch = gFdlUsedChannel->GetChar(gFdlUsedChannel);
        if (0x7e == ch)
            break;
    }

    packet = FDL_MallocPacket();
    packet->packet_body.type = BSL_REP_VER;
    packet->packet_body.size = sizeof(VERSION_STR);
    FDL_memcpy(packet->packet_body.content, VERSION_STR, sizeof(VERSION_STR));
    FDL_SendPacket(packet);
    FDL_FreePacket(packet);
#if defined(CONFIG_SCX35L64) || defined(CONFIG_CHIP_ENV_SET) || defined (CONFIG_WHALE)|| defined (CONFIG_WHALE2)
	chipram_env_set(BOOTLOADER_MODE_DOWNLOAD);
#endif
    FDL_DlEntry(DL_STAGE_NONE);

    error();
    return 1;
}


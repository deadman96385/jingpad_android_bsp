#include <common.h>
#include <boot_mode.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/common.h>
#include "adi_hal_internal.h"
#include <asm/arch/check_reboot.h>
#include <asm/arch/sprd_debug.h>
#include <sprd_pmic_misc.h>

#define KEY_PRESSED		0
#define KEY_NOT_PRESSED		1

unsigned reboot_reg = 0;
unsigned sysdump_flag = 0;
extern int hw_watchdog_rst_pending(void);
extern int is_hw_smpl_enable(void);
extern void power_down_cpu(ulong ignored);
extern int sprd_eic_request(unsigned offset);
extern int sprd_eic_get(unsigned offset);

static void rtc_domain_reg_write(uint32_t val)
{
#if  !defined(CONFIG_ADIE_SC2713S)  &&  !defined(CONFIG_ADIE_SC2713)
	sci_adi_write(ANA_REG_GLB_RTC_RST1, (~val),(~0)); //clear status reg
	sci_adi_write(ANA_REG_GLB_RTC_RST0, (val),(~0));  //set status reg
#else
	val = val;
#endif
}

static uint32_t rtc_domain_reg_read(void)
{
#if  !defined(CONFIG_ADIE_SC2713S)  &&  !defined(CONFIG_ADIE_SC2713)
	return sci_adi_read(ANA_REG_GLB_RTC_RST2);  //read
#else
	return 0;
#endif
}

unsigned check_reboot_mode(void)
{
	unsigned rst_mode= 0;
	unsigned hw_rst_mode = ANA_REG_GET(ANA_REG_GLB_POR_SRC_FLAG);
	debugf("hw_rst_mode==%x\n", hw_rst_mode);

/*for download mode reboot system */
	if(HWRST_RTCSTATUS_DOWNLOAD_BOOT == rtc_domain_reg_read()) {
		debugf("rtc_domain_reg get reboot normal mode \n");
		rtc_domain_reg_write(HWRST_RTCSTATUS_DEFAULT);
		ANA_REG_SET(ANA_REG_GLB_POR_RST_MONITOR, 0); //clear flag
		return CMD_NORMAL_MODE;
	}
/*for download mode reboot system ---- end*/

	reboot_reg = rst_mode = ANA_REG_GET(ANA_REG_GLB_POR_RST_MONITOR);
	sysdump_flag = rst_mode & HWRST_STATUS_SYSDUMPEN;
	printf("check_reboot_mode:get raw rst_mode is %x and sysdump_flag is %x\n",rst_mode,sysdump_flag);
	rst_mode &= 0xFF;
	ANA_REG_SET(ANA_REG_GLB_POR_RST_MONITOR, sysdump_flag | 0); //clear flag

	/* clear the flag which used by modem side in any scenes , prevent some errors */
	ANA_REG_SET(ANA_REG_GLB_WDG_RST_MONITOR, 0);

	debugf("rst_mode==%x\n",rst_mode);
	if(hw_watchdog_rst_pending()){
		debugf("hw watchdog rst int pending\n");
		if(rst_mode == HWRST_STATUS_RECOVERY)
			return CMD_RECOVERY_MODE;
		else if(rst_mode == HWRST_STATUS_FASTBOOT)
			return CMD_FASTBOOT_MODE;
		else if(rst_mode == HWRST_STATUS_NORMAL)
			return CMD_NORMAL_MODE;
		else if(rst_mode == HWRST_STATUS_NORMAL2)
			return CMD_WATCHDOG_REBOOT;
		else if(rst_mode == HWRST_STATUS_NORMAL3)
			return CMD_AP_WATCHDOG_REBOOT;
		else if(rst_mode == HWRST_STATUS_ALARM)
			return CMD_ALARM_MODE;
		else if(rst_mode == HWRST_STATUS_SLEEP)
			return CMD_SLEEP_MODE;
		else if(rst_mode == HWRST_STATUS_CALIBRATION)
			return CMD_CALIBRATION_MODE;
		else if(rst_mode == HWRST_STATUS_PANIC)
			return CMD_PANIC_REBOOT;
		else if(rst_mode == HWRST_STATUS_SPECIAL)
			return CMD_SPECIAL_MODE;
		else if(rst_mode == HWRST_STATUS_AUTODLOADER)
			return CMD_AUTODLOADER_REBOOT;
		else if(rst_mode == HWRST_STATUS_IQMODE)
			return CMD_IQ_REBOOT_MODE;
		else if(rst_mode == HWRST_STATUS_SPRDISK)
			return CMD_SPRDISK_MODE;
		else if(rst_mode == HWRST_STATUS_FACTORYTEST)
			return CMD_FACTORYTEST_MODE;
#if defined(CONFIG_X86)
		else if(rst_mode == HWRST_STATUS_MOBILEVISOR)
			return CMD_VMM_PANIC_MODE;
		else if(rst_mode == HWRST_STATUS_SECURITY)
			return CMD_TOS_PANIC_MODE;
#elif defined(HWRST_STATUS_SECURITY)
		else if(rst_mode == HWRST_STATUS_SECURITY)
			return CMD_TOS_PANIC_MODE;
#endif
		else{
			debugf(" a boot mode not supported\n");
			return 0;
		}
	}else{
		printf("is_7s_reset 0x%x, systemdump 0x%x\n", is_7s_reset(), is_7s_reset_for_systemdump());
		debugf("is_hw_smpl_enable %d\n", is_hw_smpl_enable());
		debugf("no hw watchdog rst int pending\n");
		if(rst_mode == HWRST_STATUS_NORMAL2)
			return CMD_UNKNOW_REBOOT_MODE;
		else if(is_7s_reset_for_systemdump())
			return CMD_UNKNOW_REBOOT_MODE;
		else if(is_7s_reset())
			return CMD_NORMAL_MODE;
		else if(hw_rst_mode & SW_EXT_RSTN_STATUS)
			return CMD_EXT_RSTN_REBOOT_MODE;
#ifndef CONFIG_SS_FUNCTION
		else if(is_smpl_bootup()) {
			debugf("SMPL bootup!\n");
			return CMD_NORMAL_MODE;
		}
#endif
		else
			return 0;
	}

}

void reset_to_normal(unsigned reboot_mode)
{
	unsigned rst_mode = 0;

#if  !defined(CONFIG_ADIE_SC2713S)  &&  !defined(CONFIG_ADIE_SC2713)
	if (CMD_NORMAL_MODE == reboot_mode) {
		rtc_domain_reg_write(HWRST_RTCSTATUS_DOWNLOAD_BOOT);
		udelay(300);
	}
#endif
	if (reboot_mode ==  CMD_NORMAL_MODE) {
		rst_mode = HWRST_STATUS_NORMAL;
	}

	ANA_REG_SET(ANA_REG_GLB_POR_RST_MONITOR, rst_mode);

	reset_cpu(0);
}
void reboot_devices(unsigned reboot_mode)
{
	unsigned rst_mode = 0;

	if(reboot_mode == CMD_RECOVERY_MODE){
		rst_mode = HWRST_STATUS_RECOVERY;
	}else if(reboot_mode == CMD_FASTBOOT_MODE){
		rst_mode = HWRST_STATUS_FASTBOOT;
	}else if(reboot_mode == CMD_NORMAL_MODE){
		rst_mode = HWRST_STATUS_NORMAL;
	}else{
		rst_mode = 0;
	}

	ANA_REG_SET(ANA_REG_GLB_POR_RST_MONITOR, rst_mode);

	reset_cpu(0);
}
void power_down_devices(unsigned pd_cmd)
{
	power_down_cpu(0);
}

int power_button_pressed(void)
{
	int eic_value,ret;
//maybe get button status from eic API is batter
	sprd_eic_request(EIC_PBINT);
	udelay(3000);
	eic_value = sprd_eic_get(EIC_PBINT);
	debugf("power_button_pressed status %x\n", eic_value);

#ifdef CONFIG_POWERKEY_DEFAULT_HIGH
	if (eic_value == 0)
		ret = KEY_PRESSED;
	else
		ret = KEY_NOT_PRESSED;
#else
	if (eic_value == 0)
		ret = KEY_NOT_PRESSED;
	else
		ret = KEY_PRESSED;
#endif

	return ret;
}

int alarm_triggered(void)
{
	//printf("ANA_RTC_INT_RSTS is 0x%x\n", ANA_RTC_INT_RSTS);
	debugf("value of it 0x%x\n", ANA_REG_GET(ANA_RTC_INT_RSTS));
	return ANA_REG_GET(ANA_RTC_INT_RSTS) & BIT_4;
}


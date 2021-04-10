#include <common.h>
#include <asm/io.h>

#include <regs_adi.h>
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_eic.h>
#include <sprd_battery.h>
#include <asm/arch/check_reboot.h>
#include <chipram_env.h>
#include <sprd_pmic_misc.h>
#include "sprd_chg_helper.h"
#ifdef DEBUG
#define debugf(fmt, args...) do { printf("bat:%s(): ", __func__); printf(fmt, ##args); } while (0)
#else
#define debugf(fmt, args...)
#endif

#define DCP_LIMIT_CUR	3000
#define SDP_LIMIT_CUR	500
#ifndef DCP_CHG_CUR
#define DCP_CHG_CUR	1000
#endif
#define SDP_CHG_CUR	450
#define FAST_CHG_VOL 3000

/* 30min = 30*60*1000ms*/
#define DEAD_DETECT_MS	(30 * 60 * 1000)
#define DEAD_DETECT_CNT	((DEAD_DETECT_MS) / (SPRDBAT_CHG_POLLING_T))
#define DEAD_DETECT_VOL	2000	/* 2000mv */
#define ENABLE_CHARGE_DOWNLOAD_THRESHOLD      3700

extern chipram_env_t* get_chipram_env(void);

extern void power_down_devices(unsigned pd_cmd);
extern int sprd_eic_request(unsigned offset);
extern int sprd_eic_get(unsigned offset);

static enum sprd_adapter_type adp_type;
static int chg_cur,limit_cur,fast_chg;
static const struct sprdchg_ic_operations *sprd_chg_ic_op;
static int count;

static void sprdchg_timer_callback(void)
{
	if (!sprd_chg_ic_op)
		return;

	count ++;
	if(count == 50){
		count = 0;
		sprd_chg_ic_op->timer_callback();
	}
}

void sprdbat_lowbat_chg(void)
{
	enum sprd_adapter_type charger = sprdchg_charger_is_adapter();
	unsigned int vbat_vol = sprdfgu_read_vbat_vol();
	static unsigned int polling_cnt = 0;
	static int dead_bat_flag = 0;

	if (!sprd_chg_ic_op)
		return;

	if (charger == ADP_TYPE_DCP) {
		limit_cur = DCP_LIMIT_CUR;
		chg_cur = DCP_CHG_CUR;
	} else {
		limit_cur = SDP_LIMIT_CUR;
		chg_cur = SDP_CHG_CUR;
	}

	if (charger != adp_type) {
		adp_type = charger;
		debugf("adp_type changed:%d\n", adp_type);
		sprd_chg_ic_op->chg_cmd(CHG_SET_LIMIT_CURRENT,limit_cur);

		/* if battery voltage is low, we use small current to charge */
		if (vbat_vol < FAST_CHG_VOL) {
			chg_cur = SDP_CHG_CUR;
			fast_chg = 0;
		}
		sprd_chg_ic_op->chg_cmd(CHG_SET_CURRENT,chg_cur);
	}

	if (!fast_chg && (vbat_vol > FAST_CHG_VOL)) {
		fast_chg = 1;
		sprd_chg_ic_op->chg_cmd(CHG_SET_CURRENT,chg_cur);
	}
	debugf("chg_cur:%d,limit_cur:%d\n",chg_cur,limit_cur);
	sprdchg_timer_callback();

	debugf("vbat_vol:%d\n", vbat_vol);

	/* dead battery detect */
	if (dead_bat_flag) {
		printf("ERR!!!:Dead battery,disable charge!!!\n");
	} else {
		polling_cnt ++;

		if (vbat_vol > DEAD_DETECT_VOL) {
			debugf("polling_cnt:%d clear,DEAD_DETECT_VOL:%d\n",
			    polling_cnt,DEAD_DETECT_VOL);
			polling_cnt = 0;
		}

		if(polling_cnt > DEAD_DETECT_CNT) {
			printf("ERR!!!:Dead battery shutdown charge now!!!\n");
			dead_bat_flag = 1;
			sprd_chg_ic_op->chg_stop(1);
		}
	}
}

void sprdchg_register_ops(const struct sprdchg_ic_operations *ops)
{
	sprd_chg_ic_op = ops;
}

const struct sprdchg_ic_operations *sprdchg_ic_ops_get(void)
{
	return sprd_chg_ic_op;
}

int charger_connected(void)
{
	sprd_eic_request(EIC_CHG_INT);
	udelay(3000);
	debugf("eica status %x\n", sprd_eic_get(EIC_CHG_INT));

	return !!sprd_eic_get(EIC_CHG_INT);
}

int get_mode_from_gpio(void)
{
	int ret = 0;
	unsigned hw_rst_mode;

	hw_rst_mode = ANA_REG_GET(ANA_REG_GLB_POR_SRC_FLAG);
	ret = (hw_rst_mode & HW_PBINT2_STATUS) && !charger_connected();

	return ret;
}

void sprdbat_init(void)
{
	boot_mode_t boot_role;
	unsigned int vbat_vol;
	unsigned int keep_charge;
	chipram_env_t* cr_env = get_chipram_env();

	boot_role = cr_env->mode;
	keep_charge = cr_env->keep_charge;

	sprdbat_help_init();
	sprdfgu_init();
	if (!sprd_chg_ic_op) {
		printf("ERR!!!:chg op is NULL....\n");
		printf("ERR!!!:chg op is NULL....\n");
		printf("ERR!!!:chg op is NULL....\n");
		printf("ERR!!!:chg op is NULL....\n");
		printf("ERR!!!:chg op is NULL....\n");
		printf("ERR!!!:chg op is NULL....\n");
		printf("ERR!!!:chg op is NULL....\n");
		return;
	}

	sprd_chg_ic_op->ic_init();

	/* if it's BOOTLOADER_MODE_DONLOAD, donot check battery is connect or not, return. */
	if(boot_role == BOOTLOADER_MODE_DOWNLOAD){
		if(!keep_charge) {
			if (sprdfgu_read_vbat_vol() < ENABLE_CHARGE_DOWNLOAD_THRESHOLD)
				sprd_chg_ic_op->chg_start(0);
			else
				sprd_chg_ic_op->chg_stop(0);

		}
		return;
	}

	//set charge current 500mA(USB) or 600mA(AC)
	if (charger_connected()) {
		adp_type = sprdchg_charger_is_adapter();
		if (adp_type == ADP_TYPE_DCP) {
			debugf("uboot adp AC\n");
			limit_cur = DCP_LIMIT_CUR;
			chg_cur = DCP_CHG_CUR;
		} else {
			limit_cur = SDP_LIMIT_CUR;
			chg_cur = SDP_CHG_CUR;
			debugf("uboot adp USB\n");
		}

		debugf("chg_cur:%d,limit_cur:%d\n",chg_cur,limit_cur);
		vbat_vol = sprdfgu_read_vbat_vol();
		/* if battery voltage is low, we use small current to charge */
		if (vbat_vol < FAST_CHG_VOL)
			chg_cur = SDP_CHG_CUR;
		else
			fast_chg = 1;

		sprd_chg_ic_op->chg_cmd(CHG_SET_LIMIT_CURRENT,limit_cur);
		sprd_chg_ic_op->chg_cmd(CHG_SET_CURRENT,chg_cur);
		sprd_chg_ic_op->chg_start(0);
	}

	//if battery do NOT connect, shutdown charge,maybe system poweroff
	if (!sprdbat_is_battery_connected()) {
		printf("battery unconnected shutdown charge!!!!!\n");
		sprd_chg_ic_op->chg_stop(0);
	}

	sprdfgu_late_init();
}


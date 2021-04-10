#include <common.h>
#include <asm/io.h>

#include <regs_adi.h>
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_eic.h>
#include <sprd_battery.h>
#include "sprd_chg_helper.h"
#ifdef DEBUG
#define debugf(fmt, args...) do { printf("fgu:%s(): ", __func__); printf(fmt, ##args); } while (0)
#else
#define debugf(fmt, args...)
#endif

extern int charger_connected(void);

extern void power_down_devices(unsigned pd_cmd);

#define REGS_FGU_BASE ANA_FGU_BASE
#define REG_FGU_START                   SCI_ADDR(REGS_FGU_BASE, 0x0000)
#define REG_FGU_CONFIG                  SCI_ADDR(REGS_FGU_BASE, 0x0004)
#define REG_FGU_INT_EN                  SCI_ADDR(REGS_FGU_BASE, 0x0010)
#define REG_FGU_INT_CLR                 SCI_ADDR(REGS_FGU_BASE, 0x0014)
#define REG_FGU_INT_RAW                 SCI_ADDR(REGS_FGU_BASE, 0x0018)
#define REG_FGU_VOLT_VAL                SCI_ADDR(REGS_FGU_BASE, 0x0020)
#define REG_FGU_OCV_VAL                 SCI_ADDR(REGS_FGU_BASE, 0x0024)
#define REG_FGU_POCV_VAL                SCI_ADDR(REGS_FGU_BASE, 0x0028)
#define REG_FGU_CURT_VAL                SCI_ADDR(REGS_FGU_BASE, 0x002c)
#define REG_FGU_CURT_OFFSET             SCI_ADDR(REGS_FGU_BASE, 0x0090)
#define BIT_VOLT_H_VALID                ( BIT(12) )
#define BITS_VOLT_DUTY(_x_)             ( (_x_) << 5 & (BIT(5)|BIT(6)) )
#define BIT_VOL_READY_INT				(BIT(6))

#define REG_FGU_USER_AREA_SET             SCI_ADDR(REGS_FGU_BASE, 0x00A0)
#define REG_FGU_USER_AREA_CLEAR             SCI_ADDR(REGS_FGU_BASE, 0x00A4)
#define REG_FGU_USER_AREA_STATUS             SCI_ADDR(REGS_FGU_BASE, 0x00A8)

#define BITS_POWERON_TYPE_SHIFT   12
#define BITS_POWERON_TYPE(_x_)           ( (_x_) << 12 & (0xF000))
#define BITS_RTC_AREA_SHIFT     0
#define BITS_RTC_AREA(_x_)           ( (_x_) << 0 & (0xFFF) )
#define BITSINDEX(b, o, w)		((b) * (w) + (o))

#define FIRST_POWERTON  0xF
#define NORMAIL_POWERTON  0x5
#define WDG_POWERTON  0xA

#define SPRDBAT_FGUADC_CAL_NO         	0
#define SPRDBAT_FGUADC_CAL_NV         	1
#define SPRDBAT_FGUADC_CAL_CHIP		2
#define VOL_READY_INT_THRESHOLD		1000


static int fgu_nv_4200mv = 2752;
static int fgu_nv_3600mv = 2374;

struct sprdfgu_cal {
	int vol_1000mv_adc;
	int vol_offset;
	int cal_type;
};

static struct sprdfgu_cal fgu_cal =
	{ 2872, 0, SPRDBAT_FGUADC_CAL_NO};

static u32 sprdfgu_adc2vol_mv(int adc)
{
	return ((adc + fgu_cal.vol_offset) * 1000)
		/ fgu_cal.vol_1000mv_adc;
}

static  int sprdfgu_reg_get(unsigned long reg)
{
	int old_value = sci_adi_read(reg);
	int new_value, times = 1000;

	while ((old_value != (new_value = sci_adi_read(reg))) &&
		(times > 0)) {
		old_value = new_value;
		times--;
	}
	return new_value;
}

uint32_t sprdfgu_read_vbat_vol(void)
{
	int cur_vol_raw;
	uint32_t temp;

	cur_vol_raw = sprdfgu_reg_get(REG_FGU_VOLT_VAL);
	temp = sprdfgu_adc2vol_mv(cur_vol_raw);
	return temp;
}

static void sprdfgu_rtc_reg_write(uint32_t val)
{
	sci_adi_write(REG_FGU_USER_AREA_CLEAR, BITS_RTC_AREA(~val),
		      BITS_RTC_AREA(~0));
	sci_adi_write(REG_FGU_USER_AREA_SET, BITS_RTC_AREA(val),
		      BITS_RTC_AREA(~0));
}

static uint32_t sprdfgu_rtc_reg_read(void)
{
	return (sci_adi_read(REG_FGU_USER_AREA_STATUS) & BITS_RTC_AREA(~0)) >>
	    BITS_RTC_AREA_SHIFT;
}

static void sprdfgu_poweron_type_write(uint32_t val)
{
	sci_adi_write(REG_FGU_USER_AREA_CLEAR, BITS_POWERON_TYPE(~val),
		      BITS_POWERON_TYPE(~0));
	sci_adi_write(REG_FGU_USER_AREA_SET, BITS_POWERON_TYPE(val),
		      BITS_POWERON_TYPE(~0));
}

static uint32_t sprdfgu_poweron_type_read(void)
{
	return (sci_adi_read(REG_FGU_USER_AREA_STATUS) & BITS_POWERON_TYPE(~0))
	    >> BITS_POWERON_TYPE_SHIFT;
}

static int sprdfgu_cal_get(unsigned int *p_cal_data)
{
	unsigned int data;

#if defined(CONFIG_ADIE_SC2723)
	data = sprd_pmic_efuse_read_bits(BITSINDEX(12, 0, 8), 9);
	debugf("fgu_cal_get 4.2 data data: 0x%x\n", data);
	p_cal_data[0] = (data + 6963) - 4096 - 256;

	return 0;

#elif defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721)|| defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	data = sprd_pmic_efuse_read_bits(BITSINDEX(3, 0, 16), 9);
	debugf("fgu_cal_get 4.2 data data: 0x%x\n", data);
	p_cal_data[0] = (data + 6963) - 4096 - 256;

	return 0;

#else
	data = sprd_pmic_efuse_read_bits(BITSINDEX(3, 0, 16), 9);
	debugf("fgu_cal_get 4.2 data data: 0x%x\n", data);
	p_cal_data[0] = (data + 6963) - 4096 - 256;

	return 0;
#endif
}

static void sprdfgu_cal_init(void)
{
	if (fgu_nv_3600mv == 0) {
		fgu_cal.vol_1000mv_adc =
		    DIV_ROUND_CLOSEST((fgu_nv_4200mv) * 10, 42);
		fgu_cal.vol_offset = 0;
	} else {
		fgu_cal.vol_1000mv_adc =
		    DIV_ROUND_CLOSEST((fgu_nv_4200mv - fgu_nv_3600mv) * 10, 6);
		fgu_cal.vol_offset =
		    0 - (fgu_nv_4200mv * 10 - fgu_cal.vol_1000mv_adc * 42) / 10;
	}

	debugf("4200mv=%d, 3600mv=%d\n", fgu_nv_4200mv, fgu_nv_3600mv);

	debugf("fgu_cal.vol_1000mv_adc=%d, vol_offset=%d\n",
		fgu_cal.vol_1000mv_adc, fgu_cal.vol_offset);
}

#define mdelay(_ms) udelay(_ms*1000)

static int sprdfgu_cal_from_chip(void)
{
	unsigned int fgu_data[4] = { 0 };

	if (sprdfgu_cal_get(fgu_data)) {
		debugf("efuse no cal data\n");
		return 1;
	}

	debugf("fgu_data: 0x%x\n", fgu_data[0]);

	fgu_nv_4200mv = fgu_data[0];
	fgu_nv_3600mv = 0;
	fgu_cal.cal_type = SPRDBAT_FGUADC_CAL_CHIP;
	debugf("sprdfgu: one point\n");
	return 0;
}

void sprdfgu_init(void)
{
	int cnt = VOL_READY_INT_THRESHOLD;

	sci_adi_set(ANA_REG_GLB_ARM_MODULE_EN, BIT_ANA_FGU_EN);
#if defined(CONFIG_ADIE_SC2721) || defined(CONFIG_ADIE_SC2720)  || defined(CONFIG_ADIE_SC2730)
	sci_adi_set(ANA_REG_GLB_RTC_CLK_EN, BIT_RTC_FGU_EN);
#else
	sci_adi_set(ANA_REG_GLB_RTC_CLK_EN, BIT_RTC_FGU_EN | BIT_RTC_FGUA_EN);
#endif
	sci_adi_clr(REG_FGU_INT_EN, 0xFFFF);	//disable int after watchdog reset
	sci_adi_set(REG_FGU_INT_CLR, 0xFFFF);
	sci_adi_write(REG_FGU_CURT_OFFSET, 0, ~0);	//init offset after watchdog reset

	/* When the symbol position BIT_VOL_READY_INT is 1,
	 * the FGU voltage can be picked up
	 */
	while (!(sci_adi_read(REG_FGU_INT_RAW) & BIT_VOL_READY_INT) && cnt--){
		mdelay(2);
	}

	if (cnt <= 0)
		printf("error!!! fgu voltage not ready!");

	sprdfgu_cal_from_chip();
	sprdfgu_cal_init();
}

void sprdfgu_late_init(void)
{
	if (charger_connected() && sprdbat_is_battery_connected()) {
		if ((FIRST_POWERTON == sprdfgu_poweron_type_read())
			|| (sprdfgu_rtc_reg_read() == 0xFFF)) {
			sprdfgu_rtc_reg_write(0xFF);
			mdelay(1);
			sprdfgu_poweron_type_write(NORMAIL_POWERTON);
			printf("charge first poweron reset!!!!!\n");
			mdelay(3);
			power_down_devices(0);
		}
	}

	if (sprdfgu_rtc_reg_read() == 0xFF) {
		printf("secend poweron !!!!!\n");
		sprdfgu_poweron_type_write(FIRST_POWERTON);
		mdelay(1);
		sprdfgu_rtc_reg_write(0xFFF);
	}
}


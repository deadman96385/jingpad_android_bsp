#include <common.h>
#include <boot_mode.h>
#include <part_efi.h>
#include "loader_common.h"
#include <sprd_common_rw.h>

u32 get_first_mode = 0;
u32 first_cali_mode = 0;
extern void download_after_enter_cali_mode(u8 cail_mode);

static first_boot_mode_t first_boot_mode[CMD_SET_FIRST_MAX_MODE] = {
	{CMD_SET_FIRST_NORMAL_BOOT_MODE, CMD_NORMAL_MODE, 0x0},

	{CMD_SET_FIRST_GSM_CLA_MODE, CMD_CALIBRATION_MODE, 0x1},
	{CMD_SET_FIRST_GSM_FINAL_TEST_MODE, CMD_CALIBRATION_MODE, 0x5},

	{CMD_SET_FIRST_WCDMA_CLA_MODE, CMD_CALIBRATION_MODE, 0xB},
	{CMD_SET_FIRST_WCDMA_FINAL_TEST_MODE, CMD_CALIBRATION_MODE, 0xC},

	{CMD_SET_FIRST_TDSCDMA_CLA_MODE, CMD_CALIBRATION_MODE, 0x7},
	{CMD_SET_FIRST_TDSCDMA_FINAL_TEST_MODE, CMD_CALIBRATION_MODE, 0x8},

	{CMD_SET_FIRST_LTETDD_CLA_MODE, CMD_CALIBRATION_MODE, 0x10},
	{CMD_SET_FIRST_LTETDD_FINAL_TEST_MODE, CMD_CALIBRATION_MODE, 0x11},

	{CMD_SET_FIRST_LTEFDD_CLA_MODE, CMD_CALIBRATION_MODE, 0x10},
	{CMD_SET_FIRST_LTEFDD_FINAL_TEST_MODE, CMD_CALIBRATION_MODE, 0x11},

	{CMD_SET_FIRST_NR5GSUB6G_CLA_MODE, CMD_CALIBRATION_MODE, 0x18},
	{CMD_SET_FIRST_NR5GSUB6G_FINAL_TEST_MODE, CMD_CALIBRATION_MODE, 0x19},

	{CMD_SET_FIRST_NRMMW_CLA_MODE, CMD_CALIBRATION_MODE, 0x18},
	{CMD_SET_FIRST_NRMMW_FINAL_TEST_MODE, CMD_CALIBRATION_MODE, 0x19},

	{CMD_SET_FIRST_CDMA2K_CLA_MODE, CMD_CALIBRATION_MODE, 0x12},
	{CMD_SET_FIRST_CDMA2K_FINAL_TEST_MODE, CMD_CALIBRATION_MODE, 0x13},

	{CMD_SET_FIRST_BBAT_MODE, CMD_AUTOTEST_MODE, 0},

	{CMD_SET_FIRST_NATIVE_MMI_MODE, CMD_FACTORYTEST_MODE, 0},

	{CMD_SET_FIRST_APK_MMI_MODE, CMD_APKMMI_MODE, 0},

	{CMD_SET_FIRST_NBIOT_CAL_MODE, CMD_CALIBRATION_MODE, 0x20},
	{CMD_SET_FIRST_NBIOT_FINAL_TEST_MODE, CMD_CALIBRATION_MODE, 0x21},

	{CMD_SET_FIRST_UPT_MODE, CMD_UPT_MODE, 0x0},
};

static int get_miscdata_boot_flag(char *out)
{
	if (0 != common_raw_read("miscdata", SET_FIRST_MDOE_LEN,
			(uint64_t)(SET_FIRST_MODE_OFFSET), out)) {
		errorf("partition <miscdata> read error\n");
		return -1;
	}

	return 0;
}

static int set_miscdata_boot_flag(char *in)
{
	if (0 != common_raw_write("miscdata", SET_FIRST_MDOE_LEN, (uint64_t)0,
			(uint64_t)(SET_FIRST_MODE_OFFSET), in)) {
		errorf("write partition <miscdata> fail\n");
		return -1;
	}

	return 0;
}

int read_boot_flag(void)
{
	u32 first_mode = 0;
	u32 clear_first_mode = 0;
	int err;

	err = get_miscdata_boot_flag((char *)(&get_first_mode));
	if (err < 0) {
		errorf("Reading mode from miscdata failed!\n");
		return CMD_UNDEFINED_MODE;
	}

	err = set_miscdata_boot_flag((char *)(&clear_first_mode));
	if (err < 0) {
		errorf("Clearing the miscdata set first mode flag failed!\n");
		return CMD_UNDEFINED_MODE;
	}

	if ((get_first_mode & 0xFFFFFF00) != SET_FIRST_MODE_MAGIC) {
		errorf("The data obtained from miscdata is not a magic number!\n");
		return CMD_UNDEFINED_MODE;
	}

	first_mode = get_first_mode & 0x000000FF;
	first_cali_mode = first_boot_mode[first_mode].cail_parameter;
	debugf("The mode obtained from miscdata: 0x%x.\n", first_mode);

	if ((first_mode > CMD_SET_FIRST_NORMAL_BOOT_MODE) &&
			(first_mode < CMD_SET_FIRST_MAX_MODE)) {
		if (first_boot_mode[first_mode].boot_mode == CMD_CALIBRATION_MODE)
			download_after_enter_cali_mode(first_boot_mode[first_mode].cail_parameter);
		else if (first_boot_mode[first_mode].boot_mode == CMD_AUTOTEST_MODE)
			download_after_enter_autotest_mode(first_boot_mode[first_mode].cail_parameter);

		return first_boot_mode[first_mode].boot_mode;
	}

	return CMD_UNDEFINED_MODE;
}
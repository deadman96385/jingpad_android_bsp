#include <common.h>
#include <boot_mode.h>
#include <part_efi.h>
#include "loader_common.h"
#include <sprd_common_rw.h>

extern void reboot_devices(unsigned reboot_mode);

/* Recovery Message */
struct recovery_message {
	char command[32];
	char status[32];
	char recovery[1024];
};

int get_recovery_message(struct recovery_message *out)
{
#ifdef OTA_BACKUP_MISC_RECOVERY
	int ret = 0;
	disk_partition_t info;
	block_dev_desc_t *p_block_dev = NULL;

	p_block_dev = get_dev("mmc", 0);
	if (NULL == p_block_dev)
		return -1;
        if (0 != get_partition_info_by_name(p_block_dev, "misc", &info))
		return -1;

	debugf("info.attributes.power_off_protection=%d\n", info.attributes.fields.power_off_protection);
	if (1 == info.attributes.fields.power_off_protection) {
		debugf("get the power-off protection flag, need to check the misc file in sd card\n");
		ret = get_recovery_msg_in_sd((void*)out,sizeof(struct recovery_message));
		if (ret > 0) {
			debugf("get recovery image from sd card\n");
			return 0;
		} else {
			debugf("no recovery image in sd card\n");
		}
	}
#endif

	if (0 != common_raw_read("misc", sizeof(struct recovery_message), (uint64_t)0, (char *)out)) {
		errorf("partition <misc> read error, can not get recovery message\n");
		return -1;
	}

	return 0;

}

#ifndef CONFIG_NAND_BOOT
int set_recovery_message(const struct recovery_message *in)
{
	if (common_raw_write("misc", sizeof(struct recovery_message), (uint64_t)0, (uint64_t)0, (char *)in)) {
		errorf("write partition <misc> fail\n");
		return -1;
	}
	return 0;
}

#else

int set_recovery_message(const struct recovery_message *in)
{
	uint32_t size = sizeof(struct recovery_message);

	if (do_raw_data_write("misc", size, size, (uint32_t)0, (char *)in)) {
		errorf("write misc data error");
		return -1;
	}
	return 0;
}
#endif

int get_mode_from_file(void)
{

	struct recovery_message msg;
	char partition_name[32];
	unsigned valid_command = 0;

	/*get recovery message */
	if (get_recovery_message(&msg))
		return CMD_UNKNOW_REBOOT_MODE;
	if (msg.command[0] != 0 && msg.command[0] != 255) {
		debugf("Recovery command: %.*s\n", sizeof(msg.command), msg.command);
	}
	/*Ensure termination */
	msg.command[sizeof(msg.command) - 1] = '\0';

	if (!strcmp("boot-recovery", msg.command)) {
		debugf("%s:Message in misc indicate the RECOVERY MODE\n", __FUNCTION__);
		return CMD_RECOVERY_MODE;
	} else if (!strcmp("update-radio", msg.command)) {
		strcpy(msg.status, "OKAY");
		strcpy(msg.command, "boot-recovery");
		/*send recovery message */
		set_recovery_message(&msg);
		reboot_devices(0);
		return CMD_UNKNOW_REBOOT_MODE;
	} else {
		return 0;
	}
}

/* set recovery message to boot fastbootd */
int set_recovery_run_fastbootd(void)
{
	struct recovery_message msg = {0};

	strcpy(msg.command, "boot-fastboot");
	strcpy(msg.recovery, "recovery\n");
	strcpy(msg.recovery, "--fastboot\n");

	set_recovery_message(&msg);
	return 0;
}

/* clear recovery message for boot fastbootd */
int clear_recovery_not_run_fastbootd(void)
{
	struct recovery_message msg = {0};

	strcpy(msg.command, "boot-recovery");
	strcpy(msg.recovery, "recovery\n");

	set_recovery_message(&msg);
	return 0 ;
}

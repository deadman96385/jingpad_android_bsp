#include <common.h>
#include <command.h>
#include <linux/types.h>
#include <chipram_env.h>


chipram_env_t  local_chipram_env;


void setup_chipram_env(void)
{
	chipram_env_t * env = CHIPRAM_ENV_LOCATION;

	if (CHIPRAM_ENV_MAGIC != env->magic) {
		printf("Chipram magic wrong ,mode data may be broken\n");
		return 0;
	}

	local_chipram_env = * env;

}

chipram_env_t* get_chipram_env(void)
{
	return &local_chipram_env;
}

boot_mode_t get_boot_role(void)
{
	boot_mode_t boot_role;
	chipram_env_t* cr_env = get_chipram_env();
	boot_role = cr_env->mode;
	return boot_role;
}

int do_role(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
#ifdef CONFIG_ZEBU
	boot_mode_t boot_role = BOOTLOADER_MODE_LOAD;
#else
	boot_mode_t boot_role = get_boot_role();
#endif
	switch(boot_role) {
		case BOOTLOADER_MODE_DOWNLOAD:
			setenv("bootdelay", "0");
			setenv("bootcmd", "download");
			debugf("Get chipram env mode %x,go download\n", boot_role);
			break;
		case BOOTLOADER_MODE_LOAD:
			setenv("bootcmd", "cboot");
			debugf("Get chipram env mode %x,go cboot\n", boot_role);
			break;
		default :
			printf("unkown uboot role ,nothing to do in preboot\n");
	}

	return 0;
}


U_BOOT_CMD(
		  role, CONFIG_SYS_MAXARGS, 1, do_role,
		  "choose the role of spreadtrum uboot",
		  "two roles:dloader and cboot\n"
		);


#include <config.h>
#include <common.h>
#include <boot_mode.h>
#include <asm/io.h>
#if defined CONFIG_CHIP_ENV_SET
#include <asm/arch/sprd_chipram_env.h>
#endif
#include <adi.h>
#include <asm/arch/sprd_reg.h>

void nand_boot(void)
{
	int ret;
	__attribute__ ((noreturn)) void (*uboot) (void);

#if defined	CONFIG_CHIP_ENV_SET
	chipram_env_set(BOOTLOADER_MODE_LOAD);
#endif

#ifdef CONFIG_LOAD_ATF
	uboot = (void *)CONFIG_SML_LDADDR_START;
#else
	uboot = (void *)CONFIG_SYS_NAND_U_BOOT_START;
#endif

	(*uboot) ();
}



#ifndef __CONFIG_CHIP_H
#define __CONFIG_CHIP_H

//#define CONFIG_SECURE_BOOT
//#define CONFIG_ROM_VERIFY_SPL



#define CONFIG_AUTODLOADER

#define CHIP_ENDIAN_LITTLE
#define _LITTLE_ENDIAN 1

#ifdef CONFIG_SECURE_BOOT
#define CONFIG_SPL_LOAD_LEN	(0x8000)
#else
#define CONFIG_SPL_LOAD_LEN     (0x6000)
#endif

/*
 * Serial Info
 */
#define CONFIG_SYS_SC8800X_UART1	1


/* U-Boot general configuration */
#define CONFIG_SYS_PROMPT	"=> "	/* Monitor Command Prompt */
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size  */
/* Print buffer sz */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + \
		sizeof(CONFIG_SYS_PROMPT) + 16)




/* U-Boot commands */
#include <config_cmd_default.h>

#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_NET
#undef CONFIG_CMD_SETGETDCR



#define xstr(s)	str(s)
#define str(s)	#s

#endif /* __CONFIG_CHIP_H */

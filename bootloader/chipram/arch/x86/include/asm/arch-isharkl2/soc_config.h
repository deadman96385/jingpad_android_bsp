#ifndef SOC_CONFIG_H
#define SOC_CONFIG_H

#define MAX_PKT_SIZE    0x1000 /* Just data field of a packet excluding header and checksum */
#define PACKET_MAX_NUM    3

#define CONFIG_FRMCHECK
#define CONFIG_PAD_TO 0xE5003000
#define CONFIG_BIN_SIZE 100000
#define CONFIG_SPL_BASE
#define CONFIG_EMMC_BOOT
#define CONFIG_MMC_V40
#define CONFIG_IEFUSE
#define CONFIG_SECURE_EFUSE
#define CONFIG_DUAL_BACKUP

#endif

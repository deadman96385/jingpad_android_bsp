
#ifndef SOC_CONFIG_H
#define SOC_CONFIG_H

#define MAX_PKT_SIZE    0x1000 /* Just data field of a packet excluding header and checksum */
#define PACKET_MAX_NUM    3

#define CONFIG_FRMCHECK
#define CONFIG_PAD_TO 0x50003C00
#define CONFIG_BIN_SIZE 49152

#define CONFIG_EMMC_BOOT
#define CONFIG_SPRD_DMC_R3P0
#define CONFIG_MENTOR_USB
#define SECURITY_HEADER
#define CONFIG_MMC_V40
#define CONFIG_SECURE_EFUSE

#endif

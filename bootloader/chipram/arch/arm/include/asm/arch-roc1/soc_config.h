#ifndef SOC_CONFIG_H
#define SOC_CONFIG_H

#define MAX_PKT_SIZE    0x1000 /* Just data field of a packet excluding header and checksum */
#define PACKET_MAX_NUM    3

#define CONFIG_FRMCHECK
#define CONFIG_SECURE_EFUSE
#define CONFIG_PAD_TO 0x00008C00
#define CONFIG_BIN_SIZE 57808
#define CONFIG_SPL_BASE
#define CONFIG_SPRD_DDRC_R1P1
#define CONFIG_USB_DWC3
#define CONFIG_EFUSE
#define CONFIG_FDL_CHECK_SIGN
#define CONFIG_ARM64

#endif

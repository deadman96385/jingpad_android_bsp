#ifndef __ROMCODE_DOWNLOAD_H__
#define __ROMCODE_DOWNLOAD_H__

int romcode_flow_exec(unsigned int addr);
int romcode_flow_start(void);
int romcode_flow_download_nocrc(unsigned int addr, const void *buf,
				unsigned int len, unsigned int packet_max);

#define WCN_USB_FDL_ADDR 0x40f00000
#define WCN_USB_FW_ADDR 0x100000
#define WCN_USB_FDL_PATH \
	"/dev/block/platform/soc/soc:ap-ahb/50430000.sdio/by-name/wcnfdl"

#define WCN_USB_FDL_SIZE 1024

#endif

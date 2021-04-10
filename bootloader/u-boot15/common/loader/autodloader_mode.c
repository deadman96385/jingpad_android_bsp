//#include <boot_mode.h>
#include <common.h>
#include <packet.h>
#include <dl_cmd_def.h>
#include "asm/arch/sprd_reg.h"
#include "adi_hal_internal.h"
#include <dl_channel.h>
#include "asm/arch/check_reboot.h"
#include <malloc.h>
#include <linux/usb/ch9.h>
#include <linux/usb/usb_uboot.h>

#define USB_ENUM_MS 300000


static const char VERSION_STR[] = {"SPRD4:AutoD"};

int act_as_romcode = 0;

extern struct FDL_ChannelHandler *gFdlUsedChannel;
#ifndef CONFIG_NAND_BOOT
extern uint64_t emmc_buf_size;
#endif
extern int usb_serial_init(void);
extern int usb_is_port_open(void);
extern int usb_is_configured(void);
extern void usb_init (uint32_t autodl_mode);

extern int do_download(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);

static struct dl_cmd *adl_cmdlist = NULL;

void adl_cmd_register(enum dl_cmd_type type,
		       int (*handle)(struct dl_packet *pkt, void *arg))
{
	//debugf("%s:enter\n");
	struct dl_cmd *cmd = (void *)0;

	cmd = (struct dl_cmd *)malloc(sizeof(struct dl_cmd));

	if (cmd) {
		cmd->type = type;
		cmd->handle = handle;
		cmd->next = adl_cmdlist;
		adl_cmdlist = cmd;
	}
	return;
}
void adl_cmd_handler(void)
{
	struct dl_cmd *cmd;
	struct dl_packet *pkt;
	debugf("%s:enter\n", __func__);
	for (;;) {
		//printf("befor get_pkt\n");
		pkt = dl_get_packet();
		pkt->body.type = (pkt->body.type >> 8 | pkt->body.type << 8);
		pkt->body.size = (pkt->body.size >> 8 | pkt->body.size << 8);
		for (cmd = adl_cmdlist; cmd; cmd = cmd->next) {
			if(cmd->type != pkt->body.type)
				continue;
			cmd->handle(pkt,NULL);
			dl_free_packet(pkt);
			break;
		}
	}
	return 0;
}

void adl_send_version(void)
{
	char ch;
	dl_packet_t *packet;
	for (;;) {
		ch = gFdlUsedChannel->GetChar(gFdlUsedChannel);
		if (0x7e == ch)
			break;
	}

	packet = FDL_MallocPacket();
	packet->body.type = BSL_REP_VER;
	packet->body.size = sizeof(VERSION_STR);
	memcpy(packet->body.content, VERSION_STR, sizeof(VERSION_STR));
	dl_send_packet(packet);
	dl_free_packet(packet);
}

int autodloader_initusb(void)
{
	ulong now;

	usb_driver_init(USB_SPEED_HIGH);
	usb_serial_init();

	now = 0;
	while(!usb_is_configured()){
		mdelay(1);
		now++;
		if(now > USB_ENUM_MS) {
			printf("USB SERIAL CONFIGED failed \n");
			return -1;
		}
	}
	printf("USB SERIAL CONFIGED\n");

	printf("Waiting For USB SERIAL PORT OPEN ... ... \n");
	while(!usb_is_port_open());
	printf("USB SERIAL PORT OPENED\n");

	//gs_open();

	return 0;
}


int autodloader_connect(dl_packet_t *packet, void *arg)
{
	//debugf("connect~~~\n");
	dl_send_ack(BSL_REP_ACK);
	return 1;
}

int autodloader_start(dl_packet_t *packet, void *arg)
{
	//debugf("start@@@\n");
	dl_send_ack(BSL_REP_ACK);
	return 1;
}

int autodloader_midst(dl_packet_t *packet, void *arg)
{
	//debugf("midst$$$\n");
	dl_send_ack(BSL_REP_ACK);
	return 1;
}

int autodloader_end(dl_packet_t *packet, void *arg)
{
	//debugf("end###\n");
	dl_send_ack(BSL_REP_ACK);
	return 1;
}

int autodloader_baudrate(dl_packet_t *packet, void *arg)
{
	//debugf("baudrate changed###\n");
	dl_send_ack(BSL_REP_ACK);
	return 1;
}

int autodloader_charger(dl_packet_t *packet, void *arg)
{
	debugf("set charger###\n");
	dl_send_ack(BSL_REP_ACK);
	return 1;
}


int autodloader_exec(dl_packet_t *packet, void *arg)
{
	static uint32_t cheater = 0;
	if (0 == cheater) {
		debugf("reply exec act as Romcode\n");
		dl_send_ack(BSL_REP_ACK);
		/*now we finish our role of RomCode, and start to play as fdl1*/
		act_as_romcode = 0;
		adl_send_version();
		cheater++;
	} else {
		/*our cosplay finish, and start the real download*/
		do_download(NULL, 0, 0, NULL);
	}

	return 1;
}


int autodloader_mainhandler(void)
{
	/*clear autodloader flag*/
	ANA_REG_SET(ANA_REG_GLB_POR_RST_MONITOR, 0);
	/*start from here, we play a role of RomCode*/
	act_as_romcode = 1;
#ifndef CONFIG_NAND_BOOT
	emmc_buf_size = SZ_128M;
	debugf("emmc_buf_size = 0x%llx\n",emmc_buf_size);
#endif
	/* initialize usb module*/
	if(autodloader_initusb())
		return 0;

	usb_init(1);
	dl_packet_init();

	debugf("start register adl cmd\n");
	adl_cmd_register(BSL_CMD_CONNECT,    autodloader_connect);
	adl_cmd_register(BSL_CMD_START_DATA, autodloader_start);
	adl_cmd_register(BSL_CMD_MIDST_DATA, autodloader_midst);
	adl_cmd_register(BSL_CMD_EXEC_DATA,  autodloader_exec);
	adl_cmd_register(BSL_CMD_END_DATA,   autodloader_end);
	adl_cmd_register(BSL_SET_BAUDRATE,   autodloader_baudrate);
	adl_cmd_register(BSL_CMD_OFF_CHG,    autodloader_charger);

	/*act as RomCode and send a version reply*/
	adl_send_version();

	adl_cmd_handler();

	return 0;
}



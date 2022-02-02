#include "romcode_download.h"

#ifdef CONFIG_WCN_USB
#include "wcn_usb.h"
#define USB_DOWNLOAD_TX_CHN 2
#define USB_DOWNLOAD_RX_CHN 18

static int romcode_msg_send(char *data, unsigned int data_len)
{
	int ret;
	int actual_len;

	struct wcn_usb_ep *tx_ep = wcn_usb_store_get_ep(USB_DOWNLOAD_TX_CHN);

	if (!tx_ep)
		return -EIO;

	ret = wcn_usb_msg(tx_ep, data, data_len, &actual_len, 3000);
	if (ret) {
		wcn_usb_err("wcn %s sent msg is error %d\n", __func__, ret);
		return ret;
	}

	if (actual_len != data_len) {
		wcn_usb_err("wcn %s sent msg's len is error\n", __func__);
		ret = -EIO;
	}

	return ret;
}

static int romcode_msg_recv(char *data, unsigned int *data_len)
{
	int ret;
	int actual_len;

	struct wcn_usb_ep *rx_ep = wcn_usb_store_get_ep(USB_DOWNLOAD_RX_CHN);

	if (!rx_ep)
		return -EIO;

	ret = wcn_usb_msg(rx_ep, data, *data_len, &actual_len, 3000);
	if (ret) {
		wcn_usb_err("wcn %s recv msg is error %d\n", __func__, ret);
		return ret;
	}

	if (actual_len > *data_len) {
		wcn_usb_err("wcn %s recv msg's len is error\n", __func__);
		return -EIO;
	}

	*data_len = actual_len;
	return ret;
}

#endif

#define DEFAULT_RECV_LEN 128
static int romcode_sent_command(const char *command,
				unsigned int command_len, const char *ack,
				unsigned int ack_len)
{
	int ret;
	char *command_temp;
	int actual_len = command_len > DEFAULT_RECV_LEN ?
	    command_len : DEFAULT_RECV_LEN;

	command_temp = kmalloc(actual_len, GFP_KERNEL);
	if (!command_temp)
		return -ENOMEM;
	memcpy(command_temp, command, command_len);

	/* sent command */
	ret = romcode_msg_send(command_temp, command_len);
	if (ret) {
		wcn_usb_err("wcn %s sent msg is error\n", __func__);
		goto OUT;
	}

	/* get ack and compare */
	ret = romcode_msg_recv(command_temp, &actual_len);
	if (ret) {
		wcn_usb_err("wcn %s recv io is not ok\n", __func__);
		ret = -EIO;
		goto OUT;

	}
	if (ack_len > actual_len || strncmp(ack, command_temp, ack_len)) {
		wcn_usb_err("wcn %s ack is not ok\n", __func__);
		print_hex_dump(KERN_DEBUG, "WCN ack", 0, 16, 1,
			       command_temp, 128, 1);
		print_hex_dump(KERN_DEBUG, "WCN command", 0, 16, 1,
			       command, command_len, 1);
		ret = -EIO;
		goto OUT;
	}

OUT:
	kfree(command_temp);

	return ret;
}

static unsigned short crc16_xmodem_cal(unsigned char *buf, unsigned int buf_len)
{
	unsigned int i;
	unsigned short crc = 0;

	while (buf_len-- != 0) {
		for (i = 0x80; i != 0; i = i >> 1) {
			if ((crc & 0x8000) != 0) {
				crc = crc << 1;
				crc = crc ^ 0x1021;
			} else {
				crc = crc << 1;
			}

			if ((*buf & i) != 0)
				crc = crc ^ 0x1021;
		}

		buf++;
	}

	return crc;
}

/* The following command do not need to conver */
static const char get_version[] = { 0x7E };

static const char get_version_ack[] = {
	0x7E, 0x00, 0x81, 0x00, 0x06, 0x53, 0x50,
	0x52, 0x44, 0x33, 0x00, 0x57, 0x0A, 0x7E
};

static const char connect[] = {
	0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7E
};

static const char common_ack[] = {
	0x7E, 0x00, 0x80, 0x00, 0x00, 0x3B, 0x5A, 0x7E
};

static const char end_download[] = {
	0x7E, 0x00, 0x03, 0x00, 0x00, 0x59, 0x50, 0x7E
};

/* 0x7e 0x7d is a magic number, we replace it with [0x5e 0x7d] or [0x5d 0x7d] */
unsigned short romcode_command_replace_magic(char *command, unsigned short len)
{
	unsigned short tail = len - 1;
	unsigned short i;
	unsigned short j;

	/* no head and no tail because they are 0x7e */
	for (i = len - 2; i > 0; i--) {
		if (command[i] == 0x7E || command[i] == 0x7D) {
			tail += 1;
			for (j = tail; j > i; j--)
				command[j] = command[j - 1];
			command[i + 1] = 0x50 | (command[i + 1] & 0x0F);
			command[i] = 0x7D;
		}
	}

	return tail + 1;
}

int romcode_sent_start_download(unsigned int addr, unsigned int len)
{
	unsigned short command_len = 16;
	char command[20] = { 0x7E,	/* head */
		0x00, 0x01,	/* command type */
		0x00, 0x08,	/* for command data len */
		0x00, 0x00, 0x00, 0x00,	/* addr */
		0x00, 0x00, 0x00, 0x00,	/* data len */
		0x00, 0x00,	/* for crc */
		0x7E /* tail */
	};

	*((u32 *)&command[5]) = cpu_to_be32(addr);
	*((u32 *)&command[9]) = cpu_to_be32(len);

	*((u16 *)&command[command_len - 3]) =
	    cpu_to_be16(crc16_xmodem_cal(&command[1], command_len - 4));

	command_len = romcode_command_replace_magic(command, 16);

	return romcode_sent_command(command, command_len,
				    common_ack, sizeof(common_ack));
}

int romcode_sent_exec(unsigned int addr)
{
	unsigned short command_len = 12;
	char command[16] = { 0x7E,	/* head */
		0x00, 0x04,	/* command type */
		0x00, 0x04,	/* command len */
		0x00, 0x00, 0x00, 0x00,	/* addr */
		0x00, 0x00,	/* for crc */
		0x7E /* tail */
	};

	*((u32 *)&command[5]) = cpu_to_be32(addr);

	*((u16 *)&command[command_len - 3]) =
	    cpu_to_be16(crc16_xmodem_cal(&command[1], command_len - 4));

	command_len = romcode_command_replace_magic(command, 12);

	return romcode_sent_command(command, command_len,
				    common_ack, sizeof(common_ack));
}

#define romcode_sent_get_version()				\
	romcode_sent_command(get_version, sizeof(get_version),	\
			get_version_ack, sizeof(get_version_ack))
#define romcode_sent_connect()				\
	romcode_sent_command(connect, sizeof(connect),	\
			common_ack, sizeof(common_ack))
#define romcode_sent_end_download()				\
	romcode_sent_command(end_download, sizeof(end_download),	\
			common_ack, sizeof(common_ack))

/*
 * 1. sent command "get_version"
 * 2. sent command "connect"
 */
int romcode_flow_start(void)
{
	int ret;

	ret = romcode_sent_get_version();
	if (ret) {
		wcn_usb_err("%s start command is error\n", __func__);
		return ret;
	}

	ret = romcode_sent_connect();
	if (ret) {
		wcn_usb_err("%s connect command is error\n", __func__);
		return ret;
	}

	return 0;
}

int romcode_flow_exec(unsigned int addr)
{
	int ret;

	ret = romcode_sent_exec(addr);
	if (ret) {
		wcn_usb_err("%s exec command is error\n", __func__);
		return ret;
	}

	return 0;
}

/*
 * 1. sent command "start download"
 * 2. sent data
 * 3. sent download
 *
 * NOTE:
 * 1. this function __MUST__ called after "romcode_flow_start"
 * 2. this function will __NOT__ sent crc! (for usb)
 * 3. arg "packet_max" is not used. usb bus will download all data once.
 */
int romcode_flow_download_nocrc(unsigned int addr, const void *buf,
				unsigned int len, unsigned int packet_max)
{
	int ret;

	ret = romcode_sent_start_download(addr, len);
	if (ret) {
		wcn_usb_err("start download command is error\n");
		return ret;
	}

	/* we sent data as command because it donot need crc for usb */
	ret = romcode_sent_command(buf, len, common_ack, sizeof(common_ack));
	if (ret) {
		wcn_usb_err("donwload img is error\n");
		return ret;
	}

	ret = romcode_sent_end_download();
	if (ret) {
		wcn_usb_err("end donwload command is error\n");
		return ret;
	}

	return 0;
}

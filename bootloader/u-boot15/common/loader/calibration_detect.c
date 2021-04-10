#include "calibration_detect.h"
#include "sprd_cpcmdline.h"
#include "loader_common.h"
#include <asm/arch/check_reboot.h>
#include <chipram_env.h>
#include <linux/usb/ch9.h>
#include <linux/usb/usb_uboot.h>
#include <sprd_common_rw.h>

#define MAX_CALIBRATION_LEN   50
#define CMD_BUF_NUMBER 20

static unsigned int nv_buffer[128]={0};
static int s_is_calibration_mode = 0;
static char calibration_cmd_buf[MAX_CALIBRATION_LEN] = {0};
uint8_t pctool_cmd_buf[CMD_BUF_NUMBER];
uint8_t pctool_cnf_buf[20];


char *get_calibration_parameter(void)
{
	if(s_is_calibration_mode != 0)
		return calibration_cmd_buf;
	else
		return NULL;
}

bool is_calibration_by_uart(void)
{
    return (2 == s_is_calibration_mode);
}

#define mdelay(_ms) udelay(_ms*1000)
#define CALIBERATE_STRING_LEN 10
#define CALIBERATE_HEAD 0x7e
#define CALIBERATE_COMMOND_T 0xfe
#define CALIBERATE_COMMAND_REQ  1

#define CALIBERATE_DEVICE_NULL  0
#define CALIBERATE_DEVICE_USB   1
#define CALIBERATE_DEVICE_UART  2

extern int charger_connected(void);
typedef  struct tag_cali_command {
	unsigned int   	reserved;
	unsigned short  size;
	unsigned char   cmd;
	unsigned char   sub_cmd;
} COMMAND_T;

extern int serial_tstc(void);
static unsigned long start_time;
static unsigned long now_time;



static int caliberate_device = CALIBERATE_DEVICE_NULL;

static void send_caliberation_request(void)
{
	COMMAND_T cmd;
        unsigned int i;
        unsigned char *data = (unsigned char *)&cmd;

        cmd.reserved = 0;
        cmd.cmd = CALIBERATE_COMMOND_T;
        cmd.size = CALIBERATE_STRING_LEN-2;
        cmd.sub_cmd = CALIBERATE_COMMAND_REQ;

        serial_putc(CALIBERATE_HEAD);

        for (i = 0; i < sizeof(COMMAND_T); i++)
             serial_putc(data[i]);

        serial_putc(CALIBERATE_HEAD);
}

static int receive_caliberation_response(uint8_t *buf,int len)
{
        int count = 0;
        int ch;
        uint32_t is_not_empty = 0;
        uint32_t start_time = 0,current_time = 0;

	if ((buf == NULL) || (len == 0))
        	return 0;

        is_not_empty = serial_tstc();
        if (is_not_empty) {
             start_time = get_timer_masked();
             do {
                  do {
                  	ch = serial_getc();
                  	if (count < CALIBERATE_STRING_LEN)
		        	buf[count++] = ch;
                  } while (serial_tstc());

                  if ((count >= CALIBERATE_STRING_LEN) || (count >= len)) {
                       caliberate_device = CALIBERATE_DEVICE_UART;
                       break;
                  }

                  current_time = get_timer_masked();
             } while((current_time - start_time) < 500);
        }

        return count;
}

unsigned int check_caliberate(uint8_t * buf, int len)
{
	unsigned int command = 0;
    	unsigned int freq = 0;

	if (len != CALIBERATE_STRING_LEN)
		return 0;

	if ((*buf == CALIBERATE_HEAD) && (*(buf + len -1) == CALIBERATE_HEAD)) {
		if ((*(buf+7) == CALIBERATE_COMMOND_T) && (*(buf + len - 2) != 0x1)) {
			command = *(buf + len - 2);
			command &= 0x7f;

            		freq = *(buf + 1);
            		freq = freq << 8;
            		freq += *(buf + 2);

            		command += freq << 8;
		}
	}

	return command;
}

int pctool_mode_detect_uart(void)
{
	int i, ret;
	unsigned int caliberate_mode;
	uint8_t buf[20];
	int got = 0;

	printf("%s\n", "uart calibrate detecting");
	send_caliberation_request();

#ifdef CONFIG_MODEM_CALIBERATE
	for(i = 0; i < 20; i++)
		buf[i] = i + 'a';

	start_time = get_timer_masked();
	while (1) {
		got = receive_caliberation_response(buf, sizeof(buf));
		if (caliberate_device == CALIBERATE_DEVICE_UART)
			break;

		now_time = get_timer_masked();
		if ((now_time - start_time) > CALIBRATE_ENUM_MS) {
			printf("usb calibrate configuration timeout\n");
			return -1;
		}
	}

	printf("caliberate : what got from host total %d is \n", got);
	for (i = 0; i < got; i++)
		printf("0x%x ", buf[i]);
	printf("\n");

	caliberate_mode = check_caliberate(buf, CALIBERATE_STRING_LEN);
	if (!caliberate_mode) {
		printf("func: %s line: %d caliberate failed\n", __func__, __LINE__);
		return -1;
    } else {
		memset(calibration_cmd_buf, 0, MAX_CALIBRATION_LEN);
		s_is_calibration_mode = 2;

		switch (caliberate_mode & 0xff){
			case CALIBERATE_COMMAND_AUTOTEST:
				snprintf(calibration_cmd_buf, MAX_CALIBRATION_LEN, "autotest=1 ");
				ret = CMD_AUTOTEST_MODE;
				break;
			default:
				snprintf(calibration_cmd_buf, MAX_CALIBRATION_LEN, "calibration=%d,%d,130 ", caliberate_mode&0xff, (caliberate_mode&(~0xff))>>8);
				ret = CMD_CALIBRATION_MODE;
				break;
		}
		return ret;
	}
#endif
	/* nerver come to here */
	return -1;
}


unsigned long get_cal_enum_ms(void)
{
    return CALIBRATE_ENUM_MS;
}

unsigned long get_cal_io_ms(void)
{
    return CALIBRATE_IO_MS;
}


int check_pctool_cmd(uint8_t* buf, int len)
{
    int command = 0;
    unsigned int freq = 0;
    MSG_HEAD_T* msg_head_ptr;
    uint8_t* msg_ptr = buf + 1;
    TOOLS_DIAG_AP_EXIT_CMD_T* msg_exit_prokey;
    TOOLS_DIAG_AP_CMD_T* msg_enter_prokey;

	if((*buf == CALIBERATE_HEAD) && (*(buf + len -1) == CALIBERATE_HEAD)){
	    msg_head_ptr = (MSG_HEAD_T*)(buf + 1);
	    switch(msg_head_ptr->type){
	        case CALIBERATE_COMMOND_T:
				command = msg_head_ptr->subtype;
				command &= 0x3f;
	            freq = *(buf+1);
	            freq = freq<<8;
	            freq += *(buf+2);
	            freq += ((*(buf+3)) << 16); /* bit16~bit23, new fre may > 65535 */
	            command += freq<<8;
	            break;
	        case CALIBERATE_PROKEY_COMMOND_T:
	            if(DIAG_AP_CMD_PROGRAM_KEY == *(msg_ptr + sizeof(MSG_HEAD_T))){
	                msg_enter_prokey =  (TOOLS_DIAG_AP_CMD_T*)(msg_ptr + sizeof(MSG_HEAD_T));
	                command = msg_enter_prokey->cmd;
	            }
	            else if(DIAG_AP_CMD_EXIT_PROGRAM_KEY == *(msg_ptr + sizeof(MSG_HEAD_T))){
	                msg_exit_prokey = (TOOLS_DIAG_AP_EXIT_CMD_T*)(msg_ptr + sizeof(MSG_HEAD_T));
	                command = msg_exit_prokey->para;
	            }
			    break;
	        default:
	            command = 0;
	            break;
		}
	}
	printf("checked command from pc , and return value = %x\n" , command);
	return command;
}

extern int power_button_pressed(void);
static unsigned long count_ms;

int is_timeout(void)
{

    now_time = get_timer_masked();

    if((now_time - start_time)>count_ms)
      	return 1;
    else{
        return 0;
    }
}

void cali_usb_debug(uint8_t *buf)
{
	int i, ret;
 	for(i = 0; i<20; i++)
	buf[i] = i+'a';
 	while(!usb_serial_configed)
 		usb_gadget_handle_interrupts();
	printf("USB SERIAL CONFIGED\n");
    gs_open();
#if WRITE_DEBUG
	while(1){
		ret = gs_write(buf, 20);
		printf("func: %s waitting write done\n", __func__);
		if(usb_trans_status)
			printf("func: %s line %d usb trans with error %d\n", __func__, __LINE__, usb_trans_status);
		usb_wait_trans_done(1);
		printf("func: %s readly send %d\n", __func__, ret);
	}
#else
	while(1){
		int count = 20;
		usb_wait_trans_done(0);
		if(usb_trans_status)
			printf("func: %s line %d usb trans with error %d\n", __func__, __LINE__, usb_trans_status);
		ret = gs_read(buf, &count);
		printf("func: %s readly read %d，return ret %d\n", __func__, count, ret);
		if(usb_trans_status)
			printf("func: %s line %d usb trans with error %d\n", __func__, __LINE__, usb_trans_status);
		for(i = 0; i<count; i++)
			printf("%c ", buf[i]);
		printf("\n");
	}

#endif
}
int cali_usb_prepare(void)
{
	if(usb_driver_init(USB_SPEED_FULL) < 0)
	{
		printf("%s\n", "usb_driver_init error");
		return 0;
	}
	if(usb_serial_init() < 0)
	{
		printf("%s\n", "usb_serial_init error");
		return 0;
	}
	return 1;
}
int cali_usb_enum(void)
{
	int ret = 0;
	count_ms = get_cal_enum_ms();
	start_time = get_timer_masked();
	while(!usb_is_configured()){
		ret = is_timeout();
		if(ret == 0)
			continue;
		else{
			printf("usb calibrate configuration timeout,%lu,%lu,%lu\n",now_time,start_time,count_ms);
			return 0;
			}
		}
	printf("USB SERIAL CONFIGED\n");

	start_time = get_timer_masked();
	count_ms = get_cal_io_ms();
	while(!usb_is_port_open()){
		ret = is_timeout();
		if(ret == 0)
			continue;
		else{
			printf("usb calibrate port open timeout%lu,%lu,%lu\n",now_time,start_time,count_ms);
			return 0;
			}
		}
	gs_open();
	printf("USB SERIAL PORT OPENED\n");
	return 1;
}

int escape_char(uint8_t *buf,int got)
{
	int size = 2 * got;
	int i = 0;
	int t = 0;
	uint8_t* temp = (uint8_t*) malloc(size);
	if(!temp){
		printf("escape malloc failed\n");
		return 0;
	}

	memset(temp, 0, size);

	for(; i < got; i++, t++){
		if (buf[i] == 0x7d){
			i++;
			temp[t] = buf[i] ^ 0x20;
		} else {
			temp[t] = buf[i];
		}
	}

	memcpy(buf, temp, size);

	free(temp);
	return 1;
}

int cali_get_cmd(uint8_t *pctool_cmd_buf, int receive_len)
{
	int got = 0;
	int count = CMD_BUF_NUMBER;
	int ret = 0;
	int i;
	int max_len = CMD_BUF_NUMBER;
	if(max_len < receive_len){
		printf("cmd_buf out of bounds\n");
		return 0;
	}

	start_time = get_timer_masked();

	while(got < max_len){
		if(usb_is_trans_done(0))
		{
			if(usb_trans_status)
				printf("func: %s line %d usb trans with error %d\n", __func__, __LINE__, usb_trans_status);
			gs_read(pctool_cmd_buf + got, &count);
			if(usb_trans_status)
				printf("func: %s line %d usb trans with error %d\n", __func__, __LINE__, usb_trans_status);
			got+=count;
			if(got >= receive_len && pctool_cmd_buf[got-1] == 0x7e)
				break;
		}
		if(got < max_len){
			ret = is_timeout();
			if(ret == 0){
				count=max_len - got;
				continue;
				}
			else{
				printf("usb read timeout\n");
				return 0;
				}
		}else{
			break;
		}
	}
 	printf("caliberate:what got from host total %d is \n", got);
 	for(i=0; i<got;i++)
 		printf("0x%x ", pctool_cmd_buf[i]);
 	printf("\n");
	return got;
}

int reply_to_pctool(uint8_t* buf, int len)
{
	gs_write(buf, len);
	dprintf("%s waitting %d write done\n", __func__, len);
	if(usb_trans_status)
		printf("%s line %d usb trans with error %d\n", __func__, __LINE__, usb_trans_status);
	usb_wait_trans_done(1);

	return 1;
}

int translate_packet(char *dest,char *src,int size)
{
    int i;
    int translated_size = 0;

    dest[translated_size++] = 0x7E;

    for(i=0;i<size;i++){
        if(src[i] == 0x7E){
            dest[translated_size++] = 0x7D;
            dest[translated_size++] = 0x5E;
        } else if(src[i] == 0x7D) {
            dest[translated_size++] = 0x7D;
            dest[translated_size++] = 0x5D;
        } else
            dest[translated_size++] = src[i];
    }
    dest[translated_size++] = 0x7E;
    return translated_size;
}

int prepare_reply_buf(uint8_t* buf, int status)
{
    char *rsp_ptr;
    MSG_HEAD_T* msg_head_ptr;
    TOOLS_DIAG_AP_CNF_T* aprsp;
	int total_len,rsplen;
	printf("preparing reply buf");
    if(NULL == buf){
	    printf("in function prepare_reply_buf, buf = NULL\n");
        return 0;
    }

    msg_head_ptr = (MSG_HEAD_T*)(buf + 1);
    rsplen = sizeof(TOOLS_DIAG_AP_CNF_T) + sizeof(MSG_HEAD_T);
    rsp_ptr = (char*)malloc(rsplen);
    if(NULL == rsp_ptr){
	    printf("in function prepare_reply_buf: Buffer malloc failed\n");
	    return 0;
    }
    aprsp = (TOOLS_DIAG_AP_CNF_T*)(rsp_ptr + sizeof(MSG_HEAD_T));
	msg_head_ptr->len = rsplen;
    memcpy(rsp_ptr,msg_head_ptr,sizeof(MSG_HEAD_T));

    aprsp->status = status;
    aprsp->length = CALIBERATE_CNF_LEN;

    total_len = translate_packet((char*)pctool_cnf_buf,rsp_ptr,((MSG_HEAD_T*)rsp_ptr)->len);
    free(rsp_ptr);
    return total_len;
}

int pctool_mode_detect(void)
{

	int ret , command , bat_info;
	int recive_char = 0;
	uint8_t pctool_cmd_backup_buf[CMD_BUF_NUMBER] = {0};

	debugf(" uart cooperating with pc tool\n");
    //if(get_mode_from_gpio() && (get_poweron_src() == POWERON_JIG))
	if(get_mode_from_gpio())
		return pctool_mode_detect_uart();

	debugf("%s\n", "usb cooperating with pc tool");

	if (charger_connected()) {
		bat_info = sprdchg_charger_is_adapter();
		if (bat_info == ADP_TYPE_DCP)
			return -1;
	}else{
		return -1;
	}

	ret = cali_usb_prepare();
	if (!ret)
		return -1;

#if IO_DEBUG
	cali_usb_debug(pctool_cmd_buf);
#endif
	ret = cali_usb_enum();
	if (!ret)
		return -1;

	recive_char = cali_get_cmd(pctool_cmd_buf, CALIBERATE_STRING_LEN );
	if (!recive_char)
		return -1;

	memcpy(pctool_cmd_backup_buf, pctool_cmd_buf, recive_char);

	ret = escape_char(pctool_cmd_buf, recive_char);
	if (!ret)
		return -1;

	command = check_pctool_cmd(pctool_cmd_buf, CALIBERATE_STRING_LEN);
	printf("%s caliberate_mode: %x \n",__func__, command&0xff);
	if (!command) {
		printf("func: %s line: %d caliberate failed\n", __func__, __LINE__);
		return -1;
	}

	ret = reply_to_pctool(pctool_cmd_backup_buf, recive_char);
	if (!ret)
		return -1;

	if (CALIBERATE_COMMAND_PROGRAMKEY == command)
	{
		ret = cali_get_cmd(pctool_cmd_buf, CALIBERATE_STRING_LEN_14);
		if(!ret)
			return -1;
		command = check_pctool_cmd(pctool_cmd_buf, CALIBERATE_STRING_LEN_14);
		if(!command)
			return -1;
		else if(DIAG_AP_CMD_PROGRAM_KEY == command)
		{
#if defined(CONFIG_SECURE_BOOT)||defined (CONFIG_SECBOOT)
			ret = secure_efuse_program();
			if(!ret)
				ret = prepare_reply_buf(pctool_cmd_buf ,CALIBERATE_CNF_SCS);
			else{
				printf("write efuse failed and error code = %d \n" , ret);
				ret = prepare_reply_buf(pctool_cmd_buf , CALIBERATE_CNF_FAIL);
			}
			if(ret)
				ret = reply_to_pctool(pctool_cnf_buf, ret);
			if(!ret)
				return -1;
#endif
		}
		ret = cali_get_cmd(pctool_cmd_buf,CALIBERATE_STRING_LEN_16);
		if(!ret)
			return -1;
		command = check_pctool_cmd(pctool_cmd_buf , CALIBERATE_STRING_LEN_16);
		if(!command)
			return -1;
		switch(command){
			case 0xffff:
				ret = prepare_reply_buf(pctool_cmd_buf ,CALIBERATE_CNF_SCS);
				reply_to_pctool(pctool_cnf_buf, ret);
				return CMD_POWER_DOWN_DEVICE;
				break;
			case 0xfffe:
				ret = prepare_reply_buf(pctool_cmd_buf ,CALIBERATE_CNF_SCS);
				reply_to_pctool(pctool_cnf_buf, ret);
				return CMD_CHARGE_MODE;
				break;
			default:
				ret = prepare_reply_buf(pctool_cmd_buf ,CALIBERATE_CNF_SCS);
				reply_to_pctool(pctool_cnf_buf, ret);
				break;
		}
	}

	memset(calibration_cmd_buf, 0, MAX_CALIBRATION_LEN);
	s_is_calibration_mode=1;

	switch (command & 0xff){
		case CALIBERATE_COMMAND_AUTOTEST:
			snprintf(calibration_cmd_buf, MAX_CALIBRATION_LEN, "autotest=1 ");
			ret = CMD_AUTOTEST_MODE;
			usb_driver_exit();
			break;
		default:
			snprintf(calibration_cmd_buf, MAX_CALIBRATION_LEN, "calibration=%d,%d,146 ", command&0xff, (command&(~0xff))>>8);
			ret = CMD_CALIBRATION_MODE;
			usb_driver_exit();
			break;
	}
	return ret;
}


int poweron_by_calibration(void)
{
	return s_is_calibration_mode;
}

int cali_file_check(void)
{

#define CALI_MAGIC      (0x49424143) //CALI
#define CALI_COMP       (0x504D4F43) //COMP

	if(do_fs_file_read("prodnv", "/adc.bin", (char *)nv_buffer,sizeof(nv_buffer)))
		return 1;

	if((nv_buffer[0] != CALI_MAGIC)||(nv_buffer[1]!=CALI_COMP))
		return 1;
	else
		return 0;
}

#define VLX_ADC_ID   2
#define VLX_RAND_TO_U32( _addr )	if( (_addr) & 0x3 ){_addr += 0x4 -((_addr) & 0x3); }

u32 Vlx_GetFixedNvitemAddr(u16 identifier, u32 search_start, u32 search_end)
{
	u32 start_addr, end_addr;
	u16 id, len;
	volatile u16 *flash_ptr;

	start_addr = search_start;
	end_addr   = search_end;
	start_addr += sizeof(u32); //skip update flag

	while(start_addr < end_addr)
	{
		flash_ptr = (volatile u16 *)(start_addr);
		id  = *flash_ptr++;
		len = *flash_ptr;
		if(0xFFFF == id)
		{
			return 0xFFFFFFFF;
		}
		if(identifier == id)
		{
			return (start_addr + 4);
		}
		else
		{
			start_addr += 4 + len +(len & 0x1);
			VLX_RAND_TO_U32( start_addr )
		}
	}
	return 0xFFFFFFFF;
}

int read_adc_calibration_data(char *buffer,int size)
{
	chipram_env_t* cr_env = get_chipram_env();
	boot_mode_t boot_role = cr_env->mode;
	if (boot_role == BOOTLOADER_MODE_DOWNLOAD)
		return 0;

	unsigned int adc_magic_flag = 0;
	int adc_magic_len = sizeof(unsigned int);
	int tmp_size = adc_magic_len + sizeof(nv_buffer);
	char *tmp = malloc(tmp_size);

	debugf("start read miscdata adc data...\n");
	if(common_raw_read("miscdata", (uint64_t)tmp_size, ADC_DATA_START, tmp)) {
		errorf("read miscdata adc data error.\n");
		free(tmp);
		return 0;
	}
	adc_magic_flag = *((unsigned int *)tmp);
	if(adc_magic_flag == ADC_MAGIC) {
		debugf("ADC MAGIC is true!\n");
		memcpy(nv_buffer, tmp + adc_magic_len, sizeof(nv_buffer));

	} else {
		debugf("ADC MAGIC is false!\nstart read prodnv /adc.bin...\n");
		if(do_fs_file_read("prodnv", "/adc.bin", (char *)nv_buffer,sizeof(nv_buffer))) {
			printf("%s: cannot read prodnv /adb.bin.\n", __func__);
			free(tmp);
			return 0;
		}

	}

	if(size>48)
		size=48;
	memcpy(buffer,&nv_buffer[2],size);
	free(tmp);

	return size;
}

void download_after_enter_cali_mode(u8 cail_mode)
{
	memset(calibration_cmd_buf, 0, MAX_CALIBRATION_LEN);
	s_is_calibration_mode = 1;
	snprintf(calibration_cmd_buf, MAX_CALIBRATION_LEN, "calibration=%d,%d,146 ", cail_mode, 0);
}

void download_after_enter_autotest_mode(u8 cali_mode)
{
	memset(calibration_cmd_buf, 0, MAX_CALIBRATION_LEN);
	s_is_calibration_mode = 1;
	snprintf(calibration_cmd_buf, MAX_CALIBRATION_LEN, "autotest=1 ");
}


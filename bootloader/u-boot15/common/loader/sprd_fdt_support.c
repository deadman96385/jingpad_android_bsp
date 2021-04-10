#include <common.h>
#include <stdio_dev.h>
#include <linux/ctype.h>
#include <linux/types.h>
#include <asm/global_data.h>
#include <libfdt.h>
#include <fdt_support.h>
#include <exports.h>
#include "loader_common.h"
#include "sprd_cpcmdline.h"
#include "sysdump.h"
#include <sprd_common_rw.h>
#include <adi_hal_internal.h>
#include <asm/arch/sprd_reg.h>
#include <uboot_sec_drv.h>
#include <fdtdec.h>
#include <chipram_env.h>
#ifdef CONFIG_VBOOT_V2
#include <avb/uboot_avb_ops.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

extern uint32_t get_first_mode;
extern uint32_t first_cali_mode;
extern void *lcd_get_base_addr(void *lcd_base);
extern uint32_t lcd_get_pixel_clock(void);
extern uint32_t load_lcd_id_to_kernel();
extern uint32_t load_lcd_width_to_kernel();
extern uint32_t load_lcd_hight_to_kernel();
extern int get_dram_cs_number(void);
extern int get_dram_cs0_size(void);
extern char *get_product_sn(void);
extern void tee_call_request(unsigned int **mem_ptr);
extern int fdtdec_decode_region_private(const void *blob, int node, const char *prop_name,
			 fdt_addr_t *basep, fdt_size_t *sizep);
extern int poweron_by_calibration(void);
extern int get_img_partition_id(char *part_name, unsigned int *id);

/*for verified boot*/
enVerifiedState g_verifiedbootstate = v_state_green;
extern unsigned int g_DeviceStatus;
int fdt_chosen_bootargs_append(void *fdt, char *append_args, int force);
#define MAX_BOOTARG_LEN  (0x1000)  /*4kb*/

#ifdef CONFIG_SECURE_BOOT
#define CMDLINE_BUF_SIZE	(1024)
unsigned spl_data_buf[0x2000] __attribute__ ((align(4))) = {
0};

unsigned harsh_data_buf[8] __attribute__ ((align(4))) = {
0};

void *spl_data = spl_data_buf;
void *harsh_data = harsh_data_buf;
#endif

typedef enum {
#ifdef CONFIG_SOC_IWHALE2
	DDR_HOLLOW0 = 0,
	DDR_HOLLOW1,
	TOS_MEMORY,
#else
	TOS_MEMORY = 0,
#endif
	MULTIMEDIA,
	AUDIO_MEMORY,
	SIPC_MEMORY,
	CP_MODEM,
	FRAMEBUFFER,
	OVERLAYBUFFER
} mem_type;

typedef struct {
	mem_type type;
	uint32_t start_high;
	uint32_t start_low;
	uint32_t size;
} mem_info;

#ifdef CONFIG_VBOOT_V2
#include "libavb.h"
extern AvbSlotVerifyData* avb_slot_data[2];
#endif

#define LOGLEVEL_DATA_OFFSET	(9 * 1024)
#define LOGLEVEL_DATA_LEN		32

int fdt_fixup_verified_boot(void *fdt)
{
	int ret = 0;
	char buf[64];
	int str_len;
	memset(buf, 0, 64);

	switch(g_verifiedbootstate)
	{
		case v_state_green:
			sprintf(buf,"androidboot.verifiedbootstate=green");
			break;
		case v_state_yellow:
			sprintf(buf,"androidboot.verifiedbootstate=yellow");
			break;
		case v_state_orange:
			sprintf(buf,"androidboot.verifiedbootstate=orange");
			break;
		case v_state_red:
			sprintf(buf,"androidboot.verifiedbootstate=red");
			break;
		default:
			sprintf(buf,"androidboot.verifiedbootstate=green");
			break;
	}

	str_len = strlen(buf);
	buf[str_len] = '\0';
	ret = fdt_chosen_bootargs_append(fdt, buf, 1);

	return ret;
}

int fdt_fixup_flash_lock_state(void *fdt)
{
	int ret = 0;
	char buf[64];
	int str_len;
	memset(buf, 0, 64);

	switch(g_DeviceStatus)
	{
		case 1:
			sprintf(buf,"androidboot.flash.locked=0");
			break;
		case 0:
			sprintf(buf,"androidboot.flash.locked=1");
			break;
		default:
			sprintf(buf,"androidboot.flash.locked=1");
			break;
	}

	str_len = strlen(buf);
	buf[str_len] = '\0';
	ret = fdt_chosen_bootargs_append(fdt, buf, 1);

	return ret;
}


#ifdef CONFIG_VBOOT_V2
int fdt_fixup_vboot(void *fdt)
{
#ifdef CONFIG_VBOOT_SYSTEMASROOT
    fdt_fixup_vboot_system(fdt);
#else
    fdt_fixup_ando_vboot(fdt);
#endif
    return 0;
}

int fdt_fixup_ando_vboot(void *fdt)
{
	int ret = 0;
	int str_len = 0;

	str_len = strlen((char *)g_sprd_vboot_cmdline);
	if(str_len == 0) {
		debug("g_sprd_vboot_cmdline is null. \n");
		return ret;
	}
	g_sprd_vboot_cmdline[str_len] = '\0';
	ret = fdt_chosen_bootargs_append(fdt, (char *)g_sprd_vboot_cmdline, 1);
	debug("fdt vboot str_len is %d, ret is %d\n", str_len, ret);

	return ret;
}
#ifdef CONFIG_VBOOT_SYSTEMASROOT
int fdt_fixup_vboot_system(void *fdt)
{
    int ret = 0;
    int str_len = 0;

    debug("fdt_fixup_vboot_system enter \n");
    str_len = strlen((char *)g_vboot_sys_cmdline);
    if(str_len == 0) {
        debug("g_vboot_sys_cmdline is null. \n");
        return ret;
    }
    g_vboot_sys_cmdline[str_len] = '\0';
    ret = fdt_chosen_bootargs_append(fdt, (char *)g_vboot_sys_cmdline, 1);
    debug("fdt vboot system str_len is %d, ret is %d\n", str_len, ret);
    return ret;
}
#endif
#endif

int fdt_initrd_norsvmem(void *fdt, ulong initrd_start, ulong initrd_end, int force)
{
	int nodeoffset;
	int err;
	unsigned long tmp=0;
	const char *path;
	uint64_t addr, size;

	/* Find the "chosen" node.  */
	nodeoffset = fdt_path_offset(fdt, "/chosen");

	/* If there is no "chosen" node in the blob return */
	if (nodeoffset < 0) {
		errorf("fdt_initrd: %s\n", fdt_strerror(nodeoffset));
		return nodeoffset;
	}

	/* just return if initrd_start/end aren't valid */
	if ((initrd_start == 0) || (initrd_end == 0))
		return 0;

	path = fdt_getprop(fdt, nodeoffset, "linux,initrd-start", NULL);
	if ((path == NULL) || force) {
#ifdef CONFIG_ARM64
		tmp = __cpu_to_be64(initrd_start);
#else
		tmp = __cpu_to_be32(initrd_start);
#endif
		err = fdt_setprop(fdt, nodeoffset, "linux,initrd-start", &tmp, sizeof(tmp));
		if (err < 0) {
			errorf("could not set linux,initrd-start %s.\n", fdt_strerror(err));
			return err;
		}
#ifdef CONFIG_ARM64
		tmp = __cpu_to_be64(initrd_end);
#else
		tmp = __cpu_to_be32(initrd_end);
#endif
		err = fdt_setprop(fdt, nodeoffset, "linux,initrd-end", &tmp, sizeof(tmp));
		if (err < 0) {
			errorf("could not set linux,initrd-end %s.\n", fdt_strerror(err));

			return err;
		}
	}

	return 0;
}

int fdt_chosen_bootargs_append(void *fdt, char *append_args, int force)
{
	int nodeoffset;
	int err;
	const char *path;
	char *strargs;
	int size;

	if (!append_args)
		return -1;

	err = fdt_check_header(fdt);
	if (err < 0) {
		errorf("fdt_chosen_bootargs_append: %s\n", fdt_strerror(err));
		return err;
	}

	/*
	 * Find the "chosen" node.
	 */
	nodeoffset = fdt_path_offset(fdt, "/chosen");

	/*
	 * If there is no "chosen" node in the blob, leave.
	 */
	if (nodeoffset < 0) {
		errorf("fdt_chosen_bootargs_append: cann't find chosen");
		return -1;
	}

	/*
	 * If the property exists, update it only if the "force" parameter
	 * is true.
	 */
	path = fdt_getprop(fdt, nodeoffset, "bootargs", NULL);
	if ((path == NULL) || force) {
		strargs = malloc(MAX_BOOTARG_LEN+1);
		if (!strargs)
			return -1;
		memset(strargs, 0, MAX_BOOTARG_LEN+1);
		if(path != NULL)
		{
			size = strlen(path) + strlen(append_args);
			if (size > (MAX_BOOTARG_LEN - 1)) {
				errorf("bootargs len:%d overflow (MAX_BOOTARG_LEN-1)\n", size);
				free(strargs);
				return -1;
			}
			sprintf(strargs, "%s %s", path, append_args);
		}
		else
		{
			size = strlen(append_args);
			if (size > MAX_BOOTARG_LEN) {
				errorf("bootargs len:%d overflow MAX_BOOTARG_LEN\n", size);
				free(strargs);
				return -1;
			}
			sprintf(strargs, "%s", append_args);
		}
		err = fdt_setprop(fdt, nodeoffset, "bootargs", strargs, strlen(strargs) + 1);
		if (err < 0)
			errorf("could not set bootargs %s.\n", fdt_strerror(err));
		free(strargs);
	}

	return err;
}

#ifdef CONFIG_X86
int uboot_set_secure_range_paraneters(mem_type type,fdt_addr_t start,fdt_addr_t size){
	mem_info mi;
	unsigned int result = 0;
	unsigned int *share_data;

	printf("type1=%d, start1= 0x%x size1=0x%x\n",type,start,size);

	mi.type = type;
	mi.start_high = (start >> 32);
	mi.start_low = (start & 0xffffffff);
	mi.size = size;

	printf("##%s:%d---mi->type=0x%x\n", __func__, __LINE__,
	       mi.type);

	printf("##%s:%d---mi->start_high=0x%x mi->start_low=0x%x mi->size=0x%x \n", __func__, __LINE__,
	       mi.start_high,mi.start_low,mi.size);

	printf("##%s:%d---&mi=0x%x \n", __func__, __LINE__,
	       &mi);

	tee_call_request(&share_data);/*check tos status and send cmd to tos, tos return share memory point*/


	printf("##%s:%d---vm=%d,cpu=%d,result: %d\n", __func__, __LINE__,
	       share_data[0], share_data[1], share_data[2]);

	puts("## Start firewall config ...\n");
	share_data[2] = result;
	share_data[3] = SEC_FIREWALL_CMD; /*cmd, other feature add own cmd*/
	share_data[4] = ((unsigned int)&mi)&0xFFFFFFFF;
	share_data[5] = sizeof(mem_info);

	printf("##cmd:0x%x,mem_info_addr:0x%x,mem_info_len:0x%x",share_data[3],share_data[4],share_data[5]);
    /* secvm id: 3 */
	if (mv_svc_ivmc_request(3) != 0) {
		printf("## Waiting for response ...\n");
		while (1) {
			/* check the return value of ptr[2] */
			if (share_data[2] != result) {
				printf("%s:%d---vm=%u,cpu=%u,result: %u\n",__func__, __LINE__,
				       share_data[0], share_data[1], share_data[2]);
				break;
			}

			mdelay(200);
		}
	} else {
		printf("## Verify request failed");
	}
	return share_data[2];
}
#else
int uboot_set_secure_range_paraneters(mem_type type,fdt_addr_t start,fdt_addr_t size){
	mem_info mi __attribute__((aligned(4096)));
	smc_param *param;
	mi.type = type;
	mi.start_high = (start >> 32);
	mi.start_low = (start & 0xffffffff);
	mi.size = size;
	param = tee_common_call(FUNCTYPE_SET_SECURE_RANGE_PARAM, (uint32_t)(&mi), (uint32_t)(sizeof(mem_info)));

	return param->a0;
}
#endif

int fdt_reserved_mem_multimedia_parse(void*fdt)
{
	int parentoffset,nodeoffset;
	int offset;
	uchar * dt_addr;
	const fdt32_t *reg;
	int str_len;
	char nodename[256];
	fdt_addr_t  s_addr;
	fdt_addr_t  s_size ;
	char *pStr=NULL;
	mem_info mi;
	char name[64];
	char value[64];

	strncpy(name, "sprd,decoup", sizeof(name));
	/*check cproc-use-decoup*/
	strncpy(value, "cproc-use-decoup", sizeof(value));
	offset = fdt_node_offset_by_prop_value(fdt, 0, name, value, strlen(value) + 1);
	if(offset < 0) {
		/*check cproc-use-decoup-v1*/
		strncpy(value, "cproc-use-decoup-v1", sizeof(value));
		offset = fdt_node_offset_by_prop_value(fdt, 0, name, value, strlen(value) + 1);
		if(offset < 0)
		{
			debugf("the sipc info already exist, don't need to parse\n");
			return -1;
		}
	}
	if(0 == (fdtdec_decode_region_private(fdt, offset, "reg", &s_addr, &s_size)))
	{
		/*find reg prop ok*/
		uboot_set_secure_range_paraneters(CP_MODEM,s_addr,s_size);
	}
	parentoffset = fdt_path_offset(fdt, "/reserved-memory");
	if (parentoffset < 0) {
		errorf("fdt_reserved_mem_multimedia_parse: cann't find mm_reserved \n");
		return -1;
	}
	for (offset = fdt_first_subnode(fdt, parentoffset);
	      offset >= 0; offset = fdt_next_subnode(fdt, offset)) {
		sprintf(nodename, "%s", fdt_get_name(fdt, offset, NULL));
		str_len = strlen(nodename);
		nodename[str_len] = '\0';
		pStr = strstr(nodename,"multimediabuffer");
		if(pStr){
			if(fdtdec_decode_region(fdt, offset, "reg", &s_addr, &s_size) < 0)
			{
				debugf("cannot find reg prop, go to next node.\n" );
				goto next;
			}
			uboot_set_secure_range_paraneters(MULTIMEDIA,s_addr,s_size);
		}
		pStr = strstr(nodename,"tos-mem");
		if(pStr){
			if(fdtdec_decode_region(fdt, offset, "reg", &s_addr, &s_size) < 0)
			{
				debugf("cannot find reg prop, go to next node.\n" );
				goto next;
			}
			uboot_set_secure_range_paraneters(TOS_MEMORY,s_addr,s_size);
		}
		pStr = strstr(nodename,"audio-mem");
		if(pStr){
			if(fdtdec_decode_region(fdt, offset, "reg", &s_addr, &s_size) < 0)
			{
				debugf("cannot find reg prop, go to next node.\n" );
				goto next;
			}
			uboot_set_secure_range_paraneters(AUDIO_MEMORY,s_addr,s_size);
		}
		pStr = strstr(nodename,"framebuffer");
		if(pStr){
			if(fdtdec_decode_region(fdt, offset, "reg", &s_addr, &s_size) < 0)
			{
				debugf("cannot find reg prop, go to next node.\n" );
				goto next;
			}
			uboot_set_secure_range_paraneters(FRAMEBUFFER,s_addr,s_size);
		}
		pStr = strstr(nodename,"overlaybuffer");
		if(pStr){
			if(fdtdec_decode_region(fdt, offset, "reg", &s_addr, &s_size) < 0)
			{
				debugf("cannot find reg prop, go to next node.\n" );
				goto next;
			}
			uboot_set_secure_range_paraneters(OVERLAYBUFFER,s_addr,s_size);
		}
next:;
	}
	return 0;
}

int fdt_chosen_bootargs_replace(void *fdt, char *old_args, char *new_args)
{
	int nodeoffset;
	int err, i;
	char *str, *src, *dst;
	const char *path;
	char *strargs;

	if (!old_args || !new_args)
		return -1;
	debugf("fdt_chosen_bootargs_replace start!");

	err = fdt_check_header(fdt);
	if (err < 0) {
		errorf("fdt_chosen_bootargs_replace: %s\n", fdt_strerror(err));
		return err;
	}

	/*
	 * Find the "chosen" node.
	 */
	nodeoffset = fdt_path_offset(fdt, "/chosen");

	/*
	 * If there is no "chosen" node in the blob, leave.
	 */
	if (nodeoffset < 0) {
		errorf("fdt_chosen_bootargs_replace: cann't find chosen");
		return -1;
	}

	/*
	 * If the property exists, update it only if the "force" parameter
	 * is true.
	 */
	path = fdt_getprop(fdt, nodeoffset, "bootargs", NULL);
	if (path != NULL ) {

        debugf("fdt_chosen_bootargs_replace: old bootargs %s!", path);
        str = strstr(path, old_args);
        if(!str) {
            errorf("fdt_chosen_bootargs_replace: cann't find str %s!", old_args);
            return -1;
        }
		strargs = malloc(1024);
		if (!strargs)
			return -1;
        src = path;
        dst = strargs;
        i = 0;
        /* copy the front str */
        while(src != str && i < 1023){
            *dst++ = *src++;
            i++;
        }

        /* copy the new str */
        src = new_args;
        while(*src && i < 1023){
            *dst++ = *src++;
            i++;
        }

        /* copy the back str */
        src = str + strlen(old_args);
        while(*src && i < 1023){
            *dst++ = *src++;
            i++;
        }
        *dst = 0;

        debugf("fdt_chosen_bootargs_replace: new bootargs %s!", strargs);
		err = fdt_setprop(fdt, nodeoffset, "bootargs", strargs, strlen(strargs) + 1);
		if (err < 0)
			errorf("could not set bootargs %s.\n", fdt_strerror(err));
		free(strargs);
	}

	return err;
}

void fdt_fixup_pmic_wa(void *fdt)
{
	int cpunode, vddnode;
	u32 cpureg;
	int vddarm0_node, vddarm1_node;
	u32 vddarm0_phandle, vddarm1_phandle;
	char buf[16];
	int str_len;
	int ret;

	if (ANA_REG_GET(ANA_REG_GLB_CHIP_ID_LOW) >= 0xC003) {
		debugf("2731 later than CE version, skip pmic wa\n");
		return;
	}

	vddarm0_node = fdt_node_offset_by_prop_value(fdt, -1, "regulator-name", "vddarm0", 8);
	if (vddarm0_node == -FDT_ERR_NOTFOUND) {
		errorf("vddarm0 not found\n");
		return;
	} else
		vddarm0_phandle = fdt_get_phandle(fdt, vddarm0_node);

	vddarm1_node = fdt_node_offset_by_prop_value(fdt, -1, "regulator-name", "vddarm1", 8);
	if (vddarm1_node == -FDT_ERR_NOTFOUND)
		return;
	else
		vddarm1_phandle = fdt_get_phandle(fdt, vddarm1_node);

	debugf("vddarm0 phandle 0x%x, vddarm1 phandle 0x%x\n", vddarm0_phandle, vddarm1_phandle);

	cpunode = fdt_node_offset_by_prop_value(fdt, 0, "device_type", "cpu", 4);
	if (cpunode < 0) {
		errorf("cannot find bullhill cpu\n");
		/* Exit if there is no CPU devices but this should never happen */
		return;
	} else {
		while (cpunode != -FDT_ERR_NOTFOUND) {
			u32 *reg = (u32 *)fdt_getprop(fdt, cpunode, "reg", 0);
			if (reg) {
				cpureg = *reg >> 24;
				if (cpureg == 0) {
					debugf("add vddarm0 to cpu0\n");
					vddnode = fdt_appendprop_u32(fdt, cpunode, "cpu0-supply", vddarm0_phandle);
					if (vddnode < 0) {
						char s[64];
						fdt_get_path(fdt, cpunode, s, sizeof(s));
						debugf("could not add vddarm0 node to %s, %s\n", s,
								fdt_strerror(vddnode));
					}
					vddnode = fdt_appendprop(fdt, cpunode, "dual-phase-supply", NULL, 0);
					if (vddnode < 0) {
						char s[64];
						fdt_get_path(fdt, cpunode, s, sizeof(s));
						debugf("could not add dual phase supply node to %s, %s\n", s,
								fdt_strerror(vddnode));
					}
				} else if (cpureg == 4) {
					debugf("add vddarm1 to cpu2\n");
					vddnode = fdt_appendprop_u32(fdt, cpunode, "cpu1-supply", vddarm1_phandle);
					if (vddnode < 0) {
						char s[64];
						fdt_get_path(fdt, cpunode, s, sizeof(s));
						debugf("could not add vddarm1 node to %s, %s\n", s,
								fdt_strerror(vddnode));
					}
					vddnode = fdt_appendprop(fdt, cpunode, "dual-phase-supply", NULL, 0);
					if (vddnode < 0) {
						char s[64];
						fdt_get_path(fdt, cpunode, s, sizeof(s));
						debugf("could not add dual phase supply node to %s, %s\n", s,
								fdt_strerror(vddnode));
					}
				}
			}
			cpunode = fdt_node_offset_by_prop_value(fdt, cpunode, "device_type", "cpu", 4);
		}
	}

	/* append bootargs if all above dts edits sucess */
	memset(buf, 0, 16);
	sprintf(buf, "pmic2731_wa");
	str_len = strlen(buf);
	buf[str_len] = '\0';
	fdt_chosen_bootargs_append(fdt, buf, 1);

	return;
}

int fdt_fixup_iq_reserved_mem(void *fdt)
{
	int offset;
	int ret = 0;
	char *mode;

	mode = getenv("bootmode");
	if (!mode || strcmp("iq", mode)) {
		offset = fdt_node_offset_by_prop_value(fdt, 0, "compatible", "sprd,iq-mem", strlen("sprd,iq-mem") + 1);
		if (offset < 0) {
			return 0;
		}
		ret = fdt_del_node(fdt, offset);
		if (ret < 0)
			errorf("del iq reserved mem failed\n");
	}

	return ret;
}

int fdt_fixup_cp_reserved_mem(void *fdt)
{
	int i;
	int offset, lenp;
	int ret = 0;
	uint32_t value[16];
	char *mode;
	fdt_addr_t  s_addr;
	fdt_addr_t  s_size;
	const fdt_addr_t *cell;

	offset = fdt_path_offset(fdt, "/reserved-memory");
	if (offset < 0) {
		errorf("cann't find reserved-memory node");
		return -1;
	}

	offset = fdt_subnode_offset(fdt, offset, "cp-modem");
	if (offset == -FDT_ERR_NOTFOUND) {
		errorf("cann't find cp-modem@xxxx node\n");
		return -1;
	}

	cell = fdt_getprop(fdt, offset, "sprd,cpdbg-size", &lenp);
	if (!cell) {
		debugf("the cp has no debug area\n");
		return 0;
	}

	memcpy(&value[0], cell, sizeof(value[0]));
	value[0] = __be32_to_cpu(value[0]);
	debugf("cpdbg-size = %x\n", value[0]);

	if(fdtdec_decode_region(fdt, offset, "reg", &s_addr, &s_size) < 0)
	{
		errorf("cannot find reg prop in cp-modem@xxxx node");
		return -1;
	}
	debugf("s_addr = %p, s_size = %p\n", s_addr, s_size);

	s_size -= value[0];
#ifdef CONFIG_PHYS_64BIT
	s_addr = __cpu_to_be64(s_addr);
	s_size = __cpu_to_be64(s_size);
#else
	s_addr = __cpu_to_be32(s_addr);
	s_size = __cpu_to_be32(s_size);
#endif
	memcpy((char *)value, &s_addr, sizeof(fdt_addr_t));
	memcpy((char *)value + sizeof(fdt_addr_t), &s_size, sizeof(fdt_addr_t));

	ret = fdt_setprop(fdt, offset, "reg", value, 2 * sizeof(fdt_addr_t));

	return ret;
}

int fdt_fixup_cp_boot(void *fdt)
{
	int ret = 0;
#if defined( CONFIG_KERNEL_BOOT_CP )
	char buf[64];
	int str_len;
	memset(buf, 0, 64);
	sprintf(buf,"modem=shutdown");
	str_len = strlen(buf);
	buf[str_len] = '\0';
	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
#endif

	ret += fdt_chosen_bootargs_append(fdt, cp_getcmdline(), 1);

	/* if is uart calibraton, remove ttys1 console */
	if(is_calibration_by_uart())
	{
		//__raw_writel(0x285480, CTL_PIN_BASE + REG_PIN_CTRL2);
		//ret = fdt_chosen_bootargs_replace(fdt,"console=ttyS1", "console=ttyS3");
		ret = fdt_chosen_bootargs_replace(fdt,"console=ttyS1", "console=null");
	}

	return 0;
}

#ifdef CONFIG_TEECFG_CUSTOM
int fdt_fixup_tee_reserved_mem(void *fdt)
{
	int i;
	int offset, lenp;
	int ret = 0;
	uint32_t value[16];
	char *mode;
	fdt_addr_t  s_addr;
	fdt_addr_t  s_size;
	const fdt_addr_t *cell;

	offset = fdt_path_offset(fdt, "/reserved-memory");
	if (offset < 0) {
		errorf("cann't find reserved-memory node\n");
		return -1;
	}

	offset = fdt_subnode_offset(fdt, offset, "tos-mem");
	if (offset == -FDT_ERR_NOTFOUND) {
		errorf("cann't find tos-mem@xxxx node\n");
		return -1;
	}

	if(fdtdec_decode_region(fdt, offset, "reg", &s_addr, &s_size) < 0)
	{
		errorf("cannot find reg prop in tos-mem@xxxx node\n");
		return -1;
	}
	debugf("s_addr = %p, s_size = %p\n", s_addr, s_size);

	ret = tee_smc_get_tee_size();
	if(ret < 0)
	{
		errorf("smc get sec size failed! (%d)\n", ret);
		return -1;
	}

	s_size = ret;
#ifdef CONFIG_PHYS_64BIT
	s_addr = __cpu_to_be64(s_addr);
	s_size = __cpu_to_be64(s_size);
#else
	s_addr = __cpu_to_be32(s_addr);
	s_size = __cpu_to_be32(s_size);
#endif
	memcpy((char *)value, &s_addr, sizeof(fdt_addr_t));
	memcpy((char *)value + sizeof(fdt_addr_t), &s_size, sizeof(fdt_addr_t));

	ret = fdt_setprop(fdt, offset, "reg", value, 2 * sizeof(fdt_addr_t));

	return ret;
}
#endif


#ifdef CONFIG_NAND_BOOT
int fdt_fixup_mtd(void *fdt)
{
	char buf[128];
	int str_len;
	int ret;

	memset(buf, 0, 128);

	sprintf(buf, MTDPARTS_DEFAULT);
	str_len = strlen(buf);
	buf[str_len] = '\0';

	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}

#ifdef CONFIG_UBI_ATTACH_MTD
int fdt_fixup_ubi_ai(void *fdt)
{
	char buf[128];
	int str_len;
	int ret;

	memset(buf, 0, 128);

	sprintf(buf, UBI_ATTACH_INFO);
	str_len = strlen(buf);
	buf[str_len] = '\0';

	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}
#endif
#endif

int fdt_fixup_first_mode(void *fdt)
{
	char buf[32] = {0};
	char cali_buf[32] = {0};
	int ret = 0;
	uint32_t first_mode = 0;
	uint32_t cali_mode = 0;

	if ((get_first_mode & 0xFFFFFF00) == SET_FIRST_MODE_MAGIC){
		first_mode = get_first_mode & 0x000000FF;
		cali_mode = first_cali_mode;
		sprintf(buf, "first_mode=%x", first_mode);
		sprintf(cali_buf, "cali_mode=%x", cali_mode);
		debugf("cmdline first_mode=%x,cali_mode=%x\n", first_mode, cali_mode);

		if (fdt_chosen_bootargs_append(fdt, buf, 1))
			return -1;
		if (fdt_chosen_bootargs_append(fdt, cali_buf, 1))
			return -1;
	}

	return ret;
}

int fdt_fixup_lcdid(void *fdt)
{
	char buf[16];

	uint32_t lcd_id = 0;
	int str_len;
	int ret;

	lcd_id = load_lcd_id_to_kernel();
	memset(buf, 0, 16);

	sprintf(buf, "lcd_id=ID");
	str_len = strlen(buf);
	sprintf(&buf[str_len], "%x", lcd_id);
	str_len = strlen(buf);
	buf[str_len] = '\0';

	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}

int fdt_fixup_lcdbase(void *fdt)
{
	char buf[32];
	int str_len;
	int ret;
	void *lcd_base;

	memset(buf, 0, 32);

	//add lcd frame buffer base, length should be lcd w*h*2(RGB565)
	lcd_base = lcd_get_base_addr(NULL);
	debugf("lcd_base=%p\n" ,lcd_base);
	sprintf(buf, "lcd_base=");
	str_len = strlen(buf);
	sprintf(&buf[str_len], "%lx", lcd_base);
	str_len = strlen(buf);
	buf[str_len] = '\0';

	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}

int fdt_fixup_lcdsize(void *fdt)
{
	char buf[32];
	int str_len;
	int ret;

	memset(buf,0,32);
	sprintf(buf, "lcd_size=");
	str_len = strlen(buf);
	sprintf(&buf[str_len], "%dx%d", load_lcd_width_to_kernel(), load_lcd_hight_to_kernel());
	str_len = strlen(buf);

	buf[str_len] = '\0';

	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}

__weak const char *lcd_get_name(void) { return NULL; }

int fdt_fixup_lcdname(void *fdt)
{
	char buf[64];
	const char *lcd_name;

	lcd_name = lcd_get_name();
	if (!lcd_name)
		return 0;

	memset(buf, 0, sizeof(buf));

	sprintf(buf, "lcd_name=%s", lcd_name);

	return fdt_chosen_bootargs_append(fdt, buf, 1);
}

int fdt_fixup_pixelclock(void *fdt)
{
	char buf[32];
	uint32_t pixel_clk;

	memset(buf, 0, 32);

	pixel_clk = lcd_get_pixel_clock();
	sprintf(buf, "pixel_clock=%u", pixel_clk);

	return fdt_chosen_bootargs_append(fdt, buf, 1);
}

int fdt_fixup_lcdbpix(void *fdt)
{
	char buf[16];
	uint32_t bpix = 0;

	memset(buf, 0, 16);

	bpix = lcd_get_bpix();
	sprintf(buf, "logo_bpix=%d", bpix);

	return fdt_chosen_bootargs_append(fdt, buf, 1);
}

int fdt_fixup_serialno(void *fdt)
{
	char buf[255];
	int str_len;
	int ret;
	memset(buf, 0, 255);

	sprintf(buf, " androidboot.serialno=%s", get_product_sn());
	str_len = strlen(buf);
	buf[str_len] = '\0';
	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}

int fdt_fixup_memleakon(void *fdt)
{
	char buf[32];
	int str_len;
	int ret;
	memset(buf, 0, 32);


	sprintf(buf, "kmemleak=on");
	str_len = strlen(buf);
	buf[str_len] = '\0';
	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}

int fdt_fixup_sysdump_magic(void *fdt)
{
	char buf[64];
	int str_len;
	int ret;
	void* magic = (void *)SPRD_SYSDUMP_MAGIC;
	memset(buf, 0, 64);

	sprintf(buf, " sysdump_magic=%lx", magic);
	str_len = strlen(buf);
	buf[str_len] = '\0';
	//debugf("sysdump flag in fdt:%s\n", buf);
	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}

int fdt_fixup_sysdump_uboot(void *fdt)
{
	int err;
	char *pStr=NULL;
	char nodename[256];
	int offset, str_len;
	phys_size_t uboot_size;
	fdt_addr_t s_addr, s_size;
	int parentoffset,nodeoffset;
	phys_addr_t uboot_base = CONFIG_SYS_TEXT_BASE;
	phys_addr_t ddr_base = CONFIG_SYS_SDRAM_BASE;
	phys_size_t ddr_size = get_real_ram_size();

	parentoffset = fdt_path_offset(fdt, "/reserved-memory");
	if (parentoffset < 0) {
		debugf("cannot find reserved-memory node.\n" );
		return -1;
	}

	for (offset = fdt_first_subnode(fdt, parentoffset);
		offset >= 0; offset = fdt_next_subnode(fdt, offset)) {
		sprintf(nodename, "%s", fdt_get_name(fdt, offset, NULL));
		str_len = strlen(nodename);
		nodename[str_len] = '\0';

		pStr = strstr(nodename, "sysdump-uboot");
		if (pStr) {
			debugf("find sysdump-uboot reserved memory\n" );
			uboot_base &= (ddr_base + ddr_size);
			debugf("uboot load address is 0x%x\n", uboot_base);
			uboot_size = (ddr_base + ddr_size) - uboot_base;
			debugf("uboot size is 0x%x\n", uboot_size);

			if (ddr_size >= SZ_512M) {
				debugf("DDR size is more than 512MB\n" );
				uboot_base = CONFIG_SYS_TEXT_BASE;
				uboot_size = CONFIG_SYS_SDRAM_END - uboot_base;
				debugf("uboot_base = 0x%x uboot size is 0x%x\n", uboot_base, uboot_size);
			}

			if (fdtdec_decode_region(fdt, offset, "reg", &s_addr, &s_size) < 0) {
				debugf("cannot find reg prop in sysdump-uboot node.\n" );
				return -1;
			} else {
				debugf("sysdump-uboot: addr is 0x%x, size is 0x%x\n", s_addr, s_size);
				fdt_delprop(fdt, offset, "reg");
#ifdef CONFIG_ARM64
				err = fdt_setprop_u64(fdt, offset, "reg", uboot_base);
				if (err < 0) {
					errorf("ERROR: cannot set sysdump-uboot node's reg property(addr)!\n");
					return -1;
				}

				err = fdt_appendprop_u64(fdt, offset, "reg", uboot_size);
				if (err < 0) {
					errorf("ERROR: cannot set sysdump-uboot node's reg property(size)!\n");
					return -1;
				}
#else
				err = fdt_setprop_u32(fdt, offset, "reg", uboot_base);
				if (err < 0) {
					errorf("ERROR: cannot set sysdump-uboot node's reg property(addr)!\n");
					return -1;
				}

				err = fdt_appendprop_u32(fdt, offset, "reg", uboot_size);
				if (err < 0) {
					errorf("ERROR: cannot set sysdump-uboot node's reg property(size)!\n");
					return -1;
				}
#endif

			if (!fdtdec_decode_region(fdt, offset, "reg", &s_addr, &s_size))
				debugf("sysdump-uboot: addr is 0x%x, size is 0x%x again\n", s_addr, s_size);
			}

			return 0;
		}
	}

	debugf("can not find sysdump-uboot reserved memory\n" );
	return -1;
}

int fdt_fixup_adc_calibration_data(void *fdt)
{
	//extern unsigned int *adc_data_to_transfer;
	unsigned int *adc_data = malloc(64);
	int ret = read_adc_calibration_data(adc_data, 48);

	if (ret) {
		char buf[64];
		int str_len;
		int ret;

		memset(buf, 0, 64);
		if (((adc_data[2] & 0xffff) < 4500) && ((adc_data[2] & 0xffff) > 3000) && ((adc_data[3] & 0xffff) < 4500) && ((adc_data[3] & 0xffff) > 3000)) {
			str_len = strlen(buf);
			sprintf(&buf[str_len], " adc_cal=%d,%d", adc_data[2], adc_data[3]);
		}
		/*just after fgu adc calibration,and no aux adc calibration,need save fgu adc parameters */
		if ((0x00000002 == adc_data[10]) && (0x00000002 & adc_data[11])) {
			str_len = strlen(buf);
			sprintf(&buf[str_len], " fgu_cal=%d,%d,%d", adc_data[4], adc_data[5], adc_data[6]);
		}

		str_len = strlen(buf);
		buf[str_len] = '\0';
		ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	} else {
		debugf("read_adc_calibration_data failed\n");
	}
	free(adc_data);
	return ret;
}

int fdt_fixup_dram_training(void *fdt)
{
	char buf[64];
	int str_len;
	int ret;
	uint64_t addr;
	uint64_t size;
	size = 0x1000;
	memset(buf, 0, 64);

	sprintf(buf, " mem_cs=%d, mem_cs0_sz=%08x", get_dram_cs_number(), get_dram_cs0_size());
	str_len = strlen(buf);
	buf[str_len] = '\0';
	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	debugf(" mem_cs=%d, mem_cs0_sz=%08x", get_dram_cs_number(), get_dram_cs0_size());

	/* gerenally, reserved memory should be configured in dts file. Add fixup here to avoid the wide
	 * range of change for various boards.
	 * reserved for ddr training data used
	 */
	if (ret < 0)
		errorf("failed to append ddr training data args bootargs\n");
	else {
		addr = PHYS_SDRAM_1;
		ret = fdt_add_mem_rsv(fdt, addr, size);
		if(ret < 0) {
			errorf("failed to reserved cs0 ddr training data space\n");
		}
		else {
			if(2 == get_dram_cs_number()) {
				addr = PHYS_SDRAM_1 + get_dram_cs0_size();
				ret = fdt_add_mem_rsv(fdt, addr, size);
				if(ret < 0) {
					errorf("failed to reserved cs1 ddr training data space\n");
				}
			}
		}
	}

	return ret;
}

/**
 * You can re-define function void fdt_fixup_chosen_bootargs_board(char *buf, const char *boot_mode, int calibration_mode)
 * in your u-boot/board/spreadtrum/xxx/xxx.c to override this default function
 */
void __attribute__ ((weak)) fdt_fixup_chosen_bootargs_board(char *buf, int calibration_mode)
{
}

int fdt_fixup_chosen_bootargs_board_private(void *fdt)
{
	int ret = 0;
	char buf[512];
	memset(buf, 0, sizeof buf);
	fdt_fixup_chosen_bootargs_board(buf, poweron_by_calibration());
	if (buf[0])
		ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}

#ifdef CONFIG_SECURE_BOOT
static void convertBinToHex(char *bin_ptr, int length, char *hex_ptr)
{
    int i;
    unsigned char tmp;

    if (bin_ptr == NULL || hex_ptr == NULL) {
        return;
    }
    for (i=0; i<length; i++) {
        tmp = (unsigned char)((bin_ptr[i] & 0xf0)>>4);
        if (tmp <= 9) {
            *hex_ptr = (unsigned char)(tmp + '0');
        } else {
            *hex_ptr = (unsigned char)(tmp + 'A' - 10);
        }
        hex_ptr++;
        tmp = (unsigned char)(bin_ptr[i] & 0x0f);
        if (tmp <= 9) {
            *hex_ptr = (unsigned char)(tmp + '0');
        } else {
            *hex_ptr = (unsigned char)(tmp + 'A' - 10);
        }
        hex_ptr++;
    }
}

void fdt_fixup_secureboot_param(void *fdt_blob)
{

	uint8_t *buf = NULL;
	unsigned int str_len = 0;
	buf = malloc(CMDLINE_BUF_SIZE);
	memset(buf, 0, CMDLINE_BUF_SIZE);
	uint8_t *pubk = NULL;
	pubk = malloc(512);
	int i = 0;
#ifdef PRIMPUKPATH
	str_len = strlen(buf);
	sprintf(&buf[str_len], " primpukpath=%s", PRIMPUKPATH);	//"/dev/block/mmcblk0boot0");
	str_len = strlen(buf);
	buf[str_len] = '\0';
#endif
#ifdef PRIMPUKSTART
	str_len = strlen(buf);
	sprintf(&buf[str_len], " primpukstart=%d", PRIMPUKSTART);	//512);
	str_len = strlen(buf);
	buf[str_len] = '\0';
#endif
#ifdef PRIMPUKLEN
	str_len = strlen(buf);
	sprintf(&buf[str_len], " primpuklen=%d", PRIMPUKLEN);	//260);
	str_len = strlen(buf);
	buf[str_len] = '\0';
#endif
	/*hash write by pc tool,but the hash value calculated by u-boot */
	/*if rom secure enable,do not need cal spl hash and pass to kernel */
	if (!secureboot_enabled()) {
		int ret = get_spl_hash(harsh_data);
		if (ret) {
			str_len = strlen(buf);
			sprintf(&buf[str_len], " securesha1=%08x%08x%08x%08x%08x", *(uint32_t *) harsh_data, *(uint32_t *) (harsh_data + 4),
				*(uint32_t *) (harsh_data + 8), *(uint32_t *) (harsh_data + 12), *(uint32_t *) (harsh_data + 16));
			str_len = strlen(buf);
			buf[str_len] = '\0';
		}
	}
/*TODO*/
	if(gd->boot_device == BOOT_DEVICE_EMMC) {
		if (0 != common_raw_read("uboot" , SEC_HEADER_MAX_SIZE,
				PUBKEY_VLR_BLOCK_INDEX*EMMC_SECTOR_SIZE, (uint8_t *) pubk)) {
					errorf("PARTITION_BOOT2 read error \n");
					return 0;
		}
	}

	str_len = strlen(buf);
	sprintf(&buf[str_len]," pubk=");
	str_len = strlen(buf);
	buf[str_len] = '\0';

	str_len = strlen(buf);

	convertBinToHex(pubk, 260, &buf[str_len]);

	fdt_chosen_bootargs_append(fdt_blob, buf, 1);
}

#endif

/**
 * Fix me:
 * fix_memory_size() interface which can be fixup memory size, but because of our
 * device tree is not suitable for the context, for simple, we add a new function. In arm64,
 * we should discard it. It should be ok now.
 */
int fdt_fixup_ddr_size(void *fdt)
{
#ifdef CONFIG_DDR_AUTO_DETECT
	int nodeoffset;
	int err;
	const char *path;
	phys_addr_t ddr_base = CONFIG_SYS_SDRAM_BASE;
	phys_size_t ddr_size = get_real_ram_size();

	nodeoffset = fdt_path_offset(fdt, "/memory");
	debugf("/memory nodeoffset = %d, ddr_base: 0x%x, ddr_size: 0x%x\n",
		nodeoffset, ddr_base, ddr_size);
	if (nodeoffset < 0) {
	    errorf("ERROR: device tree must have /memory node %s.\n", fdt_strerror(nodeoffset));
	    return nodeoffset;
	}

	fdt_delprop(fdt, nodeoffset, "reg");

#ifdef CONFIG_ARM64
	err = fdt_setprop_u64(fdt, nodeoffset, "reg", ddr_base);
	if (err < 0) {
	    errorf("ERROR: cannot set /memory node's reg property(addr)!\n");
	    return err;
	}

	err = fdt_appendprop_u64(fdt, nodeoffset, "reg", ddr_size);
	if (err < 0) {
	    errorf("ERROR: cannot set /memory node's reg property(size)!\n");
	}
#else
	err = fdt_setprop_u32(fdt, nodeoffset, "reg", ddr_base);
	if (err < 0) {
	    errorf("ERROR: cannot set /memory node's reg property(addr)!\n");
	    return err;
	}

	err = fdt_appendprop_u32(fdt, nodeoffset, "reg", ddr_size);
	if (err < 0) {
	    errorf("ERROR: cannot set /memory node's reg property(size)!\n");
	}
#endif

	return err;
#else
	return 0;
#endif
}

int fdt_fixup_ro_boot_ramsize(void *fdt)
{
#ifdef CONFIG_DDR_AUTO_DETECT
	char buf[32];

	phys_size_t ddr_size;
	uint64_t ro_boot_ddrsize = 0;
	int str_len;
	int ret;

	ddr_size = get_real_ram_size();
	ddr_size = ALIGN(ddr_size, 0x100000);
	ro_boot_ddrsize = ddr_size >> 20;

	memset(buf, 0, 32);

	sprintf(buf, "androidboot.ddrsize=%ldM", ro_boot_ddrsize);
	str_len = strlen(buf);
	buf[str_len] = '\0';

	ret = fdt_chosen_bootargs_append(fdt, buf, 1);

	return ret;
#else
	return 0;
#endif
}

int fdt_fixup_ddrsize_range(void *fdt) {
    char buf[64], *range = NULL;
    int ret, str_len;
    memset(buf, 0, sizeof(buf));
#ifdef CONFIG_DDR_AUTO_DETECT
    uint64_t ro_boot_ddrsize = 0;
    phys_size_t ddr_size;

    ddr_size = get_real_ram_size();
    ddr_size = ALIGN(ddr_size, 0x100000);
    ro_boot_ddrsize = ddr_size >> 20;

    if (ro_boot_ddrsize < 512) {
        range = "[0,512)";
    } else if (ro_boot_ddrsize < 1024) {
        range = "[512,1024)";
    } else if (ro_boot_ddrsize < 2048) {
        range = "[1024,2048)";
    } else {
        range = "[2048,)";
    }
#else
    range = "[1024,2048)";
#endif
    sprintf(buf, "androidboot.ddrsize.range=%s", range);
    str_len = strlen(buf);
    buf[str_len] = '\0';

    ret = fdt_chosen_bootargs_append(fdt, buf, 1);

    return 0;
}

#ifdef CONFIG_SANSA_SECBOOT
int fdt_fixup_socid(void *fdt)
{
	char buf[128];
	char *tmp = NULL;
	uint8_t soc_id[32] = {0};
	int str_len;
	int ret;
	int i;

	ret = sansa_compute_socid(soc_id);
	if (ret != 0) {
		errorf("ERROR: compute socid fail!\n");
		return ret;
	}
	memset(buf, 0, sizeof(buf));

	str_len = sprintf(buf, "soc_id=");
	tmp = buf + str_len;
	for (i=0; i<32; i++,tmp+=2) {
		str_len += sprintf(tmp,"%02X",soc_id[i]);
	}
	buf[str_len] = '\0';

	ret = fdt_chosen_bootargs_append(fdt, buf, 1);
	return ret;
}
#endif

#ifdef CONFIG_BOARD_KERNEL_CMDLINE
/**
 *  Fix me:
 *  merge board kernel cmdline to bootargs
 */
int fdt_fixup_board_kernel_cmdline(void *fdt)
{
	int nodeoffset;
	int err, ret;
	int append_flag = 0;
	const char *path;
	char buf[BOOT_ARGS_SIZE+1];
	boot_img_hdr *hdr = (boot_img_hdr *)raw_header;
	char *v, *k, *tmp_v, *tmp_k, *cmdline, *v_copy, *path_copy, *s;

	memset(buf, 0, sizeof(buf));
	memcpy(buf, hdr->cmdline, BOOT_ARGS_SIZE);
	cmdline = buf;

	debugf("android kernel cmdline :%s\n",cmdline);

	/* first, get bootargs value */
	err = fdt_check_header(fdt);
	if (err < 0) {
		errorf("fdt_chosen_bootargs_replace: %s\n", fdt_strerror(err));
		return err;
	}

	/*
	 * Find the "chosen" node.
	 */
	nodeoffset = fdt_path_offset(fdt, "/chosen");

	/*
	 * If there is no "chosen" node in the blob, leave.
	 */
	if (nodeoffset < 0) {
		errorf("fdt_chosen_bootargs_replace: cann't find chosen");
		return -1;
	}

	/*
	 * If the property exists, get the value
	 */
	path = fdt_getprop(fdt, nodeoffset, "bootargs", NULL);
	debugf("before bootargs:%s\n",path);

	/* second, append */
	if (path == NULL) {/* It's almost never gonna happen */
		printf("bootargs empty, board kernel cmdline append!\n");
		ret = fdt_chosen_bootargs_append(fdt, cmdline, 1);
		if (ret < 0)
			errorf("failed to append board kernel cmdline to bootargs\n");

		return ret;
	}

	/* loop for matching */
	while ((v = strsep(&cmdline, " ")) != NULL) {
		v_copy = strdup(v);
		if (v_copy == NULL) {
			errorf("string copy failed!\n");
			return -1;
		}

		k = strsep(&v, "=");
		if (!k)
			break;

		path_copy = strdup(path);
		if (path_copy == NULL) {
			errorf("pathcopy string copy failed!\n");
			free(v_copy);
			return -1;
		}
		s = path_copy;

		while ((tmp_v = strsep(&s, " ")) != NULL) {
			tmp_k = strsep(&tmp_v, "=");
			if (!tmp_k)
				break;

			if (strcmp(tmp_k, k) == 0) {
				append_flag = 0;
				break;
			}

			append_flag = 1;
		}

		if (append_flag) {
			ret = fdt_chosen_bootargs_append(fdt, v_copy, 1);
			if (ret < 0) {
				errorf("failed to append board kernel cmdline to bootargs\n");
				free(v_copy);
				free(path_copy);
				return -1;
			}
			append_flag = 0;
		}

		free(path_copy);
		free(v_copy);
	}

	path = fdt_getprop(fdt, nodeoffset, "bootargs", NULL);
	debugf("after bootargs:%s\n",path);

	return 0;
}
#endif

/**
 *  Fix me:
 *  set loglevel = 7
 */
int fdt_fixup_loglevel(void *fdt)
{
	int nodeoffset;
	const char *path;
	int ret = 0;
	int loglevel;
	char *path_copy, *s, *v, *v_copy, *k, *p;
	char buf[LOGLEVEL_DATA_LEN];

	memset(buf, 0, sizeof(buf));
	p = buf;

	/*
	 * Find the "chosen" node.
	 */
	nodeoffset = fdt_path_offset(fdt, "/chosen");

	/*
	 * If there is no "chosen" node in the blob, leave.
	 */
	if (nodeoffset < 0) {
		errorf("fdt_chosen_bootargs_replace: cann't find chosen");
		return -1;
	}

	/*
	 * If the property exists, get the value
	 */
	path = fdt_getprop(fdt, nodeoffset, "bootargs", NULL);
	if (path == NULL) {
		errorf("bootargs is null\n");
		return -1;
	}

	path_copy = strdup(path);
	if (path_copy == NULL) {
		errorf("pathcopy string copy failed!\n");
		return -1;
	}
	s = path_copy;

	while ((v = strsep(&s, " ")) != NULL) {
		v_copy = strdup(v);
		if (v_copy == NULL) {
			errorf("string copy failed!\n");
			free(path_copy);
			return -1;
		}

		k = strsep(&v, "=");
		if (!k) {
			free(v_copy);
			continue;
		}

		if (strcmp("loglevel", k) == 0) {
			/* get value */
			k = strsep(&v, "=");
			if (!k) {
				free(v_copy);
				continue;
			}

			loglevel = simple_strtol(k, NULL, 10);
			debugf("kernel loglevel = %d\n",loglevel);
			if (loglevel >= 7) {
				free(v_copy);
				break;
			}

			if(common_raw_read("miscdata", (uint64_t)LOGLEVEL_DATA_LEN, LOGLEVEL_DATA_OFFSET, p)) {
				errorf("read miscdata loglevel data error.\n");
				free(v_copy);
				break;
			}

			debugf("read loglevel data {%s} from misc\n", p);
			if (!strncmp("enable", p, strlen("enable"))) {
				char buf[16], *t = p, l = '\0';

				t += strlen("enable");
				if (!t[0])
					l = '7';
				else if (!strncmp(t, ":level=", strlen(":level="))) {
					t += strlen(":level=");
					if (t[0] >= '1' && t[0] <= '6' && t[1] == '\0')
						l = t[0];
				}

				if (l) {
					sprintf(buf, "loglevel=%c", l);
					ret = fdt_chosen_bootargs_replace(fdt, v_copy, buf);
					if (ret < 0)
						errorf("set %s failed!\n", buf);
					else
						debugf("\nupdate kernel %s\n", buf);
				}
			}

			free(v_copy);
			break;
		}

		free(v_copy);
	}

	free(path_copy);
	return ret;
}

int fdt_fixup_system_mount_part_num(void *fdt)
{
	int ret = 0;

#ifndef CONFIG_NAND_BOOT
	if (gd->boot_device == BOOT_DEVICE_EMMC) {
		unsigned int num;
		int nodeoffset;
		const char *path;
		char buf[128];
		int str_len;

		char *path_copy, *s, *v, *v_copy, *k;

		get_img_partition_id("system", &num);
		memset(buf, 0, sizeof(buf));

		/* Find the "chosen" node */
		nodeoffset = fdt_path_offset(fdt, "/chosen");
		/* If there is no "chosen" node in the blob, leave */
		if (nodeoffset < 0) {
			errorf("fdt_chosen_bootargs_replace: cann't find chosen");
			return -1;
		}

		/* If the property exists, get the value */
		path = fdt_getprop(fdt, nodeoffset, "bootargs", NULL);
		if (path == NULL) {
			errorf("bootargs is null\n");
			return -1;
		}
		path_copy = strdup(path);
		if (path_copy == NULL) {
			errorf("path_copy string copy failed!\n");
			return -1;
		}
		s = path_copy;
		while ((v = strsep(&s, " ")) != NULL) {
			v_copy = strdup(v);
			if (v_copy == NULL) {
				errorf("v_copy string copy failed!\n");
				free(path_copy);
				return -1;
			}

			k = strsep(&v, "=");
			if (!k || v == NULL) {
				free(v_copy);
				continue;
			}

			if (strncmp("/dev/mmcblk0p", v, 13) == 0) {
				memset(buf, 0, 128);
				sprintf(buf, "/dev/mmcblk0p%d", num);
				str_len = strlen(buf);
				buf[str_len] = '\0';
				ret = fdt_chosen_bootargs_replace(fdt, v, buf);
				free(v_copy);
				break;
			}
			free(v_copy);
		}
		free(path_copy);
	}
#endif
	return ret;
}

#ifdef CONFIG_GET_CPU_SERIAL_NUMBER
extern int sprd_get_chip_hex_uid(char *buf);
extern void sha256_csum_wd_sw(const unsigned char *input,unsigned int ilen,
		unsigned char *output,unsigned int chunk_sz);
int fdt_fixup_cpu_serial_number(void *fdt)
{
	char *serial;
	int err;
	char serial_num[17];
	char raw_serial_num[32];
	char mask_serial_num[65];
	int cnt;

	memset(serial_num, 0, sizeof(serial_num));
	err = sprd_get_chip_hex_uid(serial_num);
	if (err < 0) {
		printf("read serial number error\n");
		return err;
	}

	memset(raw_serial_num, 0, sizeof(raw_serial_num));
	sha256_csum_wd_sw(serial_num, strlen(serial_num), raw_serial_num, NULL);

	memset(mask_serial_num, 0, sizeof(mask_serial_num));
	for (cnt = 0; cnt < sizeof(raw_serial_num); cnt++) {
		sprintf(mask_serial_num + cnt * 2, "%02x", raw_serial_num[cnt]);
	}

	setenv("serial#", mask_serial_num);

	err = fdt_root(fdt);
	if (err < 0) {
		printf("set serial number error\n");
		return err;
	}

	return 0;
}
#endif

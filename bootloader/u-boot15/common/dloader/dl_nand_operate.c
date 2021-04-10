#include <common.h>
#include <packet.h>
//#include "parsemtdparts.h"
//#include "asm/arch/nand_controller.h"
//#include <linux/mtd/mtd.h>
//#include <linux/mtd/ubi.h>
#include <linux/mtd/partitions.h>

#include <malloc.h>
//#include <ubi_uboot.h>
#include "dl_ubi.h"
#include "dl_common.h"
#include "dl_cmd_proc.h"
#include "dl_nand_operate.h"
#include "parsemtdparts.h"
extern int nand_curr_device ;
#ifdef CONFIG_SECURE_BOOT
#include "secure_verify.h"
#endif
extern uint64_t	spl_read_size;

static dl_status_t dl_stat = { 0 };

#ifndef CONFIG_DTS_MEM_LAYOUT
static char * fdl_buf = (char *)0x82000000;
uint64_t fdl_buf_size = FDL_BUF_LEN;
#else
static char * fdl_buf = NULL;
uint64_t fdl_buf_size = 0;
#endif

extern struct ubi_selected_dev cur_ubi;
static dl_nv_info_t s_nv_backup_cfg[] = {
	{"fixnv1", "fixnv2"},
	{"l_fixnv1", "l_fixnv2"},
	{"runtimenv1", "runtimenv2"},
	{"l_runtimenv1", "l_runtimenv2"},
	{"nr_fixnv1", "nr_fixnv2"},
	{"nr_runtimenv1", "nr_runtimenv2"},
	{"tdfixnv1", "tdfixnv2"},
	{"tdruntimenv1", "tdruntimenv2"},
	{"wfixnv1", "wfixnv2"},
	{"wruntimenv1", "wruntimenv2"},
	{"w_fixnv1", "w_fixnv2"},
	{"w_runtimenv1", "w_runtimenv2"},
	{"wcnfixnv1", "wcnfixnv2"},
	{"wcnruntimenv1", "wcnruntimenv2"},
	{NULL, NULL}
};

#ifdef CONFIG_DTS_MEM_LAYOUT

#define SET_DOWNLOAD_BUFFER_BASE_SIZE_SEC(basep, sizep)                get_buffer_base_size_from_dt("heap@5", basep, sizep)
#define SET_DOWNLOAD_BUFFER_BASE_SIZE_NOSEC(basep, sizep)             get_buffer_base_size_from_dt("heap@6", basep, sizep)

int set_buf_base_size()
{
	unsigned long buf_base;

#ifdef CONFIG_SECURE_BOOT
	if (SET_DOWNLOAD_BUFFER_BASE_SIZE_SEC(&buf_base, &fdl_buf_size) < 0) {
		errorf("set download buffer error\n");
		return -1;
	}
#else
	if (SET_DOWNLOAD_BUFFER_BASE_SIZE_NOSEC(&buf_base, &fdl_buf_size) < 0) {
		errorf("set download buffer error\n");
		return -1;
	}
#endif

	fdl_buf = (unsigned char *)ALIGN(buf_base , 8);

	debugf("download buffer base 0x%lx, size 0x%llx\n",fdl_buf, fdl_buf_size);

	return 0;
}
#endif


#ifdef CONFIG_SECURE_BOOT
static int secure_image_flag = 0;
static int check_secure_flag = 0;

static char *const s_force_secure_check[] = {
	"spl", "uboot", "boot", "recovery", "tdmodem", "tddsp", "wmodem", "wdsp", "wcnmodem", NULL
};

static int _nand_check_secure_part(uchar * partition_name)
{
	int i = 0;
	do {
		if (0 == strcmp(s_force_secure_check[i], partition_name))
			return i;
		i++;
	}
	while (s_force_secure_check[i] != 0);

	return -1;
}

#endif
struct mtd_info *_get_cur_nand(void)
{
	if ((nand_curr_device < 0) || (nand_curr_device >= CONFIG_SYS_MAX_NAND_DEVICE)) {
		printf("--->get current nand failed<---\n");
		return NULL;
	}
	return &nand_info[nand_curr_device];
}

/**
 * check whether is a nv volume.
 * return backup nv volume in case of true, otherwise null.
 */
static char *_is_nv_volume(char *volume)
{
	int i;

	for (i = 0; s_nv_backup_cfg[i].vol != NULL; i++) {
		if (0 == strcmp(volume, s_nv_backup_cfg[i].vol)) {
			return s_nv_backup_cfg[i].bakvol;
		}
	}
	return NULL;
}

/**
 * parse mtd partitions from a string.
 */
static int _parse_mtd_partitions(void)
{
	struct mtd_info *nand = NULL;

	nand = _get_cur_nand();
	if (!nand)
		return 0;
	parse_cmdline_partitions(nand->size);
	return 1;
}

/**
 * get mtd partition info from partition table parsed.
 */
int _get_mtd_partition_info(char *name, struct mtd_partition *part)
{
	int ret;

	if (!_parse_mtd_partitions())
		return 0;

	ret = parse_mtd_part_info(name, part);
	if (ret != 1)
		return 0;

	return 1;
}

/**
 * add volume info to change list.
 */
static int _dl_add_to_list(char *name, long long size, int autoresize, struct list_head *list)
{
	fdl_ubi_cvol_t *cvol;

	cvol = malloc(sizeof(fdl_ubi_cvol_t));
	if (!cvol) {
		debugf("malloc failed.\n");
		return PART_FATAL_ERR;
	}

	cvol->name = name;
	cvol->size = size;
	cvol->autoresize = autoresize;
	list_add_tail(&cvol->list, list);
	return 0;
}

/**
 * parse volume table config, just compatible with dl tool.
 */
static void _dl_parse_volume_cfg(uchar * vol_cfg, uint16_t total_num, fdl_ubi_vtbl_t * vtbl)
{
	int i, j;
	int64_t size;

	/*Decode String: Partition Name(72Byte)+SIZE(4Byte)+... */
	for (i = 0; i < total_num; i++) {
		size = *(uint32_t *) (vol_cfg + 76 * (i + 1) - 4);
		/*the partition size received from tool is MByte */
		if (AUTO_RESIZE_FLAG == size) {
			vtbl[i].size = 1024 * 1024;	//just set size as 1M when autoresize flag enable
			vtbl[i].autoresize = 1;
		} else
			vtbl[i].size = 1024 * 1024 * size;

		for (j = 0; j < 36; j++) {
			/*convert name wchar to char with violent */
			vtbl[i].name[j] = *((uint16_t *) vol_cfg + 38 * i + j) & 0xFF;
		}
		vtbl[i].name[j] = '\0';

		printf("volume name:%s,size:0x%llx,autoresize flag:%d\n", vtbl[i].name, vtbl[i].size, vtbl[i].autoresize);
	}
	return;
}

/**
 * update the nv volume with nv header.
 */
static int _dl_update_nv(char *vol, char *bakvol, int size, char *data)
{
	int ret, time = 1;
	char *buf;
	char *nvbuf = NULL;
	char *curvol;
	char tmp[NV_HEAD_LEN];
	nv_header_t *header;

	if (size > dl_stat.bufsize) {
		nvbuf = malloc(size + NV_HEAD_LEN);
		if (!nvbuf) {
			debugf("buf malloc failed.\n");
			return -1;
		}
		buf = nvbuf;
		fdl_ubi_volume_read(dl_stat.ubi.dev, dl_stat.ubi.cur_volnm, buf, size, 0);
		if (size != ret) {
			debugf("read volume %s failed.\n", dl_stat.ubi.cur_volnm);
			goto err;
		}
	} else {
		buf = data;
	}

	memset(tmp, 0x0, NV_HEAD_LEN);
	header = (nv_header_t *) tmp;
	header->magic = NV_HEAD_MAGIC;
	header->version = NV_VERSION;
	header->len = size;
	header->checksum = fdl_calc_checksum(buf, size);
	curvol = vol;
	do {
		ret = fdl_ubi_volume_start_update(dl_stat.ubi.dev, curvol, size + NV_HEAD_LEN);
		if (ret) {
			debugf("vol %s start update failed!\n", curvol);
			goto err;
		}
		ret = fdl_ubi_volume_write(dl_stat.ubi.dev, curvol, tmp, NV_HEAD_LEN);
		if (ret) {
			printf("%s volume write error %d!\n", curvol, ret);
			goto err;
		}
		ret = fdl_ubi_volume_write(dl_stat.ubi.dev, curvol, buf, size);
		if (ret) {
			printf("%s volume write error %d!\n", curvol, ret);
			goto err;
		}
		curvol = bakvol;
	}
	while (time--);

	printf("update nv success!\n");
	return 0;
err:
	if (nvbuf)
		free(nvbuf);
	return -1;
}

static int _dl_check_nv(char *vol)
{
	char *buf = 0, *bakbuf = 0, *pbakvol = 0;
	nv_header_t *header;
	int ret = OPERATE_SYSTEM_ERROR;
	int size = FIXNV_SIZE + NV_HEAD_LEN;
	uint8_t status_nand = 0;
	int chkRet = -1;

/*read org*/
	buf = malloc(size);
	if (!buf) {
		debugf("buf malloc failed.\n");
		goto out;
	}
	ret = fdl_ubi_volume_read(dl_stat.ubi.dev, vol, buf, size, 0);
	if (size != ret) {
		debugf("can read 0x%x data from vol %s ret %d!!\n", size, vol, ret);
	} else {
		header = (nv_header_t *) buf;
		ret = fdl_check_crc(buf + NV_HEAD_LEN, header->len, header->checksum);
		if (ret) {
			status_nand |= 1;
			debugf("org nv is ok.\n");
		} else {
			debugf("org nv is damaged.\n");
		}
	}

/*read backup*/
	bakbuf = malloc(size);
	if (!bakbuf) {
		debugf("bakbuf malloc failed.\n");
		goto out;
	}
	debugf("bakbuf malloc succees.\n");
	pbakvol = _is_nv_volume(vol);
	if (!pbakvol) {
		goto out;
	}
	ret = fdl_ubi_volume_read(dl_stat.ubi.dev, pbakvol, bakbuf, size, 0);
	if (size != ret) {
		debugf("can read 0x%x data from bakup %s ret %d!!!\n", size, pbakvol, ret);
	} else {
		header = (nv_header_t *) bakbuf;
		ret = fdl_check_crc(bakbuf + NV_HEAD_LEN, header->len, header->checksum);
		if (ret) {
			status_nand |= 2;
			debugf("bak nv is ok.\n");
		} else {
			debugf("bak nv is damaged.\n");
		}
	}
	switch (status_nand) {
	case 0:
		debugf("both org and bak nv are damaged.\n");
		goto out;
		break;
	case 1:
		debugf("bak nv is damaged.\n");
		fdl_ubi_volume_start_update(dl_stat.ubi.dev, pbakvol, size);
		ret = fdl_ubi_volume_write(dl_stat.ubi.dev, pbakvol, buf, size);
		if (ret) {
			debugf("bak ubi volume write error %d!\n", ret);
			goto out;
		}
		chkRet = 0;
		break;
	case 2:
		debugf("org nv is damaged.\n");
		fdl_ubi_volume_start_update(dl_stat.ubi.dev, vol, size);
		ret = fdl_ubi_volume_write(dl_stat.ubi.dev, vol, bakbuf, size);
		if (ret) {
			debugf("org ubi volume write error %d!\n", ret);
			goto out;
		}
		chkRet = 0;
		break;
	case 3:
		debugf("both org and bak nv are ok.\n");
		chkRet = 0;
		break;
	default:
		debugf("status_nand error!\n");
		goto out;
		break;
	}
out:
	if (bakbuf) {
		free(bakbuf);
	}
	if (buf) {
		free(buf);
	}
	return chkRet;
}

/**
 * check whether the new volumes table same with original.
 * return 0 in case of diff and 1 in case of same.
 */
static int _dl_vtbl_check(fdl_ubi_vtbl_t * vtbl, int total_vols, struct list_head *rm, struct list_head *mk)
{
	int i, j;
	int arid = -1;
	int same = 0, fulleq = 1;
	struct ubi_volume *vol;
	struct ubi_device *ubi = cur_ubi.dev;
	int32_t ret = 0;

	if (!cur_ubi.ubi_initialized) {
		debugf("ubi init failed.\n");
		return -1;
	}

	if (!(ubi->vol_count - UBI_INT_VOL_COUNT)) {
		debugf("empty ubi device.\n");
		return -1;
	}

	if (total_vols != (ubi->vol_count - UBI_INT_VOL_COUNT)) {
		debugf("new vol count is %d,old vol count is %d.\n", total_vols, ubi->vol_count - UBI_INT_VOL_COUNT);
		fulleq = 0;
	}

	for (i = 0; i < total_vols; i++) {
		same = 0;
		for (j = 0; j < ubi->vtbl_slots; j++) {
			vol = ubi->volumes[j];
			if (vol && !strcmp(vol->name, vtbl[i].name)) {
				printf("Volume \"%s\" found at volume id %d.\n", vtbl[i].name, j);
				if (vtbl[i].autoresize) {
					/*autoresize_vol_id flag will set -1 after ubi attach, so we can't get it. */
					same = 1;
					arid = i;
				} else {
					int new_rsvd_pebs = 0;
					uint64_t bytes = vtbl[i].size;
					if (do_div(bytes, vol->usable_leb_size))
						new_rsvd_pebs = 1;
					new_rsvd_pebs += bytes;
					if (new_rsvd_pebs == vol->reserved_pebs)
						same = 1;
					else
						printf("reserved pebs not same,new %d,old %d.\n", new_rsvd_pebs, vol->reserved_pebs);
					if (!same) {
						printf("add volume \"%s\" to remove list.\n", vtbl[i].name);
						ret = _dl_add_to_list(vtbl[i].name, 0, 0, rm);
						if (0 != ret)
							return ret;
					}
				}
				break;
			}
		}
		if (!same) {
			fulleq = 0;
			printf("add volume \"%s\" to create list.\n", vtbl[i].name);
			ret = _dl_add_to_list(vtbl[i].name, vtbl[i].size, vtbl[i].autoresize, mk);
			if (0 != ret)
				return ret;
		}
	}

	for (i = 0; i < ubi->vtbl_slots; i++) {
		same = 0;
		vol = ubi->volumes[i];
		if (!vol)
			continue;
		printf("old volume slot: %d, name \"%s\"\n", i, vol->name);
		for (j = 0; j < total_vols; j++) {
			if (!strcmp(vol->name, vtbl[j].name)) {
				same = 1;
				break;
			}
		}
		if (!same) {
			fulleq = 0;
			printf("add volume \"%s\" to remove list.\n", vol->name);
			_dl_add_to_list(vol->name, 0, 0, rm);
			if (0 != ret)
				return ret;
		}
	}

	if (fulleq) {
		return 1;
	} else {
		if (arid >= 0) {
			printf("add autoresize volume \"%s\" to rm/mk list.\n", vtbl[arid].name);
			ret = _dl_add_to_list(vtbl[arid].name, 0, 0, rm);
			if (0 != ret)
				return ret;
			ret = _dl_add_to_list(vtbl[arid].name, vtbl[arid].size, vtbl[arid].autoresize, mk);
			if (0 != ret)
				return ret;
		}
		return 0;
	}
}

/**
 * nand write and dl_stat update.
 */
static void _dl_nand_write(nand_info_t * nand, unsigned long long offset, unsigned long length, char *buffer)
{
	int ret;

	printf("_dl_nand_write:partname:%s,offset:0x%llx,len:0x%x\n", dl_stat.mtd.name, offset, length);
	//TODO:temp here for step 1 debug
	if (strcmp(dl_stat.mtd.name, "splloader") == 0) {
		ret = sprd_nand_write_spl(buffer, dl_stat.nand);
		if (ret)
			printf("write spl fail\n");
		else
			printf("write spl\n");
		dl_stat.wp = 0;
		dl_stat.unsv_size = 0;
		return;
	}
	switch (dl_stat.part_type) {
	case PART_TYPE_MTD:
		ret = nand_write_skip_bad(nand, offset, &length, NULL, dl_stat.mtd.size, buffer, 0);
		dl_stat.unsv_size -= length;
		memmove(dl_stat.buf, dl_stat.buf + length, dl_stat.unsv_size);
		dl_stat.wp -= length;
		dl_stat.mtd.rw_point += length;
		if (ret) {
			/*mark a block as badblock */
			printf("nand write error %d, mark bad block 0x%llx\n", ret, dl_stat.mtd.rw_point & ~(nand->erasesize - 1));
			nand->_block_markbad(nand, dl_stat.mtd.rw_point & ~(nand->erasesize - 1));
		}
		break;
	case PART_TYPE_UBI:
		debugf("write volume %s\n", dl_stat.ubi.cur_volnm);
		ret = fdl_ubi_volume_write(dl_stat.ubi.dev, dl_stat.ubi.cur_volnm, buffer, length);
		if (ret) {
			printf("ubi volume write error %d!\n", ret);
			return;
		}
		dl_stat.unsv_size -= length;
		memmove(dl_stat.buf, dl_stat.buf + length, dl_stat.unsv_size);
		dl_stat.wp -= length;
		break;
	default:
		debugf("part type error!\n");
		return;
	}

	return;
}

/**
 * erase the given mtd part.
 * return 0 in case of success.
 */
int _dl_mtd_part_erase(nand_info_t * nand, char *name)
{
	int ret;
	struct mtd_partition mtd_part;
	nand_erase_options_t opts;

	ret = _get_mtd_partition_info(name, &mtd_part);
	if (ret) {
		memset(&opts, 0, sizeof(opts));
		opts.offset = mtd_part.offset;
		opts.length = mtd_part.size;
		opts.quiet = 0;
		debugf("erase offset 0x%x ,size 0x%x\n", opts.offset, opts.length);
		ret = nand_erase_opts(nand, &opts);
		debugf("erase OK\n");
		if (!ret)
			return 0;
		debugf("nand erase %s failure %d\n", name, ret);
	} else
		debugf("Can't find part %s", name);
	return 1;
}

/**
 * parse the given part is mtd partition or ubi volume.
 */
static void _dl_part_info_parse(char *part)
{
	int ret;
	struct mtd_partition mtd_part;
	struct ubi_volume_desc *vol;

	ret = _get_mtd_partition_info(part, &mtd_part);
	if (ret) {
		strncpy(dl_stat.mtd.name, part, MAX_PARTITION_NAME_SIZE);
		dl_stat.mtd.size = mtd_part.size;
		dl_stat.mtd.rw_point = mtd_part.offset;
		dl_stat.part_type = PART_TYPE_MTD;
		return;
	}

	vol = ubi_open_volume_nm(cur_ubi.dev_num, part, UBI_READWRITE);
	if (IS_ERR(vol)) {
		printf("cannot open volume \"%s\", error %d\n", part, (int)PTR_ERR(vol));
	} else {
		dl_stat.ubi.dev = cur_ubi.dev;
		dl_stat.ubi.dev_num = cur_ubi.dev_num;
		strncpy(dl_stat.ubi.cur_volnm, part, UBI_VOL_NAME_MAX);
		dl_stat.ubi.cur_voldesc = vol;
		dl_stat.part_type = PART_TYPE_UBI;
		return;
	}
	dl_stat.part_type = PART_TYPE_MAX;
	printf("Can't find part %s.\n", part);
	return;
}

/**
 * dl_download_start
 *
 * Get download info from download start command which  
 * will used in next step
 *
 * @param part partition/volume name
 * @param size total download size
 * @param nv_checksum NA
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_download_start(char *name, uint32_t size, uint32_t nv_checksum)
{
	int ret;
	int index;

#ifdef CONFIG_SECURE_BOOT
	printf("dl_download_start(): check secure part. name:%s, size:%d.\n", name, size);
	index = _nand_check_secure_part(name);
	if (index != -1) {
		printf("fdl2_download_start(): the part should be checked. %s\n", name);
		/*because there is no secure header flag in the spl image. */
		if (strcmp(name, "spl") == 0) {
			secure_image_flag = ENABLE_SECURE;	//1;
			check_secure_flag = UNABLE_SECURE;	//0;
		} else {
			secure_image_flag = UNABLE_SECURE;	//0;
			check_secure_flag = ENABLE_SECURE;	//1;
		}
	} else {
		secure_image_flag = UNABLE_SECURE;	//0;
		check_secure_flag = UNABLE_SECURE;	//0;
	}
#endif
	memset(&dl_stat, 0x0, sizeof(dl_status_t));

	dl_stat.nand = _get_cur_nand();
	if (NULL == dl_stat.nand)
		return OPERATE_DEVICE_INIT_ERROR;

	_dl_part_info_parse(name);

	switch (dl_stat.part_type) {
	case PART_TYPE_MTD:
		if (size > dl_stat.mtd.size) {
			debugf("dl size 0x%x > partition size 0x%llx\n", size, dl_stat.mtd.size);
			ret = OPERATE_INVALID_SIZE;
			goto err;
		}
#ifdef CONFIG_SECURE_BOOT
		if (!secure_image_flag && !check_secure_flag) {
#endif
			ret = _dl_mtd_part_erase(dl_stat.nand, name);
			if (ret) {
				debugf("mtd %s erase failed!\n", name);
				ret = OPERATE_SYSTEM_ERROR;
				goto err;
			}
#ifdef CONFIG_SECURE_BOOT
		}
#endif
		break;
	case PART_TYPE_UBI:
		if (size > dl_stat.ubi.cur_voldesc->vol->used_bytes) {
			printf("dl size > partition size!\n");
			ret = OPERATE_INVALID_SIZE;
			goto err;
		}
#ifdef CONFIG_SECURE_BOOT
		if (!secure_image_flag && !check_secure_flag) {
#endif
			ret = fdl_ubi_volume_start_update(dl_stat.ubi.dev, name, size);
			if (ret) {
				debugf("vol %s start update failed!\n", name);
				ret = OPERATE_SYSTEM_ERROR;
				goto err;
			}
#ifdef CONFIG_SECURE_BOOT
		}
#endif
		break;
	default:
		ret = OPERATE_INCOMPATIBLE_PART;
		goto err;
	}

	dl_stat.total_dl_size = size;
	dl_stat.recv_size = 0;
	dl_stat.unsv_size = 0;
	dl_stat.buf = fdl_buf;
	dl_stat.bufsize = fdl_buf_size;
	dl_stat.rp = 0;
	dl_stat.wp = 0;

	printf("fdl2_download_start:part:%s,size:0x%x\n", name, size);

	return OPERATE_SUCCESS;
err:

	return ret;
}

/**
 * dl_download_midst
 *
 * Save data to fdl buf and finally write it to nand flash
 *
 * @param size total download size
 * @param buf data recvd
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_download_midst(uint32_t size, char *buf)
{
	int ret = 0;
	unsigned int cpy_len = 0, unsv_len = 0;
	unsigned long len;
	nand_info_t *nand;
#ifdef CONFIG_SECURE_BOOT
	if (check_secure_flag == ENABLE_SECURE /*1 */ ) {
		check_secure_flag = UNABLE_SECURE;	//0;
		if (secure_header_parser(buf) != 1) {
			secure_image_flag = UNABLE_SECURE;	//0;
			return 0;
		} else {
			secure_image_flag = ENABLE_SECURE;	//1;
		}
	}

	if (secure_image_flag == ENABLE_SECURE /*1 */ ) {
		dl_stat.recv_size += size;
		unsv_len = size;
		memcpy(dl_stat.buf + dl_stat.wp, &buf[size - unsv_len], unsv_len);
		dl_stat.wp += unsv_len;
		dl_stat.unsv_size += unsv_len;
		return 1;
	}
#endif

	nand = dl_stat.nand;
	dl_stat.recv_size += size;
	unsv_len = size;
	while ((dl_stat.unsv_size + unsv_len) > dl_stat.bufsize) {
		len = dl_stat.unsv_size;
		len = len & ~(nand->erasesize - 1);

		_dl_nand_write(nand, dl_stat.mtd.rw_point, len, dl_stat.buf);

		cpy_len = dl_stat.bufsize - dl_stat.unsv_size;
		cpy_len = (unsv_len > cpy_len) ? cpy_len : unsv_len;
		memcpy(dl_stat.buf + dl_stat.wp, &buf[size - unsv_len], cpy_len);
		unsv_len -= cpy_len;
		dl_stat.wp += cpy_len;
		dl_stat.unsv_size += cpy_len;
	}

	/*copy data to dl buf */
	memcpy(dl_stat.buf + dl_stat.wp, &buf[size - unsv_len], unsv_len);
	dl_stat.wp += unsv_len;
	dl_stat.unsv_size += unsv_len;

	if (dl_stat.recv_size == dl_stat.total_dl_size) {
		len = dl_stat.unsv_size;
		_dl_nand_write(nand, dl_stat.mtd.rw_point, len, dl_stat.buf);
	}

	return OPERATE_SUCCESS;
}

/**
 * dl_download_end
 *
 * Set download end
 *
 * @param void
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_download_end(void)
{
	int i = 0;
	char *name;
	int ret = OPERATE_SUCCESS;

#ifdef CONFIG_SECURE_BOOT
	if (secure_image_flag) {
		if (dl_stat.part_type == PART_TYPE_MTD) {
			name = dl_stat.mtd.name;
		} else if (dl_stat.part_type == PART_TYPE_UBI) {
			name = dl_stat.ubi.cur_volnm;
		} else {
			return 0;
		}

		if (strcmp(name, "spl") == 0) {
			secure_verify("splloader0", dl_stat.buf, 0);
		} else if (strcmp(name, "uboot") == 0) {
			secure_verify("splloader", dl_stat.buf, 0);
		} else {
			secure_verify("fdl2", dl_stat.buf, 0);
		}

		switch (dl_stat.part_type) {
		case PART_TYPE_MTD:
			ret = _dl_mtd_part_erase(dl_stat.nand, name);
			if (ret) {
				printf("%s:mtd %d erase failed!\n", __FUNCTION__, name);
			}
			break;
		case PART_TYPE_UBI:
			ret = fdl_ubi_volume_start_update(dl_stat.ubi.dev, name, dl_stat.total_dl_size);
			if (ret) {
				printf("%s: vol %s start update failed!\n", __FUNCTION__, name);
			}
			break;
		default:
			break;
		}
		if (ret != 0) {
			return 0;
		}
		else
		{
			ret = OPERATE_SUCCESS;
		}
	}
#endif
	while (0 != dl_stat.unsv_size) {
		_dl_nand_write(dl_stat.nand, dl_stat.mtd.rw_point, dl_stat.unsv_size, dl_stat.buf);
		if (i++ > 1) {
			printf("download end write error, try 2 times.\n");
			return OPERATE_SYSTEM_ERROR;
		}
	}
	/*close opened ubi volume */
	if (PART_TYPE_UBI == dl_stat.part_type) {
		int err;
		char *bakvol;
		bakvol = _is_nv_volume(dl_stat.ubi.cur_volnm);
		if (bakvol) {
			err = _dl_update_nv(dl_stat.ubi.cur_volnm, bakvol, dl_stat.total_dl_size, dl_stat.buf);
			if (err)
				ret = OPERATE_SYSTEM_ERROR;
		}
		ubi_close_volume(dl_stat.ubi.cur_voldesc);
	}
#ifdef CONFIG_SECURE_BOOT
	secure_image_flag = UNABLE_SECURE;	//0;
	check_secure_flag = UNABLE_SECURE;	// 0;
#endif
	return ret;
}

/**
 * dl_read_start
 *
 * Get partition/volume info from read start command which  
 * will used in next step
 *
 * @param part partition/volume name
 * @param size total size
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_read_start(char *part, uint32_t size)
{
	int ret;

	memset(&dl_stat, 0x0, sizeof(dl_status_t));

	dl_stat.nand = _get_cur_nand();
	if (NULL == dl_stat.nand)
		return OPERATE_DEVICE_INIT_ERROR;

	_dl_part_info_parse(part);

	switch (dl_stat.part_type) {
	case PART_TYPE_MTD:
		if (size > dl_stat.mtd.size) {
			debugf("read size 0x%x > partition size 0x%llx\n", size, dl_stat.mtd.size);
			ret = OPERATE_INVALID_SIZE;
			goto err;
		}
		break;
	case PART_TYPE_UBI:
		if (size > dl_stat.ubi.cur_voldesc->vol->used_bytes) {
			debugf("read size 0x%x > partition size 0x%llx\n", size, dl_stat.ubi.cur_voldesc->vol->used_bytes);
			ret = OPERATE_INVALID_SIZE;
			goto err;
		}
		if (_is_nv_volume(dl_stat.ubi.cur_volnm)) {
			_dl_check_nv(dl_stat.ubi.cur_volnm);
		}
		if (!strcmp(dl_stat.ubi.cur_volnm, "prodnv")) {
			u32 magic;
			fdl_ubi_volume_read(dl_stat.ubi.dev, dl_stat.ubi.cur_volnm, &magic, sizeof(u32), 0);
			if (magic != UBIFS_NODE_MAGIC) {
				printf("bad ubifs node magic %#08x, expected %#08x\n", magic, UBIFS_NODE_MAGIC);
				ret = OPERATE_SYSTEM_ERROR;
				goto err;
			}
		}
		break;
	default:
		debugf("Incompatible part %s!\n", part);
		ret = OPERATE_INCOMPATIBLE_PART;
		goto err;
	}

	debugf("fdl2_read_start:%s,size:0x%x\n", part, size);

	return OPERATE_SUCCESS;
err:
	return ret;
}

/**
 * dl_read_midst
 *
 * Read partition/volume data
 *
 * @param size size to be read
 * @param off offset of begin of part/vol
 * @param buf data saved
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_read_midst(uint32_t size, uint32_t off, uchar * buf)
{
	int ret;
	size_t read_size = (size_t) size;
	size_t read_offset = (size_t) off;
	switch (dl_stat.part_type) {
	case PART_TYPE_MTD:
		if(0 == strcmp(dl_stat.mtd.name,"splloader")) {
			if(off == 0){
				ret = sprd_nand_read_spl(fdl_buf, dl_stat.nand, spl_read_size);
				if (ret)
					goto err;
				debugf("read %s finish\n", dl_stat.mtd.name);
			}
			memcpy(buf, fdl_buf+off, read_size);
		} else if (strcmp(dl_stat.mtd.name,"uboot") == 0) {
			if(off == 0){
				ret = nand_read_skip_bad(dl_stat.nand, dl_stat.mtd.rw_point + off, &spl_read_size, NULL, dl_stat.mtd.size, fdl_buf);
				if (ret)
					goto err;
				debugf("read %s finish\n", dl_stat.mtd.name);
			}
			memcpy(buf, fdl_buf+off, read_size);
		}else{
			ret = nand_read_skip_bad(dl_stat.nand, dl_stat.mtd.rw_point + off, &read_size, NULL, dl_stat.mtd.size, buf);
			if (ret)
				goto err;
		}
		break;
	case PART_TYPE_UBI:
		if (_is_nv_volume(dl_stat.ubi.cur_volnm)) {
			read_offset += NV_HEAD_LEN;
		}
		ret = fdl_ubi_volume_read(dl_stat.ubi.dev, dl_stat.ubi.cur_volnm, buf, read_size, read_offset);
		if (size != ret)
			goto err;
		break;
	default:
		debugf("part type err!\n");
		goto err;
	}

	return OPERATE_SUCCESS;
err:
	debugf("read error %d!\n", ret);
	return OPERATE_SYSTEM_ERROR;
}

/**
 * dl_read_end
 *
 * Set read flash end
 *
 * @param void
 * @return 0 failed
 *         1 success
 */
OPERATE_STATUS dl_read_end(void)
{
	//close opened ubi volume
	if (PART_TYPE_UBI == dl_stat.part_type) {
		ubi_close_volume(dl_stat.ubi.cur_voldesc);
	}

	return OPERATE_SUCCESS;
}

/**
 * dl_erase
 *
 * Erase partition/volume
 *
 * @param part partition/volume name
 * @param size size to be erased(no use now)
 * @return 0 failed
 *             1 success
 */
OPERATE_STATUS dl_erase(char *part, uint32_t size)
{
	int ret;
	char *bak_vol;
	struct mtd_info *nand = NULL;

	nand = _get_cur_nand();
	if (NULL == nand)
		return OPERATE_DEVICE_INIT_ERROR;

	if (!strcmp(part, "erase_all")) {
		nand_erase_options_t opts;

		memset(&opts, 0, sizeof(opts));
		nand = _get_cur_nand();
		opts.offset = 0;
		opts.length = nand->size;
		opts.quiet = 1;
		ret = nand_erase_opts(nand, &opts);
		if (ret) {
			ret = OPERATE_SYSTEM_ERROR;
			goto err;
		}
		//reinit after erase all
		fdl_ubi_dev_init();
		goto end;
	}

	_dl_part_info_parse(part);

	switch (dl_stat.part_type) {
	case PART_TYPE_MTD:
		ret = _dl_mtd_part_erase(nand, part);
		if (ret) {
			debugf("mtd %s erase failed!\n", part);
			ret = OPERATE_SYSTEM_ERROR;
			goto err;
		}
		break;
	case PART_TYPE_UBI:
		bak_vol = _is_nv_volume(dl_stat.ubi.cur_volnm);
		if (bak_vol) {
			ret = fdl_ubi_volume_start_update(dl_stat.ubi.dev, bak_vol, 0);
			if (ret) {
				debugf("backup : vol %s erase failed!\n", part);
				ret = OPERATE_SYSTEM_ERROR;
				goto err;
			}
		}
		ret = fdl_ubi_volume_start_update(dl_stat.ubi.dev, part, 0);
		if (ret) {
			debugf("vol %s erase failed!\n", part);
			ret = OPERATE_SYSTEM_ERROR;
			goto err;
		}
		ubi_close_volume(dl_stat.ubi.cur_voldesc);
		break;
	default:
		debugf("Incompatible part %s!\n", part);
		ret = OPERATE_INCOMPATIBLE_PART;
		goto err;
	}
end:
	ret = OPERATE_SUCCESS;
	return ret;
err:
	return ret;
}

OPERATE_STATUS dl_repartition(uchar * partition_cfg, uint16_t total_partition_num,
									uchar version, uchar size_unit)

{
	int ret, i, vol_id, auto_resize_id = -1;
	fdl_ubi_vtbl_t *vtbl = NULL;
	fdl_ubi_cvol_t *cvol, *cvol_tmp;
	struct list_head remove;
	struct list_head create;
	struct mtd_info *nand = NULL;

	//return OPERATE_SUCCESS;
	INIT_LIST_HEAD(&remove);
	INIT_LIST_HEAD(&create);

	nand = _get_cur_nand();
	if (NULL == nand)
		return OPERATE_DEVICE_INIT_ERROR;

	vtbl = malloc(total_partition_num * sizeof(fdl_ubi_vtbl_t));
	if (!vtbl) {
		debugf("malloc vtbl failed!\n");
		goto err;
	}
	memset(vtbl, 0x0, total_partition_num * sizeof(fdl_ubi_vtbl_t));
	_dl_parse_volume_cfg(partition_cfg, total_partition_num, vtbl);

	ret = _dl_vtbl_check(vtbl, total_partition_num, &remove, &create);
	switch (ret) {
	case PART_SAME:
		debugf("ubi volumes are same.\n");
		ret = OPERATE_SUCCESS;
		goto end;

	case PART_DIFF:
		debugf("partial repartition.\n");
		goto partial_repartition;

	case PART_FAIL:
		debugf("full repartition.\n");
		goto full_repartition;

	case PART_FATAL_ERR:
		debugf("fatal error , no way to continue repartition.\n");
		goto err;
	default:
		debugf("unknown volumes table check return value ,can not repartition.\n");
		goto err;
	}

full_repartition:
	ret = _dl_mtd_part_erase(nand, UBIPAC_PART);
	debugf("full repartition erase mtd part finish ,ret=%d\n", ret);
	//return OPERATE_SUCCESS;
	if (ret)
		goto err;
	ret = fdl_ubi_dev_init();
	debugf("full repartition init ubi dev finish \n");
	if (!ret) {
		printf("attach ubi failed after erase!\n");
		goto err;
	}
	/*create volumes */
	for (i = 0; i < total_partition_num; i++) {
		ret = fdl_ubi_create_vol(cur_ubi.dev, vtbl[i].name, &vol_id, vtbl[i].size, 1);
		if (ret) {
			printf("ubi vol \"%s\" create err %d.\n", vtbl[i].name, ret);
			goto err;
		}
		if (vtbl[i].autoresize) {
			auto_resize_id = vol_id;
		}
	}
	goto autoresize;

partial_repartition:
	list_for_each_entry(cvol, &remove, list) {
		debugf("partial_repartition remove vol \"%s\" \n", cvol->name);
		ret = fdl_ubi_remove_vol(cur_ubi.dev, cvol->name);
		if (ret) {
			debugf("ubi vol \"%s\" remove err %d.\n", cvol->name, ret);
			goto err;
		}
	}
	list_for_each_entry(cvol, &create, list) {
		debugf("partial_repartition create vol \"%s\" size:0x%llx atr-flag:%d\n", cvol->name, cvol->size, cvol->autoresize);
		ret = fdl_ubi_create_vol(cur_ubi.dev, cvol->name, &vol_id, cvol->size, 1);
		if (ret) {
			debugf("ubi vol \"%s\" create err %d.\n", cvol->name, ret);
			goto err;
		}
		if (cvol->autoresize) {
			auto_resize_id = vol_id;
		}
	}

autoresize:
	/*resize the autoresize volume */
	if (-1 != auto_resize_id) {
		ret = fdl_ubi_volume_autoresize(cur_ubi.dev, auto_resize_id);
		if (ret) {
			debugf("volume auto resize failed %d.\n", ret);
			goto err;
		}
	}

	ret = OPERATE_SUCCESS;
end:
	list_for_each_entry_safe(cvol, cvol_tmp, &remove, list) {
		list_del(&cvol->list);
		free(cvol);
	}
	list_for_each_entry_safe(cvol, cvol_tmp, &create, list) {
		list_del(&cvol->list);
		free(cvol);
	}
	free(vtbl);
	return ret;
err:
	ret = OPERATE_SYSTEM_ERROR;
	goto end;
}

OPERATE_STATUS dl_get_mcptype(uchar * content, uint16_t * size)
{
	struct mtd_info *nand;
	struct MCP_TYPE mcp_type;
	char temp[sizeof(struct MCP_TYPE)];
	int i = 0;
	int j = 0;
	debugf("enter\n");
	nand = _get_cur_nand();
	mcp_type.flag = 0;
	mcp_type.pagesize = nand->writesize;
	mcp_type.blocksize = nand->erasesize;
	*size = sizeof(struct MCP_TYPE);
	memcpy(temp, &mcp_type, *size);
	for (i = 0; i < *size; i++) {
		if ((i % 4) == 0)
			j = i + 4;
		content[i] = temp[--j];
	}
	debugf("return\n");
	return 1;
}

OPERATE_STATUS dl_record_pacdatetime(uchar * buf, uint64_t size)
{
	if(0 != common_raw_write(DATATIME_PARTNAME, size, (uint64_t)0, DATETIME_OFFSET, buf)){
		return OPERATE_WRITE_ERROR;
	}
	return OPERATE_SUCCESS;
}

OPERATE_STATUS dl_read_ref_info(char *part_name, uint16_t size, uint64_t offset,
	uchar *receive_buf, uchar  *transmit_buf)
{}

OPERATE_STATUS dl_download_flush_data(uint32_t total_len, unsigned char *total_buf,
						uint16_t size, unsigned char *buf)
{
	unsigned char *pdata = (unsigned char *)total_buf;
	unsigned char hash[32];
	unsigned char Cnt;

	if (0x20 != size)
		return OPERATE_INVALID_SIZE;

	sha256_csum_wd((const unsigned char*)pdata, (uint32_t)total_len, hash, 0);

	if (memcmp(hash, buf, 32))
		return OPERATE_CHECKSUM_DIFF;

	return OPERATE_SUCCESS;
}

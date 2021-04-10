/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <common.h>
#include <exports.h>

#include <nand.h>
#include <onenand_uboot.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <asm/errno.h>
#include <jffs2/load_kernel.h>
#include "dl_ubi.h"


struct ubi_selected_dev cur_ubi={0,-1,NULL};

static int verify_mkvol_req(const struct ubi_device *ubi,
			    const struct ubi_mkvol_req *req)
{
	int n, err = -EINVAL;

	if (req->bytes < 0 || req->alignment < 0 || req->vol_type < 0 ||
	    req->name_len < 0)
		goto bad;

	if ((req->vol_id < 0 || req->vol_id >= ubi->vtbl_slots) &&
	    req->vol_id != UBI_VOL_NUM_AUTO)
		goto bad;

	if (req->alignment == 0)
		goto bad;

	if (req->bytes == 0)
		goto bad;

	if (req->vol_type != UBI_DYNAMIC_VOLUME &&
	    req->vol_type != UBI_STATIC_VOLUME)
		goto bad;

	if (req->alignment > ubi->leb_size)
		goto bad;

	n = req->alignment % ubi->min_io_size;
	if (req->alignment != 1 && n)
		goto bad;

	if (req->name_len > UBI_VOL_NAME_MAX) {
		err = -ENAMETOOLONG;
		goto bad;
	}

	return 0;
bad:
	printf("bad volume creation request");
	return err;
}

int fdl_ubi_create_vol(struct ubi_device *ubi, char *volume, int *vol_id, long long size, int dynamic)
{
	struct ubi_mkvol_req req;
	int err;

	if (dynamic)
		req.vol_type = UBI_DYNAMIC_VOLUME;
	else
		req.vol_type = UBI_STATIC_VOLUME;

	req.vol_id = UBI_VOL_NUM_AUTO;
	req.alignment = 1;
	req.bytes = size;

	strcpy(req.name, volume);
	req.name_len = strlen(volume);
	req.name[req.name_len] = '\0';
	req.padding1 = 0;
	/* It's duplicated at drivers/mtd/ubi/cdev.c */
	err = verify_mkvol_req(ubi, &req);
	if (err) {
		printf("verify_mkvol_req failed %d\n", err);
		return err;
	}
	printf("Creating %s volume %s of size 0x%llx\n",
		dynamic ? "dynamic" : "static", volume, size);
	/* Call real ubi create volume */
	err = ubi_create_volume(ubi, &req);
	if(err){
		printf("Creat volume err %d\n",err);
	}
	*vol_id = req.vol_id;
	return err;
}

int fdl_ubi_remove_vol(struct ubi_device *ubi, char *volume)
{
	int i, err, reserved_pebs;
	int found = 0, vol_id = 0;
	struct ubi_volume *vol = NULL;

	for (i = 0; i < ubi->vtbl_slots; i++) {
		vol = ubi->volumes[i];
		if (vol && !strcmp(vol->name, volume)) {
			printf("Volume %s found at valid %d\n", volume, i);
			vol_id = i;
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("%s volume not found\n", volume);
		return -ENODEV;
	}
	printf("remove UBI volume %s (id %d)\n", vol->name, vol->vol_id);

	if (ubi->ro_mode) {
		printf("It's read-only mode\n");
		err = -EROFS;
		goto out_err;
	}

	err = ubi_change_vtbl_record(ubi, vol_id, NULL);
	if (err) {
		printf("Error changing Vol tabel record err=%x\n", err);
		goto out_err;
	}
	reserved_pebs = vol->reserved_pebs;
	for (i = 0; i < vol->reserved_pebs; i++) {
		err = ubi_eba_unmap_leb(ubi, vol, i);
		if (err)
			goto out_err;
	}

	kfree(vol->eba_tbl);
	ubi->volumes[vol_id]->eba_tbl = NULL;
	ubi->volumes[vol_id] = NULL;

	ubi->rsvd_pebs -= reserved_pebs;
	ubi->avail_pebs += reserved_pebs;
	i = ubi->beb_rsvd_level - ubi->beb_rsvd_pebs;
	if (i > 0) {
		i = ubi->avail_pebs >= i ? i : ubi->avail_pebs;
		ubi->avail_pebs -= i;
		ubi->rsvd_pebs += i;
		ubi->beb_rsvd_pebs += i;
		if (i > 0)
			ubi_msg("reserve more %d PEBs", i);
	}
	ubi->vol_count -= 1;

	return 0;
out_err:
	ubi_err("cannot remove volume %d, error %d", vol_id, err);
	return err;
}

int fdl_ubi_volume_write(struct ubi_device *ubi, char *volume, void *buf, size_t size)
{
	int i = 0, err = -1;
	int found = 0;
	struct ubi_volume *vol;

	for (i = 0; i < ubi->vtbl_slots; i++) {
		vol = ubi->volumes[i];
		if (vol && !strcmp(vol->name, volume)) {
			printf("Volume \"%s\" found at volume id %d\n", volume, i);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("%s volume not found\n", volume);
		return 1;
	}
	
	err = ubi_more_update_data(ubi, vol, buf, size);
	if (err < 0) {
		printf("Couldnt or partially wrote data \n");
		return err;
	}

	if (err) {
		size = err;

		err = ubi_check_volume(ubi, vol->vol_id);
		if ( err < 0 )
			return err;

		if (err) {
			ubi_warn("volume %d on UBI device %d is corrupted",
					vol->vol_id, ubi->ubi_num);
			vol->corrupted = 1;
		}

		vol->checked = 1;
		ubi_gluebi_updated(vol);
	}

	return 0;
}

int fdl_ubi_volume_read(struct ubi_device *ubi, char *volume, char *buf, size_t size, size_t offset)
{
	int err, lnum, off, len, tbuf_size, i = 0;
	size_t count_save = size;
	void *tbuf;
	unsigned long long tmp;
	struct ubi_volume *vol = NULL;
	loff_t offp = offset;

	for (i = 0; i < ubi->vtbl_slots; i++) {
		vol = ubi->volumes[i];
		if (vol && !strcmp(vol->name, volume)) {
			printf("Volume %s found at volume id %d\n",
				volume, vol->vol_id);
			break;
		}
	}
	if (i == ubi->vtbl_slots) {
		printf("%s volume not found\n", volume);
		return -ENODEV;
	}

	printf("read %i bytes from volume %d offset 0x%x to %x(buf address)\n",
	       (int) size, vol->vol_id, offset, (unsigned)buf);

	if (vol->updating) {
		printf("updating");
		return -EBUSY;
	}
	if (vol->upd_marker) {
		printf("damaged volume, update marker is set");
		return -EBADF;
	}
	if (offp == vol->used_bytes) {
		printf("offset=used_bytes,nothing to read\n");
		return 0;
	}

	if (size == 0) {
		printf("Read [%lu] bytes\n", (unsigned long) vol->used_bytes);
		size = vol->used_bytes;
	}

	if (vol->corrupted)
		printf("read from corrupted volume %d", vol->vol_id);
	if (offp + size > vol->used_bytes)
		count_save = size = vol->used_bytes - offp;

	tbuf_size = vol->usable_leb_size;
	if (size < tbuf_size)
		tbuf_size = ALIGN(size, ubi->min_io_size);
	tbuf = malloc(tbuf_size);
	if (!tbuf) {
		printf("NO MEM\n");
		return -ENOMEM;
	}
	len = size > tbuf_size ? tbuf_size : size;

	tmp = offp;
	off = do_div(tmp, vol->usable_leb_size);
	lnum = tmp;
	do {
		if (off + len >= vol->usable_leb_size)
			len = vol->usable_leb_size - off;
		printf("before ubi_eba_read_leb lnum=0x%x, tbuf=%p, off=0x%x, len=0x%x\n", lnum, tbuf, off, len);
		err = ubi_eba_read_leb(ubi, vol, lnum, tbuf, off, len, 0);
		if (err) {
			printf("read err %x\n", err);
			break;
		}
		off += len;
		if (off == vol->usable_leb_size) {
			lnum += 1;
			off -= vol->usable_leb_size;
		}

		size -= len;
		offp += len;

		memcpy(buf, tbuf, len);

		buf += len;
		len = size > tbuf_size ? tbuf_size : size;
	} while (size);

	free(tbuf);
	return err ? err : count_save - size;
}

/**
	attach ubi device to given mtdpart, and return the new
	ubi device num.
*/
int fdl_ubi_dev_attach(const char *mtdpart)
{
	struct mtd_device *dev;
	struct part_info *part;
	struct mtd_info *mtd;
	struct mtd_partition mtd_part;
	char mtd_dev[16];
	u8 pnum;
	int ret;

	ret = find_dev_and_part(mtdpart, &dev, &pnum, &part);
	if(ret){
		printf("--->main partition %s miss<---\n",mtdpart);
		return -1;
	}
	if(dev->id->type != MTD_DEV_TYPE_NAND){
		printf("mtd dev %s not a nand device!\n",mtdpart);
		return -1;
	}
	sprintf(mtd_dev, "%s%d", MTD_DEV_TYPE(dev->id->type), dev->id->num);
	mtd = get_mtd_device_nm(mtd_dev);

	memset(&mtd_part, 0, sizeof(mtd_part));
	mtd_part.name = mtdpart;
	mtd_part.size = part->size;
	mtd_part.offset = part->offset;
	add_mtd_partitions(mtd, &mtd_part, 1);
	mtd = get_mtd_device_nm(mtdpart);
	ret = ubi_attach_mtd_dev(mtd, UBI_DEV_NUM_AUTO, 0,CONFIG_MTD_UBI_BEB_LIMIT);
	if(ret<0){
		printf("--->ubi attach mtd %s failed<---\n",mtdpart);
	}
	return ret;
}

/**
 * init mtd ubi module and attach the UBIPAC part to ubi device.
 *
 * Returns 1 in case of success and 0 in case of failure.
 */

int fdl_ubi_dev_init(void)
{
	int ret;
	if(cur_ubi.ubi_initialized){
		ubi_detach_mtd_dev(cur_ubi.dev_num, 1);
		cur_ubi.dev_num = fdl_ubi_dev_attach(UBIPAC_PART);
	}else{
		cur_ubi.dev_num = nand_ubi_dev_init();
	}
	cur_ubi.ubi_initialized =1;
	if(cur_ubi.dev_num<0){
		printf("%s:ubi dev attach failure!\n",__FUNCTION__);
		return 0;
	}
	cur_ubi.dev = ubi_get_device(cur_ubi.dev_num);
	if(!cur_ubi.dev){
		printf("%s:ubi get device failure!\n",__FUNCTION__);
		return 0;
	}

	return 1;
}

/**
 * autoresize - re-size the volume to max.
 * @ubi: UBI device description object
 * @vol_id: ID of the volume to re-size
 *
 * Returns zero in case of success and a
 * negative error code in case of failure.
 */
int fdl_ubi_volume_autoresize(struct ubi_device *ubi, int vol_id)
{
	struct ubi_volume_desc desc;
	struct ubi_volume *vol = ubi->volumes[vol_id];
	int err, old_reserved_pebs = vol->reserved_pebs;

	desc.vol = vol;
	err = ubi_resize_volume(&desc,
			(old_reserved_pebs + ubi->avail_pebs));
	if (err){
		printf("cannot auto-resize volume %d\n", vol_id);
		return err;
	}

	printf("volume %d (\"%s\") re-sized from %d to %d LEBs\n", vol_id,
		vol->name, old_reserved_pebs, vol->reserved_pebs);
	return 0;
}

/**
 * fdl_ubi_volume_start_update - prepare volume update.
 * @ubi: UBI device description object
 * @volume: volume description object
 * @size: update bytes
 *
 * This function starts volume update operation. If @size is zero, the volume
 * is just wiped out. Returns zero in case of success and a negative error code
 * in case of failure.
 */
int fdl_ubi_volume_start_update(struct ubi_device *ubi, char *volume, size_t size)
{
	int i = 0, err = -1;
	int rsvd_bytes = 0;
	int found = 0;
	struct ubi_volume *vol;

	for (i = 0; i < ubi->vtbl_slots; i++) {
		vol = ubi->volumes[i];
		if (vol && !strcmp(vol->name, volume)) {
			printf("Volume \"%s\" found at volume id %d\n", volume, i);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("%s volume not found\n", volume);
		return 1;
	}
	rsvd_bytes = vol->reserved_pebs * (ubi->leb_size - vol->data_pad);
	if (size < 0 || size > rsvd_bytes) {
		printf("rsvd_bytes=%d vol->reserved_pebs=%d ubi->leb_size=%d\n",
		     rsvd_bytes, vol->reserved_pebs, ubi->leb_size);
		printf("vol->data_pad=%d\n", vol->data_pad);
		printf("Size > volume size !!\n");
		return 1;
	}

	err = ubi_start_update(ubi, vol, size);
	if (err < 0) {
		printf("Cannot start volume update\n");
		return err;
	}

	return 0;
}


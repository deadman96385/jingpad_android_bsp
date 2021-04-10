
//#include <linux/module.h>
#include <linux/types.h>
//#include <linux/init.h>
//#include <linux/kernel.h>
#include <linux/err.h>
//#include <linux/slab.h>

#include <linux/string.h>
#include <linux/bitops.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>

#include "nfc_base.h"
#include <nand.h>
#include <common.h>

nand_info_t nand_info[CONFIG_SYS_MAX_NAND_DEVICE];

const char *part_probes[] = { "cmdlinepart", NULL };

#define STATIC_FUNC

#ifdef CONFIG_DEBUG_FS
void nfc_add_debugfs(NFC_BASE_T * this);
#endif

STATIC_FUNC struct mtd_info sprd_mtd;

// resource1:
STATIC_FUNC int _init_device(NFC_BASE_T * this)
{
	
}

//used by yaffs only .
STATIC_FUNC int nand_do_write_ops(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops)
{
	//we do not need yaffs ,so currently, it is not  realized.
	return 0;	
}

STATIC_FUNC int _get_device(NFC_BASE_T * this, int new_state)
{
	
}

STATIC_FUNC void _put_device(NFC_BASE_T * this, char *callName, int ret)
{

}

STATIC_FUNC void _init_param(NFC_BASE_T * this)
{
	this->pageMsk = (1 << this->pageShift) - 1;
	this->blkMsk = (1 << this->blkShift) - 1;
	this->pagePerBuf = (1 << (this->bufShift - this->pageShift));
	this->pagePerMtd = (1 << (this->chipShift - this->pageShift)) * this->chipNum;
}

#define _set_bbt(x) {this->bbt[(x)>>5] |= (1<<((x)-(((x)>>5)<<5)));}
#define _is_bbt(x) (!!(this->bbt[(x)>>5] & (1<<((x)-(((x)>>5)<<5)))))
STATIC_FUNC int _init_bbt(NFC_BASE_T * this)
{
	uint32_t blk, cnt, bbt_size;
	int ret;

	cnt = (1 << (this->chipShift - this->blkShift)) * this->chipNum;
	bbt_size = (cnt >> 5) << 2;
	this->bbt = kmalloc(bbt_size, GFP_KERNEL);
	memset(this->bbt, 0, bbt_size);
	printk("nand:cnt %d,bbt_size %d,chipshift %d,blkshift %d,chipnum %d\n",
			cnt, bbt_size, this->chipShift,
			this->blkShift, this->chipNum);
	for (blk = 0; blk < cnt; blk++) {
		ret = this->_nand_isBadBlk(this,
				blk << (this->blkShift - this->pageShift));
		if (0 > ret) {
			printk(KERN_ERR "nand:init bbt err..\n");
			kfree(this->bbt);
			this->bbt = 0;
			return ret;
		} else if (ret) {
			_set_bbt(blk);
			printk(KERN_ERR "nand:blk %d, blkpage %d is bad block.\n",
				blk, blk << (this->blkShift - this->pageShift));
		}
	}
	return ret;
}

#define __checkRet(tmpRet){\
		if(-EUCLEAN == tmpRet){ret = -EUCLEAN;}\
		else if(0 > tmpRet){ret = tmpRet; return ret;}\
}

STATIC_FUNC int _nand_read_oob(struct mtd_info *mtd, NFC_BASE_T *this, loff_t from,
		struct mtd_oob_ops *ops, struct mtd_ecc_stats *ecc_stats)
{
	int ret = 0, tmpRet = 0;
	uint32_t pageS, pageE, pageNum, pagePerBuf, remainPageInfBuf, retNum, i;
	struct mtd_ecc_stats stats;
	uint32_t readLen;
	uint32_t oobReadLen;
	uint32_t maxOobReadLen;
	uint8_t *mBuf, *oobBuf, *sBuf_v;
	uint32_t toread_m, toread_s, col;
	stats = mtd->ecc_stats;
	ops->retlen = 0;
	ops->oobretlen = 0;
//---
	readLen = ops->len;
	oobReadLen = ops->ooblen;
	if (MTD_OPS_AUTO_OOB == ops->mode) {
		maxOobReadLen = this->layout.oobavail;
	} else {		//pass
		maxOobReadLen = this->oobSize;
	}
	mBuf = ops->datbuf;
	oobBuf = ops->oobbuf;
	col = from & this->pageMsk;
//---
	pagePerBuf = this->pagePerBuf;
	pageS = from >> this->pageShift;

	if (mBuf) {		//pass
		if (!readLen) {
			return 0;
		}
		if ((oobBuf) && (maxOobReadLen <= ops->ooboffs)) {
			return -EINVAL;
		}
		pageE = ((from + readLen - 1) >> this->pageShift);
		pageNum = pageE - pageS + 1;
	} else if (oobBuf) {
		if (((maxOobReadLen) && (maxOobReadLen <= ops->ooboffs))
		    || ((!maxOobReadLen) && (0 < ops->ooboffs))
		    ) {
			return -EINVAL;
		}
		if (!oobReadLen) {
			return 0;
		}
		pageNum = oobReadLen / (maxOobReadLen - ops->ooboffs);
		if (oobReadLen % (maxOobReadLen - ops->ooboffs)) {
			pageNum++;
		}
	} else {
		return -EINVAL;
	}
//---
// check param
	if ((pageS + pageNum) > this->pagePerMtd) {
		return -EINVAL;
	}
//---
	remainPageInfBuf = (pagePerBuf - (pageS & (pagePerBuf - 1)));
	if (remainPageInfBuf >= pageNum) {	//pass
		tmpRet = this->_readPageInBlk(this, pageS, pageNum, &retNum, (uint32_t) (! !ops->datbuf), (uint32_t) (! !ops->oobbuf), ops->mode, ecc_stats);
		__checkRet(tmpRet);
		if (mBuf) {	//pass
			memcpy(mBuf, this->mBuf_v + col, readLen);
			ops->retlen = readLen;
		}
		if (oobBuf) {
			sBuf_v = this->sBuf_v;
			for (i = 0; i < pageNum; i++) {
				toread_s = min(maxOobReadLen - ops->ooboffs, oobReadLen);
				memcpy(oobBuf, sBuf_v + ops->ooboffs, toread_s);
				oobBuf += toread_s;
				oobReadLen -= toread_s;
				sBuf_v += maxOobReadLen;
			}
			ops->oobretlen = ops->ooblen - oobReadLen;
		}
		return ret;
	} else {		//pass
		tmpRet =
		    this->_readPageInBlk(this, pageS, remainPageInfBuf,
					 &retNum, (uint32_t) (! !ops->datbuf), (uint32_t) (! !ops->oobbuf), ops->mode, ecc_stats);
		__checkRet(tmpRet);
		if (mBuf) {
			toread_m = ((remainPageInfBuf << this->pageShift) - col);
			memcpy(mBuf, this->mBuf_v + col, toread_m);
			mBuf += toread_m;
			readLen -= toread_m;
			col = 0;
			ops->retlen += toread_m;
		}
		if (oobBuf) {
			sBuf_v = this->sBuf_v;
			for (i = 0; i < remainPageInfBuf; i++) {
				toread_s = min(maxOobReadLen - ops->ooboffs, oobReadLen);
				memcpy(oobBuf, sBuf_v + ops->ooboffs, toread_s);
				oobBuf += toread_s;
				sBuf_v += maxOobReadLen;
				oobReadLen -= toread_s;
			}
			ops->oobretlen = ops->ooblen - oobReadLen;
		}
		pageS += remainPageInfBuf;
		pageNum -= remainPageInfBuf;
	}

	while (pageNum >= pagePerBuf) {	//pass
		tmpRet = this->_readPageInBlk(this, pageS, pagePerBuf, &retNum, (uint32_t) (! !ops->datbuf), (uint32_t) (! !ops->oobbuf), ops->mode, ecc_stats);
		__checkRet(tmpRet);
		if (mBuf) {
			toread_m = min(readLen, (pagePerBuf << this->pageShift));
			memcpy(mBuf, this->mBuf_v, toread_m);
			mBuf += toread_m;
			readLen -= toread_m;
			ops->retlen += toread_m;
		}
		if (oobBuf) {
			sBuf_v = this->sBuf_v;
			for (i = 0; i < pagePerBuf; i++) {
				toread_s = min(maxOobReadLen - ops->ooboffs, oobReadLen);
				memcpy(oobBuf, sBuf_v + ops->ooboffs, toread_s);
				oobBuf += toread_s;
				sBuf_v += maxOobReadLen;
				oobReadLen -= toread_s;
			}
			ops->oobretlen = ops->ooblen - oobReadLen;
		}
		pageS += pagePerBuf;
		pageNum -= pagePerBuf;
	}
	if (pageNum) {		//pass
		tmpRet = this->_readPageInBlk(this, pageS, pageNum, &retNum, (uint32_t) (! !ops->datbuf), (uint32_t) (! !ops->oobbuf), ops->mode, ecc_stats);
		__checkRet(tmpRet);
		if (mBuf) {
			toread_m = readLen;
			memcpy(mBuf, this->mBuf_v, toread_m);
			mBuf += toread_m;
			readLen -= toread_m;
			ops->retlen += toread_m;
		}
		if (oobBuf) {
			sBuf_v = this->sBuf_v;
			for (i = 0; i < pageNum; i++) {
				toread_s = min(maxOobReadLen - ops->ooboffs, oobReadLen);
				memcpy(oobBuf, sBuf_v + ops->ooboffs, toread_s);
				oobBuf += toread_s;
				sBuf_v += maxOobReadLen;
				oobReadLen -= toread_s;
			}
			ops->oobretlen = ops->ooblen - oobReadLen;
		}
	}
	if (mtd->ecc_stats.failed - stats.failed)
		return -EBADMSG;

	return ret;
}

STATIC_FUNC int _nand_write_oob(NFC_BASE_T * this, loff_t to, struct mtd_oob_ops *ops)
{
	int ret = 0;
	uint32_t pageS, pageE, pageNum, pagePerBuf, remainPageInfBuf, retNum, i;

	uint32_t readLen;
	uint32_t oobReadLen;
	uint32_t maxOobReadLen;
	uint8_t *mBuf, *oobBuf, *sBuf_v;
	uint32_t toread_m, toread_s, col;

	ops->retlen = 0;
	ops->oobretlen = 0;
//---
	readLen = ops->len;
	oobReadLen = ops->ooblen;
	if (MTD_OPS_AUTO_OOB == ops->mode) {
		maxOobReadLen = this->layout.oobavail;
	} else {
		maxOobReadLen = this->oobSize;
	}
	mBuf = ops->datbuf;
	oobBuf = ops->oobbuf;
	sBuf_v = this->sBuf_v;
	col = to & this->pageMsk;
//---
	pagePerBuf = this->pagePerBuf;
	pageS = to >> this->pageShift;

	if (mBuf) {		//pass
		if (!readLen) {
			return 0;
		}
		if ((oobBuf) && (maxOobReadLen <= ops->ooboffs)) {
			return -EINVAL;
		}
		pageE = ((to + readLen - 1) >> this->pageShift);
		pageNum = pageE - pageS + 1;
	} else if (oobBuf) {
		if (((maxOobReadLen) && (maxOobReadLen <= ops->ooboffs))
		    || ((!maxOobReadLen) && (0 < ops->ooboffs))
		    || (maxOobReadLen < (ops->ooboffs + oobReadLen))
		    ) {
			return -EINVAL;
		}
		if (!oobReadLen) {
			return 0;
		}
		pageNum = oobReadLen / (maxOobReadLen - ops->ooboffs);
		if (oobReadLen % (maxOobReadLen - ops->ooboffs)) {
			pageNum++;
		}
	} else {
		return -EINVAL;
	}
//---
// check param
	if ((pageS + pageNum) > this->pagePerMtd) {
		return -EINVAL;
	}
//---
	if ((!mBuf) && (MTD_OPS_RAW != ops->mode)) {
		memset(this->mBuf_v, 0xFF, (min(pagePerBuf, pageNum)) << this->pageShift);
	}
	if ((!oobBuf) && (MTD_OPS_RAW != ops->mode)) {
		memset(this->sBuf_v, 0xFF, (min(pagePerBuf, pageNum)) * this->oobSize);
	}
//---
	remainPageInfBuf = (pagePerBuf - (pageS & (pagePerBuf - 1)));
	if (remainPageInfBuf >= pageNum) {
		if (mBuf) {	//pass
			memset(this->mBuf_v, 0xFF, col);
			memcpy(this->mBuf_v + col, mBuf, readLen);
			if ((col + readLen) & this->pageMsk) {
				memset(this->mBuf_v + col + readLen, 0xFF, ((1 << this->pageShift) - ((col + readLen) & this->pageMsk)));
			}
		}
		if (oobBuf) {
			sBuf_v = this->sBuf_v;
			for (i = 0; i < pageNum; i++) {
				toread_s = min(maxOobReadLen - ops->ooboffs, oobReadLen);
				memset(sBuf_v, 0xFF, ops->ooboffs);
				memcpy(sBuf_v + ops->ooboffs, oobBuf, toread_s);
				memset(sBuf_v + ops->ooboffs + toread_s, 0xFF, maxOobReadLen - ops->ooboffs - toread_s);
				oobBuf += toread_s;
				oobReadLen -= toread_s;
				sBuf_v += maxOobReadLen;
			}
		}
		ret = this->_writePageInBlk(this, pageS, pageNum, &retNum, (uint32_t) (! !ops->datbuf), (uint32_t) (! !ops->oobbuf), ops->mode);
		if (0 == ret) {
			if (ops->datbuf) {
				ops->retlen = readLen;
			}
			if (ops->oobbuf) {
				ops->oobretlen = ops->ooblen - oobReadLen;
			}
		}
		return ret;
	} else {
		if (mBuf) {	//pass
			toread_m = ((remainPageInfBuf << this->pageShift) - col);
			memset(this->mBuf_v, 0xFF, col);
			memcpy(this->mBuf_v + col, mBuf, toread_m);
			mBuf += toread_m;
			readLen -= toread_m;
			col = 0;
		}
		if (oobBuf) {
			sBuf_v = this->sBuf_v;
			for (i = 0; i < remainPageInfBuf; i++) {
				toread_s = min(maxOobReadLen - ops->ooboffs, oobReadLen);
				memset(sBuf_v, 0xFF, ops->ooboffs);
				memcpy(sBuf_v + ops->ooboffs, oobBuf, toread_s);
				memset(sBuf_v + ops->ooboffs + toread_s, 0xFF, maxOobReadLen - ops->ooboffs - toread_s);
				oobBuf += toread_s;
				sBuf_v += maxOobReadLen;
				oobReadLen -= toread_s;
			}
		}
		ret = this->_writePageInBlk(this, pageS, remainPageInfBuf, &retNum, (uint32_t) (! !ops->datbuf), (uint32_t) (! !ops->oobbuf), ops->mode);
		if (0 > ret) {
			return ret;
		}
		if (0 == ret) {
			if (ops->datbuf) {
				ops->retlen += toread_m;
			}
			if (ops->oobbuf) {
				ops->oobretlen = ops->ooblen - oobReadLen;
			}
		}

		pageS += remainPageInfBuf;
		pageNum -= remainPageInfBuf;
	}

	while (pageNum >= pagePerBuf) {
		if (mBuf) {	//pass
			toread_m = min(readLen, (pagePerBuf << this->pageShift));
			memcpy(this->mBuf_v, mBuf, toread_m);
			mBuf += toread_m;
			readLen -= toread_m;
		}
		if (oobBuf) {
			sBuf_v = this->sBuf_v;
			for (i = 0; i < pagePerBuf; i++) {
				toread_s = min(maxOobReadLen - ops->ooboffs, oobReadLen);
				memset(sBuf_v, 0xFF, ops->ooboffs);
				memcpy(sBuf_v + ops->ooboffs, oobBuf, toread_s);
				memset(sBuf_v + ops->ooboffs + toread_s, 0xFF, maxOobReadLen - ops->ooboffs - toread_s);
				oobBuf += toread_s;
				sBuf_v += maxOobReadLen;
				oobReadLen -= toread_s;
			}
		}
		ret = this->_writePageInBlk(this, pageS, pagePerBuf, &retNum, (uint32_t) (! !ops->datbuf), (uint32_t) (! !ops->oobbuf), ops->mode);
		if (0 > ret) {
			return ret;
		}
		if (0 == ret) {
			if (ops->datbuf) {
				ops->retlen += toread_m;
			}
			if (ops->oobbuf) {
				ops->oobretlen = ops->ooblen - oobReadLen;
			}
		}
		pageS += pagePerBuf;
		pageNum -= pagePerBuf;
	}
	if (pageNum) {
		if (mBuf) {	//pass
			toread_m = readLen;
			memcpy(this->mBuf_v, mBuf, toread_m);
			if (toread_m & this->pageMsk) {
				memset(this->mBuf_v + toread_m, 0xFF, ((1 << this->pageShift) - (toread_m & this->pageMsk)));
			}
			mBuf += toread_m;
			readLen -= toread_m;
		}
		if (oobBuf) {
			sBuf_v = this->sBuf_v;
			for (i = 0; i < pageNum; i++) {
				toread_s = min(maxOobReadLen - ops->ooboffs, oobReadLen);
				memset(sBuf_v, 0xFF, ops->ooboffs);
				memcpy(sBuf_v + ops->ooboffs, oobBuf, toread_s);
				memset(sBuf_v + ops->ooboffs + toread_s, 0xFF, maxOobReadLen - ops->ooboffs - toread_s);
				oobBuf += toread_s;
				sBuf_v += maxOobReadLen;
				oobReadLen -= toread_s;
			}
		}
		ret = this->_writePageInBlk(this, pageS, pageNum, &retNum, (uint32_t) (! !ops->datbuf), (uint32_t) (! !ops->oobbuf), ops->mode);
		if (0 > ret) {
			return ret;
		}
		if (0 == ret) {
			if (ops->datbuf) {
				ops->retlen += toread_m;
			}
			if (ops->oobbuf) {
				ops->oobretlen = ops->ooblen - oobReadLen;
			}
		}
	}
	return ret;
}

STATIC_FUNC int callback_block_isbad(struct mtd_info *mtd, loff_t ofs)
{
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	int ret;

	_get_device(this, FL_READING);
	ret = _is_bbt(ofs >> this->blkShift);
	_put_device(this, __FILE__, ret);
	return ret;
}

STATIC_FUNC int callback_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	int ret;
	uint32_t page;

	if (_is_bbt(ofs >> this->blkShift)) {
		return 0;
	}

	page = ((ofs >> this->blkShift) << (this->blkShift - this->pageShift));

	_get_device(this, FL_ERASING);
	ret = this->_nand_eraseBlk(this, page);
	_put_device(this, __FILE__, ret);

	_get_device(this, FL_WRITING);
	ret = this->_nand_markBadBlk(this, page);
	_put_device(this, __FILE__, ret);

	_set_bbt(ofs >> this->blkShift);

	return ret;
}

STATIC_FUNC int callback_read(struct mtd_info *mtd, loff_t from, size_t len, size_t * retlen, u_char * buf)
{
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	int ret;
	struct mtd_oob_ops ops;
	memset(&ops, 0, sizeof(struct mtd_oob_ops));
	ops.mode = MTD_OPS_PLACE_OOB;
	ops.len = len;
	ops.datbuf = (uint8_t *) buf;
	ops.oobbuf = NULL;
	_get_device(this, FL_READING);
	ret = _nand_read_oob(mtd,this, from, &ops, &mtd->ecc_stats);
	*retlen = ops.retlen;
	_put_device(this, __FILE__, ret);
	return ret;
}

STATIC_FUNC int callback_write(struct mtd_info *mtd, loff_t to, size_t len, size_t * retlen, const u_char * buf)
{
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	int ret;
	struct mtd_oob_ops ops;

	memset(&ops, 0, sizeof(struct mtd_oob_ops));
	ops.mode = MTD_OPS_PLACE_OOB;
	ops.len = len;
	ops.datbuf = (uint8_t *) buf;
	ops.oobbuf = NULL;
	_get_device(this, FL_WRITING);
	ret = _nand_write_oob(this, to, &ops);
	*retlen = ops.retlen;
	_put_device(this, __FILE__, ret);
	return ret;
}

STATIC_FUNC int callback_read_oob(struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops)
{
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	int ret;

	_get_device(this, FL_READING);
	ret = _nand_read_oob(mtd,this, from, ops, &mtd->ecc_stats);
	_put_device(this, __FILE__, ret);

	return ret;
}

STATIC_FUNC int callback_write_oob(struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops)
{
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	int ret;

	_get_device(this, FL_WRITING);
	ret = _nand_write_oob(this, to, ops);
	_put_device(this, __FILE__, ret);

	return ret;
}

STATIC_FUNC int callback_erase(struct mtd_info *mtd, struct erase_info *instr)
{				// pass
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	int ret;
	uint32_t blkS, blkE, i;

	if ((instr->addr & this->blkMsk) || (instr->len & this->blkMsk)) {	// check whether addr and len is block align
		return -EINVAL;
	}

	_get_device(this, FL_ERASING);
	do {
		blkS = instr->addr >> this->blkShift;
		blkE = (instr->addr + instr->len - 1) >> this->blkShift;

		instr->state = MTD_ERASING;
		for (i = blkS; i <= blkE; i++) {
			if (_is_bbt(i) && (!this->allowEraseBadBlock)) {
				instr->state = MTD_ERASE_FAILED;
				break;
			}
			if (this->_nand_eraseBlk(this, i << (this->blkShift - this->pageShift))) {
				instr->fail_addr = (i << this->blkShift);
				instr->state = MTD_ERASE_FAILED;
				break;
			}
		}
		if (MTD_ERASING == instr->state) {
			instr->state = MTD_ERASE_DONE;
		}
	} while (0);
	ret = (instr->state == MTD_ERASE_DONE ? 0 : -EIO);
	_put_device(this, __FILE__, ret);

	if (!ret)
		mtd_erase_callback(instr);

	return ret;
}

STATIC_FUNC void callback_sync(struct mtd_info *mtd)
{				//checkeck
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	_get_device(this, FL_SYNCING);
	_put_device(this, __FILE__, 0);
}

STATIC_FUNC int callback_suspend(struct mtd_info *mtd)
{
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	_get_device(this, FL_PM_SUSPENDED);
	this->_ctrl_suspend(this);
	return 0;
}

STATIC_FUNC void callback_resume(struct mtd_info *mtd)
{
	NFC_BASE_T *this = (NFC_BASE_T *) mtd->priv;
	if (FL_PM_SUSPENDED == this->state) {
		this->_ctrl_resume(this);
		_put_device(this, __FILE__, 0);
	} else {
		printk(KERN_ERR "nfc_base: resume multi\n");
	}
}

STATIC_FUNC void _init_mtd(struct mtd_info *mtd, NFC_BASE_T * this)
{
	memset((char *)mtd, 0, sizeof(struct mtd_info));
    mtd->priv = this;
    mtd->type = MTD_NANDFLASH;
    mtd->flags = MTD_CAP_NANDFLASH;
    mtd->size = (1 << this->chipShift) * this->chipNum;
    mtd->erasesize = (1 << this->blkShift);
    mtd->writesize = (1 << this->pageShift);
    mtd->oobsize = this->oobSize;
    mtd->oobavail = this->layout.oobavail;
    mtd->name = "nand0";

    //	int index;
    mtd->ecclayout = &this->layout;

    //mtd->numeraseregions
    //mtd->eraseregions
    mtd->_erase = callback_erase;
   // mtd->_point = NULL;
  //  mtd->_unpoint = NULL;
    mtd->_read = callback_read;
    mtd->_write = callback_write;
    mtd->_panic_write = NULL;
	mtd->_read_oob = callback_read_oob;
	mtd->_write_oob = callback_write_oob;
	mtd->_get_fact_prot_info = NULL;
	mtd->_read_fact_prot_reg = NULL;
	mtd->_get_user_prot_info = NULL;
	mtd->_read_user_prot_reg = NULL;
	mtd->_write_user_prot_reg = NULL;
	mtd->_lock_user_prot_reg = NULL;
    mtd->_sync = callback_sync;
    mtd->_lock = NULL;
    mtd->_unlock = NULL;
    mtd->_block_isbad = callback_block_isbad;
    mtd->_block_markbad = callback_block_markbad;

    mtd->ecc_stats;
    mtd->subpage_sft = 0;

    mtd->owner = THIS_MODULE;
    mtd->usecount ;
    mtd->_get_device = NULL;
    mtd->_put_device = NULL;

}

int nfc_base_register(NFC_BASE_T * this)
{
	_init_device(this);
	_init_param(this);
	_init_bbt(this);
	_init_mtd(&sprd_mtd, this);
#ifdef CONFIG_DEBUG_FS
	nfc_add_debugfs(this);
#endif
	add_mtd_device(&sprd_mtd);
    memcpy((char *)nand_info,(char *)&sprd_mtd,sizeof(sprd_mtd));

	return 0;
}

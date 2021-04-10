#include <common.h>
#include <command.h>
#include <config.h>
#include <fat.h>
#include <asm/byteorder.h>
#include <errno.h>
#include <part.h>
#include <linux/ctype.h>
#include <malloc.h>

#define MAXU16   0xffff     /* maximum unsigned 16-bit quantity */
#define BPN      4          /* bits per nibble */
#define NPB      2          /* nibbles per byte */

#define DOSMAGIC  0xaa55    /* DOS magic number */
#define MINBPS    512       /* minimum bytes per sector */
#define MAXSPC    128       /* maximum sectors per cluster */
#define MAXNFT    16        /* maximum number of FATs */
#define DEFBLK    4096      /* default block size */
#define DEFBLK16  2048      /* default block size FAT16 */
#define DEFRDE    512       /* default root directory entries */
#define RESFTE    2         /* reserved FAT entries */
#define MINCLS12  1         /* minimum FAT12 clusters */
#define MINCLS16  0x1000    /* minimum FAT16 clusters */
#define MINCLS32  2         /* minimum FAT32 clusters */
#define MAXCLS12  0xfed     /* maximum FAT12 clusters */
#define MAXCLS16  0xfff5    /* maximum FAT16 clusters */
#define MAXCLS32  0xffffff5 /* maximum FAT32 clusters */

#define mincls(fat)  ((fat) == 12 ? MINCLS12 :    \
                      (fat) == 16 ? MINCLS16 :    \
                                        MINCLS32)

#define maxcls(fat)  ((fat) == 12 ? MAXCLS12 :    \
                      (fat) == 16 ? MAXCLS16 :    \
                                        MAXCLS32)

#define mk1(p, x)                           \
    (p) = (u_int8_t)(x)

#define mk2(p, x)                           \
    (p)[0] = (u_int8_t)(x),                 \
    (p)[1] = (u_int8_t)((x) >> 010)

#define mk4(p, x)                           \
    (p)[0] = (u_int8_t)(x),                 \
    (p)[1] = (u_int8_t)((x) >> 010),        \
    (p)[2] = (u_int8_t)((x) >> 020),        \
    (p)[3] = (u_int8_t)((x) >> 030)

#define powerof2(x) ((((x)-1)&(x))==0)
#define howmany(x, y) (((x)+((y)-1))/(y))
#define MAXPATHLEN 256

struct bs {
    u_int8_t jmp[3];        /* bootstrap entry point */
    u_int8_t oem[8];        /* OEM name and version */
};

struct bsbpb {
    u_int8_t bps[2];    /* bytes per sector */
    u_int8_t spc;       /* sectors per cluster */
    u_int8_t res[2];    /* reserved sectors */
    u_int8_t nft;       /* number of FATs */
    u_int8_t rde[2];    /* root directory entries */
    u_int8_t sec[2];    /* total sectors */
    u_int8_t mid;       /* media descriptor */
    u_int8_t spf[2];    /* sectors per FAT */
    u_int8_t spt[2];    /* sectors per track */
    u_int8_t hds[2];    /* drive heads */
    u_int8_t hid[4];    /* hidden sectors */
    u_int8_t bsec[4];   /* big total sectors */
};

struct bsxbpb {
    u_int8_t bspf[4];       /* big sectors per FAT */
    u_int8_t xflg[2];       /* FAT control flags */
    u_int8_t vers[2];       /* file system version */
    u_int8_t rdcl[4];       /* root directory start cluster */
    u_int8_t infs[2];       /* file system info sector */
    u_int8_t bkbs[2];       /* backup boot sector */
    u_int8_t rsvd[12];      /* reserved */
};

struct bsx {
    u_int8_t drv;           /* drive number */
    u_int8_t rsvd;          /* reserved */
    u_int8_t sig;           /* extended boot signature */
    u_int8_t volid[4];      /* volume ID number */
    u_int8_t label[11];     /* volume label */
    u_int8_t type[8];       /* file system type */
};

struct de {
    u_int8_t namext[11];    /* name and extension */
    u_int8_t attr;          /* attributes */
    u_int8_t rsvd[10];      /* reserved */
    u_int8_t time[2];       /* creation time */
    u_int8_t date[2];       /* creation date */
    u_int8_t clus[2];       /* starting cluster */
    u_int8_t size[4];       /* size */
};

struct bpb {
    u_int bps;          /* bytes per sector */
    u_int spc;          /* sectors per cluster */
    u_int res;          /* reserved sectors */
    u_int nft;          /* number of FATs */
    u_int rde;          /* root directory entries */
    u_int sec;          /* total sectors */
    u_int mid;          /* media descriptor */
    u_int spf;          /* sectors per FAT */
    u_int spt;          /* sectors per track */
    u_int hds;          /* drive heads */
    u_int hid;          /* hidden sectors */
    u_int bsec;         /* big total sectors */
    u_int bspf;         /* big sectors per FAT */
    u_int rdcl;         /* root directory start cluster */
    u_int infs;         /* file system info sector */
    u_int bkbs;         /* backup boot sector */
};

static const u_int8_t bootcode[] = {
    0xfa,               /* cli             */
    0x31, 0xc0,         /* xor    ax,ax    */
    0x8e, 0xd0,         /* mov    ss,ax    */
    0xbc, 0x00, 0x7c,   /* mov    sp,7c00h */
    0xfb,               /* sti             */
    0x8e, 0xd8,         /* mov    ds,ax    */
    0xe8, 0x00, 0x00,   /* call   $ + 3    */
    0x5e,               /* pop    si       */
    0x83, 0xc6, 0x19,   /* add    si,+19h  */
    0xbb, 0x07, 0x00,   /* mov    bx,0007h */
    0xfc,               /* cld             */
    0xac,               /* lodsb           */
    0x84, 0xc0,         /* test   al,al    */
    0x74, 0x06,         /* jz     $ + 8    */
    0xb4, 0x0e,         /* mov    ah,0eh   */
    0xcd, 0x10,         /* int    10h      */
    0xeb, 0xf5,         /* jmp    $ - 9    */
    0x30, 0xe4,         /* xor    ah,ah    */
    0xcd, 0x16,         /* int    16h      */
    0xcd, 0x19,         /* int    19h      */
    0x0d, 0x0a,
    'N', 'o', 'n', '-', 's', 'y', 's', 't',
    'e', 'm', ' ', 'd', 'i', 's', 'k',
    0x0d, 0x0a,
    'P', 'r', 'e', 's', 's', ' ', 'a', 'n',
    'y', ' ', 'k', 'e', 'y', ' ', 't', 'o',
    ' ', 'r', 'e', 'b', 'o', 'o', 't',
    0x0d, 0x0a,
    0
};

static void print_bpb(struct bpb *);
static void mklabel(u_int8_t *, const char *);
static void setstr(u_int8_t *, const char *, size_t);

/*
 * Construct a FAT12, FAT16, or FAT32 file system.
 */
int fat_format(void)
{
    const char *opt_O = NULL;
    u_int opt_F = 0, opt_b = 0, opt_c = 0;
    u_int opt_A = 0;
    char buf[MAXPATHLEN];
    struct bpb bpb;
    struct bs *bs;
    struct bsbpb *bsbpb;
    struct bsxbpb *bsxbpb;
    struct bsx *bsx;
    struct de *de;
    u_int8_t *img;
    ssize_t n;
    u_int fat, bss, rds, cls, dir, lsn, x, x1, x2;
    u_int extra_res, alignment=0, set_res, set_spf, set_spc, tempx, attempts=0;

	__u8 *block;
	boot_sector boot_sec;

	opt_A = 1;
    opt_F = 32;
    opt_O = "android";
    opt_c = 64;
    opt_b = 0;

	block = memalign(ARCH_DMA_MINALIGN, 512);
	if (block == NULL) {
		debug("Error: allocating block\n");
		return -1;
	}

	if (disk_read(0, 1, block) < 0) {
		debug("Error: reading block\n");
		free(block);
		return -1;
	}

	memcpy(&boot_sec, block, sizeof(boot_sector));
	memset(&bpb, 0, sizeof(bpb));
	free(block);

	bpb.bps = boot_sec.sector_size[1] << 8 + boot_sec.sector_size[0];
	bpb.spt = FAT2CPU16(boot_sec.secs_track);
	bpb.hds = FAT2CPU16(boot_sec.heads);
	bpb.bsec = FAT2CPU32(boot_sec.total_sect);

	if (bpb.bsec * bpb.bps <= (128*1024*1024LL)) {
		opt_F = 16;
        bpb.spc = 32;
	} else if (bpb.bsec * bpb.bps <= (2*1024*1024*1024LL)) {
		opt_F = 16;
        bpb.spc = 64;
	}

    off_t delta;
    delta = bpb.bsec % bpb.spt;
    if (delta != 0) {
       debug("trim %d sectors from %u to adjust to a multiple of %d",
          (int)delta, bpb.bsec, bpb.spt);
        bpb.bsec -= delta;
    }

    if (bpb.spc == 0) {    /* set defaults */
        if (bpb.bsec <= 6000)    /* about 3MB -> 512 bytes */
            bpb.spc = 1;
        else if (bpb.bsec <= (1<<17)) /* 64M -> 4k */
            bpb.spc = 8;
        else if (bpb.bsec <= (1<<19)) /* 256M -> 8k */
            bpb.spc = 16;
        else if (bpb.bsec <= (1<<22)) /* 2G -> 16k, some versions of windows
                                     require a minimum of 65527 clusters */
            bpb.spc = 32;
        else
            bpb.spc = 64;        /* otherwise 32k */
    }

	if (!powerof2(bpb.bps)) {
        debug("bytes/sector (%u) is not a power of 2", bpb.bps);
		goto error;
	}
    if (bpb.bps < MINBPS) {
        debug("bytes/sector (%u) is too small; minimum is %u",
             bpb.bps, MINBPS);
		goto error;
	}

    fat = opt_F;
    bss = 1;

    if (!bpb.nft)
        bpb.nft = 2;

    x = bss;
    if (fat == 32) {
        if (!bpb.infs) {
            if (x == MAXU16 || x == bpb.bkbs) {
                debug(1, "no room for info sector");
				goto error;
			}
            bpb.infs = x;
        }
        if (bpb.infs != MAXU16 && x <= bpb.infs)
            x = bpb.infs + 1;
        if (!bpb.bkbs) {
            if (x == MAXU16) {
                debug("no room for backup sector");
				goto error;
			}
            bpb.bkbs = x;
        } else if (bpb.bkbs != MAXU16 && bpb.bkbs == bpb.infs) {
            debug("backup sector would overwrite info sector");
			goto error;
		}
        if (bpb.bkbs != MAXU16 && x <= bpb.bkbs)
            x = bpb.bkbs + 1;
    }

    extra_res = 0;
    set_res = !bpb.res;
    set_spf = !bpb.bspf;
    set_spc = !bpb.spc;
    tempx = x;
    /*
     * Attempt to align if opt_A is set. This is done by increasing the number
     * of reserved blocks. This can cause other factors to change, which can in
     * turn change the alignment. This should take at most 2 iterations, as
     * increasing the reserved amount may cause the FAT size to decrease by 1,
     * requiring another nft reserved blocks. If spc changes, it will
     * be half of its previous size, and thus will not throw off alignment.
     */
    do {
        x = tempx;
        if (set_res)
            bpb.res = (fat == 32 ? max(x, max(16384 / bpb.bps, 4)) : x) + extra_res;
        else if (bpb.res < x) {
            debug("too few reserved sectors");
			goto error;
		}
        if (fat != 32 && !bpb.rde)
            bpb.rde = DEFRDE;
        rds = howmany(bpb.rde, bpb.bps / sizeof(struct de));
        if (set_spc)
            for (bpb.spc = howmany(fat == 16 ? DEFBLK16 : DEFBLK, bpb.bps);
                    bpb.spc < MAXSPC &&
                    bpb.res +
                    howmany((RESFTE + maxcls(fat)) * (fat / BPN),
                            bpb.bps * NPB) * bpb.nft +
                            rds +
                            (u_int64_t)(maxcls(fat) + 1) * bpb.spc <= bpb.bsec;
                    bpb.spc <<= 1);
        if (fat != 32 && bpb.bspf > MAXU16) {
            debug("too many sectors/FAT for FAT12/16");
			goto error;
		}
        x1 = bpb.res + rds;
        x = bpb.bspf ? bpb.bspf : 1;
        if (x1 + (u_int64_t)x * bpb.nft > bpb.bsec) {
            debug("meta data exceeds file system size");
			goto error;
		}
        x1 += x * bpb.nft;
        x = (u_int64_t)(bpb.bsec - x1) * bpb.bps * NPB /
                (bpb.spc * bpb.bps * NPB + fat / BPN * bpb.nft);
        x2 = howmany((RESFTE + min(x, maxcls(fat))) * (fat / BPN), bpb.bps * NPB);
        if (set_spf) {
            if (!bpb.bspf) {
                bpb.bspf = x2;
            }
            x1 += (bpb.bspf - 1) * bpb.nft;
        }
        if(set_res) {
            /* attempt to align root directory */
            alignment = (bpb.res + bpb.bspf * bpb.nft) % bpb.spc;
            extra_res += bpb.spc - alignment;
        }
        attempts++;
    } while(opt_A && alignment != 0 && attempts < 2);
    if (alignment != 0)
        debug("warning: Alignment failed.");

    cls = (bpb.bsec - x1) / bpb.spc;
    x = (u_int64_t)bpb.bspf * bpb.bps * NPB / (fat / BPN) - RESFTE;
    if (cls > x)
        cls = x;
    if (bpb.bspf < x2)
        debug("warning: sectors/FAT limits file system to %u clusters", cls);
    if (cls < mincls(fat)) {
        debug("%u clusters too few clusters for FAT%u, need %u", cls, fat, mincls(fat));
		goto error;
	}
	if (cls > maxcls(fat)) {
        cls = maxcls(fat);
        bpb.bsec = x1 + (cls + 1) * bpb.spc - 1;
        debug("warning: FAT type limits file system to %u sectors", bpb.bsec);
    }

    debug("%u sector%s in %u FAT%u cluster%s (%u bytes/cluster)\n",
           cls * bpb.spc, cls * bpb.spc == 1 ? "" : "s", cls, fat,
           cls == 1 ? "" : "s", bpb.bps * bpb.spc);
    if (!bpb.mid)
        bpb.mid = !bpb.hid ? 0xf0 : 0xf8;
    if (fat == 32)
        bpb.rdcl = RESFTE;
    if (bpb.hid + bpb.bsec <= MAXU16) {
        bpb.sec = bpb.bsec;
        bpb.bsec = 0;
    }
    if (fat != 32) {
        bpb.spf = bpb.bspf;
        bpb.bspf = 0;
    }
    print_bpb(&bpb);

    if (!(img = malloc(bpb.bps))) {
        debug("%u", bpb.bps);
		goto error;
	}
    dir = bpb.res + (bpb.spf ? bpb.spf : bpb.bspf) * bpb.nft;
    for (lsn = 0; lsn < dir + (fat == 32 ? bpb.spc : rds); lsn++) {
        x = lsn;

        memset(img, 0, bpb.bps);
        if (!lsn || (fat == 32 && bpb.bkbs != MAXU16 && lsn == bpb.bkbs)) {
            x1 = sizeof(struct bs);
            bsbpb = (struct bsbpb *)(img + x1);
            mk2(bsbpb->bps, bpb.bps);
            mk1(bsbpb->spc, bpb.spc);
            mk2(bsbpb->res, bpb.res);
            mk1(bsbpb->nft, bpb.nft);
            mk2(bsbpb->rde, bpb.rde);
            mk2(bsbpb->sec, bpb.sec);
            mk1(bsbpb->mid, bpb.mid);
            mk2(bsbpb->spf, bpb.spf);
            mk2(bsbpb->spt, bpb.spt);
            mk2(bsbpb->hds, bpb.hds);
            mk4(bsbpb->hid, bpb.hid);
            mk4(bsbpb->bsec, bpb.bsec);
            x1 += sizeof(struct bsbpb);
            if (fat == 32) {
                bsxbpb = (struct bsxbpb *)(img + x1);
                mk4(bsxbpb->bspf, bpb.bspf);
                mk2(bsxbpb->xflg, 0);
                mk2(bsxbpb->vers, 0);
                mk4(bsxbpb->rdcl, bpb.rdcl);
                mk2(bsxbpb->infs, bpb.infs);
                mk2(bsxbpb->bkbs, bpb.bkbs);
                x1 += sizeof(struct bsxbpb);
            }
            bsx = (struct bsx *)(img + x1);
            mk1(bsx->sig, 0x29);

            x = (((u_int)(1 + 10) << 8 |
                     (u_int)22) + (u_int)(1900 + 87));

            mk4(bsx->volid, x);
            mklabel(bsx->label, "NO NAME");
            sprintf(buf, "FAT%u", fat);
            setstr(bsx->type, buf, sizeof(bsx->type));

			x1 += sizeof(struct bsx);
            bs = (struct bs *)img;
            mk1(bs->jmp[0], 0xeb);
			mk1(bs->jmp[1], x1 - 2);
			mk1(bs->jmp[2], 0x90);
			setstr(bs->oem, opt_O ? opt_O : "BSD  4.4",
                            sizeof(bs->oem));
			memcpy(img + x1, bootcode, sizeof(bootcode));
			mk2(img + MINBPS - 2, DOSMAGIC);

        } else if (fat == 32 && bpb.infs != MAXU16 &&
                (lsn == bpb.infs || (bpb.bkbs != MAXU16 &&
                                lsn == bpb.bkbs + bpb.infs))) {
            mk4(img, 0x41615252);
            mk4(img + MINBPS - 28, 0x61417272);
            mk4(img + MINBPS - 24, 0xffffffff);
            mk4(img + MINBPS - 20, bpb.rdcl);
            mk2(img + MINBPS - 2, DOSMAGIC);
        } else if (lsn >= bpb.res && lsn < dir &&
                !((lsn - bpb.res) % (bpb.spf ? bpb.spf : bpb.bspf))) {
            mk1(img[0], bpb.mid);
            for (x = 1; x < fat * (fat == 32 ? 3 : 2) / 8; x++)
                mk1(img[x], fat == 32 && x % 4 == 3 ? 0x0f : 0xff);
         }

		 if ((n = disk_write(lsn, 1, img)) != 1) {
            debug("can't write sector %u, %d\n", lsn, n);
			free(img);
			goto error;
         }
     }
    return 0;

error:
	return -1;
}

/*
 * Print out BPB values.
 */
static void print_bpb(struct bpb *bpb)
{
    debug("bps=%u spc=%u res=%u nft=%u", bpb->bps, bpb->spc, bpb->res,
           bpb->nft);
    if (bpb->rde)
        debug(" rde=%u", bpb->rde);
    if (bpb->sec)
        debug(" sec=%u", bpb->sec);
    debug(" mid=%#x", bpb->mid);
    if (bpb->spf)
        debug(" spf=%u", bpb->spf);
    debug(" spt=%u hds=%u hid=%u", bpb->spt, bpb->hds, bpb->hid);
    if (bpb->bsec)
        debug(" bsec=%u", bpb->bsec);
    if (!bpb->spf) {
        debug(" bspf=%u rdcl=%u", bpb->bspf, bpb->rdcl);
        debug(" infs=");
        debug(bpb->infs == MAXU16 ? "%#x" : "%u", bpb->infs);
        debug(" bkbs=");
        debug(bpb->bkbs == MAXU16 ? "%#x" : "%u", bpb->bkbs);
    }
    debug("\n");
}

/*
 * Make a volume label.
 */
static void mklabel(u_int8_t *dest, const char *src)
{
    int c, i;

    for (i = 0; i < 11; i++) {
        c = *src ? toupper(*src++) : ' ';
        *dest++ = !i && c == '\xe5' ? 5 : c;
    }
}

/*
 * Copy string, padding with spaces.
 */
static void setstr(u_int8_t *dest, const char *src, size_t len)
{
    while (len--)
        *dest++ = *src ? *src++ : ' ';
}


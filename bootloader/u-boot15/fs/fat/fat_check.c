#include <common.h>
#include <config.h>
#include <exports.h>
#include <fat.h>
#include <asm/byteorder.h>
#include <part.h>
#include <malloc.h>
#include <linux/compiler.h>
#include <linux/ctype.h>

#include "dosfs.h"
/*
 * If the FAT > this size then skip comparing, lest we risk
 * OOMing the framework. in the future we need to just re-write
 * this whole thing and optimize for less memory
 */
#define FAT_COMPARE_MAX_KB 4096
#define THISMOD 0x8000

#define	SLOT_EMPTY	0x00		/* slot has never been used */
#define	SLOT_E5		0x05		/* the real value is 0xe5 */
#define	SLOT_DELETED	0xe5		/* file in this slot deleted */

#define	ATTR_NORMAL	0x00		/* normal file */
#define	ATTR_READONLY	0x01		/* file is readonly */
#define	ATTR_HIDDEN	0x02		/* file is hidden */
#define	ATTR_SYSTEM	0x04		/* file is a system file */
#define	ATTR_VOLUME	0x08		/* entry is a volume label */
#define	ATTR_DIRECTORY	0x10		/* entry is a directory name */
#define	ATTR_ARCHIVE	0x20		/* file is new or modified */

#define	ATTR_WIN95	0x0f		/* long name record */

static int
readboot(struct bootblock *boot)
{
	u_char block[DOSBOOTBLOCKSIZE];
	u_char fsinfo[2 * DOSBOOTBLOCKSIZE];
	u_char backup[DOSBOOTBLOCKSIZE];
	int ret = FSOK;

	if (disk_read(0, 1, block) < 1) {
		debug("could not read boot block");
        return FSFATAL;
	}

	debug("boot block: %02x%02x", block[511], block[510]);
	if (block[510] != 0x55 || block[511] != 0xaa) {
		debug("Invalid signature in boot block: %02x%02x", block[511], block[510]);
        return FSFATAL;
	}

	boot->ValidFat = -1;

	/* decode bios parameter block */
	boot->BytesPerSec = block[11] + (block[12] << 8);
	boot->SecPerClust = block[13];
	boot->ResSectors = block[14] + (block[15] << 8);
	boot->FATs = block[16];
	boot->RootDirEnts = block[17] + (block[18] << 8);
	boot->Sectors = block[19] + (block[20] << 8);
	boot->Media = block[21];
	boot->FATsmall = block[22] + (block[23] << 8);
	boot->SecPerTrack = block[24] + (block[25] << 8);
	boot->Heads = block[26] + (block[27] << 8);
	boot->HiddenSecs = block[28] + (block[29] << 8) + (block[30] << 16) + (block[31] << 24);
	boot->HugeSectors = block[32] + (block[33] << 8) + (block[34] << 16) + (block[35] << 24);
	boot->FATsecs = boot->FATsmall;

	if (!boot->RootDirEnts)
		boot->flags |= FAT32;
	else {
		debug("not fat32, uboot don't support fat16\n");
        return FSFATAL;
	}

	if (boot->flags & FAT32) {
		boot->FATsecs = block[36] + (block[37] << 8)
				+ (block[38] << 16) + (block[39] << 24);
		if (block[40] & 0x80)
			boot->ValidFat = block[40] & 0x0f;

		/* check version number: */
		if (block[42] || block[43]) {
			/* Correct?				XXX */
			debug("Unknown file system version: %x.%x",
			       block[43], block[42]);
                        return FSFATAL;
		}
		boot->RootCl = block[44] + (block[45] << 8)
			       + (block[46] << 16) + (block[47] << 24);
		boot->FSInfo = block[48] + (block[49] << 8);
		boot->Backup = block[50] + (block[51] << 8);

		/* If the OEM Name field is EXFAT, it's not FAT32, so bail */
		if (!memcmp(&block[3], "EXFAT   ", 8)) {
			debug("exFAT filesystem is not supported.");
			return FSFATAL;
		}

		/* check basic parameters */
		if ((boot->FSInfo == 0) ||
		    (boot->BytesPerSec % DOSBOOTBLOCKSIZE != 0) ||
		    (boot->BytesPerSec / DOSBOOTBLOCKSIZE == 0) ||
		    (boot->SecPerClust == 0)) {
			/*
			 * Either the BIOS Parameter Block has been corrupted,
                         * or this is not a FAT32 filesystem, most likely an
                         * exFAT filesystem.
			 */
			debug("Invalid FAT32 Extended BIOS Parameter Block");
			return FSFATAL;
		}
		if (disk_read(boot->FSInfo * boot->BytesPerSec / boot->BytesPerSec, 2, fsinfo)
		    != 2) {
			debug("could not read fsinfo block");
			return FSFATAL;
		}
		if (memcmp(fsinfo, "RRaA", 4)
		    || memcmp(fsinfo + 0x1e4, "rrAa", 4)
		    || fsinfo[0x1fc]
		    || fsinfo[0x1fd]
		    || fsinfo[0x1fe] != 0x55
		    || fsinfo[0x1ff] != 0xaa
		    || fsinfo[0x3fc]
		    || fsinfo[0x3fd]
		    || fsinfo[0x3fe] != 0x55
		    || fsinfo[0x3ff] != 0xaa) {
			debug("Invalid signature in fsinfo block\n");
			debug("fix\n");
			memcpy(fsinfo, "RRaA", 4);
			memcpy(fsinfo + 0x1e4, "rrAa", 4);
			fsinfo[0x1fc] = fsinfo[0x1fd] = 0;
			fsinfo[0x1fe] = 0x55;
			fsinfo[0x1ff] = 0xaa;
			fsinfo[0x3fc] = fsinfo[0x3fd] = 0;
			fsinfo[0x3fe] = 0x55;
			fsinfo[0x3ff] = 0xaa;
			if (disk_write(boot->FSInfo * boot->BytesPerSec / boot->BytesPerSec, 2, fsinfo) != 2) {
				debug("Unable to write FSInfo");
				return FSFATAL;
			}
			ret = FSBOOTMOD;
		}
		if (boot->FSInfo) {
			boot->FSFree = fsinfo[0x1e8] + (fsinfo[0x1e9] << 8)
				       + (fsinfo[0x1ea] << 16)
				       + (fsinfo[0x1eb] << 24);
			boot->FSNext = fsinfo[0x1ec] + (fsinfo[0x1ed] << 8)
				       + (fsinfo[0x1ee] << 16)
				       + (fsinfo[0x1ef] << 24);
		}

		if (disk_read(boot->Backup * boot->BytesPerSec / boot->BytesPerSec, 1, backup) != 1) {
			debug("could not read backup bootblock");
			return FSFATAL;
		}
		backup[65] = block[65];				/* XXX */
		if (memcmp(block + 11, backup + 11, 79)) {
                        char tmp[255];
                        int i;

			/*
			 * For now, lets not bail out if they don't match
			 * It seems a lot of sdcards are formatted with
			 * the backup either empty or containing garbage.
			 */

			debug("Primary/Backup bootblock miscompare\n");

            strcpy(tmp, "");
            debug("Primary:\n");
			for (i = 0; i < 79; i++) {
				char tmp2[16];
				snprintf(tmp2, sizeof(tmp2), "%.2x ", block[11 + i]);
				strcat(tmp, tmp2);
            }
            debug("%s\n", tmp);

			strcpy(tmp, "");
            debug("Backup:\n");
			for (i = 0; i < 79; i++) {
				char tmp2[16];
				snprintf(tmp2, sizeof(tmp2), "%.2x ", backup[11 + i]);
				strcat(tmp, tmp2);
            }
            debug("%s\n", tmp);
		}
		/* Check backup FSInfo?					XXX */
	}

	if (boot->BytesPerSec % DOSBOOTBLOCKSIZE != 0) {
		debug("Invalid sector size: %u", boot->BytesPerSec);
		return FSFATAL;
	}
	if (boot->SecPerClust == 0) {
		debug("Invalid cluster size: %u", boot->SecPerClust);
		return FSFATAL;
	}
	if (boot->BytesPerSec == 0) {
		debug("Invalid sector size: %u", boot->BytesPerSec);
		return FSFATAL;
	}
	if (boot->FATs == 0) {
		debug("Invalid number of FATs: %u", boot->FATs);
		return FSFATAL;
	}
	if (boot->Sectors) {
		boot->HugeSectors = 0;
		boot->NumSectors = boot->Sectors;
	} else
		boot->NumSectors = boot->HugeSectors;

	boot->ClusterOffset = (boot->RootDirEnts * 32 + boot->BytesPerSec - 1)
	    / boot->BytesPerSec
	    + boot->ResSectors
	    + boot->FATs * boot->FATsecs
	    - CLUST_FIRST * boot->SecPerClust;

	boot->NumClusters = (boot->NumSectors - boot->ClusterOffset) / boot->SecPerClust;

	if (boot->flags&FAT32)
		boot->ClustMask = CLUST32_MASK;
	else {
		debug("Filesystem too big (%u clusters) for non-FAT32 partition",
		       boot->NumClusters);
		return FSFATAL;
	}

	boot->NumFatEntries = (boot->FATsecs * boot->BytesPerSec) / 4;

	if (boot->NumFatEntries < boot->NumClusters) {
		debug("FAT size too small, %u entries won't fit into %u sectors\n",
		       boot->NumClusters, boot->FATsecs);
		return FSFATAL;
	}
	boot->ClusterSize = boot->BytesPerSec * boot->SecPerClust;

	boot->NumFiles = 1;
	boot->NumFree = 0;

	return ret;
}

/*
 * Get type of reserved cluster
 */
static char *
rsrvdcltype(cl_t cl)
{
	if (cl == CLUST_FREE)
		return "free";
	if (cl < CLUST_BAD)
		return "reserved";
	if (cl > CLUST_BAD)
		return "as EOF";
	return "bad";
}

/*
 * Check a cluster number for valid value
 */
static int
checkclnum(struct bootblock *boot, int fat, cl_t cl, cl_t *next)
{
	if (*next >= (CLUST_RSRVD&boot->ClustMask))
		*next |= ~boot->ClustMask;
	if (*next == CLUST_FREE) {
		boot->NumFree++;
		return FSOK;
	}
	if (*next == CLUST_BAD) {
		boot->NumBad++;
		return FSOK;
	}
	if (*next < CLUST_FIRST
	    || (*next >= boot->NumClusters && *next < CLUST_EOFS)) {
		debug("Cluster %u in FAT %d continues with %s cluster number %u\n",
		      cl, fat,
		      *next < CLUST_RSRVD ? "out of range" : "reserved",
		      *next&boot->ClustMask);
		debug("Truncate\n");
		*next = CLUST_EOF;
		return FSFATMOD;
	}
	return FSOK;
}

/*
 * Read a FAT and decode it into internal format
 */
static int
checkfat(struct bootblock *boot, int no)
{
	struct fatEntry *fat;
	u_char *p, *buffer;
	__u32 cl, cl_t, start_cl, SecEnd;
	int ret = FSOK;
	__u32 EntryNum;

	boot->NumFree = boot->NumBad = 0;

	__u32 off;

    debug("Attempting to allocate %u KB for Fat\n",
                (boot->SecPerClust * boot->BytesPerSec) / 1024);

	buffer = malloc(boot->SecPerClust * boot->BytesPerSec);
	if (buffer == NULL) {
		debug("no space for fat");
		return FSFATAL;
	}

	off = boot->ResSectors + no * boot->FATsecs;

	if (disk_read(off, boot->SecPerClust, buffer) != boot->SecPerClust) {
		debug("unable to read fat");
		free(buffer);
		return FSFATAL;
	}

	EntryNum = boot->SecPerClust * boot->BytesPerSec / 4;
    debug("Attempting to allocate %u KB for Entry\n",
                (EntryNum * sizeof(struct fatEntry)) / 1024);
	fat = malloc(EntryNum * sizeof(struct fatEntry));
	if (fat == NULL) {
		debug("No space for FAT");
		free(buffer);
		return FSFATAL;
	}
	memset(fat, 0, EntryNum * sizeof(struct fatEntry));

	if (buffer[0] != boot->Media
	    || buffer[1] != 0xff || buffer[2] != 0xff
	    || (boot->ClustMask == CLUST32_MASK
		&& ((buffer[3]&0x0f) != 0x0f
		    || buffer[4] != 0xff || buffer[5] != 0xff
		    || buffer[6] != 0xff || (buffer[7]&0x0f) != 0x0f))) {

		/* Windows 95 OSR2 (and possibly any later) changes
		 * the FAT signature to 0xXXffff7f for FAT16 and to
		 * 0xXXffff0fffffff07 for FAT32 upon boot, to know that the
		 * file system is dirty if it doesn't reboot cleanly.
		 * Check this special condition before errorring out.
		 */
		if (buffer[0] == boot->Media && buffer[1] == 0xff
		    && buffer[2] == 0xff
		    && (boot->ClustMask == CLUST32_MASK
			    && buffer[3] == 0x0f && buffer[4] == 0xff
			    && buffer[5] == 0xff && buffer[6] == 0xff
			    && buffer[7] == 0x07))
			ret |= FSFATAL;
		else {
			/* just some odd byte sequence in FAT */

			debug("%s (%02x%02x%02x%02x%02x%02x%02x%02x)\n",
			      "FAT starts with odd byte sequence",
			      buffer[0], buffer[1], buffer[2], buffer[3],
			      buffer[4], buffer[5], buffer[6], buffer[7]);

			debug("Correct\n");
			ret |= FSFIXFAT;
		}
	}

	p = buffer + 8;

	start_cl = 0;
	cl = CLUST_FIRST;
	SecEnd =  off + boot->FATsecs;

	if (boot->flags & FAT32) {
		if (boot->RootCl < CLUST_FIRST || boot->RootCl >= boot->NumClusters) {
			debug("Root directory starts with cluster out of range(%u)",
			       boot->RootCl);
			free(buffer);
			free(fat);
			return FSFATAL;
		}
	}

	fat[boot->RootCl].flags |= FAT_USED;

	do {
		while (cl - start_cl < EntryNum) {
			fat[cl - start_cl].next = p[0] + (p[1] << 8)
				       + (p[2] << 16) + (p[3] << 24);
			fat[cl - start_cl].next &= boot->ClustMask;
			ret |= checkclnum(boot, no, cl, &fat[cl - start_cl].next);

			if (boot->RootCl == cl) {
				cl_t = fat[boot->RootCl].next;
				if (cl_t < CLUST_FIRST
					|| (cl_t >= CLUST_RSRVD && cl_t < CLUST_EOFS)) {
					if (cl_t == CLUST_FREE)
						debug("Root directory starts with free cluster\n");
					else if (cl_t >= CLUST_RSRVD)
						debug("Root directory starts with cluster marked %s\n",
						rsrvdcltype(cl_t));
					else {
						debug("Root directory doesn't start a cluster chain");
						free(buffer);
						free(fat);
						return FSFATAL;
					}
					debug("Fix\n");
					fat[boot->RootCl].next = CLUST_FREE;
					ret = FSFATAL;
				}
			}

			cl++;
			p += 4;
		}

		start_cl = cl;
		off += boot->SecPerClust;

		if (off > SecEnd)
			goto back;
		else if (off > SecEnd - boot->SecPerClust)
			EntryNum = (SecEnd - off) * boot->SecPerClust / 4;

		if (disk_read(off, boot->SecPerClust, buffer) != boot->SecPerClust) {
			debug("Unable to read\n");
			free(buffer);
			free(fat);
			return FSFATAL;
		}
		p = buffer;
	} while(cl < boot->NumClusters);

back:
	free(buffer);
	free(fat);
	return ret;
}

/*
 * Read a directory and
 *   - resolve long name records
 *   - enter file and directory records into the parent's list
 *   - push directories onto the todo-stack
 */
static int
checkRootDir(struct bootblock *boot, struct fatEntry *fat,
    struct dosDirEntry *dir)
{
	struct dosDirEntry dirent;
	u_char *p, *empty, *buf;
	__u32 off, last;
	cl_t cl, empcl = ~0;
	int i, j, k;
	char *t;
	int mod = FSOK;

#define	THISMOD	0x8000			/* Only used within this routine */

	cl = dir->head;
	if (cl < CLUST_FIRST || cl >= boot->NumClusters) {
		/*
		 * root dir should be ok.
		 */
		return FSFATAL;
	}
	empty = NULL;

	debug("Attempting to allocate %u KB for RootDir\n",
            (boot->SecPerClust * boot->BytesPerSec) / 1024);
	buf = malloc(boot->SecPerClust * boot->BytesPerSec);
	if (buf == NULL) {
		debug("no space for fat");
		return FSFATAL;
	}

	do {
		last = boot->SecPerClust;
		off = cl * boot->SecPerClust + boot->ClusterOffset;

		//need check last size
	    if (disk_read(off, last, buf) != last) {
			debug("Unable to read\n");
			free(buf);
			return FSFATAL;
        }

		last *= boot->BytesPerSec;
		last /= 32;
		for (p = buf, i = 0; i < last; i++, p += 32) {

			if (*p == SLOT_EMPTY || *p == SLOT_DELETED) {
				if (*p == SLOT_EMPTY) {
					dir->fsckflags |= DIREMPTY;
					empty = p;
					empcl = cl;
				}
				break;
			}

			if (dir->fsckflags & DIREMPTY) {
				debug("Extend\n");
				u_char *q;

				dir->fsckflags &= ~DIREMPTY;
				q = empcl == cl ? empty : buf;
				for (; q < p; q += 32)
					*q = SLOT_DELETED;
				mod |= FSDIRMOD|FSERROR|THISMOD;
			}

			if (p[11] == ATTR_WIN95) {
				continue;	/* long records don't carry further
					 * information */
			}

			/*
			 * This is a standard msdosfs directory entry.
			 */
			memset(&dirent, 0, sizeof dirent);

			/*
			 * it's a short name record, but we need to know
			 * more, so get the flags first.
			 */
			dirent.flags = p[11];

			/*
			 * Translate from 850 to ISO here		XXX
			 */
			for (j = 0; j < 8; j++)
				dirent.name[j] = p[j];
			dirent.name[8] = '\0';
			for (k = 7; k >= 0 && dirent.name[k] == ' '; k--)
				dirent.name[k] = '\0';
			if (dirent.name[k] != '\0')
				k++;
			if (dirent.name[0] == SLOT_E5)
				dirent.name[0] = 0xe5;

			if (dirent.flags & ATTR_VOLUME) {
				continue;
			}

			if (p[8] != ' ')
				dirent.name[k++] = '.';
			for (j = 0; j < 3; j++)
				dirent.name[k++] = p[j+8];
			dirent.name[k] = '\0';
			for (k--; k >= 0 && dirent.name[k] == ' '; k--)
				dirent.name[k] = '\0';

			dirent.head = p[26] | (p[27] << 8);
			if (boot->ClustMask == CLUST32_MASK)
				dirent.head |= (p[20] << 16) | (p[21] << 24);
			dirent.size = p[28] | (p[29] << 8) | (p[30] << 16) | (p[31] << 24);

			if (dirent.size == 0 && !(dirent.flags & ATTR_DIRECTORY)) {
				if (dirent.head != 0) {
					debug("Drop allocated clusters\n");
					p[26] = p[27] = 0;
					if (boot->ClustMask == CLUST32_MASK)
						p[20] = p[21] = 0;
					dirent.head = 0;
					mod |= FSDIRMOD|FSFATMOD|FSFATAL|THISMOD;
				}
			} else if (dirent.head == 0
				   && !strcmp(dirent.name, "..")) {
				/*
				 *  Do nothing, the parent is the root
				 */
			} else if (dirent.head < CLUST_FIRST
				   || dirent.head >= boot->NumClusters) {

				if (dirent.flags & ATTR_DIRECTORY) {
					debug("Remove\n");
					*p = SLOT_DELETED;
					mod |= FSDIRMOD|THISMOD;
					continue;
				} else {
					debug("Truncate\n");
					p[28] = p[29] = p[30] = p[31] = 0;
					p[26] = p[27] = 0;
					if (boot->ClustMask == CLUST32_MASK)
						p[20] = p[21] = 0;
					dirent.size = 0;
					mod |= FSDIRMOD|FSFATAL|THISMOD;
				}
			}
		}
		if (mod & THISMOD) {
			last = boot->SecPerClust;
			if (disk_write(off, last, buf) != last) {
				debug("Unable to write directory");
				free(buf);
				return FSFATAL;
			}
			mod &= ~THISMOD;
		}
	} while (0);

	free(buf);
	return mod & ~THISMOD & ~FSFATAL;
}

static int checkfree(struct bootblock *boot, __u64 ram_size)
{
	if ((__u64)boot->NumFree * (__u64)boot->SecPerClust * (__u64)boot->BytesPerSec <= ram_size)
		return FSNOSPACE;
	else
		return FSOK;
}

int fat_checksys(__u64 ram_size)
{
	struct bootblock boot;
	struct dosDirEntry rootDir;
	struct fatEntry *fat = NULL;
	int mod = 0;

	debug("** Phase 1 - Check Boot\n");
	memset(&boot, 0, sizeof(struct bootblock));
	if (readboot(&boot) == FSFATAL) {
		debug("read boot fail\n");
		return FSFATAL;
	}

	debug("** Phase 2 - Check FAT\n");
	mod |= checkfat(&boot, boot.ValidFat >= 0 ? boot.ValidFat : 0);
	if (mod & FSFATAL) {
		debug("Fatal error during readfat()\n");
		return FSFATAL;
	}

	debug("** Phase 3 - Check Free Space\n");
	mod |= checkfree(&boot, ram_size);
	if (mod & FSNOSPACE) {
		debug("don't have enough space\n");
		return FSNOSPACE;
	}

	rootDir.head = boot.RootCl;
	rootDir.fsckflags = 0;
	debug("** Phase 4 - Check RootDir\n");
	mod |= checkRootDir(&boot, fat, &rootDir);
	if (mod & FSFATAL) {
		debug("Fatal error during checkRootDir()\n");
		return FSFATAL;
	}

	return FSOK;
}

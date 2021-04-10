#include <common.h>
#include <part.h>
#include <sparse_format.h>
#include <sprd_common_rw.h>
#include "sparse_crc32.h"


#define COPY_BUF_SIZE (1024*1024)
#define SPARSE_HEADER_LEN       (sizeof(sparse_header_t))
#define CHUNK_HEADER_LEN (sizeof(chunk_header_t))

/* modify for download very big size ext4 image */
typedef enum EXT4_DL_STATUS_DEF
{
	START = 0,
	END
} EXT4_DL_STATUS_E;

typedef struct {
	chunk_header_t header;    /* chunk header */
	int idx;	  /* index of chunk */
	u64 saved_len;            /* length of chunk which was already saved */
} uncomplete_chunk_t;

static u8 copybuf[COPY_BUF_SIZE];
static unsigned int g_buf_index = 0;

static sparse_header_t sparse_header;
static EXT4_DL_STATUS_E download_status = END;
static unsigned long current_chunks = 0;
static u32 total_blocks = 0;
static uncomplete_chunk_t uncomplete_ck;/* save chunk relative information */

static int read_all(void *buf_src, u32 src_index, void *buf_dest, size_t len)
{
	memcpy(buf_dest, (void*)((u32)buf_src + src_index), len);
	g_buf_index += len;
	return len;
}

static int preread_chunk(void *buf_src, u32 src_index, void *buf_dest, size_t len)
{
	memcpy(buf_dest, (void*)((u32)buf_src + src_index), len);
	return len;
}


static int process_crc32_chunk(void *buf, u32 crc32)
{
	u32 file_crc32;
	int ret;

	ret = read_all(buf, g_buf_index, &file_crc32, 4);
	if (ret != 4) {
		errorf("read returned an error copying a crc32 chunk\n");
		return -1;
	}

	if (file_crc32 != crc32) {
		errorf("computed crc32 of 0x%8.8x, expected 0x%8.8x\n",
			 crc32, file_crc32);
		return -1;
	}

	return 0;
}

/* -1 : error; x : buf is finished to write */
int write_sparse_img(uchar * partname, u8* buf, unsigned long length)
{
	unsigned int i;
	unsigned int j;
	chunk_header_t chunk_header;
	u32 crc32 = 0;
	int ret;
	static uint64_t offset = 0;
	uint64_t chunk_len = 0;
	int chunk;
	u32 fill_val;
	u32 *fillbuf;
	u64 sparse_sz, part_sz;

	g_buf_index = 0;

	if (download_status == END) {
		memset(&uncomplete_ck, 0, sizeof(uncomplete_ck));
		uncomplete_ck.idx = -1;
		current_chunks = 0;
		total_blocks = 0;
		offset = 0;
		memset(&sparse_header, 0, sizeof(sparse_header_t));
		ret = read_all(buf, g_buf_index, &sparse_header, sizeof(sparse_header));
		debugf("sparse_header file_hdr_sz = %d chunk_hdr_sz = %d blk_sz = %d total_blks = %d total_chunks = %d\n",
			sparse_header.file_hdr_sz, sparse_header.chunk_hdr_sz, sparse_header.blk_sz,

			sparse_header.total_blks, sparse_header.total_chunks);
		if (ret != sizeof(sparse_header)) {
			errorf("Error reading sparse file header\n");
			goto fail;
		}
		if (sparse_header.magic != SPARSE_HEADER_MAGIC) {
			errorf("Bad magic\n");
			goto fail;
		}
		if (sparse_header.major_version != SPARSE_HEADER_MAJOR_VER) {
			errorf("Unknown major version number\n");
			goto fail;
		}

		if (sparse_header.file_hdr_sz > SPARSE_HEADER_LEN) {
			/* Skip the remaining bytes in a header that is longer than
			* we expected.
			 */
			g_buf_index += (sparse_header.file_hdr_sz - SPARSE_HEADER_LEN);
		}
		download_status = START;
	}

	for (i = current_chunks; i < sparse_header.total_chunks; i++) {
		memset(&chunk_header, 0, sizeof(chunk_header_t));
		if ((g_buf_index + sizeof(chunk_header)) > length) {
			debugf("bufferindex(%d) + sizeof(chunk_header)(%d) exceed length\n", g_buf_index, sizeof(chunk_header));
			current_chunks = i;
			break;
		}

		if (!i || (i != uncomplete_ck.idx)) {
			preread_chunk((void*)buf, g_buf_index, &chunk_header, sizeof(chunk_header));
			//debugf("chunk_header.total_sz(%d)\n", chunk_header.total_sz);

			/*
			 * fixup for "fastboot flash -S 200M system system.img"
			 *   1. first block(200M): the first chunk type must not be 0xCAC3
			 *   2. other blocks: the first chuck type is 0xCAC3 and chunk_len was offset continue
			 *   from last block
			 */
			if (!offset && !current_chunks
				&& (chunk_header.chunk_type != CHUNK_TYPE_DONT_CARE)
				&& strcmp(partname, "userdata")) {
				/* erase partition before spare image write */
				sparse_sz = (u64)sparse_header.total_blks * (u64)sparse_header.blk_sz;
				if (sparse_sz) {
					if ((get_img_partition_size(partname, &part_sz) >= 0)
							&& (part_sz > 0)) {
						if (sparse_sz > part_sz) {
							errorf("fail: sparse sz(0x%llx) large than partition sz(0x%llx)\n", sparse_sz, part_sz);
							goto fail;
						} else {
							debugf("??? sparse img write, erase partition %s sz 0x%llx\n", partname, sparse_sz);
							if (common_raw_erase(partname, sparse_sz > part_sz ? part_sz : sparse_sz, offset)) {
								errorf("sparse image write, erase partition %s fail\n", partname);
								goto fail;
							}
						}
					}
				}
			}

			ret = 0;
			switch (chunk_header.chunk_type) {
			case CHUNK_TYPE_RAW:
			case CHUNK_TYPE_FILL:
			case CHUNK_TYPE_DONT_CARE:
			case CHUNK_TYPE_CRC32:
				if ((g_buf_index + chunk_header.total_sz) > length) {
					debugf("bufferindex(%d)+chunk_header.total_sz(%d) exceed  length(%d) \n", g_buf_index, chunk_header.total_sz, length);
					ret = 1;
				}
				break;
			default:
				errorf("Unknown chunk type 0x%4.4x\n", chunk_header.chunk_type);
			}

			if (ret == 1) {
				/* save uncomplete chunk header only for type RAW */
				current_chunks = i;
				if (chunk_header.chunk_type == CHUNK_TYPE_RAW) {
					memcpy(&uncomplete_ck.header, &chunk_header, sizeof(chunk_header_t));
					uncomplete_ck.idx = i;
					uncomplete_ck.saved_len = 0;
				} else
					break;
			}

			memset(&chunk_header, 0, sizeof(chunk_header_t));
			ret = read_all((void*)buf, g_buf_index, &chunk_header, sizeof(chunk_header));

			if (ret != sizeof(chunk_header)) {
				errorf("Error reading chunk header\n");
				goto fail;
			}

			if (sparse_header.chunk_hdr_sz > CHUNK_HEADER_LEN) {
				/* Skip the remaining bytes in a header that is longer than
				 * we expected.*/
				g_buf_index += sparse_header.chunk_hdr_sz - CHUNK_HEADER_LEN;
			}

			/* write current part of this chunk to flash */
			if ((chunk_header.chunk_type == CHUNK_TYPE_RAW)
				&& i && (i == uncomplete_ck.idx)) {
				chunk_len = length - g_buf_index;
			} else
				chunk_len = (uint64_t)chunk_header.chunk_sz * sparse_header.blk_sz;
		} else {
			memcpy(&chunk_header, &uncomplete_ck.header, sizeof(chunk_header_t));

			chunk_len = (uint64_t)chunk_header.total_sz - sizeof(chunk_header_t)
							- uncomplete_ck.saved_len;
			if (chunk_len > (length - g_buf_index))
				chunk_len = length - g_buf_index;
		}

		switch (chunk_header.chunk_type) {
		case CHUNK_TYPE_RAW:
			if ((i != uncomplete_ck.idx)
				&& (chunk_header.total_sz != (sparse_header.chunk_hdr_sz + chunk_len))) {
				errorf("Bogus chunk size for chunk %d, type Raw\n", i);
				goto fail;
			}

			if (0 != common_raw_write(partname, chunk_len, (uint64_t)0, offset, buf + g_buf_index)) {
				errorf("Write raw chunk fail, trunk_len=0x%x!\n", chunk_len);
				goto fail;
			} else {
				crc32 = sparse_crc32(crc32, buf + g_buf_index, chunk_len);
				g_buf_index += chunk_len;
				offset += chunk_len;
				if (i == uncomplete_ck.idx) {
					uncomplete_ck.saved_len += chunk_len;
					if (uncomplete_ck.saved_len == (uint64_t)chunk_header.total_sz - sizeof(chunk_header_t)) {
						total_blocks += chunk_header.chunk_sz;
						memset(&uncomplete_ck, 0, sizeof(uncomplete_ck));
						uncomplete_ck.idx = -1;
					} else
						goto out;
				} else
					total_blocks += chunk_header.chunk_sz;
			}
			break;
		case CHUNK_TYPE_FILL:
			if (chunk_header.total_sz != (sparse_header.chunk_hdr_sz + sizeof(fill_val)) ) {
				errorf("Bogus chunk size for chunk %d, type Fill\n", i);
				goto fail;
			}
			/* Fill copy_buf with the fill value */
			ret = read_all(buf, g_buf_index, &fill_val, sizeof(fill_val));
			fillbuf = (u32 *)copybuf;
			for (j = 0; j < (COPY_BUF_SIZE / sizeof(fill_val)); j++)
				fillbuf[j] = fill_val;

			while (chunk_len) {
				chunk = (chunk_len > COPY_BUF_SIZE) ? COPY_BUF_SIZE : chunk_len;
				if (0 != common_raw_write(partname, (uint64_t)chunk, (uint64_t)0, offset, copybuf)) {
					errorf("Write fill chunk fail, trunk_len=0x%x!\n", chunk_len);
					goto fail;
				}
				crc32 = sparse_crc32(crc32, copybuf, chunk);
				offset += chunk;
				chunk_len -= chunk;
			}
			total_blocks += chunk_header.chunk_sz;
			break;
		case CHUNK_TYPE_DONT_CARE:
			if (chunk_header.total_sz != sparse_header.chunk_hdr_sz) {
				errorf("Bogus chunk size for chunk %d, type Dont Care\n", i);
				goto fail;
			}
			offset += chunk_len;
			total_blocks += chunk_header.chunk_sz;
			break;
		case CHUNK_TYPE_CRC32:
			if (process_crc32_chunk((void*)buf, crc32) != 0) {
				goto fail;
			}
			break;
		default:
			errorf("Unknown chunk type 0x%4.4x\n", chunk_header.chunk_type);
		}

	}

out:
	if (sparse_header.total_blks != total_blocks) {
		return g_buf_index;
	} else {
		download_status = END;
		current_chunks = 0;
		offset = 0;
		total_blocks = 0;
		return 0;
	}

fail:
	return -1;
}

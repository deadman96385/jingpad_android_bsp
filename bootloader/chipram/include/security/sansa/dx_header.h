#ifndef _DX_HEADER_H
#define _DX_HEADER_H


typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long      ulong;
//typedef unsigned int       size_t;
typedef unsigned long long uint64_t;

#define MAGIC_SIZE 8

#ifndef NULL
#define NULL (0x00000000)
#endif

typedef uint32_t   DxStatus;

#define DxError_t  DxStatus
#define DX_NULL    NULL
#define DX_OK      0

#define CRYPTOCELL_SECURE_BASE (0x50000000)
#define BOOT_BASE_ADDR         (0x00002000)
#define CONFIG_SPL_LDADDR_START (0xA000)
#define IMAGE_HEAD_SIZE		(512)

#define WORKSPACE_BUFFER_WORDS 1024*2
#define WORKSPACE_BUFFER_BYTES (WORKSPACE_BUFFER_WORDS*sizeof(uint32_t))
#define DX_DOUBLE_BUFFER_MAX_SIZE_IN_BYTES (WORKSPACE_BUFFER_BYTES)


//unsigned long* g_boot_workspace_base_addr
static uint32_t tmp_workspace_buf[WORKSPACE_BUFFER_WORDS];

typedef void * DX_PAL_DmaBufferHandle;

//uint64_t g_boot_free_mem_addr;
//unsigned long* g_boot_test_stack_base_addr;

typedef enum {
	DX_PAL_DMA_DIR_NONE = 0,
	DX_PAL_DMA_DIR_TO_DEVICE = 1,
	DX_PAL_DMA_DIR_FROM_DEVICE = 2,
	DX_PAL_DMA_DIR_BI_DIRECTION = 3,
	DX_PAL_DMA_DIR_MAX,
	DX_PAL_DMA_DIR_RESERVE32 = 0x7FFFFFFF
}DX_PAL_DmaBufferDirection_t;

typedef struct fmpreambleheader {


    /* Magic number */
    uint8_t magic[MAGIC_SIZE];
    /* Version of this header format */
    uint32_t header_version_major;
    /* Version of this header format */
    uint32_t header_version_minor;

    /*offset from itself start*/
    /*certificationA size,if 0,ignore*/
    uint64_t certa_size;
    uint64_t certa_offset;

    /*certificationB size,if 0,ignore*/
    uint64_t certb_size;
    uint64_t certb_offset;

    /*content certification size,if 0,ignore*/
    uint64_t certcnt_size;
    uint64_t certcnt_offset;

    /*(opt)private content size,if 0,ignore*/
    uint64_t priv_size;
    uint64_t priv_offset;

    /*(opt)debug/rma certification second size,if 0,ignore*/
    uint64_t cert_dbg_second_size;
    uint64_t cert_dbg_second_offset;

} fmpreambleheader;

SecBoot_Result_Ret sansa_secure_check(void *rootaddr, void *imgaddr, SECURE_TYPE type);
unsigned int DX_SecureBootVerify(void *imgaddr, void *pubkeyhash);
void sansa_update_swVersion(void);
void set_swVsersion_parameter_init(void);

#endif

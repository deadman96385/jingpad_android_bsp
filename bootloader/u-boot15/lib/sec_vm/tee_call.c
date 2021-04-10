#include <common.h>
#include "uboot_sec_drv.h"
#include "mv_gal.h"
#include "mv_svc_hypercalls.h"

static int init_flag = 0;
static int tos_flag = 0;

#define TOS_READY           1
#define TOS_CHECK           0x5a5a
#define TOS_STATUS          0xa5a5
#define TOS_START_NOTIFY    0x5a5a55aa
#define TOS_END_NOTIFY      0x5a5aaa55

void tee_call_request(unsigned int **mem_ptr)
{
    struct mv_shared_data *shared_data;
    volatile unsigned int *ptr;
    if(!init_flag) {
        printf("init flag=%d\n",init_flag);
        mv_init();
        init_flag = 1;
    }
    shared_data = mv_gal_get_shared_data();
    ptr = (unsigned int *)shared_data->pal_shared_mem_data;
    puts("##Wait for tos ready....\n");
    ptr[3] = TOS_CHECK;/*send check cmd*/
    if(!tos_flag) {
        if(mv_svc_ivmc_request(3) != 0){
            while(1) {
                printf("tos is not ready,status: 0x%x\n",ptr[2]);
                if(ptr[2] == TOS_STATUS)/*tos return status val at ptr[2]*/
                {
                    tos_flag = TOS_READY;
                    ptr[3] = 0; /*clear cmd*/
                    break;
                }
                mdelay(200);
            }
        }
    }
    *mem_ptr = ptr;
}

void tos_status_check()
{
    unsigned int *share_data;
    tee_call_request(&share_data);
}

void tee_sync_request(uint32_t tag)
{
    struct mv_shared_data *shared_data;
    volatile unsigned int *ptr;

    printf("tee_sync_request() tag = 0x%x\n", tag);
    if(!init_flag) {
        mv_init();
        init_flag = 1;
    }
    shared_data = mv_gal_get_shared_data();
    ptr = (unsigned int *)shared_data->pal_shared_mem_data;
    ptr[3] = tag;
    if (mv_svc_ivmc_request(3) != 0) {
        printf("start notify: will wait ready... \n");
        while(1) {
            /* tos return status val at ptr[2] */
            printf("tos status: 0x%x\n", ptr[2]);
            if (ptr[2] == TOS_STATUS) {
                tos_flag = TOS_READY;
                ptr[3] = 0; /*clear cmd*/
                break;
            }
            mdelay(200);
        }
    }
}

void tos_start_notify()
{
    tee_sync_request(TOS_START_NOTIFY);
}

void tos_end_notify()
{
    tee_sync_request(TOS_END_NOTIFY);
}


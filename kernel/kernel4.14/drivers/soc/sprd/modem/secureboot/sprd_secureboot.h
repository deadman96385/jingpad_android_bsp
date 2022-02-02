#include "sprd_verify.h"
#include <linux/stddef.h>

#define SECBOOT_HEAD_SIZE 512
#define MAX_MODEM_NUM 10

static u8 *const secure_modem[] = {
	"modem", "v3phy", "nrphy", "nrdsp1", NULL
};

struct kbc_image_s {
	u8 *img_name;
	u64 img_addr;
	u32 img_len;
};

struct kbc_load_table_s {
	u32 image_cnt;
	struct kbc_image_s image[MAX_MODEM_NUM];
};

int sprd_image_verify(struct kbc_load_table_s  *p_table);
int sprd_check_secure_part(u8 *partition_name);


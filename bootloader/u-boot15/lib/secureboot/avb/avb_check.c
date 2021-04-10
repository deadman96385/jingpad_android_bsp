#include <common.h>

#include <libavb.h>
#include <avb/uboot_avb_pub.h>
#include <secureboot/sec_common.h>


AvbOps g_avb_ops;
AvbSlotVerifyData* avb_slot_data[2] = {NULL, NULL};

int avb_check_vbmeta(uint8_t * vbmeta_img_paddr, uint32_t vbmeta_image_len)
{
    AvbSlotVerifyResult verify_result;
    uint8_t * vbmeta_pubkey_addr = 0;
    uint32_t vbmeta_pubkey_len = 0;
    AvbVBMetaVerifyResult vbmeta_ret;
    const uint8_t* pk_data = 0;
    size_t pk_len = 0;
    bool key_istrusted = false;
    uint32_t vboot_verify_ret = 0;
    uint64_t rollback_index = 0;
    uint64_t stored_rollback_index = 0;
    AvbIOResult io_ret;

    if (!vbmeta_img_paddr ||!vbmeta_image_len) {
        debug("invalid: para is null.\n");
        return AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    }
    vbmeta_ret = avb_vbmeta_image_verify(vbmeta_img_paddr, vbmeta_image_len,
                                         &pk_data, &pk_len, &rollback_index);
    debug("vbmeta_ret is %d.\n", vbmeta_ret);
    debug("rollback_index is %lld.\n", rollback_index);
    if (vbmeta_ret == 0) {
#ifdef CONFIG_VBOOT_DUMP
        debug("dump pk_data:, pk_len:%d\n", pk_len);
        do_hex_dump(pk_data, pk_len);
#endif
        vboot_verify_ret = g_avb_ops.validate_vbmeta_public_key(&g_avb_ops, pk_data, pk_len, vbmeta_pubkey_addr, vbmeta_pubkey_len, &key_istrusted);
        debug("vboot_verify_ret is %d, key_istrusted:%d.\n", vboot_verify_ret, key_istrusted);
        verify_result = vboot_verify_ret;
        if (verify_result!=AVB_IO_RESULT_OK)
            goto out;
        /* Check rollback index. */
        debug("Check rollback index for vbmeta \n");
        io_ret = g_avb_ops.read_rollback_index(&g_avb_ops, 0, &stored_rollback_index);
        if (io_ret != AVB_IO_RESULT_OK) {
            verify_result = AVB_SLOT_VERIFY_RESULT_ERROR_ROLLBACK_INDEX;
            goto out;
        }
        if (rollback_index < stored_rollback_index) {
            debug("Error: vbmeta rollback_index:%lld, < stored_rollback_index:%lld.\n",
                  rollback_index, stored_rollback_index);
            verify_result = AVB_SLOT_VERIFY_RESULT_ERROR_ROLLBACK_INDEX;
            goto out;
        } else {
            debug("Info: vbmeta rollback_index:%lld, >= stored_rollback_index:%lld.\n",
                  rollback_index, stored_rollback_index);
            verify_result = AVB_SLOT_VERIFY_RESULT_OK;
        }
    } else {
        verify_result = vbmeta_ret;
    }
out:
    return verify_result;
}

int avb_check_image(unsigned char *name)
{
    AvbSlotVerifyResult verify_result;
    const char         *slot_suffixes[2] = {"", ""};
    const char         *requested_partitions[] = {"boot", NULL};
    AvbSlotVerifyFlags flags = AVB_SLOT_VERIFY_FLAGS_NONE;
    AvbSlotVerifyData  *out_slot_data = NULL;

    if (name) {
        debug("avb check image name:%s.\n", name);
        requested_partitions[0] = name;
    } else {
        debug("avb check image name is null.\n");
        requested_partitions[0] = "";
    }

#ifndef CONFIG_VBOOT_SYSTEMASROOT
	if ((g_ulAvbCheckType == AVB_CHECK_BOOTING) &&
		VBOOT_STATUS_UNLOCK == get_lock_status()) {
		flags |= AVB_SLOT_VERIFY_FLAGS_ALLOW_VERIFICATION_ERROR;
	}
#endif

    //load data and check
      verify_result = avb_slot_verify(&g_avb_ops,
                                      requested_partitions,
                                      slot_suffixes[0],
                                      flags,
                                      AVB_HASHTREE_ERROR_MODE_RESTART_AND_INVALIDATE,
                                      &avb_slot_data[0]);
    debug(">>>>>>>>>>>>>>>>  avb_slot_verify result is %d.\n", verify_result);
    debug(">>>>>>>>>>>>>>>>  avb_slot_verify result is %s.\n", avb_slot_verify_result_to_string(verify_result));
    debug("slot_data[0] is 0x%x.\n", avb_slot_data[0]);
    debug("slot_data[1] is 0x%x.\n", avb_slot_data[1]);
    out_slot_data = avb_slot_data[0];
    return verify_result;
}

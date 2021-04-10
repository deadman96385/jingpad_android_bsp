/*
 * sprd_ce.h
 *
 *  Created on: 2016.1.25.
 *      Author: feng.wang
 */

#ifndef SPRD_CE_H_
#define SPRD_CE_H_

#include <linux/types.h>

#ifndef bool
typedef int bool;
#endif
#ifndef false
#define false 0
#endif
#ifndef true
#define true 1
#endif

enum sprd_ce_status {
    SPRD_CE_OK          = 0x00,
    SPRD_CE_FAILED,
    SPRD_CE_START,
    SPRD_CE_DONE,
    SPRD_CE_END,
    SPRD_CE_ERR_LEN,
    SPRD_CE_ERR_KEY,
    SPRD_CE_ERR_CONT,
    SPRD_CE_ERR_MODE,
    SPRD_CE_ERR_ADDR,
    SPRD_CE_ERR_ARG,
    SPRD_CE_NOP,
};

#define SPRD_CE_STD             0x00
#define SPRD_CE_LINK            0x01

#define SPRD_CE_MAIN_MODE_MASK  0xFFFF0000
#define SPRD_CE_SUB_MODE_MASK   0x0000FFFF
#define SPRD_CE_MAIN_MODE_OFFSET        16

#define SPRD_CE_ENC     0
#define SPRD_CE_DEC     1

#define SPRD_CE_DMA                     0x00000000

#define SPRD_CE_AES                     0x00010000
#define SPRD_CE_AES_ECB                 (SPRD_CE_AES + 0x0000)
#define SPRD_CE_AES_CBC                 (SPRD_CE_AES + 0x0001)
#define SPRD_CE_AES_CTR                 (SPRD_CE_AES + 0x0002)
#define SPRD_CE_AES_XTS                 (SPRD_CE_AES + 0x0003)

#define SPRD_CE_TDES                    0x00020000
#define SPRD_CE_TDES_ECB                (SPRD_CE_TDES + 0x0000)
#define SPRD_CE_TDES_CBC                (SPRD_CE_TDES + 0x0001)

#define SPRD_CE_HASH                    0x00030000
#define SPRD_CE_HASH_MD5                (SPRD_CE_HASH + 0x0001)
#define SPRD_CE_HASH_SHA1               (SPRD_CE_HASH + 0x0002)
#define SPRD_CE_HASH_SHA224             (SPRD_CE_HASH + 0x0003)
#define SPRD_CE_HASH_SHA256             (SPRD_CE_HASH + 0x0004)
#define SPRD_CE_HASH_SHA384             (SPRD_CE_HASH + 0x0005)
#define SPRD_CE_HASH_SHA512             (SPRD_CE_HASH + 0x0006)
#define SPRD_CE_HASH_SHA512_224         (SPRD_CE_HASH + 0x0007)
#define SPRD_CE_HASH_SHA512_256         (SPRD_CE_HASH + 0x0008)
#define SPRD_CE_HASH_LIMIT              0x0008
#define SPRD_CE_HMAC_MD5                (SPRD_CE_HASH + 0x0009)
#define SPRD_CE_HMAC_SHA1               (SPRD_CE_HASH + 0x000A)
#define SPRD_CE_HMAC_SHA224             (SPRD_CE_HASH + 0x000B)
#define SPRD_CE_HMAC_SHA256             (SPRD_CE_HASH + 0x000C)
#define SPRD_CE_HMAC_SHA384             (SPRD_CE_HASH + 0x000D)
#define SPRD_CE_HMAC_SHA512             (SPRD_CE_HASH + 0x000E)
#define SPRD_CE_HMAC_SHA512_224         (SPRD_CE_HASH + 0x000F)
#define SPRD_CE_HMAC_SHA512_256         (SPRD_CE_HASH + 0x0010)

#define SPRD_CE_RSA                     0x00040000
#define SPRD_CE_RSA_ENC_1024            (SPRD_CE_RSA + 0x0000)
#define SPRD_CE_RSA_ENC_2048            (SPRD_CE_RSA + 0x0001)
#define SPRD_CE_RSA_ENC_3072            (SPRD_CE_RSA + 0x0002)
#define SPRD_CE_RSA_ENC_4096            (SPRD_CE_RSA + 0x0003)
#define SPRD_CE_RSA_DEC_1024            (SPRD_CE_RSA + 0x0004)
#define SPRD_CE_RSA_DEC_2048            (SPRD_CE_RSA + 0x0005)
#define SPRD_CE_RSA_DEC_3072            (SPRD_CE_RSA + 0x0006)
#define SPRD_CE_RSA_DEC_4096            (SPRD_CE_RSA + 0x0007)
#define SPRD_CE_RSA_KEY_GEN_PRIME_512   (SPRD_CE_RSA + 0x0008)
#define SPRD_CE_RSA_KEY_GEN_PRIME_1024  (SPRD_CE_RSA + 0x0009)
#define SPRD_CE_RSA_KEY_GEN_PRIME_1536  (SPRD_CE_RSA + 0x000A)
#define SPRD_CE_RSA_KEY_GEN_PRIME_2048  (SPRD_CE_RSA + 0x000B)

#define SPRD_CE_RNG                     0x00050000
#define SPRD_CE_RNG_MIX                 (SPRD_CE_RNG + 0x0000)
#define SPRD_CE_RNG_TRUE                (SPRD_CE_RNG + 0x0001)
#define SPRD_CE_RNG_PSEUDO              (SPRD_CE_RNG + 0x0002)

#define SPRD_CE_MODE_LIMIT              0x00060000

#define SPRD_CE_ITEM_NUM_PER_LIST  0x02
#define SPRD_CE_DATA_LEN_PER_ITEM  0x10

struct sprd_ce_aes_mode {
    uint32_t mode;
    struct {
        uint32_t en             :1;
        uint32_t                :3;
        uint32_t enc_dec_sel    :1;
        uint32_t                :3;
        uint32_t mode           :2;
        uint32_t                :2;
        uint32_t keylen         :2;
        uint32_t xts_iv_rotate  :1;
        uint32_t                :17;
    } cfg;
};

struct sprd_ce_tdes_mode {
    uint32_t mode;
    struct {
        uint32_t en             :1;
        uint32_t                :3;
        uint32_t enc_dec_sel    :1;
        uint32_t                :3;
        uint32_t mode           :2;
        uint32_t                :2;
        uint32_t key_even_sel   :1;
        uint32_t                :19;
    } cfg;
};

struct sprd_ce_hash_mode {
    uint32_t mode;
    struct {
        uint32_t en         :1;
        uint32_t            :3;
        uint32_t mode       :5;
        uint32_t            :23;
    } cfg;
};

struct sprd_ce_rsa_mode {
    uint32_t mode;
    struct {
        uint32_t en             :1;
        uint32_t                :3;
        uint32_t mode           :4;
        uint32_t miller_num     :4;
        uint32_t random_sel     :3;
        uint32_t                :1;
        uint32_t random_mode_sel:2;
        uint32_t                :14;
    } cfg;
};

struct sprd_ce_rng_mode {
    uint32_t mode;
    struct {
        uint32_t rng_mode       :2;
        uint32_t                :6;
        uint32_t prng_work_mode :1;
        uint32_t                :23;
    } cfg;
};

union sprd_ce_mode{
    uint32_t mode;
    struct sprd_ce_aes_mode aes_mode;
    struct sprd_ce_tdes_mode tdes_mode;
    struct sprd_ce_hash_mode hash_mode;
    struct sprd_ce_rsa_mode rsa_mode;
    struct sprd_ce_rng_mode rng_mode;
};

struct sprd_ce_cfg {
    uint32_t link_mode              :1;
    uint32_t                        :3;
    uint32_t std_end                :1;
    uint32_t                        :3;
    uint32_t key_in_ddr             :1;
    uint32_t key_in_efuse           :1;
    uint32_t key_in_session         :1;
    uint32_t                        :1;
    uint32_t do_wait_bdone          :1;
    uint32_t gen_int_each_list      :1;
    uint32_t                        :2;
    uint32_t list_pause             :1;
    uint32_t list_end               :1;
    uint32_t list_up_iv_sec_cnt     :1;
    uint32_t                        :1;
    uint32_t dst_byte_switch        :1;
    uint32_t src_byte_switch        :1;
    uint32_t dst_word_switch        :1;
    uint32_t src_word_switch        :1;
    uint32_t dst_outstanding_num    :4;
    uint32_t src_outstanding_num    :4;
} ;

/*struct sprd_ce_cfg {
    union sprd_ce_mode mode;
    struct sprd_ce_basic_cfg basic_cfg;
};*/

struct sprd_ce_data {
    uint8_t *in;
    uint32_t in_len;
    uint32_t in_max_len;
    bool    in_cacheable;
    uint8_t *out;
    uint32_t out_len;
    uint32_t out_max_len;
    bool    out_cacheable;
};

struct sprd_ce_key {
    uint8_t *key;
    uint32_t key_len;
    uint32_t key_max_len;
    bool    key_cacheable;
};

struct sprd_ce_iv {
    uint8_t *iv;
    uint32_t iv_len;
    uint32_t iv_max_len;
};

struct sprd_ce_flag {
    volatile int ret;
    volatile int status;
    volatile int start;
    volatile int end;
};

struct sprd_ce_list_data{
    uint64_t src_addr;
    uint64_t dst_addr;
    uint32_t data_len;
} ;

struct sprd_ce_list_node {
    struct sprd_ce_list_node* next_list;
    uint32_t next_len;
    uint32_t iv_sec_cnt[4];
    struct sprd_ce_list_data list_data[SPRD_CE_ITEM_NUM_PER_LIST];
};

struct sprd_ce_list {
    struct sprd_ce_list_node *list_ptr;
    uint32_t  first_list_len;
};

struct sprd_ce_dma {
    uint64_t    dst_addr;
    uint32_t    dst_len;
    bool        dst_cacheable;
    uint64_t    src_addr;
    uint32_t    src_len;
    bool        src_cacheable;
    uint64_t    key_addr;
    uint32_t    key_len;
    bool        key_cacheable;
    //struct sprd_ce_list ce_list;
};

typedef void (*sprd_ce_fiq_handler_t)(void);
typedef void (*sprd_ce_fiq_func_t)(uint32_t, void*);


void sprd_ce_init(void);
void sprd_ce_reset(void);
void sprd_ce_open(void);
void sprd_ce_close(void);
void sprd_ce_operate(void);
int  sprd_ce_polling(void);
void sprd_ce_clear(void);


/* register interrupt function */
void sprd_ce_register_fiq_func(sprd_ce_fiq_func_t fiq_function, void *context);

/* configurate crypt engine */
void sprd_ce_set_cfg(struct sprd_ce_cfg *p_cfg);
int  sprd_ce_set_mode(union sprd_ce_mode *p_mode);
int  sprd_ce_clr_mode(union sprd_ce_mode *p_mode);
int  sprd_ce_set_data(uint32_t mode, struct sprd_ce_data *p_data);
int  sprd_ce_set_key(uint32_t mode, struct sprd_ce_key *p_key);
int  sprd_ce_set_iv(uint32_t mode, struct sprd_ce_iv *p_iv);
int  sprd_ce_set_seed(uint32_t prng_seed);
int  sprd_ce_rng_read(uint8_t *out, uint32_t *out_len);

#endif /* SPRD_CE_H_ */

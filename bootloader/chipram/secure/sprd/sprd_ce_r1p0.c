/*
 * ce.c
 *
 *  Created on: 2016.1.25
 *      Author: feng.wang
 */

#include <stdarg.h>
#include <sci_types.h>
#include <security/sprd_ce_r1p0.h>
#include <asm/arch/hardware.h>

#define BIT(_n)             			((u32) 1 << (_n))
#define MASK(__n,__w)  					(((1 << (__w)) - 1) << (__n))
#define VALUE(__n,__v) 					((__v) << (__n))
#define REG_SET_BIT(__base,__n,__v)		((*(volatile u32 *)(__base)) |= (__v) << (__n))
#define REG_CLR_BIT(__base,__n,__v)		((*(volatile u32 *)(__base)) &= (~__v) << (__n))
#define REG_SET_VALUE(__base,__v) 		((*(volatile u32 *)(__base)) = (uint32)(__v))
#define REG_GET_VALUE(__base)		    (*(volatile u32 *)(__base))
#define SCI_ADDR(_b_, _o_) 				( (u32)(_b_) + (_o_) )
//sprd register set/clr mode
#define SET_OFFSET  0x1000
#define CLR_OFFSET  0x2000
#define SPRD_REG_SET_BIT(__base, __v)   ((*(volatile u32 *)((__base) + SET_OFFSET)) = (uint32_t)(__v))
#define SPRD_REG_CLR_BIT(__base, __v)   ((*(volatile u32 *)((__base) + CLR_OFFSET)) = (uint32_t)(__v))

#define SPRD_CE_ARGCHK(x)   if (!(x)) return SPRD_CE_ERR_ARG;

#define CTL_BASE_AHB    	REGS_AP_AHB_BASE
#define CTL_BASE_SCE    	SPRD_CE0_BASE//secure
//#define CTL_BASE_PCE    	SPRD_CE1_BASE//public

#define SPRD_BYTE_ALIGN	               0x08
#define REGS_AP_AHB_RF_BASE           (CTL_BASE_AHB)

/* registers definitions for AP_AHB_RF */
#define REG_AP_AHB_RF_AHB_EB           SCI_ADDR(REGS_AP_AHB_RF_BASE, 0x0000)/*AHB_EB*/
#define REG_AP_AHB_RF_AHB_RST          SCI_ADDR(REGS_AP_AHB_RF_BASE, 0x0004)/*AHB_RST*/

/* bits definitions for register REG_AP_AHB_RF_AHB_RST */
//#define BIT_AP_AHB_RF_CE1_SOFT_RST     ( BIT(26) )
#define BIT_AP_AHB_RF_CE0_SOFT_RST     ( BIT(25) )

/* bits definitions for register REG_AP_AHB_RF_AHB_EB */
//#define BIT_AP_AHB_RF_CE1_EB           ( BIT(25) )
#define BIT_AP_AHB_RF_CE0_EB           ( BIT(24) )

//CE register
#define	 INT_REQ_AP_SCE                  (46 + 32)
//#define	 INT_REQ_AP_PCE                  (47 + 32)
#define SPRD_CE_INT_NUM                 INT_REQ_AP_SCE
#define SPRD_CE_REG_BASE                CTL_BASE_SCE

#define SPRD_CE_CLKGATE_EN              (SPRD_CE_REG_BASE + 0x18)
#define SPRD_CE_INT_EN                  (SPRD_CE_REG_BASE + 0x1C)
#define SPRD_CE_INT_STATUS              (SPRD_CE_REG_BASE + 0x20)
#define SPRD_CE_INT_CLEAR               (SPRD_CE_REG_BASE + 0x24)
#define SPRD_CE_START                   (SPRD_CE_REG_BASE + 0x28)
#define SPRD_CE_CLEAR                   (SPRD_CE_REG_BASE + 0x2c)
#define SPRD_CE_AES_MODE                (SPRD_CE_REG_BASE + 0x30)
#define SPRD_CE_TDES_MODE               (SPRD_CE_REG_BASE + 0x34)
#define SPRD_CE_HASH_MODE               (SPRD_CE_REG_BASE + 0x38)
#define SPRD_CE_RSA_MODE                (SPRD_CE_REG_BASE + 0x3c)
#define SPRD_CE_RSA_E_PUB_KEY_MODE      (SPRD_CE_REG_BASE + 0x40)
#define SPRD_CE_CFG                     (SPRD_CE_REG_BASE + 0x44)
#define SPRD_CE_SRC_FLAG_LEN            (SPRD_CE_REG_BASE + 0x48)
#define SPRD_CE_DST_FLAG_LEN            (SPRD_CE_REG_BASE + 0x4C)
#define SPRD_CE_SRC_ADDR                (SPRD_CE_REG_BASE + 0x50)
#define SPRD_CE_DST_ADDR                (SPRD_CE_REG_BASE + 0x54)
#define SPRD_CE_LIST_LEN                (SPRD_CE_REG_BASE + 0x58)
#define SPRD_CE_LIST_PTR                (SPRD_CE_REG_BASE + 0x5C)
#define SPRD_CE_HMAC_KEY_LEN            (SPRD_CE_REG_BASE + 0x60)
#define SPRD_CE_HMAC_KEY_ADDR           (SPRD_CE_REG_BASE + 0x64)
#define SPRD_CE_ATR_KEY_LEN             (SPRD_CE_REG_BASE + 0x68)
#define SPRD_CE_ATR_KEY_ADDR            (SPRD_CE_REG_BASE + 0x6C)
#define SPRD_CE_IV_SEC_CNT0             (SPRD_CE_REG_BASE + 0x70)
#define SPRD_CE_IV_SEC_CNT1             (SPRD_CE_REG_BASE + 0x74)
#define SPRD_CE_IV_SEC_CNT2             (SPRD_CE_REG_BASE + 0x78)
#define SPRD_CE_IV_SEC_CNT3             (SPRD_CE_REG_BASE + 0x7C)
#define SPRD_CE_AES_DES_KEY10           (SPRD_CE_REG_BASE + 0x80)
#define SPRD_CE_AES_DES_KEY11           (SPRD_CE_REG_BASE + 0x84)
#define SPRD_CE_AES_DES_KEY12           (SPRD_CE_REG_BASE + 0x88)
#define SPRD_CE_AES_DES_KEY13           (SPRD_CE_REG_BASE + 0x8C)
#define SPRD_CE_AES_DES_KEY14           (SPRD_CE_REG_BASE + 0x90)
#define SPRD_CE_AES_DES_KEY15           (SPRD_CE_REG_BASE + 0x94)
#define SPRD_CE_AES_DES_KEY16           (SPRD_CE_REG_BASE + 0x98)
#define SPRD_CE_AES_DES_KEY17           (SPRD_CE_REG_BASE + 0x9C)
#define SPRD_CE_AES_DES_KEY20           (SPRD_CE_REG_BASE + 0xA0)
#define SPRD_CE_AES_DES_KEY21           (SPRD_CE_REG_BASE + 0xA4)
#define SPRD_CE_AES_DES_KEY22           (SPRD_CE_REG_BASE + 0xA8)
#define SPRD_CE_AES_DES_KEY23           (SPRD_CE_REG_BASE + 0xAC)
#define SPRD_CE_AES_DES_KEY24           (SPRD_CE_REG_BASE + 0xB0)
#define SPRD_CE_AES_DES_KEY25           (SPRD_CE_REG_BASE + 0xB4)
#define SPRD_CE_AES_DES_KEY26           (SPRD_CE_REG_BASE + 0xB8)
#define SPRD_CE_AES_DES_KEY27           (SPRD_CE_REG_BASE + 0xBC)
#define SPRD_CE_RNG_EN                  (SPRD_CE_REG_BASE + 0x200)
#define SPRD_CE_RNG_CONFIG              (SPRD_CE_REG_BASE + 0x204)
#define SPRD_CE_RNG_DATA                (SPRD_CE_REG_BASE + 0x208)
#define SPRD_CE_RNG_SAMPLE_PERIOD       (SPRD_CE_REG_BASE + 0x20C)
#define SPRD_CE_RNG_POST_PROCESS_EN     (SPRD_CE_REG_BASE + 0x210)
#define SPRD_CE_RNG_WORK_STATUS         (SPRD_CE_REG_BASE + 0x214)
#define SPRD_CE_RNG_TIMEOUT_CNT         (SPRD_CE_REG_BASE + 0x218)
#define SPRD_CE_RNG_INT_EN              (SPRD_CE_REG_BASE + 0x21C)
#define SPRD_CE_RNG_INT_STS             (SPRD_CE_REG_BASE + 0x220)
#define SPRD_CE_RNG_INT_CLR             (SPRD_CE_REG_BASE + 0x224)
#define SPRD_CE_RNG_MODE                (SPRD_CE_REG_BASE + 0x228)
#define SPRD_CE_RNG_SEED_UPDATE         (SPRD_CE_REG_BASE + 0x22C)
#define SPRD_CE_RNG_SEED_CONFIG         (SPRD_CE_REG_BASE + 0x230)
#define SPRD_CE_RNG_BIT_RATE            (SPRD_CE_REG_BASE + 0x234)

#define SPRD_CE_START_EN                BIT(0)
#define SPRD_CE_RESET_EN                BIT(0)

#define SPRD_DMA_CG_EN                  BIT(0)
#define SPRD_AES_CG_EN                  BIT(1)
#define SPRD_TDES_CG_EN                 BIT(2)
#define SPRD_HASH_CG_EN                 BIT(3)
#define SPRD_RSA_CG_EN                  BIT(4)
#define SPRD_TRNG_CG_EN                 BIT(5)

#define SPRD_STD_DONE_INT               BIT(0)
#define SPRD_STD_END_INT                BIT(1)
#define SPRD_LIST_DONE_INT              BIT(2)
#define SPRD_LIST_END_INT               BIT(3)
#define SPRD_LEN_ERR_INT                BIT(4)
#define SPRD_TDES_KEY_ERR_INT           BIT(5)
#define SPRD_RSA_WORK_DONE_INT          BIT(6)
#define SPRD_TRNG_INT                   BIT(7)

#define SPRD_STD_DONE_INT_STATUS        BIT(0)
#define SPRD_STD_END_INT_STATUS         BIT(1)
#define SPRD_LIST_DONE_INT_STATUS       BIT(2)
#define SPRD_LIST_END_INT_STATUS        BIT(3)
#define SPRD_LEN_ERR_INT_STATUS         BIT(4)
#define SPRD_TDES_KEY_ERR_INT_STATUS    BIT(5)
#define SPRD_RSA_WORK_DONE_INT_STATUS   BIT(6)
#define SPRD_TRNG_INT_STATUS            BIT(7)

#define SPRD_CLEAR_STD_DONE_INT         BIT(0)
#define SPRD_CLEAR_STD_END_INT          BIT(1)
#define SPRD_CLEAR_LIST_DONE_INT        BIT(2)
#define SPRD_CLEAR_LIST_END_INT         BIT(3)
#define SPRD_CLEAR_LEN_ERR_INT          BIT(4)
#define SPRD_CLEAR_TDES_KEY_ERR_INT     BIT(5)
#define SPRD_CLEAR_RSA_WORK_DONE_INT    BIT(6)
#define SPRD_CLEAR_TRNG_INT             BIT(7)

#define SPRD_CE_START_EN                BIT(0)
#define SPRD_CE_CLEAR_EN                BIT(0)

#define SPRD_CE_AES_EN                  BIT(0)
#define SPRD_AES_ENC_DEC_SEL            BIT(4)

#define SPRD_CE_TDES_EN                 BIT(0)
#define SPRD_TDES_ENC_DES_SEL           BIT(4)

#define SPRD_CE_HASH_EN                 BIT(0)
#define SPRD_HASH_MD5_MODE              VALUE(4, 0x01)
#define SPRD_HASH_SHA_1_MODE            VALUE(4, 0x02)
#define SPRD_HASH_SHA_224_MODE          VALUE(4, 0x03)
#define SPRD_HASH_SHA_256_MODE          VALUE(4, 0x04)
#define SPRD_HASH_SHA_384_MODE          VALUE(4, 0x05)
#define SPRD_HASH_SHA_512_MODE          VALUE(4, 0x06)
#define SPRD_HASH_SHA_512_224_MODE      VALUE(4, 0x07)
#define SPRD_HASH_SHA_512_256_MODE      VALUE(5, 0x08)
#define SPRD_HMAC_MD5_MODE              VALUE(4, 0x09)
#define SPRD_HMAC_SHA_1_MODE            VALUE(4, 0x0A)
#define SPRD_HMAC_SHA_224_MODE          VALUE(4, 0x0B)
#define SPRD_HMAC_SHA_256_MODE          VALUE(4, 0x0C)
#define SPRD_HMAC_SHA_384_MODE          VALUE(4, 0x0D)
#define SPRD_HMAC_SHA_512_MODE          VALUE(4, 0x0E)
#define SPRD_HMAC_SHA_512_224_MODE      VALUE(4, 0x0F)
#define SPRD_HMAC_SHA_512_256_MODE      VALUE(5, 0x10)

#define SPRD_CE_RSA_EN                  BIT(0)
#define SPRD_RSA_ENC_1024               VALUE(4, 0x00)
#define SPRD_RSA_ENC_2048               VALUE(4, 0x01)
#define SPRD_RSA_ENC_3072               VALUE(4, 0x02)
#define SPRD_RSA_ENC_4096               VALUE(4, 0x03)
#define SPRD_RSA_DEC_1024               VALUE(4, 0x04)
#define SPRD_RSA_DEC_2048               VALUE(4, 0x05)
#define SPRD_RSA_DEC_3072               VALUE(4, 0x06)
#define SPRD_RSA_DEC_4096               VALUE(4, 0x07)
#define SPRD_RSA_KEY_GEN_512            VALUE(4, 0x08)
#define SPRD_RSA_KEY_GEN_1024           VALUE(4, 0x09)
#define SPRD_RSA_KEY_GEN_1536           VALUE(4, 0x0A)
#define SPRD_RSA_KEY_GEN_2048           VALUE(4, 0x0B)
#define SPRD_RSA_RAND_SEL_0             VALUE(8, 0x00)
#define SPRD_RSA_RAND_SEL_1             VALUE(8, 0x01)
#define SPRD_RSA_RAND_SEL_2             VALUE(8, 0x02)
#define SPRD_RSA_RAND_SEL_3             VALUE(8, 0x03)
#define SPRD_RSA_MILLER_CNT(_x)         VALUE(12, _x)

#define SPRD_CE_STD_MODE                VALUE(0, 0x00)
#define SPRD_CE_LINK_MODE               VALUE(0, 0x01)

#define SPRD_LIST_MODE                  VALUE(16,0x00)
#define SPRD_LIST_END                   VALUE(16,0x01)
#define SPRD_LIST_PAUSE                 VALUE(17,0x01)

/*#define SPRD_INTC1_IRQ_ENABLE       (CTL_BASE_INTC1 + 0x08)
#define SPRD_INTC1_FIQ_ENABLE       (CTL_BASE_INTC1 + 0x28)
#define SPRD_INTC1_REQ_CE0          (46-32)
#define SPRD_INTC1_REQ_CE1          (47-32)*/

#define is_aligned(POINTER, BYTE_COUNT) ((((uint32_t)(POINTER)) & ((uint32_t)(BYTE_COUNT)-1)) == 0)
#define is_multiple(NUMBER, FACTOR) ((((uint32_t)(NUMBER)) & ((FACTOR)-1)) == 0)

#define SPRD_CE_RNG_THRESHOLD 8
#define SPRD_CE_PRNG_SEED 0x55987565
#define SPRD_CE_CLK_MASK 0xDE   /* all clks except for RNG and DMA */

//ce clk register
#define BIT_CGM_CE0_SEL				(0x3)
#define CGM_CE0_SEL_26M				(0x0)
#define CGM_CE0_SEL_96M				(0x1)
#define CGM_CE0_SEL_192M			(0x2)
#define CGM_CE0_SEL_256M			(0x3)

struct sprd_ce_dma g_dma;

void sprd_dma_init(void) {
    g_dma.src_addr = 0x0;
    g_dma.src_len = 0;
    g_dma.dst_addr = 0x0;
    g_dma.dst_len = 0;
    g_dma.key_addr = 0x0;
    g_dma.key_len = 0;
}


static inline void sprd_ce_clk_enable(uint32_t sprd_ce_mode) {
    uint32_t reg = REG_GET_VALUE(SPRD_CE_CLKGATE_EN);
    reg |= 1 << (sprd_ce_mode >> SPRD_CE_MAIN_MODE_OFFSET);
    switch(sprd_ce_mode & SPRD_CE_MAIN_MODE_MASK) {
    case SPRD_CE_AES:
    case SPRD_CE_TDES:
    case SPRD_CE_HASH:
        reg |= 1 << (SPRD_CE_DMA >> SPRD_CE_MAIN_MODE_OFFSET);
        break;
    case SPRD_CE_RSA:
        reg |= (1 << (SPRD_CE_DMA >> SPRD_CE_MAIN_MODE_OFFSET)) | (1 << (SPRD_CE_RNG >> SPRD_CE_MAIN_MODE_OFFSET));
        break;
    case SPRD_CE_RNG:
        break;
    }
    REG_SET_VALUE(SPRD_CE_CLKGATE_EN, reg);
}

static inline void sprd_ce_clk_disable(uint32_t sprd_ce_mode) {
    unsigned int reg = REG_GET_VALUE(SPRD_CE_CLKGATE_EN);
    reg &= ~(1 << (sprd_ce_mode >> SPRD_CE_MAIN_MODE_OFFSET));
    switch(sprd_ce_mode & SPRD_CE_MAIN_MODE_MASK) {
    case SPRD_CE_AES:
    case SPRD_CE_TDES:
    case SPRD_CE_HASH:
        break;
    case SPRD_CE_RSA:
        /*if(!(REG_GET_VALUE(SPRD_CE_RNG_EN) & 0x1)) {
            reg &= ~(1 << (SPRD_CE_RNG >> SPRD_CE_MAIN_MODE_OFFSET));
        }*/
        break;
    case SPRD_CE_RNG:
        break;
    }

    /*if all mode is closed, dma is closed*/
    if(!(reg & SPRD_CE_CLK_MASK)) {
        reg &= ~(1 << (SPRD_CE_DMA >> SPRD_CE_MAIN_MODE_OFFSET));
    }
    REG_SET_VALUE(SPRD_CE_CLKGATE_EN, reg);
}

static inline void sprd_ce_all_clk_disable(void) {
    REG_SET_VALUE(SPRD_CE_CLKGATE_EN, 0x0);
}

static inline void sprd_ce_all_int_enable(void) {
    REG_SET_VALUE(SPRD_CE_INT_EN, 0x3F);
}

static inline void sprd_ce_all_int_disable(void) {
    REG_SET_VALUE(SPRD_CE_INT_EN, 0x00);
}

static inline void sprd_ce_int_clear(int sprd_ce_int) {
    REG_SET_VALUE(SPRD_CE_INT_CLEAR, sprd_ce_int);
}

static inline int sprd_ce_int_get(void) {
    return REG_GET_VALUE(SPRD_CE_INT_STATUS);
}

/*
 * in should be aligned at the size of cache line
 * out should be aligned at the size of cache line
 * in_len should be multiple of the size of cache line
 * out_len should be multiple of the size of cache line
 * */
void sprd_ce_set_cfg(struct sprd_ce_cfg *p_cfg) {
    REG_SET_VALUE(SPRD_CE_CFG, *(uint32_t*)p_cfg);
}

int sprd_ce_set_mode (union sprd_ce_mode *p_mode){
    sprd_ce_clk_enable(p_mode->mode);

    switch(p_mode->mode & SPRD_CE_MAIN_MODE_MASK) {
    case SPRD_CE_AES:
        REG_SET_VALUE(SPRD_CE_AES_MODE, *(uint32_t*)(&p_mode->aes_mode.cfg));
        break;
    case SPRD_CE_TDES:
        REG_SET_VALUE(SPRD_CE_TDES_MODE, *(uint32_t*)(&p_mode->tdes_mode.cfg));
        break;
    case SPRD_CE_HASH:
        REG_SET_VALUE(SPRD_CE_HASH_MODE, *(uint32_t*)(&p_mode->hash_mode.cfg));
        break;
    case SPRD_CE_RSA:
        REG_SET_VALUE(SPRD_CE_RSA_MODE, *(uint32_t*)(&p_mode->rsa_mode.cfg));
        break;
    case SPRD_CE_RNG:
        REG_SET_VALUE(SPRD_CE_RNG_MODE, *(uint32_t*)(&p_mode->rng_mode.cfg));
        REG_SET_VALUE(SPRD_CE_RNG_CONFIG,
                (REG_GET_VALUE(SPRD_CE_RNG_CONFIG) & 0x00FF) | ((SPRD_CE_RNG_THRESHOLD & 0xFF) << 8));

        switch(p_mode->mode) {
        case SPRD_CE_RNG_MIX:
        case SPRD_CE_RNG_TRUE:
            /*
             * first time, enable trng source;
             * the second time, enable the RNG mode;
             * the time between two accesses is enough for a delay.
             */
            REG_SET_VALUE(SPRD_CE_RNG_EN, REG_GET_VALUE(SPRD_CE_RNG_EN) | (0x01<<1));
            break;
        case SPRD_CE_RNG_PSEUDO:
            REG_SET_VALUE(SPRD_CE_RNG_SEED_CONFIG, SPRD_CE_PRNG_SEED);
            REG_SET_VALUE(SPRD_CE_RNG_SEED_UPDATE, 0x1);
            break;
        }

        REG_SET_VALUE(SPRD_CE_RNG_EN, REG_GET_VALUE(SPRD_CE_RNG_EN) | 0x01);

        /* RNG will not use fiq */
        sprd_ce_all_int_disable();
        break;
    default:
        return SPRD_CE_ERR_MODE;
    }
    return SPRD_CE_OK;
}

int sprd_ce_clr_mode (union sprd_ce_mode *p_mode) {
    switch(p_mode->mode & SPRD_CE_MAIN_MODE_MASK) {
    case SPRD_CE_AES:
        REG_SET_VALUE(SPRD_CE_AES_MODE, 0x0);
        break;
    case SPRD_CE_TDES:
        REG_SET_VALUE(SPRD_CE_TDES_MODE, 0x0);
        break;
    case SPRD_CE_HASH:
        REG_SET_VALUE(SPRD_CE_HASH_MODE, 0x0);
        break;
    case SPRD_CE_RSA:
        REG_SET_VALUE(SPRD_CE_RSA_MODE, 0x0);
        break;
    case SPRD_CE_RNG:
        REG_SET_VALUE(SPRD_CE_RNG_EN, 0x0);
        REG_SET_VALUE(SPRD_CE_RNG_MODE, 0x0);
        break;
    }

    sprd_ce_clk_disable(p_mode->mode);
    return SPRD_CE_OK;
}

int sprd_ce_set_data_phy(uint32_t mode, struct sprd_ce_data *p_data) {

    SPRD_CE_ARGCHK(p_data != NULL);
    SPRD_CE_ARGCHK(p_data->out != NULL);
    SPRD_CE_ARGCHK(p_data->in_len <= p_data->in_max_len);
    SPRD_CE_ARGCHK(p_data->out_len <= p_data->out_max_len);

    g_dma.src_addr = 0x0000000fffffffff & (uint32_t)p_data->in;
    g_dma.src_len = p_data->in_len;
    g_dma.src_cacheable = p_data->in_cacheable;
    REG_SET_VALUE(SPRD_CE_SRC_ADDR, (uint32_t )g_dma.src_addr & 0xffffffff);
    REG_SET_VALUE(SPRD_CE_SRC_FLAG_LEN, (((uint32_t)(g_dma.src_addr >> 8)) & 0x0f000000) | (g_dma.src_len & 0xffffff));

    g_dma.dst_addr = 0x0000000fffffffff & (uint32_t)p_data->out;
    g_dma.dst_len = p_data->out_len;
    g_dma.dst_cacheable = p_data->out_cacheable;
    REG_SET_VALUE(SPRD_CE_DST_ADDR, (uint32_t)g_dma.dst_addr & 0xffffffff);
    REG_SET_VALUE(SPRD_CE_DST_FLAG_LEN, (((uint32_t)(g_dma.dst_addr >> 8)) & 0x0f000000) | (g_dma.dst_len & 0xffffff));

    return SPRD_CE_OK;
}

int sprd_ce_set_key_phy(uint32_t mode, struct sprd_ce_key *p_key) {
    bool flush = false;

    SPRD_CE_ARGCHK(p_key != NULL);
    SPRD_CE_ARGCHK(p_key->key_len <= p_key->key_max_len);

    g_dma.key_addr = 0x0000000fffffffff & (uint32_t)p_key->key;
    g_dma.key_len = p_key->key_len;
    g_dma.key_cacheable = p_key->key_cacheable;
    switch(mode & SPRD_CE_MAIN_MODE_MASK) {
    case SPRD_CE_AES:
        REG_SET_VALUE(SPRD_CE_ATR_KEY_ADDR, (uint32_t)g_dma.key_addr & 0xffffffff);
        REG_SET_VALUE(SPRD_CE_ATR_KEY_LEN, (((uint32_t)(g_dma.key_addr >> 8)) & 0x0f000000) | (g_dma.key_len & 0xffffff));
        flush = true;
        break;
    case SPRD_CE_TDES:
        REG_SET_VALUE(SPRD_CE_ATR_KEY_ADDR, (uint32_t)g_dma.key_addr & 0xffffffff);
        REG_SET_VALUE(SPRD_CE_ATR_KEY_LEN, (((uint32_t)(g_dma.key_addr >> 8)) & 0x0f000000) | (g_dma.key_len & 0xffffff));
        flush = true;
        break;
    case SPRD_CE_HASH:
        if(mode > SPRD_CE_HASH_LIMIT) {
            REG_SET_VALUE(SPRD_CE_HMAC_KEY_ADDR, (uint32_t)g_dma.key_addr & 0xffffffff);
            REG_SET_VALUE(SPRD_CE_HMAC_KEY_LEN, (((uint32_t)(g_dma.key_addr >> 8)) & 0x0f000000) | (g_dma.key_len & 0xffffff));
            flush = true;
        }
        break;
    case SPRD_CE_RSA:
        switch(mode) {
        case SPRD_CE_RSA_KEY_GEN_PRIME_512:
        case SPRD_CE_RSA_KEY_GEN_PRIME_1024:
        case SPRD_CE_RSA_KEY_GEN_PRIME_1536:
        case SPRD_CE_RSA_KEY_GEN_PRIME_2048:
            REG_SET_VALUE(SPRD_CE_RSA_E_PUB_KEY_MODE, *(uint32_t *)((uint32_t)g_dma.key_addr) & 0x1ffff);
            break;

        case SPRD_CE_RSA_ENC_1024:
        case SPRD_CE_RSA_ENC_2048:
        case SPRD_CE_RSA_ENC_3072:
        case SPRD_CE_RSA_ENC_4096:
            REG_SET_VALUE(SPRD_CE_RSA_E_PUB_KEY_MODE, *(uint32_t *)((uint32_t)g_dma.key_addr + g_dma.key_len - 4) & 0x1ffff);
            g_dma.key_len -= 4;
            REG_SET_VALUE(SPRD_CE_ATR_KEY_ADDR, (uint32_t)g_dma.key_addr & 0xffffffff);
            REG_SET_VALUE(SPRD_CE_ATR_KEY_LEN, (((uint32_t)(g_dma.key_addr >> 8)) & 0x0f000000) | (g_dma.key_len & 0xffffff));
            flush =  true;
            break;
        case SPRD_CE_RSA_DEC_1024:
        case SPRD_CE_RSA_DEC_2048:
        case SPRD_CE_RSA_DEC_3072:
        case SPRD_CE_RSA_DEC_4096:
            REG_SET_VALUE(SPRD_CE_ATR_KEY_ADDR, (uint32_t)g_dma.key_addr & 0xffffffff);
            REG_SET_VALUE(SPRD_CE_ATR_KEY_LEN, (((uint32_t)(g_dma.key_addr >> 8)) & 0x0f000000) | (g_dma.key_len & 0xffffff));
            flush = true;
            break;

        default:
            break;
        }
        break;
    case SPRD_CE_RNG:
        break;
    default:
        break;
    }

    return SPRD_CE_OK;
}

void sprd_ce_rng_set_seed(uint32_t prng_seed)
{
    REG_SET_VALUE(SPRD_CE_RNG_SEED_UPDATE, 1);
    REG_SET_VALUE(SPRD_CE_RNG_SEED_CONFIG, prng_seed);
}

int sprd_ce_set_iv(uint32_t mode, struct sprd_ce_iv *p_iv) {

    SPRD_CE_ARGCHK(p_iv != NULL);
    SPRD_CE_ARGCHK(p_iv->iv_len <= p_iv->iv_max_len);

    switch(mode & SPRD_CE_MAIN_MODE_MASK) {
    case SPRD_CE_AES:
        if(p_iv != NULL && p_iv->iv_len <= 16) {
            REG_SET_VALUE(SPRD_CE_IV_SEC_CNT3, (p_iv->iv[12] << 24) | (p_iv->iv[13] << 16) | (p_iv->iv[14] << 8) | p_iv->iv[15]);
            REG_SET_VALUE(SPRD_CE_IV_SEC_CNT2, (p_iv->iv[8] << 24) | (p_iv->iv[9] << 16) | (p_iv->iv[10] << 8) | p_iv->iv[11]);
            REG_SET_VALUE(SPRD_CE_IV_SEC_CNT1, (p_iv->iv[4] << 24) | (p_iv->iv[5] << 16) | (p_iv->iv[6] << 8) | p_iv->iv[7]);
            REG_SET_VALUE(SPRD_CE_IV_SEC_CNT0, (p_iv->iv[0] << 24) | (p_iv->iv[1] << 16) | (p_iv->iv[2] << 8) | p_iv->iv[3]);
        }
        break;
    case SPRD_CE_TDES:
        if(p_iv != NULL && p_iv->iv_len <= 8) {
            REG_SET_VALUE(SPRD_CE_IV_SEC_CNT3, (p_iv->iv[4] << 24) | (p_iv->iv[5] << 16) | (p_iv->iv[6] << 8) | p_iv->iv[7]);
            REG_SET_VALUE(SPRD_CE_IV_SEC_CNT2, (p_iv->iv[0] << 24) | (p_iv->iv[1] << 16) | (p_iv->iv[2] << 8) | p_iv->iv[3]);
        }
        break;
    case SPRD_CE_HASH:
        break;
    case SPRD_CE_RSA:
        break;
    case SPRD_CE_RNG:
        break;
    default:
        return SPRD_CE_ERR_MODE;
    }

    return SPRD_CE_OK;
}

int sprd_ce_rng_read(uint8_t *out, uint32_t *out_len) {
    uint32_t random, i, length = *out_len;

    while (length > 0) {
        if (REG_GET_VALUE(SPRD_CE_RNG_WORK_STATUS) & 0x02) {
            random = REG_GET_VALUE(SPRD_CE_RNG_DATA);

            if(length/4) {
                *out++ = (unsigned char)random;
                *out++ = (unsigned char)(random >> 8);
                *out++ = (unsigned char)(random >> 16);
                *out++ = (unsigned char)(random >> 24);
                length -= 4;
            } else {
                switch (length%4) {
                case 1:
                    *out++ = (unsigned char)random;
                    break;
                case 2:
                    *out++ = (unsigned char)random;
                    *out++ = (unsigned char)(random >> 8);
                    break;
                case 3:
                    *out++ = (unsigned char)random;
                    *out++ = (unsigned char)(random >> 8);
                    *out++ = (unsigned char)(random >> 16);
                    break;
                default:
                    break;
                }
                length = 0;
            }
        }
    }

    *out_len -= length;

    return SPRD_CE_OK;
}

void sprd_ce_open(void) {
    sprd_ce_all_int_enable();
}

void sprd_ce_operate(void) {
    REG_SET_BIT(SPRD_CE_START, 0, SPRD_CE_START_EN);
}

int sprd_ce_polling(void) {
    while (1) {
        if (REG_GET_VALUE(SPRD_CE_INT_STATUS) & 0x02) {
            REG_SET_VALUE(SPRD_CE_INT_CLEAR, REG_GET_VALUE(SPRD_CE_INT_STATUS));
            break;
        }
    }
    return SPRD_CE_END;
}

void sprd_ce_clear(void) {
    REG_SET_VALUE(SPRD_CE_AES_MODE, 0x0);
    REG_SET_VALUE(SPRD_CE_TDES_MODE, 0x0);
    REG_SET_VALUE(SPRD_CE_HASH_MODE, 0x0);
    REG_SET_VALUE(SPRD_CE_RSA_MODE, 0x0);
    REG_SET_BIT(SPRD_CE_CLEAR, 0, SPRD_CE_CLEAR_EN);
    sprd_ce_all_int_enable();
}

void sprd_ce_close(void) {
    sprd_ce_all_int_disable();
    sprd_ce_all_clk_disable();
}

static inline void delay(unsigned int count) {
	unsigned int i;
	unsigned int l = 0;
	for(i = count; i > 0; i--)
		l++;
}

static inline void sprd_ce_enable(void) {
	//set ce freq : 256M
	unsigned int cgm_ce0_val = REG_GET_VALUE(REG_AP_CLK_CGM_CE0_CFG);
	if ((cgm_ce0_val & BIT_CGM_CE0_SEL) != CGM_CE0_SEL_256M) {
		REG_SET_VALUE(REG_AP_CLK_CGM_CE0_CFG, (cgm_ce0_val | CGM_CE0_SEL_256M));
	}
	delay(300);
	//enable ce
	SPRD_REG_SET_BIT(REG_AP_AHB_RF_AHB_EB, BIT_AP_AHB_RF_CE0_EB);
}

static inline void sprd_ce_disable(void) {
	delay(3000);
	SPRD_REG_CLR_BIT(REG_AP_AHB_RF_AHB_EB, BIT_AP_AHB_RF_CE0_EB);
}

void sprd_ce_reset(void) {
	SPRD_REG_SET_BIT(REG_AP_AHB_RF_AHB_RST, BIT_AP_AHB_RF_CE0_SOFT_RST);
	SPRD_REG_CLR_BIT(REG_AP_AHB_RF_AHB_RST, BIT_AP_AHB_RF_CE0_SOFT_RST);
}

void sprd_ce_init(void) {
    sprd_ce_enable();
    sprd_ce_reset();
    sprd_dma_init();
}

void sprd_ce_destroy(void) {
    sprd_ce_disable();
}

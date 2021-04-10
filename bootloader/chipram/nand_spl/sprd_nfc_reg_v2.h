#ifndef _SPRD_NFC_REG_V2_H_
#define _SPRD_NFC_REG_V2_H_

#define NFC_REG_BASE                (0x20b00000)
#define NFC_START_REG               (NFC_REG_BASE)
#define NFC_CFG0_REG                (NFC_REG_BASE + 0x04)
#define NFC_CFG1_REG                (NFC_REG_BASE + 0x08)
#define NFC_CFG2_REG                (NFC_REG_BASE + 0x0C)
#define NFC_INT_REG                 (NFC_REG_BASE + 0x10)
#define NFC_TIMING_REG              (NFC_REG_BASE + 0x14)
#define NFC_TIMING1_REG             (NFC_REG_BASE + 0x18)
#define NFC_TIMING2_REG             (NFC_REG_BASE + 0x1C)
#define NFC_MAIN_ADDR_REG           (NFC_REG_BASE + 0x20)
#define NFC_SPAR_ADDR_REG           (NFC_REG_BASE + 0x24)
#define NFC_STAT_ADDR_REG           (NFC_REG_BASE + 0x28)
#define NFC_SEED_ADDR_REG           (NFC_REG_BASE + 0x2c) 

#define NFC_STAT_STSMCH_REG         (NFC_REG_BASE + 0x30)
#define NFC_TIMEOUT_REG		    (NFC_REG_BASE + 0x34)
#define NFC_CFG3_REG		    (NFC_REG_BASE + 0x38)

#define NFC_STATUS0_REG             (NFC_REG_BASE + 0x40)
#define NFC_STATUS1_REG             (NFC_REG_BASE + 0x44)
#define NFC_STATUS2_REG             (NFC_REG_BASE + 0x48)
#define NFC_STATUS3_REG             (NFC_REG_BASE + 0x4C)
#define NFC_INST0_REG               (NFC_REG_BASE + 0x60)
#define NFC_INST1_REG               (NFC_REG_BASE + 0x64)
#define NFC_INST2_REG               (NFC_REG_BASE + 0x68)
#define NFC_INST3_REG               (NFC_REG_BASE + 0x6C)
#define NFC_INST4_REG               (NFC_REG_BASE + 0x70)
#define NFC_INST5_REG               (NFC_REG_BASE + 0x74)
#define NFC_INST6_REG               (NFC_REG_BASE + 0x78)
#define NFC_INST7_REG               (NFC_REG_BASE + 0x7C)
#define NFC_INST8_REG               (NFC_REG_BASE + 0x80)
#define NFC_INST9_REG               (NFC_REG_BASE + 0x84)
#define NFC_INST10_REG              (NFC_REG_BASE + 0x88)
#define NFC_INST11_REG              (NFC_REG_BASE + 0x8C)

//NFC_START bit define
#define NFC_VALID               (BIT_31)
#define NFC_RBN                 (BIT_30)
#define NFC_RBN_CNT_OFFSET      (28)
#define NFC_RBN_CNT_MASK        (0x3 << NFC_RBN_CNT_OFFSET)
#define NFC_CMD_CLR             (BIT_1)
#define NFC_START               (BIT_0)

//NFC_CFG0 bit define
#define MAST_ENDIAN_OFFSET      (30)
#define MAST_ENDIAN_MASK        (0x3 << MAST_ENDIAN_OFFSET)
#define CS_SEL                  (BIT_29)
#define SECTOR_NUM_OFFSET       (24)
#define SECTOR_NUM_MASK         (0x1f << SECTOR_NUM_OFFSET)
#define REPEAT_NUM_OFFSET       (16)
#define REPEAT_NUM_MASK         (0xff << REPEAT_NUM_OFFSET)
#define NFC_WPN                 (BIT_15)
#define BUS_WIDTH               (BIT_14)
#define SPAR_DLEN_CFG           (BIT_13)
#define SECNUM_IN_INST          (BIT_12)
#define DETECT_ALL_FF           (BIT_11)
#define NFC_RW                  (BIT_8)
#define MAIN_SPAR_APT           (BIT_6)
#define SPAR_USE                (BIT_5)
#define MAIN_USE                (BIT_4)
#define ECC_EN                  (BIT_2)
#define NFC_MODE_MASK           (0x3)
#define NFC_AUTO_MODE           (0x0)
#define NFC_ONLY_MST_MODE       (0x1)
#define NFC_ONLY_NAND_MODE      (0x2)
#define NFC_ONLY_ECC_MODE       (0x3)
//NFC_CFG1 bit define
#define SPAR_INFO_SIZE_OFFSET   (24)
#define SPAR_INFO_SIZE_MASK     (0x7f << SPAR_INFO_SIZE_OFFSET)
#define SPAR_SIZE_OFFSET        (16)
#define SPAR_SIZE_MASK          (0x7F << SPAR_SIZE_OFFSET)
#define MAIN_SIZE_MASK          (0x7ff)
//NFC_CFG2 bit define
#define SPAR_SECTOR_NUM_OFFSET  (24)
#define SPAR_SECTOR_NUM_MASK    (0x1f << SPAR_SECTOR_NUM_OFFSET)
#define SPAR_INFO_POS_OFFSET    (16)
#define SPAR_INFO_POS_MASK      (0x7f << SPAR_INFO_POS_OFFSET)
#define ECC_MODE_OFFSET         (12)
#define ECC_MODE_MASK           (0xF << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_1BIT       (0 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_2BIT       (1 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_4BIT       (2 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_8BIT       (3 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_12BIT      (4 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_16BIT      (5 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_24BIT      (6 << ECC_MODE_OFFSET)

#define ECC_STR_SEC_IND_OFFSET  (7)
#define ECC_STR_SEC_IND_MASK    (0x1f << ECC_STR_SEC_IND_OFFSET)
#define ECC_POSITON_MASK        (0x7f)
//NFC_INT bit define
#define INT_STSMCH_RAW          (BIT_27)
#define INT_WP_RAW              (BIT_26)
#define INT_TO_RAW              (BIT_25)
#define INT_DONE_RAW            (BIT_24)
#define INT_STSMCH_STS          (BIT_19)
#define INT_WP_STS              (BIT_18)
#define INT_TO_STS              (BIT_17)
#define INT_DONE_STS            (BIT_16)

#define INT_STSMCH_CLR          (BIT_11)
#define INT_WP_CLR              (BIT_10)
#define INT_TO_CLR              (BIT_9)
#define INT_DONE_CLR            (BIT_8)

#define INT_STSMCH_EN           (BIT_3)
#define INT_WP_EN               (BIT_2)
#define INT_TO_EN               (BIT_1)
#define INT_DONE_EN             (BIT_0)


//NFC_TIMING
#define NFC_ACS_OFFSET          (27)
#define NFC_ACS_MASK            (0x1f << NFC_ACS_OFFSET)
#define NFC_ACE_OFFSET          (22)
#define NFC_ACE_MASK            (0x1f << NFC_ACE_OFFSET)
#define NFC_RWS_OFFSET          (16)
#define NFC_RWS_MASK            (0x3f << NFC_RWS_OFFSET)
#define NFC_RWE_OFFSET          (11)
#define NFC_RWE_MASK            (0x1f << NFC_RWS_OFFSET)
#define NFC_RWH_OFFSET          (6)
#define NFC_RWH_MASK            (0x1f << NFC_RWH_OFFSET)
#define NFC_RWL_MASK            (0x3f)
//NFC_TIMEOUT bit define
#define REPT_CLR_EN             (BIT_31)
#define TIMETOUT_MASK           (0x7fffffff)

//NFC_STAT_STSMCH bit define
#define NFC_STSMCH_SEL          (BIT_17)
#define NFC_STSMCH_STOP_EN      (BIT_16)
#define NFC_STSMCH_MASK_OFFSET  (8)
#define NFC_STSMCH_VALUE_MASK   (0xff)
#define ERR_ERR_NUM0_MASK       (0x3f)
//#define ECC_ERR_NUM_MASK            (0x1f)
//#define ECC_ERR_STS_SHIFT           (5)
//#define ECC_ERR_STS_MASK            (0x3 << ECC_ERR_STS_SHIFT)
#define ECC_ALL_FF                  (1 << 7)

struct sprd_ecc_param {
	u8 mode; //1, 2, 4, 8,12,16,24
	u8 ecc_num; //max is 8
	u8 sp_size; //spare part size
	u8 ecc_pos; //ecc postion
	u8 sinfo_pos;
	u8 sinfo_size;
	u16 m_size;// main part size;
	u8 *p_mbuf;
	u8 *p_sbuf;
	u8 *sts;
};
unsigned int sprd_ecc_encode(struct sprd_ecc_param *param);
#endif

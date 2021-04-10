#ifndef _SDRAM_H_
#define _SDRAM_H_

/*
#define EMC_BASEADDR 0x20000000
#define EMC_CFG0  0x20000000

#define DMEM_CFG0   (EMC_BASEADDR + 0x40)
*/
#ifndef NAND_FDL_SC8800H
#define DCFG0_DQM_MODE_LOW             0           //DQM low in deactive
#define DCFG0_DQM_MODE_W0R0            1           //DQM hihe in deactive,Write: 0 cycle delay; Read: 0 cycle delay;
#define DCFG0_DQM_MODE_W0R1            2           //DQM hihe in deactive,Write: 0 cycle delay; Read: 1 cycle delay;
#define DCFG0_DQM_MODE_W0R2            3           //DQM hihe in deactive,Write: 0 cycle delay; Read: 2 cycle delay;

#define DCFG0_DQM_TERM_EN              (1u << 2)
#define DCFG0_DQM_FORCE_HIGH           (1u << 3)

#define DCFG0_BKPOS_HADDR3             (0u << 4)
#define DCFG0_BKPOS_HADDR4             (1u << 4)
#define DCFG0_BKPOS_HADDR5             (2u << 4)
#define DCFG0_BKPOS_HADDR6             (3u << 4)
#define DCFG0_BKPOS_HADDR8             (4u << 4)
#define DCFG0_BKPOS_HADDR10             (5u << 4)
#define DCFG0_BKPOS_HADDR13             (6u << 4)
#define DCFG0_BKPOS_HADDR16             (7u << 4)
#define DCFG0_BKPOS_HADDR18             (8u << 4)
#define DCFG0_BKPOS_HADDR20             (9u << 4)
#define DCFG0_BKPOS_HADDR22             (10u << 4)
#define DCFG0_BKPOS_HADDR23             (11u << 4)
#define DCFG0_BKPOS_HADDR24             (12u << 4)
#define DCFG0_BKPOS_HADDR25             (13u << 4)
#define DCFG0_BKPOS_HADDR26             (14u << 4)
#define DCFG0_BKPOS_HADDR28             (15u << 4)

#define DCFG0_BKMODE_1                (0u << 8)
#define DCFG0_BKMODE_2                (1u << 8)
#define DCFG0_BKMODE_4                (2u << 8)
#define DCFG0_BKMODE_8                (3u << 8)

#define DCFG0_ROWMODE_11              (0u << 10)
#define DCFG0_ROWMODE_12              (1u << 10)
#define DCFG0_ROWMODE_13              (2u << 10)

#define DCFG0_COLMODE_8               (0u << 12)
#define DCFG0_COLMODE_9               (1u << 12)
#define DCFG0_COLMODE_10               (2u << 12)
#define DCFG0_COLMODE_11               (3u << 12)
#define DCFG0_COLMODE_12               (4u << 12)

#define DCFG0_DWIDTH_16               (0u << 15)
#define DCFG0_DWIDTH_32               (1u << 15)

#define DCFG0_BL_2                    (1u << 16)
#define DCFG0_BL_4                    (2u << 16)
#define DCFG0_BL_8                    (3u << 16)
#define DCFG0_BL_16                   (4u << 16)
#define DCFG0_BL_FULLPAGE             (7u << 16)

#define DCFG0_AUTOREF_ALLCS           (1u << 19)

#define DCFG0_RL_2                    (2u << 20)
#define DCFG0_RL_3                    (3u << 20)
#define DCFG0_RL_4                    (4u << 20)
#define DCFG0_RL_5                    (5u << 20)
#define DCFG0_RL_6                    (6u << 20)
#define DCFG0_RL_7                    (7u << 20)

#define DCFG0_AUTOREF_EN              (BIT_23)

#define DCFG0_T_RW_0                  (0u << 29)
#define DCFG0_T_RW_1                  (1u << 29)

#define DCFG0_ALTERNATIVE_EN          (1u << 30)
#define DCFG0_ROWHIT_EN               (1u << 31)
#else
#define DCFG0_BKPOS_HADDR_6_5           0
#define DCFG0_BKPOS_HADDR_11_10         1
#define DCFG0_BKPOS_HEADR_16_15         2
#define DCFG0_BKPOS_HADDR_21_20         3
#define DCFG0_BKPOS_HADDR_23_22         4
#define DCFG0_BKPOS_HADDR_24_23         5
#define DCFG0_BKPOS_HADDR_25_24         6
#define DCFG0_BKPOS_HEADR_26_25         7

#define DCFG0_AUTO_PRE_POSITION_A10     (0u << 6)
#define DCFG0_AUTO_PRE_POSITION_A11     (1u << 6)
#define DCFG0_AUTO_PRE_POSITION_A12     (2u << 6)
#define DCFG0_AUTO_PRE_POSITION_A13     (3u << 6)

#define DCFG0_CLKDMEM_OUT_EN            (BIT_14)
#define DCFG0_CLKDMEM_OUT_SEL           (BIT_15)
#define DCFG0_ALTERNATIVE_EN            (BIT_16)
#define DCFG0_ROWHIT_EN                 (BIT_17)
#define DCFG0_AUTOREF_EN                (BIT_18)
#define DCFG0_AUTO_REF_ALLCS            (BIT_19)



#define DCFG2_CNT_DONE                  (BIT_14)
#define DCFG2_REF_CNT_RST               (BIT_15)
#define DCFG2_AUTO_SLEEP_MODE           (BIT_22)
#define DCFG2_AUTO_SLEEP_EN             (BIT_23)
#define DCFG2_SAMPLE_RST                (BIT_24)
#define DCFG2_SAMPLE_AUTO_RST_EN        (BIT_25)
#endif
//define mode register domain..
#define MODE_REG_BL_2               (1)
#define MODE_REG_BL_4               (2)
#define MODE_REG_BL_8               (3)

#define MODE_REG_BT_SEQ               (0)
#define MODE_REG_BT_INT               (1)

#define MODE_REG_CL_1                 (1)
#define MODE_REG_CL_2                 (2)
#define MODE_REG_CL_3                 (3)

#define MODE_REG_OPMODE               (0)

#define MODE_REG_WB_PRORAM            (0)
#define MODE_REG_WB_SINGLE            (1)

//define extended mode register domain...
#define EX_MODE_REG_PASR_4_BANKS      (0)
#define EX_MODE_REG_PASR_2_BANKS      (1)
#define EX_MODE_REG_PASR_1_BANKS      (2)
#define EX_MODE_REG_PASR_HALF_BANK      (5)
#define EX_MODE_REG_PASR_QUART_BANK      (6)  

#define EX_MODE_REG_DS_FULL           (0)
#define EX_MODE_REG_DS_HALF           (1)            


#endif



#ifndef _SPRD_NAND_H_
#define _SPRD_NAND_H_

#define init_waitqueue_head(...)	do { } while (0)
#define wait_event_interruptible(...)	0
#define wake_up_interruptible(...)	do { } while (0)
#define print_hex_dump(...)		do { } while (0)
#define dump_stack(...)			do { } while (0)




//NFC_START bit define
#define NFC_VALID                   (1 << 31)
#define NFC_RBN                     (1 << 30)
#define NFC_RBN_CNT_OFFSET          (28)
#define NFC_RBN_CNT_MASK            (0x3 << NFC_RBN_CNT_OFFSET)
#define NFC_ONLY_START              (1 << 3)
#define NFC_CMD_CLR                 (1 << 1)
#define NFC_START                   (1 << 0)
#define ECC_MODE_OFFSET             (11) //this offset is significent
#define ECC_MODE_MASK               (0x7 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_1BIT           (0 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_2BIT           (1 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_4BIT           (2 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_8BIT           (3 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_12BIT          (4 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_16BIT          (5 << ECC_MODE_OFFSET)
#define NFC_ECC_MODE_24BIT          (6 << ECC_MODE_OFFSET)


//NFC_CFG0 bit define
#define MAST_ENDIAN_OFFSET          (30)
#define MAST_ENDIAN_MASK            (0x3 << MAST_ENDIAN_OFFSET)
#define CS_SEL                      (1 << 0)
#define SECTOR_NUM_OFFSET           (24)
#define SECTOR_NUM_MASK             (0x1f << SECTOR_NUM_OFFSET)
#define REPEAT_NUM_OFFSET           (16)
#define REPEAT_NUM_MASK             (0xff << REPEAT_NUM_OFFSET)
#define NFC_WPN                     (1 << 15)
#define BUS_WIDTH                   (1 << 14)
#define SPAR_DLEN_CFG               (1 << 13)
#define SECNUM_IN_INST              (1 << 12)
#define DETECT_ALL_FF               (1 << 11)
#define NFC_RW                      (1 << 8)
#define MAIN_SPAR_APT               (1 << 6)
#define SPAR_USE                    (1 << 5)
#define MAIN_USE                    (1 << 4)
#define ECC_EN                      (1 << 2)
#define NFC_MODE_MASK               (0x3)
#define NFC_AUTO_MODE               (0x0)
#define NFC_ONLY_MST_MODE           (0x1)
#define NFC_ONLY_NAND_MODE          (0x2)
#define NFC_ONLY_ECC_MODE           (0x3)
//NFC_CFG1 bit define
#define SPAR_INFO_SIZE_OFFSET       (24)
#define SPAR_INFO_SIZE_MASK         (0x3f << SPAR_INFO_SIZE_OFFSET)
#define SPAR_SIZE_OFFSET            (16)
#define SPAR_SIZE_MASK              (0x7F << SPAR_SIZE_OFFSET)
#define MAIN_SIZE_MASK              (0x3ff)
//NFC_CFG2 bit define
#define SPAR_SECTOR_NUM_OFFSET      (24)
#define SPAR_SECTOR_NUM_MASK        (0x1f << SPAR_SECTOR_NUM_OFFSET)
#define SPAR_INFO_POS_OFFSET        (16)
#define SPAR_INFO_POS_MASK          (0x7f << SPAR_INFO_POS_OFFSET)


#define ECC_STR_SEC_IND_OFFSET      (8)
#define ECC_STR_SEC_IND_MASK        (0x1f << ECC_STR_SEC_IND_OFFSET)
#define ECC_POSITON_MASK            (0x7f)
//NFC_INT bit define
#define INT_STSMCH_RAW              (1 << 27)
#define INT_WP_RAW                  (1 << 26)
#define INT_TO_RAW                  (1 << 25)
#define INT_DONE_RAW                (1 << 24)
#define INT_STSMCH_STS              (1 << 19)
#define INT_WP_STS                  (1 << 18)
#define INT_TO_STS                  (1 << 17)
#define INT_DONE_STS                (1 << 16)

#define INT_STSMCH_CLR              (1 << 11)
#define INT_WP_CLR                  (1 << 10)
#define INT_TO_CLR                  (1 << 9)
#define INT_DONE_CLR                (1 << 8)

#define INT_STSMCH_EN               (1 << 3)
#define INT_WP_EN                   (1 << 2)
#define INT_TO_EN                   (1 << 1)
#define INT_DONE_EN                 (1 << 0)

typedef struct {
	uint8_t *m_buf;
	uint8_t *s_buf;
	uint8_t m_sct;
	uint8_t s_sct;
	uint8_t dir; //if dir is 0, read dadta from NFC buffer, if 1, write data to NFC buffer
	uint16_t m_size;
	uint16_t s_size;
} sprd_dolphin_nand_data_param;




#define BOOTLOADER_HEADER_OFFSET    32
#define CONFIG_SYS_SPL_ECC_POS    8
#define NAND_BOOT_MAGIC_DATA   (0x42544844)
#define NAND_BOOT_HEADER_VER	  (0x1)
#define BL_HASH_BYTE_LEN  32
struct bootloader_header
{
	uint32_t magic_num; //0xaa55a5a5
	uint32_t version; //version
	uint8_t  mpayloadhash[BL_HASH_BYTE_LEN];
	uint64_t image_addr;
	uint32_t image_size;
	uint32_t reserved[70];/* 512 - (4 * 2 + 32 + 4 * 2 + 4) */
	uint32_t sct_size; //
	uint32_t acycle; // 3, 4, 5
	uint32_t mRandAcyCle;
	uint32_t bus_width; //0 ,1
	uint32_t spare_size; //spare part sise for one sector
	uint32_t ecc_mode; //0--1bit, 1--2bit,2--4bit,3--8bit,4--12bit, 5--16bit, 6--24bit
	uint32_t ecc_pos; // ecc postion at spare part
	uint32_t sct_per_page; //sector per page
	uint32_t info_pos;
	uint32_t info_size;
	uint32_t ecc_value[27];
	uint32_t mBlkShift;
	uint32_t mPageShift;
       uint32_t img_page[5];
};


#define __32reg_read(reg) 		readl(reg)
#define __32reg_write(reg, val) writel((val),(reg))

#define NFC_REG_BASE				(this->ioaddr)
/*reg memory map --checked*/
#define NFC_START_REG				(NFC_REG_BASE + 0x00)
#define NFC_CFG0_REG				(NFC_REG_BASE + 0x04)
#define NFC_CFG1_REG				(NFC_REG_BASE + 0x08)
#define NFC_CFG2_REG				(NFC_REG_BASE + 0x0C)

#define NFC_POLY0_REG				(NFC_REG_BASE + 0xB0)
#define NFC_POLY1_REG				(NFC_REG_BASE + 0xB4)
#define NFC_POLY2_REG				(NFC_REG_BASE + 0xB8)
#define NFC_POLY3_REG				(NFC_REG_BASE + 0xBC)
#define NFC_POLY4_REG				(NFC_REG_BASE + 0x60)
#define NFC_POLY5_REG				(NFC_REG_BASE + 0x64)
#define NFC_POLY6_REG				(NFC_REG_BASE + 0x68)
#define NFC_POLY7_REG				(NFC_REG_BASE + 0x6c)


#define NFC_DLL0_REG					(NFC_REG_BASE + 0xE0)
#define NFC_DLL1_REG					(NFC_REG_BASE + 0xE4)
#define NFC_DLL2_REG					(NFC_REG_BASE + 0xE8)
#define NFC_DLL_REG						(NFC_REG_BASE + 0xEC)


#define NFC_PHY_REG					(NFC_REG_BASE + 0xdc)
#define NFC_CFG4_REG				(NFC_REG_BASE + 0xf8)

#define NFC_INT_REG					(NFC_REG_BASE + 0x10)
#define NFC_TIMING0_REG				(NFC_REG_BASE + 0x14)
#define NFC_TIMING1_REG				(NFC_REG_BASE + 0x18)
#define NFC_TIMING2_REG				(NFC_REG_BASE + 0x1C)


#define NFC_MAIN_ADDRH_REG			(NFC_REG_BASE + 0x200)
#define NFC_MAIN_ADDRL_REG			(NFC_REG_BASE + 0x204)

#define NFC_SPAR_ADDRH_REG			(NFC_REG_BASE + 0x208)
#define NFC_SPAR_ADDRL_REG			(NFC_REG_BASE + 0x20C)

#define NFC_STAT_ADDRH_REG			(NFC_REG_BASE + 0x210)
#define NFC_STAT_ADDRL_REG			(NFC_REG_BASE + 0x214)

#define NFC_SEED_ADDRH_REG			(NFC_REG_BASE + 0x218)
#define NFC_SEED_ADDRL_REG			(NFC_REG_BASE + 0x21C)

#define NFC_STAT_STSMCH_REG			(NFC_REG_BASE + 0x30)
#define NFC_TIMEOUT_REG				(NFC_REG_BASE + 0x34)
#define NFC_CFG3_REG				(NFC_REG_BASE + 0x38)
#define NFC_STATUS0_REG				(NFC_REG_BASE + 0x40)
#define NFC_STATUS1_REG				(NFC_REG_BASE + 0x44)
#define NFC_STATUS2_REG				(NFC_REG_BASE + 0x48)
#define NFC_STATUS3_REG				(NFC_REG_BASE + 0x4C)
#define NFC_STATUS4_REG				(NFC_REG_BASE + 0x50)
#define NFC_STATUS5_REG				(NFC_REG_BASE + 0x54)
#define NFC_STATUS6_REG				(NFC_REG_BASE + 0x58)
#define NFC_STATUS7_REG				(NFC_REG_BASE + 0x5C)



#define NFC_INST0_REG				(NFC_REG_BASE + 0x220)
#define NFC_MAX_MC_INST_NUM			(24)

/*NFC_START bit define --checked*/
#define _CTRL_NFC_VALID				(1 << 31)
#define _CTRL_unused_NFC_RBN		(1 << 30)
#define _CTRL_unused_NFC_RBN_CNT	(0x3<<28)
#define _CTRL_NFC_CMD_CLR			(1 << 1)
#define _CTRL_NFC_CMD_START			(1 << 0)
#define _START_DEF1_ECC_MODE(mode)			(((mode)&0xF)<<11)

/*NFC_CFG0 bit define --checked*/
#define _CFG0_DEF0_MAST_ENDIAN					(0)
#define _CFG0_DEF1_SECT_NUM(num)				(((num-1)&0x1F)<<24)
#define _CFG0_temp_SECT_NUM_MSK					(0x1F<<24)
#define _CFG0_SET_REPEAT_NUM(num)				(((num-1)&0xFF)<<16)
#define _CFG0_SET_WPN							(1<<15)
#define _CFG0_DEF1_BUS_WIDTH(width)				(((!!(width!=BW_08))&0x1)<<14)
#define _CFG0_SET_SPARE_ONLY_INFO_PROD_EN		(1<<13)
#define _CFG0_DEF0_SECT_NUM_IN_INST				(0<<12)
#define _CFG0_DEF0_DETECT_ALL_FF				(1<<11)
#define _CFG0_SET_CS_SEL(cs)					(((cs)&0x3)<<9)
#define _CFG0_CS_MAX							4
#define _CFG0_CS_MSKCLR							(~(0x3<<9))
#define _CFG0_SET_NFC_RW						(1 << 8)
#define _CFG0_DEF1_MAIN_SPAR_APT(sectPerPage)	((1==sectPerPage)?0:(1 << 6))
#define _CFG0_SET_SPAR_USE						(1 << 5)
#define _CFG0_SET_MAIN_USE						(1 << 4)
#define _CFG0_SET_ECC_EN						(1 << 2)
#define _CFG0_SET_NFC_MODE(mode)				((mode)&0x3)

/*NFC_CFG1 bit define --checked*/
#define _CFG1_DEF1_SPAR_INFO_SIZE(size)		(((size)&0x7F)<<24)
#define _CFG1_DEF1_SPAR_SIZE(size)			((((size)-1)&0xFF)<<16)
#define _CFG1_unused_INTERNAL_CEN_EN		(0<<15)
#define _CFG1_unused_INTF_TYPE(type)		(((type)&0x07)<<12)
#define _CFG1_DEF1_MAIN_SIZE(size)			((((size)-1))&0x7FF)
#define _CFG1_temp_MIAN_SIZE_MSK			(0x7FF)

/*NFC_CFG2 bit define --checked*/
#define _CFG2_unused_ACE_HIGH_EN			(0<<30)
#define _CFG2_unused_CDQSS_HIGH_EN			(1<<29)
#define _CFG2_DEF1_SPAR_SECTOR_NUM(num)		(((num-1)&0x1F)<<24)
#define _CFG2_DEF1_SPAR_INFO_POS(pos)		(((pos)&0x7F)<<16)
#define _CFG2_nouse_ECC_STR_SEC_IND(pos)	(((pos)&0x1F)<<7)
#define _CFG2_DEF1_ECC_POSITION(pos)		((pos)&0x7F)

												/*NFC_CFG3 --checked *//*may be unused */
#define _CFG3_SEED_LOOP_CNT(cnt)			(((cnt)&0x3FF)<<16)
#define _CFG3_SEED_LOOP_EN					(1<<2)
#define _CFG3_USE_POLY4R1_SEL(sel)		(((sel)&0x1)<<1)
#define _CFG3_RANDOM_EN						(1)
#define _CFG3_DETECT_ALL_FF					(1<<3)

/*NFC_CFG2 bit define --checked*/
#define _CFG4_ONLY_SEL_MODE 					BIT_14


/* NFC register --checked*/
#define _INT_STSMCH					(0x1<<3)
#define _INT_WP						(0x1<<2)
#define _INT_TO						(0x1<<1)
#define _INT_DONE					(0x1)
#define __int_clr_all()				writel((0xF<<8),NFC_INT_REG)
#define __int_dis_all()				writel(0,NFC_INT_REG)
#define __int_en(bits)				writel((bits&0xF),NFC_INT_REG)
#define __int_sts_get()				((readl(NFC_INT_REG)>>16)&0xF)
#define __int_rawsts_get()			((readl(NFC_INT_REG)>>24)&0xF)

/*NFC_TIMING0 --checked*/
#define _TIME0_ACS(acs)				(((acs-1)&0x1F)<<27)
#define _TIME0_ACE(ace)				(((ace-1)&0x1F)<<22)
#define _TIME0_RDS(rds)				(((rds-1)&0x3F)<<16)
#define _TIME0_RDE(rde)				(((rde-1)&0x1F)<<11)
#define _TIME0_RWH(rwh)				(((rwh-1)&0x1F)<<6)
#define _TIME0_RWL(rwl)				((rwl-1)&0x3F)	/*must >= 2 */

							/*NFC_TIMING1 --checked *//*may be unused */
#define NFC_ACS_OFFSET              (27)
#define NFC_ACS_MASK                (0x1f << NFC_ACS_OFFSET)
#define NFC_ACE_OFFSET              (22)
#define NFC_ACE_MASK                (0x1f << NFC_ACE_OFFSET)
#define NFC_RWS_OFFSET              (16)
#define NFC_RWS_MASK                (0x3f << NFC_RWS_OFFSET)
#define NFC_RWE_OFFSET              (11)
#define NFC_RWE_MASK                (0x3f << NFC_RWS_OFFSET)
#define NFC_RWH_OFFSET              (6)
#define NFC_RWH_MASK                (0x1f << NFC_RWH_OFFSET)
#define NFC_RWL_MASK                (0x3f)

#define _TIME1_WTE(wte)				(((wte-1)&0x1F)<<26)
#define _TIME1_WTS(wts)				(((wts-1)&0x1F)<<21)
#define _TIME1_WTI(wti)				(((wti-1)&0x1F)<<16)
#define _TIME1_CL0(cl0)				(((cl0-1)&0x1F)<<10)
#define _TIME1_CL1(cl1)				(((cl1-1)&0x1F)<<5)
#define _TIME1_RDI(rdi)				(((rdi-1)&0x1F)<<0)
/*NFC_TIMING2 --checked*/
#define _TIME2_unused_DQS_FORCE_HIGH	(0<<2)	/*??? */
#define _TIME2_unused_RD_POINT_IND		(0<<1)	/*??? */
#define _TIME2_unused_RD_POINT_SEL		(0)	/*??? */
/*NFC_TIMEOUT bit define --checked*/
#define _TIMEOUT_REPT_EN			(1<<31)
#define _TIMEOUT(val)				(val&0x7FFFFFFF)
/* NFC Ram address --checked*/
#define _RAM_MAIN_ADDR(addr)		((uint32_t)(addr))	/* 0xFFFF'FFFF means not to move data to read buf, when read. */
#define _RAM_SPAR_ADDR(addr)		((uint32_t)(addr))	/* 0xFFFF'FFFF means not to move data to read buf, when read. */
#define _RAM_STAT_ADDR(addr)		((uint32_t)(addr))	/* 0xFFFF'FFFF means not to move data to read buf, when read. */
#define _RAM_SEED_ADDR(addr)		((uint32_t)(addr))
/*NFC status mach --checked*/
#define _MACH_ERASE					((1)|(1<<11)|(1<<22))	// check IO 0_bit, stop if error
#define _MACH_WRITE					((1)|(1<<11)|(1<<22))	// check IO 0_bit, stop if error
#define _MACH_READ					(0)	// no check
#define _DEF0_MATCH					(0)
/*NFC_STATUS0_REG bit define --checked*/
#define _ECC_STAT(status)			(((status)>>9)&0x3)
#define _ECC_NUM(status)			((status)&0x1FF)
/*NFC Micro-Instrction Register --checked*/
#define __CMD_TYPE1(cmdId,param)			((uint16_t)(((param & 0xff) << 8) | (cmdId & 0xff)))
#define __CMD_TYPE2(cmdId)					((uint16_t)(cmdId & 0xff))
#define __CMD_TYPE3(cmdId,param1,param0)	((uint16_t)(((param1 & 0xff) << 8) | ((cmdId & 0xf) << 4)|(param0 & 0xf)))
#define _INST_CMD(cmd)			__CMD_TYPE1(0xCD,(cmd))
#define _INST_ADDR(addr,step)	__CMD_TYPE3(0x0A,(addr),(step))
#define _INST_WRB0()			__CMD_TYPE2(0xB0)
#define _INST_WRB1(cycle)		__CMD_TYPE1(0xB1,(cycle))
#define _INST_MRDT()			__CMD_TYPE2(0xD0)	// SECNUM_IN_INST == 0
#define _INST_MWDT()			__CMD_TYPE2(0xD1)	// SECNUM_IN_INST == 0
#define _INST_SRDT()			__CMD_TYPE2(0xD2)	// SECNUM_IN_INST == 0
#define _INST_SWDT()			__CMD_TYPE2(0xD3)	// SECNUM_IN_INST == 0
#define _INST_IDST(num)			__CMD_TYPE1(0xDD,(num-1))
#define _INST_CSEN(en)			__CMD_TYPE1(0xCE,(en))	// 0 or 1, priority > _CFG0_CS_SEL
#define _INST_INOP(num)			__CMD_TYPE1(0xF0,(num-1))
#define _INST_DONE()			__CMD_TYPE2(0xFF)
// Other define
#define NFC_MAX_CHIP				4
#define NFC_TIMEOUT_VAL				3000000	//usecs
#define NFC_DEFAULT_TIMING			((7)  | (6 << NFC_RWH_OFFSET) | (7 << NFC_RWE_OFFSET) | (7 << NFC_RWS_OFFSET) | (7 << NFC_ACE_OFFSET) | (7 << NFC_ACS_OFFSET))
#define NFC_MBUF_SIZE				(16<<10)
/* TODO : use global interface */
#define AHB_SOFT_NFC_RST			(1 << 5)
#define SPRD_NFC_AHB_RST  (SPRD_AHB_BASE + 0x0004)
#define SPRD_NFC_CLK_CFG  (SPRD_AHB_BASE + 0x0060)
#define DOLPHIN_ADISLAVE_BASE	 	SPRD_ADISLAVE_BASE
#define DOLPHIN_ANA_CTL_GLB_BASE		(DOLPHIN_ADISLAVE_BASE + 0x8800)
#define SPRD_NFC_REG_BASE  SPRD_NFC_BASE
#define SPRD_NFC_TIMING_REG  (SPRD_NFC_REG_BASE + 0x14)
#define SPRD_NFC_TIMEOUT_REG  (SPRD_NFC_REG_BASE + 0x34)
struct nand_ecc_stats {
	__u16 ecc_stats[16];
	__u32 layout4_ecc_stats;
	__u32 freecount[5];
};

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

#endif


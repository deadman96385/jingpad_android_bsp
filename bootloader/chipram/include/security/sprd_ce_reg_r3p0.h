/*
* Copyright (c) 2016, Spreadtrum Communications.
*
* The above copyright notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#ifndef SPRD_CE_REG_H
#define SPRD_CE_REG_H
#include <asm/arch/sprd_reg.h>

/* device base physical address */
//#define SPRD_AHB_BASE    		0x20E00000
//#define SPRD_PCE_BASE    		0x21300000//public
//#define SPRD_SCE_BASE    		0x21400000//secure

/* registers definitions for AP_AHB_RF */
//#define REG_AP_AHB_AHB_EB		(0x0000)/*AHB_EB*/
//#define REG_AP_AHB_AHB_RST		(0x0004)/*AHB_RST*/
#define REG_AP_AHB_AHB_EB_OFFSET	(REG_AP_AHB_AHB_EB & 0xFFFF)
#define REG_AP_AHB_AHB_RST_OFFSET	(REG_AP_AHB_AHB_RST & 0xFFFF)

/* bits definitions for register REG_AP_AHB_RF_AHB_EB */
//#define BIT_AP_AHB_CE_PUB_EB		( BIT(6) )
//#define BIT_AP_AHB_CE_SEC_EB		( BIT(12) )

/* bits definitions for register REG_AP_AHB_RF_AHB_RST */
//#define BIT_AP_AHB_CE_PUB_SOFT_RST	( BIT(9) )
//#define BIT_AP_AHB_CE_SEC_SOFT_RST	( BIT(15) )

/* CE interrupt vector */
//#define INT_REQ_AP_PCE		(54 + 32)
//#define INT_REQ_AP_SCE		(53 + 32)

#define CE_CLK_EN			(0x18)
#define CE_INT_EN			(0x1C)
#define CE_INT_STATUS			(0x20)
#define CE_INT_CLEAR			(0x24)
#define CE_START			(0x28)
#define CE_CLEAR			(0x2c)
#define CE_AES_MODE			(0x30)
#define CE_TDES_MODE			(0x34)
#define CE_HASH_MODE			(0x38)
#define CE_CFG				(0x44)
#define CE_SRC_FLAG_LEN			(0x48)
#define CE_PKA_CMD_FLAG_LEN		(0x48)
#define CE_DST_FLAG_LEN			(0x4C)
#define CE_SRC_ADDR			(0x50)
#define CE_PKA_INSTR_ADDR		(0x50)
#define CE_DST_ADDR			(0x54)
#define CE_PKA_STORE_ADDR_HI		(0x54)
//#define CE_LIST_LEN 			(0x58)
//#define CE_LIST_PTR 			(0x5C)
#define CE_ATR_KEY_LEN			(0x60)
#define CE_ATR_KEY_ADDR			(0x64)
#define CE_PKA_LOAD_ADDR_HI		(0x64)
#define CE_AES_TAG_LEN			(0x68)
//#define CE_AES_MAC_MLEN		(0x6c)
#define CE_AES_TAG_ADDR			(0x6c)
#define CE_IV_SEC_CNT0			(0x70)
#define CE_IV_SEC_CNT1			(0x74)
#define CE_IV_SEC_CNT2			(0x78)
#define CE_IV_SEC_CNT3			(0x7C)
#define CE_AES_DES_KEY10		(0x80)
#define CE_AES_DES_KEY11		(0x84)
#define CE_AES_DES_KEY12		(0x88)
#define CE_AES_DES_KEY13		(0x8C)
#define CE_AES_DES_KEY14		(0x90)
#define CE_AES_DES_KEY15		(0x94)
#define CE_AES_DES_KEY16		(0x98)
#define CE_AES_DES_KEY17		(0x9C)
#define CE_AES_DES_KEY20		(0xA0)
#define CE_AES_DES_KEY21		(0xA4)
#define CE_AES_DES_KEY22		(0xA8)
#define CE_AES_DES_KEY23		(0xAC)
#define CE_AES_DES_KEY24		(0xB0)
#define CE_AES_DES_KEY25		(0xB4)
#define CE_AES_DES_KEY26		(0xB8)
#define CE_AES_DES_KEY27		(0xBC)
#define CE_SM4_MODE			(0xC0)
#define CE_RC4_MODE			(0xC4)
#define CE_IP_VERSION			(0xC8)
#define CE_PKA_MODE			(0xCC)
#define CE_PKA_REG_LEN01		(0xD0)
#define CE_PKA_REG_LEN23		(0xD4)
//#define CE_PKA_REG_LEN45		(0xD8)
//#define CE_PKA_REG_LEN67		(0xDC)
//#define CE_PKA_REG_LEN89		(0xE0)
//#define CE_PKA_REG_LENAB		(0xE4)
//#define CE_PKA_REG_LENCD		(0xE8)
//#define CE_PKA_REG_LENEF		(0xEC)
//#define CE_PKA_RAM_START_ADDR0	(0x0f0)
//#define CE_PKA_RAM_START_ADDR1	(0x0f4)
//#define CE_PKA_RAM_START_ADDR2	(0x0f8)
//#define CE_PKA_RAM_START_ADDR3	(0x0fc)
//#define CE_PKA_RAM_START_ADDR4	(0x100)
//#define CE_PKA_RAM_START_ADDR5	(0x104)
//#define CE_PKA_RAM_START_ADDR06	(0x108)
//#define CE_PKA_RAM_START_ADDR7	(0x10c)
//#define CE_PKA_RAM_START_ADDR8	(0x110)
//#define CE_PKA_RAM_START_ADDR9	(0x114)
//#define CE_PKA_RAM_START_ADDR10	(0x118)
//#define CE_PKA_RAM_START_ADDR11	(0x11c)
//#define CE_PKA_RAM_START_ADDR12	(0x120)
//#define CE_PKA_RAM_START_ADDR13	(0x124)
//#define CE_PKA_RAM_START_ADDR14	(0x128)
//#define CE_PKA_RAM_START_ADDR15	(0x12c)
#define CE_PKA_INST_PC			(0x130)
//#define CE_PKA_DEBUG0			(0x134)
//#define CE_PKA_DEBUG1			(0x138)
//#define CE_PKA_DEBUG2			(0x13c)
//#define CE_PKA_DEBUG3			(0x140)

#define CE_PERF_CNT			(0X150)
#define CE_CMD_STOP_CTRL		(0X15C)

#define CE_RNG_EN			(0x200)
#define CE_RNG_CONFIG			(0x204)
#define CE_RNG_DATA			(0x208)
#define CE_RNG_POST_PROCESS_EN		(0x210)
#define CE_RNG_WORK_STATUS		(0x214)
#define CE_RNG_MODE			(0x228)
//#define CE_PRNG_SEED_UPDATE		(0x22C)
//#define CE_PRNG_SEED_CONFIG		(0x230)
#define CE_RNG_BIT_RATE			(0x234)
#define CE_RNG_DATA_THRESHHOLD		(0x238)
#define CE_RNG_DATA_RESIDUE_NUM		(0x23C)
#define CE_RNG_EXOTIC_FAULT_COUNTER	(0x240)

#define CE_SESSION_KEY0			(0x300)
#define CE_SESSION_KEY1			(0x304)
#define CE_SESSION_KEY2			(0x308)
#define CE_SESSION_KEY3			(0x30C)
#define CE_SESSION_KEY4			(0x310)
#define CE_SESSION_KEY5			(0x314)
#define CE_SESSION_KEY6			(0x318)
#define CE_SESSION_KEY7			(0x31C)
#define CE_IRAM_KEY0			(0x320)
#define CE_IRAM_KEY1			(0x324)
#define CE_IRAM_KEY2			(0x328)
#define CE_IRAM_KEY3			(0x32C)
#define CE_IRAM_KEY4			(0x330)
#define CE_IRAM_KEY5			(0x334)
#define CE_IRAM_KEY6			(0x338)
#define CE_IRAM_KEY7			(0x33C)
#define CE_SEC_KEY_WORK_MODE		(0x340)
#define CE_SEC_SNYC_ADDR		(0x344)
#define	CE_SECURE_KEY_INDEX0		(0x400)
#define	CE_SECURE_KEY_INDEX1		(0x404)
#define	CE_SECURE_KEY_INDEX2		(0x408)
#define	CE_SECURE_KEY_INDEX3		(0x40C)
#define	CE_SECURE_KEY_INDEX4		(0x410)
#define	CE_SECURE_KEY_INDEX5		(0x414)
#define	CE_SECURE_KEY_INDEX6		(0x418)
#define	CE_SECURE_KEY_INDEX7		(0x41C)
#define	CE_SECURE_KEY_INDEX8		(0x420)
#define	CE_SECURE_KEY_INDEX9		(0x424)
#define	CE_SECURE_KEY_INDEX10		(0x428)
#define	CE_SECURE_KEY_INDEX11		(0x42C)
#define	CE_SECURE_KEY_INDEX12		(0x430)
#define	CE_SECURE_KEY_INDEX13		(0x434)
#define	CE_SECURE_KEY_INDEX14		(0x438)
#define	CE_SECURE_KEY_INDEX15		(0x43C)
#define CE_SECURE_KEY_INDEX16		(0x440)
#define CE_SECURE_KEY_INDEX17		(0x444)
#define CE_SECURE_KEY_INDEX18		(0x448)
#define CE_SECURE_KEY_INDEX19		(0x44C)
#define CE_SECURE_KEY_INDEX20		(0x450)
#define CE_SECURE_KEY_INDEX21		(0x454)
#define CE_SECURE_KEY_INDEX22		(0x458)
#define CE_SECURE_KEY_INDEX23		(0x45C)
#define	CE_SECURE_KEY_INDEX24		(0x460)
#define	CE_SECURE_KEY_INDEX25		(0x464)
#define	CE_SECURE_KEY_INDEX26		(0x468)
#define	CE_SECURE_KEY_INDEX27		(0x46C)
#define	CE_SECURE_KEY_INDEX28		(0x470)
#define	CE_SECURE_KEY_INDEX29		(0x474)
#define	CE_SECURE_KEY_INDEX30		(0x478)
#define	CE_SECURE_KEY_INDEX31		(0x47C)
#define	CE_SECURE_KEY_INDEX32		(0x480)
#define	CE_SECURE_KEY_INDEX33		(0x484)
#define	CE_SECURE_KEY_INDEX34		(0x488)
#define	CE_SECURE_KEY_INDEX35		(0x48C)
#define	CE_SECURE_KEY_INDEX36		(0x490)
#define	CE_SECURE_KEY_INDEX37		(0x494)
#define	CE_SECURE_KEY_INDEX38		(0x498)
#define	CE_SECURE_KEY_INDEX39		(0x49C)
#define	CE_SECURE_KEY_INDEX40		(0x4A0)
#define	CE_SECURE_KEY_INDEX41		(0x4A4)
#define	CE_SECURE_KEY_INDEX42		(0x4A8)
#define	CE_SECURE_KEY_INDEX43		(0x4AC)
#define	CE_SECURE_KEY_INDEX44		(0x4B0)
#define	CE_SECURE_KEY_INDEX45		(0x4B4)
#define	CE_SECURE_KEY_INDEX46		(0x4B8)
#define	CE_SECURE_KEY_INDEX47		(0x4BC)
#define	CE_SECURE_KEY_INDEX48		(0x4C0)
#define	CE_SECURE_KEY_INDEX49		(0x4C4)
#define	CE_SECURE_KEY_INDEX50		(0x4C8)
#define	CE_SECURE_KEY_INDEX51		(0x4CC)
#define	CE_SECURE_KEY_INDEX52		(0x4D0)
#define	CE_SECURE_KEY_INDEX53		(0x4D4)
#define	CE_SECURE_KEY_INDEX54		(0x4D8)
#define	CE_SECURE_KEY_INDEX55		(0x4DC)
#define	CE_SECURE_KEY_INDEX56		(0x4E0)
#define	CE_SECURE_KEY_INDEX57		(0x4E4)
#define	CE_SECURE_KEY_INDEX58		(0x4E8)
#define	CE_SECURE_KEY_INDEX59		(0x4EC)
#define	CE_SECURE_KEY_INDEX60		(0x4F0)
#define	CE_SECURE_KEY_INDEX61		(0x4F4)
#define	CE_SECURE_KEY_INDEX62		(0x4F8)
#define	CE_SECURE_KEY_INDEX63		(0x4FC)

#define CE_CMD_FIFO_ENTRY		(0x500)
#define CE_CMD_FIFO_STATUS		(0x504)
#define CE_RCV_ADDR_LO			(0x508)
#define CE_DUMP_ADDR_LO			(0x50C)
#define CE_DUMP_ADDR_HI			(0x510)
#define CE_FINISH_CMD_CNT		(0x514)

/* 112 words*/
#define CE_CMD_FIFO_LEN			(109)

/*
 * CE_START				(0x28)
 */
#define CE_START_EN			BIT(0)

/*
 * CE_CLEAR				(0x2c)
 */
#define CE_CLEAR_EN			BIT(0)

/**
 * sec ce clk register
 * sharklj1/sharkl2 bit0: 0:26M 1:256M
 * isharkl2 bit[0:1] 0:26M 1:96M 2:192M 3:256M
 **/

#define BIT_CGM_CE0_SEL		(0x3)
#define CGM_CE0_SEL_256M	(0x3)

#endif /* SPRD_CE_REG_H */

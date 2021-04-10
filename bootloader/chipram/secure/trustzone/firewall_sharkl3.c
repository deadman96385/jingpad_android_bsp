/*
* Copyright (c) 2018, Spreadtrum Communications.
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

#include <linux/types.h>
#include <common.h>
#include <asm/arch/sprd_reg.h>
#include <security/sec_string.h>
#include <security/trustzone/trustzone.h>

#define SET_REG_OFF			0x1000
#define CLR_REG_OFF			0x2000

#define SPRD_MST_CTRL_AON_BASE		(SPRD_SEC_TZPC_PHYS + 0x5000)
#define SPRD_MST_CTRL_AP_BASE		(SPRD_SEC_TZPC_PHYS + 0x4000)
#define SPRD_SLV_FW_AON_BASE		(SPRD_SEC_TZPC_PHYS + 0x3000)
#define SPRD_SLV_FW_APCPU_BASE		(SPRD_SEC_TZPC_PHYS + 0x2000)
#define SPRD_SLV_FW_AP0_BASE		(SPRD_SEC_TZPC_PHYS + 0x0000)
#define SPRD_SLV_FW_AP1_BASE		(SPRD_SEC_TZPC_PHYS + 0x1000)
#define SPRD_REG_FW_AON_APB_BASE	(SPRD_SEC_TZPC_PHYS + 0x8000)
#define SPRD_REG_FW_AON_PMU_BASE	(SPRD_SEC_TZPC_PHYS + 0x9000)
#define SPRD_REG_FW_AON_PIN_BASE	(SPRD_SEC_TZPC_PHYS + 0xC000)
#define SPRD_REG_FW_AP_AHB_BASE		(SPRD_SEC_TZPC_PHYS + 0xA000)
#define SPRD_REG_FW_AP_APB_BASE		(SPRD_SEC_TZPC_PHYS + 0xB000)
#define SPRD_MEM_FW_AON_BASE		(SPRD_SEC_TZPC_PHYS + 0xD000)
#define SPRD_MEM_FW_PUB_BASE		(SPRD_MEM_FW_PUB_PHYS)

#define MST_ID_MAX_NUM			(128)
#define MST_ID_ARRAY_LEN		(MST_ID_MAX_NUM/32)

#define MST_CTRL_AON_RD0_OFF		(0x0000)
#define MST_CTRL_AON_WR0_OFF		(0x0004)

#define MST_CTRL_AP_RD0_OFF		(0x0000)
#define MST_CTRL_AP_WR0_OFF		(0x0004)

#define SLV_FW_AON_RD0_OFF		(0x002C)
#define SLV_FW_AON_RD1_OFF		(0x0030)
#define SLV_FW_AON_RD3_OFF		(0x0038)
#define SLV_FW_AON_RD4_OFF		(0x003C)
#define SLV_FW_AON_WR0_OFF		(0x0040)
#define SLV_FW_AON_WR1_OFF		(0x0044)
#define SLV_FW_AON_WR3_OFF		(0x004C)
#define SLV_FW_AON_WR4_OFF		(0x0050)

#define SLV_FW_AP0_RD1_OFF		(0x0018)
#define SLV_FW_AP0_WR1_OFF		(0x0020)

#define REG_FW_AON_APB_CTRL_ADDR0_OFF	(0x0038)
#define REG_FW_AON_APB_CTRL_VAL0_OFF	(0x0078)

#define REG_FW_AON_PMU_CTRL_ADDR0_OFF	(0x0058)
#define REG_FW_AON_PMU_CTRL_ADDR1_OFF	(0x005C)
#define REG_FW_AON_PMU_CTRL_ADDR2_OFF	(0x0060)
#define REG_FW_AON_PMU_CTRL_VAL0_OFF	(0x0098)
#define REG_FW_AON_PMU_CTRL_VAL1_OFF	(0x009C)
#define REG_FW_AON_PMU_CTRL_VAL2_OFF	(0x00A0)

#define REG_FW_AP_AHB_CTRL_ADDR0_OFF	(0x0010)
#define REG_FW_AP_AHB_CTRL_VAL0_OFF	(0x0050)

#define MEM_FW_SEG_OFF			(0x1000)
#define MEM_FW_SEG_LEN			(0x80)

#define AON_ADDR_SHIFT_BITS		(4)
#define PUB_ADDR_SHIFT_BITS		(12)

//master ctrl aon
#define CM4_ATTR_MASK  			BIT(25)
#define CM4_ATTR_RD 			BIT(25)	//security read  operation
#define CM4_ATTR_WR 			BIT(25)	//security write operation

//master ctrl ap
#define NAND_RD_SEC			(BIT(1)|BIT(0))
#define NAND_WR_SEC			(BIT(1)|BIT(0))

#define SDIO2_RD_SEC			(BIT(3)|BIT(2))
#define SDIO2_WR_SEC			(BIT(3)|BIT(2))

#define SDIO1_RD_SEC			(BIT(5)|BIT(4))
#define SDIO1_WR_SEC			(BIT(5)|BIT(4))

#define SDIO0_RD_SEC			(BIT(7)|BIT(6))
#define SDIO0_WR_SEC			(BIT(7)|BIT(6))

#define EMMC_RD_SEC			(BIT(9)|BIT(8))
#define EMMC_WR_SEC			(BIT(9)|BIT(8))

#define USB_RD_SEC			(BIT(11)|BIT(10))
#define USB_WR_SEC			(BIT(11)|BIT(10))

#define SCE_MST_ATTR_MASK		(BIT(13)|BIT(12))
#define SCE_MST_ATTR_RD			BIT(12)			//decided by iteself
#define SCE_MST_ATTR_WR			BIT(12)			//decided by iteself

//slave fw aon
#define SEC_GPIO_MASK			(BIT(23)|BIT(22))
#define SEC_GPIO_ATTR_RD		(0x1 << 22)		//security access only
#define SEC_GPIO_ATTR_WR		(0x1 << 22)		//security access only

#define SEC_REG_MASK			(BIT(27)|BIT(26))
#define SEC_REG_ATTR_RD			(0x1 << 26)		//security access only
#define SEC_REG_ATTR_WR			(0x1 << 26)		//security access only

#define SEC_WDG_MASK			(BIT(29)|BIT(28))
#define SEC_WDG_ATTR_RD			(0x1 << 28)		//security access only
#define SEC_WDG_ATTR_WR			(0x1 << 28)		//security access only

#define SEC_RTC_MASK			(BIT(31)|BIT(30))
#define SEC_RTC_ATTR_RD			(0x1 << 30)		//security access only
#define SEC_RTC_ATTR_WR			(0x1 << 30)		//security access only

#define SEC_TMR_MASK			(BIT(1)|BIT(0))
#define SEC_TMR_ATTR_RD			(0x1 << 0)		//security access only
#define SEC_TMR_ATTR_WR			(0x1 << 0)		//security access only

#define SEC_EIC_MASK			(BIT(13)|BIT(12))
#define SEC_EIC_ATTR_RD			(0x1 << 12)		//security access only
#define SEC_EIC_ATTR_WR			(0x1 << 12)		//security access only

#define DDR_PHY_CH1_MASK		(BIT(23)|BIT(22))
#define DDR_PHY_CH1_ATTR_RD		(BIT(23)|BIT(22))	//security/non_security accesss
#define DDR_PHY_CH1_ATTR_WR		BIT(22)			//security access only

#define DDR_PHY_CH0_MASK		(BIT(25)|BIT(24))
#define DDR_PHY_CH0_ATTR_RD		(BIT(25)|BIT(24))	//security/non_security accesss
#define DDR_PHY_CH0_ATTR_WR		BIT(24)			//security access only

#define MEM_FW_PUB_MASK			(BIT(7)|BIT(6))
#define MEM_FW_PUB_ATTR_RD		BIT(6)			//security access only
#define MEM_FW_PUB_ATTR_WR		BIT(6)			//security access only

#define DDR_ATTR_MASK			(BIT(19)|BIT(18))
#define DDR_ATTR_RD			(BIT(19)|BIT(18))	//security/non_security accesss
#define DDR_ATTR_WR			BIT(18)			//security access only

//slave fw ap0
#define SCE_SLV_ATTR_MASK		(BIT(13)|BIT(12))
#define SCE_SLV_ATTR_RD			BIT(12)			//security access only
#define SCE_SLV_ATTR_WR			BIT(12)			//security access only

// IRAM address and size
#define IRAM_PM_ADDR	0x00000000
#define IRAM_PM_SIZE	0x2000

#define IRAM_FW_ADDR	0x00015800
#define IRAM_FW_SIZE	0x1000

#define REG_READ(reg_addr,value)\
do{\
	value = *(volatile uint32_t*)(reg_addr);\
}while(0)

#define REG_WRITE(reg_addr,value)\
do{\
	*(volatile uint32_t*)(reg_addr) = (value);\
}while(0)

#define REG_OR(reg_addr,or_mask)\
do{\
	*(volatile uint32_t*)(reg_addr) |= (or_mask);\
}while(0)

#define REG_AND(reg_addr,and_mask)\
do{\
	*(volatile uint32_t*)(reg_addr) &= (and_mask);\
}while(0)

#define REG_BIT(reg_addr,bit,value)\
do{\
	*(volatile uint32_t*)(reg_addr) |= ((value)<<(bit));\
}while(0)

#define REG32(_x_)	(*(volatile uint32_t*)(_x_))

#define REG32_SET(_addr_, _mask_, _value_) \
	(REG32(_addr_) = ((REG32(_addr_) & (_mask_)) | (_value_)))

typedef struct {
	volatile uint32_t first_addr;
	volatile uint32_t last_addr;
	volatile uint32_t mst_id_rd_sec[MST_ID_ARRAY_LEN];
	volatile uint32_t mst_id_rd_nsec[MST_ID_ARRAY_LEN];
	volatile uint32_t mst_id_wr_sec[MST_ID_ARRAY_LEN];
	volatile uint32_t mst_id_wr_nsec[MST_ID_ARRAY_LEN];
} sprd_mem_seg_cfg;

typedef struct {
	volatile uint32_t first_addr;
	volatile uint32_t last_addr;
	volatile uint32_t mst_id_sec[MST_ID_ARRAY_LEN];
	volatile uint32_t mst_id_nsec[MST_ID_ARRAY_LEN];
} sprd_slv_seg_cfg;

static void nand_unsec(void)
{
	/* make emmc non-secure*/
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~NAND_RD_SEC;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~NAND_WR_SEC;
}

static void sdio_unsec(void)
{
	/* make sdio non-secure */
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~SDIO0_RD_SEC;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~SDIO0_WR_SEC;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~SDIO1_RD_SEC;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~SDIO1_WR_SEC;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~SDIO2_RD_SEC;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~SDIO2_WR_SEC;
}

static void emmc_unsec(void)
{
	/* make emmc non-secure */
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~EMMC_RD_SEC;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~EMMC_WR_SEC;
}

static void usb_unsec(void)
{
	/* make usb non-secure */
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~USB_RD_SEC;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~USB_WR_SEC;
}

static void sce_sec(void)
{
	uint32_t val;

	/* set master attr */
	val = REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF);
	val &= ~SCE_MST_ATTR_MASK;
	val |= SCE_MST_ATTR_RD;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) = val;

	val = REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF);
	val &= ~SCE_MST_ATTR_MASK;
	val |= SCE_MST_ATTR_WR;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) = val;

	/* set slave attr */
	val = REG32(SPRD_SLV_FW_AP0_BASE + SLV_FW_AP0_RD1_OFF);
	val &= ~SCE_SLV_ATTR_MASK;
	val |= SCE_SLV_ATTR_RD;
	REG32(SPRD_SLV_FW_AP0_BASE + SLV_FW_AP0_RD1_OFF) = val;

	val = REG32(SPRD_SLV_FW_AP0_BASE + SLV_FW_AP0_WR1_OFF);
	val &= ~SCE_SLV_ATTR_MASK;
	val |= SCE_SLV_ATTR_WR;
	REG32(SPRD_SLV_FW_AP0_BASE + SLV_FW_AP0_WR1_OFF) = val;

	/* protect enable bit */
	REG32(SPRD_REG_FW_AP_AHB_BASE + REG_FW_AP_AHB_CTRL_ADDR0_OFF) = REG_AP_AHB_AHB_EB;
	REG32(SPRD_REG_FW_AP_AHB_BASE + REG_FW_AP_AHB_CTRL_VAL0_OFF) = BIT_AP_AHB_CE_EB;
}

static void cm4_sec(void)
{
	REG32(SPRD_MST_CTRL_AON_BASE + MST_CTRL_AON_RD0_OFF) &= ~CM4_ATTR_MASK;
	REG32(SPRD_MST_CTRL_AON_BASE + MST_CTRL_AON_RD0_OFF) |= CM4_ATTR_RD;
	REG32(SPRD_MST_CTRL_AON_BASE + MST_CTRL_AON_WR0_OFF) &= ~CM4_ATTR_MASK;
	REG32(SPRD_MST_CTRL_AON_BASE + MST_CTRL_AON_WR0_OFF) |= CM4_ATTR_WR;
}

static void mem_fw_pub_sec(void)
{
	uint32_t val;

	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD4_OFF);
	val &= ~MEM_FW_PUB_MASK;
	val |= MEM_FW_PUB_ATTR_RD;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD4_OFF) = val;

	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR4_OFF);
	val &= ~MEM_FW_PUB_MASK;
	val |= MEM_FW_PUB_ATTR_WR;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR4_OFF) = val;
}

static void iram_sec (void)
{
	uint32_t i;
	sprd_mem_seg_cfg *mem_seg_addr;

	/* iram 0x0000 ~ 0x1FFF secure read/write */
	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_AON_BASE + MEM_FW_SEG_OFF));
	REG_WRITE(&(mem_seg_addr->first_addr), 0xFFFFFFFF);
	for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
		REG_WRITE(&(mem_seg_addr->mst_id_rd_sec[i]), 0xFFFFFFFF);
		REG_WRITE(&(mem_seg_addr->mst_id_rd_nsec[i]), 0x0);
		REG_WRITE(&(mem_seg_addr->mst_id_wr_sec[i]),  0xFFFFFFFF);
		REG_WRITE(&(mem_seg_addr->mst_id_wr_nsec[i]), 0x0);
	}
	REG_WRITE(&(mem_seg_addr->last_addr),((IRAM_PM_ADDR + IRAM_PM_SIZE - 1) >> AON_ADDR_SHIFT_BITS));
	REG_WRITE(&(mem_seg_addr->first_addr),(IRAM_PM_ADDR >> AON_ADDR_SHIFT_BITS));

	/* iram 0x15800 ~ 0x167FF secure read/write */
        mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_AON_BASE + MEM_FW_SEG_OFF + MEM_FW_SEG_LEN));
        REG_WRITE(&(mem_seg_addr->first_addr), 0xFFFFFFFF);
        for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
                REG_WRITE(&(mem_seg_addr->mst_id_rd_sec[i]), 0xFFFFFFFF);
                REG_WRITE(&(mem_seg_addr->mst_id_rd_nsec[i]), 0x0);
                REG_WRITE(&(mem_seg_addr->mst_id_wr_sec[i]),  0xFFFFFFFF);
                REG_WRITE(&(mem_seg_addr->mst_id_wr_nsec[i]), 0x0);
        }
        REG_WRITE(&(mem_seg_addr->last_addr),((IRAM_FW_ADDR + IRAM_FW_SIZE - 1) >> AON_ADDR_SHIFT_BITS));
        REG_WRITE(&(mem_seg_addr->first_addr),(IRAM_FW_ADDR >> AON_ADDR_SHIFT_BITS));
}

static void ddr_controller_sec (void)
{
	uint32_t val;

	// protect DDR controller
	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR4_OFF);
	val &= ~DDR_ATTR_MASK;
	val |= DDR_ATTR_WR;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR4_OFF) = val;

	/* enable mem_fw_pub, */
	/* rf_fw_en is tied 1, always enabled */

	// protect ddr phy channel
	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR3_OFF);
	val &= ~DDR_PHY_CH0_MASK;
	val |= DDR_PHY_CH0_ATTR_WR;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR3_OFF) = val;

	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR3_OFF);
	val &= ~DDR_PHY_CH1_MASK;
	val |= DDR_PHY_CH1_ATTR_WR;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR3_OFF) = val;
}

static void sml_teecfg_sec (void)
{
#ifdef CONFIG_ATF_BOOT_TOS
	uint32_t i;
	sprd_mem_seg_cfg *mem_seg_addr;

	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_PUB_BASE + MEM_FW_SEG_OFF));
	REG_WRITE(&(mem_seg_addr->first_addr), 0xFFFFFFFF);
	for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
		REG_WRITE(&(mem_seg_addr->mst_id_rd_sec[i]),  0xFFFFFFFF);
		REG_WRITE(&(mem_seg_addr->mst_id_rd_nsec[i]), 0x0);
		REG_WRITE(&(mem_seg_addr->mst_id_wr_sec[i]),  0xFFFFFFFF);
		REG_WRITE(&(mem_seg_addr->mst_id_wr_nsec[i]), 0x0);
	}
	REG_WRITE(&(mem_seg_addr->last_addr),((CONFIG_SML_LDADDR_START + CONFIG_SEC_MEM_SIZE - 1 - 0x80000000)>>PUB_ADDR_SHIFT_BITS));
	REG_WRITE(&(mem_seg_addr->first_addr),((CONFIG_SML_LDADDR_START - 0x80000000)>>PUB_ADDR_SHIFT_BITS));
#endif
}

static void tos_sec (uint32_t tos_size)
{
	sprd_mem_seg_cfg *mem_seg_addr;

	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_PUB_BASE + MEM_FW_SEG_OFF));
	REG32(&(mem_seg_addr->last_addr)) = (CONFIG_SML_LDADDR_START + CONFIG_SEC_MEM_SIZE + tos_size - 1 - 0x80000000)>>PUB_ADDR_SHIFT_BITS;
}

static void peri_sec (void)
{
	uint32_t val;

	/* secure SEC GPIO/REG/WDG/RTC */
	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD0_OFF);
	val &= ~(SEC_GPIO_MASK | SEC_REG_MASK | SEC_WDG_MASK | SEC_RTC_MASK);
	val |= SEC_GPIO_ATTR_RD | SEC_REG_ATTR_RD | SEC_WDG_ATTR_RD | SEC_RTC_ATTR_RD;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD0_OFF) = val;

	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR0_OFF);
	val &= ~(SEC_GPIO_MASK | SEC_REG_MASK | SEC_WDG_MASK | SEC_RTC_MASK);
	val |= SEC_GPIO_ATTR_WR | SEC_REG_ATTR_WR | SEC_WDG_ATTR_WR | SEC_RTC_ATTR_WR;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR0_OFF) = val;

	/* secure SEC TMR/EIC */
	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD1_OFF);
	val &= ~(SEC_TMR_MASK | SEC_EIC_MASK);
	val |= SEC_TMR_ATTR_RD | SEC_EIC_ATTR_RD;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD1_OFF) = val;

	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR1_OFF);
	val &= ~(SEC_TMR_MASK | SEC_EIC_MASK);
	val |= SEC_TMR_ATTR_WR | SEC_EIC_ATTR_WR;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR1_OFF) = val;
}

static void cp_sec (void)
{
	/* protect reset/sleep/shutdown bits */
	//PUBCP_CR5_CORE_SOFT_RST
	REG32(SPRD_REG_FW_AON_APB_BASE + REG_FW_AON_APB_CTRL_ADDR0_OFF) = REG_AON_APB_PCP_SOFT_RST;
	REG32(SPRD_REG_FW_AON_APB_BASE + REG_FW_AON_APB_CTRL_VAL0_OFF) = BIT_AON_APB_PUBCP_CR5_CORE_SOFT_RST;

	//PD_PUBCP_SYS_FORCE_SHUTDONW
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_ADDR0_OFF) = REG_PMU_APB_PD_PUBCP_SYS_CFG;
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_VAL0_OFF) = BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN;

	//PUBCP_SOFT_RST
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_ADDR1_OFF) = REG_PMU_APB_CP_SOFT_RST;
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_VAL1_OFF) = BIT_PMU_APB_PUBCP_SOFT_RST;

	//PUBCP_FORCE_DEEP_SLEEP
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_ADDR2_OFF) = REG_PMU_APB_SLEEP_CTRL;
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_VAL2_OFF) = BIT_PMU_APB_PUBCP_FORCE_DEEP_SLEEP;
}

static void disable_tzpc (void)
{
	/* disable tzpc */
	REG32(REG_AON_SEC_APB_SEC_EB + CLR_REG_OFF) = BIT_AON_SEC_APB_SEC_TZPC_EB;
}

void sprd_firewall_config_pre (void)
{
	sce_sec();
	cm4_sec();

	mem_fw_pub_sec();
	ddr_controller_sec();

#ifdef CONFIG_ATF_BOOT_TOS
	sml_teecfg_sec();
	peri_sec();
#endif

#ifdef CONFIG_SECBOOT
	cp_sec();
#endif
}

void sprd_firewall_config_attr (sprd_fw_attr *attr)
{
#ifdef CONFIG_ATF_BOOT_TOS
	tos_sec(attr->tos_size);
#endif
}

void sprd_firewall_config (void)
{
	nand_unsec();
	sdio_unsec();
	emmc_unsec();
	usb_unsec();

	iram_sec();

	disable_tzpc();
}

/*
* Copyright (c) 2017, Spreadtrum Communications.
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

#define SET_REG_OFF			0x1000
#define CLR_REG_OFF			0x2000

#define SPRD_MST_CTRL_AON_BASE		(SPRD_SEC_TZPC_PHYS + 0x3000)
#define SPRD_MST_CTRL_AP_BASE		(SPRD_SEC_TZPC_PHYS + 0x8000)
#define SPRD_SLV_FW_AON_BASE		(SPRD_SEC_TZPC_PHYS + 0x0000)
#define SPRD_SLV_FW_AP_BASE		(SPRD_SEC_TZPC_PHYS + 0x7000)
#define SPRD_REG_FW_AON_APB_BASE	(SPRD_SEC_TZPC_PHYS + 0x4000)
#define SPRD_REG_FW_AON_PMU_BASE	(SPRD_SEC_TZPC_PHYS + 0x5000)
#define SPRD_MEM_FW_AON_BASE		(SPRD_SEC_TZPC_PHYS + 0x1000)
#define SPRD_MEM_FW_PUB_BASE		(SPRD_SEC_TZPC_PHYS + 0xB000)

#define MST_ID_MAX_NUM			(128)
#define MST_ID_ARRAY_LEN		(MST_ID_MAX_NUM/32)

#define MST_CTRL_AON_RD0_OFF		(0x0000)
#define MST_CTRL_AON_WR0_OFF		(0x0004)

#define MST_CTRL_AP_RD0_OFF		(0x0000)
#define MST_CTRL_AP_WR0_OFF		(0x0004)

#define SLV_FW_AON_RD0_OFF		(0x0024)
#define SLV_FW_AON_RD3_OFF		(0x0030)
#define SLV_FW_AON_WR0_OFF		(0x0038)
#define SLV_FW_AON_WR3_OFF		(0x0044)
#define SLV_FW_AON_SEG_OFF		(0x004C)

#define SLV_FW_AP_RD1_OFF		(0x0024)
#define SLV_FW_AP_WR1_OFF		(0x0030)

#define REG_FW_AON_APB_CTRL_ADDR0_OFF	(0x0038)
#define REG_FW_AON_APB_CTRL_VAL0_OFF	(0x0078)

#define REG_FW_AON_PMU_CTRL_ADDR0_OFF	(0x0030)
#define REG_FW_AON_PMU_CTRL_ADDR1_OFF	(0x0034)
#define REG_FW_AON_PMU_CTRL_ADDR2_OFF	(0x0038)
#define REG_FW_AON_PMU_CTRL_VAL0_OFF	(0x0070)
#define REG_FW_AON_PMU_CTRL_VAL1_OFF	(0x0074)
#define REG_FW_AON_PMU_CTRL_VAL2_OFF	(0x0078)

#define MEM_FW_SEG_OFFSET		(0x0024)
#define MEM_FW_SEG_LEN			(72)

#define IRAM_MIN_ADDR			(0x0)

#define AON_ADDR_SHIFT_BITS		(4)
#define PUB_ADDR_SHIFT_BITS		(12)

#define MEM_FW_PUB_ENABLE		29

#define CM4_ATTR_MASK	BIT(15)
#define CM4_ATTR_RD	BIT(15)		//security read  operation
#define CM4_ATTR_WR	BIT(15)		//security write operation

//master ctlr ap
#define NAND_RD_SEC	(BIT(7)|BIT(6))
#define NAND_WR_SEC	(BIT(7)|BIT(6))

#define EMMC_RD_SEC	(BIT(9)|BIT(8))
#define EMMC_WR_SEC	(BIT(9)|BIT(8))

#define SD_RD_SEC	(BIT(13)|BIT(12))
#define SD_WR_SEC	(BIT(13)|BIT(12))

#define USB_RD_SEC	(BIT(15)|BIT(14))
#define USB_WR_SEC	(BIT(15)|BIT(14))

//slave fw aon
#define SEC_EIC_MASK			(BIT(3)|BIT(2))
#define SEC_EIC_ATTR_RD			(0x1 << 2)	//security access only
#define SEC_EIC_ATTR_WR			(0x1 << 2)	//security access only

#define SEC_GPIO_MASK			(BIT(5)|BIT(4))
#define SEC_GPIO_ATTR_RD		(0x1 << 4)	//security access only
#define SEC_GPIO_ATTR_WR		(0x1 << 4)	//security access only

#define SEC_REG_MASK			(BIT(7)|BIT(6))
#define SEC_REG_ATTR_RD			(0x1 << 6)	//security access only
#define SEC_REG_ATTR_WR			(0x1 << 6)	//security access only

#define SEC_WDG_MASK			(BIT(9)|BIT(8))
#define SEC_WDG_ATTR_RD			(0x1 << 8)	//security access only
#define SEC_WDG_ATTR_WR			(0x1 << 8)	//security access only

#define SEC_RTC_MASK			(BIT(11)|BIT(10))
#define SEC_RTC_ATTR_RD			(0x1 << 10)	//security access only
#define SEC_RTC_ATTR_WR			(0x1 << 10)	//security access only

#define SEC_TMR_MASK			(BIT(13)|BIT(12))
#define SEC_TMR_ATTR_RD			(0x1 << 12)	//security access only
#define SEC_TMR_ATTR_WR			(0x1 << 12)	//security access only

#define DDR_ATTR_MASK			(BIT(29)|BIT(28))
#define DDR_ATTR_RD			(0x3 << 28)	//security/non_security accesss
#define DDR_ATTR_WR			(0x1 << 28)	//security access only

//slave fw ap
#define SCE_ATTR_MASK	(BIT(7)|BIT(6))
#define SCE_ATTR_RD	(0x1 << 6)	//security access only
#define SCE_ATTR_WR	(0x1 << 6)	//security access only

#define BIT_PUBCP_CR5_CORE_SOFT_RST		BIT(10)
#define BIT_PD_PUBCP_SYS_FORCE_SHUTDONW		BIT(25)
#define BIT_PUBCP_SOFT_RST			BIT(1)
#define BIT_PUBCP_FORCE_DEEP_SLEEP		BIT(18)

#define IRAM_PM_ADDR	0x00000000
#define IRAM_PM_SIZE	0x2000

#define IRAM_FW_ADDR	0x0000EC00
#define IRAM_FW_SIZE	0x1400

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
	/***disable emmc secure set***/
	*(volatile uint32_t*)(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~NAND_RD_SEC;
	*(volatile uint32_t*)(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~NAND_WR_SEC;
}

static void emmc_unsec(void)
{
	/***disable emmc secure set***/
	*(volatile uint32_t*)(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~EMMC_RD_SEC;
	*(volatile uint32_t*)(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~EMMC_WR_SEC;
}

static void sd_unsec(void)
{
	/***disable sd secure set***/
	*(volatile uint32_t*)(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~SD_RD_SEC;
	*(volatile uint32_t*)(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~SD_WR_SEC;
}

static void usb_unsec(void)
{
	/***disable usb secure set***/
	*(volatile uint32_t*)(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~USB_RD_SEC;
	*(volatile uint32_t*)(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~USB_WR_SEC;
}

static void sce_sec(void)
{
	/* protect secure ce */
	*(volatile uint32_t*)(SPRD_SLV_FW_AP_BASE + SLV_FW_AP_RD1_OFF) &= ~SCE_ATTR_MASK;
	*(volatile uint32_t*)(SPRD_SLV_FW_AP_BASE + SLV_FW_AP_RD1_OFF) |= SCE_ATTR_RD;

	*(volatile uint32_t*)(SPRD_SLV_FW_AP_BASE + SLV_FW_AP_WR1_OFF) &= ~SCE_ATTR_MASK;
	*(volatile uint32_t*)(SPRD_SLV_FW_AP_BASE + SLV_FW_AP_WR1_OFF) |= SCE_ATTR_WR;
}

static void iram_sec (void)
{
	uint32_t i;
	sprd_mem_seg_cfg *mem_seg_addr;

	/* iram 0x0000 ~ 0x1FFF secure read/write */
	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_AON_BASE + MEM_FW_SEG_OFFSET));
	REG_WRITE(&(mem_seg_addr->first_addr), 0xFFFFFFFF);
	for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
		REG_WRITE(&(mem_seg_addr->mst_id_rd_sec[i]), 0xFFFFFFFF);
		REG_WRITE(&(mem_seg_addr->mst_id_rd_nsec[i]), 0x0);
		REG_WRITE(&(mem_seg_addr->mst_id_wr_sec[i]),  0xFFFFFFFF);
		REG_WRITE(&(mem_seg_addr->mst_id_wr_nsec[i]), 0x0);
	}
	REG_WRITE(&(mem_seg_addr->last_addr),((IRAM_PM_ADDR + IRAM_PM_SIZE - 1) >> AON_ADDR_SHIFT_BITS));
	REG_WRITE(&(mem_seg_addr->first_addr),(IRAM_PM_ADDR >> AON_ADDR_SHIFT_BITS));

	/* iram 0xEC00 ~ 0xFFFF secure read/write */
        mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_AON_BASE + MEM_FW_SEG_OFFSET + MEM_FW_SEG_LEN));
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
	/* secure ddr controller register */
	//*(volatile uint32_t*)(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD3_OFF) &= ~DDR_ATTR_MASK;
	//*(volatile uint32_t*)(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD3_OFF) |= DDR_ATTR_RD;

	*(volatile uint32_t*)(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR3_OFF) &= ~DDR_ATTR_MASK;
	*(volatile uint32_t*)(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR3_OFF) |= DDR_ATTR_WR;

	/* enable mem_fw_pub, */
	REG_OR(SPRD_DDR_PHYS, BIT(MEM_FW_PUB_ENABLE));
}

static void sml_tos_sec (void)
{
#ifdef CONFIG_ATF_BOOT_TOS
	uint32_t i;
	sprd_mem_seg_cfg *mem_seg_addr;

	/*
	 * DDR 0x94000000 ~ 0x94100000 SML secure read/write
	 * DDR 0x94100000 ~ 0x95000000 TOS secure read/write
	 */
	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_PUB_BASE + MEM_FW_SEG_OFFSET));

	REG_WRITE(&(mem_seg_addr->first_addr), 0xFFFFFFFF);
	for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
		REG_WRITE(&(mem_seg_addr->mst_id_rd_sec[i]),  0xFFFFFFFF);
		REG_WRITE(&(mem_seg_addr->mst_id_rd_nsec[i]), 0x0);
		REG_WRITE(&(mem_seg_addr->mst_id_wr_sec[i]),  0xFFFFFFFF);
		REG_WRITE(&(mem_seg_addr->mst_id_wr_nsec[i]), 0x0);
	}
	REG_WRITE(&(mem_seg_addr->last_addr),((CONFIG_SML_LDADDR_START + CONFIG_SML_TOS_RUNNING_SIZE - 1 - 0x80000000)>>PUB_ADDR_SHIFT_BITS));
	REG_WRITE(&(mem_seg_addr->first_addr),((CONFIG_SML_LDADDR_START - 0x80000000)>>PUB_ADDR_SHIFT_BITS));
#endif
}

static void peri_sec (void)
{
	uint32_t val;

	/* secure SEC REG/TMR/RTC/WDG/GPIO/EIC */
	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD0_OFF);
	val &= ~(SEC_REG_MASK | SEC_TMR_MASK | SEC_RTC_MASK | SEC_WDG_MASK | SEC_GPIO_MASK | SEC_EIC_MASK);
	val |= SEC_REG_ATTR_RD | SEC_TMR_ATTR_RD | SEC_RTC_ATTR_RD | SEC_WDG_ATTR_RD | SEC_GPIO_ATTR_RD | SEC_EIC_ATTR_RD;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_RD0_OFF) = val;

	val = REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR0_OFF);
	val &= ~(SEC_REG_MASK | SEC_TMR_MASK | SEC_RTC_MASK | SEC_WDG_MASK | SEC_GPIO_MASK | SEC_EIC_MASK);
	val |= SEC_REG_ATTR_WR | SEC_TMR_ATTR_WR | SEC_RTC_ATTR_WR | SEC_WDG_ATTR_WR | SEC_GPIO_ATTR_WR | SEC_EIC_ATTR_WR;
	REG32(SPRD_SLV_FW_AON_BASE + SLV_FW_AON_WR0_OFF) = val;
}

static void cm4_sec (void)
{
	/* protect reset/sleep/shutdown bits */

	/* cm4 is forced as a secure master by chip */
}

static void cp_sec (void)
{
	/* protect reset/sleep/shutdown bits */
	//PUBCP_CR5_CORE_SOFT_RST
	REG32(SPRD_REG_FW_AON_APB_BASE + REG_FW_AON_APB_CTRL_ADDR0_OFF) = REG_AON_APB_PCP_SOFT_RST;
	REG32(SPRD_REG_FW_AON_APB_BASE + REG_FW_AON_APB_CTRL_VAL0_OFF) = BIT_PUBCP_CR5_CORE_SOFT_RST;

	//PD_PUBCP_SYS_FORCE_SHUTDONW
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_ADDR0_OFF) = REG_PMU_APB_PD_PUBCP_SYS_CFG;
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_VAL0_OFF) = BIT_PD_PUBCP_SYS_FORCE_SHUTDONW;

	//PUBCP_SOFT_RST
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_ADDR1_OFF) = REG_PMU_APB_CP_SOFT_RST;
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_VAL1_OFF) = BIT_PUBCP_SOFT_RST;

	//PUBCP_FORCE_DEEP_SLEEP
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_ADDR2_OFF) = REG_PMU_APB_SLEEP_CTRL;
	REG32(SPRD_REG_FW_AON_PMU_BASE + REG_FW_AON_PMU_CTRL_VAL2_OFF) = BIT_PUBCP_FORCE_DEEP_SLEEP;
}

static void disable_tzpc (void)
{
	/* disable tzpc */
	REG32(REG_AON_SEC_APB_SEC_EB + CLR_REG_OFF) = BIT_AON_SEC_APB_SEC_TZPC_EB;
}

void sprd_firewall_config_pre (void)
{
	sce_sec();

	//make ddr controller secure
	ddr_controller_sec();

#ifdef CONFIG_ATF_BOOT_TOS
	sml_tos_sec();
	peri_sec();
#endif

#ifdef CONFIG_SECBOOT
	cm4_sec();
	cp_sec();
#endif
}

void sprd_firewall_config (void)
{
	//make nand/emmc/sdio/usb non-secure
	nand_unsec();
	emmc_unsec();
	sd_unsec();
	usb_unsec();

	//reset iram secure. only 8K will be pretected.
	iram_sec();

	//disable tzpc
	disable_tzpc();
}

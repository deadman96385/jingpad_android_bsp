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

#define REG32(_x_)	(*(volatile uint32_t*)(_x_))

#define SET_REG_OFF			0x1000
#define CLR_REG_OFF			0x2000

#define SPRD_MST_CTRL_AON_BASE		(SPRD_SEC_TZPC_PHYS + 0x3000)
#define SPRD_MST_CTRL_AP_BASE		(SPRD_SEC_TZPC_PHYS + 0x8000)
#define SPRD_SLV_FW_AON0_BASE		(SPRD_SEC_TZPC_PHYS + 0x0000)
#define SPRD_SLV_FW_AON1_BASE		(SPRD_SEC_TZPC_PHYS + 0xE000)
#define SPRD_SLV_FW_AP0_BASE		(SPRD_SEC_TZPC_PHYS + 0x7000)
#define SPRD_REG_FW_AON_APB_BASE	(SPRD_SEC_TZPC_PHYS + 0x4000)
#define SPRD_REG_FW_AON_PMU_BASE	(SPRD_SEC_TZPC_PHYS + 0x5000)
#define SPRD_REG_FW_AON_PIN_BASE	(SPRD_SEC_TZPC_PHYS + 0x6000)
#define SPRD_REG_FW_AP_AHB_BASE		(SPRD_SEC_TZPC_PHYS + 0xA000)
#define SPRD_REG_FW_AP_APB_BASE		(SPRD_SEC_TZPC_PHYS + 0x9000)
#define SPRD_MEM_FW_AON_BASE		(SPRD_SEC_TZPC_PHYS + 0x1000)
#define SPRD_MEM_FW_PUB_BASE		(SPRD_SEC_TZPC_PHYS + 0xB000)

#define MST_ID_MAX_NUM			(128)
#define MST_ID_ARRAY_LEN		(MST_ID_MAX_NUM/32)

#define MST_ID_DAP			0x00
#define MST_ID_CPU			0x01
#define MST_ID_ETR			0x02
#define MST_ID_TMC			0x72
#define MST_ID_CM4			0x73

#define MST_CTRL_AON_RD0_OFF		(0x0000)
#define MST_CTRL_AON_WR0_OFF		(0x0004)

#define MST_CTRL_AP_RD0_OFF		(0x0000)
#define MST_CTRL_AP_WR0_OFF		(0x0004)

#define SLV_FW_AON0_RD5_OFF		(0x004C)
#define SLV_FW_AON0_WR5_OFF		(0x0064)

#define SLV_FW_AON1_RD0_OFF		(0x0018)
#define SLV_FW_AON1_RD3_OFF		(0x0024)
#define SLV_FW_AON1_RD5_OFF		(0x002C)
#define SLV_FW_AON1_WR0_OFF		(0x0030)
#define SLV_FW_AON1_WR3_OFF		(0x003C)
#define SLV_FW_AON1_WR5_OFF		(0x0044)

#define SLV_FW_AP0_RD0_OFF		(0x0020)
#define SLV_FW_AP0_WR0_OFF		(0x002C)

#define REG_FW_AON_APB_RD0		(0x0000)
#define REG_FW_AON_APB_WR0		(0x0018)

#define REG_FW_AON_APB_CTRL_ADDR0_OFF	(0x0030)
#define REG_FW_AON_APB_CTRL_VAL0_OFF	(0x0070)

#define REG_FW_AON_PMU_CTRL_ADDR0_OFF	(0x0050)
#define REG_FW_AON_PMU_CTRL_ADDR1_OFF	(0x0054)
#define REG_FW_AON_PMU_CTRL_ADDR2_OFF	(0x0058)
#define REG_FW_AON_PMU_CTRL_VAL0_OFF	(0x0090)
#define REG_FW_AON_PMU_CTRL_VAL1_OFF	(0x0094)
#define REG_FW_AON_PMU_CTRL_VAL2_OFF	(0x0098)

#define REG_FW_AP_APB_CTRL_ADDR0_OFF	(0x0008)
#define REG_FW_AP_APB_CTRL_ADDR1_OFF	(0x000C)
#define REG_FW_AP_APB_CTRL_VAL0_OFF	(0x0048)
#define REG_FW_AP_APB_CTRL_VAL1_OFF	(0x004C)

#define MEM_FW_SEG_OFF			(0x1000)
#define MEM_FW_SEG_LEN			(0x80)

#define AON_ADDR_SHIFT_BITS		(4)
#define PUB_ADDR_SHIFT_BITS		(12)

#define USB_RD_SEC			BIT(21)
#define USB_WR_SEC			BIT(21)

//master ctrl ap
#define SDIO0_RD_SEC			(BIT(11)|BIT(10))
#define SDIO0_WR_SEC			(BIT(11)|BIT(10))

#define EMMC_RD_SEC			(BIT(5)|BIT(4))
#define EMMC_WR_SEC			(BIT(5)|BIT(4))

//slave fw aon
#define PUB_CTRL_ATTR_MASK		(BIT(21)|BIT(20))
#define PUB_CTRL_ATTR_RD		(BIT(21)|BIT(20))	//security/non_security accesss
#define PUB_CTRL_ATTR_WR		BIT(20)			//security access only

#define SP_RAM_CTRL_ATTR_MASK		(BIT(29)|BIT(28))
#define SP_RAM_CTRL_ATTR_RD		BIT(28)			//security access only
#define SP_RAM_CTRL_ATTR_WR		BIT(28)			//security access only

#define KEYPAD_CTRL_ATTR_MASK		(BIT(29)|BIT(28))
#define KEYPAD_CTRL_ATTR_RD		BIT(28)			//security access only
#define KEYPAD_CTRL_ATTR_WR		BIT(28)			//security access only

//slave fw ap0
#define SCE_SLV_ATTR_MASK		(BIT(3)|BIT(2))
#define SCE_SLV_ATTR_RD			BIT(2)			//security access only
#define SCE_SLV_ATTR_WR			BIT(2)			//security access only

// IRAM for PM
#define IRAM_PM_ADDR	0x00000000
#define IRAM_PM_SIZE	0x2000

// IRAM for FW
#define IRAM_FW_ADDR	0x00002000
#define IRAM_FW_SIZE	0x1000

// IRAM for efuse
#define IRAM_EFUSE_ADDR	0x00015C00
#define IRAM_EFUSE_SIZE	0x00000400

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

static void sdio_unsec(void)
{
	/* make sdio non-secure */
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_RD0_OFF) &= ~SDIO0_RD_SEC;
	REG32(SPRD_MST_CTRL_AP_BASE + MST_CTRL_AP_WR0_OFF) &= ~SDIO0_WR_SEC;
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
	REG32(SPRD_MST_CTRL_AON_BASE + MST_CTRL_AON_RD0_OFF) &= ~USB_RD_SEC;
	REG32(SPRD_MST_CTRL_AON_BASE + MST_CTRL_AON_WR0_OFF) &= ~USB_WR_SEC;
}

static void sce_sec(void)
{
	uint32_t val;

	/* set master attr */
	// master is secure. No config is needed

	/* set slave attr */
	// non-sec access is forbidden by itself. No config is needed
	val = REG32(SPRD_SLV_FW_AP0_BASE + SLV_FW_AP0_RD0_OFF);
	val &= ~SCE_SLV_ATTR_MASK;
	val |= SCE_SLV_ATTR_RD;
	REG32(SPRD_SLV_FW_AP0_BASE + SLV_FW_AP0_RD0_OFF) = val;

	val = REG32(SPRD_SLV_FW_AP0_BASE + SLV_FW_AP0_WR0_OFF);
	val &= ~SCE_SLV_ATTR_MASK;
	val |= SCE_SLV_ATTR_WR;
	REG32(SPRD_SLV_FW_AP0_BASE + SLV_FW_AP0_WR0_OFF) = val;

	/* protect enable bit */
	REG32(SPRD_REG_FW_AP_APB_BASE + REG_FW_AP_APB_CTRL_ADDR0_OFF) = REG_AP_APB_APB_EB;
	REG32(SPRD_REG_FW_AP_APB_BASE + REG_FW_AP_APB_CTRL_VAL0_OFF)  = BIT_AP_APB_CE_SEC_EB;

	/* protect softreset bit */
	REG32(SPRD_REG_FW_AP_APB_BASE + REG_FW_AP_APB_CTRL_ADDR1_OFF) = REG_AP_APB_APB_RST;
	REG32(SPRD_REG_FW_AP_APB_BASE + REG_FW_AP_APB_CTRL_VAL1_OFF)  = BIT_AP_APB_CE_SEC_SOFT_RST;
}

static void cm4_sec(void)
{
	uint32_t val;

	/* master is secure. No config is needed */

	/* cm4 is always enabled */

	/* tested protect soft-reset bit */
	/*val = REG32(SPRD_REG_FW_AON_APB_BASE + REG_FW_AON_APB_WR0);
	val |= BIT_REG_FW0_AON_CM4_SYS_SOFT_RST_WR_SEC;
	REG32(SPRD_REG_FW_AON_APB_BASE + REG_FW_AON_APB_WR0) = val;*/
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

static void iram_sec (void)
{
	uint32_t i;
	sprd_mem_seg_cfg *mem_seg_addr;

	/* iram 0x0000 ~ 0x1FFF secure read/write. Used by SML */
	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_AON_BASE + MEM_FW_SEG_OFF));
	REG32(&(mem_seg_addr->first_addr)) = 0xFFFFFFFF;
	for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
		REG32(&(mem_seg_addr->mst_id_rd_sec[i]))  = 0x0;
		REG32(&(mem_seg_addr->mst_id_rd_nsec[i])) = 0x0;
		REG32(&(mem_seg_addr->mst_id_wr_sec[i]))  = 0x0;
		REG32(&(mem_seg_addr->mst_id_wr_nsec[i])) = 0x0;
	}
	// only DAP/CPU/CM4 can access
	REG32(&(mem_seg_addr->mst_id_rd_sec[0]))  = BIT(MST_ID_DAP) | BIT(MST_ID_CPU);
	REG32(&(mem_seg_addr->mst_id_wr_sec[0]))  = BIT(MST_ID_DAP) | BIT(MST_ID_CPU);
	REG32(&(mem_seg_addr->mst_id_rd_sec[3]))  = BIT(MST_ID_CM4 % 32);
	REG32(&(mem_seg_addr->mst_id_wr_sec[3]))  = BIT(MST_ID_CM4 % 32);
	REG32(&(mem_seg_addr->last_addr)) = ((IRAM_PM_ADDR + IRAM_PM_SIZE - 1) >> AON_ADDR_SHIFT_BITS);
	REG32(&(mem_seg_addr->first_addr)) = (IRAM_PM_ADDR >> AON_ADDR_SHIFT_BITS);

	/* iram 0x2000 ~ 0x2FFF secure read/write. Used by TOS */
        mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_AON_BASE + MEM_FW_SEG_OFF + MEM_FW_SEG_LEN));
        REG32(&(mem_seg_addr->first_addr)) = 0xFFFFFFFF;
        for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
        	REG32(&(mem_seg_addr->mst_id_rd_sec[i]))  = 0x0;
        	REG32(&(mem_seg_addr->mst_id_rd_nsec[i])) = 0x0;
        	REG32(&(mem_seg_addr->mst_id_wr_sec[i]))  = 0x0;
        	REG32(&(mem_seg_addr->mst_id_wr_nsec[i])) = 0x0;
        }
        // only DAP/CPU/CM4 can access
	REG32(&(mem_seg_addr->mst_id_rd_sec[0]))  = BIT(MST_ID_DAP) | BIT(MST_ID_CPU);
	REG32(&(mem_seg_addr->mst_id_wr_sec[0]))  = BIT(MST_ID_DAP) | BIT(MST_ID_CPU);
	REG32(&(mem_seg_addr->mst_id_rd_sec[3]))  = BIT(MST_ID_CM4 % 32);
	REG32(&(mem_seg_addr->mst_id_wr_sec[3]))  = BIT(MST_ID_CM4 % 32);
        REG32(&(mem_seg_addr->last_addr)) = ((IRAM_FW_ADDR + IRAM_FW_SIZE - 1) >> AON_ADDR_SHIFT_BITS);
        REG32(&(mem_seg_addr->first_addr)) = (IRAM_FW_ADDR >> AON_ADDR_SHIFT_BITS);

        /* iram 0x15C00 ~ 0x15FFF read only */
	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_AON_BASE + MEM_FW_SEG_OFF + MEM_FW_SEG_LEN * 2));
	REG32(&(mem_seg_addr->first_addr)) = 0xFFFFFFFF;
	for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
		REG32(&(mem_seg_addr->mst_id_rd_sec[i]))  = 0xFFFFFFFF;
		REG32(&(mem_seg_addr->mst_id_rd_nsec[i])) = 0xFFFFFFFF;
		REG32(&(mem_seg_addr->mst_id_wr_sec[i]))  = 0x0;
		REG32(&(mem_seg_addr->mst_id_wr_nsec[i])) = 0x0;
	}
	REG32(&(mem_seg_addr->last_addr)) = ((IRAM_EFUSE_ADDR + IRAM_EFUSE_SIZE - 1) >> AON_ADDR_SHIFT_BITS);
	REG32(&(mem_seg_addr->first_addr)) = (IRAM_EFUSE_ADDR >> AON_ADDR_SHIFT_BITS);
}

static void dmc_sec (void)
{
	uint32_t val;

	// protect DDR controller
	val = REG32(SPRD_SLV_FW_AON0_BASE + SLV_FW_AON0_WR5_OFF);
	val &= ~PUB_CTRL_ATTR_MASK;
	val |= PUB_CTRL_ATTR_WR;
	REG32(SPRD_SLV_FW_AON0_BASE + SLV_FW_AON0_WR5_OFF) = val;

	val = REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_WR5_OFF);
	val &= ~PUB_CTRL_ATTR_MASK;
	val |= PUB_CTRL_ATTR_WR;
	REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_WR5_OFF) = val;

	/* enable mem_fw_pub, */
	/* rf_fw_en is tied 1, always enabled */
}

static void sml_teecfg_sec (void)
{
	uint32_t i;
	sprd_mem_seg_cfg *mem_seg_addr;

	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_PUB_BASE + MEM_FW_SEG_OFF));
	REG32(&(mem_seg_addr->first_addr)) = 0xFFFFFFFF;
	for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
		REG32(&(mem_seg_addr->mst_id_rd_sec[i]))  = 0xFFFFFFFF;
		REG32(&(mem_seg_addr->mst_id_rd_nsec[i])) = 0x0;
		REG32(&(mem_seg_addr->mst_id_wr_sec[i]))  = 0xFFFFFFFF;
		REG32(&(mem_seg_addr->mst_id_wr_nsec[i])) = 0x0;
	}
	REG32(&(mem_seg_addr->last_addr)) = (CONFIG_SML_LDADDR_START + CONFIG_SEC_MEM_SIZE - 1 - 0x80000000)>>PUB_ADDR_SHIFT_BITS;
	REG32(&(mem_seg_addr->first_addr)) = (CONFIG_SML_LDADDR_START - 0x80000000)>>PUB_ADDR_SHIFT_BITS;
}

static void tos_sec (uint32_t tos_size)
{
	sprd_mem_seg_cfg *mem_seg_addr;

	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)(SPRD_MEM_FW_PUB_BASE + MEM_FW_SEG_OFF));
	REG32(&(mem_seg_addr->last_addr)) = (CONFIG_SML_LDADDR_START + CONFIG_SEC_MEM_SIZE + tos_size - 1 - 0x80000000)>>PUB_ADDR_SHIFT_BITS;
}

// special for sharkl5. Only setting slv_fw_aon1
static void slv_fw_aon1_special (void) {
	uint32_t val;

	// SP_RAM
	val = REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_RD0_OFF);
	val &= ~SP_RAM_CTRL_ATTR_MASK;
	val |= SP_RAM_CTRL_ATTR_RD;
	REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_RD0_OFF) = val;

	val = REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_WR0_OFF);
	val &= ~SP_RAM_CTRL_ATTR_MASK;
	val |= SP_RAM_CTRL_ATTR_WR;
	REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_WR0_OFF) = val;

	// keypad
	val = REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_RD3_OFF);
	val &= ~KEYPAD_CTRL_ATTR_MASK;
	val |= KEYPAD_CTRL_ATTR_RD;
	REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_RD3_OFF) = val;

	val = REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_WR3_OFF);
	val &= ~KEYPAD_CTRL_ATTR_MASK;
	val |= KEYPAD_CTRL_ATTR_WR;
	REG32(SPRD_SLV_FW_AON1_BASE + SLV_FW_AON1_WR3_OFF) = val;
}

static void disable_tzpc (void)
{
	/* disable tzpc */
	REG32(REG_AON_SEC_APB_SEC_EB + CLR_REG_OFF) = BIT_AON_SEC_APB_SEC_TZPC_EB;
}

void sprd_firewall_config_pre (void)
{
	// special for sharkl5, enable USB clk.
	REG32(REG_AON_APB_APB_EB1 + SET_REG_OFF) = BIT_AON_APB_OTG_UTMI_EB;

#ifdef CONFIG_SECBOOT
	sce_sec();
	cm4_sec();
	cp_sec();

	dmc_sec();
	sml_teecfg_sec();

	slv_fw_aon1_special();
#endif
}

void sprd_firewall_config_attr (sprd_fw_attr *attr)
{
#ifdef CONFIG_SECBOOT
	tos_sec(attr->tos_size);
#endif
}

void sprd_firewall_config (void)
{
	sdio_unsec();
	emmc_unsec();
	usb_unsec();

	iram_sec();

	disable_tzpc();

	// special for sharkl5, enable USB clk.
	REG32(REG_AON_APB_APB_EB1 + CLR_REG_OFF) = BIT_AON_APB_OTG_UTMI_EB;
}

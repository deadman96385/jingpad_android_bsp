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

//#define REG32(_x_)	(*(volatile uint32_t*)(_x_))

#define SET_REG_OFF			0x1000
#define CLR_REG_OFF			0x2000

#define MST_ID_MAX_NUM			(128)
#define MST_ID_ARRAY_LEN		(MST_ID_MAX_NUM/32)

#define MST_ID_DAP			0x00
#define MST_ID_CPU			0x01
#define MST_ID_CM4			0x73

#define AON_ADDR_SHIFT_BITS		(4)
#define PUB_ADDR_SHIFT_BITS		(12)

// IRAM for PM
#define IRAM_PM_ADDR	0x00000000
#define IRAM_PM_SIZE	0x2000

// IRAM for FW
#define IRAM_FW_ADDR	0x00002000
#define IRAM_FW_SIZE	0x1000

typedef struct {
	volatile uint32_t first_addr;
	volatile uint32_t last_addr;
	volatile uint32_t mst_id_rd_sec[MST_ID_ARRAY_LEN];
	volatile uint32_t mst_id_rd_nsec[MST_ID_ARRAY_LEN];
	volatile uint32_t mst_id_wr_sec[MST_ID_ARRAY_LEN];
	volatile uint32_t mst_id_wr_nsec[MST_ID_ARRAY_LEN];
} sprd_mem_seg_cfg;

static inline void sdio_unsec(void)
{
	/* make sdio non-secure */
	REG32(REG_MASTER_CTRL_AP_RD_SEC_0) &= ~BIT_MASTER_CTRL_AP_RD_SEC_0_SDIO0_RD_SEC(3);
	REG32(REG_MASTER_CTRL_AP_WR_SEC_0) &= ~BIT_MASTER_CTRL_AP_WR_SEC_0_SDIO0_WR_SEC(3);
}

static inline void emmc_unsec(void)
{
	/* make emmc non-secure */
	REG32(REG_MASTER_CTRL_AP_RD_SEC_0) &= ~BIT_MASTER_CTRL_AP_RD_SEC_0_EMMC_RD_SEC(3);
	REG32(REG_MASTER_CTRL_AP_WR_SEC_0) &= ~BIT_MASTER_CTRL_AP_WR_SEC_0_EMMC_WR_SEC(3);
}

static inline void usb_unsec(void)
{
	/* make usb non-secure */
	REG32(REG_MASTER_CTRL_AON_RD_SEC_0) &= ~BIT_MASTER_CTRL_AON_RD_SEC_0_USBOTG_RD_SEC;
	REG32(REG_MASTER_CTRL_AON_WR_SEC_0) &= ~BIT_MASTER_CTRL_AON_WR_SEC_0_USBOTG_WR_SEC;

	// make usb3 non-secure
	//REG32(REG_MASTER_CTRL_IPA_RD_SEC_0) &= ~BIT_MASTER_CTRL_IPA_RD_SEC_0_USB3_RD_SEC;
	//REG32(REG_MASTER_CTRL_IPA_WR_SEC_0) &= ~BIT_MASTER_CTRL_IPA_WR_SEC_0_USB3_WR_SEC;
}

static inline void sce_sec(void)
{
	// master attr is decided by itself. No config is needed

	// non-sec access is forbidden by itself or slave firewall. So config is not a must.

	/* protect enable bit */
	REG32(REG_REG_FW0_AP_BIT_CTRL_ADDR_ARRAY0) = REG_AP_APB_APB_EB;
	REG32(REG_REG_FW0_AP_BIT_CTRL_ARRAY0)  = BIT_AP_APB_CE_SEC_EB;

	/* protect softreset bit */
	REG32(REG_REG_FW0_AP_BIT_CTRL_ADDR_ARRAY1) = REG_AP_APB_APB_RST;
	REG32(REG_REG_FW0_AP_BIT_CTRL_ARRAY1)  = BIT_AP_APB_CE_SEC_SOFT_RST;
}

static inline void cm4_sec(void)
{
	//uint32_t val;

	/* master is secure. No config is needed */

	/* cm4 is always enabled */

	/* tested protect soft-reset bit */
	/*val = REG32(REG_REG_FW0_AON_REG_WR_CTRL_0);
	val |= BIT_REG_FW0_AON_CM4_SYS_SOFT_RST_WR_SEC;
	REG32(REG_REG_FW0_AON_REG_WR_CTRL_0) = val;*/
}

static inline void cp_sec (void)
{
	/* protect reset/sleep/shutdown bits */

	//PUBCP_CR5_CORE_SOFT_RST
	REG32(REG_REG_FW0_AON_BIT_CTRL_ADDR_ARRAY0) = REG_AON_APB_PCP_SOFT_RST;
	REG32(REG_REG_FW0_AON_BIT_CTRL_ARRAY0) = BIT_AON_APB_PUBCP_CR5_CORE_SOFT_RST;

	//PD_PUBCP_SYS_FORCE_SHUTDONW
	REG32(REG_REG_FW1_AON_BIT_CTRL_ADDR_ARRAY0) = REG_PMU_APB_PD_PUBCP_SYS_CFG;
	REG32(REG_REG_FW1_AON_BIT_CTRL_ARRAY0) = BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN;

	//PUBCP_SOFT_RST
	REG32(REG_REG_FW1_AON_BIT_CTRL_ADDR_ARRAY1) = REG_PMU_APB_CP_SOFT_RST;
	REG32(REG_REG_FW1_AON_BIT_CTRL_ARRAY1) = BIT_PMU_APB_PUBCP_SOFT_RST;

	//PUBCP_FORCE_DEEP_SLEEP
	REG32(REG_REG_FW1_AON_BIT_CTRL_ADDR_ARRAY2) = REG_PMU_APB_FORCE_DEEP_SLEEP_CFG;
	REG32(REG_REG_FW1_AON_BIT_CTRL_ARRAY2) = BIT_PMU_APB_PUBCP_FORCE_DEEP_SLEEP;
}

static inline void iram_sec (void)
{
	uint32_t i;
	sprd_mem_seg_cfg *mem_seg_addr;

	/* iram 0x0000 ~ 0x1FFF secure read/write. Used by SML */
	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)REG_MEM_FW_AON_SEG_0_FIRST_ADDR);
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
        mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)REG_MEM_FW_AON_SEG_1_FIRST_ADDR);
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
}

static inline void dmc_sec (void)
{
	uint32_t val;

	// ctrl 3100_0000 non-secure/secure read, security write
	// phy0 3100_1000 non-secure/secure read, security write
	// phy1 3100_2000 non-secure/secure read, security write
	val = REG32(REG_SLV_FW_AON0_WR_SEC_5);
	val &= ~BIT_SLV_FW_AON0_WR_SEC_5_PUB_CRTL_REG_WR_SEC(3);
	val |= BIT_SLV_FW_AON0_WR_SEC_5_PUB_CRTL_REG_WR_SEC(1);
	REG32(REG_SLV_FW_AON0_WR_SEC_5) = val;

	val = REG32(REG_SLV_FW_AON1_WR_SEC_5);
	val &= ~BIT_SLV_FW_AON1_WR_SEC_5_PUB_CRTL_REG_WR_SEC(3);
	val |= BIT_SLV_FW_AON1_WR_SEC_5_PUB_CRTL_REG_WR_SEC(1);
	REG32(REG_SLV_FW_AON1_WR_SEC_5) = val;

	/* enable mem_fw_pub, */
	/* rf_fw_en is tied 1, always enabled */
}

static inline void sml_tos_sec (void)
{
	uint32_t i;
	sprd_mem_seg_cfg *mem_seg_addr;

	mem_seg_addr = (sprd_mem_seg_cfg *)((uint64_t)REG_MEM_FW_PUB_SEG_0_FIRST_ADDR);
	REG32(&(mem_seg_addr->first_addr)) = 0xFFFFFFFF;
	for (i = 0; i < MST_ID_ARRAY_LEN; i++) {
		REG32(&(mem_seg_addr->mst_id_rd_sec[i]))  = 0xFFFFFFFF;
		REG32(&(mem_seg_addr->mst_id_rd_nsec[i])) = 0x0;
		REG32(&(mem_seg_addr->mst_id_wr_sec[i]))  = 0xFFFFFFFF;
		REG32(&(mem_seg_addr->mst_id_wr_nsec[i])) = 0x0;
	}
	REG32(&(mem_seg_addr->last_addr)) = (CONFIG_SML_LDADDR_START + CONFIG_SML_TOS_RUNNING_SIZE - 1 - 0x80000000)>>PUB_ADDR_SHIFT_BITS;
	REG32(&(mem_seg_addr->first_addr)) = (CONFIG_SML_LDADDR_START - 0x80000000)>>PUB_ADDR_SHIFT_BITS;
}

// special for roc1. Only setting slv_fw_aon1
static inline void slv_fw_aon1_special (void) {
	uint32_t val;

	// SP_RAM
	val = REG32(REG_SLV_FW_AON1_RD_SEC_0);
	val &= ~BIT_SLV_FW_AON1_RD_SEC_0_AON_SP_RAM_RD_SEC(3);
	val |= BIT_SLV_FW_AON1_RD_SEC_0_AON_SP_RAM_RD_SEC(1);
	REG32(REG_SLV_FW_AON1_RD_SEC_0) = val;

	val = REG32(REG_SLV_FW_AON1_WR_SEC_0);
	val &= ~BIT_SLV_FW_AON1_WR_SEC_0_AON_SP_RAM_WR_SEC(3);
	val |= BIT_SLV_FW_AON1_WR_SEC_0_AON_SP_RAM_WR_SEC(1);
	REG32(REG_SLV_FW_AON1_WR_SEC_0) = val;

	// keypad
	val = REG32(REG_SLV_FW_AON1_RD_SEC_3);
	val &= ~BIT_SLV_FW_AON1_RD_SEC_3_KEYPAD_RD_SEC(3);
	val |= BIT_SLV_FW_AON1_RD_SEC_3_KEYPAD_RD_SEC(1);
	REG32(REG_SLV_FW_AON1_RD_SEC_3) = val;

	val = REG32(REG_SLV_FW_AON1_WR_SEC_3);
	val &= ~BIT_SLV_FW_AON1_WR_SEC_3_KEYPAD_WR_SEC(3);
	val |= BIT_SLV_FW_AON1_WR_SEC_3_KEYPAD_WR_SEC(1);
	REG32(REG_SLV_FW_AON1_WR_SEC_3) = val;
}

static inline void disable_tzpc (void)
{
	/* disable tzpc ipa */
	REG32(REG_AON_SEC_APB_SEC_EB + CLR_REG_OFF) = BIT_AON_SEC_APB_SEC_TZPC_IPA_EB;

	/* disable tzpc */
	REG32(REG_AON_SEC_APB_SEC_EB + CLR_REG_OFF) = BIT_AON_SEC_APB_SEC_TZPC_EB;
}

void sprd_firewall_config_pre (void)
{
	// special for roc1, enable USB clk.
	REG32(REG_AON_APB_APB_EB1 + SET_REG_OFF) = BIT_AON_APB_OTG_UTMI_EB;

#ifdef CONFIG_SECBOOT
	sce_sec();
	cm4_sec();
	cp_sec();

	dmc_sec();
	sml_tos_sec();

	slv_fw_aon1_special();
#endif
}

void sprd_firewall_config (void)
{
	sdio_unsec();
	emmc_unsec();
	usb_unsec();

	iram_sec();

	disable_tzpc();

	// special for roc1, enable USB clk.
	REG32(REG_AON_APB_APB_EB1 + CLR_REG_OFF) = BIT_AON_APB_OTG_UTMI_EB;
}

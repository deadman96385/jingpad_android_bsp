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

#include <sprd_ce.h>
#include <sprd_crypto.h>
#include <sprd_pka.h>

//#define SPRD_CE_ARGCHK(x)   if (!(x)) return SPRD_CE_ERR_ARG;

static void* s_ahb_vaddr;
static void* s_ce_vaddr;

#define REG_SET_VAL(__base, __offset, __v)	((*(volatile uint32_t *)((__base) + (__offset))) = (uint32_t)(__v))
#define REG_GET_VAL(__base, __offset)		 (*(volatile uint32_t *)((__base) + (__offset)))

#define SET_OFFSET		(0x1000)
#define CLR_OFFSET		(0x2000)
#define SPRD_REG_SET_BIT(__offset, __v)		REG_SET_VAL((s_ahb_vaddr+SET_OFFSET), __offset, __v)
#define SPRD_REG_CLR_BIT(__offset, __v)		REG_SET_VAL((s_ahb_vaddr+CLR_OFFSET), __offset, __v)

static uint32_t get_paddr_hi (void *vaddr){
	void *paddr = sprd_pal_vaddr_to_paddr(vaddr);
	return (uint32_t)(((uintptr_t)paddr & 0xF00000000ULL) >> 32);
};

static uint32_t get_paddr_lo (void *vaddr){
	void *paddr = sprd_pal_vaddr_to_paddr(vaddr);
	return (uint32_t)((uintptr_t)paddr & 0xFFFFFFFFULL);
};

static uint32_t get_pka_paddr_hi (uint8_t *vaddr){
	void *paddr = sprd_pal_vaddr_to_paddr(vaddr);
	return (uint32_t)(((uintptr_t)paddr & 0xFFFFE0000ULL) >> 17);
};

static uint32_t get_pka_paddr_lo (uint8_t *vaddr){
	void *paddr = sprd_pal_vaddr_to_paddr(vaddr);
	return (uint32_t)(((uintptr_t)paddr & 0x1FFFFULL));
};

void sprd_crypto_init_ce_cfg(sprd_ce_cfg_t* ce_cfg) {
	*(uint32_t*)(ce_cfg) = 0x0;
	ce_cfg->src_outstanding_num = 0x7;
	ce_cfg->dst_outstanding_num = 0x7;
	ce_cfg->src_word_switch = 0x0;
	ce_cfg->dst_word_switch = 0x0;
	ce_cfg->src_byte_switch = 0x1;
	ce_cfg->dst_byte_switch = 0x1;
	ce_cfg->do_wait_bdone = 0x1;
	ce_cfg->key_in_iram = 0x0;
	ce_cfg->key_in_session = 0x0;
	ce_cfg->key_in_efuse = 0x0;
	ce_cfg->key_in_ddr = 0x0;
	ce_cfg->dma_bypass = 0x0;
	ce_cfg->std_aad = 0x0;
	ce_cfg->std_aad_end = 0x0;
	ce_cfg->std_end = 0;
	ce_cfg->cmd_ioc = 0x1;
	ce_cfg->dont_dump_ddr = 0;
	ce_cfg->dont_rcv_ddr = 0;
	ce_cfg->link_mode = SPRD_CE_STD;
}

void sprd_ce_write_cmd_cfg(uint32_t reg, uint32_t reg_num, uint32_t* reg_val) {
	uint32_t i;
	uint32_t cfg_reg_op = ((0x1 & 0xF) << 28)
		| ((reg_num & 0x1F) << 16)
		| (reg & 0xFFFF);

	SPRD_CRYPTO_LOG_TRACE("[0x%x] = 0x%x\n", CE_CMD_FIFO_ENTRY, cfg_reg_op);
	REG_SET_VAL(s_ce_vaddr, CE_CMD_FIFO_ENTRY, cfg_reg_op);

	for(i = 0; i< reg_num; i++) {
		SPRD_CRYPTO_LOG_TRACE("[0x%x] = 0x%x\n", CE_CMD_FIFO_ENTRY, *(reg_val+i));
		REG_SET_VAL(s_ce_vaddr, CE_CMD_FIFO_ENTRY, *(reg_val+i));
	}
}

void sprd_ce_write_cmd_start(sprd_ce_start_param_t *param) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
	uint32_t start_op = (((uint32_t)0x2 & 0xF) << 28)
		| ((param->algo & 0x7000000) >> 4)
		| (*((uint32_t*)(&param->rcv_dump_addr_hi)) & 0xFF) << 8;

	SPRD_CRYPTO_LOG_TRACE("[0x%x] = 0x%x\n", CE_CMD_FIFO_ENTRY, start_op);
	SPRD_CRYPTO_LOG_TRACE("[0x%x] = 0x%x\n", CE_CMD_FIFO_ENTRY, *(uint32_t*)(&param->algo_cfg));
	SPRD_CRYPTO_LOG_TRACE("[0x%x] = 0x%x\n", CE_CMD_FIFO_ENTRY, *(uint32_t*)(&param->ce_cfg));
	SPRD_CRYPTO_LOG_TRACE("[0x%x] = 0x%x\n", CE_CMD_FIFO_ENTRY, param->rcv_addr_lo);
	SPRD_CRYPTO_LOG_TRACE("[0x%x] = 0x%x\n", CE_CMD_FIFO_ENTRY, param->dump_addr_lo);

	REG_SET_VAL(s_ce_vaddr, CE_CMD_FIFO_ENTRY, start_op);
	REG_SET_VAL(s_ce_vaddr, CE_CMD_FIFO_ENTRY, *(uint32_t*)(&param->algo_cfg));
	REG_SET_VAL(s_ce_vaddr, CE_CMD_FIFO_ENTRY, *(uint32_t*)(&param->ce_cfg));
	REG_SET_VAL(s_ce_vaddr, CE_CMD_FIFO_ENTRY, param->rcv_addr_lo);
	REG_SET_VAL(s_ce_vaddr, CE_CMD_FIFO_ENTRY, param->dump_addr_lo);
#pragma GCC diagnostic pop
}

void sprd_ce_write_cmd_hash(sprd_crypto_context_t* context) {
	sprd_ce_data_t data;
	sprd_ce_start_param_t start_param;

	sprd_pal_memset(&data, 0, sizeof(sprd_ce_data_t));
	data.src_addr_hi = get_paddr_hi(context->in);
	data.src_addr_lo = get_paddr_lo(context->in);
	data.src_frag_len = context->in_len & 0xFFFFFF;
	data.dst_addr_hi = get_paddr_hi(context->out);
	data.dst_addr_lo = get_paddr_lo(context->out);
	data.dst_frag_len = context->out_len & 0xFFFFFF;
	sprd_ce_write_cmd_cfg(CE_SRC_FLAG_LEN, 4, (uint32_t*)(&data));

	//start
	sprd_pal_memset(&start_param, 0, sizeof(sprd_ce_start_param_t));
	start_param.algo = context->algo;
	//set ce config
	sprd_crypto_init_ce_cfg(&start_param.ce_cfg);
	start_param.ce_cfg.std_end = context->end;
	start_param.ce_cfg.dont_dump_ddr = (context->end == 0 ? 0 : 1);
	start_param.ce_cfg.dont_rcv_ddr = (context->continued == 0 ? 1 : 0);
	//set algo config
	start_param.algo_cfg.hash.mode = context->algo & SPRD_CRYPTO_SUB_MODE_MASK;
	start_param.algo_cfg.hash.en = 0x1;
	//set dump addr
	start_param.rcv_dump_addr_hi.rcv_addr_hi = get_paddr_hi(context->info.hash.dump);
	start_param.rcv_dump_addr_hi.dump_addr_hi = get_paddr_hi(context->info.hash.dump);
	start_param.rcv_addr_lo = get_paddr_lo(context->info.hash.dump);
	start_param.dump_addr_lo = get_paddr_lo(context->info.hash.dump);
	sprd_ce_write_cmd_start(&start_param);
}

void sprd_ce_write_cmd_rsa(sprd_crypto_context_t* context) {
	sprd_ce_pka_data_t data;
	uint32_t pka_reg_len01;
	sprd_ce_start_param_t start_param;

	pka_reg_len01 = context->info.rsa.key_len;
	sprd_ce_write_cmd_cfg(CE_PKA_REG_LEN01, 1, &pka_reg_len01);
	sprd_pal_memset(&data, 0, sizeof(sprd_ce_pka_data_t));
	data.pka_store_addr_hi = get_pka_paddr_hi(context->out);
	data.pka_instr_addr_hi = get_paddr_hi((void*)(context->info.rsa.pka_cmd));
	data.pka_instr_addr_lo = get_paddr_lo((void*)(context->info.rsa.pka_cmd));
	data.pka_instr_len = 16 & 0xFFFFFF;
	sprd_ce_write_cmd_cfg(CE_PKA_CMD_FLAG_LEN, 4, (uint32_t*)(&data));

	//start
	sprd_pal_memset(&start_param, 0, sizeof(sprd_ce_start_param_t));
	start_param.algo = context->algo;
	//set ce config
	sprd_crypto_init_ce_cfg(&start_param.ce_cfg);
	start_param.ce_cfg.src_word_switch = 0x1;
	start_param.ce_cfg.dst_word_switch = 0x0;
	start_param.ce_cfg.key_in_ddr = 0x1;
	start_param.ce_cfg.std_end = 1;
	start_param.ce_cfg.dont_dump_ddr = 1;
	start_param.ce_cfg.dont_rcv_ddr = 1;
	//set algo config
	start_param.algo_cfg.pka.find_prime_num = 0xff;
	start_param.algo_cfg.pka.reg_num_sel = 0x1;
	start_param.algo_cfg.pka.en = 0x1;

	//load n
	data.pka_load_addr_hi = get_pka_paddr_hi(context->info.rsa.key_n);
	sprd_ce_write_cmd_cfg(CE_PKA_LOAD_ADDR_HI, 1, (uint32_t*)(&data.pka_load_addr_hi));
	context->info.rsa.pka_cmd[0] =
		sprd_pka_load(SPRD_CE_PKA_LEN_0, SPRD_CE_PKA_REG_0, 1, get_pka_paddr_lo(context->info.rsa.key_n));
	context->info.rsa.pka_cmd[1] =
			sprd_pka_stop();
	sprd_pal_clean_by_vaddr(context->info.rsa.pka_cmd, SPRD_CRYPTO_PKA_CMD_LEN*4);
	sprd_ce_write_cmd_start(&start_param);
	sprd_ce_polling();

	//load e
	data.pka_load_addr_hi = get_pka_paddr_hi(context->info.rsa.key_eod);
	sprd_ce_write_cmd_cfg(CE_PKA_LOAD_ADDR_HI, 1, (uint32_t*)(&data.pka_load_addr_hi));
	context->info.rsa.pka_cmd[0] =
			sprd_pka_load(SPRD_CE_PKA_LEN_0, SPRD_CE_PKA_REG_2, 1, get_pka_paddr_lo(context->info.rsa.key_eod));
	context->info.rsa.pka_cmd[1] =
			sprd_pka_stop();
	sprd_pal_clean_by_vaddr(context->info.rsa.pka_cmd, SPRD_CRYPTO_PKA_CMD_LEN*4);
	sprd_ce_write_cmd_start(&start_param);
	sprd_ce_polling();

	//load in and cal
	data.pka_load_addr_hi = get_pka_paddr_hi(context->in);
	sprd_ce_write_cmd_cfg(CE_PKA_LOAD_ADDR_HI, 1, (uint32_t*)(&data.pka_load_addr_hi));
	context->info.rsa.pka_cmd[0] =
		sprd_pka_load(SPRD_CE_PKA_LEN_0, SPRD_CE_PKA_REG_1, 1, get_pka_paddr_lo(context->in));
	context->info.rsa.pka_cmd[1] =
		sprd_pka_mod_exp(SPRD_CE_PKA_LEN_0, SPRD_CE_PKA_REG_3, SPRD_CE_PKA_REG_1, SPRD_CE_PKA_REG_2);;
	context->info.rsa.pka_cmd[2] =
		sprd_pka_store(SPRD_CE_PKA_LEN_0, SPRD_CE_PKA_REG_3, 1, get_pka_paddr_lo(context->out));
	context->info.rsa.pka_cmd[3] =
		sprd_pka_stop();
	sprd_pal_clean_by_vaddr(context->info.rsa.pka_cmd, SPRD_CRYPTO_PKA_CMD_LEN*4);
	sprd_ce_write_cmd_start(&start_param);
}

void sprd_ce_write_cmd_rng(sprd_crypto_context_t* context) {
	sprd_ce_pka_data_t data;
	uint32_t pka_reg_len01;
	sprd_ce_start_param_t start_param;

	context->info.rng.pka_cmd[0] =
		sprd_pka_load_rng(SPRD_CE_PKA_LEN_0, SPRD_CE_PKA_REG_0);
	context->info.rng.pka_cmd[1] =
		sprd_pka_store(SPRD_CE_PKA_LEN_0, SPRD_CE_PKA_REG_0, 1, get_pka_paddr_lo(context->out));
	context->info.rng.pka_cmd[2] = sprd_pka_stop();
	sprd_pal_clean_by_vaddr(context->info.rng.pka_cmd, SPRD_CRYPTO_PKA_CMD_LEN*4);

	pka_reg_len01 = context->out_len;
	sprd_ce_write_cmd_cfg(CE_PKA_REG_LEN01, 1, &pka_reg_len01);
	sprd_pal_memset(&data, 0, sizeof(sprd_ce_pka_data_t));
	data.pka_load_addr_hi = 0;
	data.pka_store_addr_hi = get_pka_paddr_hi(context->out);
	data.pka_instr_addr_hi = get_paddr_hi((void*)(context->info.rng.pka_cmd));
	data.pka_instr_addr_lo = get_paddr_lo((void*)(context->info.rng.pka_cmd));
	data.pka_instr_len = (12) & 0xFFFFFF;
	sprd_ce_write_cmd_cfg(CE_PKA_CMD_FLAG_LEN, 4, (uint32_t*)(&data));

	//start
	sprd_pal_memset(&start_param, 0, sizeof(sprd_ce_start_param_t));
	start_param.algo = context->algo;
	//set ce config
	sprd_crypto_init_ce_cfg(&start_param.ce_cfg);
	start_param.ce_cfg.src_word_switch = 0x1;
	start_param.ce_cfg.dst_word_switch = 0x0;
	start_param.ce_cfg.std_end = 1;
	start_param.ce_cfg.dont_dump_ddr = 1;
	start_param.ce_cfg.dont_rcv_ddr = 1;
	//set algo config
	start_param.algo_cfg.pka.find_prime_num = 0xff;
	start_param.algo_cfg.pka.reg_num_sel = 0x1;
	start_param.algo_cfg.pka.en = 0x1;
	sprd_ce_write_cmd_start(&start_param);
}

void
sprd_ce_write_cmd(sprd_crypto_context_t* context) {
	SPRD_CRYPTO_LOG_TRACE("context->algo = 0x%x, cmd_status = %d\n", context->algo, REG_GET_VAL(s_ce_vaddr, CE_CMD_FIFO_STATUS));
	switch (context->algo & SPRD_CRYPTO_MAIN_MODE_MASK) {
	case SPRD_CRYPTO_HASH:
		sprd_ce_write_cmd_hash(context);
		break;

	case SPRD_CRYPTO_RSA:
		sprd_ce_write_cmd_rsa(context);
		break;

	case SPRD_CRYPTO_RNG:
		sprd_ce_write_cmd_rng(context);
		break;

	default:
		break;
	}
}

uint32_t sprd_ce_get_finish_count(void) {
	return REG_GET_VAL(s_ce_vaddr, CE_FINISH_CMD_CNT);
}

uint32_t sprd_ce_polling(void) {
	while (1) {
		if (REG_GET_VAL(s_ce_vaddr, CE_INT_STATUS) & 0x01) {
			REG_SET_VAL(s_ce_vaddr, CE_INT_CLEAR, REG_GET_VAL(s_ce_vaddr, CE_INT_STATUS));
			break;
		}
	}
	return SPRD_CRYPTO_SUCCESS;
}

static inline void sprd_ce_all_int_enable(void) {
	sprd_ce_int_t int_en;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
	*(uint32_t*)(&int_en) = 0;
	int_en.cmd_done = 1;
	int_en.len_err = 1;
	int_en.tdes_key_err = 1;
	int_en.rng = 0;
	int_en.pka_store_done = 0;
	int_en.pka_one_cmd_done = 0;
	int_en.use_efuse_err = 1;
	int_en.pka_div_zero_err = 1;
	int_en.pka_find_prime_err = 1;
	REG_SET_VAL(s_ce_vaddr, CE_INT_EN, *(uint32_t*)(&int_en));
#pragma GCC diagnostic pop
}

static inline void sprd_ce_all_int_disable(void) {
	REG_SET_VAL(s_ce_vaddr, CE_INT_EN, 0x00);
}

static inline void sprd_ce_all_int_clear(void) {
	sprd_ce_int_t int_en;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
	*(uint32_t*)(&int_en) = 0;
	int_en.cmd_done = 1;
	int_en.len_err = 1;
	int_en.tdes_key_err = 1;
	int_en.rng = 1;
	int_en.pka_store_done = 1;
	int_en.pka_one_cmd_done = 1;
	int_en.use_efuse_err = 1;
	int_en.pka_div_zero_err = 1;
	int_en.pka_find_prime_err = 1;
	REG_SET_VAL(s_ce_vaddr, CE_INT_CLEAR, *(uint32_t*)(&int_en));
#pragma GCC diagnostic pop
}

static inline void sprd_ce_enable(void) {
	//set ce freq : 256M
	unsigned int cgm_ce0_val = REG_GET_VAL(REG_AP_CLK_CE_SEC_CFG, 0);
	if ((cgm_ce0_val & BIT_CGM_CE0_SEL) != CGM_CE0_SEL_256M) {
		REG_SET_VAL(REG_AP_CLK_CE_SEC_CFG, 0, (cgm_ce0_val | CGM_CE0_SEL_256M));
	}
	//enable ce
	SPRD_REG_SET_BIT(REG_AP_AHB_AHB_EB_OFFSET, BIT_AP_AHB_CE_SEC_EB);
}

static inline void sprd_ce_disable(void) {
	SPRD_REG_CLR_BIT(REG_AP_AHB_AHB_EB_OFFSET, BIT_AP_AHB_CE_SEC_EB);
}

void sprd_ce_open(void) {
	uint32_t count;
	(void)count;

	sprd_ce_enable();
	sprd_ce_reset();
	count = sprd_ce_get_finish_count();
	SPRD_CRYPTO_LOG_DEBUG("sprd_ce_open finish_count = %d\n", count);
	sprd_ce_all_int_clear();
	//sprd_ce_all_int_enable();
}

void sprd_ce_close(void){
	//sprd_ce_all_int_disable();
	sprd_ce_disable();
	SPRD_CRYPTO_LOG_TRACE("sprd_ce_close\n");
}

void sprd_ce_reset(void) {
	SPRD_REG_SET_BIT(REG_AP_AHB_AHB_RST_OFFSET, BIT_AP_AHB_CE_SEC_SOFT_RST);
	SPRD_REG_CLR_BIT(REG_AP_AHB_AHB_RST_OFFSET, BIT_AP_AHB_CE_SEC_SOFT_RST);
	REG_SET_VAL(s_ce_vaddr, CE_CLEAR, CE_CLEAR_EN);
}

void sprd_ce_init(void) {
	s_ahb_vaddr = sprd_pal_paddr_to_vaddr(SPRD_AHB_PHYS);
	s_ce_vaddr = sprd_pal_paddr_to_vaddr(SPRD_SECURE_CE_PHYS);
	SPRD_CRYPTO_LOG_DEBUG("success!  ahb = %p, ce = %p\n", s_ahb_vaddr, s_ce_vaddr);
}

void sprd_ce_terminal(void) {
}

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

#ifndef SPRD_CE_H
#define SPRD_CE_H

#include <sprd_ce_reg.h>
#include <sprd_crypto.h>

#define SPRD_CE_STD			0x00
#define SPRD_CE_LINK			0x01

typedef struct {
	uint32_t cmd_done		:1;
	uint32_t			:3;
	uint32_t len_err		:1;
	uint32_t tdes_key_err		:1;
	uint32_t			:1;
	uint32_t rng			:1;
	uint32_t pka_store_done		:1;
	uint32_t pka_one_cmd_done	:1;
	uint32_t use_efuse_err		:1;
	uint32_t pka_div_zero_err	:1;
	uint32_t pka_find_prime_err	:1;
	uint32_t			:19;
} sprd_ce_int_t;

/* offset 0x44 */
typedef struct {
	uint32_t link_mode		:1;
	uint32_t dont_rcv_ddr		:1;
	uint32_t dont_dump_ddr		:1;
	uint32_t cmd_ioc		:1;
	uint32_t std_end		:1;
	uint32_t std_aad_end		:1;
	uint32_t std_aad		:1;
	uint32_t dma_bypass		:1;
	uint32_t key_in_ddr		:1;
	uint32_t key_in_efuse		:1;
	uint32_t key_in_session		:1;
	uint32_t key_in_iram		:1;
	uint32_t do_wait_bdone		:1;
	uint32_t list_aad_end		:1;
	uint32_t list_aad		:1;
	uint32_t list_end		:1;
	uint32_t list_data_end		:1;
	uint32_t list_up_iv_sec_cnt	:1;
	uint32_t			:2;
	uint32_t dst_byte_switch	:1;
	uint32_t src_byte_switch	:1;
	uint32_t dst_word_switch	:1;
	uint32_t src_word_switch	:1;
	uint32_t dst_outstanding_num	:4;
	uint32_t src_outstanding_num	:4;
} sprd_ce_cfg_t;

typedef struct {
	/* offset 0x48 */
	uint32_t src_frag_len	:24;
	uint32_t src_addr_hi	:4;
	uint32_t		:4;

	/* offset 0x4C */
	uint32_t dst_frag_len	:24;
	uint32_t dst_addr_hi	:4;
	uint32_t		:4;

	/* offset 0x50 */
	uint32_t src_addr_lo;

	/* offset 0x54*/
	uint32_t dst_addr_lo;
} sprd_ce_data_t;

typedef struct {
	/* offset 0x48 */
	uint32_t pka_instr_len		:24;
	uint32_t pka_instr_addr_hi	:4;
	uint32_t			:4;

	/* offset 0x4C */
	uint32_t			:32;

	/* offset 0x50 */
	uint32_t pka_instr_addr_lo;

	/* offset 0x54 */
	uint32_t pka_store_addr_hi;

	/* offset 0x64 */
	uint32_t pka_load_addr_hi;
} sprd_ce_pka_data_t;

typedef struct {
	uint32_t len_0		:10;
	uint32_t		:6;
	uint32_t len_1		:10;
	uint32_t		:6;
} sprd_ce_pka_reg_len01_t;

/* offset 0x38 */
typedef struct {
	uint32_t en		:1;
	uint32_t		:3;
	uint32_t mode		:5;
	uint32_t 		:3;
	uint32_t hamc_pad_sel	:2;
	uint32_t		:18;
} sprd_ce_algo_hash_t;

/* offset 0xCC */
typedef struct {
	uint32_t en		:1;
	uint32_t reg_num_sel	:1;
	uint32_t		:14;
	uint32_t find_prime_num	:8;
	uint32_t 		:8;
} sprd_ce_algo_pka_t;

typedef struct {
	uint32_t algo;

	union {
		sprd_ce_algo_hash_t hash;
		sprd_ce_algo_pka_t pka;
	} algo_cfg;

	/* 0x44 */
	sprd_ce_cfg_t ce_cfg;

	/* offset 0x508 */
	uint32_t rcv_addr_lo;

	/* offset 0x50C */
	uint32_t dump_addr_lo;

	/* offset 0x510 */
	struct {
		uint32_t rcv_addr_hi	:4;
		uint32_t dump_addr_hi	:4;
		uint32_t		:24;
	} rcv_dump_addr_hi;
} sprd_ce_start_param_t;

void sprd_ce_reset(void);
void sprd_ce_init(void);
void sprd_ce_terminal(void);

void sprd_ce_open(void);
void sprd_ce_close(void);

void sprd_ce_write_cmd(sprd_crypto_context_t *context);
void sprd_ce_write_cmd_cfg(uint32_t reg, uint32_t reg_num, uint32_t* reg_val);
uint32_t sprd_ce_polling(void);

#endif /* SPRD_CE_H */

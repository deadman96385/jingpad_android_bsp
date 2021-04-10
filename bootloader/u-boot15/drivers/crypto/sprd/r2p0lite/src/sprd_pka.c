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

#include <sprd_crypto.h>

//operation codes
#define SPRD_PKA_OP_LOAD_RNG		0x01
#define SPRD_PKA_OP_JUMP		0x05
#define SPRD_PKA_OP_MOD_EXP		0x0B
#define SPRD_PKA_OP_LOAD		0x16
#define SPRD_PKA_OP_STORE		0x17
#define SPRD_PKA_OP_FIND_PRIME		0x1E
#define SPRD_PKA_OP_RSA_KEY_GEN		0x1F
#define SPRD_PKA_OP_STOP		0xFFFFFFFF

typedef struct {
	uint32_t special_bits	:6;
	uint32_t op_b		:5;
	uint32_t con_b		:1;
	uint32_t op_a		:5;
	uint32_t con_a		:1;
	uint32_t op_d		:5;
	uint32_t len		:4;
	uint32_t op		:5;
} sprd_crypto_pka_op_t;

typedef struct {
	uint32_t addr_lo	:17;
	uint32_t endian		:1;
	uint32_t op_d		:5;
	uint32_t len		:4;
	uint32_t op		:5;
} sprd_crypto_pka_trans_t;

#define SPRD_CRYPTO_PKA_CMD(_op, _len, _r, _con_a, _a, _con_b, _b, _spec) \
	  ( ((_op & 0x1F)	<< 27) \
	  | ((_len & 0xF)	<< 23) \
	  | ((_r & 0x1F)	<< 18) \
	  | ((_con_a & 0x1)	<< 17) \
	  | ((_a & 0x1F)	<< 12) \
	  | ((_con_b & 0x1)	<< 11) \
	  | ((_b & 0x1F)	<< 6)  \
	  | (_spec & 0x3F))

#define SPRD_CRYPTO_PKA_TRANS(_op, _len, _r, _endian, _a) \
	  ( ((_op & 0x1F)	<< 27) \
	  | ((_len & 0xF)	<< 23) \
	  | ((_r & 0x1F)	<< 18) \
	  | ((_endian & 0x1)	<< 17) \
	  | (_a & 0x1FFFF))

uint32_t
sprd_pka_stop (void) {
	return SPRD_PKA_OP_STOP;
}

uint32_t
sprd_pka_load (uint32_t len_index, uint32_t reg_index, uint8_t endian, uint32_t data_addr_low) {
	return SPRD_CRYPTO_PKA_TRANS(SPRD_PKA_OP_LOAD, len_index, reg_index, endian, data_addr_low);
}

uint32_t
sprd_pka_store (uint32_t len_index, uint32_t reg_index, uint8_t endian, uint32_t data_addr_low) {
	return SPRD_CRYPTO_PKA_TRANS(SPRD_PKA_OP_STORE, len_index, reg_index, endian, data_addr_low);
}

uint32_t
sprd_pka_jump(uint32_t condition, uint32_t offset) {
	return ((SPRD_PKA_OP_JUMP << 27) | ((condition & 0x1F) << 18) | (offset & 0x3FFFF));
}

uint32_t
sprd_pka_find_prime(uint32_t len_index, uint32_t r) {
	return SPRD_CRYPTO_PKA_CMD(SPRD_PKA_OP_FIND_PRIME, len_index, r, 1, 0, 1, 0, 5);
}

uint32_t
sprd_pka_key_gen0(uint32_t len_index, uint32_t e) {
	return ((SPRD_PKA_OP_RSA_KEY_GEN << 27) | ((len_index & 0xF) << 23) | ((e & 0x1FFFF) << 6) | 0);
}

uint32_t
sprd_pka_key_gen1(uint32_t len_index, uint32_t n_high, uint32_t d_high, uint32_t d_low){
	return SPRD_CRYPTO_PKA_CMD(SPRD_PKA_OP_RSA_KEY_GEN, len_index, n_high, 0, d_high, 0, d_low, 1);
}

uint32_t
sprd_pka_key_gen2(uint32_t len_index, uint32_t n_low, uint32_t p, uint32_t q) {
	return SPRD_CRYPTO_PKA_CMD(SPRD_PKA_OP_RSA_KEY_GEN, len_index, n_low, 0, p, 0, q, 2);
}

/* r = (a ^ b) mod reg0 */
uint32_t
sprd_pka_mod_exp(uint32_t len_index, uint32_t r, uint32_t a, uint32_t b) {
	return SPRD_CRYPTO_PKA_CMD(SPRD_PKA_OP_MOD_EXP, len_index, r, 0, a, 0, b, 0);
}

uint32_t
sprd_pka_load_rng(uint32_t len_index, uint32_t r) {
	return SPRD_CRYPTO_PKA_CMD(SPRD_PKA_OP_LOAD_RNG, len_index, r, 0, 0, 0, 0, 0);
}

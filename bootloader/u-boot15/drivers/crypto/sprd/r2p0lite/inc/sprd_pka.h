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

#ifndef SPRD_PKA_H
#define SPRD_PKA_H

#define SPRD_CE_PKA_REG_0	0
#define SPRD_CE_PKA_REG_1	1
#define SPRD_CE_PKA_REG_2	2
#define SPRD_CE_PKA_REG_3	3
#define SPRD_CE_PKA_REG_4	4
#define SPRD_CE_PKA_REG_5	5
#define SPRD_CE_PKA_REG_6	6
#define SPRD_CE_PKA_REG_7	7
#define SPRD_CE_PKA_REG_8	8
#define SPRD_CE_PKA_REG_9	9

#define SPRD_CE_PKA_LEN_0	0
//#define SPRD_CE_PKA_LEN_1	1

#define SPRD_CE_PKA_FIND_PRIME_TIMEOUT	0x12

uint32_t
sprd_pka_stop (void);

uint32_t
sprd_pka_load (uint32_t len_index, uint32_t reg_index, uint8_t endian, uint32_t data_addr_low);

uint32_t
sprd_pka_store (uint32_t len_index, uint32_t reg_index, uint8_t endian, uint32_t data_addr_low);

uint32_t
sprd_pka_jump(uint32_t condition, uint32_t offset);

uint32_t
sprd_pka_find_prime(uint32_t len_index, uint32_t r);

uint32_t
sprd_pka_key_gen0(uint32_t len_index, uint32_t e);

uint32_t
sprd_pka_key_gen1(uint32_t len_index, uint32_t n_high, uint32_t d_high, uint32_t d_low);

uint32_t
sprd_pka_key_gen2(uint32_t len_index, uint32_t n_low, uint32_t p, uint32_t q);

/* r = (a ^ b) mod reg0 */
uint32_t
sprd_pka_mod_exp(uint32_t len_index, uint32_t r, uint32_t a, uint32_t b);

uint32_t
sprd_pka_load_rng(uint32_t len_index, uint32_t r);

#endif /* SPRD_PKA_H */

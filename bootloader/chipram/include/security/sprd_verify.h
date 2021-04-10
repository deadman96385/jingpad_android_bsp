/*
 * Copyright (c) 2019, Spreadtrum Communications.
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
 *
 */

#ifndef __SPRD_VERIFY_H
#define __SPRD_VERIFY_H

#include <security/sec_common.h>
#include<security/sprdsec_header.h>
#include<security/sprd_rsa.h>

#ifndef false
#define false 0
#endif

#ifndef true
#define true 1
#endif

#ifndef bool
typedef int bool;
#endif

void dumpHex(const char *title, uint8_t * data, int len);
void cal_sha256(uint8_t * input, uint32_t bytes_num, uint8_t * output);
bool sprd_verify_cert(uint8_t * hash_key_precert, uint8_t * hash_data, uint8_t * certptr);
uint8_t * sprd_get_sechdr_addr(uint8_t * buf);
uint8_t * sprd_get_code_addr(uint8_t * buf);
uint8_t * sprd_get_cert_addr(uint8_t * buf);
bool sprd_verify_img(uint8_t * hash_key_precert, uint8_t * imgbuf);
SecBoot_Result_Ret sprd_secure_check(uint8_t * current_img_addr, uint8_t * data_header);

#endif	/* __SPRD_VERIFY_H */

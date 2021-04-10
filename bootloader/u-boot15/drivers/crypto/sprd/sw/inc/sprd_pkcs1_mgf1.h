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
 */

#ifndef SPRD_PKCS1_MGF1_H
#define SPRD_PKCS1_MGF1_H

#include <sprd_crypto_sw.h>

uint32_t sprd_pkcs1_mgf1(sprd_crypto_algo_t hash_type, const unsigned char *seed, unsigned long seedlen,
		unsigned char *mask, unsigned long masklen);

#endif   /* SPRD_PKCS1_MGF1_H*/

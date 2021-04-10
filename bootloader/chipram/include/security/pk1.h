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

#ifndef PK1_H
#define PK1_H

void invert_char(unsigned char *src,int len);

int get_rand_bytes(unsigned char *buf, int num);

int padding_add_pkcs_type_1(unsigned char *to, int tlen,
	     const unsigned char *from, int flen);

int padding_check_pkcs_type_1(unsigned char *to, int tlen,
	     const unsigned char *from, int flen, int num);

int padding_add_pkcs_type_2(unsigned char *to, int tlen,
	     const unsigned char *from, int flen);

int padding_check_pkcs_type_2(unsigned char *to, int tlen,
	     const unsigned char *from, int flen, int num);

#endif

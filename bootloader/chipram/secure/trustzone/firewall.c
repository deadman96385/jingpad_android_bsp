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
#include <security/trustzone/trustzone.h>

/******************************************************************************
* The following functions are defined as weak to allow a platform to override
* the way the firewall is initialised and used.
*****************************************************************************/
#pragma weak sprd_firewall_config_pre
#pragma weak sprd_firewall_config_attr
#pragma weak sprd_firewall_config

void sprd_firewall_config_pre (void) {}
void sprd_firewall_config_attr (sprd_fw_attr *attr) {}
void sprd_firewall_config (void) {}

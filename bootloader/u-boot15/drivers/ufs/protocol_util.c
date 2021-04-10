/* ==========================================================================
 * The Synopsys DWC UFS Software Driver and documentation (hereinafter
 * "Software") is an unsupported proprietary work of Synopsys, Inc. unless
 * otherwise expressly agreed to in writing between Synopsys and you.
 *
 * The Software IS NOT an item of Licensed Software or Licensed Product under
 * any End User Software License Agreement or Agreement for Licensed Product
 * with Synopsys or any supplement thereto.  Permission is hereby granted,
 * free of charge, to any person obtaining a copy of this software annotated
 * with this license and the Software, to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS" BASIS
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * ========================================================================== */
#include <common.h>
#include "protocol_util.h"

void get_cmnd(uint32_t opcode, lbaint_t lba, lbaint_t size, uint8_t *cmd)
{
	//debugf("Logical blk addr 0x%lx, size 0x%lx \n",lba, size);
	memset(cmd,0x0,16);

	switch (opcode)
	{
		case UFS_OP_READ_10 :
			cmd[0] = UFS_OP_READ_10;
			cmd[1] = 0;
			cmd[2] = (uint8_t)((lba & 0xff000000) >> 24); /* MSB Byte */
			cmd[3] = (uint8_t)((lba & 0x00ff0000) >> 16);
			cmd[4] = (uint8_t)((lba & 0x0000ff00) >> 8);
			cmd[5] = (uint8_t)(lba & 0x000000ff); /* LSB byte */
			cmd[6] = 0;
			cmd[7] = (uint8_t)((size >> 8) & 0xff);
			cmd[8] = (uint8_t)((size) & 0xff);
			cmd[9] = 0;
			break;

		case UFS_OP_WRITE_10 :
			cmd[0] = UFS_OP_WRITE_10;
			cmd[1] = 0;
			cmd[2] = (uint8_t)((lba & 0xff000000) >> 24); /* MSB Byte */
			cmd[3] = (uint8_t)((lba & 0x00ff0000) >> 16);
			cmd[4] = (uint8_t)((lba & 0x0000ff00) >> 8);
			cmd[5] = (uint8_t)(lba & 0x000000ff); /* LSB byte */
			cmd[6] = 0;
			cmd[7] = (uint8_t)((size >> 8) & 0xff);
			cmd[8] = (uint8_t)((size) & 0xff);
			cmd[9] = 0;
			break;

		case UFS_OP_TEST_UNIT_READY :
			cmd[0] = UFS_OP_TEST_UNIT_READY;
			cmd[1] = 0;
			cmd[2] = 0;
			cmd[3] = 0;
			cmd[4] = 0;
			cmd[5] = 0;
			break;

		case UFS_OP_SECURITY_PROTOCOL_IN :
			cmd[0] = UFS_OP_SECURITY_PROTOCOL_IN;
			cmd[1] = SECURITY_PROTOCOL;  /* Manju updated from 0x00 */
			cmd[2] = 0x00;
			cmd[3] = 0x01;
			cmd[4] = 0x00;
			cmd[5] = 0x00;
			cmd[6] = (uint8_t)(size >> 24);
			cmd[7] = (uint8_t)((size >> 16) & 0xff);
			cmd[8] = (uint8_t)((size >> 8) & 0xff);
			cmd[9] = (uint8_t)(size & 0xff);
			cmd[10] = 0x00;
			cmd[11] = 0x00;
			break;

		case UFS_OP_SECURITY_PROTOCOL_OUT:
			cmd[0] = UFS_OP_SECURITY_PROTOCOL_OUT;
			cmd[1] = SECURITY_PROTOCOL;
			cmd[2] = 0x00;
			cmd[3] = 0x01;
			cmd[4] = 0x00;
			cmd[6] = (uint8_t)((size >> 24));
			cmd[7] = (uint8_t)((size >> 16) & 0xff);
			cmd[8] = (uint8_t)((size >> 8) & 0xff);
			cmd[9] = (uint8_t)(size & 0xff);
			cmd[10] = 0x00;
			cmd[11] = 0x00;
			break;

		case UFS_OP_UNMAP:
			cmd[0] = UFS_OP_UNMAP;
			cmd[1] = 0;
			cmd[2] = 0;
			cmd[3] = 0;
			cmd[4] = 0;
			cmd[5] = 0;
			cmd[6] = 0;
			/*use size as parameter list length*/
			cmd[7] = (uint8_t)((size >> 8) & 0xff);
			cmd[8] = (uint8_t)((size) & 0xff);
			cmd[9] = 0;
			break;

		case UFS_OP_SYNCHRONIZE_CACHE_10:
			cmd[0] = UFS_OP_SYNCHRONIZE_CACHE_10;
			cmd[1] = 0;
			cmd[2] = (uint8_t)((lba & 0xff000000) >> 24); /* MSB Byte */
			cmd[3] = (uint8_t)((lba & 0x00ff0000) >> 16);
			cmd[4] = (uint8_t)((lba & 0x0000ff00) >> 8);
			cmd[5] = (uint8_t)(lba & 0x000000ff); /* LSB byte */
			cmd[6] = 0;
			cmd[7] = (uint8_t)((size >> 8) & 0xff);
			cmd[8] = (uint8_t)((size) & 0xff);
			cmd[9] = 0;
			break;

		default:
			break;
	}
}


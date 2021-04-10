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

#ifndef SCSI_PROCESSOR_H
#define SCSI_PROCESSOR_H

/* Ref [2], Sec 11.3 */
#define UFS_OP_FORMAT_UNIT           (0x04)
#define UFS_OP_INQUIRY               (0x12)
#define UFS_OP_MODE_SELECT_10        (0x55)
#define UFS_OP_MODE_SENSE_10         (0x5A)
#define UFS_OP_PRE_FETCH_10          (0x34)
#define UFS_OP_PRE_FETCH_16          (0x90)
#define UFS_OP_READ_6                (0x08)
#define UFS_OP_READ_10               (0x28)
#define UFS_OP_READ_16               (0x88)
#define UFS_OP_READ_BUFFER           (0x3C)
#define UFS_OP_READ_CAPACITY_10      (0x25)
#define UFS_OP_READ_CAPACITY_16      (0x9E)
#define UFS_OP_REPORT_LUNS           (0xA0)
#define UFS_OP_REQUEST_SENSE         (0x03)
#define UFS_OP_SECURITY_PROTOCOL_IN  (0xA2)
#define UFS_OP_SECURITY_PROTOCOL_OUT (0xB5)
#define UFS_OP_SEND_DIAGNOSTIC       (0x1D)
#define UFS_OP_START_STOP_UNIT       (0x1B)
#define UFS_OP_SYNCHRONIZE_CACHE_10  (0x35)
#define UFS_OP_SYNCHRONIZE_CACHE_16  (0x91)
#define UFS_OP_TEST_UNIT_READY       (0x00)
#define UFS_OP_UNMAP                 (0x42)
#define UFS_OP_VERIFY_10             (0x2F)
#define UFS_OP_WRITE_6               (0x0A)
#define UFS_OP_WRITE_10              (0x2A)
#define UFS_OP_WRITE_16              (0x8A)
#define UFS_OP_WRITE_BUFFER          (0x3B)
#define SECURITY_PROTOCOL            (0xEC)

/* Function Prototypes */
void get_cmnd(uint32_t opcode, ulong lba, ulong size, uint8_t *cmd);

#endif

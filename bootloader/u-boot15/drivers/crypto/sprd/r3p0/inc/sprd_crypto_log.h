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


#ifndef SPRD_CRYPTO_LOG_H
#define SPRD_CRYPTO_LOG_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <sprd_pal_plat.h>

#define SPRD_CRYPTO_CUR_LOG_LEVEL 	1

/**
* @brief File Description:
*        This file contains functions for logging.
*        The functions implementations are generally just wrappers to different operating system calls.
*        None of the described functions will check the input parameters so the behavior
*        of the APIs in illegal parameters case is dependent on the operating system behavior.
*
*/

#define __SPRD_CRYPTO_LOG(level, format, ...) printf(format, ##__VA_ARGS__)

/* crypto log levels */
#define SPRD_CRYPTO_LOG_LEVEL_ERR       0
#define SPRD_CRYPTO_LOG_LEVEL_WARN      1
#define SPRD_CRYPTO_LOG_LEVEL_DEBUG     2
#define SPRD_CRYPTO_LOG_LEVEL_TRACE     3

#define _SPRD_CRYPTO_LOG(level, format, ...)  \
		__SPRD_CRYPTO_LOG(SPRD_CRYPTO_LOG_LEVEL_ ## level, "%s: %s: " format, "SPRD_CE", __func__, ##__VA_ARGS__)

#if (SPRD_CRYPTO_CUR_LOG_LEVEL >= SPRD_CRYPTO_LOG_LEVEL_ERR)
#define SPRD_CRYPTO_LOG_ERR(format, ...) \
	_SPRD_CRYPTO_LOG(ERR, format, ##__VA_ARGS__)
#else
#define SPRD_CRYPTO_LOG_ERR(format, arg...) do {} while (0)
#endif

#if (SPRD_CRYPTO_CUR_LOG_LEVEL >= SPRD_CRYPTO_LOG_LEVEL_WARN)
#define SPRD_CRYPTO_LOG_WARN(format, ...) \
	_SPRD_CRYPTO_LOG(WARN, format, ##__VA_ARGS__)
#else
#define SPRD_CRYPTO_LOG_WARN(format, arg...) do {} while (0)
#endif

#if (SPRD_CRYPTO_CUR_LOG_LEVEL >= SPRD_CRYPTO_LOG_LEVEL_DEBUG)
#define SPRD_CRYPTO_LOG_DEBUG(format, ...) \
	_SPRD_CRYPTO_LOG(DEBUG, format, ##__VA_ARGS__)

#define SPRD_CRYPTO_LOG_DUMP_BUF(msg, buf, size)		\
	do {						\
	int i;						\
	uint8_t	*pData = (uint8_t*)buf;			\
							\
	PRINTF("%s (%d):\n", msg, size);		\
	for (i = 0; i < size; i++) {			\
		PRINTF("0x%02X ", pData[i]);		\
		if ((i & 0xF) == 0xF) {			\
			PRINTF("\n");			\
		}					\
	}						\
	PRINTF("\n");					\
	} while (0)
#else
#define SPRD_CRYPTO_LOG_DEBUG(format, arg...) do {} while (0)
#define SPRD_CRYPTO_LOG_DUMP_BUF(msg, buf, size)	do {} while (0)
#endif

#if (SPRD_CRYPTO_CUR_LOG_LEVEL >= SPRD_CRYPTO_LOG_LEVEL_TRACE)
#define SPRD_CRYPTO_LOG_TRACE(format, ...) \
	_SPRD_CRYPTO_LOG(TRACE, format, ##__VA_ARGS__)
#else
#define SPRD_CRYPTO_LOG_TRACE(format, arg...) do {} while (0)
#endif

#ifdef __cplusplus
}
#endif

#endif /* SPRD_CRYPTO_LOG_H */

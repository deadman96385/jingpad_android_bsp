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

#ifndef SPRD_PAL_PLAT_H
#define SPRD_PAL_PLAT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <asm/io.h>
#include <asm/cache.h>
#include <linux/types.h>
#include <linux/string.h>
#include <common.h>
#include <malloc.h>

/**
* @brief File Description:
*        This file contains informations of secure OS used by third party.
*        It will be modified by third party.
*
*/

#ifdef CONFIG_SYS_CACHELINE_SIZE
#define SPRD_PAL_CACHE_LINE	(CONFIG_SYS_CACHELINE_SIZE)
#else
#define SPRD_PAL_CACHE_LINE	128
#endif

#define sprd_pal_paddr_to_vaddr(__va)	((void*)(__va))
#define	sprd_pal_vaddr_to_paddr(__pa)	((void*)(__pa))

#define sprd_pal_flush_by_vaddr(__addr, __size) \
	flush_dcache_range((unsigned long)(__addr), (unsigned long)(__addr)+(__size))
#define sprd_pal_clean_by_vaddr(__addr, __size)	\
	flush_dcache_range((unsigned long)(__addr), (unsigned long)(__addr)+(__size))
#define sprd_pal_invalidate_by_vaddr(__addr, __size) \
	invalidate_dcache_range((unsigned long)(__addr), (unsigned long)(__addr)+(__size))

#define sprd_pal_malloc		malloc
#define sprd_pal_free		free

#define sprd_pal_memcpy		memcpy
#define sprd_pal_memcmp		memcmp
#define sprd_pal_memset		memset

#define sprd_pal_strlen		strlen

#ifdef __cplusplus
}
#endif

#endif /* SPRD_PAL_PLAT_H */

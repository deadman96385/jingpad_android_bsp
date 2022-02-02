/*!
 *****************************************************************************
 * Copyright (c) Imagination Technologies Ltd.
 *
 * The contents of this file are subject to the MIT license as set out below.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the terms of the
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above.
 *
 * If you wish to allow use of your version of this file only under the terms
 * of GPL, and not to allow others to use your version of this file under the
 * terms of the MIT license, indicate your decision by deleting the provisions
 * above and replace them with the notice and other provisions required by GPL
 * as set out in the file called "GPLHEADER" included in this distribution. If
 * you do not delete the provisions above, a recipient may use your version of
 * this file under the terms of either the MIT license or GPL.
 *
 * This License is also included in this distribution in the file called
 * "MIT_COPYING".
 *
 *****************************************************************************/

#if defined(HW_AX2)
#include <hwdefs/vha_cr_mirage.h>
#elif defined(HW_AX3)
#include <hwdefs/vha_cr.h>
#else
#error "No HW layout defined"
#endif

/* value missing from vha_cr.h: value obtained from email from SS */
#define VHA_CR_CNN_DEBUG_STATUS_CNN_DEBUG_OFFSET_ALIGNSHIFT 32

#define IMG_UINT64_C(v) v##ULL

#define VHA_DEAD_HW (0xdead1000dead1ULL)

#ifndef OSID
#define _OSID_ 0
#else
#define _OSID_ OSID
#endif

#define _CONCAT(x, y, z) x ## y ## z
#define OSID_TOKEN(group, osid, reg) _CONCAT(group, osid, reg)

#define VHA_CR_OS(reg_name) \
	OSID_TOKEN(VHA_CR_OS, _OSID_, _ ## reg_name)

/* HW Series AURA or MIRAGE */
#if defined(HW_AX2)
#define HW_SERIES (23U)
#elif defined(HW_AX3)
#if defined(CONFIG_VHA_NEXEF)
/* 3NX-F use a different B. value */
#define HW_SERIES (32U)
#else
#define HW_SERIES (28U)
#endif
#else
#error "No HW Series defined"
#endif

/* Events macros definition */
#define VHA_EVENT_TYPE(name) \
		VHA_CR_VHA_EVENT_TYPE_VHA_##name##_EN

#if defined(HW_AX2)
#define VHA_CNN_ERR_EVNTS (VHA_EVENT_TYPE(CNN0_ERROR) |\
			VHA_EVENT_TYPE(CNN0_MEM_WDT) |\
			VHA_EVENT_TYPE(CNN0_WDT))

#define VHA_CORE_EVNTS (VHA_EVENT_TYPE(MMU_PAGE_FAULT) |\
			VHA_EVENT_TYPE(AXI_ERROR))
#elif defined(HW_AX3)
#define VHA_CNN_ERR_EVNTS (VHA_EVENT_TYPE(CNN0_ERROR) |\
			VHA_EVENT_TYPE(CNN0_MEM_WDT))

#ifdef VHA_SCF
#define VHA_CORE_EVNTS ( \
			VHA_EVENT_TYPE(MMU_PARITY_ERROR) |\
			VHA_EVENT_TYPE(PARITY_ERROR) |\
			VHA_EVENT_TYPE(LOCKSTEP_ERROR) |\
			VHA_EVENT_TYPE(READY) |\
			VHA_EVENT_TYPE(ERROR) |\
			VHA_EVENT_TYPE(HL_WDT) |\
			VHA_EVENT_TYPE(MMU_PAGE_FAULT) |\
			VHA_EVENT_TYPE(AXI_ERROR))
#else  /*!VHA_SCF */
#define VHA_CORE_EVNTS ( \
			VHA_EVENT_TYPE(READY) |\
			VHA_EVENT_TYPE(ERROR) |\
			VHA_EVENT_TYPE(HL_WDT) |\
			VHA_EVENT_TYPE(MMU_PAGE_FAULT) |\
			VHA_EVENT_TYPE(AXI_ERROR))
#endif /* VHA_SCF */
#endif  /* HW_AX3 */

/* ignore bottom 4 bits of CONFIG_ID: they identify different build variants */
#define VHA_CR_CORE_ID_BVNC_CLRMSK (0xfffffffffffffff0ULL)
#define VHA_CNN_CMPLT_EVNT (VHA_EVENT_TYPE(CNN0_COMPLETE))
#define VHA_CNN_EVNTS (VHA_CNN_ERR_EVNTS | VHA_CNN_CMPLT_EVNT)

#define VHA_EVNTS_DEFAULT ( ( \
		VHA_CNN_EVNTS | VHA_CORE_EVNTS \
		) & VHA_CR_OS(VHA_EVENT_ENABLE_MASKFULL))

#define VHA_SYS_CLOCK_MODE(name, mode) \
		VHA_CR_SYS_CLK_CTRL0_##name##_##mode \

#define VHA_SYS_CLOCKS_DEFAULT(mode) ( (\
			VHA_SYS_CLOCK_MODE(SLC, mode) \
			) & VHA_CR_SYS_CLK_CTRL0_MASKFULL)

/* Clocks macros definition */
#define VHA_MAIN_CLOCK_MODE(name, mode) \
		VHA_CR_CLK_CTRL0_##name##_##mode \

#if defined(HW_AX2)
#define VHA_MAIN_CLOCKS_DEFAULT(mode) ( (\
			VHA_MAIN_CLOCK_MODE(CNN_EWO, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_PACK, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_OIN, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_POOL, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_SB, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_XBAR, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_NORM, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_ACT, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_ACCUM, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_CNV, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_CBUF, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_IBUF, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_CMD, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN, mode) | \
			VHA_MAIN_CLOCK_MODE(SLC, mode) | \
			VHA_MAIN_CLOCK_MODE(BIF, mode) \
			) & VHA_CR_CLK_CTRL0_MASKFULL)
#elif defined(HW_AX3)
#define VHA_MAIN_CLOCKS_DEFAULT(mode) ( (\
			VHA_MAIN_CLOCK_MODE(CNN_CORE_XBAR, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_MMM, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_EWO, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_PACK, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_OIN, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_POOL, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_SB, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_NORM, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_ACT, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_ACCUM, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_CNV, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_CBUF, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_IBUF, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_CMD, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_TRS_A, mode) | \
			VHA_MAIN_CLOCK_MODE(CNN_TRS_B, mode) | \
			VHA_MAIN_CLOCK_MODE(SLC, mode) | \
			VHA_MAIN_CLOCK_MODE(BIF, mode) \
			) & VHA_CR_CLK_CTRL0_MASKFULL)
#endif

/* Reset macros definition */
#define VHA_RESET_EN(name) \
		VHA_CR_RESET_CTRL_VHA_##name##_EN

#define VHA_RESET_DEFAULT ( ( \
			VHA_RESET_EN(SYS_SOFT_RESET) | \
			VHA_RESET_EN(AXI_SOFT_RESET) | \
			VHA_RESET_EN(CNN0_SOFT_RESET) | \
			VHA_RESET_EN(SLC_SOFT_RESET) | \
			VHA_RESET_EN(BIF_SOFT_RESET) | \
			VHA_RESET_EN(SOFT_RESET) \
			) & VHA_CR_RESET_CTRL_MASKFULL)

#define ADDR_CAST __force void *

/* IO access macros */
#define IOREAD64(b, o) vha_plat_read64((ADDR_CAST)b + (o))
#define IOWRITE64(b, o, v) vha_plat_write64((ADDR_CAST)b + (o), v)

/* write value to register and log into pdump file */
#define IOWRITE64_PDUMP(v, r) do {				\
		uint64_t _val_ = v;					\
		vha_plat_write64((ADDR_CAST)vha->reg_base + r, _val_);	\
		img_pdump_printf("WRW64 :REG:%#x %#llx\n",	\
				 (r), _val_);		\
	} while (0)

/* poll c-times for the exact register value(v) masked with m,
 * using d-cycles delay between polls and log into pdump file */
#define IOPOLL64_PDUMP(v, c, d, m, r) do {				\
		uint64_t _req_ = v & m;					\
		uint64_t _val_ = ~_req_;						\
		int _count_ = c;						\
		while (--_count_ >= 0 && _val_ != _req_) {			\
			_val_ = vha_plat_read64(	\
					(ADDR_CAST)vha->reg_base + ((r))) & m;\
			if ((_val_ != _req_)) {				\
				if (vha->freq_khz > 0) {		\
					ndelay(d*1000000/vha->freq_khz); \
				} else					\
					udelay(100);			\
			}						\
		}							\
		WARN_ON(_val_ != _req_ && !vha->core_props.num_dummy_devs);	\
		img_pdump_printf("POL64 :REG:%#x %#llx %#llx 0 %d %d\n", \
				(r), _req_, m, c, d);			\
	} while (0)

/* write phys address of buffer to register, and log into pdump */
#define IOWRITE_PDUMP_PHYS(buf, offset, reg) do {			\
		uint64_t __maybe_unused _addr_ = vha_buf_addr(session, buf);	\
		vha_plat_write64(	\
				(ADDR_CAST)session->vha->reg_base + reg,\
				_addr_ + offset);	\
		img_pdump_printf(					\
			"WRW64 :REG:%#x "_PMEM_":BLOCK_%d:%#x -- '%s%s'\n",	\
			reg, buf->id, offset, buf->name,		\
				buf->pcache.valid ? "_cached" : "");	\
	} while (0)

/* write virt address of buffer to register, and log into pdump */
#define IOWRITE_PDUMP_VIRT(buf, offset, reg) \
		IOWRITE64_PDUMP(buf->devvirt + offset, reg)

/* write address of buffer to register and log into pdump file */
#define IOWRITE_PDUMP_BUFADDR(session, buf, offset, reg) do {		\
		if (session->vha->mmu_mode)				\
			IOWRITE_PDUMP_VIRT(buf, offset, reg);		\
		else							\
			IOWRITE_PDUMP_PHYS(buf, offset, reg);		\
	} while (0)



/* extract bitfield from a register value */
static inline
uint64_t _get_bits(uint64_t val, uint32_t shift, uint64_t mask)
{
	return (val & mask) >> shift;
}
/* set bitfield in a register value */
static inline
uint64_t _set_bits(uint64_t val, uint32_t shift, uint64_t mask)
{
	uint64_t v = val << shift;

	return v & mask;
}

/* utility macros for manipulating fields within registers */
/* apply bitmask */
#define VHA_CR_BITMASK(reg, field)			\
	(~VHA_CR_##reg##_##field##_CLRMSK)
/* get field from register */
#define VHA_CR_GETBITS(reg, field, val)			\
	_get_bits(val,					\
		 VHA_CR_##reg##_##field##_SHIFT,	\
		 VHA_CR_BITMASK(reg, field))
/* get value of a field in a register, taking alignment into account */
#define VHA_CR_ALIGN_GETBITS(reg, field, val)		\
	(VHA_CR_GETBITS(reg, field, val)		\
	 << VHA_CR_##reg##_##field##_ALIGNSHIFT)

/* apply bitmask - OS dependent */
#define VHA_CR_BITMASK_OS(reg, field)			\
	~OSID_TOKEN(VHA_CR_OS, _OSID_, _ ## reg ## _ ## field ## _CLRMSK)
/* get field from register - OS dependent */
#define VHA_CR_GETBITS_OS(reg, field, val)			\
	_get_bits(val,					\
		 OSID_TOKEN(VHA_CR_OS, _OSID_, _ ## reg ## _ ## field ## _SHIFT), \
		 VHA_CR_BITMASK_OS(reg, field))
/* get value of a field in a register, taking alignment into account - OS */
#define VHA_CR_ALIGN_GETBITS_OS(reg, field, val)		\
	(VHA_CR_GETBITS_OS(reg, field, val)		\
	 << OSID_TOKEN(VHA_CR_OS, _OSID_, _ ## reg ## _ ## field ## _ALIGNSHIFT)) \

/* max value of a field */
#define VHA_CR_MAX(reg, field)				\
	VHA_CR_GETBITS(reg, field, ~0ULL)
/* max value of an field taking alignment into account */
#define VHA_CR_ALIGN_MAX(reg, field)			\
	(VHA_CR_MAX(reg, field)				\
	 << VHA_CR_##reg##_##field##_SHIFT)

/* max value of a field - OS dependent */
#define VHA_CR_MAX_OS(reg, field)				\
	VHA_CR_GETBITS_OS(reg, field, ~0ULL)
/* max value of an field taking alignment into account - OS dependent */
#define VHA_CR_ALIGN_MAX_OS(reg, field)			\
	(VHA_CR_MAX_OS(reg, field)				\
	 << OSID_TOKEN(VHA_CR_OS, _OSID_, _ ## reg ## _ ## field ## _SHIFT)) \

/* set value of a field within a register */
#define VHA_CR_SETBITS(reg, field, val)			\
	_set_bits(val,					\
		 VHA_CR_##reg##_##field##_SHIFT,	\
		 VHA_CR_BITMASK(reg, field))
/* set value of a field within a register reducing value by alignment */
#define VHA_CR_ALIGN_SETBITS(reg, field, val)		\
	VHA_CR_SETBITS(					\
		reg, field, (val)			\
	 >> VHA_CR_##reg##_##field##_ALIGNSHIFT)

/* set value of a field within a register - OS dependent */
#define VHA_CR_SETBITS_OS(reg, field, val)			\
	_set_bits(val,					\
		 OSID_TOKEN(VHA_CR_OS, _OSID_, _ ## reg ## _ ## field ## _SHIFT), \
		 VHA_CR_BITMASK_OS(reg, field))
/* set value of a field within a register reducing value by alignment - OS */
#define VHA_CR_ALIGN_SETBITS_OS(reg, field, val)		\
	VHA_CR_SETBITS_OS(			\
		reg, field, (val)		\
	 >> OSID_TOKEN(VHA_CR_OS, _OSID_, _ ## reg ## _ ## field ## _ALIGNSHIFT)) \

/* clear bits of a field within a register */
#define VHA_CR_CLEARBITS(val, reg, field)			\
	(val &= ~VHA_CR_BITMASK(reg, field))
/* clear bits of a field within a register - OS dependent */
#define VHA_CR_CLEARBITS_OS(val, reg, field)			\
	(val &= ~VHA_CR_BITMASK_OS(reg, field))

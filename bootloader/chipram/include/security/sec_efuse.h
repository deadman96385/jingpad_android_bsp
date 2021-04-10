#ifndef _SEC_EFUSE_H_
#define _SEC_EFUSE_H_

#if defined(CONFIG_SOC_IWHALE2) || defined(CONFIG_SOC_ISHARKL2)
#include "sec_iefuse.h"
#endif

#ifdef CONFIG_ARCH_SCX35L2
#include "sec_efuse_sharkl2.h"
#endif

#ifdef CONFIG_SOC_SHARKLJ1
#include "sec_efuse_sharklj1.h"
#endif

#ifdef CONFIG_SOC_SHARKLE
#include "sec_efuse_sharkle.h"
#endif

#ifdef CONFIG_SOC_SHARKL3
#include "sec_efuse_sharkl3.h"
#endif

#ifdef CONFIG_SOC_SHARKL5
#include "sec_efuse_sharkl5.h"
#endif

#ifdef CONFIG_SOC_SHARKL5PRO
#include "sec_efuse_sharkl5pro.h"
#endif

#ifdef CONFIG_SOC_ROC1
#include "sec_efuse_roc1.h"
#endif

#ifdef CONFIG_SOC_ORCA
#include "sec_efuse_orca.h"
#endif

#ifdef CONFIG_SOC_PIKE2
#include "sec_efuse_pike2.h"
#endif

#endif

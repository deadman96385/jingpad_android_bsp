#ifndef _SPRD_REG_EIC_H_
#define _SPRD_REG_EIC_H_

#define SPRD_ADIE_EIC_START 160
#if defined(CONFIG_ADIE_SC2723S)||defined(CONFIG_ADIE_SC2723)
#define SPRD_ADIE_EIC_END   170
#elif defined(CONFIG_ADIE_SC2731)
#define SPRD_ADIE_EIC_END   172
#else
#define SPRD_ADIE_EIC_END   167
#endif

#define EIC_CHG_INT         160
#if defined(CONFIG_ADIE_SC2731)
#define EIC_PBINT 161
#define EIC_PBINT2 162
#else
#define EIC_PBINT2          161
#define EIC_PBINT           162
#endif
#define EIC_AUDIO_HEAD_BTN  163
#define EIC_AUDIO_HEAD_INS  164
#define EIC_AUDIO_HEAD_INS2 165
#define EIC_VCHG_OVI        166
#define EIC_VBAT_OVI        167

#if defined(CONFIG_ADIE_SC2723S) || defined(CONFIG_ADIE_SC2723) \
	|| defined(CONFIG_ADIE_SC2731)
#define EIC_AUDIO_HEAD_INS3	168
#define EIC_BATDET		169
#define EIC_KEY2_7S_RST_EXT_RSTN_ACTIVE		170
#if defined(CONFIG_ADIE_SC2731)
#define EIC_SWITCHG_VIN1_OVI	171
#define EIC_EXT_XTL_EN0		172
#endif
#endif

#define SPRD_DDIE_EIC_START 0
#define SPRD_DDIE_EIC_END   4
#define SPRD_DDIE_EIC_EXTINT3 3
#define SPRD_DDIE_EIC_EXTINT2 2

#endif

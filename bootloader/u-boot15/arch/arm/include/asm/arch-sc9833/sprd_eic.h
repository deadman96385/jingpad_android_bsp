#ifndef _SPRD_REG_EIC_H_
#define _SPRD_REG_EIC_H_

#define SPRD_ADIE_EIC_START 160
#if defined(CONFIG_ADIE_SC2723S)||defined(CONFIG_ADIE_SC2723)||defined(CONFIG_ADIE_SC2721)
#define SPRD_ADIE_EIC_END   170
#else
#define SPRD_ADIE_EIC_END   167
#endif

#define EIC_CHG_INT         160
#if defined(CONFIG_ADIE_SC2721)
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
#if defined(CONFIG_ADIE_SC2723S)||defined(CONFIG_ADIE_SC2723)||defined(CONFIG_ADIE_SC2721)
#define EIC_AUDIO_HEAD_INS3 168
#define EIC_BATDET		169
#define EIC_KEY2_7S_RST_EXT_RSTN_ACTIVE        170
#endif

/*
 * name of macro uses FUNCTION1 name from specification, which is same as name
 * from pinmap file.
 */
#define SPRD_DDIE_EIC_START 0
#define SPRD_DDIE_EIC_KEYIN0 2
#define SPRD_DDIE_EIC_END   7
#define SPRD_DDIE_EIC1_START 8
#define SPRD_DDIE_EIC1_END   15
#define SPRD_DDIE_EIC_EXTINT1 2


#endif
